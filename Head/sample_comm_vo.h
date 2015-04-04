/*
 * sample_comm_vo.h
 *
 *  Created on: 2014年12月5日
 *      Author: frank
 */

#ifndef SAMPLE_COMM_VO_H_
#define SAMPLE_COMM_VO_H_
HI_S32 SAMPLE_COMM_VO_GetWH(VO_INTF_SYNC_E enIntfSync, HI_U32 *pu32W,
		HI_U32 *pu32H, HI_U32 *pu32Frm);
HI_S32 SAMPLE_COMM_VO_MemConfig(VO_DEV VoDev, HI_CHAR *pcMmzName);
HI_S32 SAMPLE_COMM_VO_StartDevLayer(VO_DEV VoDev, VO_PUB_ATTR_S *pstPubAttr,
		HI_U32 u32SrcFrmRate);
HI_S32 SAMPLE_COMM_VO_StopDevLayer(VO_DEV VoDev);
HI_S32 SAMPLE_COMM_VO_StartChn(VO_DEV VoDev, VO_PUB_ATTR_S *pstPubAttr,
		SAMPLE_VO_MODE_E enMode);
HI_S32 SAMPLE_COMM_VO_StopChn(VO_DEV VoDev, SAMPLE_VO_MODE_E enMode);
HI_S32 SAMPLE_COMM_VO_BindVpss(VO_DEV VoDev, VO_CHN VoChn, VPSS_GRP VpssGrp,
		VPSS_CHN VpssChn);
HI_S32 SAMPLE_COMM_VO_UnBindVpss(VO_DEV VoDev, VO_CHN VoChn, VPSS_GRP VpssGrp,
		VPSS_CHN VpssChn);
HI_S32 SAMPLE_COMM_VO_BindVi(VO_DEV VoDev, VO_CHN VoChn, VI_CHN ViChn);
HI_S32 SAMPLE_COMM_VO_UnBindVi(VO_DEV VoDev, VO_CHN VoChn);

#endif /* SAMPLE_COMM_VO_H_ */
