// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 01.11.2002 12:18:27
//
// @doc
// @module VBPropertySequence.cpp | Implementation of the <c CVBGeoComponent> class

#include "trias03p.hxx"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include <Atl/Ciid.h>
#include <Com/ComBool.h>
#include <Com/PropertyBagOnStream.h>

#include <triastlb.h>
#include <itriasap.h>		// IGetTRiASApplication
#include <oleguid.h>
#include <ipropseq.hxx>

#include "trias03.h"
#include "Strings.h"
#include "Datahelp.h"

#include "VBPropertySequence.h"
#include "TRiASPropertyBagOnIPropertyBag.h"

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(GetTRiASApplication);
DefineSmartInterface2(DApplication, IID_DApplication);
DefineSmartInterface2(DDocument, IID_DDocument);
DefineSmartInterface(ProgressIndicator2);
DefineSmartInterface(TRiASDataObject);
DefineSmartInterface(ParseStringPairs2);
DefineSmartInterface(TRiASPropertyBag);
DefineSmartInterface(PropertyActionSequence);
DefineSmartInterface(DataObject);
DefineSmartInterface(ObjectWithSite);

///////////////////////////////////////////////////////////////////////////////
// 
HRESULT CVBGeoComponent::FinalConstruct()
{
	return S_OK;
}

void CVBGeoComponent::FinalRelease()
{
	m_EmbeddedObj.Assign(NULL);
}

/////////////////////////////////////////////////////////////////////////////
// CVBGeoComponent
// IPropertyAction 

STDMETHODIMP CVBGeoComponent::BeginAction (IProgressIndicator *pIProgInd)
{
	COM_TRY {
		THROW_FAILED_HRESULT(CPropertyActionImpl::BeginAction (pIProgInd));
		THROW_FAILED_HRESULT(m_EmbeddedObj->BeginAction(WProgressIndicator2(pIProgInd)));
	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CVBGeoComponent::DoAction (IDataObject *pIDataObj, DWORD dwReserved)
{
	COM_TRY {
		THROW_FAILED_HRESULT(m_EmbeddedObj->DoAction(WTRiASDataObject(pIDataObj)));
	} COM_CATCH;
	return S_OK;
}

void CVBGeoComponent::ReleaseAll()
{
	if (m_EmbeddedObj.IsValid())
		m_EmbeddedObj->putref_Callback(NULL);
	ReleaseDlgs();
}

STDMETHODIMP CVBGeoComponent::EndAction (DWORD, IDataObject **ppDataObj)
{
	if (NULL == ppDataObj)
		return E_POINTER;
	*ppDataObj = NULL;

HRESULT hr = E_ABORT;
CComBool fHasDataOut;

	COM_TRY {
	WTRiASDataObject DataOut;

		THROW_FAILED_HRESULT(m_EmbeddedObj->EndAction(DataOut.ppi()));
		THROW_FAILED_HRESULT(m_EmbeddedObj->get_HasDataOut(&fHasDataOut));

	// Ausgabeobjektmenge nur dann liefern, wenn wirklich eine da ist
		if (DataOut.IsValid())
		{
			THROW_FAILED_HRESULT(DataOut->QueryInterface(ppDataObj));
		}

	} COM_CATCH_OP_NOASSERT_ON(ReleaseAll(), E_ABORT);

// DialogPage freigeben
	if (!fHasDataOut) {
		ReleaseAll();
		return S_OK;
	} 
	return S_FALSE;		// es kommt noch was
}

/////////////////////////////////////////////////////////////////////////////
// IPersist
STDMETHODIMP CVBGeoComponent::GetClassID (CLSID *pClsID)
{
	*pClsID = GetObjectCLSID();
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistStreamInit

namespace local {

	template <class Base>
	class CComObjectStack : public Base
	{
	public:
		typedef Base _BaseClass;
		CComObjectStack(void* = NULL){ m_hResFinalConstruct = FinalConstruct();}
		~CComObjectStack()
		{
			FinalRelease();
	#ifdef _ATL_DEBUG_INTERFACES
			_Module.DeleteNonAddRefThunk(_GetRawUnknown());
	#endif
		}

		STDMETHOD_(ULONG, AddRef)() { return 0;}
		STDMETHOD_(ULONG, Release)(){ return 0;}
		STDMETHOD(QueryInterface)(REFIID iid, void ** ppvObject)
		{return _InternalQueryInterface(iid, ppvObject);}

		HRESULT m_hResFinalConstruct;
	};
}

// 2F7F478E-D9B8-4571-8A41-3723A8479BF7
EXTERN_C const GUID __declspec(selectany) FMTID_SABiSGeoComponent = 
	{ 0x2F7F478E, 0xD9B8, 0x4571, 0x8A, 0x41, 0x37, 0x23, 0xA8, 0x47, 0x9B, 0xF7 };

STDMETHODIMP CVBGeoComponent::Load (IStream *pStm)
{
	if (IsInitialized())
		return E_UNEXPECTED;

	RETURN_FAILED_HRESULT(CPropertyActionImpl::Load (pStm));

os_string strGuid;

	RETURN_FAILED_HRESULT(LoadString(pStm, strGuid));
	m_GuidInit = CIID(strGuid.c_str(), CIID::INITCIID_InitFromProgId);
	if (!m_GuidInit.IsValid())
		return E_UNEXPECTED;

// embedded Objekt erzeugen
	RETURN_FAILED_HRESULT(m_EmbeddedObj.CreateInstance(m_GuidInit));
	RETURN_FAILED_HRESULT(m_EmbeddedObj -> putref_Callback(this));

WPropertyBag PropBag;

	RETURN_FAILED_HRESULT(OpenPropertyBagOnIStream(pStm, FMTID_SABiSGeoComponent, PropBag.ppi()));

local::CComObjectStack<CTRiASPropertyBagOnIPropertyBag> Bag;
	
	Bag.SetPropertyBag(PropBag);

HRESULT hr = m_EmbeddedObj->ReadProperties(Bag.GetPropertyBag());

	if (FAILED(hr)) {
		if (E_FAIL != hr) {
			RETURN_FAILED_HRESULT(hr);
		}
		return E_FAIL;
	}

	SetInitialized();
	return S_OK;
}

STDMETHODIMP CVBGeoComponent::Save (IStream *pStm, BOOL fClearDirty)
{
	RETURN_FAILED_HRESULT(CPropertyActionImpl::Save (pStm, fClearDirty));

CIID Guid(m_GuidInit);
WPropertyBag PropBag;

	RETURN_FAILED_HRESULT(SaveString(pStm, Guid.ProgID()));
	RETURN_FAILED_HRESULT(CreatePropertyBagOnIStream(pStm, FMTID_SABiSGeoComponent, PropBag.ppi()));

local::CComObjectStack<CTRiASPropertyBagOnIPropertyBag> Bag;

	Bag.SetPropertyBag(PropBag);
	RETURN_FAILED_HRESULT(m_EmbeddedObj->WriteProperties(Bag.GetPropertyBag()));
	return S_OK;
}

STDMETHODIMP CVBGeoComponent::GetSizeMax (ULARGE_INTEGER *pcbSize)
{
	if (NULL == pcbSize)
		return E_POINTER;
	pcbSize -> QuadPart = 0L;

	RETURN_FAILED_HRESULT(CPropertyActionImpl::GetSizeMax (pcbSize));

// TODO: Add the size of your data to pcbSize
	pcbSize  -> QuadPart += sizeof(m_GuidInit);
	return S_OK;
}

STDMETHODIMP CVBGeoComponent::InitNew()
{
	if (IsInitialized())
		return E_UNEXPECTED;

// TODO: initialize your data
	SetInitialized();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Geokomponente hat eigenen Dialog
STDMETHODIMP CVBGeoComponent::AddConfigPages (
	LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam, LPCSTR pcDesc, UINT *puiCnt)
{
	if (puiCnt) *puiCnt = 0;		// initialisieren

	COM_TRY {
	char cbCaption[128];

		if (NULL != pcDesc)	{	// Caption ist gegeben
			_ASSERTE(strlen(pcDesc) < sizeof(cbCaption));
			strcpy (cbCaption, pcDesc);
		} else	// von zugehöriger ClassProperty unseren Namen besorgen
			GetPropInfo (cbCaption, sizeof(cbCaption), NULL);

	long lCount = 0;

		THROW_FAILED_HRESULT(m_EmbeddedObj->get_PageCount(&lCount));
		if (lCount > 0) {
		// zugehörige ConfigDialoge (PropertyPage(s)) anlegen
			ReleaseDlgs();
			m_ppCfgDlgs = new CVBGeoComponentDlg *[lCount];
			m_lDlgCount = lCount;

			for (long i = 0; i < lCount; ++i) {
			CComBSTR bstrProgId;

				THROW_FAILED_HRESULT(m_EmbeddedObj->get_PageProgId(i, &bstrProgId));

			CIID Guid (bstrProgId, CIID::INITCIID_InitFromProgId);

				if (!Guid)
					_com_issue_error(REGDB_E_CLASSNOTREG);

				m_ppCfgDlgs[i] = CVBGeoComponentDlg::CreateInstance(cbCaption, Guid, i);
				if (NULL == m_ppCfgDlgs[i]) _com_issue_error(E_OUTOFMEMORY);

			// Geokomponente durchreichen
				m_ppCfgDlgs[i]->SetGeoComponent(m_EmbeddedObj);

				if (!IsNoShow()) {
				// Seite hizufügen, wenn selbige angezeigt werden soll
					if (m_strHeaderTitle.size() > 0) {
						m_ppCfgDlgs[i]->SetHeaderTitle(m_strHeaderTitle.c_str());
						if (m_strHeaderSubTitle.size() > 0)
							m_ppCfgDlgs[i]->SetHeaderSubTitle(m_strHeaderSubTitle.c_str());
					}

				HPROPSHEETPAGE hPSP = m_ppCfgDlgs[i]->Create();

					if (NULL == hPSP) return E_HANDLE;
					if (!(*lpfnAddPage) (hPSP, lParam))
						return E_FAIL;
				}
			}

			if (!IsNoShow() && NULL != puiCnt) 
				*puiCnt = lCount;	// wir haben eine/mehrere Page hinzugefügt
		}
		 
	} COM_CATCH_OP(ReleaseDlgs());
	return S_OK;
}  

STDMETHODIMP CVBGeoComponent::PreConfigPages (IDataObject *pIDataObject, DWORD dwFlags)
{
	COM_TRY {
	WGetTRiASApplication GetApp (CLSID_OleAutoExtension);	//throws hr
	WDApplication App;
	WDDocument Doc;

		THROW_FAILED_HRESULT(GetApp->GetApplication (IID_DApplication, App.ppv()));
		App -> get_ActiveDocument (Doc.ppi());		// Fehler ignorieren

		THROW_FAILED_HRESULT(m_EmbeddedObj->PreConfigAction(App, Doc, 
			WTRiASDataObject(pIDataObject)));

	// Dialog von diesem Ereignis informieren
		for (long i = 0; i < m_lDlgCount; ++i) {
			if (NULL != m_ppCfgDlgs[i])
				m_ppCfgDlgs[i] -> SetFlags(dwFlags);
		}

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// 
HRESULT CVBGeoComponent::CreateEmbeddedAction (BSTR bstrProgId)
{
	COM_TRY {
		m_GuidInit = CIID(bstrProgId, CIID::INITCIID_InitFromProgId);
		if (!m_GuidInit)
			_com_issue_error(REGDB_E_CLASSNOTREG);

		THROW_FAILED_HRESULT(m_EmbeddedObj.CreateInstance(m_GuidInit));
		THROW_FAILED_HRESULT(m_EmbeddedObj -> putref_Callback(this));

	} COM_CATCH_OP(m_GuidInit = GUID_NULL);
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistPropertyBag
STDMETHODIMP CVBGeoComponent::Load (IPropertyBag *pBag, IErrorLog *pLog)
{
	USES_CONVERSION;
	RETURN_FAILED_HRESULT(CPropertyActionImpl::Load (pBag, pLog));

// InitData=
CComVariant vInitData;
HRESULT hr = pBag -> Read (CComBSTR(g_cbInitData), &vInitData, pLog);

	if (S_OK == hr && SUCCEEDED(vInitData.ChangeType(VT_BSTR))) {
	WParseStringPairs2 Pairs;
	long lPairs = 0;

		RETURN_FAILED_HRESULT(Pairs.CreateInstance(CLSID_ParseStringPairs));
		RETURN_FAILED_HRESULT(Pairs -> put_Pattern(CComBSTR(g_cbVBInitPattern)));
		RETURN_FAILED_HRESULT(Pairs -> Parse(V_BSTR(&vInitData), &lPairs));
		if (0 != lPairs) 
		{
			RETURN_FAILED_HRESULT(m_EmbeddedObj -> InitFromData(WTRiASPropertyBag(Pairs)));
		}
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// 
STDMETHODIMP CVBGeoComponent::get_ContextData(ITRiASDataObject **ppIDataCtx)
{
	if (NULL == ppIDataCtx)
		return E_POINTER;
	*ppIDataCtx = NULL;

	COM_TRY {
	WDataObject DO;
	WPropertyActionSequence Seq;

		THROW_FAILED_HRESULT(WObjectWithSite(GetUnknown()) -> GetSite (
			Seq.GetIID(), Seq.ppv()));
		THROW_FAILED_HRESULT(Seq -> GetSequenceContext (DO.ppi()));

	WTRiASDataObject TDO (DO);

		*ppIDataCtx = TDO.detach();

	} COM_CATCH;
	return S_OK;
}


