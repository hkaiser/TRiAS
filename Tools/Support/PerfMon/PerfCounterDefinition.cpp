// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 12/26/1998 12:14:15 PM
//
// @doc
// @module PerfCounterDefinition.cpp | Implementation of the <c CPerfCounterDefinitionBase> class

#include "stdafx.h"

#include <Com/PerfMonContext.h>
#include "Wrapper.h"

#include "PerfCounterDefinition.h"

/////////////////////////////////////////////////////////////////////////////
// CPerfCounterDefinitionBase

STDMETHODIMP CPerfCounterDefinitionBase::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IPerfCounterDefinition,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistMemory
STDMETHODIMP CPerfCounterDefinitionBase::IsDirty ()
{
	return m_fIsDirty ? S_OK : S_FALSE;
}

STDMETHODIMP CPerfCounterDefinitionBase::Load (void *pvMem, ULONG cbSize)
{
	return E_NOTIMPL;
}

STDMETHODIMP CPerfCounterDefinitionBase::Save (void *pvMem, BOOL fClearDirty, ULONG cbSize)
{
	if (sizeof(PERF_COUNTER_DEFINITION) > cbSize)
		return E_UNEXPECTED;		// zu wenig Platz

void *pData = pvMem;

// PERF_COUNTER_DEFINITION Struktur wegschreiben
ULONG ulBaseName = 0L;
ULONG ulBaseHelp = 1L;
WPerfContextHelper Ctx;

	RETURN_FAILED_HRESULT(GetPerfContext (m_ContextName, IID_IPerfContextHelper, Ctx.ppv()));

	Ctx -> get_BaseNameIndex (&ulBaseName);
	Ctx -> get_BaseHelpIndex (&ulBaseHelp);

	SaveAndAdvance(pData, (DWORD)sizeof(PERF_COUNTER_DEFINITION));	// ByteLength
	SaveAndAdvance(pData, (DWORD)m_BaseIndex+ulBaseName);	// CounterNameTitleIndex
	SaveAndAdvance(pData, (LPWSTR)NULL);					// CounterNameTitle
	SaveAndAdvance(pData, (DWORD)(m_BaseIndex+ulBaseHelp));	// CounterHelpTitleIndex
	SaveAndAdvance(pData, (LPWSTR)NULL);					// CounterHelpTitle

	SaveAndAdvance(pData, m_DefaultScale);					// DefaultScale
	SaveAndAdvance(pData, (DWORD)m_Detail);					// DetailLevel

	SaveAndAdvance(pData, (DWORD)m_Type);					// CounterType
	SaveAndAdvance(pData, (DWORD)SizeFromType(m_Type));		// CounterSize

	COM_TRY {
		_ASSERTE(NULL != m_pITargetObject);

	WPerfCounterDefinitions Defs;

		THROW_FAILED_HRESULT(m_pITargetObject -> get_CounterDefs (Defs.ppi()));

	WEnumVARIANT Enum;
	CComVariant v;
	DWORD cbOffset = sizeof(DWORD);	// PERF_COUNTER_BLOCK starts with 'DWORD ByteLength'

		THROW_FAILED_HRESULT(Defs -> _NewEnum(Enum.ppu()));
		for (Enum -> Reset(); S_OK == Enum -> Next (1, &v, NULL); /**/) {
			_ASSERTE(V_VT(&v) == VT_DISPATCH);

		WPerfCounterDefinition Def (V_DISPATCH(&v));
		COUNTERTYPE rgType = 0;

			if (Def == WPerfCounterDefinition(GetUnknown()))
				break;		// nur alle _vor_ uns beachten

			THROW_FAILED_HRESULT(Def -> get_Type (&rgType));
			cbOffset += SizeFromType (rgType);
		}
		SaveAndAdvance(pData, (DWORD)cbOffset);			// CounterOffset

	} COM_CATCH;
	cbSize -= sizeof(PERF_COUNTER_DEFINITION);

	_ASSERTE(0 == cbSize);
	if (fClearDirty)
		m_fIsDirty = false;
	return S_OK;
}

STDMETHODIMP CPerfCounterDefinitionBase::GetSizeMax (ULONG *pcbSize)
{
	*pcbSize = sizeof(PERF_COUNTER_DEFINITION);
	return S_OK;
}

STDMETHODIMP CPerfCounterDefinitionBase::InitNew()
{
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Properties
IMPLEMENT_PROPERTY_ACCESS(CPerfCounterDefinitionBase, Name, BSTR);
IMPLEMENT_PROPERTY_ACCESS(CPerfCounterDefinitionBase, Description, BSTR);
IMPLEMENT_PROPERTY_ACCESS(CPerfCounterDefinitionBase, HelpText, BSTR);
IMPLEMENT_PROPERTY_ACCESS(CPerfCounterDefinitionBase, Detail, DETAILLEVEL);
IMPLEMENT_PROPERTY_ACCESS(CPerfCounterDefinitionBase, Type, COUNTERTYPE);
IMPLEMENT_PROPERTY_ACCESS(CPerfCounterDefinitionBase, DefaultScale, LONG);
IMPLEMENT_PROPERTY_GET(CPerfCounterDefinitionBase, BaseIndex, ULONG); 
IMPLEMENT_PROPERTY_GET(CPerfCounterDefinitionBase, ContextName, BSTR);

STDMETHODIMP CPerfCounterDefinitionBase::putref_TargetObject(IPerfObject *newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_pITargetObject = newVal;		// no AddRef !
	return S_OK;
}

STDMETHODIMP CPerfCounterDefinitionBase::put_ContextName(BSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_ContextName = newVal;

WPerfContextHelper Ctx;

	RETURN_FAILED_HRESULT(GetPerfContext (m_ContextName, IID_IPerfContextHelper, Ctx.ppv()));
	return Ctx -> GetNextBaseIndex (&m_BaseIndex);
}

///////////////////////////////////////////////////////////////////////////////
// IPersist
STDMETHODIMP CPerfCounterDefinition::GetClassID (CLSID *pClassID)
{
	if (NULL == pClassID) 
		return E_POINTER;

	*pClassID = CLSID_PerfCounterDefinition;
	return S_OK;
}

STDMETHODIMP CPerfCounterDefinition::CreateCounter(IPerfCounter **ppICounter)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	COM_TRY {
	WPerfCounter Counter;

		THROW_FAILED_HRESULT(Counter.LocalCreateInstance (sizeof(LONG) == SizeFromType(m_Type) ? CLSID_PerfCounterInt32 : CLSID_PerfCounterInt64));
		THROW_FAILED_HRESULT(WPersistMemory(Counter) -> InitNew());
		*ppICounter = Counter.detach();

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// CPerfCounterDefinitionCollect

// IPersist
STDMETHODIMP CPerfCounterDefinitionCollect::GetClassID (CLSID *pClassID)
{
	if (NULL == pClassID) 
		return E_POINTER;

	*pClassID = CLSID_PerfCounterDefinitionCollect;
	return S_OK;
}

STDMETHODIMP CPerfCounterDefinitionCollect::CreateCounter(IPerfCounter **ppICounter)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	COM_TRY {
	WPerfCounter Counter;

		THROW_FAILED_HRESULT(Counter.LocalCreateInstance (CLSID_PerfCounterCollect));
		THROW_FAILED_HRESULT(WPersistMemory(Counter) -> InitNew());
		*ppICounter = Counter.detach();

	} COM_CATCH;
	return S_OK;
}
