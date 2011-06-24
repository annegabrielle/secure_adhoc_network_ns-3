################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../examples/tap/tap-csma-virtual-machine.cc \
../examples/tap/tap-csma.cc \
../examples/tap/tap-wifi-dumbbell.cc \
../examples/tap/tap-wifi-virtual-machine.cc 

OBJS += \
./examples/tap/tap-csma-virtual-machine.o \
./examples/tap/tap-csma.o \
./examples/tap/tap-wifi-dumbbell.o \
./examples/tap/tap-wifi-virtual-machine.o 

CC_DEPS += \
./examples/tap/tap-csma-virtual-machine.d \
./examples/tap/tap-csma.d \
./examples/tap/tap-wifi-dumbbell.d \
./examples/tap/tap-wifi-virtual-machine.d 


# Each subdirectory must supply rules for building sources it contributes
examples/tap/%.o: ../examples/tap/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


