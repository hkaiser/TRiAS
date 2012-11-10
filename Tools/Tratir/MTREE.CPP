// Einlesen einer Datei, die Merkmale definiert
// File: MTREE.CXX

#include "tratasp.h"

#include <containr.hxx>

#include "mtree.hxx"

//extern "C" char _pascal *DtoA (char *, char *, double);

static MTree *pMTree = NULL;
static CTable *pMTable = NULL;

static char InLine[1024];

// Eröffnen und einlesen der Info-Datei, die Merkmale für Objekte beschreibt
void MIOpen (char *pFileName) {
FILE *fpIn = NULL;

// Datei eröffnen
	if ((fpIn = fopen (pFileName, "r")) == NULL) {
		fprintf (stderr, "Kann Datei %s nicht eröffnen.\n", pFileName);
		return;
	}

// Baum bei Bedarf anlegen
	if (pMTree == NULL) {
		pMTree = new MTree;
		if (pMTree == NULL) {
			fprintf (stderr, "Kein Speicherplatz.\n");
			fclose (fpIn);
			return;
		}
		pMTable = new CTable (*pMTree);
		if (pMTable == NULL) {
			fprintf (stderr, "Kein Speicherplatz.\n");
			fclose (fpIn);
			delete pMTree;
			pMTree = NULL;
			return;
		}
	}

// Baum aufbauen, gesamte Datei verarbeiten
// erwartetes DateiFormat:
//
//	Unique Ident,MerkmalsCode,MerkmalsText
//	etc.

	while (fgets (InLine, sizeof(InLine), fpIn) != NULL) {
	MInfoCreator MICr (*pMTree);
	long MCode;
	char *pUIdent, *pMText;
	char *cptr;
	short MTyp;
	
//		if ((cptr = strchr (InLine, '\n')) != NULL) *cptr = '\0';

		pUIdent = strtok (InLine, ";, \t");
		cptr = strtok (NULL, ";, \t");
		MCode = atol (cptr);			// MerkmalsCode
		MTyp = *strtok (NULL, ";, \t");		// MerkmalsTyp
		pMText = strtok (NULL, "\n");		// MerkmalsWert

		ContCreate (MICr, MInfo) (pUIdent, MCode, pMText, MTyp);
	}

// Datei wieder schlieáen
	fclose (fpIn);
}

// Zugriffroutinen auf die Elemente des Baumes --------------------------------
static char ActUIdent[50];
static hasActUIdent = FALSE;

short ExtractMI (char *pUIdent, long *pMCode, short *pMTyp, char *pMText, short maxLen) 
{
	if (pMTree == NULL || pMTable == NULL)
		return FALSE;

	pMTable -> Find (pUIdent);	// auf ersten SchlüsselWert positionieren
	if (pMTable -> Valid()) {
	MInfoLock l(*pMTable);

		if (!l) return FALSE;

	// aktuellen UIDent merken
		strncpy (ActUIdent, pUIdent, sizeof(ActUIdent)-1);
		ActUIdent[sizeof (ActUIdent)-1] = '\0';
		hasActUIdent = TRUE;

	// Merkmal extrahieren
		*pMCode = l -> GetMCode();		// MerkmalsCode
		*pMTyp = l -> GetMTyp();
		strncpy (pMText, l -> GetMText(), maxLen-1);	// MWert
		pMText[maxLen-1] = '\0';
		return TRUE;
	}

return FALSE;
}

short NextMI (long *pMCode, short *pMTyp, char *pMText, short maxLen) 
{
	if (pMTree == NULL || pMTable == NULL)
		return FALSE;

	if (!pMTable -> Valid()) 
		return FALSE;

	if (hasActUIdent && pMTable -> FindNext (ActUIdent)) {
	MInfoLock l(*pMTable);

		if (l) {
		// Merkmal extrahieren
			*pMCode = l -> GetMCode();		// MerkmalsCode
			*pMTyp = l -> GetMTyp();
			strncpy (pMText, l -> GetMText(), maxLen-1); // MWert
			pMText[maxLen-1] = '\0';
			return TRUE;
		}
	}
	hasActUIdent = FALSE;

return FALSE;
}

// Baum wieder freigeben ------------------------------------------------------
void ReleaseMTree (void) 
{
	if (pMTree != NULL) {
		delete pMTree;
		pMTree = NULL;
	}
	if (pMTable != NULL) {
		delete pMTable;
		pMTable = NULL;
	}
}

// Member für Klasse MInfo ----------------------------------------------------
MInfo :: MInfo (char *pUIdent, long MCode, char *pMText, short MTyp) 
{
	_MCode = MCode;
	_pUIdent = _pMText = NULL;

	if (MTyp != 'A' && MTyp != 'I' && MTyp != 'F')
		return;
	_MTyp = MTyp;

	if (pUIdent != NULL) {
		_pUIdent = new char [strlen (pUIdent) +1];
		if (_pUIdent == NULL) {
			fprintf (stderr, "Kein Speicherplatz.\n");
			return;
		}
		strcpy (_pUIdent, pUIdent);
	} else {
		_pUIdent = new char [1];
		if (_pUIdent == NULL) {
			fprintf (stderr, "Kein Speicherplatz.\n");
			return;
		}
		*_pUIdent = '\0';
	}

	if (pMText != NULL) {
		_pMText = new char [strlen (pMText) +1];
		if (_pMText == NULL) {
			fprintf (stderr, "Kein Speicherplatz.\n");
			return;
		}
		strcpy (_pMText, pMText);
	} else {
		_pMText = new char [1];
		if (_pMText == NULL) {
			fprintf (stderr, "Kein Speicherplatz.\n");
			return;
		}
		*_pMText = '\0';
	}
}

MInfo :: ~MInfo (void) 
{
	if (_pUIdent != NULL) { delete _pUIdent; _pUIdent = NULL; }
	if (_pMText != NULL) { delete _pMText; _pMText = NULL; }
}


// Memberfunktionen für MTree -------------------------------------------------
MTree :: MTree (void) 
       : CTree (GetUIdent, (pKeyCmpFcn)StrCmp)
{
	// nothing else to do
}

MTree :: ~MTree (void) 
{
	EveryDelete ();	// alle Elemente des Baumes freigeben
}

void MTree :: UserDelete (void *pObj) 
{
	((MInfo *)pObj) -> ~MInfo();
}

void *GetUIdent (void *pObj) 
{
	return ((MInfo *)pObj) -> UIdent ();
}
