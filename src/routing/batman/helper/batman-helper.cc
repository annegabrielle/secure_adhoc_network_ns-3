/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2010 Hemanth Narra
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
 * Authors: Hemanth Narra <hemanth@ittc.ku.com>, written after OlsrHelper by Mathieu Lacage <mathieu.lacage@sophia.inria.fr>
 *
 * James P.G. Sterbenz <jpgs@ittc.ku.edu>, director
 * ResiliNets Research Group  http://wiki.ittc.ku.edu/resilinets
 * Information and Telecommunication Technology Center (ITTC)
 * and Department of Electrical Engineering and Computer Science
 * The University of Kansas Lawrence, KS USA.
 *
 * Work supported in part by NSF FIND (Future Internet Design) Program
 * under grant CNS-0626918 (Postmodern Internet Architecture),
 * NSF grant CNS-1050226 (Multilayer Network Resilience Analysis and Experimentation on GENI),
 * US Department of Defense (DoD), and ITTC at The University of Kansas.
 */
#include "batman-helper.h"
#include "ns3/batman-routing-protocol.h"
#include "ns3/node-list.h"
#include "ns3/names.h"
#include "ns3/ipv4-list-routing.h"

namespace ns3 {
BatmanHelper::~BatmanHelper ()
{
}

BatmanHelper::BatmanHelper () : Ipv4RoutingHelper ()
{
  m_agentFactory.SetTypeId ("ns3::batman::RoutingProtocol");
}

BatmanHelper*
BatmanHelper::Copy (void) const
{
  return new BatmanHelper (*this);
}

Ptr<Ipv4RoutingProtocol>
BatmanHelper::Create (Ptr<Node> node) const
{
  Ptr<batman::RoutingProtocol> agent = m_agentFactory.Create<batman::RoutingProtocol> ();
  node->AggregateObject (agent);
  return agent;
}

void
BatmanHelper::Set (std::string name, const AttributeValue &value)
{
  m_agentFactory.Set (name, value);
}

}
