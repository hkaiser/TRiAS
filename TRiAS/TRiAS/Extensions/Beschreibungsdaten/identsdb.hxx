// ExtensionKlasse fuer die Verwaltung von BeschreibungsDaten -----------------
// File: IDENTSDB.HXX

#if !defined(_IDENTSDB_HXX)
#define _IDENTSDB_HXX

#define TEXTLEN	_MAX_PATH

#include <istatus.h>
#if !defined(WIN16)
#include <itoolbar.h>
#endif

#import "msxml.dll" named_guids rename_namespace("xml")

class IdIgnoreList;
class MCodeIgnoreList;

class CIdentsDBExtension : 
	public CTriasExtension 
{
private:
	bool _AllIdentIgnore;	// alle weiteren Fehler ignorieren
	bool _AllMCodeIgnore;

	bool m_fSysMode;

	ULONG _iOPKText;	// ID's der ObjPropFuncs
	ULONG _iOPLText;
	
	long m_lIdentHandled;	// FehlerBehandlung aktiv, wenn != -1L
	long m_lMCodeHandled;

	short m_iMkBase;

	CObjectProperties *m_pObjProp;
	Menu *m_pPopupMenu;
		
protected:
	IdIgnoreList *pIIL;
	MCodeIgnoreList *pIML;
	
	HRESULT InitializeImportStatus (LPPROGRESSINDICATOR pIStatus, LPCSTR pcFName);
	HRESULT InitializeImportStatus (LPPROGRESSINDICATOR pIStatus, LPCSTR pcFName, ULONG ulCnt, bool fFirst = true);
	HRESULT InitializeExportStatus (LPPROGRESSINDICATOR pIStatus, int iType);

public:		// Menubefehle
	bool DefineIdentifier (void);
	bool DefineMerkmal (void);
	bool DeleteIdentifier (void);
	bool DeleteMerkmal (void);

public:
// Konstruktor / Destruktor
		CIdentsDBExtension (void);
		~CIdentsDBExtension (void);

// *** IUnknown methods
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj);

// ***ITriasXtension methods
	STDMETHOD_(BOOL, InitExtension) (THIS_ short iMode);
	STDMETHOD_(BOOL, UnLoadExtension) (THIS);
	STDMETHOD_(BOOL, MenuInit) (THIS_ HMENU hMenu, LPARAM lParam, HWND hWnd);
	STDMETHOD_(BOOL, MenuSelect) (THIS_ UINT uiMenuID, HMENU hMenu, HWND hWnd);
	STDMETHOD_(BOOL, MenuCommand) (THIS_ UINT uiMenuID, HWND hWnd);
	STDMETHOD_(LRESULT, Notification) (THIS_ WPARAM wParam, LPARAM lParam);
	STDMETHOD_(LRESULT, WindowsNotification) (THIS_ UINT wMsg, WPARAM wParam, LPARAM lParam);

	short HandleErrorMessage (ERRORMESSAGE *pEM);

	short DefineNewIdent (long Ident = -1L, bool = FALSE);
	bool DeleteIdent (long Ident, bool fUndo = true);
	bool DeleteAllIdents (HPROJECT hPr);

	short DefineNewMCode (long MCode = -1, bool = FALSE);
	bool DeleteMCode (long MCode, long lIdent, bool fUndo = true);	
	bool DeleteAllMCodes (HPROJECT hPr);	

	short DefineNewPbd (HPROJECT hPr);
	bool SelectNewPbdName (HPROJECT hPr);
	bool GenerateNewPbd (HPROJECT hPr);
	bool GenerateNewCOMPbd (HPROJECT hPr, IStorage *pIStorage);
	bool GenerateNewFilePbd (HPROJECT hPr);

	bool ExportCodes (void);
	bool ExportIdents (LPUNKNOWN pIUnk, char *pFName, const char *pExt = NULL);
	bool ExportMCodes (LPUNKNOWN pIUnk, char *pFName, const char *pExt = NULL);
	bool ExportAsXml (LPUNKNOWN pIUnk, LPCSTR pFName);
	bool ExportDataSourceAsXml (LPUNKNOWN pIUnk, HPROJECT hPr, LPCSTR pFName, ULONG &rulCnt);
	bool ExportCodeTemplate (LPUNKNOWN pIUnk, LPSTR pFName, LPCSTR pcExt, short iTyp, ENUMLONGKEYPROC pFcn);

	bool ImportCodes (void);
	bool ImportFromXml (LPCSTR pcFile, IProgressIndicator *pIStatus, HPROJECT hPr, bool fKeepExisting, bool fRejectUnused, bool fFirst);
	HRESULT ImportMetaData (LPCSTR pcFile, IProgressIndicator *pIStatus, xml::IXMLDOMElement *pIData, HPROJECT hPr, bool fKeepExisting, bool fRejectUnused, bool fFirst);
	HRESULT ImportObjectClass (LPCSTR pcFile, xml::IXMLDOMNode *pINode, HPROJECT hPr, bool fKeepExisting, bool fRejectUnused);
	HRESULT ImportObjectFeatures (LPCSTR pcFile, INT_PTR lIdent, xml::IXMLDOMNode *pINode, bool fKeepExisting);
	HRESULT ImportObjectFeature (LPCSTR pcFile, INT_PTR lIdent, xml::IXMLDOMNode *pINode, bool fKeepExisting);

	void ShowXMLError (xml::IXMLDOMParseError *pIError);
	void ShowBadTXCFile(LPCSTR pcFName);

	bool InstallPopupMenu (int iIndex);
	void RemovePopupMenus();
	bool FindMenuItem (HMENU hMenu, UINT uiID);

// Funktionen für ObjProperties
	ULONG AddPropertyFunction (LPCSTR pFName, OBJPROPCALLBACK pFunc, DWORD dwFlags)
		{ return m_pObjProp -> AddPropertyFunction (pFName, pFunc, dwFlags); }

// Freigeben einer/aller OPFs
	bool RemovePropertyFunction (ULONG ulFuncID)
		{ return m_pObjProp -> RemovePropertyFunction (ulFuncID); }

	HRESULT CreateMetaDataToolBar (void);
	HRESULT RemoveMetaDataToolBar (void);

#if defined(_SUPPORT_QUERYDEFS)
	BOOL HasQueryDef();
#endif // defined(_SUPPORT_QUERYDEFS)

protected:
// DEX_... commandsupport
	bool InitJumpTable();
	void FreeJumpTable();
	LRESULT FullFillWill (WPARAM wParam, LPARAM lParam);

	typedef LRESULT (CIdentsDBExtension::*DEXMESSAGEPROC)(HPROJECT, LPARAM);
	DEXMESSAGEPROC *m_cbDexProcs;	// Sprungverteiler (DEX_...)

	unsigned int m_i1stDexProc;		// erste Funktion
	unsigned int m_iDexProcsNum;	// Anzahl der Funktionen in Tabelle

public:
#include "DexCommands.h"
};

string FakeTRiASName (UINT resID, ...);
string FakeTRiASName (LPCSTR pcTempl, ...);

///////////////////////////////////////////////////////////////////////////////
// ExportMode
typedef enum tagEXPORTMODE {
	EXPORTMODE_Normal = 0,
	EXPORTMODE_IdentOnly = 0x01,
	EXPORTMODE_OKSOnly = 0x02,
	EXPORTMODE_IdentAndOKS = 0x03,
	EXPORTMODE_TXI = 0x0F,
} EXPORTMODE;

extern EXPORTMODE s_rgExportMode;

#endif 	// _IDENTSDB_HXX
