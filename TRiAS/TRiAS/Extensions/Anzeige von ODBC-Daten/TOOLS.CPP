/*
File: TOOLS.CPP
Das Modul beinhaltet allgemeine Funktionen zur Kommunikation mit TRIAS

Erarbeitet: J. Benkenstein                      Stand vom 4.Dezember 1995
*/

#include "pheader.h"
#include "odbcext.hr"           // ResourceKonstanten

#include <hpp/objinfo.hpp>				// LangTextLen
#include <hpp/getodbci.hpp>				// COdbcInfos
#include "importpa.hpp"             // CImportParams
#include "tools.hpp"                // zugeh. Header

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// 	Konstanten
const char UnIDSep [] = "_";    	// Separator für Unique Ident

// 	externe Variablen
extern CImportParams *g_pCParams;      // Speicher für allg. Parameter

//  Merkmal für ein bestimmtes Objekt ausgeben
ErrCode OutputMerkmal (long lObjNummer, ulong MerkmalsKode, const char *pMerkmalsText) 
{
	ASSERT (lObjNummer > 0);
	ASSERT (MerkmalsKode > 0);
	ASSERT (pMerkmalsText != NULL && AfxIsValidString (pMerkmalsText));

	TARGETMERKMALEX TM;
	memset (&TM, 0, sizeof (TARGETMERKMALEX));              // init.
	TM.dwSize = sizeof (TARGETMERKMALEX);
	TM.lTarget = lObjNummer;
	TM.lMCode = MerkmalsKode;
	TM.imaxLen = lstrlen (pMerkmalsText);
	TM.iTTyp = TT_Objekt;
	TM.pMText = (char *) pMerkmalsText;         
	TM.iFlags = TMNoCaching;
	return DEX_ModTextMerkmal (TM);
}

//  Unique Ident für ein bestimmtes Objekt ausgeben
ErrCode OutputUniqueIdent (long lObjNr) 
{
// 	prüfe Parameter	
	ASSERT (g_pCParams != NULL);
	ASSERT (!g_pCParams -> m_strTableName.IsEmpty ());
	ASSERT (lObjNr > 0);

	TRY
	{
		CString strInfo, strFormat;
		char *pInfo = strInfo.GetBuffer (g_pCParams -> m_strTableName.GetLength () + 20);
		strFormat.LoadString (IDS_UNIQUE_IDENT);		
		wsprintf (pInfo, strFormat, (const char *) g_pCParams -> m_strTableName, lObjNr);
		return OutputMerkmal (lObjNr, g_pCParams -> m_ulUnIdMKode, (const char *) strInfo); // Merkmal ausgeben
	}
	CATCH (CMemoryException, me)
	{
		DEX_Error (RC_OdbcImport, EC_NOMEMORY);
	}
	END_CATCH              
	
	return EC_NOMEMORY;
}

//  Geometrie eines Punktes ausgeben
//  und von TRIAS gebildete ObjektNummer zurückgeben,
//  die im Fehlerfall -1 ist
//  unique Ident Merkmal ausgeben
long OutputPunkt (double KoordX, double KoordY, ulong ID) 
{
//	prüfe Parameter
	ASSERT (ID > 0);
	ASSERT (g_pCParams != NULL);

	OBJGEOMETRIE OG;
	memset (&OG, 0, sizeof (OBJGEOMETRIE));   // Struktur init.
	OG.dwSize = sizeof (OBJGEOMETRIE);
	OG.lONr = -1;
	OG.lIdent = ID;
	OG.iObjTyp = OGPunkt;
	OG.iFlags = (short) (OGConverted |   	// double Koordinaten
				OGNewObject |           	// neues Object erzeugen
				OGNoMemoryObject);       	// nicht im Speicher halten
				
	OG.lCnt = 1;                      		// Anzahl Stützpunkte
	OG.pdblX = &KoordX;                 	// Koordinaten
	OG.pdblY = &KoordY;

//  Object in TRIAS speichern
	Bool bImported = DEX_ModObjGeometrie (OG);
	if (!bImported && OG.lONr <= 0)
	{                       
		g_pCParams -> m_lErrImpCnt++;
		return -1;
	}   
	else
		g_pCParams -> m_lNewCnt++;     // neues Objekt importiert             				            

	return OutputUniqueIdent (OG.lONr) == EC_OKAY ?  OG.lONr : -1;
}

//	Punkt-Geometrie modif.
BOOL ModPunktGeometrie (long lObjNr, double dX, double dY)
{
//	prüfe Parameter
	ASSERT (g_pCParams != NULL);
	ASSERT (lObjNr > 0);

	OBJGEOMETRIE og;

	memset (&og, 0, sizeof (og));			// init.
	og.dwSize = sizeof (og);				// Größe der Struktur
	og.lONr = lObjNr;						// ObjektNummer
	og.pdblX = &dX;
	og.pdblY = &dY;
	og.iObjTyp = OGPunkt;
	og.lCnt = 1;							// 1 Koordinate
	og.iFlags = (short) (OGConverted |		// double Koordinaten
						 OGIgnoreIdent |	// Id ignorieren
						 OGNoMemoryObject | // nicht im Speicher halten
						 OGModObject);		// Geometrie des Objektes ersetzen		

//  Object in TRIAS modifizieren
	if (DEX_ModObjGeometrie (og))
	{
		g_pCParams -> m_lImpCnt++;			// abgeglichenes Objekt                  				            
		return TRUE;
	}
	
	g_pCParams -> m_lErrImpCnt++;			// Fehler beim Abgleich
	return FALSE;
}


