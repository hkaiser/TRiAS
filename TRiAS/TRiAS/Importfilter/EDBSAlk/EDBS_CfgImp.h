// EDBS_CfgImp.h : Deklaration von CEDBS_CfgImp

#ifndef __EDBS_CFGIMP_H_
#define __EDBS_CFGIMP_H_

#include <atlcom.h>

#include "resource.h"       // Hauptsymbole
#include <xtension.h>
#include <Ixtensn.hxx>
#include <Ixtnext.hxx>

#include "Cfg.h"
#include "EDBS_CfgImpOBAK.h"
#include "EDBS_CfgImpCmn.h"
#include "EDBS_CfgImpObj.h"

/////////////////////////////////////////////////////////////////////////////
// CEDBS_CfgImp
class ATL_NO_VTABLE CEDBS_CfgImp :
#if defined(__ATL_11_USED__)
	public CComObjectRoot,
#else
	public CComObjectRootEx<CComSingleThreadModel>,
#endif
	public CComCoClass<CEDBS_CfgImp, &CLSID_EDBS_CfgImp>,
#if _TRiAS_VER >= 0x300
	public ITRiASImportWizardPropExt,
#endif
	public ITriasPropSheetExt,
	public IDispatchImpl<IEDBS_CfgImp, &IID_IEDBS_CfgImp, &LIBID_EDBS_CFGLib>
{
protected:
	CString			m_strCaption;
	UINT			m_uiFlags;
	UINT			m_uiPageCount;
	CEDBS_CfgImpOBAK	*m_pPrpOBAK;
#if defined(_USE_CONFIG_DIALOGS)
	CEDBS_CfgImpCmn	*m_pPrpCommon;
#endif // defined(_USE_CONFIG_DIALOGS)
	CEDBS_CfgImpObj	*m_pPrpObjects;
	CCfg			*pConfiguration;

public:
	CEDBS_CfgImp();
	~CEDBS_CfgImp();

DECLARE_REGISTRY_RESOURCEID(IDR_EDBS_CFGIMP)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CEDBS_CfgImp)
	COM_INTERFACE_ENTRY(IEDBS_CfgImp)
#if _TRiAS_VER >= 0x300
	COM_INTERFACE_ENTRY(ITRiASImportWizardPropExt)
	COM_INTERFACE_ENTRY(ITriasPropSheetExt)
#endif
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// ITRiASImportWizardPropExt
	STDMETHOD(InitForImportDialog) (THIS_ IImportGeoData *pIImport, BSTR Caption, UINT dwFlags);
	STDMETHOD(get_PageCount) (THIS_ UINT *puiCnt);
	STDMETHOD(put_SelectedFiles) (THIS_ IEnumString *pEnumFiles);

// ITriasPropSheetExt
	STDMETHOD(AddPages) (THIS_ LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam);
	STDMETHOD(ReplacePage) (THIS_ UINT uPageID, LPFNADDPROPSHEETPAGE lpfnReplacePage, LPARAM lParam);

// IEDBS_CfgImp
public:

};

#endif //__EDBS_CFGIMP_H_
