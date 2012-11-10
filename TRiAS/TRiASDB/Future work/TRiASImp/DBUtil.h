///////////////////////////////////////////////////////////////////////////
// Allgemeine Makrodefinitionen et.al.
// File: DBUTIL.H

#if !defined(_DBUTIL_H__B728BBE5_2FED_11d1_96A0_00A024D6F582__INCLUDED_)
#define _DBUTIL_H__B728BBE5_2FED_11d1_96A0_00A024D6F582__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

///////////////////////////////////////////////////////////////////////////////
// FehlerMeldung formatieren und ausgeben
#if defined(_DEBUG)
#define REPORT_DBERROR_IID(hr,rout,riid) Error(hr,rout,riid)
#define REPORT_DBERROR_ROUT(hr,rout) Error(hr,rout)
#define REPORT_DBERROR(hr) Error(hr)
#else
#define REPORT_DBERROR_IID(hr,rout,riid) Error(hr,NULL,riid)
#define REPORT_DBERROR_ROUT(hr,rout) Error(hr)
#define REPORT_DBERROR(hr) Error(hr)
#endif // _DEBUG


// Kein Speicher mehr !
#define REPORT_OUTOFMEMORY() return Error (g_cbNoMemory, E_OUTOFMEMORY)

// FormatMessage aus MessageTyble in ein CString
void __cdecl FormatMessage (CString &rStr, UINT uiError, ...);

// MessageBox anzeigen, Text ist formatierbar 
int __cdecl VMessageBox (UINT uiCaption, UINT uiType, UINT uiText, ...);
int __cdecl VMessageBox (LPCSTR pcCaption, UINT uiType, UINT uiText, ...);
os_string __cdecl FakeTRiASName (UINT resID, ...);
os_string __cdecl FakeTRiASName (LPCSTR pcTempl, ...);

///////////////////////////////////////////////////////////////////////////////
// Größe eines Arrays
#define _countof(x) (sizeof(x)/sizeof(x[0]))

///////////////////////////////////////////////////////////////////////////////
// Anzahl der Bytes für ein BSTR in einem Stream
inline 
ULONG LenForStream (CComBSTR bstr)
{
	return (bstr.m_str ? ::SysStringByteLen(bstr.m_str)+sizeof(OLECHAR) : 0) + sizeof(ULONG);
}

inline
HRESULT LoadLong (IStream *pIStm, long &riVal)
{
	return pIStm -> Read (&riVal, sizeof(long), NULL);
}

inline
HRESULT SaveLong (IStream *pIStm, long iVal)
{
	return pIStm -> Write (&iVal, sizeof(long), NULL);
}

///////////////////////////////////////////////////////////////////////////////
// sonstige globale Funktionsdeklarationen
HRESULT GetSubStorage (IStorage *pIRootStg, LPCOLESTR pcoleName, REFCLSID rClsId, IStorage **ppIStg, bool fCreate = false);
HRESULT GetSubStream (IStorage *pIRootStg, LPCOLESTR pcoleName, IStream **ppIStm, bool fCreate = false);

// WindowsVersion
bool WINAPI IsWin31 (void);
bool WINAPI IsWin40 (void);
bool WINAPI IsWin41 (void);
bool WINAPI IsWin32s (void);
bool WINAPI IsWinNT (void);

///////////////////////////////////////////////////////////////////////////////
// nützliche Datendefinitionen
typedef enum tagSTGMODE {
	STGMODE_Normal = 0x01,
	STGMODE_NoScribble = 0x02,

	STGMODE_HandsOff = 0x10,
	STGMODE_HandsOffAfterNormal = 0x14,
	STGMODE_HandsOffAfterSave = 0x18,

	STGMODE_Unknown = 0,
} STGMODE;


#endif // !defined(_DBUTIL_H__B728BBE5_2FED_11d1_96A0_00A024D6F582__INCLUDED_)
