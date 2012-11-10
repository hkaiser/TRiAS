// File: WHEREPRP.CPP

#include "pheader.h"		//	vorübers. Header
#include "odbcext.hr"		//	Resource-Konstanten

//	TRIAS-Header
// #include <ospace/com/iterenum.h>
//#include "Ixtensn.hxx"		//	IClassProperty

//	STL-Header
#include <ospace/com/smartif.h>
// #include <ospace/std/list>	// list

//	allgem. Header
#include <float.h>			// DBL_MIN, DBL_MAX
//#include <int64.h>			// LARGE

// GUID-Header
#include <xtsnguid.h>
#include <initguid.h>
//#include <triashelper.h>
#include "whereprp.h"		// CLSID_WhereKlauselPropAct
#define _TriasTLB_H_           
#include <dirisole.h>		// CLSID_DataTransferObject

#include <hpp/propactb.hpp>		// Basisklasse
#include <hpp/datahelp.hpp>		// Get/SetEnumLongData

#include <hpp/Getodbci.hpp>		// CODBCInfos
#include <hpp/tooltipb.h>		// CToolTipButton
#include <hpp/helptext.hpp>		// CHelpText
#include <Tabdlgs.hpp>		// CTabbedDialogs

#include "UserDlg.h"		// CUserDlg
#include "FileDlg.h"		// CFileDsnPage

#include "wherepge.h"		// DialogPage

#include "whereprp.hpp"		// zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//	Konstanten
#define ParamCount 4				//	4 Parameter für Eingabe

//	externe Variablen
class COdbcExtension;
extern COdbcExtension *g_pCOdbcExtension;

///////////////////////////////////////////////////////////////////////////////
// benötigte InterfaceWrapper
DefineSmartInterface(DataObject);
//DefineEnumIIDWrapper(LONG);		// CIID_LONGEnum
DefineSmartInterface(EnumObjectsByNumber);	
DefineSmartInterface(ClassProperty);

CWhereKlauselPropAct :: CWhereKlauselPropAct (void)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());

	m_pCfgDlg = NULL;
	m_bIsDirty = FALSE;
	m_bIsInitialized = FALSE;
	m_bHasInitData = FALSE;
	VERIFY (m_strDesc.LoadString(IDS_HELPDESC_WHERE));

	//	Nutzereingaben
	m_tpDataSource = NoDataSource;
}

CWhereKlauselPropAct :: ~CWhereKlauselPropAct (void)
{
//	Dialog löschen
	DELETE_OBJ (m_pCfgDlg);
}

///////////////////////////////////////////////////////////////////////////////
// IClassProperty specific functions 
STDMETHODIMP CWhereKlauselPropAct::GetPropInfo (LPSTR pBuffer, WORD wLen, DWORD *pdwFlags)
{
	try {
		if (NULL == g_pCOdbcExtension)
			return E_UNEXPECTED;

		if (NULL != pBuffer && wLen > 0) {
		// Namen der Property kopieren
		// ULONG ulLen = tmin (wLen-1, (WORD)m_strDesc.GetLength());
			ULONG ulLen= min (wLen-1, m_strDesc.GetLength());

			strncpy (pBuffer, m_strDesc, ulLen);
			pBuffer[ulLen] = '\0';
		}
	} catch (...) {
		return (E_FAIL);
	}

//	wenn gewünscht, Flags übergeben
	if (pdwFlags) {
		*pdwFlags = PROPCAPS_ACTION_SINK_MULTI|PROPCAPS_ACTION_SOURCE;
	}

return NOERROR;
}

STDMETHODIMP CWhereKlauselPropAct::HelpInfo (LPSTR pBuffer, ULONG ulLen, LPSTR pHelpFile, ULONG *pulHelpCtx)
{
	try {
		if (NULL == g_pCOdbcExtension)
			return E_UNEXPECTED;

		if (NULL != pBuffer && ulLen > 0) {
		// Beschreibung übergeben
		WORD wLen = min ((WORD) ulLen-1, m_strDesc.GetLength());

			strncpy (pBuffer, m_strDesc, wLen);
			pBuffer[ulLen] = '\0';
		}
	} catch (...) {
		return (E_FAIL);
	}

// HelpFileInfo übergeben
	if (pHelpFile) pHelpFile[0] = '\0';
	if (pulHelpCtx) *pulHelpCtx = 0L;
	
return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// IPropertyAction methods 
STDMETHODIMP CWhereKlauselPropAct::AddConfigPages (
				LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam, 
			    LPCSTR pcDesc, UINT *puiCnt)
{
	try 
	{
		if (NULL == g_pCOdbcExtension)
			return S_FALSE;
	//		return E_UNEXPECTED;

	//	zugehörigen ConfigDialog (PropertyPage(s)) anlegen
		DELETE_OBJ(m_pCfgDlg);	// evtl. vorherigen freigeben

		UINT uiResID = IDD_INPUT_WHERE_PAGE1;
		if (m_objSite)
		{
			try
			{
				WClassProperty wclass (m_objSite);
				DWORD dwFlags = 0;
				if (SUCCEEDED(wclass -> GetPropInfo (NULL, 0, &dwFlags)))
				{
					if (!(dwFlags & PROPCAPS_CONTAINER_IS_CHOICE))
						uiResID = IDD_INPUT_WHERE_PAGE2;
				}
			} 
			catch (HRESULT)
			{
			//	nur auffangen	
			}
		}
		m_pCfgDlg = CWherePage::CreateInstance (uiResID, this);

		if (NULL == m_pCfgDlg) 
			throw E_OUTOFMEMORY;
		
		if (m_bHasInitData)
		{
			m_pCfgDlg -> m_strDataSource = m_strDataSource;
			m_pCfgDlg -> m_tpDataSource = m_tpDataSource;
			m_pCfgDlg -> m_strFilter = m_strWhereKlausel;
			m_pCfgDlg -> m_strTable = m_strTable;
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
			throw E_OUTOFMEMORY;
	
		if (!(*lpfnAddPage) (hPSP, lParam))  
			return E_FAIL;

		if (puiCnt) 
			*puiCnt = 1;		// eine Seite ist dazu gekommen
	} 
	catch (HRESULT hr_result) 
	{
		DELETE_OBJ (m_pCfgDlg);
		if (puiCnt) 
			*puiCnt = 0;
		return (hr_result);
	}
	
	return NOERROR;
}

STDMETHODIMP CWhereKlauselPropAct::PreConfigPages (IDataObject *, DWORD dwFlags)
{
	if (NULL == g_pCOdbcExtension)
		return E_UNEXPECTED;

	m_pCfgDlg -> SetFlags (dwFlags);
	return NOERROR;
}

STDMETHODIMP CWhereKlauselPropAct::DoAction (IDataObject *pIDataObj, DWORD)
{
	if (NULL == pIDataObj)
		return E_POINTER;
		
	if (NULL == g_pCOdbcExtension)
		return E_UNEXPECTED;

	HRESULT hRes = NOERROR;
	try
	{
		WEnumObjectsByNumber IEnumObj;
		HRESULT hr = GetEnumLONGData (pIDataObj, IEnumObj.ppi());

		if (FAILED(hr)) 
			throw hr;

		ASSERT (NULL != m_pCfgDlg);
		hRes = m_pCfgDlg -> SetEnumLONG (IEnumObj);
	}
	catch (HRESULT hrs)
	{
		hRes = hrs;
	}

	return hRes;
}

STDMETHODIMP CWhereKlauselPropAct::EndAction (DWORD, IDataObject **ppDataObj)
{
	if (NULL == ppDataObj)
		return E_POINTER;
		
	if (NULL == g_pCOdbcExtension)
		return E_UNEXPECTED;

	WEnumObjectsByNumber IEnumObj;
	HRESULT hr = m_pCfgDlg -> GetEnumLONG (IEnumObj.ppi());
	
	if (FAILED(hr)) 
		return hr;

//	DataObject generieren
	*ppDataObj = NULL;

	try {
		WDataObject IDO;
	
		hr = CoCreateInstance (CLSID_DataTransferObject, NULL, CLSCTX_INPROC_SERVER,
							   IID_IDataObject, IDO.ppv()); 
		if (FAILED(hr)) throw hr;

		HRESULT hr2 = SetEnumLONGData (IEnumObj, IDO);
		
		if (FAILED(hr2)) throw hr2;
	
		*ppDataObj = IDO.detach();

	} catch (HRESULT hr_result) {
		DELETE_OBJ (m_pCfgDlg);	// DialogPage freigeben
		return (hr_result);
	}

//	Parameter speichern
	m_strDataSource =  m_pCfgDlg -> m_strDataSource;
	m_strWhereKlausel = m_pCfgDlg -> m_strFilter;
	m_tpDataSource = m_pCfgDlg -> m_tpDataSource;
	m_strTable = m_pCfgDlg -> m_strTable;
	
//	letzter Enumerator/PropAction erzeugt lediglich eine Objektmenge
	DELETE_OBJ (m_pCfgDlg);		// DialogPage freigeben

return hr;
}

///////////////////////////////////////////////////////////////
// IPersist methods
STDMETHODIMP CWhereKlauselPropAct::GetClassID (LPCLSID lpClassID)
{
	if (NULL == lpClassID)
		return E_POINTER;

	*lpClassID = CLSID_WhereKlauselPropAct;
	return NOERROR;
}

//	IPersistStreamInit method
STDMETHODIMP CWhereKlauselPropAct::InitNew (void)
{
	if (NULL == g_pCOdbcExtension)
		return E_ABORT;				// ERweiterung ist nicht geladen

	if (m_bIsInitialized)
		return E_UNEXPECTED;		// already initialized with Load

	m_bIsInitialized = TRUE;
	m_bIsDirty = FALSE;
	m_bHasInitData = FALSE;

	m_tpDataSource = NoDataSource;
	m_strDataSource.Empty ();
	m_strWhereKlausel.Empty ();
	m_strTable.Empty ();

	return NOERROR;
}

// IPersistStream methods
STDMETHODIMP CWhereKlauselPropAct::IsDirty (void)
{
	return m_bIsDirty ? S_OK : S_FALSE;
}

STDMETHODIMP CWhereKlauselPropAct::GetSizeMax (ULARGE_INTEGER *pcbSize)
{
	if (NULL == pcbSize) return E_POINTER;

ULARGE_INTEGER cbSize;
HRESULT hr = CPropertyAction::GetSizeMax (&cbSize);

	if (FAILED(hr)) return hr;

	UINT uiMaxStreamSize = m_strWhereKlausel.GetLength () + m_strDataSource.GetLength () + 
						   m_strTable.GetLength () + (ParamCount * sizeof (LONG));
						
ULARGE_INTEGER liOwnSize;

	liOwnSize.QuadPart = uiMaxStreamSize;
	liOwnSize.QuadPart += cbSize.QuadPart;
	*pcbSize = liOwnSize;
	return S_OK;
}

STDMETHODIMP CWhereKlauselPropAct::Load (LPSTREAM pStm)
{
	if (NULL == g_pCOdbcExtension)
		return E_UNEXPECTED;

	if (m_bIsInitialized)
		return E_UNEXPECTED;		// already initialized with InitNew

HRESULT hr = CPropertyAction::Load (pStm);

	if (FAILED(hr)) 
		return hr;

//	dann selektierte Info der letzten Auswahl
	CString strDataSource, strFilter, strTable;
	char *pDataSource = NULL;
	char *pFilter = NULL;
	char *pTable = NULL;
	LONG lDataSource = 0;
	LONG lFilter = 0;
	LONG lTable = 0;
	LONG lType = 0;

//	zuerst Typ lesen
	hr = pStm -> Read (&lType, sizeof(LONG), NULL);
	if (FAILED(hr)) return hr;

//	DataSourcegröße lesen	
	hr = pStm -> Read (&lDataSource, sizeof(LONG), NULL);
	if (FAILED(hr)) return hr;
	if (lDataSource > 0)
	{
	//	DataSource lesen
		pDataSource = strDataSource.GetBuffer (lDataSource+1);
		memset (pDataSource, 0, lDataSource+1);
		hr = pStm -> Read (pDataSource, lDataSource, NULL);
		pDataSource [lDataSource] = '\0';
		if (FAILED(hr)) return hr;
	}

//	Filtergröße lesen
	hr = pStm -> Read (&lFilter, sizeof(LONG), NULL);
	if (FAILED(hr)) return hr;
	if (lFilter > 0)
	{
	//	Filter selbst lesen
		pFilter = strFilter.GetBuffer (lFilter + 1);
		memset (pFilter, 0, lFilter + 1);
		hr = pStm -> Read (pFilter, lFilter, NULL);
		pFilter [lFilter] = '\0';
		if (FAILED(hr)) return hr;
	}

//	Tabelle lesen
	hr = pStm -> Read (&lTable, sizeof(LONG), NULL);
	if (FAILED(hr)) return hr;
	if (lTable > 0)
	{
	//	Filter selbst lesen
		pTable = strTable.GetBuffer (lTable + 1);
		memset (pTable, 0, lTable + 1);
		hr = pStm -> Read (pTable, lTable, NULL);
		pTable [lTable] = '\0';
		if (FAILED(hr)) return hr;
	}

	if (NULL == m_pCfgDlg) {
	//	Dialog ist noch nicht initialisiert
		m_tpDataSource = (DataSourceType) lType;
		m_strDataSource = pDataSource ? pDataSource : "";
		m_strWhereKlausel = pFilter ? pFilter : "";
		m_strTable = pTable ? pTable : "";
		m_bHasInitData = TRUE;
	} else {
		m_pCfgDlg -> m_tpDataSource = (DataSourceType) lType;
		m_pCfgDlg -> m_strDataSource = pDataSource ? pDataSource : "";
		m_pCfgDlg -> m_strFilter = pFilter ? pFilter : "";
		m_pCfgDlg -> m_strTable = pTable ? pTable : "";
	}

	m_bIsInitialized = TRUE;
	m_bIsDirty = FALSE;

return NOERROR;
}

STDMETHODIMP CWhereKlauselPropAct::Save (LPSTREAM pStm, BOOL fClearDirty)
{
//	zuerst Bezeichner wegschreiben
	HRESULT hr = CPropertyAction::Save (pStm, fClearDirty);

	if (FAILED(hr)) return hr;

//	dann selektierte Info der letzten Auswahl: DataSourcetyp
	long lTemp = m_tpDataSource;
	hr = pStm -> Write (&lTemp, sizeof(LONG), NULL);
	if (FAILED(hr)) return hr;

//	DataSource
//	zuerst Länge
	lTemp = m_strDataSource.GetLength ();
	hr = pStm -> Write (&lTemp, sizeof(LONG), NULL);
	if (FAILED(hr)) return hr;

//	Namen der Datenquelle selbst
	if (lTemp > 0)
	{
		hr = pStm -> Write ((const char *)m_strDataSource, lTemp, NULL);
			if (FAILED(hr)) return hr;
	}

//	Filter
//	Länge
	lTemp = m_strWhereKlausel.GetLength ();
	hr = pStm -> Write (&lTemp, sizeof(LONG), NULL);
	if (FAILED(hr)) return hr;

//	Filter selbst
	if (lTemp > 0)
	{
		hr = pStm -> Write ((const char *)m_strWhereKlausel, lTemp, NULL);
			if (FAILED(hr)) return hr;
	}

//	Tabelle
//	Länge
	lTemp = m_strTable.GetLength ();
	hr = pStm -> Write (&lTemp, sizeof(LONG), NULL);
	if (FAILED(hr)) return hr;

//	Tabelle selbst
	if (lTemp > 0)
	{
		hr = pStm -> Write ((const char *)m_strTable, lTemp, NULL);
			if (FAILED(hr)) return hr;
	}

	if (fClearDirty) m_bIsDirty = FALSE;
	return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// IPropertyInfo specific functions 
STDMETHODIMP CWhereKlauselPropAct::SetPropInfo (LPCSTR pcBuffer, DWORD dwFlags) 
{
	if (NULL == g_pCOdbcExtension)
		return E_UNEXPECTED;

	if (NULL == pcBuffer) return E_POINTER;

	m_strDesc = pcBuffer;
	return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// Sonstiges
void CWhereKlauselPropAct::SetDirty (BOOL fDirty) 
{ 
	m_bIsDirty = fDirty; 
}

STDMETHODIMP CWhereKlauselPropAct::SetSite(/*[in]*/IUnknown * pUnkSite)
{
	m_objSite = pUnkSite;
	return S_OK;
}

STDMETHODIMP CWhereKlauselPropAct::GetSite(/*[in]*/ REFIID riid,
					  /*[out, iid_is(riid)]*/void ** ppvSite)
{
	if (!m_objSite)
		return E_UNEXPECTED;

	return m_objSite -> QueryInterface (riid, ppvSite);
}

	