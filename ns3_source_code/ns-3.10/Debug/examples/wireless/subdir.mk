################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../examples/wireless/mixed-wireless.cc \
../examples/wireless/multirate.cc \
../examples/wireless/ofdm-validation.cc \
../examples/wireless/simple-wifi-frame-aggregation.cc \
../examples/wireless/wifi-adhoc.cc \
../examples/wireless/wifi-ap.cc \
../examples/wireless/wifi-blockack.cc \
../examples/wireless/wifi-clear-channel-cmu.cc \
../examples/wireless/wifi-hidden-terminal.cc \
../examples/wireless/wifi-simple-adhoc-grid.cc \
../examples/wireless/wifi-simple-adhoc.cc \
../examples/wireless/wifi-simple-infra.cc \
../examples/wireless/wifi-simple-interference.cc \
../examples/wireless/wifi-wired-bridging.cc 

OBJS += \
./examples/wireless/mixed-wireless.o \
./examples/wireless/multirate.o \
./examples/wireless/ofdm-validation.o \
./examples/wireless/simple-wifi-frame-aggregation.o \
./examples/wireless/wifi-adhoc.o \
./examples/wireless/wifi-ap.o \
./examples/wireless/wifi-blockack.o \
./examples/wireless/wifi-clear-channel-cmu.o \
./examples/wireless/wifi-hidden-terminal.o \
./examples/wireless/wifi-simple-adhoc-grid.o \
./examples/wireless/wifi-simple-adhoc.o \
./examples/wireless/wifi-simple-infra.o \
./examples/wireless/wifi-simple-interference.o \
./examples/wireless/wifi-wired-bridging.o 

CC_DEPS += \
./examples/wireless/mixed-wireless.d \
./examples/wireless/multirate.d \
./examples/wireless/ofdm-validation.d \
./examples/wireless/simple-wifi-frame-aggregation.d \
./examples/wireless/wifi-adhoc.d \
./examples/wireless/wifi-ap.d \
./examples/wireless/wifi-blockack.d \
./examples/wireless/wifi-clear-channel-cmu.d \
./examples/wireless/wifi-hidden-terminal.d \
./examples/wireless/wifi-simple-adhoc-grid.d \
./examples/wireless/wifi-simple-adhoc.d \
./examples/wireless/wifi-simple-infra.d \
./examples/wireless/wifi-simple-interference.d \
./examples/wireless/wifi-wired-bridging.d 


# Each subdirectory must supply rules for building sources it contributes
examples/wireless/%.o: ../examples/wireless/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


