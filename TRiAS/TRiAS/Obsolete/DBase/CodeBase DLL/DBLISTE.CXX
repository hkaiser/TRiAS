// Memberfunktionen fuer RechercheDatentypen ----------------------------------
// File: DBLISTE.CXX

#include <d4all.h>   
#ifdef WIN32
#include <bool.h>
#endif
#include <cxxtypes.hxx>
   
extern "C" {
	// #include <stdlib.h>	 	// _splitpath, _makepath
	#include <string.h>	 	// strupr ()
#ifndef WIN32	
	#include <storage.h>	// LPSTORAGE
#endif	
	#include <xtension.h>
	#include <xtensnx.h>	// f�r Message-Funktionen
	#include <protos.h>		// DELETE_VEC ()
}

#include <containr.hxx>
#include <errcodes.hxx>

#include <ristypes.hxx>
#include <objfeld.hxx>
#include <dbliste.hxx>
#include <dbtools.hxx>		  // GetFulldBaseName ()

// Gr��e der DBaseArrayContainer beim Erzeugen
const short MINOBJNUM = 5;

// Memberfunktionen f�r RechercheObjFeld --------------------------------------
ObjFeld :: ObjFeld (void)
		 : CListContainer ()  {
	// nothing to do
}

ObjFeld :: ~ObjFeld (void) {
		EveryDelete ();		 // alle Elemente des Baumes l�schen
}

// ein Element des Baumes l�schen 
void __export ObjFeld :: UserDelete (void *pObj) {
		((ObjNummer *)pObj) -> ~ObjNummer ();
}

// diese 'virtual' - Funktion ist von der Wirkung her f�r die Klasse der
// Elemente, die gerade im ObjFeld gespeichert sind, ein 'virtual constructor'
ObjNummer *ObjFeld :: NewObj (ObjNummerCreator &ONC, long ON) {
		return Create (ONC, ObjNummer)(ON);
}

ObjFeldTyp ObjFeld :: isA (void) { return OFTObjFeld; }

// Elemente der DBaseSatzListe
RecordObj :: RecordObj (long RN) {
		_RecNr = RN;
		_Valid = True;	// beim Einspeichern automatisch g�ltig
}

RecordObj :: ~RecordObj (void) 
{
		// nothing to do
}

// Liste der DBaseS�tze, die zu einem Objekt geh�ren --------------------------
void __export RecordArray :: UserDelete (void *pObj) {

		((RecordObj *)pObj) -> ~RecordObj ();
}

RecordArray :: RecordArray (void) 
			 : CArrayContainer (MINOBJNUM)
{
		// nothing to do
}

RecordArray :: ~RecordArray (void) {

		EveryDelete ();		 // alle Elemente des Containers l�schen
}

// neue Rekord-Nummer speichern, True wenn wenn OK, sonst False
Bool RecordArray :: AddRecordNr (long RN)
{
	  RecordObjCreator RIcreat (*this);
	  RecordObj *pRI = Create (RIcreat, RecordObj) (RN);  // Konstruktor rufen
	  return (pRI != NULL);
}

// logische Rekord-Nummer aus Container lesen
long __export RecordArray :: GetRecordNr (ulong Index) // akt. Index
{
   CRing Nav ( *this );
   if (Nav.Goto (Index))		 // wenn Index OK
   {
	  RecordObjLock rilock (Nav);		// speichersicheren Zugriff
	  if (rilock)
		   return (rilock->_RecNr);	  // mit Rekord-Nummer zur�ck
	  else
		 return 0;
   }
   else return 0;
}

// alle, als Invalid gekennzeichneten DBaseS�tze l�schen
ulong RecordArray :: Compact (void) {
CRing r(*this);

		for (r.First(); r.Valid(); ) {
		Bool toDelete = FALSE;
				{
				RecordObjLock l(r);

						if (l) toDelete = !l -> _Valid;
				}
				if (toDelete) {
						if (!r.Delete()) break;
				} else {
						if (!r.Next()) break;
				}
		}

return Count();		 // Anzahl der noch verbliebenen Elemente liefern
}


// ObjFeld, dessen Elemente zus�tzlich zur Objektnummer noch den jeweiligen ---
// Ident enthalten k�nnen
ObjIdFeld :: ObjIdFeld (void) 
		   : ObjFeld ()
{
		// nothing else to do
}

ObjIdFeld :: ~ObjIdFeld (void) {

		EveryDelete ();
}

void __export ObjIdFeld :: UserDelete (void *pObj) {

		((ObjIdNummer *)pObj) -> ~ObjIdNummer ();
}

ObjNummer *ObjIdFeld :: NewObj (ObjNummerCreator &ONC, long ON) {

		return Create (ONC, ObjIdNummer)(ON);
}

ObjFeldTyp ObjIdFeld :: isA (void) { return OFTObjIdFeld; }

ObjIdNummer :: ObjIdNummer (long ON)
			 : ObjNummer (ON) 
{
		_Id = -1L;
}

ObjIdNummer :: ~ObjIdNummer (void)
{
}

// Ein Objekt mit seinen DBaseDatenS�tzen -------------------------------------
__export DBaseObjNummer :: DBaseObjNummer (long ON)
				: ObjIdNummer (ON) 
{
		_RA = new RecordArray;  // zu Beginn keine DatenS�tze
		_DBStat = NotFiltered;
}

__export DBaseObjNummer :: ~DBaseObjNummer (void) {

		if (_RA) {
				delete _RA;
				_RA = NULL;
		}
}

// Einen DBaseDatenSatz zur Liste hinzuf�gen
Bool DBaseObjNummer :: AddDBaseRecord (long RecNo) {
CRing r(RA());

		for (r.First(); r.Valid(); r.Next()) {
		RecordObjLock l(r);

				if (l && l -> _RecNr == RecNo)
				// wenn Satz breits exitiert
						return TRUE;
		}

// wenn Satz noch nicht existiert, soll er eingespeichert werden
		{
		RecordObjCreator RAC (RA());

				return Create (RAC, RecordObj) (RecNo) != NULL;
		}
}

// Einen DBaseDatenSatz aus der Liste l�schen
Bool DBaseObjNummer :: DeleteDBaseRecord (long RecNo) {
CRing r(RA());
Bool toDelete = FALSE;

		for (r.First(); r.Valid(); r.Next()) {
				{
				RecordObjLock l(r);

						if (l && l -> _RecNr == RecNo) 
								toDelete = TRUE;
				}
				if (toDelete)
						return r.Delete();
		}

return FALSE;		   // nicht gefunden
}

// ObjFeld, welches DBaseObjNummern enth�lt -----------------------------------
__export DBaseObjFeld :: DBaseObjFeld (void) 
			  : ObjIdFeld () 
{
		// nothing else to do
}

__export DBaseObjFeld :: ~DBaseObjFeld (void) {

		EveryDelete ();
}

void __export DBaseObjFeld :: UserDelete (void *pObj) {

		((DBaseObjNummer *)pObj) -> ~DBaseObjNummer ();
}

// Ein neues Element in die Liste einf�gen
ObjNummer *DBaseObjFeld :: NewObj (ObjNummerCreator &ONC, long ON) {

		return Create (ONC, DBaseObjNummer)(ON);
}

ObjFeldTyp DBaseObjFeld :: isA (void) { return OFTDBaseObjFeld; }

// alle DBaseDatenS�tze in den RecordArrays, die Invalid sind, werden gel�scht
ulong __export DBaseObjFeld :: Compact (void) {
CRing r(*this);

		for (r.First(); r.Valid(); ) {
		Bool toDelete = FALSE;
				{
				DBaseObjNummerLock l(r);

						if (l && l ->_Id == -1L) // wenn nicht klassifiziert
						// wenn keine Elemente mehr, dann l�schen
								toDelete = (l -> RA().Compact() == 0);
				}
				if (toDelete) {
						if (!r.Delete()) break;
				} else {
						if (!r.Next()) break;
				}
		}

return Count();		 // Anzahl der ObjNummern liefern
}

// l�schen aller DBaseInformationen, die bei den ON's abgespeichert sind ------
Bool __export DBaseObjFeld :: DeleteDBaseRecordInfo (void) {
CRing r(*this);

		for (r.First(); r.Valid(); r.Next()) {
		DBaseObjNummerLock l(r);

				if (l) {
						if (!(l -> RA().EveryDelete())) return FALSE;
						else l -> SetDBStatus (DBaseObjNummer :: NotFiltered);
				}
		}

return TRUE;
}


// Container enth�lt alle DBaseDateien, die durch USE deklariert wurden -------
__export DBaseFiles :: DBaseFiles (void)
			: CTree (GetDataIndexName, StrCmp)
{
		_pMaster = NULL;
}

__export DBaseFiles :: ~DBaseFiles (void) {

		EveryDelete ();
		DELETE_VEC (_pMaster);
}

void __export DBaseFiles :: UserDelete (void *pObj) {

		((DataIndex *)pObj) -> ~DataIndex ();
}

// ZugriffsFunktion liefert Zeiger auf DateiNamen
void *GetDataIndexName (void *pObj) 
{
		return ((DataIndex *)pObj) -> alias.ptr();
}

Bool __export DBaseFiles :: AddDataIndex (CodeBase *pCB, char *pAliasName) {
//  pr�fe �bergebene Parameter
	if (!pCB || !pAliasName || !*pAliasName) {
		DEX_Error (RC_DBaseFilesAddDataI, EC_ILLPARS);
		return False;
	}

//  Datei bereits gespeichert ?
	CTable Tb (*this);
	if (Tb.Find (strupr (pAliasName)))
		return True;

//  pr�fe CodeBase
	if (pCB -> error () != r4success)
		return False;

//  vollst. Datei-Namen besorgen
	pchar pFullName = GetFulldBaseName (pAliasName);
	if (!pFullName)
		return False;

//  neuen DataIndex in Container einf�gen
	DataIndexCreator DIC (*this);
	DataIndex *pDI = Create (DIC, DataIndex) (pCB, pFullName);
	DELETE_VEC (pFullName);		 // vollst. Namen l�schen
	if (!pDI || pCB -> error () != r4success) {
		if (!pDI)
			DEX_Error (RC_DBaseFilesAddDataI, EC_NOMEMORY);
		return False;
	} else {
	//  AliasNamen setzen
		pDI -> alias = pAliasName;

	//  dessen L�nge pr�fen
		if (lstrlen (pAliasName) > (short) pDI -> alias.maximum ()) {
			DEX_Error (RC_DBaseFilesAddDataI, WC_ALIASNAMETOLONG);
		}
	//  Namen des dBase-Master-Files ggf. merken
		if (!_pMaster) {		// wenn noch nicht gespeichert
			if (! (_pMaster = new char [lstrlen (pDI -> alias.ptr ()) + 1])) {
				DEX_Error (RC_DBaseFilesAddDataI, EC_NOMEMORY);
				return False;
			}
			lstrcpy (_pMaster, pDI -> alias.ptr ());
		}
	}

	return True;
}

//  Master neu setzen
Bool __export DBaseFiles :: SetMaster (CodeBase *pCB, char *pAliasName) {
//  pr�fe �bergebene Parameter
	if (!pCB || !pAliasName || !*pAliasName) {
		DEX_Error (RC_DBaseFilesSetMaster, EC_ILLPARS);
		return False;
	}

//  neuen Eintrag ggf. in Baum
	if (! AddDataIndex (pCB, strupr (pAliasName)))
		return False;

//  Master bereits gesetzt ?
	if (_pMaster && ! lstrcmp (pAliasName, _pMaster))
		return True;		//  ja

//  neuen Master setzen
	DELETE_VEC (_pMaster);	  // alten Master l�schen
	if (! (_pMaster = new char [lstrlen (pAliasName) + 1])) {
		DEX_Error (RC_DBaseFilesSetMaster, EC_NOMEMORY);
		return False;
	}
	lstrcpy (_pMaster, pAliasName);

	return True;
}
