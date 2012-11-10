// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 09/07/1998 02:51:30 PM
//
// @doc
// @module ScriptPropAct.h | Declaration of the <c CScriptPropAct> class

#if !defined(_SCRIPTPROPACT_H__B7368639_45BF_11D2_9EBE_006008447800__INCLUDED_)
#define _SCRIPTPROPACT_H__B7368639_45BF_11D2_9EBE_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <ospace/std/string>
#include <ospace/std/list>
#include <ospace/com/iterenum.h>

#include <eb.h>
#include <ibscript.hxx>
#include <TRiASHelper.h>
#include <basetsd.h>

#include "propactb.hxx"

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(ExtendBScript);

///////////////////////////////////////////////////////////////////////////////
//
class CScriptPropAct : 
	public CPropertyAction,
	public CComObjectRoot,
	public IInitScriptPropAct,
	public IObjectWithSiteImpl<CScriptPropAct>,
	public CComCoClass<CScriptPropAct, &CLSID_ScriptPropAct>
{
public:
		CScriptPropAct();
		~CScriptPropAct();

	BEGIN_COM_MAP(CScriptPropAct)
		COM_INTERFACE_ENTRY(IInitScriptPropAct)
		COM_INTERFACE_ENTRY(IPropertyAction)
		COM_INTERFACE_ENTRY(IPropertyAction2)
		COM_INTERFACE_ENTRY(IPropertyAction3)
		COM_INTERFACE_ENTRY(IClassProperty)
		COM_INTERFACE_ENTRY(IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersistStream, IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
		COM_INTERFACE_ENTRY(IPersistPropertyBag)
		COM_INTERFACE_ENTRY(IPropertyInfo)
		COM_INTERFACE_ENTRY(IObjectWithSite)
	END_COM_MAP()

	DECLARE_ONLY_AGGREGATABLE(CScriptPropAct)	// muﬂ aggregiert werden
	DECLARE_STATIC_REGISTRY_RESOURCEID(IDR_SCRIPTPROPACT)

public:
	void SetDirty (bool fFlag = true);

public:
// IPropertyAction methods
	STDMETHOD (AddConfigPages) (LPFNADDPROPSHEETPAGE lpfnAddPage, 
								LPARAM lParam, LPCSTR pcDesc, UINT *puiCnt);
	STDMETHOD (PreConfigPages) (IDataObject *pIDataObject, DWORD dwFlags);
	STDMETHOD (BeginAction) (THIS_ IProgressIndicator *pIProgInd);
	STDMETHOD (DoAction) (IDataObject *pEnumObj, DWORD dwReserved);
	STDMETHOD (EndAction) (DWORD dwReserved, IDataObject **ppEnumObj);

// IClassProperty specific functions
	STDMETHOD(GetPropInfo) (LPSTR pBuffer, WORD wLen, DWORD *pdwFlags);
	STDMETHOD(HelpInfo) (LPSTR pBuffer, ULONG wLen, LPSTR pHelpFile, ULONG *pulHelpCtx);

// IPropertyInfo specific functions 
	STDMETHOD(SetPropInfo) (THIS_ LPCSTR pBuffer, DWORD dwFlags);

// IPersist methods
	STDMETHOD(GetClassID) (CLSID *pClsID);

// IPersistStreamInit methods
	STDMETHOD(IsDirty)(void);
	STDMETHOD(Load)(LPSTREAM pStm);
	STDMETHOD(Save)(LPSTREAM pStm, BOOL fClearDirty);
	STDMETHOD(GetSizeMax)(THIS_ ULARGE_INTEGER FAR* pcbSize);
	STDMETHOD(InitNew)(void);

// IPersistPropertyBag
	STDMETHOD(Load)(THIS_ IPropertyBag *pBag, IErrorLog *pLog);

// IInitScriptPropAct
	STDMETHOD(InitScript) (THIS_ BSTR bstrScript, INT_PTR hInst, UINT uiResID);
	STDMETHOD(GetScriptEngine) (THIS_ REFIID riid, IUnknown **ppIUnk);

public:
	class CScriptPropActStatus {
	public:
		CComBSTR m_bstrDesc;
		CComBSTR m_bstrHelpDesc;
		CComBSTR m_bstrDataSource;
		DWORD m_dwPropFlags;

		void erase (void) 
		{ 
			m_dwPropFlags = PROPCAPS_ACTION_SINK_MULTI|PROPCAPS_ACTION_SOURCE_MULTI|PROPCAPS_ACTION_MUSTREPAINT;
		}
		CScriptPropActStatus (void) { erase(); }
	};
	typedef list<WEnumLONG> COutObjs;

protected:
	HRESULT CleanUpScript (void);

private:
	bool m_fIsDirty;
	bool m_fIsInitialized;
	os_string m_strDesc;
	os_string m_strHelpDesc;

	CScriptPropActStatus m_Status;	// data to persist
	COutObjs m_OutObjs;
	COutObjs::iterator m_ObjsIter;
	WExtendBScript m_BScript;

	HINSTANCE m_hInst;
	UINT m_uiIDScript;				// ResID des zu startenden Scriptes
	os_string m_strScript;			// Name des Scriptes
};

#endif // !defined(_SCRIPTPROPACT_H__B7368639_45BF_11D2_9EBE_006008447800__INCLUDED_)
