///////////////////////////////////////////////////////////////////////////
// @doc 
// @module ViewRecordsetGenerator.h | Declaration of the <c CViewRecordsetGenerator>
// class

#if !defined(_VIEWRECORDSETGENERATOR_H__04F82133_B7EA_11D1_85B4_00600875138A__INCLUDED_)
#define _VIEWRECORDSETGENERATOR_H__04F82133_B7EA_11D1_85B4_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "TRiASGMR.h"       // main symbols

#include <DGMAddFieldsPipe.h>		// IFieldProviderCallback
#include <DGMBaseTable.h>			// IBaseTableCallback

#include <NativeView.h>

using namespace trias_nativeview;

/////////////////////////////////////////////////////////////////////////////
// SmartIF's
#if !defined(_RECORDSETGENERATOR_H__7417A5E5_AED0_11D1_859A_00600875138A__INCLUDED_)
DefineSmartInterfaceEx2(DGMAddFieldsPipe, IID_DGMAddFieldsPipe);
DefineSmartInterface2(DGMBaseTable, IID_DGMBaseTable);
DefineSmartInterface(TRiASSourceInfo);
#endif // !defined(_RECORDSETGENERATOR_H__7417A5E5_AED0_11D1_859A_00600875138A__INCLUDED_)

///////////////////////////////////////////////////////////////////////////////
// Helperklasse
class CIdentObjTyp
{
private:
	long m_lIdent;
	CNativeView::VisType m_rgType;

public:
	CIdentObjTyp (void)
		: m_lIdent(0), m_rgType(CNativeView::VT_Default)
	{
	}
	CIdentObjTyp (long lIdent, CNativeView::VisType dwType)
		: m_lIdent(lIdent), m_rgType(dwType)
	{
	}

	long GetIdent() { return m_lIdent; }
	CNativeView::VisType GetType() { return m_rgType; }
};

/////////////////////////////////////////////////////////////////////////////
// CViewRecordsetGenerator
class ATL_NO_VTABLE CViewRecordsetGenerator : 
	public CComObjectRootEx<CComObjectThreadModel>, 
	public CComCoClass<CViewRecordsetGenerator, &CLSID_OKSRecordsetGenerator>,
	public IFieldProviderCallback,
	public IBaseTableCallback,
	public IRecordsetGenerator
{
public:
	CViewRecordsetGenerator()
	{
		m_iIdBase = 16;
	}

	DECLARE_NOT_AGGREGATABLE(CViewRecordsetGenerator)
	DECLARE_REGISTRY_RESOURCEID(IDR_VIEWRECORDSETGENERATOR)
	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CViewRecordsetGenerator)
		COM_INTERFACE_ENTRY(IRecordsetGenerator)
		COM_INTERFACE_ENTRY(IBaseTableCallback)
		COM_INTERFACE_ENTRY(IFieldProviderCallback)
	END_COM_MAP()

	HRESULT FinalConstruct();
	void FinalRelease();

// IRecordsetGenerator
public:
	STDMETHOD(GetOutputRecordset)(GRecordset** ppOutputRecordset);
	STDMETHOD(SetFeatureName)(THIS_ BSTR bsFeatureName);
	STDMETHOD(SetSourceInfo)(THIS_ VARIANT vSourceInfo);

// IBaseTableCallback
	STDMETHOD(AtEOF)(THIS);
	STDMETHOD(RowDeleted)(THIS);

// IFieldProviderCallback
	STDMETHOD(SetupRecordset)(THIS);
	STDMETHOD(PopulateField)(THIS_ GField *AddedField);
	STDMETHOD(ValidatePropertySet)(THIS);
	STDMETHOD(RecordsetClosed)(THIS);
	STDMETHOD(RecordsetUpdateCalled)(THIS);
	STDMETHOD(RecordsetLoaded)(THIS_ DGMAddFieldsPipe *AddFieldsPipe);
	STDMETHOD(BeginCompletePass)(THIS);
	STDMETHOD(EndCompletePass)(THIS);

// Enumeration aller Idents/ObjTypen einer Ansicht
	typedef vector<CIdentObjTyp> CIdents;
	struct CEnumIdentEntryCallback
	{
		CViewRecordsetGenerator *m_pRSG;
		CIdents *m_pIdents;
	};
	static HRESULT CALLBACK EnumIdentsCallBack (LONG lIdent, CNativeView::VisType rgType, DWORD dwData);

protected:
	HRESULT ValidateProperties();
	HRESULT RetrieveVisInfo (HPROJECT hPr, long lIdent, CNativeView::VisType rgType, DVisInfo **ppIVis);
	HRESULT RetrieveVisInfoItem (DVisInfo *pIVis, BSTR bstrName, CNativeView::VisType rgType, VARIANT *pvValue);

private:
	WDGMAddFieldsPipe m_Pipe;
	WDGMBaseTable m_Table;

	CComBSTR m_bstrViewName;	// wir sind verantworlich für diese Ansicht
	WTRiASSourceInfo m_SrcInfo;	// alle anderen notwendigen Informationen
	CIdents m_Idents;
	int m_iIdBase;
};

#endif // !defined(_VIEWRECORDSETGENERATOR_H__04F82133_B7EA_11D1_85B4_00600875138A__INCLUDED_)
