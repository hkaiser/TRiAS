///////////////////////////////////////////////////////////////////////////
// @doc 
// @module RecordsetGenerator.h | Declaration of the <c COKSRecordsetGenerator>
// class

#if !defined(_RECORDSETGENERATOR_H__7417A5E5_AED0_11D1_859A_00600875138A__INCLUDED_)
#define _RECORDSETGENERATOR_H__7417A5E5_AED0_11D1_859A_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "TRiASGMR.h"       // main symbols

#include <DGMAddFieldsPipe.h>		// IFieldProviderCallback
#include <DGMBaseTable.h>			// IBaseTableCallback
#include <GMcssTypes.h>

#include "ScaleHeader.h"

/////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterfaceEx2(DGMAddFieldsPipe, IID_DGMAddFieldsPipe);
DefineSmartInterfaceEx2(DGMBaseTable, IID_DGMBaseTable);

DefineSmartInterface(TRiASSourceInfo);

/////////////////////////////////////////////////////////////////////////////
// COKSRecordsetGenerator
class ATL_NO_VTABLE COKSRecordsetGenerator : 
	public CComObjectRootEx<CComObjectThreadModel>, 
	public CComCoClass<COKSRecordsetGenerator, &CLSID_OKSRecordsetGenerator>,
	public IFieldProviderCallback,
	public IBaseTableCallback,
	public IRecordsetGenerator
{
public:
	COKSRecordsetGenerator()
	{
	}

	DECLARE_NOT_AGGREGATABLE(COKSRecordsetGenerator)
	DECLARE_REGISTRY_RESOURCEID(IDR_RECORDSETGENERATOR)
	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(COKSRecordsetGenerator)
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

protected:
	HRESULT ValidateProperties();

// Enumeration aller Objekte eines Idents
	typedef vector<unsigned long> CObjects;
	struct CEnumObjectsEntryCallback
	{
		COKSRecordsetGenerator *m_pRSG;
		CObjects *m_pObjs;
		DWORD m_dwTypes;
	};
	static HRESULT CALLBACK EnumObjectsCallBack (LONG lONr, DWORD dwType, DWORD dwData);

// Enumeration aller existierender Merkmale der Objekte dieses Idents
	typedef map<os_string, long, less<os_string> > CMCodes;
	struct CEnumMCodesCallback
	{
		COKSRecordsetGenerator *m_pRSG;
		CMCodes *m_pMCodes;
		HPROJECT m_hPrPbd;
	};
	static HRESULT CALLBACK EnumMCodesCallBack (LONG lMCode, DWORD dwData);

// Geometrie u.a. lesen/konvertieren
	HRESULT RetrieveGeometry (HPROJECT hPr, long lONr, VARIANT *pvValue);
	HRESULT RetrieveObjectTypeStr (HPROJECT hPr, long lONr, VARIANT *pvValue);
	HRESULT RetrieveObjectMerkmal (HPROJECT hPr, long lONr, long lMCode, VARIANT *pvValue);

private:
	WDGMAddFieldsPipe m_Pipe;
	WDGMBaseTable m_Table;

	CComBSTR m_bstrFeatName;	// wir sind verantworlich für diese Objektklasse
	WTRiASSourceInfo m_SrcInfo;	// alle anderen notwendigen Informationen
	CObjects m_Objs;
	CMCodes m_MCodes;
	CScaleHeader m_Hdr;
};

#endif // !defined(_RECORDSETGENERATOR_H__7417A5E5_AED0_11D1_859A_00600875138A__INCLUDED_)
