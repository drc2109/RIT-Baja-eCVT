################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/adrian_controller/Controller_P7.c \
../Drivers/adrian_controller/Controller_P7_data.c \
../Drivers/adrian_controller/rt_logging.c \
../Drivers/adrian_controller/rt_nonfinite.c 

OBJS += \
./Drivers/adrian_controller/Controller_P7.o \
./Drivers/adrian_controller/Controller_P7_data.o \
./Drivers/adrian_controller/rt_logging.o \
./Drivers/adrian_controller/rt_nonfinite.o 

C_DEPS += \
./Drivers/adrian_controller/Controller_P7.d \
./Drivers/adrian_controller/Controller_P7_data.d \
./Drivers/adrian_controller/rt_logging.d \
./Drivers/adrian_controller/rt_nonfinite.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/adrian_controller/%.o Drivers/adrian_controller/%.su Drivers/adrian_controller/%.cyclo: ../Drivers/adrian_controller/%.c Drivers/adrian_controller/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DUSE_HAL_DRIVER -DSTM32H753xx -DUSE_NUCLEO_144 -c -I../Core/Inc -I"C:/Users/jells/git/RIT-Baja-eCVT/msd_baja_ecvt_ecu/Drivers/nrf24" -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/BSP/STM32H7xx_Nucleo -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I"../Drivers/adrian_controller" -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-adrian_controller

clean-Drivers-2f-adrian_controller:
	-$(RM) ./Drivers/adrian_controller/Controller_P7.cyclo ./Drivers/adrian_controller/Controller_P7.d ./Drivers/adrian_controller/Controller_P7.o ./Drivers/adrian_controller/Controller_P7.su ./Drivers/adrian_controller/Controller_P7_data.cyclo ./Drivers/adrian_controller/Controller_P7_data.d ./Drivers/adrian_controller/Controller_P7_data.o ./Drivers/adrian_controller/Controller_P7_data.su ./Drivers/adrian_controller/rt_logging.cyclo ./Drivers/adrian_controller/rt_logging.d ./Drivers/adrian_controller/rt_logging.o ./Drivers/adrian_controller/rt_logging.su ./Drivers/adrian_controller/rt_nonfinite.cyclo ./Drivers/adrian_controller/rt_nonfinite.d ./Drivers/adrian_controller/rt_nonfinite.o ./Drivers/adrian_controller/rt_nonfinite.su

.PHONY: clean-Drivers-2f-adrian_controller

