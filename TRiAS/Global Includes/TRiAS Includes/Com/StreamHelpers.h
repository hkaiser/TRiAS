#if !defined(_TRIASSTREAMHELPERS_8C982590_584C_11d2_8FCA_0060085FC1CE)
#define	_TRIASSTREAMHELPERS_8C982590_584C_11d2_8FCA_0060085FC1CE

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Com/PersistHelper.h>

///////////////////////////////////////////////////////////////////////////////////
// spezielle sizeof's für BSTR / VARIANT
inline long SIZEOF( const BSTR &s ) 
{
	return (s ? ::SysStringByteLen(s) + sizeof(OLECHAR) : 0) + sizeof(ULONG);
}

inline long SIZEOF( const CComBSTR &s ) 
{
	return (s.m_str ? ::SysStringByteLen(s.m_str)+sizeof(OLECHAR) : 0) + sizeof(ULONG);
}

inline long SIZEOF( const VARIANT& v ) {
	CComVariant	_v(v);
	WStream	pStream;
	HGLOBAL	hglbl;
	::CreateStreamOnHGlobal( NULL, TRUE, pStream.ppi() );
	_v.WriteToStream( pStream );
	::GetHGlobalFromStream( pStream, &hglbl );
	return ::GlobalSize( hglbl );
}

inline long SIZEOF( const CComVariant &v ) 
{
	return SIZEOF( (const VARIANT&) v );
}

///////////////////////////////////////////////////////////////////////////////////
// 
template<class T>
inline HRESULT LoadItem(IStream *pIStm, T &rVal) 
{
#if defined(_DEBUG)
	long size = sizeof(T);
#endif // defined(_DEBUG)
	ULONG	ulSize;
	return SUCCEEDED( pIStm->Read (&rVal, sizeof(T), &ulSize) ) && ulSize == sizeof(T) ? S_OK : STG_E_READFAULT;
}

inline HRESULT LoadItem(IStream *pIStm, CComBSTR &s ) 
{
	CComBSTR	S;	// lokaler CComBSTR, damit m_str == NULL
	HRESULT	hr = S.ReadFromStream( pIStm );
	s = S.Detach();
	return hr;
}

inline HRESULT LoadItem(IStream *pIStm, REFIID riid, IUnknown** ppu ) 
{
	return ::OleLoadFromStream( pIStm, riid, (void**) ppu );
}

inline HRESULT LoadItem(IStream *pIStm, CComVariant& var ) 
{
	return var.ReadFromStream( pIStm );
}

template<typename T, typename Target, typename pred>
inline HRESULT LoadItemInd (IStream *pIStm, Target *ptarget, pred f)
{
T data;

	RETURN_FAILED_HRESULT(LoadItem (pIStm, data));
	return (ptarget ->* f)(data);
}

///////////////////////////////////////////////////////////////////////////////////
// 
template<typename T>
inline HRESULT SaveItem(IStream *pIStm, const T &Val) 
{
	long size = sizeof(T);
	ULONG	ulSize;
	return SUCCEEDED( pIStm->Write (&Val, sizeof(T), &ulSize ) ) && ulSize == sizeof(T) ? S_OK : STG_E_WRITEFAULT;
}

inline HRESULT SaveItem(IStream *pIStm, /*const*/ CComBSTR &s ) 
{
	return s.WriteToStream( pIStm );
}

inline HRESULT SaveItem(IStream *pIStm, const BSTR &s ) 
{
	return CComBSTR(s).WriteToStream( pIStm );
}

inline HRESULT SaveItem(IStream *pIStm, IPersistStreamPtr& pSaver ) 	// $INCLUDE/comdef.h
{
	return ::OleSaveToStream( pSaver, pIStm );
}

inline HRESULT SaveItem(IStream *pIStm, WPersistStream& pSaver ) 		// ospace/com/smartif.h
{
	return ::OleSaveToStream( pSaver, pIStm );
}

inline HRESULT SaveItem(IStream *pIStm, const VARIANT& var ) 
{
	return CComVariant(var).WriteToStream( pIStm );
}

inline HRESULT SaveItem(IStream *pIStm, CComVariant& var ) 
{
	return var.WriteToStream( pIStm );
}

template<typename T, typename Target, typename pred>
inline HRESULT SaveItemInd(IStream *pIStm, Target *ptarget, pred f)
{
T data;

	RETURN_FAILED_HRESULT((ptarget ->* f)(&data));
	return SaveItem(pIStm, data);
}

///////////////////////////////////////////////////////////////////////////////////
// @doc FUNCTION STREAMHELP
// @function SaveObject
// @normal Speichert ein Objekt unter seinem CLSID in einem Stream ab. CLSID
//		und (ggf. vorhandene) Objektdaten werden getrennt gespeichert.
//		Damit können Streams erzeugt werden, die auch auf Rechnern auf denen das
//		gespeicherte Objekt nicht wieder instantiiert werden kann, nicht zu einem
//		Fehlverhalten führen.

inline HRESULT SaveObject( LPSTREAM pStream, IUnknown* pObject, BOOL bClearDirty ) 
{
WStream		pStreamOfObject;
DWORD		dwBlobSize = 0;
HGLOBAL		hglbl = NULL;
CLSID		clsid(CLSID_NULL);
WPersistStreamInit	pPersistStreamInit;

	if( SUCCEEDED( pObject->QueryInterface( pPersistStreamInit.GetIID(), pPersistStreamInit.ppv() ) ) ) {
		RETURN_FAILED_HRESULT( ::CreateStreamOnHGlobal( NULL, true, pStreamOfObject.ppi() ) );
		RETURN_FAILED_HRESULT( pPersistStreamInit->Save( pStreamOfObject, bClearDirty ) );
		RETURN_FAILED_HRESULT( ::GetHGlobalFromStream( pStreamOfObject, &hglbl ) );
		dwBlobSize = ::GlobalSize( hglbl );
		RETURN_FAILED_HRESULT( pPersistStreamInit->GetClassID(&clsid) );
	}

ULONG	nWritten;

	pStream->Write( &clsid, sizeof(clsid), &nWritten );
	pStream->Write( &dwBlobSize, sizeof(dwBlobSize), &nWritten );
	if( dwBlobSize && hglbl ) {
		void* pData = ::GlobalLock( hglbl );
		pStream->Write( pData, dwBlobSize, &nWritten );
		::GlobalUnlock( hglbl );
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////////
// @doc FUNCTION STREAMHELP
// @function LoadObject
// @normal Das Gegenstück zu SaveObject.

inline 
HRESULT LoadObject (LPSTREAM pStream, IUnknown** ppIObject) 
{
	RETURN_EXPR_TRUE(NULL == ppIObject, E_POINTER);
	RETURN_EXPR_TRUE(NULL != *ppIObject, E_INVALIDARG);

CLSID clsid;
DWORD dwBlobSize = 0;
ULONG nRead;

	pStream->Read(&clsid, sizeof(clsid), &nRead);
	pStream->Read(&dwBlobSize, sizeof(dwBlobSize), &nRead);

HGLOBAL	hglbl = ::GlobalAlloc(GHND, dwBlobSize);
void* pData = ::GlobalLock(hglbl);

	pStream -> Read(pData, dwBlobSize, &nRead);
	::GlobalUnlock(hglbl);

	if (CLSID_NULL != clsid) {
	WUnknown pUnknown;

		RETURN_FAILED_HRESULT(::CoCreateInstance (clsid, NULL, CLSCTX_ALL, pUnknown.GetIID(), pUnknown.ppv()));

	WPersistStreamInit pPersistStreamInit;
	WStream	pStreamOfObject;

		::CreateStreamOnHGlobal (hglbl, true, pStreamOfObject.ppi());
		RETURN_FAILED_HRESULT(pUnknown->QueryInterface (pPersistStreamInit.ppi()));
		RETURN_FAILED_HRESULT(pPersistStreamInit -> InitNew());
		pPersistStreamInit -> Load (pStreamOfObject);

		*ppIObject = pUnknown.detach();
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////////
// 
template<class T>
inline void LoadAndAdvance (T &x, void *& p) 
{
	memcpy ((void *)&x, p, sizeof(T));
	p = (BYTE *)p + sizeof(T);
}

template<class T>
inline void SaveAndAdvance (void *& p, T x) 
{
	memcpy (p, (void *)&x, sizeof(T));
	p = (BYTE *)p + sizeof(T);
}

inline void LoadAndAdvance (void *px, void *&p, unsigned int iSize) 
{
	memcpy (px, p, iSize);
	p = (BYTE *)p + iSize;
}

inline void SaveAndAdvance (void *&p, void *px, unsigned int iSize) 
{
	memcpy (p, px, iSize);
	p = (BYTE *)p + iSize;
}

///////////////////////////////////////////////////////////////////////////
// @class CPersistStreamInitImpl
// @tcarg class | T | Die Klasse welche von <b IPersistStreamInit> abgeleitet ist.
// @tcarg const CLSID* | pCLSID | Der Class-ID von <b T>.

template<typename T, const CLSID* pCLSID = &T::GetObjectCLSID()>
class ATL_NO_VTABLE CPersistStreamInitImpl
	: public CPersistImpl<T, IPersistStreamInit, pCLSID>
{
public:
	typedef CPersistStreamInitImpl<T, pCLSID> CPersistStreamInitImpl_t;
	typedef CPersistImpl<T, IPersistStreamInit, pCLSID> CPersistImpl_t;

	CPersistStreamInitImpl() {}
	~CPersistStreamInitImpl() {}

	BEGIN_COM_MAP(CPersistStreamInitImpl)
		COM_INTERFACE_ENTRY(IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersistStream, IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
	END_COM_MAP()

// IPersistStream
	STDMETHOD(IsDirty)() 
	{
		return IsObjectDirty() ? S_OK : S_FALSE;
	}
	STDMETHOD(Load)(LPSTREAM pStm) 
	{
	DWORD dwSignat;
	DWORD dwVersion;

		RETURN_FAILED_HRESULT(LoadItem (pStm, dwSignat));
		if (dwSignat != static_cast<T *>(this) -> GetSignature())
			return E_UNEXPECTED;	// bad signature

		RETURN_FAILED_HRESULT(LoadItem (pStm, dwVersion));
		RETURN_FAILED_HRESULT(static_cast<T *>(this) -> LoadData (pStm, dwVersion));
		return S_OK;
	}
	STDMETHOD(Save)(LPSTREAM pStm, BOOL bClearDirty = TRUE) 
	{
	DWORD dw = static_cast<T *>(this) -> GetSignature();

		RETURN_FAILED_HRESULT(SaveItem(pStm, dw));
		dw = static_cast<T *>(this) -> GetVersion();							
		RETURN_FAILED_HRESULT(SaveItem(pStm, dw));

	HRESULT hr = static_cast<T *>(this) -> SaveData( pStm, bClearDirty );

		if (SUCCEEDED(hr) && bClearDirty)
			SetDirty(false);
		return hr;
	}
	STDMETHOD(GetSizeMax)(ULARGE_INTEGER *pcbSize) 
	{
		pcbSize -> QuadPart = GetDataSize() + static_cast<T *>(this) -> GetDataSize();
		return S_OK;
	}

// IPersistStreamInit
	STDMETHOD(InitNew)() 
	{
		_ASSERTE(!IsInitialized());
		if (SUCCEEDED(static_cast<T *>(this) -> OnInitNew())) {
			SetDirty(false);
			SetInitialized();
			return S_OK;
		}
		return E_FAIL;
	}
};

/***************************************************************************
@doc 
@topic Anwendung von CPersistStreamInitImpl |
Wir haben ein COM-Objekt mit drei Datenmembern die gespeichert werden müssen.
Dabei sind die Member m_strData2 bzw. m_pData3 erst später (ab Version 
FOO_VER_WITH2MEMBERS bzw. FOO_VER_WITHBARMEMBER) hinzugekommen.
Zu beachten ist die Behandlung von COM-Objekten bei Load/Save sowie des BSTR
bei der Berechnung der Größe.
@ex Anwendung von CPersistStreamInitImpl |

#define	FOO_VER_WITH1MEMBER		0x00001000L
#define FOO_VER_WITH2MEMBERS	0x00001001L
#define FOO_VER_WITHBARMEMBER	0x00001002L
#define FOO_LAST_KNOWNVERSION	FOO_VER_WITHBARMEMBER

DefineSmartInterface(WPersistStream)

#include "ClassBar.h"
DefineSmartInterface(WBar)

class CFoo : 
	public CComObjectRootEx<CComSingleThreadModel>
	, ....
	, public CPersistStreamInitImpl< CFoo, &CLSID_Foo >
{
	DWORD		m_dwData1;		// erstes Datum
	CComBSTR	m_strData2;		// zweites Datum
	WBar		m_pData3;		// drittes Datum
public:
	BEGIN_COM_MAP(CFoo)
		...
		COM_INTERFACE_ENTRY(IPersistStreamInit)
	END_COM_MAP()
	HRESULT	OnInitNew( ) {
		m_dwData1 = 0;
		m_strData2 = _T("irgendwas sinnvolles");
		return WPersistStreamInit(m_pData3)->InitNew();
	}
	HRESULT LoadData( LPSTREAM pStm, DWORD dwVersion ) {
		LoadItem( pStm, m_dwData1 );
		if( dwVersion >= FOO_VER_WITH2MEMBERS )
			LoadItem( pStm, m_strData2 );
		if( dwVersion >= FOO_VER_WITHBARMEMBER )
			LoadItem( pStm, IID_IBar, m_pData3.ppu() );
		return S_OK;
	}
	HRESULT SaveData( LPSTREAM pStm ) {
		SaveItem( pStm, m_dwData1 );
		SaveItem( pStm, m_strData2 );
		SaveItem( pStm, WPersistStream( m_pData3 ) );
		return S_OK;
	}
	LONGLONG GetDataSize( ) {
		ULARGE_INTEGER	uliSize;
		WPersistStream(m_pData3)->GetSizeMax( &uliSize );
		return sizeof(m_dwData1) + SIZEOF(m_dwData2) + uliSize.QuadPart;
	}
	DWORD	GetSignature( ) { char *s = "CFoo"; return *((DWORD*)s); }
	DWORD	GetVersion( ) { return FOO_LAST_KNOWNVERSION; }
};

***************************************************************************/
#endif // _TRIASSTREAMHELPERS_8C982590_584C_11d2_8FCA_0060085FC1CE
