// PropertyAction für Datenimport
// File: ImportProp.cpp

#include "trias03p.hxx"
#include "trias03.h"

#include <funcs03.h>

#include <xtsnguid.h>
#include <eonrguid.h>
#include <propguid.h>
#include <statguid.h>
#include <dirisole.h>

#include <pdataobj.hxx>

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "Strings.h"
#include "SelectCoordSysActionDlg.h"
#include "ImportProp.h"

/////////////////////////////////////////////////////////////////////////////
// externes
extern char g_pDLLName[_MAX_PATH];

/////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(DataObject);
DefineEnumIIDWrapper(LONG);		// CIID_LONGEnum
DefineSmartEnumerator(LONG);	// WEnumLONG

// GUID ///////////////////////////////////////////////////////////////////////
// E2FC1963-F46C-11D1-862F-00600875138A	
// DEFINE_GUID(CLSID_ImportDataPropAct, 0xE2FC1963L, 0xF46C, 0x11D1, 0x86, 0x2F, 0x00, 0x60, 0x08, 0x75, 0x13, 0x8A);

#pragma warning (disable: 4355)

CImportPropAct::CImportPropAct (void)
{
	m_pCfgDlg = NULL;
	m_pSelectCoordSysDlg = NULL;
	m_fIsDirty = false;
	m_fIsInitialized = false;
	m_fHasInitData = false;

	COM_TRY {
	ResourceFile RF (g_pDLLName);
	ResString resPropInfo (ResID (IDS_PROPINFO_IMPORTDATA, &RF), 64);

		m_strDesc = resPropInfo;

	} COM_CATCH_IGNORE;
}

#pragma warning (default: 4355)

CImportPropAct::~CImportPropAct (void)
{
	DELETE_OBJ(m_pCfgDlg);
	DELETE_OBJ(m_pSelectCoordSysDlg);
}

// *** IClassProperty specific functions *** ----------------------------------
STDMETHODIMP CImportPropAct::GetPropInfo (LPSTR pBuffer, WORD wLen, DWORD *pdwFlags)
{
	COM_TRY {
		if (NULL != pBuffer && wLen > 0) {
		// Namen der Property kopieren
		ULONG ulLen = min ((size_t)(wLen-1), m_strDesc.length());

			strncpy (pBuffer, m_strDesc.c_str(), ulLen);
			pBuffer[ulLen] = '\0';
		}
	
	} COM_CATCH;

// wenn gewünscht, Flags übergeben
	if (pdwFlags) 
		*pdwFlags = PROPCAPS_ACTION_SOURCE;
	return S_OK;
}

STDMETHODIMP CImportPropAct::HelpInfo (LPSTR pBuffer, ULONG wLen, LPSTR pHelpFile, ULONG *pulHelpCtx)
{
	COM_TRY {
		if (NULL != pBuffer && wLen > 0) {
		// Beschreibung übergeben
		ResourceFile RF (g_pDLLName);
		ResString resHelp (ResID (IDS_HELPDESC_IMPORTDATA, &RF), 128);
		ULONG ulLen = min (size_t(wLen-1), strlen(resHelp));

			strncpy (pBuffer, resHelp, ulLen);
			pBuffer[ulLen] = '\0';
		}

	} COM_CATCH;

// HelpFileInfo übergeben
	if (pHelpFile) pHelpFile[0] = '\0';
	if (pulHelpCtx) *pulHelpCtx = 0L;
	return S_OK;
}

// *** IPropertyAction methods ------------------------------------------------
STDMETHODIMP CImportPropAct::AddConfigPages (
	LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam, LPCSTR pcDesc, UINT *puiCnt)
{
char cbCaption[_MAX_PATH];

	if (puiCnt) *puiCnt = 0;	/// für alle Fälle

	COM_TRY {
		if (NULL != pcDesc)		// Caption ist gegeben
			strcpy (cbCaption, pcDesc);
		else	// von zugehöriger ClassProperty unseren Namen besorgen
			GetPropInfo (cbCaption, sizeof(cbCaption), NULL);

	// zugehörigen ConfigDialog (PropertyPage(s)) anlegen
	ResourceFile RF (g_pDLLName);

		DELETE_OBJ(m_pCfgDlg);	// evtl. vorherigen freigeben
		m_pCfgDlg = CImportDataDlg::CreateInstance (
						IDD_IMPORT_WIZ, cbCaption, RF);
		if (NULL == m_pCfgDlg) _com_issue_error(E_OUTOFMEMORY);


		if (!IsNoShow()) {
		//
		// Achtung MFC-Falle !
		// Normalerweise müßte an dieser Stelle lpfnAddPage mit unserem 
		// HPROPERTYPAGE gerufen werden, wir aber wissen (darf man das ?), daß
		// sich hinter dem eigentlich durchzureichendem lParam der Pointer auf
		// unsern PropertySheet verbirgt.
		//
			if (UINT_MAX == ((CPropertySheet *)lParam) -> AddPage (m_pCfgDlg))
				_com_issue_error(E_UNEXPECTED);
			if (puiCnt) *puiCnt = 1;

		} else if (NULL != puiCnt) 
			*puiCnt = 0;	// Page soll nicht angezeigt werden

		DELETE_OBJ(m_pSelectCoordSysDlg);
		m_pSelectCoordSysDlg = CSelectCoordSysActionDlg::CreateInstance (
				IDD_SELECTCOORDSYSACTION_OPTIONS, cbCaption, RF);
		if (NULL == m_pSelectCoordSysDlg) _com_issue_error(E_OUTOFMEMORY);

		if (!IsNoShow()) {
		//
		// Achtung MFC-Falle !
		// Normalerweise müßte an dieser Stelle lpfnAddPage mit unserem 
		// HPROPERTYPAGE gerufen werden, wir aber wissen (darf man das ?), daß
		// sich hinter dem eigentlich durchzureichendem lParam der Pointer auf
		// unsern PropertySheet verbirgt.
		//
			if (UINT_MAX == ((CPropertySheet *)lParam) -> AddPage (m_pSelectCoordSysDlg))
				_com_issue_error(E_UNEXPECTED);

			if (NULL != puiCnt)
				++(*puiCnt);
		}

		if (m_fHasInitData) 
		{
			THROW_FAILED_HRESULT(m_pCfgDlg -> SetImportInfo (&m_caImportInfo));
		}
		m_pCfgDlg->SetCoordSysDlg(m_pSelectCoordSysDlg);

	} COM_CATCH_OP (
		(	delete m_pCfgDlg, m_pCfgDlg = NULL, 
			delete m_pSelectCoordSysDlg, m_pSelectCoordSysDlg = NULL
		)
	);
	return S_OK;
}

STDMETHODIMP CImportPropAct::PreConfigPages (IDataObject *, DWORD dwFlags)
{
	if (NULL != m_pCfgDlg) 
		m_pCfgDlg -> SetFlags (dwFlags & ~ADDPAGES_LASTPAGE);
	if (NULL != m_pSelectCoordSysDlg) 
		m_pSelectCoordSysDlg -> SetFlags (dwFlags & ~ADDPAGES_FIRSTPAGE);
	return S_OK;
}

STDMETHODIMP CImportPropAct::EndAction (DWORD, IDataObject **ppDataOut)
{
	*ppDataOut = NULL;
	if (NULL == m_pCfgDlg || NULL == m_pSelectCoordSysDlg)
		return E_UNEXPECTED;

WEnumLONG IEnumObj;
os_string strObjProp;
HRESULT hr = m_pCfgDlg -> GetNextEnumLONG (IEnumObj.ppi());

	if (FAILED(hr)) return hr;

	DEX_PostRebuildSight();
	if (!IEnumObj) return S_OK;

	COM_TRY {
	// IDataObject abfragen
	WDataObject IDO (CLSID_DataTransferObject);

	// Daten und Formate im DataObjekt speichern
	// 1. Liste aller Objekte
		THROW_FAILED_HRESULT(SetEnumLONGData (IEnumObj, IDO));

	// Resultat setzen
		*ppDataOut = IDO.detach();

	} COM_CATCH_OP(
		(
			delete m_pCfgDlg, m_pCfgDlg = NULL,
			delete m_pSelectCoordSysDlg, m_pSelectCoordSysDlg = NULL
		)
	);	// DialogPage freigeben

// Dialog freigeben
	DELETE_OBJ(m_pCfgDlg);
	DELETE_OBJ(m_pSelectCoordSysDlg);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// IPersist methods
STDMETHODIMP CImportPropAct::GetClassID (LPCLSID lpClassID)
{
	if (NULL == lpClassID)
		return E_POINTER;

	*lpClassID = CLSID_ImportDataPropAct;
	return S_OK;
}

// IPersistStreamInit methods
STDMETHODIMP CImportPropAct::IsDirty (void)
{
	return m_fIsDirty ? S_OK : S_FALSE;
}

STDMETHODIMP CImportPropAct::Load (LPSTREAM pStm)
{
	if (m_fIsInitialized)
		return E_UNEXPECTED;		// already initialized with InitNew

// zuerst Bezeichner einlesen
HRESULT hr = CPropertyAction::Load (pStm);

	if (FAILED(hr)) return hr;

// dann selektierte Info der letzten Auswahl
char cbBuffer[_MAX_PATH];
LONG lLen = 0;

	RETURN_FAILED_HRESULT(pStm -> Read (&lLen, sizeof(LONG), NULL));
	RETURN_FAILED_HRESULT(pStm -> Read (cbBuffer, lLen, NULL));
	m_caImportInfo.m_strProgID = cbBuffer;

// Flags einlesen
	RETURN_FAILED_HRESULT(pStm -> Read (&m_caImportInfo.m_dwFlags, sizeof(DWORD), NULL));
	RETURN_FAILED_HRESULT(pStm -> Read (&m_caImportInfo.m_fShowErrors, sizeof(BOOL), NULL));

// Anzahl der DateiNamen
LONG lCnt = 0;

	RETURN_FAILED_HRESULT(pStm -> Read (&lCnt, sizeof(LONG), NULL));
	for (long i = 0; i < lCnt; ++i) {
		RETURN_FAILED_HRESULT(pStm -> Read (&lLen, sizeof(LONG), NULL));
		RETURN_FAILED_HRESULT(pStm -> Read (cbBuffer, lLen, NULL));
		m_caImportInfo.m_listNames.push_back (cbBuffer);
	}

	if (NULL == m_pCfgDlg) 
	// Dialog ist noch nicht initialisiert
		m_fHasInitData = true;
	else
		m_pCfgDlg -> SetImportInfo (&m_caImportInfo);
	
	m_fIsInitialized = true;
	m_fIsDirty = false;
	return S_OK;
}

STDMETHODIMP CImportPropAct::Save (LPSTREAM pStm, BOOL fClearDirty)
{
// zuerst Bezeichner wegschreiben
HRESULT hr = CPropertyAction::Save (pStm, fClearDirty);

	if (FAILED(hr)) return hr;

// dann selektierte Info der letzten Auswahl
LONG lLen = m_caImportInfo.m_strProgID.size()+1;

	RETURN_FAILED_HRESULT(pStm -> Write (&lLen, sizeof(LONG), NULL));
	RETURN_FAILED_HRESULT(pStm -> Write (m_caImportInfo.m_strProgID.c_str(), lLen, NULL));

// Flags wegschreiben
	RETURN_FAILED_HRESULT(pStm -> Write (&m_caImportInfo.m_dwFlags, sizeof(DWORD), NULL));
	RETURN_FAILED_HRESULT(pStm -> Write (&m_caImportInfo.m_fShowErrors, sizeof(BOOL), NULL));

// Anzahl der DateiNamen
LONG lCnt = m_caImportInfo.m_listNames.size();

	RETURN_FAILED_HRESULT(pStm -> Write (&lCnt, sizeof(LONG), NULL));
	for (list<os_string>::iterator it = m_caImportInfo.m_listNames.begin(); 
		 it != m_caImportInfo.m_listNames.end(); /**/) 
	{
		lLen = (*it).size()+1;
		RETURN_FAILED_HRESULT(pStm -> Write (&lLen, sizeof(LONG), NULL));
		RETURN_FAILED_HRESULT(pStm -> Write ((*it).c_str(), lLen, NULL));
	}

	if (fClearDirty) m_fIsDirty = false;
	return S_OK;
}

STDMETHODIMP CImportPropAct::GetSizeMax (ULARGE_INTEGER *pcbSize)
{
	if (NULL == pcbSize) return E_POINTER;

ULARGE_INTEGER cbSize;
HRESULT hr = CPropertyAction::GetSizeMax (&cbSize);

	if (FAILED(hr)) return hr;

ULARGE_INTEGER liOwnSize;

	liOwnSize.QuadPart = 3*sizeof(LONG) + sizeof(DWORD) + m_caImportInfo.m_strProgID.size()+1;
	for (list<os_string>::iterator it = m_caImportInfo.m_listNames.begin(); 
		 it != m_caImportInfo.m_listNames.end(); /**/) 
	{
		liOwnSize.QuadPart = liOwnSize.QuadPart + sizeof(long) + (*it).size()+1;
	}

	liOwnSize.QuadPart = liOwnSize.QuadPart + cbSize.QuadPart;
	*pcbSize = liOwnSize;
	return S_OK;
}

STDMETHODIMP CImportPropAct::InitNew (void)
{
	if (m_fIsInitialized)
		return E_UNEXPECTED;		// already initialized with Load

	m_caImportInfo.m_listNames.clear();
	m_caImportInfo.m_strProgID.empty();
	m_caImportInfo.m_dwFlags = 0L;
	m_caImportInfo.m_fShowErrors = TRUE;	// default: Fehler anzeigen

	m_fIsInitialized = true;
	m_fIsDirty = false;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// IPropertyInfo specific functions 
STDMETHODIMP CImportPropAct::SetPropInfo (LPCSTR pcBuffer, DWORD dwFlags)  
{
	if (NULL == pcBuffer) return E_POINTER;

	m_strDesc = pcBuffer;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistPropertyBag
STDMETHODIMP CImportPropAct::Load (IPropertyBag *pBag, IErrorLog *pLog)
{
	USES_CONVERSION;
	RETURN_FAILED_HRESULT(CPropertyAction::Load (pBag, pLog));

	m_caImportInfo.m_listNames.clear();
	m_caImportInfo.m_strProgID.empty();
	m_caImportInfo.m_dwFlags = 0L;
	m_caImportInfo.m_fShowErrors = TRUE;	// default: Fehler anzeigen

// ProgID der ImportErweiterung lesen
CComVariant vParam;
HRESULT hr = pBag -> Read (CComBSTR(g_cbProgID), &vParam, pLog);

	if (S_OK == hr && SUCCEEDED(vParam.ChangeType (VT_BSTR)))
	{
		m_caImportInfo.m_strProgID = OLE2A(V_BSTR(&vParam));
	}

// zu importierende Datei(en) einlesen (z.Zt nur eine Datei!!)
#pragma MSG(TODO: Voreinstellung für ImportDataPropAct auf mehrere Dateien ausbauen!)

	vParam.Clear();
	hr = pBag -> Read (CComBSTR(g_cbFiles), &vParam, pLog);
	if (S_OK == hr && SUCCEEDED(vParam.ChangeType (VT_BSTR)))
	{
		m_caImportInfo.m_listNames.push_back (OLE2A(V_BSTR(&vParam)));
	}

// zu importierende Infos einlesen
	vParam.Clear();
	hr = pBag -> Read (CComBSTR(g_cbFlags), &vParam, pLog);
	if (S_OK == hr && SUCCEEDED(vParam.ChangeType (VT_I4)))
	{
		m_caImportInfo.m_dwFlags = V_I4(&vParam);
	}

// Fehlermeldungen anzeigen ?
	vParam.Clear();
	hr = pBag -> Read (CComBSTR(g_cbShowErrors), &vParam, pLog);
	if (S_OK == hr && SUCCEEDED(vParam.ChangeType (VT_I4)))
	{
		m_caImportInfo.m_fShowErrors = V_I4(&vParam);
	}
	
	m_fHasInitData = 1;
	return S_OK;
}
