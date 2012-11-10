#include "bscriptp.hxx"
#include "bscript.h"

#include "macrguid.h"                  
#include "imacorg.h"
#include "imacro.h"

#include <ospace/std/string>
#include <ospace/source.h>

#include "myenum.h"
#include "custdlg.h"

#include "listitem.h"
#include "commsi.h"
#include "procimp.h"
#include "analimp.h"
#include "anpasimp.h"
#include "saveimp.h"

#include "macroorg.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PROCESSINTERFACEIMP.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

CImpIProcess* CImpIProcess :: Create(LPUNKNOWN pUnkOuter, CMacroOrg* pMacroOrg)
{
	if (pUnkOuter == NULL)
		return NULL;

	CImpIProcess* pIProcess = new CImpIProcess(pUnkOuter, pMacroOrg);
	if (NULL == pIProcess)	return NULL;		

	HRESULT hr = pIProcess -> FInit(); 
	if (FAILED(hr)) {
		delete pIProcess;
		return NULL;
	}

return  pIProcess;
}
		
CImpIProcess :: CImpIProcess(LPUNKNOWN pUnkOuter, CMacroOrg* pMacroOrg)
{
	m_cRef=0;

	m_pUnkOuter = pUnkOuter;
	m_pMacroOrg = pMacroOrg;
}

CImpIProcess :: ~CImpIProcess()
{                
}                                                     

HRESULT CImpIProcess :: FInit()
{
return NOERROR;	
}                                         

STDMETHODIMP CImpIProcess :: MenuSelect() 
{
return NOERROR;
} 

STDMETHODIMP CImpIProcess :: MenuInit()
{                                    
return NOERROR;
}

STDMETHODIMP CImpIProcess :: MenuCommand(UINT uiID)
{
LPIMPICOMMANDS pCs = GetCommands();
	if (pCs == NULL) return ResultFromScode(E_FAIL);

HRESULT hr =  pCs -> FireEvent(uiID);

	pCs -> Release();

return hr;
}		

STDMETHODIMP CImpIProcess :: Notification()
{
return NOERROR;
}		

STDMETHODIMP CImpIProcess :: WindowsNotification()
{
return NOERROR;
}		

LPIMPICOMMANDS CImpIProcess :: GetCommands(void)
{
return m_pMacroOrg -> GetCommands();
}

HRESULT CImpIProcess :: Run(void)
{
return NOERROR;
}

// *** IUnknown methods -------------------------------------------------------
STDMETHODIMP CImpIProcess :: QueryInterface (REFIID riid, LPVOID *ppvObj)
{
return m_pUnkOuter -> QueryInterface (riid, ppvObj);
}


STDMETHODIMP_(ULONG) CImpIProcess :: AddRef (void)
{
    ++m_cRef;
return m_pUnkOuter -> AddRef ();
}


STDMETHODIMP_(ULONG) CImpIProcess :: Release (void)
{                               
    --m_cRef;
return m_pUnkOuter -> Release ();
}

