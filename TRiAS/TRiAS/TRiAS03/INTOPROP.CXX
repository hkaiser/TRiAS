// Interne Objekteigenschaften ------------------------------------------------
// File: INTOPROP.HXX
	
#include "trias03p.hxx"

#include "trias03.h"		// Resourcen
#include "Strings.h"

#include <containr.hxx>
#include <ixtensn.hxx>
#include <ioprpini.hxx>

#include <Com/PropertyHelper.h>

#include <xtsnguid.h>
#include <oprpguid.h>

#include <errinst.hxx>
#include <funcs03.h>

#include "intoprop.hxx"
#include "queryfld.hxx"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Problem mit HUGE-Speicherbereichen im WIN16 behandeln ----------------------
#if defined(WIN32)

#define GUID_CCH		39

inline size_t hstrlen (const char *pStr) { return strlen (pStr); }

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(EnumObjectsByNumber);		// WEnumObjectsByNumber
#if !defined(_FORCE_LEGACY_CODE) && _TRiAS_VER >= 0x0300
DefineSmartInterface(TRiASObjectHandleMap);		// WTRiASObjectHandleMap
DefineSmartInterface(TRiASObjects);				// WTRiASObjects
DefineSmartInterface(TRiASObject);				// WTRiASObject
DefineSmartInterface(Dispatch);					// WDispatch
DefineSmartInterface(TRiASDatabase);			// WTRiASDatabase
DefineSmartInterface(TRiASConnection);			// WTRiASConnection
DefineSmartInterface(ObjectProperty);			// WObjectProperty
DefineSmartInterface(ObjectProperty2);			// WObjectProperty2
DefineSmartInterface(ObjectProperty3);			// WObjectProperty3
DefineSmartInterface(DelegatorFactory);			// WDelegatorFactory
DefineSmartInterface(TRiASLockFeatureEx);		// WTRiASLockFeatureEx
DefineSmartInterface(PropertyInfo2);			// WPropertyInfo2
#endif // !_FORCE_LEGACY_CODE && _TRiAS_VER >= 0x0300

#else 

static char s_cbOPBuffer[1024];
#pragma function (memcpy)		// nicht inline generieren
long hstrlen (const char *pStr);

#endif // WIN32

///////////////////////////////////////////////////////////////////////////////
// Funktion soll gerufen werden, wenn Objekt zerlegt wird
void PASCAL ObjectDestroyed (void);

// Basisklasse für alle TRiAS-internen Objekteigenschaften --------------------
CBaseObjectProperty::CBaseObjectProperty (LPCSTR pcName, ResID resHelp, bool fRO)
		     : m_resHelpID(resHelp), m_fReadOnly(fRO), m_pfnDestroy(ObjectDestroyed)
{
	m_ulCnt = 0;
	m_fIsDirty = false;
	if (pcName) 
		m_strName = pcName;
}

CBaseObjectProperty::~CBaseObjectProperty (void)
{
	if (m_pfnDestroy) m_pfnDestroy();	// das Ende vom Lied
}

///////////////////////////////////////////////////////////////////////////////
// Kopieren dieser Eigenschaft (für Clone)
bool CBaseObjectProperty::FInit (const CBaseObjectProperty &rOP)
{
#if !defined(_FORCE_LEGACY_CODE) && _TRiAS_VER >= 0x0300
	m_Objs = rOP.m_Objs;
#endif // !defined(_FORCE_LEGACY_CODE) && _TRiAS_VER >= 0x0300
	m_fIsDirty = rOP.m_fIsDirty;
	m_resHelpID = rOP.m_resHelpID;
	m_fReadOnly = rOP.m_fReadOnly;
	m_pfnDestroy = rOP.m_pfnDestroy;

	return true;
}

// *** IObjectProperty specific functions *** ---------------------------------
STDMETHODIMP CBaseObjectProperty::GetPropInfo (
		LPSTR pBuffer, WORD wLen, DWORD *pdwData)
{
	if (NULL != pBuffer && wLen > 0) {
	unsigned int uiLen = min((unsigned int)(wLen-1), m_strName.length());

		strncpy (pBuffer, m_strName.c_str(), uiLen);
		pBuffer[uiLen] = '\0';
	}

	if (pdwData) 
		*pdwData = m_fReadOnly ? PROPCAPS_NONE : PROPCAPS_NOTREADONLY;

	return S_OK;
}

STDMETHODIMP CBaseObjectProperty::Reset (void)
{
	m_ulCnt = 0;
	return S_OK;
}

STDMETHODIMP_(ULONG) CBaseObjectProperty::Count (void)
{
	return m_ulCnt;
}

STDMETHODIMP CBaseObjectProperty::HelpInfo (LPSTR pBuffer, ULONG ulLen, 
					LPSTR pHelpFile, ULONG *pulHelpCtx)
{
	TX_ASSERT(NULL != pBuffer);
	TX_ASSERT(0 != ulLen);

ResString resHelp (m_resHelpID, _MAX_PATH);
ULONG ul = min(ulLen-1, ULONG(strlen(resHelp)));

	strncpy (pBuffer, resHelp.Addr(), ul);
	pBuffer[ul] = '\0';

	if (pHelpFile) *pHelpFile = '\0';
		if (pulHelpCtx) *pulHelpCtx = 0;

return S_OK;
}

// default: no cumulation -----------------------------------------------------
STDMETHODIMP CBaseObjectProperty::Cumulation (LPSTR pBuffer, ULONG ulLen, 
					     ULONG *pulWritten)
{
	TX_ASSERT(NULL != pBuffer);
	TX_ASSERT(0 != ulLen);

	*pBuffer = '\0';	// no cumulation here
	if (pulWritten) *pulWritten = 0;
	
return S_OK;
}

STDMETHODIMP CBaseObjectProperty::Set (LONG, LPCSTR)
{
	return E_NOTIMPL;
}

STDMETHODIMP CBaseObjectProperty::SetWithUndo (LONG, LPCSTR)
{
	return E_NOTIMPL;
}

///////////////////////////////////////////////////////////////////////////////
// *** IPersistStream members
STDMETHODIMP CBaseObjectProperty::IsDirty (void)
{
	return GetDirty() ? S_OK : S_FALSE;
}

// *** IPersistStream methods *** ---------------------------------------------
STDMETHODIMP CBaseObjectProperty::Load (IStream *pIStream)
{
	if (NULL == pIStream) return E_POINTER;

// Länge des OPropNamens einlesen
char *pT = NULL;

	try {
	ULONG ulSize = 0L;
	
		THROW_FAILED_HRESULT(pIStream -> Read (&ulSize, sizeof(ULONG), NULL));
		if (ulSize > 0) {
		// Template selbst wieder einlesen
			TX_TRY(pT = new char [ulSize+1]);
			if (NULL == pT) _com_issue_error(E_OUTOFMEMORY);

			THROW_FAILED_HRESULT(pIStream -> Read (pT, ulSize+1, NULL));
			SetName (pT);
		}
	} catch (_com_error& hr) {
		DELETE_VEC(pT);
		return _COM_ERROR(hr);
	}

	DELETE_VEC(pT);
	return S_OK;
}

STDMETHODIMP CBaseObjectProperty::Save (IStream *pIStream, BOOL fClearDirty)
{
	if (NULL == pIStream) return E_POINTER;

// Namen der Objekteigenschaft wegschreiben 
ULONG ulSize = GetNameStr().length();
HRESULT hr = pIStream -> Write (&ulSize, sizeof(ULONG), NULL);

	if (FAILED(hr)) return hr;
	
	hr = pIStream -> Write (GetName(), ulSize+1, NULL);
	if (FAILED(hr)) return hr;

	return S_OK;
}
	
STDMETHODIMP CBaseObjectProperty::GetSizeMax (ULARGE_INTEGER *pcbSize)
{
	if (NULL == pcbSize) return E_POINTER;

	pcbSize -> LowPart = sizeof(ULONG) + GetNameStr().length() +1;
	pcbSize -> HighPart = 0L;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Objekteigenschaft, die Objektnummer als String liefert 
CObjPropONr::CObjPropONr (void)
	     : CBaseObjectProperty (ResString (IDS_OBJPROPONR, 64), IDS_OBJPROPONRHELP)
{
}

STDMETHODIMP CObjPropONr::GetPropInfo (LPSTR pBuffer, WORD wLen, DWORD *pdwData)
{
HRESULT hr = CBaseObjectProperty::GetPropInfo(pBuffer, wLen, pdwData);

	if (SUCCEEDED(hr) && NULL != pdwData)
		*pdwData |= PROPCAPS_OBJPROPTYPE_INTEGER;
	return hr;
}

STDMETHODIMP CObjPropONr::Eval (LONG lONr, LPSTR pBuffer, ULONG ulLen, 
				  ULONG *pulWritten)
{
	TX_ASSERT(NULL != pBuffer);
	TX_ASSERT(0 != ulLen);

	if (ulLen > 20) {
#if defined(WIN32)
		ltoa (lONr, pBuffer, 10);
		if (pulWritten) *pulWritten = strlen(pBuffer);
#else
		ltoa (lONr, s_cbOPBuffer, 10);

	long ul = hstrlen (s_cbOPBuffer);

		memcpy (pBuffer, s_cbOPBuffer, ul+1);	// '\0' mitkopieren
		if (pulWritten) *pulWritten = ul;
#endif
		m_ulCnt++;	// Zähler der erfolgreichen Aufrufe
		return S_OK;
	}

	return E_FAIL;
}

// IPersistStreamInterface ////////////////////////////////////////////////////
// *** IPersist methods *** 
STDMETHODIMP CObjPropONr::GetClassID (CLSID *pClsID)
{
	*pClsID = GetObjectCLSID();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Objekteigenschaft, die Objektnummer als String liefert 
CObjPropGUID::CObjPropGUID (void)
	: CBaseObjectProperty (ResString (IDS_OBJPROPGUID, 64), IDS_OBJPROPGUIDHELP)
{
}

STDMETHODIMP CObjPropGUID::GetPropInfo (LPSTR pBuffer, WORD wLen, DWORD *pdwData)
{
HRESULT hr = CBaseObjectProperty::GetPropInfo(pBuffer, wLen, pdwData);

	if (SUCCEEDED(hr) && NULL != pdwData)
		*pdwData |= PROPCAPS_OBJPROPTYPE_STRING;
	return hr;
}

STDMETHODIMP CObjPropGUID::Eval (
	LONG lONr, LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten)
{
	TX_ASSERT(NULL != pBuffer);
	TX_ASSERT(0 != ulLen);

#if defined(WIN32)
	if (ulLen > GUID_CCH) {
	OBJECTGUID OUID;

		INITSTRUCT(OUID, OBJECTGUID);
		OUID.lONr = lONr;
		if (SUCCEEDED(DEX_GetObjectGuid (OUID))) {
		OLECHAR coleBuffer[GUID_CCH];
		HRESULT hr = StringFromGUID2 (OUID.guid, coleBuffer, GUID_CCH);

			if (FAILED(hr)) return hr;

			USES_CONVERSION;
			strcpy (pBuffer, OLE2A(coleBuffer));

			if (pulWritten) 
				*pulWritten = strlen(pBuffer);
			m_ulCnt++;	// Zähler der erfolgreichen Aufrufe
			return S_OK;
		}
		return E_FAIL;
	}
#endif // WIN32

	return E_FAIL;
}

// IPersistStreamInterface ////////////////////////////////////////////////////
// *** IPersist methods *** 
STDMETHODIMP CObjPropGUID::GetClassID (CLSID *pClsID)
{
	*pClsID = GetObjectCLSID();
	return S_OK;
}

// normales Wegschreiben einer Objekteigenschaft ------------------------------
STDMETHODIMP CObjPropGUID::Set (LONG lONr, LPCSTR pcBuffer)
{
	USES_CONVERSION;

GUID guid;
HRESULT hr = CLSIDFromString (A2OLE(pcBuffer), &guid);

	if (FAILED(hr)) return hr;

OBJECTGUID OUID;

	INITSTRUCT (OUID, OBJECTGUID);
	OUID.lONr = lONr;
	OUID.guid = guid;
	return DEX_SetObjectGuid (OUID);
}

int ModeFromSearchMode (SEARCHMODE rgFlags);

STDMETHODIMP CObjPropGUID::ConsiderSearch (
	BSTR bstrToMatch, SEARCHMODE rgFlags, ULONG ulCnt)
{
// Eigentlich müßte an dieser Stelle getestet werden, wieviele Objekte überhaupt 
// diese Objekteigenschaft besitzen. Diese Zahl muß mit 'ulCnt' (Anzahl der 
// zu filternden Objekte) verglichen werden, um abzuschätzen, welche Recherche-
// methode effektiver ist.
// Vorläufig werden lediglich die Methoden zur direkten Recherche empfohlen, die
// auf der Grundlage eines Key's in der Datenbasis realisierbar sind.
HRESULT hr = S_FALSE;	// nicht zu empfehlen

	if (rgFlags & SEARCHMODE_NEGATERESULT)
		return E_NOTIMPL;		// Negation wird immer hier gemacht

	switch (ModeFromSearchMode(rgFlags)) {
	case SMExactMatch:
		hr = S_OK;		// geht schnell, ist Key
		break;

	case SMInexactMatch:
	case SMSubstringMatch:
	case SMSubStringStartMatch:
	case SMRegularExpression:
	case SMSubRegularExpression:
		hr = E_NOTIMPL;	// not impl 
		break;
	}
	return hr;
}

STDMETHODIMP CObjPropGUID::SearchObjects (
	BSTR bstrToMatch, SEARCHMODE rgFlags, IEnumObjectsByNumber **ppvObj)
{
// kann Objekte nur effektiv raussuchen, wenn keine RegExpr gefordert sind
	if ((rgFlags & ~SEARCHMODE_SEARCHMODIFIERS) != SEARCHMODE_FULLMATCH)
		return E_NOTIMPL;

// lediglich NoMatchCase ist zugelassen
	if ((rgFlags & SEARCHMODE_SEARCHMODIFIERS) &&
		(rgFlags & SEARCHMODE_SEARCHMODIFIERS) != SEARCHMODE_NOMATCHCASE)
	{
		return E_NOTIMPL;
	}

	if (NULL == ppvObj) return E_POINTER;
	
	*ppvObj = NULL;
	try {
	WEnumObjectsByNumber IObjs (CLSID_EnumObjectsByNumber); // Enumerator generieren
	OBJECTGUID OUID;

		INITSTRUCT(OUID, OBJECTGUID);
		THROW_FAILED_HRESULT(CLSIDFromString (bstrToMatch, &OUID.guid));
		THROW_FAILED_HRESULT(DEX_FindObjectFromGuid(OUID));

		IObjs -> AddItem (OUID.lONr);	// immer genau ein Objekt
		*ppvObj = IObjs.detach();

	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	} 

	return S_OK;
}

#if !defined(_FORCE_LEGACY_CODE) && _TRiAS_VER >= 0x0300
STDMETHODIMP CObjPropGUID::SetPropInfo (LPCSTR pBuffer, DWORD dwFlags)
{
	return E_NOTIMPL;
}

STDMETHODIMP CObjPropGUID::SetHelpInfo (LPCSTR pBuffer, LPCSTR pHelpFile, ULONG ulHelpCtx)
{
	return E_NOTIMPL;
}

// *** IPropertyInfo2 specific functions ***
STDMETHODIMP CObjPropGUID::GetConfigData (VARIANT *pvOptData)
{
	return E_NOTIMPL;
}

STDMETHODIMP CObjPropGUID::GetConfigDataEx (INT_PTR hObjs, VARIANT *pvOptData)
{
	return E_NOTIMPL;
}

STDMETHODIMP CObjPropGUID::GetPropInfoEx (INT_PTR hObjs, LPSTR pBuffer, WORD wLen, DWORD *pdwData)
{
	return GetPropInfo(pBuffer, wLen, pdwData);
}

STDMETHODIMP CObjPropGUID::EvaluatesForClass (INT_PTR hObjs)
{
HRESULT hr = E_FAIL;

	COM_TRY {
	WTRiASObjectHandleMap Map (CLSID_TRiASObjectsHandleMap);
	WTRiASObjects Objs;

		THROW_FAILED_HRESULT(Map -> GetObject (hObjs, Objs.ppu()));
		hr = GetPropertyFrom(Objs, CComBSTR(FEATUREPROPERTY_HasObjectGuid), VARIANT_FALSE) ? S_OK : S_FALSE;

	} COM_CATCH;
	return hr;
}
#endif // !defined(_FORCE_LEGACY_CODE) && _TRiAS_VER >= 0x0300

///////////////////////////////////////////////////////////////////////////////
// Objekteigenschaft, die Identifikator als String liefert --------------------
CObjPropIdent::CObjPropIdent (void)
	: CBaseObjectProperty (ResString (IDS_OBJPROPIDENT, 64), IDS_OBJPROPIDENTHELP)
{
}

STDMETHODIMP CObjPropIdent::GetPropInfo (LPSTR pBuffer, WORD wLen, DWORD *pdwData)
{
HRESULT hr = CBaseObjectProperty::GetPropInfo(pBuffer, wLen, pdwData);

	if (SUCCEEDED(hr) && NULL != pdwData)
		*pdwData |= PROPCAPS_OBJPROPTYPE_INTEGER;
	return hr;
}

STDMETHODIMP CObjPropIdent::Eval (LONG lONr, LPSTR pBuffer, ULONG ulLen, 
				    ULONG *pulWritten)
{
	TX_ASSERT(NULL != pBuffer);
	TX_ASSERT(0 != ulLen);

	if (ulLen > 20) {
	LONG lIdent = DEX_GetObjIdent (lONr);

		if (0L == lIdent || -1L == lIdent) {
			*pBuffer = '\0';
			if (NULL != pulWritten) *pulWritten = 0;
			return ResultFromScode (E_FAIL);
		}

#if defined(WIN32)
		ltoa (lIdent, pBuffer, DEX_GetIdBase());
		if (pulWritten) *pulWritten = strlen(pBuffer);
#else
		ltoa (lIdent, s_cbOPBuffer, DEX_GetIdBase());

	long ul = hstrlen (s_cbOPBuffer);

		memcpy (pBuffer, s_cbOPBuffer, ul+1);	// '\0' mitkopieren
		if (pulWritten) *pulWritten = ul;
#endif
		m_ulCnt++;	// Zähler der erfolgreichen Aufrufe
		return S_OK;
	}

	*pBuffer = '\0';
	if (NULL != pulWritten) *pulWritten = 0;

	return E_FAIL;
}

// IPersistStreamInterface ////////////////////////////////////////////////////
// *** IPersist methods *** 
STDMETHODIMP CObjPropIdent::GetClassID (CLSID *pClsID)
{
	*pClsID = GetObjectCLSID();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Objekteigenschaft, die ObjektKlassenSchlüssel liefert 
CObjPropObjClassCode::CObjPropObjClassCode (void)
	: CBaseObjectProperty (ResString (IDS_OBJPROPOKS, 64), IDS_OBJPROPOKS_HELP)
{
}

STDMETHODIMP CObjPropObjClassCode::Eval (LONG lONr, LPSTR pBuffer, ULONG ulLen, 
				    ULONG *pulWritten)
{
	TX_ASSERT(NULL != pBuffer);
	TX_ASSERT(0 != ulLen);

	if (ulLen >= MAX_OKS_LEN) {
	LONG lIdent = DEX_GetObjIdentEx (lONr);

		if (0L == lIdent || -1L == lIdent || 
			FAILED(ClassFromIdent (lIdent, pBuffer)))
		{
			*pBuffer = '\0';
			if (NULL != pulWritten) *pulWritten = 0;
			return E_FAIL;
		}

		if (pulWritten) 
			*pulWritten = strlen(pBuffer);
		m_ulCnt++;		// Zähler der erfolgreichen Aufrufe
		return S_OK;
	}

	*pBuffer = '\0';
	if (NULL != pulWritten) *pulWritten = 0;

	return E_FAIL;
}

// IPersistStreamInterface ////////////////////////////////////////////////////
// *** IPersist methods *** 
STDMETHODIMP CObjPropObjClassCode::GetClassID (CLSID *pClsID)
{
	*pClsID = GetObjectCLSID();
	return S_OK;
}

#if !defined(_FORCE_LEGACY_CODE) && _TRiAS_VER >= 0x0300
///////////////////////////////////////////////////////////////////////////////
// Objekteigenschaft, die Datenquelle liefert, aus der dieses Objekt stammt
CObjPropDataSource::CObjPropDataSource (void)
	: CBaseObjectProperty (ResString (IDS_OBJPROPDATASOURCE, 64), IDS_OBJPROPDATASOURCE_HELP)
{
}

///////////////////////////////////////////////////////////////////////////////
// Finden eines besonderen Parents in der Objekthierarchie über einem gegebenen
// Objekt
template<class T>
inline HRESULT FindSpecificParent (T ParentIn, REFIID riid, void **ppIObj)
{
__Interface<IDispatch> Parent(ParentIn);

	while (Parent.IsValid()) {
		if (SUCCEEDED(Parent -> QueryInterface(riid, ppIObj)))
			return S_OK;		// gesuchtes Objekt gefunden

	// eine Etage weiter hoch
	__Interface<ITRiASBase> ParT(Parent);

		RETURN_FAILED_HRESULT(ParT -> get_Parent (Parent.ppi()));
	}
	return E_UNEXPECTED;
}

STDMETHODIMP CObjPropDataSource::Eval (
	LONG lONr, LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten)
{
	TX_ASSERT(NULL != pBuffer);
	TX_ASSERT(0 != ulLen);

// sicherheitshalber alles initialisieren
	*pBuffer = '\0';
	if (NULL != pulWritten) *pulWritten = 0;

	USES_CONVERSION;
	COM_TRY {
	WTRiASObjectHandleMap Map (CLSID_TRiASObjectHandleMap);		// throws hr
	WUnknown Unk;
	WTRiASConnection Conn;

		THROW_FAILED_HRESULT(Map -> GetObject (lONr, Unk.ppi()));
		THROW_FAILED_HRESULT(FindSpecificParent (Unk, __uuidof(ITRiASConnection), Conn.ppv()));

	CComBSTR bstrName;

		THROW_FAILED_HRESULT(Conn -> get_Name (CLEARED(&bstrName)));
		strcpy (pBuffer, OLE2A(bstrName));

		if (pulWritten) 
			*pulWritten = strlen(pBuffer);
		m_ulCnt++;		// Zähler der erfolgreichen Aufrufe

	} COM_CATCH;
	return S_OK;
}

// IPersistStreamInterface ////////////////////////////////////////////////////
// *** IPersist methods 
STDMETHODIMP CObjPropDataSource::GetClassID (CLSID *pClsID)
{
	*pClsID = GetObjectCLSID();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Objekteigenschaft, die Datenquelle liefert, aus der dieses Objekt stammt
CObjPropDataSourceDesc::CObjPropDataSourceDesc (void)
	: CBaseObjectProperty (ResString (IDS_OBJPROPDATASOURCEDESC, 64), IDS_OBJPROPDATASOURCEDESC_HELP)
{
}

STDMETHODIMP CObjPropDataSourceDesc::Eval (
	LONG lONr, LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten)
{
	TX_ASSERT(NULL != pBuffer);
	TX_ASSERT(0 != ulLen);

// sicherheitshalber alles initialisieren
	*pBuffer = '\0';
	if (NULL != pulWritten) *pulWritten = 0;

	USES_CONVERSION;
	COM_TRY {
	WTRiASObjectHandleMap Map (CLSID_TRiASObjectHandleMap);		// throws hr
	WUnknown Unk;
	WTRiASConnection Conn;

		THROW_FAILED_HRESULT(Map -> GetObject (lONr, Unk.ppi()));
		THROW_FAILED_HRESULT(FindSpecificParent (Unk, __uuidof(ITRiASConnection), Conn.ppv()));

	CComBSTR bstrName;

		THROW_FAILED_HRESULT(Conn -> get_Description (CLEARED(&bstrName)));
		strcpy (pBuffer, OLE2A(bstrName));

		if (pulWritten) 
			*pulWritten = strlen(pBuffer);
		m_ulCnt++;		// Zähler der erfolgreichen Aufrufe

	} COM_CATCH;
	return S_OK;
}

// IPersistStreamInterface ////////////////////////////////////////////////////
// *** IPersist methods 
STDMETHODIMP CObjPropDataSourceDesc::GetClassID (CLSID *pClsID)
{
	*pClsID = GetObjectCLSID();
	return S_OK;
}
#endif // !_FORCE_LEGACY_CODE && _TRiAS_VER >= 0x0300

///////////////////////////////////////////////////////////////////////////////
// Objekteigenschaften, die ObjektTyp als String liefern ----------------------
CObjPropObjTyp::CObjPropObjTyp (LPCSTR pcName, ResID resHelp)
		: CBaseObjectProperty (pcName, resHelp)
{
	m_ulP = m_ulL = m_ulF = m_ulT = m_ulK = 0L;
}

STDMETHODIMP CObjPropObjTyp::Reset (void)
{
	m_ulP = m_ulL = m_ulF = m_ulT = m_ulK = 0L;
	return CBaseObjectProperty::Reset();
}

STDMETHODIMP CObjPropObjTyp::Cumulation (LPSTR pBuffer, ULONG ulLen, 
					   ULONG *pulWritten)
{
	TX_ASSERT(NULL != pBuffer);
	TX_ASSERT(0 != ulLen);

ResString resFormat (IDS_OBJPROPCNTFORMAT, 64);
	
#if defined(WIN32)
	wsprintf (pBuffer, resFormat, m_ulP, m_ulL,  m_ulF, m_ulT, m_ulK);
	if (pulWritten) *pulWritten = strlen (pBuffer);
#else
	wsprintf (s_cbOPBuffer, resFormat, m_ulP, m_ulL,  m_ulF, m_ulT, m_ulK);

ULONG ul = min (ulLen-1, hstrlen(s_cbOPBuffer));

	memcpy (pBuffer, s_cbOPBuffer, ul+1);
	if (pulWritten) *pulWritten = ul;
#endif

return S_OK;
}

CObjPropObjTypLong::CObjPropObjTypLong (void)
		    : CObjPropObjTyp (ResString (IDS_OBJPROPOBJTYP, 64), IDS_OBJPROPTYPHELP)
{
}

STDMETHODIMP CObjPropObjTypLong::Eval (LONG lONr, LPSTR pBuffer, ULONG ulLen, 
					 ULONG *pulWritten)
{
	TX_ASSERT(NULL != pBuffer);
	TX_ASSERT(0 != ulLen);

short iObjTyp = DEX_GetObjectType (lONr);
unsigned int iResID;

	switch (iObjTyp) {
	case OT_PUNKT:	iResID = IDS_OBJPROPPUNKTOBJ; 		m_ulP++; break;
	case OT_KANTE:	iResID = IDS_OBJPROPKANTENOBJ;		m_ulL++; break;
	case OT_FLAECHE: iResID = IDS_OBJPROPFLAECHENOBJ;	m_ulF++; break;
	case OT_TEXT:	iResID = IDS_OBJPROPTEXTOBJ;		m_ulT++; break;
	case OT_KO:	iResID = IDS_OBJPROPKOMPLEXOBJ;		m_ulK++; break;
	case OT_KREIS:	iResID = IDS_OBJPROPKREISOBJ;		m_ulF++; break;
	case OT_UNKNOWN:
	default:	iResID = IDS_OBJPROPUNKNOWNOBJ;	break;
	}

#if defined(WIN32)
	strcpy (pBuffer, ResString (iResID, 64));
	if (pulWritten) *pulWritten = strlen(pBuffer);
#else
ResString res (iResID, 64);
ULONG ul = strlen(res);

	memcpy (pBuffer, res.Addr(), ul+1);
	if (pulWritten) *pulWritten = ul;
#endif
	m_ulCnt++;	// Zähler der erfolgreichen Aufrufe

return S_OK;
}

// IPersistStreamInterface ////////////////////////////////////////////////////
// *** IPersist methods *** 
STDMETHODIMP CObjPropObjTypLong::GetClassID (CLSID *pClsID)
{
	*pClsID = GetObjectCLSID();
	return S_OK;
}

#if defined(_FORCE_LEGACY_CODE)
///////////////////////////////////////////////////////////////////////////////
// KurzForm
CObjPropObjTypShort::CObjPropObjTypShort (void)
		     : CObjPropObjTyp (ResString (IDS_OBJPROPOBJTYPSHORT, 64), IDS_OBJPROPTYPHELPSHORT)
{
}

STDMETHODIMP CObjPropObjTypShort::Eval (LONG lONr, LPSTR pBuffer, ULONG ulLen, 
					  ULONG *pulWritten)
{
	TX_ASSERT(NULL != pBuffer);
	TX_ASSERT(0 != ulLen);

short iObjTyp = DEX_GetObjectType (lONr);
unsigned int iResID;

	switch (iObjTyp) {
	case OT_PUNKT:	iResID = IDS_OBJPROPPUNKTOBJSH;		m_ulP++; break;
	case OT_KANTE:	iResID = IDS_OBJPROPKANTENOBJSH; 	m_ulL++; break;
	case OT_KREIS:	
	case OT_FLAECHE: iResID = IDS_OBJPROPFLAECHENOBJSH;	m_ulF++; break;
	case OT_TEXT:	iResID = IDS_OBJPROPTEXTOBJSH;		m_ulT++; break;
	case OT_KO:	iResID = IDS_OBJPROPKOMPLEXOBJSH;	m_ulK++; break;
	case OT_UNKNOWN:
	default:	iResID = IDS_OBJPROPUNKNOWNOBJSH;	break;
	}

#if defined(WIN32)
	strcpy (pBuffer, ResString (iResID, 8));
	if (pulWritten) *pulWritten = strlen(pBuffer);
#else
ResString res (iResID, 8);
ULONG ul = strlen(res);

	memcpy (pBuffer, res.Addr(), ul+1);
	if (pulWritten) *pulWritten = ul;
#endif
	m_ulCnt++;	// Zähler der erfolgreichen Aufrufe

return S_OK;
}

// IPersistStreamInterface ////////////////////////////////////////////////////
// *** IPersist methods *** 
STDMETHODIMP CObjPropObjTypShort::GetClassID (CLSID *pClsID)
{
	*pClsID = GetObjectCLSID();
	return S_OK;
}
#endif // defined(_FORCE_LEGACY_CODE)

///////////////////////////////////////////////////////////////////////////////
// Eingabefelder als Objekteigenschaft ----------------------------------------
static const char *MakeFullOPName (int iCnt)
{
static char cbName[_MAX_PATH];
ResString res (IDS_OBJPROPFTEXT, _MAX_PATH);

	strcpy (cbName, res);
	strcat (cbName, " ");
	itoa (iCnt, &cbName[strlen(cbName)], 10);
	
return cbName;
}

#pragma warning (disable:4355)

CObjPropQueryField::CObjPropQueryField (void)
		    : CBaseObjectProperty (NULL, IDS_OBJPROPQFIELDHELP), m_iNumber(0), m_hWnd(NULL)
{
	m_lCum = 0L;
	m_fUseForAll = false;
	m_fFirst = true;
	m_fInitialized = false;
}

#pragma warning (default:4355)

// *** IObjectProperty specific functions *** ---------------------------------
STDMETHODIMP CObjPropQueryField::GetPropInfo (LPSTR pBuffer, WORD wLen, DWORD *pdwData)
{
HRESULT hr = CBaseObjectProperty::GetPropInfo(pBuffer, wLen, pdwData);

	if (SUCCEEDED(hr) && NULL != pdwData)
		*pdwData |= PROPCAPS_INTERACTIVE|PROPCAPS_INTERACTIVE_INIT;
	return hr;
}

STDMETHODIMP CObjPropQueryField::Reset (void)
{
	if (!m_fInitialized) 
		return ResultFromScode (E_FAIL);

	m_lCum = 0L;
	m_fUseForAll = false;
	m_fFirst = true;

return CBaseObjectProperty::Reset();
}

STDMETHODIMP CObjPropQueryField::Eval(LONG lONr, LPSTR pBuffer, ULONG ulLen, 
					ULONG *pulWritten)
{
	if (!m_fInitialized) 
		return ResultFromScode (E_FAIL);

	TX_ASSERT(NULL != pBuffer);
	TX_ASSERT(0 != ulLen);

	if (m_fUseForAll) {	// Fenster ist bereits da gewesen
#if defined(WIN32)
		strcpy (pBuffer, m_strFText.c_str());
		if (pulWritten) *pulWritten = strlen (pBuffer);
#else
	ULONG ul = min(ulLen-1, m_strFText.length());

		memcpy (pBuffer, m_strFText.c_str(), ul+1);
		if (pulWritten) *pulWritten = ul;
#endif
	} else {
	// hier Fenster anzeigen und Text abfragen
	Window Wnd (m_hWnd);
	CQueryFieldDlg QFDlg (&Wnd, m_iNumber);
	
		if (!QFDlg.FInit (lONr, m_fFirst || m_fUseForAll, m_strFText.c_str())) {
			*pBuffer = '\0';
			if (pulWritten) *pulWritten = 0;
			return E_FAIL;		// Initfehler
		}
		QFDlg.Show (Centre);
		if (!QFDlg.Result()) {
			*pBuffer = '\0';
			if (pulWritten) *pulWritten = 0;
			return S_FALSE;		// keine Eingabe
		}
		m_fUseForAll = QFDlg.UseForAll();

#if defined(WIN32)
		QFDlg.GetFieldText (pBuffer, ulLen);
		m_strFText = pBuffer;
		if (pulWritten) *pulWritten = strlen (pBuffer);
#else
		QFDlg.GetFieldText (s_cbOPBuffer, ulLen-1);

	ULONG ul = hstrlen (s_cbOPBuffer);

		memcpy (pBuffer, s_cbOPBuffer, ul+1);
		m_strFText = s_cbOPBuffer;
		if (pulWritten) *pulWritten = ul;
#endif
		m_fFirst = false;		// nicht mehr das erste mal
	}	
	m_lCum += atol (m_strFText.c_str());
	m_ulCnt++;

return S_OK;
}

STDMETHODIMP CObjPropQueryField::Cumulation (LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten)
{
	if (!m_fInitialized) 
		return ResultFromScode (E_FAIL);

	TX_ASSERT(NULL != pBuffer);
	TX_ASSERT(0 != ulLen);

#if defined(WIN32)
	ltoa (m_lCum, pBuffer, 10);
	if (pulWritten) *pulWritten = strlen (pBuffer);
#else
	ltoa (m_lCum, s_cbOPBuffer, 10);

ULONG ul = min (ulLen-1, hstrlen(s_cbOPBuffer));

	memcpy (pBuffer, s_cbOPBuffer, ul+1);
	if (pulWritten) *pulWritten = ul;
#endif

return S_OK;
}

// IConfigObjectProperty
STDMETHODIMP CObjPropQueryField::ConfigObjectProperty (HWND hWndParent)
{
Window Wnd (hWndParent);
CQueryFieldDlg QFDlg (&Wnd, m_iNumber);

	if (!QFDlg.FInit (0, m_fFirst || m_fUseForAll, m_strFText.c_str(), false)) 
		return E_FAIL;		// Initfehler

	QFDlg.Show (Centre);
	if (!QFDlg.Result()) 
		return S_FALSE;		// keine Eingabe

char cbBuffer[_MAX_PATH];

	QFDlg.GetFieldText (cbBuffer, sizeof(cbBuffer));
	m_strFText = cbBuffer;
	m_fUseForAll = true;

	return S_OK;
}

STDMETHODIMP CObjPropQueryField::get_IsConfigured (VARIANT_BOOL *pfConfigState)
{
	if (NULL == pfConfigState)
		return E_POINTER;

	*pfConfigState = m_fUseForAll ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}

// InitialisierungsInterface //////////////////////////////////////////////////
// *** IInitObjPropQueryField method *** 
STDMETHODIMP CObjPropQueryField::Init (HWND hParent, int iNumber)
{
	SetParent (hParent);
	SetName (MakeFullOPName (iNumber));
	if (iNumber > 0) SetNumber (iNumber);

	SetInitialized (true);
	return S_OK;
}

// IPersistStreamInterface ////////////////////////////////////////////////////
// *** IPersist methods *** 
STDMETHODIMP CObjPropQueryField::GetClassID (CLSID *pClsID)
{
	*pClsID = GetObjectCLSID();
	return S_OK;
}

#if !defined(_FORCE_LEGACY_CODE) && _TRiAS_VER >= 0x0300
///////////////////////////////////////////////////////////////////////////////
// ITRiASLockFeature
HRESULT CTRiASLockFeatureImplBase::get_IsRO(INT_PTR lONr, IUnknown *pIUnk, VARIANT_BOOL * pVal)
{
	if (NULL == pVal)
		return E_POINTER;

CLockedObjs::iterator it = m_Objs.find(lONr);

	if (it == m_Objs.end())
		return E_UNEXPECTED;

char cbBuffer[2048];
WObjectProperty Prop;
WPropertyInfo2 Info;

	if (SUCCEEDED(pIUnk -> QueryInterface(Info.ppi()))) {
	DWORD dwType = 0;
	INT_PTR hObjs = DEX_GetObjIdentEx(lONr);

		if (NULL == hObjs)
			return E_UNEXPECTED;

	HRESULT hr = Info -> GetPropInfoEx (hObjs, cbBuffer, sizeof(cbBuffer), &dwType);

		if (SUCCEEDED(hr)) {
			*pVal = (dwType & PROPCAPS_NOTREADONLY) ? VARIANT_FALSE : VARIANT_TRUE;
			return S_OK;
		} 
		return hr;
	}
	else if (SUCCEEDED(pIUnk -> QueryInterface(Prop.ppi()))) {
	DWORD dwType = 0;
	HRESULT hr = Prop -> GetPropInfo (cbBuffer, sizeof(cbBuffer), &dwType);

		if (SUCCEEDED(hr)) {
			*pVal = (dwType & PROPCAPS_NOTREADONLY) ? VARIANT_FALSE : VARIANT_TRUE;
			return S_OK;
		} 
		return hr;
	}
	return E_NOINTERFACE;
}

HRESULT CTRiASLockFeatureImplBase::get_Name (IUnknown *pIUnk, BSTR *pVal)
{
	if (NULL == pVal)
		return E_POINTER;

char cbBuffer[2048];
WObjectProperty Prop;

	if (SUCCEEDED(pIUnk -> QueryInterface(IID_IObjectProperty, Prop.ppv()))) {
	HRESULT hr = Prop -> GetPropInfo (cbBuffer, sizeof(cbBuffer), NULL);

		if (SUCCEEDED(hr)) {
		CComBSTR vVal (cbBuffer);

			*pVal = vVal.Detach();
			return S_OK;
		} 
		return hr;
	}
	return E_NOINTERFACE;
}

HRESULT CTRiASLockFeatureImplBase::get_Description (IUnknown *pIUnk, BSTR *pVal)
{
	if (NULL == pVal)
		return E_POINTER;

char cbBuffer[2048];
WObjectProperty Prop;

	if (SUCCEEDED(pIUnk -> QueryInterface(IID_IObjectProperty, Prop.ppv()))) {
	HRESULT hr = Prop -> HelpInfo (cbBuffer, sizeof(cbBuffer), NULL, NULL);

		if (SUCCEEDED(hr)) {
		CComBSTR vVal (cbBuffer);

			*pVal = vVal.Detach();
			return S_OK;
		} 
		return hr;
	}
	return E_NOINTERFACE;
}

HRESULT CTRiASLockFeatureImplBase::get_Feature(INT_PTR lONr, IUnknown *pIUnk, VARIANT * pVal)
{
	if (NULL == pVal)
		return E_POINTER;

CLockedObjs::iterator it = m_Objs.find(lONr);

	if (it == m_Objs.end())
		return E_UNEXPECTED;

	if ((*it).second.m_fIsDirty || (*it).second.m_fIsEvaluated) {
	// Objekteigenschaft ist bereits modifiziert/eingelesen
	CComVariant vVal ((*it).second.m_vValue);

		if (VT_ERROR == V_VT(&vVal)) {
			vVal = g_cbNil;			// liefert nichts
	
		HRESULT hr = vVal.Detach (pVal);

			return SUCCEEDED(hr) ? S_FALSE : hr;	// nicht existierende Objprop liefert S_FALSE
		}
		return vVal.Detach (pVal);
	} 
	else {
	char cbBuffer[2048];
	WObjectProperty Prop;

		if (SUCCEEDED(pIUnk -> QueryInterface(IID_IObjectProperty, Prop.ppv()))) {	
			if (SUCCEEDED(Prop -> Eval (lONr, cbBuffer, sizeof(cbBuffer), NULL))) {
			CComVariant vVal (cbBuffer);
			DWORD dwFlags = 0L;

				if (SUCCEEDED(Prop -> GetPropInfo (cbBuffer, sizeof(cbBuffer), &dwFlags)) && 
					!(dwFlags & PROPCAPS_OBJPROPTYPE_VOLATILE))
				{
					(*it).second.m_vValue = vVal;
					(*it).second.m_fIsEvaluated = true;
				}
				return vVal.Detach(pVal);
			} 
			else {
			CComVariant vVal (g_cbNil);
			HRESULT hr = vVal.Detach(pVal);

				(*it).second.m_fIsEvaluated = false;
				return SUCCEEDED(hr) ? S_FALSE : hr;		// nicht existierende Objprop liefert S_FALSE
			}
		}
	// hier durchfallen ...
	}
	return E_NOINTERFACE;
}

// Wert an Objekteigenschaft wegspeichern
HRESULT CTRiASLockFeatureImplBase::CommitFeature(INT_PTR lONr, IUnknown *pIUnk, VARIANT_BOOL fCommit)
{
CLockedObjs::iterator it = m_Objs.find(lONr);

	if (it == m_Objs.end())
		return E_UNEXPECTED;

	USES_CONVERSION;
	if ((*it).second.m_fIsDirty && fCommit) {
	// Schreiben ggf. mit Undo
	WObjectProperty2 Prop2;
	WObjectProperty3 Prop3;

		if (SUCCEEDED(pIUnk -> QueryInterface(Prop3.ppi()))) {	
		// ObjProp writeable ?
		CComVariant v;

			if (VT_ERROR != V_VT(&(*it).second.m_vValue) && 
				SUCCEEDED(v.ChangeType (VT_BSTR, &(*it).second.m_vValue))) 
			{
			// gültigen Wert zurückschreiben
				RETURN_FAILED_HRESULT(Prop3 -> SetWithUndo (lONr, OLE2A(V_BSTR(&v))));
			} else {
			// ObjProp sol gelöscht werden
				RETURN_FAILED_HRESULT(Prop3 -> SetWithUndo (lONr, NULL));
			}
		} 
		else if (SUCCEEDED(pIUnk -> QueryInterface(Prop2.ppi()))) {	
		// ObjProp writeable ?
		CComVariant v;

			if (VT_ERROR != V_VT(&(*it).second.m_vValue) && 
				SUCCEEDED(v.ChangeType (VT_BSTR, &(*it).second.m_vValue))) 
			{
			// gültigen Wert zurückschreiben
				RETURN_FAILED_HRESULT(Prop2 -> Set (lONr, OLE2A(V_BSTR(&v))));
			} else {
			// ObjProp sol gelöscht werden
				RETURN_FAILED_HRESULT(Prop2 -> Set (lONr, NULL));
			}
		} 
		(*it).second.m_fIsDirty = false;
	}
	return S_OK;
}

HRESULT CTRiASLockFeatureImplBase::LockFeature(INT_PTR lONr)
{
CLockedObjs::iterator it = m_Objs.find(lONr);

	if (it != m_Objs.end())
		return S_FALSE;

	m_Objs.insert(CLockedObjs::value_type(lONr, CLockData()));
	return S_OK;
}

HRESULT CTRiASLockFeatureImplBase::UnlockFeature(INT_PTR lONr)
{
CLockedObjs::iterator it = m_Objs.find(lONr);

	if (it == m_Objs.end())
		return S_FALSE;

	m_Objs.erase(it);
	return S_OK;
}

HRESULT CTRiASLockFeatureImplBase::get_IsLocked(INT_PTR lONr, VARIANT_BOOL *pfLocked)
{
	if (NULL == pfLocked)
		return E_POINTER;

	*pfLocked = m_Objs.find(lONr) != m_Objs.end() ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}

STDMETHODIMP CTRiASLockFeatureImplBase::put_Feature (INT_PTR lONr, VARIANT newVal)
{
CLockedObjs::iterator it = m_Objs.find(lONr);

	if (it == m_Objs.end()) {
		m_Objs.insert(CLockedObjs::value_type(lONr, CLockData()));
		it = m_Objs.find(lONr);
	}
	_ASSERTE(it != m_Objs.end());

	(*it).second.m_vValue = newVal;
	(*it).second.m_fIsDirty = true;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// 
STDMETHODIMP CTRiASLockFeatureStandAlone::get_IsRO (INT_PTR lONr, VARIANT_BOOL *pVal)
{
	return CTRiASLockFeatureImplBase::get_IsRO (lONr, GetUnknown(), pVal);
}

STDMETHODIMP CTRiASLockFeatureStandAlone::get_Name (/*[out, retval]*/ BSTR *pVal)
{
	return CTRiASLockFeatureImplBase::get_Name (GetUnknown(), pVal);
}

STDMETHODIMP CTRiASLockFeatureStandAlone::get_Description (/*[out, retval]*/ BSTR *pVal)
{
	return CTRiASLockFeatureImplBase::get_Description (GetUnknown(), pVal);
}

STDMETHODIMP CTRiASLockFeatureStandAlone::get_Feature(INT_PTR lONr, VARIANT * pVal)
{
	return CTRiASLockFeatureImplBase::get_Feature (lONr, GetUnknown(), pVal);
}

STDMETHODIMP CTRiASLockFeatureStandAlone::UnlockFeature(INT_PTR lONr, VARIANT_BOOL fCommit)
{
	RETURN_FAILED_HRESULT(CTRiASLockFeatureImplBase::CommitFeature (lONr, GetUnknown(), fCommit));
	RETURN_FAILED_HRESULT(CTRiASLockFeatureImplBase::UnlockFeature(lONr));

// spezifische Member vergessen
CComBSTR bstrFeature (L"Feature_");
CComBSTR bstrIsRO (L"IsRO_");
char cbBuffer[64];

	wsprintf (cbBuffer, "%08x", lONr);
	bstrFeature.Append(cbBuffer);
	bstrIsRO.Append(cbBuffer);
	RETURN_FAILED_HRESULT(DeleteMemberByName(bstrFeature, fdexNameCaseInsensitive|fdexNameInternal));
	RETURN_FAILED_HRESULT(DeleteMemberByName(bstrIsRO, fdexNameCaseInsensitive|fdexNameInternal));
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// IInitInnerObject
STDMETHODIMP CTRiASLockFeatureStandAlone::SetInnerObject (
	IUnknown *pIInner, REFIID riid, IUnknown **ppIOuter)
{
WDelegatorFactory Factory;

	RETURN_FAILED_HRESULT(::CoGetClassObject (CLSID_CoDelegator, CLSCTX_INPROC_SERVER, NULL, IID_IDelegatorFactory, Factory.ppv()));
	RETURN_FAILED_HRESULT(Factory -> CreateDelegator (GetUnknown(), pIInner, IID_IUnknown, m_Unk.ppv()));
	return m_Unk -> QueryInterface (riid, (LPVOID *)ppIOuter);
}

///////////////////////////////////////////////////////////////////////////////
// 
STDMETHODIMP CBaseObjectProperty::get_IsRO (INT_PTR lONr, VARIANT_BOOL *pVal)
{
	return CTRiASLockFeatureImplBase::get_IsRO (lONr, GetUnknown(), pVal);
}

STDMETHODIMP CBaseObjectProperty::get_Name (/*[out, retval]*/ BSTR *pVal)
{
	return CTRiASLockFeatureImplBase::get_Name (GetUnknown(), pVal);
}

STDMETHODIMP CBaseObjectProperty::get_Description (/*[out, retval]*/ BSTR *pVal)
{
	return CTRiASLockFeatureImplBase::get_Description (GetUnknown(), pVal);
}

STDMETHODIMP CBaseObjectProperty::get_Feature(INT_PTR lONr, VARIANT * pVal)
{
	return CTRiASLockFeatureImplBase::get_Feature (lONr, GetUnknown(), pVal);
}

STDMETHODIMP CBaseObjectProperty::UnlockFeature(INT_PTR lONr, VARIANT_BOOL fCommit)
{
	RETURN_FAILED_HRESULT(CTRiASLockFeatureImplBase::CommitFeature (lONr, GetUnknown(), fCommit));
	return CTRiASLockFeatureImplBase::UnlockFeature(lONr);
}

#endif // !defined(_FORCE_LEGACY_CODE) && _TRiAS_VER >= 0x0300

