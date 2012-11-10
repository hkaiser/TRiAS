/*
Datei: EXPREING.CXX
Dialog zur Eingabe und zum Prüfen eines dBASE-Ausdrucks.

Erarbeitet: J.Benkenstein			   Stand vom: 29.06.1995
*/

#include <d4all.h>

extern "C" {
	#include <stdarg.h>			// va_list u.a.
	#include "dbasedll.hr"   // Resourcen-Defines
}

#include "expreing.htp"	 	// Klassenselektion
#ifdef WIN32
#include <bool.h>
#endif
#include <commonvu.hxx>
#include <containr.hxx>
#include <dbliste.hxx>	  	// DBaseFiles
#include <dbtools.hxx>	  	// CheckdBaseExpression ()	
#include <expreing.hxx>	 	// zugeh. Header
#ifndef WIN32
#include <storage.h>		// LPSTORAGE
#include <string.h>			// strstr ()
#endif
#include <xtension.h>	   	// für DEX_Error (), DEX_SetError ()
#include <xtensnx.h>
#include <errinstx.hxx>	 	// ErrInstall
#include <protos.h>			// DELETE ()

//  externe Variablen
extern "C" {
	extern char pDLLName [_MAX_PATH];	// Name der Bibliothek
}
ResourceFile *pRF = NULL;

//  Konstanten
const short FileNameSize = 8;
const short FieldNameSize = 10;
const short FieldQualiSize = 4;
								// max. Größe einer Zeile in FeldListe
const short FieldSize = FileNameSize + FieldNameSize + FieldQualiSize;

//  Struktur einer Liste vereinbaren
typedef struct {
	pchar pContents;
	pchar pComment;
} LISTE;

const LISTE OperatorList [] = {
//  Operatoren-Liste
	{   "+", "Numerische Addition oder Texte verbinden, z.B.: \"A  \"+\"B\" wird \"A  B\"."},
	{   "-", "Numerische Subtraktion oder Texte verbinden, z.B.: \"A  \"-\"B\" wird \"AB\"."},
	{   "*", "Numerische Multiplikation."},
	{   "/", "Numerische Division."},
	{   "^", "Numerische Potenzierung."},
	{   "=", "Werte sind gleich."},
	{   "#", "Werte sind verschieden."},
	{   "<", "Wert ist kleiner."},
	{   ">", "Wert ist größer."},
	{   "<=", "Wert ist kleiner oder gleich."},
	{   ">=", "Wert ist größer oder gleich."},
	{   "$", "Text ist enthalten in, z.B.: \"AB\" $ \"ABCD\" ist wahr."},
	{   ".NOT.", "Logische Verneinung."},
	{   ".AND.", "Logisches UND."},
	{   ".OR.", "Logisches ODER."}
};

const LISTE FunctionList [] = {
//  Liste der benutzten Funktionen
	{   "CTOD()", "Konvertiert Zeichenwert in Datumswert, z.B.: CTOD (\"11/30/80\")."},
	{   "DATE()", "Gibt das Systemdatum zurück."},
	{   "DAY()", "Gibt den Tag des Datums als Zahl zurück."},
	{   "DEL()", "Wenn der aktuelle Satz zum Löschen markiert ist, wird \"*\" ansonsten \" \" zurückgegeben."},
	{   "DELETED()", "Gibt .TRUE. zurück, wenn der aktuelle Satz zum Löschen markiert ist."},
	{   "DTOC()", "Konvertiert Datumswert in Zeichenwert, z.B.: DTOC (DATE ()) gibt den Wert \"22/10/93\" zurück."},
	{   "DTOS", "Konvertiert Datumswert in Zeichenwert, z.B.: DTOS (DATE ()) gibt den Wert \"19931022\" zurück."},
	{   "IFF(,,)", "Ist der 1. Parameter wahr, wird der 2. Parameter zurückgegeben ansonsten der 3.."},
	{   "MONTH()", "Gibt den Monat des Datums als Zahl zurück, z.B. MONTH (DATE ())."},
	{   "RECCOUNT()", "Gibt die Anzahl der Datensätze in der Datenbank zurück."},
	{   "RECNO()", "Gibt die Satznummer des aktuellen Datensatzes zurück."},
	{   "STOD()", "Konvertiert Zeichenwert in Datumswert, z.B.: STOD (\"19931022\")."},
	{   "STR(,,)", "Konvertiert numerischen Wert in Zeichenwert, z.B.: STR (5.7,4,2) erzeugt \"5.70\"."},
	{   "SUBSTR(,,)", "Gibt einen Teiltext aus einem Zeichenwert zurück, z.B.: SUBSTR (\"ABC\",2,1) erzeugt \"B\"."},
	{   "TIME()", "Gibt die Sytemzeit als Zeichenwert zurück, z.B.: \"12:00:00\"."},
	{   "TRIM()", "Abschließende Leerzeichen am Zeichenwert abschneiden, z.B. aus TRIM (\"AB  \") wird \"AB\"."},
	{   "UPPER()", "Großbuchstaben eines Zeichenwertes erzeugen, z.B. aus UPPER (\"ab\") wird \"AB\"."},
	{   "VAL()", "Konvertiert Zeichenwert in numerischen Wert, z.B. aus VAL (\"10\") wird 10."},
	{   "YEAR()", "Gibt das Jahr des Datums als Ziffer zurück, z.B.: YEAR (DATE ())."}
};

//  globale Funktionen
extern "C" {
	int _cdecl __export ExprErrHandler (int ErrCode, int RoutCode, ...);
}

//  globale Funktionen -----------------------------------------------------
extern "C" {
int _cdecl __export ExprErrHandler (int ErrCode, int RoutCode, ...) {
	MessageBeep (0);
	va_list VarList;
	va_start (VarList, RoutCode);
	void *pD = va_arg (VarList, void*);	// 3. Parameter ign.
	FixedText *pInfoText =  va_arg (VarList, FixedText *);
	va_end (VarList);

	if (pInfoText && pRF) {
		ResString ErrText (ResID (IDS_ALLGERROR, pRF), 80);
		switch (ErrCode) {
			case e4field_name:
				ErrText = ResString (ResID (IDS_UNFIELDNAME, pRF), 80);
			break;
			case e4unterminated:
				ErrText = ResString (ResID (IDS_STRINGNOTCLOSED, pRF), 80);
			break;
			case e4unrec_value:
				ErrText = ResString (ResID (IDS_UNKNOWNVALUE, pRF), 80);
			break;
			case e4unrec_operator:
				ErrText = ResString (ResID (IDS_UNKNOWNOPERT, pRF), 80);
			break;
			case e4unrec_function:
				ErrText = ResString (ResID (IDS_UNKNOWNFCTN, pRF), 80);
			break;
			case e4type:
				ErrText = ResString (ResID (IDS_UNKNOWNOPERD, pRF), 80);
			break;
			case e4right_missing:
				ErrText = ResString (ResID (IDS_KLAMMEREXPEC, pRF), 80);
			break;
			case e4overflow:
				ErrText = ResString (ResID (IDS_TOCOMPLEX, pRF), 80);
			break;
			case e4num_parms:
				ErrText = ResString (ResID (IDS_PARAMERROR, pRF), 80);
			break;
			case e4data_name:
				ErrText = ResString (ResID (IDS_OPENERROR, pRF), 80);
			break;
			case e4complete:
				ErrText = ResString (ResID (IDS_UNCOMPLETE, pRF), 80);
			break;
			case e4comma_expected:
				ErrText = ResString (ResID (IDS_KOMMAORKLA, pRF), 80);
			break;
			default:
			break;
		}

		pInfoText -> SetText (ErrText.Addr ());
	}

	return ErrCode;
}
}   //  extern "C"


#pragma warning (disable : 4355)
//  EntryExpression ---------------------------------------------------------
__export EntryExpression :: EntryExpression (pWindow pParent,	// Eltern-Fenster
							CodeBase *pCodeBase,				// CodeBase-Klasse
							DBaseFiles *pDataTree,  			// Liste der dbf-Dateien
							pchar pExpression,	  				// opt. dBASE-Expression
							short ExpressionSize)   			// opt. Expression-Größe
: DialogWindow (pParent, ResID (IDD_ENTRYEXPRESSION, (pRF = new ResourceFile (pDLLName)))),
_FieldList (this, ResID (IDL_FIELDS, pRF)),
_FunctionList (this, ResID (IDL_FUNCTIONS, pRF)),
_OperatorList (this, ResID (IDL_OPERATORS, pRF)),
_ExprLine (this, ResID (IDE_EXPRESSION, pRF)),
_InfoText (this, ResID (IDT_EXPRESSIONINFO, pRF)),
_OKButton (this, ResID (IDOK, pRF)),
_CheckButton (this, ResID (IDB_CHECK, pRF)) {
//  Variablen prüfen und speichern
	if (!pCodeBase || !pDataTree || !pDataTree -> Count ()) 
	{
		_OpFlag = False;
		DEX_Error (RC_ctEntryExpression, EC_ILLPARS);
		return;
	}

//  CodeBase OK ?
	if (pCodeBase -> error () != r4success) 
	{
		_OpFlag = False;
		return;
	}

	_pCB = pCodeBase;
	_pDataTree = pDataTree;

//  ggf. Expr.-Eingabe begrenzen
	if (ExpressionSize) 
	{
		_ExprSize = ExpressionSize;
		_ExprLine.SetTextLimit (_ExprSize);
	} else
		_ExprSize = 0;

//  Expression ggf. setzen
	if (pExpression && *pExpression) 
	{
		if (_ExprSize && _ExprSize < lstrlen (pExpression)) 
		{
			*(pExpression + _ExprSize) = '\0';
			MessageBeep (0);
			ResString ErrText (ResID (IDS_TOCOMPLEX, pRF), 80);
			_InfoText.SetText (ErrText.Addr ());
		}
		_ExprLine.SetText (pExpression);
		_OKButton.Enable ();
		_CheckButton.Enable ();
	}

//  Zeichen konvertieren
	_OemToAnsii = GetOemToAnsiiFlag ();

//  ListBoxen füllen: FieldListe
	if (! (_OpFlag = _FillFieldListe ()))
		return;

//  Operator-Liste füllen
	short Entries = sizeof (OperatorList) / sizeof (LISTE);
	short i = 0;
	for (; i < Entries; i++) 
	{
		if (_OperatorList.AddString (OperatorList [i].pContents) == -1) 
		{
			DEX_Error (RC_ctEntryExpression, EC_NOMEMORY);
			_OpFlag = False;
			return;
		}
	}

//  Funktionen-Liste füllen
	Entries = sizeof (FunctionList) / sizeof (LISTE);
	for (i = 0; i < Entries; i++) 
	{
		if (_FunctionList.AddString (FunctionList [i].pContents) == -1) 
		{
			DEX_Error (RC_ctEntryExpression, EC_NOMEMORY);
			_OpFlag = False;
			return;
		}
	}

	_OpFlag = True;
}							 
#pragma warning (default : 4355)

__export EntryExpression :: ~ EntryExpression (void) 
{
	// nothing to do
}

//  aktuellen Expression lesen
pchar __export EntryExpression :: GetExpression (void) 
{
//  prüfe interne Parameter
	if (!_OpFlag)
		return NULL;

	pchar pText = NULL;
	short Len = _ExprLine.GetTextLen ();
	if (Len) {	  // wenn Text vorhanden
		pText = new char [Len + 1];
		if (!pText) 
		{
			DEX_Error (RC_EntryExprGetExpression, EC_NOMEMORY);
			return NULL;
		}
		_ExprLine.GetText (pText, Len + 1);
		return pText;
	}

	return NULL;
}

//  Expression-Eingabe
void __export EntryExpression :: EditChange (ControlEvt CE) 
{
//  prüfe interne Parameter
	if (!_OpFlag)
		return;

	switch ((uint) CE.GetControlID ()) 
	{
		case IDE_EXPRESSION: 				  // OK-Button freigeben
		{
			if (_ExprLine.GetTextLen ()) 
			{
				_OKButton.Enable ();
				_CheckButton.Enable ();
			} 
			else 
			{
				_OKButton.Disable ();
				_CheckButton.Disable ();
			}
		}
		break;
	}
}

//  Button wurde betätigt
void __export EntryExpression :: ButtonClick (ControlEvt CE) 
{
//  prüfe interne Parameter
	if (!_OpFlag)
		return;

	switch ((uint) CE.GetControlID ()) 
	{
		case IDCANCEL:
			EndDlg (_OpFlag = False);			   // identisch Abbruch
		break;
		case IDOK:
			if (_CheckExpression ())
				EndDlg (_OpFlag = True);
		break;
		case IDB_CHECK:
			_CheckExpression ();
		break;
		default:
		break;
	}
}

Bool __export EntryExpression :: QueryClose (Event) 
{
	_OpFlag = False;
	return True;
}

//  Expression prüfen
Bool EntryExpression :: _CheckExpression (void) 
{
//  prüfe interne Parameter
	if (! _OpFlag)
		return False;

	short Len = _ExprLine.GetTextLen ();
	if (!Len)
		return False;

	pchar pExpr = new char [Len + 1];
	if (!pExpr) 
	{
		DEX_Error (RC_EntryExprCheck, EC_NOMEMORY);
		return False;
	}

//  alle evtl. Fehlermeldungen umleiten
	ErrInstall E1 (e4comma_expected, ExprErrHandler, (DWORD) &_InfoText);
	ErrInstall E2 (e4complete, ExprErrHandler, (DWORD) &_InfoText);
	ErrInstall E3 (e4data_name, ExprErrHandler, (DWORD) &_InfoText);
	ErrInstall E4 (e4num_parms, ExprErrHandler, (DWORD) &_InfoText);
	ErrInstall E5 (e4overflow, ExprErrHandler, (DWORD) &_InfoText);
	ErrInstall E6 (e4right_missing, ExprErrHandler, (DWORD) &_InfoText);
	ErrInstall E7 (e4type, ExprErrHandler, (DWORD) &_InfoText);
	ErrInstall E8 (e4unrec_function, ExprErrHandler, (DWORD) &_InfoText);
	ErrInstall E9 (e4unrec_operator, ExprErrHandler, (DWORD) &_InfoText);
	ErrInstall E10 (e4unrec_value, ExprErrHandler, (DWORD) &_InfoText);
	ErrInstall E11 (e4unterminated, ExprErrHandler, (DWORD) &_InfoText);
	ErrInstall E12 (e4field_name, ExprErrHandler, (DWORD) &_InfoText);

	Bool Ret = True;
	_ExprLine.GetText (pExpr, Len + 1);
	CTable Tb (*_pDataTree);
	if (Tb.First ()) 
	{
		DataIndexLock pData (Tb);
		if (pData) 		// keine Meldung ausgeben
		{
			Ret = CheckdBaseExpression (*_pCB, *pData, pExpr, True);
			if (_pCB -> error () == r4success) 
			{
				if (pRF) 
				{
					ResString ExprText (ResID (IDS_EXPROK, pRF), 50);
					_InfoText.SetText (ExprText.Addr ());
				}
			} else
				_pCB -> error_set (r4success);  // evtl. Fehler rücksetzen
		} 
		else 
		{
			DEX_Error (RC_EntryExprCheck, EC_LOCKERROR);
			Ret = False;
		}
	} 
	else 
	{
		DEX_Error (RC_EntryExprCheck, EC_SYSERROR);
		Ret = False;
	}

	DELETE_VEC (pExpr);
	return Ret;
}

//  Feldliste füllen
Bool EntryExpression :: _FillFieldListe (void) 
{
	CTable Tb (*_pDataTree);

	ResString Op (ResID (IDS_FIELDQUALIFIER, pRF), FieldQualiSize);
//  für alle dBase-Dateien
	for (Tb.First (); Tb.Valid (); Tb.Next ()) 
	{
		DataIndexLock pData (Tb);
		if (!pData) 
		{
			DEX_Error (RC_EntryExprFieldListe, EC_LOCKERROR);
			continue;	   // Versuch mit der nächsten Datei
		}

	//  für alle Felder dieser Datei
		char Buffer [FieldSize + 1] = "";
		for (short i = 1, j = pData -> num_fields (); i <= j; i++) 
		{
		//  keine logischen und Memo-Felder bearbeiten
			char Type = pData -> field (i) -> type ();
			if (Type == 'L' || Type == 'M')
				continue;

			Str10 Bez = pData -> field (i) -> name;	 // Feldname
			lstrcpy (Buffer, pData -> alias.ptr ());	// Datei-Name
			lstrcat (Buffer, Op.Addr ());			   // Qualifier
			if (_OemToAnsii)
				OemToAnsi (Bez.ptr (), Bez.ptr ());	 // dt. Umlaute ersetzen
			lstrcat (Buffer, Bez.ptr ());
			if (_FieldList.AddString (Buffer) == -1) 
			{
				DEX_Error (RC_EntryExprFieldListe, EC_NOMEMORY);
				return False;
			}
		}	   // for Felder
	}		   // for Dateien

	return True;
}			   // for Liste


//  Selektion eines Elementes in einer Liste
void __export EntryExpression :: ListBoxSel (ControlEvt CE) 
{
//  prüfe interne Parameter
	if (!_OpFlag)
		return;

	short Index = 0;
	short MaxIndex = 0;
	switch ((uint) CE.GetControlID ()) 
	{
		case IDL_FIELDS: { // Datentyp und Länge für aktuelle Feld ausgeben
			char Line [FieldSize + 1] = "";
			if (! _FieldList.GetCurrentString (Line)) 
			{
				DEX_Error (RC_EntryExprListSel, EC_SYSERROR);
				break;
			}

		//  Feld- und Dateinamen bilden
			ResString Op (ResID (IDS_FIELDQUALIFIER, pRF), FieldQualiSize);
			pchar OpBegin = strstr (Line, Op.Addr ());	  // Operatorbeginn
			char FieldName [FieldNameSize + 1] = "";
			lstrcpy (FieldName, OpBegin + lstrlen (Op.Addr ()));
			if (_OemToAnsii)		// ggf. Rückkonvertierung
				AnsiToOem (FieldName, FieldName);
			char FileName [FileNameSize + 1] = "";
			*OpBegin = '\0';					   // jetzt Dateinamen lesen
			lstrcpy (FileName, Line);

			_OutputFieldInfo (FileName, FieldName);

		}
		break;
		case IDL_FUNCTIONS:
			Index = _FunctionList.GetCurrentIndex ();
			MaxIndex = sizeof (FunctionList) / sizeof (LISTE);
			if (Index < 0 || Index >= MaxIndex)	 // wenn ungültiger Wert
				break;							  // raus
			_InfoText.SetText (FunctionList [Index].pComment);
		break;
		case IDL_OPERATORS:
			Index = _OperatorList.GetCurrentIndex ();
			MaxIndex = sizeof (OperatorList) / sizeof (LISTE);
			if (Index < 0 || Index >= MaxIndex)	 // wenn ungültiger Wert
				break;							  // raus
			_InfoText.SetText (OperatorList [Index].pComment);
		break;
	}
}

Bool EntryExpression :: _OutputFieldInfo (pchar pFileName, pchar pFieldName) 
{
//  prüfe Parameter
	if (!pFileName || !pFieldName) 
	{
		DEX_Error (RC_EntryExprFieldInfo, EC_SYSERROR);
		return False;
	}

	CTable Tb (*_pDataTree);
	if (! Tb.Find (pFileName)) 
	{
		DEX_Error (RC_EntryExprFieldInfo, EC_SYSERROR);
		return False;
	}

	DataIndexLock pData (Tb);
	if (!pData) 
	{
		DEX_Error (RC_EntryExprFieldInfo, EC_LOCKERROR);
		return False;
	}

	Field *pField = pData -> field (pFieldName);
	if (_pCB -> error () != r4success)  // CodeBase hat Fehler ausgegeben
		return False;

//  Info erzeugen
	char Buffer [80] = "";
	ResString Info (ResID (IDS_FIELDINFO, pRF), 30);
	ResString TypeText (ResID (IDS_CHARTYPE, pRF), 20);
	switch (pField -> type ()) 
	{
		case 'C':	   // "Zeichen" ist voreingestellt
		break;
		case 'D':
			TypeText = ResString (ResID (IDS_DATETYPE, pRF), 20);
		break;
		case 'N':
			TypeText = ResString (ResID (IDS_NUMTYPE, pRF), 20);
		break;
		case 'F':
			TypeText = ResString (ResID (IDS_FLOATTYPE, pRF), 20);
		break;
		default:
			TypeText = ResString (ResID (IDS_UNKNOWNTYPE, pRF), 20);
		break;
	}

//  Type-Text und Länge einhängen
	wsprintf (Buffer, Info.Addr (), TypeText.Addr (), pField -> len ());
	short Dec = pField -> decimals ();

//  wenn Nachkommastellen
	if (Dec) 
	{
		char DecBuffer [40] = "";
		ResString DecText (ResID (IDS_DECIMALTEXT, pRF), 30);
		wsprintf (DecBuffer, DecText.Addr (), Dec);
		lstrcat (Buffer, DecBuffer);
	}

//  Text ausgeben
	_InfoText.SetText (Buffer);

	return True;
}

//  Auswahl eines Elementes in einer Liste
void __export EntryExpression :: ListBoxClk (ControlEvt CE) 
{
//  prüfe interne Parameter
	if (!_OpFlag)
		return;

	char Line [FieldSize + 1] = "";
	switch ((uint) CE.GetControlID ()) 
	{
		case IDL_FIELDS:
			if (! _FieldList.GetCurrentString (Line)) 
			{
				DEX_Error (RC_EntryExprListClk, EC_SYSERROR);
				return;
			}
		break;
		case IDL_FUNCTIONS:
			if (! _FunctionList.GetCurrentString (Line)) 
			{
				DEX_Error (RC_EntryExprListClk, EC_SYSERROR);
				return;
			}
		break;
		case IDL_OPERATORS: 
		{
			Line [0] = ' ';	 // Problem mit logischen Operatoren !
			if (! _OperatorList.GetCurrentString (Line+1)) {
				DEX_Error (RC_EntryExprListClk, EC_SYSERROR);
				return;
			}
			lstrcat (Line, " ");
		}
		break;
		default:	// unbekannte Liste
		return;
	}

//	selektierten Text ersetzen
	_ExprLine.ReplaceSelected (Line);			

/*
//  alten Edit-Text lesen
	short Len = _ExprLine.GetTextLen ();
	pchar pNewText = new char [Len + lstrlen (Line) + 1];
	if (! pNewText) 
	{
		DEX_Error (RC_EntryExprListClk, EC_NOMEMORY);
		return;
	}

//  ggf. alten Text kopieren
	if (Len) 
	{
		_ExprLine.GetText (pNewText, Len + 1);
		lstrcat (pNewText, Line);		   // neuen Text anhängen
	} else
		lstrcpy (pNewText, Line);

//  ggf. Länge begrenzen
	if (_ExprSize && lstrlen (pNewText) > _ExprSize) 
	{
		MessageBeep (0);
		ResString ErrText (ResID (IDS_TOCOMPLEX, pRF), 80);
		_InfoText.SetText (ErrText.Addr ());
		*(pNewText + _ExprSize) = '\0';
	}

	_ExprLine.SetText (pNewText);		   //	   und ausgeben
	DELETE_VEC (pNewText);
*/
}
