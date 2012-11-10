// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 24.07.2000 11:53:30
//
// @doc
// @module NodeRef.cpp | Implementation of the <c CNodeRef> class

#include "StdAfx.h"

#include "EsriCfgM.h"
#include "NodeRef.h"

///////////////////////////////////////////////////////////////////////////////
// Helperfunktionen für den Zugriff auf AST Objekte
namespace {

#if defined(_DEBUG)
// Testroutinen
	inline bool IsValidAstNodeRef (noderef *pNodeRef)
	{
		return true;
	}
	inline bool IsValidAstNodeRefRef (noderef *pNodeRef)
	{
		return true;
	}
	template<typename T>
	inline bool IsValidAstNodeRefValue (noderef *pNodeRef)
	{
		return (pNodeRef -> yy_type() == GetAstType ((T *)NULL));
	}
#endif // defined(_DEBUG)

	inline string GetNodeRefName (noderef *pNodeRef)
	{
		return string("");
	}
	inline int GetNodeRefRef (noderef *pNodeRef)
	{
		return 0;
	}

// liefert den in einem NodeRef gespeicherten Wert
	template<typename T>
	T GetNodeRefValue (noderef *pNodeRef, T *);

	template<>
	inline string GetNodeRefValue (noderef *pNodeRef, string *)
	{
		return string("");
	}
	template<>
	inline int GetNodeRefValue (noderef *pNodeRef, int *)
	{
		return 0;
	}
	template<>
	inline double GetNodeRefValue (noderef *pNodeRef, double *)
	{
		return 0.0;
	}

	template<typename T>
	inline T GetNodeRefValue (noderef *pNodeRef)
	{
		return GetNodeRefValue (pNodeRef, (T *)NULL);
	}
}

///////////////////////////////////////////////////////////////////////////////
// Hinzufügen einer Referenz zu einem Node
HRESULT CNode::AddNodeRef (noderef *pNodeRef)
{
	_ASSERTE(IsValidAstNodeRef(pNodeRef));

	COM_TRY {
	CNodeRefBase *pNodeRefBase = NULL;
	string strName (GetNodeRefName(pNodeRef));

		switch (pNodeRef -> yy_type()) {
		case yy_lex_esri_cfg_obj::T_INTEGER_:
			{
				_ASSERTE(IsValidAstNodeRefRef(pNodeRef));
				pNodeRefBase = new CNodeRef(strName.c_str(), GetNodeRefRef(pNodeRef));
			}
			break;

		case yy_lex_esri_cfg_obj::T_STRING_:
			{
				_ASSERTE(IsValidAstNodeRefValue<string>(pNodeRef));
				pNodeRefBase = new CNodeRefValue<string>(strName.c_str(), GetNodeRefValue<string>(pNodeRef));
			}
			break;

		case yy_lex_esri_cfg_obj::T_DOUBLE_:
			{
				_ASSERTE(IsValidAstNodeRefValue<double>(pNodeRef));
				pNodeRefBase = new CNodeRefValue<double>(strName.c_str(), GetNodeRefValue<double>(pNodeRef));
			}
			break;

		case yy_lex_esri_cfg_obj::T_HEXINTEGER_:
			{
				_ASSERTE(IsValidAstNodeRefValue<int>(pNodeRef));
				pNodeRefBase = new CNodeRefValue<int>(strName.c_str(), GetNodeRefValue<int>(pNodeRef));
			}
			break;
		}
	} COM_CATCH;
	return S_OK;
}

