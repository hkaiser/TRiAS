// TRiASCmdUI.cpp : Implementation of CcomApp and DLL registration.

#include "fakemfcp.hxx"

#include <toolguid.h>
#include <itoolbar.h>
#include <dtoolbar.h>

#include "TRiASCmdUI.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ***ITRiASToolCmdUI specific functions

STDMETHODIMP CTRiASToolCmdUI::put_IsEnabled (VARIANT_BOOL fEnable)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

#if defined(_USE_SEC_CLASSES)
	state.Enable (fEnable);
#else
	state.m_bEnableChanged = true;

CToolBar* pToolBar = (CToolBar*)state.m_pOther;

	ASSERT(pToolBar != NULL);
	ASSERT_KINDOF(CToolBar, pToolBar);
	ASSERT(state.m_nIndex < state.m_nIndexMax);

	if (NULL == pToolBar)
		return ResultFromScode (E_POINTER);

UINT nNewStyle = 0L; // pToolBar->GetButtonStyle(state.m_nIndex) & ~TBBS_DISABLED;
UINT uiID = 0L;
int iImage = 0;

	pToolBar->GetButtonInfo (state.m_nIndex, uiID, nNewStyle, iImage);
	nNewStyle &= ~TBBS_DISABLED;

	if (nNewStyle & TBBS_SEPARATOR && 0 != uiID) {
	// sonstiges Control
	CWnd *pCtrl = pToolBar->GetDlgItem (uiID);		// Control besorgen

		if (!fEnable)
			nNewStyle |= TBBS_DISABLED;

		ASSERT(NULL != pCtrl);
		pCtrl -> EnableWindow (fEnable);
	} else {
	//normaler Button
		if (!fEnable) {
			nNewStyle |= TBBS_DISABLED;
			// WINBUG: If a button is currently pressed and then is disabled
			// COMCTL32.DLL does not unpress the button, even after the mouse
			// button goes up!  We work around this bug by forcing TBBS_PRESSED
			// off when a button is disabled.
			nNewStyle &= ~TBBS_PRESSED;
		}
		ASSERT(!(nNewStyle & TBBS_SEPARATOR));
	}
	pToolBar->SetButtonStyle(state.m_nIndex, nNewStyle);
#endif // _USE_SEC_CLASSES

	return NOERROR;
}

STDMETHODIMP CTRiASToolCmdUI::put_CheckState (int nCheck)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

#if defined(_USE_SEC_CLASSES)
	state.SetCheck (nCheck);
#else
	ASSERT(nCheck >= 0 && nCheck <= 2); // 0=>off, 1=>on, 2=>indeterminate

CToolBar* pToolBar = (CToolBar*)state.m_pOther;

	ASSERT(pToolBar != NULL);
	ASSERT_KINDOF(CToolBar, pToolBar);
	ASSERT(state.m_nIndex < state.m_nIndexMax);

	if (NULL == pToolBar)
		return ResultFromScode (E_POINTER);

UINT nNewStyle = pToolBar->GetButtonStyle(state.m_nIndex) & ~(TBBS_CHECKED | TBBS_INDETERMINATE);

	if (nCheck == 1)
		nNewStyle |= TBBS_CHECKED;
	else if (nCheck == 2)
		nNewStyle |= TBBS_INDETERMINATE;

	ASSERT(!(nNewStyle & TBBS_SEPARATOR));
	pToolBar->SetButtonStyle(state.m_nIndex, nNewStyle | TBBS_CHECKBOX);
#endif // _USE_SEC_CLASSES

	return NOERROR;
}

STDMETHODIMP CTRiASToolCmdUI::put_IsOn (VARIANT_BOOL fOn)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	state.SetRadio (fOn);
	return NOERROR;
}

STDMETHODIMP CTRiASToolCmdUI::put_Text (BSTR bstrNewText)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

#if defined(_USE_SEC_CLASSES)
	USES_CONVERSION;
	state.SetText (OLE2A(bstrNewText));
	return S_OK;
#else
	return S_FALSE;		// ignore it
#endif // _USE_SEC_CLASSES
}

STDMETHODIMP CTRiASToolCmdUI::get_CmdID (int *puiID)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	if (NULL == puiID) return E_POINTER;

	*puiID = (int)state.m_nID;
	return NOERROR;
}

/////////////////////////////////////////////////////////////////////////////
// ***ITRiASToolCmdUI specific functions

STDMETHODIMP CTRiASStatusCmdUI::put_IsEnabled (VARIANT_BOOL fEnable)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

#if defined(_USE_SEC_CLASSES)
	state.Enable (fEnable);
#else
	state.m_bEnableChanged = TRUE;

CStatusBar *pStatusBar = (CStatusBar *)state.m_pOther;

	ASSERT(pStatusBar != NULL);
	ASSERT_KINDOF(CStatusBar, pStatusBar);
	ASSERT(state.m_nIndex < state.m_nIndexMax);

UINT nNewStyle = pStatusBar->GetPaneStyle(state.m_nIndex) & ~SBPS_DISABLED;

	if (!fEnable)
		nNewStyle |= SBPS_DISABLED;
	pStatusBar->SetPaneStyle (state.m_nIndex, nNewStyle);
#endif // _USE_SEC_CLASSES

	return NOERROR;
}

STDMETHODIMP CTRiASStatusCmdUI::put_CheckState (int nCheck)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

#if defined(_USE_SEC_CLASSES)
	state.SetCheck (nCheck);
#else
CStatusBar *pStatusBar = (CStatusBar *)state.m_pOther;

	ASSERT(pStatusBar != NULL);
	ASSERT_KINDOF(CStatusBar, pStatusBar);
	ASSERT(state.m_nIndex < state.m_nIndexMax);

UINT nNewStyle = pStatusBar->GetPaneStyle(state.m_nIndex) & ~SBPS_POPOUT;

	if (nCheck != 0)
		nNewStyle |= SBPS_POPOUT;
	pStatusBar->SetPaneStyle (state.m_nIndex, nNewStyle);
#endif // _USE_SEC_CLASSES

	return NOERROR;
}

STDMETHODIMP CTRiASStatusCmdUI::put_IsOn (VARIANT_BOOL fOn)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	state.SetRadio (fOn);
	return NOERROR;
}

STDMETHODIMP CTRiASStatusCmdUI::put_Text (BSTR bstrNewText)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

#if defined(_USE_SEC_CLASSES)
	USES_CONVERSION;

	state.SetText (OLE2A(bstrNewText));
#else
CStatusBar *pStatusBar = (CStatusBar *)state.m_pOther;

	ASSERT(pStatusBar != NULL);
	ASSERT_KINDOF(CStatusBar, pStatusBar);
	ASSERT(state.m_nIndex < state.m_nIndexMax);

	USES_CONVERSION;

	pStatusBar->SetPaneText(state.m_nIndex, OLE2A(bstrNewText));
#endif // _USE_SEC_CLASSES

	return NOERROR;
}

STDMETHODIMP CTRiASStatusCmdUI::get_CmdID (int *puiID)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	if (NULL == puiID) return E_POINTER;

	*puiID = (int)state.m_nID;
	return NOERROR;
}

/////////////////////////////////////////////////////////////////////////////
// CmdUI für das Abtesten des einzustellenden Zustandes

CTRiASToolCmdQueryUI::CTRiASToolCmdQueryUI (void)
{
	m_fEnabled = false;
	m_fRadioState = false;
	m_iCheckState = 0;

	m_fChangedEnable = false;
	m_fChangedCheckState = false;
	m_fChangedRadioState = false;
	m_fChangedText = false;
}

// *** ITRiASToolCmdUI specific functions

STDMETHODIMP CTRiASToolCmdQueryUI::put_IsEnabled (VARIANT_BOOL fEnable)
{
CToolBar* pToolBar = (CToolBar *)state.m_pOther;

	ASSERT(pToolBar != NULL);
	ASSERT_KINDOF(CToolBar, pToolBar);

	if (NULL == pToolBar)
		return ResultFromScode (E_POINTER);

	m_fChangedEnable = true;
	m_fEnabled = fEnable ? true : false;

return NOERROR;
}

STDMETHODIMP CTRiASToolCmdQueryUI::put_CheckState (int nCheck)
{
	ASSERT(nCheck >= 0 && nCheck <= 2); // 0=>off, 1=>on, 2=>indeterminate

CToolBar* pToolBar = (CToolBar *)state.m_pOther;

	ASSERT(pToolBar != NULL);
	ASSERT_KINDOF(CToolBar, pToolBar);

	if (NULL == pToolBar)
		return ResultFromScode (E_POINTER);

	m_fChangedCheckState = true;
	m_iCheckState = nCheck;

return NOERROR;
}

STDMETHODIMP CTRiASToolCmdQueryUI::put_IsOn (VARIANT_BOOL fOn)
{
	m_fChangedRadioState = true;
	m_fRadioState = fOn;
	return NOERROR;
}

STDMETHODIMP CTRiASToolCmdQueryUI::put_Text (BSTR bstrNewText)
{
	USES_CONVERSION;

	m_fChangedText = true;
	m_strText = OLE2A(bstrNewText);
	return ResultFromScode(S_FALSE);
}

STDMETHODIMP CTRiASToolCmdQueryUI::get_CmdID (int *puiID)
{
	if (NULL == puiID) return E_POINTER;

	*puiID = (int)state.m_nID;
	return NOERROR;
}

