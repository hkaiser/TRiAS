// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 28.12.2000 17:49:55 
//
// @doc
// @module ObjektContainer.h | Declaration of the <c CObjektContainer> class

#if !defined(_OBJEKTCONTAINER_H__3A1030AC_94F2_4330_914D_382DE0A0F2E9__INCLUDED_)
#define _OBJEKTCONTAINER_H__3A1030AC_94F2_4330_914D_382DE0A0F2E9__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"       // main symbols
#include <Com/ObjectPropertyBase.h>

/////////////////////////////////////////////////////////////////////////////
//
enum CONTAINERTYPE {
	CONTYPE_XMIN = 0,
	CONTYPE_XMAX = 1,
	CONTYPE_YMIN = 2,
	CONTYPE_YMAX = 3,
};

extern const UINT __declspec(selectany) g_uiContNameIDs[] = 
{
	IDS_CONTAINERMINX_NAME,	// _Xmin
	IDS_CONTAINERMAXX_NAME,	// _Xmax
	IDS_CONTAINERMINY_NAME,	// _Ymin
	IDS_CONTAINERMAXY_NAME,	// _Ymax
};

extern const UINT __declspec(selectany) g_uiContHelpIDs[] = 
{
	IDS_CONTAINERMINX_HELP,	// _Xmin
	IDS_CONTAINERMAXX_HELP,	// _Xmax
	IDS_CONTAINERMINY_HELP,	// _Ymin
	IDS_CONTAINERMAXY_HELP,	// _Ymax
};

///////////////////////////////////////////////////////////////////////////////
// Objekteigenschaft CObjektContainer
class ATL_NO_VTABLE CObjektContainer : 
	public CObjectPropertyBase
{
protected:
	CObjektContainer(CONTAINERTYPE rgType) :
		CObjectPropertyBase(g_uiContNameIDs[rgType], g_uiContHelpIDs[rgType]),
		m_rgType(rgType)
	{
	// im Nachhinein den Wertebereich des Koordinatentyps testen
		_ASSERTE(CONTYPE_XMIN == m_rgType || CONTYPE_XMAX == m_rgType || CONTYPE_YMIN == m_rgType || CONTYPE_YMAX == m_rgType);
	}

public:

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return m_CumPts.LocalCreateInstance (CLSID_TRiASSimpleStatistics);
	}

	void FinalRelease()
	{
		m_CumPts.Assign (NULL);
	}

// IObjectProperty
public:
	STDMETHOD(Reset)(THIS);
	STDMETHOD(GetPropInfo) (THIS_ LPSTR pBuffer, WORD wLen, DWORD *pdwData);
	STDMETHOD(Cumulation)(THIS_ LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten);
	STDMETHOD(Eval)(THIS_ LONG lONr, LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten);

private:
	CONTAINERTYPE  m_rgType;
	WTRiASSimpleStatistics m_CumPts;	// kumulierte Punktanzahl (Mittelwertberechnung)
};

///////////////////////////////////////////////////////////////////////////////
// Objekteigenschaft CObjContainerXMin
class ATL_NO_VTABLE CObjContainerXMin : 
	public CComCoClass<CObjContainerXMin, &CLSID_ObjContainerXMin>,
	public CObjektContainer
{
public:
	CObjContainerXMin() : 
		CObjektContainer (CONTYPE_XMIN)
	{
	}

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CObjContainerXMin)

	DECLARE_NO_REGISTRY()
	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CObjContainerXMin)
	// der erste Eintrag in dieser Map muß ein 'einfacher' sein
		COM_INTERFACE_ENTRY(IObjectProperty)

	// die folgenden werden hier nicht unterstützt 
		COM_INTERFACE_ENTRY_NOINTERFACE(IPersistStreamInit)
		COM_INTERFACE_ENTRY_NOINTERFACE(IPersistStream)
		COM_INTERFACE_ENTRY_NOINTERFACE(IPersist)

	// alles andere macht die Basisklasse
		COM_INTERFACE_ENTRY_CHAIN(CObjectPropertyBase)
	END_COM_MAP()
};

///////////////////////////////////////////////////////////////////////////////
// Objekteigenschaft CObjContainerXMax
class ATL_NO_VTABLE CObjContainerXMax : 
	public CComCoClass<CObjContainerXMax, &CLSID_ObjContainerXMax>,
	public CObjektContainer
{
public:
	CObjContainerXMax() : 
		CObjektContainer (CONTYPE_XMAX)
	{
	}

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CObjContainerXMax)

	DECLARE_NO_REGISTRY()
	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CObjContainerXMax)
	// der erste Eintrag in dieser Map muß ein 'einfacher' sein
		COM_INTERFACE_ENTRY(IObjectProperty)

	// die folgenden werden hier nicht unterstützt 
		COM_INTERFACE_ENTRY_NOINTERFACE(IPersistStreamInit)
		COM_INTERFACE_ENTRY_NOINTERFACE(IPersistStream)
		COM_INTERFACE_ENTRY_NOINTERFACE(IPersist)

	// alles andere macht die Basisklasse
		COM_INTERFACE_ENTRY_CHAIN(CObjectPropertyBase)
	END_COM_MAP()
};

///////////////////////////////////////////////////////////////////////////////
// Objekteigenschaft CObjContainerYMin
class ATL_NO_VTABLE CObjContainerYMin : 
	public CComCoClass<CObjContainerYMin, &CLSID_ObjContainerYMin>,
	public CObjektContainer
{
public:
	CObjContainerYMin() : 
		CObjektContainer (CONTYPE_YMIN)
	{
	}

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CObjContainerYMin)

	DECLARE_NO_REGISTRY()
	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CObjContainerYMin)
	// der erste Eintrag in dieser Map muß ein 'einfacher' sein
		COM_INTERFACE_ENTRY(IObjectProperty)

	// die folgenden werden hier nicht unterstützt 
		COM_INTERFACE_ENTRY_NOINTERFACE(IPersistStreamInit)
		COM_INTERFACE_ENTRY_NOINTERFACE(IPersistStream)
		COM_INTERFACE_ENTRY_NOINTERFACE(IPersist)

	// alles andere macht die Basisklasse
		COM_INTERFACE_ENTRY_CHAIN(CObjectPropertyBase)
	END_COM_MAP()
};

///////////////////////////////////////////////////////////////////////////////
// Objekteigenschaft CObjContainerYMax
class ATL_NO_VTABLE CObjContainerYMax : 
	public CComCoClass<CObjContainerYMax, &CLSID_ObjContainerYMax>,
	public CObjektContainer
{
public:
	CObjContainerYMax() : 
		CObjektContainer (CONTYPE_YMAX)
	{
	}

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CObjContainerYMax)

	DECLARE_NO_REGISTRY()
	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CObjContainerYMax)
	// der erste Eintrag in dieser Map muß ein 'einfacher' sein
		COM_INTERFACE_ENTRY(IObjectProperty)

	// die folgenden werden hier nicht unterstützt 
		COM_INTERFACE_ENTRY_NOINTERFACE(IPersistStreamInit)
		COM_INTERFACE_ENTRY_NOINTERFACE(IPersistStream)
		COM_INTERFACE_ENTRY_NOINTERFACE(IPersist)

	// alles andere macht die Basisklasse
		COM_INTERFACE_ENTRY_CHAIN(CObjectPropertyBase)
	END_COM_MAP()
};

#endif // !defined(_OBJEKTCONTAINER_H__3A1030AC_94F2_4330_914D_382DE0A0F2E9__INCLUDED_)
