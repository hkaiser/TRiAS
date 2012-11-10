/*
 *
 *	_ p r i n _ i m . c x x
 *
 *  Copyright (c) 1992 Trischford Limited 
 *  ( A wholly owned subsidary of Computer Associates International, Inc)
 *  All Rights Reserved
 *
 *	Version 3.1			Nov 1992
 *
 *	Mods Log:
 *	1.0	sm		Original version
 *
 */
#include "tfrmpre.hxx"

#include <commdlg.h>


// Get Dev caps
/* Device Parameters for GetDeviceCaps() */
#define DRIVERVERSION 0     /* Device driver version			*/
#define TECHNOLOGY    2     /* Device classification			*/
#define HORZSIZE      4     /* Horizontal size in millimeters		*/
#define VERTSIZE      6     /* Vertical size in millimeters		*/
#define HORZRES       8     /* Horizontal width in pixels		*/
#define VERTRES       10    /* Vertical width in pixels 		*/
#define BITSPIXEL     12    /* Number of bits per pixel 		*/
#define PLANES	      14    /* Number of planes 			*/
#define NUMBRUSHES    16    /* Number of brushes the device has 	*/
#define NUMPENS       18    /* Number of pens the device has		*/
#define NUMMARKERS    20    /* Number of markers the device has 	*/
#define NUMFONTS      22    /* Number of fonts the device has		*/
#define NUMCOLORS     24    /* Number of colors the device supports	*/
#define PDEVICESIZE   26    /* Size required for device descriptor	*/
#define CURVECAPS     28    /* Curve capabilities			*/
#define LINECAPS      30    /* Line capabilities			*/
#define POLYGONALCAPS 32    /* Polygonal capabilities			*/
#define TEXTCAPS      34    /* Text capabilities			*/
#define CLIPCAPS      36    /* Clipping capabilities			*/
#define RASTERCAPS    38    /* Bitblt capabilities			*/
#define ASPECTX       40    /* Length of the X leg			*/
#define ASPECTY       42    /* Length of the Y leg			*/
#define ASPECTXY      44    /* Length of the hypotenuse 		*/

#define LOGPIXELSX    88    /* Logical pixels/inch in X 		*/
#define LOGPIXELSY    90    /* Logical pixels/inch in Y 		*/

#define SIZEPALETTE  104    /* Number of entries in physical palette	*/
#define NUMRESERVED  106    /* Number of reserved entries in palette	*/
#define COLORRES     108    /* Actual color resolution 			*/


#define DT_PLOTTER	    0	/* Vector plotter		    */
#define DT_RASDISPLAY	    1	/* Raster display		    */
#define DT_RASPRINTER	    2	/* Raster printer		    */
#define DT_RASCAMERA	    3	/* Raster camera		    */
#define DT_CHARSTREAM	    4	/* Character-stream, PLP	    */
#define DT_METAFILE	    5	/* Metafile, VDM		    */
#define DT_DISPFILE	    6	/* Display-file 		    */

/* Curve Capabilities */

/* Line Capabilities */

/* Polygonal Capabilities */
#define PC_TRAPEZOID	    4	/* Can do trapezoids		    */

/* Polygonal Capabilities */

/* Text Capabilities */
//#define TC_OP_CHARACTER     0x0001  /* Can do OutputPrecision	CHARACTER      */
//#define TC_OP_STROKE	    0x0002  /* Can do OutputPrecision	STROKE	       */
//#define TC_CP_STROKE	    0x0004  /* Can do ClipPrecision	STROKE	       */
//#define TC_CR_90	    0x0008  /* Can do CharRotAbility	90	       */
//#define TC_CR_ANY	    0x0010  /* Can do CharRotAbility	ANY	       */
//#define TC_SF_X_YINDEP	    0x0020  /* Can do ScaleFreedom	X_YINDEPENDENT */
//#define TC_SA_DOUBLE	    0x0040  /* Can do ScaleAbility	DOUBLE	       */
//#define TC_SA_INTEGER	    0x0080  /* Can do ScaleAbility	INTEGER        */
//#define TC_SA_CONTIN	    0x0100  /* Can do ScaleAbility	CONTINUOUS     */
//#define TC_EA_DOUBLE	    0x0200  /* Can do EmboldenAbility	DOUBLE	       */
//#define TC_IA_ABLE	    0x0400  /* Can do ItalisizeAbility	ABLE	       */
//#define TC_UA_ABLE	    0x0800  /* Can do UnderlineAbility	ABLE	       */
//#define TC_SO_ABLE	    0x1000  /* Can do StrikeOutAbility	ABLE	       */
//#define TC_RA_ABLE	    0x2000  /* Can do RasterFontAble	ABLE	       */
//#define TC_VA_ABLE	    0x4000  /* Can do VectorFontAble	ABLE	       */
//#define TC_RESERVED	    0x8000

#define NEWFRAME		     1
#define ABORTDOC		     2
#define NEXTBAND		     3
#define SETCOLORTABLE		     4
#define GETCOLORTABLE		     5
#define FLUSHOUTPUT		     6
#define DRAFTMODE		     7
#define QUERYESCSUPPORT 	     8
#define SETABORTPROC		     9
#define STARTDOC		     10
#define ENDDOC			     11
#define GETPHYSPAGESIZE 	     12
#define GETPRINTINGOFFSET	     13
#define GETSCALINGFACTOR	     14
#define MFCOMMENT		     15
#define GETPENWIDTH		     16
#define SETCOPYCOUNT		     17
#define SELECTPAPERSOURCE	     18
#define DEVICEDATA		     19
#define PASSTHROUGH		     19
#define GETTECHNOLGY		     20
#define GETTECHNOLOGY		     20
#define SETENDCAP		     21
#define SETLINEJOIN		     22
#define SETMITERLIMIT		 23
#define BANDINFO		     24
#define DRAWPATTERNRECT 	     25
#define GETVECTORPENSIZE	     26
#define GETVECTORBRUSHSIZE	     27
#define ENABLEDUPLEX		     28
#define GETSETPAPERBINS 	     29
#define GETSETPRINTORIENT	     30
#define ENUMPAPERBINS		     31
#define SETDIBSCALING		     32
#define EPSPRINTING        	     33
#define ENUMPAPERMETRICS   	     34
#define GETSETPAPERMETRICS 	     35
#define POSTSCRIPT_DATA		     37
#define POSTSCRIPT_IGNORE	     38
#define GETEXTENDEDTEXTMETRICS	     256
#define GETEXTENTTABLE		     257
#define GETPAIRKERNTABLE	     258
#define GETTRACKKERNTABLE	     259
#define EXTTEXTOUT		     512
#define ENABLERELATIVEWIDTHS	     768
#define ENABLEPAIRKERNING	     769
#define SETKERNTRACK		     770
#define SETALLJUSTVALUES	     771
#define SETCHARSET		     772

#define STRETCHBLT		     2048
#define BEGIN_PATH		     4096
#define CLIP_TO_PATH		     4097
#define END_PATH		     4098
#define EXT_DEVICE_CAPS		     4099
#define RESTORE_CTM		     4100
#define SAVE_CTM	             4101
#define SET_ARC_DIRECTION	     4102
#define SET_BACKGROUND_COLOR	     4103
#define SET_POLY_MODE		     4104
#define SET_SCREEN_ANGLE	     4105
#define SET_SPREAD		     4106
#define TRANSFORM_CTM		     4107
#define SET_CLIP_BOX		     4108
#define SET_BOUNDS                   4109
#define SET_MIRROR_MODE              4110

/* Spooler Error Codes */
#define SP_NOTREPORTED		     0x4000
#define SP_ERROR		     (-1)
#define SP_APPABORT		     (-2)
#define SP_USERABORT		     (-3)
#define SP_OUTOFDISK		     (-4)
#define SP_OUTOFMEMORY		     (-5)

#define PR_JOBSTATUS		     0x0000


PWind_Imp :: PWind_Imp ( pWindow req,const char*jobname,PrintingDevice_Imp *device)
: Wind_Imp(req)
{
HDC hPr;
char *PrJob;

	PrValid = false;
	PrAbort = false;
	PrPage = false;
	PrStdFonts = 0;
   	if (!(device -> Device() && device -> Driver() && device -> Port())) {
		hPr = 0;
		return;
	}
	
	if (!(PrJob = (char*)jobname)) PrJob = "TRiAS® Framework printout";

	if ((hPr = CreateDC (device ->Driver(), device ->Device(), device ->Port(), device ->InitString())) != 0) 
	{
    	// 	Get the printer size and set it to WndSize
	int width, height;
	
		width = GetDeviceCaps (hPr,HORZRES);
		height = GetDeviceCaps(hPr, VERTRES);
    		WndSize = Dimension(width, height);

		DCFlags.FontInUse = DCFlags.PenInUse = DCFlags.BrushInUse =
		DCFlags.Initialised = DCFlags.FontNeeded = DCFlags.PenNeeded =
		DCFlags.BrushNeeded = 0;
		GetDC();

    	/* Define the abort function */
		SetAbortProc (hPr, PrinterAbortProc);
    		CV_RunTime::Window_hDC(this) = hPr;
    		hEContext = (HWND)hPr;
    		
	DOCINFO DI;

		memset (&DI, 0, sizeof(DOCINFO));
		DI.cbSize = sizeof(DOCINFO);
    		DI.lpszDocName = PrJob;
//		DI.lpszOutput = NULL;
#if defined(WIN32)
		if (IsWin40()) {
		int iCheck = NEXTBAND;
		BOOL fBanding = Escape (hPr, QUERYESCSUPPORT, sizeof(int), (LPCSTR)&iCheck, NULL);

//			DI.fwType = fBanding ?  DI_APPBANDING : 0;
		}
#endif // WIN32
		if (StartDoc (hPr, &DI) > 0) {
			pApp_Imp AppImpInst = _AppImpFind();
			AppImpInst -> PrinterList() -> Insert ((HANDLE)hPr, this );
			PrValid = true;
		}
		else {
			DeleteDC (hPr);
    			CV_RunTime::Window_hDC(this) = 0;
    			hEContext = 0;
		}
	}
	else {
    		CV_RunTime::Window_hDC(this) = 0;
    		hEContext = 0;
    	}
}

PWind_Imp :: ~PWind_Imp()
{
	if (CV_RunTime::Window_hDC(this)) {
		if (PrValid) {
		pApp_Imp AppImpInst = _AppImpFind();

			EndDoc (CV_RunTime::Window_hDC (this));
			AppImpInst -> PrinterList() -> Delete((HANDLE)CV_RunTime::Window_hDC(this));
		}
		if (CV_RunTime::Window_hDC (this)) {
    			DeleteDC (CV_RunTime::Window_hDC(this) );
    			CV_RunTime::Window_hDC (this) = 0;
		}
	}
	if (PrStdFonts)
		delete PrStdFonts;
}


void PWind_Imp :: NewPage (void)
{
	if (PrValid) {
 	int error_val = StartPage (CV_RunTime::Window_hDC(this));

		if (error_val <= 0) 
		{	// Fehler aufgetreten
		BOOL repeat_flag = false;
		BOOL repeatable = false;

#if defined(WIN32) && defined(_DEBUG)
		DWORD dwError = GetLastError();
#endif
			do {
			Event e;

				switch (error_val) {
				case SP_ERROR:
					CV_RunTime::Event_wParam (e) = PrinterErrorEvt :: GeneralError;
					repeatable = true;
					break; 

				case SP_APPABORT:
					CV_RunTime::Event_wParam (e) = PrinterErrorEvt :: GeneralError;
					break; 
				
				case SP_USERABORT:
					CV_RunTime::Event_wParam (e) = PrinterErrorEvt :: UserAbort;
					break; 
					
				case SP_OUTOFDISK:
					repeatable = true;
					CV_RunTime::Event_wParam (e) = PrinterErrorEvt :: NoDiskSpace;
					break; 
					
				case SP_OUTOFMEMORY:
					repeatable = true;
					CV_RunTime::Event_wParam (e) = PrinterErrorEvt :: NoMemSpace;
					break; 

				default:
					CV_RunTime::Event_wParam (e) = PrinterErrorEvt :: GeneralError;
					break;
				}
				if (repeat_flag = CV_RunTime::Printer_Error((Printer*)pRequestor, e))
		    			error_val = StartPage (CV_RunTime::Window_hDC(this));
			} while (repeat_flag && repeatable && (error_val <= 0));
		}
		else if (PrAbort)
			error_val = SP_USERABORT;
		else {
		// All ok so re-initialise DC.
			DCFlags.FontInUse = DCFlags.PenInUse = DCFlags.BrushInUse =	0;
			DCFlags.Initialised = DCFlags.FontNeeded = DCFlags.PenNeeded = 0;
			DCFlags.BrushNeeded =  0;
			GetDC();
		}
		PrPage = true;

	// Do we need to clean up ?
		if (error_val < 0) {
			PrValid = false;
	
		pApp_Imp AppImpInst = _AppImpFind();
    	
			AbortDoc (CV_RunTime::Window_hDC(this));
			AppImpInst -> PrinterList() -> Delete((HANDLE)CV_RunTime::Window_hDC(this));
		}
	}
}

// #HK950907: WIN32 erfordert diese Funktion, bisher ging es ohne -------------
void PWind_Imp :: EndPage (void)
{
	if (!PrValid) return;
 
 int error_val = ::EndPage (CV_RunTime::Window_hDC(this));

	if (error_val <= 0) {
	Event e;
#if defined(WIN32) && defined(_DEBUG)
	DWORD dwError = GetLastError();
#endif 
		switch (error_val) {
		case SP_ERROR:
			CV_RunTime::Event_wParam (e) = PrinterErrorEvt :: GeneralError;
			break; 

		case SP_APPABORT:
			CV_RunTime::Event_wParam (e) = PrinterErrorEvt :: GeneralError;
			break; 
		
		case SP_USERABORT:
			CV_RunTime::Event_wParam (e) = PrinterErrorEvt :: UserAbort;
			break; 
			
		case SP_OUTOFDISK:
			CV_RunTime::Event_wParam (e) = PrinterErrorEvt :: NoDiskSpace;
			break; 
			
		case SP_OUTOFMEMORY:
			CV_RunTime::Event_wParam (e) = PrinterErrorEvt :: NoMemSpace;
			break; 

		default:
			CV_RunTime::Event_wParam (e) = PrinterErrorEvt :: GeneralError;
			break;
		}
	} else if (PrAbort)
		error_val = SP_USERABORT;
	else {
	// All ok so re-initialise DC.
		DCFlags.FontInUse = DCFlags.PenInUse = DCFlags.BrushInUse =	0;
		DCFlags.Initialised = DCFlags.FontNeeded = DCFlags.PenNeeded = 0;
		DCFlags.BrushNeeded =  0;
		GetDC();
	}

// Do we need to clean up ?
	if (error_val < 0) {
		PrValid = false;
	
	pApp_Imp AppImpInst = _AppImpFind();
    	
		AbortDoc (CV_RunTime::Window_hDC(this));
		AppImpInst -> PrinterList() -> Delete((HANDLE)CV_RunTime::Window_hDC(this));
	}
}

Rectangle PWind_Imp :: CanvasRect ()
{	
Rectangle r (WndSize.Height(), 0, 0, WndSize.Width());

	return r;
}

Rectangle PWind_Imp :: WindowRect ()
{
Rectangle r (WndSize.Height(), 0, 0, WndSize.Width());
	
	return r;
}

HDC	PWind_Imp::  GetDC	()
{
	if (!hEContext)	// Invalid printer
	{
		DCFlags.FontInUse = DCFlags.PenInUse = DCFlags.BrushInUse =
		DCFlags.Initialised = DCFlags.FontNeeded = DCFlags.PenNeeded =
		DCFlags.BrushNeeded = 0;
		return hEContext = 0, PrValid = 0, 0;
	}
	if (!DCFlags.Initialised)
	{
		SetMapMode( (HDC)hEContext, MM_ANISOTROPIC);
#if !defined(WIN32)
		SetWindowExt((HDC)hEContext,WndSize.Width(), WndSize.Height());
		SetViewportExt((HDC)hEContext, WndSize.Width(), -WndSize.Height());
		SetViewportOrg((HDC)hEContext, 0, WndSize.Height());
#else
		SetWindowExtEx ((HDC)hEContext, WndSize.Width(), WndSize.Height(), NULL);
		SetViewportExtEx ((HDC)hEContext, WndSize.Width(), -WndSize.Height(), NULL);
		SetViewportOrgEx ((HDC)hEContext, 0, WndSize.Height(), NULL);
#endif

		if ( CV_RunTime::Window_WndBackground(this)) {
		LOGBRUSH lb;
		
			GetObject(CV_RunTime::Brush_hBrush(CV_RunTime::Window_WndBackground(this)), sizeof(LOGBRUSH), (pchar) &lb);
			SetBkColor((HDC)hEContext, lb.lbColor);
		}
		DCFlags.Initialised = 1;
        }

	if (DCFlags.FontNeeded && !DCFlags.FontInUse) {
	HFONT font = 0;

		if (CV_RunTime::Window_WndFont(this)) {
			if (!PrStdFonts)
				PrStdFonts = InitPrStdFonts((HDC)hEContext);
			CV_RunTime::Font_Imp(WndFont) -> Init((LOGFONT**)PrStdFonts, (HDC)hEContext);
			 font = CV_RunTime::Font_hFont ( CV_RunTime::Window_WndFont(this) );
		}
		if (font)
			SelectObject ( (HDC)hEContext, font );					// * 0.5 *
		else
			SelectObject ( (HDC)hEContext, GetStockObject ( DEVICE_DEFAULT_FONT )); // * 0.5 *
		
		DCFlags.FontInUse = 1;
		DCFlags.FontNeeded = 0;
		SetTextAlign((HDC)hEContext, TA_LEFT | TA_BOTTOM );
	}
	if (DCFlags.PenNeeded && !DCFlags.PenInUse) {
		if (CV_RunTime::Window_WndPen(this))
			SelectObject ((HDC)hEContext, 
		   		      CV_RunTime::Pen_hPen (CV_RunTime::Window_WndPen(this))); // * 0.5 *
		else
			SelectObject ((HDC)hEContext, GetStockObject (7));	  // * 0.5 *
			// Stock Object 7 is default pen
		DCFlags.PenInUse = 1;
		DCFlags.PenNeeded = 0;
	}

	if (DCFlags.BrushNeeded && !DCFlags.BrushInUse) {
		if (CV_RunTime::Window_WndBrush(this))
			SelectObject ((HDC)hEContext,  CV_RunTime::Brush_hBrush ( CV_RunTime::Window_WndBrush(this) ));	// * 0.5 *
		else
			SelectObject ( (HDC)hEContext,  GetStockObject ( 4 ));// * 0.5 *
			// Stock Object 4 is default brush
		DCFlags.BrushInUse = 1;
		DCFlags.BrushNeeded = 0;
	}

return (HDC)hEContext;
}

#if !defined(WIN32)
int __pascal __loadds PrinterAbortProc (HDC hPr, int Code) 
#else
int CALLBACK PrinterAbortProc (HDC hPr, int Code) 
#endif
{
pApp_Imp AppImpInst = _AppImpFind();
PWind_Imp * pri;

	if (pri = (PWind_Imp*)(AppImpInst -> PrinterList() -> Find ((HANDLE)hPr)))
	{
		if (!pri -> PrAbort)
			CV_RunTime :: PrinterIdle((Printer*)(pri-> GetRequestor()));
		return !(pri -> PrAbort);
	}
	else {
		AppImpInst -> Exec(0, ExecWhileEvent);
		return true;
	}
}

void PWind_Imp :: Show(ShowState)
{}

void PWind_Imp :: Abort()
{
	PrAbort = true;
// 	if (PrValid && (!PrPage))
//    	Escape(CV_RunTime::Window_hDC(this), ABORTDOC, 0, 0, 0);
}

Dimension	PWind_Imp::  ChangeSize ( Dimension size )
{
HDC hPr = CV_RunTime::Window_hDC(this);
Dimension retval = WndSize;

	WndSize = size;
	if (PrValid && hPr) {
    	int width, height;
	
		width = GetDeviceCaps (hPr,HORZRES);
		height = GetDeviceCaps (hPr, VERTRES);
		SetMapMode (hPr, MM_ANISOTROPIC);
#if !defined(WIN32)
		SetWindowExt(hPr,WndSize.Width(), WndSize.Height());
		SetViewportExt(hPr, width ,-height);
		SetViewportOrg(hPr, 0, height);
#else
		SetWindowExtEx (hPr, WndSize.Width(), WndSize.Height(), NULL);
		SetViewportExtEx (hPr, width ,-height, NULL);
		SetViewportOrgEx (hPr, 0, height, NULL);
#endif
	}
	return retval;
}


/*
 * TargetDeviceFromPrintDlg
 *
 * Purpose:
 *  Creates an OLE DVTARGETDEVICE structure from a PRINTDLG
 *  structure as returned from the common dialog API PrintDlg,
 *  which is commonly used for Printer Setup.
 *
 * Parameters:
 *  pPD             LPPRINTDLG containing device information.
 *
 * Return Value:
 *  DVTARGETDEVICE * pointing to the new structure.  This is
 *  allocated with the task memory allocator and should be
 *  freed with CoTaskMemFree.
 */

DVTARGETDEVICE *TargetDeviceFromPrintDlg (LPPRINTDLG pPD)
{
DVTARGETDEVICE *ptd = NULL;
LPDEVNAMES pDevNames, pDN;
LPDEVMODE pDevMode, pDM;
UINT nMaxOffset;
LPTSTR pszName;
DWORD dwDevNamesSize, dwDevModeSize, dwPtdSize;

    pDN = (LPDEVNAMES)GlobalLock(pPD->hDevNames);
    if (NULL == pDN)
        return NULL;

    pDM = (LPDEVMODE)GlobalLock(pPD->hDevMode);
    if (NULL == pDM)
	{
		GlobalUnlock(pPD->hDevNames);
		return NULL;
	}

    nMaxOffset = (pDN->wDriverOffset > pDN->wDeviceOffset) ? pDN->wDriverOffset : pDN->wDeviceOffset;
    nMaxOffset = (pDN->wOutputOffset > nMaxOffset) ? pDN->wOutputOffset : nMaxOffset;

    pszName = (LPTSTR)pDN + nMaxOffset;

    dwDevNamesSize = (DWORD)(nMaxOffset+lstrlen(pszName)+1);
    dwDevModeSize = (DWORD) (pDM->dmSize+pDM->dmDriverExtra);

    dwPtdSize = sizeof(DWORD) + dwDevNamesSize + dwDevModeSize;

    ptd = (DVTARGETDEVICE *)CoTaskMemAlloc(dwPtdSize);

    if (NULL != ptd) {
		ptd->tdSize=(UINT)dwPtdSize;

		pDevNames = (LPDEVNAMES) &ptd->tdDriverNameOffset;
		memcpy(pDevNames, pDN, (size_t)dwDevNamesSize);

		pDevMode = (LPDEVMODE)((LPTSTR)&ptd->tdDriverNameOffset + dwDevNamesSize);
		memcpy(pDevMode, pDM, (size_t)dwDevModeSize);

		ptd->tdDriverNameOffset += sizeof(DWORD);
		ptd->tdDeviceNameOffset += sizeof(DWORD);
		ptd->tdPortNameOffset += sizeof(DWORD);
		ptd->tdExtDevmodeOffset = (UINT)dwDevNamesSize + sizeof(DWORD);
	}

	GlobalUnlock(pPD->hDevNames);
	GlobalUnlock(pPD->hDevMode);
	return ptd;
}

// ******************* PrintingDevice_Imp functions ***********************
PrintingDevice_Imp :: PrintingDevice_Imp (void)
{
	m_fValid = false;
	m_hDevMode = NULL;
	m_hDevNames = NULL;
	m_pDevMode = NULL;
}

PrintingDevice_Imp :: ~PrintingDevice_Imp (void)
{
	Tidy();
}

void PrintingDevice_Imp::Tidy (void)
{
// DruckerInfo's freigeben
	m_fValid = false;

	if (m_pDevMode) {
		GlobalUnlock (m_hDevMode);
		m_pDevMode = NULL;
	}
	if (m_hDevMode) {
		GlobalFree (m_hDevMode);
		m_hDevMode = NULL;
	}
	if (m_hDevNames) {
		GlobalFree (m_hDevNames);
		m_hDevNames = NULL;
	}
}

PRINTDLG PrintingDevice_Imp::s_pd;		// Struktur für PrintDialog

BOOL PrintingDevice_Imp::Setup (BOOL fInit, DVTARGETDEVICE **pdvt)
{
	if (!fInit && !InitFromDefaultPrinter()) 
		return false;

// initialize PRINTDLG structure
	if (m_pDevMode) {
		GlobalUnlock (m_hDevMode);
		m_pDevMode = NULL;
	}

	memset (&s_pd, 0, sizeof(PRINTDLG));
	s_pd.lStructSize = sizeof (PRINTDLG);
	s_pd.hwndOwner = GetActiveWindow();
	s_pd.hDevMode = m_hDevMode;
	s_pd.hDevNames = m_hDevNames;
	s_pd.nFromPage = 0;
	s_pd.nToPage = 0;
	s_pd.nMinPage = 0;
	s_pd.nMaxPage = 0;
	s_pd.nCopies = 0;
	s_pd.hInstance = NULL;
	s_pd.Flags = PD_NOPAGENUMS | PD_NOSELECTION | PD_PRINTSETUP;
	if (fInit) s_pd.Flags |= PD_RETURNDEFAULT;
	s_pd.lpfnSetupHook = NULL;
	s_pd.lpSetupTemplateName = NULL;
	s_pd.lpfnPrintHook = NULL;
	s_pd.lpPrintTemplateName = NULL;

BOOL fResult = PrintDlg (&s_pd);	// Anzeigen und raus

	m_hDevMode = s_pd.hDevMode;
	m_hDevNames = s_pd.hDevNames;

	if (NULL != pdvt)
		*pdvt = TargetDeviceFromPrintDlg (&s_pd);

	if (fResult && !fInit)
		return ParseDevNames();
	
	return fResult;
}

// Absichern der Initialisierung der internen Strukturen auf den StandardDrucker
BOOL PrintingDevice_Imp::InitFromDefaultPrinter (DVTARGETDEVICE **ppdvt)
{
	if (!isValid()) {
		if (!Setup (true, ppdvt) || !ParseDevNames())
			return false;		// Initialisierung
		m_fValid = true;
	}

return true;
}

///////////////////////////////////////////////////////////////////////////////
// Voreinstellen mit einem bestimmten Drucker
BOOL PrintingDevice_Imp::InitFromData (DVTARGETDEVICE *pdvt)
{
	if (NULL == pdvt)
		return false;

	Tidy();		// alte Einstellungen löschen

// neuen Speicher anfordern und Daten reinkopieren
// DEVNAMES kopieren
UINT nMaxOffset = max(pdvt->tdDriverNameOffset, pdvt->tdDeviceNameOffset);
	
	nMaxOffset = max(pdvt->tdPortNameOffset, nMaxOffset);

DWORD dwDevNamesSize = (DWORD)(nMaxOffset + lstrlen((LPTSTR)pdvt+nMaxOffset)+1);

	m_hDevNames = GlobalAlloc (GHND, dwDevNamesSize);
	if (NULL == m_hDevNames)
		return false;

LPDEVNAMES pNewDN = (LPDEVNAMES)GlobalLock (m_hDevNames);	

	if (NULL == pNewDN) {
		GlobalFree (m_hDevNames);
		m_hDevNames = NULL;
		return false;
	}
	memcpy (pNewDN, (DEVNAMES *)&pdvt->tdDriverNameOffset, dwDevNamesSize);
	pNewDN -> wDriverOffset -= sizeof(DWORD);
	pNewDN -> wDeviceOffset -= sizeof(DWORD);
	pNewDN -> wOutputOffset -= sizeof(DWORD);
	pNewDN -> wDefault = 0;
	GlobalUnlock (m_hDevNames);

// evtl. DEVMODE kopieren
    if (0 != pdvt -> tdExtDevmodeOffset) {
	LPDEVMODE pDevMode = (LPDEVMODE)((LPSTR)pdvt + pdvt->tdExtDevmodeOffset);
	DWORD dwDevModeSize = (DWORD) (pDevMode->dmSize + pDevMode->dmDriverExtra);

		m_hDevMode = GlobalAlloc (GHND, dwDevModeSize);
		if (NULL == m_hDevMode)
			return false;

	LPSTR pNewDM = (LPSTR)GlobalLock (m_hDevMode);	

		if (NULL == pNewDM) {
			GlobalFree (m_hDevMode);
			m_hDevMode = NULL;
			return false;
		}
		memcpy (pNewDM, pDevMode, dwDevModeSize);
		GlobalUnlock (m_hDevMode);
	}

	m_fValid = true;
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// Abfrage der derzeitigen Einstellungen
BOOL PrintingDevice_Imp :: ParseDevNames (void)
{
	if (m_pDevMode) {
		GlobalUnlock (m_hDevMode);
		m_pDevMode = NULL;
	}

	if (m_hDevNames) {
	DEVNAMES *pDevNames = (DEVNAMES *)GlobalLock (m_hDevNames);
	BYTE *pRaw = (BYTE *)pDevNames;

		if (pDevNames == NULL) return false;
		m_strDevice = (LPSTR)(pRaw + pDevNames -> wDeviceOffset);
		m_strDriver = (LPSTR)(pRaw + pDevNames -> wDriverOffset);
		m_strPort = (LPSTR)(pRaw + pDevNames -> wOutputOffset);
		GlobalUnlock (m_hDevNames);

		m_fValid = true;
		return true;
	} else
		m_fValid = false;

return false;
}

const char *PrintingDevice_Imp :: Device (void)
{
	if (!isValid() && !InitFromDefaultPrinter()) 
		return NULL;

	return m_strDevice.c_str();
}

const char *PrintingDevice_Imp :: Driver (void)
{
	if (!isValid() && !InitFromDefaultPrinter()) 
		return NULL;

	return m_strDriver.c_str();
}

const char *PrintingDevice_Imp :: Port (void)
{
	if (!isValid() && !InitFromDefaultPrinter()) 
		return NULL;

	return m_strPort.c_str();
}

DEVMODE *PrintingDevice_Imp :: InitString (void)
{
	if (!isValid() && !InitFromDefaultPrinter()) 
		return NULL;

	if (m_pDevMode == NULL && m_hDevMode != NULL)
		m_pDevMode = (DEVMODE *)GlobalLock (m_hDevMode);

	return m_pDevMode;
}


// #HK921029 ------------------------------------------------------------------
// #HK950314: unter WIN32 Banding nicht (immer) implementiert
void BPWind_Imp :: NextBand (Rectangle &Rc, BOOL fFirst)
{
	if (PrValid) {
 	int error_val;
	RECT r;
	int iCheck = NEXTBAND;
	BOOL fBanding = Escape (CV_RunTime::Window_hDC(this), QUERYESCSUPPORT, sizeof(int), (LPCSTR)&iCheck, NULL);

		if (IsWin40() && fFirst)
			fBanding = false;	// Win95: erstes Band mit StartPage

		memset (&r, '\0', sizeof(RECT));
		if (!fBanding)
			error_val = StartPage (CV_RunTime::Window_hDC(this));
		else {
			error_val = Escape (CV_RunTime::Window_hDC(this), 
					    NEXTBAND, 0, 0, (pchar)&r);
		}

		if (!fBanding ? error_val <= 0 : error_val < 0) {
		BOOL repeat_flag = false;
		BOOL repeatable = false;

#if defined(WIN32) && defined(_DEBUG)
		DWORD dwError = GetLastError();
#endif 
			do {
			Event e;
		
				switch (error_val) {
				case SP_ERROR:
					CV_RunTime::Event_wParam (e) = PrinterErrorEvt :: GeneralError;
					repeatable = true;
					break; 

				case SP_APPABORT:
					CV_RunTime::Event_wParam (e) = PrinterErrorEvt :: GeneralError;
					break; 
				
				case SP_USERABORT:
					CV_RunTime::Event_wParam (e) = PrinterErrorEvt :: UserAbort;
					break; 
					
				case SP_OUTOFDISK:
					repeatable = true;
					CV_RunTime::Event_wParam (e) = PrinterErrorEvt :: NoDiskSpace;
					break; 
					
				case SP_OUTOFMEMORY:
					repeatable = true;
					CV_RunTime::Event_wParam (e) = PrinterErrorEvt :: NoMemSpace;
					break; 
				}
				if (repeat_flag = CV_RunTime::Printer_Error((Printer*)pRequestor, e)) {
					if (!fBanding) {
			    			error_val = StartPage (CV_RunTime::Window_hDC (this)); 
					} else {
						error_val = Escape (CV_RunTime::Window_hDC(this), 
								    NEXTBAND, 0, 0, (pchar)&r);
					}
				}
			} while (repeat_flag && repeatable && (!fBanding ? error_val <= 0 : error_val < 0));
		}
		else if (PrAbort)
			error_val = SP_USERABORT;
		else {
		// All ok so re-initialise DC.
			DCFlags.FontInUse = DCFlags.PenInUse = DCFlags.BrushInUse =	0;
			DCFlags.Initialised = DCFlags.FontNeeded = DCFlags.PenNeeded = 0;
			DCFlags.BrushNeeded = DCFlags.Erasing = 0;
			
			GetDC();
		}
		PrPage = true;

	// Do we need to clean up ?
		if (!fBanding ? error_val <= 0 : error_val < 0) {
			PrValid = false;

		pApp_Imp AppImpInst = _AppImpFind();
    
			AbortDoc (CV_RunTime::Window_hDC (this));
			AppImpInst -> PrinterList() -> Delete ((HANDLE)CV_RunTime::Window_hDC(this));
		}

	// ClippingRect des nächsten Bandes
		if (!fBanding) {
			Rc = Rectangle (0, 0, WndSize.Height(), WndSize.Width());
		} else  {
			Rc.Left() = r.left;
			Rc.Right() = r.right;
			Rc.Top() = r.top;
			Rc.Bottom() = r.bottom;
		}
	}
}

