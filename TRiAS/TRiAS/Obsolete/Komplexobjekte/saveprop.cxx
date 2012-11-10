// PropertyAction, welche Ident/Objekttypen auswählt und zusammenstellt -------
// File: SELRLPRP.CXX

#include "featurep.hxx"
#include "feature.h"

#include <eonrguid.h>
#include <propguid.h>

#include <clsfyprp.h>

#include <pdataobj.hxx>

#include "selrlprp.hxx"

DeclareSmartInterface(DataObject);

// 0E54C9E0-20DE-11CF-BA55-00AA0018497C	
// DEFINE_GUID(CLSID_SelectIdentObjTyp, 0x0E54C9E0L, 0x20DE, 0x11CF, 0xBA, 0x55, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
// 'CLSPROP_ROOT\Recherche\Bilden von Objektrelationen'

#pragma warning (disable: 4355)

CSavePropValue :: CSavePropValue (ITriasXtensionSite *pIXtnSite)
	        : m_PropAct (this, this, pIXtnSite)
{
}

#pragma warning (default: 4355)

CSavePropValue :: ~CSavePropValue (void)
{
}

CSavePropValue *CSavePropValue :: CreateInstance (ITriasXtensionSite *pIXtnSite)
{
	try {
	CSavePropValue *pProp = new CSavePropValue (pIXtnSite);
		
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

bool CSavePropValue :: FInit (void)
{
	if (!m_PropAct.FInit()) return false;

return true;
}


// *** IUnknown methods *** ---------------------------------------------------
STDMETHODIMP CSavePropValue :: QueryInterface (REFIID riid, LPVOID *ppvObj)
{
	if (riid == IID_IPropertyAction) {
		*ppvObj = &m_PropAct;
		LPUNKNOWN(*ppvObj) -> AddRef();
		return NOERROR;
	}

return CClassProperty :: QueryInterface (riid, ppvObj);
}


// *** IClassProperty specific functions *** ----------------------------------
STDMETHODIMP CSavePropValue :: GetPropInfo (LPSTR pBuffer, WORD wLen, DWORD *pdwFlags)
{
	try {
		if (NULL != pBuffer && wLen > 0) {
		// Namen der Property kopieren
		ResString resPropInfo (ResID (IDS_PROPINFO_SAVEPROPVALUE, &g_pTE -> RF()), 64);
		ULONG ulLen = tmin (size_t(wLen-1), strlen(resPropInfo));

			strncpy (pBuffer, resPropInfo, ulLen);
			pBuffer[ulLen] = '\0';
		}
	} catch (...) {
		return ResultFromScode (E_FAIL);
	}

// wenn gewünscht, Flags übergeben
	if (pdwFlags) *pdwFlags = PROPCAPS_ACTION_SINK_MULTI;

return NOERROR;
}


STDMETHODIMP CSavePropValue :: Reset(void)
{
	return ResultFromScode (E_NOTIMPL);
}

STDMETHODIMP_(ULONG) CSavePropValue :: Count (void)
{
	return 0L;
}

STDMETHODIMP CSavePropValue :: HelpInfo (LPSTR pBuffer, ULONG wLen, LPSTR pHelpFile, ULONG *pulHelpCtx)
{
	try {
		if (NULL != pBuffer && wLen > 0) {
		// Beschreibung übergeben
		ResString resHelp (ResID (IDS_HELPDESC_SAVEPROPVALUE, &g_pTE -> RF()), 128);
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
CSavePropValue :: 
CImpPropAct :: CImpPropAct (LPUNKNOWN pIUnk, LPCLASSPROPERTY pIProp,
			    ITriasXtensionSite *pIXtnSite)
	     : CPropertyAction (pIUnk), m_XtnSite(pIXtnSite)
{
	m_pIClsProp = pIProp;	// AddRef nicht notwendig
}

CSavePropValue :: 
CImpPropAct :: ~CImpPropAct (void)
{
}

// *** IPropertyAction methods ------------------------------------------------
STDMETHODIMP CSavePropValue :: 
CImpPropAct :: AddConfigPages (LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam, 
			       DWORD dwFlags, UINT *puiCnt)
{
	*puiCnt = 0;
	return NOERROR;		// keine Pages hinzuzufügen
}

STDMETHODIMP CSavePropValue :: 
CImpPropAct :: BeginAction (IProgressIndicator *)
{
	return ResultFromScode (E_NOTIMPL);
}

STDMETHODIMP CSavePropValue :: 
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

// lediglich den Wert der Objekteigenschaft für diese Objektgruppe zu unserer
// Liste hinzufügen
char cbBuffer[4*_MAX_PATH];
	
	hr = ITempl.GetTemplate (cbBuffer, sizeof(cbBuffer), NULL);

	m_strResult += cbBuffer;
	m_strResult += "\r\n";		// nächste Zeile

return NOEROR;
}


STDMETHODIMP CSavePropValue :: 
CImpPropAct :: EndAction (DWORD, IDataObject **ppDataOut)
{
	*ppDataOut = NULL;

	return S_FALSE;
}

