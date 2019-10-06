################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Wrapper/Src/Deus.cpp \
../Wrapper/Src/Wrapper.cpp 

OBJS += \
./Wrapper/Src/Deus.o \
./Wrapper/Src/Wrapper.o 

CPP_DEPS += \
./Wrapper/Src/Deus.d \
./Wrapper/Src/Wrapper.d 


# Each subdirectory must supply rules for building sources it contributes
Wrapper/Src/Deus.o: ../Wrapper/Src/Deus.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DSTM32H743xx -DDEBUG -c -I../Wrapper/Inc -I../MathLib/Inc -I../SystemLib/Inc -I../SEGGER/Inc -I../MotorLib/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../CMSIS_DSP -I../Inc -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Observer/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Wrapper/Src/Deus.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Wrapper/Src/Wrapper.o: ../Wrapper/Src/Wrapper.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DSTM32H743xx -DDEBUG -c -I../Wrapper/Inc -I../MathLib/Inc -I../SystemLib/Inc -I../SEGGER/Inc -I../MotorLib/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../CMSIS_DSP -I../Inc -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Observer/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Wrapper/Src/Wrapper.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

