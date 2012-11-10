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
