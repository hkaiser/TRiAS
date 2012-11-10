// TRIASCSSet.cpp : Implementation of CTRiASCSSet
#include "stdafx.h"
#include "TRiASCsImpl.h"
#include "TRIASCSSet.h"

#if defined(_DEBUG)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

extern "C" const FMTID __declspec(selectany) FMTID_EnumTRiASCS = 
	{0x7cd5571e,0x6427,0x11d2,{0x9e,0xde,0x00,0x60,0x08,0x44,0x78,0x00}};

class matchDescription 
{
private:
	CComBSTR m_strSearch;

public:
	matchDescription( const BSTR& strSearch ) 
		: m_strSearch(strSearch)
	{
	}
	bool operator()( WTRiASCS cs ) 
	{
	CComBSTR strDescription;

		cs->get_Description( CLEARED(strDescription) );
		return strDescription == m_strSearch;
	}
};

ListOfCS::iterator	CTRiASCSSet::FindItem( const VARIANT& Item ) 
{
ListOfCS::iterator i = m_listOfCS.end();

	if( V_ISUNKNOWN(&Item) ) {
		i = find( m_listOfCS.begin(), m_listOfCS.end(), WTRiASCS( V_UNKNOWN(&Item) ) );
	} else if( V_ISDISPATCH(&Item) ) {
		i = find( m_listOfCS.begin(), m_listOfCS.end(), WTRiASCS( V_DISPATCH(&Item) ) );
	} else if( V_ISINTEGER(&Item) ) {
		CComVariant	v(Item);
		v.ChangeType(VT_UI4);
		if( V_UI4(&v) >= m_listOfCS.size() )
			return i;
		i = m_listOfCS.begin();
		advance( i, V_I4(&v) );
	} else if( V_ISBSTR(&Item) ) {
		i = find_if( m_listOfCS.begin(), m_listOfCS.end(), matchDescription( V_BSTR(&Item) ) );
	}
	return i;
}

/////////////////////////////////////////////////////////////////////////////
// CTRiASCSSet

STDMETHODIMP CTRiASCSSet::Add(VARIANT Item) 
{
	COM_TRY {
	WTRiASCS	cs;

		if( V_ISUNKNOWN(&Item)  ) {
			cs = V_UNKNOWN( &Item );
		} else if( V_ISDISPATCH(&Item) ) {
			cs = V_DISPATCH( &Item );
		}
		if( !cs )
			return S_FALSE;
		m_listOfCS.push_back( cs );
	} COM_CATCH
	return S_OK;
}

STDMETHODIMP CTRiASCSSet::Remove(VARIANT Item) 
{
	COM_TRY {
		ListOfCS::iterator i = FindItem( Item );
		if( i == m_listOfCS.end() )
			return S_FALSE;
		m_listOfCS.erase( i );
	} COM_CATCH
	return S_OK;
}

STDMETHODIMP CTRiASCSSet::Find(VARIANT Item, IDispatch** ppCS) 
{
	CHECKINPOINTER(ppCS);
	COM_TRY {
		ListOfCS::iterator i = FindItem( Item );
		if( i == m_listOfCS.end() )
			return S_FALSE;
		*ppCS = (*i);
		(*ppCS)->AddRef();
	} COM_CATCH
	return S_OK;
}

STDMETHODIMP CTRiASCSSet::_NewEnum(IUnknown * * ppIEnum) 
{
	CHECKINPOINTER(ppIEnum);
	WEnumWTRiASCS	E = GetEnum();
	MakeEnumVARIANT(E, GetUnknown(), ppIEnum );
	return S_OK;
}

STDMETHODIMP CTRiASCSSet::get_Count(long * pVal) 
{
	CHECKINPOINTER(pVal);
	*pVal = m_listOfCS.size();
	return S_OK;
}

HRESULT CTRiASCSSet::SaveToMemory( CHGLOBAL& hGlobal ) 
{
	WStream			s;
	CO_ERROR_FAILED_HRESULT( ::CreateStreamOnHGlobal( NULL, FALSE, s.ppi() ), E_FAIL );
	CO_ERROR_FAILED_HRESULT( ::OleSaveToStream( WPersistStream(GetUnknown()),s ), E_FAIL );
	HGLOBAL h = NULL;
	CO_ERROR_FAILED_HRESULT( ::GetHGlobalFromStream( s, &h ), E_FAIL );
	hGlobal = h;
	return S_OK;
}

HRESULT CTRiASCSSet::LoadFromMemory( CHGLOBAL& hGlobal ) {
	WStream	s;
	CO_ERROR_FAILED_HRESULT( ::CreateStreamOnHGlobal( *hGlobal, FALSE, s.ppi() ), E_FAIL );
	WTRiASCSSet	csset;
	CO_ERROR_FAILED_HRESULT( ::OleLoadFromStream( s, IID_ITRiASCSSet, csset.ppv() ), E_FAIL );
	ERROR_FAILED_HRESULT( CloneFrom( csset ), E_FAIL );
	return S_OK;
}

STDMETHODIMP CTRiASCSSet::SaveToFile(BSTR strFile) {
	CHGLOBAL	hGlob;
	ERROR_FAILED_HRESULT( SaveToMemory( hGlob ), TCS_E_CANNOTWRITEDATA );
	HANDLE hFile = ::CreateFileW( strFile
		, GENERIC_WRITE
		, NULL
		, NULL
		, CREATE_ALWAYS
		, FILE_ATTRIBUTE_NORMAL
		, NULL
		);
	SYS_ERROR( INVALID_HANDLE_VALUE == hFile, E_FAIL );
	DWORD	dwWritten = 0;
	SYS_ERROR( 0 == ::WriteFile( hFile, hGlob, hGlob.Size(), &dwWritten, NULL ), TCS_E_CANNOTWRITEDATA );
	SYS_ERROR( 0 == ::CloseHandle( hFile ), E_FAIL );
	return S_OK;
}

static HKEY regRoot( TCS_REGISTRYROOT root ) 
{
	return TCS_HKCR == root ? HKEY_CLASSES_ROOT :
		TCS_HKLM == root ? HKEY_LOCAL_MACHINE :
		TCS_HKCU == root ? HKEY_CURRENT_USER :
		TCS_HKCC == root ? HKEY_CURRENT_CONFIG :
		TCS_HKU == root ? HKEY_USERS :
		NULL
		;
}

STDMETHODIMP CTRiASCSSet::LoadFromFile(BSTR strFileName) 
{
	HANDLE	hFile = NULL;
	hFile = ::CreateFileW( strFileName
		, GENERIC_READ
		, FILE_SHARE_READ
		, NULL
		, OPEN_EXISTING
		, FILE_ATTRIBUTE_READONLY
		, NULL
		);
	SYS_ERROR( INVALID_HANDLE_VALUE == hFile, E_FAIL );
	DWORD	dwSize = ::GetFileSize( hFile, NULL );
	SYS_ERROR( 0xFFFFFFFFL == dwSize, E_FAIL );
	CHGLOBAL	hGlob(dwSize);
	DWORD	dwRead = 0;
	SYS_ERROR( 0 == ::ReadFile( hFile, hGlob, hGlob.Size(), &dwRead, NULL ), TCS_E_CANNOTREADDATA  );
	SYS_ERROR( 0 == ::CloseHandle( hFile ), E_FAIL);
	ERROR_FAILED_HRESULT( LoadFromMemory( hGlob ), TCS_E_INVALIDDATAFORMAT );
	return S_OK;
}

STDMETHODIMP CTRiASCSSet::SaveToRegistry(/*[in]*/ TCS_REGISTRYROOT _root, BSTR strRegKey, VARIANT strComputername) 
{
	CHGLOBAL	hGlob;
	ERROR_FAILED_HRESULT( SaveToMemory( hGlob ), TCS_E_CANNOTWRITEDATA );
	HKEY	root = regRoot( _root );
	ERROR_EXPR_FALSE( HKEY_LOCAL_MACHINE != root || HKEY_CURRENT_USER != root, TCS_E_ACCESS_DENIED );
	CRegKey	k;
	USES_CONVERSION;
	WIN_ERROR_NOTSUCCESS( k.Open( root, OLE2A(strRegKey) ), E_FAIL );
	WIN_ERROR_NOTSUCCESS( ::RegSetValueEx( k.m_hKey, _T("InstalledSystems"), NULL, REG_BINARY, (LPBYTE) (LPVOID) hGlob, hGlob.Size() ), TCS_E_CANNOTWRITEDATA );
	return S_OK;
}

STDMETHODIMP CTRiASCSSet::LoadFromRegistry(/*[in]*/ TCS_REGISTRYROOT _root, BSTR strRegKey, VARIANT strComputername) {
	HKEY	root = regRoot( _root );
	ERROR_EXPR_FALSE( HKEY_LOCAL_MACHINE != root || HKEY_CURRENT_USER != root, TCS_E_ACCESS_DENIED );
	CRegKey	k;
	USES_CONVERSION;
	WIN_ERROR_NOTSUCCESS( k.Open( root, OLE2A(strRegKey) ), E_FAIL );
	DWORD	dwType = 0, dwSize = 0;
	WIN_ERROR_NOTSUCCESS( ::RegQueryValueEx( k.m_hKey, _T("InstalledSystems"), NULL, &dwType, NULL, &dwSize ), TCS_E_CANNOTREADDATA );
	ERROR_EXPR_TRUE( REG_BINARY != dwType || 0 == dwSize, TCS_E_INVALIDDATAFORMAT );
	CHGLOBAL	hGlob(dwSize);
	WIN_ERROR_NOTSUCCESS( ::RegQueryValueEx( k.m_hKey, _T("InstalledSystems"), NULL, &dwType, (LPBYTE) (LPVOID) hGlob, &dwSize ), TCS_E_CANNOTREADDATA );
	ERROR_FAILED_HRESULT( LoadFromMemory( hGlob ), TCS_E_INVALIDDATAFORMAT );
	return S_OK;
}

DefineSmartInterface(EnumVARIANT)

HRESULT	CTRiASCSSet::CloneFrom(/*[in]*/ ITRiASCSSet* pSourceSet) {
	m_listOfCS.clear();
	WEnumVARIANT	e;
	CComVariant		v;
	pSourceSet->_NewEnum( e.ppu() );
	for( e->Reset(); S_OK == e->Next( 1, &v, NULL ); ) {
		if( V_ISDISPATCH(&v) ) {
			WTRiASCS	cs(V_DISPATCH(&v));
			m_listOfCS.push_back(cs);
		}
	}
	return S_OK;
}

class SizeContainedObject {
	DWORDLONG&	m_rSize;
public:
	SizeContainedObject( DWORDLONG& rSize )
		: m_rSize(rSize) {
	}
	void operator()( IUnknown *o ) {
		ULARGE_INTEGER	size;
		size.QuadPart = 0;
		WPersistStreamInit(o)->GetSizeMax(&size);
		m_rSize += size.QuadPart;
	}
};

class SaveContainedObject {
	WStream	m_pStm;
	BOOL	m_bClearDirty;
public:
	SaveContainedObject(LPSTREAM p, BOOL b) 
		: m_pStm(p)
		, m_bClearDirty(b) {
	}
	void operator()( IUnknown *o ) {
		SaveItem( m_pStm, WPersistStream( o ) );
	}
};

class InitContainedObject {
public:
	InitContainedObject() {
	}
	void operator()( IUnknown *o ) {
		WPersistStreamInit(o)->InitNew();
	}
};

/////////////////////////////////////////////////////////////////////////////
// CPersistStreamInit

HRESULT	CTRiASCSSet::OnInitNew( ) {
	for_each( m_listOfCS.begin(), m_listOfCS.end(), InitContainedObject() );
	return S_OK;
}

HRESULT CTRiASCSSet::LoadData( LPSTREAM pStm, DWORD dwVersion ) {
	ULONG	nItems, nItem;
	HRESULT	hr;
	ERROR_FAILED_HRESULT( hr = LoadItem( pStm, nItems ), hr );
	for( nItem = 0; nItem < nItems; nItem++ ) {
		WTRiASCS	cs;
		ERROR_FAILED_HRESULT( hr = LoadItem( pStm, IID_ITRiASCS, cs.ppu() ), hr );
		m_listOfCS.push_back(cs);
	}
	return S_OK;
}

HRESULT CTRiASCSSet::SaveData( LPSTREAM pStm, BOOL bClearDirty ) {
	ULONG	nItems = m_listOfCS.size();
	HRESULT	hr;
	ERROR_FAILED_HRESULT( hr = SaveItem( pStm, nItems ), hr );
	for_each( m_listOfCS.begin(), m_listOfCS.end(), SaveContainedObject(pStm,bClearDirty) );
	return S_OK;
}

DWORDLONG	CTRiASCSSet::GetDataSize( ) {
	DWORDLONG	size(0);
	for_each( m_listOfCS.begin(), m_listOfCS.end(), SizeContainedObject( size ) );
	return sizeof(ULONG) + size;
}
