// Anzeige diverser statistischer Informationen eines selktierten Objektes
// File: GEOSTAT.HXX

#if !defined(_GEOSTAT_HXX)
#define _GEOSTAT_HXX

#include <itriasap.h>
#include <triastlb.h>


class StatistExtension : public CTriasExtension {
private:

//-----------Basic-----------------------------
	IExtendBScript *m_pScript;
//-------------------------------------------
	_DDocument *m_pDoc;
	
	IExtendTopRel2 *m_pTop;
	IExtendObjOper * m_pObjOp;

	// Fuer Registrierung
	DWORD m_dFLM;		// Flaechenmass
	DWORD m_dLM;		// Laengenmass
	DWORD m_dON;		// Objektnummer-nur fr uns

	IDMTree *m_pIDM;		//	ID-Baum
	OBJTree *m_pOBJ;		//	Objectbaum
	SHWNDTree *m_pHWNDTree;		// 	HWND-Baum ( OR-Fenster)
	GICLATree *m_pGICLA;		//	GI-Classification
	OBJCLList *m_pOCL;		//	ObjClass-ListContainer
	class IdentInformation *m_pInfo;	// StatusFenster
	CoordTransX *m_pCTF;		// Koordinaten-CTF
	long *m_pClaObj;
	long * m_pIDC;
#if !defined(WIN32) 
	long __huge *m_pHUGE;
	short m_isHuge;
#endif
	long m_lRechMkode;
	long m_lRechKey;
	HWND m_hWnd;
	char * m_pEinheit;
	short m_ShowObjType;
	short m_isSightInfo;
	short m_isORHwnd;
	long m_iObjCount;
	short m_iRange;
	short m_isExtremum;
	short m_isBreak;

	ULONG m_iOPArea;		// RegistrierSchlüssel der OPFunc's
	ULONG m_iOPRange;		// FL_Umfang
	ULONG m_iOPBRange;		// FL_Umrandung
	ULONG m_iOPRadius;		// FL_Radius
	ULONG m_iOPDiff;		// FL_Differenz
	ULONG m_iOPLine;		// L_Laenge
	ULONG m_iOPRPointX;		// ReferenzPunktX
	ULONG m_iOPRPointY;		// ReferenzPunktY
	ULONG m_iOPRText;		// BegleitText
	ULONG m_iOPRSPointX;		// FlaechenSchwerPunktX
	ULONG m_iOPRSPointY;		// FlaechenSchwerPunktY
//
	ULONG m_iOPRObjekt;		// BegleitObjekt



//ZeitTest
	DWORD m_dStartTime;
	DWORD m_dStopTime;

//DBInfo-Fenster
	long m_lDBIdCount;
	short m_DBResult;

	CObjectProperties *m_pObjProp;

// Korrektur 02.02.99
	Menu *m_pPopupMenu;
	Menu *m_pPopupORMenu;
	
protected:

	STDMETHOD_(BOOL, InitExtension) (THIS_ short iMode);
	STDMETHOD_(BOOL, UnLoadExtension) (THIS);
	STDMETHOD_(BOOL, MenuInit) (THIS_ HMENU hMenu, LPARAM lParam, HWND hWnd);
	STDMETHOD_(BOOL, MenuSelect) (THIS_ UINT uiMenuID, HMENU hMenu, HWND hWnd);
	STDMETHOD_(BOOL, MenuCommand) (THIS_ UINT uiMenuID, HWND hWnd);
	STDMETHOD_(LRESULT, Notification) (THIS_ WPARAM wParam, LPARAM lParam);

public:
// Konstruktor / Destruktor
		StatistExtension (void);
		~StatistExtension (void);


// *** IUnknown methods
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj);


// Memberfunktionen
// Interface-STATIFCE
	void ReleaseInterface(void);
	bool GetGeoObjectFromONr ( long, _DGeoObject **);
	bool LadeBasicScript(void);
	bool LadeBasicDocument(void);
	bool LadeTopRel(void);
	bool LadeObjOp (void);
	void LoescheStatistikFlaechen(void);
//
	Bool HideSightInfo ( void );
	void AddORHwnd ( void );
	void DeleteORHwnd ( void );
	Bool HideORHwnd ( void );
	short isORHwnd ( void ) { return m_isORHwnd; };
	void SichtInfo ( void );
	void SichtAusschnitt ( short );
	void SichtGeometrieKlasse ( void );
	void CreateORWindow ( short, short, short, long *, char *, short, short, short );
	Bool ShowClassification ( void );
	char * MittelWert ( void );
	char * MedianWert ( void);
//___________________NEU_____________________________
	Bool GetObjectTypes ( LPARAM p );
	void GetFL_ObjectsFromORWindow ( Bool fGenerate, HWND hWnd );
	void GetFL_ObjectsFromAllORWindow ( Bool fGenerate );
	void CreateObjClassFromObjects ( short Typ );
	Bool ShowDataBaseInfo ( void );
	Bool BuildObjClassInfo( short );
	Bool BuildObjClassContainer( void );
	void StoreObjTree ( long Ident, OBJTree *pObj);
	void ShowObjectClassInformation ( short Typ);
	void SetTreeInformation ( void );
	pWindow GetRightpWindow ( short Typ);
	CoordTransX *MyCTF ( void){ return m_pCTF; };
	IExtendTopRel2 *MyTop ( void) { return m_pTop; };
	IExtendObjOper *MyObjOp ( void) { return m_pObjOp; };

	DWORD FLM ( void ) { return m_dFLM; };
	DWORD LM ( void ) { return m_dLM; };
//-------------Nur für uns----------------------------------
	bool ObjektTest ( void );
//----------------------------------------------------------

// Funktionen für ObjProperties
	ULONG AddPropertyFunction (LPCSTR pFName, OBJPROPCALLBACK pFunc, DWORD dwFlags = PROPCAPS_OBJPROPTYPE_STRING)
		{ return m_pObjProp -> AddPropertyFunction (pFName, pFunc, dwFlags); }
	ULONG AddPropertyFunctionEx (LPCSTR pFName, OBJPROPEXCALLBACK pFunc,
			     DWORD dwData, OBJPROPDELCALLBACK pDelF = NULL, DWORD dwFlags = PROPCAPS_OBJPROPTYPE_STRING)
		{ return m_pObjProp -> AddPropertyFunctionEx (pFName, pFunc, dwData, pDelF,dwFlags ); }

// Freigeben einer/aller OPFs
	bool RemovePropertyFunction (ULONG ulFuncID)
		{ return m_pObjProp -> RemovePropertyFunction (ulFuncID); }

// Korrektur 02.02.99
	bool InstallPopupMenu (int iIndex);
	bool InstallPopupORMenu (int iIndex);
	void RemovePopupMenus();
	void RemovePopupORMenus();
	bool FindMenuItem (HMENU hMenu, UINT uiID);


};

#endif 	// _GEOSTAT_HXX
