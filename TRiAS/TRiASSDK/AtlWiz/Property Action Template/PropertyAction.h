[!if=(FreeThreadedMarshaler, "TRUE")]
	[!set(NeedsGetControllingUnknown, "TRUE")]
[!endif]
// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: [!DateAndTime]
//
// @doc
// @module [!HeaderName] | Declaration of the <c [!ClassName]> class

[!crlf]
[!if=(FileExists, "FALSE")]
#if !defined(__[!UpperShortName]_H_)
#define __[!UpperShortName]_H_
[!crlf]
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
[!crlf]
// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif
[!crlf]
#include "resource.h"       // main symbols
[!else]
[!AddIncludeFile(TargetFile, "resource.h")]
[!endif]

[!crlf]
#include <Com/PropertyActionBase.h>

[!crlf]
#include <ienumobj.hxx>
#include <ospace/com/iterenum.h>
#include <ospace/std/set>

[!if=(PropActHasUI, "TRUE")]
[!crlf]
#include "[!DlgHeaderName]"
[!endif]

[!crlf]
/////////////////////////////////////////////////////////////////////////////
// Declaration diverser Klassen
#if !defined(_ENUM_LONG_ENUMERATOR_DEFINED)
#define _ENUM_LONG_ENUMERATOR_DEFINED

[!crlf]
DefineSortingEnumerator(LONG);		// definiert SEnumLONG
DefineSmartEnumerator2(LONG, __uuidof(IEnumLONG));		// definiert WEnumLONG (Wrapper für IEnum<LONG>)
DefineEnumInputIterator(LONG);		// definiert InEnumLONG
DefineEnumOutputIterator(LONG);		// definiert OutEnumLONG 

[!crlf]
#endif // _ENUM_LONG_ENUMERATOR_DEFINED

[!crlf]
/////////////////////////////////////////////////////////////////////////////
// [!ClassName]
class ATL_NO_VTABLE [!ClassName] : 
[!if=(ThreadingModel, "Single")]
	public CComObjectRootEx<CComSingleThreadModel>,
[!endif]
[!if=(ThreadingModel, "Apartment")]
	public CComObjectRootEx<CComSingleThreadModel>,
[!endif]
[!if=(ThreadingModel, "Both")]
	public CComObjectRootEx<CComMultiThreadModel>,
[!endif]
[!if=(ThreadingModel, "Free")]
	public CComObjectRootEx<CComMultiThreadModel>,
[!endif]
	public CComCoClass<[!ClassName], &CLSID_[!CoClassName]>,
[!if=(IOBJECTWITHSITE, "TRUE")]
	public IObjectWithSiteImpl<[!ClassName]>,
[!endif]
	public CPropertyActionImpl
{
public:
	enum { 
		PA_TYPEFLAGS = 
[!if=(PropActDataSink, "TRUE")]
			PROPCAPS_ACTION_SINK |
[!endif]
[!if=(PropActDataSource, "TRUE")]
			PROPCAPS_ACTION_SOURCE |
[!endif]
[!if=(PropActRepaint, "TRUE")]
			PROPCAPS_ACTION_MUSTREPAINT |
[!endif]
			PROPCAPS_NONE
	};

[!crlf]
	[!ClassName]() : 
		CPropertyActionImpl (PA_TYPEFLAGS, [!IDS_PA_DESCRIPTION])
	{
[!if=(FreeThreadedMarshaler, "TRUE")]
		m_pUnkMarshaler = NULL;
[!endif]
[!if=(PropActHasUI, "TRUE")]
		m_pCfgDlg = NULL;
[!endif]
	}
[!if=(PropActHasUI, "TRUE")]
	~[!ClassName]()
	{
		DELETE_OBJ(m_pCfgDlg);
	}
[!endif]

[!crlf]
	DECLARE_REGISTRY_RESOURCEID([!IDR_REGISTRYID])
[!if=(Aggregatable, "NO")]
	DECLARE_NOT_AGGREGATABLE([!ClassName])
[!endif]
[!if=(Aggregatable, "ONLY")]
	DECLARE_ONLY_AGGREGATABLE([!ClassName])
[!endif]

[!if=(NeedsGetControllingUnknown, "TRUE")]
	DECLARE_GET_CONTROLLING_UNKNOWN()
[!endif]
[!crlf]
	DECLARE_PROTECT_FINAL_CONSTRUCT()
[!if=(FreeThreadedMarshaler, "TRUE")]
[!crlf]
	HRESULT FinalConstruct()
	{
		return CoCreateFreeThreadedMarshaler(
			GetControllingUnknown(), &m_pUnkMarshaler.p);
	}

[!crlf]
	void FinalRelease()
	{
		m_pUnkMarshaler.Release();
	}

[!crlf]
	CComPtr<IUnknown> m_pUnkMarshaler;
[!endif]

	BEGIN_COM_MAP([!ClassName])
		COM_INTERFACE_ENTRY(IPropertyAction)
		COM_INTERFACE_ENTRY(IPropertyAction2)
		COM_INTERFACE_ENTRY(IClassProperty)
		COM_INTERFACE_ENTRY(IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersistStream, IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
		COM_INTERFACE_ENTRY(IPersistPropertyBag)
		COM_INTERFACE_ENTRY(IPropertyInfo)
[!if=(IOBJECTWITHSITE, "TRUE")]
		COM_INTERFACE_ENTRY(IObjectWithSite)
[!endif]
	END_COM_MAP()

[!crlf]
// IPropertyAction 
public:
	STDMETHOD(BeginAction) (THIS_ IProgressIndicator *pIProgInd);
	STDMETHOD(DoAction) (THIS_ IDataObject *pEnumObj, DWORD dwReserved);
	STDMETHOD(EndAction) (THIS_ DWORD dwReserved, IDataObject **ppEnumObj);
[!if=(PropActHasUI, "TRUE")]
[!crlf]
// Geokomponente hat eigenen Dialog
	STDMETHOD(PreConfigPages)(THIS_ IDataObject *pIDataObject, DWORD dwFlags);
	STDMETHOD(AddConfigPages)(THIS_ LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam, LPCSTR pcDesc, UINT *puiCnt);
[!endif]

[!crlf]
// IPersist
	STDMETHOD(GetClassID) (THIS_ CLSID *pClsID);

[!if=(IPERSISTSTREAMINIT, "TRUE")]
// IPersistStreamInit
	STDMETHOD(Load)(THIS_ IStream *pStm);
	STDMETHOD(Save)(THIS_ IStream *pStm, BOOL fClearDirty);
	STDMETHOD(GetSizeMax)(THIS_ ULARGE_INTEGER *pcbSize);
	STDMETHOD(InitNew) (THIS);
[!endif]

[!crlf]
private:
	SEnumLONG m_Objects;		// zu bearbeitende Objektmenge
[!if=(PropActHasUI, "TRUE")]
	[!DlgClassName] *m_pCfgDlg;	// Konfigurationsdialog
[!endif]
};

[!crlf]
[!if=(FileExists, "FALSE")]
#endif // !defined(__[!UpperShortName]_H_)
[!endif]
