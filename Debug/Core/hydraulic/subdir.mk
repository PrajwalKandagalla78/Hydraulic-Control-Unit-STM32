################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/hydraulic/hydraulic_sm.c 

OBJS += \
./Core/hydraulic/hydraulic_sm.o 

C_DEPS += \
./Core/hydraulic/hydraulic_sm.d 


# Each subdirectory must supply rules for building sources it contributes
Core/hydraulic/%.o Core/hydraulic/%.su Core/hydraulic/%.cyclo: ../Core/hydraulic/%.c Core/hydraulic/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Core/logs -I../Core/app -I../Core/sensors -I../Core/inputs -I../Core/hydraulic -I../Core/can_if -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-hydraulic

clean-Core-2f-hydraulic:
	-$(RM) ./Core/hydraulic/hydraulic_sm.cyclo ./Core/hydraulic/hydraulic_sm.d ./Core/hydraulic/hydraulic_sm.o ./Core/hydraulic/hydraulic_sm.su

.PHONY: clean-Core-2f-hydraulic

