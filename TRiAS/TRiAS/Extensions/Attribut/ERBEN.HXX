// Definition von Zuordungskriterien ------------------------------------------------------
// File: ERBEN.HXX

#if !defined(_ERBEN_HXX)
#define _ERBEN_HXX

// Definieren von ObjKlassenFenstern ---------------------
class DefineObjClassErbe : public DialogWindow {
private:
	IDMTree * _pIDM;
	long _Ident2;
	long _MkIdent;
	long *_pMCode;
	long *_lMCode;
	long _MZiel,_MQuelle;
	short _iIdSel;
	short _iMkSel;
	short _isCont;
	short _iGiTyp;
	MultiSelListBox _ObjClass1;
	ListBox _MClass1;
	ListBox _MClass2;
	ListBox _ObjClass2;
	ComboBox _MIdent;
	ComboBox _ZuOrdn;
	
	PushButton OKButton, CancelButton,_Zuordnen,_Loeschen;
	RadioButton _IDCont,_IDMCode;

	ResourceFile &_RF;

	pWindow _pW;

	NumEditX _IntervallWert;
	FixedText _ContText,_MerkmalText;
	long _lWert;
	char _WERT [35];

protected:
	void _XTENSN_EXPORT ButtonClick (ControlEvt);
	void _XTENSN_EXPORT ListBoxSel (ControlEvt e);



public:
		DefineObjClassErbe (pWindow pW, uint res, ResourceFile &RF, IDMTree *pIDM, long *lMCode);
		~DefineObjClassErbe (void);

//Memberfunktionen
	Bool FillObjClassList1 (void);
	Bool FillObjClassList2 (void);
	Bool FillMClassList1( void);
	Bool FillMClassList2( void);
	Bool FillMClassIdent( void);

	void SetzeStandard ( void);
	long Ident2 ( void ) { return _Ident2; };
	long MkIdent ( void ) { return _MkIdent; };
	long *MCode ( void ) { return _pMCode; };
	long Intervall ( void ) { return _lWert; };
	short isContainer ( void ) { return _isCont; };
	long GetIdent ( int, short *);
	long GetMCode ( int, ListBox *);
	void KonsistenzTest( void );
	void BildeMCodeTupel( void );
	void LeseMCodeTupel( void );
	short GiTyp ( void ) { return _iGiTyp; };

};    

//------------------------MKode-Fenster pro Quell-Objekt-------------
// Definieren von MerkmalFenstern ---------------------
class DefineCopyInformation : public DialogWindow {
private:
	long *_pMCode;
	long _ONr;
	MultiSelListBox _MClass;
	
	PushButton OKButton, CancelButton;
	ResourceFile &_RF;
	FixedText _Object,_ObjMerkmal;
	pWindow _pW;

protected:
	void _XTENSN_EXPORT ButtonClick (ControlEvt);
	void _XTENSN_EXPORT ListBoxSel (ControlEvt e);



public:
		DefineCopyInformation (pWindow pW, uint res, ResourceFile &RF,long ONr);
		~DefineCopyInformation (void);

//Memberfunktionen
	Bool FillMClassList( void);
	long *MCode ( void ) { return _pMCode; };
	long GetMCode ( int);
	void SetObjectInformation(void);
	void ShowObjectMerkmal( long );
};    

#endif	//ERBEN.HXX
