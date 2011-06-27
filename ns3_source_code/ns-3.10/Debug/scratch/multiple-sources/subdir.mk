################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../scratch/multiple-sources/simple-main.cc \
../scratch/multiple-sources/simple-simulation.cc 

OBJS += \
./scratch/multiple-sources/simple-main.o \
./scratch/multiple-sources/simple-simulation.o 

CC_DEPS += \
./scratch/multiple-sources/simple-main.d \
./scratch/multiple-sources/simple-simulation.d 


# Each subdirectory must supply rules for building sources it contributes
scratch/multiple-sources/%.o: ../scratch/multiple-sources/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


