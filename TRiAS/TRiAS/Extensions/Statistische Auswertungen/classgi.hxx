// Identifikator-šbersicht ------------------------------------------------------
// File: CLASSGI.HXX

#if !defined(_CLASSGI_HXX)
#define _CLASSGI_HXX


// Anzeigen von speziellen Objekten nach Fl'gr”áe bzw. Linienl„nge in einer Sicht ---------------------
class ObjectClassification : public DialogWindow {
private:

        class CHelpTextX *_pHelpText;	//HILFE

	short _isObjectFound;
	short _iOklGiTyp;
	short _iMETyp;		//	MassEinheitenTyp;

	double _MinWert;
	double _MaxWert;
	double _MinVglWert;
	double _MaxVglWert;

	PushButton OKButton, CancelButton;
	RadioButton _EinzelButton,_IntervallButton;

	ResourceFile &_RF;

	pWindow _pW;
	
	FixedText _ElementeTyp;
	FixedText _ElementeZahl;

	DoubleNumEditX _VerglWertMin;
	DoubleNumEditX _VerglWertMax;
	DoubleNumEditX _IntervallWert;
	FixedText _IntervallText;
	FixedText _ObjektKlasse; 

	ComboBox _ObjClassList;
	ComboBox _MathOpListOne;
	ComboBox _MathOpListTwo;
	ComboBox _MassEinhList;

	IDMTree *_pIDM;
	OBJTree *_pOBJ;
	GICLATree *_pGICLA;
	long *_pClaObj;

	long _Einheit;
	long _Operat1;
	long _Operat2;
	long _ObjKlasse;
	double _Wert;
	char _WERT [35];

//--------------------------------------                      
	Bool _GiTyp;
	long _Number;
//--------------------------------------------------

protected:
	void _XTENSN_EXPORT ButtonClick (ControlEvt);

	void _XTENSN_EXPORT ListBoxSel (ControlEvt);
	void _XTENSN_EXPORT ListBoxClk (ControlEvt);

public:
		ObjectClassification (pWindow, uint res, ResourceFile &RF, IDMTree *pIDM, OBJTree *pOBJ, GICLATree *pGICLA );
		~ObjectClassification (void);

//Memberfunktionen
		double GetVerglWert ( void ){ return _Wert; };
		long GetEinheit ( void ){ return _Einheit; };
		long GetObjNumber ( void ){ return _Number; };
		long GetObjKlasse ( void ){ return _ObjKlasse; };
		Bool GetGiTyp ( void ){ return _GiTyp; };
		Bool isObjectFound ( void ){ return _isObjectFound; };
		long GetObjClass ( void );
		long GetFirstObjClass ( void );
		void SetObjClass ( double *, double * );
		void DefineObjClass ( void );
		long GetMathOp ( void *);
		long GetMassEinheit ( void );
		void FillObjKlassenList ( void );
		void FillMathOpList ( int, void * );
		void SetStandardMathOp ( Bool );
		Bool isLinie ( void );
		Bool isFlaeche ( void );
		void FlaechenMassEinhListe ( void );
		void LinienMassEinhListe ( void );
		int DefineMinMaxZeile ( void );
		short MassEinheit ( void ) { return _iMETyp; };
		long GetExtrema ( double *, double * );
		Bool BuildIntervall ( void );
		void SaveIntervallWert ( void );
		void SaveVergleichsWert ( void );
		long *GetGIClassObjects ( void ) { return _pClaObj; };
		void TestVergleichsWert ( void );
		void DeleteClassification( void );
		Bool isWertDeleted( char *pWert );
		Bool isClassification (void);
		void ShowPBDText ( long, short );
		void PruefeEinzelAbfrage ( void );
		void DuplicateObject (long ON, OBJTree * pIdOBJ, OBJTree *pObj);
};
#endif 	// _CLASSGI_HXX


