 // Definition von AuswahlModi ------------------------------------------------------
// File: KOMPGEW.HXX

#if !defined(_KOMPGEW_HXX)
#define _KOMPGEW_HXX

#include "txtedit.hxx"


// Definieren von GewKlassenFenstern ---------------------
class KompaktKlassenAuswahl : public DialogWindow {
private:
	MultiSelListBox _ObjClass;
	MultiSelListBox _GewClass;
	bool _isValid;
	class TR_OCLTree *_pGew;
	long *_lClassIdent;
	long *_lGewIdent;
	ulong _lIDCode;
	short _iTyp;
	short _iRefTyp;
	KompaktHeader *_pKH;
	char *_pMText;
	PushButton OKButton, CancelButton, StoreButton, DeleteButton;
	ResourceFile &_RF;

	pWindow _pW;
	short _iChanged;
protected:
	void _XTENSN_EXPORT ButtonClick (ControlEvt);
	void _XTENSN_EXPORT ListBoxSel (ControlEvt e);



public:
		KompaktKlassenAuswahl (pWindow pW, uint res, ResourceFile &RF, KompaktHeader *pKH, short iTyp);
		~KompaktKlassenAuswahl (void);

//Memberfunktionen
	bool isValid ( void ) { return _isValid; };
	Bool FillObjClassList (void);
	Bool FillGewClassList (void);
	void ErfasseObjKlasse (int);
	void ErfasseGewKlasse (int);
	void StoreIdentFeature( long );
	void DeleteIdentFeature( long );
	void StoreIdentGewaesser(long, long);
	void DeleteIdentGewaesser(long, long);
	void DeleteGewInformation(void);
	void AddGewInformation ( void );
	void Aktualisieren ( void );
	void Korrigieren ( void );
	void BaumAktualisieren( void );
	short isChanged(void) { return _iChanged; };
	bool KlassenTyp (short,long);
	void SetzePBDMCode ( long, long, ResString);
	void SetzePBDIDCode ( short , long , long );
};    
//-------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////
// Definieren von GewKlassenUebersicht ---------------------
class TriasGewaesser : public DialogWindow {
private:
	MultiSelListBox _GewClass;
	bool _isValid;
	long *_pObj;
	long _lDiff;
	int _iCount;
	short _iFlag;
	short _iTyp;
	class KPTree *_pGew;
	FixedText _LenKompakt,_LenTRiAS,_Name,_Von,_Bis;
	FixedText _GesLaenge;
	FixedText _Ueb;
	PushButton OKButton, CancelButton,_KompShow;
	RadioButton _Alle,_Kataster,_Graphik,_Laenge,_Multi;
	RadioButton _NurKataster,_NurGraphik;
	ResourceFile &_RF;
	char *_pGewNr;
	class CKompaktDLL *_hLib;		// KompaktDLL

	pWindow _pW;

protected:
	void _XTENSN_EXPORT ButtonClick (ControlEvt);
	void _XTENSN_EXPORT ListBoxSel (ControlEvt e);


public:
		TriasGewaesser (pWindow pW, uint res, ResourceFile &RF, KPTree * pGew, CKompaktDLL *, long lDiff,short iFlag);
		~TriasGewaesser (void);

//Memberfunktionen
	bool isValid ( void ) { return _isValid; };
	Bool FillGewClassList (void);
	long GetObjNumber ( int , long *);
	long GetAllObjects ( int );
	long *Obj ( void ) { return _pObj; };
};    
//////////////////////////////////////////////////////////////////////////
// Definieren Parameterübersicht ---------------------
class ParameterAuswahl : public DialogWindow {
private:
	bool _iChangeGew;
	long _lGewDiffLaenge;
	double _dGewDiffMeter;
	double _dGewDiffProzent;
// KK010809
	long _lGewSchrittweite;
	long _lGewPuffer;

	ComboBox _GewClass;
	RadioButton _DefProzent,_DefMeter;

// KK010810
	TxtEdit _GewDiff,_GewSW,_GewPuffer;
	bool _iStatus;

//	FixedText _GewDiff,_GewSW,_GewPuffer;

	bool _isValid;
	KompaktHeader *_pKH;
	PushButton OKButton, CancelButton, _DefGew;
	ResourceFile &_RF;
	short _iChange;
	pWindow _pW;

protected:
	void _XTENSN_EXPORT ButtonClick (ControlEvt);
	void _XTENSN_EXPORT ListBoxSel (ControlEvt e);

public:
		ParameterAuswahl (pWindow pW, uint res, ResourceFile &RF, KompaktHeader *pKH);
		~ParameterAuswahl (void);

//Memberfunktionen
	bool isValid ( void ) { return _isValid; };
	Bool FillGewClassList (void);
	bool CodeModifikation ( void);
	void SpeichereNeuenCode ( void );
	void SpeichereNeuenGewCode ( char * );
	short isChanged(void) { return _iChange; };
};    
//-------------------------------------------------------------------------
// Definieren Hydraulikübersicht ---------------------
class HydraulikAuswahl : public DialogWindow {
private:
	short _iChange;
	short _iTyp;
	ComboBox _HydrClass;
	bool _isValid;
	KompaktHeader *_pKH;
	PushButton OKButton, CancelButton, _DefHydr;
	ResourceFile &_RF;        

	pWindow _pW;

protected:
	void _XTENSN_EXPORT ButtonClick (ControlEvt);
	void _XTENSN_EXPORT ListBoxSel (ControlEvt e);


public:
		HydraulikAuswahl (pWindow pW, uint res, ResourceFile &RF, KompaktHeader *pKH, short iTyp);
		~HydraulikAuswahl (void);

//Memberfunktionen
	bool isValid ( void ) { return _isValid; };
	Bool FillHydrClassList (void);
	short isChanged(void) { return _iChange; };

};    
//-------------------------------------------------------------------------
// Definieren ParameterEinstellung ---------------------
class ParameterEinstellung : public DialogWindow {
private:
	bool _isValid;
	KompaktHeader *_pKH;
	FixedText _DefName;
	PushButton OKButton, CancelButton, _DefGew,_DefHydr,_DefFla;

	ResourceFile &_RF;
	char * _pName;
	short _iFlag;

	pWindow _pW;

protected:
	void _XTENSN_EXPORT ButtonClick (ControlEvt);


public:
		ParameterEinstellung (pWindow pW, uint res, ResourceFile &RF, KompaktHeader *pKH);
		~ParameterEinstellung (void);

//Memberfunktionen
	bool isValid ( void ) { return _isValid; };
	bool GetKompaktUserName ( char *, short);
	bool SetKompaktUserName ( char *, short);
	bool isChanged (void) { return _iFlag;};
};    
//-------------------------------------------------------------------------

//-------- GewaesserStatistik -----------------------------
class GewaesserStatistik : public DialogWindow {
private:
	bool _isValid;
	long _lDiff;
	long _lCntKat;
	long _lCntTRiAS;
	long _lCntBeide;
	long _lCntDiff;

	KPTree *_pGew;
	FixedText _NurKatGew,_NurTRiASGew,_BeideGew,_DiffLaenge;
	FixedText _DiffLaengenTyp;
	PushButton OKButton;
	ResourceFile &_RF;
	pWindow _pW;

protected:
	void _XTENSN_EXPORT ButtonClick (ControlEvt);


public:
		GewaesserStatistik (pWindow pW, uint res, ResourceFile &RF, long lDiff, KPTree *pGew);
		~GewaesserStatistik (void);

//Memberfunktionen
	bool isValid ( void ) { return _isValid; };
	void ListeGewaesser ( void );
};    


//-------- BauwerkeStatistik -----------------------------
class BauwerkeStatistik : public DialogWindow {
private:
	MultiSelListBox _BauwClass;
	FixedText _BauwCount;
	TR_OCLTree *_pBauw;
	bool _isValid;
	long *_pObj;
	long _lCount;
	PushButton OKButton, CancelButton;
	ResourceFile &_RF;
	pWindow _pW;

protected:
	void _XTENSN_EXPORT ButtonClick (ControlEvt);
	void _XTENSN_EXPORT ListBoxSel (ControlEvt e);

public:
		BauwerkeStatistik (pWindow pW, uint res, ResourceFile &RF,TR_OCLTree *pBauw);
		~BauwerkeStatistik (void);

//Memberfunktionen
	bool isValid ( void ) { return _isValid; };
	Bool FillBauwClassList (void);
	long GetIdentNumber (int,long *);
	long *Obj ( void ) { return _pObj; };
};    
///////////////////////////////////////////////////////////////////////////
// Definieren von FlaechenTypen ---------------------
class GebietsFlaechen : public DialogWindow {
private:
	bool _isValid;
	short _iTyp;
	PushButton OKButton;
	RadioButton _Alle,_Gemeinde,_Behoerde,_Bezirk,_Einzug;
	ResourceFile &_RF;

	pWindow _pW;

protected:
	void _XTENSN_EXPORT ButtonClick (ControlEvt);

public:
		GebietsFlaechen (pWindow pW, uint res, ResourceFile &RF);
		~GebietsFlaechen (void);

//Memberfunktionen
	bool isValid ( void ) { return _isValid; };
	short &FlaechenTyp ( void ) { return _iTyp; };
};    
//////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------
#endif	//KOMPGEW.HXX

