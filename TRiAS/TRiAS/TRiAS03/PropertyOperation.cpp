// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 06.10.2000 15:48:46
//
// @doc
// @module PropertyOperation.cpp | Implementation of the <c CPropertyOperation> class

#include "trias03p.hxx"
#include "trias03.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include <TrCatIds.h>

#include "Strings.h"
#include "PropertyOperation.h"

/////////////////////////////////////////////////////////////////////////////
// CPropertyOperation

// IPropertyAction 

STDMETHODIMP CPropertyOperation::BeginAction (IProgressIndicator *pIProgInd)
{
	RETURN_FAILED_HRESULT(CPropertyActionImpl::BeginAction (pIProgInd));
	m_Objects.clear();
	return S_OK;
}

STDMETHODIMP CPropertyOperation::DoAction (IDataObject *pIDataObj, DWORD dwReserved)
{
// Eingabeobjekte einfach mit zu unserer Objektmenge hinzufügen
	COM_TRY {
	long lPacket = 0;

		PropActBase::GetPacketNumber(pIDataObj, &lPacket);		// kein Fehler, default PacketNumber 0

	CMapOfPackets::iterator it = m_Objects.find(lPacket);

		if (it == m_Objects.end()) {
		pair<CMapOfPackets::iterator, bool> p = m_Objects.insert (CMapOfPackets::value_type(lPacket, SEnumLONG()));

			it = p.first;
			_ASSERTE(it != m_Objects.end());
		}
		
	WEnumLONG EnumObjs;
	OutEnumLONG iter_out_if (&(*it).second);	// zu den anderen Objekten dieser Geo-Komponenten-Quelle

		THROW_FAILED_HRESULT(PropActBase::GetEnumObjects (pIDataObj, __uuidof(IEnumLONG), EnumObjs.ppv()));
		copy (InEnumLONG(EnumObjs), InEnumLONG(), iter_out_if);

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CPropertyOperation::EndAction (DWORD, IDataObject **ppDataObj)
{
	COM_TRY {
	// ProgressIndikator initialisieren
//		SetMaxTicks (m_Objects.size());

	// eigentliche Verarbeitung
	WEnumLONG EnumOut (CLSID_EnumObjectsByNumber);				// Ausgabeobjektmenge

		{
		OutEnumLONG iter_out (static_cast<IEnum<LONG> *>(EnumOut));

			_ASSERTE(2 == m_Objects.size());		// derzeit genau Eingänge
			switch (m_rgOperation) {
			case PROPERTYOPERATION_A_Or_B:
				THROW_FAILED_HRESULT(A_Or_B(iter_out));
				break;

			case PROPERTYOPERATION_A_And_B:
				THROW_FAILED_HRESULT(A_And_B(iter_out));
				break;

			case PROPERTYOPERATION_NotA_And_B:
				THROW_FAILED_HRESULT(NotA_And_B(iter_out));
				break;

			case PROPERTYOPERATION_A_And_NotB:
				THROW_FAILED_HRESULT(A_And_NotB(iter_out));
				break;

			case PROPERTYOPERATION_A_Xor_B:
				THROW_FAILED_HRESULT(A_Xor_B(iter_out));
				break;

			default:
				_ASSERTE(PROPERTYOPERATION_Unknown != m_rgOperation);
				break;
			}
		} // iter_out goes out of scope

	// Ausgabeobjektmenge in Transfer-Objekt setzen
	__Interface<IDataObject> DO (CLSID_DataTransferObject);

		THROW_FAILED_HRESULT(PropActBase::SetEnumObjects (EnumOut, DO));
		*ppDataObj = DO.detach();

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Vereinigungsmenge bilden
HRESULT CPropertyOperation::A_Or_B (OutEnumLONG &rIterOut)
{
	COM_TRY {
	CMapOfPackets::iterator it1st = m_Objects.find(0);
	CMapOfPackets::iterator it2nd = m_Objects.find(1);

		_ASSERTE(it1st != m_Objects.end() && it2nd != m_Objects.end());
		set_union(InEnumLONG(&(*it1st).second), InEnumLONG(), InEnumLONG(&(*it2nd).second), InEnumLONG(), rIterOut);

	} COM_CATCH;
	return S_OK;
}

// Schnittmenge bilden
HRESULT CPropertyOperation::A_And_B (OutEnumLONG &rIterOut)
{
	COM_TRY {
	CMapOfPackets::iterator it1st = m_Objects.find(0);
	CMapOfPackets::iterator it2nd = m_Objects.find(1);

		_ASSERTE(it1st != m_Objects.end() && it2nd != m_Objects.end());
		set_intersection(InEnumLONG(&(*it1st).second), InEnumLONG(), InEnumLONG(&(*it2nd).second), InEnumLONG(), rIterOut);

	} COM_CATCH;
	return S_OK;
}

// Komplementärmenge aus A zu B bilden
HRESULT CPropertyOperation::NotA_And_B (OutEnumLONG &rIterOut)
{
	COM_TRY {
	CMapOfPackets::iterator it1st = m_Objects.find(0);
	CMapOfPackets::iterator it2nd = m_Objects.find(1);

		_ASSERTE(it1st != m_Objects.end() && it2nd != m_Objects.end());
		set_difference(InEnumLONG(&(*it2nd).second), InEnumLONG(), InEnumLONG(&(*it1st).second), InEnumLONG(), rIterOut);

	} COM_CATCH;
	return S_OK;
}

// Komplementärmenge aus B zu A bilden
HRESULT CPropertyOperation::A_And_NotB (OutEnumLONG &rIterOut)
{
	COM_TRY {
	CMapOfPackets::iterator it1st = m_Objects.find(0);
	CMapOfPackets::iterator it2nd = m_Objects.find(1);

		_ASSERTE(it1st != m_Objects.end() && it2nd != m_Objects.end());
		set_difference(InEnumLONG(&(*it1st).second), InEnumLONG(), InEnumLONG(&(*it2nd).second), InEnumLONG(), rIterOut);

	} COM_CATCH;
	return S_OK;
}

// Exklusives Oder (syymetrische Differenzmenge)
HRESULT CPropertyOperation::A_Xor_B (OutEnumLONG &rIterOut)
{
	COM_TRY {
	CMapOfPackets::iterator it1st = m_Objects.find(0);
	CMapOfPackets::iterator it2nd = m_Objects.find(1);

		_ASSERTE(it1st != m_Objects.end() && it2nd != m_Objects.end());
		set_symmetric_difference(InEnumLONG(&(*it1st).second), InEnumLONG(), InEnumLONG(&(*it2nd).second), InEnumLONG(), rIterOut);

	} COM_CATCH;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersist
STDMETHODIMP CPropertyOperation::GetClassID (CLSID *pClsID)
{
	*pClsID = GetObjectCLSID();
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistStreamInit
STDMETHODIMP CPropertyOperation::Load (IStream *pStm)
{
	if (IsInitialized())
		return E_UNEXPECTED;

	RETURN_FAILED_HRESULT(CPropertyActionImpl::Load (pStm));
	RETURN_FAILED_HRESULT(pStm->Read(&m_rgOperation, sizeof(m_rgOperation), NULL));
	SetInitialized();
	return S_OK;
}

STDMETHODIMP CPropertyOperation::Save (IStream *pStm, BOOL fClearDirty)
{
	RETURN_FAILED_HRESULT(CPropertyActionImpl::Save (pStm, fClearDirty));
	RETURN_FAILED_HRESULT(pStm->Write(&m_rgOperation, sizeof(m_rgOperation), NULL));
	return S_OK;
}

STDMETHODIMP CPropertyOperation::GetSizeMax (ULARGE_INTEGER *pcbSize)
{
	if (NULL == pcbSize)
		return E_POINTER;
	pcbSize -> QuadPart = 0L;

	RETURN_FAILED_HRESULT(CPropertyActionImpl::GetSizeMax (pcbSize));
	pcbSize  -> QuadPart += sizeof(m_rgOperation);
	return S_OK;
}

STDMETHODIMP CPropertyOperation::InitNew()
{
	if (IsInitialized())
		return E_UNEXPECTED;

	m_rgOperation = PROPERTYOPERATION_A_Or_B;
	SetInitialized();
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistPropertyBag
STDMETHODIMP CPropertyOperation::Load (IPropertyBag *pBag, IErrorLog *pLog)
{
	USES_CONVERSION;
	RETURN_FAILED_HRESULT(CPropertyActionImpl::Load (pBag, pLog));

// Operation=
CComVariant vOperation;
HRESULT hr = pBag -> Read (CComBSTR(g_cbOperation), &vOperation, pLog);

	if (S_OK == hr && SUCCEEDED(vOperation.ChangeType(VT_BSTR))) {
		if (!_wcsicmp (V_BSTR(&vOperation), g_cbA_Or_B))
			m_rgOperation = PROPERTYOPERATION_A_Or_B;
		else if (!_wcsicmp (V_BSTR(&vOperation), g_cbA_And_B))
			m_rgOperation = PROPERTYOPERATION_A_And_B;
		else if (!_wcsicmp (V_BSTR(&vOperation), g_cbA_And_NotB))
			m_rgOperation = PROPERTYOPERATION_A_And_NotB;
		else if (!_wcsicmp (V_BSTR(&vOperation), g_cbNotA_And_B))
			m_rgOperation = PROPERTYOPERATION_NotA_And_B;
		else if (!_wcsicmp (V_BSTR(&vOperation), g_cbA_Xor_B))
			m_rgOperation = PROPERTYOPERATION_A_Xor_B;
		else 
			m_rgOperation = PROPERTYOPERATION_A_Or_B;
	}
	return S_OK;
}

