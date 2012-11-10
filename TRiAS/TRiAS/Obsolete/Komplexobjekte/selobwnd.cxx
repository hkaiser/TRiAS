// PropertyAction, welche Objekte aus RechercheFenster ausw‰hlt und zusammenstellt
// File: SELOBWND.CXX

#include "featurep.hxx"
#include "feature.h"

#include <eonrguid.h>
#include <propguid.h>

#include <pdataobj.hxx>

#include "selobdlg.hxx"
#include "selobwnd.hxx"

DefineSmartInterface(DataObject);

// 0E54C9EA-20DE-11CF-BA55-00AA0018497C	
// DEFINE_GUID(CLSID_SelectFromObjectWindow, 0x0E54C9EAL, 0x20DE, 0x11CF, 0xBA, 0x55, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
// 'CLSPROP_ROOT\Recherche\Objektauswahl aus Recherchefenster'

#pragma warning (disable: 4355)

CSelObjWndPropAct :: CSelObjWndPropAct (void)
	           : m_PropAct (this, this)
{
}

#pragma warning (default: 4355)

CSelObjWndPropAct :: ~CSelObjWndPropAct (void)
{
}

CSelObjWndPropAct *CSelObjWndPropAct :: CreateInstance (void)
{
	try {
	CSelObjWndPropAct *pProp = new CSelObjWndPropAct();

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

bool CSelObjWndPropAct :: FInit (void)
{
	if (!m_PropAct.FInit()) return false;

return true;
}


// *** IUnknown methods *** ---------------------------------------------------
STDMETHODIMP CSelObjWndPropAct :: QueryInterface (REFIID riid, LPVOID *ppvObj)
{
	if (riid == IID_IPropertyAction) {
		*ppvObj = &m_PropAct;
		LPUNKNOWN(*ppvObj) -> AddRef();
		return NOERROR;
	}

return CClassProperty :: QueryInterface (riid, ppvObj);
}


// *** IClassProperty specific functions *** ----------------------------------
STDMETHODIMP CSelObjWndPropAct :: GetPropInfo (LPSTR pBuffer, WORD wLen, DWORD *pdwFlags)
{
	try {
		if (NULL != pBuffer && wLen > 0) {
		// Namen der Property kopieren
		ResString resPropInfo (ResID (IDS_PROPINFO_OBJWND, &g_pTE -> RF()), 64);
		ULONG ulLen = tmin ((size_t)(wLen-1), strlen(resPropInfo));

			strncpy (pBuffer, resPropInfo, ulLen);
			pBuffer[ulLen] = '\0';
		}
	} catch (...) {
		return ResultFromScode (E_FAIL);
	}

// wenn gew¸nscht, Flags ¸bergeben
	if (pdwFlags) *pdwFlags = PROPCAPS_ACTION_SOURCE;

return NOERROR;
}


STDMETHODIMP CSelObjWndPropAct :: Reset(void)
{
	return ResultFromScode (E_NOTIMPL);
}

STDMETHODIMP_(ULONG) CSelObjWndPropAct :: Count (void)
{
	return 0L;
}

STDMETHODIMP CSelObjWndPropAct :: HelpInfo (LPSTR pBuffer, ULONG wLen, LPSTR pHelpFile, ULONG *pulHelpCtx)
{
	try {
		if (NULL != pBuffer && wLen > 0) {
		// Beschreibung ¸bergeben
		ResString resHelp (ResID (IDS_HELPDESC_OBJWND, &g_pTE -> RF()), 128);
		ULONG ulLen = tmin ((size_t)(wLen-1), strlen(resHelp));

			strncpy (pBuffer, resHelp, ulLen);
			pBuffer[ulLen] = '\0';
		}
	} catch (...) {
		return ResultFromScode (E_FAIL);
	}

// HelpFileInfo ¸bergeben
	if (pHelpFile) pHelpFile[0] = '\0';
	if (pulHelpCtx) *pulHelpCtx = 0L;
	
return NOERROR;
}

// Implementation des IActionProperty - Interfaces ----------------------------
CSelObjWndPropAct :: 
CImpPropAct :: CImpPropAct (LPUNKNOWN pIUnk, LPCLASSPROPERTY pIProp)
	     : CPropertyAction (pIUnk)
{
	m_pCfgDlg = NULL;
	m_pIClsProp = pIProp;	// AddRef nicht notwendig
}

CSelObjWndPropAct :: 
CImpPropAct :: ~CImpPropAct (void)
{
	DELETE(m_pCfgDlg);
}

// *** IPropertyAction methods ------------------------------------------------
STDMETHODIMP CSelObjWndPropAct :: 
CImpPropAct :: AddConfigPages (LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam, 
			       DWORD dwFlags, UINT *puiCnt)
{
HRESULT hr = ResultFromScode (E_FAIL);
char cbCaption[128];

	try {
	// von zugehˆriger ClassProperty unseren Namen besorgen
		m_pIClsProp -> GetPropInfo (cbCaption, sizeof(cbCaption), NULL);

	// zugehˆrigen ConfigDialog (PropertyPage(s)) anlegen
		DELETE(m_pCfgDlg);	// evtl. vorherigen freigeben
		m_pCfgDlg = CSelectObjWndDlg::CreateInstance (
				IDD_SELECTOBJWND_WIZ, cbCaption, dwFlags, g_pTE -> RF());
		if (NULL == m_pCfgDlg) 
			throw (hr = ResultFromScode (E_OUTOFMEMORY));

	//
	// Achtung MFC-Falle !
	// Normalerweise m¸ﬂte an dieser Stelle lpfnAddPage mit unserem 
	// HPROPERTYPAGE gerufen werden, wir aber wissen (darf man das ?), daﬂ
	// sich hinter dem eigentlich durchzureichendem lParam der Pointer auf
	// unsern PropertySheet verbirgt.
	//
		if (UINT_MAX == ((CPropertySheet *)lParam) -> AddPage (m_pCfgDlg))
			throw (hr = ResultFromScode (E_UNEXPECTED));

	// wir haben eine (1) Page hinzugef¸gt
		if (puiCnt) *puiCnt = 1;

	} catch (HRESULT hr_result) {
		DELETE (m_pCfgDlg);
		if (puiCnt) *puiCnt = 0;
		return hr_result;
	}
	
return NOERROR;
}

STDMETHODIMP CSelObjWndPropAct :: 
CImpPropAct :: BeginAction (IProgressIndicator *)
{
	return ResultFromScode (E_NOTIMPL);
}

STDMETHODIMP CSelObjWndPropAct :: 
CImpPropAct :: DoAction (IDataObject *, DWORD)
{
	return ResultFromScode (E_NOTIMPL);
}


STDMETHODIMP CSelObjWndPropAct :: 
CImpPropAct :: EndAction (DWORD, IDataObject **ppDataObj)
{
	*ppDataObj = NULL;

WEnumLONG IEnumObj;
HRESULT hr = m_pCfgDlg -> GetEnumLONG (IEnumObj.ppi());
	
	if (FAILED(hr)) return hr;
	if (!IEnumObj) return NOERROR;

// DataObject generieren, welches Info's ¸ber unser Ergenis enth‰lt
CDataObject *pDataObj = CDataObject::CreateInstance (NULL, NULL);

	if (NULL == pDataObj) return ResultFromScode (E_OUTOFMEMORY);

	try {
	WDataObject IDO = pDataObj;
	
		if (FAILED(GetLastHRESULT())) throw GetLastHRESULT();
		RELEASE(pDataObj);

	// schreiben des EnumLONG ins DataObject
	HRESULT hr2 = SetEnumLONGData (IEnumObj, CLSID_EnumObjectsByNumber, IDO);

		if (FAILED(hr2)) throw hr2;

	// Resultat an n‰chste PropertyAction weiterzureichen
		*ppDataObj = IDO.detach();

	} catch (HRESULT hr_result) {
		RELEASE(pDataObj);

		DELETE (m_pCfgDlg);	// DialogPage freigeben
		return hr_result;
	}

// S_FALSE heiﬂt, daﬂ GetEnumLONG nicht mehr gerufen werden muﬂ
	if (S_FALSE != GetScode(hr)) {	// letzter Enumerator
		DELETE (m_pCfgDlg);	// DialogPage freigeben
	}

return hr;
}

