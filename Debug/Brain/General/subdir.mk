################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Brain/General/queue.cpp \
../Brain/General/swap.cpp \
../Brain/General/swap_vars.cpp \
../Brain/General/utility.cpp 

OBJS += \
./Brain/General/queue.o \
./Brain/General/swap.o \
./Brain/General/swap_vars.o \
./Brain/General/utility.o 

CPP_DEPS += \
./Brain/General/queue.d \
./Brain/General/swap.d \
./Brain/General/swap_vars.d \
./Brain/General/utility.d 


# Each subdirectory must supply rules for building sources it contributes
Brain/General/%.o: ../Brain/General/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


