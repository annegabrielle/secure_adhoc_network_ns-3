################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/routing/olsr/test/bug780-test.cc \
../src/routing/olsr/test/hello-regression-test.cc \
../src/routing/olsr/test/regression-test-suite.cc \
../src/routing/olsr/test/tc-regression-test.cc 

OBJS += \
./src/routing/olsr/test/bug780-test.o \
./src/routing/olsr/test/hello-regression-test.o \
./src/routing/olsr/test/regression-test-suite.o \
./src/routing/olsr/test/tc-regression-test.o 

CC_DEPS += \
./src/routing/olsr/test/bug780-test.d \
./src/routing/olsr/test/hello-regression-test.d \
./src/routing/olsr/test/regression-test-suite.d \
./src/routing/olsr/test/tc-regression-test.d 


# Each subdirectory must supply rules for building sources it contributes
src/routing/olsr/test/%.o: ../src/routing/olsr/test/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


