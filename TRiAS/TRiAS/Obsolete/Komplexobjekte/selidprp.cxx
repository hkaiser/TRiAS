// PropertyAction, welche Ident/Objekttypen auswählt und zusammenstellt -------
// File: SELIDPRP.CXX

#include "featurep.hxx"
#include "feature.h"

#include <eonrguid.h>
#include <propguid.h>

#include <pdataobj.hxx>

#include "selidlst.hxx"
#include "selident.hxx"
#include "selidprp.hxx"

DefineSmartInterface(DataObject);

// 0E54C9E0-20DE-11CF-BA55-00AA0018497C	
// DEFINE_GUID(CLSID_SelectIdentObjTyp, 0x0E54C9E0L, 0x20DE, 0x11CF, 0xBA, 0x55, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
// 'CLSPROP_ROOT\Recherche\Objektauswahl nach Identifikator und Typ'

#pragma warning (disable: 4355)

CSelIDPropAct :: CSelIDPropAct (void)
	       : m_PropAct (this, this)
{
}

#pragma warning (default: 4355)

CSelIDPropAct :: ~CSelIDPropAct (void)
{
}

CSelIDPropAct *CSelIDPropAct :: CreateInstance (void)
{
	try {
	CSelIDPropAct *pProp = new CSelIDPropAct();

		if (NULL == pProp || !pProp -> FInit()) {
			DELETE(pProp);
			return NULL;
		}
		pProp -> AddRef();
		return pProp;
	} catch (...) {
		return NULL;
	}
}

bool CSelIDPropAct :: FInit (void)
{
	if (!m_PropAct.FInit()) return false;

return true;
}


// *** IUnknown methods *** ---------------------------------------------------
STDMETHODIMP CSelIDPropAct :: QueryInterface (REFIID riid, LPVOID *ppvObj)
{
	if (riid == IID_IPropertyAction) {
		*ppvObj = &m_PropAct;
		LPUNKNOWN(*ppvObj) -> AddRef();
		return NOERROR;
	}

return CClassProperty :: QueryInterface (riid, ppvObj);
}


// *** IClassProperty specific functions *** ----------------------------------
STDMETHODIMP CSelIDPropAct :: GetPropInfo (LPSTR pBuffer, WORD wLen, DWORD *pdwFlags)
{
	try {
		if (NULL != pBuffer && wLen > 0) {
		// Namen der Property kopieren
		ResString resPropInfo (ResID (IDS_PROPINFO_IDENTOTYP, &g_pTE -> RF()), 64);
		ULONG ulLen = tmin ((size_t)(wLen-1), strlen(resPropInfo));

			strncpy (pBuffer, resPropInfo, ulLen);
			pBuffer[ulLen] = '\0';
		}
	} catch (...) {
		return ResultFromScode (E_FAIL);
	}

// wenn gewünscht, Flags übergeben
	if (pdwFlags) *pdwFlags = PROPCAPS_ACTION_SOURCE;

return NOERROR;
}


STDMETHODIMP CSelIDPropAct :: Reset(void)
{
	return ResultFromScode (E_NOTIMPL);
}

STDMETHODIMP_(ULONG) CSelIDPropAct :: Count (void)
{
	return 0L;
}

STDMETHODIMP CSelIDPropAct :: HelpInfo (LPSTR pBuffer, ULONG wLen, LPSTR pHelpFile, ULONG *pulHelpCtx)
{
	try {
		if (NULL != pBuffer && wLen > 0) {
		// Beschreibung übergeben
		ResString resHelp (ResID (IDS_HELPDESC_IDENTOTYP, &g_pTE -> RF()), 128);
		ULONG ulLen = tmin ((size_t)(wLen-1), strlen(resHelp));

			strncpy (pBuffer, resHelp, ulLen);
			pBuffer[ulLen] = '\0';
		}
	} catch (...) {
		return ResultFromScode (E_FAIL);
	}

// HelpFileInfo übergeben
	if (pHelpFile) pHelpFile[0] = '\0';
	if (pulHelpCtx) *pulHelpCtx = 0L;
	
return NOERROR;
}

// Implementation des IActionProperty - Interfaces ----------------------------
CSelIDPropAct :: 
CImpPropAct :: CImpPropAct (LPUNKNOWN pIUnk, LPCLASSPROPERTY pIProp)
	     : CPropertyAction (pIUnk)
{
	m_pCfgDlg = NULL;
	m_pIClsProp = pIProp;	// AddRef nicht notwendig
}

CSelIDPropAct :: 
CImpPropAct :: ~CImpPropAct (void)
{
	DELETE(m_pCfgDlg);
}

// *** IPropertyAction methods ------------------------------------------------
STDMETHODIMP CSelIDPropAct :: 
CImpPropAct :: AddConfigPages (LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam, 
			       DWORD dwFlags, UINT *puiCnt)
{
HRESULT hr = ResultFromScode (E_FAIL);
char cbCaption[128];

	try {
	// von zugehöriger ClassProperty unseren Namen besorgen
		m_pIClsProp -> GetPropInfo (cbCaption, sizeof(cbCaption), NULL);

	// zugehörigen ConfigDialog (PropertyPage(s)) anlegen
		DELETE(m_pCfgDlg);	// evtl. vorherigen freigeben
		m_pCfgDlg = CSelectIdentDlg::CreateInstance (
				IDD_SELECTIDS_WIZ, cbCaption, dwFlags, g_pTE -> RF());
		if (NULL == m_pCfgDlg) 
			throw (hr = ResultFromScode (E_OUTOFMEMORY));

	//
	// Achtung MFC-Falle !
	// Normalerweise müßte an dieser Stelle lpfnAddPage mit unserem 
	// HPROPERTYPAGE gerufen werden, wir aber wissen (darf man das ?), daß
	// sich hinter dem eigentlich durchzureichendem lParam der Pointer auf
	// unsern PropertySheet verbirgt.
	//
		if (UINT_MAX == ((CPropertySheet *)lParam) -> AddPage (m_pCfgDlg))
			throw (hr = ResultFromScode (E_UNEXPECTED));

		if (puiCnt) *puiCnt = 1;

	} catch (HRESULT hr_result) {
		DELETE (m_pCfgDlg);
		if (puiCnt) *puiCnt = 0;
		return hr_result;
	}
	
return NOERROR;
}

STDMETHODIMP CSelIDPropAct :: 
CImpPropAct :: BeginAction (IProgressIndicator *)
{
	return ResultFromScode (E_NOTIMPL);
}

STDMETHODIMP CSelIDPropAct :: 
CImpPropAct :: DoAction (IDataObject *, DWORD)
{
	return ResultFromScode (E_NOTIMPL);
}


STDMETHODIMP CSelIDPropAct :: 
CImpPropAct :: EndAction (DWORD, IDataObject **ppDataObj)
{
WEnumLONG IEnumObj;
HRESULT hr = m_pCfgDlg -> GetEnumLONG (IEnumObj.ppi());
	
	if (FAILED(hr)) return hr;

// DataObject generieren
CDataObject *pDataObj = CDataObject::CreateInstance (NULL, NULL);

	if (NULL == pDataObj) return ResultFromScode (E_OUTOFMEMORY);
	*ppDataObj = NULL;

	try {
	WDataObject IDO = pDataObj;
		
		if (FAILED(GetLastHRESULT())) throw GetLastHRESULT();
		RELEASE(pDataObj);

	HRESULT hr2 = SetEnumLONGData (IEnumObj, CLSID_EnumObjectsByNumber, IDO);
		if (FAILED(hr2)) throw hr2;

		*ppDataObj = IDO.detach();

	} catch (HRESULT hr_result) {
		RELEASE(pDataObj);

		DELETE (m_pCfgDlg);	// DialogPage freigeben
		return hr_result;
	}

	if (S_FALSE != GetScode(hr)) {
	// letzter Enumerator
		DELETE (m_pCfgDlg);	// DialogPage freigeben
	}

return hr;
}

