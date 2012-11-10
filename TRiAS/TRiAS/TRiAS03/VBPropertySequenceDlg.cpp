// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 01.11.2002 12:18:27
//
// @doc
// @module VBPropertySequenceDlg.cpp | Implementation of the <c CVBGeoComponentDlg> class

#include "trias03p.hxx"

#include <triastlb.h>
#include <Com/ComBool.h>

#include "trias03.h"
#include "VBPropertySequenceDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(OleObject);
DefineSmartInterface(Dispatch);
DefineSmartInterface(GeoComponentUI);

/////////////////////////////////////////////////////////////////////////////
// CVBGeoComponentDlg

CVBGeoComponentDlg* CVBGeoComponentDlg::CreateInstance (LPCSTR pcCaption, 
	REFGUID rGuid, long lIndex)
{
CComObject<CVBGeoComponentDlg> *pCfgDlg = NULL;

// Dialog erzeugen
	if (FAILED(CComObject<CVBGeoComponentDlg>::CreateInstance(&pCfgDlg)))
		return NULL;

	pCfgDlg->AddRef();		// pendig AddRef
	pCfgDlg->SetTitle(pcCaption);
	pCfgDlg->SetInitData(rGuid, lIndex);
	return pCfgDlg; 
}

CVBGeoComponentDlg::CVBGeoComponentDlg() 
	: WTL::CAxPropertyPageImpl<CVBGeoComponentDlg>("")
{
	m_dwFlags = 0;
	m_hControlWnd = NULL;
	m_lIndex = -1;
}

CVBGeoComponentDlg::~CVBGeoComponentDlg()
{
	DestroyControl();
}

void CVBGeoComponentDlg::AdjustSheetButtons()
{
DWORD dwBttns = 0;

	if (!(m_dwFlags & ADDPAGES_FIRSTPAGE))
		dwBttns = PSWIZB_BACK;			// nicht erste Seite

	if (!GetDisableNextPage()) {
		if (m_dwFlags & ADDPAGES_LASTPAGE) 
			dwBttns |= PSWIZB_FINISH;	// letzte Seite
		else 
			dwBttns |= PSWIZB_NEXT;		// nicht letzte seite
	} else if (m_dwFlags & ADDPAGES_LASTPAGE)
		dwBttns |= PSWIZB_DISABLEDFINISH;

	GetPropertySheet().SetWizardButtons(dwBttns);
}

BOOL CVBGeoComponentDlg::GetDisableNextPage()
{
	// TODO: return TRUE, if 'Next >' - button should be disabled
	COM_TRY {
	WUnknown OleObj;
	CComBool fAllow;

		THROW_FAILED_HRESULT(AtlAxGetControl(m_hControlWnd, OleObj.ppi()));
		THROW_FAILED_HRESULT(WGeoComponentUI(OleObj)->get_AllowNextPage(&fAllow));
		return !fAllow;

	} COM_CATCH_IGNORE;
	return FALSE;
}

// Control anzeigen und dazu ggf. neu erzeugen
HRESULT CVBGeoComponentDlg::ShowControl(WTL::CRect &rrcPos)
{
	if (NULL == m_hControlWnd) {
		m_hControlWnd = ::CreateWindow(
			CAxWindow::GetWndClassName(),	// Style
			os_string(m_Guid).c_str(),		// Name == Guid
			WS_CHILD|WS_TABSTOP|WS_GROUP|DS_CONTROL,
			rrcPos.left, rrcPos.top, rrcPos.Width(), rrcPos.Height(),
			m_hWnd, (HMENU)IDC_VBDIALOGWRAPPER,
			_Module.GetModuleInstance(),
			NULL);

		_ASSERTE(NULL != m_hControlWnd);
	}

WUnknown OleObj;

	RETURN_FAILED_HRESULT(AtlAxGetControl(m_hControlWnd, OleObj.ppi()));
	RETURN_FAILED_HRESULT(WOleObject(OleObj) -> DoVerb(OLEIVERB_SHOW, NULL, 
		NULL, 0, m_hControlWnd, &rrcPos));
	::ShowWindow(m_hControlWnd, SW_SHOWNOACTIVATE);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// derzeit angezeigtes Control ausblenden
HRESULT CVBGeoComponentDlg::HideControl()
{
	if (NULL != m_hControlWnd) {
	WUnknown OleObj;

		RETURN_FAILED_HRESULT(AtlAxGetControl(m_hControlWnd, OleObj.ppi()));
		RETURN_FAILED_HRESULT(WOleObject(OleObj) -> DoVerb(OLEIVERB_HIDE, NULL, 
			NULL, 0, m_hControlWnd, NULL));
	}
	return S_OK;
}

void CVBGeoComponentDlg::DestroyControl()
{
	if (NULL != m_hControlWnd && ::IsWindow(m_hControlWnd)) {
		::DestroyWindow(m_hControlWnd);
		m_hControlWnd = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CVBGeoComponentDlg message handlers

LRESULT CVBGeoComponentDlg::OnInitDialog(HWND /*hWnd*/, LPARAM /*lParam*/)
{
	_ASSERTE(-1 != m_lIndex && m_Guid.IsValid());

WTL::CRect rcPos;

	::GetWindowRect(GetDlgItem(IDC_VBDIALOG), &rcPos);
	ScreenToClient(&rcPos);

	if (FAILED(ShowControl(rcPos)))
		return FALSE;	// Fehlermeldung ausgeben

// instantiiertes Control an Geokomponente weiterreichen
	COM_TRY {
	WUnknown OleObj;

		THROW_FAILED_HRESULT(AtlAxGetControl(m_hControlWnd, OleObj.ppi()));
		_ASSERTE(m_EmbeddedObj.IsValid());
		THROW_FAILED_HRESULT(m_EmbeddedObj->putref_ConnectUI(m_lIndex, WDispatch(OleObj)));
		THROW_FAILED_HRESULT(WGeoComponentUI(OleObj)->putref_Callback(this));

	} COM_CATCH_IGNORE;
	return TRUE;
}

void CVBGeoComponentDlg::OnDestroy()
{
	ResetCallbackLoop();
	SetMsgHandled(FALSE);
}

BOOL CVBGeoComponentDlg::OnSetActive() 
{
	COM_TRY {
	WUnknown OleObj;

		THROW_FAILED_HRESULT(AtlAxGetControl(m_hControlWnd, OleObj.ppi()));
		THROW_FAILED_HRESULT(WGeoComponentUI(OleObj)->OnActivate(VARIANT_TRUE));

	} COM_CATCH_RETURN(FALSE);
	return TRUE;
}

BOOL CVBGeoComponentDlg::OnKillActive() 
{
	COM_TRY {
	WUnknown OleObj;

		THROW_FAILED_HRESULT(AtlAxGetControl(m_hControlWnd, OleObj.ppi()));
		THROW_FAILED_HRESULT(WGeoComponentUI(OleObj)->OnActivate(VARIANT_FALSE));

	} COM_CATCH_RETURN(FALSE);
	return TRUE;
}

int CVBGeoComponentDlg::OnWizardBack()
{
CComBool fAllow;

	COM_TRY {
	WUnknown OleObj;

		THROW_FAILED_HRESULT(AtlAxGetControl(m_hControlWnd, OleObj.ppi()));
		THROW_FAILED_HRESULT(WGeoComponentUI(OleObj)->OnBack(&fAllow));

	} COM_CATCH_RETURN(-1);		// default is to prevent back page
	return fAllow ? 0 : -1;
}

int CVBGeoComponentDlg::OnWizardNext()
{
CComBool fAllow;

	COM_TRY {
	WUnknown OleObj;

		THROW_FAILED_HRESULT(AtlAxGetControl(m_hControlWnd, OleObj.ppi()));
		THROW_FAILED_HRESULT(WGeoComponentUI(OleObj)->OnNext(&fAllow));

	} COM_CATCH_RETURN(-1);		// default is to prevent next page
	return fAllow ? 0 : -1;
}

// Implementation of OnWizardFinish
BOOL CVBGeoComponentDlg::OnWizardFinish()
{
CComBool fAllow;

	COM_TRY {
	WUnknown OleObj;

		THROW_FAILED_HRESULT(AtlAxGetControl(m_hControlWnd, OleObj.ppi()));
		THROW_FAILED_HRESULT(WGeoComponentUI(OleObj)->OnNext(&fAllow));

	} COM_CATCH_RETURN(FALSE);		// default is to prevent finish
	return fAllow;
}

BOOL CVBGeoComponentDlg::OnTranslateAccelerator(LPMSG lpMsg)
{
CComBool fResult;

	COM_TRY {
	WUnknown OleObj;

		THROW_FAILED_HRESULT(AtlAxGetControl(m_hControlWnd, OleObj.ppi()));
		THROW_FAILED_HRESULT(WGeoComponentUI(OleObj)->TranslateAccelerator(
			reinterpret_cast<long>(lpMsg->hwnd), lpMsg->message, lpMsg->wParam,
			lpMsg->lParam, lpMsg->time, lpMsg->pt.x, lpMsg->pt.y, &fResult));

	} COM_CATCH_RETURN(FALSE);
	return fResult;
}

void CVBGeoComponentDlg::ResetCallbackLoop()
{
	COM_TRY {
	WUnknown OleObj;
	CComBool fResult;

		THROW_FAILED_HRESULT(AtlAxGetControl(m_hControlWnd, OleObj.ppi()));
		THROW_FAILED_HRESULT(WGeoComponentUI(OleObj)->putref_Callback(NULL));

	} COM_CATCH_NORETURN;
}

///////////////////////////////////////////////////////////////////////////////
// IGeoComponentUICallback
STDMETHODIMP CVBGeoComponentDlg::OnStatusChange()
{
	ATLTRACE(_T("CVBGeoComponentDlg::OnStatusChange\n"));
	AdjustSheetButtons();
	return S_OK;
}

STDMETHODIMP CVBGeoComponentDlg::TranslateAccelerator(long hWnd, long lMsg, 
	long wParam, long lParam, long lTime, long lPosX, long lPosY, 
	VARIANT_BOOL *pfResult)
{
	ATLTRACE(_T("CVBGeoComponentDlg::TranslateAccelerator\n"));
	if (NULL == pfResult)
		return E_POINTER;

MSG Msg;

	Msg.hwnd = reinterpret_cast<HWND>(hWnd);
	Msg.message = lMsg;
	Msg.wParam = wParam;
	Msg.lParam = lParam;
	Msg.time = lTime;
	Msg.pt.x = lPosX;
	Msg.pt.y = lPosY;

	*pfResult = base_t::OnTranslateAccelerator(&Msg) ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}

