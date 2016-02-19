################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/internet/IConnection.cpp \
../src/internet/IListener.cpp \
../src/internet/IRequest.cpp \
../src/internet/IRequestHandler.cpp \
../src/internet/IRequestParser.cpp \
../src/internet/IResponse.cpp 

OBJS += \
./src/internet/IConnection.o \
./src/internet/IListener.o \
./src/internet/IRequest.o \
./src/internet/IRequestHandler.o \
./src/internet/IRequestParser.o \
./src/internet/IResponse.o 

CPP_DEPS += \
./src/internet/IConnection.d \
./src/internet/IListener.d \
./src/internet/IRequest.d \
./src/internet/IRequestHandler.d \
./src/internet/IRequestParser.d \
./src/internet/IResponse.d 


# Each subdirectory must supply rules for building sources it contributes
src/internet/%.o: ../src/internet/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__cplusplus=201103L -O3 -Wall -c -fmessage-length=0 -std=c++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


