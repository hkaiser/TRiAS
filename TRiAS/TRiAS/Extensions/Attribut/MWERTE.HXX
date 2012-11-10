// Definition von Teilprojekten ------------------------------------------------------
// File: MWERTE.HXX

#if !defined(_MWERTE_HXX)
#define _MWERTE_HXX

// Zuordnen MKodes/Mwerte ---------------------
class DefineMerkmalsWert : public DialogWindow {
private:
	long _lMCode;
	short _iModus;
	ListBox _MClass;
	ComboBox _RechArt;
	
	PushButton OKButton, CancelButton,_StoreMWert;

	ResourceFile &_RF;

	pWindow _pW;

	class IDMTree *_pIDM;
	
	TxtEdit _MWert;
	char *_pText;

protected:
	void _XTENSN_EXPORT ButtonClick (ControlEvt);
	void _XTENSN_EXPORT ListBoxSel (ControlEvt e);
	void _XTENSN_EXPORT ListBoxClk (ControlEvt e);



public:
		DefineMerkmalsWert (pWindow pW, uint res, ResourceFile &RF, IDMTree *pIDM);
		~DefineMerkmalsWert (void);

//Memberfunktionen
	Bool FillMClassList( void);
	Bool FillModusList(void);
	long GetMCode ( int );
};    

#endif	//MWERTE.HXX
