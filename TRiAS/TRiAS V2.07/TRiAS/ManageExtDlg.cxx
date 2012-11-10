// Klassendefinition für das Erweiterung-Lade/Entlade Dialogfenster -----------
// File: MANAGEEXTDLG.CXX

#include "triaspre.hxx"

#define NOMINMAX
#pragma warning (disable: 4304)
#pragma warning (disable: 4114)
#pragma warning (disable: 4786)		// debug info truncated
#include <ospace/std/list>
#include <ospace/std/string>

#include "triasres.h"

#include <xtsnguid.h>
#include <dirisole.h>
#include <registry.hxx>
#include <TrCatIDs.h>
#include <TRiASHelper.h>

#include "extmain3.hxx"
#include "strings.h"
#include "cextreg.hxx"
#include "ManageExtDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern bool g_fSystemAdm;

///////////////////////////////////////////////////////////////////////////////
// SmartInterfaces
DefineSmartInterface(CatInformation);
DefineSmartInterface(RegisterTRiASExtension);

///////////////////////////////////////////////////////////////////////////////
// AnpassenDialog anzeigen
//
// Dieser Dialog lädt zusätzliche Pages über den Key:
//	HKCR\TRiAS.Application.2\TRiASEx\PropertySheetHandlers\Customize
//
bool ExtDirisWindow::doLoadExtension (void) 
{
// Dialogfenster generieren
CEierUhr Wait (this);
CManageExtDlg CustDlg (this); 

// eigene Page hinzufügen
bool fForceBttns = (GetKeyState(VK_CONTROL) < 0) ? true : false;
CManageExtPage CustExtPage (this, fForceBttns);

	CustDlg.AddPage (&CustExtPage);	// eigene Page ist die erste

string strSubKey(g_cbDocSubKey);

	strSubKey += g_cbDel;
	strSubKey += g_cbCustomize;
	LoadPages (CustDlg, g_cbAppKey, strSubKey.c_str());			// zusätzliche Pages aus Registry laden

/// folgendes ist vorläufig (bis 'Optionen' Dialog fertig ist)
	strSubKey = g_cbDocSubKey;
	strSubKey += g_cbDel;
	strSubKey += g_cbOptions;
	LoadPages (CustDlg, g_cbAppKey, strSubKey.c_str());			// zusätzliche Pages aus Registry laden
///

// Dialogfenster anzeigen
	Wait.Hide();
	CustDlg.Show (Centre);			// Header editieren
	
	CoFreeUnusedLibraries();		// DLL's wieder freigeben

return CustDlg.Result();
}

///////////////////////////////////////////////////////////////////////////////
// Konstruktor/Destruktor -----------------------------------------------------
CManageExtDlg::CManageExtDlg (pWindow pWnd)
	: CPropertySheetExt (ResString (IDS_CUSTOMIZE, 64), pWnd)
{
}

CManageExtDlg::~CManageExtDlg (void)
{
}

///////////////////////////////////////////////////////////////////////////////
#pragma warning (disable: 4355)
CManageExtPage::CManageExtPage (ExtDirisWindow *pWnd, bool fForceBttns)
	: CPropertyPage (IDD_MANAGEEXT, ResString (IDS_CUSTEXTSCAP, 32)),
	  m_pbInstall (this, IDB_INSTALL), m_pbRemove (this, IDB_REMOVE),
	  m_pWnd(pWnd), m_rEL(pWnd->EL())
{
// Variablen initialisieren
	m_pExtName = NULL;
	m_pDLLName = NULL;
	m_pBuffer = NULL;

	m_pExtList = NULL;

	m_rgFlags = (EXTENSIONFLAG)0;

	m_fToLoad = false;
	m_fToUnload = false;

	m_hIterItem = NULL;
	m_hNormal = NULL;
	m_hProject = NULL;
	m_hSystem = NULL;

	m_fNoProject = false;
	m_fNoSystem = false;
	m_fModified = false;

	if (fForceBttns || g_fSystemAdm) {
		try {
		WCatInformation CatInfo (CLSID_StdComponentCategoriesMgr);
		GUID guidImpl[1]; 

			guidImpl[0] = CATID_TRiASSelfRegister;
			THROW_FAILED_HRESULT(CatInfo -> EnumClassesOfCategories (1, guidImpl, 0, NULL, m_EnumGuids.ppi()));

		GUID guid;

			if (S_OK == m_EnumGuids -> Next (1, &guid, NULL))
				m_fBttnsEnabled = true;		// wenigstens ein Objekt existiert

		} catch (_com_error &) {
			m_fBttnsEnabled = false;
		}
	
	} else {
	// im NormalMode sowieso kein UI
		m_fBttnsEnabled = false;
		m_fNoSystem = true;
	}
}

#pragma warning (default: 4355)

// Controls initialisieren
void CManageExtPage::WindowInit (Event e)
{
// Controls initialisieren
	m_pbInstall.FInit();
	m_pbRemove.FInit();

// inhaltliche Initialisierungen
	if (!m_fBttnsEnabled) {
		m_pbInstall.Hide();
		m_pbRemove.Hide();
	}

// internen Buffer anlegen
	ATLTRY(m_pBuffer = new char [_MAX_PATH]);
	if (m_pBuffer == NULL) return;

// alle Erweiterungen in Liste aufnehemen
	if (!InitExtList()) return;

	m_pExtList -> SelectItem (m_hNormal);
	m_pExtList -> SetFocus();
	m_pbRemove.Disable();

	SetModified (false);		// für alle Fälle
}

CManageExtPage::~CManageExtPage (void)
{
CImageList *pIList = m_pExtList->SetImageList (NULL, TVSIL_NORMAL);

	DELETE(pIList);

	DELETE (m_pExtName);
	DELETE (m_pDLLName);
	DELETE (m_pBuffer);
	DELETE (m_pExtList);
}

bool CManageExtPage::InitExtList (bool fDelete)
{
// evtl. Liste löschen
string strItem;
string strNextItem;

	if (fDelete && NULL != m_pExtList) {
		if (IsModified())	// evtl. Änderungen wirksam werden lassen
			PressSheetButton (PSBTN_APPLYNOW);
		
	// Texte des aktuellen und jeweils nächstliegenden Items speichern
	HTREEITEM hItem = m_pExtList -> GetSelectedItem();

		if (NULL != hItem) {
			strItem = m_pExtList -> GetItemText (hItem);

		// das nächstliegende Item herausfinden
		HTREEITEM hNextItem = m_pExtList -> GetNextItem (hItem, TVGN_PREVIOUS);

			if (NULL == hNextItem)
				hNextItem = m_pExtList -> GetNextItem (hItem, TVGN_NEXT);
			if (NULL == hNextItem)
				hNextItem = m_pExtList -> GetNextItem (hItem, TVGN_PARENT);
							
			if (NULL != hNextItem)
				strNextItem = m_pExtList -> GetItemText (hNextItem);
		}
		m_pExtList -> DeleteAllItems();
	}

// Liste generieren 
	if (NULL == m_pExtList) {
		ATLTRY(m_pExtList = new CCheckTreeView (this, IDL_LOADLISTDLL));
		if (m_pExtList == NULL) return false;

		if (!m_pExtList -> FInit())
			return false;

	// ImageList generieren
//		if (!m_ilHdr.CreateList (IDB_HEADERSTRIP, 16, 0, RGB(255, 0, 255))) {
//			TX_TRACE("Couldnt create imagelist for CManageExtPage");
//			return false;
//		}

	CImageList *pIList = m_pExtList->SetImageList ((CImageList *)&m_rEL.GetImageList(), TVSIL_NORMAL);

		DELETE(pIList);
	}

// Liste wieder aufbauen
CTable r(m_rEL);
int iCnt = 0;

// 1. reguläre Erweiterungen
ResString resNormal (IDS_NORMALEXTENSIONS, 128);

	m_hNormal = m_pExtList -> InsertItem (resNormal, IMG_FOLDER, IMG_FOLDER);
	if (NULL == m_hNormal) return false;	// reguläre Erweiterungen müssen da sein

	m_pExtList -> HideStateImage (m_hNormal);

	for (r.First(); r.Valid(); r.Next()) {
	ExtensionLock l(r);
	COleExtension *pExt = (COleExtension *)(Extension *)l;

		if (l && pExt -> isGlobal() && pExt -> isVisible()) {
		UINT uiBmp = pExt -> GetBmp();
		HTREEITEM hItem = m_pExtList -> InsertItem (pExt -> ExtName().c_str(), uiBmp, uiBmp, m_hNormal);

			if (NULL != hItem) {
				if (pExt -> isLoaded()) 
					m_pExtList -> SetCheckState (hItem, pExt -> isUnLoadable() ? TV_CHECK_ON : TV_CHECK_PASSIVE);
				else
					m_pExtList -> SetCheckState (hItem, TV_CHECK_OFF);
				
				iCnt++;
			}
		}
	}
	TX_ASSERT(0 != iCnt);

// 2. projektbezogene Erweiterungen
ResString resPrj (IDS_PROJECTEXTENSIONS, 128);

	m_hProject = m_pExtList -> InsertItem (resPrj, IMG_FOLDER, IMG_FOLDER);
	if (NULL == m_hProject) return false;	// reguläre Erweiterungen müssen da sein

	m_pExtList -> HideStateImage (m_hProject);
	iCnt = 0;

	for (r.First(); r.Valid(); r.Next()) {
	ExtensionLock l(r);
	COleExtension *pExt = (COleExtension *)(Extension *)l;

		if (pExt && !pExt -> isGlobal() && pExt -> isVisible()) {
		UINT uiBmp = pExt -> GetBmp();
		HTREEITEM hItem = m_pExtList -> InsertItem (pExt -> ExtName().c_str(), uiBmp, uiBmp, m_hProject);

			if (NULL != hItem) {
				if (pExt -> isLoaded()) 
					m_pExtList -> SetCheckState (hItem, pExt -> isUnLoadable() ? TV_CHECK_ON : TV_CHECK_PASSIVE);
				else
					m_pExtList -> SetCheckState (hItem, TV_CHECK_OFF);
				
				iCnt++;
			}
		}
	}
	if (0 == iCnt) {
	ResString resNoPrj (IDS_NOPROJECTEXTENSIONS, 64);
	HTREEITEM hItem = m_pExtList -> InsertItem (resNoPrj, 0, 0, m_hProject);

		m_pExtList -> HideStateImage (hItem);
		m_fNoProject = true;
	}

// evtl. systeminterne Erweiterungen
	if (g_fSystemAdm || m_fBttnsEnabled) {
	ResString resSys (IDS_SYSTEMEXTENSIONS, 128);

		m_hSystem = m_pExtList -> InsertItem (resSys, IMG_FOLDER, IMG_FOLDER);
		if (NULL == m_hSystem) return false;	// reguläre Erweiterungen müssen da sein

		m_pExtList -> HideStateImage (m_hSystem);
		iCnt = 0;

		for (r.First(); r.Valid(); r.Next()) {
		ExtensionLock l(r);
		COleExtension *pExt = (COleExtension *)(Extension *)l;

			if (pExt && !pExt -> isVisible()) {
			UINT uiBmp = pExt -> GetBmp();
			HTREEITEM hItem = m_pExtList -> InsertItem (pExt -> ExtName().c_str(), uiBmp, uiBmp, m_hSystem);

				if (NULL != hItem) {
					if (pExt -> isLoaded()) 
						m_pExtList -> SetCheckState (hItem, pExt -> isUnLoadable() ? TV_CHECK_ON : TV_CHECK_PASSIVE);
					else
						m_pExtList -> SetCheckState (hItem, TV_CHECK_OFF);
					
					iCnt++;
				}
			}
		}
		if (0 == iCnt) {
		ResString resNoSys (IDS_NOSYSTEMEXTENSIONS, 64);
		HTREEITEM hItem = m_pExtList -> InsertItem (resNoSys, 0, 0, m_hSystem);

			m_pExtList -> HideStateImage (hItem);
			m_fNoSystem = true;
		}
	}

HTREEITEM hItem = NULL;

	if (strItem.length() > 0) 
		hItem = m_pExtList -> FindString (strItem.c_str());		// wiederfinden
	if (NULL == hItem && strNextItem.length() > 0)
		hItem = m_pExtList -> FindString (strNextItem.c_str());		// wiederfinden

	if (NULL == hItem) 
		hItem = m_hNormal;

	TX_ASSERT(NULL != hItem);
	m_pExtList -> Expand (m_hNormal, TVE_EXPAND);

	if (hItem == m_hProject || hItem == m_hSystem)
		m_pExtList -> Expand (hItem, TVE_EXPAND);
	m_pExtList -> SelectItem (hItem);
	m_pExtList -> EnsureVisible (hItem);
	m_pExtList -> SetFocus();
	return true;
}

void CManageExtPage::ButtonClick (ControlEvt e)
{
	switch ((UINT)e.GetControlID()) {
	case IDB_INSTALL:
		{
		HTREEITEM hItem = InstallExtension();

			m_pExtList -> SelectItem (hItem);
			m_pExtList -> SetFocus();

			if (NULL != hItem) {
				m_pExtList -> EnsureVisible (hItem);
				if (TV_CHECK_PASSIVE != m_pExtList -> GetCheckState (hItem))
					m_pbRemove.Enable();
				else 
					m_pbRemove.Disable();
				
				SetModified (true);			// muß gespeichert werden
			} else
				m_pbRemove.Disable();
		}
		break;

	case IDB_REMOVE:
		if (RemoveExtension()) {
			SetModified (true);			// muß gespeichert werden
			m_pbRemove.Disable();
		}
		break;

	default:
		break;
	}
}

void CManageExtPage::OnSelChanged (NotifyEvt)
{
HTREEITEM hItem = m_pExtList -> GetSelectedItem();

	if (NULL == hItem || m_pExtList->ItemHasChildren (hItem)) {
		m_pbRemove.Disable();
		return;		// nur Childs behandeln
	}

	if (TV_CHECK_PASSIVE != m_pExtList -> GetCheckState(hItem))
		m_pbRemove.Enable();
	else
		m_pbRemove.Disable();
}

long CManageExtPage::Dispatch (Event e)
{
	if (WM_NOTIFY == e.Msg()) {
		if (OnNotify ((NotifyEvt &)e))
			return true;
	}
	return CPropertyPage::Dispatch(e);
}

bool CManageExtPage::OnNotify (NotifyEvt e)
{
NMHDR *pNMHDR = e.GetNotifyInfo();

	switch (pNMHDR -> code) {
	case TVN_CHECKSTATECHANGED:
		SetModified (true);
		return true;

	case TVN_CHANGINGCHECKSTATE:
		return OnChangingCheckState ((NM_TREEVIEWCHECK *)pNMHDR);
	}
	return false;
}

bool CManageExtPage::OnChangingCheckState (NM_TREEVIEWCHECK *pHdr)
{
	TX_ASSERT(NULL != pHdr -> hItem);

UINT uiState = m_pExtList->GetCheckState (pHdr -> hItem);

	if (TV_CHECK_PASSIVE == uiState) {
		pHdr -> state = TV_CHECK_NOCHANGE;
		return true;
	}

	if (TV_CHECK_OFF == uiState && GetNames (pHdr -> hItem) && !isUnLoadable())
		pHdr -> state = TV_CHECK_PASSIVE;

	return true;
}

void CManageExtPage::OnItemExpanded (NotifyEvt e)
{
NM_TREEVIEW *pnmtv = (NM_TREEVIEW *)e.GetNotifyInfo();
HTREEITEM hItem = pnmtv -> itemNew.hItem;

	AdjustImage (hItem);
}

void CManageExtPage::AdjustImage (HTREEITEM hItem)
{
	if (!m_pExtList->ItemHasChildren (hItem)) 
		return;		// nur Parents behandeln

	if (m_pExtList->GetItemState (hItem, TVIS_EXPANDED) & TVIS_EXPANDED) 
		m_pExtList->SetItemImage (hItem, IMG_OPENFOLDER, IMG_OPENFOLDER);	// ist expandiert
	else
		m_pExtList->SetItemImage (hItem, IMG_FOLDER, IMG_FOLDER);	// ist collabiert
}

///////////////////////////////////////////////////////////////////////////////
// OK oder Apply 
bool CManageExtPage::OnOK (NotifyEvt e)
{
CEierUhr Wait (this);		// kann etwas dauern

// alles, was zu entladen ist, entladen
	if (GetFirstExtName()) {
		do {
			if (toUnload()) {
				m_pWnd -> ReUnLoadExtension (GetExtName(), GetDLLName());
			}
		} while (GetNextExtName());
	}

// alles, was zu laden ist, laden
	if (GetFirstExtName()) {
		do {
			if (toLoad()) {
			string strRegKey = m_rEL.GetRegKey (GetDLLName());

				m_pWnd -> LoadExtension (GetExtName(), GetDLLName(), 
							LEFullLoad, GetFlags(), strRegKey.c_str());
			}
		} while (GetNextExtName());
	}

	SetModified (false);	// wieder passivieren
	return false;	// always allow operation
}

// ZugriffsFunktionen ---------------------------------------------------------
bool CManageExtPage::GetFirstExtName (void)
{
	m_hIterItem = m_pExtList -> GetChildItem (m_hNormal);
	if (NULL == m_hIterItem) return false;

	m_rgMode = ITERMODE_Normal;
	return GetNames(m_hIterItem);
}

bool CManageExtPage::GetNextExtName (void)
{
HTREEITEM hItem = m_pExtList -> GetNextItem (m_hIterItem, TVGN_NEXT);

	if (NULL == hItem) {
		switch (m_rgMode) {
		case ITERMODE_Normal:
			m_rgMode = ITERMODE_Project;
			hItem = m_hProject;
			if (NULL == hItem) {
				m_rgMode = ITERMODE_System;
				hItem = m_hSystem;
			}
			break;

		case ITERMODE_Project:
			m_rgMode = ITERMODE_System;
			hItem = m_hSystem;
			break;

		case ITERMODE_System:
			break;
		}
		if (NULL == hItem) return false;

		hItem = m_pExtList -> GetChildItem (hItem);
		if (NULL == hItem) return false;

	}
	m_hIterItem = hItem;
	return GetNames(m_hIterItem);
}

bool CManageExtPage::GetNames (HTREEITEM hItem)
{
// Bezeichner der DLL holen
	DELETE (m_pExtName);
	DELETE (m_pDLLName);

string strItem (m_pExtList -> GetItemText(hItem));

	m_pExtName = StrDup (strItem.c_str(), RC_LoadListSel);	// Bezeichner holen
	m_pDLLName = m_rEL.RetrieveDLLName (m_pExtName);	// Namen der DLL holen
	if (NULL == m_pDLLName)
		return false;		// Erweiterung nicht wiedergefunden

	m_rgFlags = m_rEL.GetFlags(m_pDLLName);

HDEX hDexDummy;
bool fLoaded = m_rEL.isLoaded (m_pDLLName, hDexDummy) ? true : false;
bool fChecked = (TV_CHECK_OFF != m_pExtList -> GetCheckState (hItem)) ? true : false;

	m_fToLoad = !fLoaded && fChecked;
	m_fToUnload = fLoaded && !fChecked;
			
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// Eine neue Erweiterung entfernen
bool CManageExtPage::RemoveExtension (void)
{
	TX_ASSERT(m_fBttnsEnabled);

HTREEITEM hItem = m_pExtList -> GetSelectedItem();
string strItem (m_pExtList -> GetItemText (hItem));

LPSTR pDLL = m_rEL.RetrieveDLLName (strItem.c_str());

	TX_ASSERT(NULL != pDLL);
	if (NULL == pDLL) return false;

EXTENSIONFLAG rgFlags = m_rEL.GetFlags (pDLL);

	if (!(rgFlags & EF_Visible) || !(rgFlags & EF_UnLoadable)) {
	// eine nicht sichtbare Erweiterung soll gelöscht werden
	StdMessBoxReply rgRep = VMessageBox (this, IDS_DELETEEXTCAP, YesNoButtons|QuestionMarkIcon, IDS_DELETEEXT);

		if (NoReply == rgRep) {
			DELETE(pDLL);
			return false;
		}
	}

LOADEXTENSIONEX LE;

	LE.m_pDesc = pDLL;
	LE.m_pName = strItem.c_str();
	LE.m_iMode = LEFullLoad;	// vollständig entladen
	LE.m_fGlobal = true;

bool iResult = DEX_ExternalUnLoadExtensionEx (LE);

	if (iResult) {
	// das zugehörige RegistrierObjekt laden und verwenden
	WRegisterTRiASExtension RegExt;
	bool fGlobal = (rgFlags & EF_Global) ? true : false;
	HRESULT hr = UnGetRegObject (pDLL, false, fGlobal, RegExt.ppi());

		if (SUCCEEDED(hr)) {
		CComBSTR bstrName (strItem.c_str());
		CComBSTR bstrID (pDLL);

		//  evtl. projektbezogen entfernen
			if (!(rgFlags & EF_Global)) {
			HPROJECT hPr = m_pWnd->DBO().DB().DBDesc();

				RegExt -> UnRegisterTRiASExtension (bstrName, bstrID, (long)hPr);
			}

		// global immer entfernen, evtl. Fehler ignorieren
			RegExt -> UnRegisterTRiASExtension (bstrName, bstrID, NULL);

			InitExtList (true);
		} else
			iResult = false;		// snh
	}
	DELETE (pDLL);
	return iResult;
}

///////////////////////////////////////////////////////////////////////////////
// Eine neue Erweiterung hinzufügen
HTREEITEM CantLoadAndReturnNull (pWindow pW, LPCSTR pcExt, HRESULT hr)
{
	VMessageBox (pW, 
		FakeTRiASName (IDS_LOADEXTCAPTION, g_cbTRiAS).c_str(), 
		OkayButton|HandIcon, IDS_LOADEXTERROR, pcExt, hr);
	return NULL;	// Rückkehrwert wird weiterverwendet
}

HTREEITEM CManageExtPage::InstallExtension (void)
{
	TX_ASSERT(m_fBttnsEnabled);

string strTempl;

	if (S_OK != RetrieveTemplate (strTempl))
		return NULL;		// Fehler beim Generieren des DialogTemplates

COpenDialog OpenDlg (this, (char *)strTempl.c_str());

	OpenDlg.SetCaption (FakeTRiASName (IDS_LOADEXTCAPTION, g_cbTRiAS).c_str());
	OpenDlg.AddFlags (OFN_HIDEREADONLY|OFN_NOCHANGEDIR);
#if defined(WIN32)
	if (IsWin40()) 
	{
		OpenDlg.AddFlags (OFN_EXPLORER|OFN_LONGNAMES);
	} else
#endif
	{
	// SonderWünsche einstellen
		if (IsWinNT()) OpenDlg.AddFlags (OFN_LONGNAMES);
	}

// Verzeichnis auf EXE-Verzeichnis voreinstellen
string strTmp;

	GetModuleFileName (GetModuleHandle(NULL), m_pBuffer, _MAX_PATH);
	strTmp = m_pBuffer;
	
int iBackslash = strTmp.rfind(g_cbDel);	// abschließendes BackSlash wegnehmen

	if (iBackslash != NPOS)
		strTmp = strTmp.remove (iBackslash);

	OpenDlg.SetInitialDir (strTmp.c_str());		// auf EXE setzen
	OpenDlg.Show();
	if (!OpenDlg.Result()) return NULL;

	OpenDlg.GetFileName (m_pBuffer, _MAX_PATH);

// feststellen unter welchem Item die neue Erweiterung hängen soll
HTREEITEM hItem = m_pExtList -> GetSelectedItem();
EXTENSIONFLAGS rgFlags = EXTENSIONFLAGS_NoFlags;

	if (NULL != hItem) {
	HTREEITEM hParent = m_pExtList -> GetNextItem (hItem, TVGN_PARENT);

		if (NULL == hParent)
			hParent = hItem;	// Selektion ist bereits auf Parent

		if (m_hNormal == hParent) 
			rgFlags = (EXTENSIONFLAGS)(EXTENSIONFLAGS_Global + 
									   EXTENSIONFLAGS_Visible + 
									   EXTENSIONFLAGS_UnLoadable);	
		else if (m_hProject == hParent)
			rgFlags = (EXTENSIONFLAGS)(EXTENSIONFLAGS_Visible + EXTENSIONFLAGS_UnLoadable);	
		else if (m_hSystem == hParent)
			rgFlags = (EXTENSIONFLAGS)(EXTENSIONFLAGS_Global + EXTENSIONFLAGS_UnLoadable);
		
		TX_ASSERT(rgFlags != EXTENSIONFLAGS_NoFlags);	// es muß einer der SubTrees sein
	}

// das zugehörige RegistrierObjekt laden und verwenden
WRegisterTRiASExtension RegExt;
HRESULT hr = GetRegObject (OpenDlg.GetFilterIndex(), m_EnumGuids, RegExt.ppi());

	if (FAILED(hr)) return CantLoadAndReturnNull (this, m_pBuffer, hr);

CComBSTR bstrID, bstrName;
CComBSTR bstrTarget (m_pBuffer);

// RegisterTRiASExtension liefert die notwendigen Informationen, um die neue Erweiterung
// zu instantiieren:
// a) Global	bstrName ist LongName
//				bstrID	 ist String für Registry ...\Extensions\(String)\...
// b) Projekt	bstrName ist LongName
//				bstrID	 ist ProgID über den die Erweiterung erzeugt wird (evtl. Wrapper)
//
	hr = RegExt -> RegisterTRiASExtension (bstrTarget, &bstrName, &bstrID, &rgFlags);
	if (SUCCEEDED(hr)) {
		USES_CONVERSION;

	// Bezeichner der Erweiterung unbekannt, also abfragen
	string strProgID (OLE2A(bstrID));
	string strName (OLE2A(bstrName));

		if (0 == strName.length()) {	
		// Bezeichner der Erweiterung abfragen
		CQueryExtensionNameDlg QueryDlg (this, strProgID);

			QueryDlg.Show();
			if (0 == QueryDlg.Result() || !QueryDlg.GetExtName (strName))
				return NULL;
			bstrName = CComBSTR (strName.c_str());	// zurückkopieren
		}

	// jetzt neue Erweiterung TRiAS bekanntmachen
	HTREEITEM hItem = m_pExtList -> FindString (strName.c_str());

		if (NULL != hItem) return hItem;		// bereits installiert

	// jetzt evtl. noch als projektbezogene Erweiterung registrieren
	string strRegKey;

		if (!(rgFlags & EXTENSIONFLAGS_Global)) {
		HPROJECT hPr = m_pWnd->DBO().DB().DBDesc();

			hr = RegExt -> RegisterProjectExtension ((long)hPr, bstrName, bstrID, bstrTarget);
			if (FAILED(hr)) return CantLoadAndReturnNull(this, strName.c_str(), hr);
	
			strRegKey = strName;
		} else 
		// RegistryKey zusammenbauen
			strRegKey = string(g_cbRegExtensions) + g_cbDel + OLE2A(bstrID);

	// Erweiterung installieren (nur registrieren)
		m_pWnd -> LoadExtension (strName.c_str(), strProgID.c_str(), 
			LENoLoad, (EXTENSIONFLAG)rgFlags, strRegKey.c_str());

		InitExtList (true);
		return m_pExtList -> FindString (strName.c_str());
	}
	return CantLoadAndReturnNull(this, m_pBuffer, hr);
}

///////////////////////////////////////////////////////////////////////////////
// Generieren des DialogTemplates
HRESULT CManageExtPage::RetrieveTemplate (string &rStrTempl)
{
	USES_CONVERSION;

GUID guid;
bool fFound = false;
char cbBuffer[_MAX_PATH];

	rStrTempl = g_cbNil;
	for (m_EnumGuids -> Reset(); S_OK == m_EnumGuids -> Next (1, &guid, NULL); /**/)
	{
	string str (g_cbClsId);
	LPOLESTR lpOleStrID;
	HRESULT hr = StringFromCLSID ((REFCLSID)guid, &lpOleStrID);

		if (FAILED(hr)) continue;

		str += string(g_cbDel) + OLE2A(lpOleStrID) + g_cbDel + g_cbHandledExtensions;
		CoTaskMemFree (lpOleStrID);

	CClassesRoot regFilter(str.c_str());
	DWORD dwLen = sizeof(cbBuffer);

		if (!regFilter.isValid() || !regFilter.GetSubSZ (g_cbFilter, cbBuffer, dwLen))
			continue;
		
		if (fFound)
			rStrTempl += TEXT("|");		// TrennZeichen zwischen FilterStrings
		rStrTempl += cbBuffer;
		fFound = true;
	}
	return fFound ? S_OK : S_FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// Generieren des RegistrierObjektes
HRESULT GetRegObject (int iIndex, IEnumGUID *pIEnum, IRegisterTRiASExtension **ppIRegExt)
{
	TEST_E_POINTER("CManageExtPage::GetRegObject", ppIRegExt);

	try {
	GUID guid;

		THROW_FAILED_HRESULT(pIEnum -> Reset());
		if (iIndex > 1) {
			THROW_FAILED_HRESULT(pIEnum -> Skip (iIndex-1));
		}
		THROW_FAILED_HRESULT(pIEnum -> Next (1, &guid, NULL));

	WRegisterTRiASExtension RegExt ((REFCLSID)guid);

		*ppIRegExt = RegExt.detach();

	} catch (_com_error &e) {
		return _COM_ERROR(e);
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Generieren des UnRegistrierObjektes
HRESULT UnGetRegObject (
	LPCSTR pcProgID, bool fFailIfNotThere, bool fGlobal, 
	IRegisterTRiASExtension **ppIRegExt)
{
	TEST_E_POINTER("CManageExtPage::UnGetRegObject", ppIRegExt);

HKEY hKey = NULL;
string strExtReg;

	if (fGlobal) {
	// reguläre Erweiterungen
		hKey = HKEY_CURRENT_USER;
		strExtReg = string(g_cbRegExtensions) + g_cbDel + pcProgID;
	} else {
	// projektbezogene Erweiterungen
		hKey = HKEY_CLASSES_ROOT;
		strExtReg = pcProgID;
	}

CRegistry regExt (hKey, strExtReg.c_str());
char cbBuffer[_MAX_PATH];
LONG lLen = sizeof(cbBuffer);

	if (!regExt.isValid()) 
		return E_UNEXPECTED;		// snh

	try {
	CLSID clsID = CLSID_RegisterExt;	// standardmäßig normale Erweiterung

		if (regExt.GetSZ (g_cbUnRegister, cbBuffer, lLen)) {
			USES_CONVERSION;
			THROW_FAILED_HRESULT(CLSIDFromString (A2OLE(cbBuffer), &clsID));

		} else if (fFailIfNotThere)
			return E_FAIL;

	WRegisterTRiASExtension RegExt (clsID);

		*ppIRegExt = RegExt.detach();

	} catch (_com_error &e) {
		return _COM_ERROR(e);
	}

	return S_OK;
}

/*
// Finden des Kurzbezeichners einer Erweiterung über den gegebene Dateinamen
bool FindExtNameFromDLLName (
	pWindow pW, string &strDLLName, string &strExtName, string &rStrProgID,
	const char *pShortName)
{
	strExtName = g_cbNil;

#if defined(ENABLE_WIN32S_CODE)
	if (IsWin32s()) return false;
#endif // ENABLE_WIN32S_CODE

HKEY hKey = NULL;
DWORD i = 0;
bool fFound = false;
char cbTriasKey[_MAX_PATH];
DWORD retCode = RegOpenKey (HKEY_CURRENT_USER, g_cbRegExtensions, &hKey);

	if (retCode != ERROR_SUCCESS) return false;
	while (RegEnumKey (hKey, i++, cbTriasKey, _MAX_PATH) == ERROR_SUCCESS) {
	string strTriasKey = cbTriasKey;

		if (CompareDLLName (strTriasKey, strDLLName, rStrProgID)) {
			strExtName = strTriasKey;
			fFound = true;
			break;
		}
	}

	RegCloseKey (hKey);   // Close the key handle.

	if (!fFound) {	
	// Bezeichner der Erweiterung abfragen
	CQueryExtensionNameDlg QueryDlg (pW, string(pShortName));

		QueryDlg.Show();
		if (QueryDlg.Result() == 0)
			return false;
		return QueryDlg.GetExtName (strExtName);
	}

	return true;
}

bool CompareDLLName (string &strKey, string &strDLL, string &rStrProgID)
{
char cbBuffer[_MAX_PATH];
LONG dwLen = _MAX_PATH;
string strExtKey = g_cbRegExtensions;

	strExtKey += string(g_cbDel) + strKey;		// vollständiger ErweiterungsSchlüssel

// Langen Bezeichner besorgen (für alle Fälle)
	if (RegQueryValue (HKEY_CURRENT_USER, strExtKey.c_str(), cbBuffer, &dwLen) != ERROR_SUCCESS)
		return false;

string strLongName = cbBuffer;

// ClassID besorgen
	dwLen = _MAX_PATH;
	strExtKey += string(g_cbDel) + g_cbClsId;
	if (RegQueryValue (HKEY_CURRENT_USER, strExtKey.c_str(), cbBuffer, &dwLen) != ERROR_SUCCESS)
		return false;

string strCLSID = string(g_cbClsId) + g_cbDel;

	dwLen = _MAX_PATH;
	strCLSID += string(cbBuffer) + g_cbDel + g_cbInprocServer;

	if (RegQueryValue (HKEY_CLASSES_ROOT, strCLSID.c_str(), cbBuffer, &dwLen) != ERROR_SUCCESS)
		return false;

	if (strDLL == cbBuffer) {	// wenn Pfad stimmt, haben wir's
		rStrProgID = strKey;
		strKey = strLongName;
		return true;
	}
	return false;
}
*/

///////////////////////////////////////////////////////////////////////////////
// Fenster, in dem Bezeichner einer zu installierenden Erweiterung abgefragt 
// wird
#pragma warning (disable: 4355)

CQueryExtensionNameDlg::CQueryExtensionNameDlg (pWindow pW, const string &strExtFile)
			: DialogWindow (pW, QUERYEXTENSIONNAME),
			  m_pbOK (this, IDOK),
			  m_sleExtName (this, IDE_EXTNAME),
			  m_ftQueryText (this, IDT_QUERYTEXT)
{
	m_pbOK.Disable();

char cbBuffer[_MAX_PATH];

// Caption richten
	GetCaption (cbBuffer, sizeof(cbBuffer));
	SetCaption (FakeTRiASName (cbBuffer, g_cbTRiAS).c_str());

// AnzeigeText richten
	m_ftQueryText.GetText (cbBuffer, sizeof(cbBuffer));
	m_ftQueryText.SetText (FakeTRiASName (cbBuffer, g_cbTRiAS, strExtFile.c_str()).c_str());
}

#pragma warning (default: 4355)

void CQueryExtensionNameDlg::ButtonClick (ControlEvt e)
{
	switch (e.GetControlID()) {
	case IDOK:
		EndDlg (1);
		break;

	case IDCANCEL:
		EndDlg (0);
		break;
	}
}

void CQueryExtensionNameDlg::EditChange (ControlEvt)
{
	if (m_sleExtName.GetTextLen() > 0)
		m_pbOK.Enable();
	else
		m_pbOK.Disable();
}

bool CQueryExtensionNameDlg::GetExtName (string &strExtName)
{
int iLen = m_sleExtName.GetTextLen();

	if (iLen <= 0) return false;

char cbBuffer[_MAX_PATH];

	m_sleExtName.GetText (cbBuffer, sizeof(cbBuffer));
	strExtName = cbBuffer;

return true;
}
