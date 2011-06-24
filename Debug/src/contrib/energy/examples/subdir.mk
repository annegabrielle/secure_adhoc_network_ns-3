################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/contrib/energy/examples/li-ion-energy-source.cc 

OBJS += \
./src/contrib/energy/examples/li-ion-energy-source.o 

CC_DEPS += \
./src/contrib/energy/examples/li-ion-energy-source.d 


# Each subdirectory must supply rules for building sources it contributes
src/contrib/energy/examples/%.o: ../src/contrib/energy/examples/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


