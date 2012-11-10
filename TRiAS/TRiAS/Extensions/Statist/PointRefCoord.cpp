// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 07.12.2000 21:39:14 
//
// @doc
// @module PointRefCoord.cpp | Definition of the <c CPointRefCoord> class

#include "stdafx.h"

#include "Statist.h"
#include "PointRefCoord.h"
#include "GeoObj.h"

/////////////////////////////////////////////////////////////////////////////
// RUNTIME_OBJECT_MAP
RT_OBJECT_ENTRY(CLSID_PointCoordX, CPointRefCoordX)
RT_OBJECT_ENTRY(CLSID_PointCoordY, CPointRefCoordY)

/////////////////////////////////////////////////////////////////////////////
// CPointRefCoord

// IObjectProperty sepcifics
STDMETHODIMP CPointRefCoord::Reset (void)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState())
	return CObjectPropertyBase::Reset();
}

STDMETHODIMP CPointRefCoord::GetPropInfo (LPSTR pBuffer, WORD wLen, DWORD *pdwData)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState())

// erstmal BasisKlasse arbeiten lassen	
	RETURN_FAILED_HRESULT(CObjectPropertyBase::GetPropInfo (pBuffer, wLen, pdwData));

	if (pdwData)		// evtl. eigene Werte ergänzen
		*pdwData |= PROPCAPS_OBJPROPTYPE_DOUBLE;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Kumulativer Wert dieser Objekteigenschaft liefert die Summe aller bisher 
// 'gezählten' Stützpunkte
STDMETHODIMP CPointRefCoord::Cumulation (LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten)
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
STDMETHODIMP CPointRefCoord::Eval (LONG lONr, LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState())
	if (NULL == pBuffer) return E_POINTER;

	_ASSERTE(0 != ulLen);
	_ASSERTE(!IsBadWritePtr(pBuffer, ulLen));

	if (pulWritten) 
		*pulWritten = 0;

CGObject Obj (lONr);

	if (Obj.FInit() && ulLen > 32) {		// 32 Zeichen werden zumindest gebraucht
	// nur für GeometrieObjekte
	double dX = 0.0;
	double dY = 0.0;

		switch (Obj.iObjTyp()) {
		case OGFlaeche:
		// bei Flächen Außnahmeregelung
			RETURN_FAILED_HRESULT(Obj.InitRealAreaPoint (&dX, &dY));
			break;

		case OGLinie:
			{
			long lCentre = Obj.lCnt()/2 -1;

				if (0 == lCentre)
					++lCentre;

				dX = *(Obj.X() + lCentre);
				dY = *(Obj.Y() + lCentre);
			}
			break;

		case OGPunkt:
		case OGText:
			dX = *Obj.X();
			dY = *Obj.Y();
			break;

		default:
			return E_UNEXPECTED;
		}
		sprintf (pBuffer, "%f", (COORDTYPE_X == m_rgType) ? dX : dY);
		if (pulWritten) 
			*pulWritten = strlen(pBuffer);

	// Infos für Kumulation sammeln
		RETURN_FAILED_HRESULT(m_CumPts -> AddValue ((COORDTYPE_X == m_rgType) ? dX : dY, vtMissing));
		IncrementCount();			// Zähler der erfolgreichen Aufrufe
		return S_OK;
	}
	return E_FAIL;		// ObjProperty existiert nicht
}

