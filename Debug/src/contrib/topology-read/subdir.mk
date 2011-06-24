################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/contrib/topology-read/inet-topology-reader.cc \
../src/contrib/topology-read/orbis-topology-reader.cc \
../src/contrib/topology-read/rocketfuel-topology-reader.cc \
../src/contrib/topology-read/topology-reader.cc 

OBJS += \
./src/contrib/topology-read/inet-topology-reader.o \
./src/contrib/topology-read/orbis-topology-reader.o \
./src/contrib/topology-read/rocketfuel-topology-reader.o \
./src/contrib/topology-read/topology-reader.o 

CC_DEPS += \
./src/contrib/topology-read/inet-topology-reader.d \
./src/contrib/topology-read/orbis-topology-reader.d \
./src/contrib/topology-read/rocketfuel-topology-reader.d \
./src/contrib/topology-read/topology-reader.d 


# Each subdirectory must supply rules for building sources it contributes
src/contrib/topology-read/%.o: ../src/contrib/topology-read/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


