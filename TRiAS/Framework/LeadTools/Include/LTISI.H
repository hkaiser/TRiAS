/*
   LTISI.H - LEAD ISIS module header file
   Copyright (c) 1991-2000 LEAD Technologies, Inc.
   All Rights Reserved.
*/

#ifndef _LTISI_H_
#define _LTISI_H_

#include "ltkrn.h"
//#include "ltimg.h"
//#include "ltfil.h"

#define _HEADER_ENTRY_
#include "ltpck.h"
//#include <stdlib.h>

/* callback typedefs */
/* ISIS Multipage Callback */
typedef L_INT (pEXT_CALLBACK ISISCALLBACK) (pBITMAPHANDLE, L_INT32, L_CHAR L_FAR*, L_VOID L_FAR*);

/* flags for L_ISISAcquireXXX */
#define ISIS_SHOWUI       0x0001  /* show ISIS UI */
#define ISIS_MULTI_NOSAVE 0x0002  /* do not save files */

#define ISIS_DEFAULT_DIGITS 4

/* default ISIS TAG VALUE */
#define ISIS_DEFAULT  -99

/* supported ISIS TAGS and possible values */
/* long tags */
#ifndef TAG_XRESOLUTION

#define TAG_XRESOLUTION                 0x011A
#define TAG_YRESOLUTION                 0x011B
#define TAG_XPOSITION                   0x011E
#define TAG_YPOSITION                   0x011F
#define TAG_IMAGELENGTH                 0x0101
#define TAG_IMAGEWIDTH                  0x0100

#define TAG_FEEDER                      0x0503
#define     TAG_FEEDER_FEED                 0x00000001L
#define     TAG_FEEDER_FLAT                 0x00000002L
#define     TAG_FEEDER_MANUAL               0x00000004L
#define     TAG_FEEDER_TELLFEED             0x00010000L
#define     TAG_FEEDER_TELLFLAT             0x00020000L
#define     TAG_FEEDER_TELLSCAN             0x00040000L
#define     TAG_FEEDER_CENTERFEED           0x00080000L
#define     TAG_FEEDER_CENTERFLAT           0x00100000L
#define     TAG_FEEDER_PAUSE                            0x00200000L


/* short tags */
#define TAG_SAMPLESPERPIXEL             0x0115

#define TAG_BITSPERSAMPLE               0x0102

#define TAG_CONTRAST                    0x0501
#define     TAG_CONTRAST_AUTO               0x0000

#define TAG_BRIGHTNESS                  0x0502
#define     TAG_BRIGHTNESS_AUTO             0xFFFFFFFD
#define     TAG_BRIGHTNESS_DARKEN           0xFFFFFFFE
#define     TAG_BRIGHTNESS_NORM             0xFFFFFFFF
#define     TAG_BRIGHTNESS_LIGHTEN          0x00000000

#define TAG_COMPRESSION                 0x0103
#define     TAG_COMPRESSION_NONE            0x0001   /* no compression        */
#define     TAG_COMPRESSION_MG3             0x0002   /* CCITT compression     */
#define     TAG_COMPRESSION_G3              0x0003   /* CCITT G3 1-DIM        */
#define     TAG_COMPRESSION_G4              0x0004   /* CCITT G4              */
#define     TAG_COMPRESSION_LZW             0x0005   /* LZW compression       */
#define     TAG_COMPRESSION_JPEG            0x0006   /* not supported by LEAD */
#define     TAG_COMPRESSION_PACK            0x8005   /* not supported by LEAD */
#define     TAG_COMPRESSION_32771           0x8003   /* packbits compression  */
#define     TAG_COMPRESSION_JBIG            0x8765   /* not supported by LEAD */
#define     TAG_COMPRESSION_PCX             0xC350   /* not supported by LEAD */
#define     TAG_COMPRESSION_4BYTE           0xC351   /* not supported by LEAD */
#define     TAG_COMPRESSION_GIF             0xC355   /* not supported by LEAD */
#define     TAG_COMPRESSION_BMP             0xC356   /* not supported by LEAD */

#define TAG_PLANARCONFIGURATION         0x011c
#define     TAG_PLANARCONFIG_LINE           0x0001
#define     TAG_PLANARCONFIG_LINE_PACK      0x0001
#define     TAG_PLANARCONFIG_PAGE           0x0002
#define     TAG_PLANARCONFIG_LINE_UNPACK    0x1388

#define TAG_SCANORIENTATION             0x0113
#ifndef TAG_SCANORIENTATION_PORT
#define     TAG_SCANORIENTATION_PORT    0x0001  /*   0 degrees -- portait mode     */
#define     TAG_SCANORIENTATION_LAND    0x0002  /*  90 degrees -- landscape mode   */
#define     TAG_SCANORIENTATION_180     0x0003  /* 180 degrees                     */
#define     TAG_SCANORIENTATION_270     0x0004  /* 270 degrees                     */
#define     TAG_SCANORIENTATION_PORTM   0x0005  /*   0 degrees -- flipped horizontally */
#define     TAG_SCANORIENTATION_LANDM   0x0006  /*  90 degrees -- flipped horizontally */
#define     TAG_SCANORIENTATION_180M    0x0007  /* 180 degrees -- flipped horizontally */
#define     TAG_SCANORIENTATION_270M    0x0008  /* 270 degrees -- flipped horizontally */
#endif

#define TAG_MAXPAGES                    0x0504

#define TAG_SCANAHEAD                   0x050d
#define     TAG_SCANAHEAD_NO                0x0000
#define     TAG_SCANAHEAD_YES               0x0001

#define TAG_GAMMA                       0x050f
#define     TAG_GAMMA_NORMAL                0x0000
#define     TAG_GAMMA_AUTO                  TAG_GAMMA_NORMAL
#define     TAG_GAMMA_DOWNLOAD1             0x0001
#define     TAG_GAMMA_DOWNLOAD2             0x0002
#define     TAG_GAMMA_DOWNLOAD3             0x0003
#define     TAG_GAMMA_DOWNLOAD4             0x0004
#define     TAG_GAMMA_DOWNLOAD5             0x0005
#define     TAG_GAMMA_DOWNLOAD6             0x0006
#define     TAG_GAMMA_CRT                                       0x0007
/*
 * Following TAG_GAMMA_xxx values are for the Ricoh IS-5x0 only.
 * In general, try to make sharper (higher gamma) correspond to lower tag
 * values (?) and make special values (s-curves, inverting curves) negative.
 */
#define     TAG_GAMMA_BOTTOMCLIP            0xFFFFFFFD
#define     TAG_GAMMA_1TO1INVERT            0xFFFFFFFE
#define     TAG_GAMMA_SCURVE                0xFFFFFFFF
#define     TAG_GAMMA_SHARP_61              0x0001
#define     TAG_GAMMA_SHARP_67              0x0002
#define     TAG_GAMMA_SHARP_75              0x0003
#define     TAG_GAMMA_SHARP_87              0x0004
#define     TAG_GAMMA_1TO1                  0x0005
#define     TAG_GAMMA_BLUR_1_20             0x0006
#define     TAG_GAMMA_BLUR_1_45             0x0007
#define     TAG_GAMMA_BLUR_1_78             0x0008
#define     TAG_GAMMA_BLUR_2_20             0x0009

#define TAG_SCANAHEAD_MAXPAGES  0x057c  /* Max pages to scan ahead */

#define TAG_SCANTYPE                        0x0514
#define     TAG_SCANTYPE_AUTOMATIC          0 /* default */
#define     TAG_SCANTYPE_TRANSPARENCY       1
#define     TAG_SCANTYPE_FLATBED            2
#define     TAG_SCANTYPE_FEEDER             3
#define     TAG_SCANTYPE_FRONTONLY          3
#define     TAG_SCANTYPE_DUPLEX             4
#define     TAG_SCANTYPE_FRONTBACK          4
#define     TAG_SCANTYPE_BACKFRONT          5
#define     TAG_SCANTYPE_BACKONLY           6

#define TAG_PHOTOMETRICINTERPRETATION   0x0106
#define     TAG_PHOTOMETRIC_WHITE0          0
#define     TAG_PHOTOMETRIC_WHITE1          1
#define     TAG_PHOTOMETRIC_RGB             2
#define     TAG_PHOTOMETRIC_PALETTE         3
#define     TAG_PHOTOMETRIC_BGR             120

/* ASCII tags */
#define TAG_PAGESIZE                    0x050e

#endif

/* external prototypes */
L_BOOL EXT_FUNCTION L_IsISISAvailable(L_VOID);

L_INT EXT_FUNCTION L_ISISAcquire(HWND hWnd, 
                                 pBITMAPHANDLE pBitmap, 
                                 L_UINT32 uFlags);

L_INT EXT_FUNCTION L_ISISAcquireMulti(HWND hWnd, 
                                      L_CHAR L_FAR * pszBaseFileName, 
                                      L_UINT32 uFlags, 
                                      L_INT nFormat, 
                                      L_BOOL bMultiPageFile, 
                                      L_INT L_FAR *pnPagesDiscarded, 
                                      ISISCALLBACK pfnCallback, 
                                      L_VOID L_FAR * pUserData);

L_INT EXT_FUNCTION L_ISISSelect(HWND hWnd, 
                                L_CHAR L_FAR* pszCurScanDriver);

L_INT EXT_FUNCTION L_ISISLoadDriver(L_CHAR L_FAR* pszDriverName);

L_INT EXT_FUNCTION L_ISISUnloadDriver(L_VOID);

L_INT EXT_FUNCTION L_ISISSetTagLong(L_UINT uTag, 
                                    L_INT32 lValue);

L_INT EXT_FUNCTION L_ISISGetTagLong(L_UINT uTag, 
                                    L_INT32 L_FAR * plValue);

L_INT EXT_FUNCTION L_ISISSetTagShort(L_UINT uTag, 
                                     L_INT nValue);

L_INT EXT_FUNCTION L_ISISGetTagShort(L_UINT uTag, 
                                     L_INT L_FAR * pnValue);

L_INT EXT_FUNCTION L_ISISSetScanOptions(HWND hWnd);

L_INT EXT_FUNCTION L_ISISSetTagASCII(L_UINT uTag,
                                     L_CHAR L_FAR* pszValue);

L_INT EXT_FUNCTION L_ISISGetTagASCII(L_UINT uTag, 
                                     L_CHAR L_FAR* pszValue,
                                     L_UINT32 L_FAR* puSize,
                                     L_BOOL bDefault);

L_INT EXT_FUNCTION L_ISISGetTagASCIIChoice(L_UINT uTag, 
                                           L_INT32 nIndex,
                                           L_CHAR L_FAR* pszValue,
                                           L_UINT32 L_FAR* puSize);

L_INT EXT_FUNCTION L_ISISGetTagLongChoice(L_UINT uTag, 
                                          L_INT32 nIndex,
                                          L_INT32 L_FAR * plValue);

L_INT EXT_FUNCTION L_ISISGetTagShortChoice(L_UINT uTag, 
                                           L_INT32 nIndex,
                                           L_INT L_FAR * pnValue);


#undef _HEADER_ENTRY_
#include "ltpck.h"

#endif                          /* _LTISI_H_ */
