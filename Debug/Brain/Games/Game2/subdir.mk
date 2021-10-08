################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Brain/Games/Game2/burning5.cpp 

OBJS += \
./Brain/Games/Game2/burning5.o 

CPP_DEPS += \
./Brain/Games/Game2/burning5.d 


# Each subdirectory must supply rules for building sources it contributes
Brain/Games/Game2/%.o: ../Brain/Games/Game2/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


