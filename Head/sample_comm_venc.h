/*
 * sample_comm_venc.h
 *
 *  Created on: 2014年12月5日
 *      Author: frank
 */

#ifndef SAMPLE_COMM_VENC_H_
#define SAMPLE_COMM_VENC_H_
#include <hi_include/sample_comm.h>

/*const HI_U8 g_SOI[2] = {0xFF, 0xD8};
 const HI_U8 g_EOI[2] = {0xFF, 0xD9};
 static pthread_t gs_VencPid;
 static SAMPLE_VENC_GETSTREAM_PARA_S gs_stPara;
 static HI_S32 gs_s32SnapCnt = 0;*/
HI_S32 SAMPLE_COMM_VENC_MemConfig(HI_VOID);
HI_S32 SAMPLE_COMM_VENC_BindVpss(VENC_GRP GrpChn, VPSS_GRP VpssGrp,
		VPSS_CHN VpssChn);
HI_S32 SAMPLE_COMM_VENC_UnBindVpss(VENC_GRP GrpChn, VPSS_GRP VpssGrp,
		VPSS_CHN VpssChn);
HI_S32 SAMPLE_COMM_VENC_GetFilePostfix(PAYLOAD_TYPE_E enPayload,
		char *szFilePostfix);
HI_S32 SAMPLE_COMM_VENC_SaveMJpeg(FILE* fpJpegFile, VENC_STREAM_S *pstStream);
HI_S32 SAMPLE_COMM_VENC_SaveH264(FILE* fpH264File, VENC_STREAM_S *pstStream);
HI_S32 SAMPLE_COMM_VENC_SaveJPEG(FILE *fpJpegFile, VENC_STREAM_S *pstStream);
HI_S32 SAMPLE_COMM_VENC_SaveSnap(VENC_STREAM_S *pstStream);
HI_S32 SAMPLE_COMM_VENC_SaveStream(PAYLOAD_TYPE_E enType, FILE *pFd,
		VENC_STREAM_S *pstStream);
HI_S32 SAMPLE_COMM_VENC_Start(VENC_GRP VencGrp, VENC_CHN VencChn,
		PAYLOAD_TYPE_E enType, VIDEO_NORM_E enNorm, PIC_SIZE_E enSize,
		SAMPLE_RC_E enRcMode);
HI_S32 SAMPLE_COMM_VENC_Stop(VENC_GRP VencGrp, VENC_CHN VencChn);
HI_S32 SAMPLE_COMM_VENC_SnapStart(VENC_GRP VencGrp, VENC_CHN VencChn,
		SIZE_S *pstSize);
HI_S32 SAMPLE_COMM_VENC_SnapStop(VENC_GRP VencGrp, VENC_CHN VencChn);
HI_S32 SAMPLE_COMM_VENC_SnapProcess(VENC_GRP VencGrp, VENC_CHN VencChn);
HI_VOID* SAMPLE_COMM_VENC_GetVencStreamProc(HI_VOID *p);
HI_S32 SAMPLE_COMM_VENC_StartGetStream(HI_S32 s32Cnt);
HI_S32 SAMPLE_COMM_VENC_StopGetStream();

#endif /* SAMPLE_COMM_VENC_H_ */
