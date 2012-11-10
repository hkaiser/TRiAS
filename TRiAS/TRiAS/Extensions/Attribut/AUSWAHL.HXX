 // Definition von AuswahlModi ------------------------------------------------------
// File: AUSWAHL.HXX

#if !defined(_AUSWAHL_HXX)
#define _AUSWAHL_HXX

// Definieren von ObjKlassenFenstern ---------------------
class ObjClassAuswahl : public DialogWindow {
private:
	IDMTree * _pIDM;
	MultiSelListBox _ObjClass;
	MultiSelListBox _MClass;
	long *_pMCode;
	short _IDFlag,_MCFlag;
	
	PushButton OKButton, CancelButton,_MCDelete,_MCModify,_MCVergleich;
	ResourceFile &_RF;

	pWindow _pW;

protected:
	void _XTENSN_EXPORT ButtonClick (ControlEvt);
	void _XTENSN_EXPORT ListBoxSel (ControlEvt e);



public:
		ObjClassAuswahl (pWindow pW, uint res, ResourceFile &RF, IDMTree * pIdent);
		~ObjClassAuswahl (void);

//Memberfunktionen
	Bool FillObjClassList (void);
	Bool FillMClassList( void);
	long *MCode ( void ) { return _pMCode; };
	long GetMCode ( int);
	long GetIdent ( int, short *);
};    
//--------------------------------------------------------------------------
#endif

