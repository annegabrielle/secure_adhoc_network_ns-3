################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/devices/mesh/flame/test/flame-regression.cc \
../src/devices/mesh/flame/test/regression.cc 

OBJS += \
./src/devices/mesh/flame/test/flame-regression.o \
./src/devices/mesh/flame/test/regression.o 

CC_DEPS += \
./src/devices/mesh/flame/test/flame-regression.d \
./src/devices/mesh/flame/test/regression.d 


# Each subdirectory must supply rules for building sources it contributes
src/devices/mesh/flame/test/%.o: ../src/devices/mesh/flame/test/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


