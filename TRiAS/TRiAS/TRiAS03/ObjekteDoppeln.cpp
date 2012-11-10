// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 09/12/1998 09:34:14 PM
//
// @doc
// @module ObjekteDoppeln.cpp | Implementation of the <c CObjekteDoppeln> class

#include "trias03p.hxx"
#include "trias03.h"

#include <ipropseq.hxx>
#include <xtsnguid.h>
#include <funcs03.h>

#include "ObjekteDoppelnGuid.h"
#include "ObjekteDoppeln.h"

///////////////////////////////////////////////////////////////////////////////
// 
extern char g_pDLLName[_MAX_PATH];

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(PropertyActionSequence);
DefineSmartInterface(DataObject);
DefineSmartInterface(ClassProperty);

/////////////////////////////////////////////////////////////////////////////
// CCopyObjects

// IPropertyAction 
STDMETHODIMP CCopyObjects::BeginAction (IProgressIndicator *pIProgInd)
{
	COM_TRY {
	// Zieldatenquelle aus KontextObjekt herausfinden
	WPropertyActionSequence Seq;
	WDataObject CtxDO;
	CComVariant vData;
	
		m_hPr = HACTCONNECTION;

		THROW_FAILED_HRESULT(GetSite (IID_IPropertyActionSequence, Seq.ppv()));
		THROW_FAILED_HRESULT(Seq -> GetSequenceContext (CtxDO.ppi()));

		if (SUCCEEDED(GetVariantData (CtxDO, &c_feDataSourceHandle, &vData)) &&
			SUCCEEDED(vData.ChangeType (VT_I4))) 
		{
			m_hPr = reinterpret_cast<HPROJECT>(V_I4(&vData));	// Zieldatenquelle
		}
		if (HACTCONNECTION == m_hPr && m_bstrDataSource.Length() > 0) 
		{
			USES_CONVERSION;
			m_hPr = DEX_GetDataSourceHandleFromShortName (OLE2A(m_bstrDataSource));
		}

	// neue Datenquelle besorgen (für später)
		if (HACTCONNECTION != m_hPr) {
			if (!m_bstrDataSource) {
			char cbBuffer[_MAX_PATH];

				if (DEX_GetDataSourceShortName(m_hPr, cbBuffer))
					m_bstrDataSource = cbBuffer;
			}
		} else
			m_bstrDataSource = g_cbNil;

		THROW_FAILED_HRESULT(CPropertyActionImpl::BeginAction (pIProgInd));
		m_Objects.clear();
		m_itlist = m_Objects.begin();
		m_lPacket = 0;

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CCopyObjects::DoAction (IDataObject *pIDataObj, DWORD dwReserved)
{
// EingabeObjektmengen in ihrer Strutur beibehalten
	COM_TRY {
	// neues Paket speichern
		m_Objects.push_back(CListOfPackets::value_type());

	CListOfPackets::reference Enum (m_Objects.back());

	// Objekte kopieren
	WEnumLONG EnumObjs;
	OutEnumLONG iter_out_if (&Enum);

		THROW_FAILED_HRESULT(PropActBase::GetEnumObjects (pIDataObj, __uuidof(IEnumLONG), EnumObjs.ppv()));
		copy (InEnumLONG(EnumObjs), InEnumLONG(), iter_out_if);

		m_itlist = m_Objects.begin();		// jedesmal machen
		m_lPacket = m_Objects.size();

	} COM_CATCH;
	return S_OK;
}

namespace {
///////////////////////////////////////////////////////////////////////////////
// Klasse, die die Verarbeitung der einzelnen Objekte der Eingabemenge erlaubt
	class CCopyObjectsWorker 
	{
	public:
		CCopyObjectsWorker(OutEnumLONG &rOutIter, CCopyObjects *pThis) : 
			m_pPA(pThis), m_rOutIter(rOutIter), m_hPrDest(pThis -> GetDestinationProject())
		{
		}
		~CCopyObjectsWorker() {}

	// wird für jedes zu bearbeitende Objekt gerufen
		void operator() (INT_PTR lONr)
		{
			_ASSERTE(NULL != m_pPA);
			m_pPA -> Tick();			// ProgressIndikator weitersetzen
			if (FAILED(m_pPA -> GoOn()))
				_com_issue_error(E_ABORT);

		HPROJECT hPrDest = m_hPrDest;					// entweder global Ziel gegeben ..

			if (HACTCONNECTION == hPrDest)
				hPrDest = DEX_GetObjectProject(lONr);	// oder in AusgangsDatenquelle speichern

		CLONEOBJECT CO;

			INITSTRUCT(CO, CLONEOBJECT);
			CO.lONrToCopy = lONr;
			if (DEX_CloneObjectEx(hPrDest, CO))
				++m_rOutIter = CO.lNewONr;		// new object is added to the output collections
		}

	private:
		IProgressIndicatorUsage *m_pPA;
		OutEnumLONG &m_rOutIter;
		HPROJECT m_hPrDest;
	};
} // namespace

STDMETHODIMP CCopyObjects::EndAction (DWORD, IDataObject **ppDataObj)
{
HRESULT hr = S_OK;

	COM_TRY {
	// Undo initialisieren
	ResourceFile RF (g_pDLLName);
	ResString resUndo (ResID (IDS_COPYOBJECTS_UNDO, &RF), 128);

		BeginUndoLevel (resUndo);

	// Ausgabeobjektmenge in Transfer-Objekt
	WDataObject DO (CLSID_DataTransferObject);

	// eigentliche Verarbeitung
	WEnumLONG EnumOut (CLSID_EnumObjectsByNumber);		// Ausgabeobjektmenge

		if (m_itlist != m_Objects.end()) {
		OutEnumLONG iter_out (static_cast<IEnum<LONG> *>(EnumOut));

		// ProgressIndikator initialisieren
			SetMaxTicks ((*m_itlist).Count());
			for_each(InEnumLONG(&(*m_itlist)), InEnumLONG(), CCopyObjectsWorker(iter_out, this));

			++m_itlist;								// der nächste, Bitte
			hr = (m_itlist == m_Objects.end()) ? S_OK : S_FALSE;

			THROW_FAILED_HRESULT(PropActBase::SetPacketNumber(DO, m_lPacket--));
		}

		THROW_FAILED_HRESULT(PropActBase::SetEnumObjects (EnumOut, DO));
		*ppDataObj = DO.detach();

		if (hr != S_FALSE) 
		{
			DELETE_OBJ (m_pCfgDlg);		// DialogPage freigeben, wenn nichts mehr kommt
		}
		EndUndoLevel();

	} COM_CATCH_OP_NOASSERT_ON(CancelUndoLevel(TRUE), E_ABORT);
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
//// IPersist
STDMETHODIMP CCopyObjects::GetClassID (CLSID *pClsID)
{
	*pClsID = GetObjectCLSID();
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistStreamInit
STDMETHODIMP CCopyObjects::Load (IStream *pStm)
{
	if (IsInitialized())
		return E_UNEXPECTED;

	RETURN_FAILED_HRESULT(CPropertyActionImpl::Load (pStm));

string strDataSource;

	RETURN_FAILED_HRESULT(LoadString(pStm, strDataSource));
	m_bstrDataSource = strDataSource.c_str();
	if (NULL != m_pCfgDlg) 
		m_pCfgDlg -> SetDataSource(m_bstrDataSource);

	SetInitialized();
	return S_OK;
}

STDMETHODIMP CCopyObjects::Save (IStream *pStm, BOOL fClearDirty)
{
	RETURN_FAILED_HRESULT(CPropertyActionImpl::Save (pStm, fClearDirty));

	USES_CONVERSION;

string strDataSource(!m_bstrDataSource ? "" : OLE2A(m_bstrDataSource));

	RETURN_FAILED_HRESULT(SaveString(pStm, strDataSource));
	return S_OK;
}

STDMETHODIMP CCopyObjects::GetSizeMax (ULARGE_INTEGER *pcbSize)
{
	if (NULL == pcbSize)
		return E_POINTER;
	pcbSize -> QuadPart = 0L;

	RETURN_FAILED_HRESULT(CPropertyActionImpl::GetSizeMax (pcbSize));
	pcbSize -> QuadPart += m_bstrDataSource.Length();
	return S_OK;
}

STDMETHODIMP CCopyObjects::InitNew()
{
	if (IsInitialized())
		return E_UNEXPECTED;

	m_bstrDataSource.Empty();
	SetInitialized();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Geokomponente hat eigenen Dialog
STDMETHODIMP CCopyObjects::AddConfigPages (
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

	// Kontext des Dialoges feststellen
	WClassProperty Cls;
	bool fChoice = false;

		if (SUCCEEDED(GetSite (IID_IClassProperty, Cls.ppv()))) {
		// Kontext ist entweder PropertyChoice oder PropertySequence 
		DWORD dwFlags = 0;

			if (SUCCEEDED(Cls -> GetPropInfo (NULL, 0, &dwFlags)))
				fChoice = (dwFlags & PROPCAPS_CONTAINER_IS_CHOICE) ? true : false;
		}

	// zugehörigen ConfigDialog (PropertyPage(s)) anlegen
	ResourceFile RF (g_pDLLName);

		DELETE_OBJ(m_pCfgDlg);
		m_pCfgDlg = CCopyObjectsDlg::CreateInstance(this, 
						ResID (!fChoice ? CCopyObjectsDlg::IDD : CCopyObjectsDlg::IDDPP, &RF), cbCaption);
		if (NULL == m_pCfgDlg) _com_issue_error(E_OUTOFMEMORY);

		if (!IsNoShow()) {
		// Seite hizufügen, wenn selbige angezeigt werden soll
		HPROPSHEETPAGE hPSP = this -> CreatePage(m_pCfgDlg);

			if (NULL == hPSP) return E_HANDLE;
			if (!(*lpfnAddPage) (hPSP, lParam))
				return E_FAIL;

			if (puiCnt) *puiCnt = 1;		// wir haben eine Page hinzugefügt
		} 

	} COM_CATCH_OP((delete m_pCfgDlg, m_pCfgDlg = NULL));
	return S_OK;
}  

STDMETHODIMP CCopyObjects::PreConfigPages (IDataObject *pIDataObject, DWORD dwFlags)
{
	if (NULL == m_pCfgDlg) 
		return E_UNEXPECTED;

	m_pCfgDlg -> SetFlags(dwFlags);
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistPropertyBag
// mögliche SteuerParameter
//  DataSource=		Datenquelle, wo die Objekte erzeugt werden sollen

STDMETHODIMP CCopyObjects::Load (IPropertyBag *pBag, IErrorLog *pLog)
{
	USES_CONVERSION;
	RETURN_FAILED_HRESULT(CPropertyActionImpl::Load (pBag, pLog));

CComVariant vParam;

// DataSource=
HRESULT hr = pBag -> Read (CComBSTR(g_cbDataSource), &vParam, pLog);

	if (S_OK == hr && SUCCEEDED(vParam.ChangeType (VT_BSTR)))
		m_bstrDataSource = V_BSTR(&vParam);

	return S_OK;
}

