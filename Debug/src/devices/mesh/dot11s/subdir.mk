################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/devices/mesh/dot11s/airtime-metric.cc \
../src/devices/mesh/dot11s/dot11s-mac-header.cc \
../src/devices/mesh/dot11s/hwmp-protocol-mac.cc \
../src/devices/mesh/dot11s/hwmp-protocol.cc \
../src/devices/mesh/dot11s/hwmp-rtable.cc \
../src/devices/mesh/dot11s/hwmp-tag.cc \
../src/devices/mesh/dot11s/ie-dot11s-beacon-timing.cc \
../src/devices/mesh/dot11s/ie-dot11s-configuration.cc \
../src/devices/mesh/dot11s/ie-dot11s-id.cc \
../src/devices/mesh/dot11s/ie-dot11s-metric-report.cc \
../src/devices/mesh/dot11s/ie-dot11s-peer-management.cc \
../src/devices/mesh/dot11s/ie-dot11s-peering-protocol.cc \
../src/devices/mesh/dot11s/ie-dot11s-perr.cc \
../src/devices/mesh/dot11s/ie-dot11s-prep.cc \
../src/devices/mesh/dot11s/ie-dot11s-preq.cc \
../src/devices/mesh/dot11s/ie-dot11s-rann.cc \
../src/devices/mesh/dot11s/peer-link-frame.cc \
../src/devices/mesh/dot11s/peer-link.cc \
../src/devices/mesh/dot11s/peer-management-protocol-mac.cc \
../src/devices/mesh/dot11s/peer-management-protocol.cc 

OBJS += \
./src/devices/mesh/dot11s/airtime-metric.o \
./src/devices/mesh/dot11s/dot11s-mac-header.o \
./src/devices/mesh/dot11s/hwmp-protocol-mac.o \
./src/devices/mesh/dot11s/hwmp-protocol.o \
./src/devices/mesh/dot11s/hwmp-rtable.o \
./src/devices/mesh/dot11s/hwmp-tag.o \
./src/devices/mesh/dot11s/ie-dot11s-beacon-timing.o \
./src/devices/mesh/dot11s/ie-dot11s-configuration.o \
./src/devices/mesh/dot11s/ie-dot11s-id.o \
./src/devices/mesh/dot11s/ie-dot11s-metric-report.o \
./src/devices/mesh/dot11s/ie-dot11s-peer-management.o \
./src/devices/mesh/dot11s/ie-dot11s-peering-protocol.o \
./src/devices/mesh/dot11s/ie-dot11s-perr.o \
./src/devices/mesh/dot11s/ie-dot11s-prep.o \
./src/devices/mesh/dot11s/ie-dot11s-preq.o \
./src/devices/mesh/dot11s/ie-dot11s-rann.o \
./src/devices/mesh/dot11s/peer-link-frame.o \
./src/devices/mesh/dot11s/peer-link.o \
./src/devices/mesh/dot11s/peer-management-protocol-mac.o \
./src/devices/mesh/dot11s/peer-management-protocol.o 

CC_DEPS += \
./src/devices/mesh/dot11s/airtime-metric.d \
./src/devices/mesh/dot11s/dot11s-mac-header.d \
./src/devices/mesh/dot11s/hwmp-protocol-mac.d \
./src/devices/mesh/dot11s/hwmp-protocol.d \
./src/devices/mesh/dot11s/hwmp-rtable.d \
./src/devices/mesh/dot11s/hwmp-tag.d \
./src/devices/mesh/dot11s/ie-dot11s-beacon-timing.d \
./src/devices/mesh/dot11s/ie-dot11s-configuration.d \
./src/devices/mesh/dot11s/ie-dot11s-id.d \
./src/devices/mesh/dot11s/ie-dot11s-metric-report.d \
./src/devices/mesh/dot11s/ie-dot11s-peer-management.d \
./src/devices/mesh/dot11s/ie-dot11s-peering-protocol.d \
./src/devices/mesh/dot11s/ie-dot11s-perr.d \
./src/devices/mesh/dot11s/ie-dot11s-prep.d \
./src/devices/mesh/dot11s/ie-dot11s-preq.d \
./src/devices/mesh/dot11s/ie-dot11s-rann.d \
./src/devices/mesh/dot11s/peer-link-frame.d \
./src/devices/mesh/dot11s/peer-link.d \
./src/devices/mesh/dot11s/peer-management-protocol-mac.d \
./src/devices/mesh/dot11s/peer-management-protocol.d 


# Each subdirectory must supply rules for building sources it contributes
src/devices/mesh/dot11s/%.o: ../src/devices/mesh/dot11s/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


