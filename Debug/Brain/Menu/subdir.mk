################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Brain/Menu/s_menu.cpp 

OBJS += \
./Brain/Menu/s_menu.o 

CPP_DEPS += \
./Brain/Menu/s_menu.d 


# Each subdirectory must supply rules for building sources it contributes
Brain/Menu/%.o: ../Brain/Menu/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


