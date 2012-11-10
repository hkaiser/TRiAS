// @doc
// @module HeaderEntry.cpp | Routinen zum Zugriff auf die Headerinformationen eines
// Projektes bzw. einer Database

#include "trias01p.hxx"

#include <HeaderEntry.h>
#include <ErrInst.hxx>
#include <Switchkc.h>

#include "syncdb.hxx"

///////////////////////////////////////////////////////////////////////////////
//
static LPSTR ConvertFromIntern (LPCSTR pText);
static LPSTR ConvertToIntern (LPSTR pText);

///////////////////////////////////////////////////////////////////////////////
// Helperfunktion, die HeaderKey wenn notwendig mit Leerzeichen auffüllt
HRESULT CHeaderEntry::PrepareKey (LPCSTR pcKey)
{
	ZeroMemory (m_cbKey, HEADERKEYLEN+1);
	if (NULL == pcKey) return E_POINTER;

	strncpy (m_cbKey, pcKey, HEADERKEYLEN);

int iLen = min (strlen (pcKey), HEADERKEYLEN);

	if (iLen < HEADERKEYLEN)
		memset (&m_cbKey[iLen], ' ', HEADERKEYLEN-iLen);
	m_cbKey[HEADERKEYLEN] = '\0';
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Enumerieren der Headersätze
inline os_string PrepareKey (LPSTR pKey)
{
char cbBuffer[HEADERKEYLEN+1];

	strncpy (cbBuffer, pKey, HEADERKEYLEN);
	cbBuffer[HEADERKEYLEN] = '\0';

LPSTR pT = strrlchr (cbBuffer, ' ');

	if (NULL != pT)
		 *pT = '\0';
	return os_string(cbBuffer);
}

HRESULT CHeaderEntry::EnumHeaderData (HRESULT (CALLBACK *pFcn)(LPCSTR, DWORD), DWORD dwData) 
{
	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

ErrCode RC;
DB_ADDR dba(m_hPr);
ErrInstall EI ((ErrCode)S_NOTFOUND);

	dba.file_no = m_uiFile;
	RC = (ErrCode)z_keyfirst (&dba, m_uiKey);
	if (RC != EC_OKAY) {
	// Fehler aufgetreten
		if (WC_NOTFOUND == RC) 
			RC = EC_OKAY;			// nichts gefunden: OK
	
	// oder sonstiger Fehler 
		return (EC_OKAY == RC) ? S_OK : HRESULT_FROM_ERRCODE(RC);
	}

char cbHdidn[HEADERKEYLEN+1];		// HeaderSchlüssel
bool fNext = true;
HRESULT hr = S_OK;

	while (fNext) {
		RC = (ErrCode)z_keyread (m_hPr, cbHdidn);
		if (RC != EC_OKAY) break;
		cbHdidn[HEADERKEYLEN] = '\0';

	// nächsten Schlüssel suchen
		RC = (ErrCode)z_keynext (&dba, m_uiKey);
		fNext = (EC_OKAY == RC) ? true : false;

	// Enumeration
	KEYCONTEXT KC;

		GetKeyContext (&KC);
		hr = pFcn (::PrepareKey(cbHdidn).c_str(), dwData);
		SetKeyContext (&KC);

		if (S_OK != hr) return hr;		// abgebrochen oder Fehler
	}
	if (WC_NOTFOUND == RC)
		RC = EC_OKAY;

	return (EC_OKAY == RC) ? S_OK : HRESULT_FROM_ERRCODE(RC);
}

///////////////////////////////////////////////////////////////////////////////
// Einlesen eines Headersatzes

HRESULT CHeaderEntry::GetHeaderEntry (LPSTR pBuffer, size_t iLen, long *pFlags)
{
	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

DB_ADDR dba(m_hPr);
struct head headSatz;
ErrCode RC;
ErrInstall EI ((ErrCode)S_NOTFOUND);

// Satz suchen
	dba.file_no = m_uiFile;
	DBASSERTHR(z_keyfind (&dba, m_uiKey, m_cbKey));

// 1. Satz einlesen 
	__ReadHR(dba, headSatz);

	if (NULL != pFlags) 
		*pFlags = headSatz.hdrflags;		// Flags kopieren

	if (NULL == pBuffer)
		return S_OK;		// nur Flags abzufragen

size_t text_len = strlen (headSatz.text);

	if (text_len > iLen-1) {
	// Feld zu klein, wenigstens Anfang kopieren
		strncpy (pBuffer, headSatz.text, iLen-1);
		pBuffer[iLen-1] = '\0';

	string strT (ConvertToIntern (pBuffer));

		strcpy (pBuffer, strT.c_str());
		return HRESULT_FROM_ERRCODE((ErrCode)S_BADLEN);
	}
	strcpy (pBuffer, headSatz.text);

// weitere Sätze einlesen
	dba.file_no = m_uiFileNext;
	dba.rec_no = headSatz.zntext;

	while (0 != dba.rec_no) {
	struct fhead headfSatz;

		__ReadHR(dba, headfSatz);

	size_t iLenN = strlen (headfSatz.textf);

		if (text_len + iLenN > iLen-1) {
		// Feld zu klein, wenigstens voll machen 
			strncpy (&pBuffer[text_len], headfSatz.textf, iLen-text_len-1);
			pBuffer[iLen-1] = '\0';

		string strT (ConvertToIntern (pBuffer));

			strcpy (pBuffer, strT.c_str());
			return HRESULT_FROM_ERRCODE((ErrCode)S_BADLEN);
		}

		strncpy (&pBuffer[text_len], headfSatz.textf, iLenN);
		text_len += iLenN;
		dba.rec_no = headfSatz.ztextf;
	}

// sauber abschließen
	pBuffer[text_len] = '\0';

string strT (ConvertToIntern (pBuffer));

	strcpy (pBuffer, strT.c_str());
	db_status = S_OKAY;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Schreiben eines Headereintrages

HRESULT CHeaderEntry::PutHeaderEntry (LPCSTR pcText, size_t iLen, long lFlags)
{
	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

DB_ADDR dba(m_hPr);
ErrInstall EI ((ErrCode)S_NOTFOUND);		// Fehlermeldung ignorieren 

	dba.file_no = m_uiFile;
	if (S_OKAY != z_keyfind (&dba, m_uiKey, m_cbKey)) {
		if (S_NOTFOUND == db_status) {
		// Schlüssel existiert noch nicht --> Neueinspeichern
			if (S_OKAY != StoreHeaderEntryHelper (pcText, iLen, lFlags)) 
				return HRESULT_FROM_ERRCODE((ErrCode)db_status);
		} else 
			return HRESULT_FROM_ERRCODE((ErrCode)db_status);
	} else {
	// Schlüssel existiert bereits, alten Satz loeschen 
		if (S_OK != DeleteHeaderEntryHelper (&dba) ||
			S_OK != StoreHeaderEntryHelper (pcText, iLen, lFlags)) 
		{
			return HRESULT_FROM_ERRCODE((ErrCode)db_status);
		}
	}

	db_status = S_OKAY;
	return S_OK;
}

HRESULT CHeaderEntry::StoreHeaderEntryHelper (LPCSTR pcText, size_t iLen, long lFlags)
{
	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

DB_ADDR dba(m_hPr);
struct head headSatz;
ErrCode RC;

	dba.file_no = m_uiFile;
	dba.rec_no = 0;

// Konvertieren
string strTextCopy (ConvertFromIntern (pcText));

// Informationen einkopieren und 1. Satz generieren
	memcpy (headSatz.hdidn, m_cbKey, HEADERKEYLEN);
	strncpy (headSatz.text, strTextCopy.c_str(), sizeof(headSatz.text));
	headSatz.hdrflags = lFlags;
	__NewHR (dba, headSatz);

// wenn Fortsetzungssätze notwendig sind, dann diese erzeugen und verketten
	if (iLen <= sizeof(headSatz.text)) {
		db_status = S_OKAY;
		return S_OK;
	}

size_t text_len = sizeof(headSatz.text);
BOOL fFirst = TRUE;
DB_ADDR dbaHeadf (m_hPr);

	dbaHeadf.file_no = m_uiFileNext;
	dbaHeadf.rec_no = 0;

LONG lSatzNr = 0;

	while (text_len < iLen) {
	LONG lPrev = lSatzNr;
	struct fhead fheadSatz;

	// neuen Satz füllen
		strncpy (fheadSatz.textf, &(strTextCopy.c_str()[text_len]), sizeof(fheadSatz.textf));
		text_len += sizeof(fheadSatz.textf);
		__NewHR (dbaHeadf, fheadSatz);
		lSatzNr = dbaHeadf.rec_no;

	// Rückverkettung vornehmen
		if (fFirst) {
		// ersten Satz wegschreiben
			headSatz.zntext = lSatzNr;
			__WriteHR(dba, headSatz);
			fFirst = FALSE;
		} else {
		// vorherigen Satz komplettieren
			TX_ASSERT(0 != lPrev);
			dbaHeadf.rec_no = lPrev;
			__ReadHR(dbaHeadf, fheadSatz);
			fheadSatz.ztextf = lSatzNr;
			__WriteHR(dbaHeadf, fheadSatz);
		}
	} 
  
	db_status = S_OKAY;
	return S_OK;
}


///////////////////////////////////////////////////////////////////////////////
// Löschen eines Headereintrages

HRESULT CHeaderEntry::DeleteHeaderEntry (void)
{
	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

ErrInstall EI((ErrCode)S_NOTFOUND);
DB_ADDR dba(m_hPr);
ErrCode RC;

	dba.file_no = m_uiFile;
	DBASSERTHR(z_keyfind (&dba, m_uiKey, m_cbKey));

// Schlüssel existiert --> löschen
	return HRESULT_FROM_ERRCODE(DeleteHeaderEntryHelper (&dba));
}

HRESULT CHeaderEntry::DeleteHeaderEntryHelper (DB_ADDR *dba)
{
// ersten Satz einlesen ...
struct head headSatz;
ErrCode RC;

	__ReadHR(*dba, headSatz);

INT lSatzNr = headSatz.zntext;

// ... und freigeben
	__DisposeHR(*dba);

DB_ADDR mydba (m_hPr);

	mydba.file_no = m_uiFileNext;
	while (0 != lSatzNr) {
	// für alle weiteren Sätze
	struct fhead headfSatz;

	// Einlesen ...
		mydba.rec_no = lSatzNr;
		__ReadHR(mydba, headfSatz);
		lSatzNr = headfSatz.ztextf;
	
	// ... und Freigeben 
		__DisposeHR(mydba);
    }
	
	db_status = S_OKAY;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Funktionen, die Sonderzeichen in/von Escape-Folgen konvertieren
static char *ConvertFromIntern (const char *pText)
{
	if (pText == NULL) return NULL;

int iLen = 4 * strlen (pText) +1;
char *pNewText = NULL;

	TX_TRY(pNewText = new char [iLen]);
	if (NULL == pNewText) return NULL;
	ZeroMemory (pNewText, iLen);

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

static char *ConvertToIntern (char *pText)
{
	if (pText == NULL) return NULL;

char *pNewText = NULL;

	TX_TRY(pNewText = new char [strlen(pText) +1]);
	if (NULL == pNewText) return NULL;

	OemToAnsi (pText, pText);			// Windows Zeichensatz

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


