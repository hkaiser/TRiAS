// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 28.12.2000 17:40:09
//
// @doc
// @module MathOperationProperty.h | Declaration of the <c CMathOperationProperty> class

#if !defined(_MATHOPERATIONPROPERTY_H__302625D1_0D99_4B7C_A8E2_C2C5A99A3887__INCLUDED_)
#define _MATHOPERATIONPROPERTY_H__302625D1_0D99_4B7C_A8E2_C2C5A99A3887__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"       // main symbols
#include <Com/ObjectPropertyBase.h>

///////////////////////////////////////////////////////////////////////////////
// Objekteigenschaft CMathOperationProperty
enum MATHOPERATION {
	MATHOPERATION_Unknown = 0,
	MATHOPERATION_Add = 1,
	MATHOPERATION_Subtract = 2,
	MATHOPERATION_Mulitply = 3,
	MATHOPERATION_Divide = 4,
};

class ATL_NO_VTABLE CMathOperationProperty : 
	public CComCoClass<CMathOperationProperty, &CLSID_MathOperationProperty>,
	public IConfigObjectProperty,
	public CObjectPropertyBase
{
public:

	CMathOperationProperty() : 
		CObjectPropertyBase (IDS_OP_NAME_MATHOPERATIONPROPERTY, IDS_OP_DESCRIPTION_MATHOPERATIONPROPERTY),
		m_iObjTyp(OGUnknown), m_rgMathOp(MATHOPERATION_Unknown), m_fIsValid(false)
	{
	}

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

	BEGIN_COM_MAP(CMathOperationProperty)
	// der erste Eintrag in dieser Map muß ein 'einfacher' sein
		COM_INTERFACE_ENTRY(IObjectProperty)
		COM_INTERFACE_ENTRY(IConfigObjectProperty)

	// alles andere macht die Basisklasse
		COM_INTERFACE_ENTRY_CHAIN(CObjectPropertyBase)
	END_COM_MAP()

// IPersist methods
	STDMETHOD(GetClassID)(THIS_ CLSID *pClsID);

// IPersistStream methods
	STDMETHOD(Load)(THIS_ IStream *pStm);
	STDMETHOD(Save)(THIS_ IStream *pStm, BOOL fClearDirty);
	STDMETHOD(GetSizeMax)(THIS_ ULARGE_INTEGER * pcbSize);

// IPersistStreamInit methods
	STDMETHOD(InitNew)(THIS);

// IConfigObjectProperty
	STDMETHOD(ConfigObjectProperty) (THIS_ HWND hWndParent);
	STDMETHOD(get_IsConfigured) (VARIANT_BOOL *pfConfigState);

// IObjectProperty
public:
	STDMETHOD(Reset)(THIS);
	STDMETHOD(GetPropInfo) (THIS_ LPSTR pBuffer, WORD wLen, DWORD *pdwData);
	STDMETHOD(Cumulation)(THIS_ LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten);
	STDMETHOD(Eval)(THIS_ LONG lONr, LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten);

protected:
	HRESULT GetObjectProperty (LPCSTR pcName, IObjectProperty **ppIObjProp);
	HRESULT GetObjectPropertyName (IObjectProperty *pIObjProp, os_string &rStrName);

private:
	WTRiASSimpleStatistics m_CumPts;

	WObjectProperty m_ObjProp1;
	WObjectProperty m_ObjProp2;
	int m_iObjTyp;
	MATHOPERATION m_rgMathOp;

	bool m_fIsValid;		// gültige Operation
};

#endif // !defined(_MATHOPERATIONPROPERTY_H__302625D1_0D99_4B7C_A8E2_C2C5A99A3887__INCLUDED_)
