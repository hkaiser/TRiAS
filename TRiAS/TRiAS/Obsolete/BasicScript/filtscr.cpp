// PropertyAction, welche Objekte aus RechercheFenster auswählt und zusammenstellt
// File: FILTSCR.CPP

#include "bscriptp.hxx"
#include "bscript.h"


#include <oleguid.h>
#include <dirisole.h>
#include <triastlb.h>
#include <xtsnguid.h>
#include <eonrguid.h>

#include <pdataobj.hxx>
#include <ipropseq.hxx>

#include "macrguid.h"

#include "imacro.h"  
#include "imacorg.h"                

// #include "toolbarx.h"

#include "datahelp.h"

#include "enumscpt.h"
#include "strmimp.h"
#include "perstimp.h"
#include "macroimp.h"
#include "macro.h"

// #include "toolbarx.h"
#include "runerr.h"

#include "filtdlg.h"
#include "filtscr.h"

#define OS_NO_STREAM_SUPPORT

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern char g_pDLLName[]; 

BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_FilterScript, CFilterScriptPropAct)
END_OBJECT_MAP()

_ATL_OBJMAP_ENTRY *GetObjectMap (void)
{
	return ObjectMap;		
}

///////////////////////////////////////////////////////////////////////////////
// Min-Funktion, da Macro aus stdlib offensichtlich überladen ist
template<class T>
inline T tmin (T a, T b) { return (a > b) ? b : a; }

CFilterScriptPropAct :: CFilterScriptPropAct (void)
{
	m_pFilterScriptDlg = NULL;
	m_fIsDirty = false;
	m_fIsInitialized = false;
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
				LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam, 
			    LPCSTR pcDesc, UINT *puiCnt)
{
	if (m_pFilterScriptDlg) delete m_pFilterScriptDlg;
	m_pFilterScriptDlg = NULL;

	m_pFilterScriptDlg = CFilterScriptDlg::CreateInstance();
	ASSERT(m_pFilterScriptDlg);
	if (NULL == m_pFilterScriptDlg) return ResultFromScode(E_FAIL);

HPROPSHEETPAGE hPSP = NULL;
PROPSHEETPAGE psp;

	memcpy(&psp, &m_pFilterScriptDlg->m_psp, sizeof(PROPSHEETPAGE));

	hPSP = CreatePropertySheetPage (&psp);
	ASSERT(hPSP);
	if (NULL == hPSP) return E_FAIL;

	if (!(*lpfnAddPage) (hPSP, lParam))  return E_FAIL;

// wir haben eine (1) Page hinzugefügt
	if (puiCnt) *puiCnt = 1;
	
return NOERROR;
}  

STDMETHODIMP CFilterScriptPropAct::PreConfigPages (IDataObject *, DWORD dwFlags)
{
	ASSERT(NULL != m_pFilterScriptDlg);

	m_pFilterScriptDlg -> SetFlags (dwFlags);
	return NOERROR;
}

STDMETHODIMP CFilterScriptPropAct::BeginAction (IProgressIndicator * pIProgInd)
{
	ASSERT(m_pFilterScriptDlg);
	if (m_pFilterScriptDlg == NULL) return E_UNEXPECTED; 

return m_pFilterScriptDlg -> BeginAction ();
}

// wird ein paar Mal gerufen bis EndAction() 
STDMETHODIMP CFilterScriptPropAct::DoAction (IDataObject *pIDataObj, DWORD)
{
WEnumLONG IEnumOut;
// AddRef()
HRESULT hr = GetEnumLONGData (pIDataObj, IEnumOut.ppi());
	if (FAILED(hr)) return hr;

// für jedes Objekt(while innerhalb)
// Release()
return m_pFilterScriptDlg -> DoAction(IEnumOut);	
}

// wird bei S_OK wieder gerufen, fertiges Datenobjekt übergeben, so viele Datenobjekte
// wie DoAction() merken
STDMETHODIMP CFilterScriptPropAct::EndAction (DWORD, IDataObject **ppDataObj)
{
	ASSERT(m_pFilterScriptDlg);
	if (m_pFilterScriptDlg == NULL) return E_UNEXPECTED; 
	ASSERT(ppDataObj);
	
HRESULT hr = NOERROR;
WEnumLONG IEnumObj;

// liefert S_OK, solange Enums vorhanden sind, AddRef()
HRESULT hResult = m_pFilterScriptDlg -> GetEnumLONG (IEnumObj.ppi());	
	if (FAILED(hResult)) return hResult;

	*ppDataObj = NULL;

	try {	
	// DataObject generieren, welches Info's über unser Ergebnis enthält
		hr = CoCreateInstance ( CLSID_DataTransferObject, NULL, 
								CLSCTX_INPROC_SERVER, 
								IID_IDataObject, 
								(LPVOID *)ppDataObj);
		if (FAILED(hr)) throw hr;

	// schreiben des EnumLONG ins DataObject
	HRESULT hr2 = SetEnumLONGData (IEnumObj, CLSID_EnumObjectsByNumber, *ppDataObj);

		if (FAILED(hr2)) throw hr2;

	} catch (HRESULT hr_result) {
		if (*ppDataObj)	(*ppDataObj) -> Release(); *ppDataObj = NULL;  
		if (m_pFilterScriptDlg) delete m_pFilterScriptDlg; m_pFilterScriptDlg = NULL;
		ASSERT(0);
		return hr_result;
	}

// S_OK heißt, daß GetEnumLONG nicht mehr gerufen werden muß
	if (S_FALSE != GetScode(hr)) {	// letzter Enumerator

		hr = m_pFilterScriptDlg -> EndAction();

		delete m_pFilterScriptDlg;
		m_pFilterScriptDlg = NULL;
		
		if (FAILED(hr)) return hr;

		return NOERROR;
	}

return hResult;		// war's der letzte ?
}

///////////////////////////////////////////////////////////////////////////////
// IPersist methods
STDMETHODIMP CFilterScriptPropAct::GetClassID (LPCLSID lpClassID)
{
	ASSERT(lpClassID);

	if (NULL == lpClassID)
		return E_POINTER;

//	*lpClassID = CLSID_FilterScripts;
	return NOERROR;
}

// IPersistStreamInit methods
STDMETHODIMP CFilterScriptPropAct::IsDirty (void)
{
	return m_fIsDirty;
}

STDMETHODIMP CFilterScriptPropAct::Load (LPSTREAM pStm)
{
	if (m_fIsInitialized)
		return E_UNEXPECTED;		// already initialized with InitNew

HRESULT hr = CPropertyAction::Load (pStm);
	if (FAILED(hr)) return hr;
	
	m_fIsInitialized = true;
	m_fIsDirty = false;

return NOERROR;
}

STDMETHODIMP CFilterScriptPropAct::InitNew (void)
{
	if (m_fIsInitialized)
		return E_UNEXPECTED;		// already initialized with Load

	m_fIsInitialized = true;
	m_fIsDirty = false;

return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// IPropertyInfo specific functions 
STDMETHODIMP CFilterScriptPropAct::SetPropInfo (LPCSTR pcBuffer, DWORD dwFlags) 
{
	ASSERT(pcBuffer);

	if (NULL == pcBuffer) return E_POINTER;

	m_strDesc = pcBuffer;

	return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// Sonstiges
void CFilterScriptPropAct::SetDirty (bool fDirty) 
{ 
	m_fIsDirty = fDirty; 
}

