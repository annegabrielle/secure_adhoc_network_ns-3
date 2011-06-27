################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/applications/udp-echo/udp-echo-client.cc \
../src/applications/udp-echo/udp-echo-server.cc 

OBJS += \
./src/applications/udp-echo/udp-echo-client.o \
./src/applications/udp-echo/udp-echo-server.o 

CC_DEPS += \
./src/applications/udp-echo/udp-echo-client.d \
./src/applications/udp-echo/udp-echo-server.d 


# Each subdirectory must supply rules for building sources it contributes
src/applications/udp-echo/%.o: ../src/applications/udp-echo/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


