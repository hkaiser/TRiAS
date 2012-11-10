// Collection der Objects (Controlling Unknown) ------------------
// File: OBJS.CXX

#include "precomp.hxx"

#include <triastlb.h>		// TypeLibrary
#include <dirisole.h>
#include <eonrguid.h>

#include "objarray.hxx"
#include "enumobjs.hxx"
#include "objs.hxx"

#if defined(_DEBUG) && defined(WIN32)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

///////////////////////////////////////////////////////////////////////////////
// zugehörige CriticalSection
//CComGlobalsThreadModel::AutoCriticalSection CGeoObjects::m_cs;

// Das eigentliche Object --------------------------------------------
CGeoObjects::CGeoObjects (void)
	: m_fValid(false)
{
	CONSTRUCT_TRACE(CGeoObjects);
	
	m_pUnk = NULL;
	m_pApp =NULL;
	m_pDoc = NULL;

	m_pObjs = NULL;

	m_pICProc = NULL;
	m_dwData = 0L;
	m_pDCProc = NULL;
}


bool CGeoObjects::FInit (
	LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc,
	INITOBJCOLLECTIONPROC pICFunc, DWORD dwData,
	DELETEOBJCOLLECTIONPROC pDCProc)
{
// Parent festhalten
	if (pUnk == NULL || pApp == NULL || NULL == pDoc) 
		return FALSE;
	
	m_pICProc = pICFunc;
	m_dwData = dwData;
	m_pDCProc = pDCProc;

	m_pUnk = pUnk;
//	ADDREF (m_pUnk);
	
// Applickation festhalten
	m_pApp = pApp;
//	ADDREF_CAST(_IApplication, m_pApp);

// Dokument festhalten
	m_pDoc = pDoc;
//	ADDREF_CAST(_IDocument, m_pDoc);
	
// Objektbaum anlegen und füllen
	return Regenerate();
}

bool CGeoObjects::Regenerate (void)
{
	DELETE_OBJ(m_pObjs);
	m_pObjs = CEnumGeoObjs::CreateInstance (m_pUnk, m_pApp, m_pDoc, m_pICProc, m_dwData);
	if (m_pObjs == NULL) return false;

return true;
}

CGeoObjects::~CGeoObjects (void)
{
	DESTRUCT_TRACE(CGeoObjects);
	
//	RELEASE(m_pUnk);	// Parent wieder loslassen
//	RELEASE_CAST(_IApplication, m_pApp);	// Applikation wieder loslassen
//	RELEASE_CAST(_IDocument, m_pDoc);		// Document wieder loslassen

	DELETE_OBJ(m_pObjs);
}

CGeoObjects *CGeoObjects::CreateInstance (
	LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc,
	INITOBJCOLLECTIONPROC pICFunc, DWORD dwData,
	DELETEOBJCOLLECTIONPROC pDCProc)
{
CComObject<CGeoObjects> *pGeoObjs = NULL;

	try {
	// Create an instance of CGeoObjects.  Exit if an error occurs.
	HRESULT hr = CComObject<CGeoObjects>::CreateInstance(&pGeoObjs);

		if (FAILED(hr)) _com_issue_error(hr);
		if (!pGeoObjs -> FInit (pUnk, pApp, pDoc, pICFunc, dwData, pDCProc)) 
			_com_issue_error(E_FAIL);
	
		pGeoObjs -> AddRef();	// fertig initialisiert

	} catch (_com_error&) {
		DELETE_OBJ (pGeoObjs);
		return NULL;
	}
	
// If execution has reached this point, then no errors have occurred.
	pGeoObjs -> Validate();
	return pGeoObjs;
}

// *** IQueryEnumLONG methods /////////////////////////////////////////////////
STDMETHODIMP CGeoObjects::QueryEnumLONG (IEnumLONG **ppIEnum)
{
	return m_pObjs -> m_pGeoObjArray -> GetEnumLONG (ppIEnum);
}

///////////////////////////////////////////////////////////////////////////////
// Funktionen werden gerufen, wenn externe Locks entstehen bzw.
// verschwinden
ULONG CGeoObjects::InternalAddRef()
{
	_ASSERTE(m_dwRef != -1L);
	Lock();

long l = CComObjectRoot::InternalAddRef();

	if (m_dwRef == OBJS_EXTERNAL_THRESHOLD+1) {
		Unlock();
		FinalExternalConstruct();
	} else 
		Unlock();
	return l;
}

ULONG CGeoObjects::InternalRelease()
{
	Lock();

long l = CComObjectRoot::InternalRelease();

	if (m_dwRef == OBJS_EXTERNAL_THRESHOLD) {
		Unlock();
		FinalExternalRelease();
	} else 
		Unlock();
	return l;
}

HRESULT CGeoObjects::FinalExternalConstruct (void)
{
	ADDREF(m_pUnk);
	ADDREF_CAST(_DApplication, m_pApp);
	ADDREF_CAST(_DDocument, m_pDoc);
	return S_OK;
}

void CGeoObjects::FinalExternalRelease (void)
{
	RELEASE_NONULL(m_pUnk);						// Parent wieder loslassen
	RELEASE_CAST(_DApplication, m_pApp);	// Applikation wieder loslassen
	RELEASE_CAST(_DDocument, m_pDoc);		// Dokument wieder loslassen
}

