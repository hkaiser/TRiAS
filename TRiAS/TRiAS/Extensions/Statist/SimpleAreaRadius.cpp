// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
//
// @doc
// @module SimpleAreaRadius.cpp | Implementation of the <c CSimpleAreaRadius> class

#include "stdafx.h"

#include <math.h>

#include "Statist.h"
#include "SuperficialContents.h"
#include "SimpleAreaRadius.h"
#include "GeoObj.h"

/////////////////////////////////////////////////////////////////////////////
// RUNTIME_OBJECT_MAP
RT_OBJECT_ENTRYEX(SimpleAreaRadius)

/////////////////////////////////////////////////////////////////////////////
// CSimpleAreaRadius
const double PI = 3.141592653589793238;

// IObjectProperty specifics
STDMETHODIMP CSimpleAreaRadius::Reset (void)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState())
	
	RETURN_FAILED_HRESULT(m_CumPts -> Reset())
	RETURN_FAILED_HRESULT(CObjectPropertyBase::Reset());
	return S_OK;
}

STDMETHODIMP CSimpleAreaRadius::GetPropInfo (LPSTR pBuffer, WORD wLen, DWORD *pdwData)
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
STDMETHODIMP CSimpleAreaRadius::Cumulation (LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten)
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

		RETURN_FAILED_HRESULT(m_CumPts ->  get_ArithmeticAverage (&dAve));
		
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
STDMETHODIMP CSimpleAreaRadius::Eval (LONG lONr, LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState())

	if (NULL == pBuffer) 
		return E_POINTER;
	_ASSERTE(0 != ulLen);

CGObject Obj (lONr);

	if (Obj.FInit() && OGFlaeche == Obj.iObjTyp() && ulLen > 32) {		// 32 Zeichen werden zumindest gebraucht
	// nur für FlächenObjekte
	double dObjArea = 0.0;
	os_string strUnit;

		RETURN_FAILED_HRESULT(Obj.AreaOfPolygon(&dObjArea, strUnit, true));

	// muß als Längenmaßeinheit ausgewertet werden
	si::Length dRadius (sqrt(dObjArea/si::pi)/2);
	double dResult = dRadius.measuredIn(((CStatist *)g_pTE) -> GetUoL (dRadius, strUnit));

		sprintf (pBuffer, "%f%s", dResult, strUnit.c_str());
		if (pulWritten) 
			*pulWritten = strlen(pBuffer);

	// Infos für Kumulation sammeln
		RETURN_FAILED_HRESULT(m_CumPts -> AddValue (dResult, vtMissing));
		IncrementCount();			// Zähler der erfolgreichen Aufrufe
		return S_OK;
	}
	return E_FAIL;		// ObjProperty existiert nicht
}
