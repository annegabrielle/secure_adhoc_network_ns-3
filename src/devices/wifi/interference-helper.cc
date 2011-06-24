/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2005,2006 INRIA
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
 * Author: Mathieu Lacage <mathieu.lacage@sophia.inria.fr>
 */
#include "interference-helper.h"
#include "wifi-phy.h"
#include "error-rate-model.h"
#include "ns3/simulator.h"
#include "ns3/log.h"
#include <algorithm>

NS_LOG_COMPONENT_DEFINE ("InterferenceHelper");

namespace ns3 {

/****************************************************************
 *       Phy event class
 ****************************************************************/

InterferenceHelper::Event::Event (uint32_t size, WifiMode payloadMode, 
					       enum WifiPreamble preamble,
					       Time duration, double rxPower)
  : m_size (size),
    m_payloadMode (payloadMode),
    m_preamble (preamble),
    m_startTime (Simulator::Now ()),
    m_endTime (m_startTime + duration),
    m_rxPowerW (rxPower)
{}
InterferenceHelper::Event::~Event ()
{}
  
Time 
InterferenceHelper::Event::GetDuration (void) const 
{
  return m_endTime - m_startTime;
}
Time 
InterferenceHelper::Event::GetStartTime (void) const
{
  return m_startTime;
}
Time 
InterferenceHelper::Event::GetEndTime (void) const
{
  return m_endTime;
}
double 
InterferenceHelper::Event::GetRxPowerW (void) const
{
  return m_rxPowerW;
}
uint32_t 
InterferenceHelper::Event::GetSize (void) const
{
  return m_size;
}
WifiMode 
InterferenceHelper::Event::GetPayloadMode (void) const
{
  return m_payloadMode;
}
enum WifiPreamble 
InterferenceHelper::Event::GetPreambleType (void) const
{
  return m_preamble;
}

/****************************************************************
 *       Class which records SNIR change events for a 
 *       short period of time.
 ****************************************************************/

InterferenceHelper::NiChange::NiChange (Time time, double delta)
  : m_time (time), m_delta (delta) 
{}
Time
InterferenceHelper::NiChange::GetTime (void) const
{
  return m_time;
}
double 
InterferenceHelper::NiChange::GetDelta (void) const
{
  return m_delta;
}
bool 
InterferenceHelper::NiChange::operator < (const InterferenceHelper::NiChange& o) const
{
  return (m_time < o.m_time);
}

/****************************************************************
 *       The actual InterferenceHelper
 ****************************************************************/

InterferenceHelper::InterferenceHelper ()
  : m_errorRateModel (0),
    m_firstPower (0.0),
    m_rxing (false)
{}
InterferenceHelper::~InterferenceHelper ()
{
  EraseEvents ();
  m_errorRateModel = 0;
}

Ptr<InterferenceHelper::Event> 
InterferenceHelper::Add (uint32_t size, WifiMode payloadMode, 
			 enum WifiPreamble preamble,
			 Time duration, double rxPowerW)
{
  Ptr<InterferenceHelper::Event> event;

  event = Create<InterferenceHelper::Event> 
    (size,
     payloadMode,
     preamble,
     duration,
     rxPowerW);
  AppendEvent (event);
  return event;
}


void 
InterferenceHelper::SetNoiseFigure (double value)
{
  m_noiseFigure = value;
}

double 
InterferenceHelper::GetNoiseFigure (void) const
{
  return m_noiseFigure;
}

void 
InterferenceHelper::SetErrorRateModel (Ptr<ErrorRateModel> rate)
{
  m_errorRateModel = rate;
}

Ptr<ErrorRateModel> 
InterferenceHelper::GetErrorRateModel (void) const
{
  return m_errorRateModel;
}

Time 
InterferenceHelper::GetEnergyDuration (double energyW)
{
  Time now = Simulator::Now ();
  double noiseInterferenceW = 0.0;
  Time end = now;
  noiseInterferenceW = m_firstPower;
  for (NiChanges::const_iterator i = m_niChanges.begin (); i != m_niChanges.end (); i++)
    {
      noiseInterferenceW += i->GetDelta ();
      end = i->GetTime ();
      if (end < now)
        {
          continue;
        }
      if (noiseInterferenceW < energyW)
	      {
	        break;
	      }
    }
  return end > now ? end - now : MicroSeconds (0);
}

WifiMode 
InterferenceHelper::GetPlcpHeaderMode (WifiMode payloadMode, WifiPreamble preamble)
{
  switch (payloadMode.GetModulationClass ())
     {
     case WIFI_MOD_CLASS_OFDM:
       {
         switch (payloadMode.GetBandwidth ()) {
         case 5000000:
           return WifiPhy::GetOfdmRate1_5MbpsBW5MHz ();
         case 10000000:
           return WifiPhy::GetOfdmRate3MbpsBW10MHz ();
         default:
           // IEEE Std 802.11-2007, 17.3.2
           // actually this is only the first part of the PlcpHeader,
           // because the last 16 bits of the PlcpHeader are using the
           // same mode of the payload
           return WifiPhy::GetOfdmRate6Mbps ();
         }
       }

     case WIFI_MOD_CLASS_ERP_OFDM:
       return WifiPhy::GetErpOfdmRate6Mbps ();

     case WIFI_MOD_CLASS_DSSS:
       if (preamble == WIFI_PREAMBLE_LONG)
         {
           // IEEE Std 802.11-2007, sections 15.2.3 and 18.2.2.1 
           return WifiPhy::GetDsssRate1Mbps ();
         }
       else //  WIFI_PREAMBLE_SHORT
         {
           // IEEE Std 802.11-2007, section 18.2.2.2
           return WifiPhy::GetDsssRate2Mbps ();
         }

     default:
       NS_FATAL_ERROR("unsupported modulation class");
       return WifiMode ();
     }
}

uint32_t
InterferenceHelper::GetPlcpHeaderDurationMicroSeconds (WifiMode payloadMode, WifiPreamble preamble)
{
  switch (payloadMode.GetModulationClass ())
    {
    case WIFI_MOD_CLASS_OFDM:
      {
        switch (payloadMode.GetBandwidth ()) {
        case 20000000:
        default:
          // IEEE Std 802.11-2007, section 17.3.3 and figure 17-4
          // also section 17.3.2.3, table 17-4
          // We return the duration of the SIGNAL field only, since the
          // SERVICE field (which strictly speaking belongs to the PLCP
          // header, see section 17.3.2 and figure 17-1) is sent using the
          // payload mode.
          return 4;
        case 10000000:
          // IEEE Std 802.11-2007, section 17.3.2.3, table 17-4
          return 8;
        case 5000000:
          // IEEE Std 802.11-2007, section 17.3.2.3, table 17-4
          return 16;
        }
      }

    case WIFI_MOD_CLASS_ERP_OFDM:
      return 16;

    case WIFI_MOD_CLASS_DSSS:
      if (preamble == WIFI_PREAMBLE_SHORT)
        {
          // IEEE Std 802.11-2007, section 18.2.2.2 and figure 18-2
          return 24;
        }
      else // WIFI_PREAMBLE_LONG
        {
          // IEEE Std 802.11-2007, sections 18.2.2.1 and figure 18-1
          return 48;
        }

    default:
      NS_FATAL_ERROR("unsupported modulation class");
      return 0;
    }
}

uint32_t 
InterferenceHelper::GetPlcpPreambleDurationMicroSeconds (WifiMode payloadMode, WifiPreamble preamble)
{
  switch (payloadMode.GetModulationClass ())
    {
    case WIFI_MOD_CLASS_OFDM:
      {
        switch (payloadMode.GetBandwidth ()) {
        case 20000000:
        default:
          // IEEE Std 802.11-2007, section 17.3.3,  figure 17-4
          // also section 17.3.2.3, table 17-4
          return 16;
        case 10000000:
          // IEEE Std 802.11-2007, section 17.3.3, table 17-4
          // also section 17.3.2.3, table 17-4
          return 32;
        case 5000000:
          // IEEE Std 802.11-2007, section 17.3.3
          // also section 17.3.2.3, table 17-4
          return 64;
        }
      }

    case WIFI_MOD_CLASS_ERP_OFDM:
      return 4;

    case WIFI_MOD_CLASS_DSSS:
      if (preamble == WIFI_PREAMBLE_SHORT)
        {
          // IEEE Std 802.11-2007, section 18.2.2.2 and figure 18-2
          return 72;
        }
      else // WIFI_PREAMBLE_LONG
        {
          // IEEE Std 802.11-2007, sections 18.2.2.1 and figure 18-1
          return 144;
        }

    default:
      NS_FATAL_ERROR("unsupported modulation class");
      return 0;
    }
}

uint32_t 
InterferenceHelper::GetPayloadDurationMicroSeconds (uint32_t size, WifiMode payloadMode)
{
  NS_LOG_FUNCTION(size << payloadMode);

  switch (payloadMode.GetModulationClass ())
    {
    case WIFI_MOD_CLASS_OFDM:
    case WIFI_MOD_CLASS_ERP_OFDM:
      {
        // IEEE Std 802.11-2007, section 17.3.2.3, table 17-4
        // corresponds to T_{SYM} in the table
        uint32_t symbolDurationUs;

        switch (payloadMode.GetBandwidth ()) {
        case 20000000:
        default:
          symbolDurationUs = 4;
          break;
        case 10000000:
          symbolDurationUs = 8;
          break;
        case 5000000:
          symbolDurationUs = 16;
          break;
        }

        // IEEE Std 802.11-2007, section 17.3.2.2, table 17-3
        // corresponds to N_{DBPS} in the table
        double numDataBitsPerSymbol = payloadMode.GetDataRate ()  * symbolDurationUs / 1e6;

        // IEEE Std 802.11-2007, section 17.3.5.3, equation (17-11)
        uint32_t numSymbols = lrint (ceil ((16 + size * 8.0 + 6.0)/numDataBitsPerSymbol));

        // Add signal extension for ERP PHY
        if (payloadMode.GetModulationClass () == WIFI_MOD_CLASS_ERP_OFDM)
          return numSymbols*symbolDurationUs + 6;
        else
        return numSymbols*symbolDurationUs;
      }

    case WIFI_MOD_CLASS_DSSS:
      // IEEE Std 802.11-2007, section 18.2.3.5
      NS_LOG_LOGIC(" size=" << size
                   << " mode=" << payloadMode 
                   << " rate=" << payloadMode.GetDataRate () );
      return lrint(ceil ((size * 8.0) / (payloadMode.GetDataRate () / 1.0e6)));

    default:
      NS_FATAL_ERROR("unsupported modulation class");
      return 0;
    }
}

Time
InterferenceHelper::CalculateTxDuration (uint32_t size, WifiMode payloadMode, WifiPreamble preamble) 
{
  uint32_t duration = GetPlcpPreambleDurationMicroSeconds (payloadMode, preamble)     
                      + GetPlcpHeaderDurationMicroSeconds (payloadMode, preamble)  
                      + GetPayloadDurationMicroSeconds (size, payloadMode);
  return MicroSeconds (duration);
}

void 
InterferenceHelper::AppendEvent (Ptr<InterferenceHelper::Event> event)
{
  Time now = Simulator::Now ();
  if (!m_rxing)
    {
      NiChanges::iterator nowIterator = GetPosition (now);
      for (NiChanges::iterator i = m_niChanges.begin (); i != nowIterator; i++)
        {
          m_firstPower += i->GetDelta ();
        }
      m_niChanges.erase (m_niChanges.begin (), nowIterator);
      m_niChanges.insert (m_niChanges.begin (), NiChange (event->GetStartTime (), event->GetRxPowerW ())); 
    }
  else
    {
      AddNiChangeEvent (NiChange (event->GetStartTime (), event->GetRxPowerW ()));
    }
  AddNiChangeEvent(NiChange (event->GetEndTime (), -event->GetRxPowerW ()));

}


double
InterferenceHelper::CalculateSnr (double signal, double noiseInterference, WifiMode mode) const
{
  // thermal noise at 290K in J/s = W
  static const double BOLTZMANN = 1.3803e-23;
  // Nt is the power of thermal noise in W
  double Nt = BOLTZMANN * 290.0 * mode.GetBandwidth ();
  // receiver noise Floor (W) which accounts for thermal noise and non-idealities of the receiver
  double noiseFloor = m_noiseFigure * Nt;
  double noise = noiseFloor + noiseInterference;
  double snr = signal / noise;
  return snr;
}

double
InterferenceHelper::CalculateNoiseInterferenceW (Ptr<InterferenceHelper::Event> event, NiChanges *ni) const
{
  double noiseInterference = m_firstPower;
  NS_ASSERT (m_rxing);
  for (NiChanges::const_iterator i = m_niChanges.begin () + 1; i != m_niChanges.end (); i++)
    {
      if ((event->GetEndTime () == i->GetTime ()) && event->GetRxPowerW () == -i->GetDelta ())
        {
          break;
        }
      ni->push_back (*i);
    }
  ni->insert (ni->begin (), NiChange (event->GetStartTime (), noiseInterference));
  ni->push_back (NiChange (event->GetEndTime (), 0));
  return noiseInterference;
}

double
InterferenceHelper::CalculateChunkSuccessRate (double snir, Time duration, WifiMode mode) const
{
  if (duration == NanoSeconds (0)) {
    return 1.0;
  }
  uint32_t rate = mode.GetPhyRate ();
  uint64_t nbits = (uint64_t)(rate * duration.GetSeconds ());
  double csr = m_errorRateModel->GetChunkSuccessRate (mode, snir, (uint32_t)nbits);
  return csr;
}

double 
InterferenceHelper::CalculatePer (Ptr<const InterferenceHelper::Event> event, NiChanges *ni) const
{  
  double psr = 1.0; /* Packet Success Rate */
  NiChanges::iterator j = ni->begin ();
  Time previous = (*j).GetTime (); 
  WifiMode payloadMode = event->GetPayloadMode ();
  WifiPreamble preamble = event->GetPreambleType ();
  WifiMode headerMode = GetPlcpHeaderMode (payloadMode, preamble);
  Time plcpHeaderStart = (*j).GetTime () + MicroSeconds (GetPlcpPreambleDurationMicroSeconds (payloadMode, preamble));
  Time plcpPayloadStart = plcpHeaderStart + MicroSeconds (GetPlcpHeaderDurationMicroSeconds (payloadMode, preamble));
  double noiseInterferenceW = (*j).GetDelta ();
  double powerW = event->GetRxPowerW ();

  j++;
  while (ni->end () != j) 
    {
      Time current = (*j).GetTime ();
      NS_ASSERT (current >= previous);
    
      if (previous >= plcpPayloadStart) 
        {
          psr *= CalculateChunkSuccessRate (CalculateSnr (powerW, 
                                                          noiseInterferenceW, 
                                                          payloadMode), 
                                            current - previous,
                                            payloadMode);
        } 
      else if (previous >= plcpHeaderStart) 
        {
          if (current >= plcpPayloadStart) 
            {
              psr *= CalculateChunkSuccessRate (CalculateSnr (powerW, 
                                                              noiseInterferenceW, 
                                                              headerMode), 
                                                plcpPayloadStart - previous,
                                                headerMode);
              psr *= CalculateChunkSuccessRate (CalculateSnr (powerW, 
                                                              noiseInterferenceW, 
                                                              payloadMode),
                                                current - plcpPayloadStart,
                                                payloadMode);
            } 
          else 
            {
              NS_ASSERT (current >= plcpHeaderStart);
              psr *= CalculateChunkSuccessRate (CalculateSnr (powerW, 
                                                              noiseInterferenceW, 
                                                              headerMode), 
                                                current - previous,
                                                headerMode);
            }
        } 
      else 
        {
          if (current >= plcpPayloadStart) 
            {
              psr *= CalculateChunkSuccessRate (CalculateSnr (powerW, 
                                                              noiseInterferenceW, 
                                                              headerMode), 
                                                plcpPayloadStart - plcpHeaderStart,
                                                headerMode);
              psr *= CalculateChunkSuccessRate (CalculateSnr (powerW, 
                                                              noiseInterferenceW, 
                                                              payloadMode), 
                                                current - plcpPayloadStart,
                                                payloadMode);
            } 
          else if (current >= plcpHeaderStart) 
            {
              psr *= CalculateChunkSuccessRate (CalculateSnr (powerW, 
                                                              noiseInterferenceW, 
                                                              headerMode), 
                                                current - plcpHeaderStart,
                                                headerMode);
            }
        }

      noiseInterferenceW += (*j).GetDelta ();
      previous = (*j).GetTime ();
      j++;
    }

  double per = 1 - psr;
  return per;
}


struct InterferenceHelper::SnrPer 
InterferenceHelper::CalculateSnrPer (Ptr<InterferenceHelper::Event> event)
{
  NiChanges ni;
  double noiseInterferenceW = CalculateNoiseInterferenceW (event, &ni);
  double snr = CalculateSnr (event->GetRxPowerW (),
                             noiseInterferenceW,
                             event->GetPayloadMode ());
  
  /* calculate the SNIR at the start of the packet and accumulate
   * all SNIR changes in the snir vector.
   */
  double per = CalculatePer (event, &ni);

  struct SnrPer snrPer;
  snrPer.snr = snr;
  snrPer.per = per;
  return snrPer;
}

void
InterferenceHelper::EraseEvents (void) 
{  
  m_niChanges.clear ();
  m_rxing = false;
  m_firstPower = 0.0;
}
InterferenceHelper::NiChanges::iterator
InterferenceHelper::GetPosition (Time moment)
{
  return std::upper_bound (m_niChanges.begin (), m_niChanges.end (), NiChange (moment, 0));

}
void
InterferenceHelper::AddNiChangeEvent (NiChange change)
{
  m_niChanges.insert (GetPosition (change.GetTime ()), change);
}
void
InterferenceHelper::NotifyRxStart ()
{
  m_rxing = true;
}
void
InterferenceHelper::NotifyRxEnd ()
{
  m_rxing = false;
}
} // namespace ns3
