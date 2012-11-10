// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 28.08.99 21:26:52 
//
// @doc
// @module ObjectPropertyPP.h | Declaration of the <c CObjectPropertyPP> class

#if !defined(_OBJECTPROPERTYPP_H__8319BE80_5D7E_11D3_9504_0080C786297B__INCLUDED_)
#define _OBJECTPROPERTYPP_H__8319BE80_5D7E_11D3_9504_0080C786297B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"       // main symbols
#include "SymbolMap.h"      // the ISymbolMap interface

EXTERN_C const CLSID CLSID_ObjectPropertyPP;

///////////////////////////////////////////////////////////////////////////////
// 
const UINT PROPERTY_Writable = 0x01;
const UINT PROPERTY_CanConfigure = 0x02;
const UINT PROPERTY_PersistOwnData = 0x04;

extern const CONTROL __declspec(selectany) g_TRiASOP[] =
{
	{ PROPERTY_Writable, IDC_WRITABLE, false },
	{ PROPERTY_CanConfigure, IDC_CANCONFIGURE, false },
	{ PROPERTY_PersistOwnData, IDC_PERSISTSTREAM, true },
	{ 0, 0 },
};

/////////////////////////////////////////////////////////////////////////////
// CObjectPropertyPP
class ATL_NO_VTABLE CObjectPropertyPP :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CObjectPropertyPP, &CLSID_ObjectPropertyPP>,
	public IPropertyPageImpl<CObjectPropertyPP>,
	public CDialogImpl<CObjectPropertyPP>
{
public:
	CObjectPropertyPP() 
	{
		m_dwTitleID = IDS_TITLEOBJECTPROPERTY;
		m_dwHelpFileID = IDS_HELPFILEOBJECTPROPERTY;
		m_dwDocStringID = IDS_DOCSTRINGOBJECTPROPERTY;
		m_bActivated = false;
	}

	enum {IDD = IDD_OBJECTPROPERTYPP};

	DECLARE_REGISTRY_RESOURCEID(IDR_OBJECTPROPERTYPP)

	BEGIN_COM_MAP(CObjectPropertyPP) 
		COM_INTERFACE_ENTRY_IMPL(IPropertyPage)
	END_COM_MAP()

	BEGIN_MSG_MAP(CObjectPropertyPP)
		CHAIN_MSG_MAP(IPropertyPageImpl<CObjectPropertyPP>)
	END_MSG_MAP()

	bool m_bActivated;

	STDMETHOD(SetObjects)(ULONG nObjects, IUnknown **ppUnk)
	{
		ATLTRACE(_T("CObjectPropertyPP::SetObjects\n"));
		HRESULT hres = IPropertyPageImpl<CObjectPropertyPP>::SetObjects(nObjects, ppUnk);
		if (SUCCEEDED(hres))
		{
			// Loop through any objects and keep the first one that has an ISymbolMap interface
			for (UINT i = 0; i < m_nObjects; i++)
			{
				ISymbolMap* pMap = NULL;
				if (SUCCEEDED(m_ppUnk[i]->QueryInterface(__uuidof(ISymbolMap), (void**)&pMap)))
				{
				// Zeit voreinstellen
				char buf[128];
				time_t timeval;

					time(&timeval);
					buf[strftime(buf, sizeof(buf) - 1, "%d.%m.%Y %H:%M:%S", localtime(&timeval))] = 0;
					pMap -> Set (CComBSTR("DateAndTime"), CComBSTR(buf));
					pMap -> Release();
					break;
				}
			}
		}
		return hres;
	}

	STDMETHOD(Activate)(HWND hWndParent, LPCRECT prc, BOOL bModal)
	{
		ATLTRACE(_T("CObjectPropertyPP::Activate\n"));
		m_bActivated = true;
		HRESULT hres = IPropertyPageImpl<CObjectPropertyPP>::Activate(hWndParent, prc, bModal);
		if (SUCCEEDED(hres))
		{
			// Loop through any objects and keep the first one that has an ISymbolMap interface
			for (UINT i = 0; i < m_nObjects; i++)
			{
				ISymbolMap* pMap = NULL;
				if (SUCCEEDED(m_ppUnk[i]->QueryInterface(__uuidof(ISymbolMap), (void**)&pMap)))
				{
					HRESULT hresActivate = OnPageActivate(pMap);
					pMap->Release();
					return hresActivate;
				}
			}
		}
		return hres; 
	}
	STDMETHOD(Apply)(void)
	{
		ATLTRACE(_T("CObjectPropertyPP::Apply\n"));
		// Loop through any objects and keep the first one that has an ISymbolMap interface
		for (UINT i = 0; i < m_nObjects; i++)
		{
			ISymbolMap* pMap = NULL;
			if (SUCCEEDED(m_ppUnk[i]->QueryInterface(__uuidof(ISymbolMap), (void**)&pMap)))
			{
				HRESULT hresApply = S_OK;
				if (m_bActivated)
					 hresApply = OnPageApply(pMap);
				pMap->Release();
				if (SUCCEEDED(hresApply))
					m_bDirty = FALSE;
				return hresApply;
			}
		}
		return E_UNEXPECTED;
	}

	STDMETHOD(Deactivate)(void)
	{
		ATLTRACE(_T("CObjectPropertyPP::Deactivate\n"));
		if (SUCCEEDED(OnPageDeactivate()))
		{
			return IPropertyPageImpl<CObjectPropertyPP>::Deactivate();
		}
		else
		{
			IPropertyPageImpl<CObjectPropertyPP>::Deactivate();
			return E_UNEXPECTED;
		}
	}

// ******************************************************************************* //
// To use these helpers, create a string resource with the same ID as the control
// The string resource will be used as the name of the symbol and the contents of the
// control as its value.

	HRESULT SetSymbolFromCheckBox(int nID, ISymbolMap* pMap)
	{
	// Call this function to set a symbol from a check box control
	CComBSTR bstrSymbol;

		if (!bstrSymbol.LoadString (nID))
			return E_FAIL;
				
		return pMap->Set (bstrSymbol, CComBSTR(IsDlgButtonChecked(nID) ? "TRUE" : "FALSE") );
	}

	HRESULT SetSymbolFromRadiobutton(int nIDSymbol, int nID, ISymbolMap* pMap, bool fDefault = false)
	{
	// Call this function to set a symbol from a radio button control
	CComBSTR bstrSymbol;

		if (!bstrSymbol.LoadString (nID))
			return E_FAIL;

	CComBSTR bstrValue;

		if (!bstrValue.LoadString (nID))
			return E_FAIL;

		if (IsDlgButtonChecked(nID))
			return pMap->Set (bstrSymbol, bstrValue);

	CComBSTR bstr;

		if (fDefault && FAILED(pMap->Get(bstrSymbol, &bstr)))
			return pMap->Set (bstrSymbol, bstrValue);	// no value at all
		return S_FALSE;
	}

	HRESULT SetSymbolFromTextBox(int nID, ISymbolMap* pMap, int nIDDefault = 0)
	{
	// Call this function to set a symbol from a text box control
	CComBSTR bstrSymbol;

		if (!bstrSymbol.LoadString (nID))
			return E_FAIL;
				
	CComBSTR bstrValue;
	
		if (!GetDlgItemText(nID, bstrValue.m_str)) {
			if (0 == nIDDefault)
				return E_FAIL;
			if (!bstrValue.LoadString(nIDDefault))
				return E_FAIL;
		}
		return pMap->Set (bstrSymbol, bstrValue);
	}

// ******************************************************************************* //
// We can guarantee that pMap is a valid pointer to an ISymbolMap interface for both the
// OnPageAxxxx() functions.
// In fact, neither of these functions will be called if we can't get a valid pointer.

	void DisableControls (ULONG lMask)
	{
		for (const CONTROL *pCtrls = g_TRiASOP; 0 != pCtrls -> uiResID; pCtrls++) 
			::EnableWindow (GetDlgItem(pCtrls -> uiResID), (pCtrls -> uiBit & lMask) ? FALSE : TRUE);
	}

	void CheckControls (ULONG lMask)
	{
		for (const CONTROL *pCtrls = g_TRiASOP; 0 != pCtrls -> uiResID; pCtrls++) {
			if (pCtrls -> fCheck && !(pCtrls -> uiBit & lMask))
				SendMessage (GetDlgItem(pCtrls -> uiResID), BM_SETCHECK, TRUE, 0);
		}
	}

	HRESULT OnPageActivate(ISymbolMap* pMap)
	{
	// diverse Voreinstellungen
	CComBSTR bstr;

		USES_CONVERSION;
		if (bstr.LoadString (IDS_DEFAULT_NAME_OP)) 
			SetDlgItemText (IDC_OP_NAME, OLE2A(bstr));
		if (bstr.LoadString (IDS_DEFAULT_DESCRIPTION_OP)) 
			SetDlgItemText (IDC_OP_DESCRIPTION, OLE2A(bstr));

	// Controls evtl. nach Bedarf disable'n
	CComBSTR bstrAttr;
	ULONG ulMask = 0x0;

		if (SUCCEEDED(pMap -> Get(CComBSTR("ObjPropAttr"), &bstrAttr)))
			ulMask = atob (OLE2A(bstrAttr));

		DisableControls (ulMask);
		CheckControls (ulMask);
		return S_OK;
	}

	HRESULT OnPageApply(ISymbolMap* pMap)
	{
	// Description
		SetSymbolFromTextBox (IDC_OP_NAME, pMap, IDS_DEFAULT_NAME_OP);
		SetSymbolFromTextBox (IDC_OP_DESCRIPTION, pMap, IDS_DEFAULT_DESCRIPTION_OP);

	// Options
		SetSymbolFromCheckBox (IDC_WRITABLE, pMap);
		SetSymbolFromCheckBox (IDC_CANCONFIGURE, pMap);
		SetSymbolFromCheckBox (IDC_PERSISTSTREAM, pMap);

		return S_OK;
	}

	HRESULT OnPageDeactivate()
	{
		return S_OK;
	}
};

#endif // !defined(_OBJECTPROPERTYPP_H__8319BE80_5D7E_11D3_9504_0080C786297B__INCLUDED_)
