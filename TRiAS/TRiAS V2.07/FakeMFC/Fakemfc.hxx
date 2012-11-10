// Beispielerweiterung --------------------------------------------------------
// File: FAKEMFC.HXX

#if !defined(_FAKEMFC_HXX)
#define _FAKEMFC_HXX

#include <ospace/com/iterenum.h>

#include "InlineFuncs.h"
#include "Wrapper.h"
#include "TRiASBarCont.h"

#include "TRiASDocTempl.h"
#include "TRiASDoc.h"
#include "CntrItem.h"
#include "TRiASView.h"

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
// Die Erweiterung selbst

class CFakeMFCExtension : 
	public CTriasExtension 
{
private:
	void ShowTipAtStartup (void);
	void ShowTipOfTheDay (void);
	void ShowOpenWizard (void);

private:
	DWORD m_dwTOTD;			// Flags für TipOfTheDay
	class CSummInfo *m_pSummInfo;	// aktuelle SummaryInfo
	bool m_fDirty;			// SummaryInfo ist Dirty

	CComObject<CTRiASBarCont> *m_pBarCont;

	CTRiASDocTemplate *m_pDocTempl; 
	CTRiASView *m_pViewWnd;

protected:
///////////////////////////////////////////////////////////////////////////////
// Notificationhandlers
	HRESULT OnCreateNewDocument (IStorage *pIStg);
	HRESULT OnOpenDocument (void);
	HRESULT OnSaveDocument (IStorage *pIStg, bool fSameAsLoad);
	HRESULT OnProjectPrinted (void);
	HRESULT OnClosingProject (void);

	bool OnInitializedServer (void);
	bool OnExtensionsLoaded (void);
	bool OnServerClosed (void);
	bool OnQueryTipOfTheDay (DWORD dwFlags);
	bool OnViewCreated (HWND hViewWnd);
	bool OnViewDeleted (HWND hViewWnd);

	bool FindMenuItem (CMenu *pMenu, UINT uiID);

public:
	CSummInfo *GetSummInfo (void) { return m_pSummInfo; }

public:
		CFakeMFCExtension (void);
		~CFakeMFCExtension (void);

	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj);

	STDMETHOD_(bool, InitExtension) (THIS_ short iMode);
	STDMETHOD_(bool, UnLoadExtension) (THIS);
	STDMETHOD_(LRESULT, Notification) (THIS_ WPARAM wParam, LPARAM lParam);
	STDMETHOD_(bool, MenuInit) (THIS_ HMENU hMenu, LPARAM lParam, HWND hWnd);
	STDMETHOD_(bool, MenuSelect) (THIS_ UINT uiMenuID, HMENU hMenu, HWND hWnd);
	STDMETHOD_(bool, MenuCommand) (THIS_ WPARAM wParam, HWND hWnd);

	bool ShowProjectWizard (void);
	bool ShowNewprojectCommand (void);
};

// Registrieren und DeRegistrieren der PropSheetHandler -----------------------
bool RegisterHandler (REFCLSID rclsid, LPCTSTR pcProgID, UINT uiName, 
					  REFCLSID rTargetId, LPCTSTR pcTargetPropgID);
bool UnRegisterHandler (REFCLSID rclsid, LPCTSTR pcProgID, 
						REFCLSID rTargetId, LPCTSTR pcTargetPropgID);

#if defined(__XT) && defined(__DEXPROCS)
extern "C" DEXDISPATCHPROC g_pDexDispatchProc;
#endif // __XT && __DEXPROCS

#endif // _FAKEMFC_HXX
