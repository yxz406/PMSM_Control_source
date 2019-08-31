################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Observer/Src/AdaptVelEst.cpp \
../Observer/Src/EMFObs.cpp \
../Observer/Src/Observer.cpp 

OBJS += \
./Observer/Src/AdaptVelEst.o \
./Observer/Src/EMFObs.o \
./Observer/Src/Observer.o 

CPP_DEPS += \
./Observer/Src/AdaptVelEst.d \
./Observer/Src/EMFObs.d \
./Observer/Src/Observer.d 


# Each subdirectory must supply rules for building sources it contributes
Observer/Src/AdaptVelEst.o: ../Observer/Src/AdaptVelEst.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DSTM32F446xx -DUSE_FULL_LL_DRIVER -DDEBUG -c -I../CMSIS_DSP -I../Inc -I../SystemLib/Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Observer/Inc -I../MotorLib/Inc -I../MathLib/Inc -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Observer/Src/AdaptVelEst.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Observer/Src/EMFObs.o: ../Observer/Src/EMFObs.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DSTM32F446xx -DUSE_FULL_LL_DRIVER -DDEBUG -c -I../CMSIS_DSP -I../Inc -I../SystemLib/Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Observer/Inc -I../MotorLib/Inc -I../MathLib/Inc -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Observer/Src/EMFObs.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Observer/Src/Observer.o: ../Observer/Src/Observer.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DSTM32F446xx -DUSE_FULL_LL_DRIVER -DDEBUG -c -I../CMSIS_DSP -I../Inc -I../SystemLib/Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Observer/Inc -I../MotorLib/Inc -I../MathLib/Inc -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Observer/Src/Observer.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

