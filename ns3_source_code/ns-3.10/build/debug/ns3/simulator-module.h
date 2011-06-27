
#ifdef NS3_MODULE_COMPILATION
# error "Do not include ns3 module aggregator headers from other modules; these are meant only for end user scripts."
#endif

#ifndef NS3_MODULE_SIMULATOR
    

// Module headers:
#include "cairo-wideint-private.h"
#include "calendar-scheduler.h"
#include "default-simulator-impl.h"
#include "event-id.h"
#include "event-impl.h"
#include "heap-scheduler.h"
#include "high-precision-cairo.h"
#include "high-precision.h"
#include "list-scheduler.h"
#include "make-event.h"
#include "map-scheduler.h"
#include "ns2-calendar-scheduler.h"
#include "nstime.h"
#include "realtime-simulator-impl.h"
#include "scheduler.h"
#include "simulation-singleton.h"
#include "simulator-impl.h"
#include "simulator.h"
#include "synchronizer.h"
#include "time-base.h"
#include "timer-impl.h"
#include "timer.h"
#include "wall-clock-synchronizer.h"
#include "watchdog.h"
#endif
