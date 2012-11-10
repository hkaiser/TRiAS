// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 06.11.2002 09:34:38
//
// @doc
// @module CodeCheck.cpp | Implementation of the <c CCodeCheck> class

#include "stdafx.h"

#include <TRiASHelper.h>

#include <xtsnguid.h>


#include "errorcode.h"

#include "relkey.h"
#include "LineTools.h"
#include "CodeCheck.h"
#include <IPropSeq.hxx>

#include <KoOrd.h>

#include <Errcodes.hxx>
#include <errinstx.hxx>
#include <Xtensnn.h>
#include "LineToolsExt.h"

#include <hpp/datahelp.hpp>
#include <TRIAS03M.HXX>

#include <registrx.hxx>

///////////////////////////////////////////////////////////////////////////////
// strings laden/schreiben
_TRIAS03_ENTRY HRESULT LoadString (IStream *pIStm, os_string &rStr);
_TRIAS03_ENTRY HRESULT SaveString (IStream *pIStm, os_string str);
_TRIAS03_ENTRY DWORD GetSizeMax (os_string &rStr);


long ErrorCountMap[] = {0,0,0,0,0,0,0};
long ErrorCodeMap[] = {GCS_NOTHING,GCS_SYNTAX,GCS_DUPLICATE,GCS_OTHER,GI_DUPLICATE,GI_MULTI};
UINT ErrorKeyMap [] = { IDS_ERRORKEY01,IDS_ERRORKEY02,IDS_ERRORKEY03,IDS_ERRORKEY04,IDS_ERRORKEY05,IDS_ERRORKEY06};

long lMapEnd = sizeof(ErrorCodeMap)/sizeof(ErrorCodeMap[0]);
long lMapCountEnd = sizeof(ErrorCountMap)/sizeof(ErrorCountMap[0]);

//////////////////////////////////////////////////////////////////////////

// SmartIF's
DefineSmartInterface(ObjectWithSite);
DefineSmartInterface(PropertyActionSequence);
DefineSmartInterface(DataObject);
DefineEnumOutputIterator(LONG);		// definiert OutEnumLONG

////////////////////////////////////////////////////////////////////////////

// Registrierung

static LPCTSTR g_cbBNA	= TEXT("Software\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY "\\%s");

/////////////////////////////////////////////////////////////////////////////
// CCodeCheck
// IPropertyAction 

STDMETHODIMP CCodeCheck::BeginAction (IProgressIndicator *pIProgInd)
{
	RETURN_FAILED_HRESULT(CPropertyActionImpl::BeginAction (pIProgInd));
	m_Objects.Clear();
	return S_OK;
}

STDMETHODIMP CCodeCheck::DoAction (IDataObject *pIDataObj, DWORD dwReserved)
{

	THROW_FAILED_HRESULT(PreConfigData());


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
	class CCodeCheckWorker 
	{
	public:
		CCodeCheckWorker(OutEnumLONG &rOutIter, CCodeCheck *pThis, CCodeCheck& rCodeCheckAction) : 
			m_pPA(pThis), m_rOutIter(rOutIter), m_rCodeCheckAction(rCodeCheckAction)
		{
		}
		~CCodeCheckWorker() {}

		bool StoreGCSKeyTree (const char *pKey, const char *pWert, int iErrorCode, long lONr);

//------------------------------------------------------------------------------------------

	// wird für jedes zu bearbeitende Objekt gerufen
		void operator() (LONG lONr)
		{
			_ASSERTE(NULL != m_pPA);
			m_pPA -> Tick();			// ProgressIndikator weitersetzen
			if (FAILED(m_pPA -> GoOn()))
				_com_issue_error(E_ABORT);

		// TODO: Add your own precessing here
		// Hier Baum zum sammeln aufnehmen



			int m_bErrorCode = GCS_NOTHING | GCS_SYNTAX | GCS_DUPLICATE | GCS_OTHER | GI_DUPLICATE | GI_MULTI;

			m_rCodeCheckAction.ResetErrorCode ( lONr,m_bErrorCode);		// Code zurücksetzen !

			m_pStreet = m_rCodeCheckAction.Street();

			
			CObjectDefine Object ( lONr, m_bErrorCode, m_rCodeCheckAction.LinkFeature(), m_rCodeCheckAction.LinkOriginal());

			if ( Object.isValid() ) {
				m_rCodeCheckAction.SetCodeInformation(lONr, Object.ErrorCode());
				m_rOutIter++ = lONr;		// object is added to the output collections
			} else {
				StoreGCSKeyTree (Object.GCS().c_str(),Object.Guid().c_str(),  Object.ErrorCode(), lONr);
			}


		}
//--------------------------------------------------------------------------------------------
	private:
		IProgressIndicatorUsage *m_pPA;
		OutEnumLONG &m_rOutIter;
		CCodeCheck& m_rCodeCheckAction;
		TR_STREETSTree * m_pStreet;
	};

} // namespace

///////////////////////////////////////////////////////////////////////////////////

// Baum der Konfigurationsdaten 
bool CCodeCheckWorker::StoreGCSKeyTree (const char *pKey, const char *pWert, int iErrorCode, long lONr) 
{

	if (m_pStreet == NULL) {
			return false;
	}

	CTable t (*m_pStreet);

	if (!t.Find ((void *)pKey)) {

		TR_STREETSCreator OSCr (*m_pStreet);

// Hier GCSCode,Guid,...
		return ContCreate(OSCr, TR_STREETS)(pKey, pWert, iErrorCode, lONr) != NULL;

	} else {

		TR_STREETSLock l(t);

//		lErrorCode = lErrorCode | GCS_DUPLICATE;

		int iErr = l->ErrorCode();
		iErr = iErr | GCS_DUPLICATE;		// Fehlercode um doppelten Code ergänzen
		l->SetErrorCode(iErr);
		m_rCodeCheckAction.SetCodeInformation(l->Object(),iErr);

		iErrorCode = iErrorCode  | GCS_DUPLICATE;

		l->AddObject(lONr,iErrorCode );
		m_rCodeCheckAction.SetCodeInformation(lONr, iErrorCode);


		return true;
	}

	return false;

}
////////////////////////////////////////////////////////////////////////////////
string CCodeCheck :: LinkFeature ( void)
{

	USES_CONVERSION;
	string sLink =  W2A(m_bstrGCO);
	return sLink;
}
////////////////////////////////////////////////////////////////////////////////
string CCodeCheck :: LinkOriginal ( void)
{

	USES_CONVERSION;
	string sLink =  W2A(m_bstrGCOriginal);
	return sLink;
}

/////////////////////////////////////////////////////////////////////////////////
void CCodeCheck :: SetCodeInformation ( long lONr, int iErrorCode)
{
	if ( 0 == lONr || -1 == lONr)
		return;

	GetMCodeUserName(lONr);
	GetMCodeErrorCode(lONr);

	SetUserName(lONr);
	SetErrorCode(lONr,iErrorCode);

}
/////////////////////////////////////////////////////////////////////////////////
void CCodeCheck::GetMCodeUserName(long lONr)
{

	if ( 0 == lONr || -1 == lONr)
		return;

	CString UserName;
	UserName.LoadString (IDS_DBUSERNAME);

	// Test, ob OE bereits definiert

	HPROJECT hPr = DEX_GetObjectProject(lONr);
	m_lUserName = DEX_GetMCodeFromFeatureNameEx(hPr,(LPCSTR)UserName);

	if ( 0 == m_lUserName ) {
		m_lUserName = DEX_GetUniqueSysMCode ();
		SetPBDMCode( m_lUserName, lONr,(LPCSTR)UserName);
	}

	return;
}
/////////////////////////////////////////////////////////////////////////////////
void CCodeCheck::GetMCodeErrorCode(long lONr)
{

	if ( 0 == lONr || -1 == lONr)
		return;

	CString ECode;

	USES_CONVERSION;

	if (m_bstrError.Length() > 0)
		ECode = W2A(m_bstrError);
	else
		ECode.LoadString (IDS_ERRORCODEFEATUREKEY);

	// Test, ob OE bereits definiert
	HPROJECT hPr = DEX_GetObjectProject(lONr);
	m_lErrorCode = DEX_GetMCodeFromFeatureNameEx(hPr,(LPCSTR)ECode);

	if ( 0 == m_lErrorCode ) {
		m_lErrorCode = DEX_GetUniqueSysMCode ();
		SetPBDMCode( m_lErrorCode, lONr,(LPCSTR)ECode);
	}

//Merkmal Fehlertext 
	CString SCode;
	SCode.LoadString(IDS_ERRORCODESTRING);
	ECode = ECode + SCode;
	long lErrorCode = DEX_GetMCodeFromFeatureNameEx(hPr,(LPCSTR)ECode);
	m_bstrErrorText = ECode;

	if ( 0 == lErrorCode ) {
		lErrorCode = DEX_GetUniqueSysMCode ();
		SetPBDMCode( lErrorCode, lONr,(LPCSTR)ECode);
	}


	return;
}

///////////////////////////////////////////////////////////////////////////////////
void CCodeCheck::SetPBDMCode(ULONG lMCode, long lONr,const char * pData)

{
	if ( 0 == lONr || -1 == lONr)
		return;
	if ( 0 == lMCode)
		return;

	PBDMERKMALEX pbdData;
	memset (&pbdData, '\0', sizeof(PBDMERKMALEX));
	pbdData.dwSize = sizeof(PBDMERKMALEX);
	
	HPROJECT hPr = DEX_GetObjectProject(lONr);

	pbdData.pbdTyp = 'm';
	pbdData.pbdCode = lMCode;
	pbdData.pbdKTextLen = strlen(pData);
	pbdData.pbdLTextLen = 0;
	pbdData.pbdKText = (char *)pData;

//	pbdData.ipbdMTyp = MPObjectFeature | PBDMERKMAL_SYSTEMFLAG | PBDMERKMAL_READONLY;	// so tun, als ob's nur für Objekte wär
	pbdData.ipbdMTyp = MPObjectFeature | PBDMERKMAL_READONLY;	// so tun, als ob's nur für Objekte wär
	pbdData.ipbdMLen = 256;
	pbdData.lIdent = DEX_GetObjIdent(lONr);


	{
		ErrInstall EI (WC_NOMERKMAL);
		if (DEX_ModPBDDataEx (hPr,pbdData) == EC_OKAY)
			DEXN_PBDMCodeChanged (lMCode);
	}

}
//////////////////////////////////////////////////////////////////////////////////////

void CCodeCheck::SetUserName(long lONr)
{

	if ( 0 == lONr || -1 == lONr)
		return;

	if ( 0 == m_lUserName)
		return;

	TARGETMERKMAL TM;
	memset ( &TM, '\0', sizeof ( TARGETMERKMAL) );	
	TM.dwSize = sizeof (TARGETMERKMAL);
	TM.lTarget = lONr;
	TM.lMCode = (long) m_lUserName;
	TM.imaxLen = strlen((const char *)cUserName);
	TM.iTTyp = TT_Objekt;
	TM.pMText = &cUserName[0];

	DEX_ModTextMerkmal ( TM );

}
//////////////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------------------
bool CCodeCheck::GetTRiASUserName (void)
{
	// Bearbeiter
//	TCHAR cUserName[UNLEN + 1];
	DWORD nSize = UNLEN + 1;

	return GetUserName ( cUserName,&nSize);
}
//////////////////////////////////////////////////////////////////////////////////////

void CCodeCheck::ResetErrorCode(long lONr, int iError)
{

	if ( 0 == lONr || -1 == lONr)
		return;

//	if ( 0 == m_lErrorCode)
		GetMCodeErrorCode(lONr);

	if ( 0 == m_lErrorCode)
		return;

	char buffer[_MAX_PATH];


	TARGETMERKMAL TM;
	memset ( &TM, '\0', sizeof ( TARGETMERKMAL) );	
	TM.dwSize = sizeof (TARGETMERKMAL);
	TM.lTarget = lONr;
	TM.lMCode = (long) m_lErrorCode;
	TM.imaxLen = _MAX_PATH-1;
	TM.iTTyp = TT_Objekt;
	TM.pMText = &buffer[0];

	if ( !DEX_GetTextMerkmal ( TM )) 
		return;

	int iRefError = atoi(buffer);
//	int iResult = iRefError ^ iError;
	int iResult = iRefError & ~iError;

	itoa( iResult, buffer, 10 );

	TM.lTarget = lONr;
	TM.lMCode = (long) m_lErrorCode;
	TM.iTTyp = TT_Objekt;
	if ( iResult == 0) {
		TM.imaxLen = 0;
		TM.pMText = NULL;
	} else {
		TM.imaxLen = strlen((const char *)buffer);
		TM.pMText = &buffer[0];
	}

	DEX_ModTextMerkmal ( TM );

	if ( m_bstrErrorText.Length() > 1) {
		SetErrorCodeText(lONr,iResult);
	}

}

//////////////////////////////////////////////////////////////////////////////////////

void CCodeCheck::SetErrorCode(long lONr, int iError)
{

	if ( 0 == lONr || -1 == lONr)
		return;

	if ( 0 == m_lErrorCode)
		return;

	char buffer[_MAX_PATH];


	int iResult = 0;

	TARGETMERKMAL TM;
	memset ( &TM, '\0', sizeof ( TARGETMERKMAL) );	
	TM.dwSize = sizeof (TARGETMERKMAL);
	TM.lTarget = lONr;
	TM.lMCode = (long) m_lErrorCode;
	TM.imaxLen = _MAX_PATH-1;
	TM.iTTyp = TT_Objekt;
	TM.pMText = &buffer[0];

	if ( !DEX_GetTextMerkmal ( TM )) {
		itoa( iError, buffer, 10 );
		iResult = iError;
	} else {
		int iRefErr = atoi(buffer);
		iResult = iRefErr | iError;
		itoa( iResult, buffer, 10 );
	}

	TM.lMCode = (long) m_lErrorCode;
	TM.imaxLen = strlen((const char *)buffer);
	TM.iTTyp = TT_Objekt;
	TM.pMText = &buffer[0];
	DEX_ModTextMerkmal ( TM );

	if ( m_bstrErrorText.Length() > 1) {
		SetErrorCodeText(lONr,iResult);
	}

}
/////////////////////////////////////////////////////////////////////////////////
void CCodeCheck::SetErrorCodeText(long lONr, int iError)
{

	if ( 0 == lONr || -1 == lONr)
		return;

	if ( m_bstrErrorText.Length() < 1)
		return;

	USES_CONVERSION;

	HPROJECT hPr = DEX_GetObjectProject(lONr);
	long lErrorCode = DEX_GetMCodeFromFeatureNameEx(hPr,W2A(m_bstrErrorText));
	if ( lErrorCode == 0)
		return;

	TARGETMERKMAL TM;
	memset ( &TM, '\0', sizeof ( TARGETMERKMAL) );	
	TM.dwSize = sizeof (TARGETMERKMAL);
	TM.lTarget = lONr;

	TM.lMCode = (long) lErrorCode;
	TM.iTTyp = TT_Objekt;

	char *pBuffer = GetErrorText(iError);

	if ( pBuffer )
		TM.imaxLen = strlen(pBuffer);
	else
		TM.imaxLen = 0;

	TM.pMText = pBuffer;

	DEX_ModTextMerkmal ( TM );

	DELETE_OBJ(pBuffer);


}
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
char *CCodeCheck :: GetErrorText ( int iError)
{

	long lErrorCode = 0;
	long lNumber = 0;
	char * sText = new char [_MAX_PATH];
	if ( !sText) 
		return NULL;
	*sText = '\0';
	CString FText;

	long ie = _countof (ErrorCodeMap );
	for (long i = 0; i < ie; i++) {

		lErrorCode = ErrorCodeMap[i];

		if ( lErrorCode & (long)iError) {		// Abgleich gefunder zu gesuchter Fehlercode

			if ( lNumber > 0)
				strcat(sText,"/");

			FText.LoadString(ErrorKeyMap[i]);

			strcat(sText,(LPCTSTR) FText);
			lNumber++;
		}

	}

	if ( *sText != '\0')
		return sText;

	DELETE_OBJ(sText);

	return NULL;

}
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CCodeCheck::EndActionTree (TR_STREETSTree *pStreet, OutEnumLONG &rOutIter)
{
	COM_TRY {
		CTable t (*pStreet);

		for ( t.First(); t.Valid(); t.Next()) {
			TR_STREETSLock l(t);
			if ( !l)
				continue;

			int iErrorCode = GCS_DUPLICATE;

			int  iError = l->ErrorCode();

			if ( iError & iErrorCode) {
	// UserName und FehlerCode als Feature vorbereiten
				SetCodeInformation(l->Object(),iErrorCode);

//				rOutIter++ = l->Object();
			}
			
			rOutIter++ = l->Object();			// alle restlichen Daten raus
			if ( l->GetDupObj() != NULL)
				put_DuplicateObjects(l->GetDupObj(),rOutIter);
		}


	} COM_CATCH_NOASSERT_ON(E_ABORT);
	return S_OK;
}
///////////////////////////////////////////////////////////////////////////////////
bool CCodeCheck:: put_DuplicateObjects(	TR_ObjTree *pDupObj,OutEnumLONG &rOutIter)
{

	if ( !pDupObj)
		return false;

	CTable t (*pDupObj);

	int iErrorCode = GCS_DUPLICATE;

	for ( t.First(); t.Valid(); t.Next()) {
		TR_OBJECTSLock l(t);
		if ( !l)
			continue;
		rOutIter++ = l->Object();			// alle restlichen Daten raus
		SetCodeInformation(l->Object(),iErrorCode);
	}

	return true;

}
STDMETHODIMP CCodeCheck::EndAction (DWORD, IDataObject **ppDataObj)
{


	COM_TRY {
	// ProgressIndikator initialisieren
		SetMaxTicks (m_Objects.Count());

	// eigentliche Verarbeitung
		WEnumLONG EnumOut (CLSID_EnumObjectsByNumber);				// Ausgabeobjektmenge
		m_pStreet = new TR_STREETSTree();							//Objektbaum
	
		GetTRiASUserName();

		{
			OutEnumLONG iter_out (static_cast<IEnum<LONG> *>(EnumOut));

			for_each(InEnumLONG(&m_Objects), InEnumLONG(), CCodeCheckWorker(iter_out, this , *this));

			if ( m_pStreet && m_pStreet->Count() > 0 ) {
				EndActionTree(m_pStreet , iter_out);

			}
		} // iter_out goes out of scope

	// Ausgabeobjektmenge in Transfer-Objekt setzen
		__Interface<IDataObject> DO (CLSID_DataTransferObject);

		THROW_FAILED_HRESULT(PropActBase::SetEnumObjects (EnumOut, DO));
		*ppDataObj = DO.detach();

		// Baum freigeben
		if (NULL != m_pStreet) {
			delete m_pStreet;
			m_pStreet = NULL;
		}


	} COM_CATCH_NOASSERT_ON(E_ABORT);

	return S_OK;

}

/////////////////////////////////////////////////////////////////////////////
// IPersist
STDMETHODIMP CCodeCheck::GetClassID (CLSID *pClsID)
{
	*pClsID = GetObjectCLSID();
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistStreamInit
STDMETHODIMP CCodeCheck::Load (IStream *pStm)
{
	if (IsInitialized())
		return E_UNEXPECTED;

	RETURN_FAILED_HRESULT(CPropertyActionImpl::Load (pStm));

// TODO: Load your own data from the stream

// die beteiligten Objekteigenschaften


	os_string strGCO, strGCOriginal;

	RETURN_FAILED_HRESULT(LoadString(pStm, strGCO));
	RETURN_FAILED_HRESULT(LoadString(pStm, strGCOriginal));
	m_bstrGCO = strGCO.c_str();
	m_bstrParmGCO = strGCO.c_str();

	m_bstrGCOriginal = strGCOriginal.c_str();
	m_bstrParmOriginal = strGCOriginal.c_str();


	SetInitialized();
	return S_OK;
}

STDMETHODIMP CCodeCheck::Save (IStream *pStm, BOOL fClearDirty)
{
	RETURN_FAILED_HRESULT(CPropertyActionImpl::Save (pStm, fClearDirty));

// TODO: Save your own data to the stream

// die beteiligten Objekteigenschaften
	os_string strGCO, strGCOriginal;
	USES_CONVERSION;

	if (m_bstrParmGCO.Length() == 0 )
		m_bstrParmGCO = m_bstrGCO;

	if ( m_bstrParmOriginal.Length()== 0 ) 
		m_bstrParmOriginal = m_bstrGCOriginal;

	strGCO = W2A(m_bstrParmGCO);

	strGCOriginal = W2A(m_bstrParmOriginal);

	RETURN_FAILED_HRESULT(SaveString(pStm, strGCO));

	RETURN_FAILED_HRESULT(SaveString(pStm, strGCOriginal));


	return S_OK;
}
////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// IPersistPropertyBag
STDMETHODIMP CCodeCheck::Load (IPropertyBag *pBag, IErrorLog *pLog)
{
	USES_CONVERSION;
	RETURN_FAILED_HRESULT(CPropertyActionImpl::Load (pBag, pLog));

// Name=
	CComVariant vName;
	HRESULT hr = pBag -> Read (CComBSTR(L"Name"), &vName, pLog);

	if (S_OK == hr && SUCCEEDED(vName.ChangeType(VT_BSTR))) {
		m_bstrParmOriginal = V_BSTR(&vName);
	}

	CComVariant vSelect;
	hr = pBag -> Read (CComBSTR(L"Select"), &vSelect, pLog);

	if (S_OK == hr && SUCCEEDED(vSelect.ChangeType(VT_BSTR))) {
		m_bstrParmGCO = V_BSTR(&vSelect);
	}

	return S_OK;

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CCodeCheck::GetSizeMax (ULARGE_INTEGER *pcbSize)
{
	if (NULL == pcbSize)
		return E_POINTER;
	pcbSize -> QuadPart = 0L;

	RETURN_FAILED_HRESULT(CPropertyActionImpl::GetSizeMax (pcbSize));

// TODO: Add the size of your data to pcbSize
//	pcbSize  -> QuadPart += ...;
	return S_OK;
}

STDMETHODIMP CCodeCheck::InitNew()
{
	if (IsInitialized())
		return E_UNEXPECTED;

// TODO: initialize your data
	SetInitialized();

	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Geokomponente hat eigenen Dialog
STDMETHODIMP CCodeCheck::AddConfigPages (
	LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam, LPCSTR pcDesc, UINT *puiCnt)
{

//	int m_iMethod = ((CLineToolsExtension *) g_pTE)->Method();
//	if ( m_iMethod != PRF_CODE) 
//		return S_OK;

	THROW_FAILED_HRESULT(PreConfigData());	// Info von Vorgänger bzw. Registr.holen

	if ( m_bstrGCO == "")		//Keine Definitionen übergeben
		THROW_FAILED_HRESULT(SetSingleConfigData());	// Definitionen aus Parameterübergabe bzw. Ressource


	return S_OK;
}  

STDMETHODIMP CCodeCheck::PreConfigPages (IDataObject *pIDataObject, DWORD dwFlags)
{
//	int m_iMethod = ((CLineToolsExtension *) g_pTE)->Method();
//	if ( m_iMethod != PRF_CODE) 
//		return S_OK;

	return S_OK;
}
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CCodeCheck::PreConfigData (void)
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
STDMETHODIMP CCodeCheck::InitConfigDataFromRegistry(UINT IDLink,UINT IDGCO,UINT IDOriginal,UINT IDError)
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
STDMETHODIMP CCodeCheck::SetSingleConfigData (void)
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

	if ( m_bstrParmGCO.Length() > 0)
		m_bstrGCO = m_bstrParmGCO;

	if ( m_bstrParmOriginal.Length() > 0)
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

////////////////////////////////////////////////////////////////////////////////////