################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/applications/bulk-send/bulk-send-application.cc 

OBJS += \
./src/applications/bulk-send/bulk-send-application.o 

CC_DEPS += \
./src/applications/bulk-send/bulk-send-application.d 


# Each subdirectory must supply rules for building sources it contributes
src/applications/bulk-send/%.o: ../src/applications/bulk-send/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


