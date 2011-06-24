################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/simulator/cairo-wideint.c 

CC_SRCS += \
../src/simulator/calendar-scheduler.cc \
../src/simulator/default-simulator-impl.cc \
../src/simulator/event-id.cc \
../src/simulator/event-impl.cc \
../src/simulator/heap-scheduler.cc \
../src/simulator/high-precision-128.cc \
../src/simulator/high-precision-cairo.cc \
../src/simulator/high-precision.cc \
../src/simulator/list-scheduler.cc \
../src/simulator/make-event.cc \
../src/simulator/map-scheduler.cc \
../src/simulator/ns2-calendar-scheduler.cc \
../src/simulator/realtime-simulator-impl.cc \
../src/simulator/scheduler.cc \
../src/simulator/simulator-impl.cc \
../src/simulator/simulator.cc \
../src/simulator/synchronizer.cc \
../src/simulator/time-base.cc \
../src/simulator/time.cc \
../src/simulator/timer.cc \
../src/simulator/wall-clock-synchronizer.cc \
../src/simulator/watchdog.cc 

OBJS += \
./src/simulator/cairo-wideint.o \
./src/simulator/calendar-scheduler.o \
./src/simulator/default-simulator-impl.o \
./src/simulator/event-id.o \
./src/simulator/event-impl.o \
./src/simulator/heap-scheduler.o \
./src/simulator/high-precision-128.o \
./src/simulator/high-precision-cairo.o \
./src/simulator/high-precision.o \
./src/simulator/list-scheduler.o \
./src/simulator/make-event.o \
./src/simulator/map-scheduler.o \
./src/simulator/ns2-calendar-scheduler.o \
./src/simulator/realtime-simulator-impl.o \
./src/simulator/scheduler.o \
./src/simulator/simulator-impl.o \
./src/simulator/simulator.o \
./src/simulator/synchronizer.o \
./src/simulator/time-base.o \
./src/simulator/time.o \
./src/simulator/timer.o \
./src/simulator/wall-clock-synchronizer.o \
./src/simulator/watchdog.o 

C_DEPS += \
./src/simulator/cairo-wideint.d 

CC_DEPS += \
./src/simulator/calendar-scheduler.d \
./src/simulator/default-simulator-impl.d \
./src/simulator/event-id.d \
./src/simulator/event-impl.d \
./src/simulator/heap-scheduler.d \
./src/simulator/high-precision-128.d \
./src/simulator/high-precision-cairo.d \
./src/simulator/high-precision.d \
./src/simulator/list-scheduler.d \
./src/simulator/make-event.d \
./src/simulator/map-scheduler.d \
./src/simulator/ns2-calendar-scheduler.d \
./src/simulator/realtime-simulator-impl.d \
./src/simulator/scheduler.d \
./src/simulator/simulator-impl.d \
./src/simulator/simulator.d \
./src/simulator/synchronizer.d \
./src/simulator/time-base.d \
./src/simulator/time.d \
./src/simulator/timer.d \
./src/simulator/wall-clock-synchronizer.d \
./src/simulator/watchdog.d 


# Each subdirectory must supply rules for building sources it contributes
src/simulator/%.o: ../src/simulator/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/simulator/%.o: ../src/simulator/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


