// UIOwner.h : Declaration of the CUIOwner


///////////////////////////////////////////////////////////////////////////////
// CUIOwner

DefineSmartInterface(TRiASToolBar);

class CUIOwner : 
	public ITRiASUIOwner,
	public CComObjectRoot,
	public CComCoClass<CUIOwner, &CLSID_TRiASUIOwner>

{
public:
	CUIOwner() {}
	~CUIOwner() {}

	BEGIN_COM_MAP(CUIOwner)
		COM_INTERFACE_ENTRY(ITRiASUIOwner)
	END_COM_MAP()

	DECLARE_NOT_AGGREGATABLE(CUIOwner)

public:
// *** ITRiASUIOwner specific functions ***
	STDMETHOD(OnUpdateUI) (THIS_ ITRiASBar *pIBar, ITRiASCmdUI *pCmdUI);
	STDMETHOD(OnSelect) (THIS_ ITRiASBar *pIBar, UINT uiID, LPSTR pBuffer, ULONG uiLen, ULONG *pulWritten);
	STDMETHOD(OnCommand) (THIS_ ITRiASBar *pIBar, UINT uiID, int nCode);
};
