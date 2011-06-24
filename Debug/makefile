################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include utils/subdir.mk
-include src/tools/visualizer/model/subdir.mk
-include src/test/subdir.mk
-include src/test/perf/subdir.mk
-include src/test/nsctcp/subdir.mk
-include src/test/ns3wifi/subdir.mk
-include src/test/ns3tcp/subdir.mk
-include src/simulator/subdir.mk
-include src/routing/static-routing/model/subdir.mk
-include src/routing/static-routing/helper/subdir.mk
-include src/routing/olsr/test/subdir.mk
-include src/routing/olsr/model/subdir.mk
-include src/routing/olsr/helper/subdir.mk
-include src/routing/olsr/examples/subdir.mk
-include src/routing/nix-vector-routing/subdir.mk
-include src/routing/list-routing/model/subdir.mk
-include src/routing/list-routing/helper/subdir.mk
-include src/routing/global-routing/model/subdir.mk
-include src/routing/global-routing/helper/subdir.mk
-include src/routing/dsdv/test/subdir.mk
-include src/routing/dsdv/model/subdir.mk
-include src/routing/dsdv/helper/subdir.mk
-include src/routing/dsdv/examples/subdir.mk
-include src/routing/aodv/test/subdir.mk
-include src/routing/aodv/subdir.mk
-include src/node/subdir.mk
-include src/mpi/subdir.mk
-include src/mobility/subdir.mk
-include src/internet-stack/subdir.mk
-include src/helper/subdir.mk
-include src/devices/wimax/subdir.mk
-include src/devices/wifi/subdir.mk
-include src/devices/virtual-net-device/model/subdir.mk
-include src/devices/virtual-net-device/examples/subdir.mk
-include src/devices/uan/test/subdir.mk
-include src/devices/uan/model/subdir.mk
-include src/devices/uan/helper/subdir.mk
-include src/devices/uan/examples/subdir.mk
-include src/devices/tap-bridge/subdir.mk
-include src/devices/spectrum/subdir.mk
-include src/devices/point-to-point/subdir.mk
-include src/devices/mesh/subdir.mk
-include src/devices/mesh/flame/test/subdir.mk
-include src/devices/mesh/flame/subdir.mk
-include src/devices/mesh/dot11s/test/subdir.mk
-include src/devices/mesh/dot11s/subdir.mk
-include src/devices/lte/test/subdir.mk
-include src/devices/lte/model/subdir.mk
-include src/devices/lte/helper/subdir.mk
-include src/devices/lte/examples/subdir.mk
-include src/devices/emu/subdir.mk
-include src/devices/csma/subdir.mk
-include src/devices/bridge/model/subdir.mk
-include src/devices/bridge/helper/subdir.mk
-include src/devices/bridge/examples/subdir.mk
-include src/core/subdir.mk
-include src/contrib/subdir.mk
-include src/contrib/topology-read/subdir.mk
-include src/contrib/stats/subdir.mk
-include src/contrib/flow-monitor/model/subdir.mk
-include src/contrib/flow-monitor/helper/subdir.mk
-include src/contrib/energy/test/subdir.mk
-include src/contrib/energy/model/subdir.mk
-include src/contrib/energy/helper/subdir.mk
-include src/contrib/energy/examples/subdir.mk
-include src/common/subdir.mk
-include src/applications/v4ping/subdir.mk
-include src/applications/udp-echo/subdir.mk
-include src/applications/udp-client-server/subdir.mk
-include src/applications/radvd/subdir.mk
-include src/applications/ping6/subdir.mk
-include src/applications/packet-sink/subdir.mk
-include src/applications/onoff/subdir.mk
-include src/applications/bulk-send/subdir.mk
-include scratch/subdir.mk
-include scratch/multiple-sources/subdir.mk
-include samples/subdir.mk
-include examples/wireless/subdir.mk
-include examples/wimax/subdir.mk
-include examples/udp-client-server/subdir.mk
-include examples/udp/subdir.mk
-include examples/tutorial/subdir.mk
-include examples/topology-read/subdir.mk
-include examples/tcp/subdir.mk
-include examples/tap/subdir.mk
-include examples/stats/subdir.mk
-include examples/spectrum/subdir.mk
-include examples/socket/subdir.mk
-include examples/routing/subdir.mk
-include examples/realtime/subdir.mk
-include examples/naming/subdir.mk
-include examples/mpi/subdir.mk
-include examples/mobility/subdir.mk
-include examples/mesh/subdir.mk
-include examples/matrix-topology/subdir.mk
-include examples/ipv6/subdir.mk
-include examples/error-model/subdir.mk
-include examples/energy/subdir.mk
-include examples/emulation/subdir.mk
-include examples/csma/subdir.mk
-include examples/animation/subdir.mk
-include bindings/python/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: ns-3.10

# Tool invocations
ns-3.10: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	g++  -o"ns-3.10" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C++_DEPS)$(C_DEPS)$(CC_DEPS)$(CPP_DEPS)$(EXECUTABLES)$(CXX_DEPS)$(C_UPPER_DEPS) ns-3.10
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
