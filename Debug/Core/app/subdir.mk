################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/app/app.c 

OBJS += \
./Core/app/app.o 

C_DEPS += \
./Core/app/app.d 


# Each subdirectory must supply rules for building sources it contributes
Core/app/%.o Core/app/%.su Core/app/%.cyclo: ../Core/app/%.c Core/app/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Core/logs -I../Core/app -I../Core/sensors -I../Core/inputs -I../Core/hydraulic -I../Core/can_if -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-app

clean-Core-2f-app:
	-$(RM) ./Core/app/app.cyclo ./Core/app/app.d ./Core/app/app.o ./Core/app/app.su

.PHONY: clean-Core-2f-app

