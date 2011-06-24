################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../examples/routing/aodv.cc \
../examples/routing/dynamic-global-routing.cc \
../examples/routing/global-injection-slash32.cc \
../examples/routing/global-routing-slash32.cc \
../examples/routing/mixed-global-routing.cc \
../examples/routing/nix-simple.cc \
../examples/routing/nms-p2p-nix.cc \
../examples/routing/simple-alternate-routing.cc \
../examples/routing/simple-global-routing.cc \
../examples/routing/simple-routing-ping6.cc \
../examples/routing/static-routing-slash32.cc 

OBJS += \
./examples/routing/aodv.o \
./examples/routing/dynamic-global-routing.o \
./examples/routing/global-injection-slash32.o \
./examples/routing/global-routing-slash32.o \
./examples/routing/mixed-global-routing.o \
./examples/routing/nix-simple.o \
./examples/routing/nms-p2p-nix.o \
./examples/routing/simple-alternate-routing.o \
./examples/routing/simple-global-routing.o \
./examples/routing/simple-routing-ping6.o \
./examples/routing/static-routing-slash32.o 

CC_DEPS += \
./examples/routing/aodv.d \
./examples/routing/dynamic-global-routing.d \
./examples/routing/global-injection-slash32.d \
./examples/routing/global-routing-slash32.d \
./examples/routing/mixed-global-routing.d \
./examples/routing/nix-simple.d \
./examples/routing/nms-p2p-nix.d \
./examples/routing/simple-alternate-routing.d \
./examples/routing/simple-global-routing.d \
./examples/routing/simple-routing-ping6.d \
./examples/routing/static-routing-slash32.d 


# Each subdirectory must supply rules for building sources it contributes
examples/routing/%.o: ../examples/routing/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


