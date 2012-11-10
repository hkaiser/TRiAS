// @doc
// @module HeaderEntry.h | Klassendefinition zum Zugriff auf die Headerinformationen 
// eines Projektes bzw. einer Database 
// @xref <c CDBHeader>

#if !defined(_DBHEADER_H__009EE9E4_3F19_11d1_96C3_00A024D6F582__INCLUDED_)
#define _DBHEADER_H__009EE9E4_3F19_11d1_96C3_00A024D6F582__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <riw.h>
#include <risdb.h>

namespace trias_nativeheader {

///////////////////////////////////////////////////////////////////////////////
// CHeaderEntry

#define HEADERKEYLEN	16

#if !defined(_XTENSION_H)
#define HEADER_NORMAL	0x00
#define HEADER_SYSTEM	0x01
#define HEADER_READONLY	0x02
#define HEADER_SYSTEMRO	0x03
#define HEADER_DYNAMIC	0x04
#endif // _XTENSION_H

class _TRIAS01_ENTRY CHeaderEntry
{
protected:
	CHeaderEntry (HPROJECT hPr, LPCSTR pcKey)	// nur als BasisKlasse verwenden
		: m_hPr(hPr)
	{
		PrepareKey (pcKey);
	}

	HRESULT PrepareKey (LPCSTR pcKey);

public:
// Zugriffsfunktionen
	HRESULT GetHeaderEntryLen (size_t *plLen);
	HRESULT GetHeaderEntry (LPSTR pBuffer, size_t iLen, long *pFlags = NULL);
	HRESULT PutHeaderEntry (LPCSTR pcText, size_t iLen = 0, long lFlags = HEADER_NORMAL);
	HRESULT DeleteHeaderEntry (void);
	HRESULT EnumHeaderData (HRESULT (CALLBACK *pFcn)(LPCSTR, UINT_PTR), UINT_PTR dwData);

	long GetHeaderLong (long lDefault = 0L, long *plFlags = NULL);
	HRESULT PutHeaderLong (long lEntry, long lFlags = 0);
	double GetHeaderDouble (double dDefault = 0.0, long *plFlags = NULL);
	HRESULT PutHeaderDouble (double dEntry, long lFlags = 0);

protected:
// data member
	HPROJECT m_hPr;
	char m_cbKey[HEADERKEYLEN+1];	// Suchschlüssel
	UINT m_uiKey;					// Dateinummern
	UINT m_uiFile;
	UINT m_uiFileNext;

protected:
// operations
	HRESULT StoreHeaderEntryHelper (LPCSTR pcText, size_t iLen, long lFlags);
	HRESULT DeleteHeaderEntryHelper (struct db_addr *dba);
};

class _TRIAS01_ENTRY CDBHeader :
	public CHeaderEntry
{
public:
	CDBHeader (HPROJECT hPr, LPCSTR pcKey = NULL)
		: CHeaderEntry (hPr, pcKey)
	{
		m_uiKey = HDIDN;
		m_uiFile = HEAD;
		m_uiFileNext = FHEAD;
	}
};

class _TRIAS01_ENTRY CPrjHeader :
	public CHeaderEntry
{
public:
	CPrjHeader (HPROJECT hPr, LPCSTR pcKey = NULL)
		: CHeaderEntry (hPr, pcKey)
	{
		m_uiKey = PRJHDIDN;
		m_uiFile = PRJHEAD;
		m_uiFileNext = PRJFHEAD;
	}
};

inline long GetHeaderLong (HPROJECT hPr, LPCSTR pcKey, long lDefault, int iBase)
{
char cbBuffer[_MAX_PATH];
CDBHeader Hdr (hPr, pcKey);

	if ( SUCCEEDED( Hdr.GetHeaderEntry(cbBuffer, _countof(cbBuffer)) ) )
		return strtol (cbBuffer, NULL, iBase);

	return lDefault;
} 

};	// namespace trias_nativeheader

#endif // !defined(_DBHEADER_H__009EE9E4_3F19_11d1_96C3_00A024D6F582__INCLUDED_)
