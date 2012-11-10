// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 10/04/1998 09:52:50 PM
//
// @doc
// @module TRiASOptionDlg.cpp | Implementation of the <c CTRiASOptionDlg> class

#include "stdafx.h"

#include <ciid.h>

#include "UIMsg.hmc"
#include "UIUtil.h"
#include "TRiASUI.h"
#include "TRiASOptionDlg.h"

/////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(PersistStreamInit);		// WPersistStreamInit
DefineSmartInterface(Picture);					// WPicture

/////////////////////////////////////////////////////////////////////////////
// CTRiASOptionDlg

STDMETHODIMP CTRiASOptionDlg::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITRiASOptionDlg,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

HRESULT CTRiASOptionDlg::FinalConstruct()
{ 
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

// Caption initialisieren
CComBSTR bstrCaption;

	VERIFY(bstrCaption.LoadString (_Module.GetResourceInstance(), IDS_STDDIALOGCAPTION));

// Dialog anlegen, initialisieren und anzeigen
CStdCtrlDlg *pDlg = NULL;

	ATLTRY(pDlg = new CStdCtrlDlg);
	if (NULL == pDlg)
		return E_OUTOFMEMORY;

	pDlg -> SetCallback (this);
	pDlg->EnableAutomation();
	pDlg->EnableAggregation();
	pDlg->m_pOuterUnknown = static_cast<LPUNKNOWN>(GetControllingUnknown());

//LPDISPATCH _pDispatch = pDlg->GetIDispatch(FALSE);

	m_pUnkPpg = reinterpret_cast<LPUNKNOWN>(&(pDlg->m_xInnerUnknown));
	if (NULL == m_pUnkPpg) {
		delete pDlg;
		return E_UNEXPECTED;
	}

// Fenster erzeugen (ist !Visible)
//	if (!pDlg -> Create()) {
//		delete pDlg;
//		return E_UNEXPECTED;
//	}

	m_pDlg = pDlg;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersist
STDMETHODIMP CTRiASOptionDlg::GetClassID (CLSID *pClassID)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pClassID) 
		return E_POINTER;

	*pClassID = CLSID_TRiASOptionDlg;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistStream
STDMETHODIMP CTRiASOptionDlg::IsDirty (void)
{
	COM_TRY {
		THROW_FAILED_HRESULT(WPersistStreamInit(m_pUnkPpg) -> IsDirty());
	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASOptionDlg::Load (LPSTREAM pStm)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (m_fIsInitialized)
		return E_UNEXPECTED;

// Version prüfen
long lSignature = 0L;

	RETURN_FAILED_HRESULT(LoadLong (pStm, lSignature));			// Signatur
	if (TRIASOPTIONDLG_SIGNATURE != lSignature)
		return TRIASUI_E_BADOBJECTSIGNATURE;

long lVersion = 0L;

	RETURN_FAILED_HRESULT(LoadLong (pStm, lVersion));				// VersionInfo
	if (lVersion > LASTKNOWN_TRIASOPTIONDLG_VERSION)
		return TRIASUI_W_NEWERTRIASOPTIONDLG;

	COM_TRY {
		THROW_FAILED_HRESULT(WPersistStreamInit(m_pUnkPpg) -> Load(pStm));
	} COM_CATCH;

	m_fIsInitialized = true;
	return S_OK;
}

STDMETHODIMP CTRiASOptionDlg::Save (LPSTREAM pStm, BOOL fClearDirty)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	COM_TRY {
		THROW_FAILED_HRESULT(SaveLong (pStm, TRIASOPTIONDLG_SIGNATURE));
		THROW_FAILED_HRESULT(SaveLong (pStm, TRIASOPTIONDLG_VERSION));
		THROW_FAILED_HRESULT(WPersistStreamInit(m_pUnkPpg) -> Save(pStm, fClearDirty));
	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASOptionDlg::GetSizeMax (ULARGE_INTEGER *pcbSize)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pcbSize) 
		return E_POINTER;

	COM_TRY {
		pcbSize -> QuadPart = 0L;
		WPersistStreamInit(m_pUnkPpg) -> GetSizeMax(pcbSize);
	} COM_CATCH;

	pcbSize -> QuadPart += 2*sizeof(long);
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistStreamInit
STDMETHODIMP CTRiASOptionDlg::InitNew (void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (m_fIsInitialized)
		return E_UNEXPECTED;

	COM_TRY {
		THROW_FAILED_HRESULT(WPersistStreamInit(m_pUnkPpg) -> InitNew());
	} COM_CATCH;

	m_fIsInitialized = true;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// ITRiASOptionDlg
STDMETHODIMP CTRiASOptionDlg::Show(INT_PTR hWndParent, SHOWCOMMAND rgCmd, VARIANT_BOOL *pvResult)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ASSERT(NULL != m_pDlg);

	if (NULL == pvResult)
		return E_POINTER;

	USES_CONVERSION;

	switch (rgCmd) {
	case SHOWCOMMAND_ShowModeless:
	case SHOWCOMMAND_Hide:
		return E_INVALIDARG;		// erstmal (reserved for modeless stuff)

	case SHOWCOMMAND_Show:
		{
		// Parameter an Dialog übergeben
			if (IsWindow(HWND(hWndParent)))		
				m_pDlg -> SetParentWnd (CWnd::FromHandle((HWND)hWndParent));

		// und Dialog anzeigen
//			m_pDlg -> FillTreeCtrl();		// Items in Baum übernehmen
			*pvResult = (IDOK == m_pDlg -> DoModal()) ? VARIANT_TRUE : VARIANT_FALSE;
//			m_pDlg -> UpdateWindow();
//			if (SHOWCOMMAND_Show == rgCmd)
//				*pvResult = m_pDlg -> RunModalLoop (0);
//			else
//				*pvResult = VARIANT_FALSE;
		}
		break;

	default:
		return E_INVALIDARG;
	}
	return S_OK;
}

STDMETHODIMP CTRiASOptionDlg::InsertItemName(BSTR bstrType, BSTR bstrName, ULONG ulParent, ULONG *puiID)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == puiID)
		return E_POINTER;
	ASSERT(NULL != m_pDlg);

	USES_CONVERSION;

// Guid erzeugen, Type ist entweder ProgID oder ClsId
LPCSTR pcType = OLE2A(bstrType);
CIID Guid (pcType, CIID::INITCIID_InitFromGuid);

	if (!Guid) {
		Guid = CIID(pcType, CIID::INITCIID_InitFromProgId);
		if (!Guid)
			return E_INVALIDARG;
	}

// jetzt Item in Dialog einfügen
ULONG uiItem = m_pDlg -> InsertItem (Guid, OLE2A(bstrName), ulParent);

	if (0 == uiItem) 
		return E_FAIL;

	*puiID = uiItem;
	return S_OK;
}

STDMETHODIMP CTRiASOptionDlg::InsertItemObject(
	IUnknown *pIObj, BSTR bstrName, ULONG ulParent, IDispatch *pPict, ULONG *puiID)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == puiID)
		return E_POINTER;

	USES_CONVERSION;

OLE_HANDLE hBmp = NULL;
short rgType = PICTYPE_NONE;

	if (NULL != pPict) {
	WPicture Pict (pPict);

		if (Pict.IsValid()) {
			Pict -> get_Handle (&hBmp);
			Pict -> get_Type (&rgType);
		}
	}
		
ULONG uiItem = m_pDlg -> InsertItem (pIObj, OLE2A(bstrName), PICTYPE_ICON == rgType, (HANDLE)hBmp, NULL, ulParent);

	if (0 == uiItem) 
		return E_FAIL;
	*puiID = uiItem;
	return S_OK;
}

STDMETHODIMP CTRiASOptionDlg::InsertFolderItem(BSTR bstrName, ULONG ulParent, ULONG *puiItem)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ASSERT(NULL != m_pDlg);
	USES_CONVERSION;

ULONG uiItem = m_pDlg -> InsertFolderItem (OLE2A(bstrName), ulParent);

	if (0 == uiItem) 
		return E_FAIL;
	*puiItem = uiItem;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// sonstige Properties
STDMETHODIMP CTRiASOptionDlg::get_Caption(BSTR * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ASSERT(NULL != m_pDlg);
	if (NULL == pVal)
		return E_POINTER;

CComBSTR bstrCaption (m_pDlg -> GetCaption());

	if (!bstrCaption)
		return E_OUTOFMEMORY;
	*pVal = bstrCaption.Detach();
	return S_OK;
}

STDMETHODIMP CTRiASOptionDlg::put_Caption(BSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ASSERT(NULL != m_pDlg);

	USES_CONVERSION;
	m_pDlg -> SetCaption (OLE2A(newVal));
	return S_OK;
}

STDMETHODIMP CTRiASOptionDlg::get_WordWrap(VARIANT_BOOL * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ASSERT(NULL != m_pDlg);
	if (NULL == pVal)
		return E_POINTER;

	*pVal = m_pDlg -> GetWordWrap() ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}

STDMETHODIMP CTRiASOptionDlg::put_WordWrap(VARIANT_BOOL newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ASSERT(NULL != m_pDlg);

	m_pDlg -> SetWordWrap(newVal ? TRUE : FALSE);
	return S_OK;
}

STDMETHODIMP CTRiASOptionDlg::get_HasLines(VARIANT_BOOL * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ASSERT(NULL != m_pDlg);
	if (NULL == pVal)
		return E_POINTER;

	*pVal = m_pDlg -> GetHasLines() ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}

STDMETHODIMP CTRiASOptionDlg::put_HasLines(VARIANT_BOOL newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ASSERT(NULL != m_pDlg);

	m_pDlg -> SetHasLines(newVal ? TRUE : FALSE);
	return S_OK;
}

STDMETHODIMP CTRiASOptionDlg::get_HasButtons(VARIANT_BOOL * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ASSERT(NULL != m_pDlg);
	if (NULL == pVal)
		return E_POINTER;

	*pVal = m_pDlg -> GetHasButtons() ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}

STDMETHODIMP CTRiASOptionDlg::put_HasButtons(VARIANT_BOOL newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ASSERT(NULL != m_pDlg);

	m_pDlg -> SetHasButtons(newVal ? TRUE : FALSE);
	return S_OK;
}

STDMETHODIMP CTRiASOptionDlg::get_MultiSelect(VARIANT_BOOL * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal)
		return E_POINTER;

	*pVal = m_pDlg -> GetMultiSelect() ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}

STDMETHODIMP CTRiASOptionDlg::put_MultiSelect(VARIANT_BOOL newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ASSERT(NULL != m_pDlg);

	m_pDlg -> SetMultiSelect(newVal ? TRUE : FALSE);
	return S_OK;
}

STDMETHODIMP CTRiASOptionDlg::get_HasApply(VARIANT_BOOL * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal)
		return E_POINTER;

	*pVal = m_pDlg -> GetHasApply() ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}

STDMETHODIMP CTRiASOptionDlg::put_HasApply(VARIANT_BOOL newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ASSERT(NULL != m_pDlg);

	m_pDlg -> SetHasApply(newVal ? TRUE : FALSE);
	return S_OK;
}

STDMETHODIMP CTRiASOptionDlg::SelectItem(ULONG uiID, VARIANT_BOOL fSelect)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ASSERT(NULL != m_pDlg);

	return m_pDlg -> SelectItem (uiID, fSelect ? TRUE : FALSE);
}

STDMETHODIMP CTRiASOptionDlg::GetChildItem(ULONG ulParent, ULONG * pulChild)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ASSERT(NULL != m_pDlg);

	return m_pDlg -> GetChildItem (ulParent, pulChild);
}

STDMETHODIMP CTRiASOptionDlg::GetParentItem(ULONG ulChild, ULONG * pulParent)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ASSERT(NULL != m_pDlg);

	return m_pDlg -> GetParentItem (ulChild, pulParent);
}

STDMETHODIMP CTRiASOptionDlg::GetNextItem(ULONG ulItem, NEXTITEMMODE rgMode, ULONG *pulNextItem)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ASSERT(NULL != m_pDlg);

	return m_pDlg -> GetNextItem (ulItem, rgMode, pulNextItem);
}

STDMETHODIMP CTRiASOptionDlg::GetItemName(ULONG ulItem, BSTR *pbstrName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ASSERT(NULL != m_pDlg);

CString strName;

	if (!m_pDlg -> GetItemName (ulItem, strName))
		return E_FAIL;

CComBSTR bstrName (strName);

	if (!bstrName)
		return E_OUTOFMEMORY;

	*pbstrName = bstrName.Detach();
	return S_OK;
}

STDMETHODIMP CTRiASOptionDlg::GetItemObject(ULONG ulItem, IUnknown **ppIObj)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ASSERT(NULL != m_pDlg);

	return m_pDlg -> GetItemObject (ulItem, ppIObj);
}

STDMETHODIMP IXTRiASOptionDlg::Advise(IUnknown *pIConn, DWORD *pdwCookie)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return AtlAdvise (this, pIConn, IID_ITRiASOptionDlgCallback, pdwCookie);
}

STDMETHODIMP IXTRiASOptionDlg::Unadvise(DWORD dwCookie)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return AtlUnadvise (this, IID_ITRiASOptionDlgCallback, dwCookie);
}

STDMETHODIMP CTRiASOptionDlg::RefreshItem(ULONG ulItem)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return m_pDlg -> RefreshItem (ulItem);
}

STDMETHODIMP CTRiASOptionDlg::RefreshAllItems()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return RefreshAllItems();
}

STDMETHODIMP CTRiASOptionDlg::get_ActItem (ULONG *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return m_pDlg -> get_ActItem (pVal);
}

STDMETHODIMP CTRiASOptionDlg::SetFirstVisible (ULONG ulItem)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return m_pDlg -> SetFirstVisible (ulItem);
}

STDMETHODIMP CTRiASOptionDlg::get_ContextHandle(INT_PTR * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal)
		return E_POINTER;

	*pVal = m_pDlg -> GetContextHandle();
	return S_OK;
}

STDMETHODIMP CTRiASOptionDlg::put_ContextHandle(INT_PTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ASSERT(NULL != m_pDlg);

	m_pDlg -> SetContextHandle(newVal);
	return S_OK;
}

