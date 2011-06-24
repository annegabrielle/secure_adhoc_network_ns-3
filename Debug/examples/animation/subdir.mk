################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../examples/animation/dumbbell-animation.cc \
../examples/animation/grid-animation.cc \
../examples/animation/star-animation.cc 

OBJS += \
./examples/animation/dumbbell-animation.o \
./examples/animation/grid-animation.o \
./examples/animation/star-animation.o 

CC_DEPS += \
./examples/animation/dumbbell-animation.d \
./examples/animation/grid-animation.d \
./examples/animation/star-animation.d 


# Each subdirectory must supply rules for building sources it contributes
examples/animation/%.o: ../examples/animation/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


