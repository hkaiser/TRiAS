 // Definition Bildung neuer Merkmale ------------------------------------------------------
// File: BILDEN.HXX

#if !defined(_BILDEN_HXX)
#define _BILDEN_HXX

// Definieren von ObjKlassenFenstern ---------------------
class CreateFeature : public DialogWindow {
private:
	IDMTree * _pIDM;
	MultiSelListBox _ObjClass;
	ListBox _MClass;
	long *_pMCode;
	FixedText _NewM;
	char *_pText; 
	short _IDFlag,_MCFlag;
	short _isVorsatz;
	
	PushButton OKButton, CancelButton;
	RadioButton _Vorsatz,_Anhang;
	ResourceFile &_RF;

	pWindow _pW;

protected:
	void _XTENSN_EXPORT ButtonClick (ControlEvt);
	void _XTENSN_EXPORT ListBoxSel (ControlEvt e);



public:
		CreateFeature (pWindow pW, uint res, ResourceFile &RF, IDMTree * pIdent);
		~CreateFeature (void);

//Memberfunktionen
	Bool FillObjClassList (void);
	Bool FillMClassList( void);
	long *MCode ( void ) { return _pMCode; };
	long GetMCode ( int);
	long GetIdent ( int, short *);
	char *MText( void ) { return _pText; };
	short isVorsatz(void) { return _isVorsatz; };
};    
//--------------------------------------------------------------------------
#endif	//BILDEN.HXX

