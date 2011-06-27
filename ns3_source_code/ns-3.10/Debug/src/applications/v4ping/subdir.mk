################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/applications/v4ping/v4ping.cc 

OBJS += \
./src/applications/v4ping/v4ping.o 

CC_DEPS += \
./src/applications/v4ping/v4ping.d 


# Each subdirectory must supply rules for building sources it contributes
src/applications/v4ping/%.o: ../src/applications/v4ping/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


