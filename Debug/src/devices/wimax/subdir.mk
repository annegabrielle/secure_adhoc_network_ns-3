################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/devices/wimax/bandwidth-manager.cc \
../src/devices/wimax/bs-link-manager.cc \
../src/devices/wimax/bs-net-device.cc \
../src/devices/wimax/bs-scheduler-rtps.cc \
../src/devices/wimax/bs-scheduler-simple.cc \
../src/devices/wimax/bs-scheduler.cc \
../src/devices/wimax/bs-service-flow-manager.cc \
../src/devices/wimax/bs-uplink-scheduler-mbqos.cc \
../src/devices/wimax/bs-uplink-scheduler-rtps.cc \
../src/devices/wimax/bs-uplink-scheduler-simple.cc \
../src/devices/wimax/bs-uplink-scheduler.cc \
../src/devices/wimax/burst-profile-manager.cc \
../src/devices/wimax/cid-factory.cc \
../src/devices/wimax/cid.cc \
../src/devices/wimax/connection-manager.cc \
../src/devices/wimax/crc8.cc \
../src/devices/wimax/cs-parameters.cc \
../src/devices/wimax/dl-mac-messages.cc \
../src/devices/wimax/ipcs-classifier-record.cc \
../src/devices/wimax/ipcs-classifier.cc \
../src/devices/wimax/mac-messages-test.cc \
../src/devices/wimax/mac-messages.cc \
../src/devices/wimax/ofdm-downlink-frame-prefix.cc \
../src/devices/wimax/phy-test.cc \
../src/devices/wimax/qos-test.cc \
../src/devices/wimax/send-params.cc \
../src/devices/wimax/service-flow-manager.cc \
../src/devices/wimax/service-flow-record.cc \
../src/devices/wimax/service-flow.cc \
../src/devices/wimax/simple-ofdm-send-param.cc \
../src/devices/wimax/simple-ofdm-wimax-channel.cc \
../src/devices/wimax/simple-ofdm-wimax-phy.cc \
../src/devices/wimax/snr-to-block-error-rate-manager.cc \
../src/devices/wimax/snr-to-block-error-rate-record.cc \
../src/devices/wimax/ss-link-manager.cc \
../src/devices/wimax/ss-mac-test.cc \
../src/devices/wimax/ss-manager.cc \
../src/devices/wimax/ss-net-device.cc \
../src/devices/wimax/ss-record.cc \
../src/devices/wimax/ss-scheduler.cc \
../src/devices/wimax/ss-service-flow-manager.cc \
../src/devices/wimax/ul-job.cc \
../src/devices/wimax/ul-mac-messages.cc \
../src/devices/wimax/wimax-channel.cc \
../src/devices/wimax/wimax-connection.cc \
../src/devices/wimax/wimax-fragmentation-test.cc \
../src/devices/wimax/wimax-mac-header.cc \
../src/devices/wimax/wimax-mac-queue.cc \
../src/devices/wimax/wimax-mac-to-mac-header.cc \
../src/devices/wimax/wimax-net-device.cc \
../src/devices/wimax/wimax-phy.cc \
../src/devices/wimax/wimax-service-flow-test.cc \
../src/devices/wimax/wimax-tlv-test.cc \
../src/devices/wimax/wimax-tlv.cc 

OBJS += \
./src/devices/wimax/bandwidth-manager.o \
./src/devices/wimax/bs-link-manager.o \
./src/devices/wimax/bs-net-device.o \
./src/devices/wimax/bs-scheduler-rtps.o \
./src/devices/wimax/bs-scheduler-simple.o \
./src/devices/wimax/bs-scheduler.o \
./src/devices/wimax/bs-service-flow-manager.o \
./src/devices/wimax/bs-uplink-scheduler-mbqos.o \
./src/devices/wimax/bs-uplink-scheduler-rtps.o \
./src/devices/wimax/bs-uplink-scheduler-simple.o \
./src/devices/wimax/bs-uplink-scheduler.o \
./src/devices/wimax/burst-profile-manager.o \
./src/devices/wimax/cid-factory.o \
./src/devices/wimax/cid.o \
./src/devices/wimax/connection-manager.o \
./src/devices/wimax/crc8.o \
./src/devices/wimax/cs-parameters.o \
./src/devices/wimax/dl-mac-messages.o \
./src/devices/wimax/ipcs-classifier-record.o \
./src/devices/wimax/ipcs-classifier.o \
./src/devices/wimax/mac-messages-test.o \
./src/devices/wimax/mac-messages.o \
./src/devices/wimax/ofdm-downlink-frame-prefix.o \
./src/devices/wimax/phy-test.o \
./src/devices/wimax/qos-test.o \
./src/devices/wimax/send-params.o \
./src/devices/wimax/service-flow-manager.o \
./src/devices/wimax/service-flow-record.o \
./src/devices/wimax/service-flow.o \
./src/devices/wimax/simple-ofdm-send-param.o \
./src/devices/wimax/simple-ofdm-wimax-channel.o \
./src/devices/wimax/simple-ofdm-wimax-phy.o \
./src/devices/wimax/snr-to-block-error-rate-manager.o \
./src/devices/wimax/snr-to-block-error-rate-record.o \
./src/devices/wimax/ss-link-manager.o \
./src/devices/wimax/ss-mac-test.o \
./src/devices/wimax/ss-manager.o \
./src/devices/wimax/ss-net-device.o \
./src/devices/wimax/ss-record.o \
./src/devices/wimax/ss-scheduler.o \
./src/devices/wimax/ss-service-flow-manager.o \
./src/devices/wimax/ul-job.o \
./src/devices/wimax/ul-mac-messages.o \
./src/devices/wimax/wimax-channel.o \
./src/devices/wimax/wimax-connection.o \
./src/devices/wimax/wimax-fragmentation-test.o \
./src/devices/wimax/wimax-mac-header.o \
./src/devices/wimax/wimax-mac-queue.o \
./src/devices/wimax/wimax-mac-to-mac-header.o \
./src/devices/wimax/wimax-net-device.o \
./src/devices/wimax/wimax-phy.o \
./src/devices/wimax/wimax-service-flow-test.o \
./src/devices/wimax/wimax-tlv-test.o \
./src/devices/wimax/wimax-tlv.o 

CC_DEPS += \
./src/devices/wimax/bandwidth-manager.d \
./src/devices/wimax/bs-link-manager.d \
./src/devices/wimax/bs-net-device.d \
./src/devices/wimax/bs-scheduler-rtps.d \
./src/devices/wimax/bs-scheduler-simple.d \
./src/devices/wimax/bs-scheduler.d \
./src/devices/wimax/bs-service-flow-manager.d \
./src/devices/wimax/bs-uplink-scheduler-mbqos.d \
./src/devices/wimax/bs-uplink-scheduler-rtps.d \
./src/devices/wimax/bs-uplink-scheduler-simple.d \
./src/devices/wimax/bs-uplink-scheduler.d \
./src/devices/wimax/burst-profile-manager.d \
./src/devices/wimax/cid-factory.d \
./src/devices/wimax/cid.d \
./src/devices/wimax/connection-manager.d \
./src/devices/wimax/crc8.d \
./src/devices/wimax/cs-parameters.d \
./src/devices/wimax/dl-mac-messages.d \
./src/devices/wimax/ipcs-classifier-record.d \
./src/devices/wimax/ipcs-classifier.d \
./src/devices/wimax/mac-messages-test.d \
./src/devices/wimax/mac-messages.d \
./src/devices/wimax/ofdm-downlink-frame-prefix.d \
./src/devices/wimax/phy-test.d \
./src/devices/wimax/qos-test.d \
./src/devices/wimax/send-params.d \
./src/devices/wimax/service-flow-manager.d \
./src/devices/wimax/service-flow-record.d \
./src/devices/wimax/service-flow.d \
./src/devices/wimax/simple-ofdm-send-param.d \
./src/devices/wimax/simple-ofdm-wimax-channel.d \
./src/devices/wimax/simple-ofdm-wimax-phy.d \
./src/devices/wimax/snr-to-block-error-rate-manager.d \
./src/devices/wimax/snr-to-block-error-rate-record.d \
./src/devices/wimax/ss-link-manager.d \
./src/devices/wimax/ss-mac-test.d \
./src/devices/wimax/ss-manager.d \
./src/devices/wimax/ss-net-device.d \
./src/devices/wimax/ss-record.d \
./src/devices/wimax/ss-scheduler.d \
./src/devices/wimax/ss-service-flow-manager.d \
./src/devices/wimax/ul-job.d \
./src/devices/wimax/ul-mac-messages.d \
./src/devices/wimax/wimax-channel.d \
./src/devices/wimax/wimax-connection.d \
./src/devices/wimax/wimax-fragmentation-test.d \
./src/devices/wimax/wimax-mac-header.d \
./src/devices/wimax/wimax-mac-queue.d \
./src/devices/wimax/wimax-mac-to-mac-header.d \
./src/devices/wimax/wimax-net-device.d \
./src/devices/wimax/wimax-phy.d \
./src/devices/wimax/wimax-service-flow-test.d \
./src/devices/wimax/wimax-tlv-test.d \
./src/devices/wimax/wimax-tlv.d 


# Each subdirectory must supply rules for building sources it contributes
src/devices/wimax/%.o: ../src/devices/wimax/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


