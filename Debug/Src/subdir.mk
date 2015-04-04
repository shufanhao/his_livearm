################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Src/Application.cpp \
../Src/H264OnDemandServerMediaSubsession.cpp \
../Src/V4L2FramedSource.cpp \
../Src/fifo.cpp 

C_SRCS += \
../Src/loadbmp.c \
../Src/sample_comm_audio.c \
../Src/sample_comm_isp.c \
../Src/sample_comm_sys.c \
../Src/sample_comm_vda.c \
../Src/sample_comm_venc.c \
../Src/sample_comm_vi.c \
../Src/sample_comm_vo.c \
../Src/sample_comm_vpss.c \
../Src/sample_venc.c 

OBJS += \
./Src/Application.o \
./Src/H264OnDemandServerMediaSubsession.o \
./Src/V4L2FramedSource.o \
./Src/fifo.o \
./Src/loadbmp.o \
./Src/sample_comm_audio.o \
./Src/sample_comm_isp.o \
./Src/sample_comm_sys.o \
./Src/sample_comm_vda.o \
./Src/sample_comm_venc.o \
./Src/sample_comm_vi.o \
./Src/sample_comm_vo.o \
./Src/sample_comm_vpss.o \
./Src/sample_venc.o 

C_DEPS += \
./Src/loadbmp.d \
./Src/sample_comm_audio.d \
./Src/sample_comm_isp.d \
./Src/sample_comm_sys.d \
./Src/sample_comm_vda.d \
./Src/sample_comm_venc.d \
./Src/sample_comm_vi.d \
./Src/sample_comm_vo.d \
./Src/sample_comm_vpss.d \
./Src/sample_venc.d 

CPP_DEPS += \
./Src/Application.d \
./Src/H264OnDemandServerMediaSubsession.d \
./Src/V4L2FramedSource.d \
./Src/fifo.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-hisiv100nptl-linux-g++ -I"/home/frank/workspace/his_livearm/Head" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	arm-hisiv100nptl-linux-gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


