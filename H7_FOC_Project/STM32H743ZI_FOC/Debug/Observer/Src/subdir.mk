################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Observer/Src/AdaptVelEst.cpp \
../Observer/Src/EMFObs.cpp \
../Observer/Src/EstimatedAxisError.cpp \
../Observer/Src/Observer.cpp \
../Observer/Src/PII2.cpp 

OBJS += \
./Observer/Src/AdaptVelEst.o \
./Observer/Src/EMFObs.o \
./Observer/Src/EstimatedAxisError.o \
./Observer/Src/Observer.o \
./Observer/Src/PII2.o 

CPP_DEPS += \
./Observer/Src/AdaptVelEst.d \
./Observer/Src/EMFObs.d \
./Observer/Src/EstimatedAxisError.d \
./Observer/Src/Observer.d \
./Observer/Src/PII2.d 


# Each subdirectory must supply rules for building sources it contributes
Observer/Src/AdaptVelEst.o: ../Observer/Src/AdaptVelEst.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DSTM32H743xx -DDEBUG -D__FPU_PRESENT -c -I../Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../SystemLib/Inc -I../MathLib/Inc -I../MotorLib/Inc -I../Observer/Inc -I../SEGGER/Inc -I../CMSIS_DSP -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Observer/Src/AdaptVelEst.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Observer/Src/EMFObs.o: ../Observer/Src/EMFObs.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DSTM32H743xx -DDEBUG -D__FPU_PRESENT -c -I../Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../SystemLib/Inc -I../MathLib/Inc -I../MotorLib/Inc -I../Observer/Inc -I../SEGGER/Inc -I../CMSIS_DSP -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Observer/Src/EMFObs.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Observer/Src/EstimatedAxisError.o: ../Observer/Src/EstimatedAxisError.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DSTM32H743xx -DDEBUG -D__FPU_PRESENT -c -I../Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../SystemLib/Inc -I../MathLib/Inc -I../MotorLib/Inc -I../Observer/Inc -I../SEGGER/Inc -I../CMSIS_DSP -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Observer/Src/EstimatedAxisError.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Observer/Src/Observer.o: ../Observer/Src/Observer.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DSTM32H743xx -DDEBUG -D__FPU_PRESENT -c -I../Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../SystemLib/Inc -I../MathLib/Inc -I../MotorLib/Inc -I../Observer/Inc -I../SEGGER/Inc -I../CMSIS_DSP -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Observer/Src/Observer.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Observer/Src/PII2.o: ../Observer/Src/PII2.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DSTM32H743xx -DDEBUG -D__FPU_PRESENT -c -I../Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../SystemLib/Inc -I../MathLib/Inc -I../MotorLib/Inc -I../Observer/Inc -I../SEGGER/Inc -I../CMSIS_DSP -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Observer/Src/PII2.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

