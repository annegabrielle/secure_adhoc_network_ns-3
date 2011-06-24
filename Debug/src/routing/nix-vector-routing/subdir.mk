################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/routing/nix-vector-routing/ipv4-nix-vector-routing.cc 

OBJS += \
./src/routing/nix-vector-routing/ipv4-nix-vector-routing.o 

CC_DEPS += \
./src/routing/nix-vector-routing/ipv4-nix-vector-routing.d 


# Each subdirectory must supply rules for building sources it contributes
src/routing/nix-vector-routing/%.o: ../src/routing/nix-vector-routing/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


