// Collection der Features (Controlling Unknown) ------------------
// File: FTS.CXX

#include "precomp.hxx"

#include <dirisole.h>

#include "ftsarray.hxx"
#include "enumfts.hxx"
#include "fts.hxx"

#if defined(_DEBUG) && defined(WIN32)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

///////////////////////////////////////////////////////////////////////////////
// zugehörige CriticalSection
//CComGlobalsThreadModel::AutoCriticalSection CGeoFeatures::m_cs;

///////////////////////////////////////////////////////////////////////////////
// Das eigentliche Feature 
CGeoFeatures::CGeoFeatures (void)
	: m_fValid(false)
{
	CONSTRUCT_TRACE(CGeoFeatures);
	
	m_pUnk = NULL;
	m_pApp = NULL;
	m_pDoc = NULL;

	m_pViewClsObj = NULL;
	m_pEnumFts = NULL;
	
	m_pICProc = NULL;
	m_pDCProc = NULL;
	m_dwData = 0L;
	m_dwFlags = 0L;
}

bool CGeoFeatures::FInit (
	LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc, void *pViewClsObj,
	INITFEATCOLLECTIONPROC pICFunc, DWORD dwData,
	DELETEFEATCOLLECTIONPROC pDCProc, DWORD dwFlags) 
{
// Parent festhalten
	if (pUnk == NULL || pApp == NULL || pDoc == NULL) return FALSE;
	
	m_pICProc = pICFunc;
	m_pDCProc = pDCProc;
	m_dwData = dwData;
	m_dwFlags = dwFlags;

	m_pUnk = pUnk;
//	ADDREF (m_pUnk);
	
// Applikation festhalten
	m_pApp = pApp;
//	ADDREF_CAST(_IApplication, m_pApp);

// Projekt festhalten
	m_pDoc = pDoc;
//	ADDREF_CAST(_IDocument, m_pDoc);

// Object/Class/View
	m_pViewClsObj = pViewClsObj;
	ADDREF_CAST(IUnknown, m_pViewClsObj);

// Identbaum anlegen und füllen
	return Regenerate();
}

bool CGeoFeatures::Regenerate (void)
{
	DELETE_OBJ(m_pEnumFts);
	m_pEnumFts = CEnumGeoFts::CreateInstance (
		m_pUnk, m_pApp, m_pDoc, m_pViewClsObj, m_pICProc, m_dwData, m_dwFlags);
	if (m_pEnumFts == NULL) return false;

	return true;
}

CGeoFeatures::~CGeoFeatures (void)
{
	DESTRUCT_TRACE(CGeoFeatures);
	
//	RELEASE(m_pUnk);	// Parent wieder loslassen
//	RELEASE_CAST(_IApplication, m_pApp);	// Applikation wieder loslassen
//	RELEASE_CAST(_IDocument, m_pDoc);		// Document wieder loslassen

	RELEASE_CAST(IUnknown, m_pViewClsObj);

	DELETE_OBJ(m_pEnumFts);
}

CGeoFeatures *CGeoFeatures::CreateInstance (
	LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc, void *pViewClsObj,
	INITFEATCOLLECTIONPROC pICFunc, DWORD dwData,
	DELETEFEATCOLLECTIONPROC pDCProc, DWORD dwFlags)
{
CComObject<CGeoFeatures> *pGeoFts = NULL;

	try {
	// Create an instance of CGeoFeatures.  Exit if an error occurs.
	HRESULT hr = CComObject<CGeoFeatures>::CreateInstance (&pGeoFts);

		if (FAILED(hr)) _com_issue_error(hr);
		if(!pGeoFts -> FInit (pUnk, pApp, pDoc, pViewClsObj, pICFunc, dwData, pDCProc, dwFlags)) 
			_com_issue_error(E_FAIL);

		pGeoFts -> AddRef();	// fertig initialisiert

	} catch (_com_error&) {
		DELETE_OBJ (pGeoFts);
		return NULL;
	}
	
// If execution has reached this point, then no errors have occurred.
	pGeoFts -> Validate();
	return pGeoFts;
}

///////////////////////////////////////////////////////////////////////////////
// Funktionen werden gerufen, wenn externe Locks entstehen bzw.
// verschwinden
ULONG CGeoFeatures::InternalAddRef()
{
	_ASSERTE(m_dwRef != -1L);
	Lock();

long l = CComObjectRoot::InternalAddRef();

	if (m_dwRef == FTS_EXTERNAL_THRESHOLD+1) {
		Unlock();
		FinalExternalConstruct();
	} else 
		Unlock();
	return l;
}

ULONG CGeoFeatures::InternalRelease()
{
	Lock();

long l = CComObjectRoot::InternalRelease();

	if (m_dwRef == FTS_EXTERNAL_THRESHOLD) {
		Unlock();
		FinalExternalRelease();
	} else 
		Unlock();
	return l;
}

HRESULT CGeoFeatures::FinalExternalConstruct (void)
{
	ADDREF(m_pUnk);
	ADDREF_CAST(_DApplication, m_pApp);
	ADDREF_CAST(_DDocument, m_pDoc);
	return S_OK;
}

void CGeoFeatures::FinalExternalRelease (void)
{
	RELEASE_NONULL(m_pUnk);						// Parent wieder loslassen
	RELEASE_CAST(_DApplication, m_pApp);	// Applikation wieder loslassen
	RELEASE_CAST(_DDocument, m_pDoc);		// Dokument wieder loslassen
}

