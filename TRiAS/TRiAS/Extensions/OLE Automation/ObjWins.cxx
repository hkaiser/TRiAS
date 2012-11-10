// Collection der Object Windows (Controlling Unknown) ------------------
// File: OBJWINS.CXX

#include "precomp.hxx"

#include <dirisole.h>

#include "obwarray.hxx"
#include "enumobws.hxx"
#include "objwins.hxx"

#if defined(_DEBUG) && defined(WIN32)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

///////////////////////////////////////////////////////////////////////////////
// zugehörige CriticalSection
//CComGlobalsThreadModel::AutoCriticalSection CGeoObjectWins::m_cs;

///////////////////////////////////////////////////////////////////////////////
// Das eigentliche Object Window 
CGeoObjectWins::CGeoObjectWins (void)
	: m_fValid(false)
{
	CONSTRUCT_TRACE(CGeoObjectWins);
	
	m_pUnk = NULL;
	m_pApp = NULL;
	m_pDoc = NULL;
	
	m_pEnumOWins = NULL;

	m_pICProc = NULL;
	m_dwData = 0L;
	m_pDCProc = NULL;
}


bool CGeoObjectWins::FInit (
	LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc,
	INITOBJWINCOLLECTIONPROC   pICFunc, DWORD   dwData,
	DELETEOBJWINCOLLECTIONPROC pDCProc)
{
// Parent festhalten
	if (pUnk == NULL || pApp == NULL || NULL == pDoc) 
		return false;
	
	m_pICProc = pICFunc;
	m_dwData  = dwData;
	m_pDCProc = pDCProc;

	m_pUnk = pUnk;
//	ADDREF (m_pUnk);
	
// Applickation festhalten
	m_pApp = pApp;
//	ADDREF_CAST(_IApplication, m_pApp);

// Dokument festhalten
	m_pDoc = pDoc;
//	ADDREF_CAST(_IDocument, m_pDoc);
	
// OW baum anlegen und füllen
	return Regenerate();
}

bool CGeoObjectWins::Regenerate (void)
{
	DELETE_OBJ(m_pEnumOWins);
	m_pEnumOWins = CEnumGeoObjWins::CreateInstance (
		m_pUnk, m_pApp, m_pDoc, m_pICProc, m_dwData);
	if (NULL == m_pEnumOWins) return false;

return true;
}


CGeoObjectWins::~CGeoObjectWins (void)
{
	DESTRUCT_TRACE(CGeoObjectWins);
	
//	RELEASE(m_pUnk);		// Parent wieder loslassen
//	RELEASE_CAST(_IApplication, m_pApp);	// Applikation wieder loslassen
//	RELEASE_CAST(_IDocument, m_pDoc);		// Document wieder loslassen

	DELETE_OBJ(m_pEnumOWins);
}


CGeoObjectWins *CGeoObjectWins::CreateInstance (
	LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc,
	INITOBJWINCOLLECTIONPROC pICFunc, DWORD dwData,
	DELETEOBJWINCOLLECTIONPROC pDCProc)
{
CComObject<CGeoObjectWins> *pGeoObjWins = NULL;

	try {
	// Create an instance of CGeoObjectWins.  Exit if an error occurs.
	HRESULT hr = CComObject<CGeoObjectWins>::CreateInstance (&pGeoObjWins);

		if (FAILED(hr)) _com_issue_error(hr);
		if (!pGeoObjWins -> FInit (pUnk, pApp, pDoc, pICFunc, dwData, pDCProc)) 
			_com_issue_error(E_FAIL);

		pGeoObjWins -> AddRef();	// fertig initialisiert

	} catch (_com_error&) {
		DELETE_OBJ (pGeoObjWins);
		return NULL;
	}
	
// If execution has reached this point, then no errors have occurred.
	pGeoObjWins -> Validate();
	return pGeoObjWins;
}


///////////////////////////////////////////////////////////////////////////////
// Funktionen werden gerufen, wenn externe Locks entstehen bzw.
// verschwinden
ULONG CGeoObjectWins::InternalAddRef()
{
	_ASSERTE(m_dwRef != -1L);
	Lock();

long l = CComObjectRoot::InternalAddRef();

	if (m_dwRef == OBJWINS_EXTERNAL_THRESHOLD+1) {
		Unlock();
		FinalExternalConstruct();
	} else 
		Unlock();
	return l;
}

ULONG CGeoObjectWins::InternalRelease()
{
	Lock();

long l = CComObjectRoot::InternalRelease();

	if (m_dwRef == OBJWINS_EXTERNAL_THRESHOLD) {
		Unlock();
		FinalExternalRelease();
	} else 
		Unlock();
	return l;
}

HRESULT CGeoObjectWins::FinalExternalConstruct (void)
{
	ADDREF(m_pUnk);
	ADDREF_CAST(_DApplication, m_pApp);
	ADDREF_CAST(_DDocument, m_pDoc);
	return S_OK;
}

void CGeoObjectWins::FinalExternalRelease (void)
{
	RELEASE_NONULL(m_pUnk);						// Parent wieder loslassen
	RELEASE_CAST(_DApplication, m_pApp);	// Applikation wieder loslassen
	RELEASE_CAST(_DDocument, m_pDoc);		// Dokument wieder loslassen
}

