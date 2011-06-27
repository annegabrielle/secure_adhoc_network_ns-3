/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2009 University of Washington
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include "ns3/log.h"
#include "ns3/ipv4.h"
#include "ns3/ipv4-route.h"
#include "ns3/node.h"
#include "ns3/ipv4-static-routing.h"
#include "ipv4-list-routing.h"

NS_LOG_COMPONENT_DEFINE ("Ipv4ListRouting");

namespace ns3 {

NS_OBJECT_ENSURE_REGISTERED (Ipv4ListRouting);

TypeId
Ipv4ListRouting::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::Ipv4ListRouting")
    .SetParent<Ipv4RoutingProtocol> ()
    .AddConstructor<Ipv4ListRouting> ()
    ;
  return tid;
}


Ipv4ListRouting::Ipv4ListRouting () 
 : m_ipv4 (0)
{
  NS_LOG_FUNCTION_NOARGS ();
}

Ipv4ListRouting::~Ipv4ListRouting () 
{
  NS_LOG_FUNCTION_NOARGS ();
}

void
Ipv4ListRouting::DoDispose (void)
{
  NS_LOG_FUNCTION_NOARGS ();
  for (Ipv4RoutingProtocolList::iterator rprotoIter = m_routingProtocols.begin ();
       rprotoIter != m_routingProtocols.end (); rprotoIter++)
    {
      // Note:  Calling dispose on these protocols causes memory leak
      //        The routing protocols should not maintain a pointer to
      //        this object, so Dispose() shouldn't be necessary.
      (*rprotoIter).second = 0;
    }
  m_routingProtocols.clear ();
  m_ipv4 = 0;
}

void
Ipv4ListRouting::PrintRoutingTable (Ptr<OutputStreamWrapper> stream) const
{
  *stream->GetStream () << "Node: " << m_ipv4->GetObject<Node> ()->GetId () 
    << " Time: " << Simulator::Now().GetSeconds () << "s " 
    << "Ipv4ListRouting table" << std::endl;
  for (Ipv4RoutingProtocolList::const_iterator i = m_routingProtocols.begin ();
      i != m_routingProtocols.end (); i++)
      {
        *stream->GetStream () << "  Priority: " << (*i).first << " Protocol: " << (*i).second->GetInstanceTypeId () << std::endl;
        (*i).second->PrintRoutingTable (stream);
      }
  *stream->GetStream () << std::endl;
}

void
Ipv4ListRouting::DoStart (void)
{
  for (Ipv4RoutingProtocolList::iterator rprotoIter = m_routingProtocols.begin ();
       rprotoIter != m_routingProtocols.end (); rprotoIter++)
    {
      Ptr<Ipv4RoutingProtocol> protocol = (*rprotoIter).second;
      protocol->Start ();
    }
  Ipv4RoutingProtocol::DoStart ();
}


Ptr<Ipv4Route>
Ipv4ListRouting::RouteOutput (Ptr<Packet> p, const Ipv4Header &header, Ptr<NetDevice> oif, enum Socket::SocketErrno &sockerr)
{
  NS_LOG_FUNCTION (this << header.GetDestination () << " " << header.GetSource () << " " << oif);
  Ptr<Ipv4Route> route;

  for (Ipv4RoutingProtocolList::const_iterator i = m_routingProtocols.begin ();
       i != m_routingProtocols.end (); i++)
    {
      NS_LOG_LOGIC ("Checking protocol " << (*i).second->GetInstanceTypeId () << " with priority " << (*i).first);
      NS_LOG_LOGIC ("Requesting source address for destination " << header.GetDestination ());
      route = (*i).second->RouteOutput (p, header, oif, sockerr);
      if (route)
        {
          NS_LOG_LOGIC ("Found route " << route);
          sockerr = Socket::ERROR_NOTERROR;
          return route;
        }
    }
  NS_LOG_LOGIC ("Done checking " << GetTypeId ());
  NS_LOG_LOGIC ("");
  sockerr = Socket::ERROR_NOROUTETOHOST;
  return 0;
}

// Patterned after Linux ip_route_input and ip_route_input_slow
bool 
Ipv4ListRouting::RouteInput (Ptr<const Packet> p, const Ipv4Header &header, Ptr<const NetDevice> idev, 
                             UnicastForwardCallback ucb, MulticastForwardCallback mcb, 
                             LocalDeliverCallback lcb, ErrorCallback ecb)
{
  bool retVal = false;
  NS_LOG_FUNCTION (p << header << idev);
  NS_LOG_LOGIC ("RouteInput logic for node: " << m_ipv4->GetObject<Node> ()->GetId ());

  NS_ASSERT (m_ipv4 != 0);
  // Check if input device supports IP 
  NS_ASSERT (m_ipv4->GetInterfaceForDevice (idev) >= 0);
  uint32_t iif = m_ipv4->GetInterfaceForDevice (idev); 

  retVal = m_ipv4->IsDestinationAddress (header.GetDestination (), iif);
  if (retVal == true)
    {
      NS_LOG_LOGIC ("Address "<< header.GetDestination () << " is a match for local delivery");
      if (header.GetDestination ().IsMulticast ())
        {
          Ptr<Packet> packetCopy = p->Copy();
          lcb (packetCopy, header, iif);
          retVal = true;
          // Fall through
        }
      else
        {
          lcb (p, header, iif);
          return true;
        }
    }
  // Check if input device supports IP forwarding
  if (m_ipv4->IsForwarding (iif) == false)
    {
      NS_LOG_LOGIC ("Forwarding disabled for this interface");
      ecb (p, header, Socket::ERROR_NOROUTETOHOST);
      return false;
    }
  // Next, try to find a route
  // If we have already delivered a packet locally (e.g. multicast)
  // we suppress further downstream local delivery by nulling the callback
  LocalDeliverCallback downstreamLcb = lcb;
  if (retVal == true)
    {
      downstreamLcb = MakeNullCallback<void, Ptr<const Packet>, const Ipv4Header &, uint32_t > ();
    }
  for (Ipv4RoutingProtocolList::const_iterator rprotoIter =
         m_routingProtocols.begin ();
       rprotoIter != m_routingProtocols.end ();
       rprotoIter++)
    {
      if ((*rprotoIter).second->RouteInput (p, header, idev, ucb, mcb, downstreamLcb, ecb))
        {
          NS_LOG_LOGIC ("Route found to forward packet in protocol " << (*rprotoIter).second->GetInstanceTypeId ().GetName ()); 
          return true;
        }
    }
  // No routing protocol has found a route.  
  return retVal;
}

void 
Ipv4ListRouting::NotifyInterfaceUp (uint32_t interface)
{
  NS_LOG_FUNCTION (this << interface);
  for (Ipv4RoutingProtocolList::const_iterator rprotoIter =
         m_routingProtocols.begin ();
       rprotoIter != m_routingProtocols.end ();
       rprotoIter++)
    {
      (*rprotoIter).second->NotifyInterfaceUp (interface);
    }  
}
void 
Ipv4ListRouting::NotifyInterfaceDown (uint32_t interface)
{
  NS_LOG_FUNCTION (this << interface);
  for (Ipv4RoutingProtocolList::const_iterator rprotoIter =
         m_routingProtocols.begin ();
       rprotoIter != m_routingProtocols.end ();
       rprotoIter++)
    {
      (*rprotoIter).second->NotifyInterfaceDown (interface);
    }  
}
void 
Ipv4ListRouting::NotifyAddAddress (uint32_t interface, Ipv4InterfaceAddress address)
{
  NS_LOG_FUNCTION(this << interface << address);
  for (Ipv4RoutingProtocolList::const_iterator rprotoIter =
         m_routingProtocols.begin ();
       rprotoIter != m_routingProtocols.end ();
       rprotoIter++)
    {
      (*rprotoIter).second->NotifyAddAddress (interface, address);
    }  
}
void 
Ipv4ListRouting::NotifyRemoveAddress (uint32_t interface, Ipv4InterfaceAddress address)
{
  NS_LOG_FUNCTION(this << interface << address);
  for (Ipv4RoutingProtocolList::const_iterator rprotoIter =
         m_routingProtocols.begin ();
       rprotoIter != m_routingProtocols.end ();
       rprotoIter++)
    {
      (*rprotoIter).second->NotifyRemoveAddress (interface, address);
    }  
}
void 
Ipv4ListRouting::SetIpv4 (Ptr<Ipv4> ipv4)
{
  NS_LOG_FUNCTION(this << ipv4);
  NS_ASSERT (m_ipv4 == 0);
  for (Ipv4RoutingProtocolList::const_iterator rprotoIter =
         m_routingProtocols.begin ();
       rprotoIter != m_routingProtocols.end ();
       rprotoIter++)
    {
      (*rprotoIter).second->SetIpv4 (ipv4);
    }  
  m_ipv4 = ipv4;
}

void
Ipv4ListRouting::AddRoutingProtocol (Ptr<Ipv4RoutingProtocol> routingProtocol, int16_t priority)
{
  NS_LOG_FUNCTION (this << routingProtocol->GetInstanceTypeId () << priority);
  m_routingProtocols.push_back (std::make_pair (priority, routingProtocol));
  m_routingProtocols.sort ( Compare );
  if (m_ipv4 != 0)
    {
      routingProtocol->SetIpv4 (m_ipv4);
    }
}

uint32_t 
Ipv4ListRouting::GetNRoutingProtocols (void) const
{
  NS_LOG_FUNCTION (this);
  return m_routingProtocols.size (); 
}

Ptr<Ipv4RoutingProtocol> 
Ipv4ListRouting::GetRoutingProtocol (uint32_t index, int16_t& priority) const
{
  NS_LOG_FUNCTION (index);
  if (index > m_routingProtocols.size ())
    {
      NS_FATAL_ERROR ("Ipv4ListRouting::GetRoutingProtocol():  index " << index << " out of range");
    }
  uint32_t i = 0;
  for (Ipv4RoutingProtocolList::const_iterator rprotoIter = m_routingProtocols.begin ();
       rprotoIter != m_routingProtocols.end (); rprotoIter++, i++)
    {
      if (i == index)
        {
          priority = (*rprotoIter).first;
          return (*rprotoIter).second;
        }
    }
  return 0;
}

bool 
Ipv4ListRouting::Compare (const Ipv4RoutingProtocolEntry& a, const Ipv4RoutingProtocolEntry& b)
{
  return a.first > b.first;
}


} // namespace ns3

#include "ns3/test.h"
#include "ipv4-list-routing.h"
#include "ns3/ipv4-routing-protocol.h"

namespace ns3 {

class Ipv4ARouting : public Ipv4RoutingProtocol {
public:
  Ptr<Ipv4Route> RouteOutput (Ptr<Packet> p, const Ipv4Header &header, Ptr<NetDevice> oif, Socket::SocketErrno &sockerr)  { return 0;}
  bool RouteInput  (Ptr<const Packet> p, const Ipv4Header &header, Ptr<const NetDevice> idev,
                             UnicastForwardCallback ucb, MulticastForwardCallback mcb,
                             LocalDeliverCallback lcb, ErrorCallback ecb) {return false;}
  void NotifyInterfaceUp (uint32_t interface) {}
  void NotifyInterfaceDown (uint32_t interface) {}
  void NotifyAddAddress (uint32_t interface, Ipv4InterfaceAddress address) {}
  void NotifyRemoveAddress (uint32_t interface, Ipv4InterfaceAddress address) {}
  void SetIpv4 (Ptr<Ipv4> ipv4) {}
  void PrintRoutingTable (Ptr<OutputStreamWrapper> stream) const {}
};

class Ipv4BRouting : public Ipv4RoutingProtocol {
public:
  Ptr<Ipv4Route> RouteOutput (Ptr<Packet> p, const Ipv4Header &header, Ptr<NetDevice> oif, Socket::SocketErrno &sockerr)  { return 0;}
  bool RouteInput  (Ptr<const Packet> p, const Ipv4Header &header, Ptr<const NetDevice> idev,
                             UnicastForwardCallback ucb, MulticastForwardCallback mcb,
                             LocalDeliverCallback lcb, ErrorCallback ecb) {return false;}
  void NotifyInterfaceUp (uint32_t interface) {}
  void NotifyInterfaceDown (uint32_t interface) {}
  void NotifyAddAddress (uint32_t interface, Ipv4InterfaceAddress address) {}
  void NotifyRemoveAddress (uint32_t interface, Ipv4InterfaceAddress address) {}
  void SetIpv4 (Ptr<Ipv4> ipv4) {}
  void PrintRoutingTable (Ptr<OutputStreamWrapper> stream) const {}
};

class Ipv4ListRoutingNegativeTestCase : public TestCase
{
public:
  Ipv4ListRoutingNegativeTestCase();
  virtual bool DoRun (void);
};

Ipv4ListRoutingNegativeTestCase::Ipv4ListRoutingNegativeTestCase()
  : TestCase("Check negative priorities")
{}
bool 
Ipv4ListRoutingNegativeTestCase::DoRun (void)
{
  Ptr<Ipv4ListRouting> lr = CreateObject<Ipv4ListRouting> ();
  Ptr<Ipv4RoutingProtocol> aRouting = CreateObject<Ipv4ARouting> ();
  Ptr<Ipv4RoutingProtocol> bRouting = CreateObject<Ipv4BRouting> ();
  // The Ipv4BRouting should be added with higher priority (larger integer value)
  lr->AddRoutingProtocol (aRouting, -10);
  lr->AddRoutingProtocol (bRouting, -5);
  int16_t first = 3;
  uint32_t num = lr->GetNRoutingProtocols ();
  NS_TEST_ASSERT_MSG_EQ (num, 2, "XXX");
  Ptr<Ipv4RoutingProtocol> firstRp = lr->GetRoutingProtocol (0, first);
  NS_TEST_ASSERT_MSG_EQ (-5, first, "XXX");
  NS_TEST_ASSERT_MSG_EQ (firstRp, bRouting, "XXX");

  // XXX
  return false;
}

class Ipv4ListRoutingPositiveTestCase : public TestCase
{
public:
  Ipv4ListRoutingPositiveTestCase();
  virtual bool DoRun (void);
};

Ipv4ListRoutingPositiveTestCase::Ipv4ListRoutingPositiveTestCase()
  : TestCase("Check positive priorities")
{}
bool 
Ipv4ListRoutingPositiveTestCase::DoRun (void)
{
  Ptr<Ipv4ListRouting> lr = CreateObject<Ipv4ListRouting> ();
  Ptr<Ipv4RoutingProtocol> aRouting = CreateObject<Ipv4ARouting> ();
  Ptr<Ipv4RoutingProtocol> bRouting = CreateObject<Ipv4BRouting> ();
  // The Ipv4ARouting should be added with higher priority (larger integer 
  // value) and will be fetched first below
  lr->AddRoutingProtocol (aRouting, 10);
  lr->AddRoutingProtocol (bRouting, 5);
  int16_t first = 3;
  int16_t second = 3;
  uint32_t num = lr->GetNRoutingProtocols ();
  NS_TEST_ASSERT_MSG_EQ (num, 2, "XXX");
  Ptr<Ipv4RoutingProtocol> firstRp = lr->GetRoutingProtocol (0, first);
  NS_TEST_ASSERT_MSG_EQ (10, first, "XXX");
  NS_TEST_ASSERT_MSG_EQ (firstRp, aRouting, "XXX");
  Ptr<Ipv4RoutingProtocol> secondRp = lr->GetRoutingProtocol (1, second);
  NS_TEST_ASSERT_MSG_EQ (5, second, "XXX");
  NS_TEST_ASSERT_MSG_EQ (secondRp, bRouting, "XXX");
  
  // XXX
  return false;
}

static class Ipv4ListRoutingTestSuite : public TestSuite
{
public:
  Ipv4ListRoutingTestSuite()
    : TestSuite("ipv4-list-routing", UNIT)
  {
    AddTestCase(new Ipv4ListRoutingPositiveTestCase());
    AddTestCase(new Ipv4ListRoutingNegativeTestCase());
  }

} g_ipv4ListRoutingTestSuite;

} // namespace ns3


