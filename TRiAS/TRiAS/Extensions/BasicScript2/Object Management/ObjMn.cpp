// ObjMn.cpp : Implementation of CObjectManagementApp and DLL registration.

#include "stdafx.h"
#include "resource.h"

#include <new>

#include <Atl/Ciid.h>
#include <eonrguid.h>
#include <ienumobj.hxx>

#include "macrguid.h"
#include "iobjmex.h"

#include <iObjMan.h>
//#include "objman_i.c"

#include "enumex.h"
//#include "timedlg.h"
#include "ObjMn.h"

#if _MSC_VER >= 1100
using std::bad_alloc;
#endif // _MSC_VER >= 1100
 
////////////////////////////////////////////////////////////////////////////
// SmartInterfaces
DefineSmartInterface(Stream);
DefineSmartInterface(PersistFile);
DefineSmartInterface(PersistStream);
DefineSmartInterface(PersistStreamInit);
DefineSmartInterface(ObjectHolder);
DefineSmartInterface(Moniker);
DefineSmartInterface(BindCtx);
DefineSmartInterface(ObjectManagement);

/////////////////////////////////////////////////////////////////////////
// Globale Funktionen

/////////////////////////////////////////////////////////////////////////
// CObjectHolder
CObjectHolder::CObjectHolder()
{
	m_lpStream = NULL;
	m_lpObject = NULL;
	m_strName.Empty();
	m_lpMoniker = NULL;
	m_fCreateTemp = false;
	m_fInitNew = false;
	m_fDelayedDel = false;

	m_cRef = 0;
}

CObjectHolder::~CObjectHolder()
{	// Object schliessen
	ReleaseObject (VARIANT_TRUE);
	if (m_lpMoniker)
		VERIFY(0 == m_lpMoniker -> Release());
	m_lpMoniker = NULL;
}

////////////////////////////////////////////////////
// Properties IObjectHolder
STDMETHODIMP CObjectHolder::SetNew(bool fNew)
{
	m_fInitNew = fNew;
	return S_OK;
}
// zum Object gehöriger Moniker
STDMETHODIMP CObjectHolder::GetNew(bool *pfNew)
{
	*pfNew = m_fInitNew;
	return S_OK;
}	

// Stream7
STDMETHODIMP CObjectHolder::GetStream(LPSTREAM *lplpStream)
{
	if (m_lpStream)
	{
		*lplpStream = m_lpStream;
		(*lplpStream) -> AddRef();
		return S_OK;
	}
	return E_FAIL;
}
STDMETHODIMP CObjectHolder::SetStream(LPSTREAM lpStream)
{
	if (m_lpStream)
		m_lpStream -> Release();
	m_lpStream = NULL;

	if (lpStream)
	{
		m_lpStream = lpStream;
		m_lpStream -> AddRef();
	}

	return S_OK;
}
STDMETHODIMP CObjectHolder::Rename(BSTR bstrNewName)
{
	ASSERT(bstrNewName);

	USES_CONVERSION;

	if (m_strName.IsEmpty()) return E_UNEXPECTED;

	m_strName.Empty();// Name an sich ändern
	m_strName = OLE2A(bstrNewName);
	// StreamName noch ändern
	return S_OK;
}	
// zum Object gehöriger Moniker
STDMETHODIMP CObjectHolder::GetMoniker(LPMONIKER *lplpMon)
{
	if (m_lpMoniker)
	{
		*lplpMon = m_lpMoniker;
		(*lplpMon) -> AddRef();

		return S_OK;
	}

	return E_FAIL;
}	
STDMETHODIMP CObjectHolder::SetMoniker(LPMONIKER lpMon)
{
	if (m_lpMoniker)
		VERIFY(0 == m_lpMoniker -> Release());

	m_lpMoniker = NULL;
	m_lpMoniker = lpMon;
	m_lpMoniker -> AddRef();
	return S_OK;
}

// Name des Objectes
STDMETHODIMP CObjectHolder::GetName(BSTR *pbstrName)
{
CComBSTR bstr (m_strName);

	if (!bstr)
		return E_OUTOFMEMORY;
	*pbstrName = bstr.Detach();
	return S_OK;
}
STDMETHODIMP CObjectHolder::SetName(BSTR bstrName)
{
	USES_CONVERSION;
	m_strName = OLE2A(bstrName);
	
	return S_OK; 
}
// Object an sich
STDMETHODIMP CObjectHolder::GetObject(LPUNKNOWN *lplpUnk)
{
	if (NULL != m_lpObject) {
	// Objekt ist bereits instantiiert
		*lplpUnk = m_lpObject;
		(*lplpUnk) -> AddRef();
		return S_OK;
	}
//	else if (NULL != m_lpMoniker) {
//	// wenn's das erste mal ist, dann dieses Objekt erzeugen
//	HRESULT hr = BindMoniker (m_lpMoniker, 0L, IID_IUnknown, lplpUnk);
//
//		if (FAILED(hr)) 
//			return hr;
//		return SetObject (*lplpUnk);
//	}
	return E_FAIL;
}

// Object schliessen
STDMETHODIMP CObjectHolder::ReleaseObject(VARIANT_BOOL fFullRelease)
{
// Objekt lediglich bei full release freigeben
	if (fFullRelease) {
		if (m_lpObject)
			m_lpObject -> Release();
		m_lpObject  = NULL;
	}

// stream in jedem Fall freigeben
	if (m_lpStream)
		VERIFY(0 == m_lpStream  -> Release());
	m_lpStream = NULL;

	return NOERROR;
}
STDMETHODIMP CObjectHolder::SetDelayedDel()
{// Löschen erst, wenn RefCount == 1
UINT ui = 0;

	if (m_lpObject) {
		m_lpObject -> AddRef();
		ui = m_lpObject -> Release();
	}
	if (ui > 1)
	{
		m_fDelayedDel = true;
		return S_OK;
	}
	m_fDelayedDel = false;
	return S_FALSE;
}
STDMETHODIMP CObjectHolder::GetDelayedDel(bool & fDelayedDel)
{
	fDelayedDel = m_fDelayedDel;
	return NOERROR;
}
STDMETHODIMP CObjectHolder::GetTemporaer(bool & fTemp)
{
	fTemp = m_fCreateTemp;
	return NOERROR;
}
STDMETHODIMP CObjectHolder::SetTemporaer(bool fTemp)
{
	m_fCreateTemp = fTemp;
	return NOERROR;
}

STDMETHODIMP CObjectHolder::SetObject(LPUNKNOWN lpUnk)
{
	if (NULL != m_lpObject)
		VERIFY(0 == m_lpObject -> Release());

	m_lpObject = lpUnk;
	m_lpObject -> AddRef();
	return S_OK; 
}
///////////////////////////////////////////////////////////////////////////////////
// Unknown-Methods
STDMETHODIMP CObjectHolder::QueryInterface (REFIID riid, LPVOID *ppv)
{
	*ppv = NULL;                  
	
	if (IsEqualIID (riid, IID_IUnknown))
		*ppv = (IUnknown *)this;
	else if (IsEqualIID (riid, IID_IObjectHolder))
		*ppv = (IObjectHolder *)this;

	if (NULL != *ppv) 
	{
		LPUNKNOWN(*ppv) -> AddRef();
		return NOERROR;
	}
	return E_NOINTERFACE;
}
STDMETHODIMP_(ULONG) CObjectHolder::AddRef (void)
{
	return ++m_cRef;
}

STDMETHODIMP_(ULONG) CObjectHolder::Release (void)
{               
	if(--m_cRef == 0){
		delete this;
     	return 0;
    }    	
	return m_cRef;
}

/////////////////////////////////////////////////////////////////////////////
// CObjectManagement
CObjectManagement::CObjectManagement()
{// Setzt den Modulstatus der MFC.dll auf diese DLL
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	m_lpIStreamStorageContents = NULL;
	m_lpIStorage = NULL;
	
	m_iState  = PSSTATE_UNINIT;
	m_fIsDirty = false;

	m_pEnumObjects = NULL;
	CreateEnum ();
//	m_pHideTimerDlg =  NULL;

	m_dwVersion = OBJECTMANAGEMENT_VERSION_101;		// erstmal neuere Version annehmen
	//CreateTimer();
}

CObjectManagement::~CObjectManagement()
{// Setzt den Modulstatus der MFC.dll auf diese DLL
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

//	if 	(NULL != m_pHideTimerDlg)
//		m_pHideTimerDlg -> DestroyWindow();
//	DELETE_OBJ(m_pHideTimerDlg);

	Reset();
	TRACE("Object-Management wird entladen\n");
}

HRESULT CObjectManagement::CreateEnum (bool fForceRelease)
{
	if (fForceRelease && m_pEnumObjects) {
		m_pEnumObjects -> Release(); 
		m_pEnumObjects = NULL;
	}

	if (NULL == m_pEnumObjects) {
		ATLTRY(m_pEnumObjects = new CEnumObjects);
		if (NULL == m_pEnumObjects)
			return E_OUTOFMEMORY;
		m_pEnumObjects -> AddRef();
	}
	return NOERROR;
}

STDMETHODIMP CObjectManagement::InterfaceSupportsErrorInfo(REFIID riid)
{
	// Setzt den Modulstatus der MFC.dll auf diese DLL
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (riid == IID_IObjectManagement)
		return S_OK;
	return S_FALSE;
}

//////////////////////////////////////////////////////////////////
// liefert neues Objekt
STDMETHODIMP CObjectManagement::CreateObject(REFCLSID riid, BSTR bstrName, DWORD dwMode, IUnknown **ppUnk, VARIANT_BOOL fCreateTemp)
{
	// Setzt den Modulstatus der MFC.dll auf diese DLL
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	ASSERT(ppUnk);
	ASSERT(bstrName);

	// zur Sicherheit
	*ppUnk = NULL;

	HRESULT hr = IsValidName(bstrName);// falscher StreamName (StorageManagement) ?
	
	if (SUCCEEDED(hr)) 
		return MakeObject (riid, bstrName, dwMode, ppUnk, fCreateTemp);

	return hr;
}

//////////////////////////////////////////////////////////////////
// setzt ein schon kreiertes Objekt
STDMETHODIMP CObjectManagement::SetObject(LPUNKNOWN pUnk, BSTR bstrName, DWORD dwMode, BOOL fCreateTemp)
{	
	// Setzt den Modulstatus der MFC.dll auf diese DLL
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	ASSERT(pUnk);
	ASSERT(bstrName);

HRESULT hr = IsValidName (bstrName);		// falscher StreamName (StorageManagement) ?
	
	if (SUCCEEDED(hr)) 
		return InsertObject (pUnk, bstrName, dwMode, fCreateTemp);

	return hr;
}

STDMETHODIMP CObjectManagement::RenameObject(BSTR bstrName, BSTR bstrNewName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	ASSERT(NULL != m_lpIStorage);

	COM_TRY {
	// Schon Objekt mit diesem Namen vorhanden und geladen
		if (SUCCEEDED(GetLoad(bstrNewName)))
			return E_UNEXPECTED;

		THROW_FAILED_HRESULT(IsValidName(bstrNewName));	// falscher StreamName (StorageManagement) ?
		THROW_FAILED_HRESULT(IsValidName(bstrName));

	// Erst Stream umbenennen		
		THROW_FAILED_HRESULT(RenameStream(bstrName, bstrNewName));

	// Objekt an sich umbenennen
		THROW_FAILED_HRESULT(Rename(bstrName, bstrNewName));		

	// Öffnen und setzen des Streams des neuen Objektes
	WStream IStream;

		THROW_FAILED_HRESULT(OpenStream(bstrNewName, m_lpIStorage, IStream.ppi()));

	// Objekt geben lassen und neuen Moniker für da neue Objekt erzeugen
	WUnknown IU;

		THROW_FAILED_HRESULT(GetUnknownObject(bstrNewName, IU.ppi()));
		THROW_FAILED_HRESULT(CreateMoniker(IU, bstrNewName));

	} COM_CATCH;
	return S_OK;
}

//////////////////////////////////////////////////////////////////
// liefert vorhandenes persistentes Objekt
STDMETHODIMP CObjectManagement::GetObject(BSTR bstrName, IUnknown **ppUnk)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	ASSERT(ppUnk);
	ASSERT(bstrName);

	DWORD dwRegister = 0;

	*ppUnk = NULL;

HRESULT hr = IsValidName(bstrName);// falscher StreamName (StorageManagement) ?
	
	if (SUCCEEDED(hr)) {		
		hr = GetLoad(bstrName);		// Object schon geladen ?
	
	// Es muss ein Object kreiert oder anfangs geladen worden sein
		if (S_OK == hr) {	// Ist Object schon einmal geöffner worden
			hr = GetUnknownObject(bstrName, ppUnk);		// nein
			if (FAILED(hr)) {	// bei S_OK RAUS Object schon geöffnet oder neu erzeugt
			// noch nie geöffnet oder nicht bei dieser Sitzung erzeugt worden
			// Stream auf jeden Fall öffnen, bei Low-Memory auch Speichern möglich
				hr = OpenObject (bstrName, ppUnk);
			}
		}
		else 
			return E_FAIL;
	}
	return hr;
}
//////////////////////////////////////////////////////////////////
// speichert Objekte 
STDMETHODIMP CObjectManagement::SaveObject(BSTR bstrName)
{
	// Setzt den Modulstatus der MFC.dll auf diese DLL
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	ASSERT(bstrName);

	HRESULT hr = IsValidName(bstrName);// falscher StreamName (StorageManagement) ?
	
	if (SUCCEEDED(hr)) 
		hr = SaveToFileOrStorage(bstrName);

	return hr;
}

//////////////////////////////////////////////////////////////////
// Löscht Objekt vom Storage
STDMETHODIMP CObjectManagement::DelObject(BSTR bstrName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	ASSERT(NULL != bstrName);

HRESULT hr = E_FAIL;

	COM_TRY {
		{		// gleich wieder freigeben
		WStream IS;

			if (SUCCEEDED(GetStream(bstrName, IS.ppi()))) {		// Stream vorhanden, also löschen
			CComBSTR bstrCorrName;

				THROW_FAILED_HRESULT(CorrectName (bstrName, &bstrCorrName));
				THROW_FAILED_HRESULT(m_lpIStorage -> DestroyElement (bstrCorrName));
			}
		}

	bool fTemp = false;

		if (SUCCEEDED(hr = GetTemporaer(bstrName, fTemp))) {
		// Wird auf jeden Fall gelöscht, wenn gefunden
			THROW_FAILED_HRESULT(DeleteFromEnum(bstrName));

		// nur, wenn schon mal persistent				
			if (!fTemp) 
				m_fIsDirty = true;
		}

	} COM_CATCH;
	return hr;
}

/////////////////////////////////////////////////////////////////
// liefert Enumerator der Strings der persistenten Objekte
STDMETHODIMP CObjectManagement::EnumStrings(IUnknown **ppUnk)
{
	// Setzt den Modulstatus der MFC.dll auf diese DLL
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	ASSERT(ppUnk);
	if (NULL == ppUnk) return E_POINTER;

NEnumos_wstring *pIEnum = NULL;

	*ppUnk = NULL;
	try {
		pIEnum = new NEnumos_wstring; 

		{// scope setzen (zur Übersichtlichkeit)
		WUnknown IUnk;	

			m_pEnumObjects -> Reset();
			while (S_OK == m_pEnumObjects -> Next(1, IUnk.ppi(), NULL))
			{
			CComBSTR bstr;

				THROW_FAILED_HRESULT(WObjectHolder(IUnk) -> GetName(&bstr));

				pIEnum -> AddItem (os_wstring(bstr));
				pIEnum -> Reset();
			}
		} // endgültiges IUnk -> Release() bei out of scope

		m_pEnumObjects -> Reset();
		*ppUnk = pIEnum;	// übernimmt RefCnt von 'new'
	} 
	catch (bad_alloc) 
	{
		if (pIEnum) pIEnum -> Release();
		return E_OUTOFMEMORY;
	}
	catch (_com_error &e) 
	{// von new()
		if (pIEnum) pIEnum -> Release();
		return _COM_ERROR(e);
	}

	return S_OK;
}

//////////////////////////////////////////////////////////////////
// schliesst offenes Object 
STDMETHODIMP CObjectManagement::ReleaseObject(BSTR bstrName)
{
// Setzt den Modulstatus der MFC.dll auf diese DLL
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	ASSERT(bstrName);

WObjectHolder IOH;
HRESULT hr = GetObjectHolder(bstrName, IOH.ppi());

	if (FAILED(hr)) return hr;
	return IOH -> ReleaseObject (VARIANT_TRUE);
}

STDMETHODIMP CObjectManagement::Commit()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	ASSERT(m_lpIStorage);
	if (NULL == m_lpIStorage) return E_POINTER;
	return m_lpIStorage -> Commit(STGC_DEFAULT);
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Hilfsfunktionen zum Serialisieren/DeSerialisieren eines IUnknowns 
//
void CObjectManagement::Reset (bool fFullRelease)
{	
// InhaltsStream, wenn leer löschen
	DestroyNewContentStream();

	if (fFullRelease) {
		if (m_pEnumObjects) 
			VERIFY(0 == m_pEnumObjects -> Release()); 
		m_pEnumObjects = NULL;
	} else 
		m_pEnumObjects -> HandsOffStorage();

	if (m_lpIStorage)
		m_lpIStorage -> Release();
	m_lpIStorage = NULL;
}

HRESULT CObjectManagement::DestroyNewContentStream()
{
	if (m_lpIStreamStorageContents)
		VERIFY(0 == m_lpIStreamStorageContents -> Release());
	m_lpIStreamStorageContents = NULL;

	if (NULL == m_lpIStorage || 0 != ObjectCount())
		return NOERROR;
		
	USES_CONVERSION;

CString str;

	RETURN_FAILED_HRESULT(LoadString(str, IDS_STORAGEMANAGEMENTSTREAM));
	return m_lpIStorage -> DestroyElement(A2OLE(str));
}

HRESULT CObjectManagement::SetUnknownToStream (LPUNKNOWN pUnk, LPSTREAM pIStream)
{
	ASSERT(NULL != pUnk);
	ASSERT(NULL != pIStream);

	try {
	WPersistStream IPersStr (pUnk);	// throws hr

		THROW_FAILED_HRESULT(OleSaveToStream (IPersStr, pIStream));

	// dafür sorgen, daß der Stream wirklich nur so groß ist, wie benötigt
	ULARGE_INTEGER uli;

		uli.QuadPart = 0;
		THROW_FAILED_HRESULT(pIStream -> Seek ((LARGE_INTEGER &)uli, STREAM_SEEK_CUR, &uli));
		THROW_FAILED_HRESULT(pIStream -> SetSize (uli));

	} catch (_com_error &e) {
		return _COM_ERROR(e);
	}
	return S_OK;
}

HRESULT CObjectManagement::MakeObject (REFCLSID riid, BSTR bstrName, DWORD dwMode, LPUNKNOWN *ppUnk, bool fCreateTemp) 
{
	ASSERT(NULL != bstrName);
	ASSERT(NULL != ppUnk);

HRESULT hr = E_FAIL;

	if (NULL == ppUnk) return E_POINTER;
	*ppUnk = NULL;

	try  {
	// Wenn schon Altes existiert, wird bedingungslos Neues angelegt
		if ((STGM_CREATE & dwMode) && S_OK == GetLoad(bstrName)) 
			DelObject(bstrName);

	WUnknown IUnk (riid);
	
	// ObjectWrapper erzeugen und in Liste füllen
		THROW_FAILED_HRESULT(SetLoad(bstrName));

	// Object an sich in ObjectWrapper eintragen
		THROW_FAILED_HRESULT(SetUnknownObject(bstrName, IUnk));

	// Soll Object nur temporaer geladen werden ?
		THROW_FAILED_HRESULT(SetTemporaer(bstrName, fCreateTemp));

	// File oder Stream öffnen
		THROW_FAILED_HRESULT(LoadFileOrStream(IUnk, bstrName, dwMode));

	// FileMoniker, ItemMoniker für eigene Storageobjekte oder objekteigener Moniker
		THROW_FAILED_HRESULT(CreateMoniker(IUnk, bstrName));

	// Ist Neues !!!
		THROW_FAILED_HRESULT(SetNew(bstrName, true));

	// ERFOLG
		*ppUnk = IUnk.detach();

	} catch (_com_error& e) {
		if (SUCCEEDED(GetLoad(bstrName)))
			hr = DelObject(bstrName);
		return _COM_ERROR(e);
	}
	return S_OK;
}

HRESULT CObjectManagement::InsertObject (LPUNKNOWN pUnk, BSTR bstrName, DWORD dwMode, BOOL fCreateTemp) 
{
	ASSERT(bstrName);
	ASSERT(pUnk);
	if (NULL == pUnk) return E_POINTER;

	try {
	// ObjectWrapper erzeugen und in Liste füllen
		THROW_FAILED_HRESULT(SetLoad(bstrName));

	// Object an sich in ObjectWrapper eintragen
		THROW_FAILED_HRESULT(SetUnknownObject(bstrName, pUnk));

	// Soll Object nur temporaer geladen werden ?
		THROW_FAILED_HRESULT(SetTemporaer(bstrName, fCreateTemp));

	// File oder Stream öffnen
		THROW_FAILED_HRESULT(LoadFileOrStream(pUnk, bstrName, dwMode));

	// FileMoniker, ItemMoniker für eigene Storageobjekte oder objekteigener Moniker
		THROW_FAILED_HRESULT(CreateMoniker(pUnk, bstrName));
	}
	catch (_com_error &e)
	{
		if (SUCCEEDED(GetLoad(bstrName)))
			return DelObject(bstrName);
		return _COM_ERROR(e);
	}
	return S_OK;
}

HRESULT CObjectManagement::OpenObject (BSTR bstrName, LPUNKNOWN *ppUnk) 
{
	ASSERT(bstrName);
	ASSERT(ppUnk);

DWORD dwRegister = 0;

	if (NULL == ppUnk) return E_POINTER;
	*ppUnk = NULL;

	try
	{	
	// Monikers erzeugen bzw. aus Liste geben lassen
	WMoniker IBindingMon;
	WMoniker IRunningMon;

		THROW_FAILED_HRESULT(GetMoniker(bstrName, IRunningMon.ppi(), IBindingMon.ppi()));					

	// LeftComposite als Running registrieren
	WUnknown IU((IObjectManagement*)this);

	//////////////////////////////////////
	// Eintragen in die Running-Object-Table
		THROW_FAILED_HRESULT(RegisterAsRunning (ACTIVEOBJECT_STRONG, IU, IRunningMon, &dwRegister));

	/////////////////////////////////////
	// Bindcontext geben lassen
	WBindCtx IBC;

		THROW_FAILED_HRESULT(CreateBindCtx(0, IBC.ppi()));

	///////////////////////////////////
	// Laden des Objectes von Platte
	WUnknown UnkResult;		

		THROW_FAILED_HRESULT(IBindingMon -> BindToObject (IBC, 0, IID_IUnknown, UnkResult.ppv())); // GetClassID, CoCreateI..., IPersistStream/IPersistFileLoad -> Load

	// RegisterRunning zurücksetzen
		THROW_FAILED_HRESULT(RevokeAsRunning(&dwRegister));

	// Object noch nie geöffnet wurden
		THROW_FAILED_HRESULT(SetUnknownObject(bstrName, UnkResult));

	// ERFOLG		
		*ppUnk = UnkResult.detach();
	}
	catch (_com_error &e)
	{
		if (dwRegister) RevokeAsRunning(&dwRegister);
		return _COM_ERROR(e);
	}

	return S_OK;
}

HRESULT CObjectManagement::GetUnknownFromStream (LPSTREAM pIStream, REFIID riid, LPVOID *ppUnk)
{
	ASSERT(pIStream);
	ASSERT(ppUnk);

	if (NULL == ppUnk) return E_POINTER;
	*ppUnk = NULL;

	COM_TRY {
	WStream IS;	// Für alte Version laden, Muß vor OleLoadFromStream geschehen, da Seekpointer hinter CLSID
	
		THROW_FAILED_HRESULT(pIStream -> Clone(IS.ppi()));		// kein CLSID ?

	// Dieser Workaround ist notwendig, um alte Script-Objekte laden zu können
		if (FAILED(OleLoadFromStream (pIStream, riid, ppUnk)))	{	// Zu Fuß laden			
		WPersistStream IPS(CLSID_Script);

			THROW_FAILED_HRESULT(IPS -> Load(IS));
			return IPS -> QueryInterface (riid, ppUnk);
		} 

	} COM_CATCH;
	return S_OK;
}
///////////////////////////////////////////////////////////////////////////////////////
// Hilfsfunktionen für Create eines Objektes
HRESULT CObjectManagement::CreateMoniker(LPUNKNOWN lpUnk, BSTR bstrName)
{
WMoniker IMon;

	USES_CONVERSION;
	try
	{
	WPersistStream IPersistStream(lpUnk);	
	LPSTR lpstrDelimiter = "!";

	// IPersistStream: eigene Objekte in irgendeinem Storage selbst verarbeiten, BindToObj... ruft this->GetObject...
		THROW_FAILED_HRESULT(CreateItemMoniker(A2OLE(lpstrDelimiter), bstrName, IMon.ppi()));
	}
	catch (_com_error &e)
	{
		if (E_NOINTERFACE != _COM_ERROR(e)) 
			throw;	// FAILED allgemein 

		try	{
		//////////////////////////////////////////////////////////////////
		// alles in Ordnung, aber QueryInterface nach IPersistStream schlug fehl
		WPersistFile IPersistFile(lpUnk); // Query
		
		// FileMoniker kreieren, wenn QueryInterface nach IPersistFile erfolgreich
			THROW_FAILED_HRESULT(CreateFileMoniker(bstrName, IMon.ppi()));

		}
		catch (_com_error &e)
		{
			return _COM_ERROR(e);
		}
	}

	return SetMoniker(bstrName, IMon);
}

////////////////////////////////////////////////////////////////////////////
// Öffnen Kreieren Streams
HRESULT CObjectManagement::OpenStream(UINT uiResID, LPSTORAGE lpIStorage, LPSTREAM *ppStream)
{
CString str;

	RETURN_FAILED_HRESULT(LoadString (str, uiResID));
	return OpenStreamName (CComBSTR(str), NULL, lpIStorage, ppStream);
}

HRESULT CObjectManagement::OpenStream(BSTR bstrName, LPSTORAGE lpIStorage, LPSTREAM *ppStream)
{
CComBSTR bstrCorrName;

	RETURN_FAILED_HRESULT(CorrectName (bstrName, &bstrCorrName));
	return OpenStreamName (bstrName, bstrCorrName, lpIStorage, ppStream);
}

HRESULT CObjectManagement::OpenStreamName(
	BSTR bstrName, BSTR bstrCorrName, LPSTORAGE lpIStorage, LPSTREAM *ppStream)
{
	if (NULL == ppStream) 
		return E_POINTER;

HRESULT hr = E_FAIL;

	*ppStream = NULL;
	COM_TRY {
	WStream IS;

	// ist Stream schon geöffnet worden 
		hr = GetStream (bstrName, IS.ppi());
		if (FAILED(hr)) {
		// erzeugten Stream öffnen, der vordem noch nicht geöffnet wurde
		DWORD dwMode = STGM_DIRECT | STGM_READWRITE | STGM_SHARE_EXCLUSIVE; 
			hr = lpIStorage -> OpenStream (NULL != bstrCorrName ? bstrCorrName : bstrName, 0, dwMode, 0, IS.ppi());

		// Managementstream, Stream extra merken, noch nicht in Map der offenen Streams
			if (SUCCEEDED(hr) && SUCCEEDED(IsValidName(bstrName)))
				THROW_FAILED_HRESULT(SetStream (bstrName, IS));
		}
		if (IS.IsValid())
			*ppStream = IS.detach();	// Erfolg

	} COM_CATCH;

	ASSERT(NULL == *ppStream || S_OK == hr);
	return (NULL != *ppStream) ? S_OK : hr;
}

HRESULT CObjectManagement::CreateStream(UINT uiResID, LPSTORAGE lpStorage, LPSTREAM *lplpStream)
{
CString str;

	RETURN_FAILED_HRESULT(LoadString (str, uiResID));
	return CreateStreamName (CComBSTR(str), NULL, lpStorage, lplpStream);
}

HRESULT CObjectManagement::CreateStream(BSTR bstrName, LPSTORAGE lpStorage, LPSTREAM *lplpStream)
{
CComBSTR bstrCorrName;

	RETURN_FAILED_HRESULT(CorrectName (bstrName, &bstrCorrName));
	return CreateStreamName (bstrName, bstrCorrName, lpStorage, lplpStream);
}

HRESULT CObjectManagement::CreateStreamName (
	BSTR bstrName, BSTR bstrCorrName, LPSTORAGE lpStorage, LPSTREAM *lplpStream)
{
	if (NULL == lplpStream || NULL == lpStorage)
		return E_POINTER;
	*lplpStream = NULL;

	COM_TRY {
	// Stream schon erzeugt und geöffnet
	WStream Strm;

		if (SUCCEEDED(GetStream (bstrName, Strm.ppi())))
			_com_issue_error(E_UNEXPECTED);		// Stream ist bereits geöffnet

	// Stream auf jeden Fall öffnen, bei Low-Memory auch Speichern möglich
	DWORD dwMode = STGM_DIRECT | STGM_READWRITE | STGM_SHARE_EXCLUSIVE; 

		THROW_FAILED_HRESULT(lpStorage -> CreateStream (NULL != bstrCorrName ? bstrCorrName : bstrName, dwMode, 0, 0, Strm.ppi()));
		if (SUCCEEDED(IsValidName(bstrName)))
			THROW_FAILED_HRESULT(SetStream (bstrName, Strm));	// zur Map der offenen Streams hinzufügen

		*lplpStream = Strm.detach();

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////////////
// Moniker

// DefaultMoniker von Trias erzeugen (spezifisch für diese Instanz)
HRESULT CObjectManagement::GetTRiASMoniker(IMoniker **ppMon)	
{
	ASSERT(ppMon);
	USES_CONVERSION;

CString strTRiAS;

	strTRiAS.Format (IDS_FIRSTCOMPMONIKER, reinterpret_cast<DWORD>(this));
	RETURN_FAILED_HRESULT(CreateItemMoniker(L"!", A2OLE(strTRiAS), ppMon));		// CompositeMon. erzeugen
	return S_OK;
}

// DefaultMoniker aus ClassID erzeugen
HRESULT CObjectManagement::GetManagementMoniker (IMoniker **ppMon)
{
	COM_TRY {
	CIID Guid (CLSID_CObjectManagement);
	CComBSTR bstrGuid(os_string(Guid).c_str());

		THROW_FAILED_HRESULT(CreateItemMoniker (L"!", bstrGuid, ppMon));
	} COM_CATCH;
	return S_OK;
}

// Stream umbenennen
HRESULT CObjectManagement::RenameStream (BSTR bstrName, BSTR bstrNewName)
{
	COM_TRY {
		{
		WStream IS;// Stream geöffnet ?

			THROW_FAILED_HRESULT(GetStream(bstrName, IS.ppi()));
		} // WStream goes out of scope

	// Stream Release(), sonst Umbenennen nicht möglich
		THROW_FAILED_HRESULT(SetStream(bstrName, NULL));

	// Umbenennen des Streams
	CComBSTR bstrCorrName;
	CComBSTR bstrCorrNewName;

		THROW_FAILED_HRESULT(CorrectName (bstrName, &bstrCorrName));
		THROW_FAILED_HRESULT(CorrectName (bstrNewName, &bstrCorrNewName));
		THROW_FAILED_HRESULT(m_lpIStorage -> RenameElement(bstrCorrName, bstrCorrNewName));

	} COM_CATCH;
	return S_OK;
}

HRESULT CObjectManagement::GetMoniker(BSTR bstrName, IMoniker **ppIRunningMon, IMoniker **ppIBindingMon)
{
	ASSERT(ppIRunningMon);
	ASSERT(ppIBindingMon);

	HRESULT hr = NOERROR;

	if (NULL == ppIBindingMon) return E_POINTER;
	if (NULL == ppIRunningMon ) return E_POINTER;

	*ppIBindingMon = NULL;
	*ppIRunningMon = NULL;

	USES_CONVERSION;	

	COM_TRY {
	WMoniker ITRiASMon;

		THROW_FAILED_HRESULT(GetTRiASMoniker(ITRiASMon.ppi()));

	// einzelne Moniker geben lassen
	WMoniker IManagementMon;

		THROW_FAILED_HRESULT(GetManagementMoniker(IManagementMon.ppi()));

	// Eigenen Moniker geben lassen
	WMoniker IObjectMoniker;

		THROW_FAILED_HRESULT(GetMoniker(bstrName, IObjectMoniker.ppi()));

	// Composites erzeugen, zum Anmelden als Running
	WMoniker IRunning;

		THROW_FAILED_HRESULT(CreateGenericComposite(ITRiASMon, IManagementMon, IRunning.ppi()));

	// zum Binden
	WMoniker IBinding;

		THROW_FAILED_HRESULT(CreateGenericComposite(IRunning, IObjectMoniker, IBinding.ppi()));

	// ERFOLG
		*ppIRunningMon = IRunning.detach();
		*ppIBindingMon = IBinding.detach();
	
	} COM_CATCH;
	return S_OK;
}

HRESULT CObjectManagement::IsValidName(BSTR bstrName)
{
	if (0 == wcslen(bstrName)) 
		return E_INVALIDARG;

CString str;
	
	RETURN_FAILED_HRESULT(LoadString(str, IDS_STORAGEMANAGEMENTSTREAM));
	return (str == bstrName || *bstrName < L' ') ? E_UNEXPECTED : S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Running bearbeiten
HRESULT CObjectManagement::RegisterAsRunning (DWORD grfFlags, IUnknown *pIUnk, IMoniker *pIMk, DWORD *pdwRegROT)
{
	if (NULL == pdwRegROT) return E_POINTER;

IRunningObjectTable *pROT;

	if (SUCCEEDED(GetRunningObjectTable(0, &pROT))) 
	{
	// Revoke old entry, if needed
		if (0 != *pdwRegROT) {
			pROT -> Revoke (*pdwRegROT);
			*pdwRegROT = 0L;
		}

	// Register as weak so clients can free us.
		pROT -> Register(grfFlags, pIUnk, pIMk, pdwRegROT);
		pROT -> Release();
	}
	return S_OK;
}

HRESULT CObjectManagement::RevokeAsRunning (DWORD *pdwRegROT)
{
	if (NULL == pdwRegROT) return E_POINTER;
	if (0L == *pdwRegROT) return S_FALSE;

IRunningObjectTable *pROT;

	if (SUCCEEDED(GetRunningObjectTable (0, &pROT))) 
	{
	// Register as weak so clients can free us.
		pROT -> Revoke (*pdwRegROT);
		pROT -> Release();

		*pdwRegROT = 0;
	}
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////////
// CObjectHolder Properties
HRESULT CObjectManagement::SetLoad(BSTR bstr)
{
	HRESULT hr = NOERROR;
	LPUNKNOWN lpObjectHolder = NULL;

	try	{
		THROW_FAILED_HRESULT(IsValidName(bstr));

	// Schon geladen
		if (S_OK == GetLoad(bstr))
			_com_issue_error(E_UNEXPECTED);

		lpObjectHolder = new CObjectHolder();
	
	// ObjectHolder initialisieren
	os_wstring oswstr(bstr);
	WObjectHolder IOH (lpObjectHolder);
	
		THROW_FAILED_HRESULT(IOH -> SetName(bstr));

	WUnknown IU = IOH;

		THROW_FAILED_HRESULT(m_pEnumObjects -> Add(IU));
	
	} catch (bad_alloc) {
		return E_OUTOFMEMORY; 
	} catch (_com_error &e) {
		return _COM_ERROR(e); 
	}
	return S_OK;
}
HRESULT CObjectManagement::GetLoad(BSTR bstrName)
{
WUnknown IU;

	return Find(bstrName, IU.ppi());
}

HRESULT CObjectManagement::GetTemporaer(BSTR bstrName, bool & fTemp)
{
WObjectHolder IOH;
HRESULT hr = GetObjectHolder(bstrName, IOH.ppi());

	if (FAILED(hr)) return hr;
	return IOH -> GetTemporaer(fTemp);
}
HRESULT CObjectManagement::SetTemporaer(BSTR bstrName, bool fTemp)
{
WObjectHolder IOH;
HRESULT hr = GetObjectHolder(bstrName, IOH.ppi());

	if (FAILED(hr)) return hr;
	return IOH -> SetTemporaer(fTemp);
}

HRESULT CObjectManagement::GetDelayedDel(BSTR bstrName, bool & fDelayedDel)
{
WObjectHolder IOH;
HRESULT hr = GetObjectHolder(bstrName, IOH.ppi());

	if (FAILED(hr)) return hr;
	return IOH -> GetDelayedDel(fDelayedDel);
}
HRESULT CObjectManagement::SetDelayedDel(BSTR bstrName)
{
WObjectHolder IOH;
HRESULT hr = GetObjectHolder(bstrName, IOH.ppi());

	if (FAILED(hr)) return hr;
	return IOH -> SetDelayedDel();
}
// Stream Properties
HRESULT CObjectManagement::GetStream(BSTR bstrName, LPSTREAM* lplpStream)
{
WObjectHolder IOH;
HRESULT hr = GetObjectHolder(bstrName, IOH.ppi());

	if (FAILED(hr)) return hr;

WStream IS;

	hr = IOH -> GetStream(IS.ppi());
	if (FAILED(hr)) return hr;

// Stream erstmal auf Anfang des Files setzen
LARGE_INTEGER li;	

	LISet32 (li, 0);
	RETURN_FAILED_HRESULT(IS -> Seek(li, STREAM_SEEK_SET, NULL));

	*lplpStream = IS.detach();
	return S_OK;
}

HRESULT CObjectManagement::SetStream(BSTR bstrName, LPSTREAM lpStream)
{
WObjectHolder IOH;
HRESULT hr = GetObjectHolder(bstrName, IOH.ppi());

	if (FAILED(hr)) return hr;
	if (NULL != lpStream) {
	// Stream erstmal auf Anfang des Files setzen
	LARGE_INTEGER li;	

		LISet32 (li, 0);
		RETURN_FAILED_HRESULT(lpStream -> Seek(li, STREAM_SEEK_SET, NULL));
	}

// wenn NULL, Stream -> Release()
	return IOH -> SetStream(lpStream);
}

// Moniker Properties
HRESULT CObjectManagement::GetMoniker (BSTR bstrName, LPMONIKER*	lplpMon)
{
WObjectHolder IOH;
HRESULT hr = GetObjectHolder(bstrName, IOH.ppi());

	if (FAILED(hr)) return hr;
	return IOH -> GetMoniker(lplpMon);
}

HRESULT CObjectManagement::Rename (BSTR bstrName, BSTR bstrNewName)
{
WObjectHolder IOH;
HRESULT hr = GetObjectHolder(bstrName, IOH.ppi());

	if (FAILED(hr)) return hr;
	return IOH -> Rename(bstrNewName);
}

HRESULT CObjectManagement::SetMoniker (BSTR bstrName, LPMONIKER	lpMon)
{
WObjectHolder IOH;

	RETURN_FAILED_HRESULT(GetObjectHolder(bstrName, IOH.ppi()));
	return IOH -> SetMoniker(lpMon);
}

// Object geben lassen
HRESULT CObjectManagement::GetUnknownObject(BSTR bstrName, LPUNKNOWN*	lplpUnk)
{
WObjectHolder IOH;
HRESULT hr = GetObjectHolder(bstrName, IOH.ppi());

	if (FAILED(hr)) return hr;
	return IOH -> GetObject(lplpUnk);
}

HRESULT CObjectManagement::SetUnknownObject(BSTR bstrName, LPUNKNOWN	lpObject)
{
WObjectHolder IOH;
HRESULT hr = GetObjectHolder(bstrName, IOH.ppi());

	if (FAILED(hr)) return hr;

	ASSERT(NULL != lpObject);
	return IOH -> SetObject(lpObject);
}

HRESULT CObjectManagement::SaveToFileOrStorage(BSTR bstrName)
{
WUnknown IU;	
HRESULT hr = NOERROR;

	COM_TRY {
	// Object öffnen	
		THROW_FAILED_HRESULT(GetObject(bstrName, IU.ppi()));

	// IPersistStream ?, wenn nicht catch
	WPersistStream IP (IU);
	WStream IStream; 

	// ist ObjektStream nun auch geöffnet ?
		hr = GetStream(bstrName, IStream.ppi());
	
	// SaveToStream, SUCCEEDED: Stream geladen
		if (SUCCEEDED(hr) && S_OK == IP -> IsDirty()) {
			THROW_FAILED_HRESULT(SetUnknownToStream (IU, IStream));

		// Hier erst ObjMan dirty setzen
			m_fIsDirty = true;

		// Nun nicht mehr neu !!!
			THROW_FAILED_HRESULT(SetNew (bstrName, false));
		}
	} catch (_com_error& e) {
	// Query schlägt fehl
	// besitzt Object ein IPersistFile
		if (E_NOINTERFACE != _COM_ERROR(e)) 
			return _COM_ERROR(e);

		COM_TRY {
		WPersistFile IPF (IU);
		
			if (S_OK == IPF -> IsDirty()) {
				THROW_FAILED_HRESULT(IPF -> Save (NULL, false));
			
			// Hier erst ObjMan dirty setzen
				m_fIsDirty = true;
			
			// Nun nicht mehr neu !!!
				THROW_FAILED_HRESULT(SetNew (bstrName, false));
			}
		} COM_CATCH;
	}
	return hr;
}

HRESULT CObjectManagement::SetNew(BSTR bstrName, bool fNew)
{
// nur Stream öffnen, wenn StreamObject
WObjectHolder IOH;
HRESULT hr = GetObjectHolder(bstrName, IOH.ppi());

	if (FAILED(hr)) return hr;
	return IOH -> SetNew(fNew);
}

HRESULT CObjectManagement::GetNew(BSTR bstrName, bool *pfNew)
{	
// nur Stream öffnen, wenn StreamObject
WObjectHolder IOH;
HRESULT hr = GetObjectHolder(bstrName, IOH.ppi());

	if (FAILED(hr)) return hr;
	return IOH -> GetNew(pfNew);
}

HRESULT CObjectManagement::LoadFileOrStream (
	LPUNKNOWN lpUnk, BSTR bstrName, DWORD dwMode, IStorage *pIStg, BOOL fInitNew)
{	
// nur Stream öffnen, wenn StreamObject
HRESULT hr = LoadStream(lpUnk, bstrName, pIStg, fInitNew);

	if (E_NOINTERFACE == hr) 
		hr = LoadFile (lpUnk, bstrName, dwMode);

	return hr;
}

HRESULT CObjectManagement::LoadFile(LPUNKNOWN lpUnk, BSTR bstrName, DWORD dwMode)
{
	COM_TRY {	// File öffnen
	WPersistFile IPF (lpUnk);

		THROW_FAILED_HRESULT(IPF -> Load(bstrName, dwMode));

	} COM_CATCH
	return S_OK;
}

//#if _MSC_VER == 1200
//#pragma optimize ("", off)
//#endif // _MSC_VER == 1200

HRESULT CObjectManagement::LoadStream (LPUNKNOWN lpUnk, BSTR bstrName, IStorage *pIStg, BOOL fInitNew)
{
WStream Strm;

	COM_TRY {
	WPersistStream IPS (lpUnk);	// nur Stream öffnen, wenn StreamObject, ansonsten throw E_NOINTERFACE
	WStream IStream;
	
	// Stream auf jeden Fall öffnen, bei Low-Memory auch Speichern möglich
		if (NULL == pIStg)
			pIStg = m_lpIStorage;

		if (FAILED(OpenStream(bstrName, pIStg, IStream.ppi())))
		{
			ASSERT(fInitNew);		// Objekt muß neu erzeugt worden sein
			THROW_FAILED_HRESULT(CreateStream(bstrName, pIStg, IStream.ppi()));
		}
		THROW_FAILED_HRESULT(IStream -> Clone(Strm.ppi()));

	} COM_CATCH_EX(e) {		// FEHLER, eventuell E_NOINTERFACE
		return _COM_ERROR(e);
	} COM_CATCH_ALL;

	try {
	// Nun versuchen, zu initialisieren 
	WPersistStreamInit IPSI (lpUnk);		

		if (fInitNew) {
		// Objekt neu initialialiseren
			THROW_FAILED_HRESULT(IPSI -> InitNew());
		} else {
		// Objekt lediglich neu laden
		CLSID ClsId;

			THROW_FAILED_HRESULT(ReadClassStm (Strm, &ClsId));
#if defined(_DEBUG)
		CLSID ClsIdObj;

			THROW_FAILED_HRESULT(IPSI -> GetClassID (&ClsIdObj));
			ASSERT(InlineIsEqualGUID(ClsId, ClsIdObj));
#endif // _DEBUG
			THROW_FAILED_HRESULT(IPSI -> Load (Strm));
		}
	
	} catch (_com_error &e) {
		if (E_NOINTERFACE == _COM_ERROR(e) ||	// von query WPersistStreamInit IPSI = lpUnk;		
			E_NOTIMPL	  == _COM_ERROR(e) ||	// von IPSI -> InitNew();
			E_UNEXPECTED  == _COM_ERROR(e))		// Fehler ignorieren (bereits initialisiertes Objekt)
		{
			return S_FALSE;
		}
		return _COM_ERROR(e);
	}
	return S_OK;
}

//#if _MSC_VER == 1200
//#pragma optimize ("", on)
//#endif // _MSC_VER == 1200

HRESULT CObjectManagement::Find(BSTR bstr, LPUNKNOWN *ppUnk)
{
	ASSERT(bstr);
	if (FAILED(IsValidName(bstr))) return E_FAIL;

	return m_pEnumObjects -> Find(bstr, ppUnk);
}

HRESULT CObjectManagement::DeleteFromEnum(BSTR bstr)
{
	ASSERT(bstr);

	RETURN_FAILED_HRESULT(IsValidName(bstr));
	return m_pEnumObjects -> Delete(bstr);
}

UINT CObjectManagement::ObjectCount()
{
	return m_pEnumObjects -> Count();
}

HRESULT CObjectManagement::GetObjectHolder(BSTR bstrName, IObjectHolder **pp)
{
	ASSERT(bstrName);
	ASSERT(pp);

	if (NULL == pp) return E_POINTER;	
	*pp = NULL;
	
WUnknown IU; // IU -> AddRef()
HRESULT hr = Find (bstrName, IU.ppi());

	if (FAILED(hr))		// Object noch nicht geladen
		return hr;

	COM_TRY {
	WObjectHolder IOH (IU); // query, AddRef()

		*pp = IOH.detach();

	} COM_CATCH;
	return S_OK;
}

//HRESULT CObjectManagement::CreateTimer()
//{
//	try	{
//		m_pHideTimerDlg = new CHideTimerDialog(this);
//		if (!m_pHideTimerDlg -> Create(CHideTimerDialog::IDD), NULL) _com_issue_error(E_FAIL);
//		//m_pHideTimerDlg -> ShowWindow(SW_HIDE);
//	}
//	catch(bad_alloc)
//	{
//		return E_OUTOFMEMORY;
//	}
//	catch(_com_error& e)
//	{
//		return _COM_ERROR(e);
//	}
//	return S_OK;
//}

HRESULT CObjectManagement::DelayedDelete()
{
	return m_pEnumObjects -> DelayedDelete();
}

///////////////////////////////////////////////////////////////////////////////
// StreamNamen evtl. auf gültige zeichen konvertieren
HRESULT CObjectManagement::CorrectName (LPOLESTR poleName, BSTR *pbstrNewName)
{
	if (NULL == pbstrNewName)
		return E_POINTER;

OLECHAR cbBuffer[64];
LPOLESTR pOrgName = poleName;

	if (OBJECTMANAGEMENT_VERSION_101 <= m_dwVersion && wcsncmp (L"__", poleName, 2)) {
	// Streamnamen werden zusätzlich verkürzt: Hash_Name
	// nur in neuer Version und nicht, wenn StandardNamen
	DWORD dwHash = LHashValOfName (LOCALE_SYSTEM_DEFAULT, poleName);

		_ultow (dwHash, cbBuffer, 16);
		wcscat (cbBuffer, poleName);
		pOrgName = cbBuffer;
	}

// Sonderzeichen etc. austauschen
int iLen = wcslen(pOrgName);

	iLen = min(iLen, 31);

CComBSTR bstrName (iLen+1, L"");

	for (int i = 0; i < iLen; i++) {
	wchar_t c = pOrgName[i];

		switch (c) {
		case L'.':
		case L'\\':
		case L'/':
		case L':':
		case L'!':
		case L'ß':
			bstrName[i] = L'_';
			break;

		case L'\0':		// Ende des Strings
			break;

		default:
			if (c > L' ')
				bstrName[i] = c;
			else
				bstrName[i] = L'_';
			break;
		}
	}
	bstrName[i] = L'\0';

	*pbstrNewName = bstrName.Detach();
	return S_OK;
}

HRESULT LoadString(CString & str, int IDS)
{
	ASSERT(0 != IDS);

	try {
		str.Empty();
		if (!str.LoadString(IDS)) _com_issue_error(E_FAIL);
	}
	catch (CMemoryException) 
	{
		return E_OUTOFMEMORY;
	}
	catch (_com_error &e)
	{
		return _COM_ERROR(e);
	}
	return NOERROR;
}

