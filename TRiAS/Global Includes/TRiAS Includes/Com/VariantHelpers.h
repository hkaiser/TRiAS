// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 10/19/1998 01:33:31 PM
//
// @doc
// @module VariantHelpers.h | Zusätzliche VARIANT-Macros

#if !defined(_VARIANTHELPERS_H__7CD5571B_6427_11D2_9EDE_006008447800__INCLUDED_)
#define _VARIANTHELPERS_H__7CD5571B_6427_11D2_9EDE_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define	__VCHECK(V,VT)	((VT)==(V_VT(V)&VT_TYPEMASK))

//#define	V_IS (V)		__VCHECK(V,VT_)
///////////////////////////////////////////////////////////////////////////////
// allgemeine Inhalte
#define	V_ISEMPTY(V)	__VCHECK(V,VT_EMPTY)
#define	V_ISERROR(V)	__VCHECK(V,VT_ERROR)
#define	V_ISNULL(V)		__VCHECK(V,VT_NULL)

///////////////////////////////////////////////////////////////////////////////
// Integer / Unsigned Integer
#define	V_ISINT(V)		__VCHECK(V,VT_INT)
#define	V_ISI2(V)		__VCHECK(V,VT_I2)
#define	V_ISI4(V)		__VCHECK(V,VT_I4)
#define	V_ISI8(V)		__VCHECK(V,VT_I8)

#define	V_ISUINT(V)		__VCHECK(V,VT_UINT)
#define	V_ISUI1(V)		__VCHECK(V,VT_UI1)
#define	V_ISUI2(V)		__VCHECK(V,VT_UI2)
#define	V_ISUI4(V)		__VCHECK(V,VT_UI4)
#define	V_ISUI8(V)		__VCHECK(V,VT_UI8)

#define	V_ISINTEGER(V)	(__VCHECK(V,VT_INT)||__VCHECK(V,VT_I2)||__VCHECK(V,VT_I4))
#define	V_ISUINTEGER(V)	(__VCHECK(V,VT_UINT)||__VCHECK(V,VT_UI1)||__VCHECK(V,VT_UI2)||__VCHECK(V,VT_UI4))

///////////////////////////////////////////////////////////////////////////////
// Gleitkomma
#define	V_ISR4(V)		__VCHECK(V,VT_R4)
#define	V_ISR8(V)		__VCHECK(V,VT_R8)
#define	V_ISREAL(V)		(__VCHECK(V,VT_R4)||__VCHECK(V,VT_R8))

///////////////////////////////////////////////////////////////////////////////
// IUnknown, IDispatch
#define	V_ISUNKNOWN(V)	__VCHECK(V,VT_UNKNOWN)
#define	V_ISDISPATCH(V)	__VCHECK(V,VT_DISPATCH)

///////////////////////////////////////////////////////////////////////////////
// viele Daten
#define	V_ISBSTR(V)		__VCHECK(V,VT_BSTR)
#define	V_ISSAFEARRAY(V)	__VCHECK(V,VT_SAFEARRAY)
#define	V_ISBLOB(V)		__VCHECK(V,VT_BLOB)
#define	V_ISSTORAGE(V)	__VCHECK(V,VT_STORAGE)
#define	V_ISSTREAMED_OBJECT(V)	__VCHECK(V,VT_STREAMED_OBJECT)
#define	V_ISSTORED_OBJECT(V)	__VCHECK(V,VT_STORED_OBJECT)
#define	V_ISBLOB_OBJECT(V)		__VCHECK(V,VT_BLOB_OBJECT)

///////////////////////////////////////////////////////////////////////////////
// Rückkehrwerte
#define	V_ISBOOL(V)		__VCHECK(V,VT_BOOL)
#define	V_ISHRESULT(V)	__VCHECK(V,VT_HRESULT)

///////////////////////////////////////////////////////////////////////////////
// Makros für PROPVARIANT-Datentypen
#define V_BLOB(X)				V_UNION(X, blob)
#define V_BLOB_OBJECT(X)		V_UNION(X, blob)
#define V_STREAM(X)				V_UNION(X, pStream)
#define V_STREAMED_OBJECT(X)	V_UNION(X, pStream)

//////////////////////////////////////////////////////////////////////
// bei get_ ...( VARIANT* ) muß alter Inhalt von CComVariant vor dem Aufruf
// freigegeben werden (sonst wird's irgendwann knapp mit dem Speicher...,
// oder es bleiben Zeiger hängen usw.)
//
//          CComVariant    vFooValue;
//           ....
//          HRESULT hr = IFooObject->get_FooValue( CLEARED(vFooValue) );

inline VARIANT* CLEARED(CComVariant& v) 
{
	if( !V_ISEMPTY(&v) )
		v.Clear();
	return &v;
}

#endif // !defined(_VARIANTHELPERS_H__7CD5571B_6427_11D2_9EDE_006008447800__INCLUDED_)
