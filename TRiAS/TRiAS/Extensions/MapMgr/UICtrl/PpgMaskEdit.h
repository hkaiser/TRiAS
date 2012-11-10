#ifndef __PPGMASKEDITX_H_
#define __PPGMASKEDITX_H_

#include "resource.h"       // main symbols
#include "MaskEdit.h"

//EXTERN_C const CLSID CLSID_PpgMaskEditX;

/////////////////////////////////////////////////////////////////////////////
// CPpgMaskEdit
class ATL_NO_VTABLE CPpgMaskEdit :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPpgMaskEdit, &CLSID_PpgMaskEdit>,
	public IPropertyPageImpl<CPpgMaskEdit>,
	public CDialogImpl<CPpgMaskEdit>
{
public:
	CPpgMaskEdit() 
	{
		m_dwTitleID = IDS_TITLEPpgMaskEditX;
		m_dwHelpFileID = IDS_HELPFILEPpgMaskEditX;
		m_dwDocStringID = IDS_DOCSTRINGPpgMaskEditX;
	}

	enum {IDD = IDD_PPGMASKEDITX};

	DECLARE_REGISTRY_RESOURCEID(IDR_PPGMASKEDITX)

	BEGIN_COM_MAP(CPpgMaskEdit) 
		COM_INTERFACE_ENTRY_IMPL(IPropertyPage)
	END_COM_MAP()

	BEGIN_MSG_MAP(CPpgMaskEdit)
		CHAIN_MSG_MAP(IPropertyPageImpl<CPpgMaskEdit>)
		COMMAND_HANDLER( IDC_EDIT_MASK, EN_CHANGE, OnChangeMask )
		MESSAGE_HANDLER( WM_INITDIALOG, OnInitDialog )
	END_MSG_MAP()

	LRESULT OnChangeMask(WORD wNotify, WORD wID, HWND hWnd, BOOL& bHandled) {
		SetDirty(TRUE);
		return 0;
	}
	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	STDMETHOD(Apply)(void);
};

#endif //__PPGMASKEDITX_H_
