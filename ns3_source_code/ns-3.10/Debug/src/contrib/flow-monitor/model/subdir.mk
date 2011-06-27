################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/contrib/flow-monitor/model/flow-classifier.cc \
../src/contrib/flow-monitor/model/flow-monitor.cc \
../src/contrib/flow-monitor/model/flow-probe.cc \
../src/contrib/flow-monitor/model/histogram.cc \
../src/contrib/flow-monitor/model/ipv4-flow-classifier.cc \
../src/contrib/flow-monitor/model/ipv4-flow-probe.cc 

OBJS += \
./src/contrib/flow-monitor/model/flow-classifier.o \
./src/contrib/flow-monitor/model/flow-monitor.o \
./src/contrib/flow-monitor/model/flow-probe.o \
./src/contrib/flow-monitor/model/histogram.o \
./src/contrib/flow-monitor/model/ipv4-flow-classifier.o \
./src/contrib/flow-monitor/model/ipv4-flow-probe.o 

CC_DEPS += \
./src/contrib/flow-monitor/model/flow-classifier.d \
./src/contrib/flow-monitor/model/flow-monitor.d \
./src/contrib/flow-monitor/model/flow-probe.d \
./src/contrib/flow-monitor/model/histogram.d \
./src/contrib/flow-monitor/model/ipv4-flow-classifier.d \
./src/contrib/flow-monitor/model/ipv4-flow-probe.d 


# Each subdirectory must supply rules for building sources it contributes
src/contrib/flow-monitor/model/%.o: ../src/contrib/flow-monitor/model/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


