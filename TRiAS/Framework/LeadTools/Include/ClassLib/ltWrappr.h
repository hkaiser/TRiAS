/*----------------------------------------------------------------------------+
| LEADTOOLS for Windows -                                                     |
| Copyright (c) 1991-2000 LEAD Technologies, Inc.                             |
| All Rights Reserved.                                                        |
|-----------------------------------------------------------------------------|
| PROJECT   : LEAD wrappers                                                   |
| FILE NAME :                                                                 |
| DESC      :                                                                 |
+----------------------------------------------------------------------------*/
#ifndef  _LEAD_WRAPPER_H_
#define  _LEAD_WRAPPER_H_

/*---------------------------------------------------------------+
| LEAD WRAPPER CLASSES PROTOTYPES                                |
+---------------------------------------------------------------*/
class LBitmapDictionary;
class LDictionary;
class LBase;
class LBitmapBase;    
class LInet;           
class LDraw;            
class LAnnToolBar;            
class LInetServer;
class LPaint;        
class LAnnotation;   
class LInetClient;
class LPaintEffect;
class LAnnAutomation;
class LScan;
class LAnnContainer;
class LBitmap;
class LTwain;
class LAnnText;
class LBitmapWindow;
class LIsis;
class LAnnStamp;
class LAnimationWindow;
class LBaseFile;
class LAnnLine;
class LAnnotationWindow;
class LFile;
class LAnnPolyline;
class LMemoryFile;
class LAnnPolygon;
class LSettings;
class LAnnFreeHand;
class LBitmapSettings;
class LAnnRectangle;
class LFileSettings;
class LAnnEllipse;
class LPrint;
class LAnnPointer;
class LDialog;             
class LAnnButton;
class LBitmapRgn;          
class LAnnHilite;
class LPlayBack;          
class LAnnRedact;
class LChange;            
class LAnnAudioClip;
class LBuffer;            
class LAnnHotSpot;
class LScreenCapture;     
class LAnnRuler;
class LBitmapList;         
class LAnnNote;
class LImageListControl;
class LVectorBase; 
class LVectorDialog;
class LVectorFile;
class LVectorMemoryFile;
class LVectorLayer;
class LVectorObject;
class LVectorGroup;
class LVectorWindow;
class LBarCode;
class LToolbar;
class LContainer;
class LAutomation;

class LInetHttp;
class LInetFtp;

class LRasterPaint;
class LRasterDialog;
class LRasterPaintWindow;

/*----------------------------------------------------------------------------+
| INCLUDES                                                                    |
+----------------------------------------------------------------------------*/
//--STANDARD INCLUDE FILES-----------------------------------------------------
#ifndef STRICT
   #define STRICT
#endif

#if _WIN32_WINNT < 0x0400
#define _WIN32_WINNT 0x0400
#endif

#include <windows.h>

typedef COLORREF                       L_COLOR;

//--LEAD INCLUDE FILES---------------------------------------------------------
//Comment this line to compile and link the LEAD Class Library
//directly with LEAD API DLL's
#define USE_POINTERS_TO_LEAD_FUNCTIONS

#ifdef USE_POINTERS_TO_LEAD_FUNCTIONS

   #include "..\ltsys.h"
   #include "..\lttyp.h"
   #include "..\lterr.h"
   #include "..\ltkrn.h"
   #include "..\ltdis.h"
   #include "..\ltimg.h"
   #include "..\lvkrn.h"
   #include "..\ltfil.h"
   #include "..\lttwn.h"
   #include "..\ltlck.h"
   #include "..\ltwnd.h"
   #include "..\ltann.h"
   #include "..\ltefx.h"
   #include "..\ltisi.h"
   #include "..\ltscr.h"
   #include "..\ltnet.h"
   #include "..\ltdlg.h"
   #include "..\lttmb.h"
   #include "..\ltlst.h"
   #include "..\lvkrn.h"
   #include "..\lvdlg.h"
   #include "..\ltbar.h"

   #include "..\ltTlb.h"
   #include "..\ltCon.h"
   #include "..\ltPnt.h"
   #include "..\ltAut.h"
   #include "..\ltWeb.h"
   #include "..\Ltsgm.h"

   #include "..\ltPdg.h"

#else // ! USE_POINTERS_TO_LEAD_FUNCTIONS
   #include "..\..\include\l_bitmap.h"
   #include "..\..\include\ltIsi.h"
   #include "..\..\include\ltScr.h"
   #include "..\..\include\ltNet.h"
#endif //USE_POINTERS_TO_LEAD_FUNCTIONS

#define _HEADER_ENTRY_8_
#include "..\ltpck.h"

//--LEAD WRAPPER INCLUDE FILES-------------------------------------------------
#include "ltcDefs.h"
#include "ltcWrpEr.h"
#include "ltcEnums.h"
#include "ltcTypDf.h"
#include "ltcFTypD.h"
#include "ltcExtrn.h"
#include "ltcFMcro.h"

//--FRIEND FUNCTIONS ----------------------------------------------------------
LWRP_EXPORT LBitmapBase L_FAR*  LEAD_GetBitmapObject(LWRAPPERBITMAPMEMBER nClassType,LBase L_FAR* This,LPLEADCREATEOBJECT pCreateObj);
LWRP_EXPORT LBase L_FAR*        LEAD_GetObject(LWRAPPEROBJECTTYPE nType,LBase L_FAR* This,LPLEADCREATEOBJECT pCreateObj);

//--LEAD WRAPPER CLASSES HEADER FILES------------------------------------------
#include "ltcMacro.h"
#include "ltcBase.h"
#include "ltcBBase.h"
#include "ltcBtmp.h"
#include "ltcBList.h"
#include "ltcBuffr.h"
#include "ltcChng.h"
#include "ltcDlg.h"
#include "ltcDraw.h"
#include "ltcFile.h"
#include "ltcPlybk.h"
#include "ltcPrnt.h"
#include "ltcRgn.h"
#include "ltcScnnr.h"
#include "ltcSetng.h"
#include "ltcScr.h"
#include "ltcAnn.h"
#include "ltcInet.h"
//#include "ltcMMcp.h"
//#include "ltcMulti.h"
#include "ltcDictn.h"
#include "ltcBWnd.h"
#include "ltcAnim.h"
#include "ltcAnnWn.h"
#include "ltcImLst.h"


#include "ltcVBase.h"
#include "ltcVDlg.h"
#include "ltcVFile.h"
#include "ltcVMFil.h"
#include "ltcVWnd.h"
#include "ltcVLayr.h"
#include "ltcVGrp.h"
#include "ltcVObj.h"

//#include "ltcVNone.h" 
#include "ltcBar.h"
#include "ltcTb.h"
#include "ltcCon.h"
#include "ltcAut.h"

#include "ltcHttp.h"
#include "ltcFtp.h"
#include "ltcSeg.h"

#include "ltcRst.h"
#include "ltcRstDlg.h"
#include "ltcRstWd.h"

#define WRPUNLOCKSUPPORT() \
   LSettings::UnlockSupport(L_SUPPORT_DOCUMENT, L_KEY_DOCUMENT); \
   LSettings::UnlockSupport(L_SUPPORT_GIFLZW, L_KEY_GIFLZW); \
   LSettings::UnlockSupport(L_SUPPORT_TIFLZW, L_KEY_TIFLZW); \
   LSettings::UnlockSupport(L_SUPPORT_FPXEXTENSIONS, L_KEY_FPXEXTENSIONS); \
   LSettings::UnlockSupport(L_SUPPORT_MEDICAL, L_KEY_MEDICAL); \
   LSettings::UnlockSupport(L_SUPPORT_OCR, L_KEY_OCR); \
   LSettings::UnlockSupport(L_SUPPORT_MULTIMEDIA, L_KEY_MULTIMEDIA); \
   LSettings::UnlockSupport(L_SUPPORT_VECTOR, L_KEY_VECTOR); \
   LSettings::UnlockSupport(L_SUPPORT_MEDICAL_NET, L_KEY_MEDICAL_NET); \
   LSettings::UnlockSupport(L_SUPPORT_BARCODES_1D, L_KEY_BARCODES_1D); \
   LSettings::UnlockSupport(L_SUPPORT_BARCODES_2D_READ, L_KEY_BARCODES_2D_READ); \
   LSettings::UnlockSupport(L_SUPPORT_BARCODES_2D_WRITE, L_KEY_BARCODES_2D_WRITE); \
   LSettings::UnlockSupport(L_SUPPORT_BARCODES_PDF_READ, L_KEY_BARCODES_PDF_READ); \
   LSettings::UnlockSupport(L_SUPPORT_BARCODES_PDF_WRITE, L_KEY_BARCODES_PDF_WRITE); \
   LSettings::UnlockSupport(L_SUPPORT_INTERNET, L_KEY_INTERNET); \
   LSettings::UnlockSupport(L_SUPPORT_VECTOR_DWG, L_KEY_VECTOR_DWG); \
   LSettings::UnlockSupport(L_SUPPORT_VECTOR_DXF, L_KEY_VECTOR_DXF); \
   LSettings::UnlockSupport(L_SUPPORT_VECTOR_MISC, L_KEY_VECTOR_MISC); \
   LSettings::UnlockSupport(L_SUPPORT_VECTOR_DWF, L_KEY_VECTOR_DWF); \
   LSettings::UnlockSupport(L_SUPPORT_PDF       , L_KEY_PDF); \
   LSettings::UnlockSupport(L_SUPPORT_VECTOR_VIEW, L_KEY_VECTOR_VIEW);  \
   LSettings::UnlockSupport(L_SUPPORT_DIGITALPAINT, L_KEY_DIGITALPAINT);\
   LSettings::UnlockSupport(L_SUPPORT_J2K, L_KEY_J2K); \
   LSettings::UnlockSupport(L_SUPPORT_CMW, L_KEY_CMW); \
   LSettings::UnlockSupport(L_SUPPORT_MRC, L_KEY_MRC); \
   LSettings::UnlockSupport(L_SUPPORT_DICOM, L_KEY_DICOM); \
   LSettings::UnlockSupport(L_SUPPORT_EXTGRAY, L_KEY_EXTGRAY); \
   LSettings::UnlockSupport(L_SUPPORT_BITONAL, L_KEY_BITONAL); \
   LSettings::UnlockSupport(L_SUPPORT_MEDICAL_SECURITY, L_KEY_MEDICAL_SECURITY); \
   LSettings::UnlockSupport(L_SUPPORT_PDF_SAVE, L_KEY_PDF_SAVE); \
   LSettings::UnlockSupport(L_SUPPORT_OCR_PDF_OUTPUT, L_KEY_OCR_PDF_OUTPUT); \
   LSettings::UnlockSupport(L_SUPPORT_BARCODES_DATAMATRIX_READ, L_KEY_BARCODES_DATAMATRIX_READ); \
   LSettings::UnlockSupport(L_SUPPORT_BARCODES_DATAMATRIX_WRITE, L_KEY_BARCODES_DATAMATRIX_WRITE);


#undef _HEADER_ENTRY_8_
#include "..\..\include\ltpck.h"

/*================================================================= EOF =====*/
#endif //_LEAD_WRAPPER_H_
