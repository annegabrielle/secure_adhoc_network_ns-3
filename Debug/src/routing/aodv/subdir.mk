################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/routing/aodv/aodv-dpd.cc \
../src/routing/aodv/aodv-id-cache.cc \
../src/routing/aodv/aodv-neighbor.cc \
../src/routing/aodv/aodv-packet.cc \
../src/routing/aodv/aodv-routing-protocol.cc \
../src/routing/aodv/aodv-rqueue.cc \
../src/routing/aodv/aodv-rtable.cc \
../src/routing/aodv/aodv-test-suite.cc 

OBJS += \
./src/routing/aodv/aodv-dpd.o \
./src/routing/aodv/aodv-id-cache.o \
./src/routing/aodv/aodv-neighbor.o \
./src/routing/aodv/aodv-packet.o \
./src/routing/aodv/aodv-routing-protocol.o \
./src/routing/aodv/aodv-rqueue.o \
./src/routing/aodv/aodv-rtable.o \
./src/routing/aodv/aodv-test-suite.o 

CC_DEPS += \
./src/routing/aodv/aodv-dpd.d \
./src/routing/aodv/aodv-id-cache.d \
./src/routing/aodv/aodv-neighbor.d \
./src/routing/aodv/aodv-packet.d \
./src/routing/aodv/aodv-routing-protocol.d \
./src/routing/aodv/aodv-rqueue.d \
./src/routing/aodv/aodv-rtable.d \
./src/routing/aodv/aodv-test-suite.d 


# Each subdirectory must supply rules for building sources it contributes
src/routing/aodv/%.o: ../src/routing/aodv/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


