// Neuanlegen, Modifizieren und loeschen von Idents der PBD -------------------
// File: NEWRCODE.CXX

#include "idntsdbp.hxx"

#include <eieruhr.hxx>

#include "identres.h"
#include "newrcode.h"
#include "newrcode.hxx"
#include "defrelat.hxx"

#include "defident.h"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern "C" {

BOOL _XTENSN_EXPORT PASCAL FillRkListBox (long lRCode, BOOL, void *pData)
{
PBDDATA pbdData;
char KText[33];

	memset (&pbdData, '\0', sizeof(PBDDATA));

	pbdData.dwSize = sizeof(PBDDATA);
	pbdData.pbdTyp = 'r';
	pbdData.pbdCode = lRCode;
	pbdData.pbdKText = KText;
	pbdData.pbdKTextLen = sizeof(KText) -1;
	pbdData.pbdLTextLen = 0;
	DEX_GetPBDData (pbdData);
	KText[32] = '\0';

char outBuff[TEXTLEN+20];

	wsprintf (outBuff, "%08ld:%s", lRCode, pbdData.pbdKText);
	((ListBox *)pData) -> AddString (outBuff);

return true;	// weitermachen
}

} // extern "C"

#if defined(WIN32)

#include "dlghelp.h"

static DWORD s_dwHelpNew[] = {
	IDOK,			IDH_NEWRCODEDLG_OK,
	IDCANCEL,		IDH_NEWRCODEDLG_CANCEL,
	IDT_NEWRKRCODE,		IDH_NEWRCODEDLG_NEWRKRCODE,
	IDE_NEWRELRCODE,	IDH_NEWRCODEDLG_NEWRKRCODE,
	IDL_NEWRELLIST,		IDH_NEWRCODEDLG_NEWRCODESLIST,
	0,			0,		// EndeKennung
};

void NewRCodeDlg :: HelpRequest (HelpRequestEvt e)
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

NewRCodeDlg :: NewRCodeDlg (pWindow pW, ResID res) 
	     : DialogWindow (pW, res),
	       OKButton (this, IDOK),
	       CancelButton (this, IDCANCEL),
#if !defined(WIN32)
	       HelpButton (this, IDB_NEWRELHELP),
#endif // !WIN32
	       ModRCode (this, IDE_NEWRELRCODE),
	       RCodeList (this, IDL_NEWRELLIST)
{
// SandUhr
CEierUhr Wait (this);

// Variablen initaialisieren
	m_fCorrected = false;
	m_lRCode = -1L;

#if !defined(WIN32)
// HelpButton passivieren
	HelpButton.Disable();
#endif // !WIN32

// NumEdit initialiseren
	ModRCode.SetNumEditMode (NumEditX :: NEM_NoTest);
	
// ListBox füllen
ENUMLONGKEY ELK;

	memset (&ELK, '\0', sizeof (ENUMLONGKEY));
	ELK.eKey = 'r';
	ELK.eFcn = (ENUMLONGKEYPROC)FillRkListBox;
	ELK.ePtr = (void *)&RCodeList;
	DEX_EnumPBDData (ELK);

	RCodeList.ChangeCurrentIndex (-1);
	AdjustOK();

	ModRCode.SetFocus();
}

#pragma warning (default: 4355)

void _XTENSN_EXPORT NewRCodeDlg :: ButtonClick (ControlEvt e)
{
	switch ((unsigned int)e.GetControlID()) {
	case IDOK:
		HandleNewRCode();
		break;

	case IDCANCEL:
		EndDlg (m_fCorrected);
		break;

	case IDB_NEWRELHELP:
		break;
	}
}

void _XTENSN_EXPORT NewRCodeDlg :: ListBoxSel (ControlEvt)
{
int iIndex = RCodeList.GetCurrentIndex();

	if (iIndex != -1) {
	char inBuff[TEXTLEN+20];

		RCodeList.GetString (inBuff, iIndex, sizeof(inBuff));

	char *pT = strchr (inBuff, ':');
	
		TX_ASSERT(pT);

		*pT = '\0';
		ModRCode.SetText (inBuff);
	}
	AdjustOK();
}

void _XTENSN_EXPORT NewRCodeDlg :: ListBoxClk (ControlEvt)
{
	HandleNewRCode();
}

void NewRCodeDlg :: HandleNewRCode (void)
{
	if ((m_lRCode = GetModRCode()) != -1L) {
	int iResult = 0;
	
		{
		CDefineRelationDlg DRCDlg (this, ResID (DEFINERELATION, &g_pTE -> RF()), 
					   m_lRCode);

			DRCDlg.Show (Centre);
			iResult = DRCDlg.Result();
		}
		if (iResult) {
			CorrectRCode (m_lRCode);
			if (!m_fCorrected) {
			ResString resClose (ResID (IDS_BUTTONCLOSE, &g_pTE -> RF()), 16);

				CancelButton.SetText (resClose);
				m_fCorrected = true;
			}
		}
	}
}

void _XTENSN_EXPORT NewRCodeDlg :: EditChange (ControlEvt)
{
	if (ModRCode.GetTextLen() > 0) {
	char inBuff[TEXTLEN+20];
	
		ModRCode.GetText (inBuff, sizeof(inBuff));
	
	short iPrevIndex = RCodeList.GetCurrentIndex();

		RCodeList.ChangeCurrentIndex (-1);
	
	short iIndex = RCodeList.FindString (inBuff);
	
		RCodeList.ChangeCurrentIndex (iIndex != -1 ? iIndex : iPrevIndex);
	}
	AdjustOK();
}


void NewRCodeDlg :: CorrectRCode (long lRCode)
{
int iIndex = RCodeList.GetCurrentIndex();

	if (iIndex != -1) {
	char inBuff[TEXTLEN+20];

		RCodeList.GetString (inBuff, iIndex, sizeof(inBuff));
	
	long lActRCode = strtoul (inBuff, NULL, 10);

		if (lActRCode == lRCode)	// wenn nicht neu, austauschen
			RCodeList.DelString (iIndex);

		FillRkListBox (lRCode, true, (void *)&RCodeList);

	// neuen Eintrag wiederfinden und selektieren
		wsprintf (inBuff, "%08ld:", lRCode);

		RCodeList.ChangeCurrentIndex (-1);
		iIndex = RCodeList.FindString (inBuff);
		if (-1 != iIndex)
			RCodeList.ChangeCurrentIndex (iIndex);
	} else if (0 == RCodeList.GetCount()) {
		if (FillRkListBox (lRCode, true, (void *)&RCodeList))
			RCodeList.ChangeCurrentIndex (0);
	}
}

long NewRCodeDlg :: GetModRCode (void) 
{
long lRCode = -1L;
short iIndex = -1;
char inBuff[TEXTLEN+20];

	if (ModRCode.GetTextLen() > 0) {
		ModRCode.GetText (inBuff, sizeof(inBuff));
		lRCode = atol (inBuff);
		if (lRCode == 0) lRCode = -1;
	} else if ((iIndex = RCodeList.GetCurrentIndex()) != -1) {
		RCodeList.GetString (inBuff, iIndex, sizeof(inBuff));
		lRCode = atol (inBuff);
		if (lRCode == 0) lRCode = -1;
	}

return lRCode;
}

bool NewRCodeDlg :: AdjustOK (void)
{
	if (ModRCode.GetTextLen() > 0 || RCodeList.GetCurrentIndex() != -1) {
		OKButton.Enable();
		return true;
	} else {
		OKButton.Disable();
		return false;
	}
}

// Liste der Idents für Löschfenster ------------------------------------------
RCItem :: RCItem (long lRCode, char *pKT)
{
	m_Status = IDR_InValid;
	m_lRCode = lRCode;
	m_pKText = new char [strlen(pKT)+1];
	if (m_pKText) {
		strcpy (m_pKText, pKT);
		m_Status = IDR_Valid;
	}
}

RCItem :: ~RCItem (void) 
{
	DELETE_OBJ(m_pKText);
}


#pragma warning (disable: 4355)

RCList :: RCList (void)
	: CTree (GetLongKey, CmpLongKey),
	  locTab (*this)
{
	// nothing else to do
}

#pragma warning (default: 4355)

void RCList :: UserDelete (void *pObj)
{
#if defined(__GWXX__)
	((RCItem *)pObj) -> RCItem :: ~RCItem ();
#else
	((RCItem *)pObj) -> ~RCItem ();
#endif
}

// Ein Element der Liste als gelöscht markieren
void RCList :: MarkDeleted (long lRCode)
{
CTable t(*this);

	if (t.Find (&lRCode)) {
	RCItemLock l(t);

		if (l) l -> Status() = IDR_Deleted;
	}
}

bool RCList :: hasDeleted (void) 
{
CTable t(*this);

	for (t.First(); t.Valid(); t.Next()) {
	RCItemLock l(t);

		if (!l) continue;
		if (l -> Status() == IDR_Deleted)
			return true;
	}

return false;
}

// Konstruktor für Löschfenster -----------------------------------------------
extern "C" {

BOOL _XTENSN_EXPORT PASCAL FillRCodeList (long lRCode, BOOL, void *pData)
{
PBDDATA pbdData;
char KText[33];

	memset (&pbdData, '\0', sizeof(PBDDATA));

	pbdData.dwSize = sizeof(PBDDATA);
	pbdData.pbdTyp = 'r';
	pbdData.pbdCode = lRCode;
	pbdData.pbdKText = KText;
	pbdData.pbdKTextLen = sizeof(KText) -1;
	pbdData.pbdLTextLen = 0;
	DEX_GetPBDData (pbdData);

	KText[32] = '\0';		// sicherheitshalber ausnullen

	ContCreate (*(RCItemCreator *)pData, RCItem)(lRCode, pbdData.pbdKText);

return true;	// weitermachen
}

}	// extern "C"

#if defined(WIN32)

static DWORD s_dwHelpDelete[] = {
	IDOK,			IDH_DELRCODEDLG_OK,
	IDCANCEL,		IDH_DELRCODEDLG_CANCEL,
	IDT_NEWRKRCODE,		IDH_DELRCODEDLG_DELRKRCODES,
	IDL_DELRELLIST,		IDH_DELRCODEDLG_DELRKRCODES,
	IDB_DELRELUNUSED,	IDH_DELRCODEDLG_DELRKUNUSEDRKS,
	IDB_DELRCODES_SELALL,	IDH_DELRCODEDLG_DELRKSELALL,
	0,			0,		// EndeKennung
};

void DelRCodeDlg :: HelpRequest (HelpRequestEvt e)
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
#endif

#pragma warning (disable: 4355)

DelRCodeDlg :: DelRCodeDlg (pWindow pW, ResID res)
	     : DialogWindow (pW, res),
	       OKButton (this, IDOK),
#if !defined(WIN32)
	       RestoreButton (this, IDB_DELRELRESTORE),
	       HelpButton (this, IDB_DELRELHELP),
	       DeleteButton (this, IDB_DELRELDELETE),
#endif // !WIN32
	       RCodeList (this, IDL_DELRELLIST),
	       UnusedRCs (this, IDB_DELRELUNUSED)
{
// EierUhr anzeigen 
CEierUhr Wait (this);

// Variablen initialisieren
	m_pRCodes = new RCList ();
	if (m_pRCodes == NULL) 
		return;

#if !defined(WIN32)
// Controls initialisieren
	HelpButton.Disable();
	DeleteButton.Disable();
	RestoreButton.Disable();
#endif // !WIN32
	UnusedRCs.SetChecked (false);
	UnusedRCs.Disable();

// ListBox füllen
ENUMLONGKEY ELK;

	memset (&ELK, '\0', sizeof (ENUMLONGKEY));
	ELK.eKey = 'r';
	ELK.eFcn = (ENUMLONGKEYPROC)FillRCodeList;

	{
	RCItemCreator RCCr (RCodes());

		ELK.ePtr = (void *)&RCCr;
		DEX_EnumPBDData (ELK);
	}

	BuildList ();		// ListBox füllen
	RCodeList.ClearSelected();
}

#pragma warning (default: 4355)

DelRCodeDlg :: ~DelRCodeDlg (void)
{
	DELETE_OBJ(m_pRCodes);
}


void _XTENSN_EXPORT DelRCodeDlg :: ButtonClick (ControlEvt e)
{
	switch ((unsigned int)e.GetControlID()) {
	case IDOK:
#if defined(WIN32)
		EndDlg (DeleteRCodes());
#else
		EndDlg (RCodes().hasDeleted());
#endif
		break;

	case IDCANCEL:
		EndDlg();
		break;

	case IDB_DELRELRESTORE:
		RestoreRCodes();
		break;

	case IDB_DELRELHELP:
		break;

	case IDB_DELRELDELETE:	// als gelöscht markieren
		DeleteRCodes();
		break;

	case IDB_DELRELUNUSED:
		BuildList (UnusedRCs.isChecked());
		break;

	case IDB_DELRCODES_SELALL:
		{	// alle markieren
		CEierUhr Wait (this);
		short iCount = RCodeList.GetCount();
		
			RCodeList.ChangeSelected (Range (0, iCount-1));
#if !defined(WIN32)
			DeleteButton.Enable();
#else
			OKButton.Enable();
#endif // !WIN32
		}
		break;
	}
}

void _XTENSN_EXPORT DelRCodeDlg :: ListBoxSel (ControlEvt)
{
#if defined(WIN32)
	if (RCodeList.GetNoSelected())
		OKButton.Enable();
	else
		OKButton.Disable();
#else
	if (RCodeList.GetNoSelected())
		DeleteButton.Enable();
	else
		DeleteButton.Disable();
#endif
}


void DelRCodeDlg :: BuildList (bool unusedOnly)
{
// ListBox ausblenden und leeren
	RCodeList.Hide();
	RCodeList.Clear();

CTable t(RCodes().Tab());

	for (t.First(); t.Valid(); t.Next()) {
	RCItemLock l(t);

		if (!l) continue;

		if (l -> Status() == IDR_Deleted) continue;
		if (unusedOnly && DEX_isRCodeUsed (l -> FRCode())) continue;

	char outBuff[TEXTLEN+20];
	
		wsprintf (outBuff, "%08ld:%s", l -> FRCode(), l -> GetKurzText());

	int iIndex = RCodeList.AddString (outBuff);

		if (l -> Status() == IDR_Restored) {
			l -> Status() = IDR_Valid;
			RCodeList.ChangeSelected (iIndex);
		}
	}

// ListBox wieder anzeigen
	RCodeList.Show();
}


// alle markierten Einträge als gelöscht kennzeichnen -------------------------
bool DelRCodeDlg :: DeleteRCodes (void)
{
	if (RCodeList.GetNoSelected() == 0) return false;

int iIndex = RCodeList.GetFirstSelected();

	while (iIndex != -1) {
	char inBuff[TEXTLEN+20];

		RCodeList.GetString (inBuff, iIndex, sizeof(inBuff));
		RCodes().MarkDeleted (atol (inBuff));
		iIndex = RCodeList.GetNextSelected();
	}
#if !defined(WIN32)
	BuildList (UnusedRCs.isChecked());	// Liste neu füllen
	RestoreButton.Enable();
#endif // WIN32

return true;
}


void DelRCodeDlg :: RestoreRCodes (void)
{
#if !defined(WIN32)
CTable t(RCodes());

	for (t.First(); t.Valid(); t.Next()) {
	RCItemLock l(t);

		if (!l || l -> Status() != IDR_Deleted) continue;
		l -> Status() = IDR_Restored;
	}
	BuildList (UnusedRCs.isChecked());
	RestoreButton.Disable();
#endif
}



// Interfacefunktionen liefern nacheinader alle als gelöscht markierten Idents 
long DelRCodeDlg :: NextRCode (bool iFirst) 
{
// ersten/nächsten gelöschten Ident suchen
	if (iFirst) 
		RCodes().Tab().First();
	else
		RCodes().Tab().Next();

	for (/* bereits initialisiert */;
	     RCodes().Tab().Valid();
	     RCodes().Tab().Next())
	{
	RCItemLock l(RCodes().Tab());

		if (!l || l -> Status() != IDR_Deleted) continue;
		return l -> FRCode();
	}

return -1L;		// nichts gefunden
}
