/*----------------------------------------------------------------------------+
| LEADTOOLS for Windows -                                                     |
| Copyright (c) 1991-2000 LEAD Technologies, Inc.                             |
| All Rights Reserved.                                                        |
|-----------------------------------------------------------------------------|
| PROJECT   : LEAD wrappers                                                   |
| FILE NAME : ltcAnn.h                                                        |
| DESC      : Annotation classes                                              |
+----------------------------------------------------------------------------*/

#ifndef  _LEAD_ANN_H_
#define  _LEAD_ANN_H_

/*----------------------------------------------------------------------------+
| CLASSES DECLARATION                                                         |
+----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------+
| Class     : LAnnotation                                                     |
| Desc      :                                                                 |
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+
| Date      : September  1998                                                 |
+----------------------------------------------------------------------------*/
class LWRP_EXPORT LAnnotation: public LBase
{
   LEAD_DECLAREOBJECT(LAnnotation);

   public:
      L_VOID *m_extLAnnotation;
      
   protected :
      HANNOBJECT      m_hAnnObject; 
      L_UINT          m_uClassType; 

   protected : 
      L_INT    Create(L_UINT uObjectType);    
      L_UINT   GetFillPattern();
      L_INT    SetFillPattern(L_UINT uFillPattern=ANNPATTERN_SOLID,L_UINT uFlags=0);
      L_UINT   GetLineStyle();
      L_INT    SetLineStyle(L_UINT uLineStyle=ANNLINE_SOLID,L_UINT uFlags=0);
      L_DOUBLE GetLineWidth();
      L_INT    SetLineWidth(L_DOUBLE dLineWidth,L_UINT uFlags=0);
      L_INT    GetText(L_CHAR L_FAR * pText);
      L_UINT   GetTextLen();
      L_INT    SetText(L_CHAR L_FAR * pText, L_UINT uFlags=0);
      L_UINT   GetPolyFillMode();
      L_INT    SetPolyFillMode(L_UINT uPolyFillMode=ANNPOLYFILL_WINDING,
                               L_UINT uFlags=0);
      L_DOUBLE GetGaugeLength();
      L_INT    SetGaugeLength(L_DOUBLE dLength, L_UINT uFlags=0);
      L_INT    GetDistance(L_DOUBLE L_FAR*pdDistance,
                           L_DOUBLE L_FAR*pdDistance2);      
      L_UINT   GetUnit(L_CHAR L_FAR *pUnitAbbrev,L_UINT L_FAR* puPrecision);
      L_UINT   GetUnitLen();
      L_INT    SetUnit(L_UINT uUnit,L_CHAR L_FAR* pUnitAbbrev,
                       L_UINT uPrecision,L_UINT uFlags);
      L_UINT   GetPointCount();
      L_INT    GetPoints(pANNPOINT pPoints);
      L_INT    SetPoints(pANNPOINT pPoints, L_UINT uCount);
      L_INT    SetTransparent(L_BOOL  bTransparent,L_UINT uFlags=0);
      L_BOOL   GetTransparent();
      L_INT    SetDpiX(L_DOUBLE dDpiX, L_UINT uFlags=0);
      L_INT    SetDpiY(L_DOUBLE dDpiY, L_UINT uFlags=0);
      L_INT    GetBitmap(pBITMAPHANDLE pBitmap);
      L_INT    GetBitmap(LBitmapBase L_FAR* pLBitmap);
      L_INT    SetBitmap(LBitmapBase L_FAR * pBitmap, L_UINT uFlags=0);
      L_INT    SetBitmap(pBITMAPHANDLE pBitmap,L_UINT uFlags=0);
      L_INT    SetSecondaryBitmap(pBITMAPHANDLE pBitmap,L_UINT uFlags=0);
      L_INT    SetSecondaryBitmap(LBitmapBase L_FAR * pBitmap, L_UINT uFlags=0);
      L_INT    SetMetafile (HMETAFILE hMetafile, 
                                     L_UINT uType, 
                                     L_UINT uFlags=0);

      L_INT    GetMetafile (HMETAFILE L_FAR*phMetafile);

      L_INT    SetProtractorOptions(   L_BOOL   bAcute = TRUE,
                                       L_UINT   uUnit = ANNANGLE_DEGREES,
                                       L_CHAR   L_FAR*pszAbbrev = NULL,
                                       L_UINT   uPrecision = 2,
                                       L_DOUBLE dArcRadius = 30,
                                       L_UINT   uFlags = 0);

      L_INT    GetProtractorOptions(L_BOOL  L_FAR*pbAcute = NULL,
                                    L_UINT  L_FAR*puUnit = NULL,
                                    L_UINT L_FAR*puAbbrevLen = NULL,
                                    L_CHAR L_FAR*pszAbbrev = NULL,
                                    L_UINT  L_FAR*puPrecision = NULL,
                                    L_DOUBLE L_FAR*pdArcRadius = NULL);

      L_INT    GetAngle(  L_DOUBLE L_FAR*pdAngle);


      L_INT    SetShowFlags (   L_UINT uShowFlags = 0, 
                                L_UINT uFlags     = 0 );

      L_INT    GetShowFlags (   L_UINT L_FAR*puShowFlags);

      L_INT    SetNodes(   L_BOOL bShowNodes = TRUE, 
                           L_UINT uGapNodes = 0, 
                           L_UINT uFlags = 0);

      L_INT    GetNodes( L_BOOL L_FAR*pbShowNodes, 
                         L_UINT L_FAR*puGapNodes);

      L_INT    SetAutoOptions ( L_UINT uFlags);
      L_INT    GetAutoOptions ( L_UINT L_FAR *puFlags);

      L_INT    GetUndoDepth ( L_UINT L_FAR*puUsedLevels,
                              L_UINT L_FAR*puMaxLevels);


      L_INT    SetTransparentColor ( COLORREF crTransparent, 
                                             L_UINT uFlags=0);

      L_INT    GetTransparentColor ( COLORREF L_FAR * pcrTransparent);

      L_INT    GetObjectFromTag ( L_UINT32 uTag,
                                  pHANNOBJECT phTagObject,
                                  L_UINT uFlags=ANNFLAG_RECURSE | ANNFLAG_NOTCONTAINER);     
   
   public:

      LAnnotation();
      virtual ~LAnnotation();

      L_BOOL  IsCreated();
      L_BOOL  IsValid();
      HANNOBJECT GetHandle();
      L_INT              SetHandle(HANNOBJECT  hAnnObject);
      virtual L_BOOL     IsClipboardReady();
      virtual L_INT      Copy(HANNOBJECT hAnnSource);
      virtual L_INT      Copy(LAnnotation&  LAnnSource);
      LAnnotation&       operator=( LAnnotation& LAnnSource);
      virtual L_INT      CopyToClipboard(L_UINT uFormat=ANNFMT_NATIVE, 
                                         L_BOOL bSelected=FALSE,
                                         L_BOOL bEmpty=FALSE,
                                         L_BOOL fCheckMenu=FALSE);
      static  LAnnotation L_FAR* CreateAnnObject(HANNOBJECT hAnnObject);
      virtual L_INT      CutToClipboard ( L_UINT uFormat=ANNFMT_NATIVE, 
                                          L_BOOL bSelected=FALSE, 
                                          L_BOOL bEmpty=FALSE,
                                          L_BOOL fCheckMenu=FALSE);
      virtual L_INT      Define(LPPOINT pPoint, L_UINT uState);
      virtual L_INT      Destroy(L_UINT uFlags=0);
      virtual L_INT      Draw(HDC hDC,LPRECT  prcInvalid);
      virtual L_INT      Flip(pANNPOINT pCenter, L_UINT uFlags=0);
      virtual L_UINT     GetActiveState();
      virtual L_INT      GetBoundingRect(LPRECT pRect, LPRECT pRectName = NULL);    
      virtual L_INT      GetContainer(pHANNOBJECT phContainer);
      virtual L_INT      GetContainer(LAnnContainer L_FAR * pLContainer);

      virtual L_INT      GetHyperlink(L_UINT L_FAR* puType,L_UINT L_FAR* puMsg,
                                      WPARAM L_FAR* pwParam, L_CHAR L_FAR* pLink);
      virtual L_UINT     GetHyperlinkLen();
      virtual L_BOOL     IsLocked();
      virtual L_DOUBLE   GetOffsetX();
      virtual L_DOUBLE   GetOffsetY();
      virtual L_INT      GetRect(pANNRECT pRect, pANNRECT pRectName = NULL);
      virtual L_UINT     GetROP2();
      virtual L_DOUBLE   GetScalarX();
      virtual L_DOUBLE   GetScalarY();
      virtual L_BOOL     IsSelected();
      virtual L_UINT32   GetTag();
      virtual L_UINT     GetType();
      virtual L_INT      GetTopContainer(pHANNOBJECT phContainer);
      virtual L_INT      GetTopContainer(LAnnContainer L_FAR * pLContainer);
      virtual L_BOOL     IsVisible();
      virtual HWND       GetWnd();
      virtual L_INT      Lock(L_CHAR L_FAR* pLockKey, L_UINT uFlags=0);
      virtual L_INT      Move(L_DOUBLE dDx, L_DOUBLE dDy, L_UINT uFlags=0);
      virtual L_INT      Print(HDC hDC, LPRECT prcBounds);
      virtual L_INT      Realize(pBITMAPHANDLE pBitmap, LPRECT prcBounds);
      virtual L_INT      Realize(LBitmapBase L_FAR * pLBitmap, LPRECT prcBounds);
      virtual L_INT      Resize(L_DOUBLE dFactorX, L_DOUBLE dFactorY, 
                                pANNPOINT pCenter, L_UINT uFlags=0);
      virtual L_INT      Reverse(pANNPOINT pCenter, L_UINT uFlags=0);
      virtual L_INT      Remove();
      virtual L_INT      Rotate(L_DOUBLE dAngle, pANNPOINT pCenter, L_UINT uFlags=0);
      virtual L_INT      SendToBack();
      virtual L_INT      BringToFront();
      virtual L_INT      SetActiveState(L_UINT uState=ANNACTIVE_ENABLED);
      virtual L_INT      SetHyperlink(L_UINT uType, L_UINT uMsg, WPARAM wParam, 
                                      L_CHAR L_FAR* pLink, L_UINT uFlags=0);
      virtual L_INT      SetOffsetX(L_DOUBLE dOffsetX, L_UINT uFlags=0);
      virtual L_INT      SetOffsetY(L_DOUBLE dOffsetY, L_UINT uFlags=0);
      virtual L_INT      SetROP2(L_UINT uROP2=ANNROP2_COPY, L_UINT uFlags=0);
      virtual L_INT      SetRect(pANNRECT pRect);
      virtual L_INT      SetSelected(L_BOOL bSelected=TRUE, L_UINT uFlags=0);
      virtual L_INT      SetScalarX(L_DOUBLE dScalarX, L_UINT uFlags=0);
      virtual L_INT      SetScalarY(L_DOUBLE dScalarY, L_UINT uFlags=0);
      virtual L_INT      SetTag(L_UINT32 uTag, L_UINT uFlags=0);
      virtual L_UINT     GetUserMode();
      virtual L_INT      SetVisible(L_BOOL bVisible=TRUE, L_UINT uFlags=0, L_CHAR L_FAR*pUserList = NULL);

      virtual L_INT      GetName(L_BOOL * pbShowName,
                                 L_UINT * puNameLen = NULL,
                                 L_CHAR * pName = NULL,
                                 pANNPOINT pNameOffset = NULL,
                                 L_BOOL * pbNameRestrict = NULL);

      virtual L_INT      SetName(L_BOOL bShowName,
                                 L_CHAR * pText,
                                 pANNPOINT pNameOffset = NULL,
                                 L_BOOL bNameRestrict = TRUE,
                                 L_UINT uFlags = 0);

      virtual L_INT      ShowLockedIcon (L_BOOL bShow=TRUE, L_UINT uFlags=0);
      virtual L_INT      Unlock(L_CHAR L_FAR* pUnlockKey, L_UINT uFlags=0);
      virtual L_BOOL   IsFontBold();
      virtual L_BOOL   IsFontItalic();
      virtual L_INT    GetFontName(L_CHAR L_FAR * pFontName);
      virtual L_UINT   GetFontNameLen();
      virtual L_DOUBLE GetFontSize();
      virtual L_BOOL   IsFontStrikeThrough();
      virtual L_BOOL   IsFontUnderline();
      virtual L_INT    SetFontBold(L_BOOL bFontBold=TRUE, L_UINT uFlags=0);
      virtual L_INT    SetFontItalic(L_BOOL bFontItalic=TRUE, L_UINT uFlags=0);
      virtual L_INT    SetFontName(L_CHAR L_FAR * pFontName, L_UINT uFlags=0);
      virtual L_INT    SetFontSize(L_DOUBLE dFontSize, L_UINT uFlags=0);
      virtual L_INT    SetFontStrikeThrough(L_BOOL bFontStrikeThrough=TRUE, 
                                    L_UINT uFlags=0);
      virtual L_INT    SetFontUnderline(L_BOOL bFontUnderline=TRUE,L_UINT uFlags=0);
      virtual COLORREF GetForeColor();
      virtual L_INT    SetForeColor(COLORREF crFore=RGB(255,0,0),L_UINT uFlags=0);
      virtual COLORREF GetBackColor();
      virtual L_INT    SetBackColor(COLORREF crBack=RGB(0,0,0),L_UINT uFlags=0);
      virtual L_UINT   GetFillMode();
      virtual L_INT    SetFillMode(L_UINT uFillMode=ANNMODE_TRANSPARENT,L_UINT uFlags=0);

      virtual L_INT    SetAutoMenuItemEnable( L_INT nObjectType, 
                                              L_UINT uItem, 
                                              L_UINT uEnable, 
                                              L_UINT uFlags,
                                              L_CHAR L_FAR*pUserList);

      virtual L_INT    GetAutoMenuItemEnable( L_INT nObjectType, 
                                              L_UINT uItem, 
                                              L_UINT L_FAR*puEnable);

      virtual L_INT    SetAutoMenuState( L_INT nObjectType, 
                                         L_UCHAR L_FAR*pEnable, 
                                         L_UCHAR L_FAR*pEnableFlags, 
                                         L_UINT uBits, 
                                         L_UINT uFlags);

      virtual L_INT    GetAutoMenuState( L_INT nObjectType, 
                                         L_UCHAR L_FAR*pEnable, 
                                         L_UCHAR L_FAR*pEnableFlags, 
                                         L_UINT uBits); 

      virtual L_INT    SetUser(  L_CHAR L_FAR*pOldUser, 
                                 L_CHAR L_FAR*pNewUser, 
                                 L_UINT uFlags=0);
      
      virtual L_INT    Group ( L_UINT uFlags, 
                               L_CHAR L_FAR*pUserList=NULL);

      virtual L_INT    Ungroup ( L_UINT uFlags, 
                               L_CHAR L_FAR*pUserList=NULL);

      virtual L_INT    GetRgnHandle(HRGN L_FAR *phRgn,pRGNXFORM pXForm=NULL);
      virtual L_INT    GetArea( L_UINT32 L_FAR*puCount);
      virtual L_INT    SetAutoDefaults( HANNOBJECT hAutoObject, L_UINT uFlags=0);
      virtual L_INT    SetAutoDefaults( LAnnAutomation &AnnAuto, L_UINT uFlags=0);

      static  L_INT    SetPredefinedMetafile(L_UINT uType, HMETAFILE hMetafile);
      static  L_INT    GetPredefinedMetafile(L_UINT uType,
                                             HMETAFILE * phMetafile,
                                             L_BOOL * pbEnhanced);
};

/*----------------------------------------------------------------------------+
| Class     : LAnnAutomation                                                  |
| Desc      :                                                                 |
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+
| Date      : 27 may 1998                                                     |
+----------------------------------------------------------------------------*/
class LWRP_EXPORT LAnnAutomation: public LAnnotation     
{
   LEAD_DECLAREOBJECT(LAnnAutomation);
   
   public:
      L_VOID *m_extLAnnAutomation;
      
   public : 
      LAnnAutomation(L_BOOL bCreate=TRUE);
      LAnnAutomation(HANNOBJECT& hAutomation);
      virtual ~LAnnAutomation();

      virtual  L_INT    Create();
      virtual  L_INT    GetAutoContainer(pHANNOBJECT phContainer);
      virtual  L_INT    GetAutoContainer(LAnnContainer L_FAR * pLContainer);
      virtual  L_BOOL   IsAutoDrawEnabled();
      virtual  L_BOOL   IsAutoMenuEnabled();
      virtual  L_INT    GetAutoText(L_UINT uItem, L_CHAR L_FAR *pText);
      virtual  L_UINT   GetAutoTextLen (L_UINT uItem);
      virtual  L_DOUBLE GetDpiX();
      virtual  L_DOUBLE GetDpiY();
      virtual  L_BOOL   IsHyperlinkMenuEnabled();
      virtual  L_UINT   GetTool();
      virtual  L_INT    SetTransparent(L_BOOL  bTransparent,L_UINT uFlags=0);
      virtual  L_INT    SetAutoContainer(HANNOBJECT hContainer);
      virtual  L_INT    SetAutoContainer(LAnnContainer L_FAR * pLContainer);
      virtual  L_INT    SetAutoDrawEnabled(L_BOOL bEnable=TRUE);
      virtual  L_INT    SetAutoMenuEnabled(L_BOOL bEnable=TRUE);
      virtual  L_INT    SetAutoText(L_UINT uItem, L_CHAR L_FAR *pText);
      virtual  L_INT    SetDpiX(L_DOUBLE dDpiX, L_UINT uFlags=0);
      virtual  L_INT    SetDpiY(L_DOUBLE dDpiY, L_UINT uFlags=0);
      virtual  L_INT    SetHyperlinkMenuEnabled(L_BOOL bEnable=TRUE, L_UINT uFlags=0);
      virtual  L_INT    SetTool(L_UINT uTool=ANNTOOL_SELECT);
      virtual  L_INT    SetUndoDepth(L_UINT uLevels=5);
      virtual  L_INT    Undo(L_UINT uLevels=1);
      virtual  L_INT    SetBitmapDpiX(L_DOUBLE dDpiX, L_UINT uFlags=0);
      virtual  L_INT    SetBitmapDpiY(L_DOUBLE dDpiY, L_UINT uFlags=0);
      virtual  L_DOUBLE GetBitmapDpiX();
      virtual  L_DOUBLE GetBitmapDpiY();
      virtual  L_UINT   GetFillPattern();
      virtual  L_INT    SetFillPattern(L_UINT uFillPattern=ANNPATTERN_SOLID, 
                                       L_UINT uFlags=0);
      virtual  L_UINT   GetLineStyle();
      virtual  L_INT    SetLineStyle(L_UINT uLineStyle=ANNLINE_SOLID, 
                                     L_UINT uFlags=0);
      virtual  L_DOUBLE GetLineWidth();
      virtual  L_INT    SetLineWidth(L_DOUBLE dLineWidth,L_UINT uFlags=0);
      virtual  L_INT    GetText(L_CHAR L_FAR * pText);
      virtual  L_UINT   GetTextLen();
      virtual  L_INT    SetText(L_CHAR L_FAR * pText,L_UINT uFlags=0);
      virtual  L_UINT   GetPolyFillMode();
      virtual  L_INT    SetPolyFillMode(L_UINT uPolyFillMode=ANNPOLYFILL_WINDING, 
                                        L_UINT uFlags=0);
      virtual  L_DOUBLE GetGaugeLength();
      virtual  L_INT    SetGaugeLength(L_DOUBLE dLength, L_UINT uFlags=0);
      virtual  L_INT    GetDistance(L_DOUBLE L_FAR*pdDistance,
                                    L_DOUBLE L_FAR*pdDistance2=0);      
      virtual  L_UINT   GetUnit(L_CHAR L_FAR* pUnitAbbrev, L_UINT L_FAR* puPrecision);
      virtual  L_UINT   GetUnitLen();
      virtual  L_INT    SetUnit(L_UINT uUnit,
                                L_CHAR L_FAR* pUnitAbbrev,
                                L_UINT uPrecision,L_UINT uFlags=0);

      virtual  L_INT    SetAutoOptions ( L_UINT uFlags);
      virtual  L_INT    GetAutoOptions ( L_UINT L_FAR *puFlags);

      virtual L_INT    GetUndoDepth ( L_UINT L_FAR*puUsedLevels,
                                      L_UINT L_FAR*puMaxLevels);

      virtual L_INT    SetTransparentColor ( COLORREF crTransparent, 
                                             L_UINT uFlags=0);

      virtual L_INT    GetTransparentColor ( COLORREF L_FAR * pcrTransparent);

      virtual L_INT    SetNodes( L_BOOL bShowNodes = TRUE, 
                                 L_UINT uGapNodes = 0, 
                                 L_UINT uFlags = 0);

      virtual L_INT    GetNodes( L_BOOL L_FAR*pbShowNodes, 
                                 L_UINT L_FAR*puGapNodes);

      virtual  L_INT    SetShowFlags ( L_UINT uShowFlags = 0, 
                                       L_UINT uFlags     = 0 );

      virtual  L_INT    GetShowFlags ( L_UINT L_FAR*puShowFlags);


};
/*----------------------------------------------------------------------------+
| Class     : LAnnContainer                                                   |
| Desc      :                                                                 |
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+
| Date      : September  1998                                                 |
+----------------------------------------------------------------------------*/
class LWRP_EXPORT LAnnContainer: public LAnnotation      
{
   LEAD_DECLAREOBJECT(LAnnContainer);

   public:
      L_VOID *m_extLAnnContainer;
      
   private :
      static   L_INT  EXT_CALLBACK EnumerateCS (HANNOBJECT hObject,L_VOID L_FAR * pUserData);
   protected :
      virtual  L_INT    EnumerateCallBack(HANNOBJECT hObject);
   public : 
      LAnnContainer();
      LAnnContainer(HWND hWnd,pANNRECT pRect,L_BOOL bVisible);
      LAnnContainer(HANNOBJECT& hContainer);
      virtual ~LAnnContainer();

      virtual L_INT     Create(HWND hWnd, pANNRECT pRect, L_BOOL bVisible=FALSE);
      virtual L_INT     Insert (LAnnotation& LAnnObject,
                                L_BOOL bStripContainer=FALSE);
      virtual L_INT     SetWnd(HWND hWnd);
      virtual  L_INT    SetLineStyle(L_UINT uLineStyle=ANNLINE_SOLID, 
                                     L_UINT uFlags=0);
      virtual  L_INT    SetLineWidth(L_DOUBLE dLineWidth,L_UINT uFlags=0);
      virtual  L_INT    SetPolyFillMode(L_UINT uPolyFillMode=ANNPOLYFILL_WINDING,
                                        L_UINT uFlags=0);
      virtual  L_INT    SetFillPattern(L_UINT uFillPattern=ANNPATTERN_SOLID, 
                                       L_UINT uFlags=0);
      virtual  L_INT    SetText(L_CHAR L_FAR * pText,L_UINT uFlags=0);
      virtual  L_INT    SetBitmap(pBITMAPHANDLE pBitmap, L_UINT uFlags=0);
      virtual  L_INT    SetBitmap(LBitmapBase L_FAR* pBitmap, L_UINT uFlags=0);
      virtual  L_INT    SetSecondaryBitmap(pBITMAPHANDLE pBitmap,L_UINT uFlags);
      virtual  L_INT    SetSecondaryBitmap(LBitmapBase L_FAR * pBitmap, L_UINT uFlags);


      virtual  L_INT    SetDpiX(L_DOUBLE dDpiX, L_UINT uFlags=0);
      virtual  L_INT    SetDpiY(L_DOUBLE dDpiY, L_UINT uFlags=0);
      virtual  L_INT    SetTransparent(L_BOOL  bTransparent,L_UINT uFlags=0);
      virtual L_INT     CopyFromClipboard (HWND hWnd);
      virtual L_INT     Enumerate(L_UINT uFlags=ANNFLAG_SELECTED, L_CHAR L_FAR*pUserList=NULL);
      virtual L_UINT    GetSelectCount();
      virtual L_INT     GetSelectItems(pHANNOBJECT pItems);
      virtual L_INT     GetSelectRect(LPRECT pRect);
      virtual L_INT     SelectRect(LPRECT pRect);
      virtual L_INT     SelectPoint(LPPOINT pPoint);
      virtual L_INT     HitTest (LPPOINT pPoint, L_UINT L_FAR * puResult, pHANNOBJECT phObjectHit);
      virtual LAnnotation  L_FAR *  HitTest(LPPOINT pPoint,L_UINT L_FAR * puResult);
      virtual L_INT     GetItem(pHANNOBJECT phItem);
      virtual LAnnotation L_FAR *  GetItem();
      virtual L_INT     Save(L_CHAR L_FAR * pFile, L_UINT uFormat = ANNFMT_NATIVE, 
                             L_BOOL bSelected = TRUE, pSAVEFILEOPTION pSaveOptions = NULL);
      virtual L_UINT32  SaveOffset(L_INT fd, L_INT32 nOffset,
                                   L_UINT uFormat = ANNFMT_NATIVE, 
                                   L_BOOL bSelected = TRUE,
                                   pSAVEFILEOPTION pSaveOptions = NULL);
      
      virtual L_INT     SaveTag(L_UINT uFormat = ANNFMT_TIFFTAG,L_BOOL bSelected = FALSE);
      
      virtual L_INT     SaveMemory(L_UINT uFormat, L_BOOL bSelected, 
                                   HGLOBAL L_FAR * phMem,
                                   L_UINT32 L_FAR * puMemSize,
                                   pSAVEFILEOPTION pSaveOptions = NULL);
      virtual L_INT     Load(L_CHAR L_FAR * pFile, pLOADFILEOPTION pLoadFileOption=NULL);
      virtual L_INT     LoadOffset(L_INT fd,L_INT32 nOffset,L_UINT32 nLength,pLOADFILEOPTION pLoadFileOption=NULL);
      virtual L_INT     LoadMemory(L_UCHAR L_FAR * pMem, L_UINT32 uMemSize);
      virtual L_INT     Realize(pBITMAPHANDLE pBitmap, 
                                LPRECT prcBounds,L_BOOL bRedactOnly=TRUE);
      virtual L_INT     Realize(LBitmapBase L_FAR * pBitmap, LPRECT prcBounds,
                                L_BOOL bRedactOnly=TRUE);
      virtual L_INT     Unrealize(pBITMAPHANDLE pBitmap, LPRECT prcBounds, 
                                  L_BOOL bSelected=TRUE);
      virtual L_INT     Unrealize(LBitmapBase L_FAR * pBitmap, LPRECT prcBounds, 
                                  L_BOOL bSelected=TRUE);

      virtual L_INT     SetUserMode(L_UINT uMode=ANNUSER_DESIGN);
      virtual L_DOUBLE GetLineWidth();
      virtual L_UINT   GetLineStyle();
      virtual L_UINT   GetFillPattern();

      virtual L_INT    SetTransparentColor ( COLORREF crTransparent, 
                                             L_UINT uFlags=ANNFLAG_RECURSE | ANNFLAG_NOTCONTAINER);

      virtual L_INT    GetObjectFromTag( L_UINT32 uTag,
                                         pHANNOBJECT phTagObject,
                                         L_UINT uFlags=ANNFLAG_RECURSE | ANNFLAG_NOTCONTAINER);

      virtual L_INT    SetNodes( L_BOOL bShowNodes = TRUE, 
                                 L_UINT uGapNodes = 0, 
                                 L_UINT uFlags = ANNFLAG_RECURSE | ANNFLAG_NOTCONTAINER);

      virtual L_INT    FileInfo(L_CHAR * pszFile, pANNFILEINFO pAnnFileInfo);

      virtual L_INT    FileInfoMemory(L_UCHAR * pMem, L_UINT32 uMemSize, pANNFILEINFO pAnnFileInfo);

      virtual L_INT    FileInfoOffset(L_INT fd, pANNFILEINFO pAnnFileInfo);

      virtual L_INT    DeletePage(L_CHAR * pszFile, L_INT32 nPage);

      virtual L_INT    DeletePageMemory(HGLOBAL hMem, L_UINT32 * puMemSize, L_INT32 nPage);

      virtual L_INT    DeletePageOffset(L_INT fd, L_INT32 nOffset, L_INT32 nPage);

};

/*----------------------------------------------------------------------------+
| Class     : LAnnText                                                        |
| Desc      :                                                                 |
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+
| Date      : September  1998                                                 |
+----------------------------------------------------------------------------*/
class LWRP_EXPORT LAnnText: public LAnnotation     
{
   LEAD_DECLAREOBJECT(LAnnText);

   public:
      L_VOID *m_extLAnnText;
      
   public : 
      LAnnText(L_BOOL bCreate=TRUE);
      LAnnText (HANNOBJECT& hText);
      virtual ~LAnnText();

      virtual L_INT     Create();
      virtual L_INT     GetText(L_CHAR L_FAR * pText);
      virtual L_UINT    GetTextLen();
      virtual L_INT     SetText(L_CHAR L_FAR * pText,L_UINT uFlags=0);
};
/*----------------------------------------------------------------------------+
| Class     : LAnnStamp                                                       |
| Desc      :                                                                 |
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+
| Date      : September  1998                                                 |
+----------------------------------------------------------------------------*/
class LWRP_EXPORT LAnnStamp: public LAnnotation    
{
   LEAD_DECLAREOBJECT(LAnnStamp);

   public:
      L_VOID *m_extLAnnStamp;
      
   public : 
      LAnnStamp(L_BOOL bCreate=TRUE);
      LAnnStamp(HANNOBJECT& hStamp);
      virtual ~LAnnStamp();

      virtual L_INT     Create();
      virtual L_INT     GetBitmap(pBITMAPHANDLE pBitmap);
      virtual L_INT     GetBitmap(LBitmapBase L_FAR * pBitmap);
      virtual L_INT     SetBitmap(pBITMAPHANDLE pBitmap, L_UINT uFlags=0);
      virtual L_INT     SetBitmap(LBitmapBase L_FAR * pBitmap, L_UINT uFlags=0);
      virtual L_INT     SetTransparent(L_BOOL  bTransparent,L_UINT uFlags=0);
      virtual L_BOOL    GetTransparent();
      virtual L_UINT    GetFillPattern();
      virtual L_INT     SetFillPattern(L_UINT uFillPattern=ANNPATTERN_SOLID, 
                                       L_UINT uFlags=0);
      virtual L_UINT    GetLineStyle();
      virtual L_INT     SetLineStyle(L_UINT uLineStyle=ANNLINE_SOLID, 
                                     L_UINT uFlags=0);
      virtual L_DOUBLE  GetLineWidth();
      virtual L_INT     SetLineWidth(L_DOUBLE dLineWidth, L_UINT uFlags=0);
      virtual L_INT     GetText(L_CHAR L_FAR * pText);
      virtual L_UINT    GetTextLen();
      virtual L_INT     SetText(L_CHAR L_FAR * pText, L_UINT uFlags=0);

      virtual L_INT     SetMetafile (HMETAFILE hMetafile, 
                                     L_UINT uType, 
                                     L_UINT uFlags=0);

      virtual L_INT     GetMetafile (HMETAFILE L_FAR*phMetafile);
          
      virtual L_INT    SetTransparentColor ( COLORREF crTransparent, 
                                             L_UINT uFlags=0);

      virtual L_INT    GetTransparentColor ( COLORREF L_FAR * pcrTransparent);

};
/*----------------------------------------------------------------------------+
| Class     : LAnnLine                                                        |
| Desc      :                                                                 |
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+
| Date      : September  1998                                                 |
+----------------------------------------------------------------------------*/
class LWRP_EXPORT LAnnLine: public LAnnotation     
{
   LEAD_DECLAREOBJECT(LAnnLine);

   public:
      L_VOID *m_extLAnnLine;

   public : 
      LAnnLine (L_BOOL bCreate=TRUE);
      LAnnLine (HANNOBJECT& hLine);
      virtual ~LAnnLine();

      virtual  L_INT    Create();
      virtual  L_UINT   GetLineStyle();
      virtual  L_INT    SetLineStyle(L_UINT uLineStyle=ANNLINE_SOLID, L_UINT uFlags=0);
      virtual  L_DOUBLE GetLineWidth();
      virtual  L_INT    SetLineWidth(L_DOUBLE dLineWidth, L_UINT uFlags=0);
};
/*----------------------------------------------------------------------------+
| Class     : LAnnPolyline                                                    |
| Desc      :                                                                 |
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+
| Date      : September  1998                                                 |
+----------------------------------------------------------------------------*/
class LWRP_EXPORT LAnnPolyline: public LAnnotation    
{
   LEAD_DECLAREOBJECT(LAnnPolyline);

   public:
      L_VOID *m_extLAnnPolyline;
      
   public : 
      LAnnPolyline(L_BOOL bCreate=TRUE);
      LAnnPolyline(HANNOBJECT& hPolyline);
      virtual  ~LAnnPolyline();

      virtual  L_INT    Create();
      virtual  L_UINT   GetLineStyle();
      virtual  L_INT    SetLineStyle(L_UINT uLineStyle=ANNLINE_SOLID, 
                                     L_UINT uFlags=0);
      virtual  L_DOUBLE GetLineWidth();
      virtual  L_INT    SetLineWidth(L_DOUBLE dLineWidth, L_UINT uFlags=0);
      virtual  L_UINT   GetPointCount();
      virtual  L_INT    GetPoints(pANNPOINT pPoints);
      virtual  L_INT    SetPoints(pANNPOINT pPoints, L_UINT uCount);
      virtual  L_INT    SetNodes(   L_BOOL bShowNodes = TRUE, 
                                    L_UINT uGapNodes = 0, 
                                    L_UINT uFlags = 0);

      virtual  L_INT    GetNodes(L_BOOL L_FAR*pbShowNodes, 
                                 L_UINT L_FAR*puGapNodes);
};
/*----------------------------------------------------------------------------+
| Class     : LAnnPolygon                                                     |
| Desc      :                                                                 |
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+
| Date      : September  1998                                                 |
+----------------------------------------------------------------------------*/
class LWRP_EXPORT LAnnPolygon: public LAnnotation     
{
   LEAD_DECLAREOBJECT(LAnnPolygon);

   public:
      L_VOID *m_extLAnnPolygon;
      
   public : 
      LAnnPolygon(L_BOOL bCreate=TRUE);
      LAnnPolygon(HANNOBJECT& hPolygon);
      virtual ~LAnnPolygon();

      virtual  L_INT    Create();
      virtual  L_UINT   GetPolyFillMode();
      virtual  L_INT    SetPolyFillMode(L_UINT uPolyFillMode=ANNPOLYFILL_WINDING, 
                                        L_UINT uFlags=0);
      virtual  L_UINT   GetFillPattern();
      virtual  L_INT    SetFillPattern(L_UINT uFillPattern=ANNPATTERN_SOLID, 
                                       L_UINT uFlags=0);
      virtual  L_UINT   GetLineStyle();
      virtual  L_INT    SetLineStyle(L_UINT uLineStyle=ANNLINE_SOLID, 
                                     L_UINT uFlags=0);
      virtual  L_DOUBLE GetLineWidth();
      virtual  L_INT    SetLineWidth(L_DOUBLE dLineWidth,L_UINT uFlags=0);

      virtual  L_UINT   GetPointCount();
      virtual  L_INT    GetPoints(pANNPOINT pPoints);
      virtual  L_INT    SetPoints(pANNPOINT pPoints, L_UINT uCount);
      virtual  L_INT    SetNodes(   L_BOOL bShowNodes = TRUE, 
                                    L_UINT uGapNodes = 0, 
                                    L_UINT uFlags = 0);

      virtual  L_INT    GetNodes(L_BOOL L_FAR*pbShowNodes, 
                                 L_UINT L_FAR*puGapNodes);
};
/*----------------------------------------------------------------------------+
| Class     : LAnnFreehand                                                    |
| Desc      :                                                                 |
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+
| Date      : September  1998                                                 |
+----------------------------------------------------------------------------*/
class LWRP_EXPORT LAnnFreehand: public LAnnotation    
{
   LEAD_DECLAREOBJECT(LAnnFreehand);

   public:
      L_VOID *m_extLAnnFreehand;
      
   public : 
      LAnnFreehand(L_BOOL bCreate=TRUE);
      LAnnFreehand(HANNOBJECT& hFreehand);
      virtual ~LAnnFreehand();

      virtual  L_INT    Create();
      virtual  L_UINT   GetLineStyle();
      virtual  L_INT    SetLineStyle(L_UINT uLineStyle=ANNLINE_SOLID,
                                     L_UINT uFlags=0);
      virtual  L_DOUBLE GetLineWidth();
      virtual  L_INT    SetLineWidth(L_DOUBLE dLineWidth, L_UINT uFlags=0);
      virtual  L_UINT   GetPointCount();
      virtual  L_INT    GetPoints(pANNPOINT pPoints);
      virtual  L_INT    SetPoints(pANNPOINT pPoints, L_UINT uCount);
      virtual  L_INT    SetNodes(   L_BOOL bShowNodes = TRUE, 
                                    L_UINT uGapNodes = 0, 
                                    L_UINT uFlags = 0);

      virtual  L_INT    GetNodes(L_BOOL L_FAR*pbShowNodes, 
                                 L_UINT L_FAR*puGapNodes);
};
/*----------------------------------------------------------------------------+
| Class     : LAnnRectangle                                                   |
| Desc      :                                                                 |
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+
| Date      : September  1998                                                 |
+----------------------------------------------------------------------------*/
class LWRP_EXPORT LAnnRectangle: public LAnnotation      
{
   LEAD_DECLAREOBJECT(LAnnRectangle);

   public:
      L_VOID *m_extLAnnRectangle;
      
   public : 
      LAnnRectangle(L_BOOL bCreate=TRUE);
      LAnnRectangle(HANNOBJECT& hRectangle);
      virtual ~LAnnRectangle();

      virtual  L_INT    Create();
      virtual  L_UINT   GetFillPattern();
      virtual  L_INT    SetFillPattern(L_UINT uFillPattern=ANNPATTERN_SOLID, 
                                       L_UINT uFlags=0);
      virtual  L_UINT   GetLineStyle();
      virtual  L_INT    SetLineStyle(L_UINT uLineStyle=ANNLINE_SOLID, L_UINT uFlags=0);
      virtual  L_DOUBLE GetLineWidth();
      virtual  L_INT    SetLineWidth(L_DOUBLE dLineWidth, L_UINT uFlags=0);
};
/*----------------------------------------------------------------------------+
| Class     : LAnnEllipse                                                     |
| Desc      :                                                                 |
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+
| Date      : September  1998                                                 |
+----------------------------------------------------------------------------*/
class LWRP_EXPORT LAnnEllipse: public LAnnotation     
{
   LEAD_DECLAREOBJECT(LAnnEllipse);

   public:
      L_VOID *m_extLAnnEllipse;
      
   public : 
      LAnnEllipse(L_BOOL bCreate=TRUE);
      LAnnEllipse (HANNOBJECT& hEllipse);
      virtual ~LAnnEllipse();

      virtual  L_INT    Create();
      virtual  L_UINT   GetFillPattern();
      virtual  L_INT    SetFillPattern(L_UINT uFillPattern=ANNPATTERN_SOLID, 
                                       L_UINT uFlags=0);
      virtual  L_UINT   GetLineStyle();
      virtual  L_INT    SetLineStyle(L_UINT uLineStyle=ANNLINE_SOLID, 
                                     L_UINT uFlags=0);
      virtual  L_DOUBLE GetLineWidth();
      virtual  L_INT    SetLineWidth(L_DOUBLE dLineWidth, L_UINT uFlags=0);
};
/*----------------------------------------------------------------------------+
| Class     : LAnnPointer                                                     |
| Desc      :                                                                 |
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+
| Date      : September  1998                                                 |
+----------------------------------------------------------------------------*/
class LWRP_EXPORT LAnnPointer: public LAnnotation     
{
   LEAD_DECLAREOBJECT(LAnnPointer);

   public:
      L_VOID *m_extLAnnPointer;
      
   public : 
      LAnnPointer(L_BOOL bCreate=TRUE);
      LAnnPointer (HANNOBJECT& hPointer);
      virtual  ~LAnnPointer();

      virtual  L_INT    Create();
      virtual  L_UINT   GetLineStyle();
      virtual  L_INT    SetLineStyle(L_UINT uLineStyle=ANNLINE_SOLID, 
                                     L_UINT uFlags=0);
      virtual  L_DOUBLE GetLineWidth();
      virtual  L_INT    SetLineWidth(L_DOUBLE dLineWidth, L_UINT uFlags=0);
};
/*----------------------------------------------------------------------------+
| Class     : LAnnButton                                                      |
| Desc      :                                                                 |
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+
| Date      : September  1998                                                 |
+----------------------------------------------------------------------------*/
class LWRP_EXPORT LAnnButton: public LAnnotation      
{
   LEAD_DECLAREOBJECT(LAnnButton);

   public:
      L_VOID *m_extLAnnButton;

   public : 
      LAnnButton(L_BOOL bCreate=TRUE);
      LAnnButton (HANNOBJECT& hButton);
      virtual  ~LAnnButton();

      virtual  L_INT    Create();
      virtual  L_INT    GetText(L_CHAR L_FAR * pText);
      virtual  L_UINT   GetTextLen();
      virtual  L_INT    SetText(L_CHAR L_FAR * pText, L_UINT uFlags=0);
};
/*----------------------------------------------------------------------------+
| Class     : LAnnHilite                                                      |
| Desc      :                                                                 |
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+
| Date      : September  1998                                                 |
+----------------------------------------------------------------------------*/
class LWRP_EXPORT LAnnHilite: public LAnnotation      
{
   LEAD_DECLAREOBJECT(LAnnHilite);

   public:
      L_VOID *m_extLAnnHilite;
      
   public : 
      LAnnHilite(L_BOOL bCreate=TRUE);
      LAnnHilite (HANNOBJECT& hHilite);
      virtual  ~LAnnHilite();

      virtual  L_INT    Create();
};
/*----------------------------------------------------------------------------+
| Class     : LAnnRedact                                                      |
| Desc      :                                                                 |
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+
| Date      : September  1998                                                 |
+----------------------------------------------------------------------------*/
class LWRP_EXPORT LAnnRedact: public LAnnotation      
{
   LEAD_DECLAREOBJECT(LAnnRedact);

   public:
      L_VOID *m_extLAnnRedact;
      
   public : 
      LAnnRedact(L_BOOL bCreate=TRUE);
      LAnnRedact (HANNOBJECT& hRedact);
      virtual  ~LAnnRedact();

      virtual  L_INT    Create();
      virtual  L_INT    Unrealize(pBITMAPHANDLE pBitmap, 
                                  LPRECT prcBounds);
      virtual  L_INT    Unrealize(LBitmapBase L_FAR * pBitmap, 
                                  LPRECT prcBounds);
};
/*----------------------------------------------------------------------------+
| Class     : LAnnAudioClip                                                   |
| Desc      :                                                                 |
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+
| Date      : September  1998                                                 |
+----------------------------------------------------------------------------*/
class LWRP_EXPORT LAnnAudioClip: public LAnnotation      
{
   LEAD_DECLAREOBJECT(LAnnAudioClip);
   
   public:
      L_VOID *m_extLAnnAudioClip;

   public : 
      LAnnAudioClip(L_BOOL bCreate=TRUE);
      LAnnAudioClip (HANNOBJECT& hAudioClip);
      virtual  ~LAnnAudioClip();

      virtual  L_INT    Create();
      virtual  L_INT    GetText(L_CHAR L_FAR * pText);
      virtual  L_UINT   GetTextLen();
      virtual  L_INT    SetText(L_CHAR L_FAR * pText, L_UINT uFlags=0);
};
/*----------------------------------------------------------------------------+
| Class     : LAnnHotSpot                                                     |
| Desc      :                                                                 |
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+
| Date      : September  1998                                                 |
+----------------------------------------------------------------------------*/
class LWRP_EXPORT LAnnHotSpot: public LAnnotation     
{
   LEAD_DECLAREOBJECT(LAnnHotSpot);

   public:
      L_VOID *m_extLAnnHotSpot;
      
   public : 
      LAnnHotSpot(L_BOOL bCreate=TRUE);
      LAnnHotSpot (HANNOBJECT& hHotSpot);
      virtual  ~LAnnHotSpot();

      virtual  L_INT Create();
      virtual  L_INT GetMetafile(HMETAFILE * phMetafile);
      virtual  L_INT SetMetafile(HMETAFILE hMetafile,
                                 L_UINT uType,
                                 L_UINT uFlags = 0);
};
/*----------------------------------------------------------------------------+
| Class     : LAnnRuler                                                       |
| Desc      :                                                                 |
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+
| Date      : September  1998                                                 |
+----------------------------------------------------------------------------*/
class LWRP_EXPORT LAnnRuler: public LAnnotation    
{
   LEAD_DECLAREOBJECT(LAnnRuler);

   public:
      L_VOID *m_extLAnnRuler;
      
   public : 
      LAnnRuler(L_BOOL bCreate=TRUE);
      LAnnRuler (HANNOBJECT& hRuler);
      virtual  ~LAnnRuler();

      virtual  L_INT    Create();
      virtual  L_UINT   GetLineStyle();
      virtual  L_INT    SetLineStyle(L_UINT uLineStyle=ANNLINE_SOLID, 
                                     L_UINT uFlags=0);
      virtual  L_DOUBLE GetLineWidth();
      virtual  L_INT    SetLineWidth(L_DOUBLE dLineWidth,L_UINT uFlags=0);
      virtual  L_DOUBLE GetGaugeLength();
      virtual  L_INT    SetGaugeLength(L_DOUBLE dLength,L_UINT uFlags=0);
      virtual  L_INT    GetDistance(L_DOUBLE L_FAR*pdDistance);      
      virtual  L_UINT   GetUnit(L_CHAR L_FAR* pUnitAbbrev, 
                                L_UINT L_FAR* puPrecision);
      virtual  L_UINT   GetUnitLen();
      virtual  L_INT    SetUnit(L_UINT uUnit,
                                L_CHAR L_FAR* pUnitAbbrev,
                                L_UINT uPrecision,L_UINT uFlags=0);

      virtual  L_INT    GetText(L_CHAR L_FAR * pText);
      virtual  L_UINT   GetTextLen();
      virtual  L_INT    SetShowFlags ( L_UINT uShowFlags = 0, 
                                       L_UINT uFlags     = 0 );

      virtual  L_INT    GetShowFlags ( L_UINT L_FAR*puShowFlags);
      virtual  L_INT    SetPoints(pANNPOINT pPoints, L_UINT uCount);
      virtual  L_INT    GetPoints(pANNPOINT pPoints);


};
/*----------------------------------------------------------------------------+
| Class     : LAnnNote                                                        |
| Desc      :                                                                 |
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+
| Date      : September  1998                                                 |
+----------------------------------------------------------------------------*/
class LWRP_EXPORT LAnnNote: public LAnnotation     
{
   LEAD_DECLAREOBJECT(LAnnNote);

   public:
      L_VOID *m_extLAnnNote;
      
   public : 
      LAnnNote(L_BOOL bCreate=TRUE);
      LAnnNote (HANNOBJECT& hNote);
      virtual  ~LAnnNote();

      virtual  L_INT    Create();
      virtual  L_INT    GetText(L_CHAR L_FAR * pText);
      virtual  L_UINT   GetTextLen();
      virtual  L_INT    SetText(L_CHAR L_FAR * pText, L_UINT uFlags=0);
};

/*----------------------------------------------------------------------------+
| Class     : LAnnToolBar                                                     |
| Desc      :                                                                 |
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+
| Date      : September  1998                                                 |
+----------------------------------------------------------------------------*/
class LWRP_EXPORT LAnnToolBar : public LBase
{
   LEAD_DECLAREOBJECT(LAnnToolBar);

   public:
      L_VOID *m_extLAnnToolBar;
      
   protected:  
      HWND m_hWndToolBar;

   public : 
      LAnnToolBar();
      virtual ~LAnnToolBar();

      virtual L_BOOL IsCreated();
      virtual HWND   GetWndHandle();
      virtual HWND   Create(  HWND hWndParent,
                              LPPOINT pPoint,
                              L_UINT uAlign,
                              L_BOOL bVisible,
                              L_UINT uButtons=NULL,
                              pANNBUTTON pButtons=NULL);

      virtual L_INT  SetButtonVisible(L_UINT uButton,L_BOOL bVisible);
      virtual L_BOOL IsButtonVisible(L_UINT uButton);
      virtual L_UINT GetToolChecked();
      virtual L_INT  SetToolChecked(L_UINT uChecked);
         
      virtual L_INT  SetToolBarButtons(pANNBUTTON pButtons,L_UINT uButtons);
      virtual L_INT  GetToolBarButtons(pANNBUTTON pButtons,L_UINT L_FAR*puButtons);
      virtual L_INT  FreeToolBarButtons(pANNBUTTON pButtons,L_UINT uButtons);
      virtual L_INT  GetToolBarInfo(pANNTOOLBARINFO pInfo);
      virtual L_INT  SetToolBarColumns(L_UINT uColumns);
      virtual L_INT  SetToolBarRows(L_UINT uRows);


      virtual L_INT  Destroy();
};

/*----------------------------------------------------------------------------+
| Class     : LAnnPushPin                                                        |
| Desc      :                                                                 |
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+
| Date      : September  1998                                                 |
+----------------------------------------------------------------------------*/
class LWRP_EXPORT LAnnPushPin: public LAnnNote     
{
   LEAD_DECLAREOBJECT(LAnnPushPin);

   public:
      L_VOID *m_extLAnnPushPin;
      
   public : 
      LAnnPushPin (L_BOOL bCreate=TRUE);
      LAnnPushPin (HANNOBJECT& hPushPin);
      virtual ~LAnnPushPin();

      virtual  L_INT    Create();
      virtual  L_INT    SetBitmap(pBITMAPHANDLE pBitmap,L_UINT uFlags);
      virtual  L_INT    SetBitmap(LBitmapBase L_FAR * pBitmap, L_UINT uFlags);
      virtual  L_INT    GetBitmap(pBITMAPHANDLE pBitmap);
      virtual  L_INT    GetBitmap(LBitmapBase L_FAR* pLBitmap);
      virtual  L_INT    SetSecondaryBitmap(pBITMAPHANDLE pBitmap,L_UINT uFlags);
      virtual  L_INT    SetSecondaryBitmap(LBitmapBase L_FAR * pBitmap, L_UINT uFlags);
      virtual  L_INT    GetSecondaryBitmap(pBITMAPHANDLE pBitmap);
      virtual  L_INT    GetSecondaryBitmap(LBitmapBase L_FAR* pLBitmap);
};


/*----------------------------------------------------------------------------+
| Class     : LAnnVideo                                                        |
| Desc      :                                                                 |
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+
| Date      : September  1998                                                 |
+----------------------------------------------------------------------------*/
class LWRP_EXPORT LAnnVideo: public LAnnotation     
{
   LEAD_DECLAREOBJECT(LAnnVideo);

   public:
      L_VOID *m_extLAnnVideo;
      
   public : 
      LAnnVideo (L_BOOL bCreate=TRUE);
      LAnnVideo (HANNOBJECT& hVideo);
      virtual ~LAnnVideo();

      virtual  L_INT    Create();
      L_INT    GetText(L_CHAR L_FAR * pText);
      L_UINT   GetTextLen();
      L_INT    SetText(L_CHAR L_FAR * pText, L_UINT uFlags=0);
};

/*----------------------------------------------------------------------------+
| Class     : LAnnProtractor                                                        |
| Desc      :                                                                 |
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+
| Date      : September  1998                                                 |
+----------------------------------------------------------------------------*/
class LWRP_EXPORT LAnnProtractor: public LAnnRuler     
{
   LEAD_DECLAREOBJECT(LAnnProtractor);

   public:
      L_VOID *m_extLAnnProtractor;
      
   public : 
      LAnnProtractor (L_BOOL bCreate=TRUE);
      LAnnProtractor (HANNOBJECT& hVideo);
      virtual ~LAnnProtractor();

      virtual  L_INT    Create();
      virtual  L_UINT   GetPointCount();
      virtual  L_INT    GetPoints(pANNPOINT pPoints);
      virtual  L_INT    SetPoints(pANNPOINT pPoints, L_UINT uCount=3);
      virtual  L_INT    SetProtractorOptions(   L_BOOL   bAcute = TRUE,
                                                L_UINT   uUnit = ANNANGLE_DEGREES,
                                                L_CHAR   L_FAR*pszAbbrev = NULL,
                                                L_UINT   uPrecision = 2,
                                                L_DOUBLE dArcRadius = 30,
                                                L_UINT   uFlags = 0);

      virtual L_INT     GetProtractorOptions(L_BOOL  L_FAR*pbAcute = NULL,
                                             L_UINT  L_FAR*puUnit = NULL,
                                             L_UINT L_FAR*puAbbrevLen = NULL,
                                             L_CHAR L_FAR*pszAbbrev = NULL,
                                             L_UINT  L_FAR*puPrecision = NULL,
                                             L_DOUBLE L_FAR*pdArcRadius = NULL);

      virtual L_INT    GetAngle(  L_DOUBLE L_FAR*pdAngle);
      virtual  L_INT    GetDistance(L_DOUBLE L_FAR*pdDistance,
                                    L_DOUBLE L_FAR*pdDistance2);      


};

/*----------------------------------------------------------------------------+
| Class     : LAnnCrossProduct                                                        |
| Desc      :                                                                 |
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+
| Date      : September  1998                                                 |
+----------------------------------------------------------------------------*/
class LWRP_EXPORT LAnnCrossProduct: public LAnnRuler     
{
   LEAD_DECLAREOBJECT(LAnnCrossProduct);

   public:
      L_VOID *m_extLAnnCrossProduct;
      
   public : 
      LAnnCrossProduct (L_BOOL bCreate=TRUE);
      LAnnCrossProduct (HANNOBJECT& hVideo);
      virtual ~LAnnCrossProduct();

      virtual  L_INT    Create();
      virtual  L_UINT   GetPointCount();
      virtual  L_INT    GetPoints(pANNPOINT pPoints);
      virtual  L_INT    SetPoints(pANNPOINT pPoints, L_UINT uCount=5);
      virtual  L_UINT   GetLineStyle();
      virtual  L_INT    SetLineStyle(L_UINT uLineStyle=ANNLINE_SOLID,L_UINT uFlags=0);
      virtual  L_DOUBLE GetLineWidth();
      virtual  L_INT    SetLineWidth(L_DOUBLE dLineWidth,L_UINT uFlags=0);
      virtual  L_INT    GetDistance(L_DOUBLE L_FAR*pdDistance,
                                    L_DOUBLE L_FAR*pdDistance2);      



};

/*----------------------------------------------------------------------------+
| Class     : LAnnFreehandHotSpot                                             |
| Desc      :                                                                 |
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+
| Date      : September  1998                                                 |
+----------------------------------------------------------------------------*/
class LWRP_EXPORT LAnnFreehandHotSpot: public LAnnFreehand
{
   LEAD_DECLAREOBJECT(LAnnFreehandHotSpot);

   public:
      L_VOID *m_extLAnnFreehandHotSpot;
      
   public : 
      LAnnFreehandHotSpot (L_BOOL bCreate=TRUE);
      LAnnFreehandHotSpot (HANNOBJECT& hFreehandHotSpot);
      virtual ~LAnnFreehandHotSpot();

      virtual  L_INT    Create();     
      virtual  L_INT    GetMetafile(HMETAFILE * phMetafile);
      virtual  L_INT    SetMetafile(HMETAFILE hMetafile,
                                    L_UINT uType,
                                    L_UINT uFlags = 0);
};

/*----------------------------------------------------------------------------+
| Class     : LAnnPoint                                             |
| Desc      :                                                                 |
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+
| Date      : September  1998                                                 |
+----------------------------------------------------------------------------*/
class LWRP_EXPORT LAnnPoint:public LAnnotation
{
   LEAD_DECLAREOBJECT(LAnnPoint);

   public:
      L_VOID *m_extLAnnPoint;
      
   public : 
      LAnnPoint (L_BOOL bCreate=TRUE);
      LAnnPoint (HANNOBJECT& hPoint);      
      virtual ~LAnnPoint();
      virtual  L_INT    Create();

      virtual L_INT     GetBitmap(pBITMAPHANDLE pBitmap);
      virtual L_INT     GetBitmap(LBitmapBase L_FAR * pBitmap);
      virtual L_INT     SetBitmap(pBITMAPHANDLE pBitmap, L_UINT uFlags=0);
      virtual L_INT     SetBitmap(LBitmapBase L_FAR * pBitmap, L_UINT uFlags=0);
      virtual L_INT     SetTransparent(L_BOOL  bTransparent,L_UINT uFlags=0);
      virtual L_BOOL    GetTransparent();
      virtual L_INT     SetTransparentColor ( COLORREF crTransparent,L_UINT uFlags=0);
      virtual L_INT     GetTransparentColor ( COLORREF L_FAR * pcrTransparent);
      virtual L_INT     GetPoints(pANNPOINT pPoint);
      virtual L_INT     SetPoints(pANNPOINT pPoint);

};

#endif //_LEAD_ANN_H_
/*================================================================= EOF =====*/

