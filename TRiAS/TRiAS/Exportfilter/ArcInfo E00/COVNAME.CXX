/*
File: COVNAME.CXX
Prüfen des zu jedem Identifikator gehörenden Covernamens.

erarbeitet: J. Benkenstein				  Begonnen am 5. Mai 1993
											Stand vom 16. Dez. 1993
*/

#include "stdafx.h"               
/*XX*/ #include "TRiASArcImpl.h"

extern "C" {
	#include <string.h>		 	// strchr ()
}

#include <attribs.hxx>		  	// VisInfo ...
#include <impexp.hxx>		   	// IdentDescription
/*XX*/	#undef WIN32
//XX	#include <waitcur.hxx>			// CWaitCursor
/*XX*/	#include <waitcur.hpp>
/*XX*/	#define WIN32

//XX #include "triasarc.hr"		   	// Resource-IDs
#include "triasarc.hxx"		 	// FileNameSize, CheckName ()
#include "ident.hxx"			// ExtIdentDescriptionTree
#include "nameedit.hxx"		 	// NameEdit
#include "covname.hxx"		  	// zugeh. Header-File

//  Konstanten
const short IdOffset = 3;	   	// Position des IDs im String
const int Sep = ':';			// String-Separator

//  externe Variablen
extern ResourceFile *pRF;
extern ExtIdentDescriptionTree *pIDT;

#pragma warning (disable:4355)

//  CoverName -------------------------------------------------------------
CoverNameDialog :: CoverNameDialog (pWindow pParent)
: DialogWindow (pParent, ResID (IDD_COVERNAME, pRF)),
_CoverNameList (this, ResID (IDL_COVERNAME, pRF)),
_CoverNameEdit (this, ResID (IDE_COVERNAME, pRF)) {
//  prüfe Parameter
	if (!pIDT || !pRF) {
		EndDlg (EC_SYSERROR);
		return;
	}                       
	
	CWaitCursor wc;			// SandUhr einschalten
	

	_CoverNameEdit.SetTextLimit (FileNameSize);  // Filenamenlänge einst.

	ErrCode EC = EC_OKAY;

//  einzigartige CoverNamen erzeugen
	if ((EC = UniqueCoverNames ()) != EC_OKAY) {
		EndDlg (EC);
		return;
	}

//  Coverliste ausgeben
	if ((EC = FillNameList (False)) != EC_OKAY) {
		EndDlg (EC);
		return;
	}
}

#pragma warning (default:4355)

//  akt. in CoverNameListe sel. Covernamen in Edit-Feld setzen
void CoverNameDialog :: SetCoverName (void) {
	char Buffer [80] = "";
	_CoverNameList.GetCurrentString (Buffer);
	if (!Buffer [0])  { // wenn keinen gültigen Text gefunden
		EndDlg (EC_SYSERROR);
		return;
	}
                                   
    ulong Id = 0;
	if (FAILED(IdentFromClassX (hDatasource, Buffer + IdOffset, &Id, false))) {
		EndDlg (EC_SYSERROR);
		return;
	}
	pchar pFileName = pIDT -> GetCoverName (Id, GetTyp (Buffer));
	if (!pFileName) {
		EndDlg (EC_SYSERROR);
		return;
	}

	_CoverNameEdit.SetText (pFileName);
	DELETE_VEC (pFileName);
}

//  Ein Eintrag in CoverNameListe wurde selektiert.
void EXPORTFLT CoverNameDialog :: ListBoxSel (ControlEvt CE) {
	if ((uint) CE.GetControlID () == IDL_COVERNAME)
		SetCoverName ();
}

//  Ein PushBotton wurde betätigt.
void EXPORTFLT CoverNameDialog :: ButtonClick (ControlEvt CE) {
	pchar pNewCoverName = NULL;
	ErrCode EC = EC_OKAY;
	switch ((uint) CE.GetControlID ()) {
		case IDB_HELP:
		break;			  // noch kein Text definiert
		case IDB_ABBRUCH:
			EndDlg (EC_OKAY);
		break;
		case IDB_OK: {
			if (CheckAllNames ())  // wenn alle Namen OK
				EndDlg (EC_OKAY);
		}
		break;
		case IDB_STORE: {
			if (! _CoverNameEdit.isModified ()) // Aktion nur, wenn  Eintrag
				break;						  // verändert wurde

		//  Covernamen prüfen
			char Buffer [80] = "";
			_CoverNameEdit.GetText (Buffer, sizeof (Buffer));
			pchar pNewCoverName = CheckName (Buffer, FileNameSize, True);
			if (!pNewCoverName) {
				OutputOpenError (pNewCoverName);
				break;
			}

			_CoverNameList.GetCurrentString (Buffer);
            ulong Id = 0;
			if (FAILED(IdentFromClassX (hDatasource, Buffer + IdOffset, &Id, false)) || (Id <= 0))
				break;

			char Typ = GetTyp (Buffer);

			if ((pIDT -> OtherCoverName (Id, pNewCoverName, Typ))
				 && !(OutputOverwrite (pNewCoverName)))  // nicht überschr.
				break;

		//  Datei-Öffnen-Test
			OFSTRUCT of;
			int fh;
			if ((fh = OpenFile (pNewCoverName, &of, OF_CREATE | OF_WRITE)) < 0) {
				OutputOpenError (pNewCoverName);
				break;
			}
			_lclose (fh);
			remove (pNewCoverName);

			if ((EC = pIDT -> SetCoverName (Id, pNewCoverName, Typ)) != EC_OKAY)
				break;

		//  neuen Text setzen
			_CoverNameEdit.SetText (pNewCoverName);

			short ListIndex = _CoverNameList.GetCurrentIndex () + 1;
		//  ListBox neu füllen
			EC = FillNameList (True);

		//  setze akt. Index
			_CoverNameList.ChangeCurrentIndex (min (ListIndex,
											_CoverNameList.GetCount () - 1));
			SetCoverName ();
		}
		break;
		default:
		break;
	}

//  Speicher freigeben
	DELETE_VEC (pNewCoverName);
	if (EC != EC_OKAY)
		EndDlg (EC);
}

//  Fehlermeldung für Fehler beim Datei-Öffnen generieren
void CoverNameDialog :: OutputOpenError (pchar pFileName) {
	ResString Text (ResID (IDS_OPERRTEXT, pRF), 60);
	char Buffer [80] = "";
	wsprintf (Buffer, Text.Addr (), pFileName);
	Text = ResString (ResID (IDS_ERROR, pRF), 20);
	MessBox MB (Text.Addr (), Buffer, this);
	MB.SetType (Hand);
	MB.Show ();
}

//  Dateiname überschreiben
Bool CoverNameDialog :: OutputOverwrite (pchar pFileName) {
	ResString Caption (ResID (IDS_STORECAPT, pRF), 20);
	ResString TextFormat (ResID (IDS_STOREFORMAT, pRF), 40);
	char Buffer [60] = "";
	wsprintf (Buffer, TextFormat.Addr (), pFileName);
	MessBox MB (Caption.Addr (), Buffer, this);
	MB.SetType (QuestionMarkIcon | OkayCancelButtons);
	switch (MB.Show ()) {
		case OkayReply:
			return True;
		case CancelReply:
			return False;
	}
	return False;
}

//  ListBox mit Identfikatoren und Kurztexten füllen
ErrCode CoverNameDialog :: FillNameList (Bool DelOld) {
	_CoverNameList.Hide ();

//  alte Einträge ggf. vorher löschen
	if (DelOld) {
		short MaxCount = _CoverNameList.GetCount ();
		for (short i = 0; i < MaxCount; i++) {
			if (!_CoverNameList.DelString (0))
				break;
		}
	}

//  Listbox mit neuen Einträgen füllen
	char Buffer [80] = "";
	ResString OkName (ResID (IDS_OKNAME, pRF), 3);
	ResString NotOkName (ResID (IDS_NOTOKNAME, pRF), 3);

	CTable Tb (*pIDT);  // Covernamen in ListBox ausgeben
	for (Tb.First (); Tb.Valid (); Tb.Next ()) {
		ExtIdentDescriptionLock pIDD (Tb);
		if (!pIDD)
			return EC_LOCKERROR;

		pchar pCoverName = pIDD -> GetCoverName ();
		pchar pExist = pIDT -> OtherCoverName (pIDD -> ID (),
				pCoverName, pIDD -> IntTyp ()) ? (pchar) NotOkName.Addr () :
												 (pchar) OkName.Addr ();

	//  Text für Listbox zusammenstellen
		ResString IdText (ResID (IDS_IDTEXT, pRF), 5);
		char tBuffer [30] = "";
		if (FAILED(ClassFromIdentX (pIDD -> ID (), tBuffer, sizeof (tBuffer))))
		{
			DELETE_VEC (pCoverName);
			continue;
		}
		wsprintf (Buffer, "%s%s%s%c%c%c%s", pExist, IdText.Addr (), tBuffer, Sep, pIDD -> IntTyp (), Sep, pCoverName);		
		DELETE_VEC (pCoverName);

		OemToAnsi (Buffer, Buffer);
		if (_CoverNameList.AddString (Buffer) == -1)
			return EC_NOMEMORY;
	}

	_CoverNameList.Show ();

	return EC_OKAY;
}

//  prüfe, ob alle gewählten Namen einzigartig, gebe Fehlermeldung aus,
//  wenn wenigsten ein Name doppelt auftritt.
//  True, wenn alle Namen ok, sonst False
Bool CoverNameDialog :: CheckAllNames (BOOL bOutputError) {
	short Errors = 0;
	CTable Tb (*pIDT);
	for (Tb.First (); Tb.Valid (); Tb.Next ()) {
		ExtIdentDescriptionLock pIDD (Tb);
		if (!pIDD)
			return False;

		pchar pCoverName = pIDD -> GetCoverName ();
		if (pIDT -> OtherCoverName (pIDD -> ID (), pCoverName,
			pIDD -> IntTyp ()))
			Errors++;
		DELETE_VEC (pCoverName);
	}

//  ggf. Fehlermeldung ausgeben
	if (Errors) 
	{
		if (bOutputError)
		{
			ResString Text (ResID (IDS_CNAMEEXIST, pRF), 60);
			char Buffer [80] = "";
			wsprintf (Buffer, Text.Addr (), Errors);
			Text = ResString (ResID (IDS_ERROR, pRF), 20);
			MessBox MB (Text.Addr (), Buffer, this);
			MB.SetType (OkayButton | HandIcon);
			MB.Show ();
		}
		return False;
	}

	return True;
}

Bool EXPORTFLT CoverNameDialog :: QueryClose (Event) {
	return True;
}

// internen Typ aus ID-String lesen
char CoverNameDialog :: GetTyp (pchar pBuffer) {
	char Ch = 'U';	  // unbekannter Typ

//  prüfe Parameter
	if (!pBuffer || !*pBuffer)
		return Ch;

	pchar pFound = strchr (pBuffer, Sep);	   // 1. Separator
	if (pFound != NULL)
		return *(++pFound);
	else
		return Ch;		  // nicht gefunden
}

//  unique CoverNames erzeugen
ErrCode CoverNameDialog :: UniqueCoverNames (void) {
//  prüfe Parameter
	if (!pIDT)
		return EC_SYSERROR;

	CoverNamesTree CNT;		 // Baum für CoverNamen anlegen

//  alle CoverNamen im Namensbaum ablegen
	ErrCode EC = EC_OKAY;
	pchar pCoverName = NULL;
	CTable Tb (*pIDT);
	for (Tb.First (); Tb.Valid (); Tb.Next ()) {
		ExtIdentDescriptionLock pID (Tb);
		if (!pID)
			return EC_LOCKERROR;

		pCoverName = pID -> GetCoverName ();	// aktuellen CoverNamen lesen
		if (!pCoverName || !*pCoverName)
			return EC_SYSERROR;
		EC = CNT.AddName (pCoverName, pID -> ID (), pID -> IntTyp ());
		DELETE_VEC (pCoverName);
		if (EC != EC_OKAY)
			return EC;
	}

//  neuen Namen übernehmen
	CTable TbC (CNT);
	for (TbC.First (); TbC.Valid (); TbC.Next ()) {
		CoverNameLock pCN (TbC);
		if (!pCN)
			return EC_LOCKERROR;

		if ((EC = pIDT -> SetCoverName (pCN -> ID (), pCN -> Name (),
										pCN -> Typ ())) != EC_OKAY)
			return EC;
	}

	return EC_OKAY;
}

//  CoverName --------------------------------------------------------------
CoverName :: CoverName (long ID, pchar pCoverName, char Typ) {
	_EC = EC_OKAY;
	_pName = NULL;
	_Id = ID;
	_Typ = Typ;

	_pName = new char [lstrlen (pCoverName) + 1];
	if (_pName == NULL)
		_EC = EC_NOMEMORY;
	else
		lstrcpy (_pName, pCoverName);
}

CoverName :: ~ CoverName (void) {
	DELETE_VEC (_pName);
}

//  key function
void *GetCoverName (void *pObj) {
	return (((CoverName *) pObj) -> Name ());
}

// CoverNamesTree ----------------------------------------------------------
CoverNamesTree :: CoverNamesTree (void)
				: CTree (GetCoverName) {
	_NotUnique = 0;
}

void EXPORTFLT CoverNamesTree :: UserDelete (void *pObj) {
	((CoverName *) pObj) -> ~CoverName ();
}

CoverNamesTree :: ~ CoverNamesTree (void) {
	EveryDelete ();
}

// neuer Eintrag in Baum: unique Namen erzeugen
//	  - 1. Typ anhängen
//	  - 2. Nummer anhängen
ErrCode CoverNamesTree :: AddName (pchar pCoverName, long ID, char Typ) {
//  prüfe Parameter
	if (!pCoverName || !*pCoverName)
		return EC_SYSERROR;

//  Namen suchen
	CTable Tb (*this);
	pchar pNewName = NULL;
	if (Tb.Find (pCoverName)) {	 // wenn gefunden

	//  zuerst Typ anhängen
		char Buffer [10] = "_";
		Buffer [1] = Typ;
		pNewName = ConcatNames (pCoverName, Buffer);
		if (pNewName == NULL)
			return EC_SYSERROR;

	//  neuer Name OK ?
		if (Tb.Find (pNewName)) {	   // auch schon vergeben
			DELETE_VEC (pNewName);		  // alten (neuen) Namen löschen
			itoa (++_NotUnique, Buffer + 1, 10); // Zahl kopieren
			pNewName = ConcatNames (pCoverName, Buffer);
			if (pNewName == NULL)
				return EC_SYSERROR;
		}
	}

//  Namen u.a. Infos speichern
	CoverNameCreator CN_Cr (*this);
//XX	CoverName *pCN = Create (CN_Cr, CoverName) (ID, pNewName ? pNewName :
//XX												pCoverName, Typ);

/*XX*/	CoverName *pCN = ContCreate (CN_Cr, CoverName) (ID, pNewName ? pNewName : pCoverName, Typ);

	DELETE_VEC (pNewName);
	if (pCN)
		return pCN -> OpFlag ();
	else
		return EC_NOMEMORY;
}

// Zeiger auf neuen Namen ist explizit freizugeben
pchar CoverNamesTree :: ConcatNames (pchar pOldName, pchar pExt) {
//  prüfe Parameter
	if (!pOldName || !pExt)
		return NULL;

//  max. Länge des neuen Namens ist "FileNameSize"
	pchar pNewName = new char [FileNameSize + 1];
	if (pNewName == NULL)
		return NULL;

	short MaxLen = FileNameSize - lstrlen (pExt);
	lstrcpyn (pNewName, pOldName, min (MaxLen, lstrlen (pOldName)) + 1);
	return lstrcat (pNewName, pExt);
}
