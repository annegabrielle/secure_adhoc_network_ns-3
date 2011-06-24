/*
 *
 * BATMAN Routing Protocol
 *
 * Author     : Anne Gabrielle Bowitz
 * Email      : bowitz@stud.ntnu.no
 * Project    : Simulation of a Secure Ad Hoc Network Routing protocol
 * Institution: NTNU (Norwegian University of Science & Technology), ITEM (Institute of Telematics)
 *
 */
#include "batman-routing-protocol.h"
#include "ns3/log.h"
#include "ns3/random-variable.h"
#include "ns3/inet-socket-address.h"
#include "ns3/trace-source-accessor.h"
#include "ns3/udp-socket-factory.h"
#include "ns3/wifi-net-device.h"
#include "ns3/boolean.h"
#include "ns3/double.h"
#include "ns3/uinteger.h"
#include <map>

NS_LOG_COMPONENT_DEFINE ("BatmanRoutingProtocol");

namespace ns3 {
namespace batman {
NS_OBJECT_ENSURE_REGISTERED (RoutingProtocol);

// / UDP Port for BATMAN control traffic
const uint32_t RoutingProtocol::BATMAN_PORT = 269;

/*
 * Record meta-information about a subclass of the base class
 */
TypeId
RoutingProtocol::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::batman::RoutingProtocol")
		  .SetParent<Ipv4RoutingProtocol> ()
		  .AddConstructor<RoutingProtocol> ()
		  .AddAttribute ("OriginatorInterval","Periodic interval between broadcasting of OGMs. ",
				 TimeValue (Seconds (OGM_BROADCAST_INTERVAL)),
				 MakeTimeAccessor (&RoutingProtocol::m_originatorInterval),
				 MakeTimeChecker ())
		.AddAttribute ("Version", "The nodes running BATMAN version.",
                 UintegerValue (DEFAULT_VERSION),
                 MakeUintegerAccessor (&RoutingProtocol::m_version),
                 MakeUintegerChecker<uint8_t> ())
        .AddAttribute ("Sequence Number", "The nodes own sequence number.",
                 UintegerValue (0),
                 MakeUintegerAccessor (&RoutingProtocol::m_lastSeqNoUsed),
                 MakeUintegerChecker<uint16_t> ())
        .AddTraceSource ("Rx", "Receive BATMAN packet.",
        		 MakeTraceSourceAccessor (&RoutingProtocol::m_rxBatmanTrace))
		.AddTraceSource ("Tx", "Send BATMAN packet.",
				 MakeTraceSourceAccessor (&RoutingProtocol::m_txBatmanTrace))
		.AddTraceSource ("ReTx", "Send Reboradcasted BATMAN packet.",
			 MakeTraceSourceAccessor (&RoutingProtocol::m_txReBatmanTrace));

  return tid;
}

RoutingProtocol::RoutingProtocol ()
  : m_originatorList (),
    m_originatorInterval (),
    m_version (DEFAULT_VERSION),
    m_lastSeqNoUsed (0),
	m_originatorIntervalTimer (Timer::CANCEL_ON_DESTROY)
{
}

RoutingProtocol::~RoutingProtocol ()
{
}

/* Close all sockets and clear entire <socket, interfaceaddress> map */
void
RoutingProtocol::DoDispose ()
{
  m_ipv4 = 0;
  for (std::map<Ptr<Socket>, Ipv4InterfaceAddress>::iterator iter = m_socketAddresses.begin (); iter != m_socketAddresses.end (); iter++)
    {
      iter->first->Close ();
    }
  m_socketAddresses.clear ();
  Ipv4RoutingProtocol::DoDispose ();
}

void
RoutingProtocol::PrintRoutingTable (Ptr<OutputStreamWrapper> stream) const
{
}

void
RoutingProtocol::Start ()
{
  m_scb = MakeCallback (&RoutingProtocol::Send,this);
  m_ecb = MakeCallback (&RoutingProtocol::Drop,this);
  m_originatorIntervalTimer.SetFunction (&RoutingProtocol::BroadcastOriginatorMessage,this);
  m_originatorIntervalTimer.Schedule (MicroSeconds (UniformVariable ().GetInteger (0,1000)));
}

/*
 * This lookup is used by transport protocols.  It does not cause any
 * packet to be forwarded, and is synchronous.  Can be used for
 * multicast or unicast.  The Linux equivalent is ip_route_output()
 */
Ptr<Ipv4Route>
RoutingProtocol::RouteOutput (Ptr<Packet> p,
                              const Ipv4Header &header,
                              Ptr<NetDevice> oif,
                              Socket::SocketErrno &sockerr)
{
//  NS_LOG_FUNCTION (this << header << (oif ? oif->GetIfIndex () : 0));

  if (!p)
    {
      NS_LOG_LOGIC ("Packet empty");
      Ptr<Ipv4Route> emptyPacketRoute;
      return emptyPacketRoute;
    }

  if (m_socketAddresses.empty ())
    {
      sockerr = Socket::ERROR_NOROUTETOHOST;
      NS_LOG_LOGIC ("No batman interfaces");
      Ptr<Ipv4Route> route;
      return route;
    }

  std::map<Ipv4Address, OriginatorListEntry> removedAddresses;
  sockerr = Socket::ERROR_NOTERROR;
  Ptr<Ipv4Route> route;
  Ipv4Address dst = header.GetDestination ();
//  NS_LOG_DEBUG ("Find route to " << dst);
  OriginatorListEntry rt;

  m_originatorList.Purge (removedAddresses, Simulator::Now());

  if (m_originatorList.LookupRoute (dst,rt))
    {
      route = rt.GetRoute ();
      NS_ASSERT (route != 0);
      if ( dst != "10.0.0.255")
      {
    	  NS_LOG_DEBUG ("A route exists from " << route->GetSource () << " to " << dst << " via "<< rt.GetNextHop () );
      }

      if (oif != 0 && route->GetOutputDevice () != oif)
       {
    	  NS_LOG_DEBUG ("Output device doesn't match. Dropped.");
          sockerr = Socket::ERROR_NOROUTETOHOST;
          return Ptr<Ipv4Route> ();
       }
      return route;
    }
  NS_LOG_DEBUG (m_mainAddress << " says: No route found to " << dst);
  Ptr<Ipv4Route> emptyRoute;
  return emptyRoute;
}

/*
 * This lookup is used in the forwarding process.  The packet is
 * handed over to the Ipv4RoutingProtocol, and will get forwarded onward
 * by one of the callbacks.  The Linux equivalent is ip_route_input().
 * There are four valid outcomes, and a matching callbacks to handle each.
 */
bool
RoutingProtocol::RouteInput (Ptr<const Packet> p,
                             const Ipv4Header &header,
                             Ptr<const NetDevice> idev,
                             UnicastForwardCallback ucb,
                             MulticastForwardCallback mcb,
                             LocalDeliverCallback lcb,
                             ErrorCallback ecb)
{
//  NS_LOG_FUNCTION (m_mainAddress << " received packet " << p->GetUid ()<< " from " << header.GetSource ()<< " on interface " << idev->GetAddress ()<< " to destination " << header.GetDestination ());

  if (m_socketAddresses.empty ())
    {
      NS_LOG_DEBUG ("No BATMAN interfaces");
      return false;
    }
  NS_ASSERT (m_ipv4 != 0);
  // Check if input device supports IP
  NS_ASSERT (m_ipv4->GetInterfaceForDevice (idev) >= 0);
  int32_t iif = m_ipv4->GetInterfaceForDevice (idev);

  Ipv4Address dst = header.GetDestination ();
  Ipv4Address origin = header.GetSource ();

  for (std::map<Ptr<Socket>, Ipv4InterfaceAddress>::const_iterator j = m_socketAddresses.begin (); j != m_socketAddresses.end (); ++j)
    {
      Ipv4InterfaceAddress iface = j->second;
      if (origin == iface.GetLocal ())
        {
          return true;
        }
    }
  // LOCAL DELIVARY TO BATMAN INTERFACES
  for (std::map<Ptr<Socket>, Ipv4InterfaceAddress>::const_iterator j = m_socketAddresses.begin (); j != m_socketAddresses.end (); ++j)
    {
      Ipv4InterfaceAddress iface = j->second;

      if (m_ipv4->GetInterfaceForAddress (iface.GetLocal ()) == iif)
        {
          if (dst == iface.GetBroadcast () || dst.IsBroadcast ())
            {
//              NS_LOG_LOGIC ("Broadcast local delivery to " << iface.GetLocal ());
              Ptr<Packet> packet = p->Copy ();
              lcb (p,header,iif);
              if (header.GetTtl () > 1)
                {
                  NS_LOG_LOGIC ("Forward broadcast. TTL " << (uint16_t) header.GetTtl ());
                  OriginatorListEntry toBroadcast;
                  if (m_originatorList.LookupRoute (dst,toBroadcast,true))
                    {
                      Ptr<Ipv4Route> route = toBroadcast.GetRoute ();
                      ucb (route,packet,header);
                    }
                  else
                    {
                      NS_LOG_DEBUG ("No route to forward. Drop packet " << p->GetUid ());
                    }
                }
              return true;
            }
        }
    }

  if (m_ipv4->IsDestinationAddress (dst, iif))
    {
//      NS_LOG_LOGIC ("Unicast local delivery to " << dst);
      lcb (p, header, iif);
      return true;
    }
  OriginatorListEntry toDst;
  if (m_originatorList.LookupRoute (dst,toDst))
    {
      OriginatorListEntry ne;
      if (m_originatorList.LookupRoute (toDst.GetNextHop (),ne))
        {
          Ptr<Ipv4Route> route = ne.GetRoute ();
          NS_LOG_LOGIC (m_mainAddress << " is forwarding packet " << p->GetUid ()
                                      << " to " << dst
                                      << " from " << header.GetSource ()
                                      << " via nexthop neighbor " << toDst.GetNextHop ());
          ucb (route,p,header);
          return true;
        }
    }
  NS_LOG_LOGIC ("Drop packet " << p->GetUid () << " as there is no route to forward it.");
  return false;
}

/* Receive and process an OGM */
void
RoutingProtocol::RecvOriginatorMessage (Ptr<Socket> socket)
{
  Address sourceAddress;
  Ptr<Packet> packet = socket->RecvFrom (sourceAddress);
  InetSocketAddress inetSourceAddr = InetSocketAddress::ConvertFrom (sourceAddress);
  Ipv4Address sender = inetSourceAddr.GetIpv4 ();
  Ipv4Address receiver = m_socketAddresses[socket].GetLocal ();
  Ptr<NetDevice> dev = m_ipv4->GetNetDevice (m_ipv4->GetInterfaceForAddress (receiver));
  uint32_t packetSize = packet->GetSize ();
  uint32_t count = 0;

  /* Process one packet at the time. Size 20 bytes */
  for (; packetSize > 0; packetSize = packetSize - 20)
    {
	  /* Trace BATMAN packet received */
      m_rxBatmanTrace(packet);

      count = 0;
      BatmanHeader batmanHeader;
      packet->RemoveHeader (batmanHeader);

      NS_LOG_DEBUG (m_mainAddress << " received OGM " << packet->GetUid() << " from " << sender <<
                    " Version: " << (uint16_t)batmanHeader.GetVersion() <<
                    ", UDFlags: " << batmanHeader.GetUDFlags() <<
                    ", TTL: " << (uint16_t)batmanHeader.GetTimeToLive()<<
//                    ", GWFlags: " << (uint16_t)batmanHeader.GetGWFlags()<<
                    ", Seq No: " << batmanHeader.GetSequenceNumber() <<
//                    ", GWPort: " << (uint16_t)batmanHeader.GetGWPort() <<
                    ", Originator Address: " << batmanHeader.GetOriginatorAddress() <<
                    ", Previous Sender: " << batmanHeader.GetPrevSender() <<
                    ", TQ Value: " << (uint16_t)batmanHeader.GetTqValue() <<
//                    ", HNA Length: " << (uint16_t)batmanHeader.GetHnaLength() <<
                    ", AUTH Value: " << batmanHeader.GetAuthValue() );

      /* Check BATMAN version, drop if not equal to own running version */
      if (batmanHeader.GetVersion() != 4){
    	  NS_LOG_FUNCTION (m_mainAddress << " received OGM with wrong version: " << batmanHeader.GetVersion() << " from: " << sender);
    	  count++;
      }

      for (std::map<Ptr<Socket>, Ipv4InterfaceAddress>::const_iterator j = m_socketAddresses.begin (); j != m_socketAddresses.end (); ++j)
        {
    	  Ipv4InterfaceAddress interface = j->second;

    	  /* Check is sender equals own address, drop it true */
    	  if (sender == interface.GetLocal() || sender == m_mainAddress)
    	  {
    		  NS_LOG_DEBUG (m_mainAddress << " received OGM from itself");
    		  count++;
    	  }

    	  /* Check if sender equals own broadcast address, drop if true */
    	  if (sender == interface.GetBroadcast())
    	  {
    		  NS_LOG_DEBUG(m_mainAddress << " ignoring all packets with broadcast source IP");
    		  count++;
    	  }

    	  /* Check if originator address in OGM equals own address, if true count rebroadcasts and drop */
          if (batmanHeader.GetOriginatorAddress() == interface.GetLocal ())
            {
        	  count++;
        	  // TODO: (bat_packet->seqno - if_incoming->out.seqno + 2 == 0)
              if ( (batmanHeader.GetUDFlags() == batman::BatmanHeader::D_FLAG) && (batmanHeader.GetSequenceNumber() == m_lastSeqNoUsed) )
              {
            	  NS_LOG_DEBUG(m_mainAddress << " received own OGM and counting rebroadcasts!");
            	  m_originatorList.CountRebroadcast(sender);
              }
              else
              {
            	  NS_LOG_DEBUG("Bidirectional failed! Sequence numbers not equal: " << batmanHeader.GetSequenceNumber() << " != " << m_lastSeqNoUsed << "\n");
              }
              return;
            }

          /* Check if TQ value in OGM equals zero, drop if true */
    	  if (batmanHeader.GetTqValue() == 0)
    	  {
              /* Get Originator and neighbor (sender), create new originator or neighbor if they do not already exist */
        	  OriginatorListEntry *originatorEntry = NULL;
        	  m_originatorList.GetOriginator2(batmanHeader.GetOriginatorAddress(), Simulator::Now(), batmanHeader, dev, interface, &originatorEntry);
        	  NS_LOG_DEBUG(m_mainAddress << " received OGM with TQ value 0");
    		  count++;
    	  }

    	  /* Check if previous sender field equals own address, drop if true */
    	  if (batmanHeader.GetPrevSender() == m_mainAddress)
    	  {
    		  NS_LOG_DEBUG(m_mainAddress << " is the previous sender in this OGM!");
    		  count++;
    	  }

    	  /* Drop packet */
          if (count > 0)
          {
        	  NS_LOG_DEBUG(" -- Packet " << packet->GetUid() << " silently dropped! -- \n");
        	  count = 0;
        	  continue;
          }

          /* Get Originator and neighbor (sender), create new originator or neighbor if they do not already exist */
    	  OriginatorListEntry *originatorEntry = NULL;
    	  m_originatorList.GetOriginator2(batmanHeader.GetOriginatorAddress(), Simulator::Now(), batmanHeader, dev, interface, &originatorEntry);

    	  /* Check if OGM is duplicate and count received packets */
    	  uint8_t isDuplicate = originatorEntry->CountRealPackets(batmanHeader, sender);

          /* Check if neighbor is bidirectional, calculate local TQ and new TQ to put in rebroadcast */
    	 uint8_t isBidirectional = originatorEntry->BidirectionalCheck(sender, Simulator::Now(), batmanHeader, m_originatorList.GetRebroadcastCount(sender), batmanHeader.GetTqValue());

    	 /* If neighbor is bidirectional, then update the next hop towards this originator. Includes adding received TQ in packet and calculating avg recv TQ */
    	 if ((isBidirectional) &&
    		((!isDuplicate)||((originatorEntry->GetCurrentSeqNumber() == batmanHeader.GetSequenceNumber()) && ((originatorEntry->GetLastTTL()-3)<=batmanHeader.GetTimeToLive()))) )
    	 {
    		 m_originatorList.UpdateOriginator(originatorEntry->GetDestination(), sender, batmanHeader, isDuplicate);
    		 m_originatorList.Print(m_mainAddress);
    	 }

    	 /* If sender(neighbor) generated the OGM, don't check if bidirectional or duplicate, just rebroadcast */
         if (sender == batmanHeader.GetOriginatorAddress() && (batmanHeader.GetTimeToLive()-1) != 0)
         {
			  ReBroadcastOriginatorMessage(batmanHeader, sender, interface, packet->GetUid());
			  return;
         }

         /* Check if neighbor (sender) is not bidirectional, drop if true */
    	  if (!isBidirectional)
    	  {
    		  NS_LOG_DEBUG(m_mainAddress << " received OGM via a non bidirectional link!");
    		  count++;
    	  }

    	  /* Check if OGM is a duplicate packet, drop if true */
    	  if(isDuplicate)
    	  {
    		  NS_LOG_DEBUG(m_mainAddress << " received a duplicate OGM! " << originatorEntry->GetCurrentSeqNumber() << " = " << batmanHeader.GetSequenceNumber());
    		  count++;
    	  }

    	  /* Drop packet */
          if (count > 0)
          {
        	  NS_LOG_DEBUG(" -- Packet " << packet->GetUid() << " silently dropped! -- \n");
        	  count = 0;
        	  continue;
          }

      /* Check if TTL after decrementation is bigger than zero, reboradcast OGM if true  */
      if ((batmanHeader.GetTimeToLive()-1) > 0)
      {
    	  ReBroadcastOriginatorMessage(batmanHeader, sender, interface, packet->GetUid());
      }
      /* Drop OGM if TTL is smaller than or equal to zero after decrementation */
      else
      {
    	  NS_LOG_FUNCTION(" Time To Live = 0! Packet silently dropped!");
      }
    }
  }
}

/*
 * Periodically generate and broadcasts new OGM every m_originatorInterval
 */
void
RoutingProtocol::BroadcastOriginatorMessage ()
{
	  std::map<Ipv4Address, OriginatorListEntry> removedAddresses, allRoutes;

	  /* Purge originator list of expired routes before broadcasting */
	  m_originatorList.Purge(removedAddresses, Simulator::Now());

	  m_originatorList.GetListOfAllRoutes (allRoutes);

	  if (allRoutes.size () < 0)
	    {
	      return;
	    }

	  for (std::map<Ptr<Socket>, Ipv4InterfaceAddress>::const_iterator j = m_socketAddresses.begin (); j != m_socketAddresses.end (); ++j)
	    {
	      Ptr<Socket> socket = j->first;
	      Ipv4InterfaceAddress iface = j->second;
	      Ptr<Packet> packet = Create<Packet> ();
	      BatmanHeader batmanHeader;

	      /* Create BATMAN header */
	      batmanHeader.SetVersion(m_version);
	      batmanHeader.SetUDFlags(batman::BatmanHeader::_UD_FLAG);
	      batmanHeader.SetTimeToLive(DEFAULT_TTL);
	      batmanHeader.SetGWFlags(0);
	      m_lastSeqNoUsed = (m_lastSeqNoUsed+1) % (MAX_SEQUENCE_NUMBER);
	      batmanHeader.SetSequenceNumber(m_lastSeqNoUsed);
	      batmanHeader.SetGWPort(0);
	      batmanHeader.SetOriginatorAddress(m_mainAddress);
	      batmanHeader.SetPrevSender(m_mainAddress);
	      batmanHeader.SetTqValue(MAX_TQ_VALUE);
	      batmanHeader.SetHnaLength(0);
	      batmanHeader.SetAuthValue(0);
	      packet->AddHeader (batmanHeader);

	      NS_LOG_DEBUG ("** Broadcasting OGM " << packet->GetUid() <<
	    		  	  	"- Version: "<< (uint16_t)batmanHeader.GetVersion() <<
	    		        " TTL: " << (uint16_t)batmanHeader.GetTimeToLive() <<
	    		        " SeqNo: " << batmanHeader.GetSequenceNumber() <<
	    		        " GWPort: " << batmanHeader.GetGWPort() <<
	    		        " OrgAddr: " << batmanHeader.GetOriginatorAddress() <<
	    		        " PrevSender: " << batmanHeader.GetPrevSender() <<
	    		        " TqValue: " << (uint16_t)batmanHeader.GetTqValue() <<
	    		        " HnaLength: " << batmanHeader.GetHnaLength() <<
	    		        " AuthValue: " << batmanHeader.GetAuthValue() << "\n");

//	      NS_LOG_FUNCTION ("OGM Packet UID is : " << packet->GetUid () << " and destination is: " << iface.GetBroadcast ());

	      m_originatorList.BitGetPacketNeighbors();

	      /* Add RouitngTimestampTag to packet */
	      RoutingTimestampTag tag;
	      tag.SetTimestamp(Simulator::Now());
	      packet->AddByteTag(tag);

	      /* Trace BATMAN packet sent */
	      m_txBatmanTrace(packet);

	      socket->Send (packet);

	      // Send to all-hosts broadcast if on /32 addr, subnet-directed otherwise
	      Ipv4Address destination;
	      if (iface.GetMask () == Ipv4Mask::GetOnes ())
	        {
	          destination = Ipv4Address ("255.255.255.255");
	        }
	      else
	        {
	          destination = iface.GetBroadcast ();
	        }

	      socket->SendTo (packet, 0, InetSocketAddress (destination, BATMAN_PORT));
	    }
	  /* Update OGM interval */
	  m_originatorIntervalTimer.Schedule (m_originatorInterval + MicroSeconds (25 * UniformVariable ().GetInteger (0,1000)));
}

/*
 * Rebroadcast received OGM
 */
void
RoutingProtocol::ReBroadcastOriginatorMessage(BatmanHeader b, Ipv4Address s, Ipv4InterfaceAddress iface, uint64_t uid)
{
	  std::map<Ipv4Address, OriginatorListEntry> removedAddresses, allRoutes;

	  /* Purge originator list of expired routes before broadcasting */
	  m_originatorList.Purge(removedAddresses, Simulator::Now());

	  m_originatorList.GetListOfAllRoutes (allRoutes);
	  if (allRoutes.size () < 0)
	    {
	      return;
	    }

	  for (std::map<Ptr<Socket>, Ipv4InterfaceAddress>::const_iterator j = m_socketAddresses.begin (); j != m_socketAddresses.end (); ++j)
	    {
	      Ptr<Socket> socket = j->first;
	      Ipv4InterfaceAddress interface = j->second;
	      Ptr<Packet> packet = Create<Packet> ();

	      /* Check if OGM is rebroadcasted on same interface as it was received, set Direct-Link Flag if true */
	      if (interface == iface && b.GetOriginatorAddress() == s)
	      {
	    	  b.SetUDFlags(batman::BatmanHeader::D_FLAG);
	      }

	      /* Decrement Time To Live field */
	      b.SetTimeToLive(b.GetTimeToLive()-1);

	      /* Set Previous Sender field */
	      b.SetPrevSender(s);

	      OriginatorListEntry *originatorEntry;
	      m_originatorList.GetOriginator(b.GetOriginatorAddress(), &originatorEntry);

	      /* Rebroadcast the best TQ value towards the originator */
	      if (s != originatorEntry->GetNextHop() && originatorEntry->GetNextHop() != "0.0.0.0")
	      {
	    	  NeighborInformationEntry *n;
	    	  originatorEntry->GetNeighbor(originatorEntry->GetNextHop(), &n);
	    	  b.SetTqValue(n->GetTqAvg());
	    	  NS_LOG_DEBUG("*****Sent a different TQ value!");
	      }
	      else
	      {
	    	  b.SetTqValue(originatorEntry->GetNewestTqValue());
	      }

	      /* Add hop penalty*/
	      b.SetTqValue((b.GetTqValue() * (MAX_TQ_VALUE - HOP_PENALTY)/MAX_TQ_VALUE));

	      packet->AddHeader(b);

		  NS_LOG_DEBUG ("* " << m_mainAddress << " is rebroadcasting OGM " << uid << "->"<<packet->GetUid()<<" "
				  	  	  "with TTL = " << (uint16_t) b.GetTimeToLive() <<
				  	  	  " UDflags = " << b.GetUDFlags() <<
				  	  	  " TqValue = " << (uint16_t) b.GetTqValue() <<
				  	  	  " PrevSender = " << b.GetPrevSender() << "\n");

		  /* Trace OGM transmitted */
	      m_txBatmanTrace(packet);
	      m_txReBatmanTrace(packet);

	      socket->Send (packet);

	      // Send to all-hosts broadcast if on /32 addr, subnet-directed otherwise
	      Ipv4Address destination;
	      if (interface.GetMask () == Ipv4Mask::GetOnes ())
	        {
	          destination = Ipv4Address ("255.255.255.255");
	        }
	      else
	        {
	          destination = interface.GetBroadcast ();
	        }
	      socket->SendTo (packet, 0, InetSocketAddress (destination, BATMAN_PORT));
	    }
}

void
RoutingProtocol::SetIpv4 (Ptr<Ipv4> ipv4)
{
  NS_ASSERT (ipv4 != 0);
  NS_ASSERT (m_ipv4 == 0);
  NS_LOG_DEBUG ("Created batman::RoutingProtocol");
  Simulator::ScheduleNow (&RoutingProtocol::Start,this);

  m_ipv4 = ipv4;
}

void
RoutingProtocol::NotifyInterfaceUp (uint32_t i)
{
  NS_LOG_FUNCTION (this << m_ipv4->GetAddress (i, 0).GetLocal ()
                        << " interface is up");
  Ptr<Ipv4L3Protocol> l3 = m_ipv4->GetObject<Ipv4L3Protocol> ();
  Ipv4InterfaceAddress iface = l3->GetAddress (i,0);
  if (iface.GetLocal () == Ipv4Address ("127.0.0.1"))
    {
      return;
    }
  // Create a socket to listen only on this interface
  Ptr<Socket> socket = Socket::CreateSocket (GetObject<Node> (),UdpSocketFactory::GetTypeId ());
  NS_ASSERT (socket != 0);
  socket->SetRecvCallback (MakeCallback (&RoutingProtocol::RecvOriginatorMessage,this));
  socket->BindToNetDevice (l3->GetNetDevice (i));
  socket->Bind (InetSocketAddress (Ipv4Address::GetAny (), BATMAN_PORT));
  socket->SetAllowBroadcast (true);
  socket->SetAttribute ("IpTtl",UintegerValue (1));
  m_socketAddresses.insert (std::make_pair (socket,iface));
  // Add local broadcast record to the routing table
  Ptr<NetDevice> dev = m_ipv4->GetNetDevice (m_ipv4->GetInterfaceForAddress (iface.GetLocal ()));
  OriginatorListEntry rt (/*OrgAdd=*/iface.GetBroadcast (), /*Dev=*/dev, /*iface=*/iface, /*LastAwaretime=*/Seconds(0), /*lastTTL*/ 0, /*CurrentSeqNo=*/0);
  rt.SetNextHop(iface.GetBroadcast ());
  m_originatorList.AddOriginator (rt);
  if (m_mainAddress == Ipv4Address ())
    {
      m_mainAddress = iface.GetLocal ();
    }
  NS_ASSERT (m_mainAddress != Ipv4Address ());
}

void
RoutingProtocol::NotifyInterfaceDown (uint32_t i)
{
  Ptr<Ipv4L3Protocol> l3 = m_ipv4->GetObject<Ipv4L3Protocol> ();
  Ptr<NetDevice> dev = l3->GetNetDevice (i);
  Ptr<Socket> socket = FindSocketWithInterfaceAddress (m_ipv4->GetAddress (i,0));
  NS_ASSERT (socket);
  socket->Close ();
  m_socketAddresses.erase (socket);
  if (m_socketAddresses.empty ())
    {
      NS_LOG_LOGIC ("No dsdv interfaces");
      m_originatorList.Clear ();
      return;
    }
  m_originatorList.DeleteAllRoutesFromInterface (m_ipv4->GetAddress (i,0));
}

void
RoutingProtocol::NotifyAddAddress (uint32_t i,
                                   Ipv4InterfaceAddress address)
{
//  NS_LOG_FUNCTION (this << " interface " << i << " address " << address);
  Ptr<Ipv4L3Protocol> l3 = m_ipv4->GetObject<Ipv4L3Protocol> ();
  if (!l3->IsUp (i))
    {
      return;
    }
  Ipv4InterfaceAddress iface = l3->GetAddress (i,0);
  Ptr<Socket> socket = FindSocketWithInterfaceAddress (iface);
  if (!socket)
    {
      if (iface.GetLocal () == Ipv4Address ("127.0.0.1"))
        {
          return;
        }
      Ptr<Socket> socket = Socket::CreateSocket (GetObject<Node> (),UdpSocketFactory::GetTypeId ());
      NS_ASSERT (socket != 0);
      socket->SetRecvCallback (MakeCallback (&RoutingProtocol::RecvOriginatorMessage,this));
      socket->BindToNetDevice (l3->GetNetDevice (i));
      // Bind to any IP address so that broadcasts can be received
      socket->Bind (InetSocketAddress (Ipv4Address::GetAny (), BATMAN_PORT));
      socket->SetAllowBroadcast (true);
      m_socketAddresses.insert (std::make_pair (socket,iface));
      Ptr<NetDevice> dev = m_ipv4->GetNetDevice (m_ipv4->GetInterfaceForAddress (iface.GetLocal ()));
      OriginatorListEntry rt (/*OrgAdd=*/iface.GetBroadcast (), /*Dev=*/dev, /*iface=*/iface, /*LastAwaretime=*/Seconds(0), /*lastTTL*/ 0, /*CurrentSeqNo=*/0);
      rt.SetNextHop(iface.GetBroadcast ());
      m_originatorList.AddOriginator (rt);
    }
}

void
RoutingProtocol::NotifyRemoveAddress (uint32_t i,
                                      Ipv4InterfaceAddress address)
{
  Ptr<Socket> socket = FindSocketWithInterfaceAddress (address);
  if (socket)
    {
      m_socketAddresses.erase (socket);
      Ptr<Ipv4L3Protocol> l3 = m_ipv4->GetObject<Ipv4L3Protocol> ();
      if (l3->GetNAddresses (i))
        {
          Ipv4InterfaceAddress iface = l3->GetAddress (i,0);
          // Create a socket to listen only on this interface
          Ptr<Socket> socket = Socket::CreateSocket (GetObject<Node> (),UdpSocketFactory::GetTypeId ());
          NS_ASSERT (socket != 0);
          socket->SetRecvCallback (MakeCallback (&RoutingProtocol::RecvOriginatorMessage,this));
          // Bind to any IP address so that broadcasts can be received
          socket->Bind (InetSocketAddress (Ipv4Address::GetAny (), BATMAN_PORT));
          socket->SetAllowBroadcast (true);
          m_socketAddresses.insert (std::make_pair (socket,iface));
        }
    }
}

Ptr<Socket>
RoutingProtocol::FindSocketWithInterfaceAddress (Ipv4InterfaceAddress addr) const
{
  for (std::map<Ptr<Socket>, Ipv4InterfaceAddress>::const_iterator j = m_socketAddresses.begin (); j != m_socketAddresses.end (); ++j)
    {
      Ptr<Socket> socket = j->first;
      Ipv4InterfaceAddress iface = j->second;
      if (iface == addr)
        {
          return socket;
        }
    }
  Ptr<Socket> socket;
  return socket;
}

void
RoutingProtocol::Send (Ptr<Ipv4Route> route,
                       Ptr<const Packet> packet,
                       const Ipv4Header & header)
{
	NS_LOG_DEBUG ("BATMAN node " << m_mainAddress << " sending an OGM");
  Ptr<Ipv4L3Protocol> l3 = m_ipv4->GetObject<Ipv4L3Protocol> (); // agb: where does this come from??
  NS_ASSERT (l3 != 0);
  Ptr<Packet> p = packet->Copy ();
  l3->Send (p,route->GetSource (),header.GetDestination (),header.GetProtocol (),route);
}

void
RoutingProtocol::Drop (Ptr<const Packet> packet,
                       const Ipv4Header & header,
                       Socket::SocketErrno err)
{
  NS_LOG_DEBUG (m_mainAddress << " drop packet " << packet->GetUid () << " to " << header.GetDestination () << " from queue. Error " << err);
}

}

//TypeId
//RoutingPacketTag::GetTypeId(void)
//{
//  static TypeId tid = TypeId ("RoutingPacketTag")
//    .SetParent<Tag> ()
//    .AddConstructor<RoutingPacketTag> ()
////    .AddAttribute ("RoutingPacketTag",
////                   "Routing Packet Tag!")
////                   EmptyAttributeValue(),
//////                   MakeTimeAccessor(&RoutingPacketTag::GetRoutingPacketTag),
////                   MakeTraceSourceAccessor(&RoutingPacketTag::GetRoutingPacketTag))
//////                   MakeTimeChecker())
//    ;
//  return tid;
//}
//TypeId
//RoutingPacketTag::GetInstanceTypeId(void) const
//{
//  return GetTypeId ();
//}
//
//uint32_t
//RoutingPacketTag::GetSerializedSize (void) const
//{
//  return 2;
//}
//void
//RoutingPacketTag::Serialize (TagBuffer i) const
//{
////  int64_t t = m_timestamp.GetNanoSeconds();
////  i.Write((const uint8_t *)&t, 8);
//	i.WriteU16( m_routingTag );
//}
//void
//RoutingPacketTag::Deserialize (TagBuffer i)
//{
//  m_routingTag = i.ReadU16();
//}
//
//void
//RoutingPacketTag::SetRoutingPacketTag(uint16_t t)
//{
//  m_routingTag = t;
//}
//uint16_t
//RoutingPacketTag::GetRoutingPacketTag(void) const
//{
//  return m_routingTag;
//}
//
//void
//RoutingPacketTag::Print(std::ostream &os) const
//{
//  os << "t=" << m_routingTag;
//}

TypeId
RoutingTimestampTag::GetTypeId(void)
{
  static TypeId tid = TypeId ("RoutingTimestampTag")
    .SetParent<Tag> ()
    .AddConstructor<RoutingTimestampTag> ()
    .AddAttribute ("Timestamp",
                   "Some momentous point in time!",
                   EmptyAttributeValue(),
                   MakeTimeAccessor(&RoutingTimestampTag::GetTimestamp),
                   MakeTimeChecker())
    ;
  return tid;
}
TypeId
RoutingTimestampTag::GetInstanceTypeId(void) const
{
  return GetTypeId ();
}

uint32_t
RoutingTimestampTag::GetSerializedSize (void) const
{
  return 8;
}
void
RoutingTimestampTag::Serialize (TagBuffer i) const
{
  int64_t t = m_timestamp.GetNanoSeconds();
  i.Write((const uint8_t *)&t, 8);
}
void
RoutingTimestampTag::Deserialize (TagBuffer i)
{
  int64_t t;
  i.Read((uint8_t *)&t, 8);
  m_timestamp = NanoSeconds(t);
}

void
RoutingTimestampTag::SetTimestamp(Time time)
{
  m_timestamp = time;
}
Time
RoutingTimestampTag::GetTimestamp(void) const
{
  return m_timestamp;
}

void
RoutingTimestampTag::Print(std::ostream &os) const
{
  os << "t=" << m_timestamp;
}

}
