// PropertyAction für Classifikation nach Objekteigenschaft -------------------
// File: CLSFYPRP.CXX

#include "featurep.hxx"
#include "feature.h"

#include <eonrguid.h>
#include <propguid.h>

#include <pdataobj.hxx>

#include "seloprpt.hxx"
#include "seloprop.hxx"
#include "clsfyprp.hxx"

DefineSmartInterface(DataObject);

// 0E54C9E1-20DE-11CF-BA55-00AA0018497C	
// DEFINE_GUID(CLSID_ClassifyByObjProp, 0x0E54C9E1L, 0x20DE, 0x11CF, 0xBA, 0x55, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
// 'CLSPROP_ROOT\Recherche\Gruppieren von Objekten'

#pragma warning (disable: 4355)

CClsfyPropAct :: CClsfyPropAct (ITriasXtensionSite *pIXtnSite)
	       : m_PropAct (this, this, pIXtnSite)
{
}

#pragma warning (default: 4355)

CClsfyPropAct :: ~CClsfyPropAct (void)
{
}

CClsfyPropAct *CClsfyPropAct :: CreateInstance (ITriasXtensionSite *pIXtnSite)
{
	try {
	CClsfyPropAct *pProp = new CClsfyPropAct (pIXtnSite);
		
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

bool CClsfyPropAct :: FInit (void)
{
	if (!m_PropAct.FInit()) return false;

return true;
}


// *** IUnknown methods *** ---------------------------------------------------
STDMETHODIMP CClsfyPropAct :: QueryInterface (REFIID riid, LPVOID *ppvObj)
{
	if (riid == IID_IPropertyAction) {
		*ppvObj = &m_PropAct;
		LPUNKNOWN(*ppvObj) -> AddRef();
		return NOERROR;
	}

return CClassProperty :: QueryInterface (riid, ppvObj);
}


// *** IClassProperty specific functions *** ----------------------------------
STDMETHODIMP CClsfyPropAct :: GetPropInfo (LPSTR pBuffer, WORD wLen, DWORD *pdwFlags)
{
	try {
		if (NULL != pBuffer && wLen > 0) {
		// Namen der Property kopieren
		ResString resPropInfo (ResID (IDS_PROPINFO_CLASSIFYOBJ, &g_pTE -> RF()), 64);
		ULONG ulLen = tmin (size_t(wLen-1), strlen(resPropInfo));

			strncpy (pBuffer, resPropInfo, ulLen);
			pBuffer[ulLen] = '\0';
		}
	} catch (...) {
		return ResultFromScode (E_FAIL);
	}

// wenn gewünscht, Flags übergeben
	if (pdwFlags) *pdwFlags = PROPCAPS_ACTION_SINK|PROPCAPS_ACTION_SOURCE_MULTI;

return NOERROR;
}


STDMETHODIMP CClsfyPropAct :: Reset(void)
{
	return ResultFromScode (E_NOTIMPL);
}

STDMETHODIMP_(ULONG) CClsfyPropAct :: Count (void)
{
	return 0L;
}

STDMETHODIMP CClsfyPropAct :: HelpInfo (LPSTR pBuffer, ULONG wLen, LPSTR pHelpFile, ULONG *pulHelpCtx)
{
	try {
		if (NULL != pBuffer && wLen > 0) {
		// Beschreibung übergeben
		ResString resHelp (ResID (IDS_HELPDESC_CLASSIFYOBJ, &g_pTE -> RF()), 128);
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
CClsfyPropAct :: 
CImpPropAct :: CImpPropAct (LPUNKNOWN pIUnk, IClassProperty *pIProp, ITriasXtensionSite *pIXtnSite)
	     : CPropertyAction (pIUnk), m_XtnSite(pIXtnSite)
{
	m_pCfgDlg = NULL;
	m_pIClsProp = pIProp;	// AddRef nicht notwendig
}

CClsfyPropAct :: 
CImpPropAct :: ~CImpPropAct (void)
{
	DELETE(m_pCfgDlg);
}

// *** IPropertyAction methods ------------------------------------------------
STDMETHODIMP CClsfyPropAct :: 
CImpPropAct :: AddConfigPages (LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam, 
			       DWORD dwFlags, UINT *puiCnt)
{
HRESULT hr = ResultFromScode (E_FAIL);
char cbCaption[_MAX_PATH];

	try {
	// von zugehöriger ClassProperty unseren Namen besorgen
		m_pIClsProp -> GetPropInfo (cbCaption, sizeof(cbCaption), NULL);

	// Liste aller installierten Objekteigenschaften besorgen
	WObjectProps IObjProps = m_XtnSite;
	
		if (FAILED(GetLastHRESULT())) throw GetLastHRESULT();

	// zugehörigen ConfigDialog (PropertyPage(s)) anlegen
		DELETE(m_pCfgDlg);	// vorherigen evtl. löschen
		m_pCfgDlg = CClassifyDlg::CreateInstance (IDD_OBJECTROP_WIZ, cbCaption, 
							  dwFlags, g_pTE -> RF(), IObjProps);
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

STDMETHODIMP CClsfyPropAct :: 
CImpPropAct :: BeginAction (IProgressIndicator *)
{
	return ResultFromScode (E_NOTIMPL);
}

STDMETHODIMP CClsfyPropAct :: 
CImpPropAct :: DoAction (IDataObject *pDataObj, DWORD)
{
WEnumLONG IEnumObj;
HRESULT hr = GetEnumLONGData (pDataObj, CLSID_EnumObjectsByNumber, IEnumObj.ppi());

	if (FAILED(hr)) return hr;

return m_pCfgDlg -> SetEnumLONG (IEnumObj);
}


STDMETHODIMP CClsfyPropAct :: 
CImpPropAct :: EndAction (DWORD, IDataObject **ppDataOut)
{
	*ppDataOut = NULL;

WEnumLONG IEnumObj;
os_string strObjProp;
HRESULT hr = m_pCfgDlg -> GetNextEnumLONG (IEnumObj.ppi(), strObjProp);

	if (FAILED(hr)) return hr;
	if (!IEnumObj) return NOERROR;

// DataObject generieren
CDataObject *pDataObj = CDataObject::CreateInstance (NULL, NULL);

	if (NULL == pDataObj) 
		return ResultFromScode (E_OUTOFMEMORY);

	try {
	// IDataObject abfragen
	WDataObject IDO = pDataObj;

		if (FAILED(GetLastHRESULT())) throw GetLastHRESULT();
		RELEASE(pDataObj);

	// Daten und Formate im DataObjekt speichern
	// 1. Liste aller Objekte
	HRESULT hr2 = SetEnumLONGData (IEnumObj, CLSID_EnumObjectsByNumber, IDO);
		
		if (FAILED(hr2)) throw hr2;

	// 2. zu Grunde gelegte Objekteigenschaft
	os_string strObjPropName;

		m_pCfgDlg -> GetObjProp (strObjPropName);
		hr2 = SetObjPropTemplate (m_XtnSite, strObjPropName, strObjProp, IDO);
//		if (FAILED(hr2)) throw hr2;	// wenn Fehler, dann weiter

	// Resultat setzen
		*ppDataOut = IDO.detach();

	} catch (HRESULT hr_result) {
		RELEASE(pDataObj);

		DELETE (m_pCfgDlg);	// DialogPage freigeben
		return hr_result;
	}

	if (GetScode(S_FALSE) != hr) {
	// nur wenn's noch weiter geht, nicht löschen
		DELETE(m_pCfgDlg);
	}

return hr;
}

