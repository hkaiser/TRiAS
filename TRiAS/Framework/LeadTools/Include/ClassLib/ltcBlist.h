/*----------------------------------------------------------------------------+
| LEADTOOLS for Windows -                                                     |
| Copyright (c) 1991-2000 LEAD Technologies, Inc.                             |
| All Rights Reserved.                                                        |
|-----------------------------------------------------------------------------|
| PROJECT   : LEAD wrappers                                                   |
| FILE NAME : ltcBlist.h                                                      |
| DESC      :                                                                 |
+----------------------------------------------------------------------------*/

#ifndef  _LEAD_BITMAPLIST_H_
#define  _LEAD_BITMAPLIST_H_

/*----------------------------------------------------------------------------+
| STRUCTURES                                                                  |
+----------------------------------------------------------------------------*/
typedef struct tagBLISTINFO
{   
   L_INT          nWidth;
   L_INT          nHeight;
   L_UINT         uViewPerspective;
   L_UINT         uCurrentIndex;

   L_BOOL         bGlobalBackground;
   COLORREF       crBackground;
   
   L_BOOL         bGlobalLoop;
   L_UINT         uGlobalLoop;
   
   L_BOOL         bGlobalPalette;
   RGBQUAD        Palette[256];

}  BLISTINFO, L_FAR * LPBLISTINFO;

/*----------------------------------------------------------------------------+
| CLASSES DECLARATION                                                         |
+----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------+
| Class     : LBitmapList                                                     |
| Desc      :                                                                 |
| Return    :                                                                 |
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+
| Date      : September 1998                                                  |
+----------------------------------------------------------------------------*/
class LWRP_EXPORT LBitmapList :public LBase
{
   LEAD_DECLAREOBJECT(LBitmapList);
   LEAD_DECLARE_LIST_BITMAP();

   friend LWRP_EXPORT LBitmapBase L_FAR* LEAD_GetBitmapObject(LWRAPPERBITMAPMEMBER nClassType,LBase L_FAR* This,LPLEADCREATEOBJECT pCreateObj);
   friend class LAnimationWindow;

   public:
      L_VOID *m_extLBitmapList;
      
   private:  
      LBitmapBase L_FAR*   m_pBitmap;  
      L_UINT               m_nCurrentIndex; 
      pHBITMAPLIST         GetpHandle();
      
   protected:
      HBITMAPLIST   m_hBitmapList;
      //helper data for animation
      L_INT          m_Width;
      L_INT          m_Height;
      L_UINT         m_uViewPerspective;
      COLORREF       m_crBackground;
      L_BOOL         m_bGlobalBackground;
      L_BOOL         m_bGlobalPalette;
      L_BOOL         m_bGlobalLoop;
      L_UINT         m_nGlobalLoop;
      RGBQUAD        m_Palette[256];

   private:
      L_VOID            InitializeClass();

   public : 
      LBitmapList();
      LBitmapList(LBitmapList L_FAR* pBitmapList);
      virtual ~LBitmapList();

      LBitmapBase & operator[](L_UINT nIndex);
      LBitmapList & operator=(LBitmapList&  LBitmapListSrc);

      L_UINT            GetCurrentIndex(); 
      L_INT             SetCurrentIndex(L_UINT  uIndex);

      virtual  L_INT    Create();
      virtual  L_INT    Destroy();       
      virtual  L_BOOL   IsCreated();

      HBITMAPLIST       GetHandle();
      L_VOID            SetHandle(HBITMAPLIST hList, LPBLISTINFO pBListInfo = NULL,L_BOOL bFree=TRUE);

      L_INT             GetFirstItem(LBitmapBase L_FAR* pLBitmap);
      L_INT             GetLastItem(LBitmapBase L_FAR* pLBitmap);
      L_INT             GetPreviousItem(LBitmapBase L_FAR* pLBitmap);
      L_INT             GetNextItem(LBitmapBase L_FAR* pLBitmap);

      virtual  L_INT    ColorResItems(L_INT  nBitsPerPixel,L_UINT32 uFlags,
                                      LPRGBQUAD  pPalette=NULL, HPALETTE hPalette=NULL, L_UINT  uColors=0);
      virtual  L_INT    CopyItems(LBitmapList&  LBitmapListSrc,
                                  L_UINT  uIndex,L_UINT  uCount);

      /****v12
      virtual  L_INT    MoveItems(LBitmapList&  LBitmapListSrc,L_UINT  uIndex,L_UINT  uCount);
      ****/

      virtual  L_INT    DeleteItems(L_UINT  uIndex,
                                          L_UINT  uCount=1);
      virtual  L_UINT   GetItemsCount();                               
      virtual  L_INT    InsertItem(LBitmapBase L_FAR* pLBitmap, L_UINT uIndex =(L_UINT)-1);
      virtual  L_INT    RemoveItem(L_UINT uIndex, LBitmapBase L_FAR* pRemovedBitmap);
      virtual  L_INT    GetItem(L_UINT uIndex,LBitmapBase L_FAR* pLBitmap, L_BOOL bReflectIndex = TRUE);
      virtual  L_INT    SetItem(L_UINT uIndex,LBitmapBase L_FAR* pLBitmap, L_BOOL bReflectIndex = TRUE,L_UINT L_FAR* puSetIndex=NULL);

      virtual  L_INT    Save( L_CHAR L_FAR*lpszFile,
                              L_INT nFormat,
                              L_INT nBits,
                              L_INT nQFactor,
                              pSAVEFILEOPTION pSaveOptions = NULL); 
      virtual  L_INT    Load( L_CHAR L_FAR*lpszFile,
                              L_INT nBitsTo = 0,
                              L_INT nColorOrder = ORDER_BGRORGRAY,
                              pLOADFILEOPTION pLoadOption = NULL,
                              pFILEINFO pFileInfo = NULL);
      L_INT       GetGlobalWidth();
      L_INT       GetGlobalHeight();
      L_INT       GetViewPerspective();
      LPRGBQUAD   GetPalette();
      L_BOOL      HasGlobalBackground();
      COLORREF    GetBackgroundColor();
      L_BOOL      HasGlobalPalette();
      L_BOOL      HasGlobalLoop();
      L_UINT      GetGlobalLoop();
      L_VOID      SetBitmapList(LBitmapList L_FAR* pBitmapList);        
};

#endif //_LEAD_BITMAPLIST_H_
/*================================================================= EOF =====*/
