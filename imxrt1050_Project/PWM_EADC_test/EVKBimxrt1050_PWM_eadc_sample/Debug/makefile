################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include xip/subdir.mk
-include utilities/subdir.mk
-include startup/subdir.mk
-include source/subdir.mk
-include drivers/subdir.mk
-include device/subdir.mk
-include component/uart/subdir.mk
-include component/serial_manager/subdir.mk
-include component/lists/subdir.mk
-include board/boards/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: EVKBimxrt1050_PWM_eadc_sample.axf

# Tool invocations
EVKBimxrt1050_PWM_eadc_sample.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -Xlinker -Map="EVKBimxrt1050_PWM_eadc_sample.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -Xlinker --sort-section=alignment -Xlinker --cref -mcpu=cortex-m7 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -T EVKBimxrt1050_PWM_eadc_sample_Debug.ld -o "EVKBimxrt1050_PWM_eadc_sample.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) EVKBimxrt1050_PWM_eadc_sample.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "EVKBimxrt1050_PWM_eadc_sample.axf"; # arm-none-eabi-objcopy -v -O binary "EVKBimxrt1050_PWM_eadc_sample.axf" "EVKBimxrt1050_PWM_eadc_sample.bin" ; # checksum -p MIMXRT1052xxxxB -d "EVKBimxrt1050_PWM_eadc_sample.bin";
	-@echo ' '

.PHONY: all clean dependents post-build

-include ../makefile.targets
