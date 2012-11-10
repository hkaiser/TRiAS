// TRiASPCSPpg.h : Declaration of the CTRiASPCSPpg

#ifndef __TRIASPCSPPG_H_
#define __TRIASPCSPPG_H_

#include "resource.h"       // main symbols

EXTERN_C const CLSID CLSID_TRiASPCSPpg;

/////////////////////////////////////////////////////////////////////////////
// CTRiASPCSPpg
class ATL_NO_VTABLE CTRiASPCSPpg :
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CTRiASPCSPpg, &CLSID_TRiASPCSPpg>,
	public IPropertyPageImpl<CTRiASPCSPpg>,
	public CDialogImpl<CTRiASPCSPpg>
{
	HRESULT	UpdateControls();
	HRESULT UpdatePCS () {
		WTRiASCS					pCS;
		WTRiASCSPCS					pPCS;
		RETURN_FAILED_HRESULT( m_ppUnk[0]->QueryInterface(IID_ITRiASCS, pCS.ppv()) );
		RETURN_FAILED_HRESULT( pCS->get_ProjectedCS( pPCS.ppi() ) );
		HWND	hcombo = GetDlgItem( IDC_PROJECTIONALGORITHM );
		int	sel = ::SendMessage( hcombo, CB_GETCURSEL, 0, 0 );
		TRIASCSPROJECTIONALGORITHM	pa = (TRIASCSPROJECTIONALGORITHM) ::SendMessage( hcombo, CB_GETITEMDATA, sel, 0 );
		_ASSERTE( tcsPA_Undefined != pa );
		RETURN_FAILED_HRESULT( pPCS->put_ProjectionAlgorithm( pa ) );
		return S_OK;
	}
public:
	CTRiASPCSPpg()  {
		m_dwTitleID = IDS_TITLETRiASPCSPpg;
		m_dwHelpFileID = IDS_HELPFILETRiASPCSPpg;
		m_dwDocStringID = IDS_DOCSTRINGTRiASPCSPpg;
	}
	HRESULT	FinalConstruct();
	void FinalRelease();

	enum {IDD = IDD_TRIASPCSPPG};

	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASPCSPPG)
	DECLARE_NOT_AGGREGATABLE(CTRiASPCSPpg)

	BEGIN_COM_MAP(CTRiASPCSPpg) 
		COM_INTERFACE_ENTRY_IMPL(IPropertyPage)
	END_COM_MAP()

	BEGIN_MSG_MAP(CTRiASPCSPpg)
		CHAIN_MSG_MAP(IPropertyPageImpl<CTRiASPCSPpg>)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_HANDLER(IDC_PROJECTIONALGORITHM, CBN_SELCHANGE, OnSelChange)
	END_MSG_MAP()

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSelChange(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
		UpdatePCS();
		UpdateControls();
		SetDirty(TRUE);
		return 0;
	}
	STDMETHOD(Apply)(void);
};

#endif //__TRIASPCSPPG_H_
