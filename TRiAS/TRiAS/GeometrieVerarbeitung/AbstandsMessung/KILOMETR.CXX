// Kilometrierung
// File: KILOMETR.CXX
// W. Mörtl


#include "abstandp.hxx"

#include "datbank.hxx"		// IdentErmitteln()
#include "kilometr.hxx"


#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


extern ResourceFile* pRF;
const UINT WM_DEFINENEWITEM = RegisterWindowMessage("WM_DEFINENEWITEM");

///////////////////////////////////////////////////////////////////////////////////////////////
// Konstruktor
#if defined (MSCC8)
#pragma warning (disable: 4355)	// Ausschalten von uninteressanten Warnungen
#endif
KilometrDlg :: KilometrDlg (pWindow pW, ResID res, IdentList& IL, KoOrd lXA, KoOrd lYA,
							KoOrd lXE, KoOrd lYE)
			 : DialogWindow (pW, res),
			   m_RechtswertA (this, IDE_XKOORDA),
			   m_HochwertA (this, IDE_YKOORDA),
			   m_RechtswertE (this, IDE_XKOORDE),
			   m_HochwertE (this, IDE_YKOORDE),
//			   m_Tausch (this, IDB_TAUSCH),
			   m_Distanz (this, IDE_DISTANZ),
			   m_TextStartWert (this, IDE_TEXTSTARTWERT),
			   m_KilometrText (this, IDC_KILOMETRTEXT),
			   m_Teilabschnitte (this, IDC_TEILABSCHNITTE),
			   m_IdentListe (this, IDL_OBJKLASSE),
			   m_OK (this, IDOK),
			   m_IL (IL)
{
	m_pW = pW;
	StandardWerte (lXA, lYA, lXE, lYE);
}
#if defined (MSCC8)
#pragma warning (default: 4355)
#endif



// --------------------------------------------------------------------------------------------
// Destruktor
KilometrDlg :: ~KilometrDlg (void)
{
	DELETE_OBJ (m_pCT);
}



///////////////////////////////////////////////////////////////////////////////////////////////
// Überprüfung der Eingabe
void _ABSTAND_EXPORT KilometrDlg :: EditChange (ControlEvt e)
{
	m_OK.Disable();

double dDist;

	NumEditToDouble (&m_Distanz, dDist);

char pcBufferXA [40] = { '\0' };		// Konvertierungspuffer für x-
char pcBufferYA [40] = { '\0' };		//  bzw. y-Koordinaten
char pcBufferXE [40] = { '\0' };
char pcBufferYE [40] = { '\0' };

	m_RechtswertA.GetText (pcBufferXA, sizeof (pcBufferXA));
	m_HochwertA.GetText (pcBufferYA, sizeof (pcBufferYA));
	m_RechtswertE.GetText (pcBufferXE, sizeof (pcBufferXE));
	m_HochwertE.GetText (pcBufferYE, sizeof (pcBufferYE));

	if (dDist > 0 &&
		strlen (pcBufferXA) > 0 && strlen (pcBufferYA) > 0 &&
		strlen (pcBufferXE) > 0 && strlen (pcBufferYE) > 0 &&
		m_IdentListe.GetCurrentIndex() >= 0)
	{
		m_OK.Enable();		// OK-Button nur bei sinnvollen Eingaben freigeben
	}

} // EditChange


// --------------------------------------------------------------------------------------------
// Reaktion auf Button-Click
void _ABSTAND_EXPORT KilometrDlg :: ButtonClick (ControlEvt e)
{
	switch ((uint)e.GetControlID())
	{
		// Koordinaten von Anfangs- und Endpunkt austauschen
		case IDB_TAUSCH:
		{
		// Anfangspunkt einlesen
		char pcBufferXA [40] = { '\0' };		// Konvertierungspuffer für x-
		char pcBufferYA [40] = { '\0' };		//  bzw. y-Koordinaten

			m_RechtswertA.GetText (pcBufferXA, sizeof (pcBufferXA));
			m_HochwertA.GetText (pcBufferYA, sizeof (pcBufferYA));

		// Endpunkt einlesen
		char pcBufferXE [40] = { '\0' };		// Konvertierungspuffer für x-
		char pcBufferYE [40] = { '\0' };		//  bzw. y-Koordinaten

			m_RechtswertE.GetText (pcBufferXE, sizeof (pcBufferXE));
			m_HochwertE.GetText (pcBufferYE, sizeof (pcBufferYE));

		// bisherigen Anfangspunkt als neuen Endpunkt wegschreiben
			m_RechtswertA.SetText (pcBufferXE);
			m_HochwertA.SetText (pcBufferYE);

		// bisherigen Endpunkt als neuen Anfangspunkt wegschreiben
			m_RechtswertE.SetText (pcBufferXA);
			m_HochwertE.SetText (pcBufferYA);

		double dZw = m_XAR;		// 08.06.99

			m_XAR = m_XER;
			m_XER = dZw;
			dZw = m_YAR;
			m_YAR = m_YER;
			m_YER = dZw;

		KoOrd lZw = m_XADB;

			m_XADB = m_XEDB;
			m_XEDB = lZw;
			lZw = m_YADB;
			m_YADB = m_YEDB;
			m_YEDB = lZw;

			break;
		}


		case IDOK:
		{
		char pcBufferX [40] = { '\0' };		// Konvertierungspuffer für x-
		char pcBufferY [40] = { '\0' };		//  bzw. y-Koordinaten

			// nur Rückrechnung aus den Editierfenstern, wenn dort auch editiert wurde (06.05.99)
			if (m_RechtswertA.isModified() || m_HochwertA.isModified())
			{
				m_RechtswertA.GetText (pcBufferX, sizeof (pcBufferX));
				m_HochwertA.GetText (pcBufferY, sizeof (pcBufferY));
				if (m_pCT->CoordTransToValueEx (pcBufferX, pcBufferY, m_XAR, m_YAR) == false)
					return;
				m_RechtswertA.SetModified (false);
				m_HochwertA.SetModified (false);
			}

			RealInDBKoord (m_XAR, m_YAR, m_XADB, m_YADB, m_pCT);

			if (m_RechtswertE.isModified() || m_HochwertE.isModified())
			{
				m_RechtswertE.GetText (pcBufferX, sizeof (pcBufferX));
				m_HochwertE.GetText (pcBufferY, sizeof (pcBufferY));
				if (m_pCT->CoordTransToValueEx (pcBufferX, pcBufferY, m_XER, m_YER) == false)
					return;
				m_RechtswertE.SetModified (false);
				m_HochwertE.SetModified (false);
			}

			RealInDBKoord (m_XER, m_YER, m_XEDB, m_YEDB, m_pCT);

			NumEditToDouble (&m_Distanz, m_dDistanz);
			NumEditToDouble (&m_TextStartWert, m_dTextStartWert);

			m_bText = false;
			if (m_KilometrText.isChecked()) m_bText = true;

			m_bTeil = false;
			if (m_Teilabschnitte.isChecked()) m_bTeil = true;

			EndDlg (1);
			break;
		}

		
		case IDCANCEL:
			EndDlg (0);
			break;

		
		case IDC_KILOMETRTEXT:
			if (m_KilometrText.isChecked()) m_TextStartWert.Enable();
			else m_TextStartWert.Disable();
			break;
	}
} // ButtonClick


//---------------------------------------------------------------------------------------------
// Reaktion auf einfachen Klick in die ComboBox und danach auf OK-Button
void _ABSTAND_EXPORT KilometrDlg :: ListBoxSel (ControlEvt e)
{
	switch ((uint) e.GetControlID()) {
	case IDL_OBJKLASSE:
		m_ulIdent = IdentErmitteln (&m_IdentListe);
		if (INVALID_HOBJECTS == m_ulIdent) 
			PostEvent(WM_DEFINENEWITEM); 
		break;

	default:
		_ASSERTE (false);
		break;
	}
} // ListBoxSel


// --------------------------------------------------------------------------------------------
// Einstellen der Standardwerte
void KilometrDlg :: StandardWerte (KoOrd lXA, KoOrd lYA, KoOrd lXE, KoOrd lYE)
{
	// NumEditX initialiseren
	m_RechtswertA.SetNumEditMode (NumEditX :: NEM_NoTest);
	m_HochwertA.SetNumEditMode (NumEditX :: NEM_NoTest);
	m_RechtswertE.SetNumEditMode (NumEditX :: NEM_NoTest);
	m_HochwertE.SetNumEditMode (NumEditX :: NEM_NoTest);
	m_Distanz.SetNumEditMode (NumEditX :: NEM_NoTest);
	m_TextStartWert.SetNumEditMode (NumEditX :: NEM_NoTest);

	m_Distanz.SetFocus();

	// Member initialisieren
	m_pCT = new CoordTransX();
	if (m_pCT == NULL)
		return;

	m_dDistanz = 100.;				// Standardvorgabe für Distanz: 100 m
	m_Distanz.SetText ("100.0");
	m_dTextStartWert = 0.;			// Standardvorgabe für TextStartWert: 0 m
	m_TextStartWert.SetText ("0.0");
	m_KilometrText.SetChecked (true);
	m_Teilabschnitte.SetChecked (false);

	// Konvertierung des Anfangs- und Endpunktes für Kilometrierung in Realkoordinaten
	DBKoordInReal (lXA, lYA, m_XAR, m_YAR, m_pCT);
	DBKoordInReal (lXE, lYE, m_XER, m_YER, m_pCT);
	
char pcBuffer [40] = { '\0' };	// Konvertierungspuffer

	m_pCT->CoordTransToStringEx (m_XAR, m_YAR, true, pcBuffer, sizeof (pcBuffer));
	m_RechtswertA.SetText (pcBuffer);
	m_pCT->CoordTransToStringEx (m_XAR, m_YAR, false, pcBuffer, sizeof (pcBuffer));
	m_HochwertA.SetText (pcBuffer);
	m_pCT->CoordTransToStringEx (m_XER, m_YER, true, pcBuffer, sizeof (pcBuffer));
	m_RechtswertE.SetText (pcBuffer);
	m_pCT->CoordTransToStringEx (m_XER, m_YER, false, pcBuffer, sizeof (pcBuffer));
	m_HochwertE.SetText (pcBuffer);

	m_RechtswertA.SetModified (false);	// keine Modifizierung durch den Anwender
	m_HochwertA.SetModified (false);
	m_RechtswertE.SetModified (false);
	m_HochwertE.SetModified (false);

	// ComboBox mit Identifikatoren füllen
	IdListeAufbauen();

} // StandardWerte


// --------------------------------------------------------------------------------------------
// ComboBox mit Identifikatoren füllen
void KilometrDlg :: IdListeAufbauen (void)
{
CEierUhr Wait (m_pW);

ResString resNewItem (ResID(IDS_NEWITEM, pRF), 64);
int iIndex = m_IdentListe.AddString (resNewItem);

	m_IdentListe.SetItemData (iIndex, INVALID_HOBJECTS);	// NULL steht für diesen Eintrag

CTable t (m_IL);
char pcOutBuff[_MAX_PATH];

	for (t.First(); t.Valid(); t.Next())
	{
	IdentListEntryLock l(t);                                        
	
		if (!l) 
			continue;
		InsertEntry(l->KText(), l->Ident());
	}
		
	m_ulIdent = DEX_GetLastIdent();	// den zuletzt verwendeten Identifikator geben lassen
	if (0 != m_ulIdent && -1 != m_ulIdent)
	{
		ClassFromIdentX (m_ulIdent, pcOutBuff);
		iIndex = m_IdentListe.FindString (pcOutBuff);
		// den zuletzt selektierten Identifikator wieder selektieren
		m_IdentListe.ChangeCurrentIndex (iIndex);
	}
	else	// bisher noch kein Identifikator selektiert
	{
		if (m_IdentListe.GetCount() > 1)
			m_IdentListe.ChangeCurrentIndex (1);	// den ersten Identifikator selektieren
		m_ulIdent = IdentErmitteln (&m_IdentListe);
	}
} // IdListeAufbauen

///////////////////////////////////////////////////////////////////////////////
// Neue Objeklasse definieren
HOBJECTS KilometrDlg::DefineNewEntry()
{
DEFINEIDENTDLG DlgData;

	INITSTRUCT(DlgData, DEFINEIDENTDLG);
	DlgData.hWnd = Handle(API_WINDOW_HWND);
	DlgData.lIdent = 0;
	DlgData.hPr = NULL;

HOBJECTS lIdent = DEX_DefineNewObjectsDesc(DlgData);	// neue Identbeschreibung erzeugen

// neu definierten Ident für FocusItem voreinstellen
	if (0 != lIdent) {
	ErrInstall EI (WC_NOIDENT);
	PBDDATA pbdData;
	char cbBuffer[_MAX_PATH];

		INITSTRUCT(pbdData, PBDDATA);
		pbdData.pbdTyp = 'i';
		pbdData.pbdCode = lIdent;
		pbdData.pbdKText = cbBuffer;
		pbdData.pbdLText = NULL;
		pbdData.pbdKTextLen = sizeof(cbBuffer);
		pbdData.pbdLTextLen = 0;

	// PBD-Info holen
		if (EC_OKAY == DEX_GetPBDData(pbdData)) {
		int iIndex = InsertEntry(cbBuffer, lIdent);

			if (-1 != iIndex) {
				m_IdentListe.ChangeCurrentIndex(iIndex);
				return lIdent;
			}

		// ansonsten durchfallen
		// ...
		}
	}

// abgebrochen oder Fehler
	m_IdentListe.ChangeCurrentIndex(-1);
	return INVALID_HOBJECTS;
}

LRESULT KilometrDlg::Dispatch(Event e)
{
	if (WM_DEFINENEWITEM == e.Msg()) {
		m_ulIdent = DefineNewEntry();
		if (INVALID_HOBJECTS == m_ulIdent)
			m_OK.Disable();
		else
			m_OK.Enable();
	}
	return DialogWindow::Dispatch(e);
}

int KilometrDlg::InsertEntry (char const *pEntry, HOBJECTS lIdent)
{
char pcOutBuff[_MAX_PATH];

    ClassFromIdentX (lIdent, pcOutBuff);
    strcat (pcOutBuff, ":");
    strcat (pcOutBuff, pEntry);

#if _TRiAS_VER < 0x0300
int iIndex = m_IdentListe.AddString (pcOutBuff);
#else
// wenn Objektklasse schreibgeschützt ist, dann Objektklassenschlüssel nicht anzeigen
	if (DEX_GetROModeIdent (lIdent))
		return -1;

// wenn mehr als eine Datenquelle geöffnet ist, dann den Namen der zugehörigen in
// Klammern hinten anhängen
	if (DEX_GetOpenConnectionCount (QDCAllOpen|QDCCountQueryDefs) > 1) {
	char cbBuffer[_MAX_PATH];
	HPROJECT hPr = DEX_GetObjectsProject (lIdent);

		_ASSERTE(NULL != hPr);
		if (NULL != DEX_GetDataSourceShortName (hPr, cbBuffer))	{
			strcat (pcOutBuff, " (");
			strcat (pcOutBuff, cbBuffer);
			strcat (pcOutBuff, ")");
		}
	}

// Ident am jeweiligen Item speichern
int iIndex = m_IdentListe.AddString (pcOutBuff);

	if (-1 != iIndex) 
		m_IdentListe.SetItemData(iIndex, lIdent);
#endif // _TRiAS_VER < 0x0300

	return iIndex;
}
