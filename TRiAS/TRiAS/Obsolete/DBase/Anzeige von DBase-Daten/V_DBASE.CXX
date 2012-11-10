/*-----------------------------------------------------------------------

File: V_DBASE.CXX (Implementation)

View_dBase -
gibt den Inhalt eines dBase-Files satzweise in eine Listbox aus.

Erarbeitet: J. Benkenstein							   am: 19. Dez. 1991
												  Stand vom: 24. Aug. 1993
---------------------------------------------------------------------------*/

#include "pheader.h"

#include "V_DBASE.htp"   // Selektion der zu comp. Klassen
#include <commonvu.hxx>
#include <containr.hxx>

#include <bttncur.h>	 // TOOLDISPLAYDATA
#include <gizmobar.h>    // GIZMO_NORMAL

#include <objfeld.hxx>	 // für "dbliste.hxx"
#include <dbaserel.hxx>	 // für DBaseRel-Klasse
#include <dbtools.hxx>	 // GetFulldBaseName ()

#include "dbase.hxx"	 // dBaseDispatch-Klasse

#include <resstrg.h>	 // ID's f. String-Ressourcen
#include <dbliste.hxx>	 // zugehörige Filter-Klassen
#include <dbtools.hxx>	 // GetOemToAnsiiFlag ()
#include <dbasprof.hxx>	 // DBaseProFile

#include <ixtensn.hxx>	  // ITriasXtension
#include <xtencunk.hxx>	  // CTriasExtension			  
#include <xtsnprop.hxx>	  // CObjectProperties

#include "exttabl.hxx"	  // erweiterte TabularListBox
#include "dbaseext.hxx"	  // nur enum ParamType
                                                            
#include "waitcur.hxx"	  // CWaitCursor
#include "dbaseext.hr"	  // DLL-Defines
#include "afnamel.hxx"	  // CAliasFieldNameTree	
#include "v_memofd.hxx"	  // Inhalt eines Memofeldes anzeigen
#include "gizmobar.hxx"	  // CGizmoBar	
#include "v_dbase.hxx"	  // zugehöriges Header-File

// allg. Konstanten
const short SatzNrSpalten = 4;	 // Satznummern
const short RowBlockDiv   = 5;	 // MaxRow/5 Sätze weiter bei BlockBew.

//  externe Variablen
extern "C" {
extern HINSTANCE g_hInstance;
}

#pragma warning (disable : 4355)
// Listbox für File-Darstellung u.a. Parameter init. --------------------------
ShowFile ::  ShowFile (pWindow pParent,	 	// Zeiger auf Elternfenster
			 CodeBase* pCodeBase,   		// Zeiger auf CodeBase-Basis-Objekt
			 pchar pAliasName,	  			// Alias-Name der Datei
			 pchar pFieldName,	  			// akt. Feld-Name
			 pchar pFieldVal,	   			// akt. Feld-Inhalt
			 dBaseDispatch *Disp,   		// Zeiger auf rufenden dBase-Dispatcher
			 ResourceFile *pResF,   		// Zeiger auf Resource-Datei
			 short ParType,		 // Parameter-Typ
			 Point &TransL)		 // x,y-Verschiebung des Fensters
		  : ModeLessDialog (pParent, ResID (IDD_DBF, pResF)),
			ListRow (this, ResID (IDL_ROW, pResF), 2),
			ListCol (this, ResID (IDL_COLUMN, pResF), 2),
			Menue (ResID (IDM_DBF, pResF)),
			MemoDialog (this, ResID (IDD_MEMO, pResF), pResF)
{                                                       
//	wichtige Init.
	pDisp = NULL;
	pRF = NULL;
	pCBase = NULL;
	_pAliasFieldTree = NULL;           
	pRowGizmoBar = pColGizmoBar = NULL;
	_toDelete = True;			   	// Lösch-Flag setzen    
	RelCount = 0;				   	// Anz. Relationen sowie    
	ppdBaseRel = NULL;			  	// Zeiger auf entspr. Strukutren sind 0
	pRelMenu = NULL;				// Zeiger auf Relations-Menü
	ScrollSize = 0;
	pDON = NULL;
	pData = NULL;
	
//	prüfe Parameter
	if (!pAliasName || !*pAliasName || !pCodeBase || !Disp || !pResF)	
	{
		DEX_Error (RC_ctShowFile, RC = EC_ILLPARS);
		return;
	}

//  Variablen für dBase-Relationen init.           
	RC = EC_OKAY;				   	// Operation OK
	pDisp = Disp;				   	// Zeiger auf Dispatcher
	pRF = pResF;					// ResourceFile merken
	pCBase = pCodeBase;			 	// Zeiger speichern
	_BezBreite = BezSpalten;                         
	
	CWaitCursor wc;		// Sanduhr ein

//  vollst. Dateinamen lesen
	pchar pFullName = GetFulldBaseName (pAliasName);
	if (!pFullName || !*pFullName) 	  // Fehlermeldung ausgegeben
	{
		DEX_Error (RC_ctShowFile, RC = WC_NOTFOUND);
		DELETE_VEC (pFullName);
		return;
	}

//  Memo-Objekt erzeugen
	int iAutoOpen = pCodeBase -> auto_open;				// Index-Datei-Öffnen-Flag speichern
	if (ParType == TagName)
		pCodeBase -> auto_open = True;		
	pData = new DataMemo (pCBase, pFullName);
	pCodeBase -> auto_open = iAutoOpen;					// Flag rücksetzen
	DELETE_VEC (pFullName);
	if (!pData) {
		DEX_Error (RC_ctShowFile, RC = EC_NOMEMORY);
		return;
	}

	if (RC = (ErrCode) pCBase -> error ())	  // CodeBase OK ?
		return;

	pData -> alias = strupr (pAliasName);	   // Namen setzen
	if (lstrlen (pAliasName) > (short) pData -> alias.maximum ()) {
		DEX_Error (RC_ctShowFile, WC_ALIASNAMETOLONG);
	}
	
	pDON = new DBaseObjNummer (0);
	if (!pDON) {
		DEX_Error (RC_ctShowFile, RC = EC_NOMEMORY);
		return;
	}

//  Sätze filtern
	switch (ParType) {
		case TagName: {
			DB_Filter DBF (pCBase, *(DataIndex *)pData, *pDON, pFieldName, pFieldVal);
			if ((RC = DBF.Result ()) == EC_OKAY)
				RC = DBF.Check ();			  // nicht OR, nicht unique
		}
		break;
		case dBaseExpr: {
			DB_Filter DBF (pCBase, *(DataIndex *)pData, *pDON, NULL, NULL, pFieldName);
			if ((RC = DBF.Result ()) == EC_OKAY)
				RC = DBF.Check ();			  // nicht OR, nicht unique
		}
		break;
		case FeldName:
		default: {
			DB_Filter DBF (pCBase, *(DataIndex *)pData, pFieldName, pFieldVal, *pDON);
			if ((RC = DBF.Result ()) == EC_OKAY)
				RC = DBF.Check ();			  // nicht OR, nicht unique
		}
	}

	if (RC != EC_OKAY) {
		if (RC == WC_NOTFOUND)
			DEX_Error (RC_ctShowFile, WC_NOTFOUND);
		return;
	}
	
//  Zeichen-Konvertierungsflag lesen
	_OemToAnsii = GetOemToAnsiiFlag ();
	
//	Alias-Feld-Namen-Baum erzeugen
	_pAliasFieldTree = new CAliasFieldNameTree;
	if (!_pAliasFieldTree)
	{
		DEX_Error (RC_ctShowFile, RC = EC_NOMEMORY);	
		return;
	}	
	
//	lese alle Einträge in Baum	
	if (_pAliasFieldTree -> Init (pAliasName))
		_BezBreite = max (_BezBreite, _pAliasFieldTree -> GetMaxAliasSize () + 3);
	else		
		DELETE_OBJ (_pAliasFieldTree);		// Baum sofort löschen
	
//  Hilfe-Parameter init.
//	pHD = pHelp;			 // Zeiger merken
//	EnableHelp (True, pHD);  // Hilfe erlauben

//  GizmoBar für Zeilendarstellung erzeugen
	if (! _CreateRowGizmoBar ()) {
		DEX_Error (RC_ctShowFile, EC_SYSERROR);
		RC = EC_SYSERROR;
		return;
	}
//  GizmoBar für Spaltendarstellung erzeugen
	if (! _CreateColGizmoBar ()) {
		DEX_Error (RC_ctShowFile, EC_SYSERROR);
		RC = EC_SYSERROR;
		return;
	}
                         
	ListRow.SetColWidth (0, _BezBreite);	// Spaltenbreite einstellen
	ListCol.SetColWidth (0, SatzNrSpalten); // Spaltenbreite einstellen

//  Position des Fensters ggf. korrigieren
	Point ActPos = GetPosition ();	   // l. u. Ecke verschieben
	ActPos.X () += TransL.X ();
	ActPos.Y () += TransL.Y ();
	ChangePosition (ActPos);

//  Größe und Position der Listboxen ändern
	ListRow.ChangePosition (Point (0,0));
	ListCol.ChangePosition (Point (0,0));
	Rectangle Rect = CanvasRect ();
	Dimension Dim (Rect.Right () - Rect.Left (),
				   Rect.Top () - Rect.Bottom () -
				   pRowGizmoBar -> Height ());
	ListRow.ChangeSize (Dim);
	ListCol.ChangeSize (Dim);

	_ChangeButtons (True);	   // richtigen Buttons einstellen
		
	_toDelete = False;		   //  Lösch-Flag rücksetzen
}
#pragma warning (default : 4355)

// Fenster Darstellen
void  ShowFile :: Darstellen ()
{
	RC = EC_OKAY;

//  berechne maximale Feldlänge
	NewActRow = NewActCol = 1;
	ActCol = 0;
	ActRow = 0;

//  max. Anz. Sätze ermitteln
	MaxRow = pDON -> RA ().Count();

	if (!MaxRow)   // wenn kein gültigen Eintrag gefunden
	{
		DEX_Error (RC_DarstShowFile, RC = WC_NOTFOUND);
		_toDelete = True;
		return;
	}

	ScrollSize = MaxRow / RowBlockDiv;
	if (ScrollSize == 0)
		ScrollSize++;			  // wenigstens 1 Zeile weiter	
	MaxCol = pData->num_fields(); // Anz. Spalten

	Str10 Bez;
	short FieldColumns = FeldSpalten;
	for (register int i = 1, j = pData->num_fields();
		i <= j; i++) // für alle Felder eines Satzes
	{
		if (pData->field(i)->type() != 'M' && pData->field(i)->len() > FeldSpalten)		// max. Feldlänge
			 FieldColumns = pData->field(i)->len();
		Bez = pData->field(i)->name;				// Feldname
		if (_OemToAnsii)
			OemToAnsi (Bez.ptr(), Bez.ptr ());	   // dt. Umlaute ersetzen

			// einsortieren
		if (pColGizmoBar -> ComboBoxAddString (IDC_FIELDNAMES, Bez.ptr ()) == -1)
			break;
	}

	ListRow.SetColWidth (1, FieldColumns);
	ListCol.SetColWidth (1, FieldColumns);		
                                              
//  Sicht-Flag akt.
	OneRow = True;	  // Zeilen-Ansicht

	pRowGizmoBar -> DisableGizmo (IDM_FIRSTSCROLL);
	pRowGizmoBar -> DisableGizmo (IDM_BIGLEFTSCROLL);
	pRowGizmoBar -> DisableGizmo (IDM_ONELEFTSCROLL);
	if (MaxRow < 2)	 // alle weiteren Gizmos ggf. deaktiv.
		for (uint ID = IDM_ONERIGHTSCROLL; ID < IDM_ONERIGHTSCROLL + 3; ID++)
			pRowGizmoBar -> DisableGizmo (ID);

//  1. Spalte wird dargestellt
	pColGizmoBar -> DisableGizmo (IDM_PREVFIELD);

//  SrollBalken für beide Listboxen aktivieren
	short TabPos [2];       
	TabPos [0] = _BezBreite;
	TabPos [1] = FieldColumns;
	ListRow.SetHorzScroll (2, TabPos);

	TabPos [0] = SatzNrSpalten;
	TabPos [1] = FieldColumns;
	ListCol.SetHorzScroll (2, TabPos);
                
/*                
//  Horiz. Scrollbalken gesetzt ?
	long dwStyle = GetWindowLong (ListRow.Handle (), GWL_STYLE);
	CoOrd ScrollHoehe = 0;
	if (dwStyle & WS_HSCROLL)
		ScrollHoehe = (CoOrd) GetSystemMetrics (SM_CYHSCROLL);

//  Größe  ggf. korrigieren
	Rectangle CanvRect = CanvasRect ();
	CoOrd CanvHoehe = CanvRect.Top () - CanvRect.Bottom () -
					  pRowGizmoBar -> Height () - ScrollHoehe;
	Dimension Dim = TextSize ("X");
	CoOrd TextHoehe = Dim.Height ();
	if (CanvHoehe > ((MaxCol+1) * TextHoehe)) // ggf. verkleinern
	{
		Dim = GetSize ();		   // akt. Dialog-Fenster-Größe
		Dim.Height () = Dim.Height () - (CanvRect.Top () - CanvRect.Bottom ())
						+ ((MaxCol + 1) * TextHoehe) + ScrollHoehe
						+ pRowGizmoBar -> Height ();
		ChangeSize (Dim);		   // Dialog-Fenster-Größe ändern
									// ReSize wird gerufen
	}
*/	

	ChangeMenu (&Menue);

	_ShowRow ();			  // 1. Satz in Listbox ausgeben

//  Fenster darstellen
	Show ();
}

// Button-Event-Handler
void __export ShowFile :: ButtonClick (ControlEvt ce)
{
	switch (uint(ce.GetControlID()))	// lese Button-ID
	{
		case IDB_ROW:
		case IDB_COLUMN:
			_SwitchRowColumn ();
		break;
	}
}

ShowFile :: ~ShowFile (void)
{           
	DELETE_OBJ (_pAliasFieldTree);
	DELETE_OBJ (pRowGizmoBar);
	DELETE_OBJ (pColGizmoBar);
	DELETE_OBJ (pDON);
	DELETE_OBJ (pData);
	_DeleteRelMenu ();
	_DeleteOldRelations ();
}

// Event-Handler behandelt Listbox-Doppel-Click
void __export ShowFile :: ListBoxClk (ControlEvt CE)
{
   int Index;   // akt. Listbox-Index

   switch (uint (CE.GetControlID ()))
   {
	  case IDC_FIELDNAMES:
	  {
		 Index = pColGizmoBar -> ComboBoxGetCurrentIndex (IDC_FIELDNAMES);
		 if ((Index >= 0) && (Index < MaxCol))
		 {
			NewActCol = ++Index;
			_ShowColumn ();
		 }
	  }
	  break;
	  case IDL_ROW:
	  {
		 Index = ListRow.GetCurrentIndex ();
		 if ((Index >= 0) && (Index < MaxCol))  // innerhalb des Bereiches
		 {
			NewActCol = ++Index;
			if ((pData->field(Index)->type() == 'M') && // wenn MemoFeld u.
				(pData->validate_memo_ids () == 0))	   // ID's ok
			{
				Field *pField = pData -> field (Index);
				Str10 Bez = pField -> name;			   // Feldname
				if (_OemToAnsii)
					OemToAnsi (Bez.ptr(), Bez.ptr());	 // dt. Umlaute ersetzen
				String Inh (pCBase);
				Inh.set_max (pField -> len () + 1);	   // max. Länge setzen
				Inh = *pField;							// Feld kopieren
				Inh.null_ensure ();					   // Nullendung sichern
				if (Inh.len ())
				{
				   if (_OemToAnsii)
						OemToAnsi (Inh.ptr(), Inh.ptr());
				   MemoDialog.SetCaption (Bez.ptr());

				// NewLine filtern
				   Bez.assign ("\xEC\x0A");
				   Str10 ReplaceStr ("\x0D\x0A");
				   for (register int Pos = Inh.search (Bez); Pos > 0; Pos = Inh.search (Bez))
						Inh.replace (ReplaceStr, Pos);

				   MemoDialog.MultiLine.SetText (Inh.ptr ());
				   MemoDialog.Show ();
				}
				else
				{
				   ResString LeerText (ResID (IDS_EMPTYMEMO, pRF), 40);
				   MessBox MB (Bez.ptr (), (char *) LeerText.Addr (), this);
				   MB.SetType (AsteriskIcon);
				   MB.Show ();
				}
			}
			else
			{
				OneRow = False;		 // Spaltenansicht
				_ShowColumn ();
				_ChangeButtons (False); // Menüs für Spalte tauschen
				pColGizmoBar -> EnableGizmo (IDM_NEXTFIELD);
				pColGizmoBar -> EnableGizmo (IDM_PREVFIELD);
			}
		 }
	  }
	  break;
	  case IDL_COLUMN:
	  {
		 Index = ListCol.GetCurrentIndex ();
		 if ((Index >= 0) && (Index < MaxRow))  // innerhalb des Bereiches
		 {
			NewActRow = ++Index;
			OneRow = True;			  // Spaltenansicht
			_ShowRow ();
			_ChangeButtons (True);	  // Buttons für Zeile tauschen
		 }
	  }
	  break;
   }
}

void __export ShowFile :: ListBoxSel (ControlEvt CE)
{
	short Index;

	switch (uint (CE.GetControlID ()))
	{
		case IDC_FIELDNAMES:
		{
			Index = pColGizmoBar -> ComboBoxGetCurrentIndex (IDC_FIELDNAMES);
			if ((Index >= 0) && (Index < MaxCol))
			{
			   NewActCol = ++Index;
			  _ShowColumn ();
			}
		}
		break;
		case IDL_ROW:
		case IDL_COLUMN:
			_ReadDBaseRel ();  // dBase-Relationen neu lesen
		break;
	}
}

// Neuzeichen der Clientarea nach Gräßenänderung
void __export ShowFile :: ReSize (ReSizeEvt RSE) {
	if (OneRow)  // bei Einzelsatzanzeige
		ListRow.Hide ();
	else
		ListCol.Hide ();

	ListRow.ChangePosition (Point (0,0));
	ListCol.ChangePosition (Point (0,0));
	Dimension Dim (RSE.GetNewWidth (), RSE.GetNewHeight () -
									   pRowGizmoBar -> Height ());
	ListRow.ChangeSize (Dim);
	ListCol.ChangeSize (Dim);

//  Größen der ToolBars ändern
	pRowGizmoBar -> ReSize (RSE.GetNewWidth ());
	pColGizmoBar -> ReSize (RSE.GetNewWidth ());

	if (OneRow)  // bei Einzelsatzanzeige
		ListRow.Show ();
	else
		ListCol.Show ();
}

Bool __export ShowFile :: QueryClose (Event) 
{
	DELETE_OBJ (_pAliasFieldTree);
	DELETE_OBJ (pDON);
	DELETE_OBJ (pData);
	_DeleteRelMenu ();
	_DeleteOldRelations ();

	_toDelete = TRUE;   // Fenster beseitigen

	return True;		// immer zu machen
}

// Aktualisierung des Menüs
void __export ShowFile :: MenuInit (MenuInitEvt)
{
	if (OneRow)								 // bei Zeilen-Darst.
	{                   
		Menue.EnableItem (IDM_AKT_ALIAS_FILE);  // akt. der Zeile-Darstellung
	
	// 	evtl. Index erzeugen möglich
		short sIndex = ListRow.GetCurrentIndex ();
		if (sIndex >= 0)
		{
			Field *pField = pData -> field (sIndex + 1);
			if (pField && pField -> type () != 'L'	// für logische
				  && pField -> type () != 'M')   // und Memo kein Index
				Menue.EnableItem (IDM_CREATE_INDEX); 
			else
				Menue.DisableItem (IDM_CREATE_INDEX);
		}
		else                                    
			Menue.DisableItem (IDM_CREATE_INDEX);						
	
	//  MenuItem für Zeilen-Darst. ändern
		ResString RowText (ResID (IDS_ZEILENTEXT, pRF), 10);
		ModifyMenu (Menue.Handle (API_MENU_HMENU), IDM_ROWCOL,
					MF_BYCOMMAND | MF_STRING, IDM_ROWCOL, RowText);

	//  MenüItems aktiv./deakt.
		if (ActRow > 1)
			Menue.EnableItem (IDM_ONELEFTSCROLL);
		else
			Menue.DisableItem (IDM_ONELEFTSCROLL);

		if (ActRow < MaxRow)
			Menue.EnableItem (IDM_ONERIGHTSCROLL);
		else
			Menue.DisableItem (IDM_ONERIGHTSCROLL);
		Menue.DisableItem (IDM_PREVFIELD);
		Menue.DisableItem (IDM_NEXTFIELD); 
	}                           
	else  // Spaltenansicht
	{                                         
		Menue.DisableItem (IDM_AKT_ALIAS_FILE);		// kein aktual. möglich
	   
	//	hier kein Index erzeugen möglich
		Menue.DisableItem (IDM_CREATE_INDEX);
				
	//  MenuItem für Spalten-Darst. ändern
		ResString ColText (ResID (IDS_SPALTENTEXT, pRF), 10);
		ModifyMenu (Menue.Handle (API_MENU_HMENU), IDM_ROWCOL,
					MF_BYCOMMAND | MF_STRING, IDM_ROWCOL, ColText);

	//  MenüItems aktiv./deakt.
		if (ActCol > 1)
			Menue.EnableItem (IDM_PREVFIELD);
		else
			Menue.DisableItem (IDM_PREVFIELD);

		if (ActCol < MaxCol)
			Menue.EnableItem (IDM_NEXTFIELD);
		else
			Menue.DisableItem (IDM_NEXTFIELD);
		Menue.DisableItem (IDM_ONERIGHTSCROLL);
		Menue.DisableItem (IDM_ONELEFTSCROLL);
	}                   
	
// 	unabhängig von Ansichtsart
	DBaseProFile ProFile;
	char *pFileName = ProFile.GetAliasFileName (pData -> alias.ptr ());
	if (pFileName)
		Menue.EnableItem (IDM_CHANGE_ALIAS_FILE);
	else
		Menue.DisableItem (IDM_CHANGE_ALIAS_FILE);						
	DELETE_VEC (pFileName);		
}

// Menü-Event-Handler
void __export ShowFile :: MenuCommand (MenuCommandEvt mce)
{   
	switch (uint(mce.GetItemID ()))	 // lese Menü-ID
	{         
		/*
		case IDM_AKT_ALIAS_FILE: {	//  Zeilen-Darstellung akt.
			_ActRow ();
		}              
		break;
		*/
		case IDM_SET_ALIAS_FILE: {		// neue Alias-Datei über Dialog auswählen
			SetdBasePfad ();				// Pfad einstellen
			_SetAliasFile ();
		}
		break;
		case IDM_CREATE_ALIAS_FILE: {	// Alias-Datei erzeugen
			if (_CopyFieldAliasNames ())
			{                         
				char CmdLine [40] = "";
				char Buffer [30] = "";
				ResString Text (ResID (IDS_CLIPOPTION, pRF), 5);
				SetdBasePfad ();				// Pfad einstellen
				wsprintf (CmdLine, "%s %s", GetEditName (Buffer,
									sizeof (Buffer)), Text.Addr ());
				RunTriasEdit (this, CmdLine, SW_SHOWNORMAL);
			}	
		}		
		break;
		case IDM_CHANGE_ALIAS_FILE:	{	// Alias-Datei ändern
			DBaseProFile ProFile;
			char *pFileName = ProFile.GetAliasFileName (pData -> alias.ptr ());
			if (!pFileName)
				break;            
				
		//	Editor besorgen				
			char Buffer [30] = "";					
			GetEditName (Buffer, sizeof (Buffer));							
        	char *pCmdLine = new char [lstrlen (Buffer) + lstrlen (pFileName) + 5];
        	if (!pCmdLine)
        	{                      
				DEX_Error (RC_ctShowFile, EC_NOMEMORY);        		      
        		DELETE_VEC (pFileName);
        		break;
        	}                 
        	
		// 	Commando-Zeile zusammenbauen        	
        	lstrcpy (pCmdLine, Buffer);
        	lstrcat (pCmdLine, " ");
        	lstrcat (pCmdLine, pFileName);
			RunTriasEdit (this, pCmdLine, SW_SHOWNORMAL);
			          
		//	Speicher freigeben			          
			DELETE_VEC (pFileName);
			DELETE_VEC (pCmdLine);
		}
		break;
		case IDM_FIRSTSCROLL: {
			NewActRow = 1;
			_ShowRow ();
		}
		break;
		case IDM_LASTSCROLL: {
			NewActRow = MaxRow;
			_ShowRow ();
		}
		break;
		case IDM_ONELEFTSCROLL: {
			NewActRow--;
			_ShowRow ();
		}
		break;
		case IDM_ONERIGHTSCROLL: {
			NewActRow++;
			_ShowRow ();
		}
		break;
		case IDM_BIGLEFTSCROLL: {
			NewActRow = max (1, NewActRow - ScrollSize);
			if (NewActRow < 1)
				NewActRow = 1;
			_ShowRow ();
		}
		break;
		case IDM_BIGRIGHTSCROLL: {
			NewActRow = min (MaxRow, NewActRow + ScrollSize);
			if (NewActRow > MaxRow)
				NewActRow = MaxRow;
			_ShowRow ();
		}
		break;
		case IDM_FIRSTENTRY:
		case IDM_FIRSTROW:
		case IDM_FIRSTCOL:
		{			  
			_DeleteRelMenu ();
			_DeleteOldRelations ();
			if (OneRow)
				ListRow.ChangeCurrentIndex (0);
			else
				ListCol.ChangeCurrentIndex (0);
		}						
		break;
		case IDM_LASTENTRY:
		case IDM_LASTROW:
		case IDM_LASTCOL:		  
		{			  
			_DeleteRelMenu ();
			_DeleteOldRelations ();
			if (OneRow)
						ListRow.ChangeCurrentIndex (ListRow.GetCount()-1);
			else
						ListCol.ChangeCurrentIndex (ListCol.GetCount()-1);
		}				
		break;
		case IDM_NEXTFIELD:
			_NextEntry ();	  // nächsten Eintrag einstellen
		break;
		case IDM_PREVFIELD:
			_PrevEntry ();	  // vorigen Eintrag darstellen
		break;
		case IDM_ROWCOL:
			_SwitchRowColumn ();
		break;
		case IDM_COPY:	// nur Menü-Punkt
		{				 // Inhalt der akt. Listbox ins Clipboard kopieren
			if (OneRow)
				_ListToClip (ListRow);
			else
				_ListToClip (ListCol);
		}
		break;			// nur Menü-Punkt
		case IDM_CREATE_INDEX:	
		{	// Index für dieses Feld erzeugen
			_CreateIndex ();
		}
		break;
		case IDM_VDBASE_HELP:
			// pHD->Show (IDM_VDBASE_HELP);		// Hilfe anfordern
		break;
		default:
		{
			if (ppdBaseRel)	 // wenn dBase-Relation aufgebaut
			{
				short Item = mce.GetItemID () - IDM_REL;
				if (Item >= 0 && Item < RelCount)
					pDisp -> ShowDBaseWindowField (
										   ppdBaseRel [Item] -> GetDBName (),
										   ppdBaseRel[Item] -> GetFieldName(),
										   FieldVal.ptr (), pRF, FeldName);
			}
		}
		break;
	}
}

// Gizmobar-Events
void __export ShowFile :: Default (Event e) {
	CNakedEvent ne ((CNakedEvent &) e);
	if (ne.Msg () == WM_COMMAND)
		MenuCommand ((MenuCommandEvt &) e);
	else
		EventContext :: Default (e);
}

//  GizmoBar für Zeilenanzeige erzeugen
Bool ShowFile :: _CreateRowGizmoBar (void) {
//  prüfe Parameter
	if (! pRF)
		return False;

	pRowGizmoBar = CGizmoBar :: CreateGizmoBar (g_hInstance, this, ID_ROWGIZMOBAR);
	if (! pRowGizmoBar) {
		RC = EC_NOMEMORY;
		return False;
	}

//  Bitmap laden
	if (! pRowGizmoBar -> ReadBitmap (ID_TOOLBARS72))
		return False;

//  FirstEntry
	if (! pRowGizmoBar -> CreateCommandButton (IDM_FIRSTROW, 6))
		return False;

//  LastEntry
	if (! pRowGizmoBar -> CreateCommandButton (IDM_LASTROW, 7))
		return False;

//  Separator
	if (! pRowGizmoBar -> CreateSeparator (ID_SEPARATOR1))
		return False;

//  Gizmos für vert. Scrollbalken
	for (uint i = 0, ID = IDM_FIRSTSCROLL; i < 6; i++, ID++)
		if (! pRowGizmoBar -> CreateCommandButton (ID, i))
			return False;

//  Separator
	if (! pRowGizmoBar -> CreateSeparator (ID_SEPARATOR2))
		return False;

	ResString RowText (ResID (IDS_ZEILENTEXT, pRF), 10);
	return pRowGizmoBar -> CreateTextButton (IDB_ROW, (char *) RowText.Addr (),
									   pRowGizmoBar -> ButtonWidth () * 2);
}

//  GizmoBar für Spaltenanzeige erzeugen
Bool ShowFile :: _CreateColGizmoBar (void) {
//  prüfe Parameter
	if (! pRF)
		return False;

	pColGizmoBar = CGizmoBar :: CreateGizmoBar (g_hInstance, this,
												ID_COLGIZMOBAR);
	if (! pColGizmoBar) {
		RC = EC_NOMEMORY;
		return False;
	}

//  Bitmap laden
	if (! pColGizmoBar -> ReadBitmap (ID_TOOLBARS72))
		return False;

//  FirstEntry
	if (! pColGizmoBar -> CreateCommandButton (IDM_FIRSTCOL, 6))
		return False;

//  LastEntry
	if (! pColGizmoBar -> CreateCommandButton (IDM_LASTCOL, 7))
		return False;

//  Separator
	if (! pColGizmoBar -> CreateSeparator (ID_SEPARATOR3))
		return False;

//  voriges Feld
	if (! pColGizmoBar -> CreateCommandButton (IDM_PREVFIELD, 2))
		return False;

//  nächstes Feld
	if (! pColGizmoBar -> CreateCommandButton (IDM_NEXTFIELD, 3))
		return False;

//  Separator
	if (! pColGizmoBar -> CreateSeparator (ID_SEPARATOR4))
		return False;

//  ComboBox mit Feldnamen
	if (! pColGizmoBar -> CreateListBox (IDC_FIELDNAMES,
										 pColGizmoBar -> ButtonWidth () * 5))
		return False;

//  Separator
	if (! pColGizmoBar -> CreateSeparator (ID_SEPARATOR5))
		return False;

//  Text-Button: "Zeile"
	ResString ColText (ResID (IDS_SPALTENTEXT, pRF), 10);
	return pColGizmoBar -> CreateTextButton (IDB_COLUMN,
						   (char *) ColText.Addr (), 
						   pColGizmoBar -> ButtonWidth () * 2);
}
 
//	Index für das aktuelle Feld erzeugen 
void ShowFile :: _CreateIndex (void)
{          
	short sIndex = ListRow.GetCurrentIndex ();
	if (sIndex < 0)
		return;

	CWaitCursor wc;		// Sanduhr ein

//	Namen der Index-Datei zusammenbauen
	char Drive    [_MAX_DRIVE] = "";
	char Dir	  [_MAX_DIR] = "";	
	char FName    [_MAX_FNAME] = "";
	char FileName [_MAX_PATH] = "";
	pchar pFullName = GetFulldBaseName (pData -> alias.ptr ());	
	if (!pFullName || !*pFullName) 	  // Fehlermeldung ausgegeben
	{
		DEX_Error (RC_ctShowFile, RC = WC_NOALIASNAMESFOUND);
		DELETE_VEC (pFullName);
		return;
	}
	_splitpath (pFullName, Drive, Dir, FName, NULL);
	_makepath (FileName, Drive, Dir, FName, NULL);
	DELETE_VEC (pFullName);
	
//	TagInfo zusammen bauen
	Str10 FieldName = pData -> field (sIndex + 1) -> name;
	TagInfo tag_info [] = 
	{ 
		{ FieldName.ptr (), FieldName.ptr (), NULL, 0 /*r4unique_continue*/, 0},
		{ NULL, NULL, NULL, 0, 0}	
	}; 
	
	int iOpenErr = pCBase -> open_error;		// Flags speichern
	int iTagNameErr = pCBase -> tag_name_error;         
	pCBase -> open_error = False;              
	pCBase -> tag_name_error = False;
	
	Index Ind (pData, NULL);     
	ResString Caption (ResID (IDS_INDEX_CAPTION, pRF), 20);		
	
//	Existiert Index-Datei ?	
	if (Ind.open (FileName) == r4success)				// Datei geöffnet
	{
		if (pData -> tag (FieldName.ptr (), &Ind) != 0)	// Tag vorh.
			Ind.reindex ();								// alle Tags neu indizieren			
		else
		{//	Die Index-Datei beinhaltet bereits einen anderen Index !
			ResString OneIndex (ResID (IDS_ONE_INDEX, pRF), 60);
			MessBox MB (Caption.Addr (), OneIndex.Addr (), this);
			MB.SetType (AsteriskIcon);
			MB.Show ();
		}
	}
	else							
	{//	existiert Datei ?		
		OFSTRUCT of;
		_makepath (FileName, Drive, Dir, FName, INDEX_EXTENSION);
		if (OpenFile (FileName, &of, OF_EXIST) == HFILE_ERROR)	
		{
			_makepath (FileName, Drive, Dir, FName, NULL);
			Ind.create (FileName, tag_info);			// Index-Datei u. Tag erzeugen
		}			
		else
		{// bestehende Index-Datei kann nicht verändert werden !
			ResString OtherIndex (ResID (IDS_OTHER_INDEX, pRF), 60);
			MessBox MB (Caption.Addr (), OtherIndex.Addr (), this);
			MB.SetType (AsteriskIcon);
			MB.Show ();
		}
	}		
	                           
	Ind.close ();									// Index-Datei schließen	                           
	pCBase -> open_error = iOpenErr;				// alte Flags zurück
	pCBase -> tag_name_error = iTagNameErr;                      
}                                

