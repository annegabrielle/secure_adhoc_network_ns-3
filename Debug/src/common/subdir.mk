################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/common/buffer-test.cc \
../src/common/buffer.cc \
../src/common/byte-tag-list.cc \
../src/common/chunk.cc \
../src/common/cost231-propagation-loss-model.cc \
../src/common/data-rate.cc \
../src/common/error-model.cc \
../src/common/friis-spectrum-propagation-loss.cc \
../src/common/header.cc \
../src/common/jakes-propagation-loss-model.cc \
../src/common/nix-vector.cc \
../src/common/output-stream-wrapper.cc \
../src/common/packet-burst.cc \
../src/common/packet-metadata-test.cc \
../src/common/packet-metadata.cc \
../src/common/packet-tag-list.cc \
../src/common/packet.cc \
../src/common/pcap-file-test-suite.cc \
../src/common/pcap-file-wrapper.cc \
../src/common/pcap-file.cc \
../src/common/propagation-delay-model.cc \
../src/common/propagation-loss-model-test-suite.cc \
../src/common/propagation-loss-model.cc \
../src/common/sequence-number.cc \
../src/common/spectrum-converter.cc \
../src/common/spectrum-model.cc \
../src/common/spectrum-propagation-loss-model.cc \
../src/common/spectrum-type.cc \
../src/common/spectrum-value-test.cc \
../src/common/spectrum-value.cc \
../src/common/tag-buffer.cc \
../src/common/tag.cc \
../src/common/trailer.cc 

OBJS += \
./src/common/buffer-test.o \
./src/common/buffer.o \
./src/common/byte-tag-list.o \
./src/common/chunk.o \
./src/common/cost231-propagation-loss-model.o \
./src/common/data-rate.o \
./src/common/error-model.o \
./src/common/friis-spectrum-propagation-loss.o \
./src/common/header.o \
./src/common/jakes-propagation-loss-model.o \
./src/common/nix-vector.o \
./src/common/output-stream-wrapper.o \
./src/common/packet-burst.o \
./src/common/packet-metadata-test.o \
./src/common/packet-metadata.o \
./src/common/packet-tag-list.o \
./src/common/packet.o \
./src/common/pcap-file-test-suite.o \
./src/common/pcap-file-wrapper.o \
./src/common/pcap-file.o \
./src/common/propagation-delay-model.o \
./src/common/propagation-loss-model-test-suite.o \
./src/common/propagation-loss-model.o \
./src/common/sequence-number.o \
./src/common/spectrum-converter.o \
./src/common/spectrum-model.o \
./src/common/spectrum-propagation-loss-model.o \
./src/common/spectrum-type.o \
./src/common/spectrum-value-test.o \
./src/common/spectrum-value.o \
./src/common/tag-buffer.o \
./src/common/tag.o \
./src/common/trailer.o 

CC_DEPS += \
./src/common/buffer-test.d \
./src/common/buffer.d \
./src/common/byte-tag-list.d \
./src/common/chunk.d \
./src/common/cost231-propagation-loss-model.d \
./src/common/data-rate.d \
./src/common/error-model.d \
./src/common/friis-spectrum-propagation-loss.d \
./src/common/header.d \
./src/common/jakes-propagation-loss-model.d \
./src/common/nix-vector.d \
./src/common/output-stream-wrapper.d \
./src/common/packet-burst.d \
./src/common/packet-metadata-test.d \
./src/common/packet-metadata.d \
./src/common/packet-tag-list.d \
./src/common/packet.d \
./src/common/pcap-file-test-suite.d \
./src/common/pcap-file-wrapper.d \
./src/common/pcap-file.d \
./src/common/propagation-delay-model.d \
./src/common/propagation-loss-model-test-suite.d \
./src/common/propagation-loss-model.d \
./src/common/sequence-number.d \
./src/common/spectrum-converter.d \
./src/common/spectrum-model.d \
./src/common/spectrum-propagation-loss-model.d \
./src/common/spectrum-type.d \
./src/common/spectrum-value-test.d \
./src/common/spectrum-value.d \
./src/common/tag-buffer.d \
./src/common/tag.d \
./src/common/trailer.d 


# Each subdirectory must supply rules for building sources it contributes
src/common/%.o: ../src/common/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


