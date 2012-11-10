// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 27.08.2002 10:50:44
//
// @doc
// @module LimitPackets.cpp | Implementation of the <c CLimitPackets> class

#include "trias03p.hxx"

#include <datahelp.h>

#include "trias03.h"
#include "Strings.h"
#include "LimitPackets.h"

/////////////////////////////////////////////////////////////////////////////
// CLimitPackets
// IPropertyAction 

STDMETHODIMP CLimitPackets::BeginAction (IProgressIndicator *pIProgInd)
{
	RETURN_FAILED_HRESULT(CPropertyActionImpl::BeginAction (pIProgInd));
	m_Objects.clear();
	m_itlist = m_Objects.begin();
	m_lPacket = 0;
	m_lORWndCnt = 0;

	m_pCfgDlg -> GetSelectedData(m_selData);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Testen, ob ein Paket weitergeschickt werden soll
bool CLimitPackets::BlockPacket (IEnum<LONG> *pIEnumObjs)
{
	if (0 != m_selData.lLimitORWnds) {
		if (++m_lORWndCnt > m_selData.lLimitORWnds)
			return false;		// schon mehr als gebraucht
	}

ULONG lCnt = pIEnumObjs->Count();

	switch (m_selData.rgLimit) {
	case LIMITPACKETS_None:
		return false;	// nothing to do 

	case LIMITPACKETS_Lesser:
		if (m_selData.lLimitObjs > lCnt)
			return false;
		break;

	case LIMITPACKETS_Equal:
		if (m_selData.lLimitObjs == lCnt)
			return false;
		break;

	case LIMITPACKETS_More:
		if (m_selData.lLimitObjs < lCnt)
			return false;
		break;

	case LIMITPACKETS_LesserEqual:
		if (m_selData.lLimitObjs >= lCnt)
			return false;
		break;

	case LIMITPACKETS_MoreEqual:
		if (m_selData.lLimitObjs <= lCnt)
			return false;
		break;
	}
	return true;
}

STDMETHODIMP CLimitPackets::DoAction (IDataObject *pIDataObj, DWORD dwReserved)
{
// EingabeObjektmengen in ihrer Strutur beibehalten
	COM_TRY {
	// Objektnummer setzen
	long lPacket = 0;
	WEnumLONG EnumObjs;

		THROW_FAILED_HRESULT(PropActBase::GetPacketNumber(pIDataObj, &lPacket));
		THROW_FAILED_HRESULT(PropActBase::GetEnumObjects (pIDataObj, __uuidof(IEnumLONG), EnumObjs.ppv()));
		if (!BlockPacket(static_cast<IEnum<LONG> *>(EnumObjs))) {
		// ggf. neues Paket speichern
			m_Objects.push_back(EnumObjs);
		}

		m_itlist = m_Objects.begin();		// jedesmal machen
		m_lPacket = m_Objects.size();

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CLimitPackets::EndAction (DWORD, IDataObject **ppDataObj)
{
HRESULT hr = S_OK;

	if (m_itlist == m_Objects.begin())
		SetMaxTicks (m_Objects.size());		// nur beim ersten mal

	COM_TRY {
	// Ausgabeobjektmenge in Transfer-Objekt
	__Interface<IDataObject> DO (CLSID_DataTransferObject);

		if (m_itlist != m_Objects.end()) {
		// eigentliche Verarbeitung
		WEnumLONG EnumOut (*m_itlist);			// Ausgabeobjektmenge

			THROW_FAILED_HRESULT(PropActBase::SetPacketNumber(DO, m_lPacket--));
			THROW_FAILED_HRESULT(PropActBase::SetEnumObjects (EnumOut, DO));

			++m_itlist;							// der nächste, Bitte
		}
		else {
		// keine Pakete gefunden, die den Kriterien entsprechen
		WEnumLONG EnumOut (CLSID_EnumObjectsByNumber);

			THROW_FAILED_HRESULT(PropActBase::SetEnumObjects (EnumOut, DO));
		}

		hr = (m_itlist == m_Objects.end()) ? S_OK : S_FALSE;
		*ppDataObj = DO.detach();

		if (hr != S_FALSE) 
		{
			DELETE_OBJ (m_pCfgDlg);		// DialogPage freigeben, wenn nichts mehr kommt
		}

	} COM_CATCH_NOASSERT_ON(E_ABORT);
	return hr;
}

/////////////////////////////////////////////////////////////////////////////
// IPersist
STDMETHODIMP CLimitPackets::GetClassID (CLSID *pClsID)
{
	*pClsID = GetObjectCLSID();
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistStreamInit
STDMETHODIMP CLimitPackets::Load (IStream *pStm)
{
	if (IsInitialized())
		return E_UNEXPECTED;

	RETURN_FAILED_HRESULT(CPropertyActionImpl::Load (pStm));
	RETURN_FAILED_HRESULT(LoadData(pStm, m_selData));
	
	SetInitialized();
	return S_OK;
}

STDMETHODIMP CLimitPackets::Save (IStream *pStm, BOOL fClearDirty)
{
	RETURN_FAILED_HRESULT(CPropertyActionImpl::Save (pStm, fClearDirty));
	RETURN_FAILED_HRESULT(SaveData(pStm, m_selData));
	return S_OK;
}

STDMETHODIMP CLimitPackets::GetSizeMax (ULARGE_INTEGER *pcbSize)
{
	if (NULL == pcbSize)
		return E_POINTER;
	pcbSize -> QuadPart = 0L;

	RETURN_FAILED_HRESULT(CPropertyActionImpl::GetSizeMax (pcbSize));

	pcbSize  -> QuadPart += sizeof(LIMITPACKETSDATA);
	return S_OK;
}

STDMETHODIMP CLimitPackets::InitNew()
{
	if (IsInitialized())
		return E_UNEXPECTED;

	m_selData.rgLimit = LIMITPACKETS_None;
	m_selData.lLimitObjs = 0;
	m_selData.lLimitORWnds = 0;

	SetInitialized();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Geokomponente hat eigenen Dialog
STDMETHODIMP CLimitPackets::AddConfigPages (
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

	// zugehörigen ConfigDialog (PropertyPage(s)) anlegen
		DELETE_OBJ(m_pCfgDlg);
		m_pCfgDlg = CLimitPacketsDlg::CreateInstance(cbCaption);
		if (NULL == m_pCfgDlg) _com_issue_error(E_OUTOFMEMORY);

		m_pCfgDlg->PreSelectData(m_selData);

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

STDMETHODIMP CLimitPackets::PreConfigPages (IDataObject *pIDataObject, DWORD dwFlags)
{
	if (NULL == m_pCfgDlg) 
		return E_UNEXPECTED;

	m_pCfgDlg -> SetFlags(dwFlags);
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistPropertyBag
STDMETHODIMP CLimitPackets::Load (IPropertyBag *pBag, IErrorLog *pLog)
{
	USES_CONVERSION;
	RETURN_FAILED_HRESULT(CPropertyActionImpl::Load (pBag, pLog));

	m_selData.rgLimit = LIMITPACKETS_None;
	m_selData.lLimitObjs = 0;
	m_selData.lLimitORWnds = 0;

// LimitOperation=
CComVariant vLimitOperation;
HRESULT hr = pBag -> Read (CComBSTR(g_cbLimitOperation), &vLimitOperation, pLog);

	if (S_OK == hr && SUCCEEDED(vLimitOperation.ChangeType(VT_BSTR))) {
		if (!wcscmp(V_BSTR(&vLimitOperation), g_cbLimitGT)) 
			m_selData.rgLimit = LIMITPACKETS_More;
		else if (!wcscmp(V_BSTR(&vLimitOperation), g_cbLimitGE))
			m_selData.rgLimit = LIMITPACKETS_MoreEqual;
		else if (!wcscmp(V_BSTR(&vLimitOperation), g_cbLimitEQ))
			m_selData.rgLimit = LIMITPACKETS_Equal;
		else if (!wcscmp(V_BSTR(&vLimitOperation), g_cbLimitLE))
			m_selData.rgLimit = LIMITPACKETS_LesserEqual;
		else if (!wcscmp(V_BSTR(&vLimitOperation), g_cbLimitLT))
			m_selData.rgLimit = LIMITPACKETS_Lesser;

	// LimitObjCount=
		if (m_selData.rgLimit != LIMITPACKETS_None) {
		CComVariant vLimitObjCount;
		
			hr = pBag -> Read (CComBSTR(g_cbLimitObjCount), &vLimitObjCount, pLog);
			if (S_OK == hr && SUCCEEDED(vLimitObjCount.ChangeType(VT_I4))) 
				m_selData.lLimitObjs = V_I4(&vLimitObjCount);

			if (0 == m_selData.lLimitObjs)
				m_selData.rgLimit = LIMITPACKETS_None;
		}
	}

// LimitORWndCount=
CComVariant vLimitORWndCount;

	hr = pBag -> Read (CComBSTR(g_cbLimitORWndCount), &vLimitORWndCount, pLog);
	if (S_OK == hr && SUCCEEDED(vLimitORWndCount.ChangeType(VT_I4))) 
		m_selData.lLimitORWnds = V_I4(&vLimitORWndCount);

	return S_OK;
}

