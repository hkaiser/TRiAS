// PropertyAction, welche eine Statistik der Objekte anzeigt
// File: OBJSTATP.CPP

#include "pheader.h"		// vorübers. Header
#include "resource.h"		// Resource-Konstanten

//	TRIAS-Header
#include <ospace/com/iterenum.h>

//	allg. Header
//#include <int64.h>			// LARGE

// GUID-Header
#include <xtsnguid.h>
#include <dirisole.h>		// CLSID_DataTransferObject
#include <triashelper.h>
#include <initguid.h>           
#include "rsltguid.h"		// zug. GUID

#include <hpp/propactb.hpp>	// Basisklasse			// fje
#include <hpp/datahelp.hpp>	// Get/SetEnumLongData

#include "objstat.hpp"		// zug. Dialog CObjStatDlg
#include "objstatp.hpp"		// zug. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//  externe Variablen
extern const char ExtensionName [];		// Name der Erweiterung

///////////////////////////////////////////////////////////////////////////////
// benötigte InterfaceWrapper
DefineSmartInterface(DataObject);
DefineEnumIIDWrapper(LONG);		// CIID_LONGEnum
DefineSmartInterface(EnumObjectsByNumber);	

CResultPropAction :: CResultPropAction (void)
{
	m_pCfgDlg = NULL;
	m_hDex = NULL;
	m_bIsInitialized = FALSE;

	try 
	{
	//	Erweiterung laden
		LOADEXTENSIONEX le;
		memset (&le, 0, sizeof (LOADEXTENSIONEX));
		le.m_pDesc = NULL;
		le.m_pName = ExtensionName;
		le.m_iMode = LEFullLoad;
		le.m_fGlobal = TRUE;		
		if (m_hDex = DEX_ExternalLoadExtensionEx (le))
			VERIFY (m_strDesc.LoadString(IDS_HELPDESC_RESULT)); 
	} 
	catch (CException *e)
	{
		e -> ReportError ();
		e -> Delete ();
	}
}

CResultPropAction :: ~CResultPropAction (void)
{
	DELETE_OBJ (m_pCfgDlg);
}

void CResultPropAction :: FinalRelease (void)
{
	if (m_hDex)
	{
	//	Erweiterung entladen
		LOADEXTENSIONEX le;
		memset (&le, 0, sizeof (LOADEXTENSIONEX));
		le.m_pDesc = NULL;
		le.m_pName = ExtensionName;
		le.m_iMode = LENoLoad;
		le.m_fGlobal = TRUE;		
		DEX_ExternalUnLoadExtensionEx (le);
		m_hDex = NULL;
	}
}

//////////////////////////////////////////////////////////////////////////////
// IClassProperty specific functions 
STDMETHODIMP CResultPropAction::GetPropInfo (LPSTR pBuffer, WORD wLen, DWORD *pdwFlags)
{
	try {
		if (NULL == m_hDex)
			return E_FAIL;

		if (NULL != pBuffer && wLen > 0) {
		// Namen der Property kopieren
			ULONG ulLen= min (wLen-1, m_strDesc.GetLength());
			strncpy (pBuffer, m_strDesc, ulLen);
			pBuffer[ulLen] = '\0';
		}
	} catch (...) {
		return E_FAIL;
	}

//	wenn gewünscht, Flags übergeben
	if (pdwFlags) {
		*pdwFlags = PROPCAPS_ACTION_SINK_MULTI|PROPCAPS_ACTION_SOURCE;
	}

return NOERROR;
}

STDMETHODIMP CResultPropAction::HelpInfo (LPSTR pBuffer, ULONG ulLen, LPSTR pHelpFile, ULONG *pulHelpCtx)
{
	try {
		if (NULL == m_hDex)
			return E_FAIL;

		if (NULL != pBuffer && ulLen > 0) {
		// Beschreibung übergeben
		WORD wLen = min ((WORD) ulLen-1, m_strDesc.GetLength());

			strncpy (pBuffer, m_strDesc, wLen);
			pBuffer[ulLen] = '\0';
		}
	} catch (...) {
		return E_FAIL;
	}

// HelpFileInfo übergeben
	if (pHelpFile) pHelpFile[0] = '\0';
	if (pulHelpCtx) *pulHelpCtx = 0L;
	
return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// IPropertyAction methods 
STDMETHODIMP CResultPropAction::AddConfigPages (
				LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam, 
			    LPCSTR pcDesc, UINT *puiCnt)
{
	try 
	{
		if (NULL == m_hDex)
			return E_FAIL;

	//	zugehörigen ConfigDialog (PropertyPage(s)) anlegen
		DELETE_OBJ(m_pCfgDlg);	// evtl. vorherigen freigeben

		m_pCfgDlg = CObjStatDlg::CreateInstance ();
		if (NULL == m_pCfgDlg) 
			_com_issue_error (E_OUTOFMEMORY);

		HPROPSHEETPAGE hPSP = NULL;
		PROPSHEETPAGE psp;

		memcpy(&psp, &m_pCfgDlg->m_psp, sizeof(PROPSHEETPAGE));
		if (pcDesc && *pcDesc)
		{
			psp.dwFlags |= PSP_USETITLE;
			psp.pszTitle = pcDesc;
		}

		hPSP = CreatePropertySheetPage (&psp);
		
		if (NULL == hPSP)
			_com_issue_error (E_OUTOFMEMORY);
	
		if (!(*lpfnAddPage) (hPSP, lParam))  
			return E_FAIL;

		if (puiCnt) 
			*puiCnt = 1;		// eine Seite ist dazu gekommen
	} 
	catch (_com_error& hr_result) 
	{
		DELETE_OBJ (m_pCfgDlg);
		if (puiCnt) 
			*puiCnt = 0;
		return _COM_ERROR (hr_result);
	}
	
	return NOERROR;
}

STDMETHODIMP CResultPropAction::PreConfigPages (IDataObject *pIDataObj, DWORD dwFlags)
{
	if (NULL == pIDataObj)
		return E_POINTER;

	if (NULL == m_hDex)
		return E_FAIL;

	m_pCfgDlg -> SetFlags (dwFlags);

WEnumObjectsByNumber IEnumObj;
HRESULT hr = GetEnumLONGData (pIDataObj, IEnumObj.ppi());

	if (FAILED(hr)) return hr;

return m_pCfgDlg -> SetEnumLONG (IEnumObj);
}

STDMETHODIMP CResultPropAction::DoAction (IDataObject *, DWORD)
{
	return NOERROR;
}

STDMETHODIMP CResultPropAction::EndAction (DWORD, IDataObject **ppDataObj)
{
	if (NULL == ppDataObj)
		return E_POINTER;
		
	if (NULL == m_hDex)
		return E_FAIL;

WEnumObjectsByNumber IEnumObj;
HRESULT hr = m_pCfgDlg -> GetEnumLONG (IEnumObj.ppi());
	
	if (FAILED(hr)) return hr;

// DataObject generieren
	*ppDataObj = NULL;

	try {
	WDataObject IDO;
	
		hr = CoCreateInstance (CLSID_DataTransferObject, NULL, CLSCTX_INPROC_SERVER,
							   IID_IDataObject, IDO.ppv()); 
		if (FAILED(hr)) _com_issue_error (hr);

	HRESULT hr2 = SetEnumLONGData (IEnumObj, IDO);
		
		if (FAILED(hr2)) _com_issue_error (hr2);
	
		*ppDataObj = IDO.detach();

	} catch (_com_error& hr_result) {
		DELETE_OBJ (m_pCfgDlg);	// DialogPage freigeben
		return _COM_ERROR (hr_result);
	}

//	letzter Enumerator/PropAction erzeugt lediglich eine Objektmenge
	DELETE_OBJ (m_pCfgDlg);		// DialogPage freigeben

return hr;
}

///////////////////////////////////////////////////////////////
// IPersist methods
STDMETHODIMP CResultPropAction::GetClassID (LPCLSID lpClassID)
{
	if (NULL == lpClassID)
		return E_POINTER;

	*lpClassID = CLSID_ResultPropAction;
	return NOERROR;
}

//	IPersistStreamInit method
STDMETHODIMP CResultPropAction::InitNew (void)
{
	if (NULL == m_hDex)
		return E_FAIL;

	if (m_bIsInitialized)
		return E_UNEXPECTED;		// already initialized with Load

	m_bIsInitialized = TRUE;
	return NOERROR;
}

// IPersistStream methods
STDMETHODIMP CResultPropAction::IsDirty (void)
{
	return S_FALSE;
}

STDMETHODIMP CResultPropAction::GetSizeMax (ULARGE_INTEGER *pcbSize)
{
	if (NULL == pcbSize) return E_POINTER;

ULARGE_INTEGER cbSize;
HRESULT hr = CPropertyAction::GetSizeMax (&cbSize);

	if (FAILED(hr)) return hr;

	*pcbSize = cbSize;
	return S_OK;
}

STDMETHODIMP CResultPropAction::Load (LPSTREAM pStm)
{
	if (NULL == m_hDex)
		return E_FAIL;

	if (m_bIsInitialized)
		return E_UNEXPECTED;		// already initialized with InitNew

HRESULT hr = CPropertyAction::Load (pStm);

	if (FAILED(hr)) 
		return hr;

	m_bIsInitialized = TRUE;

return NOERROR;
}

STDMETHODIMP CResultPropAction::Save (LPSTREAM pStm, BOOL fClearDirty)
{
//	zuerst Bezeichner wegschreiben
	HRESULT hr = CPropertyAction::Save (pStm, fClearDirty);

	if (FAILED(hr)) return hr;

	return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// IPropertyInfo specific functions 
STDMETHODIMP CResultPropAction::SetPropInfo (LPCSTR pcBuffer, DWORD dwFlags) 
{
	if (NULL == m_hDex)
		return E_FAIL;

	if (NULL == pcBuffer) return E_POINTER;

	m_strDesc = pcBuffer;
	return NOERROR;
}


