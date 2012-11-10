// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 02.07.2000 14:01:21
//
// @doc
// @module TRiASCoordSystem.cpp | Implementation of the <c CTRiASCoordSystem> class

#include "stdafx.h"

#include <SHFolder.h>
#include <Com/ComBool.h>
#include <Com/SummaryProp.h>

#include <ospace/file/path.h>

#include "TRiASCsImpl.h"
#include "TRiASCoordSystem.h"
#include "CompareCoordSystems.h"

#include "EPSGMgr.h"
#include "Strings.h"

#define LANGUAGE_0x0407
#include "TRiASCs.rcv"

#if defined(_DEBUG)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

///////////////////////////////////////////////////////////////////////////////
// globale Daten
bool g_fEsnecil = false;	// Standard: nicht lizensiert

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TRiASCSUIHelper);
DefineSmartInterface(PropertyStorage);
DefineSmartInterface(PropertySetStorage);
DefineSmartInterface(LockBytes);

///////////////////////////////////////////////////////////////////////////////
// 
HRESULT	CTRiASCoordSystem::FinalConstruct() 
{
	COM_TRY {
		m_pGeographicCS = WTRiASCSGCS(CLSID_TRiASCSGCS);
		m_pProjectedCS = WTRiASCSPCS(CLSID_TRiASCSPCS);
		m_pDTrans = WTRiASCSDatumTransformation(CLSID_TRiASCSDatumTransformation);
		RETURN_FAILED_HRESULT(InternalInitialize());
#if defined(_USE_GM_CS)
		try {
			m_gmCS = WIGMCoordSystem(CLSID_CoordSystem);
		} catch (...) {
			m_gmCS = NULL;
		}
#endif
	} COM_CATCH;
	return S_OK;
}

void CTRiASCoordSystem::FinalRelease() 
{
}

/////////////////////////////////////////////////////////////////////////////
// CTRiASCoordSystem
STDMETHODIMP CTRiASCoordSystem::get_CoordSystemType(TRIASCSTYPE * pVal) 
{
	CHECKOUTPOINTER(pVal);
	*pVal = m_csType;
	return S_OK;
}

STDMETHODIMP CTRiASCoordSystem::put_CoordSystemType(TRIASCSTYPE newVal) 
{
	CSTRACE1(_T("    @@@ CTRiASCoordSystem::put_CoordSystemType: %d\n"), newVal);
	switch (newVal) {
		case tcsCS_Undefined :
		case tcsCS_Projected :
		case tcsCS_Geographic :
	//	case tcsCS_Geocentric :
			m_csType = newVal;
			break;

		default:
			MAKE_ERROR(CS_E_INVALIDCOORDSYSTEMTYPE);
	}
	return S_OK;
}

STDMETHODIMP CTRiASCoordSystem::get_GUID(BSTR * pVal) 
{
	CHECKOUTPOINTER(pVal);
	COM_TRY {
		CComBSTR	strGUID(m_guid);
		*pVal = strGUID.Detach();
	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASCoordSystem::put_GUID(BSTR pVal) 
{
	COM_TRY {
		USES_CONVERSION;
		CSTRACE1(_T("    @@@ CTRiASCoordSystem::put_GUID: %s\n"), OLE2A(pVal));

	GUID guid;

		ERROR_FAILED_HRESULT(CLSIDFromString(pVal, &guid), E_FAIL);
		ERROR_EXPR_TRUE(InlineIsEqualGUID(guid, CLSID_NULL), E_FAIL);
		m_guid = guid;
	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASCoordSystem::ChangeGUID() 
{
	if (!SUCCEEDED(::CoCreateGuid(&m_guid)))
		return E_FAIL;
	return S_OK;
}

STDMETHODIMP CTRiASCoordSystem::get_GeographicCS(ITRiASCSGCS **GCS) 
{
	CHECKOUTPOINTER(GCS);
	COM_TRY {
		_ASSERTE(m_pGeographicCS.IsValid());
		*GCS = m_pGeographicCS;
		if (*GCS)
			(*GCS)->AddRef();
	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASCoordSystem::get_ProjectedCS(ITRiASCSPCS **PCS) 
{
	CHECKOUTPOINTER(PCS);
	COM_TRY {
		_ASSERTE(m_pProjectedCS.IsValid());
		*PCS = m_pProjectedCS;
		if (*PCS)
			(*PCS)->AddRef();
	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASCoordSystem::get_DatumTransformation(ITRiASCSDatumTransformation **pVal) 
{
	CHECKOUTPOINTER(pVal);
	COM_TRY {
		_ASSERTE(m_pDTrans.IsValid());
		*pVal = m_pDTrans;
		if (*pVal)
			(*pVal)->AddRef();
	} COM_CATCH;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistStreamInit

HRESULT CTRiASCoordSystem::LoadData(IStream * pStream, DWORD dwVersion) 
{
	CHECKINPOINTER(pStream);
	COM_TRY {
		THROW_FAILED_HRESULT(LoadItem(pStream, m_guid));
		THROW_FAILED_HRESULT(LoadItem(pStream, m_csType));

		if (dwVersion >= CS_WITH_DESCRIPTION)
		{
			THROW_FAILED_HRESULT(LoadItem(pStream, m_strCategory));
			THROW_FAILED_HRESULT(LoadItem(pStream, m_strDescription));
		}

		THROW_FAILED_HRESULT(LoadItem(pStream, IID_ITRiASCSGCS, m_pGeographicCS.ppu()));
		THROW_FAILED_HRESULT(LoadItem(pStream, IID_ITRiASCSPCS, m_pProjectedCS.ppu()));
		THROW_FAILED_HRESULT(LoadItem(pStream, IID_ITRiASCSDatumTransformation, m_pDTrans.ppu()));
		
		if (dwVersion >= CS_WITH_NAME)
		{
			THROW_FAILED_HRESULT(LoadItem(pStream, m_bstrName));
		}

	} COM_CATCH;
	return S_OK;
}

HRESULT CTRiASCoordSystem::SaveData(IStream *pStream, BOOL bClearDirty) 
{
	CHECKINPOINTER(pStream);
	COM_TRY {
#if defined(_DEBUG)
		ULARGE_INTEGER pos0;
		LARGE_INTEGER off;

			off.QuadPart = 0;

		pStream->Seek(off, STREAM_SEEK_CUR, &pos0);
#endif / defined(_DEBUG)

		THROW_FAILED_HRESULT(SaveItem(pStream, m_guid));
		THROW_FAILED_HRESULT(SaveItem(pStream, m_csType));
	
	// CS_WITH_DESCRIPTION 
		THROW_FAILED_HRESULT(SaveItem(pStream, m_strCategory));
		THROW_FAILED_HRESULT(SaveItem(pStream, m_strDescription));
		THROW_FAILED_HRESULT(SaveItem(pStream, WPersistStream(m_pGeographicCS)));
		THROW_FAILED_HRESULT(SaveItem(pStream, WPersistStream(m_pProjectedCS)));
		THROW_FAILED_HRESULT(SaveItem(pStream, WPersistStream(m_pDTrans)));
	
	// CS_WITH_NAME
		THROW_FAILED_HRESULT(SaveItem(pStream, m_bstrName));

#if defined(_DEBUG)
	ULARGE_INTEGER	pos1;

		pStream->Seek(off, STREAM_SEEK_CUR, &pos1);

	DWORDLONG sizeOfObject = GetDataSize() + 3 * sizeof(GUID);

		_ASSERTE((pos1.QuadPart - pos0.QuadPart) == sizeOfObject);
#endif  // defined(_DEBUG)
	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// PropertySet speichern
HRESULT CTRiASCoordSystem::SavePropertySet(IStorage *pIStg, DWORD rgMode) 
{ 
	USES_CONVERSION;
	COM_TRY {
	// Mode richten
		rgMode &= ~(STGM_SHARE_DENY_NONE|STGM_SHARE_DENY_READ|STGM_SHARE_DENY_WRITE);
		rgMode |= STGM_SHARE_EXCLUSIVE;

	// PropertySet neu erzeugen
	WPropertySetStorage PropSet (pIStg);

		{
		WPropertyStorage PropStg;

			THROW_FAILED_HRESULT(PropSet -> Create(FMTID_SummaryInformation, NULL,
				PROPSETFLAG_DEFAULT, rgMode | STGM_CREATE, PropStg.ppi()));

		// Title schreiben
		CComBSTR bstrFullName(m_strCategory);

			bstrFullName.Append(L", ");
			bstrFullName.AppendBSTR(m_strDescription);

		CSummaryProp vTitle (PIDSI_TITLE, OLE2A(bstrFullName));

			THROW_FAILED_HRESULT(vTitle.WriteToPropertyStorage(PropStg));

		// Betreff
//		CComBSTR bstrSubject;
//
//			bstrSubject.LoadString(IDS_SUMMINFO_SUBJECT);
//
//		CSummaryProp vSubject (PIDSI_SUBJECT, OLE2A(bstrSubject));
//
//			THROW_FAILED_HRESULT(vSubject.WriteToPropertyStorage(PropStg));

		// Erzeugt von
		CSummaryProp vAuthor (PIDSI_AUTHOR, VER_COMPANYNAME_STR);

			THROW_FAILED_HRESULT(vAuthor.WriteToPropertyStorage(PropStg));

		// alles wegschreiben
			THROW_FAILED_HRESULT(PropStg -> Commit(STGC_DEFAULT));
		}

	} COM_CATCH;
	return S_OK; 
}

namespace getsizemax {
	inline __int64 GetSizeMax (IPersistStreamInit *pPS)
	{
	ULARGE_INTEGER uliSize;

		if (SUCCEEDED(pPS -> GetSizeMax(&uliSize)))
			return uliSize.QuadPart;
		return 0;
	}
}

LONGLONG CTRiASCoordSystem::GetDataSize() 
{
ULARGE_INTEGER uliSum;

	COM_TRY {
		uliSum.QuadPart = getsizemax::GetSizeMax (WPersistStreamInit(m_pGeographicCS));
		uliSum.QuadPart += getsizemax::GetSizeMax (WPersistStreamInit(m_pProjectedCS));
		uliSum.QuadPart += getsizemax::GetSizeMax (WPersistStreamInit(m_pDTrans));
	} COM_CATCH_RETURN(0);
	return sizeof(m_guid) + sizeof(m_csType) + SIZEOF(m_strCategory) + 
		SIZEOF(m_strDescription) + SIZEOF(m_bstrName) + uliSum.QuadPart;
}

HRESULT CTRiASCoordSystem::OnInitNew() 
{
	COM_TRY {
		THROW_FAILED_HRESULT(InternalInitialize());
		THROW_FAILED_HRESULT(WPersistStreamInit(m_pGeographicCS)->InitNew());
		THROW_FAILED_HRESULT(WPersistStreamInit(m_pProjectedCS)->InitNew());
		THROW_FAILED_HRESULT(WPersistStreamInit(m_pDTrans)->InitNew());
	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// ITRiASCSTransformData

STDMETHODIMP CTRiASCoordSystem::IsValid() 
{
	COM_TRY {
		ERROR_EXPR_TRUE(tcsCS_Undefined == m_csType, CS_E_INVALIDCOORDSYSTEMTYPE);
		ERROR_FAILED_HRESULT(WTRiASCSValidate(m_pGeographicCS)->IsValid(), CS_E_INVALIDGEOGRAPHICSYSTEM);
		if (tcsCS_Projected == m_csType)
		{
			ERROR_FAILED_HRESULT(WTRiASCSValidate(m_pProjectedCS)->IsValid(), CS_E_INVALIDPROJECTEDSYSTEM);
		}
		ERROR_FAILED_HRESULT(WTRiASCSValidate(m_pDTrans)->IsValid(), CS_E_INVALIDDATUMTRANSFORMATION);

	// im Moment kennen wir noch nicht alles... also überprüfen ob das System insgesamt
	// zulässig ist
//		CSPROPERTIES p;
//		p.m_CS = m_csType;
//		m_pGeographicCS->get_GeodeticDatum( &p.m_GD );
//		m_pGeographicCS->get_Ellipsoid( &p.m_EL );
//		m_pProjectedCS->get_ProjectionAlgorithm( &p.m_PA );
//		ERROR_EXPR_FALSE( _EM.IsCSKnown( p ), CS_E_UNKNOWNCOORDSYSTEM )
	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASCoordSystem::Recompute() 
{
	COM_TRY {
	CComBool bCannotChange;
	
		ERROR_FAILED_HRESULT(IsValid(), CS_E_INVALIDCOORDSYSTEM);
		RETURN_FAILED_HRESULT(Fire_ChangingCS(this, &bCannotChange));
		if (bCannotChange)
			return S_FALSE;

		RETURN_FAILED_HRESULT(Fire_CSToChange(this));
		ERROR_FAILED_HRESULT(RecomputeTransformation(NULL), CS_E_INVALIDCOORDSYSTEM);
		RETURN_FAILED_HRESULT(Fire_CSChanged(this));
	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASCoordSystem::RecomputeTransformation(ITRiASCSGCS *pGCS) 
{
	ERROR_EXPR_FALSE(NULL == pGCS, TCS_E_COMMON); // muß NULL im CS sein
	COM_TRY {
#if defined(_USE_GM_CS)
		if (!m_gmCS)
#endif // defined(_USE_GM_CS)
		{
		// kein Geomedia; wir machen alles selbst...
			ERROR_FAILED_HRESULT(WTRiASCSValidate(m_pGeographicCS)->IsValid(), CS_E_INVALIDGEOGRAPHICSYSTEM);
			ERROR_FAILED_HRESULT(WTRiASCSValidate(m_pGeographicCS)->RecomputeTransformation(m_pGeographicCS), CS_E_INVALIDGEOGRAPHICSYSTEM);
			if (tcsCS_Projected == m_csType)
			{
				ERROR_FAILED_HRESULT(WTRiASCSValidate(m_pProjectedCS)->IsValid(), CS_E_INVALIDPROJECTEDSYSTEM);
				ERROR_FAILED_HRESULT(WTRiASCSValidate(m_pProjectedCS)->RecomputeTransformation(m_pGeographicCS), CS_E_INVALIDPROJECTEDSYSTEM);
			}
			ERROR_FAILED_HRESULT(WTRiASCSValidate(m_pDTrans)->IsValid(), CS_E_INVALIDDATUMTRANSFORMATION);
			ERROR_FAILED_HRESULT(WTRiASCSValidate(m_pDTrans)->RecomputeTransformation(m_pGeographicCS), CS_E_INVALIDDATUMTRANSFORMATION);
		}
#if defined(_USE_GM_CS)
		else 
		{
//			double	ha, f;
//			m_pGeographicCS->get_SemiMajorAxis( &ha );
//			m_pGeographicCS->get_Flattening( &f );
//			WRefSpaceMgr	rsm = m_gmCS->GetRefSpaceMgr( );
//			WGeogSpace		gs = rsm->GetGeogSpace( );
//			gs->PutGeodeticDatumVal( csgdUserDefined );
//			gs->PutEllipsoidVal( cseUserDefined );
//			gs->PutEquatorialRad( ha );
//			gs->PutFlatteningVal( f );
		}
#endif // defined(_USE_GM_CS)
	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASCoordSystem::Transform(long nCoords, CSCOORD* pCoords) 
{
	COM_TRY {
		if (tcsCS_Projected == m_csType)
		{
			ERROR_FAILED_HRESULT(WTRiASCSTransformData(m_pProjectedCS)->Transform(nCoords, pCoords), PCS_E_TRANSFORMATIONFAILED);
		}
	} COM_CATCH;
	return S_OK;
}
	
STDMETHODIMP CTRiASCoordSystem::TransformInverse(long nCoords, CSCOORD* pCoords) 
{
	COM_TRY {
		if (tcsCS_Projected == m_csType)
		{
			ERROR_FAILED_HRESULT(WTRiASCSTransformData(m_pProjectedCS)->TransformInverse(nCoords, pCoords), PCS_E_TRANSFORMATIONFAILED);
		}
	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASCoordSystem::CanTransform(LONG typeOfTransformation) 
{
	return S_OK;
}

STDMETHODIMP CTRiASCoordSystem::get_Description(BSTR * pVal) 
{
	CHECKOUTPOINTER(pVal);
	*pVal = ::SysAllocString(m_strDescription);
	return (NULL != *pVal) ? S_OK : E_OUTOFMEMORY;
}

STDMETHODIMP CTRiASCoordSystem::put_Description(BSTR newVal) 
{
	m_strDescription = newVal;
	return S_OK;
}

STDMETHODIMP CTRiASCoordSystem::get_Name(BSTR * pVal) 
{
	CHECKOUTPOINTER(pVal);
	*pVal = ::SysAllocString(m_bstrName.Length() > 0 ? m_bstrName : L"");
	return (NULL != *pVal) ? S_OK : E_OUTOFMEMORY;
}

STDMETHODIMP CTRiASCoordSystem::put_Name(BSTR newVal) 
{
	m_bstrName = newVal;
	return S_OK;
}

STDMETHODIMP CTRiASCoordSystem::get_Category(BSTR * pVal) 
{
	CHECKOUTPOINTER(pVal);
	*pVal = ::SysAllocString(m_strCategory);
	return (NULL != *pVal) ? S_OK : E_OUTOFMEMORY;
}

STDMETHODIMP CTRiASCoordSystem::put_Category(BSTR newVal) 
{
	m_strCategory = newVal;
	return S_OK;
}

STDMETHODIMP CTRiASCoordSystem::LoadFromRegistry (TCS_REGISTRYROOT root, BSTR strRegKey, VARIANT strComputername)
{
	return S_OK;
}

STDMETHODIMP CTRiASCoordSystem::SaveToRegistry (TCS_REGISTRYROOT root, BSTR strRegKey, VARIANT strComputername)
{
	return S_OK;
}

STDMETHODIMP CTRiASCoordSystem::IsEqual (ITRiASCS *pIOther, VARIANT_BOOL *pfIsEqual)
{
	if (NULL == pfIsEqual)
		return E_POINTER;
	if (NULL == pIOther)
		return E_INVALIDARG;

	*pfIsEqual = (S_OK == EqualCoordSystems(pIOther, this)) ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// ein neues CoordSysDir auf der Platte sicherstellen
HRESULT CTRiASCoordSystem::EnsureTcfPath (BSTR *pbstrTcfPath)
{
CRegKey regKey;

	if (ERROR_SUCCESS == regKey.Open (HKEY_CURRENT_USER, "Software", KEY_READ) &&
		ERROR_SUCCESS == regKey.Open (regKey, REG_COMPANY_KEY, KEY_READ) &&
		ERROR_SUCCESS == regKey.Open (regKey, REG_PRODUCT_KEY, KEY_READ) &&
		ERROR_SUCCESS == regKey.Open (regKey, "Directories"))
	{
	char cbBuffer[_MAX_PATH];
	DWORD dwLen = sizeof(cbBuffer);

		if (ERROR_SUCCESS == regKey.QueryValue (cbBuffer, "CoordSysDir", &dwLen)) {
		CComBSTR bstr (cbBuffer);

			*pbstrTcfPath = bstr.Detach();
			return S_OK;
		}
		else {
		// VerzeichnisPfad neu erzeugen und anlegen
			if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_COMMON_APPDATA|CSIDL_FLAG_CREATE, NULL, 0, cbBuffer))) {
				PathAppend(cbBuffer, REG_COMPANY_KEY);
				CreateDirectory (cbBuffer, NULL);
				PathAppend(cbBuffer, REG_PRODUCT_KEY);
				CreateDirectory (cbBuffer, NULL);
				PathAppend(cbBuffer, "CoordSysDir");
				CreateDirectory (cbBuffer, NULL);
				PathAddBackslash(cbBuffer);

				if (ERROR_SUCCESS == regKey.SetValue(cbBuffer, "CoordSysDir")) {
				CComBSTR bstr (cbBuffer);

					*pbstrTcfPath = bstr.Detach();
					return S_OK;
				}
			}
		}
	}
	return E_FAIL;
}

///////////////////////////////////////////////////////////////////////////////
// Suchen der übergebenen CoordSysDatei
// 1. wenn keine Dateierweiterung gegeben ist
//		Erweiterung --> *.tcf
// 2. wenn Pfad gegeben ist, dann direkt öffnen
// 3. Erweiterung ist *.tcf: Pfade in folgender Reihenfolge testen
//		GetCurrentDirectory
//		CoordSysDir (global)
// 4. Erweiterung ist *.ini: [CoordSystem], LoadFromFile=Dateiname

namespace {
	inline bool FileExists (LPCSTR pcName)
	{
		return ((DWORD)-1 == ::GetFileAttributes (pcName)) ? false : true;
	}
}

HRESULT CTRiASCoordSystem::FindTcfFile (BSTR bstrOrgFile, BSTR *pbstrLocation)
{
	_ASSERTE(NULL != pbstrLocation);
	*pbstrLocation = NULL;

	USES_CONVERSION;

CComBSTR bstrLocation (bstrOrgFile);		// für alle Fälle einfach kopieren
os_path path = os_string(OLE2A(bstrOrgFile));

// nur Dateiname mit Erweiterung
	if (path.extension() == g_cbIni || 
		path.extension() == g_cbDef || 
		path.extension() == g_cbDpd) 
	{
	// nachsehen, ob in der gegeben IniDatei was Vernünftiges drinsteht
	char cbBuffer[_MAX_PATH];
	DWORD dwLen = GetPrivateProfileString("CoordSystem", "LoadFromFile", g_cbNil, 
		cbBuffer, sizeof(cbBuffer), (LPCSTR)path);

		if (0 == dwLen) 
			path = os_string(cbBuffer);		// mit dem Ini-Eintrag weiterarbeiten
		else
			return HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND);
	}
	
	if (!path.has_extension()) 
		path.extension(g_cbTcf);

// ggf. direkt öffnen
	if (path.has_directory() && (path.has_fulldrive() || path.has_unc())) {
	os_string strFile (path);

		if (FileExists(strFile.c_str())) {
		// Datei kann direkt aufgefunden werden
			bstrLocation = strFile.c_str();
			*pbstrLocation = bstrLocation.Detach();
			return S_OK;
		}
		return HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND);
	}
	_ASSERTE(!(path.has_fulldrive() || path.has_unc()) && !path.has_directory());

// im lokalen Verzeichnis nachsehen
char cbBuffer[_MAX_PATH];

	::GetCurrentDirectory(sizeof(cbBuffer), cbBuffer);

os_path currdir (cbBuffer);

	currdir.filename(path.filename());
	currdir.extension(path.extension());

os_string strFile (currdir);

	if (FileExists (strFile.c_str())) {
	// Tcf Datei liegt im aktuellen Verzeichnis
		bstrLocation = strFile.c_str();
		*pbstrLocation = bstrLocation.Detach();
		return S_OK;
	}

// im globalen CoordSysDir nachsehen
CComBSTR bstrTcfPath;

	RETURN_FAILED_HRESULT(EnsureTcfPath(&bstrTcfPath));
	currdir = os_string(OLE2A(bstrTcfPath));
	currdir.filename(path.filename());
	currdir.extension(path.extension());

	strFile = os_string(currdir);
	if (FileExists (strFile.c_str())) {
	// Tcf Datei liegt im aktuellen Verzeichnis
		bstrLocation = strFile.c_str();
		*pbstrLocation = bstrLocation.Detach();
		return S_OK;
	}	

// nichts gefunden
	if (FileExists(OLE2A(bstrLocation))) {
		*pbstrLocation = bstrLocation.Detach();		// OriginalDateiname liefern
		return S_OK;
	}
	return HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND);
}

///////////////////////////////////////////////////////////////////////////////
// Finden und ggf. laden einer CoordSys-Resource
HRESULT CTRiASCoordSystem::FindCoordSysResource(LPCSTR pcBaseName, HGLOBAL *phGbl)
{
	_ASSERTE(NULL != phGbl);
	*phGbl = NULL;

HRSRC hRsc = ::FindResource(_Module.GetResourceInstance(), pcBaseName, g_cbCOORDSYS);

	if (NULL == hRsc)
		return E_INVALIDARG;	// resource not found

HGLOBAL hGlb = ::LoadResource(_Module.GetModuleInstance(), hRsc);

	if (NULL == hGlb) 
		return E_INVALIDARG;

LPVOID pData = ::LockResource(hGlb);

	if (NULL == pData) 
		return E_INVALIDARG;

	COM_TRY {
	DWORD dwSize = ::SizeofResource(_Module.GetModuleInstance(), hRsc);
	CGlobalMem hMem (dwSize);	// throws E_OUTOFMEMORY

		{
		CGlobalMem::Lock<BYTE> lock(hMem);

			memcpy(lock, pData, dwSize);
		}
		*phGbl = hMem.Detach();

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// aus einer CoordSys-Resource ein Storage bauen und CS laden
HRESULT CTRiASCoordSystem::LoadCoordSysFromResource(CGlobalMem &rMem)
{
// Resource ist erfolgreich im Speicher
WLockBytes lockBytes;
WStorage Stg;
CGlobalMem::Lock<BYTE> lock (rMem);

	if (SUCCEEDED(CreateILockBytesOnHGlobal(lock, FALSE, lockBytes.ppi()))) {
	CIID ClsId;

		RETURN_FAILED_HRESULT(StgOpenStorageOnILockBytes(lockBytes, NULL, 
			STGM_DIRECT|STGM_SHARE_EXCLUSIVE|STGM_READ, NULL, 0L, Stg.ppi()));

		RETURN_FAILED_HRESULT(ReadClassStg(Stg, &ClsId));
		if (!InlineIsEqualGUID(ClsId, GetObjectCLSID()))
			return E_UNEXPECTED;	// bad file format

	WStream Strm;

		RETURN_FAILED_HRESULT(Stg -> OpenStream(GetSubStreamName(), NULL, 
			STGM_DIRECT|STGM_SHARE_EXCLUSIVE|STGM_READ, 0L, Strm.ppi()));

	char szSignat[4];
	DWORD dwVersion;

		RETURN_FAILED_HRESULT(LoadItem (Strm, szSignat));
		RETURN_FAILED_HRESULT(LoadItem (Strm, dwVersion));

		RETURN_FAILED_HRESULT(LoadData (Strm, dwVersion));
	}
	return S_OK;
}

STDMETHODIMP CTRiASCoordSystem::LoadFromFile (BSTR bstrFileName)
{
// zuerst versuchen, aus Resource zu laden
	USES_CONVERSION;

os_path path = os_string(OLE2A(bstrFileName));
CGlobalMem hMem;
HRESULT hr = FindCoordSysResource (path.base().c_str(), &hMem);

	if (SUCCEEDED(hr)) {
		hr = LoadCoordSysFromResource (hMem);
		if (SUCCEEDED(hr))
			return hr;		// ok, fertig geladen
	}

// jetzt Versuchen aus einer Datei zu laden
CComBSTR bstrFile;

	hr = FindTcfFile (bstrFileName, &bstrFile);
	if (FAILED(hr))
		return hr;		// Datei existiert nicht oder anderer Fehler

// Datei jetzt laden
WPersistFile PSFile;
	
	hr = GetUnknown() -> QueryInterface(PSFile.ppi());
	if (SUCCEEDED(hr))
		hr = PSFile -> Load (bstrFile, STGM_READ|STGM_SHARE_DENY_NONE);
	return hr;
}

STDMETHODIMP CTRiASCoordSystem::SaveToFile (BSTR strFile)
{
WPersistFile PSFile;
HRESULT hr = GetUnknown() -> QueryInterface(PSFile.ppi());

	if (SUCCEEDED(hr)) {
		RETURN_FAILED_HRESULT(PSFile -> Save (strFile, TRUE));
		RETURN_FAILED_HRESULT(PSFile -> SaveCompleted(strFile));
	}
	return hr;
}

// Implementation of get_InputMask
STDMETHODIMP CTRiASCoordSystem::get_InputMask(COORDELEMENT Element, BSTR *pbstrUIMask)
{
	ATLTRACE(_T("CTRiASCoordSystem::get_InputMask\n"));
	CHECKOUTPOINTER(pbstrUIMask);

WTRiASCSUIHelper UIHelper;
HRESULT hr = E_NOINTERFACE;

	switch (m_csType) {
	case tcsCS_Projected:
		if (SUCCEEDED(m_pProjectedCS -> QueryInterface(UIHelper.ppi()))) {
			RETURN_FAILED_HRESULT(UIHelper -> get_InputMask(Element, pbstrUIMask));
			return S_OK;
		}
		break;

	case tcsCS_Geographic:
		if (SUCCEEDED(m_pGeographicCS -> QueryInterface(UIHelper.ppi()))) {
			RETURN_FAILED_HRESULT(UIHelper -> get_InputMask(Element, pbstrUIMask));
			return S_OK;
		}
		break;

	case tcsCS_Geocentric:
	default:
		hr = E_UNEXPECTED;
		break;
	}
	_ASSERTE(SUCCEEDED(hr));
	return hr;
}


// Implementation of get_Precision
STDMETHODIMP CTRiASCoordSystem::get_Precision(long *plPrec)
{
	ATLTRACE(_T("CTRiASCoordSystem::get_Precision\n"));
	CHECKOUTPOINTER(plPrec);

WTRiASCSUIHelper UIHelper;
HRESULT hr = E_NOINTERFACE;

	switch (m_csType) {
	case tcsCS_Projected:
		if (SUCCEEDED(m_pProjectedCS -> QueryInterface(UIHelper.ppi()))) {
			RETURN_FAILED_HRESULT(UIHelper -> get_Precision(plPrec));
			return S_OK;
		}
		break;

	case tcsCS_Geographic:
		if (SUCCEEDED(m_pGeographicCS -> QueryInterface(UIHelper.ppi()))) {
			RETURN_FAILED_HRESULT(UIHelper -> get_Precision(plPrec));
			return S_OK;
		}
		break;

	case tcsCS_Geocentric:
	default:
		hr = E_UNEXPECTED;
		break;
	}
	_ASSERTE(SUCCEEDED(hr));
	return hr;
}

// Implementation of put_Precision
STDMETHODIMP CTRiASCoordSystem::put_Precision(long lPrec)
{
	ATLTRACE(_T("CTRiASCoordSystem::put_Precision\n"));

WTRiASCSUIHelper UIHelper;
HRESULT hr = E_NOINTERFACE;

	switch (m_csType) {
	case tcsCS_Projected:
		if (SUCCEEDED(m_pProjectedCS -> QueryInterface(UIHelper.ppi()))) {
			RETURN_FAILED_HRESULT(UIHelper -> put_Precision(lPrec));
			return S_OK;
		}
		break;

	case tcsCS_Geographic:
		if (SUCCEEDED(m_pGeographicCS -> QueryInterface(UIHelper.ppi()))) {
			RETURN_FAILED_HRESULT(UIHelper -> put_Precision(lPrec));
			return S_OK;
		}
		break;

	case tcsCS_Geocentric:
	default:
		hr = E_UNEXPECTED;
		break;
	}
	_ASSERTE(SUCCEEDED(hr));
	return hr;
}

// Implementation of Format
STDMETHODIMP CTRiASCoordSystem::Format(COORDELEMENT rgElement, double dValue, BSTR *pbstrFormattedElement)
{
	ATLTRACE(_T("CTRiASCoordSystem::Format\n"));
	CHECKOUTPOINTER(pbstrFormattedElement);

WTRiASCSUIHelper UIHelper;
HRESULT hr = E_NOINTERFACE;

	switch (m_csType) {
	case tcsCS_Projected:
		if (SUCCEEDED(m_pProjectedCS -> QueryInterface(UIHelper.ppi()))) {
			RETURN_FAILED_HRESULT(UIHelper -> Format(rgElement, dValue, pbstrFormattedElement));
			return S_OK;
		}
		break;

	case tcsCS_Geographic:
		if (SUCCEEDED(m_pGeographicCS -> QueryInterface(UIHelper.ppi()))) {
			RETURN_FAILED_HRESULT(UIHelper -> Format(rgElement, dValue, pbstrFormattedElement));
			return S_OK;
		}
		break;

	case tcsCS_Geocentric:
	default:
		hr = E_UNEXPECTED;
		break;
	}
	_ASSERTE(SUCCEEDED(hr));
	return hr;
}

// Implementation of Convert
STDMETHODIMP CTRiASCoordSystem::Convert(COORDELEMENT rgElement, BSTR bstrFormatted, double *pValue)
{
	ATLTRACE(_T("CTRiASCoordSystem::Convert\n"));
	CHECKOUTPOINTER(pValue);

WTRiASCSUIHelper UIHelper;
HRESULT hr = E_NOINTERFACE;

	switch (m_csType) {
	case tcsCS_Projected:
		if (SUCCEEDED(m_pProjectedCS -> QueryInterface(UIHelper.ppi()))) {
			RETURN_FAILED_HRESULT(UIHelper -> Convert(rgElement, bstrFormatted, pValue));
			return S_OK;
		}
		break;

	case tcsCS_Geographic:
		if (SUCCEEDED(m_pGeographicCS -> QueryInterface(UIHelper.ppi()))) {
			RETURN_FAILED_HRESULT(UIHelper -> Convert(rgElement, bstrFormatted, pValue));
			return S_OK;
		}
		break;

	case tcsCS_Geocentric:
	default:
		hr = E_UNEXPECTED;
		break;
	}
	_ASSERTE(SUCCEEDED(hr));
	return hr;
}

#if defined(_USE_OGC_COMPATIBILITY)
// ISpatialReference
// Implementation of get_Name
STDMETHODIMP CTRiASCoordSystem::get_Name(BSTR *pbstrName)
{
	ATLTRACE(_T("CTRiASCoordSystem::get_Name\n"));
	CHECKOUTPOINTER(pbstrName);

WSpatialReference RefHelper;
HRESULT hr = E_NOINTERFACE;

	switch (m_csType) {
	case tcsCS_Projected:
		if (SUCCEEDED(m_pProjectedCS -> QueryInterface(RefHelper.ppi()))) {
			RETURN_FAILED_HRESULT(RefHelper -> get_Name(pbstrName));
			return S_OK;
		}
		break;

	case tcsCS_Geographic:
		if (SUCCEEDED(m_pGeographicCS -> QueryInterface(RefHelper.ppi()))) {
			RETURN_FAILED_HRESULT(RefHelper -> get_Name(pbstrName));
			return S_OK;
		}
		break;

	case tcsCS_Geocentric:
	default:
		hr = E_UNEXPECTED;
		break;
	}
	_ASSERTE(SUCCEEDED(hr));
	return hr;
}

// Implementation of put_Name
STDMETHODIMP CTRiASCoordSystem::put_Name(BSTR bstrName)
{
	ATLTRACE(_T("CTRiASCoordSystem::put_Name\n"));

WSpatialReference RefHelper;
HRESULT hr = E_NOINTERFACE;

	switch (m_csType) {
	case tcsCS_Projected:
		if (SUCCEEDED(m_pProjectedCS -> QueryInterface(RefHelper.ppi()))) {
			RETURN_FAILED_HRESULT(RefHelper -> put_Name(bstrName));
			return S_OK;
		}
		break;

	case tcsCS_Geographic:
		if (SUCCEEDED(m_pGeographicCS -> QueryInterface(RefHelper.ppi()))) {
			RETURN_FAILED_HRESULT(RefHelper -> put_Name(bstrName));
			return S_OK;
		}
		break;

	case tcsCS_Geocentric:
	default:
		hr = E_UNEXPECTED;
		break;
	}
	_ASSERTE(SUCCEEDED(hr));
	return hr;
}

// Implementation of get_Authority
STDMETHODIMP CTRiASCoordSystem::get_Authority(BSTR *pbstrAuth)
{
	ATLTRACE(_T("CTRiASCoordSystem::get_Authority\n"));
	CHECKOUTPOINTER(pbstrAuth);

WSpatialReference RefHelper;
HRESULT hr = E_NOINTERFACE;

	switch (m_csType) {
	case tcsCS_Projected:
		if (SUCCEEDED(m_pProjectedCS -> QueryInterface(RefHelper.ppi()))) {
			RETURN_FAILED_HRESULT(RefHelper -> get_Authority(pbstrAuth));
			return S_OK;
		}
		break;

	case tcsCS_Geographic:
		if (SUCCEEDED(m_pGeographicCS -> QueryInterface(RefHelper.ppi()))) {
			RETURN_FAILED_HRESULT(RefHelper -> get_Authority(pbstrAuth));
			return S_OK;
		}
		break;

	case tcsCS_Geocentric:
	default:
		hr = E_UNEXPECTED;
		break;
	}
	_ASSERTE(SUCCEEDED(hr));
	return hr;
}

// Implementation of put_Authority
STDMETHODIMP CTRiASCoordSystem::put_Authority(BSTR bstrAuth)
{
	ATLTRACE(_T("CTRiASCoordSystem::put_Authority\n"));

WSpatialReference RefHelper;
HRESULT hr = E_NOINTERFACE;

	switch (m_csType) {
	case tcsCS_Projected:
		if (SUCCEEDED(m_pProjectedCS -> QueryInterface(RefHelper.ppi()))) {
			RETURN_FAILED_HRESULT(RefHelper -> put_Authority(bstrAuth));
			return S_OK;
		}
		break;

	case tcsCS_Geographic:
		if (SUCCEEDED(m_pGeographicCS -> QueryInterface(RefHelper.ppi()))) {
			RETURN_FAILED_HRESULT(RefHelper -> put_Authority(bstrAuth));
			return S_OK;
		}
		break;

	case tcsCS_Geocentric:
	default:
		hr = E_UNEXPECTED;
		break;
	}
	_ASSERTE(SUCCEEDED(hr));
	return hr;
}

// Implementation of get_Code
STDMETHODIMP CTRiASCoordSystem::get_Code(long *plCode)
{
	ATLTRACE(_T("CTRiASCoordSystem::get_Code\n"));
	CHECKOUTPOINTER(plCode);

WSpatialReference RefHelper;
HRESULT hr = E_NOINTERFACE;

	switch (m_csType) {
	case tcsCS_Projected:
		if (SUCCEEDED(m_pProjectedCS -> QueryInterface(RefHelper.ppi()))) {
			RETURN_FAILED_HRESULT(RefHelper -> get_Code(plCode));
			return S_OK;
		}
		break;

	case tcsCS_Geographic:
		if (SUCCEEDED(m_pGeographicCS -> QueryInterface(RefHelper.ppi()))) {
			RETURN_FAILED_HRESULT(RefHelper -> get_Code(plCode));
			return S_OK;
		}
		break;

	case tcsCS_Geocentric:
	default:
		hr = E_UNEXPECTED;
		break;
	}
	_ASSERTE(SUCCEEDED(hr));
	return hr;
}

// Implementation of put_Code
STDMETHODIMP CTRiASCoordSystem::put_Code(long lCode)
{
	ATLTRACE(_T("CTRiASCoordSystem::put_Code\n"));

WSpatialReference RefHelper;
HRESULT hr = E_NOINTERFACE;

	switch (m_csType) {
	case tcsCS_Projected:
		if (SUCCEEDED(m_pProjectedCS -> QueryInterface(RefHelper.ppi()))) {
			RETURN_FAILED_HRESULT(RefHelper -> put_Code(lCode));
			return S_OK;
		}
		break;

	case tcsCS_Geographic:
		if (SUCCEEDED(m_pGeographicCS -> QueryInterface(RefHelper.ppi()))) {
			RETURN_FAILED_HRESULT(RefHelper -> put_Code(lCode));
			return S_OK;
		}
		break;

	case tcsCS_Geocentric:
	default:
		hr = E_UNEXPECTED;
		break;
	}
	_ASSERTE(SUCCEEDED(hr));
	return hr;
}

// Implementation of get_Alias
STDMETHODIMP CTRiASCoordSystem::get_Alias(BSTR *pbstrAlias)
{
	ATLTRACE(_T("CTRiASCoordSystem::get_Alias\n"));
	CHECKOUTPOINTER(pbstrAlias);

WSpatialReference RefHelper;
HRESULT hr = E_NOINTERFACE;

	switch (m_csType) {
	case tcsCS_Projected:
		if (SUCCEEDED(m_pProjectedCS -> QueryInterface(RefHelper.ppi()))) {
			RETURN_FAILED_HRESULT(RefHelper -> get_Alias(pbstrAlias));
			return S_OK;
		}
		break;

	case tcsCS_Geographic:
		if (SUCCEEDED(m_pGeographicCS -> QueryInterface(RefHelper.ppi()))) {
			RETURN_FAILED_HRESULT(RefHelper -> get_Alias(pbstrAlias));
			return S_OK;
		}
		break;

	case tcsCS_Geocentric:
	default:
		hr = E_UNEXPECTED;
		break;
	}
	_ASSERTE(SUCCEEDED(hr));
	return hr;
}

// Implementation of put_Alias
STDMETHODIMP CTRiASCoordSystem::put_Alias(BSTR bstrAlias)
{
	ATLTRACE(_T("CTRiASCoordSystem::put_Alias\n"));

WSpatialReference RefHelper;
HRESULT hr = E_NOINTERFACE;

	switch (m_csType) {
	case tcsCS_Projected:
		if (SUCCEEDED(m_pProjectedCS -> QueryInterface(RefHelper.ppi()))) {
			RETURN_FAILED_HRESULT(RefHelper -> put_Alias(bstrAlias));
			return S_OK;
		}
		break;

	case tcsCS_Geographic:
		if (SUCCEEDED(m_pGeographicCS -> QueryInterface(RefHelper.ppi()))) {
			RETURN_FAILED_HRESULT(RefHelper -> put_Alias(bstrAlias));
			return S_OK;
		}
		break;

	case tcsCS_Geocentric:
	default:
		hr = E_UNEXPECTED;
		break;
	}
	_ASSERTE(SUCCEEDED(hr));
	return hr;
}

// Implementation of get_Abbreviation
STDMETHODIMP CTRiASCoordSystem::get_Abbreviation(BSTR *pbstrAbbrev)
{
	ATLTRACE(_T("CTRiASCoordSystem::get_Abbreviation\n"));
	CHECKOUTPOINTER(pbstrAbbrev);

WSpatialReference RefHelper;
HRESULT hr = E_NOINTERFACE;

	switch (m_csType) {
	case tcsCS_Projected:
		if (SUCCEEDED(m_pProjectedCS -> QueryInterface(RefHelper.ppi()))) {
			RETURN_FAILED_HRESULT(RefHelper -> get_Abbreviation(pbstrAbbrev));
			return S_OK;
		}
		break;

	case tcsCS_Geographic:
		if (SUCCEEDED(m_pGeographicCS -> QueryInterface(RefHelper.ppi()))) {
			RETURN_FAILED_HRESULT(RefHelper -> get_Abbreviation(pbstrAbbrev));
			return S_OK;
		}
		break;

	case tcsCS_Geocentric:
	default:
		hr = E_UNEXPECTED;
		break;
	}
	_ASSERTE(SUCCEEDED(hr));
	return hr;
}

// Implementation of put_Abbreviation
STDMETHODIMP CTRiASCoordSystem::put_Abbreviation(BSTR bstrAbbrev)
{
	ATLTRACE(_T("CTRiASCoordSystem::put_Abbreviation\n"));

WSpatialReference RefHelper;
HRESULT hr = E_NOINTERFACE;

	switch (m_csType) {
	case tcsCS_Projected:
		if (SUCCEEDED(m_pProjectedCS -> QueryInterface(RefHelper.ppi()))) {
			RETURN_FAILED_HRESULT(RefHelper -> put_Abbreviation(bstrAbbrev));
			return S_OK;
		}
		break;

	case tcsCS_Geographic:
		if (SUCCEEDED(m_pGeographicCS -> QueryInterface(RefHelper.ppi()))) {
			RETURN_FAILED_HRESULT(RefHelper -> put_Abbreviation(bstrAbbrev));
			return S_OK;
		}
		break;

	case tcsCS_Geocentric:
	default:
		hr = E_UNEXPECTED;
		break;
	}
	_ASSERTE(SUCCEEDED(hr));
	return hr;
}

// Implementation of get_Remarks
STDMETHODIMP CTRiASCoordSystem::get_Remarks(BSTR *pbstrRemarks)
{
	ATLTRACE(_T("CTRiASCoordSystem::get_Remarks\n"));
	CHECKOUTPOINTER(pbstrRemarks);

WSpatialReference RefHelper;
HRESULT hr = E_NOINTERFACE;

	switch (m_csType) {
	case tcsCS_Projected:
		if (SUCCEEDED(m_pProjectedCS -> QueryInterface(RefHelper.ppi()))) {
			RETURN_FAILED_HRESULT(RefHelper -> get_Remarks(pbstrRemarks));
			return S_OK;
		}
		break;

	case tcsCS_Geographic:
		if (SUCCEEDED(m_pGeographicCS -> QueryInterface(RefHelper.ppi()))) {
			RETURN_FAILED_HRESULT(RefHelper -> get_Remarks(pbstrRemarks));
			return S_OK;
		}
		break;

	case tcsCS_Geocentric:
	default:
		hr = E_UNEXPECTED;
		break;
	}
	_ASSERTE(SUCCEEDED(hr));
	return hr;
}

// Implementation of put_Remarks
STDMETHODIMP CTRiASCoordSystem::put_Remarks(BSTR bstrRemarks)
{
	ATLTRACE(_T("CTRiASCoordSystem::put_Remarks\n"));

WSpatialReference RefHelper;
HRESULT hr = E_NOINTERFACE;

	switch (m_csType) {
	case tcsCS_Projected:
		if (SUCCEEDED(m_pProjectedCS -> QueryInterface(RefHelper.ppi()))) {
			RETURN_FAILED_HRESULT(RefHelper -> put_Remarks(bstrRemarks));
			return S_OK;
		}
		break;

	case tcsCS_Geographic:
		if (SUCCEEDED(m_pGeographicCS -> QueryInterface(RefHelper.ppi()))) {
			RETURN_FAILED_HRESULT(RefHelper -> put_Remarks(bstrRemarks));
			return S_OK;
		}
		break;

	case tcsCS_Geocentric:
	default:
		hr = E_UNEXPECTED;
		break;
	}
	_ASSERTE(SUCCEEDED(hr));
	return hr;
}

// Implementation of get_WellKnownText
STDMETHODIMP CTRiASCoordSystem::get_WellKnownText(BSTR *pbstrWkt)
{
	ATLTRACE(_T("CTRiASCoordSystem::get_WellKnownText\n"));
	CHECKOUTPOINTER(pbstrWkt);

WSpatialReference RefHelper;
HRESULT hr = E_NOINTERFACE;

	switch (m_csType) {
	case tcsCS_Projected:
		if (SUCCEEDED(m_pProjectedCS -> QueryInterface(RefHelper.ppi()))) {
			RETURN_FAILED_HRESULT(RefHelper -> get_WellKnownText(pbstrWkt));
			return S_OK;
		}
		break;

	case tcsCS_Geographic:
		if (SUCCEEDED(m_pGeographicCS -> QueryInterface(RefHelper.ppi()))) {
			RETURN_FAILED_HRESULT(RefHelper -> get_WellKnownText(pbstrWkt));
			return S_OK;
		}
		break;

	case tcsCS_Geocentric:
	default:
		hr = E_UNEXPECTED;
		break;
	}
	_ASSERTE(SUCCEEDED(hr));
	return hr;
}
#endif // defined(_USE_OGC_COMPATIBILITY)

