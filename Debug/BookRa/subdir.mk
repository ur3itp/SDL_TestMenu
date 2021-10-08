################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../BookRa/res_ra.cpp 

OBJS += \
./BookRa/res_ra.o 

CPP_DEPS += \
./BookRa/res_ra.d 


# Each subdirectory must supply rules for building sources it contributes
BookRa/%.o: ../BookRa/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


