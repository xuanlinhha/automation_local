################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/management/Building.cpp \
../src/management/FileReader.cpp \
../src/management/Node.cpp \
../src/management/SResponseArray.cpp \
../src/management/TicketAgent.cpp 

OBJS += \
./src/management/Building.o \
./src/management/FileReader.o \
./src/management/Node.o \
./src/management/SResponseArray.o \
./src/management/TicketAgent.o 

CPP_DEPS += \
./src/management/Building.d \
./src/management/FileReader.d \
./src/management/Node.d \
./src/management/SResponseArray.d \
./src/management/TicketAgent.d 


# Each subdirectory must supply rules for building sources it contributes
src/management/%.o: ../src/management/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__cplusplus=201103L -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


