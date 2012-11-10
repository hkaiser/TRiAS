// Funktionen fuer GeoDB-DateiNamen -------------------------------------------
// File: STRFCNS.CXX

#include "triaspre.hxx"

#include "strfcns.hxx"		// Prototypen

// Verkürzt einen Dateinamen --------------------------------------------------
char *ShortenPath (char *pName, short iMaxLen)
{
char pOut[_MAX_PATH];

char *cptr = strchr (pName + strlen (pName) - iMaxLen + 4, '\\');
char *cptr1 = strchr (pName, '\\');

	if (*cptr1) *cptr1 = '\0';
	if (cptr)
		wsprintf (pOut, "%s\\..%s", pName, cptr);
	else
		strcpy (pOut, pName);
	if (cptr1) *cptr1 = '\\';

char pFormat[80];

	wsprintf (pFormat, "%%-%d.%ds", iMaxLen, iMaxLen);
	wsprintf (pName, pFormat, pOut);

return pName;
}

// Ersetz in einem Template alle '*' gegen eine Wurzel ------------------------
char *ExpandWithName (char *pName, const char *pFullPath, Bool iFullPath)
{
// ParameterTest
	if (pName == NULL) return NULL;

// alles OK, weitermachen
char *pFName = new char [_MAX_FNAME];		// Wurzel
char *pCName = new char [_MAX_PATH];		// volles Template
char *pPath = iFullPath ? new char [_MAX_DIR] : NULL;		// Pfad
char *pDrive = iFullPath ? new char [_MAX_DRIVE] : NULL;	// Drive

	if (pFName == NULL || pCName == NULL) {
		DELETE (pName);
		DELETE (pCName);
		return NULL;
	}

// Template mit vollem Pfad zusammenstellen
	_splitpath (pFullPath, pDrive, pPath, pFName, NULL);
	if (iFullPath && pDrive && pPath) {
		_makepath (pCName, pDrive, pPath, "", "");
		strcat (pCName, pName);
	} else 
		strcpy (pCName, pName);

	DELETE (pDrive);		// werden nicht mehr benötigt
	DELETE (pPath);

	DELETE (pName);			// pName sicher vergrößern
	pName = new char [_MAX_PATH];
	if (pName == NULL) {
		DELETE (pCName);
		DELETE (pFName);
		return NULL;
	}	
	memset (pName, '\0', _MAX_PATH);

// alle Vorkommen von '*' ersetzen
char *cptr = pCName;
char *dest = pName;

	if (pCName) for (cptr = pCName; *cptr; cptr++) {
		if (*cptr == '*') {
			strcat (pName, pFName);
			dest = &pName[strlen (pName)];
		} else
			*dest++ = *cptr;
	} else {
		DELETE (pName);
	}

	*dest = '\0';
	DELETE (pFName);
	DELETE (pCName);

	strlwr (pName);		// alles in Kleinbuchstaben

return pName;			
}
