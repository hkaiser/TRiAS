#include "bscriptp.hxx"
#include "bscript.h"

#include "macrguid.h"                  
#include "imacorg.h"
#include "imacro.h"

#include <ospace/source.h>

#include "myenum.h"
#include "listitem.h"
#include "commsi.h"
#include "procimp.h"
#include "analimp.h"
#include "anpasimp.h"

#include "stghelp.hxx"

#include "saveimp.h"

#include "macroorg.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SAVEINTERFACEIMP.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

CImpISave* CImpISave :: Create(LPUNKNOWN pUnkOuter, CMacroOrg* pMacroOrg)
{
	if (pUnkOuter == NULL)
		return NULL;

	CImpISave* pISave = new CImpISave(pUnkOuter, pMacroOrg);
	if (NULL == pISave)	return NULL;		

	HRESULT hr = pISave -> FInit(); 
	if (FAILED(hr)) {
		delete pISave;
		return NULL;
	}

return  pISave;
}
		
CImpISave :: CImpISave(LPUNKNOWN pUnkOuter, CMacroOrg* pMacroOrg)
{
	m_cRef=0;

	m_pUnkOuter = pUnkOuter;
	m_pMacroOrg = pMacroOrg;
	
	m_pISubStorage = NULL;
	m_pIStream = NULL;

	m_fIsDirty = false;
	m_iState = PSSTATE_UNINIT;
}

CImpISave :: ~CImpISave()
{   
DWORD dw = 0;
	if (m_pIStream) dw = m_pIStream -> Release();
	ASSERT (dw==0);
	m_pIStream = NULL;

	if (m_pISubStorage) dw = m_pISubStorage -> Release();
	ASSERT (dw==0);
	m_pISubStorage = NULL;
}                                                     

HRESULT CImpISave :: FInit()
{
return NOERROR;	
}                                         


LPIMPICOMMANDS CImpISave :: GetCommands(void)
{
return m_pMacroOrg -> GetCommands();
}

STDMETHODIMP CImpISave :: DestroyStorage(int IDS)
{
LPSTORAGE pIRootStorage = NULL;
	if(NULL == m_pISubStorage || !DEX_GetProjectStorage (pIRootStorage)) return ResultFromScode(S_FALSE);

CString strStorName;
	TRY {
		if (0 == strStorName.LoadString(IDS)) {
			return ResultFromScode(E_FAIL);
		}
	}
	CATCH ( CMemoryException, e ) {	
		AfxMessageBox (IDS_NOMEMORY);
		return ResultFromScode(E_FAIL);
	}
	END_CATCH

HRESULT hr = NOERROR;

LPSTREAM pIStream = NULL;
DWORD dwMode = STGM_DIRECT | STGM_READWRITE | STGM_SHARE_EXCLUSIVE; 

// wenn kein Stream vorhanden ,
	USES_CONVERSION;
	hr = m_pISubStorage -> OpenStream(A2OLE(strStorName), 0, dwMode, 0, &pIStream);
	if (GetScode(hr) == STG_E_FILENOTFOUND) {
// SubStorage löschen
		hr = HandsOffStorage();
		if(FAILED(hr)) return hr;

		hr = pIRootStorage -> DestroyElement(A2OLE(strStorName));
	}
	else if(pIStream) pIStream -> Release();

	pIRootStorage -> Release();

return hr;
}

// Laden vom File ALTES PROJEKT
STDMETHODIMP CImpISave :: LoadFile()
{
LPIMPICOMMANDS pCs = GetCommands();
	if (NULL == pCs) return ResultFromScode(E_FAIL);
	
HRESULT	hr = pCs -> LoadFile();
	pCs -> Release();

return hr;
}

//Speichern in File ALTES PROJEKT
STDMETHODIMP CImpISave :: SaveFile()
{
LPIMPICOMMANDS pCs = GetCommands();
	if (NULL == pCs) return ResultFromScode(E_FAIL);
	
HRESULT hr = pCs -> SaveFile();
	pCs -> Release();

return hr;
}

// wenn Menü laden von außen gerufen wird, Menühandle der Extensions bekannt
STDMETHODIMP CImpISave :: InsertMenu(HMENU hMenu)
{
LPIMPICOMMANDS pCs = GetCommands();
	if (NULL == pCs) return ResultFromScode(E_FAIL);

HRESULT hr = pCs -> InsertMenu(hMenu, NULL);	
	pCs -> Release();

return hr;
}

//
// *** IUnknown methods -------------------------------------------------------
//

STDMETHODIMP CImpISave :: QueryInterface (REFIID riid, LPVOID *ppvObj)
{
return m_pUnkOuter -> QueryInterface (riid, ppvObj);
}

STDMETHODIMP_(ULONG) CImpISave :: AddRef (void)
{
    ++m_cRef;
return m_pUnkOuter -> AddRef ();
}

STDMETHODIMP_(ULONG) CImpISave :: Release (void)
{                               
    --m_cRef;
return m_pUnkOuter -> Release ();
}

//
// *** IPersistStorage methods -------------------------------------------------------
//

STDMETHODIMP CImpISave   :: GetClassID(LPCLSID pClsID)
{
	if (PSSTATE_UNINIT == m_iState)
		return ResultFromScode (E_UNEXPECTED);

		*pClsID = CLSID_ListItem; // noch anderen ID zuweisen
		
return NOERROR;
}

STDMETHODIMP CImpISave   :: IsDirty(void)
{                                      
	if (PSSTATE_UNINIT == m_iState)
		return ResultFromScode (E_UNEXPECTED);

return ResultFromScode(m_fIsDirty ? S_OK : S_FALSE);
}

STDMETHODIMP CImpISave   :: InitNew(LPSTORAGE pIStorage)
{                            
	ASSERT(pIStorage);

// wenn schon geöffnet, nicht Weiteres öffnen (low memory situation ?) 
	if (PSSTATE_UNINIT != m_iState || NULL != m_pISubStorage)
		return ResultFromScode (E_UNEXPECTED);

	m_pISubStorage = pIStorage; 
	m_pISubStorage -> AddRef();	// Release() im ~

// Schreibmodus, schreiben erlaubt 
	m_iState = PSSTATE_WRITE;

return ResultFromScode(S_FALSE);
}

HRESULT CImpISave :: Create(LPSTORAGE pIStorage, LPSTREAM *ppIStream, LPCSTR pName)
{
	ASSERT (pIStorage);
	ASSERT (pName);

// schon geöffnet ?	
	if (*ppIStream != NULL) return NOERROR;
	
DWORD dwMode = STGM_DIRECT | STGM_READWRITE | STGM_SHARE_EXCLUSIVE; 
	USES_CONVERSION;
HRESULT hr = pIStorage -> CreateStream (A2OLE(pName), dwMode, 0, 0, ppIStream);
	if (FAILED(hr)) return hr;
		
ULARGE_INTEGER lib; lib.LowPart = 50000; lib.HighPart = 0; 
	hr = (*ppIStream) -> SetSize(lib);
	if (FAILED(hr)) return hr;

return hr;
}

HRESULT CImpISave :: Open(LPSTORAGE pIStorage, LPSTREAM *ppIStream, LPCSTR pName)
{
	ASSERT (pIStorage);
	ASSERT (pName);
DWORD dwMode = STGM_DIRECT | STGM_READWRITE | STGM_SHARE_EXCLUSIVE; 
// Öffnen des Streams                     
// AddRef() innerhalb der Funktion
	USES_CONVERSION;
HRESULT hr = pIStorage -> OpenStream (A2OLE(pName), 0, dwMode, 0, ppIStream);
	if (FAILED(hr)) return hr; 
	
return hr;
}

HRESULT CImpISave :: OpenStream(LPSTORAGE pIStorage)
{
	ASSERT (pIStorage);
// kein Stream vorhanden
	if(m_pIStream == NULL) return ResultFromScode(S_FALSE);

HRESULT hr = NOERROR; 
CString str;

	TRY {
		if (0 == str.LoadString(IDS_STORAGE_NAME_MENUITEMS))
			return ResultFromScode(E_FAIL);
	}
	CATCH ( CMemoryException, e ) {	
		AfxMessageBox (IDS_NOMEMORY);
	}
	END_CATCH

	try {
	WPersistStream IPStream (GetCommands());	// throws hr
	LARGE_INTEGER li;

		LISet32 (li, 0);
		THROW_FAILED_HRESULT(m_pIStream -> Seek (li, STREAM_SEEK_SET, NULL));
		THROW_FAILED_HRESULT(IPStream -> Load (m_pIStream));

	} catch (HRESULT hr) {
		return hr;
	}

return hr;
}

HRESULT CImpISave :: OpenStreamOnly(LPSTORAGE pIStorage)
{
	ASSERT (pIStorage);
	ASSERT(m_pIStream==NULL);

HRESULT hr = NOERROR; 
CString str;

	TRY {
		if (0 == str.LoadString(IDS_STORAGE_NAME_MENUITEMS))
			return ResultFromScode(E_FAIL);
	}
	CATCH ( CMemoryException, e ) {	
		AfxMessageBox (IDS_NOMEMORY);
	}
	END_CATCH

LPSTREAM pIStream = NULL;
// m_pIStream -> AddRef();

	hr = Open(pIStorage, &pIStream, (LPCSTR)str);
	if (FAILED(hr)) return hr;

	m_pIStream = pIStream;

return hr;
}

STDMETHODIMP CImpISave :: LoadFromStorage()
{	
	ASSERT(m_pISubStorage);
// return S_FALSE, wenn neuer Stream
return OpenStream(m_pISubStorage);	
}

STDMETHODIMP CImpISave :: SaveToStorage(bool fClearDirty)
{
HRESULT hr = NOERROR; 
CString str;
	TRY {
		if (0 == str.LoadString(IDS_STORAGE_NAME_MENUITEMS))
			return ResultFromScode(E_FAIL);
	}
	CATCH ( CMemoryException, e ) {	
		AfxMessageBox (IDS_NOMEMORY);
	}
	END_CATCH;

// wenn Stream nicht geöffnet, m_pIStream -> AddRef()
	hr = Create(m_pISubStorage, &m_pIStream, (LPCSTR)str);
	if (FAILED(hr)) return hr;

	try {
	WPersistStream IPStream (GetCommands());	// throws hr
	LARGE_INTEGER li;

		LISet32 (li, 0);
		THROW_FAILED_HRESULT(m_pIStream -> Seek (li, STREAM_SEEK_SET, NULL));
		THROW_FAILED_HRESULT(IPStream -> Save(m_pIStream, fClearDirty));

	} catch (HRESULT hr) {
		return hr;
	}

return hr;
}

STDMETHODIMP CImpISave   :: Load(LPSTORAGE pIStorage)
{	
	ASSERT(pIStorage);

// wenn schon geöffnet, nicht Weiteres öffnen (low memory situation ?) 
	if (PSSTATE_UNINIT != m_iState || NULL != m_pISubStorage)
		return ResultFromScode (E_UNEXPECTED);

// versuchen, immer Stream zu öffnen
HRESULT hr = OpenStreamOnly(pIStorage);	 
	if(FAILED(hr)) return hr; 

	m_pISubStorage = pIStorage;	
	m_pISubStorage -> AddRef();

// Schreibmodus 
	m_iState = PSSTATE_WRITE;

// return S_FALSE, wenn neuer Stream
return hr;
}

// Speichern NEUES PROJEKT
STDMETHODIMP CImpISave   :: Save(LPSTORAGE pIStorage, BOOL fSameAsLoad)
{
HRESULT hr = NOERROR;	
// nur Schreibzugriff möglich
	if (PSSTATE_WRITE != m_iState)
		return ResultFromScode (E_UNEXPECTED);

	if (NULL == pIStorage && !fSameAsLoad) 
		return ResultFromScode (E_POINTER);
 
	if (!fSameAsLoad) {
//  SaveAs()
		if(m_pISubStorage) hr = m_pISubStorage -> CopyTo( 0, NULL, NULL, pIStorage);
		if (FAILED(hr)) return hr;
	}
// Sollte der gleiche Storage zum Speichern wie beim Laden genutzt werden, dann 
	else {
		if (pIStorage != m_pISubStorage && pIStorage != NULL) 
			return ResultFromScode(E_POINTER);
	}

// Speichern abgeschlossen
	m_fIsDirty = false;
// Schreiben bis SaveCompleted() verboten !
	m_iState = PSSTATE_ZOMBIE;

return hr;
}

STDMETHODIMP CImpISave   :: SaveCompleted(LPSTORAGE pIStorage)
{
	if (m_iState == PSSTATE_UNINIT || m_iState == PSSTATE_WRITE)	
		return ResultFromScode(E_UNEXPECTED);

// kann nicht zum Schreiben auf Storage freigegeben werden, da StoragePointer
// NULL	nach HandsOffStorage()
	if (NULL == pIStorage && 
		PSSTATE_HANDSOFF == m_iState) 
		return ResultFromScode (E_POINTER);

// Nur freigeben, wenn anderer Storage zum Speichern übergeben wurde
	if (pIStorage != NULL) {
// Wenn nicht vorher schon HandsOffStorage()		
// alles freigeben
		if (m_iState != PSSTATE_HANDSOFF) {

		DWORD dw = 0;			
			if(m_pIStream) dw = m_pIStream -> Release();
			ASSERT (dw==0);
			m_pIStream = NULL;

			if(m_pISubStorage) dw = m_pISubStorage -> Release();
			ASSERT (dw==0);
			m_pISubStorage = NULL;
		}

	HRESULT hr = OpenStreamOnly(pIStorage);
		if(FAILED(hr)) return hr; 

// wie InitNew() !!!
		m_pISubStorage = pIStorage;		
// Release() im ~
		m_pISubStorage -> AddRef();
	}

// Wieder zum Schreiben freigeben
	m_iState = PSSTATE_WRITE;

return NOERROR;
}

STDMETHODIMP CImpISave :: HandsOffStorage(void)
{
// erst wieder nach SaveCompleted() Zugriff möglich
	if (m_iState == PSSTATE_UNINIT ||	
			m_iState == PSSTATE_HANDSOFF)
		return ResultFromScode(E_UNEXPECTED);

DWORD dw = 0;
	// Stream freigeben
	if(m_pIStream) dw = m_pIStream -> Release();
	ASSERT (dw==0);
	m_pIStream = NULL;

// Storage freigeben
	if(m_pISubStorage) dw = m_pISubStorage -> Release();
	ASSERT (dw==0);
	m_pISubStorage = NULL;

// Schreiben bis SaveCompleted() verboten !
	m_iState = PSSTATE_HANDSOFF;

return NOERROR;
}


        
        
        
        
        
