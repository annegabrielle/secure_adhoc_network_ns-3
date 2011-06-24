/*
 *
 * BATMAN Originator List
 *
 * Author     : Anne Gabrielle Bowitz
 * Email      : bowitz@stud.ntnu.no
 * Project    : Simulation of a Secure Ad Hoc Network Routing protocol
 * Institution: NTNU (Norwegian University of Science & Technology), ITEM (Institute of Telematics)
 *
 */
#include "batman-rtable.h"
#include "ns3/simulator.h"
#include <iomanip>
#include "ns3/log.h"
#include <math.h>
#include "bitarray.h"
#include "ring-buffer.h"

#define PURGE_TIMEOUT 			200
#define WINDOW_SIZE				8
#define LOCAL_WINDOW_SIZE		64
#define TQ_LOCAL_BIDRECT_SEND_MINIMUM 1
#define TQ_LOCAL_BIDRECT_RECV_MINIMUM 1
#define TQ_TOTAL_BIDRECT_LIMIT	1
#define MAX_TQ_VALUE			255

NS_LOG_COMPONENT_DEFINE ("BatmanOriginatorList");

namespace ns3 {
namespace batman {
NeighborInformationEntry::NeighborInformationEntry (Ipv4Address neighborAddress,
													Time lastValidTime,
													uint8_t lastTimeToLive)
	:m_neighborAddress(neighborAddress),
	 m_lastValidTime(lastValidTime),
	 m_lastTimeToLive(lastTimeToLive)
{
	m_index = 0;
	m_tqAvg = 0;
		for (uint8_t i = 0; i<10; ++i)
		{
			m_recvTq[i] = 0;
		}

		for (uint32_t j = 0; j<(8);j++)
		{
			real_bits[j] = 0;
		}

		realPacketCount = 0;

		for (uint32_t k = 0; k<(8);k++)
		{
			bcast_own[k] = 0;
		}

		broadcastOwn = 0;
}

NeighborInformationEntry::~NeighborInformationEntry()
{
}
OriginatorListEntry::OriginatorListEntry (Ipv4Address originatorAddress,
									  Ptr<NetDevice> dev,
									  Ipv4InterfaceAddress iface,
									  Time lastAwareTime,
									  uint8_t lastTTL,
									  uint16_t currentSeqNumber)

	: m_iface (iface),
	  m_lastAwareTime (lastAwareTime),
	  m_lastTimeToLive (lastTTL),
	  m_currentSeqNumber (currentSeqNumber)
{
  m_ipv4Route = Create<Ipv4Route> ();
  m_ipv4Route->SetDestination (originatorAddress);
  m_ipv4Route->SetOutputDevice (dev);
  m_ipv4Route->SetSource (m_iface.GetLocal ());
  m_ipv4Route->SetGateway("0.0.0.0");
  m_newestTqValue = 0;
}

uint8_t
OriginatorListEntry::CountRealPackets(BatmanHeader batmanPacket, Ipv4Address sender)
{
	uint8_t isDuplicate = 0;
	uint16_t old = 0;

	for (std::map<Ipv4Address, NeighborInformationEntry>::iterator i = m_neighborInformation.begin (); i != m_neighborInformation.end (); ++i )
	{
		if ( !isDuplicate )
		{
			isDuplicate = get_bit_status(i->second.real_bits, GetCurrentSeqNumber(), batmanPacket.GetSequenceNumber());
		}

		if (i->first == sender)
		{
			bit_get_packet( i->second.real_bits, batmanPacket.GetSequenceNumber() - GetCurrentSeqNumber(), 1 );
		}
		else
		{
			bit_get_packet( i->second.real_bits, batmanPacket.GetSequenceNumber() - GetCurrentSeqNumber(), 0 );
		}

		i->second.realPacketCount = bit_packet_count( i->second.real_bits );
	}

	if ( !isDuplicate )
	{
		old = GetCurrentSeqNumber();
		SetCurrentSeqNumber(batmanPacket.GetSequenceNumber());
		NS_LOG_DEBUG("Update CurrentSequenceNumber - old:  " << old << " new: " << GetCurrentSeqNumber());
	}

	return isDuplicate;
}

void
OriginatorListEntry::UpdateNeighborRanking(Ipv4Address sender, BatmanHeader batmanPacket, std::map<Ipv4Address, NeighborInformationEntry> &directNeighbors, uint8_t isDuplicate)
{
	uint8_t maxRebroadcastCount = 0, maxTq = 0;
	NeighborInformationEntry neighbor, bestNeighbor;

	NeighborInformationEntry *prevBestNeighbor = NULL;
	GetNeighbor(GetNextHop(), &prevBestNeighbor);
	std::map<Ipv4Address, NeighborInformationEntry>::const_iterator k;

	for (std::map<Ipv4Address, NeighborInformationEntry>::iterator i = m_neighborInformation.begin (); i != m_neighborInformation.end (); ++i )
	{
		if(i->second.GetNeighborAddress() == sender)
		{
			ring_buffer_set(i->second.m_recvTq, &(i->second.m_index), GetNewestTqValue());
			i->second.SetTqAvg(ring_buffer_avg(i->second.m_recvTq));
			neighbor = i->second;
			NS_LOG_DEBUG("Neighbor " << sender << " updated " << (uint16_t)GetNewestTqValue() << "! Avg TQ = " << (uint16_t)neighbor.GetTqAvg());
		}
		else
		{
			if(!isDuplicate)
			{
				ring_buffer_set(i->second.m_recvTq, &(i->second.m_index), 0);
				i->second.SetTqAvg(ring_buffer_avg(i->second.m_recvTq));
			}

			k = directNeighbors.find (i->second.GetNeighborAddress());

			if ( (i->second.GetTqAvg() > maxTq) ||
							 ((GetNextHop() == i->second.GetNeighborAddress()) && ( i->second.GetTqAvg() == maxTq)) ||
						 	 ((i->second.GetTqAvg() == maxTq) && (k->second.broadcastOwn > maxRebroadcastCount)))
			{
				bestNeighbor = i->second;
				maxTq = i->second.GetTqAvg();
				maxRebroadcastCount = k->second.broadcastOwn;
			}
		}
	}

	k = directNeighbors.find(sender);

	if ( (neighbor.GetTqAvg() > maxTq) ||
		 ((GetNextHop() == neighbor.GetNeighborAddress()) && (neighbor.GetTqAvg() == maxTq)) ||
		 ((neighbor.GetTqAvg() == maxTq) && (k->second.broadcastOwn > maxRebroadcastCount)))
	{
		SetNextHop(neighbor.GetNeighborAddress());
//		NS_LOG_DEBUG("New best neighbor selected: " << neighbor.GetNeighborAddress() << " to originator: " << m_ipv4Route->GetDestination());
	}
	else
	{
		SetNextHop(bestNeighbor.GetNeighborAddress());
//		NS_LOG_DEBUG("New best neighbor selected: " << prevBestNeighbor.GetNeighborAddress() << " to originator: " << m_ipv4Route->GetDestination());
	}

	/* New best neighbor has been chosen */
	if ( (prevBestNeighbor != NULL) && (prevBestNeighbor->GetNeighborAddress() != GetNextHop()) )
	{
		NS_LOG_DEBUG(" -- Best next hop to " << batmanPacket.GetOriginatorAddress() << " changed from " << prevBestNeighbor->GetNeighborAddress()
				<< " (" << (uint16_t)prevBestNeighbor->GetTqAvg() << ")"
				<< " to " << GetNextHop() << " (" << (uint16_t)bestNeighbor.GetTqAvg() << ")");
	}

}

bool
OriginatorListEntry::AddNeighbor(NeighborInformationEntry newNeighbor)
{
	  std::pair<std::map<Ipv4Address, NeighborInformationEntry>::iterator, bool> result = m_neighborInformation.insert (std::make_pair (newNeighbor.GetNeighborAddress(),newNeighbor));
	  if (result.second)
	  {
		  NS_LOG_DEBUG("Added neighbor " << result.first->second.GetNeighborAddress() << " to " << m_ipv4Route->GetDestination() );
	  }
	  return result.second;
}

bool
OriginatorListEntry::GetNeighbor2(Ipv4Address sender, Time currentTime, BatmanHeader batmanPacket, NeighborInformationEntry **neighborEntry)
{
	if ( !(m_neighborInformation.empty()) )
	{
		std::map<Ipv4Address, NeighborInformationEntry>::iterator i = m_neighborInformation.find (sender);

		if( i != m_neighborInformation.end() )
		{
			/* Found the neighbor in this originators neighbor list, update and return pointer to object */
			i->second.SetLastValidTime(currentTime);
			*neighborEntry = &(i->second);
		}
		else
		{
			NS_LOG_DEBUG("Neighbor does not exist in neighbor list, add new neighbor");
			NeighborInformationEntry newNeighbor (
				/*neighbor address=*/ sender,
				/*lastValidTime=*/ Simulator::Now(),
				/*lastTTL=*/ batmanPacket.GetTimeToLive() );

			std::pair<std::map<Ipv4Address, NeighborInformationEntry>::iterator, bool> result = m_neighborInformation.insert (std::make_pair (sender, newNeighbor));

			if (result.second)
			{
				std::map<Ipv4Address, NeighborInformationEntry>::iterator i = m_neighborInformation.find (sender);
				*neighborEntry = &(i->second);
			}
			else
			{
				return false;
			}
		}
	}
	else
	{
		NS_LOG_DEBUG("Neighbor List is empty, add new neighbor");
		NeighborInformationEntry newNeighbor (
			/*neighbor address=*/ sender,
			/*lastValidTime=*/ Simulator::Now(),
			/*lastTTL=*/ batmanPacket.GetTimeToLive() );

		std::pair<std::map<Ipv4Address, NeighborInformationEntry>::iterator, bool> result = m_neighborInformation.insert (std::make_pair (sender, newNeighbor));

		if (result.second)
		{
			std::map<Ipv4Address, NeighborInformationEntry>::iterator i = m_neighborInformation.find (sender);
			*neighborEntry = &(i->second);
		}
		else
		{
			return false;
		}
	}
	return true;
}

bool
OriginatorListEntry::GetNeighbor(Ipv4Address sender, NeighborInformationEntry **neighborEntry)
{
		  if (m_neighborInformation.empty ())
		    {
		      return false;
		    }
		  std::map<Ipv4Address, NeighborInformationEntry>::iterator i = m_neighborInformation.find (sender);
		  if (i == m_neighborInformation.end ())
		    {
		      return false;
		    }
		  *neighborEntry = &(i->second);
		  return true;
}

uint8_t
OriginatorListEntry::BidirectionalCheck(Ipv4Address sender, Time currentTime, BatmanHeader batmanPacket, uint8_t rebroadcastCount, uint8_t tqRecv)
{
	uint8_t totalCount = 0, tqLocal = 0, newTq = 0, RQ = 0, asymetricPenalty = 0;
	NeighborInformationEntry *neighborEntry = NULL;
	GetNeighbor2(sender, currentTime, batmanPacket, &neighborEntry);

	RQ = neighborEntry->realPacketCount;

	/* pay attention to not get a value bigger than 100 % */
	if ( rebroadcastCount > RQ )
	{
		totalCount = RQ;
	}
	else
	{
		totalCount = rebroadcastCount;
	}

	/* if we have too few packets (too less data) we set tq_own to zero */
	/* if we receive too few packets it is not considered bidirectional */
	if (totalCount < TQ_LOCAL_BIDRECT_SEND_MINIMUM || RQ < TQ_LOCAL_BIDRECT_RECV_MINIMUM )
	{
//				NS_LOG_DEBUG("totalcount "<< (uint16_t)i->second.GetReceivedPacketCount());
		tqLocal = 0;
	}
	else
	{
		if(RQ == 0)
		{
			tqLocal = 0;
		}
		else
		{
			tqLocal = (MAX_TQ_VALUE * totalCount) / RQ;
		}
//				NS_LOG_DEBUG("TQlocal: (255 * " << (uint16_t)totalCount << ") / " << (uint16_t)i->second.GetReceivedPacketCount() << " = " << (uint16_t)tqLocal);
	}

	/* Add asymmetric penalty */
	asymetricPenalty = MAX_TQ_VALUE - (MAX_TQ_VALUE*(LOCAL_WINDOW_SIZE - RQ)*(LOCAL_WINDOW_SIZE - RQ)*(LOCAL_WINDOW_SIZE - RQ)
			/(LOCAL_WINDOW_SIZE*LOCAL_WINDOW_SIZE*LOCAL_WINDOW_SIZE));

	newTq = (tqRecv * tqLocal * asymetricPenalty) / (MAX_TQ_VALUE*MAX_TQ_VALUE) ;

	NS_LOG_DEBUG("New TQ: (" << (uint16_t)tqRecv << " * (255 * ("<< (uint16_t)totalCount << "/" << (uint16_t)RQ << ")) * " << (uint16_t)asymetricPenalty <<
			" / 255 * 255 = " << (uint16_t)newTq);
//			NS_LOG_DEBUG("New TQ: (" << (uint16_t)tqRecv << " * "<< (uint16_t)tqLocal << " * " << (uint16_t)asymetricPenalty <<
//					" / 255 * 255 = " << (uint16_t)newTq);

	if ( newTq >= TQ_TOTAL_BIDRECT_LIMIT )
	{
		SetNewestTqValue(newTq);
		return 1;
	}

	NS_LOG_DEBUG(sender << " is NOT a bidirectional neighbor !");
	return 0;
}

void
OriginatorListEntry::PurgeNeighborInformation()
{
	Time purgeTimeout = Seconds(2*PURGE_TIMEOUT);
	uint8_t neighborsPurged = 0, maxTq = 0, prevTqAvg = 0;
	NeighborInformationEntry *bestNeighbor = NULL;

	for (std::map<Ipv4Address, NeighborInformationEntry>::iterator i = m_neighborInformation.begin (); i != m_neighborInformation.end (); ++i)
	{
		if (Simulator::Now() > (purgeTimeout + i->second.GetLastValidTime()))
		{
			NS_LOG_DEBUG("Neighbor " << i->first << " timed-out!");
			/* Is this neighbor the best next hop? */
			if (GetNextHop() == i->first)
			{
				prevTqAvg = i->second.GetTqAvg();
				NS_LOG_DEBUG("Clear this as best next hop!");
				SetNextHop("0.0.0.0");

			}
			std::map<Ipv4Address, NeighborInformationEntry>::iterator itmp = i;
			m_neighborInformation.erase(itmp);

			neighborsPurged = 1;
		}
		else
		{
			if( (bestNeighbor == NULL) && (i->second.GetTqAvg() > maxTq))
			{
				bestNeighbor = &(i->second);

				maxTq = i->second.GetTqAvg();
			}
		}
	}

	/* Set new best next best hop*/
	if ( (neighborsPurged) && ((bestNeighbor == NULL) || (GetNextHop() == "0.0.0.0") || (maxTq > prevTqAvg)))
	{
		NS_LOG_DEBUG("New best hop: " << bestNeighbor->GetNeighborAddress());
		SetNextHop(bestNeighbor->GetNeighborAddress());
	}
}

void
OriginatorListEntry::DeleteNeighborInformation()
{
	m_neighborInformation.clear();
}

OriginatorListEntry::~OriginatorListEntry ()
{
}

OriginatorList::OriginatorList ()
{
}

void
OriginatorList::BitGetPacketNeighbors()
{
	uint8_t old = 0;
	for (std::map<Ipv4Address, NeighborInformationEntry>::iterator i = m_directNeighbors.begin (); i != m_directNeighbors.end (); ++i)
	{
		old = i->second.broadcastOwn = bit_packet_count(i->second.bcast_own);
		bit_get_packet( i->second.bcast_own, 1, 0 );
		i->second.broadcastOwn = bit_packet_count(i->second.bcast_own);
//		NS_LOG_DEBUG("Schedule own packet! old = " << (uint16_t)old << " new = " << (uint16_t)i->second.broadcastOwn);
	}
}

void
OriginatorList::UpdateOriginator(Ipv4Address originator, Ipv4Address sender, BatmanHeader batmanPacket, uint8_t isDuplicate)
{
	OriginatorListEntry *originatorEntry = NULL;
	GetOriginator(originator, &originatorEntry);

	originatorEntry->UpdateNeighborRanking(sender, batmanPacket, m_directNeighbors, isDuplicate);
}

uint8_t
OriginatorList::GetRebroadcastCount(Ipv4Address sender)
{
	  if (m_directNeighbors.empty ())
	    {
	      return 0;
	    }
	  std::map<Ipv4Address, NeighborInformationEntry>::iterator i = m_directNeighbors.find (sender);
	  if (i == m_directNeighbors.end ())
	    {
	      return 0;
	    }
	  return i->second.broadcastOwn;
}

void
OriginatorList::CountRebroadcast (Ipv4Address sender)
{
	uint8_t old = 0;

	if (!(m_directNeighbors.empty()))
	{
		std::map<Ipv4Address, NeighborInformationEntry>::iterator i = m_directNeighbors.find (sender);

		if (! (i == m_directNeighbors.end()))
		{
			old = i->second.broadcastOwn;
			bit_mark(i->second.bcast_own, 0);
			i->second.broadcastOwn = bit_packet_count(i->second.bcast_own);
			NS_LOG_DEBUG("New EQ from " << sender << " - old = " << (uint16_t)old << " new = " << (uint16_t)(i->second.broadcastOwn) << "\n");
		}
		else
		{
			NS_LOG_DEBUG( sender << " not found in Neighborlist, create new neighbor.");
			NeighborInformationEntry newDirectNeighbor (
					/*neighbor address=*/ sender,
					/*lastValidTime=*/ Simulator::Now(),
					/*lastTTL=*/ 0 );
			std::pair<std::map<Ipv4Address, NeighborInformationEntry>::iterator, bool> result = m_directNeighbors.insert (std::make_pair (sender, newDirectNeighbor));
			bit_mark(result.first->second.bcast_own, 0);
			result.first->second.broadcastOwn = bit_packet_count(result.first->second.bcast_own);
			NS_LOG_DEBUG("New EQ from " << sender << " = " << (uint16_t)(result.first->second.broadcastOwn) << "\n");
		}
	}
	else
	{
		NS_LOG_DEBUG("Neighborlist empty, create new neighbor.");
		NeighborInformationEntry newDirectNeighbor (
				/*neighbor address=*/ sender,
				/*lastValidTime=*/ Simulator::Now(),
				/*lastTTL=*/ 0 );
		std::pair<std::map<Ipv4Address, NeighborInformationEntry>::iterator, bool> result = m_directNeighbors.insert (std::make_pair (sender, newDirectNeighbor));
		bit_mark(result.first->second.bcast_own, 0);
		result.first->second.broadcastOwn = bit_packet_count(result.first->second.bcast_own);
		NS_LOG_DEBUG("New EQ from " << sender << " = " << (uint16_t)(result.first->second.broadcastOwn) << "\n");
	}
}

bool
OriginatorList::GetOriginator(Ipv4Address originatorAddress, OriginatorListEntry **originatorEntry)
{
		  if (m_ipv4AddressEntry.empty ())
		    {
		      return false;
		    }
		  std::map<Ipv4Address, OriginatorListEntry>::iterator i = m_ipv4AddressEntry.find (originatorAddress);
		  if (i == m_ipv4AddressEntry.end ())
		    {
		      return false;
		    }
		  *originatorEntry = &(i->second);
		  return true;
}

bool
OriginatorList::GetOriginator2(Ipv4Address originatorAddr, Time currentTime, BatmanHeader batmanPacket, Ptr<NetDevice> dev, Ipv4InterfaceAddress interface,
		OriginatorListEntry **originatorEntry)
{
	if ( !(m_ipv4AddressEntry.empty()) )
	{
		std::map<Ipv4Address, OriginatorListEntry>::iterator i = m_ipv4AddressEntry.find (originatorAddr);

		if( i != m_ipv4AddressEntry.end() )
		{
			/* Found the originator in OL, update and return pointer to object */
			i->second.SetLastAwareTime(currentTime);
			*originatorEntry = &(i->second);
		}
		else
		{
			NS_LOG_DEBUG("Originator does not exist in OL, add new originator");
			OriginatorListEntry newOriginatorEntry (
				/*originator address=*/ batmanPacket.GetOriginatorAddress(),
				/*device=*/ dev,
				/*iface=*/ interface,
				/*lastAwareTime=*/ Simulator::Now(),
				/*lastTTL=*/ batmanPacket.GetTimeToLive(),
				/*CurrentSequenceNumber=*/ batmanPacket.GetSequenceNumber() );

			newOriginatorEntry.SetNextHop("0.0.0.0");

			std::pair<std::map<Ipv4Address, OriginatorListEntry>::iterator, bool> result = m_ipv4AddressEntry.insert (std::make_pair (originatorAddr, newOriginatorEntry));

			if (result.second)
			{
				std::map<Ipv4Address, OriginatorListEntry>::iterator i = m_ipv4AddressEntry.find (originatorAddr);
				*originatorEntry = &(i->second);
			}
		}
	}
	else
	{
		NS_LOG_DEBUG("Originator List is empty, add new originator");
		OriginatorListEntry newOriginatorEntry (
			/*originator address=*/ batmanPacket.GetOriginatorAddress(),
			/*device=*/ dev,
			/*iface=*/ interface,
			/*lastAwareTime=*/ Simulator::Now(),
			/*lastTTL=*/ batmanPacket.GetTimeToLive(),
			/*CurrentSequenceNumber=*/ batmanPacket.GetSequenceNumber() );

		newOriginatorEntry.SetNextHop("0.0.0.0");

		std::pair<std::map<Ipv4Address, OriginatorListEntry>::iterator, bool> result = m_ipv4AddressEntry.insert (std::make_pair (originatorAddr, newOriginatorEntry));

		if (result.second)
		{
			std::map<Ipv4Address, OriginatorListEntry>::iterator i = m_ipv4AddressEntry.find (originatorAddr);
			*originatorEntry = &(i->second);
		}
	}
	return true;
}

bool
OriginatorList::LookupRoute (Ipv4Address id,
                           OriginatorListEntry & rt)
{
  if (m_ipv4AddressEntry.empty ())
    {
      return false;
    }
  std::map<Ipv4Address, OriginatorListEntry>::iterator i = m_ipv4AddressEntry.find (id);
  if (i == m_ipv4AddressEntry.end ())
    {
      return false;
    }
  if(i->second.GetNextHop() == "0.0.0.0")
  {
	  return false;
  }
  rt = i->second;
  return true;
}

bool
OriginatorList::LookupRoute (Ipv4Address id,
                           OriginatorListEntry & rt,
                           bool forRouteInput)
{
	  if (m_ipv4AddressEntry.empty ())
	    {
	      return false;
	    }
	  std::map<Ipv4Address, OriginatorListEntry>::iterator i = m_ipv4AddressEntry.find (id);
	  if (i == m_ipv4AddressEntry.end ())
	    {
	      return false;
	    }
	  if (forRouteInput == true && id == i->second.GetInterface ().GetBroadcast ())
	    {
	      return false;
	    }

	  rt = i->second;
	  return true;
}

uint32_t
OriginatorList::OriginatorListSize ()
{
  return m_ipv4AddressEntry.size ();
}

bool
OriginatorList::AddOriginator (OriginatorListEntry & rt)
{
  std::pair<std::map<Ipv4Address, OriginatorListEntry>::iterator, bool> result = m_ipv4AddressEntry.insert (std::make_pair (rt.GetDestination (),rt));
  if (result.second)
  {
	  NS_LOG_DEBUG("Added originator " << result.first->second.GetDestination() << " with next hop " << result.first->second.GetNextHop() );
  }
  return result.second;
}

/*
 * agb
 * finds every OriginatorListEntry with the parameter iface and removes the entire entry
 */
void
OriginatorList::DeleteAllRoutesFromInterface (Ipv4InterfaceAddress iface)
{
	  if (m_ipv4AddressEntry.empty ())
	    {
	      return;
	    }
	  for (std::map<Ipv4Address, OriginatorListEntry>::iterator i = m_ipv4AddressEntry.begin (); i != m_ipv4AddressEntry.end (); )
	    {
	      if (i->second.GetInterface () == iface)
	        {
	          std::map<Ipv4Address, OriginatorListEntry>::iterator tmp = i;
	          ++i;
	          m_ipv4AddressEntry.erase (tmp);
	        }
	      else
	        {
	          ++i;
	        }
	    }
}

void
OriginatorList::GetListOfAllRoutes (std::map<Ipv4Address, OriginatorListEntry> & allRoutes)
{
  for (std::map<Ipv4Address, OriginatorListEntry>::iterator i = m_ipv4AddressEntry.begin (); i != m_ipv4AddressEntry.end (); ++i)
    {
      if (i->second.GetDestination () != Ipv4Address ("127.0.0.1"))
        {
          allRoutes.insert (std::make_pair (i->first,i->second));
        }
    }
}

void
OriginatorList::Purge (std::map<Ipv4Address, OriginatorListEntry> & removedAddresses, Time currentTime)
{
//	if (m_ipv4AddressEntry.empty ())
//	    {
//	      return;
//	    }
//	Time purgeTimeout = Seconds(2*PURGE_TIMEOUT);
//	  for (std::map<Ipv4Address, OriginatorListEntry>::iterator i = m_ipv4AddressEntry.begin (); i != m_ipv4AddressEntry.end (); ++i)
//	  {
//		  if (currentTime > (purgeTimeout + i->second.GetLastAwareTime()))
//		  {
//			  NS_LOG_DEBUG("Originator " << i->first << " timed-out!");
//			  i->second.DeleteNeighborInformation();
//			  NS_LOG_DEBUG("Remove all neighbors");
//			  std::map<Ipv4Address, OriginatorListEntry>::iterator itmp = i;
//			  removedAddresses.insert(std::make_pair(i->first, i->second));
//			  m_ipv4AddressEntry.erase(itmp);
//		  }
//		  /* Check if the Originators Neighbors has timed out */
//		  else
//		  {
//			  i->second.PurgeNeighborInformation();
//		  }
//	  }
	  return;
}

void
OriginatorList::Print(Ipv4Address me)
{
	NeighborInformationEntry *n = NULL;
	NS_LOG_DEBUG(me << "s OriginatorList:");
	for (std::map<Ipv4Address, OriginatorListEntry>::iterator i = m_ipv4AddressEntry.begin (); i != m_ipv4AddressEntry.end (); ++i)
	{
		i->second.GetNeighbor(i->second.GetNextHop(), &n);
		if (n != NULL && i->second.GetDestination()!= "10.0.0.255")
		{
			NS_LOG_DEBUG("Org: " << i->second.GetDestination() << " Next Hop (" << i->second.GetNumberOfNeighbors() << "): " << i->second.GetNextHop() << " AvgTQ: " << (uint16_t)n->GetTqAvg());
		}
	}
}

}
}
