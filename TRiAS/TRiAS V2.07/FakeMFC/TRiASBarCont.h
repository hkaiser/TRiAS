// TRiASBarCont.h : Declaration of the CTRiASBarCont


///////////////////////////////////////////////////////////////////////////////
// CTRiASBarCont

class CTRiASBarCont : 
	public ITRiASBarContainer,
	public CComDualImpl<DControlToolBars, &IID_DControlToolBars, &LIBID_ToolBarLib, 
				TOOLBAR_TYPELIB_VERSION_MAJOR, TOOLBAR_TYPELIB_VERSION_MINOR>,
	public CComISupportErrorInfoImpl<&IID_DControlToolBars>,
	public CComObjectRoot
{
public:
	CTRiASBarCont() {}
	~CTRiASBarCont() {}

	BEGIN_COM_MAP(CTRiASBarCont)
		COM_INTERFACE_ENTRY(ITRiASBarContainer)
		COM_INTERFACE_ENTRY(DControlToolBars)
		COM_INTERFACE_ENTRY_IID(IID_DTRiASCollection, DControlToolBars)
		COM_INTERFACE_ENTRY_IID(IID_DTRiASBaseClass, DControlToolBars)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

	DECLARE_AGGREGATABLE(CTRiASBarCont)

public:
// *** ITRiASBarContainer specific functions ***
	STDMETHOD(EnumTRiASBars) (THIS_ IEnumITRiASBar **ppEnum);
	STDMETHOD(FindTRiASBar) (THIS_ LPCSTR pcName, ITRiASBar **pIBar);
	STDMETHOD(AddTRiASBar) (THIS_ LPCSTR pcName, DWORD dwStyle, DWORD dwStyleEx, ITRiASBar **ppITools);
	STDMETHOD(DeleteTRiASBar) (THIS_ LPCSTR pcName);

// *** DControlToolBars specific functions
	STDMETHOD(get_isA)(THIS_ LONG *plRTTI);					// ObjektTyp (RTTI)
	STDMETHOD(get_Parent)(THIS_ IDispatch **ppIBase);		// übergeordnetes Objekt
	STDMETHOD(put_Parent)(THIS_ IDispatch *pIBase);
	STDMETHOD(get_Application)(THIS_ IDispatch **ppIApp);	// Anwendung
	STDMETHOD(put_Application)(THIS_ IDispatch *pIApp);

	STDMETHOD(get_Count)(THIS_ LONG *plCnt);
	STDMETHOD(Item)(THIS_ VARIANT vItem, IDispatch **ppIDisp);
	STDMETHOD(_NewEnum)(THIS_ IUnknown **pvEnum);
	STDMETHOD(Add)(THIS_ VARIANT vAdd, IDispatch **ppIDisp);
	STDMETHOD(Remove)(THIS_ VARIANT vRemove);
	STDMETHOD(Refresh)(THIS);

	STDMETHOD(SaveState)(THIS_ VARIANT vKey, VARIANT vProject);
	STDMETHOD(LoadState)(THIS_ VARIANT vKey, VARIANT vProject);

private:
	class CMainFrame *m_pFrame;

protected:
	CComPtr<IDispatch> m_Parent;	// für Einbindung in OleAutomation
	CComPtr<IDispatch> m_App;

public:
	HRESULT SetFrame (CMainFrame *pFrame) { m_pFrame = pFrame; return S_OK; }
};

///////////////////////////////////////////////////////////////////////////////
// _NewEnum-Enumerator

class CToolBarNewEnum :
	public IEnumVARIANT,
	public CComObjectRoot
{
public:
	CToolBarNewEnum() {}
	~CToolBarNewEnum() {}

	BEGIN_COM_MAP(CToolBarNewEnum)
		COM_INTERFACE_ENTRY(IEnumVARIANT)
	END_COM_MAP()

	DECLARE_NOT_AGGREGATABLE(CToolBarNewEnum)

// *** IEnumVARIANT methods
	STDMETHOD(Next)(ULONG celt, VARIANT *rgvar, ULONG *pceltFetched);
	STDMETHOD(Skip)(ULONG celt);
	STDMETHOD(Reset)(void);
	STDMETHOD(Clone)(LPENUMVARIANT *ppenum);

// zusätzliche Member
	HRESULT FInit (CMainFrame *pFrame);		// Initialisierung
	HRESULT FInit (IEnumITRiASBar *pIEnum)
		{ m_Enum = pIEnum; return S_OK; }

private:
	WEnumITRiASBar m_Enum;
};
