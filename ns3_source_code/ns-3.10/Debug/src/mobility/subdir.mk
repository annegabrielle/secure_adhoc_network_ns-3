################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/mobility/box.cc \
../src/mobility/constant-acceleration-mobility-model.cc \
../src/mobility/constant-position-mobility-model.cc \
../src/mobility/constant-velocity-helper.cc \
../src/mobility/constant-velocity-mobility-model.cc \
../src/mobility/gauss-markov-mobility-model.cc \
../src/mobility/hierarchical-mobility-model.cc \
../src/mobility/mobility-model.cc \
../src/mobility/position-allocator.cc \
../src/mobility/random-direction-2d-mobility-model.cc \
../src/mobility/random-walk-2d-mobility-model.cc \
../src/mobility/random-waypoint-mobility-model.cc \
../src/mobility/rectangle.cc \
../src/mobility/steady-state-random-waypoint-mobility-model.cc \
../src/mobility/waypoint-mobility-model.cc \
../src/mobility/waypoint.cc 

OBJS += \
./src/mobility/box.o \
./src/mobility/constant-acceleration-mobility-model.o \
./src/mobility/constant-position-mobility-model.o \
./src/mobility/constant-velocity-helper.o \
./src/mobility/constant-velocity-mobility-model.o \
./src/mobility/gauss-markov-mobility-model.o \
./src/mobility/hierarchical-mobility-model.o \
./src/mobility/mobility-model.o \
./src/mobility/position-allocator.o \
./src/mobility/random-direction-2d-mobility-model.o \
./src/mobility/random-walk-2d-mobility-model.o \
./src/mobility/random-waypoint-mobility-model.o \
./src/mobility/rectangle.o \
./src/mobility/steady-state-random-waypoint-mobility-model.o \
./src/mobility/waypoint-mobility-model.o \
./src/mobility/waypoint.o 

CC_DEPS += \
./src/mobility/box.d \
./src/mobility/constant-acceleration-mobility-model.d \
./src/mobility/constant-position-mobility-model.d \
./src/mobility/constant-velocity-helper.d \
./src/mobility/constant-velocity-mobility-model.d \
./src/mobility/gauss-markov-mobility-model.d \
./src/mobility/hierarchical-mobility-model.d \
./src/mobility/mobility-model.d \
./src/mobility/position-allocator.d \
./src/mobility/random-direction-2d-mobility-model.d \
./src/mobility/random-walk-2d-mobility-model.d \
./src/mobility/random-waypoint-mobility-model.d \
./src/mobility/rectangle.d \
./src/mobility/steady-state-random-waypoint-mobility-model.d \
./src/mobility/waypoint-mobility-model.d \
./src/mobility/waypoint.d 


# Each subdirectory must supply rules for building sources it contributes
src/mobility/%.o: ../src/mobility/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


