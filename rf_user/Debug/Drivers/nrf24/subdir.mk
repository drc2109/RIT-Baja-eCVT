################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/nrf24/NRF24.c 

OBJS += \
./Drivers/nrf24/NRF24.o 

C_DEPS += \
./Drivers/nrf24/NRF24.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/nrf24/%.o Drivers/nrf24/%.su Drivers/nrf24/%.cyclo: ../Drivers/nrf24/%.c Drivers/nrf24/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DUSE_NUCLEO_144 -DUSE_HAL_DRIVER -DSTM32H753xx -c -I../Core/Inc -I"C:/Users/jells/STM32CubeIDE/workspace_2.0.0/rf_tx_test2/Drivers/nrf24" -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/BSP/STM32H7xx_Nucleo -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/jells/git/RIT-Baja-eCVT/rf_user/Drivers/nrf24" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-nrf24

clean-Drivers-2f-nrf24:
	-$(RM) ./Drivers/nrf24/NRF24.cyclo ./Drivers/nrf24/NRF24.d ./Drivers/nrf24/NRF24.o ./Drivers/nrf24/NRF24.su

.PHONY: clean-Drivers-2f-nrf24

