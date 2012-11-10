// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 28.01.2003 11:54:08
//
// @doc
// @module ClsfyByCode.cpp | Implementation of the <c CClsfyByCode> class

#include "stdafx.h"
#include <TRiASHelper.h>

#include <xtsnguid.h>

#include "errorcode.h"
#include "relkey.h"

#include "LineTools.h"
#include "LineToolsUtil.h"

#include "ClsfyByCode.h"

#include <KoOrd.h>
#include <IPropSeq.hxx>

#include <Errcodes.hxx>
#include <errinstx.hxx>
#include <Xtensnn.h>

#include <hpp/datahelp.hpp>

#include <CLSFYPRP.H>

#include <registrx.hxx>

// SmartIF's
DefineSmartInterface(ObjectWithSite);
DefineSmartInterface(PropertyActionSequence);
DefineSmartInterface(DataObject);
DefineEnumOutputIterator(LONG);		// definiert OutEnumLONG

////////////////////////////////////////////////////////////////////////////

// Registrierung

static LPCTSTR g_cbBNA	= TEXT("Software\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY "\\%s");


/////////////////////////////////////////////////////////////////////////////
// CClsfyByCode
// IPropertyAction 

STDMETHODIMP CClsfyByCode::BeginAction (IProgressIndicator *pIProgInd)
{
	RETURN_FAILED_HRESULT(CPropertyActionImpl::BeginAction (pIProgInd));
	m_Objects.Clear();
	return S_OK;
}

STDMETHODIMP CClsfyByCode::DoAction (IDataObject *pIDataObj, DWORD dwReserved)
{

	m_iAreaCtrl = m_pCfgDlg->GetAreaCode();


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
	class CClsfyByCodeWorker 
	{
	public:
		CClsfyByCodeWorker(OutEnumLONG &rOutIter, CClsfyByCode *pThis) : 
			m_pPA(pThis), m_rOutIter(rOutIter), m_rCodeAction(*pThis)
		{
		}
		~CClsfyByCodeWorker() {}

		bool StoreObjTree ( const char *pKey,long lONr);

	// wird für jedes zu bearbeitende Objekt gerufen
		void operator() (LONG lONr)
		{
			_ASSERTE(NULL != m_pPA);
			m_pPA -> Tick();			// ProgressIndikator weitersetzen
			if (FAILED(m_pPA -> GoOn()))
				_com_issue_error(E_ABORT);

			m_pMesh = m_rCodeAction.Mesh();

		// TODO: Add your own precessing here


			CObjectPipe Object ( lONr,m_rCodeAction.LinkFeature(),m_rCodeAction.AreaType(), m_rCodeAction.Index());

			if ( Object.isValid() ) 
				StoreObjTree (Object.Key().c_str(),lONr);


		}

	private:
		IProgressIndicatorUsage *m_pPA;
		OutEnumLONG &m_rOutIter;
		CClsfyByCode& m_rCodeAction;
		TR_MESHTree * m_pMesh;
	};
} // namespace
/////////////////////////////////////////////////////////////////////////////////////////////
// Baum der Konfigurationsdaten 
bool CClsfyByCodeWorker::StoreObjTree (const char * pKey,long lONr) 
{

	if (m_pMesh == NULL) {
		return false;
	}

	CTable t (*m_pMesh);

	if (!t.Find ((void *)pKey)) {

		TR_MESHCreator OSCr (*m_pMesh);

		return ContCreate(OSCr, TR_MESH)(pKey, lONr) != NULL;

	} else {

		TR_MESHLock l(t);
		if (l)
			l->AddObject ( lONr);

	}

	return false;

}
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
string CClsfyByCode :: LinkFeature ( void)
{

	USES_CONVERSION;
	string sLink =  W2A(m_bstrGCO);
	return sLink;
}
////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
void DeleteKey ( TR_MESHTree *pMesh, char * pKey)
{

	CTable t(*pMesh);

	if ( t.Find((void *) pKey)) {
		t.Delete();
	}

	return;

}

/////////////////////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CClsfyByCode::EndAction (DWORD, IDataObject **ppDataObj)
{

	long lPacket = 0;


	COM_TRY {
	// ProgressIndikator initialisieren
		SetMaxTicks (m_Objects.Count());

	// eigentliche Verarbeitung
	WEnumLONG EnumOut (CLSID_EnumObjectsByNumber);				// Ausgabeobjektmenge


	bool iFirst = false;
	if ( !m_pMesh) {
		m_pMesh = new TR_MESHTree();
		iFirst = true;
	}


		{
		OutEnumLONG iter_out (static_cast<IEnum<LONG> *>(EnumOut));

		if ( iFirst) {
			for_each(InEnumLONG(&m_Objects), InEnumLONG(), CClsfyByCodeWorker(iter_out, this));
			m_lPacket = m_pMesh->Count();
		}

			if ( m_pMesh && m_pMesh->Count() > 0 ) {

				EndActionTree(m_pMesh , iter_out);
				ResetActionTree();

			}


		} // iter_out goes out of scope

		lPacket = m_lPacket--;				// Paketnummer rückwärts zählen

	// Ausgabeobjektmenge in Transfer-Objekt setzen
	__Interface<IDataObject> DO (CLSID_DataTransferObject);

		THROW_FAILED_HRESULT(PropActBase::SetEnumObjects (EnumOut, DO));

		if ( lPacket > 0 ) {

			PropActBase::SetPacketNumber(DO, lPacket);

			SetPacketCaption(DO,lPacket);
			SetPacketFeature (DO);
		}


		*ppDataObj = DO.detach();

	// DialogPage freigeben
		if (NULL != m_pCfgDlg) {
			delete m_pCfgDlg;
			m_pCfgDlg = NULL;
		}

	} COM_CATCH_NOASSERT_ON(E_ABORT);

	if ( m_pMesh->Count() == 0) {
		DELETE_OBJ(m_pMesh);
		return S_OK;
	}

	return S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////////

STDMETHODIMP CClsfyByCode::ResetActionTree (void)
{

	USES_CONVERSION;

	DeleteKey(m_pMesh, W2A(m_bstrKey));

//	m_bstrKey.Empty();

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////////

STDMETHODIMP CClsfyByCode::EndActionTree (TR_MESHTree *pMesh, OutEnumLONG &rOutIter)
{

	COM_TRY {

		CTable t (*pMesh);

		for ( t.First(); t.Valid(); t.Next()) {
			TR_MESHLock l(t);
			if ( !l)
				continue;

			m_bstrKey.Empty();

			if ( l->GetObj() != NULL) {

				put_Objects(l->GetObj(),rOutIter);
				m_bstrKey = l->Key();
				return S_OK;

			}

		}


	} COM_CATCH_NOASSERT_ON(E_ABORT);

	return S_OK;
}
///////////////////////////////////////////////////////////////////////////////////
bool CClsfyByCode :: put_Objects( TR_ObjTree *pObj, OutEnumLONG &rOutIter)
{

	if ( !pObj)
		return false;

	CTable t (*pObj);

	for ( t.First(); t.Valid(); t.Next()) {
		TR_OBJECTSLock l(t);
		if ( !l)
			continue;
		rOutIter++ = l->Object();			// alle restlichen Daten raus
	}

	return true;

}

/////////////////////////////////////////////////////////////////////////////
// IPersist
STDMETHODIMP CClsfyByCode::GetClassID (CLSID *pClsID)
{
	*pClsID = GetObjectCLSID();
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistStreamInit
STDMETHODIMP CClsfyByCode::Load (IStream *pStm)
{
	if (IsInitialized())
		return E_UNEXPECTED;

	RETURN_FAILED_HRESULT(CPropertyActionImpl::Load (pStm));
	RETURN_FAILED_HRESULT(LoadData(pStm, m_iListIndex));

// TODO: Load your own data from the stream
	SetInitialized();
	return S_OK;
}

STDMETHODIMP CClsfyByCode::Save (IStream *pStm, BOOL fClearDirty)
{
	RETURN_FAILED_HRESULT(CPropertyActionImpl::Save (pStm, fClearDirty));
	RETURN_FAILED_HRESULT(SaveData(pStm, m_iListIndex));

// TODO: Save your own data to the stream
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistPropertyBag
STDMETHODIMP CClsfyByCode::Load (IPropertyBag *pBag, IErrorLog *pLog)
{
	USES_CONVERSION;
	RETURN_FAILED_HRESULT(CPropertyActionImpl::Load (pBag, pLog));

// ListIndex=
CComVariant vListIndex;
HRESULT hr = pBag -> Read (CComBSTR(L"ListIndex"), &vListIndex, pLog);

// ListIndex = 0 - Punkt, 1 - Linie/Fläche, 2 - Beide
	m_iListIndex = 0;
	//
	if (S_OK == hr && SUCCEEDED(vListIndex.ChangeType(VT_I2))) 
		m_iListIndex = V_I2(&vListIndex);

	return S_OK;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////


STDMETHODIMP CClsfyByCode::GetSizeMax (ULARGE_INTEGER *pcbSize)
{
	if (NULL == pcbSize)
		return E_POINTER;
	pcbSize -> QuadPart = 0L;

	RETURN_FAILED_HRESULT(CPropertyActionImpl::GetSizeMax (pcbSize));

// TODO: Add the size of your data to pcbSize
//	pcbSize  -> QuadPart += ...;
	return S_OK;
}

STDMETHODIMP CClsfyByCode::InitNew()
{
	if (IsInitialized())
		return E_UNEXPECTED;

// TODO: initialize your data
	SetInitialized();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Geokomponente hat eigenen Dialog
STDMETHODIMP CClsfyByCode::AddConfigPages (
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
		m_pCfgDlg = CClsfyByCodeDlg::CreateInstance(cbCaption);
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
	} COM_CATCH_OP((delete m_pCfgDlg, m_pCfgDlg = NULL));
	return S_OK;
}  

STDMETHODIMP CClsfyByCode::PreConfigPages (IDataObject *pIDataObject, DWORD dwFlags)
{
	if (NULL == m_pCfgDlg) 
		return E_UNEXPECTED;

	m_pCfgDlg -> SetFlags(dwFlags);

	THROW_FAILED_HRESULT(PreConfigData());

	if ( m_bstrGCO == "")		//Keine Definitionen übergeben
		THROW_FAILED_HRESULT(SetSingleConfigData());	// Definitionen aus Parameterübergabe bzw. Ressource

	m_pCfgDlg -> SetConfigData(m_bstrGCO,m_iListIndex);

	return S_OK;
}
///////////////////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CClsfyByCode::PreConfigData (void)
{


	CString sLF;
	CString sGCO;
	CString sECF;
	CString sGCAV;
	CString sGCOriginal;

	sGCO.LoadString(IDS_GCOCODE);

	sLF.LoadString(IDS_LINKFEATURE);			// MW - kann GCO-Code sein, später GUID

	sGCOriginal.LoadString(IDS_GCORIGINAL);

	sECF.LoadString(IDS_ERRORCODEFEATURE);

	sGCAV.LoadString(IDS_GCAVORSPANN);


	COM_TRY {
////////////////////////////////////////////////// Link //////////////////////////////////////
	FORMATETC c_feSABiS = 	{
			RegisterClipboardFormat (sLF),	// CLIPFORMAT cf
			NULL,											// DVTARGETDEVICE *ptd
			DVASPECT_CONTENT,								// DWORD dwAspect
			-1,												// LONG lindex	
			TYMED_ISTREAM,									// DWORD tymed
		};

	WDataObject DO;
	WPropertyActionSequence Seq;

		THROW_FAILED_HRESULT(WObjectWithSite(GetUnknown()) -> GetSite (IID_IPropertyActionSequence, Seq.ppv()));
		THROW_FAILED_HRESULT(Seq -> GetSequenceContext (DO.ppi()));


	CComVariant vData;

//------------------------SABIS-Link-------------------------------------
		THROW_FAILED_HRESULT(GetVariantData ( DO, &c_feSABiS, &vData));

		if ( SUCCEEDED(vData.ChangeType (VT_BSTR)))
		{
			m_bstrLink = V_BSTR(&vData);
		}

////////////////////////////////////////////////// GCO //////////////////////////////////////
	FORMATETC c_feGCO = 	{
			RegisterClipboardFormat (sGCO),	// CLIPFORMAT cf
			NULL,											// DVTARGETDEVICE *ptd
			DVASPECT_CONTENT,								// DWORD dwAspect
			-1,												// LONG lindex	
			TYMED_ISTREAM,									// DWORD tymed
		};


//------------------------GCO-Code-------------------------------------
		THROW_FAILED_HRESULT(GetVariantData ( DO, &c_feGCO, &vData));

		if ( SUCCEEDED(vData.ChangeType (VT_BSTR)))
		{
			m_bstrGCO = V_BSTR(&vData);
		}

//-------------------------ErrorFeld-------------------------------------
//////////////////////////////////////////////////Error///////////////////////////////////////////////
	 FORMATETC c_feSABiSError = 	{
			RegisterClipboardFormat (sECF),	// CLIPFORMAT cf
			NULL,											// DVTARGETDEVICE *ptd
			DVASPECT_CONTENT,								// DWORD dwAspect
			-1,												// LONG lindex	
			TYMED_ISTREAM,									// DWORD tymed
		};


		THROW_FAILED_HRESULT(GetVariantData ( DO, &c_feSABiSError, &vData));

		if ( SUCCEEDED(vData.ChangeType (VT_BSTR)))
		{
			m_bstrError = V_BSTR(&vData);
		}
//-------------------------GCA-Vorspann-------------------------------------
/////////////////////////////////////////////GCA-Vorspann///////////////////////////
	 FORMATETC c_feSABiSGCA = 	{
			RegisterClipboardFormat (sGCAV),	// CLIPFORMAT cf
			NULL,											// DVTARGETDEVICE *ptd
			DVASPECT_CONTENT,								// DWORD dwAspect
			-1,												// LONG lindex	
			TYMED_ISTREAM,									// DWORD tymed
		};


		THROW_FAILED_HRESULT(GetVariantData ( DO, &c_feSABiSGCA, &vData));

		if ( SUCCEEDED(vData.ChangeType (VT_BSTR)))
		{
			m_bstrGCA = V_BSTR(&vData);
		}

//-------------------------GCO Original-------------------------------------
///////////////////////////////////////////////////////////////////////////
	 FORMATETC c_feOriginal = 	{
			RegisterClipboardFormat (sGCOriginal),	// CLIPFORMAT cf
			NULL,											// DVTARGETDEVICE *ptd
			DVASPECT_CONTENT,								// DWORD dwAspect
			-1,												// LONG lindex	
			TYMED_ISTREAM,									// DWORD tymed
		};


		THROW_FAILED_HRESULT(GetVariantData ( DO, &c_feOriginal, &vData));

		if ( SUCCEEDED(vData.ChangeType (VT_BSTR)))
		{
			m_bstrGCOriginal = V_BSTR(&vData);
		}



	} COM_CATCH;

	return S_OK;
}
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CClsfyByCode::InitConfigDataFromRegistry(UINT IDLink,UINT IDGCO,UINT IDOriginal,UINT IDError)
{

	TCHAR szBNAKey[_MAX_PATH];

	USES_CONVERSION;

	CComBSTR Projekt;
	Projekt.LoadString(IDS_PROJECTLAYER);
	

//	wsprintf(szBNAKey,g_cbBNA,REG_COMPANY_KEY,REG_PRODUCT_KEY,W2A(Projekt));

	wsprintf(szBNAKey,g_cbBNA,W2A(Projekt));	// TRiAS Technology

	CCurrentUser rgMass(szBNAKey, true);


	CComBSTR Link;
	Link.LoadString (IDLink);				// Koppelbegriff

	CComBSTR GCO;
	GCO.LoadString (IDGCO);				// GCO-Koppelbegriff

	CComBSTR Original;
	Link.LoadString (IDOriginal);			// GCO Original

	CComBSTR Error;
	Error.LoadString (IDError);				// Fehlerattribut

	TCHAR pRef[_MAX_PATH];


	// Link
	DWORD dW = 50;

	rgMass.GetSubSZ ((LPCTSTR )W2A(Link), pRef, dW);
	if ( dW > 0 )
		m_bstrLink = pRef;

	// GCO
	dW = 50;

	rgMass.GetSubSZ ((LPCTSTR )W2A(GCO), pRef, dW);
	if ( dW > 0 )
		m_bstrGCO = pRef;

	// Fehlerattribut
	dW = 50;

	rgMass.GetSubSZ ((LPCTSTR )W2A(Error),pRef, dW);
	if ( dW > 0 )
		m_bstrError = pRef;

	// GCO Original
	dW = 50;

	rgMass.GetSubSZ ((LPCTSTR )W2A(Original),pRef, dW);
	if ( dW > 0 )
		m_bstrGCOriginal = pRef;

	return S_OK;

}
///////////////////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CClsfyByCode::SetSingleConfigData (void)
{

	CString sLF;
	CString sLF_Code;
	CString sGCO;
	CString sGCO_Code;
	CString sO;
	CString sO_Code;
	CString sECF;
	CString sECF_Code;

	sLF.LoadString(IDS_LINKFEATURE);
	sLF_Code.LoadString(IDS_LINKFEATUREKEY);

	sGCO.LoadString(IDS_GCOCODE);
	sGCO_Code.LoadString(IDS_GCOCODEKEY);

	sO.LoadString(IDS_GCORIGINAL);
	sO_Code.LoadString(IDS_GCORIGINALKEY);

	sECF.LoadString(IDS_ERRORCODEFEATURE);
	sECF_Code.LoadString(IDS_ERRORCODEFEATUREKEY);

	m_bstrError.Empty();
	m_bstrGCO.Empty();
	m_bstrLink.Empty();
	m_bstrGCOriginal.Empty();

	THROW_FAILED_HRESULT(InitConfigDataFromRegistry(IDS_LINKFEATURE,IDS_GCOCODE,IDS_GCORIGINAL,IDS_ERRORCODEFEATURE));

	if ( m_bstrError.Length() < 1)
		m_bstrError = sECF_Code;

	if ( m_bstrGCO.Length() < 1)
		m_bstrGCO = sGCO_Code;

	if ( m_bstrGCOriginal.Length() < 1)
		m_bstrGCOriginal = sO_Code;

	if ( m_bstrLink.Length() < 1)
		m_bstrLink = sLF_Code;


////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////// Parameterauswertung ///////////////////////////////////////////////////////

	if ( m_bstrParmGCO.Length() > 2)
		m_bstrGCO = m_bstrParmGCO;

	if ( m_bstrParmOriginal.Length() > 2)
		m_bstrGCOriginal = m_bstrParmOriginal;



////////////////////////////////////////////////////////////////////////////////////////////////////


	COM_TRY {
/////////////////////////////////////////LINK////////////////////////////////////////////////////////
		FORMATETC c_feSABiS = 	{
		RegisterClipboardFormat (sLF),	// CLIPFORMAT cf
		NULL,											// DVTARGETDEVICE *ptd
		DVASPECT_CONTENT,								// DWORD dwAspect
		-1,												// LONG lindex	
		TYMED_ISTREAM,									// DWORD tymed
		};

		WDataObject DO;
		WPropertyActionSequence Seq;

		THROW_FAILED_HRESULT(WObjectWithSite(GetUnknown()) -> GetSite (IID_IPropertyActionSequence, Seq.ppv()));
		THROW_FAILED_HRESULT(Seq -> GetSequenceContext (DO.ppi()));


		CComVariant vData (m_bstrLink);

		THROW_FAILED_HRESULT(SetVariantData (vData, DO, &c_feSABiS));

/////////////////////////////////GCO-Code//////////////////////////////////////////////////////////////////
		FORMATETC c_feGCO = 	{
		RegisterClipboardFormat (sGCO),	// CLIPFORMAT cf
		NULL,											// DVTARGETDEVICE *ptd
		DVASPECT_CONTENT,								// DWORD dwAspect
		-1,												// LONG lindex	
		TYMED_ISTREAM,									// DWORD tymed
		};


		CComVariant vDataO (m_bstrGCO);

		THROW_FAILED_HRESULT(SetVariantData (vDataO, DO, &c_feGCO));
/////////////////////////////////GCO Original//////////////////////////////////////////////////////////////////
		FORMATETC c_feOriginal = 	{
		RegisterClipboardFormat (sO),	// CLIPFORMAT cf
		NULL,											// DVTARGETDEVICE *ptd
		DVASPECT_CONTENT,								// DWORD dwAspect
		-1,												// LONG lindex	
		TYMED_ISTREAM,									// DWORD tymed
		};


		CComVariant vDataOR (m_bstrGCOriginal);

		THROW_FAILED_HRESULT(SetVariantData (vDataOR, DO, &c_feOriginal));

////////////////////////////////////ERROR////////////////////////////////////////////////////////////////
		FORMATETC c_feSABiSError = 	{
			RegisterClipboardFormat (sECF),	// CLIPFORMAT cf
			NULL,											// DVTARGETDEVICE *ptd
			DVASPECT_CONTENT,								// DWORD dwAspect
			-1,												// LONG lindex	
			TYMED_ISTREAM,									// DWORD tymed
		};

		CComVariant vDataE (m_bstrError);

		THROW_FAILED_HRESULT(SetVariantData (vDataE, DO, &c_feSABiSError));


	} COM_CATCH;
	

	return S_OK;
}
////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
	HRESULT CClsfyByCode::SetPacketFeature (IDataObject *pIDO )
	{

		CComVariant vData (m_bstrKey);

//		c_feClassifyObjects
		RETURN_FAILED_HRESULT(PropActBase::SetVariantData(vData, pIDO, &c_feClassifyValue));

		return S_OK;
	}

///////////////////////////////////////////////////////////////////////////////////////////////
	HRESULT CClsfyByCode::SetPacketCaption (IDataObject *pIDO, long lPacket )
	{
		CComVariant vData (m_bstrKey);

		RETURN_FAILED_HRESULT(SetVariantData(vData, pIDO, &c_feORWndCaption));

		return S_OK;
	}


////////////////////////////////////////////////////////////////////////////////////////////////(

///////////////////////////////////////////////////////////////////////////////////////
