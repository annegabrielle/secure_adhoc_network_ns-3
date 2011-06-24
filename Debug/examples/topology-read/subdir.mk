################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../examples/topology-read/topology-example-sim.cc 

OBJS += \
./examples/topology-read/topology-example-sim.o 

CC_DEPS += \
./examples/topology-read/topology-example-sim.d 


# Each subdirectory must supply rules for building sources it contributes
examples/topology-read/%.o: ../examples/topology-read/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


