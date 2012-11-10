
#include "stdafx.h"
#include "resource.h"

DefineSmartInterface(Stream);

// GUIDS
#include "objmanguid.h"
#include "macrguid.h"
#include "iobjmex.h"
#include <iObjMan.h>

#include "enumex.h"
#include "ObjMn.h"

// SmartInterfaces
DefineSmartInterface(Moniker);
DefineSmartInterface(PersistStream);
DefineSmartEnumerator2(os_wstring, IID_IEnumos_wstring);


/*
 * Purpose:
 *  Returns the CLSID of the object represented by this interface.
 *
 * Parameters:
 *  pClsID          LPCLSID in which to store our CLSID.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CObjectManagement::GetClassID(LPCLSID pClsID)
{
	// Setzt den Modulstatus der MFC.dll auf diese DLL
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (PSSTATE_UNINIT == m_iState)
		return E_UNEXPECTED;
	
return NOERROR;
}
/*
 * CObjectManagement::IsDirty
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

STDMETHODIMP CObjectManagement::IsDirty(void)
{                                      
	// Setzt den Modulstatus der MFC.dll auf diese DLL
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	if (PSSTATE_UNINIT == m_iState)
		return E_UNEXPECTED;

return m_fIsDirty ? S_OK : S_FALSE;
}

/*
 * CObjectManagement::InitNew
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

STDMETHODIMP CObjectManagement::InitNew(LPSTORAGE pIStorage)
{                            
	// Setzt den Modulstatus der MFC.dll auf diese DLL
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (PSSTATE_UNINIT != m_iState)
		return E_UNEXPECTED;

// wenn schon geöffnet, nicht Weiteres öffnen (low memory situation ?) 
	if (NULL != m_lpIStorage)
		return E_UNEXPECTED;
		
	if (NULL == pIStorage) 
		return STG_E_INVALIDPOINTER;

	m_lpIStorage = pIStorage; 

	m_lpIStorage -> AddRef();	// Release() im ~

// Schreibmodus, schreiben erlaubt 
	m_iState = PSSTATE_WRITE;

return NOERROR;
}

/*
 * CObjectManagement::Load
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
STDMETHODIMP CObjectManagement::Load(LPSTORAGE pIStorage)
{	
	// Setzt den Modulstatus der MFC.dll auf diese DLL
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	ASSERT(NULL != pIStorage);

HRESULT hr_global = S_OK;

	COM_TRY {
		if (NULL == pIStorage) 
			_com_issue_error(STG_E_INVALIDPOINTER);	// Root NULL
	
	// nicht initialisieren, wenn schon geöffnet, nicht Weiteres öffnen
		if (PSSTATE_UNINIT != m_iState || NULL != m_lpIStorage)
			_com_issue_error(E_UNEXPECTED); 

	// auf jeden Fall den StorageInhaltsStream öffen bzw. erzeugen
	HRESULT hr = OpenStream (IDS_STORAGEMANAGEMENTSTREAM, pIStorage, &m_lpIStreamStorageContents);

		if (SUCCEEDED(hr)) // Streamnamen vom Inhaltsstream lesen
			hr = Load (m_lpIStreamStorageContents);
		else {	
		// Inhaltsstream nicht vorhanden, kreieren
			THROW_FAILED_HRESULT(CreateStream (IDS_STORAGEMANAGEMENTSTREAM, pIStorage, &m_lpIStreamStorageContents));

		// Streams vom Storage -> EnumElements() enumerieren lassen
			hr = EnumElements(pIStorage);
		}

	// Kein Streamelement vorhanden
		if (S_FALSE == hr) 
			hr_global = S_FALSE;
		else
		{
			THROW_FAILED_HRESULT(hr);
		}
	} COM_CATCH;

// Schreibmodus
	if (S_OK == hr_global) {
		m_lpIStorage = pIStorage; // Release() im ~
		m_lpIStorage -> AddRef();
		m_iState = PSSTATE_WRITE;
	}
	return hr_global;
}

/*
 * CObjectManagement::Save
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

STDMETHODIMP CObjectManagement::Save(LPSTORAGE pIStorage, BOOL fSameAsLoad)
{
	// Setzt den Modulstatus der MFC.dll auf diese DLL
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	// nur Schreibzugriff möglich
	if (PSSTATE_WRITE != m_iState) return E_UNEXPECTED;
	if (NULL == pIStorage && !fSameAsLoad) return E_POINTER;
 
HRESULT hr = NOERROR;
HRESULT hrWasDirty = NOERROR;

	try {
	// Erstmal die Dirty-Objekte wegschreiben
	HRESULT hr1 = SaveDirtyObjects();
	
	// Dirty-Objekte ? 		
		hrWasDirty = IsDirty();
		if (S_OK == hrWasDirty) 	// wurden welche gesaved
		{
		// Liste wegschreiben mit Hilfe IPersistStream
			hr = Save (m_lpIStreamStorageContents, true);
			if (FAILED(hr)) _com_issue_error(hr);
		
			m_fIsDirty = false;		// Speichern abgeschlossen
		}
		if (FAILED(hr1))	// Streamcontents immer speichern
			_com_issue_error(hr1);
		
	// Sollte der gleiche Storage zum Speichern wie beim Laden genutzt werden, dann 
		if (!fSameAsLoad && m_lpIStorage) {
		//  SaveAs() oder Kopie speichern, Storage vielleicht schon zerstoert (war leer)
			hr = m_lpIStorage -> CopyTo (0, NULL, NULL, pIStorage);
			if (FAILED(hr)) _com_issue_error(hr);
		} 
		else {
			if (pIStorage != m_lpIStorage && pIStorage != NULL) 
				_com_issue_error(E_POINTER);
		}

	// Schreiben bis SaveCompleted() verboten !
		m_iState = PSSTATE_ZOMBIE;
	}
	catch (_com_error& e) {
		hr = _COM_ERROR(e);
	}

// hr2 zurück, damit Commit() gemacht werden kann, wenn Speicherung stattgefunden hat
	return hrWasDirty;
}

HRESULT CObjectManagement::SaveDirtyObjects()
{
HRESULT hr = NOERROR;

	USES_CONVERSION;
	try {
		WUnknown IU;
		HRESULT hr = EnumStrings(IU.ppi());
		if (FAILED(hr)) _com_issue_error(hr);
		
		WEnumos_wstring IE(IU);
		os_wstring oswstr;
		
		while (S_OK == IE -> Next(1, &oswstr, NULL)) 
		{
			HRESULT hres = SaveObject(CComBSTR(oswstr.c_str()));
			if (FAILED(hres)) hr = hres;
		}
		if (FAILED(hr)) _com_issue_error(hr);
	}
	catch (_com_error& e) {
		hr = _COM_ERROR(e);
	}
	return hr;
}
/*
 * CObjectManagement::SaveCompleted
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

STDMETHODIMP CObjectManagement::SaveCompleted(LPSTORAGE pIStorage)
{
// Setzt den Modulstatus der MFC.dll auf diese DLL
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (m_iState == PSSTATE_UNINIT || m_iState == PSSTATE_WRITE)	
		return E_UNEXPECTED;

// kann nicht zum Schreiben auf Storage freigegeben werden, da StoragePointer
// NULL	nach HandsOffStorage()
	if (NULL == pIStorage && PSSTATE_HANDSOFF == m_iState) 
		return E_POINTER;

HRESULT hr = NOERROR;

// Nur freigeben, wenn anderer Storage zum Speichern übergeben wurde
	USES_CONVERSION;
	if (pIStorage != NULL) {
	// Wenn nicht vorher schon HandsOffStorage() jetzt simulieren
		if (m_iState != PSSTATE_HANDSOFF) 
		// letztes Geöffnetes war noch nicht in der Liste und wurde zwischendurch nicht gespeichert
			Reset (false);

	// Enum Released, neuen Enum erzeugen
		RETURN_FAILED_HRESULT(CreateEnum (false));

	// StoragecontentsStream, Released
	// auf jeden Fall den StorageInhaltsStream öffen bzw. kreieren
		hr = OpenStream (IDS_STORAGEMANAGEMENTSTREAM, pIStorage, &m_lpIStreamStorageContents);
		if (SUCCEEDED(hr))		// Streamnamen vom Inhaltsstream lesen
			hr = ReLoad (pIStorage, m_lpIStreamStorageContents);
		else 
			hr = CreateStream (IDS_STORAGEMANAGEMENTSTREAM, pIStorage, &m_lpIStreamStorageContents);

		if (SUCCEEDED(hr)) {
		// Streamnamen vom Inhaltsstream lesen
			m_lpIStorage = pIStorage;
			m_lpIStorage -> AddRef();
		}
	}

// Wieder zum Schreiben freigeben
	m_iState = PSSTATE_WRITE;
	return hr;
}

/*
 * CObjectManagement::HandsOffStorage
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

STDMETHODIMP CObjectManagement::HandsOffStorage(void)
{
// Setzt den Modulstatus der MFC.dll auf diese DLL
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

// erst wieder nach SaveCompleted() Zugriff möglich
	if (m_iState == PSSTATE_UNINIT || m_iState == PSSTATE_HANDSOFF)
		return E_UNEXPECTED;

// Storage freigeben
	Reset(false);

// Schreiben bis SaveCompleted() verboten !
	m_iState = PSSTATE_HANDSOFF;
	return NOERROR;
}

HRESULT CObjectManagement::EnumElements(LPSTORAGE pIStorage)
{        
	ASSERT(pIStorage);

LPENUMSTATSTG penumStatStg = NULL;
bool fStreamFound = false;
STATSTG stat;   

	USES_CONVERSION;
	try {
	// Streams und Storageelemente enumerieren
		THROW_FAILED_HRESULT(pIStorage -> EnumElements (0, 0, 0, &penumStatStg));

	CString str;	// Managementstream nicht eintragen

		THROW_FAILED_HRESULT(LoadString(str, IDS_STORAGEMANAGEMENTSTREAM));

		while (S_OK == penumStatStg -> Next (1, &stat, 0)) {
			if (STGTY_STREAM != stat.type || str == stat.pwcsName || *(stat.pwcsName) < L' ') 
				continue; 

		///////////////////////////////////////////////////////////////
		// Diese Schritte sind notwendig, um auch alte Storages, 
		// erzeugt mit älterer Version, laden zu können
			THROW_FAILED_HRESULT(SetLoad(stat.pwcsName));	// Namen setzen

		// Moniker erzeugen, bei alter Version immer ItemMoniker !!!
		WMoniker IMon;

			THROW_FAILED_HRESULT(CreateItemMoniker(L"!", stat.pwcsName, IMon.ppi()));
			THROW_FAILED_HRESULT(SetMoniker(stat.pwcsName, IMon));	// Moniker setzen
	
			if (stat.pwcsName) 
				CoTaskMemFree (stat.pwcsName);
			fStreamFound = true;
		}
	}
	catch (_com_error &e) {
		if (stat.pwcsName) CoTaskMemFree (stat.pwcsName);
		if (penumStatStg) penumStatStg -> Release(); penumStatStg = NULL;// von EnumElements()
		return _COM_ERROR(e);
	}

	if (penumStatStg) {
		penumStatStg -> Release(); 
		penumStatStg = NULL;		// von EnumElements()
	}
	return fStreamFound ? S_OK : S_FALSE;        
}         
        
