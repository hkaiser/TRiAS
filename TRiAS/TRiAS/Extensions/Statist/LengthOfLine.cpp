// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 07.12.2000 19:58:37 
//
// @doc
// @module LengthOfLine.cpp | Definition of the <c CLengthOfLine> class

#include "stdafx.h"

#include "Statist.h"
#include "LengthOfLine.h"
#include "GeoObj.h"

/////////////////////////////////////////////////////////////////////////////
// RUNTIME_OBJECT_MAP
RT_OBJECT_ENTRYEX(LengthOfLine)

///////////////////////////////////////////////////////////////////////////////
// CLengthOfLine

// IObjectProperty specifics
STDMETHODIMP CLengthOfLine::Reset (void)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState())

	RETURN_FAILED_HRESULT(m_CumPts -> Reset())
	RETURN_FAILED_HRESULT(CObjectPropertyBase::Reset());
	return S_OK;
}

STDMETHODIMP CLengthOfLine::GetPropInfo (LPSTR pBuffer, WORD wLen, DWORD *pdwData)
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
STDMETHODIMP CLengthOfLine::Cumulation (LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState())
	if (NULL == pBuffer) return E_POINTER;

	_ASSERTE(0 != ulLen);
	_ASSERTE(!IsBadWritePtr(pBuffer, ulLen));

	if (pulWritten) 
		*pulWritten = 0;

// Mittelwert der bisher gezählten Längen als Zeichenkette liefern
	if (ulLen > 32) {
	double dAve = 0;

		RETURN_FAILED_HRESULT(m_CumPts ->  get_Sum (&dAve));
		
	os_string strUnit;
	si::Length dAveLength (dAve);

		dAve = dAveLength.measuredIn(((CStatist *)g_pTE) -> GetUoL (dAveLength, strUnit));
		sprintf (pBuffer, "%f%s", dAve, strUnit.c_str());
		if (pulWritten) 
			*pulWritten = strlen (pBuffer);
		return S_OK;
	}
	return E_INVALIDARG;
}

///////////////////////////////////////////////////////////////////////////////
// Berechnen dieser Objekteigenschaft
STDMETHODIMP CLengthOfLine::Eval (LONG lONr, LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState())
	if (NULL == pBuffer) return E_POINTER;

	_ASSERTE(0 != ulLen);
	_ASSERTE(!IsBadWritePtr(pBuffer, ulLen));

	if (pulWritten) 
		*pulWritten = 0;

CGObject Obj (lONr);

	if (Obj.FInit() && OGLinie == Obj.iObjTyp() && ulLen > 20) { 		// 20 Zeichen werden zumindest gebraucht
	// nur für LinienObjekte
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
