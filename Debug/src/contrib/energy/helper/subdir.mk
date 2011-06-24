################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/contrib/energy/helper/basic-energy-source-helper.cc \
../src/contrib/energy/helper/energy-model-helper.cc \
../src/contrib/energy/helper/energy-source-container.cc \
../src/contrib/energy/helper/rv-battery-model-helper.cc \
../src/contrib/energy/helper/wifi-radio-energy-model-helper.cc 

OBJS += \
./src/contrib/energy/helper/basic-energy-source-helper.o \
./src/contrib/energy/helper/energy-model-helper.o \
./src/contrib/energy/helper/energy-source-container.o \
./src/contrib/energy/helper/rv-battery-model-helper.o \
./src/contrib/energy/helper/wifi-radio-energy-model-helper.o 

CC_DEPS += \
./src/contrib/energy/helper/basic-energy-source-helper.d \
./src/contrib/energy/helper/energy-model-helper.d \
./src/contrib/energy/helper/energy-source-container.d \
./src/contrib/energy/helper/rv-battery-model-helper.d \
./src/contrib/energy/helper/wifi-radio-energy-model-helper.d 


# Each subdirectory must supply rules for building sources it contributes
src/contrib/energy/helper/%.o: ../src/contrib/energy/helper/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


