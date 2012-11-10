// EigenschaftsDialogfenster --------------------------------------------------
// File: COORDP16.CXX

#include "begeodp.hxx"

#include <xtensnn.h> 

#include "begeod.h"

#include "numeditx.hxx"
#include "coordp16.hxx"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern "C" char g_pDLLName[260];

// Konstruktor/Destruktor/Initialisierung -------------------------------------

#pragma warning (disable:4355)

CCTFParams16 :: CCTFParams16 (pWindow pParent, ResID resID,
			  COORDTRANSFORMTYPE &rCTF, COORDTRANSFORMMODE &rCTFMode, 
			  int &riM, int &riS)
	    : DialogWindow (pParent, resID),
	      m_rbNative (this, IDC_GEOCOORDS),
	      m_rbTransMerc (this, IDC_GAUCOORDS),
	      m_cbMeridian (this, IDC_MERIDIAN), 
	      m_ftMeridian (this, IDT_MERIDIAN),
	      m_cbStrBreite (this, IDC_STRBREITE),
	      m_ftStrBreite (this, IDT_STRBREITE),
	      m_cbSave (this, IDC_SAVE),
		  m_rbAutoMeridian (this, IDC_AUTOMERIDIAN),
		  m_rbSelectMeridian (this, IDC_SELECTMERIDIAN),
	      m_rCTFType(rCTF), m_rCTFMode (rCTFMode),
		  m_riMeridian(riM), m_riStrBreite(riS)
{
// Minimale/maximale Meridian berechnen
	CalcMeridians();

// Controls initialisieren
	m_rbNative.SetState (false);
	m_rbTransMerc.SetState (false);
	SwitchState (rCTF, rCTFMode);		// Radiobuttons richten

	m_cbSave.SetChecked(false);	// erstmal nicht speichern

// Comboboxen füllen
	m_cbStrBreite.AddString("3");
	m_cbStrBreite.AddString("6");
	m_cbStrBreite.ChangeCurrentIndex (riS == 3 ? 0 : 1);

	FillMeridian (riS, riM);
}

#pragma warning (default:4355)

CCTFParams16 :: ~CCTFParams16 (void)
{
	// nothing to do
}

void CCTFParams16 :: SwitchState (COORDTRANSFORMTYPE rgCTF, COORDTRANSFORMMODE rgCTFMode)
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
		break;

	case CTF_TransMercator:
		m_rbNative.SetState (false);
		m_rbTransMerc.SetState (true);
		m_ftStrBreite.Enable();
		m_cbStrBreite.Enable();
		m_ftMeridian.Enable();
		m_rbAutoMeridian.Enable();
		m_rbSelectMeridian.Enable();
		if (CTFMODE_AutoMeridian == rgCTFMode) {
			m_rbAutoMeridian.SetState (true);
			m_rbSelectMeridian.SetState (false);
			m_cbMeridian.Disable();
		} else {
			m_rbAutoMeridian.SetState (false);
			m_rbSelectMeridian.SetState (true);
			m_cbMeridian.Enable();
		}
		break;

	default:
		TX_ASSERT(false);
		break;
	}
}

void CCTFParams16 :: FillMeridian (int iStrBreite, int iMeridian)
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

void EXPORTCTF CCTFParams16 :: ButtonClick (ControlEvt e)
{
	switch ((uint)e.GetControlID()) {
	case IDOK:
	// Werte zurückschreiben
		m_riStrBreite = GetStrBreite();
		m_riMeridian = GetMeridian();
		if (m_rbNative.GetState()) 
			m_rCTFType = CTF_Native;
		else
			m_rCTFType = CTF_TransMercator;

		if (m_rbAutoMeridian.GetState())
			m_rCTFMode = CTFMODE_AutoMeridian;
		else
			m_rCTFMode = CTFMODE_SelectMeridian;

	// evtl. Voreinstellungen ändern		
		if (m_cbSave.isChecked()) {
		ResourceFile RF (g_pDLLName);

			{
			// 0: geodätische Koordinaten anzeigen
			// 1: GK mit vorgegebenem Meridian anzeigen
			// 2: GK mit automatisch ausgewähltem Meridian anzeigen
			HeaderEntryX HE (ResString (ResID (IDS_SHOWGKCOORDS, &RF), 30));

				HE.SetEntryText (m_rbNative.GetState() ? "0" : 
									(m_rbAutoMeridian.GetState() ? "2" : "1"));
				HE.WriteBack();
			}
			if (!m_rbNative.GetState()) {
			char cbBuffer[30];
			HeaderEntryX heMeridian (ResString (ResID (IDS_COORDMERIDIAN, &RF), 30));
			HeaderEntryX heBreite (ResString (ResID (IDS_COORDSTRBREITE, &RF), 30));

				if (!m_rbAutoMeridian.GetState())
					m_cbMeridian.GetText (cbBuffer, sizeof(cbBuffer)-1);
				else
					strcpy (cbBuffer, "AutoSelect");

				heMeridian.SetEntryText (cbBuffer);
				heMeridian.WriteBack();
				m_cbStrBreite.GetText (cbBuffer, sizeof(cbBuffer));
				heBreite.SetEntryText (cbBuffer);
				heBreite.WriteBack();
			}
		}
		DEXN_CoordFormatChanged();
		EndDlg (1);
		break;

	case IDCANCEL:
		EndDlg();
		break;

	case IDC_GEOCOORDS:
		SwitchState (CTF_Native);
		break;

	case IDC_GAUCOORDS:
		SwitchState (CTF_TransMercator);
		break;

	case IDC_AUTOMERIDIAN:
		SwitchState (m_rbNative.GetState() ? CTF_Native : CTF_TransMercator, 
				     CTFMODE_AutoMeridian);
		break;

	case IDC_SELECTMERIDIAN:
		SwitchState (m_rbNative.GetState() ? CTF_Native : CTF_TransMercator, 
				     CTFMODE_SelectMeridian);
		break;
	}
}

void EXPORTCTF CCTFParams16 :: ListBoxSel (ControlEvt e)
{
	if (IDC_STRBREITE == (uint)e.GetControlID()) {
	int iIndex = m_cbStrBreite.GetCurrentIndex();

		TX_ASSERT(0 == iIndex || 1 == iIndex);
		FillMeridian ((iIndex+1)*3, GetMeridian());
		if (m_rbSelectMeridian.GetState())
			m_cbMeridian.SetFocus();
	}
}

int CCTFParams16 :: GetStrBreite (void)
{
int iIndex = m_cbStrBreite.GetCurrentIndex();
char cbBuffer[20];

	if (-1 == iIndex) iIndex = 0;
	m_cbStrBreite.GetString (cbBuffer, iIndex, sizeof(cbBuffer));

return atoi(cbBuffer);
}

int CCTFParams16 :: GetMeridian (void)
{
int iIndex = m_cbMeridian.GetCurrentIndex();
char cbBuffer[20];

	if (-1 == iIndex) iIndex = 0;
	m_cbMeridian.GetString (cbBuffer, iIndex, sizeof(cbBuffer));

return atoi(cbBuffer);
}

// Minimale/maximale Meridiane berechnen --------------------------------------
void CCTFParams16 :: CalcMeridians (void)
{
// GeoDB-Container in Grad besorgen
long lCont[4];

	DEX_GetProjectCont (lCont);

double K11 = HeaderEntryX (ResString(IDS_KOEFF11, 17)).EntryDouble(1.0);
double K12 = HeaderEntryX (ResString(IDS_KOEFF12, 17)).EntryDouble(0.0);
double OX = HeaderEntryX (ResString(IDS_OFFSETX, 17)).EntryDouble(0.0);
int iMin = int((K11 * (double)lCont[0] + K12 * (double)lCont[2] + OX) / 3600.0) - 1;
int iMax = int((K11 * (double)lCont[1] + K12 * (double)lCont[3] + OX) / 3600.0) + 1;

// 3 Grad-Meridiane berechenen
	m_iMin3 = (iMin/3)*3;
	m_iMax3 = (iMax/3)*3;

// 6 Grad-Meridiane berechnen
	m_iMin6 = (iMin/6)*6 +3;
	m_iMax6 = (iMax/6)*6 +3;
}
