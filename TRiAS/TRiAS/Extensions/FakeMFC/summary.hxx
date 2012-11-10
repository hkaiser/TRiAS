// Implementation eines PropertySheetHandlers für TRiAS.Document.2 ------------
// File: SUMMARY.HXX

#if !defined(_SUMMARY_HXX)
#define _SUMMARY_HXX

#include <shlobj.h>
#include <ixtnext.hxx>
#include <dirisole.h>

// Controlling Unknown --------------------------------------------------------
class CStatPage;		// forward declaration only
class CSummPage;

class CSummaryInfo : public IUnknown {
private:
	DWORD m_dwRefCnt;
	DESTROYNOTIFYPROCPTR m_pProc;

protected:
// InterfaceImplementation für Initialisierung der PropertySheetExtension
	class CTRiASExtInit : public ITriasExtInit {
	private:
#if defined(_DEBUG)
		DWORD m_dwRefCnt;
#endif // _DEBUG
		IUnknown *m_pIUnk;
		CSummaryInfo *m_pInfo;

	public:
			CTRiASExtInit (IUnknown *pIUnk, CSummaryInfo *pInfo);
			~CTRiASExtInit (void);

	// *** IUnknown members (delegating)
		STDMETHOD(QueryInterface)(REFIID, LPVOID FAR *);
		STDMETHOD_(ULONG, AddRef) (void);
		STDMETHOD_(ULONG, Release) (void);

	// *** ITriasExtInit methods 
		STDMETHOD(Initialize) (THIS_ LPCITEMIDLIST pidl, LPDATAOBJECT lpdobj, HKEY hkeyProgID);

	friend class CSummaryInfo;
	};
	CTRiASExtInit m_Init;

// InterfaceImplementation für eigentliche PropertySheetExtension
	class CTRiASPropSheetExt : public ITriasPropSheetExt {
	private:
#if defined(_DEBUG)
		DWORD m_dwRefCnt;
#endif // _DEBUG
		IUnknown *m_pIUnk;
		CSummaryInfo *m_pInfo;

		UINT m_uiCF;			// CF_... TRiAS.Document.2
		CSummPage *m_pSummPage;
		CStatPage *m_pStatPage;

	protected:
		HRESULT Initialize (LPCITEMIDLIST pidl, LPDATAOBJECT pIDO, HKEY hKey);

	public:
			CTRiASPropSheetExt (IUnknown *pIUnk, CSummaryInfo *pInfo);
			~CTRiASPropSheetExt (void);

	// *** IUnknown members (delegating)
		STDMETHOD(QueryInterface)(REFIID, LPVOID FAR *);
		STDMETHOD_(ULONG, AddRef) (void);
		STDMETHOD_(ULONG, Release) (void);

	// *** ITriasPropSheetExt
		STDMETHOD(AddPages) (THIS_ LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam);
		STDMETHOD(ReplacePage) (THIS_ UINT uPageID, LPFNADDPROPSHEETPAGE lpfnReplacePage, LPARAM lParam);

	friend class CSummaryInfo;
	};
	CTRiASPropSheetExt m_Handler;

// Construction by friends only
		CSummaryInfo (IUnknown *pIUnk, DESTROYNOTIFYPROCPTR pProc);

	bool FInit (void);

public:
	HRESULT Initialize (LPCITEMIDLIST pidl, LPDATAOBJECT pIDO, HKEY hKey)
		{ return m_Handler.Initialize (pidl, pIDO, hKey); }

public:
		~CSummaryInfo (void);

static CSummaryInfo *CreateInstance (IUnknown *pIUnk, DESTROYNOTIFYPROCPTR pProc);

// *** IUnknown members
	STDMETHOD(QueryInterface)(REFIID, LPVOID FAR *);
	STDMETHOD_(ULONG, AddRef) (void);
	STDMETHOD_(ULONG, Release) (void);
};

#endif // _SUMMARY_HXX
