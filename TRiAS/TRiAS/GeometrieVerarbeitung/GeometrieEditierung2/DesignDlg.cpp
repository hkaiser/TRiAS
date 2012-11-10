// Definitionen: PropertySheet für Bildung von Hilfslinien
// File: DesignDlg.cpp
// W. Mörtl


#include "GeoEditP.h"

#include "DesignDlg.h"



#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif



///////////////////////////////////////////////////////////////////////////////////////////////
// globale Parameter
extern ResourceFile* pRF;



///////////////////////////////////////////////////////////////////////////////////////////////
// Konstruktor
#if defined (MSCC8)
#pragma warning (disable: 4355)	// Ausschalten von uninteressanten Warnungen
#endif
// durch den optionalen Parameter PSH_NOAPPLYNOW wird der ApplyButton ganz einfach übergangen
CDesignDlg::CDesignDlg (Point FixPt)
		  : CEditObjectSheet (ResString(ResID(IDS_DESIGNCAP,pRF),70), g_pTE->MVWind(),
							  PSH_NOAPPLYNOW),
		    m_OK (this, IDOK)/*,
			m_Cancel (this, IDCANCEL)*/
{
	m_FixPt = FixPt;
}
#if defined (MSCC8)
#pragma warning (default: 4355)
#endif


// --------------------------------------------------------------------------------------------
CDesignDlg::~CDesignDlg (void)
{
}


// --------------------------------------------------------------------------------------------
// Initialisierung der Sheet (Call-Back-Funktion)
void CDesignDlg::WindowInit (Event)
{
	m_OK.FInit();
//	m_Cancel.FInit();
	
// Position dieses Dialoges bestimmen
Point Pt = DialogPosition (m_FixPt, m_FixPt, GetSize());

//	_ASSERTE (Pt.X() >= 0);	// durch die Änderung in DialogPosition()
//	_ASSERTE (Pt.Y() >= 0);

	ChangePosition (Pt);	// Dialog positionieren

} // WindowInit


// --------------------------------------------------------------------------------------------
// ein Button der Sheet wurde gedrückt
void CDesignDlg::ButtonClick (ControlEvt e)
{
	switch ((uint) e.GetControlID())
	{
		case IDOK:
			PropSheet_PressButton (Handle(), PSBTN_OK);
			break;

		case IDCANCEL:
			PropSheet_PressButton (Handle(), PSBTN_CANCEL);
			break;
	}
} // ButtonClick
