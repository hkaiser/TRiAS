// HeaderEntry - Klasse -------------------------------------------------------
// File: HDENTRY.CXX

#include "trias02p.hxx"

#include <hdrentry.hxx>

extern char pDLLName[];

char *ConvertToIntern (char *pText);
char *ConvertFromIntern (char *pText);

// HeaderEntry ----------------------------------------------------------------
HeaderEntry :: HeaderEntry (GeoDB &geoDB) 
	     : _DB (geoDB)
{
	memset (_HeaderKey, '\0', HDRKEYLENGTH+1);
	_HeaderText = NULL;
	_Status = HE_INVALID;
	m_dwFlags = HEADER_NORMAL;
}

HeaderEntry :: HeaderEntry (GeoDB &geoDB, const char *Key) 
	     : _DB (geoDB)
{
long len;
short shortlen;
ErrCode EC;
CActDB ActDB (_DB);

// Schlüsseleintrag kopieren
	if (Key != NULL) {
		memset (_HeaderKey, ' ', HDRKEYLENGTH+1);
		strncpy (_HeaderKey, Key, HDRKEYLENGTH);

	short iLen = min (strlen (Key), HDRKEYLENGTH);

		memset (&_HeaderKey[iLen], ' ', HDRKEYLENGTH-iLen);
		_HeaderKey[HDRKEYLENGTH] = '\0';
	}
	_HeaderText = NULL;     // falls abgebrochen werden muá

	m_dwFlags = HEADER_NORMAL;

// HeaderTextlänge bestimmen
ErrInstall EI (WC_NOTFOUND);

	EC = (ErrCode)gethdlen (_DB.DBDesc(), (long *)_HeaderKey, &shortlen);
	if (EC != EC_OKAY) {
		_Status = HE_INVALID;   // profilaktisch !
		return; // Fehler aufgetreten
	}

// Puffer anlegen
	_HeaderText = new char [++shortlen];
	if (_HeaderText == NULL) {
	// Kein Speicherplatz mehr
		_Status = HE_INVALID;   // profilaktisch !
		db_error (EC_NOMEMORY, RC_ctHeaderEntry);
		return;
	}

// HeaderText einlesen
	len = (long)shortlen;
	EC = (ErrCode)gethd_ (_DB.DBDesc(), _HeaderText, shortlen, &len, (long *)_HeaderKey, (long *)&m_dwFlags);
	if (EC != EC_OKAY) {            // Fehler aufgetreten
		_Status = HE_INVALID;   // profilaktisch !
		return;
	}
	_HeaderText[shortlen-1] = '\0'; // NullByte anfügen

char *pConvert = ConvertToIntern (_HeaderText);

	if (NULL != pConvert) {
		delete _HeaderText;
		_HeaderText = pConvert;
	}

	_Status = HE_UNMODIFIED;
}


HeaderEntry :: HeaderEntry (GeoDB &geoDB, ResID uiRes) 
	     : _DB (geoDB)
{
ResString rsKey (uiRes, 17);
long len;
short shortlen;
ErrCode EC;
CActDB ActDB (_DB);

// Schlüsseleintrag kopieren
	memset (_HeaderKey, ' ', HDRKEYLENGTH+1);
	strncpy (_HeaderKey, rsKey.Addr(), HDRKEYLENGTH);

	m_dwFlags = HEADER_NORMAL;

short iLen = min (strlen(rsKey.Addr()), HDRKEYLENGTH);

	memset (&_HeaderKey[iLen], ' ', HDRKEYLENGTH-iLen);
	_HeaderKey[HDRKEYLENGTH] = '\0';

	_HeaderText = NULL;     // falls abgebrochen werden muß

// HeaderTextlänge bestimmen
ErrInstall EI (WC_NOTFOUND);

	EC = (ErrCode)gethdlen (_DB.DBDesc(), (long *)_HeaderKey, &shortlen);
	if (EC != EC_OKAY) {
		_Status = HE_INVALID;   // profilaktisch !
		return; // Fehler aufgetreten
	}

// Puffer anlegen
	_HeaderText = new char [++shortlen];
	if (_HeaderText == NULL) {
	// Kein Speicherplatz mehr
		_Status = HE_INVALID;   // profilaktisch !
		db_error (EC_NOMEMORY, RC_ctHeaderEntry);
		return;
	}

// HeaderText einlesen
	len = (long)shortlen;
	EC = (ErrCode)gethd_ (_DB.DBDesc(), _HeaderText, shortlen, &len, (long *)_HeaderKey, (long *)m_dwFlags);
	if (EC != EC_OKAY) {            // Fehler aufgetreten
		_Status = HE_INVALID;   // profilaktisch !
		return;
	}
	_HeaderText[shortlen-1] = '\0'; // NullByte anfügen

char *pConvert = ConvertToIntern (_HeaderText);

	if (NULL != pConvert) {
		delete _HeaderText;
		_HeaderText = pConvert;
	}
	_Status = HE_UNMODIFIED;
}


HeaderEntry :: HeaderEntry (GeoDB &geoDB, const char *Key, const char *Text, DWORD dwFlags) 
	     : _DB (geoDB)
{
	m_dwFlags = dwFlags;

	if (Key != NULL) {
	// Schlüsseleintrag kopieren
		memset (_HeaderKey, ' ', HDRKEYLENGTH+1);
		strncpy (_HeaderKey, Key, HDRKEYLENGTH);

	short iLen = min (strlen (Key), HDRKEYLENGTH);

		memset (&_HeaderKey[iLen], ' ', HDRKEYLENGTH-iLen);
		_HeaderKey[HDRKEYLENGTH] = '\0';
	}
	if (Text != NULL) {
	// Headertext kopieren
		_HeaderText = new char [strlen (Text)+1];
		if (_HeaderText == NULL) {
		// Kein Speicherplatz
			db_error (EC_NOMEMORY, RC_ctHeaderEntry);
			return;
		}
		strcpy (_HeaderText, Text);
	}
	_Status = HE_MODIFIED;
}

HeaderEntry :: HeaderEntry (HeaderEntry &HE) 
	     : _DB (HE.GetGeoDB())
{
	m_dwFlags = HE.Flags();

// Schlüsseleintrag kopieren
	memset (_HeaderKey, '\0', HDRKEYLENGTH+1);
	strncpy (_HeaderKey, HE._HeaderKey, HDRKEYLENGTH);
	_HeaderKey[HDRKEYLENGTH] = '\0';

// HeaderText kopieren
	if (HE._HeaderText != NULL) {
	// HeaderText vorhanden
		_HeaderText = new char [strlen (HE._HeaderText)+1];
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
HeaderEntry & HeaderEntry :: operator = (HeaderEntry &HE) 
{
// alten HeaderEntry freigeben
	DELETE (_HeaderText);

	m_dwFlags = HE.Flags();

// Schlüsseleintrag kopieren
	memset (_HeaderKey, '\0', HDRKEYLENGTH+1);
	strncpy (_HeaderKey, HE._HeaderKey, HDRKEYLENGTH);
	_HeaderKey[HDRKEYLENGTH] = '\0';

// HeaderText kopieren
	if (HE._HeaderText != NULL) {
	// HeaderText vorhanden
		_HeaderText = new char [strlen (HE._HeaderText)+1];
		if (_HeaderText == NULL) {
		// Kein Speicherplatz
			_Status = HE_INVALID;
			db_error (EC_NOMEMORY, RC_ctHeaderEntry);
			return *this;
		}
		strcpy (_HeaderText, HE._HeaderText);
	}
	_Status = HE._Status;           // Kennzeichnen

return *this;
}

// verpaßt diesem HeaderEntry einen neuen Text --------------------------------
void HeaderEntry :: SetEntryText (char *pNewText)
{
// HeaderText kopieren
	if (pNewText != NULL) {		// HeaderText vorhanden
		DELETE (_HeaderText);	// alten Text löschen
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

ErrCode HeaderEntry :: WriteBack (void)
{
CActDB ActDB (_DB);
ErrCode RC = EC_OKAY;

	if (_Status == HE_MODIFIED) {
	char *pTextCopy = ConvertFromIntern (_HeaderText);

		if (pTextCopy == NULL) 
			return (ErrCode)db_error (EC_NOMEMORY, RC_HdrWriteBack);

	long lLen = strlen (pTextCopy);

		RC = (ErrCode)puthd_ (_DB.DBDesc(), pTextCopy, (short)lLen, &lLen, (long *)_HeaderKey, (long)m_dwFlags);
		_DB.SetDirty (true);		// DB wurde modifiziert

	// Speicher freigeben
		delete pTextCopy;
	}
	
return RC;
}

// liefert HeaderText als DoubleWert zurück
double HeaderEntry :: EntryDouble (double Default) 
{
	if (_Status != HE_INVALID)
		return atof(_HeaderText);       // HeaderText konvertieren
	else
		return Default;         // ansonsten Standardwert liefern
}

// liefert HeaderTexxt als LongWert zurück
long HeaderEntry :: EntryLong (long Default, int iBase) 
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
HeaderEntry :: ~HeaderEntry (void) 
{
	DELETE (_HeaderText);	// alten HeaderEntry freigeben
}

///////////////////////////////////////////////////////////////////////////////
// Funktionen, die Sonderzeichen in/von Escape-Folgen konvertieren
char *ConvertFromIntern (char *pText)
{
	if (pText == NULL) return NULL;

int iLen = 4 * strlen (pText) +1;
char *pNewText = new char [iLen];

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
	AnsiToOem (pNewText, pNewText);

return pNewText;
}

char *ConvertToIntern (char *pText)
{
	if (pText == NULL) return NULL;

	OemToAnsi (pText, pText);			// Windows Zeichensatz

char *pNewText = new char [strlen (pText) +1];
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


