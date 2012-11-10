// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 30.07.2000 20:24:06
//
// @doc
// @module DeleteAttributes.cpp | Implementation of the <c CDeleteAttributes> class

#include "stdafx.h"

#include "PropActSubSeq.h"
#include "DeleteAttributes.h"

/////////////////////////////////////////////////////////////////////////////
// CDeleteAttributes
// IPropertyAction 

STDMETHODIMP CDeleteAttributes::BeginAction (IProgressIndicator *pIProgInd)
{
	RETURN_FAILED_HRESULT(CPropertyActionImpl::BeginAction (pIProgInd));
	m_Objects.Clear();
	return S_OK;
}

STDMETHODIMP CDeleteAttributes::DoAction (IDataObject *pIDataObj, DWORD dwReserved)
{
// Eingabeobjekte einfach mit zu unserer Objektmenge hinzufügen
	COM_TRY {
	WEnumLONG EnumObjs;
	OutEnumLONG iter_out_if (&m_Objects);

		THROW_FAILED_HRESULT(PropActBase::GetEnumObjects (pIDataObj, __uuidof(IEnumLONG), EnumObjs.ppv()));
		copy (InEnumLONG(EnumObjs), InEnumLONG(), iter_out_if);

	} COM_CATCH;
	return S_OK;
}

namespace {
///////////////////////////////////////////////////////////////////////////////
// Klasse, die die Verarbeitung der einzelnen Objekte der Eingabemenge erlaubt
	class CDeleteAttributesWorker 
	{
	public:
		CDeleteAttributesWorker(OutEnumLONG &rOutIter, CDeleteAttributes *pThis) : 
			m_pPA(pThis), m_rOutIter(rOutIter)
		{
		}
		~CDeleteAttributesWorker() {}

	// wird für jedes zu bearbeitende Objekt gerufen
		void operator() (LONG lONr)
		{
			_ASSERTE(NULL != m_pPA);
			m_pPA -> Tick();			// ProgressIndikator weitersetzen

		// TODO: Add your own precessing here
			m_rOutIter++ = lONr;		// object is added to the output collections
		}

	private:
		IProgressIndicatorUsage *m_pPA;
		OutEnumLONG &m_rOutIter;
	};
} // namespace

STDMETHODIMP CDeleteAttributes::EndAction (DWORD, IDataObject **ppDataObj)
{
	COM_TRY {
	// ProgressIndikator initialisieren
		SetMaxTicks (m_Objects.Count());

	// eigentliche Verarbeitung
	WEnumLONG EnumOut (CLSID_EnumObjectsByNumber);				// Ausgabeobjektmenge

		{
		OutEnumLONG iter_out (static_cast<IEnum<LONG> *>(EnumOut));

			for_each(InEnumLONG(&m_Objects), InEnumLONG(), CDeleteAttributesWorker(iter_out, this));
		} // iter_out goes out of scope

	// Ausgabeobjektmenge in Transfer-Objekt setzen
	__Interface<IDataObject> DO (CLSID_DataTransferObject);

		THROW_FAILED_HRESULT(PropActBase::SetEnumObjects (EnumOut, DO));
		*ppDataObj = DO.detach();

	// DialogPage freigeben
		if (NULL != m_pCfgDlg) {
			delete m_pCfgDlg;
			m_pCfgDlg = NULL;
		}

	} COM_CATCH;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersist
STDMETHODIMP CDeleteAttributes::GetClassID (CLSID *pClsID)
{
	*pClsID = GetObjectCLSID();
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistStreamInit
STDMETHODIMP CDeleteAttributes::Load (IStream *pStm)
{
	if (IsInitialized())
		return E_UNEXPECTED;

	RETURN_FAILED_HRESULT(CPropertyActionImpl::Load (pStm));

// TODO: Load your own data from the stream
	SetInitialized();
	return S_OK;
}

STDMETHODIMP CDeleteAttributes::Save (IStream *pStm, BOOL fClearDirty)
{
	RETURN_FAILED_HRESULT(CPropertyActionImpl::Save (pStm, fClearDirty));

// TODO: Save your own data to the stream
	return S_OK;
}

STDMETHODIMP CDeleteAttributes::GetSizeMax (ULARGE_INTEGER *pcbSize)
{
	if (NULL == pcbSize)
		return E_POINTER;
	pcbSize -> QuadPart = 0L;

	RETURN_FAILED_HRESULT(CPropertyActionImpl::GetSizeMax (pcbSize));

// TODO: Add the size of your data to pcbSize
//	pcbSize  -> QuadPart += ...;
	return S_OK;
}

STDMETHODIMP CDeleteAttributes::InitNew()
{
	if (IsInitialized())
		return E_UNEXPECTED;

// TODO: initialize your data
	SetInitialized();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Geokomponente hat eigenen Dialog
STDMETHODIMP CDeleteAttributes::AddConfigPages (
	LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam, LPCSTR pcDesc, UINT *puiCnt)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	if (puiCnt) *puiCnt = 0;		// initialisieren

	COM_TRY {
	char cbCaption[128];

		if (NULL != pcDesc)	{	// Caption ist gegeben
			ASSERT(strlen(pcDesc) < sizeof(cbCaption));
			strcpy (cbCaption, pcDesc);
		} else	// von zugehöriger ClassProperty unseren Namen besorgen
			GetPropInfo (cbCaption, sizeof(cbCaption), NULL);

	// zugehörigen ConfigDialog (PropertyPage(s)) anlegen
		if (NULL != m_pCfgDlg) delete m_pCfgDlg;
		m_pCfgDlg = CDeleteAttributesDlg::CreateInstance(cbCaption);
		if (NULL == m_pCfgDlg) _com_issue_error(E_OUTOFMEMORY);

		if (!IsNoShow()) {
		// Seite hizufügen, wenn selbige angezeigt werden soll
		PROPSHEETPAGE psp;

			memcpy(&psp, &m_pCfgDlg->m_psp, sizeof(PROPSHEETPAGE));
		

		HPROPSHEETPAGE hPSP = ::CreatePropertySheetPage (&psp);

			if (NULL == hPSP) return E_HANDLE;
			if (!(*lpfnAddPage) (hPSP, lParam))
				return E_FAIL;

			if (puiCnt) *puiCnt = 1;		// wir haben eine Page hinzugefügt
		} 
	} COM_CATCH_OP(delete m_pCfgDlg);
	return S_OK;
}  

STDMETHODIMP CDeleteAttributes::PreConfigPages (IDataObject *pIDataObject, DWORD dwFlags)
{
	if (NULL == m_pCfgDlg) 
		return E_UNEXPECTED;

	m_pCfgDlg -> SetFlags(dwFlags);
	return S_OK;
}
