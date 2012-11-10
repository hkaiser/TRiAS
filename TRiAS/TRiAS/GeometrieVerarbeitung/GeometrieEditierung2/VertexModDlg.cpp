// Definitionen: Dialogfenster für manuelle Modifizierung von Stützpunkten
// File: VertexModDlg.cpp
// W. Mörtl

#include "GeoEditP.h"

#include "VertexModDlg.h"


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
CVertexModifyDlg::CVertexModifyDlg (KoOrd x, KoOrd y, bool bDel)
    			: DialogWindow (g_pTE->MVWind(), ResID (IDD_MINIEDIT, pRF)),
    			  m_X (this, IDE_XKOORD),
    			  m_Y (this, IDE_YKOORD),
    			  m_OKButton (this, IDOK),
    			  m_DeleteButton (this, IDB_DELETE)
{
    StandardWerte (x, y, bDel);		// Standardwerte einstellen
}
#if defined (MSCC8)
#pragma warning (default: 4355)
#endif


// --------------------------------------------------------------------------------------------
// Destruktor
CVertexModifyDlg::~CVertexModifyDlg (void)
{
	DELETE_OBJ (m_pCT);
}


///////////////////////////////////////////////////////////////////////////////////////////////
// EventHandler	(Ereignishandler)
// Reaktion auf Button-Click
void CVertexModifyDlg::ButtonClick (ControlEvt e)
{
    switch ((uint)e.GetControlID())
    {
    	case IDOK:
    		EndDlg (BEENDEN);
    		break;
    		
    	case IDB_DELETE:
    		EndDlg (LOESCHEN);
    		break;

    	case IDCANCEL:
    		EndDlg (ABBRECHEN);
    		break;

    	default:
    		_ASSERTE (false);
    		break;
    }
} // ButtonClick


// --------------------------------------------------------------------------------------------
// Reaktion auf Eingabe in eines der Editierfelder
void CVertexModifyDlg::EditChange (ControlEvt e)
{
uint uiCE = (uint) e.GetControlID();

    if ((IDE_XKOORD != uiCE && IDE_YKOORD != uiCE) ||	// keine Modifikation der Editierfelder
    													// m_X bzw. m_Y
    	m_bIntern)	// programm-interne Modifikation der Editierfelder m_X bzw. m_Y
    	return;

// Koordinaten wurden extern durch Anwender verändert
int iXKS, iYKS;	// Anzahl der Vorkommastellen von m_X und m_Y
// metrische (bMetr == true) bzw. geodätische (false) Koordinaten
bool bMetr = DigitNumerator (iXKS, iYKS, &m_X, &m_Y, m_pCT);

    if (bMetr)
    {
    	if (m_XLen == iXKS && m_YLen == iYKS)
    		m_OKButton.Enable();
    	else
    		m_OKButton.Disable();
    }

} // EditChange


// --------------------------------------------------------------------------------------------
// Einstellung von Standardwerten
void CVertexModifyDlg::StandardWerte (KoOrd x, KoOrd y, bool bDel)
{
// Variablen initialisieren
    m_pCT = new CoordTransX();
    if (NULL == m_pCT) return;

// Voreinstellungen der Editierfelder
    m_X.SetNumEditMode (NumEditX::NEM_NoTest);
    m_Y.SetNumEditMode (NumEditX::NEM_NoTest);
    
    m_bIntern = true;	// programm-interne Modifikation der Editierfelder m_X bzw. m_Y
    DBCoordToNumEdit (x, y, &m_X, &m_Y, m_pCT);
    m_bIntern = false;

// DeleteButton sollte nur bei Linien- und Flächenobjekten freigegeben werden, wenn sich Dialog
// auf einen Stützpunkt bezieht
    if (bDel)
    	m_DeleteButton.Enable();
    else
    	m_DeleteButton.Disable();
    
// weitere Member initialisieren
    // Anzahl der Vorkomma-Stellen von m_X und m_Y ermitteln
    DigitNumerator (m_XLen, m_YLen, &m_X, &m_Y, m_pCT);

} // StandardWerte


// --------------------------------------------------------------------------------------------
// (modifizierte) Koordinaten auslesen; wurden die Koordinaten tatsächlich verändert, ist der
// return-Wert "true"
bool CVertexModifyDlg::GetCoordinates (KoOrd& ResultX, KoOrd& ResultY)
{
    NumEditToDBCoord (&m_X, &m_Y, ResultX, ResultY, m_pCT);

    if (!m_X.GetEditControl()->isModified() &&
    	!m_Y.GetEditControl()->isModified())	
    	return false;	// keine der Koordinaten wurde geändert

    return true;

} // GetCoordinates


// --------------------------------------------------------------------------------------------
// Dialog positionieren; RMPt ist der BS-Punkt, bei dem die rechte Maustaste für das Menü
// gedrückt wurde
void CVertexModifyDlg::SetPosition (Point RMPt)
{
Point RefPt = DialogPosition (RMPt, RMPt, GetSize());

    ChangePosition (RefPt);

} // SetPosition
