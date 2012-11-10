// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 02.11.2000 16:14:08 
//
// @doc
// @module MapImport.cpp | Definition of the <c CMapImport> class

#include "stdafx.h"

#include <math.h>
#include <ospace/file/path.h>

#include "MapMgr.h"
#include "resource.h"
#include "ImportDlg.h"

#include <istatus.h>
#include <defattr.h>

#include <initguid.h>

#include <statguid.h>
#include <REGISTRX.HXX>

#include "MapImport.h"

#pragma warning (disable: 4192)	// automatically excluding 'bla' while importing type library 
#import "tlb/VisInfo.tlb" raw_interfaces_only raw_dispinterfaces no_namespace named_guids

DEFINE_GUID(CLSID_ProgressIndicator, 0x07963819L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);

DefineSmartInterface(ProgressIndicator)
DefineSmartInterface(VisObjExt)
DefineSmartInterface2(DVisInfo, IID_DVisInfo);
DefineSmartInterface(ExtendedObjectVisInfo);

/////////////////////////////////////////////////////////////////////////////
// für XtensionBasisLib benötigte globale Funktionen

// Liefert den CLSID des TRiAS-Zusatzmodules MapMgr
BOOL GetExtensionCLSID (CLSID &rClsID)
{
	rClsID = CLSID_MapImport;
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// 
CMapImport::CMapImport()
{
	AfxEnableControlContainer();
}

///////////////////////////////////////////////////////////////////////////
// InitExtension wird nach erfolgreichem Laden des Zusatzmodules gerufen 
STDMETHODIMP_(BOOL) CMapImport::InitExtension (short iMode) 
{
	if (!CTriasExtension::InitExtension (iMode))
		return FALSE;

	m_strDstDir.Empty();

//CString	myIniSection, myIniEntry;
//
//	VERIFY(myIniSection.LoadString(IDS_MYINISECTION));
//	VERIFY(myIniEntry.LoadString(IDS_MAPDIRENTRY));
//
//CString	strMapDir;
//char ch;
//
//	for(int i = 1; /**/; ++i) {
//		strMapDir.Format ("%s%d", (LPCTSTR) myIniEntry, i);
//		strMapDir = GetMyProfileString( myIniSection, strMapDir, m_strDstDir); // myIniEntry + (char) ( '1' + i ) );
//		if (strMapDir.IsEmpty())
//			break;
//
//		if ('\\' != (ch = strMapDir[ strMapDir.GetLength() - 1 ]) && '/' != ch )
//			strMapDir += '\\';
//		strMapDir.MakeLower();
//	}

// KK010314
	InstallMainMenu();	// Menü ins ExtraMenü einhängen

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// UnLoadExtension wird vor dem Entladen des Zusatzmodules gerufen
STDMETHODIMP_(BOOL) CMapImport::UnLoadExtension (void) 
{
	RemoveMainMenu();
	return CTriasExtension::UnLoadExtension();
}

///////////////////////////////////////////////////////////
// Einbau der Menüpunkte in das Extras-Menü
bool CMapImport::InstallMainMenu()
{
INSTALLMENUITEM imi;

	INITSTRUCT(imi, INSTALLMENUITEM);
	imi.hDex = hDex();
	imi.iMenuID = ID_MAPIMPORT;
	imi.iFlag = IMINormalMenu;
	imi.iMenuNum = EXTRA_MENU_POS;
	imi.iMenuPos = 2;

CString S;

	S.LoadString(IDS_IMPORTMENU);
	imi.pMenuText = (LPTSTR)(LPCTSTR)S;
	return (NULL != DEX_InstallMenuItem (imi)) ? TRUE : FALSE;
}

//////////////////////////////////////////////////////////////////////
//
void CMapImport::RemoveMainMenu()
{
REMOVEMENUITEM rmi;

	INITSTRUCT(rmi, REMOVEMENUITEM);
	rmi.hDex = hDex();
	rmi.iMenuID = ID_MAPIMPORT;
	rmi.iMenuNum = EXTRA_MENU_POS;
	rmi.iFlag = IMINormalMenu;
	DEX_RemoveMenuItem (rmi);
}

/////////////////////////////////////////////////////////////////////////////
// Die eigentlichen Arbeitstiere
LRESULT CMapImport::OnMapImport(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) 
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());

CWaitCursor wait;
CMapImportDlg dlg;

	dlg.m_strDstDir = m_strDstDir;
	wait.Restore();
	if (ID_WIZFINISH == dlg.DoModal()) {
	bool fReturn = false;

		if (dlg.m_bMulti)
			fReturn = DoMultiImport(dlg);
		else
			fReturn = DoTheImport(dlg);

		if (!fReturn)
			return 0;

		dlg.CorrectDirectory();
		if (!dlg.m_strDstDir.IsEmpty() && m_strDstDir != dlg.m_strDstDir) {
		CString	myIniSection, myIniEntry;

			VERIFY(myIniSection.LoadString(IDS_MYINISECTION));
			VERIFY(myIniEntry.LoadString(IDS_MAPDIRENTRY));

		CString	strMapDir;
		char ch;
			
			for (int i = 1; /**/; ++i) {
				strMapDir.Format("%s%d", (LPCTSTR)myIniEntry, i);
				strMapDir = GetMyProfileString(myIniSection, strMapDir, m_strDstDir); // myIniEntry + (char) ( '1' + i ) );
				if (strMapDir.IsEmpty())
					break;

				m_strDstDir = dlg.m_strDstDir;
				strMapDir.MakeLower();
				m_strDstDir.MakeLower();

				if (m_strDstDir == strMapDir)
					break;

				if ('\\' != (ch = strMapDir[strMapDir.GetLength() - 1]) && '/' != ch)
					strMapDir += '\\';
			}
			strMapDir.Format("%s%d", (LPCTSTR)myIniEntry, i);
			WriteProfileString(myIniSection, strMapDir, (LPCTSTR)dlg.m_strDstDir);
		}

		m_strDstDir = dlg.m_strDstDir;

	// Ansicht sicher auswählen
	char cbView[_MAX_PATH];

		if (NULL == DEX_GetActiveSight (cbView)) {
		// Neue Ansicht erzeugen und auswählen
		CString str;

			VERIFY(str.LoadString(IDS_VIEWNAME));
			strcpy (cbView, (LPCTSTR)str);
		}

		DEX_SelectNewSight(cbView);
		DEX_RebuildSight();
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////////
bool CMapImport::WriteProfileString(LPCSTR lpszSection, LPCSTR lpszEntry, LPCSTR lpszValue) 
{
	ASSERT(lpszSection != NULL);
	ASSERT(lpszEntry != NULL);

CString	S;
HPROJECT hPr = DEX_GetDataSourceHandle();

	DEX_GetDataSourceName(hPr, S.GetBufferSetLength(_MAX_PATH));

	S.ReleaseBuffer(-1);

CPath pathOfIni(S);

	pathOfIni.Suffix(".ini");
	return ::WritePrivateProfileString(lpszSection, lpszEntry, lpszValue, pathOfIni.Path());
}

/////////////////////////////////////////////////////////////////////////////////////
//
CString CMapImport::GetMyProfileString(LPCSTR lpszSection, LPCSTR lpszEntry, LPCSTR lpszDefault) 
{
	ASSERT(lpszSection != NULL);

CString	S;
HPROJECT hPr = DEX_GetDataSourceHandle();

	DEX_GetDataSourceName(hPr, S.GetBufferSetLength(_MAX_PATH));

	S.ReleaseBuffer(-1);
	
CPath pathOfIni(S);
	
	pathOfIni.Suffix(".ini");
	::GetPrivateProfileString(lpszSection, lpszEntry, lpszDefault, S.GetBufferSetLength(_MAX_PATH), _MAX_PATH - 2, pathOfIni.Path());
	S.ReleaseBuffer(-1);
	return S;
}

///////////////////////////////////////////////////////////////////////////////////
//
bool CMapImport::DoTheImport(CMapImportDlg& dlg) 
{
// KK001108
double XDiff[4];
double YDiff[4];
double Z;

	for (long j = 0; j < 4 ; j++) {
		XDiff[j] = 0.0;
		YDiff[j] = 0.0;
	}

SAFEARRAY *pCoords = NULL;
HRESULT	hr = dlg.m_pTopoMap->GetDifferenz(&pCoords);

	_ASSERTE(S_OK == hr);
	if (S_OK != hr)
		return false;

MC::ArrayDouble	geoPoints(pCoords);
UINT arrIdx, coord;
	
	_ASSERTE(geoPoints.Elements() == 4 * 3);
	geoPoints.Lock();
	for (coord = 0, arrIdx = 0; coord < 4; coord++) {
		XDiff[coord] = geoPoints[arrIdx++];
		YDiff[coord] = geoPoints[arrIdx++];
		Z = geoPoints[arrIdx++];
	}
	geoPoints.Unlock();

GCPList::iterator g = dlg.m_gcpList.begin();
double X[5];
double Y[5];

	X[4] = (*g).m_ptGeoCoord.X;
	Y[4] = (*g).m_ptGeoCoord.Y;
	for (int i = 0; i < 4 && dlg.m_gcpList.end() != g; ++i, ++g) {
		X[i] = (*g).m_ptGeoCoord.X;
		Y[i] = (*g).m_ptGeoCoord.Y;
	}
	_ASSERTE(4 == i);

// Identifikator definieren
CString MK;
CString MT;

	VERIFY(MT.LoadString (IDS_OBJKLASSE));
	VERIFY(MK.LoadString (IDS_OKLKEY));

long lIdent = GetIdentifikator(dlg.m_hPr, MK, MT);

	if (0 == lIdent)
		return false;

long objNum = CreateArea (lIdent, 5, X, Y, dlg.m_pCS);

	if (0 == objNum)
		return false;

// UniqueIdent
	VERIFY(MK.LoadString (IDS_UIDCODE));
	VERIFY(MT.LoadString (IDS_UNIQUEIDENT));

long lMUIDCode = atol (MK);

	if (SetObjectFeature (lMUIDCode, lIdent, MT)) {
		if(!ModifyObjectFeature (objNum, lMUIDCode, dlg.m_strIdent))
			return false;
	} else 
		return false;

// Objektname
	VERIFY(MK.LoadString (IDS_OBJNAMECODE));
	VERIFY(MT.LoadString (IDS_OBJNAME));

long lMObjCode = atol (MK);

	if (SetObjectFeature (lMObjCode, lIdent, MT)) {
		if (!ModifyObjectFeature (objNum, lMObjCode, dlg.m_strName))
			return false;
	} else
		return false;

CString S;
CPath pathOfPict(dlg.m_strSrcMap);
CComBSTR bstrToWrite;

	USES_CONVERSION;

	hr = dlg.m_pTopoMap->CorrectName(CComBSTR(dlg.m_strDstDir), 
		CComBSTR(pathOfPict.FileName()), &bstrToWrite);

	S.Format( _T("%s %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld"),
		SUCCEEDED(hr) ? OLE2A(bstrToWrite) : (LPCTSTR)pathOfPict.FileName(),
		dlg.m_sizeOfPicture.cx,	dlg.m_sizeOfPicture.cy,
		(long)XDiff[0], (long)YDiff[0],
		(long)XDiff[1], (long)YDiff[1],
		(long)XDiff[2], (long)YDiff[2],
		(long)XDiff[3], (long)YDiff[3]);

// TKInfo
	VERIFY(MK.LoadString (IDS_TKINFOCODE));
	VERIFY(MT.LoadString (IDS_TKINFO));

long lMCode = atol (MK);
long lVisMCode = lMCode;

	if (SetObjectFeature (lMCode, lIdent, MT)) {
		if (!ModifyObjectFeature (objNum, lMCode, S))
			return false;
	} else 
		return false;

#if defined(_DEBUG)
	for (int k = 1; dlg.m_gcpList.end() != g; ++g, ++k) {

		objNum = CreatePoint (lIdent, (*g).m_ptGeoCoord.X, (*g).m_ptGeoCoord.Y, dlg.m_pCS);
		S.Format (_T("%s.Punkt.%d"), dlg.m_strIdent, k);

		ModifyObjectFeature(objNum, lMUIDCode,  S);
		ModifyObjectFeature(objNum, lMObjCode,  S);
	}
#endif // defined(_DEBUG)

// objektbezogene Visualisierung erzeugen
	SetObjVisInfo(lIdent, objNum, lVisMCode);

	DEXN_ReScale();
	DEXN_ReReadIdents();
	DEXN_ReReadContainer();
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// objektbezogene Visualisierung erzeugen
HRESULT CMapImport::SetObjVisInfo (long lIdent, long lONr, long lMCode)
{
	COM_TRY {
	// zuerst ggf. Ansicht erzeugen
	char cbView[_MAX_PATH];

		if (NULL == DEX_GetActiveSight (cbView)) {
		// Neue Ansicht erzeugen und auswählen
		CString str;

			VERIFY(str.LoadString(IDS_VIEWNAME));
			DEX_CreateView((LPCTSTR)str);
			DEX_SelectNewSight((LPCTSTR)str);
		}

	WVisObjExt VisObjExt;
	WDVisInfo Vis;

		THROW_FAILED_HRESULT(m_pXtnSite -> GetXtension (
			CLSID_ObjVisInfoExtension, IID_IVisObjExt, VisObjExt.ppv()));

	// Objektklasse
	int iPriority = DEF_PRIORITY_FLAECHE;

		THROW_FAILED_HRESULT(VisObjExt -> GetVisInfoClass(lIdent, 
			VISINFOTYPE_Area, vtMissing, Vis.ppi()));
		THROW_FAILED_HRESULT(Vis -> get_Priority(&iPriority));
		if (DEF_PRIORITY_FLAECHE == iPriority) {
		// Rasterkarten ganz nach hinten und nicht recherchierbar
			THROW_FAILED_HRESULT(Vis -> put_Priority(1));
			THROW_FAILED_HRESULT(Vis -> put_Locatable(VARIANT_FALSE));
		}
		THROW_FAILED_HRESULT(VisObjExt -> SetVisInfoClass(lIdent, 
			VISINFOTYPE_Area, Vis, vtMissing));

	// objektbezogene Darstellungsparameter schreiben
		THROW_FAILED_HRESULT(VisObjExt -> GetVisInfoObject(lONr, 
			VISINFOTYPE_Area, vtMissing, Vis.ppi()));

		THROW_FAILED_HRESULT(Vis -> put_Style(10));
		THROW_FAILED_HRESULT(Vis -> put_Name(CComBSTR("Standardfarben;0;0;")));

	WExtendedObjectVisInfo ExtVI (Vis);
	CString strInfo;

		strInfo.Format ("%%%d", lMCode);
		THROW_FAILED_HRESULT(ExtVI -> put_ModuleInfo(CComBSTR("karten")));
		THROW_FAILED_HRESULT(ExtVI -> put_ExtendedInfo(CComBSTR(strInfo)));

		THROW_FAILED_HRESULT(VisObjExt -> SetVisInfoObject(lONr, 
			VISINFOTYPE_Area, Vis, VARIANT_TRUE, vtMissing));

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////////
//
const LPCTSTR g_cbSecKey = 
	TEXT("Software\\") REG_COMPANY_KEY TEXT("\\") 
	REG_PRODUCT_KEY TEXT("\\Extensions\\TRiAS.MapMgr.Import.1\\Config");

bool CMapImport::DoMultiImport(CMapImportDlg& dlg) 
{
DWORD dwNoReduce = 0;
CCurrentUser rgMASS(KEY_READ, g_cbSecKey);

	rgMASS.GetDWORD ("NoReduce", dwNoReduce);
	if (!dwNoReduce) dwNoReduce = dlg.m_bNoReduce;

long lNum = 0;
CString sText;

	sText.LoadString(IDS_INDICATORCAPTION);

WProgressIndicator pProgressIndicator;
long lMaxCount = (dlg.m_lMultiCount > 0) ? dlg.m_lMultiCount : 1;

	if (FAILED(pProgressIndicator.CreateInstance(CLSID_ProgressIndicator)))
		return false;

	pProgressIndicator->InitNew(MWind()->GetSafeHwnd(), PIFLAG_ALL);
	pProgressIndicator->Restart(0, lMaxCount, PIFLAG_ALL);
	pProgressIndicator->ChangeText(PIFLAG_CAPTION, sText);

bool fReturn = true;

	if (dlg.m_lMultiCount > 0) {
	// alle Karten importieren
		dlg.m_TopKart.reverse();
		for (list_char::iterator i = dlg.m_TopKart.begin(); i != dlg.m_TopKart.end(); ++i) {
			fReturn = DoImport (dlg, lNum, dwNoReduce, pProgressIndicator, (*i).c_str());
			if (!fReturn) 
				break;
		}
		dlg.m_TopKart.erase (dlg.m_TopKart.begin(), dlg.m_TopKart.end());
	}
	else {
	// eine Karte importieren
		fReturn = DoImport(dlg, lNum, dwNoReduce, pProgressIndicator, dlg.m_strSrcMap);
	}
	return fReturn;
}

bool CMapImport::DoImport(CMapImportDlg& dlg, long &rlNum, DWORD dwNoReduce, 
	IProgressIndicator *pProgressIndicator, LPCTSTR pcMap)
{
TCHAR fmtBuf[_MAX_PATH];
CString sText;

	pProgressIndicator->SetPosition(++rlNum);

	wsprintf(fmtBuf, _T("%d / %d"), rlNum, dlg.m_lMultiCount);
	pProgressIndicator->ChangeText(PIFLAG_RESULT, fmtBuf);

	wsprintf(fmtBuf, _T("%s "), pcMap);
	pProgressIndicator->ChangeText(PIFLAG_FILENAME, fmtBuf);

	if (dlg.m_lMultiCount > 0) {
		VERIFY(sText.LoadString(IDS_INDICATORSTATUS));
		wsprintf(fmtBuf, _T("%s "), sText);
		pProgressIndicator->ChangeText(PIFLAG_STATUS, fmtBuf);
		if (!OnMultiMap (dlg, pcMap)) 
			return false;
	}

	VERIFY(sText.LoadString(IDS_INDICATORTAGS));
	wsprintf(fmtBuf, _T("%s "), sText);
	pProgressIndicator->ChangeText(PIFLAG_STATUS, fmtBuf);
	if (!OnMultiTag (dlg)) 
		return false;

	VERIFY(sText.LoadString(IDS_INDICATORDOC));
	wsprintf(fmtBuf, _T("%s "), sText);
	pProgressIndicator->ChangeText(PIFLAG_STATUS, fmtBuf);
	if (!OnMultiDoc(dlg)) 
		return false;


	VERIFY(sText.LoadString(IDS_SETCOORDINATE));
	wsprintf(fmtBuf, _T("%s "), sText);
	pProgressIndicator->ChangeText(PIFLAG_STATUS, fmtBuf);
	if (!OnMapCoordinate(dlg)) 
		return false;

	if (!dwNoReduce) {
		VERIFY(sText.LoadString(IDS_MAPREDUCE));
		wsprintf(fmtBuf, _T("%s "), sText);
		pProgressIndicator->ChangeText(PIFLAG_STATUS, fmtBuf);
		if (!OnReduceMap (dlg)) 
			return false;
	}

	VERIFY(sText.LoadString(IDS_STOREMAP));
	wsprintf(fmtBuf, _T("%s "), sText);
	pProgressIndicator->ChangeText(PIFLAG_STATUS, fmtBuf);
	if (!DoTheImport(dlg)) 
		return false;

	return true;
}

///////////////////////////////////////////////////////////////////////////////////
// KK001120
bool CMapImport::OnMultiMap (CMapImportDlg& dlg, const char *sPath)  
{
TCHAR strDrive[_MAX_DRIVE];
TCHAR strDir[_MAX_DIR];
TCHAR strName[_MAX_FNAME];
TCHAR strExt[_MAX_EXT];

	USES_CONVERSION;

char sNew[_MAX_PATH];

	::_splitpath(dlg.m_strSrcMap, strDrive, strDir, strName, strExt);
	::_makepath(sNew, strDrive, strDir, sPath, "tif");

CString strPath = sNew;
CComQIPtr<IPictHolder, &IID_IPictHolder> p;

	_ASSERTE(dlg.m_pTopoPict);
	p = dlg.m_pTopoPict;

CComBSTR bstrFullName;

	if (SUCCEEDED(dlg.m_pTopoMap->MakeFullName(CComBSTR(strPath), &bstrFullName)) &&
		S_OK == p->OpenPictureFile(bstrFullName)) 
	{
	long bValid;
	
		dlg.m_pTopoMap->CheckPictureFile(dlg.m_pTopoPict, &bValid);
		dlg.m_strSrcMap = strPath;
	} 
	else {
	CString	S;

		S.Format(IDS_NOMAP, (LPCTSTR)strPath);
		::AfxMessageBox(S);
		dlg.m_strSrcMap.Empty();
		return false;
	}
	return true;
}

//////////////////////////////////////////////////////////////////////////////////
//
bool CMapImport::OnMultiDoc(CMapImportDlg& dlg) 
{
	_ASSERTE(dlg.m_pTopoMap);

CComBSTR STyp;
HRESULT hr = dlg.m_pTopoMap->GetAltFileTyp(&STyp);

	if (FAILED(hr) || 0 == STyp.Length()) {
	CString ST;
	
		ST.LoadString(IDS_HARDERROR);
		::AfxMessageBox( ST );
		return false;
	}

CString	S (dlg.m_strSrcMap);
COPYFLAG rgFlags = COPYFLAG_Default;

	hr = dlg.m_pTopoMap->CopyFlags(&rgFlags);
	if (FAILED(hr)) return false;

	if (!(COPYFLAG_SourceIsDirectory & rgFlags)) {
	os_path dir = (LPCTSTR)dlg.m_strSrcMap;

		USES_CONVERSION;
		dir.extension(OLE2A(STyp));
		S = (LPCTSTR)dir;
	}	

// Beschreibungsdatei-Name besorgen
long bValid = TRUE;
CComBSTR Sa(S);
	
	if (S_OK == dlg.m_pTopoMap->CheckAltFile(Sa, &bValid) && bValid) {
		dlg.m_strAddMap = Sa;
	} 
	else {
	CString	St;

		St.Format(IDS_NOMAPDOC, (LPCTSTR) S, (LPCTSTR) dlg.m_strMapType );
		::AfxMessageBox( St );
		dlg.m_strAddMap.Empty();
		return false;
	}

// Beschreibungsdatei-lesen
CComBSTR strName;
CComBSTR strIdent;

	hr = dlg.m_pTopoMap->GetNameAndIdent(CComBSTR(dlg.m_strSrcMap), &strName, &strIdent);
	_ASSERTE(S_OK == hr);
	if(S_OK != hr)
		return false;
	
	dlg.m_strName = strName;
	dlg.m_strIdent = strIdent;
	return true;
}

//////////////////////////////////////////////////////////////////////////////////
bool CMapImport::OnMultiTag(CMapImportDlg& dlg)  
{
	_ASSERTE(dlg.m_pTopoMap);

long bValid;

	if (S_OK == dlg.m_pTopoMap->CheckPictureFile(dlg.m_pTopoPict, &bValid) && bValid) {
	CComVariant	v;
	HRESULT	hr = dlg.m_pTopoPict->GetTagValue(256, &v);
	
		if(S_OK != hr)
			goto labelWrongPicture;
		
		dlg.m_sizeOfPicture.cx = v.lVal;
		hr = dlg.m_pTopoPict->GetTagValue(257, &v);
		if (S_OK != hr)
			goto labelWrongPicture;

		dlg.m_sizeOfPicture.cy = v.lVal;
		return true;
	}

labelWrongPicture:
CString S;

	S.Format(IDS_NOMAPTYPE, dlg.m_strSrcMap, dlg.m_strMapType);
	::AfxMessageBox(S);
	return false;
}

///////////////////////////////////////////////////////////////////////////////////
//
bool CMapImport::OnReduceMap(CMapImportDlg& dlg) 
{
CComQIPtr<IPictHolder,&IID_IPictHolder>	p;

	p = dlg.m_pTopoPict;
	p->Close();
	if (!dlg.ReduceMapFile()) {
	CString S;
	
		S.LoadString ( IDS_ERRORREDUCEMAP);
		::AfxMessageBox( S );
		return false;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////////
//
bool CMapImport::OnMapCoordinate(CMapImportDlg& dlg) 
{
SAFEARRAY	*pCoords = NULL;
HRESULT	hr = dlg.m_pTopoMap->GetCoordinates(&pCoords);

	_ASSERTE(S_OK == hr);
	if (S_OK != hr)
		return false;;
	
MC::ArrayDouble	geoPoints(pCoords);

	hr = dlg.m_pTopoMap->GetRefPoints(&pCoords);
	_ASSERTE(S_OK == hr);
	if (S_OK != hr)
		return false;

MC::ArrayDouble	picPoints(pCoords);

	_ASSERTE(geoPoints.Elements() == picPoints.Elements());
	_ASSERTE(0 == geoPoints.Elements() % 3 );
	_ASSERTE(geoPoints.Elements() >= 4);
	
long coord, nCoords = geoPoints.Elements() / 3, geoIdx, picIdx;

	dlg.m_gcpList.clear();

GCP	gcp;
int ptIndex = 1;

	for( coord = 0, geoIdx = 0, picIdx = 0; coord < nCoords; coord++ ) {
		gcp.m_ptGeoCoord.X = geoPoints[geoIdx++];
		gcp.m_ptGeoCoord.Y = geoPoints[geoIdx++];
		gcp.m_ptGeoCoord.Z = geoPoints[geoIdx++];
		gcp.m_ptPictPoint.X = picPoints[picIdx++];
		gcp.m_ptPictPoint.Y = picPoints[picIdx++];
		gcp.m_ptPictPoint.Z = picPoints[picIdx++];
		dlg.m_gcpList.push_back(gcp);
	}
	return true;
}


///////////////////////////////////////////////////////////////////////////////////
// TRiAS spezifische Funktionen
HOBJECT CMapImport::CreateArea (HOBJECTS ident, long nCoords, double *pX, 
	double *pY, ITRiASCS *pICS) 
{
OBJGEOMETRIE OG;

	INITSTRUCT(OG, OBJGEOMETRIE);
	OG.lIdent = ident;
	OG.iObjTyp = OGFlaeche;
	OG.iFlags = OGNewObject | OGConverted | OGForceGeometry | OGAddToView;
	OG.lCnt = nCoords;
	OG.iKCnt = 1;
	OG.pdblX = pX;
	OG.pdblY = pY;
	OG.plCnt = &nCoords;

HPROJECT hPr = DEX_GetObjectsProject(ident);
GEOMETRIEWITHCS GCS;

	INITSTRUCT(GCS, GEOMETRIEWITHCS);
	GCS.pICS = pICS;
	GCS.pOG = &OG;

	if (DEX_ModObjGeometrieEx (hPr, GCS)) 
		return OG.lONr;

	return INVALID_HOBJECT;
}

HOBJECT CMapImport::CreatePoint (HOBJECTS ident, double X, double Y, 
	ITRiASCS *pICS) 
{
long nPoints = 1;
OBJGEOMETRIE OG;

	INITSTRUCT(OG, OBJGEOMETRIE);
	OG.lIdent = ident;
	OG.iObjTyp = OGPunkt;
	OG.iFlags = OGNewObject | OGConverted | OGForceGeometry | OGAddToView;
	OG.lCnt = nPoints;
	OG.iKCnt = 1;
	OG.pdblX = &X;
	OG.pdblY = &Y;
	OG.plCnt = &nPoints;

HPROJECT hPr = DEX_GetObjectsProject(ident);
GEOMETRIEWITHCS GCS;

	INITSTRUCT(GCS, GEOMETRIEWITHCS);
	GCS.pICS = pICS;
	GCS.pOG = &OG;
	if (DEX_ModObjGeometrieEx (hPr, GCS)) 
		return OG.lONr;

	return INVALID_HOBJECT;
}

bool CMapImport::ModifyObjectFeature (HOBJECT objNum, HFEATURE lMCode, CString &rString) 
{
TARGETMERKMALEX	tm;

	INITSTRUCT(tm, TARGETMERKMALEX);
	tm.lTarget = objNum;
	tm.lMCode = lMCode;
	tm.imaxLen = rString.GetLength();
	tm.pMText = (LPTSTR)(LPCTSTR)rString;
	tm.iTTyp = TT_Objekt;
	tm.iFlags = TMNoCaching;
	return EC_OKAY == DEX_ModTextMerkmal(tm) ? true : false;
}

bool CMapImport::SetObjectFeature (HFEATURE &rlMCode, HOBJECTS lIdent, CString &rString) 
{
HPROJECT hPr = DEX_GetObjectsProject(lIdent);
PBDMERKMALEX pbdData;
MAPMCODETOHANDLE MMH;
HFEATURE lMCodeHandle = INVALID_HFEATURE;

	INITSTRUCT(MMH, MAPMCODETOHANDLE);
	MMH.lIdent = lIdent;
	MMH.lMCode = rlMCode;
	MMH.plHandle = &lMCodeHandle;
	MMH.fCreate = true;
	if (!DEX_MapOrCreateMCodeToHandle(hPr, MMH))
		return false;
	_ASSERTE(INVALID_HFEATURE != lMCodeHandle);
	rlMCode = lMCodeHandle;

char cbKText[33] = { '\0' };

	INITSTRUCT(pbdData, PBDMERKMALEX);
	pbdData.pbdTyp = 'm';
	pbdData.pbdCode = lMCodeHandle;
	pbdData.pbdKTextLen = sizeof(cbKText)-1;
	pbdData.pbdLTextLen = 0;
	pbdData.pbdKText = cbKText;
	pbdData.ipbdMTyp = MPObjectFeature;	// so tun, als ob's nur für Objekte wär
	pbdData.ipbdMLen = 256;
	pbdData.lIdent = lIdent;

	if (EC_OKAY == DEX_GetPBDDataEx (hPr, pbdData))
		return true;

ErrInstall EI (WC_NOMERKMAL);

	pbdData.pbdKText = (LPTSTR)(LPCTSTR)rString;
	pbdData.pbdKTextLen = rString.GetLength();
	if (EC_OKAY != DEX_ModPBDDataEx (hPr, pbdData))
		return false;
	else
		DEXN_PBDMCodeChanged (pbdData.pbdCode);

	return true;
}

HOBJECTS CMapImport::GetIdentifikator (HPROJECT hPr, CString &iString, CString &tString)
{
	if (HACTCONNECTION == hPr)
		hPr = DEX_GetDataSourceHandle();

ULONG lIdent = 0L;
HRESULT hr = IdentFromClassX (hPr, (LPTSTR)(LPCTSTR)iString, &lIdent, true);

	if (S_OK != hr && S_FALSE != hr)
		return INVALID_HOBJECTS;

char KText[33] = { '\0' };
PBDDATA pbdData;

	INITSTRUCT(pbdData, PBDDATA);
	pbdData.pbdTyp = 'i';
	pbdData.pbdCode = lIdent;
	pbdData.pbdKText = KText;
	pbdData.pbdKTextLen = sizeof(KText) -1;
	pbdData.pbdLTextLen = 0;

ErrInstall EI (WC_NOIDENT);

	if (EC_OKAY == DEX_GetPBDDataEx(hPr, pbdData)) 
		return HOBJECTS(lIdent);

	strncpy (KText, tString, sizeof(KText)-1);
	KText[sizeof(KText)-1] = '\0';

	pbdData.pbdLText = (LPTSTR)(LPCTSTR)tString;
	pbdData.pbdLTextLen = tString.GetLength();

	DEX_ModPBDDataEx (hPr, pbdData); 
	DEXN_PBDIdentsChanged();

	return HOBJECTS(lIdent);
}
