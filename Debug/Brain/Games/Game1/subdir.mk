################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Brain/Games/Game1/burning20.cpp 

OBJS += \
./Brain/Games/Game1/burning20.o 

CPP_DEPS += \
./Brain/Games/Game1/burning20.d 


# Each subdirectory must supply rules for building sources it contributes
Brain/Games/Game1/%.o: ../Brain/Games/Game1/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


