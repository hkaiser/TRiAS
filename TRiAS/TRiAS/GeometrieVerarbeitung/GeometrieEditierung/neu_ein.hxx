// Eingaben bei Neuerfassung
// File: NEU_EIN.HXX
// W. Mörtl
      
      
#if !defined(_NEU_EIN_HXX)
#define _NEU_EIN_HXX

class NeuEditDlg : public DialogWindow
{
private:
	pWindow _pW;
	CoordTransX* m_pCT;	// Klasse für Zugriff auf Header-Informationen
	IdentList& _IL;

	ComboBox m_IdentListe;
	GroupBox _Rahmen;	// Rahmen für Speicherform
	SingleLineEdit _ObjName;
	DoubleNumEditX _XKoord, _YKoord;
	RadioButton _Temporaer, _Permanent;
	PushButton _OKButton, _FortsetzButton;
	PushButton _ZuZiehButton, _LoeschButton, _InselButton, _KreisButton;
	            
	EObjekt* _pEO;		// editiertes EObjekt
	ulong m_ulIdent;	// selektierter Identifikator
	char* _pcObjName;	// Objektname des editierten Objektes
	SpForm _sfSForm;	// Speicherform (permanent, temporär)
	short _XLen;		// Anzahl der Vorkomma-Ziffern von _XKoord
	short _YLen;		// Anzahl der Vorkomma-Ziffern von _YKoord
		
	bool _bIntern;		// Editierfelder XKoord bzw. YKoord werden intern (true) bzw. extern durch
						// Anwender beieinflußt
	bool _bPtKorr;		// in _XKoord bzw. _YKoord wurden durch Anwender Änderungen vorgenommen
	Punkt* m_pZuZiePkt;	// Endpunkt einer Kante, die verlängert werden soll, für Zuziehen
	
	void StandardWerte (void);
	void ButtonClick (ControlEvt);  // Reaktion bei Button-Betätigung
	void ListBoxSel (ControlEvt);
	void ListBoxClk (ControlEvt);
	void EditChange (ControlEvt e);	// Reaktion bei Änderungen im Editierfenster
	
	long IdentErmitteln (void);
	void KoordTextToDB (Punkt& ResultPkt);
	void KoordDBToText (Punkt& Pt);
	void StellenAnzahl (short& iXL, short& iYL);
	void idb_cancel (void);
	void idb_ok (void);
	void idb_fortsetzen (void);
	void idb_zuziehen (void);
	void idb_loeschen (void);
	void idb_insel (void);
	void idb_kreis (void);
	void PunktKorrigieren (void);
	void FlaecheZuziehen (Masche* pF);
	void OKB (void);
	void Focus (void);
	void DialogBoxCaption (void);
		
protected:

public:
// Konstruktor/Destruktor
		NeuEditDlg (pWindow pW, IdentList&, EObjekt*, char*, Punkt* = NULL);
		~NeuEditDlg (void);

// weitere Memberfunktionen
	ulong GetIdent (void) { return m_ulIdent; }
	SpForm GetForm (void) { return _sfSForm; }
};

#endif  // _NEU_EIN_HXX
