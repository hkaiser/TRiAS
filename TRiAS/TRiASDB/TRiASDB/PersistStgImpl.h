///////////////////////////////////////////////////////////////////////////
// @doc
// @module PersistStgImpl.h | Implementation of IPersistStorage on base on
// IObjectManagement

#if !defined(_PERSISTSTGIMPL_H__911535F4_837A_11D1_9778_00A024D6F582__INCLUDED_)
#define _PERSISTSTGIMPL_H__911535F4_837A_11D1_9778_00A024D6F582__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//////////////////////////////////////////////////////////////////////////////////////////////
// Hier benötigter Enumerator (EnumStrings)

#if !defined(_ENUM_OS_STRING)
#define _ENUM_OS_STRING
// {0796384F-3123-101C-BB62-00AA0018497C}
extern "C" const IID __declspec(selectany) IID_IEnumos_wstring = 
	{0x0796384f,0x3123,0x101c,{0xbb,0x62,0x00,0xaa,0x00,0x18,0x49,0x7c}};

DefineEnumerator2(os_wstring, IID_IEnumos_wstring);
DefineSmartEnumerator2(os_wstring, IID_IEnumos_wstring);
#endif // !defined(_ENUM_OS_STRING)

///////////////////////////////////////////////////////////////////////////////
// das Wundertier an sich
template <class T>
class ATL_NO_VTABLE IPersistStorageOMImpl :
	public IPersistStorage
{
public:
///////////////////////////////////////////////////////////////////////////////
// Initialization: call this from FinalConstruct of target
	HRESULT FinalConstruct()
	{
	// initialize instance data
		m_StgMode = STGMODE_Unknown;
		m_fIsInitialized = false;
		m_fIsDirty = false;

	// initialize static data
		if (0 == m_cf) {
		T* pT = static_cast<T*>(this);

			m_cf = ::RegisterClipboardFormat(pT -> GetDescription());
		}
		return S_OK;
	}

///////////////////////////////////////////////////////////////////////////////
// support functions
	HRESULT InitTeanants (IStorage *pIStg, bool fCreate = false)
	{
		USES_CONVERSION;
		_ASSERTE(!m_ObjMan);		// InitTeanants nur einmal rufen !
		COM_TRY {
		// ObjectManagement öffnen/anlegen
			m_ObjMan = WObjectManagement(CLSID_CObjectManagement);
			{
			WPersistStorage Init (m_ObjMan);
			HRESULT hr = Init -> Load (pIStg);

				if (S_FALSE == hr)
					hr = Init -> InitNew (pIStg);
				if (FAILED(hr)) _com_issue_error(hr);
			}

		// alle bisher existierenden Objekte instantiieren
			if (!fCreate) {
			WUnknown Unk;
		
				THROW_FAILED_HRESULT(m_ObjMan -> EnumStrings (Unk.ppi()));

			WEnumos_wstring EnumStr (Unk);
			os_wstring wstrName;
			T* pT = static_cast<T*>(this);

				for (EnumStr -> Reset(); S_OK == EnumStr -> Next (1, &wstrName, NULL); /**/) {
				// betreffendes Objekt sicher erzeugen und ...
					THROW_FAILED_HRESULT(m_ObjMan -> GetObject (CComBSTR(wstrName.c_str()), Unk.ppi()));

				// ... zum Enumerator hinzufügen
					THROW_FAILED_HRESULT(pT -> _Add(__Interface<T::controlled_t>(Unk), VARIANT_TRUE));
				}
			}

		// jetzt ist alles in Butter
			m_StgMode = STGMODE_Normal;

		} COM_CATCH_OP(m_ObjMan.Release());

		return S_OK;
	}

	HRESULT InitObjMan (IObjectManagement *pIObjMan, IStorage *pIStg, STGMODE rgStgMode)
	{
		m_ObjMan = pIObjMan;
		m_Stg = pIStg;
		m_StgMode = rgStgMode;
		m_fIsInitialized = true;
		m_fIsDirty = false;
		return S_OK;
	}

	bool IsInitialized() { return m_fIsInitialized; }

// umbenenne eines der Streams
	HRESULT RenameObject (BSTR bstrOld, BSTR bstrNew)
	{
		return m_ObjMan -> RenameObject (bstrOld, bstrNew);
	}

///////////////////////////////////////////////////////////////////////////////
// IUnknown
	STDMETHOD(QueryInterface)(REFIID riid, void ** ppvObject) = 0;
	_ATL_DEBUG_ADDREF_RELEASE_IMPL(IPersistStorageOMImpl)

// IPersist
	STDMETHOD(GetClassID)(CLSID *pClassID)
	{
//		ATLTRACE(_T("IPersistStorageOMImpl::GetClassID\n"));
	
		T* pT = static_cast<T*>(this);
		*pClassID = pT -> GetObjectCLSID();
		return S_OK;
	}

// IPersistStorage
	STDMETHOD(IsDirty)(void)
	{
//		ATLTRACE(_T("IPersistStorageOMImpl::IsDirty\n"));

	// zuerst nachsehen, ob ObjMan dirty ist
	CComQIPtr<IPersistStorage, &IID_IPersistStorage> PS (m_ObjMan);

		_ASSERTE(NULL != PS.p);
		if (S_OK == PS -> IsDirty()) return S_OK;

	// danach alle Elemente des Enums abklappern
		COM_TRY {
		WEnumVARIANT Enum;
		CComVariant v;

			THROW_FAILED_HRESULT(static_cast<T*>(this) -> _NewEnum (Enum.ppu()));
			for (Enum -> Reset(); S_OK == Enum -> Next (1, CLEARED(&v), NULL); /**/)
			{
				if (FAILED(v.ChangeType (VT_UNKNOWN)))
					continue;

			CComQIPtr<IPersistStream, &IID_IPersistStream> pstm (V_UNKNOWN(&v));

				if (NULL != pstm.p && S_OK == pstm -> IsDirty())
					return S_OK;
			}

		} COM_CATCH;

	// ok, nichts muß gespeichert werden
		return S_FALSE;
	}
	STDMETHOD(InitNew)(IStorage *pIStg)
	{
//		ATLTRACE(_T("IPersistStorageOMImpl::InitNew\n"));
		if (m_fIsInitialized || NULL != (IStorage *)m_Stg)
			return E_UNEXPECTED;

		USES_CONVERSION;

	// if the following assertion fires you probably forgot to call
	// FinalConstruct for this class
		_ASSERTE(0 != m_cf);
		_ASSERTE(!m_Stg);

	// erste rudimentäre StorageVorbereitungen
	T* pT = static_cast<T*>(this);
	HRESULT hr = ::WriteFmtUserTypeStg(pIStg, m_cf, T2OLE(pT -> GetDescription()));
		
		if (FAILED(hr)) return hr;
	
	// jetzt substorages etc. initialisieren (füllt m_ConnectStg)
		hr = InitTeanants (pIStg, true);
		if (FAILED(hr)) return hr;

	// assign Storage object
		m_Stg = pIStg;

		m_fIsDirty = false;
		m_fIsInitialized = true;
		return S_OK;
	}
	STDMETHOD(Load)(IStorage *pIStg)
	{
//		ATLTRACE(_T("IPersistStorageOMImpl::Load\n"));
		if (m_fIsInitialized || NULL != (IStorage *)m_Stg)
			return E_UNEXPECTED;

	// jetzt Substorages etc. initialisieren (füllt m_Stg)
	HRESULT hr = InitTeanants (pIStg);

		if (FAILED(hr)) return hr;
		m_Stg = pIStg;

		m_fIsDirty = false;
		m_fIsInitialized = true;
		return S_OK;
	}
	STDMETHOD(Save)(IStorage *pIStg, BOOL fSameAsLoad)
	{
//		ATLTRACE(_T("IPersistStorageOMImpl::Save\n"));
		if (!m_fIsInitialized)
			return E_UNEXPECTED;

		USES_CONVERSION;
		_ASSERTE(STGMODE_Normal == m_StgMode);
		_ASSERTE(NULL != (IObjectManagement *)m_ObjMan);

	CComQIPtr<IPersistStorage, &IID_IPersistStorage> PS (m_ObjMan);
	CComPtr<IStorage> pStg = m_Stg;

		_ASSERTE(NULL != (IPersistStorage *)PS);
		m_Stg.Release();
		if (!fSameAsLoad)
			pStg = pIStg;

	HRESULT hr = PS -> Save (pStg, fSameAsLoad);

		if (FAILED(hr)) return hr;

		m_Stg = pStg;
		m_fIsDirty = true;
		m_StgMode = STGMODE_NoScribble;
		return S_OK;
	}
	STDMETHOD(SaveCompleted)(IStorage *pIStg)
	{
//		ATLTRACE(_T("IPersistStorageOMImpl::SaveCompleted\n"));
		if (!m_fIsInitialized)
			return E_UNEXPECTED;

		USES_CONVERSION;
		_ASSERTE(STGMODE_NoScribble == m_StgMode || STGMODE_HandsOff == m_StgMode);

	CComQIPtr<IPersistStorage, &IID_IPersistStorage> PS (m_ObjMan);
	HRESULT hr = S_OK;

		_ASSERTE(NULL != (IPersistStorage *)PS);
		if (NULL == pIStg) {
		// kann nicht zum Schreiben auf Storage freigegeben werden, da StoragePointer
		// NULL	nach HandsOffStorage()
			if (STGMODE_HandsOff == m_StgMode) 
				return E_POINTER;
			hr = PS -> SaveCompleted (NULL);
		} else {
		// etvl. HandsOffStorage simulieren
			if (STGMODE_NoScribble == m_StgMode) {
				hr = static_cast<T*>(this) -> HandsOffStorage();
				if (FAILED(hr)) return hr;
			}

		// vorheriges Storage freigeben, neues geben lassen
			hr = PS -> SaveCompleted (pIStg);
			if (FAILED(hr)) return hr;
			m_Stg = pIStg;
		}

	// nur, wenn alles glatt gegangen ist
		m_fIsDirty = false;
		m_StgMode = STGMODE_Normal;
		return S_OK;
	}
	STDMETHOD(HandsOffStorage)(void)
	{
//		ATLTRACE(_T("IPersistStorageOMImpl::HandsOffStorage\n"));
		if (!m_fIsInitialized)
			return E_UNEXPECTED;

	CComQIPtr<IPersistStorage, &IID_IPersistStorage> PS (m_ObjMan);

		_ASSERTE(NULL != (IPersistStorage *)PS);

	HRESULT hr = PS -> HandsOffStorage();

		if (SUCCEEDED(hr)) {
			m_Stg.Release();
			m_StgMode = STGMODE_HandsOff;
		}
		return hr;
	}

protected:
	STGMODE m_StgMode;
	CComPtr<IStorage> m_Stg;					// Storage for targetdata
	CComPtr<IObjectManagement> m_ObjMan;		// StorageManagement for targetdata

	bool m_fIsDirty;
	bool m_fIsInitialized;

	static UINT m_cf;
};

///////////////////////////////////////////////////////////////////////////////
// static data
template <class T>
UINT IPersistStorageOMImpl<T>::m_cf = 0;

#endif // !defined(_PERSISTSTGIMPL_H__911535F4_837A_11D1_9778_00A024D6F582__INCLUDED_)
