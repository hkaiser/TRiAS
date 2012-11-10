// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
//
// @doc
// @module CountAreaIsland.cpp | Implementation of the <c CCountAreaIsland> class

#include "stdafx.h"

#include "Statist.h"
#include "CountAreaIsland.h"
#include "GeoObj.h"

/////////////////////////////////////////////////////////////////////////////
// RUNTIME_OBJECT_MAP
RT_OBJECT_ENTRYEX(CountAreaIsland)

/////////////////////////////////////////////////////////////////////////////
// CCountAreaIsland

// IObjectProperty specifics
STDMETHODIMP CCountAreaIsland::Reset (void)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState())
	
	RETURN_FAILED_HRESULT(m_CumPts -> Reset());
	RETURN_FAILED_HRESULT(CObjectPropertyBase::Reset());
	return S_OK;
}

STDMETHODIMP CCountAreaIsland::GetPropInfo (LPSTR pBuffer, WORD wLen, DWORD *pdwData)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState())

// erstmal BasisKlasse arbeiten lassen	
	RETURN_FAILED_HRESULT(CObjectPropertyBase::GetPropInfo (pBuffer, wLen, pdwData));
	if (pdwData)	// evtl. eigene Werte ergänzen
		*pdwData |= PROPCAPS_OBJPROPTYPE_INTEGER;	// Anzahl ist immer eine IntZahl
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Kumulativer Wert dieser Objekteigenschaft 
STDMETHODIMP CCountAreaIsland::Cumulation (LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState())
	if (NULL == pBuffer) return E_POINTER;

	_ASSERTE(0 != ulLen);
	_ASSERTE(!IsBadWritePtr(pBuffer, ulLen));

	if (pulWritten) 
		*pulWritten = 0;

// Mittelwert der bisher gezählten Inseln als Zeichenkette liefern
	if (ulLen > 32) {
	double dAve = 0;

		RETURN_FAILED_HRESULT(m_CumPts ->  get_ArithmeticAverage (&dAve));
		sprintf (pBuffer, "%f", dAve);
		if (pulWritten) 
			*pulWritten = strlen (pBuffer);
		return S_OK;
	}
	return E_INVALIDARG;
}

///////////////////////////////////////////////////////////////////////////////
// Berechnen dieser Objekteigenschaft
STDMETHODIMP CCountAreaIsland::Eval (LONG lONr, LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState())
	if (NULL == pBuffer) return E_POINTER;

	_ASSERTE(0 != ulLen);
	_ASSERTE(!IsBadWritePtr(pBuffer, ulLen));

	if (pulWritten) 
		*pulWritten = 0;

CGObject Obj (lONr);

	if (Obj.FInit(true) && OGFlaeche == Obj.iObjTyp() && ulLen > 20) {	// 20 Zeichen werden zumindest gebraucht
	// nur für FlächenObjekte
		ltoa (Obj.iKCnt()-1, pBuffer, 10);
		if (pulWritten) 
			*pulWritten = strlen(pBuffer);

	// Infos für Kumulation sammeln
		RETURN_FAILED_HRESULT(m_CumPts -> AddValue (double(Obj.iKCnt()-1), vtMissing));
		IncrementCount();			// Zähler der erfolgreichen Aufrufe
		return S_OK;
	}
	return E_FAIL;		// ObjProperty existiert nicht
}
