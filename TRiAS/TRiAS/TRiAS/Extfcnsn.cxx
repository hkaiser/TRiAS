// Verteilen der intern zu verarbeitenden Notifikationen ----------------------
// File: EXTFCNSN.CXX
//
// 03.03.2001 18:40:26
//		Added: support for DEX_N_HIDEORSHOWPROJECTWINDOW

#include "triaspre.hxx"

#include <dirisole.h>
#include "extmain3.hxx"

#include "tools.hxx"
#include "overview.hxx"
#include "legdinfo.hxx"
#include "legwind.hxx"
#if defined(OLD_COORDS)
#include "coords.hxx"
#endif // OLD_COORDS
#include <Array.h>		// SafeArray

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// globale Variablen
#if defined(OLD_COORDS)
extern CoordsDlg *pCoords;
#endif // OLD_COORDS
extern CLegendeClientWindow *pLegende;	// Legende
extern bool LegendeCFlag;				// Legende eingeblendet
extern DWORD g_dwMenu;

///////////////////////////////////////////////////////////////////////////////
// SAFEARRAY-Zugriff
DeclareSafeLock(long);	

///////////////////////////////////////////////////////////////////////////////
// Sprungverteiler für Notifications

LRESULT ExtDirisWindow::DispatchNotification (WPARAM wParam, LPARAM lParam)
{
	if (m_cbDexProcsNfy) {	// über Sprungverteiler abwickeln
	register UINT uiMsg = wParam-m_i1stDexProcNfy;
	
		if (uiMsg >= 0 && uiMsg < m_iDexProcsNumNfy)
			return (this ->* m_cbDexProcsNfy[uiMsg])(lParam);
	}

#if defined(_DEBUG)
	switch (wParam) {
	case DEX_SETNEWPALETTE:		return doNfySetNewPalette (lParam);
	case DEX_RESCALE:			return doNfyReScale (lParam);
	case DEX_REREADIDENTS:		return doNfyReReadIdents (lParam);
	case DEX_REREADCONTAINER:	return doNfyReReadContainer (lParam);
	case DEX_REREADSIGHTS:		return doNfyReReadViews (lParam);
	case DEX_HEADERREREAD:		return doNfyReReadHeader (lParam);
	case DEX_N_REREADOBJPROPS:	return doNfyReReadObjectProps(lParam);
	case DEX_SETACTIVETOOL:		return doNfyHandleDeleteMenu (lParam);
	case DEX_OBJECTTODELETE:	return doNfyHandleDeletingObject (lParam);
	case DEX_DELOBJECT:			return doNfyHandleObjectDeleted (lParam);
	case DEX_N_TODELETEOBJECT:	return doNfyHandleToDeleteObject (lParam);
	case DEX_MODIFYINGIDENT:	return doNfyIdentToModify (lParam);
	case DEX_IDENTWASMODIFIED:	return doNfyIdentModified (lParam);
	case DEX_N_MODIFYMERKMALSET:	return doNfyFeatureSetModified (lParam);
	case DEX_QUERYRECHOBJECT:	return doNfyQueryRechObject (lParam);
	case DEX_TXICHANGED:		return doNfyTXIChanged (lParam);
	case DEX_TXMCHANGED:		return doNfyTXMChanged (lParam);
	case DEX_TXRCHANGED:		return doNfyTXRChanged (lParam);
	case DEX_DELETEVIEW:		return doNfyDeleteView (lParam);
	case DEX_SIGHTDELETED:		return doNfyViewDeleted (lParam);
	case DEX_VIEWCREATED:		return doNfyViewCreated (lParam);
	case DEX_GOTOBJWNDFOCUS:	return doNfyORWndFocusChanged (lParam);
	case DEX_COORDFORMATWASCHANGED:	return doNfyUpdateCoordFormat (lParam);
	case DEX_SETGEODBDIRTY:		return doNfySetDirty (lParam);
	case DEX_INITIALIZEDSERVER:	return doNfyInitialized (lParam);
	case DEX_N_EXTENSIONSLOADED:	return doNfyExtensionsLoaded (lParam);
	case DEX_SERVERISCLOSING:	return doNfyClosingApp (lParam);
	case DEX_SERVERCLOSED:		return doNfyAppClosed (lParam);
	case DEX_SIGHTTOSELECT:		return doNfySelectingView (lParam);
	case DEX_SIGHTSELECTED:		return doNfyViewSelected (lParam);
	case DEX_PROJECTOPEN:		return doNfyProjectOpened (lParam);
	case DEX_PROJECTCLOSE:		return doNfyClosingProject (lParam);
	case DEX_ISCLOSEDPROJECT:	return doNfyProjectClosed (lParam);
	case DEX_N_PROJECTTOCLOSE:	return doNfyProjectToClose (lParam);
// Objektrecherchefenster
	case DEX_OBJECTSELECTED:	return doNfyObjectSelected (lParam);	
	case DEX_OBJECTUNSELECTED:	return doNfyObjectUnselected (lParam);	
	case DEX_OBJECTACTIVATED:	return doNfyObjectActivated (lParam);	
	case DEX_OBJECTDEACTIVATED:	return doNfyObjectDeactivated (lParam);	
	case DEX_CREATEOBJEKTINFO:	return doNfyCreateORWnd (lParam);		
	case DEX_OBJWNDCLOSED:		return doNfyCloseORWnd (lParam);		
	case DEX_N_RENAMINGFILE:	return doNfyRenamingFile (lParam);
	case DEX_N_FILERENAMED:		return doNfyFileRenamed (lParam);
	case DEX_OBJECTCHANGED:		return doNfyObjectChanged (lParam);
	case DEX_CHANGINGOBJECT:	return doNfyChangingObject (lParam);
	case DEX_N_OBJECTSPLITTED:	return doNfyObjectSplitted (lParam);
	case DEX_N_OBJECTCREATED_EDIT:	return doNfyObjectCreated (lParam);
	case DEX_N_SCROLLING_VERT:	return doNfyScrollingVert (lParam);
	case DEX_N_SCROLLING_HORZ:	return doNfyScrollingHorz (lParam);
	default:
		break;		// do nothing
	}
#endif // _DEBUG

return false;		// einfach weiterleiten
}

///////////////////////////////////////////////////////////////////////////////
// Handler für interne Notifications

// noop -----------------------------------------------------------------------
LRESULT ExtDirisWindow::OnNotUsedNotification (LPARAM lParam)
{
	return false;
}

// DEX_SETNEWPALETTE: HintergrundFarbe hinzufügen -----------------------------
LRESULT ExtDirisWindow::doNfySetNewPalette (LPARAM lParam)
{
	ExpandPaletteColor (*(HPALETTE *)lParam, (COLORREF &)Color(BLACK));
	ExpandPaletteColor (*(HPALETTE *)lParam, (COLORREF &)Color(WHITE));
	ExpandPaletteColor (*(HPALETTE *)lParam, (COLORREF &)DBO().GetBkColor());
	return FALSE;
}

// DEX_RESCALE: Header neu lesen ----------------------------------------------
LRESULT ExtDirisWindow::doNfyReScale (LPARAM lParam)
{
	if (NULL != m_pView)
		DBO().ReScale (m_pView);		
	return FALSE;
}

// DEX_REREADIDENTS: IdentTree neu aufbauen -----------------------------------
LRESULT ExtDirisWindow::doNfyReReadIdents (LPARAM lParam)
{
	DBO().ReReadIdents();	
	return FALSE;
}		

// DEX_REREADCONTAINER: DBContainer neu lesen/setzen --------------------------
LRESULT ExtDirisWindow::doNfyReReadContainer (LPARAM lParam)
{
	if (IsValidActiveView()) {
	DatenBasisObjekt &rDBO = DBO();
	ObjContainer OC = rDBO.DBCont(true).InflateCont(10);

	// ObjContainerStack rücksetzen
		TX_ASSERT(NULL != m_pView);
		m_pView -> ResetObjContainerStack();

		if (rDBO.HasActiveSight() && rDBO.hasSichtCont())
			rDBO.GetSichtCont (&OC);
		
		m_pView -> ResetSelectionRect();
		SetExtend (OC);
	}
	return FALSE;		// immer weiterschicken
}

// DEX_REREADSIGHTS: Sichtmenu initialisieren ---------------------------------
LRESULT ExtDirisWindow::doNfyReReadViews (LPARAM lParam)
{
	if (IsValidActiveView()) {	// Sichten neu einlesen
	bool fDraw = DBO().DeleteAllSightItems (this, MainMenu());

		if ((DBO().InitSightMenu (MainMenu(), (bool)lParam) || fDraw) &&
			!(g_dwMenu & HANDLEMENU_MainMenu))
		{
			::DrawMenuBar (Handle (API_WINDOW_HWND));
		}
	}

CComVariant vDefault (lParam ? true : false);

	m_pEL -> GeoViewEvent (HACTPROJECT, GEOVIEWEVT_ReReadAll, vDefault);
	return false;		// immer weiterleiten
}

// DEX_HEADERREREAD: Diverse HeaderEinträge neu einlesen ----------------------
LRESULT ExtDirisWindow :: doNfyReReadHeader (LPARAM lParam)
{
	if (!IsValidActiveProject())
		return LRESULT(false);

	ReReadHeader();
	ReReadCaption();

	if (0 != lParam) {
	CComVariant vProj ((LPCSTR)lParam);

		m_pEL -> ProjectEvent (HACTPROJECT, PROJECTEVT_ReReadHeader, vProj);
	} else {
	CComVariant vData;

		vData.vt = VT_ERROR;
		V_ERROR(&vData) = DISP_E_PARAMNOTFOUND;
		m_pEL -> ProjectEvent (HACTPROJECT, PROJECTEVT_ReReadHeader, vData);
	}
	return false;
}

// Objekteigenschaften neu einlesen
LRESULT ExtDirisWindow::doNfyReReadObjectProps (LPARAM lParam)
{
	InstallObjectProperties (lParam ? true : false);
	return false;
}

// DEX_SETACTIVETOOL: DeleteMenu aktivieren/passivieren -----------------------
LRESULT ExtDirisWindow::doNfyHandleDeleteMenu (LPARAM lParam)
{
#if defined(WIN16)
	HandleDeleteMenu ((int)lParam == NUMSCHERE);
#endif // !WIN32

// MouseBttnSupport etc.
	if (NULL != m_pView)
		m_pView -> ResetMouseFlags();
				
	App::Exec(ExecIdleOnly);		// UI richten
	return false;
}	

// DEX_OBJECTTODELETE: vor Löschen aus Fenstern nehmen ------------------------
LRESULT ExtDirisWindow::doNfyHandleDeletingObject (LPARAM lParam)
{
	if (S_FALSE == m_pEL -> GeoObjectEvent (DBO().GetObjectDBHandle (lParam), GEOOBJECTEVT_DeletingObject, lParam))
		return true;		// jemand hat was dagegen

	return false;
}

// DEX_DELOBJECT: Objekt wurde gelöscht
LRESULT ExtDirisWindow::doNfyHandleObjectDeleted (LPARAM lParam)
{
	m_pEL -> GeoObjectEvent (HACTCONNECTION, GEOOBJECTEVT_ObjectDeleted, 0L);
	return false;
}

// DEX_N_TODELETEOBJECT: Objekt wird jetzt gelöscht
LRESULT ExtDirisWindow::doNfyHandleToDeleteObject (LPARAM lParam)
{
	HandleDeleteObject ((LONG)lParam);		// aus OR-Fenstern rausnehmen

	m_pEL -> GeoObjectEvent (DBO().GetObjectDBHandle (lParam), GEOOBJECTEVT_ObjectToDelete, lParam);
	return false;
}

// DEX_MODIFYINGIDENT: vor umklassifizieren rufen
LRESULT ExtDirisWindow::doNfyIdentToModify (LPARAM lParam)
{
	m_pEL -> GeoObjectEvent (DBO().GetObjectDBHandle (lParam), GEOOBJECTEVT_ObjectToClassify, lParam);
	return false;
}

// DEX_IDENTWASMODIFIED: nach umklassifizieren nachführen ---------------------
LRESULT ExtDirisWindow::doNfyIdentModified (LPARAM lParam)
{
	HandleModifyIdent ((long)lParam);

	m_pEL -> GeoObjectEvent (DBO().GetObjectDBHandle (lParam), GEOOBJECTEVT_ObjectClassified, lParam);
	return false;
}

// DEX_N_MODIFYMERKMALSET: Merkmal hinzugefügt bzw. gelöscht
LRESULT ExtDirisWindow::doNfyFeatureSetModified (LPARAM lParam)
{
	m_pEL -> FeatureSetModified (lParam);
	return false;
}

// DEX_MODIFYMERKMAL: Objekteigenschaft wurde verändert -----------------------
LRESULT ExtDirisWindow::doNfyFeatureModified (LPARAM lParam)
{
	HandleModifyFeature ((long)lParam, NULL);
	return false;
}

// DEX_N_MODIFYMERKMAL: Objekteigenschaft wurde verändert -----------------------
LRESULT ExtDirisWindow::doNfyFeatureModifiedEx (LPARAM lParam)
{
FEATUREMODIFIED *pFM = (FEATUREMODIFIED *)lParam;

	HandleModifyFeature (pFM -> lONr, pFM -> pcName);
	m_pEL -> GeoFeatureEvent (DBO().GetObjectDBHandle (pFM -> lONr), GEOFEATUREEVT_FeatureChanged, lParam);
	return false;
}

// DEX_QUERYRECHOBJECT: was soll in einem ORFenster angezeigt werden ----------
LRESULT ExtDirisWindow::doNfyQueryRechObject (LPARAM lParam)
{
RECHOBJECT *pRO = (RECHOBJECT *)lParam;
CTable t(DBO().Idents().IdentTree());

	if (!DEX_GetIgnoreSearchOptions() && t.Find (&pRO -> lIdent)) {
	CIdentifikatorLock l(t);
	
		TX_ASSERT(NULL != (CIdentifikator *)l);
		if (!l -> GetSearchAble (OTypToBits(ObjTyp(pRO -> iOTyp)))) {
			if (!(ROShowHidden & pRO -> iFlags)) {
				pRO -> iFlags = ROHideFlags;
				return true;	// wird sowieso nicht angezeigt
			}
		}
	}
	return false;
}

// DEX_TXICHANGED: PBD geändert (Idents) --------------------------------------
LRESULT ExtDirisWindow::doNfyTXIChanged (LPARAM lParam)
{
#if defined(_FORCE_LEGACY_CODE)
	if (IsValidActiveView())
		DBO().PbdDB().UpdateIdents (lParam);
#endif // defined(_FORCE_LEGACY_CODE)

	DEX_RefreshLegend();
	DEX_RepaintLegend();
	return false;
}

// DEX_TXMCHANGED: PBD geändert (Merkmale) ------------------------------------
LRESULT ExtDirisWindow::doNfyTXMChanged (LPARAM lParam)
{
#if defined(_FORCE_LEGACY_CODE)
	if (IsValidActiveView())
		DBO().PbdDB().UpdateMCodes (lParam);
#endif // defined(_FORCE_LEGACY_CODE)

	return false;
}
		
// DEX_TXRCHANGED: PBD geändert (Relationen) ----------------------------------
LRESULT ExtDirisWindow::doNfyTXRChanged (LPARAM lParam)
{
#if defined(_FORCE_LEGACY_CODE)
	if (IsValidActiveView())
		DBO().PbdDB().UpdateRCodes (lParam);
#endif // defined(_FORCE_LEGACY_CODE)

	return false;
}

// DEX_VIEWCREATED: neue Sicht wurde erzeugt ----------------------------------
LRESULT ExtDirisWindow::doNfyViewCreated (LPARAM lParam)
{
VIEWCREATED *pVC = (VIEWCREATED *)lParam;

// neue Ansicht erzeugt
CComVariant vNew (pVC -> m_pNewName);

	m_pEL -> GeoViewEvent (HACTPROJECT, GEOVIEWEVT_ViewCreated, vNew);

	if (pVC -> m_iMode & VCDeleteTarget && NULL != pVC -> m_pTarget &&
		strcmp (pVC -> m_pTarget, pVC -> m_pNewName)) 
	{
	// Um im UI kein geflacker zuzulassen, erst neue Sicht als aktiv 
	// kennzeichnen, erst danach alte Ansicht rausnehmen
	CComVariant vOld (pVC -> m_pTarget);	// Ansicht gelöscht

		m_pEL -> GeoViewEvent (HACTPROJECT, GEOVIEWEVT_ViewSelected, vNew);	
		m_pEL -> GeoViewEvent (HACTPROJECT, GEOVIEWEVT_ViewDeleted, vOld);	
	}

	return false;
}

// DEX_SIGHTDELETED: Sicht wurde gelöscht -------------------------------------
LRESULT ExtDirisWindow::doNfyViewDeleted (LPARAM lParam)
{
CComVariant vData ((LPCSTR)lParam);

	m_pEL -> GeoViewEvent (HACTPROJECT, GEOVIEWEVT_ViewDeleted, vData);
	return false;
}

// DEX_DELETEVIEW:Sicht soll gelöscht werden ----------------------------------
LRESULT ExtDirisWindow::doNfyDeleteView (LPARAM lParam)
{
CComVariant vData (reinterpret_cast<LPCSTR>(lParam));

	if (S_FALSE == m_pEL -> GeoViewEvent (HACTPROJECT, GEOVIEWEVT_DeletingView, vData))
		return true;		// jemand hat was dagegen

	DBO().ResetLegend(reinterpret_cast<LPCSTR>(lParam));
	return false;
}

// DEX_COORDFORMATWASCHANGED: wenn Koordinatenanzeige aktiv ist, dann refreshen
LRESULT ExtDirisWindow::doNfyUpdateCoordFormat (LPARAM lParam)
{
#if defined(OLD_COORDS)
	if (NULL != pCoords) 
		pCoords -> RefreshCoords();
#endif // OLD_COORDS

CComVariant vData;

	vData.vt = VT_ERROR;
	V_ERROR(&vData) = DISP_E_PARAMNOTFOUND;
	m_pEL -> ProjectEvent (HACTPROJECT, PROJECTEVT_ChangedCoordFormat, vData);
	return false;
}
	
// DEX_SETGEODBDIRTY: GeoDB als Dirty bzw. nicht dirty gekennzeichnet ---------
LRESULT ExtDirisWindow::doNfySetDirty (LPARAM lParam)
{
char cbName[_MAX_PATH];

	RetrieveActiveProject(cbName);

CComVariant vProj (cbName);

	if (lParam)	
		m_pEL -> ProjectEvent (HACTPROJECT, PROJECTEVT_ProjectIsDirty, vProj);
	else
		m_pEL -> ProjectEvent (HACTPROJECT, PROJECTEVT_ProjectIsNotDirty, vProj);

	ReReadCaption (true);	// Caption richten
	App::Exec(ExecIdleOnly);

	return false;
}

// DEX_N_EXTENSIONSLOADED: TRiAS fertig initialisiert, Erweiterungen geladen --
LRESULT ExtDirisWindow::doNfyExtensionsLoaded (LPARAM lParam)
{
	m_pEL -> ServerEvent (SERVEREVT_ExtensionsLoaded);
	return false;
}

// DEX_INITIALIZEDSERVER: TRiAS fertig initialisiert, MessageLoop läuft -------
LRESULT ExtDirisWindow::doNfyInitialized (LPARAM lParam)
{
	m_pEL -> ServerEvent (SERVEREVT_InitializedServer);
	return false;
}

// DEX_SERVERISCLOSING: TRiAS soll beendet werden -----------------------------
LRESULT ExtDirisWindow::doNfyClosingApp (LPARAM lParam)
{
	if (S_FALSE == m_pEL -> ServerEvent (SERVEREVT_ClosingServer))
		return true;		// jamand hat was dagegen

	return false;
}

// DEX_SERVERCLOSED: TRiAS wird beendet (das ist die letzte Notification) -----
LRESULT ExtDirisWindow::doNfyAppClosed (LPARAM lParam)
{
	m_pEL -> ServerEvent (SERVEREVT_ServerToClose);
	return false;
}

// DEX_N_SHOWTOOLTIPS: ToolTipStatus wurde geändert ---------------------------
LRESULT ExtDirisWindow::doNfyShowToolTips (LPARAM lParam)
{
	m_pEL -> ServerEvent (lParam ? SERVEREVT_ShowToolTips : SERVEREVT_ShowNoMoreToolTips);
	return false;
}

// DEX_SIGHTTOSELECT: Sicht soll gewechselt werden ----------------------------
LRESULT ExtDirisWindow::doNfySelectingView (LPARAM lParam)
{
CComVariant vData ((LPCSTR)lParam);

	if (S_FALSE == m_pEL -> GeoViewEvent (HACTPROJECT, GEOVIEWEVT_SelectingView, vData))
		return true;		// jemand hat was dagegen

	m_pEL -> ResetObjProps();
	m_pEL -> ResetClsProps();
	m_fMustInitOPFs = true;

	DEX_SaveLegend();		// ggf. Legende speichern
	return false;
}

// DEX_SIGHTSELECTED: Sicht wurde gewechselt ----------------------------------
LRESULT ExtDirisWindow::doNfyViewSelected (LPARAM lParam)
{
CComVariant vData (reinterpret_cast<LPCSTR>(lParam));

	m_pEL -> GeoViewEvent (HACTPROJECT, GEOVIEWEVT_ViewSelected, vData);
	if (NULL != pLegende)
		pLegende -> ViewSelected(reinterpret_cast<LPCSTR>(lParam));

	m_fViewSelected = (NULL != lParam) ? true : false;
	if (!m_fViewSelected)
		m_fViewPainted = false;

	App::Exec(ExecIdleOnly);
	return false;
}

///////////////////////////////////////////////////////////////////////////////
// DEX_N_SCROLLING_VERT: Sicht wird vertikal gescrollt
LRESULT ExtDirisWindow::doNfyScrollingVert (LPARAM lParam)
{
	m_pEL -> GeoViewEvent (HACTPROJECT, GEOVIEWEVT_ScrollingVert, CComVariant(lParam, VT_I4));
	return false;
}

///////////////////////////////////////////////////////////////////////////////
// DEX_N_SCROLLING_HORZ: Sicht wird horizontal gescrollt
LRESULT ExtDirisWindow::doNfyScrollingHorz (LPARAM lParam)
{
	m_pEL -> GeoViewEvent (HACTPROJECT, GEOVIEWEVT_ScrollingHorz, CComVariant(lParam, VT_I4));
	return false;
}

// DEX_PROJECTOPEN: GeoDB wurde eröffnet --------------------------------------
LRESULT ExtDirisWindow::doNfyProjectOpened (LPARAM lParam)
{
char cbName[_MAX_PATH];

	RetrieveActiveProject(cbName);

CComVariant vProj (cbName);

	m_pEL -> ProjectEvent ((HPROJECT)lParam, PROJECTEVT_ProjectOpened, vProj);
	return false;
}

// DEX_ISCLOSEDPROJECT: GeoDB wurde geschlossen -------------------------------
LRESULT ExtDirisWindow::doNfyProjectClosed (LPARAM lParam)
{
CComVariant vData;

	vData.vt = VT_ERROR;
	V_ERROR(&vData) = DISP_E_PARAMNOTFOUND;
	m_pEL -> ProjectEvent (NULL, PROJECTEVT_ProjectClosed, vData);
	return false;
}

// DEX_PROJECTCLOSE: GeoDB soll geschlossen werden ----------------------------
LRESULT ExtDirisWindow::doNfyClosingProject (LPARAM lParam)
{
char cbName[_MAX_PATH];

	RetrieveActiveProject(cbName);

CComVariant vData (cbName);

	if (S_FALSE == m_pEL -> ProjectEvent ((HPROJECT)lParam, PROJECTEVT_ClosingProject, vData))
		return true;	// jemand hat was dagegen

	return false;
}

// DEX_N_RENAMINGFILE
LRESULT ExtDirisWindow::doNfyRenamingFile (LPARAM lParam)
{
CComVariant vData;

	vData.vt = VT_ERROR;
	V_ERROR(&vData) = DISP_E_PARAMNOTFOUND;
	m_pEL -> ProjectEvent (HACTPROJECT, PROJECTEVT_RenamingFile, vData);
	return false;		// immer weiterversenden
}

// DEX_N_FILERENAMED
LRESULT ExtDirisWindow::doNfyFileRenamed (LPARAM lParam)
{
char cbName[_MAX_PATH];

	RetrieveActiveProject(cbName);

CComVariant vProj (cbName);

	m_pEL -> ProjectEvent (HACTPROJECT, PROJECTEVT_FileRenamed, vProj);
	return false;		// immer weiterversenden
}

// DEX_N_SCALINGCHANGED: Darstellungsmaßstab wurde verändert ------------------
LRESULT ExtDirisWindow::doNfyScalingChanged (LPARAM lParam)
{
	USES_CONVERSION;

// Projekt vom neuen Maßstab imformieren
	DBO().SetActScale (lParam);

CComVariant vData;

	vData.vt = VT_I4;
	V_I4(&vData) = lParam;
	m_pEL -> GeoViewEvent (HACTPROJECT, GEOVIEWEVT_ZoomChanged, vData);
	return false;
}

// DEX_N_PROJECTTOCLOSE: Projekt wird wirklich geschlossen --------------------
LRESULT ExtDirisWindow::doNfyProjectToClose (LPARAM lParam)
{
char cbName[_MAX_PATH];

	RetrieveActiveProject(cbName);

CComVariant vProj (cbName);

	m_pEL -> ProjectEvent (HACTPROJECT, PROJECTEVT_ProjectToClose, vProj);

// jetzt Objekteigenschaften etc. freigeben
	m_pEL -> ResetObjProps(true);
	m_pEL -> ResetClsProps();
	return false;
}

// DEX_ERASEBKGND: Beginn der ZeichenAktion
LRESULT ExtDirisWindow::doNfyPaintingView (LPARAM lParam)
{
CComVariant vData;

	vData.vt = VT_ERROR;
	V_ERROR(&vData) = DISP_E_PARAMNOTFOUND;
	m_pEL -> GeoViewEvent (HACTPROJECT, GEOVIEWEVT_PaintingView, vData);

	m_fViewPainted = true;
	m_fPaintingView = true;
	return false;
}

// DEX_PAINTTOPLAYER: Ende der ZeichenAktion 
LRESULT ExtDirisWindow::doNfyViewPainted (LPARAM lParam)
{
// lParam zeigt auf Feld mit 2 hDCs
CSafeArray sa (VT_I4, 2);

	if (!!sa) {

		{
		CLocklong l (sa);
		HDC *phDC = reinterpret_cast<HDC *>(lParam);

			*l = reinterpret_cast<long>(phDC[0]);
			*(l + 1) = reinterpret_cast<long>(phDC[1]);
		}

	// erst alle benachrichtigen
	CComVariant vData;

		V_VT(&vData) = VT_ARRAY|VT_I4;
		V_ARRAY(&vData) = sa.Detach();

		m_pEL -> GeoViewEvent (HACTPROJECT, GEOVIEWEVT_ViewPainted, vData);
		m_fPaintingView = false;
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////////
// Objektrecherchefenster
// ACHTUNG: Die folgende Notifikationen sind genau falsch bezeichnet
// DEX_OBJECTSELECTED/DEX_OBJECTUNSELECTED steht für aktiviert/deaktiviert
// DEX_OBJECTACTIVATED/DEX_OBJECTDEACTIVATED steht für selektiert/deselektiert

// DEX_OBJECTSELECTED
LRESULT ExtDirisWindow::doNfyObjectSelected (LPARAM lParam)
{
	TX_TRACE1("TRiAS:ObjectActivated: %ld\n", lParam);
	m_pEL -> GeoObjectEvent (DBO().GetObjectDBHandle(lParam), GEOOBJECTEVT_ObjectActivated, lParam);
	return false;
}
	
// DEX_OBJECTUNSELECTED
LRESULT ExtDirisWindow::doNfyObjectUnselected (LPARAM lParam)
{
	TX_TRACE1("TRiAS:ObjectDeActivated: %ld\n", lParam);
	m_pEL -> GeoObjectEvent (DBO().GetObjectDBHandle(lParam), GEOOBJECTEVT_ObjectDeActivated, lParam);
	return false;
}
	
// DEX_OBJECTACTIVATED
LRESULT ExtDirisWindow::doNfyObjectActivated (LPARAM lParam)
{
	TX_TRACE1("TRiAS:ObjectSelected: %ld\n", lParam);
	m_pEL -> GeoObjectEvent (DBO().GetObjectDBHandle(lParam), GEOOBJECTEVT_ObjectSelected, lParam);
	return false;
}
	
// DEX_OBJECTDEACTIVATED
LRESULT ExtDirisWindow::doNfyObjectDeactivated (LPARAM lParam)
{
	TX_TRACE1("TRiAS:ObjectUnSelected: %ld\n", lParam);
	m_pEL -> GeoObjectEvent (DBO().GetObjectDBHandle(lParam), GEOOBJECTEVT_ObjectUnSelected, lParam);
	return false;
}
	
// DEX_OBJECTCHANGED
LRESULT ExtDirisWindow::doNfyObjectChanged (LPARAM lParam)
{
	TX_TRACE1("TRiAS:doNfyObjectChanged: %ld\n", lParam);
	m_pEL -> GeoObjectEvent (DBO().GetObjectDBHandle(lParam), GEOOBJECTEVT_GeometryChanged, lParam);
	return false;
}
	
// DEX_CHANGINGOBJECT
LRESULT ExtDirisWindow::doNfyChangingObject (LPARAM lParam)
{
	TX_TRACE1("TRiAS:doNfyChangingObject: %ld\n", lParam);
	m_pEL -> GeoObjectEvent (DBO().GetObjectDBHandle(lParam), GEOOBJECTEVT_ChangingGeometry, lParam);
	return false;
}

// DEX_N_OBJECTSPLITTED
LRESULT ExtDirisWindow::doNfyObjectSplitted (LPARAM lParam)
{
// wird als ProjektEvent verschickt, da hier ein 'VARIANT' vorhanden ist
CComVariant vData;
CSafeArray sa (VT_I4, 3);	// SAFEARRAY mit den 3 ObjektNummern
long lONrOrig = 0L;

	{
	OBJECTSPLITTED *pOS = (OBJECTSPLITTED *)lParam;

		TX_ASSERT(sizeof(OBJECTSPLITTED) == pOS -> dwSize);
		TX_ASSERT_POINTER(pOS, OBJECTSPLITTED);

		TX_ASSERT(IsValidONr (pOS -> m_lONrOrig));
		TX_ASSERT(IsValidONr (pOS -> m_lONrNew1));
//		TX_ASSERT(IsValidONr (DBO().DB().DBDesc(), pOS -> m_lONrNew2));

	CLocklong l (sa);

		*l = lONrOrig = pOS -> m_lONrOrig;
		*(l + 1) = pOS -> m_lONrNew1;
		*(l + 2) = pOS -> m_lONrNew2;
	} // lock aufheben

	V_VT(&vData) = VT_ARRAY|VT_I4;
	V_ARRAY(&vData) = sa.Detach();

	m_pEL -> ProjectEvent (DBO().GetObjectDBHandle(lONrOrig), PROJECTEVT_ObjectSplitted, vData);
	return false;
}

// DEX_N_OBJECTCREATED
LRESULT ExtDirisWindow::doNfyObjectCreated (LPARAM lParam)
{
	TX_TRACE1("TRiAS:doNfyObjectCreated: %ld\n", lParam);
	if (S_FALSE == m_pEL -> GeoObjectEvent (DBO().GetObjectDBHandle(lParam), GEOOBJECTEVT_ObjectCreated, lParam))
		return true;		// Abbrechen, da jemand was dagegen hatte
	return false;
}

// DEX_CREATEOBJEKTINFO
LRESULT ExtDirisWindow::doNfyCreateORWnd (LPARAM lParam)
{
	m_pEL -> ObjectWindowEvent (OBJWNDEVT_WindowCreated, lParam);
	return false; 
}

// DEX_OBJWNDCLOSED
LRESULT ExtDirisWindow::doNfyCloseORWnd (LPARAM lParam)
{
	m_pEL -> ObjectWindowEvent (OBJWNDEVT_WindowDestroyed, lParam);
	return false;
}

#if !defined(WIN16)
// DEX_GOTOBJWNDFOCUS: Merken des letzten aktiven Fensters --------------------
LRESULT ExtDirisWindow::doNfyORWndFocusChanged (LPARAM lParam)
{
	SetLastActive ((HWND)lParam);
	m_pEL -> ObjectWindowEvent (OBJWNDEVT_GotFocus, lParam);
	return false;
}

// DEX_LOSTOBJWNDFOCUS
LRESULT ExtDirisWindow::doNfyKillFocus (LPARAM lParam)
{
	m_pEL -> ObjectWindowEvent (OBJWNDEVT_LostFocus, lParam);
	return false;
}

// DEX_N_...OBJECTPROPERTY
LRESULT ExtDirisWindow::doNfyChangedObjectProperties (LPARAM lParam)
{
	m_fMustInitOPFs = true;		// beim nächsten mal neu generieren
	return (LRESULT)true;
}

#endif // WIN16

// #HK010303: DEX_N_HIDEORSHOWPROJECTWINDOW
LRESULT ExtDirisWindow::doNfyProjectWindowShownOrHidden (LPARAM lParam)
{
// Legende ausblenden, wenn Projektfenster geschlossen wird
	if (!lParam && LegendeCFlag)
		PostEvent (WM_COMMAND, IDM_LEGENDE);
		
	return (LRESULT)TRUE;
}

// #HK021217
// DEX_N_ADDINGOBJECT
LRESULT ExtDirisWindow::doNfyAddingObject(LPARAM lParam)
{
	if (S_FALSE == m_pEL -> GeoObjectEvent (HPROJECT(lParam), GEOOBJECTEVT_AddingObject, lParam))
		return true;		// Abbrechen, da jemand was dagegen hatte
	return false;
}

// DEX_N_OBJECTTOADD
LRESULT ExtDirisWindow::doNfyObjectToAdd(LPARAM lParam)
{
	m_pEL -> GeoObjectEvent (HPROJECT(lParam), GEOOBJECTEVT_ObjectToAdd, lParam);
	return false;
}

// DEX_N_OBJECTADDED
LRESULT ExtDirisWindow::doNfyObjectAdded(LPARAM lParam)
{
	m_pEL -> GeoObjectEvent (DBO().GetObjectDBHandle(lParam), GEOOBJECTEVT_ObjectAdded, lParam);
	return false;
}
