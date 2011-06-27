################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../examples/spectrum/adhoc-aloha-ideal-phy-with-microwave-oven.cc \
../examples/spectrum/adhoc-aloha-ideal-phy.cc 

OBJS += \
./examples/spectrum/adhoc-aloha-ideal-phy-with-microwave-oven.o \
./examples/spectrum/adhoc-aloha-ideal-phy.o 

CC_DEPS += \
./examples/spectrum/adhoc-aloha-ideal-phy-with-microwave-oven.d \
./examples/spectrum/adhoc-aloha-ideal-phy.d 


# Each subdirectory must supply rules for building sources it contributes
examples/spectrum/%.o: ../examples/spectrum/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


