// @doc
// @module ManageParamDlg.cpp | Implementation of class CManageParamDlg

#include "defaultp.hxx"

#include <shlobj.h>
#include <Com/PropertyHelper.h>

#include "Default.h"
#include "Strings.h"

#include "ManageParamDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TRiASPropertyBase);		// WTRiASPropertyBase
DefineSmartInterface(TRiASProperties);			// WTRiASProperties
DefineSmartInterface(TriasExtInit);				// WTriasExtInit

/////////////////////////////////////////////////////////////////////////////
//
STDMETHODIMP CManageParamDlg::AddPages (LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam)
{
// Koordinatensystem sicherstellen
	if (!m_PSE.IsValid())
	{
	HRESULT hr = EnsureConnectedCTF();

		if (S_OK != hr) {
			if (E_NOINTERFACE != hr)
				RETURN_FAILED_HRESULT(hr);
			return hr;		// E_NOINTERFACE darfs sein
		}
	}
	_ASSERTE(m_PSE.IsValid());

// den Aufruf einfach an das Objekt weiterleiten
	return m_PSE -> AddPages (lpfnAddPage, lParam);
}

STDMETHODIMP CManageParamDlg::ReplacePage (UINT uPageID, LPFNADDPROPSHEETPAGE lpfnReplacePage, LPARAM lParam)
{
	return E_NOTIMPL;
}

/////////////////////////////////////////////////////////////////////////////
// ITriasExtInit methods 
STDMETHODIMP CManageParamDlg::Initialize (LPCITEMIDLIST pidl, LPDATAOBJECT lpdobj, HKEY hkeyProgID)
{
// Koordinatensystem sicherstellen
	if (!m_PSE.IsValid())
	{
	HRESULT hr = EnsureConnectedCTF();

		if (S_OK != hr) {
			if (E_NOINTERFACE != hr)
				RETURN_FAILED_HRESULT(hr);
			return hr;		// E_NOINTERFACE darfs sein
		}
	}
	_ASSERTE(m_PSE.IsValid());

// den Aufruf einfach an das Objekt weiterleiten
WTriasExtInit PSI;

	if (SUCCEEDED(m_PSE -> QueryInterface (__uuidof(ITriasExtInit), PSI.ppv())))
		return PSI -> Initialize (pidl, lpdobj, hkeyProgID);

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Helperfunktionen
HRESULT CManageParamDlg::EnsureConnectedCTF()
{
	TX_ASSERT(!!m_spUnkSite);		// SetSite muß gerufen worden sein

	try {
	// Koordinatensystem vom SiteObjekt besorgen
	WTRiASPropertyBase PropBase (m_spUnkSite);
	WTRiASProperties Props;

		THROW_FAILED_HRESULT(PropBase -> get_Properties (Props.ppi()));

	IUnknown *pIUnk = GetProperty (Props, g_cbCTFService, (IUnknown *)NULL);

		m_PSE = pIUnk;
		if (NULL != pIUnk)
			pIUnk -> Release();

	} catch (_com_error &e) {
	// E_NOINTERFACE darfs sein (CTF unterstützt keinen ConfigDlg)
		if (E_NOINTERFACE != _COM_ERROR(e)) {
			COM_TRACECOMERROR(e); 
			COM_ASSERT_EX(e); 
		}
		return _COM_ERROR(e);
	}
	return S_OK;
}

