 // Definition von Datenquellen ----------------------------------------------
// File: KPPROJECT.HXX

#if !defined(_KPPROJECT_HXX)
#define _KPPROJECT_HXX

// Definieren von DatenquellenUebersicht ---------------------
class TRiASDatenQuelle : public DialogWindow {
private:

	ComboBox _DataClass;
	DATACLList *_pData;
	bool _isValid;

	HPROJECT _hPr;
	short _iCount;

	PushButton OKButton, CancelButton;
	ResourceFile &_RF;

	pWindow _pW;

protected:

	void _XTENSN_EXPORT ButtonClick (ControlEvt);
	void _XTENSN_EXPORT ListBoxSel (ControlEvt e);


public:

		TRiASDatenQuelle (pWindow pW, uint res, ResourceFile &RF);
		~TRiASDatenQuelle (void);

//Memberfunktionen

	bool isValid ( void ) { return _isValid; };
	BOOL FillDataClassList (void);
	HPROJECT GetProjectHandle(void) { return _hPr;};
	short GetProjectCount(void) { return _iCount;};

};    
//-------------------------------------------------------------------------
#endif	//KPPROJECT.HXX

