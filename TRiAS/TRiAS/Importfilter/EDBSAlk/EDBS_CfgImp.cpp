// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 05.09.2000 20:22:16
//
// @doc
// @module EDBS_CfgImp.cpp | Implementation of the <c CEDBS_CfgImp> class

#include "stdafx.h"

#include "edbs.hpp"
#include "EDBS_Cfg.h"
#include "EDBS_CfgImp.h"
#include "resource.h"

CEDBS_CfgImp::CEDBS_CfgImp()
{
	m_uiPageCount = 0;
	pConfiguration = &((CEDBSExtension*)g_pTE)->Configuration;

	m_pPrpOBAK = NULL;
	m_pPrpObjects = NULL;
#if defined(_USE_CONFIG_DIALOGS)
	m_pPrpCommon = NULL;
#endif // defined(_USE_CONFIG_DIALOGS)
//	pConfiguration->Load();
}

CEDBS_CfgImp::~CEDBS_CfgImp()
{
	DELETE_OBJ(m_pPrpOBAK);
	DELETE_OBJ(m_pPrpObjects);
#if defined(_USE_CONFIG_DIALOGS)
	DELETE_OBJ(m_pPrpCommon);
#endif // defined(_USE_CONFIG_DIALOGS)
}

HRESULT CEDBS_CfgImp::InitForImportDialog(THIS_ IImportGeoData *pIImport, BSTR Caption, UINT dwFlags)
{
	USES_CONVERSION;
	m_strCaption = OLE2A(Caption);
	m_uiFlags = dwFlags;
	return S_OK;
}

HRESULT CEDBS_CfgImp::get_PageCount(THIS_ UINT *puiCnt)
{
	*puiCnt = m_uiPageCount;
	return S_OK;
}

HRESULT CEDBS_CfgImp::put_SelectedFiles(THIS_ IEnumString *pEnumFiles)
{
	return S_OK;
}

HRESULT CEDBS_CfgImp::AddPages(THIS_ LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam)
{
HPROPSHEETPAGE hPSP = NULL;

	try {
	// Page erzeugen
		m_pPrpOBAK = new CEDBS_CfgImpOBAK();
		if( NULL == m_pPrpOBAK )
			_com_issue_error(E_OUTOFMEMORY);
		else {
			m_pPrpOBAK->m_pConfiguration = pConfiguration;
			hPSP = CreatePropertySheetPage ((PROPSHEETPAGE *)&m_pPrpOBAK->m_psp); 
	// Page hinzufügen
			if( (*lpfnAddPage) (hPSP, lParam) )
				m_uiPageCount++;
			else
				_com_issue_error(E_FAIL);
		}
#if defined(_USE_CONFIG_DIALOGS)
	// Page erzeugen
		m_pPrpCommon = new CEDBS_CfgImpCmn();
		if( NULL == m_pPrpCommon )
			_com_issue_error(E_OUTOFMEMORY);
		else {
			m_pPrpCommon->m_pConfiguration = pConfiguration;
			hPSP = CreatePropertySheetPage ((PROPSHEETPAGE *)&m_pPrpCommon->m_psp); 
	// Page hinzufügen
			if( (*lpfnAddPage) (hPSP, lParam) )
				m_uiPageCount++;
			else
				_com_issue_error(E_FAIL);
		}
#endif // defined(_USE_CONFIG_DIALOGS)

	// Page erzeugen
		m_pPrpObjects = new CEDBS_CfgImpObj();
		if( NULL == m_pPrpObjects )
			_com_issue_error(E_OUTOFMEMORY);
		else {
			m_pPrpObjects->m_pConfiguration = pConfiguration;
			hPSP = CreatePropertySheetPage ((PROPSHEETPAGE *)&m_pPrpObjects->m_psp); 
	// Page hinzufügen
			if( (*lpfnAddPage) (hPSP, lParam) )
				m_uiPageCount++;
			else
				_com_issue_error(E_FAIL);
		}
		
	} catch (CException &e) {
		DELETE_OBJ(m_pPrpOBAK);
		DELETE_OBJ(m_pPrpObjects);
#if defined(_USE_CONFIG_DIALOGS)
		DELETE_OBJ(m_pPrpCommon);
#endif // defined(_USE_CONFIG_DIALOGS)
		e.ReportError();
	} catch (_com_error &) {
		DELETE_OBJ(m_pPrpOBAK);
		DELETE_OBJ(m_pPrpObjects);
#if defined(_USE_CONFIG_DIALOGS)
		DELETE_OBJ(m_pPrpCommon);
#endif // defined(_USE_CONFIG_DIALOGS)
	}
	return S_OK;
}

HRESULT CEDBS_CfgImp::ReplacePage (THIS_ UINT uPageID, LPFNADDPROPSHEETPAGE lpfnReplacePage, LPARAM lParam)
{
	return E_NOTIMPL;
}
