
#include "bscriptp.hxx"
#include "bscript.h"

#include "macrguid.h"
#include "imacorg.h"                  
#include "imacro.h"                  

#include <ospace/std/string>

#include "myenum.h"

#include "listitem.h"
#include "custdlg.h"
#include "commsi.h"
#include "analimp.h"
#include "procimp.h"
#include "anpasimp.h"
#include "saveimp.h"

#include "macroorg.h"

CMacroOrg* CMacroOrg :: Create(LPUNKNOWN pIUnk, UINT uiOffset, 
							   IScriptContainer *pISC)
{
CMacroOrg* pMacroOrg = new CMacroOrg (pIUnk, uiOffset);	
	if ( NULL == pMacroOrg ) return NULL;
	
HRESULT hr = pMacroOrg -> FInit (pISC);
	if (FAILED(hr)) {
		if (pMacroOrg -> m_pIProcess) pMacroOrg -> m_pIProcess -> Release();
		if (pMacroOrg -> m_pIAnalyse) pMacroOrg -> m_pIAnalyse -> Release();
		if (pMacroOrg -> m_pIAnpassen) pMacroOrg -> m_pIAnpassen -> Release();
		if (pMacroOrg -> m_pISave) pMacroOrg -> m_pISave -> Release();

		if (pMacroOrg -> m_pICommands) pMacroOrg -> m_pICommands -> Release();
		delete pMacroOrg;
		return NULL;
	}

	pMacroOrg -> AddRef();

return pMacroOrg;
}
		
CMacroOrg :: CMacroOrg (LPUNKNOWN pIUnk, UINT uiOffset)
{                                                        
	m_cRef = 0;
	
	m_pIUnk = pIUnk;		// no AddRef !
	m_pIProcess = NULL;
	m_pIAnalyse = NULL;
	m_pIAnpassen = NULL;
	m_pISave = NULL;

	m_pICommands = NULL;

	m_uiOffset = uiOffset;
}

CMacroOrg :: ~CMacroOrg()
{	
	if (m_pISave) delete m_pISave;
	m_pISave = NULL;	

	if (m_pIProcess) delete m_pIProcess;
	m_pIProcess = NULL;	

	if (m_pIAnalyse) delete m_pIAnalyse;
	m_pIAnalyse = NULL;	

	if (m_pIAnpassen) delete m_pIAnpassen;
	m_pIAnpassen = NULL;	

	if (m_pICommands) m_pICommands -> Release();
	m_pICommands = NULL;
}                                                     

HRESULT CMacroOrg :: FInit(IScriptContainer *pISC)
{
	m_pIProcess = new CImpIProcess (NULL != m_pIUnk ? 
									m_pIUnk : this, this);
	if ( NULL == m_pIProcess) return ResultFromScode(E_FAIL);
                                                              
	m_pIAnpassen = new CImpIAnpassen (NULL != m_pIUnk ? 
									m_pIUnk : this, this);
	if ( NULL == m_pIAnpassen) return ResultFromScode(E_FAIL);

	m_pIAnalyse = new CImpIAnalyse (NULL != m_pIUnk ? 
									m_pIUnk : this, this);
	if ( NULL == m_pIAnalyse) return ResultFromScode(E_FAIL);

	m_pISave = new CImpISave (	NULL != m_pIUnk ? 
								m_pIUnk : this, this);
	if ( NULL == m_pISave) return ResultFromScode(E_FAIL);

	m_pICommands = CImpICommands :: Create (NULL != m_pIUnk ? 
											m_pIUnk : this, pISC);
	if (NULL == m_pICommands) return ResultFromScode(E_FAIL);

return NOERROR;	
}

// other functions
CImpICommands * CMacroOrg :: GetCommands() 
{ 
	if (NULL == m_pICommands) return NULL;
	
	m_pICommands -> AddRef();

return m_pICommands;
}

// *** IUnknown methods -------------------------------------------------------
STDMETHODIMP CMacroOrg :: QueryInterface (REFIID riid, LPVOID *ppv)
{
	*ppv = NULL;                  
	
	if ( IsEqualIID (riid, IID_IUnknown) )
		*ppv = this;
    else if ( IsEqualIID (riid, IID_IProcess) ) 
		*ppv = m_pIProcess;               
    else if ( IsEqualIID (riid, IID_IAnalyse) ) 
		*ppv = m_pIAnalyse;               
    else if ( IsEqualIID (riid, IID_IAnpassen) ) 
		*ppv = m_pIAnpassen;               
    else if ( IsEqualIID (riid, IID_ISave) || IsEqualIID (riid, IID_IPersistStorage) ) 
		*ppv = m_pISave;               

	if (NULL != *ppv) {
		LPUNKNOWN(*ppv) -> AddRef();
		return NOERROR;
	}
	
return ResultFromScode(E_NOINTERFACE);
}

STDMETHODIMP_(ULONG) CMacroOrg :: AddRef (void)
{
	return ++m_cRef;
}

STDMETHODIMP_(ULONG) CMacroOrg :: Release (void)
{                               
	if(--m_cRef == 0){
		delete this;
     	return 0;
    }
    	
return m_cRef;
}


