################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../examples/mpi/nms-p2p-nix-distributed.cc \
../examples/mpi/simple-distributed.cc \
../examples/mpi/third-distributed.cc 

OBJS += \
./examples/mpi/nms-p2p-nix-distributed.o \
./examples/mpi/simple-distributed.o \
./examples/mpi/third-distributed.o 

CC_DEPS += \
./examples/mpi/nms-p2p-nix-distributed.d \
./examples/mpi/simple-distributed.d \
./examples/mpi/third-distributed.d 


# Each subdirectory must supply rules for building sources it contributes
examples/mpi/%.o: ../examples/mpi/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


