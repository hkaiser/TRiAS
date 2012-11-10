/*
   LTIMG.H - image module header file
   Copyright (c) 1991-2000 LEAD Technologies, Inc.
   All Rights Reserved.
*/

#ifndef _LTIMG_H_
#define _LTIMG_H_

#include "ltkrn.h"

#define _HEADER_ENTRY_
#include "ltpck.h"

/*
   flags for L_EmbossBitmap
*/
#define EMBOSS_N    0
#define EMBOSS_NE   1
#define EMBOSS_E    2
#define EMBOSS_SE   3
#define EMBOSS_S    4
#define EMBOSS_SW   5
#define EMBOSS_W    6
#define EMBOSS_NW   7

/*
   flags for L_GetHistogram, L_RemapBitmapIntensity, and L_AddNoiseBitmap
*/
#define CHANNEL_MASTER 0        /* All channels */
#define CHANNEL_RED    1        /* Red channel only */
#define CHANNEL_GREEN  2        /* Green channel only */
#define CHANNEL_BLUE   3        /* Blue channel only */

/*
   flags for L_ColorSeparateBitmap/L_ColorMergeBitmap
*/
#define COLORSEP_RGB                 0x00 /* Use 3 RGB color planes. */
#define COLORSEP_CMYK                0x01 /* Use 4 CMYK color planes. */
#define COLORSEP_HSV                 0x02 /* Use 3 HSV color planes. */
#define COLORSEP_HLS                 0x03 /* Use 3 HLS color planes. */
#define COLORSEP_CMY                 0x04 /* Use 3 CMY color planes. */

#define RGB_SPACE  0x0001 
#define YUV_SPACE  0x0002
#define GRAY_SPACE 0x0004

#define SWAP_RG     0x0001
#define SWAP_RB     0x0002
#define SWAP_GB     0x0004
#define SWAP_RGBR   0x0008
#define SWAP_RBGR   0x0010

/*
   flags for L_ResizeBitmapRgn
*/
#define RGN_EXPAND   0x0001
#define RGN_CONTRACT 0x0002

/*
   flags for L_CreateFadedMask
*/
#define FADE_OUTER                   0x0001
#define FADE_DUMPFILL                0x0002
#define FADE_FILLCOLOR_START         0x0004
#define FADE_WHITETOBLACK            0x0008
#define FADE_NOTRANSPARENCY          0x0010
#define FADE_TRANSPARENCY_DUMPCOLOR  0x0020

/*
   flags for L_CombineBitmapExt
*/
#define CB_SRC_MASTER 0x00000000
#define CB_SRC_RED    0x00010000
#define CB_SRC_GREEN  0x00020000
#define CB_SRC_BLUE   0x00030000

#define CB_DST_MASTER 0x00000000
#define CB_DST_RED    0x00100000
#define CB_DST_GREEN  0x00200000
#define CB_DST_BLUE   0x00300000

#define CB_RES_MASTER 0x00000000
#define CB_RES_RED    0x01000000
#define CB_RES_GREEN  0x02000000
#define CB_RES_BLUE   0x03000000

/*
   flags for L_AddBitmaps and L_AddWeightedBitmaps.
*/
#define BC_AVG         0x0001
#define BC_ADD         0x0002
#define BC_AVGWEIGHTED 0x0003
#define BC_ADDWEIGHTED 0x0004

/*
   flags for L_AntiAliasBitmap
*/
#define ANTIALIAS_1       0x0000
#define ANTIALIAS_2       0x0001
#define ANTIALIAS_3       0x0002
#define ANTIALIAS_DIAG    0x0003
#define ANTIALIAS_HORZ    0x0004
#define ANTIALIAS_VERT    0x0005

/*
   flags for L_EdgeDetectorBitmap
*/
#define EDG_SOBEL_VERT    0x0101
#define EDG_SOBEL_HORZ    0x0102
#define EDG_SOBEL_ALL     0x0103


#define EDG_PREWITT_VERT  0x0201
#define EDG_PREWITT_HORZ  0x0202
#define EDG_PREWITT_ALL   0x0203


#define EDG_LAPLACE_1     0x0301
#define EDG_LAPLACE_2     0x0302
#define EDG_LAPLACE_3     0x0303
#define EDG_LAPLACE_DIAG  0x0304
#define EDG_LAPLACE_HORZ  0x0305
#define EDG_LAPLACE_VERT  0x0306

#define EDG_GRADIENT_N    0x0401
#define EDG_GRADIENT_NE   0x0402
#define EDG_GRADIENT_E    0x0403
#define EDG_GRADIENT_SE   0x0404
#define EDG_GRADIENT_S    0x0405
#define EDG_GRADIENT_SW   0x0406
#define EDG_GRADIENT_W    0x0407
#define EDG_GRADIENT_NW   0x0408

/*
   flags for L_GetFunctionalLookupTable
*/
#define FLT_EXP    0x0000
#define FLT_LN     0x0001
#define FLT_LINEAR 0x0002

/*
   flags for L_HalfToneBitmap
*/
#define HT_PRINT  0x0000
#define HT_VIEW   0x0001
#define HT_RECT   0x0002
#define HT_CIRC   0x0003
#define HT_ELLIPS 0x0004
#define HT_RAND   0x0005
#define HT_LINEAR 0x0006
#define HT_USERDEF 0x0007

/*
   flags for L_AddFrame
*/
#define FRAME_QUALITY_LOW  0
#define FRAME_QUALITY_HIGH 1

#define FRAME_INSIDE  0
#define FRAME_OUTSIDE 1

/*
   flags for L_AddBorder
*/
#define BORDER_INSIDE            0X0000
#define BORDER_OUTSIDE           0X0001

#define BORDER_STYLE_TRANSPARENT 0x0000
#define BORDER_STYLE_OPAQUE      0x0001
#define BORDER_STYLE_GRADIENT    0x0002
#define BORDER_STYLE_TILES       0x0003

#define BORDER_EFFECT_CURVEDIN   0x0001
#define BORDER_EFFECT_CURVEDOUT  0x0002
#define BORDER_EFFECT_RAISED     0x0003

#define BORDER_SHADOW_LEFT       0x0000
#define BORDER_SHADOW_RIGHT      0x0001
#define BORDER_SHADOW_SURROUND   0x0002

#define BORDER_GRAD_INSIDEOUT    0x0000
#define BORDER_GRAD_CENTEROUT    0x0001
#define BORDER_GRAD_CORNEROUT    0x0002

//for L_CylendricalBitmap
#define CYL_HORZ     0x0000
#define CYL_VERT     0x0001

//for L_BendingBitmap
#define BND_NORM     0x0000
#define BND_HORZ     0x0100
#define BND_VERT     0x0200

//for L_PolarBitmap
#define CART_TO_POL  0x0000
#define POL_TO_CART  0x0010

//for L_PixelateBitmap
#define PIX_MAX      0x0000
#define PIX_MIN      0x0001
#define PIX_AVR      0x0002
#define PIX_RECT     0x0010
#define PIX_RAD      0x0020
#define PIX_WFRQ     0x0100
#define PIX_WPER     0x0200
#define PIX_HFRQ     0x0400
#define PIX_HPER     0x0800

//for L_GetUserBuffer
#define GUB_CURVE    0x0000
#define GUB_LINEAR   0x0001

//for L_FreeHandWaveBitmap
//for L_RadWaveBitmap
//for L_WaveBitmap
#define DIS_PER      0x0000
#define DIS_FRQ      0x0010

//for L_ShearBitmapExt
#define SHR_HORZ     0x0000
#define SHR_VERT     0x0010

//for L_WaveBitmap
#define WV_SIN       0x0000
#define WV_COS       0x0100
#define WV_SQUARE    0x0200
#define WV_TRIANG    0x0300

//General
#define FILL_CLR     0x0000
#define FILL_RPT     0x0001
#define FILL_NOCHG   0x0002
#define FILL_ROT     0x0000
#define FILL_WOUTROT 0x0010

typedef struct tagBALANCING
{
   L_DOUBLE toRed;
   L_DOUBLE toGreen;
   L_DOUBLE toBlue;
}BALANCING;

/*
   Add Frame.
*/

typedef struct _ADDFRAMEINFO
{
   pBITMAPHANDLE pBitmapFrame;
   L_BOOL        bKeepFrameState;
   L_BOOL        bUseMask;
   COLORREF      crMask;
   BYTE          SmoothEdge;
   L_INT         nLocation;
   L_INT         nQuality;
} ADDFRAMEINFO, L_FAR * LPADDFRAMEINFO;

/*
   Add Border.
*/

typedef struct _ADDBORDERINFO
{
   L_INT         nLeftThickness;
   L_INT         nTopThickness;
   L_INT         nRightThickness;
   L_INT         nBottomThickness;
   L_INT         nLocation;
   L_INT         nStyle;
   L_INT         nEffectStyle;
   pBITMAPHANDLE pTileBitmap;
   L_INT         nGradientStyle;
   COLORREF      crGradientStart;
   COLORREF      crGradientEnd;
   L_INT         nCurveIntensity;
   L_BOOL        bSoftCurve;
   L_BOOL        bShadow;
   L_INT         nShadowSize;
   L_INT         nShadowDirection;
   L_BOOL        bBumpyShadow;
} ADDBORDERINFO, L_FAR * LPADDBORDERINFO;

/*
   Add & Extract Message
*/

typedef struct _ADDMESGINFO
{
   L_UCHAR L_FAR * pStrMsg;
   L_UCHAR L_FAR * pPassword;
   L_UCHAR L_FAR * pFileName;
   L_UCHAR L_FAR * pDirectory;
   LPPOINT pStart;
} ADDMESGINFO, L_FAR * LPADDMESGINFO;

/*
   Binary filter constants
*/

#define BFLT_DONTCARE   256

typedef struct tagBINARYFLT
{
   L_BOOL bfltMax;              /* select maximimum value */
   L_UINT bfltDim;              /* filter dimensions */
   L_INT bfltMatrix[1];         /* array of filter coefficients */
} BINARYFLT, L_FAR * LPBINARYFLT;

#define BINARYFLTSIZE(dim) (sizeof(BINARYFLT) + (sizeof(L_INT) * (((L_INT) (dim) * (L_INT) (dim)) - 1)))
#define MAKEINTBFLT(i) ((LPBINARYFLT)((L_UINT32)((L_UINT16) (i))))

#define BFLT_EROSION_OMNI    MAKEINTBFLT(0)
#define BFLT_EROSION_HORZ    MAKEINTBFLT(1)
#define BFLT_EROSION_VERT    MAKEINTBFLT(2)
#define BFLT_EROSION_DIAG    MAKEINTBFLT(3)
#define BFLT_DILATION_OMNI    MAKEINTBFLT(4)
#define BFLT_DILATION_HORZ    MAKEINTBFLT(5)
#define BFLT_DILATION_VERT    MAKEINTBFLT(6)
#define BFLT_DILATION_DIAG    MAKEINTBFLT(7)

/*
   spatial filter constants
*/
typedef struct tagSPATIALFLT
{
   L_INT fltDivisor;            /* sum divisor */
   L_INT fltBias;               /* sum bias */
   L_UINT fltDim;               /* filter dimensions */
   L_INT fltMatrix[1];          /* array of filter coefficients */
} SPATIALFLT, L_FAR * LPSPATIALFLT;

#define SPATIALFLTSIZE(dim) (sizeof(SPATIALFLT) + (sizeof(L_INT) * (((L_INT) (dim) * (L_INT) (dim)) - 1)))
#define MAKEINTFLT(i) ((LPSPATIALFLT)((L_UINT32)((L_UINT16) (i))))

#define FLT_EMBOSS_N    MAKEINTFLT(0)
#define FLT_EMBOSS_NE   MAKEINTFLT(1)
#define FLT_EMBOSS_E    MAKEINTFLT(2)
#define FLT_EMBOSS_SE   MAKEINTFLT(3)
#define FLT_EMBOSS_S    MAKEINTFLT(4)
#define FLT_EMBOSS_SW   MAKEINTFLT(5)
#define FLT_EMBOSS_W    MAKEINTFLT(6)
#define FLT_EMBOSS_NW   MAKEINTFLT(7)

#define FLT_GRADIENT_N    MAKEINTFLT(8)
#define FLT_GRADIENT_NE   MAKEINTFLT(9)
#define FLT_GRADIENT_E    MAKEINTFLT(10)
#define FLT_GRADIENT_SE   MAKEINTFLT(11)
#define FLT_GRADIENT_S    MAKEINTFLT(12)
#define FLT_GRADIENT_SW   MAKEINTFLT(13)
#define FLT_GRADIENT_W    MAKEINTFLT(14)
#define FLT_GRADIENT_NW   MAKEINTFLT(15)

#define FLT_LAPLACE_1     MAKEINTFLT(16)
#define FLT_LAPLACE_2     MAKEINTFLT(17)
#define FLT_LAPLACE_3     MAKEINTFLT(18)
#define FLT_LAPLACE_DIAG  MAKEINTFLT(19)
#define FLT_LAPLACE_HORZ  MAKEINTFLT(20)
#define FLT_LAPLACE_VERT  MAKEINTFLT(21)

#define FLT_SOBEL_HORZ    MAKEINTFLT(22)
#define FLT_SOBEL_VERT    MAKEINTFLT(23)

#define FLT_PREWITT_HORZ  MAKEINTFLT(24)
#define FLT_PREWITT_VERT  MAKEINTFLT(25)

#define FLT_SHIFTDIFF_DIAG  MAKEINTFLT(26)
#define FLT_SHIFTDIFF_HORZ  MAKEINTFLT(27)
#define FLT_SHIFTDIFF_VERT  MAKEINTFLT(28)

#define FLT_LINESEG_HORZ  MAKEINTFLT(29)
#define FLT_LINESEG_VERT  MAKEINTFLT(30)
#define FLT_LINESEG_LTOR  MAKEINTFLT(31)
#define FLT_LINESEG_RTOL  MAKEINTFLT(32)

/*
   Flags for L_PicturizeBitmap
*/
#define PICTURIZE_LOADALL     0x0001   /* Load all files in memory */
#define PICTURIZE_RESIZE      0x0002   /* Resize all images that are not the required size */
#define PICTURIZE_RESAMPLE    0x0004   /* Resample all images that are not the required size */
#define PICTURIZE_ONCE        0x0010   /* Use the image only once thoughout the process */
#define PICTURIZE_EQUALUSAGE  0x0020   /* Use all images equally, i.e. before an image will be
                                          used twice all other images must be used at least once */
#define PICTURIZE_BESTFIT     0x0040   /* Images will be resized to fit the image if the bitmap
                                          width or height is not a multiple of nCellWidth/nCellHeight */

#define CONTOUR_THIN              0
#define CONTOUR_LINK_BLACKWHITE   1
#define CONTOUR_LINK_GRAY         2
#define CONTOUR_LINK_COLOR        3
#define CONTOUR_APPROX_COLOR      4

#define DEFAULT_THRESHOLD       15 /* default for background threshold value */
#define DEFAULT_DELTADIRECTION  35 /* default for maximum angle for the thinning algorithm */
#define DEFAULT_MAXIMUMERROR     5 /* default for maximum approximation error */

/*
   Constants and Flags for Doc Imaging functions

*/
/* Defined so that !(SMOOTH_BUMP) == (SMOOTH_NICK) */
#define SMOOTH_BUMP 0
#define SMOOTH_NICK 1
#define SMOOTH_NONE 2

#define SMOOTH_HORIZONTAL_ELEMENT   0
#define SMOOTH_VERTICAL_ELEMENT     1

#define SUCCESS_REMOVE              1  
#define SUCCESS_NOREMOVE            2  
#define LINEREMOVE_HORIZONTAL       1
#define LINEREMOVE_VERTICAL         2
#define SUCCESS_INVERT              1
#define SUCCESS_NOINVERT            2

#define BORDER_LEFT     1
#define BORDER_RIGHT    2
#define BORDER_TOP      4
#define BORDER_BOTTOM   8
#define BORDER_ALL      (BORDER_LEFT | BORDER_RIGHT | BORDER_TOP | BORDER_BOTTOM)
#define BORDER_DELTA_MAX (0xffffffff)

//flags for iLocation
#define HOLEPUNCH_LEFT     (1)
#define HOLEPUNCH_RIGHT    (2)
#define HOLEPUNCH_TOP      (3)
#define HOLEPUNCH_BOTTOM   (4)

#define STAPLE_TOPLEFT     (1)
#define STAPLE_TOPRIGHT    (2)
#define STAPLE_BOTTOMLEFT  (3)
#define STAPLE_BOTTOMRIGHT (4)

#define FLAG_USE_DPI                 0x00000001
#define FLAG_SINGLE_REGION           0x00000002
#define FLAG_LEAD_REGION             0x00000004
#define FLAG_CALLBACK_REGION         0x00000008
#define FLAG_IMAGE_UNCHANGED         0x00000010
#define FLAG_USE_SIZE                0x00000020
#define FLAG_USE_COUNT               0x00000040
#define FLAG_USE_LOCATION            0x00000080
#define FLAG_FAVOR_LONG              0x00000100
#define FLAG_REMOVE_ENTIRE           0x00000200
#define FLAG_USE_GAP                 0x00000400
#define FLAG_USE_VARIANCE            0x00000800
#define FLAG_USE_DIAGONALS           0x00001000


#define SMOOTH_SINGLE_REGION         (FLAG_SINGLE_REGION)
#define SMOOTH_LEAD_REGION           (FLAG_LEAD_REGION)
#define SMOOTH_IMAGE_UNCHANGED       (FLAG_IMAGE_UNCHANGED)
#define SMOOTH_FAVOR_LONG            (FLAG_FAVOR_LONG)
#define SMOOTH_ALLFLAGS              ( \
                                       SMOOTH_SINGLE_REGION       | \
                                       SMOOTH_LEAD_REGION         | \
                                       SMOOTH_IMAGE_UNCHANGED     | \
                                       SMOOTH_FAVOR_LONG \
                                      )

#define LINE_USE_DPI                 (FLAG_USE_DPI)            
#define LINE_SINGLE_REGION           (FLAG_SINGLE_REGION)     
#define LINE_LEAD_REGION             (FLAG_LEAD_REGION)  
#define LINE_CALLBACK_REGION         (FLAG_CALLBACK_REGION) 
#define LINE_IMAGE_UNCHANGED         (FLAG_IMAGE_UNCHANGED)
#define LINE_REMOVE_ENTIRE           (FLAG_REMOVE_ENTIRE)
#define LINE_USE_GAP                 (FLAG_USE_GAP)
#define LINE_USE_VARIANCE            (FLAG_USE_VARIANCE)
#define LINE_ALLFLAGS                ( \
                                       LINE_USE_DPI                  | \
                                       LINE_SINGLE_REGION            | \
                                       LINE_LEAD_REGION              | \
                                       LINE_CALLBACK_REGION          | \
                                       LINE_REMOVE_ENTIRE            | \
                                       LINE_USE_GAP                  | \
                                       LINE_USE_VARIANCE               \
                                     )

#define BORDER_LEAD_REGION           (FLAG_LEAD_REGION) 
#define BORDER_CALLBACK_REGION       (FLAG_CALLBACK_REGION)
#define BORDER_SINGLE_REGION         (FLAG_SINGLE_REGION)
#define BORDER_IMAGE_UNCHANGED       (FLAG_IMAGE_UNCHANGED)
#define BORDER_USE_VARIANCE          (FLAG_USE_VARIANCE)
#define BORDER_ALLFLAGS              ( \
                                       BORDER_LEAD_REGION      | \
                                       BORDER_CALLBACK_REGION  | \
                                       BORDER_SINGLE_REGION    | \
                                       BORDER_IMAGE_UNCHANGED  | \
                                       BORDER_USE_VARIANCE       \
                                     )

#define INVERTEDTEXT_USE_DPI         (FLAG_USE_DPI) 
#define INVERTEDTEXT_SINGLE_REGION   (FLAG_SINGLE_REGION)  
#define INVERTEDTEXT_LEAD_REGION     (FLAG_LEAD_REGION)
#define INVERTEDTEXT_CALLBACK_REGION (FLAG_CALLBACK_REGION)
#define INVERTEDTEXT_IMAGE_UNCHANGED (FLAG_IMAGE_UNCHANGED)
#define INVERTEDTEXT_USE_DIAGONALS   (FLAG_USE_DIAGONALS)

#define INVERTEDTEXT_ALLFLAGS         ( \
                                       INVERTEDTEXT_USE_DPI             | \
                                       INVERTEDTEXT_SINGLE_REGION       | \
                                       INVERTEDTEXT_LEAD_REGION         | \
                                       INVERTEDTEXT_CALLBACK_REGION     | \
                                       INVERTEDTEXT_IMAGE_UNCHANGED     | \
                                       INVERTEDTEXT_USE_DIAGONALS         \
                                      )


#define DOT_USE_DPI                  (FLAG_USE_DPI)
#define DOT_SINGLE_REGION            (FLAG_SINGLE_REGION)
#define DOT_LEAD_REGION              (FLAG_LEAD_REGION)
#define DOT_CALLBACK_REGION          (FLAG_CALLBACK_REGION)
#define DOT_IMAGE_UNCHANGED          (FLAG_IMAGE_UNCHANGED)
#define DOT_USE_SIZE                 (FLAG_USE_SIZE)
#define DOT_USE_DIAGONALS            (FLAG_USE_DIAGONALS)

#define DOT_ALLFLAGS                 ( \
                                       DOT_USE_DPI             | \
                                       DOT_SINGLE_REGION       | \
                                       DOT_LEAD_REGION         | \
                                       DOT_CALLBACK_REGION     | \
                                       DOT_IMAGE_UNCHANGED     | \
                                       DOT_USE_SIZE            | \
                                       DOT_USE_DIAGONALS         \
                                     )


#define HOLEPUNCH_USE_DPI            (FLAG_USE_DPI)       
#define HOLEPUNCH_SINGLE_REGION      (FLAG_SINGLE_REGION)
#define HOLEPUNCH_LEAD_REGION        (FLAG_LEAD_REGION)
#define HOLEPUNCH_CALLBACK_REGION    (FLAG_CALLBACK_REGION)
#define HOLEPUNCH_IMAGE_UNCHANGED    (FLAG_IMAGE_UNCHANGED)
#define HOLEPUNCH_USE_SIZE           (FLAG_USE_SIZE)      
#define HOLEPUNCH_USE_COUNT          (FLAG_USE_COUNT)     
#define HOLEPUNCH_USE_LOCATION       (FLAG_USE_LOCATION)  

#define HOLEPUNCH_ALLFLAGS           ( \
                                       HOLEPUNCH_USE_DPI          | \
                                       HOLEPUNCH_SINGLE_REGION    | \
                                       HOLEPUNCH_LEAD_REGION      | \
                                       HOLEPUNCH_CALLBACK_REGION  | \
                                       HOLEPUNCH_IMAGE_UNCHANGED  | \
                                       HOLEPUNCH_USE_SIZE         | \
                                       HOLEPUNCH_USE_COUNT        | \
                                       HOLEPUNCH_USE_LOCATION \
                                       )


#define STAPLE_USE_DPI            (FLAG_USE_DPI)       
#define STAPLE_SINGLE_REGION      (FLAG_SINGLE_REGION)
#define STAPLE_LEAD_REGION        (FLAG_LEAD_REGION)
#define STAPLE_CALLBACK_REGION    (FLAG_CALLBACK_REGION)
#define STAPLE_IMAGE_UNCHANGED    (FLAG_IMAGE_UNCHANGED)
#define STAPLE_USE_SIZE           (FLAG_USE_SIZE)      
#define STAPLE_USE_LOCATION       (FLAG_USE_LOCATION)  

#define STAPLE_ALLFLAGS           ( \
                                       STAPLE_USE_DPI          | \
                                       STAPLE_SINGLE_REGION    | \
                                       STAPLE_LEAD_REGION      | \
                                       STAPLE_CALLBACK_REGION  | \
                                       STAPLE_IMAGE_UNCHANGED  | \
                                       STAPLE_USE_SIZE         | \
                                       STAPLE_USE_LOCATION \
                                       )

/*
   Flags for L_ConvertBitmapSignedToUnsigned
*/
#define SHIFT_ZERO_TO_CENTER	0
#define SHIFT_MIN_TO_ZERO	   1
#define SHIFT_NEG_TO_ZERO	   2

/*
   structures for Doc Imaging functions
*/

typedef struct tagSMOOTH
{
   L_INT32        iSize;              
   L_UINT32       uFlags;
   L_INT32        iLength;  
   pBITMAPHANDLE  pBitmapRegion;
   HRGN           hRgn;
} SMOOTH, L_FAR *LPSMOOTH;

typedef struct tagHOLEPUNCH
{
   L_INT32        iSize;              
   L_UINT32       uFlags;
   L_INT32        iMinHoleCount;
   L_INT32        iMaxHoleCount;
   L_INT32        iMinHoleWidth;
   L_INT32        iMinHoleHeight;
   L_INT32        iMaxHoleWidth;
   L_INT32        iMaxHoleHeight;
   L_INT32        iLocation;
   pBITMAPHANDLE  pBitmapRegion;
   HRGN           hRgn;

} HOLEPUNCH, L_FAR * LPHOLEPUNCH;

typedef struct tagSTAPLE
{
   L_INT32        iSize;              
   L_UINT32       uFlags;
   L_INT32        iMinLength;
   L_INT32        iMaxLength;
   L_INT32        iLocation;
   pBITMAPHANDLE  pBitmapRegion;
   HRGN           hRgn;

} STAPLE, L_FAR * LPSTAPLE;

typedef struct tagDOTREMOVE
{
   L_INT32        iSize;
   L_UINT32       uFlags;
   L_INT32        iMinDotWidth;
   L_INT32        iMinDotHeight;
   L_INT32        iMaxDotWidth;
   L_INT32        iMaxDotHeight;
   pBITMAPHANDLE  pBitmapRegion;
   HRGN           hRgn;
} DOTREMOVE, L_FAR *LPDOTREMOVE;

typedef struct tagINVERTEDTEXT
{
   L_INT32        iSize;
   L_UINT32       uFlags;
   L_INT32        iMinInvertWidth;
   L_INT32        iMinInvertHeight;
   L_INT32        iMinBlackPercent;
   L_INT32        iMaxBlackPercent;
   pBITMAPHANDLE  pBitmapRegion;
   HRGN           hRgn;
} INVERTEDTEXT, L_FAR *LPINVERTEDTEXT;

typedef struct tagBORDERREMOVE
{
   L_INT32       iSize;
   L_UINT32      uFlags;
   L_UINT32      uBorderToRemove;
   L_INT32       iBorderPercent;
   L_INT32       iWhiteNoiseLength;
   L_INT32       iVariance;
   HRGN          hRgn;
   pBITMAPHANDLE pBitmapRegion;
} BORDERREMOVE, L_FAR *LPBORDERREMOVE;

typedef struct tagLINEREMOVE
{
   L_INT32       iSize;
   L_UINT32      uFlags;
   L_INT32       iMinLineLength;
   L_INT32       iMaxLineWidth;
   L_INT32       iWall;
   L_INT32       iMaxWallPercent;
   L_INT32       iGapLength;
   L_INT32       iVariance;
   L_UINT32      uRemoveFlags;
   HRGN          hRgn;
   pBITMAPHANDLE pBitmapRegion;
} LINEREMOVE, L_FAR *LPLINEREMOVE;


/*
   callback typedefs
*/
typedef L_INT (pEXT_CALLBACK PICTURIZECALLBACK)(pBITMAPHANDLE, L_INT, L_INT, L_VOID L_FAR *);

typedef L_INT (pEXT_CALLBACK SMOOTHCALLBACK)
   (  
    L_UINT32       uBumpOrNick,
    L_INT32        iStartRow, 
    L_INT32        iStartCol, 
    L_INT32        iLength,
    L_UINT32       uHorV,
    L_VOID L_FAR  *pUserData
    );

typedef L_INT (pEXT_CALLBACK LINEREMOVECALLBACK)
   (
    HRGN           hRgn, 
    L_INT32        iStartRow, 
    L_INT32        iStartCol, 
    L_INT32        iLength, 
    L_VOID L_FAR  *pUserData
    );

typedef L_INT (pEXT_CALLBACK BORDERREMOVECALLBACK)
   (
    HRGN          hRgn, 
    L_UINT32      uBorderToRemove, 
    PRECT         pBoundingRect, 
    L_VOID L_FAR *pUserData
    );

typedef L_INT (pEXT_CALLBACK INVERTEDTEXTCALLBACK)
   (
    HRGN          hRgn, 
    PRECT         pBoundingRect, 
    L_INT32       iWhiteCount, 
    L_INT32       iBlackCount, 
    L_VOID L_FAR *pUserData
    );

typedef L_INT (pEXT_CALLBACK DOTREMOVECALLBACK)
   (
    HRGN          hRgn, 
    PRECT         pBoundingRect, 
    L_INT32       iWhiteCount, 
    L_INT32       iBlackCount, 
    L_VOID L_FAR *pUserData
    );

typedef L_INT (pEXT_CALLBACK HOLEPUNCHREMOVECALLBACK)
   (
    HRGN          hRgn, 
    PRECT         pBoundingRect, 
    L_INT32       iHoleIndex,  
    L_INT32       iHoleTotalCount, 
    L_INT32       iWhiteCount, 
    L_INT32       iBlackCount, 
    L_VOID L_FAR *pUserData
    );

typedef L_INT (pEXT_CALLBACK STAPLEREMOVECALLBACK)
   (
    HRGN          hRgn, 
    PRECT         pBoundingRect, 
    L_UINT32      iWhiteCount, 
    L_UINT32      iBlackCount, 
    L_VOID L_FAR *pUserData
    );


/*
   callback typedefs
*/
typedef L_INT (pEXT_CALLBACK PICTURIZECALLBACK) (pBITMAPHANDLE, L_INT, L_INT, L_VOID L_FAR *);

/*
   function prototypes
*/
L_INT EXT_FUNCTION L_AddBitmapNoise (pBITMAPHANDLE pBitmap,
                                      L_UINT uRange,
                                      L_UINT uChannel);

L_INT EXT_FUNCTION L_AutoTrimBitmap(pBITMAPHANDLE pBitmap,
                                     L_UINT uThreshold);

L_INT EXT_FUNCTION L_AverageFilterBitmap (pBITMAPHANDLE pBitmap,
                                           L_UINT uDim);

L_INT EXT_FUNCTION L_BinaryFilterBitmap (pBITMAPHANDLE pBitmap,
                                          LPBINARYFLT pFilter);

L_INT EXT_FUNCTION L_ChangeBitmapContrast (pBITMAPHANDLE pBitmap,
                                            L_INT nChange);

L_INT EXT_FUNCTION L_ChangeBitmapHue (pBITMAPHANDLE pBitmap,
                                       L_INT nAngle);

L_INT EXT_FUNCTION L_ChangeBitmapIntensity (pBITMAPHANDLE pBitmap,
                                             L_INT nChange);

L_INT EXT_FUNCTION L_ChangeBitmapSaturation (pBITMAPHANDLE pBitmap,
                                              L_INT nChange);

L_INT EXT_FUNCTION L_ColorMergeBitmap (pBITMAPHANDLE pBitmap,
                                        pBITMAPHANDLE L_FAR * ppBitmap,
                                        L_UINT32 uFlags);

L_INT EXT_FUNCTION L_ColorSeparateBitmap (pBITMAPHANDLE pBitmap,
                                           pBITMAPHANDLE L_FAR * ppBitmap,
                                           L_UINT32 uFlags);

L_INT EXT_FUNCTION L_DeskewBitmap (pBITMAPHANDLE pBitmap,
                                   L_INT32 L_FAR *pnAngle);

L_INT EXT_FUNCTION L_DeskewBitmap2 (pBITMAPHANDLE pBitmap,
                                    L_INT32 L_FAR *pnAngle,
									COLORREF crBack);

L_INT EXT_FUNCTION L_DespeckleBitmap (pBITMAPHANDLE pBitmap);

L_INT EXT_FUNCTION L_EmbossBitmap (pBITMAPHANDLE pBitmap,
                                    L_UINT uDirection,
                                    L_UINT uDepth);

L_INT EXT_FUNCTION L_GammaCorrectBitmap (pBITMAPHANDLE pBitmap,
                                          L_UINT uGamma);

L_INT EXT_FUNCTION L_GetAutoTrimRect(pBITMAPHANDLE pBitmap,
                                     L_UINT uThreshold,
                                     RECT L_FAR *pRect);

L_INT EXT_FUNCTION L_GetBitmapColorCount(pBITMAPHANDLE pBitmap,
                                         L_UINT32 L_FAR *puCount);

L_INT EXT_FUNCTION L_GetMinMaxBits(pBITMAPHANDLE pBitmap,
                                  L_INT L_FAR*pLowBit,
                                  L_INT L_FAR*pHighBit);

L_INT EXT_FUNCTION L_GetMinMaxVal(pBITMAPHANDLE pBitmap,
                                  L_INT L_FAR*pMinVal,
                                  L_INT L_FAR*pMaxVal);

L_INT EXT_FUNCTION L_HistoContrastBitmap (pBITMAPHANDLE pBitmap,
                                           L_INT nChange);

L_INT EXT_FUNCTION L_IntensityDetectBitmap (pBITMAPHANDLE pBitmap,
                                             L_UINT uLow,
                                             L_UINT uHigh);

L_INT EXT_FUNCTION L_InvertBitmap (pBITMAPHANDLE pBitmap);


L_INT EXT_FUNCTION L_MaxFilterBitmap(pBITMAPHANDLE pBitmap,
                                     L_UINT uDim);

L_INT EXT_FUNCTION L_MedianFilterBitmap (pBITMAPHANDLE pBitmap,
                                          L_UINT uDim);

L_INT EXT_FUNCTION L_MinFilterBitmap(pBITMAPHANDLE pBitmap,
                                     L_UINT uDim);

L_INT EXT_FUNCTION L_MosaicBitmap (pBITMAPHANDLE pBitmap,
                                    L_UINT uDim);

L_INT EXT_FUNCTION L_PosterizeBitmap (pBITMAPHANDLE pBitmap,
                                       L_UINT uLevels);

L_INT EXT_FUNCTION L_RemapBitmapHue(
                                    pBITMAPHANDLE pBitmap,
                                    L_UCHAR L_FAR * pMask,
                                    L_UCHAR L_FAR * pHTable,
                                    L_UCHAR L_FAR * pSTable,
                                    L_UCHAR L_FAR * pVTable);

L_INT EXT_FUNCTION L_SharpenBitmap (pBITMAPHANDLE pBitmap,
                                     L_INT nSharpness);

L_INT EXT_FUNCTION L_SolarizeBitmap (pBITMAPHANDLE pBitmap,
                                     L_UINT uThreshold);

L_INT EXT_FUNCTION L_SpatialFilterBitmap (pBITMAPHANDLE pBitmap,
                                           LPSPATIALFLT pFilter);

L_INT EXT_FUNCTION L_StretchBitmapIntensity (pBITMAPHANDLE pBitmap);


L_INT EXT_FUNCTION L_WindowLevelBitmap( pBITMAPHANDLE pBitmap,
                                 L_INT nLowBit,
                                 L_INT nHighBit,
                                 RGBQUAD L_HUGE*pLUT,
                                 L_UINT32 uLUTLength,
                                 L_INT nOrderDst);

L_INT EXT_FUNCTION L_GaussianFilterBitmap(pBITMAPHANDLE pBitmap,
                                          L_INT nRadius);

L_INT EXT_FUNCTION L_UnsharpMaskBitmap(pBITMAPHANDLE pBitmap,
                                       L_INT nAmount,
                                       L_INT nRadius,
                                       L_INT nThreshold,
                                       L_UINT uFlags);

L_INT EXT_FUNCTION L_LineProfile(pBITMAPHANDLE pBitmap,
                                 POINT FirstPoint,
                                 POINT SecondPoint,
                                 L_INT L_FAR * L_FAR * pRed,
                                 L_INT L_FAR * L_FAR * pGreen,
                                 L_INT L_FAR * L_FAR * pBlue);

L_INT EXT_FUNCTION L_GrayScaleBitmapExt(pBITMAPHANDLE pBitmap,
                                        L_INT RedFact,
                                        L_INT GreenFact,
                                        L_INT BlueFact);

L_INT EXT_FUNCTION L_SwapColors(pBITMAPHANDLE pBitmap,
                                L_INT nFlags);

L_INT EXT_FUNCTION L_BalanceColors(pBITMAPHANDLE pBitmap,
                                   BALANCING L_FAR * pRedFact,
                                   BALANCING L_FAR * pGreenFact,
                                   BALANCING L_FAR * pBlueFact);


L_INT EXT_FUNCTION L_ConvertToColoredGray(pBITMAPHANDLE pBitmap,
                                          L_INT RedFact,
                                          L_INT GreenFact,
                                          L_INT BlueFact,
                                          L_INT RedGrayFact,
                                          L_INT GreenGrayFact,
                                          L_INT BlueGrayFact);


L_INT EXT_FUNCTION L_HistoEqualizeBitmap(BITMAPHANDLE L_FAR * pBitmap,
                                         L_INT nFlag);

L_INT EXT_FUNCTION L_AlphaBlendBitmap(pBITMAPHANDLE pBitmapDst,
                                      L_INT nXDst,
                                      L_INT nYDst,
                                      L_INT nWidth,
                                      L_INT nHeight,
                                      pBITMAPHANDLE pBitmapSrc,
                                      L_INT nXSrc,
                                      L_INT nYSrc,
                                      L_INT nOpacity);

L_INT  EXT_FUNCTION L_CombineBitmapExt(pBITMAPHANDLE pBitmapDst,
                                      L_INT nXDst,
                                      L_INT nYDst,
                                      L_INT nWidth,
                                      L_INT nHeight,
                                      pBITMAPHANDLE pBitmapSrc,
                                      L_INT nXSrc,
                                      L_INT nYSrc,
                                      L_UINT uFlags);

L_INT EXT_FUNCTION L_AntiAliasBitmap(pBITMAPHANDLE pBitmap,
                                     L_UINT uThreshold,
                                     L_UINT uDim,
                                     L_UINT uFilter);

L_INT EXT_FUNCTION L_EdgeDetectorBitmap(pBITMAPHANDLE pBitmap,
                                        L_UINT  uThreshold,
                                        L_UINT  uFilter);

L_INT EXT_FUNCTION L_RemapBitmapIntensity(pBITMAPHANDLE pBitmap, L_UINT L_FAR * pLUT,
                                          L_UINT uLUTLen,L_UINT uChannel);

L_INT EXT_FUNCTION L_GetBitmapHistogram(pBITMAPHANDLE pBitmap, 
                                        L_UINT32 L_FAR * pHisto, 
                                        L_UINT uHistoLen,
                                        L_UINT uChannel);

L_INT EXT_FUNCTION L_GetUserLookUpTable(L_UINT L_FAR * pLookupTable,
                                        L_UINT uLookupLen,
                                        POINT L_FAR * apUserPoint,
                                        L_UINT uUserPointCount,
                                        L_UINT L_FAR * puPointCount);

L_INT EXT_FUNCTION L_GetFunctionalLookupTable(L_UINT L_FAR * pLookupTable,
                                              L_UINT uLookupLen,
                                              L_UINT uStart,
                                              L_UINT uEnd,
                                              L_INT  nFactor,
                                              L_UINT uFlag);

L_INT EXT_FUNCTION L_HalfToneBitmap(pBITMAPHANDLE pBitmap,
                                    L_UINT uType,
                                    L_INT32 nAngle,
                                    L_UINT uDim);

L_INT EXT_FUNCTION L_ConvertBitmapSignedToUnsigned(pBITMAPHANDLE pBitmap, 
                                                   L_UINT uShift);

L_INT EXT_FUNCTION L_IntensityDetectBitmapBinary(pBITMAPHANDLE pBitmap,
                                                 L_UINT uLow,
                                                 L_UINT uHigh,
                                                 L_UINT uChannel);

L_INT EXT_FUNCTION L_TextureAlphaBlendBitmap(pBITMAPHANDLE pBitmapDst,
                                             L_INT nXDst,
                                             L_INT nYDst,
                                             L_INT nWidth,
                                             L_INT nHeight,
                                             pBITMAPHANDLE pBitmapSrc,
                                             L_INT nXSrc,
                                             L_INT nYSrc,
                                             pBITMAPHANDLE pBitmapMask,
                                             L_INT nOpacity,
                                             pBITMAPHANDLE pBitmapUnderlay,
                                             LPPOINT pOffset);

L_INT EXT_FUNCTION L_RemapBitmapHueExt(pBITMAPHANDLE pBitmap,
                                       L_UINT L_FAR * pMask,
                                       L_UINT L_FAR * pHTable,
                                       L_UINT L_FAR * pSTable,
                                       L_UINT L_FAR * pVTable,
                                       L_UINT uLUTLen);

L_INT EXT_FUNCTION L_MultiplyBitmap (pBITMAPHANDLE pBitmap,
                                     L_UINT uFactor);

L_INT EXT_FUNCTION L_LocalHistoEqualizeBitmap(BITMAPHANDLE L_FAR * pBitmap,
                                              L_INT nWidthLen,
                                              L_INT nHeightLen,
                                              L_INT nxExt,
                                              L_INT nyExt,
                                              L_UINT uType,
                                              L_UINT uSmooth);

L_INT EXT_FUNCTION L_GetUserBuffer(L_INT  L_FAR*    pBuf,
                                   POINT L_FAR*     apUserPoint,
                                   L_UINT           uUserPointCount,
                                   L_UINT L_FAR *   puPointCount,
                                   L_UINT           uFlag);

/* These functions not ported to Windows CE */
#if !defined(_WIN32_WCE)
L_INT EXT_FUNCTION L_SmoothBitmap ( pBITMAPHANDLE pBitmap, 
                                    LPSMOOTH pSmooth,
                                    SMOOTHCALLBACK pfnCallback,
                                    L_VOID L_FAR * pUserData);

L_INT EXT_FUNCTION L_LineRemoveBitmap(   pBITMAPHANDLE pBitmap,
                                         LPLINEREMOVE pLineRemove,
                                         LINEREMOVECALLBACK pfnCallback,
                                         L_VOID L_FAR * pUserData);

L_INT EXT_FUNCTION L_BorderRemoveBitmap(   pBITMAPHANDLE pBitmap, 
                                           LPBORDERREMOVE pBorderRemove,
                                           BORDERREMOVECALLBACK pfnCallback,
                                           L_VOID L_FAR *pUserData);

L_INT EXT_FUNCTION L_InvertedTextBitmap(pBITMAPHANDLE pBitmap,
                                        LPINVERTEDTEXT pInvertedText,
                                        INVERTEDTEXTCALLBACK pfnCallback,
                                        L_VOID L_FAR *pUserData);

L_INT EXT_FUNCTION L_DotRemoveBitmap(
                                     pBITMAPHANDLE pBitmap,
                                     LPDOTREMOVE pDotRemove,
                                     DOTREMOVECALLBACK pfnCallback,
                                     L_VOID L_FAR *pUserData);


L_INT EXT_FUNCTION L_HolePunchRemoveBitmap(
                                           pBITMAPHANDLE pBitmap,
                                           LPHOLEPUNCH pHolePunch,
                                           HOLEPUNCHREMOVECALLBACK pfnCallback,
                                           L_VOID L_FAR *pUserData);


//L_StapleRemoveBitmap() reserved for future use
L_INT EXT_FUNCTION L_StapleRemoveBitmap(
                                           pBITMAPHANDLE pBitmap,
                                           LPSTAPLE pStaplePunch,
                                           STAPLEREMOVECALLBACK pfnCallback,
                                           L_VOID L_FAR *pUserData);

L_INT EXT_FUNCTION L_OilifyBitmap (pBITMAPHANDLE pBitmap,
                                     L_UINT uDim);

L_INT EXT_FUNCTION L_PicturizeBitmap(pBITMAPHANDLE pBitmap, 
                                     L_TCHAR L_FAR*pszDirName, 
                                     L_UINT uFlags,
                                     L_INT nCellWidth,
                                     L_INT nCellHeight,
                                     PICTURIZECALLBACK pfnCallback,
                                     L_VOID L_FAR*pUserData);

L_INT EXT_FUNCTION L_ContourFilterBitmap( pBITMAPHANDLE pBitmap,
                                          L_INT16 nThreshold,
                                          L_INT16 nDeltaDirection,
                                          L_INT16 nMaximumError,
                                          L_INT nOption);

L_INT EXT_FUNCTION L_ResizeBitmapRgn(pBITMAPHANDLE pBitmap,
                                     L_UINT uDim,
                                     L_UINT uFlag,
                                     L_BOOL bAsFrame);

L_INT EXT_FUNCTION L_CreateFadedMask(pBITMAPHANDLE pBitmap,
                                     pBITMAPHANDLE pMaskBitmap,
                                     L_INT nLength,
                                     L_INT nFadeRate,
                                     L_INT nStepSize,
                                     L_INT nInflate,
                                     L_UINT uFlag,
                                     L_INT nMaxGray,
                                     COLORREF crTransparent);

L_INT EXT_FUNCTION L_AddBitmaps(HBITMAPLIST hList,
                                L_UINT uFlag);

L_INT EXT_FUNCTION L_MotionBlurBitmap(pBITMAPHANDLE pBitmap,
                                      L_UINT uDim,
                                      L_INT  nAngle,
                                      L_BOOL bUnidirectional);

L_INT EXT_FUNCTION L_PicturizeBitmapList(pBITMAPHANDLE pBitmap,
                                         L_UINT uxDim,
                                         L_UINT uyDim,
                                         L_UINT uLightnessFact,
                                         HBITMAPLIST hList);

L_INT EXT_FUNCTION L_PicturizeBitmapSingle(pBITMAPHANDLE pBitmap,
                                           pBITMAPHANDLE pThumbBitmap,
                                           L_UINT uxDim,
                                           L_UINT uyDim,
                                           L_UINT uGammaFact);

L_INT EXT_FUNCTION L_AddBorder(pBITMAPHANDLE pBitmap,
                               LPADDBORDERINFO pAddBorderInfo);

L_INT EXT_FUNCTION L_AddFrame(pBITMAPHANDLE pBitmap,
                              LPADDFRAMEINFO pAddFrameInfo);

L_INT EXT_FUNCTION L_AddWeightedBitmaps(HBITMAPLIST hList,
                                        L_UINT L_FAR * puFactor,
                                        L_UINT uFlag);

L_INT EXT_FUNCTION L_AddMessageToBitmap(pBITMAPHANDLE pBitmap,
                                        LPADDMESGINFO pAddMesgInfo);

L_INT EXT_FUNCTION L_ExtractMessageFromBitmap(pBITMAPHANDLE pBitmap,
                                              LPADDMESGINFO pAddMesgInfo);

L_INT EXT_FUNCTION L_PixelateBitmap(pBITMAPHANDLE pBitmap,
                                    L_UINT        uCellWidth,
                                    L_UINT        uCellHeight,
                                    L_UINT        uOpacity,
                                    POINT         CenterPt,
                                    L_UINT        uFlags);

L_INT EXT_FUNCTION L_SpherizeBitmap(pBITMAPHANDLE pBitmap,
                                    L_INT         nValue,
                                    POINT         CenterPt,
                                    COLORREF      crFill,
                                    L_UINT        uFlags);

L_INT EXT_FUNCTION L_CylindricalBitmap(pBITMAPHANDLE pBitmap,
                                       L_INT         nValue,
                                       L_UINT        uType);

L_INT EXT_FUNCTION L_BendingBitmap(pBITMAPHANDLE pBitmap,
                                   L_INT         nValue,
                                   POINT         CenterPt,
                                   COLORREF      crFill,
                                   L_UINT        uFlags);

L_INT EXT_FUNCTION L_PunchBitmap(pBITMAPHANDLE pBitmap,
                                 L_INT         nValue,
                                 L_UINT        uStress,
                                 POINT         CenterPt,
                                 COLORREF      crFill,
                                 L_UINT        uFlags);

L_INT EXT_FUNCTION L_PolarBitmap(pBITMAPHANDLE pBitmap,
                                 COLORREF      crFill,
                                 L_UINT        uFlags);

L_INT  EXT_FUNCTION L_RadialBlurBitmap(pBITMAPHANDLE pBitmap,
                                       L_UINT        uDim,
                                       L_UINT        uStress,
                                       POINT         CenterPt);

L_INT EXT_FUNCTION L_RippleBitmap(pBITMAPHANDLE pBitmap,
                                  L_UINT        uAmplitude,
                                  L_UINT        uFrequency,
                                  L_INT         nPhase,
                                  L_UINT        uAttenuation,
                                  POINT         CenterPt,
                                  COLORREF      crFill,
                                  L_UINT        uFlag);

L_INT EXT_FUNCTION L_SwirlBitmap(pBITMAPHANDLE pBitmap,
                                 L_INT         nRotationAngle,
                                 POINT         CenterPt);

L_INT  EXT_FUNCTION L_ZoomBlurBitmap(pBITMAPHANDLE pBitmap,
                                     L_UINT        uDim,
                                     L_UINT        uStress,
                                     POINT         CenterPt);

L_INT  EXT_FUNCTION L_FreeHandWaveBitmap(pBITMAPHANDLE  pBitmap,
                                         L_INT  L_FAR * pBuf,
                                         L_UINT         uScale,
                                         L_UINT         uWaveLen,
                                         L_INT          nAngle,
                                         L_UINT         uBufSize,
                                         COLORREF       crFill,
                                         L_UINT         uFlags);

L_INT EXT_FUNCTION L_ImpressionistBitmap(pBITMAPHANDLE pBitmap,
                                         L_UINT       uHorzDim,
                                         L_UINT       uVertDim);

L_INT  EXT_FUNCTION L_RadWaveBitmap(pBITMAPHANDLE pBitmap,
                                    L_UINT   uAmplitude,
                                    L_UINT   uWaveLen,
                                    L_INT    nPhase,
                                    POINT    pCenter,
                                    COLORREF crFill,
                                    L_UINT   uFlag);

L_INT EXT_FUNCTION L_ShearBitmapExt(pBITMAPHANDLE   pBitmap,
                                    L_INT    L_FAR *pBuf,
                                    L_UINT          uScale,
                                    L_UINT          uBufSize,
                                    COLORREF        crFill,
                                    L_UINT          uFlags);

L_INT  EXT_FUNCTION L_WaveBitmap(pBITMAPHANDLE pBitmap,
                                 L_UINT   uAmplitude,
                                 L_UINT   uWaveLen,
                                 L_INT    nAngle,
                                 L_UINT   uHorzFact,
                                 L_UINT   uVertFact,
                                 COLORREF crFill,
                                 L_UINT   uFlags);

L_INT  EXT_FUNCTION L_WindBitmap(pBITMAPHANDLE pBitmap,
                                 L_UINT        uDim,
                                 L_INT         nAngle,
                                 L_UINT        uOpacity);

L_INT  EXT_FUNCTION L_ZoomWaveBitmap(pBITMAPHANDLE pBitmap,
                                     L_UINT        uAmplitude,
                                     L_UINT        uFrequency,
                                     L_INT         nPhase,
                                     L_UINT        uZomFact,
                                     POINT         pCenter,
                                     COLORREF      crFill,
                                     L_UINT        uFlag);

L_INT EXT_FUNCTION L_RemoveRedeyeBitmap(pBITMAPHANDLE pBitmap,
                                        COLORREF rcNewColor,
                                        L_UINT uThreshold,
                                        L_INT nLightness);

L_INT EXT_FUNCTION L_FeatherAlphaBlendBitmap(pBITMAPHANDLE pBitmapDst,
                                             L_INT nXDst,
                                             L_INT nYDst,
                                             L_INT nWidth,
                                             L_INT nHeight,
                                             pBITMAPHANDLE pBitmapSrc,
                                             L_INT nXSrc,
                                             L_INT nYSrc,
                                             pBITMAPHANDLE pBitmapMask);

/**** v14 functions ****/
L_INT EXT_FUNCTION L_HalfToneBitmapExt(pBITMAPHANDLE pBitmap,
                                       L_UINT        uType,
                                       L_INT32       nAngle, 
                                       L_UINT        uDim,
                                       HBITMAPLIST   hList);
#endif /* _WIN32_WCE */


#undef _HEADER_ENTRY_
#include "ltpck.h"

#endif                          /* _LTIMG_H_ */

