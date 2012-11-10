// SignOnBildchen fuer TRIAS --------------------------------------------------
// File: SIGNON.CXX

#include "triaspre.hxx"

#if !defined(WIN32)
#include <toolhelp.h>
#endif
#include <stdio.h>
#include <malloc.h>

#include <funcs03.h>
#include <registry.hxx>
#include "signon.h"
#include "copystr.h"

#include "bildobj.hxx"
#include "signon.hxx"
#include "WinMMWrap.h"

#include "triasres.h"
#include "strings.h"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern char *ReadResource (HINSTANCE hInst, int resID, DWORD &dwSize);

bool IsInternalRegNumber (LPCSTR pcRegEntry) 
{
char *pNext = NULL;
long lInit = strtol (pcRegEntry, &pNext, 10);
long l2nd = strtol (pNext+1, &pNext, 10);
long lNumber = strtol (pNext+1, &pNext, 10);

	return (100 == lInit && 0 == l2nd && 16670989L == lNumber);
}

bool IsDemoRegNumber (LPCSTR pcRegEntry) 
{
char *pNext = NULL;
long lInit = strtol (pcRegEntry, &pNext, 10);
long l2nd = strtol (pNext+1, &pNext, 10);
long lNumber = strtol (pNext+1, &pNext, 10);

	return (1 == lInit && 0 == l2nd && 7621669L == lNumber);
}

bool IsLegalRegNumber (LPCSTR pcRegEntry) 
{
char *pNext = NULL;
long lInit = strtol (pcRegEntry, &pNext, 10);
long l2nd = strtol (pNext+1, &pNext, 10);
long lNumber = strtol (pNext+1, &pNext, 10);

	srand (230459L);
	for (long i = 0; i < lInit-1; i++) 
		rand();

long lGroup = rand() % 1000;
long lResult = 0;

	for (int j = 0; j <= l2nd; j++)
		lResult = rand()*lGroup+rand();

	return (lResult == lNumber);
}

#pragma warning (disable: 4355)

CSignOnDlg :: CSignOnDlg (pWindow pW, HINSTANCE hInst, uint resID, bool fModal)
	    : DialogWindow (pW, resID, fModal)
{
	m_pSnd = NULL;
	m_fGlobalFree = false;
	m_fModal = fModal;
	m_hInst = hInst;

	if (m_fModal) MouseTrap (On);
}


CSignOnDlg :: ~CSignOnDlg (void)
{
	if (m_pSnd) {
	CWinMMBind WinMM;

		if (WinMM.IsValid())
			WinMM.PlaySound (NULL, NULL, SND_PURGE);

		if (m_fGlobalFree) {
#if !defined(WIN32)
		HGLOBAL hGbl = (HGLOBAL)GlobalHandle(HIWORD(m_pSnd));
#else
		HGLOBAL hGbl = (HGLOBAL)GlobalHandle(LPVOID(m_pSnd));
#endif
	
			GlobalUnlock (hGbl);
			GlobalFree (hGbl);
		} else {
			delete m_pSnd;
		}
		m_pSnd = NULL;
	}

	if (m_fModal) MouseTrap (Off);
}

CSignOnDlg16 :: CSignOnDlg16 (pWindow pW, HINSTANCE hInst, bool fModal)
	      : CSignOnDlg (pW, hInst, SIGNONDLG1, fModal),
		m_bmpLogo (this, IDBM_SIGNONBMP, SIGNONBMP),
		m_ftRegName (this, IDT_USERNAME),
		m_ftRegCompany (this, IDT_COMPANYNAME),
		m_ftRegNr (this, IDT_REGNUMBER)
{
	// nothing else to do
}


CSignOnDlg16 :: ~CSignOnDlg16 (void)
{
	// nothing else to do
}

CSignOnDlg256 :: CSignOnDlg256 (pWindow pW, HINSTANCE hInst, bool fModal)
	       : CSignOnDlg (pW, hInst, SIGNONDLG, fModal),
		 m_bmpSignOn (this, Point (0, 0))
{
	m_pFont = NULL;
	m_pFontP = NULL;
	m_pPersonal = NULL;
	m_fNativeLogo = true;
}


CSignOnDlg256 :: ~CSignOnDlg256 (void)
{
	if (m_pPersonal) delete m_pPersonal;
	if (m_pFont) delete m_pFont;
	if (m_pFontP) delete m_pFontP;
}

#pragma warning (default: 4355)

// Member, die für beide Fälle verwendbar sind --------------------------------
// In Abhängigkeit der verfügbaren Farbauflösung verschiedene SignOns verwenden
CSignOnDlg *CSignOnDlg :: CreateInstance (pWindow pW, HINSTANCE hInst, bool fModal)
{
CSignOnDlg *pSODlg = NULL;
HDC hDC = CreateIC ("DISPLAY", NULL, NULL, NULL);
int iNumColors = GetDeviceCaps (hDC, NUMCOLORS);
bool fOld = false;

	if (iNumColors == -1) {
	int iBitsPixel = GetDeviceCaps (hDC, BITSPIXEL);

		if (iBitsPixel <= 4)
			fOld = true;
	} else if (iNumColors <= 16)
		fOld = true;

	if (hDC == NULL || fOld) 
		pSODlg = new CSignOnDlg16 (pW, hInst, fModal);	// 16 Farben
	else
		pSODlg = new CSignOnDlg256 (pW, hInst, fModal);	// 256 Farben

	if (hDC) DeleteDC (hDC);
	if (pSODlg == NULL || !pSODlg -> FInit()) {
		DELETE (pSODlg);
		return NULL;
	}
	
return pSODlg;		
}

void CSignOnDlg :: PlaySound (void)
{
DWORD dwSndSize = 0;

	m_pSnd = ReadResource (m_hInst, IDSND_STARTUP, dwSndSize);
	if (m_pSnd) {
	//asynchron abspielen
	CWinMMBind WinMM;

		if (WinMM.IsValid()) {
		DWORD dwFlags = SND_MEMORY|SND_NODEFAULT|SND_NOWAIT;

//			if (IsWinNT()) 
//				dwFlags |= SND_ASYNC;
			WinMM.PlaySound (m_pSnd, NULL, dwFlags);
		}
	}
	if (dwSndSize > UINT_MAX) 	// SND größer als 64KByte
		m_fGlobalFree = true;
}

void CSignOnDlg :: MouseButtonDn (MouseEvt)
{
	if (m_fModal) {
		GetParent() -> SetFocus();		
		EndDlg();
	}
	else Hide();
}

void CSignOnDlg :: KeyDown (KeyEvt)
{
	if (m_fModal) {
		GetParent() -> SetFocus();		
		EndDlg();
	}
	else Hide();
}

void CSignOnDlg16 :: PlaySound16 (void)
{
	PlaySound();
}

void CSignOnDlg256 :: PlaySound16 (void)
{
}

// Member für 16-Farb-Variante ------------------------------------------------
bool CSignOnDlg16 :: FInit (void)
{
	if (!m_bmpLogo.Init()) return false;

short iScreenX = GetSystemMetrics (SM_CXSCREEN);
short iScreenY = GetSystemMetrics (SM_CYSCREEN);
Rectangle CRc = CanvasRect ();

	ChangePosition (Point ((iScreenX-(CRc.Right()-CRc.Left()))/2,
			       (iScreenY-(CRc.Top()-CRc.Bottom()))/2));

// Versuchen Personalisierung aus der Registry zu lesen, ansonsten
// Voreinstellungen aus der Resource verwenden
ResString resPName (IDS_PERSONALNAME, 64);
ResString resPAddr (IDS_PERSONALADDRESS, 64);
ResString resDemoName (IDS_DEMONAME, 64);
ResString resDemoAddr (IDS_DEMOADDRESS, 64);

#if defined(WIN32)
#if defined(ENABLE_WIN32S_CODE)
	if (!IsWin32s()) 
#endif // ENABLE_WIN32S_CODE
	{
	CLocalMachine regName (g_cbRegVersion);
	char cbRegEntry[128], cbRegName[65], cbRegNr[65];
	ResString resNotRegistered (IDS_NOTREGISTEREDVERSION, 128);
	DWORD dwLen = sizeof(cbRegNr);

		if (!regName.GetSubSZ (g_cbSerial, cbRegNr, dwLen) ||
			!IsLegalRegNumber (cbRegNr)) 
		{
			m_ftRegNr.SetText (resNotRegistered.Addr());
			m_ftRegName.SetText (resPName);
			m_ftRegCompany.SetText (resPAddr);
		}
		else {
		string str (ResString (IDS_REGNR, 20));

			str += cbRegEntry;
			m_ftRegNr.SetText (str.c_str());

		bool fInternal = IsInternalRegNumber (cbRegNr);
		bool fDemo = IsDemoRegNumber (cbRegNr);

			dwLen = sizeof(cbRegName);
			if (!fInternal && !fDemo && regName.GetSubSZ (g_cbRegName, cbRegName, dwLen)) 
				m_ftRegName.SetText(cbRegName);
			else
				m_ftRegName.SetText (fDemo ? resDemoName : resPName);

			dwLen = sizeof(cbRegEntry);
			if (!fInternal && !fDemo && regName.GetSubSZ (g_cbRegCompany, cbRegEntry, dwLen))
				m_ftRegCompany.SetText (cbRegEntry);
			else
				m_ftRegCompany.SetText (fDemo ? resDemoAddr : resPAddr);
		}
	} 
#if defined(ENABLE_WIN32S_CODE)
	else 
#endif // ENABLE_WIN32S_CODE
#endif // WIN32
#if defined(ENABLE_WIN32S_CODE)
	{
		m_ftRegName.SetText (resPName);
		m_ftRegCompany.SetText (resPAddr);
		m_ftRegNr.SetText("");
	}
#endif // ENABLE_WIN32S_CODE

return true;
}

// Member für 256-Farb-Variante -----------------------------------------------
bool CSignOnDlg256 :: FInit (void)
{
CCurrentUser regKey (g_cbRegConfig);
char cbBuffer[_MAX_PATH];
DWORD dwSize = sizeof(cbBuffer);

	if (regKey.isValid() && regKey.GetSubSZ (g_cbLogoFileName, cbBuffer, dwSize))
		m_fNativeLogo = false;
	
	if (!m_fNativeLogo) {
	// lediglich Datei lesen
		if (!m_bmpSignOn.FInit (cbBuffer)) 
			m_fNativeLogo = true;	// doch das originale nehmen
	}

// bei Fehler hier durchfallen
	if (m_fNativeLogo) {
	// BMP-Resource wegschreiben, damit sie dekomprimiert werden kann
	DWORD dwBmpSize = 0;
	BYTE *pBmp = (BYTE *)ReadResource (m_hInst, IDBMP_STARTUP, dwBmpSize);
	char *pTFile = _tempnam ("C:\\", "Trias");
		
		if (!WriteBmpToDisk (pTFile, pBmp, dwBmpSize)) {
			if (pBmp) delete pBmp;
			free (pTFile);
			return false;
		}
		if (pBmp) delete pBmp;
	
	bool fInit = m_bmpSignOn.FInit (pTFile);
		
		_unlink (pTFile);	// temp. File wieder löschen
		free (pTFile);		// Speicher freigeben
		if (!fInit) return false;
		
	// Font generieren
	ResString rsArial (IDS_ARIAL, 20);

		m_pFont = new Font (Swiss, Dimension (0, -12), rsArial);
		if (m_pFont) m_pFont -> Init();
		m_pFontP = new Font (Swiss, Dimension (0, -11), rsArial);
		if (m_pFontP) m_pFontP -> Init();
		
		m_pPersonal = new char [128];
		if (m_pPersonal == NULL) return false;
	}

// das folgende für beide Fälle (auch bei fremden Logo) ausführen
// Dialogfenster in Größe und Lage anpassen
Dimension dim (m_bmpSignOn.GetSize());

	dim.Width() += 2;
	dim.Height() += 2;
	ChangeSize (dim);
	
// mittig auf dem Bildschirm positionieren
short iScreenX = GetSystemMetrics (SM_CXSCREEN);
short iScreenY = GetSystemMetrics (SM_CYSCREEN);
Rectangle CRc = CanvasRect ();

	ChangePosition (Point ((iScreenX-(CRc.Right()-CRc.Left()))/2,
			       (iScreenY-(CRc.Top()-CRc.Bottom()))/2));
	return true;
}


void CSignOnDlg256 :: Expose (ExposeEvt)
{
	if (!m_fNativeLogo) {
		Draw (&m_bmpSignOn);	// lediglich Bitmap ausgeben
		PlaySound();			// und Sound spielen
		return;
	}

// hDC initialisieren
HWND hWnd = Handle (API_WINDOW_HWND);
HDC hDC = ::GetDC (hWnd);
COLORREF oTColor = RGB(255, 255, 255);
int ioBk = SetBkMode (hDC, TRANSPARENT);
RECT rcP;
HFONT hF = 0;
bool fFontChanged = false;

#if defined(WIN32)
	if (IsWin40()) 
		oTColor = SetTextColor (hDC, GetSysColor (COLOR_3DFACE));	// HintergrundFarbe
	else
#endif // WIN32
		oTColor = SetTextColor (hDC, GetSysColor (COLOR_WINDOW));	// HintergrundFarbe

	if (m_pFont) {
		hF = (HFONT)SelectObject (hDC, m_pFont -> Handle(API_FONT_HFONT));
		fFontChanged = true;
	}
	
// Bitmap und Texte zeichnen
ResString resAddress (IDS_UVEADDRESS, 128);
ResString resVersion1 (!IsModal() ? IDS_SIGNONVERSION : IDS_SIGNONVERSION_MODAL, 64);
ResString resVersion2 (IDS_SIGNONCOPYRIGHT, 64);
ResString resPName (IDS_PERSONALNAME, 64);
ResString resPAddr (IDS_PERSONALADDRESS, 64);
ResString resDemoName (IDS_DEMONAME, 64);
ResString resDemoAddr (IDS_DEMOADDRESS, 64);
bool fRegistered = false;

// einen Text vor der Bitmap ausgeben, damit der Font geladen wird
	SetRect (&rcP, 178, 155, 430, 168);
	Justify (hDC, hDC, resVersion1, NULL, &rcP, ATRight, true);

	Draw (&m_bmpSignOn);	// Bitmap ausgeben

// VersionsZeilen
	SetTextColor (hDC, RGB (255, 255, 255));	// jetzt weiß
	Justify (hDC, hDC, resVersion1, NULL, &rcP, ATRight, true);
	SetRect (&rcP, 178, 171, 430, 186);
	Justify (hDC, hDC, resVersion2, NULL, &rcP, ATRight, true);

// RegNr mit kleinerem Font schreiben
	if (m_pFontP) {
	HFONT hFont = 0;
	
		if (m_pFontP)
			hFont = (HFONT)SelectObject (hDC, m_pFontP -> Handle(API_FONT_HFONT));
		if (!fFontChanged) {
			hF = hFont;
			fFontChanged = true;
		}
	}

#if defined(WIN32)
#if defined(ENABLE_WIN32S_CODE)
	if (!IsWin32s()) 
#endif // ENABLE_WIN32S_CODE
char cbRegEntry[128];

	{
	CLocalMachine regName (g_cbRegVersion);
	DWORD dwLen = sizeof(cbRegEntry);
	ResString resNotRegistered (IDS_NOTREGISTEREDVERSION, 128);

		SetRect (&rcP, 178, 196, 430, 212);
		if (!regName.GetSubSZ (g_cbSerial, cbRegEntry, dwLen) ||
			!IsLegalRegNumber (cbRegEntry)) 
		{
			strcpy (cbRegEntry, resNotRegistered);
			Justify (hDC, hDC, cbRegEntry, NULL, &rcP, ATRight, true);
		}
		else {
		string str (ResString (IDS_REGNR, 20));

			str += cbRegEntry;
			Justify (hDC, hDC, str.c_str(), NULL, &rcP, ATRight, true);
			fRegistered = true;
		}
	}
#endif // WIN32

// Adresse
	SetRect (&rcP, 178, 300, 430, 246);
	Justify (hDC, hDC, (char *)resAddress.Addr(), NULL, &rcP, ATRight, true);

// Personalisierung
#if defined(WIN32)
// Versuchen Personalisierung aus der Registry zu lesen, ansonsten
// Voreinstellungen aus der Resource verwenden
#if defined(ENABLE_WIN32S_CODE)
	if (!IsWin32s()) 
#endif // ENABLE_WIN32S_CODE
	{
	CLocalMachine regName (g_cbRegVersion);
	char cbRegComp[65], cbRegName[65];
	DWORD dwLen = sizeof(cbRegName);
	bool fIntern = IsInternalRegNumber(cbRegEntry);
	bool fDemo = IsDemoRegNumber (cbRegEntry);

		if (fIntern || fDemo || !regName.GetSubSZ (g_cbRegName, cbRegName, dwLen)) {
			strcpy (cbRegName, fDemo ? resDemoName : resPName);
			fRegistered = true;
		}
		dwLen = sizeof(cbRegEntry);
		if (fIntern || fDemo || !regName.GetSubSZ (g_cbRegCompany, cbRegComp, dwLen)) {
			strcpy (cbRegComp, fDemo ? resDemoAddr : resPAddr);
			fRegistered = true;
		}

		strcpy (m_pPersonal, cbRegName);
		strcat (m_pPersonal, " (");
		strcat (m_pPersonal, cbRegComp);
		strcat (m_pPersonal, ")");
	} 
#if defined(ENABLE_WIN32S_CODE)
	else
#endif // ENABLE_WIN32S_CODE
#endif 
#if defined(ENABLE_WIN32S_CODE)
	{
		strcpy (m_pPersonal, resPName);
		strcat (m_pPersonal, resPAddr);
	}
#endif // ENABLE_WIN32S_CODE

	SetRect (&rcP, 18, 330, 448, 344);
	Justify (hDC, hDC, m_pPersonal, NULL, &rcP, ATLeft, true);
        
	PlaySound();	// Sound spielen
	
// Pling machen
	Pling (hDC);

// hDC rücksetzen und freigeben
	SetBkMode (hDC, ioBk);
	SetTextColor (hDC, oTColor);
	if (fFontChanged) SelectObject (hDC, hF);
	::ReleaseDC (hWnd, hDC);
}

bool CSignOnDlg256 :: WriteBmpToDisk (char *pFile, BYTE *pBmp, DWORD dwSize)
{
	if (pBmp == NULL) return false;
	
OFSTRUCT of;
HFILE fh = OpenFile (pFile, &of, OF_CREATE|OF_READWRITE|OF_SHARE_EXCLUSIVE);

	if (fh == HFILE_ERROR) return false;

#if !defined(WIN32)
bool fWritten = ((DWORD)_hwrite (fh, pBmp, dwSize) == dwSize);
#else
bool fWritten = ((DWORD)_lwrite (fh, (LPCSTR)pBmp, dwSize) == dwSize);
#endif
	_lclose (fh);
	
return fWritten;
}

#define PLINGROP	0x00b8074a	// weiß ist transparent, schwarz wird bunt

bool CSignOnDlg256 :: Pling (HDC hDC)
{
Bitmap bmpPling (BLINKEL);		// enthält 8 Bitmaps
Dimension dimBmp = bmpPling.GetSize();
CoOrd dx = dimBmp.Width()/8, dy = dimBmp.Height();

HBITMAP hBmpCopy = CreateCompatibleBitmap (hDC, dx, dy);	// Kopie des PlingBereiches
HBITMAP hBmpOff = CreateCompatibleBitmap (hDC, dx, dy);		// OffScreenBitmap
HDC hDCCopy = CreateCompatibleDC (hDC);		// entsprechende DC's
HDC hDCOff = CreateCompatibleDC (hDC);
HDC hDCPling = CreateCompatibleDC (hDC);

HBITMAP hOldBmpCopy = (HBITMAP)SelectObject (hDCCopy, hBmpCopy);
HBITMAP hOldBmpOff = (HBITMAP)SelectObject (hDCOff, hBmpOff);
HBITMAP hOldBmpPling = (HBITMAP)SelectObject (hDCPling, bmpPling.Handle(API_BITMAP_HBITMAP));

// PlingDC initialisieren
HBRUSH hBr = CreateSolidBrush (RGB (255, 255, 255));
HBRUSH hOldBrush = (HBRUSH)SelectObject (hDCOff, hBr);

// PlingBereich kopieren
short xSrc = 87/*Krone: 277*/ - dx/2;
short ySrc = 86/*Krone: 54*/ - dy/2;

	BitBlt (hDCCopy, 0, 0, dx, dy, hDC, xSrc, ySrc, SRCCOPY);

// Plings generieren und ausgeben
DWORD dwDelta = 0;
#if !defined(WIN32)
TIMERINFO TI;

	TI.dwSize = sizeof(TIMERINFO);
#endif
	for (short i = 0; i < 8; i++) {
	// Zeit stoppen
#if !defined(WIN32)
		TimerCount (&TI);
		dwDelta = TI.dwmsSinceStart + 100;	// 100ms
#else
		dwDelta = GetTickCount() + 100;
#endif

	// Offscreen Bitmap initialisieren
		BitBlt (hDCOff, 0, 0, dx, dy, hDCCopy, 0, 0, SRCCOPY);
		BitBlt (hDCOff, 0, 0, dx, dy, hDCPling, i*dx, 0, PLINGROP);
		
	// ins Bild kopieren
		BitBlt (hDC, xSrc, ySrc, dx, dy, hDCOff, 0, 0, SRCCOPY);

#if !defined(WIN32)
	// etwas warten
		do {
			TimerCount (&TI);
		} while (TI.dwmsSinceStart < dwDelta);
#else
	// den Rest der Zeit (100ms) verwarten
	LONG lSleep = (LONG)(dwDelta - GetTickCount());

		if (lSleep > 0) {
			if (lSleep > 100)
				lSleep = 100;
			Sleep(lSleep);
		}
#endif
	}
	BitBlt (hDC, xSrc, ySrc, dx, dy, hDCCopy, 0, 0, SRCCOPY);
	
// alles wieder aufräumen
	SelectObject (hDCPling, hOldBmpPling);
	SelectObject (hDCCopy, hOldBmpCopy);
	SelectObject (hDCOff, hOldBmpOff);
	SelectObject (hDCOff, hOldBrush);
	
	DeleteDC (hDCPling);
	DeleteDC (hDCCopy);
	DeleteDC (hDCOff);
	DeleteObject (hBr);
	DeleteObject (hBmpOff);
	DeleteObject (hBmpCopy);

return true;
}

///////////////////////////////////////////////////////////////////////////////
// WinMM für PlaySound binden
CWinMMBind::CWinMMBind (void)
	: DLLBind (TEXT("WINMM.DLL")), m_fIsValid(false)
{
	if (NULL == hLib()) return;		// Initialisierungs-Fehler

	m_pPlaySound = (PLAYSOUNDPROC)GetProcAddress (TEXT("PlaySoundA"));
	if (NULL != m_pPlaySound)
		m_fIsValid = true;
}

BOOL CWinMMBind::PlaySound (LPCSTR pszSound, HMODULE hmod, DWORD fdwSound)
{
	TX_ASSERT(NULL != m_pPlaySound);
	return m_pPlaySound (pszSound, hmod, fdwSound);
}
