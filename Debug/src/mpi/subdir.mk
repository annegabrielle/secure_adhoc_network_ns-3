################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/mpi/distributed-simulator-impl.cc \
../src/mpi/mpi-interface.cc 

OBJS += \
./src/mpi/distributed-simulator-impl.o \
./src/mpi/mpi-interface.o 

CC_DEPS += \
./src/mpi/distributed-simulator-impl.d \
./src/mpi/mpi-interface.d 


# Each subdirectory must supply rules for building sources it contributes
src/mpi/%.o: ../src/mpi/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


