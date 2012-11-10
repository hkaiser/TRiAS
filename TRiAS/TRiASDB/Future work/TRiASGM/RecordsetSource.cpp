// @doc
// @module RecordsetSource.cpp | Implementation of the <c CRecordsetSource>
// class

#include "stdafx.h"

//#include <sys/stat.h>
#include <ActDB.h>
#include <Array.h>

#include <GFWSysTbl.h>
#include <CGFW.h>
#include <CAliasTblInMemRecSet.h>
#include <CCoordSysInMemRecSet.h>
#include "OKSInMemRecordSet.h"
#include "FeatureInMemRecordSet.h"

#include <ErrInst.hxx>
#include <NativeIdent.h>
#include <NativeView.h>

#include "CssHeader.h"
#include "Strings.h"
#include "TRiASGM.h"
#include "RecordsetSource.h"
#include "TRiASSourceInfo.h"

using namespace trias_nativeident;
using namespace trias_nativeview;

#if defined(_DEBUG)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

/////////////////////////////////////////////////////////////////////////////
// Funktionsprototypen
long GetGeometryType (DWORD dwTypes, BOOL *pfHasTexts = NULL);

/////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(GDOFramework);
DefineSmartInterface(RecordsetGenerator);

DefineSmartInterfaceEx(GMRefSpaceMgr);
DefineSmartInterfaceEx(GMGeogSpace);
DefineSmartInterfaceEx(GMProjSpace);

DefineSmartInterface(Storage);
DefineSmartInterface(Dispatch);

DefineSmartInterface(TRiASSourceInfo);		// WTRiASSourceInfo 

/////////////////////////////////////////////////////////////////////////////
// CRecordsetSource

HRESULT CRecordsetSource::FinalConstruct()
{
	try {
	WGDOFramework FrmWrk (CLSID_GDOFrameWork);

		THROW_FAILED_HRESULT(FrmWrk -> CreateGDatabase (this, &m_pIDB));

	} catch (_com_error &e) {
		ASSERT(SUCCEEDED(_COM_ERROR(e)));
		return _COM_ERROR(e);
	}
	return S_OK;
}

// Die folgende Funktion hat die Aufgabe _einmalig_ bei QI einen Pointer auf ein
// GDatabase-Objekt zu liefern.
// (very very ugly, violates COM-specification !)
HRESULT WINAPI CRecordsetSource::_RetrievePtr(void* pv, REFIID iid, void** ppvObject, DWORD dw)
{
HRESULT hRes = E_NOINTERFACE;
CRecordsetSource *pObj = (CRecordsetSource *)pv;

	if (NULL == pObj->m_pIDB) {
		ASSERT(NULL != pObj->m_pIDB);
		return hRes;
	}
	*ppvObject = pObj -> m_pIDB;		// wie gesagt nur einmal liefern
	pObj -> m_pIDB = NULL;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// This method is called when OpenDatabase is called on the GDO Framework 
// GDatabase object
STDMETHODIMP CRecordsetSource::OpenSource (
	BSTR Name, VARIANT vExclusive, VARIANT vReadonly, VARIANT vModTrack, VARIANT vSource)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL != m_hPr)
		return TRIASDB_W_ALREADY_OPENED;

// Werte aus Parametern besorgen und speichern
CComVariant v;

	m_fIsReadOnly = true;
	if (SUCCEEDED(v.ChangeType (VT_BOOL, &vReadonly)))
		m_fIsReadOnly = V_BOOL(&v) ? true : false;

	if (SUCCEEDED(v.ChangeType (VT_BSTR, &vSource)))
		m_bstrSource = V_BSTR(&v);

	m_bstrName = Name;
	if (!m_bstrName)
		return E_OUTOFMEMORY;

	USES_CONVERSION;
	try {
	// Datenbank jetzt entsprechend Vorgaben öffnen
		m_hPr = Open(OLE2A(m_bstrName), m_fIsReadOnly);	// erfolgreich geöffnet (throws hr)

		THROW_FAILED_HRESULT(OpenMetaDatabase());		// Pbd dazu eröffnen

	} catch (_com_error &e) {
		if (NULL != m_hPr) 
			Close();		// wieder schließen

		ASSERT(SUCCEEDED(_COM_ERROR(e)));
		return _COM_ERROR(e);
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// This method is called when the GDO Framework needs to build a list 
// of GTableDef objects 
os_string CorrectName (LPCSTR pcName)
{
#if !defined(_CONVERT_NAMES)

	return os_string('[') + pcName + ']';
#else
os_string str;
LPCSTR pT = pcName;

	while (*pT) {
		if (isalnum(*pT))
			str += *pT;
		else switch (*pT) {
		case 'ä':
		case 'ö':
		case 'ü':
		case 'Ä':
		case 'Ö':
		case 'Ü':
		case 'ß':
			str += *pT;
			break;

		default:
			str += '_';
			break;
		}
		pT++;	// nächstes Zeichen
	}
	return str;
#endif // _CONVERT_NAMES
}

HRESULT CALLBACK CRecordsetSource::EnumIdentCallBack (LONG lIdent, DWORD dwTypes, DWORD dwData)
{
CEnumIdentEntryCallback *pData = reinterpret_cast<CEnumIdentEntryCallback *>(dwData);

	try {
	ErrInstall EI (WC_NOIDENT);
	CNativeIdent Ident (pData->m_pRSS->GetHandle(), lIdent, dwTypes);
	char cbBuffer[_MAX_PATH];
	char cbLText[_MAX_PATH];
	BOOL fHasTexts = FALSE;
	long lgdbType = GetGeometryType(dwTypes, &fHasTexts);

		THROW_FAILED_HRESULT(Ident.GetName (cbBuffer, sizeof(cbBuffer)));
		if (FAILED(Ident.GetDescription (cbLText, sizeof(cbLText))))
			cbLText[0] = '\0';

		if (fHasTexts) {
		// spezielle Behandlung wenn Texte mit was anderem
		os_string str (cbBuffer);
		CString strApp;

			VERIFY(strApp.LoadString(IDS_APPENDTEXT));
			str += strApp;

			pData->m_pNames->insert(CorrectName(str.c_str()), CTableEntry(lIdent, OTText, str.c_str(), cbLText));
			dwTypes &= ~OTText;
		}
		pData->m_pNames->insert(CorrectName(cbBuffer), CTableEntry(lIdent, dwTypes, cbBuffer, cbLText));

	} catch (_com_error &e) {
		ASSERT(SUCCEEDED(_COM_ERROR(e)));
		return _COM_ERROR(e);
	} catch(...) {
		ASSERT(SUCCEEDED(E_OUTOFMEMORY));
		return E_OUTOFMEMORY;
	}
	return S_OK;
}

HRESULT CRecordsetSource::EnumViewCallBack (LPCSTR pcView, DWORD dwData)
{
CEnumViewEntryCallback *pData = reinterpret_cast<CEnumViewEntryCallback *>(dwData);

	try {
	CString str;

		VERIFY(str.LoadString(IDS_VIEWPREFIX));
		str += CorrectName(pcView).c_str();
		pData->m_pViews->insert(os_string(str), os_string(pcView));

	} catch (_com_error &e) {
		ASSERT(SUCCEEDED(_COM_ERROR(e)));
		return _COM_ERROR(e);
	} catch(...) {
		ASSERT(SUCCEEDED(E_OUTOFMEMORY));
		return E_OUTOFMEMORY;
	}
	return S_OK;
}

STDMETHODIMP CRecordsetSource::GetTableNames (SAFEARRAY **pTableNames)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pTableNames)
		return E_POINTER;

	try {
	// Objektklassen enumerieren
		{
		CEnumIdentEntryCallback CallBackData;

			m_Names.erase();
			CallBackData.m_pRSS = this;
			CallBackData.m_pNames = &m_Names;
			THROW_FAILED_HRESULT(CNativeIdent::EnumIdents (m_hPr, EnumIdentCallBack, reinterpret_cast<DWORD>(&CallBackData)));
		}

	// Ansichten enumerieren
		{
		CEnumViewEntryCallback CallBackData;

			m_Views.erase();
			CallBackData.m_pRSS = this;
			CallBackData.m_pViews = &m_Views;
			THROW_FAILED_HRESULT(CNativeView::EnumViews (m_hPr, EnumViewCallBack, reinterpret_cast<DWORD>(&CallBackData)));
		}

	// gefundene OKS-Bezeichner umkopieren 
	CSafeArray sa (VT_BSTR, m_Names.size()+m_Views.size()+4);	// + 3 Systemtabellen + Objektklassen

		{
		CSafeArrayLock<BSTR> lock(sa);
		BSTR *pActBstr = lock;

		// Objektklassen hinzufügen
			for (CTables::iterator it = m_Names.begin(); it != m_Names.end(); ++it)
			{
				ASSERT(size_t(pActBstr - lock) < m_Names.size());

			CComBSTR bstr((*it).first.c_str());

				*pActBstr++ = bstr.Detach();
			}

		// Ansichten hinzufügen
#if defined(_DEBUG)
		BSTR *pTmp = pActBstr;
#endif // _DEBUG

			for (CViews::iterator viewit = m_Views.begin(); viewit != m_Views.end(); ++viewit)
			{
				ASSERT(size_t(pActBstr - pTmp) < m_Views.size());

			CComBSTR bstr((*viewit).first.c_str());

				*pActBstr++ = bstr.Detach();
			}

		// Systemtabellen nicht vergessen
		CComBSTR bstr (GFWAliasTableName);		// GAliasTable

			*pActBstr++ = bstr.Detach();
			bstr = GFWCSTableName;				// GCoordSystem
			*pActBstr++ = bstr.Detach();
			bstr = GFWFeaturesTableName;		// GFeatures
			*pActBstr++ = bstr.Detach();

		// Objektklassen in einer eigenen Tabelle liefern
			bstr = g_cbMetaData;
			*pActBstr++ = bstr.Detach();
		}

	// Ergebnis liefern
		*pTableNames = sa.Detach();

	} catch (_com_error &e) {
		ASSERT(SUCCEEDED(_COM_ERROR(e)));
		return _COM_ERROR(e);
	}
	return S_OK;
}
  
// This method is called when the GDO Framework needs to create a Framework 
// GRecordset for the client and it doesn't have the source GRecordset for a 
// certain feature.
STDMETHODIMP CRecordsetSource::GetGRecordset (
	BSTR TableName, GRecordset **pSourceGRecordset)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	USES_CONVERSION;

// spezielle Tabellen direkt liefern
	if (!wcscmp(TableName, GFWAliasTableName)) 
		return GetAliasTableRecordset (pSourceGRecordset);

	if (!wcscmp(TableName, GFWCSTableName)) 
		return GetCSTableRecordset (pSourceGRecordset);

	if (!wcscmp(TableName, GFWFeaturesTableName)) 
		return GetFeatureTableRecordset (pSourceGRecordset);

	if (!wcscmp(TableName, A2OLE(g_cbMetaData)))
		return GetMetaTableRecordSet (pSourceGRecordset);

// Ansichten und Objektklassen getrennt behandeln
CViews::iterator it = m_Views.find (OLE2A(TableName));

	if (it != m_Views.end())	// es ist eine Ansicht
		return GetViewRecordset (TableName, CComBSTR((*it).second.c_str()), pSourceGRecordset);

	if (!m_CoordSys.IsValid()) {
	// Koordinatensystem sicherstellen
	WGRecordset tmp;
		
		RETURN_FAILED_HRESULT(GetCSTableRecordset (tmp.ppi()));	
	}
	return GetOKSRecordset (TableName, pSourceGRecordset);
}

///////////////////////////////////////////////////////////////////////////////
// Recordset für Ansichten generieren
HRESULT CRecordsetSource::GetViewRecordset (
	BSTR TableName, BSTR bstrView, GRecordset **pSourceGRecordset)
{
	USES_CONVERSION;
	try {
	// durch Ansichts-RecordsetGenerator erzeugen lassen
	WRecordsetGenerator GenRS(CLSID_ViewRecordsetGenerator);

		THROW_FAILED_HRESULT(GenRS -> SetFeatureName (bstrView));

	WTRiASSourceInfo SrcInfo;

		THROW_FAILED_HRESULT(GenerateViewSourceInfo (TableName, SrcInfo.ppi()));
		THROW_FAILED_HRESULT(GenRS -> SetSourceInfo (CComVariant(SrcInfo)));
		THROW_FAILED_HRESULT(GenRS -> GetOutputRecordset (pSourceGRecordset))

	} catch (_com_error &e) {
		return _COM_ERROR(e);
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Recordset für Objektklassen erzeugen
HRESULT CRecordsetSource::GetOKSRecordset (
	BSTR TableName, GRecordset **pSourceGRecordset)
{
	USES_CONVERSION;
	try {
#if defined(_DEBUG)
	CTables::iterator oksit = m_Names.find(OLE2A(TableName));

		ASSERT(oksit != m_Names.end());		// muß existieren
#endif // _DEBUG

	// alle sonstigen durch OKS-RecordsetGenerator erzeugen lassen
	WRecordsetGenerator GenRS(CLSID_OKSRecordsetGenerator);

		THROW_FAILED_HRESULT(GenRS -> SetFeatureName (TableName));

	WTRiASSourceInfo SrcInfo;

		THROW_FAILED_HRESULT(GenerateOKSSourceInfo (TableName, SrcInfo.ppi()));
		THROW_FAILED_HRESULT(GenRS -> SetSourceInfo (CComVariant(SrcInfo)));
		THROW_FAILED_HRESULT(GenRS -> GetOutputRecordset (pSourceGRecordset))

	} catch (_com_error &e) {
		ASSERT(SUCCEEDED(_COM_ERROR(e)));
		return _COM_ERROR(e);
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// This method is called when the GDO Framework needs to collect information 
// about this server. e.g. CaseSensitive? ReadOnly? DataUpdatable? 
// Server Version? CollatingOrder? The GDO Framework assumes the defaults 
// whenever the returned VARIANT value is VT_EMPTY.

namespace {
	struct tagPROPERTY {
		LPOLESTR m_poleName;
		VARIANT m_vValue;
	} g_cbProps[] = {
		{ L"Updatable", { VT_BOOL, { VARIANT_FALSE } } },
		{ L"SchemaUpdatable", { VT_BOOL, { VARIANT_FALSE } } },
	};
}

STDMETHODIMP CRecordsetSource::GetProperty (
	BSTR pPropName, VARIANT *pPropValue)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	TRACE("GetProperty: asked for %ls.\r\n", pPropName);

// alle bekannten Properties durchgehen
bool fFound = false;

	for (long i = 0; i < _countof(g_cbProps); i++) {
		if (!wcscmp (pPropName, g_cbProps[i].m_poleName)) {
		CComVariant v;

			if (SUCCEEDED(v.Copy(&g_cbProps[i].m_vValue))) {
				v.Detach(pPropValue);
				fFound = true;
			}
			break;
		}
	}

// wenn nicht gefunden oder nicht zu behandeln, dann VT_EMPTY liefern
	if (!fFound) {
	CComVariant v;

		v.Detach(pPropValue);
	}
	return S_OK;
}

// This method is called whenever the OpenRecordset method is called on the GDatabase object
// of the GDO Framework. It's meant to be as a hook for the Recordset Source in case it needs
// to build the GRecordset itself. If the Recordset source doesn't want to implement the 
// OpenRecordset, it can simply return E_NOTIMPL which is the indication for the GDO 
// Framework to proceed and create a Framework GRecordset for the query.
STDMETHODIMP CRecordsetSource::OpenRecordset (
	BSTR pName,	VARIANT pType, VARIANT pOptions, VARIANT pSpatialOp, 
	VARIANT pSpatialGeometryFilter, VARIANT pGeometryFieldName,	
	GRecordset **ppGRecordset)
{
	ATLTRACENOTIMPL("CRecordsetSource::OpenRecordset");
}

///////////////////////////////////////////////////////////////////////////////
// Helperfunktionen

static bool TestFileRO (LPCSTR pcName, BOOL &rRO)
{
	rRO = (FILE_ATTRIBUTE_READONLY & GetFileAttributes(pcName)) ? TRUE : FALSE;
//
//struct _stat buf;
//int iResult = _stat (pcName, &buf);
//
//	if (0 != iResult || !(buf.st_mode & _S_IFREG)) 
//		return false;		// keine Datei oder existiert nicht
//
//	rRO = (buf.st_mode & _S_IWRITE) ? false : true;
	return true;
}

HPROJECT CRecordsetSource::Open (LPCTSTR pcName, bool &rfReadOnly)
{
	if (NULL == pcName) _com_issue_error(E_POINTER);

// set corresponding StorageModeFlags
DWORD dwMode = rfReadOnly ? STGM_READ : (STGM_READWRITE | STGM_SHARE_DENY_WRITE);

// try to open without error-reporting
HPROJECT hPr = (HPROJECT)z_open_ex ((LPTSTR)pcName, NULL, NULL, rfReadOnly ? TRUE : FALSE, dwMode, FALSE);

	if (NULL == hPr) {
	HRESULT hr = ::GetLastError();

		if (FACILITY_ERRCODE == HRESULT_FACILITY(hr)) {
		// Fehler ist in Wirklichkeit ein ErrCode
		ErrCode RC = ERRCODE_FROM_HRESULT(hr);

			switch (RC) {
			// nicht korrigierbare Fehler
			case EC_NOTAPROJECT:
				hr = TRIASDB_E_NOTAPROJECT;
				break;

			case EC_NOMEMORY:
				hr = E_OUTOFMEMORY;
				break;

			case EC_ACCESS:
				hr = TRIASDB_E_COULD_NOT_OPEN;
				break;
			}
		} else {
		// alle anderen hier bearbeiten
		BOOL fRO = rfReadOnly ? TRUE : FALSE;

			if (STG_E_SHAREVIOLATION == hr || STG_E_LOCKVIOLATION == hr) {
			// ZugriffsKonflikt
				if (!fRO && !TestFileRO (pcName, fRO)) 
					hr = TRIASDB_E_FILENOTEXISTS;	// keine Datei oder existiert nicht
				else
					hr = fRO ? TRIASDB_S_MUSTOPENASCOPY : TRIASDB_S_MUSTOPENASCOPY_SHAREVIOLATION;

			} else if (STG_E_ACCESSDENIED == hr) {
			// ZugriffsRechtsÜberschreitung (Datei ist lediglich ReadOnly)
				if (!TestFileRO (pcName, fRO)) 
					hr = TRIASDB_E_FILENOTEXISTS;	// keine Datei oder existiert nicht
				else 
					hr = TRIASDB_S_MUSTOPENASCOPY;
			}
		}

	// den Fehler nach oben propagieren
		_com_issue_error(hr);
	}

// evtl. alle Dateien auf ReadOnly setzen
	if (rfReadOnly) 
		z_access (hPr, Z_ALL|Z_RDONLY); 	// DB ReadOnly

	return hPr;
}

HRESULT CRecordsetSource::OpenMetaDatabase (void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == m_hPr)
		return TRIASDB_E_DATABASE_NOT_OPENED;

	USES_CONVERSION;
	try {
	// Storage der Datenbank besorgen
	WStorage Stg;

		THROW_FAILED_HRESULT(GetProjectStorage(Stg.ppi()));

	// SubStg öffnen (muß existieren !)
	WStorage PbdStg;
	DWORD dwMode = STGM_TRANSACTED|STGM_SHARE_EXCLUSIVE;
	bool fReadOnly = m_fIsReadOnly;

		if (m_fIsReadOnly) 
			dwMode |= STGM_READ;
		else
			dwMode |= STGM_READWRITE;

		THROW_FAILED_HRESULT(Stg -> OpenStorage(A2OLE(g_cbMetaData), NULL, dwMode, NULL, 0L, PbdStg.ppi()));
		m_hPrPbd = OpenStoragePbd (PbdStg, fReadOnly);

		if (NULL != m_hPrPbd) {		// Pbd dem TRiAS-Projekt zuordnen
			ASSERT(NULL != m_hPr);
			::SetRelatedProject (m_hPr, m_hPrPbd);
		}

	} catch (_com_error &e) {
		ASSERT(SUCCEEDED(_COM_ERROR(e)));
		return _COM_ERROR(e);
	}

	return S_OK;
}

HRESULT CRecordsetSource::Close()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == m_hPr)
		return TRIASDB_E_DATABASE_NOT_OPENED;

// ACHTUNG: Unter bestimmten Umständen kann/können die Datenbank(en) bereits durch
// TRiAS geschlossen worden sein (Übergangszustände vom alten zum neuen TRiAS), deshalb die
// total sinnlos erscheinenden Tests.
HRESULT hr = S_OK;
ErrCode RC = EC_OKAY;
BOOL fOpened = FALSE;
CComBSTR bstrTempName;

	get_TemporaryName (&bstrTempName);

// Pbd schließen
	VERIFY(::IsOpened (m_hPrPbd, &fOpened));
	if (fOpened && NULL != m_hPrPbd) {
	CActDB ActDB (m_hPrPbd);

		RC = (ErrCode)z_close (m_hPrPbd, false);	// PBD schließen, Fehler nicht fatal
		if (EC_OKAY != RC)
			hr = HRESULT_FROM_ERRCODE(RC);
		m_hPrPbd = NULL;
		ActDB.Reset();
	} else
		m_hPrPbd = NULL;

// Datenbank schließen
	VERIFY(::IsOpened (m_hPr, &fOpened));
	if (fOpened && NULL != m_hPr) {
	CActDB ActDB (m_hPr);

		RC = (ErrCode)z_close (m_hPr, false);	// DB schließen
		if (EC_OKAY != RC)
			hr = HRESULT_FROM_ERRCODE(RC);
		m_hPr = NULL;
		ActDB.Reset();
	} else
		m_hPr = NULL;

	if (m_fIsTemporary)	{	// Datei jetzt löschen, da temporär erzeugt
		USES_CONVERSION;
		DeleteFile (OLE2A(bstrTempName));
	}

	m_bstrName.Empty();
	m_bstrSource.Empty();

	return hr;
}

HRESULT CRecordsetSource::get_TemporaryName(BSTR * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == m_hPr)
		return TRIASDB_E_DATABASE_NOT_OPENED;
	if (NULL == pVal)
		return TRIASDB_E_INVALID_PARAMETER;

CComBSTR bstrName (m_bstrName);

	if (m_fIsTemporary) {
	WStorage IStorage;
		
		if (SUCCEEDED(::GetProjectStorage (m_hPr, IStorage.ppi()))) {
		STATSTG st;

			IStorage -> Stat (&st, STATFLAG_DEFAULT);
			bstrName = st.pwcsName;
			CoTaskMemFree (st.pwcsName);	// aufräumen
		}
	} 
	if (!bstrName)
		return E_OUTOFMEMORY;

	*pVal = bstrName.Detach();
	return S_OK;
}

// Pbd öffnen
HPROJECT CRecordsetSource::OpenStoragePbd (IStorage *pIStg, bool &rfReadOnly)
{
	if (NULL == pIStg) _com_issue_error(E_POINTER);

HPROJECT hPr = (HPROJECT)z_open_storage_pbd (pIStg, rfReadOnly ? TRUE : FALSE);

	if (NULL == hPr && !rfReadOnly) {
	ErrCode EC = ERRCODE_FROM_HRESULT(::GetLastError());
	
		if (EC == EC_OPENRO) {		// muß ReadOnly geöffnet werden
			rfReadOnly = true;
			hPr = (HPROJECT)z_open_storage_pbd (pIStg, TRUE);
		}
		if (NULL == hPr)		// erfolgloser Versuch
			_com_issue_error(HRESULT_FROM_ERRCODE(EC_NOOPEN));
	}

// evtl. alle Dateien auf ReadOnly setzen
	if (rfReadOnly) 
		z_access (hPr, Z_ALL|Z_RDONLY); 	// DB ReadOnly

	return hPr;
}

///////////////////////////////////////////////////////////////////////////////
// Spezielle Recordsets liefern
HRESULT CRecordsetSource::GetAliasTableRecordset (GRecordset **pSourceGRecordset)
{
	if (NULL == pSourceGRecordset)
		return E_POINTER;

// wenns nicht das erste mal ist, dann direkt liefern
	if (m_Alias.IsValid())
		return m_Alias -> QueryInterface (IID_GRecordset, (LPVOID *)pSourceGRecordset);

// neu erzeugen
GMCAliasTableInMemoryRecordset *pAliasTable = NULL;
	
	try {
	// create new InMemRecSet
		pAliasTable = new GMCAliasTableInMemoryRecordset();
		THROW_FAILED_HRESULT(pAliasTable->Initialize());
		
	// Populate Alias table rows
		THROW_FAILED_HRESULT(pAliasTable->AddRecord(GFWCoordSystemTableType, GFWCSTableName));
		THROW_FAILED_HRESULT(pAliasTable->AddRecord(GFWFeatureTableType, GFWFeaturesTableName));
		
	// Get the output Recordset.
		THROW_FAILED_HRESULT(pAliasTable->GetOutputRecordset(m_Alias.ppi()));

	WGRecordset RSet (m_Alias);

		*pSourceGRecordset = RSet.detach();

	} catch (_com_error &e) {
		DELETE_OBJ(pAliasTable);

		ASSERT(SUCCEEDED(_COM_ERROR(e)));
		return _COM_ERROR(e);
	} catch (...) {
		DELETE_OBJ(pAliasTable);

		ASSERT(SUCCEEDED(E_OUTOFMEMORY));
		return E_OUTOFMEMORY;
	}

	DELETE_OBJ(pAliasTable);
	return S_OK;
}

HRESULT CRecordsetSource::GetCSTableRecordset (GRecordset **pSourceGRecordset)
{
	if (NULL == pSourceGRecordset)
		return E_POINTER;
	
// wenns nicht das erste mal ist, dann direkt liefern
	if (m_CoordSys.IsValid())
		return m_CoordSys -> QueryInterface (IID_GRecordset, (LPVOID *)pSourceGRecordset);

// neu erzeugen
GMCCoordSystemInMemoryRecordset* pCsTable = NULL;

	try {
	// create new InMemRecSet
		pCsTable = new GMCCoordSystemInMemoryRecordset();
		THROW_FAILED_HRESULT(pCsTable->Initialize());

	// Koordinatensystem erzeugen und initialisieren
	WGMCoordSystem CS(CLSID_CoordSystem);
	CCSSHeader Hdr (m_hPr, CS);

		Hdr.InitCoordTransform();

		THROW_FAILED_HRESULT(CS -> put_BaseStorageType(Hdr.BaseStorageType()));
		if (Hdr.IsTransverseMercator() || Hdr.IsUserDefined()) {
			THROW_FAILED_HRESULT(CS -> SetHorizResByGroundDistVal (Hdr.GetMetricDistVal(), Hdr.GetMetricUnitStr()));
		} else {
			THROW_FAILED_HRESULT(CS -> SetHorizResByAngAlongGroundVal(Hdr.GetAngleDistVal(), Hdr.GetAngleUnitStr()));
		}

	// Ellipsoidparameter einstellen
		{
		WDispatch Disp;

			THROW_FAILED_HRESULT(CS -> get_RefSpaceMgr((RefSpaceMgr **)Disp.ppi()));

		WGMRefSpaceMgr RefMgr (Disp);

			THROW_FAILED_HRESULT(RefMgr -> get_GeogSpace((GeogSpace **)Disp.ppi()));

		// geodätische Grundlage
			if (!Hdr.IsUserDefined()) {
				ASSERT(csgdUndefined != Hdr.GetGeodDatum());

			WGMGeogSpace GSpace (Disp);

				THROW_FAILED_HRESULT(GSpace -> put_GeodeticDatumVal(Hdr.GetGeodDatum()));
			}

		// für Gauß-Krüger Systeme
			if (Hdr.IsTransverseMercator()) {
				THROW_FAILED_HRESULT(RefMgr -> get_ProjSpace((ProjSpace **)Disp.ppi()));

			WGMProjSpace PSpace (Disp);

				THROW_FAILED_HRESULT(PSpace -> put_ProjAlgorithmVal (Hdr.GetProjection()));
				THROW_FAILED_HRESULT(PSpace -> put_LonOfOrig (Hdr.GetMeridian()));
				THROW_FAILED_HRESULT(PSpace -> put_LatOfOrig (0.0));
				THROW_FAILED_HRESULT(PSpace -> put_FalseX (Hdr.GetFalseX()));
				THROW_FAILED_HRESULT(PSpace -> put_FalseY (0.0));
			}
		}

	// Koordinatensystem zum Recordset hinzufügen
		THROW_FAILED_HRESULT(pCsTable -> AddRecord(CS, &m_CsGuid));

	// OutputRecordset abholen
		THROW_FAILED_HRESULT(pCsTable -> GetOutputRecordset(m_CoordSys.ppi()));

	WGRecordset RSet (m_CoordSys);

		*pSourceGRecordset = RSet.detach();

	} catch (_com_error &e) {
		DELETE_OBJ(pCsTable);

		ASSERT(SUCCEEDED(_COM_ERROR(e)));
		return _COM_ERROR(e);
	} catch (...) {
		DELETE_OBJ(pCsTable);

		ASSERT(SUCCEEDED(E_OUTOFMEMORY));
		return E_OUTOFMEMORY;
	}
	DELETE_OBJ(pCsTable);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Erzeugen und Initialisieren des SourceInfo-Objektes für eine Objektklasse
HRESULT CRecordsetSource::GenerateOKSSourceInfo (
	BSTR bstrName, ITRiASSourceInfo **ppISrcInfo)
{
	if (NULL == ppISrcInfo) 
		return E_POINTER;

	USES_CONVERSION;
	try {
	CComObject<CTRiASSourceInfo> *pInfo = NULL;

		THROW_FAILED_HRESULT(CComObject<CTRiASSourceInfo>::CreateInstance(&pInfo));

	WTRiASSourceInfo SrcInfo (pInfo);	// required AddRef

		THROW_FAILED_HRESULT(SrcInfo -> put_TableName (bstrName));
		THROW_FAILED_HRESULT(SrcInfo -> put_Handle (m_hPr));
		THROW_FAILED_HRESULT(SrcInfo -> put_CoordSystemType (m_CsGuid));

	CTables::iterator it = m_Names.find(os_string(OLE2A(bstrName)));

		if (it == m_Names.end())
			return E_UNEXPECTED;

		THROW_FAILED_HRESULT(SrcInfo -> put_Ident ((*it).second.GetIdent()));
		THROW_FAILED_HRESULT(SrcInfo -> put_Types ((*it).second.GetTypes()));

		*ppISrcInfo = SrcInfo.detach();

	} catch (_com_error &e) {
		ASSERT(SUCCEEDED(_COM_ERROR(e)));
		return _COM_ERROR(e);
	} catch (...) {
		ASSERT(SUCCEEDED(E_OUTOFMEMORY));
		return E_OUTOFMEMORY;
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Erzeugen und Initialisieren des SourceInfo-Objektes für eine Ansicht
HRESULT CRecordsetSource::GenerateViewSourceInfo (
	BSTR bstrName, ITRiASSourceInfo **ppISrcInfo)
{
	if (NULL == ppISrcInfo) 
		return E_POINTER;

	USES_CONVERSION;
	try {
	CComObject<CTRiASSourceInfo> *pInfo = NULL;

		THROW_FAILED_HRESULT(CComObject<CTRiASSourceInfo>::CreateInstance(&pInfo));

	WTRiASSourceInfo SrcInfo (pInfo);	// required AddRef

		THROW_FAILED_HRESULT(SrcInfo -> put_TableName (bstrName));
		THROW_FAILED_HRESULT(SrcInfo -> put_Handle (m_hPr));

		*ppISrcInfo = SrcInfo.detach();

	} catch (_com_error &e) {
		ASSERT(SUCCEEDED(_COM_ERROR(e)));
		return _COM_ERROR(e);
	} catch (...) {
		ASSERT(SUCCEEDED(E_OUTOFMEMORY));
		return E_OUTOFMEMORY;
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// alle Objektklassen in einer eigenen Tabelle
HRESULT CRecordsetSource::GetMetaTableRecordSet (GRecordset **pSourceGRecordset)
{
	if (NULL == pSourceGRecordset)
		return E_POINTER;
	
// wenns nicht das erste mal ist, dann direkt liefern
	if (m_OKS.IsValid())
		return m_OKS -> QueryInterface (IID_GRecordset, (LPVOID *)pSourceGRecordset);

// neu erzeugen
COKSInMemRecordSet* pOKSTable = NULL;

	try {
	// create new InMemRecSet
		pOKSTable = new COKSInMemRecordSet(m_hPr, m_bstrName);
		THROW_FAILED_HRESULT(pOKSTable -> Initialize());

	// alle Objektklassen als Sätze hinzufügen
		for (CTables::iterator it = m_Names.begin(); it != m_Names.end(); ++it)
		{
			THROW_FAILED_HRESULT(pOKSTable -> AddRecord (
				(*it).second.GetIdent(), (*it).second.GetTypes(), 
				(*it).second.GetName(), (*it).second.GetDescription()));
		}

	// OutputRecordset abholen
		THROW_FAILED_HRESULT(pOKSTable -> GetOutputRecordset(m_OKS.ppi()));

	WGRecordset RSet (m_OKS);

		*pSourceGRecordset = RSet.detach();

	} catch (_com_error &e) {
		DELETE_OBJ(pOKSTable);

		ASSERT(SUCCEEDED(_COM_ERROR(e)));
		return _COM_ERROR(e);
	} catch (...) {
		DELETE_OBJ(pOKSTable);

		ASSERT(SUCCEEDED(E_OUTOFMEMORY));
		return E_OUTOFMEMORY;
	}

	DELETE_OBJ(pOKSTable);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// alle Geometriefelder/GeometrieTypen in einer eigenen Tabelle
HRESULT CRecordsetSource::GetFeatureTableRecordset (GRecordset **pSourceGRecordset)
{
	if (NULL == pSourceGRecordset)
		return E_POINTER;
	
// wenns nicht das erste mal ist, dann direkt liefern
	if (m_Features.IsValid())
		return m_Features -> QueryInterface (IID_GRecordset, (LPVOID *)pSourceGRecordset);

// neu erzeugen
CFeatureInMemRecordSet* pFeatureTable = NULL;

	try {
	// create new InMemRecSet
		pFeatureTable = new CFeatureInMemRecordSet(m_bstrName);
		THROW_FAILED_HRESULT(pFeatureTable -> Initialize());

	// alle GeometrieFelder/Typen als Sätze hinzufügen
		for (CTables::iterator it = m_Names.begin(); it != m_Names.end(); ++it)
		{
			THROW_FAILED_HRESULT(pFeatureTable -> AddRecord (
				CorrectName((*it).second.GetName()).c_str(), (*it).second.GetTypes(), 
				g_cbGeometry, (*it).second.GetDescription()));
		}

	// Alle anderen Tabellen (Ansichten, Objektklassen etc.)
		for (CViews::iterator viewit = m_Views.begin(); viewit != m_Views.end(); ++viewit)
		{
			THROW_FAILED_HRESULT(pFeatureTable -> AddRecord (
				CorrectName((*viewit).first.c_str()).c_str(), 0L));
		}

	// OutputRecordset abholen
		THROW_FAILED_HRESULT(pFeatureTable -> GetOutputRecordset(m_Features.ppi()));

	WGRecordset RSet (m_Features);

		*pSourceGRecordset = RSet.detach();

	} catch (_com_error &e) {
		DELETE_OBJ(pFeatureTable);

		ASSERT(SUCCEEDED(_COM_ERROR(e)));
		return _COM_ERROR(e);
	} catch (...) {
		DELETE_OBJ(pFeatureTable);

		ASSERT(SUCCEEDED(E_OUTOFMEMORY));
		return E_OUTOFMEMORY;
	}

	DELETE_OBJ(pFeatureTable);
	return S_OK;
}

