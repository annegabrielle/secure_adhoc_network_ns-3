################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/test/nsctcp/nsctcp-loss-test-suite.cc 

OBJS += \
./src/test/nsctcp/nsctcp-loss-test-suite.o 

CC_DEPS += \
./src/test/nsctcp/nsctcp-loss-test-suite.d 


# Each subdirectory must supply rules for building sources it contributes
src/test/nsctcp/%.o: ../src/test/nsctcp/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


