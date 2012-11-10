// Interfacedeklaration für Schnittstelle zu BScript-Erweiterung --------------
// File: BSCREXT.CXX

#include "bscriptp.hxx"

#include "bscrext.hxx"

// Liste, die die Modulenamen enthält -----------------------------------------
#pragma warning (disable: 4355)

CExtendModules :: CExtendModules (void)
		: CListContainer (CONTFLAG(CFAutoDelete|CFSyncThreads)),
		  m_navModules (*this)
{
}

#pragma warning (default: 4355)

CExtendModules :: ~CExtendModules (void)
{
	EveryDelete();
}

void CExtendModules :: UserDelete (void *pObj)
{
	((CExtendModule *)pObj) -> ~CExtendModule();
}

void CExtendModules :: Reset (void)
{
	m_navModules.First();
}

bool CExtendModules :: GetNextModule (LPTSTR pModule)
{
	if (!m_navModules.Valid()) return false;	// keiner mehr da

	{
	CExtendModuleLock l(m_navModules);

		l -> GetModule (pModule);
	}
	m_navModules.Next();	// auf nächsten weiterstellen

return true;
}

bool CExtendModules :: AddModule (LPCSTR pModule)
{
CExtendModuleCreator cr (*this);

	return ContCreate (cr, CExtendModule)(pModule) != NULL;
}

// Implementation des IExtendBScript-Interfaces -------------------------------
CExtendBScript :: CExtendBScript (CMacroScriptExtension *pIUnk)
{
	m_dwRefCnt = 0L;
	m_pIUnk = pIUnk;	// no AddRef, fully dependent
}

CExtendBScript :: ~CExtendBScript (void)
{
	// nothing else to do
}

CExtendBScript *CExtendBScript :: CreateInstance (CMacroScriptExtension *pIUnk)
{
CExtendBScript *pIScr = new CExtendBScript (pIUnk);

	if (pIScr == NULL || !pIScr -> FInit()) {
			delete pIScr;
		return NULL;
	}
//	pIScr -> AddRef();

return pIScr;
}

bool CExtendBScript :: FInit (void)
{
	if (m_pIUnk == NULL) 
		return false;	// controlling IUnk must exist

return true;	// nothing to do
}

// *** IExtendBScript methods *** ---------------------------------------------
STDMETHODIMP CExtendBScript :: RegisterExtModule (LPCSTR pModule)
{
	if (m_Modules.AddModule (pModule)) return NOERROR;

return ResultFromScode (E_OUTOFMEMORY);
}


STDMETHODIMP CExtendBScript :: FireEvent (
		LPCSTR pEntry, int iNumParams, BSPARAM *pPars)
{
	return m_pIUnk -> FireEvent (pEntry, iNumParams, pPars);
}


STDMETHODIMP CExtendBScript :: RunText (LPCSTR pText, LPCSTR pEntry, int iNumParams, BSPARAM *pPars)
{
return m_pIUnk -> RunText(pText, pEntry, iNumParams, pPars);
}

STDMETHODIMP CExtendBScript :: RunCode (HINSTANCE hInst, int iResID, LPCSTR pEntry, int iNumParams, BSPARAM *pPars)
{
return m_pIUnk -> RunCode (hInst, iResID, pEntry, iNumParams, pPars);
}

// delegating IUnknown-Interface ----------------------------------------------
STDMETHODIMP CExtendBScript :: QueryInterface (REFIID riid, LPVOID *ppvObj)
{
	return m_pIUnk -> QueryInterface (riid, ppvObj);
}

STDMETHODIMP_(ULONG) CExtendBScript :: AddRef (void)
{
	m_dwRefCnt++;		// debug purposes only

return m_pIUnk -> AddRef();	// delegate
}

STDMETHODIMP_(ULONG) CExtendBScript :: Release (void)
{
	m_dwRefCnt--;		// debug purposes only

return m_pIUnk -> Release();	// delegate
}

