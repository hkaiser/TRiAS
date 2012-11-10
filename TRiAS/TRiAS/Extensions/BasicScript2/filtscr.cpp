// PropertyAction, welche Objekte aus RechercheFenster auswählt und zusammenstellt
// File: FILTSCR.CPP

#include "bscriptp.hxx"
#include "bscript.h"


#include <oleguid.h>
#include <dirisole.h>
#include <triastlb.h>
#include <xtsnguid.h>
#include <eonrguid.h>

extern CComModule _Module;

#include <pdataobj.hxx>
#include <ipropseq.hxx>

#include "macrguid.h"

#include "iscrprop.h"
#include "conststr.h"
#include "datahelp.h"
#include "macro.h"
#include "runerr.h"

DefineEnumerator2(LONG, IID_IEnumLONG);
#include "filtdlg2.h"
#include "filtscr.h"

#define OS_NO_STREAM_SUPPORT

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern char g_pDLLName[]; 
BOOL		LoadString(CString & str, int IDS);

/////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(PropertyActionSequence);			// WPropertyActionSequence
DefineSmartInterface(DataObject);						// WDataObject

///////////////////////////////////////////////////////////////////////////////
// Min-Funktion, da Macro aus stdlib offensichtlich überladen ist
template<class T>
inline T tmin (T a, T b) { return (a > b) ? b : a; }

CFilterScriptPropAct :: CFilterScriptPropAct (void)
{
	m_pFilterScriptDlg = NULL;
	m_fIsDirty = false;
	m_fIsInitialized = false;
	m_hPrCtx = HACTCONNECTION;
}

CFilterScriptPropAct :: ~CFilterScriptPropAct (void)
{
	if (m_pFilterScriptDlg) delete m_pFilterScriptDlg;
	m_pFilterScriptDlg = NULL;
}

///////////////////////////////////////////////////////////////////////////////
// IClassProperty specific functions 
STDMETHODIMP CFilterScriptPropAct::GetPropInfo (LPSTR pBuffer, WORD wLen, DWORD *pdwFlags)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());

	if (NULL != pBuffer && wLen > 0) 
	{// Namen der Property kopieren
		if (0 == m_strDesc.GetLength()) 
			::LoadString(m_strDesc, IDS_LONGCLASSNAME);
		ULONG ulLen = tmin ((size_t)(wLen-1), (size_t)m_strDesc.GetLength());
		strncpy (pBuffer, m_strDesc, ulLen);
		pBuffer[ulLen] = '\0';
	}
	// wenn gewünscht, Flags übergeben
	if (pdwFlags) *pdwFlags = PROPCAPS_ACTION_SOURCE;

return NOERROR;
}

STDMETHODIMP CFilterScriptPropAct::HelpInfo (LPSTR pBuffer, ULONG wLen, LPSTR pHelpFile, ULONG *pulHelpCtx)
{
return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// IPropertyAction methods 
STDMETHODIMP CFilterScriptPropAct::AddConfigPages (
	LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam, LPCSTR pcDesc, UINT *puiCnt)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());

	DELETE_OBJ(m_pFilterScriptDlg);
	m_pFilterScriptDlg = CFilterScriptDlg2::CreateInstance();
	if (NULL == m_pFilterScriptDlg) return E_OUTOFMEMORY;


// dieses Script soll gestartet werden
	m_pFilterScriptDlg -> SetStartName (m_strScriptName);

	if (!IsNoShow()) {
	// Seite hizufügen
	PROPSHEETPAGE psp;

		memcpy(&psp, &m_pFilterScriptDlg->m_psp, sizeof(PROPSHEETPAGE));
		
	HPROPSHEETPAGE hPSP = ::CreatePropertySheetPage (&psp);

		if (NULL == hPSP) return E_HANDLE;

		if (!(*lpfnAddPage) (hPSP, lParam))
			return E_FAIL;
		if (puiCnt) *puiCnt = 1;		// wir haben eine Page hinzugefügt
	} else {
	// In diesem Falle muß ein Startsctript geladen sein 
		ASSERT(!m_strScriptName.IsEmpty());
		
	// Script von aussen init., öffnen
		RETURN_FAILED_HRESULT(m_pFilterScriptDlg -> OuterInit());
		if (puiCnt) *puiCnt = 0;		// wir haben keine Page hinzugefügt
	}
	return S_OK;
}  

STDMETHODIMP CFilterScriptPropAct::PreConfigPages (IDataObject *, DWORD dwFlags)
{
	ASSERT(NULL != m_pFilterScriptDlg);

	m_pFilterScriptDlg -> SetFlags (dwFlags);
	return NOERROR;
}

STDMETHODIMP CFilterScriptPropAct::BeginAction (IProgressIndicator * pIProgInd)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());

	COM_TRY {
		if (NULL == m_pFilterScriptDlg)	{
		// In diesem Falle muss ein Startsctript geladen sein 
			if (m_strScriptName.IsEmpty()) _com_issue_error(E_FAIL);
		
		// Dialog nur als Objekt laden, nicht anzeigen
			m_pFilterScriptDlg = CFilterScriptDlg2::CreateInstance();
			if (NULL == m_pFilterScriptDlg) _com_issue_error(E_OUTOFMEMORY);
		
		// zu startendes Script setzen
			m_pFilterScriptDlg -> SetStartName(m_strScriptName);
		
		// Script von aussen init., öffnen
			THROW_FAILED_HRESULT(m_pFilterScriptDlg -> OuterInit());
		}

	// Zieldatenquelle aus KontextObjektherausfinden
		if (HACTCONNECTION == m_hPrCtx) {
		WPropertyActionSequence Seq;
		WDataObject CtxDO;
		CComVariant vData;
		HPROJECT hPrCtx = HACTCONNECTION;

			THROW_FAILED_HRESULT(GetSite (IID_IPropertyActionSequence, Seq.ppv()));
			THROW_FAILED_HRESULT(Seq -> GetSequenceContext (CtxDO.ppi()));
			if (SUCCEEDED(GetVariantData (CtxDO, &c_feDataSourceHandle, &vData)) &&
				SUCCEEDED(vData.ChangeType (VT_I4))) 
			{
				m_pFilterScriptDlg -> SetCtxDataSource (reinterpret_cast<HPROJECT>(V_I4(&vData)));
			}
		} 
		else {
			m_pFilterScriptDlg -> SetCtxDataSource (m_hPrCtx);
		}
		THROW_FAILED_HRESULT(m_pFilterScriptDlg -> BeginAction());

	} COM_CATCH;
	return S_OK;
}

// wird ein paar Mal gerufen bis EndAction() 
STDMETHODIMP CFilterScriptPropAct::DoAction (IDataObject *pIDataObj, DWORD)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());

	COM_TRY {
	WEnumLONG IEnumOut;

		if (NULL == pIDataObj) 
			IEnumOut = WEnumLONG(CLSID_EnumObjectsByNumber);
		else
			THROW_FAILED_HRESULT(GetEnumLONGData (pIDataObj, IEnumOut.ppi()));

		THROW_FAILED_HRESULT(m_pFilterScriptDlg -> DoAction(IEnumOut));		// für jedes Objekt(while innerhalb)
	} COM_CATCH;
	return S_OK;
}

// wird bei S_OK wieder gerufen, fertiges Datenobjekt übergeben, so viele Datenobjekte
// wie DoAction() merken
STDMETHODIMP CFilterScriptPropAct::EndAction (DWORD, IDataObject **ppDataObj)
{	
	AFX_MANAGE_STATE(AfxGetAppModuleState());

// Holt alle IEnums in Form von IDataObject * zurück
	ASSERT(NULL != m_pFilterScriptDlg);
	ASSERT(NULL != ppDataObj);
	if (NULL == m_pFilterScriptDlg || NULL == ppDataObj) 
		return E_UNEXPECTED; 

HRESULT hResult = NOERROR;

	*ppDataObj = NULL;
	COM_TRY {
	// liefert S_FALSE, solange Enums vorhanden sind, AddRef()
	WEnumLONG IEnumObj;
	WDataObject DO (CLSID_DataTransferObject);
		
		THROW_FAILED_HRESULT(hResult = m_pFilterScriptDlg -> GetEnumLONG (IEnumObj.ppi()));

	// schreiben des EnumLONG ins DataObject
		THROW_FAILED_HRESULT(SetEnumLONGData (IEnumObj, CLSID_EnumObjectsByNumber, DO));

	// S_OK heißt, daß GetEnumLONG nicht mehr gerufen werden muß
		if (S_OK == hResult) {
		// letzter Enumerator, EndAction rufen
			THROW_FAILED_HRESULT(m_pFilterScriptDlg -> EndAction());

		// Nun noch den ausgeführten Script holen
		char Buffer[_MAX_PATH];

			THROW_FAILED_HRESULT(m_pFilterScriptDlg -> GetStartName(Buffer, _MAX_PATH));
			m_strScriptName = Buffer;

		// Freigeben des Dialogs
			DELETE_OBJ(m_pFilterScriptDlg);		
		}
		*ppDataObj = DO.detach();

	} COM_CATCH_OP((delete m_pFilterScriptDlg, m_pFilterScriptDlg = NULL));

// Bei S_FALSE immer weiterruffen, S_OK == Abbruch (dem Letzten)
	return hResult;
}

///////////////////////////////////////////////////////////////////////////////
// IPersist methods
STDMETHODIMP CFilterScriptPropAct::GetClassID (LPCLSID lpClassID)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	ASSERT(lpClassID);

	if (NULL == lpClassID)
		return E_POINTER;

	*lpClassID = CLSID_FilterScript;

	return NOERROR;
}

// IPersistStreamInit methods
STDMETHODIMP CFilterScriptPropAct::IsDirty (void)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	return m_fIsDirty ? S_OK : S_FALSE;
}

STDMETHODIMP CFilterScriptPropAct::Load (LPSTREAM pStm)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());

// Hier soll gespeichertes Makro geladen werden.
	if (m_fIsInitialized) return E_UNEXPECTED;		// already initialized with InitNew

	RETURN_FAILED_HRESULT(CPropertyAction::Load (pStm));

// Namen des zu Ladenden holen
	RETURN_FAILED_HRESULT(LoadName(pStm));

	m_fIsInitialized = true;
	m_fIsDirty = false;
	return NOERROR;
}

// BasisKlasse schreibt lediglich den Bezeichner weg 
STDMETHODIMP CFilterScriptPropAct::Save (LPSTREAM pStm, BOOL fClearDirty)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	HRESULT hr = CPropertyAction::Save (pStm, fClearDirty);
	if (FAILED(hr)) return hr;
	// Namen des zuletzt genutzten und später neu zu Ladenden speichern
	return SaveName (pStm, fClearDirty);
}

STDMETHODIMP CFilterScriptPropAct::InitNew (void)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());

// Hier soll neues Makro geladen werden: Makro1...Makron
	if (m_fIsInitialized)
		return E_UNEXPECTED;		// already initialized with Load

	m_fIsInitialized = true;
	m_fIsDirty = false;
	m_strScriptName.Empty();
	return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// IPropertyInfo specific functions 
STDMETHODIMP CFilterScriptPropAct::SetPropInfo (LPCSTR pBuffer, DWORD dwFlags)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	ASSERT(pBuffer);
	if (NULL == pBuffer) return E_POINTER;
	m_strDesc = pBuffer;
	return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// IPersistPropertyBag
STDMETHODIMP CFilterScriptPropAct::Load (IPropertyBag *pBag, IErrorLog *pLog)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());

	RETURN_FAILED_HRESULT(CPropertyAction::Load (pBag, pLog));

// weitere Parameter einlesen
CComVariant vScriptName;
HRESULT hr = pBag -> Read (CComBSTR(g_cbPAScriptName), &vScriptName, pLog);

	if (S_OK == hr && SUCCEEDED(vScriptName.ChangeType (VT_BSTR))) {
		USES_CONVERSION;
		m_strScriptName = OLE2A(V_BSTR(&vScriptName));

		m_fIsInitialized = true;
		m_fIsDirty = false;
	}

// DataSource=
CComVariant vParam;

	m_hPrCtx = HACTCONNECTION;
	hr = pBag -> Read (CComBSTR(g_cbPADataSource), &vParam, pLog);
	if (S_OK == hr && SUCCEEDED(vParam.ChangeType (VT_BSTR)))
	{
	CComBSTR bstrDS (V_BSTR(&vParam));

		if (bstrDS.Length() > 0) {
			USES_CONVERSION;
			m_hPrCtx = DEX_GetDataSourceHandleFromShortName (OLE2A(bstrDS));
		}
	}
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
// Sonstiges
void CFilterScriptPropAct::SetDirty (BOOL fDirty) 
{ 
	m_fIsDirty = fDirty; 
}

HRESULT CFilterScriptPropAct::LoadName (LPSTREAM pStm)
{
// Daten einlesen, Länge des Namens lesen
ULONG ulLen = 0;
ULONG ulRead = 0;

	RETURN_FAILED_HRESULT(pStm -> Read (&ulLen, sizeof(ULONG), &ulRead));
	if (ulLen == 0 || ulLen > _MAX_PATH || ulRead != sizeof(ULONG)) 
		return E_FAIL;

// Namen lesen
char cbBuffer[_MAX_PATH];

	RETURN_FAILED_HRESULT(pStm -> Read (cbBuffer, ulLen, &ulRead));
	if (ulLen != ulRead) 
		return E_FAIL;

// Namen in Member kopieren
	m_strScriptName = cbBuffer;
	return S_OK;
}

HRESULT CFilterScriptPropAct::SaveName (LPSTREAM pStm, BOOL fClearDirty)
{
ULONG ulLen = m_strScriptName.GetLength()+1;

	if (ulLen == 0 || ulLen > _MAX_PATH) 
		return E_FAIL;

// Länge des Namens wegschreiben
ULONG ulWritten = 0;

	RETURN_FAILED_HRESULT(pStm -> Write (&ulLen, sizeof(ULONG), &ulWritten));
	if (ulWritten != sizeof(ULONG)) return E_FAIL;

// Namen wegschreiben
	RETURN_FAILED_HRESULT(pStm -> Write ((LPCSTR)m_strScriptName, ulLen, &ulWritten));
	if (ulWritten != ulLen) return E_FAIL;

	return S_OK;
}
