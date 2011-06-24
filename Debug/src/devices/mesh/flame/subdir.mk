################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/devices/mesh/flame/flame-header.cc \
../src/devices/mesh/flame/flame-protocol-mac.cc \
../src/devices/mesh/flame/flame-protocol.cc \
../src/devices/mesh/flame/flame-rtable.cc \
../src/devices/mesh/flame/flame-test-suite.cc 

OBJS += \
./src/devices/mesh/flame/flame-header.o \
./src/devices/mesh/flame/flame-protocol-mac.o \
./src/devices/mesh/flame/flame-protocol.o \
./src/devices/mesh/flame/flame-rtable.o \
./src/devices/mesh/flame/flame-test-suite.o 

CC_DEPS += \
./src/devices/mesh/flame/flame-header.d \
./src/devices/mesh/flame/flame-protocol-mac.d \
./src/devices/mesh/flame/flame-protocol.d \
./src/devices/mesh/flame/flame-rtable.d \
./src/devices/mesh/flame/flame-test-suite.d 


# Each subdirectory must supply rules for building sources it contributes
src/devices/mesh/flame/%.o: ../src/devices/mesh/flame/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


