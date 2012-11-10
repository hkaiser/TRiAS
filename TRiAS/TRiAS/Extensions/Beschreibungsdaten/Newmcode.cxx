// Neuanlegen, Modifizieren und loeschen von MCodes der PBD -------------------
// File: NEWMCODE.CXX

#include "idntsdbp.hxx"

#if defined(WIN32)
#pragma warning (disable: 4304)
#include <ospace/std/set>
#include <ospace/std/algorithm>
#endif // WIN32

#include <eieruhr.hxx>

#include "identsdb.hxx"
#include "identres.h"
#include "newmcode.h"
#include "newmcode.hxx"
#include "defmerkm.hxx"

#include "defident.h"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern "C" 
BOOL _XTENSN_EXPORT PASCAL FillListBox (long Ident, BOOL, void *pData);

int FillMKListBoxEntry (long lMCode, BaseListBox *pLB)
{
	TX_ASSERT(NULL != pLB);

PBDMERKMAL pbdData;
char KText[_MAX_PATH] = { '\0' };

	INITSTRUCT(pbdData, PBDMERKMAL);
	pbdData.pbdTyp = 'm';
	pbdData.pbdCode = lMCode;
	pbdData.pbdKText = KText;
	pbdData.pbdKTextLen = sizeof(KText) -1;
	pbdData.pbdLTextLen = 0;
	pbdData.ipbdMTyp = 'u';
	DEX_GetPBDData (pbdData);

	if (strncmp ("__", pbdData.pbdKText, 2)) {		// wirklich systeminterne ausblenden
	int iIndex = pLB -> AddString (pbdData.pbdKText);

		TX_ASSERT(-1 != iIndex);
		pLB -> AddExtentEntry (pbdData.pbdKText);
		pLB -> SetItemData (iIndex, lMCode);
		return iIndex;		// liefert immer neuen Index
	}
	return -1;		// nicht hinzugenommen
}

extern "C" 
BOOL _XTENSN_EXPORT PASCAL FillMKListBox (long MCode, DWORD, void *pData)
{
	FillMKListBoxEntry (MCode, (BaseListBox *)pData);
	return TRUE;
}

#include "dlghelp.h"

static DWORD s_dwHelpNew[] = {
	IDOK,				IDH_NEWMCODEDLG_OK,
	IDCANCEL,			IDH_NEWMCODEDLG_CANCEL,
	IDT_NEWMKMCODE,		IDH_NEWMCODEDLG_NEWMKMCODE,
	IDE_NEWMKMCODE,		IDH_NEWMCODEDLG_NEWMKMCODE,
	IDL_NEWMKMCODES,	IDH_NEWMCODEDLG_NEWMCODESLIST,
	0,			0,		// EndeKennung
};

void NewMCodeDlg::HelpRequest (HelpRequestEvt e)
{
	if (HelpWmHelp == e.RequestType()) {
	const HELPINFO *pHI = e.GetHelpInfo();
	char cbHelpFile[_MAX_PATH];

		strcpy (cbHelpFile, g_cbHelpPath);
		strcat (cbHelpFile, DIALOG_HELP_FILE);

		WinHelp ((HWND)pHI -> hItemHandle, cbHelpFile, 
			 HELP_WM_HELP, (DWORD)s_dwHelpNew);
	}
}

// Konstruktoren/Destruktoren der DialogFenster --------------------------------
#pragma warning (disable: 4355)

NewMCodeDlg::NewMCodeDlg (pWindow pW, ResID res, short iMkBase) 
	     : DialogWindow (pW, res),
	       OKButton (this, IDOK),
	       CancelButton (this, IDCANCEL),
		   SelectNewBttn (this, IDC_NEWENTRY),
	       MCodeList (this, IDL_NEWMKMCODES),
		   m_cbSelObjClass (this, IDC_SELOBJCLASS),
		   m_iMkBase (iMkBase)
{
CEierUhr Wait (this);

	MCodeList.InitListboxExtents();

// Variablen initaialisieren
	m_fCorrected = false;
	_MCode = -1L;
	_lActIdent = 0L;

// Objektklassen bereitstellen, ListBox füllen
ENUMLONGKEY ELI;

	ELI.eKey = 'i';
	ELI.eFcn = (ENUMLONGKEYPROC)FillListBox;
	ELI.ePtr = (void *)&m_cbSelObjClass;
	DEX_EnumPBDData (ELI);

	if (0 < m_cbSelObjClass.GetCount()) {
		m_cbSelObjClass.ChangeCurrentIndex(0);			// den ersten auswählen
		BuildList (m_cbSelObjClass.GetItemData (0));	// ListBox neu befüllen
		AdjustOK();
	}
}

#pragma warning (default: 4355)

NewMCodeDlg::~NewMCodeDlg()
{
	MCodeList.FreeListboxExtents();
}

void _XTENSN_EXPORT NewMCodeDlg::ButtonClick (ControlEvt e)
{
	switch ((unsigned int)e.GetControlID()) {
	case IDOK:
		HandleExistingMCode();
		break;

	case IDCANCEL:
		EndDlg (m_fCorrected);
		break;

	case IDC_NEWENTRY:
		HandleNewMCode();
		break;
	}
}

void _XTENSN_EXPORT NewMCodeDlg::ListBoxSel (ControlEvt e)
{
	switch ((unsigned int)e.GetControlID()) {
	case IDL_NEWMKMCODES:
		AdjustOK();
		break;

	case IDC_SELOBJCLASS:
		{ 
		int iIndex = m_cbSelObjClass.GetCurrentIndex();

			if (iIndex != -1) {
				_lActIdent = m_cbSelObjClass.GetItemData (iIndex);
				TX_ASSERT(0 != _lActIdent);

				BuildList (_lActIdent);	// ListBox neu befüllen
			}
			AdjustOK();
		}
		break;
	}
}

void NewMCodeDlg::BuildList (LONG lIdent)
{
	TX_ASSERT(0 != lIdent && -1 != lIdent);

	MCodeList.ForwardEvent (WM_SETREDRAW, FALSE);
	MCodeList.Clear();
	MCodeList.ResetListboxExtents();

ENUMLONGKEYEX ELK;

	ELK.eKey = lIdent;
	ELK.eFcn = (ENUMLONGKEYEXPROC)FillMKListBox;
	ELK.ePtr = (void *)&MCodeList;
	ELK.eData = MPObjectFeature|MPSystemFeatures|MPReadOnlyFeatures|MPPbdOnly;
	DEX_EnumObjektMerkmaleClassEx (ELK);

	if (MCodeList.GetCount() > 0)
		MCodeList.ChangeCurrentIndex (0);

	_lActIdent = lIdent;
	MCodeList.ForwardEvent (WM_SETREDRAW, TRUE);
}

void _XTENSN_EXPORT NewMCodeDlg::ListBoxClk (ControlEvt)
{
	HandleExistingMCode();
}

///////////////////////////////////////////////////////////////////////////////
// 
void NewMCodeDlg::HandleNewMCode (void)
{
//	_MCode = DEX_GetUniqueMCodeEx(DEX_GetObjectsProject(_lActIdent));
	_MCode = DEX_GetUniqueMCode();

int iResult = 0;
int iIndex = m_cbSelObjClass.GetCurrentIndex();
char cbBuffer[_MAX_PATH] = { '\0' };

	TX_ASSERT(iIndex != -1);
	m_cbSelObjClass.GetString (cbBuffer, iIndex, sizeof(cbBuffer));
	_lActIdent = m_cbSelObjClass.GetItemData (iIndex);

	{
#if defined(_DEBUG)
	bool fShowAdminDlg = (QMSysAdmin & DEX_QueryMode()) ? true : false;

		if (!fShowAdminDlg && (GetKeyState(VK_SHIFT) < 0 && GetKeyState(VK_CONTROL) < 0))
			fShowAdminDlg = true;

	ResID resID(!fShowAdminDlg ? DEFINEMERKMAL : DEFINEMERKMAL_ADMIN, &g_pTE -> RF());
	DefineMerkmalDlg DMCDlg (this, resID, _MCode, _lActIdent, cbBuffer, NULL, fShowAdminDlg);
#else
	ResID resID(DEFINEMERKMAL, &g_pTE -> RF());
	DefineMerkmalDlg DMCDlg (this, resID, _MCode, _lActIdent, cbBuffer, NULL, false);
#endif // defined(_DEBUG)

		DMCDlg.Show (Centre);
		iResult = DMCDlg.Result();
		_MCode = DMCDlg.GetMCode();
	}

	if (iResult) {
		CorrectMCode (_MCode, true);
		if (!m_fCorrected) {
		ResString resClose (ResID (IDS_BUTTONCLOSE, &g_pTE -> RF()), 16);

			CancelButton.SetText (resClose);
			m_fCorrected = true;
		}
	}
}

void NewMCodeDlg::HandleExistingMCode (void)
{
char cbNewProp[TEXTLEN] = { '\0' };

	_MCode = GetModMCode(cbNewProp, sizeof(cbNewProp));

int iResult = 0;
int iIndex = m_cbSelObjClass.GetCurrentIndex();
char cbBuffer[_MAX_PATH] = { '\0' };

	TX_ASSERT(iIndex != -1);
	m_cbSelObjClass.GetString (cbBuffer, iIndex, sizeof(cbBuffer));
	_lActIdent = m_cbSelObjClass.GetItemData (iIndex);

	{
#if defined(_DEBUG)
	bool fShowAdminDlg = (QMSysAdmin & DEX_QueryMode()) ? true : false;

		if (!fShowAdminDlg && (GetKeyState(VK_SHIFT) < 0 && GetKeyState(VK_CONTROL) < 0))
			fShowAdminDlg = true;

	ResID resID(!fShowAdminDlg ? DEFINEMERKMAL : DEFINEMERKMAL_ADMIN, &g_pTE -> RF());
	DefineMerkmalDlg DMCDlg (this, resID, _MCode, _lActIdent, cbBuffer, cbNewProp, fShowAdminDlg);
#else
	ResID resID(DEFINEMERKMAL, &g_pTE -> RF());
	DefineMerkmalDlg DMCDlg (this, resID, _MCode, _lActIdent, cbBuffer, cbNewProp, false);
#endif // defined(_DEBUG)

		DMCDlg.Show (Centre);
		iResult = DMCDlg.Result();
		_MCode = DMCDlg.GetMCode();
	}

	if (iResult) {
		CorrectMCode (_MCode, false);
		if (!m_fCorrected) {
		ResString resClose (ResID (IDS_BUTTONCLOSE, &g_pTE -> RF()), 16);

			CancelButton.SetText (resClose);
			m_fCorrected = true;
		}
	}
}

void NewMCodeDlg::CorrectMCode (long lMCode, bool fNewEntry)
{
int iIndex = MCodeList.GetCurrentIndex();

	if (iIndex != -1 && !fNewEntry) {
	char cbBuffer[_MAX_PATH];

		MCodeList.GetString (cbBuffer, iIndex, sizeof(cbBuffer));
		MCodeList.RemoveExtentEntry (cbBuffer);
		MCodeList.DelString (iIndex);		// wenn nicht neu, austauschen
	}

	if (0 == MCodeList.GetCount()) {
	// es ist der erste intrag überhaupt
		if (0 == FillMKListBoxEntry (lMCode, &MCodeList))
			MCodeList.ChangeCurrentIndex (0);
	} else {
	// neuen Eintrag selektieren
		iIndex = FillMKListBoxEntry (lMCode, &MCodeList);
		if (-1 != iIndex)
			MCodeList.ChangeCurrentIndex (iIndex);
	}
}

long NewMCodeDlg::GetModMCode (char *pBuffer, int iLen) 
{
int iIndex = MCodeList.GetCurrentIndex();

	pBuffer[0] = '\0';
	if (-1 != iIndex) {
	long lMCode = MCodeList.GetItemData (iIndex);

		TX_ASSERT(0 != lMCode);
		MCodeList.GetString (pBuffer, iIndex, iLen);
		return lMCode;
	} 
	return -1L;
}

bool NewMCodeDlg::AdjustOK (void)
{
char cbBuffer[_MAX_PATH];
long lMCode = GetModMCode(cbBuffer, sizeof(cbBuffer));

	if (0 != _lActIdent && -1 != lMCode) {
	HPROJECT hPr = DEX_GetObjectsProject(_lActIdent);

		if ((DEX_GetROModeIdent(_lActIdent) && !DEX_GetGDODataSourceEx(hPr)) || DEX_GetROModeEx (HACTPROJECT)) 
			OKButton.SetText (ResString (ResID(IDS_SHOWENTRY, &g_pTE -> RF()), 32));
		else
			OKButton.SetText (ResString (ResID(IDS_MODIFYENTRY, &g_pTE -> RF()), 32));

		if (DEX_GetSchemaUpdatableEx(hPr))
			SelectNewBttn.Enable();
		else
			SelectNewBttn.Disable();

		OKButton.Enable();
		return true;
	} else {
		OKButton.Disable();
		return false;
	}
}

///////////////////////////////////////////////////////////////////////////////
// Liste der Idents für Löschfenster 
MKItem::MKItem (long MCode, char *pKT)
{
	_Status = MKI_InValid;
	_MCode = MCode;
	_pKText = new char [strlen(pKT)+1];
	if (_pKText) {
		strcpy (_pKText, pKT);
		_Status = MKI_Valid;
	}
}

MKItem::~MKItem (void) 
{
	DELETE_OBJ(_pKText);
}


#pragma warning (disable: 4355)

MKList::MKList (void)
	: CTree (GetLongKey, CmpLongKey),
	  locTab (*this)
{
	// nothing else to do
}

#pragma warning (default: 4355)

void MKList::UserDelete (void *pObj)
{
#if defined(__GWXX__)
	((MKItem *)pObj) -> MKItem::~MKItem ();
#else
	((MKItem *)pObj) -> ~MKItem ();
#endif
}

// Ein Element der Liste als gelöscht markieren
void MKList::MarkDeleted (long MCode)
{
CTable t(*this);

	if (t.Find (&MCode)) {
	MKItemLock l(t);

		if (l) l -> Status() = MKI_Deleted;
	}
}

bool MKList::hasDeleted (void) 
{
CTable t(*this);

	for (t.First(); t.Valid(); t.Next()) {
	MKItemLock l(t);

		if (!l) continue;
		if (l -> Status() == MKI_Deleted)
			return true;
	}
	return false;
}

// Konstruktor für Löschfenster -----------------------------------------------
extern "C" 
BOOL _XTENSN_EXPORT PASCAL FillMCodeList (long MCode, BOOL, void *pData)
{
PBDMERKMAL pbdData;
char KText[_MAX_PATH] = { '\0' };

	memset (&pbdData, '\0', sizeof(PBDMERKMAL));

	pbdData.dwSize = sizeof(PBDMERKMAL);
	pbdData.pbdTyp = 'm';
	pbdData.pbdCode = MCode;
	pbdData.pbdKText = KText;
	pbdData.pbdKTextLen = sizeof(KText) -1;
	pbdData.pbdLTextLen = 0;
	pbdData.ipbdMTyp = 'u';
	DEX_GetPBDData (pbdData);
	        
	ContCreate (*(MKItemCreator *)pData, MKItem)(MCode, pbdData.pbdKText);
	return true;	// weitermachen
}

static DWORD s_dwHelpDelete[] = {
	IDOK,					IDH_DELMCODEDLG_OK,
	IDCANCEL,				IDH_DELMCODEDLG_CANCEL,
	IDT_DELMKMCODES,		IDH_DELMCODEDLG_DELMKMCODES,
	IDL_DELMKMCODES,		IDH_DELMCODEDLG_DELMKMCODES,
	IDB_DELMKUNUSEDMKS,		IDH_DELMCODEDLG_DELMKUNUSEDMKS,
	IDB_DELMCODES_SELALL,	IDH_DELMCODEDLG_DELMKSELALL,
	0,			0,		// EndeKennung
};

void DelMCodeDlg::HelpRequest (HelpRequestEvt e)
{
	if (HelpWmHelp == e.RequestType()) {
	const HELPINFO *pHI = e.GetHelpInfo();
	char cbHelpFile[_MAX_PATH];

		strcpy (cbHelpFile, g_cbHelpPath);
		strcat (cbHelpFile, DIALOG_HELP_FILE);

		WinHelp ((HWND)pHI -> hItemHandle, cbHelpFile, 
			 HELP_WM_HELP, (DWORD)s_dwHelpDelete);
	}
}

#pragma warning (disable: 4355)

DelMCodeDlg::DelMCodeDlg (pWindow pW, ResID res, short iMkBase)
	     : DialogWindow (pW, res),
	       OKButton (this, IDC_DELETE),
		   CancelBttn (this, IDCANCEL),
	       m_pbSelAll (this, IDB_DELMCODES_SELALL),
	       MCodeList (this, IDL_DELMKMCODES),
		   m_cbSelObjClass (this, IDC_SELOBJCLASS),
	       m_iMkBase (iMkBase)
{
// EierUhr anzeigen 
CEierUhr Wait (this);

	MCodeList.InitListboxExtents();

// Variablen initialisieren
	m_fMCodesFilled = false;
	_lActIdent = 0L;
	_pMCodes = NULL;
	
	ATLTRY(_pMCodes = new MKList());
	if (_pMCodes == NULL) return;

// Controls initialisieren
	OKButton.Disable();

// Objektklassen bereitstellen
ENUMLONGKEY ELI;

	ELI.eKey = 'i';
	ELI.eFcn = (ENUMLONGKEYPROC)FillListBox;
	ELI.ePtr = (void *)&m_cbSelObjClass;
	DEX_EnumPBDData (ELI);

	if (0 < m_cbSelObjClass.GetCount()) {
		m_cbSelObjClass.ChangeCurrentIndex(0);		// den ersten auswählen
        _lActIdent = m_cbSelObjClass.GetItemData (0);
		FillMCodes (_lActIdent);
		BuildList();
	}
}

#pragma warning (default: 4355)

DelMCodeDlg::~DelMCodeDlg (void)
{
	MCodeList.FreeListboxExtents();
	DELETE_OBJ(_pMCodes);
}

void DelMCodeDlg::FillMCodes (long lIdent)
{
	DelMKList();

HPROJECT hPr = DEX_GetObjectsProject(lIdent);

	if (HACTPROJECT != hPr) {
	// nur für normale Objektklassen testen
		if (!DEX_GetOpenedEx(hPr))
			return;	// nicht geöffnet
		if (DEX_GetROModeIdent(lIdent) && !DEX_GetGDODataSourceEx(hPr))
			return;	// real schreibgeschützt
	}

MKItemCreator MKCr (MCodes());
ENUMLONGKEYEX ELK;

	ELK.eKey = lIdent;
	ELK.eFcn = (ENUMLONGKEYEXPROC)FillMCodeList;
	ELK.ePtr = (void *)&MKCr;
	ELK.eData = MPObjectFeature|MPSystemFeatures|MPReadOnlyFeatures|MPPbdOnly;
	DEX_EnumObjektMerkmaleClassEx (ELK);

	_lActIdent = lIdent;
}

void _XTENSN_EXPORT DelMCodeDlg::ButtonClick (ControlEvt e)
{
	switch ((unsigned int)e.GetControlID()) {
	case IDC_DELETE:
		if (DeleteMCodes()) {
		// erfolgreich gelöscht
			CancelBttn.SetText(ResString(ResID(IDS_CLOSE, &g_pTE->RF()), 64));
		}
		break;

	case IDCANCEL:
		EndDlg();
		break;

	case IDB_DELMKHELP:
		break;

	case IDB_DELMCODES_SELALL:
		{	// alle markieren
		CEierUhr Wait (this);
		short iCount = MCodeList.GetCount();
		
			MCodeList.ChangeSelected (Range (0, iCount-1));
			if (MCodeList.GetNoSelected())
				OKButton.Enable();
			else
				OKButton.Disable();
		}
		break;
	}
}


void _XTENSN_EXPORT DelMCodeDlg::ListBoxSel (ControlEvt e)
{
	switch ((unsigned int)e.GetControlID()) {
	case IDC_SELOBJCLASS:
		{ 
		int iIndex = m_cbSelObjClass.GetCurrentIndex();

			if (-1 != iIndex) {
				_lActIdent = m_cbSelObjClass.GetItemData (iIndex);
				TX_ASSERT(0 != _lActIdent);

				FillMCodes (_lActIdent);
				BuildList();		// ListBox füllen
				MCodeList.ClearSelected();
			}
		}
		break;
	}

	if (MCodeList.GetNoSelected())
		OKButton.Enable();
	else
		OKButton.Disable();
}

//---------------------------------------------------------------------------
bool DelMCodeDlg::DelMKList (void)
{
	if (NULL == _pMCodes) {
		ATLTRY(_pMCodes = new MKList());
		return (NULL != _pMCodes) ? true : false;
	}
	_pMCodes -> EveryDelete();
	return true;
}

//---------------------------------------------------------------------------
void DelMCodeDlg::BuildList (bool unusedOnly)
{
// ListBox ausblenden und leeren
	MCodeList.ForwardEvent (WM_SETREDRAW, FALSE);
	MCodeList.Clear();

CTable t(MCodes().Tab());

	for (t.First(); t.Valid(); t.Next()) {
	MKItemLock l(t);

		if (!l) continue;

		if (l -> Status() == MKI_Deleted) continue;
		if (unusedOnly && isMCodeUsed (l -> MCode())) 
			continue;

		if (strncmp ("__", l -> GetKurzText(), 2)) {		// wirklich systeminterne ausblenden
		int iIndex = MCodeList.AddString (l -> GetKurzText());

			MCodeList.AddExtentEntry (l -> GetKurzText());
			if (-1 != iIndex)
				MCodeList.SetItemData (iIndex, l -> MCode());

			if (l -> Status() == MKI_Restored) {
				l -> Status() = MKI_Valid;
				MCodeList.ChangeSelected (iIndex);
			}
		}
	}

// ListBox wieder anzeigen
	MCodeList.ForwardEvent (WM_SETREDRAW, TRUE);

	if (0 < MCodeList.GetCount()) {
		MCodeList.Enable();
		m_pbSelAll.Enable();
	} 
	else {
	ResString resNoItems (ResID (IDS_NOUNUSEDPROPERTIES, &g_pTE -> RF()), 64);

		MCodeList.AddString (resNoItems);
		MCodeList.AddExtentEntry (resNoItems);
		MCodeList.Disable();
		m_pbSelAll.Disable();
	}

	TX_ASSERT(0 != _lActIdent);
	if (DEX_GetROModeIdent (_lActIdent)) {
	// diese Tabelle ist schreibgeschützt
		OKButton.Disable();
	} 
	else {
		if (MCodeList.GetNoSelected())
			OKButton.Enable();
		else
			OKButton.Disable();
	}
}


// alle markierten Einträge als gelöscht kennzeichnen -------------------------
bool DelMCodeDlg::DeleteMCodes (void)
{
	if (0 == MCodeList.GetNoSelected()) 
		return false;

// erst markieren
int iIndex = MCodeList.GetFirstSelected();

	while (iIndex != -1) {
		MCodes().MarkDeleted (MCodeList.GetItemData (iIndex));
		iIndex = MCodeList.GetNextSelected();
	}

// dann löschen
long lMCode = FirstMCode();
long lIdent = ActiveID();
CEierUhr Wait (GetParent());

ResString resUndo (ResID (IDS_UNDODELMCODES, &g_pTE->RF()), 128);
HRESULT hr = DEX_BeginUndoLevel (resUndo.Addr());

// Sätze aus Pbd herauslöschen
	DEX_BeginPBDTransaction();
	while (lMCode != -1L) {
		if (!((CIdentsDBExtension *)g_pTE)->DeleteMCode (lMCode, lIdent)) {
		// Fehler: Zustand wieder herstellen
			DEX_BreakPBDTransaction();
			if (SUCCEEDED(hr)) 
				DEX_CancelUndoLevel (false);	// nicht mehr gebraucht
			return false;
		}
		lMCode = NextMCode();
	}

	DEX_EndPBDTransaction();
	DEXN_PBDMCodesChanged();
	if (SUCCEEDED(hr)) 
		DEX_EndUndoLevel();

// jetzt Liste neu aufbauen
	FillMCodes (m_cbSelObjClass.GetItemData (0));
	BuildList();

	return true;
}

// Interfacefunktionen liefern nacheinader alle als gelöscht markierten MCodes 
long DelMCodeDlg::NextMCode (bool iFirst) 
{
// ersten/nächsten gelöschten Ident suchen
	if (iFirst) 
		MCodes().Tab().First();
	else
		MCodes().Tab().Next();

	for (/* bereits initialisiert */;
	     MCodes().Tab().Valid();
	     MCodes().Tab().Next())
	{
	MKItemLock l(MCodes().Tab());

		if (!l || l -> Status() != MKI_Deleted) continue;
		return l -> MCode();
	}
	return -1L;		// nichts gefunden
}

// Testen, ob ein MCode in der GeoDb benutzt ist oder nicht -------------------
extern "C"
BOOL _XTENSN_EXPORT PASCAL FillAllMCodeList (long lMCode, DWORD, void *pData)
{
	((DelMCodeDlg::MCodeSet *)pData) -> insert (lMCode);
	return true;
}

bool DelMCodeDlg::isMCodeUsed (long lMCode)
{
	if (!m_fMCodesFilled) {
	ENUMNOKEYLONGEX ENK;

		ENK.eFcn = (ENUMNOKEYLONGEXPROC)FillAllMCodeList;
		ENK.ePtr = &m_setMCodes;
		ENK.eData = (MPSystemFeatures|MPAllFeatures|MPReadOnlyFeatures);

		DEX_EnumMCodesEx (ENK);		// mit allen MCodes (außer PbdOnly) füllen

		m_fMCodesFilled = true;
	}
	return m_setMCodes.find (lMCode) != m_setMCodes.end();
}
