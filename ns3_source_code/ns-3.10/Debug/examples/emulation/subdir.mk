################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../examples/emulation/emu-ping.cc \
../examples/emulation/emu-udp-echo.cc 

OBJS += \
./examples/emulation/emu-ping.o \
./examples/emulation/emu-udp-echo.o 

CC_DEPS += \
./examples/emulation/emu-ping.d \
./examples/emulation/emu-udp-echo.d 


# Each subdirectory must supply rules for building sources it contributes
examples/emulation/%.o: ../examples/emulation/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


