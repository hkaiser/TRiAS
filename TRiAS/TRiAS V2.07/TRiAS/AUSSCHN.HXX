// Dialogfenster fuer die Eingabe eines Bildausschnittes/Maßstabes ------------
// File: AUSSCHN.HXX

#if !defined(_AUSSCHN_HXX)
#define _AUSSCHN_HXX

#define INBUFFLEN 	64
#define CNT_MASSTAB	16

class CAusschnittsDlg : public DialogWindow {
private:
// allgemeine Member
	PushButton m_pbOK;
	PushButton m_pbCancel;
#if !defined(WIN32)
	PushButton m_pbHelp;
#endif // WIN32

// Member für Maßstabsauswahl
	RadioButton m_rbMasstab;
//	FixedText m_ftMasstab;
	ComboBox m_cbMasstab;
	
	long m_lMasstab;
	
//	GroupBox m_gbMittel;
//	FixedText m_ftMittelHoch;
//	FixedText m_ftMittelRechts;
	DoubleNumEdit m_dneMittelHochWert;
	DoubleNumEdit m_dneMittelRechtsWert;

// Member für Ausschnittsdefinition
	RadioButton m_rbAusschnitt;
//	GroupBox m_gbOben;
//	FixedText m_ftObenHoch;
//	FixedText m_ftObenRechts;
	DoubleNumEdit m_dneObenHochWert;
	DoubleNumEdit m_dneObenRechtsWert;

//	GroupBox m_gbUnten;
//	FixedText m_ftUntenHoch;
//	FixedText m_ftUntenRechts;
	DoubleNumEdit m_dneUntenHochWert;
	DoubleNumEdit m_dneUntenRechtsWert;

	ObjContainer *m_pOC;	// eingegebener ObjContainer
	CoordTrans *m_pCT;	// aktuelle CTF
	
	Dimension m_dimDotsPerMM;

	char *m_pInBuff;	// allgemeiner EingabePuffer
	char *m_pInBuffY;

protected:
	void ButtonClick (ControlEvt);
	void ListBoxSel (ControlEvt);
	void EditFocusChg (EditFocusChgEvt);

	void SetStateMasstab (void);
	void SetStateAusschnitt (void);

	long GetMasstab (short iIndex);
	
	BOOL EvalMasstab (BOOL fShow = TRUE);
	BOOL GetValue (DoubleNumEdit &dblNED, double &dbl, DoubleNumEdit &, double &);
	BOOL EvalCoords (void);
	
public:
// Konstruktor/Destruktor
		CAusschnittsDlg (pWindow, CoordTrans *pCTF, Dimension);
		~CAusschnittsDlg (void);
		
	BOOL Init (Rectangle *pRc = NULL);

	ObjContainer NewRect (void) { return *m_pOC; }
	CoordTrans *& pCT (void) { return m_pCT; }
};


#endif // _AUSSCHN_HXX

