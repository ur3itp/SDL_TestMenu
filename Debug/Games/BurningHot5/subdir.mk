################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Games/BurningHot5/mgame2.cpp 

OBJS += \
./Games/BurningHot5/mgame2.o 

CPP_DEPS += \
./Games/BurningHot5/mgame2.d 


# Each subdirectory must supply rules for building sources it contributes
Games/BurningHot5/%.o: ../Games/BurningHot5/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


