################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/routing/dsdv/model/dsdv-packet-queue.cc \
../src/routing/dsdv/model/dsdv-packet.cc \
../src/routing/dsdv/model/dsdv-routing-protocol.cc \
../src/routing/dsdv/model/dsdv-rtable.cc 

OBJS += \
./src/routing/dsdv/model/dsdv-packet-queue.o \
./src/routing/dsdv/model/dsdv-packet.o \
./src/routing/dsdv/model/dsdv-routing-protocol.o \
./src/routing/dsdv/model/dsdv-rtable.o 

CC_DEPS += \
./src/routing/dsdv/model/dsdv-packet-queue.d \
./src/routing/dsdv/model/dsdv-packet.d \
./src/routing/dsdv/model/dsdv-routing-protocol.d \
./src/routing/dsdv/model/dsdv-rtable.d 


# Each subdirectory must supply rules for building sources it contributes
src/routing/dsdv/model/%.o: ../src/routing/dsdv/model/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


