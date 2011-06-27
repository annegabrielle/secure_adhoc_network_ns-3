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
#ifndef __BATMAN_RTABLE_H__
#define __BATMAN_RTABLE_H__

#include <cassert>
#include <map>
#include <sys/types.h>
#include "ns3/ipv4.h"
#include "ns3/ipv4-route.h"
#include "ns3/timer.h"
#include "ns3/net-device.h"
#include "ns3/output-stream-wrapper.h"
#include "batman-packet.h"


#define WINDOW_SIZE						8
#define GLOBAL_WINDOW_SIZE				10
#define MAX_SEQUENCE_NUMBER				65535
#define TYPE_OF_WORD uintmax_t /* you should choose something big, if you don't want to waste cpu */

namespace ns3 {
namespace batman {

/*
 * Neighbor Information List Entry
 */
class NeighborInformationEntry
{
public:
  // / c-tor
	NeighborInformationEntry (Ipv4Address neighborAddress = Ipv4Address (), Time lastValidTime = Simulator::Now(),
			uint8_t lastTimeToLive = 0);
  ~NeighborInformationEntry ();

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

  /* Sliding window for total amount of received OGMs from this neighbor RQ */
  TYPE_OF_WORD real_bits[8];
  uint8_t realPacketCount;

  /* Sliding window for total amount of recevied rebroadcasts of self generated OGMs from this neighbor EQ */
  TYPE_OF_WORD bcast_own[8];
  uint8_t broadcastOwn;

  uint8_t m_recvTq[10];
  uint8_t m_index;

private:

  uint8_t m_tqAvg;

  Ipv4Address m_neighborAddress;

  /*
   * Timestamp when the last valid OGM was received via this neighbor
   */
  Time m_lastValidTime;

  /*
   * TTL of the last received OGM which was received via this neighbor
   */
  uint8_t m_lastTimeToLive;

};

/*
 * Originator List Entry
 */
class OriginatorListEntry
{
public:
  OriginatorListEntry (Ipv4Address originatorAddress = Ipv4Address (), Ptr<NetDevice> dev = 0, Ipv4InterfaceAddress iface = Ipv4InterfaceAddress (), Time lastAwareTime = Simulator::Now(),
		  	  	  	  uint8_t lastTTL = 0, uint16_t currentSeqNumber = 0);
  ~OriginatorListEntry ();

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
	  return m_neighborInformationList.size();
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
  GetNeighbor2(Ipv4Address sender, Time currentTime, BatmanHeader batmanPacket, NeighborInformationEntry **neighborEntry);

  uint8_t
  BidirectionalCheck(Ipv4Address sender, Time currentTime, BatmanHeader batmanPacket, uint8_t rebroadcastCount, uint8_t tqRecv);

  void
  UpdateNeighborRanking(Ipv4Address sender, BatmanHeader batmanPacket, std::map<Ipv4Address, NeighborInformationEntry> &directNeighbors, uint8_t isDuplicate);

  bool
  DuplicatePacketCheck(Ipv4Address sender, BatmanHeader batmanPacket);

  uint8_t
  DuplicatePacketCheck(BatmanHeader batmanPacket, Ipv4Address sender);

  void
  DeleteNeighborInformation();

  void
  PurgeNeighborInformation();

  /*
   * Compare destination address
   * return true if equal
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

  Ipv4InterfaceAddress m_iface;

  /*
   * Timestamp updated when an OGM is received from this Originator
   */
  Time m_lastAwareTime;

  uint8_t m_lastTimeToLive;

  /*
   * Newest OGM sequence number accepted from Originator
   */
  uint16_t m_currentSeqNumber;

  uint8_t m_newestTqValue;

  /*
   * For each direct link to each neighbor of the node this information must be maintained.
   */
  std::map<Ipv4Address, NeighborInformationEntry> m_neighborInformationList;

};

/*
 * The Originator List used by BATMAN protocol
 */
class OriginatorList
{
public:
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
  CountReceivedPackets(Ipv4Address sender, BatmanHeader batmanHeader, Ptr<NetDevice> dev, Ipv4InterfaceAddress interface);

  bool
  GetOriginator(Ipv4Address originatorAddress, OriginatorListEntry **originatorEntry);

  bool
  GetOriginator2(Ipv4Address originatorAddr, Time currentTime, BatmanHeader batmanPacket, Ptr<NetDevice> dev, Ipv4InterfaceAddress interface, OriginatorListEntry **originatorEntry);

  uint8_t
  GetRebroadcastCount(Ipv4Address sender);

  void
  UpdateOriginator(Ipv4Address originator, Ipv4Address sender, BatmanHeader batmanPacket, uint8_t isDuplicate);

  void
  BitGetPacketNeighbors();

private:
  /* Map containing all entries in Originator List */
  std::map<Ipv4Address, OriginatorListEntry> m_ipv4AddressEntry;
  /* Map containing all entries in Neighbor Information List */
  std::map<Ipv4Address, NeighborInformationEntry> m_directNeighbors;
};
}
}
#endif /*__BATMAN_RTABLE_H__ */
