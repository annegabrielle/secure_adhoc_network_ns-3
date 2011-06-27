################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../examples/socket/socket-bound-static-routing.cc \
../examples/socket/socket-bound-tcp-static-routing.cc 

OBJS += \
./examples/socket/socket-bound-static-routing.o \
./examples/socket/socket-bound-tcp-static-routing.o 

CC_DEPS += \
./examples/socket/socket-bound-static-routing.d \
./examples/socket/socket-bound-tcp-static-routing.d 


# Each subdirectory must supply rules for building sources it contributes
examples/socket/%.o: ../examples/socket/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


