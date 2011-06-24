################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/devices/point-to-point/point-to-point-channel.cc \
../src/devices/point-to-point/point-to-point-net-device.cc \
../src/devices/point-to-point/point-to-point-remote-channel.cc \
../src/devices/point-to-point/point-to-point-test.cc \
../src/devices/point-to-point/ppp-header.cc 

OBJS += \
./src/devices/point-to-point/point-to-point-channel.o \
./src/devices/point-to-point/point-to-point-net-device.o \
./src/devices/point-to-point/point-to-point-remote-channel.o \
./src/devices/point-to-point/point-to-point-test.o \
./src/devices/point-to-point/ppp-header.o 

CC_DEPS += \
./src/devices/point-to-point/point-to-point-channel.d \
./src/devices/point-to-point/point-to-point-net-device.d \
./src/devices/point-to-point/point-to-point-remote-channel.d \
./src/devices/point-to-point/point-to-point-test.d \
./src/devices/point-to-point/ppp-header.d 


# Each subdirectory must supply rules for building sources it contributes
src/devices/point-to-point/%.o: ../src/devices/point-to-point/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


