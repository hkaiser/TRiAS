// $Header: /TRiAS/TRiAS/TRiAS03/GenTextPropAct.h 3     4.06.98 9:51 Hartmut Kaiser $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 06/01/1998 06:53:15 PM
//
// @doc
// @module GenTextPropAct.h | Declaration of the <c CGenTextPropAct> class

#if !defined(_GENTEXTPROPACT_H__DEF044D3_F96E_11D1_8639_00600875138A__INCLUDED_)
#define _GENTEXTPROPACT_H__DEF044D3_F96E_11D1_8639_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "propactb.hxx"
#include "gentguid.h"
#include "GenTextDlg.h"

class CGenTextPropAct : 
	public CPropertyActionExt,	// JG 980914
	public CComObjectRoot,
	public IObjectWithSiteImpl<CGenTextPropAct>,
	public CComCoClass<CGenTextPropAct, &CLSID_GenTextPropAct>
{
public:
		CGenTextPropAct();
		~CGenTextPropAct();

	BEGIN_COM_MAP(CGenTextPropAct)
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

	DECLARE_AGGREGATABLE(CGenTextPropAct)
	DECLARE_STATIC_REGISTRY_RESOURCEID(IDR_GENTEXTPROPACT)

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

private:
	bool m_fIsDirty;
	bool m_fIsInitialized;
	string m_strDesc;

	CGenTextDlg *m_pCfgDlg;
	CGenTextDlg::CDlgStatus m_Status;

	HPROJECT m_hPr;		// Zieldatenquelle
};

#endif // !defined(_GENTEXTPROPACT_H__DEF044D3_F96E_11D1_8639_00600875138A__INCLUDED_)
