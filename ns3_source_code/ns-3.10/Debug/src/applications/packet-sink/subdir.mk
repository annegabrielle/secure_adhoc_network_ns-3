################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/applications/packet-sink/packet-sink.cc 

OBJS += \
./src/applications/packet-sink/packet-sink.o 

CC_DEPS += \
./src/applications/packet-sink/packet-sink.d 


# Each subdirectory must supply rules for building sources it contributes
src/applications/packet-sink/%.o: ../src/applications/packet-sink/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


