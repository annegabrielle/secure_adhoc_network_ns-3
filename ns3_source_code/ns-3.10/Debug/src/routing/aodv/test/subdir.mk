################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/routing/aodv/test/aodv-regression.cc \
../src/routing/aodv/test/bug-772.cc \
../src/routing/aodv/test/loopback.cc 

OBJS += \
./src/routing/aodv/test/aodv-regression.o \
./src/routing/aodv/test/bug-772.o \
./src/routing/aodv/test/loopback.o 

CC_DEPS += \
./src/routing/aodv/test/aodv-regression.d \
./src/routing/aodv/test/bug-772.d \
./src/routing/aodv/test/loopback.d 


# Each subdirectory must supply rules for building sources it contributes
src/routing/aodv/test/%.o: ../src/routing/aodv/test/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


