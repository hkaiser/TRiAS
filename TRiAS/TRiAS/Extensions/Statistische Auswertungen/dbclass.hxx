// Klassen-Übersicht ------------------------------------------------------
// File: DBCLASS.HXX

#if !defined(_DBCLASS_HXX)
#define _DBCLASS_HXX

// Anzeigen von Objektklassen -----------------------------------------
class DBClassification : public DialogWindow {
private:   
	
        class CHelpTextX *_pHelpText;	//HILFE
	class OBJCLList *_pOCL;	// ListContainer sel. OKL
	class CoordTransX *_pCTF;	// KoordinatenTransf.
//
	MultiSelListBox _ObjClassList;
	ComboBox _MerkmalList;
//
	PushButton _PutClipBoard;
	PushButton _Details,_Schliessen,_AlleKlassen,_Anzeigen;

	CheckBox _ObjektEigenschaften,_MerkmalAnzeige;
	RadioButton _EinschlMerkmal,_AusschlMerkmal;

	FixedText _ObjektKlassen;
	FixedText _LoHochWert;
	FixedText _LoRechtsWert;
	FixedText _RuHochWert;
	FixedText _RuRechtsWert;
//
	FixedText _FlaechenInhalt;
	FixedText _FlaechenMass;
	FixedText _LinienLaenge;
	FixedText _LinienMass;
//
	FixedText _Objekte;
	CheckBox _Punkte,_Linien,_Flaechen,_Texte,_Sonstige;
//
	ResourceFile &_RF;
	IDMTree *_pIDM;
	OBJTree *_pOBJ;
	GICLATree *_pGICLA;
	long *_pIDC;

#if !defined(WIN32)
	long __huge *_pHUGE;	// für große
	short _isHuge;
#endif

	class IdentInformation *_pInfoBox;
	short _isShowInfoBox;
	short _isBreak;
	pWindow _pW;
	long _MKode;
	long _LastIdent;
	long _LastMkode;

	int _isHelpText;

	short _IdentBase;
	short _ObjRecherche;
	short _isDetails;
	long _lRange;
	short _ShowObjTyp;
	short _OKlTyp;		// ObjektKlassenTypArten
	long _KooCont[4];

//---------------------------------------------------------------------
	long _NumObject;
	long _NumIdent;
	short _iIdTyp;
	short _isMKModified;	//	MK-RechercheWechsel
	long _DBKooCont[4];
	long _SightCont[4];
	int _isIDLIST;
// Für ClipBoard
	bool _isClipUeberschrift;
	bool _isClipKumulativ;
	bool _isClipEintrag;
	bool _isClipEigenschaft;



protected:
	void _XTENSN_EXPORT ButtonClick (ControlEvt e);
	void _XTENSN_EXPORT ListBoxSel (ControlEvt e);
	void _XTENSN_EXPORT ListBoxClk (ControlEvt e);


public:                           
	
		DBClassification (pWindow pW, uint res, ResourceFile &RF, CoordTransX *pCTF, char *pCaption, void *pData1 , short iSightInfo, void* pData2);
		~DBClassification (void);

// Memberfunktionen
	Bool SetKoord ( void );
	void SetNoMetric ( void );
	void FillMerkmalList ( void );
	void FillObjKlassenList ( short Flag, char * pSightName );
	long SetAllObjClass ( void );
	void SetObjTyp ( short Typ );
	void DelObjTyp ( short Typ );
	void DefineMwertAnzeige ( void );
	long AnalysObjProp ( void );
	long DefineMwertButton ( void );
	long DefineInvMwertButton ( void );
	long AnalysObjClass ( void );
	long AnalysObjEig ( void );
	long *GetObjListe ( void ) { return _pIDC; };


//
	void ShowObjects ( struct IDGITYP *);
	void AnalysIDListBox ( long MKode );
	long NumberObjects ( void ){ return _NumObject; };
	long GetMKode ( void ) { return _MKode; };
	long *GetStaCont ( void ) { return &_DBKooCont[0]; };
	Bool ShowMKWert ( void ) ;
	long SetMKode ( void );
	long SetIdent ( int iIndex );
	long SetGIIdent ( int iIndex );
	short GetIdentBase( void ) { return _IdentBase; };
	short GetShowObjTyp ( void ) { return _ShowObjTyp; };
	void AddIdentinTree ( long Ident , struct IDGITYP * );
	Bool FindIntervall ( long *pIdent , struct IDGITYP * );
	void ShowPBDText ( long Key, short TCode);
	void ShowGIKlassText ( long Key );
	Bool ModifyGIKlassList ( void );
	int isHelpText ( void ) { return _isHelpText ; };
	void SetHelpText ( int );
	void PutIdentToClipBoard ( void );
	void PutGIClassToClipBoard ( void );
//-----------------NEU-----------------------------------
	void SetStandardInformation ( void );
	void GetObjClassContainer ( void );
	void AddCountObjTypes ( long *pKey, struct IDGITYP * );
	void ClearObjectInformation ( void );
	void FindAllObjects ( bool iall ,long Key );
	long CountObjects( long*, long*, short* );
	void LoadObjectVector( void );
	void LoadGIVector( long );
	void LoadObjectClassList( void );
	void LoescheClickInObjList ( long );
	void IdentInListBox ( long Ident );
	Bool isDefinedMCLine ( char * );
	Bool isDefinedMCArea ( char * );
	void EnumeriereObjekte ( long Ident, struct IDGITYP *);
//	void FindeNurObjekte(long Ident);
	void KillIdent(void);
#if !defined(WIN32)
	long *GetHugeObjListe ( void ) { return _pHUGE; };
	short isHuge (void) { return _isHuge; };
#endif
};
#endif 	// _DBCLASS_HXX


