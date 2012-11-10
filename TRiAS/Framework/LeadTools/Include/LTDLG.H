/*
   LTDLG.H - LEAD Common Dialog module header file
   Copyright (c) 1991-2000 LEAD Technologies, Inc.
   All Rights Reserved.
*/

#ifndef LTDLG_H
#define LTDLG_H

#include "ltkrn.h"
#include "ltfil.h"
#include "ltimg.h"

#define _HEADER_ENTRY_
#include "ltpck.h"

#define ERROR_LTCOLOR_DLL_NOTLOADED -4

/* callback typedefs */
typedef L_VOID (pEXT_CALLBACK LTCOMMDLGHELPCB) (L_UINT32, L_INT, L_VOID L_FAR*);

/* structure typedefs */
typedef struct _FILEOPENPARM
{
   L_INT32       nSize ;               // size of this structure 
   L_TCHAR       szFileName[L_MAXPATH] ;// filename                                   
   pBITMAPHANDLE pBitmap ;              // Bitmap to fill in if AutoProcess           
   pBITMAPHANDLE pThumbnail ;           // Bitmap to fill in with Thumbnail           
   pFILEINFO     pFileInfo ;            // FILEINFO structure to fill                 
   L_INT         nPageNumber ;          // Page Number to load                        
   L_INT         nPasses ;              // Passes to load from Progressive image file 
   L_BOOL        bLoadCompressed ;      // Load 1-bit image as compressed data?       
   L_BOOL        bLoadRotated ;         // Load image without rotating data?          
   L_BOOL        bPreviewEnabled ;      // TRUE to have Preview enabled               

} FILEOPENPARM, L_FAR* LPFILEOPENPARM ;

// possible values for uSaveMulti 
#define SAVE_OVERWRITE 0
#define SAVE_APPEND    1
#define SAVE_REPLACE   2
#define SAVE_INSERT    3

typedef struct _FILESAVEPARM
{
   L_INT32       nSize  ;                 // size of this structure 
   L_TCHAR       szFileName[L_MAXPATH] ;  // filename                       
   pBITMAPHANDLE pBitmap ;                // Bitmap to save                 
   L_INT         nBitsPerPixel ;          // bits per pixel to save         
   L_INT         nFormat ;                // file format to save            
   L_INT         nQFactor ;               // QFactor value for save         
   L_UINT        uSaveMulti ;             // save as multi-page file?       
   L_BOOL        bSaveInterlaced ;        // save as interlaced GIF?        
   L_BOOL        bSaveProgressive ;       // save as progressive image?     
   L_INT         nPasses ;                // # of progressive passes        
   L_BOOL        bSaveWithStamp ;         // save with stamp preview?       
   L_INT         nStampBits ;             // stamp bits per pixel           
   L_INT         nStampWidth ;            // stamp width                    
   L_INT         nStampHeight ;           // stamp height                   
   L_INT         nPageNumber ;            // Page Number to replace/insert  
   L_INT         nSubTypeIndex ;          // index to the sub-type (if any) 

} FILESAVEPARM, L_FAR* LPFILESAVEPARM ;

typedef struct _FILESAVEFORMAT
{
   L_INT32  nSize  ;         // size of this structure 
   L_INT  nFormat ;          // one of the dlg save formats, DLG_FS_LEAD1, DLG_FS_JFIF8, etc.   
   L_UINT uSubFormats ;      // combination of sub-format flags, if applicable.  DLG_FS_SUB_XXX 
}FILESAVEFORMAT, L_FAR* LPFILESAVEFORMAT ;

typedef struct _EFXDLGPARM
{
   L_INT32  nSize  ;          // size of this structure 
   L_UINT   uEffect ;         // effect to use 
   L_UINT   uGrain ;          // grain size 
   L_UINT   uDelay ;          // delay 
   L_UINT   uMaxPass ;        // maximum passes 
   L_BOOL   bTransparent ;    // use transparent color? 
   COLORREF crTransparent ;   // transparent color 
   L_UINT   uWandWidth ;      // wand width 
   COLORREF crWand ;          // wand color 

} EFXDLGPARM, L_FAR * LPEFXDLGPARM ;

typedef struct _GETNOISEDLGPARM
{
   L_INT32  nSize ;     // size of this structure 
   L_UINT   uRange ;	   // the noise value 
   L_UINT   uChannel ;	// the channel. 

} GETNOISEDLGPARM, L_FAR* LPGETNOISEDLGPARM ;

typedef struct _GETCHANGEDLGPARM
{
   L_INT32     nSize ;        // size of this structure 
   L_INT       nChange ;	   // the change value 
   L_UINT32    uProcess ;	   // flag indicating which function was chosen.  

} GETCHANGEDLGPARM, L_FAR* LPGETCHANGEDLGPARM ;

typedef struct _HALFTONEDLGPARM
{
   L_INT32  nSize ;  // size of this structure 
   L_INT    nAngle ; // the change value 
   L_UINT32 uType ;	// flag indicating which function was chosen.  

} HALFTONEDLGPARM, L_FAR* LPHALFTONEDLGPARM ;

typedef struct _COLORRESDLGPARM
{
   L_INT32  nSize ;
   L_INT    nBitsPerPixel ;   // the desired bits per pixel 
   L_UINT32 uColorResFlags ;  // user's choice of flags 
   HPALETTE hpalCustom ;      

} COLORRESDLGPARM, L_FAR* LPCOLORRESDLGPARM ;

typedef struct _GETANGLEDLGPARM
{
   L_INT32   nSize ;
   L_INT     nAngle ;  // Angle 
   L_BOOL    bFlag ;   // option flag for the dialog 
   L_UINT    uResize ; // 
   COLORREF  crBack ;  // Background color 

} GETANGLEDLGPARM, L_FAR* LPGETANGLEDLGPARM ;

typedef struct _GETSIZEDLGPARM
{
   L_INT32  nSize ;        // size of this structure 
   L_INT    nWidth ;       // the new width 
   L_INT    nHeight ;      // the new width 
   L_UINT   uResize ;      // Flags for the Method of resizing
   L_INT    nResolutionX ;
   L_INT    nResolutionY ;

} GETSIZEDLGPARM, L_FAR* LPGETSIZEDLGPARM ;

typedef struct _GETEMBOSSDLGPARM
{
   L_INT32 nSize ;
   L_UINT  uDepth ;
   L_UINT  uDirection ;

} GETEMBOSSDLGPARM, L_FAR* LPGETEMBOSSDLGPARM ;

typedef struct _GETFILTERDLGPARM
{
   L_INT32      nSize ;
   LPSPATIALFLT pSpatialFlt ;
   LPBINARYFLT  pBinaryFlt ;
   L_BOOL       bSpatialFilter ;

} GETFILTERDLGPARM, L_FAR* LPGETFILTERDLGPARM ;

typedef struct _GETGAMMADLGPARM
{
   L_INT32 nSize ;
   L_INT   nRedValue ;
   L_INT   nGreenValue ;
   L_INT   nBlueValue ;   
   L_BOOL  bAllChannels ;   

} GETGAMMADLGPARM, L_FAR* LPGETGAMMADLGPARM ;

typedef struct _GETRANGEDLGPARM
{
   L_INT32 nSize ;
   L_UINT  uLow ;
   L_UINT  uHigh ;

} GETRANGEDLGPARM, L_FAR* LPGETRANGEDLGPARM ;

typedef struct _CONTOURFILTERDLGPARM
{
   L_INT32  nSize ;
   L_INT16  nThreshold ;
   L_INT16  nDeltaDirection ;
   L_INT16  nMaxError ;
   L_INT    nOption ;
   L_UINT32 uOptionFlags ;

} CONTOURFILTERDLGPARM, L_FAR* LPCONTOURFILTERDLGPARM ;

typedef struct _SHAPEDLGPARM
{
   L_INT32  nSize  ;        // size of this structure 
   L_UINT   uShape ;        // type of shape  
   COLORREF crBack ;        // background color  
   L_UINT   uBackStyle ;    // background style  
   COLORREF crFill ;        // foreground color  
   L_UINT   uFillStyle ;    // foreground style  
   COLORREF crBorder ;      // border color   
   L_UINT   uBorderStyle ;  // border style   
   L_UINT   uBorderWidth ;  // border width   
   COLORREF crInnerHilite ; // inner band highlight color 
   COLORREF crInnerShadow ; // inner band shadow color 
   L_UINT   uInnerStyle ;   // inner band style  
   L_UINT   uInnerWidth ;   // inner band width  
   COLORREF crOuterHilite ; // outer band highlight color 
   COLORREF crOuterShadow ; // outer band shadow color 
   L_UINT   uOuterStyle ;   // outer band style  
   L_UINT   uOuterWidth ;   // outer band width  
   L_INT    nShadowX ;      // horizontal position of the shadow   
   L_INT    nShadowY ;      // vertical position of the shadow  
   COLORREF crShadow ;      // shadow color   

} SHAPEDLGPARM, L_FAR * LPSHAPEDLGPARM ;

typedef struct _TEXTDLGPARM
{
   L_INT32         nSize  ;        // size of this structure 
   L_TCHAR L_FAR * pszSampleText ; // pointer to sample text 
   L_INT           nMaxCount ;     // maximum size of sample text 
   L_INT           nAngle ;        // rotation angle for text 
   L_UINT          uStyle ;        // text style flag 
   L_UINT          uAlign ;        // text align flag 
   L_BOOL          bWordWrap ;     // word wrap 
   HFONT           hFont ;         // handle to font to use 
   COLORREF        crText ;        // text color 
   COLORREF        crHilite ;      // border color 
   COLORREF        crShadow ;      // shadow color 
   L_INT           nXDepth ;       // horz. shadow position 
   L_INT           nYDepth ;       // vert. shadow position 
   L_BOOL          bUseForeImage ; // use foreground image 

} TEXTDLGPARM, L_FAR * LPTEXTDLGPARM ;

typedef struct _GRADDLGPARM
{
   L_INT32  nSize  ;  // size of this structure 
   L_UINT   uStyle ;  // gradient style 
   COLORREF crStart ; // start color 
   COLORREF crEnd ;   // end color 
   L_UINT   uSteps ;  // gradient steps 

} GRADDLGPARM, L_FAR * LPGRADDLGPARM ;

typedef struct _TRANSDLGPARM
{
   L_INT32  nSize  ;        // size of this structure 
   L_UINT   uTransition ;   // transition 
   COLORREF crBack ;        // back/start color 
   COLORREF crFore ;        // fore/end color 
   L_UINT   uSteps ;        // gradient steps 
   L_UINT   uEffect ;       // effect to use 
   L_UINT   uGrain ;        // grain size 
   L_UINT   uDelay ;        // delay 
   L_UINT   uMaxPass ;      // maximum passes 
   L_BOOL   bTransparent ;  // use transparent color? 
   COLORREF crTransparent ; // transparent color 
   L_UINT   uWandWidth ;    // wand width 
   COLORREF crWand ;        // wand color 

} TRANSDLGPARM, L_FAR * LPTRANSDLGPARM ;

typedef struct _GETDIRECTORYDLGPARM
{
   L_INT32        nSize ;          // size of this structure 
   L_TCHAR L_FAR* pszDirectory ; 
   L_INT          nBuffSize ; 
   L_TCHAR L_FAR* pszFilter ;
   L_INT          nFilterIndex ;
   L_TCHAR L_FAR* pszTitle ; 

} GETDIRECTORYDLGPARM, L_FAR* LPGETDIRECTORYDLGPARM ;

typedef struct _WINDOWLEVELDLGPARM
{
   L_INT32           nSize ;          // size of this structure 
   L_RGBQUAD L_HUGE* pLUT ;
   L_UINT32          uLUTLength ; 
   L_INT             nLowBit ; 
   L_INT             nHighBit ; 
   L_UINT            nLow ;
   L_UINT            nHigh ; 
   COLORREF          crStart ; 
   COLORREF          crEnd ;

} WINDOWLEVELDLGPARM, L_FAR* LPWINDOWLEVELDLGPARM ;


/* flags for the Help Callbacks for L_Dlg* function */
#define DLG_HELP_FILEOPEN          1
#define DLG_HELP_FILESAVE          2
#define DLG_HELP_COLORRES          3
#define DLG_HELP_GETANGLE          4
#define DLG_HELP_GETSIZE           5
#define DLG_HELP_GETFILTER         6
#define DLG_HELP_GETCHANGE         7
#define DLG_HELP_GETRANGE          8
#define DLG_HELP_GETGAMMA          9
#define DLG_HELP_GETNOISE          10
#define DLG_HELP_GETEMBOSS         11
#define DLG_HELP_WINDOWLEVEL       12
#define DLG_HELP_GETEFFECT         13
#define DLG_HELP_GETSHAPE          14
#define DLG_HELP_GETTEXT           15
#define DLG_HELP_GETGRADIENT       16
#define DLG_HELP_GETTRANSITION     17
#define DLG_HELP_GETDIR            18
#define DLG_HELP_GETRES            19
#define DLG_HELP_CONTOUR           20
#define DLG_HELP_HALFTONE          21
#define DLG_HELP_PDF               22
#define DLG_HELP_COLOR             23
#define DLG_HELP_VECTOROPTIONS     24
#define DLG_HELP_DFXANDDWGOPTIONS  25
#define DLG_HELP_PLTOPTIONS        26
#define DLG_HELP_ADVANCEJ2KOPTIONS 27
#define DLG_HELP_FILEINFO          28


/* flags for L_DlgFileOpen() */
#define DLG_FO_AUTOPROCESS          0x00000001   /* Dlg should autoprocess image and fill the pBitmap */
#define DLG_FO_PROGRESSIVE          0x00000002   /* FileOpen Dlg should have Prog. File options */
#define DLG_FO_MULTIPAGE            0x00000004   /* FileOpen Dlg should have Multipage options */
#define DLG_FO_LOADROTATED          0x00000008   /* FileOpen Dlg should have Load Rotated option */
#define DLG_FO_LOADCOMPRESSED       0x00000010   /* FileOpen Dlg should have Load 1-bit compressed option */
#define DLG_FO_FILEINFO             0x00000020   /* FileOpen Dlg should have FileInfo button */
#define DLG_FO_SHOWPREVIEW          0x00000040   /* FileOpen Dlg should have ThumbNail and should create the */
                                                 /* preview if none is stored in the file */
#define DLG_FO_SHOWSTAMP            0x00000080   /* FileOpen Dlg should have ThumbNail and should only load */
                                                 /* the preview stamp if one is stored in the file */
#define DLG_FO_DELPAGE              0x00000200   /* FileOpen Dlg should have Delete Page option */
#define DLG_FO_RESDLG               0x00000400   /* If AutoProcess, and format supports resolution, show
                                                 GetRes dlg */
#define DLG_FO_NOFILEMUSTEXIST      0x00000800 /* Do not verify that the path exists */
#define DLG_FO_NOPATHMUSTEXIST      0x00001000 /* Do not verify that the file exists */
                                    
#define DLG_GETRES_95CONTEXTHELP    0x00002000 /* GetRes Dlg should contain context sensitive help icon */

#define DLG_FO_FILEINFO_TOTALPAGES  0x00004000 /* when filling FILEINFO, get TOTALPAGES */
#define DLG_FO_FILEINFO_PDFDLG      0x00008000 /*  If AutoProcess, and format is PDF , show
                                                   PDF options dlg */
#define DLG_FO_ENABLESIZING         0x00010000 /* Enable sizing in the dialog*/
#define DLG_PDFDLG_95CONTEXTHELP    0x00020000 /* PDF Dlg should contain context sensitive help icon */
#define DLG_FO_VECTOROPTIONSDLG     0x00040000

/* flags for L_DlgFileSave() */
#define DLG_FS_AUTOPROCESS    0x00000001   /* Dlg should autoprocess image and fill the pBitmap */
#define DLG_FS_PROGRESSIVE    0x00000002   /* FileSave Dlg should have Prog. File options */
#define DLG_FS_MULTIPAGE      0x00000004   /* FileSave Dlg should have Multipage options */
#define DLG_FS_STAMP          0x00000008   /* FileSave Dlg should have save with stamp options */
#define DLG_FS_QFACTOR        0x00000010   /* FileSave Dlg should have QFactor option */
#define DLG_FS_ENABLESIZING   0x00000100   /* Enable sizing in the dialog*/

/* file save format option constants for L_DlgFileSave*/
/* top-level formats */
enum {
   FS_LEAD24 = 0,
   FS_LEAD8,
   FS_LEAD1BIT,
   FS_JFIF24,
   FS_JFIF16,
   FS_JFIF12,
   FS_JFIF8,
   FS_CALS,
   FS_PNG1,
   FS_PNG4,
   FS_PNG8,
   FS_PNG24,
   FS_PNG32,
   FS_DICOM8,
   FS_DICOM16,
   FS_DICOM24,
   FS_FAX,
   FS_EPS,
   FS_EXIF,
   FS_FPX24,
   FS_FPX8,
   FS_IMG,
   FS_GIF1,
   FS_GIF2,
   FS_GIF3,
   FS_GIF4,
   FS_GIF5,
   FS_GIF6,
   FS_GIF7,
   FS_GIF8,
   FS_IOCA,
   FS_MODCA,
   FS_PCT1,
   FS_PCT4,
   FS_PCT8,
   FS_PCT24,
   FS_MAC,
   FS_AWD,
   FS_MSP,
   FS_OS2BMP1,
   FS_OS2BMP4,
   FS_OS2BMP8,
   FS_OS2BMP24,
   FS_PCX1,
   FS_PCX4,
   FS_PCX8,
   FS_PCX24,
   FS_PSD1,
   FS_PSD8,
   FS_PSD24,
   FS_RAS1,
   FS_RAS4,
   FS_RAS8,
   FS_RAS24,
   FS_RAS32,
   FS_TGA8,
   FS_TGA16,
   FS_TGA24,
   FS_TGA32,
   FS_TIFF1,
   FS_TIFF2,
   FS_TIFF3,
   FS_TIFF4,
   FS_TIFF5,
   FS_TIFF6,
   FS_TIFF7,
   FS_TIFF8,
   FS_TIFF12,
   FS_TIFF16,
   FS_TIFF24,
   FS_TIFF32,
   FS_BMP1,
   FS_BMP4,
   FS_BMP8,
   FS_BMP16,
   FS_BMP24,
   FS_BMP32,
   FS_WFX,
   FS_WMF8,
   FS_WMF24,
   FS_EMF8,
   FS_EMF24,
   FS_WPG1,
   FS_WPG4,
   FS_WPG8,
   FS_ICO1,
   FS_ICO4,
   FS_ICO8,
   FS_ICO24,
   FS_CUR1,
   FS_CUR4,
   FS_CUR8,
   FS_CUR24,
   FS_JBIG1,
   FS_JBIG2,
   FS_JBIG3,
   FS_JBIG4,
   FS_JBIG5,
   FS_JBIG6,
   FS_JBIG7,
   FS_JBIG8,
   FS_CUT,
   FS_PPM,
   FS_PGM,
   FS_PBM,
   FS_IFF1,
   FS_IFF2,
   FS_IFF3,
   FS_IFF4,
   FS_IFF5,
   FS_IFF6,
   FS_IFF7,
   FS_IFF8,
   FS_IFF24,
   FS_XBM,
   FS_XPM8,
   FS_XPM16,
   FS_XPM24,
   FS_XPM32,
   FS_ITG,
   FS_TIFF48,
   FS_TIFF64,
   FS_FLC8,
   FS_ANI1,
   FS_ANI4,
   FS_ANI8,
   FS_ANI24,
   FS_XWD10_1,
   FS_XWD10_4,
   FS_XWD10_8,
   FS_XWD11_1,
   FS_XWD11_4,
   FS_XWD11_8,
   FS_XWD11_16,
   FS_XWD11_24,
   FS_XWD11_32,
   FS_SGI8,
   FS_SGI24,
   FS_SGI32,
   FS_CLP1,
   FS_CLP4,
   FS_CLP8,
   FS_CLP24,
   FS_RAW,
   
   #ifndef FOR_LEADViEW
   FS_PDF1,
   FS_PDF2,
   FS_PDF4,
   FS_PDF8,
   FS_PDF24,
   #endif
      
   FS_J2K8,
   FS_J2K24,
   FS_CMW8,
   FS_CMW24,
   FS_J2K12,
   FS_J2K16,
   FS_CMW12,
   FS_CMW16,
   FS_PCT16,
   FS_WBMP,
   FS_SCT24,
   FS_SMP,

#ifdef FOR_LEADViEW   

   FS_PSP1,
   FS_PSP4,
   FS_PSP8,
   FS_PSP24,
   FS_ECW,   
   FS_TIFX1,
   FS_TIFX3,
   FS_TIFX8,
   FS_TIFX24,

#endif

   FS_MAX
};

// FileSave sub-format values        
// LEAD CMP file subtypes (8,24-bit) 
#define DLG_FS_SUB_CMP_NONPROGRESSIVE           0x0001
#define DLG_FS_SUB_CMP_PROGRESSIVE              0x0002
// JPEG file subtypes (24-bit)       
#define DLG_FS_SUB_JPEG24_YUV_444               0x0001
#define DLG_FS_SUB_JPEG24_YUV_422               0x0002
#define DLG_FS_SUB_JPEG24_YUV_411               0x0004
#define DLG_FS_SUB_JPEG24_PROG_444              0x0008
#define DLG_FS_SUB_JPEG24_PROG_422              0x0010
#define DLG_FS_SUB_JPEG24_PROG_411              0x0020
#define DLG_FS_SUB_JPEG24_LOSSLESS              0x0040
// JPEG file subtypes (12-bit)       
#define DLG_FS_SUB_JPEG12_YUV_400               0x0001
#define DLG_FS_SUB_JPEG12_LOSSLESS              0x0002
// JPEG file subtypes (8-bit)        
#define DLG_FS_SUB_JPEG8_YUV_400                0x0001
#define DLG_FS_SUB_JPEG8_PROG_400               0x0002
#define DLG_FS_SUB_JPEG8_LOSSLESS               0x0004

//new ver 13.0
// JPEG 2000 file subtypes (8,12,16,24-bit)
#define DLG_FS_SUB_J2K_STREAM                   0x0001
#define DLG_FS_SUB_J2K_JP2                      0x0002

// DICOM file subtypes (8-bit)       
#define DLG_FS_SUB_DICOM8_GRAY                  0x0001
#define DLG_FS_SUB_DICOM8_COLOR                 0x0002
// DICOM file subtypes (Other-bit)   
#define DLG_FS_SUB_DICOM_RLE_GRAY               0x0001
#define DLG_FS_SUB_DICOM_RLE_COLOR              0x0002
#define DLG_FS_SUB_DICOM_JPEG_GRAY              0x0004
#define DLG_FS_SUB_DICOM_LOSSLESSJPEG_GRAY      0x0008
#define DLG_FS_SUB_DICOM_JPEG_COLOR             0x0010
#define DLG_FS_SUB_DICOM_LOSSLESSJPEG_COLOR     0x0020
// RAW FAX, IOCA, & MODCA subtypes   
#define DLG_FS_SUB_FAX_G3_1D                    0x0001
#define DLG_FS_SUB_FAX_G3_2D                    0x0002
#define DLG_FS_SUB_FAX_G4                       0x0004
// EXIF file subtypes                
#define DLG_FS_SUB_EXIF_UNCOMPRESSEDRGB         0x0001
#define DLG_FS_SUB_EXIF_UNCOMPRESSEDYCC         0x0002
#define DLG_FS_SUB_EXIF_JPEG_411                0x0004
#define DLG_FS_SUB_EXIF_JPEG_422                0x0008
// FPX file subtypes                 
#define DLG_FS_SUB_FPX_UNCOMPRESSED             0x0001
#define DLG_FS_SUB_FPX_SINGLECOLOR              0x0002
#define DLG_FS_SUB_FPX_DEFQFACTOR               0x0004
#define DLG_FS_SUB_FPX_SPECQFACTOR              0x0008
// GIF file subtypes                 
#define DLG_FS_SUB_GIF_INTERLACED89A            0x0001
#define DLG_FS_SUB_GIF_NONINTERLACED89A         0x0002
// OS/2 BMP file subtypes            
#define DLG_FS_SUB_OS2_VER1                     0x0001
#define DLG_FS_SUB_OS2_VER2                     0x0002
// TIFF file subtypes (1-bit)        
#define DLG_FS_SUB_TIFF1_CCITT                  0x0001
#define DLG_FS_SUB_TIFF1_CCITT_G3_1D            0x0002
#define DLG_FS_SUB_TIFF1_CCITT_G3_2D            0x0004
#define DLG_FS_SUB_TIFF1_CCITT_G4               0x0008
#define DLG_FS_SUB_TIFF1_UNCOMPRESSEDRGB        0x0010
#define DLG_FS_SUB_TIFF1_RLERGB                 0x0020
#define DLG_FS_SUB_TIFF1_LZWRGB                 0x0040
// TIFF file subtypes (2,3,4,5,6,7-bit) 
#define DLG_FS_SUB_TIFFOTHER_UNCOMPRESSED       0x0001
#define DLG_FS_SUB_TIFFOTHER_RLE                0x0002
#define DLG_FS_SUB_TIFFOTHER_LZW                0x0004
// TIFF file subtypes (8-bit)        
#define DLG_FS_SUB_TIFF8_UNCOMPRESSEDRGB        0x0001
#define DLG_FS_SUB_TIFF8_RLERGB                 0x0002
#define DLG_FS_SUB_TIFF8_JPEG_GRAY_YCC          0x0004
#define DLG_FS_SUB_TIFF8_LOSSLESSJPEG           0x0008
#define DLG_FS_SUB_TIFF8_LZWRGB                 0x0010
 // new for ver 13.0
#define DLG_FS_SUB_TIFF8_JBIG                   0x0020
#define DLG_FS_SUB_TIFF8_CMP                    0x0040
#define DLG_FS_SUB_TIFF8_J2K                    0x0080
#define DLG_FS_SUB_TIFF8_CMW                    0x0100

// TIFF file subtypes (12-bit)       
#define DLG_FS_SUB_TIFF12_UNCOMPRESSED          0x0001
#define DLG_FS_SUB_TIFF12_RLE                   0x0002
#define DLG_FS_SUB_TIFF12_LOSSLESSJPEG          0x0004
#define DLG_FS_SUB_TIFF12_JPEG_GRAY_YCC         0x0008
#define DLG_FS_SUB_TIFF12_LZW                   0x0010
// new for ver 13.0
#define DLG_FS_SUB_TIFF12_J2K                   0x0020
#define DLG_FS_SUB_TIFF12_CMW                   0x0040

// TIFF file subtypes (16-bit)       
#define DLG_FS_SUB_TIFF16_UNCOMPRESSED          0x0001
#define DLG_FS_SUB_TIFF16_RLE                   0x0002
#define DLG_FS_SUB_TIFF16_LOSSLESSJPEG          0x0004
#define DLG_FS_SUB_TIFF16_LZW                   0x0008
// new for ver 13.0
#define DLG_FS_SUB_TIFF16_J2K                   0x0010
#define DLG_FS_SUB_TIFF16_CMW                   0x0020

// TIFF file subtypes (24-bit)       
#define DLG_FS_SUB_TIFF24_UNCOMPRESSEDRGB       0x0001
#define DLG_FS_SUB_TIFF24_UNCOMPRESSEDCMYK      0x0002
#define DLG_FS_SUB_TIFF24_UNCOMPRESSEDYCC       0x0004
#define DLG_FS_SUB_TIFF24_RLERGB                0x0008
#define DLG_FS_SUB_TIFF24_RLECMYK               0x0010
#define DLG_FS_SUB_TIFF24_RLEYCC                0x0020
#define DLG_FS_SUB_TIFF24_JPEG_YCC_444          0x0040
#define DLG_FS_SUB_TIFF24_JPEG_YCC_422          0x0080
#define DLG_FS_SUB_TIFF24_JPEG_YCC_411          0x0100
#define DLG_FS_SUB_TIFF24_LOSSLESSJPEG          0x0200
#define DLG_FS_SUB_TIFF24_LZWRGB                0x0400
#define DLG_FS_SUB_TIFF24_LZWCMYK               0x0800
#define DLG_FS_SUB_TIFF24_LZWYCC                0x1000

// new for ver 13.0
#define DLG_FS_SUB_TIFF24_CMP_NONPROGRESSIVE    0x2000
#define DLG_FS_SUB_TIFF24_CMP_PROGRESSIVE       0x4000
#define DLG_FS_SUB_TIFF24_J2K                   0x8000
#define DLG_FS_SUB_TIFF24_CMW                   0x00010000

// TIFF file subtypes (32-bit)       
#define DLG_FS_SUB_TIFF32_UNCOMPRESSEDRGB       0x0001
#define DLG_FS_SUB_TIFF32_UNCOMPRESSEDCMYK      0x0002
#define DLG_FS_SUB_TIFF32_RLERGB                0x0004
#define DLG_FS_SUB_TIFF32_RLECMYK               0x0008
#define DLG_FS_SUB_TIFF32_LZWRGB                0x0010
#define DLG_FS_SUB_TIFF32_LZWCMYK               0x0020
// TIFF file subtypes (48-bit)       
#define DLG_FS_SUB_TIFF48_UNCOMPRESSEDRGB       0x0001
#define DLG_FS_SUB_TIFF48_LZWRGB                0x0002
// TIFF file subtypes (64-bit)       
#define DLG_FS_SUB_TIFF64_UNCOMPRESSEDRGB       0x0001
#define DLG_FS_SUB_TIFF64_LZWRGB                0x0002
// BMP file subtypes (4 and 8-bit only) 
#define DLG_FS_SUB_BMP_UNCOMPRESSED             0x0001
#define DLG_FS_SUB_BMP_RLECOMPRESSED            0x0002
// WFX file subtypes                 
#define DLG_FS_SUB_WFX_CCITT_G3_1D              0x0001
#define DLG_FS_SUB_WFX_CCITT_G4                 0x0002
// PPM file subtypes                 
#define DLG_FS_SUB_PPM_ASCII                    0x0001
#define DLG_FS_SUB_PPM_BINARY                   0x0002
// PGM file subtypes 
#define DLG_FS_SUB_PGM_ASCII                    0x0001
#define DLG_FS_SUB_PGM_BINARY                   0x0002
// PBM file subtypes 
#define DLG_FS_SUB_PBM_ASCII                    0x0001
#define DLG_FS_SUB_PBM_BINARY                   0x0002
// IFF file subtypes 
// All BitsPerPixel have subtypes 
#define DLG_FS_SUB_IFF_ILBM_RLE                 0x0001
#define DLG_FS_SUB_IFF_CAT_RLE                  0x0002
// SGI file subtypes 
// All BitsPerPixel have subtypes 
#define DLG_FS_SUB_SGI_UNCOMPRESSED             0x0001
#define DLG_FS_SUB_SGI_RLECOMPRESSED            0x0002
// PDF file subtypes (1-bit)       
#define DLG_FS_SUB_PDF1_UNCOMPRESSED            0x0001
#define DLG_FS_SUB_PDF1_CCITT_G3_1D             0x0002
#define DLG_FS_SUB_PDF1_CCITT_G3_2D             0x0004
#define DLG_FS_SUB_PDF1_CCITT_G4                0x0008
// PDF file subtypes (8-bit)       
#define DLG_FS_SUB_PDF8_UNCOMPRESSED            0x0001
#define DLG_FS_SUB_PDF8_LOSSLESSJPEG            0x0002
// PDF file subtypes (24-bit)       
#define DLG_FS_SUB_PDF24_UNCOMPRESSED           0x0001
#define DLG_FS_SUB_PDF24_YUV_444                0x0002
#define DLG_FS_SUB_PDF24_YUV_422                0x0004
#define DLG_FS_SUB_PDF24_YUV_411                0x0008

// RAS file subtypes
#define DLG_FS_SUB_RAS_RLE          0x0001
#define DLG_FS_SUB_RAS_UNCOMPRESSED 0x0002

// PSP file subtypes (1, 4, 8, 24 bit )
#define DLG_FS_SUB_PSP_RLE          0x0001
#define DLG_FS_SUB_PSP_UNCOMPRESSED 0x0002

// PSP file subtypes (1, 4, 8, 24 bit )
#define DLG_FS_SUB_PSP_RLE          0x0001
#define DLG_FS_SUB_PSP_UNCOMPRESSED 0x0002

// TIFX file subtypes (1 bit)
#define DLG_FS_SUB_TIFX_CCITT_G4    0x0001
#define DLG_FS_SUB_TIFX_CCITT_G3_1D 0x0002
#define DLG_FS_SUB_TIFX_CCITT_G3_2D 0x0004
#define DLG_FS_SUB_TIFX_JBIG        0x0008

// SVG file subtypes 
#define DLG_FS_SUB_SVG_EXTERNAL     0x0001
#define DLG_FS_SUB_SVG_EMBEDDED     0x0002


/* flags for L_DlgGetDir() */
#define DLG_GD_95CONTEXTHELP  0x00000002  /* Dlg should contain context sensitive help icon */

/* flags for Image processing dialog functions */
#define DLG_IMG_AUTOPROCESS     0x80000000   /* Dlg should autoprocess image and fill the pBitmap */
#define DLG_IMG_SHOWPREVIEW     0x40000000   /* ImageProcess Dlg should preview of image */
#define DLG_IMG_HIDEBACKCOLOR   0x20000000   /* GetAngle Dlg should hide the Background Color button */
#define DLG_IMG_95CONTEXTHELP   0x10000000   /* Dlg should contain context sensitive help icon */
#define DLG_IMG_SHOWRESIZEOPT   0x08000000   /* GetAngle Dlg should show resize options */
#define DLG_IMG_INIT_DLG        0x04000000   // Initialize the width and height fields with the user data. 
#define DLG_IMG_TOOL            0x02000000   // Dlg should show the toolbar 
#define DLG_IMG_PERCENTAGE      0x01000000   // Image resize Dlg should Percentage value combo
#define DLG_IMG_IDENTICALVAL    0x00100000   // Image resize Dlg should Identical value check box
#define DLG_IMG_MAINTAINASPECT  0x00200000   // Image resize Dlg should Maintain aspect  check box
#define DLG_IMG_RESOLUTIONGRP   0x00400000   // Image resize Dlg should Resolution group information
#define DLG_IMG_USESYSCOLORDLG  0x00800000   /* Use windows color picker dialog */

#define DLG_IMG_ROTATE          0x00000001   /* rotate dialog */
#define DLG_IMG_SHEAR           0x00000002   /* shear dialog */

#define DLG_IMG_GRADIENT        0x00000001   /* gradient dialog */
#define DLG_IMG_LAPLACIAN       0x00000002   /* laplacian dialog */
#define DLG_IMG_SOBEL           0x00000004   /* sobel dialog */
#define DLG_IMG_PREWITT         0x00000008   /* prewitt dialog */
#define DLG_IMG_SHIFTDIFF       0x00000010   /* shiftdiff dialog */
#define DLG_IMG_LINESEG         0x00000020   /* lineseg dialog */
#define DLG_IMG_EROSION         0x00000040   /* erosion dialog */
#define DLG_IMG_DILATION        0x00000080   /* dilation dialog */

#define DLG_IMG_SHARPEN         0x00000001   /* sharpen dialog */
#define DLG_IMG_BRIGHTNESS      0x00000002   /* brightness dialog */
#define DLG_IMG_CONTRAST        0x00000004   /* contrast dialog */
#define DLG_IMG_SATURATION      0x00000008   /* saturation dialog */
#define DLG_IMG_HISTOCONTRAST   0x00000010   /* histo contrast dialog */
#define DLG_IMG_HUE             0x00000020   /* hue dialog */
#define DLG_IMG_POSTERIZE       0x00000040   /* posterize dialog */
#define DLG_IMG_MOSAIC          0x00000080   /* mosaic dialog */
#define DLG_IMG_AVERAGE         0x00000100   /* average dialog */
#define DLG_IMG_MEDIAN          0x00000200   /* median dialog */
#define DLG_IMG_OILIFY          0x00000400   /* oilify dialog */
#define DLG_IMG_MIN             0x00000800   /* min filter dialog */
#define DLG_IMG_MAX             0x00001000   /* max filter dialog */
#define DLG_IMG_SOLARIZE        0x00002000   /* solarize dialog */

#define DLG_IMG_ADDNOISE        0x0000001C   /* add noise dialog */
#define DLG_IMG_GAMMACORRECT    0x0000001D   /* gamma correct dialog */
#define DLG_IMG_EMBOSS          0x0000001E   /* emboss filter dialog */
#define DLG_IMG_INTENSITYDETECT 0x0000001F   /* intensity detect dialog */

#define DLG_IMG_TOOL_RESIZE         0x00004000
#define DLG_IMG_TOOL_ONSCREEN       0x00008000
#define DLG_IMG_TOOL_SHOWEFFECT     0x00010000   
#define DLG_IMG_FORCELINKCHANNELS   0x00020000  // To Force the dialog to apply "Link all channels" all the times.
#define DLG_IMG_TOOL_RESET          0x00040000

/* flags for L_DlgColorRes() */
#define DLG_CR_SHOWPREVIEW      0x0001   /* shows preview of image */
#define DLG_CR_AUTOPROCESS      0x0002   /* process the image on OK */
#define DLG_CR_95CONTEXTHELP    0x0004   /* Dlg should contain context sensitive help icon */
//New controls Ver 13
#define DLG_CR_OPENPALFILEBTN   0x0008   // Dlg should contain Open palett file button 
#define DLG_CR_TOOL             0x0010   // Dlg should contain toolbar in the dialog
#define DLG_CR_ORDER            0x0020   // color order is an option */

#define DLG_CR_1BIT             0x00000001   /* 1-bit is an option */
#define DLG_CR_2BIT             0x00000002   /* 2-bit is an option */
#define DLG_CR_3BIT             0x00000004   /* 3-bit is an option */
#define DLG_CR_4BIT             0x00000008   /* 4-bit is an option */
#define DLG_CR_5BIT             0x00000010   /* 5-bit is an option */
#define DLG_CR_6BIT             0x00000020   /* 6-bit is an option */
#define DLG_CR_7BIT             0x00000040   /* 7-bit is an option */
#define DLG_CR_8BIT             0x00000080   /* 8-bit is an option */
#define DLG_CR_12BIT            0x00000100   /* 12-bit is an option */
#define DLG_CR_16BIT            0x00000200   /* 16-bit is an option */
#define DLG_CR_24BIT            0x00000400   /* 24-bit is an option */
#define DLG_CR_32BIT            0x00000800   /* 32-bit is an option */
#define DLG_CR_48BIT            0x00001000   /* 48-bit is an option */
#define DLG_CR_64BIT            0x00002000   /* 64-bit is an option */
#define DLG_CR_BITALL           0x00003FFF   /* All BitsPerPixel are options */

#define DLG_CR_DITHER_NONE      0x00004000   /* no dithering is an option */
#define DLG_CR_DITHER_FLOYD     0x00008000   /* floyd dithering is an option */
#define DLG_CR_DITHER_STUCKI    0x00010000   /* stucki dithering is an option */
#define DLG_CR_DITHER_BURKES    0x00020000   /* burkes dithering is an option */
#define DLG_CR_DITHER_SIERRA    0x00040000   /* sierra dithering is an option */
#define DLG_CR_DITHER_STEVENSON 0x00080000   /* stevenson dithering is an option */
#define DLG_CR_DITHER_JARVIS    0x00100000   /* jarvis dithering is an option */
#define DLG_CR_DITHER_CLUSTER   0x00200000   /* clustered dithering is an option */
#define DLG_CR_DITHER_ORDERED   0x00400000   /* ordered dithering is an option */
#define DLG_CR_DITHER_ALL       0x007FC000   /* All dithering methods are options */

#define DLG_CR_PAL_FIXED        0x00800000   /* fixed palette is an option */
#define DLG_CR_PAL_OPTIMIZED    0x01000000   /* fixed palette is an option */
#define DLG_CR_PAL_IDENTITY     0x02000000   /* identity palette is an option */
#define DLG_CR_PAL_NETSCAPE     0x04000000   /* netscape palette is an option */
//New Pallet Ver 13
#define DLG_CR_PAL_SVGA         0x08000000   // SVGA palette is an option 
#define DLG_CR_PAL_UNIFORM      0x10000000   // Uniform palette is an option 
#define DLG_CR_PAL_MSIE         0x20000000   // MSIE palette is an option 
#define DLG_CR_PAL_ALL          0x3F800000   // All palette options are options 

#define DLG_CR_ORDER_HIDEGRAYSCALE  0x40000000 // To hide the Gray Scale color order

#define DLG_CR_TOOL_RESIZE      0x00000040
#define DLG_CR_TOOL_ONSCREEN    0x00000080
#define DLG_CR_TOOL_SHOWEFFECT  0x00000100
#define DLG_CR_TOOL_RESET       0x00000200

/* flags for L_DlgWindowLevel() */
#define DLG_WL_SHOWPREVIEW      0x00000001   /* shows preview of image */
#define DLG_WL_AUTOPROCESS      0x00000002   /* process the image on OK */
#define DLG_WL_95CONTEXTHELP    0x00000004   /* Dlg should contain context sensitive help icon */
#define DLG_WL_USESYSCOLORDLG   0x00000008   /* Use windows color picker dialog */
#define DLG_WL_USENEWLUTFILL    0x00000010   /* Use L_DlgWindowLevelFillLUT2 */

/* flags for L_DlgGetEffect() */
#define DLG_EFX_SHOWPREVIEW      0x00000001   /* shows preview of image */
#define DLG_EFX_AUTOPREVIEW      0x00000002   /* auto preview when options change */
#define DLG_EFX_DELAY            0x00000004   /* effect delay is an option */
#define DLG_EFX_GRAIN            0x00000008   /* effect grain is an option */
#define DLG_EFX_PASSES           0x00000010   /* effect passes is an option */
#define DLG_EFX_TRANSPARENT      0x00000020   /* transparency is an option */
#define DLG_EFX_WAND             0x00000040   /* wand is an option */
#define DLG_EFX_NO_TREEVIEW      0x00000080   /* DO NOT use TreeView */
#define DLG_EFX_CLASS_NONE       0x00000100   /* no effect class is option */
#define DLG_EFX_CLASS_WIPE       0x00000200   /* linear wipe class is option */
#define DLG_EFX_CLASS_WIPERECT   0x00000400   /* rect wipe class is option */
#define DLG_EFX_CLASS_WIPECIRCLE 0x00000800   /* circle wipe class is option */
#define DLG_EFX_CLASS_PUSH       0x00001000   /* push class is option */
#define DLG_EFX_CLASS_SLIDE      0x00002000   /* slide class is option */
#define DLG_EFX_CLASS_ROLL       0x00004000   /* roll class is option */
#define DLG_EFX_CLASS_ROTATE     0x00008000   /* rotate class is option */
#define DLG_EFX_CLASS_ZOOM       0x00010000   /* zoom class is option */
#define DLG_EFX_CLASS_DRIP       0x00020000   /* drip class is option */
#define DLG_EFX_CLASS_BLIND      0x00040000   /* blind class is option */
#define DLG_EFX_CLASS_RANDOM     0x00080000   /* random class is option */
#define DLG_EFX_CLASS_CHECK      0x00100000   /* check class is option */
#define DLG_EFX_CLASS_BLOCKS     0x00200000   /* blocks class is option */
#define DLG_EFX_CLASS_CIRCLE     0x00400000   /* circle class is option */
#define DLG_EFX_CLASS_ELLIPSE    0x00800000   /* ellipse class is option */
#define DLG_EFX_95CONTEXTHELP    0x01000000   /* Dlg should contain context sensitive help icon */
#define DLG_EFX_USESYSCOLORDLG   0x02000000   /* Use windows color picker dialog */

/* flags for L_DlgGetShape() */
#define DLG_SHAPE_SHOWPREVIEW          0x00000001   /* shows preview of image */
#define DLG_SHAPE_AUTOPREVIEW          0x00000002   /* auto preview when options change */
#define DLG_SHAPE_BACKSTYLE            0x00000004   /* backstyle is an option */
#define DLG_SHAPE_FILLSTYLE            0x00000008   /* fillstyle is an option */
#define DLG_SHAPE_FORE_BACK_COLOR      0x00000010   /* fore and back colors are options */
#define DLG_SHAPE_BORDERSTYLE          0x00000020   /* borderstyle is an option */
#define DLG_SHAPE_BORDERWIDTH          0x00000040   /* border width is an option */
#define DLG_SHAPE_BORDERCOLOR          0x00000080   /* bordercolor is an option */
#define DLG_SHAPE_INNERSTYLE           0x00000100   /* innerbandstyle is an option */
#define DLG_SHAPE_INNERWIDTH           0x00000200   /* innerband width is an option */
#define DLG_SHAPE_INNER_HILITE_SHADOW  0x00000400   /* innerband colors are options */
#define DLG_SHAPE_OUTERSTYLE           0x00000800   /* outerbandstyle is an option */
#define DLG_SHAPE_OUTERWIDTH           0x00001000   /* outerband width is an option */
#define DLG_SHAPE_OUTER_HILITE_SHADOW  0x00002000   /* outerband colors are options */
#define DLG_SHAPE_SHADOWCOLOR          0x00004000   /* shadow color is an option */
#define DLG_SHAPE_SHADOW_X_Y           0x00008000   /* shadow x and y are options */
#define DLG_SHAPE_BROWSEIMAGE          0x00010000   /* browse image button is option */
#define DLG_SHAPE_NO_TREEVIEW          0x00020000   /* DO NOT use TreeView */
#define DLG_SHAPE_CLASS_SQUARE         0x00040000   /* squares are options */
#define DLG_SHAPE_CLASS_RECTANGLE      0x00080000   /* rectangles are options */
#define DLG_SHAPE_CLASS_PARALLELOGRAM  0x00100000   /* parallelograms are options */
#define DLG_SHAPE_CLASS_TRAPEZOID      0x00200000   /* trapezoids are options */
#define DLG_SHAPE_CLASS_TRIANGLE       0x00400000   /* triangles are options */
#define DLG_SHAPE_CLASS_OTHER          0x00800000   /* other polygons are options */
#define DLG_SHAPE_CLASS_CIRCLE         0x01000000   /* circles are options */
#define DLG_SHAPE_CLASS_ELLIPSE        0x02000000   /* ellipses are options */
#define DLG_SHAPE_CLASS_STAR           0x04000000   /* stars are options */
#define DLG_SHAPE_CLASS_CROSS          0x08000000   /* crosses are options */
#define DLG_SHAPE_CLASS_ARROW          0x10000000   /* arrows are options */
#define DLG_SHAPE_95CONTEXTHELP        0x20000000   /* Dlg should contain context sensitive help icon */
#define DLG_SHAPE_USESYSCOLORDLG       0x40000000   /* Use windows color picker dialog */

/* flags for L_DlgGetText() */
#define DLG_TEXT_SHOWPREVIEW           0x00000001   /* shows preview of image */
#define DLG_TEXT_AUTOPREVIEW           0x00000002   /* auto preview when options change */
#define DLG_TEXT_SAMPLETEXT            0x00000004   /* sample text edit box is an option */
#define DLG_TEXT_STYLE                 0x00000008   /* text style is an option */
#define DLG_TEXT_COLOR                 0x00000010   /* text color is an option */
#define DLG_TEXT_BORDERCOLOR           0x00000020   /* bordercolor is an option */
#define DLG_TEXT_ALIGN                 0x00000040   /* alignment is an option */
#define DLG_TEXT_ANGLE                 0x00000080   /* angle is an option */
#define DLG_TEXT_WORDWRAP              0x00000100   /* wordwrap is an option */
#define DLG_TEXT_FONT                  0x00000200   /* font is an option */
#define DLG_TEXT_FOREIMAGE             0x00000400   /* foreground image is an option */
#define DLG_TEXT_BROWSEIMAGE           0x00000800   /* browse image button is option */
#define DLG_TEXT_SHADOWCOLOR           0x00001000   /* shadow color is an option */
#define DLG_TEXT_SHADOW_X_Y            0x00002000   /* shadow x and y are options */
#define DLG_TEXT_95CONTEXTHELP         0x00004000   /* Dlg should contain context sensitive help icon */
#define DLG_TEXT_USESYSCOLORDLG        0x00008000   /* Use windows color picker dialog */

/* flags for L_DlgGetGradient() */
#define DLG_GRAD_SHOWPREVIEW           0x00000001   /* shows preview of image */
#define DLG_GRAD_AUTOPREVIEW           0x00000002   /* auto preview when options change */
#define DLG_GRAD_STARTCOLOR            0x00000004   /* start color is an option */
#define DLG_GRAD_ENDCOLOR              0x00000008   /* end color is an option */
#define DLG_GRAD_STEPS                 0x00000010   /* gradient steps is an option */
#define DLG_GRAD_NO_TREEVIEW           0x00000020   /* DO NOT use TreeView */
#define DLG_GRAD_CLASS_LINEAR          0x00000040   /* linear gradients are an option */
#define DLG_GRAD_CLASS_ANGULAR         0x00000080   /* angular gradients are an option */
#define DLG_GRAD_CLASS_RECTANGULAR     0x00000100   /* rectangular gradients are an option */
#define DLG_GRAD_CLASS_ELLIPTICAL      0x00000200   /* elliptical gradients are an option */
#define DLG_GRAD_CLASS_CONICAL         0x00000400   /* conical gradients are an option */
#define DLG_GRAD_95CONTEXTHELP         0x00000800   /* Dlg should contain context sensitive help icon */
#define DLG_GRAD_USESYSCOLORDLG        0x00001000   /* Use windows color picker dialog */

/* flags for L_DlgGetTransition() */
#define DLG_TRANS_SHOWPREVIEW     0x00000001   /* shows preview of image */
#define DLG_TRANS_AUTOPREVIEW     0x00000002   /* auto preview when options change */
#define DLG_TRANS_FORECOLOR       0x00000004   /* forecolor is an option */
#define DLG_TRANS_BACKCOLOR       0x00000008   /* backcolor is an option */
#define DLG_TRANS_DELAY           0x00000010   /* transition delay is an option */
#define DLG_TRANS_GRAIN           0x00000020   /* transition grain is an option */
#define DLG_TRANS_EFFECT          0x00000040   /* paint effect is an option */
#define DLG_TRANS_PASSES          0x00000080   /* transition passes is an option */
#define DLG_TRANS_WAND            0x00000100   /* wand is an option */
#define DLG_TRANS_TRANSPARENT     0x00000200   /* transparency is an option */
#define DLG_TRANS_GRADIENT        0x00000400   /* gradient is an option */
#define DLG_TRANS_95CONTEXTHELP   0x00000800   /* Dlg should contain context sensitive help icon */
#define DLG_TRANS_USESYSCOLORDLG  0x00001000   /* Use windows color picker dialog */

/* flags for L_DlgContourFilter() */
#define DLG_CONTOUR_SHOWPREVIEW           0x00000001   /* shows preview of image */
#define DLG_CONTOUR_AUTOPROCESS           0x00000002   /* AutoProcess on close   */
#define DLG_CONTOUR_OPTION                0x00000004   /* Contour Option is an option */
#define DLG_CONTOUR_THRESHOLD             0x00000008   /* Threshold is an option */
#define DLG_CONTOUR_DELTADIRECTION        0x00000010   /* DeltaDirection is an option  */
#define DLG_CONTOUR_MAXIMUMERROR          0x00000020   /* MaximumError is an option    */
#define DLG_CONTOUR_95CONTEXTHELP         0x00000040   /* Dlg should contain context sensitive help icon */
#define DLG_CONTOUR_TOOL                  0x00000080   /* Dlg should contain tool bar */

#define DLG_CONTOUR_OPTION_THIN           0x00000001
#define DLG_CONTOUR_OPTION_LINK_BW        0x00000002
#define DLG_CONTOUR_OPTION_LINK_GRAY      0x00000004
#define DLG_CONTOUR_OPTION_LINK_COLOR     0x00000008
#define DLG_CONTOUR_OPTION_APPROX_COLOR   0x00000010

#define DLG_CONTOUR_TOOL_RESIZE     0x00000100
#define DLG_CONTOUR_TOOL_ONSCREEN   0x00000200
#define DLG_CONTOUR_TOOL_SHOWEFFECT 0x00000400
#define DLG_CONTOUR_TOOL_RESET      0x00000800

// Flags for L_DlgHalftone ( ... )
#define DLG_HALFTONE_SHOWPREVIEW       0X0001
#define DLG_HALFTONE_AUTOPROCESS       0X0002
#define DLG_HALFTONE_95CONTEXTHELP     0X0004
#define DLG_HALFTONE_TOOL              0X0008

#define DLG_HALFTONE_TOOL_RESIZE       0x0010
#define DLG_HALFTONE_TOOL_ONSCREEN     0x0020
#define DLG_HALFTONE_TOOL_SHOWEFFECT   0x0040
#define DLG_HALFTONE_TOOL_RESET        0x0080
        

/* Dialog String Indices */
enum {
   /*
     Generic Control Strings
   */
   DLG_STR_OKSTR=0,           /* OK button                           */
   DLG_STR_CANCELSTR,         /* Cancel button                       */
   DLG_STR_HELPSTR,           /* Help button                         */
   /*
     ColorRes Dialog Strings
   */
   /* ColorRes BitsPerPixel */
   DLG_STR_CR1BIT,            /* ColorRes dialog 1-bit               */
   DLG_STR_CR2BIT,            /* ColorRes dialog 2-bit               */
   DLG_STR_CR3BIT,            /* ColorRes dialog 3-bit               */
   DLG_STR_CR4BIT,            /* ColorRes dialog 4-bit               */
   DLG_STR_CR5BIT,            /* ColorRes dialog 5-bit               */
   DLG_STR_CR6BIT,            /* ColorRes dialog 6-bit               */
   DLG_STR_CR7BIT,            /* ColorRes dialog 7-bit               */
   DLG_STR_CR8BIT,            /* ColorRes dialog 8-bit               */
   DLG_STR_CR12BIT,           /* ColorRes dialog 12-bit              */
   DLG_STR_CR16BIT,           /* ColorRes dialog 16-bit              */
   DLG_STR_CR24BIT,           /* ColorRes dialog 24-bit              */
   DLG_STR_CR32BIT,           /* ColorRes dialog 32-bit              */
   /* Dithering */
   DLG_STR_CRNONE,            /* ColorRes dialog No Dithering        */
   DLG_STR_CRFLOYD,           /* ColorRes dialog Floyd Dithering     */
   DLG_STR_CRSTUCKI,          /* ColorRes dialog Stucki Dithering    */
   DLG_STR_CRBURKES,          /* ColorRes dialog Burkes Dithering    */
   DLG_STR_CRSIERRA,          /* ColorRes dialog Sierra Dithering    */
   DLG_STR_CRSTEVEN,          /* ColorRes dialog Stevenson Dithering */
   DLG_STR_CRJARVIS,          /* ColorRes dialog Jarvis Dithering    */
   DLG_STR_CRCLUSTER,         /* ColorRes dialog Cluster Dithering   */
   DLG_STR_CRORDERED,         /* ColorRes dialog Ordered Dithering   */
   /* Palette */
   DLG_STR_CRFIXEDPAL,        /* ColorRes dialog Fixed Palette       */
   DLG_STR_CROPTIMIZEDPAL,    /* ColorRes dialog Optimized Palette   */
   DLG_STR_CRIDENTITYPAL,     /* ColorRes dialog Identity Palette    */
   DLG_STR_CRNETSCAPEPAL,     /* ColorRes dialog Netscape Palette    */
   /* Color Order */
   DLG_STR_CRRGBORDER,        /* ColorRes dialog RGB Color Order     */
   DLG_STR_CRBGRORDER,        /* ColorRes dialog BGR Color Order     */
   DLG_STR_CRGRAYORDER,       /* ColorRes dialog Gray Color Order    */
   /* ColorRes Dlg Control Strings */
   DLG_STR_CRCAPTION,         /* ColorRes dialog title caption       */
   DLG_STR_CRBPP,             /* ColorRes dialog BitsPerPixel Label  */
   DLG_STR_CRDITHER,          /* ColorRes dialog Diterhing Label     */
   DLG_STR_CRPALETTE,         /* ColorRes dialog Palette Label       */
   DLG_STR_CRORDER,           /* ColorRes dialog Color Order Label   */
   /*
     WindowLevel Dialog Strings
   */
   /* WindowLevel Dlg Control Strings */
   DLG_STR_WLCAPTION,         /* WindowLevel dialog title caption    */
   DLG_STR_WLLABEL,           /* WindowLevel dialog label            */
   DLG_STR_WLRANGELABEL,      /* WindowLevel dialog range label      */
   DLG_STR_WLINSIDE,          /* WindowLevel dialog inside label     */
   DLG_STR_WLOUTSIDE,         /* WindowLevel dialog outside label    */
   DLG_STR_WLCOLORSLABEL,     /* WindowLevel dialog colors label     */
   DLG_STR_WLENDCOLORS,       /* WindowLevel dialog end color button */
   DLG_STR_WLSTARTCOLORS,     /* WindowLevel dialog start color button*/
   /*
     Image Processing Dialogs
   */
   /* Filter Directions */
   DLG_STR_FLTN,              /* Filter/Emboss dialog - North        */
   DLG_STR_FLTNE,             /* Filter/Emboss dialog - North East   */
   DLG_STR_FLTE,              /* Filter/Emboss dialog - East         */
   DLG_STR_FLTSE,             /* Filter/Emboss dialog - Sourth East  */
   DLG_STR_FLTS,              /* Filter/Emboss dialog - South        */
   DLG_STR_FLTSW,             /* Filter/Emboss dialog - South West   */
   DLG_STR_FLTW,              /* Filter/Emboss dialog - West         */
   DLG_STR_FLTNW,             /* Filter/Emboss dialog - North West   */
   DLG_STR_FLTDIAG,           /* Filter dialog - Diagonal            */
   DLG_STR_FLTHORZ,           /* Filter dialog - Horizontal          */
   DLG_STR_FLTVERT,           /* Filter dialog - Vertical            */
   DLG_STR_FLTLTOR,           /* Filter dialog - Left To Right Diag. */
   DLG_STR_FLTRTOL,           /* Filter dialog - Right To Left Diag. */
   DLG_STR_FLT1,              /* Filter dialog - Filter 1            */
   DLG_STR_FLT2,              /* Filter dialog - Filter 2            */
   DLG_STR_FLT3,              /* Filter dialog - Filter 3            */
   DLG_STR_FLTOMNI,           /* Filter dialog - Omni Directional    */
   /* Image Processing Dialog control strings */
   DLG_STR_RESIZESTR,         /* Resize dialog title caption         */
   DLG_STR_RESAMPLESTR,       /* Resample dialog title caption       */
   DLG_STR_BICUBICSTR,        /* Bicubic Resize dialog title caption */
   DLG_STR_CHANMASTER,        /* AddNoise dialog channel strings     */
   DLG_STR_CHANRED,           /* AddNoise dialog channel strings     */
   DLG_STR_CHANGREEN,         /* AddNoise dialog channel strings     */
   DLG_STR_CHANBLUE,          /* AddNoise dialog channel strings     */
   DLG_STR_PROCESSIMAGESTR,   /* Change dialog title if > 1 process                    */
   DLG_STR_PROCESSSTR,        /* Change dialog process label if > 1 process            */
   DLG_STR_SHARPENSTR,        /* Change dialog title/string for sharpen process        */
   DLG_STR_BRIGHTNESSSTR,     /* Change dialog title/string for brightness process     */
   DLG_STR_CONTRASTSTR,       /* Change dialog title/string for contrast process       */
   DLG_STR_SATURATIONSTR,     /* Change dialog title/string for saturation process     */
   DLG_STR_HISTOCONTRASTSTR,  /* Change dialog title/string for histo-contrast process */
   DLG_STR_HUESTR,            /* Change dialog title/string for hue process            */
   DLG_STR_HALFTONESTR,       /* Change dialog title/string for halftone process       */
   DLG_STR_POSTERIZESTR,      /* Change dialog title/string for posterize process      */
   DLG_STR_MOSAICSTR,         /* Change dialog title/string for mosaic process         */
   DLG_STR_AVERAGESTR,        /* Change dialog title/string for average process        */
   DLG_STR_MEDIANSTR,         /* Change dialog title/string for median process         */
   DLG_STR_OILIFYSTR,         /* Change dialog title/string for oilify process         */
   DLG_STR_MINFLTSTR,         /* Change dialog title/string for min filter process     */
   DLG_STR_MAXFLTSTR,         /* Change dialog title/string for max filter process     */
   DLG_STR_SOLARIZESTR,       /* Change dialog title/string for solarize process       */
   DLG_STR_PERCENTAGESTR,     /* Change dialog value label for process that use percentages  */
   DLG_STR_ANGLEDEGREESSTR,   /* Change dialog value label for process that use angles       */
   DLG_STR_LEVELSSTR,         /* Change dialog value label for process that use levels       */
   DLG_STR_TILESIZESTR,       /* Change dialog value label for process that use tile sizes   */
   DLG_STR_SAMPLESIZESTR,     /* Change dialog value label for process that use sample sizes */
   DLG_STR_THRESHOLDSTR,      /* Change dialog value label for process that use threshold    */
   DLG_STR_ROTATESTR,         /* Rotate dialog title caption         */
   DLG_STR_ROTATERESIZESTR,   /* Rotate dialog checkbox              */
   DLG_STR_SHEARSTR,          /* Shear dialog title caption          */
   DLG_STR_SHEARHORZSTR,      /* Shear dialog checkbox               */
   DLG_STR_FLTVALSTR,         /* Filter dialog filter value label                      */
   DLG_STR_FLTIMAGESTR,       /* Filter dialog title for > 1 filter                    */
   DLG_STR_FLTTYPESTR,        /* Filter dialog filter type label, for > 1 filter       */
   DLG_STR_GRADIENTFLTSTR,    /* Filter dialog title/string for Gradient filter        */
   DLG_STR_LAPLACIANFLTSTR,   /* Filter dialog title/string for Laplacian filter       */
   DLG_STR_SOBELFLTSTR,       /* Filter dialog title/string for Sobel filter           */
   DLG_STR_PREWITTFLTSTR,     /* Filter dialog title/string for Prewitt filter         */
   DLG_STR_SHIFTDIFFFLTSTR,   /* Filter dialog title/string for ShiftDifference filter */
   DLG_STR_LINESEGFLTSTR,     /* Filter dialog title/string for LineSegment filter     */
   DLG_STR_EROSIONFLTSTR,     /* Filter dialog title/string for Erosion filter         */
   DLG_STR_DILATIONFLTSTR,    /* Filter dialog title/string for Dilation filter        */
   DLG_STR_RESIZEASPECTSTR,   /* Resize dialog checkbox              */
   DLG_STR_RESIZEWIDTHSTR,    /* Resize dialog width label           */
   DLG_STR_RESIZEHEIGHTSTR,   /* Resize dialog height label          */
   DLG_STR_ROTATEANGLESTR,    /* Rotate/Shear dialog angle label     */
   DLG_STR_ROTATECOLORSTR,    /* Rotate/Shear dialog backcolor button*/
   DLG_STR_EMBOSSSTR,         /* Emboss dialog title caption         */
   DLG_STR_EMBOSSDIRSTR,      /* Emboss dialog direction label       */
   DLG_STR_EMBOSSDEPTHSTR,    /* Emboss dialog depth label           */
   DLG_STR_INTENSITYDETECTSTR,    /* IntensityDetect dialog title caption */
   DLG_STR_INTENSITYDETECTLOWSTR, /* IntensityDetect low label            */
   DLG_STR_INTENSITYDETECTHIGHSTR,/* IntensityDetect high label           */
   DLG_STR_ADDNOISESTR,       /* AddNoise dialog title caption       */
   DLG_STR_NOISELEVELSTR,     /* AddNoise dialog level label         */
   DLG_STR_NOISECHANNELSTR,   /* AddNoise dialog channel label       */
   DLG_STR_GAMMACORRECTSTR,   /* GammaCorrect dialog title caption   */
   DLG_STR_GAMMAVALUESTR,     /* GammaCorrect dialog value label     */
   /*
     Contour Filter Dialog strings
   */
   /* Contour Filter Dialog control strings */
   DLG_STR_CONTOURSTR,        /* ContourFilter dialog title caption  */
   DLG_STR_CONTOUROPTIONSTR,  /* ContourFilter dialog option label   */
   DLG_STR_CONTOURTHRESHOLDSTR,/* ContourFilter dialog threshold label*/
   DLG_STR_CONTOURDELTADIRECTIONSTR,/* ContourFilter dialog deltadir label */
   DLG_STR_CONTOURMAXIMUMERRORSTR,  /* ContourFilter dialog maxerr label   */
   /* contour options */
   DLG_STR_CONTOURTHINSTR,
   DLG_STR_CONTOURLINKBLACKWHITESTR,
   DLG_STR_CONTOURLINKGRAYSCALESTR,
   DLG_STR_CONTOURLINKCOLORSTR,
   DLG_STR_CONTOURAPPROXCOLORSTR,
   /*
     3d Text Dialog strings
   */
   /* 3d Text Dialog option strings */
   DLG_STR_TEXT_NOEFFECT,     /* 3d Text dialog effect strings       */
   DLG_STR_TEXT_INSETLIGHT,
   DLG_STR_TEXT_INSETXLIGHT,
   DLG_STR_TEXT_INSETHEAVY,
   DLG_STR_TEXT_INSETXHEAVY,
   DLG_STR_TEXT_RAISEDLIGHT,
   DLG_STR_TEXT_RAISEDXLIGHT,
   DLG_STR_TEXT_RAISEDHEAVY,
   DLG_STR_TEXT_RAISEDXHEAVY,
   DLG_STR_TEXT_DROPSHADOW,
   DLG_STR_TEXT_BLOCKSHADOW,
   DLG_STR_TEXT_OUTLINEBLOCK,
   DLG_STR_TEXT_ALIGNLEFT,    /* 3d Text dialog alignment strings    */
   DLG_STR_TEXT_ALIGNHORZCENTER,
   DLG_STR_TEXT_ALIGNRIGHT,
   DLG_STR_TEXT_ALIGNTOP,
   DLG_STR_TEXT_ALIGNVERTCENTER,
   DLG_STR_TEXT_ALIGNBOTTOM,
   /* 3d Text Dialog control strings */
   DLG_STR_TEXTOPTIONSSTR,    /* 3d Text dialog title caption        */
   DLG_STR_TEXTPREVIEWSTR,    /* 3d Text dialog preview button label */
   DLG_STR_TEXTSAMPLETEXTSTR, /* 3d Text dialog sample text label    */
   DLG_STR_TEXTSTYLESTR,      /* 3d Text dialog style label          */
   DLG_STR_TEXTCOLORSTR,      /* 3d Text dialog text color label     */
   DLG_STR_TEXTBORDERCOLORSTR,/* 3d Text dialog border color label   */
   DLG_STR_TEXTALIGNSTR,      /* 3d Text dialog alignment label      */
   DLG_STR_TEXTANGLESTR,      /* 3d Text dialog angle label          */
   DLG_STR_TEXTWORDWRAPSTR,   /* 3d Text dialog word wrap label      */
   DLG_STR_TEXTFONTSTR,       /* 3d Text dialog font button label    */
   DLG_STR_TEXTUSEFOREIMAGESTR,/* 3d Text dialog use foreground image label */
   DLG_STR_TEXTFOREIMAGESTR,  /* 3d Text dialog image button label   */
   DLG_STR_TEXTSHADOWSTR,     /* 3d Text dialog shadow label         */
   DLG_STR_TEXTSHADOWCOLORSTR,/* 3d Text dialog shadow color label   */
   DLG_STR_TEXTSHADOWXSTR,    /* 3d Text dialog shadow X label       */
   DLG_STR_TEXTSHADOWYSTR,    /* 3d Text dialog shadow Y label       */
   /*
     Resolution Dialog strings
   */
   /* Resolution Dialog option strings */
   DLG_STR_WMFRESPROMPT,      /* Resolution dialog WMF prompt/title  */
   DLG_STR_WMFRESLABEL,       /* Resolution dialog WMF label         */
   DLG_STR_PCDRESPROMPT,      /* Resolution dialog PCD prompt/title  */
   DLG_STR_PCDRESLABEL,       /* Resolution dialog PCD label         */
   DLG_STR_FPXRESPROMPT,      /* Resolution dialog FPX prompt/title  */
   DLG_STR_FPXRESLABEL,       /* Resolution dialog FPX label         */
   DLG_STR_JBIGRESPROMPT,     /* Resolution dialog JBIG prompt/title */
   DLG_STR_JBIGRESLABEL,      /* Resolution dialog JBIG label        */
   DLG_STR_RESOLUTIONWIDTHSTR,/* Resolution dialog width label       */
   DLG_STR_RESOLUTIONHEIGHTSTR,/* Resolution dialog height label     */
   /*
     GetDirectory Dialog strings
   */
   DLG_STR_GETDIRSELECTEDSTR,  /* GetDir dialog selected label           */
   DLG_STR_GETDIR31DIRSTR,     /* GetDir 31-style dialog Directory label */
   DLG_STR_GETDIR95DIRSTR,     /* GetDir 95-style dialog Directory label */
   DLG_STR_GETDIR31FILETYPESTR,/* GetDir 31-style dialog FileType label  */
   DLG_STR_GETDIR95FILETYPESTR,/* GetDir 95-style dialog FileType label  */
   DLG_STR_GETDIRDRIVESSTR,    /* GetDir 31-style dialog Drives label    */
   DLG_STR_GETDIROKSTR,        /* GetDir dialog OK button label          */
   /*
     FileOpen and FileSave Dialog strings
   */
   /* Progressive Passes strings */
   DLG_STR_PROGMEANINGFUL,     /* FileOpen/FileSave dialog passes strings*/
   DLG_STR_PROGALL,
   DLG_STR_PROG1,
   DLG_STR_PROG2,
   DLG_STR_PROG3,
   DLG_STR_PROG4,
   DLG_STR_PROG5,
   DLG_STR_PROG6,
   DLG_STR_PROG7,
   DLG_STR_PROG8,
   DLG_STR_PROG9,
   DLG_STR_PROG10,
   /* FileOpen FileInfo Dialog strings */
   DLG_STR_FILEINFOERRORSTRING,/* FileInfo dialog error msgbox prompt */
   DLG_STR_FILEINFOERROR,      /* FileInfo dialog error msgbox title  */
   /* FileOpen FileInfo control strings */
   DLG_STR_FILEINFORMATIONSTR,    /* FileInfo dialog title caption       */
   DLG_STR_FILEINFO_FORMATSTR,
   DLG_STR_FILEINFO_FILENAMESTR,
   DLG_STR_FILEINFO_WIDTHSTR,
   DLG_STR_FILEINFO_HEIGHTSTR,
   DLG_STR_FILEINFO_BPPSTR,
   DLG_STR_FILEINFO_SIZEDISKSTR,
   DLG_STR_FILEINFO_SIZEMEMSTR,
   DLG_STR_FILEINFO_COMPRESSIONSTR,
   DLG_STR_FILEINFO_PAGESTR,
   /* file tags */
   DLG_STR_FILEINFO_ARTISTSTR,
   DLG_STR_FILEINFO_COPYRIGHTSTR,
   DLG_STR_FILEINFO_DATETIMESTR,
   DLG_STR_FILEINFO_DESCRIPTIONSTR,
   DLG_STR_FILEINFO_HOSTCOMPUTERSTR,
   DLG_STR_FILEINFO_MAKESTR,
   DLG_STR_FILEINFO_MODELSTR,
   DLG_STR_FILEINFO_DOCNAMESTR,
   DLG_STR_FILEINFO_PAGENAMESTR,
   DLG_STR_FILEINFO_SOFTWARESTR,
   DLG_STR_FILEINFO_XRESOLUTIONSTR,
   DLG_STR_FILEINFO_YRESOLUTIONSTR,
   /* dicom */
   DLG_STR_FILEINFO_PATIENTNAMESTR,
   DLG_STR_FILEINFO_PATIENTIDSTR,
   DLG_STR_FILEINFO_PATIENTBIRTHDATESTR,
   DLG_STR_FILEINFO_PATIENTSEXSTR,
   DLG_STR_FILEINFO_STUDYINSTANCESTR,
   DLG_STR_FILEINFO_STUDYDATESTR,
   DLG_STR_FILEINFO_STUDYTIMESTR,
   DLG_STR_FILEINFO_STUDYREFPHYSICIANSTR,
   DLG_STR_FILEINFO_SERIESMODALITYSTR,
   DLG_STR_FILEINFO_SERIESIDSTR,
   DLG_STR_FILEINFO_SERIESNUMBERSTR,
   DLG_STR_FILEINFO_LOSSLESSJPEG,
   DLG_STR_FILEINFO_LOSSLESSJTIF,
   /* png */
   DLG_STR_FILEINFO_WARNINGSTR,
   DLG_STR_FILEINFO_DISCLAIMERSTR,

   /* FileSave Dialog Multipage Save Option Strings */
   DLG_STR_OVERWRITESTR,       /* FileSave dialog overwrite string    */
   DLG_STR_APPENDSTR,          /* FileSave dialog append string       */
   DLG_STR_REPLACESTR,         /* FileSave dialog replace string      */
   DLG_STR_INSERTSTR,          /* FileSave dialog insert string       */
   /* Delete page options strings */
   DLG_STR_DELPAGEPROMPT,
   DLG_STR_DELPAGETITLE,
   DLG_STR_DELPAGEERROR,
   /* file format strings, used in FileOpen FileInfo Dialog */
   /* these correspond to the FILE_XXX file format constant */
   DLG_STR_FILE_PCX,           /* PCX                    */
   DLG_STR_FILE_GIF,           /* GIF                    */
   DLG_STR_FILE_TIF,           /* TIFF                   */
   DLG_STR_FILE_TGA,           /* TGA                    */
   DLG_STR_FILE_CMP,           /* LEAD                   */
   DLG_STR_FILE_BMP,           /* Win BMP                */
   DLG_STR_FILE_JFIF,          /* JPEG 4:4:4             */
   DLG_STR_FILE_JTIF,          /* JTIF 4:4:4             */
   DLG_STR_FILE_LEAD1JFIF,     /* JPEG 4:1:1             */
   DLG_STR_FILE_LEAD2JFIF,     /* JPEG 4:2:2             */
   DLG_STR_FILE_LEAD1JTIF,     /* JTIF 4:1:1             */
   DLG_STR_FILE_LEAD2JTIF,     /* JTIF 4:2:2             */
   DLG_STR_FILE_OS2,           /* OS/2 BMP Version 1.0   */
   DLG_STR_FILE_WMF,           /* Win Metafile           */
   DLG_STR_FILE_EPS,           /* PostScript Raster      */
   DLG_STR_FILE_TIFLZW,        /* TIFF                   */
   DLG_STR_FILE_CCITT,         /* TIFF                   */
   DLG_STR_FILE_CCITT_GROUP3_1DIM,/* TIFF                */
   DLG_STR_FILE_CCITT_GROUP3_2DIM,/* TIFF                */
   DLG_STR_FILE_CCITT_GROUP4,  /* TIFF                   */
   DLG_STR_FILE_LEAD1BIT,      /* LEAD 1 bit             */
   DLG_STR_FILE_CALS,          /* CALS Type 1            */
   DLG_STR_FILE_CALS2,         /* CALS Type 2            */
   DLG_STR_FILE_CALS3,         /* CALS Type 3            */
   DLG_STR_FILE_CALS4,         /* CALS Type 4            */
   DLG_STR_FILE_MAC,           /* MacPaint               */
   DLG_STR_FILE_IMG,           /* GEM Image              */
   DLG_STR_FILE_MSP,           /* MS Paint               */
   DLG_STR_FILE_WPG,           /* WordPerfect            */
   DLG_STR_FILE_RAS,           /* SUN Raster             */
   DLG_STR_FILE_PCT,           /* Mac PICTURE            */
   DLG_STR_FILE_PCD,           /* Photo CD               */
   DLG_STR_FILE_AVI,           /* Windows AVI            */
   DLG_STR_FILE_EPSTIFF,       /* PostScript TIFF        */
   DLG_STR_FILE_EPSWMF,        /* Metafile PostScript    */
   DLG_STR_FILE_FAX_G3_1D,     /* FAX G3 1D              */
   DLG_STR_FILE_FAX_G3_2D,     /* FAX G3 2D              */
   DLG_STR_FILE_FAX_G4,        /* FAX G4                 */
   DLG_STR_FILE_WFX_G3_1D,     /* Winfax G3 1D           */
   DLG_STR_FILE_WFX_G4,        /* Winfax G4              */
   DLG_STR_FILE_ICA_G3_1D,     /* IBM IOCA (Wrapped) G31D*/
   DLG_STR_FILE_ICA_G3_2D,     /* IBM IOCA (Wrapped) G32D*/
   DLG_STR_FILE_ICA_G4,        /* IBM IOCA (Wrapped) G4  */
   DLG_STR_FILE_OS2_2,         /* OS/2 BMP Version 2.0   */
   DLG_STR_FILE_PNG,           /* CServe PNG             */
   DLG_STR_FILE_PSD,           /* PhotoShop PSD          */
   DLG_STR_FILE_RAWICA_G3_1D,  /* IBM IOCA (Raw) G31D    */
   DLG_STR_FILE_RAWICA_G3_2D,  /* IBM IOCA (Raw) G32D    */
   DLG_STR_FILE_RAWICA_G4,     /* IBM IOCA (Raw) G4      */
#ifdef WIN32
   DLG_STR_FILE_FPX,           /* Kodak FlashPix         */
   DLG_STR_FILE_FPX_SINGLE_COLOR,/* Kodak FlashPix Single Color*/
   DLG_STR_FILE_FPX_JPEG,      /* Kodak FlashPix - JPEG  */
   DLG_STR_FILE_FPX_JPEG_QFACTOR,/* Kodak FlashPix - JPEG*/
#endif
   DLG_STR_FILE_BMP_RLE,       /* Windows RLE BMP        */
   DLG_STR_FILE_TIF_CMYK,      /* CMYK TIFF              */
   DLG_STR_FILE_TIFLZW_CMYK,   /* CMYK TIFF              */
   DLG_STR_FILE_TIF_PACKBITS,  /* TIFF                   */
   DLG_STR_FILE_TIF_PACKBITS_CMYK,/* CMYK TIFF           */
   DLG_STR_FILE_DICOM_GRAY,    /* DICOM Grayscale        */
   DLG_STR_FILE_DICOM_COLOR,   /* DICOM Color            */
   DLG_STR_FILE_DICOM_RLE_GRAY,/* RLE Grayscale          */
   DLG_STR_FILE_DICOM_RLE_COLOR,/* RLE Color             */
   DLG_STR_FILE_DICOM_JPEG_GRAY,/* JPEG Grayscale        */
   DLG_STR_FILE_DICOM_JPEG_COLOR,/* JPEG Color           */
   DLG_STR_FILE_WIN_ICO,       /* Windows ICON           */
   DLG_STR_FILE_WIN_CUR,       /* Windows Cursor         */
   DLG_STR_FILE_TIF_YCC,       /* YCbCr TIFF             */
   DLG_STR_FILE_TIFLZW_YCC,    /* YCbCr TIFF             */
   DLG_STR_FILE_TIF_PACKBITS_YCC,/* YCbCr TIFF           */
   DLG_STR_FILE_EXIF,          /* Exif RGB TIFF          */
   DLG_STR_FILE_EXIF_YCC,      /* Exif YCbCr TIFF        */
   DLG_STR_FILE_EXIF_JPEG,     /* Exif JPEG              */
#ifdef WIN32
   DLG_STR_FILE_AWD,           /* Microsoft FAX          */
#endif
   DLG_STR_FILE_EXIF_JPEG_411, /* JPEG 4:1:1 - Exif      */
#ifdef WIN32
   DLG_STR_FILE_EMF,           /* Enhanced Metafile      */
#endif
   DLG_STR_FILE_JBIG,          /* JBIG                   */
   DLG_STR_FILE_ICA_IBM_MMR,
   DLG_STR_FILE_RAWICA_IBM_MMR,
   DLG_STR_FILE_ANI,
   DLG_STR_FILE_ANI_RLE,
   DLG_STR_FILE_LASERDATA,
   DLG_STR_FILE_INTERGRAPH_RLE,
   DLG_STR_FILE_INTERGRAPH_VECTOR,
   DLG_STR_FILE_DWG,
   DLG_STR_FILE_CUT,
   DLG_STR_FILE_PPM_ASCII,
   DLG_STR_FILE_PPM_BINARY,
   DLG_STR_FILE_PGM_ASCII,
   DLG_STR_FILE_PGM_BINARY,
   DLG_STR_FILE_PBM_ASCII,
   DLG_STR_FILE_PBM_BINARY,
   DLG_STR_FILE_IFF_ILBM,
   DLG_STR_FILE_IFF_CAT,
   DLG_STR_FILE_XBM,
   DLG_STR_FILE_XPM,
   DLG_STR_FILE_DXF,
   DLG_STR_FILE_DUMMY,
   DLG_STR_FILE_MPEG1,
   DLG_STR_FILE_MPEG2,
   /* FileOpen Dialog control strings */
   DLG_STR_FILEOPENOKSTR,               /* FileOpen OK button label          */
   /* 95 style */
   DLG_STR_FILEOPEN95FILEINFOSTR,       /* FileOpen FileInfo button label    */
   DLG_STR_FILEOPEN95LOADROTATEDSTR,    /* FileOpen Load Rotated label       */
   DLG_STR_FILEOPEN95LOADCOMPRESSEDSTR, /* FileOpen Load Compressed label    */
   DLG_STR_FILEOPEN95PROGPASSESSTR,     /* FileOpen Progressive Passes label */
   DLG_STR_FILEOPEN95PAGENUMSTR,        /* FileOpen Page Number label        */
   DLG_STR_FILEOPEN95DELETEPAGESTR,     /* FileOpen Delete Page button label */
   DLG_STR_FILEOPEN95ENABLEPREVIEWSTR,  /* FileOpen Enable Preview label     */
   DLG_STR_FILEOPEN95FILETYPESTR,       /* FileOpen File Type label          */
   DLG_STR_FILEOPEN95DIRSTR,            /* FileOpen Folder label             */
   DLG_STR_FILEOPEN95FILENAMESTR,       /* FileOpen File Name label          */
   /* 31 style */
   DLG_STR_FILEOPEN31FILEINFOSTR,       /* FileOpen FileInfo button label    */
   DLG_STR_FILEOPEN31LOADROTATEDSTR,    /* FileOpen Load Rotated label       */
   DLG_STR_FILEOPEN31LOADCOMPRESSEDSTR, /* FileOpen Load Compressed label    */
   DLG_STR_FILEOPEN31PROGPASSESSTR,     /* FileOpen Progressive Passes label */
   DLG_STR_FILEOPEN31PAGENUMSTR,        /* FileOpen Page Number label        */
   DLG_STR_FILEOPEN31DELETEPAGESTR,     /* FileOpen Delete Page button label */
   DLG_STR_FILEOPEN31ENABLEPREVIEWSTR,  /* FileOpen Enable Preview label     */
   DLG_STR_FILEOPEN31DRIVESSTR,         /* FileOpen Drive ListBox label      */
   DLG_STR_FILEOPEN31FILETYPESTR,       /* FileOpen File Type label          */
   DLG_STR_FILEOPEN31DIRSTR,            /* FileOpen Folder label             */
   DLG_STR_FILEOPEN31FILENAMESTR,       /* FileOpen File Name label          */
   /* FileSave Dialog control strings */
   /* 95 style */
   DLG_STR_FILESAVEOKSTR,               /* FileSave OK button label          */
   DLG_STR_FILESAVE95FILETYPESTR,       /* FileSave File Type label          */
   DLG_STR_FILESAVE95DIRSTR,            /* FileSave Folder label             */
   DLG_STR_FILESAVE95FILENAMESTR,       /* FileSave File Name label          */
   DLG_STR_FILESAVE95STAMPOPTIONSSTR,   /* FileSave stamp options label      */
   DLG_STR_FILESAVE95SAVESTAMPSTR,      /* FileSave save stamp label         */
   DLG_STR_FILESAVE95STAMP8STR,         /* FileSave 8-bit stamp label        */
   DLG_STR_FILESAVE95STAMP24STR,        /* FileSave 24-bit stamp label       */
   DLG_STR_FILESAVE95STAMPWIDTHSTR,     /* FileSave stamp width label        */
   DLG_STR_FILESAVE95STAMPHEIGHTSTR,    /* FileSave stamp height label       */
   DLG_STR_FILESAVE95SUBTYPESTR,        /* FileSave sub file type label      */
   DLG_STR_FILESAVE95QFACTORSTR,        /* FileSave qfactor label            */
   DLG_STR_FILESAVE95PROGOPTIONSSTR,    /* FileSave progressive save label   */
   DLG_STR_FILESAVE95MULTIPAGESTR,      /* FileSave multipage save label     */
   DLG_STR_FILESAVE95PAGENUMBERSTR,     /* FileSave page number label        */
   /* 31 style */
   DLG_STR_FILESAVE31FILENAMESTR,       /* FileSave File Name label          */
   DLG_STR_FILESAVE31DIRSTR,            /* FileSave Folder label             */
   DLG_STR_FILESAVE31FILETYPESTR,       /* FileOpen File Type label          */
   DLG_STR_FILESAVE31DRIVESSTR,         /* FileSave Drive ListBox label      */
   DLG_STR_FILESAVE31MULTIPAGESTR,      /* FileSave multipage save label     */
   DLG_STR_FILESAVE31PAGENUMBERSTR,     /* FileSave page number label        */
   DLG_STR_FILESAVE31QFACTORSTR,        /* FileSave qfactor label            */
   DLG_STR_FILESAVE31SUBTYPESTR,        /* FileSave sub file type label      */
   DLG_STR_FILESAVE31STAMPOPTIONSSTR,   /* FileSave stamp options label      */
   DLG_STR_FILESAVE31SAVESTAMPSTR,      /* FileSave save stamp label         */
   DLG_STR_FILESAVE31STAMP8STR,         /* FileSave 8-bit stamp label        */
   DLG_STR_FILESAVE31STAMP24STR,        /* FileSave 24-bit stamp label       */
   DLG_STR_FILESAVE31STAMPWIDTHSTR,     /* FileSave stamp width label        */
   DLG_STR_FILESAVE31STAMPHEIGHTSTR,    /* FileSave stamp height label       */
   DLG_STR_FILESAVE31PROGOPTIONSSTR,    /* FileSave progressive save label   */
   /* FileSave File Format strings */
   /* NOTE: for top-level and sub-format strings, only the first 40 chars will be used! */
   /* for the top-level formats */
   DLG_STR_LEAD24,
   DLG_STR_LEAD8,
   DLG_STR_LEAD1,
   DLG_STR_JFIF24,
   DLG_STR_JFIF16,
   DLG_STR_JFIF12,
   DLG_STR_JFIF8,
   DLG_STR_CALS,
   DLG_STR_PNG1,
   DLG_STR_PNG4,
   DLG_STR_PNG8,
   DLG_STR_PNG24,
   DLG_STR_PNG32,
   DLG_STR_DICOM8,
   DLG_STR_DICOM16,
   DLG_STR_DICOM24,
   DLG_STR_FAX,
   DLG_STR_EPS,
   DLG_STR_EXIF,
#ifdef WIN32
   DLG_STR_FPX24,
   DLG_STR_FPX8,
#endif
   DLG_STR_IMG,
   DLG_STR_GIF1,
   DLG_STR_GIF2,
   DLG_STR_GIF3,
   DLG_STR_GIF4,
   DLG_STR_GIF5,
   DLG_STR_GIF6,
   DLG_STR_GIF7,
   DLG_STR_GIF8,
   DLG_STR_IOCA,
   DLG_STR_MODCA,
   DLG_STR_PCT1,
   DLG_STR_PCT4,
   DLG_STR_PCT8,
   DLG_STR_PCT24,
   DLG_STR_MAC,
#ifdef WIN32
   DLG_STR_AWD,
#endif
   DLG_STR_MSP,
   DLG_STR_OS2BMP1,
   DLG_STR_OS2BMP4,
   DLG_STR_OS2BMP8,
   DLG_STR_OS2BMP24,
   DLG_STR_PCX1,
   DLG_STR_PCX4,
   DLG_STR_PCX8,
   DLG_STR_PCX24,
   DLG_STR_PSD1,
   DLG_STR_PSD8,
   DLG_STR_PSD24,
   DLG_STR_RAS1,
   DLG_STR_RAS4,
   DLG_STR_RAS8,
   DLG_STR_RAS24,
   DLG_STR_RAS32,
   DLG_STR_TGA8,
   DLG_STR_TGA16,
   DLG_STR_TGA24,
   DLG_STR_TGA32,
   DLG_STR_TIFF1,
   DLG_STR_TIFF2,
   DLG_STR_TIFF3,
   DLG_STR_TIFF4,
   DLG_STR_TIFF5,
   DLG_STR_TIFF6,
   DLG_STR_TIFF7,
   DLG_STR_TIFF8,
   DLG_STR_TIFF12,
   DLG_STR_TIFF16,
   DLG_STR_TIFF24,
   DLG_STR_TIFF32,
   DLG_STR_BMP1,
   DLG_STR_BMP4,
   DLG_STR_BMP8,
   DLG_STR_BMP16,
   DLG_STR_BMP24,
   DLG_STR_BMP32,
   DLG_STR_WFX,
   DLG_STR_WMF8,
   DLG_STR_WMF24,
#ifdef WIN32
   DLG_STR_EMF8,
   DLG_STR_EMF24,
#endif
   DLG_STR_WPG1,
   DLG_STR_WPG4,
   DLG_STR_WPG8,
   DLG_STR_ICO1,
   DLG_STR_ICO4,
   DLG_STR_ICO8,
   DLG_STR_ICO24,
   DLG_STR_CUR1,
   DLG_STR_CUR4,
   DLG_STR_CUR8,
   DLG_STR_CUR24,
   DLG_STR_JBIG1,
   DLG_STR_JBIG2,
   DLG_STR_JBIG3,
   DLG_STR_JBIG4,
   DLG_STR_JBIG5,
   DLG_STR_JBIG6,
   DLG_STR_JBIG7,
   DLG_STR_JBIG8,
   DLG_STR_CUT,
   DLG_STR_PPM,
   DLG_STR_PGM,
   DLG_STR_PBM,
   DLG_STR_IFF1,
   DLG_STR_IFF2,
   DLG_STR_IFF3,
   DLG_STR_IFF4,
   DLG_STR_IFF5,
   DLG_STR_IFF6,
   DLG_STR_IFF7,
   DLG_STR_IFF8,
   DLG_STR_IFF24,
   DLG_STR_XBM,
   DLG_STR_XPM8,
   DLG_STR_XPM16,
   DLG_STR_XPM24,
   DLG_STR_XPM32,
   DLG_STR_ITG,
   /* for the sub-formats */
   /* LEAD CMP file subtypes (8,24-bit) */
   DLG_STR_SUB_CMP_NONPROGRESSIVE,
   DLG_STR_SUB_CMP_PROGRESSIVE,
   /* JPEG file subtypes (24-bit)       */
   DLG_STR_SUB_JPEG24_YUV_444,
   DLG_STR_SUB_JPEG24_YUV_422,
   DLG_STR_SUB_JPEG24_YUV_411,
   DLG_STR_SUB_JPEG24_PROG_444,
   DLG_STR_SUB_JPEG24_PROG_422,
   DLG_STR_SUB_JPEG24_PROG_411,
   DLG_STR_SUB_JPEG24_LOSSLESS,
   /* JPEG file subtypes (12-bit)       */
   DLG_STR_SUB_JPEG12_YUV_400,
   DLG_STR_SUB_JPEG12_LOSSLESS,
   /* JPEG file subtypes (8-bit)        */
   DLG_STR_SUB_JPEG8_YUV_400,
   DLG_STR_SUB_JPEG8_PROG_400,
   DLG_STR_SUB_JPEG8_LOSSLESS,
   /* CALS file subtypes (1-bit)        */
   DLG_STR_SUB_CALS,
   DLG_STR_SUB_CALS2,
   DLG_STR_SUB_CALS3,
   DLG_STR_SUB_CALS4,
   /* DICOM file subtypes (8-bit)       */
   DLG_STR_SUB_DICOM_GRAY,
   DLG_STR_SUB_DICOM_COLOR,
   /* DICOM file subtypes (Other-bit)   */
   DLG_STR_SUB_DICOM_RLE_GRAY,
   DLG_STR_SUB_DICOM_RLE_COLOR,
   DLG_STR_SUB_DICOM_JPEG_GRAY,
   DLG_STR_SUB_DICOM_LOSSLESSJPEG_GRAY,
   DLG_STR_SUB_DICOM_JPEG_COLOR,
   DLG_STR_SUB_DICOM_LOSSLESSJPEG_COLOR,
   /* RAW FAX, IOCA, & MODCA subtypes   */
   DLG_STR_SUB_FAX_G3_1D,
   DLG_STR_SUB_FAX_G3_2D,
   DLG_STR_SUB_FAX_G4,
   /* EXIF file subtypes                */
   DLG_STR_SUB_EXIF_UNCOMPRESSEDRGB,
   DLG_STR_SUB_EXIF_UNCOMPRESSEDYCC,
   DLG_STR_SUB_EXIF_JPEG_411,
   DLG_STR_SUB_EXIF_JPEG_422,
#ifdef WIN32
   /* FPX file subtypes                 */
   DLG_STR_SUB_FPX_UNCOMPRESSED,
   DLG_STR_SUB_FPX_SINGLECOLOR,
   DLG_STR_SUB_FPX_DEFQFACTOR,
   DLG_STR_SUB_FPX_SPECQFACTOR,
#endif
   /* GIF file subtypes                 */
   DLG_STR_SUB_GIF_INTERLACED89A,
   DLG_STR_SUB_GIF_NONINTERLACED89A,
   /* OS/2 BMP file subtypes            */
   DLG_STR_SUB_OS2_VER1,
   DLG_STR_SUB_OS2_VER2,
   /* TIFF file subtypes (1-bit)        */
   DLG_STR_SUB_TIFF1_CCITT,
   DLG_STR_SUB_TIFF1_CCITT_G3_1D,
   DLG_STR_SUB_TIFF1_CCITT_G3_2D,
   DLG_STR_SUB_TIFF1_CCITT_G4,
   DLG_STR_SUB_TIFF1_UNCOMPRESSEDRGB,
   DLG_STR_SUB_TIFF1_RLERGB,
   DLG_STR_SUB_TIFF1_LZWRGB,
   /* TIFF file subtypes (2,3,4,5,6,7-bit) */
   DLG_STR_SUB_TIFFOTHER_UNCOMPRESSED,
   DLG_STR_SUB_TIFFOTHER_RLE,
   DLG_STR_SUB_TIFFOTHER_LZW,
   /* TIFF file subtypes (8-bit)        */
   DLG_STR_SUB_TIFF8_UNCOMPRESSEDRGB,
   DLG_STR_SUB_TIFF8_RLERGB,
   DLG_STR_SUB_TIFF8_JPEG_GRAY_YCC,
   DLG_STR_SUB_TIFF8_LOSSLESSJPEG,
   DLG_STR_SUB_TIFF8_LZWRGB,
   /* TIFF file subtypes (12-bit)       */
   DLG_STR_SUB_TIFF12_UNCOMPRESSED,
   DLG_STR_SUB_TIFF12_LOSSLESSJPEG,
   /* TIFF file subtypes (16-bit)       */
   DLG_STR_SUB_TIFF16_UNCOMPRESSED,
   DLG_STR_SUB_TIFF16_RLE,
   DLG_STR_SUB_TIFF16_LOSSLESSJPEG,
   DLG_STR_SUB_TIFF16_LZW,
   /* TIFF file subtypes (24-bit)       */
   DLG_STR_SUB_TIFF24_UNCOMPRESSEDRGB,
   DLG_STR_SUB_TIFF24_UNCOMPRESSEDCMYK,
   DLG_STR_SUB_TIFF24_UNCOMPRESSEDYCC,
   DLG_STR_SUB_TIFF24_RLERGB,
   DLG_STR_SUB_TIFF24_RLECMYK,
   DLG_STR_SUB_TIFF24_RLEYCC,
   DLG_STR_SUB_TIFF24_JPEG_YCC_444,
   DLG_STR_SUB_TIFF24_JPEG_YCC_422,
   DLG_STR_SUB_TIFF24_JPEG_YCC_411,
   DLG_STR_SUB_TIFF24_LOSSLESSJPEG,
   DLG_STR_SUB_TIFF24_LZWRGB,
   DLG_STR_SUB_TIFF24_LZWCMYK,
   DLG_STR_SUB_TIFF24_LZWYCC,
   /* TIFF file subtypes (32-bit)       */
   DLG_STR_SUB_TIFF32_UNCOMPRESSEDRGB,
   DLG_STR_SUB_TIFF32_UNCOMPRESSEDCMYK,
   DLG_STR_SUB_TIFF32_RLERGB,
   DLG_STR_SUB_TIFF32_RLECMYK,
   DLG_STR_SUB_TIFF32_LZWRGB,
   DLG_STR_SUB_TIFF32_LZWCMYK,
   /* BMP file subtypes (4 and 8-bit only) */
   DLG_STR_SUB_BMP_UNCOMPRESSED,
   DLG_STR_SUB_BMP_RLECOMPRESSED,
   /* WFX file subtypes                 */
   DLG_STR_SUB_WFX_CCITT_G3_1D,
   DLG_STR_SUB_WFX_CCITT_G4,
   /* PPM file subtypes                 */
   DLG_STR_SUB_PPM_ASCII,
   DLG_STR_SUB_PPM_BINARY,
   /* PGM file subtypes                 */
   DLG_STR_SUB_PGM_ASCII,
   DLG_STR_SUB_PGM_BINARY,
   /* PBM file subtypes                 */
   DLG_STR_SUB_PBM_ASCII,
   DLG_STR_SUB_PBM_BINARY,
   /* IFF file subtypes                 */
//   DLG_STR_SUB_IFF_ILBM_UNCOMPRESSED,
//   DLG_STR_SUB_IFF_CAT_UNCOMPRESSED,
   DLG_STR_SUB_IFF_ILBM_RLE,
   DLG_STR_SUB_IFF_CAT_RLE,
   /* FileSave Dialog default extension strings */
   /* NOTE: for extension strings, only the first 3 chars will be used! */
   DLG_STR_EXT_LEAD,
   DLG_STR_EXT_JFIF,
   DLG_STR_EXT_CALS,
   DLG_STR_EXT_PNG,
   DLG_STR_EXT_DICOM,
   DLG_STR_EXT_FAX,
   DLG_STR_EXT_EPS,
   DLG_STR_EXT_EXIF,
#ifdef WIN32
   DLG_STR_EXT_FPX,
#endif
   DLG_STR_EXT_IMG,
   DLG_STR_EXT_GIF,
   DLG_STR_EXT_IOCA,
   DLG_STR_EXT_MODCA,
   DLG_STR_EXT_PCT,
   DLG_STR_EXT_MAC,
#ifdef WIN32
   DLG_STR_EXT_AWD,
#endif
   DLG_STR_EXT_MSP,
   DLG_STR_EXT_OS2BMP,
   DLG_STR_EXT_PCX,
   DLG_STR_EXT_PSD,
   DLG_STR_EXT_RAS,
   DLG_STR_EXT_TGA,
   DLG_STR_EXT_TIFF,
   DLG_STR_EXT_BMP,
   DLG_STR_EXT_WFX,
   DLG_STR_EXT_WMF,
#ifdef WIN32
   DLG_STR_EXT_EMF,
#endif
   DLG_STR_EXT_WPG,
   DLG_STR_EXT_ICO,
   DLG_STR_EXT_CUR,
   DLG_STR_EXT_JBIG,
   DLG_STR_EXT_CUT,
   DLG_STR_EXT_PPM,
   DLG_STR_EXT_PGM,
   DLG_STR_EXT_PBM,
   DLG_STR_EXT_IFF,
   DLG_STR_EXT_XBM,
   DLG_STR_EXT_XPM,
   DLG_STR_EXT_ITG,
   DLG_STR_MAX_MAIN, /* end of main strings */
};

enum {
   /*
     3d Shape Dialog strings
   */
   /* Shape Categories */
   DLG_STR_SHAPE_SQUARES=DLG_STR_MAX_MAIN,
   DLG_STR_SHAPE_RECTS,
   DLG_STR_SHAPE_PARALLELS,
   DLG_STR_SHAPE_TRAPS,
   DLG_STR_SHAPE_TRIANGLES,
   DLG_STR_SHAPE_OTHERS,
   DLG_STR_SHAPE_CIRCLES,
   DLG_STR_SHAPE_ELLIPSES,
   DLG_STR_SHAPE_STARS,
   DLG_STR_SHAPE_CROSSES,
   DLG_STR_SHAPE_ARROWS,
   /* Shape Styles */
   DLG_STR_SHAPE_NORMAL,
   DLG_STR_SHAPE_ROUNDED,
   DLG_STR_SHAPE_LEFT,
   DLG_STR_SHAPE_RIGHT,
   DLG_STR_SHAPE_TOP,
   DLG_STR_SHAPE_BOTTOM,
   DLG_STR_SHAPE_EQ_LEFT,
   DLG_STR_SHAPE_EQ_RIGHT,
   DLG_STR_SHAPE_EQ_TOP,
   DLG_STR_SHAPE_EQ_BOTTOM,
   DLG_STR_SHAPE_IS_LEFT,
   DLG_STR_SHAPE_IS_RIGHT,
   DLG_STR_SHAPE_IS_TOP,
   DLG_STR_SHAPE_IS_BOTTOM,
   DLG_STR_SHAPE_RIGHT_LT,
   DLG_STR_SHAPE_RIGHT_LB,
   DLG_STR_SHAPE_RIGHT_RT,
   DLG_STR_SHAPE_RIGHT_RB,
   DLG_STR_OCTAGONSTR,
   DLG_STR_DIAMONDSTR,
   DLG_STR_PENTAGONSTR,
   DLG_STR_HEXAGONSTR,
   DLG_STR_LINESTR,
   /* NOTE: REGION IS OMITTED */
   DLG_STR_SHAPE_90_LT,
   DLG_STR_SHAPE_90_LB,
   DLG_STR_SHAPE_90_RT,
   DLG_STR_SHAPE_90_RB,
   DLG_STR_SHAPE_180_L,
   DLG_STR_SHAPE_180_R,
   DLG_STR_SHAPE_180_T,
   DLG_STR_SHAPE_180_B,
   DLG_STR_SHAPE_270_LT,
   DLG_STR_SHAPE_270_LB,
   DLG_STR_SHAPE_270_RT,
   DLG_STR_SHAPE_270_RB,
   DLG_STR_SHAPE_4_POINT,
   DLG_STR_SHAPE_5_POINT,
   DLG_STR_SHAPE_8_POINT,
   DLG_STR_SHAPE_16_POINT,
   DLG_STR_SHAPE_24_POINT,
   DLG_STR_SHAPE_324_POINT,
   DLG_STR_SHAPE_SMALL,
   DLG_STR_SHAPE_MEDIUM,
   DLG_STR_SHAPE_LARGE,
   DLG_STR_SHAPE_2WAY_LR,
   DLG_STR_SHAPE_2WAY_TB,
   DLG_STR_SHAPE_2WAY_LT,
   DLG_STR_SHAPE_2WAY_LB,
   DLG_STR_SHAPE_2WAY_RT,
   DLG_STR_SHAPE_2WAY_RB,
   DLG_STR_SHAPE_3WAY_LTR,
   DLG_STR_SHAPE_3WAY_TRB,
   DLG_STR_SHAPE_3WAY_LBR,
   DLG_STR_SHAPE_3WAY_LTB,
   DLG_STR_SHAPE_4WAY,
   /* Shape Styles */
   DLG_STR_SHAPE_TRANSPARENT,
   DLG_STR_SHAPE_OPAQUE,
   DLG_STR_SHAPE_TRANSLUCENT,
   DLG_STR_SHAPE_TILEDIMAGE,
   DLG_STR_SHAPE_TRANSTILEDIMAGE,
   DLG_STR_SHAPE_SOLIDFILL,
   DLG_STR_SHAPE_TRANSFILL,
   DLG_STR_SHAPE_HORZFILL,
   DLG_STR_SHAPE_VERTFILL,
   DLG_STR_SHAPE_FOREDIAGFILL,
   DLG_STR_SHAPE_BACKDIAGFILL,
   DLG_STR_SHAPE_CROSSFILL,
   DLG_STR_SHAPE_DIAGCROSSFILL,
   DLG_STR_SHAPE_TRANSBORDER,
   DLG_STR_SHAPE_SOLIDBORDER,
   DLG_STR_SHAPE_DASHBORDER,
   DLG_STR_SHAPE_DOTBORDER,
   DLG_STR_SHAPE_DASHDOTBORDER,
   DLG_STR_SHAPE_DASHDOTDOTBORDER,
   DLG_STR_SHAPE_INNEROUTERNONE,
   DLG_STR_SHAPE_INNEROUTERINSET,
   DLG_STR_SHAPE_INNEROUTERRAISED,
   /* 3d Shape Dialog control strings */
   DLG_STR_SHAPEOPTIONSSTR,      /* 3d Shape Dialog title caption          */
   DLG_STR_SHAPECATEGORYSTR,     /* 3d Shape Dialog category label         */
   DLG_STR_SHAPESTYLESTR,        /* 3d Shape Dialog style label            */
   DLG_STR_SHAPEPREVIEWSTR,      /* 3d Shape Dialog preview button label   */
   DLG_STR_SHAPEBACKSTYLESTR,    /* 3d Shape Dialog background style label */
   DLG_STR_SHAPEBACKIMAGESTR,    /* 3d Shape Dialog background image label */
   DLG_STR_SHAPEFILLSTYLESTR,    /* 3d Shape Dialog fill style label       */
   DLG_STR_SHAPEFORECOLORSTR,    /* 3d Shape Dialog foreground color label */
   DLG_STR_SHAPEBACKCOLORSTR,    /* 3d Shape Dialog background color label */
   DLG_STR_SHAPEBORDERSTYLESTR,  /* 3d Shape Dialog border style label     */
   DLG_STR_SHAPEBORDERCOLORSTR,  /* 3d Shape Dialog border color label     */
   DLG_STR_SHAPEBORDERWIDTHSTR,  /* 3d Shape Dialog border width label     */
   DLG_STR_SHAPEINNERSTYLESTR,   /* 3d Shape Dialog inner style label      */
   DLG_STR_SHAPEINNERHILITESTR,  /* 3d Shape Dialog inner hilite label     */
   DLG_STR_SHAPEINNERSHADOWSTR,  /* 3d Shape Dialog inner shadow label     */
   DLG_STR_SHAPEINNERWIDTHSTR,   /* 3d Shape Dialog inner width label      */
   DLG_STR_SHAPEOUTERSTYLESTR,   /* 3d Shape Dialog outer style label      */
   DLG_STR_SHAPEOUTERHILITESTR,  /* 3d Shape Dialog outer hilite label     */
   DLG_STR_SHAPEOUTERSHADOWSTR,  /* 3d Shape Dialog outer shadow label     */
   DLG_STR_SHAPEOUTERWIDTHSTR,   /* 3d Shape Dialog outer width label      */
   DLG_STR_SHAPESHADOWSTR,       /* 3d Shape Dialog shadow label           */
   DLG_STR_SHAPESHADOWCOLORSTR,  /* 3d Shape Dialog shadow color label     */
   DLG_STR_SHAPESHADOWXSTR,      /* 3d Shape Dialog shadow x label         */
   DLG_STR_SHAPESHADOWYSTR,      /* 3d Shape Dialog shadow y label         */
   /*
     Gradient Dialog strings
   */
   /* Gradient Categories */
   DLG_STR_GRAD_LINE_CLASS,
   DLG_STR_GRAD_ANGLE_CLASS,
   DLG_STR_GRAD_RECT_CLASS,
   DLG_STR_GRAD_ELLIPSE_CLASS,
   DLG_STR_GRAD_CON_CLASS,
   /* Gradient Styles */
   DLG_STR_GRAD_LINE_LTOR,
   DLG_STR_GRAD_LINE_RTOL,
   DLG_STR_GRAD_LINE_TTOB,
   DLG_STR_GRAD_LINE_BTOT,
   DLG_STR_GRAD_LINE_LTTORB,
   DLG_STR_GRAD_LINE_LBTORT,
   DLG_STR_GRAD_LINE_RTTOLB,
   DLG_STR_GRAD_LINE_RBTOLT,
   DLG_STR_GRAD_LINE2_LRTOC,
   DLG_STR_GRAD_LINE2_CTOLR,
   DLG_STR_GRAD_LINE2_TBTOC,
   DLG_STR_GRAD_LINE2_CTOTB,
   DLG_STR_GRAD_LINE2_LTRBTOC,
   DLG_STR_GRAD_LINE2_CTOLTRB,
   DLG_STR_GRAD_LINE2_RTLBTOC,
   DLG_STR_GRAD_LINE2_CTORTLB,
   DLG_STR_GRAD_ANGLE_TOLT,
   DLG_STR_GRAD_ANGLE_TOLB,
   DLG_STR_GRAD_ANGLE_TORT,
   DLG_STR_GRAD_ANGLE_TORB,
   DLG_STR_GRAD_ANGLE_FROMLT,
   DLG_STR_GRAD_ANGLE_FROMLB,
   DLG_STR_GRAD_ANGLE_FROMRT,
   DLG_STR_GRAD_ANGLE_FROMRB,
   DLG_STR_GRAD_RECT_TOC,
   DLG_STR_GRAD_RECT_FROMC,
   DLG_STR_GRAD_ELLIPSE_TOC,
   DLG_STR_GRAD_ELLIPSE_FROMC,
   DLG_STR_GRAD_CON_FROML,
   DLG_STR_GRAD_CON_FROMR,
   DLG_STR_GRAD_CON_FROMT,
   DLG_STR_GRAD_CON_FROMB,
   DLG_STR_GRAD_CON_FROMLT,
   DLG_STR_GRAD_CON_FROMLB,
   DLG_STR_GRAD_CON_FROMRT,
   DLG_STR_GRAD_CON_FROMRB,
   /* Gradient Dialog control strings */
   DLG_STR_GRADIENTOPTIONSSTR,    /* Gradient dialog title caption        */
   DLG_STR_GRADIENTPREVIEWSTR,    /* Gradient dialog preview button label */
   DLG_STR_GRADIENTCATEGORYSTR,   /* Gradient dialog category label       */
   DLG_STR_GRADIENTSTYLESTR,      /* Gradient dialog style label          */
   DLG_STR_GRADIENTSTARTCOLORSTR, /* Gradient dialog start color label    */
   DLG_STR_GRADIENTENDCOLORSTR,   /* Gradient dialog end color label      */
   DLG_STR_GRADIENTSTEPSSTR,      /* Gradient dialog steps label          */
   /*
     Transition Dialog strings
   */
   /* Transition options */
   DLG_STR_TRANS_SOLIDFILL,
   DLG_STR_TRANS_HORZFILL,
   DLG_STR_TRANS_VERTFILL,
   DLG_STR_TRANS_FOREDIAGFILL,
   DLG_STR_TRANS_BACKDIAGFILL,
   DLG_STR_TRANS_CROSSFILL,
   DLG_STR_TRANS_DIAGCROSSFILL,
   DLG_STR_TRANS_GRADIENTFILL,
   /* Transition Dialog control strings */
   DLG_STR_TRANSITIONOPTIONSSTR,  /* Transition dialog title caption        */
   DLG_STR_TRANSITIONPREVIEWSTR,  /* Transition dialog preview button label */
   DLG_STR_TRANSITIONFILLSTR,     /* Transition dialog fill style label     */
   DLG_STR_TRANSITIONGRADIENTSTR, /* Transition dialog gradient style label */
   DLG_STR_TRANSITIONFORECOLORSTR,/* Transition dialog fore color label     */
   DLG_STR_TRANSITIONBACKCOLORSTR,/* Transition dialog back color label     */
   DLG_STR_TRANSITIONDELAYSTR,    /* Transition dialog delay label          */
   DLG_STR_TRANSITIONGRAINSTR,    /* Transition dialog grain label          */
   DLG_STR_TRANSITIONEFFECTSTR,   /* Transition dialog effect button label  */
   DLG_STR_TRANSITIONTRANSPARENTSTR,/* Transition dialog transparent label  */
   DLG_STR_TRANSITIONPASSESSTR,   /* Transition dialog passes label         */
   DLG_STR_TRANSITIONWANDSTR,     /* Transition dialog wand label           */
   DLG_STR_SHAPE_TRANS_MAX,       /* end of shape/trans strings */
};

enum {
   /*
     Paint Effect Dialog strings
   */
   /* Paint Effect Dialog control strings */
   DLG_STR_EFFECTOPTIONSSTR=DLG_STR_SHAPE_TRANS_MAX,/* Paint Effect dialog title caption      */
   DLG_STR_EFFECTCATEGORYSTR,     /* Paint Effect dialog category label     */
   DLG_STR_EFFECTSTYLESTR,        /* Paint Effect dialog style label        */
   DLG_STR_EFFECTPREVIEWSTR,      /* Paint Effect dialog preview label      */
   DLG_STR_EFFECTDELAYSTR,        /* Paint Effect dialog delay label        */
   DLG_STR_EFFECTGRAINSTR,        /* Paint Effect dialog grain label        */
   DLG_STR_EFFECTPASSESSTR,       /* Paint Effect dialog passes label       */
   DLG_STR_EFFECTWANDSTR,         /* Paint Effect dialog wand label         */
   DLG_STR_EFFECTTRANSPARENTSTR,  /* Paint Effect dialog transparent label */
   /* Paint Effect Dialog effect class strings */
   DLG_STR_EFFECT_NONE_CLASS,
   DLG_STR_EFFECT_WIPE_CLASS,
   DLG_STR_EFFECT_WIPE_RECTANGLE_CLASS,
   DLG_STR_EFFECT_WIPE_CIRCLE_CLASS,
   DLG_STR_EFFECT_PUSH_CLASS,
   DLG_STR_EFFECT_SLIDE_CLASS,
   DLG_STR_EFFECT_ROLL_CLASS,
   DLG_STR_EFFECT_ROTATE_CLASS,
   DLG_STR_EFFECT_ZOOM_CLASS,
   DLG_STR_EFFECT_DRIP_CLASS,
   DLG_STR_EFFECT_BLIND_CLASS,
   DLG_STR_EFFECT_RANDOM_CLASS,
   DLG_STR_EFFECT_CHECKERBOARD_CLASS,
   DLG_STR_EFFECT_BLOCKS_CLASS,
   DLG_STR_EFFECT_CIRCLE_CLASS,
   DLG_STR_EFFECT_ELLIPSE_CLASS,
   /* Paint Effect Dialog effect strings */
   DLG_STR_EFFECT_NONE,
   DLG_STR_EFFECT_NO_PICTURE,

   DLG_STR_EFFECT_WIPE_L_TO_R,
   DLG_STR_EFFECT_WIPE_R_TO_L,
   DLG_STR_EFFECT_WIPE_T_TO_B,
   DLG_STR_EFFECT_WIPE_B_TO_T,
   DLG_STR_EFFECT_WIPE_LT_TO_RB,
   DLG_STR_EFFECT_WIPE_LB_TO_RT,
   DLG_STR_EFFECT_WIPE_RT_TO_LB,
   DLG_STR_EFFECT_WIPE_RB_TO_LT,
   DLG_STR_EFFECT_WIPE_INTERH_L_TO_R_THEN_L_TO_R,
   DLG_STR_EFFECT_WIPE_INTERV_T_TO_B_THEN_T_TO_B,
   DLG_STR_EFFECT_WIPE_INTERH_L_TO_R_THEN_R_TO_L,
   DLG_STR_EFFECT_WIPE_INTERV_T_TO_B_THEN_B_TO_T,
   DLG_STR_EFFECT_WIPE_INTERV_L_TO_R_THEN_L_TO_R,
   DLG_STR_EFFECT_WIPE_INTERV_R_TO_L_THEN_R_TO_L,
   DLG_STR_EFFECT_WIPE_INTERH_T_TO_B_THEN_T_TO_B,
   DLG_STR_EFFECT_WIPE_INTERH_B_TO_T_THEN_B_TO_T,
   DLG_STR_EFFECT_WIPE_INTERV_L_TO_R_THEN_R_TO_L,
   DLG_STR_EFFECT_WIPE_INTERV_R_TO_L_THEN_L_TO_R,
   DLG_STR_EFFECT_WIPE_INTERH_T_TO_B_THEN_B_TO_T,
   DLG_STR_EFFECT_WIPE_INTERH_B_TO_T_THEN_T_TO_B,
   DLG_STR_EFFECT_WIPE_INTERH_L_TO_R_AND_R_TO_L,
   DLG_STR_EFFECT_WIPE_INTERV_T_TO_B_AND_B_TO_T,
   DLG_STR_EFFECT_WIPE_INTERV_L_AND_R_TO_C,
   DLG_STR_EFFECT_WIPE_INTERV_C_TO_L_AND_R,
   DLG_STR_EFFECT_WIPE_INTERH_T_AND_B_TO_C,
   DLG_STR_EFFECT_WIPE_INTERH_C_TO_T_AND_B,
   DLG_STR_EFFECT_WIPE_INTERV_L_AND_R_TO_C_THEN_C_TO_L_AND_R,
   DLG_STR_EFFECT_WIPE_INTERV_C_TO_L_AND_R_THEN_L_AND_R_TO_C,
   DLG_STR_EFFECT_WIPE_INTERH_T_AND_B_TO_C_THEN_C_TO_T_AND_B,
   DLG_STR_EFFECT_WIPE_INTERH_C_TO_T_AND_B_THEN_T_AND_B_TO_C,
   DLG_STR_EFFECT_WIPE2_LT_AND_RB_TO_C,
   DLG_STR_EFFECT_WIPE2_LB_AND_RT_TO_C,
   DLG_STR_EFFECT_WIPE2_C_TO_LT_AND_RB,
   DLG_STR_EFFECT_WIPE2_C_TO_LB_AND_RT,
   DLG_STR_EFFECT_WIPE2_LB_AND_RB_TO_T,
   DLG_STR_EFFECT_WIPE2_LT_AND_RT_TO_B,
   DLG_STR_EFFECT_WIPE2_RT_AND_RB_TO_L,
   DLG_STR_EFFECT_WIPE2_LT_AND_LB_TO_R,
   DLG_STR_EFFECT_WIPE2_L_T_TO_B_AND_R_B_TO_T,
   DLG_STR_EFFECT_WIPE2_T_L_TO_R_AND_B_R_TO_L,
   DLG_STR_EFFECT_WIPE4_CORNERS_OUT,
   DLG_STR_EFFECT_WIPE4_C_TO_L_AND_R_THEN_T_AND_B,
   DLG_STR_EFFECT_WIPE4_T_AND_B_THEN_L_AND_R_TO_C,
   DLG_STR_EFFECT_WIPE4_L_L_L_L,
   DLG_STR_EFFECT_WIPE4_L_L_L_R,
   DLG_STR_EFFECT_WIPE4_L_L_L_T,
   DLG_STR_EFFECT_WIPE4_L_L_L_B,
   DLG_STR_EFFECT_WIPE4_L_L_R_L,
   DLG_STR_EFFECT_WIPE4_L_L_R_R,
   DLG_STR_EFFECT_WIPE4_L_L_R_T,
   DLG_STR_EFFECT_WIPE4_L_L_R_B,
   DLG_STR_EFFECT_WIPE4_L_L_T_L,
   DLG_STR_EFFECT_WIPE4_L_L_T_R,
   DLG_STR_EFFECT_WIPE4_L_L_T_T,
   DLG_STR_EFFECT_WIPE4_L_L_T_B,
   DLG_STR_EFFECT_WIPE4_L_L_B_L,
   DLG_STR_EFFECT_WIPE4_L_L_B_R,
   DLG_STR_EFFECT_WIPE4_L_L_B_T,
   DLG_STR_EFFECT_WIPE4_L_L_B_B,
   DLG_STR_EFFECT_WIPE4_L_R_L_L,
   DLG_STR_EFFECT_WIPE4_L_R_L_R,
   DLG_STR_EFFECT_WIPE4_L_R_L_T,
   DLG_STR_EFFECT_WIPE4_L_R_L_B,
   DLG_STR_EFFECT_WIPE4_L_R_R_L,
   DLG_STR_EFFECT_WIPE4_L_R_R_R,
   DLG_STR_EFFECT_WIPE4_L_R_R_T,
   DLG_STR_EFFECT_WIPE4_L_R_R_B,
   DLG_STR_EFFECT_WIPE4_L_R_T_L,
   DLG_STR_EFFECT_WIPE4_L_R_T_R,
   DLG_STR_EFFECT_WIPE4_L_R_T_T,
   DLG_STR_EFFECT_WIPE4_L_R_T_B,
   DLG_STR_EFFECT_WIPE4_L_R_B_L,
   DLG_STR_EFFECT_WIPE4_L_R_B_R,
   DLG_STR_EFFECT_WIPE4_L_R_B_T,
   DLG_STR_EFFECT_WIPE4_L_R_B_B,
   DLG_STR_EFFECT_WIPE4_L_T_L_L,
   DLG_STR_EFFECT_WIPE4_L_T_L_R,
   DLG_STR_EFFECT_WIPE4_L_T_L_T,
   DLG_STR_EFFECT_WIPE4_L_T_L_B,
   DLG_STR_EFFECT_WIPE4_L_T_R_L,
   DLG_STR_EFFECT_WIPE4_L_T_R_R,
   DLG_STR_EFFECT_WIPE4_L_T_R_T,
   DLG_STR_EFFECT_WIPE4_L_T_R_B,
   DLG_STR_EFFECT_WIPE4_L_T_T_L,
   DLG_STR_EFFECT_WIPE4_L_T_T_R,
   DLG_STR_EFFECT_WIPE4_L_T_T_T,
   DLG_STR_EFFECT_WIPE4_L_T_T_B,
   DLG_STR_EFFECT_WIPE4_L_T_B_L,
   DLG_STR_EFFECT_WIPE4_L_T_B_R,
   DLG_STR_EFFECT_WIPE4_L_T_B_T,
   DLG_STR_EFFECT_WIPE4_L_T_B_B,
   DLG_STR_EFFECT_WIPE4_L_B_L_L,
   DLG_STR_EFFECT_WIPE4_L_B_L_R,
   DLG_STR_EFFECT_WIPE4_L_B_L_T,
   DLG_STR_EFFECT_WIPE4_L_B_L_B,
   DLG_STR_EFFECT_WIPE4_L_B_R_L,
   DLG_STR_EFFECT_WIPE4_L_B_R_R,
   DLG_STR_EFFECT_WIPE4_L_B_R_T,
   DLG_STR_EFFECT_WIPE4_L_B_R_B,
   DLG_STR_EFFECT_WIPE4_L_B_T_L,
   DLG_STR_EFFECT_WIPE4_L_B_T_R,
   DLG_STR_EFFECT_WIPE4_L_B_T_T,
   DLG_STR_EFFECT_WIPE4_L_B_T_B,
   DLG_STR_EFFECT_WIPE4_L_B_B_L,
   DLG_STR_EFFECT_WIPE4_L_B_B_R,
   DLG_STR_EFFECT_WIPE4_L_B_B_T,
   DLG_STR_EFFECT_WIPE4_L_B_B_B,
   DLG_STR_EFFECT_WIPE4_R_L_L_L,
   DLG_STR_EFFECT_WIPE4_R_L_L_R,
   DLG_STR_EFFECT_WIPE4_R_L_L_T,
   DLG_STR_EFFECT_WIPE4_R_L_L_B,
   DLG_STR_EFFECT_WIPE4_R_L_R_L,
   DLG_STR_EFFECT_WIPE4_R_L_R_R,
   DLG_STR_EFFECT_WIPE4_R_L_R_T,
   DLG_STR_EFFECT_WIPE4_R_L_R_B,
   DLG_STR_EFFECT_WIPE4_R_L_T_L,
   DLG_STR_EFFECT_WIPE4_R_L_T_R,
   DLG_STR_EFFECT_WIPE4_R_L_T_T,
   DLG_STR_EFFECT_WIPE4_R_L_T_B,
   DLG_STR_EFFECT_WIPE4_R_L_B_L,
   DLG_STR_EFFECT_WIPE4_R_L_B_R,
   DLG_STR_EFFECT_WIPE4_R_L_B_T,
   DLG_STR_EFFECT_WIPE4_R_L_B_B,
   DLG_STR_EFFECT_WIPE4_R_R_L_L,
   DLG_STR_EFFECT_WIPE4_R_R_L_R,
   DLG_STR_EFFECT_WIPE4_R_R_L_T,
   DLG_STR_EFFECT_WIPE4_R_R_L_B,
   DLG_STR_EFFECT_WIPE4_R_R_R_L,
   DLG_STR_EFFECT_WIPE4_R_R_R_R,
   DLG_STR_EFFECT_WIPE4_R_R_R_T,
   DLG_STR_EFFECT_WIPE4_R_R_R_B,
   DLG_STR_EFFECT_WIPE4_R_R_T_L,
   DLG_STR_EFFECT_WIPE4_R_R_T_R,
   DLG_STR_EFFECT_WIPE4_R_R_T_T,
   DLG_STR_EFFECT_WIPE4_R_R_T_B,
   DLG_STR_EFFECT_WIPE4_R_R_B_L,
   DLG_STR_EFFECT_WIPE4_R_R_B_R,
   DLG_STR_EFFECT_WIPE4_R_R_B_T,
   DLG_STR_EFFECT_WIPE4_R_R_B_B,
   DLG_STR_EFFECT_WIPE4_R_T_L_L,
   DLG_STR_EFFECT_WIPE4_R_T_L_R,
   DLG_STR_EFFECT_WIPE4_R_T_L_T,
   DLG_STR_EFFECT_WIPE4_R_T_L_B,
   DLG_STR_EFFECT_WIPE4_R_T_R_L,
   DLG_STR_EFFECT_WIPE4_R_T_R_R,
   DLG_STR_EFFECT_WIPE4_R_T_R_T,
   DLG_STR_EFFECT_WIPE4_R_T_R_B,
   DLG_STR_EFFECT_WIPE4_R_T_T_L,
   DLG_STR_EFFECT_WIPE4_R_T_T_R,
   DLG_STR_EFFECT_WIPE4_R_T_T_T,
   DLG_STR_EFFECT_WIPE4_R_T_T_B,
   DLG_STR_EFFECT_WIPE4_R_T_B_L,
   DLG_STR_EFFECT_WIPE4_R_T_B_R,
   DLG_STR_EFFECT_WIPE4_R_T_B_T,
   DLG_STR_EFFECT_WIPE4_R_T_B_B,
   DLG_STR_EFFECT_WIPE4_R_B_L_L,
   DLG_STR_EFFECT_WIPE4_R_B_L_R,
   DLG_STR_EFFECT_WIPE4_R_B_L_T,
   DLG_STR_EFFECT_WIPE4_R_B_L_B,
   DLG_STR_EFFECT_WIPE4_R_B_R_L,
   DLG_STR_EFFECT_WIPE4_R_B_R_R,
   DLG_STR_EFFECT_WIPE4_R_B_R_T,
   DLG_STR_EFFECT_WIPE4_R_B_R_B,
   DLG_STR_EFFECT_WIPE4_R_B_T_L,
   DLG_STR_EFFECT_WIPE4_R_B_T_R,
   DLG_STR_EFFECT_WIPE4_R_B_T_T,
   DLG_STR_EFFECT_WIPE4_R_B_T_B,
   DLG_STR_EFFECT_WIPE4_R_B_B_L,
   DLG_STR_EFFECT_WIPE4_R_B_B_R,
   DLG_STR_EFFECT_WIPE4_R_B_B_T,
   DLG_STR_EFFECT_WIPE4_R_B_B_B,
   DLG_STR_EFFECT_WIPE4_T_L_L_L,
   DLG_STR_EFFECT_WIPE4_T_L_L_R,
   DLG_STR_EFFECT_WIPE4_T_L_L_T,
   DLG_STR_EFFECT_WIPE4_T_L_L_B,
   DLG_STR_EFFECT_WIPE4_T_L_R_L,
   DLG_STR_EFFECT_WIPE4_T_L_R_R,
   DLG_STR_EFFECT_WIPE4_T_L_R_T,
   DLG_STR_EFFECT_WIPE4_T_L_R_B,
   DLG_STR_EFFECT_WIPE4_T_L_T_L,
   DLG_STR_EFFECT_WIPE4_T_L_T_R,
   DLG_STR_EFFECT_WIPE4_T_L_T_T,
   DLG_STR_EFFECT_WIPE4_T_L_T_B,
   DLG_STR_EFFECT_WIPE4_T_L_B_L,
   DLG_STR_EFFECT_WIPE4_T_L_B_R,
   DLG_STR_EFFECT_WIPE4_T_L_B_T,
   DLG_STR_EFFECT_WIPE4_T_L_B_B,
   DLG_STR_EFFECT_WIPE4_T_R_L_L,
   DLG_STR_EFFECT_WIPE4_T_R_L_R,
   DLG_STR_EFFECT_WIPE4_T_R_L_T,
   DLG_STR_EFFECT_WIPE4_T_R_L_B,
   DLG_STR_EFFECT_WIPE4_T_R_R_L,
   DLG_STR_EFFECT_WIPE4_T_R_R_R,
   DLG_STR_EFFECT_WIPE4_T_R_R_T,
   DLG_STR_EFFECT_WIPE4_T_R_R_B,
   DLG_STR_EFFECT_WIPE4_T_R_T_L,
   DLG_STR_EFFECT_WIPE4_T_R_T_R,
   DLG_STR_EFFECT_WIPE4_T_R_T_T,
   DLG_STR_EFFECT_WIPE4_T_R_T_B,
   DLG_STR_EFFECT_WIPE4_T_R_B_L,
   DLG_STR_EFFECT_WIPE4_T_R_B_R,
   DLG_STR_EFFECT_WIPE4_T_R_B_T,
   DLG_STR_EFFECT_WIPE4_T_R_B_B,
   DLG_STR_EFFECT_WIPE4_T_T_L_L,
   DLG_STR_EFFECT_WIPE4_T_T_L_R,
   DLG_STR_EFFECT_WIPE4_T_T_L_T,
   DLG_STR_EFFECT_WIPE4_T_T_L_B,
   DLG_STR_EFFECT_WIPE4_T_T_R_L,
   DLG_STR_EFFECT_WIPE4_T_T_R_R,
   DLG_STR_EFFECT_WIPE4_T_T_R_T,
   DLG_STR_EFFECT_WIPE4_T_T_R_B,
   DLG_STR_EFFECT_WIPE4_T_T_T_L,
   DLG_STR_EFFECT_WIPE4_T_T_T_R,
   DLG_STR_EFFECT_WIPE4_T_T_T_T,
   DLG_STR_EFFECT_WIPE4_T_T_T_B,
   DLG_STR_EFFECT_WIPE4_T_T_B_L,
   DLG_STR_EFFECT_WIPE4_T_T_B_R,
   DLG_STR_EFFECT_WIPE4_T_T_B_T,
   DLG_STR_EFFECT_WIPE4_T_T_B_B,
   DLG_STR_EFFECT_WIPE4_T_B_L_L,
   DLG_STR_EFFECT_WIPE4_T_B_L_R,
   DLG_STR_EFFECT_WIPE4_T_B_L_T,
   DLG_STR_EFFECT_WIPE4_T_B_L_B,
   DLG_STR_EFFECT_WIPE4_T_B_R_L,
   DLG_STR_EFFECT_WIPE4_T_B_R_R,
   DLG_STR_EFFECT_WIPE4_T_B_R_T,
   DLG_STR_EFFECT_WIPE4_T_B_R_B,
   DLG_STR_EFFECT_WIPE4_T_B_T_L,
   DLG_STR_EFFECT_WIPE4_T_B_T_R,
   DLG_STR_EFFECT_WIPE4_T_B_T_T,
   DLG_STR_EFFECT_WIPE4_T_B_T_B,
   DLG_STR_EFFECT_WIPE4_T_B_B_L,
   DLG_STR_EFFECT_WIPE4_T_B_B_R,
   DLG_STR_EFFECT_WIPE4_T_B_B_T,
   DLG_STR_EFFECT_WIPE4_T_B_B_B,
   DLG_STR_EFFECT_WIPE4_B_L_L_L,
   DLG_STR_EFFECT_WIPE4_B_L_L_R,
   DLG_STR_EFFECT_WIPE4_B_L_L_T,
   DLG_STR_EFFECT_WIPE4_B_L_L_B,
   DLG_STR_EFFECT_WIPE4_B_L_R_L,
   DLG_STR_EFFECT_WIPE4_B_L_R_R,
   DLG_STR_EFFECT_WIPE4_B_L_R_T,
   DLG_STR_EFFECT_WIPE4_B_L_R_B,
   DLG_STR_EFFECT_WIPE4_B_L_T_L,
   DLG_STR_EFFECT_WIPE4_B_L_T_R,
   DLG_STR_EFFECT_WIPE4_B_L_T_T,
   DLG_STR_EFFECT_WIPE4_B_L_T_B,
   DLG_STR_EFFECT_WIPE4_B_L_B_L,
   DLG_STR_EFFECT_WIPE4_B_L_B_R,
   DLG_STR_EFFECT_WIPE4_B_L_B_T,
   DLG_STR_EFFECT_WIPE4_B_L_B_B,
   DLG_STR_EFFECT_WIPE4_B_R_L_L,
   DLG_STR_EFFECT_WIPE4_B_R_L_R,
   DLG_STR_EFFECT_WIPE4_B_R_L_T,
   DLG_STR_EFFECT_WIPE4_B_R_L_B,
   DLG_STR_EFFECT_WIPE4_B_R_R_L,
   DLG_STR_EFFECT_WIPE4_B_R_R_R,
   DLG_STR_EFFECT_WIPE4_B_R_R_T,
   DLG_STR_EFFECT_WIPE4_B_R_R_B,
   DLG_STR_EFFECT_WIPE4_B_R_T_L,
   DLG_STR_EFFECT_WIPE4_B_R_T_R,
   DLG_STR_EFFECT_WIPE4_B_R_T_T,
   DLG_STR_EFFECT_WIPE4_B_R_T_B,
   DLG_STR_EFFECT_WIPE4_B_R_B_L,
   DLG_STR_EFFECT_WIPE4_B_R_B_R,
   DLG_STR_EFFECT_WIPE4_B_R_B_T,
   DLG_STR_EFFECT_WIPE4_B_R_B_B,
   DLG_STR_EFFECT_WIPE4_B_T_L_L,
   DLG_STR_EFFECT_WIPE4_B_T_L_R,
   DLG_STR_EFFECT_WIPE4_B_T_L_T,
   DLG_STR_EFFECT_WIPE4_B_T_L_B,
   DLG_STR_EFFECT_WIPE4_B_T_R_L,
   DLG_STR_EFFECT_WIPE4_B_T_R_R,
   DLG_STR_EFFECT_WIPE4_B_T_R_T,
   DLG_STR_EFFECT_WIPE4_B_T_R_B,
   DLG_STR_EFFECT_WIPE4_B_T_T_L,
   DLG_STR_EFFECT_WIPE4_B_T_T_R,
   DLG_STR_EFFECT_WIPE4_B_T_T_T,
   DLG_STR_EFFECT_WIPE4_B_T_T_B,
   DLG_STR_EFFECT_WIPE4_B_T_B_L,
   DLG_STR_EFFECT_WIPE4_B_T_B_R,
   DLG_STR_EFFECT_WIPE4_B_T_B_T,
   DLG_STR_EFFECT_WIPE4_B_T_B_B,
   DLG_STR_EFFECT_WIPE4_B_B_L_L,
   DLG_STR_EFFECT_WIPE4_B_B_L_R,
   DLG_STR_EFFECT_WIPE4_B_B_L_T,
   DLG_STR_EFFECT_WIPE4_B_B_L_B,
   DLG_STR_EFFECT_WIPE4_B_B_R_L,
   DLG_STR_EFFECT_WIPE4_B_B_R_R,
   DLG_STR_EFFECT_WIPE4_B_B_R_T,
   DLG_STR_EFFECT_WIPE4_B_B_R_B,
   DLG_STR_EFFECT_WIPE4_B_B_T_L,
   DLG_STR_EFFECT_WIPE4_B_B_T_R,
   DLG_STR_EFFECT_WIPE4_B_B_T_T,
   DLG_STR_EFFECT_WIPE4_B_B_T_B,
   DLG_STR_EFFECT_WIPE4_B_B_B_L,
   DLG_STR_EFFECT_WIPE4_B_B_B_R,
   DLG_STR_EFFECT_WIPE4_B_B_B_T,
   DLG_STR_EFFECT_WIPE4_B_B_B_B,
   DLG_STR_EFFECT_WIPE4_LT_LT_LT_LT,
   DLG_STR_EFFECT_WIPE4_LT_LT_LT_LB,
   DLG_STR_EFFECT_WIPE4_LT_LT_LT_RT,
   DLG_STR_EFFECT_WIPE4_LT_LT_LT_RB,
   DLG_STR_EFFECT_WIPE4_LT_LT_LB_LT,
   DLG_STR_EFFECT_WIPE4_LT_LT_LB_LB,
   DLG_STR_EFFECT_WIPE4_LT_LT_LB_RT,
   DLG_STR_EFFECT_WIPE4_LT_LT_LB_RB,
   DLG_STR_EFFECT_WIPE4_LT_LT_RT_LT,
   DLG_STR_EFFECT_WIPE4_LT_LT_RT_LB,
   DLG_STR_EFFECT_WIPE4_LT_LT_RT_RT,
   DLG_STR_EFFECT_WIPE4_LT_LT_RT_RB,
   DLG_STR_EFFECT_WIPE4_LT_LT_RB_LT,
   DLG_STR_EFFECT_WIPE4_LT_LT_RB_LB,
   DLG_STR_EFFECT_WIPE4_LT_LT_RB_RT,
   DLG_STR_EFFECT_WIPE4_LT_LT_RB_RB,
   DLG_STR_EFFECT_WIPE4_LT_LB_LT_LT,
   DLG_STR_EFFECT_WIPE4_LT_LB_LT_LB,
   DLG_STR_EFFECT_WIPE4_LT_LB_LT_RT,
   DLG_STR_EFFECT_WIPE4_LT_LB_LT_RB,
   DLG_STR_EFFECT_WIPE4_LT_LB_LB_LT,
   DLG_STR_EFFECT_WIPE4_LT_LB_LB_LB,
   DLG_STR_EFFECT_WIPE4_LT_LB_LB_RT,
   DLG_STR_EFFECT_WIPE4_LT_LB_LB_RB,
   DLG_STR_EFFECT_WIPE4_LT_LB_RT_LT,
   DLG_STR_EFFECT_WIPE4_LT_LB_RT_LB,
   DLG_STR_EFFECT_WIPE4_LT_LB_RT_RT,
   DLG_STR_EFFECT_WIPE4_LT_LB_RT_RB,
   DLG_STR_EFFECT_WIPE4_LT_LB_RB_LT,
   DLG_STR_EFFECT_WIPE4_LT_LB_RB_LB,
   DLG_STR_EFFECT_WIPE4_LT_LB_RB_RT,
   DLG_STR_EFFECT_WIPE4_LT_LB_RB_RB,
   DLG_STR_EFFECT_WIPE4_LT_RT_LT_LT,
   DLG_STR_EFFECT_WIPE4_LT_RT_LT_LB,
   DLG_STR_EFFECT_WIPE4_LT_RT_LT_RT,
   DLG_STR_EFFECT_WIPE4_LT_RT_LT_RB,
   DLG_STR_EFFECT_WIPE4_LT_RT_LB_LT,
   DLG_STR_EFFECT_WIPE4_LT_RT_LB_LB,
   DLG_STR_EFFECT_WIPE4_LT_RT_LB_RT,
   DLG_STR_EFFECT_WIPE4_LT_RT_LB_RB,
   DLG_STR_EFFECT_WIPE4_LT_RT_RT_LT,
   DLG_STR_EFFECT_WIPE4_LT_RT_RT_LB,
   DLG_STR_EFFECT_WIPE4_LT_RT_RT_RT,
   DLG_STR_EFFECT_WIPE4_LT_RT_RT_RB,
   DLG_STR_EFFECT_WIPE4_LT_RT_RB_LT,
   DLG_STR_EFFECT_WIPE4_LT_RT_RB_LB,
   DLG_STR_EFFECT_WIPE4_LT_RT_RB_RT,
   DLG_STR_EFFECT_WIPE4_LT_RT_RB_RB,
   DLG_STR_EFFECT_WIPE4_LT_RB_LT_LT,
   DLG_STR_EFFECT_WIPE4_LT_RB_LT_LB,
   DLG_STR_EFFECT_WIPE4_LT_RB_LT_RT,
   DLG_STR_EFFECT_WIPE4_LT_RB_LT_RB,
   DLG_STR_EFFECT_WIPE4_LT_RB_LB_LT,
   DLG_STR_EFFECT_WIPE4_LT_RB_LB_LB,
   DLG_STR_EFFECT_WIPE4_LT_RB_LB_RT,
   DLG_STR_EFFECT_WIPE4_LT_RB_LB_RB,
   DLG_STR_EFFECT_WIPE4_LT_RB_RT_LT,
   DLG_STR_EFFECT_WIPE4_LT_RB_RT_LB,
   DLG_STR_EFFECT_WIPE4_LT_RB_RT_RT,
   DLG_STR_EFFECT_WIPE4_LT_RB_RT_RB,
   DLG_STR_EFFECT_WIPE4_LT_RB_RB_LT,
   DLG_STR_EFFECT_WIPE4_LT_RB_RB_LB,
   DLG_STR_EFFECT_WIPE4_LT_RB_RB_RT,
   DLG_STR_EFFECT_WIPE4_LT_RB_RB_RB,
   DLG_STR_EFFECT_WIPE4_LB_LT_LT_LT,
   DLG_STR_EFFECT_WIPE4_LB_LT_LT_LB,
   DLG_STR_EFFECT_WIPE4_LB_LT_LT_RT,
   DLG_STR_EFFECT_WIPE4_LB_LT_LT_RB,
   DLG_STR_EFFECT_WIPE4_LB_LT_LB_LT,
   DLG_STR_EFFECT_WIPE4_LB_LT_LB_LB,
   DLG_STR_EFFECT_WIPE4_LB_LT_LB_RT,
   DLG_STR_EFFECT_WIPE4_LB_LT_LB_RB,
   DLG_STR_EFFECT_WIPE4_LB_LT_RT_LT,
   DLG_STR_EFFECT_WIPE4_LB_LT_RT_LB,
   DLG_STR_EFFECT_WIPE4_LB_LT_RT_RT,
   DLG_STR_EFFECT_WIPE4_LB_LT_RT_RB,
   DLG_STR_EFFECT_WIPE4_LB_LT_RB_LT,
   DLG_STR_EFFECT_WIPE4_LB_LT_RB_LB,
   DLG_STR_EFFECT_WIPE4_LB_LT_RB_RT,
   DLG_STR_EFFECT_WIPE4_LB_LT_RB_RB,
   DLG_STR_EFFECT_WIPE4_LB_LB_LT_LT,
   DLG_STR_EFFECT_WIPE4_LB_LB_LT_LB,
   DLG_STR_EFFECT_WIPE4_LB_LB_LT_RT,
   DLG_STR_EFFECT_WIPE4_LB_LB_LT_RB,
   DLG_STR_EFFECT_WIPE4_LB_LB_LB_LT,
   DLG_STR_EFFECT_WIPE4_LB_LB_LB_LB,
   DLG_STR_EFFECT_WIPE4_LB_LB_LB_RT,
   DLG_STR_EFFECT_WIPE4_LB_LB_LB_RB,
   DLG_STR_EFFECT_WIPE4_LB_LB_RT_LT,
   DLG_STR_EFFECT_WIPE4_LB_LB_RT_LB,
   DLG_STR_EFFECT_WIPE4_LB_LB_RT_RT,
   DLG_STR_EFFECT_WIPE4_LB_LB_RT_RB,
   DLG_STR_EFFECT_WIPE4_LB_LB_RB_LT,
   DLG_STR_EFFECT_WIPE4_LB_LB_RB_LB,
   DLG_STR_EFFECT_WIPE4_LB_LB_RB_RT,
   DLG_STR_EFFECT_WIPE4_LB_LB_RB_RB,
   DLG_STR_EFFECT_WIPE4_LB_RT_LT_LT,
   DLG_STR_EFFECT_WIPE4_LB_RT_LT_LB,
   DLG_STR_EFFECT_WIPE4_LB_RT_LT_RT,
   DLG_STR_EFFECT_WIPE4_LB_RT_LT_RB,
   DLG_STR_EFFECT_WIPE4_LB_RT_LB_LT,
   DLG_STR_EFFECT_WIPE4_LB_RT_LB_LB,
   DLG_STR_EFFECT_WIPE4_LB_RT_LB_RT,
   DLG_STR_EFFECT_WIPE4_LB_RT_LB_RB,
   DLG_STR_EFFECT_WIPE4_LB_RT_RT_LT,
   DLG_STR_EFFECT_WIPE4_LB_RT_RT_LB,
   DLG_STR_EFFECT_WIPE4_LB_RT_RT_RT,
   DLG_STR_EFFECT_WIPE4_LB_RT_RT_RB,
   DLG_STR_EFFECT_WIPE4_LB_RT_RB_LT,
   DLG_STR_EFFECT_WIPE4_LB_RT_RB_LB,
   DLG_STR_EFFECT_WIPE4_LB_RT_RB_RT,
   DLG_STR_EFFECT_WIPE4_LB_RT_RB_RB,
   DLG_STR_EFFECT_WIPE4_LB_RB_LT_LT,
   DLG_STR_EFFECT_WIPE4_LB_RB_LT_LB,
   DLG_STR_EFFECT_WIPE4_LB_RB_LT_RT,
   DLG_STR_EFFECT_WIPE4_LB_RB_LT_RB,
   DLG_STR_EFFECT_WIPE4_LB_RB_LB_LT,
   DLG_STR_EFFECT_WIPE4_LB_RB_LB_LB,
   DLG_STR_EFFECT_WIPE4_LB_RB_LB_RT,
   DLG_STR_EFFECT_WIPE4_LB_RB_LB_RB,
   DLG_STR_EFFECT_WIPE4_LB_RB_RT_LT,
   DLG_STR_EFFECT_WIPE4_LB_RB_RT_LB,
   DLG_STR_EFFECT_WIPE4_LB_RB_RT_RT,
   DLG_STR_EFFECT_WIPE4_LB_RB_RT_RB,
   DLG_STR_EFFECT_WIPE4_LB_RB_RB_LT,
   DLG_STR_EFFECT_WIPE4_LB_RB_RB_LB,
   DLG_STR_EFFECT_WIPE4_LB_RB_RB_RT,
   DLG_STR_EFFECT_WIPE4_LB_RB_RB_RB,
   DLG_STR_EFFECT_WIPE4_RT_LT_LT_LT,
   DLG_STR_EFFECT_WIPE4_RT_LT_LT_LB,
   DLG_STR_EFFECT_WIPE4_RT_LT_LT_RT,
   DLG_STR_EFFECT_WIPE4_RT_LT_LT_RB,
   DLG_STR_EFFECT_WIPE4_RT_LT_LB_LT,
   DLG_STR_EFFECT_WIPE4_RT_LT_LB_LB,
   DLG_STR_EFFECT_WIPE4_RT_LT_LB_RT,
   DLG_STR_EFFECT_WIPE4_RT_LT_LB_RB,
   DLG_STR_EFFECT_WIPE4_RT_LT_RT_LT,
   DLG_STR_EFFECT_WIPE4_RT_LT_RT_LB,
   DLG_STR_EFFECT_WIPE4_RT_LT_RT_RT,
   DLG_STR_EFFECT_WIPE4_RT_LT_RT_RB,
   DLG_STR_EFFECT_WIPE4_RT_LT_RB_LT,
   DLG_STR_EFFECT_WIPE4_RT_LT_RB_LB,
   DLG_STR_EFFECT_WIPE4_RT_LT_RB_RT,
   DLG_STR_EFFECT_WIPE4_RT_LT_RB_RB,
   DLG_STR_EFFECT_WIPE4_RT_LB_LT_LT,
   DLG_STR_EFFECT_WIPE4_RT_LB_LT_LB,
   DLG_STR_EFFECT_WIPE4_RT_LB_LT_RT,
   DLG_STR_EFFECT_WIPE4_RT_LB_LT_RB,
   DLG_STR_EFFECT_WIPE4_RT_LB_LB_LT,
   DLG_STR_EFFECT_WIPE4_RT_LB_LB_LB,
   DLG_STR_EFFECT_WIPE4_RT_LB_LB_RT,
   DLG_STR_EFFECT_WIPE4_RT_LB_LB_RB,
   DLG_STR_EFFECT_WIPE4_RT_LB_RT_LT,
   DLG_STR_EFFECT_WIPE4_RT_LB_RT_LB,
   DLG_STR_EFFECT_WIPE4_RT_LB_RT_RT,
   DLG_STR_EFFECT_WIPE4_RT_LB_RT_RB,
   DLG_STR_EFFECT_WIPE4_RT_LB_RB_LT,
   DLG_STR_EFFECT_WIPE4_RT_LB_RB_LB,
   DLG_STR_EFFECT_WIPE4_RT_LB_RB_RT,
   DLG_STR_EFFECT_WIPE4_RT_LB_RB_RB,
   DLG_STR_EFFECT_WIPE4_RT_RT_LT_LT,
   DLG_STR_EFFECT_WIPE4_RT_RT_LT_LB,
   DLG_STR_EFFECT_WIPE4_RT_RT_LT_RT,
   DLG_STR_EFFECT_WIPE4_RT_RT_LT_RB,
   DLG_STR_EFFECT_WIPE4_RT_RT_LB_LT,
   DLG_STR_EFFECT_WIPE4_RT_RT_LB_LB,
   DLG_STR_EFFECT_WIPE4_RT_RT_LB_RT,
   DLG_STR_EFFECT_WIPE4_RT_RT_LB_RB,
   DLG_STR_EFFECT_WIPE4_RT_RT_RT_LT,
   DLG_STR_EFFECT_WIPE4_RT_RT_RT_LB,
   DLG_STR_EFFECT_WIPE4_RT_RT_RT_RT,
   DLG_STR_EFFECT_WIPE4_RT_RT_RT_RB,
   DLG_STR_EFFECT_WIPE4_RT_RT_RB_LT,
   DLG_STR_EFFECT_WIPE4_RT_RT_RB_LB,
   DLG_STR_EFFECT_WIPE4_RT_RT_RB_RT,
   DLG_STR_EFFECT_WIPE4_RT_RT_RB_RB,
   DLG_STR_EFFECT_WIPE4_RT_RB_LT_LT,
   DLG_STR_EFFECT_WIPE4_RT_RB_LT_LB,
   DLG_STR_EFFECT_WIPE4_RT_RB_LT_RT,
   DLG_STR_EFFECT_WIPE4_RT_RB_LT_RB,
   DLG_STR_EFFECT_WIPE4_RT_RB_LB_LT,
   DLG_STR_EFFECT_WIPE4_RT_RB_LB_LB,
   DLG_STR_EFFECT_WIPE4_RT_RB_LB_RT,
   DLG_STR_EFFECT_WIPE4_RT_RB_LB_RB,
   DLG_STR_EFFECT_WIPE4_RT_RB_RT_LT,
   DLG_STR_EFFECT_WIPE4_RT_RB_RT_LB,
   DLG_STR_EFFECT_WIPE4_RT_RB_RT_RT,
   DLG_STR_EFFECT_WIPE4_RT_RB_RT_RB,
   DLG_STR_EFFECT_WIPE4_RT_RB_RB_LT,
   DLG_STR_EFFECT_WIPE4_RT_RB_RB_LB,
   DLG_STR_EFFECT_WIPE4_RT_RB_RB_RT,
   DLG_STR_EFFECT_WIPE4_RT_RB_RB_RB,
   DLG_STR_EFFECT_WIPE4_RB_LT_LT_LT,
   DLG_STR_EFFECT_WIPE4_RB_LT_LT_LB,
   DLG_STR_EFFECT_WIPE4_RB_LT_LT_RT,
   DLG_STR_EFFECT_WIPE4_RB_LT_LT_RB,
   DLG_STR_EFFECT_WIPE4_RB_LT_LB_LT,
   DLG_STR_EFFECT_WIPE4_RB_LT_LB_LB,
   DLG_STR_EFFECT_WIPE4_RB_LT_LB_RT,
   DLG_STR_EFFECT_WIPE4_RB_LT_LB_RB,
   DLG_STR_EFFECT_WIPE4_RB_LT_RT_LT,
   DLG_STR_EFFECT_WIPE4_RB_LT_RT_LB,
   DLG_STR_EFFECT_WIPE4_RB_LT_RT_RT,
   DLG_STR_EFFECT_WIPE4_RB_LT_RT_RB,
   DLG_STR_EFFECT_WIPE4_RB_LT_RB_LT,
   DLG_STR_EFFECT_WIPE4_RB_LT_RB_LB,
   DLG_STR_EFFECT_WIPE4_RB_LT_RB_RT,
   DLG_STR_EFFECT_WIPE4_RB_LT_RB_RB,
   DLG_STR_EFFECT_WIPE4_RB_LB_LT_LT,
   DLG_STR_EFFECT_WIPE4_RB_LB_LT_LB,
   DLG_STR_EFFECT_WIPE4_RB_LB_LT_RT,
   DLG_STR_EFFECT_WIPE4_RB_LB_LT_RB,
   DLG_STR_EFFECT_WIPE4_RB_LB_LB_LT,
   DLG_STR_EFFECT_WIPE4_RB_LB_LB_LB,
   DLG_STR_EFFECT_WIPE4_RB_LB_LB_RT,
   DLG_STR_EFFECT_WIPE4_RB_LB_LB_RB,
   DLG_STR_EFFECT_WIPE4_RB_LB_RT_LT,
   DLG_STR_EFFECT_WIPE4_RB_LB_RT_LB,
   DLG_STR_EFFECT_WIPE4_RB_LB_RT_RT,
   DLG_STR_EFFECT_WIPE4_RB_LB_RT_RB,
   DLG_STR_EFFECT_WIPE4_RB_LB_RB_LT,
   DLG_STR_EFFECT_WIPE4_RB_LB_RB_LB,
   DLG_STR_EFFECT_WIPE4_RB_LB_RB_RT,
   DLG_STR_EFFECT_WIPE4_RB_LB_RB_RB,
   DLG_STR_EFFECT_WIPE4_RB_RT_LT_LT,
   DLG_STR_EFFECT_WIPE4_RB_RT_LT_LB,
   DLG_STR_EFFECT_WIPE4_RB_RT_LT_RT,
   DLG_STR_EFFECT_WIPE4_RB_RT_LT_RB,
   DLG_STR_EFFECT_WIPE4_RB_RT_LB_LT,
   DLG_STR_EFFECT_WIPE4_RB_RT_LB_LB,
   DLG_STR_EFFECT_WIPE4_RB_RT_LB_RT,
   DLG_STR_EFFECT_WIPE4_RB_RT_LB_RB,
   DLG_STR_EFFECT_WIPE4_RB_RT_RT_LT,
   DLG_STR_EFFECT_WIPE4_RB_RT_RT_LB,
   DLG_STR_EFFECT_WIPE4_RB_RT_RT_RT,
   DLG_STR_EFFECT_WIPE4_RB_RT_RT_RB,
   DLG_STR_EFFECT_WIPE4_RB_RT_RB_LT,
   DLG_STR_EFFECT_WIPE4_RB_RT_RB_LB,
   DLG_STR_EFFECT_WIPE4_RB_RT_RB_RT,
   DLG_STR_EFFECT_WIPE4_RB_RT_RB_RB,
   DLG_STR_EFFECT_WIPE4_RB_RB_LT_LT,
   DLG_STR_EFFECT_WIPE4_RB_RB_LT_LB,
   DLG_STR_EFFECT_WIPE4_RB_RB_LT_RT,
   DLG_STR_EFFECT_WIPE4_RB_RB_LT_RB,
   DLG_STR_EFFECT_WIPE4_RB_RB_LB_LT,
   DLG_STR_EFFECT_WIPE4_RB_RB_LB_LB,
   DLG_STR_EFFECT_WIPE4_RB_RB_LB_RT,
   DLG_STR_EFFECT_WIPE4_RB_RB_LB_RB,
   DLG_STR_EFFECT_WIPE4_RB_RB_RT_LT,
   DLG_STR_EFFECT_WIPE4_RB_RB_RT_LB,
   DLG_STR_EFFECT_WIPE4_RB_RB_RT_RT,
   DLG_STR_EFFECT_WIPE4_RB_RB_RT_RB,
   DLG_STR_EFFECT_WIPE4_RB_RB_RB_LT,
   DLG_STR_EFFECT_WIPE4_RB_RB_RB_LB,
   DLG_STR_EFFECT_WIPE4_RB_RB_RB_RT,
   DLG_STR_EFFECT_WIPE4_RB_RB_RB_RB,

   DLG_STR_EFFECT_WIPE_RECTANGLE_IN,
   DLG_STR_EFFECT_WIPE_RECTANGLE_OUT,
   DLG_STR_EFFECT_WIPE_RECTANGLE_INTER_IN_THEN_IN,
   DLG_STR_EFFECT_WIPE_RECTANGLE_INTER_OUT_THEN_OUT,
   DLG_STR_EFFECT_WIPE_RECTANGLE_INTER_IN_THEN_OUT,
   DLG_STR_EFFECT_WIPE_RECTANGLE_INTER_OUT_THEN_IN,

   DLG_STR_EFFECT_WIPE_CIRCLE_C_CW_FROM_L,
   DLG_STR_EFFECT_WIPE_CIRCLE_C_CCW_FROM_L,
   DLG_STR_EFFECT_WIPE_CIRCLE_C_CW_FROM_R,
   DLG_STR_EFFECT_WIPE_CIRCLE_C_CCW_FROM_R,
   DLG_STR_EFFECT_WIPE_CIRCLE_C_CW_FROM_T,
   DLG_STR_EFFECT_WIPE_CIRCLE_C_CCW_FROM_T,
   DLG_STR_EFFECT_WIPE_CIRCLE_C_CW_FROM_B,
   DLG_STR_EFFECT_WIPE_CIRCLE_C_CCW_FROM_B,
   DLG_STR_EFFECT_WIPE_CIRCLE_L_CCW_FROM_B,
   DLG_STR_EFFECT_WIPE_CIRCLE_L_CW_FROM_T,
   DLG_STR_EFFECT_WIPE_CIRCLE_R_CW_FROM_B,
   DLG_STR_EFFECT_WIPE_CIRCLE_R_CCW_FROM_T,
   DLG_STR_EFFECT_WIPE_CIRCLE_T_CCW_FROM_L,
   DLG_STR_EFFECT_WIPE_CIRCLE_T_CW_FROM_R,
   DLG_STR_EFFECT_WIPE_CIRCLE_B_CW_FROM_L,
   DLG_STR_EFFECT_WIPE_CIRCLE_B_CCW_FROM_R,
   DLG_STR_EFFECT_WIPE_CIRCLE2_C_CW_FROM_L_AND_FROM_R,
   DLG_STR_EFFECT_WIPE_CIRCLE2_C_CCW_FROM_L_AND_FROM_R,
   DLG_STR_EFFECT_WIPE_CIRCLE2_C_CW_FROM_T_AND_FROM_B,
   DLG_STR_EFFECT_WIPE_CIRCLE2_C_CCW_FROM_T_AND_FROM_B,
   DLG_STR_EFFECT_WIPE_CIRCLE2_L_CW_FROM_T_AND_CCW_FROM_B,
   DLG_STR_EFFECT_WIPE_CIRCLE2_L_CCW_TO_T_AND_CW_TO_B,
   DLG_STR_EFFECT_WIPE_CIRCLE2_R_CCW_FROM_T_AND_CW_FROM_B,
   DLG_STR_EFFECT_WIPE_CIRCLE2_R_CW_TO_T_AND_CCW_TO_B,
   DLG_STR_EFFECT_WIPE_CIRCLE2_T_CCW_FROM_L_AND_CW_FROM_R,
   DLG_STR_EFFECT_WIPE_CIRCLE2_T_CW_TO_L_AND_CCW_TO_R,
   DLG_STR_EFFECT_WIPE_CIRCLE2_B_CW_FROM_L_AND_CCW_FROM_R,
   DLG_STR_EFFECT_WIPE_CIRCLE2_B_CCW_TO_L_AND_CW_TO_R,
   DLG_STR_EFFECT_WIPE_CIRCLE4_C_CW_CCW_CCW_CW,
   DLG_STR_EFFECT_WIPE_CIRCLE4_C_CCW_CW_CW_CCW,
   DLG_STR_EFFECT_WIPE_END,
};

enum {
   DLG_STR_EFFECT_PUSH_R_TO_L=DLG_STR_EFFECT_WIPE_END,
   DLG_STR_EFFECT_PUSH_L_TO_R,
   DLG_STR_EFFECT_PUSH_B_TO_T,
   DLG_STR_EFFECT_PUSH_T_TO_B,
   DLG_STR_EFFECT_PUSH2_T_R_TO_L_AND_B_L_TO_R,
   DLG_STR_EFFECT_PUSH2_T_L_TO_R_AND_B_R_TO_L,
   DLG_STR_EFFECT_PUSH2_L_B_TO_T_AND_R_T_TO_B,
   DLG_STR_EFFECT_PUSH2_L_T_TO_B_AND_R_B_TO_T,
   DLG_STR_EFFECT_PUSH4_L_L_L_L,
   DLG_STR_EFFECT_PUSH4_L_L_L_R,
   DLG_STR_EFFECT_PUSH4_L_L_L_T,
   DLG_STR_EFFECT_PUSH4_L_L_L_B,
   DLG_STR_EFFECT_PUSH4_L_L_R_L,
   DLG_STR_EFFECT_PUSH4_L_L_R_R,
   DLG_STR_EFFECT_PUSH4_L_L_R_T,
   DLG_STR_EFFECT_PUSH4_L_L_R_B,
   DLG_STR_EFFECT_PUSH4_L_L_T_L,
   DLG_STR_EFFECT_PUSH4_L_L_T_R,
   DLG_STR_EFFECT_PUSH4_L_L_T_T,
   DLG_STR_EFFECT_PUSH4_L_L_T_B,
   DLG_STR_EFFECT_PUSH4_L_L_B_L,
   DLG_STR_EFFECT_PUSH4_L_L_B_R,
   DLG_STR_EFFECT_PUSH4_L_L_B_T,
   DLG_STR_EFFECT_PUSH4_L_L_B_B,
   DLG_STR_EFFECT_PUSH4_L_R_L_L,
   DLG_STR_EFFECT_PUSH4_L_R_L_R,
   DLG_STR_EFFECT_PUSH4_L_R_L_T,
   DLG_STR_EFFECT_PUSH4_L_R_L_B,
   DLG_STR_EFFECT_PUSH4_L_R_R_L,
   DLG_STR_EFFECT_PUSH4_L_R_R_R,
   DLG_STR_EFFECT_PUSH4_L_R_R_T,
   DLG_STR_EFFECT_PUSH4_L_R_R_B,
   DLG_STR_EFFECT_PUSH4_L_R_T_L,
   DLG_STR_EFFECT_PUSH4_L_R_T_R,
   DLG_STR_EFFECT_PUSH4_L_R_T_T,
   DLG_STR_EFFECT_PUSH4_L_R_T_B,
   DLG_STR_EFFECT_PUSH4_L_R_B_L,
   DLG_STR_EFFECT_PUSH4_L_R_B_R,
   DLG_STR_EFFECT_PUSH4_L_R_B_T,
   DLG_STR_EFFECT_PUSH4_L_R_B_B,
   DLG_STR_EFFECT_PUSH4_L_T_L_L,
   DLG_STR_EFFECT_PUSH4_L_T_L_R,
   DLG_STR_EFFECT_PUSH4_L_T_L_T,
   DLG_STR_EFFECT_PUSH4_L_T_L_B,
   DLG_STR_EFFECT_PUSH4_L_T_R_L,
   DLG_STR_EFFECT_PUSH4_L_T_R_R,
   DLG_STR_EFFECT_PUSH4_L_T_R_T,
   DLG_STR_EFFECT_PUSH4_L_T_R_B,
   DLG_STR_EFFECT_PUSH4_L_T_T_L,
   DLG_STR_EFFECT_PUSH4_L_T_T_R,
   DLG_STR_EFFECT_PUSH4_L_T_T_T,
   DLG_STR_EFFECT_PUSH4_L_T_T_B,
   DLG_STR_EFFECT_PUSH4_L_T_B_L,
   DLG_STR_EFFECT_PUSH4_L_T_B_R,
   DLG_STR_EFFECT_PUSH4_L_T_B_T,
   DLG_STR_EFFECT_PUSH4_L_T_B_B,
   DLG_STR_EFFECT_PUSH4_L_B_L_L,
   DLG_STR_EFFECT_PUSH4_L_B_L_R,
   DLG_STR_EFFECT_PUSH4_L_B_L_T,
   DLG_STR_EFFECT_PUSH4_L_B_L_B,
   DLG_STR_EFFECT_PUSH4_L_B_R_L,
   DLG_STR_EFFECT_PUSH4_L_B_R_R,
   DLG_STR_EFFECT_PUSH4_L_B_R_T,
   DLG_STR_EFFECT_PUSH4_L_B_R_B,
   DLG_STR_EFFECT_PUSH4_L_B_T_L,
   DLG_STR_EFFECT_PUSH4_L_B_T_R,
   DLG_STR_EFFECT_PUSH4_L_B_T_T,
   DLG_STR_EFFECT_PUSH4_L_B_T_B,
   DLG_STR_EFFECT_PUSH4_L_B_B_L,
   DLG_STR_EFFECT_PUSH4_L_B_B_R,
   DLG_STR_EFFECT_PUSH4_L_B_B_T,
   DLG_STR_EFFECT_PUSH4_L_B_B_B,
   DLG_STR_EFFECT_PUSH4_R_L_L_L,
   DLG_STR_EFFECT_PUSH4_R_L_L_R,
   DLG_STR_EFFECT_PUSH4_R_L_L_T,
   DLG_STR_EFFECT_PUSH4_R_L_L_B,
   DLG_STR_EFFECT_PUSH4_R_L_R_L,
   DLG_STR_EFFECT_PUSH4_R_L_R_R,
   DLG_STR_EFFECT_PUSH4_R_L_R_T,
   DLG_STR_EFFECT_PUSH4_R_L_R_B,
   DLG_STR_EFFECT_PUSH4_R_L_T_L,
   DLG_STR_EFFECT_PUSH4_R_L_T_R,
   DLG_STR_EFFECT_PUSH4_R_L_T_T,
   DLG_STR_EFFECT_PUSH4_R_L_T_B,
   DLG_STR_EFFECT_PUSH4_R_L_B_L,
   DLG_STR_EFFECT_PUSH4_R_L_B_R,
   DLG_STR_EFFECT_PUSH4_R_L_B_T,
   DLG_STR_EFFECT_PUSH4_R_L_B_B,
   DLG_STR_EFFECT_PUSH4_R_R_L_L,
   DLG_STR_EFFECT_PUSH4_R_R_L_R,
   DLG_STR_EFFECT_PUSH4_R_R_L_T,
   DLG_STR_EFFECT_PUSH4_R_R_L_B,
   DLG_STR_EFFECT_PUSH4_R_R_R_L,
   DLG_STR_EFFECT_PUSH4_R_R_R_R,
   DLG_STR_EFFECT_PUSH4_R_R_R_T,
   DLG_STR_EFFECT_PUSH4_R_R_R_B,
   DLG_STR_EFFECT_PUSH4_R_R_T_L,
   DLG_STR_EFFECT_PUSH4_R_R_T_R,
   DLG_STR_EFFECT_PUSH4_R_R_T_T,
   DLG_STR_EFFECT_PUSH4_R_R_T_B,
   DLG_STR_EFFECT_PUSH4_R_R_B_L,
   DLG_STR_EFFECT_PUSH4_R_R_B_R,
   DLG_STR_EFFECT_PUSH4_R_R_B_T,
   DLG_STR_EFFECT_PUSH4_R_R_B_B,
   DLG_STR_EFFECT_PUSH4_R_T_L_L,
   DLG_STR_EFFECT_PUSH4_R_T_L_R,
   DLG_STR_EFFECT_PUSH4_R_T_L_T,
   DLG_STR_EFFECT_PUSH4_R_T_L_B,
   DLG_STR_EFFECT_PUSH4_R_T_R_L,
   DLG_STR_EFFECT_PUSH4_R_T_R_R,
   DLG_STR_EFFECT_PUSH4_R_T_R_T,
   DLG_STR_EFFECT_PUSH4_R_T_R_B,
   DLG_STR_EFFECT_PUSH4_R_T_T_L,
   DLG_STR_EFFECT_PUSH4_R_T_T_R,
   DLG_STR_EFFECT_PUSH4_R_T_T_T,
   DLG_STR_EFFECT_PUSH4_R_T_T_B,
   DLG_STR_EFFECT_PUSH4_R_T_B_L,
   DLG_STR_EFFECT_PUSH4_R_T_B_R,
   DLG_STR_EFFECT_PUSH4_R_T_B_T,
   DLG_STR_EFFECT_PUSH4_R_T_B_B,
   DLG_STR_EFFECT_PUSH4_R_B_L_L,
   DLG_STR_EFFECT_PUSH4_R_B_L_R,
   DLG_STR_EFFECT_PUSH4_R_B_L_T,
   DLG_STR_EFFECT_PUSH4_R_B_L_B,
   DLG_STR_EFFECT_PUSH4_R_B_R_L,
   DLG_STR_EFFECT_PUSH4_R_B_R_R,
   DLG_STR_EFFECT_PUSH4_R_B_R_T,
   DLG_STR_EFFECT_PUSH4_R_B_R_B,
   DLG_STR_EFFECT_PUSH4_R_B_T_L,
   DLG_STR_EFFECT_PUSH4_R_B_T_R,
   DLG_STR_EFFECT_PUSH4_R_B_T_T,
   DLG_STR_EFFECT_PUSH4_R_B_T_B,
   DLG_STR_EFFECT_PUSH4_R_B_B_L,
   DLG_STR_EFFECT_PUSH4_R_B_B_R,
   DLG_STR_EFFECT_PUSH4_R_B_B_T,
   DLG_STR_EFFECT_PUSH4_R_B_B_B,
   DLG_STR_EFFECT_PUSH4_T_L_L_L,
   DLG_STR_EFFECT_PUSH4_T_L_L_R,
   DLG_STR_EFFECT_PUSH4_T_L_L_T,
   DLG_STR_EFFECT_PUSH4_T_L_L_B,
   DLG_STR_EFFECT_PUSH4_T_L_R_L,
   DLG_STR_EFFECT_PUSH4_T_L_R_R,
   DLG_STR_EFFECT_PUSH4_T_L_R_T,
   DLG_STR_EFFECT_PUSH4_T_L_R_B,
   DLG_STR_EFFECT_PUSH4_T_L_T_L,
   DLG_STR_EFFECT_PUSH4_T_L_T_R,
   DLG_STR_EFFECT_PUSH4_T_L_T_T,
   DLG_STR_EFFECT_PUSH4_T_L_T_B,
   DLG_STR_EFFECT_PUSH4_T_L_B_L,
   DLG_STR_EFFECT_PUSH4_T_L_B_R,
   DLG_STR_EFFECT_PUSH4_T_L_B_T,
   DLG_STR_EFFECT_PUSH4_T_L_B_B,
   DLG_STR_EFFECT_PUSH4_T_R_L_L,
   DLG_STR_EFFECT_PUSH4_T_R_L_R,
   DLG_STR_EFFECT_PUSH4_T_R_L_T,
   DLG_STR_EFFECT_PUSH4_T_R_L_B,
   DLG_STR_EFFECT_PUSH4_T_R_R_L,
   DLG_STR_EFFECT_PUSH4_T_R_R_R,
   DLG_STR_EFFECT_PUSH4_T_R_R_T,
   DLG_STR_EFFECT_PUSH4_T_R_R_B,
   DLG_STR_EFFECT_PUSH4_T_R_T_L,
   DLG_STR_EFFECT_PUSH4_T_R_T_R,
   DLG_STR_EFFECT_PUSH4_T_R_T_T,
   DLG_STR_EFFECT_PUSH4_T_R_T_B,
   DLG_STR_EFFECT_PUSH4_T_R_B_L,
   DLG_STR_EFFECT_PUSH4_T_R_B_R,
   DLG_STR_EFFECT_PUSH4_T_R_B_T,
   DLG_STR_EFFECT_PUSH4_T_R_B_B,
   DLG_STR_EFFECT_PUSH4_T_T_L_L,
   DLG_STR_EFFECT_PUSH4_T_T_L_R,
   DLG_STR_EFFECT_PUSH4_T_T_L_T,
   DLG_STR_EFFECT_PUSH4_T_T_L_B,
   DLG_STR_EFFECT_PUSH4_T_T_R_L,
   DLG_STR_EFFECT_PUSH4_T_T_R_R,
   DLG_STR_EFFECT_PUSH4_T_T_R_T,
   DLG_STR_EFFECT_PUSH4_T_T_R_B,
   DLG_STR_EFFECT_PUSH4_T_T_T_L,
   DLG_STR_EFFECT_PUSH4_T_T_T_R,
   DLG_STR_EFFECT_PUSH4_T_T_T_T,
   DLG_STR_EFFECT_PUSH4_T_T_T_B,
   DLG_STR_EFFECT_PUSH4_T_T_B_L,
   DLG_STR_EFFECT_PUSH4_T_T_B_R,
   DLG_STR_EFFECT_PUSH4_T_T_B_T,
   DLG_STR_EFFECT_PUSH4_T_T_B_B,
   DLG_STR_EFFECT_PUSH4_T_B_L_L,
   DLG_STR_EFFECT_PUSH4_T_B_L_R,
   DLG_STR_EFFECT_PUSH4_T_B_L_T,
   DLG_STR_EFFECT_PUSH4_T_B_L_B,
   DLG_STR_EFFECT_PUSH4_T_B_R_L,
   DLG_STR_EFFECT_PUSH4_T_B_R_R,
   DLG_STR_EFFECT_PUSH4_T_B_R_T,
   DLG_STR_EFFECT_PUSH4_T_B_R_B,
   DLG_STR_EFFECT_PUSH4_T_B_T_L,
   DLG_STR_EFFECT_PUSH4_T_B_T_R,
   DLG_STR_EFFECT_PUSH4_T_B_T_T,
   DLG_STR_EFFECT_PUSH4_T_B_T_B,
   DLG_STR_EFFECT_PUSH4_T_B_B_L,
   DLG_STR_EFFECT_PUSH4_T_B_B_R,
   DLG_STR_EFFECT_PUSH4_T_B_B_T,
   DLG_STR_EFFECT_PUSH4_T_B_B_B,
   DLG_STR_EFFECT_PUSH4_B_L_L_L,
   DLG_STR_EFFECT_PUSH4_B_L_L_R,
   DLG_STR_EFFECT_PUSH4_B_L_L_T,
   DLG_STR_EFFECT_PUSH4_B_L_L_B,
   DLG_STR_EFFECT_PUSH4_B_L_R_L,
   DLG_STR_EFFECT_PUSH4_B_L_R_R,
   DLG_STR_EFFECT_PUSH4_B_L_R_T,
   DLG_STR_EFFECT_PUSH4_B_L_R_B,
   DLG_STR_EFFECT_PUSH4_B_L_T_L,
   DLG_STR_EFFECT_PUSH4_B_L_T_R,
   DLG_STR_EFFECT_PUSH4_B_L_T_T,
   DLG_STR_EFFECT_PUSH4_B_L_T_B,
   DLG_STR_EFFECT_PUSH4_B_L_B_L,
   DLG_STR_EFFECT_PUSH4_B_L_B_R,
   DLG_STR_EFFECT_PUSH4_B_L_B_T,
   DLG_STR_EFFECT_PUSH4_B_L_B_B,
   DLG_STR_EFFECT_PUSH4_B_R_L_L,
   DLG_STR_EFFECT_PUSH4_B_R_L_R,
   DLG_STR_EFFECT_PUSH4_B_R_L_T,
   DLG_STR_EFFECT_PUSH4_B_R_L_B,
   DLG_STR_EFFECT_PUSH4_B_R_R_L,
   DLG_STR_EFFECT_PUSH4_B_R_R_R,
   DLG_STR_EFFECT_PUSH4_B_R_R_T,
   DLG_STR_EFFECT_PUSH4_B_R_R_B,
   DLG_STR_EFFECT_PUSH4_B_R_T_L,
   DLG_STR_EFFECT_PUSH4_B_R_T_R,
   DLG_STR_EFFECT_PUSH4_B_R_T_T,
   DLG_STR_EFFECT_PUSH4_B_R_T_B,
   DLG_STR_EFFECT_PUSH4_B_R_B_L,
   DLG_STR_EFFECT_PUSH4_B_R_B_R,
   DLG_STR_EFFECT_PUSH4_B_R_B_T,
   DLG_STR_EFFECT_PUSH4_B_R_B_B,
   DLG_STR_EFFECT_PUSH4_B_T_L_L,
   DLG_STR_EFFECT_PUSH4_B_T_L_R,
   DLG_STR_EFFECT_PUSH4_B_T_L_T,
   DLG_STR_EFFECT_PUSH4_B_T_L_B,
   DLG_STR_EFFECT_PUSH4_B_T_R_L,
   DLG_STR_EFFECT_PUSH4_B_T_R_R,
   DLG_STR_EFFECT_PUSH4_B_T_R_T,
   DLG_STR_EFFECT_PUSH4_B_T_R_B,
   DLG_STR_EFFECT_PUSH4_B_T_T_L,
   DLG_STR_EFFECT_PUSH4_B_T_T_R,
   DLG_STR_EFFECT_PUSH4_B_T_T_T,
   DLG_STR_EFFECT_PUSH4_B_T_T_B,
   DLG_STR_EFFECT_PUSH4_B_T_B_L,
   DLG_STR_EFFECT_PUSH4_B_T_B_R,
   DLG_STR_EFFECT_PUSH4_B_T_B_T,
   DLG_STR_EFFECT_PUSH4_B_T_B_B,
   DLG_STR_EFFECT_PUSH4_B_B_L_L,
   DLG_STR_EFFECT_PUSH4_B_B_L_R,
   DLG_STR_EFFECT_PUSH4_B_B_L_T,
   DLG_STR_EFFECT_PUSH4_B_B_L_B,
   DLG_STR_EFFECT_PUSH4_B_B_R_L,
   DLG_STR_EFFECT_PUSH4_B_B_R_R,
   DLG_STR_EFFECT_PUSH4_B_B_R_T,
   DLG_STR_EFFECT_PUSH4_B_B_R_B,
   DLG_STR_EFFECT_PUSH4_B_B_T_L,
   DLG_STR_EFFECT_PUSH4_B_B_T_R,
   DLG_STR_EFFECT_PUSH4_B_B_T_T,
   DLG_STR_EFFECT_PUSH4_B_B_T_B,
   DLG_STR_EFFECT_PUSH4_B_B_B_L,
   DLG_STR_EFFECT_PUSH4_B_B_B_R,
   DLG_STR_EFFECT_PUSH4_B_B_B_T,
   DLG_STR_EFFECT_PUSH4_B_B_B_B,
   DLG_STR_EFFECT_PUSH_END,
};

enum {
   DLG_STR_EFFECT_SLIDE_R_TO_L=DLG_STR_EFFECT_PUSH_END,
   DLG_STR_EFFECT_SLIDE_L_TO_R,
   DLG_STR_EFFECT_SLIDE_B_TO_T,
   DLG_STR_EFFECT_SLIDE_T_TO_B,
   DLG_STR_EFFECT_SLIDE_LT_TO_RB,
   DLG_STR_EFFECT_SLIDE_RT_TO_LB,
   DLG_STR_EFFECT_SLIDE_LB_TO_RT,
   DLG_STR_EFFECT_SLIDE_RB_TO_LT,
   DLG_STR_EFFECT_SLIDE_INTERH_L_TO_R_AND_R_TO_L,
   DLG_STR_EFFECT_SLIDE_INTERV_T_TO_B_AND_B_TO_T,
   DLG_STR_EFFECT_SLIDE2_T_R_TO_L_AND_B_L_TO_R,
   DLG_STR_EFFECT_SLIDE2_T_L_TO_R_AND_B_R_TO_L,
   DLG_STR_EFFECT_SLIDE2_L_B_TO_T_AND_R_T_TO_B,
   DLG_STR_EFFECT_SLIDE2_L_T_TO_B_AND_R_B_TO_T,
   DLG_STR_EFFECT_SLIDE4_L_L_L_L,
   DLG_STR_EFFECT_SLIDE4_L_L_L_R,
   DLG_STR_EFFECT_SLIDE4_L_L_L_T,
   DLG_STR_EFFECT_SLIDE4_L_L_L_B,
   DLG_STR_EFFECT_SLIDE4_L_L_R_L,
   DLG_STR_EFFECT_SLIDE4_L_L_R_R,
   DLG_STR_EFFECT_SLIDE4_L_L_R_T,
   DLG_STR_EFFECT_SLIDE4_L_L_R_B,
   DLG_STR_EFFECT_SLIDE4_L_L_T_L,
   DLG_STR_EFFECT_SLIDE4_L_L_T_R,
   DLG_STR_EFFECT_SLIDE4_L_L_T_T,
   DLG_STR_EFFECT_SLIDE4_L_L_T_B,
   DLG_STR_EFFECT_SLIDE4_L_L_B_L,
   DLG_STR_EFFECT_SLIDE4_L_L_B_R,
   DLG_STR_EFFECT_SLIDE4_L_L_B_T,
   DLG_STR_EFFECT_SLIDE4_L_L_B_B,
   DLG_STR_EFFECT_SLIDE4_L_R_L_L,
   DLG_STR_EFFECT_SLIDE4_L_R_L_R,
   DLG_STR_EFFECT_SLIDE4_L_R_L_T,
   DLG_STR_EFFECT_SLIDE4_L_R_L_B,
   DLG_STR_EFFECT_SLIDE4_L_R_R_L,
   DLG_STR_EFFECT_SLIDE4_L_R_R_R,
   DLG_STR_EFFECT_SLIDE4_L_R_R_T,
   DLG_STR_EFFECT_SLIDE4_L_R_R_B,
   DLG_STR_EFFECT_SLIDE4_L_R_T_L,
   DLG_STR_EFFECT_SLIDE4_L_R_T_R,
   DLG_STR_EFFECT_SLIDE4_L_R_T_T,
   DLG_STR_EFFECT_SLIDE4_L_R_T_B,
   DLG_STR_EFFECT_SLIDE4_L_R_B_L,
   DLG_STR_EFFECT_SLIDE4_L_R_B_R,
   DLG_STR_EFFECT_SLIDE4_L_R_B_T,
   DLG_STR_EFFECT_SLIDE4_L_R_B_B,
   DLG_STR_EFFECT_SLIDE4_L_T_L_L,
   DLG_STR_EFFECT_SLIDE4_L_T_L_R,
   DLG_STR_EFFECT_SLIDE4_L_T_L_T,
   DLG_STR_EFFECT_SLIDE4_L_T_L_B,
   DLG_STR_EFFECT_SLIDE4_L_T_R_L,
   DLG_STR_EFFECT_SLIDE4_L_T_R_R,
   DLG_STR_EFFECT_SLIDE4_L_T_R_T,
   DLG_STR_EFFECT_SLIDE4_L_T_R_B,
   DLG_STR_EFFECT_SLIDE4_L_T_T_L,
   DLG_STR_EFFECT_SLIDE4_L_T_T_R,
   DLG_STR_EFFECT_SLIDE4_L_T_T_T,
   DLG_STR_EFFECT_SLIDE4_L_T_T_B,
   DLG_STR_EFFECT_SLIDE4_L_T_B_L,
   DLG_STR_EFFECT_SLIDE4_L_T_B_R,
   DLG_STR_EFFECT_SLIDE4_L_T_B_T,
   DLG_STR_EFFECT_SLIDE4_L_T_B_B,
   DLG_STR_EFFECT_SLIDE4_L_B_L_L,
   DLG_STR_EFFECT_SLIDE4_L_B_L_R,
   DLG_STR_EFFECT_SLIDE4_L_B_L_T,
   DLG_STR_EFFECT_SLIDE4_L_B_L_B,
   DLG_STR_EFFECT_SLIDE4_L_B_R_L,
   DLG_STR_EFFECT_SLIDE4_L_B_R_R,
   DLG_STR_EFFECT_SLIDE4_L_B_R_T,
   DLG_STR_EFFECT_SLIDE4_L_B_R_B,
   DLG_STR_EFFECT_SLIDE4_L_B_T_L,
   DLG_STR_EFFECT_SLIDE4_L_B_T_R,
   DLG_STR_EFFECT_SLIDE4_L_B_T_T,
   DLG_STR_EFFECT_SLIDE4_L_B_T_B,
   DLG_STR_EFFECT_SLIDE4_L_B_B_L,
   DLG_STR_EFFECT_SLIDE4_L_B_B_R,
   DLG_STR_EFFECT_SLIDE4_L_B_B_T,
   DLG_STR_EFFECT_SLIDE4_L_B_B_B,
   DLG_STR_EFFECT_SLIDE4_R_L_L_L,
   DLG_STR_EFFECT_SLIDE4_R_L_L_R,
   DLG_STR_EFFECT_SLIDE4_R_L_L_T,
   DLG_STR_EFFECT_SLIDE4_R_L_L_B,
   DLG_STR_EFFECT_SLIDE4_R_L_R_L,
   DLG_STR_EFFECT_SLIDE4_R_L_R_R,
   DLG_STR_EFFECT_SLIDE4_R_L_R_T,
   DLG_STR_EFFECT_SLIDE4_R_L_R_B,
   DLG_STR_EFFECT_SLIDE4_R_L_T_L,
   DLG_STR_EFFECT_SLIDE4_R_L_T_R,
   DLG_STR_EFFECT_SLIDE4_R_L_T_T,
   DLG_STR_EFFECT_SLIDE4_R_L_T_B,
   DLG_STR_EFFECT_SLIDE4_R_L_B_L,
   DLG_STR_EFFECT_SLIDE4_R_L_B_R,
   DLG_STR_EFFECT_SLIDE4_R_L_B_T,
   DLG_STR_EFFECT_SLIDE4_R_L_B_B,
   DLG_STR_EFFECT_SLIDE4_R_R_L_L,
   DLG_STR_EFFECT_SLIDE4_R_R_L_R,
   DLG_STR_EFFECT_SLIDE4_R_R_L_T,
   DLG_STR_EFFECT_SLIDE4_R_R_L_B,
   DLG_STR_EFFECT_SLIDE4_R_R_R_L,
   DLG_STR_EFFECT_SLIDE4_R_R_R_R,
   DLG_STR_EFFECT_SLIDE4_R_R_R_T,
   DLG_STR_EFFECT_SLIDE4_R_R_R_B,
   DLG_STR_EFFECT_SLIDE4_R_R_T_L,
   DLG_STR_EFFECT_SLIDE4_R_R_T_R,
   DLG_STR_EFFECT_SLIDE4_R_R_T_T,
   DLG_STR_EFFECT_SLIDE4_R_R_T_B,
   DLG_STR_EFFECT_SLIDE4_R_R_B_L,
   DLG_STR_EFFECT_SLIDE4_R_R_B_R,
   DLG_STR_EFFECT_SLIDE4_R_R_B_T,
   DLG_STR_EFFECT_SLIDE4_R_R_B_B,
   DLG_STR_EFFECT_SLIDE4_R_T_L_L,
   DLG_STR_EFFECT_SLIDE4_R_T_L_R,
   DLG_STR_EFFECT_SLIDE4_R_T_L_T,
   DLG_STR_EFFECT_SLIDE4_R_T_L_B,
   DLG_STR_EFFECT_SLIDE4_R_T_R_L,
   DLG_STR_EFFECT_SLIDE4_R_T_R_R,
   DLG_STR_EFFECT_SLIDE4_R_T_R_T,
   DLG_STR_EFFECT_SLIDE4_R_T_R_B,
   DLG_STR_EFFECT_SLIDE4_R_T_T_L,
   DLG_STR_EFFECT_SLIDE4_R_T_T_R,
   DLG_STR_EFFECT_SLIDE4_R_T_T_T,
   DLG_STR_EFFECT_SLIDE4_R_T_T_B,
   DLG_STR_EFFECT_SLIDE4_R_T_B_L,
   DLG_STR_EFFECT_SLIDE4_R_T_B_R,
   DLG_STR_EFFECT_SLIDE4_R_T_B_T,
   DLG_STR_EFFECT_SLIDE4_R_T_B_B,
   DLG_STR_EFFECT_SLIDE4_R_B_L_L,
   DLG_STR_EFFECT_SLIDE4_R_B_L_R,
   DLG_STR_EFFECT_SLIDE4_R_B_L_T,
   DLG_STR_EFFECT_SLIDE4_R_B_L_B,
   DLG_STR_EFFECT_SLIDE4_R_B_R_L,
   DLG_STR_EFFECT_SLIDE4_R_B_R_R,
   DLG_STR_EFFECT_SLIDE4_R_B_R_T,
   DLG_STR_EFFECT_SLIDE4_R_B_R_B,
   DLG_STR_EFFECT_SLIDE4_R_B_T_L,
   DLG_STR_EFFECT_SLIDE4_R_B_T_R,
   DLG_STR_EFFECT_SLIDE4_R_B_T_T,
   DLG_STR_EFFECT_SLIDE4_R_B_T_B,
   DLG_STR_EFFECT_SLIDE4_R_B_B_L,
   DLG_STR_EFFECT_SLIDE4_R_B_B_R,
   DLG_STR_EFFECT_SLIDE4_R_B_B_T,
   DLG_STR_EFFECT_SLIDE4_R_B_B_B,
   DLG_STR_EFFECT_SLIDE4_T_L_L_L,
   DLG_STR_EFFECT_SLIDE4_T_L_L_R,
   DLG_STR_EFFECT_SLIDE4_T_L_L_T,
   DLG_STR_EFFECT_SLIDE4_T_L_L_B,
   DLG_STR_EFFECT_SLIDE4_T_L_R_L,
   DLG_STR_EFFECT_SLIDE4_T_L_R_R,
   DLG_STR_EFFECT_SLIDE4_T_L_R_T,
   DLG_STR_EFFECT_SLIDE4_T_L_R_B,
   DLG_STR_EFFECT_SLIDE4_T_L_T_L,
   DLG_STR_EFFECT_SLIDE4_T_L_T_R,
   DLG_STR_EFFECT_SLIDE4_T_L_T_T,
   DLG_STR_EFFECT_SLIDE4_T_L_T_B,
   DLG_STR_EFFECT_SLIDE4_T_L_B_L,
   DLG_STR_EFFECT_SLIDE4_T_L_B_R,
   DLG_STR_EFFECT_SLIDE4_T_L_B_T,
   DLG_STR_EFFECT_SLIDE4_T_L_B_B,
   DLG_STR_EFFECT_SLIDE4_T_R_L_L,
   DLG_STR_EFFECT_SLIDE4_T_R_L_R,
   DLG_STR_EFFECT_SLIDE4_T_R_L_T,
   DLG_STR_EFFECT_SLIDE4_T_R_L_B,
   DLG_STR_EFFECT_SLIDE4_T_R_R_L,
   DLG_STR_EFFECT_SLIDE4_T_R_R_R,
   DLG_STR_EFFECT_SLIDE4_T_R_R_T,
   DLG_STR_EFFECT_SLIDE4_T_R_R_B,
   DLG_STR_EFFECT_SLIDE4_T_R_T_L,
   DLG_STR_EFFECT_SLIDE4_T_R_T_R,
   DLG_STR_EFFECT_SLIDE4_T_R_T_T,
   DLG_STR_EFFECT_SLIDE4_T_R_T_B,
   DLG_STR_EFFECT_SLIDE4_T_R_B_L,
   DLG_STR_EFFECT_SLIDE4_T_R_B_R,
   DLG_STR_EFFECT_SLIDE4_T_R_B_T,
   DLG_STR_EFFECT_SLIDE4_T_R_B_B,
   DLG_STR_EFFECT_SLIDE4_T_T_L_L,
   DLG_STR_EFFECT_SLIDE4_T_T_L_R,
   DLG_STR_EFFECT_SLIDE4_T_T_L_T,
   DLG_STR_EFFECT_SLIDE4_T_T_L_B,
   DLG_STR_EFFECT_SLIDE4_T_T_R_L,
   DLG_STR_EFFECT_SLIDE4_T_T_R_R,
   DLG_STR_EFFECT_SLIDE4_T_T_R_T,
   DLG_STR_EFFECT_SLIDE4_T_T_R_B,
   DLG_STR_EFFECT_SLIDE4_T_T_T_L,
   DLG_STR_EFFECT_SLIDE4_T_T_T_R,
   DLG_STR_EFFECT_SLIDE4_T_T_T_T,
   DLG_STR_EFFECT_SLIDE4_T_T_T_B,
   DLG_STR_EFFECT_SLIDE4_T_T_B_L,
   DLG_STR_EFFECT_SLIDE4_T_T_B_R,
   DLG_STR_EFFECT_SLIDE4_T_T_B_T,
   DLG_STR_EFFECT_SLIDE4_T_T_B_B,
   DLG_STR_EFFECT_SLIDE4_T_B_L_L,
   DLG_STR_EFFECT_SLIDE4_T_B_L_R,
   DLG_STR_EFFECT_SLIDE4_T_B_L_T,
   DLG_STR_EFFECT_SLIDE4_T_B_L_B,
   DLG_STR_EFFECT_SLIDE4_T_B_R_L,
   DLG_STR_EFFECT_SLIDE4_T_B_R_R,
   DLG_STR_EFFECT_SLIDE4_T_B_R_T,
   DLG_STR_EFFECT_SLIDE4_T_B_R_B,
   DLG_STR_EFFECT_SLIDE4_T_B_T_L,
   DLG_STR_EFFECT_SLIDE4_T_B_T_R,
   DLG_STR_EFFECT_SLIDE4_T_B_T_T,
   DLG_STR_EFFECT_SLIDE4_T_B_T_B,
   DLG_STR_EFFECT_SLIDE4_T_B_B_L,
   DLG_STR_EFFECT_SLIDE4_T_B_B_R,
   DLG_STR_EFFECT_SLIDE4_T_B_B_T,
   DLG_STR_EFFECT_SLIDE4_T_B_B_B,
   DLG_STR_EFFECT_SLIDE4_B_L_L_L,
   DLG_STR_EFFECT_SLIDE4_B_L_L_R,
   DLG_STR_EFFECT_SLIDE4_B_L_L_T,
   DLG_STR_EFFECT_SLIDE4_B_L_L_B,
   DLG_STR_EFFECT_SLIDE4_B_L_R_L,
   DLG_STR_EFFECT_SLIDE4_B_L_R_R,
   DLG_STR_EFFECT_SLIDE4_B_L_R_T,
   DLG_STR_EFFECT_SLIDE4_B_L_R_B,
   DLG_STR_EFFECT_SLIDE4_B_L_T_L,
   DLG_STR_EFFECT_SLIDE4_B_L_T_R,
   DLG_STR_EFFECT_SLIDE4_B_L_T_T,
   DLG_STR_EFFECT_SLIDE4_B_L_T_B,
   DLG_STR_EFFECT_SLIDE4_B_L_B_L,
   DLG_STR_EFFECT_SLIDE4_B_L_B_R,
   DLG_STR_EFFECT_SLIDE4_B_L_B_T,
   DLG_STR_EFFECT_SLIDE4_B_L_B_B,
   DLG_STR_EFFECT_SLIDE4_B_R_L_L,
   DLG_STR_EFFECT_SLIDE4_B_R_L_R,
   DLG_STR_EFFECT_SLIDE4_B_R_L_T,
   DLG_STR_EFFECT_SLIDE4_B_R_L_B,
   DLG_STR_EFFECT_SLIDE4_B_R_R_L,
   DLG_STR_EFFECT_SLIDE4_B_R_R_R,
   DLG_STR_EFFECT_SLIDE4_B_R_R_T,
   DLG_STR_EFFECT_SLIDE4_B_R_R_B,
   DLG_STR_EFFECT_SLIDE4_B_R_T_L,
   DLG_STR_EFFECT_SLIDE4_B_R_T_R,
   DLG_STR_EFFECT_SLIDE4_B_R_T_T,
   DLG_STR_EFFECT_SLIDE4_B_R_T_B,
   DLG_STR_EFFECT_SLIDE4_B_R_B_L,
   DLG_STR_EFFECT_SLIDE4_B_R_B_R,
   DLG_STR_EFFECT_SLIDE4_B_R_B_T,
   DLG_STR_EFFECT_SLIDE4_B_R_B_B,
   DLG_STR_EFFECT_SLIDE4_B_T_L_L,
   DLG_STR_EFFECT_SLIDE4_B_T_L_R,
   DLG_STR_EFFECT_SLIDE4_B_T_L_T,
   DLG_STR_EFFECT_SLIDE4_B_T_L_B,
   DLG_STR_EFFECT_SLIDE4_B_T_R_L,
   DLG_STR_EFFECT_SLIDE4_B_T_R_R,
   DLG_STR_EFFECT_SLIDE4_B_T_R_T,
   DLG_STR_EFFECT_SLIDE4_B_T_R_B,
   DLG_STR_EFFECT_SLIDE4_B_T_T_L,
   DLG_STR_EFFECT_SLIDE4_B_T_T_R,
   DLG_STR_EFFECT_SLIDE4_B_T_T_T,
   DLG_STR_EFFECT_SLIDE4_B_T_T_B,
   DLG_STR_EFFECT_SLIDE4_B_T_B_L,
   DLG_STR_EFFECT_SLIDE4_B_T_B_R,
   DLG_STR_EFFECT_SLIDE4_B_T_B_T,
   DLG_STR_EFFECT_SLIDE4_B_T_B_B,
   DLG_STR_EFFECT_SLIDE4_B_B_L_L,
   DLG_STR_EFFECT_SLIDE4_B_B_L_R,
   DLG_STR_EFFECT_SLIDE4_B_B_L_T,
   DLG_STR_EFFECT_SLIDE4_B_B_L_B,
   DLG_STR_EFFECT_SLIDE4_B_B_R_L,
   DLG_STR_EFFECT_SLIDE4_B_B_R_R,
   DLG_STR_EFFECT_SLIDE4_B_B_R_T,
   DLG_STR_EFFECT_SLIDE4_B_B_R_B,
   DLG_STR_EFFECT_SLIDE4_B_B_T_L,
   DLG_STR_EFFECT_SLIDE4_B_B_T_R,
   DLG_STR_EFFECT_SLIDE4_B_B_T_T,
   DLG_STR_EFFECT_SLIDE4_B_B_T_B,
   DLG_STR_EFFECT_SLIDE4_B_B_B_L,
   DLG_STR_EFFECT_SLIDE4_B_B_B_R,
   DLG_STR_EFFECT_SLIDE4_B_B_B_T,
   DLG_STR_EFFECT_SLIDE4_B_B_B_B,
   DLG_STR_EFFECT_SLIDE4_LT_LT_LT_LT,
   DLG_STR_EFFECT_SLIDE4_LT_LT_LT_LB,
   DLG_STR_EFFECT_SLIDE4_LT_LT_LT_RT,
   DLG_STR_EFFECT_SLIDE4_LT_LT_LT_RB,
   DLG_STR_EFFECT_SLIDE4_LT_LT_LB_LT,
   DLG_STR_EFFECT_SLIDE4_LT_LT_LB_LB,
   DLG_STR_EFFECT_SLIDE4_LT_LT_LB_RT,
   DLG_STR_EFFECT_SLIDE4_LT_LT_LB_RB,
   DLG_STR_EFFECT_SLIDE4_LT_LT_RT_LT,
   DLG_STR_EFFECT_SLIDE4_LT_LT_RT_LB,
   DLG_STR_EFFECT_SLIDE4_LT_LT_RT_RT,
   DLG_STR_EFFECT_SLIDE4_LT_LT_RT_RB,
   DLG_STR_EFFECT_SLIDE4_LT_LT_RB_LT,
   DLG_STR_EFFECT_SLIDE4_LT_LT_RB_LB,
   DLG_STR_EFFECT_SLIDE4_LT_LT_RB_RT,
   DLG_STR_EFFECT_SLIDE4_LT_LT_RB_RB,
   DLG_STR_EFFECT_SLIDE4_LT_LB_LT_LT,
   DLG_STR_EFFECT_SLIDE4_LT_LB_LT_LB,
   DLG_STR_EFFECT_SLIDE4_LT_LB_LT_RT,
   DLG_STR_EFFECT_SLIDE4_LT_LB_LT_RB,
   DLG_STR_EFFECT_SLIDE4_LT_LB_LB_LT,
   DLG_STR_EFFECT_SLIDE4_LT_LB_LB_LB,
   DLG_STR_EFFECT_SLIDE4_LT_LB_LB_RT,
   DLG_STR_EFFECT_SLIDE4_LT_LB_LB_RB,
   DLG_STR_EFFECT_SLIDE4_LT_LB_RT_LT,
   DLG_STR_EFFECT_SLIDE4_LT_LB_RT_LB,
   DLG_STR_EFFECT_SLIDE4_LT_LB_RT_RT,
   DLG_STR_EFFECT_SLIDE4_LT_LB_RT_RB,
   DLG_STR_EFFECT_SLIDE4_LT_LB_RB_LT,
   DLG_STR_EFFECT_SLIDE4_LT_LB_RB_LB,
   DLG_STR_EFFECT_SLIDE4_LT_LB_RB_RT,
   DLG_STR_EFFECT_SLIDE4_LT_LB_RB_RB,
   DLG_STR_EFFECT_SLIDE4_LT_RT_LT_LT,
   DLG_STR_EFFECT_SLIDE4_LT_RT_LT_LB,
   DLG_STR_EFFECT_SLIDE4_LT_RT_LT_RT,
   DLG_STR_EFFECT_SLIDE4_LT_RT_LT_RB,
   DLG_STR_EFFECT_SLIDE4_LT_RT_LB_LT,
   DLG_STR_EFFECT_SLIDE4_LT_RT_LB_LB,
   DLG_STR_EFFECT_SLIDE4_LT_RT_LB_RT,
   DLG_STR_EFFECT_SLIDE4_LT_RT_LB_RB,
   DLG_STR_EFFECT_SLIDE4_LT_RT_RT_LT,
   DLG_STR_EFFECT_SLIDE4_LT_RT_RT_LB,
   DLG_STR_EFFECT_SLIDE4_LT_RT_RT_RT,
   DLG_STR_EFFECT_SLIDE4_LT_RT_RT_RB,
   DLG_STR_EFFECT_SLIDE4_LT_RT_RB_LT,
   DLG_STR_EFFECT_SLIDE4_LT_RT_RB_LB,
   DLG_STR_EFFECT_SLIDE4_LT_RT_RB_RT,
   DLG_STR_EFFECT_SLIDE4_LT_RT_RB_RB,
   DLG_STR_EFFECT_SLIDE4_LT_RB_LT_LT,
   DLG_STR_EFFECT_SLIDE4_LT_RB_LT_LB,
   DLG_STR_EFFECT_SLIDE4_LT_RB_LT_RT,
   DLG_STR_EFFECT_SLIDE4_LT_RB_LT_RB,
   DLG_STR_EFFECT_SLIDE4_LT_RB_LB_LT,
   DLG_STR_EFFECT_SLIDE4_LT_RB_LB_LB,
   DLG_STR_EFFECT_SLIDE4_LT_RB_LB_RT,
   DLG_STR_EFFECT_SLIDE4_LT_RB_LB_RB,
   DLG_STR_EFFECT_SLIDE4_LT_RB_RT_LT,
   DLG_STR_EFFECT_SLIDE4_LT_RB_RT_LB,
   DLG_STR_EFFECT_SLIDE4_LT_RB_RT_RT,
   DLG_STR_EFFECT_SLIDE4_LT_RB_RT_RB,
   DLG_STR_EFFECT_SLIDE4_LT_RB_RB_LT,
   DLG_STR_EFFECT_SLIDE4_LT_RB_RB_LB,
   DLG_STR_EFFECT_SLIDE4_LT_RB_RB_RT,
   DLG_STR_EFFECT_SLIDE4_LT_RB_RB_RB,
   DLG_STR_EFFECT_SLIDE4_LB_LT_LT_LT,
   DLG_STR_EFFECT_SLIDE4_LB_LT_LT_LB,
   DLG_STR_EFFECT_SLIDE4_LB_LT_LT_RT,
   DLG_STR_EFFECT_SLIDE4_LB_LT_LT_RB,
   DLG_STR_EFFECT_SLIDE4_LB_LT_LB_LT,
   DLG_STR_EFFECT_SLIDE4_LB_LT_LB_LB,
   DLG_STR_EFFECT_SLIDE4_LB_LT_LB_RT,
   DLG_STR_EFFECT_SLIDE4_LB_LT_LB_RB,
   DLG_STR_EFFECT_SLIDE4_LB_LT_RT_LT,
   DLG_STR_EFFECT_SLIDE4_LB_LT_RT_LB,
   DLG_STR_EFFECT_SLIDE4_LB_LT_RT_RT,
   DLG_STR_EFFECT_SLIDE4_LB_LT_RT_RB,
   DLG_STR_EFFECT_SLIDE4_LB_LT_RB_LT,
   DLG_STR_EFFECT_SLIDE4_LB_LT_RB_LB,
   DLG_STR_EFFECT_SLIDE4_LB_LT_RB_RT,
   DLG_STR_EFFECT_SLIDE4_LB_LT_RB_RB,
   DLG_STR_EFFECT_SLIDE4_LB_LB_LT_LT,
   DLG_STR_EFFECT_SLIDE4_LB_LB_LT_LB,
   DLG_STR_EFFECT_SLIDE4_LB_LB_LT_RT,
   DLG_STR_EFFECT_SLIDE4_LB_LB_LT_RB,
   DLG_STR_EFFECT_SLIDE4_LB_LB_LB_LT,
   DLG_STR_EFFECT_SLIDE4_LB_LB_LB_LB,
   DLG_STR_EFFECT_SLIDE4_LB_LB_LB_RT,
   DLG_STR_EFFECT_SLIDE4_LB_LB_LB_RB,
   DLG_STR_EFFECT_SLIDE4_LB_LB_RT_LT,
   DLG_STR_EFFECT_SLIDE4_LB_LB_RT_LB,
   DLG_STR_EFFECT_SLIDE4_LB_LB_RT_RT,
   DLG_STR_EFFECT_SLIDE4_LB_LB_RT_RB,
   DLG_STR_EFFECT_SLIDE4_LB_LB_RB_LT,
   DLG_STR_EFFECT_SLIDE4_LB_LB_RB_LB,
   DLG_STR_EFFECT_SLIDE4_LB_LB_RB_RT,
   DLG_STR_EFFECT_SLIDE4_LB_LB_RB_RB,
   DLG_STR_EFFECT_SLIDE4_LB_RT_LT_LT,
   DLG_STR_EFFECT_SLIDE4_LB_RT_LT_LB,
   DLG_STR_EFFECT_SLIDE4_LB_RT_LT_RT,
   DLG_STR_EFFECT_SLIDE4_LB_RT_LT_RB,
   DLG_STR_EFFECT_SLIDE4_LB_RT_LB_LT,
   DLG_STR_EFFECT_SLIDE4_LB_RT_LB_LB,
   DLG_STR_EFFECT_SLIDE4_LB_RT_LB_RT,
   DLG_STR_EFFECT_SLIDE4_LB_RT_LB_RB,
   DLG_STR_EFFECT_SLIDE4_LB_RT_RT_LT,
   DLG_STR_EFFECT_SLIDE4_LB_RT_RT_LB,
   DLG_STR_EFFECT_SLIDE4_LB_RT_RT_RT,
   DLG_STR_EFFECT_SLIDE4_LB_RT_RT_RB,
   DLG_STR_EFFECT_SLIDE4_LB_RT_RB_LT,
   DLG_STR_EFFECT_SLIDE4_LB_RT_RB_LB,
   DLG_STR_EFFECT_SLIDE4_LB_RT_RB_RT,
   DLG_STR_EFFECT_SLIDE4_LB_RT_RB_RB,
   DLG_STR_EFFECT_SLIDE4_LB_RB_LT_LT,
   DLG_STR_EFFECT_SLIDE4_LB_RB_LT_LB,
   DLG_STR_EFFECT_SLIDE4_LB_RB_LT_RT,
   DLG_STR_EFFECT_SLIDE4_LB_RB_LT_RB,
   DLG_STR_EFFECT_SLIDE4_LB_RB_LB_LT,
   DLG_STR_EFFECT_SLIDE4_LB_RB_LB_LB,
   DLG_STR_EFFECT_SLIDE4_LB_RB_LB_RT,
   DLG_STR_EFFECT_SLIDE4_LB_RB_LB_RB,
   DLG_STR_EFFECT_SLIDE4_LB_RB_RT_LT,
   DLG_STR_EFFECT_SLIDE4_LB_RB_RT_LB,
   DLG_STR_EFFECT_SLIDE4_LB_RB_RT_RT,
   DLG_STR_EFFECT_SLIDE4_LB_RB_RT_RB,
   DLG_STR_EFFECT_SLIDE4_LB_RB_RB_LT,
   DLG_STR_EFFECT_SLIDE4_LB_RB_RB_LB,
   DLG_STR_EFFECT_SLIDE4_LB_RB_RB_RT,
   DLG_STR_EFFECT_SLIDE4_LB_RB_RB_RB,
   DLG_STR_EFFECT_SLIDE4_RT_LT_LT_LT,
   DLG_STR_EFFECT_SLIDE4_RT_LT_LT_LB,
   DLG_STR_EFFECT_SLIDE4_RT_LT_LT_RT,
   DLG_STR_EFFECT_SLIDE4_RT_LT_LT_RB,
   DLG_STR_EFFECT_SLIDE4_RT_LT_LB_LT,
   DLG_STR_EFFECT_SLIDE4_RT_LT_LB_LB,
   DLG_STR_EFFECT_SLIDE4_RT_LT_LB_RT,
   DLG_STR_EFFECT_SLIDE4_RT_LT_LB_RB,
   DLG_STR_EFFECT_SLIDE4_RT_LT_RT_LT,
   DLG_STR_EFFECT_SLIDE4_RT_LT_RT_LB,
   DLG_STR_EFFECT_SLIDE4_RT_LT_RT_RT,
   DLG_STR_EFFECT_SLIDE4_RT_LT_RT_RB,
   DLG_STR_EFFECT_SLIDE4_RT_LT_RB_LT,
   DLG_STR_EFFECT_SLIDE4_RT_LT_RB_LB,
   DLG_STR_EFFECT_SLIDE4_RT_LT_RB_RT,
   DLG_STR_EFFECT_SLIDE4_RT_LT_RB_RB,
   DLG_STR_EFFECT_SLIDE4_RT_LB_LT_LT,
   DLG_STR_EFFECT_SLIDE4_RT_LB_LT_LB,
   DLG_STR_EFFECT_SLIDE4_RT_LB_LT_RT,
   DLG_STR_EFFECT_SLIDE4_RT_LB_LT_RB,
   DLG_STR_EFFECT_SLIDE4_RT_LB_LB_LT,
   DLG_STR_EFFECT_SLIDE4_RT_LB_LB_LB,
   DLG_STR_EFFECT_SLIDE4_RT_LB_LB_RT,
   DLG_STR_EFFECT_SLIDE4_RT_LB_LB_RB,
   DLG_STR_EFFECT_SLIDE4_RT_LB_RT_LT,
   DLG_STR_EFFECT_SLIDE4_RT_LB_RT_LB,
   DLG_STR_EFFECT_SLIDE4_RT_LB_RT_RT,
   DLG_STR_EFFECT_SLIDE4_RT_LB_RT_RB,
   DLG_STR_EFFECT_SLIDE4_RT_LB_RB_LT,
   DLG_STR_EFFECT_SLIDE4_RT_LB_RB_LB,
   DLG_STR_EFFECT_SLIDE4_RT_LB_RB_RT,
   DLG_STR_EFFECT_SLIDE4_RT_LB_RB_RB,
   DLG_STR_EFFECT_SLIDE4_RT_RT_LT_LT,
   DLG_STR_EFFECT_SLIDE4_RT_RT_LT_LB,
   DLG_STR_EFFECT_SLIDE4_RT_RT_LT_RT,
   DLG_STR_EFFECT_SLIDE4_RT_RT_LT_RB,
   DLG_STR_EFFECT_SLIDE4_RT_RT_LB_LT,
   DLG_STR_EFFECT_SLIDE4_RT_RT_LB_LB,
   DLG_STR_EFFECT_SLIDE4_RT_RT_LB_RT,
   DLG_STR_EFFECT_SLIDE4_RT_RT_LB_RB,
   DLG_STR_EFFECT_SLIDE4_RT_RT_RT_LT,
   DLG_STR_EFFECT_SLIDE4_RT_RT_RT_LB,
   DLG_STR_EFFECT_SLIDE4_RT_RT_RT_RT,
   DLG_STR_EFFECT_SLIDE4_RT_RT_RT_RB,
   DLG_STR_EFFECT_SLIDE4_RT_RT_RB_LT,
   DLG_STR_EFFECT_SLIDE4_RT_RT_RB_LB,
   DLG_STR_EFFECT_SLIDE4_RT_RT_RB_RT,
   DLG_STR_EFFECT_SLIDE4_RT_RT_RB_RB,
   DLG_STR_EFFECT_SLIDE4_RT_RB_LT_LT,
   DLG_STR_EFFECT_SLIDE4_RT_RB_LT_LB,
   DLG_STR_EFFECT_SLIDE4_RT_RB_LT_RT,
   DLG_STR_EFFECT_SLIDE4_RT_RB_LT_RB,
   DLG_STR_EFFECT_SLIDE4_RT_RB_LB_LT,
   DLG_STR_EFFECT_SLIDE4_RT_RB_LB_LB,
   DLG_STR_EFFECT_SLIDE4_RT_RB_LB_RT,
   DLG_STR_EFFECT_SLIDE4_RT_RB_LB_RB,
   DLG_STR_EFFECT_SLIDE4_RT_RB_RT_LT,
   DLG_STR_EFFECT_SLIDE4_RT_RB_RT_LB,
   DLG_STR_EFFECT_SLIDE4_RT_RB_RT_RT,
   DLG_STR_EFFECT_SLIDE4_RT_RB_RT_RB,
   DLG_STR_EFFECT_SLIDE4_RT_RB_RB_LT,
   DLG_STR_EFFECT_SLIDE4_RT_RB_RB_LB,
   DLG_STR_EFFECT_SLIDE4_RT_RB_RB_RT,
   DLG_STR_EFFECT_SLIDE4_RT_RB_RB_RB,
   DLG_STR_EFFECT_SLIDE4_RB_LT_LT_LT,
   DLG_STR_EFFECT_SLIDE4_RB_LT_LT_LB,
   DLG_STR_EFFECT_SLIDE4_RB_LT_LT_RT,
   DLG_STR_EFFECT_SLIDE4_RB_LT_LT_RB,
   DLG_STR_EFFECT_SLIDE4_RB_LT_LB_LT,
   DLG_STR_EFFECT_SLIDE4_RB_LT_LB_LB,
   DLG_STR_EFFECT_SLIDE4_RB_LT_LB_RT,
   DLG_STR_EFFECT_SLIDE4_RB_LT_LB_RB,
   DLG_STR_EFFECT_SLIDE4_RB_LT_RT_LT,
   DLG_STR_EFFECT_SLIDE4_RB_LT_RT_LB,
   DLG_STR_EFFECT_SLIDE4_RB_LT_RT_RT,
   DLG_STR_EFFECT_SLIDE4_RB_LT_RT_RB,
   DLG_STR_EFFECT_SLIDE4_RB_LT_RB_LT,
   DLG_STR_EFFECT_SLIDE4_RB_LT_RB_LB,
   DLG_STR_EFFECT_SLIDE4_RB_LT_RB_RT,
   DLG_STR_EFFECT_SLIDE4_RB_LT_RB_RB,
   DLG_STR_EFFECT_SLIDE4_RB_LB_LT_LT,
   DLG_STR_EFFECT_SLIDE4_RB_LB_LT_LB,
   DLG_STR_EFFECT_SLIDE4_RB_LB_LT_RT,
   DLG_STR_EFFECT_SLIDE4_RB_LB_LT_RB,
   DLG_STR_EFFECT_SLIDE4_RB_LB_LB_LT,
   DLG_STR_EFFECT_SLIDE4_RB_LB_LB_LB,
   DLG_STR_EFFECT_SLIDE4_RB_LB_LB_RT,
   DLG_STR_EFFECT_SLIDE4_RB_LB_LB_RB,
   DLG_STR_EFFECT_SLIDE4_RB_LB_RT_LT,
   DLG_STR_EFFECT_SLIDE4_RB_LB_RT_LB,
   DLG_STR_EFFECT_SLIDE4_RB_LB_RT_RT,
   DLG_STR_EFFECT_SLIDE4_RB_LB_RT_RB,
   DLG_STR_EFFECT_SLIDE4_RB_LB_RB_LT,
   DLG_STR_EFFECT_SLIDE4_RB_LB_RB_LB,
   DLG_STR_EFFECT_SLIDE4_RB_LB_RB_RT,
   DLG_STR_EFFECT_SLIDE4_RB_LB_RB_RB,
   DLG_STR_EFFECT_SLIDE4_RB_RT_LT_LT,
   DLG_STR_EFFECT_SLIDE4_RB_RT_LT_LB,
   DLG_STR_EFFECT_SLIDE4_RB_RT_LT_RT,
   DLG_STR_EFFECT_SLIDE4_RB_RT_LT_RB,
   DLG_STR_EFFECT_SLIDE4_RB_RT_LB_LT,
   DLG_STR_EFFECT_SLIDE4_RB_RT_LB_LB,
   DLG_STR_EFFECT_SLIDE4_RB_RT_LB_RT,
   DLG_STR_EFFECT_SLIDE4_RB_RT_LB_RB,
   DLG_STR_EFFECT_SLIDE4_RB_RT_RT_LT,
   DLG_STR_EFFECT_SLIDE4_RB_RT_RT_LB,
   DLG_STR_EFFECT_SLIDE4_RB_RT_RT_RT,
   DLG_STR_EFFECT_SLIDE4_RB_RT_RT_RB,
   DLG_STR_EFFECT_SLIDE4_RB_RT_RB_LT,
   DLG_STR_EFFECT_SLIDE4_RB_RT_RB_LB,
   DLG_STR_EFFECT_SLIDE4_RB_RT_RB_RT,
   DLG_STR_EFFECT_SLIDE4_RB_RT_RB_RB,
   DLG_STR_EFFECT_SLIDE4_RB_RB_LT_LT,
   DLG_STR_EFFECT_SLIDE4_RB_RB_LT_LB,
   DLG_STR_EFFECT_SLIDE4_RB_RB_LT_RT,
   DLG_STR_EFFECT_SLIDE4_RB_RB_LT_RB,
   DLG_STR_EFFECT_SLIDE4_RB_RB_LB_LT,
   DLG_STR_EFFECT_SLIDE4_RB_RB_LB_LB,
   DLG_STR_EFFECT_SLIDE4_RB_RB_LB_RT,
   DLG_STR_EFFECT_SLIDE4_RB_RB_LB_RB,
   DLG_STR_EFFECT_SLIDE4_RB_RB_RT_LT,
   DLG_STR_EFFECT_SLIDE4_RB_RB_RT_LB,
   DLG_STR_EFFECT_SLIDE4_RB_RB_RT_RT,
   DLG_STR_EFFECT_SLIDE4_RB_RB_RT_RB,
   DLG_STR_EFFECT_SLIDE4_RB_RB_RB_LT,
   DLG_STR_EFFECT_SLIDE4_RB_RB_RB_LB,
   DLG_STR_EFFECT_SLIDE4_RB_RB_RB_RT,
   DLG_STR_EFFECT_SLIDE4_RB_RB_RB_RB,
   DLG_STR_EFFECT_SLIDE_END,
};

enum {
   DLG_STR_EFFECT_ROLL_L_TO_R=DLG_STR_EFFECT_SLIDE_END,
   DLG_STR_EFFECT_ROLL_R_TO_L,
   DLG_STR_EFFECT_ROLL_T_TO_B,
   DLG_STR_EFFECT_ROLL_B_TO_T,
   DLG_STR_EFFECT_ROLL2_T_R_TO_L_AND_B_L_TO_R,
   DLG_STR_EFFECT_ROLL2_T_L_TO_R_AND_B_R_TO_L,
   DLG_STR_EFFECT_ROLL2_L_B_TO_T_AND_R_T_TO_B,
   DLG_STR_EFFECT_ROLL2_L_T_TO_B_AND_R_B_TO_T,
   DLG_STR_EFFECT_ROLL4_L_L_L_L,
   DLG_STR_EFFECT_ROLL4_L_L_L_R,
   DLG_STR_EFFECT_ROLL4_L_L_L_T,
   DLG_STR_EFFECT_ROLL4_L_L_L_B,
   DLG_STR_EFFECT_ROLL4_L_L_R_L,
   DLG_STR_EFFECT_ROLL4_L_L_R_R,
   DLG_STR_EFFECT_ROLL4_L_L_R_T,
   DLG_STR_EFFECT_ROLL4_L_L_R_B,
   DLG_STR_EFFECT_ROLL4_L_L_T_L,
   DLG_STR_EFFECT_ROLL4_L_L_T_R,
   DLG_STR_EFFECT_ROLL4_L_L_T_T,
   DLG_STR_EFFECT_ROLL4_L_L_T_B,
   DLG_STR_EFFECT_ROLL4_L_L_B_L,
   DLG_STR_EFFECT_ROLL4_L_L_B_R,
   DLG_STR_EFFECT_ROLL4_L_L_B_T,
   DLG_STR_EFFECT_ROLL4_L_L_B_B,
   DLG_STR_EFFECT_ROLL4_L_R_L_L,
   DLG_STR_EFFECT_ROLL4_L_R_L_R,
   DLG_STR_EFFECT_ROLL4_L_R_L_T,
   DLG_STR_EFFECT_ROLL4_L_R_L_B,
   DLG_STR_EFFECT_ROLL4_L_R_R_L,
   DLG_STR_EFFECT_ROLL4_L_R_R_R,
   DLG_STR_EFFECT_ROLL4_L_R_R_T,
   DLG_STR_EFFECT_ROLL4_L_R_R_B,
   DLG_STR_EFFECT_ROLL4_L_R_T_L,
   DLG_STR_EFFECT_ROLL4_L_R_T_R,
   DLG_STR_EFFECT_ROLL4_L_R_T_T,
   DLG_STR_EFFECT_ROLL4_L_R_T_B,
   DLG_STR_EFFECT_ROLL4_L_R_B_L,
   DLG_STR_EFFECT_ROLL4_L_R_B_R,
   DLG_STR_EFFECT_ROLL4_L_R_B_T,
   DLG_STR_EFFECT_ROLL4_L_R_B_B,
   DLG_STR_EFFECT_ROLL4_L_T_L_L,
   DLG_STR_EFFECT_ROLL4_L_T_L_R,
   DLG_STR_EFFECT_ROLL4_L_T_L_T,
   DLG_STR_EFFECT_ROLL4_L_T_L_B,
   DLG_STR_EFFECT_ROLL4_L_T_R_L,
   DLG_STR_EFFECT_ROLL4_L_T_R_R,
   DLG_STR_EFFECT_ROLL4_L_T_R_T,
   DLG_STR_EFFECT_ROLL4_L_T_R_B,
   DLG_STR_EFFECT_ROLL4_L_T_T_L,
   DLG_STR_EFFECT_ROLL4_L_T_T_R,
   DLG_STR_EFFECT_ROLL4_L_T_T_T,
   DLG_STR_EFFECT_ROLL4_L_T_T_B,
   DLG_STR_EFFECT_ROLL4_L_T_B_L,
   DLG_STR_EFFECT_ROLL4_L_T_B_R,
   DLG_STR_EFFECT_ROLL4_L_T_B_T,
   DLG_STR_EFFECT_ROLL4_L_T_B_B,
   DLG_STR_EFFECT_ROLL4_L_B_L_L,
   DLG_STR_EFFECT_ROLL4_L_B_L_R,
   DLG_STR_EFFECT_ROLL4_L_B_L_T,
   DLG_STR_EFFECT_ROLL4_L_B_L_B,
   DLG_STR_EFFECT_ROLL4_L_B_R_L,
   DLG_STR_EFFECT_ROLL4_L_B_R_R,
   DLG_STR_EFFECT_ROLL4_L_B_R_T,
   DLG_STR_EFFECT_ROLL4_L_B_R_B,
   DLG_STR_EFFECT_ROLL4_L_B_T_L,
   DLG_STR_EFFECT_ROLL4_L_B_T_R,
   DLG_STR_EFFECT_ROLL4_L_B_T_T,
   DLG_STR_EFFECT_ROLL4_L_B_T_B,
   DLG_STR_EFFECT_ROLL4_L_B_B_L,
   DLG_STR_EFFECT_ROLL4_L_B_B_R,
   DLG_STR_EFFECT_ROLL4_L_B_B_T,
   DLG_STR_EFFECT_ROLL4_L_B_B_B,
   DLG_STR_EFFECT_ROLL4_R_L_L_L,
   DLG_STR_EFFECT_ROLL4_R_L_L_R,
   DLG_STR_EFFECT_ROLL4_R_L_L_T,
   DLG_STR_EFFECT_ROLL4_R_L_L_B,
   DLG_STR_EFFECT_ROLL4_R_L_R_L,
   DLG_STR_EFFECT_ROLL4_R_L_R_R,
   DLG_STR_EFFECT_ROLL4_R_L_R_T,
   DLG_STR_EFFECT_ROLL4_R_L_R_B,
   DLG_STR_EFFECT_ROLL4_R_L_T_L,
   DLG_STR_EFFECT_ROLL4_R_L_T_R,
   DLG_STR_EFFECT_ROLL4_R_L_T_T,
   DLG_STR_EFFECT_ROLL4_R_L_T_B,
   DLG_STR_EFFECT_ROLL4_R_L_B_L,
   DLG_STR_EFFECT_ROLL4_R_L_B_R,
   DLG_STR_EFFECT_ROLL4_R_L_B_T,
   DLG_STR_EFFECT_ROLL4_R_L_B_B,
   DLG_STR_EFFECT_ROLL4_R_R_L_L,
   DLG_STR_EFFECT_ROLL4_R_R_L_R,
   DLG_STR_EFFECT_ROLL4_R_R_L_T,
   DLG_STR_EFFECT_ROLL4_R_R_L_B,
   DLG_STR_EFFECT_ROLL4_R_R_R_L,
   DLG_STR_EFFECT_ROLL4_R_R_R_R,
   DLG_STR_EFFECT_ROLL4_R_R_R_T,
   DLG_STR_EFFECT_ROLL4_R_R_R_B,
   DLG_STR_EFFECT_ROLL4_R_R_T_L,
   DLG_STR_EFFECT_ROLL4_R_R_T_R,
   DLG_STR_EFFECT_ROLL4_R_R_T_T,
   DLG_STR_EFFECT_ROLL4_R_R_T_B,
   DLG_STR_EFFECT_ROLL4_R_R_B_L,
   DLG_STR_EFFECT_ROLL4_R_R_B_R,
   DLG_STR_EFFECT_ROLL4_R_R_B_T,
   DLG_STR_EFFECT_ROLL4_R_R_B_B,
   DLG_STR_EFFECT_ROLL4_R_T_L_L,
   DLG_STR_EFFECT_ROLL4_R_T_L_R,
   DLG_STR_EFFECT_ROLL4_R_T_L_T,
   DLG_STR_EFFECT_ROLL4_R_T_L_B,
   DLG_STR_EFFECT_ROLL4_R_T_R_L,
   DLG_STR_EFFECT_ROLL4_R_T_R_R,
   DLG_STR_EFFECT_ROLL4_R_T_R_T,
   DLG_STR_EFFECT_ROLL4_R_T_R_B,
   DLG_STR_EFFECT_ROLL4_R_T_T_L,
   DLG_STR_EFFECT_ROLL4_R_T_T_R,
   DLG_STR_EFFECT_ROLL4_R_T_T_T,
   DLG_STR_EFFECT_ROLL4_R_T_T_B,
   DLG_STR_EFFECT_ROLL4_R_T_B_L,
   DLG_STR_EFFECT_ROLL4_R_T_B_R,
   DLG_STR_EFFECT_ROLL4_R_T_B_T,
   DLG_STR_EFFECT_ROLL4_R_T_B_B,
   DLG_STR_EFFECT_ROLL4_R_B_L_L,
   DLG_STR_EFFECT_ROLL4_R_B_L_R,
   DLG_STR_EFFECT_ROLL4_R_B_L_T,
   DLG_STR_EFFECT_ROLL4_R_B_L_B,
   DLG_STR_EFFECT_ROLL4_R_B_R_L,
   DLG_STR_EFFECT_ROLL4_R_B_R_R,
   DLG_STR_EFFECT_ROLL4_R_B_R_T,
   DLG_STR_EFFECT_ROLL4_R_B_R_B,
   DLG_STR_EFFECT_ROLL4_R_B_T_L,
   DLG_STR_EFFECT_ROLL4_R_B_T_R,
   DLG_STR_EFFECT_ROLL4_R_B_T_T,
   DLG_STR_EFFECT_ROLL4_R_B_T_B,
   DLG_STR_EFFECT_ROLL4_R_B_B_L,
   DLG_STR_EFFECT_ROLL4_R_B_B_R,
   DLG_STR_EFFECT_ROLL4_R_B_B_T,
   DLG_STR_EFFECT_ROLL4_R_B_B_B,
   DLG_STR_EFFECT_ROLL4_T_L_L_L,
   DLG_STR_EFFECT_ROLL4_T_L_L_R,
   DLG_STR_EFFECT_ROLL4_T_L_L_T,
   DLG_STR_EFFECT_ROLL4_T_L_L_B,
   DLG_STR_EFFECT_ROLL4_T_L_R_L,
   DLG_STR_EFFECT_ROLL4_T_L_R_R,
   DLG_STR_EFFECT_ROLL4_T_L_R_T,
   DLG_STR_EFFECT_ROLL4_T_L_R_B,
   DLG_STR_EFFECT_ROLL4_T_L_T_L,
   DLG_STR_EFFECT_ROLL4_T_L_T_R,
   DLG_STR_EFFECT_ROLL4_T_L_T_T,
   DLG_STR_EFFECT_ROLL4_T_L_T_B,
   DLG_STR_EFFECT_ROLL4_T_L_B_L,
   DLG_STR_EFFECT_ROLL4_T_L_B_R,
   DLG_STR_EFFECT_ROLL4_T_L_B_T,
   DLG_STR_EFFECT_ROLL4_T_L_B_B,
   DLG_STR_EFFECT_ROLL4_T_R_L_L,
   DLG_STR_EFFECT_ROLL4_T_R_L_R,
   DLG_STR_EFFECT_ROLL4_T_R_L_T,
   DLG_STR_EFFECT_ROLL4_T_R_L_B,
   DLG_STR_EFFECT_ROLL4_T_R_R_L,
   DLG_STR_EFFECT_ROLL4_T_R_R_R,
   DLG_STR_EFFECT_ROLL4_T_R_R_T,
   DLG_STR_EFFECT_ROLL4_T_R_R_B,
   DLG_STR_EFFECT_ROLL4_T_R_T_L,
   DLG_STR_EFFECT_ROLL4_T_R_T_R,
   DLG_STR_EFFECT_ROLL4_T_R_T_T,
   DLG_STR_EFFECT_ROLL4_T_R_T_B,
   DLG_STR_EFFECT_ROLL4_T_R_B_L,
   DLG_STR_EFFECT_ROLL4_T_R_B_R,
   DLG_STR_EFFECT_ROLL4_T_R_B_T,
   DLG_STR_EFFECT_ROLL4_T_R_B_B,
   DLG_STR_EFFECT_ROLL4_T_T_L_L,
   DLG_STR_EFFECT_ROLL4_T_T_L_R,
   DLG_STR_EFFECT_ROLL4_T_T_L_T,
   DLG_STR_EFFECT_ROLL4_T_T_L_B,
   DLG_STR_EFFECT_ROLL4_T_T_R_L,
   DLG_STR_EFFECT_ROLL4_T_T_R_R,
   DLG_STR_EFFECT_ROLL4_T_T_R_T,
   DLG_STR_EFFECT_ROLL4_T_T_R_B,
   DLG_STR_EFFECT_ROLL4_T_T_T_L,
   DLG_STR_EFFECT_ROLL4_T_T_T_R,
   DLG_STR_EFFECT_ROLL4_T_T_T_T,
   DLG_STR_EFFECT_ROLL4_T_T_T_B,
   DLG_STR_EFFECT_ROLL4_T_T_B_L,
   DLG_STR_EFFECT_ROLL4_T_T_B_R,
   DLG_STR_EFFECT_ROLL4_T_T_B_T,
   DLG_STR_EFFECT_ROLL4_T_T_B_B,
   DLG_STR_EFFECT_ROLL4_T_B_L_L,
   DLG_STR_EFFECT_ROLL4_T_B_L_R,
   DLG_STR_EFFECT_ROLL4_T_B_L_T,
   DLG_STR_EFFECT_ROLL4_T_B_L_B,
   DLG_STR_EFFECT_ROLL4_T_B_R_L,
   DLG_STR_EFFECT_ROLL4_T_B_R_R,
   DLG_STR_EFFECT_ROLL4_T_B_R_T,
   DLG_STR_EFFECT_ROLL4_T_B_R_B,
   DLG_STR_EFFECT_ROLL4_T_B_T_L,
   DLG_STR_EFFECT_ROLL4_T_B_T_R,
   DLG_STR_EFFECT_ROLL4_T_B_T_T,
   DLG_STR_EFFECT_ROLL4_T_B_T_B,
   DLG_STR_EFFECT_ROLL4_T_B_B_L,
   DLG_STR_EFFECT_ROLL4_T_B_B_R,
   DLG_STR_EFFECT_ROLL4_T_B_B_T,
   DLG_STR_EFFECT_ROLL4_T_B_B_B,
   DLG_STR_EFFECT_ROLL4_B_L_L_L,
   DLG_STR_EFFECT_ROLL4_B_L_L_R,
   DLG_STR_EFFECT_ROLL4_B_L_L_T,
   DLG_STR_EFFECT_ROLL4_B_L_L_B,
   DLG_STR_EFFECT_ROLL4_B_L_R_L,
   DLG_STR_EFFECT_ROLL4_B_L_R_R,
   DLG_STR_EFFECT_ROLL4_B_L_R_T,
   DLG_STR_EFFECT_ROLL4_B_L_R_B,
   DLG_STR_EFFECT_ROLL4_B_L_T_L,
   DLG_STR_EFFECT_ROLL4_B_L_T_R,
   DLG_STR_EFFECT_ROLL4_B_L_T_T,
   DLG_STR_EFFECT_ROLL4_B_L_T_B,
   DLG_STR_EFFECT_ROLL4_B_L_B_L,
   DLG_STR_EFFECT_ROLL4_B_L_B_R,
   DLG_STR_EFFECT_ROLL4_B_L_B_T,
   DLG_STR_EFFECT_ROLL4_B_L_B_B,
   DLG_STR_EFFECT_ROLL4_B_R_L_L,
   DLG_STR_EFFECT_ROLL4_B_R_L_R,
   DLG_STR_EFFECT_ROLL4_B_R_L_T,
   DLG_STR_EFFECT_ROLL4_B_R_L_B,
   DLG_STR_EFFECT_ROLL4_B_R_R_L,
   DLG_STR_EFFECT_ROLL4_B_R_R_R,
   DLG_STR_EFFECT_ROLL4_B_R_R_T,
   DLG_STR_EFFECT_ROLL4_B_R_R_B,
   DLG_STR_EFFECT_ROLL4_B_R_T_L,
   DLG_STR_EFFECT_ROLL4_B_R_T_R,
   DLG_STR_EFFECT_ROLL4_B_R_T_T,
   DLG_STR_EFFECT_ROLL4_B_R_T_B,
   DLG_STR_EFFECT_ROLL4_B_R_B_L,
   DLG_STR_EFFECT_ROLL4_B_R_B_R,
   DLG_STR_EFFECT_ROLL4_B_R_B_T,
   DLG_STR_EFFECT_ROLL4_B_R_B_B,
   DLG_STR_EFFECT_ROLL4_B_T_L_L,
   DLG_STR_EFFECT_ROLL4_B_T_L_R,
   DLG_STR_EFFECT_ROLL4_B_T_L_T,
   DLG_STR_EFFECT_ROLL4_B_T_L_B,
   DLG_STR_EFFECT_ROLL4_B_T_R_L,
   DLG_STR_EFFECT_ROLL4_B_T_R_R,
   DLG_STR_EFFECT_ROLL4_B_T_R_T,
   DLG_STR_EFFECT_ROLL4_B_T_R_B,
   DLG_STR_EFFECT_ROLL4_B_T_T_L,
   DLG_STR_EFFECT_ROLL4_B_T_T_R,
   DLG_STR_EFFECT_ROLL4_B_T_T_T,
   DLG_STR_EFFECT_ROLL4_B_T_T_B,
   DLG_STR_EFFECT_ROLL4_B_T_B_L,
   DLG_STR_EFFECT_ROLL4_B_T_B_R,
   DLG_STR_EFFECT_ROLL4_B_T_B_T,
   DLG_STR_EFFECT_ROLL4_B_T_B_B,
   DLG_STR_EFFECT_ROLL4_B_B_L_L,
   DLG_STR_EFFECT_ROLL4_B_B_L_R,
   DLG_STR_EFFECT_ROLL4_B_B_L_T,
   DLG_STR_EFFECT_ROLL4_B_B_L_B,
   DLG_STR_EFFECT_ROLL4_B_B_R_L,
   DLG_STR_EFFECT_ROLL4_B_B_R_R,
   DLG_STR_EFFECT_ROLL4_B_B_R_T,
   DLG_STR_EFFECT_ROLL4_B_B_R_B,
   DLG_STR_EFFECT_ROLL4_B_B_T_L,
   DLG_STR_EFFECT_ROLL4_B_B_T_R,
   DLG_STR_EFFECT_ROLL4_B_B_T_T,
   DLG_STR_EFFECT_ROLL4_B_B_T_B,
   DLG_STR_EFFECT_ROLL4_B_B_B_L,
   DLG_STR_EFFECT_ROLL4_B_B_B_R,
   DLG_STR_EFFECT_ROLL4_B_B_B_T,
   DLG_STR_EFFECT_ROLL4_B_B_B_B,
   DLG_STR_EFFECT_ROLL_END,
};

enum {
   DLG_STR_EFFECT_ROTATE_L_TO_R=DLG_STR_EFFECT_ROLL_END,
   DLG_STR_EFFECT_ROTATE_R_TO_L,
   DLG_STR_EFFECT_ROTATE_T_TO_B,
   DLG_STR_EFFECT_ROTATE_B_TO_T,
   DLG_STR_EFFECT_ROTATE4_L_L_L_L,
   DLG_STR_EFFECT_ROTATE4_L_L_L_R,
   DLG_STR_EFFECT_ROTATE4_L_L_L_T,
   DLG_STR_EFFECT_ROTATE4_L_L_L_B,
   DLG_STR_EFFECT_ROTATE4_L_L_R_L,
   DLG_STR_EFFECT_ROTATE4_L_L_R_R,
   DLG_STR_EFFECT_ROTATE4_L_L_R_T,
   DLG_STR_EFFECT_ROTATE4_L_L_R_B,
   DLG_STR_EFFECT_ROTATE4_L_L_T_L,
   DLG_STR_EFFECT_ROTATE4_L_L_T_R,
   DLG_STR_EFFECT_ROTATE4_L_L_T_T,
   DLG_STR_EFFECT_ROTATE4_L_L_T_B,
   DLG_STR_EFFECT_ROTATE4_L_L_B_L,
   DLG_STR_EFFECT_ROTATE4_L_L_B_R,
   DLG_STR_EFFECT_ROTATE4_L_L_B_T,
   DLG_STR_EFFECT_ROTATE4_L_L_B_B,
   DLG_STR_EFFECT_ROTATE4_L_R_L_L,
   DLG_STR_EFFECT_ROTATE4_L_R_L_R,
   DLG_STR_EFFECT_ROTATE4_L_R_L_T,
   DLG_STR_EFFECT_ROTATE4_L_R_L_B,
   DLG_STR_EFFECT_ROTATE4_L_R_R_L,
   DLG_STR_EFFECT_ROTATE4_L_R_R_R,
   DLG_STR_EFFECT_ROTATE4_L_R_R_T,
   DLG_STR_EFFECT_ROTATE4_L_R_R_B,
   DLG_STR_EFFECT_ROTATE4_L_R_T_L,
   DLG_STR_EFFECT_ROTATE4_L_R_T_R,
   DLG_STR_EFFECT_ROTATE4_L_R_T_T,
   DLG_STR_EFFECT_ROTATE4_L_R_T_B,
   DLG_STR_EFFECT_ROTATE4_L_R_B_L,
   DLG_STR_EFFECT_ROTATE4_L_R_B_R,
   DLG_STR_EFFECT_ROTATE4_L_R_B_T,
   DLG_STR_EFFECT_ROTATE4_L_R_B_B,
   DLG_STR_EFFECT_ROTATE4_L_T_L_L,
   DLG_STR_EFFECT_ROTATE4_L_T_L_R,
   DLG_STR_EFFECT_ROTATE4_L_T_L_T,
   DLG_STR_EFFECT_ROTATE4_L_T_L_B,
   DLG_STR_EFFECT_ROTATE4_L_T_R_L,
   DLG_STR_EFFECT_ROTATE4_L_T_R_R,
   DLG_STR_EFFECT_ROTATE4_L_T_R_T,
   DLG_STR_EFFECT_ROTATE4_L_T_R_B,
   DLG_STR_EFFECT_ROTATE4_L_T_T_L,
   DLG_STR_EFFECT_ROTATE4_L_T_T_R,
   DLG_STR_EFFECT_ROTATE4_L_T_T_T,
   DLG_STR_EFFECT_ROTATE4_L_T_T_B,
   DLG_STR_EFFECT_ROTATE4_L_T_B_L,
   DLG_STR_EFFECT_ROTATE4_L_T_B_R,
   DLG_STR_EFFECT_ROTATE4_L_T_B_T,
   DLG_STR_EFFECT_ROTATE4_L_T_B_B,
   DLG_STR_EFFECT_ROTATE4_L_B_L_L,
   DLG_STR_EFFECT_ROTATE4_L_B_L_R,
   DLG_STR_EFFECT_ROTATE4_L_B_L_T,
   DLG_STR_EFFECT_ROTATE4_L_B_L_B,
   DLG_STR_EFFECT_ROTATE4_L_B_R_L,
   DLG_STR_EFFECT_ROTATE4_L_B_R_R,
   DLG_STR_EFFECT_ROTATE4_L_B_R_T,
   DLG_STR_EFFECT_ROTATE4_L_B_R_B,
   DLG_STR_EFFECT_ROTATE4_L_B_T_L,
   DLG_STR_EFFECT_ROTATE4_L_B_T_R,
   DLG_STR_EFFECT_ROTATE4_L_B_T_T,
   DLG_STR_EFFECT_ROTATE4_L_B_T_B,
   DLG_STR_EFFECT_ROTATE4_L_B_B_L,
   DLG_STR_EFFECT_ROTATE4_L_B_B_R,
   DLG_STR_EFFECT_ROTATE4_L_B_B_T,
   DLG_STR_EFFECT_ROTATE4_L_B_B_B,
   DLG_STR_EFFECT_ROTATE4_R_L_L_L,
   DLG_STR_EFFECT_ROTATE4_R_L_L_R,
   DLG_STR_EFFECT_ROTATE4_R_L_L_T,
   DLG_STR_EFFECT_ROTATE4_R_L_L_B,
   DLG_STR_EFFECT_ROTATE4_R_L_R_L,
   DLG_STR_EFFECT_ROTATE4_R_L_R_R,
   DLG_STR_EFFECT_ROTATE4_R_L_R_T,
   DLG_STR_EFFECT_ROTATE4_R_L_R_B,
   DLG_STR_EFFECT_ROTATE4_R_L_T_L,
   DLG_STR_EFFECT_ROTATE4_R_L_T_R,
   DLG_STR_EFFECT_ROTATE4_R_L_T_T,
   DLG_STR_EFFECT_ROTATE4_R_L_T_B,
   DLG_STR_EFFECT_ROTATE4_R_L_B_L,
   DLG_STR_EFFECT_ROTATE4_R_L_B_R,
   DLG_STR_EFFECT_ROTATE4_R_L_B_T,
   DLG_STR_EFFECT_ROTATE4_R_L_B_B,
   DLG_STR_EFFECT_ROTATE4_R_R_L_L,
   DLG_STR_EFFECT_ROTATE4_R_R_L_R,
   DLG_STR_EFFECT_ROTATE4_R_R_L_T,
   DLG_STR_EFFECT_ROTATE4_R_R_L_B,
   DLG_STR_EFFECT_ROTATE4_R_R_R_L,
   DLG_STR_EFFECT_ROTATE4_R_R_R_R,
   DLG_STR_EFFECT_ROTATE4_R_R_R_T,
   DLG_STR_EFFECT_ROTATE4_R_R_R_B,
   DLG_STR_EFFECT_ROTATE4_R_R_T_L,
   DLG_STR_EFFECT_ROTATE4_R_R_T_R,
   DLG_STR_EFFECT_ROTATE4_R_R_T_T,
   DLG_STR_EFFECT_ROTATE4_R_R_T_B,
   DLG_STR_EFFECT_ROTATE4_R_R_B_L,
   DLG_STR_EFFECT_ROTATE4_R_R_B_R,
   DLG_STR_EFFECT_ROTATE4_R_R_B_T,
   DLG_STR_EFFECT_ROTATE4_R_R_B_B,
   DLG_STR_EFFECT_ROTATE4_R_T_L_L,
   DLG_STR_EFFECT_ROTATE4_R_T_L_R,
   DLG_STR_EFFECT_ROTATE4_R_T_L_T,
   DLG_STR_EFFECT_ROTATE4_R_T_L_B,
   DLG_STR_EFFECT_ROTATE4_R_T_R_L,
   DLG_STR_EFFECT_ROTATE4_R_T_R_R,
   DLG_STR_EFFECT_ROTATE4_R_T_R_T,
   DLG_STR_EFFECT_ROTATE4_R_T_R_B,
   DLG_STR_EFFECT_ROTATE4_R_T_T_L,
   DLG_STR_EFFECT_ROTATE4_R_T_T_R,
   DLG_STR_EFFECT_ROTATE4_R_T_T_T,
   DLG_STR_EFFECT_ROTATE4_R_T_T_B,
   DLG_STR_EFFECT_ROTATE4_R_T_B_L,
   DLG_STR_EFFECT_ROTATE4_R_T_B_R,
   DLG_STR_EFFECT_ROTATE4_R_T_B_T,
   DLG_STR_EFFECT_ROTATE4_R_T_B_B,
   DLG_STR_EFFECT_ROTATE4_R_B_L_L,
   DLG_STR_EFFECT_ROTATE4_R_B_L_R,
   DLG_STR_EFFECT_ROTATE4_R_B_L_T,
   DLG_STR_EFFECT_ROTATE4_R_B_L_B,
   DLG_STR_EFFECT_ROTATE4_R_B_R_L,
   DLG_STR_EFFECT_ROTATE4_R_B_R_R,
   DLG_STR_EFFECT_ROTATE4_R_B_R_T,
   DLG_STR_EFFECT_ROTATE4_R_B_R_B,
   DLG_STR_EFFECT_ROTATE4_R_B_T_L,
   DLG_STR_EFFECT_ROTATE4_R_B_T_R,
   DLG_STR_EFFECT_ROTATE4_R_B_T_T,
   DLG_STR_EFFECT_ROTATE4_R_B_T_B,
   DLG_STR_EFFECT_ROTATE4_R_B_B_L,
   DLG_STR_EFFECT_ROTATE4_R_B_B_R,
   DLG_STR_EFFECT_ROTATE4_R_B_B_T,
   DLG_STR_EFFECT_ROTATE4_R_B_B_B,
   DLG_STR_EFFECT_ROTATE4_T_L_L_L,
   DLG_STR_EFFECT_ROTATE4_T_L_L_R,
   DLG_STR_EFFECT_ROTATE4_T_L_L_T,
   DLG_STR_EFFECT_ROTATE4_T_L_L_B,
   DLG_STR_EFFECT_ROTATE4_T_L_R_L,
   DLG_STR_EFFECT_ROTATE4_T_L_R_R,
   DLG_STR_EFFECT_ROTATE4_T_L_R_T,
   DLG_STR_EFFECT_ROTATE4_T_L_R_B,
   DLG_STR_EFFECT_ROTATE4_T_L_T_L,
   DLG_STR_EFFECT_ROTATE4_T_L_T_R,
   DLG_STR_EFFECT_ROTATE4_T_L_T_T,
   DLG_STR_EFFECT_ROTATE4_T_L_T_B,
   DLG_STR_EFFECT_ROTATE4_T_L_B_L,
   DLG_STR_EFFECT_ROTATE4_T_L_B_R,
   DLG_STR_EFFECT_ROTATE4_T_L_B_T,
   DLG_STR_EFFECT_ROTATE4_T_L_B_B,
   DLG_STR_EFFECT_ROTATE4_T_R_L_L,
   DLG_STR_EFFECT_ROTATE4_T_R_L_R,
   DLG_STR_EFFECT_ROTATE4_T_R_L_T,
   DLG_STR_EFFECT_ROTATE4_T_R_L_B,
   DLG_STR_EFFECT_ROTATE4_T_R_R_L,
   DLG_STR_EFFECT_ROTATE4_T_R_R_R,
   DLG_STR_EFFECT_ROTATE4_T_R_R_T,
   DLG_STR_EFFECT_ROTATE4_T_R_R_B,
   DLG_STR_EFFECT_ROTATE4_T_R_T_L,
   DLG_STR_EFFECT_ROTATE4_T_R_T_R,
   DLG_STR_EFFECT_ROTATE4_T_R_T_T,
   DLG_STR_EFFECT_ROTATE4_T_R_T_B,
   DLG_STR_EFFECT_ROTATE4_T_R_B_L,
   DLG_STR_EFFECT_ROTATE4_T_R_B_R,
   DLG_STR_EFFECT_ROTATE4_T_R_B_T,
   DLG_STR_EFFECT_ROTATE4_T_R_B_B,
   DLG_STR_EFFECT_ROTATE4_T_T_L_L,
   DLG_STR_EFFECT_ROTATE4_T_T_L_R,
   DLG_STR_EFFECT_ROTATE4_T_T_L_T,
   DLG_STR_EFFECT_ROTATE4_T_T_L_B,
   DLG_STR_EFFECT_ROTATE4_T_T_R_L,
   DLG_STR_EFFECT_ROTATE4_T_T_R_R,
   DLG_STR_EFFECT_ROTATE4_T_T_R_T,
   DLG_STR_EFFECT_ROTATE4_T_T_R_B,
   DLG_STR_EFFECT_ROTATE4_T_T_T_L,
   DLG_STR_EFFECT_ROTATE4_T_T_T_R,
   DLG_STR_EFFECT_ROTATE4_T_T_T_T,
   DLG_STR_EFFECT_ROTATE4_T_T_T_B,
   DLG_STR_EFFECT_ROTATE4_T_T_B_L,
   DLG_STR_EFFECT_ROTATE4_T_T_B_R,
   DLG_STR_EFFECT_ROTATE4_T_T_B_T,
   DLG_STR_EFFECT_ROTATE4_T_T_B_B,
   DLG_STR_EFFECT_ROTATE4_T_B_L_L,
   DLG_STR_EFFECT_ROTATE4_T_B_L_R,
   DLG_STR_EFFECT_ROTATE4_T_B_L_T,
   DLG_STR_EFFECT_ROTATE4_T_B_L_B,
   DLG_STR_EFFECT_ROTATE4_T_B_R_L,
   DLG_STR_EFFECT_ROTATE4_T_B_R_R,
   DLG_STR_EFFECT_ROTATE4_T_B_R_T,
   DLG_STR_EFFECT_ROTATE4_T_B_R_B,
   DLG_STR_EFFECT_ROTATE4_T_B_T_L,
   DLG_STR_EFFECT_ROTATE4_T_B_T_R,
   DLG_STR_EFFECT_ROTATE4_T_B_T_T,
   DLG_STR_EFFECT_ROTATE4_T_B_T_B,
   DLG_STR_EFFECT_ROTATE4_T_B_B_L,
   DLG_STR_EFFECT_ROTATE4_T_B_B_R,
   DLG_STR_EFFECT_ROTATE4_T_B_B_T,
   DLG_STR_EFFECT_ROTATE4_T_B_B_B,
   DLG_STR_EFFECT_ROTATE4_B_L_L_L,
   DLG_STR_EFFECT_ROTATE4_B_L_L_R,
   DLG_STR_EFFECT_ROTATE4_B_L_L_T,
   DLG_STR_EFFECT_ROTATE4_B_L_L_B,
   DLG_STR_EFFECT_ROTATE4_B_L_R_L,
   DLG_STR_EFFECT_ROTATE4_B_L_R_R,
   DLG_STR_EFFECT_ROTATE4_B_L_R_T,
   DLG_STR_EFFECT_ROTATE4_B_L_R_B,
   DLG_STR_EFFECT_ROTATE4_B_L_T_L,
   DLG_STR_EFFECT_ROTATE4_B_L_T_R,
   DLG_STR_EFFECT_ROTATE4_B_L_T_T,
   DLG_STR_EFFECT_ROTATE4_B_L_T_B,
   DLG_STR_EFFECT_ROTATE4_B_L_B_L,
   DLG_STR_EFFECT_ROTATE4_B_L_B_R,
   DLG_STR_EFFECT_ROTATE4_B_L_B_T,
   DLG_STR_EFFECT_ROTATE4_B_L_B_B,
   DLG_STR_EFFECT_ROTATE4_B_R_L_L,
   DLG_STR_EFFECT_ROTATE4_B_R_L_R,
   DLG_STR_EFFECT_ROTATE4_B_R_L_T,
   DLG_STR_EFFECT_ROTATE4_B_R_L_B,
   DLG_STR_EFFECT_ROTATE4_B_R_R_L,
   DLG_STR_EFFECT_ROTATE4_B_R_R_R,
   DLG_STR_EFFECT_ROTATE4_B_R_R_T,
   DLG_STR_EFFECT_ROTATE4_B_R_R_B,
   DLG_STR_EFFECT_ROTATE4_B_R_T_L,
   DLG_STR_EFFECT_ROTATE4_B_R_T_R,
   DLG_STR_EFFECT_ROTATE4_B_R_T_T,
   DLG_STR_EFFECT_ROTATE4_B_R_T_B,
   DLG_STR_EFFECT_ROTATE4_B_R_B_L,
   DLG_STR_EFFECT_ROTATE4_B_R_B_R,
   DLG_STR_EFFECT_ROTATE4_B_R_B_T,
   DLG_STR_EFFECT_ROTATE4_B_R_B_B,
   DLG_STR_EFFECT_ROTATE4_B_T_L_L,
   DLG_STR_EFFECT_ROTATE4_B_T_L_R,
   DLG_STR_EFFECT_ROTATE4_B_T_L_T,
   DLG_STR_EFFECT_ROTATE4_B_T_L_B,
   DLG_STR_EFFECT_ROTATE4_B_T_R_L,
   DLG_STR_EFFECT_ROTATE4_B_T_R_R,
   DLG_STR_EFFECT_ROTATE4_B_T_R_T,
   DLG_STR_EFFECT_ROTATE4_B_T_R_B,
   DLG_STR_EFFECT_ROTATE4_B_T_T_L,
   DLG_STR_EFFECT_ROTATE4_B_T_T_R,
   DLG_STR_EFFECT_ROTATE4_B_T_T_T,
   DLG_STR_EFFECT_ROTATE4_B_T_T_B,
   DLG_STR_EFFECT_ROTATE4_B_T_B_L,
   DLG_STR_EFFECT_ROTATE4_B_T_B_R,
   DLG_STR_EFFECT_ROTATE4_B_T_B_T,
   DLG_STR_EFFECT_ROTATE4_B_T_B_B,
   DLG_STR_EFFECT_ROTATE4_B_B_L_L,
   DLG_STR_EFFECT_ROTATE4_B_B_L_R,
   DLG_STR_EFFECT_ROTATE4_B_B_L_T,
   DLG_STR_EFFECT_ROTATE4_B_B_L_B,
   DLG_STR_EFFECT_ROTATE4_B_B_R_L,
   DLG_STR_EFFECT_ROTATE4_B_B_R_R,
   DLG_STR_EFFECT_ROTATE4_B_B_R_T,
   DLG_STR_EFFECT_ROTATE4_B_B_R_B,
   DLG_STR_EFFECT_ROTATE4_B_B_T_L,
   DLG_STR_EFFECT_ROTATE4_B_B_T_R,
   DLG_STR_EFFECT_ROTATE4_B_B_T_T,
   DLG_STR_EFFECT_ROTATE4_B_B_T_B,
   DLG_STR_EFFECT_ROTATE4_B_B_B_L,
   DLG_STR_EFFECT_ROTATE4_B_B_B_R,
   DLG_STR_EFFECT_ROTATE4_B_B_B_T,
   DLG_STR_EFFECT_ROTATE4_B_B_B_B,
   DLG_STR_EFFECT_ROTATE_END,
};

enum {
   DLG_STR_EFFECT_ZOOM_TO_C=DLG_STR_EFFECT_ROTATE_END,
   DLG_STR_EFFECT_ZOOM_FROM_C,

   DLG_STR_EFFECT_DRIP_T_TO_B,
   DLG_STR_EFFECT_DRIP_B_TO_T,
   DLG_STR_EFFECT_DRIP_L_TO_R,
   DLG_STR_EFFECT_DRIP_R_TO_L,

   DLG_STR_EFFECT_BLIND_T_TO_B,
   DLG_STR_EFFECT_BLIND_L_TO_R,
   DLG_STR_EFFECT_BLIND_GROWING_L_TO_R,
   DLG_STR_EFFECT_BLIND_GROWING_R_TO_L,
   DLG_STR_EFFECT_BLIND_GROWING_T_TO_B,
   DLG_STR_EFFECT_BLIND_GROWING_B_TO_T,
   DLG_STR_EFFECT_BLIND2_T_TO_B_AND_L_TO_R,

   DLG_STR_EFFECT_RANDOM_BARS_R_TO_L,
   DLG_STR_EFFECT_RANDOM_BARS_L_TO_R,
   DLG_STR_EFFECT_RANDOM_BARS_B_TO_T,
   DLG_STR_EFFECT_RANDOM_BARS_T_TO_B,
   DLG_STR_EFFECT_RANDOM_LINES,
   DLG_STR_EFFECT_RANDOM_BLOCKS,
   DLG_STR_EFFECT_RANDOM_BLOCKS_R_TO_L,
   DLG_STR_EFFECT_RANDOM_BLOCKS_L_TO_R,
   DLG_STR_EFFECT_RANDOM_BLOCKS_B_TO_T,
   DLG_STR_EFFECT_RANDOM_BLOCKS_T_TO_B,

   DLG_STR_EFFECT_CHECKERBOARD_T_TO_B_THEN_T_TO_B,
   DLG_STR_EFFECT_CHECKERBOARD_B_TO_T_THEN_B_TO_T,
   DLG_STR_EFFECT_CHECKERBOARD_L_TO_R_THEN_L_TO_R,
   DLG_STR_EFFECT_CHECKERBOARD_R_TO_L_THEN_R_TO_L,
   DLG_STR_EFFECT_CHECKERBOARD_T_TO_B_THEN_B_TO_T,
   DLG_STR_EFFECT_CHECKERBOARD_B_TO_T_THEN_T_TO_B,
   DLG_STR_EFFECT_CHECKERBOARD_L_TO_R_THEN_R_TO_L,
   DLG_STR_EFFECT_CHECKERBOARD_R_TO_L_THEN_L_TO_R,

   DLG_STR_EFFECT_BLOCKS_T_TO_B,
   DLG_STR_EFFECT_BLOCKS_B_TO_T,
   DLG_STR_EFFECT_BLOCKS_L_TO_R,
   DLG_STR_EFFECT_BLOCKS_R_TO_L,
   DLG_STR_EFFECT_BLOCKS_SWIRL_CW_TO_C,
   DLG_STR_EFFECT_BLOCKS_SWIRL_CW_FROM_C,
   DLG_STR_EFFECT_BLOCKS_SWIRL_CCW_TO_C,
   DLG_STR_EFFECT_BLOCKS_SWIRL_CCW_FROM_C,

   DLG_STR_EFFECT_CIRCLE_C_IN,
   DLG_STR_EFFECT_CIRCLE_C_OUT,
   DLG_STR_EFFECT_CIRCLE_L_IN,
   DLG_STR_EFFECT_CIRCLE_L_OUT,
   DLG_STR_EFFECT_CIRCLE_R_IN,
   DLG_STR_EFFECT_CIRCLE_R_OUT,
   DLG_STR_EFFECT_CIRCLE_T_IN,
   DLG_STR_EFFECT_CIRCLE_T_OUT,
   DLG_STR_EFFECT_CIRCLE_B_IN,
   DLG_STR_EFFECT_CIRCLE_B_OUT,
   DLG_STR_EFFECT_CIRCLE_C_INTER_IN_THEN_IN,
   DLG_STR_EFFECT_CIRCLE_C_INTER_OUT_THEN_OUT,
   DLG_STR_EFFECT_CIRCLE_C_INTER_IN_THEN_OUT,
   DLG_STR_EFFECT_CIRCLE_C_INTER_OUT_THEN_IN,
   DLG_STR_EFFECT_CIRCLE_L_INTER_IN_THEN_IN,
   DLG_STR_EFFECT_CIRCLE_L_INTER_OUT_THEN_OUT,
   DLG_STR_EFFECT_CIRCLE_L_INTER_IN_THEN_OUT,
   DLG_STR_EFFECT_CIRCLE_L_INTER_OUT_THEN_IN,
   DLG_STR_EFFECT_CIRCLE_R_INTER_IN_THEN_IN,
   DLG_STR_EFFECT_CIRCLE_R_INTER_OUT_THEN_OUT,
   DLG_STR_EFFECT_CIRCLE_R_INTER_IN_THEN_OUT,
   DLG_STR_EFFECT_CIRCLE_R_INTER_OUT_THEN_IN,
   DLG_STR_EFFECT_CIRCLE_T_INTER_IN_THEN_IN,
   DLG_STR_EFFECT_CIRCLE_T_INTER_OUT_THEN_OUT,
   DLG_STR_EFFECT_CIRCLE_T_INTER_IN_THEN_OUT,
   DLG_STR_EFFECT_CIRCLE_T_INTER_OUT_THEN_IN,
   DLG_STR_EFFECT_CIRCLE_B_INTER_IN_THEN_IN,
   DLG_STR_EFFECT_CIRCLE_B_INTER_OUT_THEN_OUT,
   DLG_STR_EFFECT_CIRCLE_B_INTER_IN_THEN_OUT,
   DLG_STR_EFFECT_CIRCLE_B_INTER_OUT_THEN_IN,
   DLG_STR_EFFECT_CIRCLE_L_R_INTER,
   DLG_STR_EFFECT_CIRCLE_T_B_INTER,
   DLG_STR_EFFECT_CIRCLE2_L_R_OUT,
   DLG_STR_EFFECT_CIRCLE2_L_R_IN,
   DLG_STR_EFFECT_CIRCLE2_T_B_OUT,
   DLG_STR_EFFECT_CIRCLE2_T_B_IN,

   DLG_STR_EFFECT_ELLIPSE_C_IN,
   DLG_STR_EFFECT_ELLIPSE_C_OUT,
   DLG_STR_EFFECT_ELLIPSE_L_IN,
   DLG_STR_EFFECT_ELLIPSE_L_OUT,
   DLG_STR_EFFECT_ELLIPSE_R_IN,
   DLG_STR_EFFECT_ELLIPSE_R_OUT,
   DLG_STR_EFFECT_ELLIPSE_T_IN,
   DLG_STR_EFFECT_ELLIPSE_T_OUT,
   DLG_STR_EFFECT_ELLIPSE_B_IN,
   DLG_STR_EFFECT_ELLIPSE_B_OUT,
   DLG_STR_EFFECT_ELLIPSE_C_INTER_IN_THEN_IN,
   DLG_STR_EFFECT_ELLIPSE_C_INTER_OUT_THEN_OUT,
   DLG_STR_EFFECT_ELLIPSE_C_INTER_IN_THEN_OUT,
   DLG_STR_EFFECT_ELLIPSE_C_INTER_OUT_THEN_IN,
   DLG_STR_EFFECT_ELLIPSE_L_INTER_IN_THEN_IN,
   DLG_STR_EFFECT_ELLIPSE_L_INTER_OUT_THEN_OUT,
   DLG_STR_EFFECT_ELLIPSE_L_INTER_IN_THEN_OUT,
   DLG_STR_EFFECT_ELLIPSE_L_INTER_OUT_THEN_IN,
   DLG_STR_EFFECT_ELLIPSE_R_INTER_IN_THEN_IN,
   DLG_STR_EFFECT_ELLIPSE_R_INTER_OUT_THEN_OUT,
   DLG_STR_EFFECT_ELLIPSE_R_INTER_IN_THEN_OUT,
   DLG_STR_EFFECT_ELLIPSE_R_INTER_OUT_THEN_IN,
   DLG_STR_EFFECT_ELLIPSE_T_INTER_IN_THEN_IN,
   DLG_STR_EFFECT_ELLIPSE_T_INTER_OUT_THEN_OUT,
   DLG_STR_EFFECT_ELLIPSE_T_INTER_IN_THEN_OUT,
   DLG_STR_EFFECT_ELLIPSE_T_INTER_OUT_THEN_IN,
   DLG_STR_EFFECT_ELLIPSE_B_INTER_IN_THEN_IN,
   DLG_STR_EFFECT_ELLIPSE_B_INTER_OUT_THEN_OUT,
   DLG_STR_EFFECT_ELLIPSE_B_INTER_IN_THEN_OUT,
   DLG_STR_EFFECT_ELLIPSE_B_INTER_OUT_THEN_IN,
   DLG_STR_EFFECT_ELLIPSE_L_R_INTER,
   DLG_STR_EFFECT_ELLIPSE_T_B_INTER,
   DLG_STR_EFFECT_ELLIPSE2_L_R_OUT,
   DLG_STR_EFFECT_ELLIPSE2_L_R_IN,
   DLG_STR_EFFECT_ELLIPSE2_T_B_OUT,
   DLG_STR_EFFECT_ELLIPSE2_T_B_IN,
   DLG_STR_EFFECT_END,
   };

enum {
   DLG_STR_CR48BIT = DLG_STR_EFFECT_END,           /* ColorRes dialog 48-bit              */
   DLG_STR_CR64BIT,           /* ColorRes dialog 64-bit              */
   DLG_STR_TIFF48,
   DLG_STR_TIFF64,
   /* TIFF file subtypes (48-bit)       */
   DLG_STR_SUB_TIFF48_UNCOMPRESSEDRGB,
   DLG_STR_SUB_TIFF48_LZWRGB,
   /* TIFF file subtypes (64-bit)       */
   DLG_STR_SUB_TIFF64_UNCOMPRESSEDRGB,
   DLG_STR_SUB_TIFF64_LZWRGB,
   DLG_STR_SUB_TIFF12_JPEG_GRAY_YCC,
   DLG_STR_SUB_TIFF12_LZW,

   /* new in 11.5 - for rotate dialog box */
   DLG_STR_ROTATENONESTR,
   DLG_STR_ROTATERESAMPLESTR,
   DLG_STR_ROTATEBICUBICSTR,

   /* new formats in 11.5 */
   DLG_STR_FILE_FLI,
   DLG_STR_FILE_FLC,
   DLG_STR_FLC8,
   DLG_STR_EXT_FLC,
   DLG_STR_ANI1,
   DLG_STR_ANI4,
   DLG_STR_ANI8,
   DLG_STR_ANI24,
   DLG_STR_EXT_ANI,

   DLG_STR_FILE_XWD10,
   DLG_STR_FILE_XWD11,
   DLG_STR_XWD10_1,
   DLG_STR_XWD10_4,
   DLG_STR_XWD10_8,
   DLG_STR_XWD11_1,
   DLG_STR_XWD11_4,
   DLG_STR_XWD11_8,
   DLG_STR_XWD11_16,
   DLG_STR_XWD11_24,
   DLG_STR_XWD11_32,
   DLG_STR_EXT_XWD,

   DLG_STR_FILE_CGM,
   DLG_STR_FILE_DRW,
   DLG_STR_FILE_PLT,

   DLG_STR_SUB_TIFF1_JBIG,
   DLG_STR_SUB_TIFFOTHER_JBIG,
   DLG_STR_SUB_TIFF8_JBIG,
   DLG_STR_SUB_TIFF8_CMP,
   DLG_STR_SUB_TIFF24_CMP_NONPROGRESSIVE,
   DLG_STR_SUB_TIFF24_CMP_PROGRESSIVE,

   DLG_STR_FILE_TIF_CMP,
   DLG_STR_FILE_TIF_JBIG,
   DLG_STR_FILE_TIF_DXF,
   DLG_STR_FILE_TIF_UNKNOWN,

   /* new formats in 12.0 */
   DLG_STR_FILE_SGI,
   DLG_STR_SGI8,
   DLG_STR_SGI24,
   DLG_STR_SGI32,
   DLG_STR_EXT_SGI,
   /* SGI file subtypes */
   DLG_STR_SUB_SGI_UNCOMPRESSED,
   DLG_STR_SUB_SGI_RLECOMPRESSED,
   /* TIFF file subtypes (12-bit)       */
   DLG_STR_SUB_TIFF12_RLE,

   DLG_STR_FILE_CLP,
   DLG_STR_CLP1,
   DLG_STR_CLP4,
   DLG_STR_CLP8,
   DLG_STR_CLP24,
   DLG_STR_EXT_CLP,

   DLG_STR_FILE_RAW,
   DLG_STR_RAW,
   DLG_STR_EXT_RAW,

   DLG_STR_SUB_PDF1_UNCOMPRESSED,
   DLG_STR_SUB_PDF1_CCITT_G3_1D,
   DLG_STR_SUB_PDF1_CCITT_G3_2D,
   DLG_STR_SUB_PDF1_CCITT_G4,

   DLG_STR_SUB_PDF8_UNCOMPRESSED,
   DLG_STR_SUB_PDF8_LOSSLESSJPEG,
   DLG_STR_SUB_PDF24_UNCOMPRESSED,
   DLG_STR_SUB_PDF24_YUV_444,
   DLG_STR_SUB_PDF24_YUV_422,
   DLG_STR_SUB_PDF24_YUV_411,
   DLG_STR_FILE_PDF,
   DLG_STR_PDF1,
   DLG_STR_PDF2,
   DLG_STR_PDF4,
   DLG_STR_PDF8,
   DLG_STR_PDF24,
   DLG_STR_EXT_PDF,
   DLG_STR_PDFCAPTION,
   DLG_STR_PDFHRESOLUTION,
   DLG_STR_PDFVRESOLUTION,
   DLG_STR_PDFDISPLAYDEPTH, 
   DLG_STR_PDFTEXTALPHA,
   DLG_STR_PDFGRAPHICSALPHA,
   DLG_STR_PDFDPI,
   DLG_STR_PDFBPP,
   DLG_STR_PDFBITS,

   // new filter strings added since 12.1
   DLG_STR_J2K8,
   DLG_STR_J2K24,
   DLG_STR_CMW8,
   DLG_STR_CMW24,
   DLG_STR_SUB_J2K,
   DLG_STR_SUB_JP2,
   DLG_STR_EXT_EXIF_JPEG,
   DLG_STR_EXT_J2K,
   DLG_STR_EXT_JP2,
   DLG_STR_EXT_CMW,
   DLG_STR_FILE_CMW,
   DLG_STR_FILE_J2K,
   DLG_STR_FILE_JP2,
   DLG_STR_J2KLOSSLESS,
   DLG_STR_J2KCOMPRATIO,
   DLG_STR_J2KTARGETSIZE,
   DLG_STR_J2KQFACTOR,
   DLG_STR_J2KQUALITY,
   DLG_STR_J2KRESOLUTION1,
   DLG_STR_J2KRESOLUTION2,
   DLG_STR_J2KCOLOR,
   DLG_STR_J2KPOSITION,
   DLG_STR_FILESAVE95J2KCOMPRESSIONCONTROLLABEL,
   DLG_STR_FILESAVE95J2KPROGRESSIONORDERLABEL,
   DLG_STR_FILESAVE95J2KCOMPRESSIONRATIOLABEL,
   DLG_STR_FILESAVE95J2KTARGETSIZELABEL,
   DLG_STR_FILESAVE95J2KADVANCED,

   DLG_STR_J2KCAPTION,

   DLG_STR_J2KXOSIZLABEL,
   DLG_STR_J2KYOSIZLABEL,
   DLG_STR_J2KXTSIZLABEL,
   DLG_STR_J2KYTSIZLABEL,
   DLG_STR_J2KXTOSIZLABEL,
   DLG_STR_J2KYTOSIZLABEL,
   DLG_STR_J2KCOLORTRANSFORM,
   DLG_STR_J2KDERIVEDQUANTIZATION,
   DLG_STR_J2KUSESOPMARKER,
   DLG_STR_J2KUSEEPHMARKER,
   DLG_STR_J2KDECOMPLEVELLABEL,
   DLG_STR_J2KGUARDBITSLABEL,
   DLG_STR_J2KMANTISSALABEL,
   DLG_STR_J2KEXPONENTLABEL,
   DLG_STR_J2KCODEBLOCKWIDTHLABEL,
   DLG_STR_J2KCODEBLOCKHEIGHTLABEL,
   DLG_STR_J2KSELECTIVEACBYPASS,
   DLG_STR_J2KRESETCONTEXT,
   DLG_STR_J2KTERMINATION,
   DLG_STR_J2KVERTICALLYCAUSAL,
   DLG_STR_J2KPREDICTABLETERMINATION,
   DLG_STR_J2KERRORRESILIENCE,
   DLG_STR_J2KDEFAULT,
   DLG_STR_J2KOFFSETANDTILING,
   DLG_STR_J2KGENERAL1,
   DLG_STR_J2KGENERAL2,
   DLG_STR_J2KARITHMETICENCODER,
   DLG_STR_J2KOKSTR,
   DLG_STR_J2KCANCELSTR,
   DLG_STR_FILE_TIF_J2K,
   DLG_STR_FILE_TIF_CMW,
   DLG_STR_SUB_TIFF8_J2K,
   DLG_STR_SUB_TIFF8_CMW,
   DLG_STR_SUB_TIFF24_J2K,
   DLG_STR_SUB_TIFF24_CMW,
   
   DLG_STR_SUB_TIFF12_J2K,
   DLG_STR_SUB_TIFF12_CMW,
   DLG_STR_SUB_TIFF16_J2K,
   DLG_STR_SUB_TIFF16_CMW,
   DLG_STR_J2K12,
   DLG_STR_J2K16,
   DLG_STR_CMW12,
   DLG_STR_CMW16,

   // The new strings ID's for ver 13
   //Open/ Save, Shortcut bar strings
   DLG_STR_SCB_PATHS,
   DLG_STR_SCB_HISTORY,
   DLG_STR_SCB_MYDOCUMENTS,
   DLG_STR_SCB_DESKTOP,
   DLG_STR_SCB_FAVORITES,
   DLG_STR_SCB_OPTIONS,

   DLG_STR_FILEINFO_ITEM,
   DLG_STR_FILEINFO_VALUE,

   //Image dialogs
   DLG_STR_BEFORESTR,	
   DLG_STR_AFTERSTR,	

   DLG_STR_NORMALSTR,
   DLG_STR_INTERPOLATIONSTR,
   DLG_STR_AUTOTRIMSTR,

   // Image Resize dialog
   DLG_STR_GETSIZE,
   DLG_STR_GETSIZE_ORIGINAL,
   DLG_STR_GETSIZE_NEW,
   DLG_STR_GETSIZE_IDENTICALVALUE,
   DLG_STR_GETSIZE_WIDTH,
   DLG_STR_GETSIZE_HEIGHT,
   DLG_STR_GETSIZE_SIZE,
   DLG_STR_GETSIZE_RESOLUTION,
   DLG_STR_GETSIZE_HORIZONTAL,
   DLG_STR_GETSIZE_VERTICAL,
   DLG_STR_GETSIZE_METHOD,
   DLG_STR_GETSIZE_NORMAL,
   DLG_STR_GETSIZE_FAVORBLACK,
   DLG_STR_GETSIZE_RESAMPLE,
   DLG_STR_GETSIZE_BICUBIC,
   DLG_STR_GETSIZE_MAINTAINAR,

   // color res dialog 
   DLG_STR_COLORRES_OPENPALETTE,
   DLG_STR_COLORRES_SVGA,
   DLG_STR_COLORRES_UNIFORM,
   DLG_STR_COLORRES_MSIE,

   //the Color Picker page
   DLG_STR_CLRPCKR,
   DLG_STR_CLRPCKR_NAME,
   DLG_STR_CLRPCKR_RGB,
   DLG_STR_CLRPCKR_HSB,
   DLG_STR_CLRPCKR_HLS,
   DLG_STR_CLRPCKR_CMY,
   DLG_STR_CLRPCKR_CMYK,
   DLG_STR_CLRPCKR_LAB,
   
   // the Canvas resize dialog
   DUMMY_DLG_STR_CANVASRESIZESTR,
   DUMMY_DLG_STR_CANVASRESIZE_SIZESTR,
   DUMMY_DLG_STR_CANVASRESIZE_NEWWIDTHSTR,
   DUMMY_DLG_STR_CANVASRESIZE_NEWHEIGHTSTR,
   DUMMY_DLG_STR_CANVASRESIZE_MAINTAINARSTR,
   DUMMY_DLG_STR_CANVASRESIZE_CURRENTWIDTHSTR,
   DUMMY_DLG_STR_CANVASRESIZE_CURRENTHIGHTSTR,
   DUMMY_DLG_STR_CANVASRESIZE_POSITIONSTR,
   DUMMY_DLG_STR_CANVASRESIZE_HORIZENTALSTR,
   DUMMY_DLG_STR_CANVASRESIZE_LEFTSTR,
   DUMMY_DLG_STR_CANVASRESIZE_RIGHTSTR,
   DUMMY_DLG_STR_CANVASRESIZE_VERTICALSTR,
   DUMMY_DLG_STR_CANVASRESIZE_TOPSTR,
   DUMMY_DLG_STR_CANVASRESIZE_BOTTOMSTR,
   DUMMY_DLG_STR_CANVASRESIZE_CENTERSTR,
   DUMMY_DLG_STR_CANVASRESIZE_CUSTOMSTR,
   DUMMY_DLG_STR_CANVASRESIZE_BKGCOLORSTR,

   // Picturize dialog
   DUMMY_DLG_STR_PICTURIZESTR,
   DUMMY_DLG_STR_PICTURIZE_CELLWIDTHSTR,
   DUMMY_DLG_STR_PICTURIZE_CELLHEIGHTSTR,
   DUMMY_DLG_STR_PICTURIZE_OPTIONSSTR,
   DUMMY_DLG_STR_PICTURIZE_RESIZESTR,
   DUMMY_DLG_STR_PICTURIZE_RESAMPLESTR,
   DUMMY_DLG_STR_PICTURIZE_BESTFITSTR,

   // Browse for directory dialog <used internally>
   DUMMY_DLG_STR_BROWSEDIRECTORYSTR,
   DUMMY_DLG_STR_BROWSEDIRECTORY_REFRESHSTR,
   DUMMY_DLG_STR_BROWSEDIRECTORY_SETTINGSSTR,
   DUMMY_DLG_STR_BROWSEDIRECTORY_DISPLAYDESKSTR,
   DUMMY_DLG_STR_BROWSEDIRECTORY_RCLKPOPUPSTR,
   DUMMY_DLG_STR_BROWSEDIRECTORY_ONLYSYSFILEFOLDERSTR,
   DUMMY_DLG_STR_BROWSEDIRECTORY_FILESSTR,
   DUMMY_DLG_STR_BROWSEDIRECTORY_NOTIFYERRORSTR,
   
   //Common Menu Item
   DLG_STR_HSBHUE,
   DLG_STR_HSBWHEEL,
   DLG_STR_HSBBRIGHT,
   DLG_STR_RGBADDITIVE,
   DLG_STR_CMYSUBTRACT,
   DLG_STR_CMYKSUBTRACT,
   DLG_STR_LABDEVICEIND,

   // the Palette Editor dialog 
   DUMMY_DLG_STR_PALEDTRSTR,
   DUMMY_DLG_STR_PALEDTR_PALETTESTR,
   DUMMY_DLG_STR_PALEDTR_IMAGECLRSTR,
   DUMMY_DLG_STR_PALEDTR_UNIFORMSTR,
   DUMMY_DLG_STR_PALEDTR_GRAYSCALESTR,
   DUMMY_DLG_STR_PALEDTR_NETSCAPESTR,
   DUMMY_DLG_STR_PALEDTR_MICROSOFTIESTR,
   DUMMY_DLG_STR_PALEDTR_STANDERDVGASTR,
   DUMMY_DLG_STR_PALEDTR_SYSTEMCOLORSTR,
   DUMMY_DLG_STR_PALEDTR_REPLACESTR,
   DUMMY_DLG_STR_PALEDTR_ADDSTR,
   DUMMY_DLG_STR_PALEDTR_ATTHEENDSTR,
   DUMMY_DLG_STR_PALEDTR_AFTERSELECTEDSTR,
   DUMMY_DLG_STR_PALEDTR_BEFORESELECTEDSTR,
   DUMMY_DLG_STR_PALEDTR_REMOVESTR,
   DUMMY_DLG_STR_PALEDTR_CONFIRMSTR,
   DUMMY_DLG_STR_PALEDTR_FINDCLOSESTSTR,
   DUMMY_DLG_STR_PALEDTR_SORTSTR,
   DUMMY_DLG_STR_PALEDTR_HSBSTR,
   DUMMY_DLG_STR_PALEDTR_HUESTR,
   DUMMY_DLG_STR_PALEDTR_SATURATIONSTR,
   DUMMY_DLG_STR_PALEDTR_BRIGHTNESSSTR,
   DUMMY_DLG_STR_PALEDTR_RGBMNUSTR,
   DUMMY_DLG_STR_PALEDTR_REVERSESTR,
   DUMMY_DLG_STR_PALEDTR_COLORMODELSTR,
   DUMMY_DLG_STR_PALEDTR_PALETTEMNUSTR,
   DUMMY_DLG_STR_PALEDTR_NEWSTR,
   DUMMY_DLG_STR_PALEDTR_OPENSTR,
   DUMMY_DLG_STR_PALEDTR_SAVESTR,
   DUMMY_DLG_STR_PALEDTR_SAVEASSTR,
   DUMMY_DLG_STR_PALEDTR_RGBSTR,
   DUMMY_DLG_STR_PALEDTR_HTMLSTR,
   DUMMY_DLG_STR_PALEDTR_INDEXSTR,
   DUMMY_DLG_STR_PALEDTR_HTML_FORMATSTR,
   DUMMY_DLG_STR_PALEDTR_RGB_FORMATSTR,
   DUMMY_DLG_STR_PALEDTR_INDEX_FORMATSTR,
   // the error messages
   DUMMY_DLG_STR_PALEDTR_ERR_SAVETITLESTR,
   DUMMY_DLG_STR_PALEDTR_ERR_ERRORTITLESTR,
   DUMMY_DLG_STR_PALEDTR_ERR_OPENTITLESTR,
   DUMMY_DLG_STR_PALEDTR_ERR_WARNINGTITLESTR,

   DUMMY_DLG_STR_PALEDTR_ERR_NOT_PALETTESTR,
   DUMMY_DLG_STR_PALEDTR_ERR_LOSE_CHANGESSTR,
   DUMMY_DLG_STR_PALEDTR_ERR_NO_SELECTIONSTR,
   DUMMY_DLG_STR_PALEDTR_ERR_FIND_CLOSESTSTR,
   DUMMY_DLG_STR_PALEDTR_ERR_NO_RIGHT_SELSTR,
   DUMMY_DLG_STR_PALEDTR_ERR_ADD_SELECTIONSTR,
   DUMMY_DLG_STR_PALEDTR_ERR_MAX_COLORSSTR,
   DUMMY_DLG_STR_PALEDTR_ERR_DUPLICATE_CLRSTR,
   DUMMY_DLG_STR_PALEDTR_ERR_DUPLCLR_NO_INDEXSTR,
   DUMMY_DLG_STR_PALEDTR_ERR_CONFIRM_REMOVESTR,
   DUMMY_DLG_STR_PALEDTR_ERR_IN_RIGHT_PANSTR,
   DUMMY_DLG_STR_PALEDTR_ERR_FIND_CLOSEST_SELSTR,
   DUMMY_DLG_STR_PALEDTR_ERR_COUNT_DIFFERSTR,
   DUMMY_DLG_STR_PALEDTR_ERR_MULTIPLE_BY_ONESTR,

   // Optemizer dialogs
   DUMMY_DLG_STR_PNGOPTIMIZERSTR,
   DUMMY_DLG_STR_GIFOPTIMIZERSTR,
   DUMMY_DLG_STR_JPEGOPTIMIZERSTR,
   DUMMY_DLG_STR_OPTIMIZER_UNCOMPRESSEDSTR,
   DUMMY_DLG_STR_OPTIMIZER_COMPRESSEDSTR,
   DUMMY_DLG_STR_OPTIMIZER_ERRORSTR,
   DUMMY_DLG_STR_OPTIMIZER_WAITSTR,
   DUMMY_DLG_STR_OPTIMIZER_144KBSSTR,
   DUMMY_DLG_STR_OPTIMIZER_288KBSSTR,
   DUMMY_DLG_STR_OPTIMIZER_56KBSSTR,
   DUMMY_DLG_STR_OPTIMIZER_128KBSSTR,
   DUMMY_DLG_STR_OPTIMIZER_266KBSSTR,
   DUMMY_DLG_STR_OPTIMIZER_NEARESTCLRMATCHSTR,
   DUMMY_DLG_STR_OPTIMIZER_FLOYDSTEINBERGSTR,
   DUMMY_DLG_STR_OPTIMIZER_STUCKISTR,
   DUMMY_DLG_STR_OPTIMIZER_BURKESSTR,
   DUMMY_DLG_STR_OPTIMIZER_SIERRASTR,
   DUMMY_DLG_STR_OPTIMIZER_STEVENSONSTR,
   DUMMY_DLG_STR_OPTIMIZER_JARVUISSTR,
   DUMMY_DLG_STR_OPTIMIZER_ORDEREDSTR,
   DUMMY_DLG_STR_OPTIMIZER_CLUSTEREDSTR,
   DUMMY_DLG_STR_OPTIMIZER_COLORSSTR,
   DUMMY_DLG_STR_OPTIMIZER_COLORDEPTHSTR,
   DUMMY_DLG_STR_OPTIMIZER_PALETTESTR,
   DUMMY_DLG_STR_OPTIMIZER_AUTOMATICSTR,
   DUMMY_DLG_STR_OPTIMIZER_FIXEDSTR,
   DUMMY_DLG_STR_OPTIMIZER_CUSTOMSTR,
   DUMMY_DLG_STR_OPTIMIZER_DITHERINGSTR,
   DUMMY_DLG_STR_OPTIMIZER_NUMOFCOLORSSTR,
   DUMMY_DLG_STR_OPTIMIZER_ADDWINCOLORSSTR,
   DUMMY_DLG_STR_OPTIMIZER_TRANSPARENCYSTR,
   DUMMY_DLG_STR_OPTIMIZER_ENABLEDSTR,
   DUMMY_DLG_STR_OPTIMIZER_TOLERANCESTR,
   DUMMY_DLG_STR_OPTIMIZER_TRANSPARENTCLRSTR,
   DUMMY_DLG_STR_OPTIMIZER_INFORMATIONSSTR,
   DUMMY_DLG_STR_OPTIMIZER_BAUDRATESTR,
   DUMMY_DLG_STR_OPTIMIZER_ESTIMATEDTIMESTR,
   DUMMY_DLG_STR_OPTIMIZER_OPTIONSSTR,
   DUMMY_DLG_STR_OPTIMIZER_INTERLACEDSTR,
   DUMMY_DLG_STR_OPTIMIZER_IMAGETYPESTR,
   DUMMY_DLG_STR_OPTIMIZER_COMPRESSIONSTR, 
   DUMMY_DLG_STR_OPTIMIZER_PROGRESSIVESTR,
   DUMMY_DLG_STR_OPTIMIZER_SAVETHUMBNAILSTR,
   DUMMY_DLG_STR_OPTIMIZER_YUV444STR,
   DUMMY_DLG_STR_OPTIMIZER_YUV422STR,
   DUMMY_DLG_STR_OPTIMIZER_YUV411STR,

   //Image Formats File Association Dialog
   DUMMY_DLG_STR_FILEASSSTR,
   DUMMY_DLG_STR_FILEASS_FORMATSTR,
   DUMMY_DLG_STR_FILEASS_DESCRPSTR,
   DUMMY_DLG_STR_FILEASS_SELECTALLSTR,
   DUMMY_DLG_STR_FILEASS_SELECTNONESTR,

   //Image Mapper dialog
   DUMMY_DLG_STR_HTMLMAPSTR,
   DUMMY_DLG_STR_HTMLMAP_AREAINFOSTR,
   DUMMY_DLG_STR_HTMLMAP_URLSTR,
   DUMMY_DLG_STR_HTMLMAP_ALTTEXTSTR,
   DUMMY_DLG_STR_HTMLMAP_TARGETSTR,
   DUMMY_DLG_STR_HTMLMAP_OUTPUTSTR,
   DUMMY_DLG_STR_HTMLMAP_IMAGEFORMATSTR,
   DUMMY_DLG_STR_HTMLMAP_JPGFORMATSTR,
   DUMMY_DLG_STR_HTMLMAP_GIFFORMATSTR,
   DUMMY_DLG_STR_HTMLMAP_PNGFORMATSTR,
   DUMMY_DLG_STR_HTMLMAP_GENERATESELSTR,
   DUMMY_DLG_STR_HTMLMAP_OPTIMIZEDSTR,
   DUMMY_DLG_STR_HTMLMAP_ROLLOVERSTR,
   DUMMY_DLG_STR_HTMLMAP_EVENTSTR,
   DUMMY_DLG_STR_HTMLMAP_ONCLICKSTR,
   DUMMY_DLG_STR_HTMLMAP_ONDBLCLICKSTR,
   DUMMY_DLG_STR_HTMLMAP_ONMMOUSEDOWNSTR,
   DUMMY_DLG_STR_HTMLMAP_ONMMOUSEOVERSTR,
   DUMMY_DLG_STR_HTMLMAP_ONMMOUSEUPSTR,
   DUMMY_DLG_STR_HTMLMAP_ONMMOUSEOUTSTR,
   DUMMY_DLG_STR_HTMLMAP_ENABLEDSTR,
   DUMMY_DLG_STR_HTMLMAP_IMAGESTR,
   DUMMY_DLG_STR_HTMLMAP_CURSORPOSITIONSTR,
   DUMMY_DLG_STR_HTMLMAP_CLOSESTR,

   //Image Mapper dialog Error Messages
   DUMMY_DLG_STR_HTMLMAP_OUTMEMSTR,
   DUMMY_DLG_STR_HTMLMAP_PNFSTR,
   DUMMY_DLG_STR_HTMLMAP_FNFSTR,
   DUMMY_DLG_STR_HTMLMAP_FORMATSTR,
   DUMMY_DLG_STR_HTMLMAP_ACCESSDENIEDSTR,
   DUMMY_DLG_STR_HTMLMAP_ASSOCINCOMPLETESTR,
   DUMMY_DLG_STR_HTMLMAP_DDEBUSYSTR,
   DUMMY_DLG_STR_HTMLMAP_DDEFAILSTR,
   DUMMY_DLG_STR_HTMLMAP_DDETIMEOUTSTR,
   DUMMY_DLG_STR_HTMLMAP_DLLNOTFOUNDSTR,
   DUMMY_DLG_STR_HTMLMAP_NOASSOCSTR,
   DUMMY_DLG_STR_HTMLMAP_OOMSTR,
   DUMMY_DLG_STR_HTMLMAP_SHARESTR,
   DUMMY_DLG_STR_HTMLMAP_UNNONESTR,
   DUMMY_DLG_STR_HTMLMAP_DEFAULTSTR,

   // The New Dialog 
   DUMMY_DLG_STR_NEWSTR,
   DUMMY_DLG_STR_NEW_NAMESTR,
   DUMMY_DLG_STR_NEW_WIDTHSTR,
   DUMMY_DLG_STR_NEW_HEIGHTSTR,
   DUMMY_DLG_STR_NEW_PIXELSSTR,
   DUMMY_DLG_STR_NEW_INCHESSTR,
   DUMMY_DLG_STR_NEW_CENTIMETERSSTR,
   DUMMY_DLG_STR_NEW_RESOLUTIONSTR,
   DUMMY_DLG_STR_NEW_PIXELPERINCHESTR,
   DUMMY_DLG_STR_NEW_PIXELPERCMSTR,
   DUMMY_DLG_STR_NEW_IMAGETYPESTR,
   DUMMY_DLG_STR_NEW_2COLORSSTR,
   DUMMY_DLG_STR_NEW_16COLORSSTR,
   DUMMY_DLG_STR_NEW_256COLORSSTR,
   DUMMY_DLG_STR_NEW_256GRAYSCALESTR,
   DUMMY_DLG_STR_NEW_65536COLORSSTR,
   DUMMY_DLG_STR_NEW_167MCOLORSSTR,
   DUMMY_DLG_STR_NEW_IMAGEMEMSIZESTR,
   DUMMY_DLG_STR_NEW_BACKCOLORSTR,

   // Combine Image Dialog strings
   DUMMY_DLG_STR_COMBINESTR,
   DUMMY_DLG_STR_COMBINE_SOURCE1STR,
   DUMMY_DLG_STR_COMBINE_SOURCE2STR,
   DUMMY_DLG_STR_COMBINE_IMAGESTR,
   DUMMY_DLG_STR_COMBINE_CHANELSTR,
   DUMMY_DLG_STR_COMBINE_BLUESTR,
   DUMMY_DLG_STR_COMBINE_REDSTR,
   DUMMY_DLG_STR_COMBINE_GREENSTR,
   DUMMY_DLG_STR_COMBINE_INVERTSTR,
   DUMMY_DLG_STR_COMBINE_OPTIONSSTR,
   DUMMY_DLG_STR_COMBINE_FUNCTIONSTR,
   DUMMY_DLG_STR_COMBINE_ADDSTR,
   DUMMY_DLG_STR_COMBINE_SUBT1STR,
   DUMMY_DLG_STR_COMBINE_SUBT2STR,
   DUMMY_DLG_STR_COMBINE_MULTISTR,
   DUMMY_DLG_STR_COMBINE_DIV1STR,
   DUMMY_DLG_STR_COMBINE_DIV2STR,
   DUMMY_DLG_STR_COMBINE_MINSTR,
   DUMMY_DLG_STR_COMBINE_MAXSTR,
   DUMMY_DLG_STR_COMBINE_AVERAGESTR,
   DUMMY_DLG_STR_COMBINE_ANDSTR,
   DUMMY_DLG_STR_COMBINE_ORSTR,
   DUMMY_DLG_STR_COMBINE_XORSTR,
   DUMMY_DLG_STR_COMBINE_ALLSTR,
   DUMMY_DLG_STR_COMBINE_RESIZESTR,
   DUMMY_DLG_STR_COMBINE_RESULTINGSTR,
   DUMMY_DLG_STR_COMBINE_COLORDEPTHSTR,

   //Halftone dialog 
   DLG_STR_HALFTONE_TYPE,
   DLG_STR_HALFTONE_PRINT,
   DLG_STR_HALFTONE_VIEW,

   //Gamma Dialog
   DLG_STR_GAMMA,
   DLG_STR_GAMMA_RED,
   DLG_STR_GAMMA_GREEN,
   DLG_STR_GAMMA_BLUE,
   DLG_STR_GAMMA_ALLCHNNELS,

   //Underlay dialog
   DUMMY_DLG_STR_UNDERLAYSTR,
   DUMMY_DLG_STR_UNDERLAY_SETTINGSSTR,
   DUMMY_DLG_STR_UNDERLAY_STRETCHEDSTR,
   DUMMY_DLG_STR_UNDERLAY_TILEDSTR,
   DUMMY_DLG_STR_UNDERLAY_ERRSTR,
   DUMMY_DLG_STR_UNDERLAY_ERR_INITALSTR,
   
   //Selection Feather Dialog
   DUMMY_DLG_STR_FEATHERSTR,
   DUMMY_DLG_STR_FEATHER_PLACEMENTSTR,
   DUMMY_DLG_STR_FEATHER_GROWSTR,
   DUMMY_DLG_STR_FEATHER_INSIDESTR,
   DUMMY_DLG_STR_FEATHER_OUTSIDESTR,
   DUMMY_DLG_STR_FEATHER_FACTORSSTR,
   DUMMY_DLG_STR_FEATHER_SIZESTR,
   DUMMY_DLG_STR_FEATHER_SMOOTHNESSSTR,
   DUMMY_DLG_STR_FEATHER_FADERATESTR,
   DUMMY_DLG_STR_FEATHER_AUTOFADERATESTR,
   
   // Add Border Dialog strings
   DUMMY_DLG_STR_ADDBORDERSTR,
   DUMMY_DLG_STR_ADDBORDER_MARGINSSTR,
   DUMMY_DLG_STR_ADDBORDER_LEFTSTR,
   DUMMY_DLG_STR_ADDBORDER_RIGHTSTR,
   DUMMY_DLG_STR_ADDBORDER_TOPSTR,
   DUMMY_DLG_STR_ADDBORDER_BOTTOMSTR,
   DUMMY_DLG_STR_ADDBORDER_PLACEMENTSTR,
   DUMMY_DLG_STR_ADDBORDER_INSIDESTR,
   DUMMY_DLG_STR_ADDBORDER_OUTSIDESTR,
   DUMMY_DLG_STR_ADDBORDER_LOCKMARGINSSTR,
   DUMMY_DLG_STR_ADDBORDER_BORDERSTYLESTR,
   DUMMY_DLG_STR_ADDBORDER_SAMEIMAGESTR,
   DUMMY_DLG_STR_ADDBORDER_OPAQUESTR,
   DUMMY_DLG_STR_ADDBORDER_GRADIENTSTR,
   DUMMY_DLG_STR_ADDBORDER_TILESSTR,
   DUMMY_DLG_STR_ADDBORDER_OPTIONSSTR,
   DUMMY_DLG_STR_ADDBORDER_INSIDEOUTSTR,
   DUMMY_DLG_STR_ADDBORDER_CENTEROUT1STR,
   DUMMY_DLG_STR_ADDBORDER_CENTEROUT2STR,
   DUMMY_DLG_STR_ADDBORDER_STARTCOLORSTR,
   DUMMY_DLG_STR_ADDBORDER_ENDCOLORSTR,
   DUMMY_DLG_STR_ADDBORDER_TILEIMAGESTR,
   DUMMY_DLG_STR_ADDBORDER_PRESETSSTR,
   DUMMY_DLG_STR_ADDBORDER_USERDEFINESTR,
   DUMMY_DLG_STR_ADDBORDER_SIMPLESTR,
   DUMMY_DLG_STR_ADDBORDER_PRESET1STR,
   DUMMY_DLG_STR_ADDBORDER_PRESET2STR,
   DUMMY_DLG_STR_ADDBORDER_PRESET3STR,
   DUMMY_DLG_STR_ADDBORDER_PRESET4STR,
   DUMMY_DLG_STR_ADDBORDER_PRESET5STR,
   DUMMY_DLG_STR_ADDBORDER_PRESET6STR,
   DUMMY_DLG_STR_ADDBORDER_PRESET7STR,
   DUMMY_DLG_STR_ADDBORDER_PRESET8STR,
   DUMMY_DLG_STR_ADDBORDER_PRESET9STR,
   DUMMY_DLG_STR_ADDBORDER_SHADOWSSTR,
   DUMMY_DLG_STR_ADDBORDER_NONESHADOWSLSTSTR,
   DUMMY_DLG_STR_ADDBORDER_ADDSHADOWSLSTSTR,
   DUMMY_DLG_STR_ADDBORDER_LEFTLSTSTR,
   DUMMY_DLG_STR_ADDBORDER_RIGHTLSTSTR,
   DUMMY_DLG_STR_ADDBORDER_SURROUNDLSTSTR,
   DUMMY_DLG_STR_ADDBORDER_BUMPEDSTR,
   DUMMY_DLG_STR_ADDBORDER_SIZESTR,
   DUMMY_DLG_STR_ADDBORDER_EFFECTSTR,
   DUMMY_DLG_STR_ADDBORDER_NONEEFFECTSTR,
   DUMMY_DLG_STR_ADDBORDER_CURVEDINSTR,
   DUMMY_DLG_STR_ADDBORDER_CURVEDOUTSTR,
   DUMMY_DLG_STR_ADDBORDER_RAISEDSTR,
   DUMMY_DLG_STR_ADDBORDER_LOWEREDSTR,
   DUMMY_DLG_STR_ADDBORDER_INTENSITYSTR,
   DUMMY_DLG_STR_ADDBORDER_SMOOTHSTR,

   // Add Frame Dialog strings
   DUMMY_DLG_STR_ADDFRAMESTR,
   DUMMY_DLG_STR_ADDFRAME_OPTIONSSTR,
   DUMMY_DLG_STR_ADDFRAME_PLACEMENTSTR,
   DUMMY_DLG_STR_ADDFRAME_INSIDESTR,
   DUMMY_DLG_STR_ADDFRAME_OUTSIDESTR,
   DUMMY_DLG_STR_ADDFRAME_FRAMESTR,
   DUMMY_DLG_STR_ADDFRAME_MASKSTR,
   DUMMY_DLG_STR_ADDFRAME_USEMASKSTR,
   DUMMY_DLG_STR_ADDFRAME_TOLERANCESTR,
   DUMMY_DLG_STR_ADDFRAME_TRANSPARENTCOLORSTR,

   DLG_STR_FILE_GERBER,
   DLG_STR_FILE_WBMP,
   DLG_STR_FILE_PTOCA,
   DLG_STR_FILE_SCT,
   DLG_STR_FILE_SCT24,   
   DLG_STR_FILE_PCL,
   DLG_STR_FILE_AFP,
   DLG_STR_FILE_SHP,
   DLG_STR_SUB_ICA_UNCOMPRESSED,
   DLG_STR_SUB_RAWICA_UNCOMPRESSED,
   
   // old file format but updated
   DLG_STR_SUB_ICA_IBM_MMR,
   DLG_STR_SUB_RAWICA_IBM_MMR,
   
   DLG_STR_EXT_GERBER,
   DLG_STR_EXT_WBMP,
   DLG_STR_EXT_PTOCA, 
   DLG_STR_EXT_SCT,
   DLG_STR_EXT_PCL,
   DLG_STR_EXT_AFP,
   DLG_STR_EXT_SHP,

   DLG_STR_SUB_JPEG24_LAB_444,
   DLG_STR_SUB_JPEG24_LAB_422,
   DLG_STR_SUB_JPEG24_LAB_411,

   DUMMY_DLG_STR_PALEDTR_CLOSESTR,

   DLG_STR_GETSIZE_WIDTHNEW,
   DLG_STR_GETSIZE_HEIGHTNEW,
   DLG_STR_GETSIZE_HORIZONTALNEW,
   DLG_STR_GETSIZE_VERTICALNEW,

   DLG_STR_FILE_SMP,
   DLG_STR_EXT_SMP,
   DLG_STR_SUB_SMP_CCITT_GROUP3_1D,
   DLG_STR_SUB_SMP_CCITT_GROUP3_2D,
   DLG_STR_SUB_SMP_CCITT_GROUP4,
   DLG_STR_SUB_SMP_UNCOMPRESSED,

   DLG_STR_SUB_TGA_RLE,
   DLG_STR_SUB_TGA_UNCOMPRESSED,

   DUMMY_DLG_STR_FILEASS_ERR_CAPTION_WRITINGREGSTR,
   DUMMY_DLG_STR_FILEASS_ERR_BODY_WRITINGREGSTR,
   DUMMY_DLG_STR_FILEASS_ERR_BODY_ACCESSSTR,

   DUMMY_DLG_STR_HTMLMAP_BODY_SAVESUCCESSSTR,
   DUMMY_DLG_STR_HTMLMAP_CAPTION_SAVESUCCESSSTR,
   DUMMY_DLG_STR_HTMLMAP_BODY_SAVEERRORSTR,
   DUMMY_DLG_STR_HTMLMAP_CAPTION_SAVEERRORSTR,
   DUMMY_DLG_STR_HTMLMAP_BODY_IMAGEWRITINGSTR,
   
   DUMMY_DLG_STR_COMBINE_ERR_BODY_INITIALIZINGSTR,
   DUMMY_DLG_STR_COMBINE_ERR_CAPTION_ERRORSTR,
   
   DUMMY_DLG_STR_PRINTMULT_STATUSDLG_CAPTIONSTR,
   DUMMY_DLG_STR_PRINTMULT_STATUSDLG_SCALESTR,
   DUMMY_DLG_STR_PRINTMULT_STATUSDLG_SIZESTR,
   DUMMY_DLG_STR_PRINTMULT_STATUSDLG_PIXLESSTR,
   DUMMY_DLG_STR_PRINTMULT_ERR_BODY_MARGINVALUESTR,
   DUMMY_DLG_STR_PRINTMULT_ERR_CAPTION_ERRORSTR,

   // Convert to Colored Gray dialog strings
   DUMMY_DLG_STR_COLOREDGRAY_CAPTIONSTR,
   DUMMY_DLG_STR_COLOREDGRAY_COLORFACTSTR,
   DUMMY_DLG_STR_COLOREDGRAY_GRAYFACTSTR,
   DUMMY_DLG_STR_COLOREDGRAY_REDSTR,
   DUMMY_DLG_STR_COLOREDGRAY_GREENSTR,
   DUMMY_DLG_STR_COLOREDGRAY_BLUESTR,
   DUMMY_DLG_STR_COLOREDGRAY_REDGRAYSTR,
   DUMMY_DLG_STR_COLOREDGRAY_GREENGRAYSTR,
   DUMMY_DLG_STR_COLOREDGRAY_BLUEGRAYSTR,

   // Gaussiam Filter dialog strings
   DUMMY_DLG_STR_GAUSSIANFILTER_CAPTIONSTR,
   DUMMY_DLG_STR_GAUSSIANFILTER_RADIUSSTR,

   // Unsharp Mask dialog strings
   DUMMY_DLG_STR_UNSHARPMASK_CAPTIONSTR,
   DUMMY_DLG_STR_UNSHARPMASK_ADJUSTMENTSTR,
   DUMMY_DLG_STR_UNSHARPMASK_RADIUSSTR,
   DUMMY_DLG_STR_UNSHARPMASK_THERSHOLDSTR,
   DUMMY_DLG_STR_UNSHARPMASK_COLORESPACESTR,
   DUMMY_DLG_STR_UNSHARPMASK_RGBSTR,
   DUMMY_DLG_STR_UNSHARPMASK_YUVSTR,

   // Antialias dialog strings
   DUMMY_DLG_STR_ANTIALIAS_CAPTIONSTR,
   DUMMY_DLG_STR_ANTIALIAS_THRESHOLDSTR,
   DUMMY_DLG_STR_ANTIALIAS_DIMSTR,
   DUMMY_DLG_STR_ANTIALIAS_FILTERSTR,
   DUMMY_DLG_STR_ANTIALIAS_ANTIALIAS_1STR,
   DUMMY_DLG_STR_ANTIALIAS_ANTIALIAS_2STR,
   DUMMY_DLG_STR_ANTIALIAS_ANTIALIAS_3STR,
   DUMMY_DLG_STR_ANTIALIAS_ANTIALIAS_DIAGSTR,
   DUMMY_DLG_STR_ANTIALIAS_ANTIALIAS_HORZSTR,
   DUMMY_DLG_STR_ANTIALIAS_ANTIALIAS_VERTSTR,

   // Edge Detector Colors dialog strings
   DUMMY_DLG_STR_EDGEDETECTOR_CAPTIONSTR,
   DUMMY_DLG_STR_EDGEDETECTOR_THRESHOLDSTR,
   DUMMY_DLG_STR_EDGEDETECTOR_FILTERSTR,

   DUMMY_DLG_STR_EDGEDETECTOR_EDG_SOBEL_VERTSTR,
   DUMMY_DLG_STR_EDGEDETECTOR_EDG_SOBEL_HORZSTR,
   DUMMY_DLG_STR_EDGEDETECTOR_EDG_SOBEL_ALLSTR,
   DUMMY_DLG_STR_EDGEDETECTOR_EDG_PREWITT_VERTSTR,
   DUMMY_DLG_STR_EDGEDETECTOR_EDG_PREWITT_HORZSTR,
   DUMMY_DLG_STR_EDGEDETECTOR_EDG_PREWITT_ALLSTR,
   DUMMY_DLG_STR_EDGEDETECTOR_EDG_LAPLACE_1STR,
   DUMMY_DLG_STR_EDGEDETECTOR_EDG_LAPLACE_2STR,
   DUMMY_DLG_STR_EDGEDETECTOR_EDG_LAPLACE_3STR,
   DUMMY_DLG_STR_EDGEDETECTOR_EDG_LAPLACE_DIAGSTR,
   DUMMY_DLG_STR_EDGEDETECTOR_EDG_LAPLACE_HORZSTR,
   DUMMY_DLG_STR_EDGEDETECTOR_EDG_LAPLACE_VERTSTR,
   DUMMY_DLG_STR_EDGEDETECTOR_EDG_GRADIENT_NSTR,
   DUMMY_DLG_STR_EDGEDETECTOR_EDG_GRADIENT_NESTR,
   DUMMY_DLG_STR_EDGEDETECTOR_EDG_GRADIENT_ESTR,
   DUMMY_DLG_STR_EDGEDETECTOR_EDG_GRADIENT_SESTR,
   DUMMY_DLG_STR_EDGEDETECTOR_EDG_GRADIENT_SSTR,
   DUMMY_DLG_STR_EDGEDETECTOR_EDG_GRADIENT_SWSTR,
   DUMMY_DLG_STR_EDGEDETECTOR_EDG_GRADIENT_WSTR,
   DUMMY_DLG_STR_EDGEDETECTOR_EDG_GRADIENT_NWSTR,

   // Remove Red Eye Detector Colors dialog strings
   DUMMY_DLG_STR_REMOVEREDEYE_CAPTIONSTR,
   DUMMY_DLG_STR_REMOVEREDEYE_LIGHTNESSSTR,
   DUMMY_DLG_STR_REMOVEREDEYE_THRESHOLDSTR,
   DUMMY_DLG_STR_REMOVEREDEYE_NEWCOLORSTR,

   // Motion Blur dialog strings
   DUMMY_DLG_STR_MOTIONBLUR_CAPTIONSTR,
   DUMMY_DLG_STR_MOTIONBLUR_DIMSTR,
   DUMMY_DLG_STR_MOTIONBLUR_ANGLESTR,
   DUMMY_DLG_STR_MOTIONBLUR_UNIDIRECTIONALSTR,
   
   // Gray Scale dialog strings
   DUMMY_DLG_STR_GRAYSCALE_CAPTIONSTR,
   DUMMY_DLG_STR_GRAYSCALE_WEIGHTSTR,
   DUMMY_DLG_STR_GRAYSCALE_REDSTR,
   DUMMY_DLG_STR_GRAYSCALE_GREENSTR,
   DUMMY_DLG_STR_GRAYSCALE_BLUESTR,

   // Updates on the Half tone dialog strings
   DLG_STR_HALFTONE_DIM,
   DLG_STR_HALFTONE_RECT,
   DLG_STR_HALFTONE_CIRC,
   DLG_STR_HALFTONE_ELLIPS,
   DLG_STR_HALFTONE_RAND,
   DLG_STR_HALFTONE_LINEAR,

   // Histogram dialog strings
   DUMMY_DLG_STR_HISTOGRAM_CAPTIONSTR,
   DUMMY_DLG_STR_HISTOGRAM_CLOSESTR,
   DUMMY_DLG_STR_HISTOGRAM_CHANNELSTR,
   DUMMY_DLG_STR_HISTOGRAM_MEANSTR,
   DUMMY_DLG_STR_HISTOGRAM_MEDIANSTR,
   DUMMY_DLG_STR_HISTOGRAM_PIXELSSTR,
   DUMMY_DLG_STR_HISTOGRAM_LEVELSTR,
   DUMMY_DLG_STR_HISTOGRAM_COUNTSTR,
   DUMMY_DLG_STR_HISTOGRAM_PERCENTAGESTR,
   DUMMY_DLG_STR_HISTOGRAM_MASTERSTR,
   DUMMY_DLG_STR_HISTOGRAM_REDSTR,
   DUMMY_DLG_STR_HISTOGRAM_GREENSTR,
   DUMMY_DLG_STR_HISTOGRAM_BLUESTR,
   DUMMY_DLG_STR_HISTOGRAM_VIEWSTR,
   DUMMY_DLG_STR_HISTOGRAM_LINESTR,
   DUMMY_DLG_STR_HISTOGRAM_AREASTR,

   // The Strins of toolbar tooltip in the dialogs 
   DLG_STR_TOOLTIP_ZOOMNORMALSTR,
   DLG_STR_TOOLTIP_ZOOMTOFITSTR,

   DLG_STR_CMWRESPROMPT,
   DLG_STR_CMWRESLABEL,
   DLG_STR_J2KRESPROMPT,
   DLG_STR_J2KRESLABEL,
   
   DLG_STR_SUB_RAS_RLE,
   DLG_STR_SUB_RAS_UNCOMPRESSED,
   
   DLG_STR_PCT16,
   DLG_STR_FILE_PSP1,
   DLG_STR_FILE_PSP4,
   DLG_STR_FILE_PSP8,
   DLG_STR_FILE_PSP24,
   DLG_STR_EXT_PSP,
   DLG_STR_SUB_PSP_RLE,
   DLG_STR_SUB_PSP_UNCOMPRESSED,

   DLG_STR_FILE_ECW,
   DLG_STR_EXT_ECW,

   DLG_STR_FILE_SVG,
   DLG_STR_EXT_SVG,
   DLG_STR_SUB_SVG,
   DLG_STR_SUB_SVG_EMBED_IMAGES,

   DLG_STR_FILE_TIFX1,
   DLG_STR_SUB_TIFX_CCITT_G4,
   DLG_STR_SUB_TIFX_CCITT_G3_1D,
   DLG_STR_SUB_TIFX_CCITT_G3_2D,
   DLG_STR_SUB_TIFX_JBIG,
   DLG_STR_FILE_TIFX3,
   DLG_STR_FILE_TIFX8,
   DLG_STR_FILE_TIFX24,
   DLG_STR_EXT_TIFX,

   // Vector Options dialog
   DLG_STR_VECTOROPTIONS_CAPTION,
   DLG_STR_VECTOROPTIONS_DWF,
   DLG_STR_VECTOROPTIONS_CGM,
   DLG_STR_VECTOROPTIONS_CMX,
   DLG_STR_VECTOROPTIONS_PCL,
   DLG_STR_VECTOROPTIONS_VECTOR_DUMP,
   DLG_STR_VECTOROPTIONS_PCT,
   DLG_STR_VECTOROPTIONS_DRW,
   DLG_STR_VECTOROPTIONS_INTERGRAPH_VECTOR,
   DLG_STR_VECTOROPTIONS_GERBER,
   DLG_STR_VECTOROPTIONS_SHP,
   DLG_STR_VECTOROPTIONS_SVG,
   DLG_STR_VECTOROPTIONS_VWPG,
   DLG_STR_VECTOROPTIONS_VIEWPORT,
   DLG_STR_VECTOROPTIONS_WIDTH,
   DLG_STR_VECTOROPTIONS_HEIGHT,
   DLG_STR_VECTOROPTIONS_MODE,
   DLG_STR_VECTOROPTIONS_MODE_USE_BEST,
   DLG_STR_VECTOROPTIONS_MODE_USE_WIDTH,
   DLG_STR_VECTOROPTIONS_MODE_USE_HEIGHT,
   DLG_STR_VECTOROPTIONS_MODE_USE_WIDTH_HEIGHT,

   // DFX and DWG Options dialog
   DLG_STR_DFXANDDWGOPTIONS_CAPTION,
   DLG_STR_DFXANDDWGOPTIONS_VIEWPORT,
   DLG_STR_DFXANDDWGOPTIONS_WIDTH,
   DLG_STR_DFXANDDWGOPTIONS_HEIGHT,
   DLG_STR_DFXANDDWGOPTIONS_MODE,
   DLG_STR_DFXANDDWGOPTIONS_MODE_USE_BEST,
   DLG_STR_DFXANDDWGOPTIONS_MODE_USE_WIDTH,
   DLG_STR_DFXANDDWGOPTIONS_MODE_USE_HEIGHT,
   DLG_STR_DFXANDDWGOPTIONS_MODE_USE_WIDTH_HEIGHT,
   DLG_STR_DFXANDDWGOPTIONS_BACKGROUND,
   DLG_STR_DFXANDDWGOPTIONS_BACKGROUND_BLACKONWHITE,
   DLG_STR_DFXANDDWGOPTIONS_BACKGROUND_WHITEONBLACK,

   // PLT Options dialog
   DLG_STR_PLTOPTIONS_CAPTION,
   DLG_STR_PLTOPTIONS_VIEWPORT,
   DLG_STR_PLTOPTIONS_WIDTH,
   DLG_STR_PLTOPTIONS_HEIGHT,
   DLG_STR_PLTOPTIONS_MODE,
   DLG_STR_PLTOPTIONS_MODE_USE_BEST,
   DLG_STR_PLTOPTIONS_MODE_USE_WIDTH,
   DLG_STR_PLTOPTIONS_MODE_USE_HEIGHT,
   DLG_STR_PLTOPTIONS_MODE_USE_WIDTH_HEIGHT,
   DLG_STR_PLTOPTIONS_PEN,
   DLG_STR_PLTOPTIONS_PENWIDTH,
   DLG_STR_PLTOPTIONS_PENNUMBER,
   DLG_STR_PLTOPTIONS_PENCOLOR,
   DLG_STR_PLTOPTIONS_PEN_1,
   DLG_STR_PLTOPTIONS_PEN_2,
   DLG_STR_PLTOPTIONS_PEN_3,
   DLG_STR_PLTOPTIONS_PEN_4,
   DLG_STR_PLTOPTIONS_PEN_5,
   DLG_STR_PLTOPTIONS_PEN_6,
   DLG_STR_PLTOPTIONS_PEN_7,
   DLG_STR_PLTOPTIONS_PEN_8,

   // Messges in the save dialog
   DLG_STR_SAVE_FILE_MULTIPAGE_UPDATE,
   DLG_STR_SAVE_FILE_OVERWRITE,

   DLG_STR_SUB_CLP_UNCOMPRESSED,
   DLG_STR_SUB_CLP_RLE,
      
   DLG_STR_MAX
};

//General Functions
//Font Functions
HFONT EXT_FUNCTION L_DlgSetFont ( HFONT hFont ) ; 

//String Functions
L_INT EXT_FUNCTION L_DlgGetStringLen ( L_UINT32 uString, L_UINT L_FAR * puLen ) ;
L_INT EXT_FUNCTION L_DlgSetString    ( L_UINT32 uString, L_TCHAR L_FAR * pString ) ;  
L_INT EXT_FUNCTION L_DlgGetString    ( L_UINT32 uString, L_TCHAR L_FAR * pString ) ;  

L_INT EXT_FUNCTION L_DlgFileOpen ( HWND hWndOwner,
                                   LPOPENFILENAME pOpenFileName, 
                                   LPFILEOPENPARM pFileOpenParm, 
                                   L_UINT32 uFlags, 
                                   LTCOMMDLGHELPCB pfnCallback, 
                                   L_VOID L_FAR* pUserData ) ;

L_INT EXT_FUNCTION L_DlgFileSave ( HWND hWndOwner,
                                   LPOPENFILENAME pOpenFileName, 
                                   LPFILESAVEPARM pFileSaveParm, 
                                   L_UINT32 uFlags, 
                                   LPFILESAVEFORMAT pSaveFormats,
                                   L_INT nSaveFormats,
                                   LTCOMMDLGHELPCB pfnCallback, 
                                   L_VOID L_FAR* pUserData ) ;

L_INT EXT_FUNCTION L_DlgGetNoise ( HWND hWndOwner,
                                   pBITMAPHANDLE pBitmap, 
                                   LPGETNOISEDLGPARM pDlgParams ,
                                   L_UINT32 uFlags, 
                                   LTCOMMDLGHELPCB pfnCallback, 
                                   L_VOID L_FAR* pUserData ) ;

L_INT EXT_FUNCTION L_DlgGetChange ( HWND hWndOwner,
                                    pBITMAPHANDLE pBitmap, 
                                    LPGETCHANGEDLGPARM pDlgParams ,
                                    L_UINT32 uFlags, 
                                    LTCOMMDLGHELPCB pfnCallback, 
                                    L_VOID L_FAR* pUserData ) ;

L_INT EXT_FUNCTION L_DlgHalftone ( HWND hWndOwner,
                                   pBITMAPHANDLE pBitmap, 
                                   LPHALFTONEDLGPARM pDlgParams ,
                                   L_UINT32 uFlags, 
                                   LTCOMMDLGHELPCB pfnCallback, 
                                   L_VOID L_FAR* pUserData ) ;

L_INT EXT_FUNCTION L_DlgColorRes ( HWND hWndOwner, 
                                   pBITMAPHANDLE pBitmap, 
                                   LPCOLORRESDLGPARM pDlgParams, 
                                   L_UINT32 uFlags, 
                                   L_UINT32 uExFlags,
                                   LTCOMMDLGHELPCB pfnCallback, 
                                   L_VOID L_FAR * pUserData ) ;

L_INT EXT_FUNCTION L_DlgGetAngle ( HWND hWndOwner, 
                                   pBITMAPHANDLE pBitmap, 
                                   LPGETANGLEDLGPARM pDlgParams, 
                                   L_UINT32 uFlags, 
                                   LTCOMMDLGHELPCB pfnCallback, 
                                   L_VOID L_FAR * pUserData ) ;

L_INT EXT_FUNCTION L_DlgGetSize ( HWND hWndOwner, 
                                  pBITMAPHANDLE pBitmap, 
                                  LPGETSIZEDLGPARM pDlgParams, 
                                  L_UINT32 uFlags, 
                                  LTCOMMDLGHELPCB pfnCallback, 
                                  L_VOID L_FAR * pUserData ) ;

L_INT EXT_FUNCTION L_DlgGetEmboss ( HWND hWndOwner, 
                                    pBITMAPHANDLE pBitmap, 
                                    LPGETEMBOSSDLGPARM pDlgParams, 
                                    L_UINT32 uFlags, 
                                    LTCOMMDLGHELPCB pfnCallback, 
                                    L_VOID L_FAR * pUserData ) ;

L_INT EXT_FUNCTION L_DlgGetFilter ( HWND hWndOwner, 
                                    pBITMAPHANDLE pBitmap, 
                                    LPGETFILTERDLGPARM pDlgParams, 
                                    L_UINT32 uFlags, 
                                    LTCOMMDLGHELPCB pfnCallback, 
                                    L_VOID L_FAR * pUserData ) ;

L_INT EXT_FUNCTION L_DlgGetGamma ( HWND hWndOwner, 
                                   pBITMAPHANDLE pBitmap, 
                                   LPGETGAMMADLGPARM pDlgParams, 
                                   L_UINT32 uFlags, 
                                   LTCOMMDLGHELPCB pfnCallback, 
                                   L_VOID L_FAR * pUserData ) ;

L_INT EXT_FUNCTION L_DlgGetRange ( HWND hWndOwner, 
                                   pBITMAPHANDLE pBitmap, 
                                   LPGETRANGEDLGPARM pDlgParams, 
                                   L_UINT32 uFlags, 
                                   LTCOMMDLGHELPCB pfnCallback, 
                                   L_VOID L_FAR * pUserData ) ;

L_INT EXT_FUNCTION L_DlgContourFilter ( HWND hWndOwner, 
                                        pBITMAPHANDLE pBitmap, 
                                        LPCONTOURFILTERDLGPARM pDlgParams, 
                                        L_UINT32 uFlags, 
                                        LTCOMMDLGHELPCB pfnCallback, 
                                        L_VOID L_FAR * pUserData ) ;

L_INT EXT_FUNCTION L_DlgGetShape  ( HWND hWndOwner, 
                                    pBITMAPHANDLE pBitmap, 
                                    pBITMAPHANDLE pBackgroundBitmap, 
                                    LPSHAPEDLGPARM pShapeDlgParm, 
                                    L_UINT32 uFlags, 
                                    LTCOMMDLGHELPCB pfnCallback, 
                                    L_VOID L_FAR * pUserData ) ;  

L_INT EXT_FUNCTION L_DlgGetDirectory  ( HWND hWndOwner,
                                        LPGETDIRECTORYDLGPARM pDlgParams,
                                        L_UINT32 uFlags, 
                                        LTCOMMDLGHELPCB pfnCallback, 
                                        L_VOID L_FAR * pUserData) ;

L_INT EXT_FUNCTION L_DlgGetEffect ( HWND hWndOwner,
                                    pBITMAPHANDLE pBitmap, 
                                    EFXDLGPARM L_FAR * pEfxDlgParm, 
                                    L_UINT32 uFlags, 
                                    LTCOMMDLGHELPCB pfnCallback, 
                                    L_VOID L_FAR* pUserData ) ;

L_INT EXT_FUNCTION L_DlgGetTransition ( HWND hWndOwner,
                                        pBITMAPHANDLE pBitmap, 
                                        TRANSDLGPARM L_FAR * pTransDlgParm, 
                                        L_UINT32 uFlags, 
                                        LTCOMMDLGHELPCB pfnCallback, 
                                        L_VOID L_FAR* pUserData) ;

L_INT EXT_FUNCTION L_DlgGetGradient ( HWND hWndOwner,
                                      pBITMAPHANDLE pBitmap,
                                      GRADDLGPARM L_FAR * pGradDlgParm,
                                      L_UINT32 uFlags,
                                      LTCOMMDLGHELPCB pfnCallback, 
                                      L_VOID L_FAR* pUserData ) ;

L_INT EXT_FUNCTION L_DlgGetText ( HWND hWndOwner, 
                                  pBITMAPHANDLE pBitmap,
                                  pBITMAPHANDLE pForegroundBitmap,
                                  TEXTDLGPARM L_FAR * pTextDlgParm,
                                  L_UINT32 uFlags, 
                                  LTCOMMDLGHELPCB pfnCallback, 
                                  L_VOID L_FAR* pUserData ) ;

L_INT EXT_FUNCTION L_DlgWindowLevel ( HWND hWndOwner, 
                                      pBITMAPHANDLE pBitmap, 
                                      LPWINDOWLEVELDLGPARM pDlgParams,
                                      L_UINT32 uFlags, 
                                      LTCOMMDLGHELPCB pfnCallback, 
                                      L_VOID L_FAR* pUserData ) ;


#undef _HEADER_ENTRY_
#include "ltpck.h"


#endif

