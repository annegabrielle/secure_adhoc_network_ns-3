/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2010 Hemanth Narra, Yufei Cheng
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
 * Author: Yufei Cheng   <yfcheng@ittc.ku.edu>
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
#ifndef BATMANROUTINGPROTOCOL_H_
#define BATMANROUTINGPROTOCOL_H_

#include "batman-rtable.h"
#include "batman-packet.h"
#include "ns3/node.h"
#include "ns3/ipv4-routing-protocol.h"
#include "ns3/ipv4-interface.h"
#include "ns3/ipv4-l3-protocol.h"
#include "ns3/output-stream-wrapper.h"
#include <stdint.h>
#include "bitarray.h"

#define OGM_BROADCAST_INTERVAL	1
#define MAX_SEQUENCE_NUMBER		65535
#define DEFAULT_TTL				50
#define DEFAULT_VERSION			4
#define WINDOW_SIZE				8
#define MAX_TQ_VALUE			255
#define LOCAL_WINDOW_SIZE		64
#define HOP_PENALTY				5
#define TQ_LOCAL_WINDOW_SIZE	64
#define TYPE_OF_WORD uintmax_t /* you should choose something big, if you don't want to waste cpu */

namespace ns3 {
namespace batman {

/**
 * \ingroup dsdv
 * \brief DSDV routing protocol.
 */
class RoutingProtocol : public Ipv4RoutingProtocol
{
public:
  static TypeId
  GetTypeId (void);
  static const uint32_t BATMAN_PORT;

  // / c-tor
  RoutingProtocol ();
  virtual
  ~RoutingProtocol ();
  virtual void
  DoDispose ();

  // /\name From Ipv4RoutingProtocol
  // \{
  Ptr<Ipv4Route> RouteOutput (Ptr<Packet> p, const Ipv4Header &header, Ptr<NetDevice> oif, Socket::SocketErrno &sockerr);
  bool RouteInput (Ptr<const Packet> p, const Ipv4Header &header, Ptr<const NetDevice> idev, UnicastForwardCallback ucb,
                   MulticastForwardCallback mcb, LocalDeliverCallback lcb, ErrorCallback ecb);
  virtual void PrintRoutingTable (Ptr<OutputStreamWrapper> stream) const;
  virtual void NotifyInterfaceUp (uint32_t interface);
  virtual void NotifyInterfaceDown (uint32_t interface);
  virtual void NotifyAddAddress (uint32_t interface, Ipv4InterfaceAddress address);
  virtual void NotifyRemoveAddress (uint32_t interface, Ipv4InterfaceAddress address);
  virtual void SetIpv4 (Ptr<Ipv4> ipv4);
  // \}

private:
  // /\name Protocol parameters.
  // \{
  // /Nodes IP address
  Ipv4Address m_mainAddress;
  // / IP protocol
  Ptr<Ipv4> m_ipv4;
  // / Raw socket per each IP interface, map socket -> iface address (IP + mask)
  std::map<Ptr<Socket>, Ipv4InterfaceAddress> m_socketAddresses;
  // / Originator List for the node
  OriginatorList m_originatorList;
  // / Unicast callback for own packets
  UnicastForwardCallback m_scb;
  // / Error callback for own packets
  ErrorCallback m_ecb;
  // /\}

  // Periodic time interval between which the node broadcasts OGMs.
  Time m_originatorInterval;

  // The nodes BATMAN version
  uint8_t m_version;

  // The nodes sequence numbers used for broadcasting OGMs
  uint16_t m_lastSeqNoUsed;

//  TracedCallback <const Packet &> m_rxPacketTrace;
//  TracedCallback <const Packet &> m_txPacketTrace;

private:
  // / Start protocol operation
  void
  Start ();
  // / Find socket with local interface address iface
  Ptr<Socket>
  FindSocketWithInterfaceAddress (Ipv4InterfaceAddress iface) const;
  // /\name Receive dsdv control packets
  // \{
  // / Receive and process batman control packet
  void
  RecvOriginatorMessage (Ptr<Socket> socket);
  // \}
  void
  Send (Ptr<Ipv4Route>, Ptr<const Packet>, const Ipv4Header &);
  void
  BroadcastOriginatorMessage ();
  void
  ReBroadcastOriginatorMessage (BatmanHeader b, Ipv4Address s, Ipv4InterfaceAddress iface, uint64_t uid);
  // / Notify that packet is dropped for some reason
  void
  Drop (Ptr<const Packet>, const Ipv4Header &, Socket::SocketErrno);
  // / Timer to trigger periodic updates from a node
  Timer m_originatorIntervalTimer;
};

}
}
#endif /* BATMANROUTINGPROTOCOL_H_ */
