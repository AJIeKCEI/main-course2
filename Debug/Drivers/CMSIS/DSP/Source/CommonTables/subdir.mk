################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CMSIS/DSP/Source/CommonTables/arm_common_tables.c \
../Drivers/CMSIS/DSP/Source/CommonTables/arm_const_structs.c 

C_DEPS += \
./Drivers/CMSIS/DSP/Source/CommonTables/arm_common_tables.d \
./Drivers/CMSIS/DSP/Source/CommonTables/arm_const_structs.d 

OBJS += \
./Drivers/CMSIS/DSP/Source/CommonTables/arm_common_tables.o \
./Drivers/CMSIS/DSP/Source/CommonTables/arm_const_structs.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/DSP/Source/CommonTables/%.o Drivers/CMSIS/DSP/Source/CommonTables/%.su: ../Drivers/CMSIS/DSP/Source/CommonTables/%.c Drivers/CMSIS/DSP/Source/CommonTables/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DARM_MATH_CM7 -D__FPU_PRESENT -DSTM32F746xx -DSTM32 -DSTM32F746ZGTx -DSTM32F7 -c -I../Inc -I"C:/Users/amoiseenko.YAM/STM32CubeIDE/workspace_1.9.0/main course2/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"C:/Users/amoiseenko.YAM/STM32CubeIDE/workspace_1.9.0/main course2/Drivers/CMSIS/Core/Include" -I"C:/Users/amoiseenko.YAM/STM32CubeIDE/workspace_1.9.0/main course2/Drivers/CMSIS/Device/ST/STM32F7xx" -I"C:/Users/amoiseenko.YAM/STM32CubeIDE/workspace_1.9.0/main course2/Drivers/CMSIS/Include" -I"C:/Users/amoiseenko.YAM/STM32CubeIDE/workspace_1.9.0/main course2/Drivers/CMSIS/Device" -I"C:/Users/amoiseenko.YAM/STM32CubeIDE/workspace_1.9.0/main course2/Drivers/CMSIS/Device/ST" -I"C:/Users/amoiseenko.YAM/STM32CubeIDE/workspace_1.9.0/main course2/Drivers" -I"C:/Users/amoiseenko.YAM/STM32CubeIDE/workspace_1.9.0/main course2/Inc/periph" -I"C:/Users/amoiseenko.YAM/STM32CubeIDE/workspace_1.9.0/main course2/Drivers/CMSIS/DSP/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-CMSIS-2f-DSP-2f-Source-2f-CommonTables

clean-Drivers-2f-CMSIS-2f-DSP-2f-Source-2f-CommonTables:
	-$(RM) ./Drivers/CMSIS/DSP/Source/CommonTables/arm_common_tables.d ./Drivers/CMSIS/DSP/Source/CommonTables/arm_common_tables.o ./Drivers/CMSIS/DSP/Source/CommonTables/arm_common_tables.su ./Drivers/CMSIS/DSP/Source/CommonTables/arm_const_structs.d ./Drivers/CMSIS/DSP/Source/CommonTables/arm_const_structs.o ./Drivers/CMSIS/DSP/Source/CommonTables/arm_const_structs.su

.PHONY: clean-Drivers-2f-CMSIS-2f-DSP-2f-Source-2f-CommonTables

