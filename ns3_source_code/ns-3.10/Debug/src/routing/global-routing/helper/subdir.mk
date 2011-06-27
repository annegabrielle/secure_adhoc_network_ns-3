################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/routing/global-routing/helper/ipv4-global-routing-helper.cc 

OBJS += \
./src/routing/global-routing/helper/ipv4-global-routing-helper.o 

CC_DEPS += \
./src/routing/global-routing/helper/ipv4-global-routing-helper.d 


# Each subdirectory must supply rules for building sources it contributes
src/routing/global-routing/helper/%.o: ../src/routing/global-routing/helper/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


