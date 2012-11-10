// Eingaben und Ergebnisse der Abstandsmessung
// File: ABST_AUS.HXX
// W. Mörtl
      
      
#if !defined(_ABST_AUS_HXX)
#define _ABST_AUS_HXX


#define MESSZEILE 100	// Länge des Konvertierungspuffers für eine Meßzeile


class AbstandsWerte : public ModeLessDialog
{
private:
	MultiLineEdit _Ergebnis;
	FixedText _Abstand;
	PushButton _Speichern, _Vorzeichen, _Loeschen, _Statistik, _Datei, _Automatisch;
	NumEditX _Schritt;
	DoubleNumEditX _Winkel;
	DoubleNumEditX _Zuwachs;

	char m_cGenau;			// Anzahl der Nachkommastellen für Anzeige des Abstandes
	int _iSchritt;		// Schrittweite und
	double _dWinkel;		//  Winkel für automatische Erzeugung der Abstände
	double _dAbst;			// aktueller Abstand
	double _dZIndex;		// einstellbare Zeilennumerierung (Standard: ab 1.0 aufwärts)
	double _dZuwachs;		// einstellbarer Zuwachs bei der Zeilennumerierung (Standard: 1.0)
	pWindow m_pW;
	int* m_piAnz;	// Anzahl der selektierten (markierten) Objekte in den geöffneten
					// Recherchefenstern
					// m_piAnz[0]  Anzahl der selektierten Objekte außer dem aktivierten
					//             (blinkenden) Objekt
					// m_piAnz[1]  Anzahl der selektierten Flächen (evtl. einschl. einer
					//             aktivierten Fläche)
					// m_piAnz[2]  Anzahl der selektierten Kanten (evtl. einschl. einer
					//             aktivierten Kante)
	int _iOT;			// Typ des aktivierten (blinkenden) Objektes
	char* _pcFileName;	// Name der Datei, in die die Abstände abgespeichert werden sollen
	FILE* _fAbst;		// Datei, in die die Abstände abgespeichert werden sollen
	int _iAnzAbst;		// Anzahl der für Statistik verwendeten Abstände
	double _dSumAbst;	// Summe der Abstände (für Statistik)
	double _dSumAbst2;	// Summe der Abstandsquadrate (für Statistik)
	bool _Vorz;			// Vorzeichen für gemessene Abstände (true = plus, false = minus)
	bool _bSichtb;		// DialogBox ist nicht/sichtbar (false/true)
	bool _bSpForm;		// Speicherform für Ergebnisse (true = Überschreiben, false = Anhängen)

protected:
	void ButtonClick (ControlEvt);  // Reaktion auf Button-Betätigung
	void EditChange (ControlEvt);
	BOOL QueryClose (Event);	// Reaktion auf Betätigung des Systemmenüfeldes
	int SchrittEinlesen (NumEditX* pEingWert);	// Eingabe der Schrittweite
	void ZIndexEinlesen (void);
//	double DblParamEinlesen (DoubleNumEditX* pEingWert);

	void idb_speichern (void);
	void idb_loeschen (void);
	void idb_datei (void);
	void idb_statistik (void);
	bool idb_automatisch (void);
	void AutomatischSpeichern (void);

public:
// Konstruktor/Destruktor
//		AbstandsWerte (void);
		AbstandsWerte (pWindow, ResID, int iOT, int* piAnz, char cGenau);
		~AbstandsWerte (void);

// Member zurückgeben bzw. setzen
	MultiLineEdit* GetErgebnis (void) { return &_Ergebnis; }
	FILE* GetDatei (void) { return _fAbst; }
	bool GetSichtbarkeit (void) { return _bSichtb; }
	void SetSichtbarkeit (bool bSichtb) { _bSichtb = bSichtb; }
	bool GetSpForm (void) { return _bSpForm; }
	void SetSpForm (bool bSpForm) { _bSpForm = bSpForm; }

// weitere Memberfunktionen
	void AbstandEintragen (double dAbst);
	void ErgebnisEintragen (DoublePair AP, DoublePair EP, CoordTransX* pCT);
	char* DateiAuswaehlen (pWindow pParentWindow);
	bool Ueberschreiben (char* pFileName);
};

#endif  // _ABST_AUS_HXX
