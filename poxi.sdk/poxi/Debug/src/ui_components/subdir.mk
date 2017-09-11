################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/ui_components/framepanel.c \
../src/ui_components/plot2d.c \
../src/ui_components/textlabel.c 

OBJS += \
./src/ui_components/framepanel.o \
./src/ui_components/plot2d.o \
./src/ui_components/textlabel.o 

C_DEPS += \
./src/ui_components/framepanel.d \
./src/ui_components/plot2d.d \
./src/ui_components/textlabel.d 


# Each subdirectory must supply rules for building sources it contributes
src/ui_components/%.o: ../src/ui_components/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 gcc compiler'
	arm-none-eabi-gcc -Wall -O0 -g3 -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -I../../poxi_zybo_bsp_0/ps7_cortexa9_0/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


