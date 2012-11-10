//////////////////////////////////////////////////////////////////////////
// @doc 
// @module iterenumDef.h |
// voredefinierte IID's / Enumeratordefinitionen 

#if !defined(__ITERENUMDEF_H__510D0D60_02BD_11d3_B6C6_006008A80E6A)
#define __ITERENUMDEF_H__510D0D60_02BD_11d3_B6C6_006008A80E6A

//////////////////////////////////////////////////////////////////////////
// IID-Definitionen für 'ne Menge von Datentypen

//////////////////////////////////////////////////////////////////////////
// (1) Systemtypen / Interfaces

extern "C" const IID __declspec(selectany) IID_IEnumDispatch = 
	{0x28a55900,0xa2fb,0x11d1,{0xa0,0x52,0x00,0x60,0x97,0x55,0x66,0xb4}};

DefineEnumerator2(WDispatch,IID_IEnumDispatch)				// NEnumWDispatch
DefineSmartEnumerator2(WDispatch,IID_IEnumDispatch)			// WEnumWDispatch

//////////////////////////////////////////////////////////////////////////
// Ospace-STL

#if defined(OS_STRING_STRING_H)

extern "C" const IID __declspec(selectany) IID_IEnumos_wstring = 
	{0x0796384f,0x3123,0x101c,{0xbb,0x62,0x00,0xaa,0x00,0x18,0x49,0x7c}};
//DefineEnumerator2(os_wstring, IID_IEnumos_wstring);
//DefineSmartEnumerator2(os_wstring, IID_IEnumos_wstring);

#endif // OS_STRING_STRING_H

#endif // __ITERENUMDEF_H__510D0D60_02BD_11d3_B6C6_006008A80E6A