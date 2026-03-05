################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/sensors/sensors.c 

OBJS += \
./Core/sensors/sensors.o 

C_DEPS += \
./Core/sensors/sensors.d 


# Each subdirectory must supply rules for building sources it contributes
Core/sensors/%.o Core/sensors/%.su Core/sensors/%.cyclo: ../Core/sensors/%.c Core/sensors/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Core/logs -I../Core/app -I../Core/sensors -I../Core/inputs -I../Core/hydraulic -I../Core/can_if -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-sensors

clean-Core-2f-sensors:
	-$(RM) ./Core/sensors/sensors.cyclo ./Core/sensors/sensors.d ./Core/sensors/sensors.o ./Core/sensors/sensors.su

.PHONY: clean-Core-2f-sensors

