// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 10/19/1998 05:47:08 PM
//
// @doc
// @module CStructHelper.h | Helperklassen/Makros für die Verwaltung von C-Strukturen

#if !defined(_CSTRUCTHELPER_H__7CD5571D_6427_11D2_9EDE_006008447800__INCLUDED_)
#define _CSTRUCTHELPER_H__7CD5571D_6427_11D2_9EDE_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

///////////////////////////////////////////////////////////////////////////////
// 
template<class T>
class CStruct : 
	public T
{
public:
	CStruct() { Init(); }
	~CStruct() { Tidy(); }

	T * operator& () { Tidy(); return this; }
	void Detach (T *pDest)
	{
		memcpy (pDest, this, sizeof(T));
		Init();
	}

protected:
	void Init() { memset (this, '\0', sizeof(T)); }
	void Tidy() { Clear (this); }
};
#define TIDY(x,y)	if (NULL == x->y) {} else { CoTaskMemFree(x->y); x->y = NULL; }

///////////////////////////////////////////////////////////////////////////////
//
template<class T>
class CStructEx :
	public CStruct<T>
{
public:
	CStructEx() { InitEx(); }
	~CStructEx() {}

protected:
	void InitEx() { dwSize = sizeof(T); }
};

#endif // !defined(_CSTRUCTHELPER_H__7CD5571D_6427_11D2_9EDE_006008447800__INCLUDED_)
