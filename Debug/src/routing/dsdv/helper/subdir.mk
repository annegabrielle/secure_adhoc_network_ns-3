################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/routing/dsdv/helper/dsdv-helper.cc 

OBJS += \
./src/routing/dsdv/helper/dsdv-helper.o 

CC_DEPS += \
./src/routing/dsdv/helper/dsdv-helper.d 


# Each subdirectory must supply rules for building sources it contributes
src/routing/dsdv/helper/%.o: ../src/routing/dsdv/helper/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


