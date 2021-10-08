################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Tool/media.cpp \
../Tool/rtext.cpp 

OBJS += \
./Tool/media.o \
./Tool/rtext.o 

CPP_DEPS += \
./Tool/media.d \
./Tool/rtext.d 


# Each subdirectory must supply rules for building sources it contributes
Tool/%.o: ../Tool/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


