/*----------------------------------------------------------------------------+
| LEADTOOLS for Windows -                                                     |
| Copyright (c) 1990, 1998 by LEAD Technologies, Inc.                         |
| All Rights Reserved.                                                        |
|-----------------------------------------------------------------------------|
| PROJECT   : LEAD wrappers                                                   |
| FILE NAME : tcprnt.h                                                        |
| DESC      :                                                                 |
+----------------------------------------------------------------------------*/

#ifndef  _LEAD_WRAPPER_TYPEDEF_H_
#define  _LEAD_WRAPPER_TYPEDEF_H_

/*----------------------------------------------------------------------------+
| TYPEDEFS                                                                    |
+----------------------------------------------------------------------------*/

//--BITMAPSETTINGS-------------------------------------------------------------
typedef struct tagBITMAPSETTINGS
{
   L_UINT      uDitheringMethod;
   //L_INT       nPaintContrast;
   //L_UINT      uPaintGamma;
   //L_INT       nPaintIntensity;
   L_UINT32    uDisplayModeFlagPos;
   L_UINT32    uDisplayModeFlagSet;
} BITMAPSETTINGS, L_FAR* pBITMAPSETTINGS;
#define soBITMAPSETTINGS sizeof(BITMAPSETTINGS)
//--LPLEADCREATEOBJECT---------------------------------------------------------
typedef LBase* (*LPLEADCREATEOBJECT) (L_VOID);

//--NOTIFICATION MESSAGES STRUCTURES-------------------------------------------
typedef struct tagMOUSEDATA
{  
   HWND                 hWnd;
   union
   {
      LBitmapWindow L_FAR* pBitmapWindowClass;
      LVectorWindow L_FAR* pVectorWindowClass;
   } Class;
   L_UINT32             fwKeys;
   L_INT16              xPos;
   L_INT16              yPos;
} MOUSEDATA, L_FAR* pMOUSEDATA;
#define soMOUSEDATA sizeof(MOUSEDATA)

typedef struct tagKEYDATA
{
   HWND                 hWnd;
   union
   {
      LBitmapWindow L_FAR* pBitmapWindowClass;
      LVectorWindow L_FAR* pVectorWindowClass;
   } Class;
   L_INT32              nVirtKey;
   L_INT32              lKeyData;
}KEYDATA, L_FAR* pKEYDATA;
#define soKEYDATA sizeof(KEYDATA)

typedef struct tagSIZEDATA
{
   HWND                 hWnd;
   union
   {
      LBitmapWindow L_FAR* pBitmapWindowClass;
      LVectorWindow L_FAR* pVectorWindowClass;
   } Class;
   L_INT                fwSizeType;
   L_INT16              nWidth;
   L_INT16              nHeight;
}SIZEDATA, L_FAR* pSIZEDATA;
#define soSIZEDATA sizeof(SIZEDATA)

typedef struct tagPANWINDOWDATA
{
   HWND                 hBitmapWindow;
   LBitmapWindow L_FAR* pClass;
   HWND                 hPanWindow;
   L_UINT               uFlag;
   LPRECT               prcPan;
}PANWINDOWDATA, L_FAR* pPANWINDOWDATA;
#define soPANWINDOWDATA sizeof(PANWINDOWDATA)

typedef struct tagZOOMDATA
{
   HWND                 hWnd;
   union
   {
      LBitmapWindow L_FAR* pBitmapWindowClass;
      LVectorWindow L_FAR* pVectorWindowClass;
   } Class;
   L_UINT               uZoomPercent;
}ZOOMDATA, L_FAR* pZOOMDATA;
#define soZOOMDATA sizeof(ZOOMDATA)

typedef struct tagVECTORSCALEDATA
{
   HWND                 hWnd;
   LVectorWindow L_FAR* pVectorWindowClass;
   VECTORPOINT          ScaleFactor;
}VECTORSCALEDATA, L_FAR* pVECTORSCALEDATA;
#define soVECTORSCALEDATA sizeof(VECTORSCALEDATA)

typedef struct tagPAINTEFFECTDATA
{
   HWND                 hBitmapWindow;
   LBitmapWindow L_FAR* pClass;
   L_UINT               uPass;
   L_UINT               uType;
}PAINTEFFECTDATA, L_FAR* pPAINTEFFECTDATA;
#define soPAINTEFFECTDATA sizeof(PAINTEFFECTDATA)

typedef struct tagDRAGDROPDATA
{
   HWND                 hWnd;
   union
   {
      LBitmapWindow L_FAR* pBitmapWindowClass;
      LVectorWindow L_FAR* pVectorWindowClass;
   } Class;
   L_UINT               uFilesCount;
   L_UINT               uFileNumber;
   L_CHAR L_FAR*        pszFileName;
}DRAGDROPDATA, L_FAR* pDRAGDROPDATA;
#define soDRAGDROPDATA sizeof(DRAGDROPDATA)

typedef struct tagREGIONDATA
{
   HWND                 hBitmapWindow;
   LBitmapWindow L_FAR* pClass;
   L_INT                nModificationType;
}REGIONDATA, L_FAR* pREGIONDATA;
#define soREGIONDATA sizeof(REGIONDATA)

typedef struct tagANNEVENTDATA
{
   HWND                 hBitmapAnnWindow;
   LAnnotationWindow L_FAR* pClass;
   HANNOBJECT           hAnnObject;
}ANNEVENTDATA, L_FAR* pANNEVENTDATA;
#define soANNEVENTDATA sizeof(ANNEVENTDATA)

typedef struct tagANIMATIONEVENTDATA
{
   HWND                       hAnimationWindow;
   LAnimationWindow L_FAR*    pClass;
   L_UINT                     nEvent;
   L_UINT                     nFrameNumber;
} ANIMATIONEVENTDATA, L_FAR* pANIMATIONEVENTDATA;
#define soANIMATIONEVENTDATA  sizeof(ANIMATIONEVENTDATA)

typedef struct tagSTATUSDATA
{
   DWORD   dwID;
   LBase*  pObject;
}STATUSDATA, L_FAR* pSTATUSDATA;

typedef struct tagCONLISTOPTIONS
{
   L_UINT   uColumns;      /* Columns at the control (Description & Adderss)  */
   HICON    hServerIcon;   /* Server icon                                     */
   HICON    hClientIcon;   /* Client icon                                     */
} CONLISTOPTIONS, L_FAR *pCONLISTOPTIONS;

typedef struct tagBarCodeReadOpt
{
   L_UINT32       ulSearchType;
   L_INT          nUnits;
   L_UINT32       ulFlags;
   L_INT          nMultipleMax;
   RECT           rcSearch;
   L_BOOL         bUseRgn;
   BARCODECOLOR   BarColor;
} BARCODEREADOPT, L_FAR * pBARCODEREADOPT;

#endif //_LEAD_WRAPPER_TYPEDEF_H_
/*================================================================= EOF =====*/
