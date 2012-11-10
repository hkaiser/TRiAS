// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
//
// @doc
// @module PointCentreCoord.cpp | Implementation of the <c CPointCentreCoord> class : 
// Bildet die Objekteigenschaft, die den Rechtswert und Hochwert der Schwerpunktkoordinate 
// eines Flächenobjektes im aktuell ausgewählten Darstellungsformat und Koordinatensystem
// liefert.

#include "stdafx.h"

#include "Statist.h"
#include "PointCentreCoord.h"
#include "GeoObj.h"

/////////////////////////////////////////////////////////////////////////////
// RUNTIME_OBJECT_MAP
RT_OBJECT_ENTRYEX(PointCentreCoordX)
RT_OBJECT_ENTRYEX(PointCentreCoordY)

/////////////////////////////////////////////////////////////////////////////
// CPointCentreCoord

// IObjectProperty specifics
STDMETHODIMP CPointCentreCoord::Reset (void)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState())
	return CObjectPropertyBase::Reset();
}

STDMETHODIMP CPointCentreCoord::GetPropInfo (LPSTR pBuffer, WORD wLen, DWORD *pdwData)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState())

// erstmal BasisKlasse arbeiten lassen	
	RETURN_FAILED_HRESULT(CObjectPropertyBase::GetPropInfo (pBuffer, wLen, pdwData));
	if (pdwData)
		*pdwData |= PROPCAPS_OBJPROPTYPE_DOUBLE;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Kumulativer Wert dieser Objekteigenschaft 
STDMETHODIMP CPointCentreCoord::Cumulation (LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState())
	if (NULL == pBuffer) return E_POINTER;

	_ASSERTE(0 != ulLen);
	_ASSERTE(!IsBadWritePtr(pBuffer, ulLen));

	if (pulWritten) 
		*pulWritten = 0;

// Mittelwert der bisher bestimmten Koordinaten als Zeichenkette liefern
	if (ulLen > 32) {
	double dAve = 0;

		RETURN_FAILED_HRESULT(m_CumPts -> get_ArithmeticAverage (&dAve));
		sprintf (pBuffer, "%f", dAve);
		if (pulWritten) 
			*pulWritten = strlen (pBuffer);
		return S_OK;
	}
	return E_NOTIMPL;
}

///////////////////////////////////////////////////////////////////////////////
// Berechnen dieser Objekteigenschaft
STDMETHODIMP CPointCentreCoord::Eval (
	LONG lONr, LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten)
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
	double dX = 0.0;
	double dY = 0.0;

		RETURN_FAILED_HRESULT(Obj.CentroidOfPolygon(&dX, &dY));
		sprintf (pBuffer, "%f", (COORDCENTRETYPE_X == m_rgType) ? dX : dY);
		if (pulWritten) 
			*pulWritten = strlen(pBuffer);

	// Infos für Kumulation sammeln
		RETURN_FAILED_HRESULT(m_CumPts -> AddValue ((COORDCENTRETYPE_X == m_rgType) ? dX : dY, vtMissing));
		IncrementCount();			// Zähler der erfolgreichen Aufrufe
		return S_OK;
	}
	return E_FAIL;		// ObjProperty existiert nicht
}

