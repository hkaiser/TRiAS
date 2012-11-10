// Diverse Hilfsfunktionen ----------------------------------------------------
// File KONSUTIL.CXX

#include "trias02p.hxx"

#include <dbaddr.hxx>

#include "trias02.h"

#include "konssatz.hxx"
#include "kons.hxx"
#include "kroutins.hxx"

extern char g_pDLLName[260];	// ModuleName

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// Testen und Korrigieren einer Koordinate ------------------------------------
enum CoordTyp {		// getesteter KoordinatenTyp
	CT_XCoord,
	CT_YCoord,
};

#define MAXKOORD 	1073741824L 

inline bool isValidCoord (long k) { return (k >= 0 && k < MAXKOORD); }

inline void CorrectCoord (long &x) 
{
	if (x < 0) x = 0;
	if (x > MAXKOORD) x = MAXKOORD;
}

bool ValidateCoord (long x, CoordTyp iCT)
{
	if (!isValidCoord (x)) 
		return (ErrCode)db_error (WC_BADCOORD, RC_TestCoords, &iCT) != EC_CORRECTED;

return false;	// Kordinate ist gültig
}

// Testen eines KoordinatenPaares ---------------------------------------------
ERRHANDLERFUNC ERBadCoord;

ErrCode CKonsistenzTestKontext :: TestCoords (long &x, long &y) 
{
// Koordinaten Testen
ErrInstall BadCoord (WC_BADCOORD, ERBadCoord, this);

// X-Koordinate wird getestet
bool XisInvalid = false;

	SetField (&x);
	XisInvalid = ValidateCoord (x, CT_XCoord);

// Y - Koordinate wwird getestet
bool YisInvalid = false;

	SetField (&y);
	YisInvalid = ValidateCoord (y, CT_YCoord);

return (XisInvalid || YisInvalid) ? WC_BADCOORD : EC_OKAY;
}


// Fehlerbehandlung bei falschen Koordinaten ----------------------------------
int ERBadCoord (int EC, int RC, ...)
{
va_list locList;
CKonsistenzTestKontext *pKTK;
CoordTyp *pCT;

	va_start (locList, RC);
	pCT = va_arg (locList, CoordTyp *);
	pKTK = va_arg (locList, CKonsistenzTestKontext *);
	va_end (locList);

	if (pKTK == NULL || pCT == NULL)
		return WC_RETURN;	// StandardFehlerBehandlung rufen

	if (!(~(KTDDiagnose|KTDDeepDiagnose) & pKTK -> DStatus()))
		return EC;

CSatzKontext *pMe = pKTK -> GetMe();

	if (pMe == NULL) return WC_RETURN;	// StandardFehlerBehandlung rufen

// Entschlüsselung des getesteten KoordinatenTyps
char cCoordTyp = ' ';

	switch (*pCT) {
	case CT_XCoord:	
		cCoordTyp = 'X'; break;

	case CT_YCoord: 
		cCoordTyp = 'Y'; break;

	default:
		TX_ASSERT(false);
		break;
	}

// generieren und ausgeben der Fehlermeldung
char outBuff[128];
char cbBuffer[64];
ResourceFile RF (g_pDLLName);

	wsprintf (outBuff, ResString (ResID (IDS_KONSBADCOORD, &RF), 120), cCoordTyp, 
		  ResString (ResID (pKTK -> TStatus(), &RF), 10).Addr(),
		  pKTK -> ObjNr(), pKTK -> ListName(pMe -> FileNo(), cbBuffer), 
		  pMe -> RecNo());

	if (pKTK -> DStatus() & KTDProtocol)
		pKTK -> Out (outBuff);

// Wenn repariert werden soll
	if (pKTK -> DStatus() & KTDRepair) {
	// erstmal nachfragen
		if (pKTK -> DStatus() & KTDQueryCorrection) {
			if (!KonsErrorWindow (outBuff))
				return EC;
		}

	// Koordinate Korrigieren und Satz wegschreiben
		CorrectCoord (*(long *)(pKTK -> GetField()));

		if (pMe -> KWrite() != EC_OKAY)		// Satz wegschreiben
			return pMe -> RC();
		return EC_CORRECTED;
	}

return EC;
}


// Testen einer allgemeinen Verbindungskette ----------------------------------
inline void SwabPtrs (CVerbKontext *&pP1, CVerbKontext *&pP2)
{
CVerbKontext *pTmp = pP2;

	pP2 = pP1; 
	pP1 = pTmp;
}

// Die Funktion TestLink testet eine beliebige SatzKette in der Datei iFileNo, 
// wobei lFirst die Referenz auf den Anfang (Aufhänger) dieser Kette darstellt,
// GWProc liefert eine Referenz auf den eigentlichen 'Wert' eines Verbindungs-
// satzes, GLProc eine Referenz auf den Verkettungszeiger eines Verbindungs-
// satzes, lWert ist der zu suchende Wert, bei dem die Analyse der Kette
// beendet wird (optional, default = -1) und TLProc eine Funktion, die für 
// jeden erfolgreich gelesenen Satz der Verbindungskette gerufen wird.
ErrCode CKonsistenzTestKontext::TestLink (short iFileNo, long &lFirst, long lWert,
					    GETWERTPROC GWProc, GETLINKPROC GLProc,
					    TESTLINKPROC TLProc)
{
	if (VERSION0500000F <= DB().GetDBVersion()) {
		if (VIO_OLD == iFileNo) {
			TX_ASSERT(DefGetWert == GWProc);
			TX_ASSERT(DefGetLink == GLProc);
			TX_ASSERT(NULL == TLProc);

			GWProc = VIOGetWert;
			GLProc = VIOGetLink;
		} else if (VMO_OLD == iFileNo) {
			TX_ASSERT(DefGetWert == GWProc);
			TX_ASSERT(DefGetLink == GLProc);
			TX_ASSERT(NULL == TLProc);

			GWProc = VMOGetWert;
			GLProc = VMOGetLink;
		}
	}

CVerbKontext V1 (iFileNo, lFirst, *this);
CVerbKontext V2 (iFileNo, 0, *this);
CVerbKontext *pV1 = &V1;
CVerbKontext *pV2 = &V2;
ErrCode RC = EC_OKAY;
long *pData;
bool fFound = false;

	do {
	// laufenden Satz einlesen
		if ((RC = pV1 -> KRead()) != EC_OKAY) {
			if (RC == EC_CORRECTED) 
				break;	// Fehler behoben: Ende der Kette
			return RC;
		}

	// TestLinkProc für jeden gelesenen Verbindungssatz rufen
		if (TLProc) RC = TLProc (*this, pV1);

	// Eingelesene Daten holen
		pData = (long *)pV1 -> GetData();

	// Testen, ob gefunden
		if (lWert != -1 && GWProc(pData) == lWert) {
			if (!(KTDDeepDiagnose & DStatus()))
				return EC_OKAY;				// gefunden und nicht weitersuchen, OK
			if (fFound)						// mehrfach in rückverkettung vertreten
				return (ErrCode)db_error (EC_DUPLLINK, RC_TestLink, &lWert);
			fFound = true;
		}

	// Testen, ob Ende der Verbindungskette
	long &lLink = GLProc (pData);

		if (lLink == 0) break;

	// nächster Satz
		SetField (&lLink);		// hot point
		SetBrother();			// ist jetzt Vorgänger

		pV2 -> RecNo() = lLink;
		SwabPtrs (pV1, pV2);
	} while (true);

// inhaltlicher Fehler, wenn Satz da gefunden wurde
	if (lWert != -1 && !fFound) 
		RC = (ErrCode)db_error (EC_BADLINK, RC_TestLink, &lWert);

	return RC;
}

// Routine, die den schlechteren der beiden übergebenen FehlerCodes auswählt --
ErrCode BadestRC (ErrCode RC1, ErrCode RC2)
{
// wenn einer der beiden ok ist, dann ist der andere maximal gleich gut
	if (RC1 == EC_OKAY) return RC2;
	if (RC2 == EC_OKAY) return RC1;

// wenn einer der beiden korrigiert ist, dann den anderen liefern
	if (RC1 == EC_CORRECTED) return RC2;
	if (RC2 == EC_CORRECTED) return RC1;

// wenn einer der beiden eine Warnung ist, dann den anderen liefern
	if ((short)RC1 > 0) return RC2;
	if ((short)RC2 > 0) return RC1;

// ansonsten ist's egal, wir liefern den ersten
return RC1;
}


// Anzeige einer Messagebox und Abfrage, ob Fehler korrigiert werden soll
bool KonsErrorWindow (LPCSTR cbOutBuff)
{
ResourceFile RF (g_pDLLName);
ResString resCap (ResID (IDS_KONSCAPTION, &RF), 50);
ResString resText (ResID (IDS_KONSQUERYTEXT, &RF), 128);
char cbOut[_MAX_PATH];

	wsprintf (cbOut, resText, cbOutBuff);

int iRes = MessageBox (__hWndM, cbOut, resCap, MB_APPLMODAL|MB_YESNO|MB_ICONQUESTION);

	return (IDYES == iRes) ? true : false;
}
