/*
 *
 * Secure BATMAN Header class
 *
 * Author     : Anne Gabrielle Bowitz
 * Email      : bowitz@stud.ntnu.no
 * Project    : Simulation of a Secure Ad Hoc Network Routing protocol
 * Institution: NTNU (Norwegian University of Science & Technology), ITEM (Institute of Telematics)
 *
 */
#include "secure-batman-packet.h"
#include "ns3/address-utils.h"
#include "ns3/packet.h"
#include "ns3/log.h"

NS_LOG_COMPONENT_DEFINE ("SecureBatmanHeader");

namespace ns3 {
namespace securebatman {
NS_OBJECT_ENSURE_REGISTERED (SecureBatmanHeader);

SecureAmHeader::SecureAmHeader (unsigned char *key,
								unsigned char *iv,
								unsigned char *nonce )
{
}

SecureAmHeader::~SecureAmHeader ()
{
}

/*
 * Need to give a TypeId to SecureBatmanHeader class
 */
TypeId
SecureAmHeader::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::securebatman::SecureAmHeader")
    .SetParent<Header> ()
    .AddConstructor<SecureAmHeader> ();
  return tid;
}

TypeId
SecureAmHeader::GetInstanceTypeId () const
{
  return GetTypeId ();
}

/*
 * Return total packet size, 799 Bytes
 */
uint32_t
SecureAmHeader::GetSerializedSize () const
{
  return 799;
}

/*
 * Need to serialize and deserialize the header/packet to a byte buffer in its network representation
 */
void
SecureAmHeader::Serialize (Buffer::Iterator start) const
{
	Buffer::Iterator it = start;
	for(uint i = 0;i<16;i++)
	{
		it.WriteU8 (m_ephemeralKey[i]);
	}
	for(uint i = 0;i<16;i++)
	{
		it.WriteU8 (m_iv[i]);
	}
	for(uint i = 0;i<767;i++)
	{
		it.WriteU8 (m_nonce[i]);
	}
}
uint32_t
SecureAmHeader::Deserialize (Buffer::Iterator start)
{
	Buffer::Iterator it = start;
//	if (m_ephemeralKey) delete m_ephemeralKey;
	m_ephemeralKey = new unsigned char[16];
	for (uint i=0;i<16;i++)
	{
		m_ephemeralKey[i] = it.ReadU8();
	}

	m_iv = new unsigned char[16];
	for (uint i=0;i<16;i++)
	{
		m_iv[i] = it.ReadU8();
	}

	m_nonce = new unsigned char[767];
	for (uint i=0;i<767;i++)
	{
		m_nonce[i] = it.ReadU8();
	}

	uint32_t dist = it.GetDistanceFrom (start);
	NS_ASSERT (dist == GetSerializedSize ());
	return dist;
}

/*
 * Prints the content of the header/packet
 */
void
SecureAmHeader::Print (std::ostream &os) const
{
}

/*
 * constructor initializing fields in packet
 */
SecureBatmanHeader::SecureBatmanHeader (uint8_t version,
										UDFlags udFlags,
										uint8_t timeToLive,
										uint8_t gwFlags,
										uint16_t sequenceNumber,
										uint16_t gwPort,
										Ipv4Address originatorAddress,
										Ipv4Address prevSender,
										uint8_t tqValue,
										uint8_t hnaLength,
										unsigned char *oneTimePassword,
										uint16_t keyStreamSeqNo )
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
    m_keyStreamSeqNo (keyStreamSeqNo)
{
}

SecureBatmanHeader::~SecureBatmanHeader ()
{
}

/*
 * Need to give a TypeId to BatmanHeader class
 */
TypeId
SecureBatmanHeader::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::securebatman::SecureBatmanHeader")
    .SetParent<Header> ()
    .AddConstructor<SecureBatmanHeader> ();
  return tid;
}

TypeId
SecureBatmanHeader::GetInstanceTypeId () const
{
  return GetTypeId ();
}

/*
 * Return total packet size, 22 Bytes
 */
uint32_t
SecureBatmanHeader::GetSerializedSize () const
{
  return 22;
}

/*
 * Need to serialize and deserialize the header/packet to a byte buffer in its network representation
 */
void
SecureBatmanHeader::Serialize (Buffer::Iterator i) const
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
	for(uint it = 0;it<2;it++)
	{
		i.WriteU8 (m_oneTimePassword[it]);
	}
//	i.WriteHtonU16( m_oneTimePassword );
	i.WriteHtonU16( m_keyStreamSeqNo );
}
uint32_t
SecureBatmanHeader::Deserialize (Buffer::Iterator start)
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
	m_oneTimePassword = new unsigned char[2];
	for (uint it=0;it<2;it++)
	{
		m_oneTimePassword[it] = i.ReadU8();
	}
//	m_oneTimePassword = i.ReadNtohU16 ();
	m_keyStreamSeqNo = i.ReadNtohU16 ();

  uint32_t dist = i.GetDistanceFrom (start);
  NS_ASSERT (dist == GetSerializedSize ());
  return dist;
}

/*
 * Prints the content of the header/packet
 */
void
SecureBatmanHeader::Print (std::ostream &os) const
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
	   << " HNA Length: " << m_hnaLength;
}
}
}
