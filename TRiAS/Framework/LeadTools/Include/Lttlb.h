//=====================================================================================================================
//
//  LtTB : Header file.
//
//  Copyright (C) 1991-2000 LEAD Technologies, Inc.
//  All rights reserved.
//
//=====================================================================================================================
#ifndef LTTB_H_INCLUDE
#define LTTB_H_INCLUDE


//.....................................................................................................................
// Constants.
//.....................................................................................................................
#define TOOLBAR_ANNOTATION       0X0001
#define TOOLBAR_PAINT            0X0002
#define TOOLBAR_VECTOR           0X0004
#define TOOLBAR_EMPTY            0X0008

#define TOOLBAR_TOOLTIP_MAX_TEXT 255

// Toolbar position.
#define TOOLBAR_POSITION_TOP     0X0001
#define TOOLBAR_POSITION_LEFT    0X0002
#define TOOLBAR_POSITION_RIGHT   0X0004
#define TOOLBAR_POSITION_BOTTOM  0X0008

// new definitions
#define TOOLBAR_ADD_BEFORE       0x0001
#define TOOLBAR_ADD_AFTER        0x0002
#define TOOLBAR_ADD_TOOL         0x0004


//.....................................................................................................................
// NOTIFICATION IDS
//.....................................................................................................................

// PaintTools buttons notification ID's.

typedef enum 
{
   ID_TOOL_PAINT_BRUSH             = 30001,
   ID_TOOL_PAINT_SHAPE_LINE        = 30002,
   ID_TOOL_PAINT_SHAPE_RECT        = 30003,
   ID_TOOL_PAINT_SHAPE_ROUNDRECT   = 30004,
   ID_TOOL_PAINT_SHAPE_ELLIPSE     = 30005,
   ID_TOOL_PAINT_SHAPE_POLYGON     = 30006,
   ID_TOOL_PAINT_SHAPE_BEZIER      = 30007,
   ID_TOOL_PAINT_REGION_RECT       = 30008,
   ID_TOOL_PAINT_REGION_ROUNDRECT  = 30009,
   ID_TOOL_PAINT_REGION_ELLIPSE    = 30010,
   ID_TOOL_PAINT_REGION_POLYGON    = 30011,
   ID_TOOL_PAINT_REGION_SURFACE    = 30012,
   ID_TOOL_PAINT_REGION_BORDER     = 30013,
   ID_TOOL_PAINT_REGION_COLOR      = 30014,
   ID_TOOL_PAINT_FILL_SURFACE      = 30015,
   ID_TOOL_PAINT_FILL_BORDER       = 30016,
   ID_TOOL_PAINT_FILL_COLORREPLACE = 30017,
   ID_TOOL_PAINT_TEXT              = 30018,
   ID_TOOL_PAINT_ZOOM              = 30019,
   ID_TOOL_PAINT_BORDERCOLORPICKER = 30020,
   ID_TOOL_PAINT_MOVER             = 30021,
   ID_TOOL_PAINT_COUNT             = 21,

   ID_TOOL_VECTOR_NONE             = 30101,
   ID_TOOL_VECTOR_SELECT           = 30102,
   ID_TOOL_VECTOR_VERTEX           = 30103,
   ID_TOOL_VECTOR_LINE             = 30104,
   ID_TOOL_VECTOR_RECTANGLE        = 30105,
   ID_TOOL_VECTOR_POLYLINE         = 30106,
   ID_TOOL_VECTOR_POLYBEZIER       = 30107,
   ID_TOOL_VECTOR_POLYGON          = 30108,
   ID_TOOL_VECTOR_ELLIPSE          = 30109,
   ID_TOOL_VECTOR_CIRCLE           = 30110,
   ID_TOOL_VECTOR_ARC              = 30111,
   ID_TOOL_VECTOR_TEXT             = 30112,
   ID_TOOL_VECTOR_PIE              = 30113,
   ID_TOOL_VECTOR_CHORD            = 30114,
   ID_TOOL_VECTOR_RASTER           = 30115,
   ID_TOOL_VECTOR_ROTATE           = 30116,
   ID_TOOL_VECTOR_PAN              = 30117,
   ID_TOOL_VECTOR_COUNT            = 17

} TOOLBARBUTTONID ; 

//.....................................................................................................................
// Types.
//.....................................................................................................................

//.....................................................................................................................
// Toolbar Button info.
//.....................................................................................................................
typedef struct _LBUTTONINFO
{
   L_INT    nSize ;
   L_UINT   uID ;
   L_UCHAR  fsState ;
   HBITMAP  hBitmap ; 
   L_CHAR   szToolTipText [ TOOLBAR_TOOLTIP_MAX_TEXT ] ; 
   L_UINT32 dwTag ;

} LBUTTONINFO, *pLBUTTONINFO ;

//.....................................................................................................................
// Toolbar Tool info.
//.....................................................................................................................
typedef struct _LTOOLBARTOOL
{
   L_INT        nSize ;
   L_UINT       uButtonsCount ;
   pLBUTTONINFO pButtons ;
   L_UINT32     dwTag ;

} LTOOLBARTOOL, *pLTOOLBARTOOL ;

//.....................................................................................................................
// Toolbar info.
//.....................................................................................................................
typedef struct _LTOOLBARINFO
{
   L_INT         nSize ;
   L_INT         cxBitmapWidth ; 
   L_INT         cyBitmapHeight ;
   L_UINT        uToolsCount ;
   pLTOOLBARTOOL pTools ;
   L_UINT32      dwTag ;

} LTOOLBARINFO, *pLTOOLBARINFO ;

//.....................................................................................................................
// Toolbar handle.
//.....................................................................................................................
typedef L_VOID L_FAR* pTOOLBARHANDLE ;
typedef pTOOLBARHANDLE*  ppTOOLBARHANDLE ;

typedef struct _INTERNALTOOLBARHANDLE
{
   L_INT         nSize; 
   L_UINT32      dwSignature ; 
   L_VOID L_FAR* pToolbarObject ; 

} INTERNALTOOLBARHANDLE ;

typedef INTERNALTOOLBARHANDLE*   pINTERNALTOOLBARHANDLE ; 

//.....................................................................................................................
// user callback function.
//.....................................................................................................................
typedef L_INT ( pEXT_CALLBACK pTOOLBARCALLBACK ) ( pTOOLBARHANDLE  pToolbar, 
                                                   L_UINT          nButtonID,
                                                   L_UINT32        dwData,  
                                                   L_VOID L_FAR   *pUserData ) ;

//============= FUNCTIONS =============================================================================================

// general paint functions.
#ifdef __cplusplus
extern "C" {
#endif   // __cplusplus

//{DOCUMENTED FUNCTIONS

   // general toolbar operations funtions.
   L_INT EXT_FUNCTION L_TBIsValid         ( pTOOLBARHANDLE pToolbar ) ; 
   L_INT EXT_FUNCTION L_TBInit            ( ppTOOLBARHANDLE ppToolbar ) ; 
   L_INT EXT_FUNCTION L_TBFree            ( pTOOLBARHANDLE pToolbar ) ; 
   L_INT EXT_FUNCTION L_TBCreate          ( pTOOLBARHANDLE pToolbar, HWND hwndParent, LPCSTR szTitle, L_UINT32 dwFlags ) ;
   L_INT EXT_FUNCTION L_TBFreeToolbarInfo ( pTOOLBARHANDLE pToolbar, pLTOOLBARINFO pToolbarInfo ) ;

   // status query functions.
   L_INT EXT_FUNCTION L_TBIsVisible       ( pTOOLBARHANDLE pToolbar, L_BOOL *pfVisible ) ;
   L_INT EXT_FUNCTION L_TBIsButtonEnabled ( pTOOLBARHANDLE pToolbar, L_UINT uButtonID, L_BOOL *pfEnable ) ;
   L_INT EXT_FUNCTION L_TBIsButtonVisible ( pTOOLBARHANDLE pToolbar, L_UINT uButtonID, L_BOOL *pfVisible ) ;

   // setting functions.
   L_INT EXT_FUNCTION L_TBSetVisible       ( pTOOLBARHANDLE pToolbar, L_BOOL fVisible ) ; 
   L_INT EXT_FUNCTION L_TBSetPosition      ( pTOOLBARHANDLE pToolbar, LPPOINT lpptPos, L_UINT32 dwFlags ) ;
   L_INT EXT_FUNCTION L_TBSetRows          ( pTOOLBARHANDLE pToolbar, L_INT nRows ) ;
   L_INT EXT_FUNCTION L_TBSetButtonChecked ( pTOOLBARHANDLE pToolbar, L_UINT uButtonID ) ;
   L_INT EXT_FUNCTION L_TBSetButtonEnabled ( pTOOLBARHANDLE pToolbar, L_UINT uButtonID, L_BOOL fEnable ) ;
   L_INT EXT_FUNCTION L_TBSetButtonVisible ( pTOOLBARHANDLE pToolbar, L_UINT uButtonID, L_BOOL fVisible ) ;
   L_INT EXT_FUNCTION L_TBSetToolbarInfo   ( pTOOLBARHANDLE pToolbar, pLTOOLBARINFO pToolbarInfo ) ;
   L_INT EXT_FUNCTION L_TBSetCallback      ( pTOOLBARHANDLE pToolbar, const pTOOLBARCALLBACK pCallback, L_VOID L_FAR *pUserData ) ;

   // getting functions.
   L_INT EXT_FUNCTION L_TBGetPosition      ( pTOOLBARHANDLE pToolbar, LPPOINT lpptPos, L_UINT32 dwFlags ) ;
   L_INT EXT_FUNCTION L_TBGetRows          ( pTOOLBARHANDLE pToolbar, L_INT *pnRows ) ;
   L_INT EXT_FUNCTION L_TBGetButtonChecked ( pTOOLBARHANDLE pToolbar, L_INT *pnChecked ) ;
   L_INT EXT_FUNCTION L_TBGetToolbarInfo   ( pTOOLBARHANDLE pToolbar, pLTOOLBARINFO pToolbarInfo ) ;
   L_INT EXT_FUNCTION L_TBGetCallback      ( pTOOLBARHANDLE pToolbar, pTOOLBARCALLBACK *ppCallback, L_VOID L_FAR **ppUserData ) ;

   // new functions
   L_INT EXT_FUNCTION L_TBAddButton( pTOOLBARHANDLE pToolbar, L_UINT uButtonRefId, const pLBUTTONINFO pButtonInfo, L_UINT32 dwFlags );
   L_INT EXT_FUNCTION L_TBRemoveButton( pTOOLBARHANDLE pToolbar, L_UINT uButtonId );
   L_INT EXT_FUNCTION L_TBGetButtonInfo( const pTOOLBARHANDLE pToolbar, L_UINT uButtonId, pLBUTTONINFO pButtonInfo );
   L_INT EXT_FUNCTION L_TBSetButtonInfo( pTOOLBARHANDLE pToolbar, L_UINT uButtonId, const pLBUTTONINFO pButtonInfo );


//}DOCUMENTED FUNCTIONS

//{UNDOCUMENTED FUNCTIONS

   L_INT EXT_FUNCTION L_TBSetAutomationCallback ( pTOOLBARHANDLE pToolbar, const pTOOLBARCALLBACK pAutomationCallback, L_VOID L_FAR *pAutomationData ) ;

//}UNDOCUMENTED FUNCTIONS

#ifdef __cplusplus
}
#endif   // __cplusplus

#endif // LTTB_H_INCLUDE