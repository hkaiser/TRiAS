/*
   ltSeg.h - LEAD Segmentation Module header file
   Copyright (c) 1990-2001 by LEAD Technologies, Inc.
   All Rights Reserved.
*/

#ifndef __LTSEG_H__
#define __LTSEG_H__

#include "ltfil.h"

#define _HEADER_ENTRY_
#include "ltpck.h"


/* Segment Type */
#define SEGMENT_TEXT       0x01
#define SEGMENT_PICTURE    0x02

/* Coder Type */
#define MRC_MASK_COMPRESSION_FAX_G4       0x001
#define MRC_MASK_COMPRESSION_FAX_G3_1D    0x002
#define MRC_MASK_COMPRESSION_FAX_G3_2D    0x003
#define MRC_MASK_COMPRESSION_JBIG         0x004
#define MRC_BACKGROUND_COMPRESSION_JPEG   0x005
#define MRC_BACKGROUND_COMPRESSION_CMP    0x006

/* segmentation handle */
#define HSEGMENTATION     HANDLE
#define pHSEGMENTATION    HSEGMENTATION L_FAR*

/* define segment info structure */
typedef struct _SEGMENTDATA
{
   RECT     rcBitmapSeg;
   L_UINT   uType;
   RGBQUAD  rgbBGColor;
   RGBQUAD  rgbFGColor;
} SEGMENTDATA, L_FAR * pSEGMENTDATA;

typedef struct _tagCOMPRESSIONOPTIONS
{
   L_INT    nMaskCoder;
   L_INT    nBGCoder;
   L_INT    nBGQFactor;
   L_BOOL   bEnhanceQuality;
} COMPRESSIONOPTIONS, L_FAR* pCOMPRESSIONOPTIONS;
/* define minimum segment structure */
typedef struct _MINSEG
{
   L_INT nMinWidth;
   L_INT nMinHeight;
} MINSEGMENT, L_FAR * pMINSEGMENT;

/*------------Callbacks-------------------------------------------------------------*/
typedef L_INT (pEXT_CALLBACK pSEGMENTATIONCALLBACK) (HSEGMENTATION  hSegment,
                                                     L_INT nStripeNo,
                                                     L_INT nStripeStartRow,
                                                     L_INT nStripeEndRow,
                                                     L_INT nSegmentCount,
                                                     pSEGMENTDATA pSegment,
                                                     L_VOID L_FAR * pUserData);
typedef L_INT (pEXT_CALLBACK pMRCENUMSEGMENTSPROC)(HSEGMENTATION  hSegment, 
                                                       const pSEGMENTDATA pSegment, 
                                                       L_INT nSegId,
                                                       L_VOID L_FAR *pUserData);

/*------------Bitmap Segmentation -------------------------------------------------*/

// Initialize segmentation handle
L_INT EXT_FUNCTION L_MrcStartBitmapSegmentation(pHSEGMENTATION phSegment,
                                                L_INT          nWidth,
                                                L_INT          nHeight,
                                                COLORREF       clrBackground,
                                                COLORREF       clrForeground);
// Free segmentation handle
L_INT EXT_FUNCTION L_MrcEndBitmapSegmentation(HSEGMENTATION hSegment);


// Break a bitmap into segments 
L_INT EXT_FUNCTION L_MrcSegmentBitmap(HSEGMENTATION         hSegment,
                                      pBITMAPHANDLE          pBitmap,
                                      pMINSEGMENT           pMinSeg,
                                      L_UINT32              uSegFactor,
                                      pSEGMENTATIONCALLBACK pfnCallback,
                                      L_VOID L_FAR *        pUserData);

// Set a new stripe in the segmentation handle 
L_INT EXT_FUNCTION L_MrcSetNewStripe(HSEGMENTATION hSegment,
                                     L_INT         nStripeStartRow,
                                     L_INT         nStripeEndRow);

// Set a new segment  in the segmentation handle 
L_INT EXT_FUNCTION L_MrcSetStripeSegment(HSEGMENTATION   hSegment,
                                         L_INT           nStripeIndex,
                                         pSEGMENTDATA    pSegment);


// Set maximum height of a stripe
L_INT EXT_FUNCTION L_MrcSetStripeMaxHeight(HSEGMENTATION    hSegment,
                                           L_INT            nStripeMaxHeight);

// Get all segments stored inside a segmentation handle
L_INT EXT_FUNCTION L_MrcEnumSegments(HSEGMENTATION              hSegment, 
                                     pMRCENUMSEGMENTSPROC   pEnumProc, 
                                     L_VOID L_FAR *             pUserData, 
                                     L_UINT32                   dwFlags);

// Update a certain segment in the segmentation handle 
L_INT EXT_FUNCTION L_MrcUpdateSegmentData(HSEGMENTATION  hSegment, 
                                          L_INT          nSegId,
                                          pSEGMENTDATA   pSegmentData,
                                          L_BOOL         bVerifyUpdate);

L_INT EXT_FUNCTION L_MrcDeleteSegment(HSEGMENTATION  hSegment,
                                      L_INT          nSegId);

/*------------Save a file as MRC ---------------------------------------------------*/

L_INT EXT_FUNCTION L_MrcSaveBitmap(HSEGMENTATION           hSegment,
                                   pBITMAPHANDLE           pBitmap,
                                   pCOMPRESSIONOPTIONS     pCmpOption,
                                   L_CHAR L_FAR*           pszFileName,
                                   FILESAVECALLBACK        pfnCallback,
                                   L_VOID L_FAR *          pUserData);

L_INT EXT_FUNCTION L_MrcSaveBitmapT44(HSEGMENTATION           hSegment,
                                      pBITMAPHANDLE           pBitmap,
                                      pCOMPRESSIONOPTIONS     pCmpOption,
                                      L_CHAR L_FAR*           pszFileName,
                                      FILESAVECALLBACK        pfnCallback,
                                      L_VOID L_FAR *          pUserData);

/*------------Load an MRC file -----------------------------------------------------*/

L_INT EXT_FUNCTION L_MrcLoadBitmap( L_CHAR L_FAR*     pszFileName,
                                    pBITMAPHANDLE     pBitmap,
                                    L_INT             nPageNo,
                                    FILEREADCALLBACK  pfnCallback,
                                    L_VOID L_FAR *    pUserData);

L_INT EXT_FUNCTION L_MrcGetPagesCount( L_CHAR L_FAR* pszFileName,
                                       L_INT* pnPages);


#undef _HEADER_ENTRY_
#include "ltpck.h"

#endif //__LTSEG_H__
