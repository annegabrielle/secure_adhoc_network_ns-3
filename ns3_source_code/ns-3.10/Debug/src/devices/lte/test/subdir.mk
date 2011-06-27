################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/devices/lte/test/lte-bearer-test.cc \
../src/devices/lte/test/lte-device-test.cc \
../src/devices/lte/test/lte-phy-test.cc \
../src/devices/lte/test/lte-propagation-loss-model-test.cc 

OBJS += \
./src/devices/lte/test/lte-bearer-test.o \
./src/devices/lte/test/lte-device-test.o \
./src/devices/lte/test/lte-phy-test.o \
./src/devices/lte/test/lte-propagation-loss-model-test.o 

CC_DEPS += \
./src/devices/lte/test/lte-bearer-test.d \
./src/devices/lte/test/lte-device-test.d \
./src/devices/lte/test/lte-phy-test.d \
./src/devices/lte/test/lte-propagation-loss-model-test.d 


# Each subdirectory must supply rules for building sources it contributes
src/devices/lte/test/%.o: ../src/devices/lte/test/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


