// $Header: /TRiAS/TRiAS V2.07/TRiAS/ExtFcns3.cpp 1     1.06.98 21:38 Hartmut Kaiser $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 05/27/1998 07:55:46 PM
//
// @doc
// @module ExtFcns3.cpp | Fuktionen, die bei externen Messages gerufen werden

#include "triaspre.hxx"

#include <dirisole.h>

#include "obj32/TRiASVersion.h"
#include "extmain3.hxx"
#include "extqnfy2.hxx"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#if _TRiAS_VER < 0x0510
extern DWORD g_dwVer51;
#endif // _TRiAS_VER < 0x0510

///////////////////////////////////////////////////////////////////////////////
// 
// DEX_ENUMEXTENSIONS
LRESULT ExtDirisWindow::OnEnumExtensions (HPROJECT, LPARAM lParam)
{
ENUMNOKEY *pK = (ENUMNOKEY *)lParam;

	TX_ASSERT_POINTER(pK, ENUMNOKEY);
	TX_ASSERT(TIsValidAddress(pK -> eFcn, 1, false));
	return EnumExtensions (pK);
}

// DEX_QUERYEXTENSIONINFO
LRESULT ExtDirisWindow::OnGetExtensionInfo (HPROJECT, LPARAM lParam)
{
EXTENSIONINFO *pInfo = (EXTENSIONINFO *)lParam;

	TX_ASSERT_POINTER(pInfo, EXTENSIONINFO);
	TX_ASSERT(sizeof(EXTENSIONINFO) == pInfo -> dwSize);
	TX_ASSERT(TIsValidString(pInfo -> pcDLLName));
	TX_ASSERT(TIsValidAddress(pInfo -> pName, pInfo -> iLen, true));
	return GetExtensionInfo (pInfo);
}

// DEX_QUERYEXTENSIONPTR
LRESULT ExtDirisWindow::OnGetExtensionPtr (HPROJECT, LPARAM lParam)
{
EXTENSIONPTR *pInfo = (EXTENSIONPTR *)lParam;

	TX_ASSERT_POINTER(pInfo, EXTENSIONPTR);
	TX_ASSERT(sizeof(EXTENSIONPTR) == pInfo -> dwSize);
	TX_ASSERT(TIsValidString(pInfo -> pcDLLName));
	return GetExtensionPtr (pInfo);
}

// DEX_QUERYPREVENTREPAINT
LRESULT ExtDirisWindow::OnQueryPreventRepaint (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LPARAM(FALSE);

	return LRESULT(m_pView -> GetPreventRepaint());
}

// DEX_PREVENTREPAINT
LRESULT ExtDirisWindow::OnPreventRepaint (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LPARAM(FALSE);

	m_pView -> SetPreventRepaint(bool(lParam));
	return LRESULT(TRUE);
}


// DEX_QUERYACTASPECTRATIO
LRESULT ExtDirisWindow::OnGetActiveAspect (HPROJECT, LPARAM lParam)
{
	TX_ASSERT_POINTER((double *)lParam, double);
	if (!IsValidActiveView() || 0 == lParam)
		return LPARAM(FALSE);

	*(double *)lParam = DBO().GetAspectRatio();
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// DEX_MODIFYIDENTSCALEDATA
LRESULT ExtDirisWindow::OnModifyIdentScaleData (HPROJECT, LPARAM lParam)
{
	if (!IsValidActiveView() || 0 == lParam)
		return LPARAM(FALSE);

IDENTSCALEDATA *pISD = (IDENTSCALEDATA *)lParam;

#if defined(_DEBUG)
	TX_ASSERT_POINTER(pISD, IDENTSCALEDATA);
	TX_ASSERT(pISD -> pcView == NULL || TIsValidString(pISD -> pcView));
	TX_ASSERT(IsValidIdent(pISD -> lIdent));
#endif // _DEBUG

	return DBO().SetIdentScaleData(
			pISD -> pcView, pISD -> lIdent, VisType(pISD -> iVTyp), 
			pISD -> lUpperScale, pISD -> lLowerScale) ? TRUE : FALSE;
}

// DEX_QUERYIDENTSCALEDATA
LRESULT ExtDirisWindow::OnGetIdentScaleData (HPROJECT, LPARAM lParam)
{
	if (!IsValidActiveView() || 0 == lParam)
		return LPARAM(FALSE);

IDENTSCALEDATA *pISD = (IDENTSCALEDATA *)lParam;

#if defined(_DEBUG)
	TX_ASSERT_POINTER(pISD, IDENTSCALEDATA);
	TX_ASSERT(pISD -> pcView == NULL || TIsValidString(pISD -> pcView));
	TX_ASSERT(IsValidIdent(pISD -> lIdent));
#endif // _DEBUG

	return DBO().RetrieveIdentScaleData (
				pISD -> pcView, pISD -> lIdent, VisType(pISD -> iVTyp), 
				&pISD -> lUpperScale, &pISD -> lLowerScale) ? TRUE : FALSE;
}

// DEX_TESTIDENTSCALETOPAINT
///////////////////////////////////////////////////////////////////////////////
// Maßstabsbereich testen (nur, wenn Bereich gegeben ist
namespace {
inline 
bool FMatchScales (long lActScale, long lUpperScale, long lLowerScale)
{
	if (0 != lUpperScale && lActScale < lUpperScale)
		return false;

	if (0 != lLowerScale && lActScale > lLowerScale)
		return false;

	return true;
}
}

LRESULT ExtDirisWindow::OnTestIdentScaleToPaint (HPROJECT, LPARAM lParam)
{
	if (!IsValidActiveView() || 0 == lParam)
		return LPARAM(FALSE);

IDENTSCALEDATA *pISD = (IDENTSCALEDATA *)lParam;

#if defined(_DEBUG)
	TX_ASSERT_POINTER(pISD, IDENTSCALEDATA);
	TX_ASSERT(pISD -> pcView == NULL || TIsValidString(pISD -> pcView));
	TX_ASSERT(IsValidIdent(pISD -> lIdent));
#endif // _DEBUG

LONG lUpperScale = 0, lLowerScale = 0;

	if (DBO().RetrieveIdentScaleData (pISD -> pcView, pISD -> lIdent, VisType(pISD -> iVTyp), &lUpperScale, &lLowerScale))
		return FMatchScales (DBO().GetActScale(), lUpperScale, lLowerScale) ? TRUE : FALSE;
	return TRUE;
}

// #HK980921
// DEX_SETHAVETOINITOPFS
LRESULT ExtDirisWindow::OnMustInitOPFs (HPROJECT, LPARAM lParam)
{
BOOL fMustInit = m_fMustInitOPFs;

	m_fMustInitOPFs = lParam ? true : false;
	return fMustInit;
}

// DEX_QUERYMUSTINITOPFS
LRESULT ExtDirisWindow::OnGetMustInitOPFs(HPROJECT, LPARAM)
{
	return m_fMustInitOPFs ? TRUE : FALSE;
}

// DEX_QUERYTRIASVERSIONLONG
LRESULT ExtDirisWindow::OnGetTRiASVersionLong (HPROJECT hPr, LPARAM lParam)
{
int iBuild = atol (TRIASVERSION_BUILD_STR);
int iRelease = atol (TRIASVERSION_RELEASE_STR);
int iVersion = atol (TRIASVERSION_VERSION_STR);

	return MAKELONG(iBuild, MAKEWORD(iRelease, iVersion));
}

///////////////////////////////////////////////////////////////////////////////
// DEX_LOADEXTENSION2: Erweiterung mit Optionen laden 
LRESULT ExtDirisWindow::OnLoadExtension2 (HPROJECT hPr, LPARAM lParam)
{
LOADEXTENSION2 *pLE = (LOADEXTENSION2 *)lParam;

	TX_ASSERT_POINTER(pLE, LOADEXTENSION2);
	TX_ASSERT(sizeof(LOADEXTENSION2) == pLE -> dwSize);
	TX_ASSERT(NULL == pLE -> m_pDesc || TIsValidString(pLE -> m_pDesc));
	TX_ASSERT(TIsValidString(pLE -> m_pName));

	return (LRESULT)(void *)LoadExtension (
				pLE -> m_pDesc, pLE -> m_pName, 
				pLE -> m_iMode, (EXTENSIONFLAG)pLE -> m_fGlobal,
				NULL, pLE -> m_pIUnk
			);
}

///////////////////////////////////////////////////////////////////////////////
// DEX_UNLOADEXTENSION2: Erweiterung mit Optionen entladen 
LRESULT ExtDirisWindow::OnUnLoadExtension2 (HPROJECT hPr, LPARAM lParam)
{
LOADEXTENSION2 *pLE = (LOADEXTENSION2 *)lParam;
bool iResult = false;

	TX_ASSERT_POINTER(pLE, LOADEXTENSION2);
	TX_ASSERT(sizeof(LOADEXTENSION2) == pLE -> dwSize);
	TX_ASSERT(NULL == pLE -> m_pDesc || TIsValidString(pLE -> m_pDesc));
	TX_ASSERT(TIsValidString(pLE -> m_pName));

	if (pLE -> m_iMode & LEFullLoad)	// hier FullUnload
		iResult = UnLoadExtension (pLE -> m_pName, true);
	else {		// nur entladen
		if (pLE -> m_pDesc == NULL) {
		char *pExtName = m_pEL -> RetrieveExtName (pLE -> m_pName);

			iResult = ReUnLoadExtension (pExtName, pLE -> m_pName);
			DELETE_OBJ (pExtName);
		} else
			iResult = ReUnLoadExtension (pLE -> m_pDesc, pLE -> m_pName);
	}
	return (LRESULT)iResult;
}

///////////////////////////////////////////////////////////////////////////////
// DEX_QUERYNAMEDVIEWPROPERTY
LRESULT ExtDirisWindow::OnGetNamedViewProperty (HPROJECT hPr, LPARAM lParam)
{
NAMEDVIEWPROPERTY *pNVP = (NAMEDVIEWPROPERTY *)lParam;

	TX_ASSERT_POINTER(pNVP, NAMEDVIEWPROPERTY);
	TX_ASSERT(sizeof(NAMEDVIEWPROPERTY) == pNVP -> dwSize);
	TX_ASSERT(NULL == pNVP -> pcView || TIsValidString(pNVP -> pcView));
	TX_ASSERT(TIsValidString(pNVP -> pcName));
	TX_ASSERT(TIsValidAddress(pNVP -> pBuffer, pNVP -> iLen, false));
	TX_ASSERT(NULL == pNVP -> pcShort || TIsValidString(pNVP -> pcShort));
	TX_ASSERT(NULL == pNVP -> pcDesc || TIsValidString(pNVP -> pcDesc));

	return (LRESULT)DBO().GetNamedViewProperty (pNVP);
}

// DEX_SETNAMEDVIEWPROPERTY
LRESULT ExtDirisWindow::OnSetNamedViewProperty (HPROJECT hPr, LPARAM lParam)
{
NAMEDVIEWPROPERTY *pNVP = (NAMEDVIEWPROPERTY *)lParam;

	TX_ASSERT_POINTER(pNVP, NAMEDVIEWPROPERTY);
	TX_ASSERT(sizeof(NAMEDVIEWPROPERTY) == pNVP -> dwSize);
	TX_ASSERT(NULL == pNVP -> pcView || TIsValidString(pNVP -> pcView));
	TX_ASSERT(TIsValidString(pNVP -> pcName));
	TX_ASSERT(NULL == pNVP -> pBuffer || TIsValidAddress(pNVP -> pBuffer, pNVP -> iLen, true));
	TX_ASSERT(NULL == pNVP -> pcShort || TIsValidString(pNVP -> pcShort));
	TX_ASSERT(NULL == pNVP -> pcDesc || TIsValidString(pNVP -> pcDesc));

	return (LRESULT)DBO().SetNamedViewProperty (pNVP);
}

// ProjektHandle von einem Objekthandle feststellen
// DEX_QUERYOBJECTPROJECT
LRESULT ExtDirisWindow::OnGetObjectProject (HPROJECT hPr, LPARAM lParam)
{
	return (LRESULT)DBO().GetObjectDBHandle (lParam, hPr);
}

// ProjektHandle von einem Objektklassenhandle feststellen
// DEX_QUERYOBJECTSPROJECT
LRESULT ExtDirisWindow::OnGetObjectsProject (HPROJECT hPr, LPARAM lParam)
{
	return (LRESULT)DBO().GetIdentDBHandle (lParam, hPr);
}

///////////////////////////////////////////////////////////////////////////////
// DEX_MODIFYSHOWNCOORDS
LRESULT ExtDirisWindow::OnSetShownCoords (HPROJECT hPr, LPARAM lParam)
{
	TX_ASSERT(NULL != m_pQNH);
	return m_pQNH -> SetShownCoords (lParam);
}

/////////////////////////////////////////////////////////////////////////////////
// DEX_QUERYDATASOURCECOUNT
LRESULT ExtDirisWindow::OnGetDataSourceCount (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);
		
	return (LRESULT)DBO().GetDataSourceCount (lParam);
}

/////////////////////////////////////////////////////////////////////////////////
// DEX_ENUMPROJECTSFORCLASS
LRESULT ExtDirisWindow::OnEnumClassProjects (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);
		
ENUMTEXTKEY *pK = (ENUMTEXTKEY *)lParam;

	TX_ASSERT_POINTER(pK, ENUMTEXTKEY);
	TX_ASSERT(TIsValidString(pK -> eKey));
	TX_ASSERT(TIsValidAddress(pK -> eFcn, 1, false));

	return (LRESULT)DBO().EnumClassProjects (
		(LPCSTR)pK -> eKey, 
		(BOOL (CALLBACK *)(HPROJECT, LPCSTR, UINT_PTR))(pK -> eFcn), 
		(UINT_PTR)(pK -> ePtr));
}

/////////////////////////////////////////////////////////////////////////////////
// DEX_GETHANDLEFROMMCODE
LRESULT ExtDirisWindow::OnMapMCodeToHandle (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(0);

	TX_ASSERT(HACTPROJECT != hPr);
	TX_ASSERT(HACTCONNECTION != hPr);
	return LRESULT(DBO().DB(hPr).MapMCodeToHandle (lParam));
}

///////////////////////////////////////////////////////////////////////////////
// DEX_QUERYFEATUREPROJECT
LRESULT ExtDirisWindow::OnGetFeatureProject (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(NULL);	// kein Projekt geöffnet

	return (LRESULT)DBO().GetFeatureDBHandle (lParam, hPr);
}

///////////////////////////////////////////////////////////////////////////////
// DEX_QUERYTRIASDATASOURCE
LRESULT ExtDirisWindow::OnIsTRiASDataSource (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(FALSE);	// kein Projekt geöffnet
	if (HACTPROJECT == hPr)
		return FALSE;			// ist keine Datenquelle

	return (LRESULT)DBO().DB(hPr).IsTRiASDataSource();
}

///////////////////////////////////////////////////////////////////////////////
// DEX_QUERYGDODATASOURCE
LRESULT ExtDirisWindow::OnIsGDODataSource (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(FALSE);	// kein Projekt geöffnet
	if (HACTPROJECT == hPr)
		return FALSE;			// ist keine Datenquelle

	return (LRESULT)DBO().DB(hPr).IsGDODataSource();
}

///////////////////////////////////////////////////////////////////////////////
// DEX_QUERYDATASOURCEOPEN
LRESULT ExtDirisWindow::OnIsOpened (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(FALSE);	// kein Projekt geöffnet
	if (HACTPROJECT == hPr)
		return FALSE;			// ist keine Datenquelle

	return (LRESULT)DBO().DB(hPr).isOpened();
}

///////////////////////////////////////////////////////////////////////////////
// DEX_GETROMODEIDENT
LRESULT ExtDirisWindow::OnDexQueryROModeIdent (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(TRUE);	// kein Projekt geöffnet

	if (DEX_GetROModeEx (DEX_GetObjectsProject(lParam)))
		return TRUE;			// Datenquelle ist RO

	return (LRESULT)DBO().GetROModeIdent(lParam);
}

///////////////////////////////////////////////////////////////////////////////
// DEX_MODIFYROMODEIDENT
LRESULT ExtDirisWindow::OnDexModifyROModeIdent (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(TRUE);	// kein Projekt geöffnet

MODIFYROMODE *pMRM = reinterpret_cast<MODIFYROMODE *>(lParam);

	TX_ASSERT(pMRM -> dwSize == sizeof(MODIFYROMODE));
	TX_ASSERT(IsValidIdent(pMRM -> lTarget));

	return (LRESULT)SUCCEEDED(DBO().SetROModeIdent(pMRM -> lTarget, pMRM -> fROMode ? true : false));
}

///////////////////////////////////////////////////////////////////////////////
// DEX_GETROMODEMCODE
LRESULT ExtDirisWindow::OnDexQueryROModeMCode (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(TRUE);	// kein Projekt geöffnet

HPROJECT hPrFeat = DEX_GetFeatureProject(lParam);

	if (NULL == hPrFeat) {
	// wenn noch keine Zuordnung existiert, dann muß Datenquelle gegeben sein
		TX_ASSERT(HACTCONNECTION != hPr);
		hPrFeat = hPr;
	}
	if (DEX_GetROModeEx (hPrFeat))
		return TRUE;			// Datenquelle ist RO

	if (DEX_GetTRiASDataSourceEx(hPrFeat))
		return FALSE;			// TRiAS-Merkmale sind an sich _nie_ RO

	return (LRESULT)DBO().GetROModeFeature(hPr, lParam);
}

///////////////////////////////////////////////////////////////////////////////
// DEX_MODIFYROMODEMCODE
LRESULT ExtDirisWindow::OnDexModifyROModeMCode (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(TRUE);	// kein Projekt geöffnet

MODIFYROMODE *pMRM = reinterpret_cast<MODIFYROMODE *>(lParam);

	TX_ASSERT(pMRM -> dwSize == sizeof(MODIFYROMODE));
	TX_ASSERT(IsValidMCode(pMRM -> lTarget));

HPROJECT hPrFeat = DEX_GetFeatureProject(pMRM -> lTarget);

	if (NULL == hPrFeat) {
	// wenn noch keine Zuordnung existiert, dann muß Datenquelle gegeben sein
		TX_ASSERT(HACTCONNECTION != hPr);
		hPrFeat = hPr;
	}
	if (DEX_GetROModeEx (hPrFeat))
		return FALSE;			// Datenquelle ist RO

	return (LRESULT)SUCCEEDED(DBO().SetROModeFeature(pMRM -> lTarget, pMRM -> fROMode ? true : false));
}

///////////////////////////////////////////////////////////////////////////////
// DEX_QUERYTABLENAME
LRESULT ExtDirisWindow::OnGetTableName (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(TRUE);	// kein Projekt geöffnet

#if defined(_DEBUG)
TABLENAME *pTableName = reinterpret_cast<TABLENAME *>(lParam);

	TX_ASSERT_POINTER(pTableName, TABLENAME);
	TX_ASSERT(sizeof(TABLENAME) == pTableName -> dwSize);
	TX_ASSERT(IsValidIdent(pTableName -> lIdent));
	TX_ASSERT(TIsValidAddress(pTableName -> pBuffer, pTableName -> iLen, true));
#endif // _DEBUG

	return (LRESULT)DBO().GetTableName(reinterpret_cast<TABLENAME *>(lParam));
}

///////////////////////////////////////////////////////////////////////////////
// DEX_QUERYOBJGUIDMCODE
LRESULT ExtDirisWindow::OnGetObjGuidMCode (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(0L);	// kein Projekt geöffnet

	TX_ASSERT(IsValidIdent (lParam));
	return (LRESULT)DBO().RetrieveObjGuidMCodeIdent (lParam);
}

///////////////////////////////////////////////////////////////////////////////
// DEX_PROJECTHANDLEFROMSHORTNAME
LRESULT ExtDirisWindow::OnGetDataSourceFromShortName (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(0L);	// kein Projekt geöffnet

	TX_ASSERT(TIsValidString(reinterpret_cast<LPCSTR>(lParam)));
	return (LRESULT)DBO().GetDataSourceFromShortName (reinterpret_cast<LPCSTR>(lParam));
}

///////////////////////////////////////////////////////////////////////////////
// DEX_ENUMALLPROJECTHANDLES
LRESULT ExtDirisWindow::OnEnumDatasourceHandles (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(0L);	// kein Projekt geöffnet

//	TX_ASSERT(TIsValidString(reinterpret_cast<LPCSTR>(lParam)));
	return (LRESULT)DBO().EnumDataSourceHandles (reinterpret_cast<ENUMNOKEYLONG *>(lParam));
}

///////////////////////////////////////////////////////////////////////////////
// DEX_GETMCODEFROMHANDLE
LRESULT ExtDirisWindow::OnMapHandleToMCode (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(0L);	// kein Projekt geöffnet

	TX_ASSERT(HACTPROJECT != hPr);
	if (HACTCONNECTION == hPr)
		hPr = DEX_GetFeatureProject(lParam);
	return LRESULT(DBO().DB(hPr).MapHandleToMCode (lParam));
}

///////////////////////////////////////////////////////////////////////////////
// DEX_QUERYCONTEXTPROJECT
LRESULT ExtDirisWindow::OnGetContextDataSource (HPROJECT hPr, LPARAM lParam)
{
	if (NULL == m_pQNH)
		return LRESULT(HACTCONNECTION);
	return LRESULT(m_pQNH -> GetContextHandle());
}

/////////////////////////////////////////////////////////////////////////////////
// DEX_MAPORCREATEHANDLEFROMMCODE
LRESULT ExtDirisWindow::OnMapOrCreateMCodeToHandle (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(0);

	TX_ASSERT(HACTPROJECT != hPr);
	TX_ASSERT(HACTCONNECTION != hPr);

MAPMCODETOHANDLE *pData = reinterpret_cast<MAPMCODETOHANDLE *>(lParam);

	TX_ASSERT_POINTER(pData, MAPMCODETOHANDLE);
	TX_ASSERT(sizeof(MAPMCODETOHANDLE) == pData -> dwSize);
	TX_ASSERT(NULL != pData -> plHandle);

	if (HACTPROJECT != hPr && HACTCONNECTION != hPr) {
		*(pData -> plHandle) = DBO().DB(hPr).MapMCodeToHandle (
			pData -> lMCode, pData -> fCreate, pData -> pfCreated, pData -> lIdent);
		return TRUE;
	}
	return FALSE;		// fehlerhafter Parameter
}

/////////////////////////////////////////////////////////////////////////////////
// DEX_QUERYSCHEMAUPDATABLE
LRESULT ExtDirisWindow::OnDexQuerySchemaUpdatable (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(FALSE);

	if (HACTPROJECT != hPr)
		return DBO().GetSchemaUpdatable (hPr);

// beim Projekt gehts um die Zuordnungsobjektklassen
	return DBO().GetROMode() ? FALSE : TRUE;
}

/////////////////////////////////////////////////////////////////////////////////
// DEX_ENUMCLASSESFROMOBJECT
LRESULT ExtDirisWindow::OnEnumObjectClasses (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(FALSE);

ENUMLONGKEYEX *pK = reinterpret_cast<ENUMLONGKEYEX *>(lParam);

	_ASSERTE(!IsBadReadPtr(pK, sizeof(ENUMLONGKEYEX)));
	_ASSERTE(!IsBadCodePtr((FARPROC)pK -> eFcn));
	_ASSERTE(IsValidONr((long)pK -> eKey));

	return DBO().EnumObjectClasses (pK -> eKey, pK -> eFcn, pK -> ePtr, pK -> eData);
}

///////////////////////////////////////////////////////////////////////////////
// DEX_OBJECTISINCLASS
LRESULT ExtDirisWindow::OnIsObjectInClass (HPROJECT hPr, LPARAM lParam)
{
ISOBJECTINCLASS *pIOC = reinterpret_cast<ISOBJECTINCLASS *>(lParam);

	_ASSERTE(!IsBadReadPtr(pIOC, sizeof(ISOBJECTINCLASS)));
	_ASSERTE(sizeof(ISOBJECTINCLASS) == pIOC -> dwSize);
	_ASSERTE(IsValidONr(pIOC -> lONr));
	_ASSERTE(IsValidIdent(pIOC -> lIdent));

	return DBO().IsObjectInClass (pIOC -> lIdent, pIOC -> lONr, pIOC -> plONrMapped);
}

///////////////////////////////////////////////////////////////////////////////
// DEX_UNLOADOBJECTFROMMEMORY
LRESULT ExtDirisWindow::OnUnloadObject (HPROJECT hPr, LPARAM lParam)
{
	_ASSERTE(IsValidONr(lParam));
	return DBO().UnloadObject (lParam);
}

///////////////////////////////////////////////////////////////////////////////
// DEX_QUERYNATIVEOBJECT
LRESULT ExtDirisWindow::OnGetNativeObject (HPROJECT hPr, LPARAM lParam)
{
	_ASSERTE(IsValidONr(lParam));
	return 0L;		// hier keine Rechercheobjektklassen
}

///////////////////////////////////////////////////////////////////////////////
// DEX_CHANGEIMPORTMODE
LRESULT ExtDirisWindow::OnHandleImportMode (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(NULL);	// kein Projekt geöffnet

	OnHandleNotificationMode(hPr, lParam ? TRUE : FALSE);
	return DBO().HandleImportMode (lParam);
}

///////////////////////////////////////////////////////////////////////////////
// DEX_CHANGENOTIFICATIONMODE
LRESULT ExtDirisWindow::OnHandleNotificationMode (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(NULL);	// kein Projekt geöffnet

BOOL fOldValue = m_pEL -> IsNotify();

	m_pEL -> SetNotificationMode (lParam ? true : false);	// ImportMode ist hier gespeichert
	return fOldValue;
}

///////////////////////////////////////////////////////////////////////////////
// DEX_MRUMENUMODE
LRESULT ExtDirisWindow::OnHandleMRUMenu (HPROJECT hPr, LPARAM lParam)
{
BOOL fOldValue = m_fHandleMRU;

	m_fHandleMRU = lParam ? true : false;	// MRUMode ist hier gespeichert
	if (!m_fHandleMRU && NULL != m_pMRU) {
		::RemoveMenuMRUItem (m_pMRU, MainMenu() -> Handle());
		::RemoveMenuMRUItem (m_pMRU, StartUpMenu() -> Handle());
		DrawMenuBar (Handle (API_WINDOW_HWND));
	}
	return fOldValue;
}

///////////////////////////////////////////////////////////////////////////////
// #HK000526
// DEX_RELATEDDATASOURCENAME
LRESULT ExtDirisWindow::OnGetRelatedDataSourceName (HPROJECT hPr, LPARAM lParam)
{
RELATEDDATASOURCENAME *pRDSN = reinterpret_cast<RELATEDDATASOURCENAME *>(lParam);

	_ASSERTE(!IsBadReadPtr(pRDSN, sizeof(RELATEDDATASOURCENAME)));
	_ASSERTE(sizeof(RELATEDDATASOURCENAME) == pRDSN -> dwSize);
	_ASSERTE(TIsValidString(pRDSN -> pcTargetName));
	_ASSERTE(TIsValidAddress(pRDSN -> pDataSourceName, pRDSN -> iLen, true));

	return DBO().GetRelatedDataSourceName (pRDSN);
}

///////////////////////////////////////////////////////////////////////////////
// #HK000705
// DEX_QUERYFEATUREIDENT
LRESULT ExtDirisWindow::OnGetFeatureIdent (HPROJECT hPr, LPARAM lParam)
{
	return DBO().GetFeatureIdent (lParam);
}

///////////////////////////////////////////////////////////////////////////////
// #HK000713
// DEX_SHOWPRINTLAYOUTDIALOG
LRESULT ExtDirisWindow::OnShowPrintLayoutDlg (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LPARAM(FALSE);

PRINTLAYOUTDIALOG *pPLDlg = reinterpret_cast<PRINTLAYOUTDIALOG *>(lParam);

	_ASSERTE(!IsBadReadPtr(pPLDlg, sizeof(PRINTLAYOUTDIALOG)));
	_ASSERTE(sizeof(PRINTLAYOUTDIALOG) == pPLDlg -> dwSize);
	_ASSERTE(!IsBadReadPtr(pPLDlg -> m_pLayout, sizeof(PRINTLAYOUT)));
	_ASSERTE(sizeof(PRINTLAYOUT) == pPLDlg -> m_pLayout -> dwSize);
	
	return m_pView -> ShowPrintLayoutDialog (pPLDlg);
}

// DEX_PREVIEWPRINT
LRESULT ExtDirisWindow::OnPrintPreview (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LPARAM(FALSE);

PRINTPREVIEW *pPP = reinterpret_cast<PRINTPREVIEW *>(lParam);

	_ASSERTE(!IsBadReadPtr(pPP, sizeof(PRINTPREVIEW)));
	_ASSERTE(sizeof(PRINTPREVIEW) == pPP -> dwSize);
	_ASSERTE(!IsBadReadPtr(pPP -> pLayout, sizeof(PRINTLAYOUT)));
	_ASSERTE(sizeof(PRINTLAYOUT) == pPP -> pLayout -> dwSize);
	_ASSERTE(!IsBadReadPtr(pPP -> pRenderDb, sizeof(RENDERGEODB)));
	_ASSERTE(sizeof(RENDERGEODB) == pPP -> pRenderDb -> dwSize);

	return m_pView -> PrintPreview (pPP);
}

// DEX_ENDPREVIEWPRINT
LRESULT ExtDirisWindow::OnEndPrintPreview (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LPARAM(FALSE);

PRINTPREVIEW *pPP = reinterpret_cast<PRINTPREVIEW *>(lParam);

	_ASSERTE(!IsBadReadPtr(pPP, sizeof(PRINTPREVIEW)));
	_ASSERTE(sizeof(PRINTPREVIEW) == pPP -> dwSize);

	return m_pView -> EndPrintPreview (pPP);
}

///////////////////////////////////////////////////////////////////////////////
// DEX_SHOWSTARTUPDIALOG: FakeMFC
// #HK000807
LRESULT ExtDirisWindow::OnShowStartupDialog (HPROJECT, LPARAM)
{
	return FALSE;	// nie hier bearbeiten
}

///////////////////////////////////////////////////////////////////////////////
// DEX_CLONEOBJECT: Objekt kopieren
// #HK001022
LRESULT ExtDirisWindow::OnCloneObject (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LPARAM(FALSE);

CLONEOBJECT *pCloneObj = reinterpret_cast<CLONEOBJECT *>(lParam);

	_ASSERTE(!IsBadReadPtr(pCloneObj, sizeof(CLONEOBJECT)));
	_ASSERTE(sizeof(CLONEOBJECT) == pCloneObj -> dwSize);
	_ASSERTE(IsValidONr(pCloneObj -> lONrToCopy));
	_ASSERTE(0 == pCloneObj -> lNewIdent || IsValidIdent(pCloneObj -> lNewIdent));

	return DBO().CloneObject (hPr, pCloneObj);
}

///////////////////////////////////////////////////////////////////////////////
// #HK001114
// DEX_VERIFYLICLEVEL
LRESULT ExtDirisWindow::OnVerifyLicenseLevel (HPROJECT hPr, LPARAM lParam)
{
	return FALSE;	// nie hier bearbeiten
}

// DEX_VERIFYLICOPTION
LRESULT ExtDirisWindow::OnVerifyLicenseOption (HPROJECT hPr, LPARAM lParam)
{
	return FALSE;	// nie hier bearbeiten
}

///////////////////////////////////////////////////////////////////////////////
// #HK001220
// DEX_QUERYTEXTFEATURE
LRESULT ExtDirisWindow::OnGetTextFeature (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LPARAM(FALSE);

INT_PTR lFeat = NULL;

	if (SUCCEEDED(DBO().GetTextFeature(lParam, &lFeat)))
		return lFeat;
	return 0L;
}

///////////////////////////////////////////////////////////////////////////////
// #HK010306
// DEX_QUERYOBJECTDESCSTRING
LRESULT ExtDirisWindow::OnGetObjDescString (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LPARAM(NULL);

	_ASSERTE(IsValidONr(lParam));

LPSTR pObjDesc = NULL;

	DBO().GetObjPropDesc((INT_PTR)lParam, &pObjDesc);
	return reinterpret_cast<LRESULT>(pObjDesc);
}

// DEX_ZOOMIN2OBJECT
LRESULT ExtDirisWindow::OnZoomInToObject (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LPARAM(FALSE);

	_ASSERTE(IsValidONr(lParam));
	return DBO().ZoomInToObject((INT_PTR)lParam);
}

// DEX_REFRESHENTRY
LRESULT ExtDirisWindow::OnRefreshEntries (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LPARAM(FALSE);

	return m_pView -> RefreshObjectEntries(lParam);
}

///////////////////////////////////////////////////////////////////////////////
// ProjectBar angezeigt
// WM_QUERYPROJECTBARACTIVE
LRESULT ExtDirisWindow::OnQueryProjectBarActive(HPROJECT hPr, LPARAM lParam)
{
	_ASSERTE(SUCCEEDED(E_NOTIMPL));	// should never be called
	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// OverViewBar angezeigt
// WM_QUERYOVERVIEWBARACTIVE
LRESULT ExtDirisWindow::OnQueryOverViewBarActive(HPROJECT hPr, LPARAM lParam)
{
	_ASSERTE(SUCCEEDED(E_NOTIMPL));	// should never be called
	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// SABiSBar angezeigt
// WM_QUERYSABiSBARACTIVE
LRESULT ExtDirisWindow::OnQuerySABiSBarActive(HPROJECT hPr, LPARAM lParam)
{
	_ASSERTE(SUCCEEDED(E_NOTIMPL));	// should never be called
	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// GenericBar angezeigt
// WM_QUERYGENERICBARACTIVE
LRESULT ExtDirisWindow::OnQueryGenericBarActive(HPROJECT hPr, LPARAM lParam)
{
	_ASSERTE(SUCCEEDED(E_NOTIMPL));	// should never be called
	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// Legende/Gesamtübersicht dürfen angezeigt werden
// #HK010922
// WM_QUERYMAYOPENLEGEND
LRESULT ExtDirisWindow::OnQueryMayOpenLegend (HPROJECT, LPARAM)	
{
	if (!IsValidActiveView())
		return LPARAM(FALSE);
	return (m_fViewSelected && m_fViewPainted) ? TRUE : FALSE;
}

// WM_QUERYMAYOPENOVERVIEW
LRESULT ExtDirisWindow::OnQueryMayOpenOverview (HPROJECT, LPARAM)
{
	if (!IsValidActiveView())
		return LPARAM(FALSE);
	return (m_fViewSelected && m_fViewPainted && !m_fPaintingView) ? TRUE : FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// #HK020413
// DEX_SHOWOBJPROPEX
LRESULT ExtDirisWindow::OnShowObjPropEx (HPROJECT, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LPARAM(E_UNEXPECTED);

SHOWOBJPROPEX *pSOP = (SHOWOBJPROPEX *)lParam;

	TX_ASSERT(NULL != pSOP);
	TX_ASSERT(sizeof(SHOWOBJPROPEX) == pSOP -> dwSize);
	TX_ASSERT(NULL == pSOP -> pcView || TIsValidString(pSOP -> pcView));
	TX_ASSERT(NULL == pSOP -> pObjProp || TIsValidString(pSOP -> pObjProp));

	return DBO().SetObjPropToShow(pSOP -> pcView, pSOP -> pObjProp, pSOP -> iFlags);
}

// DEX_QUERYOBJPROPEX
LRESULT ExtDirisWindow::OnGetObjPropEx (HPROJECT, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LPARAM(E_UNEXPECTED);

SHOWOBJPROPEX *pSOP = (SHOWOBJPROPEX *)lParam;

	TX_ASSERT(NULL != pSOP);
	TX_ASSERT(sizeof(SHOWOBJPROPEX) == pSOP -> dwSize);
	TX_ASSERT(NULL == pSOP -> pcView || TIsValidString(pSOP -> pcView));
	TX_ASSERT(NULL == pSOP -> pObjProp || TIsValidAddress(pSOP -> pObjProp, pSOP -> iLen, true));

	return DBO().GetObjPropToShow(pSOP -> pcView, pSOP -> pObjProp, pSOP -> iLen, &pSOP -> iFlags);
}

///////////////////////////////////////////////////////////////////////////////
// Recherchen auf aktuellen Bildausschnitt begrenzen
// DEX_SETLIMITSEARCHES
LRESULT ExtDirisWindow::OnSetLimitSearches (HPROJECT, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LPARAM(FALSE);

BOOL fOldValue = DBO().GetLimitSearches() ? TRUE : FALSE;

	DBO().SetLimitSearches(lParam ? true : false);
	return fOldValue;
}

// DEX_QUERYLIMITSEARCHES
LRESULT ExtDirisWindow::OnGetLimitSearches (HPROJECT, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LPARAM(FALSE);
	return DBO().GetLimitSearches() ? TRUE : FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// Recherche-Einschränkungen (objektklassenbezogen) ignorieren
// DEX_SETIGNORESEARCHOPTIONS
LRESULT ExtDirisWindow::OnSetIgnoreSearchOptions (HPROJECT, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LPARAM(FALSE);

BOOL fOldValue = DBO().GetIgnoreSearchOptions() ? TRUE : FALSE;

	DBO().SetIgnoreSearchOptions(lParam ? true : false);
	return fOldValue;
}

// DEX_QUERYIGNORESEARCHOPTIONS
LRESULT ExtDirisWindow::OnGetIgnoreSearchOptions (HPROJECT, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LPARAM(FALSE);
	return DBO().GetIgnoreSearchOptions() ? TRUE : FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// WM_QUERYDROPSOURCEORWND
LRESULT ExtDirisWindow::OnQueryDropSourceORWnd (HPROJECT, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LPARAM(NULL);
	return LPARAM(m_pView->GetDropSourceORWnd());
}

///////////////////////////////////////////////////////////////////////////////
// #HK021209
// DEX_QUERYOBJECTPTR
LRESULT ExtDirisWindow::OnQueryObjectPtr (HPROJECT, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LPARAM(E_UNEXPECTED);

QUERYCOMOBJECT *pQCO = reinterpret_cast<QUERYCOMOBJECT *>(lParam);

	TX_ASSERT_POINTER(pQCO, QUERYCOMOBJECT);
	TX_ASSERT(sizeof(QUERYCOMOBJECT) == pQCO -> dwSize);
	TX_ASSERT(IsValidONr(pQCO->hObject));
	TX_ASSERT(TIsValidAddress(pQCO->ppIUnk, sizeof(IUnknown *)));

	*(pQCO->ppIUnk) = NULL;

WTRiASObject Obj;
HRESULT hr = DBO().GetObjectFromMap(pQCO->hObject, Obj);

	if (SUCCEEDED(hr))
		return Obj->QueryInterface(*(pQCO->piid), (LPVOID *)pQCO->ppIUnk);
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
// #HK021209
// DEX_QUERYOBJECTSPTR
LRESULT ExtDirisWindow::OnQueryObjectsPtr (HPROJECT, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LPARAM(E_UNEXPECTED);

QUERYCOMOBJECT *pQCO = reinterpret_cast<QUERYCOMOBJECT *>(lParam);

	TX_ASSERT_POINTER(pQCO, QUERYCOMOBJECT);
	TX_ASSERT(sizeof(QUERYCOMOBJECT) == pQCO -> dwSize);
	TX_ASSERT(IsValidIdent(pQCO->hObject));
	TX_ASSERT(TIsValidAddress(pQCO->ppIUnk, sizeof(IUnknown *)));

	*(pQCO->ppIUnk) = NULL;

WTRiASObjects Objs;
HRESULT hr = DBO().GetObjectsFromMap(pQCO->hObject, Objs);

	if (SUCCEEDED(hr))
		return Objs->QueryInterface(*(pQCO->piid), (LPVOID *)pQCO->ppIUnk);
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
// #HK021209
// DEX_QUERYFEATUREPTR
LRESULT ExtDirisWindow::OnQueryFeaturePtr (HPROJECT, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LPARAM(E_UNEXPECTED);

QUERYCOMOBJECT *pQCO = reinterpret_cast<QUERYCOMOBJECT *>(lParam);

	TX_ASSERT_POINTER(pQCO, QUERYCOMOBJECT);
	TX_ASSERT(sizeof(QUERYCOMOBJECT) == pQCO -> dwSize);
	TX_ASSERT(IsValidMCode(pQCO->hObject));
	TX_ASSERT(TIsValidAddress(pQCO->ppIUnk, sizeof(IUnknown *)));

	*(pQCO->ppIUnk) = NULL;

WTRiASFeature Feat;
HRESULT hr = DBO().GetFeatureFromMap(pQCO->hObject, Feat);

	if (SUCCEEDED(hr))
		return Feat->QueryInterface(*(pQCO->piid), (LPVOID *)pQCO->ppIUnk);
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
// #HK021217
// DEX_CREATECONNECTIONFILTER
LRESULT ExtDirisWindow::OnCreateConnectionFilter (HPROJECT hPr, LPARAM lParam)
{
#if _TRiAS_VER < 0x0510
	if (0 == g_dwVer51)
		return E_UNEXPECTED;
#endif // _TRiAS_VER < 0x0510

	if (!IsValidActiveView())
		return LPARAM(E_UNEXPECTED);

CONNECTIONFILTER *pCF = reinterpret_cast<CONNECTIONFILTER *>(lParam);

	TX_ASSERT_POINTER(pCF, CONNECTIONFILTER);
	TX_ASSERT(sizeof(CONNECTIONFILTER) == pCF -> dwSize);
	TX_ASSERT(TIsValidString(pCF -> pcName));
	TX_ASSERT(NULL == pCF -> pICS || TIsValidIUnknown(pCF -> pICS));
	TX_ASSERT(TIsValidIUnknown(pCF -> pIGeometry));

	return DBO().CreateConnectionFilter(pCF);
}
	
// DEX_DELETECONNECTIONFILTER
LRESULT ExtDirisWindow::OnDeleteConnectionFilter (HPROJECT hPr, LPARAM lParam)
{
#if _TRiAS_VER < 0x0510
	if (0 == g_dwVer51)
		return E_UNEXPECTED;
#endif // _TRiAS_VER < 0x0510

	if (!IsValidActiveView())
		return LPARAM(E_UNEXPECTED);

CONNECTIONFILTER *pCF = reinterpret_cast<CONNECTIONFILTER *>(lParam);

	TX_ASSERT_POINTER(pCF, CONNECTIONFILTER);
	TX_ASSERT(sizeof(CONNECTIONFILTER) == pCF -> dwSize);
	TX_ASSERT(TIsValidString(pCF -> pcName));
	TX_ASSERT(NULL == pCF -> pICS);
	TX_ASSERT(NULL == pCF -> pIGeometry);

	return DBO().DeleteConnectionFilter(pCF);
}

// DEX_ENUMCONNECTIONFILTERS
LRESULT ExtDirisWindow::OnEnumConnectionFilters (HPROJECT hPr, LPARAM lParam)	
{
#if _TRiAS_VER < 0x0510
	if (0 == g_dwVer51)
		return E_UNEXPECTED;
#endif // _TRiAS_VER < 0x0510

	if (!IsValidActiveView())
		return LPARAM(E_UNEXPECTED);

ENUMNOKEY *pENK = reinterpret_cast<ENUMNOKEY *>(lParam);

	TX_ASSERT_POINTER(pENK, ENUMNOKEY);
	TX_ASSERT(TIsValidAddress(pENK -> eFcn, 1, false));

	return DBO().EnumConnectionFilters(pENK);
}

// DEX_ATTACHCONNECTIONFILTER
LRESULT ExtDirisWindow::OnAttachConnectionFilter (HPROJECT hPr, LPARAM lParam)	
{
#if _TRiAS_VER < 0x0510
	if (0 == g_dwVer51)
		return E_UNEXPECTED;
#endif // _TRiAS_VER < 0x0510

	if (!IsValidActiveView())
		return LPARAM(E_UNEXPECTED);

ATTACHCONNECTIONFILTER *pACF = reinterpret_cast<ATTACHCONNECTIONFILTER *>(lParam);

	TX_ASSERT_POINTER(pACF, ATTACHCONNECTIONFILTER);
	TX_ASSERT(sizeof(ATTACHCONNECTIONFILTER) == pACF -> dwSize);
	TX_ASSERT(TIsValidString(pACF -> pcName));
	TX_ASSERT(TIsValidString(pACF -> pcConnName));

	return DBO().AttachConnectionFilter(pACF);
}

// DEX_DETACHCONNECTIONFILTER
LRESULT ExtDirisWindow::OnDetachConnectionFilter (HPROJECT hPr, LPARAM lParam)
{
#if _TRiAS_VER < 0x0510
	if (0 == g_dwVer51)
		return E_UNEXPECTED;
#endif // _TRiAS_VER < 0x0510

	if (!IsValidActiveView())
		return LPARAM(E_UNEXPECTED);

ATTACHCONNECTIONFILTER *pACF = reinterpret_cast<ATTACHCONNECTIONFILTER *>(lParam);

	TX_ASSERT_POINTER(pACF, ATTACHCONNECTIONFILTER);
	TX_ASSERT(sizeof(ATTACHCONNECTIONFILTER) == pACF -> dwSize);
	TX_ASSERT(NULL == pACF -> pcName || TIsValidString(pACF -> pcName));
	TX_ASSERT(TIsValidString(pACF -> pcConnName));

	return DBO().DetachConnectionFilter(pACF);
}

// DEX_QUERYATTACHEDCONNECTIONFILTER
LRESULT ExtDirisWindow::OnGetAttachedConnectionFilter (HPROJECT hPr, LPARAM lParam)
{
#if _TRiAS_VER < 0x0510
	if (0 == g_dwVer51)
		return E_UNEXPECTED;
#endif // _TRiAS_VER < 0x0510

	if (!IsValidActiveView())
		return LPARAM(E_UNEXPECTED);

GETATTACHEDCONNECTIONFILTER *pGACF = reinterpret_cast<GETATTACHEDCONNECTIONFILTER *>(lParam);

	TX_ASSERT_POINTER(pGACF, GETATTACHEDCONNECTIONFILTER);
	TX_ASSERT(sizeof(GETATTACHEDCONNECTIONFILTER) == pGACF -> dwSize);
	TX_ASSERT(TIsValidString(pGACF -> pcConnName));
	TX_ASSERT(0 == pGACF -> iLen || TIsValidAddress(pGACF -> pName, pGACF -> iLen));

	return DBO().GetAttachedConnectionFilter(pGACF);
}

// DEX_CREATECONNECTIONFILTER_DLG
LRESULT ExtDirisWindow::OnShowCreateConnectionFilterDlg (HPROJECT hPr, LPARAM lParam)
{
	_ASSERTE(SUCCEEDED(E_NOTIMPL));
	return FALSE;		// shouldn't be called
}

// #HK030107
// DEX_SHOWCONNECTFILTERS
LRESULT ExtDirisWindow::OnShowConnectionFilters (HPROJECT hPr, LPARAM lParam)
{
	_ASSERTE(SUCCEEDED(E_NOTIMPL));
	return FALSE;		// shouldn't be called
}

// DEX_CONNECTFILTERSSHOWN
LRESULT ExtDirisWindow::OnConnectionFiltersShown (HPROJECT hPr, LPARAM lParam)
{
	_ASSERTE(SUCCEEDED(E_NOTIMPL));
	return FALSE;		// shouldn't be called
}

// #HK030117
// DEX_QUERYCONNECTIONFILTER
LRESULT ExtDirisWindow::OnGetConnectionFilter (HPROJECT hPr, LPARAM lParam)
{
#if _TRiAS_VER < 0x0510
	if (0 == g_dwVer51)
		return E_UNEXPECTED;
#endif // _TRiAS_VER < 0x0510

	if (!IsValidActiveView())
		return LPARAM(E_UNEXPECTED);

CONNECTIONFILTER *pCF = reinterpret_cast<CONNECTIONFILTER *>(lParam);

	TX_ASSERT_POINTER(pCF, CONNECTIONFILTER);
	TX_ASSERT(sizeof(CONNECTIONFILTER) == pCF -> dwSize);
	TX_ASSERT(TIsValidString(pCF -> pcName));
	TX_ASSERT(NULL == pCF -> pICS || TIsValidIUnknown(pCF -> pICS));
	TX_ASSERT(NULL == pCF -> pIGeometry);

	return DBO().GetConnectionFilter(pCF);
}

//////////////////////////////////////////////////////////////////////////////
// #HK041112
// DEX_EXECUTECOMMANDSEQUENCE
LRESULT ExtDirisWindow::OnExecuteSequence(HPROJECT, LPARAM)
{
#if _TRiAS_VER < 0x0510
	if (0 == g_dwVer51)
		return E_UNEXPECTED;
#endif // _TRiAS_VER < 0x0510

	if (!IsValidActiveView())
		return E_UNEXPECTED;

    return ExecuteSequence() ? S_OK : E_FAIL;
}
