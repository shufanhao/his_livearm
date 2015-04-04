/*
 * sample_comm_isp.h
 *
 *  Created on: 2014年12月5日
 *      Author: frank
 */

#ifndef SAMPLE_COMM_ISP_H_
#define SAMPLE_COMM_ISP_H_

#include <hi_include/sample_comm.h>

/*
 static pthread_t gs_IspPid;
 static HI_U32 u32IspExtBase = 0;

 #define  MAX_STRLEN		128
 #define  MAX_REGLEN		32
 #define  REAL_REGLEN	strlen("0x00000000:0x00000000")
 #define ISP_REG_SIZE_CFG	0x1014
 #define ISP_EXT_SIZE_CFG	0x0264

 #define CHECKREGADDR(regaddr)		\
do{\
	if ((regaddr < (unsigned int)ISP_REG_BASE)){return HI_FAILURE;}\
	else if(regaddr > (unsigned int)(u32IspExtBase + ISP_EXT_SIZE_CFG)){return HI_FAILURE;}\
	else if ((regaddr > (unsigned int)(ISP_REG_BASE + ISP_REG_SIZE_CFG)) && (regaddr < (unsigned int)u32IspExtBase) ){return HI_FAILURE;}\
	else{;};\
}while(0)
 */

HI_VOID SAMPLE_COMM_ISP_CircleWriteReg(HI_U32 u32RegAddr, FILE* fd);
HI_S32 SAMPLE_COMM_ISP_GetLine(HI_CHAR * pcSrcBuf, HI_S32 s32SrcLen);
HI_S32 SAMPLE_COMM_ISP_Reg2File(HI_CHAR* pcCfgFile);
HI_S32 SAMPLE_COMM_ISP_File2Reg(HI_CHAR* pCfgFile);
HI_S32 SAMPLE_COMM_ISP_LoadRegFile(SAMPLE_CFG_OPT_E enCfgOpt,
		HI_CHAR *pcIspCfgFile);
HI_S32 SAMPLE_COMM_ISP_SaveRegFile(SAMPLE_CFG_OPT_E enCfgOpt,
		HI_CHAR *pcIspCfgFile);
HI_S32 SAMPLE_COMM_ISP_SensorInit(void);
HI_S32 SAMPLE_COMM_ISP_Init(void);
HI_S32 SAMPLE_COMM_ISP_Run();
HI_VOID SAMPLE_COMM_ISP_Stop();

#endif /* SAMPLE_COMM_ISP_H_ */
