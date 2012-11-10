// @doc 
// @module CountLinePoints.cpp | Implementation of the <c CCountLinePoints> class

#include "stdafx.h"

#include "Statist.h"
#include "CountLinePoints.h"
#include "GeoObj.h"

/////////////////////////////////////////////////////////////////////////////
// RUNTIME_OBJECT_MAP
RT_OBJECT_ENTRYEX(CountLinePoints)

/////////////////////////////////////////////////////////////////////////////
// CCountLinePoints

// IObjectProperty sepcifics
STDMETHODIMP CCountLinePoints::Reset (void)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState())
	
	RETURN_FAILED_HRESULT(m_CumPts -> Reset());
	RETURN_FAILED_HRESULT(CObjectPropertyBase::Reset());
	return S_OK;
}

STDMETHODIMP CCountLinePoints::GetPropInfo (LPSTR pBuffer, WORD wLen, DWORD *pdwData)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState())

// erstmal BasisKlasse arbeiten lassen	
	RETURN_FAILED_HRESULT(CObjectPropertyBase::GetPropInfo (pBuffer, wLen, pdwData));

	if (pdwData)	// evtl. eigene Werte ergänzen
		*pdwData |= PROPCAPS_OBJPROPTYPE_INTEGER;	// Stützpunktanzahl ist immer eine IntZahl
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Kumulativer Wert dieser Objekteigenschaft liefert die Summe aller bisher 
// 'gezählten' Stützpunkte
STDMETHODIMP CCountLinePoints::Cumulation (LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState())
	if (NULL == pBuffer) return E_POINTER;

	_ASSERTE(0 != ulLen);
	_ASSERTE(!IsBadWritePtr(pBuffer, ulLen));

	if (pulWritten) 
		*pulWritten = 0;

// Summe der bisher gezählten Stützpunkte als Zeichenkette liefern
	if (ulLen > 32) {
	double dAve = 0;

		RETURN_FAILED_HRESULT(m_CumPts ->  get_Sum (&dAve));
		sprintf (pBuffer, "%f", dAve);
		if (pulWritten) 
			*pulWritten = strlen (pBuffer);
		return S_OK;
	}
	return E_INVALIDARG;
}

///////////////////////////////////////////////////////////////////////////////
// Berechnen dieser Objekteigenschaft
STDMETHODIMP CCountLinePoints::Eval (LONG lONr, LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState())
	if (NULL == pBuffer) return E_POINTER;

	_ASSERTE(0 != ulLen);
	_ASSERTE(!IsBadWritePtr(pBuffer, ulLen));

int iOTyp = DEX_GetObjectType(lONr);

	if (((OGLinie == iOTyp) ||
		(OGPunkt == iOTyp) ||
		(OGFlaeche == iOTyp) ||
		(OGKreis == iOTyp) )
		&& ulLen > 20) {		// 20 Zeichen werden zumindest gebraucht
	// nur für GeometrieObjekte
	OBJSTATISTIK OG;

		INITSTRUCT(OG, OBJSTATISTIK);
		OG.lONr = lONr;
		if (!DEX_GetObjStatistik(OG))
			return E_FAIL;		// irgend was ist faul

		ltoa (OG.lCnt, pBuffer, 10);
		if (pulWritten) 
			*pulWritten = strlen(pBuffer);

	// Infos für Kumulation sammeln
		RETURN_FAILED_HRESULT(m_CumPts -> AddValue (double(OG.lCnt), vtMissing));
		IncrementCount();			// Zähler der erfolgreichen Aufrufe
		return S_OK;
	}
	return E_FAIL;		// ObjeProperty existiert nicht
}
