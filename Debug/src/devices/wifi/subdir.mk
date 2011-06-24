################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/devices/wifi/aarf-wifi-manager.cc \
../src/devices/wifi/aarfcd-wifi-manager.cc \
../src/devices/wifi/adhoc-wifi-mac.cc \
../src/devices/wifi/amrr-wifi-manager.cc \
../src/devices/wifi/amsdu-subframe-header.cc \
../src/devices/wifi/ap-wifi-mac.cc \
../src/devices/wifi/arf-wifi-manager.cc \
../src/devices/wifi/block-ack-agreement.cc \
../src/devices/wifi/block-ack-cache.cc \
../src/devices/wifi/block-ack-manager.cc \
../src/devices/wifi/block-ack-test-suite.cc \
../src/devices/wifi/capability-information.cc \
../src/devices/wifi/cara-wifi-manager.cc \
../src/devices/wifi/constant-rate-wifi-manager.cc \
../src/devices/wifi/ctrl-headers.cc \
../src/devices/wifi/dca-txop.cc \
../src/devices/wifi/dcf-manager-test.cc \
../src/devices/wifi/dcf-manager.cc \
../src/devices/wifi/dcf.cc \
../src/devices/wifi/dsss-error-rate-model.cc \
../src/devices/wifi/edca-txop-n.cc \
../src/devices/wifi/error-rate-model.cc \
../src/devices/wifi/ideal-wifi-manager.cc \
../src/devices/wifi/interference-helper-tx-duration-test.cc \
../src/devices/wifi/interference-helper.cc \
../src/devices/wifi/mac-low.cc \
../src/devices/wifi/mac-rx-middle.cc \
../src/devices/wifi/mac-tx-middle.cc \
../src/devices/wifi/mgt-headers.cc \
../src/devices/wifi/minstrel-wifi-manager.cc \
../src/devices/wifi/msdu-aggregator.cc \
../src/devices/wifi/msdu-standard-aggregator.cc \
../src/devices/wifi/nist-error-rate-model.cc \
../src/devices/wifi/onoe-wifi-manager.cc \
../src/devices/wifi/originator-block-ack-agreement.cc \
../src/devices/wifi/qos-blocked-destinations.cc \
../src/devices/wifi/qos-tag.cc \
../src/devices/wifi/qos-utils.cc \
../src/devices/wifi/random-stream.cc \
../src/devices/wifi/regular-wifi-mac.cc \
../src/devices/wifi/rraa-wifi-manager.cc \
../src/devices/wifi/ssid.cc \
../src/devices/wifi/sta-wifi-mac.cc \
../src/devices/wifi/status-code.cc \
../src/devices/wifi/supported-rates.cc \
../src/devices/wifi/wifi-channel.cc \
../src/devices/wifi/wifi-information-element-vector.cc \
../src/devices/wifi/wifi-information-element.cc \
../src/devices/wifi/wifi-mac-header.cc \
../src/devices/wifi/wifi-mac-queue.cc \
../src/devices/wifi/wifi-mac-trailer.cc \
../src/devices/wifi/wifi-mac.cc \
../src/devices/wifi/wifi-mode.cc \
../src/devices/wifi/wifi-net-device.cc \
../src/devices/wifi/wifi-phy-state-helper.cc \
../src/devices/wifi/wifi-phy-test.cc \
../src/devices/wifi/wifi-phy.cc \
../src/devices/wifi/wifi-remote-station-manager.cc \
../src/devices/wifi/wifi-test.cc \
../src/devices/wifi/yans-error-rate-model.cc \
../src/devices/wifi/yans-wifi-channel.cc \
../src/devices/wifi/yans-wifi-phy.cc 

OBJS += \
./src/devices/wifi/aarf-wifi-manager.o \
./src/devices/wifi/aarfcd-wifi-manager.o \
./src/devices/wifi/adhoc-wifi-mac.o \
./src/devices/wifi/amrr-wifi-manager.o \
./src/devices/wifi/amsdu-subframe-header.o \
./src/devices/wifi/ap-wifi-mac.o \
./src/devices/wifi/arf-wifi-manager.o \
./src/devices/wifi/block-ack-agreement.o \
./src/devices/wifi/block-ack-cache.o \
./src/devices/wifi/block-ack-manager.o \
./src/devices/wifi/block-ack-test-suite.o \
./src/devices/wifi/capability-information.o \
./src/devices/wifi/cara-wifi-manager.o \
./src/devices/wifi/constant-rate-wifi-manager.o \
./src/devices/wifi/ctrl-headers.o \
./src/devices/wifi/dca-txop.o \
./src/devices/wifi/dcf-manager-test.o \
./src/devices/wifi/dcf-manager.o \
./src/devices/wifi/dcf.o \
./src/devices/wifi/dsss-error-rate-model.o \
./src/devices/wifi/edca-txop-n.o \
./src/devices/wifi/error-rate-model.o \
./src/devices/wifi/ideal-wifi-manager.o \
./src/devices/wifi/interference-helper-tx-duration-test.o \
./src/devices/wifi/interference-helper.o \
./src/devices/wifi/mac-low.o \
./src/devices/wifi/mac-rx-middle.o \
./src/devices/wifi/mac-tx-middle.o \
./src/devices/wifi/mgt-headers.o \
./src/devices/wifi/minstrel-wifi-manager.o \
./src/devices/wifi/msdu-aggregator.o \
./src/devices/wifi/msdu-standard-aggregator.o \
./src/devices/wifi/nist-error-rate-model.o \
./src/devices/wifi/onoe-wifi-manager.o \
./src/devices/wifi/originator-block-ack-agreement.o \
./src/devices/wifi/qos-blocked-destinations.o \
./src/devices/wifi/qos-tag.o \
./src/devices/wifi/qos-utils.o \
./src/devices/wifi/random-stream.o \
./src/devices/wifi/regular-wifi-mac.o \
./src/devices/wifi/rraa-wifi-manager.o \
./src/devices/wifi/ssid.o \
./src/devices/wifi/sta-wifi-mac.o \
./src/devices/wifi/status-code.o \
./src/devices/wifi/supported-rates.o \
./src/devices/wifi/wifi-channel.o \
./src/devices/wifi/wifi-information-element-vector.o \
./src/devices/wifi/wifi-information-element.o \
./src/devices/wifi/wifi-mac-header.o \
./src/devices/wifi/wifi-mac-queue.o \
./src/devices/wifi/wifi-mac-trailer.o \
./src/devices/wifi/wifi-mac.o \
./src/devices/wifi/wifi-mode.o \
./src/devices/wifi/wifi-net-device.o \
./src/devices/wifi/wifi-phy-state-helper.o \
./src/devices/wifi/wifi-phy-test.o \
./src/devices/wifi/wifi-phy.o \
./src/devices/wifi/wifi-remote-station-manager.o \
./src/devices/wifi/wifi-test.o \
./src/devices/wifi/yans-error-rate-model.o \
./src/devices/wifi/yans-wifi-channel.o \
./src/devices/wifi/yans-wifi-phy.o 

CC_DEPS += \
./src/devices/wifi/aarf-wifi-manager.d \
./src/devices/wifi/aarfcd-wifi-manager.d \
./src/devices/wifi/adhoc-wifi-mac.d \
./src/devices/wifi/amrr-wifi-manager.d \
./src/devices/wifi/amsdu-subframe-header.d \
./src/devices/wifi/ap-wifi-mac.d \
./src/devices/wifi/arf-wifi-manager.d \
./src/devices/wifi/block-ack-agreement.d \
./src/devices/wifi/block-ack-cache.d \
./src/devices/wifi/block-ack-manager.d \
./src/devices/wifi/block-ack-test-suite.d \
./src/devices/wifi/capability-information.d \
./src/devices/wifi/cara-wifi-manager.d \
./src/devices/wifi/constant-rate-wifi-manager.d \
./src/devices/wifi/ctrl-headers.d \
./src/devices/wifi/dca-txop.d \
./src/devices/wifi/dcf-manager-test.d \
./src/devices/wifi/dcf-manager.d \
./src/devices/wifi/dcf.d \
./src/devices/wifi/dsss-error-rate-model.d \
./src/devices/wifi/edca-txop-n.d \
./src/devices/wifi/error-rate-model.d \
./src/devices/wifi/ideal-wifi-manager.d \
./src/devices/wifi/interference-helper-tx-duration-test.d \
./src/devices/wifi/interference-helper.d \
./src/devices/wifi/mac-low.d \
./src/devices/wifi/mac-rx-middle.d \
./src/devices/wifi/mac-tx-middle.d \
./src/devices/wifi/mgt-headers.d \
./src/devices/wifi/minstrel-wifi-manager.d \
./src/devices/wifi/msdu-aggregator.d \
./src/devices/wifi/msdu-standard-aggregator.d \
./src/devices/wifi/nist-error-rate-model.d \
./src/devices/wifi/onoe-wifi-manager.d \
./src/devices/wifi/originator-block-ack-agreement.d \
./src/devices/wifi/qos-blocked-destinations.d \
./src/devices/wifi/qos-tag.d \
./src/devices/wifi/qos-utils.d \
./src/devices/wifi/random-stream.d \
./src/devices/wifi/regular-wifi-mac.d \
./src/devices/wifi/rraa-wifi-manager.d \
./src/devices/wifi/ssid.d \
./src/devices/wifi/sta-wifi-mac.d \
./src/devices/wifi/status-code.d \
./src/devices/wifi/supported-rates.d \
./src/devices/wifi/wifi-channel.d \
./src/devices/wifi/wifi-information-element-vector.d \
./src/devices/wifi/wifi-information-element.d \
./src/devices/wifi/wifi-mac-header.d \
./src/devices/wifi/wifi-mac-queue.d \
./src/devices/wifi/wifi-mac-trailer.d \
./src/devices/wifi/wifi-mac.d \
./src/devices/wifi/wifi-mode.d \
./src/devices/wifi/wifi-net-device.d \
./src/devices/wifi/wifi-phy-state-helper.d \
./src/devices/wifi/wifi-phy-test.d \
./src/devices/wifi/wifi-phy.d \
./src/devices/wifi/wifi-remote-station-manager.d \
./src/devices/wifi/wifi-test.d \
./src/devices/wifi/yans-error-rate-model.d \
./src/devices/wifi/yans-wifi-channel.d \
./src/devices/wifi/yans-wifi-phy.d 


# Each subdirectory must supply rules for building sources it contributes
src/devices/wifi/%.o: ../src/devices/wifi/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


