################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../examples/mesh/mesh.cc 

OBJS += \
./examples/mesh/mesh.o 

CC_DEPS += \
./examples/mesh/mesh.d 


# Each subdirectory must supply rules for building sources it contributes
examples/mesh/%.o: ../examples/mesh/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


