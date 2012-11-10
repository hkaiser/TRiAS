// DatenStrukturen für die ObjektRecherche in DBaseDateien
// File: DBLISTE.HXX				Stand vom 20.01. 1992

#if !defined(_DBLISTE_HXX)
#define _DBLISTE_HXX

class CodeBase;
class DataIndex;
class Expr;
class String;
class ExtDataFilter;
class Field;
class RelationList;

#ifndef NODBASEOBJS
// enthält Info über einen DBase-DatenSatz ------------------------------------
class RecordObj {
public:
		long _RecNr;
		Bool _Valid;

// Konstruktor
				RecordObj (long RecNo);
// Destruktor
				~RecordObj (void);
};

// Liste von zu einem Objekt gehörenden DBaseSätzen ---------------------------
class RecordArray : public CArrayContainer {
protected:
		void UserDelete (void *pObj);

public:
// Konstruktor/Destruktor
				RecordArray (void);
				~RecordArray (void);

// Member
		Bool AddRecordNr (long RecNr);
		E4EXPORT_FCT long GetRecordNr (ulong Index); // i-ten Eintrag lesen
		ulong Compact (void);
};
DeclareLock (RecordArray, RecordObj);

// wird ebenfalls in einem ObjFeld gespeichert, enthält jedoch weiterhin ------
// noch den Id des untersuchten Objektes
class ObjIdNummer : public ObjNummer {
public:
		long _Id;

// Konstruktor, Destruktor
				ObjIdNummer (long ON);
				~ObjIdNummer (void);

};

// Das zugehörige Feld heist ObjIdFeld
class ObjIdFeld : public ObjFeld {
protected:
		void UserDelete (void *pObj);
public:
// Konstruktor, Destruktor
				ObjIdFeld (void);
				~ObjIdFeld (void);

// neues Element in der Liste bilden
		ObjNummer *NewObj (ObjNummerCreator &ONC, long ON);
		ObjFeldTyp isA (void);
};

// ObjektNummer mit zugehörigen DBaseSätzen -----------------------------------
// (wird in ObjFeld gespeichert)
class DBaseObjNummer : public ObjIdNummer {
public:
		enum DBaseStatus { Filtered, NotFiltered };

private:
// Member
		RecordArray *_RA;
		DBaseStatus _DBStat;

public:
		RecordArray & RA (void) { return *_RA; }

// RecordArray pflegen
		Bool AddDBaseRecord (long RecNo);
		Bool DeleteDBaseRecord (long RecNo);

// Status
		DBaseStatus GetStatus (void) { return _DBStat; }
		void SetDBStatus (DBaseStatus S) { _DBStat = S; }

// Konstruktor/Destruktor
		E4EXPORT_FCT DBaseObjNummer (long ON);
		E4EXPORT_FCT ~DBaseObjNummer (void);
};

// Liste der DBaseObjNummern --------------------------------------------------
class DBaseObjFeld : public ObjIdFeld {
protected:
		void UserDelete (void *);

public:
// Konstruktor/Destruktor
		E4EXPORT_FCT DBaseObjFeld (void);
		E4EXPORT_FCT ~DBaseObjFeld (void);

// konstruieren eines neuen ListenElementes
		E4EXPORT_FCT ObjNummer *NewObj (ObjNummerCreator &ONC, long ON);
		E4EXPORT_FCT ObjFeldTyp isA (void);
		E4EXPORT_FCT ulong Compact (void);
		E4EXPORT_FCT Bool DeleteDBaseRecordInfo (void);
};

// diese Liste enthält DBaseSätze mit ihren Objektnummern
DeclareLock (DBaseObjFeld, DBaseObjNummer);

#endif	  // NODBASEOBJS

#ifndef NODBFILTER
class E4EXPORT DB_Filter {

// Filter-Test-Funktionen
friend int __export __far PASCAL BoolFilterFunction (void *);
friend int __export __far PASCAL CompareFilterFunction (void *);
friend int __export __far PASCAL EndJokerFilterFunction (void *);
friend int __export __far PASCAL BeginJokerFilterFunction (void *);
friend int __export __far PASCAL JokerFilterFunction (void *);

private:
		Bool TagSelected;			// True, wenn Tag selektiert

// CodeBase-Variablen
		CodeBase* _pCBase;			// CodeBase-Basis-Objekt
		DataIndex &_Data;			 // Index-File-Objekt
		Expr* _pTrueFalse;			// dBase-Expression-Objekt
		String* _pString;			 // speichert Expression oder
		String* _pExprStr;			// Vergleichs-String
		ExtDataFilter *_pDataFilter;  // Filter-Objekt
		Field *_pFieldPtr;			// nur Feld-Zeiger !
		pchar _pTName;				// TagName
		pchar _pKeyValue;			 // Zeiger auf Keywert
		DBaseObjNummer &_ON;		  // Container für selektierte Rekord-Nrn.
		RelationList *_pRel;		  // Liste der dBas-Relationen
				

// Return-Kode
		ErrCode _RC;				  // Fehlerkode bei DB-Operationen

protected:
		void InitVariablen (void);	  // interne Variablen setzen
		Bool Expression (DataIndex &Data, pchar pExpr, String &);
						// prüfen und speichern eines dBase-Expression

public:
// Konstruktoren/Destuktor - Filter initialisieren

   // Selektion über Feldname und Inhalt
   DB_Filter (CodeBase* pCodeBase,	// Zeiger auf CodeBase-Basis-Objekt
			  DataIndex &DI,		  // Index-File-Objekt
			  pchar pFieldName,	   // Zeiger auf Feld-Namen
			  pchar pFieldVal,		// Zeiger auf Feld-Inhalt
			  DBaseObjNummer &DON,	// speichert selektierte Rekord-Nrn.
			  RelationList *pRL = NULL, // Liste der Master/Slave Verbindungen
			  pchar pExprBuff = NULL);  // logischer dBase-Expression

   // Selektion über boolschen dBase-Expression oder Tag und Schlüssel
   DB_Filter (CodeBase* pCodeBase,	// Zeiger auf CodeBase-Basis-Objekt
			  DataIndex &DI,		  // Index-File-Objekt
			  DBaseObjNummer &ObjNumber, // speichert selektierte Rekord-Nrn.
			  pchar pTagName,			// dBase-Tag-Name
			  pchar pKeyValue,		   // Zeiger auf Keywert
			  pchar pExpStr = NULL,	  // logischer (!) dBase-Expression,
										 // bzw. wenn NULL, dann alle Sätze sel.
			  RelationList *pRL = NULL); // Liste der Master/Slave Verbindungen

   // Selektion über Tag aus dem zugehörigen Index-File
   DB_Filter (CodeBase* pCodeBase,	// Zeiger auf CodeBase-Basis-Objekt
			  DataIndex &DI,		  // Index-File-Objekt
			  pchar pTagName,		 // dBase-Tag-Name
			  DBaseObjNummer &ObjNumber); // speichert selektierte Rekord-Nrn.

   ~DB_Filter (void);				 // dyn. erz. Objekte löschen

// Memberfunktionen
   ErrCode Check (Bool OrOp = False, // ODER-Verknüpfung bereits exist. Sätze
				  Bool Unique = False); // einzigartigen Key verwenden

   ErrCode CheckTag (Bool Unique = False);	  // Selektion über Tag
   ErrCode Result (void) { return _RC; }		// liefert Ergebniskode
};

#endif  // NODBFILTER

#ifndef NODBASEFILES

// Liste aller DBaseDateien ---------------------------------------------------
class E4EXPORT DBaseFiles : public CTree {
//	  Attribute	   
private:
		pchar _pMaster;						 // dBase-Master-Filename
protected:
		void UserDelete (void *pObj);

public:
// Konstruktor/Destruktor
				DBaseFiles (void);
				~DBaseFiles (void);

// Memberfunktionen
		Bool AddDataIndex (CodeBase *pCB, char *pAliasName);
		pchar GetMaster (void) { return _pMaster; }
		Bool SetMaster (CodeBase *pCB, pchar pAliasName); 
};
// in diesem Container werden 'DataIndex'-Elemente gespeichert werden
DeclareLock (DBaseFiles, DataIndex);

void *GetDataIndexName (void *pObj);

#endif  // NODBASEFILES

#endif // _DBLISTE_HXX
