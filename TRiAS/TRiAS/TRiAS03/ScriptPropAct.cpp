// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 09/07/1998 02:29:43 PM
//
// @doc
// @module ScriptPropAct.cpp | Implementation of the <c CScriptPropAct> class

#include "trias03p.hxx"

#include "trias03.h"
#include "Strings.h"

#include <xtsnguid.h>
#include <eonrguid.h>
#include <bscrguid.h>
#include <statguid.h>
#include <ScriptPropActGuid.h>
#include <dirisole.h>

#include <triastlb.h>
#include <iGeoObjs.h>
#include <funcs03.h>
#include <ipropseq.hxx>

#include "datahelp.h"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

DefineEnumIIDWrapper(LONG);				// CIID_LONGEnum
DefineSmartEnumerator(LONG);			// WEnumLONG
#include "ScriptPropAct.h"

///////////////////////////////////////////////////////////////////////////////
// benötigte InterfaceWrapper
DefineSmartInterface(DataObject);
DefineSmartInterface(PropertyActionSequence);
DefineSmartInterface(QueryGeoObjects);
DefineSmartInterface(QueryEnumLONG);
DefineSmartInterface2(DGeoObjects, IID_DGeoObjects);

///////////////////////////////////////////////////////////////////////////////
//
CScriptPropAct::CScriptPropAct (void)
{
	m_fIsDirty = false;
	m_fIsInitialized = false;
	m_hInst = NULL;
	m_uiIDScript = 0L;

	COM_TRY {
	extern char g_pDLLName[_MAX_PATH];
	ResourceFile RF (g_pDLLName);
	ResString resPropInfo (ResID (IDS_SCRIPTPROPACT_DESC, &RF), 64);
	ResString resHelp (ResID (IDS_SCRIPTPROPACT_HELPDESC, &RF), 128);

		m_Status.m_bstrDesc = resPropInfo;
		m_Status.m_bstrHelpDesc = resHelp;
		m_Status.m_bstrDataSource = g_cbNil;		// keine vordefinierte Datenquelle

		m_BScript = WExtendBScript(CLSID_MacroScriptExtension);

	} COM_CATCH_NORETURN;
}

CScriptPropAct::~CScriptPropAct (void)
{
}

/////////////////////////////////////////////////////////////////////////////
// IPropertyAction methods
STDMETHODIMP CScriptPropAct::AddConfigPages (
	LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam, LPCSTR pcDesc, UINT *puiCnt)
{
	if (puiCnt) 
		*puiCnt = 0;
	return S_OK;
}

STDMETHODIMP CScriptPropAct::PreConfigPages (IDataObject *pIDataObject, DWORD dwFlags)
{
	return S_OK;
}

STDMETHODIMP CScriptPropAct::BeginAction (IProgressIndicator *)
{
	TX_ASSERT(m_BScript.IsValid());

BOOL lReturn = FALSE;		// RückgabeWert initialiseren

	COM_TRY {
	// Zieldatenquelle aus KontextObjekt herausfinden
	WPropertyActionSequence Seq;
	WDataObject CtxDO;
	CComVariant vData;
	HPROJECT hPr = HACTCONNECTION;

		THROW_FAILED_HRESULT(GetSite (IID_IPropertyActionSequence, Seq.ppv()));
		THROW_FAILED_HRESULT(Seq -> GetSequenceContext (CtxDO.ppi()));
		if (SUCCEEDED(GetVariantData (CtxDO, &c_feDataSourceHandle, &vData)) &&
			SUCCEEDED(vData.ChangeType (VT_I4))) 
		{
			hPr = reinterpret_cast<HPROJECT>(V_I4(&vData));
		}
		if (HACTCONNECTION == hPr && m_Status.m_bstrDataSource.Length() > 0) {
			USES_CONVERSION;
			hPr = DEX_GetDataSourceHandleFromShortName (OLE2A(m_Status.m_bstrDataSource));
		}

	// Variablen initialisieren
		m_OutObjs.clear();				// Liste sicher leeren
		m_ObjsIter = m_OutObjs.begin();	// auf Anfang stellen

	// BasicOperationen
	ebPARAM Pars[1];
	LPVOID cbParam[1];
	BSPARAM bs = { Pars, cbParam };

	// Function BeginAction () As Boolean 
		Pars[0].wType = TYP_BOOLEAN;
		Pars[0].szExtType[0] = '\0';
		cbParam[0] = &lReturn;

	// Script starten
		THROW_FAILED_HRESULT(m_BScript -> RunCodeEx (m_hInst, m_uiIDScript, m_strScript.c_str(), "BeginAction", 0, &bs, FALSE, reinterpret_cast<INT_PTR>(hPr)));

	} COM_CATCH_OP(CleanUpScript());

	if (!lReturn)
		CleanUpScript();
	return lReturn ? S_OK : E_ABORT;	// evtl. abgebrochen
}

STDMETHODIMP CScriptPropAct::DoAction (IDataObject *pIDataObj, DWORD)
{
	TX_ASSERT(m_BScript.IsValid());

HRESULT hr = E_FAIL;

	COM_TRY {
	// Zieldatenquelle aus KontextObjektherausfinden
	WPropertyActionSequence Seq;
	WDataObject CtxDO;
	CComVariant vData;
	HPROJECT hPr = HACTCONNECTION;

		THROW_FAILED_HRESULT(GetSite (IID_IPropertyActionSequence, Seq.ppv()));
		THROW_FAILED_HRESULT(Seq -> GetSequenceContext (CtxDO.ppi()));
		if (SUCCEEDED(GetVariantData (CtxDO, &c_feDataSourceHandle, &vData)) &&
			SUCCEEDED(vData.ChangeType (VT_I4))) 
		{
			hPr = reinterpret_cast<HPROJECT>(V_I4(&vData));
		}
		if (HACTCONNECTION == hPr && m_Status.m_bstrDataSource.Length() > 0) {
			USES_CONVERSION;
			hPr = DEX_GetDataSourceHandleFromShortName (OLE2A(m_Status.m_bstrDataSource));
		}

	// EingabeObjektmenge aus Dataobject holen
	WEnumLONG EnumObj;
	
		hr = GetEnumLONGData (pIDataObj, EnumObj.ppi());
		if (S_OK != hr) 
			return S_OK;		// nothing to do
	
	// in GeoObjects-collection umformen
	WQueryGeoObjects QueryObjs (EnumObj);
	WDGeoObjects GeoObjs;

		THROW_FAILED_HRESULT(QueryObjs -> GetGeoObjects (GeoObjs.ppi()));

	// BasicOperationen
	ebPARAM Pars[2];
	LPVOID cbParam[2];
	BSPARAM bs = { Pars, cbParam };

	// Function DoAction (Objs As GeoObjects) As GeoObjects
	DGeoObjects *pOutObjs = NULL;		// RückgabeWert initialiseren

		Pars[0].wType = TYP_APPOBJECT;
		strcpy (Pars[0].szExtType, "GeoObjects");
		cbParam[0] = &pOutObjs;

	// Parameter initialiseren
	DGeoObjects *pIObjs = (DGeoObjects *)GeoObjs;

		Pars[1].wType = TYP_APPOBJECT;
		strcpy (Pars[1].szExtType, "GeoObjects");
		cbParam[1] = &pIObjs;

	// Script starten
		pIObjs -> AddRef();						// BScript ruft Release()
		THROW_FAILED_HRESULT(m_BScript -> ExecuteMethod (m_strScript.c_str(), "DoAction", 1, &bs, FALSE, reinterpret_cast<INT_PTR>(hPr)));

	// Resultat wieder in EnumObjectsByNumber umwandeln
	WQueryEnumLONG QEnum(pOutObjs);
	WEnumLONG EnumOut;

		if (NULL != pOutObjs) {
		// wenn abgebrochen kann ExecuteMethod S_OK liefern, aber kein Resultat
			pOutObjs -> Release();
			THROW_FAILED_HRESULT(QEnum -> QueryEnumLONG ((IEnumLONG **)EnumOut.ppi()));

			m_OutObjs.push_back (EnumOut);		// Enumerator in Liste speichern
			hr = S_OK;
		} else
			hr = E_ABORT;	// abgebrochen 

		if (1 == m_OutObjs.size())
			m_ObjsIter = m_OutObjs.begin();	// auf Anfang stellen

	} COM_CATCH_OP(CleanUpScript());
	return hr;
}

STDMETHODIMP CScriptPropAct::EndAction (DWORD, IDataObject **ppDataObj)
{
	if (NULL == ppDataObj) return E_POINTER;

	TX_ASSERT(m_ObjsIter != m_OutObjs.end());
	if (m_ObjsIter == m_OutObjs.end())
		return CleanUpScript();		// nur noch aufräumen

WEnumLONG EnumObj(*m_ObjsIter);

	*ppDataObj = NULL;

	TX_ASSERT(m_BScript.IsValid());
	COM_TRY {
	// Zieldatenquelle aus KontextObjektherausfinden
	WPropertyActionSequence Seq;
	WDataObject CtxDO;
	CComVariant vData;
	HPROJECT hPr = HACTCONNECTION;

		THROW_FAILED_HRESULT(GetSite (IID_IPropertyActionSequence, Seq.ppv()));
		THROW_FAILED_HRESULT(Seq -> GetSequenceContext (CtxDO.ppi()));
		if (SUCCEEDED(GetVariantData (CtxDO, &c_feDataSourceHandle, &vData)) &&
			SUCCEEDED(vData.ChangeType (VT_I4))) 
		{
			hPr = reinterpret_cast<HPROJECT>(V_I4(&vData));
		}
		if (HACTCONNECTION == hPr && m_Status.m_bstrDataSource.Length() > 0) {
			USES_CONVERSION;
			hPr = DEX_GetDataSourceHandleFromShortName (OLE2A(m_Status.m_bstrDataSource));
		}

	WDataObject IDO (CLSID_DataTransferObject);

		THROW_FAILED_HRESULT(SetEnumLONGData (EnumObj, IDO));
		*ppDataObj = IDO.detach();

		m_ObjsIter++;
		if (m_ObjsIter == m_OutObjs.end()) {
		// BasicOperationen
		ebPARAM Pars[1];
		LPVOID cbParam[1];
		BSPARAM bs = { Pars, cbParam };

		// Sub EndAction()
			Pars[0].wType = 0;
			Pars[0].szExtType[0] = '\0';
			cbParam[0] = NULL;

		// Script starten: EndAction
			THROW_FAILED_HRESULT(m_BScript -> ExecuteMethod (m_strScript.c_str(), "EndAction", 0, &bs, FALSE, reinterpret_cast<INT_PTR>(hPr)));

			CleanUpScript();
			return S_OK;		// das war der letzte Auffruf
		}

	} COM_CATCH_OP(CleanUpScript());
	return S_FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// Script sauber beenden
HRESULT CScriptPropAct::CleanUpScript (void)
{
// separater try/catch, da diese Funktion als ExceptionHandler gerufen wird
	COM_TRY {	// Script anhalten und rauswerfen
		return m_BScript -> StopScript (m_strScript.c_str());
	} COM_CATCH_ALL;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IClassProperty specific functions
STDMETHODIMP CScriptPropAct::GetPropInfo (LPSTR pBuffer, WORD wLen, DWORD *pdwFlags)
{
	if (NULL != pBuffer && wLen > 0) {
	// Namen der Property kopieren
	ULONG ulLen = min ((size_t)(wLen-1), m_Status.m_bstrDesc.Length());

		USES_CONVERSION;
		strncpy (pBuffer, OLE2A(m_Status.m_bstrDesc), ulLen);
		pBuffer[ulLen] = '\0';
	}

// wenn gewünscht, Flags übergeben
	if (pdwFlags) 
		*pdwFlags =	m_Status.m_dwPropFlags;
	return S_OK;
}

STDMETHODIMP CScriptPropAct::HelpInfo (LPSTR pBuffer, ULONG wLen, LPSTR pHelpFile, ULONG *pulHelpCtx)
{
	if (NULL != pBuffer && wLen > 0) {
	// Beschreibung übergeben
	ULONG ulLen = min ((size_t)(wLen-1), m_Status.m_bstrHelpDesc.Length());

		USES_CONVERSION;
		strncpy (pBuffer, OLE2A(m_Status.m_bstrHelpDesc), ulLen);
		pBuffer[ulLen] = '\0';
	}

// HelpFileInfo übergeben
	if (pHelpFile) pHelpFile[0] = '\0';
	if (pulHelpCtx) *pulHelpCtx = 0L;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPropertyInfo specific functions 
STDMETHODIMP CScriptPropAct::SetPropInfo (LPCSTR pcBuffer, DWORD dwFlags) 
{
	if (NULL == pcBuffer) 
		return E_POINTER;

	COM_TRY {
	os_string str (pcBuffer);
	size_t iPos = str.find('\n');

		if (NPOS != iPos) {
			m_Status.m_bstrDesc = str.substr(0, iPos).c_str();
			m_Status.m_bstrHelpDesc = str.substr(iPos).c_str();
		} else {
			m_Status.m_bstrDesc = pcBuffer;
		}
		m_Status.m_dwPropFlags = dwFlags;

	} COM_CATCH;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersist methods
STDMETHODIMP CScriptPropAct::GetClassID (CLSID *pClsID)
{
	if (NULL == pClsID)
		return E_POINTER;

	*pClsID = CLSID_ScriptPropAct;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistStreamInit methods
STDMETHODIMP CScriptPropAct::IsDirty(void)
{
	return m_fIsDirty ? S_OK : S_FALSE;
}

STDMETHODIMP CScriptPropAct::Load(LPSTREAM pStm)
{
	if (m_fIsInitialized)
		return E_UNEXPECTED;		// already initialized with InitNew

HRESULT hr = CPropertyAction::Load (pStm);

	if (FAILED(hr)) return hr;

	m_Status.erase();

	RETURN_FAILED_HRESULT(LoadLong(pStm, (long &)m_Status.m_dwPropFlags));
	RETURN_FAILED_HRESULT(LoadString(pStm, m_strDesc));
	RETURN_FAILED_HRESULT(LoadString(pStm, m_strHelpDesc));

	m_fIsInitialized = true;
	m_fIsDirty = false;
	return S_OK;
}

STDMETHODIMP CScriptPropAct::Save (LPSTREAM pStm, BOOL fClearDirty)
{
// zuerst Basisklasse wegschreiben
HRESULT hr = CPropertyAction::Save (pStm, fClearDirty);

	if (FAILED(hr)) return hr;

	RETURN_FAILED_HRESULT(SaveLong(pStm, m_Status.m_dwPropFlags));
	RETURN_FAILED_HRESULT(SaveString(pStm, m_strDesc));
	RETURN_FAILED_HRESULT(SaveString(pStm, m_strHelpDesc));

	if (fClearDirty) 
		m_fIsDirty = false;
	return S_OK;
}

STDMETHODIMP CScriptPropAct::GetSizeMax (ULARGE_INTEGER *pcbSize)
{
	if (NULL == pcbSize) 
		return E_POINTER;

ULARGE_INTEGER cbSize;
HRESULT hr = CPropertyAction::GetSizeMax (&cbSize);

	if (FAILED(hr)) return hr;

// TODO: calculate size of saved data (m_Status) here
	*pcbSize = cbSize;
	return S_OK;
}

STDMETHODIMP CScriptPropAct::InitNew(void)
{
	if (m_fIsInitialized)
		return E_UNEXPECTED;		// already initialized with Load

	m_fIsInitialized = true;
	m_fIsDirty = false;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistPropertyBag
// mögliche SteuerParameter
//	Desc="..."		BeschreibungsInfo
//	HelpDesc="..."	Langer BeschreibungsText
STDMETHODIMP CScriptPropAct::Load (IPropertyBag *pBag, IErrorLog *pLog)
{
	RETURN_FAILED_HRESULT(CPropertyAction::Load (pBag, pLog));

	m_Status.erase();

// Desc=
CComVariant vParam;
HRESULT hr = pBag -> Read (CComBSTR(g_cbDesc), &vParam, pLog);

	if (S_OK == hr && SUCCEEDED(vParam.ChangeType (VT_BSTR)))
	{
		m_Status.m_bstrDesc = V_BSTR(&vParam);
	}

// HelpDesc=
	vParam.Clear();
	hr = pBag -> Read (CComBSTR(g_cbHelpDesc), &vParam, pLog);
	if (S_OK == hr && SUCCEEDED(vParam.ChangeType (VT_BSTR)))
	{
		m_Status.m_bstrHelpDesc = V_BSTR(&vParam);
	}

// DataSource=
	vParam.Clear();
	hr = pBag -> Read (CComBSTR(g_cbDataSource), &vParam, pLog);
	if (S_OK == hr && SUCCEEDED(vParam.ChangeType (VT_BSTR)))
	{
		m_Status.m_bstrDataSource = V_BSTR(&vParam);
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Sonstiges
void CScriptPropAct::SetDirty (bool fDirty) { m_fIsDirty = fDirty; }

///////////////////////////////////////////////////////////////////////////////
// IInitScriptPropAct
STDMETHODIMP CScriptPropAct::InitScript (BSTR bstrScript, INT_PTR hInst, UINT uiResID)
{
	USES_CONVERSION;

	m_hInst = (HINSTANCE)hInst;
	m_uiIDScript = uiResID;
	m_strScript = OLE2A(bstrScript);
	return S_OK;
}

STDMETHODIMP CScriptPropAct::GetScriptEngine (REFIID riid, IUnknown **ppIUnk)
{
	if (!m_BScript.IsValid())
		return E_UNEXPECTED;
	return m_BScript -> QueryInterface (riid, (LPVOID *)ppIUnk);
}
