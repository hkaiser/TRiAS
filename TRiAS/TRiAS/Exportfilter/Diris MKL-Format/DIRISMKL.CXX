// Routinen zum Schreiben der DIRIS-Merkmalsinformationen ---------------------
// File: DIRISMKL.CXX

#include "merkmp.hxx"

#include <fcntl.h>
#include <io.h>
#include <stdlib.h>
#include <ctype.h>

#include <zprotos.h>

#include "dirismkl.hxx"

// lokale FunktionsPrototypen
static ErrCode DirisMKLExportGeometrie (int fh, GSTRUCT &GS);
static ErrCode DirisMKLExportLine (int fh, const char *lpStr = NULL);

extern "C" {	// alle exportierten Funktionen sollen _pascal sein 

// Begin des DatenExports -----------------------------------------------------
ErrCode EXPORTFLT PASCAL DirisMKLExportBegin (char *lpFileName, OFSTRUCT &of, 
					     OutMode OutFlag, HWND) 
{
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
ErrCode EXPORTFLT PASCAL DirisMKLExportComment (OFSTRUCT &, const char *) 
{
	return EC_OKAY;
}

// Ausgeben der HeaderInformation ---------------------------------------------
ErrCode EXPORTFLT PASCAL DirisMKLExportHeader (OFSTRUCT &, const char *) 
{
	return EC_OKAY;
}

// Ausgeben der BeschreibungsInformation --------------------------------------
ErrCode EXPORTFLT PASCAL DirisMKLExportDescription (OFSTRUCT &, const char *, 
						   const char *) 
{
	return EC_OKAY;
}


// Ausgeben der TrailerInformation --------------------------------------------
ErrCode EXPORTFLT PASCAL DirisMKLExportTrailer (OFSTRUCT &, const char *) 
{
	return EC_OKAY;
}

static char outBuff[1024];

// Ausgabe eines Geometrieobjektes mit Merkmalsinformation --------------------
ErrCode EXPORTFLT PASCAL DirisMKLExportData (OFSTRUCT &of, GSTRUCT &GS, MFELD *MF,
					    RSTRUCT *, char *pUIdent) 
{
register int fh;        // DateiHandle

// Datei eröffnen
	if ((fh = OpenFile (NULL, &of, OF_REOPEN+OF_WRITE)) < 0)
	// Fehler: kann Datei nicht eröffnen
		return EC_NOFILE;
	_llseek (fh, 0L, SEEK_END);
	setmode (fh, O_TEXT);

// wenn kein Unique Ident gegeben ist, dann ObjektNummer verschlüsseln
char pUniqueId[40];

	if (pUIdent == NULL) {
		_splitpath (of.szPathName, NULL, NULL, pUniqueId, NULL);
		strupr (pUniqueId);
		wsprintf (pUniqueId, "%s_%ld", pUniqueId, GS.ON);
	} else
		strcpy (pUniqueId, pUIdent);

// Merkmalszeile generieren und ausgeben
register ErrCode RC;
char outBuff[81];

// erstes Merkmal weglassen, da dieses bereits im BNA-File ausgegeben wurde
	if (MF -> MCode != 0) MF++;
	
	while (MF -> MCode != 0) {
	// für alle Merkmale MerkmalsSatz ausgeben
	char *pMText = MF -> MText;

		if (pMText == NULL || 
		    MF -> MCode == -1L || 
		    !strcmp (pMText, pUniqueId)) 
		{
			MF++;		// nächstes Merkmal
			continue;	// Merkmal auslassen
		}
		wsprintf (outBuff, "%s,%08ld,%c,%s", 
					pUniqueId, MF -> MCode, 
					toupper(MF -> MTyp), MF -> MText
			 );
		DBASSERT (DirisMKLExportLine (fh, outBuff));

		MF++;           // nächstes Merkmal
	}

return (ErrCode)_lclose (fh);
}


// Ende des DatenExports ------------------------------------------------------
ErrCode EXPORTFLT PASCAL DirisMKLExportEnd (OFSTRUCT &) 
{ 
	return EC_OKAY;
}

// Abbrechen des Datenexportes ------------------------------------------------
ErrCode EXPORTFLT PASCAL DirisMKLExportBreak (OFSTRUCT &of) 
{ 
// Datei löschen, damit keine Reste bleiben
	OpenFile (of.szPathName, &of, OF_DELETE);

return EC_OKAY; 
} 

}	// extern "C"

static ErrCode DirisMKLExportLine (int fh, const char *Line) 
{
// Ausgabe der Zeile
	if (Line != NULL) {
	UINT Len = strlen (Line);

		if (_lwrite (fh, (char *)Line, Len) != Len)
			return EC_NOSPACE;
	} 
// NewLine ausgeben
char *cptr = "\r\n";		// CR,LF

	if (_lwrite (fh, cptr, 2) != 2)
		return EC_NOSPACE;            

return EC_OKAY;
}

