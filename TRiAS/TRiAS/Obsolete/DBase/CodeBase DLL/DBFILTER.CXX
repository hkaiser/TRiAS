/*------------------------------------------------------------------------

File: DBFILTER.CXX (Implementation)

DBFILTER -
ermittelt all Rekord-Nummern die einem bestimmtem Filter genügen.

Erarbeitet: J. Benkenstein					  gegonnen am 25. Jan. 1991
												 Stand vom 18. August 1993
------------------------------------------------------------------------*/

#include <d4all.h>

#ifndef MDX
#define MDX
#endif

#ifdef WIN32
#include <bool.h>
#endif
#include <cxxtypes.hxx>

extern "C" {
	#include <string.h>
#ifndef WIN32	
	#include <math.h>
	#include <storage.h>	// LPSTORAGE
#endif	
	#include <xtension.h>	   	// für DEX_Error (), DEX_SetError ()
	#include <xtensnx.h>
	#include <protos.h>			// DELETE ()
}

#include <containr.hxx>
#include <errcodes.hxx>	 // Fehlerkodes
#include <objfeld.hxx>

#include <dbliste.hxx>	  // zugeh. Header-File

#include <relation.hxx>	 // Relationen zwischen DBaseDateien
#include <dbtools.hxx>	  // GetOemToAnsiiFlag ()

// lokale Variablen
static uint ActFieldLen = 0;	   // Variablen für akt. Feld
static pchar pActFieldVal = NULL;

// wende auf den akt. Satz den logischen dBase-Expression an
int __export __far PASCAL BoolFilterFunction (void* pInfoParm)
{
	DB_Filter *pInfo = (DB_Filter *) pInfoParm;

//  SlaveDB's ggf. nachführen
	RelationList *pRel = pInfo -> _pRel;
	if (pRel && pRel -> Count() > 0) {
	CRing r(*pRel);
		for (r.First(); r.Valid(); r.Next()) {
			RelationLock l(r);
				if (!l || !(l -> Seek(pInfo -> _pCBase))) return r4ignore;
		}
	}

//  Master-File-Test								   
	return  pInfo -> _pTrueFalse -> ExprTrue (Str255 (pInfo -> _pString -> ptr ())) ?
			r4keep : r4ignore;
}

// vergleiche Feld-Inhalt
int __export __far PASCAL CompareFilterFunction (void* InfoParm)
{
	DB_Filter *pInfo = (DB_Filter *) InfoParm;

//  Master-File-Test
	if (ActFieldLen && pActFieldVal) {
		short Len = min (pInfo -> _pFieldPtr -> len (), ActFieldLen);
		memcpy (pActFieldVal, pInfo -> _pFieldPtr -> ptr (), Len);
		*(pActFieldVal + Len) = '\0';
		OemToAnsi (pActFieldVal, pActFieldVal);
		if (! (StrPtr (pActFieldVal) == *pInfo -> _pString))
			return r4ignore;
	} else {
		if (! (*pInfo -> _pFieldPtr == *pInfo -> _pString))
			return r4ignore;
	}
	
//  SlaveDB's nachführen
	RelationList *pRel = pInfo -> _pRel;
	if (pRel && pRel -> Count() > 0) {
		CRing r(*pRel);
		for (r.First(); r.Valid(); r.Next()) {
			RelationLock l(r);
			if (!l || !(l -> Seek(pInfo -> _pCBase))) return r4ignore;
		}
	}
	
//  evtl. zusätzlichen dBase-Expression auswerten
	if (pInfo -> _pExprStr)
		return pInfo -> _pTrueFalse -> ExprTrue (Str255 (pInfo -> _pExprStr -> ptr ())) ?
			   r4keep : r4ignore;

	return r4keep;
}

// Joker ("*") letztes Zeichen im Feld-Inhalt
int __export __far PASCAL EndJokerFilterFunction (void* InfoParm)
{
	DB_Filter *pInfo = (DB_Filter *) InfoParm;

//  Master-File-Test
	if (ActFieldLen && pActFieldVal) {
		short Len = min (pInfo -> _pFieldPtr -> len (), ActFieldLen);
		memcpy (pActFieldVal, pInfo -> _pFieldPtr -> ptr (), Len);
		*(pActFieldVal + Len) = '\0';
		OemToAnsi (pActFieldVal, pActFieldVal);
		if (StrPtr (pActFieldVal).search (*pInfo -> _pString))
			return r4ignore;
	} else {
		if ((*pInfo -> _pFieldPtr).search (*pInfo -> _pString))
			return r4ignore;
	}
	
//  SlaveDB's nachführen
	RelationList *pRel = pInfo -> _pRel;
	if (pRel && pRel -> Count() > 0) {
		CRing r(*pRel);
		for (r.First(); r.Valid(); r.Next()) {
			RelationLock l(r);
			if (!l || !(l -> Seek(pInfo -> _pCBase))) return r4ignore;
		}
	}

//  evtl. zusätzlichen dBase-Expression auswerten
	if (pInfo -> _pExprStr)
		return pInfo -> _pTrueFalse -> ExprTrue (Str255 (pInfo -> _pExprStr -> ptr ())) ?
			   r4keep : r4ignore;

	return r4keep;
}

// Joker ("*") erstes Zeichen im Feld-Inhalt
int __export __far PASCAL BeginJokerFilterFunction (void* InfoParm)
{
	DB_Filter *pInfo = (DB_Filter *) InfoParm;

//  Master-File-Test
	if (ActFieldLen && pActFieldVal) {
		short Len = min (pInfo -> _pFieldPtr -> len (), ActFieldLen);
		memcpy (pActFieldVal, pInfo -> _pFieldPtr -> ptr (), Len);
		*(pActFieldVal + Len) = '\0';
		OemToAnsi (pActFieldVal, pActFieldVal);
		if (StrPtr (pActFieldVal).search (*pInfo -> _pString) < 0)
			return r4ignore;
	} else {
		if ((*pInfo -> _pFieldPtr).search (*pInfo -> _pString) < 0)
			return r4ignore;
	}
	
//  SlaveDB's nachführen
	RelationList *pRel = pInfo -> _pRel;
	if (pRel && pRel -> Count() > 0) {
		CRing r(*pRel);
		for (r.First(); r.Valid(); r.Next()) {
			RelationLock l(r);
			if (!l || !(l -> Seek(pInfo -> _pCBase))) return r4ignore;
		}
	}
	
//  evtl. zusätzlichen dBase-Expression auswerten
	if (pInfo -> _pExprStr)
		return pInfo -> _pTrueFalse -> ExprTrue (Str255 (pInfo -> _pExprStr -> ptr ())) ?
			   r4keep : r4ignore;

	return r4keep;
}

// Feldinhalt = "*"
int __export __far PASCAL JokerFilterFunction (void* InfoParm)
{
	DB_Filter *pInfo = (DB_Filter *) InfoParm;

//  SlaveDB's nachführen
	RelationList *pRel = ((DB_Filter *)InfoParm) -> _pRel;

	if (pRel && pRel -> Count() > 0) {
		CRing r(*pRel);
		for (r.First(); r.Valid(); r.Next()) {
			RelationLock l(r);
			if (!l || !(l -> Seek(pInfo -> _pCBase))) return r4ignore;
		}
	}

//  Master-File-Test: evtl. zusätzlichen dBase-Expression auswerten
	if (pInfo -> _pExprStr)
		return pInfo -> _pTrueFalse -> ExprTrue (Str255 (pInfo -> _pExprStr -> ptr ())) ?
			   r4keep : r4ignore;

	return r4keep;
}

// Selektion über boolschen dBase-Expression oder Tag + Schlüssel
__export DB_Filter :: DB_Filter (CodeBase* pCodeBase,		// CodeBaseObjekt
						DataIndex &DI,			  // Index-File-Objekt
						DBaseObjNummer &DBaseON,	// zu filternde ObjektNummer
						pchar pTagName,			 // Zeiger auf dBase-Tag-Name
						pchar pKeyVal,			  // Zeiger auf Keywert
						pchar pExprBuff,			// FilterExpression
						RelationList *pRel)		 // Relationen
		   : _ON (DBaseON),
			 _Data (DI)
{
	InitVariablen ();	   // Variablen init.

	_pRel = pRel;		   // Relationsliste
	_pCBase = pCodeBase;			// Zeiger speichern

	if (_RC = (ErrCode) _pCBase -> error ())  // CodeBase OK ?
		return;

//  ggf. Tag selektieren
	if (pTagName) {
	//  fehlerhafte Zeichen im Tagnamen
		if (strchr (pTagName, '*')) {
			DEX_Error (RC_ctDB_Filter, _RC = EC_ILLPARS);
			return;
		}

#ifdef MDX
		if (_Data.select (pTagName) == r4success) {
#else
#if defined (CLIPPER) || defined (NDX)
			Index NewIndex (&_Data, pTagName);
		if ((_RC = (ErrCode) _pCBase -> error ()) == r4success) {
			_Data.select (&NewIndex);
#endif
#endif
			if (! (_pTName = new char [lstrlen (pTagName) + 1])) {
				DEX_Error (RC_ctDB_Filter, _RC = EC_NOMEMORY);
				return;
			}
			lstrcpy (_pTName, pTagName);
			TagSelected = True;
		} else { // Fehlermeldg. bereits durch CodeBase ausgegeben
			_RC = e4tag_name;
			return;
		}
	}   // Tag gegeben

//  ggf. Keywert speichern
	if (pKeyVal) {
		if (! (_pKeyValue = new char [lstrlen (pKeyVal) + 1])) {
			DEX_Error (RC_ctDB_Filter, _RC = EC_NOMEMORY);
			return;
		}
		lstrcpy (_pKeyValue, pKeyVal);
		AnsiToOem (_pKeyValue, _pKeyValue);	 // DOS-String erzeugen
	}   // KeyVal gegeben

//  Filter erz. und init.
	_pDataFilter = new ExtDataFilter ();
	if (!_pDataFilter) {						// wenn kein Speicher mehr vorhanden
		DEX_Error (RC_ctDB_Filter, _RC = EC_NOMEMORY); // Fehlermeldung raus
		return;
	}

	if (pExprBuff && *pExprBuff) 
	{    
		_pString = new String (_pCBase);
		if (! _pString) 
		{
			_RC = EC_NOMEMORY;
			return;			
		}

		if (! Expression (DI, pExprBuff, *_pString)) // wenn Expression nicht OK
		{
		    _RC = EC_ILLPARS;
			return;
		}			
		_pDataFilter->filter (&_Data, BoolFilterFunction, this);
	} else
		_pDataFilter->filter (&_Data, JokerFilterFunction, this);

	_RC = EC_OKAY;				  // Returnkode OK
}

// Selektion über Feldname und Inhalt
__export DB_Filter :: DB_Filter (CodeBase* pCodeBase,	//  CodeBase-Objekt
						DataIndex &DI,		  //  DataIndex-Objekt
						pchar pFieldName,	   //  Feldname
						pchar pFieldVal,		//  zu vergl. Feldwert
						DBaseObjNummer &ON,	 //  Objektnummern-Feld
						RelationList *pRel,	 //  Relationen zw. dBase-DBs
						pchar pExprBuff)		//  boolscher dBase-Expr.
		   : _ON (ON),
			 _Data (DI)
{
	InitVariablen ();		   // interne Variablen init.
						 
//		Teste Parameter								 
		if (!pCodeBase || !pFieldName || !*pFieldName || !pFieldVal || !*pFieldVal)
		{
				_RC = EC_ILLPARS;						
				return;
		}				
								 
	_pRel = pRel;
	_pCBase = pCodeBase;		// Zeiger speichern

	if (_RC = (ErrCode) pCodeBase -> error ())  // CodeBase OK ?
		 return;

//  ggf. Expression init.
	if (pExprBuff && *pExprBuff) 
	{
		_pExprStr = new String (_pCBase);
		if (! _pExprStr) 
		{
			_RC = EC_NOMEMORY;
			return;			
		}
		if (!Expression (DI, pExprBuff, *_pExprStr)) // diesen prüfen und laden
		{
			_RC = EC_ILLPARS;						
			return;
		}			
	}			

//  Filter init.
	_pDataFilter = new ExtDataFilter ();
	if (!_pDataFilter) {   // wenn kein dyn. Speicher mehr vorhanden
		 DEX_Error (RC_ctDB_Filter, _RC = EC_NOMEMORY); // Fehlermeldung raus
		 return;
	}						   

//  Feldnamen konvertieren und setzen
	AnsiToOem (pFieldName, pFieldName);	// DOS-String erzeugen
	_pFieldPtr = _Data.field (pFieldName); // Feldname setzen; CodeBase über-
										// nimmt evtl. Fehlerausgabe
	if (_RC = (ErrCode) _pCBase->error ()) //  bei CodeBase-Fehler
		return ;

	if (_pFieldPtr == NULL) {			   // wenn Fehler ausgeschaltet
		_RC = e4field_name;				 // Zeiger explizit prüfen
		return;
	}

//  Längen angleichen
	_pString = new String (_pCBase);
	if (!_pString) {   // wenn kein dyn. Speicher mehr vorhanden
		DEX_Error (RC_ctDB_Filter, _RC = EC_NOMEMORY); // Fehlermeldung raus
		return;
	}   

	_pString->set_len (_pFieldPtr->len());	  // Länge wie Suchfeld
	_pString->set (' ');						// mit Leerzeichen init.
	_pString->replace (StrPtr(pFieldVal));// String mit Key-Inahlt init.

//  ggf. leeres Vergleichsfeld anlegen
	if (GetOemToAnsiiFlag ()) 
	{
		ActFieldLen = _pFieldPtr->len();
		if (! (pActFieldVal = new char [ActFieldLen + 1])) 
		{
			DEX_Error (RC_ctDB_Filter, _RC = EC_NOMEMORY); // Fehlermeldung raus
			return;
		}
		*pActFieldVal = '\0';
	}

//  Test auf evtl. Jokerzeichen im Suchstring
	if (StrPtr (pFieldVal) == StrPtr ("*"))	  // wenn alle Sätze selektieren
		_pDataFilter->filter (&_Data, JokerFilterFunction, this);
	else
	{
		if (_pString->search (StrPtr ("*")) == 0)	// 1. Zeichen Joker ("*") ?
		{
			_pString->replace (StrPtr(pFieldVal+1)); // Joker streichen
			_pString->set_len (StrPtr(pFieldVal).len() - 1);
			_pDataFilter->filter (&_Data, BeginJokerFilterFunction, this);
		}
		else
		{   // letztes Zeichen Joker ("*") ?
			if ((uint)_pString->search (StrPtr ("*")) == (StrPtr (pFieldVal).len() - 1))
			{
				_pString->set_len (StrPtr(pFieldVal).len() - 1);		// Joker abschneiden
				_pDataFilter->filter (&_Data, EndJokerFilterFunction, this);
			}
			else
				_pDataFilter->filter (&_Data, CompareFilterFunction, this); // allg. Funktion
		}
	}
	_RC = EC_OKAY;
}

// Selektion über Tag aus dem zugehörigen Index-File
__export DB_Filter :: DB_Filter (CodeBase* pCodeBase, DataIndex &DI,
						pchar pTagName, // dBase-Tag-Name
						DBaseObjNummer &ON) // speichert sel. Rekord-Nrn.
		   : _ON (ON),
			 _Data (DI)
{
	InitVariablen ();	   // interen Variablen init.

	_pCBase = pCodeBase;			// Zeiger speichern

	if (_RC = (ErrCode) _pCBase -> error ())	// CodeBase OK ?
		return;

#ifdef MDX
	if (_Data.select (pTagName) == r4success) {
#else
#if defined (CLIPPER) || defined (NDX)
	Index NewIndex (&_Data, pTagName);
	if ((_RC = (ErrCode) _pCBase -> error ()) == r4success) {
		_Data.select (&NewIndex);
#endif
#endif
		if (! (_pTName = new char [lstrlen (pTagName) + 1])) {
			DEX_Error (RC_ctDB_Filter, _RC = EC_NOMEMORY); // Fehlermeldung raus
			return;
		}
		lstrcpy (_pTName, pTagName);
		TagSelected = True;
		_RC = EC_OKAY;
		return;
	} else {	// evtl. Fehler bereits durch CodeBase ausgegeben
		_RC = e4tag_name;
		return;
	}				   
}

//  eigentliches Filtern
ErrCode __export DB_Filter :: Check (Bool OROperation, Bool Unique) {
//  FehlerTest
	if (_RC != EC_OKAY)
		return _RC;

	if (_RC = (ErrCode) _pCBase -> error ())	// CodeBase OK ?
		return _RC;

//  Argumente OK ?
	if (_pKeyValue && !TagSelected) {   // Key-Suche geht nur über sel. Tag !
		DEX_SetError (_RC, RC_CheckDB_Filter, EC_ILLPARS, NULL);
		return _RC;
	}

//  Filter-Initialisierung OK
	if (_ON.GetStatus () == DBaseObjNummer :: NotFiltered || OROperation) {

	//  Filtern über Key
		if (_pKeyValue) {
		//  Typ bestimmen
			Bool KeyType = True;			// String, False: numeric
			double KeyValue = 0.0;
#ifdef MDX
			switch (_Data.tag_selected () -> type ()) {
#else
#if defined (CLIPPER) || defined (NDX)
			if (!_pTName || !*_pTName)  // Parameter prüfen
				return e4tag_name;
			Index NewIndex (&_Data, _pTName);
			switch (_Data.index_selected () -> type ()) {
#endif
#endif
				case 'D':			   // Datum
				case 'C':			   // String
					KeyType = True;
				break;
				case 'N':			   // Numeric
				case 'F': {			 // Float
					KeyType = False;
					KeyValue = atof (_pKeyValue);	// Wert entspr. Typ konv.
				}
				break;
				default: {	  // alle anderen Typen erzeugen Fehler
					DEX_SetError (_RC, RC_CheckDB_Filter, e4field_type, NULL);
					return _RC;
				}
				break;
			}

		//  suche 1. Satz
			if (KeyType)
				_RC = (ErrCode) _pDataFilter -> seek (_pKeyValue);
			else
				_RC = (ErrCode) _pDataFilter -> seek (KeyValue);
			if (_RC)  // Fehlertest
				if (_RC == r4after || _RC == r4eof)   // nicht gefunden
					return (_RC = WC_NOTFOUND);
				else {									// echter Fehler
					DEX_SetError (_RC, RC_CheckDB_Filter, _RC, NULL);
					return _RC;
				}
			else {
				if (!_Data.deleted ()) {		// wenn keine Löschmarke gesetzt
					if (!_ON.AddDBaseRecord (_Data.recno ())) { // Rekord-Nummer speichern
						DEX_SetError (_RC, RC_CheckDB_Filter, EC_NOMEMORY, NULL);
						return _RC;
					}
				}
			}

			if (Unique || _Data.eof ()) { // wenn nur ein gefundener Satz wichtig
				_ON.SetDBStatus (DBaseObjNummer :: Filtered);
				return _RC = EC_OKAY;
			}

		//  suche alle weiteren Sätze
			if (KeyType) {
				for (_RC = (ErrCode) _pDataFilter -> seek_on (_pKeyValue); _RC != r4after && _RC != r4eof;
					 _RC = (ErrCode) _pDataFilter -> seek_on (_pKeyValue)) {
					if (_RC != r4success)	   	// wenn beim Filtern Fehler
						return _RC;			 	// zurück
					if (_Data.deleted ()) 		// wenn Löschmarke gesetzt
						continue;				// nächsten Satz	
					if (!_ON.AddDBaseRecord (_Data.recno ())) { // Rekord-Nummer speichern
						DEX_SetError (_RC, RC_CheckDB_Filter, EC_NOMEMORY, NULL);
						return _RC;
					}
				}
				if (_ON.RA().Count() == 0)  // wenn kein Eintrag gefunden
					return (_RC = WC_NOTFOUND);
				else {
					_ON.SetDBStatus (DBaseObjNummer :: Filtered);
					return _RC = EC_OKAY;
				}
			} else {		// KeyValue ist vom Typ numeric
				for (_RC = (ErrCode) _pDataFilter -> seek_on (KeyValue); _RC != r4after && _RC != r4eof;
					_RC = (ErrCode) _pDataFilter -> seek_on (KeyValue)) {
					if (_RC != r4success)	   	// wenn beim Filtern Fehler
						return _RC;			 	// zurück
					if (_Data.deleted ()) 		// wenn Löschmarke gesetzt
						continue;	
					if (!_ON.AddDBaseRecord (_Data.recno ())) { // Rekord-Nummer speichern
						DEX_SetError (_RC, RC_CheckDB_Filter, EC_NOMEMORY, NULL);
						return _RC;
					}
				}
				if (_ON.RA().Count() == 0)  // wenn kein Eintrag gefunden
					return (_RC = WC_NOTFOUND);
				else {
					_ON.SetDBStatus (DBaseObjNummer :: Filtered);
					return _RC = EC_OKAY;
				}
			}
		} else { // normales Filtern
			_RC = (ErrCode) _pDataFilter -> top ();   // suche 1. Satz
			if (_RC) { // Fehlertest
				if (_RC == r4after || _RC == r4eof)   // nicht gefunden
					return (_RC = WC_NOTFOUND);
				else {									// echter Fehler
					DEX_SetError (_RC, RC_CheckDB_Filter, _RC, NULL);
					return _RC;
				}
			} else {
				if (!_Data.deleted ()) {				// wenn keine Löschmarke gesetzt
					if (!_ON.AddDBaseRecord (_Data.recno ())) { // Rekord-Nummer speichern
						DEX_SetError (_RC, RC_CheckDB_Filter, EC_NOMEMORY, NULL);
						return _RC;
					}
				}
			}
			if (Unique || _Data.eof ()) {	   // nur 1. Satz finden
				_ON.SetDBStatus (DBaseObjNummer :: Filtered);
				return _RC = EC_OKAY;
			}

			// nach weiteren Sätzen suchen
			for (_pDataFilter->skip(); !_Data.eof(); _pDataFilter->skip()) {
				if (_RC = (ErrCode) _pCBase -> error ()) // wenn beim Filtern Fehler
					return _RC;
				if (_Data.deleted ())		// wenn Löschmark gesetzt
					continue;				// nächsten Satz suchen
				if (!_ON.AddDBaseRecord (_Data.recno ())) { // Rekord-Nummer speichern
					DEX_SetError (_RC, RC_CheckDB_Filter, EC_NOMEMORY, NULL);
					return _RC;
				}
			}
			if (_ON.RA().Count() == 0) // wenn kein Eintrag gefunden
				return (_RC = WC_NOTFOUND);
			_ON.SetDBStatus (DBaseObjNummer :: Filtered);
			return _RC = EC_OKAY;					   // Filtern OK
		}
	} else { // Container bereits gefiltert
		CRing r(_ON.RA());
	//  nur noch bereits bekannte DBaseSätze anfassen
		for (r.First(); r.Valid(); r.Next()) {
			RecordObjLock l(r);

		//  wenn Zeiger ungültig
			if (!l) continue;
		//  UND + Record ist bereits ausgesondert
			if (!OROperation && !l -> _Valid) continue;
		//  OR + Record ist bereits gültig
			if (OROperation && l -> _Valid) continue;
		//  Record muß überprüft werden
			l -> _Valid = (_pDataFilter -> go (l -> _RecNr) == r4success);
		}
	}
	return _RC = EC_OKAY;
}

// Selektion über Tag
ErrCode DB_Filter :: CheckTag (Bool Unique)
{
//  FehlerTest
	if (_RC != EC_OKAY || (_RC = (ErrCode) _pCBase -> error ()))
		return _RC;
	if (!TagSelected)
		return _RC =  e4tag_name;

#ifdef MDX
	Tag *pTag = _Data.tag_selected ();
#else
#if defined (CLIPPER) || defined (NDX)
	if (!_pTName || !*_pTName)
		return e4tag_name;
	Index NewIndex (&_Data, _pTName);
	Tag *pTag = _Data.index_selected ();
#endif
#endif

	if (pTag -> top () == r4success) {
		if (!(_Data.deleted ())) {		// wenn Löschmarke nicht gesetzt
			if (!_ON.AddDBaseRecord (pTag -> recno ())) {
				DEX_SetError (_RC, RC_CheckTagDB_Filter, EC_NOMEMORY, NULL);
				return _RC;
			}
		} else {
			if (!Unique) {
				while (pTag -> skip (1)) {
					if (_RC = (ErrCode) _pCBase -> error ())
						return _RC;
					else {
						if (_Data.deleted ())		// wenn Löschmarke gesetzt
							continue;				// dann weiter
						if (!_ON.AddDBaseRecord (pTag -> recno ())) {
							DEX_SetError (_RC, RC_CheckTagDB_Filter, EC_NOMEMORY, NULL);
							return _RC;
						}
					}
				}
			}
		}
	}

	return EC_OKAY;
}

__export DB_Filter :: ~DB_Filter (void)
{
	DELETE_OBJ (_pDataFilter);
	DELETE_OBJ (_pString);
	DELETE_OBJ (_pExprStr);
	if (_pTrueFalse) {
		_pTrueFalse -> free();	
		DELETE_OBJ (_pTrueFalse);		// hier kommt gelegentlich die interne
								    // Speicherverwaltung durcheinander
	}
	DELETE_VEC (_pTName);
	DELETE_VEC (_pKeyValue);
}

//  prüfen und speichern eines dBase-Expression
Bool DB_Filter :: Expression (DataIndex &Data, pchar pExpr, String &Str)
{
	if (!pExpr || !*pExpr || !_pCBase)  // Parameter prüfen
		return False;
		
//	für CodeBase nicht verarbeitbaren Expression nicht zulassen:
//	wenn 2 " aufeinanderfolgen
/*
	char *pTest = pExpr;
	char *pFind = NULL;
	while (pTest && *pTest)
	{
		pFind = strchr (pTest, '\"');				
		if (pFind && *++pFind == '\"')
			return False;
		pTest = pFind;			
	}		                
*/	
		                
//  Expression speichern
//	Str = new String (_pCBase);
//	if (!Str) {		 // wenn kein Speicher mehr
//		DEX_Error (RC_ctDB_Filter, EC_NOMEMORY);
//		return False;
//	}
    
    AnsiToOem (pExpr, pExpr);	// DOS-String erzeugen
	Str = StrPtr (pExpr);	  	// Expression kopieren
	Str.add (StrChar (0));   	// Nullendung sichern

//  Expression prüfen
	_pTrueFalse = new Expr (&Data);	 // Expression-Objekt erzeugen
	if (!_pTrueFalse) {				 // wenn kein Speicher mehr vorhanden
		// DELETE (Str);
		DEX_Error (RC_ctDB_Filter, EC_NOMEMORY);
		return False;
	}

	// _pTrueFalse -> source = Str;	// dBase-Expression laden
	_pTrueFalse -> source = pExpr;	
	_pTrueFalse -> parse ();		// Expr. prüfen

//  Fehlerbeh. durch CodeBase bereits ausgegeben und abfragen
	if (_RC = (ErrCode) _pCBase -> error ()) {  // Ausdruck nicht ok
		// DELETE (Str);
		_pTrueFalse -> free ();	
		DELETE_OBJ (_pTrueFalse);
		return False;
	}

	_RC = EC_OKAY;
	return True;		// Expression ist OK
}

// Variablen init.
void DB_Filter :: InitVariablen (void)
{
	_pDataFilter =NULL;
	_pTrueFalse = NULL;
	_pString = _pExprStr = NULL;
	_pTName = _pKeyValue = NULL;
	_pCBase = NULL;
	_pRel = NULL; 
	_pFieldPtr = NULL;
	TagSelected = False;

	ActFieldLen = 0;
	pActFieldVal = NULL;
}
