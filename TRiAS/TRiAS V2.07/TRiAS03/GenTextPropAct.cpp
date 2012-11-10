// $Header: /TRiAS/TRiAS/TRiAS03/GenTextPropAct.cpp 3     4.06.98 9:51 Hartmut Kaiser $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 06/01/1998 07:21:40 PM
//
// @doc
// @module GenTextPropAct.cpp | Implementation of CGenTextPropAct

#include "trias03p.hxx"
#include "trias03.h"

#include <ospace/com/olestrea.h>
#include <xtsnguid.h>
#include <srchguid.h>
#include <statguid.h>

#include <funcs03.h>
#include <int64.h>

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "Strings.h"
#include "Datahelp.h"
#include "TRiASHelper.h"
#include "GenTextPropAct.h"

///////////////////////////////////////////////////////////////////////////////
// Min-Funktion, da Macro aus stdlib offensichtlich überladen ist
template<class T>
inline T tmin (T a, T b) { return (a > b) ? b : a; }

///////////////////////////////////////////////////////////////////////////////
// benötigte InterfaceWrapper
DefineSmartInterface(DataObject);
DefineSmartEnumerator(LONG);	// WEnumLONG

///////////////////////////////////////////////////////////////////////////////
//
extern char g_pDLLName[_MAX_PATH];

///////////////////////////////////////////////////////////////////////////////
//
CGenTextPropAct::CGenTextPropAct (void)
{
	m_pCfgDlg = NULL;
	m_fIsDirty = false;
	m_fIsInitialized = false;

	try {
	ResourceFile RF (g_pDLLName);
	ResString resPropInfo (ResID (IDS_GENTEXTPROPACT_DESC, &RF), 64);

		m_strDesc = resPropInfo;
	} catch (...) {
		TX_ASSERT(false);
	}
}

CGenTextPropAct::~CGenTextPropAct (void)
{
	DELETE_OBJ(m_pCfgDlg);
}

/////////////////////////////////////////////////////////////////////////////
// IPropertyAction methods
STDMETHODIMP CGenTextPropAct::AddConfigPages (LPFNADDPROPSHEETPAGE lpfnAddPage, 
								LPARAM lParam, LPCSTR pcDesc, UINT *puiCnt)
{
	if (puiCnt) *puiCnt = 0;
	COM_TRY {
	char cbCaption[128];

		if (NULL != pcDesc)		// Caption ist gegeben
			strcpy (cbCaption, pcDesc);
		else	// von zugehöriger ClassProperty unseren Namen besorgen
			GetPropInfo (cbCaption, sizeof(cbCaption), NULL);

	// zugehörigen ConfigDialog (PropertyPage(s)) anlegen
	ResourceFile RF (g_pDLLName);

		DELETE_OBJ(m_pCfgDlg);	// evtl. vorherigen freigeben
		m_pCfgDlg = CGenTextDlg::CreateInstance (this, 
						ResID (IDD_CREATETEXTS_WIZ, &RF), cbCaption);
		if (NULL == m_pCfgDlg) _com_issue_error(E_OUTOFMEMORY);
	//
	// Achtung MFC-Falle !
	// Normalerweise müßte an dieser Stelle lpfnAddPage mit unserem 
	// HPROPERTYPAGE gerufen werden, wir aber wissen (darf man das ?), daß
	// sich hinter dem eigentlich durchzureichendem lParam der Pointer auf
	// unsern PropertySheet verbirgt.
	//
		if (!IsNoShow() && UINT_MAX == ((CPropertySheet *)lParam) -> AddPage (m_pCfgDlg))
			_com_issue_error(E_UNEXPECTED);

		m_pCfgDlg -> InitWithData (m_Status);
		if (NULL != puiCnt) 
			*puiCnt = IsNoShow() ? 0 : 1;

	} COM_CATCH_OP(delete m_pCfgDlg);
	return S_OK;
}

STDMETHODIMP CGenTextPropAct::PreConfigPages (IDataObject *pIDataObject, DWORD dwFlags)
{
	if (NULL == m_pCfgDlg) 
		return E_UNEXPECTED;
	
	m_pCfgDlg -> SetFlags(dwFlags);
	return NOERROR;
}

STDMETHODIMP CGenTextPropAct::BeginAction (IProgressIndicator *pPI)
{
	if (NULL == m_pCfgDlg) 
		return E_UNEXPECTED;

	// JG 980914
	CPropertyActionExt::BeginAction(pPI);
	return m_pCfgDlg -> ResetEnumLONG();
}

STDMETHODIMP CGenTextPropAct::DoAction (IDataObject *pIDataObj, DWORD)
{
	if (NULL == m_pCfgDlg) 
		return E_UNEXPECTED;

WEnumLONG EnumObj;
HRESULT hr = GetEnumLONGData (pIDataObj, EnumObj.ppi());

	if (SUCCEEDED(hr)) 
	{
		m_pCfgDlg -> SetAction(this);
		hr = m_pCfgDlg -> SetEnumLONG (EnumObj);
	}
	return hr;
}

STDMETHODIMP CGenTextPropAct::EndAction (DWORD, IDataObject **ppDataObj)
{
	if (NULL == m_pCfgDlg) return E_UNEXPECTED;
	if (NULL == ppDataObj) return E_POINTER;

// DataObject generieren und mit EnumObj füllen
WEnumLONG EnumObj;

	RETURN_FAILED_HRESULT(m_pCfgDlg -> GetEnumLONG (EnumObj.ppi()));
	*ppDataObj = NULL;

HRESULT hr = E_FAIL;

	COM_TRY {
	WDataObject IDO;
	
		THROW_FAILED_HRESULT(DataObjectCreateInstance (NULL, IID_IDataObject, IDO.ppv()));
		THROW_FAILED_HRESULT(hr = SetEnumLONGData (EnumObj, IDO));

		*ppDataObj = IDO.detach();

	} COM_CATCH_OP(delete m_pCfgDlg);

	if (S_OK != hr)				// nach dem letzten Aufruf
		DELETE_OBJ(m_pCfgDlg);		// Dialog wird nicht mehr gebraucht
	return hr;
}

/////////////////////////////////////////////////////////////////////////////
// IClassProperty specific functions
STDMETHODIMP CGenTextPropAct::GetPropInfo (LPSTR pBuffer, WORD wLen, DWORD *pdwFlags)
{
	if (NULL != pBuffer && wLen > 0) {
	// Namen der Property kopieren
	ULONG ulLen = tmin ((size_t)(wLen-1), m_strDesc.length());

		strncpy (pBuffer, m_strDesc.c_str(), ulLen);
		pBuffer[ulLen] = '\0';
	}

// wenn gewünscht, Flags übergeben
	if (pdwFlags) *pdwFlags = PROPCAPS_ACTION_SINK_MULTI|PROPCAPS_ACTION_SOURCE|PROPCAPS_ACTION_MUSTREPAINT;
	return NOERROR;
}

STDMETHODIMP CGenTextPropAct::HelpInfo (LPSTR pBuffer, ULONG wLen, LPSTR pHelpFile, ULONG *pulHelpCtx)
{
	try {
		if (NULL != pBuffer && wLen > 0) {
		// Beschreibung übergeben
		ResourceFile RF (g_pDLLName);
		ResString resHelp (ResID (IDS_HELPDESC_GENTEXTPROPACT, &RF), 128);
		ULONG ulLen = tmin ((size_t)(wLen-1), strlen(resHelp));

			strncpy (pBuffer, resHelp, ulLen);
			pBuffer[ulLen] = '\0';
		}
	} catch (...) {
		return E_FAIL;
	}

// HelpFileInfo übergeben
	if (pHelpFile) pHelpFile[0] = '\0';
	if (pulHelpCtx) *pulHelpCtx = 0L;
	
return NOERROR;
}

/////////////////////////////////////////////////////////////////////////////
// IPropertyInfo specific functions 
STDMETHODIMP CGenTextPropAct::SetPropInfo (LPCSTR pcBuffer, DWORD dwFlags) 
{
	if (NULL == pcBuffer) return E_POINTER;

	m_strDesc = pcBuffer;
	return NOERROR;
}

/////////////////////////////////////////////////////////////////////////////
// IPersist methods
STDMETHODIMP CGenTextPropAct::GetClassID (CLSID *pClsID)
{
	if (NULL == pClsID)
		return E_POINTER;

	*pClsID = CLSID_GenTextPropAct;
	return NOERROR;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistStreamInit methods
STDMETHODIMP CGenTextPropAct::IsDirty(void)
{
	return m_fIsDirty ? S_OK : S_FALSE;
}

STDMETHODIMP CGenTextPropAct::Load(LPSTREAM pStm)
{
	if (m_fIsInitialized)
		return E_UNEXPECTED;		// already initialized with InitNew

HRESULT hr = CPropertyAction::Load (pStm);

	if (FAILED(hr)) return hr;

	COM_TRY {
		m_Status.erase();

		TX_ASSERT(sizeof(BOOL) == sizeof(long));
		
		THROW_FAILED_HRESULT(LoadLong(pStm, (long &)m_Status.m_fFromObjProp));
		THROW_FAILED_HRESULT(LoadLong(pStm, (long &)m_Status.m_fDependend));
		THROW_FAILED_HRESULT(LoadLong(pStm, (long &)m_Status.m_fDelete));
		THROW_FAILED_HRESULT(LoadLong(pStm, (long &)m_Status.m_fRotate));
		THROW_FAILED_HRESULT(LoadLong(pStm, (long &)m_Status.m_fDoNotMove));
		THROW_FAILED_HRESULT(LoadLong(pStm, (long &)m_Status.m_fDynamic));
		THROW_FAILED_HRESULT(LoadLong(pStm, (long &)m_Status.m_fDeleteTarget));

		THROW_FAILED_HRESULT(LoadString(pStm, m_Status.m_strDirectText));

	CDirectTextList::size_type lCnt = 0;

		THROW_FAILED_HRESULT(LoadLong(pStm, (long &)lCnt));
		for (CDirectTextList::size_type i = 0; i < lCnt; i++) {
		os_string str;

			THROW_FAILED_HRESULT(LoadString(pStm, str));
			m_Status.m_lstDirectText.push_back(str);
		}

		THROW_FAILED_HRESULT(LoadString(pStm, m_Status.m_strObjProp));

	} COM_CATCH;

	m_fIsInitialized = true;
	m_fIsDirty = false;
	return NOERROR;
}

STDMETHODIMP CGenTextPropAct::Save (LPSTREAM pStm, BOOL fClearDirty)
{
// zuerst Bezeichner wegschreiben
HRESULT hr = CPropertyAction::Save (pStm, fClearDirty);

	if (FAILED(hr)) return hr;

	COM_TRY {
		THROW_FAILED_HRESULT(SaveLong(pStm, m_Status.m_fFromObjProp));
		THROW_FAILED_HRESULT(SaveLong(pStm, m_Status.m_fDependend));
		THROW_FAILED_HRESULT(SaveLong(pStm, m_Status.m_fDelete));
		THROW_FAILED_HRESULT(SaveLong(pStm, m_Status.m_fRotate));
		THROW_FAILED_HRESULT(SaveLong(pStm, m_Status.m_fDoNotMove));
		THROW_FAILED_HRESULT(SaveLong(pStm, m_Status.m_fDynamic));
		THROW_FAILED_HRESULT(SaveLong(pStm, m_Status.m_fDeleteTarget));

		THROW_FAILED_HRESULT(SaveString(pStm, m_Status.m_strDirectText));

		THROW_FAILED_HRESULT(SaveLong(pStm, m_Status.m_lstDirectText.size()));
		for (CDirectTextList::iterator it = m_Status.m_lstDirectText.begin(); 
			 it != m_Status.m_lstDirectText.end(); ++it)
		{
			THROW_FAILED_HRESULT(SaveString(pStm, *it));
		}

		THROW_FAILED_HRESULT(SaveString(pStm, m_Status.m_strObjProp));

	} COM_CATCH;

// dann selektierte Info der letzten Auswahl
	if (fClearDirty) 
		m_fIsDirty = false;
	return NOERROR;
}

STDMETHODIMP CGenTextPropAct::GetSizeMax (ULARGE_INTEGER *pcbSize)
{
	if (NULL == pcbSize) return E_POINTER;

ULARGE_INTEGER cbSize;
HRESULT hr = CPropertyAction::GetSizeMax (&cbSize);

	if (FAILED(hr)) return hr;

LARGE liOwnSize (UINT(5*sizeof(LONG)));

	liOwnSize = liOwnSize + LARGE(UINT(::GetSizeMax (m_Status.m_strDirectText)));
	for (CDirectTextList::iterator it = m_Status.m_lstDirectText.begin(); 
		 it != m_Status.m_lstDirectText.end(); ++it)
	{
		liOwnSize = liOwnSize + LARGE(UINT(::GetSizeMax (*it)));
	}
	liOwnSize = liOwnSize + LARGE(UINT(::GetSizeMax (m_Status.m_strObjProp)));

	liOwnSize = liOwnSize + LARGE(cbSize);
	*pcbSize = liOwnSize;
	return S_OK;
}

STDMETHODIMP CGenTextPropAct::InitNew(void)
{
	if (m_fIsInitialized)
		return E_UNEXPECTED;		// already initialized with Load

	m_fIsInitialized = true;
	m_fIsDirty = false;
	return NOERROR;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistPropertyBag
// mögliche SteuerParameter
//	ObjProp="..."	aus Objekteigenschaft ... generieren
//	Direct="..."	aus gegebenem Text erzeugen
//	Dependend=1		abhängige Texte erzeugen
//	Dynamic=1		dynamische Text erzeugeen (nur bei ObjProp und Dependend)
//	Delete=1		evtl existierende Texte vorher löschen (nur bei Dependend)
//	DoNotMove=1		an Punktobjekte nicht verschieben
//	Rotate=1		an Linienobjekten drehen (nur bei Dependend)
//  DeleteTarget=1	Bezugsobjekt nach Texterzeugen weglöschen
STDMETHODIMP CGenTextPropAct::Load (IPropertyBag *pBag, IErrorLog *pLog)
{
	USES_CONVERSION;
	RETURN_FAILED_HRESULT(CPropertyAction::Load (pBag, pLog));

	m_Status.erase();

CComVariant vParam;
HRESULT hr = pBag -> Read (CComBSTR(g_cbObjProp), &vParam, pLog);

	if (S_OK == hr && SUCCEEDED(vParam.ChangeType (VT_BSTR)))
	{
		m_Status.m_strObjProp = OLE2A(V_BSTR(&vParam));
	}

// Direct=
	vParam.Clear();
	hr = pBag -> Read (CComBSTR(g_cbDirect), &vParam, pLog);
	if (S_OK == hr && SUCCEEDED(vParam.ChangeType (VT_BSTR)))
	{
		m_Status.m_strDirectText = OLE2A(V_BSTR(&vParam));
	}
// Dependend=
	vParam.Clear();
	hr = pBag -> Read (CComBSTR(g_cbDependend), &vParam, pLog);
	if (S_OK == hr && SUCCEEDED(vParam.ChangeType (VT_BOOL)))
	{
		m_Status.m_fDependend = V_BOOL(&vParam) ? TRUE : FALSE;
	}

// Dynamic=
	vParam.Clear();
	hr = pBag -> Read (CComBSTR(g_cbDynamic), &vParam, pLog);
	if (S_OK == hr && SUCCEEDED(vParam.ChangeType (VT_BOOL)))
	{
		m_Status.m_fDynamic = V_BOOL(&vParam) ? TRUE : FALSE;
	}

// Delete=
	vParam.Clear();
	hr = pBag -> Read (CComBSTR(g_cbDelete), &vParam, pLog);
	if (S_OK == hr && SUCCEEDED(vParam.ChangeType (VT_BOOL)))
	{
		m_Status.m_fDelete = V_BOOL(&vParam) ? TRUE : FALSE;
	}

// Rotate=
	vParam.Clear();
	hr = pBag -> Read (CComBSTR(g_cbRotate), &vParam, pLog);
	if (S_OK == hr && SUCCEEDED(vParam.ChangeType (VT_BOOL)))
	{
		m_Status.m_fRotate = V_BOOL(&vParam) ? TRUE : FALSE;
	}

	if (m_Status.m_fDependend) {
	// DoNotMove=
		vParam.Clear();
		hr = pBag -> Read (CComBSTR(g_cbDoNotMove), &vParam, pLog);
		if (S_OK == hr && SUCCEEDED(vParam.ChangeType (VT_BOOL)))
		{
			m_Status.m_fDoNotMove = V_BOOL(&vParam) ? TRUE : FALSE;
		}
	} else {
	// DeleteTarget=
		vParam.Clear();
		hr = pBag -> Read (CComBSTR(g_cbDeleteTarget), &vParam, pLog);
		if (S_OK == hr && SUCCEEDED(vParam.ChangeType (VT_BOOL)))
		{
			m_Status.m_fDeleteTarget = V_BOOL(&vParam) ? TRUE : FALSE;
		}
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Sonstiges
void CGenTextPropAct::SetDirty (bool fDirty) { m_fIsDirty = fDirty; }
