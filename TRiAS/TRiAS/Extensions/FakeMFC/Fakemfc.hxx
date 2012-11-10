// Beispielerweiterung --------------------------------------------------------
// File: FAKEMFC.HXX

#if !defined(_FAKEMFC_HXX)
#define _FAKEMFC_HXX

#include <ospace/com/iterenum.h>
#include <ospace/std/set>

#include <comcat.h>
#include <itoolbar.h>

#include "InlineFuncs.h"
#include "Wrapper.h"
#include "TRiASBarCont.h"

#include "TRiASDocTempl.h"
#include "TRiASDoc.h"
#include "CntrItem.h"
#include "TRiASView.h"
#include "ConnectParams.h"

// Offset der ResourceID's für diese Erweiterung ------------------------------
#define RESID_OFFSET	22000

// neuer NotificationCode für ComboBoxen
#define CBN_HITRETURN	WM_USER+1000

/////////////////////////////////////////////////////////////////////////////
// sonstige Funktionen
#ifndef _MAC
bool InstallFont (CFont &rFont, bool fBold = false, int iPtr = -12);
#else
bool InstallFont (CFont &rFont, bool fBold = false, int iPtr = -14);
#endif 

///////////////////////////////////////////////////////////////////////////////
// Smartinterfaces
DefineSmartInterface(TRiASDBEngine);
DefineSmartInterface(TRiASDataServerRegEntries);
DefineSmartInterface(DataObject);

/////////////////////////////////////////////////////////////////////////////
// GUIDs sollten gecached werden
DefineEnumerator2(GUID, IID_IEnumGUID);

///////////////////////////////////////////////////////////////////////////////
// forward declarations
class CCreateNewWiz;

///////////////////////////////////////////////////////////////////////////////
// Helper für Lizensierungsdialog
class CVerifyLicense:
	public VERIFYLICENSEEX
{
public:
	CVerifyLicense() { INITSTRUCT(*this, VERIFYLICENSEEX); }
	~CVerifyLicense() 
	{
		if (NULL != pcCaption) {
			delete const_cast<char *>(pcCaption);
			pcCaption = NULL;
		}
		if (NULL != pcLicText) {
			delete const_cast<char *>(pcLicText);
			pcLicText = NULL;
		}
	}
	CVerifyLicense &operator= (const VERIFYLICENSE &rhs)
	{
		if (reinterpret_cast<VERIFYLICENSE *>(this) != &rhs) {
			INITSTRUCT(*this, VERIFYLICENSE); 
			lLevelOrOption = rhs.lLevelOrOption;
			iMode = rhs.iMode;
			hWndParent = rhs.hWndParent;
			if (NULL != rhs.pcCaption) {
				try { pcCaption = new char [strlen(rhs.pcCaption) +1]; } catch(...) {};
				if (NULL != pcCaption)
					strcpy (const_cast<char *>(pcCaption), rhs.pcCaption);
			}
			else
				pcCaption = NULL;
		}
		return *this;
	}
	CVerifyLicense &operator= (const VERIFYLICENSEEX &rhs)
	{
		if (this != &rhs) {
			INITSTRUCT(*this, VERIFYLICENSEEX); 
			lLevelOrOption = rhs.lLevelOrOption;
			iMode = rhs.iMode;
			hWndParent = rhs.hWndParent;
			if (NULL != rhs.pcCaption) {
				try { pcCaption = new char [strlen(rhs.pcCaption) +1]; } catch(...) {};
				if (NULL != pcCaption)
					strcpy (const_cast<char *>(pcCaption), rhs.pcCaption);
			}
			else
				pcCaption = NULL;

			if (NULL != rhs.pcLicText) {
				try { pcLicText = new char [strlen(rhs.pcLicText) +1]; } catch(...) {};
				if (NULL != pcLicText)
					strcpy (const_cast<char *>(pcLicText), rhs.pcLicText);
			}
			else
				pcLicText = NULL;
		}
		return *this;
	}
};

///////////////////////////////////////////////////////////////////////////////
// Die Erweiterung selbst

class CManageConnections;

class CFakeMFCExtension : 
	public CTriasExtension 
{
private:
	void ShowTipAtStartup (void);
	void ShowTipOfTheDay (void);
	void ShowOpenWizard (void);

public:
	CManageConnections *m_pManageConnections;

private:
	DWORD m_dwTOTD;			// Flags für TipOfTheDay
	class CSummInfo *m_pSummInfo;	// aktuelle SummaryInfo
	bool m_fDirty;			// SummaryInfo ist Dirty

	CComObject<CTRiASBarCont> *m_pBarCont;

	CTRiASDocTemplate *m_pDocTempl; 
	CTRiASView *m_pViewWnd;

	typedef list<os_pair<WTRiASDBEngine, DWORD> > CTRiASDBEngines;
	CTRiASDBEngines m_DBEngs;	// Liste der registrierten DBEngines
	DWORD m_dwCookie;			// Advise für ITRiASProjectEvents
	LONG m_ulOpenSem;			// Semaphore beim Öffnen
	CVerifyLicense m_vLic;		// Helper für Lizensierungsdialog

	WTRiASDataServerRegEntries m_Entries;	// Liste der registrierten DataServer

	bool m_bRunEmbedded;

	CMenu *m_pPopupMenu;
	BOOL InstallToolbarMenu();
	void RemoveToolbarMenu();

	CMenu *m_pConnectFilterMenu;
	BOOL InstallConnectFilterMenu();
	void RemoveConnectFilterMenu();

#if defined(_USE_DRAG_N_DROP)
	struct ignore_case_string_cmp :
		public os_binary_function<os_string, os_string, bool>
	{
		bool operator() (const os_string &lhs, const os_string &rhs)
		{
			return (stricmp(lhs.c_str(), rhs.c_str()) < 0) ? true : false;
		}
	};
	typedef map<os_string, CConnectParams, ignore_case_string_cmp> CExtensions;

	WDataObject m_DataObject;
	CExtensions m_lstExts;
	bool m_fHasExts;
#endif // defined(_USE_DRAG_N_DROP)

protected:
///////////////////////////////////////////////////////////////////////////////
// Notificationhandlers
	HRESULT OnCreateNewDocument (IStorage *pIStg);
	HRESULT OnOpenDocument (void);
	HRESULT OnSaveDocument (IStorage *pIStg, bool fSameAsLoad);
	HRESULT OnProjectPrinted (void);
	HRESULT OnClosingProject (void);
	HRESULT OnProjectToClose (void);
	HRESULT OnReReadHeader();

	bool OnInitializedServer (void);
	bool OnExtensionsLoaded (void);
	bool OnServerClosed (void);
	bool OnQueryTipOfTheDay (DWORD dwFlags);
	bool OnViewCreated (HWND hViewWnd);
	bool OnViewDeleted (HWND hViewWnd);
#if defined(_SEC_SUBCLASS_ORWND)
	bool OnORWndCreated (HWND hORWnd);
	bool OnORWndDeleted (HWND hORWnd);
#endif // _SUBCLASS_ORWND

	bool FindMenuItem (CMenu *pMenu, UINT uiID);

public:
	CSummInfo *GetSummInfo (void) { return m_pSummInfo; }
	CTRiASView *GetViewWnd() { return m_pViewWnd; }

public:
		CFakeMFCExtension (void);
		~CFakeMFCExtension (void);

	COleTemplateServer m_server;

	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj);

	STDMETHOD_(BOOL, InitExtension) (THIS_ short iMode);
	STDMETHOD_(BOOL, UnLoadExtension) (THIS);
	STDMETHOD_(LRESULT, Notification) (THIS_ WPARAM wParam, LPARAM lParam);
	STDMETHOD_(BOOL, MenuInit) (THIS_ HMENU hMenu, LPARAM lParam, HWND hWnd);
	STDMETHOD_(BOOL, MenuSelect) (THIS_ UINT uiMenuID, HMENU hMenu, HWND hWnd);
	STDMETHOD_(BOOL, MenuCommand) (THIS_ WPARAM wParam, HWND hWnd);
	STDMETHOD_(LRESULT, WindowsNotification) (THIS_ UINT wMsg, WPARAM wParam, LPARAM lParam);

#if defined(_USE_DRAG_N_DROP)
// *** ITRiASDropTarget
	STDMETHOD(DragEnter) (THIS_ DRAGDROPTYPE rgType, HWND hWnd, IDataObject *pDataObj, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect);
	STDMETHOD(DragOver) (THIS_ DRAGDROPTYPE rgType, HWND hWnd, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect);
	STDMETHOD(DragLeave) (THIS_ DRAGDROPTYPE rgType, HWND hWnd);
	STDMETHOD(Drop) (THIS_ DRAGDROPTYPE rgType, HWND hWnd, IDataObject *pDataObj, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect);
#endif // defined(_USE_DRAG_N_DROP)

	void InstallMenuItems (void);
	void InstallEmbeddedMenu (void);	// #AD000408
	void RemoveMenuItems (void);

	bool ShowProjectWizard (void);
	bool ShowNewprojectCommand (void);
	bool ShowOpenprojectCommand (void);
	bool OpenLastMRUProject (UINT uiMenuID = 1);
	HRESULT ShowAddConnectionCommand (CWnd *pWnd = NULL, BOOL fShowError = TRUE);
	HRESULT OpenExistingProjectOrDatasource (LPCSTR pcName, bool fRO);

	bool StartDBEngines (void);
	bool StopDBEngines (void);

// Verwaltung von Projekten/DataSources
	HRESULT CreateNewProject (LPCSTR pcName, bool fForce, OPENMODE rgMode = OPENMODE_Unknown, ITRiASProject **ppIPrj = NULL);
	HRESULT OpenExistingProject (LPCSTR pcName, BOOL fReadOnly, ITRiASProject **ppIPrj = NULL);
	HRESULT CreateNewProject (IStorage *pIStg, LPCSTR pcName = NULL, OPENMODE rgMode = OPENMODE_Unknown, ITRiASProject **ppIPrj = NULL);
	HRESULT OpenExistingProject (IStorage *pIStg, BOOL fReadOnly, LPCSTR pcName = NULL, ITRiASProject **ppIPrj = NULL);

	HRESULT CreateNewDataSource (
		ITRiASProject *pIPrj, REFCLSID rClsId, CFiles &rFiles, 
		LPCTSTR pcConnName,	LPCTSTR pcProgID, LPCTSTR pcConnect, BOOL fNameIsSubStorage);
	HRESULT OpenDataSource (
		ITRiASProject *pIPrj, REFCLSID rClsId, CFiles &rFiles, 
		LPCTSTR pcConnName, LPCTSTR pcConnDesc, CONNECTMODE rgMode,
		LPCTSTR pcProgID, LPCTSTR pcConnect, BOOL fNameIsSubStorage, 
		BOOL fPathIsConnectName, ITRiASConnection **ppIConn = NULL);
	HRESULT OpenDataSource(
		ITRiASProject *pIPrj, LPCSTR pcFileName, CConnectParams *pParams,
		BOOL fReadOnly = FALSE, BOOL fConvert = FALSE, ITRiASConnection **ppIConn = NULL);

	HRESULT CreateNewProjectNewDatasource (
		CConnectParams *pParams, CFiles &rFiles, LPCTSTR pcConnName, 
		LPCTSTR pcConnDesc, CCreateNewWiz &rAskForCoordSystem, ITRiASProject **ppIPrj);
	HRESULT CreateNewProjectOpenDatasource (
		CConnectParams *pParams, CFiles &rFiles, LPCTSTR pcConnName, 
		LPCTSTR pcConnDesc, CCreateNewWiz &rAskForCoordSystem, ITRiASProject **ppIPrj);

	HRESULT AddNewDatasource (CConnectParams *pParams, CFiles &rFiles, LPCTSTR pcConnName, 
		LPCTSTR pcConnDesc, BOOL fShowError = TRUE);
	HRESULT AddOpenDatasource (CConnectParams *pParams, CFiles &rFiles, LPCTSTR pcConnName, 
		LPCTSTR pcConnDesc, BOOL fShowError = TRUE);

	HRESULT CreateNewProjectOpenAndConvertDatasource (
		LPCTSTR pcFileName, bool fRO, CConnectParams *pParam = NULL, ITRiASProject **ppIPrj = NULL);
	HRESULT ConvertFromDataSource (LPCSTR pcName, ITRiASConnection *pIConn, ITRiASProject *pIPrj, BOOL fConvertProps);
	HRESULT CopyViewsToProject (ITRiASConnection *pIConn, ITRiASProject *pIPrj, BOOL fCopyDefault = FALSE, BOOL *pfIsDirty = NULL);
	HRESULT CopyPropertiesToProject (ITRiASConnection *pIConn, ITRiASProject *pIPrj, BOOL *pfIsDirty = NULL);
	HRESULT CopyPropertiesToDatasource (ITRiASProject *pIPrj, ITRiASConnection *pIConn, LPCSTR pcTcfName, BOOL *pfIsDirty = NULL);
	HRESULT CopyCoordSysParams (ITRiASProperties *pIPropsSrc, ITRiASProperties *pIPropsDest, BOOL *pfIsDirty = NULL);
	HRESULT CopyAuxHeaderEntries (ITRiASProperties *pIPropsSrc, ITRiASProperties *pIPropsDest, BOOL *pfIsDirty = NULL);
	HRESULT CopyHeaderEntries (const struct tagCOORDSYSKEY *pEntries, int iCntKeys, ITRiASProperties *pIPropsSrc, ITRiASProperties *pIPropsDest, BOOL *pfIsDirty = NULL);

	BOOL DoPromptFileName (CString &strFile, CString title, DWORD dwFlags, BOOL fOpenDlg, BOOL &rfRO, CDocTemplate* pTemplate, int *piFilter);

	HRESULT GetMainDBEngine (ITRiASMainDBEngine **ppIEngine);
	HRESULT ReadDataServerParams (DWORD &rdwPos, CConnectParams *pNewItem, LPCTSTR pcProgID = NULL);
	HRESULT RetrieveTarget (BSTR bstrProgID, BSTR *bstrTargetProgID);

	CString EnsureUniqueConnectionName (CWnd *pWnd, LPCSTR pcOrigName, LPCSTR pcFileName, BOOL *pfCorrected);
	HRESULT FindConnection (LPCSTR pToSearch);
	HRESULT ToDeleteConnection (LPCSTR pToSearch);

protected:
// DEX_... commandsupport
	bool InitJumpTable();
	void FreeJumpTable();
	LRESULT FullFillWill (WPARAM wParam, LPARAM lParam);

	typedef LRESULT (CFakeMFCExtension::*DEXMESSAGEPROC)(HPROJECT, LPARAM);
	DEXMESSAGEPROC *m_cbDexProcs;	// Sprungverteiler (DEX_...)

	unsigned int m_i1stDexProc;		// erste Funktion
	unsigned int m_iDexProcsNum;	// Anzahl der Funktionen in Tabelle

#if defined(_USE_DRAG_N_DROP)
	HRESULT EnsureFileExtensionList();
	HRESULT InitFileExtensionList(REFGUID rGuid);
	BOOL QueryPasteFromData(IDataObject *pIDO);
	BOOL PasteFromData(IDataObject *pIDO);
#endif // defined(_USE_DRAG_N_DROP)

public:
// globaler (gecachter) enumerator für GUID's der DBEngines
	class CEnumGuids
		: public NEnumGUID
	{
	public:
		CEnumGuids() : m_fIsInitialized(false) {}
		~CEnumGuids() {}

		HRESULT InitGuids (bool fForce = false);
		bool IsValid() { return m_fIsInitialized; }

		void RemoveActiveItem()
		{
		iterator itprev = m_itcur;

			--itprev;
			m_data.erase(itprev);		// aktuelles Item nicht mehr enumerieren
		}
		
	private:
		bool m_fIsInitialized;
	};
	static CEnumGuids s_DBEngineGUIDs;

public:
#include "DexCommands.h"
};

///////////////////////////////////////////////////////////////////////////////
// Registrieren und DeRegistrieren der PropSheetHandler 
bool RegisterHandler (REFCLSID rclsid, LPCTSTR pcProgID, UINT uiName, 
					  REFCLSID rTargetId, LPCTSTR pcTargetPropgID);
bool UnRegisterHandler (REFCLSID rclsid, LPCTSTR pcProgID, 
						REFCLSID rTargetId, LPCTSTR pcTargetPropgID);

///////////////////////////////////////////////////////////////////////////////
//
int __cdecl VMessageBox (CWnd *pWnd, UINT uiCaption, UINT rgType, UINT uiText, ...);
int __cdecl VMessageBox (CWnd *pWnd, LPCSTR pcCaption, UINT rgType, UINT uiText, ...);
string __cdecl FakeTRiASName (UINT resID, ...);
string __cdecl FakeTRiASName (LPCSTR pcTempl, ...);

///////////////////////////////////////////////////////////////////////////////
//
inline CFakeMFCExtension * TxGetExtension() { ASSERT(NULL != g_pTE); return (CFakeMFCExtension *)g_pTE; }

///////////////////////////////////////////////////////////////////////////////
//
#if defined(__XT) && defined(__DEXPROCS)
extern "C" DEXDISPATCHPROC g_pDexDispatchProc;
#endif // __XT && __DEXPROCS

///////////////////////////////////////////////////////////////////////////////
// ComponentCategory
extern const CATID CATID_TRiASDBEngine;

#if _TRiAS_VER < 0x0400
///////////////////////////////////////////////////////////////////////////////
// Version 4 emulieren
extern DWORD g_dwVer4;
#endif // _TRiAS_VER < 0x0400

#endif // _FAKEMFC_HXX
