/******************************************************************************
 A simple program of Hisilicon HI3531 video encode implementation.
 Copyright (C), 2010-2011, Hisilicon Tech. Co., Ltd.
 ******************************************************************************
 Modification:  2011-2 Created
 ******************************************************************************/
#ifdef __cplusplus
#if __cplusplus
/*
 #include "sample_comm_sys.h"
 #include "sample_venc.h"
 */
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>

#include <hi_include/sample_comm.h>

VIDEO_NORM_E gs_enNorm = VIDEO_ENCODING_MODE_NTSC; //gs_enNorm=1  全局变量 把这句话放在了sample_venc.h里面了

/******************************************************************************
 * function : show usage
 * 输出的信息：
 * Usage : ./sample_venc <index>
 index:
 0) 720p frank test classic H264 encode.
 1) 1*720p frank test MJPEG encode.
 2) 1*720p JPEG snap.
 ******************************************************************************/
void SAMPLE_VENC_Usage(char *sPrgNm) {
	printf("Usage success: %s <index>\n", sPrgNm);
	printf("index:\n");
	printf("\t 0) 720p frank test classic H264 encode.\n");
	printf("\t 1) 1*720p frank test MJPEG encode.\n");
	printf("\t 2) 1*720p JPEG snap.\n");

	return;
}

/******************************************************************************
 * function : to process abnormal case
 ******************************************************************************/
void SAMPLE_VENC_HandleSig(HI_S32 signo) {
	if (SIGINT == signo || SIGTSTP == signo) {
		SAMPLE_COMM_SYS_Exit();
		printf("\033[0;31mprogram termination abnormally!\033[0;39m\n");
	}
	exit(-1);
}

/*****************************************************************************
 * function : to process abnormal case - the case of stream venc
 ******************************************************************************/
void SAMPLE_VENC_StreamHandleSig(HI_S32 signo) {

	if (SIGINT == signo || SIGTSTP == signo) {
		SAMPLE_COMM_SYS_Exit();
		printf("\033[0;31mprogram exit abnormally!\033[0;39m\n");
	}

	exit(0);
}

/******************************************************************************
 * function :  H.264@720p@30fps+H.264@VGA@30fps+H.264@QVGA@30fps
 ******************************************************************************/
HI_S32 SAMPLE_VENC_720P_CLASSIC(HI_VOID) {
	PAYLOAD_TYPE_E enPayLoad[3] = { PT_H264, PT_H264, PT_H264 }; //PT_H264是96
	PIC_SIZE_E enSize[3] = { PIC_HD720, PIC_VGA, PIC_QVGA }; //enSIze[0]=PIC_HD720

	VB_CONF_S stVbConf; //缓存池 结构体
	SAMPLE_VI_CONFIG_S stViConfig; //输入通道配置

	VPSS_GRP VpssGrp; //int 型 组
	VPSS_CHN VpssChn; //int 型 通道
	VPSS_GRP_ATTR_S stVpssGrpAttr; //VPSS组属性结构体
	VPSS_CHN_ATTR_S stVpssChnAttr; //VPSS通道属性结构体
	VPSS_CHN_MODE_S stVpssChnMode; //VPSS通道工作属性结构体
	VPSS_EXT_CHN_ATTR_S stVpssExtChnAttr; //VPSS扩展通道的工作属性结构体

	VENC_GRP VencGrp; //int 型 Venc组
	VENC_CHN VencChn; //int 型 Venc通道
	SAMPLE_RC_E enRcMode = SAMPLE_RC_CBR; //帧率控制方式
	//HI_S32 s32ChnNum = 3;
	HI_S32 s32Ret = HI_SUCCESS;
	HI_U32 u32BlkSize;
	SIZE_S stSize;

	/******************************************
	 step  1: init sys variable 主要是初始化视频缓存池
	 ******************************************/
	memset(&stVbConf, 0, sizeof(VB_CONF_S)); //memset()把你快连续的内存初始化为你给的值,这里是初始化为0
	stVbConf.u32MaxPoolCnt = 128;//系统中所容纳缓存池的个数
	/*video buffer*/
	//根据enSize 来确定缓存块的大小 因为是输出了三段码流 则初始化了三个缓存池
	//u32BlkSize是缓存池中每个缓存块的大小
	u32BlkSize = SAMPLE_COMM_SYS_CalcPicVbBlkSize(gs_enNorm, enSize[0],
	SAMPLE_PIXEL_FORMAT, SAMPLE_SYS_ALIGN_WIDTH);
	stVbConf.astCommPool[0].u32BlkSize = u32BlkSize; //每个缓存块大小768*576*2
	stVbConf.astCommPool[0].u32BlkCnt = 5;//5;//10; //缓存块的个数。可不可以小点呢？？
	//stVbConf.astCommPool[0].u32BlkCnt = 6;
	u32BlkSize = SAMPLE_COMM_SYS_CalcPicVbBlkSize(gs_enNorm, enSize[1],
	SAMPLE_PIXEL_FORMAT, SAMPLE_SYS_ALIGN_WIDTH);
	//stVbConf.astCommPool[1].u32BlkSize = u32BlkSize;//384*288*2
	stVbConf.astCommPool[1].u32BlkSize = 0;
	stVbConf.astCommPool[1].u32BlkCnt = 0;
	//stVbConf.astCommPool[1].u32BlkCnt = 2;
	u32BlkSize = SAMPLE_COMM_SYS_CalcPicVbBlkSize(gs_enNorm, enSize[2],
	SAMPLE_PIXEL_FORMAT, SAMPLE_SYS_ALIGN_WIDTH);
	stVbConf.astCommPool[2].u32BlkSize = 0;
	stVbConf.astCommPool[2].u32BlkCnt = 0;//6;
	//stVbConf.astCommPool[2].u32BlkCnt = 1;

	stVbConf.astCommPool[3].u32BlkSize = (196 * 4);
	stVbConf.astCommPool[3].u32BlkCnt = 0;//6;
	//stVbConf.astCommPool[3].u32BlkCnt = 1;
	//以下部分是原始的
	/*u32BlkSize = SAMPLE_COMM_SYS_CalcPicVbBlkSize(gs_enNorm,\
	                enSize[0], SAMPLE_PIXEL_FORMAT, SAMPLE_SYS_ALIGN_WIDTH);
	    stVbConf.astCommPool[0].u32BlkSize = u32BlkSize;
	    stVbConf.astCommPool[0].u32BlkCnt = 10;

	    u32BlkSize = SAMPLE_COMM_SYS_CalcPicVbBlkSize(gs_enNorm,\
	                enSize[1], SAMPLE_PIXEL_FORMAT, SAMPLE_SYS_ALIGN_WIDTH);
	    stVbConf.astCommPool[1].u32BlkSize = u32BlkSize;
	    stVbConf.astCommPool[1].u32BlkCnt = 6;

	    u32BlkSize = SAMPLE_COMM_SYS_CalcPicVbBlkSize(gs_enNorm,\
	                enSize[2], SAMPLE_PIXEL_FORMAT, SAMPLE_SYS_ALIGN_WIDTH);
	    stVbConf.astCommPool[2].u32BlkSize = u32BlkSize;
	    stVbConf.astCommPool[2].u32BlkCnt = 6;

	    stVbConf.astCommPool[3].u32BlkSize = (196*4);
	    stVbConf.astCommPool[3].u32BlkCnt = 6;*/
	/******************************************
	 step 2: mpp system init.
	 ******************************************/
	s32Ret = SAMPLE_COMM_SYS_Init(&stVbConf);
	if (HI_SUCCESS != s32Ret) {
		SAMPLE_PRT("system init failed with %d!\n", s32Ret);
		// goto END_VENC_720P_CLASSIC_0; //goto 语句使标号直接跳转到标号所指定位置
		SAMPLE_COMM_SYS_Exit();
	}

	/******************************************
	 step 3: start vi dev & chn to capture
	 ******************************************/
	stViConfig.enViMode = APTINA_AR0130_DC_720P_30FPS; //将输入通道配置的参数设置好
	stViConfig.enRotate = ROTATE_NONE;
	stViConfig.enNorm = VIDEO_ENCODING_MODE_AUTO;
	stViConfig.enViChnSet = VI_CHN_SET_NORMAL;
	s32Ret = SAMPLE_COMM_VI_StartVi(&stViConfig);
	if (HI_SUCCESS != s32Ret) {
		SAMPLE_PRT("start vi failed!\n");
		//goto END_VENC_720P_CLASSIC_1;
		SAMPLE_COMM_VI_StopVi(&stViConfig);
	}

	/******************************************
	 step 4: start vpss and vi bind vpss
	 ******************************************/
	s32Ret = SAMPLE_COMM_SYS_GetPicSize(gs_enNorm, enSize[0], &stSize); //获得的是720P分辨率的宽度和高度，1280*720
	if (HI_SUCCESS != s32Ret) {
		SAMPLE_PRT("SAMPLE_COMM_SYS_GetPicSize failed!\n");
		//goto END_VENC_720P_CLASSIC_1;
		SAMPLE_COMM_VI_StopVi(&stViConfig);
	}
	VpssGrp = 0;
	//group 0 属性结构体设置
	stVpssGrpAttr.u32MaxW = stSize.u32Width;
	stVpssGrpAttr.u32MaxH = stSize.u32Height;
	stVpssGrpAttr.bDrEn = HI_FALSE;
	stVpssGrpAttr.bDbEn = HI_FALSE;
	stVpssGrpAttr.bIeEn = HI_TRUE;
	stVpssGrpAttr.bNrEn = HI_TRUE;
	stVpssGrpAttr.bHistEn = HI_TRUE;
	stVpssGrpAttr.enDieMode = VPSS_DIE_MODE_AUTO;
	stVpssGrpAttr.enPixFmt = SAMPLE_PIXEL_FORMAT;
	//启动VPSS Group（）
	s32Ret = SAMPLE_COMM_VPSS_StartGroup(VpssGrp, &stVpssGrpAttr);
	if (HI_SUCCESS != s32Ret) {
		SAMPLE_PRT("Start Vpss failed!\n");
		//goto END_VENC_720P_CLASSIC_2;
		SAMPLE_COMM_VPSS_StopGroup(VpssGrp);
	}
	//绑定 vi 和vpss绑定
	s32Ret = SAMPLE_COMM_VI_BindVpss(stViConfig.enViMode);
	if (HI_SUCCESS != s32Ret) {
		SAMPLE_PRT("Vi bind Vpss failed!\n");
		//goto END_VENC_720P_CLASSIC_3;
		SAMPLE_COMM_VI_UnBindVpss(stViConfig.enViMode);
	}
	//VPSS通道0，1，3三种方式 因为编码出来三种分辨率的，分别对应720P、VGA、QVGA三种
	//方式
	VpssChn = 0;
	memset(&stVpssChnAttr, 0, sizeof(stVpssChnAttr));
	stVpssChnAttr.bFrameEn = HI_FALSE;//边框使能开关
	stVpssChnAttr.bSpEn = HI_TRUE;//边框属性
	s32Ret = SAMPLE_COMM_VPSS_EnableChn(VpssGrp, VpssChn, &stVpssChnAttr,
	HI_NULL, HI_NULL);
	if (HI_SUCCESS != s32Ret) {
		SAMPLE_PRT("Enable vpss chn failed!\n");
		//goto END_VENC_720P_CLASSIC_4;
		VpssGrp = 0;
		VpssChn = 3;
		SAMPLE_COMM_VPSS_DisableChn(VpssGrp, VpssChn);
		VpssChn = 0;
		SAMPLE_COMM_VPSS_DisableChn(VpssGrp, VpssChn);
		VpssChn = 1;
		SAMPLE_COMM_VPSS_DisableChn(VpssGrp, VpssChn);
	}

	VpssChn = 1;
	stVpssChnMode.enChnMode = VPSS_CHN_MODE_USER;//user模式,此模式下物理通道可与多个接受者进行绑定
	stVpssChnMode.bDouble = HI_FALSE;
	stVpssChnMode.enPixelFormat = SAMPLE_PIXEL_FORMAT;
	stVpssChnMode.u32Width = 640;
	stVpssChnMode.u32Height = 480;
	s32Ret = SAMPLE_COMM_VPSS_EnableChn(VpssGrp, VpssChn, &stVpssChnAttr,
			&stVpssChnMode, HI_NULL);
	if (HI_SUCCESS != s32Ret) {
		SAMPLE_PRT("Enable vpss chn failed!\n");
		//goto END_VENC_720P_CLASSIC_4;
		VpssGrp = 0;
		VpssChn = 3;
		SAMPLE_COMM_VPSS_DisableChn(VpssGrp, VpssChn);
		VpssChn = 0;
		SAMPLE_COMM_VPSS_DisableChn(VpssGrp, VpssChn);
		VpssChn = 1;
		SAMPLE_COMM_VPSS_DisableChn(VpssGrp, VpssChn);
	}

	VpssChn = 3;    //扩展通道
	stVpssExtChnAttr.s32BindChn = 1;
	stVpssExtChnAttr.s32SrcFrameRate = 30;
	stVpssExtChnAttr.s32DstFrameRate = 30;
	stVpssExtChnAttr.enPixelFormat = SAMPLE_PIXEL_FORMAT;
	stVpssExtChnAttr.u32Width = 320;
	stVpssExtChnAttr.u32Height = 240;
	s32Ret = SAMPLE_COMM_VPSS_EnableChn(VpssGrp, VpssChn, HI_NULL, HI_NULL,
			&stVpssExtChnAttr);
	if (HI_SUCCESS != s32Ret) {
		SAMPLE_PRT("Enable vpss chn failed!\n");
		//goto END_VENC_720P_CLASSIC_4;
		VpssGrp = 0;
		VpssChn = 3;
		SAMPLE_COMM_VPSS_DisableChn(VpssGrp, VpssChn);
		VpssChn = 0;
		SAMPLE_COMM_VPSS_DisableChn(VpssGrp, VpssChn);
		VpssChn = 1;
		SAMPLE_COMM_VPSS_DisableChn(VpssGrp, VpssChn);
	}

	/******************************************
	 step 5: start stream venc
	 ******************************************/
	/*** HD720P **/

	VpssGrp = 0;    //为什么这个地方又要重新再设置一次呢
	VpssChn = 0;
	VencGrp = 0;
	VencChn = 0;
	s32Ret = SAMPLE_COMM_VENC_Start(VencGrp, VencChn, enPayLoad[0], gs_enNorm,
			enSize[0], enRcMode);
	if (HI_SUCCESS != s32Ret) {
		SAMPLE_PRT("Start Venc failed!\n");
		//goto END_VENC_720P_CLASSIC_5;
		VpssGrp = 0;

		VpssChn = 0;
		VencGrp = 0;
		VencChn = 0;
		SAMPLE_COMM_VENC_UnBindVpss(VencGrp, VpssGrp, VpssChn);
		SAMPLE_COMM_VENC_Stop(VencGrp, VencChn);

		VpssChn = 1;
		VencGrp = 1;
		VencChn = 1;
		SAMPLE_COMM_VENC_UnBindVpss(VencGrp, VpssGrp, VpssChn);
		SAMPLE_COMM_VENC_Stop(VencGrp, VencChn);

		VpssChn = 3;
		VencGrp = 2;
		VencChn = 2;
		SAMPLE_COMM_VENC_UnBindVpss(VencGrp, VpssGrp, VpssChn);
		SAMPLE_COMM_VENC_Stop(VencGrp, VencChn);

		SAMPLE_COMM_VI_UnBindVpss(stViConfig.enViMode);
	}

	s32Ret = SAMPLE_COMM_VENC_BindVpss(VencGrp, VpssGrp, VpssChn);
	if (HI_SUCCESS != s32Ret) {
		SAMPLE_PRT("Start Venc failed!\n");
		//goto END_VENC_720P_CLASSIC_5;
		VpssGrp = 0;

		VpssChn = 0;
		VencGrp = 0;
		VencChn = 0;
		SAMPLE_COMM_VENC_UnBindVpss(VencGrp, VpssGrp, VpssChn);
		SAMPLE_COMM_VENC_Stop(VencGrp, VencChn);

		VpssChn = 1;
		VencGrp = 1;
		VencChn = 1;
		SAMPLE_COMM_VENC_UnBindVpss(VencGrp, VpssGrp, VpssChn);
		SAMPLE_COMM_VENC_Stop(VencGrp, VencChn);

		VpssChn = 3;
		VencGrp = 2;
		VencChn = 2;
		SAMPLE_COMM_VENC_UnBindVpss(VencGrp, VpssGrp, VpssChn);
		SAMPLE_COMM_VENC_Stop(VencGrp, VencChn);

		SAMPLE_COMM_VI_UnBindVpss(stViConfig.enViMode);
	}


	/*** vga 640*480**/
	VpssChn = 1;
	VencGrp = 1;
	VencChn = 1;
	s32Ret = SAMPLE_COMM_VENC_Start(VencGrp, VencChn, enPayLoad[1], gs_enNorm,
			enSize[1], enRcMode);
	if (HI_SUCCESS != s32Ret) {
		SAMPLE_PRT("Start Venc failed!\n");
		//goto END_VENC_720P_CLASSIC_5;
		VpssGrp = 0;

		VpssChn = 0;
		VencGrp = 0;
		VencChn = 0;
		SAMPLE_COMM_VENC_UnBindVpss(VencGrp, VpssGrp, VpssChn);
		SAMPLE_COMM_VENC_Stop(VencGrp, VencChn);

		VpssChn = 1;
		VencGrp = 1;
		VencChn = 1;
		SAMPLE_COMM_VENC_UnBindVpss(VencGrp, VpssGrp, VpssChn);
		SAMPLE_COMM_VENC_Stop(VencGrp, VencChn);

		VpssChn = 3;
		VencGrp = 2;
		VencChn = 2;
		SAMPLE_COMM_VENC_UnBindVpss(VencGrp, VpssGrp, VpssChn);
		SAMPLE_COMM_VENC_Stop(VencGrp, VencChn);

		SAMPLE_COMM_VI_UnBindVpss(stViConfig.enViMode);
	}

	s32Ret = SAMPLE_COMM_VENC_BindVpss(VencChn, VpssGrp, VpssChn);
	if (HI_SUCCESS != s32Ret) {
		SAMPLE_PRT("Start Venc failed!\n");
		//goto END_VENC_720P_CLASSIC_5;
		VpssGrp = 0;

		VpssChn = 0;
		VencGrp = 0;
		VencChn = 0;
		SAMPLE_COMM_VENC_UnBindVpss(VencGrp, VpssGrp, VpssChn);
		SAMPLE_COMM_VENC_Stop(VencGrp, VencChn);

		VpssChn = 1;
		VencGrp = 1;
		VencChn = 1;
		SAMPLE_COMM_VENC_UnBindVpss(VencGrp, VpssGrp, VpssChn);
		SAMPLE_COMM_VENC_Stop(VencGrp, VencChn);

		VpssChn = 3;
		VencGrp = 2;
		VencChn = 2;
		SAMPLE_COMM_VENC_UnBindVpss(VencGrp, VpssGrp, VpssChn);
		SAMPLE_COMM_VENC_Stop(VencGrp, VencChn);

		SAMPLE_COMM_VI_UnBindVpss(stViConfig.enViMode);
	}

	/*** qvga 320*240 **/
	VpssChn = 3;
	VencGrp = 2;
	VencChn = 2;
	s32Ret = SAMPLE_COMM_VENC_Start(VencGrp, VencChn, enPayLoad[2], gs_enNorm,
			enSize[2], enRcMode);
	if (HI_SUCCESS != s32Ret) {
		SAMPLE_PRT("Start Venc failed!\n");
		//goto END_VENC_720P_CLASSIC_5;
		VpssGrp = 0;

		VpssChn = 0;
		VencGrp = 0;
		VencChn = 0;
		SAMPLE_COMM_VENC_UnBindVpss(VencGrp, VpssGrp, VpssChn);
		SAMPLE_COMM_VENC_Stop(VencGrp, VencChn);

		VpssChn = 1;
		VencGrp = 1;
		VencChn = 1;
		SAMPLE_COMM_VENC_UnBindVpss(VencGrp, VpssGrp, VpssChn);
		SAMPLE_COMM_VENC_Stop(VencGrp, VencChn);

		VpssChn = 3;
		VencGrp = 2;
		VencChn = 2;
		SAMPLE_COMM_VENC_UnBindVpss(VencGrp, VpssGrp, VpssChn);
		SAMPLE_COMM_VENC_Stop(VencGrp, VencChn);

		SAMPLE_COMM_VI_UnBindVpss(stViConfig.enViMode);
	}

	s32Ret = SAMPLE_COMM_VENC_BindVpss(VencChn, VpssGrp, VpssChn);
	if (HI_SUCCESS != s32Ret) {
		SAMPLE_PRT("Start Venc failed!\n");
		// goto END_VENC_720P_CLASSIC_5;
		VpssGrp = 0;

		VpssChn = 0;
		VencGrp = 0;
		VencChn = 0;
		SAMPLE_COMM_VENC_UnBindVpss(VencGrp, VpssGrp, VpssChn);
		SAMPLE_COMM_VENC_Stop(VencGrp, VencChn);

		VpssChn = 1;
		VencGrp = 1;
		VencChn = 1;
		SAMPLE_COMM_VENC_UnBindVpss(VencGrp, VpssGrp, VpssChn);
		SAMPLE_COMM_VENC_Stop(VencGrp, VencChn);

		VpssChn = 3;
		VencGrp = 2;
		VencChn = 2;
		SAMPLE_COMM_VENC_UnBindVpss(VencGrp, VpssGrp, VpssChn);
		SAMPLE_COMM_VENC_Stop(VencGrp, VencChn);

		SAMPLE_COMM_VI_UnBindVpss(stViConfig.enViMode);
	}

	/******************************************
	 step 6: stream venc process -- get stream, then save it to file.
	 需要修改，不能让它放到文件里面。而是让它进行转发就是不存储了。
	 ******************************************/
	/*s32Ret = SAMPLE_COMM_VENC_StartGetStream(s32ChnNum);//传进来的参数是3三个不同分辨率码流
	 if (HI_SUCCESS != s32Ret)
	 {
	 SAMPLE_PRT("Start Venc failed!\n");
	 //goto END_VENC_720P_CLASSIC_5;
	 VpssGrp = 0;

	 VpssChn = 0;
	 VencGrp = 0;
	 VencChn = 0;
	 SAMPLE_COMM_VENC_UnBindVpss(VencGrp, VpssGrp, VpssChn);
	 SAMPLE_COMM_VENC_Stop(VencGrp,VencChn);

	 VpssChn = 1;
	 VencGrp = 1;
	 VencChn = 1;
	 SAMPLE_COMM_VENC_UnBindVpss(VencGrp, VpssGrp, VpssChn);
	 SAMPLE_COMM_VENC_Stop(VencGrp,VencChn);

	 VpssChn = 3;
	 VencGrp = 2;
	 VencChn = 2;
	 SAMPLE_COMM_VENC_UnBindVpss(VencGrp, VpssGrp, VpssChn);
	 SAMPLE_COMM_VENC_Stop(VencGrp,VencChn);

	 SAMPLE_COMM_VI_UnBindVpss(stViConfig.enViMode);
	 }
	 */
/*	printf("程序运行到step 6  \n");
	HI_S32 i;
	HI_S32 s32ChnTotal;
	VENC_CHN_ATTR_S stVencChnAttr;
	SAMPLE_VENC_GETSTREAM_PARA_S *pstPara;*/

	/******************************************
	 step 7: exit process
	 ******************************************/
	// SAMPLE_COMM_VENC_StopGetStream();
	/*END_VENC_720P_CLASSIC_5:
	 VpssGrp = 0;

	 VpssChn = 0;
	 VencGrp = 0;
	 VencChn = 0;
	 SAMPLE_COMM_VENC_UnBindVpss(VencGrp, VpssGrp, VpssChn);
	 SAMPLE_COMM_VENC_Stop(VencGrp,VencChn);

	 VpssChn = 1;
	 VencGrp = 1;
	 VencChn = 1;
	 SAMPLE_COMM_VENC_UnBindVpss(VencGrp, VpssGrp, VpssChn);
	 SAMPLE_COMM_VENC_Stop(VencGrp,VencChn);

	 VpssChn = 3;
	 VencGrp = 2;
	 VencChn = 2;
	 SAMPLE_COMM_VENC_UnBindVpss(VencGrp, VpssGrp, VpssChn);
	 SAMPLE_COMM_VENC_Stop(VencGrp,VencChn);

	 SAMPLE_COMM_VI_UnBindVpss(stViConfig.enViMode);
	 END_VENC_720P_CLASSIC_4:	//vpss stop
	 VpssGrp = 0;
	 VpssChn = 3;
	 SAMPLE_COMM_VPSS_DisableChn(VpssGrp, VpssChn);
	 VpssChn = 0;
	 SAMPLE_COMM_VPSS_DisableChn(VpssGrp, VpssChn);
	 VpssChn = 1;
	 SAMPLE_COMM_VPSS_DisableChn(VpssGrp, VpssChn);
	 END_VENC_720P_CLASSIC_3:    //vpss stop
	 SAMPLE_COMM_VI_UnBindVpss(stViConfig.enViMode);
	 END_VENC_720P_CLASSIC_2:    //vpss stop
	 SAMPLE_COMM_VPSS_StopGroup(VpssGrp);
	 END_VENC_720P_CLASSIC_1:	//vi stop
	 SAMPLE_COMM_VI_StopVi(&stViConfig);
	 END_VENC_720P_CLASSIC_0:	//system exit
	 SAMPLE_COMM_SYS_Exit();*/

	return s32Ret;
}

/******************************************************************************
 * function    : main()
 * Description : video venc sample
 ******************************************************************************/
//argc记录了用户在运行程序的命令行中输入的参数的个数 输入./sample_venc 0 参数是2个
//argv[]指向的数组中至少有一个字符指针，即arg[0].他通常指向程序中的可执行文件的文件名
//argc   是参数的个数，argv[]是参数，argv[0]是文件名，argv[1]是第一个参数
/*int main(int argc, char *argv[])
 {
 HI_S32 s32Ret; //int型默认是 s32Ret 是0
 if ( (argc < 2) || (1 != strlen(argv[1])))
 {
 SAMPLE_VENC_Usage(argv[0]);
 return HI_FAILURE; //HI_FAILURE 是-1 success 是0
 }
 //signal是多线程调用中用到的函数，只有程序运行着才可以有响应
 //如果发生sigint信号转去执行SAMPLE_VENC_HandleSig函数。ctrl +C 会产生sigint信号
 //SIGTERM是kill命令发出的信号
 signal(SIGINT, SAMPLE_VENC_HandleSig);
 signal(SIGTERM, SAMPLE_VENC_HandleSig);
 switch (*argv[1])
 {
 case '0': H.264@720p@30fps+H.264@VGA@30fps+H.264@QVGA@30fps
 s32Ret = SAMPLE_VENC_720P_CLASSIC();
 break;
 default:
 printf("the index is invaild!\n");
 SAMPLE_VENC_Usage(argv[0]);
 return HI_FAILURE;
 }

 if (HI_SUCCESS == s32Ret)
 printf("program exit normally!\n");
 else
 printf("program exit abnormally!\n");
 exit(s32Ret);
 }*/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */
