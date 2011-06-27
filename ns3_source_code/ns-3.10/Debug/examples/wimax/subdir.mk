################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../examples/wimax/wimax-ipv4.cc \
../examples/wimax/wimax-multicast.cc \
../examples/wimax/wimax-simple.cc 

OBJS += \
./examples/wimax/wimax-ipv4.o \
./examples/wimax/wimax-multicast.o \
./examples/wimax/wimax-simple.o 

CC_DEPS += \
./examples/wimax/wimax-ipv4.d \
./examples/wimax/wimax-multicast.d \
./examples/wimax/wimax-simple.d 


# Each subdirectory must supply rules for building sources it contributes
examples/wimax/%.o: ../examples/wimax/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


