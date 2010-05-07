#pragma once

#define DEFINE_GUID_FOURCC(FOURCC) \
 DEFINE_GUID(MEDIASUBTYPE_##FOURCC,FOURCC_##FOURCC, 0x0000, 0x0010, 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71);

#define DEFINE_GUID_WAVE(WAVE) \
 DEFINE_GUID(MEDIASUBTYPE_##WAVE,WAVE_FORMAT_##WAVE, 0x0000, 0x0010, 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71);

#define FOURCC_FFDS mmioFOURCC('F','F','D','S')
#define FOURCC_FVFW mmioFOURCC('F','V','F','W')
#define FOURCC_FMP4 mmioFOURCC('F','M','P','4')
#define FOURCC_XVID mmioFOURCC('X','V','I','D')
#define FOURCC_DIVX mmioFOURCC('D','I','V','X')
#define FOURCC_DIV3 mmioFOURCC('D','I','V','3')
#define FOURCC_DVX3 mmioFOURCC('D','V','X','3')
#define FOURCC_DX50 mmioFOURCC('D','X','5','0')
#define FOURCC_MPG4 mmioFOURCC('M','P','G','4')
#define FOURCC_MP41 mmioFOURCC('M','P','4','1')
#define FOURCC_MP42 mmioFOURCC('M','P','4','2')
#define FOURCC_MP43 mmioFOURCC('M','P','4','3')
#define FOURCC_H261 mmioFOURCC('H','2','6','1')
#define FOURCC_M261 mmioFOURCC('M','2','6','1')
#define FOURCC_H263 mmioFOURCC('H','2','6','3')
//#define FOURCC_I263 mmioFOURCC('I','2','6','3')
#define FOURCC_S263 mmioFOURCC('S','2','6','3')
#define FOURCC_L263 mmioFOURCC('L','2','6','3')
#define FOURCC_M263 mmioFOURCC('M','2','6','3')
#define FOURCC_U263 mmioFOURCC('U','2','6','3')
#define FOURCC_X263 mmioFOURCC('X','2','6','3')
#define FOURCC_H264 mmioFOURCC('H','2','6','4')
#define FOURCC_X264 mmioFOURCC('X','2','6','4')
#define FOURCC_h264 mmioFOURCC('h','2','6','4')
#define FOURCC_avc1 mmioFOURCC('a','v','c','1')
//#define FOURCC_L264 mmioFOURCC('L','2','6','4')
#define FOURCC_VSSH mmioFOURCC('V','S','S','H')
#define FOURCC_DAVC mmioFOURCC('D','A','V','C')
#define FOURCC_PAVC mmioFOURCC('P','A','V','C')
#define FOURCC_AVC1 mmioFOURCC('A','V','C','1')
//#define FOURCC_SVM2 mmioFOURCC('S','V','M','2')
#define FOURCC_BLZ0 mmioFOURCC('B','L','Z','0')
#define FOURCC_SMP4 mmioFOURCC('S','M','P','4')
#define FOURCC_DXGM mmioFOURCC('D','X','G','M')
#define FOURCC_WMV1 mmioFOURCC('W','M','V','1')
#define FOURCC_WMV2 mmioFOURCC('W','M','V','2')
#define FOURCC_WMV3 mmioFOURCC('W','M','V','3')
#define FOURCC_WVC1 mmioFOURCC('W','V','C','1')
#define FOURCC_WMVA mmioFOURCC('W','M','V','A')
#define FOURCC_WMVP mmioFOURCC('W','M','V','P')
#define FOURCC_WVP2 mmioFOURCC('W','V','P','2')
#define FOURCC_VP50 mmioFOURCC('V','P','5','0')
#define FOURCC_VP60 mmioFOURCC('V','P','6','0')
#define FOURCC_VP61 mmioFOURCC('V','P','6','1')
#define FOURCC_VP62 mmioFOURCC('V','P','6','2')
#define FOURCC_VP6F mmioFOURCC('V','P','6','F')
#define FOURCC_VP6A mmioFOURCC('V','P','6','A')
#define FOURCC_FLV4 mmioFOURCC('F','L','V','4')
#define FOURCC_CAVS mmioFOURCC('C','A','V','S')
#define FOURCC_MSS1 mmioFOURCC('M','S','S','1')
#define FOURCC_MSS2 mmioFOURCC('M','S','S','2')
#define FOURCC_MJPG mmioFOURCC('M','J','P','G')
#define FOURCC_LJPG mmioFOURCC('L','J','P','G')
#define FOURCC_MJLS mmioFOURCC('M','J','L','S')
#define FOURCC_AVRN mmioFOURCC('A','V','R','N')
#define FOURCC_MJPA mmioFOURCC('M','J','P','A')
#define FOURCC_DVSD mmioFOURCC('D','V','S','D')
#define FOURCC_DV25 mmioFOURCC('D','V','2','5')
#define FOURCC_DV50 mmioFOURCC('D','V','5','0')
#define FOURCC_CDVC mmioFOURCC('C','D','V','C')
#define FOURCC_CDV5 mmioFOURCC('C','D','V','5')
#define FOURCC_DVIS mmioFOURCC('D','V','I','S')
#define FOURCC_PDVC mmioFOURCC('P','D','V','C')
#define FOURCC_HFYU mmioFOURCC('H','F','Y','U')
#define FOURCC_FFVH mmioFOURCC('F','F','V','H')
#define FOURCC_CYUV mmioFOURCC('C','Y','U','V')
#define FOURCC_ASV1 mmioFOURCC('A','S','V','1')
#define FOURCC_ASV2 mmioFOURCC('A','S','V','2')
#define FOURCC_VCR1 mmioFOURCC('V','C','R','1')
#define FOURCC_FFV1 mmioFOURCC('F','F','V','1')
#define FOURCC_AVIS mmioFOURCC('A','V','I','S')
#define FOURCC_MPEG mmioFOURCC('M','P','E','G')
#define FOURCC_1001 0x10000001 // MPEG1 in AVI generated by mencoder
#define FOURCC_1002 0x10000002 // MPEG2 in AVI generated by mencoder
#define FOURCC_MPG1 mmioFOURCC('M','P','G','1')
#define FOURCC_MPG2 mmioFOURCC('M','P','G','2')
#define FOURCC_EM2V mmioFOURCC('E','M','2','V')
#define FOURCC_MMES mmioFOURCC('M','M','E','S')
#define FOURCC_DIV1 mmioFOURCC('D','I','V','1')
#define FOURCC_DIV2 mmioFOURCC('D','I','V','2')
#define FOURCC_DIV4 mmioFOURCC('D','I','V','4')
#define FOURCC_DIV5 mmioFOURCC('D','I','V','5')
#define FOURCC_DIV6 mmioFOURCC('D','I','V','6')
#define FOURCC_AP41 mmioFOURCC('A','P','4','1')
#define FOURCC_MPG3 mmioFOURCC('M','P','G','3')
#define FOURCC_MP4S mmioFOURCC('M','P','4','S')
#define FOURCC_SEDG mmioFOURCC('S','E','D','G')
#define FOURCC_MP4V mmioFOURCC('M','P','4','V')
#define FOURCC_M4S2 mmioFOURCC('M','4','S','2')
#define FOURCC_COL1 mmioFOURCC('C','O','L','1')
#define FOURCC_XVIX mmioFOURCC('X','V','I','X')
#define FOURCC_UMP4 mmioFOURCC('U','M','P','4')
#define FOURCC_3IV1 mmioFOURCC('3','I','V','1')
#define FOURCC_3IV2 mmioFOURCC('3','I','V','2')
#define FOURCC_3IVX mmioFOURCC('3','I','V','X')
#define FOURCC_NDIG mmioFOURCC('N','D','I','G')
#define FOURCC_LMP4 mmioFOURCC('L','M','P','4')
#define FOURCC_RMP4 mmioFOURCC('R','M','P','4')
#define FOURCC_DM4V mmioFOURCC('D','M','4','V')
#define FOURCC_HDX4 mmioFOURCC('H','D','X','4')
#define FOURCC_CRAM mmioFOURCC('C','R','A','M')
#define FOURCC_RT21 mmioFOURCC('R','T','2','1')
#define FOURCC_IV32 mmioFOURCC('I','V','3','2')
#define FOURCC_IV31 mmioFOURCC('I','V','3','1')
#define FOURCC_CVID mmioFOURCC('C','V','I','D')
#define FOURCC_MSZH mmioFOURCC('M','S','Z','H')
#define FOURCC_ZLIB mmioFOURCC('Z','L','I','B')
#define FOURCC_FLV1 mmioFOURCC('F','L','V','1')
#define FOURCC_8BPS mmioFOURCC('8','B','P','S')
#define FOURCC_PNG1 mmioFOURCC('P','N','G','1')
#define FOURCC_MPNG mmioFOURCC('M','P','N','G')
#define FOURCC_DUCK mmioFOURCC('D','U','C','K')
#define FOURCC_TM20 mmioFOURCC('T','M','2','0')
#define FOURCC_TSCC mmioFOURCC('T','S','C','C')
//#define FOURCC_SNOW mmioFOURCC('S','N','O','W')
#define FOURCC_QPEG mmioFOURCC('Q','P','E','G')
#define FOURCC_Q1_0 mmioFOURCC('Q','1','.','0')
#define FOURCC_Q1_1 mmioFOURCC('Q','1','.','1')
#define FOURCC_WV1F mmioFOURCC('W','V','1','F')
#define FOURCC_LOCO mmioFOURCC('L','O','C','O')
#define FOURCC_WNV1 mmioFOURCC('W','N','V','1')
#define FOURCC_CSCD mmioFOURCC('C','S','C','D')
#define FOURCC_ZMBV mmioFOURCC('Z','M','B','V')
#define FOURCC_ULTI mmioFOURCC('U','L','T','I')
#define FOURCC_VIXL mmioFOURCC('V','I','X','L')
#define FOURCC_AASC mmioFOURCC('A','A','S','C')
#define FOURCC_FPS1 mmioFOURCC('F','P','S','1')
#define FOURCC_AMVV mmioFOURCC('A','M','V','V')
#define FOURCC_SP5X mmioFOURCC('S','P','5','X')
#define FOURCC_SP51 mmioFOURCC('S','P','5','1')
#define FOURCC_SP52 mmioFOURCC('S','P','5','2')
#define FOURCC_SP53 mmioFOURCC('S','P','5','3')
#define FOURCC_SP54 mmioFOURCC('S','P','5','4')
#define FOURCC_SP55 mmioFOURCC('S','P','5','5')
#define FOURCC_SP56 mmioFOURCC('S','P','5','6')
#define FOURCC_SP57 mmioFOURCC('S','P','5','7')
#define FOURCC_RLE4 BI_RLE4
#define FOURCC_RLE8 BI_RLE8
#define FOURCC_BITFIELDS 3

//H.264/AVC
DEFINE_GUID_FOURCC(H264)
DEFINE_GUID_FOURCC(h264)
DEFINE_GUID_FOURCC(AVC1)
DEFINE_GUID_FOURCC(avc1)
#define FOURCC_H264_HAALI 0x31564343
DEFINE_GUID_FOURCC(H264_HAALI)
DEFINE_GUID(H264_HAALI_CUSTOM, 0x31564343, 0x0000, 0x0010, 0x80, 0x00, 0x00, 0xAA, 0x00, 0x38, 0x9B, 0x71);

static __inline bool isH264_mediatype(GUID subtype) {return (subtype == MEDIASUBTYPE_H264 || subtype == MEDIASUBTYPE_h264 || subtype == MEDIASUBTYPE_AVC1 || subtype == MEDIASUBTYPE_avc1 || subtype == MEDIASUBTYPE_H264_HAALI || subtype == H264_HAALI_CUSTOM);}

//theora
#define FOURCC_THEO mmioFOURCC('T','H','E','O')
#define FOURCC_VP31 mmioFOURCC('V','P','3','1')
DEFINE_GUID(FORMAT_TheoraIll, 0xa99f116c, 0xdffa, 0x412c, 0x95, 0xde, 0x72, 0x5f, 0x99, 0x87, 0x48, 0x26);
DEFINE_GUID(MEDIASUBTYPE_RLTheora, 0xd124b2b1, 0x8968, 0x4ae8, 0xb2, 0x88, 0xfe, 0x16, 0xea, 0x34, 0xb0, 0xce);
DEFINE_GUID(FORMAT_RLTheora , 0xe69b30d1, 0x7d65, 0x4166, 0xb9, 0x90, 0x10, 0x3d, 0xa8, 0xc9, 0x11, 0xe3 );
//31564343-0000-0010-8000-00AA00389B71 : Haali custom media type

//quicktime
#define FOURCC_JPEG mmioFOURCC('J','P','E','G')
#define FOURCC_SVQ1 mmioFOURCC('S','V','Q','1')
#define FOURCC_SVQ3 mmioFOURCC('S','V','Q','3')
#define FOURCC_QRLE mmioFOURCC('Q','R','L','E')
#define FOURCC_RPZA mmioFOURCC('R','P','Z','A')

//real
#define FOURCC_RV10 mmioFOURCC('R','V','1','0')
#define FOURCC_RV20 mmioFOURCC('R','V','2','0')
#define FOURCC_RV30 mmioFOURCC('R','V','3','0')
#define FOURCC_RV40 mmioFOURCC('R','V','4','0')

//uncompressed
#define FOURCC_YUY2 mmioFOURCC('Y','U','Y','2')
#define FOURCC_V422 mmioFOURCC('V','4','2','2')
#define FOURCC_YV12 mmioFOURCC('Y','V','1','2')
#define FOURCC_YVYU mmioFOURCC('Y','V','Y','U')
#define FOURCC_UYVY mmioFOURCC('U','Y','V','Y')
#define FOURCC_YUYV mmioFOURCC('Y','U','Y','V')
#define FOURCC_VYUY mmioFOURCC('V','Y','U','Y')
#define FOURCC_I420 mmioFOURCC('I','4','2','0')
#define FOURCC_IYUV mmioFOURCC('I','Y','U','V')
#define FOURCC_444P mmioFOURCC('4','4','4','P')
#define FOURCC_YV24 mmioFOURCC('Y','V','2','4') // YUV 4:4:4
#define FOURCC_422P mmioFOURCC('4','2','2','P')
#define FOURCC_YV16 mmioFOURCC('Y','V','1','6') // YUV 4:2:2
#define FOURCC_411P mmioFOURCC('4','1','1','P')
#define FOURCC_Y41B mmioFOURCC('Y','4','1','B') // YUV 4:1:1
#define FOURCC_410P mmioFOURCC('4','1','0','P')
#define FOURCC_PAL1 mmioFOURCC('P','A','L','1')
#define FOURCC_PAL4 mmioFOURCC('P','A','L','4')
#define FOURCC_PAL8 mmioFOURCC('P','A','L','8')
#define FOURCC_RGB2 mmioFOURCC('R','G','B','2')
#define FOURCC_RGB3 mmioFOURCC('R','G','B','3')
#define FOURCC_RGB5 mmioFOURCC('R','G','B','5')
#define FOURCC_RGB6 mmioFOURCC('R','G','B','6')
#define FOURCC_CLJR mmioFOURCC('C','L','J','R')
#define FOURCC_Y800 mmioFOURCC('Y','8','0','0')
#define FOURCC_NV12 mmioFOURCC('N','V','1','2')
#define FOURCC_NV21 mmioFOURCC('N','V','2','1')

DEFINE_GUID_FOURCC(I420)
DEFINE_GUID_FOURCC(422P)
DEFINE_GUID_FOURCC(444P)
DEFINE_GUID_FOURCC(411P)
DEFINE_GUID_FOURCC(410P)
DEFINE_GUID_FOURCC(VYUY)
DEFINE_GUID_FOURCC(Y800)
DEFINE_GUID_FOURCC(NV12)
DEFINE_GUID_FOURCC(NV21)
DEFINE_GUID_FOURCC(YV16)

#define FOURCC_MASK_ALL 1
#define FOURCC_MASK_YUV 2
#define FOURCC_MASK_RGB 3
#define FOURCC_MASK_PAL 4

//audio
#define WAVE_FORMAT_WMA7    0x160
#define WAVE_FORMAT_WMA8    0x161
//#define WAVE_FORMAT_DIVXWMA 0x353
#define WAVE_FORMAT_AC3_W   0x2000
#define WAVE_FORMAT_DTS_W   0x2001
#define WAVE_FORMAT_AAC1    0xAAC0
#define WAVE_FORMAT_AAC2    0x00FF
#define WAVE_FORMAT_AAC3    mmioFOURCC('M','P','4','A')
#define WAVE_FORMAT_AAC4    0x706D
#define WAVE_FORMAT_AAC5    mmioFOURCC('m','p','4','a')
#define WAVE_FORMAT_AVIS    0x3313
#define WAVE_FORMAT_AMR     0xFE
#define WAVE_FORMAT_SAMR    mmioFOURCC('s','a','m','r')
#define WAVE_FORMAT_IMA_DK3 0x62
#define WAVE_FORMAT_IMA_WAV 0x11
#define WAVE_FORMAT_IMA_DK4 0x61
#define WAVE_FORMAT_IMA4    mmioFOURCC('i','m','a','4')
#define WAVE_FORMAT_G726    0x45
#define WAVE_FORMAT_TTA     0x77a1
#define WAVE_FORMAT_VORBIS1  ((WORD)'O'+((WORD)'g'<<8)) // 0x674f("Og") ... Original stream compatible
#define WAVE_FORMAT_VORBIS2  ((WORD)'P'+((WORD)'g'<<8)) // 0x6750("Pg") ... Have independent header
#define WAVE_FORMAT_VORBIS3  ((WORD)'Q'+((WORD)'g'<<8)) // 0x6751("Qg") ... Have no codebook header
#define WAVE_FORMAT_VORBIS1P ((WORD)'o'+((WORD)'g'<<8)) // 0x676f("og") ... Original stream compatible
#define WAVE_FORMAT_VORBIS2P ((WORD)'p'+((WORD)'g'<<8)) // 0x6770("pg") ... Have independent header
#define WAVE_FORMAT_VORBIS3P ((WORD)'q'+((WORD)'g'<<8)) // 0x6771("qg") ... Have no codebook header
#define WAVE_FORMAT_FFVORBIS (('V'<<8)+'o')
#define WAVE_FORMAT_QT_ULAW 0x6c75
#define WAVE_FORMAT_alaw    mmioFOURCC('a','l','a','w')
#define WAVE_FORMAT_ulaw    mmioFOURCC('u','l','a','w')
#define WAVE_FORMAT_ULAW    mmioFOURCC('U','L','A','W')
#define WAVE_FORMAT_LPCM    mmioFOURCC('l','p','c','m')
#define WAVE_FORMAT_RAW     mmioFOURCC('r','a','w',' ')
#define WAVE_FORMAT_qdm2    mmioFOURCC('q','d','m','2')
#define WAVE_FORMAT_QDM2    mmioFOURCC('Q','D','M','2')
#define WAVE_FORMAT_sowt    mmioFOURCC('s','o','w','t')
#define WAVE_FORMAT_SOWT    mmioFOURCC('S','O','W','T')
#define WAVE_FORMAT_twos    mmioFOURCC('t','w','o','s')
#define WAVE_FORMAT_TWOS    mmioFOURCC('T','W','O','S')
#define WAVE_FORMAT_IN32    mmioFOURCC('I','N','3','2')
#define WAVE_FORMAT_in32    mmioFOURCC('i','n','3','2')
#define WAVE_FORMAT_IN24    mmioFOURCC('I','N','2','4')
#define WAVE_FORMAT_in24    mmioFOURCC('i','n','2','4')
#define WAVE_FORMAT_FL32    mmioFOURCC('F','L','3','2')
#define WAVE_FORMAT_fl32    mmioFOURCC('f','l','3','2')
#define WAVE_FORMAT_FL64    mmioFOURCC('F','L','6','4')
#define WAVE_FORMAT_fl64    mmioFOURCC('f','l','6','4')
#define WAVE_FORMAT_MAC3    mmioFOURCC('M','A','C','3')
#define WAVE_FORMAT_MAC6    mmioFOURCC('M','A','C','6')
#define WAVE_FORMAT_QT_GSM  0x6761
#define WAVE_FORMAT_COOK1   0x2004
#define WAVE_FORMAT_COOK2   mmioFOURCC('C','O','O','K')
#define WAVE_FORMAT_IMC     0x401
#define WAVE_FORMAT_ATRAC3  0x270
#define WAVE_FORMAT_NELLYMOSER  mmioFOURCC('N','E','L','L')
#define WAVE_FORMAT_WAVPACK 0x5756
#define WAVE_FORMAT_PCM8    0x9a120008
#define WAVE_FORMAT_PCM16   0x9a120016
#define WAVE_FORMAT_PCM24   0x9a120024
#define WAVE_FORMAT_PCM32   0x9a120032
#define WAVE_FORMAT_FLOAT32 0x9a120132
#define WAVE_FORMAT_FLOAT64 0x9a120164
#define WAVE_FORMAT_IMA_AMV   mmioFOURCC('A','M','V','A')
#define WAVE_FORMAT_ADPCM_SWF mmioFOURCC('A','S','W','F')
#define WAVE_FORMAT_EAC3      mmioFOURCC('E','A','C','3')
#define WAVE_FORMAT_MLP       mmioFOURCC('M','L','P',' ')
#define WAVE_FORMAT_DTS_HD    mmioFOURCC('D','T','S','H')
#define WAVE_FORMAT_TRUEHD    mmioFOURCC('T','R','U','E')
#define WAVE_FORMAT_CYBERLINK_TRUEHD 49155
#define WAVE_FORMAT_CYBERLINK_DTS_HD 49156


DEFINE_GUID_WAVE(WMA7)
DEFINE_GUID_WAVE(WMA8)
//DEFINE_GUID_WAVE(DIVXWMA)
DEFINE_GUID(MEDIASUBTYPE_MP3, WAVE_FORMAT_MPEGLAYER3, 0x0000, 0x0010, 0x80, 0x00, 0x00, 0xAA, 0x00, 0x38, 0x9B, 0x71);
DEFINE_GUID_WAVE(AC3_W)
DEFINE_GUID_WAVE(DTS_W)
DEFINE_GUID_WAVE(AAC1)
DEFINE_GUID_WAVE(AAC2)
DEFINE_GUID_WAVE(AAC3)
DEFINE_GUID_WAVE(AAC4)
DEFINE_GUID_WAVE(AAC5)
DEFINE_GUID_WAVE(AMR)
DEFINE_GUID_WAVE(SAMR)
DEFINE_GUID_WAVE(IMA_DK3)
DEFINE_GUID_WAVE(IMA_WAV)
DEFINE_GUID_WAVE(IMA_DK4)
DEFINE_GUID_WAVE(IMA4)
DEFINE_GUID_WAVE(G726)
DEFINE_GUID(MEDIASUBTYPE_MSADPCM, WAVE_FORMAT_ADPCM, 0x0000, 0x0010, 0x80, 0x00, 0x00, 0xAA, 0x00, 0x38, 0x9B, 0x71);
DEFINE_GUID(MEDIASUBTYPE_CREATIVE_ADPCM, WAVE_FORMAT_CREATIVE_ADPCM, 0x0000, 0x0010, 0x80, 0x00, 0x00, 0xAA, 0x00, 0x38, 0x9B, 0x71);
DEFINE_GUID(MEDIASUBTYPE_YAMAHA_ADPCM, WAVE_FORMAT_YAMAHA_ADPCM, 0x0000, 0x0010, 0x80, 0x00, 0x00, 0xAA, 0x00, 0x38, 0x9B, 0x71);
DEFINE_GUID_WAVE(alaw)
DEFINE_GUID_WAVE(ALAW)
DEFINE_GUID_WAVE(ulaw)
DEFINE_GUID_WAVE(ULAW)
DEFINE_GUID_WAVE(MULAW)
DEFINE_GUID_WAVE(QT_ULAW)
DEFINE_GUID_WAVE(GSM610)
DEFINE_GUID_WAVE(FLAC)
DEFINE_GUID(MEDIASUBTYPE_FLAC2, 0x1541C5C0, 0xCDDF, 0x477D, 0xBC, 0x0A, 0x86, 0xF8, 0xAE, 0x7F, 0x83, 0x54);
DEFINE_GUID_WAVE(TTA)
DEFINE_GUID_WAVE(VORBIS1)
DEFINE_GUID_WAVE(VORBIS2)
DEFINE_GUID_WAVE(VORBIS3)
DEFINE_GUID_WAVE(VORBIS1P)
DEFINE_GUID_WAVE(VORBIS2P)
DEFINE_GUID_WAVE(VORBIS3P)
DEFINE_GUID_WAVE(FFVORBIS)
DEFINE_GUID_WAVE(RAW)
DEFINE_GUID_WAVE(AVIS)
DEFINE_GUID_WAVE(qdm2)
DEFINE_GUID_WAVE(QDM2)
DEFINE_GUID_WAVE(sowt)
DEFINE_GUID_WAVE(SOWT)
DEFINE_GUID_WAVE(twos)
DEFINE_GUID_WAVE(TWOS)
DEFINE_GUID_WAVE(in32)
DEFINE_GUID_WAVE(IN32)
DEFINE_GUID_WAVE(in24)
DEFINE_GUID_WAVE(IN24)
DEFINE_GUID_WAVE(fl32)
DEFINE_GUID_WAVE(FL32)
DEFINE_GUID_WAVE(fl64)
DEFINE_GUID_WAVE(FL64)
DEFINE_GUID_WAVE(MAC3)
DEFINE_GUID_WAVE(MAC6)
DEFINE_GUID_WAVE(QT_GSM)
DEFINE_GUID_WAVE(DSPGROUP_TRUESPEECH)
DEFINE_GUID_WAVE(14_4)
DEFINE_GUID_WAVE(28_8)
DEFINE_GUID_WAVE(IMC)
DEFINE_GUID_WAVE(ATRAC3)
DEFINE_GUID_WAVE(IMA_AMV)
DEFINE_GUID_WAVE(NELLYMOSER)
DEFINE_GUID_WAVE(WAVPACK)
DEFINE_GUID_WAVE(ADPCM_SWF)
DEFINE_GUID_WAVE(MLP)
DEFINE_GUID_WAVE(EAC3)
DEFINE_GUID_WAVE(COOK1)
DEFINE_GUID_WAVE(COOK2)

// vorbis/tremor/illiminable
#define WAVE_FORMAT_VORBIS 0xcddca2d5
DEFINE_GUID(FORMAT_VorbisFormat         ,0x6bddfa7e, 0x9f22, 0x46a9, 0xab, 0x5e, 0x88, 0x4e, 0xff, 0x29, 0x4d, 0x9f);
DEFINE_GUID(FORMAT_VorbisFormat2        ,0xb36e107f, 0xa938, 0x4387, 0x93, 0xc7, 0x55, 0xe9, 0x66, 0x75, 0x74, 0x73);
DEFINE_GUID(FORMAT_VorbisFormatIll      ,0x44e04f43, 0x58b3, 0x4de1, 0x9b, 0xaa, 0x89, 0x01, 0xf8, 0x52, 0xda, 0xe4);
DEFINE_GUID(MEDIASUBTYPE_Vorbis         ,0xcddca2d5, 0x6d75, 0x4f98, 0x84, 0x0e, 0x73, 0x7b, 0xed, 0xd5, 0xc6, 0x3b);
DEFINE_GUID(MEDIASUBTYPE_Vorbis2        ,0x8d2fd10b, 0x5841, 0x4a6b, 0x89, 0x05, 0x58, 0x8f, 0xec, 0x1a, 0xde, 0xd9);
DEFINE_GUID(MEDIASUBTYPE_VorbisIll      ,0x8a0566ac, 0x42b3, 0x4ad9, 0xac, 0xa3, 0x93, 0xb9, 0x06, 0xdd, 0xf9, 0x8a);
DEFINE_GUID(MEDIASUBTYPE_H264_TRANSPORT ,0x8d2d71cb, 0x243f, 0x45e3, 0xb2, 0xd8, 0x5f, 0xd7, 0x96, 0x7e, 0xc0, 0x9b);

DEFINE_GUID(IID_IGraphBuilder           ,0x56a868a9, 0x0ad4, 0x11ce, 0xb0, 0x3a, 0x00, 0x20, 0xaf, 0x0b, 0xa7, 0x70);
DEFINE_GUID(CLSID_AVIDec                ,0xcf49d4e0, 0x1115, 0x11ce, 0xb0, 0x3a, 0x00, 0x20, 0xaf, 0x0b, 0xa7, 0x70);
DEFINE_GUID(CLSID_EnhancedVideoRenderer ,0xfa10746c, 0x9b63, 0x4b6c, 0xbc, 0x49, 0xfc, 0x30, 0x0e, 0xa5, 0xf2, 0x56);
DEFINE_GUID(CLSID_VideoMixingRenderer9  ,0x51b4abf3, 0x748f, 0x4e3b, 0xa2, 0x76, 0xc8, 0x28, 0x33, 0x0e, 0x92, 0x6a);
DEFINE_GUID(CLSID_DirectVobSubFilter    ,0x93a22e7a, 0x5091, 0x45ef, 0xba, 0x61, 0x6d, 0xa2, 0x61, 0x56, 0xa5, 0xd0);
DEFINE_GUID(CLSID_DirectVobSubFilter2   ,0x9852a670, 0xf845, 0x491b, 0x9b, 0xe6, 0xeb, 0xd8, 0x41, 0xb8, 0xa6, 0x13);
DEFINE_GUID(CLSID_HaaliVideoRenderer    ,0x760a8f35, 0x97e7, 0x479d, 0xaa, 0xf5, 0xda, 0x9e, 0xff, 0x95, 0xd7, 0x51);
DEFINE_GUID(CLSID_HaaliMediaSplitter    ,0x55da30fc, 0xf16b, 0x49fc, 0xba, 0xa5, 0xae, 0x59, 0xfc, 0x65, 0xf8, 0x2d);
DEFINE_GUID(MEDIASUBTYPE_SVCD_SUBPICTURE,0xda5b82ee, 0x6bd2, 0x426f, 0xbf, 0x1e, 0x30, 0x11, 0x2d, 0xa7, 0x8a, 0xe1);
DEFINE_GUID(MEDIASUBTYPE_CVD_SUBPICTURE ,0x7b57308f, 0x5154, 0x4c36, 0xb9, 0x03, 0x52, 0xfe, 0x76, 0xe1, 0x84, 0xfc);
DEFINE_GUID(CLSID_MPC_MatroskaSplitter  ,0x0a68c3b5, 0x9164, 0x4a54, 0xaf, 0xaf, 0x99, 0x5b, 0x2f, 0xf0, 0xe0, 0xd4);
DEFINE_GUID(CLSID_MPC_MpegSourceFilter  ,0x1365be7a ,0xc86a, 0x473c, 0x9a, 0x41, 0xc0, 0xa6, 0xe8, 0x2c, 0x9f, 0xa3);
DEFINE_GUID(CLSID_MPC_MpegSplitterFilter,0xdc257063, 0x045f, 0x4be2 ,0xbd ,0x5b ,0xe1 ,0x22 ,0x79 ,0xc4 ,0x64 ,0xf0);
DEFINE_GUID(CLSID_GabestMatroskaSplitter,0x149d2e01, 0xc32e, 0x4939, 0x80, 0xf6, 0xc0, 0x7b, 0x81, 0x01, 0x5a, 0x7a);
DEFINE_GUID(CLSID_DVBSourceFilter       ,0xd8c561de, 0x1a6c, 0x4f15, 0xbe, 0x71, 0x29, 0x47, 0xdb, 0xe2, 0x64, 0x19);
DEFINE_GUID(CLSID_NeuviewSource         ,0xe69f911e, 0x571d, 0x4d54, 0xb4, 0x7b, 0xf2, 0x4c, 0x67, 0xb3, 0x78, 0x97);

DEFINE_GUID(CLSID_InfTee                ,0xf8388a40, 0xd5bb, 0x11d0, 0xbe, 0x5a, 0x00, 0x80, 0xc7, 0x06, 0x56, 0x8e);
DEFINE_GUID(CLSID_SmartT                ,0xCC58E280, 0x8AA1, 0x11D1, 0xB3, 0xF1, 0x00, 0xAA, 0x00, 0x37, 0x61, 0xC5);
DEFINE_GUID(CLSID_DecklinkVideoRenderFilter ,0xCEB13CC8,0x3591,0x45a5,0xBA,0x0F, 0x20, 0xE9, 0xA1, 0xD7, 0x2F, 0x76);
DEFINE_GUID(CLSID_WMP_VIDEODSP_DMO      ,0xaa20215c, 0xb047, 0x4702 ,0xba, 0x13, 0x57, 0x37, 0x61, 0x13, 0xaa, 0xd0);
DEFINE_GUID(CLSID_PBDA_DTFilter         ,0x09144FD6, 0xBB29, 0x11DB ,0x96, 0xF1, 0x00, 0x50, 0x56, 0xC0, 0x00, 0x08);

DEFINE_GUID(MEDIASUBTYPE_NERO_MLP       ,0x1e889be7, 0xb276, 0x4064, 0x9a, 0x39, 0x16, 0x0a, 0x06, 0x89, 0x5b, 0x52);
DEFINE_GUID(MEDIASUBTYPE_ARCSOFT_MLP    ,0x4288b843, 0x610b, 0x4e15, 0xa5, 0x3b, 0x43, 0x00, 0x7f, 0xcf, 0xf6, 0x14);
DEFINE_GUID(MEDIASUBTYPE_SONIC_MLP      ,0x4094a857, 0x7891, 0x44ac, 0x92, 0xb5, 0xc1, 0xcf, 0xf3, 0x7a, 0xf2, 0xe7);
DEFINE_GUID(MEDIASUBTYPE_ARCSOFT_DDPLUS ,0x71cfa727, 0x37e4, 0x404a, 0xae, 0xc0, 0x34, 0x84, 0x25, 0x32, 0xef, 0xf7);
DEFINE_GUID(MEDIASUBTYPE_ARCSOFT_DTSHD  ,0xf6498f57, 0xb399, 0x4a43, 0xa6, 0xfa, 0xf6, 0x94, 0xad, 0x42, 0xb9, 0xbe);
DEFINE_GUID(MEDIASUBTYPE_CYBERLINK_BITSTREAM,0x6AD2A952, 0x9979, 0x4DC4, 0xB6, 0xE1, 0x6F, 0x3C, 0x31, 0x37, 0xB3, 0x42);
DEFINE_GUID(MEDIASUBTYPE_DOLBY_DDPLUS   ,0xa7fb87af, 0x2d02, 0x42fb, 0xa4, 0xd4, 0x5,  0xcd, 0x93, 0x84, 0x3b, 0xdd);
DEFINE_GUID(MEDIASUBTYPE_DOLBY_TRUEHD   ,0xeb27cec4, 0x163e, 0x4ca3, 0x8b, 0x74, 0x8e, 0x25, 0xf9, 0x1b, 0x51, 0x7e);
DEFINE_GUID(MEDIASUBTYPE_DTS_HD         ,0xa2e58eb7, 0xfa9,  0x48bb, 0xa4, 0xc,  0xfa, 0xe,  0x15, 0x6d, 0x06, 0x45);
DEFINE_GUID(MEDIASUBTYPE_HDMV_LPCM_AUDIO,0x949f97fd, 0x56f6, 0x4527, 0xb4, 0xae, 0xdd, 0xeb, 0x37, 0x5a, 0xb8, 0x0f);
DEFINE_GUID(AM_KSPROPSETID_TSRateChange ,0xa503c5c0, 0x1d1d, 0x11d1, 0xad, 0x80, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00);


DEFINE_GUID(MEDIASUBTYPE_DOLBY_AC3_SPDIF, 0x00000092, 0x0000, 0x0010, 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71);

// Define the GUIDS for Windows SDK < V7.0
#ifndef KSDATAFORMAT_SUBTYPE_IEC61937_DOLBY_MLP
// Windows 7 GUIDs for WAVEFORMATEXTENSIBLE IEC61937 structure 

// Dolby digital
#define KSDATAFORMAT_SUBTYPE_IEC61937_DOLBY_DIGITAL MEDIASUBTYPE_DOLBY_AC3_SPDIF
//Advanced Audio Coding (MPEG-2/4 AAC in ADTS)
DEFINE_GUID(KSDATAFORMAT_SUBTYPE_IEC61937_AAC, 0x00000006, 0x0cea, 0x0010, 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71);
//DTS
DEFINE_GUID(KSDATAFORMAT_SUBTYPE_IEC61937_DTS, 0x00000008, 0x0cea, 0x0010, 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71);
//Dolby Digital Plus (EAC3)
DEFINE_GUID(KSDATAFORMAT_SUBTYPE_IEC61937_DOLBY_DIGITAL_PLUS, 0x0000000a, 0x0cea, 0x0010, 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71);
//DTS-HD (24-bit, 96Khz)
DEFINE_GUID(KSDATAFORMAT_SUBTYPE_IEC61937_DTS_HD, 0x0000000b, 0x0cea, 0x0010, 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71);
//MAT(MLP)� Meridian Lossless Packing (Dolby Digital True HD � 24-bit 196KHz/up to 18M bps, 8 channels)
DEFINE_GUID(KSDATAFORMAT_SUBTYPE_IEC61937_DOLBY_MLP, 0x0000000c, 0x0cea, 0x0010, 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71);
//Windows Media Audio (WMA) Pro
DEFINE_GUID(KSDATAFORMAT_SUBTYPE_IEC61937_WMA_PRO, 0x00000164, 0x0000, 0x0010, 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71);

#if !defined( STATIC_KSDATAFORMAT_SUBTYPE_WAVEFORMATEX )
DEFINE_GUID(KSDATAFORMAT_SUBTYPE_WAVEFORMATEX, 0x00000000, 0x0000, 0x0010, 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71);
#endif

#define SPEAKER_FRONT_LEFT              0x1
#define SPEAKER_FRONT_RIGHT             0x2
#define SPEAKER_FRONT_CENTER            0x4
#define SPEAKER_LOW_FREQUENCY           0x8
#define SPEAKER_BACK_LEFT               0x10
#define SPEAKER_BACK_RIGHT              0x20
#define SPEAKER_FRONT_LEFT_OF_CENTER    0x40
#define SPEAKER_FRONT_RIGHT_OF_CENTER   0x80
#define SPEAKER_BACK_CENTER             0x100
#define SPEAKER_SIDE_LEFT               0x200
#define SPEAKER_SIDE_RIGHT              0x400
#define SPEAKER_TOP_CENTER              0x800
#define SPEAKER_TOP_FRONT_LEFT          0x1000
#define SPEAKER_TOP_FRONT_CENTER        0x2000
#define SPEAKER_TOP_FRONT_RIGHT         0x4000
#define SPEAKER_TOP_BACK_LEFT           0x8000
#define SPEAKER_TOP_BACK_CENTER         0x10000
#define SPEAKER_TOP_BACK_RIGHT          0x20000


#define KSAUDIO_SPEAKER_5POINT1         (SPEAKER_FRONT_LEFT | SPEAKER_FRONT_RIGHT | \
                                         SPEAKER_FRONT_CENTER | SPEAKER_LOW_FREQUENCY | \
                                         SPEAKER_BACK_LEFT  | SPEAKER_BACK_RIGHT)
#define KSAUDIO_SPEAKER_7POINT1         (SPEAKER_FRONT_LEFT | SPEAKER_FRONT_RIGHT | \
                                         SPEAKER_FRONT_CENTER | SPEAKER_LOW_FREQUENCY | \
                                         SPEAKER_BACK_LEFT | SPEAKER_BACK_RIGHT | \
                                         SPEAKER_FRONT_LEFT_OF_CENTER | SPEAKER_FRONT_RIGHT_OF_CENTER)
#endif

// Additionnal DXVA GUIDs
// Intel ClearVideo VC1 bitstream decoder
DEFINE_GUID(DXVA_Intel_VC1_ClearVideo, 0xBCC5DB6D, 0xA2B6,0x4AF0,0xAC,0xE4,0xAD,0xB1,0xF7,0x87,0xBC,0x89);

// Intel ClearVideo H264 bitstream decoder
DEFINE_GUID(DXVA_Intel_H264_ClearVideo, 0x604F8E68, 0x4951,0x4C54,0x88,0xFE,0xAB,0xD2,0x5C,0x15,0xB3,0xD6);

//AE7EC2A2-1913-4a80-8DD6-DF1497ABA494
DEFINE_GUID(IID_IFFDSDXVA2Sample, 0xAE7EC2A2, 0x1913, 0x4a80, 0x8D, 0xD6, 0xDF, 0x14, 0x97, 0xAB, 0xA4, 0x94);
DEFINE_GUID(IID_IDirect3DDeviceManager9,          0xa0cade0f,0x06d5,0x4cf4,0xa1,0xc7,0xf3,0xcd,0xd7,0x25,0xaa,0x75);
DEFINE_GUID(IID_IDirectXVideoAccelerationService, 0xfc51a550,0xd5e7,0x11d9,0xaf,0x55,0x00,0x05,0x4e,0x43,0xff,0x02);

DEFINE_GUID(DXVA_ModeMPEG2_A, 0x1b81be0A, 0xa0c7,0x11d3,0xb9,0x84,0x00,0xc0,0x4f,0x2e,0x73,0xc5);
DEFINE_GUID(DXVA_ModeMPEG2_B, 0x1b81be0B, 0xa0c7,0x11d3,0xb9,0x84,0x00,0xc0,0x4f,0x2e,0x73,0xc5);
DEFINE_GUID(DXVA_ModeMPEG2_C, 0x1b81be0C, 0xa0c7,0x11d3,0xb9,0x84,0x00,0xc0,0x4f,0x2e,0x73,0xc5);
DEFINE_GUID(DXVA_ModeMPEG2_D, 0x1b81be0D, 0xa0c7,0x11d3,0xb9,0x84,0x00,0xc0,0x4f,0x2e,0x73,0xc5);

DEFINE_GUID(DXVA_ModeH264_A,  0x1b81be64, 0xa0c7,0x11d3,0xb9,0x84,0x00,0xc0,0x4f,0x2e,0x73,0xc5);
DEFINE_GUID(DXVA_ModeH264_B,  0x1b81be65, 0xa0c7,0x11d3,0xb9,0x84,0x00,0xc0,0x4f,0x2e,0x73,0xc5);
DEFINE_GUID(DXVA_ModeH264_C,  0x1b81be66, 0xa0c7,0x11d3,0xb9,0x84,0x00,0xc0,0x4f,0x2e,0x73,0xc5);
DEFINE_GUID(DXVA_ModeH264_D,  0x1b81be67, 0xa0c7,0x11d3,0xb9,0x84,0x00,0xc0,0x4f,0x2e,0x73,0xc5);
DEFINE_GUID(DXVA_ModeH264_E,  0x1b81be68, 0xa0c7,0x11d3,0xb9,0x84,0x00,0xc0,0x4f,0x2e,0x73,0xc5);
DEFINE_GUID(DXVA_ModeH264_F,  0x1b81be69, 0xa0c7,0x11d3,0xb9,0x84,0x00,0xc0,0x4f,0x2e,0x73,0xc5);

DEFINE_GUID(DXVA2_ModeH264_A,  0x1b81be64, 0xa0c7,0x11d3,0xb9,0x84,0x00,0xc0,0x4f,0x2e,0x73,0xc5);
DEFINE_GUID(DXVA2_ModeH264_B,  0x1b81be65, 0xa0c7,0x11d3,0xb9,0x84,0x00,0xc0,0x4f,0x2e,0x73,0xc5);
DEFINE_GUID(DXVA2_ModeH264_C,  0x1b81be66, 0xa0c7,0x11d3,0xb9,0x84,0x00,0xc0,0x4f,0x2e,0x73,0xc5);
DEFINE_GUID(DXVA2_ModeH264_D,  0x1b81be67, 0xa0c7,0x11d3,0xb9,0x84,0x00,0xc0,0x4f,0x2e,0x73,0xc5);
DEFINE_GUID(DXVA2_ModeH264_E,  0x1b81be68, 0xa0c7,0x11d3,0xb9,0x84,0x00,0xc0,0x4f,0x2e,0x73,0xc5);
DEFINE_GUID(DXVA2_ModeH264_F,  0x1b81be69, 0xa0c7,0x11d3,0xb9,0x84,0x00,0xc0,0x4f,0x2e,0x73,0xc5);

DEFINE_GUID(DXVA2_ModeVC1_A,   0x1b81beA0, 0xa0c7,0x11d3,0xb9,0x84,0x00,0xc0,0x4f,0x2e,0x73,0xc5);
DEFINE_GUID(DXVA2_ModeVC1_B,   0x1b81beA1, 0xa0c7,0x11d3,0xb9,0x84,0x00,0xc0,0x4f,0x2e,0x73,0xc5);
DEFINE_GUID(DXVA2_ModeVC1_C,   0x1b81beA2, 0xa0c7,0x11d3,0xb9,0x84,0x00,0xc0,0x4f,0x2e,0x73,0xc5);
DEFINE_GUID(DXVA2_ModeVC1_D,   0x1b81beA3, 0xa0c7,0x11d3,0xb9,0x84,0x00,0xc0,0x4f,0x2e,0x73,0xc5);

DEFINE_GUID(DXVA_NoEncrypt,   0x1b81beD0, 0xa0c7,0x11d3,0xb9,0x84,0x00,0xc0,0x4f,0x2e,0x73,0xc5);

