// Neuanlegen, Modifizieren und loeschen von Idents der PBD -------------------
// File: NEWIDENT.CXX

#include "idntsdbp.hxx"

#include <eieruhr.hxx>
#include <errinstx.hxx>

#include "identres.h"
#include "newident.h"
#include "newident.hxx"
#include "defident.hxx"

#include "defident.h"

#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern "C" 
BOOL _XTENSN_EXPORT PASCAL FillListBox (long Ident, BOOL, void *pData)
{
HPROJECT hPr = DEX_GetObjectsProject(Ident);

	TX_ASSERT(HACTCONNECTION != hPr);
	if (HACTPROJECT != hPr && !DEX_GetOpenedEx(hPr))
		return TRUE;		// nicht geöffnete Datenquelle

PBDDATA pbdData;
char cbBuffer[_MAX_PATH] = { '\0' };

	INITSTRUCT(pbdData, PBDDATA);
	pbdData.pbdTyp = 'i';
	pbdData.pbdCode = Ident;
	pbdData.pbdKText = cbBuffer;
	pbdData.pbdKTextLen = sizeof(cbBuffer) -1;
	pbdData.pbdLTextLen = 0;
	DEX_GetPBDData (pbdData);

char outBuff[_MAX_PATH] = { '\0' };

	ClassFromIdentX (Ident, outBuff);
	strcat (outBuff, ":");
	strcat (outBuff, cbBuffer);

// wenn mehr als eine Datenquelle geöffnet ist, dann den Namen der zugehörigen 
// in Klammern hintendran hängen
	if (DEX_GetOpenConnectionCount (QDCAllOpen|QDCCountQueryDefs) > 1) {
		if (NULL != DEX_GetDataSourceShortName (hPr, cbBuffer)) {
			strcat (outBuff, " (");
			strcat (outBuff, cbBuffer);
			strcat (outBuff, ")");
		}
	}

int iIndex = ((BaseListBox *)pData) -> AddString (outBuff);

	((BaseListBox *)pData) -> AddExtentEntry (outBuff);
	((BaseListBox *)pData) -> SetItemData (iIndex, Ident);		// Ident wird diesem LB-Eintrag zugeordnet
	return true;	// weitermachen
}

#if defined(WIN32)

#include "dlghelp.h"

static DWORD s_dwHelpNew[] = {
	IDOK,			IDH_NEWIDENTDLG_OK,
	IDCANCEL,		IDH_NEWIDENTDLG_CANCEL,
	IDT_NEWIDENT,		IDH_NEWIDENTDLG_NEWIDENT,
	IDE_NEWIDIDENT,		IDH_NEWIDENTDLG_NEWIDENT,
	IDL_NEWIDLIST,		IDH_NEWIDENTDLG_NEWIDENTSLIST,
	0,			0,		// EndeKennung
};

void NewIdentDlg::HelpRequest (HelpRequestEvt e)
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
#endif

// Konstruktoren/Destruktoren der DialogFenster --------------------------------
#pragma warning (disable: 4355)

NewIdentDlg::NewIdentDlg (pWindow pW, ResID res) 
	     : DialogWindow (pW, res),
	       OKButton (this, IDOK),
	       CancelButton (this, IDCANCEL),
		   NewEntryBttn (this, IDC_NEWENTRY),
	       IdentList (this, IDL_NEWIDLIST)
{
// EierUhr anzeigen 
CEierUhr Wait(this);

	IdentList.InitListboxExtents();

// Variablen initialisieren
	m_fCorrected = false;
	_Ident = -1L;

// ListBox füllen
ENUMLONGKEY ELK;

	memset (&ELK, '\0', sizeof (ENUMLONGKEY));
	ELK.eKey = 'i';
	ELK.eFcn = (ENUMLONGKEYPROC)FillListBox;
	ELK.ePtr = (void *)&IdentList;
	DEX_EnumPBDData (ELK);

	if (IdentList.GetCount() > 0)
		IdentList.ChangeCurrentIndex (0);

	AdjustOK();
	IdentList.SetFocus();
}

#pragma warning (default: 4355)

NewIdentDlg::~NewIdentDlg()
{
	IdentList.FreeListboxExtents();
}

void _XTENSN_EXPORT NewIdentDlg::ButtonClick (ControlEvt e)
{
	switch ((unsigned int)e.GetControlID()) {
	case IDOK:
		HandleExistingIdent();
		break;

	case IDCANCEL:
		EndDlg (m_fCorrected);
		break;

	case IDC_NEWENTRY:
		HandleNewIdent();
		break;
	}
}

void _XTENSN_EXPORT NewIdentDlg::ListBoxSel (ControlEvt)
{
	AdjustOK();
}

void _XTENSN_EXPORT NewIdentDlg::ListBoxClk (ControlEvt)
{
	HandleExistingIdent();
}

void NewIdentDlg::HandleNewIdent (void)
{
int iResult = 0;
#if defined(_DEBUG)
bool fShowAdminDlg = (QMSysAdmin & DEX_QueryMode()) ? true : false;

	if (!fShowAdminDlg && (GetKeyState(VK_SHIFT) < 0 && GetKeyState(VK_CONTROL) < 0))
		fShowAdminDlg = true;

ResID resID(!fShowAdminDlg ? DEFINEIDENT : DEFINEIDENT_ADMIN, &g_pTE -> RF());
#else
ResID resID(DEFINEIDENT, &g_pTE -> RF());
#endif // defined(_DEBUG)
DefineIdentDlg DIDlg (this, resID);

int iIndex = IdentList.GetCurrentIndex();
INT_PTR lIdent = _Ident;
HPROJECT hPr = NULL;

	if (-1 != iIndex) {
		lIdent = IdentList.GetItemData (iIndex);
		hPr = DEX_GetObjectsProject(lIdent);
	}

// neuer Identifikator/OKS
	if (!DIDlg.FInit ("", hPr))
		return;

	DIDlg.Show (Centre);
	iResult = DIDlg.Result();
	if (iResult) {
		_Ident = DIDlg.GetIdent();
		CorrectIdent (_Ident, true);
		if (!m_fCorrected) {
		ResString resClose (ResID (IDS_BUTTONCLOSE, &g_pTE -> RF()), 16);

			CancelButton.SetText (resClose);
			m_fCorrected = true;
		}
	}
}

void NewIdentDlg::HandleExistingIdent (void)
{
char inBuff[TEXTLEN+20];

	_Ident = GetModIdent(inBuff, sizeof(inBuff));

int iResult = ONOK_ERROR;
#if defined(_DEBUG)
bool fShowAdminDlg = (QMSysAdmin & DEX_QueryMode()) ? true : false;

	if (!fShowAdminDlg && (GetKeyState(VK_SHIFT) < 0 && GetKeyState(VK_CONTROL) < 0))
		fShowAdminDlg = true;

ResID resID(!fShowAdminDlg ? DEFINEIDENT : DEFINEIDENT_ADMIN, &g_pTE -> RF());
#else
ResID resID(DEFINEIDENT, &g_pTE -> RF());
#endif // defined(_DEBUG)
DefineIdentDlg DIDlg (this, resID);

	if (-1 == _Ident) {		// neuer Identifikator/OKS
		if (!DIDlg.FInit (inBuff))
			return;
	} else {
	// bereits existierender Identifikator/OKS
		if (!DIDlg.FInit (_Ident))
			return;
	}

	DIDlg.Show (Centre);
	iResult = DIDlg.Result();

	if (iResult) {
		_Ident = DIDlg.GetIdent();
		CorrectIdent (_Ident, ONOK_CREATED == iResult);
		if (!m_fCorrected) {
		ResString resClose (ResID (IDS_BUTTONCLOSE, &g_pTE -> RF()), 16);

			CancelButton.SetText (resClose);
			m_fCorrected = true;
		}
	}
}

void NewIdentDlg::CorrectIdent (long lIdent, bool fNewEntry)
{
// Eintrag auf irgend eine Weise wiederfinden
int iIndex = IdentList.GetCurrentIndex();

	if (iIndex != -1 && !fNewEntry && lIdent == IdentList.GetItemData (iIndex)) 
		IdentList.DelString (iIndex);	// wenn nicht neu und wirklich modifiziert, dann austauschen
	else 
	{
		iIndex = FindEntryInList (lIdent);
		if (-1 != iIndex) {
		char cbBuffer[_MAX_PATH];

			IdentList.GetString (cbBuffer, iIndex, sizeof(cbBuffer));
			IdentList.RemoveExtentEntry (cbBuffer);
			IdentList.DelString (iIndex);	// wenn nicht neu, austauschen
		}
	}

	if (0 == IdentList.GetCount()) {
	// erster Eintrag
		if (FillListBox (lIdent, true, (void *)&IdentList))
			IdentList.ChangeCurrentIndex (0);
	} 
	else {
		FillListBox (lIdent, true, (void *)&IdentList);

	// neuen Eintrag wiederfinden und selektieren
		iIndex = FindEntryInList (lIdent);
		if (-1 != iIndex)
			IdentList.ChangeCurrentIndex (iIndex);
	} 
}

int NewIdentDlg::FindEntryInList (long lIdent)
{
	IdentList.ForwardEvent (WM_SETREDRAW, FALSE);

char inBuff[TEXTLEN+20];
int iOldIndex = IdentList.GetCurrentIndex();

	ClassFromIdentX (lIdent, inBuff);
	IdentList.ChangeCurrentIndex (-1);

int iIndex = IdentList.FindString (inBuff);

	while (-1 != iIndex) {
		if (lIdent == IdentList.GetItemData (iIndex))
			break;

	// nächsten suchen
	int iPrevIndex = iIndex;

		IdentList.ChangeCurrentIndex (iIndex);
		iIndex = IdentList.FindString (inBuff);
		if (iIndex <= iPrevIndex) {
		// einmal die Runde rum gemacht
			iIndex = -1;
			break;
		}
	}

	IdentList.ChangeCurrentIndex (iOldIndex);
	IdentList.ForwardEvent (WM_SETREDRAW, TRUE);
	return iIndex;
}

///////////////////////////////////////////////////////////////////////////////
// nachsehen, ob es diesen Ident schon gibt
long NewIdentDlg::GetModIdent (char *inBuff, int iLen) 
{
int iIndex = IdentList.GetCurrentIndex();

	inBuff[0] = '\0';
	if (-1 != iIndex) {
	long lIdent = IdentList.GetItemData (iIndex);

		TX_ASSERT(0 != lIdent);
		return lIdent;
	} 
	return -1L;
}

bool NewIdentDlg::AdjustOK (void)
{
// ROMode
char cbBuffer[_MAX_PATH];
long lIdent = GetModIdent(cbBuffer, sizeof(cbBuffer));

	if (-1 != lIdent) {
	HPROJECT hPr = DEX_GetObjectsProject(lIdent);

		if ((DEX_GetROModeEx (hPr) && !DEX_GetGDODataSourceEx(hPr)) || DEX_GetROModeEx (HACTPROJECT)) {
			OKButton.SetText (ResString (ResID(IDS_SHOWENTRY, &g_pTE -> RF()), 32));
		} else {
		// GDO-Datenbanken können Texte ändern
			OKButton.SetText (ResString (ResID(IDS_MODIFYENTRY, &g_pTE -> RF()), 32));
		}
		
		if (DEX_GetSchemaUpdatableEx(hPr))
			NewEntryBttn.Enable();
		else
			NewEntryBttn.Disable();

	// OKButton 
		OKButton.Enable();
		return true;
	} else {
		OKButton.Disable();
		return false;
	}
}

///////////////////////////////////////////////////////////////////////////////
// Liste der Idents für Löschfenster 
IDItem::IDItem (long Id, char *pKT)
{
	_Status = IDI_InValid;
	_Ident = Id;
	_pKText = new char [strlen(pKT)+1];
	if (_pKText) {
		strcpy (_pKText, pKT);
		_Status = IDI_Valid;
	}
}

IDItem::~IDItem (void) 
{
	DELETE_OBJ(_pKText);
}


#pragma warning (disable: 4355)

IDList::IDList (void)
	: CTree (GetLongKey, CmpLongKey),
	  locTab (*this)
{
	// nothing else to do
}

#pragma warning (default: 4355)

void _XTENSN_EXPORT IDList::UserDelete (void *pObj)
{
#if defined(__GWXX__)
	((IDItem *)pObj) -> IDItem::~IDItem ();
#else
	((IDItem *)pObj) -> ~IDItem ();
#endif
}

// Ein Element der Liste als gelöscht markieren
void IDList::MarkDeleted (long Ident)
{
CTable t(*this);

	if (t.Find (&Ident)) {
	IDItemLock l(t);

		if (l) l -> Status() = IDI_Deleted;
	}
}

bool IDList::hasDeleted (void) 
{
CTable t(*this);

	for (t.First(); t.Valid(); t.Next()) {
	IDItemLock l(t);

		if (!l) continue;
		if (l -> Status() == IDI_Deleted)
			return true;
	}
	return false;
}

// Konstruktor für Löschfenster -----------------------------------------------
extern "C" 
BOOL _XTENSN_EXPORT PASCAL FillIdentList (long Ident, BOOL, void *pData)
{
HPROJECT hPr = DEX_GetObjectsProject(Ident);

	TX_ASSERT(NULL != hPr);
	if (HACTPROJECT != hPr) {
	// nur für normale Objektklassen testen
		if (!DEX_GetOpenedEx(hPr))
			return TRUE;	// nicht geöffnet
		if (DEX_GetROModeEx (hPr) && !DEX_GetGDODataSourceEx(hPr))
			return TRUE;	// real schreibgeschützt
	}

PBDDATA pbdData;
char KText[33];

	memset (&pbdData, '\0', sizeof(PBDDATA));

	pbdData.dwSize = sizeof(PBDDATA);
	pbdData.pbdTyp = 'i';
	pbdData.pbdCode = Ident;
	pbdData.pbdKText = KText;
	pbdData.pbdKTextLen = sizeof(KText) -1;
	pbdData.pbdLTextLen = 0;
	DEX_GetPBDData (pbdData);

	KText[32] = '\0';	// sicherheitshalber beenden
	
	ContCreate (*(IDItemCreator *)pData, IDItem)(Ident, pbdData.pbdKText);
	return true;	// weitermachen
}

// kontextsensitive Hilfe -----------------------------------------------------
static DWORD s_dwHelpDelete[] = {
	IDOK,			IDH_DELIDENTDLG_OK,
	IDCANCEL,		IDH_DELIDENTDLG_CANCEL,
	IDT_DELIDENT,		IDH_DELIDENTDLG_DELIDENTS,
	IDL_DELIDLIST,		IDH_DELIDENTDLG_DELIDENTS,
	IDB_DELIDUNUSED,	IDH_DELIDENTDLG_DELIDUNUSEDIDENTS,
	IDB_DELIDENTS_SELALL,	IDH_DELIDENTDLG_DELIDSELALL,
	0,			0,		// EndeKennung
};

void DelIdentDlg::HelpRequest (HelpRequestEvt e)
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

DelIdentDlg::DelIdentDlg (pWindow pW, ResID res)
	     : DialogWindow (pW, res),
	       OKButton (this, IDOK),
	       m_pbSelAll (this, IDB_DELIDENTS_SELALL),
	       IdentList (this, IDL_DELIDLIST)
{
// EierUhr anzeigen 
CEierUhr Wait(this);

	IdentList.InitListboxExtents();

// Variablen initialisieren
	_pIdents = new IDList ();
	if (_pIdents == NULL) 
		return;

// Controls initialisieren
	OKButton.Disable();

// ListBox füllen
ENUMLONGKEY ELK;

	memset (&ELK, '\0', sizeof (ENUMLONGKEY));
	ELK.eKey = 'i';
	ELK.eFcn = (ENUMLONGKEYPROC)FillIdentList;

	{
	IDItemCreator IDCr (Idents());

		ELK.ePtr = (void *)&IDCr;
		DEX_EnumPBDData (ELK);
	}

	BuildList();		// ListBox füllen
	IdentList.ClearSelected();
}

#pragma warning (default: 4355)

DelIdentDlg::~DelIdentDlg (void)
{
	IdentList.FreeListboxExtents();
	DELETE_OBJ(_pIdents);
}


void _XTENSN_EXPORT DelIdentDlg::ButtonClick (ControlEvt e)
{
	switch ((unsigned int)e.GetControlID()) {
	case IDOK:
		EndDlg (DeleteIdents());
		break;

	case IDCANCEL:
		EndDlg();
		break;

	case IDB_DELIDHELP:
		break;

	case IDB_DELIDDELETE:	// als gelöscht markieren
		DeleteIdents();
		break;

	case IDB_DELIDENTS_SELALL:
		{	// alle markieren
		CEierUhr Wait (this);
		short iCount = IdentList.GetCount();
		
			IdentList.ChangeSelected (Range (0, iCount-1));
			OKButton.Enable();
		}
		break;
	}
}


void _XTENSN_EXPORT DelIdentDlg::ListBoxSel (ControlEvt)
{
	if (IdentList.GetNoSelected())
		OKButton.Enable();
	else
		OKButton.Disable();
}


void DelIdentDlg::BuildList (bool unusedOnly)
{
// ListBox ausblenden und leeren
	IdentList.Hide();
	IdentList.Clear();
	IdentList.ResetListboxExtents();

CTable t(Idents().Tab());
ULONG iConnCnt = DEX_GetOpenConnectionCount (QDCAllOpen|QDCCountQueryDefs);
char outBuff[_MAX_PATH];

	for (t.First(); t.Valid(); t.Next()) {
	IDItemLock l(t);

		if (!l || IDI_Deleted == l -> Status()) 
			continue;

	long lIdent = l -> Id();
	HPROJECT hPr = DEX_GetObjectsProject(lIdent);

		if (unusedOnly && DEX_isIdentUsed (lIdent) && HACTPROJECT != hPr) 
			continue;	// Zuordnungsobjektklassen dürfen immer gelöscht werden

		ClassFromIdentX (lIdent, outBuff);
		strcat (outBuff, ":");
		strcat (outBuff, l -> GetKurzText());

	// wenn mehr als eine Datenquelle geöffnet ist, dann den Namen der zugehörigen 
	// in Klammern hintendran hängen
		if (iConnCnt > 1) {
		char cbBuffer[_MAX_PATH];

			TX_ASSERT(NULL != hPr);
			if (NULL != DEX_GetDataSourceShortName (hPr, cbBuffer)) {
				strcat (outBuff, " (");
				strcat (outBuff, cbBuffer);
				strcat (outBuff, ")");
			}
		}
	
	int iIndex = IdentList.AddString (outBuff);

		IdentList.AddExtentEntry (outBuff);
		if (-1 != iIndex)
			IdentList.SetItemData (iIndex, lIdent);

		if (l -> Status() == IDI_Restored) {
			l -> Status() = IDI_Valid;
			IdentList.ChangeSelected (iIndex);
		}
	}

// ListBox wieder anzeigen
	IdentList.Show();
	if (0 < IdentList.GetCount()) {
		IdentList.Enable();
		m_pbSelAll.Enable();
	} else {
	ResString resNoItems (ResID (IDS_NOUNUSEDIDENTS, &g_pTE -> RF()), 64);

		IdentList.AddString (resNoItems);
		IdentList.AddExtentEntry (resNoItems);
		IdentList.Disable();
		m_pbSelAll.Disable();		
	}
}


// alle markierten Einträge als gelöscht kennzeichnen -------------------------
bool DelIdentDlg::DeleteIdents (void)
{
	if (IdentList.GetNoSelected() == 0) return false;

CEierUhr Wait (this);		// EierUhr anzeigen
int iIndex = IdentList.GetFirstSelected();

	while (iIndex != -1) {
	ULONG ulIdent = 0;

		ulIdent = IdentList.GetItemData (iIndex);
		TX_ASSERT(0 != ulIdent);
		Idents().MarkDeleted (ulIdent);

		iIndex = IdentList.GetNextSelected();
	}
	return true;
}

// Interfacefunktionen liefern nacheinader alle als gelöscht markierten Idents 
long DelIdentDlg::NextIdent (Bool iFirst) 
{
// ersten/nächsten gelöschten Ident suchen
	if (iFirst) 
		Idents().Tab().First();
	else
		Idents().Tab().Next();

	for (/* bereits initialisiert */;
	     Idents().Tab().Valid();
	     Idents().Tab().Next())
	{
	IDItemLock l(Idents().Tab());

		if (!l || l -> Status() != IDI_Deleted) continue;
		return l -> Id();
	}
	return -1L;		// nichts gefunden
}

