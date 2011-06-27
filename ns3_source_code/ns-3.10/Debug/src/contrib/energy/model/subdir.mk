################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/contrib/energy/model/basic-energy-source.cc \
../src/contrib/energy/model/device-energy-model-container.cc \
../src/contrib/energy/model/device-energy-model.cc \
../src/contrib/energy/model/energy-source.cc \
../src/contrib/energy/model/li-ion-energy-source.cc \
../src/contrib/energy/model/rv-battery-model.cc \
../src/contrib/energy/model/simple-device-energy-model.cc \
../src/contrib/energy/model/wifi-radio-energy-model.cc 

OBJS += \
./src/contrib/energy/model/basic-energy-source.o \
./src/contrib/energy/model/device-energy-model-container.o \
./src/contrib/energy/model/device-energy-model.o \
./src/contrib/energy/model/energy-source.o \
./src/contrib/energy/model/li-ion-energy-source.o \
./src/contrib/energy/model/rv-battery-model.o \
./src/contrib/energy/model/simple-device-energy-model.o \
./src/contrib/energy/model/wifi-radio-energy-model.o 

CC_DEPS += \
./src/contrib/energy/model/basic-energy-source.d \
./src/contrib/energy/model/device-energy-model-container.d \
./src/contrib/energy/model/device-energy-model.d \
./src/contrib/energy/model/energy-source.d \
./src/contrib/energy/model/li-ion-energy-source.d \
./src/contrib/energy/model/rv-battery-model.d \
./src/contrib/energy/model/simple-device-energy-model.d \
./src/contrib/energy/model/wifi-radio-energy-model.d 


# Each subdirectory must supply rules for building sources it contributes
src/contrib/energy/model/%.o: ../src/contrib/energy/model/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


