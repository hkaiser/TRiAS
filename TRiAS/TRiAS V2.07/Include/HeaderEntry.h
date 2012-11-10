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

///////////////////////////////////////////////////////////////////////////////
// CHeaderEntry

#define HEADERKEYLEN	16

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
	HRESULT GetHeaderEntry (LPSTR pBuffer, size_t iLen, long *pFlags);
	HRESULT PutHeaderEntry (LPCSTR pcText, size_t iLen, long lFlags);
	HRESULT DeleteHeaderEntry (void);
	HRESULT EnumHeaderData (HRESULT (CALLBACK *pFcn)(LPCSTR, DWORD), DWORD dwData);

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

#endif // !defined(_DBHEADER_H__009EE9E4_3F19_11d1_96C3_00A024D6F582__INCLUDED_)
