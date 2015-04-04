/*
 * sample_comm_vi.h
 *
 *  Created on: 2014年12月5日
 *      Author: frank
 */

#ifndef SAMPLE_COMM_VI_H_
#define SAMPLE_COMM_VI_H_
#include <hi_include/sample_comm.h>
/*VI_DEV_ATTR_S DEV_ATTR_BT656D1_1MUX =
 {
 接口模式
 VI_MODE_BT656,
 1、2、4路工作模式
 VI_WORK_MODE_1Multiplex,
 r_mask    g_mask    b_mask
 {0xFF000000,    0x0},
 逐行or隔行输入
 VI_SCAN_INTERLACED,
 AdChnId
 {-1, -1, -1, -1},
 enDataSeq, 仅支持YUV格式
 VI_INPUT_DATA_YVYU,
 同步信息，对应reg手册的如下配置, --bt1120时序无效
 {
 port_vsync   port_vsync_neg     port_hsync        port_hsync_neg
 VI_VSYNC_FIELD, VI_VSYNC_NEG_HIGH, VI_HSYNC_VALID_SINGNAL,VI_HSYNC_NEG_HIGH,VI_VSYNC_VALID_SINGAL,VI_VSYNC_VALID_NEG_HIGH,

 timing信息，对应reg手册的如下配置
 hsync_hfb    hsync_act    hsync_hhb
 {0,            0,        0,
 vsync0_vhb vsync0_act vsync0_hhb
 0,            0,        0,
 vsync1_vhb vsync1_act vsync1_hhb
 0,            0,            0}
 },
 使用内部ISP
 VI_PATH_BYPASS,
 输入数据类型
 VI_DATA_TYPE_YUV
 };

 AR0130 DC 12bit输入720P@30fps
 VI_DEV_ATTR_S DEV_ATTR_AR0130_DC_720P =
 {
 接口模式
 VI_MODE_DIGITAL_CAMERA,
 1、2、4路工作模式
 VI_WORK_MODE_1Multiplex,
 r_mask    g_mask    b_mask
 {0xFFF00000,    0x0},
 逐行or隔行输入
 VI_SCAN_PROGRESSIVE,
 AdChnId
 {-1, -1, -1, -1},
 enDataSeq, 仅支持YUV格式
 VI_INPUT_DATA_YUYV,

 同步信息，对应reg手册的如下配置, --bt1120时序无效
 {
 port_vsync   port_vsync_neg     port_hsync        port_hsync_neg
 VI_VSYNC_PULSE, VI_VSYNC_NEG_HIGH, VI_HSYNC_VALID_SINGNAL,VI_HSYNC_NEG_HIGH,VI_VSYNC_VALID_SINGAL,VI_VSYNC_VALID_NEG_HIGH,

 timing信息，对应reg手册的如下配置
 hsync_hfb    hsync_act    hsync_hhb
 {0,            1280,        0,
 vsync0_vhb vsync0_act vsync0_hhb
 0,            720,        0,
 vsync1_vhb vsync1_act vsync1_hhb
 0,            0,            0}
 },
 使用内部ISP
 VI_PATH_ISP,
 输入数据类型
 VI_DATA_TYPE_RGB
 };

 OV9712 DC 10bit输入
 VI_DEV_ATTR_S DEV_ATTR_OV9712_DC_720P =
 典型时序3:7441 BT1120 720P@60fps典型时序 (对接时序: 时序)
 {
 接口模式
 VI_MODE_DIGITAL_CAMERA,
 1、2、4路工作模式
 VI_WORK_MODE_1Multiplex,
 r_mask    g_mask    b_mask
 {0xFFC00000,    0x0},
 逐行or隔行输入
 VI_SCAN_PROGRESSIVE,
 AdChnId
 {-1, -1, -1, -1},
 enDataSeq, 仅支持YUV格式
 VI_INPUT_DATA_YUYV,

 同步信息，对应reg手册的如下配置, --bt1120时序无效
 {
 port_vsync   port_vsync_neg     port_hsync        port_hsync_neg
 VI_VSYNC_PULSE, VI_VSYNC_NEG_HIGH, VI_HSYNC_VALID_SINGNAL,VI_HSYNC_NEG_HIGH,VI_VSYNC_NORM_PULSE,VI_VSYNC_VALID_NEG_HIGH,

 timing信息，对应reg手册的如下配置
 hsync_hfb    hsync_act    hsync_hhb
 {408,            1280,        0,
 vsync0_vhb vsync0_act vsync0_hhb
 6,            720,        6,
 vsync1_vhb vsync1_act vsync1_hhb
 0,            0,            0}
 },
 使用内部ISP
 VI_PATH_ISP,
 输入数据类型
 VI_DATA_TYPE_RGB
 };

 imx122 DC 12bit输入
 VI_DEV_ATTR_S DEV_ATTR_IMX122_DC_1080P =
 {
 接口模式
 VI_MODE_DIGITAL_CAMERA,
 1、2、4路工作模式
 VI_WORK_MODE_1Multiplex,
 r_mask    g_mask    b_mask
 {0xFFF00000,    0x0},
 逐行or隔行输入
 VI_SCAN_PROGRESSIVE,
 AdChnId
 {-1, -1, -1, -1},
 enDataSeq, 仅支持YUV格式
 VI_INPUT_DATA_YUYV,

 同步信息，对应reg手册的如下配置, --bt1120时序无效
 {
 port_vsync   port_vsync_neg     port_hsync        port_hsync_neg
 VI_VSYNC_PULSE, VI_VSYNC_NEG_HIGH, VI_HSYNC_VALID_SINGNAL,VI_HSYNC_NEG_HIGH,VI_VSYNC_NORM_PULSE,VI_VSYNC_VALID_NEG_HIGH,

 timing信息，对应reg手册的如下配置
 hsync_hfb    hsync_act    hsync_hhb
 {0,            1920,        0,
 vsync0_vhb vsync0_act vsync0_hhb
 0,            1080,        0,
 vsync1_vhb vsync1_act vsync1_hhb
 0,            0,            0}
 },
 使用内部ISP
 VI_PATH_ISP,
 输入数据类型
 VI_DATA_TYPE_RGB
 };


 VI_CHN_ATTR_S CHN_ATTR_1920x1080_422 =
 典型通道属性2:1920x1080@xxfps 格式422
 {
 crop_x crop_y crop_w  crop_h
 {0,     0, 1920,   1080},
 dest_w  dest_h
 {1920,   1080 },
 enCapSel
 VI_CAPSEL_BOTH,
 通道格式
 PIXEL_FORMAT_YUV_SEMIPLANAR_422,
 bMirr  bFlip   bChromaResample
 0,      0,      0,
 s32SrcFrameRate   s32FrameRate
 -1, -1
 };

 VI_CHN_ATTR_S CHN_ATTR_860x540_422 =
 典型通道属性2:860x540@xxfps 格式422
 {
 crop_x crop_y crop_w  crop_h
 {0,     0, 860,   540},
 dest_w  dest_h
 {860,   540 },
 enCapSel
 VI_CAPSEL_BOTH,
 通道格式
 PIXEL_FORMAT_YUV_SEMIPLANAR_422,
 bMirr  bFlip   bChromaResample
 0,      0,      0,
 s32SrcFrameRate   s32FrameRate
 -1, -1
 };


 VI_CHN_ATTR_S CHN_ATTR_1280x720_422 =
 典型通道属性2:1280x720@xxfps 格式422
 {
 crop_x crop_y crop_w  crop_h
 {0,     0, 1280,   720 },
 dest_w  dest_h
 {1280,   720 },
 enCapSel
 VI_CAPSEL_BOTH,
 通道格式
 PIXEL_FORMAT_YUV_SEMIPLANAR_422,
 bMirr  bFlip   bChromaResample
 0,      0,      0,
 s32SrcFrameRate   s32FrameRate
 -1, -1
 };

 VI_CHN_ATTR_S CHN_ATTR_640x360_422 =
 典型通道属性2:640x360@xxfps 格式422
 {
 crop_x crop_y crop_w  crop_h
 {0,     0, 640,   360},
 dest_w  dest_h
 {640,   360 },
 enCapSel
 VI_CAPSEL_BOTH,
 通道格式
 PIXEL_FORMAT_YUV_SEMIPLANAR_422,
 bMirr  bFlip   bChromaResample
 0,      0,      0,
 s32SrcFrameRate   s32FrameRate
 -1, -1
 };


 VI_CHN_ATTR_S CHN_ATTR_1280x720_420 =
 典型通道属性2:1280x720@xxfps 格式422
 {
 crop_x crop_y crop_w  crop_h
 {0,     0, 1280,   720},
 dest_w  dest_h
 {1280,   720 },
 enCapSel
 VI_CAPSEL_BOTH,
 通道格式
 PIXEL_FORMAT_YUV_SEMIPLANAR_420,
 bMirr  bFlip   bChromaResample
 0,      0,      0,
 s32SrcFrameRate   s32FrameRate
 -1, -1
 };


 VI_CHN_ATTR_S CHN_ATTR_720x576_422 =
 典型通道属性2:720x576@xxfps 格式422
 {
 crop_x crop_y crop_w  crop_h
 {0,     0, 720,   576 },
 dest_w  dest_h
 {720,   576 },
 enCapSel
 VI_CAPSEL_BOTH,
 通道格式
 PIXEL_FORMAT_YUV_SEMIPLANAR_422,
 bMirr  bFlip   bChromaResample
 0,      0,      0,
 s32SrcFrameRate   s32FrameRate
 -1, -1
 };

 VI_CHN_ATTR_S CHN_ATTR_720x576_420 =
 典型通道属性2:720x576@xxfps 格式420
 {
 crop_x crop_y crop_w  crop_h
 {0,     0, 720,   576},
 dest_w  dest_h
 {720,   576},
 enCapSel
 VI_CAPSEL_BOTH,
 通道格式
 PIXEL_FORMAT_YUV_SEMIPLANAR_420,
 bMirr  bFlip   bChromaResample
 0,      0,      0,
 s32SrcFrameRate   s32FrameRate
 -1, -1
 };

 VI_CHN_ATTR_S CHN_ATTR_360x288_422 =
 典型通道属性2:360x288@xxfps 格式422
 {
 crop_x crop_y crop_w  crop_h
 {0,     0, 360,   288 },
 dest_w  dest_h
 {360,   288 },
 enCapSel
 VI_CAPSEL_BOTH,
 通道格式
 PIXEL_FORMAT_YUV_SEMIPLANAR_422,
 bMirr  bFlip   bChromaResample
 0,      0,      0,
 s32SrcFrameRate   s32FrameRate
 -1, -1
 };

 VI_CHN_ATTR_S CHN_ATTR_360x288_420 =
 典型通道属性2:360x288@xxfps 格式420
 {
 crop_x crop_y crop_w  crop_h
 {0,     0, 360,   288},
 dest_w  dest_h
 {360,   288},
 enCapSel
 VI_CAPSEL_BOTH,
 通道格式
 PIXEL_FORMAT_YUV_SEMIPLANAR_420,
 bMirr  bFlip   bChromaResample
 0,      0,      0,
 s32SrcFrameRate   s32FrameRate
 -1, -1
 };

 VI_CHN_ATTR_S CHN_ATTR_16x16_422 =
 典型通道属性2:720x576@xxfps 格式422
 {
 crop_x crop_y crop_w  crop_h
 {0,     0, 16,   16 },
 dest_w  dest_h
 {16,   16 },
 enCapSel
 VI_CAPSEL_BOTH,
 通道格式
 PIXEL_FORMAT_YUV_SEMIPLANAR_422,
 bMirr  bFlip   bChromaResample
 0,      0,      0,
 s32SrcFrameRate   s32FrameRate
 -1, -1
 };

 VI_CHN_ATTR_S CHN_ATTR_960x576_422 =
 典型通道属性2:720x576@xxfps 格式422
 {
 crop_x crop_y crop_w  crop_h
 {0,     0, 960,   576 },
 dest_w  dest_h
 {960,   576 },
 enCapSel
 VI_CAPSEL_BOTH,
 通道格式
 PIXEL_FORMAT_YUV_SEMIPLANAR_422,
 bMirr  bFlip   bChromaResample
 0,      0,      0,
 s32SrcFrameRate   s32FrameRate
 -1, -1
 };

 VI_CHN_ATTR_S CHN_ATTR_480x288_422 =
 典型通道属性2:720x576@xxfps 格式422
 {
 crop_x crop_y crop_w  crop_h
 {0,     0, 480,   288},
 dest_w  dest_h
 {480,   288 },
 enCapSel
 VI_CAPSEL_BOTH,
 通道格式
 PIXEL_FORMAT_YUV_SEMIPLANAR_422,
 bMirr  bFlip   bChromaResample
 0,      0,      0,
 s32SrcFrameRate   s32FrameRate
 -1, -1
 };*/

VI_DEV g_as32ViDev[VIU_MAX_DEV_NUM];
VI_CHN g_as32MaxChn[VIU_MAX_CHN_NUM];
VI_CHN g_as32SubChn[VIU_MAX_CHN_NUM];
HI_S32 SAMPLE_TW2865_CfgV(VIDEO_NORM_E enVideoMode, VI_WORK_MODE_E enWorkMode);
HI_S32 SAMPLE_COMM_VI_Mode2Param(SAMPLE_VI_MODE_E enViMode,
		SAMPLE_VI_PARAM_S *pstViParam);
HI_S32 SAMPLE_COMM_VI_ADStart(SAMPLE_VI_MODE_E enViMode, VIDEO_NORM_E enNorm);
HI_S32 SAMPLE_COMM_VI_Mode2Size(SAMPLE_VI_MODE_E enViMode, VIDEO_NORM_E enNorm,
		SIZE_S *pstSize);
VI_DEV SAMPLE_COMM_VI_GetDev(SAMPLE_VI_MODE_E enViMode, VI_CHN ViChn);
HI_S32 SAMPLE_COMM_VI_MemConfig(SAMPLE_VI_MODE_E enViMode);
HI_S32 SAMPLE_COMM_VI_StartDev(VI_DEV ViDev, SAMPLE_VI_MODE_E enViMode);
HI_S32 SAMPLE_COMM_VI_StartChn(VI_CHN ViChn, RECT_S *pstCapRect,
		SIZE_S *pstTarSize, SAMPLE_VI_CONFIG_S* pstViConfig);
HI_S32 SAMPLE_COMM_VI_StartBT656(SAMPLE_VI_MODE_E enViMode,
		VIDEO_NORM_E enNorm);
HI_S32 SAMPLE_COMM_VI_StopBT656(SAMPLE_VI_MODE_E enViMode);
HI_S32 SAMPLE_COMM_VI_BindVpss(SAMPLE_VI_MODE_E enViMode);
HI_BOOL IsSensorInput(SAMPLE_VI_MODE_E enViMode);
HI_S32 SAMPLE_COMM_VI_BindVenc(SAMPLE_VI_MODE_E enViMode);
HI_S32 SAMPLE_COMM_VI_StartIsp(SAMPLE_VI_CONFIG_S* pstViConfig);
HI_S32 SAMPLE_COMM_VI_StopIsp(SAMPLE_VI_CONFIG_S* pstViConfig);
HI_S32 SAMPLE_COMM_VI_StartVi(SAMPLE_VI_CONFIG_S* pstViConfig);
HI_S32 SAMPLE_COMM_VI_StopVi(SAMPLE_VI_CONFIG_S* pstViConfig);
HI_S32 SAMPLE_COMM_VI_UnBindVpss(SAMPLE_VI_MODE_E enViMode);
HI_S32 SAMPLE_COMM_VI_UnBindVenc(SAMPLE_VI_MODE_E enViMode);
HI_VOID SAMPLE_COMM_VI_ReadFrame(FILE * fp, HI_U8 * pY, HI_U8 * pU, HI_U8 * pV,
		HI_U32 width, HI_U32 height, HI_U32 stride, HI_U32 stride2);
HI_S32 SAMPLE_COMM_VI_PlanToSemi(HI_U8 *pY, HI_S32 yStride, HI_U8 *pU,
		HI_S32 uStride, HI_U8 *pV, HI_S32 vStride, HI_S32 picWidth,
		HI_S32 picHeight);
HI_S32 SAMPLE_COMM_VI_GetVFrameFromYUV(FILE *pYUVFile, HI_U32 u32Width,
		HI_U32 u32Height, HI_U32 u32Stride, VIDEO_FRAME_INFO_S *pstVFrameInfo);
HI_S32 SAMPLE_COMM_VI_ChangeCapSize(VI_CHN ViChn, HI_U32 u32CapWidth,
		HI_U32 u32CapHeight, HI_U32 u32Width, HI_U32 u32Height);

#endif /* SAMPLE_COMM_VI_H_ */
