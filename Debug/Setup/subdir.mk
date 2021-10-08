################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Setup/dosmode.cpp \
../Setup/rawmake.cpp 

OBJS += \
./Setup/dosmode.o \
./Setup/rawmake.o 

CPP_DEPS += \
./Setup/dosmode.d \
./Setup/rawmake.d 


# Each subdirectory must supply rules for building sources it contributes
Setup/%.o: ../Setup/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


