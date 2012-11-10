// Eine ObjektKlasse (Controlling Unknown) ------------------------------------
// File: CLASS.CXX

#include "precomp.hxx"

#include "oleautor.h"

#include <dirisole.h>
#include <xtensnn.h>

#include "ftcltree.hxx"
#include "class.hxx"		// CClass

#if defined(_DEBUG) && defined(WIN32)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#if _TRiAS_VER >= 0x0300
using std::bad_alloc;
#endif // _TRiAS_VER >= 0x0300

///////////////////////////////////////////////////////////////////////////////
// zugehörige CriticalSection
//CComGlobalsThreadModel::AutoCriticalSection CClass::m_cs;

// Das eigentliche DocumentsObject --------------------------------------------
CClass::CClass (void)
	: m_fValid(false)
{
	CONSTRUCT_TRACE(CClass);

	m_pUnk = NULL;
	m_pApp = NULL;
	m_pDoc = NULL;

	m_pFeatClsTree = NULL;
	m_pFeatObjTree = NULL;

	m_lIdent = INVALID_IDENT;
	m_pName = NULL;		// Kurz- und LangText werden 
	m_pFullName = NULL;	// erst bei Bedarf geladen
}

bool CClass::FInit (
	LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc, 
	GEOCLASSMODE rgMode, ULONG lIdent, LPCSTR pcSrc)
{
	if (pUnk == NULL || pApp == NULL || pDoc == NULL) return FALSE;

	m_lIdent = lIdent;

// create class, if applicable
	switch (rgMode) {
	case GEOCLASSMODE_Get:
		{
		char *pName = GetName (false);

			if (m_lIdent == INVALID_IDENT || NULL == pName || '\0' == pName[0])
				return false;	// kein Ident oder existiert noch nicht
		}
		break;
		
	case GEOCLASSMODE_Add:
		{
		HPROJECT hPrCtx = HACTCONNECTION;

			if (NULL != pcSrc && '\0' != pcSrc[0]) {
			// ZielDatenquelle ist gegeben
			HPROJECT hPrDest = DEX_GetDataSourceHandleFromShortName(pcSrc);
			
				if (HACTCONNECTION == hPrDest) {
					SetLastError (E_UNEXPECTED);
					return false;		// Name gegeben, aber keine entsprechende Datenquelle gefunden
				}
			} else {
				hPrCtx = pDoc -> GetCtxDataSource();
				if (INVALID_IDENT != lIdent && HACTCONNECTION == hPrCtx)
					hPrCtx = DEX_GetObjectsProject(lIdent);

				ASSERT(HACTCONNECTION != hPrCtx);
			}

			if (lIdent == INVALID_IDENT)
				m_lIdent = DEX_GetUniqueICodeEx (hPrCtx);
		
		char *pName = GetName (false, hPrCtx);

			if (NULL != pName && 0 != strlen(pName)) 
				return false;						// existiert bereits

			RefreshNames();

		string strName (GetName (true, hPrCtx));		// kopieren !

			if (!SetName (strName.c_str(), true, true, hPrCtx))	// jetzt wirklich initialisieren
				return false;						// E_OUTOFMEMORY
		}
		break;
		
	case GEOCLASSMODE_Replace:
	case GEOCLASSMODE_Remove:
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
	m_pFeatClsTree = CFeatClsTree::CreateInstance (m_pApp, m_pDoc, this);
	if (m_pFeatClsTree == NULL) return false;

// init GeoObjectFeatures Tree 
	m_pFeatObjTree = CFeatObjTree::CreateInstance (m_pApp, m_pDoc, (DGeoClass *)this);
	if (m_pFeatObjTree == NULL) return false;

	return true;
}

bool CClass::FInit (
	LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc,
	GEOCLASSMODE rgMode, LPCSTR bName, LPCSTR pcSrc)
{
	if (pUnk == NULL || pApp == NULL || pDoc == NULL) return FALSE;

HPROJECT hPrCtx = pDoc -> GetCtxDataSource();

	if (NULL == hPrCtx)
		hPrCtx = DEX_GetDataSourceHandle();

	if (NULL != pcSrc && '\0' != pcSrc) {
	// ZielDatenquelle ist gegeben
	HPROJECT hPrDest = DEX_GetDataSourceHandleFromShortName(pcSrc);
	
		if (HACTCONNECTION != hPrDest)
			hPrCtx = hPrDest;
	}

	ASSERT(HACTCONNECTION != hPrCtx);
	switch (rgMode) {
	case GEOCLASSMODE_Get:
		{
		// TRiAS nur im Fall eines OKS nach dem Ident fragen
		HRESULT hr = E_INVALIDARG;
		bool fNameIsOKS = false;

			if (NULL != bName && !strncmp(bName, OKS_SCOPE_BEGIN, OKS_SCOPE_BEGIN_LEN))
				hr = IdentFromClassX (hPrCtx, bName, &m_lIdent);

			if (S_OK != hr) {
			// bName ist kein existierender OKS
				if (hr != E_INVALIDARG)
					return false;
	
			// bName ist kein OKS sondern der KurzText einer Objektklasse
				m_lIdent = DEX_GetIdentFromClassNameEx (hPrCtx, bName);
			} else 
				fNameIsOKS = true;

			if (m_lIdent == INVALID_IDENT)
				return false;		// kein Ident

			if (!fNameIsOKS && !SetName (bName, false, true)) 
				return false;
	
		char *pName = GetName (false, hPrCtx);

			if (NULL == pName || '\0' == pName[0])
				return false;		// Ident nicht definiert
		}
		break;
		
	case GEOCLASSMODE_Add:
// optimized: do not look for existent class
//		if (m_lIdent != INVALID_IDENT)
//			return false;		// if exists --> error
		{
		HRESULT hr = E_INVALIDARG;

			if (NULL != bName && !strncmp(bName, OKS_SCOPE_BEGIN, OKS_SCOPE_BEGIN_LEN))
				hr = IdentFromClassX (hPrCtx, bName, &m_lIdent, true);

			if (FAILED(hr) && E_INVALIDARG != hr)
				return false;	// Fehler und nicht OKS
		
			if (E_INVALIDARG == hr) {
			// Text ist kein OKS sondern Kurztext, wiederfinden des Idents
				m_lIdent = DEX_GetIdentFromClassNameEx (hPrCtx, bName);
				if (INVALID_IDENT != m_lIdent) 
					return false;		// darf noch nicht existieren

//				m_lIdent = DEX_GetUniqueICode();		// neuen Ident generieren
				m_lIdent = DEX_GetUniqueICodeEx(hPrCtx);		// neuen Ident generieren

		// neuer Objektklassenschlüssel, ab V3.00 in DEX_GetUniqueICode enthalten
//			MODOBJCLASSCODE MOCC;
//			char cbBuffer[64];
//
//				ultoa (m_lIdent, cbBuffer, DEX_GetIdBase());
//				INITSTRUCT(MOCC, MODOBJCLASSCODE);
//				MOCC.ulIdent = m_lIdent;
//				MOCC.pcClass = cbBuffer;
//				MOCC.fOverWrite = true;
//				hr = DEX_ModObjectClassCode(MOCC);
//				if (FAILED(hr) && GetScode(hr) != E_ACCESSDENIED)
//					return false;						// Fehler und nicht bereits vorhanden

				ASSERT(INVALID_IDENT != m_lIdent);
				if (!SetName (bName, true, true, hPrCtx)) 
					return false;	// E_OUTOFMEMORY
			} 

		// den Kurztext auf jeden Fall sicherstellen (wird für den Baum benötigt)
		char *pName = GetName (false, hPrCtx);

			if (NULL == pName || '\0' == pName[0])
				return false;		// Ident nicht definiert
		}
		break;
		
	case GEOCLASSMODE_Replace:
	case GEOCLASSMODE_Remove:
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
	m_pFeatClsTree = CFeatClsTree::CreateInstance (m_pApp, m_pDoc, this);
	if (m_pFeatClsTree == NULL) return false;

// init GeoObjectFeatures Tree 
	m_pFeatObjTree = CFeatObjTree::CreateInstance (m_pApp, m_pDoc, this);
	if (m_pFeatObjTree == NULL) return false;

	return true;
}

CClass::~CClass (void)
{
	DESTRUCT_TRACE(CClass);

//	RELEASE (m_pUnk);						// Parent wieder loslassen
//	RELEASE_CAST(_IApplication, m_pApp);	// Applikation wieder loslassen
//	RELEASE_CAST(_IDocument, m_pDoc);		// Document wieder loslassen

	DELETE_OBJ(m_pFeatClsTree);
	DELETE_OBJ(m_pFeatObjTree);

	DELETE_OBJ(m_pName);	
	DELETE_OBJ(m_pFullName);
}

// Funktionen werden gerufen, wenn externe Locks entstehen bzw.
// verschwinden
ULONG CClass::InternalAddRef()
{
	_ASSERTE(m_dwRef != -1L);
	Lock();

long l = CComObjectRoot::InternalAddRef();

	if (m_dwRef == CLASS_EXTERNAL_THRESHOLD+1) {
		Unlock();
		FinalExternalConstruct();
	} else 
		Unlock();
	return l;
}

ULONG CClass::InternalRelease()
{
	Lock();

long l = CComObjectRoot::InternalRelease();

	if (m_dwRef == CLASS_EXTERNAL_THRESHOLD) {
		Unlock();
		FinalExternalRelease();
	} else 
		Unlock();
	return l;
}

HRESULT CClass::FinalExternalConstruct (void)
{
	ADDREF(m_pUnk);
	ADDREF_CAST(_DApplication, m_pApp);
	ADDREF_CAST(_DDocument, m_pDoc);
	return S_OK;
}

void CClass::FinalExternalRelease (void)
{
	RELEASE_NONULL(m_pUnk);					// Parent wieder loslassen
	RELEASE_CAST(_DApplication, m_pApp);	// Applikation wieder loslassen
	RELEASE_CAST(_DDocument, m_pDoc);		// Document wieder loslassen
}

CClass *CClass::CreateInstance (
	LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc, 
	ULONG lIdent, GEOCLASSMODE rgMode, LPCSTR pcSrc)
{
CComObject<CClass> *pClass = NULL;

	try {
	// Create an instance of CClass.  Exit if an error occurs.
	HRESULT hr = CComObject<CClass>::CreateInstance (&pClass);

		if (FAILED(hr)) _com_issue_error(hr);
		if (!pClass -> FInit (pUnk, pApp, pDoc, rgMode, lIdent, pcSrc)) 
			_com_issue_error(E_FAIL);

		pClass -> AddRef();	// fertig initialisiert
	
	} catch (_com_error&) {
		DELETE_OBJ (pClass);
		return NULL;
	}

// If execution has reached this point, then no errors have occurred.
// Save the standard dispatch item and return the new instance.
	pClass -> Validate();
	return pClass;
}


CClass *CClass::CreateInstance (
	LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc, 
	LPCSTR bName, GEOCLASSMODE rgMode, LPCSTR pcSrc)
{
CComObject<CClass> *pClass = NULL;

	try {
	// Create an instance of CClass.  Exit if an error occurs.
	HRESULT hr = CComObject<CClass>::CreateInstance (&pClass);

		if (FAILED(hr)) _com_issue_error(hr);
		if (!pClass -> FInit (pUnk, pApp, pDoc, rgMode, bName, pcSrc)) 
			_com_issue_error(E_FAIL);
	
		pClass -> AddRef();	// fertig initialisiert
	
	} catch (_com_error&) {
		DELETE_OBJ (pClass);
		return NULL;
	}

// If execution has reached this point, then no errors have occurred.
// Save the standard dispatch item and return the new instance.
	pClass -> Validate();
	return pClass;
}

// Diverse ZugriffsFunktionen -------------------------------------------------
void CClass::RefreshNames (void)
{
	DELETE_OBJ(m_pName);
	DELETE_OBJ(m_pFullName);
}

char *CClass::GetName (bool fInitDefault, HPROJECT hPr)
{
	if (m_pName == NULL) { 		// noch nicht eingelesen
	// erstmaliges einlesen des IdentKurzTextes
		try {
			m_pName = new char [KTEXTLEN +1];
		} catch (bad_alloc) {
			return NULL;
		}

	ErrInstall EI (WC_NOIDENT);
	PBDDATA pbdData;

		INITSTRUCT (pbdData, PBDDATA);
		pbdData.pbdTyp = 'i';
		pbdData.pbdCode = m_lIdent;
		pbdData.pbdKText = m_pName;	// gesucht
		pbdData.pbdLText = NULL;
		pbdData.pbdKTextLen = KTEXTLEN;
		pbdData.pbdLTextLen = 0;
	
	// PBD-Info holen
		*m_pName = '\0';

	ErrCode RC = DEX_GetPBDDataEx (hPr, pbdData);

		if (EC_OKAY == RC || WC_RETURN == RC) {
			if (pbdData.pbdKTextLen > 0) 
				m_pName[KTEXTLEN] = '\0';
		}

#if _TRiAS_VER >= 0x0300
		if (fInitDefault && 0 == strlen(m_pName)) {
			DELETE_OBJ(m_pName);

		// DefaultNamen setzen
			TRY {
			CString strUnk; strUnk.LoadString (IDS_DEFAULTCLASSNAME);
			CString strId;

				strId.Format (strUnk, m_lIdent);
				try {
					m_pName = new char [strlen(strId)+1];
				} catch (bad_alloc) {
					AfxThrowMemoryException();
				}
				strcpy (m_pName, strId);
			
			} CATCH (CMemoryException, e) {
				return NULL;
			} END_CATCH;
		}
#endif // _TRiAS_VER >= 0x0300
	}	
	return m_pName;
}

// Setzen/löschen eines neuen KurzTextes --------------------------------------
bool CClass::SetName (const char *pName, bool fCreate, bool fIgnoreValid, HPROJECT hPr)
{
	if (!fIgnoreValid && !m_fValid) return false;

// als erstes alten KurzText freigeben
	DELETE_OBJ(m_pName);
		
// neuen KurzText kopieren
	if (pName) {
		try {
			m_pName = new char [strlen(pName)+1];
			strcpy (m_pName, pName);
		} catch (bad_alloc) {
			return NULL;
		}
	}
	
	if (NULL == m_pFullName) 
		GetFullName (hPr);

	if (fCreate) {
	ErrInstall EI (WC_NOIDENT);
	PBDDATA pbdData;

		INITSTRUCT (pbdData, PBDDATA);
		pbdData.pbdTyp = 'i';
		pbdData.pbdCode = m_lIdent;
		pbdData.pbdKText = m_pName;
		pbdData.pbdLText = m_pFullName;
		pbdData.pbdKTextLen = KTEXTLEN;
		pbdData.pbdLTextLen = LTEXTLEN;
	
	// PBD-Info setzen/löschen
	ErrCode RC = DEX_ModPBDDataEx (hPr, pbdData);

		if (EC_OKAY != RC && WC_RETURN != RC) 
			return false;
		m_lIdent = pbdData.pbdCode;		// kann sich geändert haben 

		DEXN_PBDIdentChanged (m_lIdent);
	}
	return true;
}

char *CClass::GetFullName (HPROJECT hPr)
{
	if (!m_fValid) return NULL;

	if (m_pFullName == NULL) { 		// noch nicht eingelesen
	// erstmaliges einlesen des IdentKurzTextes
		try {
			m_pFullName = new char [LTEXTLEN +1];
		} catch (bad_alloc) {
			return NULL;
		}
						
	ErrInstall EI (WC_NOIDENT);
	PBDDATA pbdData;
	
		INITSTRUCT (pbdData, PBDDATA);
		pbdData.pbdTyp = 'i';
		pbdData.pbdCode = m_lIdent;
		pbdData.pbdKText = NULL;
		pbdData.pbdLText = m_pFullName;		// gesucht
		pbdData.pbdKTextLen = 0;
		pbdData.pbdLTextLen = LTEXTLEN;
	
	// PBD-Info holen
		if (m_pFullName) *m_pFullName = '\0';
		if (DEX_GetPBDDataEx (hPr, pbdData) == EC_OKAY) {
			if (pbdData.pbdKTextLen > 0) 
				m_pFullName[LTEXTLEN] = '\0';
		}
	}	

return m_pFullName;
}


// Setzen/löschen eines neuen KurzTextes --------------------------------------
void CClass::SetFullName (const char *pFullName)
{
// als erstes alten LangText freigeben
	DELETE_OBJ(m_pFullName);
		
// neuen KurzText kopieren
	if (pFullName) {
		m_pFullName = new char [strlen(pFullName)+1];
		if (m_pFullName) strcpy (m_pFullName, pFullName);
	}
	if (m_pName == NULL) 
		GetName (true);

	{
	ErrInstall EI (WC_NOIDENT);
	PBDDATA pbdData;
	
		INITSTRUCT (pbdData, PBDDATA);
		pbdData.pbdTyp = 'i';
		pbdData.pbdCode = m_lIdent;
		pbdData.pbdKText = m_pName;
		pbdData.pbdLText = m_pFullName;
		pbdData.pbdKTextLen = KTEXTLEN;
		pbdData.pbdLTextLen = LTEXTLEN;
	
	// PBD-Info setzen/löschen
		DEX_ModPBDData (pbdData);
		DEXN_PBDIdentChanged (m_lIdent);
	}
}

// remove object physically ---------------------------------------------------
bool CClass::Remove (void)
		{
	if (!m_fValid) return false;
	
bool fResult = DEX_DeleteAllIdentObjects (m_lIdent);

	Invalidate();
	return fResult;
}

void CClass::Invalidate (void) 
{ 
	DELETE_OBJ (m_pFeatClsTree);
	DELETE_OBJ (m_pFeatObjTree);
	m_fValid = false; 
}

