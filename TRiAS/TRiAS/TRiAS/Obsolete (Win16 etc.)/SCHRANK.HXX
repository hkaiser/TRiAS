// Klassendefinitionen fuer Kartenschrankanzeige
// File: SCHRANK.HXX

#if !defined(_SCHRANK_HXX)
#define _SCHRANK_HXX

const int NUMFACH = 20;

#if !defined(NOSCHRANKSCHNULLI)

enum FachSpec { 
	FACH_MECKLENBURG = 20,
	FACH_SACHSENANHALT = 15,
	FACH_BRANDENBURG = 8,
	FACH_THUERINGEN = 9,
	FACH_SACHSEN = 4,
};

class SchrankSchnulli : public ModeLessDialog {
private:
	RadioButton *_Fach[NUMFACH];

protected:
	Bool QueryClose (Event e);
	void FocusChange (FocusChangeEvt e);

public:
// Konstruktor
		SchrankSchnulli (pWindow pW);

// Memberfunktionen
	RadioButton &Fach (short i) { return *(_Fach[(i >= 0 && i < NUMFACH) ? i : 0]); }
	void SetFach (char *Nomenkl);
	short GetFachNummer (short NM, short A, short B);

// Destruktor
		~SchrankSchnulli (void);
};

#endif // NOSCHRANKSCHNULLI

#endif // _SCHRANK_HXX
