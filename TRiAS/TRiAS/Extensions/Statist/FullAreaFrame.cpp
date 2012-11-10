// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
//
// @doc
// @module FullAreaFrame.cpp | Implementation of the <c CFullAreaFrame> class

#include "stdafx.h"

#include "Statist.h"
#include "FullAreaFrame.h"
#include "GeoObj.h"

/////////////////////////////////////////////////////////////////////////////
// RUNTIME_OBJECT_MAP
RT_OBJECT_ENTRYEX(FullAreaFrame)

/////////////////////////////////////////////////////////////////////////////
// CFullAreaFrame

// IObjectProperty specifics
STDMETHODIMP CFullAreaFrame::Reset (void)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState())
	
	RETURN_FAILED_HRESULT(m_CumPts -> Reset())
	return CObjectPropertyBase::Reset();
}

STDMETHODIMP CFullAreaFrame::GetPropInfo (LPSTR pBuffer, WORD wLen, DWORD *pdwData)
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
STDMETHODIMP CFullAreaFrame::Cumulation (LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState())
	if (NULL == pBuffer) return E_POINTER;

	_ASSERTE(0 != ulLen);
	_ASSERTE(!IsBadWritePtr(pBuffer, ulLen));

	if (pulWritten) 
		*pulWritten = 0;

// Summe der bisher berechnten Polygonlängen als Zeichenkette liefern
	if (ulLen > 32) {
	double dAve = 0;

		RETURN_FAILED_HRESULT(m_CumPts ->  get_Sum (&dAve));

	os_string strUnit;
	si::Area dAveArea (dAve);

		dAve = dAveArea.measuredIn(((CStatist *)g_pTE) -> GetUoA (dAveArea, strUnit));
		sprintf (pBuffer, "%f%s", dAve, strUnit.c_str());
		if (pulWritten) 
			*pulWritten = strlen (pBuffer);
		return S_OK;
	}

	return E_INVALIDARG;
}

///////////////////////////////////////////////////////////////////////////////
// Berechnen dieser Objekteigenschaft
STDMETHODIMP CFullAreaFrame::Eval (LONG lONr, LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState())
	if (NULL == pBuffer) 
		return E_POINTER;

	_ASSERTE(0 != ulLen);
	_ASSERTE(!IsBadWritePtr(pBuffer, ulLen));

	if (pulWritten) 
		*pulWritten = 0;	// Initialisierung

CGObject Obj (lONr);

	if (Obj.FInit() && OGFlaeche == Obj.iObjTyp() && ulLen > 32) {		// 32 Zeichen werden zumindest gebraucht
	// nur für existierende FlächenObjekte
	double dObjLength = 0.0;
	os_string strUnit;

		RETURN_FAILED_HRESULT(Obj.LengthOfPolyline (&dObjLength, strUnit));
		sprintf (pBuffer, "%f%s", dObjLength, strUnit.c_str());

		if (pulWritten) 
			*pulWritten = strlen(pBuffer);

	// Infos für Kumulation sammeln
		RETURN_FAILED_HRESULT(m_CumPts -> AddValue (dObjLength, vtMissing));

		IncrementCount();			// Zähler der erfolgreichen Aufrufe
		return S_OK;
	}
	return E_FAIL;		// ObjProperty existiert nicht
}
