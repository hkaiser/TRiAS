// Klassendeklarationen fÅr Ausgebeformen in CLIPBOARD
// File: SCLIPBRD.HXX

#if !defined(_SCLIPBRD_HXX)
#define _SCLIPBRD_HXX

// Verwaltung  Identifikator
class GlobalObjClass {
private:
	char * _pText;	// öberschrift
	long _lMCode;
	ResourceFile *_pResF;
	unsigned short *_pParam;
	short _iIdTyp;
	short _MFlag;

	long _KeyNr;	// Zeilenz‰hler- Zaehler Idents...

	long _Count;
//	Kumulativ - Okl-Typen
	long _PCount;
	long _LCount;
	long _FCount;
	long _TCount;
	long _SCount;

	double _SFlInhalt;
	double _SLinLaenge;
	double _SMinL;
	double _SMinF;
	double _SMaxL;
	double _SMaxF;

// Zaehlen der Eintraege
	long _EintragP;
	long _EintragL;
	long _EintragF;
	long _EintragT;
	long _EintragS;

	long _EintragFlaeche;
	long _EintragLaenge;
	long _EintragMinL;
	long _EintragMinF;
	long _EintragMaxL;
	long _EintragMaxF;

	long _EintragAML;
	long _EintragAMF;
	long _EintragMedL;
	long _EintragMedF;
//-----------------------------------------
	IDMTree *_pIDM;
	GICLATree * _pGICLA;
	OBJTree *_pObj;
	short _Typ;
	double _VglWert1;
	double _VglWert2;
	double _rGlobalWert;

public:
// Konstruktor/Destruktor
		GlobalObjClass ( ResourceFile *pResF, short MFlag, long MCode, void *pData , short Typ, unsigned short *pParam, short iIdTyp);
		~GlobalObjClass (void);

// Memberfunktionen
	char * GetCaption ( void );
	char * GetText ( long Key , bool flag);  
	char * GetCumulate ( void );
	char * GetEintrag ( void );
	void GetIDValue ( long, IDGITYP *);
	void GetGIValue ( long, IDGITYP *);
	void SetGlobalWert( double);
};

//-----------------DialogFenster zum Zusammenstellen der Parameter------
// Parameter fÅr Zwischenablage ---------------------
class ClipBoardClass : public DialogWindow {
private:   

	short _CountParm;
	short _CountSel;
	pWindow _pW;
	int *_pIndex;
	int *_pSelIndex;
	unsigned short *_pResParm;
	unsigned short *_pResHelp;
	unsigned short *_pParam;
	class CHelpTextX *_pHelpText;
	MultiSelListBox _ObjClassList;
//----------------------------------------------------------
	CheckBox _Ueberschrift,_OKLEigenschaft,_KumulIndex,_AnzahlEintrag;
	PushButton OKButton,CancelButton,_ReihenFolge;
	ResourceFile &_RF;
	short _Typ;

protected:
	void _XTENSN_EXPORT ButtonClick (ControlEvt e);
	void _XTENSN_EXPORT ListBoxSel (ControlEvt e);
	void _XTENSN_EXPORT ListBoxClk (ControlEvt e);


public:
		ClipBoardClass (pWindow pW, uint res, ResourceFile &RF, short Typ, unsigned short *pParam);
		~ClipBoardClass (void);


// Memberfunktionen
	void FillParameterList ( void );
	void StoreParameter ( unsigned short, unsigned short );
	void ParameterAuswahl( void );
	bool Ueberschrift_isChecked( void ) { return _Ueberschrift.isChecked(); }
	bool Kumulativ_isChecked( void ) { return _KumulIndex.isChecked(); }
	bool Eigenschaft_isChecked( void ) { return _OKLEigenschaft.isChecked(); }
	bool Eintrag_isChecked( void ) { return _AnzahlEintrag.isChecked(); }
};

//------------DialogFenster zum Sortieren der Reihenfolge der Parameter---
// Sortieren der Parameter fÅr Zwischenablage ---------------------
class ParameterSort : public DialogWindow {
private:   

	short _Count;
	int _iParmIndex;
	pWindow _pW;
	int *_pSelIndex;
	unsigned short *_pResParm;
	ListBox _ParmList;
//----------------------------------------------------------
	PushButton OKButton,CancelButton,_Plus,_Minus,_Hilfe;
	ResourceFile &_RF;

protected:
	void _XTENSN_EXPORT ButtonClick (ControlEvt e);
	void _XTENSN_EXPORT ListBoxSel (ControlEvt e);
	void _XTENSN_EXPORT ListBoxClk (ControlEvt e);


public:
		ParameterSort (pWindow pW, uint res, ResourceFile &RF, short Count, int *pIndex, unsigned short *pRefParm);
		~ParameterSort (void);


// Memberfunktionen
	void FillParameterList ( void );
	void SortPosition ( bool);
};


#endif //	SCLIPBRD.HXX
