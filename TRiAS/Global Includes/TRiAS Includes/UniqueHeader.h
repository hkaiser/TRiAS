///////////////////////////////////////////////////////////////////////////
// @doc 
// @module UniqueHeader.h | Eindeutige Handles aus Header besorgen

#if !defined(_UNIQUEHEADER_H__4356D8D4_D867_11D1_85F5_00600875138A__INCLUDED_)
#define _UNIQUEHEADER_H__4356D8D4_D867_11D1_85F5_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <HeaderEntry.h>

class _TRIAS01_ENTRY CUniqueHeader
{
public:
	enum UNIQUETYPE {
		UNIQUETYPE_ICODE = 1,
		UNIQUETYPE_SYSICODE = 2,
		UNIQUETYPE_MCODE = 3,
		UNIQUETYPE_SYSMCODE = 4,
		UNIQUETYPE_RCODE = 5,
	};

private:
	HPROJECT m_hPr;

protected:
	long GetUniqueLong (LPCSTR pcKey, long lFirstCode);

public:
	CUniqueHeader (HPROJECT hPr);
	long GetNextUniqueCode(UNIQUETYPE rgType);
};

#endif // !defined(_UNIQUEHEADER_H__4356D8D4_D867_11D1_85F5_00600875138A__INCLUDED_)
