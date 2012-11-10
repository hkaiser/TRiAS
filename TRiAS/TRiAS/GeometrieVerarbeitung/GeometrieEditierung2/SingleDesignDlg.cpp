// Deklarationen: Dialogfenster für Bildung von einfachen Hilfslinien
// File: SingleDesignDlg.cpp
// W. Mörtl

#include "GeoEditP.h"

#include "DesignDlg.h"

#include "SingleDesignDlg.h"


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
CSingleDesignDlg::CSingleDesignDlg (RestrType ResType, bool bRightAngle, double dRelAngle,
									double dLength, bool bWithAngle)
				: CPropertyPage (ResID (IDD_SINGLEDESIGNING, pRF), 
								 ResString (ResID (IDS_SINGLEDESIGNCAP, pRF), 32)),
				  m_RBttnSegment (this, IDR_STRECKE),
				  m_RBttnLine (this, IDR_GERADE),
				  m_RBttnCircle (this, IDR_KREIS),
				  m_RBttnAngle90 (this, IDR_ANGLE90),
				  m_RBttnAngleFree (this, IDR_ANGLEFREE),
				  m_Angle (this, IDE_ANGLE),
				  m_TextLength (this, IDT_DISTANCE),
				  m_Length (this, IDE_DISTANCE)
{
	m_bWithAngle = bWithAngle;
	m_ResType = ResType;
	m_bRightAngle = bRightAngle;
	m_dRelAngle = dRelAngle;
	m_dLength = dLength;
}
#if defined (MSCC8)
#pragma warning (default: 4355)
#endif


// --------------------------------------------------------------------------------------------
// Destruktor
CSingleDesignDlg::~CSingleDesignDlg (void)
{
}


///////////////////////////////////////////////////////////////////////////////////////////////
// Call-Back-Funktion für die Initialisierung der Controls
void CSingleDesignDlg::WindowInit (Event)
{
    m_pDesDlg = (CDesignDlg*)GetPropertySheet();

    // explizite Initialisierung der Controls
	m_RBttnSegment.FInit();
	m_RBttnLine.FInit();
	m_RBttnCircle.FInit();
    m_RBttnAngle90.FInit();
    m_RBttnAngleFree.FInit();
    m_Angle.FInit();
	m_TextLength.FInit();
    m_Length.FInit();

} // WindowInit


// --------------------------------------------------------------------------------------------
// wird gerufen, wenn OK-, Übernehmen- oder CloseButton gedrückt wurden
BOOL CSingleDesignDlg::OnOK (NotifyEvt)
{
    return FALSE;

} // OnOK


// --------------------------------------------------------------------------------------------
// wird gerufen, wenn diese Page aktiviert werden soll
BOOL CSingleDesignDlg::OnSetActive (NotifyEvt)
{
    ControlsSetting();

	// Mit nachfolgendem Befehl wird der Focus über eine PostMessage gesetzt. Das hat zur
	// Folge, daß diese Aktion erst dann ausgeführt wird, wenn Windows mit seinem Kram fertig
	// ist.
	// Dieser Umweg wurde erforderlich, weil ein in WindowInit() gesetzter Focus
	// (aus unklaren Gründen) durch Windows wieder gelöscht wird. 
	PostEvent (WM_WM_SETMYFOCUS);

    return FALSE;	// bei Gültigkeit "FALSE" sonst "TRUE" (???)

} // OnSetActive


// --------------------------------------------------------------------------------------------
// Reaktion auf WindowsMessages
LRESULT CSingleDesignDlg::Dispatch (Event e)
{
	if (WM_WM_SETMYFOCUS == e.Msg())
	{
		m_Length.SetFocus();
		return TRUE;	// Bedeutung des return-Wertes unklar !!!
	}

	return CPropertyPage::Dispatch (e);

} // Dispatch


// --------------------------------------------------------------------------------------------
// wird gerufen, wenn die diese Page deaktiviert werden soll; deshalb wird hier die Gültigkeit
// der Daten dieser Page überprüft (bei Gültigkeit "return FALSE" sonst "return TRUE")
BOOL CSingleDesignDlg::OnKillActive (NotifyEvt)
{
string str;

	if (m_RBttnSegment.GetState())
		m_ResType = RESTRTYPE_STRECKE;
	else if (m_RBttnLine.GetState())
		m_ResType = RESTRTYPE_GERADE;
	else if (m_RBttnCircle.GetState())
		m_ResType = RESTRTYPE_KREIS;
	else
	{
		_ASSERTE (m_RBttnSegment.GetState() || m_RBttnLine.GetState() ||
				   m_RBttnCircle.GetState());

		m_ResType = RESTRTYPE_UNKNOWN;
	}

	m_RBttnAngle90.GetState() ? (m_bRightAngle = true) : (m_bRightAngle = false);
	NumEditToString (&m_Angle, str);
	m_dRelAngle = atof (str.c_str());
	NumEditToString (&m_Length, str);
	m_dLength = atof (str.c_str());

	if (AdjustOK()) return FALSE;
		return TRUE;

} // OnKillActive


// --------------------------------------------------------------------------------------------
// Reaktion auf Button-Click
void CSingleDesignDlg::ButtonClick (ControlEvt e)
{
    switch ((uint)e.GetControlID())
    {
		case IDR_STRECKE:
			m_ResType = RESTRTYPE_STRECKE;
			m_RBttnAngle90.Enable();
			m_RBttnAngleFree.Enable();
			m_Angle.Enable();
			m_TextLength.SetText (ResString (ResID (IDS_LENGTH, pRF), 30).Addr());
			m_TextLength.Enable();
			m_Length.Enable();
    		break;

		case IDR_GERADE:
			m_ResType = RESTRTYPE_GERADE;
			m_RBttnAngle90.Enable();
			m_RBttnAngleFree.Enable();
			m_Angle.Enable();
			m_TextLength.SetText (ResString (ResID (IDS_LENGTH, pRF), 30).Addr());
			m_TextLength.Disable();
			m_Length.Disable();
    		break;
    		
		case IDR_KREIS:
			m_ResType = RESTRTYPE_KREIS;
			m_RBttnAngle90.Disable();
			m_RBttnAngleFree.Disable();
			m_Angle.Disable();
			m_TextLength.SetText (ResString (ResID (IDS_RADIUS, pRF), 30).Addr());
			m_TextLength.Enable();
			m_Length.Enable();
    		break;
    		
		case IDR_ANGLE90:
			m_bValidAngle = true;
    		break;
    		
		case IDR_ANGLEFREE:
		{
		string str;	// Parameter von GetStringParameter()

			if (NumEditToString (&m_Angle, str))
				m_bValidAngle = true;
			else
				m_bValidAngle = false;

			m_Angle.SetFocus();
    		break;
		}

    	default:
    		_ASSERTE (false);
    		break;
    }

	AdjustOK();

} // ButtonClick


// --------------------------------------------------------------------------------------------
// Reaktion auf Eingabe in eines der Editierfelder
void CSingleDesignDlg::EditChange (ControlEvt e)
{
uint uiCE = (uint) e.GetControlID();

    if ((IDE_ANGLE != uiCE &&		// KEINE Modifikation der Editierfelder
		IDE_DISTANCE != uiCE) ||	//  m_Angle bzw. m_Length bzw.
    	m_bIntern)	// programm-INTERNE Modifikation der Editierfelder m_Angle bzw. m_Length
    	return;

// Editierfelder m_Angle bzw. m_Length wurden EXTERN durch Anwender modifiziert
string str;	// Parameter von GetStringParameter()

    if (IDE_ANGLE == uiCE)						// Editierfeld m_Angle wurde modifiziert und
	{
		m_RBttnAngleFree.SetState (true);
		m_RBttnAngle90.SetState (false);

		if (NumEditToString (&m_Angle, str))	// enthält einen numerischen Eintrag
			m_bValidAngle = true;
		else
			m_bValidAngle = false;
	}

	else if (IDE_DISTANCE == uiCE)				// Editierfeld m_Length wurde modifiziert und
	{
		if (NumEditToString (&m_Length, str) &&	// enthält einen numerischen Eintrag, der
			atof (str.c_str()) > 0.)				// größer Null ist
			m_bValidLength = true;
		else
			m_bValidLength = false;
	}
	else _ASSERTE (uiCE == IDE_ANGLE || uiCE == IDE_DISTANCE);

	AdjustOK();

} // EditChange


// --------------------------------------------------------------------------------------------
// Controls dieser Page aktivieren/deaktivieren
void CSingleDesignDlg::ControlsSetting (void)
{
	if (m_bWithAngle)
	{
		m_RBttnSegment.Enable();
		m_RBttnLine.Enable();
		m_RBttnAngle90.Enable();
		m_RBttnAngleFree.Enable();
		m_Angle.Enable();
	}
	else
	{
		m_ResType = RESTRTYPE_KREIS;
		m_RBttnSegment.Disable();
		m_RBttnLine.Disable();
		m_RBttnAngle90.Disable();
		m_RBttnAngleFree.Disable();
		m_Angle.Disable();
	}

	m_RBttnSegment.SetState (false);
	m_RBttnLine.SetState (false);
	m_RBttnCircle.SetState (false);

	if (RESTRTYPE_STRECKE == m_ResType || RESTRTYPE_UNKNOWN == m_ResType)
		m_RBttnSegment.SetState (true);
	else if (RESTRTYPE_GERADE == m_ResType)
		m_RBttnLine.SetState (true);
	else	// RESTRTYPE_KREIS == m_ResType
	{
		m_RBttnCircle.SetState (true);
		m_TextLength.SetText (ResString (ResID (IDS_RADIUS, pRF), 30).Addr());
	}

	m_Angle.SetNumEditMode (NumEditX :: NEM_NoTest);
	m_Length.SetNumEditMode (NumEditX :: NEM_NoTest);

	if (m_bRightAngle)
	{
		m_RBttnAngle90.SetState (true);
		m_RBttnAngleFree.SetState (false);
	}
	else
	{
		m_RBttnAngle90.SetState (false);
		m_RBttnAngleFree.SetState (true);
	}

    m_bIntern = true;	// programm-interne Modifikation der Editierfelder m_Angle bzw. m_Length
	m_Angle.SetValue (m_dRelAngle);
	m_Length.SetValue (m_dLength);
	m_bValidAngle = true;
	m_bValidLength = true;
    m_bIntern = false;

} // ControlsSetting


// --------------------------------------------------------------------------------------------
// OKButton in der Sheet aktivieren/deaktivieren
bool CSingleDesignDlg::AdjustOK (void)
{
	if ((RESTRTYPE_STRECKE == m_ResType && m_bValidAngle && m_bValidLength) ||
		(RESTRTYPE_GERADE == m_ResType && m_bValidAngle) ||
		(RESTRTYPE_KREIS == m_ResType && m_bValidLength))
	{
		m_pDesDlg->SetOKButton();
		return true;
	}

	m_pDesDlg->SetOKButton (false);
	return false;
}

/*
// --------------------------------------------------------------------------------------------
// Auslesen des Eintrags aus dem DoubleNumEdit-Feld pEingWert und Rückgabe in sParam
bool CSingleDesignDlg::GetStringParameter (DoubleNumEditX* pEingWert, string& sParam)
{
	_ASSERTE (pEingWert != NULL);

	sParam = "";

	if (pEingWert->GetTextLen() > 0)
	{
	char pcInBuff [20];

		pEingWert->GetText (pcInBuff, sizeof(pcInBuff));

		if (0.0 == atof(pcInBuff) && NPOS == ((string)pcInBuff).find_first_of ("0"))
			return false;	// Editier-Feld ist leer

		sParam = pcInBuff;
		return true;
	}

	return false;

} // GetStringParameter
*/