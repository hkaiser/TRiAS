// TRiASCSPpg.h : Declaration of the CTRiASCSPpg

#ifndef __TRIASCSPPG_H_
#define __TRIASCSPPG_H_

#include "resource.h"       // main symbols

EXTERN_C const CLSID CLSID_TRiASCSPpg;

/////////////////////////////////////////////////////////////////////////////
// CTRiASCSPpg
class ATL_NO_VTABLE CTRiASCSPpg :
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CTRiASCSPpg, &CLSID_TRiASCSPpg>,
	public IPropertyPageImpl<CTRiASCSPpg>,
	public CDialogImpl<CTRiASCSPpg>
{
public:
	CTRiASCSPpg() 
	{
		m_dwTitleID = IDS_TITLETRiASCSPpg;
		m_dwHelpFileID = IDS_HELPFILETRiASCSPpg;
		m_dwDocStringID = IDS_DOCSTRINGTRiASCSPpg;
	}
	HRESULT	FinalConstruct();
	void FinalRelease();

	enum {IDD = IDD_TRIASCSPPG};

	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASCSPPG)
	DECLARE_NOT_AGGREGATABLE(CTRiASCSPpg)

	BEGIN_COM_MAP(CTRiASCSPpg) 
		COM_INTERFACE_ENTRY_IMPL(IPropertyPage)
	END_COM_MAP()

	BEGIN_MSG_MAP(CTRiASCSPpg)
		CHAIN_MSG_MAP(IPropertyPageImpl<CTRiASCSPpg>)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_RANGE_HANDLER(IDC_CHECKCS_GCS,IDC_CHECKCS_PCS,OnCSChange)
	END_MSG_MAP()

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnCSChange(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
		SetDirty(TRUE);
		return 0;
	}
	STDMETHOD(Apply)(void);
};

#endif //__TRIASCSPPG_H_
