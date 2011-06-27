################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/devices/uan/test/uan-energy-model-test.cc \
../src/devices/uan/test/uan-test.cc 

OBJS += \
./src/devices/uan/test/uan-energy-model-test.o \
./src/devices/uan/test/uan-test.o 

CC_DEPS += \
./src/devices/uan/test/uan-energy-model-test.d \
./src/devices/uan/test/uan-test.d 


# Each subdirectory must supply rules for building sources it contributes
src/devices/uan/test/%.o: ../src/devices/uan/test/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


