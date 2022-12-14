################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/periph/adc.c \
../Src/periph/dac.c \
../Src/periph/dma.c \
../Src/periph/gpio.c \
../Src/periph/interrupt.c \
../Src/periph/rcc.c \
../Src/periph/timer.c 

C_DEPS += \
./Src/periph/adc.d \
./Src/periph/dac.d \
./Src/periph/dma.d \
./Src/periph/gpio.d \
./Src/periph/interrupt.d \
./Src/periph/rcc.d \
./Src/periph/timer.d 

OBJS += \
./Src/periph/adc.o \
./Src/periph/dac.o \
./Src/periph/dma.o \
./Src/periph/gpio.o \
./Src/periph/interrupt.o \
./Src/periph/rcc.o \
./Src/periph/timer.o 


# Each subdirectory must supply rules for building sources it contributes
Src/periph/%.o Src/periph/%.su: ../Src/periph/%.c Src/periph/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DSTM32F746xx -DSTM32 -DSTM32F746ZGTx -DSTM32F7 -c -I../Inc -I"C:/Users/amoiseenko.YAM/STM32CubeIDE/workspace_1.9.0/main course2/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"C:/Users/amoiseenko.YAM/STM32CubeIDE/workspace_1.9.0/main course2/Drivers/CMSIS/Core/Include" -I"C:/Users/amoiseenko.YAM/STM32CubeIDE/workspace_1.9.0/main course2/Drivers/CMSIS/Device/ST/STM32F7xx" -I"C:/Users/amoiseenko.YAM/STM32CubeIDE/workspace_1.9.0/main course2/Drivers/CMSIS/Include" -I"C:/Users/amoiseenko.YAM/STM32CubeIDE/workspace_1.9.0/main course2/Drivers/CMSIS/Device" -I"C:/Users/amoiseenko.YAM/STM32CubeIDE/workspace_1.9.0/main course2/Drivers/CMSIS/Device/ST" -I"C:/Users/amoiseenko.YAM/STM32CubeIDE/workspace_1.9.0/main course2/Drivers" -I"C:/Users/amoiseenko.YAM/STM32CubeIDE/workspace_1.9.0/main course2/Inc/periph" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-periph

clean-Src-2f-periph:
	-$(RM) ./Src/periph/adc.d ./Src/periph/adc.o ./Src/periph/adc.su ./Src/periph/dac.d ./Src/periph/dac.o ./Src/periph/dac.su ./Src/periph/dma.d ./Src/periph/dma.o ./Src/periph/dma.su ./Src/periph/gpio.d ./Src/periph/gpio.o ./Src/periph/gpio.su ./Src/periph/interrupt.d ./Src/periph/interrupt.o ./Src/periph/interrupt.su ./Src/periph/rcc.d ./Src/periph/rcc.o ./Src/periph/rcc.su ./Src/periph/timer.d ./Src/periph/timer.o ./Src/periph/timer.su

.PHONY: clean-Src-2f-periph

