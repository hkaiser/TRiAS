// Implementation einer Objekteigenschaft über eine Funktion 'alten Typus' ----
// File: OBJPROPF.CXX

#include "xtensnp.hxx"

#include <xtsnguid.h>

#include "objpropf.hxx"

#if defined(_DEBUG) && defined(WIN32)
#if defined(__MFC__)
#define new DEBUG_NEW
#endif // __MFC__
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

extern LONG g_cObj;		// globaler ObjektZähler

// Konstruktor/Destruktor/Initialisierung -------------------------------------
CFuncObjectProperty :: CFuncObjectProperty (
		LPCSTR pName, OBJPROPCALLBACK pPropProc, DWORD dwFlags)
		     : m_strName(pName), m_dwFlags(dwFlags)
{
	_ASSERTE(NULL != pPropProc);

	m_dwRefCnt = 0L;
	m_pPropF = pPropProc;
	m_pDelF = NULL;
	m_dwData = 0L;
	m_fExType = false;		// einfacher Typ
}

CFuncObjectProperty :: CFuncObjectProperty (
				LPCSTR pName, OBJPROPEXCALLBACK pPropProcEx, 
				DWORD dwData, OBJPROPDELCALLBACK pDelProc, DWORD dwFlags)
		     : m_strName(pName), m_dwFlags(dwFlags)
{
	_ASSERTE(NULL != pPropProcEx);

	m_dwRefCnt = 0L;
	m_pPropF = OBJPROPCALLBACK(pPropProcEx);
	m_pDelF = pDelProc;
	m_dwData = dwData;
	m_fExType = true;		// erweiterter Typ
}

CFuncObjectProperty :: ~CFuncObjectProperty (void)
{
	if (m_fExType && NULL != m_pDelF)
		m_pDelF (m_dwData);		// LöschFunktion rufen
	piInterlockedDecrement (&g_cObj);		// ein Objekt weniger
}

CFuncObjectProperty *CFuncObjectProperty :: CreateInstance (
				LPCSTR pName, OBJPROPCALLBACK pPropProc, DWORD dwFlags)
{
CFuncObjectProperty *pFOP = new CFuncObjectProperty(pName, pPropProc, dwFlags);

	if (NULL == pFOP || !pFOP -> FInit()) {
		DELETE_OBJ(pFOP);
		return NULL;
	}
	pFOP -> AddRef();
	
	piInterlockedIncrement (&g_cObj);		// DLL nicht entladen !

return pFOP;
}

CFuncObjectProperty *CFuncObjectProperty :: CreateInstance (
				LPCSTR pName, OBJPROPEXCALLBACK pPropProcEx, 
				DWORD dwData, OBJPROPDELCALLBACK pDelProc, DWORD dwFlags)
{
CFuncObjectProperty *pFOP = new CFuncObjectProperty (
				pName, pPropProcEx, dwData, pDelProc, dwFlags);

	if (NULL == pFOP || !pFOP -> FInit()) {
		DELETE_OBJ(pFOP);
		return NULL;
	}
	pFOP -> AddRef();

	piInterlockedIncrement (&g_cObj);		// DLL nicht entladen !

return pFOP;
}

// IUnknown members -----------------------------------------------------------
STDMETHODIMP_(ULONG) CFuncObjectProperty :: AddRef (void)
{
	return ++m_dwRefCnt;
}

STDMETHODIMP_(ULONG) CFuncObjectProperty :: Release (void)
{
	if (--m_dwRefCnt == 0) {
		delete this;	// freigeben
		return 0L;
	}

return m_dwRefCnt;
}

STDMETHODIMP CFuncObjectProperty :: QueryInterface (REFIID riid, LPVOID *ppvObj)
{
	if (riid == IID_IUnknown || riid == IID_IObjectProperty)
		*ppvObj = this;
	else {
		*ppvObj = NULL;
		return ResultFromScode (E_NOINTERFACE);
	}

	LPUNKNOWN(*ppvObj) -> AddRef();

return NOERROR;
}

// IObjectProperty members ----------------------------------------------------
STDMETHODIMP CFuncObjectProperty :: GetPropInfo (
		LPSTR pBuffer, WORD wLen, DWORD *pdwFlags)
{
// FunktionsNamen kopieren (wenn verlangt)
	if (NULL != pBuffer && wLen > 0) {
		if (m_strName.length() > wLen) {
			strncpy (pBuffer, m_strName.c_str(), wLen);
			pBuffer[wLen-1] = '\0';
			return ResultFromScode (S_FALSE);
		}

	// FunktionsNamen umkopieren
		strcpy (pBuffer, m_strName.c_str());
	}

// Eigenschaften kopieren (wenn verlangt)
	if (pdwFlags) *pdwFlags = m_dwFlags;
	return NOERROR;
}

LPSTR CFuncObjectProperty :: InvokeHelper (LONG lONr, LPSTR pBuff, short iLen)
{
	if (m_fExType)
		return (*(OBJPROPEXCALLBACK)m_pPropF)(lONr, pBuff, iLen, m_dwData);
	else
		return m_pPropF (lONr, pBuff, iLen);
}

// Setzt alle Internen Info's dieses Objektes zurück --------------------------
STDMETHODIMP CFuncObjectProperty :: Reset (void)
{
	return (NULL != InvokeHelper (LONG(OBJPROP_RESET), NULL, 0)) ? 
			NOERROR : ResultFromScode (E_FAIL);
}

// Liefert die Anzahl der gültigen Aufrufe seit dem letzten Reset -------------
STDMETHODIMP_(ULONG) CFuncObjectProperty :: Count (void)
{
char cbBuffer[40];

	if (cbBuffer == InvokeHelper (LONG(OBJPROP_COUNT), cbBuffer, sizeof(cbBuffer))) 
		return strtoul (cbBuffer, NULL, 10);
	return 0L;
}

// Liefert HelpInfo zu dieser ObjProperty -------------------------------------
STDMETHODIMP CFuncObjectProperty :: HelpInfo (
		LPSTR pBuffer, ULONG ulLen, LPSTR pHelpFile, ULONG *pulHelpCtx)
{
	if (NULL == InvokeHelper (LONG(OBJPROP_GETHELPTEXT), pBuffer, short(ulLen))) 
		return ResultFromScode (E_FAIL);	// Fehler melden

	if (NULL != pHelpFile) *pHelpFile = '\0';
	if (NULL != pulHelpCtx) *pulHelpCtx = 0;

	return (strlen(pBuffer) > 0) ? NOERROR : ResultFromScode (S_FALSE);
}

// Liefert die ObjProperty für ein gegebenes Objekt (lONr) --------------------
STDMETHODIMP CFuncObjectProperty :: Eval (
			LONG lONr, LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten)
{
	if (NULL == InvokeHelper (lONr, pBuffer, short(ulLen))) 
		return ResultFromScode (E_FAIL);	// Fehler melden

ULONG ulWrittenLen = ULONG(strlen (pBuffer));

	if (NULL != pulWritten)
		*pulWritten = ulWrittenLen;

	return ulWrittenLen != 0 ? NOERROR : ResultFromScode (S_FALSE);
}

// Liefert einen kumulativen Index für diese Objproperty ----------------------
STDMETHODIMP CFuncObjectProperty :: Cumulation (
			LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten)
{
	if (NULL == InvokeHelper (LONG(OBJPROP_CUMULATION), pBuffer, short(ulLen))) 
		return ResultFromScode (E_FAIL);	// Fehler melden

ULONG ulWrittenLen = ULONG(strlen (pBuffer));

	if (NULL != pulWritten)
		*pulWritten = ulWrittenLen;

	return ulWrittenLen != 0 ? NOERROR : ResultFromScode (S_FALSE);
}

