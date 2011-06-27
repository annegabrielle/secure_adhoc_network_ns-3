################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/devices/spectrum/aloha-noack-mac-header.cc \
../src/devices/spectrum/aloha-noack-net-device.cc \
../src/devices/spectrum/half-duplex-ideal-phy.cc \
../src/devices/spectrum/microwave-oven-spectrum-value-helper.cc \
../src/devices/spectrum/multi-model-spectrum-channel.cc \
../src/devices/spectrum/non-communicating-net-device.cc \
../src/devices/spectrum/single-model-spectrum-channel.cc \
../src/devices/spectrum/spectrum-analyzer.cc \
../src/devices/spectrum/spectrum-error-model.cc \
../src/devices/spectrum/spectrum-interference-test.cc \
../src/devices/spectrum/spectrum-interference.cc \
../src/devices/spectrum/spectrum-model-300kHz-300GHz-log.cc \
../src/devices/spectrum/spectrum-model-ism2400MHz-res1MHz.cc \
../src/devices/spectrum/waveform-generator.cc \
../src/devices/spectrum/wifi-spectrum-value-helper.cc 

OBJS += \
./src/devices/spectrum/aloha-noack-mac-header.o \
./src/devices/spectrum/aloha-noack-net-device.o \
./src/devices/spectrum/half-duplex-ideal-phy.o \
./src/devices/spectrum/microwave-oven-spectrum-value-helper.o \
./src/devices/spectrum/multi-model-spectrum-channel.o \
./src/devices/spectrum/non-communicating-net-device.o \
./src/devices/spectrum/single-model-spectrum-channel.o \
./src/devices/spectrum/spectrum-analyzer.o \
./src/devices/spectrum/spectrum-error-model.o \
./src/devices/spectrum/spectrum-interference-test.o \
./src/devices/spectrum/spectrum-interference.o \
./src/devices/spectrum/spectrum-model-300kHz-300GHz-log.o \
./src/devices/spectrum/spectrum-model-ism2400MHz-res1MHz.o \
./src/devices/spectrum/waveform-generator.o \
./src/devices/spectrum/wifi-spectrum-value-helper.o 

CC_DEPS += \
./src/devices/spectrum/aloha-noack-mac-header.d \
./src/devices/spectrum/aloha-noack-net-device.d \
./src/devices/spectrum/half-duplex-ideal-phy.d \
./src/devices/spectrum/microwave-oven-spectrum-value-helper.d \
./src/devices/spectrum/multi-model-spectrum-channel.d \
./src/devices/spectrum/non-communicating-net-device.d \
./src/devices/spectrum/single-model-spectrum-channel.d \
./src/devices/spectrum/spectrum-analyzer.d \
./src/devices/spectrum/spectrum-error-model.d \
./src/devices/spectrum/spectrum-interference-test.d \
./src/devices/spectrum/spectrum-interference.d \
./src/devices/spectrum/spectrum-model-300kHz-300GHz-log.d \
./src/devices/spectrum/spectrum-model-ism2400MHz-res1MHz.d \
./src/devices/spectrum/waveform-generator.d \
./src/devices/spectrum/wifi-spectrum-value-helper.d 


# Each subdirectory must supply rules for building sources it contributes
src/devices/spectrum/%.o: ../src/devices/spectrum/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


