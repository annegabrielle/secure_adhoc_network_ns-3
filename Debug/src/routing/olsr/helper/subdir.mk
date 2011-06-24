################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/routing/olsr/helper/olsr-helper.cc 

OBJS += \
./src/routing/olsr/helper/olsr-helper.o 

CC_DEPS += \
./src/routing/olsr/helper/olsr-helper.d 


# Each subdirectory must supply rules for building sources it contributes
src/routing/olsr/helper/%.o: ../src/routing/olsr/helper/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


