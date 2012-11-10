// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 02.01.2001 12:29:17 
//
// @doc
// @module ObjPropTree.cpp | Definition of the <c CPopupTree> class

#include "stdafx.h"

#include "Statist.h"
#include "ObjPropTree.h"

#include "ObjPropTreeDlg.h"
#include "StatFuncTreeDlg.h"

/////////////////////////////////////////////////////////////////////////////
// RUNTIME_OBJECT_MAP
RT_OBJECT_ENTRYEX(PopupTree)

/////////////////////////////////////////////////////////////////////////////
// CPopupTree
LRESULT CPopupTree::OnInitDialog(HWND hFocus, LPARAM lParam)
{
	m_ftLabel.Attach(GetDlgItem(IDC_LABEL));
	m_sleSelItem.Attach(GetDlgItem(IDC_OBJECTPROPERTY));
	m_bttnSelObjProp.SubclassWindow(GetDlgItem(IDC_SELECT_OBJPROP));
	m_bttnSelObjProp.LoadImages(IDB_ARROW);
	m_bttnCustBttn.SubclassWindow(GetDlgItem(IDC_CUSTOMIZE));
	m_bttnCustBttn.LoadImages(IDB_CUSTOMIZEOBJPROP);
	m_bttnCustBttn.ShowWindow(SW_HIDE);

	m_fIsInitialized = TRUE;
	AdjustSizes();

	return TRUE;
}

namespace {
	class CLocalMessageLoop :
		public CMessageLoop
	{
	public:
		CLocalMessageLoop()
		{
			_Module.AddMessageLoop(this);
		}
		~CLocalMessageLoop()
		{
			_Module.RemoveMessageLoop();
		}
	};
}

///////////////////////////////////////////////////////////////////////////////
// Button wurde betätigt
LRESULT CPopupTree::OnSelectObjProp(WORD wNotifyCode, int iCtrlId, HWND hCtrl)
{
	ReleaseCapture();

char cbBuffer[_MAX_PATH];

	cbBuffer[0] = '\0';
	m_sleSelItem.GetWindowText(cbBuffer, sizeof(cbBuffer));

	if (POPUPTREEMODE_SHOWOBJPROPS == m_rgToShow) 
		return ShowObjPropDlg(cbBuffer);
	else if (POPUPTREEMODE_SHOWSTATFUNCS == m_rgToShow) 
		return ShowStatFuncDlg(cbBuffer);
	else {
		_ASSERTE(POPUPTREEMODE_UNKNOWN != m_rgToShow);
		return FALSE;
	}
}

namespace {
	class CActDlgWrapper
	{
	public:
		CActDlgWrapper(CPopupTree *pCtrl, CPopupTreeDlgBase *pActDlg) :
			m_pCtrl(pCtrl)
		{
			pCtrl -> SetActDlg(pActDlg);
		}
		~CActDlgWrapper()
		{
			m_pCtrl -> SetActDlg(NULL);
		}

	private:
		CPopupTree *m_pCtrl;
	};
}

LRESULT CPopupTree::ShowObjPropDlg (LPCSTR pcPreSelect)
{
CLocalMessageLoop theLoop;
CObjPropTreeDlg treeDlg (this, pcPreSelect);

	if(NULL == treeDlg.Create(m_hWnd))
	{
		ATLTRACE(_T("Dialog creation failed!\n"));
		return 0;
	}

CActDlgWrapper ActDlg(this, &treeDlg);
CRect rcEdit, rcBttn, rcPopup;

	m_sleSelItem.GetWindowRect(&rcEdit);
	m_bttnSelObjProp.GetWindowRect(&rcBttn);
	treeDlg.AdjustPosAndSize (this, rcEdit, rcBttn, &rcPopup);

// jetzt das Popupfenster anzeigen
	m_bValid = FALSE;
	m_SelObject.Assign(NULL);
	m_bttnCustBttn.EnableWindow(FALSE);		// während PopupPhase kein Customize

	treeDlg.SetWindowPos(HWND_TOP, rcPopup, SWP_SHOWWINDOW);
	if (IDOK == theLoop.Run()) {
		_ASSERTE(m_bValid);
		m_bttnCustBttn.EnableWindow(TRUE);		// während PopupPhase kein Customize

	// neuer Wert wurde selektiert
	CString strText;

		if (treeDlg.GetSelectedItem (strText)) {
			if (!m_SelObject.IsValid() && FAILED(treeDlg.GetSelectedObject (m_SelObject.ppu())))
				return FALSE;		// snh
			_ASSERTE(m_SelObject.IsValid());

			m_sleSelItem.SetWindowText(strText);
			m_bttnSelObjProp.SetFocus();

		// ggf. CustomizeBttn anzeigen
		WObjectProperty ObjProp;
		DWORD dwFlags = 0;

			if (SUCCEEDED(m_SelObject -> QueryInterface(ObjProp.ppi())) && 
				SUCCEEDED(ObjProp -> GetPropInfo(NULL, 0, &dwFlags)) &&
				dwFlags & (PROPCAPS_INTERACTIVE_INIT|PROPCAPS_INTERACTIVE)) {
			// Button anzeigen
				m_sleSelItem.GetWindowRect(&rcEdit);
				ScreenToClient(&rcEdit);
				rcEdit.right = m_iMinEditRight;
				m_sleSelItem.SetWindowPos (NULL, &rcEdit, SWP_NOMOVE|SWP_NOACTIVATE|SWP_NOZORDER);
				m_bttnCustBttn.ShowWindow(SW_SHOW);
			}
			else {
			// Button ausblenden
				m_sleSelItem.GetWindowRect(&rcEdit);
				ScreenToClient(&rcEdit);
				rcEdit.right = m_iMaxEditRight;
				m_sleSelItem.SetWindowPos (NULL, &rcEdit, SWP_NOMOVE|SWP_NOACTIVATE|SWP_NOZORDER);
				m_bttnCustBttn.ShowWindow(SW_HIDE);
			}
		} else
			m_bValid = FALSE;
	} else
		m_bttnCustBttn.EnableWindow(TRUE);

	return TRUE;
}

LRESULT CPopupTree::ShowStatFuncDlg (LPCSTR pcPreSelect)
{
CLocalMessageLoop theLoop;
CStatFuncTreeDlg treeDlg (this, pcPreSelect);

	if(NULL == treeDlg.Create(m_hWnd))
	{
		ATLTRACE(_T("Dialog creation failed!\n"));
		return 0;
	}

CActDlgWrapper ActDlg(this, &treeDlg);
CRect rcEdit, rcBttn, rcPopup;

	m_sleSelItem.GetWindowRect(&rcEdit);
	m_bttnSelObjProp.GetWindowRect(&rcBttn);
	treeDlg.AdjustPosAndSize (this, rcEdit, rcBttn, &rcPopup);

// jetzt das Popupfenster anzeigen
	m_bValid = FALSE;
	m_SelObject.Assign(NULL);

	treeDlg.SetWindowPos(HWND_TOP, rcPopup, SWP_SHOWWINDOW);
	if (IDOK == theLoop.Run()) {
		_ASSERTE(m_bValid);

	// neuer Wert wurde selektiert
	CString strText;

		if (treeDlg.GetSelectedItem (strText)) {
			if (!m_SelObject.IsValid() && FAILED(treeDlg.GetSelectedObject (m_SelObject.ppu())))
				return FALSE;		// snh
			_ASSERTE(m_SelObject.IsValid());

			m_sleSelItem.SetWindowText(strText);
			m_bttnSelObjProp.SetFocus();
		} else
			m_bValid = FALSE;
	}
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// Größen der Controls anpassen
BOOL CPopupTree::AdjustSizes()
{
	if (!m_fIsInitialized)
		return FALSE;

CSize szSize;

	AtlHiMetricToPixel(&m_sizeExtent, &szSize);

CRect rcLabel, rcEdit, rcBttn, rcCustBttn;

	m_ftLabel.GetWindowRect(&rcLabel);
	m_sleSelItem.GetWindowRect(&rcEdit);
	ScreenToClient(&rcEdit);

	m_bttnSelObjProp.GetWindowRect(&rcBttn);
	ScreenToClient(&rcBttn);

	m_bttnCustBttn.GetWindowRect(&rcCustBttn);
	ScreenToClient(&rcCustBttn);

int iEditWidth = szSize.cx - (GAP_LABEL + GAP_EDIT + GAP_BUTTON) - rcLabel.Width() - rcBttn.Width();

	if (iEditWidth > 0) {
		rcEdit.right = rcEdit.left + iEditWidth;
		m_sleSelItem.SetWindowPos (NULL, &rcEdit, SWP_NOMOVE|SWP_NOZORDER);

	int iBttnWidth = rcBttn.Width();
	int iCustBttnWidth = rcCustBttn.Width();

		rcBttn.left = rcEdit.right + GAP_BUTTON;
		rcBttn.right = rcBttn.left + iBttnWidth;
		m_bttnSelObjProp.SetWindowPos(NULL, &rcBttn, SWP_NOSIZE|SWP_NOZORDER);

		rcCustBttn.right = rcEdit.right;
		rcCustBttn.left = rcCustBttn.right - iCustBttnWidth;
		m_bttnCustBttn.SetWindowPos(NULL, rcCustBttn, SWP_NOSIZE|SWP_NOZORDER);
	}

	m_iMaxEditRight = rcEdit.right;
	m_iMinEditRight = rcCustBttn.left - GAP_SMALLBUTTON;
	return TRUE;
}

BOOL CPopupTree::UpdateCaption()
{
	if (!m_fIsInitialized)
		return FALSE;

	USES_CONVERSION;
	m_ftLabel.SetWindowText(OLE2A(m_bstrCaption));
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// custom properties
STDMETHODIMP CPopupTree::get_ButtonTooltipText (BSTR *pbstrTTText)
{
	ATLTRACE2(atlTraceControls,2,_T("CPopupTree::get_ButtonTooltipText\n")); 

char cbBuffer[_MAX_PATH];

	cbBuffer[0] = '\0';
	m_bttnSelObjProp.GetToolTipText (cbBuffer, sizeof(cbBuffer));
	*pbstrTTText = CComBSTR(cbBuffer).Detach();
	return S_OK;
}

STDMETHODIMP CPopupTree::put_ButtonTooltipText (BSTR bstrTTText)
{
	ATLTRACE2(atlTraceControls,2,_T("CPopupTree::put_ButtonTooltipText\n")); 
	if (!m_nFreezeEvents) 
		if (FireOnRequestEdit(100) == S_FALSE) 
			return S_FALSE;

	USES_CONVERSION;
	m_bttnSelObjProp.SetToolTipText(OLE2A(bstrTTText));

	m_bRequiresSave = TRUE; 
	if (!m_nFreezeEvents) 
		FireOnChanged(100);
	FireViewChange();
	SendOnDataChange(NULL); 
	return S_OK;
}

STDMETHODIMP CPopupTree::get_PopupTreeMode (POPUPTREEMODE *prgMode)
{
	ATLTRACE2(atlTraceControls,2,_T("CPopupTree::get_PopupTreeMode\n")); 
	*prgMode = m_rgToShow;
	return S_OK;
}

STDMETHODIMP CPopupTree::put_PopupTreeMode (POPUPTREEMODE rgMode)
{
	ATLTRACE2(atlTraceControls,2,_T("CPopupTree::put_ButtonTooltipText\n")); 
	if (!m_nFreezeEvents) 
		if (FireOnRequestEdit(101) == S_FALSE) 
			return S_FALSE;

	m_rgToShow = rgMode;

	m_bRequiresSave = TRUE; 
	if (!m_nFreezeEvents) 
		FireOnChanged(101);
	FireViewChange();
	SendOnDataChange(NULL); 
	return S_OK;
}

// Implementation of get_HasSelection
STDMETHODIMP CPopupTree::get_HasSelection(VARIANT_BOOL *pfHasSel)
{
	ATLTRACE2(atlTraceControls, 2, _T("CPopupTree::get_HasSelection\n")); 
	*pfHasSel = m_bValid ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}

// Implementation of get_Selection
STDMETHODIMP CPopupTree::get_Selection(REFIID riid, IUnknown **ppIUnk)
{
	ATLTRACE2(atlTraceControls, 2, _T("CPopupTree::get_Selection\n")); 
	if (!m_bValid)
		return E_UNEXPECTED;

	_ASSERTE(NULL != m_pActDlg);
	if (!m_SelObject.IsValid() && FAILED(m_pActDlg -> GetSelectedObject (m_SelObject.ppu())))
		return E_UNEXPECTED;

	_ASSERTE(m_SelObject.IsValid());
	return m_SelObject -> QueryInterface(riid, (LPVOID *)ppIUnk);
}

STDMETHODIMP CPopupTree::SetSelection(BSTR bstrSelection)
{
	ATLTRACE2(atlTraceControls, 2, _T("CPopupTree::SetSelection\n")); 
	m_bValid = FALSE;
	m_SelObject.Assign(NULL);

	USES_CONVERSION;
	if (POPUPTREEMODE_SHOWOBJPROPS == m_rgToShow) {
	WObjectProperty ObjProp;
	HRESULT hr = CObjPropTreeDlg::GetObjectProp (OLE2A(bstrSelection), ObjProp.ppi());

		if (FAILED(hr))	return hr;
		m_SelObject = ObjProp;
	} 
	else if (POPUPTREEMODE_SHOWSTATFUNCS == m_rgToShow) {
	WGenericStatistics StatFunc;
	HRESULT hr = CStatFuncTreeDlg::GetStatFunc(OLE2A(bstrSelection), StatFunc.ppi());

		if (FAILED(hr))	return hr;
		m_SelObject = StatFunc;
	} 
	else {
		_ASSERTE(POPUPTREEMODE_UNKNOWN != m_rgToShow);
		return E_INVALIDARG;
	}
	m_bValid = TRUE;
	return S_OK;
}

