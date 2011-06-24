################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/routing/dsdv/examples/dsdv-manet.cc 

OBJS += \
./src/routing/dsdv/examples/dsdv-manet.o 

CC_DEPS += \
./src/routing/dsdv/examples/dsdv-manet.d 


# Each subdirectory must supply rules for building sources it contributes
src/routing/dsdv/examples/%.o: ../src/routing/dsdv/examples/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


