///////////////////////////////////////////////////////////////////////////
// @doc 
// @module Wrapper.h | Description goes here

#if !defined(_WRAPPER_H__727979D3_ABAD_11D1_A066_0060975566B4__INCLUDED_)
#define _WRAPPER_H__727979D3_ABAD_11D1_A066_0060975566B4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


DefineSmartInterface2(_DGMPoint, IID__DGMPoint);
DefineSmartInterface(CTFExContext);

// {F778CFA8-507C-11D1-96F1-00A024D6F582}
extern "C" const IID __declspec(selectany) IID_IEnum_DGMPoint = 
	{0xf778cfa8,0x507c,0x11d1,{0x96,0xf1,0x00,0xa0,0x24,0xd6,0xf5,0x82}};

DefineEnumerator2(W_DGMPoint, IID_IEnum_DGMPoint);		// NEnumWTRiASCSPoint
DefineSmartEnumerator2(W_DGMPoint, IID_IEnum_DGMPoint);	// WEnumWTRiASCSPoint

#endif // !defined(_WRAPPER_H__727979D3_ABAD_11D1_A066_0060975566B4__INCLUDED_)
