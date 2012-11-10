// Klassendefinition fÅr Koordinatenanzeige
// File: NOMENKL.HXX

#if !defined(_NOMENKL_HXX)
#define _NOMENKL_HXX

enum Masstab { M_INVALID, M10000, M25000, M50000 };

#if !defined(NONOMENKL)
class NomenklaturDlg : public ModeLessDialog {
private:
// Controls
	FixedText NomenklaturTyp;	// Anzeige des Ma·stabes
	FixedText Nomenklatur;		// Anzeige der Nomenklatur

	CoordTrans *_pCT;

// Anzeigemode
	Masstab _M;		// AnzeigeMa·stab: 1:25000 oder 1:50000

// lokale Funktionen
	char *GetNomenklatur (double, double, char *, Masstab);

protected:
	Bool QueryClose (Event);
	void FocusChange (FocusChangeEvt e);

public:
// Konstruktor
		NomenklaturDlg (pWindow pW, Masstab M, CoordTrans *pCT);

// Memberfuntkionen
	void SetCoords (Point &);	// aktuelle Nomeklatur berechnen
	void SetMode (Masstab);		// Ma·stab setzen

	CoordTrans *& pCT (void) const { return (CoordTrans *&)_pCT; }

// friend Funktionen
friend long gaugeo (double *, double *, double *, double *);
};

#endif // NONOMENKL

#endif // _NOMENKL_HXX
