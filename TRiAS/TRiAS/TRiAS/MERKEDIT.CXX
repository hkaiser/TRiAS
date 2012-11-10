// Merkmalseditierung fuer einzelne Objekte
// File: MERKEDIT.CXX

#include "triaspre.hxx"

#include "triasres.h"

#if !defined(WIN16)
#include <funcs03.h>
#include <undoguid.h>		// GUID
#include <iunredo.hxx>		// Interface
#include <dirisole.h>
#include "extmain3.hxx"
#endif // WIN16

#include "merkedit.hxx"

extern HelpDisplay *IrisHD;
extern ExtDirisWindow *CurrActDirisW;

const char ExistChar = '»';

// static ListObjektInfoDialog *pMEDlg;

// Konstruktor ----------------------------------------------------------------
#pragma warning (disable: 4355)

ListObjektInfoDialog :: ListObjektInfoDialog (
	pWindow pW, DatenBasisObjekt &rDBO, long ON, long ID, BOOL fSystem)
		      : DialogWindow (pW, MKEDIT),
			Merkmale (this, IDC_MKCODE),
			MWert (this, IDE_MKWERT),
			OKButton (this, IDOK),
			CancelButton (this, IDCANCEL),
			SaveButton (this, IDB_MKSAVE),
			DelButton (this, IDB_MKDELETE),
#if defined(WIN16)
			HelpButton (this, IDB_MKEHELP),
#endif // WIN16
			ObjSpec (this, IDT_OBJNAME),
			MName (this, IDT_MNAME),
			StandardName (this, IDB_STANDARDNAME),
			m_rDB(rDBO.DB()), 
			ML (&m_rDB, &rDBO.PbdDB(), ON, OBL_OLD, fSystem)
					// alle Merkmale dieses Objektes
{
// ObjektNummer merken
	_ON = ON;

// R/O-Mode merken
	_ROMode = DEX_GetROModeEx(HACTPROJECT);

// DialogBoxüberschrift setzen
char OutText[80];

	wsprintf (OutText, ResString (IDS_ATTRIBUTCAPTION, 50), ON);
	SetCaption (OutText);

// alle MerkmalsKodes dieser GeoDB lesen
	FillMerkmale (rDBO, ML);
//	pMEDlg = this;                          // Pointer auf dieses Fenster
	ML.Every (FillMerkmalsListe, this);	// ComboBox füllen

// Objektnamen setzen
	SetObjName (pW, ID);

// erstes Merkmal in DialogBox aktivieren
	Merkmale.ChangeCurrentIndex (0);
	ActivateMerkmal();

// StandardNamen deaktivieren
	StandardName.Disable();

// DB R/O eröffnet ?
	if (_ROMode) {
	// Modifizierungsmöglichkeiten sperren
		SaveButton.Disable();
		DelButton.Disable();
#if !defined(WIN16)
		MWert.SetRO (true);
#endif // WIN16
	}
}


#pragma warning (default: 4355)

// Destruktor -----------------------------------------------------------------
ListObjektInfoDialog :: ~ListObjektInfoDialog (void) 
{
//	pMEDlg = NULL;                          // Pointer wieder rücksetzen
}


// ObjektNamensCode aus ProfileDatei lesen und Objektnamen anzeigen -----------
void ListObjektInfoDialog :: SetObjName (pWindow, long ID) 
{
ProFile PF (CurrActDirisW -> DBO().DB().GetDBName());
char OutString[MAX_OKS_LEN];
	
	ClassFromIdent (ID, OutString, sizeof(OutString));

long ObjNameCode = PF.GetObjNameCode (OutString);
CTable t(ML);

	if (t.Find (&ObjNameCode)) {
	PBD_MerkmalLock l(t);

		if (l) {
		char *cptr = l -> GetMerkmalsText();

			if (cptr != NULL) {
				ObjSpec.SetText(cptr);
				DELETE_OBJ (cptr);
			}
		}
	}
}

// Ein Merkmal in die ComboBox des Dialoges einfügen -------------------------
int EXPORTTRIAS FillMerkmalsListe (void *pItem, void *pData) 
{
PBD_Merkmal *pTM = (PBD_Merkmal *)pItem;
ListObjektInfoDialog *pMEDlg = (ListObjektInfoDialog *)pData;

	if (pTM -> isA() == 'a') {      // Textmerkmal
	char OutText[KEYLENGTH+1];
	char ExistStr[2];

		ExistStr[0] = '\0';
		ExistStr[1] = '\0';
		if (((TextMerkmal *)pTM) -> hasTextMerkmal())
			ExistStr[0] = ExistChar;

		switch (pTM -> Status()) {
		case PBD_Data :: PBD_Modified:
		case PBD_Data :: PBD_Deleted:
			ExistStr[0] = ModifiedChar;
			break;

		case PBD_Data :: PBD_Invalid:
			return true;         // Fehler, trotzdem weitermachen

		case PBD_Data :: PBD_Unmodified:
			break;

		default:                // Fehler
			return false;
		}

	char *pKText = pTM -> GetKurzText();

		if (NULL == pKText || 0 == strlen (pKText)) {
		string strFmt = ExistStr;
		
			strFmt += ResString (IDM_MCODEFORMAT, 32);
		
			if (10 == DEX_GetMkBase()) 
				strFmt += "%ld";
			else
				strFmt += "%lx";

		PBD_Data::PBDStatus rgStatus = pTM -> Status();

			wsprintf (OutText, strFmt.c_str(), pTM -> GetCode());
			pTM -> SetKurzText (OutText);
			pTM -> Status() = rgStatus;		// vorherigen Staus wieder einstellen
		} else {
			if (*pKText == ExistChar || *pKText == ModifiedChar)
				pKText++;
			wsprintf (OutText, "%s%s", ExistStr, pKText);
		}
		pMEDlg -> Merkmale.AddString (OutText);		// in ComboBox einhängen
	}

return true;
}

#if defined(_FORCE_LEGACY_CODE)
// alle vorhandenen MerkmalsCodes dieser GeoDB lesen und zu ML ergänzen
ErrCode FillMerkmale (DatenBasisObjekt &rDBO, MerkmalsListe &ML) 
{
ErrCode EC;
GeoDB &rDB = rDBO.DB();
DB_ADDR dba(rDB.DBDesc());
CActDB ActDB (rDB);	// DB aktivieren

	{
	// Fehler WC_NOTFOUND ignorieren
	ErrInstall EI (WC_NOTFOUND);
	PBD_MerkmalCreator MC (ML);

	// ersten MerkmalsCode suchen
		EC = (ErrCode)z_keyfirst (&dba, MK);
		if (EC != EC_OKAY) {
		// Fehler aufgetreten
			if (EC == WC_NOTFOUND) 
				return EC_OKAY;         // nichts gefunden: OK
			return EC;                      // sonstiger Fehler
		}

	// für alle weiteren Merkmale
		do {
		long MKode;
		CTable t(ML);

		// MKode aus Schlüsseldatei lesen
			EC = (ErrCode)z_keyread (rDB.DBDesc(), &MKode);
			if (EC != EC_OKAY) break;
			if (!t.Find (&MKode)) {
			// Textmerkmal in MerkmalsListe einfügen
			TextMerkmal *pMK = new TextMerkmal(
						&rDBO.PbdDB(), MKode, NULL
					);

				if (pMK) {
					if (!ML.isSystem() && pMK -> isSystem()) {
					// nicht einspeichern
						delete pMK;
					} else
						MC.InsertPtr (pMK);
				} else {
					db_error (EC_NOMEMORY, RC_FillMerkmale);
					return EC_NOMEMORY;
				}

			// wieder auf GeoDB umschalten
				EC = (ErrCode)z_keyfind (&dba, MK, &MKode);
				if (EC != EC_OKAY)
					break;	// snh
			}

		// nächsten Schlüssel suchen
			EC = (ErrCode)z_keynext (&dba, MK);
		} while (EC == EC_OKAY);
	} // Fehlerbearbeitung wieder einstellen
	if (EC == WC_NOTFOUND) 
		EC = EC_OKAY;           // nichts mehr gefunden: OK

// Baum optimieren
	if (EC == EC_OKAY) 
		ML.Optimize();

return EC;
}
#endif // _FORCE_LEGACY_CODE

// Ein Merkmal in der gesamten DialogBox aktivieren
void ListObjektInfoDialog :: ActivateMerkmal (void) 
{
char InText[KEYLENGTH+1];
char *cptr;

	Merkmale.GetCurrentString (InText);
	strcpy (ActEntry, InText);              // lfden Eintrag merken
	if (*(cptr = InText) == ModifiedChar || *cptr == ExistChar) 
		cptr++;

CTable t(ML);
ResString resFmt (IDM_MCODEFORMAT, 32);

	for (t.First(); t.Valid(); t.Next()) {
	PBD_MerkmalLock l(t);
	char *pKText = l -> GetKurzText();
	char cbOutBuff[64];

		if (NULL == pKText || 0 == strlen (pKText)) {
		string strFmt = resFmt;
		
			if (10 == DEX_GetMkBase()) 
				strFmt += "%ld";
			else
				strFmt += "%lx";
			wsprintf (cbOutBuff, strFmt.c_str(), l -> GetCode());
			pKText = cbOutBuff;
		}

		if (*pKText == ModifiedChar || *pKText == ExistChar) 
			pKText++;

		if (l && !strcmp (cptr, pKText)) {
		// Merkmal gefunden
		TextMerkmal *pTM = (TextMerkmal *)((PBD_Merkmal *)l);
		char *cptr1 = pTM -> GetMerkmalsText();

			if (cptr1 != NULL) {
			// MerkmalsText vorhanden: anzeigen
				MWert.SetText (cptr1);
				DELETE_OBJ (cptr1);   // GetMerkmalsText liefert Kopie
			} else if (MWert.GetTextLen() != 0)
			// sonst Anzeige löschen
				MWert.SetText ("");

		char *pLText = pTM -> GetLangText();

			if (NULL == pLText || 0 == strlen(pLText)) 
				pLText = pKText;

			MName.SetText (pLText);
			if (!_ROMode && pTM -> Status() != PBD_Data :: PBD_Deleted)
				DelButton.Enable();
			else 
				DelButton.Disable();
#if !defined(WIN16)
		// Schreibschutz ?
			if (_ROMode || pTM -> isReadOnly()) {
				DelButton.Disable();
				SaveButton.Disable();
				MWert.SetRO (true);
			} else {
				DelButton.Enable();
				SaveButton.Enable();
				MWert.SetRO (false);
			}
#endif
			break;          // Merkmal gefunden, also fertig
		}
	}
}

// Eventhandler --------------------------------------------------------------
void ListObjektInfoDialog :: ButtonClick (ControlEvt e) 
{
	switch ((unsigned int)e.GetControlID()) {
	case IDCANCEL:
		EndDlg();               // alles vergessen
		break;

	case IDOK:
		AskToSaveReply();       // evtl. noch ausstehenden Eintrag schreiben
		CleanUpEntries();       // DB aktualisieren
		EndDlg(1);
		break;

	case IDB_MKSAVE:
		SaveEntry ();           // Eintrag modifizieren
		ReBuildEntries ();      // Liste neu aufbauen
		break;

	case IDB_MKDELETE:
		DeleteEntry ();         // Eintrag löschen
		ReBuildEntries ();      // Liste neu aufbauen
		break;

	case IDB_STANDARDNAME:          // z.Zt. passiviert
		break;

	case IDB_MKEHELP:
		IrisHD -> Show (IDB_MKEHELP);
		break;

	default:
		break;
	}
}

void ListObjektInfoDialog :: ListBoxSel (ControlEvt) 
{
// wenn kein neuer Wert ausgewählt wurde, dann wieder raus
char InText[KEYLENGTH+1];

	Merkmale.GetCurrentString (InText);
	if (!strcmp (ActEntry, InText))
		return;

// fragen, ob Merkmalstext verändert wurde, ggf. speichern
	AskToSaveReply();

// gewünschtes neues Merkmal anzeigen
	ActivateMerkmal();
}

// fragt ab, ob der aktuelle Satz gespeichert werden soll --------------------
BOOL ListObjektInfoDialog :: AskToSaveReply (void) 
{
	if (MWert.isModified()) {
	StdMessBoxReply rgReply = VMessageBox (this, IDS_SAVEMERKMALSWERTCAP,
			QuestionMarkIcon|YesNoButtons, IDS_SAVEMERKMALSWERT);

		switch (rgReply) {
		case YesReply:
			SaveEntry ();
			return true;

		case NoReply:
			return false;
		}
	}

return false;
}

// Aktuellen Eintrag in MerkmalsListe abspeichern -----------------------------
ErrCode ListObjektInfoDialog :: SaveEntry (void) 
{
// 1. vorhandenen Eintrag aus MerkmalsListe herauslöschen
char InText[KEYLENGTH+1];
char *cptr;

	strcpy (InText, ActEntry);
	if (*(cptr = InText) == ModifiedChar || *cptr == ExistChar)
		cptr++;

CTable t(ML);
long MKode = 0L;
bool toDelete = false;

	// alten Eintrag finden und löschen
	for (t.First(); t.Valid(); t.Next()) {
		{
		PBD_MerkmalLock l(t);

			if (!l) continue;

		char *pKText = l -> GetKurzText();

			if (*pKText == ModifiedChar || *pKText == ExistChar)
				pKText++;

			if (!strcmp (cptr, pKText)) {
			// Merkmal in Liste gefunden
				toDelete = true;
				MKode = l -> GetCode(); // MKode holen
			}
		}
		if (toDelete) {
		// Eintrag aus Baum löschen
			t.Delete();
			break;
		}
	}
	{       // neuen Eintrag einfügen
	PBD_MerkmalCreator MC(ML);
	PBD_Merkmal *pMK;
	short TextLen = MWert.GetTextLen();
	ExtDirisWindow *pIW = CurrActDirisW;

		if (TextLen > 0) {
		char *InBuff = new char [TextLen+2];

			if (InBuff == NULL) {
				db_error (EC_NOMEMORY, RC_LOIDlgSaveEntry);
				return EC_NOMEMORY;
			}
			MWert.GetText (InBuff, TextLen+1);
#if defined(MSWIND)
//			AnsiToOem (InBuff, InBuff);
#endif
			pMK = ContCreate (MC, TextMerkmal)(&pIW -> DBO().PbdDB(), MKode, InBuff);
			if (pMK == NULL) {
				db_error (EC_NOMEMORY, RC_LOIDlgSaveEntry);
				return EC_NOMEMORY;
			}
			pMK -> Status() = PBD_Data :: PBD_Modified;
			DELETE_OBJ (InBuff);
		} else {
		// Kein Text mehr da: gelöschter Satz
			pMK = ContCreate (MC, TextMerkmal)(&pIW -> DBO().PbdDB(), MKode, NULL);
			if (pMK == NULL) {
				db_error (EC_NOMEMORY, RC_LOIDlgSaveEntry);
				return EC_NOMEMORY;
			}
			pMK -> Status() = PBD_Data :: PBD_Deleted;
		}
	}

// EditControl: Touch
	MWert.SetModified (false);

return EC_OKAY;
}

// Liste neu aufbauen ---------------------------------------------------------
void ListObjektInfoDialog :: ReBuildEntries (void) 
{
// selektierten Eintrag merken
int iSelectedItem = Merkmale.GetCurrentIndex();
char cbBuffer[_MAX_PATH];
char *pCptr = NULL;

	if (iSelectedItem >= 0) {
		Merkmale.GetString (cbBuffer, iSelectedItem, _MAX_PATH);
		pCptr = cbBuffer;
		if (cbBuffer[0] == ExistChar || cbBuffer[0] == ModifiedChar)
			pCptr++;
	}

// alle Einträge löschen
	Merkmale.Hide();

int iItemCount = Merkmale.GetCount();

	for (int i = 0; i < iItemCount; i++)
		Merkmale.DelString(0);

// Einträge neu generieren
	ML.Every (FillMerkmalsListe, this);

int iIndex = -1;

	if (pCptr) {	// alten Eintrag wieder einstellen
		iIndex = Merkmale.FindString (pCptr);
		if (iIndex >= 0) goto labelOK;
	
	// wenn ein Zeichen dazugekommen ist, dann String verschieben
		if (cbBuffer == pCptr)
			memmove (cbBuffer+1, cbBuffer, strlen(cbBuffer)+1);
		else
			--pCptr;

	// ohne "»" und "*" nicht gefunden
		*pCptr = ExistChar;
		iIndex = Merkmale.FindString (pCptr);
		if (iIndex >= 0) goto labelOK;

		*pCptr = ModifiedChar;
		iIndex = Merkmale.FindString (pCptr);
	}

labelOK:
	Merkmale.ChangeCurrentIndex (iIndex);
	Merkmale.SetFocus();
	Merkmale.Show();        
}

// Eintrag löschen (Merkmal für dieses Objekt löschen) ------------------------
ErrCode ListObjektInfoDialog :: DeleteEntry (void) 
{
	MWert.SetText ("");     // EditFenster löschen

return SaveEntry ();            // diesen Zustand speichern
}

// Zurückspeichern in die DB --------------------------------------------------
ErrCode ListObjektInfoDialog :: CleanUpEntries (void) 
{
#if !defined(WIN16)
ResString resUndo (IDS_UNDOEDITFEATURES, 64);
char cbBuffer[64];

	wsprintf (cbBuffer, resUndo.Addr(), _ON);
	DEX_BeginUndoLevel (cbBuffer);
	ML.Every (WriteBackChanges, this);
	DEX_EndUndoLevel();
#else
	ML.Every (WriteBackChanges, this);
#endif

return EC_OKAY;
}

int EXPORTTRIAS WriteBackChanges (void *pItem, void *pData) 
{
PBD_Merkmal *pTM = (PBD_Merkmal *)pItem;
ListObjektInfoDialog *pMEDlg = (ListObjektInfoDialog *)pData;

	if (pTM -> isA() == 'a') {      // Textmerkmal
		switch (pTM -> Status()) {
		case PBD_Data :: PBD_Modified:  // löschen und neu schreiben
			{
#if !defined(WIN16)
			LPTSTR pText = pTM -> GetMerkmalsText();
			LPUNDOREDOOBJECTFEATURE pIUndo = NULL;
			HRESULT hr = UndoCreateInstance (IID_IUndoRedoObjectFeature,
							 (LPVOID *)&pIUndo);

				if (SUCCEEDED(hr))
					hr = pIUndo -> Init (pMEDlg -> _ON, pTM -> GetCode(), pText, NULL); 

				DELETE_OBJ (pText);
				pTM -> SaveInDB (pMEDlg -> _ON, OBL_OLD);

				if (hr == NOERROR) 
					DEX_AddUndoRedo (pIUndo);
				if (pIUndo) pIUndo -> Release();
#else
				pTM -> SaveInDB (pMEDlg -> _ON, OBL);
#endif // WIN16
			}
			break;

		case PBD_Data :: PBD_Deleted:   // Merkmal löschen
			{
#if !defined(WIN16)
			LPUNDOREDOOBJECTFEATURE pIUndo = NULL;
			HRESULT hr = UndoCreateInstance (IID_IUndoRedoObjectFeature,
							 (LPVOID *)&pIUndo);
//			HRESULT hr = CoCreateInstance (CLSID_UndoRedoObject, NULL,
//					CLSCTX_INPROC_SERVER, IID_IUndoRedoObjectFeature,
//					(LPVOID *)&pIUndo);

				if (SUCCEEDED(hr))
					hr = pIUndo -> Init (pMEDlg -> _ON, pTM -> GetCode(), "", NULL); 

				pTM -> DeleteInDB (pMEDlg -> _ON, OBL_OLD);

				if (hr == NOERROR) 
					DEX_AddUndoRedo (pIUndo);
				if (pIUndo) pIUndo -> Release();
#else
				pTM -> DeleteInDB (pMEDlg -> _ON, OBL);
#endif // WIN16
			}
			break;

		case PBD_Data :: PBD_Unmodified:
			break;		// weitermachen

		case PBD_Data :: PBD_Invalid:
		default:                // Fehler
			break;		// aber weitermachen
		}
	}

return true;
}

#if !defined(WIN16)
// MultiLineEdit, welches ReadOnly sein kann ----------------------------------
CEditCondRO :: CEditCondRO (pDialogWindow p, ResID r)
	     : ControlWindow (new MultiLineEdit (p, r))
{
	m_fRO = false;
}

CEditCondRO :: ~CEditCondRO (void)
{
	if (GetControl())
		delete (MultiLineEdit *)GetControl();
}

void CEditCondRO :: KeyDown (KeyEvt e)
{
	if (!m_fRO) {	// wenn nicht RO, dann bearbeiten
		Default ((Event &)e);
		return;
	}
	MessageBeep (MB_ICONHAND);
}

void CEditCondRO :: GetText (char *pBuff, uint uiLen)
{
	if (GetControl())
        	((MultiLineEdit *)GetControl()) -> GetText (pBuff, uiLen);
}

void CEditCondRO :: SetText (const char *pcBuff)
{
	if (GetControl())
        	((MultiLineEdit *)GetControl()) -> SetText (pcBuff);
}

void CEditCondRO :: SetTextLimit (uint nchars)
{
	if (GetControl())
        	((MultiLineEdit *)GetControl()) -> SetTextLimit (nchars);
}

int CEditCondRO :: GetTextLen (void)
{
	if (GetControl())
	        return ((MultiLineEdit *)GetControl()) -> GetTextLen ();

return 0;
}

bool CEditCondRO :: isModified (void)
{
	if (GetControl())
	        return ((MultiLineEdit *)GetControl()) -> isModified();

return false;
}

void CEditCondRO :: SetModified (bool fModified)
{
	if (GetControl() && !m_fRO)
        	((MultiLineEdit *)GetControl()) -> SetModified (fModified);
}

bool CEditCondRO :: FInit (void)
{
	if (GetControl())
	        return ((MultiLineEdit *)GetControl()) -> FInit();

return false;
}

#endif // WIN16
