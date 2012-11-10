// DispUIOwner.h: Declaration of CDispUIOwner

#if !defined(_DISPUIOWNER_H)
#define _DISPUIOWNER_H

///////////////////////////////////////////////////////////////////////////////
// spezielle SmartInterfaces
DefineSmartInterface2(DToolBarUIOwner, IID_DToolBarUIOwner);

class CDispUIOwner : 
	public ITRiASUIOwner,
	public CComObjectRoot
//	public CComObjectBase<&CLSID_TRiASUIOwner>
{
public:
		CDispUIOwner() {}
		~CDispUIOwner() {}

	BEGIN_COM_MAP(CDispUIOwner)
		COM_INTERFACE_ENTRY(ITRiASUIOwner)
	END_COM_MAP()

	DECLARE_NOT_AGGREGATABLE(CDispUIOwner)

	HRESULT SetTargetUIOwner (DToolBarUIOwner *pIDispUI);

public:
// *** ITRiASUIOwner specific functions ***
	STDMETHOD(OnUpdateUI) (THIS_ ITRiASBar *pIBar, ITRiASCmdUI *pCmdUI);
	STDMETHOD(OnSelect) (THIS_ ITRiASBar *pIBar, UINT uiID, LPSTR pBuffer, ULONG uiLen, ULONG *pulWritten);
	STDMETHOD(OnCommand) (THIS_ ITRiASBar *pIBar, UINT uiID, int nCode);

private:
	WDToolBarUIOwner m_TargetUIOwner;
};

#endif // _DISPUIOWNER_H
