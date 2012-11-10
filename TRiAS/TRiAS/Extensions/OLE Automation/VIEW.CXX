// Eine View (Controlling Unknown) ------------------------------------
// File: VIEW.CXX

#include "precomp.hxx"

#include <dirisole.h>

#include "obj.hxx"			// CGeoObject
#include "class.hxx"		// CClass
#include "view.hxx"			// CGeoView

#include "ftvwtree.hxx"

#if defined(_DEBUG) && defined(WIN32)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

///////////////////////////////////////////////////////////////////////////////
// zugehörige CriticalSection
//CComGlobalsThreadModel::AutoCriticalSection CGeoView::m_cs;

///////////////////////////////////////////////////////////////////////////////
// Das eigentliche ViewObject 
CGeoView::CGeoView (void)
	: m_fValid(false)
{
	CONSTRUCT_TRACE(CGeoView);
	
	m_pUnk = NULL;
	m_pApp = NULL;
	m_pDoc = NULL;

	m_pFeatViewTree = NULL;
	m_pName = NULL;		// View NameText werden 
}


BOOL CGeoView::FInit (LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc, 
	VIEWMODE rgMode, LPCSTR bName)
{
	if (pUnk == NULL || pApp == NULL || pDoc == NULL) return FALSE;
	
// Copy View name
	if (bName) {
		m_pName = new char [strlen(bName)+1];
		if (m_pName == NULL) 
			return false;
		strcpy (m_pName, bName);
	} 
	switch (rgMode) {
	case VIEWMODE_Get:		// get default
		if (bName == NULL || !DEX_ProjectHasView(bName)) return false;
		break;
			
	case VIEWMODE_Add:		// create new, Error, if exists
		if (DEX_CreateView (bName) != CVCreated)
			return false;
		break;
			
	case VIEWMODE_Replace:		// replace, error, if not exists
		if (DEX_CreateViewOpt (bName) != CVCreated)
			return false;
		break;

	case  VIEWMODE_Remove:		// remove item 
	default:
		return false;
	}

// Parent festhalten
	m_pUnk = pUnk;
//	ADDREF (m_pUnk);
	
// Applikation festhalten
	m_pApp = pApp;
//	ADDREF_CAST(_DApplication, m_pApp);

// Document festhalten
	m_pDoc = pDoc;
//	ADDREF_CAST(_DDocument, m_pDoc);
	
// init GeoFeatures Tree 
	m_pFeatViewTree = CFeatViewTree::CreateInstance (m_pApp, m_pDoc, this);
	if (m_pFeatViewTree == NULL) return false;

return TRUE;
}

CGeoView::~CGeoView (void)
{
	DESTRUCT_TRACE(CGeoView);
	
//	RELEASE(m_pUnk);	// Parent wieder loslassen
//	RELEASE_CAST(_DApplication, m_pApp);	// Applikation wieder loslassen
//	RELEASE_CAST(_DDocument, m_pDoc);		// Document wieder loslassen

	DELETE_OBJ(m_pFeatViewTree);
	DELETE_OBJ(m_pName);	
}

CGeoView *CGeoView::CreateInstance (LPUNKNOWN pUnk, 
									  CTriasApp *pApp, 
									  CGeoDoc *pDoc, 
				      				  LPCSTR bName, 
				      				  VIEWMODE rgMode)
{
CComObject<CGeoView> *pView = NULL;

	try {
	// Create an instance of CGeoView.  Exit if an error occurs.
	HRESULT hr = CComObject<CGeoView>::CreateInstance(&pView);

		if (FAILED(hr)) _com_issue_error(hr);
		if (!pView -> FInit (pUnk, pApp, pDoc, rgMode, bName)) 
			_com_issue_error(E_FAIL);

		pView -> AddRef();	// fertig initialisiert

	} catch (_com_error&) {
		DELETE_OBJ (pView);
		return NULL;
	}
	
// If execution has reached this point, then no errors have occurred.
	pView -> Validate();
	return pView;
}

// Diverse ZugriffsFunktionen -------------------------------------------------
char *CGeoView::GetName (bool fForce)
{
	if (!fForce && !m_fValid) 
		return NULL;
	return m_pName;
 }

// Setzen/löschen eines neuen Textes --------------------------------------
bool CGeoView::SetName (const char *pName, bool fIgnoreValid)
{
	if ((!fIgnoreValid && !m_fValid) || pName == NULL) return false;
	
RENAMEVIEW RV;

	RV.m_pOldName = m_pName;
	RV.m_pNewName = pName;
	if (DEX_RenameView (RV)) {
	// als erstes alten Text freigeben
		DELETE_OBJ(m_pName);
		
	// neuen Text kopieren
		m_pName = new char [strlen(pName)+1];
		if (m_pName) 
			strcpy (m_pName, pName);
		
		return true;
	}

return false;
}

// remove Class from View -----------------------------------------------------
bool CGeoView::FRemoveIdentFromView (ULONG lIdent, OBJECTTYPE rgOTypes)
{
	if (!m_fValid) return false;
	
VIEWIDENTOBJECT VIO;

	INITSTRUCT (VIO, VIEWIDENTOBJECT);
	VIO.m_pView = GetName();
	VIO.m_lIdent = lIdent;
	VIO.m_iOTyp = rgOTypes; // (OTPunkt|OTLinie|OTFlaeche|OTText);

return DEX_RemoveIdentFromView (VIO);
}

// test, if Ident is in view --------------------------------------------------
bool CGeoView::ClassIsMemberOfView (CClass *pClass, OBJECTTYPE rgOTypes)
{
	if (!m_fValid) return false;
	
VIEWIDENTOBJECT VIO;

	INITSTRUCT (VIO, VIEWIDENTOBJECT);
	VIO.m_pView = GetName();
	VIO.m_lIdent = pClass -> GetValue();
	VIO.m_iOTyp = rgOTypes; // (OTPunkt|OTLinie|OTFlaeche|OTText);
	
return DEX_ViewHasIdent (VIO);
}

// add ident to view ----------------------------------------------------------
bool CGeoView::FAddIdentToView (CClass *pClass, OBJECTTYPE rgOTypes)
{
	if (!m_fValid) return false;
	
VIEWIDENTOBJECT VIO;

	INITSTRUCT (VIO, VIEWIDENTOBJECT);
	VIO.m_pView = GetName();
	VIO.m_lIdent = pClass -> GetValue();
	VIO.m_iOTyp = rgOTypes;	// (OTPunkt|OTLinie|OTFlaeche|OTText);

return DEX_AddIdentToView (VIO);
}

// helper function ------------------------------------------------------------
bool CGeoView::ObjectIsMemberOfView (CGeoObject *pObject)
{
	if (!m_fValid) return false;
	
VIEWIDENTOBJECT VIO;

	INITSTRUCT (VIO, VIEWIDENTOBJECT);
	VIO.m_pView = GetName();
	VIO.m_lONr = pObject -> GetValue();

return DEX_ViewHasObject (VIO);
}

// remove physically ----------------------------------------------------------
bool CGeoView::Remove (void)
{
	if (!m_fValid) return false;
	
	if (DEX_DeleteSight (m_pName)) {
		Invalidate();
		return true;
	}

return false;
}

void CGeoView::Invalidate (void)
{
	DELETE_OBJ (m_pFeatViewTree);
	m_fValid = false; 
}

///////////////////////////////////////////////////////////////////////////////
// Funktionen werden gerufen, wenn externe Locks entstehen bzw.
// verschwinden
ULONG CGeoView::InternalAddRef()
{
	_ASSERTE(m_dwRef != -1L);
	Lock();

long l = CComObjectRoot::InternalAddRef();

	if (m_dwRef == VIEW_EXTERNAL_THRESHOLD+1) {
		Unlock();
		FinalExternalConstruct();
	} else 
		Unlock();
	return l;
}

ULONG CGeoView::InternalRelease()
{
	Lock();

long l = CComObjectRoot::InternalRelease();

	if (m_dwRef == VIEW_EXTERNAL_THRESHOLD) {
		Unlock();
		FinalExternalRelease();
	} else 
		Unlock();
	return l;
}

HRESULT CGeoView::FinalExternalConstruct (void)
{
	ADDREF(m_pUnk);
	ADDREF_CAST(_DApplication, m_pApp);
	ADDREF_CAST(_DDocument, m_pDoc);
	return S_OK;
}

void CGeoView::FinalExternalRelease (void)
{
	RELEASE_NONULL(m_pUnk);						// Parent wieder loslassen
	RELEASE_CAST(_DApplication, m_pApp);	// Applikation wieder loslassen
	RELEASE_CAST(_DDocument, m_pDoc);		// Dokument wieder loslassen
}

