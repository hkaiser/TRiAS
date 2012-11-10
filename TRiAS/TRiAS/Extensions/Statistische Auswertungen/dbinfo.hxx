// Datenbank-‹bersicht ------------------------------------------------------
// File: DBINFO.HXX

#if !defined(_DBINFO_HXX)
#define _DBINFO_HXX

struct GIEXTREMUM;

// Anzeigen von Datenbankeigenschaften ---------------------
class DataBaseInformation : public DialogWindow {
private:
	

	long _lIdents;
	short *_pDBInfoFeld;
	short _iDBInfo;
	FixedText _DBName;
	FixedText _DBBeschreibung;

	ComboBox _DBInfo;
	FixedText _Datum;

	PushButton OKButton, CancelButton;
	ResourceFile &_RF;

	pWindow _pW;

	IDMTree *_pIDM;

protected:
	void _XTENSN_EXPORT ButtonClick (ControlEvt e);
	void _XTENSN_EXPORT ListBoxSel (ControlEvt e);
//	void _XTENSN_EXPORT ListBoxClk (ControlEvt e);

public:
		DataBaseInformation (pWindow pW, uint res, ResourceFile &RF, IDMTree *pIDM);
		~DataBaseInformation (void);

//Memberfunktionen
	void ShowDataBaseParam ( void );
	long NumberSights ( void );
	long NumberIdents ( void );
	long NumberMCodes ( void );
	long NumberTProjects ( void );
	long NumberDBase ( void );
	long NumberPerm ( void );
	long &Ident ( void ) { return _lIdents; };
	short &DBInfo ( void ) { return _iDBInfo; };
	char * GetHeaderMText ( char * );
	double GetHeaderDWert ( char * );
	void FillDataBaseInformation ( void );
	short GetDBInfo(void);
};

// Anzeigen von Identifikatoren ---------------------
class IdentInformation : public ModeLessDialog {
private:

	bool _fWasInterrupted;

	long _lIdents;	
	long _Number;
	long _Key;
//	FixedText _IDNumber;
//	FixedText _IDKey;
	PushButton CancelButton;
	ResourceFile &_RF;
	IDMTree *_pIDM;
	pWindow _pW;
	long _iRangeAll;
	short _iCurrVal;
	GaugeBox _Status;
	
protected:
	void _XTENSN_EXPORT ButtonClick (ControlEvt);

public:
		IdentInformation (pWindow pW, uint res, ResourceFile &RF, IDMTree *pIDM ,pchar pCaption, long iRange);
		~IdentInformation (void);


//Memberfunktionen
	bool Break (void) { 
#if defined(WIN32)
		App :: Exec (ExecWhileEvent);  // bei Windows nachfragen
#else
		CallAppExec (ExecWhileEvent);
#endif // WIN32
		return _fWasInterrupted; 
	}

	void SetPosition (long lCnt) { _Status.SetPosition ((short) lCnt);}
	void Disable ( void ) { CancelButton.Disable();};
	void Enable ( void ) { CancelButton.Enable();};
	void ModifyWindow ( long Ident );
	void SetText ( long );
	void SetObjectText ( long );
	void SetStart ( void );
	void ModifyGIWindow ( long Ident , double First , double Second);

};
//-----------------------------------------------------------------
// Anzeigen von Objektklassen einer Datenbank ---------------------
class DataBaseObjClass : public DialogWindow {
private:   

	class CHelpTextX *_pHelpText;
	class OBJCLList *_pOCL;
	long _IdCount;
//
// F¸r ClipBoard
	bool _isClipUeberschrift;
	bool _isClipKumulativ;
	bool _isClipEintrag;
	bool _isClipEigenschaft;

//EinzelKlassen
	long _MCode;		// Merkmal
	short _MFlag;
	long _BezugsID;
	char _BezugsTyp;
	char _SelTyp;
	long *_pIdent;
//-------GesamtKlassen-Sicherung--------------------
//---------Linien--------------------------
	long _ObjectsL;
	double _CumulL;
	double _MinL;
	double _MaxL;
	double _MedianL;
	double _MWertL;
//---------Flaechen------------------------
	long _ObjectsF;
	double _CumulF;
	double _MinF;
	double _MaxF;
	double _MedianF;
	double _MWertF;

//-----------Selektierte Klassen
	long _NumObjects;	// Count ONr
	double _SumObject;	// Cumul Wert
	double _Prozent;
	double _Minim;
	double _Maxim;
	double _Median;
	double _Mittelwert;
//------------ReferenzKlasse------------------
	long _BezNumObjects;	// Count ONr
	double _BezSumObject;	// Cumul Werte
	double _BezMinim;
	double _BezMaxim;
	double _BezMedian;
	double _BezMittelwert;
//--------------------------------------------
	char * _pEinheit;
	pWindow _pW;
	MultiSelListBox _ObjClassList;
	ComboBox _BezugsList;
//---------------------------------------------
	FixedText _ObjClassCount;
//----------------------------------------------------------
	FixedText _Objekte;
	FixedText _Minimum,_Maximum,_MedianWert,_MittelWert;
	FixedText _Summe,_Anteil;
//---------------------------------------------------------
	FixedText _BezObjekte;
	FixedText _BezMinimum,_BezMaximum,_BezMedianWert,_BezMittelWert;
	FixedText _BezSumme;
//----------------------------------------------------------
	CheckBox _BezugsBox;
	PushButton _PutClipBoard;
	PushButton CancelButton;
	ResourceFile &_RF;
	IDMTree *_pIDM;
	OBJTree *_pOBJ;
	long _OBJCount;

protected:
	void _XTENSN_EXPORT ButtonClick (ControlEvt e);
	void _XTENSN_EXPORT ListBoxSel (ControlEvt e);
	void _XTENSN_EXPORT ListBoxClk (ControlEvt e);


public:
		DataBaseObjClass (pWindow pW, uint res, ResourceFile &RF, short MFlag, IDMTree *pIDM, OBJCLList *pOCL, long *pMCode = NULL);
		~DataBaseObjClass (void);


// Memberfunktionen
	void BuildExtremum ( char * , struct GIEXTREMUM *);
	void AddCountObjClassTypes ( Bool, long , char * , struct GIEXTREMUM *);
	void FillObjKlassenList ( OBJCLList * );
	void LoadObjKlassenList ( short * );
	void KlassenAuswahl ( void );
	void BezugsKlassenAuswahl( void );
	void LoadBezugsWert ( char * TYP );
	void ShowCountObjects ( char * TYP );
	void ShowNoObjects ( void );
	void ShowNoBezugsKlasse ( void );
	void SelectIdents ( void );
	void CreateObjectTree ( OBJTree *pObj , char * Typ, IDGITYP *p);
	void ShowPBDText ( long, short );
	void ShowBezugsPBDText ( long, short);
	void PutIdentToClipBoard ( void );
	long SetIdent ( int);
};
//-----------------Nur fÅr uns ------------------------------------
//--------------------Objektnummer suchen -------------------------
//-----------------------------------------------------------------
// Anzeigen von Objekten einer Datenbank --------------------------
class DataBaseObject : public DialogWindow {
private:   
	NumEditX _Objekt;
	long _lONr;
	PushButton OKButton,CancelButton;
	pWindow _pW;
	ResourceFile &_RF;


protected:
	void _XTENSN_EXPORT ButtonClick (ControlEvt e);

public:
		DataBaseObject (pWindow pW, uint res, ResourceFile &RF );
		~DataBaseObject (void);


// Memberfunktionen
	long &Object ( void ) { return _lONr; };
};
//-----------------------------------------------------------------
#endif 	// _DBINFO_HXX
