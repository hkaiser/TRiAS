// Definition KOMPAKT- DLL ---------------------------------
// File: KOMPDLL.HXX

#if !defined(_KOMPDLL_HXX)
#define _KOMPDLL_HXX


class CKompaktDLL : public CDllBindX {
public:
	short _isValid;
	short _iOperation;

	CKompaktDLL (DWORD p, HWND hWnd, const char *pLibrary);
	~CKompaktDLL (void);

	bool IGMMenuCommand (short, HWND);
//	bool KompaktMenuCommand (short, HWND);
	bool IGMEinzelGewaesser ( HWND, char *);
//	bool KompaktEinzelGewaesser ( HWND, char *);
	bool KompaktObjektEigenschaft ( HWND, BAUWERKE *);
	bool KompaktDatenPfad (char *);
	long GewaesserKatasterLaengeHolen ( char *, long, long);
	bool GewaesserStrukturSetzen ( GEWAESSER *);
	bool GewaesserStrukturHolen ( GEWAESSER *);
	long GewaesserNeueLaenge ( char *,long);
	bool GewaesserNeuAnlegen ( char *,char *, long);
	char *GewaesserNameHolen ( char *);
	bool EnumeriereLeistung ( short, LEISTUNGPROC, DWORD);
	bool EnumeriereBauwerke ( short, BAUWERKEPROC, DWORD);
	bool EnumeriereGewaesser ( short, GEWAESSERPROC, DWORD);
	bool EnumeriereKompaktKatalog ( short, KOMPAKTKATALOGPROC, DWORD);
	short isValid ( void ) { return _isValid;};
	short Operation ( void ) { return _iOperation;};
	void SetOperation ( bool iOp) { _iOperation = iOp;};
	bool BemerkungenBauwerkGewaesserEinAus(int);
};

#endif // _KOMPDLL_HXX
