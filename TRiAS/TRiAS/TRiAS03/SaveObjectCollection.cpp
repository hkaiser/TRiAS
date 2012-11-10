// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 09.12.2002 09:00:07
//
// @doc
// @module SaveObjectCollection.cpp | Implementation of the <c CSaveObjectCollection> class

#include "trias03p.hxx"
#include "trias03.h"
#include "obj32/trias323.rcv"

#include <Com/MkHelper.h>
#include <Com/SummaryProp.h>
#include <clsfyprp.h>

#include "datahelp.h"
#include "SaveObjectCollection.h"

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TRiASObject);
DefineSmartInterface(Moniker);
DefineSmartInterface(Storage);
DefineSmartInterface(Stream);
DefineSmartInterface(PropertySetStorage);
DefineSmartInterface(PropertyStorage);

/////////////////////////////////////////////////////////////////////////////
// CSaveObjectCollection
// IPropertyAction 

STDMETHODIMP CSaveObjectCollection::BeginAction (IProgressIndicator *pIProgInd)
{
	RETURN_FAILED_HRESULT(CPropertyActionImpl::BeginAction (pIProgInd));
	m_Objects.clear();
	m_itlist = m_Objects.begin();
	m_lPacket = 0;
	return S_OK;
}

STDMETHODIMP CSaveObjectCollection::DoAction (IDataObject *pIDataObj, DWORD dwReserved)
{
// Eingabeobjekte einfach mit zu unserer Objektmenge hinzufügen
	COM_TRY {
	// neues Paket speichern
		m_Objects.push_back(CListOfPackets::value_type());

	CListOfPackets::reference packetref (m_Objects.back());
	SEnumLONG &Enum = packetref.first;

	// Objekte kopieren
	WEnumLONG EnumObjs;
	OutEnumLONG iter_out_if (&Enum);

		THROW_FAILED_HRESULT(PropActBase::GetEnumObjects (pIDataObj, __uuidof(IEnumLONG), EnumObjs.ppv()));
		copy (InEnumLONG(EnumObjs), InEnumLONG(), iter_out_if);

		m_itlist = m_Objects.begin();		// jedesmal machen
		m_lPacket = m_Objects.size();

	// evtl. Caption des ORFensters besorgen
	CComVariant vCap;

		USES_CONVERSION;
		if (S_OK == PropActBase::GetVariantData(pIDataObj, const_cast<FORMATETC *>(&c_feORWndCaption), &vCap) &&
			SUCCEEDED(vCap.ChangeType(VT_BSTR)))
		{ 
			m_Objects.back().second = OLE2A(V_BSTR(&vCap));
		}

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Stream initialisieren
HRESULT CSaveObjectCollection::InitStream (long lCnt)
{
	COM_TRY {
		if (m_CfgData.m_fSaveInProject) {
			_ASSERTE(!m_CfgData.m_fSaveInProject);		// E_NOTIMPL
		}
		else {
		WStorage Stg;
		WStream Strm;
		DWORD rgMode = STGM_DIRECT|STGM_READWRITE|STGM_SHARE_EXCLUSIVE|STGM_CREATE;
		
			RETURN_FAILED_HRESULT(StgCreateDocfile(
				CComBSTR(m_CfgData.m_strSaveAs.c_str()), rgMode, 0L, Stg.ppi()));
			RETURN_FAILED_HRESULT(WriteClassStg(Stg, GetObjectCLSID()));
			RETURN_FAILED_HRESULT(WriteFmtUserTypeStg(Stg, GetClipFormat(), GetUserType()));
			RETURN_FAILED_HRESULT(Stg -> CreateStream(GetSubStreamName(), rgMode, 0L, 0L, Strm.ppi()));

		// eigentliche Daten speichern
			RETURN_FAILED_HRESULT(SaveData(Strm, OBJECTCOLL_SIGNATURE));
			RETURN_FAILED_HRESULT(SaveData(Strm, OBJECTCOLL_LASTKNOWNVERSION));
			RETURN_FAILED_HRESULT(SaveData(Strm, lCnt));		// Anzahl der Objektmengen

		// jetzt noch PropertySet schreiben
			RETURN_FAILED_HRESULT(SavePropertySet(Stg, rgMode));
		}

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Stream (wieder-)öffnen
HRESULT CSaveObjectCollection::ReOpenStream (IStream **ppIStm)
{
	COM_TRY {
		if (m_CfgData.m_fSaveInProject) {
			_ASSERTE(!m_CfgData.m_fSaveInProject);		// E_NOTIMPL
		}
		else {

		}

	} COM_CATCH;
	return S_OK;
}

namespace {

///////////////////////////////////////////////////////////////////////////////
// Klasse, die die Verarbeitung der einzelnen Objekte der Eingabemenge erlaubt
	class CSaveObjectCollectionWorker 
	{
	public:
		CSaveObjectCollectionWorker(OutEnumLONG &rOutIter, IStream *pIStm) : 
			m_rOutIter(rOutIter), m_Strm(pIStm)
		{
			_ASSERTE(m_Strm.IsValid());
		}
		~CSaveObjectCollectionWorker() {}

	// wird für jedes zu bearbeitende Objekt gerufen
		void operator() (LONG lONr)
		{
		QUERYCOMOBJECT QCO;
		WTRiASObject Obj;

			INITSTRUCT(QCO, QUERYCOMOBJECT);
			QCO.hObject = lONr;
			QCO.piid = &IID_ITRiASObject;
			QCO.ppIUnk = Obj.ppu();
			if (SUCCEEDED(DEX_GetObjectPtr(QCO))) {
			// MonikerName (DisplayName) in den Stream wegschreiben
			WMoniker Mk;
			CComBSTR bstrMkName;
			
				THROW_FAILED_HRESULT(MkGetMoniker (Obj, OLEGETMONIKER_FORCEASSIGN, OLEWHICHMK_OBJFULL, Mk.ppi()));
				THROW_FAILED_HRESULT(MkGetDisplayName(Mk, &bstrMkName, NULL));
				THROW_FAILED_HRESULT(m_Strm -> Write(bstrMkName, bstrMkName.Length()*sizeof(OLECHAR), NULL));

				m_rOutIter++ = lONr;		// object is added to the output collection
			}
		}

	private:
		OutEnumLONG &m_rOutIter;
		WStream m_Strm;
	};

} // namespace

///////////////////////////////////////////////////////////////////////////////
// 
STDMETHODIMP CSaveObjectCollection::EndAction (DWORD, IDataObject **ppDataObj)
{
HRESULT hr = S_OK;

	COM_TRY {
	// wenn mindestens eine Objektmenge vorhanden ist, dann darf nach der letzten
	// Objektmenge kein Aufruf mehr erfolgen
		_ASSERTE(0 == m_Objects.size() || m_itlist != m_Objects.end());

		if (m_itlist == m_Objects.begin()) {
		// beim ersten mal den ProgressIndicator ...
			SetMaxTicks(m_Objects.size());

		// ... und den Stream initialisieren
			THROW_FAILED_HRESULT(InitStream(m_Objects.size()));
		}

	// Ausgabeobjektmenge in Transfer-Objekt
	__Interface<IDataObject> DO (CLSID_DataTransferObject);

	// eigentliche Verarbeitung
	WEnumLONG EnumOut (CLSID_EnumObjectsByNumber);		// Ausgabeobjektmenge

		if (m_itlist != m_Objects.end()) {
		// Stream (wieder-)öffnen und diverses reinschreiben
		WStream Strm;

			THROW_FAILED_HRESULT(ReOpenStream(Strm.ppi()));

		// nächste Objektmenge in den Stream wegschreiben
		OutEnumLONG iter_out (static_cast<IEnum<LONG> *>(EnumOut));
		size_t uiCnt = (*m_itlist).first.Count();

			THROW_FAILED_HRESULT(Strm->Write(&uiCnt, sizeof(size_t), NULL));
			THROW_FAILED_HRESULT(Strm->Write(&m_lPacket, sizeof(long), NULL));

			for_each(InEnumLONG(&(*m_itlist).first), InEnumLONG(), 
				CSaveObjectCollectionWorker(iter_out, Strm));

			++m_itlist;								// der nächste, Bitte
			hr = (m_itlist == m_Objects.end()) ? S_OK : S_FALSE;

			THROW_FAILED_HRESULT(PropActBase::SetPacketNumber(DO, m_lPacket--));
			THROW_FAILED_HRESULT(Strm->Commit(STGC_DEFAULT));
		}

		THROW_FAILED_HRESULT(PropActBase::SetEnumObjects (EnumOut, DO));
		*ppDataObj = DO.detach();

		Tick();					// ProgressIndikator weitersetzen
		if (FAILED(GoOn()))
			hr = E_ABORT;

		if (hr != S_FALSE) 
		{
			DELETE_OBJ (m_pCfgDlg);		// DialogPage freigeben, wenn nichts mehr kommt
		}

	} COM_CATCH_NOASSERT_ON(E_ABORT);
	return hr;
}

/////////////////////////////////////////////////////////////////////////////
// IPersist
STDMETHODIMP CSaveObjectCollection::GetClassID (CLSID *pClsID)
{
	*pClsID = GetObjectCLSID();
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistStreamInit
STDMETHODIMP CSaveObjectCollection::Load (IStream *pStm)
{
	if (IsInitialized())
		return E_UNEXPECTED;

DWORD dwSignature = 0;
DWORD dwVersion = 0;

	LoadData(pStm, dwSignature);
	if (dwSignature != SAVEOBJCOLL_SIGNATURE)
		return E_UNEXPECTED;
	LoadData(pStm, dwVersion);
	if ((dwVersion & ~SAVEOBJCOLL_MINORVERSIONMASK) > SAVEOBJCOLL_LASTKNOWNVERSION)
		return STG_E_OLDDLL;

	RETURN_FAILED_HRESULT(CPropertyActionImpl::Load (pStm));

	LoadData(pStm, m_CfgData.m_fSaveInProject);
	LoadString(pStm, m_CfgData.m_strSaveAs);

	SetInitialized();
	return S_OK;
}

STDMETHODIMP CSaveObjectCollection::Save (IStream *pStm, BOOL fClearDirty)
{
	SaveData(pStm, SAVEOBJCOLL_SIGNATURE);
	SaveData(pStm, SAVEOBJCOLL_LASTKNOWNVERSION);

	RETURN_FAILED_HRESULT(CPropertyActionImpl::Save (pStm, fClearDirty));

	SaveData(pStm, m_CfgData.m_fSaveInProject);
	SaveString(pStm, m_CfgData.m_strSaveAs);
	return S_OK;
}

STDMETHODIMP CSaveObjectCollection::GetSizeMax (ULARGE_INTEGER *pcbSize)
{
	if (NULL == pcbSize)
		return E_POINTER;
	pcbSize -> QuadPart = 0L;

	RETURN_FAILED_HRESULT(CPropertyActionImpl::GetSizeMax (pcbSize));

	pcbSize -> QuadPart += 2*sizeof(DWORD) + sizeof(bool) +
		::GetSizeMax(m_CfgData.m_strSaveAs);
	return S_OK;
}

STDMETHODIMP CSaveObjectCollection::InitNew()
{
	if (IsInitialized())
		return E_UNEXPECTED;

	TidySaveData(m_CfgData);

	SetInitialized();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Geokomponente hat eigenen Dialog
STDMETHODIMP CSaveObjectCollection::AddConfigPages (
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
		if (NULL != m_pCfgDlg) delete m_pCfgDlg;
		m_pCfgDlg = CSaveObjectCollectionDlg::CreateInstance(cbCaption);
		if (NULL == m_pCfgDlg) _com_issue_error(E_OUTOFMEMORY);

		if (!IsNoShow()) {
		// Seite hizufügen, wenn selbige angezeigt werden soll
		HPROPSHEETPAGE hPSP = this -> CreatePage(m_pCfgDlg);

			if (NULL == hPSP) return E_HANDLE;
			if (!(*lpfnAddPage) (hPSP, lParam))
				return E_FAIL;

			if (puiCnt) *puiCnt = 1;		// wir haben eine Page hinzugefügt
		} 

		m_pCfgDlg->SetData(m_CfgData);

	} COM_CATCH_OP((delete m_pCfgDlg, m_pCfgDlg = NULL));
	return S_OK;
}  

STDMETHODIMP CSaveObjectCollection::PreConfigPages (IDataObject *pIDataObject, DWORD dwFlags)
{
	if (NULL == m_pCfgDlg) 
		return E_UNEXPECTED;

	m_pCfgDlg -> SetFlags(dwFlags);
	return S_OK;
}

// IPersistPropertyBag
STDMETHODIMP CSaveObjectCollection::Load (IPropertyBag *pBag, IErrorLog *pLog)
{
	USES_CONVERSION;
	RETURN_FAILED_HRESULT(CPropertyActionImpl::Load (pBag, pLog));

// SaveAs=
HRESULT hr = S_OK;
CComVariant vSaveAs;

	TidySaveData(m_CfgData);
	hr = pBag -> Read (CComBSTR("SaveAs"), &vSaveAs, pLog);
	if (S_OK == hr && SUCCEEDED(vSaveAs.ChangeType(VT_BSTR))) 
		m_CfgData.m_strSaveAs = OLE2A(V_BSTR(&vSaveAs));

// SaveToProject=
CComVariant vSaveToProject;

	hr = pBag -> Read (CComBSTR("SaveToProject"), &vSaveToProject, pLog);
	if (S_OK == hr && SUCCEEDED(vSaveToProject.ChangeType(VT_BOOL))) 
		m_CfgData.m_fSaveInProject = V_BOOL(&vSaveToProject);

	return S_OK;
}

HRESULT CSaveObjectCollection::SavePropertySet(IStorage *pIStg, DWORD rgMode)
{
	COM_TRY {
	// Mode richten
		rgMode &= ~(STGM_SHARE_DENY_NONE|STGM_SHARE_DENY_READ|STGM_SHARE_DENY_WRITE);
		rgMode |= STGM_SHARE_EXCLUSIVE;

	// PropertySet neu erzeugen
	WPropertySetStorage PropSet (pIStg);

		{
		WPropertyStorage PropStg;

			THROW_FAILED_HRESULT(PropSet -> Create(FMTID_SummaryInformation, NULL,
				PROPSETFLAG_DEFAULT, rgMode | STGM_CREATE, PropStg.ppi()));

		// Title schreiben
		CSummaryProp vAppName (PIDSI_APPNAME, VER_PRODUCTNAME_STR);

			THROW_FAILED_HRESULT(vAppName.WriteToPropertyStorage(PropStg));

		// Erzeugt am
		PROPVARIANT propLastSaved;

			V_VT(&propLastSaved) = VT_FILETIME;
			CoFileTimeNow(&propLastSaved.filetime);

		CSummaryProp vLastSaved (PIDSI_CREATE_DTM, propLastSaved);

				THROW_FAILED_HRESULT(vLastSaved.WriteToPropertyStorage(PropStg));

		// Erzeugt von
		char cbBuffer[_MAX_PATH+1];
		ULONG ulLen = sizeof(cbBuffer);

			if (::GetUserName (cbBuffer, &ulLen)) {
			CSummaryProp vAuthor (PIDSI_AUTHOR, cbBuffer);

				THROW_FAILED_HRESULT(vAuthor.WriteToPropertyStorage(PropStg));
			}

		// alles wegschreiben
			THROW_FAILED_HRESULT(PropStg -> Commit(STGC_DEFAULT));
		}

	} COM_CATCH;
	return S_OK;
}

