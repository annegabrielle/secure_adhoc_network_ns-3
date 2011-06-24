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
 * Author: Josh Pelkey <jpelkey@gatech.edu>
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

  uint32_t xSize = 5;
  uint32_t ySize = 5;
  uint16_t port = 0;
  std::string animFile;

  CommandLine cmd;
  cmd.AddValue ("xSize", "Number of rows of nodes", xSize);
  cmd.AddValue ("ySize", "Number of columns of nodes", ySize);
  cmd.AddValue ("port",  "Port Number for Remote Animation", port);
  cmd.AddValue ("animFile",  "File Name for Animation Output", animFile);

  cmd.Parse (argc,argv);
  if (xSize < 1 || ySize < 1 || (xSize < 2 && ySize < 2))
    {
      NS_FATAL_ERROR ("Need more nodes for grid.");
    }
  
  PointToPointHelper pointToPoint;
  pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
  pointToPoint.SetChannelAttribute ("Delay", StringValue ("2ms"));

  // Create Grid
  PointToPointGridHelper grid (xSize, ySize, pointToPoint);

  // Install stack on Grid
  InternetStackHelper stack;
  grid.InstallStack (stack);

  // Assign Addresses to Grid
  grid.AssignIpv4Addresses (Ipv4AddressHelper ("10.1.1.0", "255.255.255.0"),
                            Ipv4AddressHelper ("10.2.1.0", "255.255.255.0"));


  OnOffHelper clientHelper ("ns3::UdpSocketFactory", Address ());
  clientHelper.SetAttribute 
    ("OnTime", RandomVariableValue (ConstantVariable (1)));
  clientHelper.SetAttribute 
    ("OffTime", RandomVariableValue (ConstantVariable (0)));
  ApplicationContainer clientApps;

  // Create an on/off app sending packets
  AddressValue remoteAddress (InetSocketAddress (grid.GetIpv4Address (xSize-1,ySize-1), 1000));
  clientHelper.SetAttribute ("Remote", remoteAddress);
  clientApps.Add (clientHelper.Install (grid.GetNode (0,0)));

  clientApps.Start (Seconds (0.0));
  clientApps.Stop (Seconds (1.5));

  // Set the bounding box for animation
  grid.BoundingBox (1, 1, 10, 10);

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
  
  // Set up the actual simulation
  Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

  std::cout << "Running the simulation" << std::endl;
  Simulator::Run ();
  std::cout << "Destroying the simulation" << std::endl;
  Simulator::Destroy ();
  std::cout << "Stopping the animation" << std::endl;
  anim.StopAnimation();
  return 0;
}
