################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
LD_SRCS += \
../src/lscript.ld 

C_SRCS += \
../src/guicom.c \
../src/main.c \
../src/miscellaneous.c \
../src/platform.c \
../src/poxi.c 

OBJS += \
./src/guicom.o \
./src/main.o \
./src/miscellaneous.o \
./src/platform.o \
./src/poxi.o 

C_DEPS += \
./src/guicom.d \
./src/main.d \
./src/miscellaneous.d \
./src/platform.d \
./src/poxi.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 gcc compiler'
	arm-none-eabi-gcc -Wall -O0 -g3 -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -I../../poxi_zybo_bsp_0/ps7_cortexa9_0/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


