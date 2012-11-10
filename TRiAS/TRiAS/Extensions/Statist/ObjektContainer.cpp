// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 28.12.2000 18:26:40 
//
// @doc
// @module ObjektContainer.cpp | Definition of the <c CObjektContainer> class

#include "stdafx.h"

#include <triastlb.h>

#include "Statist.h"
#include "ConnectedCtf.h"
#include "ObjektContainer.h"
#include "GeoObj.h"

/////////////////////////////////////////////////////////////////////////////
// RUNTIME_OBJECT_MAP
RT_OBJECT_ENTRYEX(ObjContainerXMin)
RT_OBJECT_ENTRYEX(ObjContainerXMax)
RT_OBJECT_ENTRYEX(ObjContainerYMin)
RT_OBJECT_ENTRYEX(ObjContainerYMax)

/////////////////////////////////////////////////////////////////////////////
// CObjektContainer

// IObjectProperty specifics
STDMETHODIMP CObjektContainer::Reset (void)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState())
	return CObjectPropertyBase::Reset();
}

STDMETHODIMP CObjektContainer::GetPropInfo (LPSTR pBuffer, WORD wLen, DWORD *pdwData)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState())

	RETURN_FAILED_HRESULT(CObjectPropertyBase::GetPropInfo (pBuffer, wLen, pdwData));

#pragma TODO("Koordinatenformatierung über CTF-Objekt entscheidet über Datenformat (double oder string).")
	if (pdwData)		// evtl. eigene Werte ergänzen
		*pdwData |= PROPCAPS_OBJPROPTYPE_DOUBLE;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Kumulativer Wert dieser Objekteigenschaft 
STDMETHODIMP CObjektContainer::Cumulation (
	LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState())
	if (NULL == pBuffer) return E_POINTER;

	_ASSERTE(0 != ulLen);

// Mittelwert der bisher bestimmten Koordinaten als Zeichenkette liefern
	if (ulLen > 32) {
	double dAve = 0;

		if (CONTYPE_XMIN == m_rgType || CONTYPE_YMIN == m_rgType) {
			RETURN_FAILED_HRESULT(m_CumPts -> get_MinValue (&dAve));
		} else {
			RETURN_FAILED_HRESULT(m_CumPts -> get_MaxValue (&dAve));
		}

		sprintf (pBuffer, "%f", dAve);
		if (pulWritten) *pulWritten = strlen (pBuffer);
		return S_OK;
	}

	return E_NOTIMPL;
}

///////////////////////////////////////////////////////////////////////////////
// Berechnen dieser Objekteigenschaft
STDMETHODIMP CObjektContainer::Eval (
	LONG lONr, LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten)
{
	if (NULL == pBuffer) 
		return E_POINTER;

	_ASSERTE(0 != ulLen);
	_ASSERTE(!IsBadWritePtr(pBuffer, ulLen));


// nur für GeometrieObjekte
int iOTyp = DEX_GetObjectType(lONr);

	if ((OGLinie == iOTyp || OGPunkt == iOTyp || OGText == iOTyp || OGFlaeche == iOTyp || OGKreis == iOTyp)
		&& ulLen > 32) 
	{		// 32 Zeichen werden zumindest gebraucht
	CGObject Obj(lONr);

		if (!Obj.FInit())
			return E_FAIL;

	// Container berechnen
	double dXMin;
	double dXMax;
	double dYMin;
	double dYMax;

		RETURN_FAILED_HRESULT(Obj.TransformCoords(true));
		RETURN_FAILED_HRESULT(Obj.GetObjContainer(dXMin, dXMax, dYMin, dYMax));

		switch (m_rgType) {
		case CONTYPE_XMIN:
			{
				sprintf (pBuffer, "%f", dXMin);
				RETURN_FAILED_HRESULT(m_CumPts -> AddValue (dXMin, vtMissing));
			}
			break;

		case CONTYPE_XMAX:
			{
				sprintf (pBuffer, "%f", dXMax);
				RETURN_FAILED_HRESULT(m_CumPts -> AddValue (dXMax, vtMissing));
			}
			break;

		case CONTYPE_YMIN:
			{
				sprintf (pBuffer, "%f", dYMin);
				RETURN_FAILED_HRESULT(m_CumPts -> AddValue (dYMin, vtMissing));
			}
			break;

		case CONTYPE_YMAX:
			{
				sprintf (pBuffer, "%f", dYMax);
				RETURN_FAILED_HRESULT(m_CumPts -> AddValue (dYMax, vtMissing));
			}
			break;
		}

		if (pulWritten) 
			*pulWritten = strlen(pBuffer);

		IncrementCount();			// Zähler der erfolgreichen Aufrufe
		return S_OK;
	}
	return E_FAIL;		// ObjProperty existiert nicht
}

