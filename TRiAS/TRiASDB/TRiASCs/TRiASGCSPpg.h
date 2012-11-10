// TRiASGCSPpg.h : Declaration of the CTRiASGCSPpg

#ifndef __TRIASGCSPPG_H_
#define __TRIASGCSPPG_H_

#include "resource.h"       // main symbols

EXTERN_C const CLSID CLSID_TRiASGCSPpg;

/////////////////////////////////////////////////////////////////////////////
// CTRiASGCSPpg
class ATL_NO_VTABLE CTRiASGCSPpg :
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CTRiASGCSPpg, &CLSID_TRiASGCSPpg>,
	public IPropertyPageImpl<CTRiASGCSPpg>,
	public CDialogImpl<CTRiASGCSPpg>
{
	void UpdateControls();
	void RecalcEllipsoid(TRIASCSELLIPSOID el);
	bool	m_bUserDefined;
public:
	CTRiASGCSPpg()  {
		m_dwTitleID = IDS_TITLETRiASGCSPpg;
		m_dwHelpFileID = IDS_HELPFILETRiASGCSPpg;
		m_dwDocStringID = IDS_DOCSTRINGTRiASGCSPpg;
		m_bUserDefined = false;
	}

	HRESULT	FinalConstruct();
	void FinalRelease();

	enum { IDD = IDD_TRIASGCSPPG };

	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASGCSPPG)
	DECLARE_NOT_AGGREGATABLE(CTRiASGCSPpg)

	BEGIN_COM_MAP(CTRiASGCSPpg) 
		COM_INTERFACE_ENTRY_IMPL(IPropertyPage)
	END_COM_MAP()

	BEGIN_MSG_MAP(CTRiASGCSPpg)
		CHAIN_MSG_MAP(IPropertyPageImpl<CTRiASGCSPpg>)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_HANDLER(IDC_GEODETIC_DATUM, CBN_SELCHANGE, OnSelChange)
		COMMAND_HANDLER(IDC_ELLIPSOID, CBN_SELCHANGE, OnSelChange)
		COMMAND_HANDLER(IDC_EDIT_SEMI_MAJOR, EN_CHANGE, OnEditChange)
		COMMAND_HANDLER(IDC_EDIT_SEMI_MINOR, EN_CHANGE, OnEditChange)
	END_MSG_MAP()

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnEditChange(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
		if( m_bUserDefined ) {
			UpdateControls();
			SetDirty(TRUE);
		}
			return 0;
	}
	LRESULT OnSelChange(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
		UpdateControls();
		SetDirty(TRUE);
		return 0;
	}
	STDMETHOD(Apply)(void);
};

#endif //__TRIASGCSPPG_H_
