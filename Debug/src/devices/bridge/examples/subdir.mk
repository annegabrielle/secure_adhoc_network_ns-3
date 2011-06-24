################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/devices/bridge/examples/csma-bridge-one-hop.cc \
../src/devices/bridge/examples/csma-bridge.cc 

OBJS += \
./src/devices/bridge/examples/csma-bridge-one-hop.o \
./src/devices/bridge/examples/csma-bridge.o 

CC_DEPS += \
./src/devices/bridge/examples/csma-bridge-one-hop.d \
./src/devices/bridge/examples/csma-bridge.d 


# Each subdirectory must supply rules for building sources it contributes
src/devices/bridge/examples/%.o: ../src/devices/bridge/examples/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


