/*
 * sample_comm_vpss.h
 *
 *  Created on: 2014年12月5日
 *      Author: frank
 */

#ifndef SAMPLE_COMM_VPSS_H_
#define SAMPLE_COMM_VPSS_H_
HI_S32 SAMPLE_COMM_VPSS_MemConfig();
HI_S32 SAMPLE_COMM_VPSS_StartGroup(VPSS_GRP VpssGrp,
		VPSS_GRP_ATTR_S *pstVpssGrpAttr);
HI_S32 SAMPLE_COMM_VPSS_EnableChn(VPSS_GRP VpssGrp, VPSS_CHN VpssChn,
		VPSS_CHN_ATTR_S *pstVpssChnAttr, VPSS_CHN_MODE_S *pstVpssChnMode,
		VPSS_EXT_CHN_ATTR_S *pstVpssExtChnAttr);
HI_S32 SAMPLE_COMM_VPSS_StopGroup(VPSS_GRP VpssGrp);
HI_S32 SAMPLE_COMM_VPSS_DisableChn(VPSS_GRP VpssGrp, VPSS_CHN VpssChn);
HI_S32 SAMPLE_COMM_VPSS_Start(HI_S32 s32GrpCnt, SIZE_S *pstSize,
		HI_S32 s32ChnCnt, VPSS_GRP_ATTR_S *pstVpssGrpAttr);
HI_S32 SAMPLE_COMM_VPSS_Stop(HI_S32 s32GrpCnt, HI_S32 s32ChnCnt);

#endif /* SAMPLE_COMM_VPSS_H_ */
