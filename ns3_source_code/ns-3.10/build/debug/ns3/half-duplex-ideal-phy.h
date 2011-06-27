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
 */

#ifndef HALF_DUPLEX_IDEAL_PHY_H
#define HALF_DUPLEX_IDEAL_PHY_H


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

namespace ns3 {



/**
 * This PHY layer implementation realizes an ideal OFDM PHY which
 * transmits half-duplex (i.e., it can either receive or transmit at a
 * given time). The device is ideal in the sense that:
 * 1) it uses an error model based on the Shannon capacity, which
 * assumes ideal channel coding;
 * 2) it uses ideal signal acquisition, i.e., preamble detection and
 * synchronization are always successful
 * 3) it has no PHY layer overhead
 *
 * Being half duplex, if a RX is ongoing but a TX is requested, the RX
 * is aborted and the TX is started. Of course, no RX can be performed
 * while there is an ongoing TX.
 *
 * The use of OFDM is modeled by means of the Spectrum framework. By
 * calling the method SetTxPowerSpectralDensity(), the
 * user can specify how much of the spectrum is used, how many
 * subcarriers are used, and what power is allocated to each
 * subcarrier.
 *
 * The user can also specify the PHY rate
 * at which communications take place by using SetRate(). This is
 * equivalent to choosing a particular modulation and coding scheme.
 *
 * The use of the ShannonSpectrumErrorModel allows us to account for
 * the following aspects in determining whether a
 * transmission is successful or not:
 * - the PHY rate (trades off communication speed with reliability)
 * - the power spectral density (trade-off among total power consumed,
 * total bandwidth used (i.e., how much of the spectrum is occupied),
 * and communication reliability)
 * - the signal propagation
 */
class HalfDuplexIdealPhy : public SpectrumPhy
{

public:
  HalfDuplexIdealPhy ();
  virtual ~HalfDuplexIdealPhy ();

  /**
   *  PHY states
   *
   */
  enum State {
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
  void StartRx (Ptr<PacketBurst> p, Ptr <const SpectrumValue> rxPsd, SpectrumType st, Time duration);
  


  /**
   * Get the SpectrumType used by this PHY
   *
   * @return
   */
  SpectrumType GetSpectrumType ();


  /**
   * set the Power Spectral Density of outgoing signals in power units
   * (Watt, Pascal...) per Hz.
   *
   * @param txPsd
   */
  void SetTxPowerSpectralDensity (Ptr<SpectrumValue> txPsd);

  /**
   *
   * @param noisePsd the Noise Power Spectral Density in power units
   * (Watt, Pascal...) per Hz.
   */
  void SetNoisePowerSpectralDensity (Ptr<const SpectrumValue> noisePsd);


  /**
   * Start a transmission
   *
   *
   * @param p the packet to be transmitted
   *
   * @return true if an error occurred and the transmission was not
   * started, false otherwise.
   */
  bool StartTx (Ptr<Packet> p);

  /**
   * set the PHY rate to be used by this PHY.
   *
   * @param rate
   */
  void SetRate (DataRate rate);

  /**
   *
   * @return the PHY rate used by this PHY.
   */
  DataRate GetRate () const;

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



private:

  virtual void DoDispose (void);
  
  void ChangeState (State newState);
  void EndTx ();
  void AbortRx ();
  void EndRx ();

  EventId m_endRxEventId;

  Ptr<Object> m_mobility;
  Ptr<Object> m_netDevice;
  Ptr<SpectrumChannel> m_channel;

  Ptr<SpectrumValue> m_txPsd;
  Ptr<const SpectrumValue> m_rxPsd;
  Ptr<Packet> m_txPacket;
  Ptr<Packet> m_rxPacket;

  DataRate m_rate;

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

  SpectrumInterference m_interference;

};






}





#endif /* HALF_DUPLEX_IDEAL_PHY_H */
