// Klassendefinition fuer Masstabsanzeige
// File: MASSTAB.HXX

#if !defined(_MASSTAB_HXX)
#define _MASSTAB_HXX


#if !defined(NOMASSTAB)
class MasstabDlg : public ModeLessDialog {
private:
// Controls
	FixedText Masstab;		// Anzeige des Maástabes

// Transformationsparameter
	Dimension _DotsPerMM;		// Bildschirmaufl”sung
	pWindow _pW;
	CoordTrans *_pCT;

protected:
	Bool QueryClose (Event);
	void FocusChange (FocusChangeEvt e);

public:
// Konstruktor
		MasstabDlg (pWindow pW, CoordTrans *pCTF);

// Memberfuntkionen
	void SetMasstab (Rectangle);	// aktuellen Maástab berechnen
	CoordTrans *& pCT (void) const { return (CoordTrans *&)_pCT; }
};

#endif // NOMASSTAB

#endif // _MASSTAB_HXX
