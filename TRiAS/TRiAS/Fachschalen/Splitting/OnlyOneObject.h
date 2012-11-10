// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 09/12/1998 09:20:50 PM
//
// @doc
// @module OnlyOneObject.h | Declaration of the <c COnlyOneObject> class

#if !defined(_ONLYONEOBJECT_H__E3C50CA4_4A48_11D2_9EC2_006008447800__INCLUDED_)
#define _ONLYONEOBJECT_H__E3C50CA4_4A48_11D2_9EC2_006008447800__INCLUDED_



#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//#include "Strings.h"


#if _MSC_VER < 1100
#define ATL_NO_VTABLE
#endif // _MSC_VER < 1100


//#include "trias03.h"       // main symbols


/////////////////////////////////////////////////////////////////////////////
// SmartIF's
#if !defined(_INITSCRIPTPROPACT_SMARTIF)
#define _INITSCRIPTPROPACT_SMARTIF
DefineSmartInterface(InitScriptPropAct);	// WInitScriptPropAct
#endif // _INITSCRIPTPROPACT_SMARTIF

/////////////////////////////////////////////////////////////////////////////
// COnlyOneObject
class ATL_NO_VTABLE COnlyOneObject : 
	public CComObjectRoot,
	public IUnknown,
	public CComCoClass<COnlyOneObject, &CLSID_OnlyOneObject>
{
public:
	COnlyOneObject()
	{
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_ONLYONEOBJECT)	// *.rgs
	DECLARE_NOT_AGGREGATABLE(COnlyOneObject)

	BEGIN_COM_MAP(COnlyOneObject)
		COM_INTERFACE_ENTRY(IUnknown)
		COM_INTERFACE_ENTRY_AGGREGATE(IID_IPropertyAction, m_BaseUnk.p)
		COM_INTERFACE_ENTRY_AGGREGATE(IID_IPropertyAction2, m_BaseUnk.p)
		COM_INTERFACE_ENTRY_AGGREGATE(IID_IClassProperty, m_BaseUnk.p)
		COM_INTERFACE_ENTRY_AGGREGATE(IID_IPersistStreamInit, m_BaseUnk.p)
		COM_INTERFACE_ENTRY_AGGREGATE(IID_IPersistStream, m_BaseUnk.p)
		COM_INTERFACE_ENTRY_AGGREGATE(IID_IPersist, m_BaseUnk.p)
		COM_INTERFACE_ENTRY_AGGREGATE(IID_IPersistPropertyBag, m_BaseUnk.p)
		COM_INTERFACE_ENTRY_AGGREGATE(IID_IPropertyInfo, m_BaseUnk.p)
	END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()
	DECLARE_GET_CONTROLLING_UNKNOWN()
	//
	HRESULT FinalConstruct()
	{
		RETURN_FAILED_HRESULT(m_BaseUnk.CreateInstance (CLSID_ScriptPropAct, CLSCTX_INPROC_SERVER, GetControllingUnknown()));

	WInitScriptPropAct BaseObj;

		RETURN_FAILED_HRESULT(m_BaseUnk -> QueryInterface (IID_IInitScriptPropAct, BaseObj.ppv()));
		return BaseObj -> InitScript(CComBSTR("OnlyOneObject"), (INT_PTR)_Module.GetModuleInstance(), IDR_SCRIPT_ONLYONEOBJECT);
	}
	void FinalRelease()
	{
		m_BaseUnk.Assign(NULL);
	}

public:

private:
	WUnknown m_BaseUnk;		// aggregierte Klasse
};

#endif // !defined(_ONLYONEOBJECT_H__E3C50CA4_4A48_11D2_9EC2_006008447800__INCLUDED_)
