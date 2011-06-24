################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/devices/uan/helper/acoustic-modem-energy-model-helper.cc \
../src/devices/uan/helper/uan-helper.cc 

OBJS += \
./src/devices/uan/helper/acoustic-modem-energy-model-helper.o \
./src/devices/uan/helper/uan-helper.o 

CC_DEPS += \
./src/devices/uan/helper/acoustic-modem-energy-model-helper.d \
./src/devices/uan/helper/uan-helper.d 


# Each subdirectory must supply rules for building sources it contributes
src/devices/uan/helper/%.o: ../src/devices/uan/helper/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


