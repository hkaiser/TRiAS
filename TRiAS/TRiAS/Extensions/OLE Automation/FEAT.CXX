// Eine Feature (Controlling Unknown) ------------------------------------
// File: FEAT.CXX

#include "precomp.hxx"

#include <dirisole.h>
#include <xtensnn.h>

#include "feat.hxx"			// CGeoFeature

#if _TRiAS_VER < 0x0300
// {6330F814-4C6B-11D2-9EC8-006008447800}
extern "C" const IID IID_IForceObjectProperty2 = 
	{0x6330f814,0x4c6b,0x11d2,{0x9e,0xc8,0x00,0x60,0x08,0x44,0x78,0x00}};
#endif // _TRiAS_VER < 0x0300

#if defined(_DEBUG) && defined(WIN32)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

///////////////////////////////////////////////////////////////////////////////
// zugehörige CriticalSection
//CComGlobalsThreadModel::AutoCriticalSection CGeoFeatureBase::m_cs;

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(ObjectProperty)
DefineSmartInterface(ObjectProperty2)
DefineSmartInterface(PropertyInfo)

///////////////////////////////////////////////////////////////////////////////
// FeatureBaseClass
CGeoFeatureBase::CGeoFeatureBase (void)
	: m_fValid(false)
{
	CONSTRUCT_TRACE(CGeoFeatureBase);

	m_pUnk = NULL;
	m_pApp = NULL;
	m_pDoc = NULL;

	m_pFCstr = NULL;	
	m_pName = NULL;	
    m_pFullName = NULL;
	m_pFeat = NULL;
}

BOOL CGeoFeatureBase::FInit (LPUNKNOWN  pUnk, CTriasApp *pApp, CGeoDoc *pDoc)
{
// Parent festhalten
	if (pUnk == NULL || pApp == NULL || pDoc == NULL) return FALSE;

	m_pUnk = pUnk;
//	ADDREF (m_pUnk);
	
// Applikation festhalten
	m_pApp = pApp;
//	ADDREF_CAST(_IApplication, m_pApp);

// Document festhalten
	m_pDoc = pDoc;
//	ADDREF_CAST(_IDocument, m_pDoc);
	
return true;
}

CGeoFeatureBase::~CGeoFeatureBase (void)
{
	DESTRUCT_TRACE(CGeoFeatureBase);
	
//	RELEASE (m_pUnk);		// Parent wieder loslassen
//	RELEASE_CAST(_IApplication, m_pApp);	// Applikation wieder loslassen
//	RELEASE_CAST(_IDocument, m_pDoc);		// Document wieder loslassen

	DELETE_OBJ(m_pFCstr);	
	DELETE_OBJ(m_pFeat);	
	DELETE_OBJ(m_pName);	
	DELETE_OBJ(m_pFullName);	
}

// View, GeoClass Features -------------------------------------------------------------
CGeoFeatureVC::CGeoFeatureVC (void)
	: m_iTType(0), m_dwTarget(0)
{
	CONSTRUCT_TRACE(CGeoFeatureVC);
	
	m_lFCd = INVALID_MCODE;
}

BOOL CGeoFeatureVC::FInit (
	LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc, 
	FEATUREMODE rgMode, LPCSTR bName, short iTType, DWORD dwTarget)
{
	if (!CGeoFeatureBase::FInit (pUnk, pApp, pDoc))
		return false;

	m_iTType = iTType;
	m_dwTarget = dwTarget;

// Copy Feature name
	if (bName) {
		m_pName = new char [strlen(bName)+1];
		if (m_pName == NULL) 
			return false;

		strcpy (m_pName, bName);
	}

	m_lFCd = DEX_GetMCodeFromFeatureName (bName);
	switch (rgMode) {
	case FEATUREMODE_Get:			// get default,   Error, if not exists
	case FEATUREMODE_Replace:		// replace  
		if (INVALID_MCODE == m_lFCd || NULL == GetFeat(true)) 
			return false;	
		break;
			
	case FEATUREMODE_Add:			// create new, 	  Error, if exists
		if (INVALID_MCODE == m_lFCd) {
			m_lFCd = DEX_GetUniqueMCode();
			if (!SetName (bName)) 
				return false;
		}
		if (NULL != GetFeat(true)) 
			return false;
		break;
			
	case  FEATUREMODE_Remove:		// remove item  (ne tut)
	default:
		return false;
	}
	return true;
}

CGeoFeatureVC::~CGeoFeatureVC (void)
{
	DESTRUCT_TRACE(CGeoFeatureVC);
}

CGeoFeatureVC *CGeoFeatureVC::CreateInstance (
	LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc,
	LPCSTR bName, short iTType, DWORD dwTarget, FEATUREMODE rgMode)
{
CComObject<CGeoFeatureVC> *pGeoFeature = NULL;

	try {
	// Create an instance of CGeoFeatureVC.  Exit if an error occurs.
	HRESULT hr = CComObject<CGeoFeatureVC>::CreateInstance(&pGeoFeature);

		if (FAILED(hr)) _com_issue_error(hr);
		if (!pGeoFeature -> FInit (pUnk, pApp, pDoc, rgMode, bName, iTType, dwTarget)) 
			_com_issue_error(E_FAIL);

		pGeoFeature -> AddRef();	// fertig initialisiert
	
	} catch (_com_error&) {
		DELETE_OBJ (pGeoFeature);
		return NULL;
	}
	
// If execution has reached this point, then no errors have occurred.
	pGeoFeature -> Validate();
	return pGeoFeature;
}

// Diverse ZugriffsFunktionen ----------------------------------------------
char *CGeoFeatureVC::GetValue (void)
{
	if (!m_fValid) return NULL;

	if (m_pFCstr == NULL) { 		// noch nicht eingelesen
	char *pBuffer = new char[64];
	
		if (NULL == pBuffer) return NULL;

		if (16 == DEX_GetMkBase()) {
			strcpy (pBuffer, "&H");
			ultoa (m_lFCd, pBuffer+2, 16);
		} else
			ultoa (m_lFCd, pBuffer, 10);

		m_pFCstr = pBuffer;
   }

return m_pFCstr;
}

char *CGeoFeatureVC::GetName (bool fForce)
{
	if (!fForce && !m_fValid) return NULL;

	if (m_pName == NULL) {  		// noch nicht eingelesen
	// erstmaliges einlesen des IdentKurzTextes
		m_pName = new char [KTEXTLEN +1];

		if (NULL == m_pName) return NULL;

	ErrInstall EI (WC_NOIDENT);
	PBDDATA pbdData;
	
		INITSTRUCT (pbdData, PBDDATA);
		pbdData.pbdTyp = 'm';
		pbdData.pbdCode = m_lFCd;
		pbdData.pbdKText = m_pName;	// gesucht
		pbdData.pbdLText = NULL;
		pbdData.pbdKTextLen = KTEXTLEN;
		pbdData.pbdLTextLen = 0;
	
	// PBD-Info holen
		*m_pName = '\0';
		
		if (DEX_GetPBDData (pbdData) == EC_OKAY) {
			if (pbdData.pbdKTextLen > 0) 
				m_pName[KTEXTLEN] = '\0';
		}
	}

return m_pName;
}

// Setzen/löschen eines neuen KurzTextes --------------------------------------
bool CGeoFeatureVC::SetName (const char *pName, bool fIgnoreValid)
{
	if ((!fIgnoreValid && !m_fValid) || pName == NULL) return true;
// als erstes alten KurzText freigeben
	DELETE_OBJ(m_pName);
		
// neuen KurzText kopieren
	if (pName) {
		m_pName = new char [strlen(pName)+1];
		if (m_pName) strcpy (m_pName, pName);
	}
	if (m_pFullName == NULL) GetFullName();

	{
	ErrInstall EI (WC_NOMERKMAL);
	PBDDATA pbdData;
	
		INITSTRUCT (pbdData, PBDDATA);
		pbdData.pbdTyp = 'm';
		pbdData.pbdCode = m_lFCd;
		pbdData.pbdKText = m_pName;	// gesucht
		pbdData.pbdLText = m_pFullName;
		pbdData.pbdKTextLen = KTEXTLEN;
		pbdData.pbdLTextLen = LTEXTLEN;
	
	// PBD-Info setzen/löschen
		if (DEX_ModPBDData (pbdData) == EC_OKAY) {
			DEXN_PBDMCodeChanged (m_lFCd);

			return true;
		}
	}
return false;
}

char *CGeoFeatureVC::GetFullName (void)
{	
	if (!m_fValid) return NULL;
	if (m_pFullName == NULL) { 		// noch nicht eingelesen

	// erstmaliges einlesen des FCdLangTextes
		m_pFullName = new char [LTEXTLEN +1];
		if (NULL == m_pFullName) return NULL;			

	ErrInstall EI (WC_NOMERKMAL);
	PBDDATA pbdData;

		INITSTRUCT (pbdData, PBDDATA);
		pbdData.pbdTyp = 'm';
		pbdData.pbdCode = m_lFCd;
		pbdData.pbdKText = NULL;
		pbdData.pbdLText = m_pFullName;	// gesucht
		pbdData.pbdKTextLen = 0;
		pbdData.pbdLTextLen = LTEXTLEN;

	// PBD-Info holen
		*m_pFullName = '\0';
		
		if (DEX_GetPBDData (pbdData) == EC_OKAY) {
			if (pbdData.pbdKTextLen > 0) 
				m_pFullName[LTEXTLEN] = '\0';
		}
	}

return m_pFullName;
}

// Setzen/löschen eines neuen LangTextes --------------------------------------
bool CGeoFeatureVC::SetFullName (const char *pFullName)
{
	if (!m_fValid) return false;
// als erstes alten LangText freigeben
	DELETE_OBJ(m_pFullName);
		
// neuen LangText kopieren
	if (pFullName) {
		m_pFullName = new char [strlen(pFullName)+1];
		if (m_pFullName) strcpy (m_pFullName, pFullName);
	}
	if (m_pName == NULL) GetName();
	
	{
	ErrInstall EI (WC_NOMERKMAL);
	PBDDATA pbdData;
	
		INITSTRUCT (pbdData, PBDDATA);
		pbdData.pbdTyp = 'm';
		pbdData.pbdCode = m_lFCd; 
		pbdData.pbdKText = m_pName;
		pbdData.pbdLText = m_pFullName;
		pbdData.pbdKTextLen = KTEXTLEN;
		pbdData.pbdLTextLen = LTEXTLEN;
	
	// PBD-Info setzen/löschen
		if (DEX_ModPBDData (pbdData) == EC_OKAY) {
			DEXN_PBDMCodeChanged (m_lFCd);

			return true;
		}
	}

return false;
}

// remove physically ----------------------------------------------------------
bool CGeoFeatureVC::Remove (void)
{
	if (!m_fValid) return false;
	
	if (SUCCEEDED(SetFeat (NULL))) {
		Invalidate();
		return true;
	}
	return false;
}

char *CGeoFeatureVC::GetFeat (bool fForce)  
{
	if (!fForce && !m_fValid) return NULL;

	if (INVALID_MCODE == m_lFCd) return NULL;

#if defined(_CACHE_FEATURES)
	if (m_pFeat == NULL) 		// noch nicht eingelesen
								// erstmaliges einlesen des ObjektFeature
#else
	DELETE_OBJ(m_pFeat);			// jedesmal neu einlesen
#endif // _CACHE_FEATURE
	{
	char *pBuffer = NULL;
	TARGETMERKMAL TM;
	
		ATLTRY(pBuffer = new char [MAXFEATLEN+1]);
		if (pBuffer != NULL) {
			INITSTRUCT (TM, TARGETMERKMAL);
			TM.lTarget = m_dwTarget; // pView, Ident
			TM.lMCode  = m_lFCd;
			TM.imaxLen = MAXFEATLEN;
			TM.pMText = pBuffer;
			TM.iTTyp = m_iTType; 	// TT_Sicht, TT_Identifikator
			if (DEX_GetTextMerkmal (TM))
				m_pFeat = pBuffer;
			else
				delete [] pBuffer;
		}
	}	
	return m_pFeat;
}

// Setzen/löschen eines neuen Feature --------------------------------------
HRESULT CGeoFeatureVC::SetFeat (const char *pFeat, BOOL)  
{	
	if (!m_fValid) return E_UNEXPECTED;

	if (INVALID_MCODE == m_lFCd) return E_FAIL;

// als erstes alten Feature freigeben
	DELETE_OBJ(m_pFeat);
		
// neuen Feature kopieren
	if (pFeat) {
		ATLTRY(m_pFeat = new char [strlen(pFeat)+1]);
		if (NULL == m_pFeat) return E_OUTOFMEMORY;

		strcpy (m_pFeat, pFeat);
	}

CNotifyWrapper WrapNotif;
ErrInstall EI (WC_NOMERKMAL);
TARGETMERKMAL TM;

	INITSTRUCT (TM, TARGETMERKMAL);
	TM.lTarget = m_dwTarget; 		// pView, Ident
	TM.lMCode  = m_lFCd;
	TM.imaxLen = m_pFeat ? strlen (m_pFeat) : NULL;
	TM.pMText = m_pFeat;			// NULL: delete feature
	TM.iTTyp = m_iTType; 			// TT_Sicht, TT_Identifikator

	return DEX_ModTextMerkmal(TM) ? S_OK : E_FAIL;
}

///////////////////////////////////////////////////////////////////////////////
// GeoObject Features 
CGeoFeatureObj::CGeoFeatureObj (void)
	: m_lONrOrIdent(INVALID_ONR)
{
	CONSTRUCT_TRACE(CGeoFeatureObj);

	m_rgProps = PROPERTYCAPS_UNKNOWN;
//	m_ObjProp = NULL;
}

BOOL CGeoFeatureObj::FInit (
	LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc, FEATUREMODE rgMode, 
	LPCSTR bName, LONG lONrOrIdent, PROPCAPS rgProps, VARIANT *pvOptData,
	IObjectProperty *pIObjProp) 
{
	if (!CGeoFeatureBase::FInit (pUnk, pApp, pDoc))
		return false;

	m_lONrOrIdent = lONrOrIdent;
	m_rgProps = (PROPERTYCAPS)rgProps;
	m_ObjProp = pIObjProp;
//	ADDREF(m_ObjProp);

bool fIsObject = (S_OK == IsGeoObject()) ? true : false;

// Copy Feature name
	if (bName) {
		m_pName = new char [strlen(bName)+1];
		if (m_pName == NULL) 
			return false;

		strcpy (m_pName, bName);
	} else 	
		return false;

HRESULT hr = NOERROR;

	if (!m_ObjProp.IsValid()) {
		if (fIsObject) 
			hr = pApp -> GetObjectProperty (bName, m_lONrOrIdent, m_ObjProp.ppi());
		else
			hr = pApp -> GetObjectPropertyIdent (bName, m_lONrOrIdent, m_ObjProp.ppi());
		if (FAILED(hr)) // S_FALSE, wenn nicht existent
			return false;
	}

	switch (rgMode & ~FEATUREMODE_GetDoNotReadValue) {
	case FEATUREMODE_Get:			// get default,   Error, if not exists
		if (S_OK == hr) {
			_ASSERTE(m_ObjProp.IsValid());
			m_ObjProp -> GetPropInfo(NULL, 0, (DWORD *)&m_rgProps);
		}
		if (S_OK != hr || (!(rgMode & FEATUREMODE_GetDoNotReadValue) && NULL == GetFeat(true) && fIsObject)) 
			return false;	
		break;

	case FEATUREMODE_Replace:		// replace now as get ???
		if (S_OK != hr || (NULL == GetFeat(true) && fIsObject)) 
			return false;	
		break;
			
	case FEATUREMODE_Add:			// create new, Error, if exists
		if (fIsObject) {
			if (S_OK != hr) {
				if (NULL != pvOptData)
					hr = pApp -> AddObjectProperty (bName, DWORD(m_rgProps), m_lONrOrIdent, *pvOptData, m_ObjProp.ppi());
				else {
				CComVariant vData;

					V_VT(&vData) = VT_ERROR;
					V_ERROR(&vData) = DISP_E_PARAMNOTFOUND;
					hr = pApp -> AddObjectProperty (bName, DWORD(m_rgProps), m_lONrOrIdent, vData, m_ObjProp.ppi());
				}
				if (FAILED(hr)) return false;
			}
		} else {
			if (S_OK != hr) {
				if (NULL != pvOptData)
					hr = pApp -> AddObjectPropertyIdent (bName, DWORD(m_rgProps), m_lONrOrIdent, *pvOptData, m_ObjProp.ppi());
				else {
				CComVariant vData;

					V_VT(&vData) = VT_ERROR;
					V_ERROR(&vData) = DISP_E_PARAMNOTFOUND;
					hr = pApp -> AddObjectPropertyIdent (bName, DWORD(m_rgProps), m_lONrOrIdent, vData, m_ObjProp.ppi());
				}
				if (FAILED(hr)) return false;
			}
		}
		if (NULL != GetFeat(true)) 
			return false;
		break;
			
	case  FEATUREMODE_Remove:		// remove item  (ne tut)
	default:
		return false;
	}

// evtl. Eigenschaften der OE vervollständigen
	if (PROPERTYCAPS_UNKNOWN == m_rgProps) {
	DWORD dwFlags = PROPERTYCAPS_UNKNOWN;
	HRESULT hr = m_ObjProp -> GetPropInfo (NULL, 0, &dwFlags);

		if (SUCCEEDED(hr))	
			m_rgProps = (PROPERTYCAPS)dwFlags;
	}
	return true;
}

CGeoFeatureObj::~CGeoFeatureObj (void)
{
	DESTRUCT_TRACE(CGeoFeatureObj);

//	RELEASE(m_ObjProp);
}


CGeoFeatureObj *CGeoFeatureObj::CreateInstance (
	LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc, LPCSTR bName,
	LONG lONr, FEATUREMODE rgMode, PROPCAPS rgProps, VARIANT *pvOptData, 
	IObjectProperty *pIObjProp)
{
CComObject<CGeoFeatureObj> *pGeoFeature = NULL;

	try {
	// Create an instance of CGeoFeatureObj.  Exit if an error occurs.
	HRESULT hr = CComObject<CGeoFeatureObj>::CreateInstance (&pGeoFeature);

		if (FAILED(hr)) _com_issue_error(hr);
		if (!pGeoFeature -> FInit (pUnk, pApp, pDoc, rgMode, bName, lONr, rgProps, pvOptData, pIObjProp)) 
			_com_issue_error(E_FAIL);
	
		pGeoFeature -> AddRef();	// fertig initialisiert
	
	} catch (_com_error&) {
		DELETE_OBJ (pGeoFeature);
		return NULL;
	}
	
// If execution has reached this point, then no errors have occurred.
	pGeoFeature -> Validate();
	return pGeoFeature;
}


// Diverse ZugriffsFunktionen ----------------------------------------------
char *CGeoFeatureObj::GetValue (void)
{
	if (!m_fValid) return NULL;

	if (m_pFCstr == NULL) { 		// noch nicht eingelesen
	char *pBuffer = new char [2];
	
		if (NULL == pBuffer) return NULL;

		strcpy (pBuffer, "0");
		m_pFCstr = pBuffer;
   }
	return m_pFCstr;
}

char *CGeoFeatureObj::GetName (bool fForce)
{
	if (!fForce && !m_fValid) return NULL;

	if (m_pName == NULL) {   		// noch nicht eingelesen
	// erstmaliges einlesen des Namens der Objekteigenschaft
		m_pName = new char [LTEXTLEN +1];
		if (NULL == m_pName) return NULL;

		ASSERT(m_ObjProp.IsValid());

	HRESULT hr = m_ObjProp -> GetPropInfo (m_pName, LTEXTLEN, NULL);

		if (FAILED(hr)) {
			DELETE_OBJ(m_pName);
			return NULL;		// error
		}
	}
	return m_pName;
}

// Setzen/löschen eines neuen KurzTextes --------------------------------------
bool CGeoFeatureObj::SetName (const char *pName, bool fIgnoreValid)
{
	if ( (!fIgnoreValid && !m_fValid) || pName == NULL ) return false;
	
HRESULT hr = NOERROR;

	if (pName) {
		ASSERT (m_ObjProp.IsValid());

	WPropertyInfo ObjSetPN;

		hr = m_ObjProp -> QueryInterface (IID_IPropertyInfo, ObjSetPN.ppv());
		if (FAILED(hr))	return false;

	// als erstes alten KurzText freigeben
		DELETE_OBJ(m_pName);
		
	// neuen KurzText kopieren
		m_pName = new char [strlen(pName)+1];
		if (NULL == m_pName) return false;

		strcpy (m_pName, pName);

		hr = ObjSetPN -> SetPropInfo (pName, m_rgProps); 
	}
	return SUCCEEDED(hr);
}

char *CGeoFeatureObj::GetFullName (void)
{	
	if (!m_fValid) return NULL;

	if (m_pFullName == NULL) { 		// noch nicht eingelesen
	// erstmaliges einlesen des Namens der Objekteigenschaft
		m_pFullName = new char [LTEXTLEN +1];
		if (NULL == m_pFullName) return NULL;

		ASSERT(m_ObjProp.IsValid());

	HRESULT hr = m_ObjProp -> HelpInfo (m_pFullName, LTEXTLEN, NULL, NULL);

		if (FAILED(hr)) {
			DELETE_OBJ(m_pFullName);
			return NULL;		// error
		}
	}
	return m_pFullName;
}

// Setzen/löschen eines neuen LangTextes --------------------------------------
bool CGeoFeatureObj::SetFullName (const char *pFullName)
{
	if (!m_fValid) return NULL;

HRESULT hr = NOERROR;

	if (pFullName) {
		ASSERT (m_ObjProp.IsValid());

	WPropertyInfo ObjSetHI;
		
		hr = m_ObjProp -> QueryInterface (IID_IPropertyInfo, ObjSetHI.ppv());
		if (FAILED(hr))	return false;

	// als erstes alten LangText freigeben
		DELETE_OBJ(m_pFullName);
		
	// neuen LangText kopieren
		m_pFullName = new char [strlen(pFullName)+1];
		if (NULL == m_pFullName) return false;
		
		strcpy (m_pFullName, pFullName);

		hr = ObjSetHI -> SetHelpInfo (pFullName, NULL, 0);
	}
	return SUCCEEDED(hr);
}

// remove physically ----------------------------------------------------------
bool CGeoFeatureObj::Remove (void)
{
	if (!m_fValid) return false;
	
	if (SUCCEEDED(SetFeat (NULL))) {
		Invalidate();
		return true;
	}

	return false;
}

char *CGeoFeatureObj::GetFeat (bool fForce)  
{
	if (!fForce && !m_fValid) return NULL;

#if defined(_CACHE_FEATURES)
	if (m_pFeat == NULL)
#else
	DELETE_OBJ(m_pFeat);		// jedesmal neu einlesen 
#endif // _CACHE_FEATURE
	{ 		// noch nicht eingelesen
	// erstmaliges einlesen des ObjektFeature
		ASSERT(m_ObjProp.IsValid());

	// ggf. Feature eines Objektes
		if (S_OK != IsGeoObject())
			return NULL;	// lediglich Beschreibungsobjekt (von Objektklasse)

#if !defined(_CACHE_FEATURES)
		if (NULL == m_pFeat) 
#endif // !defined(_CACHE_FEATURES)
		{
			ATLTRY(m_pFeat = new char [MAXFEATLEN+1]);
			if (NULL == m_pFeat) return NULL;
		}

	ULONG ulWritten = 0;
	HRESULT hr = m_ObjProp -> Eval (m_lONrOrIdent, m_pFeat, MAXFEATLEN, &ulWritten);

		if (FAILED(hr)) {	
			DELETE_OBJ(m_pFeat);
			return NULL;		// error
		}
	}	
	return m_pFeat;
}

// Setzen/löschen eines neuen Feature --------------------------------------
HRESULT CGeoFeatureObj::SetFeat (const char *pFeat, BOOL fForce)  
{	
	if (!m_fValid) return E_UNEXPECTED;

	ASSERT (m_ObjProp.IsValid());

WObjectProperty2 ObjSetP;
HRESULT hr = m_ObjProp -> QueryInterface (fForce ? IID_IForceObjectProperty2 : IID_IObjectProperty2, ObjSetP.ppv());

	if (FAILED(hr))	return hr;

	if (pFeat) {
	// als erstes alten Feature freigeben
		DELETE_OBJ(m_pFeat);
		
	// neuen Feature kopieren
		ATLTRY(m_pFeat = new char [strlen(pFeat)+1]);
		if (NULL == m_pFeat) return E_OUTOFMEMORY;
		
		strcpy (m_pFeat, pFeat);
	}

	if (S_OK == IsGeoObject())
		hr = ObjSetP -> Set (m_lONrOrIdent, pFeat);
	else
		hr = E_INVALIDARG;		// lediglich Beschreibungsobjekt (von Objektklasse)

	return hr;
}

///////////////////////////////////////////////////////////////////////////////
// Funktionen werden gerufen, wenn externe Locks entstehen bzw.
// verschwinden
ULONG CGeoFeatureBase::InternalAddRef()
{
	_ASSERTE(m_dwRef != -1L);
	Lock();

long l = CComObjectRoot::InternalAddRef();

	if (m_dwRef == FEAT_EXTERNAL_THRESHOLD+1) {
		Unlock();
		FinalExternalConstruct();
	} else 
		Unlock();
	return l;
}

ULONG CGeoFeatureBase::InternalRelease()
{
	Lock();

long l = CComObjectRoot::InternalRelease();

	if (m_dwRef == FEAT_EXTERNAL_THRESHOLD) {
		Unlock();
		FinalExternalRelease();
	} else 
		Unlock();
	return l;
}

HRESULT CGeoFeatureBase::FinalExternalConstruct (void)
{
	ADDREF(m_pUnk);
	ADDREF_CAST(_DApplication, m_pApp);
	ADDREF_CAST(_DDocument, m_pDoc);
	return S_OK;
}

void CGeoFeatureBase::FinalExternalRelease (void)
{
	RELEASE_NONULL(m_pUnk);						// Parent wieder loslassen
	RELEASE_CAST(_DApplication, m_pApp);	// Applikation wieder loslassen
	RELEASE_CAST(_DDocument, m_pDoc);		// Dokument wieder loslassen
}

