// @doc
// @module Wrapper.h | Definition verschiedener SmartIF's etc.

#if !defined(_WRAPPER_H__F778CFA9_507C_11D1_96F1_00A024D6F582__INCLUDED_)
#define _WRAPPER_H__F778CFA9_507C_11D1_96F1_00A024D6F582__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// {F778CFA8-507C-11D1-96F1-00A024D6F582}
extern "C" const IID __declspec(selectany) IID_IEnum_DGMPoint = 
	{0xf778cfa8,0x507c,0x11d1,{0x96,0xf1,0x00,0xa0,0x24,0xd6,0xf5,0x82}};

DefineEnumerator2(W_DGMPoint, IID_IEnum_DGMPoint);		// NEnumWTRiASCSPoint
DefineSmartEnumerator2(W_DGMPoint, IID_IEnum_DGMPoint);	// WEnumWTRiASCSPoint

#endif // !defined(_WRAPPER_H__F778CFA9_507C_11D1_96F1_00A024D6F582__INCLUDED_)
