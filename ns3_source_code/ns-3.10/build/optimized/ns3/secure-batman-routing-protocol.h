/*
 *
 * Secure BATMAN Routing Protocol
 *
 * Author     : Anne Gabrielle Bowitz
 * Email      : bowitz@stud.ntnu.no
 * Project    : Simulation of a Secure Ad Hoc Network Routing protocol
 * Institution: NTNU (Norwegian University of Science & Technology), ITEM (Institute of Telematics)
 *
 */
#ifndef SECURE_BATMANROUTINGPROTOCOL_H_
#define SECURE_BATMANROUTINGPROTOCOL_H_

#include "secure-batman-rtable.h"
#include "secure-batman-packet.h"
#include "ns3/node.h"
#include "ns3/ipv4-routing-protocol.h"
#include "ns3/ipv4-interface.h"
#include "ns3/ipv4-l3-protocol.h"
#include "ns3/output-stream-wrapper.h"
#include <stdint.h>
#include "secure-bitarray.h"
#include "am.h"

#define OGM_BROADCAST_INTERVAL	1
#define AM_PACKET_INTERVAL		60
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
namespace securebatman {

/*
 * brief SECURE BATMAN Routing Protocol.
 */
class RoutingProtocol : public Ipv4RoutingProtocol
{
public:
  static TypeId
  GetTypeId (void);
  static const uint32_t BATMAN_PORT;

  RoutingProtocol ();
  virtual
  ~RoutingProtocol ();
  virtual void
  DoDispose ();

  Ptr<Ipv4Route> RouteOutput (Ptr<Packet> p, const Ipv4Header &header, Ptr<NetDevice> oif, Socket::SocketErrno &sockerr);
  bool RouteInput (Ptr<const Packet> p, const Ipv4Header &header, Ptr<const NetDevice> idev, UnicastForwardCallback ucb,
                   MulticastForwardCallback mcb, LocalDeliverCallback lcb, ErrorCallback ecb);
  virtual void PrintRoutingTable (Ptr<OutputStreamWrapper> stream) const;
  virtual void NotifyInterfaceUp (uint32_t interface);
  virtual void NotifyInterfaceDown (uint32_t interface);
  virtual void NotifyAddAddress (uint32_t interface, Ipv4InterfaceAddress address);
  virtual void NotifyRemoveAddress (uint32_t interface, Ipv4InterfaceAddress address);
  virtual void SetIpv4 (Ptr<Ipv4> ipv4);

  enum STATE {
	  UNAUTH	= 0,
	  SP		= 1,
	  AUTH		= 2,
  };

  void
  SetState(uint8_t state)
  {
  	m_state = state;
  }
  uint8_t
  GetState ()
  {
  	return m_state;
  }
  void
  SetPC(uint64_t pc)
  {
  	m_pc = pc;
  }
  uint64_t
  GetPC ()
  {
  	return m_pc;
  }

private:
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
  Time m_amPacketInterval;

  // The nodes BATMAN version
  uint8_t m_version;

  // The nodes sequence numbers used for broadcasting OGMs
  uint16_t m_lastSeqNoUsed;

  EVP_CIPHER_CTX m_aes_master;
  unsigned char *m_auth_value;
  int m_auth_value_len;
  uint16_t m_auth_seq_num;
  int m_key_count;
  unsigned char *m_current_key, *m_current_iv, *m_current_nonce;
  int m_value_len;
  uint8_t m_state;
  uint64_t m_pc;

  TracedCallback<Ptr<const Packet> > m_txBatmanTrace;
  TracedCallback<Ptr<const Packet> > m_rxBatmanTrace;

private:
  // / Start protocol operation
  void
  Start ();
  // / Find socket with local interface address iface
  Ptr<Socket>
  FindSocketWithInterfaceAddress (Ipv4InterfaceAddress iface) const;
  // / Receive and process batman control packet
  void
  RecvOriginatorMessage (Ptr<Socket> socket);
  // \}
  void
  Send (Ptr<Ipv4Route>, Ptr<const Packet>, const Ipv4Header &);
  void
  BroadcastOriginatorMessage ();
  void
  ReBroadcastOriginatorMessage (SecureBatmanHeader b, Ipv4Address s, Ipv4InterfaceAddress iface, uint64_t uid);
  // / Notify that packet is dropped for some reason
  void
  Drop (Ptr<const Packet>, const Ipv4Header &, Socket::SocketErrno);
  // / Timer to trigger periodic updates from a node
  Timer m_originatorIntervalTimer;
  Timer m_amPacketIntervalTimer;

  void
  GenerateKeyStream();

  void
  GenerateKeystreamMaterial();
};

}
}
#endif /* SECURE_BATMANROUTINGPROTOCOL_H_ */
