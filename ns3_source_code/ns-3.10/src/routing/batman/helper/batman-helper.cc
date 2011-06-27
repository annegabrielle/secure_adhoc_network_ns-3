/*
 *
 * BATMAN Helper Class
 *
 * Author     : Anne Gabrielle Bowitz
 * Email      : bowitz@stud.ntnu.no
 * Project    : Simulation of a Secure Ad Hoc Network Routing protocol
 * Institution: NTNU (Norwegian University of Science & Technology), ITEM (Institute of Telematics)
 *
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
