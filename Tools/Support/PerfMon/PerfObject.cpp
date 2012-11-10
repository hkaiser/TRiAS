// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 12/26/1998 12:10:14 PM
//
// @doc
// @module PerfObject.cpp | Implementation of the <c CPerfObject> class

#include "stdafx.h"

#include <Com/PerfMonContext.h>
#include "Wrapper.h"

#include "PerfObject.h"

/////////////////////////////////////////////////////////////////////////////
// CPerfObject

STDMETHODIMP CPerfObject::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IPerfObject,
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
STDMETHODIMP CPerfObject::GetClassID (CLSID *pClassID)
{
	if (NULL == pClassID) 
		return E_POINTER;

	*pClassID = GetObjectCLSID();
	return S_OK;
}

// IPersistMemory
STDMETHODIMP CPerfObject::IsDirty ()
{
	return m_fIsDirty ? S_OK : S_FALSE;
}

STDMETHODIMP CPerfObject::Load (void *pvMem, ULONG cbSize)
{
	return E_NOTIMPL;
}

STDMETHODIMP CPerfObject::Save (void *pvMem, BOOL fClearDirty, ULONG cbSize)
{
	if (sizeof(PERF_OBJECT_TYPE) > cbSize)
		return E_UNEXPECTED;		// garantiert zu wenig Platz

void *pData = pvMem;		// LaufVariable
void *pvBase = pvMem;

// PERF_OBJECT_TYPE Struktur wegschreiben
ULONG ulBaseName = 0L;
ULONG ulBaseHelp = 0L;
WPerfContextHelper Ctx;

	RETURN_FAILED_HRESULT(GetPerfContext (m_ContextName, IID_IPerfContextHelper, Ctx.ppv()));

	Ctx -> get_BaseNameIndex (&ulBaseName);
	Ctx -> get_BaseHelpIndex (&ulBaseHelp);

	Advance(pData, 2*sizeof(DWORD));		// Größenfelder (TotalByteLength etc.) überspringen
	SaveAndAdvance(pData, (DWORD)sizeof(PERF_OBJECT_TYPE));	// HeaderLength
	SaveAndAdvance(pData, (DWORD)m_BaseIndex+ulBaseName);	// ObjectNameTitleIndex
	SaveAndAdvance(pData, (LPWSTR)NULL);					// ObjectNameTitle
	SaveAndAdvance(pData, (DWORD)(m_BaseIndex+ulBaseHelp));	// ObjectHelpTitleIndex
	SaveAndAdvance(pData, (LPWSTR)NULL);					// ObjectHelpTitle

// Infos über CounterDefs sammeln
ULONG ulCount = 0;
DETAILLEVEL rgDetailLevel = PERF_DETAIL_WIZARD;

	COM_TRY {
	WEnumVARIANT Enum;
	CComVariant v;

		THROW_FAILED_HRESULT(m_CounterDefs -> get_Count (&ulCount));
		THROW_FAILED_HRESULT(m_CounterDefs -> _NewEnum (Enum.ppu()));
		for (Enum -> Reset(); S_OK == Enum -> Next (1, &v, NULL); /**/) {
			_ASSERTE(V_VT(&v) == VT_DISPATCH);

		WPerfCounterDefinition CounterDef(V_DISPATCH(&v));
		DETAILLEVEL rgDetail = 0;

			THROW_FAILED_HRESULT(CounterDef -> get_Detail (&rgDetail));
			rgDetailLevel = min(rgDetail, rgDetailLevel);
		}
	} COM_CATCH;

	if (0 == ulCount)
		rgDetailLevel = PERF_DETAIL_NOVICE;
	SaveAndAdvance(pData, (DWORD)rgDetailLevel);			// DetailLevel
	SaveAndAdvance(pData, (DWORD)ulCount);					// NumCounters
	SaveAndAdvance(pData, 0L);								// DefaultCounter

// Infos über Instanzen sammeln
	ulCount = 0L;
	COM_TRY {
		THROW_FAILED_HRESULT(m_InstanceDefs -> get_Count (&ulCount));
	} COM_CATCH;

	SaveAndAdvance(pData, (DWORD)ulCount);					// NumInstances
	SaveAndAdvance(pData, 0L);								// CodePage
	SaveAndAdvance(pData, 0i64);							// PerfTime
	SaveAndAdvance(pData, 0i64);							// PerfFreq

	cbSize -= sizeof(PERF_OBJECT_TYPE);

// CounterDefinitionen
	COM_TRY {
	WEnumVARIANT Enum;
	CComVariant v;

		THROW_FAILED_HRESULT(m_CounterDefs -> _NewEnum (Enum.ppu()));
		for (Enum -> Reset(); S_OK == Enum -> Next (1, &v, NULL); /**/) {
			_ASSERTE(V_VT(&v) == VT_DISPATCH);

		WPersistMemory PMCounterDef(V_DISPATCH(&v));
		ULONG ulSize = 0L;

			THROW_FAILED_HRESULT(PMCounterDef -> GetSizeMax (&ulSize));
			if (ulSize > cbSize)
				return E_UNEXPECTED;		// Platz reicht nicht
			THROW_FAILED_HRESULT(PMCounterDef -> Save (pData, fClearDirty, ulSize));
			cbSize -= ulSize;
			Advance (pData, ulSize);
		}
	} COM_CATCH;

// jetzt DefinitionLength speichern
ptrdiff_t dist = Distance(pData, pvBase);

// InstanzDaten und Counter
	COM_TRY {
	WEnumVARIANT Enum;
	CComVariant v;

		THROW_FAILED_HRESULT(m_InstanceDefs -> _NewEnum (Enum.ppu()));
		for (Enum -> Reset(); S_OK == Enum -> Next (1, &v, NULL); /**/) {
			_ASSERTE(V_VT(&v) == VT_DISPATCH);

		WPersistMemory PMInstanceDef(V_DISPATCH(&v));
		ULONG ulSize = 0L;

			THROW_FAILED_HRESULT(PMInstanceDef -> GetSizeMax (&ulSize));
			if (ulSize > cbSize)
				return E_UNEXPECTED;		// Platz reicht nicht
			THROW_FAILED_HRESULT(PMInstanceDef -> Save (pData, fClearDirty, ulSize));
			cbSize -= ulSize;
			Advance (pData, ulSize);
		}
	} COM_CATCH;

// jetzt TotalByteLength schreiben
	SaveAndAdvance (pvMem, Distance(pData, pvBase));	// TotalByteLength
	SaveAndAdvance (pvMem, dist);						// DefinitionLength

	_ASSERTE(0 == cbSize);
	if (fClearDirty)
		m_fIsDirty = false;
	return S_OK;
}

STDMETHODIMP CPerfObject::GetSizeMax (ULONG *pcbSize)
{
ULONG cbSize = 0L;

	*pcbSize = 0L;

// die Struktur selbst
	cbSize = sizeof(PERF_OBJECT_TYPE);

// CounterDefinitionen
	COM_TRY {
	WEnumVARIANT Enum;
	CComVariant v;

		THROW_FAILED_HRESULT(m_CounterDefs -> _NewEnum (Enum.ppu()));
		for (Enum -> Reset(); S_OK == Enum -> Next (1, &v, NULL); /**/) {
			_ASSERTE(V_VT(&v) == VT_DISPATCH);

		WPersistMemory PMCounterDef(V_DISPATCH(&v));
		ULONG ulSize = 0L;

			THROW_FAILED_HRESULT(PMCounterDef -> GetSizeMax (&ulSize));
			cbSize += ulSize;
		}
	} COM_CATCH;

// InstanzDaten und Counter
	COM_TRY {
	WEnumVARIANT Enum;
	CComVariant v;

		THROW_FAILED_HRESULT(m_InstanceDefs -> _NewEnum (Enum.ppu()));
		for (Enum -> Reset(); S_OK == Enum -> Next (1, &v, NULL); /**/) {
			_ASSERTE(V_VT(&v) == VT_DISPATCH);

		WPersistMemory PMInstanceDef(V_DISPATCH(&v));
		ULONG ulSize = 0L;

			THROW_FAILED_HRESULT(PMInstanceDef -> GetSizeMax (&ulSize));
			cbSize += ulSize;
		}
	} COM_CATCH;

	*pcbSize = cbSize;
	return S_OK;
}

STDMETHODIMP CPerfObject::InitNew()
{
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Properties
IMPLEMENT_PROPERTY_ACCESS(CPerfObject, Name, BSTR);
IMPLEMENT_PROPERTY_ACCESS(CPerfObject, Description, BSTR);
IMPLEMENT_PROPERTY_ACCESS(CPerfObject, HelpText, BSTR);
IMPLEMENT_PROPERTY_GET(CPerfObject, BaseIndex, ULONG); 
IMPLEMENT_PROPERTY_GET(CPerfObject, ContextName, BSTR);

STDMETHODIMP CPerfObject::get_CounterDefs(IPerfCounterDefinitions **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal)
		return E_POINTER;

WPerfCounterDefinitions CounterDefs (m_CounterDefs);

	*pVal = CounterDefs.detach();
	return S_OK;
}

STDMETHODIMP CPerfObject::get_InstanceDefs(IPerfInstanceDefinitions **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal)
		return E_POINTER;

WPerfInstanceDefinitions InstanceDefs (m_InstanceDefs);

	*pVal = InstanceDefs.detach();
	return S_OK;
}

STDMETHODIMP CPerfObject::put_ContextName(BSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_ContextName = newVal;

WPerfContextHelper Ctx;

	RETURN_FAILED_HRESULT(GetPerfContext (m_ContextName, IID_IPerfContextHelper, Ctx.ppv()));
	return Ctx -> GetNextBaseIndex (&m_BaseIndex);
}

/////////////////////////////////////////////////////////////////////////////
// Methods
STDMETHODIMP CPerfObject::AddCounterDefinition(
	BSTR Name, BSTR Desc, BSTR HelpText, DETAILLEVEL rgDetail, LONG lScale, COUNTERTYPE rgType)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	COM_TRY {
	CComVariant v;

		if (SUCCEEDED(m_CounterDefs -> get_Item (CComVariant(Name), &v)))
			return S_FALSE;		// exitiert bereits

	WPerfCounterDefinition CounterDef;

		THROW_FAILED_HRESULT(CounterDef.LocalCreateInstance(CLSID_PerfCounterDefinition));
		THROW_FAILED_HRESULT(WPersistMemory(CounterDef) -> InitNew());

		THROW_FAILED_HRESULT(CounterDef -> put_ContextName (m_ContextName));
		THROW_FAILED_HRESULT(CounterDef -> put_Name (Name));
		THROW_FAILED_HRESULT(CounterDef -> put_Description (Desc));
		THROW_FAILED_HRESULT(CounterDef -> put_HelpText (HelpText));
		THROW_FAILED_HRESULT(CounterDef -> put_Detail (rgDetail));
		THROW_FAILED_HRESULT(CounterDef -> put_Type (rgType));
		THROW_FAILED_HRESULT(CounterDef -> put_DefaultScale (lScale));
		THROW_FAILED_HRESULT(CounterDef -> putref_TargetObject (this));

		THROW_FAILED_HRESULT(m_CounterDefs -> Append (CounterDef));
		m_fIsDirty = true;

	// alle Strukturen neu erzeugen
	WPerfContextHelper Ctx;

		THROW_FAILED_HRESULT(GetPerfContext (m_ContextName, IID_IPerfContextHelper, Ctx.ppv()));
		THROW_FAILED_HRESULT(Ctx -> RegeneratePerfData());

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CPerfObject::AddInstanceDefinition(BSTR Name, IPerfInstanceDefinition **ppIInstanceDef)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == ppIInstanceDef)
		return E_POINTER;

	COM_TRY {
	CComVariant v;
	WPerfInstanceDefinition InstanceDef;

		if (SUCCEEDED(m_InstanceDefs -> get_Item (CComVariant(Name), &v))) {
			THROW_FAILED_HRESULT(v.ChangeType (VT_DISPATCH));

			InstanceDef = (V_DISPATCH(&v));
			*ppIInstanceDef = InstanceDef.detach();
			return S_FALSE;		// exitiert bereits
		}

		THROW_FAILED_HRESULT(InstanceDef.LocalCreateInstance(CLSID_PerfInstanceDefinition));
		THROW_FAILED_HRESULT(WPersistMemory(InstanceDef) -> InitNew());

		THROW_FAILED_HRESULT(InstanceDef -> put_ContextName (m_ContextName));
		THROW_FAILED_HRESULT(InstanceDef -> put_Name (Name));
		THROW_FAILED_HRESULT(InstanceDef -> putref_TargetObject (this));

		THROW_FAILED_HRESULT(m_InstanceDefs -> Append (InstanceDef));
		m_fIsDirty = true;

		*ppIInstanceDef = InstanceDef.detach();

	// alle Strukturen neu erzeugen
	WPerfContextHelper Ctx;

		THROW_FAILED_HRESULT(GetPerfContext (m_ContextName, IID_IPerfContextHelper, Ctx.ppv()));
		THROW_FAILED_HRESULT(Ctx -> RegeneratePerfData());

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CPerfObject::AddCounter(BSTR bstrInstance, IPerfCollect *pICollect)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	COM_TRY {
	// InstanceDefinition muß exitieren
	CComVariant v;

		THROW_FAILED_HRESULT(m_InstanceDefs -> get_Item (CComVariant(bstrInstance), &v));
		THROW_FAILED_HRESULT(v.ChangeType (VT_DISPATCH));

	WPerfInstanceDefinition InstanceDef (V_DISPATCH(&v));
	WPerfCounterDefinition SrcDef(pICollect);
	CComBSTR Name;

		THROW_FAILED_HRESULT(SrcDef -> get_Name (&Name));

		v.Clear();
		if (FAILED(m_CounterDefs -> get_Item (CComVariant(Name), &v)) || FAILED(v.ChangeType (VT_DISPATCH))) 
		{
		// CounterDefinition exitiert noch nicht, wer zuerst kommt malt zuerst ...
		WPerfCounterDefinition CounterDef;

			THROW_FAILED_HRESULT(CounterDef.LocalCreateInstance(CLSID_PerfCounterDefinitionCollect));
			THROW_FAILED_HRESULT(WPersistMemory(CounterDef) -> InitNew());

			THROW_FAILED_HRESULT(CounterDef -> put_ContextName (m_ContextName));
			THROW_FAILED_HRESULT(CounterDef -> put_Name (Name));

		CComBSTR Desc;

			THROW_FAILED_HRESULT(SrcDef -> get_Description (&Desc));
			THROW_FAILED_HRESULT(CounterDef -> put_Description (Desc));

		CComBSTR HelpText;

			THROW_FAILED_HRESULT(SrcDef -> get_HelpText(&HelpText));
			THROW_FAILED_HRESULT(CounterDef -> put_HelpText (HelpText));

		DETAILLEVEL rgDetail = PERF_DETAIL_NOVICE;

			THROW_FAILED_HRESULT(SrcDef -> get_Detail (&rgDetail));
			THROW_FAILED_HRESULT(CounterDef -> put_Detail (rgDetail));

		COUNTERTYPE rgType = PERF_COUNTER_COUNTER;

			THROW_FAILED_HRESULT(SrcDef -> get_Type (&rgType));
			THROW_FAILED_HRESULT(CounterDef -> put_Type (rgType));

		LONG lScale = 0;

			THROW_FAILED_HRESULT(SrcDef -> get_DefaultScale (&lScale));
			THROW_FAILED_HRESULT(CounterDef -> put_DefaultScale (lScale));

			THROW_FAILED_HRESULT(CounterDef -> putref_TargetObject (this));

			THROW_FAILED_HRESULT(m_CounterDefs -> Append (CounterDef));

		// jetzt noch diesen (vorinstantiierten Counter) zur InstanceDef hinzufügen
//			THROW_FAILED_HRESULT(InstanceDef -> AddCollectCounter (pICollect));
			
			m_fIsDirty = true;
		}

	// alle Strukturen neu erzeugen
	WPerfContextHelper Ctx;

		THROW_FAILED_HRESULT(GetPerfContext (m_ContextName, IID_IPerfContextHelper, Ctx.ppv()));
		THROW_FAILED_HRESULT(Ctx -> RegeneratePerfData());

	} COM_CATCH;
	return S_OK;
}
