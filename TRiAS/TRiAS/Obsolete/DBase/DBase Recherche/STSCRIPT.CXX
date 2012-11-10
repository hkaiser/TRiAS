/*
File: STSCRIPT.CXX
Standard-Script für die Komplex-Recherche erstellen.

erarbeitet : J. Benkenstein				Begonnen am 20.09.1993
										Stand vom 14.11.1995
*/
#include "pheader.h"

extern "C" {
	#include <ctl3d.h>	  		// 3d-Kontrols
}

#include "stscript.htp"		 	// Klassen-Selektion
#include <commonvu.hxx>
#include <containr.hxx>
#include <dbliste.hxx>		  	// DBaseFiles
#include <expreing.hxx>		 	// EntryExpression

#include <dbtools.hxx>		  	// SetdBasePfad ()
#include <dbasprof.hxx>		 	// DBaseProFile
#include <dqlexprt.h>		   	// exportierte Funktionen

#include "komplexr.hr"		   	// Resourcen-Defines
#include "aliassel.hxx"		 	// SelectAliasNames
#include "stscript.hxx"		 	// zugeh. Header-File

extern "C" {
extern HINSTANCE g_hInstance;
}

//  Prototypen
extern "C" {
pchar OutputResourceTemplate (int ResID, int fh);
}

//  Konstanten
const short MAX_FNAME = 8;		  // max. Länge eines Dateinamens unter DOS
const short ExpressionSize = 256;   // max. Größen der Textfelder
const short CommentSize = 100;
const short ScriptSize = 2048;	  // Größe des expandierten Standard-Scripts
const char GroupTextSep = '\"';
const char CloseBlock = '}';
const short ExprCount = 8;		 // Anzahl der benutzten dBase-Expressions

//  Variablen
CodeBase *pCodeBase = NULL;
DBaseFiles *pDataTree = NULL;

//  externe Varaiblen
extern ResourceFile *pRF;

//		lokale Variablen
static BOOL		bUniqueRecord = TRUE;		// Dialog-Zustands-Flags: nur 1. Satz filtern
static BOOL bExprConnect = FALSE;		// Anbindung über Expression				
static BOOL bOutpuListBox = TRUE;		// Ausgabe der gefundenen Objekte in Listbox

extern "C" {
LRESULT FAR PASCAL __export Init3d (HWND hDlg, UINT Msg, WPARAM, LPARAM) {
	if (Msg == WM_INITDIALOG && Ctl3dEnabled())
			Ctl3dSubclassDlg (hDlg, CTL3D_ALL); // lediglich CTL3D aktivieren
	return FALSE;
}

//  dBase-Expression im Dialog eingeben
//  Expression ist explizit freizugeben
char* FAR PASCAL __export EntryExprDialog (
					   pWindow pParentWindow,   // ParentWindow
					   short MaxExprSize,	   // max. Länge des neuen Expr.
					   pchar pOldExpr)  {	   // voreingestellter Expr.
	pchar pNewExpr = NULL;
	if (SelectdBaseFiles (pParentWindow)) {
		pNewExpr = EntrydBaseExpression (pParentWindow, pOldExpr, MaxExprSize);
	}

	return pNewExpr;
}

//  dBASE-Expression einegeben
//  Zeiger auf Expression ist explizit freizugeben
char * FAR PASCAL __export EntrydBaseExpression (Window *pParent, pchar pExpr,
												short ExprSize) {
//  prüfe interne Parameter
	if (!pCodeBase || !pDataTree) {
		DEX_Error (RC_EntrydBaseExpression, EC_SYSERROR);
		return NULL;
	}
	if (pCodeBase -> error () != r4success || !pDataTree -> Count ())
		return NULL;

//  Expression eingeben und prüfen
	EntryExpression EntryExpr (pParent, pCodeBase, pDataTree, pExpr, ExprSize);
	if (EntryExpr.OpFlag () == False)
		return NULL;
	EntryExpr.Show ();

//  ggf. Expression übernehmen
	pchar pNewExpr = NULL;
	if (EntryExpr.OpFlag () == True) {
		pNewExpr = EntryExpr.GetExpression ();
		if (pNewExpr && *pNewExpr) {
		//  Test auf Längenüberschreitung
			if (lstrlen (pNewExpr) >= ExprSize) {
				DEX_Error (RC_EntrydBaseExpression, EC_NOEXPRSPACE);
				*(pNewExpr + ExpressionSize - 1) = '\0';
			}
		}
	}

	return pNewExpr;
}

// AliasNamen für dBase-Dateien auswählen
// und diese Namen im DataIndexTree speichern
BOOL FAR PASCAL __export  SelectdBaseFiles (Window *pParent) {
//  prüfe Parameter
	if (!pParent) {
		DEX_Error (RC_SelectdBaseFiles, EC_ILLPARS);
		return FALSE;
	}

//  alten Infos löschen
	if (pCodeBase) {
		DELETE_OBJ (pDataTree);
		DeleteCodeBaseObj ();
		pCodeBase = NULL;
	}

//  neues CodeBase-Objekt erzeugen
	pCodeBase = CreateCodeBaseObj (g_hInstance);
	if (!pCodeBase) {
		DEX_Error (RC_SelectdBaseFiles, EC_NOMEMORY);
		return FALSE;
	}

	if (pCodeBase -> error () != r4success) {
		DeleteCodeBaseObj ();
		pCodeBase = NULL;
		return FALSE;
	}

//  neuen Baum anlegen
	pDataTree = new DBaseFiles;
	if (!pDataTree) {
		DEX_Error (RC_SelectdBaseFiles, EC_NOMEMORY);
		DeleteCodeBaseObj ();
		pCodeBase = NULL;
		return FALSE;
	}

//  Diolag für Auswahl der Aliasnahmen
	SelectAliasNames SA (pParent, pRF, pCodeBase, pDataTree);
	Bool Ret = SA.OpFlag ();
	if (Ret) {
		SA.Show ();
		Ret = SA.Result ();
	}

//  ggf. alles löschen
	if (Ret == False) {
		DELETE_OBJ (pDataTree);
		DeleteCodeBaseObj ();
		pCodeBase = NULL;
	}

	return Ret;
}
}   // extern "C"
								  
								  
#pragma warning (disable:4355)
								  
//  StandScript -------------------------------------------------------------
StandScriptDialog :: StandScriptDialog (pWindow pParent)
: DialogWindow (pParent, ResID (IDD_STANDSCRIPT, pRF)),
_UniqueCheck (this, ResID (IDB_UNIQUEKEY, pRF)),
_ExprCheck (this, ResID (IDB_CONNECTEXPR, pRF)),
_CommentLine (this, ResID (IDE_COMMENT, pRF)),
_dBaseExprList (this, ResID (IDC_EXPRESSIONLIST, pRF)),
_AusfButton (this, ResID (IDOK, pRF)),
_SelFileButton (this, ResID (IDB_SELECTFILE, pRF)),
_FileName (this, ResID (IDT_DBASEDATEI, pRF)),
_OutListButton (this, ResID (IDR_LIST, pRF)),
_EntryExprButton (this, ResID (IDB_ENTRYEXPR, pRF)),
_OutClassifyButton (this, ResID (IDR_CLASSIFY, pRF)) {
	_pScript = NULL;
	pDataTree = NULL;
	pCodeBase = NULL;

//  Controls mit Standardwerten init.
	_CommentLine.SetTextLimit (CommentSize);
	_SetComment ();
	_UniqueCheck.SetChecked (bUniqueRecord);
	_ExprCheck.SetChecked (bExprConnect);
	_OutListButton.SetState (bOutpuListBox);
	_OutClassifyButton.SetState (!bOutpuListBox);

//  letzten 8 dBase-Ausdrücke lesen
	_ReadExpression ();
	_OpFlag = True;
}							 

#pragma warning (default:4355)

StandScriptDialog :: ~StandScriptDialog (void) {
	if (pCodeBase) 
	{
		DELETE_OBJ (pDataTree);
		DeleteCodeBaseObj ();
		pCodeBase = NULL;
	}
	DELETE_VEC (_pScript);
	
//	Dialog-Zustands-Variablen speichern	
	bUniqueRecord = _UniqueCheck.isChecked ();
	bExprConnect = _ExprCheck.isChecked ();
	bOutpuListBox = _OutListButton.GetState ();
}

//  Kommentar-Zeile init.
void StandScriptDialog :: _SetComment (void) {
//  prüfe interne Parameter
	if (!pRF)
		return;

	char Buffer [_MAX_PATH] = "";
	char FName [_MAX_FNAME] = "";
	DEX_GetActiveProject (Buffer);
	_splitpath (Buffer, NULL, NULL, FName, NULL);
	if (lstrlen (FName) > MAX_FNAME)	   // Länge ggf. begrenzen
		FName [MAX_FNAME] = '\0';
	strupr (FName);

//  Standard-Text zusammenbauen
	ResString Comment (ResID (IDS_COMMENT, pRF), 80);
	wsprintf (Buffer, Comment, FName);
	_CommentLine.SetText (Buffer);
}

//  Button wurde betätigt
void __export StandScriptDialog :: ButtonClick (ControlEvt CE) {
	switch ((uint) CE.GetControlID ()) {
		case IDB_HELP:
		break;				  // noch kein Text definiert
		case IDCANCEL:
			EndDlg (Abbruch);	 // identisch Abbruch
		break;
		case IDOK:
			if (_GenerateScript ())		 // Script erzeugen
				EndDlg (Start);			 // Recherche durchf.
		break;
		case IDB_MODIFY:
			if (_GenerateScript ())		   // Script erzeugen
				EndDlg (Modify);			// Dialog modifiz.
		break;
		case IDB_ENTRYEXPR: {
			char Expr [ExpressionSize] = "";
			_dBaseExprList.GetCurrentString (Expr);
			pchar pNewExpr = EntrydBaseExpression (this, Expr,
												   ExpressionSize - 1);

		//  Test ob Expr. bereits vorhanden
			if (pNewExpr && *pNewExpr) {
				short Index = _dBaseExprList.FindString (pNewExpr, True);
				if (Index >= 0)  // Expr. bereits vorhanden
					_dBaseExprList.DelString (Index);	// als 1. Eintrag
				_dBaseExprList.AddString (pNewExpr, 0);  // hinzufügen
				_dBaseExprList.ChangeCurrentIndex (0);   // in Sicht-Zeile
				_AusfButton.Enable ();
			}
			DELETE_VEC (pNewExpr);
		}
		break;
		case IDB_SELECTFILE: {  // dBase-Datei auswählen
			Bool OpFlag = SelectdBaseFiles (this);
			if (OpFlag) {
					OpFlag = _OutputAliasNames ();
			}

		//  Auswertung der Aktionen: Setzen des Eingabe-Buttons
			if (OpFlag)
				_EntryExprButton.Enable ();
			else {
				_EntryExprButton.Disable ();
				ResString Keine (ResID (IDS_KEINEDATEI, pRF), 10);
				_FileName.SetText (Keine.Addr ());
			}
		}
		break;
		default:
		break;
	}
}

Bool __export StandScriptDialog :: QueryClose (Event) {
	EndDlg (Abbruch);
	return True;
}

//  generiere Standard-Script
Bool StandScriptDialog :: _GenerateScript (void) {
	const short BufferSize = 200;	   // Größe des Arbeitspuffers

//  prüfe interne Parameter
	if (!pRF)
		return False;

//  leeren Script anlegen
	DELETE_VEC (_pScript);	  // alten Script zuvor löschen
	if (! (_pScript = new char [ScriptSize])) {
		DEX_Error (RC_ScriptDlgGenScript, EC_NOMEMORY);
		return False;
	}
	memset (_pScript, 0, ScriptSize);

//  Srcipt-Template lesen
	pchar pTemp = OutputResourceTemplate (SCRIPT_TEMPLATE, NULL);
	if (!pTemp) {
		DEX_Error (RC_ScriptDlgGenScript, EC_NOMEMORY);
		DELETE_VEC (_pScript);
		return False;
	}

//  Arbeitspuffer erzeugen und init.
	pchar pBuffer = new char [BufferSize];
	if (!pBuffer) {
		DEX_Error (RC_ScriptDlgGenScript, EC_NOMEMORY);
		DELETE_VEC (_pScript);
		DELETE_VEC (pTemp);
		return False;
	}
	memset (pBuffer, 0, BufferSize);

//  Parameter aus Dialog-Box lesen: Standard-Kommentar
	_CommentLine.GetText (pBuffer, BufferSize);
	wsprintf (_pScript, pTemp, pBuffer);				// Kommentar kopieren

//  Key-Zeile generieren				
		if (_ExprCheck.isChecked ())
		{
			ResString Textf (ResID (IDS_REDKEYLINE, pRF), 40);			// Zeile lesen
			ResString Textu (ResID (_UniqueCheck.isChecked () ? IDS_KEYFLAG :
																IDS_DUMMY, pRF), 10);
			wsprintf (pBuffer, Textf.Addr (), Textu.Addr ());
		}			
		else
		{
				ResString Textf (ResID (IDS_KEYLINE, pRF), 40);					// Zeile lesen
				ResString Textu (ResID (_UniqueCheck.isChecked () ? IDS_KEYFLAG :
																IDS_DUMMY, pRF), 10);
			wsprintf (pBuffer, Textf.Addr (), Textu.Addr ());
		}
	lstrcat (_pScript, pBuffer);				// Key-Zeile anfügen

//  ggf. Gruppen-Bildung
	if (_OutClassifyButton.GetState ()) {	// wenn Umklassifizierung geford.
	//  Group-Text lesen
		ResString Text (ResID (IDS_GROUPLINE, pRF), 50);
		wsprintf (pBuffer, Text.Addr (), GroupTextSep, GroupTextSep);
		lstrcat (_pScript, pBuffer);	// Zeile anfügen

	//  Expression lesen und anfügen
		Text = ResString (ResID (IDS_EXPRLINE, pRF), 30);
		char Expr [ExpressionSize] = "";
		_dBaseExprList.GetCurrentString (Expr);
		wsprintf (pBuffer, Text, Expr);
		lstrcat (_pScript, pBuffer);

	//  Blocke-Ende der Gruppe
		wsprintf (pBuffer, "\t\t%c\r\n", CloseBlock);
		lstrcat (_pScript, pBuffer);
	} else {							// Ausgabe als Objekt-Liste
	//  Expression lesen und anfügen
		ResString Text (ResID (IDS_EXPRLINE, pRF), 30);
		char Expr [ExpressionSize] = "";
		_dBaseExprList.GetCurrentString (Expr);
		wsprintf (pBuffer, Text.Addr (), Expr);
		lstrcat (_pScript, pBuffer);
	}

//  Ausgabe anhängen
	ResString Text1 (ResID (_OutClassifyButton.GetState () ?
							 IDS_REPORTONCLASS : IDS_REPORTONLIST, pRF), 20);
	ResString Text (ResID (IDS_REPORTLINE, pRF), 50);
	wsprintf (pBuffer, Text.Addr (), Text1.Addr ());
	lstrcat (_pScript, pBuffer);

//  Speicher freigeben
	DELETE_VEC (pTemp);		 // für Template
	DELETE_VEC (pBuffer);	   // Arbeitspuffer

//  akt. Ausdruck sichern
	_SaveExpression ();

	return True;
}

//  Lese letzen 4 dBase-Ausdrücke aus INI-Datei lesen
void StandScriptDialog :: _ReadExpression (void) {
	DBaseProFile ProFile;
	ResString Section (ResID (IDS_EXPRSECTION, pRF), 20);
	ResString Entry (ResID (IDS_EXPRENTRY, pRF), 10);
	char Buffer [10] = "";
	lstrcpy (Buffer, Entry.Addr ());
	char ValBuffer [5] = "";
	char Expression [ExpressionSize] = "";
	for (short i = 0; i < ExprCount; i++) {
		lstrcat (Buffer, itoa (i+1, ValBuffer, 10));
		if (GetPrivateProfileString (Section.Addr (), Buffer, "",
			Expression, sizeof (Expression), ProFile.GetProFileName ())) {
			if (_dBaseExprList.AddString (Expression) == -1) {
				DEX_Error (RC_ScriptDlgReadExpr, EC_NOMEMORY);
				break;
			}
			if (i == 0) {
				_dBaseExprList.ChangeCurrentIndex (0);
				_AusfButton.Enable ();
			}
		}
		else
			break;
		Buffer [lstrlen (Buffer) - 1] = '\0';   // Ziffer löschen
	}
}

//  letzen 4 dBase-Ausdrücke in INI-Datei speichern
void StandScriptDialog :: _SaveExpression (void) {
	DBaseProFile ProFile;
	ResString Section (ResID (IDS_EXPRSECTION, pRF), 20);
	ResString Entry (ResID (IDS_EXPRENTRY, pRF), 10);
	char Buffer [10] = "";
	lstrcpy (Buffer, Entry.Addr ());
	char ValBuffer [5] = "";
	char Expression [ExpressionSize] = "";

//  restlichen Ausdrücke aus ListBox lesen und in INI-Datei schreiben
	for (short Index = 0; Index < ExprCount; Index++) {
		lstrcat (Buffer, itoa (Index + 1, ValBuffer, 10));
	//  String aus ListBox lesen und in INI-Datei schreiben
		if (_dBaseExprList.GetString (Expression, Index, sizeof (Expression)))
			WritePrivateProfileString (Section.Addr (), Buffer, Expression,
									   ProFile.GetProFileName ());
		else
			break;	  // keine weiteren Enträge in ListBox
		Buffer [lstrlen (Buffer) - 1] = '\0';   // Ziffer löschen
	}
}

void __export StandScriptDialog :: ListBoxSel (ControlEvt CE) {
	switch ((uint) CE.GetControlID ()) {
		case IDC_EXPRESSIONLIST:
			_AusfButton.Enable ();
		break;
	}
}

//  Alias-Namen in Textfeld ausgeben
Bool StandScriptDialog :: _OutputAliasNames (void) {
//  prüfe interne Parameter
	if (!pCodeBase || !pDataTree) {
		DEX_Error (RC_StScriptOutAlias, EC_SYSERROR);
		return False;
	}

	short Cnt = (short) pDataTree -> Count ();
	if (!Cnt)
		return True;

	pchar pText = new char [(Cnt * (MAX_FNAME + 2)) + 1];
	if (!pText) {
		DEX_Error (RC_StScriptOutAlias, EC_NOMEMORY);
		return False;
	}
	*pText = '\0';

//  alle Namen auflisten
	CTable Tb (*pDataTree);
	for (Tb.First (); Tb.Valid (); Tb.Next ()) {
		DataIndexLock pData (Tb);
		if (!pData) {
			DEX_Error (RC_StScriptOutAlias, EC_LOCKERROR);
			continue;   // weiter mit nächstem
		}
		if (*pText == '\0')	 // bei 1. Namen
			lstrcpy (pText, pData -> alias.ptr ());
		else {
			lstrcat (pText, ", ");
			lstrcat (pText, pData -> alias.ptr ());
		}
	}

//  Text ausgeben
	_FileName.SetText (pText);

	DELETE_VEC (pText);
	return True;
}

/*
Die alte Version zeigt, wie der vom Datei-Auswahl-Fenster gelieferte
String (multiple Selection) in einzelne vollständige Dateinamen
zerlegt werden muß.
//  DBase-File-Liste erstellen
BOOL FAR PASCAL __export CreateDataTree (pchar pFiles) {
//  prüfe Parameter
	if (!pFiles || !*pFiles) {
		DEX_Error (RC_CreateDataTree, EC_SYSERROR);
		return FALSE;
	}

//  alten Infos löschen
	if (pCodeBase) {
		DELETE (pDataTree);
		DeleteCodeBaseObj ();
		pCodeBase = NULL;
	}

//  neues CodeBase-Objekt erzeugen
	pCodeBase = CreateCodeBaseObj (hInstance);
	if (!pCodeBase) {
		DEX_Error (RC_CreateDataTree, EC_NOMEMORY);
		return FALSE;
	}

	if (pCodeBase -> error () != r4success) {
		DeleteCodeBaseObj ();
		pCodeBase = NULL;
		return FALSE;
	}

//  neuen Baum anlegen
	pDataTree = new DBaseFiles;
	if (!pDataTree) {
		DEX_Error (RC_CreateDataTree, EC_NOMEMORY);
		DeleteCodeBaseObj ();
		pCodeBase = NULL;
		return FALSE;
	}

	const char Sep = ' ';			   // Separator
	const char Ekz = '\0';			  // Textende
	const char BSlash = '\\';
	const char Lw = ':';
	const char SubDir [] = ".\\";		// Beginn eines subdirectorys
	const char ParDir [] = "..\\";	   // Beginn eines parentdirectorys

	char Path [_MAX_PATH] = "";
	char ActFile [_MAX_PATH] = "";
	char Drive [_MAX_DRIVE] = "";
	char Dir [_MAX_DIR] = "";
	char FName [_MAX_FNAME] = "";
	char Ext [_MAX_EXT] = "";
	BOOL Ret = TRUE;

//  lese globalen Path
	pchar pActLZ = strchr (pFiles, Sep);
	if (! pActLZ) {	 // nur eine Datei gegeben
		Ret = pDataTree -> AddDataIndex (pCodeBase, pFiles);
	} else {			// mehrere Dateien gegeben
		*pActLZ = Ekz;
		lstrcpy (Path, pFiles);
		if (Path [lstrlen (Path - 1)] != BSlash)
			lstrcat (Path, "\\");
		_splitpath (Path, Drive, Dir, NULL, NULL);
		*pActLZ = Sep;

	//  dBase-Dateinamen speichern
		for (; pActLZ && *pActLZ; pActLZ = strchr (pActLZ++, Sep)) {
			pchar pActFileEnd = strchr (++pActLZ, Sep); // akt. Namensende
			if (pActFileEnd) {
				*pActFileEnd = Ekz;
				lstrcpy (Path, pActLZ);			 // akt. Namen kopieren
				*pActFileEnd = Sep;
			} else
				lstrcpy (Path, pActLZ);			 // akt. Namen kopieren

		//  Namen bilden:	   // Test auf evtl. Directoryeinträge
			pchar pDir = strchr (Path, Lw);	 // Lw-Kennung
			if (pDir)						   // kompletter Pfad gegeben
				lstrcpy (ActFile, Path);
			else {							  // relative Pfade
				if ((pDir = strstr (Path, ParDir)) ||   // übergeordn. Verz.
					(pDir = strstr (Path, SubDir)))	 // lokales Verz.
					_fullpath (ActFile, pDir, sizeof (ActFile));
				else {						  // "normale" Bildung
					_splitpath (Path, NULL, NULL, FName, Ext);
					_makepath (ActFile, Drive, Dir, FName, Ext);
				}
			}

		//  DataIndex-Objekt erzeugen
			if (! (Ret = pDataTree -> AddDataIndex (pCodeBase, ActFile)))
				break;
		}   // end_for
	}	   // end_else

//  ggf. alles löschen
	if (Ret == FALSE) {
		DELETE (pDataTree);
		DeleteCodeBaseObj ();
		pCodeBase = NULL;
	}

	return Ret;
}
*/

/*
//  Die alte Version
//  DBase-Dateien auswählen:
//  Der zurückgegebene Zeiger mit den Namen der gewählten dBase-Dateien
//  muß explizit wieder freigegeben werden.
char* FAR PASCAL __export SelectdBaseFiles (Window *pParentWindow) {
//  prüfe übergebene Parameter
	if (!pParentWindow) {
		DEX_Error (RC_SelectdBaseFiles, EC_ILLPARS);
		return NULL;
	}

//  prüfe interne Parameter
	if (!pRF) {
		DEX_Error (RC_SelectdBaseFiles, EC_SYSERROR);
		return NULL;
	}

//  alten Infos löschen
	if (pCodeBase) {
		DELETE (pDataTree);
		DeleteCodeBaseObj ();
		pCodeBase = NULL;
	}

	SetdBasePfad ();					// dBase-Pfad einstellen

	ResString Spec (ResID (IDS_DBASESPEC, pRF), 30);
	OpenDialog OD (pParentWindow, (char *) Spec.Addr ());
	OD.AddFlags (OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT);
	ResString Caption (ResID (IDS_SELECTCAPTION, pRF), 30);
	OD.SetCaption (Caption.Addr ());
	OD.SetHookFcn ((HOOKFCN) Init3d);
	OD.Show ();

	Bool Ret = OD.Result ();

//  neuen Namen kopieren
	pchar pFileNames = NULL;
	if (Ret == True) {
		if (pFileNames = new char [OD.GetFileNameLen () + 1])
			OD.GetFileName (pFileNames);
		else {
			DEX_Error (RC_SelectdBaseFiles, EC_NOMEMORY);
			Ret = False;
		}
	}

	return Ret ? pFileNames : NULL;
}
*/
