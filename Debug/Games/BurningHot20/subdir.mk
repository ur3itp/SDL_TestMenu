################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Games/BurningHot20/mgame1.cpp 

OBJS += \
./Games/BurningHot20/mgame1.o 

CPP_DEPS += \
./Games/BurningHot20/mgame1.d 


# Each subdirectory must supply rules for building sources it contributes
Games/BurningHot20/%.o: ../Games/BurningHot20/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


