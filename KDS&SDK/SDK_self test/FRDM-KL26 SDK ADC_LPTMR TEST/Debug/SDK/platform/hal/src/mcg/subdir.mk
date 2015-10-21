################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SDK/platform/hal/src/mcg/fsl_mcg_hal.c \
../SDK/platform/hal/src/mcg/fsl_mcg_hal_modes.c 

OBJS += \
./SDK/platform/hal/src/mcg/fsl_mcg_hal.o \
./SDK/platform/hal/src/mcg/fsl_mcg_hal_modes.o 

C_DEPS += \
./SDK/platform/hal/src/mcg/fsl_mcg_hal.d \
./SDK/platform/hal/src/mcg/fsl_mcg_hal_modes.d 


# Each subdirectory must supply rules for building sources it contributes
SDK/platform/hal/src/mcg/%.o: ../SDK/platform/hal/src/mcg/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -D"FSL_OSA_BM_TIMER_CONFIG=2" -D"CPU_MKL26Z128VLH4" -I"C:/Users/b46569/workspace.kds3.0/FRDM-KL26 SDK TEST/SDK/platform/hal/inc" -I"C:/Users/b46569/workspace.kds3.0/FRDM-KL26 SDK TEST/SDK/platform/hal/src/sim/MKL26Z4" -I"C:/Users/b46569/workspace.kds3.0/FRDM-KL26 SDK TEST/SDK/platform/system/src/clock/MKL26Z4" -I"C:/Users/b46569/workspace.kds3.0/FRDM-KL26 SDK TEST/SDK/platform/system/inc" -I"C:/Users/b46569/workspace.kds3.0/FRDM-KL26 SDK TEST/SDK/platform/osa/inc" -I"C:/Users/b46569/workspace.kds3.0/FRDM-KL26 SDK TEST/SDK/platform/CMSIS/Include" -I"C:/Users/b46569/workspace.kds3.0/FRDM-KL26 SDK TEST/SDK/platform/devices" -I"C:/Users/b46569/workspace.kds3.0/FRDM-KL26 SDK TEST/SDK/platform/devices/MKL26Z4/include" -I"C:/Users/b46569/workspace.kds3.0/FRDM-KL26 SDK TEST/SDK/platform/devices/MKL26Z4/startup" -I"C:/Users/b46569/workspace.kds3.0/FRDM-KL26 SDK TEST/Generated_Code/SDK/platform/devices/MKL26Z4/startup" -I"C:/Users/b46569/workspace.kds3.0/FRDM-KL26 SDK TEST/Sources" -I"C:/Users/b46569/workspace.kds3.0/FRDM-KL26 SDK TEST/Generated_Code" -I"C:/Users/b46569/workspace.kds3.0/FRDM-KL26 SDK TEST/SDK/platform/drivers/inc" -I"C:/Users/b46569/workspace.kds3.0/FRDM-KL26 SDK TEST/SDK/platform/utilities/src" -I"C:/Users/b46569/workspace.kds3.0/FRDM-KL26 SDK TEST/SDK/platform/utilities/inc" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


