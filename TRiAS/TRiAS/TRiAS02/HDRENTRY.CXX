// HeaderEntryBase - Klasse -------------------------------------------------------
// File: HDRENTRY.CXX

#include "trias02p.hxx"

#include <hdrentry.hxx>

extern char pDLLName[];

char *ConvertToIntern (char *pText);
char *ConvertFromIntern (char *pText);

// HeaderEntryBase ----------------------------------------------------------------
HeaderEntryBase::HeaderEntryBase (GeoDB &geoDB, bool fForceNoProject) 
	: _DB (geoDB)
{
	memset (_HeaderKey, '\0', HDRKEYLENGTH+1);
	_HeaderText = NULL;
	_Status = HE_INVALID;
	m_dwFlags = HEADER_NORMAL;
	m_fForceNoProject = fForceNoProject;
}

HeaderEntryBase::HeaderEntryBase (GeoDB &geoDB, const char *Key, bool fForceNoProject) 
	: _DB (geoDB)
{
CActDB ActDB (_DB);

// Schlüsseleintrag kopieren
	if (Key != NULL) {
		memset (_HeaderKey, ' ', HDRKEYLENGTH+1);
		strncpy (_HeaderKey, Key, HDRKEYLENGTH);

	int iLen = min (strlen (Key), (size_t)HDRKEYLENGTH);

		memset (&_HeaderKey[iLen], ' ', HDRKEYLENGTH-iLen);
		_HeaderKey[HDRKEYLENGTH] = '\0';
	}
	_HeaderText = NULL;     // falls abgebrochen werden muß
	m_dwFlags = HEADER_NORMAL;
	m_fForceNoProject = fForceNoProject;

//// HeaderTextlänge bestimmen
//ErrInstall EI (WC_NOTFOUND);
//long len;
//short shortlen;
//
//	EC = (ErrCode)gethdlen (_DB.DBDesc(), (long *)_HeaderKey, &shortlen);
//	if (EC != EC_OKAY) {
//		_Status = HE_INVALID;   // profilaktisch !
//		return; // Fehler aufgetreten
//	}
//
//// Puffer anlegen
//	ATLTRY(_HeaderText = new char [++shortlen]);
//	if (_HeaderText == NULL) {
//	// Kein Speicherplatz mehr
//		_Status = HE_INVALID;   // profilaktisch !
//		db_error (EC_NOMEMORY, RC_ctHeaderEntryBase);
//		return;
//	}
//
//// HeaderText einlesen
//	len = (long)shortlen;
//	EC = (ErrCode)gethd_ (_DB.DBDesc(), _HeaderText, shortlen, &len, (long *)_HeaderKey, (long *)&m_dwFlags);
//	if (EC != EC_OKAY) {            // Fehler aufgetreten
//		_Status = HE_INVALID;   // profilaktisch !
//		return;
//	}
//	_HeaderText[shortlen-1] = '\0'; // NullByte anfügen
// HeaderEintrag holen

// Puffer anlegen
	ATLTRY(_HeaderText = new char [HDRENTRYTEXTLEN+1]);
	if (_HeaderText == NULL) {
	// Kein Speicherplatz mehr
		_Status = HE_INVALID;  	// profilaktisch !
		return;
	}
	*_HeaderText = '\0';

GEODBHDRENTRYEX HE;

	INITSTRUCT (HE, GEODBHDRENTRYEX);
	strncpy (HE.hdrKey, _HeaderKey, HDRKEYLENGTH);
	HE.lphdrText = _HeaderText;
	HE.hdrTextLen = HDRENTRYTEXTLEN;
	
// HeaderText einlesen
	_Status = HE_INVALID;
	if (EC_OKAY == DEX_ReadHeaderEntry(DBDesc(), HE)) {
		_Status = HE_UNMODIFIED;
		m_dwFlags = HE.dwFlags;

	char *pConvert = ConvertToIntern (_HeaderText);

		if (NULL != pConvert) {
			DELETE_VEC(_HeaderText);
			_HeaderText = pConvert;
		}
	}
}


HeaderEntryBase::HeaderEntryBase (GeoDB &geoDB, ResID uiRes, bool fForceNoProject) 
	: _DB (geoDB)
{
ResString rsKey (uiRes, 17);
CActDB ActDB (_DB);

// Schlüsseleintrag kopieren
	memset (_HeaderKey, ' ', HDRKEYLENGTH+1);
	strncpy (_HeaderKey, rsKey.Addr(), HDRKEYLENGTH);

	m_dwFlags = HEADER_NORMAL;
	m_fForceNoProject = fForceNoProject;

int iLen = min (strlen(rsKey.Addr()), (size_t)HDRKEYLENGTH);

	memset (&_HeaderKey[iLen], ' ', HDRKEYLENGTH-iLen);
	_HeaderKey[HDRKEYLENGTH] = '\0';

	_HeaderText = NULL;     // falls abgebrochen werden muß

//// HeaderTextlänge bestimmen
//ErrInstall EI (WC_NOTFOUND);
//long len;
//short shortlen;
//
//	EC = (ErrCode)gethdlen (_DB.DBDesc(), (long *)_HeaderKey, &shortlen);
//	if (EC != EC_OKAY) {
//		_Status = HE_INVALID;   // profilaktisch !
//		return; // Fehler aufgetreten
//	}
//
//// Puffer anlegen
//	ATLTRY(_HeaderText = new char [++shortlen]);
//	if (_HeaderText == NULL) {
//	// Kein Speicherplatz mehr
//		_Status = HE_INVALID;   // profilaktisch !
//		db_error (EC_NOMEMORY, RC_ctHeaderEntryBase);
//		return;
//	}
//
//// HeaderText einlesen
//	len = (long)shortlen;
//	EC = (ErrCode)gethd_ (_DB.DBDesc(), _HeaderText, shortlen, &len, (long *)_HeaderKey, (long *)m_dwFlags);
//	if (EC != EC_OKAY) {            // Fehler aufgetreten
//		_Status = HE_INVALID;   // profilaktisch !
//		return;
//	}
//	_HeaderText[shortlen-1] = '\0'; // NullByte anfügen

// Puffer anlegen
	ATLTRY(_HeaderText = new char [HDRENTRYTEXTLEN+1]);
	if (_HeaderText == NULL) {
	// Kein Speicherplatz mehr
		_Status = HE_INVALID;  	// profilaktisch !
		return;
	}
	*_HeaderText = '\0';

// HeaderEintrag holen
GEODBHDRENTRYEX HE;

	INITSTRUCT (HE, GEODBHDRENTRYEX);
	strncpy (HE.hdrKey, _HeaderKey, HDRKEYLENGTH);
	HE.lphdrText = _HeaderText;
	HE.hdrTextLen = HDRENTRYTEXTLEN;

// HeaderText einlesen
	_Status = HE_INVALID;
	if (EC_OKAY == DEX_ReadHeaderEntry(DBDesc(), HE)) {
		_Status = HE_UNMODIFIED;
		m_dwFlags = HE.dwFlags;

	char *pConvert = ConvertToIntern (_HeaderText);

		if (NULL != pConvert) {
			DELETE_VEC(_HeaderText);
			_HeaderText = pConvert;
		}
	}
}

HeaderEntryBase::HeaderEntryBase (
	GeoDB &geoDB, const char *Key, const char *Text, DWORD dwFlags, bool fForceNoProject) 
	: _DB (geoDB)
{
	m_dwFlags = dwFlags;
	m_fForceNoProject = fForceNoProject;

	if (Key != NULL) {
	// Schlüsseleintrag kopieren
		memset (_HeaderKey, ' ', HDRKEYLENGTH+1);
		strncpy (_HeaderKey, Key, HDRKEYLENGTH);

	int iLen = min (strlen (Key), (size_t)HDRKEYLENGTH);

		memset (&_HeaderKey[iLen], ' ', HDRKEYLENGTH-iLen);
		_HeaderKey[HDRKEYLENGTH] = '\0';
	}
	if (Text != NULL) {
	// Headertext kopieren
		ATLTRY(_HeaderText = new char [strlen (Text)+1]);
		if (_HeaderText == NULL) {
		// Kein Speicherplatz
			db_error (EC_NOMEMORY, RC_ctHeaderEntry);
			return;
		}
		strcpy (_HeaderText, Text);
	}
	_Status = HE_MODIFIED;
}

HeaderEntryBase::HeaderEntryBase (HeaderEntryBase &HE) 
	: _DB (HE.GetGeoDB())
{
	m_dwFlags = HE.Flags();
	m_fForceNoProject = HE.	m_fForceNoProject;

// Schlüsseleintrag kopieren
	memset (_HeaderKey, '\0', HDRKEYLENGTH+1);
	strncpy (_HeaderKey, HE._HeaderKey, HDRKEYLENGTH);
	_HeaderKey[HDRKEYLENGTH] = '\0';

// HeaderText kopieren
	if (HE._HeaderText != NULL) {
	// HeaderText vorhanden
		ATLTRY(_HeaderText = new char [strlen (HE._HeaderText)+1]);
		if (_HeaderText == NULL) {
		// Kein Speicherplatz
			_Status = HE_INVALID;
			db_error (EC_NOMEMORY, RC_ctHeaderEntry);
			return;
		}
		strcpy (_HeaderText, HE._HeaderText);
	}
	_Status = HE_UNMODIFIED;
}

// Zuweisungsoperator überladen
HeaderEntryBase & HeaderEntryBase::operator = (HeaderEntryBase &HE) 
{
	if (&HE != this) {
	// alten HeaderEntryBase freigeben
		DELETE_VEC (_HeaderText);

		m_dwFlags = HE.Flags();
		m_fForceNoProject = HE.m_fForceNoProject;

	// Schlüsseleintrag kopieren
		memset (_HeaderKey, '\0', HDRKEYLENGTH+1);
		strncpy (_HeaderKey, HE._HeaderKey, HDRKEYLENGTH);
		_HeaderKey[HDRKEYLENGTH] = '\0';

	// HeaderText kopieren
		if (HE._HeaderText != NULL) {
		// HeaderText vorhanden
			ATLTRY(_HeaderText = new char [strlen (HE._HeaderText)+1]);
			if (_HeaderText == NULL) {
			// Kein Speicherplatz
				_Status = HE_INVALID;
				db_error (EC_NOMEMORY, RC_ctHeaderEntry);
				return *this;
			}
			strcpy (_HeaderText, HE._HeaderText);
		}
		_Status = HE._Status;           // Kennzeichnen
	}
	return *this;
}

// verpaßt diesem HeaderEntryBase einen neuen Text --------------------------------
void HeaderEntryBase::SetEntryText (char *pNewText)
{
// HeaderText kopieren
	if (pNewText != NULL) {		// HeaderText vorhanden
		DELETE_OBJ (_HeaderText);	// alten Text löschen
		_HeaderText = new char [strlen (pNewText)+1];
		if (_HeaderText == NULL) {
		// Kein Speicherplatz
			_Status = HE_INVALID;
			db_error (EC_NOMEMORY, RC_SetEntryText);
			return;
		}
		strcpy (_HeaderText, pNewText);
		_Status = HE_MODIFIED;
	}
}

ErrCode HeaderEntryBase::WriteBack (void)
{
CActDB ActDB (_DB);
ErrCode RC = EC_OKAY;

//	if (_Status == HE_MODIFIED) {
//	char *pTextCopy = ConvertFromIntern (_HeaderText);
//
//		if (pTextCopy == NULL) 
//			return (ErrCode)db_error (EC_NOMEMORY, RC_HdrWriteBack);
//
//	long lLen = strlen (pTextCopy);
//
//		RC = (ErrCode)puthd_ (_DB.DBDesc(), pTextCopy, (short)lLen, &lLen, (long *)_HeaderKey, (long)m_dwFlags);
//		_DB.SetDirty (true);		// DB wurde modifiziert
//
//	// Speicher freigeben
//		DELETE_VEC(pTextCopy);
//	}

	if (_Status == HE_MODIFIED) {
	char *pTextCopy = ConvertFromIntern (_HeaderText);

		if (pTextCopy == NULL) 
			return (ErrCode)db_error (EC_NOMEMORY, RC_HdrWriteBack);

	GEODBHDRENTRYEX HE;

		INITSTRUCT (HE, GEODBHDRENTRYEX);
		strncpy (HE.hdrKey, _HeaderKey, HDRKEYLENGTH);
		HE.lphdrText = _HeaderText;
		HE.hdrTextLen = strlen (_HeaderText);
		HE.dwFlags = m_dwFlags;

		RC = DEX_WriteHeaderEntry (DBDesc(), HE);
		if (EC_OKAY == RC)	
			_Status = HE_UNMODIFIED;

	// Speicher freigeben
		DELETE_VEC(pTextCopy);
	}
	return RC;
}

ErrCode HeaderEntryBase::DeleteEntry (void)
{
ErrCode RC;
GEODBHDRENTRY HE;

	INITSTRUCT (HE, GEODBHDRENTRY);
	strncpy (HE.hdrKey, _HeaderKey, HDRKEYLENGTH);

	RC = DEX_DeleteHeaderEntry (DBDesc(), HE);
	if (EC_OKAY == RC)	
		_Status = HE_UNMODIFIED;

	return RC;
}

// liefert HeaderText als DoubleWert zurück
double HeaderEntryBase::EntryDouble (double Default) 
{
	if (_Status != HE_INVALID)
		return atof(_HeaderText);       // HeaderText konvertieren
	else
		return Default;         // ansonsten Standardwert liefern
}

// liefert HeaderTexxt als LongWert zurück
long HeaderEntryBase::EntryLong (long Default, int iBase) 
{
	if (_Status != HE_INVALID) {
		if (16 == iBase)
			return (long)strtoul (_HeaderText, NULL, 16);	// HeaderText konvertieren
		else 
			return atol (_HeaderText);
	} else
		return Default;
}

// Destruktor
HeaderEntryBase::~HeaderEntryBase (void) 
{
	DELETE_VEC (_HeaderText);	// alten HeaderEntryBase freigeben
}

///////////////////////////////////////////////////////////////////////////////
// Funktionen, die Sonderzeichen in/von Escape-Folgen konvertieren
char *ConvertFromIntern (char *pText)
{
	if (pText == NULL) return NULL;

int iLen = 5 * strlen (pText) +1;
char *pNewText = NULL; ATLTRY(pNewText = new char [iLen]);

	if (NULL == pNewText) return NULL;
	memset (pNewText, '\0', iLen);

// alle Sonderzeichen umkodieren
char *pTmp = pNewText;

	if (pNewText) {
		while (*pText) {
			switch (*pText) {
			case '\n':
				*pTmp++ = '\\';
				*pTmp++ = 'n';
				pText++;
				break;

			case '\t':
				*pTmp++ = '\\';
				*pTmp++ = 't';
				pText++;
				break;

			default:
				if (!isascii(*pText)) {
					wsprintf (pTmp, "\\0x%02.2x", (unsigned char)(*pText++));
					while (*pTmp)
						pTmp++;
				} else
					*pTmp++ = *pText++;
				break;
			}
		}
		*pTmp = '\0';
	}
#if defined(_FORCE_LEGACY_CODE)
	AnsiToOem (pNewText, pNewText);
#endif // defined(_FORCE_LEGACY_CODE)
	return pNewText;
}

char *ConvertToIntern (char *pText)
{
	if (pText == NULL) return NULL;

#if defined(_FORCE_LEGACY_CODE)
	OemToAnsi (pText, pText);			// Windows Zeichensatz
#endif // defined(_FORCE_LEGACY_CODE)

char *pNewText = NULL; ATLTRY(pNewText = new char [strlen (pText) +1]);
char *pTmp = pNewText;

	if (pNewText) {
		while (*pText) {
			if (*pText == '\\') {
				switch (*(pText+1)) {
				case 'n': 
					*pTmp++ = '\r';
					*pTmp++ = '\n';
					pText += 2;
					break;

				case 'r':
					*pTmp++ = '\r';
					pText += 2;
					break;

				case 't':
					*pTmp++ = '\t';
					pText += 2;
					break;

				case '0':	// Sonderzeichen
					{
					char cbTemp[5];

						memset (cbTemp, '\0', sizeof(cbTemp));
						strncpy (cbTemp, pText+1, 4);
						*pTmp++ = (char)strtol (cbTemp, NULL, 16);
						pText += 5;
					}
					break;

				default:
					*pTmp++ = *++pText;
					break;
				}
			} else
				*pTmp++ = *pText++;
		}
		*pTmp = '\0';
	}
	return pNewText;
}

