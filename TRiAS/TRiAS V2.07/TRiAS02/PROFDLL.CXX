// Memberfunktionen f¸r Projekt- ProfileDatei ---------------------------------
// File: PROFILE.CXX

#include "trias02p.hxx"

#include "profile.hxx"

// Konstruktor ----------------------------------------------------------------
ProFile :: ProFile (const char *Project, const char *pResTarget) 
{
char Drive[_MAX_DRIVE];
char Path[_MAX_DIR];
char Name[_MAX_FNAME];
char Ext[_MAX_EXT];

	_FullName = NULL;
	_pResTarget = NULL;

	if (Project == NULL) return;

// Dateinamen der ProfileDatei neu generieren
	_splitpath (Project, Drive, Path, Name, Ext);
	_FullName = new char [_MAX_PATH];
	if (_FullName == NULL) {
		db_error (EC_NOMEMORY, RC_ctProFile);
		return;
	}

// vollen ProFileNamen zusammenbauen
	_makepath (_FullName, Drive, Path, Name, ResString (IDS_EXTPROFILE, 5));

// etvl. ResourceFile merken
	_pResTarget = pResTarget;
}

// Destruktor
ProFile :: ~ProFile (void) 
{
	DELETE (_FullName);
}

#if 0
// Einlesen der zu einem Objekt gehˆrenden DBase MerkmalsCodes ----------------
int ProFile :: ReadDBaseCodes (long **MKs, char ***MStrs, char *Id) 
{
	*MKs = NULL;
	*MStrs = NULL;

	if (_FullName == NULL) return 0;

ResourceFile *pRF = _pResTarget != NULL ?	// ResourceFile generieren
		    new ResourceFile (_pResTarget) : NULL;	

	if (_pResTarget != NULL && pRF == NULL) {
		db_error (EC_NOMEMORY, RC_ReadDBaseCodes);
		return 0;
	}

ResString DBaseInfo (ResID (IDS_DBASEINFO, pRF), 13);
char IdKey[12];
char *PString = "";
Bool PStringAllocated = FALSE;
short Cnt = 0;		// Anzahl der MerkmalsCodes

// f¸r bestimmten Id liefern
	if (Id != NULL) {
		strcpy (IdKey, ResString (ResID (IDS_PROFID, pRF), 3));
		strncat (IdKey, Id, 8);

	// Anzahl der MerkmalsCodes lesen
		Cnt = GetPrivateProfileInt (DBaseInfo, IdKey, 0, _FullName);
		if (Cnt > 0) {
		// Feld f¸r ProfileString anfordern
			PString = new char [(Cnt+1)*80+1];
			if (PString == NULL) {          // kein Speicher mehr
				DELETE (pRF);
				db_error (EC_NOMEMORY, RC_ReadDBaseCodes);
				*MKs = NULL;
				*MStrs = NULL;
				return 0;
			}
			PStringAllocated = TRUE;

		// MerkmalsCodes selbst lesen
			GetPrivateProfileString (DBaseInfo, IdKey, "", PString, (Cnt+1)*80, _FullName);
		}
	} 

// wenn nichts da, dann Standard liefern
	if (!strcmp (PString, "")) {
	ResString Standard (ResID (IDS_STANDARD, pRF), 20);

	// Anzahl der MerkmalsCodes lesen
		Cnt = GetPrivateProfileInt (DBaseInfo, Standard, 0, _FullName);
		if (Cnt > 0) {
		// Feld f¸r ProfileString anfordern
			PString = new char [(Cnt+1)*80+1];
			if (PString == NULL) {          // kein Speicher mehr
				DELETE (pRF);
				db_error (EC_NOMEMORY, RC_ReadDBaseCodes);
				*MKs = NULL;
				*MStrs = NULL;
				return 0;
			}
			PStringAllocated = TRUE;

		// MerkmalsCodes selbst lesen
			GetPrivateProfileString (DBaseInfo, Standard, "", PString, (Cnt+1)*80, _FullName);
		}
	}

// wenn nicht gegeben ist, wieder raus
	if (Cnt == 0) {	
		if (PStringAllocated) 
			DELETE(PString);
		DELETE (pRF);
		*MKs = NULL; 
		*MStrs = NULL;
		return 0; 
	}

// MKFeld anfordern
	*MKs = new long [Cnt];
	*MStrs = new char * [Cnt];
	if (*MKs == NULL || *MStrs == NULL) {
		if (PStringAllocated)
			DELETE (PString);
		DELETE (pRF);
		db_error (EC_NOMEMORY, RC_ReadDBaseCodes);
		if (*MKs != NULL) DELETE (*MKs);
		*MKs = NULL;
		*MStrs = NULL;
		return 0;
	}

// MerkmalsCodes konvertieren
register char *cptr = strchr (PString, ',');          // 1. Komma suchen
int i = 0;

	while (i < Cnt) {
		if (cptr == NULL) {
			(*MKs)[i] = -1L;	// Default
			(*MStrs)[i] = NULL;
			break;	// abbrechen
		}
	// entweder MerkmalsCode, Tag oder direkt Merkmalswert
	char Quote = *(cptr+1);
		if (Quote == '\"' || Quote == '\'' || Quote == '\`' || Quote == '<') {
		// bereits Wert/Tag gegeben
			if (Quote == '\`') {
				Quote = '\'';
				(*MKs)[i] = -2L;	// DBaseExpr gegeben
			} else if (Quote == '<') {
				Quote = '>';
				(*MKs)[i] = -3L;	// Tag gegeben
			} else
				(*MKs)[i] = -1L;	// MerkmalsWert gegeben
			(*MStrs)[i] = new char [strlen (cptr+2)+1];
			if ((*MStrs)[i] == NULL) {
				db_error (EC_NOMEMORY, RC_ReadDBaseCodes);
				break;
			}
			strcpy ((*MStrs)[i], cptr+2);	// Merkmalswert
		// QuoteChar am Ende rausnehmen
		char *tmpPtr;

			if ((tmpPtr = strchr ((*MStrs)[i], Quote)) != NULL)
				*tmpPtr = '\0';
#if defined(MSWIND)	
		// Zeichensatz konvertieren
			OemToAnsi ((*MStrs)[i], (*MStrs)[i]);
#endif
		} else {
		// nur MerkmalsCode gegeben
			(*MKs)[i] = atol (cptr+1);	// MK konvertieren
			(*MStrs)[i] = NULL;		// kein Merkmalswert
		}
		cptr = strchr (cptr+1, ',');	// nÑchsten MK suchen
		i++;
	}
// Speicher wieder freigeben
	if (PStringAllocated) DELETE (PString);
	DELETE (pRF);

return i;	// real gelesene Werte
}

// Einlesen der zu einem Objekt gehîrenden DBase MerkmalsCodes ----------------
int ProFile :: ReadDBaseRelations (DBaseRel &Master, DBaseRel ***pppDR, char *Id) 
{
	*pppDR = NULL;
	if (_FullName == NULL) return 0;

ResourceFile *pRF = _pResTarget != NULL ?	// ResourceFile generieren
		    new ResourceFile (_pResTarget) : NULL;

	if (_pResTarget != NULL && pRF == NULL) {
		db_error (EC_NOMEMORY, RC_ReadDBaseRelations);
		return 0;
	}

char IdKey[40];
char *PString = "";
Bool PStringAllocated = FALSE;
short Cnt = 0;		// Anzahl der Relationen

// Namen der Sektion generieren
	strcpy (IdKey, ResString (ResID (IDS_DBASERELINFO, pRF), 20));

// fÅr bestimmten Id liefern
	if (Id != NULL) {
		strcat (IdKey, ResString (ResID (IDS_PROFID, pRF), 3));
		strcat (IdKey, Id);
	}

// Anzahl der Relationen lesen
char MasterEntry[25];

	strcpy (MasterEntry, Master.GetDBName());
	strcat (MasterEntry, ":");
	strcat (MasterEntry, Master.GetFieldName());
	Cnt = GetPrivateProfileInt (IdKey, MasterEntry, 0, _FullName);
	if (Cnt > 0) {
	// Feld fÅr ProfileString anfordern
		PString = new char [(Cnt+1)*80+1];
		if (PString == NULL) {          // kein Speicher mehr
			DELETE (pRF);
			db_error (EC_NOMEMORY, RC_ReadDBaseRelations);
			*pppDR = NULL;
			return 0;
		}
		PStringAllocated = TRUE;

	// MerkmalsCodes selbst lesen
		GetPrivateProfileString (IdKey, MasterEntry, "", 
					 PString, (Cnt+1)*80, _FullName);
	}

// wenn nicht gegeben ist, wieder raus
	if (Cnt == 0) {	
		if (PStringAllocated) DELETE (PString);
		DELETE (pRF);
		*pppDR = NULL;
		return 0; 
	}

// RelationsFeld anfordern
	*pppDR = new DBaseRel* [Cnt];
	if (*pppDR == NULL) {
		if (PStringAllocated) DELETE (PString);
		DELETE (pRF);
		db_error (EC_NOMEMORY, RC_ReadDBaseRelations);
		return 0;
	}

// Relationen konvertieren
register char *cptr = strchr (PString, ',');          // 1. Komma suchen
int i = 0;

	while (i < Cnt) {
		if (cptr == NULL) {
			(*pppDR)[i] = NULL;	// Default
			break;	// abbrechen
		}

	char *pDBName = cptr+1;
	char *pField = strchr (pDBName, ':') +1;

		if (pField) 
			*(pField-1) = '\0';
	// nÑchster Eintrag
		cptr = strchr (pField, ',');
		if (cptr) 
			*cptr = '\0';
		(*pppDR)[i] = new DBaseRel (pDBName, pField);
		if ((*pppDR)[i] == NULL) {
			db_error (EC_NOMEMORY, RC_ReadDBaseRelations);
			break;
		}

#if defined(MSWIND)	
		// Zeichensatz konvertieren
		(*pppDR)[i] -> OemToAnsi();
#endif
		i++;
	}

// Speicher wieder freigeben
	if (PStringAllocated) DELETE (PString);
	DELETE (pRF);

return i;	// real gelesene Werte
}

// Einlesen des Namens des als DQL-Editor zu verwendenden Programmes ----------
char *ProFile :: EDName (char *pEDName, short maxLen) 
{
	if (_FullName == NULL) return NULL;

ResourceFile *pRF = _pResTarget != NULL ?	// ResourceFile generieren
		    new ResourceFile (_pResTarget) : NULL;	

	if (_pResTarget != NULL && pRF == NULL) {
		db_error (EC_NOMEMORY, RC_EDName);
		return NULL;
	}

ResString EDEntry (ResID (IDS_DIRISEDENTRY, pRF), 15);
ResString EDKey (ResID (IDS_DIRISEDKEY, pRF), 15);
ResString DefED (ResID (IDS_DIRISED, pRF), 8);
ResString Profile (ResID (IDS_PROFILE, pRF), 13);

	GetPrivateProfileString (EDEntry, EDKey, DefED, 
				 pEDName, maxLen, Profile);

return pEDName;
}
#endif

int ProFile :: SetPreLoad (char *pExtName, int iFlag) 
{
	if (_FullName == NULL) return 0;

Bool oldFlag = 0;
ResString ExtSection (IDS_EXTENSION, 20);
char Value[80];

	GetPrivateProfileString (ExtSection, pExtName, "",
				 Value, sizeof(Value), _FullName);
// neues Flag setzen
char *pFlag = strchr (Value, ',');

	if (pFlag) {
		oldFlag = atoi (++pFlag);
		_itoa (iFlag, pFlag, 10);
		WritePrivateProfileString (ExtSection, pExtName, 
					   Value, _FullName);
	}

return oldFlag;	// altes Flag liefern
}


int ProFile :: GetPreLoad (char *pExtName) 
{
	if (_FullName == NULL) return 0;

ResString ExtSection (IDS_EXTENSION, 20);
char Value[80];

	GetPrivateProfileString (ExtSection, pExtName, "",
				 Value, sizeof(Value), _FullName);
// neues Flag setzen
char *pFlag = strchr (Value, ',');

	if (pFlag) return atoi (++pFlag);

return 0;
}
