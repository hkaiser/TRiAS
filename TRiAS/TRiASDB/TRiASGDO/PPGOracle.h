// PPGOracle.h : Declaration of the CPPGOracle

#ifndef __PPGORACLE_H_
#define __PPGORACLE_H_

EXTERN_C const CLSID CLSID_PPGOracle;

/////////////////////////////////////////////////////////////////////////////
// CPPGOracle
class ATL_NO_VTABLE CPPGOracle :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPPGOracle, &CLSID_PPGOracle>,
	public IPropertyPageImpl<CPPGOracle>,
	public CDialogImpl<CPPGOracle>
{
public:
	CPPGOracle() 
	{
		m_dwTitleID = IDS_TITLEPPGOracle;
		m_dwHelpFileID = IDS_HELPFILEPPGOracle;
		m_dwDocStringID = IDS_DOCSTRINGPPGOracle;
	}

	enum {IDD = IDD_PPGORACLE};

	DECLARE_REGISTRY_RESOURCEID(IDR_PPGORACLE)
	DECLARE_NOT_AGGREGATABLE(CPPGOracle)

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CPPGOracle) 
		COM_INTERFACE_ENTRY(IPropertyPage)
	END_COM_MAP()

	BEGIN_MSG_MAP(CPPGOracle)
		CHAIN_MSG_MAP(IPropertyPageImpl<CPPGOracle>)
	END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	STDMETHOD(Apply)(void)
	{
		ATLTRACE(_T("CPPGOracle::Apply\n"));
		for (UINT i = 0; i < m_nObjects; i++)
		{
			// Do something interesting here
			// ICircCtl* pCirc;
			// m_ppUnk[i]->QueryInterface(IID_ICircCtl, (void**)&pCirc);
			// pCirc->put_Caption(CComBSTR("something special"));
			// pCirc->Release();
		}
		m_bDirty = FALSE;
		return S_OK;
	}
};

#endif //__PPGORACLE_H_
