// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 15.04.2002 11:21:55 
//
// @doc
// @module LimitSearches.cpp | Definition of the <c CLimitSearches> class

#include "trias03p.hxx"
#include "trias03.h"

#include <Com/Thunk.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "LimitSearches.h"

/////////////////////////////////////////////////////////////////////////////
// CLimitSearches
// IPropertyAction 

STDMETHODIMP CLimitSearches::BeginAction (IProgressIndicator *pIProgInd)
{
	RETURN_FAILED_HRESULT(CPropertyActionImpl::BeginAction (pIProgInd));
	m_Objects.clear();
	m_itlist = m_Objects.begin();
	m_lPacket = 0;

	m_RefObjects.Clear();
	m_fRefObjectsInit = false;
 	return S_OK;
}

STDMETHODIMP CLimitSearches::DoAction (IDataObject *pIDataObj, DWORD dwReserved)
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
		m_lPacket = 0;

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CLimitSearches::EndAction (DWORD, IDataObject **ppDataObj)
{
HRESULT hr = S_OK;

	COM_TRY {
	// ProgressIndikator initialisieren
		SetMaxTicks (m_Objects.size());

	// Ausgabeobjektmenge in Transfer-Objekt
	__Interface<IDataObject> DO (CLSID_DataTransferObject);

	// eigentliche Verarbeitung
	WEnumLONG EnumOut (CLSID_EnumObjectsByNumber);		// Ausgabeobjektmenge

		if (m_itlist != m_Objects.end()) {
		OutEnumLONG iter_out (static_cast<IEnum<LONG> *>(EnumOut));

			if (DEX_GetLimitSearches() && SUCCEEDED(EnsureRefObjects())) {
			// Schnittmenge mit Bildausschnitt bilden
				set_intersection(InEnumLONG(&(*m_itlist)), InEnumLONG(), 
					InEnumLONG(&m_RefObjects), InEnumLONG(), iter_out);
			}
			else {
			// aktuelles Paket weiterreichen
				copy(InEnumLONG(&(*m_itlist)), InEnumLONG(), iter_out);
			}

			++m_itlist;								// der nächste, Bitte
			hr = (m_itlist == m_Objects.end()) ? S_OK : S_FALSE;

			THROW_FAILED_HRESULT(PropActBase::SetPacketNumber(DO, ++m_lPacket));

		// ProgressIndikator weitersetzen
			Tick();
			if (FAILED(GoOn()))
				_com_issue_error(E_ABORT);
		}

		THROW_FAILED_HRESULT(PropActBase::SetEnumObjects (EnumOut, DO));
		*ppDataObj = DO.detach();

	} COM_CATCH_NOASSERT_ON(E_ABORT);
	return hr;
}

/////////////////////////////////////////////////////////////////////////////
// IPersist
STDMETHODIMP CLimitSearches::GetClassID (CLSID *pClsID)
{
	*pClsID = GetObjectCLSID();
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistStreamInit
STDMETHODIMP CLimitSearches::Load (IStream *pStm)
{
	if (IsInitialized())
		return E_UNEXPECTED;

	RETURN_FAILED_HRESULT(CPropertyActionImpl::Load (pStm));
	SetInitialized();
	return S_OK;
}

STDMETHODIMP CLimitSearches::Save (IStream *pStm, BOOL fClearDirty)
{
	RETURN_FAILED_HRESULT(CPropertyActionImpl::Save (pStm, fClearDirty));
	return S_OK;
}

STDMETHODIMP CLimitSearches::GetSizeMax (ULARGE_INTEGER *pcbSize)
{
	if (NULL == pcbSize)
		return E_POINTER;
	pcbSize -> QuadPart = 0L;

	RETURN_FAILED_HRESULT(CPropertyActionImpl::GetSizeMax (pcbSize));
	return S_OK;
}

STDMETHODIMP CLimitSearches::InitNew()
{
	if (IsInitialized())
		return E_UNEXPECTED;

	SetInitialized();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Geokomponente hat eigenen Dialog
STDMETHODIMP CLimitSearches::AddConfigPages (
	LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam, LPCSTR pcDesc, UINT *puiCnt)
{
	if (puiCnt) 
		*puiCnt = 0;		// wir haben keine Pages
	return S_OK;
}  

STDMETHODIMP CLimitSearches::PreConfigPages (IDataObject *pIDataObject, DWORD dwFlags)
{
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// ReferenzObjektmenge sicherstellen
BOOL __stdcall CLimitSearches::AddRefObject (HOBJECT lONr, BOOL iNotLast, void *pData)
{
	m_RefObjects.AddItem(lONr);
	return TRUE;
}

HRESULT CLimitSearches::EnsureRefObjects()
{
	if (m_fRefObjectsInit)
		return S_OK;

long lCoords[4];

	if (DEX_GetActiveSelection(lCoords) || DEX_GetWindowAsDbContainer(lCoords)) {
	CStdThunkImpl<CLimitSearches, RECHGEOMETRIECALLBACK> Thunk(this, &CLimitSearches::AddRefObject);
	ENUMRECHGEOMETRIEEX ERG;

		INITSTRUCT(ERG, ENUMRECHGEOMETRIEEX);
		ERG.lCont = lCoords;
		ERG.iMode = ERGActSight|ERGExact;
		ERG.eFcn = (RECHGEOMETRIEPROC)Thunk.GetThunk();
		if (DEX_EnumRechGeometrie(ERG)) {
			m_fRefObjectsInit = true;
			return S_OK;
		}
	}
	return E_UNEXPECTED;
}

