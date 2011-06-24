################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../examples/csma/csma-broadcast.cc \
../examples/csma/csma-multicast.cc \
../examples/csma/csma-one-subnet.cc \
../examples/csma/csma-packet-socket.cc \
../examples/csma/csma-ping.cc \
../examples/csma/csma-raw-ip-socket.cc \
../examples/csma/csma-star.cc 

OBJS += \
./examples/csma/csma-broadcast.o \
./examples/csma/csma-multicast.o \
./examples/csma/csma-one-subnet.o \
./examples/csma/csma-packet-socket.o \
./examples/csma/csma-ping.o \
./examples/csma/csma-raw-ip-socket.o \
./examples/csma/csma-star.o 

CC_DEPS += \
./examples/csma/csma-broadcast.d \
./examples/csma/csma-multicast.d \
./examples/csma/csma-one-subnet.d \
./examples/csma/csma-packet-socket.d \
./examples/csma/csma-ping.d \
./examples/csma/csma-raw-ip-socket.d \
./examples/csma/csma-star.d 


# Each subdirectory must supply rules for building sources it contributes
examples/csma/%.o: ../examples/csma/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


