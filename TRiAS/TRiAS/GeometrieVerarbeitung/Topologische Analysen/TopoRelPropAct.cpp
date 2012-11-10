// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 20.12.2002 11:31:12
//
// @doc    PropertyAction für topologische Relationen von GeoObjekten zu einem Bezugsobjekt
// @module TopoRelPropAct.cpp | Implementation of the <c CTopoRelPropAct> class

#include "TopoRelP.hxx"

#include "TopoRelR.h"

#include <triastlb.h>
#include "clsfyprp.h"		// c_feORWndCaption, c_fePAORWndErrMsg

#include "SmartInterfaces.h"
#include "TopoRelPropAct.h"



///////////////////////////////////////////////////////////////////////////////////////////////
// CTopoRelPropAct
// IPropertyAction 

CTopoRelPropAct::CTopoRelPropAct (void)
			   : CPropertyActionImpl (PA_TYPEFLAGS, IDS_DESCRIPTION_TOPORELPROPACT)
{
	// ggf. Erweiterung TopoRel.ext laden
	m_hDex = NULL;
	if (NULL == g_pTE)
	{
	LOADEXTENSIONEX le;

		memset (&le, 0, sizeof (LOADEXTENSIONEX));
		le.m_pDesc = 0;
		le.m_pName = "TRiAS.Topologie.1";
		le.m_iMode = LEFullLoad;
		le.m_fGlobal = TRUE;		
		m_hDex = DEX_ExternalLoadExtensionEx (le);

		_ASSERTE (0 != m_hDex);
	}

	// Member initialisieren
	m_pRelationDlg = NULL;
	m_pMultiRefDlg = NULL;
	m_pTRF = NULL;
	m_bFirstEndAction = true;		// EndAction zum ersten Mal aufgerufen (true)
	m_bIsDirtyRelation = false;		// Parameter von RelationDialog wurden (noch) nicht verändert
	m_bHasInitRelationData = false;	// (noch) keine Initialisierungsdaten für den RelationenDialog
									// von Load() bereitgestellt bzw. schon an diesen weitergereicht
	m_bIsDirtyMultiRef = false;		// Parameter von MultiRefDialog wurden (noch) nicht verändert
	m_bHasInitMultiRefData = false;	// (noch) keine Initialisierungsdaten für den MultiRefDialog
}


// --------------------------------------------------------------------------------------------
CTopoRelPropAct::~CTopoRelPropAct (void)
{
	DELETE_OBJ (m_pRelationDlg);
	DELETE_OBJ (m_pMultiRefDlg);
	DELETE_OBJ (m_pTRF);
}


// --------------------------------------------------------------------------------------------
void CTopoRelPropAct::FinalRelease (void)
{
	if (m_hDex)
	{
	//	Erweiterung TopoRel.ext entladen
	LOADEXTENSIONEX le;

		memset (&le, 0, sizeof (LOADEXTENSIONEX));
		le.m_pDesc = NULL;
		le.m_pName = "TRiAS.Topologie.1";
		le.m_iMode = LENoLoad;
		le.m_fGlobal = TRUE;		
		DEX_ExternalUnLoadExtensionEx (le);
		m_hDex = 0;
	}
} // FinalRelease



///////////////////////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTopoRelPropAct::BeginAction (IProgressIndicator *pIProgInd)
{
	RETURN_FAILED_HRESULT(CPropertyActionImpl::BeginAction (pIProgInd));

	DELETE_OBJ (m_pTRF);
	m_pTRF = new TopoRelFunc();

	if (! m_pTRF)
	{                                                                      
		DEX_Error (RC_TopoRelPropAct, EC_NOMEMORY);
		return E_OUTOFMEMORY;
	}

	// Zustand der Dialoge retten (für evtl. späteres Save())
	RETURN_FAILED_HRESULT(m_pRelationDlg->GetSelectedInfo (&m_caRelationInfo, m_bIsDirtyRelation));
	RETURN_FAILED_HRESULT(m_pMultiRefDlg->GetSelectedInfo (&m_caMultiRefInfo, m_bIsDirtyMultiRef));

	// Listen für Objekte, die an die PropertyPage übergeben werden, leeren
	m_RefObjects.Clear();
	m_AnalyObjects.Clear();

	return S_OK;

} // BeginAction


// --------------------------------------------------------------------------------------------
// Hier bekomme ich alle Objekte angeboten, sowohl die Bezugsobjekte (lPackNumber == 1), als
// auch die zu testenden Objekte (lPackNumber == 2), und sammle sie erst einmal auf.
STDMETHODIMP CTopoRelPropAct::DoAction (IDataObject *pIDataObj, DWORD dwReserved)
{
	// Eingabeobjekte einfach mit zu unserer Objektmenge hinzufügen
	COM_TRY
	{
	WEnumLONG EnumObjs;
	OutEnumLONG iter_ref (&m_RefObjects);
	OutEnumLONG iter_obj (&m_AnalyObjects);
	long lPackNumber;		// Paketnummer

		THROW_FAILED_HRESULT(PropActBase::GetEnumObjects (pIDataObj, __uuidof(IEnumLONG), EnumObjs.ppv()));
		THROW_FAILED_HRESULT(PropActBase::GetPacketNumber (pIDataObj, &lPackNumber));
		if (1 == lPackNumber)	// Bezugsobjekte
			copy (InEnumLONG(EnumObjs), InEnumLONG(), iter_ref);
		else					// zu testende Objekte
			copy (InEnumLONG(EnumObjs), InEnumLONG(), iter_obj);

	}
	COM_CATCH;

	return S_OK;

} // DoAction


// --------------------------------------------------------------------------------------------
// Hier werden 2 Aktionen durchgeführt:
// 1. Die eigentliche Verarbeitung für alle Objekte einschließlich der Anwendung des
//    ProgressIndikator und
// 2. das Weiterreichen der Ausgabeströme.
// Letzteres kann mehrfach notwendig werden, wenn es mehrere zu unterscheidende Ausgabeströme
// gibt (wird durch den Rückgabewert (S_FALSE bzw. S_OK) gesteuert). Die Verarbeitng darf
// dann natürlich nur beim ERSTEN Aufruf von EndAction erfolgen.
STDMETHODIMP CTopoRelPropAct::EndAction (DWORD, IDataObject **ppDataObj)
{
	COM_TRY
	{
		if (m_bFirstEndAction)	// nur beim 1. Aufruf von EndAction
		{
			// ProgressIndikator initialisieren
			SetMaxTicks (m_RefObjects.Count() * m_AnalyObjects.Count());

			// Vorbereitung der Analyse
			THROW_FAILED_HRESULT(m_pRelationDlg->GetSelectedInfo (&m_caRelationInfo, m_bIsDirtyRelation));
			THROW_FAILED_HRESULT(m_pMultiRefDlg->GetSelectedInfo (&m_caMultiRefInfo, m_bIsDirtyMultiRef));
			m_pTRF->SetRefObjectsCount (m_RefObjects.Count());

		// topologische Relation für alle übergebenen Objekte zu jedem Referenzobjekt bestimmen
		InEnumLONG itRefEnd = InEnumLONG();		// Zeiger HINTER das letzte m_RefObjects-Element
		InEnumLONG itAnalyEnd = InEnumLONG();	// Zeiger HINTER das letzte m_AnalyObjects-Element
		bool bFirstRelObj = true;				// Abarbeitung des 1. Referenzobjektes

			for (InEnumLONG itRef = InEnumLONG(&m_RefObjects); itRef != itRefEnd; ++itRef)
			{
				THROW_FAILED_HRESULT(m_pTRF->PrepareAnalysis (itRef, m_caRelationInfo,
															  m_caMultiRefInfo, bFirstRelObj));
		
				for (InEnumLONG itAnaly = InEnumLONG(&m_AnalyObjects); itAnaly != itAnalyEnd; ++itAnaly)
				{
					Tick();				// ProgressIndikator weitersetzen

					if (FAILED(GoOn()))	// Abfrage, ob Operation abgebrochen werden soll
					{
					ErrCode rcDummy;	// Rückkehrcode von DEX_SetError()
					ResourceFile RF (g_pDLLName);
					ResString resText (ResID (IDS_CANCEL, &RF), 100);

						DEX_SetError (rcDummy, 0, WC_MESSAGE_TOPO, (void*)resText.Addr());
						return E_ABORT;
					}

					m_pTRF->GetObjectRelation (*itAnaly);
				}

				if (bFirstRelObj) bFirstRelObj = false;	// Abarbeitung des 1. Referenzobjektes ist beendet
			}

			m_pTRF->CountPackets(m_lPacket);	// Anzahl der Ausgabeströme ermitteln

			m_bstrMessageNoObjects = m_pTRF->MessageNoObjects();
			m_bFirstEndAction = false;
		}

	// Ausgabeobjektmenge in Transfer-Objekt übertragen
	WEnumLONG wEnumOut (CLSID_EnumObjectsByNumber);	// Ausgabeobjektmenge
	WDataObject wDO (CLSID_DataTransferObject);		// Transfer-Objekt
	CComBSTR bstrCapt, bstrColor;
	OGCPosit rgPosition;

		if (m_lPacket > 0)
		{
			m_pTRF->BuildOutputObjects (wEnumOut, bstrCapt, bstrColor, rgPosition);

			THROW_FAILED_HRESULT(PropActBase::SetEnumObjects (wEnumOut, wDO));		// Ausgabeobjektmenge

			THROW_FAILED_HRESULT(PropActBase::SetPacketNumber (wDO, m_lPacket));	// Paketnummer setzen
			THROW_FAILED_HRESULT(PropActBase::SetVariantData (CComVariant(bstrCapt), wDO, &c_feORWndCaption));	// Caption
			THROW_FAILED_HRESULT(PropActBase::SetVariantData (CComVariant(bstrColor), wDO, &c_fePAORWndColor));	// Farbe
			THROW_FAILED_HRESULT(PropActBase::SetVariantData (CComVariant(rgPosition), wDO, &c_feClassifyTopoRelation));	// TopoRelation
		}
		else
		{
			THROW_FAILED_HRESULT(PropActBase::SetEnumObjects (wEnumOut, wDO));		// leere Ausgabeobjektmenge

			THROW_FAILED_HRESULT(PropActBase::SetPacketNumber (wDO, m_lPacket));	// Paketnummer setzen
			THROW_FAILED_HRESULT(PropActBase::SetVariantData (CComVariant(m_bstrMessageNoObjects), wDO, &c_fePAORWndErrMsg));	// Message
		}

		*ppDataObj = wDO.detach();
	}
	COM_CATCH_NOASSERT_ON(E_ABORT);

	DELETE_OBJ (m_pRelationDlg);	// Dialoge freigeben
	DELETE_OBJ (m_pMultiRefDlg);

	if (m_lPacket > 1)
	{
		m_lPacket--;
		return S_FALSE;		// Es kommen noch weitere Objektmengen.
	}

	if (1 == m_lPacket)
	{
		if (m_bstrMessageNoObjects == "")
			return S_OK;	// Das ist die letzte Objektmenge.

		m_lPacket--;
		return S_FALSE;		// Es kommt noch eine leere Objektmenge mit einer Message.
	}
	
	return S_OK;			// Das ist die leere Objektmenge mit einer Message.

} // EndAction


///////////////////////////////////////////////////////////////////////////////////////////////
// IPersist
STDMETHODIMP CTopoRelPropAct::GetClassID (CLSID *pClsID)
{
	*pClsID = GetObjectCLSID();
	return S_OK;
}


///////////////////////////////////////////////////////////////////////////////////////////////
// IPersistStreamInit
STDMETHODIMP CTopoRelPropAct::Load (IStream *pStm)
{
	if (IsInitialized())		// IsInitialized() == true, wenn Page schon durch InitNew()
		return E_UNEXPECTED;	//  initialisiert wurde

	// Load my own data from the stream
	// zuerst Bezeichner einlesen
	RETURN_FAILED_HRESULT(CPropertyActionImpl::Load (pStm));

// meine Versionsnummer lesen und überprüfen
long lVersion = 0;

	RETURN_FAILED_HRESULT(pStm->Read (&lVersion, sizeof(long), NULL));
	if (lVersion > LAST_KNOWN_VERSION)
		return STG_E_OLDDLL;	// File was written with a newer version

	// die zuletzt weggeschriebenen Relationen einlesen
	RETURN_FAILED_HRESULT (pStm->Read (&m_caRelationInfo, sizeof(TOPORELRESULT), NULL));

	// Initialisierungsdaten an den RelationenDialog weiterreichen
	if (m_pRelationDlg)
	{
		RETURN_FAILED_HRESULT (m_pRelationDlg->SetSelectedInfo (&m_caRelationInfo));
	}
	else
		// Initialisierungsdaten für den RelationenDialog wurden zwar soeben von Load()
		// bereitgestellt, können hier aber noch nicht an diesen weitergereicht werden
		m_bHasInitRelationData = true;

	// die zuletzt weggeschriebenen MultiRef-Daten einlesen
	RETURN_FAILED_HRESULT (pStm->Read (&m_caMultiRefInfo, sizeof(MULTIREFRESULT), NULL));

	// Initialisierungsdaten an den MultiRefDialog weiterreichen
	if (m_pMultiRefDlg)
	{
		RETURN_FAILED_HRESULT (m_pMultiRefDlg->SetSelectedInfo (&m_caMultiRefInfo));
	}
	else
		m_bHasInitMultiRefData = true;

	SetInitialized();			// Page wurde jetzt durch Load() initialisiert
	m_bIsDirtyRelation = false;	// Dialogparameter wurden (noch)
	m_bIsDirtyMultiRef = false;	//  nicht verändert
	return S_OK;
	
} // Load


// --------------------------------------------------------------------------------------------
STDMETHODIMP CTopoRelPropAct::Save (IStream *pStm, BOOL bClearDirty)
{
	// Bezeichner wegschreiben
	RETURN_FAILED_HRESULT(CPropertyActionImpl::Save (pStm, bClearDirty));

// Save my own data to the stream
// Version wegschreiben
long lVersion = LAST_KNOWN_VERSION;

	RETURN_FAILED_HRESULT (pStm->Write (&lVersion, sizeof(long), NULL));

	// die zuletzt gesetzten Relationen wegschreiben
	if (m_pRelationDlg)
		RETURN_FAILED_HRESULT (m_pRelationDlg->GetSelectedInfo (&m_caRelationInfo, m_bIsDirtyRelation));
	
	RETURN_FAILED_HRESULT (pStm->Write (&m_caRelationInfo, sizeof(TOPORELRESULT), NULL));

	// die zuletzt gesetzten MultiRef-Daten wegschreiben
	if (m_pMultiRefDlg)
		RETURN_FAILED_HRESULT (m_pMultiRefDlg->GetSelectedInfo (&m_caMultiRefInfo, m_bIsDirtyMultiRef));
	
	RETURN_FAILED_HRESULT (pStm->Write (&m_caMultiRefInfo, sizeof(MULTIREFRESULT), NULL));

	if (bClearDirty)
	{
		m_bIsDirtyRelation = false;
		m_bIsDirtyMultiRef = false;
	}

	return S_OK;

} // Save


// --------------------------------------------------------------------------------------------
// Bestimmen der benötigten Speichergröße für Save()
STDMETHODIMP CTopoRelPropAct::GetSizeMax (ULARGE_INTEGER *pcbSize)
{
	if (NULL == pcbSize)
		return E_POINTER;

	pcbSize -> QuadPart = 0L;

	RETURN_FAILED_HRESULT(CPropertyActionImpl::GetSizeMax (pcbSize));

	// Add the size of my data to pcbSize
	pcbSize  -> QuadPart += sizeof(TOPORELRESULT) + sizeof(MULTIREFRESULT);

	return S_OK;

} // GetSizeMax


// --------------------------------------------------------------------------------------------
STDMETHODIMP CTopoRelPropAct::InitNew()
{
	if (IsInitialized())		// IsInitialized() == true, wenn Page schon durch Load()
		return E_UNEXPECTED;	//  initialisiert wurde

	// Initialisierung der Dialoge
	m_caRelationInfo.ulSelRelat = WITH;
	m_caRelationInfo.bSepaWin = TRUE;
	m_caMultiRefInfo.iReferenceType = Least;
	m_caMultiRefInfo.iRefListIndex = 0;
	m_caMultiRefInfo.lLimitCnt = 1;
	
	// Initialisierungsdaten an den RelationenDialog weiterreichen
	if (m_pRelationDlg)
	{
		RETURN_FAILED_HRESULT (m_pRelationDlg->SetSelectedInfo (&m_caRelationInfo));
	}
	else
		// Initialisierungsdaten für den RelationenDialog wurden zwar soeben von InitNew()
		// bereitgestellt, können hier aber noch nicht an diesen weitergereicht werden
		m_bHasInitRelationData = true;

	// Initialisierungsdaten an den MultiRefDialog weiterreichen
	if (m_pMultiRefDlg)
	{
		RETURN_FAILED_HRESULT (m_pMultiRefDlg->SetSelectedInfo (&m_caMultiRefInfo));
	}
	else
		// Initialisierungsdaten für den MultiRefDialog wurden zwar soeben von InitNew()
		// bereitgestellt, können hier aber noch nicht an diesen weitergereicht werden
		m_bHasInitMultiRefData = true;

	SetInitialized();			// Page wurde jetzt durch InitNew() initialisiert
	m_bIsDirtyRelation = false;	// Dialogparameter wurden (noch)
	m_bIsDirtyMultiRef = false;	//  nicht verändert
	return S_OK;

} // InitNew


///////////////////////////////////////////////////////////////////////////////////////////////
// IPersistPropertyBag
// Einstellungen für Initialisierung der Dialoge aus der XML-Datei lesen
STDMETHODIMP CTopoRelPropAct::Load (IPropertyBag *pBag, IErrorLog *pLog)
{
	RETURN_FAILED_HRESULT(CPropertyActionImpl::Load (pBag, pLog));	// Load der Basisklasse

	// default-Einstellungen für Initialisierung der Dialoge
	m_caRelationInfo.ulSelRelat = WITH;
	m_caRelationInfo.bSepaWin = TRUE;
	m_caMultiRefInfo.iReferenceType = Least;
	m_caMultiRefInfo.iRefListIndex = 0;
	m_caMultiRefInfo.lLimitCnt = 1;

// Parameter aus XML-Datei auswerten
// SelectedRelations
CComVariant vSelectedRelations;
HRESULT hr = pBag -> Read (CComBSTR(c_cbSelectedRelations), &vSelectedRelations, pLog);

	if (S_OK == hr && SUCCEEDED(vSelectedRelations.ChangeType(VT_I4))) 
		m_caRelationInfo.ulSelRelat = V_I4(&vSelectedRelations);

// SeparateWindows
CComVariant vSeparateWindows;

	hr = pBag -> Read (CComBSTR(c_cbSeparateWindows), &vSeparateWindows, pLog);
	if (S_OK == hr && SUCCEEDED(vSeparateWindows.ChangeType(VT_BOOL))) 
		m_caRelationInfo.bSepaWin = V_BOOL(&vSeparateWindows) ? true : false;

// MultiReferenceType
CComVariant vMultiReferenceType;

	hr = pBag -> Read (CComBSTR(c_cbMultiReferenceType), &vMultiReferenceType, pLog);
	if (S_OK == hr && SUCCEEDED(vMultiReferenceType.ChangeType(VT_BSTR))) 
	{
		USES_CONVERSION;	// legt _convert für OLE2A() an

	string strMultiReferenceType = OLE2A(V_BSTR(&vMultiReferenceType));

		if ("All" == strMultiReferenceType)
			m_caMultiRefInfo.iReferenceType = 1;
		else if ("Least" == strMultiReferenceType.c_str())
			m_caMultiRefInfo.iReferenceType = 2;
		else if ("Most" == strMultiReferenceType.c_str())
			m_caMultiRefInfo.iReferenceType = 3;
		else if ("Exact" == strMultiReferenceType)
			m_caMultiRefInfo.iReferenceType = 4;
	}

// RefListIndex
	switch (m_caMultiRefInfo.iReferenceType)
	{
		case All:
		{
		CComVariant vRefListIndex;

			hr = pBag -> Read (CComBSTR(c_cbRefListIndex), &vRefListIndex, pLog);
			if (S_OK == hr && SUCCEEDED(vRefListIndex.ChangeType(VT_I2))) 
				m_caMultiRefInfo.iRefListIndex = V_I2(&vRefListIndex);
			break;
		}

		case Least:
			m_caMultiRefInfo.iRefListIndex = 0;
			break;

		case Most:
			m_caMultiRefInfo.iRefListIndex = 1;
			break;

		case Exact:
			m_caMultiRefInfo.iRefListIndex = 2;
	}

// LimitCounter
CComVariant vLimitCounter;

	hr = pBag -> Read (CComBSTR(c_cbLimitCounter), &vLimitCounter, pLog);
	if (S_OK == hr && SUCCEEDED(vLimitCounter.ChangeType(VT_I4))) 
		m_caMultiRefInfo.lLimitCnt = V_I4(&vLimitCounter);

	// Initialisierungsdaten für die Dialoge wurden zwar soeben von Load() bereitgestellt,
	// können hier aber noch nicht an diese weitergereicht werden
	m_bHasInitRelationData = true;
	m_bHasInitMultiRefData = true;
	return S_OK;
	
} // Load


///////////////////////////////////////////////////////////////////////////////////////////////
// GeoKomponente hat eigenen Dialog
STDMETHODIMP CTopoRelPropAct::AddConfigPages (LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam,
											  LPCSTR pcDesc, UINT *puiCnt)
{
	if (puiCnt) *puiCnt = 0;	// initialisieren

	COM_TRY
	{
	char cbCaption[128];

		if (NULL != pcDesc)	{	// Caption ist gegeben
			_ASSERTE(strlen(pcDesc) < sizeof(cbCaption));
			strcpy (cbCaption, pcDesc);
		} else	// von zugehöriger ClassProperty unseren Namen besorgen
			GetPropInfo (cbCaption, sizeof(cbCaption), NULL);

		// zugehörige Dialoge (PropertyPage(s)) anlegen
		DELETE_OBJ (m_pRelationDlg);
		m_pRelationDlg = CTopoRelDlg::CreateInstance(cbCaption);
		if (NULL == m_pRelationDlg) _com_issue_error(E_OUTOFMEMORY);

		DELETE_OBJ (m_pMultiRefDlg);
		m_pMultiRefDlg = CTopoRelRefDlg::CreateInstance(cbCaption);
		if (NULL == m_pMultiRefDlg) _com_issue_error(E_OUTOFMEMORY);

		if (!IsNoShow())
		{
		// Seite für Optionen hizufügen
		HPROPSHEETPAGE hPSP = m_pRelationDlg->CreatePage ();

			if (NULL == hPSP) return E_HANDLE;
			if (!(*lpfnAddPage) (hPSP, lParam))
				return E_FAIL;

			// Seite für Behandlung mehrerer Bezugsobjekte hizufügen
			hPSP = m_pMultiRefDlg->CreatePage ();

			if (NULL == hPSP) return E_HANDLE;
			if (!(*lpfnAddPage) (hPSP, lParam))
				return E_FAIL;

			if (puiCnt) *puiCnt = 2;	// es wurden 2 Pages hinzugefügt
		}

		// Initialisierungsdaten für den RelationenDialog wurden von Load() bereitgestellt,
		// konnten aber noch nicht an diesen weitergereicht werden
		if (m_bHasInitRelationData)
			// Initialisierungsdaten jetzt an den RelationenDialog weiterreichen
			THROW_FAILED_HRESULT(m_pRelationDlg->SetSelectedInfo (&m_caRelationInfo, IsNoShow()));

		// Initialisierungsdaten für den MultiRefDialog wurden von Load() bereitgestellt,
		// konnten aber noch nicht an diesen weitergereicht werden
		if (m_bHasInitMultiRefData)
			// Initialisierungsdaten jetzt an den MultiRefDialog weiterreichen
			THROW_FAILED_HRESULT(m_pMultiRefDlg->SetSelectedInfo (&m_caMultiRefInfo, IsNoShow()));
	}
	COM_CATCH_OP(DELETE_OBJ (m_pRelationDlg); DELETE_OBJ (m_pMultiRefDlg));

	return S_OK;

} // AddConfigPages


// --------------------------------------------------------------------------------------------
STDMETHODIMP CTopoRelPropAct::PreConfigPages (IDataObject *pIDataObject, DWORD dwFlags)
{
	if (NULL == m_pRelationDlg || NULL == m_pMultiRefDlg) 
		return E_UNEXPECTED;

	m_pRelationDlg -> SetFlags(dwFlags & ~ADDPAGES_LASTPAGE);	// als "nicht letzte Seite" kennzeichnen
	m_pMultiRefDlg -> SetFlags(dwFlags & ~ADDPAGES_FIRSTPAGE);	// als "nicht erste Seite" kennzeichnen
	return S_OK;
}
