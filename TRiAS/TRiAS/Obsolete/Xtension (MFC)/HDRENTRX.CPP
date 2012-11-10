// HeaderEntry-Memberklassen, Variante fuer Erweiterungen
// File: HDRENTRX.CXX

extern "C" {
	#include <windows.h>
	#include <stdlib.h>
	#include <string.h>

	#include <protos.h>
	#include <zprotos.h> 
	
	#include <xtension.h>
	#include <xtensnx.h>
}

#include <commonvu.hxx>

#include <ristypes.hxx>
#include <errcodes.hxx>

#include "hdrentrx.hxx"

// HeaderEntry ----------------------------------------------------------------
HeaderEntryX :: HeaderEntryX (void) 
{
	memset (_HeaderKey, '\0', HDRKEYLENGTH+1);
	_HeaderText = NULL;
	_Status = HE_INVALID;
}

HeaderEntryX :: HeaderEntryX (const char *Key) 
{
	_Status = HE_INVALID;

// Schl¸sseleintrag kopieren
	if (Key != NULL) {
		memset (_HeaderKey, '\0', HDRKEYLENGTH+1);
		strncpy (_HeaderKey, Key, HDRKEYLENGTH);
		_HeaderKey[HDRKEYLENGTH] = '\0';
	}
	_HeaderText = NULL;     // falls abgebrochen werden muﬂ

// Puffer anlegen
	_HeaderText = new char [HDRENTRYTEXTLEN+1];
	if (_HeaderText == NULL) {
	// Kein Speicherplatz mehr
		_Status = HE_INVALID;  	// profilaktisch !
		return;
	}

// HeaderEintrag holen
GEODBHDRENTRY HE;

	memset (&HE, '\0', sizeof(GEODBHDRENTRY));
	HE.dwSize = sizeof(GEODBHDRENTRY);
	strncpy (HE.hdrKey, _HeaderKey, HDRKEYLENGTH);
	HE.lphdrText = _HeaderText;
	HE.hdrTextLen = HDRENTRYTEXTLEN;
	
// HeaderText einlesen
	if (DEX_ReadGeoDBHdrEntry(HE)  == EC_OKAY)
		_Status = HE_UNMODIFIED;
}


HeaderEntryX :: HeaderEntryX (const char *Key, const char *Text) 
{
	_Status = HE_INVALID;

	if (Key != NULL) {
	// Schl¸sseleintrag kopieren
		memset (_HeaderKey, '\0', HDRKEYLENGTH+1);
		strncpy (_HeaderKey, Key, HDRKEYLENGTH);
		_HeaderKey[HDRKEYLENGTH] = '\0';
	}
	if (Text != NULL) {
	// Headertext kopieren
		_HeaderText = new char [strlen (Text)+1];
		if (_HeaderText == NULL)	// Kein Speicherplatz
			return;
		strcpy (_HeaderText, Text);
	}
	_Status = HE_UNMODIFIED;
}

HeaderEntryX :: HeaderEntryX (HeaderEntryX &HE) 
{
// Schl¸sseleintrag kopieren
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
}

// Zuweisungsoperator Åberladen
HeaderEntryX & HeaderEntryX :: operator = (HeaderEntryX &HE) 
{
// alten HeaderEntry freigeben
	DELETE (_HeaderText);

// SchlÅsseleintrag kopieren
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
	}
	_Status = HE._Status;           // Kennzeichnen

return *this;
}

// verpa·t diesem HeaderEntry einen neuen Text --------------------------------
void HeaderEntryX :: SetEntryText (char *pNewText)
{
// HeaderText kopieren
	if (pNewText != NULL) {		// HeaderText vorhanden
		DELETE (_HeaderText);	// alten Text lˆschen
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
GEODBHDRENTRY HE;

	memset (&HE, '\0', sizeof(GEODBHDRENTRY));
	HE.dwSize = sizeof(GEODBHDRENTRY);
	strncpy (HE.hdrKey, _HeaderKey, HDRKEYLENGTH);
	HE.lphdrText = _HeaderText;
	HE.hdrTextLen = strlen (_HeaderText);

	if ((RC = DEX_WriteGeoDBHdrEntry (HE)) == EC_OKAY)	
		_Status = HE_UNMODIFIED;

return RC;
}

// liefert HeaderText als DoubleWert zur¸ck
double HeaderEntryX :: EntryDouble (double Default) 
{
	if (_Status != HE_INVALID)
		return atof(_HeaderText);       // HeaderText konvertieren
	else
		return Default;         // ansonsten Standardwert liefern
}

// liefert HeaderText als LongWert zur¸ck
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
// Schl¸sseleintrag lˆschen
	memset (_HeaderKey, '\0', HDRKEYLENGTH);

// alten HeaderEntry freigeben
	DELETE (_HeaderText);
}

