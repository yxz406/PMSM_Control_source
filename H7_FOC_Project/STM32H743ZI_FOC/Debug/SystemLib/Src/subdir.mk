################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../SystemLib/Src/ADCInit.cpp \
../SystemLib/Src/ErrorHandler.cpp \
../SystemLib/Src/GPIOCtrl.cpp \
../SystemLib/Src/GPIOInit.cpp \
../SystemLib/Src/Interrupt.cpp \
../SystemLib/Src/PWM.cpp \
../SystemLib/Src/SystemTest.cpp \
../SystemLib/Src/TIMInit.cpp \
../SystemLib/Src/UART.cpp \
../SystemLib/Src/USARTInit.cpp 

OBJS += \
./SystemLib/Src/ADCInit.o \
./SystemLib/Src/ErrorHandler.o \
./SystemLib/Src/GPIOCtrl.o \
./SystemLib/Src/GPIOInit.o \
./SystemLib/Src/Interrupt.o \
./SystemLib/Src/PWM.o \
./SystemLib/Src/SystemTest.o \
./SystemLib/Src/TIMInit.o \
./SystemLib/Src/UART.o \
./SystemLib/Src/USARTInit.o 

CPP_DEPS += \
./SystemLib/Src/ADCInit.d \
./SystemLib/Src/ErrorHandler.d \
./SystemLib/Src/GPIOCtrl.d \
./SystemLib/Src/GPIOInit.d \
./SystemLib/Src/Interrupt.d \
./SystemLib/Src/PWM.d \
./SystemLib/Src/SystemTest.d \
./SystemLib/Src/TIMInit.d \
./SystemLib/Src/UART.d \
./SystemLib/Src/USARTInit.d 


# Each subdirectory must supply rules for building sources it contributes
SystemLib/Src/ADCInit.o: ../SystemLib/Src/ADCInit.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DSTM32H743xx -DDEBUG -c -I../CMSIS_DSP -I../Inc -I../MathLib/Inc -I../SystemLib/Inc -I../Drivers/CMSIS/Include -I../SEGGER/Inc -I../MotorLib/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Observer/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Wrapper/Inc -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"SystemLib/Src/ADCInit.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
SystemLib/Src/ErrorHandler.o: ../SystemLib/Src/ErrorHandler.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DSTM32H743xx -DDEBUG -c -I../CMSIS_DSP -I../Inc -I../MathLib/Inc -I../SystemLib/Inc -I../Drivers/CMSIS/Include -I../SEGGER/Inc -I../MotorLib/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Observer/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Wrapper/Inc -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"SystemLib/Src/ErrorHandler.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
SystemLib/Src/GPIOCtrl.o: ../SystemLib/Src/GPIOCtrl.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DSTM32H743xx -DDEBUG -c -I../CMSIS_DSP -I../Inc -I../MathLib/Inc -I../SystemLib/Inc -I../Drivers/CMSIS/Include -I../SEGGER/Inc -I../MotorLib/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Observer/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Wrapper/Inc -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"SystemLib/Src/GPIOCtrl.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
SystemLib/Src/GPIOInit.o: ../SystemLib/Src/GPIOInit.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DSTM32H743xx -DDEBUG -c -I../CMSIS_DSP -I../Inc -I../MathLib/Inc -I../SystemLib/Inc -I../Drivers/CMSIS/Include -I../SEGGER/Inc -I../MotorLib/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Observer/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Wrapper/Inc -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"SystemLib/Src/GPIOInit.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
SystemLib/Src/Interrupt.o: ../SystemLib/Src/Interrupt.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DSTM32H743xx -DDEBUG -c -I../CMSIS_DSP -I../Inc -I../MathLib/Inc -I../SystemLib/Inc -I../Drivers/CMSIS/Include -I../SEGGER/Inc -I../MotorLib/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Observer/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Wrapper/Inc -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"SystemLib/Src/Interrupt.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
SystemLib/Src/PWM.o: ../SystemLib/Src/PWM.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DSTM32H743xx -DDEBUG -c -I../CMSIS_DSP -I../Inc -I../MathLib/Inc -I../SystemLib/Inc -I../Drivers/CMSIS/Include -I../SEGGER/Inc -I../MotorLib/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Observer/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Wrapper/Inc -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"SystemLib/Src/PWM.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
SystemLib/Src/SystemTest.o: ../SystemLib/Src/SystemTest.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DSTM32H743xx -DDEBUG -c -I../CMSIS_DSP -I../Inc -I../MathLib/Inc -I../SystemLib/Inc -I../Drivers/CMSIS/Include -I../SEGGER/Inc -I../MotorLib/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Observer/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Wrapper/Inc -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"SystemLib/Src/SystemTest.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
SystemLib/Src/TIMInit.o: ../SystemLib/Src/TIMInit.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DSTM32H743xx -DDEBUG -c -I../CMSIS_DSP -I../Inc -I../MathLib/Inc -I../SystemLib/Inc -I../Drivers/CMSIS/Include -I../SEGGER/Inc -I../MotorLib/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Observer/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Wrapper/Inc -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"SystemLib/Src/TIMInit.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
SystemLib/Src/UART.o: ../SystemLib/Src/UART.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DSTM32H743xx -DDEBUG -c -I../CMSIS_DSP -I../Inc -I../MathLib/Inc -I../SystemLib/Inc -I../Drivers/CMSIS/Include -I../SEGGER/Inc -I../MotorLib/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Observer/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Wrapper/Inc -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"SystemLib/Src/UART.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
SystemLib/Src/USARTInit.o: ../SystemLib/Src/USARTInit.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DSTM32H743xx -DDEBUG -c -I../CMSIS_DSP -I../Inc -I../MathLib/Inc -I../SystemLib/Inc -I../Drivers/CMSIS/Include -I../SEGGER/Inc -I../MotorLib/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Observer/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Wrapper/Inc -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"SystemLib/Src/USARTInit.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

