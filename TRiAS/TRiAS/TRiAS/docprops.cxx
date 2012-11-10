// PropertySheet für TRiAS.Document.2 -----------------------------------------
// File: DOCPROPS.CXX

#include "triaspre.hxx"

// STL-related stuff ----------------------------------------------------------
#define NOMINMAX
#pragma warning (disable: 4304)
#pragma warning (disable: 4114)
#pragma warning (disable: 4786)		// debug info truncated
#include <ospace/std/list>
#include <ospace/std/map>
#include <ospace/std/set>
#include <ospace/std/string>
#include <ospace/std/algorithm>

#include <shlobj.h>

#include <xtsnguid.h>
#include <regprop.hxx>
#include <funcs03.h>
#include <dirisole.h>

#include "editro.hxx"

#include "strings.h"
#include "triasres.h"
#include "docprops.hxx"

#if defined(_DEBUG) && !defined(WIN16)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#pragma optimize("", off)		// problems with map

#define MAXHEADERTEXTLEN	1024
#define IDM_TOGGLERO_POS	5

// Anzeige und Verarbeitung des Dialoges für die ProjektEigenschaften ---------
//
// Dieser Dialog lädt zusätzliche Pages über den Key:
//	HKCR\TRiAS.Document.2\TRiASEx\PropertySheetHandlers
//
bool IrisWind::ShowEditHeader (IUnknown *pIUnkSite, HPROJECT hPr) 
{
bool fResult = false;

	{
	// Dialogfenster generieren
	CEierUhr Wait (this);
	char cbBuffer[_MAX_PATH];

		if (HACTPROJECT == hPr)
			strcpy (cbBuffer, ResString(IDS_DOCPROPS, 64));
		else {
			DEX_GetDataSourceShortName(hPr, cbBuffer);
		
		string str = FakeTRiASName (IDS_DATASOURCEPROPS, cbBuffer);

			strcpy (cbBuffer, str.c_str());
		}

	CDocumentProperties DocProps (this, cbBuffer); 

	// eigene Page hinzufügen
	CEditHeader EHPage (hPr);

		DocProps.AddPage (&EHPage);		// eigene Page ist die erste
		if (HACTPROJECT == hPr)
			LoadPages (DocProps, g_cbDocKey, g_cbDocSubKey, pIUnkSite);			// zusätzliche Pages aus Registry laden

	// Dialogfenster anzeigen
		Wait.Hide();
		DocProps.Show (Centre);			// Header editieren
		fResult = DocProps.Result();
	}
	CoFreeUnusedLibraries();			// DLL's wieder freigeben
	return fResult;
}


///////////////////////////////////////////////////////////////////////////////
// PropertySheet --------------------------------------------------------------
CDocumentProperties::CDocumentProperties (pWindow pWnd, LPCSTR pcTitle)
	: CPropertySheetExt (pcTitle, pWnd)
{
}

CDocumentProperties::~CDocumentProperties (void)
{
}

///////////////////////////////////////////////////////////////////////////////
// immer wieder zu verwendende Routinen 
HRESULT LoadPages (
	CPropertySheetExt &rPage, LPCSTR pcKey, LPCSTR pcSubKey, IUnknown *pIUnkSite,
	LPCSTR pcProgID, int *piPage)
{
// alle sonstigen Pages aus der Registry laden
WStorage IStg;
WDataObject IDO;

	if (DEX_GetProjectStorage (*IStg.ppv())) 
		CreateDataObject (IStg, IDO);

	return rPage.LoadExtPagesFromRegistry (
		HKEY_CLASSES_ROOT, pcKey, pcSubKey, IDO, NULL, pIUnkSite, pcProgID, piPage);
}

HRESULT CreateDataObject (WStorage &rIStg, WDataObject &rIDO)
{ 
// DataObject generieren
HRESULT hr = DataObjectCreateInstance (NULL, IID_IDataObject, rIDO.ppv()); 

	if (FAILED(hr)) return hr;

// Storage im DataObject wegspeichern
STGMEDIUM stm;

	stm.tymed = TYMED_ISTORAGE;
	stm.pstg = rIStg.detach();		// übergibt AddRef()
	stm.pUnkForRelease = NULL;

FORMATETC fe;
UINT uiCf = RegisterClipboardFormat (g_cbDocKey);

	SETDefFormatEtc (fe, uiCf, TYMED_ISTORAGE);
	return rIDO -> SetData (&fe, &stm, true);
}

///////////////////////////////////////////////////////////////////////////////
// Eigene PropertyPage zur Editierung des DB-Headers --------------------------
#pragma warning (disable: 4355)

CEditHeader::CEditHeader (HPROJECT hPr)
	: CPropertyPage (IDD_EDITHEADER, ResString (IDS_HEADERCAP, 32)),
	  m_mleValue (this, IDC_HEADERENTRY),
	  m_tvKeys (this, IDC_HEADERKEYS),
	  m_pbDelete (this, IDC_DELETEKEY),
	  m_pbAddNewEntry (this, IDC_NEWKEY),
	  m_cbRO (this, IDC_READONLY),
	  m_hPr(hPr)
{
	m_pSLE = NULL;
	m_hNormal = NULL;
	m_hSystem = NULL;
	m_fSystemMode = (DEX_QueryMode() & QMSysAdmin) ? true : false;
	m_fRO = DEX_GetROModeEx(hPr) ? true : false;
}

#pragma warning (default: 4355)

CEditHeader::~CEditHeader (void)
{
	DELETE_OBJ(m_pSLE);

// ImageList wird vom Destruktor ~CImageList freigegeben, hier 
// doppeltes Freigeben verhindern
CImageList *pIL = m_tvKeys.SetImageList (NULL, TVSIL_NORMAL);
	
	if (pIL) delete pIL;
}

void CEditHeader::WindowInit (Event)
{
CEierUhr Wait (this);

// explizite Initialisierung der Controls
	m_mleValue.FInit();
	m_tvKeys.FInit();
	m_pbDelete.FInit();
	m_pbAddNewEntry.FInit();
	m_cbRO.FInit();
	m_ilHdr.CreateList (IDB_HEADERSTRIP, 16, 0, RGB(255, 0, 255));

// wenn nicht SuperUser, dann kein RO-Check
	if (!m_fSystemMode)
		m_cbRO.Hide();

// inhaltliche Initialisierungen
	if (!FillTreeView()) return;

CImageList *pIL = m_tvKeys.SetImageList (&m_ilHdr, TVSIL_NORMAL);
	
	if (pIL) delete pIL;
	
	m_tvKeys.SelectItem (m_hNormal);
	SetRO (true);
	m_cbRO.SetChecked (m_fRO);
	m_mleValue.SetTextLimit (MAXHEADERTEXTLEN);
}

extern "C" 
BOOL AddHdrEntry (char *pKey, BOOL, void *pData)
{
GEODBHDRENTRYEX HE;
char cbEntry[MAXHEADERTEXTLEN];

	INITSTRUCT(HE, GEODBHDRENTRYEX);
	strncpy (HE.hdrKey, pKey, HDRKEYLENGTH);
	HE.lphdrText = cbEntry;
	HE.hdrTextLen = sizeof(cbEntry)-1;

	if (EC_OKAY == DEX_ReadHeaderEntry(((CEditHeader *)pData) -> GetCtxHandle(), HE) &&
		!(PROPERTY_TYPE_Hidden & HE.dwFlags)) 
	{
	// abschließende Leerzeichen wegschneiden
	char cbKey[HDRKEYLENGTH+1];

		memset (cbKey, '\0', sizeof(cbKey));
		strncpy (cbKey, pKey, HDRKEYLENGTH);

	char *pT = &cbKey[HDRKEYLENGTH-1];
			
		while (' ' == *pT && pT > cbKey)
			--pT;
		*(pT+1) = '\0';

	// in Liste und Control speichern
		return ((CEditHeader *)pData) -> AddEntry (
				cbKey, cbEntry, HE.dwFlags);
	}

// Assertion nicht mehr richtig, da PROPERTY_TYPE_Dynamic vorkommen kann
//	TX_ASSERT(false);	// sollte nicht passieren
	return true;		// trotz Fehler weitermachen
}

bool CEditHeader::FillTreeView (void)
{
// Hauptschlüssel hinzufügen
	m_hNormal = m_tvKeys.InsertItem (
			ResString (IDS_PROJECTENTRIES, 64), 
			IMG_FOLDER, IMG_FOLDER, TVI_ROOT, TVI_LAST);
	m_hSystem = m_tvKeys.InsertItem (
			ResString (IDS_SYSTEMENTRIES, 64), 
			IMG_FOLDER, IMG_FOLDER, TVI_ROOT, TVI_LAST);
	
	if (NULL == m_hNormal || NULL == m_hSystem)	
		return false;

// HeaderEinträge hinzufügen
ENUMNOKEY ENK;

	ENK.eFcn = (ENUMNOKEYPROC)AddHdrEntry;
	ENK.ePtr = this;

bool fRet = DEX_EnumHeaderEntries(GetCtxHandle(), ENK);

// wenigstens ein SubItem generieren
	{
	ResString resNo (IDS_NOENTRIESAVAIL, 64);

		if (!m_tvKeys.ItemHasChildren(m_hNormal))
			m_tvKeys.InsertItem (resNo, IMG_NONE, IMG_NONE, m_hNormal, TVI_LAST);
		if (!m_tvKeys.ItemHasChildren(m_hSystem))
			m_tvKeys.InsertItem (resNo, IMG_NONE, IMG_NONE, m_hSystem, TVI_LAST);
	}
	return true;
}

bool CEditHeader::AddEntry (LPCSTR pcKey, LPCSTR pcValue, DWORD dwFlags)
{
CHeaderEntry HE (pcKey, pcValue, dwFlags);
int iImage = IMG_STRING;

	if ((dwFlags & HEADER_SYSTEM) && !m_fSystemMode)
		iImage = IMG_STRING_RO;
	else if (dwFlags & HEADER_READONLY) {
		if (dwFlags & HEADER_DYNAMIC)
			iImage = IMG_OBJECT_RO;
		else
			iImage = IMG_STRING_RO;
	}

HTREEITEM hItem = m_tvKeys.InsertItem (pcKey, iImage, iImage,
		(dwFlags & (HEADER_SYSTEM|HEADER_DYNAMIC)) ? m_hSystem : m_hNormal, 
		TVI_LAST);

	m_Entries.insert (hItem, HE);
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// sonstige HelperFunktionen --------------------------------------------------

bool CEditHeader::DeleteActiveKey (HTREEITEM hItem)
{
CEntryList::iterator it = m_Entries.find (hItem);

	if (m_Entries.end() == it || RetrieveRO (hItem)) 
		return false;		// nicht wiedergefunden

// Eintrag als gelöscht kennzeichnen
os_string str = (*it).second.GetKey();

	if (!(*it).second.isNotSaved()) {
	// nur in DB löschen, wenn bereits gespeichert
	CStringSet::iterator its = m_Deleted.find (str);

		if (m_Deleted.end() == its)
			m_Deleted.insert (str);
	}
	m_Entries.erase (it);	// wirklich löschen

// Anzeige nachführen
HTREEITEM hParent = m_tvKeys.GetParentItem (hItem);
HTREEITEM hSibling = m_tvKeys.GetNextItem (hItem, TVGN_NEXT);

	if (NULL == hSibling)
		hSibling = m_tvKeys.GetNextItem (hItem, TVGN_PREVIOUS);

	if (NULL != hSibling)	// Nachbar aktivieren
		m_tvKeys.SelectItem (hSibling);
	m_tvKeys.DeleteItem (hItem);

	TX_ASSERT(NULL != hParent);
	if (!m_tvKeys.ItemHasChildren (hParent))
		m_tvKeys.InsertItem (ResString (IDS_NOENTRIESAVAIL, 64), 
					IMG_NONE, IMG_NONE,	hParent, TVI_LAST);

	SetModified();		// activate 'Apply'
	return true;
}

// neuen Eitrag hinzufügen ----------------------------------------------------
bool CEditHeader::AddNewEntry (void)
{
// Parent des aktiven Entries herausfinden
HTREEITEM hItem = m_tvKeys.GetSelectedItem();
HTREEITEM hParent = NULL;
HTREEITEM hToDelete = NULL;
CEntryList::iterator it = m_Entries.find (hItem);

	if (m_Entries.end() == it) {
	// entweder bereits Parent oder 'Kein Eintrag vorhanden'
		if (m_tvKeys.ItemHasChildren (hItem)) {
		HTREEITEM hChild = m_tvKeys.GetChildItem (hItem);

			hParent = hItem;
			if (m_Entries.end() == m_Entries.find (hChild))
			// SubItem muß ersetzt werden
				hToDelete = hChild;
		} else {
			hToDelete = hItem;
			hParent = m_tvKeys.GetParentItem (hItem);
		}
	} else 
		hParent = m_tvKeys.GetParentItem (hItem);

	TX_ASSERT(hParent == m_hNormal || hParent == m_hSystem);

// evtl. alten 'Dummy'-Schlüssel löschen
	if (hToDelete) m_tvKeys.DeleteItem (hToDelete);

// neuen Eintrag setzen und sofort zum editieren aktivieren
	m_mleValue.SetText (g_cbNil);
	SetRO (m_fRO);

char cbBuffer[64];
ResString resNew (IDS_NEWENTRY, 32);
unsigned int uiCnt = 1;

	do {
		wsprintf (cbBuffer, "%s%d", resNew.Addr(), uiCnt++);
	} while (KeyExists (cbBuffer));

CHeaderEntry HE (cbBuffer, g_cbNil, (hParent == m_hNormal) ? HEADER_NORMAL : HEADER_SYSTEM);

	hItem = m_tvKeys.InsertItem (cbBuffer, IMG_STRING, IMG_STRING, hParent, TVI_LAST);
	InsertNotSaved (hItem, HE);

	m_tvKeys.SelectItem (hItem);
	EditLabel (hItem);
	return true;
}

// RO-Flag in Anzeige und den internen Daten nachführen -----------------------
bool CEditHeader::AdjustRO (HTREEITEM hItem, bool fRO)
{
	TX_ASSERT(IsHeaderEntryItem(hItem));

	m_cbRO.SetChecked (fRO);
	m_mleValue.SetRO (fRO);

	if (fRO) m_pbDelete.Disable();
	else 	 m_pbDelete.Enable();

CEntryList::iterator it = m_Entries.find (hItem);

	if (m_Entries.end() != it) {
		(*it).second.SetRO (fRO);
		SetModified();		// activate 'Apply'

	int iImage = IMG_STRING;

		if ((*it).second.isDynamic())
			iImage = IMG_OBJECT_RO;
		else		
			iImage = fRO ? IMG_STRING_RO : IMG_STRING;

		m_tvKeys.SetItemImage (hItem, iImage, iImage);
		return true;
	}

return false;
}

// RO-Zustand eines Eintrages finden ------------------------------------------
bool CEditHeader::RetrieveRO (HTREEITEM hItem)
{
//	TX_ASSERT(IsHeaderEntryItem(hItem));

CEntryList::iterator it = m_Entries.find (hItem);

	if (m_Entries.end() != it) {
		if (!m_fSystemMode && (*it).second.isSystem())
			return true;	// für nicht SU sind systeminterne immer RO

		if ((*it).second.isDynamic())
			return true;	// dynamische Property nie editierbar
		return (*it).second.isRO();
	}
	return true;	// nicht gefunden, also schreibgeschützt
}

bool CEditHeader::RetrieveDynamic (HTREEITEM hItem)
{
CEntryList::iterator it = m_Entries.find (hItem);

	if (m_Entries.end() != it) 
		return (*it).second.isDynamic();

	return false;	// nicht gefunden, also nicht dynamisch
}

// Neuen Eintrag zu Liste hinzufügen und als nicht gespeichert kennzeichnen ---
bool CEditHeader::InsertNotSaved (HTREEITEM hItem, const CHeaderEntry &rHE)
{
	m_Entries.insert (hItem, rHE);

CEntryList::iterator it = m_Entries.find (hItem);

	if (m_Entries.end() != it) {	// wieder gefunden
		(*it).second.SetNotSaved();
		return true;
	}

return false;
}

// Bildchen an Parents richten ------------------------------------------------
void CEditHeader::AdjustImage (HTREEITEM hItem)
{
	if (!m_tvKeys.ItemHasChildren (hItem)) 
		return;		// nur Parents behandeln

	if (m_tvKeys.GetItemState (hItem, TVIS_EXPANDED) & TVIS_EXPANDED) 
		m_tvKeys.SetItemImage (hItem, IMG_OPENFOLDER, IMG_OPENFOLDER);	// ist expandiert
	else
		m_tvKeys.SetItemImage (hItem, IMG_FOLDER, IMG_FOLDER);	// ist collabiert
}

void CEditHeader::EditLabel (HTREEITEM hItem)
{
	DELETE_OBJ(m_pSLE);
	m_pSLE = m_tvKeys.EditLabel (hItem);
	if (m_pSLE) m_pSLE -> SetTextLimit (HDRKEYLENGTH);
}


bool CEditHeader::IsHeaderEntryItem (HTREEITEM hItem)
{
// wenns ein Folder ist, dann gleich raus
	if (hItem == m_hNormal || hItem == m_hSystem)
		return false;

// wenn's im container ist, dann ist's ein EntryItem
CEntryList::iterator it = m_Entries.find (hItem);

	return m_Entries.end() != it;
}

bool CEditHeader::KeyExists (LPCSTR pcNewKey, HTREEITEM hItem)
{
	for (CEntryList::iterator itl = m_Entries.begin();
		 itl != m_Entries.end(); ++itl)
	{
		if ((*itl).second.GetKey() == pcNewKey && 
			(NULL == hItem || (*itl).first != hItem))
		{
			return true;
		}
	}
	return false;		// nicht wiedergefunden
}

// Text inm aktuellen Item neu setzen -----------------------------------------
bool CEditHeader::ChangeItemText (void)
{
	if (!m_mleValue.isModified())
		return false;		// not changed

HTREEITEM hItem = m_tvKeys.GetSelectedItem();
CEntryList::iterator it = m_Entries.find (hItem);

	if (m_Entries.end() != it) {
	char cbBuffer[MAXHEADERTEXTLEN+1];

		m_mleValue.GetText (cbBuffer, sizeof(cbBuffer)-1);
		(*it).second.SetValue (cbBuffer);

		SetModified();		// activate 'Apply'
		return true;
	}
	return false;
}

// setzen des UI entsprechend RO-Status ---------------------------------------
void CEditHeader::SetRO (bool fFlag)
{
	m_mleValue.SetRO (fFlag);
	m_cbRO.SetChecked (fFlag);

	if (fFlag) m_pbDelete.Disable();
	else 	   m_pbDelete.Enable();
}

HTREEITEM CEditHeader::MatchPositionToHTreeItem (UINT *puiFlags)
{
POINT pt;

	GetCursorPos (&pt);
	ScreenToClient (m_tvKeys.Handle (API_CONTROL_HCONTROL), &pt);

	if (NULL == puiFlags) {
	UINT uiFlags = 0;

		return m_tvKeys.HitTest ((Point &)pt, &uiFlags);
	}
	return m_tvKeys.HitTest ((Point &)pt, puiFlags);
}


bool CEditHeader::IsSystemEntry (HTREEITEM hItem)
{
CEntryList::iterator it = m_Entries.find (hItem);

	if (m_Entries.end() != it) 
		return (*it).second.isSystem();
	return false;	// nicht gefunden, also SystemEintrag
}

///////////////////////////////////////////////////////////////////////////////
// EventHandler

// neues Item soll selektiert werden ------------------------------------------
BOOL CEditHeader::OnSelChanging (NotifyEvt e)
{
	ChangeItemText();
	return false;		// always allow operation
}

// im EditFenster wurde geändert ----------------------------------------------
void CEditHeader::EditChange (ControlEvt e)
{
	if ((uint)e.GetControlID() == IDC_HEADERENTRY)
		ChangeItemText();
}

// neues Item wurde selektiert ------------------------------------------------
void CEditHeader::OnSelChanged (NotifyEvt e)
{
HTREEITEM hItem = m_tvKeys.GetSelectedItem();
CEntryList::iterator it = m_Entries.find (hItem);

	if (m_Entries.end() == it) {
	// Schlüssel nicht im container
		m_mleValue.SetText(g_cbNil);
		m_mleValue.SetRO (true);

		m_pbDelete.Disable();
		m_cbRO.SetChecked (false);
		m_cbRO.Disable();
	} else {
		m_pbDelete.Enable();
		if ((*it).second.isDynamic()) {
			m_cbRO.SetChecked (true);
			m_cbRO.Disable();
		} else
			m_cbRO.Enable();

		m_mleValue.SetText ((*it).second.GetValue().c_str());
		SetRO (RetrieveRO (hItem) || m_fRO);
	}

	if (!m_fSystemMode) {
		if (hItem == m_hSystem || IsSystemEntry (hItem))
			m_pbAddNewEntry.Disable();
		else
			m_pbAddNewEntry.Enable();
	}

	AdjustImage (hItem);
}

// Editieren lediglich bei den 'richtigen' HeaderEinträgen erlauben
BOOL CEditHeader::OnBeginLabelEdit (NotifyEvt e)
{
// true cancels operation
HTREEITEM hItem = m_tvKeys.GetSelectedItem();

	if (NULL == hItem) return true;

// when not found, then disable edit
CEntryList::iterator it = m_Entries.find (hItem);
bool fRO = RetrieveRO (hItem);

	if (fRO) return true;		// schreibgeschützte nicht editieren

	return (m_Entries.end() == it) ? true : false;
}

// wenn der Key geändert wurde, dann bisherigen Eintrag löschen und neuen hinzufügen
void CEditHeader::OnEndLabelEdit (NotifyEvt e)
{
HTREEITEM hItem = m_tvKeys.GetSelectedItem();

	TX_ASSERT(NULL != hItem);

CEntryList::iterator it = m_Entries.find (hItem);

	if (m_Entries.end() == it) 
		return;		// nicht wiedergefunden

// jetzt neuen Key generieren
TV_DISPINFO *ptvi = (TV_DISPINFO  *)e.GetNotifyInfo();
LPCSTR pcNewText = ptvi -> item.pszText;

	if (NULL == pcNewText)	// key not modified
		pcNewText = (*it).second.GetKey().c_str();

// überprüfen, ob der neue Schlüssel wirklich eindeutig ist
	if (KeyExists (pcNewText, hItem)) {
	// diesen Eintrag gibt es schon an anderer Stelle
	MessBox mb (ResString (IDS_DUPHDRENTRIES_CAP, 32), 
				ResString (IDS_DUPHDRENTRIES, 128), this);

		mb.SetType (ExclamationIcon | OkayButton);	
		mb.Show();
	
		EditLabel (hItem);		// nochmal versuchen
		return;
	}

// alten Eintrag als gelöscht kennzeichnen
os_string str = (*it).second.GetKey();

	if (str == pcNewText) 
		return;		// kein neuer Schlüssel

	if (!(*it).second.isNotSaved()) {
	// nur in DB löschen, wenn bereits gespeichert
	CStringSet::iterator its = m_Deleted.find (str);

		if (m_Deleted.end() == its)		// zum ersten mal gelöscht
			m_Deleted.insert (str);
	}

// neuen Eintrag an alter Stelle erzeugen
CHeaderEntry HE ((*it).second);

	m_Entries.erase (it);

// neu einfügen und als nicht gespeichert kennzeichnen
	HE.SetKey (pcNewText);
	InsertNotSaved (hItem, HE);
	m_tvKeys.SetItemText (hItem, pcNewText);

	SetModified();		// activate 'Apply'
}

// Apply oder OK gedrückt -----------------------------------------------------
namespace {
	class CDeleteEntryInDB 
	{
	public:
		CDeleteEntryInDB (HPROJECT hPr) : m_hPr(hPr) {}

		bool operator() (os_string rstr)
		{
		GEODBHDRENTRY HE;

			INITSTRUCT (HE, GEODBHDRENTRY);
			strncpy (HE.hdrKey, rstr.c_str(), HDRKEYLENGTH);
			return (EC_OKAY == DEX_DeleteHeaderEntry(m_hPr, HE)) ? true : false;
		}

	private:
		HPROJECT m_hPr;
	};

	class CSaveEntryIfDirty
	{
	public:
		CSaveEntryIfDirty(HPROJECT hPr) : m_hPr(hPr) {}

		bool operator() (CEntryListPair rPair)
		{
		CHeaderEntry &rHE = rPair.second;

		// Eintrag nur bearbeiten, wenn dieser zu speichern ist
			if (!rHE.isDirty()) return false;

		// Eintrag in GeoDB speichern
		GEODBHDRENTRYEX HE;

			INITSTRUCT (HE, GEODBHDRENTRYEX);
			strncpy (HE.hdrKey, rHE.GetKey().c_str(), HDRKEYLENGTH);
			HE.hdrTextLen = rHE.GetValue().length();
			HE.lphdrText = (char *)rHE.GetValue().c_str();
			HE.dwFlags = rHE.isSystem() ? HEADER_SYSTEM : HEADER_NORMAL;
			HE.dwFlags |= rHE.isRO() ? HEADER_READONLY : HEADER_NORMAL;

		bool fResult = (EC_OKAY == DEX_WriteHeaderEntry(m_hPr, HE)) ? true : false;

		// Eintrag wurde gespeichert
			rHE.SetDirty (false);
			rHE.SetNotSaved (false);

			return fResult;
		}

	private:
		HPROJECT m_hPr;
	};

	bool IsEntryDirty (CEntryListPair &rPair)
	{
		return rPair.second.isDirty();
	}
};

// OK oder Apply --------------------------------------------------------------
BOOL CEditHeader::OnOK (NotifyEvt e)
{
int iCnt = 0;
bool fUpdate = false;

// zu löschende Einträge aus DB löschen
	if (m_Deleted.size() > 0) {
	CDeleteEntryInDB DeleteEntryInDB(GetCtxHandle());

		for_each (m_Deleted.begin(), m_Deleted.end(), DeleteEntryInDB);
		fUpdate = true;
	}
	m_Deleted.erase();		// alle Einträge aus Set löschen

// zu modifizierende Einträge in DB abgleichen
	count_if (m_Entries.begin(), m_Entries.end(), IsEntryDirty, iCnt);
	if (iCnt > 0) {
	CSaveEntryIfDirty SaveEntryIfDirty(GetCtxHandle());
	
		for_each (m_Entries.begin(), m_Entries.end(), SaveEntryIfDirty);
		fUpdate = true;
	}

	if (fUpdate) {
		DEXN_ReReadHeader();		// alle sollen Header neu lesen
		DEX_SetDirtyGeoDB(true);	// DirtyFlag setzen
	}

	SetModified (false);	// wieder passivieren
	return false;			// always allow operation
}

// Knopf dieser Page gedrückt -------------------------------------------------
void CEditHeader::ButtonClick (ControlEvt e)
{
HTREEITEM hItem = m_tvKeys.GetSelectedItem();

	switch ((uint)e.GetControlID()) {
	case IDC_DELETEKEY:		// aktuellen Eintrag löschen
		DeleteActiveKey (hItem);
		break;

	case IDC_NEWKEY:		// neuen Schlüssel erzeugen
		AddNewEntry();
		break;

	case IDC_READONLY:
		AdjustRO (hItem, m_cbRO.isChecked() || m_fRO);
		break;

	default:
		break;
	}
}

// Ein Item wurde Expandiert/Collapst -----------------------------------------
void CEditHeader::OnItemExpanded (NotifyEvt e)
{
NM_TREEVIEW *pnmtv = (NM_TREEVIEW *)e.GetNotifyInfo();
HTREEITEM hItem = pnmtv -> itemNew.hItem;

	AdjustImage (hItem);
}

void CEditHeader::OnClick (NotifyEvt e)
{
NMHDR *pNMHdr = e.GetNotifyInfo();

	if (pNMHdr -> idFrom != IDC_HEADERKEYS || pNMHdr -> code != NM_RCLICK) 
	{
		CPropertyPage::OnClick (e);
		return;		// nicht rechte Maus im TreeViewCtrl
	}

// rausfinden, welches Item aktiv ist
HTREEITEM hItem = MatchPositionToHTreeItem();

	if (NULL == hItem) return;			// kein Item getroffen

HTREEITEM hCurrItem = m_tvKeys.GetSelectedItem();

	if (hCurrItem != hItem)
		m_tvKeys.SelectItem (hItem);

// Popupmenu anzeigen
	if (!m_fSystemMode) {
		if (!IsHeaderEntryItem (hItem)) {
			if (m_hNormal != hItem)
				return;
		} else if (IsSystemEntry (hItem))
			return;			// kein Menu
	}

Menu HdrMenu (IsHeaderEntryItem(hItem) ? IDR_EDITHDRENTRYMENU : IDR_EDITHDRMENU);
POINT pt;

	GetCursorPos (&pt);
	m_hPopupMenu = GetSubMenu (HdrMenu.Handle (API_MENU_HMENU), 0);		// SubMenu holen

	if (!TrackPopupMenu (m_hPopupMenu, TPM_LEFTALIGN|TPM_LEFTBUTTON, 
				pt.x, pt.y, 0, Handle (API_WINDOW_HWND), NULL))
	{
		m_tvKeys.SelectItem (hCurrItem);
	}

	m_hPopupMenu = NULL;
}


// DoppelClick ----------------------------------------------------------------
void CEditHeader::OnDblClick (NotifyEvt e)
{
NMHDR *pNMHdr = e.GetNotifyInfo();
HTREEITEM hCurrItem = m_tvKeys.GetSelectedItem();

	if (pNMHdr -> idFrom != IDC_HEADERKEYS || pNMHdr -> code != NM_DBLCLK)
	{
		CPropertyPage::OnDblClick (e);
		return;		// nicht linke DoppelMaus im TreeViewCtrl
	}
		
// Finden des getroffenen Items
HTREEITEM hItem = MatchPositionToHTreeItem();

	if (NULL == hItem || hCurrItem != hItem) 
		return;			// kein Item getroffen

// auslösen der jeweiligen default-action
	if (!IsHeaderEntryItem (hItem)) {
		if (m_hNormal == hItem || m_hSystem == hItem) 
			CPropertyPage::OnDblClick (e);
		else if (m_fSystemMode)
			PostMessage (Handle(API_WINDOW_HWND), WM_COMMAND, IDM_NEWENTRY, 0L);
	} else {
		if (IsSystemEntry(hItem)) {
			if (m_fSystemMode)
				PostMessage (Handle(API_WINDOW_HWND), WM_COMMAND, IDM_NEWENTRY, 0L);
		} 
		else if (RetrieveRO (hItem))
			PostMessage (Handle(API_WINDOW_HWND), WM_COMMAND, IDM_NEWENTRY, 0L);
		else
			PostMessage (Handle(API_WINDOW_HWND), WM_COMMAND, IDM_RENAMEENTRY, 0L);
	}
}

// PopupMenu wird aufgeklappt -------------------------------------------------
void CEditHeader::MenuInit (MenuInitEvt e)
{
HTREEITEM hItem = m_tvKeys.GetSelectedItem();

	if (NULL == hItem || NULL == m_hPopupMenu) 
		return;		// generic error

	if (!IsHeaderEntryItem(hItem)) {
		if (m_hNormal == hItem || m_hSystem == hItem) {
		// wenn nicht expandiert, dann Menu ändern
			if (m_tvKeys.GetItemState (hItem, TVIS_EXPANDED) & TVIS_EXPANDED) {
				if (IsWin40()) 
					SetMenuDefaultItem (m_hPopupMenu, IDM_COLLAPSE, false);
			} else {
				ModifyMenu (m_hPopupMenu, IDM_COLLAPSE, MF_BYCOMMAND, 
							IDM_EXPAND, ResString (IDS_EXPAND, 32));
				if (IsWin40()) 
					SetMenuDefaultItem (m_hPopupMenu, IDM_EXPAND, false);
			}
		} else {	
		// 'Dummy'-SubItem
			EnableMenuItem (m_hPopupMenu, IDM_COLLAPSE, MF_BYCOMMAND|MF_GRAYED);
			if (IsWin40()) 
				SetMenuDefaultItem (m_hPopupMenu, IDM_NEWENTRY, false);
		}
	} else {
	bool fRO = RetrieveRO (hItem);

		if (!m_fSystemMode) {
			if (DeleteMenu (m_hPopupMenu, IDM_TOGGLERO, MF_BYCOMMAND))
				DeleteMenu (m_hPopupMenu, IDM_TOGGLERO_POS, MF_BYPOSITION);
		} else {
			CheckMenuItem (m_hPopupMenu, IDM_TOGGLERO, 
				MF_BYCOMMAND|(fRO ? MF_CHECKED : MF_UNCHECKED));
			if (RetrieveDynamic(hItem))
				EnableMenuItem (m_hPopupMenu, IDM_TOGGLERO, MF_BYCOMMAND|MF_GRAYED);
		}
		EnableMenuItem (m_hPopupMenu, IDM_DELETEENTRY, MF_BYCOMMAND|(fRO ? MF_GRAYED : MF_ENABLED));
		EnableMenuItem (m_hPopupMenu, IDM_RENAMEENTRY, MF_BYCOMMAND|(fRO ? MF_GRAYED : MF_ENABLED));

		if (IsWin40()) 
			SetMenuDefaultItem (m_hPopupMenu, fRO ? IDM_NEWENTRY : IDM_RENAMEENTRY, false);
	}
}

// Menuselektion aus Popupmenu ------------------------------------------------
void CEditHeader::MenuCommand (MenuCommandEvt e)
{
HTREEITEM hItem = m_tvKeys.GetSelectedItem();

	switch ((uint)e.GetItemID()) {
	case IDM_COLLAPSE:
		m_tvKeys.Expand (hItem, TVE_COLLAPSE);
		AdjustImage (hItem);
		break;

	case IDM_EXPAND:
		m_tvKeys.Expand (hItem, TVE_EXPAND);
		AdjustImage (hItem);
		break;

	case IDM_NEWENTRY:
		AddNewEntry();
		break;

	case IDM_FINDENTRY:
		break;

	case IDM_DELETEENTRY:
		DeleteActiveKey (hItem);
		break;

	case IDM_RENAMEENTRY:
		EditLabel (hItem);
		break;

	case IDM_TOGGLERO:
		AdjustRO (hItem, !RetrieveRO (hItem) || m_fRO);
		break;

	default:
		break;
	}
}

///////////////////////////////////////////////////////////////////////////////
// Objekt, welches im Baum hängt 
CHeaderEntry::CHeaderEntry (void)
{
	m_fSystem = false;
	m_fRO = false;

	m_fModified = false;
	m_fNotSaved = false;
}

CHeaderEntry::CHeaderEntry (LPCSTR pcKey, LPCSTR pcValue, DWORD dwFlags)
		: m_strKey(pcKey), m_strValue(pcValue)
{
	m_fSystem = (dwFlags & HEADER_SYSTEM) ? true : false;
	m_fRO = (dwFlags & HEADER_READONLY) ? true : false;
	m_fDynamic = (dwFlags & HEADER_DYNAMIC) ? true : false;

	m_fModified = false;
	m_fNotSaved = false;
}

CHeaderEntry::CHeaderEntry (const CHeaderEntry &rHdr)
		: m_strKey(rHdr.GetKey()), m_strValue(rHdr.GetValue())
{
	m_fSystem = rHdr.isSystem();
	m_fRO = rHdr.isRO();
	m_fDynamic = rHdr.isDynamic();

	m_fModified = rHdr.isDirty();
	m_fNotSaved = rHdr.isNotSaved();
}

