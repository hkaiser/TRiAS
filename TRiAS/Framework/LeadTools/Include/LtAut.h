//.....................................................................................................................
//
//  LtAut : Header file.
//
//  Copyright (C) 1991-2000 LEAD Technologies, Inc.
//  All rights reserved.
//
//.....................................................................................................................
#ifndef LTAUT_PAINT_H_INCLUDED
#define LTAUT_PAINT_H_INCLUDED

//.....................................................................................................................
// INCLUDES 
//.....................................................................................................................

//.....................................................................................................................
// CONSTANTS 
//.....................................................................................................................
#define DEF_AUTOMATION_UNDO_LEVEL         16
#define AUTOMATION_PAINT_MIN_ZOOM        -32
#define AUTOMATION_PAINT_MAX_ZOOM         32


typedef enum _AUTOMATION_MODE
{
   AUTOMATION_MODE_PAINT,
   AUTOMATION_MODE_VECTOR,
   AUTOMATION_MODE_ANNOTATION

} AUTOMATIONMODE, *pAUTOMATIONMODE ;

typedef enum 
{
   AUTOMATION_SELECT_NONE,
   AUTOMATION_SELECT_ALL

} AUTOMATIONSELECT, *pAUTOMATIONSELECT ;

//.....................................................................................................................
// TYPES
//.....................................................................................................................

//.....................................................................................................................
// PAINTING TYPES
//.....................................................................................................................
typedef struct _CONTAINERPAINTDATA
{
   pBITMAPHANDLE pBitmap ;
   HPALETTE      hRestrictionPalette ;

} CONTAINERPAINTDATA, *pCONTAINERPAINTDATA ; 


//.....................................................................................................................
// VECTOR Properties
//.....................................................................................................................
typedef struct _AUTOMATIONVECTORPROPERTIES
{
   L_INT          nSize;
   L_UINT32       dwMask;
   VECTORPEN      Pen;
   VECTORBRUSH    Brush;
   VECTORFONT     Font;
}
AUTOMATIONVECTORPROPERTIES, *pAUTOMATIONVECTORPROPERTIES; 

// Masks for AUTOMATIONVECTORPROPERTIES
typedef enum
{
   AUTOMATION_VECTOR_PEN   = 1,
   AUTOMATION_VECTOR_BRUSH = 2,
   AUTOMATION_VECTOR_FONT  = 4
}
AUTOMATION_VECTOR_MASK, *pAUTOMATION_VECTOR_MASK;


//.....................................................................................................................
// Automation handle.
//.....................................................................................................................
typedef L_VOID L_FAR*         pAUTOMATIONHANDLE ;
typedef pAUTOMATIONHANDLE*    ppAUTOMATIONHANDLE ;

typedef struct _INTERNALAUTOMATIONHANDLE
{
   //{ GENERAL STUFF

      L_INT               nSize ; 
      L_UINT32            dwSignature ; 
      AUTOMATIONMODE      nAutomationMode ; 
      L_VOID L_FAR*       pContainerList ;
      pCONTAINERHANDLE    hActiveContainer ;
      pCONTAINERCALLBACK  pContainerCallback ;
      pTOOLBARHANDLE      pToolbar ;
      pTOOLBARCALLBACK    pToolbarCallback ;
      L_INT               nCurrentTool;
      L_UINT              uUndoLevel ;

   //} GENERAL STUFF

   //{ PAINTING STUFF

      L_VOID L_FAR* pPaintAutomationObject ; 

   //} PAINTING STUFF

   //{ VECTOR STUFF

      L_VOID L_FAR *pVectorAutomationObject;

   //} VECTOR STUFF

   //{ ANNOTATION STUFF

   //} ANNOTATION STUFF

} INTERNALAUTOMATIONHANDLE, *pINTERNALAUTOMATIONHANDLE ;

//.....................................................................................................................
// USER CALLBACK FUNCTION
//.....................................................................................................................
typedef L_INT ( pEXT_CALLBACK pAUTCONTAINERCALLBACK ) ( CONTAINEREVENTTYPE nEventType,
                                                        L_VOID L_FAR *pEventData, 
                                                        L_VOID L_FAR *pUserData ) ;

typedef L_INT ( pEXT_CALLBACK pAUTOMATIONENUMCONTAINERPROC ) ( pCONTAINERHANDLE pContainer, L_VOID L_FAR *pUserData ) ;

//.....................................................................................................................
// VARIABLES 
//.....................................................................................................................

//.....................................................................................................................
// FUNCTIONS 
//.....................................................................................................................

//.....................................................................................................................
// EXPORTED FUNCTIONS 
//.....................................................................................................................

#ifdef __cplusplus
extern "C" {
#endif   // __cplusplus

// General functions.
L_INT EXT_FUNCTION L_AutIsValid            ( pAUTOMATIONHANDLE pAutomation ) ;
L_INT EXT_FUNCTION L_AutInit               ( ppAUTOMATIONHANDLE ppAutomation ) ;
L_INT EXT_FUNCTION L_AutCreate             ( pAUTOMATIONHANDLE pAutomation, AUTOMATIONMODE nMode, L_UINT32 dwFlags ) ;
L_INT EXT_FUNCTION L_AutFree               ( pAUTOMATIONHANDLE pAutomation ) ;
L_INT EXT_FUNCTION L_AutSetUndoLevel       ( pAUTOMATIONHANDLE pAutomation, L_UINT uLevel ) ;
L_INT EXT_FUNCTION L_AutGetUndoLevel       ( pAUTOMATIONHANDLE pAutomation, L_UINT *puLevel ) ;
L_INT EXT_FUNCTION L_AutCanUndo            ( pAUTOMATIONHANDLE pAutomation, L_BOOL *pfCanUndo ) ;
L_INT EXT_FUNCTION L_AutCanRedo            ( pAUTOMATIONHANDLE pAutomation, L_BOOL *pfCanRedo ) ;
L_INT EXT_FUNCTION L_AutUndo               ( pAUTOMATIONHANDLE pAutomation, L_UINT32 dwFlags ) ;
L_INT EXT_FUNCTION L_AutRedo               ( pAUTOMATIONHANDLE pAutomation, L_UINT32 dwFlags ) ;
L_INT EXT_FUNCTION L_AutSetUndoEnabled     ( pAUTOMATIONHANDLE pAutomation, L_BOOL bEnabled );
L_INT EXT_FUNCTION L_AutAddUndoNode        ( pAUTOMATIONHANDLE pAutomation, L_UINT32 dwFlags );
L_INT EXT_FUNCTION L_AutSelect             ( pAUTOMATIONHANDLE pAutomation, AUTOMATIONSELECT nSelect, L_UINT32 dwFlags ) ;
L_INT EXT_FUNCTION L_AutClipboardDataReady ( pAUTOMATIONHANDLE pAutomation, L_BOOL *pfReady ) ;
L_INT EXT_FUNCTION L_AutCut                ( pAUTOMATIONHANDLE pAutomation, L_UINT32 dwFlags ) ;
L_INT EXT_FUNCTION L_AutCopy               ( pAUTOMATIONHANDLE pAutomation, L_UINT32 dwFlags ) ;
L_INT EXT_FUNCTION L_AutPaste              ( pAUTOMATIONHANDLE pAutomation, L_UINT32 dwFlags ) ;
L_INT EXT_FUNCTION L_AutDelete             ( pAUTOMATIONHANDLE pAutomation, L_UINT32 dwFlags ) ;
L_INT EXT_FUNCTION L_AutPrint              ( pAUTOMATIONHANDLE pAutomation, L_UINT32 dwFlags ) ;

// Container Functions.
L_INT EXT_FUNCTION L_AutAddContainer       ( pAUTOMATIONHANDLE pAutomation, pCONTAINERHANDLE pContainer , L_VOID L_FAR *pModeData ) ;
L_INT EXT_FUNCTION L_AutRemoveContainer    ( pAUTOMATIONHANDLE pAutomation, pCONTAINERHANDLE pContainer ) ;
L_INT EXT_FUNCTION L_AutSetActiveContainer ( pAUTOMATIONHANDLE pAutomation, pCONTAINERHANDLE pContainer ) ;
L_INT EXT_FUNCTION L_AutGetActiveContainer ( pAUTOMATIONHANDLE pAutomation, pCONTAINERHANDLE *ppContainer ) ;
L_INT EXT_FUNCTION L_AutEnumContainers     ( pAUTOMATIONHANDLE pAutomation, pAUTOMATIONENUMCONTAINERPROC pEnumProc, L_VOID L_FAR *pUserData ) ;

// Painting Functionts.
L_INT EXT_FUNCTION L_AutSetPaintProperty  ( pAUTOMATIONHANDLE pAutomation, PAINTGROUP nGroup, const L_VOID L_FAR *pProperty ) ;
L_INT EXT_FUNCTION L_AutGetPaintProperty  ( pAUTOMATIONHANDLE pAutomation, PAINTGROUP nGroup, L_VOID L_FAR *pProperty ) ;
L_INT EXT_FUNCTION L_AutSetPaintBkColor   ( pAUTOMATIONHANDLE pAutomation, COLORREF rcBKColor ) ;
L_INT EXT_FUNCTION L_AutGetPaintBkColor   ( pAUTOMATIONHANDLE pAutomation, COLORREF *prcBKColor ) ;

// Vector Functions.
L_INT EXT_FUNCTION L_AutSetVectorProperty( pAUTOMATIONHANDLE pAutomation, const pAUTOMATIONVECTORPROPERTIES );
L_INT EXT_FUNCTION L_AutGetVectorProperty( const pAUTOMATIONHANDLE pAutomation, pAUTOMATIONVECTORPROPERTIES );
L_INT EXT_FUNCTION L_AutEditVectorObject( pAUTOMATIONHANDLE, const pVECTOROBJECT );

//Toolbar Functions.
L_INT EXT_FUNCTION L_AutSetToolbar ( pAUTOMATIONHANDLE pAutomation, pTOOLBARHANDLE pToolbar );
L_INT EXT_FUNCTION L_AutGetToolbar ( pAUTOMATIONHANDLE pAutomation, pTOOLBARHANDLE *ppToolbar ) ;

L_INT EXT_FUNCTION L_AutSetCurrentTool( pAUTOMATIONHANDLE pAutomation, L_INT nTool );
L_INT EXT_FUNCTION L_AutGetCurrentTool( pAUTOMATIONHANDLE pAutomation, L_INT *pnTool );

#ifdef __cplusplus
}
#endif   // __cplusplus

#endif  // LTAUT_PAINT_H_INCLUDED

//.....................................................................................................................
// END-OF-FILE 
//.....................................................................................................................
