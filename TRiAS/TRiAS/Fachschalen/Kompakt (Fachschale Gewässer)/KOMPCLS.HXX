// FlaechenAuswahl ------------------------------------------------------
// File: KOMPCLS.HXX

#if !defined(_KOMPCLS_HXX)
#define _KOMPCLS_HXX

// Definieren von FlaechenKlassenFenstern ---------------------
class TriasFlaechen : public DialogWindow {
private:
	MultiSelListBox _ObjClass;
	bool _isValid;
	class CTop_ObjTree *_pObj;
	long *_lClassIdent;
	PushButton OKButton, CancelButton;
	ResourceFile &_RF;

	pWindow _pW;

protected:
	void _XTENSN_EXPORT ButtonClick (ControlEvt);
	void _XTENSN_EXPORT ListBoxSel (ControlEvt e);



public:
		TriasFlaechen (pWindow pW, uint res, ResourceFile &RF, long lIdent );
		~TriasFlaechen (void);

//Memberfunktionen
	bool isValid ( void ) { return _isValid; };
	Bool FillObjClassList (long);
	long *FlaechenCls();
	void ErfasseObjKlasse (int);
};    
/////////////////////////////////////////////////////////////////
// Definieren von KlassenFenstern ---------------------
class AlleTRiASKlassen : public DialogWindow {
private:
	MultiSelListBox _ObjClass;
	bool _isValid;
	long *_lClassIdent;
	PushButton OKButton, CancelButton;
	ResourceFile &_RF;

	pWindow _pW;

protected:
	void _XTENSN_EXPORT ButtonClick (ControlEvt);
	void _XTENSN_EXPORT ListBoxSel (ControlEvt e);



public:
		AlleTRiASKlassen (pWindow pW, uint res, ResourceFile &RF, long lIdent );
		~AlleTRiASKlassen (void);

//Memberfunktionen
	bool isValid ( void ) { return _isValid; };
	Bool FillObjClassList (long);
	long *TRiASCls(void) { return _lClassIdent; };
	void ErfasseObjKlasse (int);
};    
//-----------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////
// Definieren von KlassenFenstern ---------------------
class TRiASRechercheKlassen : public DialogWindow {
private:
	MultiSelListBox _ObjClass;
	MultiSelListBox _InClass;
	MultiSelListBox _InAusClass;
	long *_lClassIdent;
	long _lONNew;
	bool _isValid;
	FixedText _InText,_InAusText;
	PushButton OKButton, CancelButton,_NewButton;
	ResourceFile &_RF;
	TR_IDMTree *_pIDM;
	pWindow _pW;

protected:
	void _XTENSN_EXPORT ButtonClick (ControlEvt);
	void _XTENSN_EXPORT ListBoxSel (ControlEvt e);



public:
		TRiASRechercheKlassen (pWindow pW, uint res, ResourceFile &RF, long lIdent , TR_IDMTree *pIDM);
		~TRiASRechercheKlassen (void);

//Memberfunktionen
	bool isValid ( void ) { return _isValid; };
	long *Obj(void) { return _lClassIdent; };
	long Objekt(void) { return _lONNew;};
	bool FillObjClassList (void);
	bool FillRechercheList(void);
	bool FillErgebnisListe(TR_IDOTree *, MultiSelListBox*);
	void ErfasseObjKlasse (int);
	void ErfasseInKlasse (int);
	void ErfasseInAusKlasse (int);
};    
//-----------------------------------------------------------------------------
#endif	//KOMPCLS.HXX

