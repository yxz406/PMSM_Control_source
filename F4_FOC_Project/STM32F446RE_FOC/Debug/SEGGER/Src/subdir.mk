################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SEGGER/Src/SEGGER_RTT.c \
../SEGGER/Src/SEGGER_RTT_printf.c 

OBJS += \
./SEGGER/Src/SEGGER_RTT.o \
./SEGGER/Src/SEGGER_RTT_printf.o 

C_DEPS += \
./SEGGER/Src/SEGGER_RTT.d \
./SEGGER/Src/SEGGER_RTT_printf.d 


# Each subdirectory must supply rules for building sources it contributes
SEGGER/Src/SEGGER_RTT.o: ../SEGGER/Src/SEGGER_RTT.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DSTM32F446xx -DUSE_FULL_LL_DRIVER -DDEBUG -c -I../CMSIS_DSP -I../Inc -I../SystemLib/Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Observer/Inc -I../MotorLib/Inc -I../MathLib/Inc -I../SEGGER/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"SEGGER/Src/SEGGER_RTT.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
SEGGER/Src/SEGGER_RTT_printf.o: ../SEGGER/Src/SEGGER_RTT_printf.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DSTM32F446xx -DUSE_FULL_LL_DRIVER -DDEBUG -c -I../CMSIS_DSP -I../Inc -I../SystemLib/Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Observer/Inc -I../MotorLib/Inc -I../MathLib/Inc -I../SEGGER/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"SEGGER/Src/SEGGER_RTT_printf.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

