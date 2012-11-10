// Memberfunktionen für Projekt- ProfileDatei ---------------------------------
// File: PROFILE.CXX

#include "triaspre.hxx"

#include "Strings.h"
#include "profile.hxx"

#if !defined(WIN32)

// Funktionen zu Verwaltung der vorhergehenden DB's ---------------------------
Bool ProFile :: SetOldDB (short i, char *DB, char *UN, Bool PWD, Bool RO) 
{
// Wenn keine ProFileDatei definiert ist - Fehler
	if (_FullName == NULL) return FALSE;

char OutBuff[141];
ResString OldDB (IDS_OLDDB, 8);
char EntryId[10];
char Num[18];

// Generieren des Eintrages
	strcpy (EntryId, OldDB);
	strcat (EntryId, itoa (i+1, Num, 10));
	wsprintf (OutBuff, "%s,%s,%d,%d", DB, UN, PWD, RO);

return WritePrivateProfileString (OldDB, EntryId, OutBuff, _FullName);
}

Bool ProFile :: SetOldDBEntry (short i, char *Entry) 
{
// Wenn keine ProFileDatei definiert ist - Fehler
	if (_FullName == NULL) return FALSE;

ResString OldDB (IDS_OLDDB, 8);
char EntryId[10];
char Num[18];

	strcpy (EntryId, OldDB);
	strcat (EntryId, itoa (i+1, Num, 10));
	
return WritePrivateProfileString (OldDB, EntryId, Entry, _FullName);
}

Bool ProFile :: GetOldDBEntry (short i, char *Entry, int len) 
{
// Wenn keine ProFileDatei definiert ist - Fehler
	if (_FullName == NULL) return FALSE;

ResString OldDB (IDS_OLDDB, 8);
char EntryId[10];
char Num[18];

	strcpy (EntryId, OldDB);
	strcat (EntryId, itoa (i+1, Num, 10));
	GetPrivateProfileString (OldDB, EntryId, "", Entry, len, _FullName);

return TRUE;
}

char *ProFile :: GetOldDBName (short i) 
{
// Wenn keine ProFileDatei definiert ist - Fehler
	if (_FullName == NULL) return NULL;

ResString OldDB (IDS_OLDDB, 8);
char EntryId[10];
static char OldDBName[_MAX_PATH];
char Num[18];

// Einlesen des Eintrages
	strcpy (EntryId, OldDB);
	strcat (EntryId, itoa (i+1, Num, 10));
	GetPrivateProfileString (OldDB, EntryId, "", OldDBName, _MAX_PATH, _FullName);

// Extrahieren des DBNamens
register char *cptr = strchr (OldDBName, ',');

	if (cptr) *cptr = '\0';         // erstes Komma ausblenden
	if (*OldDBName == '\0')
		return NULL;            // Eintrag nicht vorhanden
	
return OldDBName;
}

char *ProFile :: GetOldUserName (short i) 
{
// Wenn keine ProFileDatei definiert ist - Fehler
	if (_FullName == NULL) return NULL;

ResString OldDB (IDS_OLDDB, 8);
char EntryId[10];
static char UserName[141];
char Num[18];

// Einlesen des Eintrages
	strcpy (EntryId, OldDB);
	strcat (EntryId, itoa (i+1, Num, 10));
	GetPrivateProfileString (OldDB, EntryId, "", UserName, 140, _FullName);
// Extrahieren des Nutzernamens
register char *cptr = strchr (UserName, ',');         // erstes Komma suchen
register char *cptr1 = strchr (cptr+1, ',');          // zweites - " -
	if (cptr1) *cptr1 = '\0';                       // ausblenden
	
return cptr+1;
}

Bool ProFile :: GetOldPWDMode (short i) 
{
// Wenn keine ProFileDatei definiert ist - Fehler
	if (_FullName == NULL) return FALSE;

ResString OldDB (IDS_OLDDB, 8);
char EntryId[10];
char PWDMode[141];
char Num[18];

// Einlesen des Eintrages
	strcpy (EntryId, OldDB);
	strcat (EntryId, itoa (i+1, Num, 10));
	GetPrivateProfileString (OldDB, EntryId, "", PWDMode, 140, _FullName);
// Extrahieren des PWDModes
register char *cptr = strchr (PWDMode, ',');          // erstes Komma
	cptr = strchr (cptr+1, ',');                  // zweites Komma
register char *cptr1 = strchr (cptr+1, ',');          // drittes Komma
	if (cptr1) *cptr1 = '\0';                       // ausblenden
Bool Mode = atoi (cptr+1);                      // Mode einlesen

return Mode;
}

Bool ProFile :: GetOldROMode (short i) 
{
// Wenn keine ProFileDatei definiert ist - Fehler
	if (_FullName == NULL) return FALSE;

ResString OldDB (IDS_OLDDB, 8);
char EntryId[10];
char ROMode[141];
char Num[18];

// Einlesen des Eintrages
	strcpy (EntryId, OldDB);
	strcat (EntryId, itoa (i+1, Num, 10));
	GetPrivateProfileString (OldDB, EntryId, "", ROMode, 140, _FullName);
// Extrahieren des ROModes
register char *cptr = strrchr (ROMode, ',');          // letztes Komma suchen
Bool Mode = atoi (cptr+1);

return Mode;
}

#endif // !WIN32

// Verwaltung der Ansichten (Sight's) -----------------------------------------
// Standard-Ansicht aus Profile-Datei holen
char *ProFile :: GetStandardSight (void) 
{
// Wenn keine ProFileDatei definiert ist - Fehler
	if (_FullName == NULL) return NULL;

ResString RSight (IDS_SIGHTS, 13);
ResString Standard (IDS_STANDARD, SIGHTMENUITEM+1);
static char inString[SIGHTMENUITEM+3];

// ProfileString einlesen
	GetPrivateProfileString (RSight, Standard, "", inString, 
				 SIGHTMENUITEM+3, _FullName);

// In Windows Zeichensatz konvertieren
	OemToAnsi (inString, inString);
	return inString;
}

// Standard-Ansicht in ProFile-Datei schreiben --------------------------------
void ProFile :: SetStandardSight (char *SightName) 
{
// Wenn keine ProFileDatei definiert ist - Fehler
	if (_FullName == NULL) return;

ResString RSight (IDS_SIGHTS, 13);
ResString Standard (IDS_STANDARD, SIGHTMENUITEM+1);
char OutString[SIGHTMENUITEM+3];

// in normalen Zeichensatz konvertieren
	if (SightName) {
	// wenn neue Ansicht gegeben ist
		strcpy (OutString, "\"");			// in '"' einpacken
		AnsiToOem (SightName, OutString+1);
		strcat (OutString, "\"");

	// ProFileString wegschreiben
		WritePrivateProfileString (RSight, Standard, OutString, _FullName);
	} else
	// Standard löschen
		WritePrivateProfileString (RSight, Standard, NULL, _FullName);
}

// MerkmalsKodes, die Objektnamen enthalten ----------------------------------
long ProFile :: GetObjNameCode (char *pOKS, bool *pfForceMCode) 
{
// Wenn keine ProFileDatei definiert ist - Fehler
	if (_FullName == NULL) return 0L;

ResString ObjName (IDS_OBJNAME, 13);
char IdKey[64];
char PString[64];

// für bestimmten Id liefern
	if (NULL != pfForceMCode) *pfForceMCode = false;
	if (pOKS != NULL) {
		strcpy (IdKey, ResString (IDS_PROFID, 3));
		strcat (IdKey, pOKS);
		if (0 == GetPrivateProfileString (ObjName, IdKey, "", PString, sizeof(PString)-1, _FullName)) {
		// soll dein MCode erzwungen werden
			strcpy (IdKey, g_cbIdForce);
			strcat (IdKey, pOKS);
			if (0 != GetPrivateProfileString (ObjName, IdKey, "", PString, sizeof(PString)-1, _FullName))
			{
				if (NULL != pfForceMCode) *pfForceMCode = true;
			}
		}
	} else
		PString[0] = '\0';

// wenn nichts da, dann Standard bzw. StandardForce liefern
ResString Standard(IDS_STANDARD, 20);

	if (!strcmp (PString, "")) {
	char cbKey[64];

		strcpy (cbKey, Standard);
		strcat (cbKey, g_cbIdForce);
		if (0 == GetPrivateProfileString (ObjName, cbKey, "", PString, sizeof(PString)-1, _FullName))
			GetPrivateProfileString (ObjName, Standard, "", PString, sizeof(PString)-1, _FullName);
		else if (NULL != pfForceMCode)
			*pfForceMCode = true;
	}

// wenn immer noch nichts da, dann 5100000 setzen und liefern
	if (!strcmp (PString, "")) {
		ltoa (51100000L, PString, 10);
		WritePrivateProfileString (ObjName, Standard, PString, _FullName);
	}
	return atol (PString);
}


// Verwalten des letzten verwendeten Identifikators ---------------------------
long ProFile :: GetLastIdent (void)
{
// Wenn keine ProFileDatei definiert ist - Fehler
	if (_FullName == NULL) return 0L;

ResString rsParams (IDS_IRISPARS, 20);
ResString rsLastIdent (IDS_LASTIDENT, 20);
char cbNum[18];

	GetPrivateProfileString (rsParams, rsLastIdent, "", cbNum, sizeof(cbNum), _FullName);
	if (cbNum[0] == '\0')
		return -1L;
		
return atol (cbNum);
}


void ProFile :: SetLastIdent (long lIdent)
{
// Wenn keine ProFileDatei definiert ist - Fehler
	if (_FullName == NULL) return;

ResString rsParams (IDS_IRISPARS, 20);
ResString rsLastIdent (IDS_LASTIDENT, 20);
char cbNum[18];

	ltoa (lIdent, cbNum, 10);
	WritePrivateProfileString (rsParams, rsLastIdent, cbNum, _FullName);
}
 
 
