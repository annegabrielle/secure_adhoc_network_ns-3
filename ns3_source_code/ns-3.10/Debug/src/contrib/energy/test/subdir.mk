################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/contrib/energy/test/basic-energy-model-test.cc \
../src/contrib/energy/test/li-ion-energy-source-test.cc \
../src/contrib/energy/test/rv-battery-model-test.cc 

OBJS += \
./src/contrib/energy/test/basic-energy-model-test.o \
./src/contrib/energy/test/li-ion-energy-source-test.o \
./src/contrib/energy/test/rv-battery-model-test.o 

CC_DEPS += \
./src/contrib/energy/test/basic-energy-model-test.d \
./src/contrib/energy/test/li-ion-energy-source-test.d \
./src/contrib/energy/test/rv-battery-model-test.d 


# Each subdirectory must supply rules for building sources it contributes
src/contrib/energy/test/%.o: ../src/contrib/energy/test/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


