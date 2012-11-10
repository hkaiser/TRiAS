
#include "bscriptp.hxx"
#include "bscript.h"		// ResourceKonstanten

#include "macrguid.h"

#include "imacro.h"
                  
#include "enumscpt.h"                  
#include "macrguid.h"                  
#include "strmimp.h"
#include "perstimp.h"
#include "macroimp.h"
#include "macro.h"

// #include "bscripta.h"

/*
 * CImpIPersistStorage:CImpIPersistStorage
 * CImpIPersistStorage::~CImpIPersistStorage
 *
 * Constructor Parameters:
 *  pObj            LPVOID pointing to the object we live in.
 *  pUnkOuter       LPUNKNOWN of the controlling unknown.
 */

CImpIPersistStorage::CImpIPersistStorage(LPUNKNOWN pUnkOuter, CMacroScripts *pMacroScripts)
{
#if defined(_DEBUG)
	m_cRef = 0;
#endif // _DEBUG

	m_pUnkOuter = pUnkOuter;

	m_pMacroScripts = pMacroScripts;
	m_pISubStorage = NULL;

	m_fIsDirty = false;
	m_iState = PSSTATE_UNINIT;
}


CImpIPersistStorage::~CImpIPersistStorage(void)
{
DWORD dw = 0; 
	if(m_pISubStorage) dw = m_pISubStorage -> Release();
	ASSERT (dw==0);
	m_pISubStorage = NULL;
}

/*
 * CImpIPersistStorage::QueryInterface
 * CImpIPersistStorage::AddRef
 * CImpIPersistStorage::Release
 *
 * Purpose:
 *  Delegating IUnknown members for CImpIPersistStorage.
 */

STDMETHODIMP CImpIPersistStorage::QueryInterface(REFIID riid , LPVOID FAR *ppv)
{
return m_pUnkOuter->QueryInterface(riid, ppv);
}

STDMETHODIMP_(ULONG) CImpIPersistStorage::AddRef(void)
{
#if defined(_DEBUG)
	++m_cRef;
#endif // _DEBUG

return m_pUnkOuter->AddRef();
}

STDMETHODIMP_(ULONG) CImpIPersistStorage::Release(void)
{
#if defined(_DEBUG)
	--m_cRef;
#endif // _DEBUG

return m_pUnkOuter->Release();
}
/*
 * CImpIPersistStorage::GetClassID
 *
 * Purpose:
 *  Returns the CLSID of the object represented by this interface.
 *
 * Parameters:
 *  pClsID          LPCLSID in which to store our CLSID.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIPersistStorage::GetClassID(LPCLSID pClsID)
{
	if (PSSTATE_UNINIT == m_iState)
		return ResultFromScode (E_UNEXPECTED);

	if (m_pMacroScripts != NULL)
		*pClsID = CLSID_ScriptContainer;	
	else {
		ASSERT(m_pMacroScripts);
		return ResultFromScode (STG_E_INVALIDPOINTER);
	}
	
return NOERROR;
}
/*
 * CImpIPersistStorage::IsDirty
 *
 * Purpose:
 *  Tells the caller if we have made changes to this object since
 *  it was loaded or initialized new.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  HRESULT         Contains S_OK if we ARE dirty, S_FALSE if
 *                  NOT dirty.
 */

STDMETHODIMP CImpIPersistStorage::IsDirty(void)
{                                      
	if (PSSTATE_UNINIT == m_iState)
		return ResultFromScode (E_UNEXPECTED);

return ResultFromScode(m_fIsDirty ? S_OK : S_FALSE);
}

/*
 * CImpIPersistStorage::InitNew
 *
 * Purpose:
 *  Provides the object with the IStorage to hold on to while the
 *  object is running.  Here we initialize the structure of the
 *  storage and AddRef it for incremental access. This function will
 *  only be called once in the object's lifetime in lieu of Load.
 *
 * Parameters:
 *  pIStorage       LPSTORAGE for the object.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIPersistStorage::InitNew(LPSTORAGE pIStorage)
{                            
	if (PSSTATE_UNINIT != m_iState)
		return ResultFromScode (E_UNEXPECTED);

// wenn schon geöffnet, nicht Weiteres öffnen (low memory situation ?) 
	if (NULL != m_pISubStorage)
		return ResultFromScode(E_UNEXPECTED);
		
	if (NULL == pIStorage) 
		return ResultFromScode(STG_E_INVALIDPOINTER);

	m_pISubStorage = pIStorage; 

	m_pISubStorage -> AddRef();	// Release() im ~

// Schreibmodus, schreiben erlaubt 
	m_iState = PSSTATE_WRITE;

return NOERROR;
}

/*
 * CImpIPersistStorage::Load
 *
 * Purpose:
 *  Instructs the object to load itself from a previously saved
 *  IStorage that was handled by Save in another object lifetime.
 *  This function will only be called once in the object's lifetime
 *  in lieu of InitNew. The object should hold on to pIStorage here
 *  for incremental access and low-memory saves in Save.
 *
 * Parameters:
 *  pIStorage       LPSTORAGE from which to load.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */
STDMETHODIMP CImpIPersistStorage::Load(LPSTORAGE pIStorage)
{	
	if (PSSTATE_UNINIT != m_iState)
		return ResultFromScode (E_UNEXPECTED);
// wenn schon geöffnet, nicht Weiteres öffnen (low memory situation ?) 
	if (NULL != m_pISubStorage)
		return ResultFromScode(E_UNEXPECTED);

	if (NULL == pIStorage) {
		ASSERT(pIStorage);
		return ResultFromScode(STG_E_INVALIDPOINTER);
	}

HRESULT hr = EnumElements(pIStorage);
	if (FAILED(hr)) return hr;
	if(GetScode(hr) == S_FALSE) return ResultFromScode (S_FALSE);
	
	m_pISubStorage = pIStorage;
// Release() im ~
	m_pISubStorage -> AddRef();

// Schreibmodus 
	m_iState = PSSTATE_WRITE;

return NOERROR;
}

/*
 * CImpIPersistStorage::Save
 *
 * Purpose:
 *  Saves the data for this object to an IStorage which may
 *  or may not be the same as the one previously passed to
 *  Load, indicated with fSameAsLoad.  After this call we may
 *  not write into the storage again until SaveCompleted is
 *  called, although we may still read.
 *
 * Parameters:
 *  pIStorage       LPSTORAGE in which to save our data.
 *  fSameAsLoad     BOOL indicating if this is the same pIStorage
 *                  that was passed to Load.  If TRUE, then the
 *                  object should write whatever it has *without
 *                  *using any extra memory* as this may be a low
 *                  memory save attempt.  That means that you must
 *                  not try to open or create streams.  If FALSE
 *                  you need to regenerate your whole storage
 *                  structure, being sure to also release any
 *                  pointers held from InitNew and Load.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIPersistStorage::Save(LPSTORAGE pIStorage, BOOL fSameAsLoad)
{
HRESULT hr = NOERROR;	
// nur Schreibzugriff möglich
	if (PSSTATE_WRITE != m_iState)
		return ResultFromScode (E_UNEXPECTED);

	if (NULL == pIStorage && !fSameAsLoad) 
		return ResultFromScode (E_POINTER);
 
// Sollte der gleiche Storage zum Speichern wie beim Laden genutzt werden, dann 
	if (!fSameAsLoad) {
//  SaveAs() oder Kopie speichern, Storage vielleicht schon zerstoert (war leer)
		if(m_pISubStorage) hr = m_pISubStorage -> CopyTo( 0, NULL, NULL, pIStorage);
		if (FAILED(hr)) return hr;
	}
	else 
		if (pIStorage != m_pISubStorage && pIStorage != NULL) 
			return ResultFromScode(E_POINTER);
// Speichern abgeschlossen
	m_fIsDirty = false;
// Schreiben bis SaveCompleted() verboten !
	m_iState = PSSTATE_ZOMBIE;

return hr;
}
/*
 * CImpIPersistStorage::SaveCompleted
 *
 * Purpose:
 *  Notifies the object that the storage in pIStorage has been
 *  completely saved now.  This is called when the user of this
 *  object wants to save us in a completely new storage, and if
 *  we normally hang on to the storage we have to reinitialize
 *  ourselves here for this new one that is now complete.
 *
 * Parameters:
 *  pIStorage       LPSTORAGE of the new storage in which we live.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIPersistStorage::SaveCompleted(LPSTORAGE pIStorage)
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
	CEnumMacroScripts *pEn = NULL;

		if (m_iState != PSSTATE_HANDSOFF) {
			
		DWORD dw = 0;
			if(m_pISubStorage) dw = m_pISubStorage -> Release();
			ASSERT (dw==0);
			m_pISubStorage = NULL;

		HRESULT hr = m_pMacroScripts -> GetEnum (&pEn);
			if (FAILED(hr)) 
				return hr;
			pEn -> ReleaseStreams();
			pEn -> Release();
		}

	HRESULT hr = EnumElements(pIStorage);
		if (FAILED(hr)) return hr;

// wie InitNew() !!!
		m_pISubStorage = pIStorage;
// Release() im ~
		m_pISubStorage -> AddRef();
	}

// Wieder zum Schreiben freigeben
	m_iState = PSSTATE_WRITE;

return NOERROR;
}
/*
 * CImpIPersistStorage::HandsOffStorage
 *
 * Purpose:
 *  Instructs the object that another agent is interested in having
 *  total access to the storage we might be hanging on to from
 *  InitNew or SaveCompleted.  In this case we must release our hold
 *  and await another call to SaveCompleted before we have a hold
 *  again.  Therefore we cannot read or write after this call until
 *  SaveCompleted.
 *
 *  Situations where this might happen arise in compound document
 *  scenarios where this object might be in-place active but the
 *  application wants to rename and commit the root storage.
 *  Therefore we are asked to close our hold, let the container
 *  party on the storage, then call us again later to tell us the
 *  new storage we can hold.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIPersistStorage::HandsOffStorage(void)
{
// erst wieder nach SaveCompleted() Zugriff möglich
	if (m_iState == PSSTATE_UNINIT ||	
			m_iState == PSSTATE_HANDSOFF)
		return ResultFromScode(E_UNEXPECTED);

CEnumMacroScripts *pEn = NULL;
HRESULT hr = m_pMacroScripts -> GetEnum (&pEn);
	if (FAILED(hr) || pEn == NULL) return hr;

// nur Streams freigeben
	pEn -> ReleaseStreams();
// von GetEnum()
	pEn -> Release();

// Storage freigeben
DWORD dw = 0;
	if(m_pISubStorage) dw = m_pISubStorage -> Release();
	ASSERT (dw==0);
	m_pISubStorage = NULL;

// Schreiben bis SaveCompleted() verboten !
	m_iState = PSSTATE_HANDSOFF;

return NOERROR;
}


// sonstiges ------------------------------------------------------------------
HRESULT CImpIPersistStorage::LoadStream (LPSTORAGE pIStorage, char *pMacroName)
{                              
	ASSERT(pIStorage);  
	ASSERT(pMacroName);
// Objekte , die Streams symbolisieren schaffen und in Map laden

DWORD dwMode = STGM_DIRECT | STGM_READWRITE | STGM_SHARE_EXCLUSIVE; 
LPSTREAM pIStream = NULL;

// Öffnen des jeweiligen Streams, ist er vorhanden ?                     
// jeweils AddRef() innerhalb der Funktion

	USES_CONVERSION;
HRESULT hr = pIStorage -> OpenStream (A2OLE(pMacroName), 0, dwMode, 0, &pIStream);
	if (FAILED(hr)) return hr;		
// Stream schliessen
	pIStream -> Release();		

CMacro *pMacro = CMacro::Create (NULL/* conntrolling Unknown */);
	if (NULL == pMacro) return ResultFromScode(E_FAIL); 			

// namen des Streams merken
	pMacro -> GetIMacros() -> SetName(pMacroName);

// AddRef() in AddScript() bzw. SetAt(), Hinzufügen zum Enumerator
	hr = m_pMacroScripts -> AddScript (pMacroName, pMacro);
	if (FAILED(hr)) return hr;		 
// von AddScript()
	pMacro -> Release();
	
return NOERROR;
}
        
HRESULT CImpIPersistStorage::GetStorage (LPSTORAGE *ppIStorage) 
{ 
	if (NULL == m_pISubStorage) {
		*ppIStorage = NULL;
		return ResultFromScode(E_FAIL);
	}

	*ppIStorage = m_pISubStorage;
	(*ppIStorage) -> AddRef();
	
return NOERROR; 
}
        
HRESULT CImpIPersistStorage::EnumElements(LPSTORAGE pIStorage)
{        
STATSTG stat;   
LPENUMSTATSTG penumStatStg;
bool fStreamFound = false;
HRESULT hr = pIStorage -> EnumElements (0, 0, 0, &penumStatStg);
	if (FAILED(hr)) return hr;

	USES_CONVERSION;
	while (S_OK == penumStatStg -> Next (1, &stat, 0)) {
		if (STGTY_STREAM == stat.type) {
			hr = LoadStream (pIStorage, OLE2A(stat.pwcsName));
			CoTaskMemFree (stat.pwcsName);
			if (FAILED(hr)) {
				penumStatStg -> Release();
				return hr;
			}
			fStreamFound= true;
		}
	}

// von EnumElements()
	penumStatStg -> Release();

	if (fStreamFound == false) 
		return ResultFromScode(S_FALSE);       

return NOERROR;        
}         
        
        
        
        
        
