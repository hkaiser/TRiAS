// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 12/11/1998 08:27:02 PM
//
// @doc
// @module SignOnDlg.cpp | SignOnBildchen fuer TRIAS

#include "triaspre.hxx"

#include <stdio.h>
#include <malloc.h>
#include <shlobj.h>

#include "triasres.h"
#include "copystr.h"

#include <funcs03.h>
#include <registry.hxx>
#include <TRiASMode.h>
#include <FormatString.h>

#include "bildobj.hxx"
#include "SignOnDlg.h"
#include "WinMMWrap.h"

#include "strings.h"
#include "extmain3.hxx"

#if defined(_DEBUG) && !defined(WIN16)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#if _TRiAS_VER < 0x0400
extern DWORD g_dwVer4;
#endif // _TRiAS_VER < 0x0400

#if _TRiAS_VER < 0x0400
///////////////////////////////////////////////////////////////////////////////
//
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

#if _TRiAS_VER >= 0x0300
	if (300 > lInit && !IsInternalRegNumber(pcRegEntry) && !IsDemoRegNumber(pcRegEntry))
		return S_FALSE;
#endif // _TRiAS_VER >= 0x0300

long l2nd = strtol (pNext+1, &pNext, 10);
long lNumber = strtol (pNext+1, &pNext, 10);

	srand (230459L);
	for (long i = 0; i < lInit-2; i++) 
		rand();

long lStep = lInit / ((rand() % 93) + 7);	// teilen durch mind 7 und max 92
long lGroup = rand() % 1000;
long lResult = 0;

	if (lInit >= 500) {
	// für Werte über 500
		for (int j = 0; j <= l2nd; j += lStep)
			lResult = rand()*lGroup+rand();
		if (j != l2nd + lStep)
			return false;		// lStep muß auch stimmen
	} else {
	// für Werte zwischen 300 und 499
		for (int j = 0; j <= l2nd; j++)
			lResult = rand()*lGroup+rand();
	}
	return (lResult == lNumber);
}
#endif // _TRiAS_VER < 0x0400

#pragma warning (disable: 4355)

CSignOnDlg::CSignOnDlg (pWindow pW, HINSTANCE hInst, uint resID, bool fModal)
	    : DialogWindow (pW, resID, fModal)
{
#if _TRiAS_VER < 0x0510
	m_pSnd = NULL;
#endif
	m_fModal = fModal;
	m_hInst = hInst;

	if (m_fModal) {
#if !defined(_TRIAS_OLDIMPLEMENTATION2)
		MouseTrap (CVOn);
#else
		MouseTrap (On);
#endif // !defined(_TRIAS_OLDIMPLEMENTATION2)
	} 
}

void CSignOnDlg::Show (ShowState rgState)
{
	DialogWindow::Show(rgState);	// Anzeigen
	if (!m_fModal) {
	// aus der Taskbar rausnehmen
	CComPtr<ITaskbarList> TBList;
	
		if (SUCCEEDED(CoCreateInstance(CLSID_TaskbarList, NULL, CLSCTX_ALL, IID_ITaskbarList, (LPVOID *)&TBList.p)) &&
			SUCCEEDED(TBList -> HrInit()))
		{
			TBList -> DeleteTab (Handle(API_WINDOW_HWND));
		}
	}
}

CSignOnDlg::~CSignOnDlg (void)
{
#if _TRiAS_VER < 0x0510
	if (m_pSnd) {
	CWinMMBind WinMM;

		if (WinMM.IsValid())
			WinMM.PlaySound (NULL, NULL, SND_PURGE);

		delete m_pSnd;
		m_pSnd = NULL;
	}
#endif

	if (m_fModal) {
#if !defined(_TRIAS_OLDIMPLEMENTATION2)
		MouseTrap (CVOff);
#else
		MouseTrap (Off);
#endif // !defined(_TRIAS_OLDIMPLEMENTATION2)
	}
}

CSignOnDlg256::CSignOnDlg256 (pWindow pW, HINSTANCE hInst, bool fModal)
	       : CSignOnDlg (pW, hInst, SIGNONDLG, fModal),
		 m_bmpSignOn (this, Point (0, 0))
{
	m_pFont = NULL;
	m_pFontP = NULL;
	m_fNativeLogo = true;
#if _TRiAS_VER < 0x0400
	m_uiResIDBmp = (0 != g_dwVer4) ? IDBMP_TRIAS4 : IDBMP_STARTUP;
#elif _TRiAS_VER < 0x0420
	m_uiResIDBmp = IDBMP_TRIAS4;
#elif _TRiAS_VER < 0x0500
	m_uiResIDBmp = IDBMP_TRIAS42;
#else
	m_uiResIDBmp = IDBMP_TRIAS5;
#endif // _TRiAS_VER < 0x0500
}


CSignOnDlg256::~CSignOnDlg256 (void)
{
	if (m_pFont) delete m_pFont;
	if (m_pFontP) delete m_pFontP;
}

#pragma warning (default: 4355)

///////////////////////////////////////////////////////////////////////////////
// Member, die für beide Fälle verwendbar sind 
// In Abhängigkeit der verfügbaren Farbauflösung verschiedene SignOns verwenden
CSignOnDlg *CSignOnDlg::CreateInstance (pWindow pW, HINSTANCE hInst, bool fModal)
{
CSignOnDlg *pSODlg = NULL;
HDC hDC = ::CreateIC ("DISPLAY", NULL, NULL, NULL);
int iNumColors = ::GetDeviceCaps (hDC, NUMCOLORS);
bool fOld = false;

	if (iNumColors == -1) {
	int iBitsPixel = ::GetDeviceCaps (hDC, BITSPIXEL);

		if (iBitsPixel <= 4)
			fOld = true;
	} else if (iNumColors <= 16)
		fOld = true;

	if (hDC == NULL || fOld) 
	{
		;	// 16 Farben: do nothing, no signondlg
	}
	else
	{
		TX_TRY(pSODlg = new CSignOnDlg256 (pW, hInst, fModal));	// 256 Farben
	}

	if (hDC) 
		::DeleteDC (hDC);

	if (NULL == pSODlg || !pSODlg -> FInit()) {
		DELETE_OBJ (pSODlg);
		return NULL;
	}
	return pSODlg;		
}

#if _TRiAS_VER < 0x0510
void CSignOnDlg::PlaySound (void)
{
DWORD dwSndSize = 0;

	m_pSnd = ReadResource (m_hInst, IDSND_STARTUP, dwSndSize);
	if (m_pSnd) {
	//asynchron abspielen
	CWinMMBind WinMM;

		if (WinMM.IsValid()) {
		DWORD dwMode = SND_MEMORY|SND_NOWAIT|SND_NODEFAULT;

			if (IsWinNT())
				dwMode |= SND_ASYNC;
			else
				dwMode |= SND_SYNC;
			WinMM.PlaySound ((LPCSTR)m_pSnd, NULL, dwMode);
		}
	}
}
#endif

void CSignOnDlg::MouseButtonDn (MouseEvt)
{
	if (m_fModal) {
		GetParent() -> SetFocus();		
		EndDlg();
	}
	else Hide();
}

void CSignOnDlg::KeyDown (KeyEvt)
{
	if (m_fModal) {
		GetParent() -> SetFocus();		
		EndDlg();
	}
	else Hide();
}

///////////////////////////////////////////////////////////////////////////////
// Member für 256-Farb-Variante 
bool CSignOnDlg256::FInit (void)
{
CCurrentUser regKey (KEY_READ, g_cbRegConfig);
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
	BYTE *pBmp = NULL;
	char cbBuffer[_MAX_PATH];

		try {
		// BMP-Resource wegschreiben, damit sie dekomprimiert werden kann
		DWORD dwBmpSize = 0;
		char cbTempPath[_MAX_PATH];

			GetTempPath(sizeof(cbTempPath), cbTempPath);
			GetTempFileName(cbTempPath, "~TR", 0, cbBuffer);
			pBmp = (BYTE *)ReadResource (m_hInst, m_uiResIDBmp, dwBmpSize);
			if (!WriteBmpToDisk (cbBuffer, pBmp, dwBmpSize) || !m_bmpSignOn.FInit (cbBuffer)) 
				_com_issue_error(E_UNEXPECTED);
			
		} catch (...) {				// alle möglichen GP's fangen
			DeleteFile (cbBuffer);				// temp. File wieder löschen
			if (pBmp) delete pBmp;
			return false;
		}

	// aufräumen
		DeleteFile (cbBuffer);				// temp. File wieder löschen
		if (pBmp) delete pBmp;

	// Font generieren
	ResString rsArial (IDS_ARIAL, 20);

		try {
#if !defined(_TRIAS_OLDIMPLEMENTATION2)
			m_pFont = new CVFont (Swiss, Dimension (0, -12), rsArial);
			if (m_pFont) m_pFont -> Init();
			m_pFontP = new CVFont (Swiss, Dimension (0, -11), rsArial);
			if (m_pFontP) m_pFontP -> Init();
#else
			m_pFont = new Font (Swiss, Dimension (0, -12), rsArial);
			if (m_pFont) m_pFont -> Init();
			m_pFontP = new Font (Swiss, Dimension (0, -11), rsArial);
			if (m_pFontP) m_pFontP -> Init();
#endif // !defined(_TRIAS_OLDIMPLEMENTATION2)

		} catch (...) {
			;
		}
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

	ChangePosition (Point (((iScreenX-(CRc.Right()-CRc.Left()))/2),
						   ((iScreenY-(CRc.Top()-CRc.Bottom()))/2)
						  )
				   );
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// Liefert anzuzeigenden Text zu aktuellem Lizensierungsmode
os_string CSignOnDlg256::GetLicString ()
{
os_string str;

	switch (m_Lic.GetAuthOpt()) {
	case 0:		// RESTR_NONE
		{
			if (m_Lic.GetNumCopies() > 1)
				Format(str, IDS_UNLIMITED_COUNT, m_Lic.GetNumCopies());
			else
				Format(str, IDS_UNLIMITED);
		}
		break;

	case 1:		// RESTR_TIME
		{
		int iAllowed = m_Lic.GetNumAllowed();
		
			if (m_Lic.GetNumCopies() > 1)
				Format(str, IDS_LIMITEDBYTIME_COUNT, iAllowed - m_Lic.GetNumUsed(), iAllowed, m_Lic.GetNumCopies());
			else
				Format(str, IDS_LIMITEDBYTIME, iAllowed - m_Lic.GetNumUsed(), iAllowed);
		}
		break;

	case 2:		// RESTR_RUNS
		{
		int iAllowed = m_Lic.GetNumAllowed();
		
			if (m_Lic.GetNumCopies() > 1)
				Format(str, IDS_LIMITEDBYRUNS_COUNT, iAllowed - m_Lic.GetNumUsed(), iAllowed, m_Lic.GetNumCopies());
			else
				Format(str, IDS_LIMITEDBYRUNS, iAllowed - m_Lic.GetNumUsed(), iAllowed);
		}
		break;

	default:
		{
		ResString resNotRegistered (IDS_NOTREGISTEREDVERSION, 128);

			str = resNotRegistered.Addr();
		}
		break;		// snh
	}
	return str;
}

///////////////////////////////////////////////////////////////////////////////
// AnzeigeRoutine
void CSignOnDlg256::Expose (ExposeEvt)
{
	if (!m_fNativeLogo) {
		Draw (&m_bmpSignOn);	// lediglich Bitmap ausgeben
#if _TRiAS_VER < 0x0510
		PlaySound();			// und Sound spielen
#endif 
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

	if (m_pFont) {
		hF = (HFONT)SelectObject (hDC, m_pFont -> Handle(API_FONT_HFONT));
		fFontChanged = true;
	}
	
// Bitmap und Texte zeichnen
ResString resVersion3 (IDS_SIGNONNAME, 64);		// "#HK001112"

#if _TRiAS_VER < 0x0400
string strVersion1 (FakeTRiASName (!IsModal() ? IDS_SIGNONVERSION : IDS_SIGNONVERSION_MODAL));	// "Version 4.00.1151 (Debug)"
ResString resVersion2 ((0 != g_dwVer4) ? IDS_SIGNONCOPYRIGHT4 : IDS_SIGNONCOPYRIGHT, 128);
string strVersion2(resVersion2);
#elif _TRiAS_VER < 0x0420
string strVersion1 (FakeTRiASName (!IsModal() ? IDS_SIGNONVERSION : IDS_SIGNONVERSION_MODAL));	// "Version 4.00.1151 (Debug)"
ResString resVersion2 (IDS_SIGNONCOPYRIGHT4, 128);	// "Alle Rechte vorbehalten\nCopyright \251 1991 - 2000, TRiAS GmbH"
string strVersion2(resVersion2);
#else
// ab 4.20 steht oben die Produktbezeichnung
string resVersion (FakeTRiASName(!IsModal() ? IDS_SIGNONVERSION : IDS_SIGNONVERSION_MODAL));	// "Version 4.00.1151 (Debug)"
string strVersion2 (FakeTRiASName(IDS_SIGNONCOPYRIGHT42, resVersion.c_str(), resVersion3.Addr()));	// "Alle Rechte vorbehalten\nVersion 4.20.1272, #HK011010\nCopyright \251 1991 - 2000, TRiAS GmbH"

ResString resVersion1 (IDS_SIGNONNAME42, 128);
CRegKey regProdName;
char cbProdName[_MAX_PATH];
DWORD dwProdNameLen = sizeof(cbProdName);
string strVersion1(resVersion1);

	if (ERROR_SUCCESS == regProdName.Open(HKEY_CURRENT_USER, "Software", KEY_READ) &&
		ERROR_SUCCESS == regProdName.Open(regProdName, REG_COMPANY_KEY, KEY_READ) &&
		ERROR_SUCCESS == regProdName.Open(regProdName, REG_PRODUCT_KEY, KEY_READ) &&
		ERROR_SUCCESS == regProdName.Open(regProdName, "Config", KEY_READ) &&
		ERROR_SUCCESS == regProdName.QueryValue(cbProdName, "InstalledProduct", &dwProdNameLen) &&
		dwProdNameLen > 1)		// Nullbyte zählt mit
	{
		strVersion1 = cbProdName;
	} 
#endif // _TRiAS_VER < 0x0420
ResString resPName (IDS_PERSONALNAME, 64);		// "Version f\374r den internen Gebrauch"
ResString resPAddr (IDS_PERSONALADDRESS, 64);	// "TRiAS GmbH Potsdam"
ResString resDemoName (IDS_DEMONAME, 64);		// "Demoversion"
ResString resDemoAddr (IDS_DEMOADDRESS, 64);	// "f\374r den limitierten Gebrauch"

// einen Text vor der Bitmap ausgeben, damit der Font geladen wird
	TX_ASSERT(NULL != m_bmpSignOn.GetPalette());

	Draw (&m_bmpSignOn);	// Bitmap ausgeben

// VersionsZeilen
#if _TRiAS_VER < 0x0400
	if (0 == g_dwVer4) {
	// TRiAS V3.00
		SetTextColor (hDC, RGB (255, 255, 255));	// jetzt weiß
		SetRect (&rcP, 130, 168, 395, 140);
	} else 
#endif // _TRiAS_VER < 0x0400
	{
		SetTextColor (hDC, RGB (0, 0, 0));
#if _TRiAS_VER < 0x0400
		SetRect (&rcP, 130, 141, 440, 108);
#else
		SetRect (&rcP, 130, 153, 440, 120);
#endif // _TRiAS_VER < 0x0400
	}
	Justify (hDC, hDC, strVersion2.c_str(), NULL, &rcP, ATRight, true);

// Registriert für und RegNr mit kleinerem Font schreiben
	if (m_pFontP) {
	HFONT hFont = 0;
	
		if (m_pFontP)
			hFont = (HFONT)SelectObject (hDC, m_pFontP -> Handle(API_FONT_HFONT));
		if (!fFontChanged) {
			hF = hFont;
			fFontChanged = true;
		}
	}

// Version ausgeben
	{
	HPALETTE hPal = NULL;
	
#if _TRiAS_VER < 0x0400
		if (0 == g_dwVer4) {
		// TRiAS V3.00
			hPal = ::SelectPalette (hDC, m_bmpSignOn.GetPalette(), false);
			::RealizePalette (hDC);

		UINT uiColor = ::GetNearestPaletteIndex (m_bmpSignOn.GetPalette(), RGB(228, 187, 142));

			::SetRect (&rcP, 146, 304, 366, 321);
			::SetTextColor (hDC, PALETTEINDEX(uiColor));
		} else 
#endif // _TRiAS_VER < 0x0400
		{
#if _TRiAS_VER < 0x0420
			::SetRect (&rcP, 213, 65, 417, 65);
#else
			::SetRect (&rcP, 219, 65, 417, 65);
#endif _TRiAS_VER < 0x0420
			::SetTextColor (hDC, RGB(128, 128, 128));
		}

		Justify (hDC, hDC, strVersion1.c_str(), NULL, &rcP, ATLeft, true);
#if _TRiAS_VER < 0x0420
		Justify (hDC, hDC, resVersion3.Addr(), NULL, &rcP, ATRight, true);
#endif _TRiAS_VER < 0x0420
		if (NULL != hPal)
			::SelectPalette (hDC, hPal, false);
	}

// Personalisierung
// Versuchen Personalisierung aus der Registry zu lesen, ansonsten
// Voreinstellungen aus der Resource verwenden
#if _TRiAS_VER < 0x0400
	if (0 == g_dwVer4) {
	// TRiAS V3.00
		SetTextColor (hDC, RGB (255, 255, 255));	// jetzt wieder weiß
		SetRect (&rcP, 144, 250, 395, 205);
	} else 
#endif // _TRiAS_VER < 0x0400
	{
		SetTextColor (hDC, RGB (0, 0, 0));
		SetRect (&rcP, 144, 220, 440, 175);
	}

// weitere Textausgabe
#if _TRiAS_VER < 0x0400
	if (0 == g_dwVer4) {
	os_string str;
	CLocalMachine regName (KEY_READ, g_cbRegVersion);
	char cbRegEntry[65];
	DWORD dwLen = sizeof(cbRegEntry);
	ResString resNotRegistered (IDS_NOTREGISTEREDVERSION, 128);

		if (!regName.GetSubSZ (g_cbSerial, cbRegEntry, dwLen) || !IsLegalRegNumber (cbRegEntry)) 
		{
			str = resNotRegistered.Addr();
		}
		else {
			str = ResString (IDS_REGNR, 20);
			str += cbRegEntry;
		}
		str += g_cbNL;

	char cbRegComp[65], cbRegName[65];
	bool fIntern = IsInternalRegNumber(cbRegEntry);
	bool fDemo = IsDemoRegNumber (cbRegEntry);

		dwLen = sizeof(cbRegName);
		if (fIntern || fDemo || !regName.GetSubSZ (g_cbRegName, cbRegName, dwLen)) 
		{
			fIntern = true;
			strcpy (cbRegName, fDemo ? resDemoName : resPName);
		}
		
		dwLen = sizeof(cbRegComp);
		if (fIntern || fDemo || !regName.GetSubSZ (g_cbRegCompany, cbRegComp, dwLen)) 
		{
			fIntern = true;
			strcpy (cbRegComp, fDemo ? resDemoAddr : resPAddr);
		}

	// Registriert für
		str += cbRegComp; str += g_cbNL;					// companyname
		if (!fIntern && !fDemo)
			str += ResString(IDS_REGISTEREDFOR, 32);		// username
		str += cbRegName;

		Justify (hDC, hDC, str.c_str(), NULL, &rcP, ATRight, true);
	} else
#endif // _TRiAS_VER < 0x0400
	{
	// Neue Texte ausgeben
	bool fDemo = (0 == m_Lic.GetLevel()) ? true : false;
	bool fIntern = false;

	CLocalMachine regName (KEY_READ, g_cbRegVersion);	// Name und Organisation sind hier
	char cbRegComp[65], cbRegName[65];
	DWORD dwLen = sizeof(cbRegName);

		if (fDemo || !regName.GetSubSZ (g_cbRegName, cbRegName, dwLen) || 0 == dwLen) 
		{
			strcpy (cbRegName, fDemo ? resDemoName : resPName);
			fIntern = true;
		}

		dwLen = sizeof(cbRegComp);
		if (fDemo || fIntern || !regName.GetSubSZ (g_cbRegCompany, cbRegComp, dwLen)) 
		{
			strcpy (cbRegComp, fDemo ? resDemoAddr : resPAddr);
			fIntern = true;
		} 
		else if (0 == dwLen) {
		ResString resUnknownCompany (IDS_UNKNOWNCOMPANY, 64);

			strcpy (cbRegComp, resUnknownCompany);
		}

	// Text zusammensetzen
	os_string str (GetLicString());

	// Registriert für
		str += g_cbNL;
		if (fDemo) {
		// Sitecode mit anzeigen
			if (!m_Lic.IsValid()) {
			ResString resNoSiteCode (IDS_NOSITECODE, 64);

				str += resNoSiteCode;
			}
			else {
			ResString resSiteCode (IDS_SITECODE, 64);

				str += resSiteCode.Addr();
				str += m_Lic.GetSiteCode();
			}
			str += g_cbNL;
			str += cbRegName;
			str += g_cbSpace;
			str += cbRegComp; 					// companyname
		} 
		else {
			str += cbRegComp; 					// companyname
			str += g_cbNL;
			if (!fDemo && !fIntern)
				str += ResString(IDS_REGISTEREDFOR, 32);		// username
			str += cbRegName;
		}
		Justify (hDC, hDC, str.c_str(), NULL, &rcP, ATRight, true);
	}

#if _TRiAS_VER < 0x0510
	PlaySound();	// Sound spielen
#endif

	if (IsWinNT())
		Sleep (500);

#if _TRiAS_VER < 0x0400
	if (0 == g_dwVer4) {
	// TRiAS V3.00
		Pling (hDC, 305, 48, RGB(255, 255, 255));	// Pling machen
		Sleep (300);
		Pling (hDC, 376, 48, RGB(255, 255, 255));
	} else
#endif // _TRiAS_VER < 0x0400
	{
		Pling (hDC, 22, 61, RGB(255, 255, 255));		// Pling machen
	}
	
// hDC rücksetzen und freigeben
	::SetBkMode (hDC, ioBk);
	::SetTextColor (hDC, oTColor);
	if (fFontChanged) ::SelectObject (hDC, hF);
	::ReleaseDC (hWnd, hDC);
}

///////////////////////////////////////////////////////////////////////////////
//
bool CSignOnDlg256::WriteBmpToDisk (char *pFile, BYTE *pBmp, DWORD dwSize)
{
	if (pBmp == NULL) return false;
	
OFSTRUCT of;
HFILE fh = OpenFile (pFile, &of, OF_CREATE|OF_READWRITE|OF_SHARE_EXCLUSIVE);

	if (fh == HFILE_ERROR) return false;

bool fWritten = ((DWORD)_lwrite (fh, (LPCSTR)pBmp, dwSize) == dwSize);

	_lclose (fh);
	return fWritten;
}

///////////////////////////////////////////////////////////////////////////////
// 
#define PLINGROP	0x00b8074a	// weiß ist transparent, schwarz wird bunt
#define PLINGTIME	100

bool CSignOnDlg256::Pling (HDC hDC, int iX, int iY, COLORREF crPling)
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
HBRUSH hBr = CreateSolidBrush (crPling);
HBRUSH hOldBrush = (HBRUSH)SelectObject (hDCOff, hBr);

// PlingBereich kopieren
int xSrc = iX - dx/2;
int ySrc = iY - dy/2;

	BitBlt (hDCCopy, 0, 0, dx, dy, hDC, xSrc, ySrc, SRCCOPY);

// Plings generieren und ausgeben
DWORD dwDelta = 0;

	for (short i = 0; i < 8; i++) {
	// Zeit stoppen
		dwDelta = GetTickCount() + PLINGTIME;

	// Offscreen Bitmap initialisieren
		BitBlt (hDCOff, 0, 0, dx, dy, hDCCopy, 0, 0, SRCCOPY);
		BitBlt (hDCOff, 0, 0, dx, dy, hDCPling, (i%8)*dx, 0, PLINGROP);
		
	// ins Bild kopieren
		BitBlt (hDC, xSrc, ySrc, dx, dy, hDCOff, 0, 0, SRCCOPY);

	// den Rest der Zeit (100ms) verwarten
	LONG lSleep = (LONG)(dwDelta - GetTickCount());

		if (lSleep > 0) {
			if (lSleep > PLINGTIME)
				lSleep = PLINGTIME;
			Sleep(lSleep);
		}
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
