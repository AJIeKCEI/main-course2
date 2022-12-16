################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/c_math.c \
../Src/control.c \
../Src/dsp.c \
../Src/main.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/system_stm32f7xx.c 

C_DEPS += \
./Src/c_math.d \
./Src/control.d \
./Src/dsp.d \
./Src/main.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/system_stm32f7xx.d 

OBJS += \
./Src/c_math.o \
./Src/control.o \
./Src/dsp.o \
./Src/main.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/system_stm32f7xx.o 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DARM_MATH_CM7 -D__FPU_PRESENT -DSTM32F746xx -DSTM32 -DSTM32F746ZGTx -DSTM32F7 -c -I../Inc -I"C:/Users/amoiseenko.YAM/STM32CubeIDE/workspace_1.9.0/main course2/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"C:/Users/amoiseenko.YAM/STM32CubeIDE/workspace_1.9.0/main course2/Drivers/CMSIS/Core/Include" -I"C:/Users/amoiseenko.YAM/STM32CubeIDE/workspace_1.9.0/main course2/Drivers/CMSIS/Device/ST/STM32F7xx" -I"C:/Users/amoiseenko.YAM/STM32CubeIDE/workspace_1.9.0/main course2/Drivers/CMSIS/Include" -I"C:/Users/amoiseenko.YAM/STM32CubeIDE/workspace_1.9.0/main course2/Drivers/CMSIS/Device" -I"C:/Users/amoiseenko.YAM/STM32CubeIDE/workspace_1.9.0/main course2/Drivers/CMSIS/Device/ST" -I"C:/Users/amoiseenko.YAM/STM32CubeIDE/workspace_1.9.0/main course2/Drivers" -I"C:/Users/amoiseenko.YAM/STM32CubeIDE/workspace_1.9.0/main course2/Inc/periph" -I"C:/Users/amoiseenko.YAM/STM32CubeIDE/workspace_1.9.0/main course2/Drivers/CMSIS/DSP/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/c_math.d ./Src/c_math.o ./Src/c_math.su ./Src/control.d ./Src/control.o ./Src/control.su ./Src/dsp.d ./Src/dsp.o ./Src/dsp.su ./Src/main.d ./Src/main.o ./Src/main.su ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su ./Src/system_stm32f7xx.d ./Src/system_stm32f7xx.o ./Src/system_stm32f7xx.su

.PHONY: clean-Src

