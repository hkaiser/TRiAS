///////////////////////////////////////////////////////////////////////////
// @doc 
// @module OBJSTAT.HXX | ObjektStatus

#if !defined(_OBJSTAT_HXX__766329D3_0736_11D2_8657_00600875138A__INCLUDED_)
#define _OBJSTAT_HXX__766329D3_0736_11D2_8657_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

enum ObjStatus { 
	OS_Normal = 0, 
	OS_Temp = 1, 
	OS_Invalid = 2, 
	OS_Modified = 4,
};

#endif // !defined(_OBJSTAT_HXX__766329D3_0736_11D2_8657_00600875138A__INCLUDED_)
