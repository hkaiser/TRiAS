// Dialogfenster für Modifizierung von Stützpunktkoordinaten
// File: SPMODDLG.HXX
// W. Mörtl

#if !defined(_SPMODDLG_HXX)
#define _SPMODDLG_HXX


class VertexModifyDlg : public DialogWindow
{
private:
	pWindow m_pW;
	CoordTransX* m_pCT;

	DoubleNumEditX m_X, m_Y;
	PushButton m_AbschlussButton, m_LoeschButton;
	
	IObjektGeometrie* m_pIOG;	// (Interface des) editierten EObjektes
	long m_lInd;		// Index (bezgl. m_pIOG), bei dem etwas passieren soll
	bool m_bMehrf;		// Löschen mit LoeschButton ist mehrfach/einfach möglich (true/false)
	Punkt m_DelPkt;		// Punkt, der durch den LoeschButton gelöscht werden soll
	bool m_bIntern;		// Editierfelder X bzw. Y werden intern (true) bzw. extern durch Anwender
						//  beeinflußt
	bool m_bPtKorr;		// in m_X bzw. m_Y wurden durch Anwender Änderungen vorgenommen

// Memberfunktionen	
	void StandardWerte (long lInd);
	void KoordTextToDB (Punkt& ResultPkt);
	void KoordDBToText (Punkt& Pt);
	bool idb_abschluss (void);
	void idb_loeschen (void);

protected:
	void ButtonClick (ControlEvt e);	// Reaktion bei Button-Betätigung
	void EditChange (ControlEvt e);		// Reaktion bei Änderungen im Editierfenster

public:
		VertexModifyDlg (pWindow pW, IObjektGeometrie* pIOG, long lInd, bool bMehrf = true);
		~VertexModifyDlg (void);

// weitere Memberfunktionen
	bool GetPunkt (Punkt& ResultPkt);
	// "const" in der nachfolgenden Deklaration wird vom Compiler gefordert
	void SetAbschlussButtonText (const char* pcText) { m_AbschlussButton.SetText (pcText); }
	void SetDeleteButton (bool bAkt);
};

#endif // _SPMODDLG_HXX
