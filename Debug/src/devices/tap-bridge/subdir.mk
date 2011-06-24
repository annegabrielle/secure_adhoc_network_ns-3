################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/devices/tap-bridge/tap-bridge.cc \
../src/devices/tap-bridge/tap-creator.cc \
../src/devices/tap-bridge/tap-encode-decode.cc 

OBJS += \
./src/devices/tap-bridge/tap-bridge.o \
./src/devices/tap-bridge/tap-creator.o \
./src/devices/tap-bridge/tap-encode-decode.o 

CC_DEPS += \
./src/devices/tap-bridge/tap-bridge.d \
./src/devices/tap-bridge/tap-creator.d \
./src/devices/tap-bridge/tap-encode-decode.d 


# Each subdirectory must supply rules for building sources it contributes
src/devices/tap-bridge/%.o: ../src/devices/tap-bridge/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


