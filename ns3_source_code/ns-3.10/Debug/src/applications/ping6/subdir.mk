################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/applications/ping6/ping6.cc 

OBJS += \
./src/applications/ping6/ping6.o 

CC_DEPS += \
./src/applications/ping6/ping6.d 


# Each subdirectory must supply rules for building sources it contributes
src/applications/ping6/%.o: ../src/applications/ping6/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


