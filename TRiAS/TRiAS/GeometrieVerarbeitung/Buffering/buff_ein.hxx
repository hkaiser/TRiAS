// Eingaben für Buffering
// File: BUFF_EIN.HXX

#if !defined(_BUFF_EIN_HXX)
#define _BUFF_EIN_HXX



class Parameter : public DialogWindow 
{
private:
	pWindow _pW;

	DoubleNumEditX m_BufBreite;
	NumEditX m_BufAnzahl;
	RadioButton m_PufferRBttn, m_KreisRBttn;
	CheckBox m_RingCBox;
	RadioButton m_SpitzeRBttn, m_FlachRBttn, m_BogenRBttn;
	FixedText m_Prompt;
	DoubleNumEditX m_KantenLaenge;
	PushButton m_OKBttn;

	bool m_bIntern;		// Editierfelder m_KantenLaenge wird intern (true) bzw. extern (false)
						// durch Anwender beeinflußt
	double m_dWidth;	// Pufferbreite (mit Kommastellen möglich)
	int m_iPuffAnzahl;	// Anzahl der zu bildenden Puffer
	bool _bTyp;			// Puffertyp (echter Puffer: true, Kreis: false)
	PuffBau m_PBau;		// Puffer ringförmig / als volle Fläche
	PuffBau m_PBauSave;	// zwischengespeicherter m_PBau-Wert, wenn m_RingCBox deaktiviert ist
	ConvexMode m_cmMode;// Ausformung der konvexen Ecken
	double m_dPrec;		// Kantenlänge (in Meter) des n-Ecks, durch den Kreisbogen an konvexen
						// Ecken approximiert wird (mit Kommastellen möglich)
    int m_iAllOT;		// Kombination der Typ(en) der ausgewählten Objekte
	
	void StandardWerte (void);

protected:
	void ButtonClick (ControlEvt);
	void EditChange (ControlEvt e);
	int ParameterEinlesen (NumEditX* pEingWert);
//	double DblParameterEinlesen (DoubleNumEditX* pEingWert);

public:
// Konstruktor/Destruktor
		Parameter (pWindow pW, ResID res);
		~Parameter (void);

	double GetBreite (void) { return m_dWidth; }
	int GetAnzahl (void) { return m_iPuffAnzahl; }
	bool GetTyp (void) { return _bTyp; }
	PuffBau GetRing (void) { return m_PBau; }
//	PuffBau GetRingSave (void) { return m_PBauSave; }
	ConvexMode GetMode (void) { return m_cmMode; }
	double GetPrec (void) { return m_dPrec; }

	void VorigeEinstellung (double dWidth, int iPuffAnzahl, bool bTyp, PuffBau PBau,
							ConvexMode cmMode, double dPrec);
};

#endif  // _BUFF_EIN_HXX
