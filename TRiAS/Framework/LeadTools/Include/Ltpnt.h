//.....................................................................................................................
//
//  Ltpnt : Header file.
//
//  Copyright (C) 1991-2000 LEAD Technologies, Inc.
//  All rights reserved.
//
//.....................................................................................................................
#ifndef LTPNT_H_INCLUDE
#define LTPNT_H_INCLUDE

//.....................................................................................................................
// INCLUDES 
//.....................................................................................................................
#include "ltkrn.h"
#include "ltdis.h"
#include "ltimg.h"
#include "ltfil.h"
#include "ltefx.h"

//.....................................................................................................................
// CONSTANTS 
//.....................................................................................................................
#define PAINT_BRUSH_MIN_DIAMETER              1
#define PAINT_BRUSH_MAX_DIAMETER              200
#define PAINT_BRUSH_MIN_HARDNESS              1
#define PAINT_BRUSH_MAX_HARDNESS              100
#define PAINT_BRUSH_MIN_SPACING               1
#define PAINT_BRUSH_MAX_SPACING               1000
#define PAINT_BRUSH_MIN_OPACITY               0
#define PAINT_BRUSH_MAX_OPACITY               255
#define PAINT_BRUSH_MIN_DENSITY               1
#define PAINT_BRUSH_MAX_DENSITY               100
#define PAINT_BRUSH_MIN_FADEOUT               0
#define PAINT_BRUSH_MAX_FADEOUT               10000

#define PAINT_SHAPE_MIN_BORDER_WIDTH          1
#define PAINT_SHAPE_MAX_BORDER_WIDTH          100
#define PAINT_SHAPE_MIN_ELLIPSE_WIDTH         0
#define PAINT_SHAPE_MAX_ELLIPSE_WIDTH         500
#define PAINT_SHAPE_MIN_ELLIPSE_HEIGHT        0
#define PAINT_SHAPE_MAX_ELLIPSE_HEIGHT        500
#define PAINT_SHAPE_MIN_OPACITY               0
#define PAINT_SHAPE_MAX_OPACITY               255
#define PAINT_SHAPE_MIN_GRADIENT_STEPS        2
#define PAINT_SHAPE_MAX_GRADIENT_STEPS        255

#define PAINT_REGION_MIN_TOLERANCE            0
#define PAINT_REGION_MAX_TOLERANCE            255
#define PAINT_REGION_MIN_ELLIPSE_WIDTH        0
#define PAINT_REGION_MAX_ELLIPSE_WIDTH        500
#define PAINT_REGION_MIN_ELLIPSE_HEIGHT       0
#define PAINT_REGION_MAX_ELLIPSE_HEIGHT       500

#define PAINT_FILL_MIN_OPACITY                0
#define PAINT_FILL_MAX_OPACITY                255
#define PAINT_FILL_MIN_GRADIENT_STEPS         2
#define PAINT_FILL_MAX_GRADIENT_STEPS         255
#define PAINT_FILL_MIN_TOLERANCE              0
#define PAINT_FILL_MAX_TOLERANCE              255

#define PAINT_TEXT_MIN_BORDER_WIDTH           1
#define PAINT_TEXT_MAX_BORDER_WIDTH           100
#define PAINT_TEXT_MIN_ROTATE                 0
#define PAINT_TEXT_MAX_ROTATE                 360
#define PAINT_TEXT_MIN_SCALE                  1
#define PAINT_TEXT_MAX_SCALE                  10000
#define PAINT_TEXT_MIN_OPACITY                0
#define PAINT_TEXT_MAX_OPACITY                255

#define PAINT_XFORM_MIN_ZOOM                  1
#define PAINT_XFORM_MAX_ZOOM                  10000

#define PBF_ALL                     0X00000000
#define PBF_TOUCH                   0X00000001
#define PBF_DIAMETER                0X00000002
#define PBF_HARDNESS                0X00000004
#define PBF_SPACING                 0X00000008
#define PBF_DENSITY                 0X00000010
#define PBF_OPACITY                 0X00000020
#define PBF_FADEOUTRATE             0X00000040
#define PBF_TEXTURE                 0X00000080

#define PSF_ALL                     0X00000000   
#define PSF_BACKGROUNDSTYLE         0X00000001
#define PSF_BACKGROUNDCOLOR         0X00000002
#define PSF_BACKGROUNDTILEBITMAP    0X00000004
#define PSF_BORDERSTYLE             0X00000008
#define PSF_BORDERWIDTH             0X00000010
#define PSF_BORDERBRUSHSTYLE        0X00000020
#define PSF_BORDERCOLOR             0X00000040
#define PSF_BORDERTILEBITMAP        0X00000080
#define PSF_GRADIENTSTYLE           0X00000100
#define PSF_GRADIENTSTARTCOLOR      0X00000200
#define PSF_GRADIENTENDCOLOR        0X00000400
#define PSF_GRADIENTSTEPS           0X00000800
#define PSF_BORDERENDCAP            0X00001000
#define PSF_ROUNDRECTELLIPSEWIDTH   0X00002000  
#define PSF_ROUNDRECTELLIPSEHEIGHT  0X00004000     
#define PSF_OPACITY                 0X00008000
#define PSF_TEXTURE                 0X00010000

#define PRF_ALL                     0X00000000
#define PRF_UPPERTOLERANCE          0X00000001
#define PRF_LOWERTOLERANCE          0X00000002
#define PRF_ROUNDRECTELLIPSEWIDTH   0X00000004
#define PRF_ROUNDRECTELLIPSEHEIGHT  0X00000008

#define PFF_ALL                     0X00000000
#define PFF_STYLE                   0X00000001
#define PFF_SOLIDFILLCOLOR          0X00000002
#define PFF_BACKGROUNDTILEBITMAP    0X00000004
#define PFF_GRADIENTSTYLE           0X00000008
#define PFF_GRADIENTSTARTCOLOR      0X00000010
#define PFF_GRADIENTENDCOLOR        0X00000020
#define PFF_GRADIENTSTEPS           0X00000040
#define PFF_UPPERTOLERANCE          0X00000080
#define PFF_LOWERTOLERANCE          0X00000100
#define PFF_OPACITY                 0X00000200
#define PFF_TEXTURE                 0X00000400

#define PTF_ALL                     0X00000000
#define PTF_TEXT                    0X00000001
#define PTF_FONT                    0X00000002
#define PTF_BORDERBRUSHSTYLE        0X00000004
#define PTF_BORDERWIDTH             0X00000008
#define PTF_BORDERCOLOR             0X00000010
#define PTF_BACKGROUNDSTYLE         0X00000020
#define PTF_BACKGROUNDCOLOR         0X00000040
#define PTF_BACKGROUNDTILEBITMAP    0X00000080
#define PTF_ALIGNMENT               0X00000100
#define PTF_OPACITY                 0X00000200
#define PTF_TEXTURE                 0X00000400
#define PTF_TRANSFORMINFO           0X00000800

//.....................................................................................................................
// TYPES 
//.....................................................................................................................
typedef HRGN*  pHRGN ;

typedef struct _PAINTXFORM
{
   // Zooming stuff. 
   L_INT nZoom ;   
   
   // Offset stuff.
   L_INT nXOffset ; 
   L_INT nYOffset ; 
   
} PAINTXFORM, L_FAR *pPAINTXFORM ;

typedef struct _PAINTTRANSFORM 
{
   L_INT nRotate ;
   SIZE  Scale ;
   
} PAINTTRANSFORM, L_FAR *pPAINTTRANSFORM ;

typedef enum 
{
   PAINT_ALIGNMENT_LEFT    = 0X01,
   PAINT_ALIGNMENT_HCENTER = 0X02,
   PAINT_ALIGNMENT_RIGHT   = 0X04,
   
   PAINT_ALIGNMENT_TOP     = 0X08,
   PAINT_ALIGNMENT_VCENTER = 0X10,
   PAINT_ALIGNMENT_BOTTOM  = 0X20   
      
} PAINTALIGNMENT ; 

// paint brush PAINTTOUCH shape.
typedef enum
{
   PAINT_TOUCH_SHAPE_CIRCLE
      
} PAINTTOUCHSHAPE ;  

// paint brush PAINTTOUCH contents.
typedef enum 
{
   PAINT_TOUCH_CONTENTS_COLOR,
   PAINT_TOUCH_CONTENTS_IMAGE,
      
} PAINTTOUCHCONTENTS ; 

// paint brush PAINTTOUCH color distribution.
typedef enum 
{
   PAINT_HARDNESS_DISTRB_TYPE_0,
      
} PAINTHARDNESSDISTRBTYPE ;   

// LBrush structures.
typedef struct _PAINTTOUCH
{
   PAINTTOUCHSHAPE    nShape ;
   PAINTTOUCHCONTENTS nContentsType ; 
   COLORREF           crColor ; 
   pBITMAPHANDLE      pBitmap ; 
   COLORREF           crTransparentColor ;
   
} PAINTTOUCH, L_FAR *pPAINTTOUCH ; 

typedef struct _PAINTHARDNESS
{
   PAINTHARDNESSDISTRBTYPE nDistributionType ; 
   L_INT                   nValue ;
   
} PAINTHARDNESS, L_FAR *pPAINTHARDNESS ;

typedef struct _PAINTBRUSH
{
   L_INT  nSize ; 
   
   L_UINT32      dwMask ;
   PAINTTOUCH    Touch ; 
   L_INT         nDiameter ;     
   PAINTHARDNESS Hardness ;   
   L_INT         nSpacing ;
   L_INT         nDensity ;
   L_INT         nOpacity ;   
   L_INT         nFadeOutRate ;
   pBITMAPHANDLE pTexture ; 
   
} PAINTBRUSH, L_FAR *pPAINTBRUSH ;

// SHAPE types.
typedef enum 
{
   PAINT_SHAPE_BACK_STYLE_TRANSPARENT,
   PAINT_SHAPE_BACK_STYLE_OPAQUE, 
   PAINT_SHAPE_BACK_STYLE_TILEDIMAGE, 
   PAINT_SHAPE_BACK_STYLE_GRADIENT
      
} PAINTSHAPEBACKSTYLE ; 

typedef enum 
{
   PAINT_SHAPE_BORDER_STYLE_SOLID,
   PAINT_SHAPE_BORDER_STYLE_DASH, 
   PAINT_SHAPE_BORDER_STYLE_DOT, 
   PAINT_SHAPE_BORDER_STYLE_DASHDOT, 
   PAINT_SHAPE_BORDER_STYLE_DASHDOTDOT, 
   PAINT_SHAPE_BORDER_STYLE_DASHDOTDOTDOT, 
   PAINT_SHAPE_BORDER_STYLE_DASH_GAP, 
   PAINT_SHAPE_BORDER_STYLE_DOT_GAP, 
   PAINT_SHAPE_BORDER_STYLE_DASHDOT_GAP, 
   PAINT_SHAPE_BORDER_STYLE_DASHDOTDOT_GAP, 
   PAINT_SHAPE_BORDER_STYLE_DASHDOTDOTDOT_GAP,
   PAINT_SHAPE_BORDER_STYLE_TRANSPARENT
      
} PAINTSHAPEBORDERSTYLE ;

typedef enum 
{
   PAINT_SHAPE_BORDER_BRUSH_STYLE_COLOR,
   PAINT_SHAPE_BORDER_BRUSH_STYLE_PATTERN
      
} PAINTSHAPEBORDERBRUSHSTYLE ; 

typedef enum 
{
   PAINT_SHAPE_BORDER_ENDCAP_ROUND  = PS_ENDCAP_ROUND, 
   PAINT_SHAPE_BORDER_ENDCAP_SQUARE = PS_ENDCAP_SQUARE, 
   PAINT_SHAPE_BORDER_ENDCAP_FLAT   = PS_ENDCAP_FLAT
      
} PAINTSHAPEBORDERENDCAP ; 

typedef enum 
{
   PAINT_SHAPE_GRADIENT_STYLE_NONE,
   PAINT_SHAPE_GRADIENT_STYLE_LINE_L_TO_R          = 1000,
   PAINT_SHAPE_GRADIENT_STYLE_LINE_R_TO_L          = 1001,
   PAINT_SHAPE_GRADIENT_STYLE_LINE_T_TO_B          = 1002,
   PAINT_SHAPE_GRADIENT_STYLE_LINE_B_TO_T          = 1003,
   PAINT_SHAPE_GRADIENT_STYLE_LINE_LT_TO_RB        = 1004,
   PAINT_SHAPE_GRADIENT_STYLE_LINE_LB_TO_RT        = 1005,
   PAINT_SHAPE_GRADIENT_STYLE_LINE_RT_TO_LB        = 1006,
   PAINT_SHAPE_GRADIENT_STYLE_LINE_RB_TO_LT        = 1007,
   PAINT_SHAPE_GRADIENT_STYLE_LINE2_L_AND_R_TO_C   = 1008,
   PAINT_SHAPE_GRADIENT_STYLE_LINE2_C_TO_L_AND_R   = 1009,
   PAINT_SHAPE_GRADIENT_STYLE_LINE2_T_AND_B_TO_C   = 1010,
   PAINT_SHAPE_GRADIENT_STYLE_LINE2_C_TO_T_AND_B   = 1011,
   PAINT_SHAPE_GRADIENT_STYLE_LINE2_LT_AND_RB_TO_C = 1012,
   PAINT_SHAPE_GRADIENT_STYLE_LINE2_C_TO_LT_AND_RB = 1013,
   PAINT_SHAPE_GRADIENT_STYLE_LINE2_RT_AND_LB_TO_C = 1014,
   PAINT_SHAPE_GRADIENT_STYLE_LINE2_C_TO_RT_AND_LB = 1015,
   
   PAINT_SHAPE_GRADIENT_STYLE_ANGLE_TO_LT          = 2000,
   PAINT_SHAPE_GRADIENT_STYLE_ANGLE_TO_LB          = 2001,
   PAINT_SHAPE_GRADIENT_STYLE_ANGLE_TO_RT          = 2002,
   PAINT_SHAPE_GRADIENT_STYLE_ANGLE_TO_RB          = 2003,
   PAINT_SHAPE_GRADIENT_STYLE_ANGLE_FROM_LT        = 2004,
   PAINT_SHAPE_GRADIENT_STYLE_ANGLE_FROM_LB        = 2005,
   PAINT_SHAPE_GRADIENT_STYLE_ANGLE_FROM_RT        = 2006,
   PAINT_SHAPE_GRADIENT_STYLE_ANGLE_FROM_RB        = 2007,
   
   PAINT_SHAPE_GRADIENT_STYLE_RECTANGLE_TO_C       = 3000,
   PAINT_SHAPE_GRADIENT_STYLE_RECTANGLE_FROM_C     = 3001,
   
   PAINT_SHAPE_GRADIENT_STYLE_ELLIPSE_TO_C         = 4000,
   PAINT_SHAPE_GRADIENT_STYLE_ELLIPSE_FROM_C       = 4001,
   
   PAINT_SHAPE_GRADIENT_STYLE_CONE_FROM_L          = 5000,
   PAINT_SHAPE_GRADIENT_STYLE_CONE_FROM_R          = 5001,
   PAINT_SHAPE_GRADIENT_STYLE_CONE_FROM_T          = 5002,
   PAINT_SHAPE_GRADIENT_STYLE_CONE_FROM_B          = 5003,
   PAINT_SHAPE_GRADIENT_STYLE_CONE_FROM_LT         = 5004,
   PAINT_SHAPE_GRADIENT_STYLE_CONE_FROM_LB         = 5005,
   PAINT_SHAPE_GRADIENT_STYLE_CONE_FROM_RT         = 5006,
   PAINT_SHAPE_GRADIENT_STYLE_CONE_FROM_RB         = 5007,
      
} PAINTSHAPEGRADIENTSTYLE ;

typedef struct _PAINTSHAPE
{
   L_INT  nSize; 
   
   L_UINT32                   dwMask ;
   PAINTSHAPEBACKSTYLE        nBackgroundStyle ;  
   COLORREF                   crBackgroundColor ;    
   pBITMAPHANDLE              pBackgroundTileBitmap ;
   PAINTSHAPEBORDERSTYLE      nBorderStyle ;
   L_INT                      nBorderWidth ;
   PAINTSHAPEBORDERBRUSHSTYLE nBorderBrushStyle ; 
   COLORREF                   crBorderColor ;  
   HBITMAP                    hBorderTileBitmap ;
   PAINTSHAPEGRADIENTSTYLE    nGradientStyle ;
   COLORREF                   crGradientStartColor ;       
   COLORREF                   crGradientEndColor ;         
   L_UINT                     uGradientSteps ; 
   PAINTSHAPEBORDERENDCAP     nBorderEndCap ;
   L_INT                      nRoundRectEllipseWidth ; 
   L_INT                      nRoundRectEllipseHeight ; 
   L_INT                      nOpacity ;
   pBITMAPHANDLE              pTexture ; 
   
} PAINTSHAPE, L_FAR *pPAINTSHAPE ; ;

// REGION TYPES.
typedef struct _PAINTREGION
{
   L_INT nSize; 
   
   L_UINT32 dwMask ;
   COLORREF crUpperTolerance ;
   COLORREF crLowerTolerance ; 
   L_INT    nRoundRectEllipseWidth ; 
   L_INT    nRoundRectEllipseHeight ; 
   
} PAINTREGION, L_FAR *pPAINTREGION ;  ;

// FILL TYPES.
typedef enum 
{
   PAINT_FILL_STYLE_SOLID,
   PAINT_FILL_STYLE_GRADIENT,
   PAINT_FILL_STYLE_TILEDIMAGE,
      
} PAINTFILLSTYLE ; 

typedef enum 
{
   PAINT_FILL_GRADIENT_STYLE_NONE,
   PAINT_FILL_GRADIENT_STYLE_LINE_L_TO_R           = 1000,
   PAINT_FILL_GRADIENT_STYLE_LINE_R_TO_L           = 1001,
   PAINT_FILL_GRADIENT_STYLE_LINE_T_TO_B           = 1002,
   PAINT_FILL_GRADIENT_STYLE_LINE_B_TO_T           = 1003,
   PAINT_FILL_GRADIENT_STYLE_LINE_LT_TO_RB         = 1004,
   PAINT_FILL_GRADIENT_STYLE_LINE_LB_TO_RT         = 1005,
   PAINT_FILL_GRADIENT_STYLE_LINE_RT_TO_LB         = 1006,
   PAINT_FILL_GRADIENT_STYLE_LINE_RB_TO_LT         = 1007,
   PAINT_FILL_GRADIENT_STYLE_LINE2_L_AND_R_TO_C    = 1008,
   PAINT_FILL_GRADIENT_STYLE_LINE2_C_TO_L_AND_R    = 1009,
   PAINT_FILL_GRADIENT_STYLE_LINE2_T_AND_B_TO_C    = 1010,
   PAINT_FILL_GRADIENT_STYLE_LINE2_C_TO_T_AND_B    = 1011,
   PAINT_FILL_GRADIENT_STYLE_LINE2_LT_AND_RB_TO_C  = 1012,
   PAINT_FILL_GRADIENT_STYLE_LINE2_C_TO_LT_AND_RB  = 1013,
   PAINT_FILL_GRADIENT_STYLE_LINE2_RT_AND_LB_TO_C  = 1014,
   PAINT_FILL_GRADIENT_STYLE_LINE2_C_TO_RT_AND_LB  = 1015,
   
   PAINT_FILL_GRADIENT_STYLE_ANGLE_TO_LT           = 2000,
   PAINT_FILL_GRADIENT_STYLE_ANGLE_TO_LB           = 2001,
   PAINT_FILL_GRADIENT_STYLE_ANGLE_TO_RT           = 2002,
   PAINT_FILL_GRADIENT_STYLE_ANGLE_TO_RB           = 2003,
   PAINT_FILL_GRADIENT_STYLE_ANGLE_FROM_LT         = 2004,
   PAINT_FILL_GRADIENT_STYLE_ANGLE_FROM_LB         = 2005,
   PAINT_FILL_GRADIENT_STYLE_ANGLE_FROM_RT         = 2006,
   PAINT_FILL_GRADIENT_STYLE_ANGLE_FROM_RB         = 2007,
   
   PAINT_FILL_GRADIENT_STYLE_RECTANGLE_TO_C        = 3000,
   PAINT_FILL_GRADIENT_STYLE_RECTANGLE_FROM_C      = 3001,
   
   PAINT_FILL_GRADIENT_STYLE_ELLIPSE_TO_C          = 4000,
   PAINT_FILL_GRADIENT_STYLE_ELLIPSE_FROM_C        = 4001,
   
   PAINT_FILL_GRADIENT_STYLE_CONE_FROM_L           = 5000,
   PAINT_FILL_GRADIENT_STYLE_CONE_FROM_R           = 5001,
   PAINT_FILL_GRADIENT_STYLE_CONE_FROM_T           = 5002,
   PAINT_FILL_GRADIENT_STYLE_CONE_FROM_B           = 5003,
   PAINT_FILL_GRADIENT_STYLE_CONE_FROM_LT          = 5004,
   PAINT_FILL_GRADIENT_STYLE_CONE_FROM_LB          = 5005,
   PAINT_FILL_GRADIENT_STYLE_CONE_FROM_RT          = 5006,
   PAINT_FILL_GRADIENT_STYLE_CONE_FROM_RB          = 5007,
      
} PAINTFILLGRADIENTSTYLE ;

typedef struct _PAINTFILL
{
   L_INT nSize; 
   
   L_UINT32               dwMask ;
   PAINTFILLSTYLE         nStyle ; 
   COLORREF               crSolidFillColor;             
   pBITMAPHANDLE          pBackgroundTileBitmap ;
   PAINTFILLGRADIENTSTYLE nGradientStyle ;              
   COLORREF               crGradientStartColor ;        
   COLORREF               crGradientEndColor ;       
   L_UINT                 uGradientSteps ;  
   COLORREF               crUpperTolerance ;
   COLORREF               crLowerTolerance ; 
   L_INT                  nOpacity ;
   pBITMAPHANDLE          pTexture ; 
   
} PAINTFILL, L_FAR *pPAINTFILL ;


// TEXT TYPES.
typedef enum 
{
   PAINT_TEXT_BACK_STYLE_TRANSPARENT,
   PAINT_TEXT_BACK_STYLE_OPAQUE, 
   PAINT_TEXT_BACK_STYLE_TILEDIMAGE, 
      
} PAINTTEXTBACKSTYLE ; 

typedef enum 
{
   PAINT_TEXT_BORDER_BRUSH_STYLE_TRANSPARENT,
   PAINT_TEXT_BORDER_BRUSH_STYLE_COLOR,
      
} PAINTTEXTBORDERBRUSHSTYLE ; 

typedef struct _PAINTTEXT
{
   L_INT nSize; 
   
   L_UINT32                  dwMask ;
   LPSTR                     pszText ; 
   HFONT                     hFont ; 
   PAINTTEXTBORDERBRUSHSTYLE nBorderBrushStyle ; 
   L_INT                     nBorderWidth ; 
   COLORREF                  crBorderColor ; 
   PAINTTEXTBACKSTYLE        nBackgroundStyle ; 
   COLORREF                  crBackgroundColor ; 
   pBITMAPHANDLE             pBackgroundTileBitmap ;
   PAINTALIGNMENT            nAlignment ; 
   L_INT                     nOpacity ;   
   pBITMAPHANDLE             pTexture ; 
   PAINTTRANSFORM            TransformInfo ; 
   
} PAINTTEXT, L_FAR *pPAINTTEXT ; 

typedef enum 
{
   PAINT_GROUP_BRUSH,
   PAINT_GROUP_SHAPE,
   PAINT_GROUP_REGION,
   PAINT_GROUP_FILL,
   PAINT_GROUP_TEXT
      
} PAINTGROUP ; 

//.....................................................................................................................
// TYPES 
//.....................................................................................................................
typedef L_VOID L_FAR*   pPAINTHANDLE ;
typedef pPAINTHANDLE*   ppPAINTHANDLE ;

typedef struct _PAINTHANDLE
{
   L_INT          nSize; 
   L_UINT32       dwSignature ; 
   L_VOID L_FAR*  pPaintObject ; 
   
} INTERNALPAINTHANDLE ;

typedef INTERNALPAINTHANDLE*  pINTERNALPAINTHANDLE ; 

//{UNDOCUMENTED PAINTING DATA AND OPERATIONS

typedef enum 
{
   PAINT_REF_CANVAS_NONE,
   PAINT_REF_CANVAS_DC,
   PAINT_REF_CANVAS_BITMAP
      
} PAINTREFCANVAS ;

typedef enum 
{
   PAINT_STATE_BEGIN,
   PAINT_STATE_END
      
} PAINTSTATE ; 

typedef L_INT ( pEXT_CALLBACK pPAINTCALLBACK ) ( PAINTSTATE     nState, 
                                                 PAINTREFCANVAS nRefCanvas, 
                                                 const LPRECT   prcUpdate, 
                                                 L_VOID L_FAR   *pUserData ) ;

 
L_INT EXT_FUNCTION L_PntUpdateLeadDC ( pPAINTHANDLE pPaint, 
                                       pBITMAPHANDLE pBitmap ) ;

//}UNDOCUMENTED PAINTING DATA AND OPERATIONS

//.....................................................................................................................
// FUNCTIONS 
//.....................................................................................................................

// general paint functions.
#ifdef __cplusplus
extern "C" {
#endif   // __cplusplus
   
   // DOCUMENTED FUNCTIONS.
   L_INT EXT_FUNCTION L_PntIsValid           ( pPAINTHANDLE pPaint ) ; 
   L_INT EXT_FUNCTION L_PntInit              ( ppPAINTHANDLE ppPaint ) ; 
   L_INT EXT_FUNCTION L_PntFree              ( pPAINTHANDLE pPaint ) ; 
   L_INT EXT_FUNCTION L_PntSetProperty       ( pPAINTHANDLE pPaint, PAINTGROUP nGroup, const L_VOID L_FAR *pProperty ) ;
   L_INT EXT_FUNCTION L_PntGetProperty       ( pPAINTHANDLE pPaint, PAINTGROUP nGroup, const L_VOID L_FAR *pProperty ) ;
   L_INT EXT_FUNCTION L_PntSetMetrics        ( pPAINTHANDLE pPaint, HDC UserDC, pBITMAPHANDLE pBitmap, HPALETTE hRestrictionPalette ) ;
   L_INT EXT_FUNCTION L_PntSetTransformation ( pPAINTHANDLE pPaint, pPAINTXFORM pXForm ) ;
   L_INT EXT_FUNCTION L_PntGetTransformation ( pPAINTHANDLE pPaint, pPAINTXFORM pXForm ) ;
   L_INT EXT_FUNCTION L_PntSetDCExtents      ( pPAINTHANDLE pPaint, const LPRECT prcRect ) ; 
   L_INT EXT_FUNCTION L_PntGetDCExtents      ( pPAINTHANDLE pPaint, LPRECT prcRect ) ; 
   L_INT EXT_FUNCTION L_PntSetClipRgn        ( pPAINTHANDLE pPaint, HRGN hClipRng ) ;
   L_INT EXT_FUNCTION L_PntGetClipRgn        ( pPAINTHANDLE pPaint, pHRGN phClipRng ) ; 
   L_INT EXT_FUNCTION L_PntOffsetClipRgn     ( pPAINTHANDLE pPaint, L_INT nDX, L_INT nDY ) ;
   
   // brush fucntions.
   L_INT EXT_FUNCTION L_PntBrushMoveTo ( pPAINTHANDLE pPaint, HDC UserDC, L_INT nX, L_INT nY ) ; 
   L_INT EXT_FUNCTION L_PntBrushLineTo ( pPAINTHANDLE pPaint, HDC UserDC, L_INT nX, L_INT nY ) ; 
   
   // shape functions.
   L_INT EXT_FUNCTION L_PntDrawShapeLine       ( pPAINTHANDLE pPaint, HDC UserDC, L_INT nXStart, L_INT nYStart, L_INT nEndX, L_INT nEndY ) ; 
   L_INT EXT_FUNCTION L_PntDrawShapeRectangle  ( pPAINTHANDLE pPaint, HDC UserDC, const LPRECT prcRect ) ; 
   L_INT EXT_FUNCTION L_PntDrawShapeRoundRect  ( pPAINTHANDLE pPaint, HDC UserDC, const LPRECT prcRect ) ; 
   L_INT EXT_FUNCTION L_PntDrawShapeEllipse    ( pPAINTHANDLE pPaint, HDC UserDC, const LPRECT prcRect ) ; 
   L_INT EXT_FUNCTION L_PntDrawShapePolygon    ( pPAINTHANDLE pPaint, HDC UserDC, const LPPOINT pptPoints, L_INT nCount ) ; 
   L_INT EXT_FUNCTION L_PntDrawShapePolyBezier ( pPAINTHANDLE pPaint, HDC UserDC, const LPPOINT pptPoints, L_INT nCount ) ; 
   
   // region functions.
   L_INT EXT_FUNCTION L_PntRegionRect      ( pPAINTHANDLE pPaint, HDC UserDC, const LPRECT prcRect, pHRGN phDestRgn ) ; 
   L_INT EXT_FUNCTION L_PntRegionRoundRect ( pPAINTHANDLE pPaint, HDC UserDC, const LPRECT prcRect, pHRGN phDestRgn ) ; 
   L_INT EXT_FUNCTION L_PntRegionEllipse   ( pPAINTHANDLE pPaint, HDC UserDC, const LPRECT prcRect, pHRGN phDestRgn ) ; 
   L_INT EXT_FUNCTION L_PntRegionPolygon   ( pPAINTHANDLE pPaint, HDC UserDC, const LPPOINT pptPoints, L_INT nCount, pHRGN phDestRgn ) ; 
   L_INT EXT_FUNCTION L_PntRegionSurface   ( pPAINTHANDLE pPaint, HDC UserDC, const LPPOINT pptPoint, pHRGN phDestRgn ) ; 
   L_INT EXT_FUNCTION L_PntRegionBorder    ( pPAINTHANDLE pPaint, HDC UserDC, const LPPOINT pptPoint, const COLORREF crBorderColor, pHRGN phDestRgn ) ; 
   L_INT EXT_FUNCTION L_PntRegionColor     ( pPAINTHANDLE pPaint, HDC UserDC, const COLORREF crColor, pHRGN phDestRgn ) ; 
   L_INT EXT_FUNCTION L_PntRegionTranslate ( pPAINTHANDLE pPaint, L_INT dx, L_INT dy, pHRGN phDestRgn ) ; 
   L_INT EXT_FUNCTION L_PntRegionScale     ( pPAINTHANDLE pPaint, L_INT nHScaleFactor, L_INT nVScaleFactor, PAINTALIGNMENT nAlignment, pHRGN phDestRgn ) ; 
   
   // fill functions.
   L_INT EXT_FUNCTION L_PntFillSurface      ( pPAINTHANDLE pPaint, HDC UserDC, const LPPOINT pptPoint ) ; 
   L_INT EXT_FUNCTION L_PntFillBorder       ( pPAINTHANDLE pPaint, HDC UserDC, const LPPOINT pptPoint, const COLORREF crBorderColor ) ; 
   L_INT EXT_FUNCTION L_PntFillColorReplace ( pPAINTHANDLE pPaint, HDC UserDC, const COLORREF crColor ) ; 
   
   // text functions.
   L_INT EXT_FUNCTION L_PntApplyText ( pPAINTHANDLE pPaint, HDC UserDC, const LPRECT prcRect ) ; 
   
   // paint helping functions.
   L_INT EXT_FUNCTION L_PntPickColor ( pPAINTHANDLE pPaint, HDC UserDC, L_INT nX, L_INT nY, COLORREF* pcrDestColor ) ;
   
   //{ UNDOCUMENTED FUNCTIONS.
   L_INT EXT_FUNCTION L_PntSetCallback ( pPAINTHANDLE pPaint, pPAINTCALLBACK pCallback, L_VOID L_FAR *pUserData ) ;
   //} UNDOCUMENTED FUNCTIONS.
   
#ifdef __cplusplus
}
#endif   // __cplusplus


#endif // LTPNT_H_INCLUDE
