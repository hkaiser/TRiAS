// Collection von Docs (Controlling Unknown) -------------------------
// File: DOCS.CXX

#include "precomp.hxx"

#include <dirisole.h>

#include "docarray.hxx"		// CGeoDocsArray
#include "enumdocs.hxx"		// CEnumDocs
#include "docs.hxx"			// CGeoDocs

#if defined(_DEBUG) && defined(WIN32)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

///////////////////////////////////////////////////////////////////////////////
// zugehörige CriticalSection
//CComGlobalsThreadModel::AutoCriticalSection CGeoDocs::m_cs;

// Das eigentliche  Docs Object --------------------------------------------
CGeoDocs::CGeoDocs(void)
	: m_fValid(false)
{
	CONSTRUCT_TRACE(CGeoDocs);
	
	m_pUnk = NULL;
	m_pApp = NULL;
	m_pEnumDocs = NULL;
	
	m_pICProc = NULL;
	m_dwData = 0L;
	m_pDCProc = NULL;
}

bool CGeoDocs::FInit (LPUNKNOWN pUnk, CTriasApp *pApp, 
	INITDOCCOLLECTIONPROC pICFunc, DWORD dwData, DELETEDOCCOLLECTIONPROC pDCProc)
{
// Parent festhalten
	if (pUnk == NULL || pApp == NULL) return FALSE;
	
	m_pICProc = pICFunc;
	m_dwData = dwData;
	m_pDCProc = pDCProc;

	m_pUnk = pUnk;
//	ADDREF (m_pUnk);
	
// Applikation festhalten
	m_pApp = pApp;
//	ADDREF_CAST(_IApplication, m_pApp);

// Identbaum anlegen und füllen
	return Regenerate();
}

bool CGeoDocs::Regenerate (void)
{
	DELETE_OBJ(m_pEnumDocs);
	m_pEnumDocs = CEnumDocs::CreateInstance (m_pUnk, m_pApp, m_pICProc, m_dwData);
	if (m_pEnumDocs == NULL) return FALSE;
	
return TRUE;
}

CGeoDocs::~CGeoDocs (void)
{
	DESTRUCT_TRACE(CGeoDocs);
	
//	RELEASE (m_pUnk);	// Parent wieder loslassen
//	RELEASE_CAST(_IApplication, m_pApp);	// Applikation wieder loslassen

	DELETE_OBJ(m_pEnumDocs);
}

CGeoDocs *CGeoDocs::CreateInstance (LPUNKNOWN pUnk, CTriasApp *pApp, 
				        INITDOCCOLLECTIONPROC pICFunc, DWORD dwData,
				        DELETEDOCCOLLECTIONPROC pDCProc)
{
CComObject<CGeoDocs> *pDocs = NULL;

	try {
	// Create an instance of CGeoDocs.  Exit if an error occurs.
	HRESULT hr = CComObject<CGeoDocs>::CreateInstance (&pDocs);

		if (FAILED(hr)) _com_issue_error(hr);
		if (!pDocs -> FInit (pUnk, pApp, pICFunc, dwData, pDCProc)) 
			_com_issue_error(E_FAIL);

		pDocs -> AddRef();	// fertig initialisiert
	
	} catch (_com_error&) {
		DELETE_OBJ (pDocs);
		return NULL;
	}
	
// If execution has reached this point, then no errors have occurred.
	pDocs -> Validate();
	return pDocs;
}

///////////////////////////////////////////////////////////////////////////////
// Funktionen werden gerufen, wenn externe Locks entstehen bzw.
// verschwinden
ULONG CGeoDocs::InternalAddRef()
{
	_ASSERTE(m_dwRef != -1L);
	Lock();

long l = CComObjectRoot::InternalAddRef();

	if (m_dwRef == DOCS_EXTERNAL_THRESHOLD+1) {
		Unlock();
		FinalExternalConstruct();
	} else 
		Unlock();
	return l;
}

ULONG CGeoDocs::InternalRelease()
{
	Lock();

long l = CComObjectRoot::InternalRelease();

	if (m_dwRef == DOCS_EXTERNAL_THRESHOLD) {
		Unlock();
		FinalExternalRelease();
	} else 
		Unlock();
	return l;
}

HRESULT CGeoDocs::FinalExternalConstruct (void)
{
	ADDREF(m_pUnk);
	ADDREF_CAST(_DApplication, m_pApp);
	return S_OK;
}

void CGeoDocs::FinalExternalRelease (void)
{
	RELEASE_NONULL(m_pUnk);						// Parent wieder loslassen
	RELEASE_CAST(_DApplication, m_pApp);	// Applikation wieder loslassen
}

