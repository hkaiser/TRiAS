// $Header: $
// Copyright© 2001 Hartmut Kaiser, All rights reserved
// Created: 10.04.2001 13:48:23 
//
// @doc
// @module TRiASNativeDataSource.cpp | Definition of the <c CTRiASNativeDataSource> class

#include "StdAfx.h"

#include <ospace/file/path.h>

#include <ErrCodes.hxx>
#include <ErrInst.hxx>
#include <dbd.hxx>
#include <dirisole.h>

#include <DBMsg.hmc>
#include <ActDB.h>
#include <NativeIdent.h>
#include <CSSGuidHeader.h>
#include <WinVersion.h>

#include "TRiASNativeDB.h"
#include "Strings.h"
#include "Wrapper.h"

#include "TRiASNativeDataSource.h"
#include "TRiASNativeIdents.h"

#if defined(_DEBUG)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // defined(_DEBUG)

using namespace trias_nativeident;

/////////////////////////////////////////////////////////////////////////////
// CTRiASNativeDataSource

/////////////////////////////////////////////////////////////////////////////
// Initialisation
HRESULT CTRiASNativeDataSource::FinalConstruct()
{
	return CComObjectRootEx<_ThreadModel>::FinalConstruct();
}

void CTRiASNativeDataSource::FinalRelease()
{
}

/////////////////////////////////////////////////////////////////////////////
// ISupportErrorInfo

// InterfaceSupportsErrorInfo implementation
STDMETHODIMP CTRiASNativeDataSource::InterfaceSupportsErrorInfo(REFIID riid)
{
	return riid==IID_ITRiASNativeDataSource ? S_OK : S_FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// Helperfunktionen 
HRESULT CTRiASNativeDataSource::OpenDatabase (LPCTSTR pcName, IStorage *pIStg, DWORD dwMode, HPROJECT *phPr)
{
	if (NULL == phPr)
		return E_POINTER;
	*phPr = NULL;

// try to open without error-reporting
ErrInstall IgnoreErrors (EC_IGNOREALL);
ErrInstall IgnoreWarnings (WC_IGNOREALL);

HPROJECT hPr = NULL;
BOOL fReadOnly = ((dwMode & STGM_WRITE) || (dwMode & STGM_READWRITE)) ? FALSE : TRUE;
HRESULT hr = S_OK;

	if (NULL == pIStg) {
		if (NULL == pcName) 
			return E_INVALIDARG;

	// ggf. schon geöffnet
//		hr = z_test_open(pcName, &hPr);

	// open immer rufen, um ggf. AddRef auszuführen
		hPr = (HPROJECT)z_open_ex ((LPTSTR)pcName, NULL, NULL, fReadOnly, dwMode, FALSE);
	} 
	else
		hPr = (HPROJECT)z_open_storage_ex (pIStg, fReadOnly, FALSE, NULL, FALSE);

	if (NULL == hPr) {
		hr = ::GetLastError();
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

			case EC_INVDBNAME:
				hr = TRIASDB_E_SINGLEDATABASE_NOT_FOUND;		// keine Datei oder existiert nicht
				break;
			}
		} 
		else {
		// alle anderen hier bearbeiten
		BOOL fRO = fReadOnly ? TRUE : FALSE;

			if (STG_E_SHAREVIOLATION == hr || STG_E_LOCKVIOLATION == hr) {
			// ZugriffsKonflikt
			BOOL fFileRO = FALSE;

				if (!fRO && (NULL == pcName || !TestFileRO (pcName, fFileRO))) 
					hr = TRIASDB_E_SINGLEDATABASE_NOT_FOUND;	// keine Datei oder existiert nicht
				else
					hr = (fRO || fFileRO) ? TRIASDB_S_MUSTOPENASCOPY : TRIASDB_S_MUSTOPENASCOPY_SHAREVIOLATION;
			} 
			else if (STG_E_ACCESSDENIED == hr) {
			// ZugriffsRechtsÜberschreitung (Datei ist lediglich ReadOnly)
				if (NULL == pcName || !TestFileRO (pcName, fRO)) 
					hr = TRIASDB_E_SINGLEDATABASE_NOT_FOUND;	// keine Datei oder existiert nicht
				else 
					hr = TRIASDB_S_MUSTOPENASCOPY;
			}
		}

	// den Fehler nach oben propagieren
		return hr;
	}

// evtl. alle Dateien auf ReadOnly setzen
	if (fReadOnly) 
		z_access (hPr, Z_ALL|Z_RDONLY); 	// DB ReadOnly
	*phPr = hPr;		// Resultat
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
// MetaDatenbank eröffnen
HRESULT CTRiASNativeDataSource::OpenStoragePbd (IStorage *pIStg, bool fReadOnly, HPROJECT *phPbdPr)
{
	if (NULL == pIStg || NULL == phPbdPr) 
		return E_POINTER;

HPROJECT hPr = (HPROJECT)z_open_storage_pbd (pIStg, fReadOnly ? TRUE : FALSE);

	if (NULL == hPr && !fReadOnly) {
	ErrCode EC = ERRCODE_FROM_HRESULT(::GetLastError());
	
		if (EC == EC_OPENRO) {		// muß ReadOnly geöffnet werden
			fReadOnly = true;
			hPr = (HPROJECT)z_open_storage_pbd (pIStg, TRUE);
		}
		if (NULL == hPr)		// erfolgloser Versuch
			return HRESULT_FROM_ERRCODE(EC_NOOPEN);
	}

// evtl. alle Dateien auf ReadOnly setzen
	if (fReadOnly) 
		z_access (hPr, Z_ALL|Z_RDONLY); 	// DB ReadOnly

	*phPbdPr = hPr;
	return S_OK;
}

HRESULT CTRiASNativeDataSource::OpenMetaDatabase (HPROJECT hPr, DWORD dwMode)
{
	if (NULL == hPr)
		return TRIASDB_E_DATABASE_NOT_OPENED;

	USES_CONVERSION;
	COM_TRY {
	HPROJECT hPrPbd = NULL;

	// Storage der Datenbank besorgen
	WStorage Stg;

		THROW_FAILED_HRESULT(GetProjectStorage(hPr, Stg.ppi()));

	// SubStg öffnen (muß existieren !)
	WStorage PbdStg;
	bool fReadOnly = !((dwMode & STGM_WRITE) || (dwMode & STGM_READWRITE));

		dwMode &= ~(STGM_SHARE_DENY_READ|STGM_SHARE_DENY_WRITE|STGM_SHARE_DENY_NONE);
		dwMode |= STGM_TRANSACTED|STGM_SHARE_EXCLUSIVE;

		THROW_FAILED_HRESULT(Stg -> OpenStorage(A2OLE(g_cbMetaData), NULL, dwMode, NULL, 0L, PbdStg.ppi()));
		THROW_FAILED_HRESULT(OpenStoragePbd (PbdStg, fReadOnly, &hPrPbd));

		if (NULL != hPrPbd) {		// Pbd dem TRiAS-Projekt zuordnen
			_ASSERTE(NULL != hPr);
			SetRelatedProject (hPr, hPrPbd);
		}

	} COM_CATCH;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// ITRiASNativeDataSource

STDMETHODIMP CTRiASNativeDataSource::get_Classes(INT_PTR hPr, ITRiASEnumNativeIdents **ppVal)
{
	if (NULL == hPr)
		return TRIASDB_E_DATABASE_NOT_OPENED;
	if (NULL == ppVal)
		return E_POINTER;
	*ppVal = NULL;

	COM_TRY {
	// Enumerator erzeugen
	CComObject<CTRiASNativeIdents> *pIdents = NULL;
	WTRiASEnumNativeIdents Enum;

		THROW_FAILED_HRESULT(CComObject<CTRiASNativeIdents>::CreateInstance(&pIdents));
		Enum = pIdents;		// bump RefCnt

	// Enumerator füllen
		THROW_FAILED_HRESULT(pIdents -> FInit(reinterpret_cast<HPROJECT>(hPr)));

	// Enumerator liefern
		*ppVal = Enum.detach();

	} COM_CATCH;
	return S_OK;
}

// Liefert deas Handle einer gegebenen Objektklasse
STDMETHODIMP CTRiASNativeDataSource::get_Class(
	INT_PTR hPrjHandle, BSTR bstrIdentName, VARIANT_BOOL fCaseSensitive, INT_PTR *plIdent)
{
	if (NULL == hPrjHandle)
		return TRIASDB_E_DATABASE_NOT_OPENED;

	USES_CONVERSION;
	return CNativeIdent::FindFromName(reinterpret_cast<HPROJECT>(hPrjHandle), OLE2A(bstrIdentName), fCaseSensitive, plIdent);
}

// Liefert die Version der Datenbank
STDMETHODIMP CTRiASNativeDataSource::get_Version(INT_PTR hPrjHandle, BSTR *pbstrVersion)
{
	if (NULL == hPrjHandle)
		return TRIASDB_E_DATABASE_NOT_OPENED;
	if (NULL == pbstrVersion)
		return E_POINTER;
	*pbstrVersion = NULL;

long lV = ::GetDBVersion(reinterpret_cast<HPROJECT>(hPrjHandle));
TCHAR cbBuffer[64];

	wsprintf (cbBuffer, "%02ld.%02ld.%04ld", HIBYTE(HIWORD(lV)), LOBYTE(HIWORD(lV)), LOBYTE(LOWORD(lV)));

CComBSTR bstr (cbBuffer);

	if (!bstr) 
		return E_OUTOFMEMORY;
	*pbstrVersion = bstr.Detach();		
	return S_OK;
}

// Liefert die Version des Dbms-Systems
STDMETHODIMP CTRiASNativeDataSource::get_DbmsVersion(BSTR *pbstrVersion)
{
	if (NULL == pbstrVersion)
		return E_POINTER;
	*pbstrVersion = NULL;

long lV = ::GetDbmsVersion();
TCHAR cbBuffer[64];

	wsprintf (cbBuffer, "%02ld.%02ld.%04ld", HIBYTE(HIWORD(lV)), LOBYTE(HIWORD(lV)), LOBYTE(LOWORD(lV)));

CComBSTR bstr (cbBuffer);

	if (!bstr) 
		return E_OUTOFMEMORY;
	*pbstrVersion = bstr.Detach();		
	return S_OK;
}

// Liefert den Dateinamen der Datenbank
STDMETHODIMP CTRiASNativeDataSource::get_Name(INT_PTR hPrHandle,  BSTR *pbstrName)
{
	if (NULL == hPrHandle)
		return TRIASDB_E_DATABASE_NOT_OPENED;
	if (NULL == pbstrName)
		return E_POINTER;
	*pbstrName = NULL;

char cbBuffer[_MAX_PATH];
HRESULT hr = ::GetDataBaseName(reinterpret_cast<HPROJECT>(hPrHandle), cbBuffer, sizeof(cbBuffer));

	if (FAILED(hr)) return hr;

CComBSTR bstrName (cbBuffer);

	*pbstrName = bstrName.Detach();
	return S_OK;
}

HRESULT CTRiASNativeDataSource::FullOpen (BSTR Name, DWORD dwMode, HPROJECT *pPrjHandle)
{
	_ASSERTE(NULL != pPrjHandle);
	USES_CONVERSION;

HRESULT hr = OpenDatabase (OLE2A(Name), NULL, dwMode, pPrjHandle);

	if (S_OK == hr) {		// ggf. zum ersten mal öffnen
		_ASSERTE(NULL != *pPrjHandle);
		hr = OpenMetaDatabase(*pPrjHandle, dwMode);
	}
	return hr;
}

STDMETHODIMP CTRiASNativeDataSource::Open(BSTR Name, DWORD dwMode, NATIVEOPENMODE rgOpenMode, INT_PTR *pPrjHandle)
{
	if (NULL == pPrjHandle)
		return E_POINTER;
	*pPrjHandle = NULL;

HPROJECT hPr = NULL;
HRESULT hr = FullOpen (Name, dwMode, &hPr);

	if (SUCCEEDED(hr) && (TRIASDB_S_MUSTOPENASCOPY == hr || TRIASDB_S_MUSTOPENASCOPY_SHAREVIOLATION == hr)) {
	// noch einmal RO versuchen
		if (dwMode & (STGM_WRITE|STGM_READWRITE)) 
			hr = FullOpen (Name, STGM_READ, &hPr);
	}

	if (SUCCEEDED(hr)) {
	// evtl. zusätzliche Optionen voreinstellen
		SetAttribNoCase(hPr, (NATIVEOPENMODE_NoCaseAttribs & rgOpenMode) ? TRUE : FALSE);
		SetIdentNoCase(hPr, (NATIVEOPENMODE_NoCaseIdents & rgOpenMode) ? TRUE : FALSE);

	// Resultat liefern
		*reinterpret_cast<HPROJECT *>(pPrjHandle) = hPr;
	}
	return hr;
}

STDMETHODIMP CTRiASNativeDataSource::Close(INT_PTR hPrjHandle)
{
// Pbd schließen
HPROJECT hPr = reinterpret_cast<HPROJECT>(hPrjHandle);
HPROJECT hPrPbd = NULL;

	if (!GetRelatedProject(hPr, &hPrPbd))
		return E_UNEXPECTED;

BOOL fOpened = FALSE;
HRESULT hr = S_OK;

	::IsOpened (hPrPbd, &fOpened);
	if (fOpened && NULL != hPrPbd) {
	CActDB ActDB (hPrPbd);
	ErrCode RC = (ErrCode)z_close (hPrPbd, false);	// PBD schließen, Fehler nicht fatal

		if (EC_OKAY != RC)
			hr = HRESULT_FROM_ERRCODE(RC);
		ActDB.Reset();
	} 
	if (FAILED(hr)) return hr;

// Datenbank schließen
	::IsOpened (hPr, &fOpened);
	if (fOpened && NULL != hPr) {
	CActDB ActDB (hPr);
	ErrCode RC = (ErrCode)z_close (hPr, false);	// DB schließen

		if (EC_OKAY != RC)
			hr = HRESULT_FROM_ERRCODE(RC);
		ActDB.Reset();
	} 
	return hr;
}

HRESULT CTRiASNativeDataSource::SaveMetaDatabase (HPROJECT hPr)
{
HPROJECT hPrPbd = NULL;

	if (!GetRelatedProject(hPr, &hPrPbd))
		return E_UNEXPECTED;

// alle internen Buffer leeren
	{
	CAccessDB ActDB (hPrPbd);
	ErrCode RC = EC_OKAY;

		DBASSERTHR(DBFlush (hPrPbd, FLUSH_ACTDB));								// alles wegschreiben
		DBASSERTHR(DBPageZeroFlush (hPrPbd, FLUSH_ACTDB|FLUSH_COMMITDATA));		// PageZero's auch wegschreiben
	} // ~CAccessDB

	::SetDirty (hPrPbd, FALSE);
	::SetDirty (hPr, TRUE);
	return S_OK;
}

STDMETHODIMP CTRiASNativeDataSource::Save(INT_PTR hPrjHandle)
{
// alle internen Daten dieser Datenbank wegschreiben
HPROJECT hPr = reinterpret_cast<HPROJECT>(hPrjHandle);

// Pbd Speichern
	RETURN_FAILED_HRESULT(SaveMetaDatabase(hPr));

// alle internen Buffer leeren
ErrCode RC = EC_OKAY;
CActDB ActDB (hPr);

	DBASSERTHR(DBFlush (hPr, FLUSH_ACTDB));									// alles wegschreiben
	DBASSERTHR(DBPageZeroFlush (hPr, FLUSH_ACTDB|FLUSH_COMMITDATA));		// PageZero's auch wegschreiben

	::SetDirty (hPr, FALSE);
	return S_OK;
}

// Implementation of get_OpenedRO
STDMETHODIMP CTRiASNativeDataSource::get_OpenedRO(INT_PTR hPrjHandle, VARIANT_BOOL *pfRO)
{
	if (NULL == pfRO)
		return E_POINTER;
	*pfRO = TRUE;		// im Fehlerfall immer RO

BOOL fRO = FALSE;

	if (GetROMode(reinterpret_cast<HPROJECT>(hPrjHandle), &fRO)) {
		*pfRO = fRO ? VARIANT_TRUE : VARIANT_FALSE;
		return S_OK;
	}
	return E_INVALIDARG;
}

// Implementation of get_CoordSystemWKT
STDMETHODIMP CTRiASNativeDataSource::get_CoordSystemWKT(
	INT_PTR hPrjHandle, UINT *puiEpsgId, BSTR *pbstrCoordSystemWKT)
{
	if (NULL == pbstrCoordSystemWKT)
		return E_POINTER;
	*pbstrCoordSystemWKT = NULL;

// WKT/Id aus diversen Headereinträgen holen
CCSGuidHeader Hdr(reinterpret_cast<HPROJECT>(hPrjHandle));

	if (!Hdr.GetOgcWkt(pbstrCoordSystemWKT)) 
		*pbstrCoordSystemWKT = CComBSTR(L"PROJCS[\"Unknown\"]").Detach();

	Hdr.GetEpsgId(puiEpsgId);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Erzeugen einer neuen Datenquelle

///////////////////////////////////////////////////////////////////////////////
// Vollen GeoDBNamen erzeugen 
// Der volle GeoDBName wird erzeugt, in dem die im gegebenen DateiNamen fehlenden
// Bestandteile des vollen DateiNamens durch die Teile aus den StandardPfad
// (aus der Registry) ergänzt werden. Wenn nur der Name des Projektes vorgegeben
// ist, so wird folgender Name erzeugt
//		StandardPfad\Projekt\Projekt.ris.
// Default-Datenpfad zusammenbauen
bool GetDefaultDataStore (CString &rstrLoc)
{
CRegKey regDirs;
char cbDefaultDir[_MAX_PATH];

	if (ERROR_SUCCESS == regDirs.Open(HKEY_CURRENT_USER, "Software", KEY_READ) && 
		ERROR_SUCCESS == regDirs.Open(regDirs, REG_COMPANY_KEY, KEY_READ) &&
		ERROR_SUCCESS == regDirs.Open(regDirs, REG_PRODUCT_KEY, KEY_READ))
	{
	CRegKey regKey;

		if (ERROR_SUCCESS == regKey.Open(regDirs, "Directories") ||
			ERROR_SUCCESS == regKey.Create(regDirs, "Directories"))
		{
			regDirs.Close();
			regDirs.Attach(regKey.Detach());

		DWORD dwLen = sizeof(cbDefaultDir);

			cbDefaultDir[0] = '\0';
			if (ERROR_SUCCESS != regDirs.QueryValue(cbDefaultDir, "DefaultDataSourceDir", &dwLen) ||
				'\0' == cbDefaultDir[0]) 
			{
			// ggf. fürs nächste mal schreiben
			DWORD dwFlags = CSIDL_PERSONAL;
			CWinVersion WinVer;

				if (WinVer.IsWinNT() && WinVer.IsWin50())
					dwFlags |= CSIDL_FLAG_CREATE;

				SHGetFolderPath(NULL, dwFlags, NULL, 0, cbDefaultDir);
				PathAppend(cbDefaultDir, REG_COMPANY_KEY);
				PathAppend(cbDefaultDir, REG_PRODUCT_KEY);
				PathAppend(cbDefaultDir, "DataSources");
				PathAddBackslash(cbDefaultDir);

				regDirs.SetValue(cbDefaultDir, "DefaultDataSourceDir");

			// Verzeichnis auch noch erzeugen
				CreateDirectory (cbDefaultDir, NULL);
			}

			rstrLoc = cbDefaultDir;
			return true;
		}
	}
	return false;
}

HRESULT GenerateFullPath (LPCTSTR pcDBName, bool fMakeSubDir, os_string &rStr)
{
	if (NULL == pcDBName) 
		return E_POINTER;	// temporäre Datei erzeugen

	COM_TRY {
	os_path Name = os_string(pcDBName);

	// wenn UNC vorliegt, dann nichts machen
		if (!Name.has_unc()) {
		// Default-Verzeichnis besorgen
		CString strDefault;

			GetDefaultDataStore(strDefault);

		os_path Default = os_string(strDefault);

		// fehlende Bestandteile des Namens ersetzen
			if (!Name.has_directory() && !Name.has_fulldrive())
				Name.directory (Default.directory());
			if (!Name.has_drive())
				Name.drive (*Default.drive().c_str());
			if (Name.base().size() > 0 && !Name.has_extension())
				Name.extension (os_string("ris"));

			if (fMakeSubDir) {
			// Unterverzeichnis dranhängen, welches genau wie die Datei heißt
			os_string dir (Name.directory());

				dir += Name.path_separator();
				dir += Name.base();
				Name.directory (dir);
			}
		}
		rStr = (LPCTSTR)Name;	// Resultat kopieren

	} COM_CATCH;
	return S_OK;
}

HRESULT CTRiASNativeDataSource::CreateMainDatabase (
	BSTR Name, UINT uiResID, bool fCompressed, os_string &rStr, IStorage **ppIStg)
{
DWORD dwResSize;
LPBYTE lpRes = ReadResource (uiResID, dwResSize);

	if (NULL == lpRes)
		return E_OUTOFMEMORY;

CDBDictCompoundFile *pDBDict = NULL;

	USES_CONVERSION;
	COM_TRY {
	// TRiAS.Document.2
		THROW_FAILED_HRESULT(GenerateFullPath (OLE2A(Name), false, rStr));
		pDBDict = CDBDictCompoundFile::CreateInstance (lpRes, fCompressed);
		if (pDBDict == NULL) 
			return E_OUTOFMEMORY;

	ErrCode EC = pDBDict -> CreateDBEx (rStr.c_str(), NULL, NULL, ppIStg);
	
		if (EC_OKAY != EC)
			_com_issue_error (HRESULT_FROM_ERRCODE(EC));

	} COM_CATCH_EX(e) {
		DELETE_OBJ(lpRes);
		DELETE_OBJ(pDBDict);
		return _COM_ERROR(e);
	} 
	DELETE_OBJ(lpRes);
	DELETE_OBJ(pDBDict);
	return S_OK;
}

HRESULT CTRiASNativeDataSource::CreateMetaDatabase (
	IStorage *pIStg, UINT uiResID, BOOL fCompressed, LPCTSTR pcName)
{
DWORD dwResSize;
LPBYTE lpRes = ReadResource (uiResID, dwResSize);

	if (NULL == lpRes)
		return E_OUTOFMEMORY;

CDBDict *pDBDict = NULL;

	USES_CONVERSION;
	COM_TRY {
	// SubStorage erzeugen
	WStorage SubStg;
	DWORD dwMode = STGM_READWRITE|STGM_SHARE_EXCLUSIVE|STGM_TRANSACTED;
	LPCOLESTR poleMetaName = A2OLE(g_cbMetaData);
	HRESULT hr = pIStg -> OpenStorage (poleMetaName, NULL, dwMode, NULL, 0, SubStg.ppi());

		if (FAILED(hr)) {	
			if (STG_E_FILENOTFOUND == hr) {
			// existiert noch nicht, anlegen
				dwMode |= STGM_CREATE;
				THROW_FAILED_HRESULT(pIStg -> CreateStorage (poleMetaName, dwMode, 0, 0, SubStg.ppi()));
			} else
				_com_issue_error(hr);			// sonstiger Fehler
		}

	// "TRiAS.MetaDocument.2"
		ATLTRY(pDBDict = CDBDictCompoundFile::CreateInstance (lpRes, fCompressed));
		if (pDBDict == NULL) 
			return E_OUTOFMEMORY;

	IStorage *pIStg = SubStg;	// nur temporär kopieren
	ErrCode EC = ((CDBDictCompoundFile *)pDBDict) -> CreateDBEx (NULL, NULL, NULL, 
			&pIStg, &CLSID_TRiASMetaDocument, "TRiAS.MetaDocument.2");
	
		if (EC_OKAY != EC)
			_com_issue_error (HRESULT_FROM_ERRCODE(EC));

	// alles Speichern			
	DWORD rgStgc = STGC_DEFAULT;
	CWinVersion WinVer;

		if (WinVer.IsWin50() && WinVer.IsWinNT()) 
			rgStgc |= STGC_CONSOLIDATE;
		THROW_FAILED_HRESULT(SubStg -> Commit (rgStgc));

	} COM_CATCH_EX(e) {
		DELETE_OBJ(lpRes);
		DELETE_OBJ(pDBDict);
		return _COM_ERROR(e);
	}

	DELETE_OBJ(lpRes);
	DELETE_OBJ(pDBDict);
	return S_OK;
}

STDMETHODIMP CTRiASNativeDataSource::Create(BSTR bstrName, NATIVECREATEMODE rgMode)
{
	COM_TRY {
	CComPtr<IStorage> Stg;
	os_string strName;
	bool fCompressed = (rgMode & NATIVECREATEMODE_Compressed) ? true : false;
	UINT uiResID = IDR_DBD019;
	UINT uiResIDPbd = IDR_PBD013;

		switch (rgMode & NATIVECREATEMODE_CompatibleMsk) {
		case NATIVECREATEMODE_CompatibleV2:
			uiResID = IDR_DBDOLD; 
			uiResIDPbd = IDR_PBD011;
			break;

		case NATIVECREATEMODE_CompatibleV4:
			uiResID = IDR_DBD017; 
			uiResIDPbd = IDR_PBD012;
			break;

		default:
		case NATIVECREATEMODE_NotCompatible:
			break;
		}
		THROW_FAILED_HRESULT(CreateMainDatabase (bstrName, uiResID, fCompressed, strName, &Stg));
		THROW_FAILED_HRESULT(CreateMetaDatabase (Stg, uiResIDPbd, fCompressed, strName.c_str()));

	// Speichern
	DWORD rgStgc = STGC_DEFAULT;
	CWinVersion WinVer;

		if (WinVer.IsWin50() && WinVer.IsWinNT()) 
			rgStgc |= STGC_CONSOLIDATE;
		THROW_FAILED_HRESULT(Stg -> Commit (rgStgc));		// alles wegschreiben

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Löschen einer existiere
// Implementation of Destroy
STDMETHODIMP CTRiASNativeDataSource::Destroy(BSTR Name)
{
	return E_NOTIMPL;
}

///////////////////////////////////////////////////////////////////////////////
// Objektklassen haben gültige Daten (Erzeugungs- und Modfikationsdatum)
STDMETHODIMP CTRiASNativeDataSource::get_IdentsHaveDates(INT_PTR hPrjHandle, VARIANT_BOOL *pfHasDates)
{
	if (NULL == hPrjHandle)
		return TRIASDB_E_DATABASE_NOT_OPENED;
	if (NULL == pfHasDates)
		return E_POINTER;
	*pfHasDates = VARIANT_FALSE;

long lVersion = ::GetDBVersion(reinterpret_cast<HPROJECT>(hPrjHandle));

	*pfHasDates = (lVersion >= VERSION05000013) ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Erzeugen einer neuen Objektklasse
STDMETHODIMP CTRiASNativeDataSource::AddClass(
	INT_PTR hPrjHandle, BSTR bstrIdentName, INT_PTR *plIdent)
{
	if (NULL == hPrjHandle)
		return TRIASDB_E_DATABASE_NOT_OPENED;
	if (NULL == plIdent)
		return E_POINTER;
	*plIdent = 0L;

CNativeIdent Ident (reinterpret_cast<HPROJECT>(hPrjHandle), 0, OTAll, TRUE);

	if (!Ident)
		return E_UNEXPECTED;

	USES_CONVERSION;
	RETURN_FAILED_HRESULT(Ident.SetName(OLE2A(bstrIdentName)));
	*plIdent = Ident.GetIdent();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Löschen einer existierenden Objektklasse
STDMETHODIMP CTRiASNativeDataSource::DestroyClass(INT_PTR hPrjHandle, BSTR bstrIdentName)
{
INT_PTR lIdent = 0;

	USES_CONVERSION;
	if (FAILED(CNativeIdent::FindFromName(reinterpret_cast<HPROJECT>(hPrjHandle), OLE2A(bstrIdentName), VARIANT_TRUE, &lIdent)))
		return E_UNEXPECTED;

CNativeIdent Ident (reinterpret_cast<HPROJECT>(hPrjHandle), lIdent, OTAll);

	if (!Ident)
		return E_UNEXPECTED;

	return Ident.Delete((S_OK == Ident.HasObjects()) ? true : false);
}

