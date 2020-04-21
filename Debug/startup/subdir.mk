################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
../startup/startup_stm32f10x_md.S 

OBJS += \
./startup/startup_stm32f10x_md.o 

S_UPPER_DEPS += \
./startup/startup_stm32f10x_md.d 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -DSTM32 -DSTM32F1 -DSTM32F103RBTx -DNUCLEO_F103RB -DDEBUG -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -I"C:/Users/micha/workspace/Kacper5_v1/Utilities/STM32F1xx-Nucleo" -I"C:/Users/micha/workspace/Kacper5_v1/StdPeriph_Driver/inc" -I"C:/Users/micha/workspace/Kacper5_v1/inc" -I"C:/Users/micha/workspace/Kacper5_v1/CMSIS/device" -I"C:/Users/micha/workspace/Kacper5_v1/CMSIS/core" -I"C:/Users/micha/workspace/Kacper5_v1/Interfaces" -I"C:/Users/micha/workspace/Kacper5_v1/Measurments" -I"C:/Users/micha/workspace/Kacper5_v1/Time" -I"C:/Users/micha/workspace/Kacper5_v1/Control" -I"C:/Users/micha/workspace/Kacper5_v1/Kacper" -I"C:/Users/micha/workspace/Kacper5_v1/STM32" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


