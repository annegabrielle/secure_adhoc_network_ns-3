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
 * Author: George F. Riley<riley@ece.gatech.edu>
 */

#include <iostream>

#include "ns3/core-module.h"
#include "ns3/simulator-module.h"
#include "ns3/node-module.h"
#include "ns3/helper-module.h"
#include "ns3/ipv4-global-routing-helper.h"

using namespace ns3;

int main (int argc, char *argv[])
{
  Config::SetDefault ("ns3::OnOffApplication::PacketSize", UintegerValue (512));
  Config::SetDefault ("ns3::OnOffApplication::DataRate", StringValue ("500kb/s"));

  uint32_t    nLeftLeaf = 5;
  uint32_t    nRightLeaf = 5;
  uint32_t    nLeaf = 0; // If non-zero, number of both left and right
  uint16_t    port = 0;  // If non zero, port to bind to for anim connection
  std::string animFile;  // Name of file for animation output

  CommandLine cmd;
  cmd.AddValue ("nLeftLeaf", "Number of left side leaf nodes", nLeftLeaf);
  cmd.AddValue ("nRightLeaf","Number of right side leaf nodes", nRightLeaf);
  cmd.AddValue ("nLeaf",     "Number of left and right side leaf nodes", nLeaf);
  cmd.AddValue ("port",      "Port Number for Remote Animation", port);
  cmd.AddValue ("animFile",  "File Name for Animation Output", animFile);

  cmd.Parse (argc,argv);
  if (nLeaf > 0)
    {
      nLeftLeaf = nLeaf;
      nRightLeaf = nLeaf;
    }
  
  // Create the point-to-point link helpers
  PointToPointHelper pointToPointRouter;
  pointToPointRouter.SetDeviceAttribute  ("DataRate", StringValue ("10Mbps"));
  pointToPointRouter.SetChannelAttribute ("Delay", StringValue ("1ms"));
  PointToPointHelper pointToPointLeaf;
  pointToPointLeaf.SetDeviceAttribute    ("DataRate", StringValue ("10Mbps"));
  pointToPointLeaf.SetChannelAttribute   ("Delay", StringValue ("1ms"));

  PointToPointDumbbellHelper d(nLeftLeaf, pointToPointLeaf,
                   nRightLeaf, pointToPointLeaf,
                   pointToPointRouter);

  // Install Stack
  InternetStackHelper stack;
  d.InstallStack (stack);

  // Assign IP Addresses
  d.AssignIpv4Addresses (Ipv4AddressHelper ("10.1.1.0", "255.255.255.0"),
                    Ipv4AddressHelper ("10.2.1.0", "255.255.255.0"),
                    Ipv4AddressHelper ("10.3.1.0", "255.255.255.0"));
  
  // Install on/off app on all right side nodes
  OnOffHelper clientHelper ("ns3::UdpSocketFactory", Address ());
  clientHelper.SetAttribute 
    ("OnTime", RandomVariableValue (UniformVariable (0, 1)));
  clientHelper.SetAttribute 
    ("OffTime", RandomVariableValue (UniformVariable (0, 1)));
  ApplicationContainer clientApps;

  for (uint32_t i = 0; i < d.RightCount (); ++i)
    {
      // Create an on/off app sending packets to the same leaf right side
      AddressValue remoteAddress (InetSocketAddress (d.GetLeftIpv4Address (i), 1000));
      clientHelper.SetAttribute ("Remote", remoteAddress);
      clientApps.Add(clientHelper.Install (d.GetRight (i)));
    }

  clientApps.Start (Seconds (0.0));
  clientApps.Stop (Seconds (10.0));

  // Set the bounding box for animation
  d.BoundingBox (1, 1, 10, 10);

  // Create the animation object and configure for specified output
  AnimationInterface anim;
  if (port > 0)
    {
      anim.SetServerPort (port);
    }
  else if (!animFile.empty ())
    {
      anim.SetOutputFile (animFile);
    }
  anim.StartAnimation ();
  
  // Set up the acutal simulation
  Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

  std::cout << "Running the simulation" << std::endl;
  Simulator::Run ();
  std::cout << "Destroying the simulation" << std::endl;
  Simulator::Destroy ();
  std::cout << "Stopping the animation" << std::endl;
  anim.StopAnimation();
  return 0;
}
