/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2006 Georgia Tech Research Corporation, INRIA
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
 * Authors: George F. Riley<riley@ece.gatech.edu>
 *          Mathieu Lacage <mathieu.lacage@sophia.inria.fr>
 */
#ifndef NODE_H
#define NODE_H

#include <vector>

#include "ns3/object.h"
#include "ns3/callback.h"
#include "ns3/ptr.h"
#include "ns3/net-device.h"

namespace ns3 {

class Application;
class Packet;
class Address;


/**
 * \ingroup node
 *
 * \brief A network Node.
 *
 * This class holds together:
 *   - a list of NetDevice objects which represent the network interfaces
 *     of this node which are connected to other Node instances through
 *     Channel instances.
 *   - a list of Application objects which represent the userspace
 *     traffic generation applications which interact with the Node
 *     through the Socket API.
 *   - a node Id: a unique per-node identifier.
 *   - a system Id: a unique Id used for parallel simulations.
 *
 * Every Node created is added to the NodeList automatically.
 */
class Node : public Object
{
public:
  static TypeId GetTypeId (void);

  /**
   * Must be invoked by subclasses only.
   */
  Node();
  /**
   * \param systemId a unique integer used for parallel simulations.
   *
   * Must be invoked by subclasses only.
   */
  Node(uint32_t systemId);

  virtual ~Node();

  /**
   * \returns the unique id of this node.
   * 
   * This unique id happens to be also the index of the Node into
   * the NodeList. 
   */
  uint32_t GetId (void) const;

  /**
   * \returns the system id for parallel simulations associated
   *          to this node.
   */
  uint32_t GetSystemId (void) const;

  /**
   * \param device NetDevice to associate to this node.
   * \returns the index of the NetDevice into the Node's list of
   *          NetDevice.
   *
   * Associate this device to this node.
   */
  uint32_t AddDevice (Ptr<NetDevice> device);
  /**
   * \param index the index of the requested NetDevice
   * \returns the requested NetDevice associated to this Node.
   *
   * The indexes used by the GetDevice method start at one and
   * end at GetNDevices ()
   */
  Ptr<NetDevice> GetDevice (uint32_t index) const;
  /**
   * \returns the number of NetDevice instances associated
   *          to this Node.
   */
  uint32_t GetNDevices (void) const;

  /**
   * \param application Application to associate to this node.
   * \returns the index of the Application within the Node's list
   *          of Application.
   *
   * Associated this Application to this Node. This method is called
   * automatically from Application::Application so the user
   * has little reasons to call this method directly.
   */
  uint32_t AddApplication (Ptr<Application> application);
  /**
   * \param index
   * \returns the application associated to this requested index
   *          within this Node.
   */
  Ptr<Application> GetApplication (uint32_t index) const;

  /**
   * \returns the number of applications associated to this Node.
   */
  uint32_t GetNApplications (void) const;

  /**
   * A protocol handler
   *
   * \param device a pointer to the net device which received the packet
   * \param packet the packet received
   * \param protocol the 16 bit protocol number associated with this packet.
   *        This protocol number is expected to be the same protocol number
   *        given to the Send method by the user on the sender side.
   * \param sender the address of the sender
   * \param receiver the address of the receiver; Note: this value is
   *                 only valid for promiscuous mode protocol
   *                 handlers.  Note:  If the L2 protocol does not use L2
   *                 addresses, the address reported here is the value of 
   *                 device->GetAddress().
   * \param packetType type of packet received
   *                   (broadcast/multicast/unicast/otherhost); Note:
   *                   this value is only valid for promiscuous mode
   *                   protocol handlers.  
   */
  typedef Callback<void,Ptr<NetDevice>, Ptr<const Packet>,uint16_t,const Address &,
                   const Address &, NetDevice::PacketType> ProtocolHandler;
  /**
   * \param handler the handler to register
   * \param protocolType the type of protocol this handler is 
   *        interested in. This protocol type is a so-called
   *        EtherType, as registered here:
   *        http://standards.ieee.org/regauth/ethertype/eth.txt
   *        the value zero is interpreted as matching all
   *        protocols.
   * \param device the device attached to this handler. If the
   *        value is zero, the handler is attached to all
   *        devices on this node.
   * \param promiscuous whether to register a promiscuous mode handler
   */
  void RegisterProtocolHandler (ProtocolHandler handler, 
                                uint16_t protocolType,
                                Ptr<NetDevice> device,
                                bool promiscuous=false);
  /**
   * \param handler the handler to unregister
   *
   * After this call returns, the input handler will never
   * be invoked anymore.
   */
  void UnregisterProtocolHandler (ProtocolHandler handler);

  
  /**
   * \returns true if checksums are enabled, false otherwise.
   */
  static bool ChecksumEnabled (void);


protected:
  /**
   * The dispose method. Subclasses must override this method
   * and must chain up to it by calling Node::DoDispose at the
   * end of their own DoDispose method.
   */
  virtual void DoDispose (void);
  virtual void DoStart (void);
private:

  /**
   * \param device the device added to this Node.
   *
   * This method is invoked whenever a user calls Node::AddDevice.
   */
  virtual void NotifyDeviceAdded (Ptr<NetDevice> device);
  bool NonPromiscReceiveFromDevice (Ptr<NetDevice> device, Ptr<const Packet>, uint16_t protocol, const Address &from);
  bool PromiscReceiveFromDevice (Ptr<NetDevice> device, Ptr<const Packet>, uint16_t protocol,
                                 const Address &from, const Address &to, NetDevice::PacketType packetType);
  bool ReceiveFromDevice (Ptr<NetDevice> device, Ptr<const Packet>, uint16_t protocol,
                          const Address &from, const Address &to, NetDevice::PacketType packetType, bool promisc);

  void Construct (void);

  struct ProtocolHandlerEntry {
    ProtocolHandler handler;
    Ptr<NetDevice> device;
    uint16_t protocol;
    bool promiscuous;
  };
  typedef std::vector<struct Node::ProtocolHandlerEntry> ProtocolHandlerList;
  uint32_t    m_id;         // Node id for this node
  uint32_t    m_sid;        // System id for this node
  std::vector<Ptr<NetDevice> > m_devices;
  std::vector<Ptr<Application> > m_applications;
  ProtocolHandlerList m_handlers;

};

} //namespace ns3

#endif /* NODE_H */
