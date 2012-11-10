// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 23.12.2000 22:48:30 
//
// @doc
// @module StatisticObjectProperty.h | Declaration of the <c CStatisticObjectProperty> class

#if !defined(_STATISTICOBJECTPROPERTY_H__71DD1845_8456_49CC_A433_7BD486199414__INCLUDED_)
#define _STATISTICOBJECTPROPERTY_H__71DD1845_8456_49CC_A433_7BD486199414__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"       // main symbols

#include <Com/ObjectPropertyBase.h>
#include <ipropseq.hxx>

///////////////////////////////////////////////////////////////////////////////
// Objekteigenschaft CStatisticObjectProperty
class ATL_NO_VTABLE CStatisticObjectProperty : 
	public CComCoClass<CStatisticObjectProperty, &CLSID_StatisticObjectProperty>,
	public IPropertyInfo,
	public IConfigObjectProperty,
	public IConfigSequenceForObjectProperty,
	public CObjectPropertyBase
{
public:
	CStatisticObjectProperty() : 
		CObjectPropertyBase (IDS_OP_NAME_STATISTICOBJECTPROPERTY, IDS_OP_DESCRIPTION_STATISTICOBJECTPROPERTY),
		m_fIsConfigured(false), m_fHasAddedPage(false), 
		m_dwFlags(PROPCAPS_OBJPROPTYPE_DOUBLE|PROPCAPS_INTERACTIVE_INIT),
		m_hWndParent(NULL)
	{
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_STATISTICOBJECTPROPERTY)
	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CStatisticObjectProperty)
		COM_INTERFACE_ENTRY(IPropertyInfo)
		COM_INTERFACE_ENTRY(IConfigObjectProperty)
		COM_INTERFACE_ENTRY(IConfigSequenceForObjectProperty)
		COM_INTERFACE_ENTRY_CHAIN(CObjectPropertyBase)	// alles andere macht die Basisklasse
	END_COM_MAP()

	HRESULT FinalConstruct()
	{
	// die Erweiterung muß geladen sein
		if (!g_pTE -> isLoaded())
			return E_UNEXPECTED;
		return m_CumPts.LocalCreateInstance (CLSID_TRiASSimpleStatistics);
	}
	void FinalRelease()
	{
		m_CumPts.Assign (NULL);
	}


// IPersist methods
	STDMETHOD(GetClassID)(THIS_ CLSID *pClsID);

// IPersistStream methods
	STDMETHOD(Load)(THIS_ IStream *pStm);
	STDMETHOD(Save)(THIS_ IStream *pStm, BOOL fClearDirty);
	STDMETHOD(GetSizeMax)(THIS_ ULARGE_INTEGER * pcbSize);

// IPersistStreamInit methods
	STDMETHOD(InitNew)(THIS);

// IPropertyInfo
	STDMETHOD(SetPropInfo) (THIS_ LPCSTR pBuffer, DWORD dwFlags);
	STDMETHOD(SetHelpInfo) (THIS_ LPCSTR pBuffer, LPCSTR pHelpFile, ULONG ulHelpCtx);

// IConfigObjectProperty
	STDMETHOD(ConfigObjectProperty) (THIS_ HWND hWndParent);
	STDMETHOD(get_IsConfigured) (VARIANT_BOOL *pfConfigState);

// IConfigSequenceForObjectProperty
	STDMETHOD(AddAction) (THIS_ IUnknown *pIAct);
	STDMETHOD(AddActionsByCLSID) (THIS_ CALPCLSID *pcaClsIds);
	STDMETHOD(PrepareActions) (THIS_ HWND hWndParent, IDataObject *pIData);

// IObjectProperty
public:
	STDMETHOD(Reset)(THIS);
	STDMETHOD(GetPropInfo) (THIS_ LPSTR pBuffer, WORD wLen, DWORD *pdwData);
	STDMETHOD(Cumulation)(THIS_ LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten);
	STDMETHOD(Eval)(THIS_ LONG lONr, LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten);
	STDMETHOD(HelpInfo)(THIS_ LPSTR pBuffer, ULONG ulLen, LPSTR pHelpFile, ULONG *pulHelpCtx);

protected:
	void SetFlags(DWORD dwFlags) { m_dwFlags = dwFlags; }
	DWORD GetFlags() { return m_dwFlags; }

private:
	WPropertyActionSequence m_Seq;
	bool m_fIsConfigured;
	bool m_fHasAddedPage;
	DWORD m_dwFlags;
	HWND m_hWndParent;
	CString m_strDesc;

	WTRiASSimpleStatistics m_CumPts;	// kumulierter Wert
};

#endif // !defined(_STATISTICOBJECTPROPERTY_H__71DD1845_8456_49CC_A433_7BD486199414__INCLUDED_)
