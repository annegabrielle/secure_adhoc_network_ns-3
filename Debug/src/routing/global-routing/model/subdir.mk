################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/routing/global-routing/model/candidate-queue.cc \
../src/routing/global-routing/model/global-route-manager-impl.cc \
../src/routing/global-routing/model/global-route-manager.cc \
../src/routing/global-routing/model/global-router-interface.cc \
../src/routing/global-routing/model/ipv4-global-routing.cc 

OBJS += \
./src/routing/global-routing/model/candidate-queue.o \
./src/routing/global-routing/model/global-route-manager-impl.o \
./src/routing/global-routing/model/global-route-manager.o \
./src/routing/global-routing/model/global-router-interface.o \
./src/routing/global-routing/model/ipv4-global-routing.o 

CC_DEPS += \
./src/routing/global-routing/model/candidate-queue.d \
./src/routing/global-routing/model/global-route-manager-impl.d \
./src/routing/global-routing/model/global-route-manager.d \
./src/routing/global-routing/model/global-router-interface.d \
./src/routing/global-routing/model/ipv4-global-routing.d 


# Each subdirectory must supply rules for building sources it contributes
src/routing/global-routing/model/%.o: ../src/routing/global-routing/model/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


