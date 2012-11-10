//.....................................................................................................................
//
//  LtCon : Header file.
//
//  Copyright (C) 1991-2000 LEAD Technologies, Inc.
//  All rights reserved.
//
//.....................................................................................................................
#ifndef LTCONTAINER_H_INCLUDE
#define LTCONTAINER_H_INCLUDE

//.....................................................................................................................
// Constants.
//.....................................................................................................................
typedef enum 
{
   CONTAINER_EVENT_TYPE_DRAW,
   CONTAINER_EVENT_TYPE_MSG,     /* UNDOCUMENTED */
   CONTAINER_EVENT_TYPE_ERROR
      
} CONTAINEREVENTTYPE, * pCONTAINEREVENTTYPE ;

typedef enum 
{
   CONTAINER_STATE_BEGIN,
   CONTAINER_STATE_PROCESS,
   CONTAINER_STATE_END,
   CONTAINER_STATE_ABORT
      
} CONTAINERSTATE, * pCONTAINERSTATE ;

typedef enum 
{
   CONTAINER_OBJECT_TYPE_NONE,
   CONTAINER_OBJECT_TYPE_POINT,
   CONTAINER_OBJECT_TYPE_LINE,
   CONTAINER_OBJECT_TYPE_SQUARE,
   CONTAINER_OBJECT_TYPE_RECT,
   CONTAINER_OBJECT_TYPE_CIRCLE,
   CONTAINER_OBJECT_TYPE_ELLIPSE,
   CONTAINER_OBJECT_TYPE_POLYLINE,
   CONTAINER_OBJECT_TYPE_BEZIER,
   CONTAINER_OBJECT_TYPE_ARC,
   CONTAINER_OBJECT_TYPE_TEXT,
   CONTAINER_OBJECT_TYPE_COUNT = 11
      
} CONTAINEROBJECTTYPE, *pCONTAINEROBJECTTYPE ;

typedef enum 
{
   CONTAINER_ALIGNMENT_LEFT    = 0X01,
   CONTAINER_ALIGNMENT_HCENTER = 0X02,
   CONTAINER_ALIGNMENT_RIGHT   = 0X04,
      
} CONTAINERALIGNMENT ; 

#define CMF_ALL            0X0000
#define CMF_BORDERCOLOR    0X0001
#define CMF_HANDLEWIDTH    0X0002 
#define CMF_HANDLEHEIGHT   0X0004 
#define CMF_HANDLECOLOR    0X0008
#define CMF_ENABLEHANDLES  0X0010
#define CMF_LIMITS         0X0020
#define CMF_LOGTEXTFONT    0X0040
#define CMF_TEXTALIGNMENT  0X0080
#define CMF_PALETTE        0X0100

//{UNDOCUMENTED CONSTANTS
#define CM_SETOFFSET       ( WM_APP + 1 )
#define CM_SETSCALAR       ( WM_APP + 2 )
//}UNDOCUMENTED CONSTANTS

//.....................................................................................................................
// Types.
//.....................................................................................................................
typedef struct _CONTAINERMETRICS
{
   L_INT              nSize ;
   L_UINT32           dwMask ;
   COLORREF           crBorder ; 
   L_INT              nHandleWidth ;
   L_INT              nHandleHeight ;
   COLORREF           crHandle ; 
   L_BOOL             fEnableHandles ;
   RECT               rcLimits ;
   LOGFONT            logTextFont ;
   CONTAINERALIGNMENT nTextAlignment ;
   HPALETTE           hPalette ;
   
} CONTAINERMETRICS, * pCONTAINERMETRICS ; 

typedef struct _CONTAINEROBJECTDATA
{
   L_INT               nSize ;
   CONTAINEROBJECTTYPE nObjectType ;
   L_VOID L_FAR        *pObjectData ;
   CONTAINERSTATE      fState ;
   L_VOID L_FAR        *pUserData;
   
} CONTAINEROBJECTDATA, *pCONTAINEROBJECTDATA ;

typedef struct _CONTAINERPOINTDATA
{
   L_INT       nSize ;
   VECTORPOINT vptPoint ;
   
} CONTAINERPOINTDATA, L_FAR *pCONTAINERPOINTDATA ;

typedef struct _CONTAINERLINEDATA
{
   L_INT       nSize ;
   VECTORPOINT vptLine [ 2 ] ;
   
} CONTAINERLINEDATA, L_FAR *pCONTAINERLINEDATA ;

typedef struct _CONTAINERSQUAREDATA
{
   L_INT       nSize ;
   VECTORPOINT vptSquare [ 2 ] ;
   
} CONTAINERSQUAREDATA, L_FAR *pCONTAINERSQUAREDATA ;

typedef struct _CONTAINERRECTDATA
{
   L_INT       nSize ;
   VECTORPOINT vptRect [ 2 ] ;
   
} CONTAINERRECTDATA, L_FAR *pCONTAINERRECTDATA ;

typedef struct _CONTAINERCIRCLEDATA
{
   L_INT       nSize ;
   VECTORPOINT vptCircle [ 2 ] ;
   
} CONTAINERCIRCLEDATA, L_FAR *pCONTAINERCIRCLEDATA ;

typedef struct _CONTAINERELLIPSEDATA
{
   L_INT       nSize ;
   VECTORPOINT vptEllipse [ 2 ] ;
   
} CONTAINERELLIPSEDATA, L_FAR *pCONTAINERELLIPSEDATA ;

typedef struct _CONTAINERPOLYLINEDATA
{
   L_INT       nSize ;
   VECTORPOINT *pvptPoints ;
   L_INT       nPointCount ;
   
} CONTAINERPOLYLINEDATA, L_FAR *pCONTAINERPOLYLINEDATA ;

typedef struct _CONTAINERBEZIERDATA
{
   L_INT       nSize ;
   VECTORPOINT vptBezier [ 4 ] ;
   
} CONTAINERBEZIERDATA, L_FAR *pCONTAINERBEZIERDATA ;

typedef struct _CONTAINERARCDATA
{
   L_INT       nSize ;
   VECTORPOINT vptCenter ;
   L_DOUBLE    Radius ;
   L_DOUBLE    StartAngle ;
   L_DOUBLE    SweepAngle ;
   
} CONTAINERARCDATA, L_FAR *pCONTAINERARCDATA ;

typedef struct _CONTAINERTEXTDATA
{
   L_INT    nSize ;
   L_CHAR*  pszText ;
   L_UINT32 cbLength ;
   RECT     rcText ;
   
} CONTAINERTEXTDATA, L_FAR *pCONTAINERTEXTDATA ;

//{UNDOCUMENTED
typedef struct _CONTAINERMSG
{
   L_INT  nSize ;
   L_UINT message ; 
   WPARAM wParam ; 
   LPARAM lParam ; 
   
} CONTAINERMSG, *pCONTAINERMSG ;
//}UNDOCUMENTED

//.....................................................................................................................
// Container handle.
//.....................................................................................................................
typedef L_VOID L_FAR     *pCONTAINERHANDLE ;
typedef pCONTAINERHANDLE *ppCONTAINERHANDLE ;

typedef struct _INTERNALCONTAINERHANDLE
{
   L_INT         nSize; 
   L_UINT32      dwSignature ; 
   L_VOID L_FAR* pContainerObject ; 
   
} INTERNALCONTAINERHANDLE ;

typedef INTERNALCONTAINERHANDLE* pINTERNALCONTAINERHANDLE ;

//.....................................................................................................................
// user callback function.
//.....................................................................................................................
typedef L_INT ( pEXT_CALLBACK pCONTAINERCALLBACK ) ( pCONTAINERHANDLE   pContainer, 
                                                    CONTAINEREVENTTYPE nEventType,
                                                    L_VOID L_FAR       *pEventData, 
                                                    L_VOID L_FAR       *pUserData ) ;

//.....................................................................................................................
// EXPORTED FUNCTIONS 
//.....................................................................................................................

// general paint functions.
#ifdef __cplusplus
extern "C" {
#endif   // __cplusplus
   
   // general container operations funtions.
   L_INT EXT_FUNCTION L_ContainerIsValid         ( pCONTAINERHANDLE  pContainer ) ; 
   L_INT EXT_FUNCTION L_ContainerInit            ( ppCONTAINERHANDLE ppContainer ) ; 
   L_INT EXT_FUNCTION L_ContainerCreate          ( pCONTAINERHANDLE  pContainer, HWND hwndOwner ) ;
   L_INT EXT_FUNCTION L_ContainerFree            ( pCONTAINERHANDLE  pContainer ) ; 
   L_INT EXT_FUNCTION L_ContainerUpdate          ( pCONTAINERHANDLE  pContainer, LPRECT prcPaint ) ; 
   L_INT EXT_FUNCTION L_ContainerReset           ( pCONTAINERHANDLE  pContainer ) ; 
   L_INT EXT_FUNCTION L_ContainerEditObject      ( pCONTAINERHANDLE  pContainer, const pCONTAINEROBJECTDATA pObjectData ) ;
   
   // setting functions.
   L_INT EXT_FUNCTION L_ContainerSetOwner        ( pCONTAINERHANDLE pContainer, HWND hWndOwner ) ;
   L_INT EXT_FUNCTION L_ContainerSetMetrics      ( pCONTAINERHANDLE pContainer, pCONTAINERMETRICS pMetrics ) ; 
   L_INT EXT_FUNCTION L_ContainerSetOffset       ( pCONTAINERHANDLE pContainer, L_INT nXOffset, L_INT nYOffset, L_INT nZOffset ) ; 
   L_INT EXT_FUNCTION L_ContainerSetScalar       ( pCONTAINERHANDLE pContainer, pVECTORPOINT pvptScalarNum, pVECTORPOINT pvptScalarDen ) ; 
   L_INT EXT_FUNCTION L_ContainerSetObjectType   ( pCONTAINERHANDLE pContainer, CONTAINEROBJECTTYPE nObjectType ) ;
   L_INT EXT_FUNCTION L_ContainerSetObjectCursor ( pCONTAINERHANDLE pContainer, CONTAINEROBJECTTYPE nObjectType, HCURSOR hCursor ) ;
   L_INT EXT_FUNCTION L_ContainerSetEnabled      ( pCONTAINERHANDLE pContainer, L_BOOL fEnable ) ;
   L_INT EXT_FUNCTION L_ContainerSetCallback     ( pCONTAINERHANDLE pContainer, const pCONTAINERCALLBACK pCallback, L_VOID L_FAR *pUserData ) ;
   L_INT EXT_FUNCTION L_ContainerSetOwnerDraw    ( pCONTAINERHANDLE pContainer, L_BOOL fOwnerDraw, L_UINT32 dwFlags ) ;
   
   // getting functions.
   L_INT EXT_FUNCTION L_ContainerGetOwner        ( pCONTAINERHANDLE pContainer, HWND* phwndOwner ) ;
   L_INT EXT_FUNCTION L_ContainerGetMetrics      ( pCONTAINERHANDLE pContainer, pCONTAINERMETRICS pMetrics ) ;
   L_INT EXT_FUNCTION L_ContainerGetOffset       ( pCONTAINERHANDLE pContainer, L_INT *pnXOffset, L_INT *pnYOffset, L_INT *pnZOffset ) ; 
   L_INT EXT_FUNCTION L_ContainerGetScalar       ( pCONTAINERHANDLE pContainer, pVECTORPOINT pvptScalarNum, pVECTORPOINT pvptScalarDen ) ;
   L_INT EXT_FUNCTION L_ContainerGetObjectType   ( pCONTAINERHANDLE pContainer, pCONTAINEROBJECTTYPE pnObjectType ) ;
   L_INT EXT_FUNCTION L_ContainerGetObjectCursor ( pCONTAINERHANDLE pContainer, CONTAINEROBJECTTYPE nObjectType, HCURSOR* phCursor ) ;
   L_INT EXT_FUNCTION L_ContainerGetCallback     ( pCONTAINERHANDLE pContainer, pCONTAINERCALLBACK *ppCallback, L_VOID L_FAR **ppUserData ) ;
   
   // status query functions.
   L_INT EXT_FUNCTION L_ContainerIsEnabled   ( pCONTAINERHANDLE pContainer, L_BOOL* pfEnabled ) ;
   L_INT EXT_FUNCTION L_ContainerIsOwnerDraw ( pCONTAINERHANDLE pContainer, L_BOOL* pfOwnerDraw ) ;
   
   //{UNDOCUMENTED FUNCTIONS
   L_INT EXT_FUNCTION L_ContainerSetAutomationCallback ( pCONTAINERHANDLE pContainer, const pCONTAINERCALLBACK pAutomationCallback, L_VOID L_FAR *pAutomationData ) ;
   L_INT EXT_FUNCTION L_ScreenToContainer              ( pCONTAINERHANDLE pContainer, LPPOINT pptPoint ) ;
   L_INT EXT_FUNCTION L_ContainerToScreen              ( pCONTAINERHANDLE pContainer, LPPOINT pptPoint ) ;
   L_INT EXT_FUNCTION L_ContainerEnableUpdate          ( pCONTAINERHANDLE pContainer, L_BOOL fEnableUpdate ) ;
   //}UNDOCUMENTED FUNCTIONS
   
#ifdef __cplusplus
}
#endif   // __cplusplus

#endif // LTCONTAINER_H_INCLUDE

//.....................................................................................................................
// END-OF-FILE 
//.....................................................................................................................
