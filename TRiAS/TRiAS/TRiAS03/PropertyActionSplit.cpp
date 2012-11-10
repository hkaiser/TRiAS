// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 06.10.2000 18:40:03
//
// @doc
// @module PropertyActionSplit.cpp | Implementation of the <c CPropertyActionSplit> class

#include "trias03p.hxx"
#include "trias03.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include <TrCatIds.h>
#include "PropertyActionSplit.h"

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(Stream);
DefineSmartInterface(PersistStream);
DefineSmartInterface(PersistStreamInit);
DefineSmartInterface(ObjectWithSite);
DefineSmartInterface(PropertyAction2);
DefineSmartInterface(PropertyActionSequence);

/////////////////////////////////////////////////////////////////////////////
// CPropertyActionSplit
// IPropertyAction 

STDMETHODIMP CPropertyActionSplit::BeginAction (IProgressIndicator *pIProgInd)
{
	RETURN_FAILED_HRESULT(CPropertyActionImpl::BeginAction (pIProgInd));

// alle sekundären Geo-Komponenten durchgehen
	for (CActionList::iterator it = m_Actions.begin(); it != m_Actions.end(); ++it) 
	{
		RETURN_FAILED_HRESULT((*it) -> BeginAction(pIProgInd));
	}

// Iteratoren Rücksetzen
	m_itlist = m_listObjects.begin();
	m_itact = m_Actions.begin();
	m_iCurrAct = 1;
	m_fHasDoAction = false;
	
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// alle Objekte des direkten Input-Objektes zwischenspeichern
STDMETHODIMP CPropertyActionSplit::DoAction (IDataObject *pIDataObj, DWORD dwReserved)
{
// Eingabeobjekte einfach mit zu unserer Objektmenge hinzufügen
	COM_TRY {
	// jedes Datenobjekt separat speichern
		if (NULL != pIDataObj)
			m_listObjects.push_back(WDataObject(pIDataObj));

	// alle sekundären Geo-Komponenten durchgehen
		for (CActionList::iterator it = m_Actions.begin(); it != m_Actions.end(); ++it) 
		{
			RETURN_FAILED_HRESULT((*it) -> DoAction(pIDataObj, dwReserved));
		}

		m_itlist = m_listObjects.begin();	// muß jedesmal gemacht werden

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// zuerst werden alle Objekte des direkten Inputobjektes geliefert, danach 
// werden nacheinander alle sonstigen Eingabe- Geo-Komponenten behandelt
STDMETHODIMP CPropertyActionSplit::EndAction (DWORD dwRes, IDataObject **ppDataObj)
{
	TEST_OUT_PARAM(ppDataObj);
	COM_TRY {
	// ProgressIndikator initialisieren
		SetMaxTicks (m_listObjects.size());

	// direkte Eingabepakete einfach wieder rausreichen
		if (m_itlist != m_listObjects.end()) {
		WDataObject DO (*m_itlist);

			*ppDataObj = DO.detach();
			++m_itlist;								// der nächste, Bitte
			return (m_itlist == m_listObjects.end()) ? S_OK : S_FALSE;
		}

	} COM_CATCH;
	return S_OK;	// Ende es kommt nichts mehr
}

/////////////////////////////////////////////////////////////////////////////
// IPersist
STDMETHODIMP CPropertyActionSplit::GetClassID (CLSID *pClsID)
{
	*pClsID = GetObjectCLSID();
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistStreamInit
STDMETHODIMP CPropertyActionSplit::Load (IStream *pStm)
{
	if (IsInitialized())
		return E_UNEXPECTED;

// vorinitialisieren
	m_iLast = m_iFirst = -1;
	m_Actions.clear();
	m_listObjects.clear();

	m_itlist = m_listObjects.begin();
	m_itact = m_Actions.begin();
	m_iCurrAct = 1;
	m_fHasDoAction = false;

// jetzt alle Daten laden
	RETURN_FAILED_HRESULT(CPropertyActionImpl::Load (pStm));

// Signatur und Version prüfen
DWORD dwSignature = 0;

	RETURN_FAILED_HRESULT(pStm -> Read (&dwSignature, sizeof(dwSignature), NULL));
	if (dwSignature != PROPERTYACTIONSPLIT_SIGNATURE)
		return E_UNEXPECTED;

DWORD dwVersion = 0;

	RETURN_FAILED_HRESULT(pStm -> Read (&dwVersion, sizeof(dwVersion), NULL));
	if ((dwVersion & ~PROPERTYACTIONSPLIT_MINOR_MASK) > PROPERTYACTIONSPLIT_LASTVERSION)
		return E_UNEXPECTED;

// jetzt alle Objekte nachladen und in unserer Liste speichern
ULONG ulCount = 0;	// Anzahl der gespeicherten Objekte

	RETURN_FAILED_HRESULT(pStm ->Read (&ulCount, sizeof(ulCount), NULL));
	for (ULONG ul = 0; ul < ulCount; ++ul) {
	WPropertyAction PropAct;

		RETURN_FAILED_HRESULT(::OleLoadFromStream(pStm, __uuidof(IPropertyAction), PropAct.ppv()));
		m_Actions.push_back (PropAct);
	}
	SetInitialized();
	return S_OK;
}

STDMETHODIMP CPropertyActionSplit::Save (IStream *pStm, BOOL fClearDirty)
{
	RETURN_FAILED_HRESULT(CPropertyActionImpl::Save (pStm, fClearDirty));

// Schreiben der AktionsFolge
	RETURN_FAILED_HRESULT(pStm -> Write (&PROPERTYACTIONSPLIT_SIGNATURE, sizeof(DWORD), NULL));
	RETURN_FAILED_HRESULT(pStm -> Write (&PROPERTYACTIONSPLIT_LASTVERSION, sizeof(DWORD), NULL));

LONG ulCount = m_Actions.size();	// Anzahl der Aktionen

	RETURN_FAILED_HRESULT(pStm -> Write (&ulCount, sizeof(ulCount), NULL));
	for (CActionList::iterator it = m_Actions.begin(); it != m_Actions.end(); ++it) 
	{
	WPersistStream StmInit;

		if (SUCCEEDED((*it) -> QueryInterface(StmInit.ppi()))) 
		{
			RETURN_FAILED_HRESULT(::OleSaveToStream (StmInit, pStm));
		}
	}

	if (fClearDirty)
		m_fIsDirty = false;
	return S_OK;
}

STDMETHODIMP CPropertyActionSplit::GetSizeMax (ULARGE_INTEGER *pcbSize)
{
	if (NULL == pcbSize)
		return E_POINTER;
	pcbSize -> QuadPart = 0L;

	RETURN_FAILED_HRESULT(CPropertyActionImpl::GetSizeMax (pcbSize));

	pcbSize -> QuadPart += 2*sizeof(DWORD) + sizeof(ULONG);		// Signature, Version, Count
	for (CActionList::iterator it = m_Actions.begin(); it != m_Actions.end(); ++it) 
	{
	WPersistStream StmInit;

		if (SUCCEEDED((*it) -> QueryInterface(StmInit.ppi()))) {
		ULARGE_INTEGER uli;

			uli.QuadPart = 0;
			RETURN_FAILED_HRESULT(StmInit -> GetSizeMax(&uli));
			pcbSize -> QuadPart += uli.QuadPart;
		}
	}
	return S_OK;
}

STDMETHODIMP CPropertyActionSplit::InitNew()
{
	if (IsInitialized())
		return E_UNEXPECTED;

	m_iLast = m_iFirst = -1;
	m_Actions.clear();
	m_listObjects.clear();

	m_itlist = m_listObjects.begin();
	m_itact = m_Actions.begin();
	m_iCurrAct = 1;
	m_fHasDoAction = false;

	SetInitialized();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// IPropertyActionSequence
STDMETHODIMP CPropertyActionSplit::SetDescription (LPCSTR pcDesc)
{
	if (NULL == pcDesc) 
		return E_POINTER;
	
	m_strDesc = pcDesc;
	return S_OK;
}

STDMETHODIMP CPropertyActionSplit::AddAction (IPropertyAction *pIAct)
{
	COM_TRY {
		if (!IsInitialized()) {
		// ggf. noch schnell initialisieren
			RETURN_FAILED_HRESULT(InitNew());
		}

	// Aktion zur Liste hinzufügen
		m_Actions.push_back (WPropertyAction(pIAct));
		m_itact = m_Actions.begin();		// muß jedes mal gemacht werden

		SetDirty(true);
		
	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CPropertyActionSplit::AddActionsByCLSID (CALPCLSID *pcaClsIds)
{
	COM_TRY {
		if (!IsInitialized()) {
		// ggf. noch schnell initialisieren
			RETURN_FAILED_HRESULT(InitNew());
		}

	// hinzufügen der einzelnen Aktionen
		for (ULONG i = 0; i < pcaClsIds -> cElems; i++) {
			if (NULL != pcaClsIds -> ppElems[i]) {
			// CLSID gegeben
			WPropertyAction WAct (*(pcaClsIds -> ppElems[i]));	// throws hr

#if !defined(_TRIAS_OLDIMPLEMTATION1)
				if (NULL != pcaClsIds -> ppvData && NULL != pcaClsIds -> ppvData[i]) {
				// evtl. InitialisierungsDaten vorhanden
				WPropertyAction2 Init;

					if (WAct.IsValid() && SUCCEEDED(WAct -> QueryInterface(Init.ppi()))) {
					WDataObject Data (CLSID_DataTransferObject);	// throws hr
					CComVariant v(*(pcaClsIds -> ppvData[i]));

						THROW_FAILED_HRESULT(PropActBase::SetVariantData (v, Data, &c_feInitPropAct));
						THROW_FAILED_HRESULT(Init -> InitFromData (Data, false, 0L));
					}
				} else 
#endif // _TRIAS_OLDIMPLEMTATION1
				{
				WPersistStreamInit Init (WAct);			// throws hr
					
					THROW_FAILED_HRESULT(Init -> InitNew());
				}
				THROW_FAILED_HRESULT(AddAction (WAct));
			} 
			else if (NULL != pcaClsIds -> ppActions && NULL != pcaClsIds -> ppActions[i]) 
			{
			// Objekt ist bereits gegeben
			WPropertyAction PropAct (const_cast<IUnknown *>(pcaClsIds -> ppActions[i]));
			
				THROW_FAILED_HRESULT(AddAction (PropAct));
			} 
			else {
				TX_ASSERT(NULL != pcaClsIds -> ppElems[i] || NULL != pcaClsIds -> ppActions[i]);
				continue;		// einfach weitermachen
			}
		}
	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// BeschreibungsInfo liefert Basisklasse
STDMETHODIMP CPropertyActionSplit::GetDescription (LPSTR pDesc, ULONG ulLen, ULONG *pulWritten)
{
	if (!IsInitialized()) {
	// ggf. noch schnell initialisieren
		RETURN_FAILED_HRESULT(InitNew());
	}

	RETURN_FAILED_HRESULT(CPropertyActionImpl::GetPropInfo(pDesc, ulLen, NULL));
	if (NULL != pulWritten)
		*pulWritten = strlen(pDesc);

	return S_OK;
}

// SequenceContext wird von übergeordneter Sequence bereitgestellt
STDMETHODIMP CPropertyActionSplit::GetSequenceContext (IDataObject **ppIData)
{
WPropertyActionSequence Seq;

	if (SUCCEEDED(GetSite (__uuidof(IPropertyActionSequence), Seq.ppv())) && Seq.IsValid())
		return Seq -> GetSequenceContext (ppIData);
	return E_UNEXPECTED;
}

///////////////////////////////////////////////////////////////////////////////
// die Funktionen, die direkt mit der Sequenz zu tun haben, werden hier nicht implementiert
STDMETHODIMP CPropertyActionSplit::DoActions (HWND hParent, IProgressIndicator *pIStatus, IDataObject *pIData, IDataObject **ppOutData)
{
	_ASSERTE(SUCCEEDED(E_UNEXPECTED));		// darf hier nicht gerufen werden
	return E_UNEXPECTED;
}

STDMETHODIMP CPropertyActionSplit::RedoActions (HWND hParent, IProgressIndicator *pIStatus, IDataObject *pIData, IDataObject **ppOutData)
{
	_ASSERTE(SUCCEEDED(E_UNEXPECTED));		// darf hier nicht gerufen werden
	return E_UNEXPECTED;
}

STDMETHODIMP CPropertyActionSplit::PrepareActions (HWND hParent, IDataObject *pIData)
{
	_ASSERTE(SUCCEEDED(E_UNEXPECTED));		// darf hier nicht gerufen werden
	return E_UNEXPECTED;
}

///////////////////////////////////////////////////////////////////////////////
// angehängte Geokomponenten haben evtl. eigene Dialoge
STDMETHODIMP CPropertyActionSplit::AddConfigPages (
	LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam, LPCSTR pcDesc, UINT *puiCnt)
{
	if (puiCnt) *puiCnt = 0;		// initialisieren

UINT uiCntA = 0;
int iCnt = 0;

	for (CActionList::iterator it = m_Actions.begin(); it != m_Actions.end(); ++it, ++iCnt) {
	// PropertyAction auffordern, ihre ConfigPages hinzuzufügen
	UINT uiCnt = 0;

		if (SUCCEEDED((*it) -> AddConfigPages (lpfnAddPage, lParam, pcDesc, &uiCnt)))
			uiCntA += uiCnt;

	// erstes/letztes Objekt mit Dialog
		if (0 != uiCnt) {
			m_iLast = iCnt;
			if (-1 == m_iFirst)
				m_iFirst = iCnt;
		}
	}

	if (NULL != puiCnt)		// Gesamtanzahl der installierten Pages liefern
		*puiCnt = uiCntA;
	return S_OK;
}  

STDMETHODIMP CPropertyActionSplit::PreConfigPages (IDataObject *pIDataObject, DWORD dwAddPageFlags)
{
	if (!IsInitialized()) 
		return E_UNEXPECTED;

int iCnt = 0;
int iLast = m_Actions.size()-1;

	for (CActionList::iterator it = m_Actions.begin(); it != m_Actions.end(); ++it, ++iCnt) 
	{
	// Ausgangsdaten vorbeischicken
	DWORD dwFlags = dwAddPageFlags & ~(ADDPAGES_FIRSTPAGE|ADDPAGES_LASTPAGE);

	// wenn die letzte PropertyAction
		if (iCnt == iLast && dwAddPageFlags & ADDPAGES_LASTPROPERTYACTION)
			dwFlags |= ADDPAGES_LASTPROPERTYACTION;

	// wenn letzte PropertyAction mit Dialog
		if (iCnt == m_iLast && dwAddPageFlags & ADDPAGES_LASTPAGE)
			dwFlags |= ADDPAGES_LASTPAGE;

	// wenn erste, ebenfalls
		if (0 == iCnt && dwAddPageFlags & ADDPAGES_FIRSTPROPERTYACTION)
			dwFlags |= ADDPAGES_FIRSTPROPERTYACTION;
		if (iCnt == m_iFirst && dwAddPageFlags & ADDPAGES_FIRSTPAGE)
			dwFlags |= ADDPAGES_FIRSTPAGE;

	HRESULT hr = (*it) -> PreConfigPages (pIDataObject, dwFlags);

		if (IMPL_AND_FAILED(hr)) 
			return hr;
	}
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IObjectWithSite
STDMETHODIMP CPropertyActionSplit::SetSite (IUnknown *pUnkSite)
{
// Basisklasse bedienen
	RETURN_FAILED_HRESULT(IObjectWithSiteImpl<CPropertyActionSplit>::SetSite (pUnkSite));

// alle registrierten Geo-Komponenten bedienen
	for (CActionList::iterator it = m_Actions.begin(); it != m_Actions.end(); ++it) {
	WObjectWithSite ObjSite;

		if (SUCCEEDED((*it) -> QueryInterface(ObjSite.ppi())))
			ObjSite ->SetSite (pUnkSite);
	}
	return S_OK;
}

STDMETHODIMP CPropertyActionSplit::GetVersion (LPSTR pDesc, ULONG ulLen, ULONG *pulWritten)
{
	ATLTRACENOTIMPL(CPropertyActionSplit::GetVersion);
}

STDMETHODIMP CPropertyActionSplit::SetVersion (LPCSTR pcDesc)
{
	ATLTRACENOTIMPL(CPropertyActionSplit::SetVersion);
}

STDMETHODIMP CPropertyActionSplit::SetIsWizard97 (VARIANT_BOOL fIsWizard97)
{
	ATLTRACENOTIMPL(CPropertyActionSplit::SetIsWizard97);
}

STDMETHODIMP CPropertyActionSplit::GetHeaderTitle (LPSTR pBuffer, ULONG wLen)
{
	return CPropertyActionImpl::GetHeaderTitle(pBuffer, wLen);
}

STDMETHODIMP CPropertyActionSplit::SetHeaderTitle (LPCSTR pcHeaderTitle)
{
	return CPropertyActionImpl::SetHeaderTitle(pcHeaderTitle);
}

STDMETHODIMP CPropertyActionSplit::GetHeaderSubTitle (LPSTR pSubBuffer, ULONG wLen)
{
	return CPropertyActionImpl::GetHeaderSubTitle(pSubBuffer, wLen);
}

STDMETHODIMP CPropertyActionSplit::SetHeaderSubTitle (LPCSTR pcHeaderSubTitle)
{
	return CPropertyActionImpl::SetHeaderSubTitle(pcHeaderSubTitle);
}

