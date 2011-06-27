################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../examples/naming/object-names.cc 

OBJS += \
./examples/naming/object-names.o 

CC_DEPS += \
./examples/naming/object-names.d 


# Each subdirectory must supply rules for building sources it contributes
examples/naming/%.o: ../examples/naming/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


