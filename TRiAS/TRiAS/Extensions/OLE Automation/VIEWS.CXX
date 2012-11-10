// Collection von Views (Controlling Unknown) -------------------------
// File: VIEWS.CXX

#include "precomp.hxx"

#include <dirisole.h>

#include "viewarry.hxx"		// CGeoViewsArray
#include "enuviews.hxx"		// CEnumViews
#include "views.hxx"		// CGeoViews

#if defined(_DEBUG) && defined(WIN32)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

///////////////////////////////////////////////////////////////////////////////
// zugehörige CriticalSection
//CComGlobalsThreadModel::AutoCriticalSection CGeoViews::m_cs;

///////////////////////////////////////////////////////////////////////////////
// Das eigentliche  Views Object ----------------------------------------------
CGeoViews::CGeoViews (void)
	: m_fValid(false)
{
	CONSTRUCT_TRACE(CGeoViews);
	
	m_pUnk = NULL;
	m_pApp = NULL;
	m_pDoc = NULL;

	m_pEnumViews = NULL;
	
	m_pICProc = NULL;
	m_pDCProc = NULL;
	m_dwData = 0L;
}

bool CGeoViews::FInit (LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc,
	INITVIEWCOLLECTIONPROC pICFunc, DWORD dwData,
	DELETEVIEWCOLLECTIONPROC pDCProc)
{
// Parent festhalten
	if (pUnk == NULL || pApp == NULL || pDoc == NULL) return FALSE;
	
	m_pICProc = pICFunc;
	m_pDCProc = pDCProc;
	m_dwData = dwData;

	m_pUnk = pUnk;
//	ADDREF (m_pUnk);
	
// Applikation festhalten
	m_pApp = pApp;
//	ADDREF_CAST(_DApplication, m_pApp);

// Projekt festhalten
	m_pDoc = pDoc;
//	ADDREF_CAST(_DDocument, m_pDoc);

// Identbaum anlegen und füllen
	return Regenerate();
}

bool CGeoViews::Regenerate (void)
{
	DELETE_OBJ(m_pEnumViews);
	m_pEnumViews = CEnumViews::CreateInstance (
		m_pUnk, m_pApp, m_pDoc, m_pICProc, m_dwData);
	if (m_pEnumViews == NULL) return false;
	
return true;
}

CGeoViews::~CGeoViews (void)
{
	DESTRUCT_TRACE(CGeoViews);
	
	DELETE_OBJ (m_pEnumViews);

//	RELEASE (m_pUnk);	// Parent wieder loslassen
//	RELEASE_CAST(_DApplication, m_pApp);	// Applikation wieder loslassen
//	RELEASE_CAST(_DDocument, m_pDoc);		// Document wieder loslassen
}


CGeoViews *CGeoViews::CreateInstance (
	LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc,
	INITVIEWCOLLECTIONPROC pICFunc, DWORD dwData,
	DELETEVIEWCOLLECTIONPROC pDCProc)
{
CComObject<CGeoViews> *pViews = NULL;

	try {
	// Create an instance of CGeoViews.  Exit if an error occurs.
	HRESULT hr = CComObject<CGeoViews>::CreateInstance (&pViews);

		if (FAILED(hr)) _com_issue_error(hr);
		if (!pViews -> FInit (pUnk, pApp, pDoc, pICFunc, dwData, pDCProc)) 
			_com_issue_error(E_FAIL);

		pViews -> AddRef();	// fertig initialisiert

	} catch (_com_error&) {
		DELETE_OBJ (pViews);
		return NULL;
	}
	
// If execution has reached this point, then no errors have occurred.
	pViews -> Validate();
	return pViews;
}

///////////////////////////////////////////////////////////////////////////////
// Funktionen werden gerufen, wenn externe Locks entstehen bzw.
// verschwinden
ULONG CGeoViews::InternalAddRef()
{
	_ASSERTE(m_dwRef != -1L);
	Lock();

long l = CComObjectRoot::InternalAddRef();

	if (m_dwRef == VIEWS_EXTERNAL_THRESHOLD+1) {
		Unlock();
		FinalExternalConstruct();
	} else 
		Unlock();
	return l;
}

ULONG CGeoViews::InternalRelease()
{
	Lock();

long l = CComObjectRoot::InternalRelease();

	if (m_dwRef == VIEWS_EXTERNAL_THRESHOLD) {
		Unlock();
		FinalExternalRelease();
	} else 
		Unlock();
	return l;
}

HRESULT CGeoViews::FinalExternalConstruct (void)
{
	ADDREF(m_pUnk);
	ADDREF_CAST(_DApplication, m_pApp);
	ADDREF_CAST(_DDocument, m_pDoc);
	return S_OK;
}

void CGeoViews::FinalExternalRelease (void)
{
	RELEASE_NONULL(m_pUnk);						// Parent wieder loslassen
	RELEASE_CAST(_DApplication, m_pApp);	// Applikation wieder loslassen
	RELEASE_CAST(_DDocument, m_pDoc);		// Dokument wieder loslassen
}

