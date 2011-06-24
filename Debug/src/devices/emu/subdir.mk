################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/devices/emu/emu-encode-decode.cc \
../src/devices/emu/emu-net-device.cc \
../src/devices/emu/emu-sock-creator.cc 

OBJS += \
./src/devices/emu/emu-encode-decode.o \
./src/devices/emu/emu-net-device.o \
./src/devices/emu/emu-sock-creator.o 

CC_DEPS += \
./src/devices/emu/emu-encode-decode.d \
./src/devices/emu/emu-net-device.d \
./src/devices/emu/emu-sock-creator.d 


# Each subdirectory must supply rules for building sources it contributes
src/devices/emu/%.o: ../src/devices/emu/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


