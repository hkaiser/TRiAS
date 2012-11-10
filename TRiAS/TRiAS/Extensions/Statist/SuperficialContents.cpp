// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 07.12.2000 21:25:52 
//
// @doc
// @module SuperficialContents.cpp | Definition of the <c CSuperficialContents> class

#include "stdafx.h"

#include "Statist.h"
#include "SuperficialContents.h"
#include "GeoObj.h"

/////////////////////////////////////////////////////////////////////////////
// RUNTIME_OBJECT_MAP
RT_OBJECT_ENTRYEX(SuperficialContents)

/////////////////////////////////////////////////////////////////////////////
// CSuperficialContents

// IObjectProperty specifics
STDMETHODIMP CSuperficialContents::Reset (void)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState())
	
	RETURN_FAILED_HRESULT(m_CumPts -> Reset())
	RETURN_FAILED_HRESULT(CObjectPropertyBase::Reset());
	return S_OK;
}

STDMETHODIMP CSuperficialContents::GetPropInfo (LPSTR pBuffer, WORD wLen, DWORD *pdwData)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState())
	
// erstmal Basisklasse arbeiten lassen	
	RETURN_FAILED_HRESULT(CObjectPropertyBase::GetPropInfo (pBuffer, wLen, pdwData));
	if (pdwData)	
		*pdwData |= PROPCAPS_OBJPROPTYPE_DOUBLE;	
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Kumulativer Wert dieser Objekteigenschaft 
STDMETHODIMP CSuperficialContents::Cumulation (LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState())
	if (NULL == pBuffer) return E_POINTER;

	_ASSERTE(0 != ulLen);
	_ASSERTE(!IsBadWritePtr(pBuffer, ulLen));

	if (pulWritten) 
		*pulWritten = 0;

// Summe der bisher berechnten Flächeninhalteals Zeichenkette liefern
	if (ulLen > 32) {
	double dSum = 0;

		RETURN_FAILED_HRESULT(m_CumPts ->  get_Sum (&dSum));

	os_string strUnit;
	si::Area dSumArea (dSum);

		dSum = dSumArea.measuredIn(((CStatist *)g_pTE) -> GetUoA (dSumArea, strUnit));
		sprintf (pBuffer, "%f%s", dSum, strUnit.c_str());
		if (pulWritten) 
			*pulWritten = strlen (pBuffer);
		return S_OK;
	}
	return E_INVALIDARG;
}

///////////////////////////////////////////////////////////////////////////////
// Berechnen dieser Objekteigenschaft
STDMETHODIMP CSuperficialContents::Eval (LONG lONr, LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState())
	if (NULL == pBuffer) return E_POINTER;

	_ASSERTE(0 != ulLen);
	_ASSERTE(!IsBadWritePtr(pBuffer, ulLen));

	if (pulWritten) 
		*pulWritten = 0;

CGObject Obj (lONr);

	if (Obj.FInit() && OGFlaeche == Obj.iObjTyp() && ulLen > 32) {		// 32 Zeichen werden zumindest gebraucht
	// nur für FlächenObjekte
	double dObjArea = 0.0;
	os_string strUnit;

		RETURN_FAILED_HRESULT(Obj.AreaOfPolygon(&dObjArea, strUnit));
		sprintf (pBuffer, "%f%s", dObjArea, strUnit.c_str());

		if (pulWritten) 
			*pulWritten = strlen(pBuffer);

	// Infos für Kumulation sammeln
		RETURN_FAILED_HRESULT(m_CumPts -> AddValue (dObjArea, vtMissing));
		IncrementCount();			// Zähler der erfolgreichen Aufrufe
		return S_OK;
	}
	return E_FAIL;		// ObjProperty existiert nicht
}
