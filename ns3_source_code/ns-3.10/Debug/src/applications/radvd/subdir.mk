################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/applications/radvd/radvd-interface.cc \
../src/applications/radvd/radvd-prefix.cc \
../src/applications/radvd/radvd.cc 

OBJS += \
./src/applications/radvd/radvd-interface.o \
./src/applications/radvd/radvd-prefix.o \
./src/applications/radvd/radvd.o 

CC_DEPS += \
./src/applications/radvd/radvd-interface.d \
./src/applications/radvd/radvd-prefix.d \
./src/applications/radvd/radvd.d 


# Each subdirectory must supply rules for building sources it contributes
src/applications/radvd/%.o: ../src/applications/radvd/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


