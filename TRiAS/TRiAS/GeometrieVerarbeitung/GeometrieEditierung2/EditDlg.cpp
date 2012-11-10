// PropertySheet für EditierDialog
// File: EditDlg.cpp
// W. Mörtl


#include "GeoEditP.h"

#include "EditDlg.h"
#include "EditBaseDlg.h"	// CEditBaseDlg



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
// der optionale Parameter PSH_HASHELP positioniert konkret den HelpButton, um seine Position
// für den CancelButton nutzen zu können
CEditDlg::CEditDlg (LPCSTR pszCaption, IObjektGeometrie* pIOG, long lComONr, int* piGrabCnt)
		: CEditObjectSheet (pszCaption, g_pTE->MVWind(), PSH_HASHELP),
		  m_OK (this, IDOK),
		  m_Cancel (this, IDCANCEL),
		  m_Apply (this, IDB_APPLY),
		  m_Help (this, IDHELP)
{
	_ASSERTE (pIOG != NULL);

	try
	{
		m_wObj = pIOG;
	}
	catch (...)
	{
		_ASSERTE (false);
		return;
	}
	m_pIslandButton = NULL;
	m_pContinueButton = NULL;

	m_wObj->GetObjTyp (&m_iObjTyp);
	m_wObj->GetCnt (&m_lCnt);
	if (OT_FLAECHE == m_iObjTyp)
	{
		m_wObj->GetKCnt (&m_iKCnt);
		m_wObj->GetLPCnt (&m_plCnt);
	}

	m_bClosedLine = false;
	m_bCoordMod = false;		// Koordinaten wurden noch nicht durch den Anwender in der
								// CEditCoordDlg-Page verändert
	m_lComONr = lComONr;
	if (piGrabCnt)
	{
	    _ASSERTE (*piGrabCnt <= 3);

    	m_iGrabCnt = *piGrabCnt;
	}
    else
    	m_iGrabCnt = 0;

	m_bDelBttn = false;			// DeleteButton wurde noch nicht betätigt
}
#if defined (MSCC8)
#pragma warning (default: 4355)
#endif


// --------------------------------------------------------------------------------------------
CEditDlg::~CEditDlg (void)
{
	m_pIslandButton->ChangeFont (NULL);

pFont pMyFont = m_pContinueButton->ChangeFont (NULL);

	DELETE_OBJ (pMyFont);
	DELETE_OBJ (m_pIslandButton);
	DELETE_OBJ (m_pContinueButton);
}


// --------------------------------------------------------------------------------------------
// Initialisierung der Sheet (Call-Back-Funktion)
void CEditDlg::WindowInit (Event)
{
	m_OK.FInit();
	m_Cancel.FInit();
	m_Apply.FInit();
	m_Help.FInit();

// Text des OKButton in "Speichern" ändern
ResString resBtnText (ResID (IDS_SPEICHERN, pRF), 30);

	m_OK.SetText (resBtnText.Addr());

// 2 Button (Inselbeginn, Fortsetzen) ergänzen und 2 Button (OK, Abbrechen) verschieben
Point OPos = m_OK.GetPosition();		// alte Position des OKButtons
Point CPos = m_Cancel.GetPosition();
Point APos = m_Apply.GetPosition();
Point HPos = m_Help.GetPosition();

// die Button noch leicht nach links verschieben, da links von linkesten Button noch der gleiche
// freie Platz reserviert ist, wie zwischen je 2 der anderen Button
Dimension dimBtnSize = m_OK.GetSize();	// Größe der Standard-Button (von OKButton abgeleitet)
CoOrd LShift = CPos.X() - OPos.X() - dimBtnSize.Width();

	OPos.X() -= LShift/2;
	CPos.X() -= LShift/2;
	APos.X() -= LShift/2;
	HPos.X() -= LShift/2;
	m_Apply.ChangePosition (APos);
	m_Help.ChangePosition (HPos);

	m_Apply.Hide();		// Apply- und
	m_Help.Hide();		// HelpButton verstecken
	m_Apply.Disable();	// Apply- und
	m_Help.Disable();	// HelpButton deaktivieren

	m_OK.ChangePosition (APos);
	m_Cancel.ChangePosition (HPos);

ResString resCButton (ResID (IDS_CONTBUTTON, pRF), 30);
ResString resIButton (ResID (IDS_ISLBUTTON, pRF), 30);

	m_pIslandButton = new PushButton (this, IDB_ISLAND, OPos, dimBtnSize, resIButton.Addr());
	m_pContinueButton = new PushButton (this, IDB_CONTINUE, CPos, dimBtnSize, resCButton.Addr());

	if (!m_pIslandButton || !m_pContinueButton)
	{
		DEX_Error (RC_EditDlg, EC_NOMEMORY);
		return;
	}

	m_hF = (HFONT)SendMessage(m_OK.Handle(), WM_GETFONT, 0, 0);	// Windows-Font des OKButtons

#if !defined(_TRIAS_OLDIMPLEMENTATION2)
	pFont pStdFont = new CVFont (m_hF);
#else
	pFont pStdFont = new Font (m_hF);
#endif // !defined(_TRIAS_OLDIMPLEMENTATION2)

	m_pIslandButton->ChangeFont (pStdFont);
	m_pContinueButton->ChangeFont (pStdFont);

	if (! IsIslandEnable()) m_pIslandButton->Disable();
	if (! IsContinueEnable()) m_pContinueButton->Disable();
	if (! IsOKEnable()) m_OK.Disable();

	if (OT_FLAECHE == m_iObjTyp)
		m_pIslandButton->Show();

	if (OT_PUNKT != m_iObjTyp)
		m_pContinueButton->Show();

// Position dieses Dialoges bestimmen
Point Pt = DialogPosition (m_wObj, GetSize());

//	_ASSERTE (Pt.X() >= 0);	// durch die Änderung in DialogPosition()
//	_ASSERTE (Pt.Y() >= 0);

	ChangePosition (Pt);	// Dialog positionieren

} // WindowInit


// --------------------------------------------------------------------------------------------
// ein Button der Sheet wurde gedrückt
void CEditDlg::ButtonClick (ControlEvt e)
{
	switch ((uint) e.GetControlID())
	{
		case IDB_CONTINUE:
			PropSheet_PressButton (Handle(), PSBTN_OK);	// so als wäre der OKButton gedrückt
			break;

		case IDB_ISLAND:
			IslandButtonAction();
			PropSheet_PressButton (Handle(), PSBTN_OK);	// so als wäre der OKButton gedrückt
			break;

		case IDOK:
			AreaClose();
			PropSheet_PressButton (Handle(), PSBTN_OK);
			break;

		case IDCANCEL:
			PropSheet_PressButton (Handle(), PSBTN_CANCEL);
			break;
	}
} // ButtonClick


// ------------------------------------------------------------------------------------------------
// Test, ob bei Betätigung des ContinueButtons die entsprechende Aktion ausgeführt werden darf;
// wenn ja, dann Rückgabe von true, sonst false
bool CEditDlg::IsContinueEnable (void)
{
	// In den folgenden Fällen muß der ContinueButton deaktiviert werden
	// 1. Fall: es wird ein Punktobjekt editiert
	if (OT_PUNKT == m_iObjTyp)
		return false;


	// 2. Fall: Linien- oder Flächenobjekt ist zugezogen
	// 3. Fall: erster Punkt einer Innenkontur (und damit gesamte Innenkontur) wurde gelöscht
	// 4. Fall: es wurde ein Vollkreis gebildet
	// 5. Fall: im Anschluß an den 3. Fall wurde ein Kreisbogen gebildet
	// diese Fälle lassen sich gemeinsam abtesten
	// Deshalb davor noch eine mögliche Koordinatenkorrektur durch den Anwender
	// berücksichtigen.
bool bRet = true;	// return-Wert dieser Routine

	if (OT_KANTE == m_iObjTyp)
	{
		if (m_bClosedLine)	// das neueditierte oder eines der zu verlängernden Linienobjekte
							// ist geschlossen
			bRet = false;
	}

	else if (OT_FLAECHE == m_iObjTyp)
	{
		// da der DeleteButton (mehrmals) gedrückt worden sein konnte, sind nachfolgend erst
		// die m_wObj-Parameter zu aktualisieren
		m_wObj->GetCnt (&m_lCnt);
		m_wObj->GetKCnt (&m_iKCnt);
		m_wObj->GetLPCnt (&m_plCnt);

		if (m_plCnt[m_iKCnt-1] > 1)
		{
		KoOrd* plXK; KoOrd* plYK;	//  Felder der x- bzw. y-Koordinaten

			m_wObj->GetX ((void**)&plXK);
			m_wObj->GetY ((void**)&plYK);

		long lAInd = m_lCnt - m_plCnt[m_iKCnt-1];	// Index des Anfangspunktes der letzten
													//  Kontur
			if (plXK[lAInd] == plXK[m_lCnt-1] && plYK[lAInd] == plYK[m_lCnt-1])
				bRet = false;
		}
	}
	else
	{
		_ASSERTE (false);
		bRet = false;
	}

	return bRet;

} // IsContinueEnable


// --------------------------------------------------------------------------------------------
// Test, ob bei Betätigung des IslandButtons die entsprechende Aktion ausgeführt werden darf;
// wenn ja, dann Rückgabe von true, sonst false
bool CEditDlg::IsIslandEnable (void)
{
	// In den folgenden Fällen muß der IslandButton deaktiviert werden
	// 1. Fall: es wird ein Punkt- oder Linienobjekt editiert
	if (OT_PUNKT == m_iObjTyp || OT_KANTE == m_iObjTyp)
		return false;

	// 2. Fall: die letzte Kontur hat noch weniger als 3 Stützpunkte
	// da der DeleteButton (mehrmals) gedrückt worden sein konnte, sind nachfolgend erst
	// die m_wObj-Parameter zu aktualisieren
	m_wObj->GetKCnt (&m_iKCnt);
	m_wObj->GetLPCnt (&m_plCnt);

	if (m_plCnt[m_iKCnt-1] < 3)
		return false;

	return true;
} // IsIslandEnable


// --------------------------------------------------------------------------------------------
// Test, ob bei Betätigung des OKButtons die entsprechende Aktion ausgeführt werden darf;
// wenn ja, dann Rückgabe von true, sonst false
bool CEditDlg::IsOKEnable (void)
{
	// In den folgenden Fällen muß der OKButton deaktiviert werden
	// 1. Fall: für ein Linienobjekt wurde bisher nur 1 Punkt editiert
	// 2. Fall: für die Kontur eines Flächenobjektes wurden bisher höchstens 2 Punkte editiert
	if (OT_KANTE == m_iObjTyp)
	{
		// da der DeleteButton (mehrmals) gedrückt worden sein konnte, sind nachfolgend erst
		// die m_wObj-Parameter zu aktualisieren
		m_wObj->GetCnt (&m_lCnt);

		if (m_lCnt < 2)
			return false;
	}
	else if (OT_FLAECHE == m_iObjTyp)
	{
		m_wObj->GetKCnt (&m_iKCnt);
		m_wObj->GetLPCnt (&m_plCnt);

		if (m_plCnt[m_iKCnt-1] < 3)
			return false;
	}

	return true;

} // IsOKEnable


// --------------------------------------------------------------------------------------------
// Reaktion bei Betätigung des IslandButton
void CEditDlg::IslandButtonAction (void)
{
	AreaClose();

} // IslandButtonAction


// --------------------------------------------------------------------------------------------
// Flächenobjekt bzgl. der Koordinaten zuziehen, wenn noch offen
bool CEditDlg::AreaClose (void)
{
	if (m_iObjTyp != OT_FLAECHE) return true;

// wegen möglicherweise vorherigem Löschen aktualisieren
KoOrd* plXK; KoOrd* plYK;

	m_wObj->GetX ((void**)&plXK);
	m_wObj->GetY ((void**)&plYK);
	m_wObj->GetCnt (&m_lCnt);
	m_wObj->GetKCnt (&m_iKCnt);
	m_wObj->GetLPCnt (&m_plCnt);

long lSPA = m_plCnt[m_iKCnt-1];	// Anzahl der Stützpunkte der letzten Kontur
long lInd = m_lCnt - lSPA;		// Index des Anfangspunktes der letzten Kontur
	
	if (lSPA <= 2)	// dieser Zweig dürfte eigentlich gar nicht erreicht werden
	{
		_ASSERTE (lSPA > 2);

		return false;
	}
		
	if (plXK[lInd] == plXK[m_lCnt-1] &&	// Kontur ist (z.B. durch Bildung eines
		plYK[lInd] == plYK[m_lCnt-1])	//  Vollkreises) schon zugezogen
		return true;
		
	m_wObj->AddPunkt (plXK[lInd], plYK[lInd], -1, m_iKCnt-1);	// zuziehen

	return true;

} // AreaClose
