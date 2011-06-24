################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/routing/olsr/examples/olsr-hna.cc \
../src/routing/olsr/examples/simple-point-to-point-olsr.cc 

OBJS += \
./src/routing/olsr/examples/olsr-hna.o \
./src/routing/olsr/examples/simple-point-to-point-olsr.o 

CC_DEPS += \
./src/routing/olsr/examples/olsr-hna.d \
./src/routing/olsr/examples/simple-point-to-point-olsr.d 


# Each subdirectory must supply rules for building sources it contributes
src/routing/olsr/examples/%.o: ../src/routing/olsr/examples/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


