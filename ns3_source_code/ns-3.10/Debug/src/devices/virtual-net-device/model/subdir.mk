################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/devices/virtual-net-device/model/virtual-net-device.cc 

OBJS += \
./src/devices/virtual-net-device/model/virtual-net-device.o 

CC_DEPS += \
./src/devices/virtual-net-device/model/virtual-net-device.d 


# Each subdirectory must supply rules for building sources it contributes
src/devices/virtual-net-device/model/%.o: ../src/devices/virtual-net-device/model/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


