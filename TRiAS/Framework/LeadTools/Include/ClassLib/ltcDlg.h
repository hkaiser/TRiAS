/*----------------------------------------------------------------------------+
| LEADTOOLS for Windows -                                                     |
| Copyright (c) 1991-2000 LEAD Technologies, Inc.                             |
| All Rights Reserved.                                                        |
|-----------------------------------------------------------------------------|
| PROJECT   : LEAD wrappers                                                   |
| FILE NAME : ltcdlg.h                                                        |
| DESC      :                                                                 |
+----------------------------------------------------------------------------*/

#ifndef  _LEAD_DIALOG_H_
#define  _LEAD_DIALOG_H_

/*----------------------------------------------------------------------------+
| DEFINES                                                                     |
+----------------------------------------------------------------------------*/
//#define DLG_FS_ALL            0xFFFFFFFF  /* all file formats */

#define IDCB_OPENFILE        0   
#define IDCB_GETANGLE        1
#define IDCB_GETSIZE         2
#define IDCB_GETFILTER       3
#define IDCB_GETGHANGE       4  
#define IDCB_GETGAMMA        5
#define IDCB_GETNOISE        6 
#define IDCB_GETEMBOSS       7             
#define IDCB_GETRANG         8           
#define IDCB_COLORRES        9
#define IDCB_FILESAVE        10 
#define IDCB_WINDOWLEVEL     11
#define IDCB_COUNT           IDCB_WINDOWLEVEL+1

/*----------------------------------------------------------------------------+
| CLASSES DECLARATION                                                         |
+----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------+
| Class     : LDialog                                                         |
| Desc      :                                                                 |
| Return    :                                                                 |
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+
| Date      : september 1998                                                  |
+----------------------------------------------------------------------------*/

class LWRP_EXPORT LDialog : public LBase
{
   LEAD_DECLAREOBJECT(LDialog);

   public:
      L_VOID *m_extLDialog;
      
   private:  
      static LDialog L_FAR* pActiveDlg;
      
   protected:  
      LBitmapBase L_FAR*    m_pLBitmap;
      
      //common to all dialogs
      //L_UINT32          m_uUIFlags;
      L_BOOL              m_bShowPreview;
      L_BOOL              m_bAutoProcess;
      L_BOOL              m_bToolbar;

      //common to FileOpen and FileSave dialogs
      OPENFILENAME      m_OpenFileName;   // Windows OPENFILENAME structure
      L_CHAR            m_szFilename[L_MAXPATH];
      
      
      //FileOpen dialog
      FILEOPENPARM      m_FileOpenParm;  // FileOpen information structure

      //FileSave dialog
      FILESAVEPARM      m_FileSaveParm;   // FileSave information structure

      //ColorRes dialog
      L_INT             m_nBits;    // the desired bits per pixel
      L_UINT32          m_uColorResFlags; // user's choice of ColorRes flags
      HPALETTE          m_hpalCustom;


      //Angle dialog
      L_INT32           m_nAngle;
      L_UINT            m_uResizeFlags;
      COLORREF          m_crBack;      // background color
      L_BOOL            m_bFlag;

      //Change dialog
      L_INT             m_nChange;
      L_UINT32          m_uProcess;    // flag indicating which function was chosen.

      //Effect dialog
      EFXDLGPARM        m_EfxDlgParm;  // Effect options structure

      //Emboss dialog
      L_UINT            m_uDirection;
      L_UINT            m_uDepth;

      //Filter dialog
      LPSPATIALFLT      m_pSpatialFlt; // the spatial filter pointer
      LPBINARYFLT       m_pBinaryFlt;  // the binary filter pointer
      L_BOOL            m_bSpatialFilter; // flag indicating choice of filter

      //Gamma dialog
      L_INT    m_nGammaRed;
      L_INT    m_nGammaGreen;
      L_INT    m_nGammaBlue;      

      //Gradient dialog
      GRADDLGPARM       m_GradDlgParm; // Gradient options structure

      //Contour dialog
      CONTOURFILTERDLGPARM m_ContourDlgParm;
 
      //Noise dialog
      L_UINT            m_uRange;
      L_UINT            m_uChannel;

      //Range dialog
      L_UINT            m_uLow;
      L_UINT            m_uHigh;

      //3dShape dialog
      SHAPEDLGPARM         m_ShapeDlgParm;   // Shape options structure
      LBitmapBase L_FAR*   m_pBackgroundBitmap;

      //Size dialog
      L_INT          m_nNewWidth;      // new width
      L_INT          m_nNewHeight;     // new height
      L_UINT         m_uResizeMethod;  // Desired resize method
      L_INT          m_nXResolution;   // Desired horizontal resolution
      L_INT          m_nYResolution;   // Desired vertical resolution
      
         //3dText dialog
      LBitmapBase L_FAR*   m_pForegroundBitmap;
      TEXTDLGPARM          m_TextDlgParm; // Text options structure

      //Transition dialog
      TRANSDLGPARM      m_TransDlgParm;   // Transition options structure
      L_BOOL            m_bShowHelpButton /*=FALSE*/;

      //Window Level dialog
      L_RGBQUAD L_HUGE* m_pLUT;
      L_UINT32          m_uLUTLength;
      L_INT             m_nLowBit;
      L_INT             m_nHighBit;
      L_UINT            m_nLow;
      L_UINT            m_nHigh;
      COLORREF          m_crStart;
      COLORREF          m_crEnd;

      // Halftone Dialog
      L_INT             m_nHalftoneAngle;
      L_UINT32          m_uHalftoneType;

   private:  
      static  L_VOID    EXT_CALLBACK DialogHelpCS(L_UINT32 uFlag, L_INT iControlID, L_VOID L_FAR* pUserData);
      
      L_VOID            PrepareUIFlags(L_UINT DlgType, L_UINT32 L_FAR * pUIFlags);
      L_VOID            HandleAutoProcess(L_UINT DlgType, L_INT nRetCode, L_UINT32 uUIFlags);
      //LTCOMMDLGHELPCB   GetHelpCallback();
      //L_VOID            LockHelpCallback();
      //L_VOID            UnlockHelpCallback();
      L_VOID            InitializeClass();   

      L_VOID SetLevelTmp(L_UINT nFlag );
      L_UINT GetLevelTmp( );
      L_VOID SetResizeTmp(L_UINT nFlag );
      L_UINT GetResizeTmp() const; 

      
   protected:
      virtual L_VOID    DialogHelpCallBack(L_UINT32 uFlag, L_INT iControlID);
   
   public : 
      
      LDialog();
      LDialog(LBitmapBase L_FAR* pLBitmap);
      virtual ~LDialog();

      L_VOID           SetBitmap(LBitmapBase L_FAR* pBitmap);
      LBitmapBase L_FAR*  GetBitmap();
      L_BOOL           IsValid();
      //Accessors:
      L_BOOL           EnablePreview(L_BOOL bEnablePreview =TRUE);
      L_BOOL           IsPreviewEnabled() const;
      L_BOOL           EnableAutoProcess(L_BOOL bAuto = TRUE);
      L_BOOL           IsAutoProcessEnabled() const;
      L_BOOL           EnableToolbar(L_BOOL bEnableToolbar = TRUE);
      L_BOOL           IsToolbarEnabled() const;
      
       
      L_INT32           GetAngle() const;
      L_INT             SetAngle(L_INT32 nNewValue);
      L_UINT            GetResizeFlags() const;
      L_INT             SetResizeFlags(L_UINT nNewValue);
      L_BOOL            GetAngleFlag() const;
      L_INT             SetAngleFlag(L_BOOL bNewValue);

      L_BOOL            IsHelpButtonEnabled() const;
      L_INT             EnableHelpButton(L_BOOL bNewValue =TRUE);

      L_INT          GetNewWidth() const;
      L_INT          SetNewWidth(L_INT nNewValue);
      L_INT          GetNewHeight() const;
      L_INT          SetNewHeight(L_INT nNewValue);
      L_UINT         GetResizeMethod() const;
      L_VOID         SetResizeMethod(L_UINT uResizeMethod);
      L_INT          GetXResolution() const;
      L_INT          GetYResolution() const;

      L_INT             GetBitsPerPixel() const;
      L_INT             SetBitsPerPixel(L_INT nNewValue);
      L_UINT32          GetColorResFlags();
      HPALETTE          GetCustomPalette() const;

      L_VOID            GetFileName(L_CHAR L_FAR* pszBuff, L_INT cbSize) const;
      L_INT             SetFileName(L_CHAR L_FAR* pszFile);
      L_INT             SetOpenFileName(LPOPENFILENAME pOpenFileName);
      L_VOID            GetOpenFileName(LPOPENFILENAME pOpenFileName);
      L_INT             SetFileOpenParameters(LPFILEOPENPARM pFileOpenParm);
      L_VOID            GetFileOpenParameters(LPFILEOPENPARM pFileOpenParm) const;
      L_VOID            GetFileSaveParameters(LPFILESAVEPARM pSaveParms) const;
      L_INT             SetFileSaveParameters(LPFILESAVEPARM pNewValue);
       
      L_UINT            GetDirection() const;
      L_INT             SetDirection(L_UINT uNewValue);
      L_UINT            GetDepth() const;
      L_INT             SetDepth(L_UINT uNewValue);
       
      L_UINT            GetRange() const;
      L_INT             SetRange(L_UINT uNewValue);
      L_UINT            GetChannel() const;
      L_INT             SetChannel(L_UINT uNewValue);
      L_INT             GetGammaRed() const;
      L_VOID            SetGammaRed(L_INT nRedValue);
      L_INT             GetGammaGreen() const;
      L_VOID            SetGammaGreen(L_INT nGreenValue);
      L_INT             GetGammaBlue() const;
      L_VOID            SetGammaBlue(L_INT nBlueValue);
       
      L_UINT            GetLowRange() const;
      L_INT             SetLowRange(L_UINT uNewValue);
      L_UINT            GetHighRange() const;
      L_INT             SetHighRange(L_UINT uNewValue);

      L_INT             GetChange() const;
      L_INT             SetChange(L_INT nNewValue);

      L_UINT32          GetProcess() const;
       
      L_VOID            GetEffectParameters(LPEFXDLGPARM pEfxDlgParm ) const;
      L_INT             SetEffectParameters(LPEFXDLGPARM pEfxDlgParm );

      LPSPATIALFLT      GetSpatialFilter();
      LPBINARYFLT       GetBinaryFilter();
      L_INT             IsSpatialFilter() const;

      L_INT             GetLowBit() const;
      L_INT             SetLowBit(L_INT nNewValue);
      L_INT             GetHighBit() const;
      L_INT             SetHighBit(L_INT nNewValue);
      L_UINT            GetLowLevel() const;
      L_INT             SetLowLevel(L_UINT uNewValue);
      L_UINT            GetHighLevel() const;
      L_INT             SetHighLevel(L_UINT uNewValue);
      COLORREF          GetStartColor() const;
      L_INT             SetStartColor(COLORREF crNewValue);
      COLORREF          GetEndColor() const;
      L_INT             SetEndColor(COLORREF crNewValue);
      L_RGBQUAD L_HUGE* GetLookUpTable() const;
      L_UINT32          GetLookUpTableLength() const;
       
      L_VOID            GetGradientParameters(LPGRADDLGPARM    pGradDlgParm) const;
      L_INT             SetGradientParameters(LPGRADDLGPARM    pGradDlgParm);
      COLORREF          GetBackColor() const;
      L_INT             SetBackColor(COLORREF crNewValue);

      L_VOID            GetShapeParameters(LPSHAPEDLGPARM      pShapeDlgParm) const;
      L_INT             SetShapeParameters(LPSHAPEDLGPARM      pShapeDlgParm);
      L_VOID            GetTextParameters(LPTEXTDLGPARM        pTextDlgParm) const;
      L_INT             SetTextParameters(LPTEXTDLGPARM        pTextDlgParm);
      L_VOID            GetTransitionParameters(LPTRANSDLGPARM    pTransDlgParm) const;
      L_INT             SetTransitionParameters(LPTRANSDLGPARM    pTransDlgParm);
     
      L_VOID            GetContourParameters(LPCONTOURFILTERDLGPARM pContourDlgParm) const;
      L_INT             SetContourParameters(LPCONTOURFILTERDLGPARM pContourDlgParm);
      
      LBitmapBase L_FAR*   GetBackgroundBitmap() const;
      L_INT                SetBackgroundBitmap(LBitmapBase L_FAR* pBitmap);
      LBitmapBase L_FAR*   GetForegroundBitmap() const;
      L_INT                SetForegroundBitmap(LBitmapBase L_FAR* pBitmap);

      L_INT       GetHalftoneAngle() const;
      L_VOID      SetHalftoneAngle(L_INT nAngle);
      L_UINT32    GetHalftoneType() const;
      L_VOID      SetHalftoneType(L_UINT32 uType);

      L_VOID      SetWindowLevelFlags(L_UINT32 uUIFlags);

      static   L_INT  GetStringLen( L_UINT32 uString, L_UINT L_FAR* puLen );
      static   L_INT  GetString( L_UINT32 uString, L_CHAR L_FAR* pString );
      static   L_INT  SetString( L_UINT32 uString, L_CHAR L_FAR* pString );
      static   HFONT  SetFont( HFONT hFont );

//Operations:
      virtual L_INT  DoModalFileOpen (HWND hWndParent =NULL, L_UINT32 uUIFlags = DLG_FO_FILEINFO|
                                                                                 DLG_FO_MULTIPAGE); 
      virtual L_INT  DoModalGetAngle(HWND hWndParent  =NULL, L_UINT32 uUIFlags = DLG_IMG_ROTATE);
      virtual L_INT  DoModalGetSize(HWND hWndParent = NULL, L_UINT32 uUIFlags = DLG_IMG_PERCENTAGE |
                                                                                DLG_IMG_IDENTICALVAL |
                                                                                DLG_IMG_MAINTAINASPECT |
                                                                                DLG_IMG_RESOLUTIONGRP);

      virtual L_INT  DoModalGetFilter(HWND hWndParent =NULL, L_UINT32 uUIFlags = DLG_IMG_GRADIENT);

      virtual L_INT  DoModalGetChange(HWND hWndParent =NULL, L_UINT32 uUIFlags = DLG_IMG_POSTERIZE|
                                                                                 DLG_IMG_MOSAIC|
                                                                                 DLG_IMG_AVERAGE|
                                                                                 DLG_IMG_MEDIAN|
                                                                                 DLG_IMG_OILIFY|
                                                                                 DLG_IMG_MAX|
                                                                                 DLG_IMG_MIN|
                                                                                 DLG_IMG_SOLARIZE|
                                                                                 DLG_IMG_HUE|
                                                                                 DLG_IMG_SHARPEN|
                                                                                 DLG_IMG_BRIGHTNESS|
                                                                                 DLG_IMG_CONTRAST|
                                                                                 DLG_IMG_SATURATION|
                                                                                 DLG_IMG_HISTOCONTRAST);

      virtual L_INT  DoModalGetGamma(HWND hWndParent = NULL, L_BOOL bAllChannels = FALSE);
      virtual L_INT  DoModalGetNoise(HWND hWndParent = NULL);
      virtual L_INT  DoModalGetEmboss(HWND hWndParent = NULL);
      virtual L_INT  DoModalGetRange(HWND hWndParent = NULL);
      virtual L_INT  DoModalColorRes(HWND hWndParent = NULL,
                                     L_UINT32 uUIFlags = DLG_CR_ORDER,
                                     L_UINT32 uExFlags = DLG_CR_BITALL |
                                                         DLG_CR_DITHER_ALL |
                                                         DLG_CR_PAL_ALL);

      virtual L_INT  DoModalFileSave(  HWND hWndParent               = NULL, 
                                       L_UINT32 uUIFlags             = DLG_FS_MULTIPAGE,
                                       LPFILESAVEFORMAT pSaveFormats = NULL,
                                       L_INT nSaveFormats            = 0);

      virtual L_INT  DoModalWindowLevel(HWND hWndParent = NULL,
                                        L_BOOL bKeepLookupTable = FALSE);
      virtual L_INT  DoModalGetEffect( HWND hWndParent  =NULL, L_UINT32 uUIFlags =  DLG_EFX_DELAY            |
                                                                                    DLG_EFX_GRAIN            |
                                                                                    DLG_EFX_PASSES           |
                                                                                    DLG_EFX_TRANSPARENT      |
                                                                                    DLG_EFX_WAND             |
                                                                                    DLG_EFX_CLASS_WIPE       |
                                                                                    DLG_EFX_CLASS_WIPERECT   |
                                                                                    DLG_EFX_CLASS_WIPECIRCLE |
                                                                                    DLG_EFX_CLASS_PUSH       |
                                                                                    DLG_EFX_CLASS_SLIDE      |
                                                                                    DLG_EFX_CLASS_ROLL       |
                                                                                    DLG_EFX_CLASS_ROTATE     |
                                                                                    DLG_EFX_CLASS_ZOOM       |
                                                                                    DLG_EFX_CLASS_DRIP       |
                                                                                    DLG_EFX_CLASS_BLIND      |
                                                                                    DLG_EFX_CLASS_RANDOM     |
                                                                                    DLG_EFX_CLASS_CHECK      |
                                                                                    DLG_EFX_CLASS_BLOCKS     |
                                                                                    DLG_EFX_CLASS_CIRCLE     |
                                                                                    DLG_EFX_CLASS_ELLIPSE);

      virtual L_INT  DoModalGetShape( HWND hWndParent   =NULL, L_UINT32 uUIFlags = 
                                                                                 DLG_SHAPE_BACKSTYLE            |
                                                                                 DLG_SHAPE_FILLSTYLE            |
                                                                                 DLG_SHAPE_FORE_BACK_COLOR      |
                                                                                 DLG_SHAPE_BORDERSTYLE          |
                                                                                 DLG_SHAPE_BORDERWIDTH          |
                                                                                 DLG_SHAPE_BORDERCOLOR          |
                                                                                 DLG_SHAPE_INNERSTYLE           |
                                                                                 DLG_SHAPE_INNERWIDTH           |
                                                                                 DLG_SHAPE_INNER_HILITE_SHADOW  |
                                                                                 DLG_SHAPE_OUTERSTYLE           |
                                                                                 DLG_SHAPE_OUTERWIDTH           |
                                                                                 DLG_SHAPE_OUTER_HILITE_SHADOW  |
                                                                                 DLG_SHAPE_SHADOWCOLOR          |
                                                                                 DLG_SHAPE_SHADOW_X_Y           |
                                                                                 DLG_SHAPE_BROWSEIMAGE          |
                                                                                 DLG_SHAPE_NO_TREEVIEW          |
                                                                                 DLG_SHAPE_CLASS_SQUARE         |
                                                                                 DLG_SHAPE_CLASS_RECTANGLE      |
                                                                                 DLG_SHAPE_CLASS_PARALLELOGRAM  |
                                                                                 DLG_SHAPE_CLASS_TRAPEZOID      |
                                                                                 DLG_SHAPE_CLASS_TRIANGLE       |
                                                                                 DLG_SHAPE_CLASS_OTHER          |
                                                                                 DLG_SHAPE_CLASS_CIRCLE         |
                                                                                 DLG_SHAPE_CLASS_ELLIPSE        |
                                                                                 DLG_SHAPE_CLASS_STAR           |
                                                                                 DLG_SHAPE_CLASS_CROSS          |
                                                                                 DLG_SHAPE_CLASS_ARROW);

      virtual L_INT  DoModalGetText( HWND hWndParent    =NULL, L_UINT32 uUIFlags = 
                                                                                 DLG_TEXT_SAMPLETEXT            |
                                                                                 DLG_TEXT_STYLE                 |
                                                                                 DLG_TEXT_COLOR                 |
                                                                                 DLG_TEXT_BORDERCOLOR           |
                                                                                 DLG_TEXT_ALIGN                 |
                                                                                 DLG_TEXT_ANGLE                 |
                                                                                 DLG_TEXT_WORDWRAP              |
                                                                                 DLG_TEXT_FONT                  |
                                                                                 DLG_TEXT_FOREIMAGE             |
                                                                                 DLG_TEXT_BROWSEIMAGE           |
                                                                                 DLG_TEXT_SHADOWCOLOR           |
                                                                                 DLG_TEXT_SHADOW_X_Y);

      virtual L_INT  DoModalGetGradient( HWND hWndParent   =NULL, L_UINT32 uUIFlags = 
                                                                                    DLG_GRAD_STARTCOLOR            |
                                                                                    DLG_GRAD_ENDCOLOR              |
                                                                                    DLG_GRAD_STEPS                 |
                                                                                    DLG_GRAD_NO_TREEVIEW           |
                                                                                    DLG_GRAD_CLASS_LINEAR          |
                                                                                    DLG_GRAD_CLASS_ANGULAR         |
                                                                                    DLG_GRAD_CLASS_RECTANGULAR     |
                                                                                    DLG_GRAD_CLASS_ELLIPTICAL      |
                                                                                    DLG_GRAD_CLASS_CONICAL);
      virtual L_INT  DoModalGetTransition( HWND hWndParent =NULL, L_UINT32 uUIFlags = 
                                                                                    DLG_TRANS_FORECOLOR       |
                                                                                    DLG_TRANS_BACKCOLOR       |
                                                                                    DLG_TRANS_DELAY           |
                                                                                    DLG_TRANS_GRAIN           |
                                                                                    DLG_TRANS_EFFECT          |
                                                                                    DLG_TRANS_PASSES          |
                                                                                    DLG_TRANS_WAND            |
                                                                                    DLG_TRANS_TRANSPARENT     |
                                                                                    DLG_TRANS_GRADIENT);
      virtual L_INT  DoModalGetDirectory (L_CHAR L_FAR * pszDirectory,L_INT nBuffSize,
                                          HWND hWndParent =NULL);


      virtual L_INT DoModalGetContourFilter( HWND hWndParent=NULL,
                                             L_UINT32 uUIFlags = 
                                                DLG_CONTOUR_OPTION            |      
                                                DLG_CONTOUR_THRESHOLD         |    
                                                DLG_CONTOUR_DELTADIRECTION    |
                                                DLG_CONTOUR_MAXIMUMERROR
                                            );

      virtual L_INT DoModalGetHalftone(HWND hWndParent = NULL);
};

#endif //_LEAD_DIALOG_H_
/*================================================================= EOF =====*/
