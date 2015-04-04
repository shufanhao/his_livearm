/*
 * sample_comm_vda.c
 *
 *  Created on: 2014年12月5日
 *      Author: frank
 */

#ifndef SAMPLE_COMM_VDA_C_
#define SAMPLE_COMM_VDA_C_
#include <hi_include/sample_comm.h>

/*typedef struct hiVDA_OD_PARAM_S
 {
 HI_BOOL bThreadStart;
 VDA_CHN VdaChn;
 }VDA_OD_PARAM_S;
 typedef struct hiVDA_MD_PARAM_S
 {
 HI_BOOL bThreadStart;
 VDA_CHN VdaChn;
 }VDA_MD_PARAM_S;

 #define SAMPLE_VDA_MD_CHN 0
 #define SAMPLE_VDA_OD_CHN 1

 static pthread_t gs_VdaPid[2];
 static VDA_MD_PARAM_S gs_stMdParam;
 static VDA_OD_PARAM_S gs_stOdParam;*/

HI_S32 SAMPLE_COMM_VDA_MdPrtObj(FILE *fp, VDA_DATA_S *pstVdaData);
HI_S32 SAMPLE_COMM_VDA_MdPrtAp(FILE *fp, VDA_DATA_S *pstVdaData);
HI_S32 SAMPLE_COMM_VDA_MdPrtSad(FILE *fp, VDA_DATA_S *pstVdaData);
HI_VOID *SAMPLE_COMM_VDA_MdGetResult(HI_VOID *pdata);
HI_S32 SAMPLE_COMM_VDA_OdPrt(FILE *fp, VDA_DATA_S *pstVdaData);
HI_VOID *SAMPLE_COMM_VDA_OdGetResult(HI_VOID *pdata);
HI_S32 SAMPLE_COMM_VDA_MdStart(VDA_CHN VdaChn, VI_CHN ViChn, SIZE_S *pstSize);
HI_S32 SAMPLE_COMM_VDA_OdStart(VDA_CHN VdaChn, VI_CHN ViChn, SIZE_S *pstSize);
HI_VOID SAMPLE_COMM_VDA_MdStop(VDA_CHN VdaChn, VI_CHN ViChn);
HI_VOID SAMPLE_COMM_VDA_OdStop(VDA_CHN VdaChn, VI_CHN ViChn);

#endif /* SAMPLE_COMM_VDA_C_ */
