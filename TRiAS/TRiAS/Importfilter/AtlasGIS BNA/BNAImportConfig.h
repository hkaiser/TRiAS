// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 22.04.2002 17:36:28 
//
// @doc
// @module BNAImportConfig.h | Declaration of the <c CBNAImportConfig> class

#if !defined(_BNAIMPORTCONFIG_H__245B92DF_9331_4AB2_8684_1CA0F6D1A94B__INCLUDED_)
#define _BNAIMPORTCONFIG_H__245B92DF_9331_4AB2_8684_1CA0F6D1A94B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"

#include "bnapars.h"
#include "BNAConfigDlg.h"
#include "BNAProgressDlg.h"

DefineSmartInterface(EnumString);			// WEnumString

/////////////////////////////////////////////////////////////////////////////
// CBNAImportConfig

class ATL_NO_VTABLE CBNAImportConfig : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CBNAImportConfig, &CLSID_BNAImportConfig>,
	public ITriasPropSheetExt,
	public ITRiASImportWizardPropExt2
{
public:
// Construction
	CBNAImportConfig();
	~CBNAImportConfig();

// Initialisation

// Operations
	DECLARE_REGISTRY_RESOURCEID(IDR_BNAIMPORTCONFIG_REG)
	DECLARE_PROTECT_FINAL_CONSTRUCT()

	// Interface map
	BEGIN_COM_MAP(CBNAImportConfig)
		COM_INTERFACE_ENTRY(ITriasPropSheetExt)
		COM_INTERFACE_ENTRY(ITRiASImportWizardPropExt)
		COM_INTERFACE_ENTRY(ITRiASImportWizardPropExt2)
	END_COM_MAP()

	bool GetFilesParsed() { return m_fFilesParsed; }
	void SetFilesParsed(bool fFlag) { m_fFilesParsed = fFlag; }

	UINT GetFirstPageId() { return m_uiFirstPageId; }
	HRESULT GetEnumFiles (IEnumString **ppIEnum)
	{
		if (NULL == ppIEnum)
			return E_POINTER;
		return (*ppIEnum = m_Files) -> AddRef(), S_OK;
	}

	HRESULT StoreLayer (string const &rLayerName, DWORD dwType);
	HRESULT InitConfigDataFromRegistry();
	void ResetData();

//	BOOL UseProgressDlg();
	HPROJECT GetContextHandle() { return m_hPr; }

// Implementation
protected:
// Attributes

// Operations

// Interfaces
public:
// ITriasPropSheetExt
	STDMETHOD(AddPages)(THIS_ LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam);
	STDMETHOD(ReplacePage)(THIS_ UINT uPageID, LPFNADDPROPSHEETPAGE lpfnReplacePage, LPARAM lParam)
	{
		return E_NOTIMPL;
	}

// ITRiASImportWizardPropExt
	STDMETHOD(InitForImportDialog)(THIS_ IImportGeoData *pIImport, BSTR Caption, UINT dwFlags)
	{
	// alles wieder aufräumen
		ResetKeyTree();			// Konf_Daten_Baum wieder raus
		ResetMemoTree();		// MemoKlassen_Baum wieder raus
		ResetOKSTree();			// BNAKlassen_Baum wieder raus
		return S_OK;
	}
	STDMETHOD(get_PageCount)(THIS_ UINT *puiCnt)
	{
		if (NULL == puiCnt)
			return E_POINTER;
		*puiCnt = m_uiPageCount;
		return S_OK;
	}
	STDMETHOD(put_SelectedFiles)(THIS_ IEnumString *pEnumFiles)
	{
		if (NULL == pEnumFiles)
			return E_POINTER;

		m_Files = pEnumFiles;
		m_fFilesParsed = false;
		return S_OK;
	}

// ITRiASImportWizardPropExt2
	STDMETHOD(put_FirstPageId)(THIS_ UINT uiFirstPageId)
	{
		m_uiFirstPageId = uiFirstPageId;
		return S_OK;
	}
	STDMETHOD(get_StartPageId)(THIS_ UINT *puiStartPageId);
	STDMETHOD(put_ContextHandle)(THIS_ INT_PTR hPr)
	{
		m_hPr = (HPROJECT)hPr;
		return S_OK;
	}
	STDMETHOD(put_ImportFlags)(THIS_ DWORD dwFlags)
	{
		m_dwFlags = dwFlags;
		return S_OK;
	}

private:
	CBNAConfigDlg *m_pCfgDlg;
	CBNAProgressDlg *m_pStatusDlg;
	UINT m_uiPageCount;			// Anzahl der eingehängten Seiten

	bool m_fFilesParsed;		// Dateien wurden bereits geparst
	UINT m_uiFirstPageId;		// PageID der ersten anzuzeigenden Seite

	WEnumString m_Files;		// zu bearbeitende Dateien
	HPROJECT m_hPr;
	DWORD m_dwFlags;			// ausgewählte Importoptionen
};

#endif // !defined(_BNAIMPORTCONFIG_H__245B92DF_9331_4AB2_8684_1CA0F6D1A94B__INCLUDED_)
