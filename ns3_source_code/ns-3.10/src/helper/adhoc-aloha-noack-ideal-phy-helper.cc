/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2010 CTTC
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
 * Author: Nicola Baldo <nbaldo@cttc.es>
 */
#include "ns3/propagation-delay-model.h"
#include "ns3/spectrum-propagation-loss-model.h"
#include "ns3/mobility-model.h"
#include "ns3/log.h"
#include "ns3/config.h"
#include "ns3/simulator.h"
#include "ns3/names.h"
#include "ns3/spectrum-channel.h"
#include "ns3/half-duplex-ideal-phy.h"
#include "ns3/mac48-address.h"
#include "ns3/aloha-noack-net-device.h"
#include "adhoc-aloha-noack-ideal-phy-helper.h"




NS_LOG_COMPONENT_DEFINE ("AdhocAlohaNoackIdealPhyHelper");

namespace ns3 {


AdhocAlohaNoackIdealPhyHelper::AdhocAlohaNoackIdealPhyHelper ()
{
  m_phy.SetTypeId ("ns3::HalfDuplexIdealPhy");
  m_device.SetTypeId ("ns3::AlohaNoackNetDevice");
  m_queue.SetTypeId ("ns3::DropTailQueue");
}

AdhocAlohaNoackIdealPhyHelper::~AdhocAlohaNoackIdealPhyHelper ()
{
}

void
AdhocAlohaNoackIdealPhyHelper::SetChannel (Ptr<SpectrumChannel> channel)
{
  m_channel = channel;
}

void
AdhocAlohaNoackIdealPhyHelper::SetChannel (std::string channelName)
{
  Ptr<SpectrumChannel> channel = Names::Find<SpectrumChannel> (channelName);
  m_channel = channel;
}

void
AdhocAlohaNoackIdealPhyHelper::SetTxPowerSpectralDensity (Ptr<SpectrumValue> txPsd)
{
  NS_LOG_FUNCTION (this << txPsd);
  m_txPsd = txPsd;
}

void
AdhocAlohaNoackIdealPhyHelper::SetNoisePowerSpectralDensity (Ptr<SpectrumValue> noisePsd)
{
  NS_LOG_FUNCTION (this << noisePsd);
  m_noisePsd = noisePsd;
}

void
AdhocAlohaNoackIdealPhyHelper::SetPhyAttribute (std::string name, const AttributeValue &v)
{
  m_phy.Set (name, v);
}


void
AdhocAlohaNoackIdealPhyHelper::SetDeviceAttribute (std::string name, const AttributeValue &v)
{
  m_device.Set (name, v);
}

NetDeviceContainer
AdhocAlohaNoackIdealPhyHelper::Install (NodeContainer c) const
{
  NetDeviceContainer devices;
  for (NodeContainer::Iterator i = c.Begin (); i != c.End (); ++i)
    {
      Ptr<Node> node = *i;

      Ptr<AlohaNoackNetDevice> dev = (m_device.Create ())->GetObject<AlohaNoackNetDevice> ();
      dev->SetAddress (Mac48Address::Allocate ());
      Ptr<Queue> q = (m_queue.Create ())->GetObject<Queue> ();
      dev->SetQueue (q);

      // note that we could have used a SpectrumPhyHelper here, but
      // given that it is straightforward to handle the configuration
      // in this helper here, we avoid asking the user to pass us a
      // SpectrumPhyHelper, so to spare him some typing.

      Ptr<HalfDuplexIdealPhy>  phy = (m_phy.Create ())->GetObject<HalfDuplexIdealPhy> ();
      NS_ASSERT (phy);

      dev->SetPhy (phy);

      NS_ASSERT (node);
      phy->SetMobility (node);

      NS_ASSERT (dev);
      phy->SetDevice (dev);

      NS_ASSERT_MSG (m_txPsd, "you forgot to call AdhocAlohaNoackIdealPhyHelper::SetTxPowerSpectralDensity ()");
      phy->SetTxPowerSpectralDensity (m_txPsd);

      NS_ASSERT_MSG (m_noisePsd, "you forgot to call AdhocAlohaNoackIdealPhyHelper::SetNoisePowerSpectralDensity ()");
      phy->SetNoisePowerSpectralDensity (m_noisePsd);

      NS_ASSERT_MSG (m_channel, "you forgot to call AdhocAlohaNoackIdealPhyHelper::SetChannel ()");
      phy->SetChannel (m_channel);
      dev->SetChannel (m_channel);
      m_channel->AddRx (phy);

      phy->SetPhyMacTxEndCallback   (MakeCallback (&AlohaNoackNetDevice::NotifyTransmissionEnd, dev));
      phy->SetPhyMacRxStartCallback (MakeCallback (&AlohaNoackNetDevice::NotifyReceptionStart, dev));
      phy->SetPhyMacRxEndOkCallback (MakeCallback (&AlohaNoackNetDevice::NotifyReceptionEndOk, dev));
      dev->SetPhyMacTxStartCallback (MakeCallback (&HalfDuplexIdealPhy::StartTx, phy));

      node->AddDevice (dev);
      devices.Add (dev);
    }
  return devices;
}

NetDeviceContainer
AdhocAlohaNoackIdealPhyHelper::Install (Ptr<Node> node) const
{
  return Install (NodeContainer (node));
}

NetDeviceContainer
AdhocAlohaNoackIdealPhyHelper::Install (std::string nodeName) const
{
  Ptr<Node> node = Names::Find<Node> (nodeName);
  return Install (node);
}


} // namespace ns3
