// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 09/23/1998 07:18:21 PM
//
// @doc
// @module ObjekteVereinigen.cpp | Implementation of the <c CObjekteVereinigen> class

#include "trias03p.hxx"

#include "trias03.h"

#include <xtsnguid.h>
#include <eonrguid.h>
#include <bscrguid.h>
#include <ScriptPropActGuid.h>
#include <ObjekteVereinigenGuid.h>
#include <TrCatIds.h>

#include <eb.h>
#include <ibscript.hxx>

#include <Com/ComBool.h>

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "Strings.h"
#include "DataHelp.h"
#include "Propactb.hxx"
#include "ObjekteVereinigen.h"
#include "ObjekteVereinigenDlg.h"

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(PropertyAction);
DefineSmartInterface(ClassProperty);
DefineSmartInterface(PersistStream);
DefineSmartInterface(PersistStreamInit);
DefineSmartInterface(PersistPropertyBag);
DefineSmartInterface(ExtendBScript);

#if _TRiAS_VER < 0x0400
extern DWORD g_dwVer4;

///////////////////////////////////////////////////////////////////////////////
// in TRiASV3 nicht registrieren
/*static*/
HRESULT WINAPI CObjekteVereinigenEx::UpdateRegistry(BOOL fRegister)
{
	if (0 != g_dwVer4)
		return _Module.UpdateRegistryFromResource(IDR_OBJEKTEVEREINIGEN, fRegister);
	return S_OK;	// so tun, als ob's ok wäre ... :-)
}
#endif // _TRiAS_VER < 0x0400

/////////////////////////////////////////////////////////////////////////////
// CObjekteVereinigen
CObjekteVereinigenEx::~CObjekteVereinigenEx()
{
	DELETE_OBJ(m_pCfgDlg);
}

STDMETHODIMP CObjekteVereinigenEx::BeginAction (IProgressIndicator *pIProgInd)
{
WPropertyAction BaseObj;

	RETURN_FAILED_HRESULT(m_BaseUnk -> QueryInterface (BaseObj.ppi()));
	return BaseObj -> BeginAction (pIProgInd);
}

HRESULT CObjekteVereinigenEx::InitBool (IExtendBScript *pBasic, LPCSTR pcName, VARIANT_BOOL fFlag)
{
// BasicOperationen
ebPARAM Pars[2];
LPVOID cbParam[2];
BSPARAM bs = { Pars, cbParam };

// Sub SetBlaFlag (fFlag As Boolean)
	Pars[0].wType = 0;				// SubRoutine
	Pars[0].szExtType[0] = '\0';
	cbParam[0] = NULL;

	Pars[1].wType = TYP_BOOLEAN;
	Pars[1].szExtType[0] = '\0';
	cbParam[1] = &fFlag;

// Script starten
	USES_CONVERSION;
	pBasic -> ExecuteMethod (OLE2A(g_cbObjekteVereinigen), pcName, 1, &bs, FALSE, NULL);	// Fehler ignorieren
	return S_OK;
}

STDMETHODIMP CObjekteVereinigenEx::DoAction (IDataObject *pEnumObj, DWORD dwReserved)
{
// Daten vom Dialog holen
	m_fDeleteObjs = m_pCfgDlg -> GetDeleteObjs();
	m_fMarkObjs = m_pCfgDlg -> GetMarkObjs();
	m_fCopyObjs = m_pCfgDlg -> GetCopyObjs();

// Daten im Script voreinstellen
#if _TRiAS_VER < 0x0400
	if (0 != g_dwVer4)
#endif // _TRiAS_VER < 0x0400
	{
	WExtendBScript BasicEngine;
	WInitScriptPropAct InitPA;

		if (SUCCEEDED(m_BaseUnk -> QueryInterface(InitPA.ppi()))) {
			RETURN_FAILED_HRESULT(InitPA -> GetScriptEngine(__uuidof(IExtendBScript), BasicEngine.ppu()));
			InitBool (BasicEngine, "SetDeleteFlag", CComBool(m_fDeleteObjs));
			InitBool (BasicEngine, "SetMarkFlag", CComBool(m_fMarkObjs));
			InitBool (BasicEngine, "SetCopyFlag", CComBool(m_fCopyObjs));
		}
	}

// Eigentliche Aktion ausführen
WPropertyAction BaseObj;

	RETURN_FAILED_HRESULT(m_BaseUnk -> QueryInterface (BaseObj.ppi()));
	return BaseObj -> DoAction (pEnumObj, dwReserved);
}

STDMETHODIMP CObjekteVereinigenEx::EndAction (DWORD dwReserved, IDataObject **ppEnumObj)
{
// Eigentliche Aktion ausführen
WPropertyAction BaseObj;

	RETURN_FAILED_HRESULT(m_BaseUnk -> QueryInterface (BaseObj.ppi()));

HRESULT hr = BaseObj -> EndAction (dwReserved, ppEnumObj);

	if (S_FALSE != hr && NULL != m_pCfgDlg) {
		delete m_pCfgDlg;
		m_pCfgDlg = NULL;
	}
	return hr;
}

STDMETHODIMP CObjekteVereinigenEx::PreConfigPages (IDataObject *pIDataObject, DWORD dwFlags)
{
	if (NULL != m_pCfgDlg)
		m_pCfgDlg -> SetFlags (dwFlags);
	return S_OK;
}

STDMETHODIMP CObjekteVereinigenEx::AddConfigPages (LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam, LPCSTR pcDesc, UINT *puiCnt)
{
	if (puiCnt) *puiCnt = 0;		// initialisieren

#if _TRiAS_VER < 0x0400
	if (0 == g_dwVer4)
		return S_OK;		// mehr gibts nicht
#endif // _TRiAS_VER < 0x0400

	COM_TRY {
	char cbCaption[128];

		if (NULL != pcDesc)	{	// Caption ist gegeben
			_ASSERTE(strlen(pcDesc) < sizeof(cbCaption));
			strcpy (cbCaption, pcDesc);
		} else {	// von zugehöriger ClassProperty unseren Namen besorgen
		WClassProperty ClsProp (GetControllingUnknown());

			ClsProp -> GetPropInfo (cbCaption, sizeof(cbCaption), NULL);
		}

	// zugehörigen ConfigDialoge (PropertyPage(s)) anlegen
		DELETE_OBJ(m_pCfgDlg);

		m_pCfgDlg = CObjekteVereinigenDlg::CreateInstance(cbCaption);
		if (NULL == m_pCfgDlg) _com_issue_error(E_OUTOFMEMORY);

		if (!IsNoShow()) {
		// Seiten hizufügen, wenn selbige angezeigt werden soll
		HPROPSHEETPAGE hPSP = this -> CreatePage(m_pCfgDlg);

			if (NULL == hPSP) return E_HANDLE;
			if (!(*lpfnAddPage) (hPSP, lParam))
				return E_FAIL;

			if (puiCnt) *puiCnt = 1;		// wir haben drei Pages hinzugefügt
		} 

	// Vorinitialisierungen
		m_pCfgDlg -> SetInitialData(m_fDeleteObjs, m_fMarkObjs, m_fCopyObjs);

	} COM_CATCH_OP((delete m_pCfgDlg, m_pCfgDlg = NULL));
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// IPersist
STDMETHODIMP CObjekteVereinigenEx::GetClassID (CLSID *pClsID)
{
	*pClsID = GetObjectCLSID();
	return S_OK;
}

STDMETHODIMP CObjekteVereinigenEx::IsDirty()
{
// Basisklasse fragen
WPersistStream Persist;

	RETURN_FAILED_HRESULT(m_BaseUnk -> QueryInterface(Persist.ppi()));
	return Persist -> IsDirty();
}

STDMETHODIMP CObjekteVereinigenEx::Load (IStream *pStm)
{
// Basisklasse laden
WPersistStream Persist;

	RETURN_FAILED_HRESULT(m_BaseUnk -> QueryInterface(Persist.ppi()));
	RETURN_FAILED_HRESULT(Persist -> Load (pStm));

// unsere Daten laden
	RETURN_FAILED_HRESULT(LoadData(pStm, m_fDeleteObjs));
	RETURN_FAILED_HRESULT(LoadData(pStm, m_fMarkObjs));
	RETURN_FAILED_HRESULT(LoadData(pStm, m_fCopyObjs));

	return S_OK;
}

STDMETHODIMP CObjekteVereinigenEx::Save (IStream *pStm, BOOL fClearDirty)
{
// Basisklasse speichern
WPersistStream Persist;

	RETURN_FAILED_HRESULT(m_BaseUnk -> QueryInterface(Persist.ppi()));
	RETURN_FAILED_HRESULT(Persist -> Save (pStm, fClearDirty));

// unsere Daten laden
	RETURN_FAILED_HRESULT(SaveData(pStm, m_fDeleteObjs));
	RETURN_FAILED_HRESULT(SaveData(pStm, m_fMarkObjs));
	RETURN_FAILED_HRESULT(SaveData(pStm, m_fCopyObjs));

	return S_OK;
}

STDMETHODIMP CObjekteVereinigenEx::GetSizeMax (ULARGE_INTEGER *pcbSize)
{
// Basisklasse fragen
WPersistStream Persist;

	RETURN_FAILED_HRESULT(m_BaseUnk -> QueryInterface(Persist.ppi()));
	RETURN_FAILED_HRESULT(Persist -> GetSizeMax(pcbSize));

// unsere Daten dranhängen
	pcbSize -> QuadPart += 2*sizeof(bool);
	return S_OK;
}

STDMETHODIMP CObjekteVereinigenEx::InitNew ()
{
// Basisklasse initialisieren
WPersistStreamInit Persist;

	RETURN_FAILED_HRESULT(m_BaseUnk -> QueryInterface(Persist.ppi()));
	RETURN_FAILED_HRESULT(Persist -> InitNew());

	m_fDeleteObjs = true;
	m_fMarkObjs = false;
	m_fCopyObjs = true;
	return S_OK;
}

// IPersistPropertyBag
STDMETHODIMP CObjekteVereinigenEx::Load (IPropertyBag *pBag, IErrorLog *pLog)
{
// Basisklasse behandlen
WPersistPropertyBag Persist;

	RETURN_FAILED_HRESULT(m_BaseUnk -> QueryInterface(Persist.ppi()));
	RETURN_FAILED_HRESULT(Persist -> Load(pBag, pLog));

	m_fDeleteObjs = true;
	m_fMarkObjs = false;
	m_fCopyObjs = true;
	m_fNoShow = false;

// DeleteSrcObjs=
CComVariant vDeleteSrcObjs;
HRESULT hr = pBag -> Read (CComBSTR(g_cbDeleteSrcObjs), &vDeleteSrcObjs, pLog);

	if (S_OK == hr && SUCCEEDED(vDeleteSrcObjs.ChangeType(VT_BOOL))) 
		m_fDeleteObjs = V_BOOL(&vDeleteSrcObjs) ? true : false;

	if (!m_fDeleteObjs) {	// es darf nur einer von beiden gesetzt sein
	// MarkSrcObjs=
	CComVariant vMarkSrcObjs;

		hr = pBag -> Read (CComBSTR(g_cbMarkSrcObjs), &vMarkSrcObjs, pLog);
		if (S_OK == hr && SUCCEEDED(vMarkSrcObjs.ChangeType(VT_BOOL))) 
			m_fMarkObjs = V_BOOL(&vMarkSrcObjs) ? true : false;

	// CopySrcObjs=
	CComVariant vCopySrcObjs;

		hr = pBag -> Read (CComBSTR(g_cbCopySrcObjs), &vCopySrcObjs, pLog);
		if (S_OK == hr && SUCCEEDED(vCopySrcObjs.ChangeType(VT_BOOL))) 
			m_fCopyObjs = V_BOOL(&vCopySrcObjs) ? true : false;
	}

// NoShow=
CComVariant vNoShow;

	hr = pBag -> Read (CComBSTR(g_cbPANoShow), &vNoShow, pLog);
	if (S_OK == hr && SUCCEEDED(vNoShow.ChangeType(VT_BOOL))) 
		m_fNoShow = V_BOOL(&vNoShow) ? true : false;

	return S_OK;
}

