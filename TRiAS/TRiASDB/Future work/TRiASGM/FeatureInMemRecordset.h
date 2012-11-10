///////////////////////////////////////////////////////////////////////////
// @doc 
// @module FeatureInMemRecordset.h | Tabelle der GeometrieFelder und -typen

#if !defined(_FEATUREINMEMRECORDSET_H__51311DE3_BA47_11D1_85BB_00600875138A__INCLUDED_)
#define _FEATUREINMEMRECORDSET_H__51311DE3_BA47_11D1_85BB_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <CInMemRecSet.h>
#include "Strings.h"

class CFeatureInMemRecordSet :
	public GMCInMemoryRecordset
{
private:
	HPROJECT m_hPr;

public:
	CFeatureInMemRecordSet(BSTR bstrName);
	virtual ~CFeatureInMemRecordSet();
	virtual HRESULT Initialize();		// populates metadata

// Add a GeometryFeature from database
	virtual HRESULT AddRecord (LPCSTR pcName, DWORD dwTypes, LPCSTR pcGeoFieldName = g_cbSpace, LPCSTR pcDesc = g_cbSpace);
};

#endif // !defined(_FEATUREINMEMRECORDSET_H__51311DE3_BA47_11D1_85BB_00600875138A__INCLUDED_)
