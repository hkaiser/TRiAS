 // Definition von AuswahlModi ------------------------------------------------------
// File: KOMPSIMU.HXX

#if !defined(_KOMPSIMU_HXX)
#define _KOMPSIMU_HXX

// Definieren von GewKlassenUebersicht ---------------------
class SimuGewaesser : public DialogWindow {
private:
	ListBox _GewClass;
	ListBox _ZuoClass;
	bool _isValid;

	class KPTree *_pGew;
	class KPTree *_pNGew;
	FixedText _LenTRiAS;
	NumEditX _Von;
	NumEditX _Bis;
	int _iZ;
	int _iG;
	short _iB;
	PushButton OKButton, CancelButton, _ArchivButton;
	RadioButton _UButton, _AusButton,_AufButton,_AumButton;
	ResourceFile &_RF;

	pWindow _pW;

protected:
	void _XTENSN_EXPORT ButtonClick (ControlEvt);
	void _XTENSN_EXPORT ListBoxSel (ControlEvt e);


public:
		SimuGewaesser (pWindow pW, uint res, ResourceFile &RF, KPTree * pGew, KPTree *pNGew);
		~SimuGewaesser (void);

//Memberfunktionen
	bool isValid ( void ) { return _isValid; };
	Bool FillGewClassList (void);
	Bool FillZuoClassList (void);
};    
//-------------------------------------------------------------------------
// Definieren von Gewaesseramen ---------------------
class KompaktName : public DialogWindow {
private:
	bool _isValid;
	TxtEdit _KName;
	TxtEdit _KBezeichnung;
	FixedText _TName;
	FixedText _TBezeichnung;
	PushButton OKButton, CancelButton;
	ResourceFile &_RF;

	long _lONr;
	short _iTyp;
	short _iBTyp;

	pWindow _pW;
	char *_pName;
	char *_pBezeichnung;


protected:
	void _XTENSN_EXPORT ButtonClick (ControlEvt e);


public:
		KompaktName (pWindow pW, uint res, ResourceFile &RF, long lONr, short iTyp);
		~KompaktName (void);


//Memberfunktionen
	bool isValid ( void ) { return _isValid; };
	char *GetObjektName(void) {return _pName;};
	char *GetObjektBezeichnung(void) {return _pBezeichnung;};
	short BauwerkeKeyLen ( long);
	void SetKompaktName ( char * pName);
};  
  
// Definieren von Bauwerkenamen ---------------------
class EreignisName : public DialogWindow {
private:
	bool _isValid;

	ComboBox _NameClass;

	TxtEdit _KName;

	TxtEdit _KBezeichnung;
	FixedText _TName;
	FixedText _TBezeichnung;
	PushButton OKButton, CancelButton;
	ResourceFile &_RF;

	long _lONr;
	short _iTyp;
	short _iBTyp;
	short _iCount;

	pWindow _pW;
	char *_pName;
	char *_pBezeichnung;
	CKompaktDLL *_hLib;		// KompaktDLL

protected:
	void _XTENSN_EXPORT ButtonClick (ControlEvt e);
	void _XTENSN_EXPORT ListBoxSel (ControlEvt e);


public:
		EreignisName (pWindow pW, uint res, ResourceFile &RF, long lONr, short iTyp);
		~EreignisName (void);


//Memberfunktionen
	bool isValid ( void ) { return _isValid; };
	char *GetObjektName(void) {return _pName;};
	char *GetObjektBezeichnung(void) {return _pBezeichnung;};
	short BauwerkeKeyLen ( long);
	bool HoleKatalogVonKompakt ( short iTyp );
	bool FillKatalog(void);
	short GetKatalogCount(void) { return _iCount; };
};    
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
#endif	//KOMPSIMU.HXX

