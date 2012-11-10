/////////////////////////////////////////////////////////////////////////////
// File: MsgMap.h

#include "StdAfx.h"

#include "resource.h"		// ResourceKonstanten

#include <dirisole.h>
#include <bscrguid.h>

#include "MsgMap.h"

/////////////////////////////////////////////////////////////////////////////
//
HRESULT CMessageMap::DisConnectFromServer (void)
{
HRESULT hr = NOERROR;

	if (m_Cont.IsValid()) {
	// WindowsMessages abmelden
		if (0 != m_dwCookieSys) {
			hr = AtlUnadvise (m_Cont, IID_ITRiASSysNotificationSink, m_dwCookieSys);
			if (SUCCEEDED(hr)) 
				m_dwCookieSys = 0L;
		}
		m_Cont.Assign (NULL);	// Release()
	}
	if (m_Sink.IsValid())
		m_Sink.Assign (NULL);
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
// Am TRiAS-ConnectionPoint ankoppeln
HRESULT CMessageMap::SetXtsnSite (ITriasXtensionSite *pSite)
{
	try {
		if (NULL != pSite) {
			m_Cont = pSite;		// throws HRESULT

		// Alle WindowsMessages auch hier vorbeischicken	
			THROW_FAILED_HRESULT(AtlAdvise (m_Cont, (ITRiASSysNotificationSink *)this, IID_ITRiASSysNotificationSink, &m_dwCookieSys));

			m_Sink = WExtendBScript (CLSID_MacroScriptExtension);
		} else 
			DisConnectFromServer();

	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}

	return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// *** ITRiASSysNotificationSink specific functions ***
STDMETHODIMP CMessageMap::WindowsMessage (
	long hWnd, long uiMsg, long wParam, long lParam)
{
	ASSERT(m_fEnabled);	// muß angemeldet sein

CMsgMap::iterator it = m_Msg.find(uiMsg);

	if (it == m_Msg.end())
		return NOERROR;		// nicht bearbeitet

	return BlastMessage ((*it).second, wParam, lParam);
}

HRESULT CMessageMap::BlastMessage (os_string strToCall, WPARAM wParam, LPARAM lParam)
{
// Strukturen für Parameter/Rückkehrwert (zwei Parameter)
ebPARAM Pars[3];
LPVOID cbParam[3];
BSPARAM bs = { Pars, cbParam };

ebBOOL iRet = false;

	Pars[0].wType = TYP_BOOLEAN;		// Funktion liefern BOOL
	Pars[0].szExtType[0] = '\0';
	cbParam[0] = &iRet;

	Pars[1].wType = TYP_LONG;
	Pars[1].szExtType[0] = '\0';
	cbParam[1] = &wParam;

	Pars[2].wType = TYP_LONG;
	Pars[2].szExtType[0] = '\0';
	cbParam[2] = &lParam;

	ASSERT(m_Sink.IsValid());

	RETURN_FAILED_HRESULT(m_Sink -> FireEvent (strToCall.c_str(), 2, &bs));
		
	return iRet ? S_FALSE : S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// *** IMessageMap specific functions ***
STDMETHODIMP CMessageMap::get_Enabled (VARIANT_BOOL *pVal)
{
	TEST_E_POINTER("CMessageMap::get_Enabled", pVal);

	*pVal = m_fEnabled ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}

STDMETHODIMP CMessageMap::put_Enabled (VARIANT_BOOL newVal)
{
	if (m_fEnabled && !newVal)
		SetXtsnSite (NULL);
	else if (!m_fEnabled && newVal)
		SetXtsnSite (g_pTE -> m_pXtnSite);

	m_fEnabled = newVal ? true : false;
	return S_OK;
}

STDMETHODIMP CMessageMap::AddMessage(LONG Msg, BSTR ToCall, VARIANT_BOOL *pVal)
{
	TEST_E_POINTER("CMessageMap::AddMessage", pVal);

	if (m_Msg.find(Msg) != m_Msg.end()) {
		*pVal = VARIANT_FALSE;
		return S_OK;		// bereits vorhanden
	}

	USES_CONVERSION;
	m_Msg.insert (CMsgMap::value_type(Msg, os_string(OLE2A(ToCall))));
	*pVal = VARIANT_TRUE;
	return S_OK;
}

STDMETHODIMP CMessageMap::RemoveMessage(LONG Msg, VARIANT_BOOL *pVal)
{
CMsgMap::iterator it = m_Msg.find(Msg);

	if (it != m_Msg.end()) {
		*pVal = VARIANT_FALSE;
		return S_OK;		// bereits vorhanden
	}

// herauslöschen des gesuchten Elementes
int iCnt = m_Msg.erase (Msg);

	*pVal = iCnt == 1 ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}


STDMETHODIMP CMessageMap::RemoveAll()
{
// alle löschen
	m_Msg.erase(m_Msg.begin(), m_Msg.end());
	return S_OK;
}

STDMETHODIMP CMessageMap::get_HasMsg(LONG Msg, VARIANT_BOOL *pVal)
{
	TEST_E_POINTER("CMessageMap::get_HasMsg", pVal);

CMsgMap::iterator it = m_Msg.find(Msg);

	*pVal = (it == m_Msg.end()) ? VARIANT_FALSE : VARIANT_TRUE;
	return S_OK;
}

STDMETHODIMP CMessageMap::get_ToCall(LONG Msg, BSTR *pVal)
{
	TEST_E_POINTER("CMessageMap::get_ToCall", pVal);

CMsgMap::iterator it = m_Msg.find(Msg);
CComBSTR bstrName ((it != m_Msg.end()) ? (*it).second.c_str() : "");

	*pVal = bstrName.Detach();
	return S_OK;
}

STDMETHODIMP CMessageMap::put_ToCall(LONG Msg, BSTR newVal)
{
CMsgMap::iterator it = m_Msg.find(Msg);

	USES_CONVERSION;
	if (it != m_Msg.end()) 
		(*it).second = os_string(OLE2A(newVal));

	return S_OK;
}
