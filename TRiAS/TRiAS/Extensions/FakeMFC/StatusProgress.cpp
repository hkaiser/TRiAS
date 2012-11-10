// @doc
// @module StatusProgress.cpp | Implementation of the <c CStatusProgress> class

#include "fakemfcp.hxx"

#include "fakemfc.h"

#include <itoolbar.h>
#include "Wrapper.h"		// SmartInterfaces
#include "mainfrm.h"

#include "StatusProgress.h"

/////////////////////////////////////////////////////////////////////////////
// CStatusProgress

STDMETHODIMP CStatusProgress::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IStatusProgress,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CStatusProgress::get_ProgressControlActive(VARIANT_BOOL *pVal)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	if (NULL == pVal) return E_POINTER;

CMainFrame *pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd());

	if (NULL == pFrame)
		return E_UNEXPECTED;

	*pVal = pFrame -> IsProgressControlActive() ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}

STDMETHODIMP CStatusProgress::StepProgress(void)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

CMainFrame *pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd());

	if (NULL == pFrame)
		return E_UNEXPECTED;

	if (!pFrame -> IsProgressControlActive())
		return E_UNEXPECTED;
	pFrame -> StepProgress();
	return S_OK;
}

STDMETHODIMP CStatusProgress::SetProgress(int iPos)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

CMainFrame *pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd());

	if (NULL == pFrame)
		return E_UNEXPECTED;
	if (!pFrame -> IsProgressControlActive())
		return E_UNEXPECTED;

	return S_OK;
}

STDMETHODIMP CStatusProgress::InitializeProgressControl(
	BSTR pcszMsg, int iLow, int iHigh, VARIANT_BOOL bResetPos, VARIANT_BOOL *pSuccess)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	if (NULL == pSuccess) return E_POINTER;

CMainFrame *pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd());

	if (NULL == pFrame)
		return E_UNEXPECTED;

	USES_CONVERSION;

BOOL fResult = pFrame -> InitializeProgressControl(OLE2A(pcszMsg), iLow, iHigh, bResetPos ? TRUE : FALSE);

	if (fResult) {
	// sonstige Parameter initialisieren
		pFrame -> SetProgressExStyle(SEC_EX_PROGRESS_SHOWPERCENT|SEC_EX_PROGRESS_TEXT_ALIGN_LEFT);
		pFrame -> SetProgressFont();
		pFrame -> SetProgressColors(::GetSysColor(COLOR_BTNSHADOW), ::GetSysColor(COLOR_BTNFACE));
		pFrame -> SetProgressStep(1);
	}
	*pSuccess = fResult ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}

STDMETHODIMP CStatusProgress::UninitializeProgressControl(void)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

CMainFrame *pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd());

	if (NULL == pFrame)
		return E_UNEXPECTED;
	if (!pFrame -> IsProgressControlActive())
		return E_UNEXPECTED;

	pFrame -> UninitializeProgressControl();
	return S_OK;
}

STDMETHODIMP CStatusProgress::get_ProgressText(BSTR *pVal)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	if (NULL == pVal) return E_POINTER;

CMainFrame *pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd());

	if (NULL == pFrame)
		return E_UNEXPECTED;

CComBSTR bstr (pFrame -> GetProgressText());
	
	*pVal = bstr.Detach();
	return S_OK;
}

STDMETHODIMP CStatusProgress::put_ProgressText(BSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

CMainFrame *pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd());

	if (NULL == pFrame)
		return E_UNEXPECTED;

	USES_CONVERSION;
	pFrame -> SetProgressText (OLE2A(newVal));
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IProgressIndicator
STDMETHODIMP_(HWND) CStatusProgress::InitNew (HWND hWnd, DWORD dwReserved)
{
	return NULL;
}

STDMETHODIMP CStatusProgress::Restart (long uiMinPos, long ulMaxPos, DWORD dwFlags)
{
	return E_NOTIMPL;
}

STDMETHODIMP CStatusProgress::ChangeText (DWORD dwWhichText, LPCSTR pcNewText)
{
	return E_NOTIMPL;
}

STDMETHODIMP CStatusProgress::RetrieveText (DWORD dwWichText, LPSTR cbText, ULONG uiLen)
{
	return E_NOTIMPL;
}

STDMETHODIMP_(int) CStatusProgress::SetPosition (long uiNewPos)
{
	return 0;
}

STDMETHODIMP_(BOOL) CStatusProgress::WasCanceled ()
{
	return FALSE;
}

STDMETHODIMP CStatusProgress::get_Canceled(VARIANT_BOOL *pfWasCanceled)
{
	if (NULL == pfWasCanceled)
		return E_POINTER;
	*pfWasCanceled = VARIANT_FALSE;
	return S_OK;
}

