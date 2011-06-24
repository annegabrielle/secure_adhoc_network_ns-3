################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/contrib/stats/data-calculator.cc \
../src/contrib/stats/data-collector.cc \
../src/contrib/stats/data-output-interface.cc \
../src/contrib/stats/omnet-data-output.cc \
../src/contrib/stats/packet-data-calculators.cc \
../src/contrib/stats/sqlite-data-output.cc \
../src/contrib/stats/time-data-calculators.cc 

OBJS += \
./src/contrib/stats/data-calculator.o \
./src/contrib/stats/data-collector.o \
./src/contrib/stats/data-output-interface.o \
./src/contrib/stats/omnet-data-output.o \
./src/contrib/stats/packet-data-calculators.o \
./src/contrib/stats/sqlite-data-output.o \
./src/contrib/stats/time-data-calculators.o 

CC_DEPS += \
./src/contrib/stats/data-calculator.d \
./src/contrib/stats/data-collector.d \
./src/contrib/stats/data-output-interface.d \
./src/contrib/stats/omnet-data-output.d \
./src/contrib/stats/packet-data-calculators.d \
./src/contrib/stats/sqlite-data-output.d \
./src/contrib/stats/time-data-calculators.d 


# Each subdirectory must supply rules for building sources it contributes
src/contrib/stats/%.o: ../src/contrib/stats/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


