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

#include "intoprop.hxx"
#include "queryfld.hxx"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Problem mit HUGE-Speicherbereichen im WIN16 behandeln ----------------------
#if defined(WIN32)

inline size_t hstrlen (const char *pStr) { return strlen (pStr); }

#else 

static char s_cbOPBuffer[1024];
#pragma function (memcpy)		// nicht inline generieren
long hstrlen (const char *pStr);

#endif // WIN32

// Basisklasse für alle TRiAS-internen Objekteigenschaften --------------------
CBaseObjectProperty :: CBaseObjectProperty (LPFNDESTROYED pfn, LPCSTR pcName, ResID resHelp, bool fRO)
		     : m_resHelpID(resHelp), m_fReadOnly(fRO), m_pfnDestroy(pfn)
{
	m_ulCnt = 0;
	m_dwRefCnt = 0;

	if (pcName) m_strName = pcName;
}

CBaseObjectProperty :: ~CBaseObjectProperty (void)
{
}

// *** IUnknown methods *** ---------------------------------------------------
STDMETHODIMP CBaseObjectProperty :: QueryInterface (REFIID riid, LPVOID* ppvObj)
{
	if (riid == IID_IUnknown || riid == IID_IObjectProperty) {
		*ppvObj = this;
		LPUNKNOWN (*ppvObj) -> AddRef();
		return NOERROR;
	} 

return ResultFromScode (E_NOINTERFACE);
}

STDMETHODIMP_(ULONG) CBaseObjectProperty :: AddRef (void)
{
	return ++m_dwRefCnt;
}

STDMETHODIMP_(ULONG) CBaseObjectProperty :: Release (void)
{
	if (--m_dwRefCnt == 0) {
		if (NULL != m_pfnDestroy)
			(*m_pfnDestroy)();
		delete this;
		return 0L;
	}

return m_dwRefCnt;
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
	return ResultFromScode (E_NOTIMPL);
}

///////////////////////////////////////////////////////////////////////////////
// Objekteigenschaft, die Objeknummer als String liefert ----------------------
CObjPropONr :: CObjPropONr (LPFNDESTROYED pfnDestroy)
	     : CBaseObjectProperty (pfnDestroy, ResString (IDS_OBJPROPONR, 64), 
	     			    IDS_OBJPROPONRHELP)
{
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

return ResultFromScode (E_FAIL);
}

///////////////////////////////////////////////////////////////////////////////
// Objekteigenschaft, die Identifikator als String liefert --------------------
CObjPropIdent :: CObjPropIdent (LPFNDESTROYED pfnDestroy)
	       : CBaseObjectProperty (pfnDestroy, ResString (IDS_OBJPROPIDENT, 64), 
	       			      IDS_OBJPROPIDENTHELP)
{
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
		ltoa (lIdent, pBuffer, 10);
		if (pulWritten) *pulWritten = strlen(pBuffer);
#else
		ltoa (lIdent, s_cbOPBuffer, 10);

	long ul = hstrlen (s_cbOPBuffer);

		memcpy (pBuffer, s_cbOPBuffer, ul+1);	// '\0' mitkopieren
		if (pulWritten) *pulWritten = ul;
#endif
		m_ulCnt++;	// Zähler der erfolgreichen Aufrufe
		return NOERROR;
	}

	*pBuffer = '\0';
	if (NULL != pulWritten) *pulWritten = 0;

return ResultFromScode (E_FAIL);
}

///////////////////////////////////////////////////////////////////////////////
// Objekteigenschaften, die ObjektTyp als String liefern ----------------------
CObjPropObjTyp :: CObjPropObjTyp (LPFNDESTROYED pfnDestroy, LPCSTR pcName, ResID resHelp)
		: CBaseObjectProperty (pfnDestroy, pcName, resHelp)
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

CObjPropObjTypLong :: CObjPropObjTypLong (LPFNDESTROYED pfnDestroy)
		    : CObjPropObjTyp (pfnDestroy, ResString (IDS_OBJPROPOBJTYP, 64), 
		    		      IDS_OBJPROPTYPHELP)
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

CObjPropObjTypShort :: CObjPropObjTypShort (LPFNDESTROYED pfnDestroy)
		     : CObjPropObjTyp (pfnDestroy, ResString (IDS_OBJPROPOBJTYPSHORT, 64), 
				       IDS_OBJPROPTYPHELPSHORT)
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

CObjPropQueryField :: CObjPropQueryField (LPFNDESTROYED pfnDestroy)
		    : CBaseObjectProperty (pfnDestroy, NULL, IDS_OBJPROPQFIELDHELP),
		      m_Init (this, this),
		      m_iNumber(0), m_hWnd(NULL)
{
	m_lCum = 0L;
	m_fUseForAll = false;
	m_fFirst = true;
	m_fInitialized = false;
}

#pragma warning (default:4355)

// IUnknown für ObjPropQueryField ---------------------------------------------
STDMETHODIMP CObjPropQueryField :: QueryInterface (REFIID riid, LPVOID* ppvObj)
{
	if (riid == IID_IInitObjPropQueryField) {
		*ppvObj = &m_Init;
		LPUNKNOWN (*ppvObj) -> AddRef();
		return NOERROR;
	} 

return CBaseObjectProperty::QueryInterface (riid, ppvObj);
}

// *** IObjectProperty specific functions *** ---------------------------------
STDMETHODIMP CObjPropQueryField :: Reset (void)
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
CObjPropQueryField:: 
CInitObjPropQueryField::CInitObjPropQueryField (IUnknown *pIUnk, CObjPropQueryField *pOProp)
{
#if defined(_DEBUG)
	m_dwRefCnt = 0;
#endif // _DEBUG

	m_pIUnk = pIUnk;	// ohne AddRef !
	m_pOProp = pOProp;
}

CObjPropQueryField:: 
CInitObjPropQueryField::~CInitObjPropQueryField (void)
{
	// nothing to do
}

// *** IUnknown methods *** ---------------------------------------------------
STDMETHODIMP_(ULONG) CObjPropQueryField:: 
CInitObjPropQueryField::AddRef (void)
{
#if defined(_DEBUG)
	++m_dwRefCnt;
#endif // _DEBUG
	return m_pIUnk -> AddRef();
}


STDMETHODIMP_(ULONG) CObjPropQueryField:: 
CInitObjPropQueryField::Release (void)
{
#if defined(_DEBUG)
	--m_dwRefCnt;
#endif // _DEBUG
	return m_pIUnk -> Release();
}

STDMETHODIMP CObjPropQueryField::
CInitObjPropQueryField::QueryInterface (REFIID riid, LPVOID *ppvObj)
{
	return m_pIUnk -> QueryInterface (riid, ppvObj);
}

// *** IInitObjPropQueryField method *** --------------------------------------
STDMETHODIMP CObjPropQueryField::
CInitObjPropQueryField::Init (HWND hParent, int iNumber)
{
	m_pOProp -> SetParent (hParent);
	m_pOProp -> SetName (MakeFullOPName (iNumber));
	m_pOProp -> SetNumber (iNumber);

	m_pOProp -> SetInitialized (true);

return NOERROR;
}


