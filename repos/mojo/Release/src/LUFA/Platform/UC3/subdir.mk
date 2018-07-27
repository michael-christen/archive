################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/LUFA/Platform/UC3/InterruptManagement.c 

S_UPPER_SRCS += \
../src/LUFA/Platform/UC3/Exception.S 

OBJS += \
./src/LUFA/Platform/UC3/Exception.o \
./src/LUFA/Platform/UC3/InterruptManagement.o 

C_DEPS += \
./src/LUFA/Platform/UC3/InterruptManagement.d 

S_UPPER_DEPS += \
./src/LUFA/Platform/UC3/Exception.d 


# Each subdirectory must supply rules for building sources it contributes
src/LUFA/Platform/UC3/%.o: ../src/LUFA/Platform/UC3/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Assembler'
	avr-gcc -x assembler-with-cpp -mmcu=atmega16u4 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/LUFA/Platform/UC3/%.o: ../src/LUFA/Platform/UC3/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"/home/justin/Dropbox/laptop-workspace/Mojo-v2-Loader/src/Config" -DF_USB=8000000 -DUSE_LUFA_CONFIG_HEADER -Wall -Os -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16u4 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


