################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/tft_display/tft_graphics.c \
../src/tft_display/tft_spi_driver.c 

OBJS += \
./src/tft_display/tft_graphics.o \
./src/tft_display/tft_spi_driver.o 

C_DEPS += \
./src/tft_display/tft_graphics.d \
./src/tft_display/tft_spi_driver.d 


# Each subdirectory must supply rules for building sources it contributes
src/tft_display/%.o: ../src/tft_display/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 gcc compiler'
	arm-none-eabi-gcc -Wall -O0 -g3 -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -I../../poxi_zybo_bsp_0/ps7_cortexa9_0/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


