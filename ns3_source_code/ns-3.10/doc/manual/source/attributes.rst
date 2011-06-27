.. include:: replace.txt

Attributes
----------

In |ns3| simulations, there are two main aspects to configuration:

* the simulation topology and how objects are connected 
* the values used by the models instantiated in the topology

This chapter focuses on the second item above: how the many values in use in
|ns3| are organized, documented, and modifiable by |ns3| users. The |ns3|
attribute system is also the underpinning of how traces and statistics are
gathered in the simulator. 

Before delving into details of the attribute value system, it will help to
review some basic properties of class :cpp:class:`ns3::Object`.

Object Overview
***************

|ns3| is fundamentally a C++ object-based system. By this we mean that new C++
classes (types) can be declared, defined, and subclassed as usual.

Many |ns3| objects inherit from the :cpp:class:`ns3::Object` base class.  These
objects have some additional properties that we exploit for organizing the
system and improving the memory management of our objects:

* a "metadata" system that links the class name to a lot of meta-information
  about the object, including the base class of the subclass, the set of
  accessible constructors in the subclass, and the set of "attributes" of the
  subclass
* a reference counting smart pointer implementation, for memory management.

|ns3| objects that use the attribute system derive from either
:cpp:class:`ns3::Object` or :cpp:class:`ns3::ObjectBase`. Most |ns3| objects we
will discuss derive from :cpp:class:`ns3::Object`, but a few that are outside
the smart pointer memory management framework derive from
:cpp:class:`ns3::ObjectBase`.

Let's review a couple of properties of these objects.

Smart pointers
**************

As introduced in the |ns3| tutorial, |ns3| objects are memory managed by a
`reference counting smart pointer implementation
<http://en.wikipedia.org/wiki/Smart_pointer>`_, class :cpp:class:`ns3::Ptr`. 

Smart pointers are used extensively in the |ns3| APIs, to avoid passing
references to heap-allocated objects that may cause memory leaks.  
For most basic usage (syntax), treat a smart pointer like a regular pointer:::

  Ptr<WifiNetDevice> nd = ...;
  nd->CallSomeFunction ();
  // etc.

CreateObject
++++++++++++

As we discussed above in :ref:`Memory management and class Ptr`, at the
lowest-level API, objects of type :cpp:class:`ns3::Object` are not instantiated
using ``operator new`` as usual but instead by a templated function called
:cpp:func:`CreateObject()`.

A typical way to create such an object is as follows:::

  Ptr<WifiNetDevice> nd = CreateObject<WifiNetDevice> ();

You can think of this as being functionally equivalent to:::

  WifiNetDevice* nd = new WifiNetDevice ();

Objects that derive from :cpp:class:`ns3::Object` must be allocated on the heap
using CreateObject(). Those deriving from :cpp:class:`ns3::ObjectBase`, such as
|ns3| helper functions and packet headers and trailers, can be allocated on the
stack.  

In some scripts, you may not see a lot of CreateObject() calls in the code; this
is because there are some helper objects in effect that are doing the
CreateObject()s for you.

TypeId
++++++

|ns3| classes that derive from class ns3::Object can include a metadata class
called ``TypeId`` that records meta-information about the class, for use in the
object aggregation and component manager systems:

* a unique string identifying the class
* the base class of the subclass, within the metadata system
* the set of accessible constructors in the subclass

Object Summary
++++++++++++++

Putting all of these concepts together, let's look at a specific
example: class :cpp:class:`ns3::Node`.

The public header file node.h has a declaration that includes a static GetTypeId
function call:::

    class Node : public Object
    {
    public:
      static TypeId GetTypeId (void);
      ...

This is defined in the ``node.cc`` file as follows:::

    TypeId 
    Node::GetTypeId (void)
    {
      static TypeId tid = TypeId ("ns3::Node")
        .SetParent<Object> ()
        .AddConstructor<Node> ()
        .AddAttribute ("DeviceList", "The list of devices associated to this Node.",
                       ObjectVectorValue (),
                       MakeObjectVectorAccessor (&Node::m_devices),
                       MakeObjectVectorChecker<NetDevice> ())
        .AddAttribute ("ApplicationList", "The list of applications associated to this Node.",
                       ObjectVectorValue (),
                       MakeObjectVectorAccessor (&Node::m_applications),
                       MakeObjectVectorChecker<Application> ())
        .AddAttribute ("Id", "The id (unique integer) of this Node.",
                       TypeId::ATTR_GET, // allow only getting it.
                       UintegerValue (0),
                       MakeUintegerAccessor (&Node::m_id),
                       MakeUintegerChecker<uint32_t> ())
        ;
      return tid;
    }

Consider the TypeId of an |ns3| ``Object`` class as an extended form of run time
type information (RTTI). The C++ language includes a simple kind of RTTI in
order to support ``dynamic_cast`` and ``typeid`` operators.

The "``.SetParent<Object> ()``" call in the declaration above is used in
conjunction with our object aggregation mechanisms to allow safe up- and
down-casting in inheritance trees during ``GetObject``.

The "``.AddConstructor<Node> ()``" call is used in conjunction with our abstract
object factory mechanisms to allow us to construct C++ objects without forcing a
user to know the concrete class of the object she is building.

The three calls to "``.AddAttribute``" associate a given string with a strongly
typed value in the class. Notice that you must provide a help string which may
be displayed, for example, via command line processors. Each ``Attribute`` is
associated with mechanisms for accessing the underlying member variable in the
object (for example, ``MakeUintegerAccessor`` tells the generic ``Attribute``
code how to get to the node ID above). There are also "Checker" methods which
are used to validate values.

When users want to create Nodes, they will usually call some form of 
``CreateObject``,::

    Ptr<Node> n = CreateObject<Node> ();

or more abstractly, using an object factory, you can create a ``Node`` object
without even knowing the concrete C++ type::

    ObjectFactory factory;
    const std::string typeId = "ns3::Node'';
    factory.SetTypeId (typeId);
    Ptr<Object> node = factory.Create <Object> ();

Both of these methods result in fully initialized attributes being available 
in the resulting ``Object`` instances.

We next discuss how attributes (values associated with member variables or
functions of the class) are plumbed into the above TypeId.

Attribute Overview
******************

The goal of the attribute system is to organize the access of
internal member objects of a simulation. This goal arises because,
typically in simulation, users will cut and paste/modify existing
simulation scripts, or will use higher-level simulation constructs,
but often will be interested in studying or tracing particular 
internal variables.  For instance, use cases such as:

* "I want to trace the packets on the wireless interface only on the first
  access point"
* "I want to trace the value of the TCP congestion window (every time it
  changes) on a particular TCP socket"
* "I want a dump of all values that were used in my simulation."

Similarly, users may want fine-grained access to internal variables in the
simulation, or may want to broadly change the initial value used for a
particular parameter in all subsequently created objects. Finally, users may
wish to know what variables are settable and retrievable in a simulation
configuration. This is not just for direct simulation interaction on the command
line; consider also a (future) graphical user interface that would like to be
able to provide a feature whereby a user might right-click on an node on the
canvas and see a hierarchical, organized list of parameters that are settable on
the node and its constituent member objects, and help text and default values
for each parameter.

Functional overview
+++++++++++++++++++

We provide a way for users to access values deep in the system, without having
to plumb accessors (pointers) through the system and walk pointer chains to get
to them. Consider a class DropTailQueue that has a member variable that is an
unsigned integer ``m_maxPackets``; this member variable controls the depth of
the queue.  

If we look at the declaration of DropTailQueue, we see the following:::

    class DropTailQueue : public Queue {
    public:
      static TypeId GetTypeId (void);
      ...

    private:
      std::queue<Ptr<Packet> > m_packets;
      uint32_t m_maxPackets;
    };

Let's consider things that a user may want to do with the value of
m_maxPackets:

* Set a default value for the system, such that whenever a new DropTailQueue is
  created, this member is initialized to that default. 
* Set or get the value on an already instantiated queue.

The above things typically require providing Set() and Get() functions, and some
type of global default value.

In the |ns3| attribute system, these value definitions and accessor functions
are moved into the TypeId class; e.g.:::

    NS_OBJECT_ENSURE_REGISTERED (DropTailQueue);

    TypeId DropTailQueue::GetTypeId (void) 
    {
      static TypeId tid = TypeId ("ns3::DropTailQueue")
        .SetParent<Queue> ()
        .AddConstructor<DropTailQueue> ()
        .AddAttribute ("MaxPackets", 
                       "The maximum number of packets accepted by this DropTailQueue.",
                       UintegerValue (100),
                       MakeUintegerAccessor (&DropTailQueue::m_maxPackets),
                       MakeUintegerChecker<uint32_t> ())
        ;
      
      return tid;
    }

The AddAttribute() method is performing a number of things with this
value:

* Binding the variable m_maxPackets to a string "MaxPackets"
* Providing a default value (100 packets)
* Providing some help text defining the value
* Providing a "checker" (not used in this example) that can be used to set
  bounds on the allowable range of values

The key point is that now the value of this variable and its default value are
accessible in the attribute namespace, which is based on strings such as
"MaxPackets" and TypeId strings. In the next section, we will provide an example
script that shows how users may manipulate these values.

Note that initialization of the attribute relies on the macro
``NS_OBJECT_ENSURE_REGISTERED`` (DropTailQueue) being called; if you leave this
out of your new class implementation, your attributes will not be initialized
correctly.

While we have described how to create attributes, we still haven't described how
to access and manage these values. For instance, there is no ``globals.h``
header file where these are stored; attributes are stored with their classes.
Questions that naturally arise are how do users easily learn about all of the
attributes of their models, and how does a user access these attributes, or
document their values as part of the record of their simulation?

Default values and command-line arguments
+++++++++++++++++++++++++++++++++++++++++

Let's look at how a user script might access these values.  
This is based on the script found at ``samples/main-attribute-value.cc``,
with some details stripped out.::

    //
    // This is a basic example of how to use the attribute system to
    // set and get a value in the underlying system; namely, an unsigned
    // integer of the maximum number of packets in a queue
    //

    int 
    main (int argc, char *argv[])
    {

      // By default, the MaxPackets attribute has a value of 100 packets
      // (this default can be observed in the function DropTailQueue::GetTypeId)
      // 
      // Here, we set it to 80 packets.  We could use one of two value types:
      // a string-based value or a Uinteger value
      Config::SetDefault ("ns3::DropTailQueue::MaxPackets", StringValue ("80"));
      // The below function call is redundant
      Config::SetDefault ("ns3::DropTailQueue::MaxPackets", UintegerValue (80));

      // Allow the user to override any of the defaults and the above
      // SetDefaults() at run-time, via command-line arguments
      CommandLine cmd;
      cmd.Parse (argc, argv);

The main thing to notice in the above are the two calls to 
``Config::SetDefault``.  This is how we set the default value
for all subsequently instantiated DropTailQueues.  We illustrate
that two types of Value classes, a StringValue and a UintegerValue class,
can be used to assign the value to the attribute named by
"ns3::DropTailQueue::MaxPackets".

Now, we will create a few objects using the low-level API; here,
our newly created queues will not have a m_maxPackets initialized to
100 packets but to 80 packets, because of what we did above with
default values.::

    Ptr<Node> n0 = CreateObject<Node> ();

    Ptr<PointToPointNetDevice> net0 = CreateObject<PointToPointNetDevice> ();
    n0->AddDevice (net0);

    Ptr<Queue> q = CreateObject<DropTailQueue> ();
    net0->AddQueue(q);

At this point, we have created a single node (Node 0) and a single
PointToPointNetDevice (NetDevice 0) and added a DropTailQueue to it.

Now, we can manipulate the MaxPackets value of the already instantiated
DropTailQueue. Here are various ways to do that.

Pointer-based access
++++++++++++++++++++

We assume that a smart pointer (Ptr) to a relevant network device is in hand; in
the current example, it is the ``net0`` pointer. 

One way to change the value is to access a pointer to the underlying queue and
modify its attribute.
 
First, we observe that we can get a pointer to the (base class) queue via the
PointToPointNetDevice attributes, where it is called TxQueue::

    PointerValue tmp;
    net0->GetAttribute ("TxQueue", tmp);
    Ptr<Object> txQueue = tmp.GetObject ();

Using the GetObject function, we can perform a safe downcast to a DropTailQueue,
where MaxPackets is a member::

    Ptr<DropTailQueue> dtq = txQueue->GetObject <DropTailQueue> ();
    NS_ASSERT (dtq != 0);

Next, we can get the value of an attribute on this queue.  We have introduced
wrapper "Value" classes for the underlying data types, similar to Java wrappers
around these types, since the attribute system stores values and not disparate
types.  Here, the attribute value is assigned to a UintegerValue, and the Get()
method on this value produces the (unwrapped) uint32_t.::

    UintegerValue limit;
    dtq->GetAttribute ("MaxPackets", limit);
    NS_LOG_INFO ("1.  dtq limit: " << limit.Get () << " packets");
  
Note that the above downcast is not really needed; we could have done the same
using the Ptr<Queue> even though the attribute is a member of the subclass::

    txQueue->GetAttribute ("MaxPackets", limit);
    NS_LOG_INFO ("2.  txQueue limit: " << limit.Get () << " packets");

Now, let's set it to another value (60 packets)::

    txQueue->SetAttribute("MaxPackets", UintegerValue (60));
    txQueue->GetAttribute ("MaxPackets", limit);
    NS_LOG_INFO ("3.  txQueue limit changed: " << limit.Get () << " packets");

Namespace-based access
++++++++++++++++++++++

An alternative way to get at the attribute is to use the configuration
namespace.  Here, this attribute resides on a known path in this namespace; this
approach is useful if one doesn't have access to the underlying pointers and
would like to configure a specific attribute with a single statement.::

    Config::Set ("/NodeList/0/DeviceList/0/TxQueue/MaxPackets", UintegerValue (25));
    txQueue->GetAttribute ("MaxPackets", limit); 
    NS_LOG_INFO ("4.  txQueue limit changed through namespace: " << 
        limit.Get () << " packets");

We could have also used wildcards to set this value for all nodes and all net
devices (which in this simple example has the same effect as the previous
Set())::

    Config::Set ("/NodeList/*/DeviceList/*/TxQueue/MaxPackets", UintegerValue (15));
    txQueue->GetAttribute ("MaxPackets", limit); 
    NS_LOG_INFO ("5.  txQueue limit changed through wildcarded namespace: " << 
        limit.Get () << " packets");

Object Name Service-based access
++++++++++++++++++++++++++++++++

Another way to get at the attribute is to use the object name service facility.
Here, this attribute is found using a name string. This approach is useful if
one doesn't have access to the underlying pointers and it is difficult to
determine the required concrete configuration namespaced path.::

    Names::Add ("server", serverNode);
    Names::Add ("server/eth0", serverDevice);

    ...

    Config::Set ("/Names/server/eth0/TxQueue/MaxPackets", UintegerValue (25));

:ref:`Object names` for a fuller treatment of the |ns3| configuration namespace.

Setting through constructors helper classes
+++++++++++++++++++++++++++++++++++++++++++

Arbitrary combinations of attributes can be set and fetched from
the helper and low-level APIs; either from the constructors themselves:::

    Ptr<Object> p = CreateObject<MyNewObject> ("n1", v1, "n2", v2, ...);

or from the higher-level helper APIs, such as:::

    mobility.SetPositionAllocator ("GridPositionAllocator",
                                   "MinX", DoubleValue (-100.0),
                                   "MinY", DoubleValue (-100.0),
                                   "DeltaX", DoubleValue (5.0),
                                   "DeltaY", DoubleValue (20.0),
                                   "GridWidth", UintegerValue (20),
                                   "LayoutType", StringValue ("RowFirst"));

Implementation details
++++++++++++++++++++++

Value classes
~~~~~~~~~~~~~

Readers will note the new FooValue classes which are subclasses of the
AttributeValue base class. These can be thought of as an intermediate class that
can be used to convert from raw types to the Values that are used by the
attribute system. Recall that this database is holding objects of many types
with a single generic type. Conversions to this type can either be done using an
intermediate class (IntegerValue, DoubleValue for "floating point") or via
strings. Direct implicit conversion of types to Value is not really practical.
So in the above, users have a choice of using strings or values:::

    p->Set ("cwnd", StringValue ("100")); // string-based setter
    p->Set ("cwnd", IntegerValue (100)); // integer-based setter

The system provides some macros that help users declare and define
new AttributeValue subclasses for new types that they want to introduce into
the attribute system: 

* ATTRIBUTE_HELPER_HEADER
* ATTRIBUTE_HELPER_CPP

Initialization order
~~~~~~~~~~~~~~~~~~~~

Attributes in the system must not depend on the state of any other Attribute in
this system. This is because an ordering of Attribute initialization is not
specified, nor enforced, by the system. A specific example of this can be seen
in automated configuration programs such as :cpp:class:`ns3::ConfigStore`.
Although a given model may arrange it so that Attributes are initialized in a
particular order, another automatic configurator may decide independently to
change Attributes in, for example, alphabetic order.  

Because of this non-specific ordering, no Attribute in the system may have any
dependence on any other Attribute. As a corollary, Attribute setters must never
fail due to the state of another Attribute. No Attribute setter may change (set)
any other Attribute value as a result of changing its value.

This is a very strong restriction and there are cases where Attributes must set
consistently to allow correct operation. To this end we do allow for consistency
checking *when the attribute is used* (cf. NS_ASSERT_MSG or NS_ABORT_MSG).

In general, the attribute code to assign values to the underlying class member
variables is executed after an object is constructed. But what if you need the
values assigned before the constructor body executes, because you need them in
the logic of the constructor? There is a way to do this, used for example in the
class :cpp:class:`ns3::ConfigStore`: call ``ObjectBase::ConstructSelf ()`` as
follows:::

    ConfigStore::ConfigStore ()
    {
      ObjectBase::ConstructSelf (AttributeList ());
      // continue on with constructor.
    }

Extending attributes
********************

The |ns3| system will place a number of internal values under the attribute
system, but undoubtedly users will want to extend this to pick up ones we have
missed, or to add their own classes to this.

Adding an existing internal variable to the metadata system 
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Consider this variable in class TcpSocket:::

    uint32_t m_cWnd;   // Congestion window

Suppose that someone working with TCP wanted to get or set the value of that
variable using the metadata system. If it were not already provided by |ns3|,
the user could declare the following addition in the runtime metadata system (to
the TypeId declaration for TcpSocket):::

    .AddAttribute ("Congestion window", 
                   "Tcp congestion window (bytes)",
                   UintegerValue (1),
                   MakeUintegerAccessor (&TcpSocket::m_cWnd),
                   MakeUintegerChecker<uint16_t> ())

Now, the user with a pointer to the TcpSocket can perform operations such as
setting and getting the value, without having to add these functions explicitly.
Furthermore, access controls can be applied, such as allowing the parameter to
be read and not written, or bounds checking on the permissible values can be
applied.

Adding a new TypeId
+++++++++++++++++++

Here, we discuss the impact on a user who wants to add a new class to |ns3|;
what additional things must be done to hook it into this system.

We've already introduced what a TypeId definition looks like:::

    TypeId
    RandomWalk2dMobilityModel::GetTypeId (void)
    {
      static TypeId tid = TypeId ("ns3::RandomWalk2dMobilityModel")
        .SetParent<MobilityModel> ()
        .SetGroupName ("Mobility")
        .AddConstructor<RandomWalk2dMobilityModel> ()
        .AddAttribute ("Bounds",
                       "Bounds of the area to cruise.",
                       RectangleValue (Rectangle (0.0, 0.0, 100.0, 100.0)),
                       MakeRectangleAccessor (&RandomWalk2dMobilityModel::m_bounds),
                       MakeRectangleChecker ())
        .AddAttribute ("Time",
                       "Change current direction and speed after moving for this delay.",
                       TimeValue (Seconds (1.0)),
                       MakeTimeAccessor (&RandomWalk2dMobilityModel::m_modeTime),
                       MakeTimeChecker ())
        // etc (more parameters).
        ;
      return tid;
    }

The declaration for this in the class declaration is one-line public member
method:::

    public:
      static TypeId GetTypeId (void);

Typical mistakes here involve:

* Not calling the SetParent method or calling it with the wrong type
* Not calling the AddConstructor method of calling it with the wrong type
* Introducing a typographical error in the name of the TypeId in its constructor
* Not using the fully-qualified c++ typename of the enclosing c++ class as the
  name of the TypeId

None of these mistakes can be detected by the |ns3| codebase so, users
are advised to check carefully multiple times that they got these right.

Adding new class type to the attribute system
*********************************************

From the perspective of the user who writes a new class in the system and wants
to hook it in to the attribute system, there is mainly the matter of writing the
conversions to/from strings and attribute values.  Most of this can be
copy/pasted with macro-ized code.  For instance, consider class declaration for
Rectangle in the ``src/mobility/`` directory:

Header file
+++++++++++

::

    /**
     * \brief a 2d rectangle
     */
    class Rectangle
    {
      ...

      double xMin;
      double xMax;
      double yMin;
      double yMax;
    };
 
One macro call and two operators, must be added below the class declaration in
order to turn a Rectangle into a value usable by the ``Attribute`` system:::

    std::ostream &operator << (std::ostream &os, const Rectangle &rectangle);
    std::istream &operator >> (std::istream &is, Rectangle &rectangle);

    ATTRIBUTE_HELPER_HEADER (Rectangle);

Implementation file
+++++++++++++++++++

In the class definition (``.cc`` file), the code looks like this:::

    ATTRIBUTE_HELPER_CPP (Rectangle);

    std::ostream &
    operator << (std::ostream &os, const Rectangle &rectangle)
    {
      os << rectangle.xMin << "|" << rectangle.xMax << "|" << rectangle.yMin << "|"
         << rectangle.yMax;
      return os;
    }
    std::istream &
    operator >> (std::istream &is, Rectangle &rectangle)
     {
      char c1, c2, c3;
      is >> rectangle.xMin >> c1 >> rectangle.xMax >> c2 >> rectangle.yMin >> c3 
         >> rectangle.yMax;
      if (c1 != '|' ||
          c2 != '|' ||
          c3 != '|')
        {
          is.setstate (std::ios_base::failbit);
        }
      return is;
    }

These stream operators simply convert from a string representation of the
Rectangle ("xMin|xMax|yMin|yMax") to the underlying Rectangle, and the modeler
must specify these operators and the string syntactical representation of an
instance of the new class.

ConfigStore
***********

**Feedback requested:**  This is an experimental feature of |ns3|.  It is found
in ``src/contrib`` and not in the main tree.  If you like this feature and
would like to provide feedback on it, please email us.

Values for |ns3| attributes can be stored in an ASCII or XML text file and
loaded into a future simulation.  This feature is known as the |ns3|
ConfigStore.  The ConfigStore code is in ``src/contrib/``.  It is not yet
main-tree code, because we are seeking some user feedback and experience with
this. 

We can explore this system by using an example. Copy the ``csma-bridge.cc``
file to the scratch directory:::

    cp examples/csma-bridge.cc scratch/
    ./waf

Let's edit it to add the ConfigStore feature. First, add an include statement to
include the contrib module, and then add these lines:::

    #include "contrib-module.h"
    ...
    int main (...)
    {
      // setup topology

      // Invoke just before entering Simulator::Run ()
      ConfigStore config;
      config.ConfigureDefaults ();
      config.ConfigureAttributes ();

      Simulator::Run ();
    }

There are three attributes that govern the behavior of the ConfigStore: "Mode",
"Filename", and "FileFormat".  The Mode (default "None") configures whether
|ns3| should load configuration from a previously saved file (specify
"Mode=Load") or save it to a file (specify "Mode=Save").  The Filename (default
"") is where the ConfigStore should store its output data.  The FileFormat
(default "RawText") governs whether the ConfigStore format is Xml or RawText
format.

So, using the above modified program, try executing the following waf command
and ::

    ./waf --command-template="%s --ns3::ConfigStore::Filename=csma-bridge-config.xml
    --ns3::ConfigStore::Mode=Save --ns3::ConfigStore::FileFormat=Xml" --run scratch/csma-bridge

After running, you can open the csma-bridge-config.xml file and it will
display the configuration that was applied to your simulation; e.g.::

    <?xml version="1.0" encoding="UTF-8"?>
    <ns3>
     <default name="ns3::V4Ping::Remote" value="102.102.102.102"/>
     <default name="ns3::MsduStandardAggregator::MaxAmsduSize" value="7935"/>
     <default name="ns3::EdcaTxopN::MinCw" value="31"/>
     <default name="ns3::EdcaTxopN::MaxCw" value="1023"/>
     <default name="ns3::EdcaTxopN::Aifsn" value="3"/>
     <default name="ns3::StaWifiMac::ProbeRequestTimeout" value="50000000ns"/>
     <default name="ns3::StaWifiMac::AssocRequestTimeout" value="500000000ns"/>
     <default name="ns3::StaWifiMac::MaxMissedBeacons" value="10"/>
     <default name="ns3::StaWifiMac::ActiveProbing" value="false"/>
    ...

This file can be archived with your simulation script and output data.

While it is possible to generate a sample config file and lightly edit it to
change a couple of values, there are cases where this process will not work
because the same value on the same object can appear multiple times in the same
automatically-generated configuration file under different configuration paths.

As such, the best way to use this class is to use it to generate an initial
configuration file, extract from that configuration file only the strictly
necessary elements, and move these minimal elements to a new configuration file
which can then safely be edited and loaded in a subsequent simulation run. 

When the ConfigStore object is instantiated, its attributes Filename, Mode, and
FileFormat must be set, either via command-line or via program statements.  

As a more complicated example, let's assume that we want to read in a
configuration of defaults from an input file named "input-defaults.xml", and
write out the resulting attributes to a separate file called
"output-attributes.xml".  (Note-- to get this input xml file to begin with, it
is sometimes helpful to run the program to generate an output xml file first,
then hand-edit that file and re-input it for the next simulation run).::

    #include "contrib-module.h"
    ...
    int main (...)
    {

      Config::SetDefault ("ns3::ConfigStore::Filename", StringValue ("input-defaults.xml"));
      Config::SetDefault ("ns3::ConfigStore::Mode", StringValue ("Load"));
      Config::SetDefault ("ns3::ConfigStore::FileFormat", StringValue ("Xml"));
      ConfigStore inputConfig;
      inputConfig.ConfigureDefaults ();
      
      //
      // Allow the user to override any of the defaults and the above Bind() at
      // run-time, via command-line arguments
      //
      CommandLine cmd;
      cmd.Parse (argc, argv);

      // setup topology
      ...

      // Invoke just before entering Simulator::Run ()
      Config::SetDefault ("ns3::ConfigStore::Filename", StringValue ("output-attributes.xml"));
      Config::SetDefault ("ns3::ConfigStore::Mode", StringValue ("Save"));
      ConfigStore outputConfig;
      outputConfig.ConfigureAttributes ();
      Simulator::Run ();
    }

GTK-based ConfigStore
+++++++++++++++++++++

There is a GTK-based front end for the ConfigStore.  This allows users to use a
GUI to access and change variables.  Screenshots of this feature are available
in the `|ns3| Overview <http://www.nsnam.org/docs/ns-3-overview.pdf>`_
presentation.

To use this feature, one must install libgtk and libgtk-dev; an example
Ubuntu installation command is:::

    sudo apt-get install libgtk2.0-0 libgtk2.0-dev

To check whether it is configured or not, check the output of the
./waf configure step:::

    ---- Summary of optional NS-3 features:
    Threading Primitives          : enabled
    Real Time Simulator           : enabled
    GtkConfigStore                : not enabled (library 'gtk+-2.0 >= 2.12' not found)

In the above example, it was not enabled, so it cannot be used until a suitable
version is installed and ./waf configure; ./waf is rerun.

Usage is almost the same as the non-GTK-based version, but there
are no ConfigStore attributes involved:::

  // Invoke just before entering Simulator::Run ()
  GtkConfigStore config;
  config.ConfigureDefaults ();
  config.ConfigureAttributes ();

Now, when you run the script, a GUI should pop up, allowing you to open menus of
attributes on different nodes/objects, and then launch the simulation execution
when you are done.  

Future work
+++++++++++
There are a couple of possible improvements:
* save a unique version number with date and time at start of file
* save rng initial seed somewhere.
* make each RandomVariable serialize its own initial seed and re-read it later
* add the default values
