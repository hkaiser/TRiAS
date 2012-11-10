// $Header: $
// Copyright© 1999 TRiAS GmbH, All rights reserved
// Created: 09/23/1998 07:17:43 PM
//
// @doc
// @module ObjekteVereinigen.h | Declaration of the <c CObjekteVereinigen> class

#if !defined(_OBJEKTEVEREINIGEN_H__D32D1683_5308_11D2_9ECC_006008447800__INCLUDED_)
#define _OBJEKTEVEREINIGEN_H__D32D1683_5308_11D2_9ECC_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


#include <TRiASHelper_i.c>		// IID_IInitScriptPropAct, ...
#include <TRiASHelper.h>		// IInitScriptPropAct



/////////////////////////////////////////////////////////////////////////////
// SmartIF's
#if !defined(_INITSCRIPTPROPACT_SMARTIF)
#define _INITSCRIPTPROPACT_SMARTIF
DefineSmartInterface(InitScriptPropAct);	// WInitScriptPropAct
#endif // _INITSCRIPTPROPACT_SMARTIF

/////////////////////////////////////////////////////////////////////////////
// CObjekteVereinigen
class ATL_NO_VTABLE CObjekteVereinigen : 
	public CComObjectRoot,
	public IUnknown,
	public CComCoClass<CObjekteVereinigen, &CLSID_ObjekteVereinigen>
{
public:
	CObjekteVereinigen()
	{
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_OBJEKTEVEREINIGEN)
	DECLARE_NOT_AGGREGATABLE(CObjekteVereinigen)

	BEGIN_COM_MAP(CObjekteVereinigen)
		COM_INTERFACE_ENTRY(IUnknown)
		COM_INTERFACE_ENTRY_AGGREGATE_BLIND(m_BaseUnk.p)
	END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()
	DECLARE_GET_CONTROLLING_UNKNOWN()
	HRESULT FinalConstruct()
	{
		RETURN_FAILED_HRESULT(m_BaseUnk.CreateInstance (CLSID_ScriptPropAct, CLSCTX_INPROC_SERVER, GetControllingUnknown()));

	WInitScriptPropAct BaseObj;

		RETURN_FAILED_HRESULT(m_BaseUnk->QueryInterface (IID_IInitScriptPropAct, BaseObj.ppv()));
		return BaseObj->InitScript(CComBSTR("ObjekteVereinigen"), (INT_PTR)_Module.GetModuleInstance(), IDR_SCRIPT_BLINKEL);
	}

protected:
	void FinalRelease()
	{
		m_BaseUnk.Assign(NULL);
	}

//public:

private:
	WUnknown m_BaseUnk;		// aggregierte Klasse
};

#endif // !defined(_OBJEKTEVEREINIGEN_H__D32D1683_5308_11D2_9ECC_006008447800__INCLUDED_)
