///////////////////////////////////////////////////////////////////////////
// @doc 
// @module OKSInMemRecordSet.h | ObjektklassenTabelle

#if !defined(_OKSINMEMRECORDSET_H__AFB3ED83_B77E_11D1_85B3_00600875138A__INCLUDED_)
#define _OKSINMEMRECORDSET_H__AFB3ED83_B77E_11D1_85B3_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <CInMemRecSet.h>

class COKSInMemRecordSet :
	public GMCInMemoryRecordset
{
private:
	HPROJECT m_hPr;
	int m_iIdBase;

protected:
	os_string RetrieveObjectTypes (DWORD dwTypes);

public:
	COKSInMemRecordSet(HPROJECT hPr, BSTR bstrName);
	virtual ~COKSInMemRecordSet();
	virtual HRESULT Initialize();		// populates metadata

// Add a OKS from database
	virtual HRESULT AddRecord (long lIdent, DWORD dwTypes, LPCSTR pcName, LPCSTR pcDesc);
};

#endif // !defined(_OKSINMEMRECORDSET_H__AFB3ED83_B77E_11D1_85B3_00600875138A__INCLUDED_)
