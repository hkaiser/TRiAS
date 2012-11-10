/* 
	File: ODBCEXT.HPP
	Anzeige von ODBC-Daten.

	Erarbeitet: J. Benkenstein						Stand vom 25.09.1995
*/

#ifndef _ODBCEXT_HPP
#define _ODBCEXT_HPP

extern "C" {
// 	ObjektPropertyFunktionen
	char * __export PASCAL RetrieveFieldInfo (long lONr, char *pBuffer, short iLen, DWORD eData);
	void __export PASCAL FreeFieldName (DWORD);
}

enum ParamType { FeldName, dBaseExpr, TagName};

#ifndef NOODBCEXTENSION
class DBaseDispatchTree;
class CRecSet;
class CColumnObjArray;
class CDataBaseExt;
class CConnect;
class CObjectProperties;
class CTableNameTree;
class StringDup;
class CDataBaseExtTree;
//class CImportOdbcData;

// Diese Klasse zeigt die Fehlermeldungen an
class CErrMessageHandler
{
public:
	virtual void Show(CString& strMsg);
};

// Diese Klasse verhindert das anzeigen von Fehlermeldungen
class CErrMessageBlocker
{
private:
	CErrMessageHandler* pOldHandler;
public:
	CErrMessageBlocker();
	~CErrMessageBlocker();
};

class CLastIdentInfo
{ 
public:
	BOOL m_bRefreshed;
	ulong m_ulIdent;
	CString m_strSQL, m_strTableName;
	CDataBaseExt *m_pCDataBase;
	CRecSet *m_pCRecSet;
	CColumnObjArray *m_pCA;
	
	CLastIdentInfo (void);
	~CLastIdentInfo (void);
	
	void CleanUp (BOOL bEraseIdent = TRUE);
	void RemoveAll (void);
	BOOL HasInfo (void);
	BOOL Refresh (StringDup &strTableName, long lObjNr, ulong ulIdent);
};

class CFeldInfos
{
public:       
	CString m_strTableName;	// TabellenName
	CString m_strFeldName;	// FeldName
	CString m_strAlias;		// DSN-Alias
	int m_sIndex;			// Index in ColumnObjArray
	int m_iDataType;		// FeldTyp
	HPROJECT m_hPr;

	CFeldInfos (void) 	{ m_sIndex = -1; m_iDataType = SQL_CHAR; m_hPr = NULL; }
	~CFeldInfos (void)  {}
};

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(ObjectProperty);

class CODBCObjectProperties : 
	public CObjectProperties
{
private:
	typedef map<os_string, WObjectProperty, less<os_string> > CObjProps;
	CObjProps m_mapObjProps;

	ulong m_ulIdent;		// zuletzt install. Objektklasse
	int m_sCnt;			// Anzahl der inst. Eigenschaften

protected:
#if _TRiAS_VER >= 0x0400
	CLastIdentInfo m_LastIdentInfo;
#endif // _TRiAS_VER >= 0x0400

	short InstallIdentPropertyFunctions (ulong ulIdent, CTableNameTree *pTableNameTree = NULL, char *pAliasName = NULL);

public:
	CODBCObjectProperties ();
	~CODBCObjectProperties (void);

static CODBCObjectProperties *CreateInstance (LPUNKNOWN pIUnk, LPCSTR pcGroupName = NULL, DWORD dwFlags = PROPCAPS_NONE);

	STDMETHOD(OnNewReferenceObjects) (THIS_ INT_PTR lIdent);
	STDMETHOD(OnNewReferenceObject) (THIS_ INT_PTR lRefONr);
	STDMETHOD(OnNewReferenceObjects) (THIS_ INT_PTR lRefObjs, INT_PTR lRefObj);

	void ResetOptInfo (void) { m_ulIdent = 0; m_sCnt = 0; }
	CLastIdentInfo &GetLastIdentInfo() { return m_LastIdentInfo; }
	short InstallActPropertyFunctions (long lONr, ulong ident = 0);	// Objekt-Eigenschafts-Funktionen

	void ResetObjProps() { m_mapObjProps.clear(); }
};

class COdbcExtension :	
	public CTriasExtension, 
	public CSyncMonitor,
	public CODBCObjectProperties,
	public CComCoClass<COdbcExtension, &CLSID_ODBCExtension>
{
private:
	// CODBCObjectProperties *m_pIObjProp;			// Eigenschafts-Interface
	DBaseDispatchTree *_pDispatcher; 			// View-Odbc-Fenster-Verwalter	
	BOOL m_bShowInfo;							// Darstellungs-Semaphor
	BOOL m_bOptEnable;							// Optimierungsflag
	CMenu* m_pPopupMenu;
	CErrMessageHandler*	m_pErrMsgHdl;			// Strategie des Anzeigens von ODBC-Fehlern

public:
	HWND _hWndLast;             // ORFenster mit Fokus
	long _lONr;             	// selektiertes Objekt
	ulong _lIdent;           	// zugehöriger Ident
	short _Type;            	// Typ eines Parameters in INI-Datei

	char *_pAliasName;
	char *_pFieldName;
	char *_pKeyName;

// 	Konstruktor / Destruktor
	COdbcExtension (void);
	~COdbcExtension (void);

	HRESULT FinalConstruct (void);

	BEGIN_COM_MAP(COdbcExtension)
		COM_INTERFACE_ENTRY(ITriasXtension)
		COM_INTERFACE_ENTRY(ITriasXtension2)
		COM_INTERFACE_ENTRY(IObjectProps)
	END_COM_MAP()

	DECLARE_NO_REGISTRY()
	DECLARE_NOT_AGGREGATABLE_SINGLE(COdbcExtension, g_pTE)

//  überladene virtuelle Funktion(en)
	STDMETHOD_(BOOL, InitExtension) (THIS_ short iMode);
	STDMETHOD_(BOOL, UnLoadExtension) (THIS);
	STDMETHOD_(BOOL, MenuInit) (THIS_ HMENU hMenu, LPARAM lParam, HWND hWnd);
	STDMETHOD_(BOOL, MenuCommand) (THIS_ WPARAM wParam, HWND hWnd);
	STDMETHOD_(LRESULT, Notification) (THIS_ WPARAM wParam, LPARAM lParam);

// existiert Merkmalskode ?
	BOOL ExistsMValue (long lONr, ulong MCode);

// Merkmalswert lesen
	BOOL GetMerkmalsValue (long lONr, ulong MCode, char *pBuffer = 0, short iLen = 0);

//	akt. Anbindungs-Parameter aus Projekt-Ini-Datei lesen
	short ReadDBaseCodes (long lONr, ulong lIdent);

// dBase-Expression expandieren
	char *_ExpandDBaseExpression (long ONr, pchar pExpr);
	
//	gültiger MerkmalsCode ?                                         
	BOOL ValidMK (long MK);    

// Fenster mit ODBC-Infos anzeigen
	BOOL ShowDBaseInfo (void);

	void RemoveMainMenu();
	BOOL InstallMainMenu();

// Anzeigen von Fehlercodes
	void Show(CString& strErr)
	{
		if (m_pErrMsgHdl)
			m_pErrMsgHdl->Show(strErr);
	}
	CErrMessageHandler* SetErrMessageHandler(CErrMessageHandler* pShower);

	BOOL GetOptEnable() { return m_bOptEnable; }
		
#if _TRiAS_VER < 0x0400
	friend char* __export PASCAL RetrieveFieldInfo (long lONr, char *pBuffer, short iLen, DWORD eData);
	friend class CLastIdentInfo;
#endif // _TRiAS_VER < 0x0400
//	friend class CImportOdbcData;
};
#endif	// NOODBCEXTENSION

///////////////////////////////////////////////////////////////////////////////
// Helperfunktionen
typedef set<ULONG, less<ULONG> > CObjClassMap_t;
typedef CObjClassMap_t::iterator CObjClassMap_t_tit;

BOOL FillMapWithClasses (HPROJECT hPr, CObjClassMap_t &rMap, CString &rstrClasses);

#endif // _ODBCEXT_HPP




