// @doc
// @module TRiASConnection.cpp | Implementation of the <c CTRiASConnection> class

#include "stdafx.h"

#include <AfxDlgs.h>

#include <ospace/file/path.h>
#include <Atl/Ciid.h>
#include <Com/PropertyHelper.h>
#include <Com/MkHelper.h>
#include <Com/ComBool.h>

#include <ScopeVar.h>
#include <dirisole.h>

#import "tlb/Helper.tlb" \
	raw_interfaces_only raw_dispinterfaces no_namespace named_guids \
	exclude("IParseRegularExpression", "IParseStringPairs", "IComposeStringPairs") \
	exclude("IParseStringPairs2")

#include "PathDialog.h"
#include "MessageBoxEx.h"

#include "PersistEnum.h"
#include "Strings.h"
#include "Wrapper.h"
#include "GlobalVars.h"
#include "TRiASDBGuids.h"
#include "CSFactory.h"

#include "TRiASDBEngine.h"
#include "TRiASConnection.h"
#include "TRiASProperty.h"
#include "ConnectionMoniker.h"

/////////////////////////////////////////////////////////////////////////////
// RUNTIME_OBJECT_MAP
RT_OBJECT_ENTRY(CLSID_TRiASConnection, CTRiASConnection)

/////////////////////////////////////////////////////////////////////////////
// benötigter Guid
extern const CLSID __declspec(selectany) CLSID_DirisProject = 
	{0x937EEB40,0x2234,0x101B,{0xAA,0xE1,0xE7,0xE7,0xE7,0xE7,0xE7,0xE7}};

/////////////////////////////////////////////////////////////////////////////
// SmartInterface's
DefineSmartInterface(TRiASConnectionEvents);
DefineSmartInterface(BindCtx);
DefineSmartInterface(OleClientSite);
DefineSmartInterface(OleItemContainer);
DefineSmartInterface(TRiASCS);
DefineSmartInterface(TRiASDataServerRegEntries);
DefineSmartInterface(TRiASDataServerRegEntry);
DefineSmartInterface(ParseStringPairs);
DefineSmartInterface(TRiASMainDBEngine);
DefineSmartInterface(ReconnectDialog);

///////////////////////////////////////////////////////////////////////////////
// statische Daten
DWORD CTRiASConnection::m_rgAskMode = ASKMODE_NoOptions;

/////////////////////////////////////////////////////////////////////////////
//
HRESULT GenerateFullPath (LPCTSTR pcDBName, bool fMakeSubDir, os_string &rStr);

// Funktion entscheidet, ob IPersistStorage verfügbar ist oder nicht
HRESULT WINAPI CTRiASConnection::_Choice (void *pv, REFIID iid, void** ppvObject, DWORD dw)
{
CTRiASConnection *pThis = (CTRiASConnection *)pv;

	if (!pThis -> m_fPathIsStorageName) 
		return E_NOINTERFACE;		// IPersistStorage ist nicht verfügbar

// ansonsten normales QI
IUnknown* pUnk = (IUnknown*)((int)pThis+dw);

	pUnk->AddRef();
	*ppvObject = pUnk;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// ISupportsErrorInfo
STDMETHODIMP CTRiASConnection::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITRiASConnection,
	};

	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

HRESULT CTRiASConnection::FinalConstruct (void)
{
	return S_OK;
}

void CTRiASConnection::FinalRelease()
{
	FreePropertiesCollection();
}

/////////////////////////////////////////////////////////////////////////////
// IPersist
STDMETHODIMP CTRiASConnection::GetClassID (CLSID *pClassID)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pClassID) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASConnection::GetClassID");

	*pClassID = CLSID_TRiASConnection;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistStream
STDMETHODIMP CTRiASConnection::IsDirty (void)
{
// Connection selbst testen
	if (m_fIsDirty) 
		return S_OK;

// angehängte Datenbank testen
CComBool fDirty;

	if (!!m_DB && SUCCEEDED(m_DB -> get_IsDirty(&fDirty)))
		return fDirty ? S_OK : S_FALSE;
	return S_FALSE;
}

STDMETHODIMP CTRiASConnection::Load (LPSTREAM pStm)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (m_fIsInitialized)
		return E_UNEXPECTED;

	COM_TRY {
	// zwar noch nicht initialisiert, aber immerhin gerade dabei
	CScopeVar<bool> Scope(m_fIsInitializing, true);

		THROW_FAILED_HRESULT(CreatePropertiesCollection());

	// eigene Daten jetzt einlesen
	long lSignature = 0L;

		THROW_FAILED_HRESULT(LoadLong (pStm, lSignature));			// Signatur
		if (CONNECTION_SIGNATURE != lSignature)
			return TRIASDB_E_BADOBJECTSIGNATURE;

	long lVersion = 0L;

		THROW_FAILED_HRESULT(LoadLong (pStm, lVersion));			// VersionInfo
		if ((lVersion & ~CONNECTION_VERSION_MINOR_MASK) > LASTKNOWN_CONNECTION_VERSION)
			return TRIASDB_W_NEWERCONNECTION;
		if (lVersion <= CONNECTION_VERSION_101)
			m_fUseOldMks = true;

		m_bstrName.Empty();
		m_bstrDesc.Empty();
		m_bstrConnect.Empty();
		m_bstrType.Empty();
		m_bstrPath.Empty();

		THROW_FAILED_HRESULT(m_bstrName.ReadFromStream (pStm));
		THROW_FAILED_HRESULT(m_bstrDesc.ReadFromStream (pStm));
		THROW_FAILED_HRESULT(m_bstrConnect.ReadFromStream (pStm));
		THROW_FAILED_HRESULT(m_bstrType.ReadFromStream (pStm));
		THROW_FAILED_HRESULT(m_bstrPath.ReadFromStream (pStm));
		if (lVersion >= CONNECTION_VERSION_101) {
			THROW_FAILED_HRESULT(LoadData (pStm, m_GuidPath));
			m_bstrRelPath.Empty();
			THROW_FAILED_HRESULT(m_bstrRelPath.ReadFromStream (pStm));
		} else {
			m_GuidPath.New();
		}

	LONG lData = FALSE;

		THROW_FAILED_HRESULT(LoadLong (pStm, lData));					// CONNECTMODE
		m_rgMode = (CONNECTMODE)lData;
		m_fIsReadOnly = (m_rgMode & CONNECTMODE_OpenReadWrite) ? false : true;

		THROW_FAILED_HRESULT(LoadLong (pStm, lData));					// CONNECTSTATUS
		THROW_FAILED_HRESULT(LoadEnumeratedItems (GetProperties(), pStm, &FMTID_EnumProperties, (ITRiASProperty *)NULL, CONNECTION_VERSION_103 <= lVersion));	// Properties lesen

		m_fMustConnectAfterLoad = (lData != 0) ? true : false;

		if (lVersion >= CONNECTION_VERSION_104) {
			THROW_FAILED_HRESULT(LoadLong (pStm, lData));				// fPathIsStorageName
			m_fPathIsStorageName = (lData != 0) ? true : false;
		} else
			m_fPathIsStorageName = false;

		if (lVersion >= CONNECTION_VERSION_105) {
			THROW_FAILED_HRESULT(LoadLong (pStm, lData));				// fPathIsConnectName
			if (lVersion >= CONNECTION_VERSION_106)						// BUG in 105 tolerieren
				m_fPathIsConnectName = (lData != 0) ? true : false;
			else
				m_fPathIsConnectName = false;
		} else
			m_fPathIsConnectName = false;

	} COM_CATCH;
	
	m_fIsDirty = false;
	m_fIsInitialized = true;
	return S_OK;
}

STDMETHODIMP CTRiASConnection::Save (LPSTREAM pStm, BOOL fClearDirty)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	USES_CONVERSION;
	COM_TRY {
	// angehängte Datenbank zuerst speichern, da sich u.U. der Pfad ändern kann
	CONNECTMODE rgMode = m_fIsReadOnly ? 
					GetType(m_rgMode, CONNECTMODE_CloseResolutionFlags) : 
					CONNECTMODE_CloseAutoResolution;

	// Fehler nicht fatal, da sonst nicht sauber aufgeräumt werden kann
		if (m_DB.IsValid())		// nur speichern, wenn geöffnet
			SaveConnectedDatabase (rgMode, true);

	// jetzt ConnectionInfos wegschreiben
		THROW_FAILED_HRESULT(SaveLong (pStm, CONNECTION_SIGNATURE));
		THROW_FAILED_HRESULT(SaveLong (pStm, LASTKNOWN_CONNECTION_VERSION));

		THROW_FAILED_HRESULT(m_bstrName.WriteToStream (pStm));
		THROW_FAILED_HRESULT(m_bstrDesc.WriteToStream (pStm));
		THROW_FAILED_HRESULT(m_bstrConnect.WriteToStream (pStm));
		THROW_FAILED_HRESULT(m_bstrType.WriteToStream (pStm));
		THROW_FAILED_HRESULT(m_bstrPath.WriteToStream (pStm));
		THROW_FAILED_HRESULT(SaveData (pStm, m_GuidPath));

		if (!m_fPathIsStorageName && !m_fPathIsConnectName) {
		// wenn Dateipfad drin ist, dann relativen Pfad zum Projekt berechnen
			THROW_FAILED_HRESULT(CalculateRelPath(OLE2A(m_bstrPath)));
		}
		THROW_FAILED_HRESULT(m_bstrRelPath.WriteToStream (pStm));

		rgMode = m_rgMode;
		if (m_fIsReadOnly)
			rgMode = CONNECTMODE(m_rgMode & ~CONNECTMODE_OpenReadWrite);
		if (!m_DB.IsValid())		// R/O nur bei geöffneten DB's speichern
			rgMode = CONNECTMODE(m_rgMode | CONNECTMODE_OpenReadWrite);
		rgMode = CONNECTMODE(rgMode & ~CONNECTMODE_IsReadOnly);		// physischen Schreibschutz nicht speichern

		THROW_FAILED_HRESULT(SaveLong (pStm, rgMode));

	LONG lData = m_DB.IsValid() ? CONNECTSTATUS_Opened : CONNECTSTATUS_Closed;

		THROW_FAILED_HRESULT(SaveLong (pStm, lData));
		THROW_FAILED_HRESULT(SaveEnumeratedItems (GetProperties(), pStm, &FMTID_EnumProperties, (ITRiASProperty *)NULL));		// Properties

	// ab Version CONNECTION_VERSION_104
		lData = m_fPathIsStorageName;
		THROW_FAILED_HRESULT(SaveLong (pStm, lData));

	// ab Version CONNECTION_VERSION_105
		lData = m_fPathIsConnectName;
		THROW_FAILED_HRESULT(SaveLong (pStm, lData));

		if (fClearDirty)
			m_fIsDirty = false;

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASConnection::GetSizeMax (ULARGE_INTEGER *pcbSize)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pcbSize) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASConnection::GetSizeMax");

	pcbSize -> QuadPart = LenForStream(m_bstrName) + LenForStream(m_bstrConnect) +
						  LenForStream(m_bstrPath) + LenForStream(m_bstrDesc) +
						  LenForStream(m_bstrType) + LenForStream(m_bstrRelPath) + 
						  5*sizeof(LONG) + sizeof(CIID);
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistStreamInit
STDMETHODIMP CTRiASConnection::InitNew (void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (m_fIsInitialized)
		return E_UNEXPECTED;

CScopeVar<bool> Scope(m_fIsInitializing, true);

	m_GuidPath.New();
	RETURN_FAILED_HRESULT(CreatePropertiesCollection());

	m_fIsDirty = true;			// damit das Objekt vom ObjMan weggeschrieben wird
	m_fIsInitialized = true;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Properties
STDMETHODIMP CTRiASConnection::get_Name(BSTR * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASConnection::get_Name");

CComBSTR bstr (m_bstrName);

	if (!bstr)
		return Error(g_cbNoMemory, E_OUTOFMEMORY);

	*pVal = bstr.Detach();
	return S_OK;
}

STDMETHODIMP CTRiASConnection::put_Name(BSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == newVal)
		return E_POINTER;

	if (!m_bstrName || wcscmp (newVal, m_bstrName)) {
	CComBool fRename;

		if (!!m_Parent) {
		// nicht während der Initialisierungsphase
			RETURN_FAILED_HRESULT(Fire_RenamingConnection (m_bstrName, newVal, &fRename));
			if (fRename)
				return S_FALSE;		// abgebrochen oder Fehler
			RETURN_FAILED_HRESULT(Fire_ConnectionToRename (m_bstrName, newVal));
		}

		m_bstrName = newVal;
		if (!m_bstrName)
			return Error (g_cbNoMemory, E_OUTOFMEMORY);

		if (!!m_Parent)
		{
			RETURN_FAILED_HRESULT(Fire_ConnectionRenamed (GetDispatch()));
		}
		m_fIsDirty = true;
	}
	return S_OK;
}

STDMETHODIMP CTRiASConnection::get_Description(BSTR * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASConnection::get_Description");

CComBSTR bstr (m_bstrDesc);

	if (!bstr)
		return Error(g_cbNoMemory, E_OUTOFMEMORY);

	*pVal = bstr.Detach();
	return S_OK;
}

STDMETHODIMP CTRiASConnection::put_Description(BSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	m_bstrDesc = newVal;
	if (!m_bstrDesc)
		return Error (g_cbNoMemory, E_OUTOFMEMORY);

	m_fIsDirty = true;
	return S_OK;
}

STDMETHODIMP CTRiASConnection::get_ConnectInfo(BSTR * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASConnection::get_ConnectInfo");

CComBSTR bstr (m_bstrConnect);

	if (!bstr)
		return Error(g_cbNoMemory, E_OUTOFMEMORY);

	*pVal = bstr.Detach();
	return S_OK;
}

STDMETHODIMP CTRiASConnection::put_ConnectInfo(BSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL != (IUnknown *)m_DB)
		return REPORT_DBERROR(TRIASDB_E_ALREADYCONNECTED);

	m_bstrConnect = newVal;
	if (!m_bstrConnect)
		return Error (g_cbNoMemory, E_OUTOFMEMORY);
	
	m_fIsDirty = true;
	return S_OK;
}

STDMETHODIMP CTRiASConnection::get_Param(CONNECTPARAM * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASConnection::get_Param");

	if (m_fPathIsConnectName)
		*pVal = CONNECTPARAM_ConnectString;
	else if (m_fPathIsStorageName)
		*pVal = CONNECTPARAM_Storage;
	else if (m_fHasMultipleFiles)
		*pVal = CONNECTPARAM_MultiFile;
	else
		*pVal = CONNECTPARAM_FileOrDir;
	return S_OK;
}

STDMETHODIMP CTRiASConnection::get_Status(CONNECTSTATUS * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASConnection::get_Status");

	*pVal = !m_DB.IsValid() ? CONNECTSTATUS_Closed : CONNECTSTATUS_Opened;
	return S_OK;
}

STDMETHODIMP CTRiASConnection::get_Mode(CONNECTMODE * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASConnection::get_Mode");

	*pVal = m_fIsReadOnly ? CONNECTMODE_OpenReadOnly : CONNECTMODE_OpenReadWrite;
	SetType (*pVal, m_rgMode & (CONNECTMODE_OpenFlags|CONNECTMODE_ResolutionFlags|CONNECTMODE_IsReadOnly));
	return S_OK;
}

STDMETHODIMP CTRiASConnection::put_Mode(CONNECTMODE newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_fIsReadOnly = (newVal & CONNECTMODE_OpenFlags) ? false : true;
	m_rgMode = CONNECTMODE(newVal & ~CONNECTMODE_IsReadOnly);
	m_fIsDirty = true;
	return S_OK;
}

STDMETHODIMP CTRiASConnection::get_Type(BSTR * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASConnection::get_Type");

CComBSTR bstr (m_bstrType);

	if (!bstr)
		return Error(g_cbNoMemory, E_OUTOFMEMORY);

	*pVal = bstr.Detach();
	return S_OK;
}

STDMETHODIMP CTRiASConnection::put_Type(BSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL != (IUnknown *)m_DB)
		return REPORT_DBERROR(TRIASDB_E_ALREADYCONNECTED);

	m_bstrType = newVal;
	if (!m_bstrType)
		return Error (g_cbNoMemory, E_OUTOFMEMORY);

	m_fIsDirty = true;
	return S_OK;
}

STDMETHODIMP CTRiASConnection::get_Location(BSTR * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASConnection::get_Location");

CComBSTR bstr (m_bstrPath);

	if (!bstr)
		return Error(g_cbNoMemory, E_OUTOFMEMORY);

	*pVal = bstr.Detach();
	return S_OK;
}

HRESULT CTRiASConnection::GetProjectPath (os_string &rStrPath)
{
WTRiASProject Prj;
CComBSTR bstrPrjPath;

	USES_CONVERSION;
	if (SUCCEEDED(FindSpecificParent(m_Parent, Prj.ppi())) && 
		SUCCEEDED(Prj -> get_Name (CLEARED(&bstrPrjPath))))
	{
		return GenerateFullPath (OLE2A(bstrPrjPath), false, rStrPath);
	}

WTRiASMainDBEngine DBEng;

	VERIFY(SUCCEEDED(g_pDBEngine -> QueryInterface (IID_ITRiASMainDBEngine, DBEng.ppv())));
	if (SUCCEEDED(DBEng -> get_ProjectToOpen(CLEARED(&bstrPrjPath))))
		return GenerateFullPath (OLE2A(bstrPrjPath), false, rStrPath);

	return E_FAIL;
}

///////////////////////////////////////////////////////////////////////////////
// WurzelStorage des Projektes besorgen
HRESULT CTRiASConnection::GetProjectSubStorage (bool fRO, IStorage **ppIStg)
{
	_ASSERTE(m_fPathIsStorageName);
	_ASSERTE(m_bstrPath.Length() > 0);

WTRiASProject Prj;

	RETURN_FAILED_HRESULT(FindSpecificParent(m_Parent, Prj.ppi()));
	_ASSERTE(SupportsInterface (Prj, (IOleItemContainer *)NULL));

WBindCtx Ctx;
DWORD dwMode = 0;

	if (fRO)
		dwMode = STGM_READ|STGM_SHARE_EXCLUSIVE|STGM_TRANSACTED;
	else
		dwMode = STGM_READWRITE|STGM_SHARE_EXCLUSIVE|STGM_TRANSACTED;

	RETURN_FAILED_HRESULT(MkCreateAndInitBindCtx (Ctx.ppi(), dwMode));
	RETURN_FAILED_HRESULT(WOleItemContainer(Prj) -> GetObjectStorage (m_bstrPath, Ctx, IID_IStorage, (LPVOID *)ppIStg));
	return S_OK;
}

STDMETHODIMP CTRiASConnection::put_Location (BSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (m_DB.IsValid())
		return REPORT_DBERROR(TRIASDB_E_ALREADYCONNECTED);
	return PutLocation(newVal);
}

HRESULT CTRiASConnection::PutLocation (BSTR newVal)
{
// ggf. vollen Dateinamen generieren
	if (!wcsncmp (g_cbStorage, newVal, wcslen(g_cbStorage))) {
	// storagebasiert
		m_bstrPath = newVal + wcslen(g_cbStorage);
		m_fPathIsStorageName = true;
		m_fPathIsConnectName = false;
	} 
	else if (!wcsncmp (g_cbConnect, newVal, wcslen(g_cbConnect))) {
	// Connectstring gegeben
		m_bstrPath = newVal + wcslen(g_cbConnect);
		m_fPathIsStorageName = false;
		m_fPathIsConnectName = true;
	} 
	else {
	// absoluten Dateinamen lokal speichern
	os_string str;
	CComBSTR bstrPath (newVal);

		USES_CONVERSION;
		if (!wcsncmp (g_cbFile, newVal, wcslen(g_cbFile))) 
			bstrPath = newVal + wcslen(g_cbFile);

	// nur dann ändern, wenn neuer Pfad gegeben wird
		if (m_bstrPath.Length() > 0 && !wcscmp (newVal, m_bstrPath))
			return S_FALSE;

		RETURN_FAILED_HRESULT(GenerateFullPath (OLE2A(bstrPath), false, str));
		CalculateRelPath(str.c_str());
		m_bstrPath = str.c_str();
		m_fPathIsStorageName = false;
		m_fPathIsConnectName = false;
	}

	if (!m_bstrPath)
		return Error (g_cbNoMemory, E_OUTOFMEMORY);

	m_fHasMultipleFiles = false;
	m_fIsDirty = true;
	return S_OK;
}

HRESULT CTRiASConnection::CalculateRelPath (LPCSTR pcRisPath)
{
	_ASSERTE(!m_fPathIsStorageName && !m_fPathIsConnectName);

// relativen Dateinamen zum Projekt berechnen und speichern
os_string relstr;

	m_bstrRelPath = g_bstrNil;
	if (SUCCEEDED(GetProjectPath (relstr)))
	{
	os_path rispath (pcRisPath);
	os_path riwpath (relstr);

		_ASSERTE(rispath.absolute() && riwpath.absolute());	// beide VerzeichnisPfade müssen absolute sein

		riwpath.filename (g_cbNil);				// Dateinamen herauslöschen (muß Verzeichnis sein)
		rispath.become_relative_to (riwpath);
		m_bstrRelPath = os_string(rispath).c_str();
		if (!m_bstrRelPath)
			return Error (g_cbNoMemory, E_OUTOFMEMORY);
	}
	return S_OK;
}

STDMETHODIMP CTRiASConnection::get_Locations(IUnknown **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASConnection::get_Locations");

	*pVal = m_Files;
	if (NULL != *pVal) LPUNKNOWN(*pVal) -> AddRef();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// EnumeratorObjekt für LPOLESTR's
typedef CComEnum<IEnumString, &IID_IEnumString, LPOLESTR, _Copy<LPOLESTR> > CEnumString;
typedef set<os_string, less<os_string> > CFiles;

HRESULT MakeEnumString (IUnknown *pUnk, const CFiles &rFiles, IEnumString **ppIEnum)
{
	_ASSERTE(rFiles.size() > 1);

// Zeiger umkopieren, damit ein zusammenhängender Vektor entsteht,
// dazu auf dem Stack den Speicher anfordern (gibt sich selbst frei!)
size_t iCnt = rFiles.size();
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

STDMETHODIMP CTRiASConnection::put_Locations(IUnknown *newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

LPOLESTR lpole = NULL;

	USES_CONVERSION;
	COM_TRY {
	WEnumString Files (newVal);
	CFiles FileSet;
	bool fFirst = true;

	// ersten Pfad als Notanker merken
		for (Files -> Reset(); S_OK == Files -> Next (1, &lpole, NULL); /**/) {
		os_string str;

			if (SUCCEEDED(GenerateFullPath (OLE2A(lpole), false, str))) {
				FileSet.insert(str);
				if (fFirst) {
					fFirst = false;
					put_Location (CComBSTR(str.c_str()));
				}
			}
			CoTaskMemFree (lpole);
		}
		_ASSERTE(!fFirst);

	// neuen Enumerator anlegen
		THROW_FAILED_HRESULT(MakeEnumString (GetUnknown(), FileSet, m_Files.ppi()));
		m_fHasMultipleFiles = true;
		m_fPathIsStorageName = false;
		m_fPathIsConnectName = false;

	} COM_CATCH_OP(CoTaskMemFree (lpole));

	return S_OK;
}

STDMETHODIMP CTRiASConnection::get_Application(IDispatch **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASConnection::get_Application");

	*pVal = m_Application;
	if (NULL != *pVal) LPUNKNOWN(*pVal) -> AddRef();

	return S_OK;
}

STDMETHODIMP CTRiASConnection::put_Application(IDispatch *newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_Application = newVal;
	return S_OK;
}

STDMETHODIMP CTRiASConnection::get_Parent(IDispatch **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASConnection::get_Application");

	*pVal = m_Parent;
	if (NULL != *pVal) LPUNKNOWN(*pVal) -> AddRef();

	return S_OK;
}

STDMETHODIMP CTRiASConnection::put_Parent(IDispatch *newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_Parent = newVal;

// das Nullsetzen des Parent wird als Signal zum Freigeben gewertet
// evtl. alle SubObjekte von ihrem Bezug abhängen
	if (!m_Parent) {
	// Properties freigeben
		FreePropertiesCollection();

	// SupportObjekte freigeben
		ReleasePropertySupportObjects();

		m_fIsDirty = false;
		m_fIsInitialized = false;		// jetzt nicht mehr initialisiert
	} 
	else if (!m_fIsInitialized) {
	// bei SaveAs des Projektes muß Connection neu initialisiert werden
	CScopeVar<bool> Scope(m_fIsInitializing, true);

		RETURN_FAILED_HRESULT(CreatePropertiesCollection());	// Properties neu erzeugen/refreshen

	// wenn derzeit die angehängte Datenbank geöffnet ist, dann dieser die Chance geben,
	// evtl. Neuinitialisierungen vorzunehmen
//		if (m_DB.IsValid()) {
//			RETURN_FAILED_HRESULT(m_DB -> ReLoad (RELOADDATABASE_ConnectionInitialized));
//		}
		m_fIsInitialized = true;
		m_fIsDirty = false;
	}
	return S_OK;
}

STDMETHODIMP CTRiASConnection::get_Database(ITRiASDatabase **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_DB.IsValid())
		return REPORT_DBERROR(TRIASDB_E_NOTCONNECTED);
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASConnection::get_Database");

WTRiASDatabase DB (m_DB);

	*pVal = DB.detach();
	return S_OK;
}

STDMETHODIMP CTRiASConnection::get_Updatable(VARIANT_BOOL * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_DB.IsValid())
		return REPORT_DBERROR(TRIASDB_E_NOTCONNECTED);
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASConnection::get_Updatable");

	return m_DB -> get_Updatable (pVal);
}

STDMETHODIMP CTRiASConnection::get_SchemaUpdatable(VARIANT_BOOL * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_DB.IsValid())
		return REPORT_DBERROR(TRIASDB_E_NOTCONNECTED);
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASConnection::get_SchemaUpdatable");

	return m_DB -> get_SchemaUpdatable(pVal);
}

STDMETHODIMP CTRiASConnection::get_Transactions(VARIANT_BOOL * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_DB.IsValid())
		return REPORT_DBERROR(TRIASDB_E_NOTCONNECTED);
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASConnection::get_Transactions");

	return m_DB -> get_Transactions (pVal);
}

STDMETHODIMP CTRiASConnection::get_Version(BSTR * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_DB.IsValid())
		return REPORT_DBERROR(TRIASDB_E_NOTCONNECTED);
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASConnection::get_Version");

	return m_DB -> get_Version(pVal);
}

STDMETHODIMP CTRiASConnection::get_VersionLong(LONG * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_DB.IsValid())
		return REPORT_DBERROR(TRIASDB_E_NOTCONNECTED);
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASConnection::get_VersionLong");

	return m_DB -> get_VersionLong (pVal);
}

STDMETHODIMP CTRiASConnection::get_GuidPath(BSTR *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASConnection::get_GuidPath");

CComBSTR bstr (m_GuidPath);

	if (!bstr)
		return Error(g_cbNoMemory, E_OUTOFMEMORY);

	*pVal = bstr.Detach();
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Methods
HRESULT CTRiASConnection::AskToOpenConnectionRO (HRESULT hr)
{
// ggf. steht schon fest, was in diesem Fall gemacht werden soll
	if (m_rgAskMode & ASKMODE_YesAllOpenRO)
		return S_OK;		// alle weiteren RO öffnen
	else if (m_rgAskMode & ASKMODE_NoAllOpenRO)
		return hr;			// alle weiteren _nicht_ öffnen

// MessageBox anzeigen, in der gefragt wird, ob Projekt schreibgeschützt geöffnet
// werden soll
CString strText;
UINT uiRes = 0;

	switch (hr) {
	case TRIASDB_S_MUSTOPENASCOPY:
		uiRes = IDS_OPENCOPYTEXT;
		break;

	case TRIASDB_S_MUSTOPENASCOPY_SHAREVIOLATION:
		uiRes = IDS_SHAREVIOLATIONCOPYTEXT;
		break;

	default:
		_ASSERTE(FALSE);
		break;
	}

	_ASSERTE(0 != uiRes);
	strText.Format (uiRes, m_bstrPath);

CWnd *pWndParent = CWnd::FromHandle(GetActiveWindow());
CMessageBoxEx mb (strText, FakeTRiASName (IDS_OPENPROJECTCAP, g_cbTRiAS).c_str(), 
	false, pWndParent);

	switch (mb.Show()) {
	case IDYES:
		return S_OK;	// RO eröffnen

	case IDC_YESALL:
		m_rgAskMode |= ASKMODE_YesAllOpenRO;
		return S_OK;	// RO eröffnen

	case IDNO:
		break;

	case IDC_NOALL:
		m_rgAskMode |= ASKMODE_NoAllOpenRO;
		break;
	}
	return hr;			// nicht öffnen
}

namespace {
	HRESULT RetrieveProgIDFromConnectString (BSTR bstrConnect, BSTR *pbstrProgID)
	{
		if (NULL == pbstrProgID) return E_POINTER;

		COM_TRY {
		WParseStringPairs Parse (CLSID_ParseStringPairs);	// throws hr
		CComBSTR bstrVal;
		long lPairs = 0;

			THROW_FAILED_HRESULT(Parse -> put_Pattern(CComBSTR(g_cbCollatePattern)));
			THROW_FAILED_HRESULT(Parse -> Parse(bstrConnect, &lPairs));
			if (0 == lPairs) return E_UNEXPECTED;		// keine Key/Value-Paare gefunden

			THROW_FAILED_HRESULT(Parse -> get_Value (CComBSTR(g_cbProgID), CLEARED(&bstrVal)));
			*pbstrProgID = bstrVal.Detach();

		} COM_CATCH;
		return S_OK;
	}
} // namespace

bool CTRiASConnection::AskToRepairLink()
{
	_ASSERTE(!m_fPathIsStorageName);

	COM_TRY {
	WTRiASDataServerRegEntries RegEntries (CLSID_TRiASDataServerRegEntries);
	WTRiASDataServerRegEntry RegEntry;
	CComBSTR bstrProgID;
	CComBSTR bstrDlgClsId;
	CComBool fFile, fDir;

		THROW_FAILED_HRESULT(RetrieveProgIDFromConnectString (m_bstrConnect, CLEARED(&bstrProgID)));
		THROW_FAILED_HRESULT(RegEntries -> FindFromServerProgID (bstrProgID, RegEntry.ppi()));

		THROW_FAILED_HRESULT(RegEntry -> get_NameIsFile (&fFile));
		THROW_FAILED_HRESULT(RegEntry -> get_NameIsDirectory (&fDir));

	// erstmal nachfragen
	CString strText;
	UINT uiRes = 0;

		if (fDir) 
			strText.Format (IDS_BROKENLINKDIR, m_bstrPath, m_bstrName);
		else if (fFile) 
			strText.Format (IDS_BROKENLINK, m_bstrPath, m_bstrName);
		else
			strText.Format (IDS_BROKENCONNECTION, m_bstrName, m_bstrPath);


	int iRes = AfxGetMainWnd() -> MessageBox (
					strText, FakeTRiASName (IDS_OPENPROJECTCAP, g_cbTRiAS).c_str(), 
					MB_TASKMODAL|MB_YESNO|MB_ICONQUESTION);

		if (iRes == IDNO) 
			return false;	// Connection geschlossen halten

		if (fFile || fDir) {
		// FileDlg anzeigen
		CComBSTR bstrNewName;

			if (!ShowOpenFileDialog (IDS_OPENPROJECTCAP, m_bstrPath, CLEARED(&bstrNewName), RegEntry))
				return false;

			return SUCCEEDED(PutLocation(bstrNewName));	// auch RelPath neu berechnen
		}
		else if (SUCCEEDED(RegEntry -> get_ReconnectDialog(CLEARED(&bstrDlgClsId)))) {
		// spezieller Dialog wird zur Verfügung gestellt
		CIID Guid (bstrDlgClsId, CIID::INITCIID_InitFromProgId);
		CComBSTR bstrNewName;
		CComBSTR bstrNewConnString;
		CComBSTR bstrNewPath;
		WReconnectDialog Dlg (Guid);

			if (FAILED(Dlg -> GetReconnectParams(
				reinterpret_cast<INT_PTR>(AfxGetMainWnd()->GetSafeHwnd()),
				m_bstrName, m_bstrDesc, m_bstrConnect, m_bstrPath,
				CLEARED(&bstrNewName), CLEARED(&bstrNewConnString), CLEARED(&bstrNewPath))))
			{
				return false;
			}

		// neue Parameter setzen
			THROW_FAILED_HRESULT(put_Name(bstrNewName));
			THROW_FAILED_HRESULT(PutLocation(bstrNewPath));
			THROW_FAILED_HRESULT(put_ConnectInfo(bstrNewConnString));
			return true;
		}

	// Verbindung konnte nicht wiederhergestellt werden
		strText.Format(IDS_COULDNOTRECONNECT, m_bstrName, m_bstrPath, g_cbTRiAS);
		AfxGetMainWnd() -> MessageBox (
			strText, FakeTRiASName (IDS_OPENPROJECTCAP, g_cbTRiAS).c_str(), 
			MB_TASKMODAL|MB_OK|MB_ICONEXCLAMATION);

	} COM_CATCH_IGNORE;
	return false;
}

HRESULT CTRiASConnection::MakeFullRelativePath (BSTR *pbstrFullRel)
{
	_ASSERTE(!m_fPathIsStorageName && !m_fPathIsConnectName);

	USES_CONVERSION;
	COM_TRY {
	os_string strPath;

		THROW_FAILED_HRESULT(GetProjectPath (strPath));

	os_path path (strPath);
		
		if (!m_fPathIsStorageName && !m_fPathIsConnectName) {
		// wenn Dateipfad gegeben ist, dann neuen evtl. Pfad berechnen
		os_path relpath(OLE2A(m_bstrRelPath));

			if (relpath.relative()) {
			// nur, wenn relpath wirklich relativ ist
				path.filename (g_cbNil);		// Dateiname kommt vom RelPath
				path = os_string(path) + OLE2A(m_bstrRelPath);
				path.become_simplified();
			} else
				path = OLE2A(m_bstrRelPath);
		}

	CComBSTR bstrRes (os_string(path).c_str());

		*pbstrFullRel = bstrRes.Detach();

	} COM_CATCH;
	return S_OK;
}

bool CTRiASConnection::TellThatWeCanOpenOnlyOne (BSTR bstrName)
{
	USES_CONVERSION;

// erstmal mitteilen, daß diese Datenbank jeweils nur eine Datei öffnen kann
int iReply = VMessageBox (FakeTRiASName (IDS_OPENPROJECTCAP, g_cbTRiAS).c_str(),
		MB_TASKMODAL|MB_YESNO|MB_ICONQUESTION, IDS_COULDOPENONLYONE, OLE2A(bstrName));

	return (iReply == IDYES) ? true : false;
}

STDMETHODIMP CTRiASConnection::Connect(CONNECTMODE rgMode)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (m_DB.IsValid())
		return REPORT_DBERROR(TRIASDB_E_ALREADYCONNECTED);

// Testen, ob alle Informationen verfügbar sind, die gebraucht werden
	if (!m_bstrType)
		return REPORT_DBERROR(TRIASDB_E_MISSINGPARAMETER);

// m_fIsDirty ist hier true, wenn Objekt neu erzeugt wurde (InitNew)
bool fWasDirty = m_fIsDirty;

// evtl. Parameter richten
	if (CONNECTMODE_UseDefaultMode == rgMode) {
	// Voreinstellungen verwenden
		rgMode = m_rgMode;
	
	} else if (CONNECTMODE_ConnectAfterLoadIfApplicable & rgMode) {
	// von Load überfälliges Connect nachholen
		if (!m_fMustConnectAfterLoad)		// soll nicht verbunden werden
			return S_OK;
		rgMode = m_rgMode;
		m_fMustConnectAfterLoad = false;		// darf nur einmal gerufen werden
	}

// wenn hier RO gefordert wird und Nutzer nicht gefragt werden soll, 
// dann bisherige Einstellungen überschreiben
	if (!(rgMode & CONNECTMODE_OpenReadWrite) && !(rgMode & CONNECTMODE_OpenUserResolves))
		m_fIsReadOnly = true;
	else if (rgMode & CONNECTMODE_OpenReadWrite)
		m_fIsReadOnly = false;
	ClearType(m_rgMode, CONNECTMODE_IsReadOnly);	// sicherheitshalber rücksetzen

// ggf. AskMode behandeln
	if (rgMode & CONNECTMODE_ResetConnectAskMode) {
		ResetAskModeOpenRO();
		ClearType (m_rgMode, CONNECTMODE_ResetConnectAskMode);
	}

	COM_TRY {
	// Ausgabe-Koordinatensystem vom Projekt holen
	WTRiASProject Prj;

		THROW_FAILED_HRESULT(FindSpecificParent (GetDispatch(), Prj.ppi()));

	WTRiASCS CS (GetPropertyFrom (WTRiASPropertyBase(Prj), g_cbTRiASCSService, (IDispatch *)NULL), false);

		if (CS.IsValid()) {
			THROW_FAILED_HRESULT(SetProperty (GetProperties(), g_cbTRiASCSService, CComVariant(CS), true));
		}

	// Verbindung zur DB herstellen
	CIID ClsId (m_bstrType, CIID::INITCIID_InitFromProgId);

	// darf Connection geöffnet werden ?
	CComBool fOpen;

		THROW_FAILED_HRESULT(Fire_OpeningConnection (m_bstrName, &fOpen));
		if (fOpen)
			return S_FALSE;		// abgebrochen oder Fehler
		THROW_FAILED_HRESULT(Fire_ConnectionToOpen (m_bstrName));

	WTRiASDatabase DB (ClsId);
	CComBSTR argSource (g_cbTRiASDB);

		if (NULL != (BSTR)m_bstrConnect) {
		// sonstigen gebenen String dazufügen
			if (*m_bstrConnect != L';')
				argSource.Append (L";");
			argSource.Append (m_bstrConnect);
		} else
			argSource.Append (L";");

	// Parent und Application setzen
		THROW_FAILED_HRESULT(DB -> put_Application (m_Application));
		THROW_FAILED_HRESULT(DB -> put_Parent (GetConnection()));

	// Datenbank versuchen zu eröffnen, evtl. Fehler richtig auswerten, ggf. mit Nutzerinterface
	CScopeVar<bool> Scope(m_fIsInitializing, true);			// Connection als Quasi-Valid setzen
	HRESULT hr = S_OK;
	bool fRepeatOpenDatabase = false;
	int iCntRounds = 0;
	CComBSTR bstrRelPath;

		if (!m_fPathIsStorageName && !m_fPathIsConnectName) 
			MakeFullRelativePath (CLEARED(&bstrRelPath));
		else 
			bstrRelPath = m_bstrPath;

		do {	// wiederholen, solange broken link existiert
//		CComBSTR bstrName ((1 == iCntRounds) ? bstrRelPath : m_bstrPath);		// beim zweiten Versuch relativen Pfad nehmen
		CComBSTR bstrName ((1 <= iCntRounds) ? m_bstrPath : bstrRelPath);		// beim ersten Versuch relativen Pfad nehmen

			fRepeatOpenDatabase = false;
			if (m_fHasMultipleFiles) {
				hr = DB -> OpenFilesAsDatabase(m_Files, VARIANT_TRUE, 
					m_fIsReadOnly ? VARIANT_TRUE : VARIANT_FALSE, 
					!m_fIsReadOnly ? VARIANT_TRUE : VARIANT_FALSE, argSource);
				if (E_NOTIMPL == hr) {
				// evtl. wird nur eine Datei unterstützt, dann nehmen wir die erste
				
					if (CONNECTMODE_OpenUserResolves == (rgMode & CONNECTMODE_OpenResolutionFlags) &&
						!TellThatWeCanOpenOnlyOne (m_bstrPath))
					{
						_com_issue_error(TRIASDB_E_COULD_NOT_OPEN);
					}
					hr = DB -> OpenDatabase(m_bstrPath, VARIANT_TRUE, 
						m_fIsReadOnly ? VARIANT_TRUE : VARIANT_FALSE, 
						!m_fIsReadOnly ? VARIANT_TRUE : VARIANT_FALSE, argSource);
				}
			} 
			else if (m_fPathIsStorageName) {
			WStorage Stg;

				THROW_FAILED_HRESULT(GetProjectSubStorage (m_fIsReadOnly, Stg.ppi()));
				THROW_FAILED_HRESULT(DB -> OpenStorageAsDatabase (Stg, VARIANT_TRUE, m_fIsReadOnly ? VARIANT_TRUE : VARIANT_FALSE, VARIANT_FALSE, argSource));
			} 
			else
				hr = DB -> OpenDatabase(bstrName, VARIANT_TRUE, 
					m_fIsReadOnly ? VARIANT_TRUE : VARIANT_FALSE, 
					!m_fIsReadOnly ? VARIANT_TRUE : VARIANT_FALSE, argSource);

			if (FAILED(hr)) {
				if (0 == iCntRounds)	// in der ersten Runde auf jeden Fall nochmal machen ...
					fRepeatOpenDatabase = true;

				if (TRIASDB_E_SINGLEDATABASE_NOT_FOUND == hr && 
					(iCntRounds >= 1 || m_fPathIsConnectName)) 
				{
					if (!AskToRepairLink()) {
					// Parent und Application rücksetzen
						DB -> put_Application (NULL);
						DB -> put_Parent (NULL);
						DB.Assign(NULL);		// Datenbank wieder freigeben
						return TRIASDB_I_BROKEN_LINK;
					}
					fWasDirty = true;				// Pfad ist geändert worden
					fRepeatOpenDatabase = true;		// ... danach nur wenn gewünscht
				}
			} 
			else if (!m_fPathIsStorageName && !m_fPathIsConnectName)
				THROW_FAILED_HRESULT(put_Location (bstrName));

		} while (iCntRounds++, fRepeatOpenDatabase);

		if (S_OK != hr) {
			THROW_FAILED_HRESULT(hr);	// fataler Fehler kann nicht behoben werden

		// wenn keine Fehlerbehandlung erwünscht ist, dann mit Fehler wieder raus
			if (CONNECTMODE_OpenNoResolution == (rgMode & CONNECTMODE_OpenResolutionFlags))
				_com_issue_error(hr);

		// evtl. nochmal versuchen, diesmal aber als RO
			if (TRIASDB_S_MUSTOPENASCOPY == hr || TRIASDB_S_MUSTOPENASCOPY_SHAREVIOLATION == hr)
			{
				_ASSERTE(!m_fIsReadOnly);		// sollte nur bei schreibrechten passieren
				if (CONNECTMODE_OpenUserResolves == (rgMode & CONNECTMODE_OpenResolutionFlags))
				{
				HRESULT hrT = AskToOpenConnectionRO(hr);

					THROW_FAILED_HRESULT(hrT);
					if (S_OK != hrT)
						return hrT;		// nicht öffnen
				}

			// jetzt versuchen RO zu eröffnen
				if (m_fHasMultipleFiles) {
					hr = DB -> OpenFilesAsDatabase(m_Files, VARIANT_TRUE, 
						VARIANT_TRUE, VARIANT_FALSE, argSource);
					if (E_NOTIMPL == hr) {
					// evtl. wird nur eine Datei unterstützt, dann nehmen wir die erste
						
						if (CONNECTMODE_OpenUserResolves == (rgMode & CONNECTMODE_OpenResolutionFlags) &&
							!TellThatWeCanOpenOnlyOne (m_bstrPath))
						{
							_com_issue_error(TRIASDB_E_COULD_NOT_OPEN);
						}
						THROW_FAILED_HRESULT(DB -> OpenDatabase(m_bstrPath, 
							VARIANT_TRUE, VARIANT_TRUE, VARIANT_FALSE, argSource));
					} else
						THROW_FAILED_HRESULT(hr);
				} 
				else if (m_fPathIsStorageName) {
				WStorage Stg;

					THROW_FAILED_HRESULT(GetProjectSubStorage (true, Stg.ppi()));
					THROW_FAILED_HRESULT(DB -> OpenStorageAsDatabase (Stg, 
						VARIANT_TRUE, VARIANT_TRUE, VARIANT_FALSE, argSource));
				} 
				else {
					THROW_FAILED_HRESULT(DB -> OpenDatabase(m_bstrPath, 
						VARIANT_TRUE, VARIANT_TRUE, VARIANT_FALSE, argSource));
				}

				SetType (m_rgMode, CONNECTMODE_IsReadOnly);			// Datenquelle ist physisch schreibgeschützt
				ClearType (m_rgMode, CONNECTMODE_OpenReadWrite);	// und schreibgeschützt geöffnet
				m_fIsReadOnly = true;
			} 
		}
		m_DB = DB;		// wir sind jetzt mit dieser Datenbank verbunden ...

	// versuchen den Guid in der Datenquelle wiederzufinden, gleichzeitig Eindeutigkeit
	// des Guids im Projekt sicherstellen
	CComBSTR bstrGuid (GetPropertyFrom(WTRiASPropertyBase(DB), g_cbDataSourceGuid, g_bstrNil));
	
		THROW_FAILED_HRESULT(hr = EnsureUniqueGuid(Prj, bstrGuid));
		if (S_OK != hr || !bstrGuid || 0 == bstrGuid.Length()) {
		// wenn der Guid noch nicht existiert oder geändert wurde, dann selbigen fürs nächste mal 
		// dort wegschreiben
			SetPropertyBy (WTRiASPropertyBase(DB), g_cbDataSourceGuid, CComBSTR(m_GuidPath), true);
		} 
        else {
			m_GuidPath = CIID(bstrGuid, CIID::INITCIID_InitFromGuid);
			SetPropertyBy (WTRiASPropertyBase(DB), g_cbDataSourceGuid, CComBSTR(m_GuidPath), true);
        }

		_ASSERTE(!!m_GuidPath);
		THROW_FAILED_HRESULT(RenameConnection(CComBSTR(m_GuidPath)));
		THROW_FAILED_HRESULT(Fire_ConnectionOpened (GetConnection()));

		m_fIsDirty = fWasDirty;
	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Eindeutigkeit des Connection-Guids im aktuellen Projekt sicherstellen
HRESULT CTRiASConnection::EnsureUniqueGuid (ITRiASProject *pIPrj, CComBSTR &rbstrGuid)
{
	COM_TRY {
	WTRiASConnections Conns;

		THROW_FAILED_HRESULT(pIPrj -> get_Connections(Conns.ppi()));

	WEnumVARIANT Enum;
	CComVariant v;

		THROW_FAILED_HRESULT(Conns -> _NewEnum(Enum.ppu()));
		for (Enum -> Reset(); S_OK == Enum -> Next (1, &v, NULL); /**/) {
			_ASSERTE(V_ISDISPATCH(&v) || V_ISUNKNOWN(&v));
			THROW_FAILED_HRESULT(v.ChangeType (VT_DISPATCH));

		WTRiASConnection Conn (V_UNKNOWN(&v));
		CComBSTR bstrGuid;
		
			THROW_FAILED_HRESULT(Conn -> get_GuidPath(&bstrGuid));
			if (Conn != GetUnknown() && bstrGuid == rbstrGuid) {
			// eine andere Datenquelle hat einen identischen Guid
				_ASSERTE(Conn == WTRiASConnection(GetConnection()) || bstrGuid != rbstrGuid);	// diagnostics

			CIID NewGuid;

				rbstrGuid = NewGuid;
			}
		}

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Verbindung trennen
bool CTRiASConnection::AskToSaveNormal (LPCSTR pcName, bool &rfCommit, bool fSaving)
{
// ggf. steht schon fest, was in diesem Fall gemacht werden soll
	if (m_rgAskMode & ASKMODE_YesAllSave) {
		rfCommit = true;	// auf jeden Fall speichern
		return true;
	} else if (m_rgAskMode & ASKMODE_NoAllSave) {
		rfCommit = false;	// nicht speichern
		return true;
	}

//WTRiASProject Prj;
//CComBool fClosing (true);
//
//	if (SUCCEEDED(FindSpecificParent (GetDispatch(), Prj.ppi()))) 
//		fClosing = GetPropertyFrom (WTRiASPropertyBase(Prj), g_cbClosingProject, VARIANT_FALSE);

int iReply = IDYES;		// standardmäßig speichern

	if (/*fClosing || */!fSaving) {
	CString strText;

		strText.Format (IDS_SESSIONEND, pcName);
		_ASSERTE(strText.GetLength() > 0);

	CWnd *pWndParent = CWnd::FromHandle(GetActiveWindow());
	CMessageBoxEx mb (strText, FakeTRiASName (IDS_SESSIONENDCAP, g_cbTRiAS).c_str(), 
		true, pWndParent);
		
		iReply = mb.Show();
	} 

	switch (iReply) {
	case IDYES:
		rfCommit = true;	// auf jeden Fall speichern
		break;

	case IDC_YESALL:
		rfCommit = true;	// auf jeden Fall speichern
		m_rgAskMode |= ASKMODE_YesAllSave;
		break;

	case IDNO:
		rfCommit = false;	// nicht speichern
		break;

	case IDC_NOALL:
		rfCommit = false;	// nicht speichern
		m_rgAskMode |= ASKMODE_NoAllSave;
		break;

	case IDCANCEL:
		return false;		// abgebrochen, nicht schließen
	}
	return true;			// ok schließen
}

bool CTRiASConnection::TellThatCannotSaveDirectly (LPCSTR pcName, UINT resID, BSTR *pNewName, bool &rfSave)
{
// ggf. steht schon fest, was in diesem Fall gemacht werden soll
	if (m_rgAskMode & ASKMODE_YesAllSelectOtherName)
		return ShowSaveAsDialog (IDS_SAVEPROJECTCAP, pcName, pNewName, IDS_DBISCOPY);
	else if (m_rgAskMode & ASKMODE_NoAllSelectOtherName)
		return false;			// alle weiteren einfach übergehen

// erstmal mitteilen, daß die Datenbank nicht direkt gespeichert werden kann, und warum
CString strText;

	strText.Format(resID, pcName);
	_ASSERTE(strText.GetLength() > 0);

CWnd *pWndParent = CWnd::FromHandle(GetActiveWindow());
CMessageBoxEx mb (strText, FakeTRiASName(IDS_SAVEPROJECTCAP, g_cbTRiAS).c_str(), 
	true, pWndParent);

	switch (mb.Show()) {
	case IDYES:
		break;			// Namen abfragen

	case IDC_YESALL:
		m_rgAskMode |= ASKMODE_YesAllSelectOtherName;
		break;			// Namen abfragen

	case IDNO:
		rfSave = false;
		return true;

	case IDC_NOALL:
		m_rgAskMode |= ASKMODE_NoAllSelectOtherName;
		rfSave = false;
		return true;

	case IDCANCEL:
		return false;
	}

	rfSave = true;
	return ShowSaveAsDialog (IDS_SAVEPROJECTCAP, pcName, pNewName, IDS_DBISCOPY);
}

bool CTRiASConnection::ShowSaveAsDialog (UINT uiCap, LPCSTR pcName, BSTR *pbstrNewName, UINT uiResIDApp)
{
// jetzt einen neuen Namen abfragen
os_path path (pcName);

	{
	// neuen Namen generieren
		if (0 != uiResIDApp && path.file_path()) {
		CString strApp;

			VERIFY(strApp.LoadString(uiResIDApp));
			path.filename (os_string(path.filename().c_str() + strApp));
		} 
		else {
			USES_CONVERSION;	// ConnectionNamen verwenden
			path.filename (os_string(OLE2T(m_bstrName)));
		}

	// Extension garantieren
		if (!path.has_extension())
			path.extension (os_string(g_cbRis));
	}

// jetzt Dialog anzeigen
bool fResult = false;

	COM_TRY {
	CComBSTR bstrName (os_string(path).c_str()), bstrProgID;
	WTRiASDataServerRegEntries RegEntries (CLSID_TRiASDataServerRegEntries);
	WTRiASDataServerRegEntry RegEntry;

		THROW_FAILED_HRESULT(RetrieveProgIDFromConnectString (m_bstrConnect, &bstrProgID));
		THROW_FAILED_HRESULT(RegEntries -> FindFromServerProgID (bstrProgID, RegEntry.ppi()));
		fResult = ShowSaveAsFileDialog (uiCap, bstrName, pbstrNewName, RegEntry);

	} COM_CATCH_RETURN(false);
	return fResult;
}

bool CTRiASConnection::ShowFileBasedDialog (
	ITRiASDataServerRegEntry *pIRegEntry, UINT uiCap, BOOL fOpenDlg, BSTR bstrName, BSTR *pbstrNewName)
{
bool bResult = false;

	USES_CONVERSION;
	COM_TRY {
	CComBSTR bstrExt;
	CComBSTR bstrFilter;
		
		THROW_FAILED_HRESULT(pIRegEntry -> get_DefaultExtension (CLEARED(&bstrExt)));
		THROW_FAILED_HRESULT(pIRegEntry -> get_FilterString (CLEARED(&bstrFilter)));

	CFileDialog dlgFile (fOpenDlg, NULL, NULL, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, NULL, AfxGetMainWnd());

		if (fOpenDlg) {
			dlgFile.m_ofn.Flags &= ~OFN_HIDEREADONLY;
			dlgFile.m_ofn.Flags |= OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST;
		} else 
			dlgFile.m_ofn.Flags |= OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT;

	#if defined(OFN_ENABLESIZING)
		if (IsWin41() || (IsWinNT() && IsWin50()))		// Win98 oder WinNT50
			dlgFile.m_ofn.Flags |= OFN_ENABLESIZING;
	#endif // OFN_ENABLESIZING

	CString allFilter;

		VERIFY(allFilter.LoadString(AFX_IDS_ALLFILTER));
		bstrFilter.Append(allFilter);
		bstrFilter += L"|*.*||";	// next string please

	CString strFilter (bstrFilter);
	LPTSTR pch = strFilter.GetBuffer(0);

		while ((pch = _tcschr (pch, _T('|'))) != NULL)
			*pch++ = _T('\0');

		dlgFile.m_ofn.lpstrFilter = strFilter;
		dlgFile.m_ofn.nMaxCustFilter = 2;

	// StartPfad setzen
	os_path path (OLE2A(bstrName));
	os_string dir;

		dlgFile.m_ofn.lpstrInitialDir = NULL;
		dlgFile.m_ofn.nFilterIndex = 0;
		if (path.has_directory()) {
			if (path.has_drive()) {
				dir = path.drive();
				dir += path.drive_separator();
			}
			dir += path.directory();
			dlgFile.m_ofn.lpstrInitialDir = dir.c_str();
		}

	// Dateinamen setzen
		_ASSERTE(path.file_path());

	CString strFile (path.filename().c_str());

		dlgFile.m_ofn.lpstrFile = strFile.GetBuffer(_MAX_PATH);

	// Default extension setzen
		dlgFile.m_ofn.lpstrDefExt = OLE2A(bstrExt);

	// Caption setzen
	CString title (FakeTRiASName (uiCap, g_cbTRiAS).c_str());

		dlgFile.m_ofn.lpstrTitle = title;
		bResult = (IDOK == dlgFile.DoModal()) ? TRUE : FALSE;
		strFile.ReleaseBuffer();

		if (bResult) {
		CComBSTR bstrRes (strFile);

			*pbstrNewName = bstrRes.Detach();
		}
	} COM_CATCH_RETURN(false);
	return bResult;
} 

bool CTRiASConnection::ShowDirectoryBasedDialog (UINT uiCap, BOOL fOpenDlg, BSTR bstrName, BSTR *pbstrNewName)
{
bool bResult = false;

	USES_CONVERSION;
	COM_TRY {
	// StartPfad setzen
	os_path path (OLE2A(bstrName));
	os_string dir;
	CString strSelDir (g_cbNil);

		if (path.has_directory()) {
			if (path.has_drive()) {
				dir = path.drive();
				dir += path.drive_separator();
			}
			dir += path.directory();
			strSelDir = dir.c_str();
		}

	// Caption setzen
	CString title (FakeTRiASName (uiCap, g_cbTRiAS).c_str());
	CPathDialog dlgDir (fOpenDlg, title, NULL, (0 == strSelDir.GetLength()) ? NULL : (LPCTSTR)strSelDir, AfxGetMainWnd());

		bResult = dlgDir.DoBrowse();
		if (bResult) {
		CString strPath (dlgDir.GetPathName());

			strPath += path.path_separator();		// mit '\\' abschließen

		CComBSTR bstrRes (strPath);

			*pbstrNewName = bstrRes.Detach();
		}

	} COM_CATCH_RETURN(false);
	return bResult;
}

bool CTRiASConnection::ShowFileDialog (
	UINT uiCap, BOOL fOpenDlg, BSTR bstrName, BSTR *pbstrNewName, ITRiASDataServerRegEntry *pIRegEntry)
{
	if (NULL == pbstrNewName) return false;

bool bResult = false;

	COM_TRY {
	CComBool fFile(true), fDir;

		if (NULL != pIRegEntry) {
			THROW_FAILED_HRESULT(pIRegEntry -> get_NameIsFile (&fFile));
			THROW_FAILED_HRESULT(pIRegEntry -> get_NameIsDirectory (&fDir));
//			THROW_FAILED_HRESULT(RegEntry -> get_MultipleFiles (&fMulti));
//			THROW_FAILED_HRESULT(RegEntry -> get_NameIsStorage (&fStg));
		}

		if (fFile) 
			bResult = ShowFileBasedDialog (pIRegEntry, uiCap, fOpenDlg, bstrName, pbstrNewName);
		else if (fDir) 
			bResult = ShowDirectoryBasedDialog (uiCap, fOpenDlg, bstrName, pbstrNewName);
		else {
			_ASSERTE(SUCCEEDED(E_NOTIMPL));
		}

	} COM_CATCH_RETURN(false);
	return bResult;
}

// Fragen, ob der Originalname der Datei verwendet werden soll ----------------
bool CTRiASConnection::AskToSaveDirectly (LPCSTR pcName, bool &rfNewName, BSTR *pNewName)
{
int iReply = VMessageBox (FakeTRiASName (IDS_SAVEPROJECTCAP, g_cbTRiAS).c_str(),
		MB_TASKMODAL|MB_ICONQUESTION|MB_YESNOCANCEL, IDS_CHANGEDBYOTHERS, pcName, g_cbTRiAS);

	switch (iReply) {
	case IDYES:
		rfNewName = false;	// auf jeden Fall unter OriginalNamen speichern
		break;

	case IDNO:
		rfNewName = true;	// unter neuem Namen Speichern
		break;

	case IDCANCEL:
		return false;		// abgebrochen
	}

// wenn neuer Name benötigt wird, dann diesen hier abfragen
	if (rfNewName)
		return ShowSaveAsDialog (IDS_SAVEPROJECTCAP, pcName, pNewName);

	return true;
}

HRESULT CTRiASConnection::SaveConnectedDatabase (CONNECTMODE rgMode, bool fSaving)
{
	USES_CONVERSION;
	COM_TRY {
	// wenn Datenbank gespeichert werden muß, dann evtl. Aktionen durchführen
	CComBool fDirty;
	CComBool fUpdatable;
	CComBool fIsCopy;
	CComBool fCouldOpenTarget;

		m_DB -> get_IsDirty(&fDirty);
		m_DB -> get_Updatable(&fUpdatable);
		m_DB -> get_OpenedAsCopy(&fIsCopy);
		if (fIsCopy)
			m_DB -> get_CouldOpenTarget(&fCouldOpenTarget);

	// hier werden die Flag richtig :-) ausgewertet
	SAVEMODE rgSave = SAVEMODE_NoSave;

	LPCSTR pcName = OLE2A(m_bstrName);		// Namen der Datenquelle im UI verwenden
	CComBSTR bstrName;						// Name der DB besorgen

		THROW_FAILED_HRESULT(m_DB -> get_Name(CLEARED(&bstrName)));

	// jetzt je nach Situation entscheiden
		switch (rgMode & CONNECTMODE_CloseResolutionFlags) {
		case CONNECTMODE_CloseUserResolves:
		// speichern wenn nötig, verlangt und möglich
			if (fDirty && fUpdatable) {
			bool fCommit = false;

				if (!AskToSaveNormal (pcName, fCommit, fSaving))
					return S_FALSE;			// nicht schließen

				if (m_fIsReadOnly) {
				// SaveAs machen, da nicht auf geöffnete Datei Commit'ed werden kann
					if (fCommit) {
						if (!TellThatCannotSaveDirectly (pcName, IDS_ISREADONLY, CLEARED(&bstrName), fCommit))
							return S_FALSE;			// doch noch abgebrochen
						rgSave = fCommit ? SAVEMODE_SaveAs : SAVEMODE_NoSave;
					} else
						rgSave = SAVEMODE_NoSave;

				} else if (fIsCopy) {
				// Datei ist Kopie der OriginalDatei
					if (fCommit) {
						if (fCouldOpenTarget) {
						bool fNewName = true;		// default: neuer Name

							if (!AskToSaveDirectly (pcName, fNewName, CLEARED(&bstrName)))
								return S_FALSE;		// abgebrochen
							rgSave = fNewName ? SAVEMODE_SaveAs : SAVEMODE_NormalSave;

						} else {
							if (!TellThatCannotSaveDirectly (pcName, IDS_USEDBYOTHERS, CLEARED(&bstrName), fCommit))
								return S_FALSE;		// doch noch abgebrochen
							rgSave = fCommit ? SAVEMODE_SaveAs : SAVEMODE_NoSave;
						}
					} else
						rgSave = SAVEMODE_NoSave;

				} else {
				// Datei mit normalen Schreibrechten eröffnet
					rgSave = fCommit ? SAVEMODE_NormalSave : SAVEMODE_NoSave;
				}
			}
			break;

		case CONNECTMODE_CloseAutoResolution:
		// immer speichern, wenn nötig und möglich
			rgSave = (fDirty && fUpdatable && !fIsCopy) ? SAVEMODE_NormalSave : SAVEMODE_NoSave;
			break;

		case CONNECTMODE_CloseNoResolution:
			rgSave = SAVEMODE_NoSave;		// nie speichern
			break;
		}

	// evtl. gewünschte Speicheraktion durchführen
		switch (rgSave) {
		case SAVEMODE_NoSave:		// nothing to do
			THROW_FAILED_HRESULT(m_DB -> put_IsDirty (VARIANT_FALSE));
			break;

		case SAVEMODE_NormalSave:	// einfach alles wegschreiben
			THROW_FAILED_HRESULT(m_DB -> Save());
			break;

		case SAVEMODE_SaveAs:		// unter neuem Namen speichern
			{
			CComBool fSaveAs;

				THROW_FAILED_HRESULT(Fire_ChangingConnectedDatasource (GetDispatch(), &fSaveAs));
				if (fSaveAs)
					return S_FALSE;		// abgebrochen oder Fehler
				THROW_FAILED_HRESULT(Fire_ConnectedDatasourceToChange (GetDispatch()));

			// Datenquelle speichern unter
				THROW_FAILED_HRESULT(m_DB -> SaveAs (bstrName));
				THROW_FAILED_HRESULT(PutLocation (bstrName));	// auch RelPath neu berechnen (#HK000203)

			// #HK010115: Datenquelle ist nicht mehr physisch schreibgeschützt und nicht mehr mit
			// Schreibschutz geöffnet
				ClearType (m_rgMode, CONNECTMODE_IsReadOnly);
				SetType (m_rgMode, CONNECTMODE_OpenReadWrite);	
				
				THROW_FAILED_HRESULT(Fire_ConnectedDatasourceChanged (GetDispatch()));
			}
			break;
		}
	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASConnection::Disconnect(CONNECTMODE rgMode)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_DB.IsValid())
		return REPORT_DBERROR(TRIASDB_E_NOTCONNECTED);

	if (CONNECTMODE_UseDefaultMode == rgMode)
		rgMode = m_rgMode;

// ggf. AskMode behandeln
	if (rgMode & CONNECTMODE_ResetDisconnectAskMode) {
		ResetAskModeSave();
		ClearType (m_rgMode, CONNECTMODE_ResetDisconnectAskMode);
	}

	USES_CONVERSION;
	COM_TRY {
	// darf Connection geschlossen werden ?
	CComBool fClose;

		THROW_FAILED_HRESULT(Fire_ClosingConnection (GetConnection(), &fClose));
		if (fClose)
			return S_FALSE;		// abgebrochen oder Fehler

	HRESULT hr = SaveConnectedDatabase(rgMode, false);

		if (S_FALSE == hr) 
			return S_FALSE;		// Nutzer hat abgebrochen, Fehler ignorieren
		else {
			THROW_FAILED_HRESULT(hr);
		}

	// jetzt steht fest, daß wirklich geschlossen werden soll und kann 
	// (es wurde evtl. gespeichert)
		THROW_FAILED_HRESULT(Fire_ConnectionToClose (GetConnection()));
		THROW_FAILED_HRESULT(RenameConnection(NULL));

	// endlich das tun, was getan werden soll
		m_DB -> Close();		// Database schließen

		m_DB -> put_Application (NULL);
		m_DB -> put_Parent (NULL);
		m_DB.Assign(NULL);		// lediglich Database freigeben

		THROW_FAILED_HRESULT(Fire_ConnectionClosed (m_bstrName));

		m_fIsDirty = true;

	// alle anderen Werte für evtl. nochmaliges Connect intakt lassen
	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Datenquelle entfernen
STDMETHODIMP CTRiASConnection::Remove()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (m_DB.IsValid())
		return REPORT_DBERROR(TRIASDB_E_ALREADYCONNECTED);

	if (!m_fPathIsStorageName)
		return S_OK;		// nothing to do

	COM_TRY {
	WStorage PrjStg;
	WTRiASProject Prj;

		THROW_FAILED_HRESULT(FindSpecificParent(m_Parent, Prj.ppi()));
		THROW_FAILED_HRESULT(WOleItemContainer(Prj) -> GetObjectStorage ((LPOLESTR)g_cbObjectStgService, NULL, IID_IStorage, PrjStg.ppv()));
		THROW_FAILED_HRESULT(PrjStg -> DestroyElement (m_bstrPath));
		THROW_FAILED_HRESULT(Prj -> put_Dirty (VARIANT_TRUE));

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Speichern der angehängten Datenquelle mit allen dazu notwendigen 
// Nutzerinteraktionen (wenn gefordert)
STDMETHODIMP CTRiASConnection::SaveConnectedDatabase (CONNECTMODE rgMode)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_DB.IsValid())
		return REPORT_DBERROR(TRIASDB_E_NOTCONNECTED);

	return SaveConnectedDatabase(rgMode, false);
}

///////////////////////////////////////////////////////////////////////////////
// Speichern der angehängten Datenquelle unter einem anderen Namen mit allen dazu 
// notwendigen Nutzerinteraktionen (wenn gefordert)
STDMETHODIMP CTRiASConnection::SaveAsConnectedDatabase (CONNECTMODE rgMode)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_DB.IsValid())
		return REPORT_DBERROR(TRIASDB_E_NOTCONNECTED);

	USES_CONVERSION;
	COM_TRY {
	LPCSTR pcName = OLE2A(m_bstrName);		// Namen der Datenquelle im UI verwenden
	CComBSTR bstrNewName;

		if (!ShowSaveAsDialog (IDS_SAVEPROJECTCAP, pcName, &bstrNewName, IDS_DBISCOPY)) 
			return E_ABORT;

	CComBool fSaveAs;

		THROW_FAILED_HRESULT(Fire_ChangingConnectedDatasource (GetDispatch(), &fSaveAs));
		if (fSaveAs)
			return S_FALSE;		// abgebrochen oder Fehler
		THROW_FAILED_HRESULT(Fire_ConnectedDatasourceToChange (GetDispatch()));

	// Datenquelle speichern unter
	CWaitCursor wait;

		THROW_FAILED_HRESULT(m_DB -> SaveAs (bstrNewName));
		THROW_FAILED_HRESULT(PutLocation (bstrNewName));	// auch RelPath neu berechnen (#HK000203)

	// #HK010115: Datenquelle ist nicht mehr physisch schreibgeschützt und nicht mehr mit
	// Schreibschutz geöffnet
		ClearType (m_rgMode, CONNECTMODE_IsReadOnly);
		SetType (m_rgMode, CONNECTMODE_OpenReadWrite);	
		
		THROW_FAILED_HRESULT(Fire_ConnectedDatasourceChanged (GetDispatch()));

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Events verschicken
HRESULT CTRiASConnection::Fire_OpeningConnection (BSTR Name, VARIANT_BOOL *pVal)
{
	_ASSERTE(m_Parent);
	if (!m_Parent) return E_POINTER;

WTRiASConnectionEvents Events;

	if (SUCCEEDED(m_Parent -> QueryInterface (Events.ppi())))
		return Events -> OpeningConnection (Name, pVal);
	return S_OK;
}

HRESULT CTRiASConnection::Fire_ConnectionToOpen (BSTR Name)
{
	_ASSERTE(m_Parent);
	if (!m_Parent) return E_POINTER;

WTRiASConnectionEvents Events;

	if (SUCCEEDED(m_Parent -> QueryInterface (Events.ppi())))
		return Events -> ConnectionToOpen (Name);
	return S_OK;
}

HRESULT CTRiASConnection::Fire_ConnectionOpened (IDispatch * pIConn)
{
	_ASSERTE(m_Parent);
	if (!m_Parent) return E_POINTER;

WTRiASConnectionEvents Events;

	if (SUCCEEDED(m_Parent -> QueryInterface (Events.ppi())))
		return Events -> ConnectionOpened (pIConn);
	return S_OK;
}

HRESULT CTRiASConnection::Fire_ClosingConnection (IDispatch *pIConn, VARIANT_BOOL * pVal)
{
	_ASSERTE(m_Parent);
	if (!m_Parent) return E_POINTER;

WTRiASConnectionEvents Events;

	if (SUCCEEDED(m_Parent -> QueryInterface (Events.ppi())))
		return Events -> ClosingConnection (pIConn, pVal);
	return S_OK;
}

HRESULT CTRiASConnection::Fire_ConnectionToClose (IDispatch * pIConn)
{
	_ASSERTE(m_Parent);
	if (!m_Parent) return E_POINTER;

WTRiASConnectionEvents Events;

	if (SUCCEEDED(m_Parent -> QueryInterface (Events.ppi())))
		return Events -> ConnectionToClose (pIConn);
	return S_OK;
}

HRESULT CTRiASConnection::Fire_ConnectionClosed(BSTR Name)
{
	_ASSERTE(m_Parent);
	if (!m_Parent) return E_POINTER;

WTRiASConnectionEvents Events;

	if (SUCCEEDED(m_Parent -> QueryInterface (Events.ppi())))
		return Events -> ConnectionClosed (Name);
	return S_OK;
}

HRESULT CTRiASConnection::Fire_RenamingConnection(BSTR OldName, BSTR NewName, VARIANT_BOOL * pVal)
{
	_ASSERTE(m_Parent);
	if (!m_Parent) return E_POINTER;

WTRiASConnectionEvents Events;

	if (SUCCEEDED(m_Parent -> QueryInterface (Events.ppi())))
		return Events -> RenamingConnection (OldName, NewName, pVal);
	return S_OK;
}

HRESULT CTRiASConnection::Fire_ConnectionToRename(BSTR OldName, BSTR NewName)
{
	_ASSERTE(m_Parent);
	if (!m_Parent) return E_POINTER;

WTRiASConnectionEvents Events;

	if (SUCCEEDED(m_Parent -> QueryInterface (Events.ppi())))
		return Events -> ConnectionToRename (OldName, NewName);
	return S_OK;
}

HRESULT CTRiASConnection::Fire_ConnectionRenamed(IDispatch *pIConn)
{
	_ASSERTE(m_Parent);
	if (!m_Parent) return E_POINTER;

WTRiASConnectionEvents Events;

	if (SUCCEEDED(m_Parent -> QueryInterface (Events.ppi())))
		return Events -> ConnectionRenamed (pIConn);
	return S_OK;
}

HRESULT CTRiASConnection::Fire_ChangingConnectedDatasource (IDispatch *pIConn, VARIANT_BOOL *pVal)
{
	_ASSERTE(m_Parent);
	if (!m_Parent) return E_POINTER;

WTRiASConnectionEvents Events;

	if (SUCCEEDED(m_Parent -> QueryInterface (Events.ppi())))
		return Events -> ChangingConnectedDatasource (pIConn, pVal);
	return S_OK;
}

HRESULT CTRiASConnection::Fire_ConnectedDatasourceToChange (IDispatch *pIConn)
{
	_ASSERTE(m_Parent);
	if (!m_Parent) return E_POINTER;

WTRiASConnectionEvents Events;

	if (SUCCEEDED(m_Parent -> QueryInterface (Events.ppi())))
		return Events -> ConnectedDatasourceToChange (pIConn);
	return S_OK;
}

HRESULT CTRiASConnection::Fire_ConnectedDatasourceChanged (IDispatch *pIConn)
{
	_ASSERTE(m_Parent);
	if (!m_Parent) return E_POINTER;

WTRiASConnectionEvents Events;

	if (SUCCEEDED(m_Parent -> QueryInterface (Events.ppi())))
		return Events -> ConnectedDatasourceChanged (pIConn);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// IOleClientSite
STDMETHODIMP CTRiASConnection::SaveObject()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ATLTRACENOTIMPL("CTRiASConnection::SaveObject");
}

STDMETHODIMP CTRiASConnection::GetMoniker (
	DWORD dwAssign, DWORD dwWhichMoniker, IMoniker **ppmk)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_DB && !m_fIsInitializing)
		return TRIASDB_E_NOTCONNECTED;

	if (NULL == ppmk) return E_POINTER;
	*ppmk = NULL;

	switch (dwWhichMoniker) {
    case OLEWHICHMK_CONTAINER:
		return GetContainerMoniker (ppmk);

	case OLEWHICHMK_OBJREL:
    case OLEWHICHMK_OBJFULL:
		return GetThisMoniker (dwWhichMoniker, ppmk);
	
	default:
		break;
	}
	return (NULL == *ppmk) ? E_FAIL : S_OK;
}

STDMETHODIMP CTRiASConnection::GetContainer (IOleContainer **ppContainer)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ATLTRACENOTIMPL("CTRiASConnection::GetContainer");
}

STDMETHODIMP CTRiASConnection::ShowObject()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ATLTRACENOTIMPL("CTRiASConnection::ShowObject");
}

STDMETHODIMP CTRiASConnection::OnShowWindow (BOOL fShow)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ATLTRACENOTIMPL("CTRiASConnection::OnShowWindow");
}

STDMETHODIMP CTRiASConnection::RequestNewObjectLayout()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ATLTRACENOTIMPL("CTRiASConnection::RequestNewObjectLayout");
}

///////////////////////////////////////////////////////////////////////////////
// liefert vollständigen DisplayName dieses Objektes

HRESULT CTRiASConnection::GetMkName (BSTR *pbstrMkName)
{
	COM_TRY {
	// dem aggregierenden Objekt die Chance geben, den Moniker zu berechnen
	WMoniker mk;

		THROW_FAILED_HRESULT(MkGetMoniker (GetControllingUnknown(), OLEGETMONIKER_ONLYIFTHERE, OLEWHICHMK_OBJFULL, mk.ppi()));
		THROW_FAILED_HRESULT(MkGetDisplayName (mk, pbstrMkName));

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Moniker des zugeordneten Containers liefern
HRESULT CTRiASConnection::GetContainerMoniker (IMoniker **ppIMk)
{
	COM_TRY {
	WTRiASProject Parent;
	WMoniker mk;

		THROW_FAILED_HRESULT(FindSpecificParent(m_Parent, Parent.ppi()));
		THROW_FAILED_HRESULT(MkGetMoniker (Parent, OLEGETMONIKER_ONLYIFTHERE, OLEWHICHMK_OBJFULL, mk.ppi()));
		*ppIMk = mk.detach();

	} COM_CATCH;
	return S_OK;
}

// Den vollständigen Moniker dieses Objektes liefern
HRESULT CTRiASConnection::GetThisMoniker (DWORD dwWhich, IMoniker **ppIMk)
{
	COM_TRY {
		switch (dwWhich) {
		case OLEWHICHMK_OBJFULL:
			if (m_fPathIsStorageName) {
			// dieser Moniker dient zum Binden über das übergeordnete Projekt (nur für
			// lokal im Projekt gespeicherte Datenquellen)
			WMoniker mk, mkThis, mkItem;

				THROW_FAILED_HRESULT(GetContainerMoniker (mk.ppi()));
				THROW_FAILED_HRESULT(CreateConnectionMoniker (g_cbMkDel, m_GuidPath, mkThis.ppi()));
				THROW_FAILED_HRESULT(mk -> ComposeWith (mkThis, FALSE, mkItem.ppi()));
				*ppIMk = mkItem.detach();
				break;
			}
		// ... hier durchfallen

		case OLEWHICHMK_OBJREL:
		// !MkConnection:<GuidPath>
			THROW_FAILED_HRESULT(CreateConnectionMoniker (g_cbMkDel, m_GuidPath, ppIMk));
			break;

		default:
		case OLEWHICHMK_CONTAINER:
			return E_INVALIDARG;
		}

	} COM_CATCH;
	return S_OK;
}

// Den vollständigen Moniker dieses Objektes liefern (altes Format)
HRESULT CTRiASConnection::GetOldThisMoniker (DWORD dwWhich, IMoniker **ppIMk)
{
	COM_TRY {
		switch (dwWhich) {
		case OLEWHICHMK_OBJREL:
			{
			// !MkConnection!<GuidPath>
			WMoniker mkItem, mkGuid, mk;

				THROW_FAILED_HRESULT(CreateItemMoniker (g_cbMkDel, CComBSTR(g_cbMkConnection), mkItem.ppi()));
				THROW_FAILED_HRESULT(CreateItemMoniker (g_cbMkDel, CComBSTR(m_GuidPath), mkGuid.ppi()));
				THROW_FAILED_HRESULT(mkItem -> ComposeWith (mkGuid, FALSE, mk.ppi()));
				*ppIMk = mk.detach();
			}
			break;

		default:
		case OLEWHICHMK_OBJFULL:	// snh
		case OLEWHICHMK_CONTAINER:
			return E_INVALIDARG;
		}
	} COM_CATCH;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// PropertySupport
// Callback-interface, welches für die Konkretheit der Properties zuständig ist

STDMETHODIMP CTRiASConnection::CreateProperty (BSTR Name, ITRiASProperty **Property)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == Property)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASConnection::CreateProperty");

	COM_TRY {
	// Events vorher
	CComBool fVal;
		
		THROW_FAILED_HRESULT(Fire_CreatingProperty (Name, &fVal)); 
		if (fVal)
			return S_FALSE;
		THROW_FAILED_HRESULT(Fire_PropertyToCreate (Name));

	// eigentliche Aktion
	CComObject<CTRiASProperty> *pNew = NULL;

		THROW_FAILED_HRESULT(CComObject<CTRiASProperty>::CreateInstance (&pNew));

	WTRiASProperty Prop (pNew);		// required AddRef;
	WTRiASPropertyCallback Supp;

		THROW_FAILED_HRESULT(pNew -> put_Name (Name));
		THROW_FAILED_HRESULT(GetPropertySupportSite (Name, GetUnknown(), NULL, Supp.ppi()));
		THROW_FAILED_HRESULT(pNew -> SetSite (Supp));	// using IObjectWithSite
		*Property = Prop.detach();

	// Events hinterher
		THROW_FAILED_HRESULT(Fire_PropertyCreated (*Property));
	} COM_CATCH;
	
	return S_OK;
}

// Einlesen aller Eigenschaften der Connection und aller lokaler Props des
// Objektes.
STDMETHODIMP CTRiASConnection::RemoveProperty (BSTR Name)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == Name)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASConnection::RemoveProperty");

// evtl. abschließende Leerzeichen abschneiden
CComBSTR bstrName (TrimRight (Name));

// Events vorher
CComBool fVal;
	
	RETURN_FAILED_HRESULT(Fire_DeletingProperty (bstrName, &fVal)); 
	if (fVal)
		return S_FALSE;
	RETURN_FAILED_HRESULT(Fire_PropertyToDelete (bstrName));

// eigentliche Aktion
HRESULT hr = S_OK;

	if (S_OK == PropertyIsPredefined (bstrName)) {
	// nur bei vordefinierten Properties (nicht bei dynamisch erzeugten)
		RETURN_FAILED_HRESULT(hr = ReleasePropertySupportSite (bstrName));	// zuständiges Objekt freigeben
	}

// Event hinterher
	if (S_OK == hr) {
		m_fIsDirty = true;
		RETURN_FAILED_HRESULT(Fire_PropertyDeleted (bstrName));
	}
	return hr;		// S_FALSE heißt: nicht gefunden
}

// Properties wurden neu eingelesen
HRESULT CTRiASConnection::PropertiesRefreshed() 
{
// Ausgabe-Koordinatensystem vom Projekt holen
	if (NULL != m_Parent.p) {
		COM_TRY {
		WTRiASProject Prj;

			THROW_FAILED_HRESULT(FindSpecificParent (GetDispatch(), Prj.ppi()));
		
		WTRiASCS CS (GetPropertyFrom (WTRiASPropertyBase(Prj), g_cbTRiASCSService, (IDispatch *)NULL), false);

			if (CS.IsValid()) {
				THROW_FAILED_HRESULT(SetProperty (GetProperties(), g_cbTRiASCSService, CComVariant(CS), true));
			}

		} COM_CATCH;
	}
	return S_OK; 
}

///////////////////////////////////////////////////////////////////////////////
// ITRiASPropertyEvents
STDMETHODIMP CTRiASConnection::CreatingProperty (BSTR Name, VARIANT_BOOL *pVal)
{
	return Fire_CreatingProperty (Name, pVal);
}

STDMETHODIMP CTRiASConnection::PropertyToCreate (BSTR Name)
{
	return Fire_PropertyToCreate (Name);
}

STDMETHODIMP CTRiASConnection::PropertyCreated (IDispatch *pIProp)
{
	m_fIsDirty = true;
	return Fire_PropertyCreated (pIProp);
}

STDMETHODIMP CTRiASConnection::ModifyingProperty (BSTR Name, VARIANT_BOOL *pVal)
{
	return Fire_ModifyingProperty (Name, pVal);
}

STDMETHODIMP CTRiASConnection::PropertyToModify (BSTR Name)
{
	return Fire_PropertyToModify (Name);
}

STDMETHODIMP CTRiASConnection::PropertyModified (BSTR Name)
{
	m_fIsDirty = true;
	return Fire_PropertyModified (Name);
}

STDMETHODIMP CTRiASConnection::DeletingProperty (BSTR Name, VARIANT_BOOL *pVal)
{
	return Fire_DeletingProperty (Name, pVal);
}

STDMETHODIMP CTRiASConnection::PropertyToDelete (BSTR Name)
{
	return Fire_PropertyToDelete (Name);
}

STDMETHODIMP CTRiASConnection::PropertyDeleted (BSTR Name)
{
	m_fIsDirty = true;
	return Fire_PropertyDeleted (Name);
}

///////////////////////////////////////////////////////////////////////////////
// Connection-Moniker
// Hier wird der Guid der Connection zusammen mit dem zugehörigen WildCard-Moniker 
// mit der _Datenban_ registriert. Alle Anfragen gehen also dorthin.
// Aus diesem Grund muß die Connection selbst keinen Support für IOleItemContainer
// enthalten.
HRESULT CTRiASConnection::RenameConnection (BSTR bstrName)
{
	RenamingConnection();
	if (NULL == bstrName) return S_OK;

	USES_CONVERSION;

FILETIME ft;

	RETURN_FAILED_HRESULT(CoFileTimeNow (&ft));

WMoniker mkThis;

	RETURN_FAILED_HRESULT(GetThisMoniker (OLEWHICHMK_OBJREL, mkThis.ppi()));

WMoniker mkPid, mk;

	RETURN_FAILED_HRESULT(CreatePIDMoniker (mkPid.ppi()));
	RETURN_FAILED_HRESULT(mkPid -> ComposeWith (mkThis, FALSE, mk.ppi()));

	RETURN_FAILED_HRESULT(MkRegisterAsRunning (ROTFLAGS_REGISTRATIONKEEPSALIVE, 
		m_DB, mk, &m_dwRegROT)); 
	RETURN_FAILED_HRESULT(MkNoteChangeTime (m_dwRegROT, &ft));

#if defined(_REGISTER_WILDCARD_MONIKERS)
WMoniker mkAll;

	if (SUCCEEDED(CreateItemMoniker(g_cbMkDel, g_cbMkWild, mkAll.ppi()))) {
	WMoniker mkWild;
	HRESULT hr = mk -> ComposeWith (mkAll, FALSE, mkWild.ppi());

		if (SUCCEEDED(hr)) 
			hr = MkRegisterAsRunning(0, m_DB, mkWild, &m_dwRegROTAll);
		if (SUCCEEDED(hr))
			MkNoteChangeTime (m_dwRegROTAll, &ft);
	}
#endif // _REGISTER_WILDCARD_MONIKERS

// u.U. alte Moniker registrieren
	if (m_fUseOldMks) {
		RETURN_FAILED_HRESULT(GetOldThisMoniker (OLEWHICHMK_OBJREL, mk.ppi()));
		RETURN_FAILED_HRESULT(MkRegisterAsRunning (ROTFLAGS_REGISTRATIONKEEPSALIVE, 
			m_DB, mk, &m_dwOldRegROT)); 
		RETURN_FAILED_HRESULT(MkNoteChangeTime (m_dwOldRegROT, &ft));

#if defined(_REGISTER_WILDCARD_MONIKERS)
		if (SUCCEEDED(CreateItemMoniker(g_cbMkDel, g_cbMkWild, mkAll.ppi()))) {
		WMoniker mkWild;
		HRESULT hr = mk -> ComposeWith (mkAll, false, mkWild.ppi());

			if (SUCCEEDED(hr)) 
				hr = MkRegisterAsRunning(0, m_DB, mkWild, &m_dwOldRegROTAll);
			if (SUCCEEDED(hr))
				MkNoteChangeTime (m_dwOldRegROTAll, &ft);
		}
#endif // _REGISTER_WILDCARD_MONIKERS
	}
	return S_OK;
}

// Connection soll umbenannt werden
HRESULT CTRiASConnection::RenamingConnection (void)
{
	MkRevokeAsRunning (&m_dwRegROT);
	MkRevokeAsRunning (&m_dwOldRegROT);

#if defined(_REGISTER_WILDCARD_MONIKERS)
	MkRevokeAsRunning (&m_dwRegROTAll);
	MkRevokeAsRunning (&m_dwOldRegROTAll);
#endif // _REGISTER_WILDCARD_MONIKERS
	return S_OK;
}

// IPersistStorage: wird lediglich für Storagebasierte DB's verwendet um diese zu speichern etc.
STDMETHODIMP CTRiASConnection::InitNew (IStorage *pIStg)
{
	_ASSERTE(m_fPathIsStorageName);
	return S_OK;
}

STDMETHODIMP CTRiASConnection::Load (IStorage *pIStg)
{
	_ASSERTE(m_fPathIsStorageName);
	return S_OK;
}

STDMETHODIMP CTRiASConnection::Save (IStorage *pIStg, BOOL fSameAsLoad)
{
	_ASSERTE(m_fPathIsStorageName);
	_ASSERTE(m_DB.IsValid());
	if (!m_DB && !m_fIsInitializing) {
		RETURN_FAILED_HRESULT(TRIASDB_E_NOTCONNECTED);
	}

	COM_TRY {
	WStorage Stg;

		THROW_FAILED_HRESULT(GetSubStorage (pIStg, m_bstrPath, CLSID_DirisProject, Stg.ppi()));
		THROW_FAILED_HRESULT(WPersistStorage(m_DB) -> Save (Stg, fSameAsLoad));		// eigene DatenBank speichern
		
	DWORD rgStgc = STGC_DEFAULT;
		
		if (IsWin50() && IsWinNT()) rgStgc |= STGC_CONSOLIDATE;
		THROW_FAILED_HRESULT(Stg -> Commit (rgStgc));

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASConnection::SaveCompleted (IStorage *pIStg)
{
	_ASSERTE(m_fPathIsStorageName);
	_ASSERTE(m_DB.IsValid());
	if (!m_DB && !m_fIsInitializing) {
		RETURN_FAILED_HRESULT(TRIASDB_E_NOTCONNECTED);
	}

	COM_TRY {
	WStorage Stg;

		THROW_FAILED_HRESULT(GetSubStorage (pIStg, m_bstrPath, CLSID_DirisProject, Stg.ppi()));
		THROW_FAILED_HRESULT(WPersistStorage(m_DB) -> SaveCompleted (Stg));		// eigene DatenBank speichern

	DWORD rgStgc = STGC_DEFAULT;
		
		if (IsWin50() && IsWinNT()) rgStgc |= STGC_CONSOLIDATE;
		THROW_FAILED_HRESULT(Stg -> Commit (rgStgc));

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASConnection::HandsOffStorage (void)
{
	_ASSERTE(m_fPathIsStorageName);
	_ASSERTE(m_DB.IsValid());

	if (!m_DB && !m_fIsInitializing) {
		RETURN_FAILED_HRESULT(TRIASDB_E_NOTCONNECTED);
	}

	COM_TRY {
		THROW_FAILED_HRESULT(WPersistStorage(m_DB) -> HandsOffStorage());		// eigene DatenBank speichern
	} COM_CATCH;
	return S_OK;
}


