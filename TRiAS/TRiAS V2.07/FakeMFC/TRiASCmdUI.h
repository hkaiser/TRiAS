// TRiASCmdUI.h : Declaration of the CTRiASToolCmdUI

#if defined(_USE_SEC_CLASSES)
/////////////////////////////////////////////////////////////////////////////
// muﬂ hier nochmal definiert werden, da diese Klasse in keinem Header drin ist
class SECCustomToolCmdUI : 
	public CCmdUI
{
public:
	virtual void Enable(BOOL bOn);
	virtual void SetCheck(int nCheck);
	virtual void SetText(LPCTSTR lpszText);
};
#else
#define SECCustomToolCmdUI CCmdUI
#endif // _USE_SEC_CLASSES

/////////////////////////////////////////////////////////////////////////////
// CTRiASToolCmdUI

class CTRiASToolCmdUI : 
	public ITRiASCmdUI,
	public CComDualImpl<DTRiASCmdUI, &IID_DTRiASCmdUI, &LIBID_ToolBarLib,
				TOOLBAR_TYPELIB_VERSION_MAJOR, TOOLBAR_TYPELIB_VERSION_MINOR>,
	public CComISupportErrorInfoImpl<&IID_DTRiASCmdUI>,
	public CComObjectRoot
//	public CComObjectBase<&CLSID_TRiASToolUI>
{
public:
	CTRiASToolCmdUI() {}
	~CTRiASToolCmdUI() {}

	BEGIN_COM_MAP(CTRiASToolCmdUI)
		COM_INTERFACE_ENTRY(ITRiASCmdUI)
		COM_INTERFACE_ENTRY(DTRiASCmdUI)
		COM_INTERFACE_ENTRY2(IDispatch, DTRiASCmdUI)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

	DECLARE_NOT_AGGREGATABLE(CTRiASToolCmdUI)

public:
// *** ITRiASToolCmdUI specific functions
	STDMETHOD(put_IsEnabled) (THIS_ VARIANT_BOOL fEnable);
	STDMETHOD(put_CheckState) (THIS_ int nCheck); 
	STDMETHOD(put_IsOn) (THIS_ VARIANT_BOOL fOn);
	STDMETHOD(put_Text) (THIS_ BSTR bstrNewText);

	STDMETHOD(get_CmdID) (THIS_ int *puiID);

public:
	SECCustomToolCmdUI state;
};


/////////////////////////////////////////////////////////////////////////////
// CTRiASStatusCmdUI

class CTRiASStatusCmdUI : 
	public ITRiASCmdUI,
	public CComDualImpl<DTRiASCmdUI, &IID_DTRiASCmdUI, &LIBID_ToolBarLib,
				TOOLBAR_TYPELIB_VERSION_MAJOR, TOOLBAR_TYPELIB_VERSION_MINOR>,
	public CComISupportErrorInfoImpl<&IID_DTRiASCmdUI>,
	public CComObjectRoot
//	public CComObjectBase<&CLSID_TRiASStatusUI>
{
public:
	CTRiASStatusCmdUI() {}
	~CTRiASStatusCmdUI() {}

	BEGIN_COM_MAP(CTRiASStatusCmdUI)
		COM_INTERFACE_ENTRY(ITRiASCmdUI)
		COM_INTERFACE_ENTRY(DTRiASCmdUI)
		COM_INTERFACE_ENTRY2(IDispatch, DTRiASCmdUI)
		COM_INTERFACE_ENTRY_IID(IID_DTRiASCmdUI, DTRiASCmdUI)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

	DECLARE_NOT_AGGREGATABLE(CTRiASStatusCmdUI)

public:
// ***ITRiASToolCmdUI specific functions
	STDMETHOD(put_IsEnabled) (THIS_ VARIANT_BOOL fEnable);
	STDMETHOD(put_CheckState) (THIS_ int nCheck); 
	STDMETHOD(put_IsOn) (THIS_ VARIANT_BOOL fOn);
	STDMETHOD(put_Text) (THIS_ BSTR bstrNewText);

	STDMETHOD(get_CmdID) (THIS_ int *puiID);

public:
	SECCustomToolCmdUI state;
};

/////////////////////////////////////////////////////////////////////////////
// CTRiASToolCmdQueryUI

class CTRiASToolCmdQueryUI : 
	public ITRiASCmdUI,
	public CComObjectRoot
//	public CComObjectBase<&CLSID_TRiASToolQueryUI>
{
public:
	CTRiASToolCmdQueryUI();
	~CTRiASToolCmdQueryUI() {}

	BEGIN_COM_MAP(CTRiASToolCmdQueryUI)
		COM_INTERFACE_ENTRY(ITRiASCmdUI)
	END_COM_MAP()

	DECLARE_NOT_AGGREGATABLE(CTRiASToolCmdQueryUI)

public:
// ***ITRiASToolCmdUI specific functions
	STDMETHOD(put_IsEnabled) (THIS_ VARIANT_BOOL fEnable);
	STDMETHOD(put_CheckState) (THIS_ int nCheck); 
	STDMETHOD(put_IsOn) (THIS_ VARIANT_BOOL fOn);
	STDMETHOD(put_Text) (THIS_ BSTR bstrNewText);

	STDMETHOD(get_CmdID) (THIS_ int *puiID);

public:
	CCmdUI state;

	bool m_fEnabled;
	bool m_fRadioState;
	CString m_strText;
	int m_iCheckState;

	bool m_fChangedEnable;
	bool m_fChangedCheckState;
	bool m_fChangedRadioState;
	bool m_fChangedText;
};

