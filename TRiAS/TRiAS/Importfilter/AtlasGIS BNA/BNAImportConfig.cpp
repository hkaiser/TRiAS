// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 22.04.2002 17:33:24 
//
// @doc
// @module BNAImportConfig.cpp | Definition of the <c CBNAImportConfig> class

#include "bnaimpp.hpp"
#include "bnaimp.h"
#include "bnapars.h"

#include "BNAImportConfig.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBNAImportConfig

// Constructor
CBNAImportConfig::CBNAImportConfig() :
	m_pCfgDlg(NULL), m_pStatusDlg(NULL), 
	m_uiPageCount(0), m_fFilesParsed(false),
	m_dwFlags(0),
	m_hPr(NULL)
{
}

// Destructor
CBNAImportConfig::~CBNAImportConfig()
{
	DELETE_OBJ(m_pStatusDlg);
	DELETE_OBJ(m_pCfgDlg);
}

///////////////////////////////////////////////////////////////////////////////
// 
STDMETHODIMP CBNAImportConfig::AddPages (LPFNADDPROPSHEETPAGE lpfnAddPage, 
	LPARAM lParam)
{
	if (NULL == lpfnAddPage)
		return E_POINTER;

HPROPSHEETPAGE hPSP = NULL;
ResourceFile RF(g_pDLLName);
ResString resCap (ResID(IDS_ASSOCIATE_LAYERS_CAP, &RF), 64);

// Status-Page hinzufügen
	m_pStatusDlg = CBNAProgressDlg::CreateInstance(resCap.Addr(), this);
	if (NULL == m_pStatusDlg)
		return E_OUTOFMEMORY;

	hPSP = m_pStatusDlg -> CreatePage();
	if ((*lpfnAddPage) (hPSP, lParam))
		++m_uiPageCount;
	else {
		DELETE_OBJ(m_pStatusDlg);
		return E_FAIL;
	}

// Config-Page hinzufügen
	m_pCfgDlg = CBNAConfigDlg::CreateInstance(resCap.Addr(), this);
	if (NULL == m_pCfgDlg)
		return E_OUTOFMEMORY;

	hPSP = m_pCfgDlg -> CreatePage();
	if ((*lpfnAddPage) (hPSP, lParam))
		++m_uiPageCount;
	else {
		DELETE_OBJ(m_pCfgDlg);
		return E_FAIL;
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// 
STDMETHODIMP CBNAImportConfig::get_StartPageId (UINT *puiStartPageId)
{
	if (NULL == puiStartPageId)
		return E_POINTER;

	*puiStartPageId = CBNAProgressDlg::IDD;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Eigentliche Informationsbearbeitung
HRESULT CBNAImportConfig::StoreLayer(string const &rLayerName, DWORD dwType)
{
	// DOS-Flag beachten
	if ((m_dwFlags & TOIMPORT_ANSIOEM )) {

		char oBuff[_MAX_PATH];

		OemToChar ( rLayerName.c_str(),(LPTSTR)oBuff);

		StoreInOKSTree((LPCSTR)oBuff, dwType, m_hPr, false);
	} else
		StoreInOKSTree(rLayerName.c_str(), dwType, m_hPr, false);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Daten aus Registry einlesen
HRESULT CBNAImportConfig::InitConfigDataFromRegistry()
{
	return ((CImpBnaExtension *)g_pTE) -> InitConfigDataFromRegistry();
}

///////////////////////////////////////////////////////////////////////////////
// Alle globalen Daten rücksetzen
void CBNAImportConfig::ResetData()
{
	ResetKeyTree();
	ResetMemoTree();
	ResetOKSTree();
}

///////////////////////////////////////////////////////////////////////////////
// Feststellen, ob ProgressDlg genutzt werden soll
//BOOL CBNAImportConfig::UseProgressDlg()
//{
//ULONG ulCount = 0;
//LPOLESTR poleString = NULL;
//WEnumString Enum;
//
//	if (FAILED(m_Files -> Clone(Enum.ppi())))
//		return TRUE;	// im Zweifelsfalle benutzen
//
//	for (Enum -> Reset(); S_OK == Enum -> Next(1, &poleString, NULL); /**/) {
//		++ulCount;
//		CoTaskMemFree(poleString);
//	}
//	return (GetFilesParsed() || 1 == ulCount) ? FALSE : TRUE;
//}


