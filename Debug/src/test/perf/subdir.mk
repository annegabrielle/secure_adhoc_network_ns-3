################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/test/perf/perf-io.cc 

OBJS += \
./src/test/perf/perf-io.o 

CC_DEPS += \
./src/test/perf/perf-io.d 


# Each subdirectory must supply rules for building sources it contributes
src/test/perf/%.o: ../src/test/perf/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


