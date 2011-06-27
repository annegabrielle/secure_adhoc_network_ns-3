################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/core/attribute-list.cc \
../src/core/attribute-test-suite.cc \
../src/core/attribute.cc \
../src/core/boolean.cc \
../src/core/breakpoint.cc \
../src/core/callback-test-suite.cc \
../src/core/callback.cc \
../src/core/command-line.cc \
../src/core/config.cc \
../src/core/double.cc \
../src/core/enum.cc \
../src/core/fatal-impl.cc \
../src/core/global-value.cc \
../src/core/integer.cc \
../src/core/log.cc \
../src/core/names-test-suite.cc \
../src/core/names.cc \
../src/core/object-base.cc \
../src/core/object-factory.cc \
../src/core/object-vector.cc \
../src/core/object.cc \
../src/core/pointer.cc \
../src/core/ptr-test-suite.cc \
../src/core/random-variable.cc \
../src/core/ref-count-base.cc \
../src/core/rng-stream.cc \
../src/core/rng-test-suite.cc \
../src/core/string.cc \
../src/core/test.cc \
../src/core/trace-source-accessor.cc \
../src/core/traced-callback-test-suite.cc \
../src/core/type-id.cc \
../src/core/type-name.cc \
../src/core/type-traits-test-suite.cc \
../src/core/uinteger.cc \
../src/core/unix-fd-reader.cc \
../src/core/unix-system-condition.cc \
../src/core/unix-system-mutex.cc \
../src/core/unix-system-thread.cc \
../src/core/unix-system-wall-clock-ms.cc \
../src/core/vector.cc \
../src/core/win32-system-wall-clock-ms.cc 

OBJS += \
./src/core/attribute-list.o \
./src/core/attribute-test-suite.o \
./src/core/attribute.o \
./src/core/boolean.o \
./src/core/breakpoint.o \
./src/core/callback-test-suite.o \
./src/core/callback.o \
./src/core/command-line.o \
./src/core/config.o \
./src/core/double.o \
./src/core/enum.o \
./src/core/fatal-impl.o \
./src/core/global-value.o \
./src/core/integer.o \
./src/core/log.o \
./src/core/names-test-suite.o \
./src/core/names.o \
./src/core/object-base.o \
./src/core/object-factory.o \
./src/core/object-vector.o \
./src/core/object.o \
./src/core/pointer.o \
./src/core/ptr-test-suite.o \
./src/core/random-variable.o \
./src/core/ref-count-base.o \
./src/core/rng-stream.o \
./src/core/rng-test-suite.o \
./src/core/string.o \
./src/core/test.o \
./src/core/trace-source-accessor.o \
./src/core/traced-callback-test-suite.o \
./src/core/type-id.o \
./src/core/type-name.o \
./src/core/type-traits-test-suite.o \
./src/core/uinteger.o \
./src/core/unix-fd-reader.o \
./src/core/unix-system-condition.o \
./src/core/unix-system-mutex.o \
./src/core/unix-system-thread.o \
./src/core/unix-system-wall-clock-ms.o \
./src/core/vector.o \
./src/core/win32-system-wall-clock-ms.o 

CC_DEPS += \
./src/core/attribute-list.d \
./src/core/attribute-test-suite.d \
./src/core/attribute.d \
./src/core/boolean.d \
./src/core/breakpoint.d \
./src/core/callback-test-suite.d \
./src/core/callback.d \
./src/core/command-line.d \
./src/core/config.d \
./src/core/double.d \
./src/core/enum.d \
./src/core/fatal-impl.d \
./src/core/global-value.d \
./src/core/integer.d \
./src/core/log.d \
./src/core/names-test-suite.d \
./src/core/names.d \
./src/core/object-base.d \
./src/core/object-factory.d \
./src/core/object-vector.d \
./src/core/object.d \
./src/core/pointer.d \
./src/core/ptr-test-suite.d \
./src/core/random-variable.d \
./src/core/ref-count-base.d \
./src/core/rng-stream.d \
./src/core/rng-test-suite.d \
./src/core/string.d \
./src/core/test.d \
./src/core/trace-source-accessor.d \
./src/core/traced-callback-test-suite.d \
./src/core/type-id.d \
./src/core/type-name.d \
./src/core/type-traits-test-suite.d \
./src/core/uinteger.d \
./src/core/unix-fd-reader.d \
./src/core/unix-system-condition.d \
./src/core/unix-system-mutex.d \
./src/core/unix-system-thread.d \
./src/core/unix-system-wall-clock-ms.d \
./src/core/vector.d \
./src/core/win32-system-wall-clock-ms.d 


# Each subdirectory must supply rules for building sources it contributes
src/core/%.o: ../src/core/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


