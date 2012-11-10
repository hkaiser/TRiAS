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

#endif 	// _KOMPWIN_HXX
