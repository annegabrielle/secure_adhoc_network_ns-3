from pybindgen import Module, FileCodeSink, param, retval, cppclass, typehandlers

def register_types(module):
    root_module = module.get_root()
    
    ## event-id.h: ns3::EventId [class]
    module.add_class('EventId')
    ## high-precision-double.h: ns3::HighPrecision [class]
    module.add_class('HighPrecision')
    ## simulator.h: ns3::Simulator [class]
    module.add_class('Simulator', is_singleton=True)
    ## nstime.h: ns3::Time [class]
    module.add_class('Time')
    ## nstime.h: ns3::Time::Unit [enumeration]
    module.add_enum('Unit', ['S', 'MS', 'US', 'NS', 'PS', 'FS', 'LAST'], outer_class=root_module['ns3::Time'])
    ## time-base.h: ns3::TimeBase [class]
    module.add_class('TimeBase')
    ## time-base.h: ns3::TimeBase::Unit [enumeration]
    module.add_enum('Unit', ['S', 'MS', 'US', 'NS', 'PS', 'FS', 'LAST'], outer_class=root_module['ns3::TimeBase'])
    ## timer.h: ns3::Timer [class]
    module.add_class('Timer')
    ## timer.h: ns3::Timer::DestroyPolicy [enumeration]
    module.add_enum('DestroyPolicy', ['CANCEL_ON_DESTROY', 'REMOVE_ON_DESTROY', 'CHECK_ON_DESTROY'], outer_class=root_module['ns3::Timer'])
    ## timer.h: ns3::Timer::State [enumeration]
    module.add_enum('State', ['RUNNING', 'EXPIRED', 'SUSPENDED'], outer_class=root_module['ns3::Timer'])
    ## timer-impl.h: ns3::TimerImpl [class]
    module.add_class('TimerImpl', allow_subclassing=True)
    ## traced-value.h: ns3::TracedValue<ns3::Time> [class]
    module.add_class('TracedValue', template_parameters=['ns3::Time'])
    ## traced-value.h: ns3::TracedValue<ns3::Time> [class]
    root_module['ns3::TracedValue< ns3::Time >'].implicitly_converts_to(root_module['ns3::Time'])
    ## watchdog.h: ns3::Watchdog [class]
    module.add_class('Watchdog')
    ## nstime.h: ns3::Scalar [class]
    module.add_class('Scalar')
    ## nstime.h: ns3::Scalar [class]
    root_module['ns3::Scalar'].implicitly_converts_to(root_module['ns3::Time'])
    ## scheduler.h: ns3::Scheduler [class]
    module.add_class('Scheduler', parent=root_module['ns3::Object'])
    ## scheduler.h: ns3::Scheduler::Event [struct]
    module.add_class('Event', outer_class=root_module['ns3::Scheduler'])
    ## scheduler.h: ns3::Scheduler::EventKey [struct]
    module.add_class('EventKey', outer_class=root_module['ns3::Scheduler'])
    ## simple-ref-count.h: ns3::SimpleRefCount<ns3::EventImpl, ns3::empty, ns3::DefaultDeleter<ns3::EventImpl> > [class]
    module.add_class('SimpleRefCount', automatic_type_narrowing=True, template_parameters=['ns3::EventImpl', 'ns3::empty', 'ns3::DefaultDeleter<ns3::EventImpl>'], parent=root_module['ns3::empty'], memory_policy=cppclass.ReferenceCountingMethodsPolicy(incref_method='Ref', decref_method='Unref', peekref_method='GetReferenceCount'))
    ## simulator-impl.h: ns3::SimulatorImpl [class]
    module.add_class('SimulatorImpl', parent=root_module['ns3::Object'])
    ## synchronizer.h: ns3::Synchronizer [class]
    module.add_class('Synchronizer', parent=root_module['ns3::Object'])
    ## wall-clock-synchronizer.h: ns3::WallClockSynchronizer [class]
    module.add_class('WallClockSynchronizer', parent=root_module['ns3::Synchronizer'])
    ## calendar-scheduler.h: ns3::CalendarScheduler [class]
    module.add_class('CalendarScheduler', parent=root_module['ns3::Scheduler'])
    ## default-simulator-impl.h: ns3::DefaultSimulatorImpl [class]
    module.add_class('DefaultSimulatorImpl', parent=root_module['ns3::SimulatorImpl'])
    ## event-impl.h: ns3::EventImpl [class]
    module.add_class('EventImpl', parent=root_module['ns3::SimpleRefCount< ns3::EventImpl, ns3::empty, ns3::DefaultDeleter<ns3::EventImpl> >'])
    ## heap-scheduler.h: ns3::HeapScheduler [class]
    module.add_class('HeapScheduler', parent=root_module['ns3::Scheduler'])
    ## list-scheduler.h: ns3::ListScheduler [class]
    module.add_class('ListScheduler', parent=root_module['ns3::Scheduler'])
    ## map-scheduler.h: ns3::MapScheduler [class]
    module.add_class('MapScheduler', parent=root_module['ns3::Scheduler'])
    ## ns2-calendar-scheduler.h: ns3::Ns2CalendarScheduler [class]
    module.add_class('Ns2CalendarScheduler', parent=root_module['ns3::Scheduler'])
    ## realtime-simulator-impl.h: ns3::RealtimeSimulatorImpl [class]
    module.add_class('RealtimeSimulatorImpl', parent=root_module['ns3::SimulatorImpl'])
    ## realtime-simulator-impl.h: ns3::RealtimeSimulatorImpl::SynchronizationMode [enumeration]
    module.add_enum('SynchronizationMode', ['SYNC_BEST_EFFORT', 'SYNC_HARD_LIMIT'], outer_class=root_module['ns3::RealtimeSimulatorImpl'])
    ## nstime.h: ns3::TimeChecker [class]
    module.add_class('TimeChecker', parent=root_module['ns3::AttributeChecker'])
    ## nstime.h: ns3::TimeValue [class]
    module.add_class('TimeValue', parent=root_module['ns3::AttributeValue'])
    typehandlers.add_type_alias('ns3::Time', 'ns3::TimeInvert')
    typehandlers.add_type_alias('ns3::Time*', 'ns3::TimeInvert*')
    typehandlers.add_type_alias('ns3::Time&', 'ns3::TimeInvert&')
    module.add_typedef(root_module['ns3::Time'], 'TimeInvert')
    typehandlers.add_type_alias('ns3::Time', 'ns3::TimeSquare')
    typehandlers.add_type_alias('ns3::Time*', 'ns3::TimeSquare*')
    typehandlers.add_type_alias('ns3::Time&', 'ns3::TimeSquare&')
    module.add_typedef(root_module['ns3::Time'], 'TimeSquare')
    
    ## Register a nested module for the namespace Config
    
    nested_module = module.add_cpp_namespace('Config')
    register_types_ns3_Config(nested_module)
    
    
    ## Register a nested module for the namespace FatalImpl
    
    nested_module = module.add_cpp_namespace('FatalImpl')
    register_types_ns3_FatalImpl(nested_module)
    
    
    ## Register a nested module for the namespace addressUtils
    
    nested_module = module.add_cpp_namespace('addressUtils')
    register_types_ns3_addressUtils(nested_module)
    
    
    ## Register a nested module for the namespace aodv
    
    nested_module = module.add_cpp_namespace('aodv')
    register_types_ns3_aodv(nested_module)
    
    
    ## Register a nested module for the namespace dot11s
    
    nested_module = module.add_cpp_namespace('dot11s')
    register_types_ns3_dot11s(nested_module)
    
    
    ## Register a nested module for the namespace dsdv
    
    nested_module = module.add_cpp_namespace('dsdv')
    register_types_ns3_dsdv(nested_module)
    
    
    ## Register a nested module for the namespace flame
    
    nested_module = module.add_cpp_namespace('flame')
    register_types_ns3_flame(nested_module)
    
    
    ## Register a nested module for the namespace internal
    
    nested_module = module.add_cpp_namespace('internal')
    register_types_ns3_internal(nested_module)
    
    
    ## Register a nested module for the namespace olsr
    
    nested_module = module.add_cpp_namespace('olsr')
    register_types_ns3_olsr(nested_module)
    

def register_types_ns3_Config(module):
    root_module = module.get_root()
    

def register_types_ns3_FatalImpl(module):
    root_module = module.get_root()
    

def register_types_ns3_addressUtils(module):
    root_module = module.get_root()
    

def register_types_ns3_aodv(module):
    root_module = module.get_root()
    

def register_types_ns3_dot11s(module):
    root_module = module.get_root()
    

def register_types_ns3_dsdv(module):
    root_module = module.get_root()
    

def register_types_ns3_flame(module):
    root_module = module.get_root()
    

def register_types_ns3_internal(module):
    root_module = module.get_root()
    

def register_types_ns3_olsr(module):
    root_module = module.get_root()
    

def register_methods(root_module):
    register_Ns3EventId_methods(root_module, root_module['ns3::EventId'])
    register_Ns3HighPrecision_methods(root_module, root_module['ns3::HighPrecision'])
    register_Ns3Simulator_methods(root_module, root_module['ns3::Simulator'])
    register_Ns3Time_methods(root_module, root_module['ns3::Time'])
    register_Ns3TimeBase_methods(root_module, root_module['ns3::TimeBase'])
    register_Ns3Timer_methods(root_module, root_module['ns3::Timer'])
    register_Ns3TimerImpl_methods(root_module, root_module['ns3::TimerImpl'])
    register_Ns3Watchdog_methods(root_module, root_module['ns3::Watchdog'])
    register_Ns3Scalar_methods(root_module, root_module['ns3::Scalar'])
    register_Ns3Scheduler_methods(root_module, root_module['ns3::Scheduler'])
    register_Ns3SchedulerEvent_methods(root_module, root_module['ns3::Scheduler::Event'])
    register_Ns3SchedulerEventKey_methods(root_module, root_module['ns3::Scheduler::EventKey'])
    register_Ns3SimulatorImpl_methods(root_module, root_module['ns3::SimulatorImpl'])
    register_Ns3Synchronizer_methods(root_module, root_module['ns3::Synchronizer'])
    register_Ns3WallClockSynchronizer_methods(root_module, root_module['ns3::WallClockSynchronizer'])
    register_Ns3CalendarScheduler_methods(root_module, root_module['ns3::CalendarScheduler'])
    register_Ns3DefaultSimulatorImpl_methods(root_module, root_module['ns3::DefaultSimulatorImpl'])
    register_Ns3EventImpl_methods(root_module, root_module['ns3::EventImpl'])
    register_Ns3HeapScheduler_methods(root_module, root_module['ns3::HeapScheduler'])
    register_Ns3ListScheduler_methods(root_module, root_module['ns3::ListScheduler'])
    register_Ns3MapScheduler_methods(root_module, root_module['ns3::MapScheduler'])
    register_Ns3Ns2CalendarScheduler_methods(root_module, root_module['ns3::Ns2CalendarScheduler'])
    register_Ns3RealtimeSimulatorImpl_methods(root_module, root_module['ns3::RealtimeSimulatorImpl'])
    register_Ns3TimeChecker_methods(root_module, root_module['ns3::TimeChecker'])
    register_Ns3TimeValue_methods(root_module, root_module['ns3::TimeValue'])
    return

def register_Ns3EventId_methods(root_module, cls):
    cls.add_binary_comparison_operator('!=')
    cls.add_binary_comparison_operator('==')
    ## event-id.h: ns3::EventId::EventId(ns3::EventId const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::EventId const &', 'arg0')])
    ## event-id.h: ns3::EventId::EventId() [constructor]
    cls.add_constructor([])
    ## event-id.h: ns3::EventId::EventId(ns3::Ptr<ns3::EventImpl> const & impl, uint64_t ts, uint32_t context, uint32_t uid) [constructor]
    cls.add_constructor([param('ns3::Ptr< ns3::EventImpl > const &', 'impl'), param('uint64_t', 'ts'), param('uint32_t', 'context'), param('uint32_t', 'uid')])
    ## event-id.h: void ns3::EventId::Cancel() [member function]
    cls.add_method('Cancel', 
                   'void', 
                   [])
    ## event-id.h: uint32_t ns3::EventId::GetContext() const [member function]
    cls.add_method('GetContext', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## event-id.h: uint64_t ns3::EventId::GetTs() const [member function]
    cls.add_method('GetTs', 
                   'uint64_t', 
                   [], 
                   is_const=True)
    ## event-id.h: uint32_t ns3::EventId::GetUid() const [member function]
    cls.add_method('GetUid', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## event-id.h: bool ns3::EventId::IsExpired() const [member function]
    cls.add_method('IsExpired', 
                   'bool', 
                   [], 
                   is_const=True)
    ## event-id.h: bool ns3::EventId::IsRunning() const [member function]
    cls.add_method('IsRunning', 
                   'bool', 
                   [], 
                   is_const=True)
    ## event-id.h: ns3::EventImpl * ns3::EventId::PeekEventImpl() const [member function]
    cls.add_method('PeekEventImpl', 
                   'ns3::EventImpl *', 
                   [], 
                   is_const=True)
    return

def register_Ns3HighPrecision_methods(root_module, cls):
    cls.add_output_stream_operator()
    ## high-precision-double.h: ns3::HighPrecision::HighPrecision(ns3::HighPrecision const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::HighPrecision const &', 'arg0')])
    ## high-precision-double.h: ns3::HighPrecision::HighPrecision() [constructor]
    cls.add_constructor([])
    ## high-precision-double.h: ns3::HighPrecision::HighPrecision(int64_t value, bool dummy) [constructor]
    cls.add_constructor([param('int64_t', 'value'), param('bool', 'dummy')])
    ## high-precision-double.h: ns3::HighPrecision::HighPrecision(double value) [constructor]
    cls.add_constructor([param('double', 'value')])
    ## high-precision-double.h: void ns3::HighPrecision::Add(ns3::HighPrecision const & o) [member function]
    cls.add_method('Add', 
                   'void', 
                   [param('ns3::HighPrecision const &', 'o')])
    ## high-precision-double.h: int ns3::HighPrecision::Compare(ns3::HighPrecision const & o) const [member function]
    cls.add_method('Compare', 
                   'int', 
                   [param('ns3::HighPrecision const &', 'o')], 
                   is_const=True)
    ## high-precision-double.h: void ns3::HighPrecision::Div(ns3::HighPrecision const & o) [member function]
    cls.add_method('Div', 
                   'void', 
                   [param('ns3::HighPrecision const &', 'o')])
    ## high-precision-double.h: double ns3::HighPrecision::GetDouble() const [member function]
    cls.add_method('GetDouble', 
                   'double', 
                   [], 
                   is_const=True)
    ## high-precision-double.h: int64_t ns3::HighPrecision::GetHigh() const [member function]
    cls.add_method('GetHigh', 
                   'int64_t', 
                   [], 
                   is_const=True)
    ## high-precision-double.h: int64_t ns3::HighPrecision::GetInteger() const [member function]
    cls.add_method('GetInteger', 
                   'int64_t', 
                   [], 
                   is_const=True)
    ## high-precision-double.h: uint64_t ns3::HighPrecision::GetLow() const [member function]
    cls.add_method('GetLow', 
                   'uint64_t', 
                   [], 
                   is_const=True)
    ## high-precision-double.h: static ns3::HighPrecision ns3::HighPrecision::Invert(uint64_t v) [member function]
    cls.add_method('Invert', 
                   'ns3::HighPrecision', 
                   [param('uint64_t', 'v')], 
                   is_static=True)
    ## high-precision-double.h: void ns3::HighPrecision::Mul(ns3::HighPrecision const & o) [member function]
    cls.add_method('Mul', 
                   'void', 
                   [param('ns3::HighPrecision const &', 'o')])
    ## high-precision-double.h: void ns3::HighPrecision::MulByInvert(ns3::HighPrecision const & o) [member function]
    cls.add_method('MulByInvert', 
                   'void', 
                   [param('ns3::HighPrecision const &', 'o')])
    ## high-precision-double.h: void ns3::HighPrecision::Sub(ns3::HighPrecision const & o) [member function]
    cls.add_method('Sub', 
                   'void', 
                   [param('ns3::HighPrecision const &', 'o')])
    ## high-precision-double.h: static ns3::HighPrecision ns3::HighPrecision::Zero() [member function]
    cls.add_method('Zero', 
                   'ns3::HighPrecision', 
                   [], 
                   is_static=True)
    return

def register_Ns3Simulator_methods(root_module, cls):
    ## simulator.h: ns3::Simulator::Simulator(ns3::Simulator const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Simulator const &', 'arg0')])
    ## simulator.h: static void ns3::Simulator::Cancel(ns3::EventId const & id) [member function]
    cls.add_method('Cancel', 
                   'void', 
                   [param('ns3::EventId const &', 'id')], 
                   is_static=True)
    ## simulator.h: static void ns3::Simulator::Destroy() [member function]
    cls.add_method('Destroy', 
                   'void', 
                   [], 
                   is_static=True)
    ## simulator.h: static uint32_t ns3::Simulator::GetContext() [member function]
    cls.add_method('GetContext', 
                   'uint32_t', 
                   [], 
                   is_static=True)
    ## simulator.h: static ns3::Time ns3::Simulator::GetDelayLeft(ns3::EventId const & id) [member function]
    cls.add_method('GetDelayLeft', 
                   'ns3::Time', 
                   [param('ns3::EventId const &', 'id')], 
                   is_static=True)
    ## simulator.h: static ns3::Ptr<ns3::SimulatorImpl> ns3::Simulator::GetImplementation() [member function]
    cls.add_method('GetImplementation', 
                   'ns3::Ptr< ns3::SimulatorImpl >', 
                   [], 
                   is_static=True)
    ## simulator.h: static ns3::Time ns3::Simulator::GetMaximumSimulationTime() [member function]
    cls.add_method('GetMaximumSimulationTime', 
                   'ns3::Time', 
                   [], 
                   is_static=True)
    ## simulator.h: static uint32_t ns3::Simulator::GetSystemId() [member function]
    cls.add_method('GetSystemId', 
                   'uint32_t', 
                   [], 
                   is_static=True)
    ## simulator.h: static bool ns3::Simulator::IsExpired(ns3::EventId const & id) [member function]
    cls.add_method('IsExpired', 
                   'bool', 
                   [param('ns3::EventId const &', 'id')], 
                   is_static=True)
    ## simulator.h: static bool ns3::Simulator::IsFinished() [member function]
    cls.add_method('IsFinished', 
                   'bool', 
                   [], 
                   is_static=True)
    ## simulator.h: static ns3::Time ns3::Simulator::Next() [member function]
    cls.add_method('Next', 
                   'ns3::Time', 
                   [], 
                   is_static=True, deprecated=True)
    ## simulator.h: static ns3::Time ns3::Simulator::Now() [member function]
    cls.add_method('Now', 
                   'ns3::Time', 
                   [], 
                   is_static=True)
    ## simulator.h: static void ns3::Simulator::Remove(ns3::EventId const & id) [member function]
    cls.add_method('Remove', 
                   'void', 
                   [param('ns3::EventId const &', 'id')], 
                   is_static=True)
    ## simulator.h: static void ns3::Simulator::RunOneEvent() [member function]
    cls.add_method('RunOneEvent', 
                   'void', 
                   [], 
                   is_static=True, deprecated=True)
    ## simulator.h: static void ns3::Simulator::SetImplementation(ns3::Ptr<ns3::SimulatorImpl> impl) [member function]
    cls.add_method('SetImplementation', 
                   'void', 
                   [param('ns3::Ptr< ns3::SimulatorImpl >', 'impl')], 
                   is_static=True)
    ## simulator.h: static void ns3::Simulator::SetScheduler(ns3::ObjectFactory schedulerFactory) [member function]
    cls.add_method('SetScheduler', 
                   'void', 
                   [param('ns3::ObjectFactory', 'schedulerFactory')], 
                   is_static=True)
    ## simulator.h: static void ns3::Simulator::Stop() [member function]
    cls.add_method('Stop', 
                   'void', 
                   [], 
                   is_static=True)
    ## simulator.h: static void ns3::Simulator::Stop(ns3::Time const & time) [member function]
    cls.add_method('Stop', 
                   'void', 
                   [param('ns3::Time const &', 'time')], 
                   is_static=True)
    return

def register_Ns3Time_methods(root_module, cls):
    cls.add_binary_comparison_operator('!=')
    cls.add_inplace_numeric_operator('*=', param('ns3::Time const &', 'right'))
    cls.add_inplace_numeric_operator('+=', param('ns3::Time const &', 'right'))
    cls.add_inplace_numeric_operator('-=', param('ns3::Time const &', 'right'))
    cls.add_inplace_numeric_operator('/=', param('ns3::Time const &', 'right'))
    cls.add_output_stream_operator()
    cls.add_binary_comparison_operator('<=')
    cls.add_binary_comparison_operator('==')
    cls.add_binary_comparison_operator('>=')
    cls.add_binary_numeric_operator('*', root_module['ns3::Time'], root_module['ns3::Time'], param('ns3::Time const &', 'right'))
    cls.add_binary_numeric_operator('+', root_module['ns3::Time'], root_module['ns3::Time'], param('ns3::Time const &', 'right'))
    cls.add_binary_numeric_operator('-', root_module['ns3::Time'], root_module['ns3::Time'], param('ns3::Time const &', 'right'))
    cls.add_binary_numeric_operator('/', root_module['ns3::Time'], root_module['ns3::Time'], param('ns3::Time const &', 'right'))
    cls.add_binary_comparison_operator('<')
    cls.add_binary_comparison_operator('>')
    ## nstime.h: ns3::Time::Time() [constructor]
    cls.add_constructor([])
    ## nstime.h: ns3::Time::Time(ns3::Time const & o) [copy constructor]
    cls.add_constructor([param('ns3::Time const &', 'o')])
    ## nstime.h: ns3::Time::Time(ns3::HighPrecision const & data) [constructor]
    cls.add_constructor([param('ns3::HighPrecision const &', 'data')])
    ## nstime.h: ns3::Time::Time(std::string const & s) [constructor]
    cls.add_constructor([param('std::string const &', 's')])
    ## nstime.h: int ns3::Time::Compare(ns3::Time const & o) const [member function]
    cls.add_method('Compare', 
                   'int', 
                   [param('ns3::Time const &', 'o')], 
                   is_const=True)
    ## nstime.h: static ns3::Time ns3::Time::FromDouble(double value, ns3::Time::Unit timeUnit) [member function]
    cls.add_method('FromDouble', 
                   'ns3::Time', 
                   [param('double', 'value'), param('ns3::Time::Unit', 'timeUnit')], 
                   is_static=True)
    ## nstime.h: static ns3::Time ns3::Time::FromInteger(uint64_t value, ns3::Time::Unit timeUnit) [member function]
    cls.add_method('FromInteger', 
                   'ns3::Time', 
                   [param('uint64_t', 'value'), param('ns3::Time::Unit', 'timeUnit')], 
                   is_static=True)
    ## nstime.h: int64_t ns3::Time::GetFemtoSeconds() const [member function]
    cls.add_method('GetFemtoSeconds', 
                   'int64_t', 
                   [], 
                   is_const=True)
    ## nstime.h: ns3::HighPrecision const & ns3::Time::GetHighPrecision() const [member function]
    cls.add_method('GetHighPrecision', 
                   'ns3::HighPrecision const &', 
                   [], 
                   is_const=True)
    ## nstime.h: int64_t ns3::Time::GetMicroSeconds() const [member function]
    cls.add_method('GetMicroSeconds', 
                   'int64_t', 
                   [], 
                   is_const=True)
    ## nstime.h: int64_t ns3::Time::GetMilliSeconds() const [member function]
    cls.add_method('GetMilliSeconds', 
                   'int64_t', 
                   [], 
                   is_const=True)
    ## nstime.h: int64_t ns3::Time::GetNanoSeconds() const [member function]
    cls.add_method('GetNanoSeconds', 
                   'int64_t', 
                   [], 
                   is_const=True)
    ## nstime.h: int64_t ns3::Time::GetPicoSeconds() const [member function]
    cls.add_method('GetPicoSeconds', 
                   'int64_t', 
                   [], 
                   is_const=True)
    ## nstime.h: static ns3::Time::Unit ns3::Time::GetResolution() [member function]
    cls.add_method('GetResolution', 
                   'ns3::Time::Unit', 
                   [], 
                   is_static=True)
    ## nstime.h: double ns3::Time::GetSeconds() const [member function]
    cls.add_method('GetSeconds', 
                   'double', 
                   [], 
                   is_const=True)
    ## nstime.h: int64_t ns3::Time::GetTimeStep() const [member function]
    cls.add_method('GetTimeStep', 
                   'int64_t', 
                   [], 
                   is_const=True)
    ## nstime.h: bool ns3::Time::IsNegative() const [member function]
    cls.add_method('IsNegative', 
                   'bool', 
                   [], 
                   is_const=True)
    ## nstime.h: bool ns3::Time::IsPositive() const [member function]
    cls.add_method('IsPositive', 
                   'bool', 
                   [], 
                   is_const=True)
    ## nstime.h: bool ns3::Time::IsStrictlyNegative() const [member function]
    cls.add_method('IsStrictlyNegative', 
                   'bool', 
                   [], 
                   is_const=True)
    ## nstime.h: bool ns3::Time::IsStrictlyPositive() const [member function]
    cls.add_method('IsStrictlyPositive', 
                   'bool', 
                   [], 
                   is_const=True)
    ## nstime.h: bool ns3::Time::IsZero() const [member function]
    cls.add_method('IsZero', 
                   'bool', 
                   [], 
                   is_const=True)
    ## nstime.h: ns3::HighPrecision * ns3::Time::PeekHighPrecision() [member function]
    cls.add_method('PeekHighPrecision', 
                   'ns3::HighPrecision *', 
                   [])
    ## nstime.h: static void ns3::Time::SetResolution(ns3::Time::Unit resolution) [member function]
    cls.add_method('SetResolution', 
                   'void', 
                   [param('ns3::Time::Unit', 'resolution')], 
                   is_static=True)
    ## nstime.h: static double ns3::Time::ToDouble(ns3::Time const & time, ns3::Time::Unit timeUnit) [member function]
    cls.add_method('ToDouble', 
                   'double', 
                   [param('ns3::Time const &', 'time'), param('ns3::Time::Unit', 'timeUnit')], 
                   is_static=True)
    ## nstime.h: static uint64_t ns3::Time::ToInteger(ns3::Time const & time, ns3::Time::Unit timeUnit) [member function]
    cls.add_method('ToInteger', 
                   'uint64_t', 
                   [param('ns3::Time const &', 'time'), param('ns3::Time::Unit', 'timeUnit')], 
                   is_static=True)
    return

def register_Ns3TimeBase_methods(root_module, cls):
    ## time-base.h: ns3::TimeBase::TimeBase() [constructor]
    cls.add_constructor([])
    ## time-base.h: ns3::TimeBase::TimeBase(ns3::TimeBase const & o) [copy constructor]
    cls.add_constructor([param('ns3::TimeBase const &', 'o')])
    ## time-base.h: ns3::TimeBase::TimeBase(ns3::HighPrecision const & data) [constructor]
    cls.add_constructor([param('ns3::HighPrecision const &', 'data')])
    ## time-base.h: static ns3::TimeBase ns3::TimeBase::FromDouble(double value, ns3::TimeBase::Unit timeUnit) [member function]
    cls.add_method('FromDouble', 
                   'ns3::TimeBase', 
                   [param('double', 'value'), param('ns3::TimeBase::Unit', 'timeUnit')], 
                   is_static=True)
    ## time-base.h: static ns3::TimeBase ns3::TimeBase::FromInteger(uint64_t value, ns3::TimeBase::Unit timeUnit) [member function]
    cls.add_method('FromInteger', 
                   'ns3::TimeBase', 
                   [param('uint64_t', 'value'), param('ns3::TimeBase::Unit', 'timeUnit')], 
                   is_static=True)
    ## time-base.h: ns3::HighPrecision const & ns3::TimeBase::GetHighPrecision() const [member function]
    cls.add_method('GetHighPrecision', 
                   'ns3::HighPrecision const &', 
                   [], 
                   is_const=True)
    ## time-base.h: static ns3::TimeBase::Unit ns3::TimeBase::GetResolution() [member function]
    cls.add_method('GetResolution', 
                   'ns3::TimeBase::Unit', 
                   [], 
                   is_static=True)
    ## time-base.h: bool ns3::TimeBase::IsNegative() const [member function]
    cls.add_method('IsNegative', 
                   'bool', 
                   [], 
                   is_const=True)
    ## time-base.h: bool ns3::TimeBase::IsPositive() const [member function]
    cls.add_method('IsPositive', 
                   'bool', 
                   [], 
                   is_const=True)
    ## time-base.h: bool ns3::TimeBase::IsStrictlyNegative() const [member function]
    cls.add_method('IsStrictlyNegative', 
                   'bool', 
                   [], 
                   is_const=True)
    ## time-base.h: bool ns3::TimeBase::IsStrictlyPositive() const [member function]
    cls.add_method('IsStrictlyPositive', 
                   'bool', 
                   [], 
                   is_const=True)
    ## time-base.h: bool ns3::TimeBase::IsZero() const [member function]
    cls.add_method('IsZero', 
                   'bool', 
                   [], 
                   is_const=True)
    ## time-base.h: ns3::HighPrecision * ns3::TimeBase::PeekHighPrecision() [member function]
    cls.add_method('PeekHighPrecision', 
                   'ns3::HighPrecision *', 
                   [])
    ## time-base.h: static void ns3::TimeBase::SetResolution(ns3::TimeBase::Unit resolution) [member function]
    cls.add_method('SetResolution', 
                   'void', 
                   [param('ns3::TimeBase::Unit', 'resolution')], 
                   is_static=True)
    ## time-base.h: static double ns3::TimeBase::ToDouble(ns3::TimeBase const & time, ns3::TimeBase::Unit timeUnit) [member function]
    cls.add_method('ToDouble', 
                   'double', 
                   [param('ns3::TimeBase const &', 'time'), param('ns3::TimeBase::Unit', 'timeUnit')], 
                   is_static=True)
    ## time-base.h: static uint64_t ns3::TimeBase::ToInteger(ns3::TimeBase const & time, ns3::TimeBase::Unit timeUnit) [member function]
    cls.add_method('ToInteger', 
                   'uint64_t', 
                   [param('ns3::TimeBase const &', 'time'), param('ns3::TimeBase::Unit', 'timeUnit')], 
                   is_static=True)
    return

def register_Ns3Timer_methods(root_module, cls):
    ## timer.h: ns3::Timer::Timer(ns3::Timer const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Timer const &', 'arg0')])
    ## timer.h: ns3::Timer::Timer() [constructor]
    cls.add_constructor([])
    ## timer.h: ns3::Timer::Timer(ns3::Timer::DestroyPolicy destroyPolicy) [constructor]
    cls.add_constructor([param('ns3::Timer::DestroyPolicy', 'destroyPolicy')])
    ## timer.h: void ns3::Timer::Cancel() [member function]
    cls.add_method('Cancel', 
                   'void', 
                   [])
    ## timer.h: ns3::Time ns3::Timer::GetDelay() const [member function]
    cls.add_method('GetDelay', 
                   'ns3::Time', 
                   [], 
                   is_const=True)
    ## timer.h: ns3::Time ns3::Timer::GetDelayLeft() const [member function]
    cls.add_method('GetDelayLeft', 
                   'ns3::Time', 
                   [], 
                   is_const=True)
    ## timer.h: ns3::Timer::State ns3::Timer::GetState() const [member function]
    cls.add_method('GetState', 
                   'ns3::Timer::State', 
                   [], 
                   is_const=True)
    ## timer.h: bool ns3::Timer::IsExpired() const [member function]
    cls.add_method('IsExpired', 
                   'bool', 
                   [], 
                   is_const=True)
    ## timer.h: bool ns3::Timer::IsRunning() const [member function]
    cls.add_method('IsRunning', 
                   'bool', 
                   [], 
                   is_const=True)
    ## timer.h: bool ns3::Timer::IsSuspended() const [member function]
    cls.add_method('IsSuspended', 
                   'bool', 
                   [], 
                   is_const=True)
    ## timer.h: void ns3::Timer::Remove() [member function]
    cls.add_method('Remove', 
                   'void', 
                   [])
    ## timer.h: void ns3::Timer::Resume() [member function]
    cls.add_method('Resume', 
                   'void', 
                   [])
    ## timer.h: void ns3::Timer::Schedule() [member function]
    cls.add_method('Schedule', 
                   'void', 
                   [])
    ## timer.h: void ns3::Timer::Schedule(ns3::Time delay) [member function]
    cls.add_method('Schedule', 
                   'void', 
                   [param('ns3::Time', 'delay')])
    ## timer.h: void ns3::Timer::SetDelay(ns3::Time const & delay) [member function]
    cls.add_method('SetDelay', 
                   'void', 
                   [param('ns3::Time const &', 'delay')])
    ## timer.h: void ns3::Timer::Suspend() [member function]
    cls.add_method('Suspend', 
                   'void', 
                   [])
    return

def register_Ns3TimerImpl_methods(root_module, cls):
    ## timer-impl.h: ns3::TimerImpl::TimerImpl() [constructor]
    cls.add_constructor([])
    ## timer-impl.h: ns3::TimerImpl::TimerImpl(ns3::TimerImpl const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::TimerImpl const &', 'arg0')])
    ## timer-impl.h: void ns3::TimerImpl::Invoke() [member function]
    cls.add_method('Invoke', 
                   'void', 
                   [], 
                   is_pure_virtual=True, is_virtual=True)
    ## timer-impl.h: ns3::EventId ns3::TimerImpl::Schedule(ns3::Time const & delay) [member function]
    cls.add_method('Schedule', 
                   'ns3::EventId', 
                   [param('ns3::Time const &', 'delay')], 
                   is_pure_virtual=True, is_virtual=True)
    return

def register_Ns3Watchdog_methods(root_module, cls):
    ## watchdog.h: ns3::Watchdog::Watchdog(ns3::Watchdog const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Watchdog const &', 'arg0')])
    ## watchdog.h: ns3::Watchdog::Watchdog() [constructor]
    cls.add_constructor([])
    ## watchdog.h: void ns3::Watchdog::Ping(ns3::Time delay) [member function]
    cls.add_method('Ping', 
                   'void', 
                   [param('ns3::Time', 'delay')])
    return

def register_Ns3Scalar_methods(root_module, cls):
    ## nstime.h: ns3::Scalar::Scalar(ns3::Scalar const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Scalar const &', 'arg0')])
    ## nstime.h: ns3::Scalar::Scalar() [constructor]
    cls.add_constructor([])
    ## nstime.h: ns3::Scalar::Scalar(double v) [constructor]
    cls.add_constructor([param('double', 'v')])
    ## nstime.h: ns3::Scalar::Scalar(uint32_t v) [constructor]
    cls.add_constructor([param('uint32_t', 'v')])
    ## nstime.h: ns3::Scalar::Scalar(int32_t v) [constructor]
    cls.add_constructor([param('int32_t', 'v')])
    ## nstime.h: ns3::Scalar::Scalar(uint64_t v) [constructor]
    cls.add_constructor([param('uint64_t', 'v')])
    ## nstime.h: ns3::Scalar::Scalar(int64_t v) [constructor]
    cls.add_constructor([param('int64_t', 'v')])
    ## nstime.h: ns3::Scalar::Scalar(ns3::Time t) [constructor]
    cls.add_constructor([param('ns3::Time', 't')])
    ## nstime.h: double ns3::Scalar::GetDouble() const [member function]
    cls.add_method('GetDouble', 
                   'double', 
                   [], 
                   is_const=True)
    return

def register_Ns3Scheduler_methods(root_module, cls):
    ## scheduler.h: ns3::Scheduler::Scheduler() [constructor]
    cls.add_constructor([])
    ## scheduler.h: ns3::Scheduler::Scheduler(ns3::Scheduler const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Scheduler const &', 'arg0')])
    ## scheduler.h: static ns3::TypeId ns3::Scheduler::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## scheduler.h: void ns3::Scheduler::Insert(ns3::Scheduler::Event const & ev) [member function]
    cls.add_method('Insert', 
                   'void', 
                   [param('ns3::Scheduler::Event const &', 'ev')], 
                   is_pure_virtual=True, is_virtual=True)
    ## scheduler.h: bool ns3::Scheduler::IsEmpty() const [member function]
    cls.add_method('IsEmpty', 
                   'bool', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## scheduler.h: ns3::Scheduler::Event ns3::Scheduler::PeekNext() const [member function]
    cls.add_method('PeekNext', 
                   'ns3::Scheduler::Event', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## scheduler.h: void ns3::Scheduler::Remove(ns3::Scheduler::Event const & ev) [member function]
    cls.add_method('Remove', 
                   'void', 
                   [param('ns3::Scheduler::Event const &', 'ev')], 
                   is_pure_virtual=True, is_virtual=True)
    ## scheduler.h: ns3::Scheduler::Event ns3::Scheduler::RemoveNext() [member function]
    cls.add_method('RemoveNext', 
                   'ns3::Scheduler::Event', 
                   [], 
                   is_pure_virtual=True, is_virtual=True)
    return

def register_Ns3SchedulerEvent_methods(root_module, cls):
    cls.add_binary_comparison_operator('<')
    ## scheduler.h: ns3::Scheduler::Event::Event() [constructor]
    cls.add_constructor([])
    ## scheduler.h: ns3::Scheduler::Event::Event(ns3::Scheduler::Event const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Scheduler::Event const &', 'arg0')])
    ## scheduler.h: ns3::Scheduler::Event::impl [variable]
    cls.add_instance_attribute('impl', 'ns3::EventImpl *', is_const=False)
    ## scheduler.h: ns3::Scheduler::Event::key [variable]
    cls.add_instance_attribute('key', 'ns3::Scheduler::EventKey', is_const=False)
    return

def register_Ns3SchedulerEventKey_methods(root_module, cls):
    cls.add_binary_comparison_operator('!=')
    cls.add_binary_comparison_operator('<')
    cls.add_binary_comparison_operator('>')
    ## scheduler.h: ns3::Scheduler::EventKey::EventKey() [constructor]
    cls.add_constructor([])
    ## scheduler.h: ns3::Scheduler::EventKey::EventKey(ns3::Scheduler::EventKey const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Scheduler::EventKey const &', 'arg0')])
    ## scheduler.h: ns3::Scheduler::EventKey::m_context [variable]
    cls.add_instance_attribute('m_context', 'uint32_t', is_const=False)
    ## scheduler.h: ns3::Scheduler::EventKey::m_ts [variable]
    cls.add_instance_attribute('m_ts', 'uint64_t', is_const=False)
    ## scheduler.h: ns3::Scheduler::EventKey::m_uid [variable]
    cls.add_instance_attribute('m_uid', 'uint32_t', is_const=False)
    return

def register_Ns3SimulatorImpl_methods(root_module, cls):
    ## simulator-impl.h: ns3::SimulatorImpl::SimulatorImpl() [constructor]
    cls.add_constructor([])
    ## simulator-impl.h: ns3::SimulatorImpl::SimulatorImpl(ns3::SimulatorImpl const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::SimulatorImpl const &', 'arg0')])
    ## simulator-impl.h: void ns3::SimulatorImpl::Cancel(ns3::EventId const & ev) [member function]
    cls.add_method('Cancel', 
                   'void', 
                   [param('ns3::EventId const &', 'ev')], 
                   is_pure_virtual=True, is_virtual=True)
    ## simulator-impl.h: void ns3::SimulatorImpl::Destroy() [member function]
    cls.add_method('Destroy', 
                   'void', 
                   [], 
                   is_pure_virtual=True, is_virtual=True)
    ## simulator-impl.h: uint32_t ns3::SimulatorImpl::GetContext() const [member function]
    cls.add_method('GetContext', 
                   'uint32_t', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## simulator-impl.h: ns3::Time ns3::SimulatorImpl::GetDelayLeft(ns3::EventId const & id) const [member function]
    cls.add_method('GetDelayLeft', 
                   'ns3::Time', 
                   [param('ns3::EventId const &', 'id')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## simulator-impl.h: ns3::Time ns3::SimulatorImpl::GetMaximumSimulationTime() const [member function]
    cls.add_method('GetMaximumSimulationTime', 
                   'ns3::Time', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## simulator-impl.h: uint32_t ns3::SimulatorImpl::GetSystemId() const [member function]
    cls.add_method('GetSystemId', 
                   'uint32_t', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## simulator-impl.h: static ns3::TypeId ns3::SimulatorImpl::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## simulator-impl.h: bool ns3::SimulatorImpl::IsExpired(ns3::EventId const & ev) const [member function]
    cls.add_method('IsExpired', 
                   'bool', 
                   [param('ns3::EventId const &', 'ev')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## simulator-impl.h: bool ns3::SimulatorImpl::IsFinished() const [member function]
    cls.add_method('IsFinished', 
                   'bool', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## simulator-impl.h: ns3::Time ns3::SimulatorImpl::Next() const [member function]
    cls.add_method('Next', 
                   'ns3::Time', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## simulator-impl.h: ns3::Time ns3::SimulatorImpl::Now() const [member function]
    cls.add_method('Now', 
                   'ns3::Time', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## simulator-impl.h: void ns3::SimulatorImpl::Remove(ns3::EventId const & ev) [member function]
    cls.add_method('Remove', 
                   'void', 
                   [param('ns3::EventId const &', 'ev')], 
                   is_pure_virtual=True, is_virtual=True)
    ## simulator-impl.h: void ns3::SimulatorImpl::Run() [member function]
    cls.add_method('Run', 
                   'void', 
                   [], 
                   is_pure_virtual=True, is_virtual=True)
    ## simulator-impl.h: void ns3::SimulatorImpl::RunOneEvent() [member function]
    cls.add_method('RunOneEvent', 
                   'void', 
                   [], 
                   is_pure_virtual=True, is_virtual=True)
    ## simulator-impl.h: ns3::EventId ns3::SimulatorImpl::Schedule(ns3::Time const & time, ns3::EventImpl * event) [member function]
    cls.add_method('Schedule', 
                   'ns3::EventId', 
                   [param('ns3::Time const &', 'time'), param('ns3::EventImpl *', 'event')], 
                   is_pure_virtual=True, is_virtual=True)
    ## simulator-impl.h: ns3::EventId ns3::SimulatorImpl::ScheduleDestroy(ns3::EventImpl * event) [member function]
    cls.add_method('ScheduleDestroy', 
                   'ns3::EventId', 
                   [param('ns3::EventImpl *', 'event')], 
                   is_pure_virtual=True, is_virtual=True)
    ## simulator-impl.h: ns3::EventId ns3::SimulatorImpl::ScheduleNow(ns3::EventImpl * event) [member function]
    cls.add_method('ScheduleNow', 
                   'ns3::EventId', 
                   [param('ns3::EventImpl *', 'event')], 
                   is_pure_virtual=True, is_virtual=True)
    ## simulator-impl.h: void ns3::SimulatorImpl::ScheduleWithContext(uint32_t context, ns3::Time const & time, ns3::EventImpl * event) [member function]
    cls.add_method('ScheduleWithContext', 
                   'void', 
                   [param('uint32_t', 'context'), param('ns3::Time const &', 'time'), param('ns3::EventImpl *', 'event')], 
                   is_pure_virtual=True, is_virtual=True)
    ## simulator-impl.h: void ns3::SimulatorImpl::SetScheduler(ns3::ObjectFactory schedulerFactory) [member function]
    cls.add_method('SetScheduler', 
                   'void', 
                   [param('ns3::ObjectFactory', 'schedulerFactory')], 
                   is_pure_virtual=True, is_virtual=True)
    ## simulator-impl.h: void ns3::SimulatorImpl::Stop() [member function]
    cls.add_method('Stop', 
                   'void', 
                   [], 
                   is_pure_virtual=True, is_virtual=True)
    ## simulator-impl.h: void ns3::SimulatorImpl::Stop(ns3::Time const & time) [member function]
    cls.add_method('Stop', 
                   'void', 
                   [param('ns3::Time const &', 'time')], 
                   is_pure_virtual=True, is_virtual=True)
    return

def register_Ns3Synchronizer_methods(root_module, cls):
    ## synchronizer.h: ns3::Synchronizer::Synchronizer(ns3::Synchronizer const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Synchronizer const &', 'arg0')])
    ## synchronizer.h: ns3::Synchronizer::Synchronizer() [constructor]
    cls.add_constructor([])
    ## synchronizer.h: uint64_t ns3::Synchronizer::EventEnd() [member function]
    cls.add_method('EventEnd', 
                   'uint64_t', 
                   [])
    ## synchronizer.h: void ns3::Synchronizer::EventStart() [member function]
    cls.add_method('EventStart', 
                   'void', 
                   [])
    ## synchronizer.h: uint64_t ns3::Synchronizer::GetCurrentRealtime() [member function]
    cls.add_method('GetCurrentRealtime', 
                   'uint64_t', 
                   [])
    ## synchronizer.h: int64_t ns3::Synchronizer::GetDrift(uint64_t ts) [member function]
    cls.add_method('GetDrift', 
                   'int64_t', 
                   [param('uint64_t', 'ts')])
    ## synchronizer.h: uint64_t ns3::Synchronizer::GetOrigin() [member function]
    cls.add_method('GetOrigin', 
                   'uint64_t', 
                   [])
    ## synchronizer.h: static ns3::TypeId ns3::Synchronizer::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## synchronizer.h: bool ns3::Synchronizer::Realtime() [member function]
    cls.add_method('Realtime', 
                   'bool', 
                   [])
    ## synchronizer.h: void ns3::Synchronizer::SetCondition(bool arg0) [member function]
    cls.add_method('SetCondition', 
                   'void', 
                   [param('bool', 'arg0')])
    ## synchronizer.h: void ns3::Synchronizer::SetOrigin(uint64_t ts) [member function]
    cls.add_method('SetOrigin', 
                   'void', 
                   [param('uint64_t', 'ts')])
    ## synchronizer.h: void ns3::Synchronizer::Signal() [member function]
    cls.add_method('Signal', 
                   'void', 
                   [])
    ## synchronizer.h: bool ns3::Synchronizer::Synchronize(uint64_t tsCurrent, uint64_t tsDelay) [member function]
    cls.add_method('Synchronize', 
                   'bool', 
                   [param('uint64_t', 'tsCurrent'), param('uint64_t', 'tsDelay')])
    ## synchronizer.h: uint64_t ns3::Synchronizer::DoEventEnd() [member function]
    cls.add_method('DoEventEnd', 
                   'uint64_t', 
                   [], 
                   is_pure_virtual=True, visibility='protected', is_virtual=True)
    ## synchronizer.h: void ns3::Synchronizer::DoEventStart() [member function]
    cls.add_method('DoEventStart', 
                   'void', 
                   [], 
                   is_pure_virtual=True, visibility='protected', is_virtual=True)
    ## synchronizer.h: uint64_t ns3::Synchronizer::DoGetCurrentRealtime() [member function]
    cls.add_method('DoGetCurrentRealtime', 
                   'uint64_t', 
                   [], 
                   is_pure_virtual=True, visibility='protected', is_virtual=True)
    ## synchronizer.h: int64_t ns3::Synchronizer::DoGetDrift(uint64_t ns) [member function]
    cls.add_method('DoGetDrift', 
                   'int64_t', 
                   [param('uint64_t', 'ns')], 
                   is_pure_virtual=True, visibility='protected', is_virtual=True)
    ## synchronizer.h: bool ns3::Synchronizer::DoRealtime() [member function]
    cls.add_method('DoRealtime', 
                   'bool', 
                   [], 
                   is_pure_virtual=True, visibility='protected', is_virtual=True)
    ## synchronizer.h: void ns3::Synchronizer::DoSetCondition(bool arg0) [member function]
    cls.add_method('DoSetCondition', 
                   'void', 
                   [param('bool', 'arg0')], 
                   is_pure_virtual=True, visibility='protected', is_virtual=True)
    ## synchronizer.h: void ns3::Synchronizer::DoSetOrigin(uint64_t ns) [member function]
    cls.add_method('DoSetOrigin', 
                   'void', 
                   [param('uint64_t', 'ns')], 
                   is_pure_virtual=True, visibility='protected', is_virtual=True)
    ## synchronizer.h: void ns3::Synchronizer::DoSignal() [member function]
    cls.add_method('DoSignal', 
                   'void', 
                   [], 
                   is_pure_virtual=True, visibility='protected', is_virtual=True)
    ## synchronizer.h: bool ns3::Synchronizer::DoSynchronize(uint64_t nsCurrent, uint64_t nsDelay) [member function]
    cls.add_method('DoSynchronize', 
                   'bool', 
                   [param('uint64_t', 'nsCurrent'), param('uint64_t', 'nsDelay')], 
                   is_pure_virtual=True, visibility='protected', is_virtual=True)
    return

def register_Ns3WallClockSynchronizer_methods(root_module, cls):
    ## wall-clock-synchronizer.h: ns3::WallClockSynchronizer::WallClockSynchronizer(ns3::WallClockSynchronizer const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::WallClockSynchronizer const &', 'arg0')])
    ## wall-clock-synchronizer.h: ns3::WallClockSynchronizer::WallClockSynchronizer() [constructor]
    cls.add_constructor([])
    ## wall-clock-synchronizer.h: ns3::WallClockSynchronizer::NS_PER_SEC [variable]
    cls.add_static_attribute('NS_PER_SEC', 'uint64_t const', is_const=True)
    ## wall-clock-synchronizer.h: ns3::WallClockSynchronizer::US_PER_NS [variable]
    cls.add_static_attribute('US_PER_NS', 'uint64_t const', is_const=True)
    ## wall-clock-synchronizer.h: ns3::WallClockSynchronizer::US_PER_SEC [variable]
    cls.add_static_attribute('US_PER_SEC', 'uint64_t const', is_const=True)
    ## wall-clock-synchronizer.h: uint64_t ns3::WallClockSynchronizer::DoEventEnd() [member function]
    cls.add_method('DoEventEnd', 
                   'uint64_t', 
                   [], 
                   visibility='protected', is_virtual=True)
    ## wall-clock-synchronizer.h: void ns3::WallClockSynchronizer::DoEventStart() [member function]
    cls.add_method('DoEventStart', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    ## wall-clock-synchronizer.h: uint64_t ns3::WallClockSynchronizer::DoGetCurrentRealtime() [member function]
    cls.add_method('DoGetCurrentRealtime', 
                   'uint64_t', 
                   [], 
                   visibility='protected', is_virtual=True)
    ## wall-clock-synchronizer.h: int64_t ns3::WallClockSynchronizer::DoGetDrift(uint64_t ns) [member function]
    cls.add_method('DoGetDrift', 
                   'int64_t', 
                   [param('uint64_t', 'ns')], 
                   visibility='protected', is_virtual=True)
    ## wall-clock-synchronizer.h: bool ns3::WallClockSynchronizer::DoRealtime() [member function]
    cls.add_method('DoRealtime', 
                   'bool', 
                   [], 
                   visibility='protected', is_virtual=True)
    ## wall-clock-synchronizer.h: void ns3::WallClockSynchronizer::DoSetCondition(bool cond) [member function]
    cls.add_method('DoSetCondition', 
                   'void', 
                   [param('bool', 'cond')], 
                   visibility='protected', is_virtual=True)
    ## wall-clock-synchronizer.h: void ns3::WallClockSynchronizer::DoSetOrigin(uint64_t ns) [member function]
    cls.add_method('DoSetOrigin', 
                   'void', 
                   [param('uint64_t', 'ns')], 
                   visibility='protected', is_virtual=True)
    ## wall-clock-synchronizer.h: void ns3::WallClockSynchronizer::DoSignal() [member function]
    cls.add_method('DoSignal', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    ## wall-clock-synchronizer.h: bool ns3::WallClockSynchronizer::DoSynchronize(uint64_t nsCurrent, uint64_t nsDelay) [member function]
    cls.add_method('DoSynchronize', 
                   'bool', 
                   [param('uint64_t', 'nsCurrent'), param('uint64_t', 'nsDelay')], 
                   visibility='protected', is_virtual=True)
    ## wall-clock-synchronizer.h: uint64_t ns3::WallClockSynchronizer::DriftCorrect(uint64_t nsNow, uint64_t nsDelay) [member function]
    cls.add_method('DriftCorrect', 
                   'uint64_t', 
                   [param('uint64_t', 'nsNow'), param('uint64_t', 'nsDelay')], 
                   visibility='protected')
    ## wall-clock-synchronizer.h: uint64_t ns3::WallClockSynchronizer::GetNormalizedRealtime() [member function]
    cls.add_method('GetNormalizedRealtime', 
                   'uint64_t', 
                   [], 
                   visibility='protected')
    ## wall-clock-synchronizer.h: uint64_t ns3::WallClockSynchronizer::GetRealtime() [member function]
    cls.add_method('GetRealtime', 
                   'uint64_t', 
                   [], 
                   visibility='protected')
    ## wall-clock-synchronizer.h: void ns3::WallClockSynchronizer::NsToTimeval(int64_t ns, timeval * tv) [member function]
    cls.add_method('NsToTimeval', 
                   'void', 
                   [param('int64_t', 'ns'), param('timeval *', 'tv')], 
                   visibility='protected')
    ## wall-clock-synchronizer.h: bool ns3::WallClockSynchronizer::SleepWait(uint64_t arg0) [member function]
    cls.add_method('SleepWait', 
                   'bool', 
                   [param('uint64_t', 'arg0')], 
                   visibility='protected')
    ## wall-clock-synchronizer.h: bool ns3::WallClockSynchronizer::SpinWait(uint64_t arg0) [member function]
    cls.add_method('SpinWait', 
                   'bool', 
                   [param('uint64_t', 'arg0')], 
                   visibility='protected')
    ## wall-clock-synchronizer.h: void ns3::WallClockSynchronizer::TimevalAdd(timeval * tv1, timeval * tv2, timeval * result) [member function]
    cls.add_method('TimevalAdd', 
                   'void', 
                   [param('timeval *', 'tv1'), param('timeval *', 'tv2'), param('timeval *', 'result')], 
                   visibility='protected')
    ## wall-clock-synchronizer.h: uint64_t ns3::WallClockSynchronizer::TimevalToNs(timeval * tv) [member function]
    cls.add_method('TimevalToNs', 
                   'uint64_t', 
                   [param('timeval *', 'tv')], 
                   visibility='protected')
    return

def register_Ns3CalendarScheduler_methods(root_module, cls):
    ## calendar-scheduler.h: ns3::CalendarScheduler::CalendarScheduler(ns3::CalendarScheduler const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::CalendarScheduler const &', 'arg0')])
    ## calendar-scheduler.h: ns3::CalendarScheduler::CalendarScheduler() [constructor]
    cls.add_constructor([])
    ## calendar-scheduler.h: static ns3::TypeId ns3::CalendarScheduler::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## calendar-scheduler.h: void ns3::CalendarScheduler::Insert(ns3::Scheduler::Event const & ev) [member function]
    cls.add_method('Insert', 
                   'void', 
                   [param('ns3::Scheduler::Event const &', 'ev')], 
                   is_virtual=True)
    ## calendar-scheduler.h: bool ns3::CalendarScheduler::IsEmpty() const [member function]
    cls.add_method('IsEmpty', 
                   'bool', 
                   [], 
                   is_const=True, is_virtual=True)
    ## calendar-scheduler.h: ns3::Scheduler::Event ns3::CalendarScheduler::PeekNext() const [member function]
    cls.add_method('PeekNext', 
                   'ns3::Scheduler::Event', 
                   [], 
                   is_const=True, is_virtual=True)
    ## calendar-scheduler.h: void ns3::CalendarScheduler::Remove(ns3::Scheduler::Event const & ev) [member function]
    cls.add_method('Remove', 
                   'void', 
                   [param('ns3::Scheduler::Event const &', 'ev')], 
                   is_virtual=True)
    ## calendar-scheduler.h: ns3::Scheduler::Event ns3::CalendarScheduler::RemoveNext() [member function]
    cls.add_method('RemoveNext', 
                   'ns3::Scheduler::Event', 
                   [], 
                   is_virtual=True)
    return

def register_Ns3DefaultSimulatorImpl_methods(root_module, cls):
    ## default-simulator-impl.h: ns3::DefaultSimulatorImpl::DefaultSimulatorImpl(ns3::DefaultSimulatorImpl const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::DefaultSimulatorImpl const &', 'arg0')])
    ## default-simulator-impl.h: ns3::DefaultSimulatorImpl::DefaultSimulatorImpl() [constructor]
    cls.add_constructor([])
    ## default-simulator-impl.h: void ns3::DefaultSimulatorImpl::Cancel(ns3::EventId const & ev) [member function]
    cls.add_method('Cancel', 
                   'void', 
                   [param('ns3::EventId const &', 'ev')], 
                   is_virtual=True)
    ## default-simulator-impl.h: void ns3::DefaultSimulatorImpl::Destroy() [member function]
    cls.add_method('Destroy', 
                   'void', 
                   [], 
                   is_virtual=True)
    ## default-simulator-impl.h: uint32_t ns3::DefaultSimulatorImpl::GetContext() const [member function]
    cls.add_method('GetContext', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## default-simulator-impl.h: ns3::Time ns3::DefaultSimulatorImpl::GetDelayLeft(ns3::EventId const & id) const [member function]
    cls.add_method('GetDelayLeft', 
                   'ns3::Time', 
                   [param('ns3::EventId const &', 'id')], 
                   is_const=True, is_virtual=True)
    ## default-simulator-impl.h: ns3::Time ns3::DefaultSimulatorImpl::GetMaximumSimulationTime() const [member function]
    cls.add_method('GetMaximumSimulationTime', 
                   'ns3::Time', 
                   [], 
                   is_const=True, is_virtual=True)
    ## default-simulator-impl.h: uint32_t ns3::DefaultSimulatorImpl::GetSystemId() const [member function]
    cls.add_method('GetSystemId', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## default-simulator-impl.h: static ns3::TypeId ns3::DefaultSimulatorImpl::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## default-simulator-impl.h: bool ns3::DefaultSimulatorImpl::IsExpired(ns3::EventId const & ev) const [member function]
    cls.add_method('IsExpired', 
                   'bool', 
                   [param('ns3::EventId const &', 'ev')], 
                   is_const=True, is_virtual=True)
    ## default-simulator-impl.h: bool ns3::DefaultSimulatorImpl::IsFinished() const [member function]
    cls.add_method('IsFinished', 
                   'bool', 
                   [], 
                   is_const=True, is_virtual=True)
    ## default-simulator-impl.h: ns3::Time ns3::DefaultSimulatorImpl::Next() const [member function]
    cls.add_method('Next', 
                   'ns3::Time', 
                   [], 
                   is_const=True, is_virtual=True)
    ## default-simulator-impl.h: ns3::Time ns3::DefaultSimulatorImpl::Now() const [member function]
    cls.add_method('Now', 
                   'ns3::Time', 
                   [], 
                   is_const=True, is_virtual=True)
    ## default-simulator-impl.h: void ns3::DefaultSimulatorImpl::Remove(ns3::EventId const & ev) [member function]
    cls.add_method('Remove', 
                   'void', 
                   [param('ns3::EventId const &', 'ev')], 
                   is_virtual=True)
    ## default-simulator-impl.h: void ns3::DefaultSimulatorImpl::Run() [member function]
    cls.add_method('Run', 
                   'void', 
                   [], 
                   is_virtual=True)
    ## default-simulator-impl.h: void ns3::DefaultSimulatorImpl::RunOneEvent() [member function]
    cls.add_method('RunOneEvent', 
                   'void', 
                   [], 
                   is_virtual=True)
    ## default-simulator-impl.h: ns3::EventId ns3::DefaultSimulatorImpl::Schedule(ns3::Time const & time, ns3::EventImpl * event) [member function]
    cls.add_method('Schedule', 
                   'ns3::EventId', 
                   [param('ns3::Time const &', 'time'), param('ns3::EventImpl *', 'event')], 
                   is_virtual=True)
    ## default-simulator-impl.h: ns3::EventId ns3::DefaultSimulatorImpl::ScheduleDestroy(ns3::EventImpl * event) [member function]
    cls.add_method('ScheduleDestroy', 
                   'ns3::EventId', 
                   [param('ns3::EventImpl *', 'event')], 
                   is_virtual=True)
    ## default-simulator-impl.h: ns3::EventId ns3::DefaultSimulatorImpl::ScheduleNow(ns3::EventImpl * event) [member function]
    cls.add_method('ScheduleNow', 
                   'ns3::EventId', 
                   [param('ns3::EventImpl *', 'event')], 
                   is_virtual=True)
    ## default-simulator-impl.h: void ns3::DefaultSimulatorImpl::ScheduleWithContext(uint32_t context, ns3::Time const & time, ns3::EventImpl * event) [member function]
    cls.add_method('ScheduleWithContext', 
                   'void', 
                   [param('uint32_t', 'context'), param('ns3::Time const &', 'time'), param('ns3::EventImpl *', 'event')], 
                   is_virtual=True)
    ## default-simulator-impl.h: void ns3::DefaultSimulatorImpl::SetScheduler(ns3::ObjectFactory schedulerFactory) [member function]
    cls.add_method('SetScheduler', 
                   'void', 
                   [param('ns3::ObjectFactory', 'schedulerFactory')], 
                   is_virtual=True)
    ## default-simulator-impl.h: void ns3::DefaultSimulatorImpl::Stop() [member function]
    cls.add_method('Stop', 
                   'void', 
                   [], 
                   is_virtual=True)
    ## default-simulator-impl.h: void ns3::DefaultSimulatorImpl::Stop(ns3::Time const & time) [member function]
    cls.add_method('Stop', 
                   'void', 
                   [param('ns3::Time const &', 'time')], 
                   is_virtual=True)
    ## default-simulator-impl.h: void ns3::DefaultSimulatorImpl::DoDispose() [member function]
    cls.add_method('DoDispose', 
                   'void', 
                   [], 
                   visibility='private', is_virtual=True)
    return

def register_Ns3EventImpl_methods(root_module, cls):
    ## event-impl.h: ns3::EventImpl::EventImpl(ns3::EventImpl const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::EventImpl const &', 'arg0')])
    ## event-impl.h: ns3::EventImpl::EventImpl() [constructor]
    cls.add_constructor([])
    ## event-impl.h: void ns3::EventImpl::Cancel() [member function]
    cls.add_method('Cancel', 
                   'void', 
                   [])
    ## event-impl.h: void ns3::EventImpl::Invoke() [member function]
    cls.add_method('Invoke', 
                   'void', 
                   [])
    ## event-impl.h: bool ns3::EventImpl::IsCancelled() [member function]
    cls.add_method('IsCancelled', 
                   'bool', 
                   [])
    ## event-impl.h: void ns3::EventImpl::Notify() [member function]
    cls.add_method('Notify', 
                   'void', 
                   [], 
                   is_pure_virtual=True, visibility='protected', is_virtual=True)
    return

def register_Ns3HeapScheduler_methods(root_module, cls):
    ## heap-scheduler.h: ns3::HeapScheduler::HeapScheduler(ns3::HeapScheduler const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::HeapScheduler const &', 'arg0')])
    ## heap-scheduler.h: ns3::HeapScheduler::HeapScheduler() [constructor]
    cls.add_constructor([])
    ## heap-scheduler.h: static ns3::TypeId ns3::HeapScheduler::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## heap-scheduler.h: void ns3::HeapScheduler::Insert(ns3::Scheduler::Event const & ev) [member function]
    cls.add_method('Insert', 
                   'void', 
                   [param('ns3::Scheduler::Event const &', 'ev')], 
                   is_virtual=True)
    ## heap-scheduler.h: bool ns3::HeapScheduler::IsEmpty() const [member function]
    cls.add_method('IsEmpty', 
                   'bool', 
                   [], 
                   is_const=True, is_virtual=True)
    ## heap-scheduler.h: ns3::Scheduler::Event ns3::HeapScheduler::PeekNext() const [member function]
    cls.add_method('PeekNext', 
                   'ns3::Scheduler::Event', 
                   [], 
                   is_const=True, is_virtual=True)
    ## heap-scheduler.h: void ns3::HeapScheduler::Remove(ns3::Scheduler::Event const & ev) [member function]
    cls.add_method('Remove', 
                   'void', 
                   [param('ns3::Scheduler::Event const &', 'ev')], 
                   is_virtual=True)
    ## heap-scheduler.h: ns3::Scheduler::Event ns3::HeapScheduler::RemoveNext() [member function]
    cls.add_method('RemoveNext', 
                   'ns3::Scheduler::Event', 
                   [], 
                   is_virtual=True)
    return

def register_Ns3ListScheduler_methods(root_module, cls):
    ## list-scheduler.h: ns3::ListScheduler::ListScheduler(ns3::ListScheduler const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::ListScheduler const &', 'arg0')])
    ## list-scheduler.h: ns3::ListScheduler::ListScheduler() [constructor]
    cls.add_constructor([])
    ## list-scheduler.h: static ns3::TypeId ns3::ListScheduler::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## list-scheduler.h: void ns3::ListScheduler::Insert(ns3::Scheduler::Event const & ev) [member function]
    cls.add_method('Insert', 
                   'void', 
                   [param('ns3::Scheduler::Event const &', 'ev')], 
                   is_virtual=True)
    ## list-scheduler.h: bool ns3::ListScheduler::IsEmpty() const [member function]
    cls.add_method('IsEmpty', 
                   'bool', 
                   [], 
                   is_const=True, is_virtual=True)
    ## list-scheduler.h: ns3::Scheduler::Event ns3::ListScheduler::PeekNext() const [member function]
    cls.add_method('PeekNext', 
                   'ns3::Scheduler::Event', 
                   [], 
                   is_const=True, is_virtual=True)
    ## list-scheduler.h: void ns3::ListScheduler::Remove(ns3::Scheduler::Event const & ev) [member function]
    cls.add_method('Remove', 
                   'void', 
                   [param('ns3::Scheduler::Event const &', 'ev')], 
                   is_virtual=True)
    ## list-scheduler.h: ns3::Scheduler::Event ns3::ListScheduler::RemoveNext() [member function]
    cls.add_method('RemoveNext', 
                   'ns3::Scheduler::Event', 
                   [], 
                   is_virtual=True)
    return

def register_Ns3MapScheduler_methods(root_module, cls):
    ## map-scheduler.h: ns3::MapScheduler::MapScheduler(ns3::MapScheduler const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::MapScheduler const &', 'arg0')])
    ## map-scheduler.h: ns3::MapScheduler::MapScheduler() [constructor]
    cls.add_constructor([])
    ## map-scheduler.h: static ns3::TypeId ns3::MapScheduler::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## map-scheduler.h: void ns3::MapScheduler::Insert(ns3::Scheduler::Event const & ev) [member function]
    cls.add_method('Insert', 
                   'void', 
                   [param('ns3::Scheduler::Event const &', 'ev')], 
                   is_virtual=True)
    ## map-scheduler.h: bool ns3::MapScheduler::IsEmpty() const [member function]
    cls.add_method('IsEmpty', 
                   'bool', 
                   [], 
                   is_const=True, is_virtual=True)
    ## map-scheduler.h: ns3::Scheduler::Event ns3::MapScheduler::PeekNext() const [member function]
    cls.add_method('PeekNext', 
                   'ns3::Scheduler::Event', 
                   [], 
                   is_const=True, is_virtual=True)
    ## map-scheduler.h: void ns3::MapScheduler::Remove(ns3::Scheduler::Event const & ev) [member function]
    cls.add_method('Remove', 
                   'void', 
                   [param('ns3::Scheduler::Event const &', 'ev')], 
                   is_virtual=True)
    ## map-scheduler.h: ns3::Scheduler::Event ns3::MapScheduler::RemoveNext() [member function]
    cls.add_method('RemoveNext', 
                   'ns3::Scheduler::Event', 
                   [], 
                   is_virtual=True)
    return

def register_Ns3Ns2CalendarScheduler_methods(root_module, cls):
    ## ns2-calendar-scheduler.h: ns3::Ns2CalendarScheduler::Ns2CalendarScheduler(ns3::Ns2CalendarScheduler const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Ns2CalendarScheduler const &', 'arg0')])
    ## ns2-calendar-scheduler.h: ns3::Ns2CalendarScheduler::Ns2CalendarScheduler() [constructor]
    cls.add_constructor([])
    ## ns2-calendar-scheduler.h: static ns3::TypeId ns3::Ns2CalendarScheduler::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## ns2-calendar-scheduler.h: void ns3::Ns2CalendarScheduler::Insert(ns3::Scheduler::Event const & ev) [member function]
    cls.add_method('Insert', 
                   'void', 
                   [param('ns3::Scheduler::Event const &', 'ev')], 
                   is_virtual=True)
    ## ns2-calendar-scheduler.h: bool ns3::Ns2CalendarScheduler::IsEmpty() const [member function]
    cls.add_method('IsEmpty', 
                   'bool', 
                   [], 
                   is_const=True, is_virtual=True)
    ## ns2-calendar-scheduler.h: ns3::Scheduler::Event ns3::Ns2CalendarScheduler::PeekNext() const [member function]
    cls.add_method('PeekNext', 
                   'ns3::Scheduler::Event', 
                   [], 
                   is_const=True, is_virtual=True)
    ## ns2-calendar-scheduler.h: void ns3::Ns2CalendarScheduler::Remove(ns3::Scheduler::Event const & ev) [member function]
    cls.add_method('Remove', 
                   'void', 
                   [param('ns3::Scheduler::Event const &', 'ev')], 
                   is_virtual=True)
    ## ns2-calendar-scheduler.h: ns3::Scheduler::Event ns3::Ns2CalendarScheduler::RemoveNext() [member function]
    cls.add_method('RemoveNext', 
                   'ns3::Scheduler::Event', 
                   [], 
                   is_virtual=True)
    return

def register_Ns3RealtimeSimulatorImpl_methods(root_module, cls):
    ## realtime-simulator-impl.h: ns3::RealtimeSimulatorImpl::RealtimeSimulatorImpl(ns3::RealtimeSimulatorImpl const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::RealtimeSimulatorImpl const &', 'arg0')])
    ## realtime-simulator-impl.h: ns3::RealtimeSimulatorImpl::RealtimeSimulatorImpl() [constructor]
    cls.add_constructor([])
    ## realtime-simulator-impl.h: void ns3::RealtimeSimulatorImpl::Cancel(ns3::EventId const & ev) [member function]
    cls.add_method('Cancel', 
                   'void', 
                   [param('ns3::EventId const &', 'ev')], 
                   is_virtual=True)
    ## realtime-simulator-impl.h: void ns3::RealtimeSimulatorImpl::Destroy() [member function]
    cls.add_method('Destroy', 
                   'void', 
                   [], 
                   is_virtual=True)
    ## realtime-simulator-impl.h: uint32_t ns3::RealtimeSimulatorImpl::GetContext() const [member function]
    cls.add_method('GetContext', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## realtime-simulator-impl.h: ns3::Time ns3::RealtimeSimulatorImpl::GetDelayLeft(ns3::EventId const & id) const [member function]
    cls.add_method('GetDelayLeft', 
                   'ns3::Time', 
                   [param('ns3::EventId const &', 'id')], 
                   is_const=True, is_virtual=True)
    ## realtime-simulator-impl.h: ns3::Time ns3::RealtimeSimulatorImpl::GetHardLimit() const [member function]
    cls.add_method('GetHardLimit', 
                   'ns3::Time', 
                   [], 
                   is_const=True)
    ## realtime-simulator-impl.h: ns3::Time ns3::RealtimeSimulatorImpl::GetMaximumSimulationTime() const [member function]
    cls.add_method('GetMaximumSimulationTime', 
                   'ns3::Time', 
                   [], 
                   is_const=True, is_virtual=True)
    ## realtime-simulator-impl.h: ns3::RealtimeSimulatorImpl::SynchronizationMode ns3::RealtimeSimulatorImpl::GetSynchronizationMode() const [member function]
    cls.add_method('GetSynchronizationMode', 
                   'ns3::RealtimeSimulatorImpl::SynchronizationMode', 
                   [], 
                   is_const=True)
    ## realtime-simulator-impl.h: uint32_t ns3::RealtimeSimulatorImpl::GetSystemId() const [member function]
    cls.add_method('GetSystemId', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## realtime-simulator-impl.h: static ns3::TypeId ns3::RealtimeSimulatorImpl::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## realtime-simulator-impl.h: bool ns3::RealtimeSimulatorImpl::IsExpired(ns3::EventId const & ev) const [member function]
    cls.add_method('IsExpired', 
                   'bool', 
                   [param('ns3::EventId const &', 'ev')], 
                   is_const=True, is_virtual=True)
    ## realtime-simulator-impl.h: bool ns3::RealtimeSimulatorImpl::IsFinished() const [member function]
    cls.add_method('IsFinished', 
                   'bool', 
                   [], 
                   is_const=True, is_virtual=True)
    ## realtime-simulator-impl.h: ns3::Time ns3::RealtimeSimulatorImpl::Next() const [member function]
    cls.add_method('Next', 
                   'ns3::Time', 
                   [], 
                   is_const=True, is_virtual=True)
    ## realtime-simulator-impl.h: ns3::Time ns3::RealtimeSimulatorImpl::Now() const [member function]
    cls.add_method('Now', 
                   'ns3::Time', 
                   [], 
                   is_const=True, is_virtual=True)
    ## realtime-simulator-impl.h: ns3::Time ns3::RealtimeSimulatorImpl::RealtimeNow() const [member function]
    cls.add_method('RealtimeNow', 
                   'ns3::Time', 
                   [], 
                   is_const=True)
    ## realtime-simulator-impl.h: void ns3::RealtimeSimulatorImpl::Remove(ns3::EventId const & ev) [member function]
    cls.add_method('Remove', 
                   'void', 
                   [param('ns3::EventId const &', 'ev')], 
                   is_virtual=True)
    ## realtime-simulator-impl.h: void ns3::RealtimeSimulatorImpl::Run() [member function]
    cls.add_method('Run', 
                   'void', 
                   [], 
                   is_virtual=True)
    ## realtime-simulator-impl.h: void ns3::RealtimeSimulatorImpl::RunOneEvent() [member function]
    cls.add_method('RunOneEvent', 
                   'void', 
                   [], 
                   is_virtual=True)
    ## realtime-simulator-impl.h: ns3::EventId ns3::RealtimeSimulatorImpl::Schedule(ns3::Time const & time, ns3::EventImpl * event) [member function]
    cls.add_method('Schedule', 
                   'ns3::EventId', 
                   [param('ns3::Time const &', 'time'), param('ns3::EventImpl *', 'event')], 
                   is_virtual=True)
    ## realtime-simulator-impl.h: ns3::EventId ns3::RealtimeSimulatorImpl::ScheduleDestroy(ns3::EventImpl * event) [member function]
    cls.add_method('ScheduleDestroy', 
                   'ns3::EventId', 
                   [param('ns3::EventImpl *', 'event')], 
                   is_virtual=True)
    ## realtime-simulator-impl.h: ns3::EventId ns3::RealtimeSimulatorImpl::ScheduleNow(ns3::EventImpl * event) [member function]
    cls.add_method('ScheduleNow', 
                   'ns3::EventId', 
                   [param('ns3::EventImpl *', 'event')], 
                   is_virtual=True)
    ## realtime-simulator-impl.h: void ns3::RealtimeSimulatorImpl::ScheduleRealtime(ns3::Time const & time, ns3::EventImpl * event) [member function]
    cls.add_method('ScheduleRealtime', 
                   'void', 
                   [param('ns3::Time const &', 'time'), param('ns3::EventImpl *', 'event')])
    ## realtime-simulator-impl.h: void ns3::RealtimeSimulatorImpl::ScheduleRealtimeNow(ns3::EventImpl * event) [member function]
    cls.add_method('ScheduleRealtimeNow', 
                   'void', 
                   [param('ns3::EventImpl *', 'event')])
    ## realtime-simulator-impl.h: void ns3::RealtimeSimulatorImpl::ScheduleRealtimeNowWithContext(uint32_t context, ns3::EventImpl * event) [member function]
    cls.add_method('ScheduleRealtimeNowWithContext', 
                   'void', 
                   [param('uint32_t', 'context'), param('ns3::EventImpl *', 'event')])
    ## realtime-simulator-impl.h: void ns3::RealtimeSimulatorImpl::ScheduleRealtimeWithContext(uint32_t context, ns3::Time const & time, ns3::EventImpl * event) [member function]
    cls.add_method('ScheduleRealtimeWithContext', 
                   'void', 
                   [param('uint32_t', 'context'), param('ns3::Time const &', 'time'), param('ns3::EventImpl *', 'event')])
    ## realtime-simulator-impl.h: void ns3::RealtimeSimulatorImpl::ScheduleWithContext(uint32_t context, ns3::Time const & time, ns3::EventImpl * event) [member function]
    cls.add_method('ScheduleWithContext', 
                   'void', 
                   [param('uint32_t', 'context'), param('ns3::Time const &', 'time'), param('ns3::EventImpl *', 'event')], 
                   is_virtual=True)
    ## realtime-simulator-impl.h: void ns3::RealtimeSimulatorImpl::SetHardLimit(ns3::Time limit) [member function]
    cls.add_method('SetHardLimit', 
                   'void', 
                   [param('ns3::Time', 'limit')])
    ## realtime-simulator-impl.h: void ns3::RealtimeSimulatorImpl::SetScheduler(ns3::ObjectFactory schedulerFactory) [member function]
    cls.add_method('SetScheduler', 
                   'void', 
                   [param('ns3::ObjectFactory', 'schedulerFactory')], 
                   is_virtual=True)
    ## realtime-simulator-impl.h: void ns3::RealtimeSimulatorImpl::SetSynchronizationMode(ns3::RealtimeSimulatorImpl::SynchronizationMode mode) [member function]
    cls.add_method('SetSynchronizationMode', 
                   'void', 
                   [param('ns3::RealtimeSimulatorImpl::SynchronizationMode', 'mode')])
    ## realtime-simulator-impl.h: void ns3::RealtimeSimulatorImpl::Stop() [member function]
    cls.add_method('Stop', 
                   'void', 
                   [], 
                   is_virtual=True)
    ## realtime-simulator-impl.h: void ns3::RealtimeSimulatorImpl::Stop(ns3::Time const & time) [member function]
    cls.add_method('Stop', 
                   'void', 
                   [param('ns3::Time const &', 'time')], 
                   is_virtual=True)
    ## realtime-simulator-impl.h: void ns3::RealtimeSimulatorImpl::DoDispose() [member function]
    cls.add_method('DoDispose', 
                   'void', 
                   [], 
                   visibility='private', is_virtual=True)
    return

def register_Ns3TimeChecker_methods(root_module, cls):
    ## nstime.h: ns3::TimeChecker::TimeChecker() [constructor]
    cls.add_constructor([])
    ## nstime.h: ns3::TimeChecker::TimeChecker(ns3::TimeChecker const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::TimeChecker const &', 'arg0')])
    return

def register_Ns3TimeValue_methods(root_module, cls):
    ## nstime.h: ns3::TimeValue::TimeValue() [constructor]
    cls.add_constructor([])
    ## nstime.h: ns3::TimeValue::TimeValue(ns3::TimeValue const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::TimeValue const &', 'arg0')])
    ## nstime.h: ns3::TimeValue::TimeValue(ns3::Time const & value) [constructor]
    cls.add_constructor([param('ns3::Time const &', 'value')])
    ## nstime.h: ns3::Ptr<ns3::AttributeValue> ns3::TimeValue::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## nstime.h: bool ns3::TimeValue::DeserializeFromString(std::string value, ns3::Ptr<ns3::AttributeChecker const> checker) [member function]
    cls.add_method('DeserializeFromString', 
                   'bool', 
                   [param('std::string', 'value'), param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_virtual=True)
    ## nstime.h: ns3::Time ns3::TimeValue::Get() const [member function]
    cls.add_method('Get', 
                   'ns3::Time', 
                   [], 
                   is_const=True)
    ## nstime.h: std::string ns3::TimeValue::SerializeToString(ns3::Ptr<ns3::AttributeChecker const> checker) const [member function]
    cls.add_method('SerializeToString', 
                   'std::string', 
                   [param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_const=True, is_virtual=True)
    ## nstime.h: void ns3::TimeValue::Set(ns3::Time const & value) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('ns3::Time const &', 'value')])
    return

def register_functions(root_module):
    module = root_module
    ## high-precision.h: extern ns3::HighPrecision ns3::Abs(ns3::HighPrecision const & value) [free function]
    module.add_function('Abs', 
                        'ns3::HighPrecision', 
                        [param('ns3::HighPrecision const &', 'value')])
    ## nstime.h: ns3::Time ns3::Abs(ns3::Time const & time) [free function]
    module.add_function('Abs', 
                        'ns3::Time', 
                        [param('ns3::Time const &', 'time')])
    ## nstime.h: ns3::Time ns3::FemtoSeconds(uint64_t fs) [free function]
    module.add_function('FemtoSeconds', 
                        'ns3::Time', 
                        [param('uint64_t', 'fs')])
    ## make-event.h: extern ns3::EventImpl * ns3::MakeEvent(void (*)(  ) * f) [free function]
    module.add_function('MakeEvent', 
                        'ns3::EventImpl *', 
                        [param('void ( * ) (  ) *', 'f')])
    ## nstime.h: extern ns3::Ptr<ns3::AttributeChecker const> ns3::MakeTimeChecker() [free function]
    module.add_function('MakeTimeChecker', 
                        'ns3::Ptr< ns3::AttributeChecker const >', 
                        [])
    ## high-precision.h: ns3::HighPrecision ns3::Max(ns3::HighPrecision const & a, ns3::HighPrecision const & b) [free function]
    module.add_function('Max', 
                        'ns3::HighPrecision', 
                        [param('ns3::HighPrecision const &', 'a'), param('ns3::HighPrecision const &', 'b')])
    ## nstime.h: ns3::Time ns3::Max(ns3::Time const & ta, ns3::Time const & tb) [free function]
    module.add_function('Max', 
                        'ns3::Time', 
                        [param('ns3::Time const &', 'ta'), param('ns3::Time const &', 'tb')])
    ## nstime.h: ns3::Time ns3::MicroSeconds(uint64_t us) [free function]
    module.add_function('MicroSeconds', 
                        'ns3::Time', 
                        [param('uint64_t', 'us')])
    ## nstime.h: ns3::Time ns3::MilliSeconds(uint64_t ms) [free function]
    module.add_function('MilliSeconds', 
                        'ns3::Time', 
                        [param('uint64_t', 'ms')])
    ## high-precision.h: ns3::HighPrecision ns3::Min(ns3::HighPrecision const & a, ns3::HighPrecision const & b) [free function]
    module.add_function('Min', 
                        'ns3::HighPrecision', 
                        [param('ns3::HighPrecision const &', 'a'), param('ns3::HighPrecision const &', 'b')])
    ## nstime.h: ns3::Time ns3::Min(ns3::Time const & ta, ns3::Time const & tb) [free function]
    module.add_function('Min', 
                        'ns3::Time', 
                        [param('ns3::Time const &', 'ta'), param('ns3::Time const &', 'tb')])
    ## nstime.h: ns3::Time ns3::NanoSeconds(uint64_t ns) [free function]
    module.add_function('NanoSeconds', 
                        'ns3::Time', 
                        [param('uint64_t', 'ns')])
    ## simulator.h: extern ns3::Time ns3::Now() [free function]
    module.add_function('Now', 
                        'ns3::Time', 
                        [])
    ## nstime.h: ns3::Time ns3::PicoSeconds(uint64_t ps) [free function]
    module.add_function('PicoSeconds', 
                        'ns3::Time', 
                        [param('uint64_t', 'ps')])
    ## nstime.h: ns3::Time ns3::Seconds(double seconds) [free function]
    module.add_function('Seconds', 
                        'ns3::Time', 
                        [param('double', 'seconds')])
    ## nstime.h: ns3::Time ns3::TimeStep(uint64_t ts) [free function]
    module.add_function('TimeStep', 
                        'ns3::Time', 
                        [param('uint64_t', 'ts')])
    register_functions_ns3_Config(module.get_submodule('Config'), root_module)
    register_functions_ns3_FatalImpl(module.get_submodule('FatalImpl'), root_module)
    register_functions_ns3_addressUtils(module.get_submodule('addressUtils'), root_module)
    register_functions_ns3_aodv(module.get_submodule('aodv'), root_module)
    register_functions_ns3_dot11s(module.get_submodule('dot11s'), root_module)
    register_functions_ns3_dsdv(module.get_submodule('dsdv'), root_module)
    register_functions_ns3_flame(module.get_submodule('flame'), root_module)
    register_functions_ns3_internal(module.get_submodule('internal'), root_module)
    register_functions_ns3_olsr(module.get_submodule('olsr'), root_module)
    return

def register_functions_ns3_Config(module, root_module):
    return

def register_functions_ns3_FatalImpl(module, root_module):
    return

def register_functions_ns3_addressUtils(module, root_module):
    return

def register_functions_ns3_aodv(module, root_module):
    return

def register_functions_ns3_dot11s(module, root_module):
    return

def register_functions_ns3_dsdv(module, root_module):
    return

def register_functions_ns3_flame(module, root_module):
    return

def register_functions_ns3_internal(module, root_module):
    return

def register_functions_ns3_olsr(module, root_module):
    return

