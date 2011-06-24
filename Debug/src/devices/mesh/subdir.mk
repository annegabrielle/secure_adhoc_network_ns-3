################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/devices/mesh/mesh-information-element-vector.cc \
../src/devices/mesh/mesh-l2-routing-protocol.cc \
../src/devices/mesh/mesh-point-device.cc \
../src/devices/mesh/mesh-wifi-beacon.cc \
../src/devices/mesh/mesh-wifi-interface-mac.cc 

OBJS += \
./src/devices/mesh/mesh-information-element-vector.o \
./src/devices/mesh/mesh-l2-routing-protocol.o \
./src/devices/mesh/mesh-point-device.o \
./src/devices/mesh/mesh-wifi-beacon.o \
./src/devices/mesh/mesh-wifi-interface-mac.o 

CC_DEPS += \
./src/devices/mesh/mesh-information-element-vector.d \
./src/devices/mesh/mesh-l2-routing-protocol.d \
./src/devices/mesh/mesh-point-device.d \
./src/devices/mesh/mesh-wifi-beacon.d \
./src/devices/mesh/mesh-wifi-interface-mac.d 


# Each subdirectory must supply rules for building sources it contributes
src/devices/mesh/%.o: ../src/devices/mesh/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


