// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 12/26/1998 12:26:51 PM
//
// @doc
// @module PerfInstanceDefinition.cpp | Implementation of the <c CPerfInstanceDefinition> class

#include "stdafx.h"

#include <Com/PerfMonContext.h>
#include "Wrapper.h"

#include "PerfInstanceDefinition.h"

/////////////////////////////////////////////////////////////////////////////
// CPerfInstanceDefinition

STDMETHODIMP CPerfInstanceDefinition::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IPerfInstanceDefinition,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// IPersist
STDMETHODIMP CPerfInstanceDefinition::GetClassID (CLSID *pClassID)
{
	if (NULL == pClassID) 
		return E_POINTER;

	*pClassID = GetObjectCLSID();
	return S_OK;
}

// IPersistMemory
STDMETHODIMP CPerfInstanceDefinition::IsDirty ()
{
	return m_fIsDirty ? S_OK : S_FALSE;
}

STDMETHODIMP CPerfInstanceDefinition::Load (void *pvMem, ULONG cbSize)
{
	return E_NOTIMPL;
}

STDMETHODIMP CPerfInstanceDefinition::Save (void *pvMem, BOOL fClearDirty, ULONG cbSize)
{
DWORD dwNameLen = (m_Name.Length()+1) * sizeof(WCHAR);

	if (sizeof(PERF_INSTANCE_DEFINITION) + DWORD_MULTIPLE(dwNameLen) > cbSize)
		return E_UNEXPECTED;		// garantiert zu wenig Platz

	RETURN_FAILED_HRESULT(RegenerateCounters());

void *pData = pvMem;		// LaufVariable

// PERF_INSTANCE_DEFINITION Struktur wegschreiben (evtl. mit padding)
	SaveAndAdvance(pData, (DWORD)sizeof(PERF_INSTANCE_DEFINITION) + DWORD_MULTIPLE(dwNameLen));	// ByteLength
	SaveAndAdvance(pData, (DWORD)0);					// ParentObjectTitleIndex
	SaveAndAdvance(pData, (DWORD)0);					// ParentObjectInstance
	SaveAndAdvance(pData, (LONG)PERF_NO_UNIQUE_ID);		// UniqueID
	SaveAndAdvance(pData, (DWORD)sizeof(PERF_INSTANCE_DEFINITION));		// NameOffset
	SaveAndAdvance(pData, (DWORD)dwNameLen);			// NameLength
	SaveAndAdvance(pData, m_Name, dwNameLen);			// Name
	Advance (pData, DWORD_MULTIPLE(dwNameLen)-dwNameLen);

	cbSize -= sizeof(PERF_INSTANCE_DEFINITION) + DWORD_MULTIPLE(dwNameLen);

// zugehörige CounterDaten wegschreiben (PERF_COUNTER_BLOCK)
void *pvBase = pData;					// hier ByteLength wegschreiben
DWORD dwCounterSize = sizeof(DWORD);

	Advance (pData, sizeof(DWORD));		// Platz für ByteLength lassen
	COM_TRY {
	WEnumVARIANT Enum;
	CComVariant v;

		THROW_FAILED_HRESULT(m_Counters -> _NewEnum(Enum.ppu()));
		for (Enum -> Reset(); S_OK == Enum -> Next (1, &v, NULL); /**/) {
			_ASSERTE(V_VT(&v) == VT_DISPATCH);

		WPersistMemory PMCounter (V_DISPATCH(&v));
		ULONG ulSize = 0L;

			THROW_FAILED_HRESULT(PMCounter -> GetSizeMax (&ulSize));
			if (ulSize > cbSize)
				return E_UNEXPECTED;
			THROW_FAILED_HRESULT(PMCounter -> Save (pData, fClearDirty, ulSize));
			cbSize -= ulSize;
			Advance (pData, ulSize);

			dwCounterSize += ulSize;	// CounterSize kumulieren
		}

	// GesamtLänge des PERF_COUNTER_BLOCK am Anfang wegschreiben
		SaveAndAdvance(pvBase, (DWORD)dwCounterSize);			// PERF_COUNTER_BLOCK.ByteLength
		cbSize -= sizeof(DWORD);
	} COM_CATCH;

	_ASSERTE(0 == cbSize);
	if (fClearDirty)
		m_fIsDirty = false;
	return S_OK;
}

STDMETHODIMP CPerfInstanceDefinition::GetSizeMax (ULONG *pcbSize)
{
	RETURN_FAILED_HRESULT(RegenerateCounters());

ULONG cbSize = 0;
DWORD dwNameLen = (m_Name.Length()+1) * sizeof(WCHAR);

	*pcbSize = 0L;
	cbSize = sizeof(PERF_INSTANCE_DEFINITION) + DWORD_MULTIPLE(dwNameLen);
	cbSize += sizeof(PERF_COUNTER_BLOCK);

	COM_TRY {
	WEnumVARIANT Enum;
	CComVariant v;

		THROW_FAILED_HRESULT(m_Counters -> _NewEnum(Enum.ppu()));
		for (Enum -> Reset(); S_OK == Enum -> Next (1, &v, NULL); /**/) {
			_ASSERTE(V_VT(&v) == VT_DISPATCH);

		WPersistMemory PMCounter (V_DISPATCH(&v));
		ULONG ulSize = 0L;

			THROW_FAILED_HRESULT(PMCounter -> GetSizeMax (&ulSize));
			cbSize += ulSize;
		}
	} COM_CATCH;

	*pcbSize = cbSize;
	return S_OK;
}

STDMETHODIMP CPerfInstanceDefinition::InitNew()
{
	return S_OK;
}

HRESULT CPerfInstanceDefinition::RegenerateCounters()
{
	COM_TRY {
		if (NULL != m_pITargetObject) {
		// CounterDefinitions durchgehen und die Counter erzeugen, die noch nicht da sind
		WPerfCounterDefinitions Defs;

			_ASSERTE(NULL != m_pITargetObject);
			THROW_FAILED_HRESULT(m_pITargetObject -> get_CounterDefs (Defs.ppi()));

		WEnumVARIANT Enum;
		CComVariant v;

			THROW_FAILED_HRESULT(Defs -> _NewEnum(Enum.ppu()));
			for (Enum -> Reset(); S_OK == Enum -> Next (1, &v, NULL); /**/) {
				_ASSERTE(V_VT(&v) == VT_DISPATCH);

			WPerfCounterDefinition Def (V_DISPATCH(&v));
			CComVariant vDummy;
			CComBSTR bstrName;

				THROW_FAILED_HRESULT(Def -> get_Name (&bstrName));

				if (FAILED(m_Counters -> get_Item (CComVariant (bstrName), &vDummy))) {
				// nur neu erzeugen, wenn dieser Counter noch nicht existiert
				COUNTERTYPE rgType = 0;

					THROW_FAILED_HRESULT(Def -> get_Type (&rgType));

				// richtigen Counter erzeugen lassen
				WPerfCounter Counter;
				
					THROW_FAILED_HRESULT(Def -> CreateCounter (Counter.ppi()));

					THROW_FAILED_HRESULT(Counter -> put_ContextName (m_ContextName));
					THROW_FAILED_HRESULT(Counter -> put_Name (bstrName));
					THROW_FAILED_HRESULT(Counter -> put_Type (rgType));

					THROW_FAILED_HRESULT(m_Counters -> Append (Counter));
				}
			}
		}
	} COM_CATCH;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Properties

IMPLEMENT_PROPERTY_ACCESS(CPerfInstanceDefinition, Name, BSTR);
IMPLEMENT_PROPERTY_ACCESS(CPerfInstanceDefinition, ContextName, BSTR);

STDMETHODIMP CPerfInstanceDefinition::putref_TargetObject(IPerfObject *newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_pITargetObject = newVal;		// no AddRef !
	return S_OK;
}

STDMETHODIMP CPerfInstanceDefinition::get_Counter(BSTR bstrName, IPerfCounter **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal)
		return E_POINTER;

	COM_TRY {
	CComVariant vResult;

		THROW_FAILED_HRESULT(m_Counters -> get_Item (CComVariant(bstrName), &vResult));
		THROW_FAILED_HRESULT(vResult.ChangeType (VT_DISPATCH));

	WPerfCounter Counter (V_DISPATCH(&vResult));

		*pVal = Counter.detach();

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CPerfInstanceDefinition::get_Counters(IPerfCounters * * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal)
		return E_POINTER;

WPerfCounters Counters (m_Counters);

	*pVal = Counters.detach();
	return S_OK;
}

