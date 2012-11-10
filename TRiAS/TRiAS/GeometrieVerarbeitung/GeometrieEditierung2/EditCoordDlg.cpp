// Definitionen: Dialog für Modifikation von Stützpunktkoordinaten
// File: EditCoordDlg.cpp
// W. Mörtl


#include "GeoEditP.h"

#include "EditDlg.h"		// CEditDlg
#include "EditCoordDlg.h"



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
CEditCoordDlg::CEditCoordDlg (int iCloseCnt, KoOrd* plCloseX, KoOrd* plCloseY, KoOrd x,
    						  KoOrd y)
    		 : CPropertyPage (ResID(IDD_COORDMODIFY, pRF),
    						  ResString (ResID(IDS_EDITCOORDCAP, pRF), 32)),
    		   m_X (this, IDE_XKOORD),
    		   m_Y (this, IDE_YKOORD),
			   m_DeleteButton (this, IDB_DELETE),
			   m_DeleteText (this, IDT_DELETE)
{
    StandardWerte (iCloseCnt, plCloseX, plCloseY, x, y);
}
#if defined (MSCC8)
#pragma warning (default: 4355)
#endif


// --------------------------------------------------------------------------------------------
CEditCoordDlg::~CEditCoordDlg (void)
{
	DELETE_OBJ (m_pCT);
}



// --------------------------------------------------------------------------------------------
// Call-Back-Funktion für die Initialisierung der Controls
void CEditCoordDlg::WindowInit (Event)
{
    // explizite Initialisierung der Controls
    m_X.FInit();
    m_Y.FInit();
	m_DeleteButton.FInit();
	m_DeleteText.FInit();

	// OwnerDraw-Knopf initialisieren
	if (m_DeleteButton.LoadBitmaps (ResID(IDB_DELE, pRF), ResID(IDB_DELE_SEL, pRF),
									ResID(IDB_DELE_FOCUS, pRF), ResID(IDB_DELE_DISABLED, pRF)))
		m_DeleteButton.SizeToContent(); 

    m_pED = (CEditDlg*) GetPropertySheet();

    // Zugriff auf editiertes Objekt, das in der Sheet gehalten wird
    m_wObj = m_pED->GetObject();

	m_lComONr = m_pED->GetComONr();

    ControlsSetting();
}


// --------------------------------------------------------------------------------------------
// Reaktion auf Eingabe des Anwenders in eines der Editierfelder (m_bIntern == false) oder
// durch Aufruf von SetText() (m_bIntern == true)
void CEditCoordDlg::EditChange (ControlEvt e)
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
    		// die Sheet-Button wieder in den ursprünglichen Zustand zurückversetzen
    		if (m_bContBt)	// ContinueButton war vor Aufruf der CoordPage aktiviert
    			m_pED->SetContinueButton();
    		if (m_bIslBt)	// IslandButton war vor Aufruf der CoordPage aktiviert
    			m_pED->SetIslandButton();
    		if (m_bOKBt)	// OKButton war vor Aufruf der CoordPage aktiviert
    			m_pED->SetOKButton();

    		PunktKorrigieren();
    		TestClosedLine();
    	}
    	else	// Anzahl der Vorkommastellen von m_X und/oder m_Y stimmt nicht
    	{
    		// die Sheet-Button deaktivieren
    		m_pED->SetContinueButton (false);
    		m_pED->SetIslandButton (false);
    		m_pED->SetOKButton (false);
    	}
    }
    else	// geodätische Datenbank
    	m_bGeodMod = true;

//  m_bCoordMod = true;	// Koordinaten wurden durch den Anwender verändert
    m_pED->SetCoordMod (true);	// Koordinaten wurden durch den Anwender verändert

} // EditChange


// --------------------------------------------------------------------------------------------
// Einstellung von Standardwerten
bool CEditCoordDlg::StandardWerte (int iCloseCnt, KoOrd* plCloseX, KoOrd* plCloseY, KoOrd x,
    							   KoOrd y)
{
    m_pVWnd = g_pTE->MVWind();	// TRiAS-ViewFenster

    m_pCT = new CoordTransX();	// KoordinatenTransformation
    if (NULL == m_pCT) return false;

    m_iCloseCnt = iCloseCnt;
    m_plCloseX = plCloseX;
    m_plCloseY = plCloseY;
    m_lX = x;
    m_lY = y;

// weitere Member initialisieren
    m_bGeodMod = false;	// in m_X bzw. m_Y wurden bei geodätischer Datenbank durch
    					// den Anwender noch keine Änderungen vorgenommen	
//  m_bCoordMod = false;// Koordinaten wurden noch nicht durch den Anwender verändert
    return true;

} // StandardWerte


// --------------------------------------------------------------------------------------------
// letzten Punkt des aktuell editierten Objektes aufgrund von Eingaben des Anwenders
// modifizieren
bool CEditCoordDlg::PunktKorrigieren (void)
{
EPunkt EP0, EP1, EP2;	// manuell editierte Stützpunkte
EPunkt NewPkt;			// neuer Punkt in DB-Koordinaten

    // DB-Koordinaten aus DoubleNumEdit rekonstruieren					
    NumEditToDBCoord (&m_X, &m_Y, NewPkt.X(), NewPkt.Y(), m_pCT);

    m_wObj->GetObjTyp (&m_iObjTyp);
    m_wObj->GetCnt (&m_lCnt);
    m_wObj->GetX ((void**)&m_plX);
    m_wObj->GetY ((void**)&m_plY);

    switch (m_iObjTyp)
    {
    	case OT_PUNKT:
    		break;
    		
    	case OT_KANTE:
    		// das Linienobjekt hat mindestens schon 2 Stützpunkte, so daß noch eine Linie auf
    		// dem Bildschirm korrigiert werden muß
    		if (m_lCnt >= 2)
    		{
    			EP1.X() = m_plX[m_lCnt-1];	// der letzte und
    			EP1.Y() = m_plY[m_lCnt-1];
    			EP2.X() = m_plX[m_lCnt-2];	//  der vorletzte manuell editierte Stützpunkt
    			EP2.Y() = m_plY[m_lCnt-2];
    			DrawLine (EP2, EP1, false, m_pVWnd);	// Linie auf Bildschirm löschen
    			DrawLine (EP2, NewPkt, false, m_pVWnd);	// Linie neu zeichnen
    		}
    		break;
    
    	case OT_FLAECHE:
    	{
    		m_wObj->GetKCnt (&m_iKCnt);
    		m_wObj->GetLPCnt (&m_plCnt);

    	long lSPA = m_plCnt[m_iKCnt-1];

    		// die letzte Kontur des Flächenobjektes hat mindestens schon 2 Stützpunkte, so daß
    		// noch 1 - 2 Linien auf dem Bildschirm korrigiert werden müssen
    		if (lSPA >= 2)
    		{
    			EP1.X() = m_plX[m_lCnt-1];	// der letzte und
    			EP1.Y() = m_plY[m_lCnt-1];
    			EP2.X() = m_plX[m_lCnt-2];	//  der vorletzte manuell editierte Stützpunkt
    			EP2.Y() = m_plY[m_lCnt-2];
    			DrawLine (EP2, EP1, false, m_pVWnd);	// Linie auf Bildschirm löschen
    			DrawLine (EP2, NewPkt, false, m_pVWnd);	// Linie neu zeichnen

    			if (lSPA >= 3)
    			{
    			long lInd = m_lCnt - lSPA;	// Index des Anfangspunktes der letzten Kontur

    				EP0.X() = m_plX[lInd];	//  der erste Stützpunkt besagter Kontur
    				EP0.Y() = m_plY[lInd];
    				DrawLine (EP0, EP1, false, m_pVWnd);	// Linie auf Bildschirm löschen
    				DrawLine (EP0, NewPkt, false, m_pVWnd);	// Linie neu zeichnen
    			}
    		}

    		break;
    	}

    	default:
    		_ASSERTE (false);
    		return false;
    }

    // Der Befehl m_wObj->ModPunkt (NewPkt.X(), NewPkt.Y(), m_lCnt-1) kann nicht verwendet
    // werden, da NewPkt als Teil des Konturschlosses interpretiert wird, das noch gar nicht
    // existiert, da m_wObj noch nicht geschlossen ist.
    m_plX[m_lCnt-1] = NewPkt.X();	// Punktkoordinaten modifizieren
    m_plY[m_lCnt-1] = NewPkt.Y();

    return true;

} // PunktKorrigieren


// --------------------------------------------------------------------------------------------
// die beiden Koordinaten-Eingabe-Felder belegen
bool CEditCoordDlg::ControlsSetting (void)
{
    m_bIntern = true;	// programm-interne Modifikation der Editierfelder m_X bzw. m_Y

   	m_wObj->GetCnt (&m_lCnt);
   	m_wObj->GetObjTyp (&m_iObjTyp);

    if (m_lX < 0 || m_lY < 0)
    {
    KoOrd* m_plX; KoOrd* m_plY;	//  Feld der x- bzw. y-Koordinaten des editierten Objektes

    	m_wObj->GetX ((void**)&m_plX);
    	m_wObj->GetY ((void**)&m_plY);

    	m_lX = m_plX[m_lCnt-1];
    	m_lY = m_plY[m_lCnt-1];
    }

    DBCoordToNumEdit (m_lX, m_lY, &m_X, &m_Y, m_pCT);
    m_bIntern = false;
    // Anzahl der Vorkomma-Stellen von m_X und m_Y ermitteln
    DigitNumerator (m_XLen, m_YLen, &m_X, &m_Y, m_pCT);

    m_X.SetFocus();	// 1. Eingabestelle soll bei x-Koordinate sein

    // DeleteButton nur bei Linien- und Flächenobjekt freigeben, wenn wenigstens 2 Punkte
	// editiert wurden; Punktobjekt bzw. erster Punkt eines Linien- oder Flächenobjektes mit
    // CancelButton eliminieren
//  if (OT_PUNKT == m_iObjTyp || 1 == m_lCnt)
	if (1 == m_lCnt)
	{
    	m_DeleteButton.Disable();
    	m_DeleteText.Disable();
	}
    else
	{
    	m_DeleteButton.Enable();
    	m_DeleteText.Enable();
	}

    if (OT_PUNKT == m_iObjTyp)
	{
    	m_DeleteButton.Hide();
    	m_DeleteText.Hide();
	}

    return true;

} // ControlsSetting


// --------------------------------------------------------------------------------------------
// ein Button dieser Page wurde gedrückt
void CEditCoordDlg::ButtonClick (ControlEvt e)
{
    m_wObj->GetCnt (&m_lCnt);		// Parameter von m_wObj für die ActionRoutinen der Button
    m_wObj->GetX ((void**)&m_plX);	//  bereitstellen
    m_wObj->GetY ((void**)&m_plY);

    if (OT_FLAECHE == m_iObjTyp)
    {
    	m_wObj->GetKCnt (&m_iKCnt);
    	m_wObj->GetLPCnt (&m_plCnt);
    }

    switch ((uint) e.GetControlID())
    {
    	case IDB_DELETE:		// Löschen des zuletzt editierten Stützpunktes
    		DeleteButtonAction();
    		break;

    	default:
    		_ASSERTE (false);
    		break;
    }
} // ButtonClick


// --------------------------------------------------------------------------------------------
// wird gerufen, wenn OK-, Übernehmen- oder CloseButton gedrückt wurden
 BOOL CEditCoordDlg::OnOK (NotifyEvt)
{
    if (m_bGeodMod)	// m_X bzw. m_Y wurden bei geodätischer Datenbank durch Anwender verändert
    {
    	PunktKorrigieren();
    	TestClosedLine();
    	m_bGeodMod = false;	// doppelte Korrektur muß nicht sein
    }

    return false;

} // OnOK


// --------------------------------------------------------------------------------------------
// wird gerufen, wenn diese Page aktiviert werden soll
BOOL CEditCoordDlg::OnSetActive (NotifyEvt)
{
    if (m_pED->IsContinueEnable())	// Zustand des ContinueButton retten
    	m_bContBt = true;
    else
    	m_bContBt = false;

    if (m_pED->IsIslandEnable())	// Zustand des IsIslandButton retten
    	m_bIslBt = true;
    else
    	m_bIslBt = false;

    if (m_pED->IsOKEnable())		// Zustand des OKButton retten
    	m_bOKBt = true;
    else
    	m_bOKBt = false;

    return FALSE;	// bei Gültigkeit "FALSE" sonst "TRUE" (???)

} // OnSetActive


// --------------------------------------------------------------------------------------------
// wird gerufen, wenn die diese Page deaktiviert werden soll; deshalb wird hier die Gültigkeit
// der Daten dieser Page überprüft (bei Gültigkeit "return FALSE" sonst "return TRUE")
BOOL CEditCoordDlg::OnKillActive (NotifyEvt)
{
    if (m_bGeodMod)	// m_X bzw. m_Y wurden bei geodätischer Datenbank durch Anwender verändert
    {
    	PunktKorrigieren();
    	TestClosedLine();
    	m_bGeodMod = false;	// doppelte Korrektur muß nicht sein
    }

    // ich gehe davon aus, daß bei einer Korrektur der Koordinaten durch den Anwender nicht
    // haarscharf eine vorhandene Koordinate getroffen werden kann und soll (denn wäre dies
    // gewollt, dann wäre normales Grabben das Gebot der Stunde gewesen); deshalb jetzt den
    // ComBorderButton deaktivieren
//  m_pED->SetCoordMod (m_bCoordMod);

    return FALSE;

} // OnKillActive


// --------------------------------------------------------------------------------------------
// Zeichenroutinen
// Element vollständig malen
BOOL CEditCoordDlg::DrawEntireItem (DrawItemEvt e)
{
	return m_DeleteButton.DrawItem(e);
}


// --------------------------------------------------------------------------------------------
// Element mit Focus zeichnen
BOOL CEditCoordDlg::DrawItemFocus (DrawItemEvt e)
{
	return m_DeleteButton.DrawItem(e);
}


// --------------------------------------------------------------------------------------------
// Element ausgewählt zeichnen
BOOL CEditCoordDlg::DrawItemSelect (DrawItemEvt e)
{
	return m_DeleteButton.DrawItem(e);
}


// --------------------------------------------------------------------------------------------
// Reaktion bei Betätigung des DeleteButton
// Löschen des zuletzt editierten Stützpunktes (kann mehrfach hintereinander ausgeführt
// werden);
// bei einem Punktobjekt bzw. wenn bei einem Linien- bzw. Flächenobjekt nur (noch) ein
// Stützpunkt vorhanden ist, wird der DeleteButton deaktiviert; soll auch dieser Stützpunkt
// gelöscht werden, ist der CancelButton zu verwenden, der gleichzeitig das gesamte Objekt
// löscht
void CEditCoordDlg::DeleteButtonAction (void)
{
EPunkt EP0, EP1, EP2;	// manuell editierte Stützpunkte

    switch (m_iObjTyp)
    {
    short iKontInd;		// Parameter für SubPunkt(); wird hier nicht ausgewertet

    	case OT_PUNKT:

    		_ASSERTE (m_iObjTyp != OT_PUNKT);

    		return;		// dieser Zweig dürfte eigentlich gar nicht erreicht werden
    		
    	case OT_KANTE:
    		if (m_lCnt <= 1)
    		{
    			_ASSERTE (m_lCnt > 1);

    			return;	// dieser Zweig dürfte eigentlich gar nicht erreicht werden
    		}
    			
    		// die letzte Strecke wird auf dem Bildschirm gelöscht
    		EP1.X() = m_plX[m_lCnt-1];	// der letzte und
    		EP1.Y() = m_plY[m_lCnt-1];
    		EP2.X() = m_plX[m_lCnt-2];	//  der vorletzte manuell editierte Stützpunkt
    		EP2.Y() = m_plY[m_lCnt-2];
    		m_wObj->SubPunkt (m_lCnt-1, &iKontInd);

    		if (m_lCnt >= 2)		// Strecke zwischen EP2 und EP1 auf Bildschirm löschen
    			DrawLine (EP2, EP1, false, m_pVWnd);
    		
    		break;

    		
    	case OT_FLAECHE:
    	{
    	long lSPA = m_plCnt[m_iKCnt-1];	// Anzahl der Stützpunkte der letzten Kontur
    	
    		if (m_lCnt <= 1 || 0 == lSPA)
    		{
    			_ASSERTE (m_lCnt > 1 && lSPA > 0);

    			return;	// dieser Zweig dürfte eigentlich gar nicht erreicht werden
    		}

    	int iCCl = 0;	// Kontur, deren letzter Stützpunkt gelöscht werden soll,
    					// ist nicht geschlossen
    	long lInd = m_lCnt - lSPA;	// Index des Anfangspunktes der letzten Kontur

    		if ((m_plX[lInd] == m_plX[m_lCnt-1] &&	// 1. und letzter Stützpunkt der
    			m_plY[lInd] == m_plY[m_lCnt-1]) &&	// Kontur sind identisch
    			lSPA > 1)							// es gibt mehr als einen Stützpunkt
    			iCCl = 1;	// Kontur ist damit "ordentlich" geschlossen

    		if (lSPA >= 2)
    		{
    			EP1.X() = m_plX[m_lCnt-1-iCCl];
    			EP1.Y() = m_plY[m_lCnt-1-iCCl];
    			EP2.X() = m_plX[m_lCnt-2-iCCl];
    			EP2.Y() = m_plY[m_lCnt-2-iCCl];
    			DrawLine (EP2, EP1, false, m_pVWnd);		// 1. Linie auf Bildschirm löschen

    			if (lSPA >= 3)
    			{
    				EP0.X() = m_plX[lInd];
    				EP0.Y() = m_plY[lInd];
    				DrawLine (EP1, EP0, false, m_pVWnd);	// 2. Linie auf Bildschirm löschen

    				if (lSPA >= 4 + iCCl)					// neue Linie auf Bildschirm zeichnen
    					DrawLine (EP2, EP0, false, m_pVWnd);
    			}
    		}

    		if (1 == iCCl)
    			m_wObj->SubPunkt (2, m_lCnt-2, false, &iKontInd);	// 2 Punkte löschen
    		else
	 			m_wObj->SubPunkt (m_lCnt-1, false, &iKontInd);		// 1 Punkt löschen
    	}
    		break;

    	default:
    		_ASSERTE (false);
    		break;
    }

	// Anzeige der Koordinaten des jetzt letzten Punktes EP2
    m_bIntern = true;	// programm-interne Modifikation der Editierfelder m_X bzw. m_Y
    DBCoordToNumEdit (EP2.X(), EP2.Y(), &m_X, &m_Y, m_pCT);
    m_bIntern = false;

// Korrektur für CommonBorder
int iGrabCnt = m_pED->GetGrabCnt();

	if (0 != m_lComONr && -1 != m_lComONr && iGrabCnt > 0)
	{
    	iGrabCnt--;
    	m_pED->SetGrabCnt (iGrabCnt);
	}

    ButtonSettingAfterDelete();	// Button neu (de)aktivieren

} // DeleteButtonAction


// --------------------------------------------------------------------------------------------
// Button nach Löschen neu aktivieren/deaktivieren
void CEditCoordDlg::ButtonSettingAfterDelete (void)
{
    // Parameter von m_wObj aktualisieren (können durch das Löschen verändert worden sein)
    m_wObj->GetCnt (&m_lCnt);
    if (OT_FLAECHE == m_iObjTyp)
    {
    	m_wObj->GetKCnt (&m_iKCnt);
    	m_wObj->GetLPCnt (&m_plCnt);
    }

    // DeleteButton nur bei Linien- und Flächeobjekt freigeben, wenn immer noch wenigstens
	// 2 Punkte editiert sind; Punktobjekt, ersten Punkt eines Linienobjektes bzw. ersten Punkt
    // der Außenkontur eines Flächenobjektes mit CancelButton eliminieren
    if (OT_PUNKT == m_iObjTyp || 1 == m_lCnt)
	{
    	m_DeleteButton.Disable();
    	m_DeleteText.Disable();
	}
    else
	{
    	m_DeleteButton.Enable();
    	m_DeleteText.Enable();
	}
/*
    // nach dem Löschen ist der CloseButton möglicherweise wieder sinnvoll oder eben gerade
    // nicht
    if (OT_KANTE == m_iObjTyp &&
    	((0 == m_iCloseCnt && m_lCnt >= 3) ||	// Neueditierung oder
    	1 == m_iCloseCnt))						// Linienverlängerung für eine einzige Linie
	{
    	m_CloseButton.Enable();
    	m_CloseText.Enable();
	}
    else
	{
    	m_CloseButton.Disable();
    	m_CloseText.Disable();
	}
*/
    m_pED->SetClosedLine (false);
/*
    // der CircleButton kann wieder sinnvoll werden
    if ((OT_KANTE == m_iObjTyp && m_lCnt >= 3) ||
    	(OT_FLAECHE == m_iObjTyp && m_plCnt[m_iKCnt-1] >= 3))
	{
    	m_CircleButton.Enable();
    	m_CircleText.Enable();
	}
    else
	{
    	m_CircleButton.Disable();
    	m_CircleText.Disable();
	}

    // es sind Fälle denkbar, wo nach dem Löschen der ComBorderButton noch zulässig ist; dann
    // wäre aber dieser soeben gelöschte letzte GrabPunkt redundant gewesen; da der Test
    // hierfür ziemlich aufwendig ist und dieser Redundanzfall wohl kaum mehr als einmal in 100
    // Jahren auftritt, spare ich mir diesen Test erst einmal
    m_ComBorderButton.Disable();
    m_ComBorderText.Disable();
*/
	m_pED->SetDelBttn (true);

    // Button der Sheet akualisieren
    if (m_pED->IsContinueEnable())		// ContinueButton
    	m_pED->SetContinueButton();
    else
    	m_pED->SetContinueButton (false);
    if (m_pED->IsIslandEnable())		// IslandButton
    	m_pED->SetIslandButton();
    else
    	m_pED->SetIslandButton (false);
    if (m_pED->IsOKEnable())			// OKButton
    	m_pED->SetOKButton();
    else
    	m_pED->SetOKButton (false);

} // ButtonSettingAfterDelete


// --------------------------------------------------------------------------------------------
// Test, ob ein editiertes Linienobjekt durch manuelle Korrektur der Koordinaten jetzt
// geschlossen ist; wenn ja, dann bClosedLine = true, was zur Folge hat, daß ContinueButton
// deaktiviert wird
void CEditCoordDlg::TestClosedLine (void)
{
    m_wObj->GetObjTyp (&m_iObjTyp);

    if (OT_KANTE != m_iObjTyp)
    	return;

    m_wObj->GetCnt (&m_lCnt);
    m_wObj->GetX ((void**)&m_plX);
    m_wObj->GetY ((void**)&m_plY);

bool bClosedLine = false;

    if (0 == m_iCloseCnt)	// echte Neueditierung
    {
    	if (m_lCnt > 1 && m_plX[0] == m_plX[m_lCnt-1] && m_plY[0] == m_plY[m_lCnt-1])
    		bClosedLine = true;
    }
    else					// Linienverlängerung
    {
    	for (int i = 0; i < m_iCloseCnt; i++)
    		if (m_plX[m_lCnt-1] == m_plCloseX[i] && m_plY[m_lCnt-1] == m_plCloseX[i])
    		{
    			bClosedLine = true;
    			break;
    		}
    }

    m_pED->SetClosedLine (bClosedLine);
    if (bClosedLine)
    	m_pED->SetContinueButton (false);
    else
    	m_pED->SetContinueButton();

} // TestClosedLine
