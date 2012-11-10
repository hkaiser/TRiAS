// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 25.06.2001 18:47:58 
//
// @doc
// @module ITableCreationImpl.h | Declaration of the <c ITableCreationImpl> class

#if !defined(_ITABLECREATIONIMPL_H__0B1AF72C_6773_41FC_8E4A_2F3456B769AF__INCLUDED_)
#define _ITABLECREATIONIMPL_H__0B1AF72C_6773_41FC_8E4A_2F3456B769AF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <Atl/OleDb/ITableDefinitionImpl.h>

///////////////////////////////////////////////////////////////////////////////
// ITableCreationImpl
template<typename T, typename Base = ITableCreation>
class ATL_NO_VTABLE ITableCreationImpl :
	public ITableDefinitionImpl<T, Base>
{
public:
	STDMETHODIMP GetTableDefinition( 
            DBID *pTableID, DBORDINAL *pcColumnDescs, DBCOLUMNDESC *prgColumnDescs[],
            ULONG *pcPropertySets, DBPROPSET *prgPropertySets[],
            ULONG *pcConstraintDescs, DBCONSTRAINTDESC *prgConstraintDescs[],
            OLECHAR **ppwszStringBuffer)
	{
		ATLTRACE2(atlTraceDBProvider, 0, "ITableCreationImpl::GetTableDefinition\n");
		return E_NOTIMPL;
	}
};

#endif // !defined(_ITABLECREATIONIMPL_H__0B1AF72C_6773_41FC_8E4A_2F3456B769AF__INCLUDED_)
