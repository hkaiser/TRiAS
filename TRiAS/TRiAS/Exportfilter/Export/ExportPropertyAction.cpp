// $Header: $
// Copyright© 1999 Fernerkundungszentrum Potsdam GmbH, All rights reserved
//
// @doc
// @module ExportPropertyAction.cpp | Implementation of the <c CExportPropertyAction> class

#include "stdafx.h"
#include "ExportImpl.h"

#include <ospace/stlex/boolops.h>

#include "ExportPropertyAction.h"
#include "ExportUtil.h"

// KK000301
#include <vinfomfc.h>
#include <ristypes.hxx>

#include <Esnecil.h>

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(PropertyInfo3);

///////////////////////////////////////////////////////////////////////////////
// 
HRESULT CExportPropertyAction::FinalConstruct() 
{
	return S_OK;
}

HRESULT CExportPropertyAction::FinalRelease() 
{
	m_vecOfEngines.clear();
	m_mapOfRegisteredEngines.clear();
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// CExportPropertyAction
// IPropertyAction 

STDMETHODIMP CExportPropertyAction::BeginAction (IProgressIndicator *pIProgInd) 
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());

	RETURN_FAILED_HRESULT(CPropertyActionImpl::BeginAction (pIProgInd));
	
	///////////////////////////////////////////////////////////////////////////////
	// Eingaben aus der Konfigurationspage auslesen
	m_pTRiASExtDataEngine = m_pCfgDlg->m_pTRiASExtDataEngine;

// KK000823
	m_bSeparate = m_pCfgDlg->m_bSeparate;
	m_bSelect = m_pCfgDlg->m_bSelect;
	m_pObjPropDlg->GetSelectedObjProps(m_lstSelObjProps);

	m_mapCodes.erase();

	// KK991111
	CComBSTR	strFilename;
	m_pTRiASExtDataEngine->get_Filename(&strFilename);
	m_strWunschFile = strFilename;

	if ( strFilename.Length() > OFS_MAXPATHNAME - 40) {
	// Namenstausch - C:\Temp\...
		TCHAR	strDrive[_MAX_DRIVE];
		TCHAR	strDir[_MAX_DIR];
		TCHAR	strName[_MAX_FNAME];
		TCHAR	strExt[_MAX_EXT];

		TCHAR TempDat[_MAX_PATH];

		DWORD TD = 0;

		USES_CONVERSION;

		::_splitpath( W2A(strFilename), strDrive, strDir, strName, strExt );
		m_strWunschDir.Empty();

		::_makepath(TempDat,strDrive,strDir,NULL,NULL);
		m_strWunschDir.Append(TempDat);

		TD = GetTempPath(_MAX_PATH, TempDat);
		if ( TD > 0 ) {		// Temp-Bereich gefunden
			DWORD TTD = GetTempPath(TD +1, TempDat);
			char *cptr;
			if (*(cptr = &TempDat[strlen(TempDat)-1]) != '\\')
				lstrcat (TempDat,"\\");
			lstrcat (TempDat,"TRiASExport");
			lstrcat (TempDat,"\\");

			::_splitpath( TempDat, strDrive, strDir, NULL, NULL );
			m_strZielDir.Empty();

			::_makepath(TempDat,strDrive,strDir,NULL,NULL);
			m_strZielDir.Append(TempDat);

			strFilename.Empty();

			::_makepath( TempDat, strDrive, strDir, strName, strExt );
			strFilename.Append(TempDat);

			m_pTRiASExtDataEngine->put_Filename(strFilename);
		}
	}
	// KK991111

// Verarbeitung der Objekte vorbereiten
	m_Objects.Clear();
	return S_OK;
}

//---KK 991115-------------------------------------------------------------------------
HRESULT CExportPropertyAction :: CopyExportFilesEx (void)
{
// KK991111 - Ende ???
	USES_CONVERSION;
	if (m_strZielDir.Length() > 2) {
	WIN32_FIND_DATA Info;

		SetCurrentDirectory( W2A(m_strWunschDir) ); 

		TCHAR strRefFile[_MAX_PATH];
		TCHAR strZielFile[_MAX_PATH];
		TCHAR strQuellFile[_MAX_PATH];
		char *cptr;
	// ReferenzDirectory
		lstrcpy (strRefFile,W2A(m_strZielDir));
		if (*(cptr = &strRefFile[strlen(strRefFile)-1]) != '\\')
			lstrcat (strRefFile,"\\");

	// Move-Quelle
		lstrcpy(strQuellFile,strRefFile);

	// Move-Ziel
		lstrcpy (strZielFile,W2A(m_strWunschDir));
		if (*(cptr = &strZielFile[strlen(strZielFile)-1]) != '\\')
			lstrcat (strZielFile,"\\");

		lstrcat (strRefFile,"*");
		
	TCHAR strZielDir[_MAX_PATH];
	TCHAR strQuellDir[_MAX_PATH];
	TCHAR strStartDir[_MAX_PATH];

		lstrcpy (strStartDir, strQuellFile);
		lstrcpy (strQuellDir, strQuellFile);
		lstrcpy (strZielDir, strZielFile);

	HANDLE hFindFile = FindFirstFile(strRefFile, &Info);
	DWORD dwFlags = MOVEFILE_WRITE_THROUGH | MOVEFILE_REPLACE_EXISTING | MOVEFILE_COPY_ALLOWED;
			
		while (hFindFile != INVALID_HANDLE_VALUE) {

			if (Info.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				if (Info.cFileName[0] != '.' ) {
						
					lstrcpy (strQuellFile,strQuellDir);
					lstrcpy (strZielFile,strZielDir);

					lstrcat (strQuellFile, Info.cFileName);
					lstrcat (strZielFile, Info.cFileName);

					if(!SetCurrentDirectory( strZielFile ) )
						RETURN_EXPR_FALSE(CreateDirectory( strZielFile, NULL ), E_FAIL );

					if (*(cptr = &strQuellFile[strlen(strQuellFile)-1]) != '\\')
						lstrcat (strQuellFile,"\\");
					if (*(cptr = &strZielFile[strlen(strZielFile)-1]) != '\\')
						lstrcat (strZielFile,"\\");
					CopyExportFiles (strQuellFile, strZielFile);

				}
			} else {
				if (Info.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE) {

					lstrcpy(strQuellFile,strQuellDir);
					lstrcpy(strZielFile,strZielDir);

					lstrcat (strQuellFile, Info.cFileName);
		
					lstrcat (strZielFile, Info.cFileName);

					MoveFileEx (strQuellFile, strZielFile, dwFlags);
				}
			}

			Info.dwFileAttributes = 0;
			FindNextFile(hFindFile, &Info);

			if (GetLastError() == ERROR_NO_MORE_FILES) {
				FindClose (hFindFile);
				RemoveDirectory(strStartDir);
				hFindFile = INVALID_HANDLE_VALUE;
				SetLastError(ERROR_SUCCESS);
			}
		}
		FindClose (hFindFile);

		if (*(cptr = &strRefFile[strlen(strRefFile)-1]) == '*')
			*cptr = '\0';
		RemoveDirectory(strStartDir);
	}
	return S_OK;
}

//---KK 991115-------------------------------------------------------------------------
bool CExportPropertyAction :: CopyExportFiles ( char * strQuelle, char * strZiel)
{
WIN32_FIND_DATA Info;
TCHAR strRefFile[_MAX_PATH];
TCHAR strZielFile[_MAX_PATH];
TCHAR strQuellFile[_MAX_PATH];

	lstrcpy (strRefFile,strQuelle);

	char *cptr;
	// ReferenzDirectory

	if (*(cptr = &strRefFile[strlen(strRefFile)-1]) != '\\')
		lstrcat (strRefFile,"\\");
	
	// Move-Quelle
	lstrcpy(strQuellFile,strRefFile);
	
	// Move-Ziel
	lstrcpy (strZielFile,strZiel);
	if (*(cptr = &strZielFile[strlen(strZielFile)-1]) != '\\')
		lstrcat (strZielFile,"\\");

	lstrcat (strRefFile,"*");
		
TCHAR strZielDir[_MAX_PATH];
TCHAR strQuellDir[_MAX_PATH];
TCHAR strStartDir[_MAX_PATH];

	lstrcpy (strStartDir,strQuellFile);
	lstrcpy (strQuellDir,strQuellFile);
	lstrcpy (strZielDir,strZielFile);

DWORD dwFlags = MOVEFILE_WRITE_THROUGH | MOVEFILE_REPLACE_EXISTING;
HANDLE hFindFile = FindFirstFile(strRefFile, &Info);

	while ( hFindFile != INVALID_HANDLE_VALUE) {

		if (Info.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {

			if (Info.cFileName[0] != '.' ) {
							
				lstrcpy(strQuellFile,strQuellDir);
				lstrcpy(strZielFile,strZielDir);

				lstrcat (strQuellFile, Info.cFileName);
				lstrcat (strZielFile, Info.cFileName);

				if( !SetCurrentDirectory( strZielDir ) ) {
					if (!CreateDirectory( strZielDir, NULL ))
						return false;
				}

				if (*(cptr = &strQuellFile[strlen(strQuellFile)-1]) != '\\')
					lstrcat (strQuellFile,"\\");
				if (*(cptr = &strZielFile[strlen(strZielFile)-1]) != '\\')
					lstrcat (strZielFile,"\\");

				CopyExportFiles (strQuellFile,strZielFile);
			}
		} else {
			if (Info.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE) {

				lstrcpy(strQuellFile,strQuellDir);
				lstrcpy(strZielFile,strZielDir);

				lstrcat (strQuellFile, Info.cFileName);
		
				lstrcat (strZielFile, Info.cFileName);

				MoveFileEx (strQuellFile, strZielFile, dwFlags);
			}
		}

		Info.dwFileAttributes = 0;
		FindNextFile(hFindFile, &Info);

		if (GetLastError() == ERROR_NO_MORE_FILES) {
			FindClose (hFindFile);
			RemoveDirectory(strQuellDir);
			SetLastError(ERROR_SUCCESS);
			return true;
		}
	}

	FindClose (hFindFile);
	RemoveDirectory(strQuellDir);
	return true;
}
//-------------------------------------------------------------------------------------

using namespace PropActBase;		// {Get,Set}EnumObjects

STDMETHODIMP CExportPropertyAction::DoAction (IDataObject *pIDataObj, DWORD dwReserved) 
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());

	// Eingabeobjekte einfach mit zu unserer Objektmenge hinzufügen
	COM_TRY {
	WEnumLONG EnumObjs;
	CPrjMapOutputIter iter_out_if (&m_Objects);

		THROW_FAILED_HRESULT(GetEnumObjects (pIDataObj, __uuidof(IEnumLONG), EnumObjs.ppv()));

		copy (InEnumLONG(EnumObjs), InEnumLONG(), iter_out_if);

	} COM_CATCH;
	return S_OK;
}

namespace {
	bool IsLicensed()
	{
	VERIFYLICENSE VL;

		INITSTRUCT(VL, VERIFYLICENSE);
		VL.iMode = VERIFYMODE_DontShowDialog|VERIFYMODE_LessOrEqual;
		VL.lLevelOrOption = CKILEVEL_PLUS;
		return DEX_VerifyLicenseLevel(VL);
	}

	void ShowNotLicensed()
	{
	VERIFYLICENSE VL;
	CString strLicCap;

		VERIFY(strLicCap.LoadString(IDS_LONGCLASSNAME));
		
		INITSTRUCT(VL, VERIFYLICENSE);
		VL.iMode = VERIFYMODE_LessOrEqual;
		VL.lLevelOrOption = CKILEVEL_PLUS;
		VL.hWndParent = NULL;
		VL.pcCaption = strLicCap;
		DEX_VerifyLicenseLevel(VL);
	}
}

STDMETHODIMP CExportPropertyAction::PreConfigPages (IDataObject *pIDataObject, DWORD dwFlags) 
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	COM_TRY {
		if (0 == m_vecOfEngines.size()) {
		// EPA_E_NOENGINESLOADED
			if (IsLicensed()) {
			CString strCaption;
			CString strMessage;
			TCHAR _buf[_MAX_PATH];

				VERIFY(strCaption.LoadString(IDS_SHOWXMLERROR_CAP));
				VERIFY(strMessage.LoadString(IDS_NOXMLDOMPARSER));
				wsprintf (_buf, strMessage, g_szTRiAS);
				AfxGetMainWnd()->MessageBox (_buf, strCaption, MB_OK | MB_ICONERROR);
				return EPA_E_NOENGINESLOADED;
			} 
			else {
				ShowNotLicensed();
				return CLASS_E_NOTLICENSED;
			}
		}

		ERROR_EXPR_TRUE(NULL == m_pCfgDlg, E_UNEXPECTED);
		ERROR_EXPR_TRUE(NULL == m_pObjPropDlg, E_UNEXPECTED);
		ERROR_EXPR_TRUE(NULL == m_pSelCsDlg, E_UNEXPECTED);

	// Konfigurationspage mit geladenem Zustand füttern
		_ASSERTE(0 == m_pCfgDlg->m_vecOfEngines.size());
		copy(m_vecOfEngines.begin(), m_vecOfEngines.end(), 
			inserter(m_pCfgDlg->m_vecOfEngines, m_pCfgDlg->m_vecOfEngines.begin()));

		_ASSERTE(m_vecOfEngines.size() == m_pCfgDlg->m_vecOfEngines.size());
		m_pCfgDlg->m_pTRiASExtDataEngine = m_pTRiASExtDataEngine;

		if (m_fCreated2ndPage) {
			m_pCfgDlg->SetFlags(dwFlags & ~ADDPAGES_LASTPAGE);
			if (m_fCreated3rdPage) {
				m_pObjPropDlg->SetFlags(dwFlags & ~(ADDPAGES_FIRSTPAGE|ADDPAGES_LASTPAGE));
				m_pSelCsDlg->SetFlags(dwFlags & ~ADDPAGES_FIRSTPAGE);
			}
			else {
				m_pObjPropDlg->SetFlags(dwFlags & ~ADDPAGES_FIRSTPAGE);
			}
		}
		else {
			m_pCfgDlg->SetFlags(dwFlags);
		}

	} COM_CATCH;
	return S_OK;
}

static 
HRESULT CheckCapability( WTRiASExtDataEngine& pTRiASExportEngine, 
	CComBSTR& strCapability, DWORD& dwFlag, DWORD& dwCapability) 
{
	long	lRes;
	RETURN_FAILED_HRESULT( pTRiASExportEngine->get_Capability( strCapability, &lRes ) );
	if( lRes ) 
		dwCapability |= dwFlag;
	else 
		dwCapability &= ~dwFlag;

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////////////
////////// KK000305 /////////////////////////////////////////////////////////////////
bool CPrjMap::InsertObject (long lONr)
{
HPROJECT hPr = DEX_GetObjectProject(lONr);
iterator it = find(hPr);

	if (it != end()) {
	// nicht erstes Objekt dieser DQ
		/**/;
	} else {
	// erstes Objekt dieser DQ
	pair<iterator, bool> p = insert (value_type(hPr, CObjsFromProject()));

		it = p.first;
		// p.second ==> success
	}

size_t lCnt = (*it).second.size();
	
	(*it).second.push_back(lONr);
	return lCnt+1 == (*it).second.size();
}
/////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------
void CExportPropertyAction:: ScreenContObj_Erase(void)		// Objekt löschen
{

	if (m_lScreenContObj != 0) {
		if (DEX_DeleteObject(m_lScreenContObj))
			m_lScreenContObj = 0;
	}

}

/////////////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CExportPropertyAction::EndAction (DWORD, IDataObject **ppDataObject) 
{
	COM_TRY {
		CHECKOUTPOINTER(ppDataObject);
		_ASSERTE( m_pTRiASExtDataEngine.IsValid() );

	// was kann denn der Exporter so??
		typedef struct { 
			LPCOLESTR m_lpszCap; 
			DWORD m_dwFlag; 
		} EXP_CAPBILITY, *LPEXP_CAPBILITY;

		static EXP_CAPBILITY g_Capabilitys[] = {
			{ L"NeedRawCoordinates",	EXP_RAWCOORDINATES },
			{ L"NeedHeader",			EXP_HEADER },
			{ L"NeedExtendedFeatures",	EXP_FEATURES },
			{ L"NeedVisinfo",			EXP_VISINFO },
		
		// KK000225
			{ L"EC_StandardMerkmale",	EXP_STANDARDMERKMALE },
			{ L"EC_MerkmalDescription",	EXP_MERKMALDESCRIPTION },
			{ L"EC_IdentDescription",	EXP_IDENTDESCRIPTION },
			{ L"EC_Relationen",			EXP_RELATIONEN },

		// #HK020821
			{ L"EC_ObjectProperties",	EXP_OBJECTPROPERTIES },

			{ NULL, 0 }
		};

	DWORD	dwCapabilitys = 0;

		for( LPEXP_CAPBILITY pCap = g_Capabilitys; pCap->m_lpszCap; ++pCap ) 
		{
			CheckCapability(m_pTRiASExtDataEngine, CComBSTR(pCap->m_lpszCap), 
				pCap->m_dwFlag, dwCapabilitys);
		}

#if !defined(_DEBUG)  && _TRiAS_VER < 0x0510
		if (!(QMSysAdmin & DEX_QueryMode()))
			dwCapabilitys &= ~EXP_OBJECTPROPERTIES;
		else
#endif // !defined(_DEBUG)
			dwCapabilitys |= EXP_OBJECTPROPERTIES;

	// eigentliche Verarbeitung
	CTRiASXMLDocument	xmlDocument;		// hier wird alles reingestopft
	DOUBLEBUF			dblBuf;				// Hilfspuffer


		WEnumLONG EnumOut (CLSID_EnumObjectsByNumber);		// Ausgabeobjektmenge
		{
			m_nMaxObjects = m_Objects.Count();
			OutEnumLONG iter_out (static_cast<IEnum<LONG> *>(EnumOut));

		// Statusanzeige
		DWORD	dwFlags;
		
			GetType(&dwFlags);
			dwFlags |= PIFLAGS_RESULT;
			SetType(dwFlags);
			SetMaxTicks(m_nMaxObjects);

		// der eigentliche Exporter

			m_lScreenContObj = 0L;	// kein Bildauschnitt-Objekt

			{
			CComQIPtr<ITRiASCS> CS;

#if _TRiAS_VER >= 0x0510
			// ask for selected coordsystem
				m_pSelCsDlg->GetSelectedCS(&CS);
#endif

			CExportPropertyActionWorker	exporter(xmlDocument, dblBuf, iter_out, 
				*this, dwCapabilitys, CS);

				RETURN_FAILED_HRESULT(exporter.Initialize());

			// KK000831
				if (m_bSelect)
					RETURN_FAILED_HRESULT(exporter.SetActiveSelection());

			// bricht ab, wenn ein Fehler auftritt (im Gegensatz zu for_each())
			bool fResult = boolop_and(CPrjMapInputIter(&m_Objects), CPrjMapInputIter(), exporter);

	//			if (m_bSelect)
	//				RETURN_FAILED_HRESULT(exporter.DeleteActiveSelection(m_lCounter));

//				RETURN_FAILED_HRESULT(exporter.End (ENDMODE_End));
			}

			ObjectDataExport (xmlDocument, -1, ENDMODE_End);	// End setzen

			if ( m_bSelect )		// Falls Bildausschnitt
				ScreenContObj_Erase();		// Objekt löschen
			

		} // iter_out goes out of scope

	// KK000107
		DELETE_OBJ(m_pCfgDlg);
		DELETE_OBJ(m_pObjPropDlg);
		DELETE_OBJ(m_pSelCsDlg);

	// KK991111 - für lange Dateinamen
		RETURN_FAILED_HRESULT(CopyExportFilesEx());

		m_pTRiASExtDataEngine->put_Filename(m_strWunschFile);

	__Interface<IDataObject> DO (CLSID_DataTransferObject);
	
		THROW_FAILED_HRESULT(SetEnumObjects (EnumOut, DO));
		*ppDataObject = DO.detach();

	// MCodes freigeben
		m_mapCodes.erase();

	} COM_CATCH;
	return S_OK;
}

//---------------------------------------------------------------------
BOOL FAR PASCAL MerkmalExport(long lMCode, BOOL bNotLast, void* pVoid) 
{
WTRiASExtDataEngine pData = *(WTRiASExtDataEngine *) pVoid;
PBDMERKMAL Data;
char _buf[_MAX_PATH] = { '\0' };

	INITSTRUCT(Data, PBDMERKMAL);  // init.
	Data.pbdKText = _buf;
	Data.pbdKTextLen = sizeof(_buf) - 1;
	Data.pbdTyp = 'm';                          // Merkmal
	Data.pbdCode = lMCode;

ErrCode EC = DEX_GetPBDData (Data);

	if ( EC != EC_OKAY && EC != WC_RETURN)
		return TRUE;

short locMTyp = toupper (Data.ipbdMTyp & ~(PBDMERKMAL_SYSTEMFLAG|PBDMERKMAL_READONLY));

	if ('A' != locMTyp && 'I' != locMTyp && 'F' != locMTyp) {
		_ASSERTE('A' == locMTyp || 'I' == locMTyp || 'F' != locMTyp);
		return TRUE;	// unbekannter Datentyp
	}
	if (Data.ipbdMTyp & PBDMERKMAL_SYSTEMFLAG)
		return TRUE;	// keine systeminternen Attribute exportieren

WTRiASOEProxy	pTRiASOEProxy;
HRESULT hr = pData->QueryInterface(pTRiASOEProxy.ppi());

	hr = pTRiASOEProxy->ExportMerkmalDescription (lMCode, locMTyp, Data.ipbdMLen, _buf);
	return TRUE;
}

//---------------------------------------------------------------------------
BOOL GetIdentVI( long lIdent, short iVTyp, VISINFO *vi ) {
	HANDLEVISINFO	HVI;
	INITSTRUCT(HVI,HVI);
	HVI.m_lIdent = lIdent;
	HVI.m_iVTyp = iVTyp;
	HVI.m_pVI = vi;
	return DEX_GetIdentVisInfo( HVI );
//	BOOL bRes = DEX_GetIdentVisInfo( HVI );
//	if( FALSE == bRes ) {
//		GetDefault( vi );
//		vi->dwSize = 0;	// nicht mit ausgeben
//	}
}

//---------------------------------------------------------------------
BOOL FAR PASCAL IdentifikatorExport( long lIdent, BOOL bNotLast, void* pVoid ) 
{
WTRiASExtDataEngine pData = *(WTRiASExtDataEngine *) pVoid;
PBDMERKMAL Data;

	INITSTRUCT(Data, PBDMERKMAL);

char _buf[_MAX_PATH] = { '\0' };
char _lbuf[_MAX_PATH] = { '\0' };
char _DEXBUF[_MAX_PATH] = { '\0' };

	Data.pbdKText = _buf;
	Data.pbdKTextLen = sizeof(_buf) - 1;
	Data.pbdLText = _lbuf;
	Data.pbdLTextLen = sizeof(_lbuf) - 1;
	Data.pbdTyp = 'i';                          // Merkmal
	Data.pbdCode = lIdent;

ErrCode EC = DEX_GetPBDData (Data);

	if (EC != EC_OKAY && EC != WC_RETURN)
		return TRUE;

HRESULT	hr = ClassFromIdentX (lIdent, _DEXBUF, sizeof(_DEXBUF));	// zugehöriger Klassenname
WTRiASOEProxy	pTRiASOEProxy;

	hr = pData->QueryInterface(pTRiASOEProxy.ppi());

long lVisType = 0;
PVISINFO PVI;
LVISINFO LVI;
FVISINFO FVI;
TVISINFO TVI;

// KK001023 - Versuch

short iVTyp = VT_Flaeche;
short iRTyp = DEX_GetIdentObjTypes(lIdent);

	if (iRTyp & OTFlaeche) {
		iVTyp = VT_Flaeche;
		GetIdentVI (lIdent,iVTyp,&FVI.m_VI);
		lVisType = OT_FLAECHE;
		hr = pTRiASOEProxy -> ExportIDDescription(_DEXBUF, _buf, _lbuf, lVisType, (DWORD *)&FVI.m_VI, lIdent);
	}
	if (iRTyp & OTLinie) {
		iVTyp = VT_Linie;
		GetIdentVI (lIdent,iVTyp,&LVI.m_VI);
		lVisType = OT_KANTE;
		hr = pTRiASOEProxy-> ExportIDDescription(_DEXBUF, _buf, _lbuf, lVisType, (DWORD *)&LVI.m_VI, lIdent);
	}
	if (iRTyp & OTPunkt) {
		iVTyp = VT_Punkt;
		GetIdentVI (lIdent,iVTyp,&PVI.m_VI);
		lVisType = OT_PUNKT;
		hr = pTRiASOEProxy-> ExportIDDescription(_DEXBUF, _buf, _lbuf, lVisType, (DWORD *)&PVI.m_VI, lIdent);
	}
	if (iRTyp & OTText) {
		iVTyp = VT_Text;
		GetIdentVI (lIdent,iVTyp,&TVI.m_VI);
		lVisType = OT_TEXT;
		hr = pTRiASOEProxy-> ExportIDDescription(_DEXBUF, _buf, _lbuf, lVisType, (DWORD *)&TVI.m_VI, lIdent);
	}
	return TRUE;
}
//-------------------------------------------------------------------------

// KK000225
// Exportieren der Beschreibung eines Merkmales -------------------------------
bool CExportPropertyAction::ExportMerkmal (BOOL fExportObjProps) 
{
	if (fExportObjProps) {
		COM_TRY {
		WObjectProps Props;
		WEnumObjProps IEnum;

			THROW_FAILED_HRESULT(GetObjectProps (Props.ppi()));
			THROW_FAILED_HRESULT(Props->EnumObjectProps(IEnum.ppi()));

		// Objekteigenschaften durchgehen
		WObjectProperty IProp;
		char cbPropInfo[_MAX_PATH];

			for (IEnum -> Reset(); S_OK == IEnum -> Next (1, IProp.ppu(), NULL); /**/)
			{
			// vollständigen Namen und Flags geben lassen
			DWORD dwFlags = 0L;
			HRESULT hr = IProp -> GetPropInfo (cbPropInfo, sizeof(cbPropInfo), &dwFlags);

				if (FAILED(hr) || !MustExportFeature(cbPropInfo))
					continue;

				if (dwFlags & (PROPCAPS_INTERACTIVE|PROPCAPS_INTERACTIVE_INIT))
					continue;		// keine interaktiven Attribute exportieren

			WTRiASOEProxy pTRiASOEProxy(m_pTRiASExtDataEngine);
			WPropertyInfo3 PropInfo3;
			HFEATURE hFeature = INVALID_HFEATURE;
			CComVariant vMCode;
			WEnumLONG EnumFeats;

				if (SUCCEEDED(IProp->QueryInterface(PropInfo3.ppi())) &&
					SUCCEEDED(PropInfo3->GetEnumConfigData(
						reinterpret_cast<IEnumLONG **>(EnumFeats.ppi()))))
				{
					for (EnumFeats->Reset(); 
						 S_OK == EnumFeats->Next(1, &hFeature, NULL);
						 /**/)
					{
						_ASSERTE(INVALID_HFEATURE != hFeature);

						THROW_FAILED_HRESULT(pTRiASOEProxy->ExportMerkmalDescription (
							hFeature, 'A', 255, cbPropInfo));
					}
				} 
				else {
				// einen eigenen MCode vergeben, wenn keiner da ist
				os_string strName (cbPropInfo);
				CFeatureCodes::iterator it = GetCodes().find(strName);

					if (it == GetCodes().end()) {
					
						hFeature = DEX_GetUniqueMCode();
						GetCodes().insert(CFeatureCodes::value_type(strName, hFeature));
					} else 
						hFeature = (*it).second;

					_ASSERTE(INVALID_HFEATURE != hFeature);
					THROW_FAILED_HRESULT(pTRiASOEProxy->ExportMerkmalDescription (
						hFeature, 'A', 255, cbPropInfo));
				}
			}

		} COM_CATCH_RETURN(false);
		return true;
	}
	else{
	ENUMNOKEY ENK;

		ENK.eFcn = (ENUMNOKEYPROC) MerkmalExport;
		ENK.ePtr = &m_pTRiASExtDataEngine;
		return DEX_EnumMCodes (ENK);
	}
}

//-------------------------------------------------------------------------
// KK000225
// Exportieren der Beschreibung einer Objektklasse ------------------------
bool CExportPropertyAction:: ExportIdentifikator (void) 
{
// Ich brauche ein Flag, daß mir die ExportArt 
//	(ganze Datenquelle bzw.nur OK einer Sicht) beschreibt !!!
// 
//short iEAFlag = true;

//	if (iEAFlag) {
	ENUMNOKEYLONG ENL;		// Alle O'Klassen der DB formal durchzählen und Baum anlegen

		ENL.eFcn = (ENUMNOKEYLONGPROC) IdentifikatorExport;
		ENL.ePtr =  &m_pTRiASExtDataEngine;
//		HPROJECT hPr = DEX_GetDataSourceHandle();
//		DEX_EnumClasses(hPr,ENL);
		return DEX_EnumIdents(ENL);
//	} 
//	else {
////	Alle O'Klassen der Sicht formal durchzählen und Baum anlegen
//		ENUMTEXTKEY ENT;
////		ENT.eKey = "__DefaultVisInfo__";	// DefaultSicht
//		ENT.eKey = NULL;	// NULL = aktuelle Sicht
////	Bestimmen der Anzahl der Objektklassen
//		ENT.eFcn = ( ENUMTEXTKEYPROC) IdentifikatorExport;
//		ENT.ePtr =  &m_pTRiASExtDataEngine;
//		DEX_EnumSightIdents(ENT);
//	}
//	return true;
}


//-------------------------------------------------------------------------
// KK000128 
HRESULT CExportPropertyAction::ObjectDataExport(CTRiASXMLDocument& xmlDocument, long nCounter, ENDMODE rgMode)
{
// jetzt der eigentliche Export
WDispatch pDispatch;

	ERROR_FAILED_HRESULT(xmlDocument->QueryInterface(pDispatch.ppi()), E_NOINTERFACE);

HRESULT hr = m_pTRiASExtDataEngine->ExportData(pDispatch);

	if( E_NOTIMPL == hr ) { 
	WTRiASOEProxy pTRiASOEProxy;

		ERROR_FAILED_HRESULT( m_pTRiASExtDataEngine->QueryInterface(pTRiASOEProxy.ppi()), EPA_E_INVALIDEXPORTENGINE );

	/*	MIDL: Marshaling OLE Data Types
		The following OLE handles are also defined with the wire_marshal attribute, but 
		only as handles within a machine since they cannot be used in remote procedure 
		calls to other machines at this time: HWND, HMENU, HACCEL, HDC, HFONT, HICON, HBRUSH. 
		Import the objidl.idl file into your IDL file and link to ole32.lib at build time 
		to use these handles in interprocess communication on a single machine. 
		The helper routines for these data types may change to include support for remote 
		marshaling in a future release. 
	*/
		RemotableHandle	hWndM;
		hWndM.fContext = WDT_INPROC_CALL;
		hWndM.u.hInproc = (long) __hWndM;

		if (nCounter < 0)		// Ende der Abarbeitung
			hr = pTRiASOEProxy->ExportDataEnd (rgMode);
		else
			hr = pTRiASOEProxy->ExportData( pDispatch, &hWndM ,nCounter);
	}
	return hr;
}
//------------------------------------------------------------------------

HRESULT CExportPropertyAction::UpdateStatus( long nObjects ) 
{
	TCHAR	fmtBuf[_MAX_PATH];
	wsprintf( fmtBuf, _T("%d / %d"), nObjects, m_nMaxObjects );
	m_pProgressIndicator->ChangeText( PIFLAG_RESULT, fmtBuf );
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// CPersistStreamInitImpl

#include <Com/VariantHelpers.h>
#include <Com/StreamHelpers.h>
#include <Com/GUIDHelpers.h>

namespace {
	inline 
	HRESULT LoadItem (IStream *pIStm, char *pBuffer, size_t iLen)
	{
	size_t iCnt = 0;

		RETURN_FAILED_HRESULT(pIStm->Read(&iCnt, sizeof(size_t), NULL));
		_ASSERTE(iCnt <= iLen);
		RETURN_FAILED_HRESULT(pIStm->Read(pBuffer, iCnt, NULL));
		return S_OK;
	}

	inline
	HRESULT LoadItem (IStream *pIStm, list<os_string> &rlist)
	{
	size_t iCnt = 0;

		RETURN_FAILED_HRESULT(pIStm->Read(&iCnt, sizeof(size_t), NULL));
		for (size_t i = 0; i < iCnt; ++i) {
		char cbBuffer[_MAX_PATH];

			RETURN_FAILED_HRESULT(LoadItem(pIStm, cbBuffer, sizeof(cbBuffer)));
			rlist.push_back(os_string(cbBuffer));
		}
		return S_OK;
	}

	inline 
	HRESULT SaveItem(IStream *pIStm, list<os_string> const &rlist) 
	{
	size_t iCnt = rlist.size();

		RETURN_FAILED_HRESULT(pIStm->Write(&iCnt, sizeof(size_t), NULL));

	list<os_string>::const_iterator end = rlist.end();

		for (list<os_string>::const_iterator it = rlist.begin(); it != end; ++it) {
			iCnt = (*it).size()+1;
			RETURN_FAILED_HRESULT(pIStm->Write(&iCnt, sizeof(size_t), NULL));
			RETURN_FAILED_HRESULT(pIStm->Write((*it).c_str(), iCnt, NULL));
		}
		return S_OK;
	}
}

HRESULT CExportPropertyAction::LoadData(LPSTREAM pStream, DWORD dwVersion ) 
{
	if (IsInitialized())
		return E_UNEXPECTED;

	COM_TRY {
	CLSID clsidLastUsed;	// zuletzt benutzte Engine

		RETURN_FAILED_HRESULT(CPropertyActionImpl::Load(pStream));
		LoadItem(pStream, clsidLastUsed);

	HRESULT hr = LoadEngines();

		if (FAILED(hr) && EPA_E_NOENGINESLOADED != hr)
			_com_issue_error(hr);

		m_pTRiASExtDataEngine.Assign(NULL);
		for(vector<WTRiASExtDataEngine>::iterator i = m_vecOfEngines.begin(); 
			m_vecOfEngines.end() != i; ++i) 
		{
		WPersist pPersist;
		CLSID clsid;

			if(FAILED((*i)->QueryInterface (pPersist.ppi())))
				continue;

			pPersist->GetClassID(&clsid);
			if (IsEqualGUID(clsid, clsidLastUsed))
				m_pTRiASExtDataEngine = *i;
		}

		LoadItem(pStream, m_bSeparate);
		LoadItem(pStream, m_bSelect);

		LoadItem(pStream, m_lstSelObjProps);

		SetInitialized();

	} COM_CATCH;
	return S_OK;
}

HRESULT CExportPropertyAction::SaveData( LPSTREAM pStream, BOOL bClearDirty ) 
{
	RETURN_FAILED_HRESULT(CPropertyActionImpl::Save (pStream, bClearDirty));

CLSID clsid;
WPersistStreamInit pPersistStreamInit;

	RETURN_FAILED_HRESULT(m_pTRiASExtDataEngine->QueryInterface(pPersistStreamInit.ppi()));
	pPersistStreamInit->GetClassID(&clsid);
	SaveItem(pStream, clsid);
	
	SaveItem(pStream, m_bSeparate);
	SaveItem(pStream, m_bSelect);

	SaveItem (pStream, m_lstSelObjProps);

	return S_OK;
}

LONGLONG CExportPropertyAction::GetDataSize() 
{
ULARGE_INTEGER uliSize;

	uliSize.QuadPart = 0;
	RETURN_FAILED_HRESULT(CPropertyActionImpl::GetSizeMax (&uliSize));
	uliSize.QuadPart += sizeof(CLSID) + 2*sizeof(BOOL);		// letzte Engine
	return uliSize.QuadPart;
}

HRESULT	CExportPropertyAction::OnInitNew() 
{
	COM_TRY {
		if (IsInitialized())
			return E_UNEXPECTED;

	HRESULT hr = LoadEngines();

		if (FAILED(hr) && EPA_E_NOENGINESLOADED != hr)
			_com_issue_error(hr);

		m_pTRiASExtDataEngine.Assign(NULL);
		SetInitialized();

		m_bSeparate = FALSE;
		m_bSelect = FALSE;
		m_lstSelObjProps.clear();

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Geokomponente hat eigenen Dialog
STDMETHODIMP CExportPropertyAction::AddConfigPages (
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
		m_pCfgDlg = CExportPropertyActionDlg::CreateInstance(cbCaption);
		ERROR_EXPR_TRUE(NULL == m_pCfgDlg, E_OUTOFMEMORY);

		m_pObjPropDlg = CSelectObjPropsToExport::CreateInstance(cbCaption);
		ERROR_EXPR_TRUE(NULL == m_pObjPropDlg, E_OUTOFMEMORY);

#if _TRiAS_VER >= 0x0510
		m_pSelCsDlg = CSelectCoordSysActionDlg::CreateInstance(cbCaption);
		ERROR_EXPR_TRUE(NULL == m_pSelCsDlg, E_OUTOFMEMORY);
#endif

		if (!IsNoShow()) {
		// Seiten hinzufügen, wenn selbige angezeigt werden sollen
		PROPSHEETPAGE psp;
		HPROPSHEETPAGE hPSP;
		long lCnt = 0;

			memcpy(&psp, &m_pCfgDlg->m_psp, sizeof(PROPSHEETPAGE));
			hPSP = ::CreatePropertySheetPage (&psp);
			if (NULL == hPSP) return E_HANDLE;
			if (!(*lpfnAddPage) (hPSP, lParam))
				return E_FAIL;
			lCnt++;

// ab Version 5.10 immer reingenerieren
#if !defined(_DEBUG) && _TRiAS_VER < 0x0510
			if (QMSysAdmin & DEX_QueryMode())
#endif // !defined(_DEBUG) && _TRiAS_VER < 0x0510
			{
			// Objekteigenschaften
				memcpy(&psp, &m_pObjPropDlg->m_psp, sizeof(PROPSHEETPAGE));
				hPSP = ::CreatePropertySheetPage (&psp);
				if (NULL == hPSP) return E_HANDLE;

				if (!(*lpfnAddPage) (hPSP, lParam))
					return E_FAIL;

				lCnt++;
				m_pCfgDlg->m_pObjPropDlg = m_pObjPropDlg;
				m_pObjPropDlg->SetSelectedObjProps(m_lstSelObjProps);
				m_fCreated2ndPage = true;
			}

#if _TRiAS_VER >= 0x0510
		// Koordinatensysteme
			memcpy(&psp, &m_pSelCsDlg->m_psp, sizeof(PROPSHEETPAGE));
			hPSP = ::CreatePropertySheetPage (&psp);
			if (NULL == hPSP) return E_HANDLE;
			if (!(*lpfnAddPage) (hPSP, lParam))
				return E_FAIL;
			lCnt++;
			m_pCfgDlg->m_pSelCsDlg = m_pSelCsDlg;
			m_fCreated3rdPage = true;
#endif

			m_pCfgDlg->m_bSeparate = m_bSeparate;
			m_pCfgDlg->m_bSelect = m_bSelect;

			if (puiCnt) 
				*puiCnt = lCnt;		// wir haben ein/zwei Pages hinzugefügt
		} 

	} COM_CATCH_OP((delete m_pCfgDlg, delete m_pObjPropDlg, delete m_pSelCsDlg));
	return S_OK;
}  

///////////////////////////////////////////////////////////////////////////////
// Helferfunktion zum Laden aller bekannten Exportengines

HRESULT CExportPropertyAction::LoadEngines() 
{
	m_vecOfEngines.clear();
	m_mapOfRegisteredEngines.clear();
	RETURN_FAILED_HRESULT(::LoadEngines (m_mapOfRegisteredEngines));
	if (0 == m_mapOfRegisteredEngines.size()) 
		return EPA_E_NOENGINESLOADED;

	for(map<CLSID, WTRiASExtDataEngine, less<CLSID> >::iterator i = m_mapOfRegisteredEngines.begin(); 
		m_mapOfRegisteredEngines.end() != i; ++i ) 
	{
		m_vecOfEngines.push_back((*i).second);
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// 
BOOL CExportPropertyAction::MustExportFeature(LPCSTR pcName)
{
list<os_string>::iterator end = m_lstSelObjProps.end();

	for (list<os_string>::iterator it = m_lstSelObjProps.begin(); it != end; ++it)
	{
		if (!stricmp((*it).c_str(), pcName))
			return true;	// found --> export
	}
	return false;		// not found --> do not export
}


