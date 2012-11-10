// Routinen zum schreiben des DIRIS-Austauschformates
// File: ATLASEXP.CXX

#include "stdafx.h"
#include "AtlasBNAImpl.h"

#include <fcntl.h>
#include <io.h>
#include <stdlib.h>
#include <ctype.h>

#if !defined(HUGE)
#if !defined(WIN32)
#define HUGE __huge
#else
#define HUGE
#endif // WIN32
#endif // HUGE

//XX	#define INLINE inline
extern "C" char *PASCAL DtoAFlt (char *, char *, double);

// lokale FunktionsPrototypen
static ErrCode AtlasBnaExportGeometrie (int fh, GSTRUCT &GS);
static ErrCode AtlasBnaExportLine (int fh, const char *lpStr = NULL);

const int MAX_OKS_LENX = 32;
//XX	INLINE
//XX	HRESULT ClassFromIdentX (ULONG ulIdent, char *pBuffer, int iBuffLen)
//XX	{
//XX	CLASSFROMIDENT CFI;
//XX	
//XX		INITSTRUCT(CFI, CLASSFROMIDENT);
//XX		CFI.ulIdent = ulIdent;
//XX		CFI.pClass = pBuffer;
//XX		CFI.iBuffLen = iBuffLen;
//XX		if (NULL != pBuffer && iBuffLen > 0)
//XX			pBuffer[0] = '\0';
//XX		return DEX_GetClassFromIdent(CFI);
//XX	}


///////////////////////////////////////////////////////////////////////////////
//XX	extern "C" {	// alle exportieten Funktionen sollen _pascal sein 

HWND __hWndM;
UINT __DexCmd;


// KK001023
//ErrCode ExportIdentDescription(OFSTRUCT &of, const char* lpszOKS, const char* lpszShortDescription, const char* lpszLongDescription, const long lVisType, const VISINFO* pVI ) {
ErrCode ExportIdentDescription(OFSTRUCT &of, const char* lpszOKS, const char* lpszShortDescription, const char* lpszLongDescription, const long lVisType, const VISINFO* pVI , long lIdent) {
	return EC_OKAY;
}

ErrCode ExportMerkmalDescription(long lMCode, char *pbuf, short iTyp,short iLen ) {
	return EC_OKAY;
}

// Begin des DatenExports -----------------------------------------------------
//ErrCode EXPORTFLT PASCAL AtlasBnaExportBegin (char *lpFileName, OFSTRUCT &of, OutMode OutFlag, HWND hWnd) 
ErrCode ExportBegin (char *lpFileName, OFSTRUCT &of, OutMode OutFlag, HWND hWnd, const char* lpszDatasource ) 
{
// FensterHandle merken
	USES_CONVERSION;
	CComBSTR	strDEXMessage;
	strDEXMessage.LoadString(IDS_DEXMESSAGE);
	__hWndM = hWnd;
//XX		__DexCmd = RegisterWindowMessage (ResString (IDS_DEXMESSAGE, 30));
	__DexCmd = RegisterWindowMessage(W2A(strDEXMessage));
	
// Datei anlegen
register int fh;        // File Handle
register int OpenMode = OF_WRITE;

	if ((fh = OpenFile (lpFileName, &of, OF_EXIST + OF_WRITE)) >= 0) {
		if (OutFlag == OMOverwrite)
		// Datei existiert bereits und überschreiben
			OpenMode += OF_CREATE;
	} else
		OpenMode += OF_CREATE;
	if ((fh = OpenFile (lpFileName, &of, OpenMode)) < 0)
	// Fehler: kann Datei nicht eröffnen
		return EC_NOFILE;

return (ErrCode)_lclose (fh);
}


// Ausgeben einer Kommentarzeile ----------------------------------------------
//XX	ErrCode EXPORTFLT PASCAL AtlasBnaExportComment (OFSTRUCT &, const char *) 
ErrCode ExportComment (OFSTRUCT &, const char *) 
{
	return EC_OKAY;
}

// Ausgeben der HeaderInformation ---------------------------------------------
//XX	ErrCode EXPORTFLT PASCAL AtlasBnaExportHeader (OFSTRUCT &, const char *) 
ErrCode ExportHeader (OFSTRUCT &, const char *) 
{
	return EC_OKAY;
}

// Ausgeben der BeschreibungsInformation --------------------------------------
//XX	ErrCode EXPORTFLT PASCAL AtlasBnaExportDescription (OFSTRUCT &, const char *, const char *) 
ErrCode ExportDescription (OFSTRUCT &, const char *, const char *) 
{
	return EC_OKAY;
}

ErrCode ExportDescriptionEx(OFSTRUCT &, LPCSTR lpKeyInfo, LPCSTR lpDescString, DWORD dwStyle )
{
	return EC_OKAY;
}

// Ausgeben der TrailerInformation --------------------------------------------
//XX	ErrCode EXPORTFLT PASCAL AtlasBnaExportTrailer (OFSTRUCT &, const char *) 
ErrCode ExportTrailer (OFSTRUCT &of, const char *lpTrailerString)
{
	return EC_OKAY;
}

static char outBuff[1024];

// Ausgabe eines Geometrieobjektes mit Merkmalsinformation --------------------
//XX	ErrCode EXPORTFLT PASCAL AtlasBnaExportData (OFSTRUCT &of, GSTRUCT &GS, MFELD *MF, RSTRUCT *, char *pUIdent) 
ErrCode ExportData (OFSTRUCT &of, GSTRUCT &GS, MFELD *MF, RSTRUCT *, LPCTSTR pUIdent, LPCTSTR lpszGUID, LPCTSTR pParentClass )
{
register int fh;        // DateiHandle
ErrCode EC;

bool fTextInd = (toupper(MF -> MTyp) == 'T') && (MF -> MCode == -1L);

// Datei eröffnen
	if ((fh = OpenFile (NULL, &of, OF_REOPEN+OF_WRITE)) < 0)
	// Fehler: kann Datei nicht eröffnen
		return EC_NOFILE;
	_llseek (fh, 0L, SEEK_END);
	setmode (fh, O_TEXT);

// Identifikatorzeile generieren und ausgeben
char *Merkmal = MF -> MText;

// KK000309
	if (NULL != pUIdent && !strcmp(Merkmal, pUIdent))		// Merkmal = UniqueIdent
		MF++;

	Merkmal = MF -> MText;
	if (MF -> MCode == 0 || Merkmal == NULL) 
		Merkmal = "";		// für alle Fälle

char *cptr = Merkmal;

	while ((cptr = strchr (cptr, '\"')) != NULL) 
		*cptr = '\'';	// alle '\"' durch '\'' ersetzen

char pUniqueId[_MAX_PATH+1];

	if (pUIdent == NULL) {
		_splitpath (of.szPathName, NULL, NULL, pUniqueId, NULL);
		strupr (pUniqueId);
		wsprintf (pUniqueId, "%s_%ld", pUniqueId, GS.ON);
	} 
	else {
		strncpy (pUniqueId, pUIdent, _MAX_PATH);
		pUniqueId[_MAX_PATH] = '\0';
	}

	for (short i = 0; GS.cnt[i] != 0; i++)
		;	// InnenKonturen zählen

long GSize = GS.GSize + (i-1);	// Anzahl der Innenkonturen berücksichtigen
char *pFormat = NULL;
char cbIdBuff[MAX_OKS_LENX];

	ClassFromIdentX (GS.Id, cbIdBuff, MAX_OKS_LENX);

	if (fTextInd) {
// KK00309 _ alt
	// IndirektTextobjekt - nicht mehr
		wsprintf (outBuff, "\"%s\",\"%.950s\",\"[T]%s\",\"%s\",1", cbIdBuff, 
//		wsprintf (outBuff, "\"%s\",\"%ld\",\"%s\",\"%s\",1", cbIdBuff,
//				MF -> MCode,	// MerkmalsCode
				Merkmal,		// MerkmalsText
				pUniqueId,		// Unique Ident
				cbIdBuff);		// OKS als Name4
	} else {
		wsprintf (outBuff, "\"%s\",\"%.950s\",\"%s\",\"%s\",%ld", cbIdBuff, 
				Merkmal,		// MerkmalsText
				pUniqueId,		// Unique Ident
				cbIdBuff,		// OKS als Name4
				GS.Typ == OT_KANTE ? -GSize : GSize
			 );
	}
	if ((EC = AtlasBnaExportLine (fh, outBuff)) < 0) {
		_lclose (fh);
		return EC;
	}

// Geometrieinformation ausgeben
	if ((EC = AtlasBnaExportGeometrie (fh, GS)) < 0) {
		_lclose (fh);
		return EC;
	}

return (ErrCode)_lclose (fh);
}


// Ende des DatenExports ------------------------------------------------------
//XX	ErrCode EXPORTFLT PASCAL AtlasBnaExportEnd (OFSTRUCT &) 
ErrCode ExportEnd (OFSTRUCT &of)
{ 
	return EC_OKAY;
}

// Abbrechen des Datenexportes ------------------------------------------------
//XX	ErrCode EXPORTFLT PASCAL AtlasBnaExportBreak (OFSTRUCT &of) 
ErrCode ExportBreak (OFSTRUCT &of)
{ 
// Datei löschen, damit keine Reste bleiben
	OpenFile (of.szPathName, &of, OF_DELETE);

return EC_OKAY; 
} 

//XX	}	// extern "C"

// Statische Funktionen -------------------------------------------------------
// Geometrieinformation ausgeben
static ErrCode AtlasBnaExportGeometrie (int fh, GSTRUCT &GS) 
{
register ErrCode RC;
char outBuff[81];
long sumIndex = 0;
double xEnd, yEnd;
char tBuff[20];
char *dFormat = "%10.5f";

	for (short iKontur = 0; GS.cnt[iKontur] != 0; iKontur++) {
	// für alle Konturen

		for (long actIndex = 0; 
		     actIndex < GS.cnt[iKontur]; 
		     actIndex++, sumIndex++) {
		// Geometriezeile generieren
			strcpy (outBuff, DtoAFlt (tBuff, dFormat, ((double HUGE *)GS.x)[sumIndex]));
			strcat (outBuff, ",");
			strcat (outBuff, DtoAFlt (tBuff, dFormat, ((double HUGE *)GS.y)[sumIndex]));
		// Geometriezeile ausgeben
			DBASSERT (AtlasBnaExportLine (fh, outBuff));
		}
		if (iKontur == 0) {
		// Endpunkt der Außenkontur merken
			xEnd = ((double HUGE *)GS.x)[actIndex-1];
			yEnd = ((double HUGE *)GS.y)[actIndex-1];
		} else {
		// nochmal Endpunkt der Außenkontur ausgeben
			strcpy (outBuff, DtoAFlt (tBuff, dFormat, xEnd));
			strcat (outBuff, ",");
			strcat (outBuff, DtoAFlt (tBuff, dFormat, yEnd));
			DBASSERT (AtlasBnaExportLine (fh, outBuff));
		}
	}

return EC_OKAY;
}


static ErrCode AtlasBnaExportLine (int fh, const char *pLine) 
{
// Ausgabe der Zeile
	if (pLine != NULL) {
	UINT iLen = strlen (pLine);

		if (_lwrite (fh, (char *)pLine, iLen) != iLen)
			return EC_NOSPACE;
	} 
// NewLine ausgeben
char *cptr = "\r\n";		// CR,LF

	if (_lwrite (fh, cptr, 2) != 2)
		return EC_NOSPACE;            

return EC_OKAY;
}

