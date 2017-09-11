################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/dsp/composedfilter.c \
../src/dsp/filter.c 

OBJS += \
./src/dsp/composedfilter.o \
./src/dsp/filter.o 

C_DEPS += \
./src/dsp/composedfilter.d \
./src/dsp/filter.d 


# Each subdirectory must supply rules for building sources it contributes
src/dsp/%.o: ../src/dsp/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 gcc compiler'
	arm-none-eabi-gcc -Wall -O0 -g3 -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -I../../poxi_zybo_bsp_0/ps7_cortexa9_0/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


