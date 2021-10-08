################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Brain/sys_global.cpp \
../Brain/sys_main.cpp 

OBJS += \
./Brain/sys_global.o \
./Brain/sys_main.o 

CPP_DEPS += \
./Brain/sys_global.d \
./Brain/sys_main.d 


# Each subdirectory must supply rules for building sources it contributes
Brain/%.o: ../Brain/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


