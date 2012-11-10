// Kompakt Funktions-Übersicht ------------------------------------------------------
// File: KOMPWIN.HXX

#if !defined(_KOMPWIN_HXX)
#define _KOMPWIN_HXX

// Anzeigen von Kompakt-Funktionen ---------------------
class KompaktInformation : public DialogWindow {
private:

	PushButton KPKompakt;
	PushButton OKButton, CancelButton;
	PushButton KPAuschr, KPAuftrag;
	PushButton KPAufmass, KPUnterhaltung;
	PushButton KPOekologie, KPRechte;
	PushButton KPBauwerke, KPKataster;
	PushButton KPVerband, KPProjekte,KPHydrologie;

	ResourceFile &_RF;

	pWindow _pW;

protected:
	void _XTENSN_EXPORT ButtonClick (ControlEvt e);

public:
		KompaktInformation (pWindow pW, uint res, ResourceFile &RF);
		~KompaktInformation (void);

//Memberfunktionen

};

// Anzeigen von Hydraulik-Parametern ---------------------
class DatenAuswahl : public DialogWindow {
private:
	long _lPos;
	double _dHoehe;
	char *_pGewNr;

	PushButton OKButton, CancelButton;
	FixedText _GewNr,_Pos,_Hoehe;

	pWindow _pW;

protected:
	void _XTENSN_EXPORT ButtonClick (ControlEvt e);

public:
		DatenAuswahl (pWindow pW, uint res, ResourceFile &RF);
		~DatenAuswahl (void);

//Memberfunktionen
		long &Pos ( void ) { return _lPos; };
		double &Hoehe ( void ) { return _dHoehe; };
		char *GewNr ( void ) { return _pGewNr; };
};
//-----------------------------------------------------------------
#endif 	// _KOMPWIN_HXX
