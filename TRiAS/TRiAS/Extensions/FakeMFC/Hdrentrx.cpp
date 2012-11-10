// HeaderEntry-Memberklassen, Variante fuer Erweiterungen
// File: HDRENTRX.CPP

#include "fakemfcp.hxx"

#include "hdrentrx.hxx"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// HeaderEntry ----------------------------------------------------------------
HeaderEntryX::HeaderEntryX (HPROJECT hPr) 
{
	memset (_HeaderKey, '\0', HDRKEYLENGTH+1);
	_HeaderText = NULL;
	_Status = HE_INVALID;
	m_dwFlags = HEADER_NORMAL;
	m_hPr = hPr;
}

HeaderEntryX::HeaderEntryX (const char *Key, HPROJECT hPr) 
{
	_Status = HE_INVALID;
	m_dwFlags = HEADER_NORMAL;
	m_hPr = hPr;

// Schlüsseleintrag kopieren
	if (Key != NULL) {
		memset (_HeaderKey, '\0', HDRKEYLENGTH+1);
		strncpy (_HeaderKey, Key, HDRKEYLENGTH);
		_HeaderKey[HDRKEYLENGTH] = '\0';
	}
	_HeaderText = NULL;     // falls abgebrochen werden muß

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
	if (DEX_ReadHeaderEntry(m_hPr, HE) == EC_OKAY) {
		_Status = HE_UNMODIFIED;
		m_dwFlags = HE.dwFlags;
	}
}

#if defined(__CV__)
HeaderEntryX::HeaderEntryX (ResID uiResHPROJECT hPr) 
{
ResString rsKey (uiRes, 17);

	_Status = HE_INVALID;
	m_dwFlags = HEADER_NORMAL;
	m_hPr = hPr;

// Schlüsseleintrag kopieren
	memset (_HeaderKey, '\0', HDRKEYLENGTH+1);
	strncpy (_HeaderKey, rsKey, HDRKEYLENGTH);

short iLen = min (strlen(rsKey.Addr()), HDRKEYLENGTH);

	memset (&_HeaderKey[iLen], ' ', HDRKEYLENGTH-iLen);
	_HeaderKey[HDRKEYLENGTH] = '\0';

	_HeaderText = NULL;     // falls abgebrochen werden muß

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
	if (DEX_ReadHeaderEntry(m_hPr, HE) == EC_OKAY) {
		_Status = HE_UNMODIFIED;
		m_dwFlags = HE.dwFlags;
	}
}
#endif // __CV__
#if defined(__MFC__)
HeaderEntryX::HeaderEntryX (UINT uiID, HPROJECT hPr) 
{
	_Status = HE_INVALID;
	m_dwFlags = HEADER_NORMAL;
	m_hPr = hPr;

CString str;

	TRY {
		VERIFY(str.LoadString (uiID));
	} CATCH(CMemoryException, e) {
		return;
	} END_CATCH

	_Status = HE_INVALID;
	m_dwFlags = HEADER_NORMAL;

// Schlüsseleintrag kopieren
	memset (_HeaderKey, '\0', HDRKEYLENGTH+1);
	strncpy (_HeaderKey, str, HDRKEYLENGTH);

short iLen = min (str.GetLength(), (int)HDRKEYLENGTH);

	memset (&_HeaderKey[iLen], ' ', HDRKEYLENGTH-iLen);
	_HeaderKey[HDRKEYLENGTH] = '\0';

	_HeaderText = NULL;     // falls abgebrochen werden muß

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
	if (DEX_ReadHeaderEntry(m_hPr, HE) == EC_OKAY) {
		_Status = HE_UNMODIFIED;
		m_dwFlags = HE.dwFlags;
	}
}
#endif // __MFC__

HeaderEntryX::HeaderEntryX (const char *Key, const char *Text, DWORD dwFlags, HPROJECT hPr) 
{
	_Status = HE_INVALID;
	m_dwFlags = dwFlags;
	m_hPr = hPr;

	if (Key != NULL) {
	// Schlüsseleintrag kopieren
		memset (_HeaderKey, '\0', HDRKEYLENGTH+1);
		strncpy (_HeaderKey, Key, HDRKEYLENGTH);
		_HeaderKey[HDRKEYLENGTH] = '\0';
	}
	if (Text != NULL) {
	// Headertext kopieren
		ATLTRY(_HeaderText = new char [strlen (Text)+1]);
		if (_HeaderText == NULL)	// Kein Speicherplatz
			return;
		strcpy (_HeaderText, Text);
	}
	_Status = HE_UNMODIFIED;
}

HeaderEntryX::HeaderEntryX (HeaderEntryX &HE) 
{
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
			return;
		}
		strcpy (_HeaderText, HE._HeaderText);
	}
	_Status = HE_UNMODIFIED;
}

// Zuweisungsoperator überladen -----------------------------------------------
HeaderEntryX & HeaderEntryX::operator = (HeaderEntryX &HE) 
{
	if (&HE != this) {
	// alten HeaderEntry freigeben
		DELETE_OBJ (_HeaderText);

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
				return *this;
			}
			strcpy (_HeaderText, HE._HeaderText);
		}

		_Status = HE._Status;           // Kennzeichnen
		m_hPr = HE.m_hPr;
		m_dwFlags = HE.m_dwFlags;
	}
	return *this;
}

// verpaßt diesem HeaderEntry einen neuen Text --------------------------------
void HeaderEntryX::SetEntryText (char *pNewText)
{
// HeaderText kopieren
	if (pNewText != NULL) {		// HeaderText vorhanden
		DELETE_OBJ (_HeaderText);	// alten Text löschen
		ATLTRY(_HeaderText = new char [strlen (pNewText)+1]);
		if (_HeaderText == NULL) {
		// Kein Speicherplatz
			_Status = HE_INVALID;
			return;
		}
		strcpy (_HeaderText, pNewText);
		_Status = HE_MODIFIED;
	}
}

ErrCode HeaderEntryX::WriteBack (void)
{               
ErrCode RC;
GEODBHDRENTRYEX HE;

	INITSTRUCT (HE, GEODBHDRENTRYEX);
	strncpy (HE.hdrKey, _HeaderKey, HDRKEYLENGTH);
	HE.lphdrText = _HeaderText;
	HE.hdrTextLen = strlen (_HeaderText);
	HE.dwFlags = m_dwFlags;

	if ((RC = DEX_WriteHeaderEntry (m_hPr, HE)) == EC_OKAY)	
		_Status = HE_UNMODIFIED;

return RC;
}

ErrCode HeaderEntryX::DeleteEntry (void)
{
ErrCode RC;
GEODBHDRENTRY HE;

	INITSTRUCT (HE, GEODBHDRENTRY);
	strncpy (HE.hdrKey, _HeaderKey, HDRKEYLENGTH);

	if ((RC = DEX_DeleteHeaderEntry (m_hPr, HE)) == EC_OKAY)	
		_Status = HE_UNMODIFIED;

return RC;
}


// liefert HeaderText als DoubleWert zurück
double HeaderEntryX::EntryDouble (double Default) 
{
	if (_Status != HE_INVALID)
		return atof(_HeaderText);       // HeaderText konvertieren
	else
		return Default;         // ansonsten Standardwert liefern
}

// liefert HeaderText als LongWert zurück
long HeaderEntryX::EntryLong (long Default) 
{
	if (_Status != HE_INVALID)
		return atol (_HeaderText);	// HeaderText konvertieren
	else
		return Default;
}

// Destruktor
HeaderEntryX::~HeaderEntryX (void) 
{
// Schlüsseleintrag löschen
	memset (_HeaderKey, '\0', HDRKEYLENGTH);

// alten HeaderEntry freigeben
	DELETE_VEC (_HeaderText);
}

