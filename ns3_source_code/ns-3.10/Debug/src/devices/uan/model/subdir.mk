################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/devices/uan/model/acoustic-modem-energy-model.cc \
../src/devices/uan/model/uan-address.cc \
../src/devices/uan/model/uan-channel.cc \
../src/devices/uan/model/uan-header-common.cc \
../src/devices/uan/model/uan-header-rc.cc \
../src/devices/uan/model/uan-mac-aloha.cc \
../src/devices/uan/model/uan-mac-cw.cc \
../src/devices/uan/model/uan-mac-rc-gw.cc \
../src/devices/uan/model/uan-mac-rc.cc \
../src/devices/uan/model/uan-net-device.cc \
../src/devices/uan/model/uan-noise-model-default.cc \
../src/devices/uan/model/uan-noise-model.cc \
../src/devices/uan/model/uan-phy-dual.cc \
../src/devices/uan/model/uan-phy-gen.cc \
../src/devices/uan/model/uan-phy.cc \
../src/devices/uan/model/uan-prop-model-ideal.cc \
../src/devices/uan/model/uan-prop-model-thorp.cc \
../src/devices/uan/model/uan-prop-model.cc \
../src/devices/uan/model/uan-transducer-hd.cc \
../src/devices/uan/model/uan-tx-mode.cc 

OBJS += \
./src/devices/uan/model/acoustic-modem-energy-model.o \
./src/devices/uan/model/uan-address.o \
./src/devices/uan/model/uan-channel.o \
./src/devices/uan/model/uan-header-common.o \
./src/devices/uan/model/uan-header-rc.o \
./src/devices/uan/model/uan-mac-aloha.o \
./src/devices/uan/model/uan-mac-cw.o \
./src/devices/uan/model/uan-mac-rc-gw.o \
./src/devices/uan/model/uan-mac-rc.o \
./src/devices/uan/model/uan-net-device.o \
./src/devices/uan/model/uan-noise-model-default.o \
./src/devices/uan/model/uan-noise-model.o \
./src/devices/uan/model/uan-phy-dual.o \
./src/devices/uan/model/uan-phy-gen.o \
./src/devices/uan/model/uan-phy.o \
./src/devices/uan/model/uan-prop-model-ideal.o \
./src/devices/uan/model/uan-prop-model-thorp.o \
./src/devices/uan/model/uan-prop-model.o \
./src/devices/uan/model/uan-transducer-hd.o \
./src/devices/uan/model/uan-tx-mode.o 

CC_DEPS += \
./src/devices/uan/model/acoustic-modem-energy-model.d \
./src/devices/uan/model/uan-address.d \
./src/devices/uan/model/uan-channel.d \
./src/devices/uan/model/uan-header-common.d \
./src/devices/uan/model/uan-header-rc.d \
./src/devices/uan/model/uan-mac-aloha.d \
./src/devices/uan/model/uan-mac-cw.d \
./src/devices/uan/model/uan-mac-rc-gw.d \
./src/devices/uan/model/uan-mac-rc.d \
./src/devices/uan/model/uan-net-device.d \
./src/devices/uan/model/uan-noise-model-default.d \
./src/devices/uan/model/uan-noise-model.d \
./src/devices/uan/model/uan-phy-dual.d \
./src/devices/uan/model/uan-phy-gen.d \
./src/devices/uan/model/uan-phy.d \
./src/devices/uan/model/uan-prop-model-ideal.d \
./src/devices/uan/model/uan-prop-model-thorp.d \
./src/devices/uan/model/uan-prop-model.d \
./src/devices/uan/model/uan-transducer-hd.d \
./src/devices/uan/model/uan-tx-mode.d 


# Each subdirectory must supply rules for building sources it contributes
src/devices/uan/model/%.o: ../src/devices/uan/model/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


