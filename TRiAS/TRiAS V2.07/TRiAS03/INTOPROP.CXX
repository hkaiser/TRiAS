// Interne Objekteigenschaften ------------------------------------------------
// File: INTOPROP.HXX
	
#include "trias03p.hxx"

#include "trias03.h"		// Resourcen

#include <containr.hxx>
#include <ixtensn.hxx>
#include <ioprpini.hxx>

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
#if !defined(_FORCE_LEGACY_CODE)
DefineSmartInterface(TRiASObjectHandleMap);		// WTRiASObjectHandleMap
DefineSmartInterface(TRiASObject);				// WTRiASObject
DefineSmartInterface(Dispatch);					// WDispatch
DefineSmartInterface(TRiASDatabase);			// WTRiASDatabase
DefineSmartInterface(TRiASConnection);			// WTRiASConnection
#endif // !_FORCE_LEGACY_CODE

#else 

static char s_cbOPBuffer[1024];
#pragma function (memcpy)		// nicht inline generieren
long hstrlen (const char *pStr);

#endif // WIN32

///////////////////////////////////////////////////////////////////////////////
// Funktion soll gerufen werden, wenn Objekt zerlegt wird
void PASCAL ObjectDestroyed (void);

// Basisklasse für alle TRiAS-internen Objekteigenschaften --------------------
CBaseObjectProperty :: CBaseObjectProperty (LPCSTR pcName, ResID resHelp, bool fRO)
		     : m_resHelpID(resHelp), m_fReadOnly(fRO), m_pfnDestroy(ObjectDestroyed)
{
	m_ulCnt = 0;
	m_fIsDirty = false;
	if (pcName) m_strName = pcName;
}

CBaseObjectProperty :: ~CBaseObjectProperty (void)
{
	if (m_pfnDestroy) m_pfnDestroy();	// das Ende vom Lied
}

///////////////////////////////////////////////////////////////////////////////
// Kopieren dieser Eigenschaft (für Clone)
bool CBaseObjectProperty::FInit (const CBaseObjectProperty &rOP)
{
	m_fIsDirty = rOP.m_fIsDirty;
	m_resHelpID = rOP.m_resHelpID;
	m_fReadOnly = rOP.m_fReadOnly;
	m_pfnDestroy = rOP.m_pfnDestroy;

	return true;
}

// *** IObjectProperty specific functions *** ---------------------------------
STDMETHODIMP CBaseObjectProperty :: GetPropInfo (
		LPSTR pBuffer, WORD wLen, DWORD *pdwData)
{
	if (NULL != pBuffer && wLen > 0) {
	unsigned int uiLen = min((unsigned int)(wLen-1), m_strName.length());

		strncpy (pBuffer, m_strName.c_str(), uiLen);
		pBuffer[uiLen] = '\0';
	}

	if (pdwData) 
		*pdwData = m_fReadOnly ? PROPCAPS_NONE : PROPCAPS_NOTREADONLY;

return NOERROR;
}

STDMETHODIMP CBaseObjectProperty :: Reset (void)
{
	m_ulCnt = 0;
	return NOERROR;
}

STDMETHODIMP_(ULONG) CBaseObjectProperty :: Count (void)
{
	return m_ulCnt;
}

STDMETHODIMP CBaseObjectProperty :: HelpInfo (LPSTR pBuffer, ULONG ulLen, 
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

return NOERROR;
}

// default: no cumulation -----------------------------------------------------
STDMETHODIMP CBaseObjectProperty :: Cumulation (LPSTR pBuffer, ULONG ulLen, 
					     ULONG *pulWritten)
{
	TX_ASSERT(NULL != pBuffer);
	TX_ASSERT(0 != ulLen);

	*pBuffer = '\0';	// no cumulation here
	if (pulWritten) *pulWritten = 0;
	
return NOERROR;
}

STDMETHODIMP CBaseObjectProperty :: Set (LONG, LPCSTR)
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
CObjPropONr :: CObjPropONr (void)
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

STDMETHODIMP CObjPropONr :: Eval (LONG lONr, LPSTR pBuffer, ULONG ulLen, 
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
		return NOERROR;
	}

	return E_FAIL;
}

// IPersistStreamInterface ////////////////////////////////////////////////////
// *** IPersist methods *** 
STDMETHODIMP CObjPropONr::GetClassID (CLSID *pClsID)
{
	*pClsID = GetObjectCLSID();
	return NOERROR;
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
	return NOERROR;
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

///////////////////////////////////////////////////////////////////////////////
// Objekteigenschaft, die Identifikator als String liefert --------------------
CObjPropIdent :: CObjPropIdent (void)
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

STDMETHODIMP CObjPropIdent :: Eval (LONG lONr, LPSTR pBuffer, ULONG ulLen, 
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
		return NOERROR;
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
	return NOERROR;
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
	LONG lIdent = DEX_GetObjIdent (lONr);

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
		return NOERROR;
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
	return NOERROR;
}

#if !defined(_FORCE_LEGACY_CODE)
///////////////////////////////////////////////////////////////////////////////
// Objekteigenschaft, die Datenquelle liefert, aus der dieses Objekt stammt
CObjPropDataSource::CObjPropDataSource (void)
	: CBaseObjectProperty (ResString (IDS_OBJPROPDATASOURCE, 64), IDS_OBJPROPDATASOURCE_HELP)
{
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

		THROW_FAILED_HRESULT(Map -> GetObject (lONr, Unk.ppi()));

	WTRiASObject Obj (Unk);
	WDispatch Disp;

		THROW_FAILED_HRESULT(Obj -> get_Parent (Disp.ppi()));

	WTRiASDatabase DB (Disp);

		THROW_FAILED_HRESULT(DB -> get_Parent (Disp.ppi()));

	WTRiASConnection Conn (Disp);
	CComBSTR bstrName;

		THROW_FAILED_HRESULT(Conn -> get_Name (&bstrName));
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
	return NOERROR;
}
#endif // !_FORCE_LEGACY_CODE

///////////////////////////////////////////////////////////////////////////////
// Objekteigenschaften, die ObjektTyp als String liefern ----------------------
CObjPropObjTyp :: CObjPropObjTyp (LPCSTR pcName, ResID resHelp)
		: CBaseObjectProperty (pcName, resHelp)
{
	m_ulP = m_ulL = m_ulF = m_ulT = m_ulK = 0L;
}

STDMETHODIMP CObjPropObjTyp :: Reset (void)
{
	m_ulP = m_ulL = m_ulF = m_ulT = m_ulK = 0L;
	return CBaseObjectProperty :: Reset();
}

STDMETHODIMP CObjPropObjTyp :: Cumulation (LPSTR pBuffer, ULONG ulLen, 
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

return NOERROR;
}

CObjPropObjTypLong :: CObjPropObjTypLong (void)
		    : CObjPropObjTyp (ResString (IDS_OBJPROPOBJTYP, 64), IDS_OBJPROPTYPHELP)
{
}

STDMETHODIMP CObjPropObjTypLong :: Eval (LONG lONr, LPSTR pBuffer, ULONG ulLen, 
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

return NOERROR;
}

// IPersistStreamInterface ////////////////////////////////////////////////////
// *** IPersist methods *** 
STDMETHODIMP CObjPropObjTypLong::GetClassID (CLSID *pClsID)
{
	*pClsID = GetObjectCLSID();
	return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// KurzForm
CObjPropObjTypShort :: CObjPropObjTypShort (void)
		     : CObjPropObjTyp (ResString (IDS_OBJPROPOBJTYPSHORT, 64), IDS_OBJPROPTYPHELPSHORT)
{
}

STDMETHODIMP CObjPropObjTypShort :: Eval (LONG lONr, LPSTR pBuffer, ULONG ulLen, 
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

return NOERROR;
}

// IPersistStreamInterface ////////////////////////////////////////////////////
// *** IPersist methods *** 
STDMETHODIMP CObjPropObjTypShort::GetClassID (CLSID *pClsID)
{
	*pClsID = GetObjectCLSID();
	return NOERROR;
}

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

CObjPropQueryField :: CObjPropQueryField (void)
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
		*pdwData |= PROPCAPS_INTERACTIVE;
	return hr;
}

STDMETHODIMP CObjPropQueryField::Reset (void)
{
	if (!m_fInitialized) 
		return ResultFromScode (E_FAIL);

	m_lCum = 0L;
	m_fUseForAll = false;
	m_fFirst = true;

return CBaseObjectProperty :: Reset();
}

STDMETHODIMP CObjPropQueryField :: Eval(LONG lONr, LPSTR pBuffer, ULONG ulLen, 
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
			return ResultFromScode(E_FAIL);		// Initfehler
		}
		QFDlg.Show (Centre);
		if (!QFDlg.Result()) {
			*pBuffer = '\0';
			if (pulWritten) *pulWritten = 0;
			return ResultFromScode (S_FALSE);		// keine Eingabe
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

return NOERROR;
}

STDMETHODIMP CObjPropQueryField :: Cumulation (LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten)
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

return NOERROR;
}

// InitialisierungsInterface //////////////////////////////////////////////////
// *** IInitObjPropQueryField method *** 
STDMETHODIMP CObjPropQueryField::Init (HWND hParent, int iNumber)
{
	SetParent (hParent);
	SetName (MakeFullOPName (iNumber));
	if (iNumber > 0) SetNumber (iNumber);

	SetInitialized (true);

return NOERROR;
}

// IPersistStreamInterface ////////////////////////////////////////////////////
// *** IPersist methods *** 
STDMETHODIMP CObjPropQueryField::GetClassID (CLSID *pClsID)
{
	*pClsID = GetObjectCLSID();
	return NOERROR;
}


