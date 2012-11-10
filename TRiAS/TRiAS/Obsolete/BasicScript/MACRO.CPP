
#include "bscriptp.hxx"

#include "macrguid.h"

#include "imacro.h"                  
#include "enumscpt.h"

#include "strmimp.h"
#include "perstimp.h"
#include "macroimp.h"
#include "macro.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MACROSCRIPTIMP.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

CMacroScripts* CMacroScripts :: CreateScript (LPUNKNOWN pIUnk, CebInstance *pebInst)
{
	CMacroScripts* pMacroScripts = new CMacroScripts (pIUnk, pebInst);
	
	if ( NULL == pMacroScripts || !pMacroScripts -> FInit () ) {
		if (NULL != pMacroScripts) delete pMacroScripts;
		return NULL;
	}

	pMacroScripts -> AddRef();

return pMacroScripts;
}
		
CMacroScripts :: CMacroScripts (LPUNKNOWN pIUnk, CebInstance *pebInst)
{                                                        
	m_cRef = 0;
	
	m_pIUnk = pIUnk;		// no AddRef !

	m_pIPersistStorage = NULL;
	m_pIMacroScripts = NULL;
	m_pEnumScripts = NULL;                                            
	
	m_pebInst = pebInst;
}

CMacroScripts :: ~CMacroScripts()
{
	ASSERT (m_pIMacroScripts);
	ASSERT (m_pIPersistStorage);
	ASSERT (m_pEnumScripts);
	
	if (m_pIPersistStorage) delete m_pIPersistStorage;
	m_pIPersistStorage = NULL;
	
	if (m_pIMacroScripts) delete m_pIMacroScripts;
	m_pIMacroScripts = NULL;	
	
	if (m_pEnumScripts) 
		delete m_pEnumScripts;
	m_pEnumScripts = NULL;	
}                                                     

HRESULT CMacroScripts :: GetEnum (CEnumMacroScripts **ppEnumScripts)
{
	if ( ! m_pEnumScripts) 	return ResultFromScode (E_FAIL);

	*ppEnumScripts = m_pEnumScripts;
	m_pEnumScripts -> AddRef();

return NOERROR;
}

bool CMacroScripts :: FInit()
{
	m_pIPersistStorage = new CImpIPersistStorage (NULL != m_pIUnk ? m_pIUnk : this, this);
	if ( NULL == m_pIPersistStorage ) return FALSE;

	m_pIMacroScripts = new CIMacroScriptImp (NULL != m_pIUnk ? m_pIUnk : this, this);
	if ( NULL == m_pIMacroScripts ) return FALSE;
                                                              
	m_pEnumScripts = CEnumMacroScripts :: CreateInstance (NULL);
	if (NULL == m_pEnumScripts) return FALSE; 

return TRUE;	
}


// *** IUnknown methods -------------------------------------------------------
STDMETHODIMP CMacroScripts :: QueryInterface (REFIID riid, LPVOID *ppv)
{
	*ppv = NULL;                  
	
	if (IsEqualIID(riid, IID_IUnknown) )
		*ppv = this;
    else if(IsEqualIID(riid, IID_IScriptContainer) ) 
		*ppv = m_pIMacroScripts;               
    else if(IsEqualIID(riid, IID_IPersistStorage) ) 
		*ppv = m_pIPersistStorage;               

	if (NULL != *ppv) {
		LPUNKNOWN(*ppv) -> AddRef();
		return NOERROR;
	}
	
return ResultFromScode(E_NOINTERFACE);
}

STDMETHODIMP_(ULONG) CMacroScripts :: AddRef (void)
{
	return ++m_cRef;
}

STDMETHODIMP_(ULONG) CMacroScripts :: Release (void)
{                               
	if(--m_cRef == 0){
		delete this;
      		return 0;
    	}
    	
return m_cRef;

}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MACROSIMP.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

CMacro* CMacro :: Create (LPUNKNOWN pIUnk)
{
CMacro* pMacro = new CMacro (pIUnk);

	if ( NULL == pMacro || ! pMacro -> FInit() ) {
		if (NULL != pMacro) delete pMacro;
		return NULL;  
	}
	pMacro -> AddRef();

return pMacro;
}
		
CMacro :: CMacro (LPUNKNOWN pIUnk) 
{	
	m_cRef = 0;                      
	
	m_pIUnk = pIUnk;	// no AddRef

	m_pIPersistStream = NULL;
	m_pIMacro = NULL;
	m_dwSaveFlag = 0x0;
}

CMacro :: ~CMacro()
{
	ASSERT (m_pIPersistStream);
	ASSERT (m_pIMacro);
	if (m_pIPersistStream) delete m_pIPersistStream;
	m_pIPersistStream = NULL;
	if (m_pIMacro) delete m_pIMacro;
	m_pIMacro = NULL;
}                                                     

bool CMacro :: FInit (void)
{                             
	m_pIPersistStream = new CImpIPersistStream (NULL != m_pIUnk ? m_pIUnk : this, this);
	if ( NULL == m_pIPersistStream ) return FALSE;
	
	m_pIMacro = new CIMacrosImp (NULL != m_pIUnk ? m_pIUnk : this, this);
	if ( NULL == m_pIMacro ) return FALSE;
	
return TRUE;
}


// *** IUnknown methods -------------------------------------------------------
STDMETHODIMP CMacro :: QueryInterface (REFIID riid, LPVOID *ppv)
{
	if (IsEqualIID(riid, IID_IUnknown)) 
		*ppv = this;
    else if (IsEqualIID(riid, IID_IScript)) 
		*ppv = m_pIMacro;               
    else if (IsEqualIID(riid, IID_IPersistStream)) 
		*ppv = m_pIPersistStream;               
	
	if (NULL != *ppv) {
		LPUNKNOWN(*ppv) -> AddRef();
		return NOERROR;
	}
    	
return ResultFromScode(E_NOINTERFACE);
}

STDMETHODIMP_(ULONG) CMacro :: AddRef (void)
{
	return ++m_cRef;
}

STDMETHODIMP_(ULONG) CMacro :: Release (void)
{                                                 
	if(--m_cRef == 0){
		delete this;
      		return 0;
    	}

return m_cRef;
}       


