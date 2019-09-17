################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Wrapper/Src/subdir.mk
-include SystemLib/Src/subdir.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include SEGGER/Src/subdir.mk
-include Observer/Src/subdir.mk
-include MotorLib/Src/subdir.mk
-include MathLib/Src/subdir.mk
-include Drivers/STM32H7xx_HAL_Driver/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
STM32H743ZI_FOC.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
STM32H743ZI_FOC.list \


# All Target
all: STM32H743ZI_FOC.elf secondary-outputs

# Tool invocations
STM32H743ZI_FOC.elf: $(OBJS) $(USER_OBJS) /Users/watashi/STM32CubeIDE/workspace_1.0.0/STM32H743ZI_FOC/STM32H743ZITX_FLASH.ld
	arm-none-eabi-g++ -o "STM32H743ZI_FOC.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m7 -T"/Users/watashi/STM32CubeIDE/workspace_1.0.0/STM32H743ZI_FOC/STM32H743ZITX_FLASH.ld" --specs=nosys.specs -Wl,-Map="STM32H743ZI_FOC.map" -Wl,--gc-sections -static -L"/Users/watashi/STM32CubeIDE/workspace_1.0.0/STM32H743ZI_FOC/CMSIS_DSP" -u _printf_float --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -lstdc++ -lsupc++ -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

STM32H743ZI_FOC.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "STM32H743ZI_FOC.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
