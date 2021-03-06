/*
File: TOOLS.CXX
Das Modul beinhaltet allgemeine Funktionen zur Kommunikation mit TRIAS

Erarbeitet: J. Benkenstein                                     Stand vom 11. Mai 1995
*/

#include "pheader.h"

#include <hpp/filebuff.hxx>         // CFileBuffer

#include "numedit.hxx"				// NumEdit
#include "realedit.hxx"				// RealEdit
#include "helptext.hxx"				// CHelpText
#include "optparam.hxx"				// Params, OptParams

#include "arcimpif.hxx"
#include "arcimp.hxx"

#include <assert.h>					// assert ()
#include <new>						// bad_alloc ()

extern "C" {
    #include "arctrias.hr"           // Resource-Konstanten
	#include <xtensnn.h>
}

#include <errinstx.hxx>             // ErrInstall

#define NOOPTPARAM
#include "optparam.hxx"             // Params
#include "tools.hxx"                // zugeh. Header

#if _MSC_VER >= 1100
using std::bad_alloc;
#endif // _MSC_VER >= 1100

//  Konstanten
const short KurzTextLen = 32;   	// max. L�nge eines KurzTextes
const short LangTextLen = 80;   	// max. L�nge eines LangTextes
const char UnIDSep [] = "_";    	// Separator f�r Unique Ident
const char MinVerticeCnt = 4;		// Fl�che mu� wenigstens 4 St�tzpunkte haben

//  externe Variablen
extern Params *pParams;                 // Speicher f�r allg. Parameter
extern ResourceFile *pRF;               

// Prototypen
void IncCounter (long ObjNr = 0);       // Status aktualisieren         

//  Unique Ident f�r ein bestimmtes Objekt ausgeben
ErrCode OutputUniqueIdent (long ObjNr) {
	if (pParams -> CrUnID == False)                        // nicht erzeugen
		return EC_OKAY;
	char Buffer [MaxFileSize + 15] = "";
	lstrcpy (Buffer, pParams -> pCoverName);                // kurzen Dateinamen
	lstrcat (Buffer, UnIDSep);                                              // "_"
	ltoa (ObjNr, &Buffer [lstrlen (Buffer)], 10);   // Nummer anh�ngen
	return OutputMerkmal (ObjNr, pParams -> UnID, Buffer); // Merkmal ausgeben
}

//  Merkmal f�r ein bestimmtes Objekt ausgeben
ErrCode OutputMerkmal (long lObjNummer, ulong MerkmalsKode, pchar pMerkmalsText) 
{
//	pr�fe Parameter
	assert (lObjNummer != 0);
	assert (pMerkmalsText);

	if ((0 == lObjNummer)  || !pMerkmalsText)
		return EC_SYSERROR;
	
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
		if (pParams -> bAnsiiText)
			OemToAnsi (pText, pText);
		TM.iFlags = TMNoCaching;

		ec = DEX_ModTextMerkmal (TM);
	}
	catch (bad_alloc)
	{
		ec = EC_NOMEMORY;
	}

	DELETE_VEC (pText);
	return ec;
}

//  neuen Identifkator in der PBD erzeugen
//  (falls noch nicht vorhanden)
ErrCode CreateIdent (ulong ID, pchar pText, pWindow pParent) {
//  Fehlermeldung von TRIAS ausschalten
	ErrInstall E1 (WC_NOIDENT);
	ErrCode EC;

	PBDDATA Data;
	memset (&Data, '\0', sizeof (PBDDATA));         // init.
	Data.dwSize = sizeof (PBDDATA);
	Data.pbdTyp = 'i';                              // Typ
	Data.pbdCode = ID;
	Data.pbdTemp = False;                    		// ID soll fest sein

#if _TRiAS_VER < 0x0300
	EC = DEX_GetPBDData (Data);
	if ( EC == EC_OKAY )           // wenn bereits vorh.
#else
	HPROJECT hPr = DEX_GetDataSourceHandle();
	EC = DEX_GetPBDDataEx (hPr,Data);           // wenn bereits vorh.
	if ( EC == EC_OKAY )           // wenn bereits vorh.
#endif
		return EC_OKAY;                             // dann zur�ck

//  Text ggf. trimmen
	short Len = 0;
	while (((Len = lstrlen (pText)) > 0) && (*(pText + Len - 1) == ' '))
		*(pText + Len - 1) = '\0';

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


#if _TRiAS_VER < 0x0300
	EC = DEX_ModPBDData (Data);
#else
	EC = DEX_ModPBDDataEx (hPr,Data);
#endif

	if (EC == EC_OKAY)
		DEXN_PBDIdentChanged (ID);
	else           
	{               
	//	Fehlermeldung ggf. erzeugen
		if (pParent && pRF)
		{
			ResString Caption (ResID (IDS_PARAMERROR, pRF), 20);
    		ResString TextFormat (ResID (IDS_PARERR, pRF), 40);
    		char Buffer [60] = "";
			char tBuffer [30] = "";

	#if _TRiAS_VER < 0x0300
			ClassFromIdentX (ID, tBuffer, sizeof(tBuffer));
	#else
			ClassFromIdentX (hPr, ID, tBuffer, sizeof(tBuffer));
	#endif
			wsprintf (Buffer, TextFormat.Addr (), tBuffer);
    		MessBox MB (Caption.Addr (), Buffer, pParent);
    		MB.SetType (OkayButton | HandIcon);
    		MB.Show ();		
		}    		
	}		
	return EC;
}

//  neues Merkmal in der PBD erzeugen
//  (falls noch nicht vorhanden)
//ErrCode CreateMerkmal (ulong MK, pchar pText, short MaxLen) {
ErrCode CreateMerkmal (ulong MK, pchar pText, short MaxLen, ulong ID) 
{
//  Fehlermeldung von TRIAS ausschalten
	ErrInstall E1 (WC_NOMERKMAL);

// KK990927
#if _TRiAS_VER < 0x0300
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

#if _TRiAS_VER < 0x0300
	ErrCode EC = DEX_GetPBDData (Data);
#else
	Data.lIdent = ID;
	HPROJECT hPr = DEX_GetDataSourceHandle();
	ErrCode EC = DEX_GetPBDDataEx (hPr,Data);
#endif

	if ( EC == EC_OKAY && MaxLen <= Data.ipbdMLen)   // wenn bereits vorh.
		return EC_OKAY;                             // dann zur�ck

	if (EC != EC_OKAY) {            // wenn noch nicht vorh.
	//  Text ggf. trimmen
		short Len = 0;
		while (((Len = lstrlen (pText)) > 0) && (*(pText + Len - 1) == ' '))
			*(pText + Len - 1) = '\0';

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
	}

//  diese L�nge ggf. vergr��ern
	Data.ipbdMLen = MaxLen;                              	// max. L�nge des Merkmals

#if _TRiAS_VER < 0x0300
	EC = DEX_ModPBDData (Data);
#else
	EC = DEX_ModPBDDataEx (hPr,Data);
#endif

	if (EC == EC_OKAY)
		DEXN_PBDMCodeChanged (MK);
	return EC;
}

//  TextObject -------------------------------------------------------------
TextObject :: TextObject (void) {
	_pText = NULL;
	_X = _Y = 0.0;
}

TextObject :: ~ TextObject (void) {
        DELETE_VEC (_pText);
}

Bool TextObject :: AddText (pchar pText) {
//  pr�fe Parameter
	if (! pText || ! *pText)
		return True;

	short sLen = (lstrlen (pText) * 2) + 1;
	_pText = new char [sLen];
	if (!_pText) {
		DEX_Error (RC_TextObjectAddText, EC_NOMEMORY);
		return False;
	}

//	ggf. "\" durch "\n" ersetzen
	if (NULL == strchr (pText, '\\'))
		lstrcpy (_pText, pText);
	else
	{
		memset (_pText, 0, sLen);		// Text init.
		short i = 0;
		for (char *pR = pText; pR && *pR; pR++, i++)
		{
			_pText [i] = *pR;
			if ('\\' == *pR)
				_pText [++i] = 'n';
		}
	}

	return True;
}

//  Textwert und unique Ident als Merkmal ausgeben
Bool TextObject :: Output (void) {
//  pr�fe Parameter
	if (! _pText || ! *_pText)
		return True;

	TEXTGEOMETRIE TG;
	memset (&TG, 0, sizeof (TEXTGEOMETRIE));        // init.
	TG.dwSize = sizeof (TEXTGEOMETRIE);
	TG.lONr = -1;                                   // noch keine vorhanden
	TG.lIdent = pParams -> ID;
	TG.iObjTyp = OGText;
	TG.iFlags = (short)(OGConverted |               // double Koordinaten
				OGNewObject |           // neues Object erzeugen 
				OGForceGeometry |		// Geometrie nicht pr�fen
				//OGForceGeoError |
				OGNoMemoryObject);       // nicht im Speicher halten

//  textspezifische Attribute init.
	TG.lCnt = 1;                                            // Anz. St�tzpkte.
	TG.iKCnt = lstrlen (_pText);            				// max. Textl�nge
	
//	Skalierung und Offset ber.	
	_X = (_X + pParams -> XOffset) * pParams -> Scaling;    // Koordinaten   
	_Y = (_Y + pParams -> YOffset) * pParams -> Scaling;
	TG.pdblX = &_X;                                         
	TG.pdblY = &_Y;
	TG.pText = _pText;

	if (pParams -> bAnsiiText)
		OemToAnsi (TG.pText, TG.pText);

//  Object an TRIAS ausgeben      
#if _TRiAS_VER >= 0x0300
	GEOMETRIEWITHCS GCS;

	INITSTRUCT(GCS, GEOMETRIEWITHCS);
	GCS.pOG = (OBJGEOMETRIE *)&TG;
	GCS.pICS = ((CImpArcExtension *)g_pTE)->get_CS();

	HPROJECT hPr = DEX_GetDataSourceHandle();
	Bool bImported = DEX_ModObjGeometrieEx (hPr, GCS);
#else
	Bool bImported = DEX_ModObjGeometrie (TG);
#endif

	if (! bImported && TG.lONr <= 0)
	{
		pParams -> NotImported++;
		if (pParams -> DebugOutput && pRF)
		{              
			ResString Error (ResID (IDS_NOTEXTIMPORT, pRF), 90);
			OutputDebugString (Error.Addr ());
		}                       
		return False;
	}               

	if (OutputUniqueIdent (TG.lONr) == EC_OKAY) 
	{   
		IncCounter (TG.lONr);   	// Status aktualisieren         
		if (bImported)
	    	pParams -> TextCnt++;
		else
			pParams -> BugCnt++;  	// mit Geometriefehler importiert	    	
		return True;
	} else
		return False;
}

//  Geometrie eines/r Punktes/Linie ausgeben
//  und von TRIAS gebildete ObjektNummer zur�ckgeben,
//  die im Fehlerfall -1 ist
//  unique Ident Merkmal ausgeben
long OutputPunktLinie (double *pKoordX, double *pKoordY, long ArcObjNr, long Cnt, Bool Typ) {
	OBJGEOMETRIE OG;
	memset (&OG, 0, sizeof (OBJGEOMETRIE));   // Struktur init.
	OG.dwSize = sizeof (OBJGEOMETRIE);
	OG.lONr = -1;
	OG.lIdent = pParams -> ID;
	OG.iObjTyp = Typ ? OGPunkt : OGLinie;
	OG.iFlags = (short) (OGConverted |       // double Koordinaten
				OGForceGeometry |       // Geometrie nicht pr�fen
				//OGForceGeoError |
				OGNewObject |           // neues Object erzeugen
				OGNoMemoryObject);       // nicht im Speicher halten
				
	OG.lCnt = Cnt;                      // Anzahl St�tzpunkte
	OG.pdblX = pKoordX;                 // Koordinaten
	OG.pdblY = pKoordY;

//  Object in TRIAS speichern
#if _TRiAS_VER >= 0x0300
	GEOMETRIEWITHCS GCS;

	INITSTRUCT(GCS, GEOMETRIEWITHCS);
	GCS.pOG = (OBJGEOMETRIE *)&OG;
	GCS.pICS = ((CImpArcExtension *)g_pTE)->get_CS();

	HPROJECT hPr = DEX_GetDataSourceHandle();
	Bool bImported = DEX_ModObjGeometrieEx (hPr, GCS);
#else
	Bool bImported = DEX_ModObjGeometrie (OG);
#endif

	if (!bImported && OG.lONr <= 0)
	{                       
		pParams -> NotImported++;
		if (pParams -> DebugOutput && pRF)
		{
			if (OG.iObjTyp == OGLinie)                   
			{
				char Buffer [128] = "";
				ResString ErrorLinie (ResID (IDS_NOLINEIMPORT, pRF), 90);
				wsprintf (Buffer, ErrorLinie.Addr (), ArcObjNr, Cnt);
				OutputDebugString (Buffer);                             
			}                               
			else
			{   
				char Buffer1 [128] = "";                    
				ResString Error (ResID (IDS_NOPUNKTIMPORT, pRF), 90);
				wsprintf (Buffer1, Error.Addr (), ArcObjNr);				
				OutputDebugString (Buffer1);                   
			}                               
		}
		return -1;
	}               

	if (OutputUniqueIdent (OG.lONr) == EC_OKAY) 
	{
		IncCounter (OG.lONr);   // Status aktualisieren 
	
	//  Z�hler erh�hen
		if (Typ)
		{
			if (bImported)
				pParams -> PointCnt++;                  
			else
				pParams -> BugCnt++;				
		}			
		else
		{       
			if (bImported)
				pParams -> LineCnt++;                   
			else
				pParams -> BugCnt++;				
		}			
		return OG.lONr;                  // Objekt-Nummer zur�ck
	} else
		return -1;
}

//	min. Geometriebereinigung
BOOL CheckGeometrie (double __HUGE *pdX, double __HUGE *pdY, long &lCnt, short &sKCnt, long *plCnt)
{
//	pr�fe �bergebene Parameter
	if (!pdX || !pdY || !plCnt || !*plCnt || (lCnt < MinVerticeCnt) || (sKCnt < 1))
		return FALSE;
	else
		return TRUE;

/*
//	jetzt alle Fl�chen einschlie�lich Inseln pr�fen
	BOOL bOutPoly = TRUE;		// zuerst �u�ere Masche
	short sErrKCnt = 0;			// keine fehlerhaften Konturen
	long lNextCnt = 0;			// Index der noch zu kontr. St�tzpunkte
	for (short sActKCnt = 1; sActKCnt <= sKCnt; sActKCnt++, bOutPoly = FALSE)
	{
		lNextCnt += *plCnt;						// St�tzpunktz�hler setzen

	//	pr�fe Parameter der Fl�che
		if ((*plCnt < MinVerticeCnt) ||			// wenigstens 4 St�tzunkte
			(*pdX != pdX [*plCnt - 1]) ||		// und Anfangspunkt 
			(*pdY != pdY [*plCnt - 1]))			// gleich Endpunkt
		{
		//	wenn Fehler aufgetreten
			if (bOutPoly)						// bei �u�eren Masche
				return FALSE;					// diese Fl�che nicht importieren

		//	Insel entfernen
		//	Koordinatenfeld verschieben
	#ifdef WIN32
			memmove (pdX, pdX+(*plCnt), sizeof (double) * (lCnt - lNextCnt));
			memmove (pdY, pdY+(*plCnt), sizeof (double) * (lCnt - lNextCnt));		
	#else        
			long lMax = lCnt - lNextCnt;
			for (long l = 0; l < lMax; l++)
			{
				pdX [l] = pdX [l+1];
				pdY [l] = pdY [l+1];				
			}
	#endif			

		//	St�tzpunkt-Z�hlerfeld verkleinern
			memmove (plCnt, plCnt+1, sizeof (long) * (sKCnt - sActKCnt));				

			sErrKCnt++;						// eine Kontur weniger
			lCnt -= *plCnt;					// Gesamt-St�tzpunktanzahl verringern
			lNextCnt -= *plCnt;				// auch dieser Index wird kleiner
		}
		else
		{
		//	Fl�che ist OK
			pdX += *plCnt;
			pdY += *plCnt; 
			plCnt++;
		}
	}

//	Anzahl fehlerhafter Konturen ber�cksichtigen
	sKCnt -= sErrKCnt;

	return TRUE;
*/
}

//  Geometrie einer Fl�che ausgeben
//  und von TRIAS gebildete ObjektNummer zur�ckgeben,
//  die im Fehlerfall -1 ist
//  unique Ident Merkmal ausgeben
long OutputFlaeche (double *pKoordX, double *pKoordY, long Cnt,
					short KCnt, long *pCnt, long ArcObjNr) {
//	min. Geometriebereinigung
	if (!CheckGeometrie (pKoordX, pKoordY, Cnt, KCnt, pCnt))
	{
		pParams -> NotImported++;
		if (pParams -> DebugOutput && pRF)
		{
			char Buffer [128] = "";
			ResString Error (ResID (IDS_NOAREAIMPORT, pRF), 90);
			wsprintf (Buffer, Error.Addr (), ArcObjNr, Cnt, KCnt);
			OutputDebugString (Buffer);                             
		}
		return -1;
	}

	OBJGEOMETRIE OG;
	memset (&OG, 0, sizeof (OBJGEOMETRIE));   // Struktur init.
	OG.dwSize = sizeof (OBJGEOMETRIE);
	OG.lONr = -1;
	OG.lIdent = pParams -> ID;
	OG.iObjTyp = OGFlaeche;
	OG.iFlags = (short) (OGConverted |       // double Koordinaten
				OGForceGeometry |       // Geometrie nicht pr�fen 
				//OGForceGeoError |
				OGNoMemoryObject |      // nicht im Speicher halten
				OGNewObject);            // neues Object erzeugen 
				
	OG.lCnt = Cnt;                                  // Anzahl der St�tzpunkte
	OG.pdblX = pKoordX;                             // Koordinaten
	OG.pdblY = pKoordY;
	OG.iKCnt = KCnt;                                // Gr��e des Konturfeldes (Anz. Inseln + 1)
	OG.plCnt = pCnt;                                // Konturfeld


//  Object an TRIAS ausgeben      
#if _TRiAS_VER >= 0x0300
	GEOMETRIEWITHCS GCS;

	INITSTRUCT(GCS, GEOMETRIEWITHCS);
	GCS.pOG = (OBJGEOMETRIE *)&OG;
	GCS.pICS = ((CImpArcExtension *)g_pTE)->get_CS();

	HPROJECT hPr = DEX_GetDataSourceHandle();
	Bool bImported = DEX_ModObjGeometrieEx (hPr, GCS);
#else
	Bool bImported =  DEX_ModObjGeometrie (OG);
#endif


	if (!bImported && OG.lONr <= 0)
	{                       
		pParams -> NotImported++;
		if (pParams -> DebugOutput && pRF)
		{
			char Buffer [128] = "";
			ResString Error (ResID (IDS_NOAREAIMPORT, pRF), 90);
			wsprintf (Buffer, Error.Addr (), ArcObjNr, Cnt, KCnt);
			OutputDebugString (Buffer);                             
		}
		return -1;
	}               

	if (OutputUniqueIdent (OG.lONr) == EC_OKAY) 
	{                                   
		IncCounter (OG.lONr);   // Status aktualisieren 
		if (bImported)
			pParams -> AreaCnt++;
		else
		{
//#ifdef _DEBUG
//			for (long l = 0; l < Cnt; l++)
//				TRACE ("I: %ld, X=%7.2lf, Y=%7.2lf\n", l, (double)(*pKoordX+l), (double)(*pKoordY+l));
//#endif
			pParams -> BugCnt++;						
		}
		return OG.lONr;
	} 
	else
		return -1;
}

