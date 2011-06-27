################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/devices/lte/examples/lte-amc.cc \
../src/devices/lte/examples/lte-channel-model.cc \
../src/devices/lte/examples/lte-device.cc \
../src/devices/lte/examples/lte-multiple-flows.cc \
../src/devices/lte/examples/lte-phy-downlink.cc \
../src/devices/lte/examples/lte-phy-uplink.cc 

OBJS += \
./src/devices/lte/examples/lte-amc.o \
./src/devices/lte/examples/lte-channel-model.o \
./src/devices/lte/examples/lte-device.o \
./src/devices/lte/examples/lte-multiple-flows.o \
./src/devices/lte/examples/lte-phy-downlink.o \
./src/devices/lte/examples/lte-phy-uplink.o 

CC_DEPS += \
./src/devices/lte/examples/lte-amc.d \
./src/devices/lte/examples/lte-channel-model.d \
./src/devices/lte/examples/lte-device.d \
./src/devices/lte/examples/lte-multiple-flows.d \
./src/devices/lte/examples/lte-phy-downlink.d \
./src/devices/lte/examples/lte-phy-uplink.d 


# Each subdirectory must supply rules for building sources it contributes
src/devices/lte/examples/%.o: ../src/devices/lte/examples/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


