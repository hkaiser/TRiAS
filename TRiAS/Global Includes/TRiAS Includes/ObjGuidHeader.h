///////////////////////////////////////////////////////////////////////////
// @doc 
// @module ObjGuidHeader.h | MerkmalsCode für ObjektGuid im Header verwalten

#if !defined(_OBJGUIDHEADER_H__66E01023_E723_11D1_8618_00600875138A__INCLUDED_)
#define _OBJGUIDHEADER_H__66E01023_E723_11D1_8618_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <HeaderEntry.h>

class _TRIAS01_ENTRY CObjGuidHeader
{
private:
	HPROJECT m_hPr;

public:
	CObjGuidHeader (HPROJECT hPr);
	long GetObjGuidCode();
};

#endif // !defined(_OBJGUIDHEADER_H__66E01023_E723_11D1_8618_00600875138A__INCLUDED_)
