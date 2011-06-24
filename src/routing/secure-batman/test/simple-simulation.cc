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
 *
 * ns-2 simple.tcl script (ported from ns-2)
 * Originally authored by Steve McCanne, 12/19/1996
 */

#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <cassert>

#include "ns3/core-module.h"
#include "ns3/common-module.h"
#include "ns3/node-module.h"
#include "ns3/helper-module.h"
#include "ns3/mobility-module.h"
#include "ns3/wifi-module.h"
#include "ns3/simulator-module.h"
#include "ns3/stats-module.h"
#include "ns3/ceas-routing-protocol.h"
#include "ns3/interval-data-calculator.h"

using namespace ns3;
using namespace ceas;
using namespace std;

#define SIMULATION_TIME 10000

//NS_LOG_COMPONENT_DEFINE ("SimpleCeasRoutingExample");
NS_LOG_COMPONENT_DEFINE ("CeasPacketDeliveryRateExperiment");

template <class T> inline std::string to_string (const T& t)
{
	std::stringstream ss;
	ss << t;
	return ss.str();
}

void printTime();

//----------------------------------------------------------------------
//-- main
//----------------------------------------------
int main(int argc, char *argv[])
{
	string bandwidth = "10"; // In Mbps
	string delay = "1"; // In ms
	string format("db");
	string experiment("ceas-packet-delivery-test");
	string strategy("ceas-default");
	string input;
	string temptype = "total";
	uint32_t runID = 1;
	uint32_t seed = 1234;
	double beta = 0.998;
	double rho = 0.01;
	double antRate = 1; // In number of ants per second
	double explorerAntRate = 0.1; // In number of ants per second
//	int ttl = 130;
	string s_simulationTime = "30"; // In seconds

	//DefaultValue::Bind ("DropTailQueue::m_maxPackets", 30);

	// Set up command line parameters used to control the experiment.
	// Allow the user to override any of the defaults via command-line arguments
	CommandLine cmd;
	cmd.AddValue("temptype", "Which temperature to log [elite, total]", temptype);
	cmd.AddValue("bandwidth", "Bandwidth between nodes (Mbps)", bandwidth);
	cmd.AddValue("delay", "Link delay between nodes (ms)", delay);
	cmd.AddValue("format", "Format to use for data output.", format);
	cmd.AddValue("experiment", "Identifier for experiment.", experiment);
	cmd.AddValue("strategy", "Identifier for strategy.", strategy);
	cmd.AddValue("run", "Identifier for run.", runID);
	cmd.AddValue("seed", "Seed for run.", seed);
	cmd.AddValue("beta", "Beta", beta);
	cmd.AddValue("rho", "Rho", rho);
	cmd.AddValue("antRate", "Ant rate", antRate);
	cmd.AddValue("exporerAntRate", "Explorer ant rate", explorerAntRate);
	cmd.Parse (argc, argv);

	if (format != "omnet" && format != "db") {
		NS_LOG_ERROR("Unknown output format '" << format << "'. Supported formats are 'omnet' and 'db'.");
		return -1;
	}

	#ifndef STATS_HAS_SQLITE3
	if (format == "db") {
		NS_LOG_ERROR("Sqlite output chosen, but sqlite support not compiled in.");
		return -1;
	}
	#endif

	{
		stringstream sstr("");
		sstr << delay;
		input = sstr.str();
	}

//	Simulator::SetScheduler(CreateObject<Ns2CalendarScheduler>());
	Simulator::SetScheduler(CreateObject<MapScheduler>());

	// Packet metadata has to be enabled before any packets are sent (which happens already when adding CEAS to nodes), otherwise crashes occur.
//	ns3::PacketMetadata::Enable ();
//	ns3::Packet::EnablePrinting();

	// Enable logging
	LogComponentEnable("CeasPacketDeliveryRateExperiment", LOG_LEVEL_INFO);

	// Set up some default values for the simulation.
//	Config::SetDefault("ns3::OnOffApplication::PacketSize", UintegerValue(210));
//	Config::SetDefault("ns3::OnOffApplication::DataRate", StringValue("448kb/s"));

	// Create nodes
	NS_LOG_INFO("Create nodes.");
	NodeContainer c;
	c.Create(12);
//	c.Create(30000);
	NodeContainer n100 = NodeContainer(c.Get(10), c.Get(0));

	NodeContainer n04 = NodeContainer(c.Get(0), c.Get(4));
	NodeContainer n05 = NodeContainer(c.Get(0), c.Get(5));
	NodeContainer n14 = NodeContainer(c.Get(1), c.Get(4));
	NodeContainer n15 = NodeContainer(c.Get(1), c.Get(5));
	NodeContainer n24 = NodeContainer(c.Get(2), c.Get(4));
	NodeContainer n25 = NodeContainer(c.Get(2), c.Get(5));
	NodeContainer n34 = NodeContainer(c.Get(3), c.Get(4));
	NodeContainer n35 = NodeContainer(c.Get(3), c.Get(5));
	NodeContainer n45 = NodeContainer(c.Get(4), c.Get(5));

	NodeContainer n46 = NodeContainer(c.Get(4), c.Get(6));
	NodeContainer n56 = NodeContainer(c.Get(5), c.Get(6));
	NodeContainer n47 = NodeContainer(c.Get(4), c.Get(7));
	NodeContainer n58 = NodeContainer(c.Get(5), c.Get(8));
	NodeContainer n67 = NodeContainer(c.Get(6), c.Get(7));
	NodeContainer n68 = NodeContainer(c.Get(6), c.Get(8));
	NodeContainer n78 = NodeContainer(c.Get(7), c.Get(8));

	NodeContainer n79 = NodeContainer(c.Get(7), c.Get(9));
	NodeContainer n69 = NodeContainer(c.Get(6), c.Get(9));
	NodeContainer n89 = NodeContainer(c.Get(8), c.Get(9));

	NodeContainer n911 = NodeContainer(c.Get(9), c.Get(11));

	// Enable CEAS
	NS_LOG_INFO("Add internet stack with CEAS routing.");
	ns3::ceas::CeasHelper ceasHelper;
	InternetStackHelper internet;
	internet.SetRoutingHelper(ceasHelper);
	internet.Install(c);

	// Create the channels first without any IP addressing information
	NS_LOG_INFO("Create channels and assign IP addresses.");
	bandwidth.append("Mbps");
	delay.append("ms");
	PointToPointHelper p2p;
	p2p.SetDeviceAttribute("DataRate", StringValue(bandwidth));
	p2p.SetChannelAttribute("Delay", StringValue(delay));

	NetDeviceContainer ndc100 = p2p.Install(n100);

	NetDeviceContainer ndc04 = p2p.Install(n04);
	NetDeviceContainer ndc05 = p2p.Install(n05);
	NetDeviceContainer ndc14 = p2p.Install(n14);
	NetDeviceContainer ndc15 = p2p.Install(n15);
	NetDeviceContainer ndc24 = p2p.Install(n24);
	NetDeviceContainer ndc25 = p2p.Install(n25);
	NetDeviceContainer ndc34 = p2p.Install(n34);
	NetDeviceContainer ndc35 = p2p.Install(n35);
	NetDeviceContainer ndc45 = p2p.Install(n45);

	NetDeviceContainer ndc46 = p2p.Install(n46);
	NetDeviceContainer ndc56 = p2p.Install(n56);
	NetDeviceContainer ndc47 = p2p.Install(n47);
	NetDeviceContainer ndc58 = p2p.Install(n58);
	NetDeviceContainer ndc67 = p2p.Install(n67);
	NetDeviceContainer ndc68 = p2p.Install(n68);
	NetDeviceContainer ndc78 = p2p.Install(n78);

	NetDeviceContainer ndc79 = p2p.Install(n79);
	NetDeviceContainer ndc69 = p2p.Install(n69);
	NetDeviceContainer ndc89 = p2p.Install(n89);

	NetDeviceContainer ndc911 = p2p.Install(n911);

	NetDeviceContainer ndc100_10 = NetDeviceContainer(ndc100.Get(0));
	NetDeviceContainer ndc100_0 = NetDeviceContainer(ndc100.Get(1));

	NetDeviceContainer ndc04_0 = NetDeviceContainer(ndc04.Get(0));
	NetDeviceContainer ndc04_4 = NetDeviceContainer(ndc04.Get(1));
	NetDeviceContainer ndc05_0 = NetDeviceContainer(ndc05.Get(0));
	NetDeviceContainer ndc05_5 = NetDeviceContainer(ndc05.Get(1));
	NetDeviceContainer ndc14_1 = NetDeviceContainer(ndc14.Get(0));
	NetDeviceContainer ndc14_4 = NetDeviceContainer(ndc14.Get(1));
	NetDeviceContainer ndc15_1 = NetDeviceContainer(ndc15.Get(0));
	NetDeviceContainer ndc15_5 = NetDeviceContainer(ndc15.Get(1));
	NetDeviceContainer ndc24_2 = NetDeviceContainer(ndc24.Get(0));
	NetDeviceContainer ndc24_4 = NetDeviceContainer(ndc24.Get(1));
	NetDeviceContainer ndc25_2 = NetDeviceContainer(ndc25.Get(0));
	NetDeviceContainer ndc25_5 = NetDeviceContainer(ndc25.Get(1));
	NetDeviceContainer ndc34_3 = NetDeviceContainer(ndc34.Get(0));
	NetDeviceContainer ndc34_4 = NetDeviceContainer(ndc34.Get(1));
	NetDeviceContainer ndc35_3 = NetDeviceContainer(ndc35.Get(0));
	NetDeviceContainer ndc35_5 = NetDeviceContainer(ndc35.Get(1));
	NetDeviceContainer ndc45_4 = NetDeviceContainer(ndc45.Get(0));
	NetDeviceContainer ndc45_5 = NetDeviceContainer(ndc45.Get(1));

	NetDeviceContainer ndc46_4 = NetDeviceContainer(ndc46.Get(0));
	NetDeviceContainer ndc46_6 = NetDeviceContainer(ndc46.Get(1));
	NetDeviceContainer ndc56_5 = NetDeviceContainer(ndc56.Get(0));
	NetDeviceContainer ndc56_6 = NetDeviceContainer(ndc56.Get(1));
	NetDeviceContainer ndc47_4 = NetDeviceContainer(ndc47.Get(0));
	NetDeviceContainer ndc47_7 = NetDeviceContainer(ndc47.Get(1));
	NetDeviceContainer ndc58_5 = NetDeviceContainer(ndc58.Get(0));
	NetDeviceContainer ndc58_8 = NetDeviceContainer(ndc58.Get(1));
	NetDeviceContainer ndc67_6 = NetDeviceContainer(ndc67.Get(0));
	NetDeviceContainer ndc67_7 = NetDeviceContainer(ndc67.Get(1));
	NetDeviceContainer ndc68_6 = NetDeviceContainer(ndc68.Get(0));
	NetDeviceContainer ndc68_8 = NetDeviceContainer(ndc68.Get(1));
	NetDeviceContainer ndc78_7 = NetDeviceContainer(ndc78.Get(0));
	NetDeviceContainer ndc78_8 = NetDeviceContainer(ndc78.Get(1));

	NetDeviceContainer ndc79_7 = NetDeviceContainer(ndc79.Get(0));
	NetDeviceContainer ndc79_9 = NetDeviceContainer(ndc79.Get(1));
	NetDeviceContainer ndc69_6 = NetDeviceContainer(ndc69.Get(0));
	NetDeviceContainer ndc69_9 = NetDeviceContainer(ndc69.Get(1));
	NetDeviceContainer ndc89_8 = NetDeviceContainer(ndc89.Get(0));
	NetDeviceContainer ndc89_9 = NetDeviceContainer(ndc89.Get(1));

	NetDeviceContainer ndc911_9 = NetDeviceContainer(ndc911.Get(0));
	NetDeviceContainer ndc911_11 = NetDeviceContainer(ndc911.Get(1));

	// Add IP addresses.
	NS_LOG_INFO("Assign IP Addresses.");
	Ipv4AddressHelper ipv4;
	ipv4.SetBase("10.1.100.0", "255.255.255.0", "0.0.0.10");
	ipv4.Assign(ndc100_10);
	ipv4.SetBase("10.1.100.0", "255.255.255.0", "0.0.0.12");
	ipv4.Assign(ndc100_0);

	ipv4.SetBase("10.1.4.0", "255.255.255.0", "0.0.0.12");
	ipv4.Assign(ndc04_0);
	ipv4.SetBase("10.1.4.0", "255.255.255.0", "0.0.0.4");
	ipv4.Assign(ndc04_4);
	ipv4.SetBase("10.1.5.0", "255.255.255.0", "0.0.0.12");
	ipv4.Assign(ndc05_0);
	ipv4.SetBase("10.1.5.0", "255.255.255.0", "0.0.0.5");
	ipv4.Assign(ndc05_5);
	ipv4.SetBase("10.1.14.0", "255.255.255.0", "0.0.0.1");
	ipv4.Assign(ndc14_1);
	ipv4.SetBase("10.1.14.0", "255.255.255.0", "0.0.0.4");
	ipv4.Assign(ndc14_4);
	ipv4.SetBase("10.1.15.0", "255.255.255.0", "0.0.0.1");
	ipv4.Assign(ndc15_1);
	ipv4.SetBase("10.1.15.0", "255.255.255.0", "0.0.0.5");
	ipv4.Assign(ndc15_5);
	ipv4.SetBase("10.1.24.0", "255.255.255.0", "0.0.0.2");
	ipv4.Assign(ndc24_2);
	ipv4.SetBase("10.1.24.0", "255.255.255.0", "0.0.0.4");
	ipv4.Assign(ndc24_4);
	ipv4.SetBase("10.1.25.0", "255.255.255.0", "0.0.0.2");
	ipv4.Assign(ndc25_2);
	ipv4.SetBase("10.1.25.0", "255.255.255.0", "0.0.0.5");
	ipv4.Assign(ndc25_5);
	ipv4.SetBase("10.1.34.0", "255.255.255.0", "0.0.0.3");
	ipv4.Assign(ndc34_3);
	ipv4.SetBase("10.1.34.0", "255.255.255.0", "0.0.0.4");
	ipv4.Assign(ndc34_4);
	ipv4.SetBase("10.1.35.0", "255.255.255.0", "0.0.0.3");
	ipv4.Assign(ndc35_3);
	ipv4.SetBase("10.1.35.0", "255.255.255.0", "0.0.0.5");
	ipv4.Assign(ndc35_5);
	ipv4.SetBase("10.1.45.0", "255.255.255.0", "0.0.0.4");
	ipv4.Assign(ndc45_4);
	ipv4.SetBase("10.1.45.0", "255.255.255.0", "0.0.0.5");
	ipv4.Assign(ndc45_5);

	ipv4.SetBase("10.1.46.0", "255.255.255.0", "0.0.0.4");
	ipv4.Assign(ndc46_4);
	ipv4.SetBase("10.1.46.0", "255.255.255.0", "0.0.0.6");
	ipv4.Assign(ndc46_6);
	ipv4.SetBase("10.1.56.0", "255.255.255.0", "0.0.0.5");
	ipv4.Assign(ndc56_5);
	ipv4.SetBase("10.1.56.0", "255.255.255.0", "0.0.0.6");
	ipv4.Assign(ndc56_6);
	ipv4.SetBase("10.1.47.0", "255.255.255.0", "0.0.0.4");
	ipv4.Assign(ndc47_4);
	ipv4.SetBase("10.1.47.0", "255.255.255.0", "0.0.0.7");
	ipv4.Assign(ndc47_7);
	ipv4.SetBase("10.1.58.0", "255.255.255.0", "0.0.0.5");
	ipv4.Assign(ndc58_5);
	ipv4.SetBase("10.1.58.0", "255.255.255.0", "0.0.0.8");
	ipv4.Assign(ndc58_8);
	ipv4.SetBase("10.1.67.0", "255.255.255.0", "0.0.0.6");
	ipv4.Assign(ndc67_6);
	ipv4.SetBase("10.1.67.0", "255.255.255.0", "0.0.0.7");
	ipv4.Assign(ndc67_7);
	ipv4.SetBase("10.1.68.0", "255.255.255.0", "0.0.0.6");
	ipv4.Assign(ndc68_6);
	ipv4.SetBase("10.1.68.0", "255.255.255.0", "0.0.0.8");
	ipv4.Assign(ndc68_8);
	ipv4.SetBase("10.1.78.0", "255.255.255.0", "0.0.0.7");
	ipv4.Assign(ndc78_7);
	ipv4.SetBase("10.1.78.0", "255.255.255.0", "0.0.0.8");
	ipv4.Assign(ndc78_8);

	ipv4.SetBase("10.1.79.0", "255.255.255.0", "0.0.0.7");
	ipv4.Assign(ndc79_7);
	ipv4.SetBase("10.1.79.0", "255.255.255.0", "0.0.0.9");
	ipv4.Assign(ndc79_9);
	ipv4.SetBase("10.1.69.0", "255.255.255.0", "0.0.0.6");
	ipv4.Assign(ndc69_6);
	ipv4.SetBase("10.1.69.0", "255.255.255.0", "0.0.0.9");
	ipv4.Assign(ndc69_9);
	ipv4.SetBase("10.1.89.0", "255.255.255.0", "0.0.0.8");
	ipv4.Assign(ndc89_8);
	ipv4.SetBase("10.1.89.0", "255.255.255.0", "0.0.0.9");
	ipv4.Assign(ndc89_9);

	ipv4.SetBase("10.1.99.0", "255.255.255.0", "0.0.0.9");
	ipv4.Assign(ndc911_9);
	ipv4.SetBase("10.1.99.0", "255.255.255.0", "0.0.0.11");
	ipv4.Assign(ndc911_11);

	c.Get(10)->GetObject<ceas::CeasRoutingProtocol>()->AddNeededDestination(Ipv4Address("10.1.99.11"));

	c.Get(10)->GetObject<ceas::CeasRoutingProtocol>()->AddNeighbour(Ipv4InterfaceAddress(Ipv4Address("10.1.100.10"), Ipv4Mask("255.255.255.255")), Ipv4Address("10.1.100.12"), 0.0, 1);

	c.Get(0)->GetObject<ceas::CeasRoutingProtocol>()->AddNeighbour(Ipv4InterfaceAddress(Ipv4Address("10.1.4.12"), Ipv4Mask("255.255.255.255")), Ipv4Address("10.1.4.4"), 0.001, 1);
	c.Get(0)->GetObject<ceas::CeasRoutingProtocol>()->AddNeighbour(Ipv4InterfaceAddress(Ipv4Address("10.1.5.12"), Ipv4Mask("255.255.255.255")), Ipv4Address("10.1.5.5"), 0.002, 1);
	c.Get(1)->GetObject<ceas::CeasRoutingProtocol>()->AddNeighbour(Ipv4InterfaceAddress(Ipv4Address("10.1.14.1"), Ipv4Mask("255.255.255.255")), Ipv4Address("10.1.14.4"), 0.001, 1);
	c.Get(1)->GetObject<ceas::CeasRoutingProtocol>()->AddNeighbour(Ipv4InterfaceAddress(Ipv4Address("10.1.15.1"), Ipv4Mask("255.255.255.255")), Ipv4Address("10.1.15.5"), 0.002, 1);
	c.Get(2)->GetObject<ceas::CeasRoutingProtocol>()->AddNeighbour(Ipv4InterfaceAddress(Ipv4Address("10.1.24.2"), Ipv4Mask("255.255.255.255")), Ipv4Address("10.1.24.4"), 0.002, 1);
	c.Get(2)->GetObject<ceas::CeasRoutingProtocol>()->AddNeighbour(Ipv4InterfaceAddress(Ipv4Address("10.1.25.2"), Ipv4Mask("255.255.255.255")), Ipv4Address("10.1.25.5"), 0.001, 1);
	c.Get(3)->GetObject<ceas::CeasRoutingProtocol>()->AddNeighbour(Ipv4InterfaceAddress(Ipv4Address("10.1.34.3"), Ipv4Mask("255.255.255.255")), Ipv4Address("10.1.34.4"), 0.002, 1);
	c.Get(3)->GetObject<ceas::CeasRoutingProtocol>()->AddNeighbour(Ipv4InterfaceAddress(Ipv4Address("10.1.35.3"), Ipv4Mask("255.255.255.255")), Ipv4Address("10.1.35.5"), 0.001, 1);
	c.Get(4)->GetObject<ceas::CeasRoutingProtocol>()->AddNeighbour(Ipv4InterfaceAddress(Ipv4Address("10.1.45.4"), Ipv4Mask("255.255.255.255")), Ipv4Address("10.1.45.5"), 0.0002, 1);

	c.Get(4)->GetObject<ceas::CeasRoutingProtocol>()->AddNeighbour(Ipv4InterfaceAddress(Ipv4Address("10.1.46.4"), Ipv4Mask("255.255.255.255")), Ipv4Address("10.1.46.6"), 0.001, 1);
	c.Get(4)->GetObject<ceas::CeasRoutingProtocol>()->AddNeighbour(Ipv4InterfaceAddress(Ipv4Address("10.1.47.4"), Ipv4Mask("255.255.255.255")), Ipv4Address("10.1.47.7"), 0.0022, 1);

	c.Get(5)->GetObject<ceas::CeasRoutingProtocol>()->AddNeighbour(Ipv4InterfaceAddress(Ipv4Address("10.1.56.5"), Ipv4Mask("255.255.255.255")), Ipv4Address("10.1.56.6"), 0.001, 1);
	c.Get(5)->GetObject<ceas::CeasRoutingProtocol>()->AddNeighbour(Ipv4InterfaceAddress(Ipv4Address("10.1.58.5"), Ipv4Mask("255.255.255.255")), Ipv4Address("10.1.58.8"), 0.0022, 1);

	c.Get(6)->GetObject<ceas::CeasRoutingProtocol>()->AddNeighbour(Ipv4InterfaceAddress(Ipv4Address("10.1.69.6"), Ipv4Mask("255.255.255.255")), Ipv4Address("10.1.69.9"), 0.0018, 1);
	c.Get(6)->GetObject<ceas::CeasRoutingProtocol>()->AddNeighbour(Ipv4InterfaceAddress(Ipv4Address("10.1.68.6"), Ipv4Mask("255.255.255.255")), Ipv4Address("10.1.68.8"), 0.001, 1);
	c.Get(6)->GetObject<ceas::CeasRoutingProtocol>()->AddNeighbour(Ipv4InterfaceAddress(Ipv4Address("10.1.67.6"), Ipv4Mask("255.255.255.255")), Ipv4Address("10.1.67.7"), 0.001, 1);
	c.Get(7)->GetObject<ceas::CeasRoutingProtocol>()->AddNeighbour(Ipv4InterfaceAddress(Ipv4Address("10.1.78.7"), Ipv4Mask("255.255.255.255")), Ipv4Address("10.1.78.8"), 0.0002, 1);

	c.Get(7)->GetObject<ceas::CeasRoutingProtocol>()->AddNeighbour(Ipv4InterfaceAddress(Ipv4Address("10.1.79.7"), Ipv4Mask("255.255.255.255")), Ipv4Address("10.1.79.9"), 0.001, 1);
	c.Get(8)->GetObject<ceas::CeasRoutingProtocol>()->AddNeighbour(Ipv4InterfaceAddress(Ipv4Address("10.1.89.8"), Ipv4Mask("255.255.255.255")), Ipv4Address("10.1.89.9"), 0.001, 1);

	c.Get(9)->GetObject<ceas::CeasRoutingProtocol>()->AddNeighbour(Ipv4InterfaceAddress(Ipv4Address("10.1.99.9"), Ipv4Mask("255.255.255.255")), Ipv4Address("10.1.99.11"), 0.0, 1);

	// Link registration in the other direction
	c.Get(0)->GetObject<ceas::CeasRoutingProtocol>()->AddNeighbour(Ipv4InterfaceAddress(Ipv4Address("10.1.100.12"), Ipv4Mask("255.255.255.255")), Ipv4Address("10.1.100.10"), 0.0, 1);

	c.Get(4)->GetObject<ceas::CeasRoutingProtocol>()->AddNeighbour(Ipv4InterfaceAddress(Ipv4Address("10.1.4.4"), Ipv4Mask("255.255.255.255")), Ipv4Address("10.1.4.12"), 0.001, 1);
	c.Get(5)->GetObject<ceas::CeasRoutingProtocol>()->AddNeighbour(Ipv4InterfaceAddress(Ipv4Address("10.1.5.5"), Ipv4Mask("255.255.255.255")), Ipv4Address("10.1.5.12"), 0.002, 1);
	c.Get(4)->GetObject<ceas::CeasRoutingProtocol>()->AddNeighbour(Ipv4InterfaceAddress(Ipv4Address("10.1.14.4"), Ipv4Mask("255.255.255.255")), Ipv4Address("10.1.14.1"), 0.001, 1);
	c.Get(5)->GetObject<ceas::CeasRoutingProtocol>()->AddNeighbour(Ipv4InterfaceAddress(Ipv4Address("10.1.15.5"), Ipv4Mask("255.255.255.255")), Ipv4Address("10.1.15.1"), 0.002, 1);
	c.Get(4)->GetObject<ceas::CeasRoutingProtocol>()->AddNeighbour(Ipv4InterfaceAddress(Ipv4Address("10.1.24.4"), Ipv4Mask("255.255.255.255")), Ipv4Address("10.1.24.2"), 0.002, 1);
	c.Get(5)->GetObject<ceas::CeasRoutingProtocol>()->AddNeighbour(Ipv4InterfaceAddress(Ipv4Address("10.1.25.5"), Ipv4Mask("255.255.255.255")), Ipv4Address("10.1.25.2"), 0.001, 1);
	c.Get(4)->GetObject<ceas::CeasRoutingProtocol>()->AddNeighbour(Ipv4InterfaceAddress(Ipv4Address("10.1.34.4"), Ipv4Mask("255.255.255.255")), Ipv4Address("10.1.34.3"), 0.002, 1);
	c.Get(5)->GetObject<ceas::CeasRoutingProtocol>()->AddNeighbour(Ipv4InterfaceAddress(Ipv4Address("10.1.35.5"), Ipv4Mask("255.255.255.255")), Ipv4Address("10.1.35.3"), 0.001, 1);
	c.Get(5)->GetObject<ceas::CeasRoutingProtocol>()->AddNeighbour(Ipv4InterfaceAddress(Ipv4Address("10.1.45.5"), Ipv4Mask("255.255.255.255")), Ipv4Address("10.1.45.4"), 0.0002, 1);

	c.Get(6)->GetObject<ceas::CeasRoutingProtocol>()->AddNeighbour(Ipv4InterfaceAddress(Ipv4Address("10.1.46.6"), Ipv4Mask("255.255.255.255")), Ipv4Address("10.1.46.4"), 0.001, 1);
	c.Get(7)->GetObject<ceas::CeasRoutingProtocol>()->AddNeighbour(Ipv4InterfaceAddress(Ipv4Address("10.1.47.7"), Ipv4Mask("255.255.255.255")), Ipv4Address("10.1.47.4"), 0.0022, 1);

	c.Get(6)->GetObject<ceas::CeasRoutingProtocol>()->AddNeighbour(Ipv4InterfaceAddress(Ipv4Address("10.1.56.6"), Ipv4Mask("255.255.255.255")), Ipv4Address("10.1.56.5"), 0.001, 1);
	c.Get(8)->GetObject<ceas::CeasRoutingProtocol>()->AddNeighbour(Ipv4InterfaceAddress(Ipv4Address("10.1.58.8"), Ipv4Mask("255.255.255.255")), Ipv4Address("10.1.58.5"), 0.0022, 1);

	c.Get(9)->GetObject<ceas::CeasRoutingProtocol>()->AddNeighbour(Ipv4InterfaceAddress(Ipv4Address("10.1.69.9"), Ipv4Mask("255.255.255.255")), Ipv4Address("10.1.69.6"), 0.0018, 1);
	c.Get(8)->GetObject<ceas::CeasRoutingProtocol>()->AddNeighbour(Ipv4InterfaceAddress(Ipv4Address("10.1.68.8"), Ipv4Mask("255.255.255.255")), Ipv4Address("10.1.68.6"), 0.001, 1);
	c.Get(7)->GetObject<ceas::CeasRoutingProtocol>()->AddNeighbour(Ipv4InterfaceAddress(Ipv4Address("10.1.67.7"), Ipv4Mask("255.255.255.255")), Ipv4Address("10.1.67.6"), 0.001, 1);
	c.Get(8)->GetObject<ceas::CeasRoutingProtocol>()->AddNeighbour(Ipv4InterfaceAddress(Ipv4Address("10.1.78.8"), Ipv4Mask("255.255.255.255")), Ipv4Address("10.1.78.7"), 0.0002, 1);

	c.Get(9)->GetObject<ceas::CeasRoutingProtocol>()->AddNeighbour(Ipv4InterfaceAddress(Ipv4Address("10.1.79.9"), Ipv4Mask("255.255.255.255")), Ipv4Address("10.1.79.7"), 0.001, 1);
	c.Get(9)->GetObject<ceas::CeasRoutingProtocol>()->AddNeighbour(Ipv4InterfaceAddress(Ipv4Address("10.1.89.9"), Ipv4Mask("255.255.255.255")), Ipv4Address("10.1.89.8"), 0.001, 1);

	c.Get(11)->GetObject<ceas::CeasRoutingProtocol>()->AddNeighbour(Ipv4InterfaceAddress(Ipv4Address("10.1.99.11"), Ipv4Mask("255.255.255.255")), Ipv4Address("10.1.99.9"), 0.0, 1);


	// Create the OnOff application to send UDP datagrams of size
	// 210 bytes at a rate of 448 Kb/s
//	NS_LOG_INFO ("Create Applications.");
//	uint16_t port = 9;   // Discard port (RFC 863)
//
//	OnOffHelper onoff("ns3::UdpSocketFactory",
//					 InetSocketAddress(i34.GetAddress(1), port));
//	onoff.SetAttribute("OnTime", RandomVariableValue(ConstantVariable(1)));
//	onoff.SetAttribute("OffTime", RandomVariableValue(ConstantVariable(0)));
//
//	ApplicationContainer apps = onoff.Install(c.Get(0));
//	apps.Start(Seconds(0.001));
//	apps.Stop(Seconds(10.0));
//
//	// Create a packet sink to receive these packets
//	PacketSinkHelper sink("ns3::UdpSocketFactory",
//			InetSocketAddress(Ipv4Address::GetAny(), port));
//
//	apps = sink.Install(c.Get(3));
//	apps.Start(Seconds(1.0));
//	apps.Stop(Seconds(10.0));
//
//	// Create a similar flow from n3 to n1, starting at time 1.1 seconds
//	onoff.SetAttribute("Remote",
//			AddressValue(InetSocketAddress(i12.GetAddress(0), port)));
//	apps = onoff.Install(c.Get(3));
//	apps.Start(Seconds(1.1));
//	apps.Stop(Seconds(10.0));
//
//	// Create a packet sink to receive these packets
//	apps = sink.Install(c.Get(1));
//	apps.Start(Seconds(1.1));
//	apps.Stop(Seconds(10.0));

//	std::ofstream ascii;
//	ascii.open("simple-point-to-point-ceas.tr");
//	PointToPointHelper::EnablePcapAll("simple-point-to-point-ceas");
//	PointToPointHelper::EnableAsciiAll(ascii);

	Simulator::Stop(Seconds(SIMULATION_TIME));

	//------------------------------------------------------------
	//-- Setup stats and data collection
	//--------------------------------------------

//	// Create a DataCollector object to hold information about this run.
//	DataCollector data;
//	data.DescribeRun(experiment,
//			strategy,
//			input,
//			to_string(runID));
//
//	// Add any information we wish to record about this run.
//	data.AddMetadata("author", "Jonathan Brugge");
//	data.AddMetadata("seed", seed);
//
//	// Create counters to track how many packets are generated and received.
//	Ptr<PacketCounterCalculator> totalGeneratedPackets =
//		CreateObject<PacketCounterCalculator>();
//	totalGeneratedPackets->SetKey("generated-packets");
//
//	Ptr<PacketCounterCalculator> totalReceivedPackets = CreateObject<PacketCounterCalculator>();
//	totalReceivedPackets->SetKey("received-packets");
//
//	Ptr<TimeMinMaxAvgTotalCalculator> delayCalculator = CreateObject<TimeMinMaxAvgTotalCalculator>();
//	delayCalculator->SetKey("packet-delay");
//	delayCalculator->Enable();
//
//	// Add calculators to nodes
//	for (uint32_t i = 0; i < c.GetN (); ++i) {
//		Ptr<Node> node = c.Get (i);
//		Ptr<ceas::CeasRoutingProtocol> ceas = node->GetObject<ceas::CeasRoutingProtocol>();
//
//		ceas->SetReceiveCounter(totalReceivedPackets);
//		ceas->SetTransmitCounter(totalGeneratedPackets);
//		ceas->SetDelayCalculator(delayCalculator);
//	}
//
//	// The following calculator is only added to one node
//	Ptr<IntervalDataCalculator> temperatureCalculator = CreateObject<IntervalDataCalculator>();
//	temperatureCalculator->SetKey("temperature");
//	temperatureCalculator->SetInterval(Seconds(1));
//	temperatureCalculator->SetRunTime(Seconds(SIMULATION_TIME));
//	temperatureCalculator->Enable();
//	Ptr<Node> src = c.Get(10);
//	Ipv4Address ipv4Src = Ipv4Address("10.1.100.10");
//	Ipv4Address ipv4Dest = Ipv4Address("10.1.99.11");
//	Ptr<Node> dest = c.Get(11);
//	Ptr<ceas::CeasRoutingProtocol> ceasDest = dest->GetObject<ceas::CeasRoutingProtocol>();
//	Ptr<ceas::CeasRoutingProtocol> ceasSrc = src->GetObject<ceas::CeasRoutingProtocol>();
//	if (temptype.compare(string("total")) == 0) // total temperature
//	{
//		ceasDest->SetTemperatureCalculator(temperatureCalculator, ipv4Src, ipv4Dest, false);
//	}
//	else // elite temperature
//	{
//		ceasDest->SetTemperatureCalculator(temperatureCalculator, ipv4Src, ipv4Dest, true);
//	}
////	ceasSrc->EnableRoutingTablePrinting();
//	ceasDest->EnableTemperatureTablePrinting();
//
//	c.Get(0)->GetObject<ceas::CeasRoutingProtocol>()->EnableRoutingTablePrinting();
//	c.Get(1)->GetObject<ceas::CeasRoutingProtocol>()->EnableRoutingTablePrinting();
//	c.Get(2)->GetObject<ceas::CeasRoutingProtocol>()->EnableRoutingTablePrinting();
//	c.Get(3)->GetObject<ceas::CeasRoutingProtocol>()->EnableRoutingTablePrinting();
//	c.Get(4)->GetObject<ceas::CeasRoutingProtocol>()->EnableRoutingTablePrinting();
//	c.Get(5)->GetObject<ceas::CeasRoutingProtocol>()->EnableRoutingTablePrinting();
//	c.Get(6)->GetObject<ceas::CeasRoutingProtocol>()->EnableRoutingTablePrinting();
//	c.Get(7)->GetObject<ceas::CeasRoutingProtocol>()->EnableRoutingTablePrinting();
//	c.Get(8)->GetObject<ceas::CeasRoutingProtocol>()->EnableRoutingTablePrinting();
//	c.Get(9)->GetObject<ceas::CeasRoutingProtocol>()->EnableRoutingTablePrinting();
//	c.Get(10)->GetObject<ceas::CeasRoutingProtocol>()->EnableRoutingTablePrinting();
//	c.Get(11)->GetObject<ceas::CeasRoutingProtocol>()->EnableRoutingTablePrinting();
//
//	// Add calculators to the DataCollector
//	data.AddDataCalculator(totalReceivedPackets);
//	data.AddDataCalculator(totalGeneratedPackets);
//	data.AddDataCalculator(delayCalculator);
//	data.AddDataCalculator(temperatureCalculator);

	// Set the right seed for the random number generator
	SeedManager::SetSeed(seed);
	SeedManager::SetRun(runID);

	for (uint32_t i = 500; i < SIMULATION_TIME; i+=500)
	{
		Simulator::Schedule(
				Seconds(i),
				&printTime);
	}

	// Run the actual simulation
	NS_LOG_INFO("Run Simulation.");
	Simulator::Run();
	Simulator::Destroy();
	NS_LOG_INFO("Done.");

	//------------------------------------------------------------
	//-- Generate statistics output.
	//--------------------------------------------

//	// Pick an output writer based in the requested format.
//	Ptr<DataOutputInterface> output = 0;
//	if (format == "omnet") {
//		NS_LOG_INFO("Creating omnet formatted data output.");
//		output = CreateObject<OmnetDataOutput>();
//	} else if (format == "db") {
//		#ifdef STATS_HAS_SQLITE3
//			NS_LOG_INFO("Creating sqlite formatted data output.");
//			output = CreateObject<SqliteDataOutput>();
//		#endif
//	} else {
//		NS_LOG_ERROR("Unknown output format " << format);
//	}
//
//	// Finally, have that writer interrogate the DataCollector and save
//	// the results.
//	if (output != 0)
//		output->Output(data);

	return 0;
}

void printTime()
{
	NS_LOG_INFO("Time now: " << Simulator::Now());
}
