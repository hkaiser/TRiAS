// Kilometrierung
// File: KILOMETR.HXX
// W. Mörtl
      
      
#if !defined(_KILOMETR_HXX)
#define _KILOMETR_HXX


class KilometrDlg : public DialogWindow
{
private:
	pWindow m_pW;
	CoordTransX* m_pCT;

	DoubleNumEditX m_RechtswertA, m_HochwertA, m_RechtswertE, m_HochwertE;
	DoubleNumEditX m_Distanz, m_TextStartWert;
	PushButton m_OK;
	CheckBox m_KilometrText, m_Teilabschnitte;
	ComboBox m_IdentListe;

	double m_XAR, m_YAR;	// Koordinaten des Anfangspunktes bzw. 
	double m_XER, m_YER;	// des Endpunktes für Kilometrierung in Real-Koordinaten 
	KoOrd m_XADB, m_YADB;	// Koordinaten des Anfangspunktes bzw. 
	KoOrd m_XEDB, m_YEDB;	// des Endpunktes für Kilometrierung in DB-Koordinaten 
	double m_dDistanz;		// vorgebbare Distanz für Kilometrierung (Standard: 100.0)
	double m_dTextStartWert;// vorgebbare Startwert für den Text an den Kilometrierungspunkten
							// (Standard: 0.0)
	bool m_bText;			// Text an Kilometrierungspunkten erzeugen (true)
	bool m_bTeil;			// Teilabschnitte als separate Objekte erzeugen (true)

	IdentList& m_IL;
	ulong m_ulIdent;		// zuletzt ausgewählter Identifikator in ComboBox m_IdentListe

// Memberfunktionen
	void StandardWerte (KoOrd lXA, KoOrd lYA, KoOrd lXE, KoOrd lYE);
	void IdListeAufbauen (void);


protected:
	LRESULT Dispatch(Event e);
	void ButtonClick (ControlEvt);  // Reaktion auf Button-Betätigung
	void ListBoxSel (ControlEvt);	// einfacher Klick (der einen zusätzlichen OK-Button-Klick
									// erfordert)
	void EditChange (ControlEvt);

	HOBJECTS DefineNewEntry();
	int InsertEntry (char const *pEntry, HOBJECTS lIdent);

public:
// Konstruktor/Destruktor
		KilometrDlg (pWindow, ResID, IdentList&, KoOrd, KoOrd, KoOrd, KoOrd);
		~KilometrDlg (void);

// Memberfunktion
	KoOrd GetXA (void) { return m_XADB; }	// Rückgabe der x-Koordinate bzw.
	KoOrd GetYA (void) { return m_YADB; }	//  y-Koordinate des Anfangspunktes
	KoOrd GetXE (void) { return m_XEDB; }	// Rückgabe der x-Koordinate bzw.
	KoOrd GetYE (void) { return m_YEDB; }	//  y-Koordinate des Endpunktes
	double GetDistanz (void) { return m_dDistanz; }
	double GetTextStartWert (void) { return m_dTextStartWert; }
	bool GetKilometrText (void) { return m_bText; }
	bool GetTeilabschnitt (void) { return m_bTeil; }
	ulong GetIdent (void) { return m_ulIdent; }
};

#endif  // _KILOMETR_HXX
