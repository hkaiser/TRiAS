// Collection von ObjektKlassen (Controlling Unknown) -------------------------
// File: CLASSES.HXX

#include "precomp.hxx"

#include <triastlb.h>		// TypeLibrary
#include <dirisole.h>

#include "doc.hxx"
#include "clsarray.hxx"		// CIdentArray
#include "enumclss.hxx"		// CEnumClasses
#include "classes.hxx"		// CClasses

#if defined(_DEBUG) && defined(WIN32)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

///////////////////////////////////////////////////////////////////////////////
// zugehörige CriticalSection
//CComGlobalsThreadModel::AutoCriticalSection CClasses::m_cs;

// Das eigentliche DocumentsObject --------------------------------------------
CClasses::CClasses (void)
	: m_fValid(false)
{
	CONSTRUCT_TRACE(CClasses);

	m_pUnk = NULL;
	m_pApp = NULL;
	m_pDoc = NULL;
	m_pIdents = NULL;

	m_pICProc = NULL;
	m_pDCProc = NULL;
	m_dwData = 0L;
}


bool CClasses::FInit (
	LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc, 
	INITCLASSCOLLECTIONPROC pICFunc, DWORD dwData,
	DELETECLSCOLLECTIONPROC pDCProc)
{
// Parent festhalten
	if (pUnk == NULL || pApp == NULL || pDoc == NULL) return false;
	
	m_pICProc = pICFunc;
	m_pDCProc = pDCProc;
	m_dwData = dwData;

	m_pUnk = pUnk;
//	ADDREF (m_pUnk);
	
// Applikation festhalten
	m_pApp = pApp;
//	ADDREF_CAST(_IApplication, m_pApp);

// Dokument festhalten
	m_pDoc = pDoc;
//	ADDREF_CAST(_IDocument, m_pDoc);
	
// Identbaum anlegen und füllen
	return Regenerate();
}

bool CClasses::Regenerate (void)
{
	DELETE_OBJ(m_pIdents);

	m_pIdents = CEnumClasses::CreateInstance (
					m_pUnk, m_pApp, m_pDoc, m_pICProc, m_dwData);
	if (m_pIdents == NULL) return false;
	
return true;
}

CClasses::~CClasses (void)
{
	DESTRUCT_TRACE(CClasses);

//	RELEASE (m_pUnk);	// Parent wieder loslassen
//	RELEASE_CAST(_IApplication, m_pApp);	// Applikation wieder loslassen
//	RELEASE_CAST(_IDocument, m_pDoc);		// Document wieder loslassen

	DELETE_OBJ(m_pIdents);
}

CClasses *CClasses::CreateInstance (
	LPUNKNOWN  pUnk, CTriasApp *pApp, CGeoDoc   *pDoc,
	INITCLASSCOLLECTIONPROC pICFunc, DWORD dwData,
	DELETECLSCOLLECTIONPROC pDCProc)
{
CComObject<CClasses> *pClasses = NULL;

	try {
	// Create an instance of CClasses.  Exit if an error occurs.
	HRESULT hr = CComObject<CClasses>::CreateInstance (&pClasses);

		if (FAILED(hr)) _com_issue_error(hr);
		if (!pClasses -> FInit (pUnk, pApp, pDoc, pICFunc, dwData, pDCProc)) 
			_com_issue_error(E_FAIL);

		pClasses -> AddRef();	// fertig initialisiert
	
	} catch (_com_error&) {
		DELETE_OBJ (pClasses);
		return NULL;
	}
	
// If execution has reached this point, then no errors have occurred.
	pClasses -> Validate();
	return pClasses;
}

///////////////////////////////////////////////////////////////////////////////
// Funktionen werden gerufen, wenn externe Locks entstehen bzw.
// verschwinden
ULONG CClasses::InternalAddRef()
{
	_ASSERTE(m_dwRef != -1L);
	Lock();

long l = CComObjectRoot::InternalAddRef();

	if (m_dwRef == CLASSES_EXTERNAL_THRESHOLD+1) {
		Unlock();
		FinalExternalConstruct();
	} else 
		Unlock();
	return l;
}

ULONG CClasses::InternalRelease()
{
	Lock();

long l = CComObjectRoot::InternalRelease();

	if (m_dwRef == CLASSES_EXTERNAL_THRESHOLD) {
		Unlock();
		FinalExternalRelease();
	} else 
		Unlock();
	return l;
}

HRESULT CClasses::FinalExternalConstruct (void)
{
	ADDREF(m_pUnk);
	ADDREF_CAST(_DApplication, m_pApp);
	ADDREF_CAST(_DDocument, m_pDoc);
	return S_OK;
}

void CClasses::FinalExternalRelease (void)
{
	RELEASE_NONULL(m_pUnk);						// Parent wieder loslassen
	RELEASE_CAST(_DApplication, m_pApp);	// Applikation wieder loslassen
	RELEASE_CAST(_DDocument, m_pDoc);		// Dokument wieder loslassen
}

