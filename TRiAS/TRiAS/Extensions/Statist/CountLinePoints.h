// @doc 
// @module CountLinePoints.h | Declaration of the <c CCountLinePoints> class

#if !defined(_COUNTLINEPOINTS_H__A19D28F8_F022_11D2_9BE5_5AB320524153__INCLUDED_)
#define _COUNTLINEPOINTS_H__A19D28F8_F022_11D2_9BE5_5AB320524153__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"				// main symbols
#include <Com/ObjectPropertyBase.h>

/////////////////////////////////////////////////////////////////////////////
// CCountLinePoints
class ATL_NO_VTABLE CCountLinePoints : 
	public CComCoClass<CCountLinePoints, &CLSID_CountLinePoints>,
	public CObjectPropertyBase
{
public:
	CCountLinePoints() :
		CObjectPropertyBase(IDS_COUNTLINEPOINTS_NAME, IDS_COUNTLINEPOINTS_HELP)
	{
	}

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CCountLinePoints)
	DECLARE_NO_REGISTRY()

	DECLARE_PROTECT_FINAL_CONSTRUCT()
	HRESULT FinalConstruct()
	{
		return m_CumPts.LocalCreateInstance (CLSID_TRiASSimpleStatistics);
	}
	void FinalRelease()
	{
		m_CumPts.Assign (NULL);
	}

	BEGIN_COM_MAP(CCountLinePoints)
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

// IObjectProperty
public:
	STDMETHOD(Reset)(THIS);
	STDMETHOD(GetPropInfo) (THIS_ LPSTR pBuffer, WORD wLen, DWORD *pdwData);
	STDMETHOD(Cumulation)(THIS_ LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten);
	STDMETHOD(Eval)(THIS_ LONG lONr, LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten);

private:
	WTRiASSimpleStatistics m_CumPts;	// kumulierte Punktanzahl (Mittelwertberechnung)
};

#endif // !defined(_COUNTLINEPOINTS_H__A19D28F8_F022_11D2_9BE5_5AB320524153__INCLUDED_)
