################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/poxi_hardware/ad5624r.c \
../src/poxi_hardware/ad7887.c \
../src/poxi_hardware/mcp6s2x.c \
../src/poxi_hardware/probe.c \
../src/poxi_hardware/serialport.c \
../src/poxi_hardware/zybo.c 

OBJS += \
./src/poxi_hardware/ad5624r.o \
./src/poxi_hardware/ad7887.o \
./src/poxi_hardware/mcp6s2x.o \
./src/poxi_hardware/probe.o \
./src/poxi_hardware/serialport.o \
./src/poxi_hardware/zybo.o 

C_DEPS += \
./src/poxi_hardware/ad5624r.d \
./src/poxi_hardware/ad7887.d \
./src/poxi_hardware/mcp6s2x.d \
./src/poxi_hardware/probe.d \
./src/poxi_hardware/serialport.d \
./src/poxi_hardware/zybo.d 


# Each subdirectory must supply rules for building sources it contributes
src/poxi_hardware/%.o: ../src/poxi_hardware/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 gcc compiler'
	arm-none-eabi-gcc -Wall -O0 -g3 -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -I../../poxi_zybo_bsp_0/ps7_cortexa9_0/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


