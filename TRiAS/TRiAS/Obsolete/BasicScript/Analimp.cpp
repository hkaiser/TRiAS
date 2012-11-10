#include "bscriptp.hxx"
#include "bscript.h"
 
#include "macrguid.h"                  
#include "imacro.h"
#include "imacorg.h"

#include "custdlg.h" 

#include <ospace/std/string>

#include "myenum.h"

#include "listitem.h"
#include "commsi.h"
#include "procimp.h"
#include "analimp.h"
#include "anpasimp.h"
#include "saveimp.h"

#include "macroorg.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ANALYSEINTERFACEIMP.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

CImpIAnalyse* CImpIAnalyse :: Create(LPUNKNOWN pUnkOuter, CMacroOrg* pMacroOrg)
{
	if (pUnkOuter == NULL)
		return NULL;

	CImpIAnalyse* pIAnalyse = new CImpIAnalyse(pUnkOuter, pMacroOrg);
	if (NULL == pIAnalyse)	return NULL;		

	HRESULT hr = pIAnalyse -> FInit(); 
	if (FAILED(hr)) {
		delete pIAnalyse;
		return NULL;
	}

return  pIAnalyse;
}
		
CImpIAnalyse :: CImpIAnalyse(LPUNKNOWN pUnkOuter, CMacroOrg* pMacroOrg)
{
	m_cRef=0;

	m_pUnkOuter = pUnkOuter;
	m_pMacroOrg = pMacroOrg;
}

CImpIAnalyse :: ~CImpIAnalyse()
{                
}                                                     

HRESULT CImpIAnalyse :: FInit()
{
return NOERROR;	
}                                         

STDMETHODIMP CImpIAnalyse :: GetMenuStructure (HMENU hMenu)
{
	if (NULL == m_pMacroOrg || 0 == hMenu) return ResultFromScode (E_FAIL);

// pUnk -> AddRef()
LPIMPICOMMANDS pICs = m_pMacroOrg -> GetCommands();
	if (NULL == pICs) return ResultFromScode (E_FAIL);
	
HRESULT	hr = pICs -> GetMenuItems(hMenu);
	pICs -> Release();
	if (FAILED(hr)) return hr;	
		
return NOERROR;
}

// *** IUnknown methods -------------------------------------------------------
STDMETHODIMP CImpIAnalyse :: QueryInterface (REFIID riid, LPVOID *ppvObj)
{
return m_pUnkOuter -> QueryInterface (riid, ppvObj);
}


STDMETHODIMP_(ULONG) CImpIAnalyse :: AddRef (void)
{
    ++m_cRef;
return m_pUnkOuter -> AddRef ();
}


STDMETHODIMP_(ULONG) CImpIAnalyse :: Release (void)
{                               
    --m_cRef;
return m_pUnkOuter -> Release ();
}

