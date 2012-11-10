/*
File: MERKMDES.CXX
realiert die Verwaltung eines Merkmal-Beschreibungs-Baumes.

erarbeitet : J. Benkenstein                 Stand vom 12. April 1994
*/

#include "stdafx.h"
#include "AcadDXFImpl.h"

#include <attribs.hxx>      // VisInfo  
#include <impexp.hxx>       // MerkmalDesription, GSTRUCT, MFELD
#include <strdup.hxx>       // StringDup

//XX#include "acaddxf.hr"           // Resourcen-Defines
#include "acaddxf.hxx"      // AcadDxfExportLine ()
#include "identdes.hxx"     // IdentDesrciption
#include "merkmdes.hxx"     // zugeh. Header-File

// globale Konstanten
const double xPosMText = 5.0;                   // Koordinaten des Merkmaltextes an Symbolen
const double yPosMText = 5.0;

// externe Variablen                           
extern Bool ValidMKodes;                        // Merkmals-Kodes-Flag
extern Bool AlleMerkmale;                       // alle Merkmale exportieren Flag
extern char pIniFilePath [_MAX_PATH];           // vollst. Ini-File-Name
extern ResourceFile *pRF;
extern double StandTextHoehe;
extern double StandTextHoeFaktor;
extern ExtIdentDescriptionTree *pIDT;
extern char StandardLayerName [MinLayerSize];   // Standard-Layer-Name

// GetKey-Funktion für Merkmals-Baum
void* GetMKode (void *pObj)
{
    return & (((MerkmalDescription *) pObj) -> MCode ());
}

// KeyCompare-Funktion für Merkmals-Baum
int CompareMKodes (void *pObj1, void *pObj2)
{
    long Merkmal1 = *((long *) pObj1);
    long Merkmal2 = *((long *) pObj2);

    if (Merkmal1 == Merkmal2)
		return 0;
    else
		if (Merkmal1 > Merkmal2)
	    	return 1;
		else
	    	return -1;
}

// Basis-Objekt erzeugen und Spalte aktualieren
ExtMerkmalDescription :: ExtMerkmalDescription (MerkmalDescription &MD)
		       		   : MerkmalDescription (MD)
{
    char Buffer [81] = "";      // Lese-Puffer

//  Darstellungs-Attribut bilden
    ResString RS (ResID (IDS_MERKMALSKODES, pRF), 80);
    ResString RS1 (ResID (IDS_MERKMKODEKENNUNG, pRF), 80);

    char MerkmCode [15] = "";
    lstrcpy (MerkmCode, RS1.Addr ());       // Kennung f. Merkmalskode
    ltoa (MD.MCode (), Buffer, DEX_GetMkBase ());
    lstrcat (MerkmCode, Buffer);            // MerkmalsKodeString komplett.
    if (GetPrivateProfileString (RS.Addr (), MerkmCode, "",
	    Buffer, sizeof (Buffer) - 1 , pIniFilePath)) { // wenn kein Eintrag gef.
		_describe = present;
		ValidMKodes = True;    // setzen, wenn wenigstens 1 gültiger Kode ex.

    //  Test auf Sichtbarkeit
		RS = ResString (ResID (IDS_MERKMVISIBLE, pRF), 80);
		if (!lstrcmp (Buffer, RS.Addr ()))
	    	_describe |= visible;
		else {
	    	RS = ResString (ResID (IDS_MERKMINVISIBLE, pRF), 80);
	    	if (!lstrcmp (Buffer ,RS.Addr ()))
			_describe |= invisible;
		}
    } else {    // wenn kein Eintrag in Merkmalskodes-Section
		if (AlleMerkmale) {         // wenn globales Flag gesetzt
	    	_describe = present;
	    	_describe |= invisible; // Standard ist unsichtbar
	    	ValidMKodes = True; // setzen, wenn wenigstens 1 gültiger Kode ex.
		} else {
	   		_describe = not_present;
		}
    }
}

ExtMerkmalDescription :: ~ ExtMerkmalDescription (void)
{
    // nothing to do
}

// Merkmal-Beschreibungs-Baum anlegen
ExtMerkmalDescriptionTree :: ExtMerkmalDescriptionTree (void)
						   : CTree (GetMKode, CompareMKodes)
{
    ValidMKodes = False;            // keine gültigen MerkmalKodes
}

void EXPORTFLT ExtMerkmalDescriptionTree :: UserDelete (void *pObj)
{
    ((ExtMerkmalDescription *) pObj) -> ~ExtMerkmalDescription ();
}

ExtMerkmalDescriptionTree :: ~ ExtMerkmalDescriptionTree (void)
{
    EveryDelete ();
}

// neue Merkmal-Beschr. in Baum
Bool ExtMerkmalDescriptionTree :: AddMerkmDescr (MerkmalDescription &MD)
{
    CTable Tb (*this);
    if (Tb.Find (&MD.MCode ()))   // wenn Merkmal bereits existiert
		return True;

//  neuen Eintrag erzeugen
    ExtMerkmalDescriptionCreator EMD_Cr (*this);
//XX	    return Create (EMD_Cr, ExtMerkmalDescription) (MD) ? True : False;
/*XX*/	    return ContCreate (EMD_Cr, ExtMerkmalDescription) (MD) ? True : False;
}

// Attribut-Definitionen ausgeben
ErrCode ExtMerkmalDescriptionTree :: OutputAttrDef (int fh, MFELD *pMF0)
{
    ErrCode EC = EC_OKAY;
    double yKoord = yPosMText;  // Koordinaten für Textausgabe
    char Buffer [15] = "";
    char pFormat [] = "%-7.2f";
    char pxKoord [15] = "";

//  gültige MKodes-gefunden ?
    if (!ValidMKodes)
		return EC_OKAY;

//  X-Koordinate bleibt konstant
    DtoA (pxKoord, pFormat, xPosMText);

// KK001011 _ StartCode für MFeld
	MFELD * pMF;

    CTable Tb (*this);
	Bool bFound = False;
    for (Tb.First (); Tb.Valid (); Tb.Next ()) 
	{
		pMF = pMF0;

		ExtMerkmalDescriptionLock pEMD (Tb);
		if (pEMD && pEMD -> isPresent ()) 
		{
		//	ggf. Merkmal in der aktuellen Ausgabeliste suchen
			if (!pMF)
				bFound = True;
			{
				for (bFound = False; pMF && pMF->MCode; pMF++)
				{
					if (pEMD->MCode() == pMF->MCode)
					{
						bFound = True;
						break;					
					}
				}
			}

			if (!bFound)
				continue;

			if ((EC = ExportRecord (fh, 0, "ATTDEF")) < 0)  // Vorspann
				return EC;
	    	if ((EC = ExportRecord (fh, 8, StandardLayerName)) < 0) // Layer-Name
				return EC;
	    	if ((EC = ExportRecord (fh, 10, pxKoord)) < 0)
				return EC;                                  // x-Koordinate
	    	if ((EC = ExportRecord (fh, 20, DtoA (Buffer, pFormat, yKoord))) < 0)
				return EC;

// KK001009 - StandardTextHöhe 0 0 : 
//	    	yKoord -= (2 * StandTextHoehe);

	    	if ((EC = ExportRecord (fh, 40, DtoA (Buffer, "%-4.1f", StandTextHoehe))) < 0) // Text-Höhe
				return EC;
	    	if ((EC = ExportRecord (fh, 1, " ")) < 0)   // vordef. Wert
				return EC;

			if ((EC = ExportRecord (fh, 2, pEMD->Text ())) < 0)
				return EC;              // Tag für eigentlichen Wert
	    	if ((EC = ExportRecord (fh, 3, ltoa (pEMD->MCode(), Buffer, DEX_GetMkBase()))) < 0) // Anfrage-Text
				return EC;

	    	if ((EC = ExportRecord (fh, 70, 
	    			  pEMD -> isVisible () ? "     4":"     1")) < 0) // Sichtbarkeits-Flag
				return EC;
		}
    }
    return EC;
}

// die aktuellen Attribut-Werte ausgeben
ErrCode ExtMerkmalDescriptionTree :: OutputAttrVal (int fh, GSTRUCT &GS, MFELD *pMF)
{
    ErrCode EC = EC_OKAY;
    double yKoord = GS.y [0];
    char pTextHoehe [10] = "";
    char Buffer [15] = "";      

//  gültige MKodes-gefunden ?
    if (!ValidMKodes)
		return EC_OKAY;

//  Parameter-Test
    if (!pIDT)              // Ident-Beschreibungs-Baum
		return EC_OKAY;

//  TextHoehe für alle Merkmale konstant


	double dTextHoehe = StandTextHoehe * StandTextHoeFaktor;
	if (dTextHoehe <= 0.0)
		dTextHoehe = StandTextHoehe;

    DtoA (pTextHoehe, "%-4.1f", dTextHoehe);

//  Layer-Namen suchen
    StringDup LayerName (pIDT -> FindName (GS.Id), False);
    if (!LayerName)     // nicht gef. oder kein Speicher zum kopieren
		return EC_NOMEMORY;

//  für alle Merkmale
    CTable Tb (*this);
	char *pMValue = NULL;
    while (pMF -> MCode) {
		if (Tb.Find (& pMF -> MCode)) { // wenn Eintrag gefunden
	    	ExtMerkmalDescriptionLock pEMD (Tb);
	    	if (pEMD && pEMD -> isPresent ()) { // wenn durch Nutzer eingestellt
				if ((EC = ExportRecord (fh, 0, "ATTRIB")) < 0)  // Attribute-Kopf
		    		return EC;
				if ((EC = ExportRecord (fh, 8, StandardLayerName)) < 0) // Ebenen-Name
		    		return EC;
				if ((EC = ExportPunkt (fh, 10, 20, GS.x [0], yKoord)) < 0)
		    		return EC;              // x-Koordinate bleibt konstant

// KK001009 - Höhe wird 0 : absolute Notvariante !!! da Benki-Hoehe bei allen Koordinaten = 10 !!!!!
// KK001009 - Notlösung yKoord nicht verändern - !!! = StandardTexthöhe = 0 , da unterschiedliche Koo.systeme
//				yKoord -= (2 * StandTextHoehe);

				if ((EC = ExportRecord (fh, 40, pTextHoehe)) < 0) // Text-Hoehe
		    		return EC;
				
			// 	Merkmalswert ausgeben			
				if (!(pMValue = CheckUmlaute (pMF -> MText))) // Umlaute ersetzen
					return EC_NOMEMORY;
				if ((EC = ExportRecord (fh, 1, pMValue)) < 0) 
		    		return EC;
				DELETE_VEC (pMValue);

			/*
				if ((EC = ExportRecord (fh, 2, ltoa (pMF -> MCode, Buffer, DEX_GetMkBase ()))) < 0)
		    		return EC;          // Merkmals-Kode
			*/
				if ((EC = ExportRecord (fh, 2, pEMD->Text ())) < 0)
		    		return EC;          // Merkmals-Beschreibung

	    	//  Sichtbarkeits-Flag ausgeben
				if ((EC = ExportRecord (fh, 70, pEMD -> isVisible () ? "     4":"     1")) < 0)
		    		return EC;
	    	}
		}
		pMF++;           // nächstes Merkmal
    }

//  Ende der Merkmals-Kette setzen
    if ((EC = ExportRecord (fh, 0, "SEQEND")) < 0)
		return EC;
    if ((EC = ExportRecord (fh, 8, LayerName)) < 0) // Ebenen-Name
		return EC;

    return EC;
}

// alle nicht für den Export vorgesehenen Merkmalsbeschreibungen löschen
ErrCode ExtMerkmalDescriptionTree :: DeleteUnvalids (void)
{
    CTable Tb (*this);
    for (Tb.First (); Tb.Valid (); ) {
		Bool toDelete = False; {
	    	ExtMerkmalDescriptionLock pMD (Tb);
	    	if (pMD)
				toDelete = ! pMD -> isPresent ();
	    	else
				return EC_SYSERROR;
		}   // Lock aufheben
		if (toDelete) {
	    	if (!Tb.Delete ())      // Eintrag aus Baum löschen
				return EC_SYSERROR;
		} else {                    // nächsten Satz
	    	if (!Tb.Next ())
			break;
		}
    }
    return EC_OKAY;
}
