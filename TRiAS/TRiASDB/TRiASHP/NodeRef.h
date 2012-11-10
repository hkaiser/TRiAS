// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 24.07.2000 11:50:28 
//
// @doc
// @module NodeRef.h | Declaration of the <c CNodeRef> et.al. classes

#if !defined(_NODEREF_H__9F8D7CC9_8C04_4C31_9E60_CF604C8E2680__INCLUDED_)
#define _NODEREF_H__9F8D7CC9_8C04_4C31_9E60_CF604C8E2680__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <ospace/stlex/pointainer.h>

///////////////////////////////////////////////////////////////////////////////
// Lexer 
#include "EsriCfgY.h"
#include "EsriCfgL.h"

///////////////////////////////////////////////////////////////////////////////
// Eine NodeReferenz speichert einen Name und einen zugehörigen Wert,
// der seinerseits eine zeichenkette ein Zahlenwert oder ein Verweis auf einen
// anderen Node sein kann
class CNodeRefBase
{
public:
	CNodeRefBase (LPCSTR pcRefName) : m_strName(pcRefName) {}
	virtual ~CNodeRefBase() {}

// access methods
	LPCSTR GetName() { return m_strName.c_str(); }

private:
	string m_strName;
};

// Verweis auf einen anderen Node
class CNodeRef :
	public CNodeRefBase
{
public:
	CNodeRef (LPCSTR pcRefName, int iNum) : CNodeRefBase(pcRefName), m_iRefNum(iNum) {}
	~CNodeRef() {}

// access methods
	int GetNodeNum() const { return m_iRefNum; }

private:
	int m_iRefNum;
};

// Zahlenwert (double, Hexzahl, Binärzahl und Zeichenkette)
template<typename T> inline int GetAstType(T *);
template<> inline int GetAstType (int *) { return yy_lex_esri_cfg_obj::T_HEXINTEGER_; }
template<> inline int GetAstType (string *) { return yy_lex_esri_cfg_obj::T_STRING_; }
template<> inline int GetAstType (double *) { return yy_lex_esri_cfg_obj::T_DOUBLE_; }

template<typename T>
class CNodeRefValue :
	public CNodeRefBase
{
public:
	CNodeRefValue (LPCSTR pcRefName, T const & rValue) : 
		CNodeRefBase(pcRefName), m_Value(rValue), m_rgType(GetAstType((T *)NULL))
	{
	}
	~CNodeRefValue() 
	{
	}

// access methods
	T GetValue() const { return m_Value; }
	int GetType() { return m_rgType; }

private:
	T m_Value;
	int m_rgType;
};

///////////////////////////////////////////////////////////////////////////////
// Ein Node, der eine Liste von NodeRefs speichert
class CNode 
{
public:
	typedef pointainer<list<CNodeRefBase *> > CNodeRefs;

	CNode (LPCSTR pcName, int iNum) : m_strName(pcName), m_iNum(iNum) {}
	~CNode() {}

// operations
	HRESULT AddNodeRef (class noderef *pNodeRef);

// access methods
	LPCSTR GetName() { return m_strName.c_str(); }

private:
	string m_strName;
	int m_iNum;
	CNodeRefs m_NodeRefs;	// die Liste der enthaltenen NodeRefs
};

#endif // !defined(_NODEREF_H__9F8D7CC9_8C04_4C31_9E60_CF604C8E2680__INCLUDED_)
