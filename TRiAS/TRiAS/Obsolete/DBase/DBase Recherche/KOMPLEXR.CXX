// File: KOMPLEXR.CXX
// Begonnen am 9. Juli 1993
// Stand vom 13.11.1995

#include "pheader.h"

extern "C" {
	#include <direct.h>		 	// chdir ()
	#include <ctype.h>		  	// toupper ()

	#include "komplexr.hr"	   	// ResourceKonstanten
	#include "dql.h"			// RMode
}

#include "komplexr.htp"		 	// Klassen-Selektion
#include <commonvu.hxx>
#include <containr.hxx>
#include <clipbrd.hxx>		  	// DexClipboard
						
#include <ristypes.hxx>		 	// Koord
#include <geo_obj.hxx>		  	// ObjContainer
#include <objfeld.hxx>		  	// ObjNummer
#include <dbliste.hxx>		  	// DBaseObjFeld
#include <dqlexprt.h>		   	// exportierte Funktionen
#include <dbasprof.hxx>		 	// DBaseProFile

#include "defabout.hxx"		 	// AboutBox
#include <dbtools.hxx>			// GetEditName ()
#include "stscript.hxx"		 	// StandScriptDialog ()

#include <ixtensn.hxx>          // Interfaces einer Erweiterung
#include <xtencunk.hxx>         // InterfaceImplementation der BasisKlasse
#include <xtsnaux.hxx>

#include <xtsnguid.h>			// Guid-Header
#include <initguid.h>
#include "klxguid.h"
#include "version.h"

#include "komplexr.hxx"		 	// Klasse für diese Erweiterung

//  globale Variablen
ResourceFile *pRF = NULL;
pWindow pW = NULL;			  	// TRIAS-Window
KomplexrExtension *pKE = NULL;  // Basisklasse der Erweiterung
Bool DataFromED = False;		// Daten von Editor

//  externe Variablen
extern short RechSem;		   	// Recherche-Semaphor im Yacc definiert

//  Prototypen
extern "C" {
char * PASCAL					  	// Name auf selektierten Script
InitScriptDlg (HWND hWnd);		 	// Eltern-Fenster-Handle
BOOL CALLBACK __export EnumObjectProc (long Key, BOOL iNotLast, void *pData);
BOOL CALLBACK __export EnumIdentProc (long Key, BOOL iNotLast, void *pData);
}

//  Fehlermeldung ausgeben
void OutputError (pchar pErrorText) {
	if (!pErrorText || !*pErrorText || !pW || !pRF)
		return;

	ResString ErrCaption (ResID (IDS_ERRORCAPTION, pRF), 10);
	MessBox MB (ErrCaption.Addr (), pErrorText, pW);
	MB.SetType (OkayButton | HandIcon);

	MB.Show ();
}

BOOL GetExtensionCLSID (CLSID &rClsID)  // Liefert CLSID
{
    memcpy (&rClsID, &CLSID_DBaseRecherche, sizeof (GUID));
        return TRUE;
}

Bool UpdateRegistry (Bool fRegister)	// RegDB aktualisieren (initialisieren/löschen)
{
	char ImportName [] = "TRiAS.dBASERecherche.1";

	if (fRegister) 
	{// RegDB initialisieren
		bool fSuccess = ExtOleRegisterExtensionClass (g_hInstance,
                                					  CLSID_DBaseRecherche, 
                                					  TEXT(ImportName), IDS_LONGCLASSNAME,
													  DBASERE_MAJORVERSION, DBASERE_MINORVERSION, 
													  EFUnLoadable|EFVisible);
		if (!fSuccess) 
			return False;
	} 
	else 
	{// RegDB säubern
        return ExtOleUnregisterClass (CLSID_DBaseRecherche, TEXT(ImportName));
	}

	return True;	// alles ok
}

CTriasExtension *NewExtension (void) 
{
		return new KomplexrExtension ();
}

//  globale Funktionen ----------------------------------------------------
// KeyCompare-Funktion für Ident-Baum
int CompareIds (void *pObj1, void *pObj2) {
	long Id1 = * ((long *) pObj1);
	long Id2 = * ((long *) pObj2);
				
	if (Id1 == Id2)
		return 0;
	else {
		if (Id1 > Id2)
			return 1;
		else
			return -1;
	}
}

// GetKey-Funktion für Ident-Baum
void* GetId (void *pObj) {
	return & (((Ident *) pObj) -> Id ());
}

// IdentTree ---------------------------------------------------------------
//  IdentTree
IdentTree :: IdentTree ()
		   : CTree (GetId, CompareIds) {
	// nothing to do
}

IdentTree :: ~ IdentTree (void) {
	EveryDelete ();					 // alle Einträge löschen
}

void __export IdentTree :: UserDelete (void *pObj) {
	((Ident *) pObj) ->  ~ Ident ();
}

// neuen Id in Container aufnehmen
ErrCode IdentTree :: AddIdent (long Id) {
	CTable Tb (*this);
	if (Tb.Find (&Id))
		return EC_OKAY;

	IdentCreator ICr (*this);
	return Create (ICr, Ident) (Id) ? EC_OKAY : EC_NOMEMORY;
}

// Id im Baum suchen
Bool IdentTree :: FindIdent (long Id) {
	CTable Tb (*this);
	return Tb.Find (&Id);
}


// Konstruktor der ExtensionKlasse --------------------------------------------
KomplexrExtension :: KomplexrExtension (void)
				   : CTriasExtension (EXTENSIONMENU/*, EXTENSIONOBJRECHMENU*/) {
//  lokale Variablen init.
	_pScriptName = NULL;					// akt. Scriptname
	_pOF = NULL;							// Objektfeld
	_pIdTree = NULL;						// ID-Baum
	_toDo = RSUnknown;					  	// Ergenis der Recherche

//  Nachrichten mit TRIAS-ED
	_EditMsg = 0;
}

// Destruktor -----------------------------------------------------------------
KomplexrExtension :: ~KomplexrExtension (void) {
	DELETE_OBJ (_pOF);
	DELETE_VEC (_pScriptName);
	DELETE_OBJ (_pIdTree);
}

Bool KomplexrExtension :: InitExtension (short iMode) {
	if (CTriasExtension :: InitExtension (iMode) == False)
		return False;

//  globale Variablen init.
	pRF = &RF ();				   	// ResourceFile
	pW = MWind ();				  	// Eltern-Fenster (C++)
	pKE = this;					 	// dieses Objekt wird global

	InitDBaseDLL (hWnd (), __DexCmd, __DexxCmd, __DexNotify);

	RegisterNotification (DEX_PROJECTCLOSE);

//  Nachricht zur Kommunikation mit TRIAS-ED registrieren
	ResString Msg (ResID (KE_RECHERCHE, &RF ()), 80);
	_EditMsg = RegisterWindowMessage ((LPCSTR) Msg.Addr ());
	RegisterNotification (_EditMsg, FALSE);

	return True;
}

Bool KomplexrExtension :: UnLoadExtension (void) {
	UnRegisterNotification (DEX_PROJECTCLOSE);

//  TRIAS-Ed ggf. schließen
	PostMessage (HWND_BROADCAST, _EditMsg, EDIT_CLOSE, 0L);
	UnRegisterNotification (_EditMsg, False);	// zuerst abmelden !
	return CTriasExtension :: UnLoadExtension();
}

LRESULT KomplexrExtension :: Notification (WPARAM Msg, LPARAM) {
	switch (Msg) {
		case DEX_PROJECTCLOSE: {
			DELETE_VEC (_pScriptName);
			DELETE_OBJ (_pOF);
			DELETE_OBJ (_pIdTree);
		}
		return FALSE;
		default:
		return FALSE;
	}
}

LRESULT KomplexrExtension :: WindowsNotification (UINT Msg, WPARAM wParam,
												  LPARAM lParam) 
{
	char Buffer [_MAX_PATH] = "";
	static HWND EditHwnd = HWND_BROADCAST;

	if (Msg == _EditMsg) {	  							// Nachricht von TRIAS-Ed
		switch (wParam) 
		{
			case KE_READY: 								// Recherche bereit ?
			{		
			//	ggf. Fenster-Handle des Editors abfragen
				if (RechSem == 0)
				// 	an TRIAS-Ed: Recherche ist bereit !
					SendMessage (EditHwnd, _EditMsg, EDIT_CAN, 0L);	
				return TRUE;
			}
			case KE_PARSE: 
			{
				DataFromED = True;
				doClipBoardRecherche (TRUE);			// Script prüfen
				DataFromED = False;
				return TRUE;
			}
			case KE_START: 								// Recherche Starten
			{
				if (_pScriptName)
					doFileRecherche (_pScriptName);	 	// Recherche durchf.
				return TRUE;
			}
			case KE_PARAM: 
			{											// Scriptname als Parameter setzen
				_SetScriptName ();						// Scriptnamen aus Clipboard lesen
				return TRUE;
			}   
			case KE_SENT_VERSION:
			{                 
#ifdef WIN32			      
				PostMessage (EditHwnd, _EditMsg, EDIT_GET_VERSION, 1L);							
#else
				PostMessage (EditHwnd, _EditMsg, EDIT_GET_VERSION, 0L);																		
#endif
				return TRUE;
			}
			case KE_GET_HANDLE: 
			{											// Handle des Editors speichern
				EditHwnd = (HWND) lParam;				
				return TRUE;
			}					
			case KE_SENT_HANDLE: 
			{											// Handle der Recherche an Editor senden
				SendMessage (EditHwnd, _EditMsg, EDIT_GET_HANDLE, (LPARAM) pKE -> hWnd ());		
				return TRUE;
			}
/*
			case KE_CLOSE: 							// der Editor wurde geschlossen
			{
				m_EditHwnd = NULL;
				return TRUE;
			}
*/
		}
	}

	return FALSE;		// Nachricht wurde nicht bearbeitet
}

Bool KomplexrExtension :: MenuInit (HMENU hMenu, LPARAM, HWND) 
{
//  wenn Script gewählt wurde - Start-Menüitem aktivieren
	EnableMenuItem (hMenu, IDM_START + MenuOffset (),
				   _pScriptName && *_pScriptName ?
					MF_ENABLED : MF_DISABLED | MF_GRAYED);
	return True;
}

// Diese Funktion dient der Behandlung der MenuKommandos vom nutzereigenen
// Menu der Erweiterung
Bool KomplexrExtension :: MenuCommand (WPARAM MenuItemID, HWND hWnd) {
	switch (MenuItemID) {
		case IDM_STAND: {
			StandScriptDialog StDialog (MWind ());   // Dialog erzeugen
			if (! StDialog.OpFlag ())
				break;
			StDialog.Show ();						 // Fenster darst.
			pchar pS = StDialog.GetScript ();
			if (!pS || !*pS)
				break;
			switch (StDialog.Result ()) {
				case StandScriptDialog :: Modify: { // Script modfizieren
				//  Script ins Clipboard copieren
					CClipboard DCB;
					DCB.Clear ();					// Inhalt des Clipboards löschen
					DCB.Insert (pS);	 			// Inhalt kopieren

				//  Kdo.-Zeile zusammenbauen
					ResString Text (ResID (IDS_CLIPOPTION, &RF ()), 5);
					char CmdLine [40] = "";
					char Buffer [30] = "";
					SetScriptPfad ();				// Scriptpfad einstellen
					wsprintf (CmdLine, "%s %s", GetEditName (Buffer,
									sizeof (Buffer)), Text.Addr ());
					RunTriasEdit (MWind (), CmdLine, SW_SHOWNORMAL);
				}
				break;
				case StandScriptDialog :: Start:
					doBufferRecherche (pS);
				break;
				case StandScriptDialog :: Error:
				case StandScriptDialog :: Abbruch:
				default:
				break;
			}
		}
		break;
		case IDM_EDIT: {
			char Buffer [2 * _MAX_PATH] = "";
			GetEditName (Buffer, _MAX_PATH);
			if (_pScriptName && *_pScriptName) {
				lstrcat (Buffer, " ");
				lstrcat (Buffer, _pScriptName);
			} else
				SetScriptPfad ();	  //  DQLSCR-Pfad einstellen
			RunTriasEdit (MWind (), Buffer, SW_SHOWNORMAL);
		}
		break;
		case IDM_EXTABOUT: {
			AboutBox AB (MWind (), ResID (DEFIDABOUT, &RF ()));
			AB.Show ();
		}
		break;
		case IDM_PARAM: {
			SetScriptPfad ();				   // Pfad einstellen
			char *pNewName = InitScriptDlg (hWnd);
				if (pNewName)
				{		   
				DELETE_VEC (_pScriptName);			  // alten Namen löschen
				_pScriptName = pNewName;
				}			   
		}
		break;
		case IDM_START:
			doFileRecherche (_pScriptName);	   // Recherche durchf.
		break;
	}

	return True;
}

extern "C" {

BOOL CALLBACK __export EnumObjectProc (long Key, BOOL, void *pData) {

	ObjectData *pOD = (ObjectData *) (pData);

//  Objekt-Nummer im Feld speichern
	ObjNummerCreator ONC (* (pOD -> _pOF));

	if (pOD -> _pOF -> NewObj (ONC, Key)) {
		pOD -> _EC = EC_OKAY;
		return TRUE;
	} else {
		DEX_Error (RC_IdFilterNew, EC_NOMEMORY);
		pOD -> _EC = EC_NOMEMORY;
		return FALSE;
	}
}

//  enumerieren aller zu einer Sicht gehörenden IDs
BOOL CALLBACK __export EnumIdentProc (long Key, BOOL, void *pData) {

	IdentEnumDaten *pID = (IdentEnumDaten *) (pData);

	if ((pID -> _pIdT -> AddIdent (Key)) == EC_OKAY) {
		pID -> _EC = EC_OKAY;
		return TRUE;
	} else {
		DEX_Error (RC_IdFilter, EC_NOMEMORY);
		pID -> _EC = EC_NOMEMORY;
		return FALSE;
	}
}

}   // extern "C"

//  alle zu einer Sicht gehörenden Objekte lesen
ErrCode KomplexrExtension :: IdFilterNew (char *pSichtName) {
//  prüfe Parameter
	if (!pSichtName || !*pSichtName) {
		DEX_Error (RC_IdFilterNew, EC_BadInSpec);
		return EC_BadInSpec;
	}

//  Datenstrukturen init.
	IdentTree IdT;			  // ID-Baum
	IdentEnumDaten ID (&IdT);
	ENUMTEXTKEY TK;
	TK.eKey = pSichtName;
	TK.eFcn = (ENUMTEXTKEYPROC) EnumIdentProc;
	TK.ePtr = (void *) &ID;

	DEX_EnumSightIdents (TK);  // alle zur Sicht gehörenden Ids lesen

//  Fehler-Test
	if (ID._EC != EC_OKAY)
		return ID._EC;

	ObjectData OD (_pOF);
	ENUMLONGKEY LK;
	LK.eKey = 0L;
	LK.eFcn = (ENUMLONGKEYPROC) EnumObjectProc;
	LK.ePtr = (void *) &OD;

//  alle Objekte der Ids lesen
	CTable Tb (IdT);
	for (Tb.First (); Tb.Valid (); Tb.Next ()) {
		IdentLock pId (Tb);
		if (!pId) {
			DEX_Error (RC_IdFilterNew, EC_SYSERROR);
			return EC_SYSERROR;
		}
		LK.eKey = pId -> Id ();	 // akt. Id setzen

		DEX_EnumIdentObjects (LK);  // alle Objekte des Ids enumerieren

	//  Fehler-Test
		if (OD._EC != EC_OKAY)
			return OD._EC;
	}

	return EC_OKAY;
}

//  alle Objekte aus dem Feld löschen, die nicht zur Sicht gehören
ErrCode KomplexrExtension :: IdFilter (char *pSichtName) {
//  prüfe Parameter
	if (!pSichtName || !*pSichtName) {
		DEX_Error (RC_IdFilter, EC_BadInSpec);
		return EC_BadInSpec;
	}

//  Datenstrukturen init.
	IdentTree IdT;			  // ID-Baum
	ENUMTEXTKEY TK;
	IdentEnumDaten ID (&IdT);
	TK.eKey = pSichtName;
	TK.eFcn = (ENUMTEXTKEYPROC) EnumIdentProc;
	TK.ePtr = (void *) &ID;

	DEX_EnumSightIdents (TK);  // alle zu Sicht gehörenden Ids lesen

//  Fehler-Test
	if (ID._EC != EC_OKAY)
		return ID._EC;

//  alle Objekte entfernen, die nicht zu Sicht gehören
	CRing Ri (*_pOF);
	CTable Tb (IdT);
	Bool toDelete = False;
	for (Ri.First (); Ri.Valid (); ) {
		{ DBaseObjNummerLock pON (Ri);
		if (!pON) {
			DEX_Error (RC_IdFilter, EC_SYSERROR);
			return EC_SYSERROR;				 // bei Fehler zurück
		}

	//  zugeh. ID lesen, suchen und Löschflag setzen
		long Id = (long) DEX_GetObjIdent (pON -> _ON);
		toDelete = Tb.Find (&Id) ? False : True;
		}	   // unlock ObjNummer

	//  ObjNummer ggf. löschen
		if (toDelete) {
			if (! Ri.Delete ()) {
				DEX_Error (RC_IdFilter, EC_SYSERROR);
				return EC_SYSERROR;					 // bei Fehler zurück
			}
		} else {
			if (! Ri.Next ())		   // wenn kein weiters Objekt mehr
				break;
		}
	}

	return EC_OKAY;
}

//  Recherche-Ergebnisse in Liste ausgeben
void KomplexrExtension :: _OutObjectList (void) {
//  prüfe interne Parameter
	if (!_pOF || !_pOF -> Count ())
		return;

//  ObjNummer-Liste erzeugen
	long * pObjList = new long [(short) _pOF -> Count ()];
	if (!pObjList) {
		DEX_Error (RC_KomplexrOutObjList, EC_NOMEMORY);
		return;
	}

//  ObjNummer-Liste füllen
	CRing Ri (*_pOF);
	short i = 0;
	for (Ri.First (); Ri.Valid (); Ri.Next (), i++) {
		DBaseObjNummerLock pON (Ri);
		if (!pON) {
			DEX_Error (RC_KomplexrOutObjList, EC_SYSERROR);
			DELETE_OBJ (pObjList);
			return;
		}
		* (pObjList + i) = pON -> _ON;
	}

//  Daten für Recherche-Fenster init.
	CREATEOBJEKTINFO COI;
	memset (&COI, 0, sizeof (CREATEOBJEKTINFO));
	POINT Pt;
	Pt.x = 10;
	Pt.y = 10;
	COI.dwSize = sizeof (CREATEOBJEKTINFO);
	ResString Caption (ResID (IDS_OBJLISTCAPTION, &RF ()), 50);
	COI.lpCaption = (char *) Caption.Addr ();
	COI.plObjs = pObjList;
	COI.iNumObjs = (short) _pOF -> Count ();
	COI.cMColor = RGB (200, 0, 0);
	COI.pntPos = Pt;

//  Ergebnis anzeigen
	DEX_CreateObjektInfo (COI);

	DELETE_OBJ (pObjList);
}

//  Geometrierecherche durchführen
ErrCode KomplexrExtension :: doGeoRecherche (ObjContainer &OC) {
//  Daten init.
	ObjectData OD (_pOF);
	ENUMRECHGEOMETRIE ERG;
	memset (&ERG, 0, sizeof (ENUMRECHGEOMETRIE));
	ERG.dwSize = sizeof (ENUMRECHGEOMETRIE);
	ERG.lCont = (long *) &OC;	   // Objekt-Container
	ERG.eFcn = (RECHGEOMETRIEPROC) EnumObjectProc;	  // Enum-Funktion
	ERG.pData = (void *) &OD;	   // gesammelte Objekte
	ERG.iMode = ERGExact;		  // exakte Recherche durchführen
	DEX_EnumRechGeometrie (ERG);
	return EC_OKAY;
}

// gefundenen Objekte umnklassifizieren
void KomplexrExtension :: _Classify (void) {
	const short BufferSize = 256;		   // Profile-Buffer

//  prüfe interne Parameter
	if (!_pOF || !_pOF -> Count ())
		return;

	IdentTree IdT;
	DBaseProFile PF;
	char Buffer [BufferSize] = "";
	CRing rOF (*_pOF);
	long OldId = 0;
	for (rOF.First(); rOF.Valid(); rOF.Next()) {
		DBaseObjNummerLock l (rOF);
		if (!l) {
			DEX_Error (RC_KomplexrClassify, EC_LOCKERROR);
			continue;
		}

		long newID = l -> _Id;
		if (newID == -1L)
			continue;   // nicht klassifiziert

		long ONr = l -> _ON;

		if ((OldId = DEX_GetObjIdent (ONr)) == 0)   // wenn alte ID ungültig
			continue;

	//  Typ lesen und konvertieren
		short Type = 0;
		switch (DEX_GetObjectType (ONr)) {
			case OGPunkt:
				Type = MODIDENT_PUNKT;
			break;
			case OGLinie:
				Type = MODIDENT_LINIE;
			break;
			case OGKreis:
			case OGFlaeche:
				Type = MODIDENT_FLAECHE;
			break;
			case OGText:
				Type = MODIDENT_TEXT;
			break;
			case OGKO:
				Type = MODIDENT_TYP;
			break;
			case OGUnknown:
			default:
			break;
		}

	//  Objekt umklassifizieren
		PBDDATA Data;
		memset (&Data, 0, sizeof (PBDDATA));		// init.
		Data.dwSize = sizeof (PBDDATA);
		Data.pbdTyp = 'i';						  // Ident-Typ
		Data.pbdCode = newID;
		DEX_GetPBDData (Data);

	//  Modifikation des Idents durchführen
		MODOBJIDENT Ident;
		memset (&Ident, 0, sizeof (MODOBJIDENT));
		Ident.dwSize = sizeof (MODOBJIDENT);
		Ident.lONr = ONr;
		Ident.lNewIdent = newID;
		Ident.iMode = Data.pbdTemp ? MODIDENT_TEMP | Type : Type;
		DEX_ModObjectIdent (Ident);

	//  INI-Datei modif.: wenn Objekt permanent unklassifiziert
		if (! Data.pbdTemp && ! IdT.FindIdent (newID)) {
			if (IdT.AddIdent (newID) == EC_OKAY) {
				if (PF.ReadDBaseEntry (OldId, Buffer, BufferSize))
					PF.WriteDBaseEntry (newID, Buffer);
			}
		}
	}

//  alles Neu zeichnen
	DEX_RePaint();
}

//  lokale Daten für Recherche init.
ErrCode KomplexrExtension :: InitRecherche (void) {
	ErrCode EC = EC_OKAY;
	_toDo = RSUnknown;

//  alten Werte freigeben und rücksetzen
	DELETE_OBJ (_pOF);
	if (! (_pOF = new DBaseObjFeld ())) {
		DEX_Error (RC_KomplExtMenuC, EC = EC_NOMEMORY);
		return EC;
	}

//  neue Ident-Liste anlegen
	DELETE_OBJ (_pIdTree);
	if (! (_pIdTree = new IdentTree ())) {
		DEX_Error (RC_KomplExtMenuC, EC = EC_NOMEMORY);
		return EC;
	}

	return EC;
}

//  Recherche-Ergebnisse auswerten
ErrCode KomplexrExtension :: OutputRecherche (Bool ParseOnly) {
	if (ParseOnly)			  //  wenn nur prüfen
		return EC_OKAY;

//  Auswertung der Recherche
	if (_pOF && _pOF -> Count ()) {
		switch (_toDo) {
			case RSClassify:
				_Classify ();
			break;
			case RSObjList:
				_OutObjectList ();
			break;
			case RSUnknown:
			default: {
				DEX_Error (RC_doRecherche, EC_ILLPARS);
				return EC_ILLPARS;
			}
			break;
		}
	}
	DELETE_OBJ (_pOF);

	return EC_OKAY;
}

//  neuen Scriptnamen setzen
Bool KomplexrExtension :: _SetScriptName (void) {
	CClipboard DCB;			   		
	long lLen = DCB.GetItemSize (CClipboard :: FmtText);		// Länge ermitteln
	if (lLen <= 0)
		return False;

//	Speicher für ScriptNamen anfordern
	char *pFileName = new char [lLen + 1];
	if (!pFileName)
	{
		DEX_Error (RC_KomplSetScript, EC_NOMEMORY);		
		return False;
	}
	memset (pFileName, 0, (short) (lLen + 1));		// init.

//	File-Namen aus Clipboard lesen
	if (!DCB.Retrieve (pFileName, (short) lLen))
	{
		DELETE_VEC (pFileName);
		return False;
	}

//  Test: Datei existiert ?
	OFSTRUCT of;
	if (OpenFile (pFileName, &of, OF_EXIST) == HFILE_ERROR) 
	{
		DELETE_VEC (pFileName);
		DEX_Error (RC_KomplSetScript, EC_NOFILE);
		return False;
	}

//  neuen Datei-Namen speichern
	DELETE_VEC (_pScriptName);	// alten Namen löschen
	_pScriptName = pFileName;	// neuen Namen speichern

	return True;
}

//  DQLSCR-Pfad einstellen
void KomplexrExtension :: SetScriptPfad (void) {
	char oldCwd [_MAX_PATH] = "";
	int oldDrive = _getdrive ();			// altes Lw

//  alte Pfad
	if (! getcwd (oldCwd, _MAX_PATH))
		return;							 // konnte nicht gelesen werden

//  lokales Script-Verzeichnis einstellen
	char Path [_MAX_PATH] = "";
	DEX_GetActiveProject (Path);		  // Projektname lesen
	if (!*Path)
		return;

	ResString SubDir (ResID (IDS_DQLSUBDIRECT, &RF ()), 10); // SubDir lesen

//  Pfad zusammenbauen
	char Drive [_MAX_DRIVE] = "";
	char Dir [_MAX_DIR] = "";
	_splitpath (Path, Drive, Dir, NULL, NULL);
	_makepath (Path, Drive, Dir, NULL, NULL);
	lstrcat (Path, SubDir.Addr ());

	if (_chdrive (toupper (Drive [0]) - 'A' + 1)) {	 // neues Lw
		_chdrive (oldDrive);
		chdir (oldCwd);
	}

	if (! chdir (Path))
		return;					 // Pfad OK

//  globales Script-Verzeichnis lesen   
	char IniFile [_MAX_PATH] = "";
	if (! DEX_GetMainIniName (IniFile))
	{               
		_chdrive (oldDrive);
		chdir (oldCwd);
		return;
	}		
	ResString Search (ResID (IDS_SCRIPTKEY, &RF ()), 12);
	ResString Section (ResID (IDS_PFADSECTION, &RF ()), 12);
	short Len = 0;
	if (! (GetPrivateProfileString (Section.Addr (), Search.Addr (), "",
							 Path, Len, IniFile))) {
		_chdrive (oldDrive);
		chdir (oldCwd);
		return;
	}

//  ggf. letzten '\' löschen
	short LastPos = lstrlen (Path) - 1;
	if (Path [LastPos] == '\\')
		Path [LastPos] = '\0';

//  Verzeichnis einstellen
	if (chdir (Path)) {		 // globales Script-Verzeichnis
		_chdrive (oldDrive);
		chdir (oldCwd);		 // bei Fehler altes Verzeichnis
	}
}

//  Neuen Sicht-Identifiaktor in Baum aufnehmen
Bool KomplexrExtension :: AddIdent (long Id) {
//  prüfe interne Parameter
	if (!_pIdTree) {
		DEX_Error (RC_KomplexrAddIdent, EC_SYSERROR);
		return False;
	}

	if (_pIdTree -> AddIdent (Id) == EC_OKAY)
		return True;
	else {
		DEX_Error (RC_KomplexrAddIdent, EC_NOMEMORY);
		return False;
	}
}

//  Alle Objekte über Identfikator-Liste filtern
ErrCode KomplexrExtension :: IdFilterIdents (void) {
//  prüfe interne Parameter
	if (!_pIdTree || !_pOF) {
		DEX_Error (RC_KomplexrFilterIdents, EC_SYSERROR);
		return EC_SYSERROR;
	}

//  alle Objekte entfernen, die nicht zur Liste gehören
	CRing Ri (*_pOF);
	CTable Tb (*_pIdTree);
	Bool toDelete = False;
	for (Ri.First (); Ri.Valid (); ) {
		{ DBaseObjNummerLock pON (Ri);
		if (!pON) {
			DEX_Error (RC_KomplexrFilterIdents, EC_SYSERROR);
			return EC_SYSERROR;				 // bei Fehler zurück
		}

	//  zugeh. ID lesen, suchen und Löschflag setzen
		long Id = (long) DEX_GetObjIdent (pON -> _ON);
		toDelete = Tb.Find (&Id) ? False : True;
		}	   // unlock ObjNummer

	//  ObjNummer ggf. löschen
		if (toDelete) {
			if (! Ri.Delete ()) {
				DEX_Error (RC_KomplexrFilterIdents, EC_SYSERROR);
				return EC_SYSERROR;					 // bei Fehler zurück
			}
		} else {
			if (! Ri.Next ())		   // wenn kein weiters Objekt mehr
				break;
		}
	}

	return EC_OKAY;
}

