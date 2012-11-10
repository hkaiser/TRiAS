// PropertyAction, welche Ident/Objekttypen auswählt und zusammenstellt -------
// File: SELRLPRP.CXX

#include "featurep.hxx"
#include "feature.h"

#include <eonrguid.h>
#include <propguid.h>

#include <clsfyprp.h>

#include <pdataobj.hxx>

#include "selrelst.hxx"
#include "selrcode.hxx"
#include "selrlprp.hxx"

DefineSmartInterface(DataObject);

// 0E54C9E0-20DE-11CF-BA55-00AA0018497C	
// DEFINE_GUID(CLSID_SelectIdentObjTyp, 0x0E54C9E0L, 0x20DE, 0x11CF, 0xBA, 0x55, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
// 'CLSPROP_ROOT\Recherche\Bilden von Objektrelationen'

#pragma warning (disable: 4355)

CGenKomplexObj :: CGenKomplexObj (ITriasXtensionSite *pIXtnSite)
	        : m_PropAct (this, this, pIXtnSite)
{
}

#pragma warning (default: 4355)

CGenKomplexObj :: ~CGenKomplexObj (void)
{
}

CGenKomplexObj *CGenKomplexObj :: CreateInstance (ITriasXtensionSite *pIXtnSite)
{
	try {
	CGenKomplexObj *pProp = new CGenKomplexObj (pIXtnSite);
		
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

bool CGenKomplexObj :: FInit (void)
{
	if (!m_PropAct.FInit()) return false;

return true;
}


// *** IUnknown methods *** ---------------------------------------------------
STDMETHODIMP CGenKomplexObj :: QueryInterface (REFIID riid, LPVOID *ppvObj)
{
	if (riid == IID_IPropertyAction) {
		*ppvObj = &m_PropAct;
		LPUNKNOWN(*ppvObj) -> AddRef();
		return NOERROR;
	}

return CClassProperty :: QueryInterface (riid, ppvObj);
}


// *** IClassProperty specific functions *** ----------------------------------
STDMETHODIMP CGenKomplexObj :: GetPropInfo (LPSTR pBuffer, WORD wLen, DWORD *pdwFlags)
{
	try {
		if (NULL != pBuffer && wLen > 0) {
		// Namen der Property kopieren
		ResString resPropInfo (ResID (IDS_PROPINFO_GENKOMPLEXOBJS, &g_pTE -> RF()), 64);
		ULONG ulLen = tmin (size_t(wLen-1), strlen(resPropInfo));

			strncpy (pBuffer, resPropInfo, ulLen);
			pBuffer[ulLen] = '\0';
		}
	} catch (...) {
		return ResultFromScode (E_FAIL);
	}

// wenn gewünscht, Flags übergeben
	if (pdwFlags) *pdwFlags = PROPCAPS_ACTION_SINK_MULTI|PROPCAPS_ACTION_SOURCE;

return NOERROR;
}


STDMETHODIMP CGenKomplexObj :: Reset(void)
{
	return ResultFromScode (E_NOTIMPL);
}

STDMETHODIMP_(ULONG) CGenKomplexObj :: Count (void)
{
	return 0L;
}

STDMETHODIMP CGenKomplexObj :: HelpInfo (LPSTR pBuffer, ULONG wLen, LPSTR pHelpFile, ULONG *pulHelpCtx)
{
	try {
		if (NULL != pBuffer && wLen > 0) {
		// Beschreibung übergeben
		ResString resHelp (ResID (IDS_HELPDESC_GENKOMPLEXOBJS, &g_pTE -> RF()), 128);
		ULONG ulLen = tmin (size_t(wLen-1), strlen(resHelp));

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
CGenKomplexObj :: 
CImpPropAct :: CImpPropAct (LPUNKNOWN pIUnk, LPCLASSPROPERTY pIProp,
			    ITriasXtensionSite *pIXtnSite)
	     : CPropertyAction (pIUnk), m_XtnSite(pIXtnSite)
{
	m_pCfgDlg = NULL;
	m_pIClsProp = pIProp;	// AddRef nicht notwendig
}

CGenKomplexObj :: 
CImpPropAct :: ~CImpPropAct (void)
{
	DELETE(m_pCfgDlg);
}

// *** IPropertyAction methods ------------------------------------------------
STDMETHODIMP CGenKomplexObj :: 
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
		m_pCfgDlg = CSelectRCodeDlg::CreateInstance (
				IDD_SELECTREL_WIZ, cbCaption, dwFlags, g_pTE -> RF());
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

STDMETHODIMP CGenKomplexObj :: 
CImpPropAct :: BeginAction (IProgressIndicator *)
{
	return ResultFromScode (E_NOTIMPL);
}

STDMETHODIMP CGenKomplexObj :: 
CImpPropAct :: DoAction (IDataObject *pDataObj, DWORD)
{
WEnumLONG IEnumObj;
HRESULT hr = GetEnumLONGData (pDataObj, CLSID_EnumObjectsByNumber, IEnumObj.ppi());

	if (FAILED(hr)) return hr;

WPropertyTemplate ITempl;	// zu setzende Objekteigenschaft

	{
	WObjectProperty IOProp;

		if (SUCCEEDED(GetObjProperty (m_XtnSite, pDataObj, IOProp.ppi())))
			ITempl = IOProp;
	}	// Fehler ist nicht fatal

return m_pCfgDlg -> SetEnumLONG (IEnumObj, ITempl);
}


STDMETHODIMP CGenKomplexObj :: 
CImpPropAct :: EndAction (DWORD, IDataObject **ppDataOut)
{
	*ppDataOut = NULL;

WEnumLONG IEnumObj;
HRESULT hr = m_pCfgDlg -> GetEnumLONG (IEnumObj.ppi());
	
	if (FAILED(hr)) return hr;
	if (!IEnumObj) return NOERROR;

// DataObject generieren
CDataObject *pDataObj = CDataObject::CreateInstance (NULL, NULL);

	if (NULL == pDataObj) return ResultFromScode (E_OUTOFMEMORY);

	try {
	// IDataObject abfragen
	WDataObject IDO = pDataObj;
	
//		if (FAILED(GetLastHRESULT())) throw GetLastHRESULT();
		RELEASE(pDataObj);

	// Daten und Formate im DataObjekt speichern
	HRESULT hr2 = SetEnumLONGData (IEnumObj, CLSID_EnumObjectsByNumber, IDO);

		if (FAILED(hr2)) throw hr2;

	// Resultat setzen
		*ppDataOut = IDO.detach();

	} catch (HRESULT hr_result) {
		RELEASE(pDataObj);

		DELETE (m_pCfgDlg);	// DialogPage freigeben
		return hr_result;
	}

	if (S_FALSE != GetScode(hr)) {
	// letzter Auffruf
		DELETE (m_pCfgDlg);	// DialogPage freigeben
	}

return hr;
}

