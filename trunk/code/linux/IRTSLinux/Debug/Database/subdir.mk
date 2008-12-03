################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Database/DbAnnotations.cpp \
../Database/DbPatient.cpp \
../Database/DbSignals.cpp 

CPP_DEPS += \
./Database/DbAnnotations.d \
./Database/DbPatient.d \
./Database/DbSignals.d 

OBJS += \
./Database/DbAnnotations.o \
./Database/DbPatient.o \
./Database/DbSignals.o 


# Each subdirectory must supply rules for building sources it contributes
Database/%.o: ../Database/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


