// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 25.02.2000 12:19:53
//
// @doc
// @module DBObjects.cpp | Implementation of the <c CDBObjects> class

#include "StdAfx.h"
#include "resource.h"

#include <Atl/VariantStream.h>
#include <Com/MemoryHelper.h>

///////////////////////////////////////////////////////////////////////////////
// Tabellen registrieren
REGISTER_UNASSIGNED2(CDBHeader, "HEADER");
REGISTER_UNASSIGNED2(CDBObject, "OBJECTS");
REGISTER_UNASSIGNED2(CDBClass, "CLASSES");
REGISTER_UNASSIGNED2(CDBFeatureDesc, "FEATUREDESCS");
REGISTER_UNASSIGNED2(CDBFeature, "FEATURES");

///////////////////////////////////////////////////////////////////////////////
// 
void CDBDatabase::handleError (dbErrorClass error, char const* msg, int arg)
{
char buf[256];

    switch (error) { 
	case QueryError:
		wsprintf(buf, "%s in position %d\n", msg, arg);
		return;
	
	case ArithmeticError:
		wsprintf(buf, "%s\n", msg);
		break;
	
	case IndexOutOfRangeError:
		wsprintf(buf, "Index %d is out of range\n", arg);
		break;
	
	case DatabaseOpenError:
		wsprintf(buf, "%s\n", msg);
		return;
	
	case FileError:
		wsprintf(buf, "%s: %s\n", msg, dbFile::errorText(arg, buf, sizeof(buf)));
		break;
	
	case OutOfMemoryError:
		wsprintf(buf, "Not enough memory: failed to allocate %d bytes\n", arg);
		break;
	
	case NullReferenceError:
		wsprintf(buf, "Null object reference is accessed\n");
		break;
	
	case Deadlock:
		wsprintf(buf, "Deadlock is caused by upgrading shared locks to exclusive");
		break;
	
	default:
		return;
	}

CString strText;

	VERIFY(strText.LoadString (IDS_FASTDBERRORCAP));
	AfxGetMainWnd() -> MessageBox (strText, buf, MB_ICONEXCLAMATION|MB_TASKMODAL);
}

///////////////////////////////////////////////////////////////////////////////
// Zugriffsroutinen für Hdr
DefineSmartInterface(Stream);

HRESULT CDBHeader::SetValue (VARIANT Val)
{
	COM_TRY {
	WStream Strm;

		THROW_FAILED_HRESULT(CreateStreamOnHGlobal (NULL, TRUE, Strm.ppi()));
		THROW_FAILED_HRESULT(WriteVariantToStream (&Val, Strm));

	HGLOBAL hGbl = NULL;

		THROW_FAILED_HRESULT(::GetHGlobalFromStream (Strm, &hGbl));
		{
		CGlobalMem::Lock<byte> MemLock (hGbl); 

			if (!MemLock) _com_issue_error(E_OUTOFMEMORY);
			m_Data.assign(MemLock, MemLock.GetSize());
		}

	} COM_CATCH;
	return S_OK;
}

HRESULT CDBHeader::GetValue (VARIANT *pVal)
{
	COM_TRY {
	CComVariant v;
	WStream Strm;
	CGlobalMem Mem (sizeof(byte)*m_Data.length());
	
		{
		CGlobalMem::Lock<byte> lock (Mem);

			memcpy (lock, m_Data.base(), sizeof(byte)*m_Data.length());
		}
		THROW_FAILED_HRESULT(CreateStreamOnHGlobal (Mem.Handle(), FALSE, Strm.ppi()));
		THROW_FAILED_HRESULT(ReadVariantFromStream (Strm, v));
		THROW_FAILED_HRESULT(v.Detach (pVal));

	} COM_CATCH;
	return S_OK;
}

