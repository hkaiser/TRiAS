/*
File: MERKNAME.HXX
Prüfen des zu jedem Merkmal gehörenden Textes

erarbeitet : J. Benkenstein				 Begonnen am 5. Mai 1993
*/
                                   
#include "stdafx.h"               
/*XX*/ #include "TRiASArcImpl.h"

/*XX*/	#undef WIN32
//XX	#include <waitcur.hxx>			// CWaitCursor
/*XX*/	#include <waitcur.hpp>
/*XX*/	#define WIN32
#include <attribs.hxx>		 // VisInfo ...
#include <impexp.hxx>		 // MerkmalDescription
#include <string.h>			 // strchr ()

//XX#include "triasarc.hr"		 // Resource-IDs
#include "triasarc.hxx"		 // FieldNameSize, CheckName ()
#include "merkmdes.hxx"		 // ExtMerkmalDescriptionTree
#include "nameedit.hxx"		 // NameEdit
#include "merkname.hxx"		 // zugeh. Header-File

//  Konstanten
const short MKOffset = 3;

//  externe Variablen
extern ResourceFile *pRF;
extern ExtMerkmalDescriptionTree *pMDT;
/*XX*/	extern long MkBase;

#pragma warning (disable:4355)

//  MerkmalName -------------------------------------------------------------
MerkmalNameDialog :: MerkmalNameDialog (pWindow pParent)
: DialogWindow (pParent, ResID (IDD_MERKMALNAME, pRF)),
_MerkmalNameList (this, ResID (IDL_MERKMALNAME, pRF)),
_MerkmalNameEdit (this, ResID (IDE_MERKMALNAME, pRF)) {
//  prüfe Parameter
	if (!pMDT || !pRF) 
	{
		EndDlg (EC_SYSERROR);
		return;
	}                         
	
	CWaitCursor wc;				// Sanduhr einschalten	

	_MerkmalNameEdit.SetTextLimit (FieldNameSize);

	ErrCode EC = EC_OKAY;
	
//	einzigartige Merkmalsnamen erzeugen
	if ((EC = CreateUniqueNames ()) != EC_OKAY) 
	{
	    EndDlg (EC);
		return;
	}
	                                                    
// 	Merkmale in ListBox ausgeben	                                                    
	if ((EC = FillNameList (False)) != EC_OKAY) 
	{		
		EndDlg (EC);
		return;
	}
}

#pragma warning (default:4355)

//  akt. in MerkmalNameListe sel. Merkmalnamen in Edit-Feld setzen
void MerkmalNameDialog :: SetMerkmalName (void) 
{
	char Buffer [80] = "";
	_MerkmalNameList.GetCurrentString (Buffer);
	if (!Buffer [0])  // wenn keinen gültigen Text gefunden
	{
		EndDlg (EC_SYSERROR);
		return;
	}
              
//XX    long MK = strtoul (Buffer + MKOffset, NULL, DEX_GetMkBase ()); // Kode bilden
    long MK = strtoul (Buffer + MKOffset, NULL, MkBase); // Kode bilden
	pchar pMerkmal = pMDT -> GetMerkmalName (MK);
	if (!pMerkmal) 
	{
		EndDlg (EC_SYSERROR);
		return;
	}

	_MerkmalNameEdit.SetText (pMerkmal);
	DELETE_VEC (pMerkmal);
}

//  Ein Eintrag in MerkmalsNamensListe wurde selektiert.
void EXPORTFLT MerkmalNameDialog :: ListBoxSel (ControlEvt CE) {
	if ((uint) CE.GetControlID () == IDL_MERKMALNAME)
		SetMerkmalName ();
}

//  Ein PushBotton wurde betätigt.
void EXPORTFLT MerkmalNameDialog :: ButtonClick (ControlEvt CE) {
	pchar pNewMerkmalName = NULL;
	ErrCode EC = EC_OKAY;
	switch ((uint) CE.GetControlID ()) {
		case IDB_MERM_HELP:
		break;			  // noch kein Text definiert
		case IDB_ABBRUCHM:
			EndDlg (EC_OKAY);
		break;
		case IDB_OKM: {
			if (CheckAllNames ())  // wenn alle Namen OK
				EndDlg (EC_OKAY);
		}
		break;
		case IDB_STOREM: {
			if (! _MerkmalNameEdit.isModified ()) // Aktion nur, wenn  Eintrag
				break;							// verändert wurde

		//  Merkmalnamen prüfen
			char Buffer [80] = "";
			_MerkmalNameEdit.GetText (Buffer, sizeof (Buffer));
			pchar pNewMerkmalName = CheckName (Buffer, FieldNameSize, True);
			if (!pNewMerkmalName) {
				OutputNoName ();
				break;
			}

			_MerkmalNameList.GetCurrentString (Buffer);
//XX            long MKode = strtoul (Buffer + MKOffset, NULL, DEX_GetMkBase ());
            long MKode = strtoul (Buffer + MKOffset, NULL, MkBase);
			if (!MKode)
				break;

			if ((pMDT -> OtherMerkmalName (MKode, pNewMerkmalName))
				 && !(OutputOverwrite (pNewMerkmalName))) // nicht überschr.
				 break;

			if (pMDT -> SetMerkmalName (MKode, pNewMerkmalName) != EC_OKAY) {
				EC = EC_SYSERROR;
				break;
			}
			_MerkmalNameEdit.SetText (pNewMerkmalName);

			short ListIndex = _MerkmalNameList.GetCurrentIndex () + 1;
		//  ListBox neu füllen
			EC = FillNameList (True);

		//  setze akt. Index
			_MerkmalNameList.ChangeCurrentIndex (min (ListIndex,
										   _MerkmalNameList.GetCount () - 1));
			SetMerkmalName ();
		}
		break;
		default:
		break;
	}

//  Speicher freigeben
	DELETE_VEC (pNewMerkmalName);
	if (EC != EC_OKAY)
		EndDlg (EC);
}

//  Fehlermeldung für ungültigen Namen
void MerkmalNameDialog :: OutputNoName (void) {
	ResString Text (ResID (IDS_NOMERKMALNAME, pRF), 60);
	ResString Caption (ResID (IDS_ERROR, pRF), 20);
	MessBox MB (Caption.Addr (), Text.Addr (), this);
	MB.SetType (Hand);
	MB.Show ();
}

//  Merkmalsnamen überschreiben
Bool MerkmalNameDialog :: OutputOverwrite (pchar pName) {
	ResString Caption (ResID (IDS_STORECAPT, pRF), 20);
	ResString TextFormat (ResID (IDS_MSTOREFORMAT, pRF), 40);
	char Buffer [60] = "";
	wsprintf (Buffer, TextFormat.Addr (), pName);
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
ErrCode MerkmalNameDialog :: FillNameList (Bool DelOld) {
	_MerkmalNameList.Hide ();

//  alte Einträge ggf. vorher löschen
	if (DelOld) {
		short MaxCount = _MerkmalNameList.GetCount ();
		for (short i = 0; i < MaxCount; i++) {
			if (!_MerkmalNameList.DelString (0))
				break;
		}
	}

//  Listbox mit neuen Einträgen füllen
	char Buffer [80] = "";                                  
	ResString OkName (ResID (IDS_OKNAME, pRF), 3);
	ResString NotOkName (ResID (IDS_NOTOKNAME, pRF), 3);

	CTable Tb (*pMDT);  // Merkmalsnamen in ListBox ausgeben
	for (Tb.First (); Tb.Valid (); Tb.Next ()) {
		ExtMerkmalDescriptionLock pEMD (Tb);
		if (!pEMD)
			return EC_SYSERROR;

		pchar pMerkmalName = pEMD -> GetName ();
		pchar pExist = pMDT -> OtherMerkmalName (pEMD -> MCode (),
					   pMerkmalName) ? (pchar) NotOkName.Addr () :
									 (pchar) OkName.Addr ();

	//  Text für Listbox zusammenstellen
		ResString MdText (ResID (IDS_MERKMALKTEXT, pRF), 5);
//XX		if (DEX_GetMkBase () == 10)
		if( 10 == MkBase)
			wsprintf (Buffer, "%s%s%08ld:%s", pExist, MdText.Addr (),
					  pEMD -> MCode (), pMerkmalName);
		else
			wsprintf (Buffer, "%s%s%08lx:%s", pExist, MdText.Addr (),
					  pEMD -> MCode (), pMerkmalName);							  

		DELETE_VEC (pMerkmalName);
		OemToAnsi (Buffer, Buffer);
		if (_MerkmalNameList.AddString (Buffer) == -1)
			return EC_NOMEMORY;
	}

	_MerkmalNameList.Show ();

	return EC_OKAY;
}

//  prüfe, ob alle gewählten Namen einzigartig, gebe Fehlermeldung aus,
//  wenn wenigsten ein Name doppelt auftritt.
//  True, wenn alle Namen ok, sonst False
Bool MerkmalNameDialog :: CheckAllNames (BOOL bOutputError) {
	short Errors = 0;
	CTable Tb (*pMDT);
	for (Tb.First (); Tb.Valid (); Tb.Next ()) {
		ExtMerkmalDescriptionLock pMD (Tb);
		if (!pMD)
			return False;

		pchar pMerkmalName = pMD -> GetName ();
		if (pMDT -> OtherMerkmalName (pMD -> MCode (), pMerkmalName))
			Errors++;
		DELETE_VEC (pMerkmalName);
	}

//  ggf. Fehlermeldung ausgeben
	if (Errors) 
	{
		if (bOutputError)
		{
			ResString Text (ResID (IDS_MNAMEEXIST, pRF), 60);
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

Bool EXPORTFLT MerkmalNameDialog :: QueryClose (Event) 
{
	return True;
}

//	einzigartige Merkmalsnamen erzeugen
ErrCode MerkmalNameDialog :: CreateUniqueNames (void) 
{                                                                
	ErrCode EC = EC_OKAY;		// noch alles OK
	short NotUnique = 0;		// keine doppelten Namen vergeben
	
//	prüfe alle Namen	
	CTable Tb (*pMDT);                        
	char Buffer [10] = "";		// Zahlen-Puffer
	pchar pNewName = NULL;		// neu gebildete Name
	pchar pMerkmalName = NULL;	// alter Name
	for (Tb.First (); Tb.Valid (); Tb.Next ()) 
	{
		ExtMerkmalDescriptionLock pMD (Tb);
		if (!pMD)
			return EC_LOCKERROR;
            
	//  Name bereits vorhanden ?          
		pMerkmalName = pMD -> GetName ();
		if (pMDT -> OtherMerkmalName (pMD -> MCode (), pMerkmalName))
		{                                  
			Buffer [0] = '_';
			itoa (++NotUnique, &Buffer [1], 10);			
			pNewName = new char [lstrlen (pMerkmalName) + lstrlen (Buffer) + 1];
			if (!pNewName)
			{                      
				EC = EC_NOMEMORY;				
				break;
			}		
			
		//	neuen Namen zusammenbauen
			lstrcpy (pNewName, pMerkmalName);               
			
		//	max. Länge beachten
			if ((lstrlen (pMerkmalName) + lstrlen (Buffer)) <= FieldNameSize)
				lstrcat (pNewName, Buffer);
			else
				lstrcpy (&pNewName [FieldNameSize - lstrlen (Buffer)], Buffer);				
			
		//	neuen Name speichern			
			if ((EC = pMD -> SetName (pNewName)) != EC_OKAY)
				break;
				
			DELETE_VEC (pNewName);				
		}			      
		
	//	Namen freigeben		
		DELETE_VEC (pMerkmalName);
	}
	
//	Speicher wieder freigeben
	DELETE_VEC (pMerkmalName);
	DELETE_VEC (pNewName);	

	return EC;
}
