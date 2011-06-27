/*
 *
 * BATMAN Header Format
 *
 * Author     : Anne Gabrielle Bowitz
 * Email      : bowitz@stud.ntnu.no
 * Project    : Simulation of a Secure Ad Hoc Network Routing protocol
 * Institution: NTNU (Norwegian University of Science & Technology), ITEM (Institute of Telematics)
 *
 */
#include "batman-packet.h"
#include "ns3/address-utils.h"
#include "ns3/packet.h"

namespace ns3 {
namespace batman {
NS_OBJECT_ENSURE_REGISTERED (BatmanHeader);

/*
 * constructor initializing fields in packet
 */
//BatmanHeader::BatmanHeader (Ipv4Address dst, uint32_t hopCount, uint32_t dstSeqNo)
BatmanHeader::BatmanHeader (uint8_t version, UDFlags udFlags, uint8_t timeToLive, uint8_t gwFlags, uint16_t sequenceNumber, uint16_t gwPort,
							Ipv4Address originatorAddress, Ipv4Address prevSender, uint8_t tqValue, uint8_t hnaLength, uint16_t authValue)
  : m_version (version),
    m_UDFlags (udFlags),
    m_timeToLive (timeToLive),
    m_GWFlags (gwFlags),
    m_sequenceNumber (sequenceNumber),
    m_GWPort (gwPort),
    m_originatorAddress (originatorAddress),
    m_prevSender (prevSender),
    m_tqValue (tqValue),
    m_hnaLength (hnaLength),
    m_authValue (authValue)
{
}

BatmanHeader::~BatmanHeader ()
{
}

/*
 * Need to give a TypeId to BatmanHeader class
 */
TypeId
BatmanHeader::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::batman::BatmanHeader")
    .SetParent<Header> ()
    .AddConstructor<BatmanHeader> ();
  return tid;
}

TypeId
BatmanHeader::GetInstanceTypeId () const
{
  return GetTypeId ();
}

/*
 * Return total packet size, 20 Bytes
 */
uint32_t
BatmanHeader::GetSerializedSize () const
{
  return 20;
}

/*
 * Need to serialize and deserialize the header/packet to a byte buffer in its network representation
 */
void
BatmanHeader::Serialize (Buffer::Iterator i) const
{
	i.WriteU8 ( m_version );
	i.WriteU8 ( m_UDFlags );
	i.WriteU8 ( m_timeToLive);
	i.WriteU8 ( m_GWFlags );
	i.WriteHtonU16 ( m_sequenceNumber );
	i.WriteHtonU16 ( m_GWPort );
	WriteTo(i, m_originatorAddress);
	WriteTo(i, m_prevSender);
	i.WriteU8( m_tqValue );
	i.WriteU8( m_hnaLength );
	i.WriteHtonU16( m_authValue );
}
uint32_t
BatmanHeader::Deserialize (Buffer::Iterator start)
{
	Buffer::Iterator i = start;
	m_version = i.ReadU8 ();
	m_UDFlags = (UDFlags) i.ReadU8 ();
	m_timeToLive = i.ReadU8 ();
	m_GWFlags = i.ReadU8 ();
	m_sequenceNumber = i.ReadNtohU16 ();
	m_GWPort = i.ReadNtohU16 ();
	ReadFrom(i, m_originatorAddress);
	ReadFrom(i, m_prevSender);
	m_tqValue = i.ReadU8 ();
	m_hnaLength = i.ReadU8 ();
	m_authValue = i.ReadNtohU16 ();

  uint32_t dist = i.GetDistanceFrom (start);
  NS_ASSERT (dist == GetSerializedSize ());
  return dist;
}

/*
 * Prints the content of the header
 */
void
BatmanHeader::Print (std::ostream &os) const
{
	os << "Version: " << m_version
       << " UDFlags: " << m_UDFlags
       << " TTL: " << m_timeToLive
       << " GatewayFlags: " << m_GWFlags
       << " Sequence Number: " << m_sequenceNumber
       << " GatewayPort: " << m_GWPort
	   << " Originator Address: " << m_originatorAddress
	   << " Previous Sender: " << m_prevSender
	   << " TQ value: " << m_tqValue
	   << " HNA Length: " << m_hnaLength
	   << " AUTH Value: " << m_authValue;
}
}
}
