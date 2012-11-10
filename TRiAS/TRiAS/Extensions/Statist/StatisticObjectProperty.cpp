// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 23.12.2000 22:48:53 
//
// @doc
// @module StatisticObjectProperty.cpp | Definition of the <c CStatisticObjectProperty> class

#include "stdafx.h"

#include <Com/PropertyActionBase.h>
#include <PropSeqData.h>
#include <ObjectPropertyResult.h>

#include "StatistApp.h"
#include "StatisticObjectProperty.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// {0E54C9EE-20DE-11CF-BA55-00AA0018497C}
extern "C" const IID __declspec(selectany) CLSID_PropertyActionSequence = 
	{0x0E54C9EEL,0x20DE,0x11CF,{0xBA,0x55,0x00,0xAA,0x00,0x18,0x49,0x7C}};

/////////////////////////////////////////////////////////////////////////////
// CStatisticObjectProperty

// IObjectProperty specifics
STDMETHODIMP CStatisticObjectProperty::Reset (void)
{
	RETURN_FAILED_HRESULT(m_CumPts -> Reset());
	RETURN_FAILED_HRESULT(CObjectPropertyBase::Reset());
	return S_OK;
}

STDMETHODIMP CStatisticObjectProperty::GetPropInfo (LPSTR pBuffer, WORD wLen, DWORD *pdwData)
{
// erstmal Basisklasse arbeiten lassen	
	RETURN_FAILED_HRESULT(CObjectPropertyBase::GetPropInfo (pBuffer, wLen, pdwData));
	if (pdwData)	
		*pdwData |= GetFlags();
	return S_OK;
}

STDMETHODIMP CStatisticObjectProperty::HelpInfo (
	LPSTR pBuffer, ULONG ulLen, LPSTR pHelpFile, ULONG *pulHelpCtx)
{
	RETURN_FAILED_HRESULT(CObjectPropertyBase::HelpInfo(pBuffer, ulLen, pHelpFile, pulHelpCtx));
	if (m_strDesc.GetLength() > 0 && ulLen >= m_strDesc.GetLength()) 
		strcpy (pBuffer, m_strDesc);

	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Kumulativer Wert dieser Objekteigenschaft 
STDMETHODIMP CStatisticObjectProperty::Cumulation (
	LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten)
{
	if (NULL == pBuffer) return E_POINTER;

	_ASSERTE(0 != ulLen);

	if (pulWritten) 
		*pulWritten = 0;

// kumulativer Wert
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
STDMETHODIMP CStatisticObjectProperty::Eval (
	LONG lONr, LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten)
{
	if (NULL == pBuffer) return E_POINTER;

	_ASSERTE(0 != ulLen);

// Bezugsobjekt im Kontext ablegen
WDataObject DO;

	RETURN_FAILED_HRESULT(m_Seq -> GetSequenceContext (DO.ppi()));
	RETURN_FAILED_HRESULT(PropActBase::SetVariantData(CComVariant(lONr, VT_I4), 
		DO, &c_feObjPropTarget));

// Objekteigenschaft berechnen
	if (FAILED(m_Seq -> RedoActions(m_hWndParent, NULL, NULL, NULL)))
		return E_FAIL;

// Objekteigenschaft liefern
CComVariant vResult;

	if (FAILED(PropActBase::GetVariantData(DO, &c_feObjPropResult, &vResult)))
		return E_FAIL;

	switch (V_VT(&vResult)) {
	case VT_I4:
		sprintf (pBuffer, "%d", V_I4(&vResult));
		break;

	case VT_R8:
		sprintf (pBuffer, "%f", V_R8(&vResult));
		break;

	default:
		return E_FAIL;		// Objekteigenschaft nicht berechenbar
	}

	if (pulWritten) 
		*pulWritten = strlen(pBuffer);

// Infos für Kumulation sammeln
	RETURN_FAILED_HRESULT(vResult.ChangeType(VT_R8));
	RETURN_FAILED_HRESULT(m_CumPts -> AddValue (V_R8(&vResult), vtMissing));
	IncrementCount();			// Zähler der erfolgreichen Aufrufe
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersist
STDMETHODIMP CStatisticObjectProperty::GetClassID (CLSID *pClsID)
{
	*pClsID = GetObjectCLSID();
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistStreamInit
STDMETHODIMP CStatisticObjectProperty::Load (IStream *pStm)
{
	if (GetInitialized())
		return E_UNEXPECTED;

	RETURN_FAILED_HRESULT(CObjectPropertyBase::Load (pStm));
	RETURN_FAILED_HRESULT(OleLoadFromStream (pStm, m_Seq.GetIID(), m_Seq.ppv()));

	SetInitialized();
	return S_OK;
}

STDMETHODIMP CStatisticObjectProperty::Save (IStream *pStm, BOOL fClearDirty)
{
	COM_TRY {
		THROW_FAILED_HRESULT(CObjectPropertyBase::Save (pStm, fClearDirty));
		THROW_FAILED_HRESULT(OleSaveToStream (WPersistStream(m_Seq), pStm));

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CStatisticObjectProperty::GetSizeMax (ULARGE_INTEGER *pcbSize)
{
	if (NULL == pcbSize)
		return E_POINTER;
	pcbSize -> QuadPart = 0L;

	COM_TRY {
		THROW_FAILED_HRESULT(CObjectPropertyBase::GetSizeMax (pcbSize));

	ULARGE_INTEGER uli;

		THROW_FAILED_HRESULT(WPersistStreamInit(m_Seq) -> GetSizeMax (&uli));
		pcbSize -> QuadPart += uli.QuadPart;

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CStatisticObjectProperty::InitNew()
{
	if (GetInitialized())
		return E_UNEXPECTED;

	COM_TRY {
	WPropertyActionSequence Seq (CLSID_PropertyActionSequence);

		THROW_FAILED_HRESULT(WPersistStreamInit(Seq) -> InitNew());
		THROW_FAILED_HRESULT(Seq -> SetDescription (GetName()));
		m_Seq = Seq;

	} COM_CATCH;

	SetInitialized();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// IPropertyInfo
STDMETHODIMP CStatisticObjectProperty::SetPropInfo (LPCSTR pBuffer, DWORD dwFlags)
{
// Neuen Namen und neue Flags setzen
	SetName(pBuffer);
	SetFlags(dwFlags);

	_ASSERTE(m_Seq.IsValid());
	RETURN_FAILED_HRESULT(m_Seq -> SetDescription (GetName()));	// Sequence heißt genauso
	return S_OK;
}

STDMETHODIMP CStatisticObjectProperty::SetHelpInfo (LPCSTR pBuffer, LPCSTR pHelpFile, ULONG ulHelpCtx)
{
	if (NULL != pBuffer)
		m_strDesc = pBuffer;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// IConfigObjectProperty
STDMETHODIMP CStatisticObjectProperty::ConfigObjectProperty (HWND hWndParent)
{
	_ASSERT(m_Seq.IsValid());
	m_fIsConfigured = false;

HRESULT hr = PrepareActions (hWndParent, NULL);

	if (SUCCEEDED(hr))
		m_fIsConfigured = true;
	return hr;
}

STDMETHODIMP CStatisticObjectProperty::get_IsConfigured (VARIANT_BOOL *pfConfigState)
{
	if (NULL == pfConfigState)
		return E_POINTER;
	*pfConfigState = m_fIsConfigured ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// IConfigSequenceForObjectProperty
STDMETHODIMP CStatisticObjectProperty::AddAction (IUnknown *pIAct)
{
	if (NULL == pIAct)
		return E_POINTER;

WPropertyAction Prop;

	if (pIAct -> QueryInterface (Prop.ppi())) {
		RETURN_FAILED_HRESULT(m_Seq -> AddAction (Prop));
		return S_OK;
	}
	return E_INVALIDARG;
}

STDMETHODIMP CStatisticObjectProperty::AddActionsByCLSID (CALPCLSID *pcaClsIds)
{
	if (NULL == pcaClsIds)
		return E_POINTER;

	RETURN_FAILED_HRESULT(m_Seq -> AddActionsByCLSID (pcaClsIds));
	return S_OK;
}

namespace {
	class CAddOffsetPosition
	{
	public:
		CAddOffsetPosition(HWND hWnd) : m_hWnd(hWnd)
		{
		int iOffset = 2*GetSystemMetrics(SM_CYCAPTION);
		
			SetProp (hWnd, "OffsetPositionX", reinterpret_cast<HANDLE>(iOffset));	
			SetProp (hWnd, "OffsetPositionY", reinterpret_cast<HANDLE>(iOffset));	
		}
		~CAddOffsetPosition()
		{
			RemoveProp (m_hWnd, "OffsetPositionX");
			RemoveProp (m_hWnd, "OffsetPositionY");
		}

	private:
		HWND m_hWnd;
	};
}

STDMETHODIMP CStatisticObjectProperty::PrepareActions (HWND hWndParent, IDataObject *pIData)
{
// jetzt noch unsere Seite anhängen
	COM_TRY {
		if (!m_fHasAddedPage) {
		WPropertyAction Prop;

			THROW_FAILED_HRESULT(Prop.LocalCreateInstance (CLSID_SelectStatistValue));
			THROW_FAILED_HRESULT(m_Seq -> AddAction (Prop));
			m_fHasAddedPage = true;
		}
	
	// Parent-Fenster im Kontext speichern
	WDataObject DO;

		m_hWndParent = hWndParent;
		THROW_FAILED_HRESULT(m_Seq -> GetSequenceContext (DO.ppi()));
		PropActBase::SetHWND (hWndParent, DO, &c_feMainWindow);

	CAddOffsetPosition AddOffset(hWndParent);
	HRESULT hr = m_Seq -> PrepareActions (hWndParent, pIData);

		if (FAILED(hr))
			return hr;

	} COM_CATCH;
	SetInitialized (true);
	return S_OK;
}

