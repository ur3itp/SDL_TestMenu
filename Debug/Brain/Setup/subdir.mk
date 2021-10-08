################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Brain/Setup/account.cpp \
../Brain/Setup/attendant.cpp \
../Brain/Setup/audit.cpp \
../Brain/Setup/diagnos.cpp \
../Brain/Setup/eventlog.cpp \
../Brain/Setup/gparam.cpp \
../Brain/Setup/history.cpp \
../Brain/Setup/initial.cpp \
../Brain/Setup/msetting.cpp \
../Brain/Setup/setup.cpp \
../Brain/Setup/startup.cpp \
../Brain/Setup/statistic.cpp 

OBJS += \
./Brain/Setup/account.o \
./Brain/Setup/attendant.o \
./Brain/Setup/audit.o \
./Brain/Setup/diagnos.o \
./Brain/Setup/eventlog.o \
./Brain/Setup/gparam.o \
./Brain/Setup/history.o \
./Brain/Setup/initial.o \
./Brain/Setup/msetting.o \
./Brain/Setup/setup.o \
./Brain/Setup/startup.o \
./Brain/Setup/statistic.o 

CPP_DEPS += \
./Brain/Setup/account.d \
./Brain/Setup/attendant.d \
./Brain/Setup/audit.d \
./Brain/Setup/diagnos.d \
./Brain/Setup/eventlog.d \
./Brain/Setup/gparam.d \
./Brain/Setup/history.d \
./Brain/Setup/initial.d \
./Brain/Setup/msetting.d \
./Brain/Setup/setup.d \
./Brain/Setup/startup.d \
./Brain/Setup/statistic.d 


# Each subdirectory must supply rules for building sources it contributes
Brain/Setup/%.o: ../Brain/Setup/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


