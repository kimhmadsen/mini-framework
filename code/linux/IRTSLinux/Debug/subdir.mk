################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../EdrGenerator.cpp \
../LCDView.cpp \
../Patient.cpp \
../PatientDb.cpp \
../PatientHandler.cpp \
../PatientSignalIterator.cpp \
../RemoteClient.cpp \
../Subject.cpp \
../main.cpp 

CPP_DEPS += \
./EdrGenerator.d \
./LCDView.d \
./Patient.d \
./PatientDb.d \
./PatientHandler.d \
./PatientSignalIterator.d \
./RemoteClient.d \
./Subject.d \
./main.d 

OBJS += \
./EdrGenerator.o \
./LCDView.o \
./Patient.o \
./PatientDb.o \
./PatientHandler.o \
./PatientSignalIterator.o \
./RemoteClient.o \
./Subject.o \
./main.o 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/maria/tekniskIT/drts/svn/mini-framework/code/linux/minifw" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


