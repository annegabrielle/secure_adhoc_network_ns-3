/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
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
 */

#include "ns3/core-module.h"
#include "ns3/batman-helper.h"
#include "ns3/simulator-module.h"
#include "ns3/node-module.h"
#include "ns3/common-module.h"
#include "ns3/dsdv-helper.h"
#include "ns3/helper-module.h"
#include "ns3/ipv4-global-routing-helper.h"
#include "ns3/flow-monitor-module.h"
#include "ns3/mobility-module.h"
#include "ns3/olsr-helper.h"
#include "ns3/stats-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("AnnesTest");

class BatmanSimulation
{

public:
	BatmanSimulation ();
	void RunSimulation (bool batman,
						uint32_t nWifis,
            			uint32_t nSinks,
            			double send,
            			double stop,
            			double pause,
            			std::string format,
            			std::string experiment,
            			std::string strategy,
            			std::string input,
            			std::string runID );

private:
	bool m_batman;
	uint32_t m_CbrCources;
	uint32_t m_CbrSinks;
	double m_send;
	double m_stop;
	double m_pause;
	Ptr<CounterCalculator<> > m_calc;

  NodeContainer nodes;
  NetDeviceContainer devices;
  Ipv4InterfaceContainer interfaces;

private:
  void CreateNodes ();
  void CreateDevices ();
  void InstallInternetStack ();
  void InstallApplications ();
  void SetupMobility ();
  Ptr<Socket> SetupPacketReceive (Ipv4Address addr, Ptr <Node> node);
  void ReceivePacket (Ptr <Socket> socket);
public:
  void SetCounter(Ptr<CounterCalculator<> > calc);
};

void
CourseChange (std::string context, Ptr<const MobilityModel> model)
{
//  Vector position = model->GetPosition ();
//  NS_LOG_UNCOND (context << " " << Simulator::Now().GetSeconds() << "s x = " << position.x << ", y = " << position.y);
}

//std::string CSVtransmitted = "transmitted.csv";
uint64_t packetCount = 0, packetsReceived = 0;
void
TxTrace (std::string context, Ptr<const Packet> p)
{
	packetCount++;
//	std::cout << "SENT " << p->GetUid() <<  "," << Simulator::Now().GetSeconds() << "\n";
//	NS_LOG_DEBUG("Sum = " << packetCount);
//	std::ofstream out (CSVtransmitted.c_str (), std::ios::app);
//	out << p->GetUid() <<  "," << Simulator::Now().GetSeconds() << std::endl;
//	out.close ();

}

template <class T> inline std::string to_string (const T& t)
{
	std::stringstream ss;
	ss << t;
	return ss.str();
}

std::ostringstream oss, oss2, oss_tx;

int
main (int argc, char *argv[])
{
	BatmanSimulation first;

	bool batman = true;
	uint32_t nSources = 10;
	uint32_t nSinks = 10;
	double start = 0.0;
	double stop = 100.0;
	double pause = 0.0;
	uint32_t seed = 1234;

	std::string format("db");
	std::string experiment("anne-test");
	std::string strategy("anne-default");
	std::string input;
	std::string runID;

	CommandLine cmd;
	cmd.AddValue ("batman", "Run BATMAN[Default:true]", batman);
	cmd.AddValue ("sources", "Number of wifi source [Default:10]", nSources);
	cmd.AddValue ("start", "Number of wifi source [Default:0]", start);
	cmd.AddValue ("stop", "Number of wifi source [Default:10]", stop);
	cmd.AddValue ("pause", "Number of wifi source [Default:0.0]", pause);
	cmd.AddValue("format", "Format to use for data output.", format);
	cmd.AddValue ("run", "Identifier for run.", runID);
	cmd.AddValue ("seed", "Identifier for run.", seed);
	cmd.Parse (argc, argv);

	Config::SetDefault ("ns3::OnOffApplication::PacketSize", StringValue ("64"));
	Config::SetDefault ("ns3::OnOffApplication::DataRate", StringValue ("256Bps"));

	first = BatmanSimulation ();
	first.RunSimulation(batman, nSources, nSinks, start, stop, pause, format, experiment, strategy, input, runID);

	Config::Connect (oss.str (), MakeCallback (&CourseChange));
	Config::Connect (oss2.str (), MakeCallback (&CourseChange));
	Config::Connect (oss_tx.str (), MakeCallback(&TxTrace));

	// 8. Install FlowMonitor on all nodes
	FlowMonitorHelper flowmon;
	Ptr<FlowMonitor> monitor = flowmon.InstallAll();

	/* Stats and Data Collection */
	DataCollector data;
	data.DescribeRun(experiment, strategy, input, runID);

	/* Set seed valu*/
	SeedManager::SetSeed(seed);
	data.AddMetadata("seed", seed);

	Ptr<PacketCounterCalculator> totalTx = CreateObject<PacketCounterCalculator>();
	totalTx->SetKey("tx");
	Config::Connect (oss_tx.str (), MakeCallback(&PacketCounterCalculator::PacketUpdate, totalTx));
	data.AddDataCalculator(totalTx);

	Ptr<CounterCalculator<> > appRx = CreateObject<CounterCalculator<> >();
	appRx->SetKey("rx");
	first.SetCounter(appRx);
	data.AddDataCalculator(appRx);

	Simulator::Stop (Seconds(stop));
	Simulator::Run ();

	monitor->CheckForLostPackets ();
	Ptr<Ipv4FlowClassifier> classifier = DynamicCast<Ipv4FlowClassifier> (flowmon.GetClassifier ());
	std::map<FlowId, FlowMonitor::FlowStats> stats = monitor->GetFlowStats ();
	uint64_t totalPacketsTx = 0, totalPacketsRx = 0, numberOfFlows = 0;
	Time totalDelay = Seconds(0.0);
	for (std::map<FlowId, FlowMonitor::FlowStats>::const_iterator i = stats.begin (); i != stats.end (); ++i)
	{
	  Ipv4FlowClassifier::FiveTuple t = classifier->FindFlow (i->first);

	  if (t.destinationAddress != "10.0.0.255")
	  {
	//		std::cout << "Flow " << i->first  << " (" << t.sourceAddress << " -> " << t.destinationAddress << ")\n";
	//		std::cout << "  Tx Bytes:   " << i->second.txBytes << "\n";
	//		std::cout << "  Rx Bytes:   " << i->second.rxBytes << "\n";
	//		std::cout << "  Tx Packets:   " << i->second.txPackets << "\n";
	//		std::cout << "  Rx Packets:   " << i->second.rxPackets << "\n";
	//		std::cout << "  Packets lost:   " << i->second.lostPackets << "\n";
	//		std::cout << "  Throughput: " << i->second.rxBytes * 8.0 / 10.0 / 1024  << " Kbps\n";
		totalPacketsTx = totalPacketsTx + i->second.txPackets;
		totalPacketsRx = totalPacketsRx + i->second.rxPackets;
		numberOfFlows += 1;
		totalDelay = totalDelay + i->second.delaySum;
	//		std::cout << "  Sum Delay:   " << i->second.delaySum.GetSeconds() << "s\n\n";
	  }
	}

	std::cout << "Number 0f flows:   " << numberOfFlows << "\n";
	std::cout << "Flow monitor total # Packets Tx:   " << totalPacketsTx << "\n";
	std::cout << "Flow monitor total # Packets Rx:   " << totalPacketsRx << "\n\n";

	std::cout << "Flow monitor Avg Delay:   " << totalDelay.GetSeconds() << "/" << totalPacketsRx << " = " << (totalDelay.GetSeconds())/totalPacketsRx << "\n\n";

	std::cout << "Total # Packets Tx:   " << packetCount << "\n";
	std::cout << "Total # Packets Rx:   " << packetsReceived << "\n";

	std::cout << "PDR:   " << (double)packetsReceived/packetCount << "\n\n";

	std::cout << "Using seed: " << seed << "\n";

	std::cout << "\n----------------------------------------------------------------\n\n";

	Simulator::Destroy ();

	// Pick an output writer based in the requested format.
	Ptr<DataOutputInterface> output = 0;
	if (format == "omnet") {
		NS_LOG_INFO("Creating omnet formatted data output.");
		output = CreateObject<OmnetDataOutput>();
	} else if (format == "db") {
		#ifdef STATS_HAS_SQLITE3
			NS_LOG_INFO("Creating sqlite formatted data output.");
			output = CreateObject<SqliteDataOutput>();
		#endif
	} else {
		NS_LOG_ERROR("Unknown output format " << format);
	}

	// Finally, have that writer interrogate the DataCollector and save
	// the results.
	if (output != 0)
		output->Output(data);

	return 0;
}

/*
The time from sent by Application until received in the final node includes
the time to discover the route.  If you consider just the time when the
packet is transmitted by the NetDevice then it does not include the route
discovery time.

If you mean delay experienced at application layer, you need to trace
application packet transmission (Tx trace event in OnOffApplication).
You could also measure delay at IP layer, for when IP sends a packet to the
netdevice (Tx trace event in Ipv4L3Protocol).  This time does _not_ include
the route discovery time.  The Flow Monitor module (in
src/contrib/flow-monitor) currently uses this
 */

BatmanSimulation::BatmanSimulation()
{
}

std::string CSVreceived = "received.csv";

void
BatmanSimulation::SetCounter(Ptr<CounterCalculator<> > calc)
{
	m_calc = calc;
}

void
BatmanSimulation::ReceivePacket (Ptr <Socket> socket)
{
  Ptr <Packet> packet;
  while (packet = socket->Recv ())
    {
      packetsReceived += 1;
      m_calc->Update();
//      std::cout << "RECEIVED " << packet->GetUid() << "," << Simulator::Now().GetSeconds() << "\n";

//	  std::ofstream out (CSVreceived.c_str (), std::ios::app);
//	  out << packet->GetUid() <<  "," << Simulator::Now().GetSeconds() << std::endl;
//	  out.close ();
    }
}

Ptr <Socket>
BatmanSimulation::SetupPacketReceive (Ipv4Address addr, Ptr <Node> node)
{
  TypeId tid = TypeId::LookupByName ("ns3::UdpSocketFactory");
  Ptr <Socket> sink = Socket::CreateSocket (node, tid);
  InetSocketAddress local = InetSocketAddress (addr, 9);
  sink->Bind (local);

  sink->SetRecvCallback (MakeCallback ( &BatmanSimulation::ReceivePacket, this));
  return sink;
}

void
BatmanSimulation::RunSimulation(bool batman, uint32_t sources, uint32_t sinks, double send, double stop, double pause, std::string format, std::string experiment,
		std::string strategy, std::string input, std::string runID)
{
	m_batman = batman;
	m_CbrCources = sources;
	m_CbrSinks = sinks;
	m_send = send;
	m_stop = stop;
	m_pause = pause;

//	std::cout << "\n----------------------------------------------------------------\n\n";

	std::cout << "Running simulation for " << stop << " seconds with pause time = " << pause << "... ";

	CreateNodes ();
	CreateDevices ();
	SetupMobility ();
	InstallInternetStack ();
	InstallApplications ();
}

void
BatmanSimulation::CreateNodes ()
{
	  std::cout << "Creating " << (unsigned) m_CbrCources << " nodes. \n";
	  nodes.Create (m_CbrCources);

	  oss << "/NodeList/" << nodes.Get (m_CbrCources - 1)->GetId () << "/$ns3::MobilityModel/CourseChange";
	  oss2 << "/NodeList/" << nodes.Get (0)->GetId () << "/$ns3::MobilityModel/CourseChange";

}

void
BatmanSimulation::CreateDevices ()
{
//	  CsmaHelper csma;
//	  csma.SetChannelAttribute ("DataRate", StringValue ("100Mbps"));
//	  csma.SetChannelAttribute ("Delay", TimeValue (NanoSeconds (6560)));
//
//	  devices = csma.Install (nodes);

	  NqosWifiMacHelper wifiMac = NqosWifiMacHelper::Default ();
	  wifiMac.SetType ("ns3::AdhocWifiMac");
	  YansWifiPhyHelper wifiPhy = YansWifiPhyHelper::Default ();
	  YansWifiChannelHelper wifiChannel;
	  wifiChannel.SetPropagationDelay ("ns3::ConstantSpeedPropagationDelayModel");
	  wifiChannel.AddPropagationLoss ("ns3::FriisPropagationLossModel");
	  wifiPhy.SetChannel (wifiChannel.Create ());

	  WifiHelper wifi;
	  wifi.SetStandard (WIFI_PHY_STANDARD_80211b);
	  wifi.SetRemoteStationManager ("ns3::ConstantRateWifiManager", "DataMode", StringValue ("DsssRate11Mbps"), "ControlMode", StringValue ("DsssRate11Mbps"));
	  devices = wifi.Install (wifiPhy, wifiMac, nodes);
	  //  wifiPhy.EnablePcapAll ("annetest");
}

void
BatmanSimulation::InstallInternetStack ()
{
	if (m_batman)
	{
		BatmanHelper batman;
		InternetStackHelper stack;
		stack.SetRoutingHelper (batman);
		stack.Install (nodes);

		std::cout << "Running BATMAN protocol\n";
	}
	else
	{
		DsdvHelper dsdv;
		dsdv.Set ("PeriodicUpdateInterval", TimeValue (Seconds (15)));
		dsdv.Set ("SettlingTime", TimeValue (Seconds (6)));
		InternetStackHelper stack;
		stack.SetRoutingHelper (dsdv);
		stack.Install (nodes);

		std::cout << "Running DSDV protocol\n";

//		OlsrHelper olsr;
//		InternetStackHelper stack;
//		stack.SetRoutingHelper (olsr);
//		stack.Install (nodes);

//		AodvHelper aodv;
//		InternetStackHelper stack;
//		stack.SetRoutingHelper (aodv);
//		stack.Install (nodes);
	}

	  Ipv4AddressHelper address;
	  address.SetBase ("10.0.0.0", "255.255.255.0");

	  interfaces = address.Assign (devices);
}

void
BatmanSimulation::SetupMobility ()
{
//	  MobilityHelper mobility;
//	  mobility.SetPositionAllocator ("ns3::GridPositionAllocator",
//	                                 "MinX", DoubleValue (0.0),
//	                                 "MinY", DoubleValue (0.0),
//	                                 "DeltaX", DoubleValue (5.0),
//	                                 "DeltaY", DoubleValue (10.0),
//	                                 "GridWidth", UintegerValue (3),
//	                                 "LayoutType", StringValue ("RowFirst"));
//
//	  mobility.SetMobilityModel ("ns3::RandomWalk2dMobilityModel",
//	                             "Bounds", RectangleValue (Rectangle (-50, 50, -50, 50)));
//	  mobility.Install (nodes);

	  MobilityHelper mobility;
	  ObjectFactory pos;
	  pos.SetTypeId ("ns3::RandomRectanglePositionAllocator");
	  pos.Set ("X", RandomVariableValue (UniformVariable (0, 1500)));
	  pos.Set ("Y", RandomVariableValue (UniformVariable (0, 300)));

	  Ptr <PositionAllocator> taPositionAlloc = pos.Create ()->GetObject <PositionAllocator> ();
	  mobility.SetMobilityModel ("ns3::RandomWaypointMobilityModel",
			  	  	  	  	  	  "Speed", RandomVariableValue (UniformVariable (0, 20)),
			  	  	  	  	  	  "Pause", RandomVariableValue (ConstantVariable (m_pause)),
			  	  	  	  	  	  "PositionAllocator", PointerValue (taPositionAlloc) );
	  mobility.SetPositionAllocator (taPositionAlloc);
	  mobility.Install (nodes);
}

void
BatmanSimulation::InstallApplications ()
{
	  for (uint32_t i = 0; i <= m_CbrSinks - 1; i++ )
	    {
	      Ptr<Node> node = NodeList::GetNode (i);
	      Ipv4Address nodeAddress = node->GetObject<Ipv4> ()->GetAddress (1, 0).GetLocal ();
	      Ptr<Socket> sink = SetupPacketReceive (nodeAddress, node);
	    }

	  uint32_t node = 0;
	  for (uint32_t clientNode = 0; clientNode <= ((m_CbrCources - 1)/2); clientNode++ )
	  {
		  	  node = (m_CbrCources/2)+clientNode;
//		  		std::cout << clientNode <<" sending to " << node <<"\n";
	          OnOffHelper onoff1 ("ns3::UdpSocketFactory", Address (InetSocketAddress (interfaces.GetAddress (node), 9)));
	          onoff1.SetAttribute ("OnTime", RandomVariableValue (ConstantVariable (1)));
	          onoff1.SetAttribute ("OffTime", RandomVariableValue (ConstantVariable (0)));

			  ApplicationContainer apps1 = onoff1.Install (nodes.Get (clientNode));
			  UniformVariable var;
			  apps1.Start (Seconds (var.GetValue (m_send, m_send + 1)));
			  apps1.Stop (Seconds (m_stop));
	    }

	  node = (m_CbrCources/2)-1;
	  for (uint32_t clientNode = ((m_CbrCources)/2); clientNode <= m_CbrCources-1; clientNode++ )
	  {
//		  		std::cout << clientNode <<" sending to " << node <<"\n";
	          OnOffHelper onoff1 ("ns3::UdpSocketFactory", Address (InetSocketAddress (interfaces.GetAddress (node), 9)));
	          onoff1.SetAttribute ("OnTime", RandomVariableValue (ConstantVariable (1)));
	          onoff1.SetAttribute ("OffTime", RandomVariableValue (ConstantVariable (0)));

			  ApplicationContainer apps1 = onoff1.Install (nodes.Get (clientNode));
			  UniformVariable var;
			  apps1.Start (Seconds (var.GetValue (m_send, m_send + 1)));
			  apps1.Stop (Seconds (m_stop));
			  node = node - 1;
	    }

//	  for (uint32_t clientNode = 0; clientNode <= m_CbrCources - 1; clientNode++ )
//	    {
//	      for (uint32_t j = 0; j <= m_CbrSinks - 1; j++ )
//	        {
//	          OnOffHelper onoff1 ("ns3::UdpSocketFactory", Address (InetSocketAddress (interfaces.GetAddress (j), 9)));
//	          onoff1.SetAttribute ("OnTime", RandomVariableValue (ConstantVariable (1)));
//	          onoff1.SetAttribute ("OffTime", RandomVariableValue (ConstantVariable (0)));
//
//	          if (j != clientNode)
//	            {
//	              ApplicationContainer apps1 = onoff1.Install (nodes.Get (clientNode));
//	              UniformVariable var;
//	              apps1.Start (Seconds (var.GetValue (m_send, m_send + 1)));
//	              apps1.Stop (Seconds (m_stop));
//	            }
//	        }
//	    }

//	  // Manual
//		UniformVariable var;
//		OnOffHelper onoff0 ("ns3::UdpSocketFactory", Address (InetSocketAddress (interfaces.GetAddress (0), 9)));
//		onoff0.SetAttribute ("OnTime", RandomVariableValue (ConstantVariable (1)));
//		onoff0.SetAttribute ("OffTime", RandomVariableValue (ConstantVariable (0)));
//		ApplicationContainer apps0 = onoff0.Install (nodes.Get (5));
//		apps0.Start (Seconds (var.GetValue (m_send, m_send + 1)));
//		apps0.Stop (Seconds (m_stop));
//
//		OnOffHelper onoff1 ("ns3::UdpSocketFactory", Address (InetSocketAddress (interfaces.GetAddress (1), 9)));
//		onoff1.SetAttribute ("OnTime", RandomVariableValue (ConstantVariable (1)));
//		onoff1.SetAttribute ("OffTime", RandomVariableValue (ConstantVariable (0)));
//		ApplicationContainer apps1 = onoff1.Install (nodes.Get (6));
//		apps1.Start (Seconds (var.GetValue (m_send, m_send + 1)));
//		apps1.Stop (Seconds (m_stop));
//
//		OnOffHelper onoff2 ("ns3::UdpSocketFactory", Address (InetSocketAddress (interfaces.GetAddress (2), 9)));
//		onoff2.SetAttribute ("OnTime", RandomVariableValue (ConstantVariable (1)));
//		onoff2.SetAttribute ("OffTime", RandomVariableValue (ConstantVariable (0)));
//		ApplicationContainer apps2 = onoff2.Install (nodes.Get (7));
//		apps2.Start (Seconds (var.GetValue (m_send, m_send + 1)));
//		apps2.Stop (Seconds (m_stop));
//
//		OnOffHelper onoff3 ("ns3::UdpSocketFactory", Address (InetSocketAddress (interfaces.GetAddress (3), 9)));
//		onoff3.SetAttribute ("OnTime", RandomVariableValue (ConstantVariable (1)));
//		onoff3.SetAttribute ("OffTime", RandomVariableValue (ConstantVariable (0)));
//		ApplicationContainer apps3 = onoff3.Install (nodes.Get (8));
//		apps3.Start (Seconds (var.GetValue (m_send, m_send + 1)));
//		apps3.Stop (Seconds (m_stop));
//
//		OnOffHelper onoff4 ("ns3::UdpSocketFactory", Address (InetSocketAddress (interfaces.GetAddress (4), 9)));
//		onoff4.SetAttribute ("OnTime", RandomVariableValue (ConstantVariable (1)));
//		onoff4.SetAttribute ("OffTime", RandomVariableValue (ConstantVariable (0)));
//		ApplicationContainer apps4 = onoff4.Install (nodes.Get (9));
//		apps4.Start (Seconds (var.GetValue (m_send, m_send + 1)));
//		apps4.Stop (Seconds (m_stop));
//
//		OnOffHelper onoff5 ("ns3::UdpSocketFactory", Address (InetSocketAddress (interfaces.GetAddress (5), 9)));
//		onoff5.SetAttribute ("OnTime", RandomVariableValue (ConstantVariable (1)));
//		onoff5.SetAttribute ("OffTime", RandomVariableValue (ConstantVariable (0)));
//		ApplicationContainer apps5 = onoff5.Install (nodes.Get (4));
//		apps5.Start (Seconds (var.GetValue (m_send, m_send + 1)));
//		apps5.Stop (Seconds (m_stop));
//
//		OnOffHelper onoff6 ("ns3::UdpSocketFactory", Address (InetSocketAddress (interfaces.GetAddress (6), 9)));
//		onoff6.SetAttribute ("OnTime", RandomVariableValue (ConstantVariable (1)));
//		onoff6.SetAttribute ("OffTime", RandomVariableValue (ConstantVariable (0)));
//		ApplicationContainer apps6 = onoff6.Install (nodes.Get (3));
//		apps6.Start (Seconds (var.GetValue (m_send, m_send + 1)));
//		apps6.Stop (Seconds (m_stop));
//
//		OnOffHelper onoff7 ("ns3::UdpSocketFactory", Address (InetSocketAddress (interfaces.GetAddress (7), 9)));
//		onoff7.SetAttribute ("OnTime", RandomVariableValue (ConstantVariable (1)));
//		onoff7.SetAttribute ("OffTime", RandomVariableValue (ConstantVariable (0)));
//		ApplicationContainer apps7 = onoff7.Install (nodes.Get (1));
//		apps7.Start (Seconds (var.GetValue (m_send, m_send + 1)));
//		apps7.Stop (Seconds (m_stop));
//
//		OnOffHelper onoff8 ("ns3::UdpSocketFactory", Address (InetSocketAddress (interfaces.GetAddress (8), 9)));
//		onoff8.SetAttribute ("OnTime", RandomVariableValue (ConstantVariable (1)));
//		onoff8.SetAttribute ("OffTime", RandomVariableValue (ConstantVariable (0)));
//		ApplicationContainer apps8 = onoff8.Install (nodes.Get (2));
//		apps8.Start (Seconds (var.GetValue (m_send, m_send + 1)));
//		apps8.Stop (Seconds (m_stop));
//
//		OnOffHelper onoff9 ("ns3::UdpSocketFactory", Address (InetSocketAddress (interfaces.GetAddress (9), 9)));
//		onoff9.SetAttribute ("OnTime", RandomVariableValue (ConstantVariable (1)));
//		onoff9.SetAttribute ("OffTime", RandomVariableValue (ConstantVariable (0)));
//		ApplicationContainer apps9 = onoff9.Install (nodes.Get (0));
//		apps9.Start (Seconds (var.GetValue (m_send, m_send + 1)));
//		apps9.Stop (Seconds (m_stop));

	  oss_tx << "/NodeList/*/ApplicationList/*/$ns3::OnOffApplication/Tx";
}
