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
#ifndef SECURE_BATMANPACKET_H_
#define SECURE_BATMANPACKET_H_

#include <iostream>
#include "ns3/header.h"
#include "ns3/ipv4-address.h"
#include "ns3/nstime.h"

namespace ns3 {
namespace securebatman {
/*
 * BATMAN Packet Format IV
 *
 |      0        |      1        |      2        |       3       |
  0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 |    Version    |U|D|           |      TTL   	 |S| down  | up  |
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 |        Sequence Number        |           GW Port             |
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 |                       Originator Address                      |
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 |                         Previous Sender                       |
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 |       TQ      |   HNA Length  |		One-Time Password		 |
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 |		Key Stream Seq No	     |
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 *AM Header
 *
  |      0        |      1        |      2        |       3       |
  0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 |   														     |
 |   						Ephemeral Key					     |
 |   						 (16 bytes)						     |
 |   															 |
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 | 		       					 					           	 |
 | 		       					 IV 				           	 |
 | 		     				(16 bytes) 				           	 |
 | 		       					 					           	 |
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 |        					  					           	     |
 |        					  nonce				           	     |
 |        					(767 bytes)			           	     |
 |        					  					           	     |
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 */

class SecureAmHeader : public Header
{
public:
  SecureAmHeader (unsigned char *ephemeralKey = NULL,
	  	  	  	  unsigned char *iv = NULL,
	  	  	  	  unsigned char *nonce = NULL );

  virtual ~SecureAmHeader ();
  static TypeId GetTypeId (void);
  virtual TypeId GetInstanceTypeId (void) const;
  virtual uint32_t GetSerializedSize () const;
  virtual void Serialize (Buffer::Iterator start) const;
  virtual uint32_t Deserialize (Buffer::Iterator start);
  virtual void Print (std::ostream &os) const;

  /*
   * Create sets and gets for the different fields in packet
   */
    void
    SetEphemeralKey (unsigned char *key)
    {
    	m_ephemeralKey = key;
    }
    unsigned char*
    GetEphemeralKey ()
    {
    	return m_ephemeralKey;
    }
    void
    SetIv(unsigned char * iv)
    {
    	m_iv = iv;
    }
    unsigned char*
    GetIv ()
    {
    	return m_iv;
    }
    void
    SetNonce (unsigned char *nonce)
    {
    	m_nonce = nonce;
    }
    unsigned char*
    GetNonce ()
    {
    	return m_nonce;
    }

  /*
   * declare the fields in packet
   */
private:

    //AM Header
    unsigned char *m_ephemeralKey;
    unsigned char *m_iv;
    unsigned char *m_nonce;
};

class SecureBatmanHeader : public Header
{
public:

  enum UDFlags {
	  _UD_FLAG	= 0,
	  D_FLAG	= 1,
	  U_FLAG	= 2,
	  UD_FLAG	= 3,
  };

  SecureBatmanHeader (uint8_t version = 0,
		  	  	  	  UDFlags udFlags = _UD_FLAG,
		  	  	  	  uint8_t timeToLive = 0,
		  	  	  	  uint8_t gwFlags = 0,
		  	  	  	  uint16_t sequenceNumber = 0,
		  	  	  	  uint16_t gwPort = 0,
		  	  	  	  Ipv4Address originatorAddress = Ipv4Address (),
		  	  	  	  Ipv4Address prevSender = Ipv4Address(),
		  	  	  	  uint8_t tqValue = 255,
		  	  	  	  uint8_t hnaLength = 0,
		  	  	  	  unsigned char *keyStreamSeqNo = NULL,
		  	  	  	  uint16_t oneTimePassword = 0 );

  virtual ~SecureBatmanHeader ();
  static TypeId GetTypeId (void);
  virtual TypeId GetInstanceTypeId (void) const;
  virtual uint32_t GetSerializedSize () const;
  virtual void Serialize (Buffer::Iterator start) const;
  virtual uint32_t Deserialize (Buffer::Iterator start);
  virtual void Print (std::ostream &os) const;

  /*
   * Create sets and gets for the different fields in packet
   */
    void
    SetVersion (uint8_t version)
    {
    	m_version = version;
    }
    uint8_t
    GetVersion ()
    {
    	return m_version;
    }
    void
    SetUDFlags(UDFlags UDFlags)
    {
    	m_UDFlags = UDFlags;
    }
    UDFlags
    GetUDFlags ()
    {
    	return m_UDFlags;
    }
    void
    SetTimeToLive (uint8_t timeToLive)
    {
    	m_timeToLive = timeToLive;
    }
    uint8_t
    GetTimeToLive ()
    {
    	return m_timeToLive;
    }
    void
    SetGWFlags (uint8_t GWFlags)
    {
    	m_GWFlags = GWFlags;
    }
    uint8_t
    GetGWFlags ()
    {
    	return m_GWFlags;
    }
    void
    SetSequenceNumber (uint16_t sequenceNumber)
    {
    	m_sequenceNumber = sequenceNumber;
    }
    uint16_t
    GetSequenceNumber ()
    {
    	return m_sequenceNumber;
    }
    void SetGWPort (uint16_t GWPort)
    {
    	m_GWPort = GWPort;
    }
    uint16_t
    GetGWPort ()
    {
    	return m_GWPort;
    }
    void
    SetOriginatorAddress (Ipv4Address originatorAddress)
    {
    	m_originatorAddress = originatorAddress;
    }
    Ipv4Address
    GetOriginatorAddress ()
    {
    	return m_originatorAddress;
    }
    void
    SetPrevSender (Ipv4Address prevSender)
    {
    	m_prevSender = prevSender;
    }
    Ipv4Address
    GetPrevSender ()
    {
    	return m_prevSender;
    }
    void
    SetTqValue (uint8_t tqValue)
    {
    	m_tqValue = tqValue;
    }
    uint8_t
    GetTqValue ()
    {
    	return m_tqValue;
    }
    void
    SetHnaLength (uint8_t hnaLength)
    {
    	m_hnaLength = hnaLength;
    }
    uint8_t
    GetHnaLength ()
    {
    	return m_hnaLength;
    }
    void
    SetOneTimePassword (unsigned char *oneTimePassword)
    {
    	m_oneTimePassword = oneTimePassword;
    }
    unsigned char*
    GetOneTimePassword ()
    {
    	return m_oneTimePassword;
    }
    void
    SetKeyStreamSeqNo (uint16_t keyStreamSeqNo)
    {
    	m_keyStreamSeqNo = keyStreamSeqNo;
    }
    uint16_t
    GetKeyStreamSeqNo ()
    {
    	return m_keyStreamSeqNo;
    }

  /*
   * declare the fields in packet
   */
private:

    uint8_t m_version;
    UDFlags m_UDFlags;
    uint8_t m_timeToLive;
    uint8_t m_GWFlags;
    uint16_t m_sequenceNumber;
    uint16_t m_GWPort;
    Ipv4Address m_originatorAddress;
    Ipv4Address m_prevSender;
    uint8_t m_tqValue;
    uint8_t m_hnaLength;
    unsigned char *m_oneTimePassword;
    uint16_t m_keyStreamSeqNo;
};

/*
 * Prints the content of the header/packet
 */
static inline std::ostream & operator<< (std::ostream& os, const SecureBatmanHeader & packet)
{
  packet.Print (os);
  return os;
}
}
}
#endif /* SECURE_BATMANPACKET_H_ */
