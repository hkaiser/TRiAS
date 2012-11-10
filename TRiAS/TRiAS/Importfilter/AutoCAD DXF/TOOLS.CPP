/*
File: TOOLS.CPP
Das Modul beinhaltet allgemeine Funktionen zur Kommunikation mit TRIAS

Erarbeitet: J. Benkenstein                      Stand vom 21. August 1995
*/

#include "pheader.hpp"

// KK000125
#include <resstrg.h>            	// TRIAS-Resourcen

#include <stdlib.h>					// ltoa ()
#include <assert.h>					// assert ()
#include <new>						// bad_alloc

#include <errinstx.hxx>             // ErrInstall
#include <xtensnn.h>				// DEXN_PBDIdentChanged ()
#include <float.h>					// DBL_MIN

#include "optparam.hpp"             // Params
#include "tools.hpp"                // zugeh. Header
#include "header.hpp"

#if _MSC_VER >= 1100
using std::bad_alloc;
#endif // _MSC_VER >= 1100

//  Konstanten
const short UnIDLen = MaxFileSize + 20;  // max. Länge des zugeh. Merkmalstextes
const short KurzTextLen = 32;   	// max. Länge eines KurzTextes
const short LangTextLen = 80;   	// max. Länge eines LangTextes
const char UnIDSep [] = "_";    	// Separator für Unique Ident
const char DecPoint = '.';			
const short DecPlaces = 3;			// 2 Stellen nach dem Komma	

//  externe Variablen
extern Params OptParams;            // Speicher für allg. Parameter
extern char CommentBuffer [];		// Puffer für akt. Kommentar	

//  externe Funktionen
void IncCounter (long ObjNr = 0);
void yyerror (short);

//	Wert auf 2 Stellen nach dem Komma abschneiden
void SetTwoDec (char *pText)
{
	if (!pText)
		return;

//	Suche Dezimalpunkt
	char *pDP = strchr (pText, DecPoint);
	if (pDP)
	{
	//	wenn mehr als 2 Stellen nach dem Dezimalpunkt vorhanden
		if ((pText + strlen (pText)) > (pDP + DecPlaces))
			pDP [DecPlaces] = '\0';		//	Wert abschneiden
	}	
}

//  Unique Ident für ein bestimmtes Objekt ausgeben
ErrCode OutputUniqueIdent (long ObjNr,ulong ulID) 
{
	char Buffer [MaxFileSize + 15] = "";
	lstrcpy (Buffer, OptParams.pFileName);          // kurzen Dateinamen
	lstrcat (Buffer, UnIDSep);                      // "_"
	ltoa (ObjNr, &Buffer [lstrlen (Buffer)], 10);   // Nummer anhängen

	if (0 == OptParams.UnIdMKode) {
// KK 990927
#if _MSC_VER >= 1100
		HPROJECT hPr = DEX_GetObjectsProject(ulID);
		ulong MerkmalsKode = DEX_GetUniqueIdentMCodeEx (hPr);
		OptParams.UnIdMKode = MerkmalsKode;
#else
		ulong MerkmalsKode = DEX_GetUniqueIdentMCode ();
		OptParams.UnIdMKode = MerkmalsKode;
#endif

	}

	ResString Text (ResID (IDS_UNIQUEIDENT), 30);
	CreateMerkmal (OptParams.UnIdMKode, (pchar) Text.Addr () , UnIDLen, ulID);

	return OutputMerkmal (ObjNr, OptParams.UnIdMKode, Buffer); // Merkmal ausgeben
}

//  Merkmal für ein bestimmtes Objekt ausgeben
ErrCode OutputMerkmal (long lObjNummer, ulong MerkmalsKode, pchar pMerkmalsText) 
{
//	prüfe Parameter
	assert (lObjNummer != 0);
	assert (MerkmalsKode != 0);
	assert (pMerkmalsText);


	if ((0 == lObjNummer) || (0 == MerkmalsKode) || !pMerkmalsText)
	{
		yyerror (IDS_SYSERROR);
		return EC_SYSERROR;
	}

	if (!*pMerkmalsText)
		return EC_OKAY;

	ErrCode ec = EC_OKAY;
	char *pText = NULL;

	try
	{
		int iLen = strlen (pMerkmalsText);
		pText = new char [iLen + 1];
		strcpy (pText, pMerkmalsText);

		TARGETMERKMALEX TM;
		memset (&TM, 0, sizeof (TARGETMERKMALEX));              // init.
		TM.dwSize = sizeof (TARGETMERKMALEX);
		TM.lTarget = lObjNummer;
		TM.lMCode = MerkmalsKode;
		TM.imaxLen = iLen;
		TM.iTTyp = TT_Objekt;
		TM.pMText = pText;         
		TM.iFlags = TMNoCaching;
		ec = DEX_ModTextMerkmal (TM);
	}
	catch (bad_alloc)
	{
		yyerror (IDS_NOMEMORY);
		ec = EC_NOMEMORY;
	}

	DELETE_VEC (pText);
	
	return ec;
}

//  neuen Identifkator in der PBD erzeugen
//  (falls noch nicht vorhanden)
ErrCode CreateIdent (ulong ID, char *pText) {
//  Fehlermeldung von TRIAS ausschalten
	ErrInstall E1 (WC_NOIDENT);

// KK990927
//  ggf. Header komplettieren
	Header HD;

		if (! HD.GetUniqueIdent (OptParams.UnIdMKode,ID))  	// unique Ident MK lesen
			return WC_NOMERKMAL;

		if (! HD.GetTextObjMKode (OptParams.TextMKode,ID))  	// TextObjMKode lesen
			return WC_NOMERKMAL;

		if (OptParams.m_bImpTextDrehWi)
		{
			if (! HD.GetTextObjWinkel (OptParams.m_ulTextWinkel,ID))  	// TextObjWinkelMCode lesen
				return WC_NOMERKMAL;
		}
		if (OptParams.m_bImpTextHoehe)
		{
			if (! HD.GetTextObjHoehe (OptParams.m_ulTextHoehe,ID))  	// TextObjHoeheMCode lesen
				return WC_NOMERKMAL;
		}
		if (OptParams.m_bImpSymDrehWi)
		{
			if (! HD.GetSymObjWinkel (OptParams.m_ulSymWinkel,ID))  	// SymbolObjWinkelMCode lesen
				return WC_NOMERKMAL;
		}
		if (OptParams.m_bImpComment)
		{
			if (! HD.GetComment (OptParams.m_ulComment,ID))  			// CommentMCode lesen
				return WC_NOMERKMAL;
		}

// KK990927

	
	PBDDATA Data;
	memset (&Data, '\0', sizeof (PBDDATA));         // init.
	Data.dwSize = sizeof (PBDDATA);
	Data.pbdTyp = 'i';                              // Typ
	Data.pbdCode = ID;
	Data.pbdTemp = False;  	// ID soll fest sein

#if _MSC_VER < 1100
	if (DEX_GetPBDData (Data) == EC_OKAY)           // wenn bereits vorh.
#else
	HPROJECT hPr = DEX_GetObjectsProject(ID);
	if (DEX_GetPBDDataEx (hPr,Data) == EC_OKAY)           // wenn bereits vorh.
#endif
		return EC_OKAY;                             // dann zurück

//  Text ggf. trimmen
	short Len = 0;
	//while (((Len = lstrlen (pText)) > 0) && (*(pText + Len - 1) == ' '))
	//	*(pText + Len - 1) = '\0';

//  LangText setzen
	Len = lstrlen (pText);
	if (Len > LangTextLen)                      	// LangText ggf. begrenzen
		*(pText + LangTextLen) = '\0';
	Data.pbdLTextLen = Len;
	Data.pbdLText = pText;

//  KurzText setzen
	Len = lstrlen (pText);
	if (Len > KurzTextLen)                        	// KurzText ggf. begrenzen
		*(pText + KurzTextLen) = '\0';
	Data.pbdKTextLen = Len;
	Data.pbdKText = pText;

#if _MSC_VER < 1100
	ErrCode EC = DEX_ModPBDData (Data);
#else
	ErrCode EC = DEX_ModPBDDataEx (hPr,Data);
#endif

	if (EC == EC_OKAY)
		DEXN_PBDIdentChanged (ID);
	else           
		yyerror (IDS_NO_IDENT);
	return EC;
}

//  neues Merkmal in der PBD erzeugen
//  (falls noch nicht vorhanden)
//ErrCode CreateMerkmal (ulong MK, pchar pText, short MaxLen) {
ErrCode CreateMerkmal (ulong MK, pchar pText, short MaxLen, ulong ID) {
//  Fehlermeldung von TRIAS ausschalten
	ErrInstall E1 (WC_NOMERKMAL);
// KK990927

#if _MSC_VER < 1100
	PBDMERKMAL Data;
	memset (&Data, '\0', sizeof (PBDMERKMAL));  // init.
	Data.dwSize = sizeof (PBDMERKMAL);
#else
	PBDMERKMALEX Data;
	memset (&Data, '\0', sizeof (PBDMERKMALEX));  // init.
	Data.dwSize = sizeof (PBDMERKMALEX);
#endif

	Data.pbdTyp = 'm';                          // Merkmal
	Data.pbdCode = MK;

#if _MSC_VER < 1100
	ErrCode EC = DEX_GetPBDData (Data);
#else
	Data.lIdent = ID;
	HPROJECT hPr = DEX_GetObjectsProject(ID);
	ErrCode EC = DEX_GetPBDDataEx (hPr,Data);
#endif


	if (EC == EC_OKAY && MaxLen <= Data.ipbdMLen)   // wenn bereits vorh.
		return EC_OKAY;                             // dann zurück

//	if (EC != EC_OKAY) {            // wenn noch nicht vorh. - // KK990927 raus
	//  Text ggf. trimmen
		short Len = 0;
		//while (((Len = lstrlen (pText)) > 0) && (*(pText + Len - 1) == ' '))
		//	*(pText + Len - 1) = '\0';

	//  LangText setzen
		Len = lstrlen (pText);
		if (Len > LangTextLen)                             	// LangText ggf. begrenzen
			*(pText + LangTextLen) = '\0';
		Data.pbdLTextLen = Len;
		Data.pbdLText = pText;

	//  KurzText setzen
		Len = lstrlen (pText);
		if (Len > KurzTextLen)                             	// KurzText ggf. begrenzen
			*(pText + KurzTextLen) = '\0';
		Data.pbdKTextLen = Len;
		Data.pbdKText = pText;
		Data.ipbdMTyp = 'a';                               	// Objekt-Merkmal
//	}	// KK990927

//  diese Länge ggf. vergrößern
	Data.ipbdMLen = MaxLen;                              	// max. Länge des Merkmals


#if _MSC_VER < 1100
	EC = DEX_ModPBDData (Data);
#else
	EC = DEX_ModPBDDataEx (hPr,Data);
#endif

	if (EC == EC_OKAY)
		DEXN_PBDMCodeChanged (MK);
	return EC;
}

//	Textobjekt an TRiAS ausgeben
long OutputText (char *pText, double dKoordX, double dKoordY, ulong ulID)
{
//	prüfe Parameter
	if (!pText)
		return -1;

//	Textwert ausgeben
	TEXTGEOMETRIE TG;
	memset (&TG, 0, sizeof (TEXTGEOMETRIE));        // init.
	TG.dwSize = sizeof (TEXTGEOMETRIE);
	TG.lONr = -1;                                   // noch keine vorhanden
	TG.lIdent = ulID;
	TG.iObjTyp = OGText;
	TG.iFlags = (short)(OGConverted |   // double Koordinaten
				OGNewObject |           // neues Object erzeugen 
				OGForceGeometry |   	// auch außerhalb des akt. DB-Containers
				OGNoMemoryObject);      // nicht im Speicher halten

//  textspezifische Attribute init.
	TG.lCnt = 1;                        // Anz. Stützpkte.
	TG.iKCnt = strlen (pText);			// max. Textlänge
	
	TG.pdblX = &dKoordX;                                         
	TG.pdblY = &dKoordY;
	if (OptParams.bAnsiiText)			// Ansi-Text erzeugen
		OemToAnsi (pText, pText);
	TG.pText = pText;

//  Object an TRIAS ausgeben      
#if _TRiAS_VER >= 0x0300
	GEOMETRIEWITHCS GCS;

	INITSTRUCT(GCS, GEOMETRIEWITHCS);
	GCS.pOG = (OBJGEOMETRIE *)&TG;
	GCS.pICS = ((CImpDxfExtension *)g_pTE)->get_CS();

	HPROJECT hPr = DEX_GetObjectsProject(ulID);
	Bool bImported = DEX_ModObjGeometrieEx (hPr, GCS);
#else
	Bool bImported = DEX_ModObjGeometrie (TG);
#endif

//	if (! bImported && TG.lONr <= 0)	// KK991008
	if (! bImported )
	{
		OptParams.NotImported++;

// KK991008
		if (TG.lONr != -1 ) {
			ErrInstall EI (EC_INVADDR);

			DEX_DeleteObject(TG.lONr);

		}

// KK991011
//		if (OptParams.bDebugOutput)
		{              
			ResString Error (ResID (IDS_NOTEXTIMPORT, &g_pTE -> RF ()), 50);
			OutputDebugString (Error.Addr ());
	// KK991011			
			yyerror ( IDS_NOTEXTIMPORT);
		}                       
		return -1;
	}               

//	Unique Ident ausgeben
	if (EC_OKAY != OutputUniqueIdent (TG.lONr,ulID)) 
		return -1;
	
	IncCounter (TG.lONr);   		// Status aktualisieren         
	if (bImported)
	    OptParams.TextCnt++;
	else
		OptParams.BugImported++;  	// mit Geometriefehler importiert	    	

	return TG.lONr;
}

//  Geometrie eines/r Punktes/Linie ausgeben
//  und von TRIAS gebildete ObjektNummer zurückgeben,
//  die im Fehlerfall -1 ist
//  unique Ident Merkmal ausgeben
long OutputPunktLinie (double *pKoordX, double *pKoordY, ulong ID, long Cnt, Bool Typ) 
{
//	Fehlermeldung ausschalten 
	// ErrInstall E1 (EC_ILLPARS);
	// ErrInstall E2 (WC_BADCOORD);

	// KK991007
	ErrInstall E2 (WC_BADCOORD);

	OBJGEOMETRIE OG;
	memset (&OG, 0, sizeof (OBJGEOMETRIE));   // Struktur init.
	OG.dwSize = sizeof (OBJGEOMETRIE);
	OG.lONr = -1;
	OG.lIdent = ID;
	OG.iObjTyp = Typ ? OGPunkt : OGLinie;
	OG.iFlags = (short) (OGConverted |		// double Koordinaten
				OGForceGeometry |			// Geometrie nicht prüfen
				OGNewObject |				// neues Object erzeugen
				OGNoMemoryObject);			// nicht im Speicher halten
				
	OG.lCnt = Cnt;                      // Anzahl Stützpunkte
	OG.pdblX = pKoordX;                 // Koordinaten
	OG.pdblY = pKoordY;

//  Object in TRIAS speichern

#if _TRiAS_VER >= 0x0300
	GEOMETRIEWITHCS GCS;

	INITSTRUCT(GCS, GEOMETRIEWITHCS);
	GCS.pOG = &OG;
	GCS.pICS = ((CImpDxfExtension *)g_pTE)->get_CS();

	HPROJECT hPr = DEX_GetObjectsProject(ID);
	Bool bImported = DEX_ModObjGeometrieEx (hPr, GCS);
#else
	Bool bImported = DEX_ModObjGeometrie (OG);
#endif

//	if (!bImported && OG.lONr <= 0)	// KK991008
	if (!bImported)
	{                       
		OptParams.NotImported++;

// KK991008
		if (OG.lONr != -1 ) {
			ErrInstall EI (EC_INVADDR);

			DEX_DeleteObject(OG.lONr);

		}

// KK991011
//		if (OptParams.bDebugOutput)
		{
			if (OG.iObjTyp == OGLinie)                   
			{
				ResString ErrorLinie (ResID (IDS_NOLINEIMPORT, &g_pTE -> RF ()), 50);
				OutputDebugString (ErrorLinie.Addr ());                             
	// KK991011			
				yyerror ( IDS_NOLINEIMPORT);
			}                               
			else
			{   
				ResString Error (ResID (IDS_NOPUNKTIMPORT, &g_pTE -> RF ()), 50);
				OutputDebugString (Error.Addr ());                   
	// KK991011			
				yyerror ( IDS_NOPUNKTIMPORT);
			}                               
		}
		return -1;
	}               

	if (OutputUniqueIdent (OG.lONr,ID) == EC_OKAY) 
	{
		IncCounter (OG.lONr);   // Status aktualisieren 
	
	//  Zähler erhöhen
		if (Typ)
		{
			if (bImported)
				OptParams.PointCnt++;                  
			else
				OptParams.BugImported++;				
		}			
		else
		{       
			if (bImported)
				OptParams.LineCnt++;                   
			else
				OptParams.BugImported++;				
		}			
		return OG.lONr;                  // Objekt-Nummer zurück
	} else
		return -1;
}

//  Geometrie einer Fläche ausgeben
//  und von TRIAS gebildete ObjektNummer zurückgeben,
//  die im Fehlerfall -1 ist
//  unique Ident Merkmal ausgeben
long OutputFlaeche (double *pKoordX, double *pKoordY, long Cnt, ulong ID)
{
//	Fehlermeldung ausschalten 
	// ErrInstall E1 (EC_ILLPARS);
	// ErrInstall E2 (WC_BADCOORD);

	// KK991007
	ErrInstall E2 (WC_BADCOORD);

	OBJGEOMETRIE OG;
	memset (&OG, 0, sizeof (OBJGEOMETRIE));   // Struktur init.
	OG.dwSize = sizeof (OBJGEOMETRIE);
	OG.lONr = -1;
	OG.lIdent = ID;
	OG.iObjTyp = OGFlaeche;
	OG.iFlags = (short)(OGConverted |   // double Koordinaten
				OGForceGeometry |       // Geometrie nicht prüfen 
				OGNoMemoryObject |      // nicht im Speicher halten
				OGNewObject);           // neues Object erzeugen 
				
	OG.lCnt = Cnt;                      // Anzahl der Stützpunkte
	OG.pdblX = pKoordX;                 // Koordinaten
	OG.pdblY = pKoordY;
	OG.iKCnt = 1;                    	// Größe des Konturfeldes (Anz. Inseln + 1)
	long CntVec [] = { Cnt };
	OG.plCnt = CntVec;                  // Konturfeld

//  Object in TRIAS speichern

#if _TRiAS_VER >= 0x0300
	GEOMETRIEWITHCS GCS;

	INITSTRUCT(GCS, GEOMETRIEWITHCS);
	GCS.pOG = &OG;
	GCS.pICS = ((CImpDxfExtension *)g_pTE)->get_CS();

	HPROJECT hPr = DEX_GetObjectsProject(ID);
	Bool bImported = DEX_ModObjGeometrieEx (hPr, GCS);
#else
	Bool bImported = DEX_ModObjGeometrie (OG);
#endif

//	if (!bImported && OG.lONr <= 0)	// KK991008
	if (!bImported)
	{                       
		OptParams.NotImported++;
// KK991008
		if (OG.lONr != -1 ) {
			ErrInstall EI (EC_INVADDR);

			DEX_DeleteObject(OG.lONr);

		}

// KK991011
//		if (OptParams.bDebugOutput)
		{
			ResString Error (ResID (IDS_NOAREAIMPORT, &g_pTE -> RF ()), 50);
			OutputDebugString (Error.Addr ());  
// KK991011			
			yyerror ( IDS_NOAREAIMPORT);
		}
		return -1;
	}               

	if (OutputUniqueIdent (OG.lONr,ID) == EC_OKAY) 
	{                                   
		IncCounter (OG.lONr);   // Status aktualisieren 
		if (bImported)
			OptParams.AreaCnt++;
		else
			OptParams.BugImported++;						
		return OG.lONr;
	} 
	else
		return -1;
}
