#include "StdAfx.h"
#include "TRiASCSImpl.h"

#pragma comment(lib, "version.lib")

class CModuleVersion : public VS_FIXEDFILEINFO 
{
	BYTE* m_pVersionInfo;	// all version info
	struct TRANSLATION {
		WORD langID;			// language ID
		WORD charset;			// character set (code page)
	} m_translation;

protected:
	bool		SplitVersion( LPCTSTR lpszVersion, long *dwVerMajor = NULL, long *dwVerMinor = NULL, long *dwBldMajor = NULL, long *dwBldMinor = NULL );

public:
	CModuleVersion( );
	virtual ~CModuleVersion();
	bool		InitVersionInfo( LPCTSTR lpszModulename );
	bool		InitVersionInfo( HINSTANCE hModule );
	CComBSTR	QueryVersionInfo( LPCTSTR lpszKey );
	////////////////////////////////////////////////////////////
	// Modulversion
	CComBSTR	GetModuleVersion( );
	long 	GetModuleMajor( );
	long 	GetModuleMinor( );
	long 	GetModuleBuildMajor( );
	long 	GetModuleBuildMinor( );
};

CModuleVersion::CModuleVersion() {
	m_pVersionInfo = NULL;				// raw version info data 
}

CModuleVersion::~CModuleVersion() {
	delete [] m_pVersionInfo;
}

bool CModuleVersion::InitVersionInfo( HINSTANCE hModule ) {
	if( NULL == hModule )
		return false;
	TCHAR filename[_MAX_PATH];
	DWORD len = ::GetModuleFileName( hModule, filename, sizeof(filename)/sizeof(filename[0]) );
	if (len <= 0)
		return false;

	DWORD dwDummyHandle; // will always be set to zero
	len = ::GetFileVersionInfoSize( filename, &dwDummyHandle );
	if (len <= 0)
		return false;
	m_pVersionInfo = new BYTE[len]; // allocate version info
	if (!::GetFileVersionInfo(filename, 0, len, m_pVersionInfo))
		return false;
	LPVOID lpvi;
	UINT iLen;
	if (!VerQueryValue(m_pVersionInfo, _T("\\"), &lpvi, &iLen))
		return false;
	*(VS_FIXEDFILEINFO*)this = *(VS_FIXEDFILEINFO*)lpvi;
	if (VerQueryValue(m_pVersionInfo,
		"\\VarFileInfo\\Translation", &lpvi, &iLen) && iLen >= 4) {
		m_translation = *(TRANSLATION*)lpvi;
	}
	if( dwSignature != VS_FFI_SIGNATURE )
		return false;
	return true;
}

bool CModuleVersion::InitVersionInfo( LPCTSTR lpszModulename ) {
	m_translation.charset = 1252;		// default = ANSI code page
	memset((VS_FIXEDFILEINFO*)this, 0, sizeof(VS_FIXEDFILEINFO));
	
	HMODULE hModule = ::GetModuleHandle(lpszModulename);
	return InitVersionInfo( hModule );
}

CComBSTR	CModuleVersion::QueryVersionInfo( LPCTSTR lpszKey ) {
	CComBSTR	strValue;
	if (!m_pVersionInfo)
		return strValue;
	TCHAR	buf[_MAX_PATH];
	wsprintf( buf, _T("\\StringFileInfo\\%04x%04x\\%s"), m_translation.langID, m_translation.charset, lpszKey );
	LPCTSTR	pVal;
	UINT	iLenVal;
	if( ::VerQueryValue( m_pVersionInfo, (LPTSTR)(LPCTSTR)buf, (LPVOID*)&pVal, &iLenVal)) {
		strValue = pVal;
	}
	return strValue;
}
#include <stdio.h>
bool CModuleVersion::SplitVersion( LPCTSTR lpszVersion, long *dwVerMajor, long *dwVerMinor, long *dwBldMajor, long *dwBldMinor ) {
	long	l1 = 0, l2 = 0, l3 = 0, l4 = 0;
	sscanf( lpszVersion, _T("%d.%d.%d.%d"), &l1, &l2, &l3, &l4 );
	if( dwVerMajor )
		*dwVerMajor = l1;
	if( dwVerMinor )
		*dwVerMinor = l2;
	if( dwBldMajor )
		*dwBldMajor = l3;
	if( dwBldMinor )
		*dwBldMinor = l4;
	return true;
}

long CModuleVersion::GetModuleMajor( ) {
	long d;
	USES_CONVERSION;
	CComBSTR	strVersion = QueryVersionInfo( _T("FileVersion") );
	SplitVersion( OLE2A(strVersion), &d, NULL, NULL, NULL );
	return d;
}
long CModuleVersion::GetModuleMinor( ) {
	long d;
	USES_CONVERSION;
	CComBSTR	strVersion = QueryVersionInfo( _T("FileVersion") );
	SplitVersion( OLE2A(strVersion), NULL, &d, NULL, NULL );
	return d;
}
long CModuleVersion::GetModuleBuildMajor( ) {
	long d;
	USES_CONVERSION;
	CComBSTR	strVersion = QueryVersionInfo( _T("FileVersion") );
	SplitVersion( OLE2A(strVersion), NULL, NULL, &d, NULL );
	return d;
}
long CModuleVersion::GetModuleBuildMinor( ) {
	long d;
	USES_CONVERSION;
	CComBSTR	strVersion = QueryVersionInfo( _T("FileVersion") );
	SplitVersion( OLE2A(strVersion), NULL, NULL, NULL, &d  );
	return d;
}

class CTRiASModuleVersion : public CModuleVersion {
public:
	CTRiASModuleVersion() {}
	long GetNeededTRiASMajor( );
	long GetNeededTRiASMinor( );
};

long CTRiASModuleVersion::GetNeededTRiASMajor( ) {
	long d;
	USES_CONVERSION;
	CComBSTR	strVersion = QueryVersionInfo( _T("ProductVersion") );
	SplitVersion( OLE2A(strVersion), &d, NULL, NULL, NULL  );
	return d;
}
long CTRiASModuleVersion::GetNeededTRiASMinor( ) {
	long d;
	USES_CONVERSION;
	CComBSTR	strVersion = QueryVersionInfo( _T("ProductVersion") );
	SplitVersion( OLE2A(strVersion), NULL, &d, NULL, NULL );
	return d;
}

/////////////////////////////////////////////////////////////////////////////
// Registrierungsschlüssel

CTRiASCCSKeys::CTRiASCCSKeys( LPCOLESTR strRoot )
	: CTRiASExtensionRegKey( strRoot, IDR_DEFHKLM )
{
	CTRiASModuleVersion	modVer;
	modVer.InitVersionInfo( _Module.GetModuleInstance() );
	long	dwTRiASMajor = modVer.GetNeededTRiASMajor();
//	long	dwTRiASMinor = modVer.GetNeededTRiASMinor();
	put_TRiASMajor( dwTRiASMajor );
	put_TRiASMinor( 0 /*dwTRiASMinor*/ );
}

///////////////////////////////////////////////////////////
// DEBUG-Support
#if defined(_ATLX_DEBUG_REFCOUNT_WALKSTACK)

//#define _USE_BSCKIT
#include <AtlDebug.h>

CIIDsToAnalyse g_IIDsToAnalyse;

BEGIN_DEBUGSUPPORT_MAP()
	DEBUGSUPPORT_ENTRY(IID_ITRiASCS)
	DEBUGSUPPORT_ENTRY(IID_ITRiASCSPCS)
	DEBUGSUPPORT_ENTRY(IID_ITRiASCSGCS)
	DEBUGSUPPORT_ENTRY(IID_ITRiASCSTransform)
END_DEBUGSUPPORT_MAP()

#include <AtlDebug.cpp>

#endif // _ATLX_DEBUG_REFCOUNT_WALKSTACK
