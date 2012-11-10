// Merkmalscode-Übersicht ------------------------------------------------------
// File: KPMCODE.HXX

#if !defined(_KPMCODE_HXX)
#define _KPMCODE_HXX

// Anzeigen von Merkmalskodes ---------------------
class KPMCodeDef : public DialogWindow {
private:
	char * _pMCode;
	PushButton OKButton, CancelButton;

	TxtEdit _ShowKPMCode;
	ListBox KPMCodeList;
	ResourceFile &_RF;
	pWindow _pW;
	char *_pMText;

protected:
	void _XTENSN_EXPORT ButtonClick (ControlEvt);
	void _XTENSN_EXPORT ListBoxSel (ControlEvt);
	void _XTENSN_EXPORT ListBoxClk (ControlEvt);


public:
		KPMCodeDef (pWindow, uint res, ResourceFile &RF , char *pText);
		~KPMCodeDef (void);

//Memberfunktionen
	char *GetKPMCode( void )  { return _pMCode; };
	void StoreKPMCode ( char *pMCode , char * pText);

};


#endif 	// _KPMCODE_HXX


