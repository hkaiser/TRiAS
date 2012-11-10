/*
  +----------------------------------------------------+
  |   LTCLR.H - color conversion module header file    |
  |   Copyright (c) 1991-2001 LEAD Technologies, Inc.  |
  |   All Rights Reserved.                             |
  +----------------------------------------------------+
*/

#ifndef _LTCLR_H_
#define _LTCLR_H_

#include "Lttyp.h"

#define _HEADER_ENTRY_
#include "ltpck.h"   

#include "ltdis.h"

/*
   white points constants
*/

#define CIELAB_D50     50
#define CIELAB_D55     55
#define CIELAB_D65     65
#define CIELAB_D75     75
#define CIELAB_D93     93
#define CIELAB_CUSTOM  00
#define CIELAB_DEFAULT CIELAB_D50

/*
   nMethod values for CONVERSION_PARAMS
*/

#define USE_BUILTIN    1  /* for equations               */
#define USE_ICC        2  /* for Profiles                */
#define USE_CUSTOM_ICC 4  /* for Custom Profiles         */
#define USE_ET         8  /* for Emulation Tables        */
#define USE_CUSTOM_ET  16 /* for Custom Emulation Tables */
#define USE_AUTO       32 /* for Best Conversion         */
#define USE_ALL        63 /* for all of the above        */

/*
   nMask values for SET_CONVERSION_PARAMS
*/

#define CHANGE_ACTIVE_METHOD    1   /* change the active method */
#define CHANGE_CUSTOM_PROFILES  2   /* change profiles          */
#define CHANGE_WHITE_POINT      4   /* change white point       */
#define CHANGE_ET               8   /* change Emulation Tables  */
#define CHANGE_CMYK             16  /* change CMYK parameters   */
#define CHANGE_YUV              32  /* change YUV parameters    */
#define CHANGE_LAB              64  /* change LAB parameters    */
#define CHANGE_ALL              127 /* cahnge all of the above  */

/*
   nMask values for CMYK_PARAMS
*/

#define CMYK_GCR   1 /* change nGcr_level */

/*
   nMask values for LAB_PARAMS
*/

#define LAB_L_OFFSET  1  /* change L_min value */
#define LAB_L_RANGE   2  /* change a_min value */
#define LAB_a_OFFSET  4  /* change b_min value */
#define LAB_a_RANGE   8  /* change L_max value */
#define LAB_b_OFFSET  16 /* change a_max value */
#define LAB_b_RANGE   32 /* change b_max value */

/*
   nMask values for YUV_PARAMS
*/

#define YUV_UH         1  /* change nUh value       */
#define YUV_UV         2  /* change nUv value       */
#define YUV_VH         4  /* change nVh value       */
#define YUV_VV         8  /* change nvV value       */
#define YUV_OFFSETS    16 /* change pOffsets value  */
#define YUV_ELEMENTS   32 /* change nElements value */
#define YUV_RANGE      64 /* change nRange value    */

/*
   nRange values for YUV_PARAMS
*/

#define YUVRANGE_FULL   0 /* the range is 000 - 255 */
#define YUVRANGE_16_240 1 /* the range is 016 - 240 */


#define PLANAR_YUV 0
#define PLANAR_YVU 1
#define PLANAR_UYV 2
#define PLANAR_UVY 3
#define PLANAR_VYU 4
#define PLANAR_VUY 5

/* 
   user defined structures:
*/

typedef struct
{
   L_INT nWhitePoint;
   L_DOUBLE xWhite;
   L_DOUBLE yWhite;
} WHITEPOINT, L_FAR* LPWHITEPOINT;

typedef struct
{
   L_INT nSize;
   L_INT nGcr_level; /* value between 0.0 and 1.0 */
   L_INT nMask;
} CMYK_PARAMS, *LPCMYK_PARAMS;

typedef struct
{
   L_INT nSize;
   L_INT nMask;
   L_INT nUh;          /* horizontal frequency of U                                   */
   L_INT nUv;          /* vertical frequency of U                                     */
   L_INT nVh;          /* horizontal frequency of V                                   */
   L_INT nVv;          /* vertical frequency of V                                     */
   L_INT *pOffsets;    /* offsets of the byte ordering for the proposed YUV format.   */
			              /* when bPlaner is TRUE, the only useful data is pOffset[0]    */
                       /* which will indicate what is the arrangement of the YUV      */
                       /* buffer(YUV,YVU,UYV,UVY,VYU,VUY)                             */
   L_INT nMacroPixel;  /* number of pixels in the macro pixel                         */
   L_INT nRange;       /* the range of values in the input buffer; full               */
                       /* range or 16-240 (YUVRANGE_FULL and YUVRANGE_16_240)         */
   L_BOOL bPlanar;     /* the buffer consists of planes; Y plane, V plane and U plane.*/
} YUV_PARAMS, *LPYUV_PARAMS;

typedef struct
{
   L_INT nSize;
   L_INT nMask;
   L_INT L_offset;
   L_INT L_range;
   L_INT a_offset;
   L_INT a_range;
   L_INT b_offset;
   L_INT b_range;
} LAB_PARAMS, *LPLAB_PARAMS;

typedef struct
{
   L_INT  nSize;
   L_INT  nActiveMethod;                  /*  one of the values: USE_BUILTINT   for builtin,                */
                                          /*                     USE_ICC        for Profiles,               */
                                          /*                     USE_ICC_CUSTOM for user-defined profiles   */
                                          /*                     USE_ET         for Emulation Tables.       */
   LPWHITEPOINT  pWpoint;                 /*  white point struct that describes the white point to be used. */
   L_CHAR        sInputProfile[MAX_PATH]; /*  optional input profile                                        */
   L_CHAR        sOutputProfile[MAX_PATH];/*  optional output profile                                       */
   L_CHAR        sDstInputTable[MAX_PATH];/*  optional Dst image for emulation                              */
   LPCMYK_PARAMS pCmykParams;             /*  CMYK data                                                     */
   LPYUV_PARAMS  pYuvParams;              /*  YUV data                                                      */
   LPLAB_PARAMS  pLabParams;              /*  CIELab data                                                   */
   L_INT         nMethod;                 /*  in the case we use it with L_ClrInit function this structure  */
                                          /*  will have one of the valuse:                                  */
                                          /*                   USE_BUILTINT   for equations,                */
                                          /*                   USE_ICC        for Profiles,                 */
                                          /*                   USE_ICC_CUSTOM for user-defined profiles     */
                                          /*                   USE_ET         for Emulation Tables.         */
                                          /*  in the case used with L_SetConversionParams function, it will */
                                          /*  hold the masking valuse                                       */
   L_INT         nQuantization;           /*  quantization level, used with USE_ET                          */
} CONVERSION_PARAMS, *LPCONVERSION_PARAMS;


/* 
   user functions: 
*/

L_INT EXT_FUNCTION L_ClrInit(HANDLE *pClrHandle, 
                             L_INT nSrcFormat,
                             L_INT nDstFormat,
                             LPCONVERSION_PARAMS pParams);

L_INT EXT_FUNCTION L_ClrSetConversionParams(HANDLE ClrHandle,
                                         LPCONVERSION_PARAMS pParams);

L_INT EXT_FUNCTION L_ClrConvertDirect(L_INT nSrcFormat,
                                      L_INT nDstFormat,
                                      L_UCHAR *pSrcBuf,
                                      L_UCHAR *pDstBuf,
                                      L_INT nWidth,
                                      L_INT nHeight,
                                      L_INT nInAlign,
                                      L_INT nOutAlign);

L_INT EXT_FUNCTION L_ClrConvert(HANDLE ClrHandle,
                                L_UCHAR *pSrc, 
                                L_UCHAR *pDst,
                                L_INT nWidth,
                                L_INT nHeight,
                                L_INT nInAlign,
                                L_INT nOutAlign);

L_INT EXT_FUNCTION L_ClrFree(HANDLE ClrHandle);

L_INT EXT_FUNCTION L_ClrIsValid(HANDLE ClrHandle);



#undef _HEADER_ENTRY_
#include "ltpck.h"

#endif _LTCLR_H_
