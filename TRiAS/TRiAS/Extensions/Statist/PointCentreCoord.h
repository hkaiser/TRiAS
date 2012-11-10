// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
//
// @doc
// @module PointCentreCoord.h | Declaration of the <c CPointCentreCoord> class

#if !defined(__POINTCENTRECOORD_H_)
#define __POINTCENTRECOORD_H_

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
enum COORDCENTRETYPE {
	COORDCENTRETYPE_X = 0,
	COORDCENTRETYPE_Y = 1,
};

extern const UINT __declspec(selectany) g_uiCPointNameIDs[] = 
{
	IDS_COORDCENTREX_NAME,	// COORDTYPE_X
	IDS_COORDCENTREY_NAME,	// COORDTYPE_Y
};

extern const UINT __declspec(selectany) g_uiCPointHelpIDs[] = 
{
	IDS_CENTRECOORDX_HELP,	// COORDTYPE_X
	IDS_CENTRECOORDY_HELP,	// COORDTYPE_Y
};

/////////////////////////////////////////////////////////////////////////////


// CPointCentreCoord
class ATL_NO_VTABLE CPointCentreCoord : 
	public CObjectPropertyBase
{

protected:
	CPointCentreCoord(COORDCENTRETYPE rgType) :
		CObjectPropertyBase(g_uiCPointNameIDs[rgType], g_uiCPointHelpIDs[rgType]),
		m_rgType(rgType)
	{
	// im Nachhinein den Wertebereich des Koordinatentyps testen
		_ASSERTE(COORDCENTRETYPE_X == m_rgType || COORDCENTRETYPE_Y == m_rgType);
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
	COORDCENTRETYPE m_rgType;

private:
	WTRiASSimpleStatistics m_CumPts;	// kumulierte Punktanzahl (Mittelwertberechnung)

};

///////////////////////////////////////////////////////////////////////////////
// Rechtswert
class ATL_NO_VTABLE CPointCentreCoordX : 
	public CComCoClass<CPointCentreCoordX, &CLSID_PointCentreCoordX>,
	public CPointCentreCoord
{
public:

	CPointCentreCoordX() : 
		CPointCentreCoord (COORDCENTRETYPE_X)
	{
	}

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CPointCentreCoordX)
	DECLARE_NO_REGISTRY()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CPointCentreCoordX)
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
// Hochwert
class ATL_NO_VTABLE CPointCentreCoordY : 
	public CComCoClass<CPointCentreCoordY, &CLSID_PointCentreCoordY>,
	public CPointCentreCoord
{
public:
	CPointCentreCoordY() :
		CPointCentreCoord(COORDCENTRETYPE_Y)
	{
	}

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CPointCentreCoordY)
	DECLARE_NO_REGISTRY()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CPointCentreCoordY)
	// der erste Eintrag in dieser Map muß ein 'einfacher' sein
		COM_INTERFACE_ENTRY(IObjectProperty)
	//
	// die folgenden werden hier nicht unterstützt (s. DECLARE_NO_REGISTRY)
		COM_INTERFACE_ENTRY_NOINTERFACE(IPersistStreamInit)
		COM_INTERFACE_ENTRY_NOINTERFACE(IPersistStream)
		COM_INTERFACE_ENTRY_NOINTERFACE(IPersist)
	//
	// alles andere macht die Basisklasse
		COM_INTERFACE_ENTRY_CHAIN(CObjectPropertyBase)
	END_COM_MAP()
};


#endif // !defined(__POINTCENTRECOORD_H_)
