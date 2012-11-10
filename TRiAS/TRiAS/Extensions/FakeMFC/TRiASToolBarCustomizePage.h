///////////////////////////////////////////////////////////////////////////
// @doc 
// @module TRiASToolBarCustomizePage.h | Description goes here

#if !defined(_TRIASTOOLBARCUSTOMIZEPAGE_H__A213557D_B102_11D2_95A2_006008447800__INCLUDED_)
#define _TRIASTOOLBARCUSTOMIZEPAGE_H__A213557D_B102_11D2_95A2_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "TRiASCustomizeToolBar.h"
#include "PropPageExt.h"

// {A213557E-B102-11D2-95A2-006008447800}
extern "C" const CLSID __declspec(selectany) CLSID_TRiASToolBarCustomizePage = 
	{0xa213557e,0xb102,0x11d2,{0x95,0xa2,0x00,0x60,0x08,0x44,0x78,0x00}};

////////////////////////////////////////////////////////////////////////////
// Customizing von Toolbars

class ATL_NO_VTABLE CTRiASToolBarCustomizePage : 
	public CPropPageExt<CTRiASCustomizeToolBar>,
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CTRiASToolBarCustomizePage, &CLSID_TRiASToolBarCustomizePage>
{
public:
	CTRiASToolBarCustomizePage()
	{
	}

	BEGIN_COM_MAP(CTRiASToolBarCustomizePage)
		COM_INTERFACE_ENTRY(ITriasPropSheetExt)
		COM_INTERFACE_ENTRY(ITriasExtInit)
	END_COM_MAP()

	DECLARE_REGISTRY_RESOURCEID(IDR_TOOLBARCUSTOMIZE_REG)
};

#endif // !defined(_TRIASTOOLBARCUSTOMIZEPAGE_H__A213557D_B102_11D2_95A2_006008447800__INCLUDED_)
