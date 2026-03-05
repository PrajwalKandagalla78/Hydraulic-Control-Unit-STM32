################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/inputs/inputs.c 

OBJS += \
./Core/inputs/inputs.o 

C_DEPS += \
./Core/inputs/inputs.d 


# Each subdirectory must supply rules for building sources it contributes
Core/inputs/%.o Core/inputs/%.su Core/inputs/%.cyclo: ../Core/inputs/%.c Core/inputs/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Core/logs -I../Core/app -I../Core/sensors -I../Core/inputs -I../Core/hydraulic -I../Core/can_if -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-inputs

clean-Core-2f-inputs:
	-$(RM) ./Core/inputs/inputs.cyclo ./Core/inputs/inputs.d ./Core/inputs/inputs.o ./Core/inputs/inputs.su

.PHONY: clean-Core-2f-inputs

