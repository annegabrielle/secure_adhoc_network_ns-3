/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2009 CTTC
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
 *         Giuseppe Piro  <g.piro@poliba.it>
 */

#ifndef LTE_SPECTRUM_PHY_H
#define LTE_SPECTRUM_PHY_H


#include <ns3/spectrum-value.h>
#include <ns3/mobility-model.h>
#include <ns3/packet.h>
#include <ns3/nstime.h>
#include <ns3/net-device.h>
#include <ns3/spectrum-phy.h>
#include <ns3/spectrum-channel.h>
#include <ns3/spectrum-type.h>
#include <ns3/spectrum-interference.h>
#include <ns3/data-rate.h>
#include <ns3/phy-mac.h>
#include <ns3/packet-burst.h>

namespace ns3 {

class LteNetDevice;

/**
 * The LteSpectrumPhy models the physical layer of LTE
 */
class LteSpectrumPhy : public SpectrumPhy
{

public:
  LteSpectrumPhy ();
  virtual ~LteSpectrumPhy ();

  /**
   *  PHY states
   */
  enum State
  {
    IDLE, TX, RX
  };

  static TypeId GetTypeId (void);

  // inherited from SpectrumPhy
  void SetChannel (Ptr<SpectrumChannel> c);
  void SetMobility (Ptr<Object> m);
  void SetDevice (Ptr<Object> d);
  Ptr<Object> GetMobility ();
  Ptr<Object> GetDevice ();
  Ptr<const SpectrumModel> GetRxSpectrumModel () const;

  /**
   * \brief Get the channel where the physical layer is attached
   * \return a pointer to the channel
   */
  Ptr<SpectrumChannel> GetChannel (void);


  /**
   * Get the SpectrumType used by this PHY
   *
   * @return
   */
  SpectrumType GetSpectrumType ();


  /**
   * set the Power Spectral Density of outgoing signals in W/Hz.
   *
   * @param txPsd
   */
  void SetTxPowerSpectralDensity (Ptr<SpectrumValue> txPsd);

  /**
   * \brief set the noise power spectral density
   * @param noisePsd the Noise Power Spectral Density in power units
   * (Watt, Pascal...) per Hz.
   */
  void SetNoisePowerSpectralDensity (Ptr<const SpectrumValue> noisePsd);

  /**
   * \brief get the noise power spectral density
   * @return the Noise Power Spectral Density
   */
  Ptr<const SpectrumValue> GetNoisePowerSpectralDensity (void);

  /**
   * Start a transmission
   *
   *
   * @param pb the burst of packets to be transmitted
   *
   * @return true if an error occurred and the transmission was not
   * started, false otherwise.
   */
  bool StartTx (Ptr<PacketBurst> pb);

  /**
   * \brief Notify the SpectrumPhy instance of an incoming waveform
   * \param pb the burst of packet associated with the incoming waveform
   * \param rxPsd the Power Spectral Density of the incoming waveform. 
   * The units of the SPD are the same specified for SpectrumChannel::StartTx().
   * \param st the spectrum type
   * \param duration the duration of the incoming waveform
   */
  void StartRx (Ptr<PacketBurst> pb, Ptr <const SpectrumValue> rxPsd, SpectrumType st, Time duration);

  /**
   * set the callback for the end of a TX, as part of the
   * interconnections betweenthe PHY and the MAC
   *
   * @param c the callback
   */
  void SetPhyMacTxEndCallback (PhyMacTxEndCallback c);

  /**
   * set the callback for the start of RX, as part of the
   * interconnections betweenthe PHY and the MAC
   *
   * @param c the callback
   */
  void SetPhyMacRxStartCallback (PhyMacRxStartCallback c);

  /**
   * set the callback for the end of a RX in error, as part of the
   * interconnections betweenthe PHY and the MAC
   *
   * @param c the callback
   */
  void SetPhyMacRxEndErrorCallback (PhyMacRxEndErrorCallback c);

  /**
   * set the callback for the successful end of a RX, as part of the
   * interconnections betweenthe PHY and the MAC
   *
   * @param c the callback
   */
  void SetPhyMacRxEndOkCallback (PhyMacRxEndOkCallback c);

  /**
   * \brief Calculate the SINR estimated during the reception of the
   * packet.
   * \param rxPsd the Power Spectral Density of the incoming waveform.
   * \param noise the Power Spectral Density of the noise.
   */
  virtual void CalcSinrValues (Ptr <const SpectrumValue> rxPsd, Ptr <const SpectrumValue> noise) = 0;


  /**
   * \brief Set the state of the phy layer
   * \param newState the state 
   */
  void SetState (State newState);

private:
  void ChangeState (State newState);
  void EndTx ();
  void AbortRx ();
  virtual void EndRx ();

  EventId m_endRxEventId;

  Ptr<Object> m_mobility;

  Ptr<Object> m_device;

  Ptr<SpectrumChannel> m_channel;

  Ptr<SpectrumValue> m_txPsd;
  Ptr<const SpectrumValue> m_rxPsd;
  Ptr<PacketBurst> m_txPacket;
  Ptr<PacketBurst> m_rxPacket;

  State m_state;

  TracedCallback<Ptr<const Packet> > m_phyTxStartTrace;
  TracedCallback<Ptr<const Packet> > m_phyTxEndTrace;
  TracedCallback<Ptr<const Packet> > m_phyRxStartTrace;
  TracedCallback<Ptr<const Packet> > m_phyRxAbortTrace;
  TracedCallback<Ptr<const Packet> > m_phyRxEndOkTrace;
  TracedCallback<Ptr<const Packet> > m_phyRxEndErrorTrace;

  PhyMacTxEndCallback        m_phyMacTxEndCallback;
  PhyMacRxStartCallback      m_phyMacRxStartCallback;
  PhyMacRxEndErrorCallback   m_phyMacRxEndErrorCallback;
  PhyMacRxEndOkCallback      m_phyMacRxEndOkCallback;


  Ptr<const SpectrumValue> m_noise;
};






}

#endif /* LTE_SPECTRUM_PHY_H */
