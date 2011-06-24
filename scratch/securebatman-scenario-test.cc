#include "ns3/core-module.h"
#include "ns3/secure-batman-helper.h"
#include "ns3/dsdv-helper.h"
#include "ns3/batman-helper.h"
#include "ns3/simulator-module.h"
#include "ns3/node-module.h"
#include "ns3/helper-module.h"
#include "ns3/ipv4-global-routing-helper.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("securebatmantest");

int 
main (int argc, char *argv[])
{
  LogComponentEnable("UdpEchoClientApplication", LOG_LEVEL_INFO);
  LogComponentEnable("UdpEchoServerApplication", LOG_LEVEL_INFO);

  uint32_t nodeAmount = 3;

  NodeContainer nodes;
  nodes.Create (nodeAmount);

//  CsmaHelper csma;
//  csma.SetChannelAttribute ("DataRate", StringValue ("100Mbps"));
//  csma.SetChannelAttribute ("Delay", TimeValue (NanoSeconds (6560)));
//
//  NetDeviceContainer devices;
//  devices = csma.Install (nodes);


  NqosWifiMacHelper wifiMac = NqosWifiMacHelper::Default ();
  wifiMac.SetType ("ns3::AdhocWifiMac");
  YansWifiPhyHelper wifiPhy = YansWifiPhyHelper::Default ();
  YansWifiChannelHelper wifiChannel;
  wifiChannel.SetPropagationDelay ("ns3::ConstantSpeedPropagationDelayModel");
  wifiChannel.AddPropagationLoss ("ns3::FriisPropagationLossModel");
  wifiPhy.SetChannel (wifiChannel.Create ());
  NS_LOG_DEBUG ("Created WiFiChannel");

  WifiHelper wifi;
  wifi.SetStandard (WIFI_PHY_STANDARD_80211b);
  wifi.SetRemoteStationManager ("ns3::ConstantRateWifiManager", "DataMode", StringValue ("DsssRate11Mbps"), "ControlMode", StringValue ("DsssRate11Mbps"));
  NetDeviceContainer devices;
  devices = wifi.Install (wifiPhy, wifiMac, nodes);

  MobilityHelper mobility;
  Ptr <ListPositionAllocator> positionAlloc = CreateObject<ListPositionAllocator>();
  positionAlloc->Add(Vector(0.0, 0.0, 0.0));
  positionAlloc->Add(Vector(0.0, 10, 0.0));
  mobility.SetPositionAllocator(positionAlloc);
  mobility.Install(nodes);

  SecureBatmanHelper batman;
  InternetStackHelper stack;
  stack.SetRoutingHelper (batman);
  stack.Install (nodes);

//	AodvHelper aodv;
//	InternetStackHelper stack;
//	stack.SetRoutingHelper (aodv);
//	stack.Install (nodes);

//	DsdvHelper dsdv;
//	dsdv.Set ("PeriodicUpdateInterval", TimeValue (Seconds (15)));
//	dsdv.Set ("SettlingTime", TimeValue (Seconds (6)));
//	InternetStackHelper stack;
//	stack.SetRoutingHelper (dsdv);
//	stack.Install (nodes);

  Ipv4AddressHelper address;
  address.SetBase ("10.0.0.0", "255.255.255.0");

  Ipv4InterfaceContainer interfaces;
  interfaces = address.Assign (devices);

  UdpEchoServerHelper echoServer (9);

  Time start = Seconds(5.0);
  Time stop = Seconds(11.0);


  ApplicationContainer serverApps = echoServer.Install (nodes.Get(nodeAmount-1));
  serverApps.Start (Seconds (1.0));
  serverApps.Stop (stop);

  UdpEchoClientHelper echoClient (interfaces.GetAddress (nodeAmount-1), 9);
  echoClient.SetAttribute ("MaxPackets", UintegerValue (1));
  echoClient.SetAttribute ("Interval", TimeValue (Seconds (1.)));
  echoClient.SetAttribute ("PacketSize", UintegerValue (1024));

  ApplicationContainer clientApps = echoClient.Install (nodes.Get (0));
  clientApps.Start (start);
  clientApps.Stop (stop);


//  	TypeId tid = TypeId::LookupByName ("ns3::UdpSocketFactory");
//  	Ptr <Socket> sink = Socket::CreateSocket (nodes.Get (nodeAmount-1), tid);
//  	InetSocketAddress local = InetSocketAddress (interfaces.GetAddress (nodeAmount-1), 9);
//  	sink->Bind (local);
//
//	UniformVariable var;
//	OnOffHelper onoff0 ("ns3::UdpSocketFactory", Address (InetSocketAddress (interfaces.GetAddress (0), 9)));
//	onoff0.SetAttribute ("OnTime", RandomVariableValue (ConstantVariable (1)));
//	onoff0.SetAttribute ("OffTime", RandomVariableValue (ConstantVariable (0)));
//
//	AddressValue remoteAddress (InetSocketAddress (interfaces.GetAddress (nodeAmount-1), 9));
//	onoff0.SetAttribute ("Remote", remoteAddress);
//
//	ApplicationContainer apps0 = onoff0.Install (nodes.Get (0));
//	apps0.Start (Seconds (var.GetValue (start, start + 1)));
//	apps0.Stop (stop);

	wifiPhy.EnablePcapAll ("test_secure");

	Simulator::Stop (stop);
	Simulator::Run ();
	Simulator::Destroy ();
	return 0;
}
