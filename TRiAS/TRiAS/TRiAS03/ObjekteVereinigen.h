// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 09/23/1998 07:17:43 PM
//
// @doc
// @module ObjekteVereinigen.h | Declaration of the <c CObjekteVereinigen> class

#if !defined(_OBJEKTEVEREINIGEN_H__D32D1683_5308_11D2_9ECC_006008447800__INCLUDED_)
#define _OBJEKTEVEREINIGEN_H__D32D1683_5308_11D2_9ECC_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <registry.hxx>

#include <Com/PropertyActionBase.h>

#include "trias03.h"       // main symbols
#include "Strings.h"

#if _TRiAS_VER < 0x0400
// schon mal TRiAS V4 vorbereiten
extern DWORD g_dwVer4;
#endif // _TRiAS_VER < 0x0400

/////////////////////////////////////////////////////////////////////////////
// SmartIF's
#if !defined(_INITSCRIPTPROPACT_SMARTIF)
#define _INITSCRIPTPROPACT_SMARTIF
DefineSmartInterface(InitScriptPropAct);	// WInitScriptPropAct
#endif // _INITSCRIPTPROPACT_SMARTIF

class CObjekteVereinigenDlg;

/////////////////////////////////////////////////////////////////////////////
// CObjekteVereinigen
class ATL_NO_VTABLE CObjekteVereinigenEx : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CPropertyActionImpl,
	public CComCoClass<CObjekteVereinigenEx, &CLSID_ObjekteVereinigenEx>
{
public:
	enum { 
		PA_TYPEFLAGS = 
			PROPCAPS_ACTION_SINK |
			PROPCAPS_ACTION_SOURCE |
			PROPCAPS_ACTION_MUSTREPAINT
	};

	CObjekteVereinigenEx() 
	:	CPropertyActionImpl(PA_TYPEFLAGS, IDS_OBJEKTEVEREINIGEN),
		m_fDeleteObjs(true), m_fMarkObjs(false), m_fCopyObjs(true), 
		m_pCfgDlg(NULL)
	{
	}
	~CObjekteVereinigenEx();

#if _TRiAS_VER >= 0x0400
	DECLARE_STATIC_REGISTRY_RESOURCEID(IDR_OBJEKTEVEREINIGEN)
#else
	static HRESULT WINAPI UpdateRegistry(BOOL bRegister);
#endif // _TRiAS_VER >= 0x0400

	DECLARE_NOT_AGGREGATABLE(CObjekteVereinigenEx)
	DECLARE_GET_CONTROLLING_UNKNOWN()
	
	BEGIN_COM_MAP(CObjekteVereinigenEx)
		COM_INTERFACE_ENTRY(IPropertyAction3)
		COM_INTERFACE_ENTRY(IPropertyAction2)
		COM_INTERFACE_ENTRY(IPropertyAction)
		COM_INTERFACE_ENTRY(IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersistStream, IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
		COM_INTERFACE_ENTRY(IPersistPropertyBag)
		COM_INTERFACE_ENTRY_AGGREGATE_BLIND(m_BaseUnk.p)
	END_COM_MAP()

	BEGIN_CATEGORY_MAP(CObjekteVereinigenEx)
		IMPLEMENTED_CATEGORY(CATID_TRiASGeoComponent)
	END_CATEGORY_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()
	HRESULT FinalConstruct()
	{
		RETURN_FAILED_HRESULT(m_BaseUnk.CreateInstance (CLSID_ScriptPropAct, CLSCTX_INPROC_SERVER, GetControllingUnknown()));

	UINT uiResID = IDR_SCRIPT_UNIONOBJECTS_OPT;

#if _TRiAS_VER < 0x0400
	// das derzeitige TRiAS sollte den alten Script nutzen
		if (0 == g_dwVer4)
			uiResID = IDR_SCRIPT_UNIONOBJECTS;
#endif // _TRiAS_VER < 0x0400

	WInitScriptPropAct BaseObj;

		RETURN_FAILED_HRESULT(m_BaseUnk -> QueryInterface (IID_IInitScriptPropAct, BaseObj.ppv()));
		RETURN_FAILED_HRESULT(BaseObj -> InitScript(CComBSTR(g_cbObjekteVereinigen), (INT_PTR)_Module.GetModuleInstance(), uiResID));
		return S_OK;
	}
	void FinalRelease()
	{
		m_BaseUnk.Assign(NULL);
	}

// IPropertyAction 
	STDMETHOD(BeginAction) (THIS_ IProgressIndicator *pIProgInd);
	STDMETHOD(DoAction) (THIS_ IDataObject *pEnumObj, DWORD dwReserved);
	STDMETHOD(EndAction) (THIS_ DWORD dwReserved, IDataObject **ppEnumObj);

// Geokomponente hat eigenen Dialog
	STDMETHOD(PreConfigPages)(THIS_ IDataObject *pIDataObject, DWORD dwFlags);
	STDMETHOD(AddConfigPages)(THIS_ LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam, LPCSTR pcDesc, UINT *puiCnt);

// IPersist
	STDMETHOD(GetClassID) (THIS_ CLSID *pClsID);
	STDMETHOD(IsDirty) (THIS);
	STDMETHOD(Load)(THIS_ IStream *pStm);
	STDMETHOD(Save)(THIS_ IStream *pStm, BOOL fClearDirty);
	STDMETHOD(GetSizeMax)(THIS_ ULARGE_INTEGER *pcbSize);
	STDMETHOD(InitNew) (THIS);

// IPersistPropertyBag
	STDMETHOD(Load)(THIS_ IPropertyBag *pBag, IErrorLog *pLog);

protected:
	HRESULT InitBool (IExtendBScript *pBasic, LPCSTR pcName, VARIANT_BOOL fFlag);

private:
	WUnknown m_BaseUnk;		// aggregierte Klasse

	bool m_fDeleteObjs;
	bool m_fMarkObjs;
	bool m_fCopyObjs;

	CObjekteVereinigenDlg *m_pCfgDlg;
};

#endif // !defined(_OBJEKTEVEREINIGEN_H__D32D1683_5308_11D2_9ECC_006008447800__INCLUDED_)
