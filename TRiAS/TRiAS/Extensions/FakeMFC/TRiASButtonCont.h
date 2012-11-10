// TRiASButtonCont.h: Definition of the CTRiASButtonCont class
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRIASBUTTONCONT_H__3963E3A3_B249_11D0_955D_00A024D6F582__INCLUDED_)
#define AFX_TRIASBUTTONCONT_H__3963E3A3_B249_11D0_955D_00A024D6F582__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "fakemfc.h"

/////////////////////////////////////////////////////////////////////////////
// CTRiASButtonCont

class CTRiASButtonCont : 
	public CComDualImpl<DControlToolBarButtons, &IID_DControlToolBarButtons, &LIBID_ToolBarLib,
				TOOLBAR_TYPELIB_VERSION_MAJOR, TOOLBAR_TYPELIB_VERSION_MINOR>,
	public ISupportErrorInfo,
	public CComObjectRoot
{
public:
	CTRiASButtonCont() {}
	~CTRiASButtonCont() {}

	BEGIN_COM_MAP(CTRiASButtonCont)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(DControlToolBarButtons)
		COM_INTERFACE_ENTRY_IID(IID_DTRiASCollection, DControlToolBarButtons)
		COM_INTERFACE_ENTRY_IID(IID_DTRiASBaseClass, DControlToolBarButtons)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()
	
	DECLARE_NOT_AGGREGATABLE(CTRiASButtonCont) 

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// DControlToolBarButtons
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

protected:
	CComPtr<IDispatch> m_Parent;	// für Einbindung in OleAutomation
	CComPtr<IDispatch> m_App;

public:
};

#endif // !defined(AFX_TRIASBUTTONCONT_H__3963E3A3_B249_11D0_955D_00A024D6F582__INCLUDED_)
