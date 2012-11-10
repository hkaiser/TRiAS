// Routine zur Druckereinstellung ---------------------------------------------
// File: PRNTSEL2.CXX

#include "triaspre.hxx"

extern HINSTANCE hInstance;

static PRINTDLG s_pd;		// Struktur für PrintDialog

bool IrisWind :: PrinterMode (bool fInit) 
{
// initialize PRINTDLG structure
	s_pd.lStructSize = sizeof (PRINTDLG);
	s_pd.hwndOwner = Handle (API_WINDOW_HWND);
	s_pd.hDevMode = m_hDevMode;
	s_pd.hDevNames = m_hDevNames;
	s_pd.nFromPage = 0;
	s_pd.nToPage = 0;
	s_pd.nMinPage = 0;
	s_pd.nMaxPage = 0;
	s_pd.nCopies = 0;
	s_pd.hInstance = hInstance;
	s_pd.Flags = PD_NOPAGENUMS | PD_NOSELECTION | PD_PRINTSETUP;
	if (fInit) 
		s_pd.Flags |= PD_RETURNDEFAULT;
	s_pd.lpfnSetupHook = (LPSETUPHOOKPROC)NULL;
	s_pd.lpSetupTemplateName = (LPTSTR)NULL;
	s_pd.lpfnPrintHook = (LPPRINTHOOKPROC)NULL;
	s_pd.lpPrintTemplateName = (LPTSTR)NULL;

bool fResult = PrintDlg (&s_pd);	// Anzeigen und raus

	m_hDevMode = s_pd.hDevMode;
	m_hDevNames = s_pd.hDevNames;

return fResult;
}

// Generieren eines Strings aus den Namen in der DEVNAMES-Struktur ------------
string StringFromDevNames (HGLOBAL hDevNames)
{
string strT;

	if (hDevNames) {
	DEVNAMES *pDevNames = (DEVNAMES *)GlobalLock (hDevNames);
	BYTE *pRaw = (BYTE *)pDevNames;

		if (pDevNames == NULL) return strT;
		strT += (LPSTR)(pRaw + pDevNames -> wDeviceOffset);
		strT += ',';
		strT += (LPSTR)(pRaw + pDevNames -> wDriverOffset);
		strT += ',';
		strT += (LPSTR)(pRaw + pDevNames -> wOutputOffset);
		GlobalUnlock (hDevNames);
	}
 
return strT;
}

