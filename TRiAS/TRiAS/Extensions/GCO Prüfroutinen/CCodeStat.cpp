// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 04.12.2002 09:44:34
//
// @doc
// @module CCodeStat.cpp | Implementation of the <c CCCodeStat> class

#include "stdafx.h"


#include <TRiASHelper.h>

#include <xtsnguid.h>

#include "errorcode.h"

#include "relkey.h"

#include "LineTools.h"
#include "LineToolsUtil.h"

#include "CCodeStat.h"
#include <KoOrd.h>
#include <IPropSeq.hxx>

#include <Errcodes.hxx>
#include <errinstx.hxx>
#include <Xtensnn.h>
#include "LineToolsUtil.h"
#include "LineToolsExt.h"
#include <hpp/datahelp.hpp>

#include <CLSFYPRP.H>

//#include <ObjectPropertyResult.h>


// Map für MerkmalsCodes
typedef map<INT_PTR, INT_PTR, less<INT_PTR> > CObjectMap;

CObjectMap g_Objects;

//long ErrorCodeMap[] = {GCS_NOTHING,GCS_SYNTAX,GCS_DUPLICATE,GCS_OTHER,GI_DUPLICATE,GI_MULTI};
//UINT ErrorKeyMap [] = { IDS_ERRORKEY01,IDS_ERRORKEY02,IDS_ERRORKEY03,IDS_ERRORKEY04,IDS_ERRORKEY05,IDS_ERRORKEY06};

extern long ErrorCountMap[];
extern long ErrorCodeMap[];
extern UINT ErrorKeyMap[];
extern long lMapEnd;
extern long lMapCountEnd;


// SmartIF's
DefineSmartInterface(ObjectWithSite);
DefineSmartInterface(PropertyActionSequence);
DefineSmartInterface(DataObject);
DefineEnumOutputIterator(LONG);		// definiert OutEnumLONG



/////////////////////////////////////////////////////////////////////////////
// CCCodeStat
// IPropertyAction 

STDMETHODIMP CCCodeStat::BeginAction (IProgressIndicator *pIProgInd)
{
	RETURN_FAILED_HRESULT(CPropertyActionImpl::BeginAction (pIProgInd));
	m_Objects.Clear();
	return S_OK;
}

STDMETHODIMP CCCodeStat::DoAction (IDataObject *pIDataObj, DWORD dwReserved)
{

	m_iErrorCode = m_pCfgDlg->GetErrorCode();

	m_bUND = m_pCfgDlg->UND();	//Verknüpfung

	m_bErrorStatist = m_pCfgDlg->bErrorStatist();

	//FehlerTypen
	SetErrorCodeMap();



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
	class CCCodeStatWorker 
	{
	public:
		CCCodeStatWorker(OutEnumLONG &rOutIter, CCCodeStat *pThis, CCCodeStat& rCodeStatAction) : 
			m_pPA(pThis), m_rOutIter(rOutIter), m_rCodeStatAction(rCodeStatAction)
		{
		}
		~CCCodeStatWorker() {}

		bool StoreObjTree ( long lONr, int iError);


	// wird für jedes zu bearbeitende Objekt gerufen
		void operator() (LONG lONr)
		{
			_ASSERTE(NULL != m_pPA);
			m_pPA -> Tick();			// ProgressIndikator weitersetzen
			if (FAILED(m_pPA -> GoOn()))
				_com_issue_error(E_ABORT);

			m_pObjects = m_rCodeStatAction.Objects();

			int iError = m_rCodeStatAction.ErrorCode();

			CObjectStatus Object (lONr,m_rCodeStatAction.ErrorFeature());
			m_rCodeStatAction.SetObjectNumber ();

			if ( Object.isValid() ) {

//				if ( Object.ErrorCode() & iError) {
//					m_rCodeStatAction.SetPacket(Object.ErrorCode(),iError);
				if ( m_rCodeStatAction.CheckError(Object.ErrorCode() ,iError)) {

					StoreObjTree( Object.Object(),Object.ErrorCode());
				}
			}

		// TODO: Add your own precessing here
//			m_rOutIter++ = lONr;		// object is added to the output collections
		}

	private:
		IProgressIndicatorUsage *m_pPA;
		OutEnumLONG &m_rOutIter;
		CCCodeStat& m_rCodeStatAction;
		TR_ObjTree * m_pObjects;
	};
} // namespace

///////////////////////////////////////////////////////////////////////////////////

// Baum der Konfigurationsdaten 
bool CCCodeStatWorker::StoreObjTree (long lONr, int iErrorCode) 
{

	if (m_pObjects == NULL) {
			return false;
	}

	CTable t (*m_pObjects);

	if (!t.Find (&lONr)) {

		TR_OBJECTSCreator OSCr (*m_pObjects);

		return ContCreate(OSCr, TR_OBJECTS)(lONr,iErrorCode) != NULL;

	}

	return false;

}
/////////////////////////////////////////////////////////////////////////////////
bool CCCodeStat :: CheckError (int iErrorIst ,int iErrorSoll)
{
	if ( m_bShowErrors)
		SetErrorFeatures(iErrorIst);

	if ( m_bUND) {
		if ( iErrorIst == iErrorSoll) {
			SetPacket(iErrorIst,iErrorSoll);
			return true;
		}

	} else {

		if ( iErrorIst & iErrorSoll) {
			SetPacket(iErrorIst,iErrorSoll);
			return true;
		}
		
	}

	return false;

}
/////////////////////////////////////////////////////////////////////////////////
int CCCodeStat :: FindFirstCode ( int iError)
{

	int iErrorCode = 0;
	long lNumber = 0;
	m_bstrCaption = "";

	for (CErrorMap::iterator it = g_ErrorType.begin(); it != g_ErrorType.end(); ++it) {

		iErrorCode = (*it).first;

		if ( m_iErrorCode & iErrorCode) {		// Abgleich gefunder zu gesuchter Fehlercode
		
			if ( iError & iErrorCode) {
				m_bstrCaption.LoadString(ErrorKeyMap[lNumber]);
				return iErrorCode;
			}
		}

		lNumber++;
	}

	return 0;

}
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
void CCCodeStat :: FindCaption ( int iError)
{

	int iErrorCode = 0;
	long lNumber = 0;
	CComBSTR SK ;
	m_bstrCaption.Empty();

	for (CErrorMap::iterator it = g_ErrorType.begin(); it != g_ErrorType.end(); ++it) {

		iErrorCode = (*it).first;
		
		if ( iError & iErrorCode) {

			SK.LoadString(ErrorKeyMap[lNumber]);

			if (m_bstrCaption.Length() > 0)
				m_bstrCaption  += "+";

			m_bstrCaption  += SK;;

		}

		lNumber++;
	}

	return;

}

/////////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CCCodeStat::EndActionTree (TR_ObjTree *pObjects, OutEnumLONG &rOutIter)
{

	int iErrorCode = 0;
	int iError = 0;
	bool bType = false;

	COM_TRY {
		CTable t (*pObjects);

		for ( t.First(); t.Valid(); t.Next()) {

			TR_OBJECTSLock l(t);
			if ( !l)
				continue;

			iError = l->ErrorCode();				//Code-Kombination des Objektes

			if ( m_bUND ) {
				iErrorCode = m_iErrorCode;			// m_iErrorCode = ausgewählte Codes aus Dialog

				if ( iErrorCode == iError)	{	//Vergleich DialogAuswahl mit Objekt-Kombination
					bType = true;
					FindCaption(iError);
				} else
					bType = false;
			} else {
				if ( iErrorCode == 0) 
					iErrorCode = FindFirstCode( iError);		// Nur für ODER

				bType = (iError & iErrorCode);

			}

			if ( bType) {
				long lONr = l->Object();

				rOutIter++ = lONr;
				l->SetUnDef();

				CObjectMap::iterator it = g_Objects.find(lONr);

				if (it == g_Objects.end())
					g_Objects.insert(CObjectMap::value_type(lONr, (long)iErrorCode));

			}
			
		}

// Hier aus iErrorCode Caption bestimmen


	} COM_CATCH_NOASSERT_ON(E_ABORT);


	return S_OK;
}
///////////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CCCodeStat::SetErrorCodeMap(void)
{

	long lCount = 0;

//	long iEnd = _countof(ErrorCodeMap);

	int iEnd = (int) lMapEnd;
	for ( int i = 0; i < iEnd; i++) {

		CErrorMap::iterator it = g_ErrorType.find(ErrorCodeMap[i]);
		if (it == g_ErrorType.end())
			g_ErrorType.insert(CObjectMap::value_type( ErrorCodeMap[i], lCount));
	}

	return S_OK;

}
///////////////////////////////////////////////////////////////////////////////////
void DeleteObject ( TR_ObjTree * pObj, long lONr)
{

	if ( !pObj || pObj->Count() == 0L)
		return;

	CTable t(*pObj);

	if ( t.Find(&lONr)) {
		t.Delete();
	}

	return;

}

/////////////////////////////////////////////////////////////////////////////////

STDMETHODIMP CCCodeStat::ResetActionTree (TR_ObjTree *pObjects)
{


	for (CObjectMap::iterator it = g_Objects.begin(); it != g_Objects.end(); ++it) {

		DeleteObject(m_pObjects,(*it).first);

	}
			
	g_Objects.clear();
	m_pObjects->Optimize();


	return S_OK;
}
///////////////////////////////////////////////////////////////////////////////////
void CCCodeStat::SetErrorFeatures( int iObjError)
{
	int iErrorCode = 0;
	long i = 0;

	for (CErrorMap::iterator it = g_ErrorType.begin(); it != g_ErrorType.end(); ++it) {

		iErrorCode = (int)(*it).first;		//Definierter Fehlercode
		i++;

		if ( iObjError & iErrorCode) {		// ObjektFehler
			long lCount = ErrorCountMap[i-1];
			lCount++;
			ErrorCountMap[i-1] = lCount;
		}
	}

}
/////////////////////////////////////////////////////////////////////////////////
void CCCodeStat::ResetErrorFeatures( void)
{
	for ( long i = 0 ; i < lMapCountEnd; i++)
			ErrorCountMap[i] = 0;

}
//////////////////////////////////////////////////////////////////////////////////
void CCCodeStat::SetPacket (int iObjError,int iError)
{
	int iErrorCode = 0;

	for (CErrorMap::iterator it = g_ErrorType.begin(); it != g_ErrorType.end(); ++it) {

		iErrorCode = (int)(*it).first;

		if ( iObjError & iErrorCode) {		// ObjektFehler
			if ( iErrorCode & iError )	{	// Auch gewünschte Fehlerart
				long lCount = (*it).second;
				lCount++;
				(*it).second = lCount;
//				return;
			}
		}
	}

}
///////////////////////////////////////////////////////////////////////////////////////////////
void CCCodeStat::SetObjectNumber (void)
{

	long lCount = ErrorCountMap[lMapCountEnd-1];
	lCount++;
	ErrorCountMap[lMapCountEnd-1] = lCount;


}
///////////////////////////////////////////////////////////////////////////////////////////////
void CCCodeStat::GetErrorCode (void)
{

	long lCount = 0;

	TCHAR strECode [5*_MAX_PATH];
	TCHAR strFCode [_MAX_PATH];

	CString sAlle;
	CString sFormat;
	CString sName;
	CString sExit;


	sAlle.LoadString(IDS_HEADERLINE);

	sFormat.LoadString(IDS_ERRORLINE);

	sExit.LoadString(IDS_EXITLINE);

	wsprintf(strECode,sAlle,ErrorCountMap[lMapCountEnd-1]);

	bool bNoError = true;

	for (CErrorMap::iterator it = g_ErrorType.begin(); it != g_ErrorType.end(); ++it) {

		lCount++;
		sName.LoadString(ErrorKeyMap[lCount-1]);

		if ( ErrorCountMap[lCount-1] > 0 ) {
			bNoError = false;
			wsprintf(strFCode,sFormat,sName,ErrorCountMap[lCount-1]);
			strcat (strECode,strFCode);
		}
	
	}

	if ( bNoError) {
			strcat (strECode,strFCode);
	}



	AfxGetMainWnd()->MessageBox (strECode, "GCO-Fehlerstatistik", MB_OK|MB_ICONINFORMATION);


	return;
}


///////////////////////////////////////////////////////////////////////////////////////////////
long CCCodeStat::GetPacket (void)
{

	long lPacket = 0;


	for (CErrorMap::iterator it = g_ErrorType.begin(); it != g_ErrorType.end(); ++it) {

		if ( (*it).second > 0) 		// ObjektFehler
			lPacket++;
	
	}

	if ( m_bUND && lPacket > 0)
		return 1;		// Und ist immer 1!

	return lPacket;
}
///////////////////////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CCCodeStat::EndAction (DWORD, IDataObject **ppDataObj)
{


	g_Objects.clear();

	long lPacket = 0;

	ResetErrorFeatures();		// Rücksetzen der Fehlerstatistik

	COM_TRY {
	// ProgressIndikator initialisieren
		SetMaxTicks (m_Objects.Count());

	// eigentliche Verarbeitung
	WEnumLONG EnumOut (CLSID_EnumObjectsByNumber);				// Ausgabeobjektmenge

	bool iFirst = false;
	if ( !m_pObjects) {
		m_pObjects = new TR_ObjTree();
		iFirst = true;
	}

		{
			OutEnumLONG iter_out (static_cast<IEnum<LONG> *>(EnumOut));

			if ( iFirst) {
				for_each(InEnumLONG(&m_Objects), InEnumLONG(), CCCodeStatWorker(iter_out, this, *this));
				m_lPacket = GetPacket();

			// FehlerStatistik
				if ( m_bShowErrors & m_bErrorStatist)
					GetErrorCode();				// Zusammenstellen der Fehlerstatistik

			}

			if ( m_pObjects && m_pObjects->Count() > 0 ) {

				EndActionTree(m_pObjects , iter_out);
				ResetActionTree(m_pObjects );

			}


		} // iter_out goes out of scope

	lPacket = m_lPacket--;				// Paketnummer rückwärts zählen

	// Ausgabeobjektmenge in Transfer-Objekt setzen
	__Interface<IDataObject> DO (CLSID_DataTransferObject);

		THROW_FAILED_HRESULT(PropActBase::SetEnumObjects (EnumOut, DO));

		if ( lPacket > 0 ) {
			PropActBase::SetPacketNumber(DO, lPacket);

			SetPacketCaption(DO,lPacket);
	//		SetPacketFeature(DO);
		}

		*ppDataObj = DO.detach();

	// DialogPage freigeben
		if (NULL != m_pCfgDlg) {
			delete m_pCfgDlg;
			m_pCfgDlg = NULL;
		}

	} COM_CATCH_NOASSERT_ON(E_ABORT);

	if ( m_pObjects->Count() == 0) {
		DELETE_OBJ(m_pObjects);
		return S_OK;
	}
	return S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// IPersist
STDMETHODIMP CCCodeStat::GetClassID (CLSID *pClsID)
{
	*pClsID = GetObjectCLSID();
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistStreamInit
STDMETHODIMP CCCodeStat::Load (IStream *pStm)
{
	if (IsInitialized())
		return E_UNEXPECTED;

	RETURN_FAILED_HRESULT(CPropertyActionImpl::Load (pStm));
	RETURN_FAILED_HRESULT(LoadData(pStm, m_bUseAll));
	RETURN_FAILED_HRESULT(LoadData(pStm, m_bShowErrors));

// TODO: Load your own data from the stream
	SetInitialized();

	return S_OK;
}

STDMETHODIMP CCCodeStat::Save (IStream *pStm, BOOL fClearDirty)
{
	RETURN_FAILED_HRESULT(CPropertyActionImpl::Save (pStm, fClearDirty));
	RETURN_FAILED_HRESULT(SaveData(pStm, m_bUseAll));
	RETURN_FAILED_HRESULT(SaveData(pStm, m_bShowErrors));

// TODO: Save your own data to the stream
	return S_OK;
}

////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// IPersistPropertyBag
STDMETHODIMP CCCodeStat::Load (IPropertyBag *pBag, IErrorLog *pLog)
{
	USES_CONVERSION;
	RETURN_FAILED_HRESULT(CPropertyActionImpl::Load (pBag, pLog));

// UseAll=
CComVariant vUseAll;
HRESULT hr = pBag -> Read (CComBSTR(L"UseAll"), &vUseAll, pLog);

	m_bUseAll = true;
	//VT_BOOL ?
	if (S_OK == hr && SUCCEEDED(vUseAll.ChangeType(VT_I2))) 
		m_bUseAll = V_I2(&vUseAll);

	CComVariant vShowErrors;
	hr = pBag -> Read (CComBSTR(L"ShowErrors"), &vShowErrors, pLog);
	m_bShowErrors = false;
	//VT_BOOL ?
	if (S_OK == hr && SUCCEEDED(vShowErrors.ChangeType(VT_I2))) 
		m_bShowErrors = V_I2(&vShowErrors);

	
	return S_OK;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////

STDMETHODIMP CCCodeStat::GetSizeMax (ULARGE_INTEGER *pcbSize)
{
	if (NULL == pcbSize)
		return E_POINTER;
	pcbSize -> QuadPart = 0L;

	RETURN_FAILED_HRESULT(CPropertyActionImpl::GetSizeMax (pcbSize));

// TODO: Add the size of your data to pcbSize
//	pcbSize  -> QuadPart += ...;
	return S_OK;
}

STDMETHODIMP CCCodeStat::InitNew()
{
	if (IsInitialized())
		return E_UNEXPECTED;

	m_bUseAll = true;
	m_bShowErrors = false;

// TODO: initialize your data
	SetInitialized();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Geokomponente hat eigenen Dialog
STDMETHODIMP CCCodeStat::AddConfigPages (
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
		m_pCfgDlg = CCCodeStatDlg::CreateInstance(cbCaption);
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
//////////////////////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CCCodeStat::PreConfigPages (IDataObject *pIDataObject, DWORD dwFlags)
{
	if (NULL == m_pCfgDlg) 
		return E_UNEXPECTED;

	m_pCfgDlg -> SetFlags(dwFlags);

	THROW_FAILED_HRESULT(PreConfigData());

	m_pCfgDlg -> SetConfigData(m_bstrGCO,m_bstrGCOriginal,m_bstrError, m_bUseAll,m_bShowErrors);

	return S_OK;
}
///////////////////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CCCodeStat::PreConfigData (void)
{

	CString sLF;
	CString sO;
	CString sECF;

	sLF.LoadString(IDS_GCOCODE);

	sO.LoadString(IDS_GCORIGINAL);

	sECF.LoadString(IDS_ERRORCODEFEATURE);

	COM_TRY {

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

//------------------------SABIS-GCO-Code-------------------------------------
		THROW_FAILED_HRESULT(GetVariantData ( DO, &c_feSABiS, &vData));

		if ( SUCCEEDED(vData.ChangeType (VT_BSTR)))
		{
			m_bstrGCO = V_BSTR(&vData);
		}
//-------------------------ErrorFeld-------------------------------------

	 FORMATETC c_feSABiSError = 	{
			RegisterClipboardFormat (sECF),				// CLIPFORMAT cf
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
////////////////////////////////////////GCO-Original /////////////////////////////////////////

//-------------------------ErrorFeld-------------------------------------

	 FORMATETC c_feOriginal = 	{
			RegisterClipboardFormat (sO),				// CLIPFORMAT cf
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
///////////////////////////////////////////////////////////////////////////////////////////////
	HRESULT CCCodeStat::SetPacketFeature (IDataObject *pIDO )
	{

		CComVariant vData (m_bstrGCO);

//		c_feClassifyObjects
		RETURN_FAILED_HRESULT(SetVariantData(vData, pIDO, &c_feClassifyValue));

		return S_OK;
	}

///////////////////////////////////////////////////////////////////////////////////////////////
	HRESULT CCCodeStat::SetPacketCaption (IDataObject *pIDO, long lPacket )
	{
		CComVariant vData (m_bstrCaption);

		RETURN_FAILED_HRESULT(SetVariantData(vData, pIDO, &c_feORWndCaption));

		return S_OK;
	}


////////////////////////////////////////////////////////////////////////////////////////////////(
