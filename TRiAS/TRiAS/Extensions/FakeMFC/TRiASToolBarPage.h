///////////////////////////////////////////////////////////////////////////
// @doc 
// @module TRiASToolBarPage.h | Description goes here

#if !defined(_TRIASTOOLBARPAGE_H__A213557D_B102_11D2_95A2_006008447800__INCLUDED_)
#define _TRIASTOOLBARPAGE_H__A213557D_B102_11D2_95A2_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "ToolBarsPage.h"
#include "PropPageExt.h"

// {A213557D-B102-11D2-95A2-006008447800}
extern "C" const CLSID __declspec(selectany) CLSID_TRiASToolBarPage = 
	{0xa213557d,0xb102,0x11d2,{0x95,0xa2,0x00,0x60,0x08,0x44,0x78,0x00}};

////////////////////////////////////////////////////////////////////////////
// Customizing von Toolbars

class ATL_NO_VTABLE CTRiASToolBarPage : 
	public CPropPageExt<CToolBarsPage>,
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CTRiASToolBarPage, &CLSID_TRiASToolBarPage>
{
public:
	CTRiASToolBarPage()
	{
	}

	BEGIN_COM_MAP(CTRiASToolBarPage)
		COM_INTERFACE_ENTRY(ITriasPropSheetExt)
		COM_INTERFACE_ENTRY(ITriasExtInit)
	END_COM_MAP()

	DECLARE_REGISTRY_RESOURCEID(IDR_TOOLBAR_REG)
};

#endif // !defined(_TRIASTOOLBARPAGE_H__A213557D_B102_11D2_95A2_006008447800__INCLUDED_)
