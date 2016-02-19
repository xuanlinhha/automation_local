################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/serial/SChecksum.cpp \
../src/serial/SListener.cpp \
../src/serial/SNotification.cpp \
../src/serial/SRequest.cpp \
../src/serial/SRequestHandler.cpp \
../src/serial/SResponse.cpp \
../src/serial/SerialPort.cpp \
../src/serial/SerialReporter.cpp 

OBJS += \
./src/serial/SChecksum.o \
./src/serial/SListener.o \
./src/serial/SNotification.o \
./src/serial/SRequest.o \
./src/serial/SRequestHandler.o \
./src/serial/SResponse.o \
./src/serial/SerialPort.o \
./src/serial/SerialReporter.o 

CPP_DEPS += \
./src/serial/SChecksum.d \
./src/serial/SListener.d \
./src/serial/SNotification.d \
./src/serial/SRequest.d \
./src/serial/SRequestHandler.d \
./src/serial/SResponse.d \
./src/serial/SerialPort.d \
./src/serial/SerialReporter.d 


# Each subdirectory must supply rules for building sources it contributes
src/serial/%.o: ../src/serial/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__cplusplus=201103L -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


