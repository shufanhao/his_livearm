/*
 * sample_venc.h
 *
 *  Created on: 2014年12月5日
 *      Author: frank
 */

#ifndef SAMPLE_VENC_H_
#define SAMPLE_VENC_H_
//声明sample_venc.c里面所有的函数
void SAMPLE_VENC_Usage(char *sPrgNm);
void SAMPLE_VENC_HandleSig(HI_S32 signo);
void SAMPLE_VENC_StreamHandleSig(HI_S32 signo);
HI_S32 SAMPLE_VENC_720P_CLASSIC(HI_VOID);

#endif /* SAMPLE_VENC_H_ */
