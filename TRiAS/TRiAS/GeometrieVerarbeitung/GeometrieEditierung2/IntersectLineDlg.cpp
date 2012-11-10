// Definitionen: Dialogfenster bei Bildung einer Schnittlinie für Flächenteilung
// File: IntersectLineDlg.cpp
// W. Mörtl

#include "GeoEditP.h"

#include "IntersectLineDlg.h"


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
CIntersectionLineDlg::CIntersectionLineDlg (IObjektGeometrie* pISectLine)
    				: DialogWindow (g_pTE->MVWind(), ResID (IDD_MINIEDIT, pRF)),
    				  m_X (this, IDE_XKOORD),
    				  m_Y (this, IDE_YKOORD),
    				  m_OKButton (this, IDOK),
    				  m_DeleteButton (this, IDB_DELETE)
{
// Standardwerte einstellen
    m_pVWnd = g_pTE->MVWind();		// TRiAS-ViewFenster
	try
	{
		m_wSectLine = pISectLine;
	}
	catch (...)
	{
		_ASSERTE (false);
		return;
	}
    if (pISectLine) pISectLine->AddRef();

    StandardWerte();
}
#if defined (MSCC8)
#pragma warning (default: 4355)
#endif


// --------------------------------------------------------------------------------------------
// Destruktor
CIntersectionLineDlg::~CIntersectionLineDlg (void)
{
	DELETE_OBJ (m_pCT);
}


///////////////////////////////////////////////////////////////////////////////////////////////
// EventHandler	(Ereignishandler)
// Reaktion auf Button-Click
void CIntersectionLineDlg::ButtonClick (ControlEvt e)
{
    switch ((uint)e.GetControlID())
    {
    	case IDOK:
    		OKButtonAction();
    		EndDlg (OK);
    		return;
    		
    	case IDB_DELETE:
    		DeleteButtonAction();
    		return;

    	case IDCANCEL:
    		EndDlg (ABBRECHEN);
    		return;

    	default:
    		_ASSERTE (false);
    }
} // ButtonClick


// --------------------------------------------------------------------------------------------
// Reaktion auf Eingabe in eines der Editierfelder
void CIntersectionLineDlg::EditChange (ControlEvt e)
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
    	{
    		m_OKButton.Enable();
    		PunktKorrigieren();
    	}
    	else
    		m_OKButton.Disable();
    }
    else	// geodätische Datenbank
    	m_bGeodMod = true;

} // EditChange


// --------------------------------------------------------------------------------------------
// Einstellung von Standardwerten
void CIntersectionLineDlg::StandardWerte (void)
{
// Variablen initialisieren
    m_pCT = new CoordTransX();
    if (NULL == m_pCT) return;

// Voreinstellungen der Editierfelder
    m_X.SetNumEditMode (NumEditX::NEM_NoTest);
    m_Y.SetNumEditMode (NumEditX::NEM_NoTest);
    
// Koordinaten des letzten editierten Punktes im Editierfeld anzeigen
short iOT;
long lCnt;
KoOrd* plXK; KoOrd* plYK;

    m_wSectLine->GetObjTyp (&iOT);

    _ASSERTE (iOT == OT_KANTE);

    m_wSectLine->GetCnt (&lCnt);
    m_wSectLine->GetX ((void**)&plXK);
    m_wSectLine->GetY ((void**)&plYK);
    
KoOrd lRW = plXK[lCnt-1];	// Rechts- und
KoOrd lHW = plYK[lCnt-1];	// Hochwert (im KoOrd-Format) des zuletzt editierten Punktes
    
    m_bIntern = true;	// programm-interne Modifikation der Editierfelder m_X bzw. m_Y
    DBCoordToNumEdit (lRW, lHW, &m_X, &m_Y, m_pCT);
    m_bIntern = false;

// weitere Member initialisieren
    m_OKButton.Enable();
    m_DeleteButton.Enable();
    
    // Anzahl der Vorkomma-Stellen von m_X und m_Y ermitteln
    DigitNumerator (m_XLen, m_YLen, &m_X, &m_Y, m_pCT);

    // in m_X bzw. m_Y wurden bei geodätischer Datenbank durch den Anwender noch keine
    // Änderungen vorgenommen
    m_bGeodMod = false;

} // StandardWerte


// --------------------------------------------------------------------------------------------
// Reaktion auf OKButton
void CIntersectionLineDlg::OKButtonAction (void)
{
    if (m_bGeodMod)	// m_X bzw. m_Y wurden bei geodätischer Datenbank durch Anwender verändert
    {
    	PunktKorrigieren();
    	m_bGeodMod = false;	// doppelte Korrektur muß nicht sein
    }

} // OKButtonAction


// --------------------------------------------------------------------------------------------
// Reaktion auf DeleteButton;
// Löschen des zuletzt editierten Stützpunktes bei Aufbau der Schnittlinie für die
// Flächenteilung (kann mehrfach hintereinander ausgeführt werden); wenn für die Schnittlinie
// nur (noch) ein Stützpunkt vorhanden ist, wird der DeleteButton deaktiviert; soll auch dieser
// Stützpunkt gelöscht werden, ist der CancelButton zu verwenden, der gleichzeitig das gesamte
// Objekt löscht.
void CIntersectionLineDlg::DeleteButtonAction (void)
{
long lCnt;	// Anzahl der bisher editierten Stützpunkte der Schnittlinie

    m_wSectLine->GetCnt (&lCnt);

    _ASSERTE (lCnt >= 2);

    if (lCnt < 2) return;	// dieser Zweig dürfte eigentlich gar nicht erreicht werden

// den zuletzt editierten Stützpunkt in m_wSectLine löschen
KoOrd* plXK; KoOrd* plYK;

    m_wSectLine->GetX ((void**)&plXK);
    m_wSectLine->GetY ((void**)&plYK);

EPunkt EP1, EP2;		// manuell editierte Stützpunkte

    EP1.X() = plXK[lCnt-1];	// der letzte und
    EP1.Y() = plYK[lCnt-1];
    EP2.X() = plXK[lCnt-2];	//  der vorletzte manuell editierte Stützpunkt
    EP2.Y() = plYK[lCnt-2];

short iKontInd;	// für SubPunkt(), wird hier nicht ausgewertet

    m_wSectLine->SubPunkt (lCnt-1, &iKontInd);

    // Koordinaten des vorletzten Punktes anzeigen
    m_bIntern = true;	// programm-interne Modifikation der Editierfelder m_X bzw. m_Y
    DBCoordToNumEdit (EP2.X(), EP2.Y(), &m_X, &m_Y, m_pCT);
    m_bIntern = false;

    // die letzte Strecke zwischen EP2 und EP1 wird auf dem Bildschirm gelöscht
    DrawLine (EP2, EP1, false, m_pVWnd);

	m_OKButton.Disable();	// 
    if (lCnt >= 3)
    	m_DeleteButton.Enable();
    else
    	m_DeleteButton.Disable();

} // DeleteButtonAction


// --------------------------------------------------------------------------------------------
// letzten Punkt der editierten Schnittlinie aufgrund von Eingaben des Anwenders modifizieren
void CIntersectionLineDlg::PunktKorrigieren (void)
{
EPunkt EP1, EP2;	// manuell editierte Stützpunkte
EPunkt NewPkt;		// neuer Punkt in DB-Koordinaten

    // DB-Koordinaten aus DoubleNumEdit rekonstruieren					
    NumEditToDBCoord (&m_X, &m_Y, NewPkt.X(), NewPkt.Y(), m_pCT);

long lCnt;					//  Gesamtanzahl der Stützpunkte und 
KoOrd* plXK; KoOrd* plYK;	//  x- bzw. y-Koordinaten der Schnittlinie

    m_wSectLine->GetCnt (&lCnt);
    m_wSectLine->GetX ((void**)&plXK);
    m_wSectLine->GetY ((void**)&plYK);

    _ASSERTE (lCnt >= 2);

    EP1.X() = plXK[lCnt-1];	// der letzte und
    EP1.Y() = plYK[lCnt-1];
    EP2.X() = plXK[lCnt-2];	//  der vorletzte manuell editierte Stützpunkt
    EP2.Y() = plYK[lCnt-2];
    DrawLine (EP2, EP1, false, m_pVWnd);	// Linie auf Bildschirm löschen
    DrawLine (EP2, NewPkt, false, m_pVWnd);	// Linie neu zeichnen

    plXK[lCnt-1] = NewPkt.X();	// Punktkoordinaten modifizieren
    plYK[lCnt-1] = NewPkt.Y();

} // PunktKorrigieren


// --------------------------------------------------------------------------------------------
// (modifizierte) Koordinaten einlesen
bool CIntersectionLineDlg::GetCoordinates (KoOrd& ResultX, KoOrd& ResultY)
{
    if (!m_X.GetEditControl()->isModified() &&
    	!m_Y.GetEditControl()->isModified())
    	return false;	// keine der Koordinaten wurde geändert

    return NumEditToDBCoord (&m_X, &m_Y, ResultX, ResultY, m_pCT);

} // GetCoordinates
