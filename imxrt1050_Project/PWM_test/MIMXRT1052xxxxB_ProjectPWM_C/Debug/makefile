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
all: MIMXRT1052xxxxB_ProjectPWM_C.axf

# Tool invocations
MIMXRT1052xxxxB_ProjectPWM_C.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -Xlinker -Map="MIMXRT1052xxxxB_ProjectPWM_C.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -Xlinker --sort-section=alignment -Xlinker --cref -mcpu=cortex-m7 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -T MIMXRT1052xxxxB_ProjectPWM_C_Debug.ld -o "MIMXRT1052xxxxB_ProjectPWM_C.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) MIMXRT1052xxxxB_ProjectPWM_C.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "MIMXRT1052xxxxB_ProjectPWM_C.axf"; # arm-none-eabi-objcopy -v -O binary "MIMXRT1052xxxxB_ProjectPWM_C.axf" "MIMXRT1052xxxxB_ProjectPWM_C.bin" ; # checksum -p MIMXRT1052xxxxB -d "MIMXRT1052xxxxB_ProjectPWM_C.bin";
	-@echo ' '

.PHONY: all clean dependents post-build

-include ../makefile.targets
