/*
File: MERKMAL.CXX
realiert die Verwaltung einer Merkmals-Tabelle.

erarbeitet : J. Benkenstein					Stand vom 12.1.1994
*/

#include "pheader.h"

#include <ospace/file/path.h>

#include <hpp/filebuff.hxx>			// CFileBuffer

#define NOOPTPARAM
#include "optparam.hxx"			// Params
#include "filepos.hxx"			// PointEntries
#include "tools.hxx"			// CreateIdent/Merkmal
#include "textconn.hxx"			// CTextDatInfoList
#include "merkmal.hxx"	  		// zugeh. Header-File

//  externe Variablen
extern FILE *yyin;				// Eingabe-Datei
extern CTextDatInfoList *pTDI;	// ODBC-Info speichern
extern Params *pParams;  		// Klasse mit allen möglichen Parametern

//  Prototypen
extern "C"
BOOL CALLBACK __export EnumMerkmaleProc (long Key, BOOL iNotLast, void *pData);	

// void IncCounter (long ObjNr = 0);

//  Konstanten
const short RowSize = 80;		// max. Länge einer Eingabezeile
const char Separator [] = ",";	// Feld-Separator in Text-Tabellen

//  globale Funktoinen -----------------------------------------------------
void * __export GetMName (void *pObj) 
{
	return ((Merkmal *) pObj) -> MerkmalsName ();
}

int __export CompareNames (void *pObj1, void* pObj2)
{
	return strcmpi ((char *) pObj1, (char *) pObj2);
}

// Merkmal ---------------------------------------------------------------------
Merkmal::Merkmal (long MK, pchar pName, short La, short Col) 
{
	_pName = NULL;
	_MaxLa = _La = La;
	_Col = Col;
	_MK = MK;
	_Valid = MK && La && Col && pName && *pName ? True : False;
	if (pName && *pName)
	{
		_pName = new char [lstrlen (pName) + 1];
		if (!_pName) 
		{
			DEX_Error (RC_ctMerkmal, EC_NOMEMORY);
			_Result = False;
		}
		lstrcpy (_pName, pName);
	}	
	
	_Result = True;
}

Merkmal::~ Merkmal (void) 
{
	DELETE_VEC (_pName);
}

// MerkmalsBaum ------------------------------------------------------------
MerkmalsBaum:: MerkmalsBaum (void)
			  : CTree (GetMName, CompareNames) 
{
	_ActCol = 0;
	_Cnt = 0L;
	_OutTXM = False;            
	_TableType = UnknownTable;
	_pTableName = NULL;
}

void __export MerkmalsBaum::UserDelete (void *pObj) 
{
	((Merkmal *) pObj) -> ~ Merkmal ();
}

MerkmalsBaum::~ MerkmalsBaum (void) 
{
	EveryDelete ();
    DELETE_VEC (_pTableName);
}

// wenn Name gültig, dann neuen Eintrag in Liste erzeugen,
// sonst nur Spaltenzähler weitersetzen
Bool MerkmalsBaum::AddMerkmal (short La, pchar pMName, Bool UserIDFeld) {

//  gültiger Name ?
	if (!pMName || !*pMName) 
	{
		_ActCol += La;			  // nur Schreibspalte weiter
		return True;
	}                           
	
	long MKode = 0;

//  prüfen, ob Eintrag existiert ?
CTable Tb (*this);

	if (Tb.Find (pMName)) {	 // Namen suchen
		MerkmalLock pM (Tb);
		if (!pM) 
		{
			DEX_Error (RC_MerkmalAddMerkmal, EC_LOCKERROR);
			return False;
		}

	//  Werte akt.
		pM -> Valid () = True;	  // Merkmal ist wieder gültig
		pM -> MerkmalsLaenge () = La;
		pM -> MerkmalsSpalte () = _ActCol;
		if (La > pM -> MaxLa ())	// auch max. Länge ggf. akt.
			pM -> MaxLa () = La;

		_ActCol += La;				// Schreibspalte akt.
		MKode = pM -> MerkmalsKode ();
	}
	else {
	// zuerst nachsehen, ob es schon ein derartiges Attribut gibt
		MKode = DEX_GetMCodeFromFeatureNameCIEx(DEX_GetDataSourceHandle(), pMName);
		if (0 == MKode || -1 == MKode)
			MKode = DEX_GetUniqueMCode();
			
	//  neuen Eintrag erzeugen
	MerkmalCreator MC (*this);

		Merkmal *pM = ContCreate (MC, Merkmal) (MKode, pMName, La, _ActCol);
		_ActCol += La;				  // Schreibspalte akt.
		if (!pM || !pM -> Result())
			return False;
	}
	
// 	ggf. Infos für ODBC-Ausgabe abspeichern	
	if (UserIDFeld)	{
		if (pTDI) {                                            
			pTDI -> SetMKode (MKode);
			if (!pTDI -> SetKoppelFeld (pMName))
				return False;
		}
		else
			return False;
	}	
	return True;            
}

// MerkmalsBaum in PBD ausgeben
Bool MerkmalsBaum::OutTXM (void) {
//	bei "sonstiger" Tabelle Text-Datei vorher öffnen
	if (_TableType == OtherTable)
	{
		if ((_fh = OpenFile (_pTableName, &_of, OF_CREATE | OF_WRITE)) == HFILE_ERROR) 
		{
			DEX_Error (RC_MBaumOutTXM, EC_NOFILE);
			return False;
		}			
	}
            
	uint ActLen = 0;            
	CTable Tb (*this);
	for (Tb.First (); Tb.Valid (); Tb.Next ()) 
	{
		MerkmalLock pM (Tb);
		if (!pM) 
		{
			DEX_Error (RC_MBaumOutTXM, EC_LOCKERROR);
			return False;
		}

	//	ggf. Merkmal in PBD ausgeben
		if (!pM -> Valid ())			// kein ungültiges Merkmal ausgeben
			continue;
			
	//	Merkmals-Info ausgeben
		if (_fh)						// Feldnamen in Datei als erste Zeile ausgeben
		{   
			ActLen = lstrlen (pM -> MerkmalsName ());    
			if (_lwrite (_fh, pM -> MerkmalsName (), ActLen) != ActLen)
			{
				DEX_Error (RC_MBaumOutTXM, EC_NOWRITE);
				return False;	
			}				 
			
		//	Separator ausgeben                                                    
			ActLen = lstrlen (Separator);
			if (_lwrite (_fh, Separator, ActLen) != ActLen)
			{
				DEX_Error (RC_MBaumOutTXM, EC_NOWRITE);
				return False;					
			}
		}
		else							// an TRIAS ausgeben
		{			
//			if (CreateMerkmal (pM -> MerkmalsKode (), pM -> MerkmalsName (),
//						   pM -> MaxLa ()) != EC_OKAY)

// KK990927
			if (CreateMerkmal (pM -> MerkmalsKode (), pM -> MerkmalsName (),
						   pM -> MaxLa (),pParams -> ID) != EC_OKAY)

				return False;
		}			
	}                                             
	        
//	ggf. Zeilevorschub ausgeben	        
	if (_fh)
	{                 
		_llseek (_fh, -1L, 1);				//	letzten Separator löschen
		if (_lwrite (_fh, "\r\n", 2) != 2)
		{
			DEX_Error (RC_MBaumOutTXM, EC_NOWRITE);
			return False;					
		}		
		//	_lclose (_fh); Datei wird nach unmittelbar folgender Merkmalsausgabe geschlossen
	}
	
	_OutTXM = True;		// Flag für Ausgabe setzen

	return True;
}

// Merkmale einschließlich Geometrie ausgeben
Bool MerkmalsBaum::OutMerkmale (Entries *pPE, Bool CheckUniPoly, Bool Output) 
{
//  prüfe Parameter
	if (_TableType == UnknownTable) 
	{
		DEX_Error (RC_MBaumOutMerkmale, EC_SYSERROR);
		return False;
	}
	
//	Ungültige Merkmale entfernen	
	if (! DeleteUnvalids ())
		return False;
	Optimize ();							// Baum optimieren		
	
//	Flag für 1. Satz setzen	                                                          
	Bool FirstEntry = _TableType == OtherTable ? True : False;
	
//  Merkmale ggf. in PBD ausgeben
	if (Output) 
	{
		if (! OutTXM ())
		{
			Output = False;					// diese Tabelle dann überlesen	
			if (_TableType == OtherTable && pParams)
			{
				pParams -> TableCnt--; 
				pParams -> NotImported++; 
			}				
		}			
	}		
		
	pchar pBuffer = new char [_ActCol+1];	// Lesepuffer
	if (!pBuffer) 
	{
		DEX_Error (RC_MBaumOutMerkmale, EC_NOMEMORY);
		return False;
	}
	pchar pMVal = new char [_ActCol+1];		 // akt. Merkmalswert
	if (!pMVal) 
	{
                DELETE_VEC (pBuffer);
		DEX_Error (RC_MBaumOutMerkmale, EC_NOMEMORY);
		return False;
	}

//  1. Eintrag prüfen: universe polygon-Eintrag ?
	if (CheckUniPoly) 	//   1. Satz bei Polygonen überlesen
	{
		if (! _ReadNextRecord (pBuffer, _ActCol)) 
		{
            DELETE_VEC (pBuffer);
            DELETE_VEC (pMVal);
			return False;
		}
		_Cnt--;			 // interner Satzzähler
	}

//  alle Sätze ausgeben
	Bool OpFlag = True;
	CTable Tb (*this);
	long ObjNr = -1;			// aktuelle ObjektNummer
	for (long i = 1; i <= _Cnt; i++) 
	{// Speicher init.
		memset (pBuffer, ' ', _ActCol+1);
		*pBuffer = '\0';
		memset (pMVal, ' ', _ActCol+1);
		*pMVal = '\0';

	//  akt. Satz lesen
		if (! _ReadNextRecord (pBuffer, _ActCol)) 
		{
			OpFlag = False;
			break;
		}
		*(pBuffer + _ActCol) = '\0';

		if (Output)		// nur wenn Ausgabe explizit gefordert
		{
		//	Geometrie ggf. ausgeben; ObjNr lesen
			if (_TableType != OtherTable && ((ObjNr = pPE -> OutGeo (i)) == -1)) 
				continue;			// mit nächstem Objekt weiter machen

		//  alle Merkmalswerte ausgeben
			for (Tb.First (); Tb.Valid () && OpFlag; Tb.Next ()) 
			{
				MerkmalLock pM (Tb);
				if (!pM) 
				{
					DEX_Error (RC_MBaumOutMerkmale, EC_LOCKERROR);
					OpFlag = False;
					break;
				}
				if (!pM -> Valid ())	   // Eintrag gültig
					continue;

				memcpy (pMVal, pBuffer + pM -> MerkmalsSpalte (),
						pM -> MerkmalsLaenge ());
				*(pMVal + pM -> MerkmalsLaenge ()) = '\0';

			//  Text trimmen: abschließende ' ' eliminieren (außer beim 1. Satz)
				short TLen = 0;
				if (!FirstEntry)	// 1. Satz bleibt ggf. vollst. zur Ermittlung der Feldlänge durch ODBC
				{
					while (((TLen = lstrlen (pMVal)) > 0) && (*(pMVal + TLen - 1) == ' '))
						*(pMVal + TLen - 1) = '\0';
				}						

			//	Merkmalswert ausgeben
				if (_TableType == OtherTable)
				{
						OpFlag = _OutputMerkmal (pMVal);	// wenigstens Separator ausgeben					
				}   
				else 						// PAT oder AAT
				{
					if (lstrlen (pMVal))    // nur Ausgabe wenn wirklich Info vorh.
						OpFlag = OutputMerkmal (ObjNr, pM -> MerkmalsKode (),
												pMVal) == EC_OKAY ? True : False;
				}
			}
			if (! OpFlag)	// wenn Fehler bei Merkmalsausgabe
				break;
				
			if (_TableType == OtherTable)	// Zeilenvorschub ausgeben
			{
				FirstEntry = False;					// alle weiteren Werte trimmen
				_llseek (_fh, -1L, 1);				//	letzten Separator löschen
				if (_lwrite (_fh, "\r\n", 2) != 2)
				{
					DEX_Error (RC_MBaumOutMerkmale, EC_NOWRITE);
					break;
				}											
			}				
		}	// Ende der "expliziten" Ausgabe				
	}                         
	
	if (_fh)
		_lclose (_fh);

//  Speicher freigeben
        DELETE_VEC (pBuffer);
        DELETE_VEC (pMVal);

	return OpFlag;
}

//  interne Werte rücksetzen und Objekte ungültig erklären
Bool MerkmalsBaum::Reset (void) {
	_fh = NULL;
	_OutTXM = False;
	_ActCol = 0;
	_Cnt = 0;        
	_TableType = UnknownTable;
        DELETE_VEC (_pTableName);

//  alle gespeicherten Merkmale ungültig setzen
	CTable Tb (*this);
	for (Tb.First (); Tb.Valid (); Tb.Next ()) {
		MerkmalLock pM (Tb);
		if (!pM) {
			DEX_Error (RC_MBaumReset, EC_LOCKERROR);
			return False;
		}
		pM -> Valid () = False;
	}

	return True;
}

// nächsten Merkmalssatz aus Eingabe-Datei lesen
Bool MerkmalsBaum::_ReadNextRecord (pchar pBuffer, short Cnt) {
	int ch = 0;
	register ActCnt = 0;
	for (register short i = 0; i < Cnt; ) {
		ch = getc (yyin);

	//  EOF-Test
		if (ch == EOF) {
			DEX_Error (RC_MBaumReadNRec, EC_NOREAD);
			return False;
		}

		if (ch != '\n') {				  		// "normales Zeichen"
			*(pBuffer + i) = (char) ch;
			i++;
			ActCnt++;
			continue;
		}         
		// IncCounter ();                			// Zeilenzähler weiter
		pParams -> LineNr++;				   

		if (ActCnt == RowSize) {				// wenn Zeile gefüllt
			ActCnt = 0;
			continue;					   		// erwartetes \n
		}

		i += RowSize - ActCnt;					// um fehl. Zeichen weiter
		ActCnt = 0;
	}

//  letzte \n lesen
	int nch;
	if (ch != '\n') {	   // nur lesen, wenn letzte Zeichen echter Wert war
		do {
			nch = getc (yyin);
			if (nch == EOF) {
				DEX_Error (RC_MBaumReadNRec, EC_NOREAD);
				return False;
			}
		} while (nch != '\n');
		// IncCounter ();                    		// Zeilenzähler weiter
		pParams -> LineNr++;
	}

	return True;
}

Bool MerkmalsBaum::AddMerkmal (long MKode, pchar pKurzText)
{                    
	if (!pKurzText || !*pKurzText)
		return True; 
		
 	MerkmalCreator MC (*this);
    
	Merkmal *pM = ContCreate (MC, Merkmal) (MKode, pKurzText, 0, 0);
	return pM && pM -> Result ();
}

//	Tabellen-Name speichern
Bool MerkmalsBaum::StoreTableName (char *pTableName)
{
//	prüfe Parameter
	if (!pTableName || !*pTableName)
	{	// ist hier offensichtlich ein Syntax-Fehler
		DEX_Error (RC_MBaumStoreTableName, EC_SYNTAX);		
		return False;
	}			     

// Pfad der aktuellen Datenquelle hinzufügen (#HK001104)
os_path path (pTableName);
char cbPrjPath[_MAX_PATH];

	if (DEX_GetDataSourceName(DEX_GetDataSourceHandle(), cbPrjPath) && '\0' != cbPrjPath[0]) {
	os_path prjpath = os_string(cbPrjPath);

		if (prjpath.has_drive())
			path.drive(prjpath.drive()[0]);
		else if (prjpath.has_unc())
			path.unc(prjpath.server(), prjpath.share());
			
		if (prjpath.has_directory())
			path.directory(prjpath.directory());
	}
	
//	alten Namen löschen
os_string strTable = os_string(path);

	DELETE_VEC (_pTableName);
	_pTableName = new char [strTable.size() + 1];
	if (!_pTableName)
	{
		DEX_Error (RC_MBaumStoreTableName, EC_NOMEMORY);
		return False;
	}	             

//	Namen kopieren
	lstrcpy (_pTableName, strTable.c_str());	   
	return True;
}                                        

//	Merkmalswert in Text-Datei ausgeben
Bool MerkmalsBaum::_OutputMerkmal (char *pMerkmal)
{   
	uint ActLen = 0;
        
	if (pMerkmal && *pMerkmal)
	{//	Wert immer als Textfeld ausgeben: führende "                                 
		if (_lwrite (_fh, "\"", 1) != 1)
		{
			DEX_Error (RC_MBaumOutMerkmale, EC_NOWRITE);
			return False;					
		}												
	    
	    ActLen = lstrlen (pMerkmal);
	    if (_lwrite (_fh, pMerkmal, ActLen) != ActLen)
		{
			DEX_Error (RC_MBaumOutMerkmale, EC_NOWRITE);
			return False;					
		}

	//	abschließende "	
		if (_lwrite (_fh, "\"", 1) != 1)
		{
			DEX_Error (RC_MBaumOutMerkmale, EC_NOWRITE);
			return False;					
		}												
	}
	         
//	abschließenden Separator ausgeben                                                    
	ActLen = lstrlen (Separator);
	if (_lwrite (_fh, Separator, ActLen) != ActLen)
	{
		DEX_Error (RC_MBaumOutMerkmale, EC_NOWRITE);
		return False;					
	}		

	return True;
}

extern "C"  // diese Variante liefert nur die Merkmale in der GeoDB,
			// gebraucht werden aber die Merkmale der PBD.			
//  enumerieren aller Merkmale eines Projekts
BOOL CALLBACK __export EnumMerkmaleProc (long MKode, BOOL, void *pData) 
{               
//	KurzText zum Mkode lesen
	char Buffer [80] = "";
	PBDDATA Data;
	memset (&Data, 0, sizeof (PBDDATA));        // init.
	Data.dwSize = sizeof (PBDDATA);
	Data.pbdTyp = 'm';                          // Merkmal
	Data.pbdCode = MKode;
	Data.pbdKText = Buffer;
	Data.pbdKTextLen = sizeof (Buffer);
	 
#if _TRiAS_VER < 0x0300
ErrCode EC = DEX_GetPBDData (Data);

	if (EC != EC_OKAY && EC != WC_RETURN)
		return FALSE;
#else
HPROJECT hPr = DEX_GetDataSourceHandle();
ErrCode EC = DEX_GetPBDDataEx (hPr,Data);

	if (EC != EC_OKAY && EC != WC_RETURN)
		return FALSE;		
#endif
		
//	MKode und Kurztext speichern
	return ((MerkmalsBaum *) pData) -> AddMerkmal (MKode, Data.pbdKText);   
}

//	alle Projekt-Merkmale lesen    
Bool MerkmalsBaum::ReadMerkmale (void) 
{                                   
//	Daten init.
	ENUMLONGKEY Data;
	memset (&Data, 0, sizeof (Data));
	Data.eKey = 'm';									// alle Merkmale
	Data.ePtr = (void *) this;							// User-Daten	                                                                       
	Data.eFcn = (ENUMLONGKEYPROC) EnumMerkmaleProc; 	// zu rufende Funktion
			                    
#if _TRiAS_VER < 0x0300
	return DEX_EnumPBDData (Data);						// alle Merkmalskodes lesen
#else
HPROJECT hPr = DEX_GetDataSourceHandle();

	return DEX_EnumPBDDataEx (hPr,Data);				// alle Merkmalskodes lesen
#endif
}                     

// Ungültige Einträge löschen            
Bool MerkmalsBaum::DeleteUnvalids (void)
{   
	ErrCode EC = EC_OKAY;                 
	CTable Tb (*this);
	for (Tb.First (); Tb.Valid (); ) 
	{
		Bool toDelete = False; 
		{
			MerkmalLock pMD (Tb);
			if (! pMD)
			{
				EC = EC_LOCKERROR;
				break;
			}				
				
			toDelete = !pMD -> Valid ();		// Löschflag lesen
		}   // Lock aufheben
		if (toDelete) 
		{
			if (!Tb.Delete ())	  				// Eintrag aus Baum löschen
			{
				EC = EC_SYSERROR;
				break;
			}					
		} 
		else 
		{
			if (!Tb.Next ())					// nächsten Eintrag
				break;
		}
	}   
	    
//	Fehler ggf. ausgeben	         
	if (EC != EC_OKAY)
	{
		DEX_Error (RC_MBaumDeleteUnvalids, EC);
		return False;
	}	         
	         
	return True;
}

	
