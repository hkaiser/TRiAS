// Deklarationen: Dialogfenster für die Auswahl der Fixpunkte für Hilfslinien
// File: FixPointsDlg.cpp
// W. Mörtl

#include "GeoEditP.h"

#include "DesignDlg.h"

#include "FixPointsDlg.h"


#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif



///////////////////////////////////////////////////////////////////////////////////////////////
// externe Variable
extern ResourceFile* pRF;



///////////////////////////////////////////////////////////////////////////////////////////////
// Konstruktor
#if defined (MSCC8)
#pragma warning (disable: 4355)	// Ausschalten von uninteressanten Warnungen
#endif
CFixPointsDlg::CFixPointsDlg (KoOrd lRWK, KoOrd lHWK, KoOrd lRW1, KoOrd lHW1, KoOrd lRW2,
							  KoOrd lHW2)
			 : CPropertyPage (ResID (IDD_FIXPOINTS, pRF),
							  ResString (ResID (IDS_FIXPOINTSCAP, pRF), 32)),
				m_RBttnEnd2 (this, IDR_END2),
				m_RBttnEnd1 (this, IDR_END1),
				m_RBttnMiddle (this, IDR_MIDDLE),
				m_RBttnClick (this, IDR_MOUSECLICK),
				m_RWertK (this, IDT_RWK),
				m_HWertK (this, IDT_HWK),
				m_RWert1 (this, IDT_RW1),
				m_HWert1 (this, IDT_HW1),
				m_RWert2 (this, IDT_RW2),
				m_HWert2 (this, IDT_HW2),
				m_RWertM (this, IDT_RWM),
				m_HWertM (this, IDT_HWM)
{
	m_lRWK = lRWK;
	m_lHWK = lHWK;
	m_lRW1 = lRW1;
	m_lHW1 = lHW1;
	m_lRW2 = lRW2;
	m_lHW2 = lHW2;

	m_FixPkt.X() = m_lRW2;		// für den Fall, daß diese Page gar
	m_FixPkt.Y() = m_lHW2;		// nicht gerufen wird
    
    m_pCT = new CoordTransX();	// KoordinatenTransformation

    if (! m_pCT)
    	DEX_Error (RC_FixPointsDlg, EC_NOMEMORY);
}
#if defined (MSCC8)
#pragma warning (default: 4355)
#endif


// --------------------------------------------------------------------------------------------
// Destruktor
CFixPointsDlg::~CFixPointsDlg (void)
{
	DELETE_OBJ (m_pCT);
}


///////////////////////////////////////////////////////////////////////////////////////////////
// Call-Back-Funktion für die Initialisierung der Controls
void CFixPointsDlg::WindowInit (Event)
{
    // explizite Initialisierung der Controls
	m_RBttnClick.FInit();
	m_RBttnEnd1.FInit();
	m_RBttnEnd2.FInit();
	m_RBttnMiddle.FInit();
	m_RWertK.FInit();
	m_HWertK.FInit();
	m_RWert1.FInit();
	m_HWert1.FInit();
	m_RWert2.FInit();
	m_HWert2.FInit();
	m_RWertM.FInit();
	m_HWertM.FInit();

} // WindowInit


// --------------------------------------------------------------------------------------------
// wird gerufen, wenn diese Page aktiviert werden soll
BOOL CFixPointsDlg::OnSetActive (NotifyEvt)
{
	TextForEndpoints();
	ControlsSetting();

    return FALSE;	// bei Gültigkeit "FALSE" sonst "TRUE" (???)

} // OnSetActive


// --------------------------------------------------------------------------------------------
// wird gerufen, wenn die diese Page deaktiviert werden soll; deshalb wird hier die Gültigkeit
// der Daten dieser Page überprüft (bei Gültigkeit "return FALSE" sonst "return TRUE")
BOOL CFixPointsDlg::OnKillActive (NotifyEvt)
{
	if (m_RBttnClick.GetState())
	{
		m_FixPkt.X() = m_lRWK;
		m_FixPkt.Y() = m_lHWK;
	}
	else if (m_RBttnEnd1.GetState())
	{
		m_FixPkt.X() = m_lRW1;
		m_FixPkt.Y() = m_lHW1;
	}
	else if (m_RBttnEnd2.GetState())
	{
		m_FixPkt.X() = m_lRW2;
		m_FixPkt.Y() = m_lHW2;
	}
	else	// m_RBttnMiddle.GetState()
	{
		m_FixPkt.X() = m_lRWM;
		m_FixPkt.Y() = m_lHWM;
	}

	return FALSE;

} // OnKillActive


// --------------------------------------------------------------------------------------------
// Controls dieser Page definiert setzen
void CFixPointsDlg::ControlsSetting (void)
{
	m_RBttnEnd2.SetState (true);
	m_RBttnEnd1.SetState (false);
	m_RBttnMiddle.SetState (false);
	m_RBttnClick.SetState (false);

char pcOutBuff[TEXTL] = { '\0' };	// Konvertierungspuffer

	m_lRWM = DtoL ((m_lRW1 + m_lRW2) / 2.);
	m_lHWM = DtoL ((m_lHW1 + m_lHW2) / 2.);

    if (m_pCT)
    {
	double dRWK, dHWK, dRW1, dHW1, dRW2, dHW2, dRWM, dHWM;

		// Konvertierung der anzuzeigenden Koordinaten in Realkoordinaten
		DBKoordInReal (m_lRWK, m_lHWK, dRWK, dHWK, m_pCT);
		DBKoordInReal (m_lRW1, m_lHW1, dRW1, dHW1, m_pCT);
		DBKoordInReal (m_lRW2, m_lHW2, dRW2, dHW2, m_pCT);
		DBKoordInReal (m_lRWM, m_lHWM, dRWM, dHWM, m_pCT);

		m_pCT->CoordTransToStringEx (dRWK, dHWK, true, pcOutBuff, sizeof (pcOutBuff));
		m_RWertK.SetText (pcOutBuff);
		m_pCT->CoordTransToStringEx (dRWK, dHWK, false, pcOutBuff, sizeof (pcOutBuff));
		m_HWertK.SetText (pcOutBuff);
		m_pCT->CoordTransToStringEx (dRW1, dHW1, true, pcOutBuff, sizeof (pcOutBuff));
		m_RWert1.SetText (pcOutBuff);
		m_pCT->CoordTransToStringEx (dRW1, dHW1, false, pcOutBuff, sizeof (pcOutBuff));
		m_HWert1.SetText (pcOutBuff);
		m_pCT->CoordTransToStringEx (dRW2, dHW2, true, pcOutBuff, sizeof (pcOutBuff));
		m_RWert2.SetText (pcOutBuff);
		m_pCT->CoordTransToStringEx (dRW2, dHW2, false, pcOutBuff, sizeof (pcOutBuff));
		m_HWert2.SetText (pcOutBuff);
		m_pCT->CoordTransToStringEx (dRWM, dHWM, true, pcOutBuff, sizeof (pcOutBuff));
		m_RWertM.SetText (pcOutBuff);
		m_pCT->CoordTransToStringEx (dRWM, dHWM, false, pcOutBuff, sizeof (pcOutBuff));
		m_HWertM.SetText (pcOutBuff);
	}
	else
	{
		m_RWertK.SetText (ltoa (m_lRWK, pcOutBuff, 10));
		m_HWertK.SetText (ltoa (m_lHWK, pcOutBuff, 10));
		m_RWert1.SetText (ltoa (m_lRW1, pcOutBuff, 10));
		m_HWert1.SetText (ltoa (m_lHW1, pcOutBuff, 10));
		m_RWert2.SetText (ltoa (m_lRW2, pcOutBuff, 10));
		m_HWert2.SetText (ltoa (m_lHW2, pcOutBuff, 10));
		m_RWertM.SetText (ltoa (m_lRWM, pcOutBuff, 10));
		m_HWertM.SetText (ltoa (m_lHWM, pcOutBuff, 10));
	}

} // ControlsSetting


// --------------------------------------------------------------------------------------------
// Text für 2 RadioButton im Dialog ermitteln, der die Lage der beiden Endpunkte der
// Bezugsstrecke beschreibt
void CFixPointsDlg::TextForEndpoints (void)
{
string sRBttnTextB = ResString (ResID (IDS_BOTTOM, pRF), 30).Addr();
string sRBttnTextT = ResString (ResID (IDS_TOP, pRF), 30).Addr();

	if (m_lRW1 != m_lRW2)	// Bezugsstrecke nicht senkrecht
	{
	double m = (double)(m_lHW2 - m_lHW1) / (m_lRW2 - m_lRW1);	// Anstieg
	double tan70 = tan (70.*Pi/180.);

		if (m >= -tan70 && m <= tan70)
		{
		string sRBttnTextL = ResString (ResID (IDS_LEFT, pRF), 30).Addr();
		string sRBttnTextR = ResString (ResID (IDS_RIGHT, pRF), 30).Addr();

			if (m_lRW2 > m_lRW1)
			{
				m_RBttnEnd1.SetText (sRBttnTextL.c_str());	// 1. links
				m_RBttnEnd2.SetText (sRBttnTextR.c_str());	// 2. rechts
			}
			else
			{
				m_RBttnEnd1.SetText (sRBttnTextR.c_str());	// 1. rechts
				m_RBttnEnd2.SetText (sRBttnTextL.c_str());	// 2. links
			}
		}
		else	// m > tan70 || m < -tan70
		{
			if (m_lHW2 > m_lHW1)
			{
				m_RBttnEnd1.SetText (sRBttnTextB.c_str());	// 1. unten
				m_RBttnEnd2.SetText (sRBttnTextT.c_str());	// 2. oben
			}
			else
			{
				m_RBttnEnd1.SetText (sRBttnTextT.c_str());	// 1. oben
				m_RBttnEnd2.SetText (sRBttnTextB.c_str());	// 2. unten
			}
		}
	}
	else					// Bezugsstrecke senkrecht
	{
		if (m_lHW2 > m_lHW1)
		{
			m_RBttnEnd1.SetText (sRBttnTextB.c_str());	// 1. unten
			m_RBttnEnd2.SetText (sRBttnTextT.c_str());	// 2. oben
		}
		else if (m_lHW2 < m_lHW1)
		{
			m_RBttnEnd1.SetText (sRBttnTextT.c_str());	// 1. oben
			m_RBttnEnd2.SetText (sRBttnTextB.c_str());	// 2. unten
		}
		else
		{
			_ASSERTE (m_lRW1 != m_lRW2);
			_ASSERTE (m_lHW1 != m_lHW2);
		}
	}
} // TextForEndpoints
