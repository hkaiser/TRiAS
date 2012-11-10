// @doc 
// @module PointRefCoord.h |Declaration of the <c CPointRefCoord> class

#if !defined(_POINTREFCOORD_H__1E5FBF6B_F236_11D2_9BEB_0ECD20524153__INCLUDED_)
#define _POINTREFCOORD_H__1E5FBF6B_F236_11D2_9BEB_0ECD20524153__INCLUDED_

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
enum COORDTYPE {
	COORDTYPE_X = 0,
	COORDTYPE_Y = 1,
};

extern const UINT __declspec(selectany) g_uiPointNameIDs[] = 
{
	IDS_COORDX_NAME,	// COORDTYPE_X
	IDS_COORDY_NAME,	// COORDTYPE_Y
};

extern const UINT __declspec(selectany) g_uiPointHelpIDs[] = 
{
	IDS_POINTCOORDX_HELP,	// COORDTYPE_X
	IDS_POINTCOORDY_HELP,	// COORDTYPE_Y
};

/////////////////////////////////////////////////////////////////////////////
// CPointRefCoord
class ATL_NO_VTABLE CPointRefCoord : 
	public CObjectPropertyBase
{
protected:
	CPointRefCoord(COORDTYPE rgType) :
		CObjectPropertyBase(g_uiPointNameIDs[rgType], g_uiPointHelpIDs[rgType]),
		m_rgType(rgType)
	{
	// im Nachhinein den Wertebereich des Koordinatentyps testen
		_ASSERTE(COORDTYPE_X == m_rgType || COORDTYPE_Y == m_rgType);
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

	bool InitRealAreaPoint (LONG, double *, double *);


private:
	COORDTYPE m_rgType;
	WTRiASSimpleStatistics m_CumPts;	// kumulierte Punktanzahl (Mittelwertberechnung)
//	WCoordTransform m_pCT;

};

///////////////////////////////////////////////////////////////////////////////
// Rechtswert
class ATL_NO_VTABLE CPointRefCoordX : 
	public CComCoClass<CPointRefCoordX, &CLSID_PointCoordX>,
	public CPointRefCoord
{
public:
	CPointRefCoordX() :
		CPointRefCoord(COORDTYPE_X)
	{
	}

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CPointRefCoordX)
	DECLARE_NO_REGISTRY()

	DECLARE_PROTECT_FINAL_CONSTRUCT()


	BEGIN_COM_MAP(CPointRefCoordX)
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

///////////////////////////////////////////////////////////////////////////////
// Hochwert
class ATL_NO_VTABLE CPointRefCoordY : 
	public CComCoClass<CPointRefCoordY, &CLSID_PointCoordY>,
	public CPointRefCoord
{
public:
	CPointRefCoordY() :
		CPointRefCoord(COORDTYPE_Y)
	{
	}

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CPointRefCoordY)
	DECLARE_NO_REGISTRY()

	DECLARE_PROTECT_FINAL_CONSTRUCT()


	BEGIN_COM_MAP(CPointRefCoordY)
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

#endif // !defined(_POINTREFCOORD_H__1E5FBF6B_F236_11D2_9BEB_0ECD20524153__INCLUDED_)
