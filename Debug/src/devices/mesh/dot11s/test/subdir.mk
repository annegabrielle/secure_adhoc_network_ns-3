################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/devices/mesh/dot11s/test/dot11s-test-suite.cc \
../src/devices/mesh/dot11s/test/hwmp-proactive-regression.cc \
../src/devices/mesh/dot11s/test/hwmp-reactive-regression.cc \
../src/devices/mesh/dot11s/test/hwmp-simplest-regression.cc \
../src/devices/mesh/dot11s/test/hwmp-target-flags-regression.cc \
../src/devices/mesh/dot11s/test/pmp-regression.cc \
../src/devices/mesh/dot11s/test/regression.cc 

OBJS += \
./src/devices/mesh/dot11s/test/dot11s-test-suite.o \
./src/devices/mesh/dot11s/test/hwmp-proactive-regression.o \
./src/devices/mesh/dot11s/test/hwmp-reactive-regression.o \
./src/devices/mesh/dot11s/test/hwmp-simplest-regression.o \
./src/devices/mesh/dot11s/test/hwmp-target-flags-regression.o \
./src/devices/mesh/dot11s/test/pmp-regression.o \
./src/devices/mesh/dot11s/test/regression.o 

CC_DEPS += \
./src/devices/mesh/dot11s/test/dot11s-test-suite.d \
./src/devices/mesh/dot11s/test/hwmp-proactive-regression.d \
./src/devices/mesh/dot11s/test/hwmp-reactive-regression.d \
./src/devices/mesh/dot11s/test/hwmp-simplest-regression.d \
./src/devices/mesh/dot11s/test/hwmp-target-flags-regression.d \
./src/devices/mesh/dot11s/test/pmp-regression.d \
./src/devices/mesh/dot11s/test/regression.d 


# Each subdirectory must supply rules for building sources it contributes
src/devices/mesh/dot11s/test/%.o: ../src/devices/mesh/dot11s/test/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


