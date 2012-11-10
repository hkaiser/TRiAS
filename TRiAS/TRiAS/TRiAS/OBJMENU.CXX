// Menuverarbeitungsroutinen fuer ObjektInfoDlgBox ----------------------------
// File: OBJMENU.CXX

#include "triaspre.hxx"

#include "triasres.h"

#include <xtensnxx.h>
#include <ospace/com/iterenum.h>		// IEnum<LONG>
#include <TRiASMode.h>

#include <xtsnguid.h>
#include <undoguid.h>		// GUID
#include <eonrguid.h>
#include <dirisole.h>
#include <selobwnd.h>
#include <modidprp.h>
#include <statguid.h>
#include <DstObWnd.h>
#include <ObjekteDoppelnGuid.h>
#include <DelObPrp.h>
#include <propguid.h>

#include <iunredo.hxx>		// Interface's
#include <ipropseq.hxx>
#include <istatus.h>
#include <PropName.hxx>

#include <Com/PropertyActionBaseDataImpl.cpp>

#include "extmain3.hxx"
#include "Strings.h"
#include "tenums.h"
	
//#include "merkedit.hxx"
#include "objowndr.hxx"
#include "objprop.hxx"

#include "CloseCommandWrapper.h"
#include "RechResultORWnd.h"

#if defined(_DEBUG) && !defined(WIN16)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#if _TRiAS_VER < 0x0400
extern DWORD g_dwVer4;
#endif // _TRiAS_VER < 0x0400

#if _TRiAS_VER < 0x0510
extern DWORD g_dwVer51;
#endif // _TRiAS_VER < 0x0510

///////////////////////////////////////////////////////////////////////////////
// benötigte SmartIF's
DefineSmartInterface(DataObject);
DefineEnumIIDWrapper(LONG);
DefineSmartEnumerator(LONG);		// WEnumLONG etc.
DefineSmartInterface(ProgressIndicator);
DefineSmartInterface(PropertyAction);
DefineSmartInterface(PropertyAction2);
DefineSmartInterface(PropertyActionSequence);
DefineSmartInterface(UndoRedoReplaceObjectWnd);

///////////////////////////////////////////////////////////////////////////////
// globale Variablen
extern ExtDirisWindow *CurrActDirisW;
extern HelpDisplay *IrisHD;
extern HPALETTE hPalette;
extern bool LegendeCFlag;					// Legende angezeigt

#if defined(_FORCE_LEGACY_CODE)
extern bool g_fFilters;			// ExportFilter installiert
#endif // defined(_FORCE_LEGACY_CODE)
extern short GCancelFlag;       // General Cancel Flag

extern class CLegendeClientWindow *pLegende;	// Legende

char *FormatROString (char *pText, RECHOBJECT &rRO);
short OTypToBits (ObjTyp);
HRESULT DeleteObjsInitProgress (HWND hWnd, int iCntSel, IProgressIndicator **ppIProgInd);

///////////////////////////////////////////////////////////////////////////////
// MenuMessages auswerten 

#if defined(_NEWORMENU)
void ObjektInfo::MenuCommand (MenuCommandEvt e) 
{
bool fCancelMode = (e.GetItemID() == IDM_TOGGLEROLLUP) ? false : true;

	if (fCancelMode)
		DEX_CancelMode (true);		// Blinken abschalten

	{
	CCloseCommandWrapper CloseWrap(*this);

		Update();						// Fenster zeichnen lassen

	// erst mal bei der ExtensionList nachfragen, ob dieser MenuPunkt zu einer 
	// Erweiterung gehört, wenn nichts in der LB ist, dann ist das das Problem der 
	// Erweiterung
		if (m_rEL.DispatchMenuCommand (e, hWnd())) {
			if (fCancelMode)
				DEX_CancelMode (false);	// Blinken wieder zuschalten
			return;
		}

	// wenn nichts enthalten ist, dann raus
		if (-1L == GetActiveObj()) 
			return;	// nichts in der Listbox
		
	// Commando verabeiten
		BEGIN_COMMANDS(e.GetItemID())
		// SystemMenu
			ON_COMMAND_ID(IDM_REMOVEORWNDS, doRemoveAllORWnds);
			ON_COMMAND_ID(IDM_MINIMIZEORWNDS, doMinimizeAllORWnds);
			ON_COMMAND_ID(IDM_MAXIMIZEORWNDS, doMaximizeAllORWnds);

		// StandardMenu: Bearbeiten
			ON_COMMAND_ID(ID_OBJMENU_SAVEOBJECTCOLLECTION, doSaveObjColl);		// Ausschneiden
			ON_COMMAND_ID(ID_OBJMENU_CUT, doCut);		// Ausschneiden
			ON_COMMAND_ID(ID_OBJMENU_COPY, doCopy);		// Kopieren
			ON_COMMAND_ID(ID_OBJMENU_PASTE, doPaste);	// Einfügen
			ON_COMMAND_ID(ID_OBJMENU_SELECTALL, doSelectAll);				// Alle Einträge selektieren
			ON_COMMAND_ID(ID_OBJMENU_REVERSESELECTION, doReverseSelection);	// Selektion umkehren
			ON_COMMAND_ID(IDM_ATTRIBUTE, doShowOIAttribute);	// Merkmale editieren
			ON_COMMAND_ID(IDM_OBJPROPS, doObjectProps);	// Objekteigenschaften anzeigen
			ON_COMMAND_ID(IDM_DELETE_OBJPROPS, doDeleteObjProps);	// Objekteigenschaften löschen
			ON_COMMAND_ID(IDM_ZOOMOBJECTS, doZoomIn);	// Objekte zeigen
			ON_COMMAND_ID(IDM_KOMPLOBJECTS, doComplementObjects);	// komplementäre Objektmenge

		// Standardmenu: Aktionen
			ON_COMMAND_ID(IDM_MODALLIDENTS, doModAllIdents);	// Objektklasse modifizieren
			ON_COMMAND_ID(IDM_COPYOBJECTS, doCopyObjects);	// Objekte doppeln
			ON_COMMAND_ID(IDM_EXPORT, doExportObjects);		// Objekte exportieren
			ON_COMMAND_ID(IDM_OBJDELETE, doObjDelete);		// Objekte löschen
			ON_COMMAND_ID(IDM_ADDTOLEGEND, doAddToLegend);	// Zu Legende hinzufügen
			ON_COMMAND_ID(IDM_OBJMENU_SEARCH, doRecherche);	// Recherche aus ORWnd anwerfen
			ON_COMMAND_ID(IDM_OBJMENU_REPLACE, doReplace);	// Suchen und erstzen aus ORWnd anwerfen
			ON_COMMAND_ID(IDM_OBJMENU_CLASSIFY, doClassify);	// Klassifikation
			ON_COMMAND_ID(IDM_GENTEXTOBJECTS, doGenTextObjects);	// Textobjekte erzeugen

		// Standardmenu: Extras
			ON_COMMAND_ID(IDM_RECHRESULTS, doRechResults);	// Anzuzeigende Infos auswählen
			ON_COMMAND_ID(IDM_CONNECTION_FILTER, doCreateConnFilter);	// Räumlichen Filter aus Objektgeometrie erzeugen

		// StandardMenu: Hilfe anzeigen
			ON_COMMAND_ID(IDM_OBJHELP, doHelp);

		// nur als Accel vorhandeln
			ON_COMMAND_ID(IDM_CANCEL, doCancel);			// Zeichnen abbrechen
			ON_COMMAND_ID(IDM_DRAW, doDraw);				// Zeichnen
			ON_COMMAND_ID(IDM_REBUILD, doRebuild);			// Zeichnen/Neuaufbau

	#if !defined(_NO_ROLLUP_ORWND)
		// kommt von ganz wo anders ...
			ON_COMMAND_ID(IDM_TOGGLEROLLUP, doToggleRollUp);
	#endif // !defined(_NO_ROLLUP_ORWND)
		END_COMMANDS;

	}	// CCloseCommandWrapper goes out of scope

	App::Exec (ExecWhileEvent);			// erstmal alles abarbeiten
	if (fCancelMode)
		DEX_CancelMode (false);			// Blinken wieder erlauben
}

BOOL ModifyMenuObjectCount (HMENU hMenu, UINT uiID, LPCSTR pcObjs, UINT uiStrID)
{
char cbBuffer[64];
char cbOldBuff[64];

	wsprintf (cbBuffer, ResString(uiStrID, 64), pcObjs);
	GetMenuString (hMenu, uiID, cbOldBuff, sizeof(cbOldBuff), MF_BYCOMMAND);
	if (strcmp (cbOldBuff, cbBuffer))
		return ModifyMenu (hMenu, uiID, MF_BYCOMMAND|MF_STRING, uiID, cbBuffer);

	return TRUE;
}

void ObjektInfo::MenuInit (MenuInitEvt e) 
{
	if (WM_INITMENU == e.Msg()) return;	// nur WM_INITMENUPOPUP bearbeiten

	if (HIWORD(e.LParam())) {			// SystemMenu
	short iCnt = DEX_ActiveObjectsCount();

		EnableMenuItem (HMENU(e.WParam()), IDM_REMOVEORWNDS, 
			iCnt > 1 ? MF_BYCOMMAND|MF_ENABLED : MF_BYCOMMAND|MF_GRAYED);
		return;
	}

// Alle Erweiterungen fragen, ob sie etwas an den Menu's zu drehen haben
CTable r(EL());
bool fFoundExt = false;

	for (r.First(); r.Valid(); r.Next()) {
	ExtensionLock l(r);
	int iMenuType = 0;

		if (l && 0 != (iMenuType = l -> isMyMenu (e))) {
		// wenn Menu gefunden wurde
			l -> MenuInit (e, hWnd());
			if (!fFoundExt)
				fFoundExt = (1 == iMenuType) ? true : false;
		}
	}	
	if (fFoundExt) return;

// MenuText entspr. selektierter Objektanzahl richten
HMENU hMenu = ObjektMenu.Handle (API_MENU_HMENU);
ResString resObj ((m_ulActCount > 1) ? IDS_MANYOBJECTS : IDS_ONEOBJECT, 32);
ResString resObjs ((m_ulActCount > 1) ? IDS_MANYOBJECTCLASSES : IDS_ONEOBJECTCLASS, 32);

	ModifyMenuObjectCount (hMenu, IDM_MODALLIDENTS, resObjs, IDS_MODIDENT);
	ModifyMenuObjectCount (hMenu, IDM_OBJDELETE, resObj, IDS_OBJDELETE);
	ModifyMenuObjectCount (hMenu, IDM_ZOOMOBJECTS, resObj, IDS_SHOWOBJECTS);
	ModifyMenuObjectCount (hMenu, IDM_COPYOBJECTS, resObj, IDS_COPYOBJECTS);
//	ModifyMenuObjectCount (hMenu, IDM_EXPORT, resObj, IDS_EXPORTOBJECTS);
	ModifyMenuObjectCount (hMenu, IDM_ADDTOLEGEND, resObj, IDS_ADDTOLEGEND);

// eigene MenuPunkte Enable'n
BOOL fLegendVisible = TRUE;

	DEX_IsProjectBarVisible(fLegendVisible);
	MenuEnable (&ObjektMenu, IDM_ADDTOLEGEND, (LegendeCFlag && fLegendVisible && m_ulActCount > 0) ? TRUE : FALSE);
//	MenuEnable (&ObjektMenu, IDM_EXPORT, (g_fFilters && m_ulActCount > 0) ? TRUE : FALSE);
	MenuEnable (&ObjektMenu, IDM_EXPORT, FALSE);

	DrawMenuBar (m_hWnd);

// wenn kein Objekt selektiert ist, dann MenuPunkte passivieren
bool ifRO = !DEX_GetROModeEx(HACTPROJECT);
bool fNativeObj = false;

	if (-1 != m_lActObj && 0 == DEX_GetNativeObject (m_lActObj)) 
		fNativeObj = true;

	MenuEnable (&ObjektMenu, IDM_MODALLIDENTS, m_ulActCount > 0 && ifRO);
	MenuEnable (&ObjektMenu, IDM_OBJDELETE, m_ulActCount > 0 && ifRO && fNativeObj);
	MenuEnable (&ObjektMenu, IDM_ZOOMOBJECTS, m_ulActCount > 0);
	MenuEnable (&ObjektMenu, IDM_COPYOBJECTS, m_ulActCount > 0);
	MenuEnable (&ObjektMenu, IDM_GENTEXTOBJECTS, m_ulActCount > 0);

#if _TRiAS_VER < 0x0510
	if (0 != g_dwVer51)
#endif // _TRiAS_VER < 0x0510
	{
	bool fIsArea = (-1 != m_lActObj) && (OT_FLAECHE == DEX_GetObjectType (m_lActObj));

		MenuEnable(&ObjektMenu, IDM_CONNECTION_FILTER, fIsArea);
	}
}

///////////////////////////////////////////////////////////////////////////////
// MenuCommands
bool ObjektInfo::doRemoveAllORWnds (void)
{
	DEX_PostRemoveAllORWnds();		// alle ORFenster löschen
	return true;
}

extern "C"
BOOL CALLBACK MinimizeOrMaximize (LONG hWnd, BOOL, void *pData)
{
	DEXOR_ToggleRollUp((HWND)hWnd, *(BOOL *)pData);
	return TRUE;
}

bool ObjektInfo::doMinimizeAllORWnds()
{
ENUMNOKEYLONG ENK;
BOOL fToggleUp = TRUE;

	ENK.eFcn = (ENUMNOKEYLONGPROC)MinimizeOrMaximize;
	ENK.ePtr = &fToggleUp;
	return DEX_EnumORWindows(ENK);
}

bool ObjektInfo::doMaximizeAllORWnds()
{
ENUMNOKEYLONG ENK;
BOOL fToggleUp = FALSE;

	ENK.eFcn = (ENUMNOKEYLONGPROC)MinimizeOrMaximize;
	ENK.ePtr = &fToggleUp;
	return DEX_EnumORWindows(ENK);
}

bool ObjektInfo::doCut (void)				// Ausschneiden
{
	return false;
}

bool ObjektInfo::doCopy (void)				// Kopieren
{
	return false;
}

bool ObjektInfo::doPaste (void)				// Einfügen
{
	return false;
}

bool ObjektInfo::doSelectAll (void)			// Alle Einträge selektieren
{
CEierUhr Wait (GetParent());

	m_pKurzInfo -> ChangeSelected(Range(0, GetCount()-1), true);
	m_ulActCount = UpdateActivation();
	UpdateCaption();	// Caption dieses Fensters aktualisieren
	return true;
}

bool ObjektInfo::doReverseSelection (void)	// Selektion umkehren
{
CEierUhr Wait (GetParent());
int iLastIndex = GetCount();

	for (int iIndex = 0; iIndex < iLastIndex; iIndex++) {
	bool isSel = m_pKurzInfo -> GetSelection (iIndex);

		m_pKurzInfo -> ChangeSelected (iIndex, !isSel);
	}
	m_ulActCount = UpdateActivation();
	UpdateCaption();	// Caption dieses Fensters aktualisieren
	return true;
}

#if !defined(_FORCE_LEGACY_CODE)

static const CLSID *cbObjProps[] = {
	&CLSID_SelectFromObjectWindow,
	&CLSID_GenerateObjectProperties,
};
static CALPCLSID calObjProps = {
	sizeof(cbObjProps)/sizeof(cbObjProps[0]),
	cbObjProps,
	NULL,
#if !defined(_TRIAS_OLDIMPLEMTATION1)
	NULL,
#endif // _TRIAS_OLDIMPLEMTATION1
};

#endif // !defined(_FORCE_LEGACY_CODE)

#if defined(_FORCE_LEGACY_CODE)
bool ObjektInfo::doObjectProps (void)		// Objekteigenschaften
{
CEierUhr Wait (this);
WEnumLONG EnumObj;

	if (CreateObjEnumerator (EnumObj.ppi(), ENUMOBJECTTYPE_ACTIVATED, (DWORD)(void *)hWnd())) 
	{
	LONG lRefONr = GetActiveObj(); 
	ObjectPropertyDlg OPDlg (this, &m_rEL, EnumObj, (-1L == lRefONr) ? 0L : lRefONr);

		Wait.Hide();
		OPDlg.Show();
		return OPDlg.Result();
	}
	return false;
}
#else
bool ObjektInfo::doObjectProps (void)		// Objekteigenschaften
{
HRESULT hr = S_OK;

	COM_TRY {
	ResString resCap (IDS_GENOBJPROPS_OR, 128);
	WDataObject IDataObj;

		hr = DataObjectCreateInstance (NULL, IID_IDataObject, IDataObj.ppv());
		if (SUCCEEDED(hr)) 
			hr = SetHWNDData (m_hWnd, IDataObj);

	WProgressIndicator Status;

		Status.CreateInstance(CLSID_ProgressIndicator);
		if (Status.IsValid()) 
			Status -> InitNew (m_hWnd, PIFLAG_RESULT);

		hr = RunPropertyActionSequence (m_hWnd, resCap, &calObjProps, 
				Status, SUCCEEDED(hr) ? (IDataObject *)IDataObj : NULL, NULL);

	} COM_CATCH_RETURN(false);
	return SUCCEEDED(hr);
}
#endif // defined(_FORCE_LEGACY_CODE)

bool ObjektInfo::doHelp (void)				// Hilfe anzeigen
{
	IrisHD -> Show (IDM_OBJHELP);
	return true;
}

bool ObjektInfo::doCancel (void)			// Zeichnen abbrechen
{
	GCancelFlag = GCFAbort;
	return true;
}

bool ObjektInfo::doDraw (void)				// Zeichnen auslösen
{
	DEX_RePaint();
	return true;
}

bool ObjektInfo::doRebuild (void)			// Zeichnen/Neuaufbau auslösen
{
	DEX_PostRebuildSight();
	return true;
}

#if !defined(_USE_XML_GEOCOMPONENTS)
bool TextRecherche(HWND hWnd, bool fORWnd = false);
bool TextReplace(HWND hWnd, bool fORWnd = false);
bool ClassifyObjects(HWND hWnd, bool fORWnd = false);
bool GenerateTextObjects(HWND hWnd, bool fORWnd = false);

bool ObjektInfo::doRecherche (void)			// Objektrecherche
{
	return TextRecherche (m_hWnd, true);
}

bool ObjektInfo::doReplace (void)			// Suchen und ersetzen
{
	return TextReplace (m_hWnd, true);
}

bool ObjektInfo::doClassify (void)			// Klassifikation
{
	return ClassifyObjects (m_hWnd, true);
}

bool ObjektInfo::doGenTextObjects (void)			// Textobjekte erzeugen
{
	return GenerateTextObjects (m_hWnd, true);
}
#endif // !defined(_USE_XML_GEOCOMPONENTS)

// Anzuzeigende Infos auswählen
bool ObjektInfo::doRechResults()
{
CRechResultORWndDlg Dlg (this);
os_string strActOProp;

	if (NULL != m_pIObjProp) 
		Dlg.SetSelectedObjProp (m_pIObjProp);
	else if (!m_fIgnoreObjProp) {
	// nur, wenn globale Objekteigenschaft(en) nicht ignoriert werden soll(en)
	INT_PTR lONr = GetActiveObj(); 
	INT_PTR lIdent = DEX_GetObjIdentEx(lONr);
	HRESULT hr = m_rDBO.Idents().GetObjectProperty (lIdent, strActOProp);

		if (FAILED(hr)) {
			if (NULL != m_rEL.GetActObjPropName()) {
				strActOProp = m_rEL.GetActObjPropName();
				hr = S_OK;
			}
		}	
		if (SUCCEEDED(hr)) 
			Dlg.SetSelectedObjPropName (strActOProp.c_str());
		else
			Dlg.SetSelectedObjProp (NULL);
	}
	else
		Dlg.SetSelectedObjProp (NULL);

	Dlg.SetFlags (m_iFlags);
	Dlg.Show(Centre);
	if (!Dlg.Result())
		return false;		// abgebrochen

// ggf. Objekteigenschaft neu einstellen
bool fChanged = false;
WObjectProperty ObjProp;

	Dlg.GetSelectedObjProp (ObjProp.ppi());		// Fehler ignorieren
	if (ObjProp.IsValid()) {
	// neue Objekteigenschaft verwenden
		if (m_pIObjProp != ObjProp) {
		// bisherige Objekteigenschaft freigeben
			if (NULL != m_pIObjProp) {
				m_pIObjProp -> Release();
				m_pIObjProp = NULL;
			}
			ObjProp -> QueryInterface (&m_pIObjProp);
			fChanged = true;
		}
	}
	else if (NULL != m_pIObjProp) {
	// bisherige Objekteigenschaft freigeben
		m_pIObjProp -> Release();
		m_pIObjProp = NULL;
		m_fIgnoreObjProp = true;
		fChanged = true;
	}
	else if (strActOProp.size() > 0) {
	// auch globale Objekteigenschaft hier nicht mehr anzeigen
		m_fIgnoreObjProp = true;
		fChanged = true;
	}

// ggf. Flags neu einstellen
int iNewFlags = Dlg.GetNewFlags();

	if (m_iFlags != iNewFlags) {
		m_iFlags = iNewFlags;
		fChanged = true;
	}

// ggf. alle Einträge neu generieren
	if (fChanged) {
		if (GetUseEntryCallback()) {
		// schnelle Aktualisierung
		CTable t (OITree());
				
			for (t.First(); t.Valid(); t.Next()) {
			ObjInfoItemLock l(t);
			
				if (l) l -> SetInitialized(false);
			}	
		}
		else {
		// ansonsten dauerts eben etwas länger 
			RefreshAllEntries();
		}

	// neu zeichnen
		m_pKurzInfo -> Update();
		m_pKurzInfo -> RePaint();
	}
	return true;
}

// Räumlichen Filter aus Objektgeometrie erzeugen
bool ObjektInfo::doCreateConnFilter()
{
CREATECONNECTIONFILTER CCF;
char cbBuffer[_MAX_PATH] = { 0 };

	INITSTRUCT(CCF, CREATECONNECTIONFILTER);
	CCF.hWndParent = hWnd();
	CCF.iMode = CF_Polygon_OverlappedObjects;
	CCF.hTargetONr = GetActiveObj();
	CCF.pName = cbBuffer;
	CCF.iLen = sizeof(cbBuffer);
	CCF.fApplySettings = true;
	CCF.fShowApplyAllConnections = true;
	CCF.fApplyAllConnections = true;
	DEX_ShowCreateConnectionFilterDlg(CCF);

	if (IDOK == CCF.iRetVal) 
		return true;

	return false;
}

#else

void ObjektInfo::MenuCommand (MenuCommandEvt e) 
{
	if (e.GetItemID() == IDM_REMOVEORWNDS) {
		DEX_PostRemoveAllORWnds();		// alle ORFenster löschen
		return;
	}

	DEX_CancelMode (true);			// Blinken abschalten
	Update();						// Fenster zeichnen lassen

// erst mal bei der ExtensionList nachfragen, dieser MenuPunkt zu einer 
// Erweiterung gehört, wenn nichts in der LB ist, dann ist das das Problem der 
// Erweiterung
	if (m_rEL.DispatchMenuCommand (e, hWnd())) {
		DEX_CancelMode (false);		// Blinken wieder zuschalten
		return;
	}

// wenn nichts enthalten ist, dann raus
long lONr = GetActiveObj();

	if (lONr == -1L) return;	// nichts in der Listbox
	
// ObjRechFenster-eigene MenuPunkte
	switch (e.GetItemID()) {
	case IDM_ATTRIBUTE:		// allgemeine Merkmale anzeigen
		doShowOIAttribute ();
		break;

	case IDM_TOPOLOGIE:		// topologische Relationen
		ShowOITopologie ();
		break;

	case IDM_THEMATIK:		// thematische Relationen
		ShowOIThematik ();
		break;

	case IDM_OBJAREA:		// Flächeninhalt
		ShowOIObjectArea ();
		break;

	case IDM_OBJCENTRE:		// Flächenschwerpunkt
		ShowOIObjectCentre ();
		break;

	case IDM_OBJDELETE:		// Objekt physisch löschen
		doObjDelete();
		break;

	case IDM_MODALLIDENTS:
		doModAllIdents();
		break;

	case IDM_CREATEKO:		// KomplexObjekt bilden
		CreateKObject();
		break;

	case IDM_OBJPROPS:
		{
		CEierUhr Wait (this);
		IEnum<LONG> *pEnum = NULL;

			if (CreateObjEnumerator (&pEnum, ENUMOBJECTTYPE_ACTIVATED, (DWORD)(void *)hWnd())) 
			{
			ObjectPropertyDlg OPDlg (this, &m_rEL, pEnum, (-1L == lONr) ? 0L : lONr);

				Wait.Hide();
				OPDlg.Show();
				pEnum -> Release();
			}
		}
		break;

	case IDM_ZOOMOBJECTS:
		doZoomIn();
		break;
		
	case IDM_ADDTOLEGEND:
		doAddToLegend();
		break;
		
	case IDM_KOMPLOBJECTS:		// alle anderen Objekte anzeigen
		doComplementObjects();
		break;
		
	case IDM_EXPORT:
		doExportObjects();
		break;
		
	case IDM_OBJHELP:
		IrisHD -> Show (IDM_OBJHELP);
		break;
	}

	App::Exec (ExecWhileEvent);	// erstmal alles abarbeiten
	DEX_CancelMode (false);		// Blinken wieder erlauben
}

void ObjektInfo::MenuInit (MenuInitEvt e) 
{
	if (WM_INITMENU == e.Msg()) return;	// nur WM_INITMENUPOPUP bearbeiten

	if (HIWORD(e.LParam())) {		// SystemMenu
	short iCnt = DEX_ActiveObjectsCount();

		EnableMenuItem (HMENU(e.WParam()), IDM_REMOVEORWNDS, 
			iCnt > 1 ? MF_BYCOMMAND|MF_ENABLED : MF_BYCOMMAND|MF_GRAYED);
		return;
	}

// Alle Erweiterungen fragen, ob sie etwas an den Menu's zu drehen haben
CTable r(EL());

	for (r.First(); r.Valid(); r.Next()) {
	ExtensionLock l(r);

		if (l && l -> isMyMenu (e)) 
		// wenn Menu gefunden wurde
			l -> MenuInit (e, hWnd());
	}	

// eigene MenuPunkte Enable'n
long lONr = GetActiveObj();
bool isArea = (lONr == -1) ? false : DEX_GetObjectType (lONr) == OT_FLAECHE;

	MenuEnable (&ObjektMenu, IDM_OBJAREA, isArea);
	MenuEnable (&ObjektMenu, IDM_OBJCENTRE, isArea);
	MenuEnable (&ObjektMenu, IDM_ADDTOLEGEND, pLegende != NULL);
#if defined(_FORCE_LEGACY_CODE)
	MenuEnable (&ObjektMenu, IDM_EXPORT, g_fFilters);
#endif // defined(_FORCE_LEGACY_CODE)

// MenuText entspr. selektierter Objektanzahl richten
HMENU hMenu = ObjektMenu.Handle (API_MENU_HMENU);

	if (m_ulActCount > 1) {
	// mehr als ein Objekt selektiert
		ModifyMenu (hMenu, IDM_MODALLIDENTS,
			    MF_BYCOMMAND|MF_STRING, IDM_MODALLIDENTS, 
			    ResString (IDS_MODIDENT1, 30).Addr());

		ModifyMenu (hMenu, IDM_OBJDELETE,
			    MF_BYCOMMAND|MF_STRING, IDM_OBJDELETE, 
			    ResString (IDS_OBJDELETE1, 30).Addr());
	} else {
	// genau ein Objekt selektiert              
		ModifyMenu (hMenu, IDM_MODALLIDENTS,
			    MF_BYCOMMAND|MF_STRING, IDM_MODALLIDENTS, 
			    ResString (IDS_MODIDENT, 30).Addr());

		ModifyMenu (hMenu, IDM_OBJDELETE,
			    MF_BYCOMMAND|MF_STRING, IDM_OBJDELETE, 
			    ResString (IDS_OBJDELETE, 30).Addr());
	}
	                         
	DrawMenuBar (m_hWnd);

// wenn kein Objekt selektiert ist, dann MenuPunkte passivieren
bool ifRO = !DEX_GetROModeEx(HACTPROJECT);

	MenuEnable (&ObjektMenu, IDM_OBJDELETE, m_ulActCount > 0 && ifRO);
	MenuEnable (&ObjektMenu, IDM_MODALLIDENTS, m_ulActCount > 0 && ifRO);
	MenuEnable (&ObjektMenu, IDM_ZOOMOBJECTS, m_ulActCount > 0);
}
#endif // _NEWORMENU

// Dialogfenster 'Attribute' generieren ---------------------------------------
//bool ObjektInfo::doShowOIAttribute (void) 
//{
//long lONr = GetActiveObj();
//
//	TX_ASSERT(-1 != lONr);
//	if ((DEX_GetObjectStatus (lONr) & OS_Temp)) 
//		return false;		// kein selektiertes oder temporäres Objekt
//
//	if (isDBTextObjekt (m_rDBO.DB().DBDesc(), lONr)) {
//	// wenn TextObjekt, dann anderes Fenster generieren
//
//		return CurrActDirisW -> EditTextObject (this, lONr);
//	} else {
//	ListObjektInfoDialog Info (this, m_rDBO, lONr, m_rDBO.RetrieveIdent (lONr), m_fSystem);
//
//		Info.Show();
//		return Info.Result();
//	}
//}

#if !defined(_NEWORMENU)
// ObjektInfofenster mit TopologieInfo generieren -----------------------------
void ObjektInfo::ShowOITopologie (void) 
{
CEierUhr Wait (GetParent());
ObjFeld Objekte;                        // ArrayContainer
ErrCode EC;                             // FehlerCode
long lONr = GetActiveObj();

	if (lONr == -1 || (DEX_GetObjectStatus (lONr) & OS_Temp)) 
		return;		// kein selektiertes oder temporäres Objekt

	if ((EC = m_rDBO.DB().RigInfo (lONr, Objekte)) != EC_OKAY) 
		return;

// Identifikatoren filtern
	m_rDBO.DB().IdFilter (Objekte, m_rDBO.Idents());

DEXXCREATEOBJEKTINFO crOI;

	crOI.dwSize = sizeof(DEXXCREATEOBJEKTINFO);
	crOI.lpCaption = StrDup (ResString (IDS_RIGINFOCAPTION, 30), RC_ButtonResponse);
	crOI.lcObjs = &Objekte;
	crOI.pcMColor = new Color (YELLOW);
	crOI.ppntPos = new Point (0, 0);
	crOI.fcnPos = NULL;
	crOI.pData = NULL;

	DEXX_CreateObjektInfo (crOI);	// RechercheFenster generieren

	if (crOI.ppntPos) delete crOI.ppntPos;
	if (crOI.pcMColor) delete crOI.pcMColor;
	if (crOI.lpCaption) delete crOI.lpCaption;
}

// ObjektInfoFenster mit Objekten, die in thematischer Relation stehen --------
void ObjektInfo::ShowOIThematik (void) 
{
CEierUhr Wait (GetParent());
ObjFeld Objekte;                        // ArrayContainer
ErrCode EC;                             // FehlerCode
long ONr = GetActiveObj();

	if (ONr == -1 || (DEX_GetObjectStatus (ONr) & OS_Temp)) 
		return;		// kein selektiertes oder temporäres Objekt

	if ((EC = m_rDBO.DB().RelInfo (ONr, Objekte)) != EC_OKAY)
		return;

// Identifikatoren filtern
	m_rDBO.DB().IdFilter (Objekte, m_rDBO.Idents());

// Dialogfenster generieren
DEXXCREATEOBJEKTINFO crOI;

	crOI.dwSize = sizeof(DEXXCREATEOBJEKTINFO);
	crOI.lpCaption = StrDup (ResString (IDS_RELINFOCAPTION, 30), RC_ButtonResponse);
	crOI.lcObjs = &Objekte;
	crOI.pcMColor = new Color (BLUE);
	crOI.ppntPos = new Point (10, 10);
	crOI.fcnPos = NULL;
	crOI.pData = NULL;

	DEXX_CreateObjektInfo (crOI);	// RechercheFenster generieren

	if (crOI.ppntPos) delete crOI.ppntPos;
	if (crOI.pcMColor) delete crOI.pcMColor;
	if (crOI.lpCaption) delete crOI.lpCaption;
}

// Flächeninhalt der selektieren Fläche anzeigen ------------------------------
void ObjektInfo::ShowOIObjectArea (void) 
{
CTable t(m_rDBO.Shapes().ObjNumTree());
double Area = 0.0;
long lONr = GetActiveObj();

	if (lONr == -1) return;		// kein selektiertes Objekt

CEierUhr Wait (GetParent());

	if (t.Find (&lONr)) {	// ON suchen
	ExtShapeObjectLock l (t);

		if (l) {
		char OutBuff[140];
		char DBuff[20];

		// Flächeninhalt dieses PolyPolygonZuges
			Area = ((GeoFlaeche *)(l -> operator GeoObjekt *())) -> Inhalt (m_rDBO.pCT());

		// Hier noch Skalierung einfügen
//			Area *= (K11*K22);
			Area /= (1000.0*1000.0);

		// Flächeninhalt ausgeben
			strcpy (OutBuff, ResString (IDS_OBJAREA, 100));
			if (Area >= 1.0) {	// im qkm
				strcat (OutBuff, DtoA (DBuff, "%10.3f", Area));
				strcat (OutBuff, ResString (IDS_KILOMETER2, 10));
			} else if (Area >= 0.01) {	// in ha
				strcat (OutBuff, DtoA (DBuff, "%10.3f", Area*1e2));
				strcat (OutBuff, ResString (IDS_HEKTAR, 10));
			} else {	// in qm
				strcat (OutBuff, DtoA (DBuff, "%10.3f", Area*1e6));
				strcat (OutBuff, ResString (IDS_METER2, 10));
			}

		InfoBox IB (ResString (IDS_OBJAREACAP, 30), OutBuff, CurrActDirisW);

			IB.Show();
		}
	}
}

// Flächenschwerpunkt der selektierten Fläche anzeigen ------------------------
void ObjektInfo::ShowOIObjectCentre (void) 
{
CTable t(m_rDBO.Shapes().ObjNumTree());
long lONr = GetActiveObj();

	if (lONr == -1) return;		// kein selektiertes Objekt

	if (t.Find (&lONr)) {	// ON suchen
	ExtShapeObjectLock l (t);
	Punkt Pt;

		if (l) {
		char OutBuff[140];
		char XOutBuff[40], YOutBuff[40];
		double XOut, YOut;

		// Flächenschwerpunkt berechnen
			((GeoFlaeche *)(l -> operator GeoObjekt *())) -> SchwerPunkt (Pt);

		// Koordinaten korrigieren
			m_rDBO.pCT() -> UnScale (Pt, &XOut, &YOut);
			m_rDBO.pCT() -> Transform (&XOut, &YOut);

		// Schwerpunkt ausgeben
			wsprintf (OutBuff, ResString (IDS_SCHWPKTFRMT, 100), 
				  DtoA (XOutBuff, "%10.0f", YOut), 
				  DtoA (YOutBuff, "%10.0f", XOut));

		// Ausgabefenster generieren	
		InfoBox IB (ResString (IDS_OBJCENTRECAP, 40),
			    OutBuff, CurrActDirisW);
			IB.Show();
		}
	}
}
#endif // !_NEWORMENU

#if !defined(_FORCE_LEGACY_CODE)

#if !defined(_USE_XML_GEOCOMPONENTS)

///////////////////////////////////////////////////////////////////////////////
// Komplementäre Objektmenge bilden

static const CLSID *cbComplData[] = 
{
	&CLSID_SelectFromObjectWindow,
	NULL,
	&CLSID_PropertyOperation,
	&CLSID_DestinationObjectWindow,
};
static const IPropertyAction *cbComplPropActs[] = 
{
	NULL,
	NULL,
	NULL,
	NULL,
};
#if !defined(_TRIAS_OLDIMPLEMTATION1)
static const VARIANT *pvComplData[] = {
	NULL,
	NULL,
	NULL,
	NULL,
};
#endif // _TRIAS_OLDIMPLEMTATION1
static CALPCLSID calComplData = 
{
	_countof(cbComplData),
	cbComplData,
	(const IUnknown **)cbComplPropActs,
#if !defined(_TRIAS_OLDIMPLEMTATION1)
	(const VARIANT **)pvComplData,
#endif // _TRIAS_OLDIMPLEMTATION1
};

inline 
void FormatAndAdd (os_string &rStr, LPCSTR pcOks, DWORD dwType, bool fComma)
{
char cbBuffer[64];

	wsprintf(cbBuffer, "%s[%s]:%02x", fComma ? "," : "", pcOks, dwType);
	rStr += cbBuffer;
}

extern "C"
BOOL EXPORTTRIAS WINAPI SelectIdents (long lIdent, DWORD dwTypes, void *pData)
{
char cbOks[MAX_OKS_LEN];

	if (SUCCEEDED(ClassFromIdent ((ULONG)lIdent, cbOks))) {
	os_string *pStr = reinterpret_cast<os_string *>(pData);
	bool fComma = (*pStr == g_cbSelect) ? false : true;		// nur beim Ersten kein Komma

		if (dwTypes & OTPunkt) {
			FormatAndAdd (*pStr, cbOks, OTPunkt, fComma);
			fComma = true;
		}
		if (dwTypes & OTLinie) {
			FormatAndAdd (*pStr, cbOks, OTLinie, fComma);
			fComma = true;
		}
		if (dwTypes & OTFlaeche) {
			FormatAndAdd (*pStr, cbOks, OTFlaeche, fComma);
			fComma = true;
		}
		if (dwTypes & OTText)
			FormatAndAdd (*pStr, cbOks, OTText, fComma);
	}
	return TRUE;
}

bool ObjektInfo::doComplementObjects (void)
{
HRESULT hr = S_OK;

	COM_TRY {
	WProgressIndicator Status;

		Status.CreateInstance(CLSID_ProgressIndicator);
		if (Status.IsValid()) 
			Status -> InitNew (m_hWnd, PIFLAG_RESULT);

	ResString resCap (IDS_COMPLEMENTOBJS_OR, 128);
	WDataObject IDataObj(CLSID_DataTransferObject);

		THROW_FAILED_HRESULT(SetHWNDData (m_hWnd, IDataObj));

	// Einträge selektieren
	os_string str (g_cbSelect);
	ENUMNOKEYLONG ENK;
		
		ENK.eFcn = (ENUMLONGKEYPROC)SelectIdents;
		ENK.ePtr = &str;
		DEXOR_EnumIdentsSelectedEx (m_hWnd, ENK);
	
	// Initialisierungsdaten setzen
	#if !defined(_TRIAS_OLDIMPLEMTATION1)
	CComVariant v0 (L"NoShow=1");		// SelFromObjWnd _nie_ anzeigen
	CComVariant v2 (L"Operation=NotA_And_B");

		pvComplData[0] = &v0;
		pvComplData[2] = &v2;
	#endif // _TRIAS_OLDIMPLEMTATION1

	// direkt zu initialisierende Objekte erzeugen
	WPropertyAction Join(CLSID_PropertyActionJoin);			// throws hr

		{
		WDataObject Data (CLSID_DataTransferObject);		// throws hr
		WPropertyAction Init (CLSID_SelectIdentObjTyp);
		CComVariant v1 (str.c_str());

			THROW_FAILED_HRESULT(SetVariantData (v1, Data, &c_feInitPropAct));
			THROW_FAILED_HRESULT(WPropertyAction2(Init) -> InitFromData (Data, false, 0L));

			THROW_FAILED_HRESULT(WPropertyActionSequence(Join) -> AddAction (Init));
		}
		cbComplPropActs[1] = Join;

		hr = RunPropertyActionSequence (m_hWnd, resCap, &calComplData, Status, IDataObj, NULL, TRUE);

	} COM_CATCH_RETURN(false);
	return SUCCEEDED(hr);
}

///////////////////////////////////////////////////////////////////////////////
// Selektierte Objekte löschen
static const CLSID *cbDelIdClsIds[] = {
	&CLSID_SelectFromObjectWindow,
	&CLSID_DeleteObjects,
};
static CALPCLSID calDelIdClsIds = {
	sizeof(cbDelIdClsIds)/sizeof(cbDelIdClsIds[0]),
	cbDelIdClsIds,
	NULL,
#if !defined(_TRIAS_OLDIMPLEMTATION1)
	NULL,
#endif // _TRIAS_OLDIMPLEMTATION1
};

bool ObjektInfo::doObjDelete (void) 
{
int oldIndex = m_pKurzInfo -> GetCaretIndex ();
HRESULT hr = S_OK;

	COM_TRY {
	ResString resCap (IDS_DELOBJECTCAP_OR, 128);
	WDataObject IDataObj;

		hr = DataObjectCreateInstance (NULL, IID_IDataObject, IDataObj.ppv());
		if (SUCCEEDED(hr)) 
			hr = SetHWNDData (m_hWnd, IDataObj);

	WProgressIndicator Status;

		Status.CreateInstance(CLSID_ProgressIndicator);
		if (Status.IsValid()) 
			Status -> InitNew (m_hWnd, PIFLAG_RESULT);

		hr = RunPropertyActionSequence (m_hWnd, resCap, &calDelIdClsIds, 
				Status, SUCCEEDED(hr) ? (IDataObject *)IDataObj : NULL, NULL);

	} COM_CATCH_RETURN(false);

	ActivateNextItem (oldIndex);		// neues Objekt in ListBox markieren und aktivieren
	UpdateCaption();					// alles gelöscht: IrisWind neuzeichnen
	DEX_RePaint();
	return SUCCEEDED(hr);
}

#endif // !defined(_USE_XML_GEOCOMPONENTS)

#else

HRESULT DeleteObjsInitProgress (HWND hWnd, int iCntSel, IProgressIndicator **ppIProgInd)
{
	*ppIProgInd = NULL;

WProgressIndicator Status;
HRESULT hr = PiCreateInstance (IID_IProgressIndicator, Status.ppv());

	if (FAILED(hr)) return hr;

HWND hNewWnd = Status -> InitNew (hWnd, 0L);

	if (NULL == hNewWnd) return E_FAIL;

	hr = Status -> Restart (0L, (ULONG)iCntSel, 
				  PIFLAG_CAPTION | PIFLAG_STATUS | PIFLAG_RESULT |
				  PIFLAG_TIME | PIFLAG_ADJUSTPERCENT);
	if (FAILED(hr)) return hr;

// diverse Texte initialisieren
ResString resCaption (IDS_OBJDELCAPTION, 64);
ResString resStatus (IDS_OBJDELSTATUS, 64);

	Status -> ChangeText (PIFLAG_CAPTION, resCaption);
	Status -> ChangeText (PIFLAG_ADJUSTPERCENT, resStatus);

	*ppIProgInd = Status.detach();
	return NOERROR;
}

bool ObjektInfo::doObjDelete (void) 
{
int iCntSelected = m_pKurzInfo -> GetNoSelected();

	if (0 == iCntSelected) return false;	// nichts selektiert

CEierUhr Wait (GetParent());
int maxIndex = GetCount();
int oldIndex = m_pKurzInfo -> GetCaretIndex ();
bool fDeleted = false;

	{
	int iCnt = 0;
	WProgressIndicator Status;
	ResString resUndo (IDS_UNDODELETEOBJECT, 30);

		DEX_BeginUndoLevel (resUndo.Addr());
		DeleteObjsInitProgress (hWnd(), iCntSelected, Status.ppi());		// Fehler nicht fatal

		for (int iIndex = maxIndex -1; iIndex >= 0; iIndex--) {
		bool fIsSel = m_pKurzInfo -> GetSelection (iIndex);
		
			if (fIsSel) { 	// nur markierte Löschen
				DeleteObjectIndex (iIndex);
				fDeleted = true;

			// StatusFenster weiterstellen
				if (NULL != (IProgressIndicator *)Status) {
					Status -> SetPosition(++iCnt);
					if (Status -> WasCanceled())
						break;	// 'Abbrechen' gedrückt
				}
			}
		}
	} // Status freigeben

	if (!fDeleted) {
		DEX_CancelUndoLevel (false);
		return false;		// nichts gemacht
	}

// neues Objekt in ListBox markieren und aktivieren
	ActivateNextItem (oldIndex);
	DEX_EndUndoLevel();

// alles gelöscht: IrisWind neuzeichnen
	UpdateCaption();
	DEX_RePaint();
	return true;
}
#endif // defined(_FORCE_LEGACY_CODE)

///////////////////////////////////////////////////////////////////////////////
// neues Objekt in ListBox markieren und aktivieren
void ObjektInfo::ActivateNextItem (int iOldIndex)
{
int ulCnt = GetCount();

	if (ulCnt > 0) {
	// noch ein Objekt da: dann nächstes aktivieren
	int newIndex = (iOldIndex < ulCnt) ? iOldIndex : ulCnt -1;

		m_pKurzInfo -> ChangeSelected (newIndex, true);
		m_pKurzInfo -> SetCaretIndex (newIndex);

	// neues Objekt aktivieren
	long newONr = (long)m_pKurzInfo -> GetItem (newIndex);
	CTable t (OITree());
			
	// neu selektiertes Objekt mitteilen
		ActivateObj (newONr);
		DEXN_ObjectSelected (newONr);
		DEXN_ObjectActivated (newONr);

		if (t.Find (&newONr)) {
		ObjInfoItemLock l(t);
		
			if (l) {
				l -> isActive (true);
				l -> isSelected (true);

				TX_ASSERT(m_ulActCount < OITree().Count());
				m_ulActCount++;		// wieder eins mehr
			}
		}	
	}
}

///////////////////////////////////////////////////////////////////////////////
// Eine Objekteigenschaft wurde modifiziert
bool ObjektInfo::HandleModifyFeature (long lONr, LPCSTR pcName)
{
	if (NULL != pcName)	{	// DEXN_FeatureModifiedEx liefert Namen, DEXN_FeatureModified nicht
	char cbBuffer[_MAX_PATH];

		cbBuffer[0] = '\0';
		if (NULL != m_pIObjProp)
			m_pIObjProp -> GetPropInfo(cbBuffer, sizeof(cbBuffer), NULL);
		else {
		os_string strActOProp;

			if (S_OK == m_rDBO.Idents().GetObjectProperty (DEX_GetObjIdentEx(lONr), strActOProp))
				strcpy (cbBuffer, strActOProp.c_str());
			else if (NULL != m_rEL.GetActObjPropName()) 
				strcpy (cbBuffer, m_rEL.GetActObjPropName());
			else
				return false;		// es muß nichts neu eingelesen werden
		}

	// nur neu einlesen, wenn die derzeit angezeigte Objekteigenschaft modifiziert wurde
	CPropertyName localProp (cbBuffer);
	CPropertyName changedProp (pcName);

		if (localProp == changedProp) 
			RefreshEntry (lONr);	// Rückgabewert nicht auswerten, damit es weitergeht
	}
	return false;		// weitermachen
}

///////////////////////////////////////////////////////////////////////////////
// Einen Objekteintrag neu lesen, dazu die bereits lange existierende Funktion 
// HandleModifyIdent verwenden.
bool ObjektInfo::RefreshEntry (long lONr, bool fDoNotHideExisting)
{
	return HandleModifyIdent (lONr, 0L, 0L, false, fDoNotHideExisting);
}

///////////////////////////////////////////////////////////////////////////////
// neue Objekteigenschaft setzen
bool ObjektInfo::SetNewObjectProp (SHOWOBJPROP *pSOP)
{
	if (NULL != m_pIObjProp) {
		m_pIObjProp -> Release();
		m_pIObjProp = NULL;
	}

// neue Objekteigenschaft einstellen
	if (NULL != pSOP -> m_pIObjProp) {
	HRESULT hr = pSOP -> m_pIObjProp -> QueryInterface (IID_IObjectProperty, (LPVOID *)&m_pIObjProp);

		if (FAILED(hr)) 
			return false;
	}

// evtl. alle Einträge neu generieren
	if (pSOP -> m_iFlags & SOPReloadProps) 
		RefreshAllEntries();
	return true;
}

bool ObjektInfo::RefreshAllEntries(bool fDoNotHideExisting)
{
CEierUhr wait(this);
vector<INT_PTR> vecObjs;
CTable t(OITree());

	for (t.First(); t.Valid(); t.Next()) {
	ObjInfoItemLock l(t);

		if (!l) continue;
		vecObjs.push_back(l -> ONr());
	}

	for (vector<INT_PTR>::iterator it = vecObjs.begin(); it != vecObjs.end(); ++it)
		RefreshEntry (*it, fDoNotHideExisting);

	return true;
}

///////////////////////////////////////////////////////////////////////////////
// Umklassifizieren eines Objektes der Liste 
bool ObjektInfo::HandleModifyIdentDirect (
	long lONr, long lIdent, long lNewONr, bool fUndo, bool fDoNotHideExisting) 
{
	if (lONr == 0L || -1L == lONr) 
		return false;		// ungültige Objektnummer
	
	if (-1 == FindObject (lONr))
		return false;		// nicht in diesem Fenster enthalten

	if (0L == lNewONr) 
		lNewONr = lONr;		// ObjektNummer bleibt gleich
	if (0L == lIdent) 
		lIdent = DEX_GetObjIdentEx(lONr);

// Identifikator in der ListBox ändern
CTable t(OITree());
Color oldColor (BLACK);
Color oldActColor (BLACK);
Color oldOPColor (BLACK);
bool oldSelection = false;

	if (t.Find (&lONr)) {
	ObjInfoItemLock l(t);

		if (l) {
			oldColor = l -> StringColor();
			oldActColor = l -> ActColor();
			oldOPColor = l -> ObjPropColor();
			oldSelection = l -> isSelected();
		}
	} 	// Lock aufheben
	else 
		return false;		// in diesem Fenster nicht vertreten

bool fExistsOP = true;
HRESULT hr = NOERROR;

// wenn ObjProp vorgegeben ist, dann diese nutzen, sonst Voreinstellung
	if (m_fExistsOP) {
		if (m_pIObjProp)
			hr = m_pIObjProp -> Eval (lNewONr, m_pBuffer, _MAX_PATH, NULL);
		else {
		os_string strActOProp;

			if (S_OK == m_rDBO.Idents().GetObjectProperty (lIdent, strActOProp))
				hr = m_rEL.InvokeActObjProp (lNewONr, m_pBuffer, _MAX_PATH, NULL, strActOProp.c_str());
			else if (NULL != m_rEL.GetActObjPropName()) 
				hr = m_rEL.InvokeActObjProp (lNewONr, m_pBuffer, _MAX_PATH, NULL);
			else
				hr = S_FALSE;	// auch keine globale ObjProp --> Objektklasse anzeigen
		}

		if (S_OK == hr && !(m_iFlags & ROHideDatasource) && DEX_GetOpenConnectionCount (QDCAllOpen|QDCCountQueryDefs) > 1) {
		char cbBuffer[_MAX_PATH];
		HPROJECT hPr = DEX_GetObjectsProject(lIdent);

			TX_ASSERT(HACTCONNECTION != hPr);
			if (NULL != DEX_GetDataSourceShortName (hPr, cbBuffer)) {
				strcat (m_pBuffer, " (");
				strcat (m_pBuffer, cbBuffer);
				strcat (m_pBuffer, ")");
			}
		}
	}

	if (S_OK != hr) {
	// wenn keine OPF gegeben ist, dann IdentKurzText verwenden
		strncpy (m_pBuffer, m_rDBO.GetKurzText(lIdent, TRUE), _MAX_PATH);	// default: IdKurzText
		m_pBuffer[_MAX_PATH-1] = '\0';
		if (S_FALSE != GetScode(hr))
			fExistsOP = false;
	}

// noch mal nen Rundspruch losschicken
RECHOBJECT RO;

	INITSTRUCT(RO, RECHOBJECT);
	RO.lONr = lNewONr;
	RO.lIdent = lIdent;
	RO.lpText = m_pBuffer;
	RO.iTextLen = _MAX_PATH-1;
	RO.iOTyp = (short)m_rDBO.RetrieveObjTyp(lNewONr);
	RO.iFlags = m_iFlags & ROHideFlags;	// Voreinstellung verwenden
	if (fDoNotHideExisting)
		RO.iFlags |= ROShowHidden;
	if (DEXN_QueryRechObject (RO))
		return S_FALSE;				// Objekt hat nicht zu recherchierenden Ident oder jemand hat was dagegen

// Farben abgleichen
	if (fExistsOP) 
		oldOPColor = oldColor;
	else {
		if (RO.iOTyp == OT_KO) 	// Komplexobjekte werden DunkelGrün
			oldOPColor = Color(ColorVal(64), ColorVal(0), ColorVal(0));
		else {
		COLORREF cr = GetSysColor (COLOR_GRAYTEXT);

			oldOPColor = (Color &)cr;
		}
	}

	if (FormatROString (m_pBuffer1, RO))
	{	// Objekt hat zu rechierenden Ident
	int iIndex = FindObject (lONr);
	int iCurrIndex = m_pKurzInfo -> GetCaretIndex();

		TX_ASSERT(0 <= iIndex);

	// Objekt deaktivieren
		if (lONr != lNewONr) {
			if (iIndex == iCurrIndex) {
				DEXN_ObjectUnSelected (lONr);
				if (oldSelection) {
					DEXN_ObjectDeActivated (lONr);
					DeActivateObj();
				}
			} else if (oldSelection) {
				DEXN_ObjectDeActivated (lONr);
				DeActivateObj (true, false, lONr);
			}			
		}

	// alten Eintrag aus Baum herauslöschen, neuen erzeugen
		t.Delete();	
		{
		ObjInfoItemCreator OIICr (OITree());
		ObjInfoItem *pII = ContCreate (OIICr, ObjInfoItem) 
					  (lNewONr, OTypToBits (ObjTyp(RO.iOTyp)), m_pBuffer1, 
					   !(m_iFlags & ROHideText) ? m_pBuffer : g_cbNil, 
					   oldColor, oldActColor, oldOPColor);

			if (pII)
				pII -> isSelected (oldSelection);
		}		// neues Element wirklich wegspeichern

	// neues Objekt evtl selektieren
		if (lONr != lNewONr) {
			if (iCurrIndex == iIndex) {
				ActivateObj (lNewONr);
				DEXN_ObjectSelected (lNewONr);
				if (oldSelection)
					DEXN_ObjectActivated (lNewONr);
			} 
			else if (oldSelection) {
				ActivateObj (lNewONr, true, false);
				DEXN_ObjectActivated (lNewONr);
			}
		}

		if (fUndo) {
		WUndoRedoReplaceObjectWnd Undo;
		HRESULT hr = UndoCreateInstance (IID_IUndoRedoReplaceObjectWnd, Undo.ppv());

			if (SUCCEEDED(hr) && S_OK == Undo -> Init (m_hWnd, lONr, lNewONr)) 
				DEX_AddUndoRedo (Undo.p);
		}

	// den Eintrag in der Listbox ersetzen, aber nur neu zeichnen, 
	// wenn der neue Eintrag derzeit sichtbar ist
		if (0 <= iIndex) {
		string str = string (m_pBuffer1) + m_pBuffer;

			m_pKurzInfo -> ForwardEvent(WM_SETREDRAW, FALSE);

			m_pKurzInfo -> SetItemEx (lNewONr, str.c_str(), iIndex);
			m_pKurzInfo -> ChangeSelected (iIndex, oldSelection);

		HWND hCtrl = m_pKurzInfo -> Handle(API_WINDOW_HWND);
		int iTop = ListBox_GetTopIndex(hCtrl);
			
			if (iTop != LB_ERR && iIndex >= iTop && iIndex < iTop + m_iCntItems) 
				InvalidateRect(hCtrl, NULL, true);

			m_pKurzInfo -> ForwardEvent(WM_SETREDRAW, TRUE);
		}
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// Umklassifizieren eines Objektes der Liste 
bool ObjektInfo::HandleModifyIdentCallback (
	long lONr, long lIdent, long lNewONr, bool fUndo, bool fDoNotHideExisting) 
{
	if (lONr == 0L || -1L == lONr) 
		return false;		// ungültige Objektnummer
	
int iIndex = FindObject (lONr);

	if (-1 == iIndex)
		return false;		// nicht in diesem Fenster enthalten

	if (0L == lNewONr) 
		lNewONr = lONr;		// ObjektNummer bleibt gleich
	if (0L == lIdent) 
		lIdent = DEX_GetObjIdentEx(lNewONr);

// Identifikator in der ListBox ändern
CTable t(OITree());
Color oldColor (BLACK);
Color oldActColor (m_C);
Color oldOPColor (BLACK);
bool oldSelection = false;
short oldType = 0;

	if (t.Find (&lONr)) {
	ObjInfoItemLock l(t);

		if (l && l -> IsInitialized()) {
			oldColor = l -> StringColor();
			oldActColor = l -> ActColor();
			oldOPColor = l -> ObjPropColor();
			oldSelection = l -> isSelected();
            oldType = l -> GetOType();
		} 
		else {
			oldSelection = m_pKurzInfo -> GetSelection(iIndex);
		}
	} 	// Lock aufheben
	else 
		return false;		// in diesem Fenster nicht vertreten

int iCurrIndex = m_pKurzInfo -> GetCaretIndex();

	TX_ASSERT(0 <= iIndex);

// Objekt deaktivieren
	if (lONr != lNewONr) {
		if (iIndex == iCurrIndex) {
			DEXN_ObjectUnSelected (lONr);
			if (oldSelection) {
				DEXN_ObjectDeActivated (lONr);
				DeActivateObj();
			}
		} 
		else if (oldSelection) {
			DEXN_ObjectDeActivated (lONr);
			DeActivateObj (true, false, lONr);
		}			
	}

// alten Eintrag aus Baum herauslöschen, neuen erzeugen
	m_pKurzInfo -> SetItemEx (lNewONr, g_cbNil, iIndex);		// Eintrag freigeben
	t.Delete();	
	{
	ObjInfoItemCreator OIICr (OITree());
	ObjInfoItem *pII = ContCreate (OIICr, ObjInfoItem) (
        lNewONr, lIdent, oldType, oldActColor);

		if (pII) {
			pII -> isSelected (oldSelection);
			pII -> HideEntryIfHidden(!fDoNotHideExisting);
		}
	}		// neues Element wirklich wegspeichern

// neues Objekt evtl selektieren
	if (lONr != lNewONr) {
		if (iCurrIndex == iIndex) {
			ActivateObj (lNewONr);
			DEXN_ObjectSelected (lNewONr);
			if (oldSelection)
				DEXN_ObjectActivated (lNewONr);
		} 
		else if (oldSelection) {
			ActivateObj (lNewONr, true, false);
			DEXN_ObjectActivated (lNewONr);
		}
	}

	if (fUndo) {
	WUndoRedoReplaceObjectWnd Undo;
	HRESULT hr = UndoCreateInstance (IID_IUndoRedoReplaceObjectWnd, Undo.ppv());

		if (SUCCEEDED(hr) && S_OK == Undo -> Init (m_hWnd, lONr, lNewONr)) 
			DEX_AddUndoRedo (Undo.p);
	}

// den Eintrag in der Listbox ersetzen, aber nur neu zeichnen, 
// wenn der neue Eintrag derzeit sichtbar ist
	if (0 <= iIndex) {
	HWND hCtrl = m_pKurzInfo -> Handle(API_WINDOW_HWND);
	RECT rcClient, rcItem, rcToPaint;

		GetClientRect (hCtrl, &rcClient);
		ListBox_GetItemRect(hCtrl, iIndex, &rcItem);

		m_pKurzInfo -> SetItemEx (lNewONr, g_cbNil, iIndex);
		m_pKurzInfo -> ChangeSelected (iIndex, oldSelection);

		IntersectRect (&rcToPaint, &rcClient, &rcItem);
		if (!IsRectEmpty (&rcToPaint))
			InvalidateRect(hCtrl, NULL, true);
	}
	return true;
}

// Herausnehmen eines Objektes aus der Liste ----------------------------------
bool ObjektInfo::HandleDeleteObject (long lONr, bool fUpdateCaption, bool fUndo) 
{
	if (lONr == -1L) return false;

int iIndex = FindObject (lONr);
int iCurrIndex = m_pKurzInfo -> GetCaretIndex();

	if (iIndex != -1) {	// in diesem Fenster vertreten
	bool fSel = m_pKurzInfo -> GetSelection (iIndex);
	bool fActivated = (iIndex == iCurrIndex) ? true : false;

		if (fUndo) {
		LPUNDOREDODELETEOBJECTWND pIUndo = NULL;
		HRESULT hr = UndoCreateInstance (IID_IUndoRedoDeleteObjectWnd,
						 (LPVOID *)&pIUndo);

			if (SUCCEEDED(hr) && 
				S_OK == pIUndo -> Init2 (hWnd(), lONr, fSel, fActivated)) 
			{
				DEX_AddUndoRedo (pIUndo);
			}
			if (pIUndo) pIUndo -> Release();
		}

	// Objekt deaktivieren
		if (fActivated) {
			DEXN_ObjectUnSelected (lONr);
			if (fSel) {
				DEXN_ObjectDeActivated (lONr);
				DeActivateObj();
			}
		} 
		else if (fSel) {
			DEXN_ObjectDeActivated (lONr);
			DeActivateObj (true, true, lONr);
		}			
	
	// aus Listbox entfernen
		m_pKurzInfo -> DelItemEx ((ushort)iIndex);
		if (fSel) {
			TX_ASSERT(m_ulActCount > 0);
			m_ulActCount--;		// auch hier eins weniger
		}

		DEXN_ObjectDeletedFromList(lONr);

	// Caption richten
		if (fUpdateCaption) UpdateCaption();
	}
	return true;
}

// löschen eines Objektes -----------------------------------------------------
void ObjektInfo::DeleteObject (long lONr)
{
	DEX_DeleteObjectEx (lONr);	// löschen mit Undo
}

void ObjektInfo::DeleteObjectIndex (short iIndex) 
{
long lONr = (long)m_pKurzInfo -> GetItem (iIndex);	// ObjektNummer holen

	if (lONr == -1) return;		// Objekt nicht gefunden

// Objekt(e) komplett herauslöschen (Textobjekt wird ebenfalls gelöscht)
// Über die abgesetzten Notifikationen werden die Objekte aus der Listbox gelöscht
// (HandleDeleteObject)
	DEX_DeleteObjectEx (lONr);	// löschen mit Undo
}

#if !defined(_USE_XML_GEOCOMPONENTS)
///////////////////////////////////////////////////////////////////////////////
// Modifizieren der Objektidentifikatoren aller selektierten Objekte 
static const CLSID *cbModIdClsIds[] = {
	&CLSID_SelectFromObjectWindow,
	&CLSID_ModifyIdent,
};
#if !defined(_TRIAS_OLDIMPLEMTATION1)
static VARIANT *pvModIdData[] = {
	NULL,
	NULL,
};
#endif // _TRIAS_OLDIMPLEMTATION1
static CALPCLSID calModIdClsIds = {
	sizeof(cbModIdClsIds)/sizeof(cbModIdClsIds[0]),
	cbModIdClsIds,
	NULL,
#if !defined(_TRIAS_OLDIMPLEMTATION1)
	const_cast<const VARIANT **>(pvModIdData),
#endif // _TRIAS_OLDIMPLEMTATION1
};

bool ObjektInfo::doModAllIdents (void) 
{
HRESULT hr = S_OK;

	COM_TRY {
	WProgressIndicator Status;

		Status.CreateInstance(CLSID_ProgressIndicator);
		if (Status.IsValid()) 
			Status -> InitNew (m_hWnd, PIFLAG_RESULT);

	ResString resCap (IDS_MODIDENTCAP_OR, 128);
	WDataObject IDataObj;

		 hr = DataObjectCreateInstance (NULL, IID_IDataObject, IDataObj.ppv());
		if (SUCCEEDED(hr)) 
			hr = SetHWNDData (m_hWnd, IDataObj);

	#if !defined(_TRIAS_OLDIMPLEMTATION1)
	CComVariant v (L"CheckMode=0;Checked=0;ShowConnections=0");

		pvModIdData[1] = &v;		// Initialisierungsdaten setzen
	#endif // _TRIAS_OLDIMPLEMTATION1

		hr = RunPropertyActionSequence (m_hWnd, resCap, &calModIdClsIds, 
				Status, SUCCEEDED(hr) ? (IDataObject *)IDataObj : NULL, NULL);
				
	} COM_CATCH_RETURN(false);
	return SUCCEEDED(hr);
}
#endif // !defined(_USE_XML_GEOCOMPONENTS)

#if !defined(_USE_XML_GEOCOMPONENTS)
///////////////////////////////////////////////////////////////////////////////
// Löschen von Objekteigenschaften an allen selektierten Objekten
static const CLSID *cbDelObjPropClsIds[] = {
	&CLSID_SelectFromObjectWindow,
	&CLSID_DeleteObjectProperty,
};
static CALPCLSID calDelObjPropClsIds = {
	sizeof(cbDelObjPropClsIds)/sizeof(cbDelObjPropClsIds[0]),
	cbDelObjPropClsIds,
	NULL,
#if !defined(_TRIAS_OLDIMPLEMTATION1)
	NULL,
#endif // _TRIAS_OLDIMPLEMTATION1
};

bool ObjektInfo::doDeleteObjProps (void) 
{
HRESULT hr = S_OK;

	COM_TRY {
	WProgressIndicator Status;

		Status.CreateInstance(CLSID_ProgressIndicator);
		if (Status.IsValid()) 
			Status -> InitNew (m_hWnd, PIFLAG_RESULT);

	ResString resCap (IDS_DELETEOBJEPROP_CAPTION_OR, 128);
	WDataObject IDataObj;

		 hr = DataObjectCreateInstance (NULL, IID_IDataObject, IDataObj.ppv());
		if (SUCCEEDED(hr)) 
			hr = SetHWNDData (m_hWnd, IDataObj);

		hr = RunPropertyActionSequence (m_hWnd, resCap, &calDelObjPropClsIds, 
				Status, SUCCEEDED(hr) ? (IDataObject *)IDataObj : NULL, NULL);
				
	} COM_CATCH_RETURN(false);
	return SUCCEEDED(hr);
}
#endif // !defined(_USE_XML_GEOCOMPONENTS)

#if !defined(_USE_XML_GEOCOMPONENTS)
///////////////////////////////////////////////////////////////////////////////
// Koperen (doppeln) aller selektierten Objekte
static const CLSID *cbCopyObjClsIds[] = {
	&CLSID_SelectFromObjectWindow,
	&CLSID_ObjekteDoppeln,
	&CLSID_ModifyIdent,
	&CLSID_DestinationObjectWindow,
};
#if !defined(_TRIAS_OLDIMPLEMTATION1)
static VARIANT *pvData[] = {
	NULL,
	NULL,
	NULL,
	NULL,
};
#endif // _TRIAS_OLDIMPLEMTATION1
static CALPCLSID calCopyObjClsIds = {
	sizeof(cbCopyObjClsIds)/sizeof(cbCopyObjClsIds[0]),
	cbCopyObjClsIds,
	NULL,
#if !defined(_TRIAS_OLDIMPLEMTATION1)
	const_cast<const VARIANT **>(pvData),
#endif // _TRIAS_OLDIMPLEMTATION1
};

bool ObjektInfo::doCopyObjects (void) 
{
HRESULT hr = S_OK;

	COM_TRY {
	WProgressIndicator Status;

		Status.CreateInstance(CLSID_ProgressIndicator);
		if (Status.IsValid()) 
			Status -> InitNew (m_hWnd, PIFLAG_RESULT);

	ResString resCap (IDS_COPYOBJECTSCAP_OR, 128);
	WDataObject IDataObj;

		hr = DataObjectCreateInstance (NULL, IID_IDataObject, IDataObj.ppv());
		if (SUCCEEDED(hr)) 
			hr = SetHWNDData (m_hWnd, IDataObj);

	#if !defined(_TRIAS_OLDIMPLEMTATION1)
	CComVariant v (L"CheckMode=1;Checked=1;ShowConnections=0");

		pvData[2] = &v;		// Initialisierungsdaten setzen
	#endif // _TRIAS_OLDIMPLEMTATION1
		hr = RunPropertyActionSequence (m_hWnd, resCap, &calCopyObjClsIds, 
				Status, SUCCEEDED(hr) ? (IDataObject *)IDataObj : NULL, NULL);

	} COM_CATCH_RETURN(false);
	return SUCCEEDED(hr);
}
#endif // !defined(_USE_XML_GEOCOMPONENTS)

///////////////////////////////////////////////////////////////////////////////
// Modifizieren eines ObjektIdentifikators 
void ObjektInfo::ModObjIdentEx (long lONr, long newId, long SelOldId, short iIndex)
{
long oldId = DEX_GetObjIdent (lONr);

	if (SelOldId == -1L || SelOldId == oldId) {
	int iObjIndex = (-1 == iIndex) ? FindObject (lONr) : iIndex;

#if defined(_FORCE_LEGACY_CODE)
		m_rDBO.DB().SetDirty();
#endif // _FORCE_LEGACY_CODE
		ModObjIdent (lONr, oldId, newId, iObjIndex);
	}
}

extern char cFVisTyp (ObjTyp);

void ObjektInfo::ModObjIdent (long lONr, long, long newId, int) 
{
// umklassifizieren
MODOBJIDENT MOI;
				
	INITSTRUCT (MOI, MODOBJIDENT);
	MOI.lONr = lONr;
	MOI.lNewIdent = newId;
	MOI.iMode = MODIDENT_ADDTOVIEW|OTypToBits((ObjTyp)DEX_GetObjectType(lONr));
	DEX_ModObjectIdent (MOI);
}

///////////////////////////////////////////////////////////////////////////////
// Auslesen des aktuell selektierten Objektes 
long ObjektInfo::GetActiveObj (void)
{
	if (m_lActObj != -1) 
		return m_lActObj;
	else if (OITree().Count() > 0) {
	int iIndex = m_pKurzInfo -> GetCaretIndex();

		if (iIndex != -1)
			return (long)m_pKurzInfo -> GetItem (iIndex);
	}
	return -1L;
}

///////////////////////////////////////////////////////////////////////////////
// Ändern der SelektionsFarbe eines Objektes im angegebenen Fenster 
bool ObjektInfoListe::ChangeActiveColor (CHANGEACTIVECOLOR *pCAC)
{
CTable t (*this);

	if (t.Find ((void *)&pCAC -> hWnd)) {
	ObjektInfoLock l(t);
	
		if (l) 
			return l -> ChangeActiveColor (pCAC -> lONr, *(Color *)&pCAC -> newC);
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////////
// Ändern der SelektionsFarbe eines markierten Objektes 
bool ObjektInfo::ChangeActiveColor (long lONr, Color &newC)
{
CTable t (OITree());

	if (t.Find (&lONr)) {
	ObjInfoItemLock l(t);
	
		if (l) {
			newC = l -> ChangeActiveColor (newC);
			return true;
		}
	}        
	return false;
}

///////////////////////////////////////////////////////////////////////////////
// Dispatcher für diverse Messages an dieses Fenster 
LRESULT EXPORTTRIAS ObjektInfo::Dispatch (Event e)
{
	if (e.Msg() == __DexCmd) {
	// diese Meldung ist für uns
		switch (e.WParam()) {
		case DEX_DELOBJECT:
			return DEX_DeleteObject (e.LParam());		// einfach weiterreichen

		case DEX_MODOBJIDENT:
			{
			MODOBJIDENT *pMOI = (MODOBJIDENT *)e.LParam();

				ModObjIdentEx (pMOI -> lONr, pMOI -> lNewIdent);
			}
			break;

		case DEX_ENUMALLIDENTS:		// alle Idents in Listbox liefern
			{
			ENUMNOKEYLONG *pK = (ENUMNOKEYLONG *)e.LParam();
			
				return EnumIdents (pK -> eFcn, pK -> ePtr, false);
			}
			break;

		case DEX_ENUMIDENTSSELECTED:	// alle selektierten Idents in Listbox liefern
			{
			ENUMNOKEYLONG *pK = (ENUMNOKEYLONG *)e.LParam();
			
				return EnumIdents (pK -> eFcn, pK -> ePtr, true);
			}
			break;

		case DEX_ENUMALLIDENTSEX:		// alle Idents in Listbox liefern
			{
			ENUMNOKEYLONG *pK = (ENUMNOKEYLONG *)e.LParam();
			
				return EnumIdents (pK -> eFcn, pK -> ePtr, false, true);
			}
			break;

		case DEX_ENUMIDENTSSELECTEDEX:	// alle selektierten Idents in Listbox liefern
			{
			ENUMNOKEYLONG *pK = (ENUMNOKEYLONG *)e.LParam();
			
				return EnumIdents (pK -> eFcn, pK -> ePtr, true, true);
			}
			break;

		case DEX_QUERYCNTACTIVEOBJECTS:		// Anzahl der selektierten Objekte
			*(short *)e.LParam() = (short)m_ulActCount;
			break;
			
		case DEX_ADDOBJECTTOLISTEX:		// neuen Eintrag in der ListBox machen
		case DEX_ADDOBJECTTOLIST:
			{
			long lONr = e.LParam();
			
				if (lONr != -1L) {
				bool fUndo = (e.WParam() == DEX_ADDOBJECTTOLISTEX) ? true : false;

					RetrieveObjInfo (lONr, -1, NULL, fUndo);		// mit Undo
				}

			// Caption richten
				UpdateCaption();
			}
			break;

		case DEX_REMOVEOBJECTFROMLISTEX:
		case DEX_REMOVEOBJECTFROMLIST:
		// Objekt aus ListBox entfernen und Markierung rücksetzen
			if (m_pKurzInfo) {
			bool fUndo = (e.WParam() == DEX_REMOVEOBJECTFROMLISTEX) ? true : false;

				return HandleDeleteObject (e.LParam(), true, fUndo);
			}
			return false;

		case DEX_OBJECTSELECTED:
			if (m_pKurzInfo) {
			long lONr = e.LParam();

				if (lONr != -1) {
				int iObjIndex = FindObject (lONr);

					if (iObjIndex != -1) {
						if (!m_pKurzInfo -> GetSelection (iObjIndex))
							m_ulActCount++;
						m_pKurzInfo -> ChangeSelected (iObjIndex);
						UpdateActivation (iObjIndex);
					}
				} else {
				// alle selektieren
					m_pKurzInfo -> ChangeSelected (Range (0, (int)GetCount()-1));
					m_ulActCount = UpdateActivation();
				}
				UpdateCaption();
			} else
				return false;
			break;

		case DEX_OBJECTUNSELECTED:
			if (m_pKurzInfo) {
			long lONr = e.LParam();

				if (lONr != -1) {
				int iObjIndex = FindObject (e.LParam());

					if (iObjIndex != -1) {
						if (m_pKurzInfo -> GetSelection (iObjIndex))
							m_ulActCount--;
						m_pKurzInfo -> ChangeSelected (iObjIndex, false);
						UpdateActivation (iObjIndex);
					}
				} else {
				// alles deselektieren
					m_pKurzInfo -> ChangeSelected (Range (0, (int)GetCount()-1), false);
					m_ulActCount = UpdateActivation();
				}
				UpdateCaption();
			} else
				return false;
			break;

		case DEX_OBJECTACTIVATED:
			if (m_pKurzInfo) {
			int iObjIndex = FindObject (e.LParam());

				if (iObjIndex != -1) {
					m_pKurzInfo -> SetCaretIndex (iObjIndex);
					UpdateActivation (iObjIndex);
					UpdateCaption();	// Caption dieses Fensters aktualisieren
				}
			} else
				return false;
			break;

		case DEX_RECHOBJECTSTATUS:
			{
			RECHOBJECT *pRO = (RECHOBJECT *)e.LParam();

				TX_ASSERT(sizeof(RECHOBJECT) == pRO->dwSize);
				TX_ASSERT(IsValidONr(pRO -> lONr));

			int iIndex = FindObject (pRO -> lONr);
			short iRes = 0L;

				if (iIndex != -1) {
					iRes |= RSListed;
					if (m_pKurzInfo -> GetSelection (iIndex))
						iRes |= RSSelected;
					if (m_pKurzInfo -> GetCaretIndex() == iIndex)
						iRes |= RSActivated;

				CTable t(OITree());

					if (pRO -> iFlags & (RSFillIdent|RSFillText|RSFillOTyp) &&
						t.Find (&pRO -> lONr)) 
					{
					ObjInfoItemLock l (t);

						if (l) {
							if (pRO -> iFlags & RSFillIdent) 
								pRO -> lIdent = DEX_GetObjIdentEx(pRO -> lONr);
							if ((pRO -> iFlags & RSFillText) && pRO -> lpText) {
								strncpy (pRO -> lpText, l -> PropText(), pRO -> iTextLen);
								pRO -> lpText[pRO -> iTextLen-1] = '\0';
							}
							if (pRO -> iFlags & RSFillOTyp) 
								pRO -> iOTyp = l -> GetOType();
						}
					}
					pRO -> iFlags |= iRes;
				}
			}
			break;

		case DEX_CANCELMODE:
			return HandleCancelMode ((e.LParam() != 0) ? true : false);
			
		case DEX_GETSELECTEDTYPES:
			if (e.LParam()) *((short *)e.LParam()) = m_iActObjTypes;
			break;

        case DEX_QUERYIDENTOBJECTCOUNT:
            return QueryObjectCount((IDENTOBJECTCOUNT *)e.LParam());

        case DEX_EXECUTECOMMANDSEQUENCE:
            return ExecuteSequence();

#if !defined(WIN16)
		case DEX_SHOWOBJPROP:		// diese Objekteigenschaft anzeigen
			return SetNewObjectProp ((SHOWOBJPROP *)e.LParam());

		case DEX_REPLACEOBJECTINLIST:
		case DEX_REPLACEOBJECTINLISTEX:
			{
			bool fUndo = (e.WParam() == DEX_REPLACEOBJECTINLISTEX) ? true : false;

				return ReplaceObjectInList ((REPLACEOBJECT *)e.LParam(), fUndo);
			}

		case DEX_SETTEXT:
			{
			IrisWind *pWnd = static_cast<IrisWind *>(GetParent());
			string strT = pWnd->CorrectCaption (this, (LPSTR)e.LParam());
			
				Window::UpdateCaption(strT.c_str());
				UpdateCaption();
			}
			return true;
#endif // WIN16

#if !defined(_NO_ROLLUP_ORWND)
		case DEX_TOGGLEROLLUPSTATUS:
#if _TRiAS_VER < 0x0400
			if (0 != g_dwVer4)
#endif // _TRiAS_VER < 0x0400
			{
			bool fWasRolledUp = m_fIsRolledUp;
			bool fNewRollUpStatus = e.LParam() ? true : false;

				if (m_fIsRolledUp != fNewRollUpStatus) {
					ForwardEvent(WM_COMMAND, IDM_TOGGLEROLLUP);
					m_fIsRolledUp = fNewRollUpStatus;
				}
				return fWasRolledUp ? TRUE : FALSE;
			}
			break;

		case DEX_QUERYROLLUPSTATUS:
			{
#if _TRiAS_VER < 0x0400
				if (0 == g_dwVer4)
					return FALSE;
#endif // _TRiAS_VER < 0x0400
				return m_fIsRolledUp ? TRUE : FALSE;
			}
			break;
#endif // !defined(_NO_ROLLUP_ORWND)

		case DEX_REFRESHENTRY:
			{
				if (0 != e.LParam())
					return RefreshEntry(e.LParam(), true);	// einen Eintrag neu einlesen
				else
					return RefreshAllEntries(true);		// alle Einträge neu einlesen
			}
			break;

		case WM_CHANGEMARKCOLOR:
			return (long &)SetColor((Color &)e.LParam());

		case WM_QUERYMARKCOLOR:
			return (long &)m_C;

		default:
			return OwnerDrawDialogWindow::Dispatch (e);	// weiterleiten
		}
	}

#if !defined(WIN16)
	else switch (e.Msg()) {
	case WM_FAKENOTIFYFORWIN95:
	// do Drag'n Drop
		return OnNotify (e.WParam(), e.LParam());

	case WM_VSCROLL:
	// Scroll during Drag'n Drop: forward to ListBox
		return m_pKurzInfo -> ForwardEvent(e);

	case WM_GETMINMAXINFO:
		return OnGetMinMaxInfo ((MINMAXINFO *)e.LParam());

#if !defined(_NO_ROLLUP_ORWND)
	case WM_NCPAINT:
		return OnNcPaint(e);

	case WM_NCACTIVATE:
		return OnNcActivate(e);

	case WM_SETTEXT:
		return OnSetText(e);
		
	case WM_NCHITTEST:
		return OnNcHitTest(e);

	case WM_NCLBUTTONDOWN:
		return OnNcLButtonDown(e);
#endif // !defined(_NO_ROLLUP_ORWND)

	default:
		return OwnerDrawDialogWindow::Dispatch (e);	// weiterleiten
	}
#else // WIN16
	else 
		return OwnerDrawDialogWindow::Dispatch (e);	// weiterleiten
#endif // WIN16

	return true;
}

#if !defined(WIN16)
BOOL ObjektInfo::PreTranslateMsg (MSG *pMsg)		// Accels bearbeiten
{
	if (m_hAccel && ::TranslateAccelerator(m_hWnd, m_hAccel, pMsg))
		return true;

#if !defined(_NO_ROLLUP_ORWND)
	if (WM_MOUSEMOVE == pMsg -> message) 
		OnMouseMove (pMsg -> message, pMsg -> wParam, pMsg -> lParam);
#endif // !defined(_NO_ROLLUP_ORWND)

	return OwnerDrawDialogWindow::PreTranslateMsg(pMsg);		// nicht für uns
}

LRESULT ObjektInfo::ReplaceObjectInList (REPLACEOBJECT *pRO, bool fUndo)
{
	return HandleModifyIdent (pRO->lONr, 0L, pRO->lNewONr, fUndo);
}

LRESULT ObjektInfo::OnGetMinMaxInfo (MINMAXINFO *pmmi)
{
//	pmmi->ptMaxSize; 
//	pmmi->ptMinTrackSize;
//	pmmi->ptMaxTrackSize; 
#if !defined(_NO_ROLLUP_ORWND)
	if (m_fIsRolledUp) {
	Point ptSize (m_lInitialWidth, 2*GetSystemMetrics(SM_CYFRAME) + GetSystemMetrics(SM_CYSMCAPTION));

		pmmi->ptMinTrackSize = pmmi->ptMaxTrackSize = (POINT &)ptSize;
	}
#endif // !defined(_NO_ROLLUP_ORWND)
	return TRUE;
}
#endif

///////////////////////////////////////////////////////////////////////////////
// aktualisieren des FensterKopfes 
void ObjektInfo::UpdateCaption (void)
{
char cbNewCaption[80];

	GetCaption (cbNewCaption, 64);

char *pPtr2 = strrchr (cbNewCaption, '(');

	if (pPtr2 == NULL) {
		strcat (cbNewCaption , " (");
		pPtr2 = &cbNewCaption[strlen(cbNewCaption)-1];
	}

	wsprintf (pPtr2+1, "%ld/%ld)", (long)m_ulActCount, OITree().Count());
	SetCaption (cbNewCaption);
}

string ObjektInfoListe::CorrectCaption (ObjektInfo *pOIDlg, LPCSTR pcTemplate)
{
	TX_ASSERT(NULL != pcTemplate);

int iCnt = 1;
string strT (pcTemplate);
char cbBuffer[20];

	while (CaptionExists (pOIDlg, strT.c_str())) 
	{
		wsprintf (cbBuffer, " %d", iCnt);
		strT = string(pcTemplate) + cbBuffer;
		++iCnt;
	}
	return strT;
}

bool ObjektInfoListe::CaptionExists (ObjektInfo *pOIDlg, LPCSTR pcCaption)
{
CTable t (*this);
char cbBuffer[_MAX_PATH];

	for (t.First(); t.Valid(); t.Next()) {
	ObjektInfoLock l(t);
	
		TX_ASSERT(NULL != (ObjektInfo *)l);
		if (l == pOIDlg) continue;	// uns selbst übergehen

		l -> GetCaption (cbBuffer, _MAX_PATH-1);

	char *pPtr = strrchr (cbBuffer, '(');

		if (NULL == pPtr) continue;

		*(pPtr-1) = '\0';
		if (!strcmp (pcCaption, cbBuffer))
			return true;
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////////
// Einstellen des GesamtContainers der selektierten Objekte als Ausschnitt 
bool ObjektInfo::doZoomIn (void)
{
int maxIndex = GetCount();
ObjContainer OC, ocT;
bool fChanged = false;

	OC.SetXMin(MAXKOORD);	// nicht mit ctor initialisiert, da dieser min < max gewährleistet
	OC.SetXMax(0);
	OC.SetYMin(MAXKOORD);
	OC.SetYMax(0);
	for (int i = 0; i < maxIndex; i++) {
	long lONr = (long)m_pKurzInfo -> GetItem (i);	// Eintrag holen
	bool isSel = m_pKurzInfo -> GetSelection (i);
						
		if (!isSel) continue;	// nur selektierte Objekte behandeln
	
		if (m_rDBO.GetObjContainer (lONr, ocT)) {
//		if (DEX_GetObjContainer (lONr, ocT)) {
			OC += ocT;
			fChanged = true;
		}
	}
	
	if (fChanged) {
		ocT = m_rDBO.GetExtend();
//		DEX_GetActiveSightContainer (ocT);
		if (OC.HasSignificantSize()) {	// gültiger Container
			if (GetKeyState (VK_CONTROL) >= 0 && !DEX_IsHoldZoomActive())
				OC = OC.InflateCont (200);	// 100% größerer Ausschnitt
			else {
			Ausdehnung A = OC - ocT;

				OC = ocT.ShiftCont (A);
			}
		} else {			// PunktContainer
			if (GetKeyState (VK_CONTROL) >= 0 && !DEX_IsHoldZoomActive())
				ocT = ocT.InflateCont (-60);

		Ausdehnung A = OC - ocT;	// 40% des aktuelle Ausschnitts

			OC = ocT.ShiftCont (A);
		}
	
	// mit Projekt-Container abgleichen
	long lCont[4];
	KoOrd dXMin, dXMax, dYMin, dYMax;

		DEX_GetProjectCont (lCont);

		if (!m_rDBO.UnScaleCTF (lCont[0], lCont[2], &dXMin, &dYMin) ||
			!m_rDBO.UnScaleCTF (lCont[1], lCont[3], &dXMax, &dYMax))
		{
			return false;
		}

	ObjContainer dbOC (dXMin, dXMax, dYMin, dYMax);
	KoOrd dX, dY;

		OC &= dbOC;

		if (!m_rDBO.ScaleCTF (OC.XMin(), OC.YMin(), &dX, &dY))
			return false;
		lCont[0] = dX;
		lCont[2] = dY;

		if (!m_rDBO.ScaleCTF (OC.XMax(), OC.YMax(), &dX, &dY))
			return false;
		lCont[1] = dX;
		lCont[3] = dY;

		DEX_SetActiveSightContainer (lCont);
		DEX_RePaint();
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// Selektierte Objekte zu Legende hinzufügen
bool ObjektInfo::doAddToLegend (void)
{
int maxIndex = GetCount();

	for (int i = 0; i < maxIndex; i++) {
	long lONr = (long)m_pKurzInfo -> GetItem (i);	// Eintrag holen
	bool isSel = m_pKurzInfo -> GetSelection (i);
						
		if (!isSel) continue;	// nur selektierte Objekte behandeln
	
		DEX_AddObjectToLegend (lONr);
	}
	DEX_RefreshLegend();	
	DEX_RepaintLegend();
	return true;
}

#if !defined(_NO_ROLLUP_ORWND)
///////////////////////////////////////////////////////////////////////////////
// RoolUp Objekt-Recherchefenster
void ObjektInfo::CalculateButtonRect (Rectangle *prc)
{
Dimension sizeFrame(GetSystemMetrics(SM_CXFRAME), GetSystemMetrics(SM_CYFRAME));
Dimension sizeBorder(GetSystemMetrics(SM_CXBORDER),	GetSystemMetrics(SM_CYBORDER));
Rectangle rcWindow = WindowRect();

	prc->Top() = sizeFrame.Height() +2;
	prc->Bottom() = prc->Top() + GetSystemMetrics(SM_CYSMCAPTION) -5;

	prc->Right() = rcWindow.Width() - sizeFrame.Width() - GetSystemMetrics(SM_CYSMCAPTION) -1;
	prc->Left() = prc->Right() - abs(prc->Height()) -2;
}

bool ObjektInfo::IsMouseInRollUpButton (LPARAM lParam, bool fPointIsClient)
{
Rectangle rcWnd, rcClnt;

	GetWindowRect (m_hWnd, (RECT *)&rcWnd);
	ScreenToClient (m_hWnd, (POINT *)&rcWnd);
	ScreenToClient (m_hWnd, (POINT *)&rcWnd.Right());
	
	GetClientRect (m_hWnd, (RECT *)&rcClnt);

Rectangle rcBttn;
Point pt (GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));

	if (!fPointIsClient)
		ScreenToClient(m_hWnd, (POINT *)&pt);
	pt.Y() = abs(rcClnt.Top() - rcWnd.Top()) + pt.Y();

	CalculateButtonRect(&rcBttn);
	return PtInRect((RECT *)&rcBttn, (POINT &)pt);
}

void ObjektInfo::DrawButton()
{
HDC hDC = GetWindowDC(m_hWnd);
Rectangle rcBttn;

	CalculateButtonRect(&rcBttn);
	if (m_fIsRolledUp) {
		if (m_fPushedButton)
			DrawFrameControl(hDC, (RECT *)&rcBttn, DFC_CAPTION, DFCS_CAPTIONMAX | DFCS_PUSHED);
		else
			DrawFrameControl(hDC, (RECT *)&rcBttn, DFC_CAPTION, DFCS_CAPTIONMAX);
	} else {
		if (m_fPushedButton)
			DrawFrameControl(hDC, (RECT *)&rcBttn, DFC_CAPTION, DFCS_CAPTIONMIN | DFCS_PUSHED);
		else 
			DrawFrameControl(hDC, (RECT *)&rcBttn, DFC_CAPTION, DFCS_CAPTIONMIN);
	}

	ReleaseDC(m_hWnd, hDC);
}

LRESULT ObjektInfo::OnNcPaint (Event e)
{
	if (!(g_dwTRiASMode & TRIASMODE_RollUpORWnds))
		return FALSE;
		
	DefWindowProc(m_hWnd, e.Msg(), e.WParam(), e.LParam());

#if _TRiAS_VER < 0x0400
	if (0 == g_dwVer4)
		return TRUE;
#endif // _TRiAS_VER < 0x0400

	DrawButton();
	return TRUE;
}

LRESULT ObjektInfo::OnNcActivate(Event e)
{
	if (!(g_dwTRiASMode & TRIASMODE_RollUpORWnds))
		return FALSE;
		
	DefWindowProc(m_hWnd, e.Msg(), e.WParam(), e.LParam());

#if _TRiAS_VER < 0x0400
	if (0 == g_dwVer4)
		return TRUE;
#endif // _TRiAS_VER < 0x0400

	DrawButton();
	return TRUE;
}

LRESULT ObjektInfo::OnSetText(Event e)
{
	if (!(g_dwTRiASMode & TRIASMODE_RollUpORWnds))
		return FALSE;

	if (IsWindowUnicode(m_hWnd)) {
	// unter bestimmten Umständen wird unter NT der Typ des Fensters geändert
	// (BUG ?)
		USES_CONVERSION;
		DefWindowProc(m_hWnd, e.Msg(), e.WParam(), (LPARAM)OLE2A((wchar_t *)e.LParam()));
	}
	else	
		DefWindowProc(m_hWnd, e.Msg(), e.WParam(), e.LParam());

#if _TRiAS_VER < 0x0400
	if (0 == g_dwVer4)
		return TRUE;
#endif // _TRiAS_VER < 0x0400

	DrawButton();
	return TRUE;
}

LRESULT ObjektInfo::OnNcHitTest (Event e)
{
	if (!(g_dwTRiASMode & TRIASMODE_RollUpORWnds))
		return HTNOWHERE;
		
#if _TRiAS_VER < 0x0400
	if (0 == g_dwVer4)
		return HTNOWHERE;
#endif // _TRiAS_VER < 0x0400

	if (IsMouseInRollUpButton (e.LParam())) 
		return m_fIsRolledUp ? HTMAXBUTTON : HTMINBUTTON;

	return DefWindowProc(m_hWnd, e.Msg(), e.WParam(), e.LParam());	// HTNOWHERE;
}

LRESULT ObjektInfo::OnNcLButtonDown (Event e)
{
	if (!(g_dwTRiASMode & TRIASMODE_RollUpORWnds))
		return FALSE;
		
#if _TRiAS_VER < 0x0400
	if (0 == g_dwVer4) 
		return FALSE;
#endif // _TRiAS_VER < 0x0400

	if (IsMouseInRollUpButton (e.LParam())) {
		if (m_hWnd != GetActiveWindow())
			SetActiveWindow(m_hWnd);
		SetCapture(m_hWnd);
		m_fPushedButton = true;
		m_fMouseCaptured = true;
		DrawButton();
		return TRUE;
	} 
	return FALSE;
}

void ObjektInfo::MouseButtonUp (MouseEvt e)
{
	if (!(g_dwTRiASMode & TRIASMODE_RollUpORWnds))
		return;
		
#if _TRiAS_VER < 0x0400
	if (0 == g_dwVer4)
		return;
#endif // _TRiAS_VER < 0x0400

	if (m_fMouseCaptured) {
		ReleaseCapture();
		m_fMouseCaptured = false;
		m_fPushedButton = false;
		DrawButton();

		if (IsMouseInRollUpButton (e.LParam(), true)) 
			PostEvent(WM_COMMAND, IDM_TOGGLEROLLUP);
	}
}

LRESULT ObjektInfo::OnMouseMove (UINT wMsg, WPARAM wParam, LPARAM lParam)
{
	if (!(g_dwTRiASMode & TRIASMODE_RollUpORWnds))
		return FALSE;
		
#if _TRiAS_VER < 0x0400
	if (0 == g_dwVer4)
		return FALSE;
#endif // _TRiAS_VER < 0x0400

	if (m_fMouseCaptured) {
		if (IsMouseInRollUpButton (lParam, true)) {
			if (!m_fPushedButton) {
				m_fPushedButton = true;
				DrawButton();
			}
		} 
		else if (m_fPushedButton) {
			m_fPushedButton = false;
			DrawButton();
		}
	}
	return FALSE;
}

void ObjektInfo::GetCorrectedRestoreRect (Rectangle *prc)
{
Rectangle rcWnd;
Rectangle rcScreen;

	GetWindowRect (m_hWnd, (RECT *)prc);
	SystemParametersInfo (SPI_GETWORKAREA, 0, (RECT *)&rcScreen, 0);

	if (prc -> Left() + m_dimBeforeRollUp.Width() > rcScreen.Right())
		prc -> Left() = rcScreen.Right() - m_dimBeforeRollUp.Width();

	if (prc -> Top() + m_dimBeforeRollUp.Height() > rcScreen.Bottom())
		prc -> Top() = rcScreen.Bottom() - m_dimBeforeRollUp.Height();
}

bool ObjektInfo::doToggleRollUp()
{
	_ASSERTE(g_dwTRiASMode & TRIASMODE_RollUpORWnds);

	if (m_fIsRolledUp) {
		_ASSERTE(NULL != m_hMenu);
		_ASSERTE(0 != m_dimBeforeRollUp.Width() && 0 != m_dimBeforeRollUp.Height());

		SetMenu (m_hWnd, m_hMenu);
		m_hMenu = NULL;

		m_fIsRolledUp = false;
		if (m_pKurzInfo) {
			m_pKurzInfo -> Show();
			m_pKurzInfo ->SetFocus();
		}

	Rectangle rcWnd;

		GetCorrectedRestoreRect (&rcWnd);
		SetWindowPos (m_hWnd, NULL, rcWnd.Left(), rcWnd.Top(), m_dimBeforeRollUp.Width(), 
			m_dimBeforeRollUp.Height(), SWP_NOZORDER|SWP_NOACTIVATE);
		m_fIsRolledUp = false;
	} 
	else {
	Rectangle rcWnd;

		GetWindowRect (m_hWnd, (RECT *)&rcWnd);

		m_dimBeforeRollUp = Dimension(rcWnd.Width(), abs(rcWnd.Height()));
		m_hMenu = ::GetMenu(m_hWnd);

	long iNewHeight = 2*GetSystemMetrics(SM_CYFRAME) + GetSystemMetrics(SM_CYSMCAPTION);

		m_fIsRolledUp = true;
		SetMenu (m_hWnd, NULL);
		if (m_pKurzInfo)
			m_pKurzInfo -> Hide();
		SetWindowPos (m_hWnd, NULL, 0, 0, m_lInitialWidth, iNewHeight, 
			SWP_NOMOVE|SWP_NOZORDER|SWP_NOACTIVATE);

		if (m_fHighLighted) {
		// blinken - aus, nur wenns nicht zu lange dauert
			if (!m_fNoBlinking && !m_fCmd)	
				DeActivateObj (true, false);
		} 
		m_fIsRolledUp = true;
	}
	DrawButton();
	UpdateActivation();
	return true;
}

#endif // !defined(_NO_ROLLUP_ORWND)

