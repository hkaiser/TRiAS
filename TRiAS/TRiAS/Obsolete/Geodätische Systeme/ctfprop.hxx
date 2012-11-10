// Implementation eines PropertySheetHandlers für TRiAS.Document.2 ------------
// File: CTFPROP.HXX

#if !defined(_CTFPROP_HXX)
#define _CTFPROP_HXX

// Controlling Unknown --------------------------------------------------------
class CCTFParams;		// forward declaration only

class CCTFPropExt : public IUnknown {
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
		CCTFPropExt *m_pInfo;

	public:
			CTRiASExtInit (IUnknown *pIUnk, CCTFPropExt *pInfo);
			~CTRiASExtInit (void);

	// *** IUnknown members (delegating)
		STDMETHOD(QueryInterface)(REFIID, LPVOID FAR *);
		STDMETHOD_(ULONG, AddRef) (void);
		STDMETHOD_(ULONG, Release) (void);

	// *** ITriasExtInit methods 
		STDMETHOD(Initialize) (THIS_ LPCITEMIDLIST pidl, LPDATAOBJECT lpdobj, HKEY hkeyProgID);

	friend class CCTFPropExt;
	};
	CTRiASExtInit m_Init;

// InterfaceImplementation für eigentliche PropertySheetExtension
	class CTRiASPropSheetExt : public ITriasPropSheetExt {
	private:
#if defined(_DEBUG)
		DWORD m_dwRefCnt;
#endif // _DEBUG
		IUnknown *m_pIUnk;
		CCTFPropExt *m_pInfo;

		CCTFParams *m_pCTFPropPage;		// eigentliche PropertyPage

	protected:
		HRESULT Initialize (LPCITEMIDLIST pidl, LPDATAOBJECT pIDO, HKEY hKey);

	public:
			CTRiASPropSheetExt (IUnknown *pIUnk, CCTFPropExt *pInfo);
			~CTRiASPropSheetExt (void);

	// *** IUnknown members (delegating)
		STDMETHOD(QueryInterface)(REFIID, LPVOID FAR *);
		STDMETHOD_(ULONG, AddRef) (void);
		STDMETHOD_(ULONG, Release) (void);

	// *** ITriasPropSheetExt
		STDMETHOD(AddPages) (THIS_ LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam);
		STDMETHOD(ReplacePage) (THIS_ UINT uPageID, LPFNADDPROPSHEETPAGE lpfnReplacePage, LPARAM lParam);

	friend class CCTFPropExt;
	};
	CTRiASPropSheetExt m_Handler;

// Construction by friends only
		CCTFPropExt (IUnknown *pIUnk, DESTROYNOTIFYPROCPTR pProc);

	bool FInit (void);

public:
	HRESULT Initialize (LPCITEMIDLIST pidl, LPDATAOBJECT pIDO, HKEY hKey)
		{ return m_Handler.Initialize (pidl, pIDO, hKey); }

public:
		~CCTFPropExt (void);

static CCTFPropExt *CreateInstance (IUnknown *pIUnk, DESTROYNOTIFYPROCPTR pProc);

// *** IUnknown members
	STDMETHOD(QueryInterface)(REFIID, LPVOID FAR *);
	STDMETHOD_(ULONG, AddRef) (void);
	STDMETHOD_(ULONG, Release) (void);
};

#endif // _CTFPROP_HXX
