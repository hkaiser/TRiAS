#include "bscriptp.hxx"

#include <ospace/source.h>
#include <ospace/std/string>
#include <ospace/uss/std/string.h>

#include "macrguid.h"                  

#include "imacro.h"
#include "imacorg.h"

#include "commimp.h"

#pragma warning (disable: 4355)

int 	g_iC;

CString GetPathName (CString &rPath);

// Für Streaming-Realisierung von CImpICommand
const int os_ccommand_id = os_user_start_id + 124;
OS_STREAMABLE_0( (CImpICommand *), os_ccommand_id);

void os_write (os_bstream& stream, const CImpICommand & C) 
{
	ASSERT(!C.m_strCommandName.IsEmpty());

	stream << C.m_fMacro << os_string(C.m_strCommandName);
}

void os_read (os_bstream& stream, CImpICommand & C) 
{
os_string str;		
	stream >> C.m_fMacro >> str;

	C.m_strCommandName = str.c_str();
	
	ASSERT(!C.m_strCommandName.IsEmpty());
}

// Für Streaming-Realisierung von CImpIMenu
const int os_cmenucommand_id = os_user_start_id + 125;
OS_STREAMABLE_1( (CImpIMenu*), os_cmenucommand_id, (CImpICommand *));

void os_write (os_bstream& stream, const CImpIMenu & M) 
{
	os_write (stream, (const CImpICommand &) M );
}

void os_read (os_bstream& stream, CImpIMenu & M) 
{
	os_read(stream, (CImpICommand &) M );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// COMMAND-INTERFACE-IMPLEMENTATION
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

CImpICommand* CImpICommand :: Create(CString& strCommandName,
									 bool fMacro)
{
	CImpICommand* pICommand = new CImpICommand(strCommandName, fMacro);
	if (NULL == pICommand)	return NULL;		

	HRESULT hr = pICommand -> FInit(); 
	if (FAILED(hr)) {
		delete pICommand;
		return NULL;
	}

	pICommand -> AddRef();

return  pICommand;
}
		
CImpICommand :: CImpICommand()
			: m_BStream(this)
{
	m_cRef=0;
	g_iC++;
}

CImpICommand :: CImpICommand(CString& strCommandName,
							 bool fMacro)
			: m_BStream(this)
{
	m_strCommandName = strCommandName;
	m_fMacro = fMacro;

	m_cRef=0;
	g_iC++;
}

CImpICommand :: ~CImpICommand()
{              
	g_iC--;
}                                                     

HRESULT CImpICommand :: FInit()
{
return NOERROR;	
}                                         

STDMETHODIMP CImpICommand :: GetDescription(LPSTR strDesc, 
											UINT uiLen, bool &fMacro) 
{
	ASSERT(m_fMacro);
	ASSERT(strDesc);

	fMacro = m_fMacro;
	strncpy(strDesc, m_strCommandName, uiLen);  

return NOERROR;	
} 

STDMETHODIMP CImpICommand :: InitCommand(void)
{                                    
return ResultFromScode(E_NOTIMPL);	
}

STDMETHODIMP CImpICommand :: FireEvent(UINT uiID)
{
return ResultFromScode(E_NOTIMPL);	
}		

// *** IUnknown methods ---------------r----------------------------------------
STDMETHODIMP CImpICommand  :: QueryInterface (REFIID riid, LPVOID *ppv)
{
	*ppv = NULL;                  
	
	if ( IsEqualIID (riid, IID_IUnknown) || IsEqualIID (riid, IID_ICommand) )
		*ppv = this;
    else if ( IsEqualIID (riid, IID_IPersistBStream) )
		*ppv = &m_BStream;
	if (NULL != *ppv) {
		LPUNKNOWN(*ppv) -> AddRef();
		return NOERROR;
	}
	
return ResultFromScode(E_NOINTERFACE);
}

STDMETHODIMP_(ULONG) CImpICommand :: AddRef (void)
{
	return ++m_cRef;
}

STDMETHODIMP_(ULONG) CImpICommand :: Release (void)
{                               
	if(--m_cRef == 0){
		delete this;
     	return 0;
    }
    	
return m_cRef;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NOTIFICATION-INTERFACE-IMPL.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

CImpINotification* CImpINotification :: Create(CString& strCommandName,
											   bool fMacro)
{
	CImpINotification* pINot = new CImpINotification(strCommandName, fMacro);
	if (NULL == pINot)	return NULL;		

	HRESULT hr = pINot -> FInit(); 
	if (FAILED(hr)) {
		delete pINot;
		return NULL;
	}

	pINot -> AddRef();

return  pINot;
}
		
CImpINotification :: CImpINotification(CString& strCommandName,
									   bool fMacro)
						: CImpICommand (strCommandName, fMacro)
{
}

CImpINotification :: ~CImpINotification()
{                
}                                                     

HRESULT CImpINotification :: FInit()
{
return NOERROR;
}

STDMETHODIMP CImpINotification :: InitCommand()
{
return ResultFromScode(E_NOTIMPL);
}		

STDMETHODIMP CImpINotification :: FireEvent(UINT uiID)
{
return ResultFromScode(E_NOTIMPL);
}		

STDMETHODIMP CImpINotification :: GetDescription(LPSTR strDesc, UINT uiLen, bool &fMacro)
{
	ASSERT(strDesc);

	fMacro = m_fMacro;
	strncpy(strDesc, m_strCommandName, uiLen);  

return NOERROR;
}		

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MENU-INTERFACE-IMPL.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

CImpIMenu* CImpIMenu :: Create(	CString& strCommandName,
								bool fMacro)

{
	CImpIMenu* pIMenu = new CImpIMenu(strCommandName, fMacro);
	if (NULL == pIMenu)	return NULL;		

	HRESULT hr = pIMenu -> FInit(); 
	if (FAILED(hr)) {
		delete pIMenu;
		return NULL;
	}

	pIMenu -> AddRef();

return  pIMenu;
}


CImpIMenu :: CImpIMenu()
			: CImpICommand()
{
	AddRef();
}                                                     

CImpIMenu :: CImpIMenu(	CString& strCommandName, 
						bool fMacro)
			: CImpICommand(strCommandName, fMacro)
{
}

CImpIMenu :: ~CImpIMenu()
{                
}                                                     

HRESULT CImpIMenu :: FInit()
{
return NOERROR;
}

STDMETHODIMP CImpIMenu :: GetDescription(LPSTR strDesc, UINT uiLen, bool &fMacro) 
{
	ASSERT(strDesc);

	fMacro = m_fMacro;
	strncpy(strDesc, m_strCommandName, uiLen);  

return NOERROR;	
} 

STDMETHODIMP CImpIMenu :: InitCommand(void)
{                                    
return ResultFromScode(E_NOTIMPL);	
}

LPUNKNOWN CImpIMenu :: GetMacroScripts()
{	
return ((CMacroScriptExtension *)g_pTE) -> GetMacroScripts();
}

STDMETHODIMP CImpIMenu :: FireEvent(UINT uiID)
{
CebInstance *pebInst = NULL;
WScriptContainer ISC = GetMacroScripts();

HRESULT hr = (ISC -> GetebInst(&pebInst));
	if (FAILED(hr)) return hr;
	
	hr = RunThread(ISC, pebInst, m_strCommandName, false);
	if (FAILED(hr)) return hr;
 
return NOERROR;	
}		

STDMETHODIMP CImpIMenu :: GetClassID(CLSID *pClassID)
{
	*pClassID = CLSID_MenuCommand;
	return NOERROR;
}

STDMETHODIMP CImpIMenu :: Load (os_bstream *pstream)
{
	ASSERT (pstream);
// erst Basisklasse
	os_read (*pstream, (CImpICommand &)(*this));

return NOERROR;
}

STDMETHODIMP CImpIMenu :: Save (os_bstream *pstream)
{
	ASSERT (pstream);
// erst Basisklasse
	os_write (*pstream, (const CImpICommand &)(*this));

return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// WNDNOTIFICATION-INTERFACE-IMPL.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

CImpIWndNotification* CImpIWndNotification :: Create(CString& strCommandName,
													 bool fMacro)
{
	CImpIWndNotification* pIWndNot = new CImpIWndNotification(strCommandName, fMacro);
	if (NULL == pIWndNot)	return NULL;		

	HRESULT hr = pIWndNot -> FInit(); 
	if (FAILED(hr)) {
		delete pIWndNot;
		return NULL;
	}

	pIWndNot -> AddRef();

return  pIWndNot;
}
		
CImpIWndNotification :: CImpIWndNotification(CString& strCommandName,
											 bool fMacro)
							: CImpICommand(strCommandName, fMacro) 
{
}

HRESULT CImpIWndNotification :: FInit()
{
return NOERROR;
}

CImpIWndNotification :: ~CImpIWndNotification()
{                
}                                                     

STDMETHODIMP CImpIWndNotification :: GetDescription(LPSTR strDesc, UINT uiLen, bool &fMacro) 
{
	ASSERT(strDesc);

	fMacro = m_fMacro;
	strncpy(strDesc, m_strCommandName, uiLen);  

return NOERROR;	
} 

STDMETHODIMP CImpIWndNotification :: InitCommand(void)
{                                    
return ResultFromScode(E_NOTIMPL);	
}

STDMETHODIMP CImpIWndNotification :: FireEvent(UINT uiID)
{
return ResultFromScode(E_NOTIMPL);	
}		


/// ///////////////////////////////////////////////////////////////////////////////
// *** in Basisklasse eingebettete Klasse 
/// ///////////////////////////////////////////////////////////////////////////////

CImpICommand :: XPersistBStream :: XPersistBStream (CImpICommand *pParent)
{
	ASSERT (pParent);
	m_pParent = pParent;
}

// alle methods delegiert 

// *** IUnknown methods -------------------------------------------------------
STDMETHODIMP CImpICommand :: XPersistBStream :: QueryInterface (REFIID riid, LPVOID *ppvObj)
{
return m_pParent -> QueryInterface (riid, ppvObj);
}

STDMETHODIMP_(ULONG) CImpICommand :: XPersistBStream :: AddRef (void)
{
return m_pParent -> AddRef();
}

STDMETHODIMP_(ULONG) CImpICommand :: XPersistBStream :: Release (void)
{
return m_pParent -> Release();
}

// *** IPersistBStream methods -------------------------------------------------------
STDMETHODIMP CImpICommand :: XPersistBStream :: GetClassID(CLSID *pClassID)
{
return m_pParent -> GetClassID(pClassID);
}

STDMETHODIMP CImpICommand  :: XPersistBStream :: Load (os_bstream *pstream)
{
	ASSERT(pstream);
return m_pParent -> Load(pstream);
}

STDMETHODIMP CImpICommand :: XPersistBStream :: Save (os_bstream *pstream)
{
	ASSERT(pstream);
return m_pParent -> Save (pstream); 
}
