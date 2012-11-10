// @doc
// @module HandleProject.cpp | Funktionen zur Verwaltung eine TRiAS-Projektes

#include "fakemfcp.hxx"
#include "fakemfc.h"

#include <ospace/file/path.h>

#include <xtensnn.h>
#include <ciid.h>
#include <registrx.hxx>
#include <Com/PropertyHelper.h>
#include <Com/MkHelper.h>

#include <toolguid.h>
#include <itoolbar.h>
#include <DBMsg.hmc>

#include "Strings.h"
#include "FakeMfc.hxx"

#include "OpenNewPropertySheet.h"
#include "CreateNewWiz.h"

#include "CoordSysKeys.h"

///////////////////////////////////////////////////////////////////////////////
// SmartInterfaces
DefineSmartInterface(TRiASMainDBEngine);
DefineSmartInterface(TRiASProject);
DefineSmartInterface(TRiASDatabase);
DefineSmartInterface(TRiASAccessDatabase);
DefineSmartInterface(TRiASConnections);
DefineSmartInterface(TRiASConnection);
DefineSmartInterface(TRiASDataServerRegEntry);
DefineSmartInterface(TRiASViews);
DefineSmartInterface(TRiASView);
DefineSmartInterface(EnumString);
DefineSmartInterface(EnumVARIANT);
DefineSmartInterface(TRiASProperties);
DefineSmartInterface(TRiASProperty);
DefineSmartInterface(TRiASPropertyBase);
DefineSmartInterface(BindCtx);
DefineSmartInterface(OleItemContainer);
DefineSmartInterface(Storage);

/////////////////////////////////////////////////////////////////////////////
// globale Funktionen
BOOL CompareFileNames (BSTR bstrPath1, BSTR bstrPath2);

/////////////////////////////////////////////////////////////////////////////
// SmartEnums
// {422FB8C4-39C3-11d1-96B9-00A024D6F582}
extern "C" const IID __declspec(selectany) IID_IEnumTRiASView = 
	{0x422fb8c4,0x39c3,0x11d1,{0x96,0xb9,0x00,0xa0,0x24,0xd6,0xf5,0x82}};

DefineEnumerator2(WTRiASView, IID_IEnumTRiASView);			// NEnumWTRiASView
DefineSmartEnumerator2(WTRiASView, IID_IEnumTRiASView);		// WEnumWTRiASView

///////////////////////////////////////////////////////////////////////////////
// EnumeratorObjekt für LPOLESTR's
typedef CComEnum<IEnumString, &IID_IEnumString, LPOLESTR, _Copy<LPOLESTR> > CEnumString;

HRESULT MakeEnumString (IUnknown *pUnk, const CFiles &rFiles, IEnumString **ppIEnum)
{
	_ASSERTE(rFiles.size() > 0);

// Zeiger umkopieren, damit ein zusammenhängender Vektor entsteht,
// dazu auf dem Stack den Speicher anfordern (gibt sich selbst frei!)
int iCnt = rFiles.size();
LPOLESTR *ppStrs = (LPOLESTR*)alloca(sizeof(LPOLESTR) * iCnt);
DWORD dwCnt = 0;

	USES_CONVERSION;
	for (CFiles::const_iterator it = rFiles.begin(); it != rFiles.end(); ++it)
		ppStrs[dwCnt++] = A2OLE((*it).c_str());		// nutzt ebenfalls alloca()

	_ASSERTE(int(dwCnt) <= iCnt);		// sind es plötzlich mehr geworden

// Enumeratorobjekt anlegen und füllen
CComObject<CEnumString> *pIEnum = NULL;

	ATLTRY(pIEnum = new CComObject<CEnumString>());		// AddRef ist noch 0
	if (NULL == pIEnum) return E_OUTOFMEMORY;

// die Funktion Init des EnumTemplates erwartet die Adressen des ersten und 
// letzten+1 Elementes eines Vektors
HRESULT hr = pIEnum -> Init ((LPOLESTR *)&ppStrs[0], (LPOLESTR *)&ppStrs[iCnt], pUnk, AtlFlagCopy);

	if (SUCCEEDED(hr))
		hr = pIEnum -> QueryInterface(IID_IEnumString, (LPVOID *)ppIEnum);

	if (FAILED(hr))		// bei Fehler alles freigeben
		delete pIEnum;

	return hr;
}

///////////////////////////////////////////////////////////////////////////////
// Feststellen, ob die zu öffnende Datasource bereits geöffnet ist
BOOL IsAlreadyOpened(ITRiASProject *pIPrj, const CFiles &rFiles, os_string &strOpened)
{
	COM_TRY {
	// alle connections durchgehen
	WTRiASConnections Conns;

		THROW_FAILED_HRESULT(pIPrj -> get_Connections (Conns.ppi()));

	WEnumVARIANT Enum;
	CComVariant v;

		THROW_FAILED_HRESULT(Conns -> _NewEnum (Enum.ppu()));
		for (Enum -> Reset(); S_OK == Enum -> Next (1, &v, NULL); /**/) {
			if (FAILED(v.ChangeType (VT_DISPATCH)))
				continue;

		WTRiASConnection Conn (V_DISPATCH(&v));
		CONNECTSTATUS rgStatus = CONNECTSTATUS_Closed;

			THROW_FAILED_HRESULT(Conn -> get_Status (&rgStatus));
			if (CONNECTSTATUS_Opened != rgStatus)
				continue;		// diese Connection ist nicht geöffnet

		WTRiASDatabase DB;
		CComBSTR bstrName;

			THROW_FAILED_HRESULT(Conn -> get_Database (DB.ppi()));
			THROW_FAILED_HRESULT(DB -> get_Name (CLEARED(&bstrName)));

		// alle zu öffnenden Dateien durchgehen
			for (CFiles::const_iterator it = rFiles.begin(); it != rFiles.end(); ++it) {
				if (CompareFileNames (bstrName, CComBSTR((*it).c_str()))) {
				// diese Datei ist bereits geöffnet
					strOpened = *it;
					return TRUE;
				}
			}
		}

	} COM_CATCH_RETURN(FALSE);
	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// Ein neues TRiAS-Projekt anlegen und mit einer neu anzugelegenden
// Datenquelle verbinden

HRESULT CFakeMFCExtension::CreateNewProjectNewDatasource (
	CConnectParams *pParams, CFiles &rFiles, LPCTSTR pcConnName, 
	LPCTSTR pcConnDesc, CCreateNewWiz &rAskForCoordSystem, ITRiASProject **ppIPrj)
{
	if (NULL == ppIPrj) return E_POINTER;

	COM_TRY {
	// Projekt erzeugen 
	WTRiASProject Prj;

		THROW_FAILED_HRESULT(CreateNewProject (g_cbNil, true, (OPENMODE)(OPENMODE_Normal|OPENMODE_DoNotAddToMRU), Prj.ppi()));

	// Koordinatensystem im Projekt wegschreiben
		rAskForCoordSystem.RegisterEntries(HACTPROJECT);

	// Datasource erzeugen und DataSource eröffnen
		THROW_FAILED_HRESULT(CreateNewDataSource (Prj, pParams -> m_ClsId, rFiles, pcConnName,
			pParams -> m_strProgID, pParams -> m_strConnect, pParams -> m_fNameIsSubStorage));

	// DataSource öffnen und ankoppeln
	WTRiASConnection Conn;
	CONNECTMODE rgMode = pParams -> m_fIsReadWrite ? 
				CONNECTMODE(CONNECTMODE_OpenReadWrite|CONNECTMODE_OpenUserResolves|
							CONNECTMODE_CloseUserResolves|CONNECTMODE_ResetConnectAskMode) : 
				CONNECTMODE(CONNECTMODE_OpenReadOnly|CONNECTMODE_ResetConnectAskMode);

	BOOL fPathIsConnectName = !pParams -> m_fNameIsSubStorage && !pParams -> m_fNameIsFile && !pParams -> m_fNameIsDir;

		THROW_FAILED_HRESULT(OpenDataSource (Prj, pParams -> m_ClsId, rFiles, pcConnName, 
			pcConnDesc, rgMode, pParams -> m_strProgID, pParams -> m_strConnect, 
			pParams -> m_fNameIsSubStorage, fPathIsConnectName, Conn.ppi()));

	// Koordinatensystem des Projektes erstmal in Datenquelle übernehmen
	BOOL fReReadHeader = FALSE;

		THROW_FAILED_HRESULT(CopyPropertiesToDatasource (Prj, Conn, pParams->m_strCoordsKey, &fReReadHeader));

	// Header neu einlesen
		if (fReReadHeader) {
			DEXN_ReReadHeader();	// an alle: Header neu lesen
			DEXN_ReScale();
			DEXN_ReReadContainer();
		}
		*ppIPrj = Prj.detach();

	} COM_CATCH;
	return S_OK;
}

HRESULT CFakeMFCExtension::CopyPropertiesToDatasource (
	ITRiASProject *pIPrj, ITRiASConnection *pIConn, LPCSTR pcTcfName, BOOL *pfIsDirty)
{
	COM_TRY {
	WTRiASDatabase DB;

		THROW_FAILED_HRESULT(pIConn -> get_Database(DB.ppi()));

		if (NULL != pcTcfName && '\0' != pcTcfName[0]) {
		// Koordinatensystem in Oberfläche gewählt, also direkt setzen
		HPROJECT hPr = NULL;

			THROW_FAILED_HRESULT(DB -> get_Handle((INT_PTR *)&hPr));
			CCreateNewWiz::RegisterEntries (hPr, pcTcfName);			
		}
		else {
		// jetzt noch Koordinatensystem aus Projekt in DB übernehmen
		WTRiASProperties PropsPrj;
		WTRiASProperties PropsDB;

			THROW_FAILED_HRESULT(WTRiASPropertyBase(pIPrj) -> get_Properties (PropsPrj.ppi()));
			THROW_FAILED_HRESULT(WTRiASPropertyBase(DB) -> get_Properties (PropsDB.ppi()));

			CopyCoordSysParams(PropsPrj, PropsDB, pfIsDirty);	// evtl. Fehler einfach ignorieren
		}

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Ein neues TRiAS-Projekt anlegen und mit einer existierenden
// Datenquelle verbinden

HRESULT CFakeMFCExtension::CreateNewProjectOpenDatasource (
	CConnectParams *pParams, CFiles &rFiles, LPCTSTR pcConnName, 
	LPCTSTR pcConnDesc, CCreateNewWiz &rAskForCoordSystem, ITRiASProject **ppIPrj)
{
	if (NULL == ppIPrj) return E_POINTER;

	COM_TRY {
	// neues Projekt erzeugen
	WTRiASProject Prj;

		THROW_FAILED_HRESULT(CreateNewProject (g_cbNil, true, 
			(OPENMODE)(OPENMODE_Normal|OPENMODE_DoNotAddToMRU), Prj.ppi()));

	// Koordinatensystem im Projekt wegschreiben
		rAskForCoordSystem.RegisterEntries(HACTPROJECT);

	// DataSource öffnen und ankoppeln
	CONNECTMODE rgMode = pParams -> m_fIsReadWrite ? 
				CONNECTMODE(CONNECTMODE_OpenReadWrite|CONNECTMODE_OpenUserResolves|
							CONNECTMODE_CloseUserResolves|CONNECTMODE_ResetConnectAskMode) : 
				CONNECTMODE(CONNECTMODE_OpenReadOnly|CONNECTMODE_ResetConnectAskMode);
	WTRiASConnection Conn;
	HRESULT hr = S_OK;
	BOOL fPathIsConnectName = !pParams -> m_fNameIsSubStorage && !pParams -> m_fNameIsFile && !pParams -> m_fNameIsDir;

		THROW_FAILED_HRESULT(hr = OpenDataSource (Prj, pParams -> m_ClsId, rFiles, 
			pcConnName, pcConnDesc, rgMode, pParams -> m_strProgID, pParams -> m_strConnect, 
			pParams -> m_fNameIsSubStorage, fPathIsConnectName, Conn.ppi()));
		_ASSERTE(S_OK == hr);		// Link should not be broken

	// auch hier die hinzugefügte Database konvertieren, wenns _eine_ TRiASDB ist
		if (1 == rFiles.size()) {
		CFiles::const_iterator it = rFiles.begin();

			THROW_FAILED_HRESULT(ConvertFromDataSource ((*it).c_str(), Conn, Prj, FALSE));
		}
		if (NULL != ppIPrj)
			*ppIPrj = Prj.detach();

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Ein neues TRiAS-Projekt anlegen und mit einer existierenden
// Datenquelle verbinden
inline os_string MakeProfileName (LPCSTR pcName)
{
os_path profile (pcName);

	profile.extension (g_cbINI+1);
	return os_string(profile);
}

bool CopyProfileFile (LPCSTR pcSrc, LPCSTR pcDest)
{
	if (NULL == pcDest)	return false;

// INI-Dateinamen ableiten
os_string strSrcIni (MakeProfileName (pcSrc));
os_string strDestIni (MakeProfileName (pcDest));

// INI-Datei kopieren
bool fResult = ::CopyFile (strSrcIni.c_str(), strDestIni.c_str(), false);

// evtl. Schreibschutz aufheben
DWORD dwAttr = ::GetFileAttributes (strDestIni.c_str());

	if ((UINT)(-1) == dwAttr)
		return false;		// Fehler aufgetreten

	if (dwAttr & FILE_ATTRIBUTE_READONLY) {
		dwAttr &= ~FILE_ATTRIBUTE_READONLY;
		::SetFileAttributes (strDestIni.c_str(), dwAttr);
	}
	return fResult;
}

namespace {
    // Feststellen, ob eine datei component based ist
    BOOL IsComponentBased(LPCSTR pcName)
    {
        USES_CONVERSION;
        WStorage Stg;
        HRESULT hr = StgOpenStorage(A2OLE(pcName), NULL,
            STGM_READ|STGM_SHARE_DENY_WRITE, 0, 0, Stg.ppi());
        return SUCCEEDED(hr);
    }
}

HRESULT CFakeMFCExtension::CreateNewProjectOpenAndConvertDatasource (
	LPCTSTR pcFileName, bool fRO, CConnectParams *pParams, ITRiASProject **ppIPrj)
{
	USES_CONVERSION;

HRESULT hr = S_OK;

	COM_TRY {
	// neues Projekt erzeugen
	WTRiASProject Prj;
	os_path fileordir = os_string(pcFileName);

#if defined(_USE_RISNAME_AS_RIWNAME)
	// Riw nach Ris benennen
	os_path project (fileordir);

		project.extension (g_cbRiw+1);
	
		hr = CreateNewProject (project, false, OPENMODE_Normal, Prj.ppi());
		if (FAILED(hr)) {
			if (E_ABORT == hr)
				return hr;
			THROW_FAILED_HRESULT(hr);
		}
#else
		hr = CreateNewProject (g_cbNil, true, (OPENMODE)(OPENMODE_Normal|OPENMODE_DoNotAddToMRU), Prj.ppi());
		if (FAILED(hr)) {
			if (E_ABORT == hr)
				return hr;
			THROW_FAILED_HRESULT(hr);
		}

	// INI-Datei kopieren
	CComBSTR bstrName;

		THROW_FAILED_HRESULT(Prj -> get_Name (CLEARED(&bstrName)));
		CopyProfileFile (pcFileName, OLE2A(bstrName));
#endif // defined(_USE_RISNAME_AS_RIWNAME)

    // feststellen, ob  eine ganz alte DB geöffnet werden soll
	TCHAR const *pcDBType = g_cbDefaultDataBase;

        if (!IsComponentBased(pcFileName)) {
        // alte Datenbanken kann man nur schreibgeschützt öffnen
            pcDBType = g_cbOldDataBase;
            fRO = TRUE;
        }

    // gewünschte Datenbank öffnen
	DWORD dwDummy;
	CConnectParams Params;

		if (NULL == pParams) {
			THROW_FAILED_HRESULT(ReadDataServerParams (dwDummy, &Params, pcDBType));
			pParams = &Params;
		}
		THROW_FAILED_HRESULT(hr = OpenDataSource (Prj, pcFileName, pParams, fRO, TRUE));
		if (NULL != ppIPrj)
			*ppIPrj = Prj.detach();

	} COM_CATCH_EX(e) {
	// Fehlermeldung ausgeben
		VMessageBox (MWind(), FakeTRiASName(IDS_PROJECTERROR_CAP, g_cbTRiAS).c_str(), 
			MB_OK|MB_ICONEXCLAMATION, IDS_COULDNOTOPENDATASOURCE, "", pcFileName, _COM_ERROR(e));
	}
	return hr;
}

// Datenquelle mit StandardParametern zum Projekt hinzufügen
HRESULT CFakeMFCExtension::OpenDataSource(
	ITRiASProject *pIPrj, LPCSTR pcFileName, CConnectParams *pParams, BOOL fRO, 
	BOOL fConvert, ITRiASConnection **ppIConn)
{
os_path fileordir = os_string(pcFileName);
os_string basepart (fileordir.base());
CString strConnDesc;

	strConnDesc.Format (IDS_CONNECTDESCRIPTION, basepart.c_str(), pParams -> m_strFileDesc);

CONNECTMODE rgMode = fRO ? 
			CONNECTMODE(CONNECTMODE_OpenReadOnly|CONNECTMODE_ResetConnectAskMode) :
			CONNECTMODE(CONNECTMODE_OpenReadWrite|CONNECTMODE_OpenUserResolves|
						CONNECTMODE_CloseUserResolves|CONNECTMODE_ResetConnectAskMode);
WTRiASConnection Conn;
CFiles Files;
BOOL fPathIsConnectName = !pParams -> m_fNameIsSubStorage && !pParams -> m_fNameIsDir && !pParams -> m_fNameIsFile;
HRESULT hr = S_OK;

	Files.insert(pcFileName);
	hr = OpenDataSource (pIPrj, pParams -> m_ClsId, Files, basepart.c_str(), 
		strConnDesc, rgMode, pParams -> m_strProgID, pParams -> m_strConnect, 
		pParams -> m_fNameIsSubStorage, fPathIsConnectName, Conn.ppi());

	if (S_OK == hr) {
	// diverse Sachen aus der Datenquelle übernehemen
		THROW_FAILED_HRESULT(ConvertFromDataSource (pcFileName, Conn, pIPrj, fConvert));
		if (NULL != ppIConn)
			*ppIConn = Conn.detach();

	// Datenquelle im MRUMenu eintragen
	ADDMRUITEM MRU;

		INITSTRUCT(MRU, ADDMRUITEM);
		MRU.fRO = fRO;
		MRU.pcName = pcFileName;
		DEX_NewMRUItem(MRU);

		MRU.fStartup = true;
		DEX_NewMRUItem(MRU);
	}
	return hr;
}

HRESULT CFakeMFCExtension::CopyViewsToProject (
	ITRiASConnection *pIConn, ITRiASProject *pIPrj, BOOL fCopyDefault, BOOL *pfIsDirty)
{
	COM_TRY {
	CComBSTR bstrConnName;
	WTRiASDatabase DB;

		THROW_FAILED_HRESULT(pIConn -> get_Database(DB.ppi()));
		THROW_FAILED_HRESULT(pIConn -> get_Name (CLEARED(&bstrConnName)));

		DEX_SetMessageString(FakeTRiASName(IDS_CONVERTINGVIEWS, bstrConnName).c_str());

	WTRiASAccessDatabase Helper(DB);
	CComBSTR bstrStartView;		// StartAnsicht behandeln
	bool fHasStartView = false;

		if (S_OK == Helper -> get_StartViewName (CLEARED(&bstrStartView)))
			fHasStartView = true;

	// Ansichten aus DB holen und an Projekt umhängen
	WTRiASViews Views, PrjViews;

		if (SUCCEEDED(Helper -> get_Views (Views.ppi()))) {
			THROW_FAILED_HRESULT(pIPrj -> get_Views (PrjViews.ppi()));

		WEnumVARIANT Enum;
		CComVariant v;

			THROW_FAILED_HRESULT(Views -> _NewEnum (Enum.ppu()));
			for (Enum -> Reset(); S_OK == Enum -> Next (1, &v, NULL); /**/)
			{
				THROW_FAILED_HRESULT(v.ChangeType (VT_UNKNOWN));
		
			WTRiASView View (V_UNKNOWN(&v));
			CComBSTR bstrName;

				THROW_FAILED_HRESULT(View -> get_Name (CLEARED(&bstrName)));
				if (!wcscmp (bstrName, bstrStartView))
					View -> put_IsStartView (VARIANT_TRUE);

				if (wcscmp (bstrName, g_cbDefaultVisInfo)) {
				// wenns nicht die DefaultAnsicht ist, den ConnectionNamen setzen
					View -> put_RelatedDataSourceName (bstrConnName);
//					bstrName += " (";
//					bstrName += bstrConnName;
//					bstrName += ")";
				} 
				else if (!fCopyDefault)
					continue;		// DefaultAnsicht hier nicht übernehmen

//				THROW_FAILED_HRESULT(View -> put_Name (bstrName));

			WTRiASView ViewT;

				if (FAILED(PrjViews -> Item(CComVariant(bstrName), ViewT.ppi()))) {
				// nur nicht bereits existierende Ansichten zum Projekt hinzufügen
					THROW_FAILED_HRESULT(View -> put_Parent (pIPrj));			// Ansicht gehört jetzt Projekt
					THROW_FAILED_HRESULT(PrjViews -> _Add(View, VARIANT_TRUE));
				}
			}
			PrjViews -> put_StartViewName (bstrStartView);
			if (NULL != pfIsDirty)
				*pfIsDirty = TRUE;
		}

	} COM_CATCH_OP (DEX_SetMessageString(NULL));

	DEX_SetMessageString(NULL);		// Statuszeile rücksetzen
	return S_OK;
}

HRESULT CFakeMFCExtension::CopyPropertiesToProject (ITRiASConnection *pIConn, ITRiASProject *pIPrj, BOOL *pfIsDirty)
{
	COM_TRY {
	WTRiASDatabase DB;

		THROW_FAILED_HRESULT(pIConn -> get_Database(DB.ppi()));

	// jetzt noch Koordinatensystem aus DB übernehmen
	WTRiASProperties PropsPrj;
	WTRiASProperties PropsDB;

		THROW_FAILED_HRESULT(WTRiASPropertyBase(pIPrj) -> get_Properties (PropsPrj.ppi()));
		THROW_FAILED_HRESULT(WTRiASPropertyBase(DB) -> get_Properties (PropsDB.ppi()));

		CopyCoordSysParams(PropsDB, PropsPrj, pfIsDirty);	// evtl. Fehler einfach ignorieren
		CopyAuxHeaderEntries(PropsDB, PropsPrj, pfIsDirty);	
		
	} COM_CATCH;
	return S_OK;
}

HRESULT CFakeMFCExtension::CopyCoordSysParams (
	ITRiASProperties *pIPropsSrc, ITRiASProperties *pIPropsDest, BOOL *pfIsDirty)
{
	return CopyHeaderEntries (g_cbCoordSysKeys, _countof(g_cbCoordSysKeys), pIPropsSrc, pIPropsDest, pfIsDirty);
}

HRESULT CFakeMFCExtension::CopyAuxHeaderEntries (
	ITRiASProperties *pIPropsSrc, ITRiASProperties *pIPropsDest, BOOL *pfIsDirty)
{
	return CopyHeaderEntries (g_cbAuxHeaderEntries, _countof(g_cbAuxHeaderEntries), pIPropsSrc, pIPropsDest, pfIsDirty);
}

HRESULT CFakeMFCExtension::CopyHeaderEntries (
	const COORDSYSKEY *pEntries, int iCntKeys,
	ITRiASProperties *pIPropsSrc, ITRiASProperties *pIPropsDest, BOOL *pfIsDirty)
{
	_ASSERTE(NULL != pIPropsSrc && NULL != pIPropsDest);
	COM_TRY {
		for (int i = 0; i < iCntKeys; i++) {
		WTRiASProperty PropSrc, PropDest;
		CComVariant vKey(pEntries[i].m_pKey);

			if (FAILED(pIPropsSrc -> Item (vKey, PropSrc.ppi())))
				continue;		// Property existiert nicht

		// Wert lesen und Locale-spezifisch konvertieren
		CComVariantEx vVal (LOCALE_ENGLISH);

			if (FAILED(PropSrc -> get_Value (&vVal)))
				continue;		// Wert nicht lesbar

			if (!V_ISUNKNOWN(&vVal) && !V_ISDISPATCH(&vVal)) {
			HRESULT hr = vVal.ChangeTypeEx(VT_BSTR);	// Darstellung LCID-spezifisch gewährleisten

				_ASSERTE(SUCCEEDED(hr));
			}

		// neue Property ggf. erzeugen
			if (FAILED(pIPropsDest -> Item (vKey, PropDest.ppi()))) {
				if (FAILED(pIPropsDest -> Add (vKey, PropDest.ppi())))
				{
					_ASSERTE(FALSE);
					continue;		// Property existiert nicht und läßt sich nicht erzeugen
				}
			} else 
				continue;			// exitierenden Eintrag nicht überschreiben

		// Wert der neuen Property setzen
			if (SUCCEEDED(PropDest -> put_Value (vVal))) {
				if (NULL != pfIsDirty)
					*pfIsDirty = TRUE;
			}
		}
	} COM_CATCH;
	return S_OK;
}

HRESULT CFakeMFCExtension::ConvertFromDataSource (
	LPCSTR pcName, ITRiASConnection *pIConn, ITRiASProject *pIPrj, BOOL fConvertProps)
{
BOOL fIsDirty = FALSE;

	_ASSERTE(NULL != pIConn && NULL != pIPrj);
	try {
	BOOL fReReadHeader = FALSE;

		THROW_FAILED_HRESULT(CopyViewsToProject (pIConn, pIPrj, TRUE, &fIsDirty));
		if (fConvertProps)
			THROW_FAILED_HRESULT(CopyPropertiesToProject (pIConn, pIPrj, &fReReadHeader));

	// Header neu einlesen
		if (fReReadHeader) {
			DEXN_ReReadHeader();	// an alle: Header neu lesen
			DEXN_ReScale();
			DEXN_ReReadContainer();
			fIsDirty = TRUE;
		}

	} catch (_com_error &e) {
		VMessageBox (MWind(), FakeTRiASName(IDS_PROJECTERROR_CAP, g_cbTRiAS).c_str(), 
			MB_OK|MB_ICONEXCLAMATION, IDS_COULDNOTCONVERTTOPROJECT, _COM_ERROR(e), g_cbTRiAS, pcName);
		return _COM_ERROR(e);
	}
	if (fIsDirty)		// muß gespeichert werden
		pIPrj -> put_Dirty (VARIANT_TRUE);

	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// ein neues Projekt erzeugen
inline bool FileExists (LPCSTR pcName)
{
	return ((UINT)(-1) == ::GetFileAttributes (pcName)) ? false : true;
}

inline bool AskToOverWrite (CWnd *pWnd, LPCSTR pcName)
{
int iRet = VMessageBox (pWnd, FakeTRiASName(IDS_PROJECTERROR_CAP, g_cbTRiAS).c_str(), 
		MB_YESNO|MB_ICONQUESTION|MB_DEFBUTTON2, IDS_ASKTOOVERWRITE, pcName);

	return (IDYES == iRet) ? true : false;
}

HRESULT CFakeMFCExtension::CreateNewProject (
	LPCSTR pcName, bool fForce, OPENMODE rgMode, ITRiASProject **ppIPrj)
{
	USES_CONVERSION;
	try {
	WTRiASMainDBEngine Engine;

		THROW_FAILED_HRESULT(GetMainDBEngine (Engine.ppi()));

	// evtl. vor dem Überschreiben warnen
		if (!fForce && FileExists (pcName) && !AskToOverWrite (MWind(), pcName))
			return E_ABORT;		// abgebrochen

	// neues Projekt erzeugen
	WTRiASProject Prj;
	CComBSTR bstrName (pcName);

		THROW_FAILED_HRESULT(Engine -> CreateProject (bstrName, rgMode, Prj.ppi()));

	// wenn temporäres Projekt, dann evtl. existierende INI löschen
		if (0 == bstrName.Length()) {
			THROW_FAILED_HRESULT(Prj -> get_Name (&bstrName));

		os_path inipath (OLE2A(bstrName));

			inipath.extension ("ini");
			DeleteFile (os_string(inipath).c_str());
		}
		if (NULL != ppIPrj)
			*ppIPrj = Prj.detach();

	} catch (_com_error &e) {
	// Fehlermeldung ausgeben
	CString strName (pcName);

		if (0 == strName.GetLength())
			VERIFY(strName.LoadString (IDS_NONAME));

		VMessageBox (MWind(), FakeTRiASName(IDS_PROJECTERROR_CAP, g_cbTRiAS).c_str(), 
			MB_OK|MB_ICONEXCLAMATION, IDS_COULDNOTCREATEPROJECT, strName, _COM_ERROR(e));
		return _COM_ERROR(e);
	}
	return S_OK;
}

HRESULT CFakeMFCExtension::CreateNewProject (
	IStorage *pIStg, LPCSTR pcName, OPENMODE rgMode, ITRiASProject **ppIPrj)
{
	USES_CONVERSION;
	try {
	WTRiASMainDBEngine Engine;

		THROW_FAILED_HRESULT(GetMainDBEngine (Engine.ppi()));

	// neues Projekt im gegebebene Storage erzeugen
	WTRiASProject Prj;
	CComBSTR bstrName (g_cbNil);

		if (NULL != pcName)
			bstrName = pcName;

		THROW_FAILED_HRESULT(Engine -> CreateProjectStg (pIStg, bstrName, rgMode, Prj.ppi()));
		if (NULL != ppIPrj)
			*ppIPrj = Prj.detach();

	} catch (_com_error &e) {
	// Fehlermeldung ausgeben
	CString strName;

		VERIFY(strName.LoadString (IDS_NONAME));
		VMessageBox (MWind(), FakeTRiASName(IDS_PROJECTERROR_CAP, g_cbTRiAS).c_str(), 
			MB_OK|MB_ICONEXCLAMATION, IDS_COULDNOTCREATEPROJECT, strName, _COM_ERROR(e));
		return _COM_ERROR(e);
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// ein existierendes Projekt öffnen
namespace {
// MessageBox anzeigen, in der gefragt wird, ob Projekt als Kopie geöffnet werden soll
	bool AskToOpenCopy (CWnd *pWnd, LPCSTR pcName)
	{
	int iRes = VMessageBox (pWnd, FakeTRiASName(IDS_PROJECTERROR_CAP, g_cbTRiAS).c_str(), 
					MB_TASKMODAL|MB_YESNO|MB_ICONQUESTION, IDS_OPENCOPYTEXT, pcName);
				   
		if (iRes == IDYES) 
			return true;	// RO eröffnen
		return false;	// nicht öffnen
	}
}

HRESULT CFakeMFCExtension::OpenExistingProject (LPCSTR pcName, BOOL fReadOnly, ITRiASProject **ppIPrj)
{
HRESULT hr = S_OK;

	try {
	// ggf. geöffnetes Projekt schließen
	WTRiASProject Prj;

		if (DEX_GetActiveProjectPtr(*Prj.ppi())) {
			Prj.Assign(NULL);					// wieder freigeben !
			DEX_CloseProject (HACTPROJECT);		// und schließen
		}
	
	// MainDBEngine geben lassen
	WTRiASMainDBEngine Engine;

		THROW_FAILED_HRESULT(GetMainDBEngine (Engine.ppi()));

	// Projekt öffnen
	CComBSTR Name (pcName);	// temporäres Projekt

		hr = Engine -> OpenProject (Name, fReadOnly ? OPENMODE_ReadOnly : OPENMODE_Normal, Prj.ppi());
 		if (TRIASDB_S_MUSTOPENASCOPY == hr && AskToOpenCopy (MWind(), pcName))
			hr = Engine -> OpenProject (Name, OPENMODE_ReadOnly, Prj.ppi());
		THROW_FAILED_HRESULT(hr);

	// wenn gewünscht, dann zurückliefern
		if (NULL != ppIPrj)
			*ppIPrj = Prj.detach();

	} catch (_com_error &e) {
	// Fehlermeldung ausgeben
	CString strName (pcName);

		if (strName.IsEmpty())
			VERIFY(strName.LoadString (IDS_NONAME));

		VMessageBox (MWind(), FakeTRiASName(IDS_PROJECTERROR_CAP, g_cbTRiAS).c_str(), 
			MB_OK|MB_ICONEXCLAMATION, IDS_COULDNOTOPENPROJECT, strName, _COM_ERROR(e));
		return _COM_ERROR(e);
	}
	return hr;
}

HRESULT CFakeMFCExtension::OpenExistingProject (
	IStorage *pIStg, BOOL fReadOnly, LPCSTR pcName, ITRiASProject **ppIPrj)
{
	try {
	WTRiASMainDBEngine Engine;

		THROW_FAILED_HRESULT(GetMainDBEngine (Engine.ppi()));

	// Projekt im gegebenen Storage öffnen
	WTRiASProject Prj;
	CComBSTR bstrName (g_cbNil);

		if (NULL != pcName)
			bstrName = pcName;

		THROW_FAILED_HRESULT(Engine -> OpenProjectStg (pIStg, bstrName, fReadOnly ? OPENMODE_ReadOnly : OPENMODE_Normal, Prj.ppi()));

	// wenn gewünscht, dann zurückliefern
		if (NULL != ppIPrj)
			*ppIPrj = Prj.detach();

	} catch (_com_error &e) {
	// Fehlermeldung ausgeben
	CString strName;

		VERIFY(strName.LoadString (IDS_NONAME));
		VMessageBox (MWind(), FakeTRiASName(IDS_PROJECTERROR_CAP, g_cbTRiAS).c_str(), 
			MB_OK|MB_ICONEXCLAMATION, IDS_COULDNOTOPENPROJECT, strName, _COM_ERROR(e));
		return _COM_ERROR(e);
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// neue Datasource erzeugen und ins Projekt einfügen
HRESULT CFakeMFCExtension::AddNewDatasource (
	CConnectParams *pParams, CFiles &rFiles, LPCTSTR pcConnName, LPCTSTR pcConnDesc,
	BOOL fShowError)
{
WTRiASProject Prj;

	try {
	// aktives Projekt besorgen
	WTRiASMainDBEngine Engine;

		THROW_FAILED_HRESULT(GetMainDBEngine (Engine.ppi()));
		THROW_FAILED_HRESULT(Engine -> get_ActiveProject (Prj.ppi()));

	// sicherstellen, daß diese Datenbank noch nicht von uns geöffnet wurde
	os_string strOpened;

		if (IsAlreadyOpened(Prj, rFiles, strOpened)) {
			VMessageBox (MWind(), FakeTRiASName(IDS_PROJECTERROR_CAP, g_cbTRiAS).c_str(), 
				MB_OK|MB_ICONEXCLAMATION, IDS_DATASOURCEALREADYOPENED, strOpened.c_str());
			return S_FALSE;
		}

	// Datasource erzeugen und DataSource eröffnen
		THROW_FAILED_HRESULT(CreateNewDataSource (Prj, pParams -> m_ClsId, rFiles, pcConnName,
			pParams -> m_strProgID, pParams -> m_strConnect, pParams -> m_fNameIsSubStorage));

	} catch (_com_error &e) {
		if (fShowError) {
		// Fehlermeldung ausgeben
			VMessageBox (MWind(), FakeTRiASName(IDS_PROJECTERROR_CAP, g_cbTRiAS).c_str(), 
				MB_OK|MB_ICONEXCLAMATION, IDS_COULDNOTCREATEDATASOURCE, pcConnName, _COM_ERROR(e));
		}
		return _COM_ERROR(e);
	}

	try {
	// DataSource öffnen und ankoppeln
	CONNECTMODE rgMode = pParams -> m_fIsReadWrite ? 
				CONNECTMODE(CONNECTMODE_OpenReadWrite|CONNECTMODE_OpenUserResolves|
							CONNECTMODE_CloseUserResolves|CONNECTMODE_ResetConnectAskMode) : 
				CONNECTMODE(CONNECTMODE_OpenReadOnly|CONNECTMODE_ResetConnectAskMode);
	HRESULT hr = S_OK;
	BOOL fPathIsConnectName = !pParams -> m_fNameIsSubStorage && !pParams -> m_fNameIsFile && !pParams -> m_fNameIsDir;
	WTRiASConnection Conn;

		THROW_FAILED_HRESULT(hr = OpenDataSource (Prj, pParams -> m_ClsId, rFiles, 
			pcConnName, pcConnDesc, rgMode, pParams -> m_strProgID, pParams -> m_strConnect, 
			pParams -> m_fNameIsSubStorage, fPathIsConnectName, Conn.ppi()));
		_ASSERTE(S_OK == hr);		// link should not be broken


	// Koordinatensystem des Projektes erstmal in Datenquelle übernehmen
	BOOL fReReadHeader = FALSE;

		THROW_FAILED_HRESULT(CopyPropertiesToDatasource (Prj, Conn, pParams->m_strCoordsKey, &fReReadHeader));

	// Header neu einlesen
		if (fReReadHeader) {
			DEXN_ReReadHeader();	// an alle: Header neu lesen
			DEXN_ReScale();
			DEXN_ReReadContainer();
		}

	} catch (_com_error &e) {
		if (fShowError) {
		// Fehlermeldung ausgeben
			VMessageBox (MWind(), FakeTRiASName(IDS_PROJECTERROR_CAP, g_cbTRiAS).c_str(), 
				MB_OK|MB_ICONEXCLAMATION, IDS_COULDNOTOPENDATASOURCE, pcConnName, "", _COM_ERROR(e));
		}
		return _COM_ERROR(e);
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// existierende Datasource ins Projekt einfügen
HRESULT CFakeMFCExtension::AddOpenDatasource (
	CConnectParams *pParams, CFiles &rFiles, LPCTSTR pcConnName, LPCTSTR pcConnDesc,
	BOOL fShowError)
{
	try {
	// aktives Projekt besorgen
	WTRiASMainDBEngine Engine;
	WTRiASProject Prj;

		THROW_FAILED_HRESULT(GetMainDBEngine (Engine.ppi()));
		THROW_FAILED_HRESULT(Engine -> get_ActiveProject (Prj.ppi()));

	// sicherstellen, daß diese Datenbank noch nicht von uns geöffnet wurde
	os_string strOpened;

		if (IsAlreadyOpened(Prj, rFiles, strOpened)) {
			VMessageBox (MWind(), FakeTRiASName(IDS_PROJECTERROR_CAP, g_cbTRiAS).c_str(), 
				MB_OK|MB_ICONEXCLAMATION, IDS_DATASOURCEALREADYOPENED, strOpened.c_str());
			return S_FALSE;
		}

	// DataSource öffnen und ankoppeln
	CONNECTMODE rgMode = pParams -> m_fIsReadWrite ? 
				CONNECTMODE(CONNECTMODE_OpenReadWrite|CONNECTMODE_OpenUserResolves|
							CONNECTMODE_CloseUserResolves|CONNECTMODE_ResetConnectAskMode) : 
				CONNECTMODE(CONNECTMODE_OpenReadOnly|CONNECTMODE_ResetConnectAskMode);
	HRESULT hr = S_OK;
	WTRiASConnection Conn;
	BOOL fPathIsConnectName = !pParams -> m_fNameIsSubStorage && !pParams -> m_fNameIsFile && !pParams -> m_fNameIsDir;

		THROW_FAILED_HRESULT(hr = OpenDataSource (Prj, pParams -> m_ClsId, rFiles, pcConnName, 
			pcConnDesc, rgMode, pParams -> m_strProgID, pParams -> m_strConnect, 
			pParams -> m_fNameIsSubStorage, fPathIsConnectName, Conn.ppi()));
		_ASSERTE(S_OK == hr);		// link should not be broken

		THROW_FAILED_HRESULT(CopyViewsToProject (Conn, Prj));

	} catch (_com_error &e) {
		if (fShowError) {
		// Fehlermeldung ausgeben
			VMessageBox (MWind(), FakeTRiASName(IDS_PROJECTERROR_CAP, g_cbTRiAS).c_str(), 
				MB_OK|MB_ICONEXCLAMATION, IDS_COULDNOTOPENDATASOURCE, pcConnDesc, pcConnName, _COM_ERROR(e));
		}
		return _COM_ERROR(e);
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// neue Datasource erzeugen
namespace {
	HRESULT GetProjectStorage (
		ITRiASProject *pIPrj, LPCSTR pcTempl, BOOL fCreate, IStorage **ppIStg, BSTR *pbstrCorrName)
	{
		COM_TRY {
		// Namen erzeugen
		char cbBuffer[_MAX_PATH];
		LONG lActSubStg = GetPropertyFrom (pIPrj, g_cbActSubObject, 0L) +1;

			wsprintf (cbBuffer, pcTempl, lActSubStg);
			SetPropertyBy (pIPrj, g_cbActSubObject, lActSubStg, true);

		// Storage besorgen
		DWORD dwMode = 0;
		VARIANT_BOOL fUpdatable = VARIANT_FALSE;

			THROW_FAILED_HRESULT(pIPrj -> get_Updatable (&fUpdatable));
			if (fUpdatable)
				dwMode = STGM_READWRITE|STGM_SHARE_EXCLUSIVE|STGM_TRANSACTED;
			else
				dwMode = STGM_READ|STGM_SHARE_EXCLUSIVE|STGM_TRANSACTED;

			if (fCreate)
				dwMode |= STGM_CREATE;

		WBindCtx Ctx;
		CComBSTR bstrName(cbBuffer);

			THROW_FAILED_HRESULT(MkCreateAndInitBindCtx (Ctx.ppi(), dwMode));
			THROW_FAILED_HRESULT(WOleItemContainer(pIPrj) -> GetObjectStorage (bstrName, Ctx, IID_IStorage, (LPVOID *)ppIStg));
			*pbstrCorrName = bstrName.Detach();

		} COM_CATCH;
		return S_OK;
	}
};	// namespace

HRESULT CFakeMFCExtension::CreateNewDataSource (
	ITRiASProject *pIPrj, REFCLSID rClsId, CFiles &rFiles, 
	LPCTSTR pcConnName,	LPCTSTR pcProgID, LPCTSTR pcConnect, BOOL fNameIsSubStorage)
{
	try {
	// neue Datenbank erzeugen
		{
		WTRiASDatabase DB (rClsId);
		CComBSTR bstrLocale (g_cbLangGeneral);

			if (!bstrLocale) 
				_com_issue_error(E_OUTOFMEMORY);

		// ConnectString im Format ';PROGID=progid' zusammenbauen und übergeben
		CComBSTR bstrConnect (g_cbTRiASDB);

			bstrConnect.Append (g_cbConnSource);
			bstrConnect.Append (pcProgID);
			if (NULL != pcConnect && strlen (pcConnect) > 0) 
				bstrConnect.Append (pcConnect);

			if (!fNameIsSubStorage) {
				if (rFiles.size() == 1) {
				CComBSTR bstrName ((*rFiles.begin()).c_str());

					THROW_FAILED_HRESULT(DB -> CreateDatabase (bstrName, bstrLocale, bstrConnect));
				} else {
				WEnumString Enum;

					THROW_FAILED_HRESULT(MakeEnumString (DB, rFiles, Enum.ppi()));
					THROW_FAILED_HRESULT(DB -> CreateDatabaseFromFiles (Enum, bstrLocale, bstrConnect));
				}
			} else {
			// Datenquelle im Projekt erzeugen
				USES_CONVERSION;
				_ASSERTE(1 == rFiles.size());

			CComBSTR bstrName;
			LPCSTR pcName = (*rFiles.begin()).c_str();
			WStorage Stg;

				THROW_FAILED_HRESULT(GetProjectStorage (pIPrj, pcName, TRUE, Stg.ppi(), &bstrName));
				THROW_FAILED_HRESULT(DB -> CreateDatabaseOnStg (Stg, bstrName, bstrLocale, bstrConnect));
				THROW_FAILED_HRESULT(pIPrj -> put_Dirty (VARIANT_TRUE));		// späteres Commit erzwingen

			// anstelle des Templates konkreten Namen einfügen
				rFiles.clear();
				rFiles.insert (os_string(OLE2A(bstrName)));
			}
		}	// DB goes out of scope

	} catch (_com_error &e) {
	// Fehlermeldung
		VMessageBox (MWind(), FakeTRiASName(IDS_DATASOURCEERROR_CAP, g_cbTRiAS).c_str(), 
			MB_OK|MB_ICONEXCLAMATION, IDS_COULDNOTCREATEDATASOURCE, pcConnName, _COM_ERROR(e));
		return _COM_ERROR(e);
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// existierende Datasource öffnen
HRESULT CFakeMFCExtension::OpenDataSource (
	ITRiASProject *pIPrj, REFCLSID rClsId, CFiles &rFiles, 
	LPCTSTR pcConnName, LPCTSTR pcConnDesc, CONNECTMODE rgMode,
	LPCTSTR pcProgID, LPCTSTR pcConnect, BOOL fNameIsSubStorage, BOOL fPathIsConnectName,
	ITRiASConnection **ppIConn)
{
	if (NULL == pIPrj) return E_INVALIDARG;

WTRiASConnections Conns;
WTRiASConnection Conn;
HRESULT hr = S_OK;

	try {
	// Sammlung aller Connections geben lassen und eine neue hinzufügen
		THROW_FAILED_HRESULT(pIPrj -> get_Connections (Conns.ppi()));
		THROW_FAILED_HRESULT(Conns -> Add (CComBSTR(pcConnName), Conn.ppi()));

	// Connection mit allem notwendigen initialisieren
		if (fNameIsSubStorage) {
		// Im Substorage erzeugen
			_ASSERTE(1 == rFiles.size());

		CComBSTR bstrName (g_cbStorage);		// Kennung für SubStorage dranhängen

			bstrName += (*rFiles.begin()).c_str();
			THROW_FAILED_HRESULT(Conn -> put_Location (bstrName));
		} 
		else if (fPathIsConnectName) {
		// lediglich connectinfo gegeben
			_ASSERTE(1 == rFiles.size());

		CComBSTR bstrName (g_cbConnect);		// Kennung für ConnectInfo dranhängen

			bstrName += (*rFiles.begin()).c_str();
			THROW_FAILED_HRESULT(Conn -> put_Location (bstrName));
		} 
		else {
			if (rFiles.size() == 1) {
				THROW_FAILED_HRESULT(Conn -> put_Location (CComBSTR((*rFiles.begin()).c_str())));
			} else if (rFiles.size() > 1) {
			WEnumString Enum;

				THROW_FAILED_HRESULT(MakeEnumString (Conn, rFiles, Enum.ppi()));
				THROW_FAILED_HRESULT(Conn -> put_Locations (Enum));
			} 
//			else {
//			// Oracle et. al.
//			}
		}
	
	// ConnectString im Format ';PROGID=progid' zusammenbauen und übergeben
	CComBSTR bstrConnect (g_cbConnSource);

		bstrConnect.Append (pcProgID);
		if (NULL != pcConnect && strlen (pcConnect) > 0) {
			if (';' != pcConnect[0])
				bstrConnect.Append (g_cbSemicolon);
			bstrConnect.Append (pcConnect);
		}

		THROW_FAILED_HRESULT(Conn -> put_ConnectInfo (bstrConnect));

	// in der Registry haben wir lediglich den ClsId des TRiASDatabase-Objektes gefunden
	CIID ClsId (rClsId);

		THROW_FAILED_HRESULT(Conn -> put_Type (CComBSTR(ClsId.ProgID().c_str())));
		THROW_FAILED_HRESULT(Conn -> put_Description (CComBSTR(pcConnDesc)));
		THROW_FAILED_HRESULT(Conn -> put_Mode (rgMode));
		THROW_FAILED_HRESULT(hr = Conn -> Connect(CONNECTMODE_UseDefaultMode));	// hier geht's los

		if (NULL != ppIConn)
			*ppIConn = Conn.detach();

	} catch (_com_error &e) {
	// Fehlermeldung ausgeben
		VMessageBox (MWind(), FakeTRiASName(IDS_DATASOURCEERROR_CAP, g_cbTRiAS).c_str(), 
			MB_OK|MB_ICONEXCLAMATION, IDS_COULDNOTOPENDATASOURCE, pcConnDesc, pcConnName, _COM_ERROR(e));

	// Schadensbegrenzung
		if ((NULL != (ITRiASConnections *)Conns) &&
			(NULL != (ITRiASConnection *)Conn))
		{
		CComBSTR bstrName;

			if (SUCCEEDED(Conn -> get_Name (CLEARED(&bstrName))))
				Conns -> Remove (CComVariant(bstrName));
		}
		return _COM_ERROR(e);
	}
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
// Finden und Liefern der MainDBEngine, welche Projekte erzeugen kann
HRESULT CFakeMFCExtension::GetMainDBEngine (ITRiASMainDBEngine **ppIEngine)
{
	if (NULL == ppIEngine)
		return E_POINTER;
	*ppIEngine = NULL;

// DBEngines enumerieren, finden der Hauptengine
	try {
		for (CTRiASDBEngines::iterator it = m_DBEngs.begin(); it != m_DBEngs.end(); ++it)
		{
		WTRiASMainDBEngine Main;

			if (SUCCEEDED((*it).first -> QueryInterface (IID_ITRiASMainDBEngine, Main.ppv())))
			{
				*ppIEngine = Main.detach();
				return S_OK;
			}
		}

	} catch (_com_error &e) {
		return _COM_ERROR(e);
	}
	return E_UNEXPECTED;	// keine Engine kann Projekte verwalten
}

///////////////////////////////////////////////////////////////////////////////
// TargetProgID des DataServerObjektes besorgen

HRESULT CFakeMFCExtension::RetrieveTarget (BSTR bstrProgID, BSTR *bstrTargetProgID)
{
	if (NULL == bstrTargetProgID)
		return E_POINTER;

// ClsId der TRiASDatabase-class aus Registry lesen
	USES_CONVERSION;

// evtl. DataServerRegEntries besorgen, aber nur einmal und nur dann, wenn nötig
	if (!m_Entries.IsValid()) {
		try {
			m_Entries = WTRiASDataServerRegEntries(CLSID_TRiASDataServerRegEntries);
		} catch (_com_error &e) {
			return _COM_ERROR(e);
		}
	}
	_ASSERTE(m_Entries.IsValid());

// jetzt die gewünschten Daten besorgen
WTRiASDataServerRegEntry Entry;
HRESULT hr = m_Entries -> FindFromServerProgID (bstrProgID, Entry.ppi());

	if (SUCCEEDED(hr)) 
		hr = Entry -> get_DataServerClass(bstrTargetProgID);
	return hr;
}	

///////////////////////////////////////////////////////////////////////////////
// DataServerParams über ProgID besorgen

HRESULT CFakeMFCExtension::ReadDataServerParams (DWORD &rdwPos, CConnectParams *pNewItem, LPCTSTR pcProgID)
{
	USES_CONVERSION;

// evtl. defaultparams auflösen
	if (NULL == pcProgID)
		pcProgID = g_cbDefaultDataBase;

// evtl. DataServerRegEntries besorgen, aber nur einmal und nur dann, wenn nötig
	if (!m_Entries.IsValid()) {
		try {
			m_Entries = WTRiASDataServerRegEntries(CLSID_TRiASDataServerRegEntries);
		} catch (_com_error &e) {
			return _COM_ERROR(e);
		}
	}
	_ASSERTE(m_Entries.IsValid());

// jetzt die gewünschten Daten besorgen
WTRiASDataServerRegEntry Entry;
CComBSTR Name (pcProgID);
HRESULT hr = m_Entries -> FindFromServerProgID (Name, Entry.ppi());

	if (FAILED(hr)) return hr;

	TRY {
	VARIANT_BOOL fFlag;
	CComBSTR bstr;

		pNewItem -> m_strProgID = pcProgID;

	// ClassID muß exitieren, sonst geht garnichts
	HRESULT hr = Entry -> get_DatabaseClass (CLEARED(&bstr));

		if (FAILED(hr)) return hr;

		hr = CLSIDFromProgID (bstr, &pNewItem -> m_ClsId);
		if (FAILED(hr)) return hr;

		if (SUCCEEDED(Entry -> get_IsReadWrite (&fFlag)))
			pNewItem -> m_fIsReadWrite = fFlag ? TRUE : FALSE;

		if (SUCCEEDED(Entry -> get_ShortName (CLEARED(&bstr))))
			pNewItem -> m_strShortName = OLE2A(bstr);

		if (SUCCEEDED(Entry -> get_LongName (CLEARED(&bstr))))
			pNewItem -> m_strLongName = OLE2A(bstr);

		if (SUCCEEDED(Entry -> get_FileDescription (CLEARED(&bstr))))
			pNewItem -> m_strFileDesc = OLE2A(bstr);

		if (SUCCEEDED(Entry -> get_FilterString (CLEARED(&bstr))))
			pNewItem -> m_strFilter = OLE2A(bstr);

		if (SUCCEEDED(Entry -> get_DefaultExtension (CLEARED(&bstr))))
			pNewItem -> m_strDefExt = OLE2A(bstr);

		if (SUCCEEDED(Entry -> get_NameIsFile (&fFlag)))
			pNewItem -> m_fNameIsFile = fFlag ? TRUE : FALSE;

		if (fFlag && SUCCEEDED(Entry -> get_MultipleFiles (&fFlag)))
			pNewItem -> m_fMultipleFiles = fFlag ? TRUE : FALSE;
		else
			pNewItem -> m_fMultipleFiles = FALSE;

		if (SUCCEEDED(Entry -> get_NameIsDirectory (&fFlag)))
			pNewItem -> m_fNameIsDir = fFlag ? TRUE : FALSE;

		if (SUCCEEDED(Entry -> get_NameIsSubStorage (&fFlag)))
			pNewItem -> m_fNameIsSubStorage = fFlag ? TRUE : FALSE;

		if (SUCCEEDED(Entry -> get_TempName (CLEARED(&bstr))))
			pNewItem -> m_strTempName = OLE2A(bstr);

		if (SUCCEEDED(Entry -> get_LastDirUsed (CLEARED(&bstr))))
			pNewItem -> m_strLastDirUsed = OLE2A(bstr);

		if (SUCCEEDED(Entry -> get_OpenWizPages (CLEARED(&bstr))))
			pNewItem -> m_strExtProgID = OLE2A(bstr);

		if (SUCCEEDED(Entry -> get_NeedsCoordSystemExisting (&fFlag)))
			pNewItem -> m_fNeedsCoordSysWizExisting = fFlag ? TRUE : FALSE;

		if (SUCCEEDED(Entry -> get_NeedsCoordSystemNew (&fFlag)))
			pNewItem -> m_fNeedsCoordSysWizNew = fFlag ? TRUE : FALSE;

		_ASSERTE(sizeof(LONG) == sizeof(DWORD));		// verify correctness of following cast
		Entry -> get_ToolboxBitmap32 ((LONG *)&rdwPos);
		Entry -> get_RestrictInstances (&pNewItem -> m_lInstances);

	} CATCH(CMemoryException, e) {
		return E_OUTOFMEMORY;
	} END_CATCH;
	return S_OK;
}


