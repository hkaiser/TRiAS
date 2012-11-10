// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 01.11.2002 12:26:50 
//
// @doc
// @module VBPropertySequence.h | Declaration of the <c CVBGeoComponent> class

#if !defined(_VBPROPERTYSEQUENCE_H__CE8ABFC7_7B1A_4C39_8516_46F3EB10A183__INCLUDED_)
#define _VBPROPERTYSEQUENCE_H__CE8ABFC7_7B1A_4C39_8516_46F3EB10A183__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <Com/PropertyActionBase.h>

#include "trias03.h"       // main symbols
#include "VBPropertySequenceDlg.h"

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(GeoComponent);

/////////////////////////////////////////////////////////////////////////////
// CVBGeoComponent
class ATL_NO_VTABLE CVBGeoComponent : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CVBGeoComponent, &CLSID_VBGeoComponent>,
	public CPropertyActionImpl,
	public IObjectWithSiteImpl<CVBGeoComponent>,
	public IDispatchImpl<IGeoComponentCallback, &IID_IGeoComponentCallback,
		&LIBID_TRiAS, TYPELIB_VERSION_MAJOR, TYPELIB_VERSION_MINOR>
{
public:
	enum { 
		PA_TYPEFLAGS = 
			PROPCAPS_ACTION_SINK |
			PROPCAPS_ACTION_SOURCE |
			PROPCAPS_NONE
	};

	CVBGeoComponent() : 
		CPropertyActionImpl (PA_TYPEFLAGS, IDS_DESCRIPTION_VBPROPERTYSEQUENCE)
	{
		m_ppCfgDlgs = NULL;
		m_lDlgCount = 0;
	}
	~CVBGeoComponent()
	{
		ReleaseDlgs();
	}

	HRESULT FinalConstruct();
	void FinalRelease();

	DECLARE_REGISTRY_RESOURCEID(IDR_VBGEOCOMPONENT)
	DECLARE_PROTECT_FINAL_CONSTRUCT()
	DECLARE_GET_CONTROLLING_UNKNOWN()

	BEGIN_COM_MAP(CVBGeoComponent)
		COM_INTERFACE_ENTRY(IPropertyAction)
		COM_INTERFACE_ENTRY(IPropertyAction2)
		COM_INTERFACE_ENTRY(IPropertyAction3)
		COM_INTERFACE_ENTRY(IClassProperty)
		COM_INTERFACE_ENTRY(IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersistStream, IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
		COM_INTERFACE_ENTRY(IPersistPropertyBag)
		COM_INTERFACE_ENTRY(IPropertyInfo)
		COM_INTERFACE_ENTRY(IObjectWithSite)
		COM_INTERFACE_ENTRY(IGeoComponentCallback)
		COM_INTERFACE_ENTRY2(IDispatch, IGeoComponentCallback)
	END_COM_MAP()

// IPropertyAction 
public:
	STDMETHOD(BeginAction) (THIS_ IProgressIndicator *pIProgInd);
	STDMETHOD(DoAction) (THIS_ IDataObject *pEnumObj, DWORD dwReserved);
	STDMETHOD(EndAction) (THIS_ DWORD dwReserved, IDataObject **ppEnumObj);

// Geokomponente hat eigenen Dialog
	STDMETHOD(PreConfigPages)(THIS_ IDataObject *pIDataObject, DWORD dwFlags);
	STDMETHOD(AddConfigPages)(THIS_ LPFNADDPROPSHEETPAGE lpfnAddPage, 
		LPARAM lParam, LPCSTR pcDesc, UINT *puiCnt);

// IPersist
	STDMETHOD(GetClassID) (THIS_ CLSID *pClsID);
// IPersistStreamInit
	STDMETHOD(Load)(THIS_ IStream *pStm);
	STDMETHOD(Save)(THIS_ IStream *pStm, BOOL fClearDirty);
	STDMETHOD(GetSizeMax)(THIS_ ULARGE_INTEGER *pcbSize);
	STDMETHOD(InitNew) (THIS);

// IGeoComponentCallback
	STDMETHOD(get_ContextData)(ITRiASDataObject **ppIDataCtx);
	STDMETHOD(get_IsSequence)(VARIANT_BOOL *pfIsSeq)
	{
		*pfIsSeq = VARIANT_TRUE;
		return S_OK;
	}

// IPersistPropertyBag
	STDMETHOD(Load)(THIS_ IPropertyBag *pBag, IErrorLog *pLog);

public:
	HRESULT CreateEmbeddedAction (BSTR bstrProgId);

protected:
	void ReleaseDlgs()
	{
		for (long i = 0; i < m_lDlgCount; ++i) {
			if (m_ppCfgDlgs[i]) {
				m_ppCfgDlgs[i] -> Release();
				m_ppCfgDlgs[i] = NULL;
			}
		}
		DELETE_OBJ(m_ppCfgDlgs);
		m_lDlgCount = 0;
	}
	void ReleaseAll();

private:
	CIID m_GuidInit;
	WGeoComponent m_EmbeddedObj;
	long m_lDlgCount;					// Anzahl der Dialoge
	CVBGeoComponentDlg **m_ppCfgDlgs;	// Konfigurationsdialoge
};

#endif // !defined(_VBPROPERTYSEQUENCE_H__CE8ABFC7_7B1A_4C39_8516_46F3EB10A183__INCLUDED_)
