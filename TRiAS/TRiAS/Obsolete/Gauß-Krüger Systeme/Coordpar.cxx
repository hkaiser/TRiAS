// EigenschaftsDialogfenster --------------------------------------------------
// File: COORDPAR.CXX

#include "besslgkp.hxx"

#include <windowsx.h>
#include <xtensnn.h> 

#include "besslres.h"

#include "numeditx.hxx"
#include "coordpar.hxx"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern "C" void FUNCTYPE PASCAL geogau (double, double, short, short, double, double, long double *, long double *);
extern "C" void FUNCTYPE PASCAL gaugeo (double, double, short, short, double, double, long double *, long double *);

extern "C" char g_pDLLName[260];

extern double HA;	// große Ellipsoid-Halbachse
extern double HB;	// kleine Ellipsoid-Halbachse
extern "C" int g_iStrBreiteDB;	// Streifenbreite der Datenbank
extern "C" int g_iMeridianDB;		// Mittelmeridian der Datenbank

// Konstruktor/Destruktor/Initialisierung -------------------------------------

#pragma warning (disable:4355)

CCTFParams :: CCTFParams (ResID resID, ResID resIDCap, COORDTRANSFORMMODE &rCTFMode, 
						  int &riM, int &riS, int &riPrec, double &rdScale)
	    : CPropertyPage (resID,	ResString (resIDCap, 32)),
	      m_cbMeridian (this, IDC_MERIDIAN), 
	      m_cbStrBreite (this, IDC_STRBREITE),
		  m_rbAutoMeridian (this, IDC_AUTOMERIDIAN),
		  m_rbSelectMeridian (this, IDC_SELECTMERIDIAN),
	      m_rCTFMode (rCTFMode),
		  m_riMeridian(riM), m_riStrBreite(riS), 
		  m_riPrec (riPrec), m_rdScale(rdScale),
		  m_sbPrec (this, IDC_PRECISIONSPIN), 
		  m_slePrec (this, IDC_PRECISION),
		  m_sbScale (this, IDC_SCALINGSPIN), 
		  m_dneScale (this, IDC_SCALING),
		  m_ftCoordSys (this, IDC_COORDSYSTEM)
{
// 6 Grad-Meridiane initialisieren
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

void CCTFParams :: SwitchState (COORDTRANSFORMMODE rgCTFMode)
{
	m_cbStrBreite.Enable();
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
	m_cbMeridian.FInit();
	m_cbStrBreite.FInit();
	m_sbPrec.FInit();
	m_slePrec.FInit();
	m_rbAutoMeridian.FInit();
	m_rbSelectMeridian.FInit();
	m_sbScale.FInit();
	m_dneScale.FInit();

// konkretes KoordinatenSystem einstellen
ResourceFile RF (g_pDLLName);
char cbOutBuff[128];

#if defined(ELLIPSE_BESSEL)
	wsprintf (cbOutBuff, ResString (ResID(IDS_DESCRIPTIONBESSEL, &RF), 64), g_iMeridianDB, g_iStrBreiteDB);
#elif defined(ELLIPSE_KRASSOVSKY)
	wsprintf (cbOutBuff, ResString (ResID(IDS_DESCRIPTIONKRASSOVSKY, &RF), 64), g_iMeridianDB, g_iStrBreiteDB);
#else
#error "No Ellipsoid defined."
#endif
	m_ftCoordSys.SetText (cbOutBuff);

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

// Minimale/maximale Meridian berechnen
	CalcMeridians();

// Comboboxen füllen
	m_cbStrBreite.AddString("3");
	m_cbStrBreite.AddString("6");
	m_cbStrBreite.ChangeCurrentIndex (3 == m_riStrBreite ? 0 : 1);

	FillMeridian (m_riStrBreite, m_riMeridian);

// Controls initialisieren
	SwitchState (m_rCTFMode);		// Radiobuttons richten

// Precision initialisieren
	m_sbPrec.SetRange (0, 5);
	m_sbPrec.SetPos (m_riPrec);

// Scaling initialisieren
	m_sbScale.SetRange (0, 10000);
	m_sbScale.SetPos (5000);
	m_dneScale.SetValue (m_rdScale);
}

bool CCTFParams::OnOK (NotifyEvt e)
{
// Werte zurückschreiben
	m_riStrBreite = GetStrBreite();
	m_riPrec = GetPrecision();
	m_rdScale = GetScaling();

	if (m_rbAutoMeridian.GetState()) {
		m_rCTFMode = CTFMODE_AutoMeridian;
		m_riMeridian = g_iMeridianDB;
	} else {
		m_rCTFMode = CTFMODE_SelectMeridian;
		m_riMeridian = GetMeridian();
	}

// evtl. Voreinstellungen ändern		
	{
	ResourceFile RF (g_pDLLName);
	char cbBuffer[30];

	// ShowGKCoords
		{
		// 1: GK mit vorgegebenem Meridian anzeigen
		// 0: GK mit automatisch ausgewähltem Meridian anzeigen
		HeaderEntryX HE (ResString (ResID (IDS_SHOWGKCOORDS, &RF), 30));

			HE.Flags() = HEADER_SYSTEM;
			HE.SetEntryText (m_rbAutoMeridian.GetState() ? "0" : "1");
			HE.WriteBack();
		}

	// CoordMeridian, CoordStrBreite
		{
		HeaderEntryX heMeridian (ResString (ResID (IDS_CTFMERIDIANVIEW, &RF), 30));
		HeaderEntryX heBreite (ResString (ResID (IDS_CTFSTREIFENVIEW, &RF), 30));

			heMeridian.Flags() = HEADER_SYSTEM;
			if (!m_rbAutoMeridian.GetState())
				m_cbMeridian.GetText (cbBuffer, sizeof(cbBuffer)-1);
			else
				strcpy (cbBuffer, "AutoSelect");

			heMeridian.SetEntryText (cbBuffer);
			heMeridian.WriteBack();
			
			m_cbStrBreite.GetText (cbBuffer, sizeof(cbBuffer)-1);
			heBreite.Flags() = HEADER_SYSTEM;
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

	// CoordScaling
		{
		HeaderEntryX HE (ResString (ResID (IDS_CTFSCALING, &RF), 30));

			m_dneScale.GetText (cbBuffer, sizeof(cbBuffer)-1);
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
	case IDC_AUTOMERIDIAN:
		SwitchState (CTFMODE_AutoMeridian);
		SetModified();
		break;

	case IDC_SELECTMERIDIAN:
		SwitchState (CTFMODE_SelectMeridian);
		SetModified();
		break;
	}
}

void CCTFParams :: ListBoxSel (ControlEvt e)
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

	case IDC_MERIDIAN:
		SetModified();
		break;
	}
}

void CCTFParams::EditChange (ControlEvt)
{
	SetModified();
}

bool CCTFParams::OnDeltaPos (NotifyEvt e)
{
	if (IDC_SCALINGSPIN == (uint)e.GetControlID()) {
	NM_UPDOWN *pNMData = (NM_UPDOWN *)e.GetNotifyInfo();
	double dDelta, dActVal;

		if (!m_dneScale.GetValue(dActVal)) {
			MessageBeep (MB_ICONHAND);
			return true;
		}
 
	// Schrittweite bestimmen
		if (pNMData -> iDelta > 0) {
			if (dActVal >= 100.0)
				dDelta = 100.0;
			else if (dActVal >= 10.0)
				dDelta = 10.0;
			else if (dActVal >= 1.0)
				dDelta = 1.0;
			else if (dActVal >= 0.1)
				dDelta = 0.1;
			else if (dActVal >= 0.01)
				dDelta = 0.01;
			else
				dDelta = 0.001;
		} else {
			if (dActVal > 100.0)
				dDelta = -100.0;
			else if (dActVal > 10.0)
				dDelta = -10.0;
			else if (dActVal > 1.0)
				dDelta = -1.0;
			else if (dActVal > 0.1)
				dDelta = -0.1;
			else if (dActVal > 0.01)
				dDelta = -0.01;
			else
				dDelta = -0.001;
		} 		

	// Wert muß größer als 0 sein
		if (dActVal + dDelta <= 0.0) {
			MessageBeep (MB_ICONHAND);
			return true;
		}

	// neuen Wert setzen
		m_dneScale.SetValue (dActVal + dDelta);
		SetModified();
	}

return false;		// allow operation
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

double CCTFParams :: GetScaling (void)
{
double dScale = 1.0;

	if (m_dneScale.GetValue(dScale))
		return dScale;

return dScale;
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
double K21 = HeaderEntryX (ResString(IDS_KOEFF21, 17)).EntryDouble(0.0);
double K22 = HeaderEntryX (ResString(IDS_KOEFF22, 17)).EntryDouble(1.0);
double OY = HeaderEntryX (ResString(IDS_OFFSETY, 17)).EntryDouble(0.0);

double dXMin = (K11 * (double)lCont[0] + K12 * (double)lCont[2] + OX);
double dXMax = (K11 * (double)lCont[1] + K12 * (double)lCont[3] + OX);
double dYMin = (K21 * (double)lCont[0] + K22 * (double)lCont[2] + OY);
double dYMax = (K21 * (double)lCont[1] + K22 * (double)lCont[3] + OY);

// minimale Meridiane berechnen
long double dX, dY;

	gaugeo (HA, HB, g_iStrBreiteDB, g_iMeridianDB, dYMin, dXMin, &dY, &dX);

	m_iMin3 = int( (dX/3600.0 + 0.5)/3 ) * 3;
	m_iMin6 = int( (dX/3600.0 - 1.0)/6 ) * 6 + 3;

// maximale Meridiane berechnen
	gaugeo (HA, HB, g_iStrBreiteDB, g_iMeridianDB, dYMax, dXMax, &dY, &dX);

	m_iMax3 = int( (dX/3600.0 + 2.5)/3 ) * 3;
	m_iMax6 = int( (dX/3600.0 + 1.0)/6 ) * 6 + 3;
}

