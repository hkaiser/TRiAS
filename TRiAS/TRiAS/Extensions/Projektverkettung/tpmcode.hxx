// Merkmalscode-šbersicht ------------------------------------------------------
// File: TPMCODE.HXX

#if !defined(_TPMCODE_HXX)
#define _TPMCODE_HXX

// Anzeigen von Merkmalskodes ---------------------
class TPMCodeDef : public DialogWindow {
private:
	char * _pMCode;
	PushButton OKButton, CancelButton;

	TxtEdit _ShowTPMCode;
	ListBox TPMCodeList;
	ResourceFile &_RF;
	pWindow _pW;

protected:
	void _XTENSN_EXPORT ButtonClick (ControlEvt);
	void _XTENSN_EXPORT ListBoxSel (ControlEvt);
	void _XTENSN_EXPORT ListBoxClk (ControlEvt);


public:
		TPMCodeDef (pWindow, uint res, ResourceFile &RF );
		~TPMCodeDef (void);

//Memberfunktionen
	char *GetTPMCode( void )  { return _pMCode; };

};


#endif 	// _TPMCODE_HXX


