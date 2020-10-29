################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32L4xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include Core/Inc/TransformFunctions/subdir.mk
-include Core/Inc/SupportFunctions/subdir.mk
-include Core/Inc/StatisticsFunctions/subdir.mk
-include Core/Inc/MatrixFunctions/subdir.mk
-include Core/Inc/FilteringFunctions/subdir.mk
-include Core/Inc/FastMathFunctions/subdir.mk
-include Core/Inc/ControllerFunctions/subdir.mk
-include Core/Inc/ComplexMathFunctions/subdir.mk
-include Core/Inc/CommonTables/subdir.mk
-include Core/Inc/BasicMathFunctions/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
STM32L4A6TEST.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
STM32L4A6TEST.list \

OBJCOPY_BIN += \
STM32L4A6TEST.bin \


# All Target
all: STM32L4A6TEST.elf secondary-outputs

# Tool invocations
STM32L4A6TEST.elf: $(OBJS) $(USER_OBJS) E:\LoRa_STM32L4A6_ADXL345\STM32L4A6ZGTX_FLASH.ld
	arm-none-eabi-gcc -o "STM32L4A6TEST.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"E:\LoRa_STM32L4A6_ADXL345\STM32L4A6ZGTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="STM32L4A6TEST.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -u _printf_float -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

STM32L4A6TEST.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "STM32L4A6TEST.list"
	@echo 'Finished building: $@'
	@echo ' '

STM32L4A6TEST.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "STM32L4A6TEST.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
