// HeaderEntry-Memberklassen, Variante fuer Erweiterungen
// File: HDRENTRX.CXX

#include "GeometrP.hxx"

#include "hdrentrx.hxx"

// HeaderEntry ----------------------------------------------------------------
#if _TRiAS_VER >= 0x0300
HeaderEntryX :: HeaderEntryX (HPROJECT hPr) 
#else
HeaderEntryX :: HeaderEntryX (void) 
#endif // _TRiAS_VER >= 0x0300
{
	memset (_HeaderKey, '\0', HDRKEYLENGTH+1);
	_HeaderText = NULL;
	_Status = HE_INVALID;
	m_dwFlags = HEADER_NORMAL;
#if _TRiAS_VER >= 0x0300
	m_hPr = hPr;
#endif // _TRiAS_VER >= 0x0300
}

#if _TRiAS_VER >= 0x0300
HeaderEntryX :: HeaderEntryX (const char *Key, HPROJECT hPr) 
#else
HeaderEntryX :: HeaderEntryX (const char *Key) 
#endif // _TRiAS_VER >= 0x0300
{
	_Status = HE_INVALID;
	m_dwFlags = HEADER_NORMAL;
#if _TRiAS_VER >= 0x0300
	m_hPr = hPr;
#endif // _TRiAS_VER >= 0x0300

// Schlüsseleintrag kopieren
	if (Key != NULL) {
		memset (_HeaderKey, '\0', HDRKEYLENGTH+1);
		strncpy (_HeaderKey, Key, HDRKEYLENGTH);
		_HeaderKey[HDRKEYLENGTH] = '\0';
	}
	_HeaderText = NULL;     // falls abgebrochen werden muß

// Puffer anlegen
	TX_TRY(_HeaderText = new char [HDRENTRYTEXTLEN+1]);
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
#if _TRiAS_VER >= 0x0300
	if (DEX_ReadHeaderEntry(m_hPr, HE) == EC_OKAY) {
#else
	if (DEX_ReadGeoDBHdrEntry(HE) == EC_OKAY) {
#endif // _TRiAS_VER >= 0x0300
		_Status = HE_UNMODIFIED;
		m_dwFlags = HE.dwFlags;
	}
}

#if _TRiAS_VER >= 0x0300
HeaderEntryX :: HeaderEntryX (ResID uiRes, HPROJECT hPr) 
#else
HeaderEntryX :: HeaderEntryX (ResID uiRes) 
#endif // _TRiAS_VER >= 0x0300
{
ResString rsKey (uiRes, 17);

	_Status = HE_INVALID;
	m_dwFlags = HEADER_NORMAL;
#if _TRiAS_VER >= 0x0300
	m_hPr = hPr;
#endif // _TRiAS_VER >= 0x0300

// Schlüsseleintrag kopieren
	memset (_HeaderKey, '\0', HDRKEYLENGTH+1);
	strncpy (_HeaderKey, rsKey, HDRKEYLENGTH);

short iLen = min (strlen(rsKey.Addr()), (size_t)HDRKEYLENGTH);

	memset (&_HeaderKey[iLen], ' ', HDRKEYLENGTH-iLen);
	_HeaderKey[HDRKEYLENGTH] = '\0';

	_HeaderText = NULL;     // falls abgebrochen werden muß

// Puffer anlegen
	TX_TRY(_HeaderText = new char [HDRENTRYTEXTLEN+1]);
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
#if _TRiAS_VER >= 0x0300
	if (DEX_ReadHeaderEntry(m_hPr, HE) == EC_OKAY) {
#else
	if (DEX_ReadGeoDBHdrEntry(HE) == EC_OKAY) {
#endif // _TRiAS_VER >= 0x0300
		_Status = HE_UNMODIFIED;
		m_dwFlags = HE.dwFlags;
	}
}

#if _TRiAS_VER >= 0x0300
HeaderEntryX :: HeaderEntryX (const char *Key, const char *Text, DWORD dwFlags, HPROJECT hPr) 
#else
HeaderEntryX :: HeaderEntryX (const char *Key, const char *Text, DWORD dwFlags) 
#endif // _TRiAS_VER >= 0x0300
{
	_Status = HE_INVALID;
	m_dwFlags = dwFlags;
#if _TRiAS_VER >= 0x0300
	m_hPr = hPr;
#endif // _TRiAS_VER >= 0x0300

	if (Key != NULL) {
	// Schlüsseleintrag kopieren
		memset (_HeaderKey, '\0', HDRKEYLENGTH+1);
		strncpy (_HeaderKey, Key, HDRKEYLENGTH);
		_HeaderKey[HDRKEYLENGTH] = '\0';
	}
	if (Text != NULL) {
	// Headertext kopieren
		TX_TRY(_HeaderText = new char [strlen (Text)+1]);
		if (_HeaderText == NULL)	// Kein Speicherplatz
			return;
		strcpy (_HeaderText, Text);
	}
	_Status = HE_UNMODIFIED;
}

HeaderEntryX :: HeaderEntryX (HeaderEntryX &HE) 
{
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
			return;
		}
		strcpy (_HeaderText, HE._HeaderText);
	}
	_Status = HE_UNMODIFIED;
	m_dwFlags = HE.m_dwFlags;
#if _TRiAS_VER >= 0x0300
	m_hPr = HE.m_hPr;
#endif // _TRiAS_VER >= 0x0300
}

// Zuweisungsoperator überladen -----------------------------------------------
HeaderEntryX & HeaderEntryX :: operator = (HeaderEntryX &HE) 
{
// alten HeaderEntry freigeben
	DELETE_OBJ (_HeaderText);

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
			return *this;
		}
		strcpy (_HeaderText, HE._HeaderText);
		m_dwFlags = HE.m_dwFlags;
#if _TRiAS_VER >= 0x0300
		m_hPr = HE.m_hPr;
#endif // _TRiAS_VER >= 0x0300
	}
	_Status = HE._Status;           // Kennzeichnen

return *this;
}

// verpaßt diesem HeaderEntry einen neuen Text --------------------------------
void HeaderEntryX :: SetEntryText (char *pNewText)
{
// HeaderText kopieren
	if (pNewText != NULL) {		// HeaderText vorhanden
		DELETE_OBJ (_HeaderText);	// alten Text löschen
		_HeaderText = new char [strlen (pNewText)+1];
		if (_HeaderText == NULL) {
		// Kein Speicherplatz
			_Status = HE_INVALID;
			return;
		}
		strcpy (_HeaderText, pNewText);
		_Status = HE_MODIFIED;
	}
}

ErrCode HeaderEntryX :: WriteBack (void)
{               
ErrCode RC;
GEODBHDRENTRYEX HE;

	INITSTRUCT (HE, GEODBHDRENTRYEX);
	strncpy (HE.hdrKey, _HeaderKey, HDRKEYLENGTH);
	HE.lphdrText = _HeaderText;
	HE.hdrTextLen = strlen (_HeaderText);
	HE.dwFlags = m_dwFlags;

#if _TRiAS_VER >= 0x0300
	if ((RC = DEX_WriteHeaderEntry (m_hPr, HE)) == EC_OKAY)	
#else
	if ((RC = DEX_WriteGeoDBHdrEntry (HE)) == EC_OKAY)	
#endif // _TRiAS_VER >= 0x0300
		_Status = HE_UNMODIFIED;

return RC;
}

ErrCode HeaderEntryX :: DeleteEntry (void)
{
ErrCode RC;
GEODBHDRENTRY HE;

	INITSTRUCT (HE, GEODBHDRENTRY);
	strncpy (HE.hdrKey, _HeaderKey, HDRKEYLENGTH);

#if _TRiAS_VER >= 0x0300
	if ((RC = DEX_DeleteHeaderEntry (m_hPr, HE)) == EC_OKAY)	
#else
	if ((RC = DEX_DeleteGeoDBHdrEntry (HE)) == EC_OKAY)	
#endif // _TRiAS_VER >= 0x0300
		_Status = HE_UNMODIFIED;

return RC;
}


// liefert HeaderText als DoubleWert zurück
double HeaderEntryX :: EntryDouble (double Default) 
{
	if (_Status != HE_INVALID)
		return atof(_HeaderText);       // HeaderText konvertieren
	else
		return Default;         // ansonsten Standardwert liefern
}

// liefert HeaderText als LongWert zurück
long HeaderEntryX :: EntryLong (long Default) 
{
	if (_Status != HE_INVALID)
		return atol (_HeaderText);	// HeaderText konvertieren
	else
		return Default;
}

// Destruktor
HeaderEntryX :: ~HeaderEntryX (void) 
{
// Schlüsseleintrag löschen
	memset (_HeaderKey, '\0', HDRKEYLENGTH);

// alten HeaderEntry freigeben
	DELETE_OBJ (_HeaderText);
}

