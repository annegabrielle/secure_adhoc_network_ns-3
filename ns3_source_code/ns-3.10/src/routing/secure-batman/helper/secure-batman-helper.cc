/*
 *
 * Secure BATMAN Helper Class
 *
 * Author     : Anne Gabrielle Bowitz
 * Email      : bowitz@stud.ntnu.no
 * Project    : Simulation of a Secure Ad Hoc Network Routing protocol
 * Institution: NTNU (Norwegian University of Science & Technology), ITEM (Institute of Telematics)
 *
 */
#include "secure-batman-helper.h"
#include "ns3/secure-batman-routing-protocol.h"
#include "ns3/node-list.h"
#include "ns3/names.h"
#include "ns3/ipv4-list-routing.h"

namespace ns3 {
SecureBatmanHelper::~SecureBatmanHelper ()
{
}

SecureBatmanHelper::SecureBatmanHelper () : Ipv4RoutingHelper ()
{
  m_agentFactory.SetTypeId ("ns3::securebatman::RoutingProtocol");
}

SecureBatmanHelper*
SecureBatmanHelper::Copy (void) const
{
  return new SecureBatmanHelper (*this);
}

Ptr<Ipv4RoutingProtocol>
SecureBatmanHelper::Create (Ptr<Node> node) const
{
  Ptr<securebatman::RoutingProtocol> agent = m_agentFactory.Create<securebatman::RoutingProtocol> ();
  node->AggregateObject (agent);
  return agent;
}

void
SecureBatmanHelper::Set (std::string name, const AttributeValue &value)
{
  m_agentFactory.Set (name, value);
}

}
