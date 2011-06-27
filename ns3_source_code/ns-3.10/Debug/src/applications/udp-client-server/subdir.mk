################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/applications/udp-client-server/packet-loss-counter.cc \
../src/applications/udp-client-server/seq-ts-header.cc \
../src/applications/udp-client-server/udp-client-server-test.cc \
../src/applications/udp-client-server/udp-client.cc \
../src/applications/udp-client-server/udp-server.cc \
../src/applications/udp-client-server/udp-trace-client.cc 

OBJS += \
./src/applications/udp-client-server/packet-loss-counter.o \
./src/applications/udp-client-server/seq-ts-header.o \
./src/applications/udp-client-server/udp-client-server-test.o \
./src/applications/udp-client-server/udp-client.o \
./src/applications/udp-client-server/udp-server.o \
./src/applications/udp-client-server/udp-trace-client.o 

CC_DEPS += \
./src/applications/udp-client-server/packet-loss-counter.d \
./src/applications/udp-client-server/seq-ts-header.d \
./src/applications/udp-client-server/udp-client-server-test.d \
./src/applications/udp-client-server/udp-client.d \
./src/applications/udp-client-server/udp-server.d \
./src/applications/udp-client-server/udp-trace-client.d 


# Each subdirectory must supply rules for building sources it contributes
src/applications/udp-client-server/%.o: ../src/applications/udp-client-server/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


