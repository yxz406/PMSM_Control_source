################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../MotorLib/Src/ArgCtrl.cpp \
../MotorLib/Src/DebugCtrl.cpp \
../MotorLib/Src/DebugInfo.cpp \
../MotorLib/Src/DebugInfoTiny.cpp \
../MotorLib/Src/MotorCtrl.cpp 

OBJS += \
./MotorLib/Src/ArgCtrl.o \
./MotorLib/Src/DebugCtrl.o \
./MotorLib/Src/DebugInfo.o \
./MotorLib/Src/DebugInfoTiny.o \
./MotorLib/Src/MotorCtrl.o 

CPP_DEPS += \
./MotorLib/Src/ArgCtrl.d \
./MotorLib/Src/DebugCtrl.d \
./MotorLib/Src/DebugInfo.d \
./MotorLib/Src/DebugInfoTiny.d \
./MotorLib/Src/MotorCtrl.d 


# Each subdirectory must supply rules for building sources it contributes
MotorLib/Src/ArgCtrl.o: ../MotorLib/Src/ArgCtrl.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DSTM32H743xx -DDEBUG -c -I../CMSIS_DSP -I../Inc -I../MathLib/Inc -I../SystemLib/Inc -I../Drivers/CMSIS/Include -I../SEGGER/Inc -I../MotorLib/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Observer/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Wrapper/Inc -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"MotorLib/Src/ArgCtrl.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
MotorLib/Src/DebugCtrl.o: ../MotorLib/Src/DebugCtrl.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DSTM32H743xx -DDEBUG -c -I../CMSIS_DSP -I../Inc -I../MathLib/Inc -I../SystemLib/Inc -I../Drivers/CMSIS/Include -I../SEGGER/Inc -I../MotorLib/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Observer/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Wrapper/Inc -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"MotorLib/Src/DebugCtrl.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
MotorLib/Src/DebugInfo.o: ../MotorLib/Src/DebugInfo.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DSTM32H743xx -DDEBUG -c -I../CMSIS_DSP -I../Inc -I../MathLib/Inc -I../SystemLib/Inc -I../Drivers/CMSIS/Include -I../SEGGER/Inc -I../MotorLib/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Observer/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Wrapper/Inc -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"MotorLib/Src/DebugInfo.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
MotorLib/Src/DebugInfoTiny.o: ../MotorLib/Src/DebugInfoTiny.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DSTM32H743xx -DDEBUG -c -I../CMSIS_DSP -I../Inc -I../MathLib/Inc -I../SystemLib/Inc -I../Drivers/CMSIS/Include -I../SEGGER/Inc -I../MotorLib/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Observer/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Wrapper/Inc -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"MotorLib/Src/DebugInfoTiny.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
MotorLib/Src/MotorCtrl.o: ../MotorLib/Src/MotorCtrl.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DSTM32H743xx -DDEBUG -c -I../CMSIS_DSP -I../Inc -I../MathLib/Inc -I../SystemLib/Inc -I../Drivers/CMSIS/Include -I../SEGGER/Inc -I../MotorLib/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Observer/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Wrapper/Inc -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"MotorLib/Src/MotorCtrl.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

