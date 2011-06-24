################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/internet-stack/arp-cache.cc \
../src/internet-stack/arp-header.cc \
../src/internet-stack/arp-l3-protocol.cc \
../src/internet-stack/icmpv4-l4-protocol.cc \
../src/internet-stack/icmpv4.cc \
../src/internet-stack/icmpv6-header.cc \
../src/internet-stack/icmpv6-l4-protocol.cc \
../src/internet-stack/ipv4-end-point-demux.cc \
../src/internet-stack/ipv4-end-point.cc \
../src/internet-stack/ipv4-interface.cc \
../src/internet-stack/ipv4-l3-protocol.cc \
../src/internet-stack/ipv4-l4-protocol.cc \
../src/internet-stack/ipv4-raw-socket-factory-impl.cc \
../src/internet-stack/ipv4-raw-socket-impl.cc \
../src/internet-stack/ipv4-raw-test.cc \
../src/internet-stack/ipv4-test.cc \
../src/internet-stack/ipv6-autoconfigured-prefix.cc \
../src/internet-stack/ipv6-end-point-demux.cc \
../src/internet-stack/ipv6-end-point.cc \
../src/internet-stack/ipv6-extension-demux.cc \
../src/internet-stack/ipv6-extension-header-test-suite.cc \
../src/internet-stack/ipv6-extension-header.cc \
../src/internet-stack/ipv6-extension.cc \
../src/internet-stack/ipv6-interface.cc \
../src/internet-stack/ipv6-l3-protocol.cc \
../src/internet-stack/ipv6-l4-protocol.cc \
../src/internet-stack/ipv6-option-demux.cc \
../src/internet-stack/ipv6-option-header.cc \
../src/internet-stack/ipv6-option.cc \
../src/internet-stack/ipv6-raw-socket-factory-impl.cc \
../src/internet-stack/ipv6-raw-socket-impl.cc \
../src/internet-stack/ipv6-test.cc \
../src/internet-stack/loopback-net-device.cc \
../src/internet-stack/ndisc-cache.cc \
../src/internet-stack/nsc-sysctl.cc \
../src/internet-stack/nsc-tcp-l4-protocol.cc \
../src/internet-stack/nsc-tcp-socket-factory-impl.cc \
../src/internet-stack/nsc-tcp-socket-impl.cc \
../src/internet-stack/pending-data.cc \
../src/internet-stack/rtt-estimator.cc \
../src/internet-stack/tcp-header.cc \
../src/internet-stack/tcp-l4-protocol.cc \
../src/internet-stack/tcp-newreno.cc \
../src/internet-stack/tcp-reno.cc \
../src/internet-stack/tcp-rfc793.cc \
../src/internet-stack/tcp-rx-buffer.cc \
../src/internet-stack/tcp-socket-base.cc \
../src/internet-stack/tcp-socket-factory-impl.cc \
../src/internet-stack/tcp-tahoe.cc \
../src/internet-stack/tcp-test.cc \
../src/internet-stack/tcp-tx-buffer.cc \
../src/internet-stack/udp-header.cc \
../src/internet-stack/udp-l4-protocol.cc \
../src/internet-stack/udp-socket-factory-impl.cc \
../src/internet-stack/udp-socket-impl.cc \
../src/internet-stack/udp-test.cc 

OBJS += \
./src/internet-stack/arp-cache.o \
./src/internet-stack/arp-header.o \
./src/internet-stack/arp-l3-protocol.o \
./src/internet-stack/icmpv4-l4-protocol.o \
./src/internet-stack/icmpv4.o \
./src/internet-stack/icmpv6-header.o \
./src/internet-stack/icmpv6-l4-protocol.o \
./src/internet-stack/ipv4-end-point-demux.o \
./src/internet-stack/ipv4-end-point.o \
./src/internet-stack/ipv4-interface.o \
./src/internet-stack/ipv4-l3-protocol.o \
./src/internet-stack/ipv4-l4-protocol.o \
./src/internet-stack/ipv4-raw-socket-factory-impl.o \
./src/internet-stack/ipv4-raw-socket-impl.o \
./src/internet-stack/ipv4-raw-test.o \
./src/internet-stack/ipv4-test.o \
./src/internet-stack/ipv6-autoconfigured-prefix.o \
./src/internet-stack/ipv6-end-point-demux.o \
./src/internet-stack/ipv6-end-point.o \
./src/internet-stack/ipv6-extension-demux.o \
./src/internet-stack/ipv6-extension-header-test-suite.o \
./src/internet-stack/ipv6-extension-header.o \
./src/internet-stack/ipv6-extension.o \
./src/internet-stack/ipv6-interface.o \
./src/internet-stack/ipv6-l3-protocol.o \
./src/internet-stack/ipv6-l4-protocol.o \
./src/internet-stack/ipv6-option-demux.o \
./src/internet-stack/ipv6-option-header.o \
./src/internet-stack/ipv6-option.o \
./src/internet-stack/ipv6-raw-socket-factory-impl.o \
./src/internet-stack/ipv6-raw-socket-impl.o \
./src/internet-stack/ipv6-test.o \
./src/internet-stack/loopback-net-device.o \
./src/internet-stack/ndisc-cache.o \
./src/internet-stack/nsc-sysctl.o \
./src/internet-stack/nsc-tcp-l4-protocol.o \
./src/internet-stack/nsc-tcp-socket-factory-impl.o \
./src/internet-stack/nsc-tcp-socket-impl.o \
./src/internet-stack/pending-data.o \
./src/internet-stack/rtt-estimator.o \
./src/internet-stack/tcp-header.o \
./src/internet-stack/tcp-l4-protocol.o \
./src/internet-stack/tcp-newreno.o \
./src/internet-stack/tcp-reno.o \
./src/internet-stack/tcp-rfc793.o \
./src/internet-stack/tcp-rx-buffer.o \
./src/internet-stack/tcp-socket-base.o \
./src/internet-stack/tcp-socket-factory-impl.o \
./src/internet-stack/tcp-tahoe.o \
./src/internet-stack/tcp-test.o \
./src/internet-stack/tcp-tx-buffer.o \
./src/internet-stack/udp-header.o \
./src/internet-stack/udp-l4-protocol.o \
./src/internet-stack/udp-socket-factory-impl.o \
./src/internet-stack/udp-socket-impl.o \
./src/internet-stack/udp-test.o 

CC_DEPS += \
./src/internet-stack/arp-cache.d \
./src/internet-stack/arp-header.d \
./src/internet-stack/arp-l3-protocol.d \
./src/internet-stack/icmpv4-l4-protocol.d \
./src/internet-stack/icmpv4.d \
./src/internet-stack/icmpv6-header.d \
./src/internet-stack/icmpv6-l4-protocol.d \
./src/internet-stack/ipv4-end-point-demux.d \
./src/internet-stack/ipv4-end-point.d \
./src/internet-stack/ipv4-interface.d \
./src/internet-stack/ipv4-l3-protocol.d \
./src/internet-stack/ipv4-l4-protocol.d \
./src/internet-stack/ipv4-raw-socket-factory-impl.d \
./src/internet-stack/ipv4-raw-socket-impl.d \
./src/internet-stack/ipv4-raw-test.d \
./src/internet-stack/ipv4-test.d \
./src/internet-stack/ipv6-autoconfigured-prefix.d \
./src/internet-stack/ipv6-end-point-demux.d \
./src/internet-stack/ipv6-end-point.d \
./src/internet-stack/ipv6-extension-demux.d \
./src/internet-stack/ipv6-extension-header-test-suite.d \
./src/internet-stack/ipv6-extension-header.d \
./src/internet-stack/ipv6-extension.d \
./src/internet-stack/ipv6-interface.d \
./src/internet-stack/ipv6-l3-protocol.d \
./src/internet-stack/ipv6-l4-protocol.d \
./src/internet-stack/ipv6-option-demux.d \
./src/internet-stack/ipv6-option-header.d \
./src/internet-stack/ipv6-option.d \
./src/internet-stack/ipv6-raw-socket-factory-impl.d \
./src/internet-stack/ipv6-raw-socket-impl.d \
./src/internet-stack/ipv6-test.d \
./src/internet-stack/loopback-net-device.d \
./src/internet-stack/ndisc-cache.d \
./src/internet-stack/nsc-sysctl.d \
./src/internet-stack/nsc-tcp-l4-protocol.d \
./src/internet-stack/nsc-tcp-socket-factory-impl.d \
./src/internet-stack/nsc-tcp-socket-impl.d \
./src/internet-stack/pending-data.d \
./src/internet-stack/rtt-estimator.d \
./src/internet-stack/tcp-header.d \
./src/internet-stack/tcp-l4-protocol.d \
./src/internet-stack/tcp-newreno.d \
./src/internet-stack/tcp-reno.d \
./src/internet-stack/tcp-rfc793.d \
./src/internet-stack/tcp-rx-buffer.d \
./src/internet-stack/tcp-socket-base.d \
./src/internet-stack/tcp-socket-factory-impl.d \
./src/internet-stack/tcp-tahoe.d \
./src/internet-stack/tcp-test.d \
./src/internet-stack/tcp-tx-buffer.d \
./src/internet-stack/udp-header.d \
./src/internet-stack/udp-l4-protocol.d \
./src/internet-stack/udp-socket-factory-impl.d \
./src/internet-stack/udp-socket-impl.d \
./src/internet-stack/udp-test.d 


# Each subdirectory must supply rules for building sources it contributes
src/internet-stack/%.o: ../src/internet-stack/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


