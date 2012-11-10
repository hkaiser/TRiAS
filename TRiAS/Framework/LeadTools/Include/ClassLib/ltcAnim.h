/*----------------------------------------------------------------------------+
| LEADTOOLS for Windows -                                                     |
| Copyright (c) 1991-2000 LEAD Technologies, Inc.                             |
| All Rights Reserved.                                                        |
|-----------------------------------------------------------------------------|
| PROJECT   : LEAD wrappers                                                   |
| FILE NAME : ltcAnim.h                                                       |
| DESC      :                                                                 |
+----------------------------------------------------------------------------*/

#ifndef  _LEAD_ANIMATION_H_
#define  _LEAD_ANIMATION_H_

/*----------------------------------------------------------------------------+
| CLASSES DECLARATION                                                         |
+----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------+
| Class     : LAnimationWindow                                                |
| Desc      :                                                                 |
| Return    :                                                                 | 
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+
| Date      : September 1998                                                  |
+----------------------------------------------------------------------------*/

//this define is passed in nIndex parameter
#define ANIM_ALL_ITEMS        (L_UINT)-1
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "ltcBWnd.h"
class LWRP_EXPORT LAnimationWindow : public LBitmapWindow
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
{  
   LEAD_DECLAREOBJECT(LAnimationWindow);
   LEAD_DECLARE_CLASS_MAP();
   
   public:
      L_VOID *m_extLAnimationWindow;
   
   private  :  
      FILEINFO       m_fInfo;
      HPLAYBACK      m_hPlayback;
      LBitmapBase    m_PlayBitmap;
      LBitmapList *  m_pBitmapList;
      L_INT          m_nPlayMode, m_bPrevTool;
      L_BOOL         m_bPlayWhileLoad;
      L_UINT         m_PrevFrame;
      L_UINT         m_uState;
      L_INT          Move(L_UINT nIndex, L_BOOL bNewList = FALSE);
      L_VOID         PrepareNewAnimation();
      L_VOID         ResetBitmap(L_UINT nIndex);
      L_VOID         DestroyBitmapList();
      static BOOL    m_bLoadPlayback;
      L_INT          PlayProcessing();
      virtual L_BOOL OnFileDropped(L_CHAR L_FAR* pszFile,L_UINT uFileNumber,L_UINT uFilesCount);
      L_VOID         AnimationTimer();
      L_VOID         InitializeClass();

   protected:
      L_INT   GetAt(L_UINT nIndex, LBitmapBase L_FAR * pBitmap, L_BOOL bReflectIndex = FALSE);
      L_INT   SetAt(L_UINT nIndex, LBitmapBase L_FAR * pBitmap, L_BOOL bReflectIndex = FALSE);
      L_INT   InsertFrame(LBitmapBase L_FAR * pLBitmap, L_UINT uIndex =-1 /*last item*/);
      L_INT   RemoveFrame(L_UINT uIndex, LBitmapBase L_FAR * pBitmap = NULL);
   
      L_UINT            m_PlayWhileLoadFlags ;
      virtual L_INT     PlayWhileLoad();
      static  L_INT    EXT_CALLBACK  PlayCallback(pFILEINFO      pFileInfo,
                                     pBITMAPHANDLE  pBitmap,
                                     L_UCHAR L_FAR *pBuffer,
                                     L_UINT         uFlags,
                                     L_INT          nRow,
                                     L_INT          nLines,
                                     L_VOID L_FAR * pUserData);
      L_INT             PreProcessing();
      L_INT             PlayProcessing(HWND hWnd, L_BOOL bLoop = FALSE);   
      L_INT             PostProcessing();
   protected:
      L_BOOL      m_bAutoAnimate;
      L_BOOL      m_bAutoAnimationLoop;
      L_BOOL      m_bAnimationLoop;
      L_BOOL      m_bEvent;
      L_BOOL      m_bAnimationExist, m_bAllowChange;
      L_BOOL      m_fCanceled;
      L_BOOL      m_bIsAnimation;
      COLORREF    m_crBackground;

      L_INT       m_nAnimationBitsPerPixel,m_nColorOrder;      
      
   public   :
      
      LAnimationWindow();
      LAnimationWindow(HWND hWndParent,LBitmapList L_FAR * pBitmapList=NULL,
                 L_BOOL bAutoAnimate = FALSE,L_INT nID=0,
                 DWORD dwStyle=WS_VISIBLE|L_BS_CENTER|L_BS_PROCESSKEYBOARD,
                 L_INT x=0,L_INT y=0,L_INT nCX=200,L_INT nCY=200);
      virtual ~LAnimationWindow();
      
      L_BOOL   IsAutoAnimateEnabled() const;
      L_BOOL   EnableAutoAnimate(L_BOOL bAutoAnimate = TRUE);
      
      L_BOOL   IsAutoLoopEnabled() const;
      L_BOOL   EnableAutoLoop(L_BOOL bAutoLoop = TRUE);
      
      L_BOOL   IsLoopEnabled() const;
      L_BOOL   EnableLoop(L_BOOL bEnableLoop = TRUE);
      
      L_INT    GetAnimationBitsPerPixel() const;
      L_INT    GetAnimationWidth() const;
      L_INT    GetAnimationHeight() const;
      L_INT    GetAnimationColorOrder() const;

      L_INT    GetDelay(L_UINT   nIndex) const;
      L_INT    SetDelay(L_INT nDelay, L_UINT nIndex  = ANIM_ALL_ITEMS);
      
      L_INT    GetDisposalMethod(L_UINT nIndex) const;
      L_INT    SetDisposalMethod(L_INT nDisposalMethod, L_UINT nIndex  = ANIM_ALL_ITEMS);
      
      L_INT    SetPosition(L_INT nLeft, L_INT nTop, L_UINT nIndex = ANIM_ALL_ITEMS);
      L_INT    GetPosition(L_INT L_FAR * pLeft, L_INT L_FAR * pTop, L_UINT nIndex) const;
      
      L_INT    EnableTransparency(L_BOOL bEnable = TRUE, COLORREF clrTransparent = RGB(0,0,0), L_UINT nIndex  = ANIM_ALL_ITEMS);
      L_INT    IsTransparencyEnabled(L_BOOL L_FAR * pEnabled, COLORREF L_FAR * pTransparentColor,L_UINT nIndex) const;
      
      L_INT    WaitForUserInput(L_BOOL bWait = TRUE, L_UINT nIndex  =ANIM_ALL_ITEMS);
      L_BOOL   IsWaitingForUserInput(L_UINT nIndex) const;

      L_VOID   SetBackgroundColor(COLORREF   crBack);
      COLORREF GetBackgroundColor();
      L_INT    ColorResItems(L_INT  nBitsPerPixel,L_UINT32 uFlags,
                             LPRGBQUAD  pPalette = NULL, HPALETTE hPalette = NULL, L_UINT  uColors = 0);
      L_INT    DoModalColorResItems(HWND hwndParent=NULL);
      //List
      virtual L_INT    MoveFirstFrame();
      virtual L_INT    MoveLastFrame();
      virtual L_INT    MovePreviousFrame();
      virtual L_INT    MoveNextFrame();
      virtual L_INT    MoveToFrame(L_UINT nIndex);
      
      L_UINT   GetCurrentIndex() const;
      L_UINT   GetCount()  const;
      
      HWND     GetAnimationWindow() const;
      
      L_BOOL   IsNextFrameAvailable()     const;
      L_BOOL   IsPreviousFrameAvailable() const;
      L_BOOL   IsFirstFrame()             const;
      L_BOOL   IsLastFrame()              const;

protected:
   virtual LRESULT MsgProcCallBack(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
   virtual L_INT   StartChanging(L_UINT nChangeType,L_UINT nChangeCategory);
   virtual L_VOID  EndChanging(L_UINT nChangeType,L_UINT nChangeCategory,L_INT nRetCode);

public : 
   L_VOID  SetBitmapList(LBitmapList L_FAR * pBitmapList,LBitmapList L_FAR * pBitmapListPrev=NULL, L_INT nBitsPerPixel=0, L_INT nColorOrder=ORDER_BGRORGRAY);

   //1
   L_INT   Load ( L_INT nBitsPerPixel, 
                  L_INT nColorOrder, 
                  L_INT nPage,
                  pFILEINFO pFileInfo = NULL);
   //2
   L_INT   Load(  L_INT nBitsPerPixel=0, 
                  L_INT nColorOrder=ORDER_BGRORGRAY, 
                  pLOADFILEOPTION pLoadFileOption = NULL,
                  pFILEINFO pFileInfo = NULL);
   //3
   L_INT   Load ( L_CHAR L_FAR * pszFileName,
                  L_INT nBitsPerPixel, 
                  L_INT nColorOrder, 
                  L_INT nPage,
                  pFILEINFO pFileInfo = NULL);
   //4
   L_INT   Load ( L_CHAR L_FAR * pszFileName,
                  L_INT nBitsPerPixel=0, 
                  L_INT nColorOrder=ORDER_BGRORGRAY, 
                  pLOADFILEOPTION pLoadFileOption = NULL,
                  pFILEINFO pFileInfo = NULL);

   virtual L_INT    Save();
   
   
   virtual L_VOID AnimateEvent(L_INT nEvent,L_INT nFrameNumber);
   L_BOOL   EnableAnimateEvent(L_BOOL bEnable=TRUE);
   
   L_INT    PlayAnimation();
   L_VOID   StopAnimation();

   L_BOOL   IsPlaying() const;
   L_BOOL   DoEvents(L_BOOL L_FAR * pbCanceled = NULL, L_UINT uVKey = VK_ESCAPE)  const;
   L_BOOL   IsValidAnimation() const;      //TRUE if has a bitmap list with more than one image
   L_BOOL   EnablePlayWhileLoad(L_BOOL bEnable = TRUE);
   L_BOOL   IsPlayWhileLoadEnabled();
   L_UINT32 GetRemainingDelay();
   L_INT    CancelWait();
   
 
};
#endif //_LEAD_ANIMATION_H_
/*================================================================= EOF =====*/
