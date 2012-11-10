// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 27.01.2003 08:38:45
//
// @doc
// @module CodeLine.cpp | Implementation of the <c CCodeLine> class

#include "stdafx.h"

#include <TRiASHelper.h>

#include <xtsnguid.h>

#include "errorcode.h"
#include "relkey.h"

#include "LineTools.h"
#include "LineToolsUtil.h"

#include "CodeLine.h"
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

//
extern "C"  Bool PASCAL _XTENSN_EXPORT FillIDListBox (long , Bool , void *);

/////////////////////////////////////////////////////////////////////////////
// CCodeLine
// IPropertyAction 

STDMETHODIMP CCodeLine::BeginAction (IProgressIndicator *pIProgInd)
{
	RETURN_FAILED_HRESULT(CPropertyActionImpl::BeginAction (pIProgInd));
	m_Objects.Clear();
	return S_OK;
}

STDMETHODIMP CCodeLine::DoAction (IDataObject *pIDataObj, DWORD dwReserved)
{

	m_iErrorCode = m_pCfgDlg->GetErrorCode();


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
	class CCodeLineWorker 
	{
	public:
		CCodeLineWorker(OutEnumLONG &rOutIter, CCodeLine *pThis) : 
			m_pPA(pThis), m_rOutIter(rOutIter), m_rCodeLineAction(*pThis)
		{
		}
		~CCodeLineWorker() {}

	// wird für jedes zu bearbeitende Objekt gerufen
		void operator() (LONG lONr)
		{
			_ASSERTE(NULL != m_pPA);
			m_pPA -> Tick();			// ProgressIndikator weitersetzen
			if (FAILED(m_pPA -> GoOn()))
				_com_issue_error(E_ABORT);

		// TODO: Add your own precessing here

			int iError = m_rCodeLineAction.ErrorCode();

			int iCode = 0;				// Idents, die geprüft sind

			CLineStatus Object (lONr, iError,m_rCodeLineAction.CheckFeature() );

			if ( Object.isValid() )  {

				if ( Object.ErrorCode() & LINE_NOTCONTROL)	// Falls Objekte unreferenziert, Klassen merken !!
					m_rCodeLineAction.AddIdent(Object.Ident(),iCode);

				m_rOutIter++ = lONr;		// object is added to the output collections
			}

		}

	private:
		IProgressIndicatorUsage *m_pPA;
		OutEnumLONG &m_rOutIter;
		CCodeLine& m_rCodeLineAction;
	};
} // namespace

STDMETHODIMP CCodeLine::EndAction (DWORD, IDataObject **ppDataObj)
{
	COM_TRY {
	// ProgressIndikator initialisieren
		SetMaxTicks (m_Objects.Count());

	if ( !m_pIdents) {
		m_pIdents = new TR_ObjTree();
	}


	// eigentliche Verarbeitung
	WEnumLONG EnumOut (CLSID_EnumObjectsByNumber);				// Ausgabeobjektmenge

		{
		OutEnumLONG iter_out (static_cast<IEnum<LONG> *>(EnumOut));

			for_each(InEnumLONG(&m_Objects), InEnumLONG(), CCodeLineWorker(iter_out, this));
		} // iter_out goes out of scope

	// Ausgabeobjektmenge in Transfer-Objekt setzen
	__Interface<IDataObject> DO (CLSID_DataTransferObject);

		THROW_FAILED_HRESULT(PropActBase::SetEnumObjects (EnumOut, DO));
		*ppDataObj = DO.detach();


	// Bei Suche nach unreferenzierten Straßen Rest außerhalb der Sicht [Datenbank/Datenquellen] analysieren !!!
		if ( m_pIdents->Count() > 0 ) {

		//	Alle O'Klassen formal durchzählen und Baum anlegen
			ENUMNOKEYLONG ENT;
		//	Bestimmen der Anzahl der Objektklassen

			ENT.eFcn = ( ENUMTEXTKEYPROC) FillIDListBox;

	
			ENT.ePtr = this;

			DEX_EnumIdents(ENT);

			if (IsOtherClass ()) {	// Andere unreferenzierte Klassen

				CString strCaption;
				CString strMessage;

				VERIFY(strCaption.LoadString(IDS_DESCRIPTION_CODELINE));
				VERIFY(strMessage.LoadString(IDS_TESTUNREF));
				AfxGetMainWnd()->MessageBox (strMessage, strCaption, MB_OK | MB_ICONERROR);

			}
				
		}

		DELETE_OBJ(m_pIdents);

	// DialogPage freigeben

		if (NULL != m_pCfgDlg) {
			delete m_pCfgDlg;
			m_pCfgDlg = NULL;
		}

	} COM_CATCH_NOASSERT_ON(E_ABORT);
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersist
STDMETHODIMP CCodeLine::GetClassID (CLSID *pClsID)
{
	*pClsID = GetObjectCLSID();
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistStreamInit
STDMETHODIMP CCodeLine::Load (IStream *pStm)
{
	if (IsInitialized())
		return E_UNEXPECTED;

	RETURN_FAILED_HRESULT(CPropertyActionImpl::Load (pStm));

// TODO: Load your own data from the stream
	SetInitialized();
	return S_OK;
}

STDMETHODIMP CCodeLine::Save (IStream *pStm, BOOL fClearDirty)
{
	RETURN_FAILED_HRESULT(CPropertyActionImpl::Save (pStm, fClearDirty));

// TODO: Save your own data to the stream
	return S_OK;
}

STDMETHODIMP CCodeLine::GetSizeMax (ULARGE_INTEGER *pcbSize)
{
	if (NULL == pcbSize)
		return E_POINTER;
	pcbSize -> QuadPart = 0L;

	RETURN_FAILED_HRESULT(CPropertyActionImpl::GetSizeMax (pcbSize));

// TODO: Add the size of your data to pcbSize
//	pcbSize  -> QuadPart += ...;
	return S_OK;
}

STDMETHODIMP CCodeLine::InitNew()
{
	if (IsInitialized())
		return E_UNEXPECTED;

// TODO: initialize your data
	SetInitialized();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Geokomponente hat eigenen Dialog
STDMETHODIMP CCodeLine::AddConfigPages (
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
		m_pCfgDlg = CCodeLineDlg::CreateInstance(cbCaption);
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
////////////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CCodeLine::PreConfigPages (IDataObject *pIDataObject, DWORD dwFlags)
{
	if (NULL == m_pCfgDlg) 
		return E_UNEXPECTED;

	m_pCfgDlg -> SetFlags(dwFlags);

	THROW_FAILED_HRESULT(PreConfigData());

	if ( m_bstrGCO == "")		//Keine Definitionen übergeben
		THROW_FAILED_HRESULT(SetSingleConfigData());	// Definitionen aus Parameterübergabe bzw. Ressource


	m_pCfgDlg -> SetConfigData(m_bstrGCO);

	return S_OK;
}
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CCodeLine::PreConfigData (void)
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
STDMETHODIMP CCodeLine::InitConfigDataFromRegistry(UINT IDLink,UINT IDGCO,UINT IDOriginal,UINT IDError)
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
STDMETHODIMP CCodeLine::SetSingleConfigData (void)
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
///////////////////////////////////////////////////////////////////////////////
bool CCodeLine::AddIdent(long lIdent,int iErrorCode)
{
	if (lIdent == 0)
		return false;

	if ( !m_pIdents)
		m_pIdents = new TR_ObjTree();

	CTable t (*m_pIdents);

//	int iErrorCode = 0;

	if (!t.Find (&lIdent)) {

		TR_OBJECTSCreator OSCr (*m_pIdents);

		ContCreate(OSCr, TR_OBJECTS)(lIdent,iErrorCode);
	}


	return true;

}
/////////////////////////////////////////////////////////////////////////////////

bool CCodeLine::IsOtherClass (void)
{

	CTable t (*m_pIdents);

	for ( t.First(); t.Valid(); t.Next()) {

		TR_OBJECTSLock l(t);

		if ( !l)
			continue;

		if ( l->ErrorCode()) {
			return true;
		}
	}

	return false;
}
///////////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------------------------
extern "C"  Bool PASCAL _XTENSN_EXPORT FillIDListBox (long lIdent, Bool , void *pData)
{


	HPROJECT hPr = DEX_GetObjectsProject (lIdent);

	//	ID besorgen
	char NewIdent[MAX_OKS_LENX+1];

	ClassFromIdentX ( hPr,lIdent, NewIdent,strlen(NewIdent));

	char *cptr = strrchr(NewIdent,'\0');

	int iCode = 1;

	if ( cptr) {
		cptr--;
		if ( *cptr == '0' || *cptr == '2' || *cptr == '3' ) 	// nicht referenzierte Klassen
			((CCodeLine *)pData) -> AddIdent (lIdent,iCode);

	}

	return TRUE;

}

//---------------------------------------------------------------------------------------
