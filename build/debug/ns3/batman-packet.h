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
#ifndef BATMANPACKET_H_
#define BATMANPACKET_H_

#include <iostream>
#include "ns3/header.h"
#include "ns3/ipv4-address.h"
#include "ns3/nstime.h"

namespace ns3 {
namespace batman {
/**
 * \ingroup batman
 * BATMAN Packet Format III
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
 *
 ** BATMAN Packet Format IV
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
 |       TQ      |   HNA Length  |		    	AUTH			 |
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 */

class BatmanHeader : public Header
{
public:

  enum UDFlags {
	  _UD_FLAG	= 0,
	  D_FLAG	= 1,
	  U_FLAG	= 2,
	  UD_FLAG	= 3,
  };

  BatmanHeader (uint8_t version = 0, UDFlags udFlags = _UD_FLAG, uint8_t timeToLive = 0, uint8_t gwFlags = 0, uint16_t sequenceNumber = 0, uint16_t gwPort = 0,
		  	  	  Ipv4Address originatorAddress = Ipv4Address (), Ipv4Address prevSender = Ipv4Address(),
		  	  	  uint8_t tqValue = 255, uint8_t hnaLength = 0, uint16_t authValue = 0);
  virtual ~BatmanHeader ();
  static TypeId GetTypeId (void);
  virtual TypeId GetInstanceTypeId (void) const;
  virtual uint32_t GetSerializedSize () const;
  virtual void Serialize (Buffer::Iterator start) const;
  virtual uint32_t Deserialize (Buffer::Iterator start);
  virtual void Print (std::ostream &os) const;

  /*
   * agb
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
    SetAuthValue (uint16_t authValue)
    {
    	m_authValue = authValue;
    }
    uint16_t
    GetAuthValue ()
    {
    	return m_authValue;
    }

  /*
   * agb
   * declare the fields in packet
   */
private:

    //agb: BATMAN III
    uint8_t m_version;	// /< BATMAN version
    UDFlags m_UDFlags;	// /< Is-Direct-Link Flag and Unidirectional Flag
    uint8_t m_timeToLive;	// /< Time To Live
    uint8_t m_GWFlags;	// /< Gateway Flags
    uint16_t m_sequenceNumber;	// /< OGM Sequence Number
    uint16_t m_GWPort;	// /< Gateway Port
    Ipv4Address m_originatorAddress;	// /< Origiantor Address

    // agb: BATMAN IV
    Ipv4Address m_prevSender;
    uint8_t m_tqValue;
    uint8_t m_hnaLength;
    uint16_t m_authValue;
};

/*
 * agb
 * Prints the content of the header/packet
 */
static inline std::ostream & operator<< (std::ostream& os, const BatmanHeader & packet)
{
  packet.Print (os);
  return os;
}
}
}
#endif /* BATMANPACKET_H_ */
