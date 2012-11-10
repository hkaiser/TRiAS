// PBD-Datensaetze -- Klassen- & Memberfunktionen
// File: PBD.CXX

#include "trias01p.hxx"
#include "obj32/trias321.h"

#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#include <ActDB.h>
#include <ctype.h>
#include <switchkc.h>
#include <NativePbd.h>
#include <HeaderEntry.h>
#include <ErrInst.hxx>

#include "Strings.h"
#include "syncdb.hxx"

// 
#define MAXTEXTMERKMALLEN       80

extern "C" HINSTANCE g_hInstance;

namespace trias_nativepbd {

// Konstruktoren für PBD-Datenklasse-------------------------------------------
CNativePbd::CNativePbd (HPROJECT hPr, PBDTyp Typ)
	: m_hPr(hPr) 
{
	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

// Daten auf Defaultwerte initialisieren
	m_lCode = 0;
	m_dbaSatz = -1;
	m_rgTyp = Typ;
	m_rgStatus = PBD_Invalid;
	m_fTemp = false;
}

CNativePbd::CNativePbd (HPROJECT hPr, PBDTyp rgTyp, long lCode) 
	: m_hPr(hPr) 
{
	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

// Memberdaten initialisieren
	m_lCode = lCode;
	m_dbaSatz = -1;
	m_rgTyp = rgTyp;
	m_rgStatus = PBD_Invalid;
	m_hPr = hPr;
	m_fTemp = false;
}

HRESULT CNativePbd::FInit (LPCSTR lpkText, BOOL fIssueError, BOOL fCorrectName)
{
	if (NULL == m_hPr || 0 == m_lCode) 
		return E_UNEXPECTED;

// Code setzen und Kurztext dazu lesen
ErrCode EC = EC_OKAY;
HRESULT hr;

	{
	CActDB ActDB (m_hPr);		// PBD-DB aktivieren
	ErrInstall E1 (WC_NOTFOUND);

		hr = mfind (m_lCode, &m_dbaSatz);
	}

	if (S_OK != hr && NULL == lpkText) {
	// Versuchen, aus TempTree zu lesen
	ErrCode Result = EC;

	// solange versuchen bis abgebrochen oder richtig definiert
	int iCnt = 0;

		if (fIssueError) {
			do {
			// PBD wieder wegschalten
				switch (m_rgTyp) {
				case PBD_IDENT:
					Result = (ErrCode)db_error (WC_NOIDENT, RC_ctPBD_Data, &m_lCode);
					break;

				case PBD_MERKMAL:
					Result = (ErrCode)db_error (WC_NOMERKMAL, RC_ctPBD_Data, &m_lCode);
					break;

				case PBD_RELATION:
					Result = (ErrCode)db_error (WC_NORELATION, RC_ctPBD_Data, &m_lCode);
					break;
				}

				if (Result == EC_OKAY) {
				// nochmal versuchen
				CActDB ActDB (m_hPr);		// PBD wieder zuschalten
				ErrInstall E1 (WC_NOTFOUND);

					hr = mfind (m_lCode, &m_dbaSatz);
					if (S_OK == hr)
						break;
				}
			} while (++iCnt < 3 && Result == EC_OKAY);
		} // fIssueError

		if (S_OK != hr) {
		// Fehler aufgetreten
			if (hr == HRESULT_FROM_ERRCODE(WC_NOTFOUND))  // neuer Satz
				m_rgStatus = PBD_Unmodified;
			return hr;
		}
	} 

	if (NULL == lpkText || '\0' == *lpkText) {
	// KurzText lesen
	CActDB ActDB (m_hPr);
	char cbBuffer[TEXTLEN+1];

		cbBuffer[0] = '\0';		// für alle Fälle
		mgetkt (cbBuffer);

		OemToAnsi (cbBuffer, cbBuffer);

	// alten Bug ausgleichen, wo Kurztext den gesamten Objekteigenschaftsnamen
	// "OBJPROP_ROOT\\etc..." enthielt
		if (strncmp (cbBuffer, "OBJPROP_ROOT", strlen("OBJPROP_ROOT"))) {
			if (fCorrectName)
				EnsureUniqueName (cbBuffer);	// Eindeutigkeit des Kurztextes gewährleisten
			else
				m_strKurzText = cbBuffer;
		} else {
		// in der Zukunft vermeiden
			m_strKurzText = "";			// so tun, als objs nicht definiert wäre
			PutKurzText();
		}
		m_rgStatus = PBD_Unmodified;
	} 
	else if (NULL != lpkText) {
	// temporäres Objekt
		m_strKurzText = lpkText;
		m_rgStatus = PBD_Unmodified;
	}
	return S_OK;
}

CNativePbd::~CNativePbd (void) 
{
}

///////////////////////////////////////////////////////////////////////////////
// Eindeutigkeit des Kurztextes sicherstellen
HRESULT CNativePbd::EnsureUniqueName (LPCSTR pcName)
{
char cbBuffer[_MAX_PATH];
int iCnt = 1;
bool fModified = false;

	strcpy (cbBuffer, pcName);
	while (!IsUniqueName (cbBuffer)) {
	char cbCnt[16];

		strcpy (cbBuffer, pcName);
		strcat (cbBuffer, " (");
		strcat (cbBuffer, ltoa (iCnt++, cbCnt, 10));
		strcat (cbBuffer, ")");

		fModified = true;
	}
	if (fModified) {
	// gleich wegschreiben (für die Zukunft)
		m_strKurzText = cbBuffer;
		return PutKurzText();
	}

	m_strKurzText = pcName;
	return S_OK;
}

/*static*/
HRESULT CALLBACK CNativePbd::IsUniqueNameCallback (INT_PTR lCode, UINT_PTR dwData)
{
long *plCnt = reinterpret_cast<long *>(dwData);

	return (++(*plCnt) > 1) ? S_FALSE : S_OK;	// nach dem Zweiten abbrechen
}

BOOL CNativePbd::IsUniqueName (LPCSTR pcName)
{
long lCnt = 0;

	EnumEqualEntries (m_hPr, m_rgTyp, pcName, IsUniqueNameCallback, reinterpret_cast<UINT_PTR>(&lCnt));
	return (lCnt <= 1) ? TRUE : FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// Memberfunktionen 

// KurzText und LangText austauschen ------------------------------------------
HRESULT CNativePbd::SetKurzText (LPCSTR newText) 
{
	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

	m_strKurzText = (NULL != newText) ? newText : TEXT("");
	m_rgStatus = PBD_Modified;
	return S_OK;
}

HRESULT CNativePbd::SetLangText (LPCSTR newText)
{
	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

	m_strLangText = (NULL != newText) ? newText : TEXT("");
	m_rgStatus = PBD_Modified;
	return S_OK;
}

// KurzText wegschreiben
HRESULT CNativePbd::PutKurzText (void)
{
	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

// PDB-DB aktivieren
CActDB ActDB (m_hPr);

char cbBuffer[_MAX_PATH];
ErrCode RC;

	TX_ASSERT(m_strKurzText.size() < sizeof(cbBuffer));
	AnsiToOem (m_strKurzText.c_str(), cbBuffer);
	DBASSERTHR (mputkt (cbBuffer));
	return S_OK;
}

// LangText wegschreiben
HRESULT CNativePbd::PutLangText (int iTyp)
{
	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

// PDB-DB aktivieren
CActDB ActDB (m_hPr);

	if (m_strLangText.size() == 0) 
		return S_FALSE;

LPSTR pBuffer = NULL;
ErrCode RC;

	TX_TRY(pBuffer = new char[m_strLangText.size()+1]);
	if (NULL == pBuffer) return E_OUTOFMEMORY;

	AnsiToOem (m_strLangText.c_str(), pBuffer);
	DBASSERTHR(mputtx (pBuffer));

	DELETE_VEC(pBuffer);
	return S_OK;
}

LPCSTR CNativePbd::GetLangText (LPSTR pBuffer, int iLen) 
{
	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

// PDB-DB aktivieren
CActDB ActDB (m_hPr);

	m_strLangText.erase();

// wenn der gesuchte Satz nicht existiert, dann gleich wieder raus
	if (-1 == m_dbaSatz) {
		::SetLastError(E_UNEXPECTED);
		return NULL;
	}

long lTextLen = 0;

// Länge des LangTextes bestimmen
ErrCode EC = (ErrCode)mgetl (&lTextLen);
	
	if (EC != EC_OKAY) {
		::SetLastError(HRESULT_FROM_ERRCODE(EC));            // Fehler aufgetreten
		return NULL;
	}
	if (0 == lTextLen) {
		::SetLastError(HRESULT_FROM_ERRCODE(WC_NOTFOUND));            // Fehler aufgetreten
		return NULL;		// kein Text gegeben
	}

// wenn LangText noch nicht gelesen ist, dann einlesen
LPSTR pBufferT = NULL;

	TX_TRY(pBufferT = new char[lTextLen+1]);
	if (NULL == pBufferT) {
		::SetLastError(E_OUTOFMEMORY);
		return NULL;
	}

	EC = (ErrCode)mgettx (pBufferT);
	if (EC != S_OK) {
		DELETE_VEC(pBufferT);
		if (S_FALSE != EC)
			::SetLastError(HRESULT_FROM_ERRCODE(EC));
		return NULL;
	}

	OemToAnsi (pBufferT, pBufferT);       // Windows Zeichensatz
	m_strLangText = pBufferT;
	DELETE_VEC(pBufferT);

	if (NULL != pBuffer) {
	int iToCopy = min(long(iLen-1), lTextLen);
		
		strncpy (pBuffer, m_strLangText.c_str(), iToCopy);
		pBuffer[iToCopy] = '\0';
	}

	::SetLastError(S_OK);
	return m_strLangText.c_str();
}

// Freigeben der FolgeSätze eines LangTextes
HRESULT CNativePbd::FreeText (int iFileNo, long lRecNo) 
{
DB_ADDR dba (m_hPr);
ErrCode RC;
long lPBDVersion = LocGetDBVersion(m_hPr);

	dba.file_no = iFileNo;
	if (lPBDVersion <= PBDVERSION03000001) {
	struct fdesc_001 F001Satz;

		while (lRecNo != 0) {
			dba.rec_no = lRecNo;
			__ReadHR (dba, F001Satz);
			lRecNo = F001Satz.FNext;
			__DisposeHR (dba, F001Satz);
		}
	} 
	else {
		TX_ASSERT(lPBDVersion >= PBDVERSION03000002);

	struct fdesc FSatz;

		while (lRecNo != 0) {
			dba.rec_no = lRecNo;
			__ReadHR (dba, FSatz);
			lRecNo = FSatz.FNext;
			__DisposeHR (dba, FSatz);
		}
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Enumeration der Einträge einer PBD 
/*static*/ HRESULT CNativePbd::EnumPBDData (
	HPROJECT hPr, long pbdTyp, HRESULT (CALLBACK *pFcn)(INT_PTR, UINT_PTR), UINT_PTR dwData) 
{
	TX_ASSERT(NULL != hPr);
	SYNC_DBACCESS (g_pDbMutex, hPr);

// PDB-DB aktivieren
CActDB ActDB (hPr);

ErrCode RC;
DB_ADDR dba (hPr);
ErrInstall EI (WC_NOTFOUND);
int keyIndex;

	switch (pbdTyp) {
	case PBD_IDENT:
		keyIndex = IDS;
		break;
		
	case PBD_MERKMAL:
		keyIndex = MKS; 
		break;
		
	case PBD_RELATION:
		keyIndex = PRIREL; 
		break;

	default:
		TX_ASSERT(false);
		return E_UNEXPECTED;
	}

	RC = (ErrCode)z_keyfirst (&dba, keyIndex);
	if (RC != EC_OKAY) {
	// Fehler aufgetreten
		if (RC == WC_NOTFOUND) 
			return S_FALSE;					// nichts gefunden: OK
		return HRESULT_FROM_ERRCODE(RC);	// sonstiger Fehler
	}

bool iNext = true;
bool iRC = true;

	while (iNext && iRC) {
	long lKey;

		RC = (ErrCode)z_keyread (hPr, &lKey);
		if (RC != EC_OKAY) break;
		TX_ASSERT(0 != lKey);

	// nächsten Schlüssel suchen
		RC = (ErrCode)z_keynext (&dba, keyIndex);
		if (RC != EC_OKAY)
			iNext = false;

	// DB für Nutzer wieder einstellen
		{
		CKeyContext keyCtx;
		CActDB UserDB (ActDB.GetOldDB());

		// Enumeration
			iRC = SUCCEEDED(pFcn(lKey, dwData)) ? true : false;
			ActDB.ReActivate();		// diese DB wieder aktivieren
		}	
	}
	if (RC == WC_NOTFOUND) 
		RC = EC_OKAY;           // nichts mehr gefunden: OK

	return (EC_OKAY == RC) ? S_OK : HRESULT_FROM_ERRCODE(RC);
}

/////////////////////////////////////////////////////////////////////////////
// Suchen eines bestimmten Eintrages (über KurzText)
namespace {
	struct FINDENTRYDATA {
		HPROJECT m_hPr;
		long m_lTyp;
		LPCSTR m_pcItem;
		long *m_plCode;
	};
} // namespace

/*static*/
HRESULT CALLBACK CNativePbd::FindEntryCallback (INT_PTR lCode, UINT_PTR dwData)
{
	ASSERT(0L != dwData);

FINDENTRYDATA *pFED = (FINDENTRYDATA *)dwData;
CNativePbd *pEntry = NULL;

	switch (pFED ->m_lTyp) {
	case PBD_IDENT:
		TX_TRY(pEntry = new CNativePbdIdent (pFED -> m_hPr, lCode));
		break;
	
	case PBD_MERKMAL:
		TX_TRY(pEntry = new CNativePbdMerkmal (pFED -> m_hPr, lCode));
		break;

	case PBD_RELATION:
		TX_TRY(pEntry = new CNativePbdRelation (pFED -> m_hPr, lCode));
		break;

	default:
		return E_UNEXPECTED;
	}
	if (NULL == pEntry || !(*pEntry)) {
		DELETE_OBJ(pEntry);
		return E_UNEXPECTED;		// snh
	}

	if (!strcmp (pFED -> m_pcItem, pEntry -> GetKurzText())) {
		DELETE_OBJ(pEntry);
		*(pFED -> m_plCode) = lCode;
		return S_FALSE;		// gefunden, also aufhören
	}
	DELETE_OBJ(pEntry);
	return S_OK;	// weitermachen
}

/*static*/
HRESULT CNativePbd::FindEntry (HPROJECT hPr, long pbdTyp, LPCSTR pcName, long *plCode)
{
	TX_ASSERT(NULL != plCode);

FINDENTRYDATA FED;

	FED.m_hPr = hPr;
	FED.m_lTyp = pbdTyp;
	FED.m_pcItem = pcName;
	FED.m_plCode = plCode;

	*plCode = 0L;
	if (SUCCEEDED(EnumPBDData (hPr, pbdTyp, FindEntryCallback, (DWORD)&FED))) {
		if (0 == *plCode)	// nichts gefunden
			return HRESULT_FROM_ERRCODE(WC_NOTFOUND);
		return S_OK;
	}
	return E_FAIL;
}

/////////////////////////////////////////////////////////////////////////////
// Suchen aller Einträge mit identischem Kurztext
typedef HRESULT (CALLBACK *ENUMCODE)(INT_PTR lCode, UINT_PTR dwData);

namespace {
	struct FINDEQUALENTRIESDATA {
		HPROJECT m_hPr;
		long m_lTyp;
		LPCSTR m_pcItem;
		ENUMCODE m_pFcn;
		UINT_PTR m_dwData;
	};
} // namespace

/*static*/
HRESULT CALLBACK CNativePbd::FindEqualEntriesCallback (INT_PTR lCode, UINT_PTR dwData)
{
	ASSERT(0L != dwData);

FINDEQUALENTRIESDATA *pFED = (FINDEQUALENTRIESDATA *)dwData;
CNativePbd *pEntry = NULL;

	switch (pFED ->m_lTyp) {
	case PBD_IDENT:
		TX_TRY(pEntry = new CNativePbdIdent (pFED -> m_hPr, lCode, NULL, TRUE, FALSE));
		break;
	
	case PBD_MERKMAL:
		TX_TRY(pEntry = new CNativePbdMerkmal (pFED -> m_hPr, lCode, NULL, TRUE, FALSE));
		break;

	case PBD_RELATION:
		TX_TRY(pEntry = new CNativePbdRelation (pFED -> m_hPr, lCode, NULL, TRUE, FALSE));
		break;

	default:
		return E_UNEXPECTED;
	}
	if (NULL == pEntry || !(*pEntry)) {
		DELETE_OBJ(pEntry);
		return E_UNEXPECTED;		// snh
	}

	if (!strcmp (pFED -> m_pcItem, pEntry -> GetKurzText())) {
		DELETE_OBJ(pEntry);
		return (*pFED -> m_pFcn)(lCode, pFED -> m_dwData);		// eigentliche Enumeration
	}
	DELETE_OBJ(pEntry);
	return S_OK;	// weitermachen
}

/*static*/
HRESULT CNativePbd::EnumEqualEntries (
	HPROJECT hPr, long pbdTyp, LPCSTR pcName, HRESULT (CALLBACK *pFcn)(INT_PTR, UINT_PTR), UINT_PTR dwData)
{
FINDEQUALENTRIESDATA FED;

	FED.m_hPr = hPr;
	FED.m_lTyp = pbdTyp;
	FED.m_pcItem = pcName;
	FED.m_pFcn = pFcn;
	FED.m_dwData = dwData;
	return EnumPBDData (hPr, pbdTyp, FindEqualEntriesCallback, (UINT_PTR)&FED);
}

///////////////////////////////////////////////////////////////////////////////
// Konstruktoren für CNativePbdMerkmal 
CNativePbdMerkmal::CNativePbdMerkmal (HPROJECT hPr, BOOL fIssueError, BOOL fCorrectName) 
	: CNativePbd (hPr, PBD_MERKMAL) 
{
	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

	m_fSystem = false;
	m_fReadOnly = false;
	m_iMTyp = 0;
	m_lIdent = 0;

	if (FAILED(FInit(NULL, fIssueError, fCorrectName)))
		m_rgStatus = PBD_Invalid;
}

CNativePbdMerkmal::CNativePbdMerkmal (HPROJECT hPr, long lCode, LPCSTR lpkText, BOOL fIssueError, BOOL fCorrectName)
	: CNativePbd (hPr, PBD_MERKMAL, lCode) 
{
	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

	m_fSystem = false;
	m_fReadOnly = false;
	m_iMTyp = PBDFEATURETYPE_Object;		// erstmal ObjektMerkmal annehmen
	m_lIdent = 0;

// PBD-DB aktivieren
CActDB ActDB (m_hPr);

	if (!ActDB) {
		m_rgStatus = PBD_Invalid;
		return; // Fehler beim aktivieren
	}

// wenn der gesuchte Satz nicht existiert, dann gleich wieder raus
	if (FAILED(FInit(lpkText, fIssueError, fCorrectName)) || -1 == m_dbaSatz) {
		m_rgStatus = PBD_Invalid;
		return;
	}

short iMTyp = 0;

	mgetkm (&lCode, &iMTyp, &m_lIdent);
	TX_ASSERT(lCode == m_lCode);

	m_iMTyp = LOBYTE(iMTyp);		// nur niederwertiges Byte

	m_fSystem = m_iMTyp & PBDMERKMAL_SYSTEMFLAG ? true : false;
	m_iMTyp &= ~PBDMERKMAL_SYSTEMFLAG;

	m_fReadOnly = (iMTyp & PBDMERKMAL_READONLY) ? true : false;

// als Kleinbuchstaben übergeben
	m_iMTyp = tolower((unsigned char)m_iMTyp);
}

/////////////////////////////////////////////////////////////////////////////
// Liefert die vollständige Typinformation für dieses Merkmal
inline long GetHeaderLong (HPROJECT hPr, LPCSTR pcKey, long lDefault, int iBase)
{
char cbBuffer[_MAX_PATH];
trias_nativeheader::CDBHeader Hdr (hPr, pcKey);

	if ( SUCCEEDED( Hdr.GetHeaderEntry(cbBuffer, _countof(cbBuffer)) ) )
		return strtol (cbBuffer, NULL, iBase);

	return lDefault;
} 

DWORD CNativePbdMerkmal::GetFullType()
{
	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

DWORD dwType = isSystem() ? PBDFEATURETYPE_System : 0L;

	if (isReadOnly())
		dwType |= PBDFEATURETYPE_ReadOnly;

// feststellen, ob's der MCode für die Texte der Textobjekte ist
HPROJECT hPr = NULL;

	if (GetTargetProject (m_hPr, &hPr)) {
	long lMCode = GetHeaderLong (hPr, g_cbTextObjMCode, 99999100L, 10);

		if (lMCode == m_lCode)
			dwType |= PBDFEATURETYPE_TextFeature;
	}
	return dwType | m_iMTyp;
}

///////////////////////////////////////////////////////////////////////////////
// CNativePbdIdentifikator 
CNativePbdIdent::CNativePbdIdent (HPROJECT hPr, BOOL fIssueError, BOOL fCorrectName) 
	: CNativePbd (hPr, PBD_IDENT) 
{
	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

	m_fSystem  = false;
	m_fReadOnly = false;

	if (FAILED(FInit(NULL, fIssueError, fCorrectName)))
		m_rgStatus = PBD_Invalid;
}

CNativePbdIdent::CNativePbdIdent (HPROJECT hPr, long lCode, LPCSTR lpkText, BOOL fIssueError, BOOL fCorrectName) 
	: CNativePbd (hPr, PBD_IDENT, lCode) 
{
	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

	m_fSystem  = false;
	m_fReadOnly = false;

	if (FAILED(FInit(lpkText, fIssueError, fCorrectName))) 
		m_rgStatus = PBD_Invalid;
	else {
	// PBD-DB aktivieren
	CActDB ActDB (m_hPr);
	long lTyp = 0;

		mgetki (&lCode, &lTyp);
		TX_ASSERT(lCode == m_lCode);
		
		SetReadOnly (lTyp & PBDIDENTTYPE_ReadOnly);
		SetSystem (lTyp & PBDIDENTTYPE_System);
	}
}

// Destruktor
CNativePbdIdent::~CNativePbdIdent (void) 
{
	// nothing to do
}

///////////////////////////////////////////////////////////////////////////////
// Speichern einer BeschreibungsInfo in der PBD
HRESULT CNativePbdIdent::SaveInPBD (void) 
{
	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

	if (m_rgStatus != PBD_Modified) 
		return S_FALSE;

CActDB ActDB (m_hPr);
ErrCode RC;

	if (!ActDB)      // Fehler beim aktivieren der PBD
		return HRESULT_FROM_ERRCODE(EC_ACTIVATE);

// wenn der gesuchte Satz existiert, dann diesen löschen
	if (-1 != m_dbaSatz) {
	HRESULT hr = DeleteInPBD();	// alten Satz löschen

		if (FAILED(hr)) return hr;
	}

// neuen Eintrag aufbauen: IdentSatz
long lTyp = isSystem() ? PBDIDENTTYPE_System : 0;

	if (isReadOnly())
		lTyp |= PBDIDENTTYPE_ReadOnly;
	DBASSERTHR (mputki (lTyp, &m_dbaSatz));

	RETURN_FAILED_HRESULT(PutKurzText());
	RETURN_FAILED_HRESULT(PutLangText(PBD_IDENT));

	m_rgStatus = PBD_Unmodified;
	return RC;
}

///////////////////////////////////////////////////////////////////////////////
// Speichern einer BeschreibungsInfo in der PBD 
HRESULT CNativePbdMerkmal::SaveInPBD (void) 
{
	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

	if (m_rgStatus != PBD_Modified) 
		return S_FALSE;

CActDB ActDB (m_hPr);
ErrCode RC;

	if (!ActDB)      // Fehler beim aktivieren de PBD
		return HRESULT_FROM_ERRCODE(EC_ACTIVATE);

// wenn der gesuchte Satz existiert, dann diesen löschen
	if (-1 != m_dbaSatz) {
	HRESULT hr = DeleteInPBD();	// alten Satz löschen

		if (FAILED(hr)) return hr;
	}

// neuen Eintrag aufbauen: MerkmalsSatz
long lVon[2]; 
long lBis[2]; 
short mkTyp = isA();

	if (isSystem()) mkTyp |= PBDMERKMAL_SYSTEMFLAG;
	if (isReadOnly()) mkTyp |= PBDMERKMAL_READONLY;

	lVon[0] = MAXTEXTMERKMALLEN;
	lVon[1] = lBis[0] = lBis[1] = 0L;

	DBASSERTHR (mputkm (mkTyp, 1L, lVon, lBis, &m_dbaSatz));  
	RETURN_FAILED_HRESULT(PutKurzText());
	RETURN_FAILED_HRESULT(PutLangText(PBD_MERKMAL));

	m_rgStatus = PBD_Unmodified;
	return RC;
}

///////////////////////////////////////////////////////////////////////////////
// CNativePbdTextMerkmal 
CNativePbdTextMerkmal::CNativePbdTextMerkmal (HPROJECT hPr, long lCode, LPCSTR pcMText)
	: CNativePbdMerkmal (hPr, lCode)
{
	if (NULL != pcMText) 
		m_strText = pcMText;
}

CNativePbdTextMerkmal::~CNativePbdTextMerkmal (void)
{
}

// Kopie des MerkmalsTextes liefern
LPCSTR CNativePbdTextMerkmal::GetMerkmalsText (void) 
{
	if (0 == m_strText.size())
		return NULL;

	return m_strText.c_str();
}

// Zeigt, ob MerkmalsText für dieses Merkmal vorhanden ist -------------------
BOOL CNativePbdTextMerkmal::hasTextMerkmal (void) 
{
	return (m_strText.size() > 0) ? TRUE : FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// Konstruktoren für CNativePbdRelation 
CNativePbdRelation::CNativePbdRelation (HPROJECT hPr, BOOL fIssueError, BOOL fCorrectName) 
	: CNativePbd (hPr, PBD_RELATION) 
{
	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

	m_iRelTyp = 0;
	if (FAILED(FInit(NULL, fIssueError, fCorrectName)))
		m_rgStatus = PBD_Invalid;
}

CNativePbdRelation::CNativePbdRelation (HPROJECT hPr, long lCode, LPCSTR lpkText, BOOL fIssueError, BOOL fCorrectName)
	: CNativePbd (hPr, PBD_RELATION, lCode) 
{
	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

// PBD-DB aktivieren
CActDB ActDB (m_hPr);

	if (!ActDB) {// Fehler beim aktivieren
		m_rgStatus = PBD_Invalid;
		return;
	}

// wenn der gesuchte Satz nicht existiert, dann gleich wieder raus
	m_iRelTyp = 0;
	if (-1 == m_dbaSatz || FAILED(FInit(lpkText, fIssueError, fCorrectName))) {
		m_rgStatus = PBD_Invalid;
		return;
	}
	mgetkr (&lCode, &m_iRelTyp);    // RelTyp holen
	TX_ASSERT(lCode == m_lCode);

// als KleinBuchstaben übergeben        
	m_iRelTyp = tolower ((unsigned char)m_iRelTyp);
}


// Speichern einer BeschreibungsInfo in der PBD 
HRESULT CNativePbdRelation::SaveInPBD (void) 
{
	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

	if (m_rgStatus != PBD_Modified) 
		return S_FALSE;
	
CActDB ActDB (m_hPr);
ErrCode RC;

	if (!ActDB)      // Fehler beim aktivieren de PBD
		return HRESULT_FROM_ERRCODE(EC_ACTIVATE);

// wenn der gesuchte Satz existiert, dann diesen löschen
	if (-1 != m_dbaSatz) {
	HRESULT hr = DeleteInPBD();	// alten Satz löschen

		if (FAILED(hr)) return hr;
	}

// neuen Eintrag aufbauen: RelationsSatz
	DBASSERTHR (mputkr (m_iRelTyp, &m_dbaSatz));

	RETURN_FAILED_HRESULT(PutKurzText());
	RETURN_FAILED_HRESULT(PutLangText(PBD_RELATION));

	m_rgStatus = PBD_Unmodified;
	return RC;
}

///////////////////////////////////////////////////////////////////////////////
// Löschen eine IdentEintrages aus der PBD
HRESULT CNativePbdIdent::DeleteInPBD (void)
{
	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

CActDB ActDB (m_hPr);

	if (!ActDB)      // Fehler beim aktivieren de PBD
		return HRESULT_FROM_ERRCODE(EC_ACTIVATE);

// herauslöschen des alten Eintrages
ErrCode RC;
	
	if (-1 != m_dbaSatz) {
		DBASSERTHR (mdelete());
		m_dbaSatz = -1;
	}

	m_rgStatus = PBD_Modified;
	return EC_OKAY;
}

// Löschen eines MerkmalsEintrages aus der PBD 
HRESULT CNativePbdMerkmal::DeleteInPBD (void)
{
	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

CActDB ActDB (m_hPr);

	if (!ActDB)      // Fehler beim aktivieren de PBD
		return HRESULT_FROM_ERRCODE(EC_ACTIVATE);

// herauslöschen des alten Eintrages
ErrCode RC;

	if (-1 != m_dbaSatz) {
		DBASSERTHR (mdelete());
		m_dbaSatz = -1;
	}
	m_rgStatus = PBD_Modified;
	return EC_OKAY;
}

// Löschen eines RelationsEintrages aus der PBD 
HRESULT CNativePbdRelation::DeleteInPBD (void)
{
	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

CActDB ActDB (m_hPr);

	if (!ActDB)      // Fehler beim aktivieren de PBD
		return HRESULT_FROM_ERRCODE(EC_ACTIVATE);

// herauslöschen des alten Eintrages
ErrCode RC;

	if (-1 == m_dbaSatz) {
		DBASSERT (mdelete());
		m_dbaSatz = -1;
	}
	m_rgStatus = PBD_Modified;
	return EC_OKAY;
}

HRESULT CNativePbd::DeleteInPBD (void) { return S_OK; }      // Platzhalter
HRESULT CNativePbd::SaveInPBD (void) { return S_OK; }

///////////////////////////////////////////////////////////////////////////////
// Datenbankarbeit

// Einlesen des Kurztextes zu einem Identifikatorsatz 
HRESULT CNativePbd::mgetktall (char *pText, int iFileNo) 
{
DB_ADDR dba (m_hPr);
long RC;
long lPBDVersion = LocGetDBVersion (m_hPr);

// gesuchten Satz einlesen
	dba.file_no = iFileNo;
	dba.rec_no = m_dbaSatz;

	if (lPBDVersion <= PBDVERSION03000001) {
	struct desc_001 DB001Satz;

		__ReadHR (dba, DB001Satz);

	// Daten kopieren
		if (pText) {
			TX_ASSERT(TIsValidAddress(pText, TEXTLEN_001+1));
			strncpy (pText, DB001Satz.SText, TEXTLEN_001);
			pText[TEXTLEN_001] = '\0';
		}

	} else {
		TX_ASSERT(lPBDVersion >= PBDVERSION03000002);

	struct desc DBSatz;

		__ReadHR (dba, DBSatz);

	// Daten kopieren
		if (pText) {
			TX_ASSERT(TIsValidAddress(pText, TEXTLEN+1));
			strncpy (pText, DBSatz.SText, TEXTLEN);
			pText[TEXTLEN] = '\0';
		}
	}
	return S_OK;
} 

// Bestimmen der Laenge eines Langtextes in einem Beschreibungssatz der PBD
HRESULT CNativePbd::mgetlall (long *pLen, int iFileNo, int iFileNoNext) 
{
DB_ADDR dba (m_hPr), dbaF (m_hPr);
long RC;
long lNext;
long lPBDVersion = LocGetDBVersion (m_hPr);

	dba.rec_no = m_dbaSatz;
	dba.file_no = iFileNo;
	dbaF.file_no = iFileNoNext;

	if (lPBDVersion <= PBDVERSION03000001) {
	struct desc_001 DB001Satz;
	struct fdesc_001 DBF001Satz;

		__ReadHR (dba, DB001Satz);
		lNext = DB001Satz.Next;
		DB001Satz.Next = 0;	// Stringende sicher ausnullen

		*pLen = strlen (DB001Satz.LText);

		while (lNext != 0) {
			__ReadHR (dbaF, DBF001Satz);
			lNext = DBF001Satz.FNext;
			DBF001Satz.FNext = 0;	// Stringende sicher ausnullen
			*pLen += strlen (DBF001Satz.FLText);
		}

	} else {
		TX_ASSERT(lPBDVersion >= PBDVERSION03000002);

	struct desc DBSatz;
	struct fdesc DBFSatz;

		__ReadHR (dba, DBSatz);

		lNext = DBSatz.Next;
		DBSatz.Next = 0;	// Stringende sicher ausnullen

		*pLen = strlen (DBSatz.LText);

		while (lNext != 0) {
			dbaF.rec_no = lNext;
			__ReadHR (dbaF, DBFSatz);
			lNext = DBFSatz.FNext;
			DBFSatz.FNext = 0;	// Stringende sicher ausnullen
			*pLen += strlen (DBFSatz.FLText);
		}	
	}
	return S_OK;
}

// Einlesen eines Langtextes in einem Beschreibungssatz der PBD
HRESULT CNativePbd::mgettxall (char *pText, int iFileNo, int iFileNoNext) 
{
DB_ADDR dba (m_hPr), dbaF (m_hPr);
long RC;
long lNext;
int ReadLen = 0;
long lPBDVersion = LocGetDBVersion (m_hPr);

	dba.rec_no = m_dbaSatz;
	dba.file_no = iFileNo;
	dbaF.file_no = iFileNoNext;

	if (lPBDVersion <= PBDVERSION03000001) {
	struct desc_001 DB001Satz;
	struct fdesc_001 DBF001Satz;

		__ReadHR (dba, DB001Satz);
		lNext = DB001Satz.Next;
		DB001Satz.Next = 0;	// Stringende sicher ausnullen

		TX_ASSERT(TIsValidAddress(pText, strlen(DB001Satz.LText)));
		strcpy (pText, DB001Satz.LText);
		ReadLen = sizeof(DB001Satz.LText);

		while (lNext != 0) {
			__ReadHR (dbaF, DBF001Satz);
			lNext = DBF001Satz.FNext;
			DBF001Satz.FNext = 0;		// StringEnde sicher ausnullen

			TX_ASSERT(TIsValidAddress(pText, strlen(DBF001Satz.FLText)));
			strcpy (&pText[ReadLen], DBF001Satz.FLText);
			ReadLen += sizeof(DBF001Satz.FLText);
		}

	} else {
		TX_ASSERT(lPBDVersion >= PBDVERSION03000002);

	struct desc DBSatz;
	struct fdesc DBFSatz;

		__ReadHR (dba, DBSatz);
		lNext = DBSatz.Next;
		DBSatz.Next = 0;	// Stringende sicher ausnullen
	
		TX_ASSERT(TIsValidAddress(pText, strlen(DBSatz.LText)));
		strcpy (pText, DBSatz.LText);
		ReadLen = sizeof(DBSatz.LText);

		while (lNext != 0) {
			dbaF.rec_no = lNext;
			__ReadHR (dbaF, DBFSatz);
			lNext = DBFSatz.FNext;
			DBFSatz.FNext = 0;		// StringEnde sicher ausnullen

			TX_ASSERT(TIsValidAddress(pText, strlen(DBFSatz.FLText)));
			strcpy (&pText[ReadLen], DBFSatz.FLText);
			ReadLen += sizeof(DBFSatz.FLText);
		}
	}
	return (ReadLen > 0) ? S_OK : S_FALSE;
}

// Die Struktur der Beschreibungssätze (Identifikator-, Merkmals- und 
// Relations-Beschreibungssätze) in Bezug auf Kurz- und Langtext ist identisch.
// Es wird daher an dieser Stelle der Einfachheit halber ein wenig getrickst.

// KurzText schreiben
HRESULT CNativePbd::mputktall (LPCSTR pcText, int iFileNo) 
{
DB_ADDR dba (m_hPr);
long RC;
long lPBDVersion = LocGetDBVersion (m_hPr);

	dba.file_no = iFileNo;
	dba.rec_no = m_dbaSatz;

// KurzText einkopieren
	if (lPBDVersion <= PBDVERSION03000001) {
	struct desc_001 DB001Satz;

		__ReadHR (dba, DB001Satz);
		strncpy (DB001Satz.SText, pcText, TEXTLEN_001);
		__WriteHR(dba, DB001Satz);

	} else {
		TX_ASSERT(lPBDVersion >= PBDVERSION03000002);

	struct desc DBSatz;

		__ReadHR (dba, DBSatz);
		strncpy (DBSatz.SText, pcText, TEXTLEN);
		__WriteHR(dba, DBSatz);
	}
	return S_OK;
}

// LangText schreiben
HRESULT CNativePbd::mputtxall (const char *pcText, int iFileNo, int iFileNoNext) 
{
DB_ADDR dbaF(m_hPr), dba(m_hPr);
struct desc DBSatz;
struct desc_001 DB001Satz;
ErrCode RC;
int iLen, iWrittenLen;
long lPBDVersion = LocGetDBVersion (m_hPr);
int iTextLen = 0;

// wenn Text nicht gegeben ist, dann wieder raus
	if (NULL == pcText) 
		return S_FALSE;

	dba.file_no = iFileNo;
	dba.rec_no = m_dbaSatz;

// erste 76 Bytes des LangTextes einkopieren
	if (lPBDVersion <= PBDVERSION03000001) {
	// Satz aus PBD einlesen
		__ReadHR (dba, DB001Satz);

		strncpy (DB001Satz.LText, pcText, sizeof(DB001Satz.LText));
		DB001Satz.Next = 0;
		iTextLen = 120;

		__WriteHR (dba, DB001Satz);
	} else {
		TX_ASSERT(lPBDVersion >= PBDVERSION03000002);

	// Satz aus PBD einlesen
		__ReadHR (dba, DBSatz);

		strncpy (DBSatz.LText, pcText, sizeof(DBSatz.LText));
		DBSatz.Next = 0;
		iTextLen = 136;
		__WriteHR (dba, DBSatz);
	}

	iLen = strlen (pcText);
	iWrittenLen = (iLen > 76) ? 76 : iLen;

long lPrev = 0;
bool fFirst = true;

	dbaF.file_no = iFileNoNext;			// FortsetzungsSatz
	while (iLen > iWrittenLen) {
	// weitere Fortsetzungssätze anlegen

		if (lPBDVersion <= PBDVERSION03000001) {
		struct fdesc_001 DBF001Satz;	// FortSetzungsSatz

			strncpy (DBF001Satz.FLText, &pcText[iWrittenLen], iTextLen);
			DBF001Satz.FNext = 0;
			__NewHR (dbaF, DBF001Satz);

		long lCurr = dbaF.rec_no;

			if (fFirst) {
				DB001Satz.Next = lCurr;
				__WriteHR(dba, DB001Satz);
				fFirst = false;
			} else {
				TX_ASSERT(0 != lPrev);

				dbaF.rec_no = lPrev;
				__ReadHR(dbaF, DBF001Satz);
				DBF001Satz.FNext = lCurr;
				__WriteHR(dbaF, DBF001Satz);
			}
			lPrev = lCurr;

		} else {
		struct fdesc DBFSatz;			// FortSetzungsSatz

			strncpy (DBFSatz.FLText, &pcText[iWrittenLen], iTextLen);
			DBFSatz.FNext = 0;
			__NewHR (dbaF, DBFSatz);

		long lCurr = dbaF.rec_no;

			if (fFirst) {
				DBSatz.Next = lCurr;
				__WriteHR(dba, DBSatz);
				fFirst = false;
			} else {
				TX_ASSERT(0 != lPrev);

				dbaF.rec_no = lPrev;
				__ReadHR(dbaF, DBFSatz);
				DBFSatz.FNext = lCurr;
				__WriteHR(dbaF, DBFSatz);
			}
			lPrev = lCurr;
		}

	// Länge des behandelten Strings berechnen
		iWrittenLen = min (iWrittenLen + iTextLen, iLen);
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// IdentifikatorSätze
HRESULT CNativePbdIdent::mdelete (long lSatz) 
{
	if (0 == lSatz)
		lSatz = m_dbaSatz;

ErrCode RC;
DB_ADDR dbaIDL (m_hPr);
long lNext;
long lPBDVersion = LocGetDBVersion (m_hPr);

	dbaIDL.file_no = MID;
	dbaIDL.rec_no = lSatz;

	if (lPBDVersion <= PBDVERSION03000001) {
	struct mid_001 MID001Satz;

		__ReadHR (dbaIDL, MID001Satz);
		lNext = MID001Satz.zntxti;
		__DisposeHR (dbaIDL, mid_001());
	} 
	else {
		TX_ASSERT(lPBDVersion >= PBDVERSION03000002);

	struct mid MIDSatz;

		__ReadHR (dbaIDL, MIDSatz);
		lNext = MIDSatz.zntxti;
		__DisposeHR (dbaIDL, mid());
	}

// Satz mit TextFolgeSätzen freigeben 
	DBASSERTHR (FreeText (MIF, lNext));
	return S_OK;
}

// Alle Flags dieses Identifikators liefern
DWORD CNativePbdIdent::GetFullType()
{
	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

DWORD dwType = isSystem() ? PBDIDENTTYPE_System : 0L;

	if (isReadOnly())
		dwType |= PBDIDENTTYPE_ReadOnly;
	
	return dwType;
}

// Finden des Beschreibungssatzes für einen Identifikator 
HRESULT CNativePbdIdent::mfind (long lCode, long *pSatz)
{
DB_ADDR dbaIDL (m_hPr);
long RC;

	dbaIDL.file_no = MID;
	DBASSERTHR (z_keyfind (&dbaIDL, IDS, &lCode));
	*pSatz = dbaIDL.rec_no;
	return S_OK;
}

// Einlesen der BeschreibungsInformation für einen Identifikator
HRESULT CNativePbdIdent::mgetki (long *plIdent, long *piTyp)
{
DB_ADDR dbaMID (m_hPr);
long RC;
long lPBDVersion = LocGetDBVersion (m_hPr);

	dbaMID.file_no = MID;
	dbaMID.rec_no = m_dbaSatz;

// Beschreiben der geforderten Parameter (Resultat)
struct mid MIDSatz;

	__ReadHR (dbaMID, MIDSatz);
	if (NULL != piTyp) {
		if (lPBDVersion >= PBDVERSION0500000C) 
			*piTyp = MIDSatz.ityp;
		else
			*piTyp = 0;		// defaultwert
	}

	if (NULL != plIdent) 
		*plIdent = MIDSatz.ids;
	return S_OK;
}

// Schreiben/Modifizieren eines Identsatzes
HRESULT CNativePbdIdent::mputki (long iTyp, long *plRecNo) 
{
DB_ADDR dbaMID (m_hPr);
ErrCode RC;
long lPBDVersion = LocGetDBVersion (m_hPr);

	dbaMID.file_no = MID;
	*plRecNo = 0;	// für alle Fälle

	if (0 != m_lCode) {
	ErrInstall EI (WC_NOTFOUND);
	
		if ((RC = (ErrCode)z_keyfind (&dbaMID, IDS, &m_lCode)) == S_OKAY) {
		// Satz existiert schon

			DBASSERT (mdelete (dbaMID.rec_no));		// alten Satz löschen

		} else if (RC != S_NOTFOUND) // Fehler beim suchen des IDSatzes
			return HRESULT_FROM_ERRCODE(RC);		
	}

	if (lPBDVersion <= PBDVERSION03000001) {
	struct mid_001 MID001Satz;

	// neuen Satz generieren
		MID001Satz.ids = m_lCode;
		__NewHR (dbaMID, MID001Satz);
	
	} else {
		TX_ASSERT(lPBDVersion >= PBDVERSION03000002);

	struct mid MIDSatz;

	// neuen Satz generieren
		MIDSatz.ids = m_lCode;
		if (lPBDVersion >= PBDVERSION0500000C)
			MIDSatz.ityp = iTyp;
		__NewHR (dbaMID, MIDSatz);
	}

// Resultat setzen
	*plRecNo = dbaMID.rec_no;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// MerkmalsSätze
HRESULT CNativePbdMerkmal::mdelete (long lSatz) 
{
	if (0 == lSatz)
		lSatz = m_dbaSatz;

long RC;
DB_ADDR dbaMMK (m_hPr);
long lNext;
long iWBis0, iWBis1;
short iTyp;
long lPBDVersion = LocGetDBVersion (m_hPr);

	dbaMMK.file_no = MMK;
	dbaMMK.rec_no = lSatz;

	if (lPBDVersion <= PBDVERSION03000001) {
	struct mmk_001 MMK001Satz;

		__ReadHR (dbaMMK, MMK001Satz);
		lNext = MMK001Satz.zntxtm;
		iTyp = MMK001Satz.mtyp[0];
		iWBis0 = MMK001Satz.wbis.iwbis[0];
		iWBis1 = MMK001Satz.wbis.iwbis[1];

	} else {
		TX_ASSERT(lPBDVersion >= PBDVERSION03000002);

	struct mmk MMKSatz;

		__ReadHR (dbaMMK, MMKSatz);
		lNext = MMKSatz.zntxtm;
		iTyp = MMKSatz.mtyp[0];
		iWBis0 = MMKSatz.wbis.iwbis[0];
		iWBis1 = MMKSatz.wbis.iwbis[1];
	}

// Satz mit TextFolgeSätzen und evtl. MerkmalsWertFolgesätzen freigeben 
	if (iTyp == 'i' && iWBis0 == -1) {
	// solange MerkmalswertFolgesätze vorhanden 
	DB_ADDR dbaMMW (m_hPr);
	long lNextM = iWBis1;			// erster WerteFolgeSatz

		dbaMMW.file_no = MMW;

		if (lPBDVersion <= PBDVERSION03000001) {
		struct mmw_001 MMW001Satz;

			while (lNextM != 0) {
				dbaMMW.rec_no = lNextM;
				__ReadHR (dbaMMW, MMW001Satz);
	
			// TextFolgeSätze freigeben
				DBASSERTHR (FreeText (MMF, MMW001Satz.zntxtw));

			// nächster WerteFolgeSatz
				lNextM = MMW001Satz.znwert;
				__DisposeHR (dbaMMW, MMW001Satz);		// Satz freigeben
			}
		} else {
			TX_ASSERT(lPBDVersion >= PBDVERSION03000002);

		struct mmw MMWSatz;

			while (lNextM != 0) {
				dbaMMW.rec_no = lNextM;
				__ReadHR (dbaMMW, MMWSatz);
	
			// TextFolgeSätze freigeben
				DBASSERTHR (FreeText (MMF, MMWSatz.zntxtw));

			// nächster WerteFolgeSatz
				lNextM = MMWSatz.znwert;
				__DisposeHR (dbaMMW, MMWSatz);		// Satz freigeben
			}
		}

	}

	if (lPBDVersion <= PBDVERSION03000001) {
		__DisposeHR (dbaMMK, mmk_001());
	}
	else {
		__DisposeHR (dbaMMK, mmk());
	}
	DBASSERTHR (FreeText (MKF, lNext));
	return S_OK;
}

// Finden des Beschreibungssatzes für einen MerkmalsCode 
HRESULT CNativePbdMerkmal::mfind (long lCode, long *pSatz) 
{
DB_ADDR dbaMMK (m_hPr);
long RC; 

	dbaMMK.file_no = MMK;
	DBASSERTHR (z_keyfind (&dbaMMK, MKS, &lCode));
	*pSatz = dbaMMK.rec_no;
	return S_OK;
}

HRESULT CNativePbdMerkmal::mputkm (
	short MTyp, long WF, long *von, long *bis, long *plRecNo) 
{
DB_ADDR dbaMMK (m_hPr);
long RC;
long lPBDVersion = LocGetDBVersion (m_hPr);

	dbaMMK.file_no = MMK;
	*plRecNo = 0;	// für alle Fälle

	if (0 != m_lCode) {
	ErrInstall EI (WC_NOTFOUND);	// Fehler unterdrücken
	
		if ((RC = z_keyfind (&dbaMMK, MKS, &m_lCode)) == S_OKAY) {
		// Satz existiert schon
	
			DBASSERTHR (mdelete (dbaMMK.rec_no));	// alten Satz löschen
		} else if (RC != S_NOTFOUND)	// Fehler beim suchen des MKSatzes
			return HRESULT_FROM_ERRCODE(RC);		
	}
	
	if (lPBDVersion <= PBDVERSION03000001) {
	// neuen Satz generieren
	struct mmk_001 MMK001Satz;

		memset (&MMK001Satz, '\0', sizeof(mmk_001));
		MMK001Satz.mks = m_lCode;
		MMK001Satz.wfakm = WF;
		MMK001Satz.mtyp[0] = (char)MTyp;
		memcpy (&MMK001Satz.wvon, von, sizeof(long)*2);
		memcpy (&MMK001Satz.wbis, bis, sizeof(long)*2);
		__NewHR (dbaMMK, MMK001Satz);
	
	} else {
		TX_ASSERT(lPBDVersion >= PBDVERSION03000002);

	// neuen Satz generieren
	struct mmk MMKSatz;

		memset (&MMKSatz, '\0', sizeof(mmk));
		MMKSatz.mks = m_lCode;
		MMKSatz.wfakm = WF;
		memcpy (MMKSatz.mtyp, &MTyp, sizeof(short));
		memcpy (&MMKSatz.wvon, von, sizeof(long)*2);
		memcpy (&MMKSatz.wbis, bis, sizeof(long)*2);
		__NewHR (dbaMMK, MMKSatz);
	}

// Resultat setzen
	*plRecNo = dbaMMK.rec_no;
	return S_OK;
}

// Einlesen der BeschreibungsInformation für einen MerkmalsCode
HRESULT CNativePbdMerkmal::mgetkm (
	long *pMCode, short *pMTyp, INT_PTR *plIdent, long *pWF, long *pVon, long *pBis, long *pNext) 
{
DB_ADDR dbaMMK (m_hPr);
long RC;
long lPBDVersion = LocGetDBVersion (m_hPr);

	dbaMMK.file_no = MMK;
	dbaMMK.rec_no = m_dbaSatz;

	if (lPBDVersion <= PBDVERSION03000001) {
	struct mmk_001 MMK001Satz;

		__ReadHR (dbaMMK, MMK001Satz);

	// Beschreiben der geforderten Parameter (Resultat)
		if (pMTyp) *pMTyp = (char)MMK001Satz.mtyp[0];
		if (pWF) *pWF = MMK001Satz.wfakm;
		if (pMCode) *pMCode = MMK001Satz.mks;
		if (pVon) memcpy (pVon, &MMK001Satz.wvon, sizeof(long)*2);
		if (pBis) memcpy (pBis, &MMK001Satz.wbis, sizeof(long)*2);
		if (pNext) {
			if (tolower(MMK001Satz.mtyp[0]) != 'f') 
				*pNext = MMK001Satz.wbis.iwbis[1];
			else
				*pNext = 0;	// kein FolgeSatz
		}
		if (plIdent) *plIdent = 0;

	} else {
	
		TX_ASSERT(lPBDVersion >= PBDVERSION03000002);

	struct mmk MMKSatz;

		__ReadHR (dbaMMK, MMKSatz);

	// Beschreiben der geforderten Parameter (Resultat)
		if (pMTyp) memcpy (pMTyp, MMKSatz.mtyp, sizeof(short));
		if (pWF) *pWF = MMKSatz.wfakm;
		if (pMCode) *pMCode = MMKSatz.mks;
		if (pVon) memcpy (pVon, &MMKSatz.wvon, sizeof(long)*2);
		if (pBis) memcpy (pBis, &MMKSatz.wbis, sizeof(long)*2);
		if (pNext) {
			if (tolower(MMKSatz.mtyp[0]) != 'f') 
				*pNext = MMKSatz.wbis.iwbis[1];
			else
				*pNext = 0;	// kein FolgeSatz
		}

		if (plIdent) {
			if (lPBDVersion >= PBDVERSION0500000D)
				*plIdent = MMKSatz.ident;
			else
				*plIdent = 0;
		}
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// RelationsSätze
HRESULT CNativePbdRelation::mdelete (long lSatz) 
{
	if (0 == lSatz)
		lSatz = m_dbaSatz;

long RC;
DB_ADDR dbaREL (m_hPr);
long lNext;
long lPBDVersion = LocGetDBVersion (m_hPr);

	dbaREL.file_no = MRL;
	dbaREL.rec_no = lSatz;

	if (lPBDVersion <= PBDVERSION03000001) {
	struct mrl_001 MRL001Satz;

		__ReadHR (dbaREL, MRL001Satz);
		lNext = MRL001Satz.zntxtr;

	// Satz mit TextFolgeSätzen freigeben 
		__DisposeHR (dbaREL, MRL001Satz);
	} 
	else {
		TX_ASSERT(lPBDVersion >= PBDVERSION03000002);

	struct mrl MRLSatz;

		__ReadHR(dbaREL, MRLSatz);
		lNext = MRLSatz.zntxtr;

	// Satz mit TextFolgeSätzen freigeben 
		__DisposeHR (dbaREL, MRLSatz);
	}

	DBASSERTHR (FreeText (MRF, lNext));
	return S_OK;
}

// Finden des Beschreibungssatzes für eine Relation 
HRESULT CNativePbdRelation::mfind (long lCode, long *pSatz) 
{
DB_ADDR dbaMRL (m_hPr);
long RC;

	dbaMRL.file_no = MRL;
	DBASSERTHR (z_keyfind (&dbaMRL, PRIREL, &lCode));
	*pSatz = dbaMRL.rec_no;
	return S_OK;
}

HRESULT CNativePbdRelation::mputkr (short reltyp, long *plRecNo) 
{
DB_ADDR dbaMRL (m_hPr);
long RC;
long lPBDVersion = LocGetDBVersion (m_hPr);

	dbaMRL.file_no = MRL;
	*plRecNo = 0;	// für alle Fälle

	if (0 != m_lCode) {
	ErrInstall EI (WC_NOTFOUND);
	
		if ((RC = z_keyfind (&dbaMRL, PRIREL, &m_lCode)) == S_OKAY) {
		// Satz existiert schon
		
			DBASSERT (mdelete (dbaMRL.rec_no));	// alten Satz löschen
		} else if (RC != S_NOTFOUND)
		// Fehler beim Suchen des RelSatzes
			return HRESULT_FROM_ERRCODE(RC);
	}
	
	if (lPBDVersion <= PBDVERSION03000001) {
	struct mrl_001 MRL001Satz;

	// neuen Satz generieren
		MRL001Satz.prirel = m_lCode;
		MRL001Satz.reltyp = reltyp;
		__NewHR (dbaMRL, MRL001Satz);

	} else {
		TX_ASSERT(lPBDVersion >= PBDVERSION03000002);

	struct mrl MRLSatz;

	// neuen Satz generieren
		MRLSatz.prirel = m_lCode;
		MRLSatz.reltyp = reltyp;
		__NewHR (dbaMRL, MRLSatz);
	}

// Resultat setzen
	*plRecNo = dbaMRL.rec_no;
	return S_OK;
}

// Einlesen der BeschreibungsInformationen zu einer Relationsbeschreibung 
HRESULT CNativePbdRelation::mgetkr (long *pRCode, short *pRTyp) 
{
DB_ADDR dbaMRL (m_hPr);
long RC;
long lPBDVersion = LocGetDBVersion (m_hPr);

// gesuchten Satz einlesen
	dbaMRL.file_no = MRL;
	dbaMRL.rec_no = m_dbaSatz;

	if (lPBDVersion <= PBDVERSION03000001) {
	struct mrl_001 MRL001Satz;

		__ReadHR (dbaMRL, MRL001Satz);

	// Daten kopieren
		if (pRCode) *pRCode = MRL001Satz.prirel;
		if (pRTyp) *pRTyp = MRL001Satz.reltyp;
	
	} else {

		TX_ASSERT(lPBDVersion >= PBDVERSION03000002);

	struct mrl MRLSatz;

		__ReadHR (dbaMRL, MRLSatz);

	// Daten kopieren
		if (pRCode) *pRCode = MRLSatz.prirel;
		if (pRTyp) *pRTyp = MRLSatz.reltyp;
	}
	return S_OK;
} 

/////////////////////////////////////////////////////////////////////////////
// DefaultKText Ident erzeugen
LPCSTR CNativePbdIdent::MakeDefaultName (LPSTR pBuffer, int iLen)
{
	return CNativePbd::MakeDefaultName (IDS_DEFAULTIDENTKTEXT, pBuffer, iLen); 
}

// DefaultKText für Merkmal erzeugen
LPCSTR CNativePbdMerkmal::MakeDefaultName (LPSTR pBuffer, int iLen)
{
	return CNativePbd::MakeDefaultName (IDS_DEFAULTMERKMALKTEXT, pBuffer, iLen); 
}

// DefaultKText für Relation erzeugen
LPCSTR CNativePbdRelation::MakeDefaultName (LPSTR pBuffer, int iLen)
{
	return CNativePbd::MakeDefaultName (IDS_DEFAULTRELATIONKTEXT, pBuffer, iLen); 
}

LPCSTR CNativePbd::MakeDefaultName (UINT uiResID, LPSTR pBuffer, int iLen)
{
	if (m_strKurzText.size() > 0)
		return m_strKurzText.c_str();

char cbBuffer[TEXTLEN+1];

	if (!::LoadString (g_hInstance, uiResID, cbBuffer, sizeof(cbBuffer))) {
		TX_ASSERT(FALSE);
		return m_strKurzText.c_str();
	}

char cbOut[_MAX_PATH];

	wsprintf (cbOut, cbBuffer, m_lCode);
	if (NULL != pBuffer) {
		TX_ASSERT(TIsValidAddress(pBuffer, iLen));
		TX_ASSERT(iLen <= sizeof(cbOut));

		strncpy (pBuffer, cbOut, iLen-1);
		pBuffer[iLen-1] = '\0';
	}
	m_strKurzText = cbOut;
	return m_strKurzText.c_str();
}

} // namespace trias_nativepbd
