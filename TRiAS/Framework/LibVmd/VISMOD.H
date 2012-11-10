#ifndef	__TRIASVISMODULE_H__
#define	__TRIASVISMODULE_H__

#undef  INTERFACE
#define INTERFACE IVisModule

// Datentypen für Notifikationen ----------------------------------------------
typedef enum tagPROJECTCHANGE {
	PROJECTCHANGE_OPENED = 0,	// neues Projekt geöffnet
	PROJECTCHANGE_CLOSED = 1,	// Projekt geschlossen
} PROJECTCHANGE;

typedef enum tagVIEWCHANGE {
	VIEWCHANGE_SELECTED = 0,	// neue Sicht ausgewählt
	VIEWCHANGE_DELETED = 1,		// Sicht gelöscht
} VIEWCHANGE;

DECLARE_INTERFACE_(IVisModule, IUnknown)
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
	STDMETHOD_(ULONG,Release) (THIS) PURE;

// *** Own Methods ***
	STDMETHOD(QueryParameters) (THIS_ HWND hWnd, long lONr, 
				    class VisInfo *pVI, char *pVisStr,
				    char *pBuffer, short iLen, short *piOTypes) PURE;
	STDMETHOD(SymbolizeObject) (THIS_ HWND hWnd, long &rlONr, short &iOType,
				    char *pBuffer, short iLen) PURE;
	STDMETHOD(DrawObject) (THIS_ HWND hWnd, HDC hDC, HDC hTargetDC, 
			       long lONr, short &fDrawFlags, 
			       class VisInfo *pVI, char *pVisString) PURE;
	STDMETHOD_(void,OnProjectChange)(THIS_ HWND hWndM, PROJECTCHANGE rgPC, 
					 char *pPrName) PURE;
	STDMETHOD_(void,OnViewChange)(THIS_ HWND hWndM, VIEWCHANGE rgVC, 
				      char *pView) PURE;
	STDMETHOD_(void,OnPaletteChange)(THIS_ HWND hWndM, HPALETTE hPal) PURE;
};
typedef IVisModule * LPVISMODULE;

// neue FehlerCodes -----------------------------------------------------------
// IVisModule :: DrawObject
#define VISMODULE_E_GENERALERROR	MAKE_SCODE(SEVERITY_ERROR, FACILITY_NULL, 1)
#define VISMODULE_E_BADOBJECTTYPE	MAKE_SCODE(SEVERITY_ERROR, FACILITY_NULL, 2)

#define VISMODULE_S_DRAWOBJECT		MAKE_SCODE(SEVERITY_SUCCESS, FACILITY_ITF, 1)
#define VISMODULE_S_OBJECTISDRAWN	MAKE_SCODE(SEVERITY_SUCCESS, FACILITY_ITF, 2)
#define VISMODULE_S_ANALYZEONLY		MAKE_SCODE(SEVERITY_SUCCESS, FACILITY_ITF, 3)

/****************************************************************************
 *	CTriasVisModule bzw. die davon abgeleitete Klasse ist das eigentliche
 *	Arbeitstier im Visualisierungsmodul.
 ****************************************************************************/

#ifdef WIN32
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

extern "C" LRESULT PASCAL DexExtensionProc (WPARAM w, LPARAM l);
extern "C" LRESULT PASCAL DexExtensionProc2 (HPROJECT hPr, WPARAM w, LPARAM l);

class CTRiASVMDModule : public COleControlModule {
	CString	m_strTRiASIni;
public:
	BOOL	InitInstance();
	int		ExitInstance();
	void GetTRiASIni( CString& strTRiASIni ) {
		strTRiASIni = m_strTRiASIni;
	}
};

class	CTriasVMD : public COleControl {
	CWnd	m_CWnd;
	CDC		m_dcDraw;
	CDC		m_dcTarget;
//	BOOL	m_bObjectIsValid;
	BOOL	m_bProjIsOpen;
	BOOL	m_bViewIsOpen;
	BOOL	m_bPalIsRealized;

// KK010105
	HPROJECT m_hPr;		// aktuelle Datenquelle

	DECLARE_DYNAMIC( CTriasVMD )
protected:
	// Damit mit TRIAS(R) überhaupt was läuft...
	HWND	__hWndM;

	// projektübergreifend

	BOOL		m_bAdminMode;		// sind wir im Administartor - Modus?
	BOOL		m_bReadOnly;		// Projekt ist schreibgeschützt

	// Projektspezifisch ( OnProjectChange ... )
	CString		m_strCurrProj;		// Pfadname aktuelles Projekt
//	CString		m_strCurrProjIni;	// Pfandname aktuelle Initialisierungsdatei
	short		m_nIdentBase;		// Zahlenbasis für Identifikatoren
	short		m_nMCodeBase;		// dito f. Merkmalscodes
//	long		m_lUniqueIdent;		// eindeutiger Identifikator
//	long		m_lTextObjMCode;	// Merkmalscode für Textojekte
	
	// Sichtspezifisch ( OnViewChange ... )
	CString		m_strCurrView;		// Name der aktuellen Sicht

	// für das aktuelle Zeichnen
	double		m_activeZoom;		// aktueller Darstellungsmaßstab
	double		m_activeScaling;	// Verhältnis akt. Maßstab zu Bezugsmaßstab

protected:
	virtual HRESULT GetClassID( LPCLSID pClsid ) = 0;
	virtual UINT GetUserTypeNameID() = 0;
	virtual DWORD GetMiscStatus() = 0;

	virtual LPCTSTR GetProgIdent() = 0;		// liefert ProgIdent "TRiAS.VM...."

protected:
	CTriasVMD( );
	virtual	~CTriasVMD( );

private:
	void		SetHandle( HWND hWnd );
	HPALETTE	GetActivePalette( );

	///////////////////////////////////////////////////////////////////////
	// Für das Debugging ist es günstig, wenn immer wieder derselbe
	// Fensteraufbau wie bei der letzten Sitzung hergestellt wird
	
	void SaveWindowState( HWND hWndM );
	void LoadWindowState( HWND hWndM );

	///////////////////////////////////////////////////////////////////////
	// die abgeleitete Klasse muß alle Aufrufe an ihr IVismodule-Interface
	// in die folgenden Funktionen delegieren, da hier 'ne Menge an 
	// Verwaltungsarbeit erledigt wird
	// von hier aus werden dann die eigentlichten Arbeitstiere gerufen...

protected:
	STDMETHOD(QueryParameters) (THIS_ HWND hWnd, long lONr, class VisInfo *pVI, char *pVisStr, char *pBuffer, short iLen, short *piOTypes);
	STDMETHOD(SymbolizeObject) (THIS_ HWND hWnd, long &rlONr, short &iOType, char *pBuffer, short iLen);
	STDMETHOD(DrawObject) (THIS_ HWND hWnd, HDC hDC, HDC hTargetDC, long lONr, short &fDrawFlags, class VisInfo *pVI, char *pVisString);
	STDMETHOD_(void,OnProjectChange)(THIS_ HWND hWndM, PROJECTCHANGE rgPC, char *pPrName);
	STDMETHOD_(void,OnViewChange)(THIS_ HWND hWndM, VIEWCHANGE rgVC, char *pView);
	STDMETHOD_(void,OnPaletteChange)(THIS_ HWND hWndM, HPALETTE hPal);

	///////////////////////////////////////////////////////////////////////
	// ...die hier wie folgt definiert sind
	// - es ist wichtig (!!!), daß immer zuerst die Funktion der Basisklasse
	//   gerufen, und dann die eigene Arbeit erledigt wird
	// - die pur-virtuellen Funktionen bewirken, daß CTriasVMD nie instanziiert
	//   werden kann; zugleich sind sie die mindestens zu implementierenden
	//   Funktionen in einem Visualisierungsmodul

	virtual	void	DeleteContents( );

	virtual	BOOL	OnProjectOpen( LPCTSTR pszNewProject );
	virtual	void	OnProjectClose( );
	virtual	BOOL	OnViewOpen( LPCTSTR pszView );
	virtual	void	OnViewClose( );

	virtual	BOOL	OnChangePalette( CDC *pDC, HPALETTE hPal ) = 0;
	virtual	BOOL	OnQueryParameters(
						CWnd *pParentWnd,
						const DWORD lONr, 
						class VisInfo * pVI, 
						LPCTSTR pszVisStr, 
						LPSTR pBuffer, 
						short iLen,
						short * piOTypes) = 0;
	virtual	BOOL	OnDrawObject(
						CDC *pDC,
						CDC *pTarget,
						const DWORD lObjNr, 
						class VisInfo* pVI, 
						LPCTSTR pszVisString, 
						short& fDrawFlags ) = 0;

	///////////////////////////////////////////////////////////////////
	// allgemeine Hilfsfunktionen, die uns das Leben erleichtern :-)
protected:
	int		GetRegistryValue( LPCTSTR lpszKey, COleVariant& val );
	// Zugriff auf Profilestrings in PROJEKTSPEZIFISCHER (!!!) .ini
//	CString	GetProfileString(LPCSTR lpszSection, LPCSTR lpszEntry, LPCSTR lpszDefault = NULL );
//	BOOL	WriteProfileString(LPCSTR lpszSection, LPCSTR lpszEntry, LPCSTR lpszValue);
//	UINT	GetProfileInt(LPCSTR lpszSection, LPCSTR lpszEntry, int nDefault = 0 );
//	BOOL	WriteProfileInt(LPCSTR lpszSection, LPCSTR lpszEntry, int nValue );
//	void	ClearIniSection(LPCSTR lpszSection );
// KK010105
	CString	GetProfileString(HPROJECT hPr, LPCSTR lpszSection, LPCSTR lpszEntry, LPCSTR lpszDefault = NULL );
	BOOL	WriteProfileString(HPROJECT hPr,LPCSTR lpszSection, LPCSTR lpszEntry, LPCSTR lpszValue);
	UINT	GetProfileInt(HPROJECT hPr,LPCSTR lpszSection, LPCSTR lpszEntry, int nDefault = 0 );
	BOOL	WriteProfileInt(HPROJECT hPr,LPCSTR lpszSection, LPCSTR lpszEntry, int nValue );
	void	ClearIniSection(HPROJECT hPr,LPCSTR lpszSection );

public:
	// Zugriff auf Geo-DB-Header
	static BOOL	GetGeoDBEntry( HPROJECT hPr,LPCTSTR pszKey, CString& rValue );
	static BOOL	SetGeoDBEntry( HPROJECT hPr,LPCTSTR pszKey, LPCTSTR pszValue );
	static BOOL	GetGeoDBEntry( HPROJECT hPr,UINT iResrcID, CString& rValue );			// Schlüsselwerte aus Ressource
	static BOOL	SetGeoDBEntry( HPROJECT hPr,UINT iResrcID, LPCTSTR pszValue );

protected:
	// Zugriff auf PBD
	ULONG	GetUniqueIdent( void );
	ULONG	GetUniqueMCode( void );

	// Merkmalscodes
	BOOL	GetMCodeDescription( ULONG MCode, CString& rShort, CString& rLong  );
	BOOL	SetMCodeDescription( ULONG MCode, LPCTSTR pszShort, LPCTSTR pszLong, int iMCodeType = MPObjectFeature );
	BOOL	SetMCodeDescription( ULONG MCode, UINT nShortResrcID, UINT nLongResrcID, int iMCodeType = MPObjectFeature );

	BOOL	GetUniqueIdentMCode( ULONG& rlMCode );
	BOOL	GetUniqueIdentValue( ULONG lObjNr, CString& rValue );
	BOOL	GetMCodeValue( ULONG lObjNr, ULONG MCode, CString& rValue, short tType = TT_Objekt );		// Objekte / Identifikatoren 
	BOOL	GetMCodeValue( LPCTSTR pszViewName, ULONG MCode, CString& rValue );						// Sichten
	BOOL	SetMCodeValue( ULONG lObjNr, ULONG MCode, LPCTSTR pszValue, short strgLen = -1, short tType = TT_Objekt );
	BOOL	SetMCodeValue( LPCTSTR pszViewName, ULONG MCode, LPCTSTR pszValue, short strgLen = -1 );

// Message maps
	//{{AFX_MSG(CTriasVMD)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

//	LRESULT	RegisterNotification (UINT wMsg, Bool isLocal); 
//	LRESULT	UnRegisterNotification (UINT wMsg, Bool isLocal);
};

extern BOOL VMDRegister(HINSTANCE hInstance, REFCLSID rclsid, LPCTSTR lpszProgID, LPCTSTR lpszLongName, DWORD dwObjTypes);
extern BOOL VMDUnRegister(REFCLSID rclsid, LPCTSTR lpszProgID);

#define DECLARE_VISMOD_INTERFACE() \
	BEGIN_INTERFACE_PART(CVismodule, IVisModule) \
		STDMETHOD(QueryParameters) (THIS_ HWND hWnd, long lONr, class VisInfo *pVI, char *pVisStr, char *pBuffer, short iLen, short *piOTypes); \
		STDMETHOD(SymbolizeObject) (THIS_ HWND hWnd, long &rlONr, short &iOType, char *pBuffer, short iLen); \
		STDMETHOD(DrawObject) (THIS_ HWND hWnd, HDC hDC, HDC hTargetDC, long lONr, short &fDrawFlags, class VisInfo *pVI, char *pVisString); \
		STDMETHOD_(void,OnProjectChange)(THIS_ HWND hWndM, PROJECTCHANGE rgPC, char *pPrName); \
		STDMETHOD_(void,OnViewChange)(THIS_ HWND hWndM, VIEWCHANGE rgVC, char *pView); \
		STDMETHOD_(void,OnPaletteChange)(THIS_ HWND hWndM, HPALETTE hPal); \
    END_INTERFACE_PART(CVismodule)

#define IMPLEMENT_VISMOD_INTERFACE(class_name) \
	STDMETHODIMP_(ULONG) class_name::XCVismodule::AddRef (void) \
	{ METHOD_MANAGE_STATE(class_name, CVismodule); return pThis->ExternalAddRef(); } \
	STDMETHODIMP_(ULONG) class_name::XCVismodule::Release (void) \
	{ METHOD_MANAGE_STATE(class_name, CVismodule); return pThis->ExternalRelease(); } \
	STDMETHODIMP class_name::XCVismodule::QueryInterface (REFIID iid, LPVOID *ppvObj) \
	{ METHOD_MANAGE_STATE(class_name, CVismodule); return (HRESULT)pThis->ExternalQueryInterface(&iid, ppvObj); } \
	STDMETHODIMP class_name::XCVismodule::SymbolizeObject (THIS_ HWND hWndM, long &rlONr, short &riOType, char *pBuffer, short iLen) \
	{ METHOD_MANAGE_STATE(class_name, CVismodule); return pThis->SymbolizeObject (hWndM, rlONr, riOType, pBuffer, iLen); } \
	STDMETHODIMP class_name::XCVismodule::DrawObject (THIS_ HWND hWndM, HDC hDC, HDC hTargetDC, long lONr, short &rfDrawFlags, class VisInfo *pVI, char *pVisString) \
	{ METHOD_MANAGE_STATE(class_name, CVismodule); return pThis->DrawObject(hWndM, hDC, hTargetDC, lONr, rfDrawFlags, pVI, pVisString); } \
	STDMETHODIMP class_name::XCVismodule::QueryParameters (HWND hWndM, long lONr, class VisInfo *pVI, char *pVisStr, char *pBuffer, short iLen, short *piOTypes) \
	{ METHOD_MANAGE_STATE(class_name, CVismodule); return pThis->QueryParameters(hWndM, lONr, pVI, pVisStr, pBuffer, iLen, piOTypes); } \
	STDMETHODIMP_(void) class_name::XCVismodule::OnProjectChange (HWND hWndM, PROJECTCHANGE rgPC, char *pPrName) \
	{ METHOD_MANAGE_STATE(class_name, CVismodule); pThis->OnProjectChange(hWndM, rgPC, pPrName); } \
	STDMETHODIMP_(void) class_name::XCVismodule::OnViewChange (HWND hWndM, VIEWCHANGE rgVC, char *pView) \
	{ METHOD_MANAGE_STATE(class_name, CVismodule); pThis->OnViewChange(hWndM, rgVC, pView); } \
	STDMETHODIMP_(void) class_name::XCVismodule::OnPaletteChange (HWND hWndM, HPALETTE hPal) \
	{ METHOD_MANAGE_STATE(class_name, CVismodule); pThis->OnPaletteChange(hWndM, hPal); }

#define INTERFACE_MAP_VISMODULE(class_name) \
	INTERFACE_PART(class_name, IID_IVisModule, CVismodule)

///////////////////////////////////////////////////////////////////////
// Speicherüberwachung

#ifdef _DEBUG
#define	MEM_STARTCHECK( msg1, msg2 ) \
	CMemoryState oldMemState, newMemState, diffMemState; \
	oldMemState.Checkpoint()
#else
#define	MEM_STARTCHECK
#endif

#ifdef _DEBUG
#define	MEM_CHECKPOINT(msg1, msg2) \
    newMemState.Checkpoint(); \
    if( diffMemState.Difference( oldMemState, newMemState ) ) \
    { \
		TRACE( "----Memory leaked: [%s][%s][%s]\n", THIS_FILE, msg1, msg2 ); \
		diffMemState.DumpStatistics(); \
		TRACE( "----\n" ); \
    }
#else
#define	MEM_CHECKPOINT(msg1, msg2)
#endif

///////////////////////////////////////////////////////////////////////
// Bibliotheksversion

#if defined(_DEBUG)
	#define THIS_LIB "libvmdd.lib"
#elif defined(_RDEBUG)
	#define THIS_LIB "libvmdr.lib"
#else
	#define THIS_LIB "libvmd.lib"
#endif

#define IMPORT_THIS_LIB THIS_LIB
#pragma comment( lib, IMPORT_THIS_LIB )

///////////////////////////////////////////////////////////////////////
// Inlines...

#ifdef	_AFX_ENABLE_INLINES
#define	_VMD_INLINE	inline
#include	"vismod.inl"
#endif

#ifdef WIN32
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR
#endif

#endif	// __TRIASVISMODULE_H__
