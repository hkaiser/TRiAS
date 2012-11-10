// EigenschaftsDialogfenster --------------------------------------------------
// File: COORDPAR.CXX

#include "begeodp.hxx"

#include <windowsx.h>
#include <xtensnn.h> 

#include "begeod.h"

#include "numeditx.hxx"
#include "coordpar.hxx"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern "C" char g_pDLLName[260];

extern bool g_fAllowChangeEllipse;	// EllipsoidWechsel erlauben

// Konstruktor/Destruktor/Initialisierung -------------------------------------

#pragma warning (disable:4355)

CCTFParams::CCTFParams (ResID resID, ResID resIDCap, 
	COORDTRANSFORMTYPE &rCTF, COORDTRANSFORMMODE &rCTFMode, 
	int &riM, int &riS, int &riPrec, COORDTRANSELLIPSE  &rfCE)
	    : CPropertyPage (resID,	ResString (resIDCap, 32)),
	      m_rbNative (this, IDC_GEOCOORDS),
	      m_rbTransMerc (this, IDC_GAUCOORDS),
	      m_cbMeridian (this, IDC_MERIDIAN), 
	      m_ftMeridian (this, IDT_MERIDIAN),
	      m_cbStrBreite (this, IDC_STRBREITE),
	      m_ftStrBreite (this, IDT_STRBREITE),
		  m_rbAutoMeridian (this, IDC_AUTOMERIDIAN),
		  m_rbSelectMeridian (this, IDC_SELECTMERIDIAN),
	      m_rCTFType(rCTF), m_rCTFMode (rCTFMode),
		  m_riMeridian(riM), m_riStrBreite(riS), m_riPrec (riPrec),
		  m_rrgChangeEllipse(rfCE),
		  m_sbPrec (this, IDC_PRECISIONSPIN), 
		  m_slePrec (this, IDC_PRECISION),
		  m_ftCoordSystem (this, IDC_COORDSYSTEM),
		  m_cbCoordSystem (this, IDC_SELELLIPSE)
{
// 3 Grad-Meridiane initialisieren
	m_iMin3 = 0;
	m_iMax3 = 0;

// 6 Grad-Meridiane initialisieren
	m_iMin6 = 0;
	m_iMax6 = 0;

	m_hFont = NULL;
}

#pragma warning (default:4355)

CCTFParams :: ~CCTFParams (void)
{
	if (NULL != m_hFont) {
	HWND hCtrl = ::GetDlgItem (Handle(), IDC_COORDSYSTEM);
	HFONT hFont = GetWindowFont (hCtrl);
	
		SetWindowFont (hCtrl, m_hFont, false);
		::DeleteObject (hFont);
	}
}

void CCTFParams :: SwitchState (COORDTRANSFORMTYPE rgCTF, COORDTRANSFORMMODE rgCTFMode)
{
	switch (rgCTF) {
	case CTF_Native:
		m_rbTransMerc.SetState (false);
		m_rbNative.SetState (true);
		m_ftStrBreite.Disable();
		m_cbStrBreite.Disable();
		m_ftMeridian.Disable();
		m_cbMeridian.Disable();
		m_rbAutoMeridian.SetState(true);
		m_rbAutoMeridian.Disable();
		m_rbSelectMeridian.Disable();
		m_sbPrec.Disable();
		m_slePrec.Disable();
		m_cbCoordSystem.Disable();
		break;

	case CTF_TransMercator:
		m_rbNative.SetState (false);
		m_rbTransMerc.SetState (true);
		m_ftStrBreite.Enable();
		m_cbStrBreite.Enable();
		m_ftMeridian.Enable();
		m_rbAutoMeridian.Enable();
		m_rbSelectMeridian.Enable();
		m_cbCoordSystem.Enable();

		if (m_cbMeridian.GetCount() > 0) {
			if (CTFMODE_AutoMeridian == rgCTFMode) {
				m_rbAutoMeridian.SetState (true);
				m_rbSelectMeridian.SetState (false);
				m_cbMeridian.Disable();
			} else {
				m_rbAutoMeridian.SetState (false);
				m_rbSelectMeridian.SetState (true);
				m_cbMeridian.Enable();
			}
		} else {
			m_rbAutoMeridian.SetState (true);
			m_rbSelectMeridian.SetState (false);
			m_cbMeridian.Disable();
			if (CTFMODE_SelectMeridian == rgCTFMode) 
				MessageBeep (MB_ICONASTERISK);
		}
		m_sbPrec.Enable();
		m_slePrec.Enable();
		break;

	default:
		TX_ASSERT(false);
		break;
	}
}

void CCTFParams :: FillMeridian (int iStrBreite, int iMeridian)
{
char cbBuffer[20];
int iAct = 0;
int iRes = 0;

	m_cbMeridian.Clear();		// leermachen
	if (iStrBreite == 3) {
		for (int i = m_iMin3; i <= m_iMax3; i += 3) {
			_itoa (i, cbBuffer, 10);
		
		int iCurr = m_cbMeridian.AddString (cbBuffer);

			if (iMeridian == i) iAct = iCurr;
		}
	} else {
		for (int i = m_iMin6; i <= m_iMax6; i += 6) {
			_itoa (i, cbBuffer, 10);
		
		int iCurr = m_cbMeridian.AddString (cbBuffer);

			if (iMeridian == i) iAct = iCurr;
			else if (m_riMeridian == i) iRes = iCurr; 
		}
	}

	if (0 == iAct) iAct = iRes;
	m_cbMeridian.ChangeCurrentIndex (iAct);
}


///////////////////////////////////////////////////////////////////////////////
// EventHandler

void CCTFParams::WindowInit (Event)
{
// Controls initialisieren
	m_rbNative.FInit();
	m_rbTransMerc.FInit();
	m_cbMeridian.FInit();
	m_ftMeridian.FInit();
	m_cbStrBreite.FInit();
	m_ftStrBreite.FInit();
	m_sbPrec.FInit();
	m_slePrec.FInit();
	m_rbAutoMeridian.FInit();
	m_rbSelectMeridian.FInit();
	m_ftCoordSystem.FInit();
	m_cbCoordSystem.FInit();

ResourceFile RF (g_pDLLName);

	if (g_fAllowChangeEllipse) {
#if defined(ELLIPSE_BESSEL)
	ResString resEllipse0 (ResID (IDS_BESSEL_ELLIPSE, &RF), 120);
	ResString resEllipse1 (ResID (IDS_KRASSOVSKY_ELLIPSE, &RF), 120);
	ResString resEllipse2 (ResID (IDS_ETRS89_ELLIPSE, &RF), 120);
#define ETRS89_INDEX	2
#elif defined(ELLIPSE_KRASSOVSKI)
	ResString resEllipse0 (ResID (IDS_KRASSOVSKY_ELLIPSE, &RF), 120);
	ResString resEllipse1 (ResID (IDS_ETRS89_ELLIPSE, &RF), 120);
	ResString resEllipse2 (ResID (IDS_BESSEL_ELLIPSE, &RF), 120);
#define ETRS89_INDEX	1
#elif defined(ELLIPSE_ETRS89)
	ResString resEllipse0 (ResID (IDS_ETRS89_ELLIPSE, &RF), 120);
	ResString resEllipse1 (ResID (IDS_BESSEL_ELLIPSE, &RF), 120);
	ResString resEllipse2 (ResID (IDS_KRASSOVSKY_ELLIPSE, &RF), 120);
#define ETRS89_INDEX	0
#endif
		m_cbCoordSystem.AddString(resEllipse0);
		m_cbCoordSystem.AddString(resEllipse1);
		m_cbCoordSystem.AddString(resEllipse2);
		m_cbCoordSystem.Show();		// nur anzeigen, wenn verwendet
		m_cbCoordSystem.ChangeCurrentIndex (m_rrgChangeEllipse);
	}

	if (ETRS89_INDEX == m_rrgChangeEllipse) 
		m_rbTransMerc.SetText(ResString (ResID(IDS_UTMCOORDS, &RF), 32));
	else
		m_rbTransMerc.SetText(ResString (ResID(IDS_GKKOORDS, &RF), 32));


// Font des Textes des KoordSystemes FETT einstellen
HWND hCtrl = ::GetDlgItem (Handle(), IDC_COORDSYSTEM);

	if (NULL != hCtrl) {
	HFONT hFont = GetWindowFont (hCtrl);
	LOGFONT lf;

		::GetObject (hFont, sizeof(LOGFONT), &lf);
		lf.lfWeight = FW_BOLD;

		hFont = ::CreateFontIndirect (&lf);
		if (NULL != hFont) {
			m_hFont = GetWindowFont (hCtrl);
			SetWindowFont (hCtrl, hFont, true);
		}
	}

string strDesc = ResString (ResID (IDS_INTERNALKOORDS_DLG, &RF), 64);

#if defined(ELLIPSE_BESSEL)
ResString resEllipse (ResID (IDS_BESSEL_ELLIPSE, &RF), 120);
#elif defined(ELLIPSE_KRASSOVSKI)
ResString resEllipse (ResID (IDS_KRASSOVSKY_ELLIPSE, &RF), 120);
#elif defined(ELLIPSE_ETRS89)
ResString resEllipse (ResID (IDS_ETRS89_ELLIPSE, &RF), 120);
#else
#error "No Ellipse defined!"
#endif // ELLIPSES 

	strDesc += resEllipse;
	m_ftCoordSystem.SetText (strDesc.c_str());	// internes KoordSystem setzen

// Minimale/maximale Meridian berechnen
	CalcMeridians();

// Comboboxen füllen
	m_cbStrBreite.AddString("3");
	m_cbStrBreite.AddString("6");
	m_cbStrBreite.ChangeCurrentIndex (3 == m_riStrBreite ? 0 : 1);

	FillMeridian (m_riStrBreite, m_riMeridian);

// Controls initialisieren
	SwitchState (m_rCTFType, m_rCTFMode);		// Radiobuttons richten

// Precision initialisieren
	m_sbPrec.SetRange (0, 5);
	m_sbPrec.SetPos (m_riPrec);
}

bool CCTFParams::OnOK (NotifyEvt e)
{
// Werte zurückschreiben
	m_riStrBreite = GetStrBreite();
	m_riMeridian = GetMeridian();
	m_riPrec = GetPrecision();

	if (m_rbNative.GetState()) 
		m_rCTFType = CTF_Native;
	else
		m_rCTFType = CTF_TransMercator;

	if (m_rbAutoMeridian.GetState())
		m_rCTFMode = CTFMODE_AutoMeridian;
	else
		m_rCTFMode = CTFMODE_SelectMeridian;

int iIndex = 0;

	if (g_fAllowChangeEllipse) {
		iIndex = m_cbCoordSystem.GetCurrentIndex();
		TX_ASSERT(0 == iIndex || 1 == iIndex || 2 == iIndex);

		m_rrgChangeEllipse = (COORDTRANSELLIPSE)iIndex;
	}

// evtl. Voreinstellungen ändern		
	{
	ResourceFile RF (g_pDLLName);
	char cbBuffer[30];

	// ShowGKCoords
		{
		// 0: geodätische Koordinaten anzeigen
		// 1: GK mit vorgegebenem Meridian anzeigen
		// 2: GK mit automatisch ausgewähltem Meridian anzeigen
		// 0x04 bzw. 0x08: mit Übergang in den jeweils anderen Ellipsoid
		HeaderEntryX HE (ResString (ResID (IDS_SHOWGKCOORDS, &RF), 30));
		int iShow = 0;

			if (m_rbNative.GetState())
				iShow = 0;
			else if (m_rbAutoMeridian.GetState())
				iShow = 2;
			else
				iShow = 1;
			
			if (iIndex > 0) {
				TX_ASSERT(g_fAllowChangeEllipse);
				iShow |= 0x01 << (iIndex+1);
			} 

		char cbBuffer[32];

			HE.Flags() = HEADER_SYSTEM;
			HE.SetEntryText (ltoa (iShow, cbBuffer, 10));
			HE.WriteBack();
		}

	// CoordMeridian, CoordStrBreite
		if (!m_rbNative.GetState()) {
		HeaderEntryX heMeridian (ResString (ResID (IDS_COORDMERIDIAN, &RF), 30));
		HeaderEntryX heBreite (ResString (ResID (IDS_COORDSTRBREITE, &RF), 30));

			heMeridian.Flags() = HEADER_SYSTEMRO;
			if (!m_rbAutoMeridian.GetState())
				m_cbMeridian.GetText (cbBuffer, sizeof(cbBuffer)-1);
			else
				strcpy (cbBuffer, "AutoSelect");

			heMeridian.SetEntryText (cbBuffer);
			heMeridian.WriteBack();
			
			m_cbStrBreite.GetText (cbBuffer, sizeof(cbBuffer)-1);
			heBreite.Flags() = HEADER_SYSTEMRO;
			heBreite.SetEntryText (cbBuffer);
			heBreite.WriteBack();
		}

	// CoordPrecision
		{
		HeaderEntryX HE (ResString (ResID (IDS_CTFPRECISION, &RF), 30));

			m_slePrec.GetText (cbBuffer, sizeof(cbBuffer)-1);
			HE.Flags() = HEADER_SYSTEM;
			HE.SetEntryText (cbBuffer);
			HE.WriteBack();
		}
	}
	DEXN_CoordFormatChanged();
	SetModified (false);

return false;		// immer weitermachen
}

void CCTFParams :: ButtonClick (ControlEvt e)
{
	switch ((uint)e.GetControlID()) {
	case IDC_GEOCOORDS:
		SwitchState (CTF_Native);
		SetModified();
		break;

	case IDC_GAUCOORDS:
		SwitchState (CTF_TransMercator);
		SetModified();
		break;

	case IDC_AUTOMERIDIAN:
		SwitchState (m_rbNative.GetState() ? CTF_Native : CTF_TransMercator, 
				     CTFMODE_AutoMeridian);
		SetModified();
		break;

	case IDC_SELECTMERIDIAN:
		SwitchState (m_rbNative.GetState() ? CTF_Native : CTF_TransMercator, 
				     CTFMODE_SelectMeridian);
		SetModified();
		break;
	}
}

void CCTFParams::ListBoxSel (ControlEvt e)
{
	switch ((uint)e.GetControlID()) {
	case IDC_STRBREITE:
		{
		int iIndex = m_cbStrBreite.GetCurrentIndex();

			TX_ASSERT(0 == iIndex || 1 == iIndex);

			FillMeridian ((iIndex+1)*3, GetMeridian());
			if (m_rbSelectMeridian.GetState())
				m_cbMeridian.SetFocus();
			SetModified();
		}
		break;

	case IDC_SELELLIPSE:
		{
			TX_ASSERT(g_fAllowChangeEllipse);
			SetModified();

		ResourceFile RF (g_pDLLName);

			if (ETRS89_INDEX == m_cbCoordSystem.GetCurrentIndex()) 
				m_rbTransMerc.SetText(ResString (ResID(IDS_UTMCOORDS, &RF), 32));
			else
				m_rbTransMerc.SetText(ResString (ResID(IDS_GKKOORDS, &RF), 32));
		}
		break;
	}
}

void CCTFParams::EditChange (ControlEvt)
{
	SetModified();
}

///////////////////////////////////////////////////////////////////////////////
// sonstige member
int CCTFParams :: GetStrBreite (void)
{
int iIndex = m_cbStrBreite.GetCurrentIndex();
char cbBuffer[20];

	if (-1 == iIndex) iIndex = 0;
	m_cbStrBreite.GetString (cbBuffer, iIndex, sizeof(cbBuffer));

return atoi(cbBuffer);
}

int CCTFParams :: GetMeridian (void)
{
int iIndex = m_cbMeridian.GetCurrentIndex();
char cbBuffer[20];

	if (-1 == iIndex) iIndex = 0;
	m_cbMeridian.GetString (cbBuffer, iIndex, sizeof(cbBuffer));

return atoi(cbBuffer);
}

// Minimale/maximale Meridiane berechnen --------------------------------------
void CCTFParams :: CalcMeridians (void)
{
// GeoDB-Container in Grad besorgen
long lCont[4];

	DEX_GetProjectCont (lCont);

double K11 = HeaderEntryX (ResString(IDS_KOEFF11, 17)).EntryDouble(1.0);
double K12 = HeaderEntryX (ResString(IDS_KOEFF12, 17)).EntryDouble(0.0);
double OX = HeaderEntryX (ResString(IDS_OFFSETX, 17)).EntryDouble(0.0);

double dXMin = (K11 * (double)lCont[0] + K12 * (double)lCont[2] + OX);
double dXMax = (K11 * (double)lCont[1] + K12 * (double)lCont[3] + OX);

	m_iMin3 = int( (dXMin/3600.0 + 0.5)/3 ) * 3;
	m_iMin6 = int( (dXMin/3600.0 - 1.0)/6 ) * 6 + 3;

	m_iMax3 = int( (dXMax/3600.0 + 2.5)/3 ) * 3;
	m_iMax6 = int( (dXMax/3600.0 + 1.0)/6 ) * 6 + 3;

//int iMin = int((K11 * (double)lCont[0] + K12 * (double)lCont[2] + OX) / 3600.0) - 1;
//int iMax = int((K11 * (double)lCont[1] + K12 * (double)lCont[3] + OX) / 3600.0) + 1;

// 3 Grad-Meridiane berechenen
//	m_iMin3 = (iMin/3)*3;
//	m_iMax3 = (iMax/3)*3;

// 6 Grad-Meridiane berechnen
//	m_iMin6 = (iMin/6)*6 +3;
//	m_iMax6 = (iMax/6)*6 +3;
}

