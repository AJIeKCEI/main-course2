################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/adc.c \
../Src/dac.c \
../Src/dma.c \
../Src/dsp.c \
../Src/gpio.c \
../Src/interrupt.c \
../Src/main.c \
../Src/rcc.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/system_stm32f7xx.c \
../Src/timer.c 

C_DEPS += \
./Src/adc.d \
./Src/dac.d \
./Src/dma.d \
./Src/dsp.d \
./Src/gpio.d \
./Src/interrupt.d \
./Src/main.d \
./Src/rcc.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/system_stm32f7xx.d \
./Src/timer.d 

OBJS += \
./Src/adc.o \
./Src/dac.o \
./Src/dma.o \
./Src/dsp.o \
./Src/gpio.o \
./Src/interrupt.o \
./Src/main.o \
./Src/rcc.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/system_stm32f7xx.o \
./Src/timer.o 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DSTM32F746xx -DSTM32 -DSTM32F746ZGTx -DSTM32F7 -c -I../Inc -I"C:/Users/amoiseenko.YAM/STM32CubeIDE/workspace_1.9.0/main course2/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"C:/Users/amoiseenko.YAM/STM32CubeIDE/workspace_1.9.0/main course2/Drivers/CMSIS/Core/Include" -I"C:/Users/amoiseenko.YAM/STM32CubeIDE/workspace_1.9.0/main course2/Drivers/CMSIS/Device/ST/STM32F7xx" -I"C:/Users/amoiseenko.YAM/STM32CubeIDE/workspace_1.9.0/main course2/Drivers/CMSIS/Include" -I"C:/Users/amoiseenko.YAM/STM32CubeIDE/workspace_1.9.0/main course2/Drivers/CMSIS/Device" -I"C:/Users/amoiseenko.YAM/STM32CubeIDE/workspace_1.9.0/main course2/Drivers/CMSIS/Device/ST" -I"C:/Users/amoiseenko.YAM/STM32CubeIDE/workspace_1.9.0/main course2/Drivers" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/adc.d ./Src/adc.o ./Src/adc.su ./Src/dac.d ./Src/dac.o ./Src/dac.su ./Src/dma.d ./Src/dma.o ./Src/dma.su ./Src/dsp.d ./Src/dsp.o ./Src/dsp.su ./Src/gpio.d ./Src/gpio.o ./Src/gpio.su ./Src/interrupt.d ./Src/interrupt.o ./Src/interrupt.su ./Src/main.d ./Src/main.o ./Src/main.su ./Src/rcc.d ./Src/rcc.o ./Src/rcc.su ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su ./Src/system_stm32f7xx.d ./Src/system_stm32f7xx.o ./Src/system_stm32f7xx.su ./Src/timer.d ./Src/timer.o ./Src/timer.su

.PHONY: clean-Src

