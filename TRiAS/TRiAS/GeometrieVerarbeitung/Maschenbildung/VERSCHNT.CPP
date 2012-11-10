// PropertyAction, welche Verschnitt von geometrischen Objekten durchführt
// File: VERSCHNT.CPP

#include "pheader.h"		// vorübers. Header
#include "resource.h"		// Resource-Konstanten

//	TRIAS-Header
#include <ospace/com/iterenum.h>
#include <ospace/std/list>	// list

//	allgem. Header
#include <float.h>			// DBL_MIN, DBL_MAX
//#include <int64.h>			// LARGE

// GUID-Header
#include <xtsnguid.h>
#include <dirisole.h>		// CLSID_DataTransferObject
#include <triashelper.h>
#include <initguid.h>           
#include "verguid.h"		// CLSID_VerschnittPropAct

#include <hpp/propactb.hpp>		// Basisklasse			// fje
#include <hpp/datahelp.hpp>		// Get/SetEnumLongData

#define _NO_PARAM_DIAOLOG
#include "paramdlg.hpp"		// CParameters	
#include "verparam.hpp"		// CVerschnittDialog
#include "verschnt.hpp"		// zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//	Konstanten
const UINT uiMaxStreamSize = (2*sizeof (LONG)) + (2*sizeof (double));	// max. Streamgröße

//  externe Variablen
extern const char ExtensionName [];		// Name der Erweiterung

///////////////////////////////////////////////////////////////////////////////
// benötigte InterfaceWrapper
DefineSmartInterface(DataObject);
DefineEnumIIDWrapper(LONG);		// CIID_LONGEnum
// DefineSmartInterface(EnumObjectsByNumber);	

CVerschnittPropAct :: CVerschnittPropAct (void)
{
	m_pCfgDlg = NULL;
	m_bIsDirty = FALSE;
	m_bIsInitialized = FALSE;
	m_bHasInitData = FALSE;
	m_hDex = NULL;
	m_hResult = NOERROR;
	m_bDeleteOldLines = FALSE;
	m_bMarkObjects = FALSE;

	m_dDangleLen = m_dFuzzy = 0.0;
	
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
			VERIFY (m_strDesc.LoadString(IDS_HELPDESC_LINVER)); 
	} 
	catch (CException *e)
	{
		m_hResult = E_OUTOFMEMORY;
		e -> ReportError ();
		e -> Delete ();
	}
}

CVerschnittPropAct :: ~CVerschnittPropAct (void)
{
//	Dialog löschen
	DELETE_OBJ (m_pCfgDlg);
}

void CVerschnittPropAct :: FinalRelease (void)
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

///////////////////////////////////////////////////////////////////////////////
// IClassProperty specific functions 
STDMETHODIMP CVerschnittPropAct::GetPropInfo (LPSTR pBuffer, WORD wLen, DWORD *pdwFlags)
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
		return (m_hResult = E_FAIL);
	}

//	wenn gewünscht, Flags übergeben
	if (pdwFlags) {
		*pdwFlags = PROPCAPS_ACTION_SINK_MULTI|PROPCAPS_ACTION_SOURCE;
	}

return NOERROR;
}

STDMETHODIMP CVerschnittPropAct::HelpInfo (LPSTR pBuffer, ULONG ulLen, LPSTR pHelpFile, ULONG *pulHelpCtx)
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
		return (m_hResult = E_FAIL);
	}

// HelpFileInfo übergeben
	if (pHelpFile) pHelpFile[0] = '\0';
	if (pulHelpCtx) *pulHelpCtx = 0L;
	
return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// IPropertyAction methods 
STDMETHODIMP CVerschnittPropAct::AddConfigPages (
				LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam, 
			    LPCSTR pcDesc, UINT *puiCnt)
{
	try 
	{
		if (NULL == m_hDex)
			return E_FAIL;

	//	zugehörigen ConfigDialog (PropertyPage(s)) anlegen
		DELETE_OBJ(m_pCfgDlg);	// evtl. vorherigen freigeben

		m_pCfgDlg = CVerschnittPage::CreateInstance (this);
		if (NULL == m_pCfgDlg) 
			_com_issue_error (E_OUTOFMEMORY);
		if (m_bHasInitData)
		{
			m_pCfgDlg -> SelectFuzzy (m_dFuzzy);
			m_pCfgDlg -> SelectDangleLen (m_dDangleLen);
			m_pCfgDlg -> SelectDeleteOldLines (m_bDeleteOldLines);
			m_pCfgDlg -> SelectMarkOldLines (m_bMarkObjects);
		}
		
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
		return (m_hResult = _COM_ERROR (hr_result));
	}
	
	return NOERROR;
}

STDMETHODIMP CVerschnittPropAct::PreConfigPages (IDataObject *, DWORD dwFlags)
{
	if (NULL == m_hDex)
		return E_FAIL;

	m_pCfgDlg -> SetFlags (dwFlags);
	return NOERROR;
}

STDMETHODIMP CVerschnittPropAct::DoAction (IDataObject *pIDataObj, DWORD)
{
	if (NULL == pIDataObj)
		return E_POINTER;
		
	if (NULL == m_hDex)
		return E_FAIL;

	try
	{
		WEnumObjectsByNumber IEnumObj;
		HRESULT hr = GetEnumLONGData (pIDataObj, IEnumObj.ppi());

		if (FAILED(hr)) 
			_com_issue_error (hr);

		ASSERT (NULL != m_pCfgDlg);

	//	Undo beginnen
		CString strText;
		VERIFY (strText.LoadString(IDS_UNDO_TEXT_VER));
		DEX_BeginUndoLevel ((const char*)strText);

		m_hResult = m_pCfgDlg -> SetEnumLONG (IEnumObj);

	//	Undo auswerten
		if (SUCCEEDED (m_hResult))
			DEX_EndUndoLevel ();
		else
			DEX_CancelUndoLevel (TRUE);
	}
	catch (_com_error& hrs)
	{
		m_hResult = _COM_ERROR (hrs);
	}

	return m_hResult;
}

STDMETHODIMP CVerschnittPropAct::EndAction (DWORD, IDataObject **ppDataObj)
{
	HRESULT hrr = S_OK;

	try
	{
		if (NULL == ppDataObj)
			return E_POINTER;
		
		if (NULL == m_hDex)
			return E_FAIL;

		WEnumObjectsByNumber WEnumObj;
		hrr = m_pCfgDlg -> GetEnumLONG (WEnumObj);
	
		if (FAILED(hrr)) 
			return hrr;

	//	DataObject generieren
		*ppDataObj = NULL;
		WDataObject IDO;
	
		HRESULT hr = CoCreateInstance (CLSID_DataTransferObject, NULL, CLSCTX_INPROC_SERVER,
							   IID_IDataObject, IDO.ppv()); 
		if (FAILED(hr)) 
			_com_issue_error (hr);

		hr = SetEnumLONGData (WEnumObj, IDO);
		if (FAILED(hr)) 
			_com_issue_error (hr);
	
		*ppDataObj = IDO.detach();
	} 
	catch (_com_error& hr_result) 
	{
		DELETE_OBJ (m_pCfgDlg);	// DialogPage freigeben
		return (m_hResult = _COM_ERROR (hr_result));
	}

//	Parameter speichern
	if (S_OK == hrr)
	{
		m_dFuzzy = m_pCfgDlg -> GetFuzzy ();
		m_dDangleLen = m_pCfgDlg -> GetDangleLen ();
		m_bDeleteOldLines = m_pCfgDlg -> GetDeleteOldLines ();
		m_bMarkObjects = m_pCfgDlg -> GetMarkOldLines ();
	
		DELETE_OBJ (m_pCfgDlg);		// DialogPage freigeben
	}

	return hrr;
}

///////////////////////////////////////////////////////////////
// IPersist methods
STDMETHODIMP CVerschnittPropAct::GetClassID (LPCLSID lpClassID)
{
	if (NULL == lpClassID)
		return E_POINTER;

	*lpClassID = CLSID_VerschnittPropAct;
	return NOERROR;
}

//	IPersistStreamInit method
STDMETHODIMP CVerschnittPropAct::InitNew (void)
{
	if (NULL == m_hDex)
		return E_FAIL;

	if (m_bIsInitialized)
		return E_UNEXPECTED;		// already initialized with Load

	m_bIsInitialized = TRUE;
	m_bIsDirty = FALSE;
	m_bHasInitData = FALSE;

	m_dDangleLen = m_dFuzzy = 0.0;
	m_bDeleteOldLines = FALSE;
	m_bMarkObjects = FALSE;
	
	return NOERROR;
}

// IPersistStream methods
STDMETHODIMP CVerschnittPropAct::IsDirty (void)
{
	return m_bIsDirty ? S_OK : S_FALSE;
}

STDMETHODIMP CVerschnittPropAct::GetSizeMax (ULARGE_INTEGER *pcbSize)
{
	if (NULL == pcbSize) return E_POINTER;

ULARGE_INTEGER cbSize;
HRESULT hr = CPropertyAction::GetSizeMax (&cbSize);

	if (FAILED(hr)) return hr;

ULARGE_INTEGER liOwnSize;

	liOwnSize.QuadPart = uiMaxStreamSize;
	liOwnSize.QuadPart += cbSize.QuadPart;
	*pcbSize = liOwnSize;
	
	return S_OK;
}

STDMETHODIMP CVerschnittPropAct::Load (LPSTREAM pStm)
{
	if (NULL == m_hDex)
		return E_FAIL;

	if (m_bIsInitialized)
		return E_UNEXPECTED;		// already initialized with InitNew

HRESULT hr = CPropertyAction::Load (pStm);

	if (FAILED(hr)) 
		return hr;

//	dann selektierte Info der letzten Auswahl
	double dFuzzy = 0.0;
	double dDangleLen = 0.0;
	LONG lDeleteOldLines = 0L;
	LONG lMarkOldLines = 0L;
	
	hr = pStm -> Read (&dFuzzy, sizeof(double), NULL);
	if (FAILED(hr)) return hr;

	hr = pStm -> Read (&dDangleLen, sizeof(double), NULL);
	if (FAILED(hr)) return hr;

	hr = pStm -> Read (&lDeleteOldLines, sizeof(LONG), NULL);
	if (FAILED(hr)) return hr;

	hr = pStm -> Read (&lMarkOldLines, sizeof(LONG), NULL);
	if (FAILED(hr)) return hr;

	if (NULL == m_pCfgDlg) 
	{
	//	Dialog ist noch nicht initialisiert
		m_dFuzzy = dFuzzy;
		m_dDangleLen = dDangleLen;
		m_bDeleteOldLines = lDeleteOldLines ? TRUE : FALSE;
		m_bMarkObjects = lMarkOldLines ? TRUE : FALSE;
		m_bHasInitData = TRUE;
	} 
	else 
	{
		m_pCfgDlg -> SelectFuzzy (dFuzzy);
		m_pCfgDlg -> SelectDangleLen (dDangleLen);
		m_pCfgDlg -> SelectDeleteOldLines (lDeleteOldLines ? TRUE : FALSE);
		m_pCfgDlg -> SelectMarkOldLines (lMarkOldLines ? TRUE : FALSE);
	}
	
	m_bIsInitialized = TRUE;
	m_bIsDirty = FALSE;

return NOERROR;
}

STDMETHODIMP CVerschnittPropAct::Save (LPSTREAM pStm, BOOL fClearDirty)
{
//	zuerst Bezeichner wegschreiben
	HRESULT hr = CPropertyAction::Save (pStm, fClearDirty);

	if (FAILED(hr)) return hr;

//	dann selektierte Info der letzten Auswahl: Toleranz
	hr = pStm -> Write (&m_dFuzzy, sizeof(double), NULL);
	if (FAILED(hr)) return hr;

//	DangleLänge
	hr = pStm -> Write (&m_dDangleLen, sizeof(double), NULL);
	if (FAILED(hr)) return hr;

//	alten Linien löschen
	LONG lTemp = m_bDeleteOldLines ? 1 : 0;
	hr = pStm -> Write (&lTemp, sizeof(LONG), NULL);
	if (FAILED(hr)) return hr;

//	Objekt markieren
	lTemp = m_bMarkObjects ? 1 : 0;
	hr = pStm -> Write (&lTemp, sizeof(LONG), NULL);
	if (FAILED(hr)) return hr;

	if (fClearDirty) 
		m_bIsDirty = FALSE;
	return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// IPropertyInfo specific functions 
STDMETHODIMP CVerschnittPropAct::SetPropInfo (LPCSTR pcBuffer, DWORD dwFlags) 
{
	if (NULL == m_hDex)
		return E_FAIL;

	if (NULL == pcBuffer) return E_POINTER;

	m_strDesc = pcBuffer;
	return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// Sonstiges
void CVerschnittPropAct::SetDirty (BOOL fDirty) 
{ 
	m_bIsDirty = fDirty; 
}

