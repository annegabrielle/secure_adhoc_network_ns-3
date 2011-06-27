#include "ns3/core-module.h"
#include "ns3/batman-helper.h"
#include "ns3/secure-batman-helper.h"
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
#include "ns3/onoff-application.h"
#include "ns3/wifi-mac.h"
#include "ns3/batman-routing-protocol.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("main-scenario");

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
            			uint32_t runID );

private:
	bool m_batman;
	uint32_t m_CbrCources;
	uint32_t m_CbrSinks;
	double m_send;
	double m_stop;
	double m_pause;
	Ptr<CounterCalculator<> > m_calc;
	Ptr<CounterCalculator<> > m_routingCalc;
	Ptr<TimeMinMaxAvgTotalCalculator> m_onoffDelay;

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
	void SetRoutingPacketCounter(Ptr<CounterCalculator<> > calc);
	void SetOnoffDelayTracker(Ptr<TimeMinMaxAvgTotalCalculator> onoffDelay);
	void SetMacDelayTracker(Ptr<TimeMinMaxAvgTotalCalculator> macDelay);
};

/* Variables used for printing results to terminal */
uint64_t packetCount = 0, packetsReceived = 0;
Time t_delay = Seconds(0.0), t2_delay = Seconds(0.0);
uint64_t n = 0, n2 = 0, mactx=0;
uint64_t rTx = 0, rRx = 0, rReTx = 0;
uint64_t rDTx = 0, rDRx = 0;
Ptr<TimeMinMaxAvgTotalCalculator> m_macDelay;

template <class T> inline std::string to_string (const T& t)
{
	std::stringstream ss;
	ss << t;
	return ss.str();
}

BatmanSimulation::BatmanSimulation()
{
}

/*
 * Sinks connected
 * to various tracesources
 */
void
OnoffTxTrace (std::string context, Ptr<const Packet> p)
{
	packetCount++;
}
void
MacTxTrace (std::string context, Ptr<const Packet> p)
{
	mactx++;
}
/* Get timestamp on arrival from mac layer and record packet delay */
void
MacRxTrace (std::string context, Ptr<const Packet> packet)
{
	MacTimestampTag macTimestamp;
	if (packet->FindFirstMatchingByteTag(macTimestamp))
	{
		Time tx = macTimestamp.GetTimestamp();
		t2_delay = t2_delay + (Simulator::Now() - tx);
		n2++;
		if (m_macDelay != 0)
		{
			m_macDelay->Update((Simulator::Now() - tx));
		}
	}
}
void
DsdvPacketTxTrace (std::string context, Ptr<const Packet> p)
{
	rDTx++;
}
void
DsdvPacketRxTrace (std::string context, Ptr<const Packet> p)
{
	rDRx++;
}
void
BatmanPacketTxTrace (std::string context, Ptr<const Packet> p)
{
	rTx++;
}
void
BatmanPacketReTxTrace (std::string context, Ptr<const Packet> p)
{
	rReTx++;
}
void
BatmanPacketRxTrace (std::string context, Ptr<const Packet> p)
{
	rRx++;
}
void
BatmanSimulation::SetCounter(Ptr<CounterCalculator<> > calc)
{
	m_calc = calc;
}
void
BatmanSimulation::SetRoutingPacketCounter(Ptr<CounterCalculator<> > calc)
{
	m_routingCalc = calc;
}
void
BatmanSimulation::SetOnoffDelayTracker(Ptr<TimeMinMaxAvgTotalCalculator> onoffDelay)
{
  m_onoffDelay = onoffDelay;
}
void
BatmanSimulation::SetMacDelayTracker(Ptr<TimeMinMaxAvgTotalCalculator> macDelay)
{
  m_macDelay = macDelay;
}
/* Get timestamp on UDP packet on arrival and record the packet delay */
void
BatmanSimulation::ReceivePacket (Ptr <Socket> socket)
{
	Ptr <Packet> packet;
	while (packet = socket->Recv ())
	{
		TimestampTag timestamp;
		if (packet->FindFirstMatchingByteTag(timestamp))
		{
			Time tx = timestamp.GetTimestamp();
			t_delay = t_delay + (Simulator::Now() - tx);
			n++;
			if (m_onoffDelay != 0)
			{
				m_onoffDelay->Update((Simulator::Now() - tx));
			}
		}
		packetsReceived += 1;
		m_calc->Update();
    }
}

/* Setup sink to receive packets from port 9 */
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

/* Configure the simulation */
void
BatmanSimulation::RunSimulation(bool batman, uint32_t sources, uint32_t sinks, double send, double stop, double pause, std::string format, std::string experiment,
		std::string strategy, std::string input, uint32_t runID)
{
		m_batman = batman;
		m_CbrCources = sources;
		m_CbrSinks = sinks;
		m_send = send;
		m_stop = stop;
		m_pause = pause;

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
}

void
BatmanSimulation::CreateDevices ()
{
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
//	  wifiPhy.EnablePcapAll ("main-test");
}

void
BatmanSimulation::InstallInternetStack ()
{
	/* Install routing protocol */
	if (m_batman)
	{
		/* Run the BATMAN protocol   */
		BatmanHelper batman;
		InternetStackHelper stack;
		stack.SetRoutingHelper (batman);
		stack.Install (nodes);

		/* Run the Secure BATMAN protocl */
//		SecureBatmanHelper batman;
//		InternetStackHelper stack;
//		stack.SetRoutingHelper (batman);
//		stack.Install (nodes);

		std::cout << "Running BATMAN protocol\n";
	}
	else
	{
		/* Run the DSDV protocol */
		DsdvHelper dsdv;
		dsdv.Set ("PeriodicUpdateInterval", TimeValue (Seconds (15)));
		dsdv.Set ("SettlingTime", TimeValue (Seconds (6)));
		dsdv.Set("EnableBuffering", BooleanValue (false));
		InternetStackHelper stack;
		stack.SetRoutingHelper (dsdv);
		stack.Install (nodes);

		std::cout << "Running DSDV protocol\n";
	}

	  /* Assign addresses to the nodes */
	  Ipv4AddressHelper address;
	  address.SetBase ("10.0.0.0", "255.255.255.0");
	  interfaces = address.Assign (devices);
}

void
BatmanSimulation::SetupMobility ()
{
		/* Install mobility on the nodes */
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
		/* Install traffic sources and sink */
		for (uint32_t i = 0; i <= m_CbrCources - 1; i++ )
		{
			Ptr<Socket> sink = SetupPacketReceive (interfaces.GetAddress (i), nodes.Get (i));
		}

		uint32_t node = 0;
		OnOffHelper onoff1 ("ns3::UdpSocketFactory", Address ());
		onoff1.SetAttribute ("OnTime", RandomVariableValue (ConstantVariable (1)));
		onoff1.SetAttribute ("OffTime", RandomVariableValue (ConstantVariable (0)));
		for (uint32_t clientNode = 0; clientNode <= ((m_CbrCources - 1)/2); clientNode++ )
		{
			node = (m_CbrCources/2)+clientNode;
			AddressValue remoteAddress (InetSocketAddress (interfaces.GetAddress (node), 9));
			onoff1.SetAttribute ("Remote", remoteAddress);
			ApplicationContainer apps1 = onoff1.Install (nodes.Get (clientNode));
			UniformVariable var;
			apps1.Start (Seconds (var.GetValue (m_send, m_send + 10)));
			apps1.Stop (Seconds (m_stop));
		}
		node = (m_CbrCources/2)-1;
		for (uint32_t clientNode = ((m_CbrCources)/2); clientNode <= m_CbrCources-1; clientNode++ )
		{
			AddressValue remoteAddress (InetSocketAddress (interfaces.GetAddress (node), 9));
			onoff1.SetAttribute ("Remote", remoteAddress);
			ApplicationContainer apps1 = onoff1.Install (nodes.Get (clientNode));
			UniformVariable var;
			apps1.Start (Seconds (var.GetValue (m_send, m_send + 10)));
			apps1.Stop (Seconds (m_stop));
			node = node - 1;
		}
}

void printTime()
{
	NS_LOG_INFO("Time now: " << Simulator::Now());
}

int
main (int argc, char *argv[])
{
		BatmanSimulation first;

		bool batman = true;
		uint32_t nSources = 10;
		uint32_t nSinks = 10;
		double start = 30.0;
		double stop = 930.0;
		double pause = 0.0;
		uint32_t seed = 1234;
		uint32_t runID = 1;

		std::string format("db");
		std::string experiment("main-scenario");
		std::string strategy("main-default");
		std::string input;
		std::string runid;

		CommandLine cmd;
		cmd.AddValue ("batman", "Run BATMAN[Default:true]", batman);
		cmd.AddValue ("sources", "Number of wifi source [Default:10]", nSources);
		cmd.AddValue ("start", "Simulation start [Default:30]", start);
		cmd.AddValue ("stop", "Simulation stop [Default:930]", stop);
		cmd.AddValue ("pause", "Pause time [Default:0.0]", pause);
		cmd.AddValue("format", "Format to use for data output.", format);
		cmd.AddValue ("run", "Identifier for run.", runID);
		cmd.AddValue ("seed", "Set seed.", seed);
		cmd.Parse (argc, argv);

		/* Set onoff transmission data rate and packet size */
		Config::SetDefault ("ns3::OnOffApplication::PacketSize", StringValue ("64"));
		Config::SetDefault ("ns3::OnOffApplication::DataRate", StringValue ("256Bps"));

		/* Configure the simulation */
		first = BatmanSimulation ();
		first.RunSimulation(batman, nSources, nSinks, start, stop, pause, format, experiment, strategy, input, runID);

		/* Trace packet sent by OnOff application. UDP packets from source to destination. (just to show resutls in terminal) */
		Config::Connect ("/NodeList/*/ApplicationList/*/$ns3::OnOffApplication/Tx", MakeCallback (&OnoffTxTrace));

		/* Trace packets sent to and from MAC layer */
		Config::Connect ("/NodeList/*/DeviceList/*/Mac/MacTx", MakeCallback (&MacTxTrace));
		Config::Connect ("/NodeList/*/DeviceList/*/Mac/MacRx", MakeCallback (&MacRxTrace));

		/* Trace BATMAN routing packets */
		Config::Connect ("/NodeList/*/$ns3::securebatman::RoutingProtocol/Rx", MakeCallback (&BatmanPacketRxTrace));
		Config::Connect ("/NodeList/*/$ns3::securebatman::RoutingProtocol/Tx", MakeCallback (&BatmanPacketTxTrace));

		/* Trace DSDV routing packets */
		Config::Connect ("/NodeList/*/$ns3::dsdv::RoutingProtocol/Rx", MakeCallback (&DsdvPacketRxTrace));
		Config::Connect ("/NodeList/*/$ns3::dsdv::RoutingProtocol/Tx", MakeCallback (&DsdvPacketTxTrace));

		/* Install FlowMonitor on all nodes */
		FlowMonitorHelper flowmon;
		Ptr<FlowMonitor> monitor = flowmon.InstallAll();

		/* Stats and Data Collection */
		DataCollector data;
		data.DescribeRun(experiment, strategy, input, to_string(pause));

		/* Set seed and run value */
		//	SeedManager::SetSeed(seed);
		//	SeedManager::SetRun(runID);
		data.AddMetadata("seed", seed);
		data.AddMetadata("runid", runID);

		/* Datacalculator for # transmitted packets from Onoff-application */
		Ptr<PacketCounterCalculator> totalTx = CreateObject<PacketCounterCalculator>();
		totalTx->SetKey("onoffTx");
		Config::Connect ("/NodeList/*/ApplicationList/*/$ns3::OnOffApplication/Tx", MakeCallback(&PacketCounterCalculator::PacketUpdate, totalTx));
		data.AddDataCalculator(totalTx);

		/* Datacalculator for # received packets from Onoff-application */
		Ptr<CounterCalculator<> > appRx = CreateObject<CounterCalculator<> >();
		appRx->SetKey("onoffRx");
		first.SetCounter(appRx);
		data.AddDataCalculator(appRx);

		/* Datacalculator for packetdelay to Onoff packets */
		Ptr<TimeMinMaxAvgTotalCalculator> onoff_delay = CreateObject<TimeMinMaxAvgTotalCalculator>();
		onoff_delay->SetKey("onoffDelay");
		first.SetOnoffDelayTracker(onoff_delay);
		data.AddDataCalculator(onoff_delay);

		/* Datacalculator for # transmitted packets from Mac packets */
		Ptr<TimeMinMaxAvgTotalCalculator> mac_delay = CreateObject<TimeMinMaxAvgTotalCalculator>();
		mac_delay->SetKey("macDelay");
		first.SetMacDelayTracker(mac_delay);
		data.AddDataCalculator(mac_delay);

		/* Datacalculator for # transmitted BATMAN packets */
		Ptr<PacketSizeMinMaxAvgTotalCalculator> batmanTx = CreateObject<PacketSizeMinMaxAvgTotalCalculator>();
		batmanTx->SetKey("batmanTx");
		Config::Connect ("/NodeList/*/$ns3::securebatman::RoutingProtocol/Tx", MakeCallback(&PacketSizeMinMaxAvgTotalCalculator::PacketUpdate, batmanTx));
		data.AddDataCalculator(batmanTx);

		/* Datacalculator for # received BATMAN packets */
		Ptr<PacketCounterCalculator> batmanRx = CreateObject<PacketCounterCalculator>();
		batmanRx->SetKey("batmanRx");
		Config::Connect ("/NodeList/*/$ns3::securebatman::RoutingProtocol/Rx", MakeCallback(&PacketCounterCalculator::PacketUpdate, batmanRx));
		data.AddDataCalculator(batmanRx);

		/* Datacalculator for # transmitted DSDV packets */
		Ptr<PacketSizeMinMaxAvgTotalCalculator> dsdvTx = CreateObject<PacketSizeMinMaxAvgTotalCalculator>();
		dsdvTx->SetKey("dsdvTx");
		Config::Connect ("/NodeList/*/$ns3::dsdv::RoutingProtocol/Tx", MakeCallback(&PacketSizeMinMaxAvgTotalCalculator::PacketUpdate, dsdvTx));
		data.AddDataCalculator(dsdvTx);

		/* Datacalculator for # received DSDV packets */
		Ptr<PacketCounterCalculator> dsdvRx = CreateObject<PacketCounterCalculator>();
		dsdvRx->SetKey("dsdvRx");
		Config::Connect ("/NodeList/*/$ns3::dsdv::RoutingProtocol/Rx", MakeCallback(&PacketCounterCalculator::PacketUpdate, dsdvRx));
		data.AddDataCalculator(dsdvRx);

		for (uint32_t i = 200; i < 900; i+=200)
		{
			Simulator::Schedule(Seconds(i),	&printTime);
		}

		/* Start the Simulator */
		Simulator::Stop (Seconds(stop));
		Simulator::Run ();

		monitor->CheckForLostPackets ();
		Ptr<Ipv4FlowClassifier> classifier = DynamicCast<Ipv4FlowClassifier> (flowmon.GetClassifier ());
		std::map<FlowId, FlowMonitor::FlowStats> stats = monitor->GetFlowStats ();
		uint64_t totalPacketsTx = 0, totalPacketsRx = 0, numberOfFlows = 0, numberOfRoutingPackets = 0;;
		Time totalDelay = Seconds(0.0);
		for (std::map<FlowId, FlowMonitor::FlowStats>::const_iterator i = stats.begin (); i != stats.end (); ++i)
		{
			Ipv4FlowClassifier::FiveTuple t = classifier->FindFlow (i->first);

			if (t.destinationAddress == "10.0.0.255")
			{
				numberOfRoutingPackets = numberOfRoutingPackets + i->second.rxPackets;
			}

			if (t.destinationAddress != "10.0.0.255")
			{
				totalPacketsTx = totalPacketsTx + i->second.txPackets;
				totalPacketsRx = totalPacketsRx + i->second.rxPackets;
				numberOfFlows += 1;
				totalDelay = totalDelay + i->second.delaySum;
			}
		}

		/* Print simulation results to terminal */
		std::cout << "\nNumber 0f flows: " << numberOfFlows << "\n";
		std::cout << "RunID used: " << runID << "\n\n";

		std::cout << "\nTrace Onoff packet delay:\t" << t_delay.GetSeconds()  << "/" << n << " = "<< (t_delay.GetSeconds())/n <<"\n\n";
		std::cout << "Trace MAC packet delay:\t\t" << t2_delay.GetSeconds()  << "/" << n2 << " = "<< (t2_delay.GetSeconds())/n2 <<"\n\n";

		std::cout << "Trace # MAC Tx:\t" << mactx << "\n\n";

		std::cout << "Trace # BATMAN Packets Tx:\t" << rTx << "\n";
		std::cout << "Trace # BATMAN Packets ReTx:\t" << rReTx << "\n";
		std::cout << "Trace # BATMAN Packets Rx:\t" << rRx << "\n\n";

		std::cout << "Trace # DSDV Packets Tx:\t" << rDTx << "\n";
		std::cout << "Trace # DSDV Packets Rx:\t" << rDRx << "\n\n";

		std::cout << "Trace # Onoff Packets Tx:\t" << packetCount << "\n";
		std::cout << "Trace # Onoff Packets Rx:\t" << packetsReceived << "\n\n";

		std::cout << "Trace Onoff PDR:\t" << (double)packetsReceived/packetCount << "\n\n";

		std::cout << "\n----------------------------------------------------------------\n\n";

		Simulator::Destroy ();

		/* Pick an output writer based in the requested format */
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

		/* Writer interrogate the DataCollector and save the results */
		if (output != 0)
			output->Output(data);

		return 0;
}
