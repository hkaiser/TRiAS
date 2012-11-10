/*
File: MERKMDES.CXX
realiert die Verwaltung eines Merkmal-Beschreibungs-Baumes.

erarbeitet : J. Benkenstein				 Begonnen am 8. Mai 1993
*/
                                                
#include "stdafx.h"               
/*XX*/ #include "TRiASArcImpl.h"

#include <attribs.hxx>	  	// VisInfo  
#include <impexp.hxx>	   	// MerkmalDesription, GSTRUCT, MFELD
#include <strdup.hxx>	   	// StrDup ()

//XX#include "triasarc.hr"	   	// Resourcen-Defines
#include "triasarc.hxx"	 	// FieldNameSize, CheckName ()
#include "merkmdes.hxx"	 	// zugeh. Header-File

//  exteren Variablen
extern ResourceFile *pRF;

//  globale Funktionen -----------------------------------------------------
// GetKey-Funktion für Merkmals-Baum
void* GetMKode (void *pObj) {
	return & (((MerkmalDescription *) pObj) -> MCode ());
}

// KeyCompare-Funktion für Merkmals-Baum
int CompareMKodes (void *pObj1, void *pObj2) {
	long Merkmal1 = *((long *) pObj1);
	long Merkmal2 = *((long *) pObj2);

	if (Merkmal1 == Merkmal2)
		return 0;
	else {
		if (Merkmal1 > Merkmal2)
			return 1;
		else
			return -1;
	}
}

// Basis-Objekt erzeugen und Spalte aktualieren
ExtMerkmalDescription :: ExtMerkmalDescription (MerkmalDescription &MD,
												short &Column, short &Unknown)

					   : MerkmalDescription (MD) {
	_pName = NULL;
	_Column = Column;   // alter Wert
	_ArcColumn = 0;
	Column += MD.MLen ();

//  Merkmalsname OK ?
	char Buffer [20] = "";
	if (!Text () || !*Text ()) {
		Unknown++;
		ResString MerkText (ResID (IDS_MERKMAL, pRF), 10);
		wsprintf (Buffer, "%s%d", MerkText.Addr (), Unknown);
		_pName = CheckName (Buffer, FieldNameSize);
	} else
		_pName = CheckName (Text (), FieldNameSize);

	_RC = _pName ? EC_OKAY : EC_NOMEMORY;
}

ExtMerkmalDescription :: ~ ExtMerkmalDescription (void) {
	DELETE_VEC (_pName);
}

pchar ExtMerkmalDescription :: GetName (void) {
	if (!_pName || !*_pName)
		return NULL;
	return StrDup (_pName, RC_TRIASARC);
}

ErrCode ExtMerkmalDescription :: SetName (pchar pName) {
	if (!pName || !*pName)
		return EC_SYSERROR;
	DELETE_VEC (_pName);
	_pName = StrDup (pName, RC_TRIASARC);
	return _pName ? EC_OKAY : EC_NOMEMORY;
}

// ExtMerkmalDescriptionTree ------------------------------------------------
// Merkmal-Beschreibungs-Baum anlegen
ExtMerkmalDescriptionTree :: ExtMerkmalDescriptionTree (void)
						   : CTree (GetMKode, CompareMKodes) {
	_ActColumn = 1;		 	// aktuelle Spalte setzen (für PAT)
	_ActArcColumn = 1;	  	// für AAT
	_Unknown = 1;		   	// Anzahl unbekannter Merkmalstexte
}

void EXPORTFLT ExtMerkmalDescriptionTree :: UserDelete (void *pObj) {
	((ExtMerkmalDescription *) pObj) -> ~ExtMerkmalDescription ();
}

ExtMerkmalDescriptionTree :: ~ ExtMerkmalDescriptionTree (void) {
	EveryDelete ();
}

// neue Merkmal-Beschr. in Baum
Bool ExtMerkmalDescriptionTree :: AddMerkmDescr (MerkmalDescription &MD)
{
	CTable Tb (*this);
	if (Tb.Find (&MD.MCode ()))   // wenn Merkmal bereits existiert
		return True;

	// KK030129
	// Limitierung der Merkmalsausgabe

	long lCount = this->Count();
	if ( lCount >= ARC_LIMIT_FEATURES)
		return True;

//  neuen Eintrag erzeugen
	ExtMerkmalDescriptionCreator EMD_Cr (*this);
//XX	ExtMerkmalDescription *pEMD = Create (EMD_Cr, ExtMerkmalDescription) (MD, _ActColumn, _Unknown);
/*XX*/	ExtMerkmalDescription *pEMD = ContCreate (EMD_Cr, ExtMerkmalDescription) (MD, _ActColumn, _Unknown);
	if (pEMD && (pEMD -> Result () == EC_OKAY))
		return True;
	else
		return False;
}

// Spalte eines Merkmals über seinen Kode suchen, die im Fehlerfall 0 ist.
// (PAT)
short ExtMerkmalDescriptionTree :: FindColumn (long MCode) {
	CTable Tb (*this);
	if (!Tb.Find (&MCode))			  // wenn Merkmalskode nicht gefunden
		return 0;
	else {
		ExtMerkmalDescriptionLock pEMD (Tb);
		if (pEMD)
			return pEMD -> Column ();   // mit akt. Spalte zurück
		else
			return 0;
	}
}

// Spalte eines Merkmals über seinen Kode suchen, die im Fehlerfall 0 ist.
// (AAT)
short ExtMerkmalDescriptionTree :: FindArcColumn (long MCode) {
	CTable Tb (*this);
	if (!Tb.Find (&MCode))			  // wenn Merkmalskode nicht gefunden
		return 0;
	else {
		ExtMerkmalDescriptionLock pEMD (Tb);
		if (pEMD)
			return pEMD -> ArcColumn ();		// mit akt. Spalte zurück
		else
			return 0;
	}
}

// Spaltenbreite eines Merkmals über seinen Kode suchen, die im Fehlerfall 0 ist.
short ExtMerkmalDescriptionTree :: FindColumnWidth (long MCode) {
	CTable Tb (*this);
	if (!Tb.Find (&MCode))			  // wenn Merkmalskode nicht gefunden
		return 0;
	else {
		ExtMerkmalDescriptionLock pEMD (Tb);
		if (pEMD)
			return pEMD -> MLen ();	 // mit akt. Spaltenbreite zurück
		else
			return 0;
	}
}

//  Zeiger eines Merkmalstextes lesen, der im Fehlerfall NULL ist
//  und über delete freizugeben ist
pchar ExtMerkmalDescriptionTree :: GetMerkmalName (long MCode) {
	CTable Tb (*this);
	if (!Tb.Find (&MCode))			  // wenn Merkmalskode nicht gefunden
		return NULL;
	else {
		ExtMerkmalDescriptionLock pEMD (Tb);
		if (pEMD)
			return pEMD -> GetName ();  // mit Name zurück
		else
			return NULL;
	}
}

//  Neuen Merkmalsnamen speichern
ErrCode ExtMerkmalDescriptionTree :: SetMerkmalName (long MCode,
													 pchar pNewName) {
	CTable Tb (*this);
	if (!Tb.Find (&MCode))			  // wenn Merkmalskode nicht gefunden
		return EC_SYSERROR;
	else {
		ExtMerkmalDescriptionLock pEMD (Tb);
		if (pEMD)
			return pEMD -> SetName (pNewName);  // Namen setzen
		else
			return EC_SYSERROR;
	}
}

//  True, wenn noch ein weiteres Objekt den gesuchten Namen
//  enthält, sonst False
Bool ExtMerkmalDescriptionTree :: OtherMerkmalName (long MKode, pchar pSearchName) {
//  prüfe Parameter
	if (!pSearchName || !*pSearchName)
		return False;

	CTable Tb (*this);
	for (Tb.First (); Tb.Valid (); Tb.Next ()) {
		ExtMerkmalDescriptionLock pMD (Tb);
		if (! pMD)
			return False;			   // interner Fehler

		if (pMD -> MCode () != MKode) { // nicht für übergebenes Objekt
			pchar pName = pMD -> GetName ();
				if (lstrcmp (pName, pSearchName) == 0) {
					DELETE_VEC (pName);
					return True;
				}
			DELETE_VEC (pName);
		}
	}

	return False;
}

/*
// alle Merkmalsbeschreibungen mit ungültigen Parametern löschen
ErrCode ExtMerkmalDescriptionTree :: DeleteUnvalids (void) {
	CTable Tb (*this);
	for (Tb.First (); Tb.Valid (); ) {
		Bool toDelete = False; {
			ExtMerkmalDescriptionLock pMD (Tb);
			if (pMD) {
			//  Namen und Länge prüfen
				if (! pMD -> Text () || ! *(pMD -> Text ()) || ! pMD -> MLen ())
					toDelete = True;

			//  Typ prüfen
				if (! toDelete) {
					switch (toupper (pMD -> MTyp ())) {
						case 'A':
						case 'I':
						case 'F':
						case 'B':   // Sicht-Merkmal
						case 'C':   // Id-Merkmal
						break;
						default:
							toDelete = True;
						break;
					}
				}
			} else
				return EC_SYSERROR;
		}   // Lock aufheben
		if (toDelete) {
			if (!Tb.Delete ())	  // Eintrag aus Baum löschen
				return EC_SYSERROR;
		} else {
			if (!Tb.Next ())		// nächsten Eintrag
				break;
		}
	}
	return EC_OKAY;
}
*/
