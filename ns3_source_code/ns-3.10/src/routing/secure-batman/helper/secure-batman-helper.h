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
#ifndef SECURE_BATMANHELPER_H_
#define SECURE_BATMANHELPER_H_

#include "ns3/object-factory.h"
#include "ns3/node.h"
#include "ns3/node-container.h"
#include "ns3/ipv4-routing-helper.h"

namespace ns3 {

class SecureBatmanHelper : public Ipv4RoutingHelper
{
public:
  SecureBatmanHelper ();
  ~SecureBatmanHelper (); //destructor
  /**
   *
   * This method is mainly for internal use by the other helpers;
   * clients are expected to free the dynamic memory allocated by this method
   */
  SecureBatmanHelper* Copy (void) const;

  /**
   * \param node the node on which the routing protocol will run
   * \returns a newly-created routing protocol
   *
   * This method will be called by ns3::InternetStackHelper::Install
   *
   */
  virtual Ptr<Ipv4RoutingProtocol> Create (Ptr<Node> node) const;
  /**
   * \param name the name of the attribute to set
   * \param value the value of the attribute to set.
   *
   * This method controls the attributes of ns3::securebatman::RoutingProtocol
   */
  void Set (std::string name, const AttributeValue &value);

private:
  ObjectFactory m_agentFactory;
};

}
#endif /* SECURE_BATMANHELPER_H_ */
