# -*-  Mode: Python; -*-
#  Copyright (c) 2009 INESC Porto
# 
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License version 2 as
#  published by the Free Software Foundation;
# 
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
# 
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software
#  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
# 
#  Authors: Gustavo Carneiro <gjc@inescporto.pt>

import sys
import ns3

DISTANCE = 100 # (m)
NUM_NODES_SIDE = 3

def main(argv):

    cmd = ns3.CommandLine()

    cmd.NumNodesSide = None
    cmd.AddValue("NumNodesSide", "Grid side number of nodes (total number of nodes will be this number squared)")

    cmd.Results = None
    cmd.AddValue("Results", "Write XML results to file")

    cmd.Plot = None
    cmd.AddValue("Plot", "Plot the results using the matplotlib python module")

    cmd.Parse(argv)

    wifi = ns3.WifiHelper.Default()
    wifiMac = ns3.NqosWifiMacHelper.Default()
    wifiPhy = ns3.YansWifiPhyHelper.Default()
    wifiChannel = ns3.YansWifiChannelHelper.Default()
    wifiPhy.SetChannel(wifiChannel.Create())
    ssid = ns3.Ssid("wifi-default")
    wifi.SetRemoteStationManager("ns3::ArfWifiManager")
    wifiMac.SetType ("ns3::AdhocWifiMac",
                     "Ssid", ns3.SsidValue(ssid))

    internet = ns3.InternetStackHelper()
    list_routing = ns3.Ipv4ListRoutingHelper()
    olsr_routing = ns3.OlsrHelper()
    static_routing = ns3.Ipv4StaticRoutingHelper()
    list_routing.Add(static_routing, 0)
    list_routing.Add(olsr_routing, 100)
    internet.SetRoutingHelper(list_routing)

    ipv4Addresses = ns3.Ipv4AddressHelper()
    ipv4Addresses.SetBase(ns3.Ipv4Address("10.0.0.0"), ns3.Ipv4Mask("255.255.255.0"))

    port = 9   # Discard port(RFC 863)
    onOffHelper = ns3.OnOffHelper("ns3::UdpSocketFactory",
                                  ns3.Address(ns3.InetSocketAddress(ns3.Ipv4Address("10.0.0.1"), port)))
    onOffHelper.SetAttribute("DataRate", ns3.DataRateValue(ns3.DataRate("100kbps")))
    onOffHelper.SetAttribute("OnTime", ns3.RandomVariableValue(ns3.ConstantVariable(1)))
    onOffHelper.SetAttribute("OffTime", ns3.RandomVariableValue(ns3.ConstantVariable(0)))

    addresses = []
    nodes = []

    if cmd.NumNodesSide is None:
        num_nodes_side = NUM_NODES_SIDE
    else:
        num_nodes_side = int(cmd.NumNodesSide)

    for xi in range(num_nodes_side):
        for yi in range(num_nodes_side):

            node = ns3.Node()
            nodes.append(node)

            internet.Install(ns3.NodeContainer(node))

            mobility = ns3.ConstantPositionMobilityModel()
            mobility.SetPosition(ns3.Vector(xi*DISTANCE, yi*DISTANCE, 0))
            node.AggregateObject(mobility)
            
            devices = wifi.Install(wifiPhy, wifiMac, node)
            ipv4_interfaces = ipv4Addresses.Assign(devices)
            addresses.append(ipv4_interfaces.GetAddress(0))

    for i, node in enumerate(nodes):
        destaddr = addresses[(len(addresses) - 1 - i) % len(addresses)]
        #print i, destaddr
        onOffHelper.SetAttribute("Remote", ns3.AddressValue(ns3.InetSocketAddress(destaddr, port)))
        app = onOffHelper.Install(ns3.NodeContainer(node))
        app.Start(ns3.Seconds(ns3.UniformVariable(20, 30).GetValue()))
            
    #internet.EnablePcapAll("wifi-olsr")
    flowmon_helper = ns3.FlowMonitorHelper()
    #flowmon_helper.SetMonitorAttribute("StartTime", ns3.TimeValue(ns3.Seconds(31)))
    monitor = flowmon_helper.InstallAll()
    monitor.SetAttribute("DelayBinWidth", ns3.DoubleValue(0.001))
    monitor.SetAttribute("JitterBinWidth", ns3.DoubleValue(0.001))
    monitor.SetAttribute("PacketSizeBinWidth", ns3.DoubleValue(20))

    ns3.Simulator.Stop(ns3.Seconds(44.0))
    ns3.Simulator.Run()

    def print_stats(os, st):
        print >> os, "  Tx Bytes: ", st.txBytes
        print >> os, "  Rx Bytes: ", st.rxBytes
        print >> os, "  Tx Packets: ", st.txPackets
        print >> os, "  Rx Packets: ", st.rxPackets
        print >> os, "  Lost Packets: ", st.lostPackets
        if st.rxPackets > 0:
            print >> os, "  Mean{Delay}: ", (st.delaySum.GetSeconds() / st.rxPackets)
	    print >> os, "  Mean{Jitter}: ", (st.jitterSum.GetSeconds() / (st.rxPackets-1))
            print >> os, "  Mean{Hop Count}: ", float(st.timesForwarded) / st.rxPackets + 1

        if 0:
            print >> os, "Delay Histogram"
            for i in range(st.delayHistogram.GetNBins () ):
              print >> os, " ",i,"(", st.delayHistogram.GetBinStart (i), "-", \
                  st.delayHistogram.GetBinEnd (i), "): ", st.delayHistogram.GetBinCount (i)
            print >> os, "Jitter Histogram"
            for i in range(st.jitterHistogram.GetNBins () ):
              print >> os, " ",i,"(", st.jitterHistogram.GetBinStart (i), "-", \
                  st.jitterHistogram.GetBinEnd (i), "): ", st.jitterHistogram.GetBinCount (i)
            print >> os, "PacketSize Histogram"
            for i in range(st.packetSizeHistogram.GetNBins () ):
              print >> os, " ",i,"(", st.packetSizeHistogram.GetBinStart (i), "-", \
                  st.packetSizeHistogram.GetBinEnd (i), "): ", st.packetSizeHistogram.GetBinCount (i)

        for reason, drops in enumerate(st.packetsDropped):
            print "  Packets dropped by reason %i: %i" % (reason, drops)
        #for reason, drops in enumerate(st.bytesDropped):
        #    print "Bytes dropped by reason %i: %i" % (reason, drops)

    monitor.CheckForLostPackets()
    classifier = flowmon_helper.GetClassifier()

    if cmd.Results is None:
        for flow_id, flow_stats in monitor.GetFlowStats():
            t = classifier.FindFlow(flow_id)
            proto = {6: 'TCP', 17: 'UDP'} [t.protocol]
            print "FlowID: %i (%s %s/%s --> %s/%i)" % \
                (flow_id, proto, t.sourceAddress, t.sourcePort, t.destinationAddress, t.destinationPort)
            print_stats(sys.stdout, flow_stats)
    else:
        print monitor.SerializeToXmlFile(cmd.Results, True, True)


    if cmd.Plot is not None:
        import pylab
        delays = []
        for flow_id, flow_stats in monitor.GetFlowStats():
            tupl = classifier.FindFlow(flow_id)
            if tupl.protocol == 17 and tupl.sourcePort == 698:
                continue
            delays.append(flow_stats.delaySum.GetSeconds() / flow_stats.rxPackets)
        pylab.hist(delays, 20)
        pylab.xlabel("Delay (s)")
        pylab.ylabel("Number of Flows")
        pylab.show()

    return 0


if __name__ == '__main__':
    sys.exit(main(sys.argv))

