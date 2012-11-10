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
#include <Com/ObjectPropertyBase.h>
[!else]
[!AddIncludeFile(TargetFile, "resource.h")]
[!AddIncludeFile(TargetFile, "Com/ObjectPropertyBase.h")]
[!endif]

[!crlf]
///////////////////////////////////////////////////////////////////////////////
// Objekteigenschaft [!ClassName]
class ATL_NO_VTABLE [!ClassName] : 
	public CComCoClass<[!ClassName], &CLSID_[!CoClassName]>,
	public CObjectPropertyBase
{
public:
[!crlf]
	[!ClassName]() : 
		CObjectPropertyBase ([!IDS_OP_NAME], [!IDS_OP_DESCRIPTION])
	{
[!if=(ObjPropWritable, "TRUE")]
		CObjectPropertyBase::SetRO (false);		// Objekteigenschaft ist beschreibbar
[!endif]
[!if=(FreeThreadedMarshaler, "TRUE")]
		m_pUnkMarshaler = NULL;
[!endif]
	}

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
	// der erste Eintrag in dieser Map muß ein 'einfacher' sein
		COM_INTERFACE_ENTRY(IObjectProperty)

[!if=(IPERSISTSTREAMINIT, "FALSE")]
[!crlf]
	// die folgenden werden hier nicht unterstützt 
		COM_INTERFACE_ENTRY_NOINTERFACE(IPersistStreamInit)
		COM_INTERFACE_ENTRY_NOINTERFACE(IPersistStream)
		COM_INTERFACE_ENTRY_NOINTERFACE(IPersist)
[!endif]

[!crlf]
	// alles andere macht die Basisklasse
		COM_INTERFACE_ENTRY_CHAIN(CObjectPropertyBase)
	END_COM_MAP()

[!if=(IPERSISTSTREAMINIT, "TRUE")]
[!crlf]
// IPersist methods
	STDMETHOD(GetClassID)(THIS_ CLSID *pClsID);

[!crlf]
// IPersistStream methods
	STDMETHOD(Load)(THIS_ IStream *pStm);
	STDMETHOD(Save)(THIS_ IStream *pStm, BOOL fClearDirty);
	STDMETHOD(GetSizeMax)(THIS_ ULARGE_INTEGER * pcbSize);

[!crlf]
// IPersistStreamInit methods
	STDMETHOD(InitNew)(THIS);
[!endif]

[!crlf]
// IObjectProperty
public:
	STDMETHOD(Reset)(THIS);
	STDMETHOD(GetPropInfo) (THIS_ LPSTR pBuffer, WORD wLen, DWORD *pdwData);
	STDMETHOD(Cumulation)(THIS_ LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten);
	STDMETHOD(Eval)(THIS_ LONG lONr, LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten);

[!if=(ObjPropWritable, "TRUE")]
[!crlf]
// Objekteigenschaft ist beschreibbar
	STDMETHOD(Set)(THIS_ LONG lONr, LPCSTR pcBuffer);
[!endif]
};

[!crlf]
[!if=(FileExists, "FALSE")]
#endif // !defined(__[!UpperShortName]_H_)
[!endif]
