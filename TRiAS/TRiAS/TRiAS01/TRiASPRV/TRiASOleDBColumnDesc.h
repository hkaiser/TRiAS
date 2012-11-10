// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 13.07.2001 17:10:54 
//
// @doc
// @module TRiASOleDBColumnDesc.h | Declaration of the <c CTRiASOleDBColumnDesc> class

#if !defined(_TRIASOLEDBCOLUMNDESC_H__29D78939_AD93_4E89_8956_A9E94AECFF25__INCLUDED_)
#define _TRIASOLEDBCOLUMNDESC_H__29D78939_AD93_4E89_8956_A9E94AECFF25__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// Spaltenbeschreibung für neue Objekteigenschaft
class CObjectPropertyColumnDesc :
	public DBCOLUMNDESC
{
public:
	CObjectPropertyColumnDesc(LPCOLESTR pcoleName)
	{
		memset(this, '\0', sizeof(DBCOLUMNDESC));
		pwszTypeName = OLESTR("ObjectProperty");
		ulColumnSize = LONG_MAX;
		wType = DBTYPE_WSTR;

	CDBID ColId (pcoleName);

		CDBIDOps::CopyDBIDs(&dbcid, &ColId);
	}
	~CObjectPropertyColumnDesc()
	{
		CDBIDOps::FreeDBIDs(&dbcid);
	}
};

#endif // !defined(_TRIASOLEDBCOLUMNDESC_H__29D78939_AD93_4E89_8956_A9E94AECFF25__INCLUDED_)
