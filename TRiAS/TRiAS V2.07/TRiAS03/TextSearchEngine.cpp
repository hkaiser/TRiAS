// TextSearchEngine.cpp : Implementation of CTextSearchEngine

#include "trias03p.hxx"
#include "trias03.h"

#include <ospace/com/olestrea.h>
#include <xtsnguid.h>
#include <srchguid.h>
#include <statguid.h>

#include <funcs03.h>
#include <int64.h>

#include "Datahelp.h"
#include "TRiASHelper.h"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "TextSearchEngine.h"

///////////////////////////////////////////////////////////////////////////////
// Min-Funktion, da Macro aus stdlib offensichtlich überladen ist
template<class T>
inline T tmin (T a, T b) { return (a > b) ? b : a; }

///////////////////////////////////////////////////////////////////////////////
// benötigte InterfaceWrapper
DefineSmartInterface(DataObject);
DefineSmartEnumerator(LONG);	// WEnumLONG

///////////////////////////////////////////////////////////////////////////////
//
extern char g_pDLLName[_MAX_PATH];

///////////////////////////////////////////////////////////////////////////////
//
CTextSearchEngine::CTextSearchEngine (void)
{
	m_pCfgDlg = NULL;
	m_fIsDirty = false;
	m_fIsInitialized = false;

	try {
	ResourceFile RF (g_pDLLName);
	ResString resPropInfo (ResID (IDS_TEXTSEARCHENGINE_DESC, &RF), 64);

		m_strDesc = resPropInfo;
	} catch (...) {
		TX_ASSERT(false);
	}
}

CTextSearchEngine::~CTextSearchEngine (void)
{
	DELETE_OBJ(m_pCfgDlg);
}

/////////////////////////////////////////////////////////////////////////////
// IPropertyAction methods
STDMETHODIMP CTextSearchEngine::AddConfigPages (LPFNADDPROPSHEETPAGE lpfnAddPage, 
								LPARAM lParam, LPCSTR pcDesc, UINT *puiCnt)
{
char cbCaption[128];

	try {
		if (NULL != pcDesc)		// Caption ist gegeben
			strcpy (cbCaption, pcDesc);
		else	// von zugehöriger ClassProperty unseren Namen besorgen
			GetPropInfo (cbCaption, sizeof(cbCaption), NULL);

	// zugehörigen ConfigDialog (PropertyPage(s)) anlegen
	ResourceFile RF (g_pDLLName);
	UINT uiRes = IsWin40() ? IDD_TEXTSEARCHENGINE_CFG : IDD_TEXTSEARCHENGINE_CFG_WIN32S;

		DELETE_OBJ(m_pCfgDlg);	// evtl. vorherigen freigeben
		m_pCfgDlg = CCfgTextSearch::CreateInstance (this, 
						ResID (uiRes, &RF), cbCaption);
		if (NULL == m_pCfgDlg) _com_issue_error(E_OUTOFMEMORY);

	HPROPSHEETPAGE hPSP = m_pCfgDlg -> CreatePage();

		if (NULL == hPSP || !lpfnAddPage(hPSP, lParam))
			_com_issue_error(E_UNEXPECTED);

		if (puiCnt) *puiCnt = 1;

		m_pCfgDlg -> InitWithData (m_Status);

	} catch (_com_error& hr_result) {
		DELETE_OBJ (m_pCfgDlg);
		if (puiCnt) *puiCnt = 0;
		return _COM_ERROR(hr_result);
	}
	
return NOERROR;
}

STDMETHODIMP CTextSearchEngine::PreConfigPages (IDataObject *pIDataObject, DWORD dwFlags)
{
	if (NULL == m_pCfgDlg) return E_UNEXPECTED;
	
	m_pCfgDlg -> SetFlags(dwFlags);
	return NOERROR;
}

STDMETHODIMP CTextSearchEngine::BeginAction (IProgressIndicator *pPI)
{
	// JG 980916 
	CPropertyActionExt::BeginAction(pPI);	

	if (NULL == m_pCfgDlg) return E_UNEXPECTED;

	return m_pCfgDlg -> ResetEnumLONG();
}

STDMETHODIMP CTextSearchEngine::DoAction (IDataObject *pIDataObj, DWORD)
{
	if (NULL == m_pCfgDlg) return E_UNEXPECTED;

WEnumLONG EnumObj;
HRESULT hr = GetEnumLONGData (pIDataObj, EnumObj.ppi());

	if (SUCCEEDED(hr)) 
	{
		// JG 980916 für ProgInd vorbereiten
		m_pCfgDlg -> SetAction(this);

		hr = m_pCfgDlg -> SetEnumLONG (EnumObj);
	}
	return hr;
}

STDMETHODIMP CTextSearchEngine::EndAction (DWORD, IDataObject **ppDataObj)
{
	if (NULL == m_pCfgDlg) return E_UNEXPECTED;
	if (NULL == ppDataObj) return E_POINTER;

//  
// DataObject generieren und mit EnumObj füllen
WEnumLONG EnumObj;
HRESULT hr = m_pCfgDlg -> GetEnumLONG (EnumObj.ppi());
	
	if (FAILED(hr)) return hr;

	*ppDataObj = NULL;
	try {
	WDataObject IDO;
	
		hr = DataObjectCreateInstance (NULL, IID_IDataObject, IDO.ppv());
		if (FAILED(hr)) _com_issue_error(hr);

	HRESULT hr2 = SetEnumLONGData (EnumObj, IDO);
		
		if (FAILED(hr2)) _com_issue_error(hr2);

		*ppDataObj = IDO.detach();

	} catch (_com_error& hr_result) {
		hr = _COM_ERROR(hr_result);
	// hier durchfallen
	}

	if (S_OK != hr)				// nach dem letzten Aufruf
		DELETE_OBJ(m_pCfgDlg);		// Dialog wird nicht mehr gebraucht

	return hr;
}

/////////////////////////////////////////////////////////////////////////////
// IClassProperty specific functions
STDMETHODIMP CTextSearchEngine::GetPropInfo (LPSTR pBuffer, WORD wLen, DWORD *pdwFlags)
{
	try {
		if (NULL != pBuffer && wLen > 0) {
		// Namen der Property kopieren
		ULONG ulLen = tmin ((size_t)(wLen-1), m_strDesc.length());

			strncpy (pBuffer, m_strDesc.c_str(), ulLen);
			pBuffer[ulLen] = '\0';
		}
	} catch (...) {
		return E_FAIL;
	}

// wenn gewünscht, Flags übergeben
	if (pdwFlags) *pdwFlags = PROPCAPS_ACTION_SEARCHENGINE|PROPCAPS_ACTION_SOURCE;

return NOERROR;
}

STDMETHODIMP CTextSearchEngine::HelpInfo (LPSTR pBuffer, ULONG wLen, LPSTR pHelpFile, ULONG *pulHelpCtx)
{
	try {
		if (NULL != pBuffer && wLen > 0) {
		// Beschreibung übergeben
		ResourceFile RF (g_pDLLName);
		ResString resHelp (ResID (IDS_HELPDESC_IDENTOTYP, &RF), 128);
		ULONG ulLen = tmin ((size_t)(wLen-1), strlen(resHelp));

			strncpy (pBuffer, resHelp, ulLen);
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

/////////////////////////////////////////////////////////////////////////////
// IPropertyInfo specific functions 
STDMETHODIMP CTextSearchEngine::SetPropInfo (LPCSTR pcBuffer, DWORD dwFlags) 
{
	if (NULL == pcBuffer) return E_POINTER;

	m_strDesc = pcBuffer;
	return NOERROR;
}

/////////////////////////////////////////////////////////////////////////////
// IPersist methods
STDMETHODIMP CTextSearchEngine::GetClassID (CLSID *pClsID)
{
	if (NULL == pClsID)
		return E_POINTER;

	*pClsID = CLSID_TextSearchEngine;
	return NOERROR;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistStreamInit methods
STDMETHODIMP CTextSearchEngine::IsDirty(void)
{
	return m_fIsDirty ? S_OK : S_FALSE;
}

STDMETHODIMP CTextSearchEngine::Load(LPSTREAM pStm)
{
	if (m_fIsInitialized)
		return E_UNEXPECTED;		// already initialized with InitNew

HRESULT hr = CPropertyAction::Load (pStm);

	if (FAILED(hr)) return hr;

	try {
		TX_ASSERT(sizeof(int) == sizeof(long));
		
		THROW_FAILED_HRESULT(LoadLong(pStm, (long &)m_Status.m_fCapital));
		THROW_FAILED_HRESULT(LoadLong(pStm, (long &)m_Status.m_fPartialMatch));
		THROW_FAILED_HRESULT(LoadLong(pStm, (long &)m_Status.m_fFuzzyMatch));
		THROW_FAILED_HRESULT(LoadLong(pStm, (long &)m_Status.m_fUseRegExpr));

		THROW_FAILED_HRESULT(LoadString(pStm, m_Status.m_strFindWhat));

	CSearchList::size_type lCnt = 0;

		m_Status.erase();
		THROW_FAILED_HRESULT(LoadLong(pStm, (long &)lCnt));
		for (CSearchList::size_type i = 0; i < lCnt; i++) {
		os_string str;

			THROW_FAILED_HRESULT(LoadString(pStm, str));
			m_Status.m_lstFindWhat.push_back(str);
		}

		THROW_FAILED_HRESULT(LoadString(pStm, m_Status.m_strObjProp));

	// folgende Einträge sind optional, da später dazugekommen
		if (FAILED(LoadLong(pStm, (long &)m_Status.m_fTestBOB)))
			m_Status.m_fTestBOB = false;
		if (FAILED(LoadLong(pStm, (long &)m_Status.m_fExistsOnly)))
			m_Status.m_fExistsOnly = false;
		if (FAILED(LoadLong(pStm, (long &)m_Status.m_fNegate)))
			m_Status.m_fNegate = false;

	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}

	m_fIsInitialized = true;
	m_fIsDirty = false;

return NOERROR;
}

STDMETHODIMP CTextSearchEngine::Save (LPSTREAM pStm, BOOL fClearDirty)
{
// zuerst Bezeichner wegschreiben
HRESULT hr = CPropertyAction::Save (pStm, fClearDirty);

	if (FAILED(hr)) return hr;

	try {
		THROW_FAILED_HRESULT(SaveLong(pStm, m_Status.m_fCapital));
		THROW_FAILED_HRESULT(SaveLong(pStm, m_Status.m_fPartialMatch));
		THROW_FAILED_HRESULT(SaveLong(pStm, m_Status.m_fFuzzyMatch));
		THROW_FAILED_HRESULT(SaveLong(pStm, m_Status.m_fUseRegExpr));

		THROW_FAILED_HRESULT(SaveString(pStm, m_Status.m_strFindWhat));

		THROW_FAILED_HRESULT(SaveLong(pStm, m_Status.m_lstFindWhat.size()));
		for (CSearchList::iterator it = m_Status.m_lstFindWhat.begin(); 
			 it != m_Status.m_lstFindWhat.end(); ++it)
		{
			THROW_FAILED_HRESULT(SaveString(pStm, *it));
		}

		THROW_FAILED_HRESULT(SaveString(pStm, m_Status.m_strObjProp));

		THROW_FAILED_HRESULT(SaveLong(pStm, m_Status.m_fTestBOB));
		THROW_FAILED_HRESULT(SaveLong(pStm, m_Status.m_fExistsOnly));
		THROW_FAILED_HRESULT(SaveLong(pStm, m_Status.m_fNegate));

	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}

// dann selektierte Info der letzten Auswahl
	if (fClearDirty) m_fIsDirty = false;
	return NOERROR;
}

STDMETHODIMP CTextSearchEngine::GetSizeMax (ULARGE_INTEGER *pcbSize)
{
	if (NULL == pcbSize) return E_POINTER;

ULARGE_INTEGER cbSize;
HRESULT hr = CPropertyAction::GetSizeMax (&cbSize);

	if (FAILED(hr)) return hr;

LARGE liOwnSize (UINT(7*sizeof(LONG)));

	liOwnSize = liOwnSize + LARGE(UINT(::GetSizeMax (m_Status.m_strFindWhat)));
	for (CSearchList::iterator it = m_Status.m_lstFindWhat.begin(); 
		 it != m_Status.m_lstFindWhat.end(); ++it)
	{
		liOwnSize = liOwnSize + LARGE(UINT(::GetSizeMax (*it)));
	}
	liOwnSize = liOwnSize + LARGE(UINT(::GetSizeMax (m_Status.m_strObjProp)));

	liOwnSize = liOwnSize + LARGE(cbSize);
	*pcbSize = liOwnSize;
	
	return S_OK;
}

STDMETHODIMP CTextSearchEngine::InitNew(void)
{
	if (m_fIsInitialized)
		return E_UNEXPECTED;		// already initialized with Load

	m_fIsInitialized = true;
	m_fIsDirty = false;

return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// Sonstiges
void CTextSearchEngine::SetDirty (bool fDirty) { m_fIsDirty = fDirty; }
