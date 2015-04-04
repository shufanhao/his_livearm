/*
 * sample_comm_sys.h
 *
 *  Created on: 2014年12月5日
 *      Author: frank
 */

#ifndef SAMPLE_COMM_SYS_H_
#define SAMPLE_COMM_SYS_H_
#include <hi_include/sample_comm.h>

HI_S32 SAMPLE_COMM_SYS_GetPicSize(VIDEO_NORM_E enNorm, PIC_SIZE_E enPicSize,
		SIZE_S *pstSize);
HI_U32 SAMPLE_COMM_SYS_CalcHistVbBlkSize(VIDEO_NORM_E enNorm,
		PIC_SIZE_E enPicSize, SIZE_S *pstHistBlkSize, HI_U32 u32AlignWidth);
HI_U32 SAMPLE_COMM_SYS_CalcPicVbBlkSize(VIDEO_NORM_E enNorm,
		PIC_SIZE_E enPicSize, PIXEL_FORMAT_E enPixFmt, HI_U32 u32AlignWidth);
HI_S32 SAMPLE_COMM_SYS_MemConfig(HI_VOID);
HI_S32 SAMPLE_COMM_SYS_Init(VB_CONF_S *pstVbConf);
HI_S32 SAMPLE_COMM_SYS_Payload2FilePostfix(PAYLOAD_TYPE_E enPayload,
		HI_CHAR* szFilePostfix);
HI_VOID SAMPLE_COMM_SYS_Exit(void);

#endif /* SAMPLE_COMM_SYS_H_ */
