################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../examples/matrix-topology/matrix-topology.cc 

OBJS += \
./examples/matrix-topology/matrix-topology.o 

CC_DEPS += \
./examples/matrix-topology/matrix-topology.d 


# Each subdirectory must supply rules for building sources it contributes
examples/matrix-topology/%.o: ../examples/matrix-topology/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


