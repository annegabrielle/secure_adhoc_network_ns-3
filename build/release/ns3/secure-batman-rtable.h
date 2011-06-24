/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2010 Hemanth Narra
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
 * Author: Hemanth Narra <hemanth@ittc.ku.com>
 *
 * James P.G. Sterbenz <jpgs@ittc.ku.edu>, director
 * ResiliNets Research Group  http://wiki.ittc.ku.edu/resilinets
 * Information and Telecommunication Technology Center (ITTC)
 * and Department of Electrical Engineering and Computer Science
 * The University of Kansas Lawrence, KS USA.
 *
 * Work supported in part by NSF FIND (Future Internet Design) Program
 * under grant CNS-0626918 (Postmodern Internet Architecture),
 * NSF grant CNS-1050226 (Multilayer Network Resilience Analysis and Experimentation on GENI),
 * US Department of Defense (DoD), and ITTC at The University of Kansas.
 */
#ifndef __SECURE_BATMAN_RTABLE_H__
#define __SECURE_BATMAN_RTABLE_H__

#include <cassert>
#include <map>
#include <sys/types.h>
#include "ns3/ipv4.h"
#include "ns3/ipv4-route.h"
#include "ns3/timer.h"
#include "ns3/net-device.h"
#include "ns3/output-stream-wrapper.h"
#include "secure-batman-packet.h"


#define WINDOW_SIZE						8
#define GLOBAL_WINDOW_SIZE				10
#define MAX_SEQUENCE_NUMBER				65535
#define TYPE_OF_WORD uintmax_t /* you should choose something big, if you don't want to waste cpu */

namespace ns3 {
namespace securebatman {

/*
 * agb
 *
 * BATMAN OriginatorList
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 | OriginatorAddress | OriginatorListEntry |
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * BATMAN OriginatorListEntry
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 | OriginatorAddress | NetDevicePtr | InterfaceAdr | LastAwareTime | BiDirectSeqNumber | CurrentSeqNumber | NeighborInformationEntries<Neighbor,NeighborInformationEntry> |
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * excluded fields: | HNAList* | GWCapability* |
 *
 * NeighborInformationEntry
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 | Neighbor | SlidingWindow  | PacketCount | LastValidTime | LastTTL |
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 *
 *
 */


class NeighborInformationEntry
{
public:
  // / c-tor
	NeighborInformationEntry (Ipv4Address neighborAddress = Ipv4Address (), Time lastValidTime = Simulator::Now(),
			uint8_t lastTimeToLive = 0);
  ~NeighborInformationEntry ();

  /*
   * agb
   * Get/set methods
   */
  void
  SetNeighborAddress (Ipv4Address neighborAddress)
  {
	  m_neighborAddress = neighborAddress;
  }
  Ipv4Address
  GetNeighborAddress () const
  {
	  return m_neighborAddress;
  }
  void
  SetLastValidTime (Time lastValidTime)
  {
	  m_lastValidTime = lastValidTime;
  }
  Time
  GetLastValidTime () const
  {
	  return m_lastValidTime;
  }
  void
  SetLastTimeToLive (uint8_t lastTimeToLive)
  {
	  m_lastTimeToLive = lastTimeToLive;
  }
  uint8_t
  GetLastTimeToLive () const
  {
	  return m_lastTimeToLive;
  }
  void
  SetTqAvg (uint8_t tqAvg)
  {
	   m_tqAvg = tqAvg;
  }
  uint8_t
  GetTqAvg () const
  {
	  return m_tqAvg;
  }

  TYPE_OF_WORD real_bits[8];
  uint8_t realPacketCount;

  TYPE_OF_WORD bcast_own[8];
  uint8_t broadcastOwn;

  uint8_t m_recvTq[10];
  uint8_t m_index;

private:

  uint8_t m_tqAvg;
  /*
   * agb
   * Neighbor address
   */
  Ipv4Address m_neighborAddress;

  /*
   * agb
   * timestamp when the last valid OGM was received via this neighbor
   */
  Time m_lastValidTime;

  /*
   * agb
   * TTL of the last received OGM which was received via this neighbor
   */
  uint8_t m_lastTimeToLive;

};

/**
 * \ingroup dsdv
 * \brief Originator List Entry
 */
class OriginatorListEntry
{
public:
  // / c-tor
  OriginatorListEntry (Ipv4Address originatorAddress = Ipv4Address (), Ptr<NetDevice> dev = 0, Ipv4InterfaceAddress iface = Ipv4InterfaceAddress (), Time lastAwareTime = Simulator::Now(),
		  	  	  	  uint8_t lastTTL = 0, uint16_t currentSeqNumber = 0);
  ~OriginatorListEntry ();

  /*
   * agb
   * get/set from Ipv4Route
   */
  Ipv4Address
  GetDestination () const
  {
    return m_ipv4Route->GetDestination ();
  }
  Ipv4InterfaceAddress
  GetInterface () const
  {
    return m_iface;
  }
  void
  SetInterface (Ipv4InterfaceAddress iface)
  {
    m_iface = iface;
  }
  Ptr<Ipv4Route>
  GetRoute () const
  {
    return m_ipv4Route;
  }
  void
  SetRoute (Ptr<Ipv4Route> route)
  {
    m_ipv4Route = route;
  }
  void
  SetNextHop (Ipv4Address nextHop)
  {
    m_ipv4Route->SetGateway (nextHop);
  }
  Ipv4Address
  GetNextHop () const
  {
    return m_ipv4Route->GetGateway ();
  }
  void
  SetOutputDevice (Ptr<NetDevice> device)
  {
    m_ipv4Route->SetOutputDevice (device);
  }
  Ptr<NetDevice>
  GetOutputDevice () const
  {
    return m_ipv4Route->GetOutputDevice ();
  }
  /*
   * agb
   * Get/set methods for the remaining fields in packet
   */
  void
  SetLastAwareTime (Time lastAwareTime)
  {
    m_lastAwareTime = lastAwareTime;
  }
  Time
  GetLastAwareTime () const
  {
    return (m_lastAwareTime);
  }
  void
  SetLastTTL (uint8_t lastTTL)
  {
    m_lastTimeToLive = lastTTL;
  }
  uint8_t
  GetLastTTL ()
  {
    return m_lastTimeToLive;
  }
  void
  SetCurrentSeqNumber (uint16_t currentSequenceNumber)
  {
    m_currentSeqNumber = currentSequenceNumber;
  }
  uint16_t
  GetCurrentSeqNumber () const
  {
    return m_currentSeqNumber;
  }

  uint16_t
  GetNumberOfNeighbors ()
  {
	  return m_neighborInformation.size();
  }

  void
  SetNewestTqValue (uint8_t v)
  {
	  m_newestTqValue = v;
  }

  uint8_t
  GetNewestTqValue ()
  {
	  return m_newestTqValue;
  }

  bool
  AddNeighbor(NeighborInformationEntry newNeighbor);

  bool
  GetNeighbor(Ipv4Address sender, NeighborInformationEntry **neighborEntry);

  bool
  GetNeighbor2(Ipv4Address sender, Time currentTime, SecureBatmanHeader batmanPacket, NeighborInformationEntry **neighborEntry);

  uint8_t
  BidirectionalCheck(Ipv4Address sender, Time currentTime, SecureBatmanHeader batmanPacket, uint8_t rebroadcastCount, uint8_t tqRecv);

  void
  UpdateNeighborRanking(Ipv4Address sender, SecureBatmanHeader batmanPacket, std::map<Ipv4Address, NeighborInformationEntry> &directNeighbors, uint8_t isDuplicate);

  bool
  DuplicatePacketCheck(Ipv4Address sender, SecureBatmanHeader batmanPacket);

  uint8_t
  CountRealPackets(SecureBatmanHeader batmanPacket, Ipv4Address sender);

  void
  DeleteNeighborInformation();

  void
  PurgeNeighborInformation();

  /**
   * \brief Compare destination address
   * \return true if equal
   */
  bool
  operator== (Ipv4Address const destination) const
  {
    return (m_ipv4Route->GetDestination () == destination);
  }

private:
  /** Ip route, include
   *   - originator address
   *   - source address
   *   - next hop address (gateway)
   *   - output device
   */
  Ptr<Ipv4Route> m_ipv4Route;

  /*
     * agb
     * Output interface address
     */
  Ipv4InterfaceAddress m_iface;

  /**
   * agb
   * timestamp updated when an OGM is received from this Originator
   */
  Time m_lastAwareTime;

  uint8_t m_lastTimeToLive;

  /**
   * agb
   * newest OGM sequence number accepted from Originator
   */
  uint16_t m_currentSeqNumber;

  uint8_t m_newestTqValue;

  /*
   * agb
   * For each direct link to each neighbor of the node this information must be maintained.
   */
  std::map<Ipv4Address, NeighborInformationEntry> m_neighborInformation;

};

/**
 * \ingroup dsdv
 * \brief The Routing table used by DSDV protocol
 */
class OriginatorList
{
public:
  // / c-tor
  OriginatorList ();
  /**
   * Add routing table entry if it doesn't yet exist in routing table
   * \param r routing table entry
   * \return true in success
   */
  bool
  AddOriginator (OriginatorListEntry & r);
  /**
   * Lookup routing table entry with destination address dst
   * \param dst destination address
   * \param rt entry with destination address dst, if exists
   * \return true on success
   */
  bool
  LookupRoute (Ipv4Address originator, OriginatorListEntry & rt);
  bool
  LookupRoute (Ipv4Address id, OriginatorListEntry & rt, bool forRouteInput);
  /**
   * Lookup list of addresses for which nxtHp is the next Hop address
   * \param nexthop's address for which we want the list of destinations
   * \param dstList is the list that will hold all these originator addresses
   */
  void
  GetListOfOriginatorsWithNextHop (Ipv4Address nxtHp, std::map<Ipv4Address, OriginatorListEntry> & orgList);
  /**
   * Lookup list of all addresses in the routing table
   * \param allRoutes is the list that will hold all these addresses present in the nodes routing table
   */
  void
  GetListOfAllRoutes (std::map<Ipv4Address, OriginatorListEntry> & allRoutes);
  // / Delete all route from interface with address iface
  void
  DeleteAllRoutesFromInterface (Ipv4InterfaceAddress iface);
  // / Delete all entries from routing table
  void
  Clear ()
  {
    m_ipv4AddressEntry.clear ();
  }
  // / Delete all outdated entries
  void
  Purge (std::map<Ipv4Address, OriginatorListEntry> & removedAddresses, Time currentTime);

  void
  Print(Ipv4Address me);

  // / Provides the number of routes present in that nodes routing table.
  uint32_t
  OriginatorListSize ();

  void
  CountRebroadcast(Ipv4Address sender);

  void
  CountReceivedPackets(Ipv4Address sender, SecureBatmanHeader batmanHeader, Ptr<NetDevice> dev, Ipv4InterfaceAddress interface);

  bool
  GetOriginator(Ipv4Address originatorAddress, OriginatorListEntry **originatorEntry);

  bool
  GetOriginator2(Ipv4Address originatorAddr, Time currentTime, SecureBatmanHeader batmanPacket, Ptr<NetDevice> dev, Ipv4InterfaceAddress interface, OriginatorListEntry **originatorEntry);

  uint8_t
  GetRebroadcastCount(Ipv4Address sender);

  void
  UpdateOriginator(Ipv4Address originator, Ipv4Address sender, SecureBatmanHeader batmanPacket, uint8_t isDuplicate);

  void
  BitGetPacketNeighbors();

private:
  // /\name Fields
  // \{
  // / an entry in the routing table.
  std::map<Ipv4Address, OriginatorListEntry> m_ipv4AddressEntry;

  std::map<Ipv4Address, NeighborInformationEntry> m_directNeighbors;
  // \}
};
}
}
#endif /*__SECURE_BATMAN_RTABLE_H__ */
