// TRiASCSPointEnum.cpp : Implementation of CTRiASCSPointEnum
#include "stdafx.h"
#include "TDBGeoImpl.h"

#include "TRiASCSPointEnum.h"
#include "coordfield.h"

// Heap für diese Klasse implementieren
//
IMPLEMENT_ONE_SIZE_PRIVATE_LOCAL_HEAP_LIST(CTRiASCSPointEnum)

/////////////////////////////////////////////////////////////////////////////
// RUNTIME_PERFINSTANCE_MAP
RT_PERFINSTANCEDATA_ENTRY(CTRiASCSPointEnum, g_cbCounts)

/////////////////////////////////////////////////////////////////////////////
// CTRiASCSPointEnum

STDMETHODIMP CTRiASCSPointEnum::Next(
	/* [in] */ ULONG celt,
	/* [length_is][size_is][out] */ VARIANT __RPC_FAR*rgVar,
	/* [out] */ ULONG __RPC_FAR*pCeltFetched)
{
	// Parameterprüfung
	if(NULL == rgVar || NULL == pCeltFetched)
		return E_POINTER;

ObjectLock l(this);
ULONG fetched = 0;
CComVariant erg;
HRESULT	hr = S_OK;

// solange noch nicht genügend Werte gelesen sind
	while (fetched < celt) {
	// gibt es so einen Eintrag überhaupt
	CSCOORD c;

		hr = m_wParent -> GetPoint(m_nIndex, & c.X);
		if (S_OK != hr)	// bei jedem kleinem Zimperlein keine weiteren Versuche
			break;

	// einen Punkt mit Zugriffsinformationen erzeugen
	CComObject<CTRiASCSPointInCol> *pPt = NULL;

		RETURN_FAILED_HRESULT(CComObject<CTRiASCSPointInCol>::CreateInstance(& pPt));
	
	W_DGMPoint wPt(pPt);

		pPt -> SetCollectionMember (m_wParent, m_nIndex);
		erg	= wPt;						// Interface in VARIANT speichern
		erg.Detach(rgVar);				// Variant in Ergebnispuffer setzen

	// fertig
		++fetched;						// ich habe also noch einen
		++rgVar;						// beim nächsten Mal hierher schreiben
		++m_nIndex;						// und den nächsten Index benutzen
	}

	if (NULL != pCeltFetched)
		*pCeltFetched = fetched;

	return hr;
}

STDMETHODIMP CTRiASCSPointEnum::Skip(
	/* [in] */ ULONG celt)
{
long colCount = 0;

ObjectLock l(this);

	RETURN_FAILED_HRESULT(m_wParent -> get_Count(& colCount))
	m_nIndex += celt;
	if (colCount <= m_nIndex)
		m_nIndex = -- colCount;

	return S_OK;
}

STDMETHODIMP CTRiASCSPointEnum::Reset(void)
{
ObjectLock l(this);

	m_nIndex = 0;
	return S_OK;
}

STDMETHODIMP CTRiASCSPointEnum::Clone(
	/* [out] */ IEnumVARIANT __RPC_FAR*__RPC_FAR*ppEnum)
{
	if(NULL == ppEnum)
		return E_POINTER;

// einen Punkt mit Zugriffsinformationen erzeugen
ObjectLock l(this);
CComObject<CTRiASCSPointEnum> *pPE  = NULL;

	RETURN_FAILED_HRESULT(CComObject<CTRiASCSPointEnum>::CreateInstance(&pPE));	// der wird weitergereicht
	pPE -> AddRef();		// pending AddRef (stabilize)

// Initialisieren
	pPE -> Init(m_wParent);

// Ergebnisse
	*ppEnum = pPE;
	return S_OK;
}
