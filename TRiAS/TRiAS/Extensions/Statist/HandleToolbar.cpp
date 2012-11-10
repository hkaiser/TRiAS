// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 14.09.2001 10:59:39 
//
// @doc
// @module HandleToolbar.cpp | Definition of the <c CHandleToolbar> class

#include "StdAfx.h"

#include "resource.h"
#include "Statist.h"
#include "StatistUIOwner.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Toolbar verwalten
HRESULT CStatist::InitToolbar()
{
	COM_TRY {
	// Finden der ToolBar "Werkzeuge"
	WTRiASBarContainer ToolBars;

		THROW_FAILED_HRESULT(m_pXtnSite->QueryInterface (ToolBars.ppi()));

	WTRiASBar Bar;
	CString strTools;
	
		strTools.LoadString (IDS_WERKZEUGETOOLBAR);	// "Werkzeuge" ist der Name der Toolbar
		_ASSERTE(strTools.GetLength() > 0);

		THROW_FAILED_HRESULT(ToolBars -> FindTRiASBar (strTools, Bar.ppi()));

	// Hinzufügen der Buttons
	CComObject<CStatistUIOwner> *pIUIOwner = NULL;
	WTRiASToolBar ToolBar (Bar);
	int iOffset = 0;

		THROW_FAILED_HRESULT (ToolBar -> AddBitmap (g_hInstance, IDR_STATFUNC, 4, &iOffset));
		THROW_FAILED_HRESULT (CComObject<CStatistUIOwner>::CreateInstance(&pIUIOwner));
		pIUIOwner -> SetCmdTarget(this);

	// für jeden zu installierenden Button diese Struktur bereitstellen
	//				       BitmapNr   CmdID		      ButtonState ButtonStyle
	WTRiASUIOwner UIOwner (pIUIOwner);
	TBBUTTON tbStatist[] = {{ iOffset,   ID_TOOL_STATISTICS,    0,    TBSTYLE_CHECK, 0L, 0, }};
	int iOverviewIdx = -1;

		if (FAILED(ToolBar -> CommandToIndex (ID_STANDARD_OVERVIEW, &iOverviewIdx)) ||
			-1 == iOverviewIdx) {
		// ans Ende anhängen
			THROW_FAILED_HRESULT(ToolBar -> AddButtons (tbStatist, _countof(tbStatist), UIOwner));
		}
		else {
		// hinter Gesamtübersicht einfügen
			THROW_FAILED_HRESULT(ToolBar -> InsertButton (iOverviewIdx, tbStatist, UIOwner));
		}

	} COM_CATCH;
	return S_OK;
}

HRESULT CStatist::FreeToolbar()
{
	COM_TRY {
	// Finden der ToolBar "Werkzeuge"
	WTRiASBarContainer ToolBars;

		THROW_FAILED_HRESULT(m_pXtnSite->QueryInterface (ToolBars.ppi()));

	WTRiASBar Bar;
	CString strTools;
	
		strTools.LoadString (IDS_WERKZEUGETOOLBAR);	// "Werkzeuge" ist der Name der Toolbar
		_ASSERTE(strTools.GetLength() > 0);

		THROW_FAILED_HRESULT(ToolBars -> FindTRiASBar (strTools, Bar.ppi()));

	// Entfernen der Buttons
	WTRiASToolBar ToolBar(Bar);
	int iIndex = -1;

		THROW_FAILED_HRESULT (ToolBar -> CommandToIndex (ID_TOOL_STATISTICS, &iIndex));
		THROW_FAILED_HRESULT (ToolBar -> DeleteItem (iIndex));

	} COM_CATCH;
	return S_OK;
}

