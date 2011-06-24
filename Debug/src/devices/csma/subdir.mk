################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/devices/csma/backoff.cc \
../src/devices/csma/csma-channel.cc \
../src/devices/csma/csma-net-device.cc 

OBJS += \
./src/devices/csma/backoff.o \
./src/devices/csma/csma-channel.o \
./src/devices/csma/csma-net-device.o 

CC_DEPS += \
./src/devices/csma/backoff.d \
./src/devices/csma/csma-channel.d \
./src/devices/csma/csma-net-device.d 


# Each subdirectory must supply rules for building sources it contributes
src/devices/csma/%.o: ../src/devices/csma/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


