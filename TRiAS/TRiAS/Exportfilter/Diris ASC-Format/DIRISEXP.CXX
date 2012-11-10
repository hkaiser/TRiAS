// Routinen zum Schreiben des DIRIS-Austauschformates -------------------------
// File: DIRISASC.CXX

#include "stdafx.h"
#include "DirisASCImpl.h"

#include <string.h>
#include <fcntl.h>
#include <io.h>
#include <ctype.h>
#include <stdlib.h>

#include <trias01m.hxx>
#include <versions.h>
#include <risdb.h>

//#include <resstrg.h>
//#include <ristypes.hxx>

//#include "dirisexp.hxx"

#if !defined(HUGE)
#if defined(WIN32)
#define HUGE
#else
#define HUGE	__huge
#endif
#endif

#define GUID_CCH	39

// lokale FunktionsPrototypen
extern "C" char * PASCAL DtoAFlt (char *, char *, double);

static ErrCode DirisAscExportMerkmale (int fh, MFELD *MF);
static ErrCode DirisAscExportGeometrie (int fh, GSTRUCT &GS);
static ErrCode DirisAscExportRelationen (int fh, RSTRUCT *pRS);
static ErrCode DirisAscExportLine (int fh, char cTyp, const char *lpStr = NULL);
static ErrCode DirisAscExportEinMerkmal (int fh, short iMTyp, long lMCode, LPCTSTR pText);

static long lUIdent = -1L;
static short iFirstData = FALSE;
static short s_iMkBase = 10;

#if defined(WIN32)
char *AnsiString (LPCWSTR strIn);
#endif // WIN32

///////////////////////////////////////////////////////////////////////////////
// Map für MerkmalsCodes
typedef map<HFEATURE, os_string, less<HFEATURE> > CMCodeMap;
CMCodeMap g_MCodes;

typedef map<os_string, os_string, less<os_string> > CIdentMap;
CIdentMap g_Idents;

///////////////////////////////////////////////////////////////////////////////
// Zuordnung Ident <--> Objektklassenschlüssel
/*XX*/	#define INLINE inline

const int MAX_OKS_LENX = 32;
const int HDRENTRYTEXTLEN = 255;		//hdrentry.hxx

//XX	INLINE
//XX	HRESULT ClassFromIdentX (ULONG ulIdent, char *pBuffer, int iBuffLen)
//XX	{
//XX	CLASSFROMIDENT CFI;
//XX	
//XX		INITSTRUCT(CFI, CLASSFROMIDENT);
//XX		CFI.ulIdent = ulIdent;
//XX		CFI.pClass = pBuffer;
//XX		CFI.iBuffLen = iBuffLen;
//XX		if (NULL != pBuffer && iBuffLen > 0)
//XX			pBuffer[0] = '\0';
//XX		return DEX_GetClassFromIdent(CFI);
//XX	}

///////////////////////////////////////////////////////////////////////////////
//XX	extern "C" {	// alle exportierten Funktionen sollen _pascal sein 

HWND __hWndM;
UINT __DexCmd;

// KK001023
//ErrCode ExportIdentDescription(OFSTRUCT &of, const char* lpszOKS, const char* lpszShortDescription, const char* lpszLongDescription, const long lVisType, const VISINFO* pVI ) {
ErrCode ExportIdentDescription(OFSTRUCT &of, const char* lpszOKS, 
	const char* lpszShortDescription, const char* lpszLongDescription, 
	const long lVisType, const VISINFO* pVI, long lIdent) 
{
#if defined(_VERBOSEOUTPUT)
//#if defined(_DEBUG)
	TCHAR	_buf[_MAX_PATH];
	sprintf( _buf, "[%s] %s ---------------------", lpszOKS, lpszShortDescription );
	::ExportComment( of, _buf );
	sprintf( _buf, "%s", lpszLongDescription );
	::ExportComment( of, _buf );
	sprintf( _buf, "prio: %d, style: %d, loc: %d, vis: %d"
		, pVI->m_Priority
		, pVI->m_Style
		, pVI->m_fLocatable
		, pVI->m_fVisible
		);
	::ExportComment( of, _buf );
	switch(lVisType) {
	case OT_PUNKT: {
			PVISINFO	*pV = (PVISINFO*) pVI;
			sprintf(_buf,"Point, size: %d, %d", pV->m_Size.cx, pV->m_Size.cy);
			break;
		}
	case OT_KANTE: {
			sprintf(_buf,"Line");
			break;
		}
	case OT_FLAECHE: {
			FVISINFO	*pV = (FVISINFO*) pVI;
			sprintf(_buf,"Area, border: %d", pV->m_iWidth );
			break;
		}
	case OT_TEXT: {
			TVISINFO	*pV = (TVISINFO*) pVI;
			sprintf(_buf,"Text, size: %d,%d rot: %d incl: %d", pV->m_Size.cx, 
				pV->m_Size.cy, pV->m_Rot, pV->m_Orient );
			break;
		}
	}
	::ExportComment( of, _buf );
#endif
// #HK030129: ehe also einer fragt, warum zwar die Merkmalsbeschreibungen exportiert 
// (und nun wieder importiert) werden aber nicht die Beschreibungen der Objektklassen, 
// exportieren wir also ab sofort auch diese mit
CIdentMap::iterator it = g_Idents.find(lpszOKS);

	if (it == g_Idents.end()) {
		g_Idents.insert(CIdentMap::value_type(os_string(lpszOKS), 
			os_string(lpszShortDescription)));
	}

	return EC_OKAY;
}
//----------------------------------------------------------------------------------
ErrCode ExportMerkmalDescription(long lMCode, char *pbuf, short iTyp,short iLen ) 
{
// #HK001203: Merkmalskodes mit ihrem Kurztext als Kommentar ausgeben,
// da dadurch einerseits die Datei kompatibel bleibt, andererseits aber 
// Merkmale wieder richtig importiert werden können (der neue ASC-Import wertet
// die Kommentarsätze aus). Daher sämtliche MCodes in einer Map speichern und bei der 
// ersten Gelegenheit mit ausgeben.
long lRefCode = DEX_MapHandleToMCode(lMCode);
CMCodeMap::iterator it = g_MCodes.find(lRefCode);

	if (it == g_MCodes.end())
		g_MCodes.insert(CMCodeMap::value_type(lRefCode, os_string(pbuf)));
	return EC_OKAY;
}
//----------------------------------------------------------------------------------
ErrCode ExportIDDescription(char* lpszOKS,char* lpszShortDescription, char* lpszLongDescription, long lVisType, DWORD *pVis) {
	return EC_OKAY;
}
//----------------------------------------------------------------------------------

// Begin des DatenExports -----------------------------------------------------
//XX	ErrCode EXPORTFLT PASCAL DirisAscExportBegin (char *lpFileName, OFSTRUCT &of, OutMode OutFlag, HWND hWnd) {
/*XX*/	ErrCode ExportBegin (char *lpFileName, OFSTRUCT &of, OutMode OutFlag, HWND hWnd, const char* lpszDatasource ) {
register int fh;        // File Handle
register int OpenMode = OF_WRITE;
// KK000215 - kein "E"
//ErrCode EC;

// KK000203-kein Erstaufruf
	if (OutFlag != OMConcatinate) {
		iFirstData = TRUE;
// lUIdent setzen
		lUIdent = -1L;
	}


// FensterHandle merken
	USES_CONVERSION;
	CComBSTR	strDEXMessage;
	strDEXMessage.LoadString(IDS_DEXMESSAGE);
	__hWndM = hWnd;
//XX		__DexCmd = RegisterWindowMessage (ResString (IDS_DEXMESSAGE, 30));
	__DexCmd = RegisterWindowMessage(W2A(strDEXMessage));
//	s_iMkBase = DEX_GetMkBase();
	
// Datei eröffnen
	if ((fh = OpenFile (lpFileName, &of, OF_EXIST + OF_WRITE)) >= 0) {
		if (OutFlag == OMOverwrite)
		// Datei existiert bereits und überschreiben
			OpenMode += OF_CREATE;
	} else
		OpenMode += OF_CREATE;
	if ((fh = OpenFile (lpFileName, &of, OpenMode)) < 0)
	// Fehler: kann Datei nicht eröffnen
		return EC_NOFILE;
// wenn neue Info angehängt werden soll
// KK000215 - kein "E"
//	if (OutFlag == OMConcatinate) {

// KK000202
//		iFirstData = FALSE;		//Kein D-Satz UniqueIden

//		_llseek (fh, -4L, SEEK_END);	// vor Ende 'E' positionieren
//		if ((EC = DirisAscExportLine (fh, ';')) != EC_OKAY)
//			return EC;
//	}

return (ErrCode)_lclose (fh);
}


// Ausgeben einer Kommentarzeile ----------------------------------------------
//XX	ErrCode EXPORTFLT PASCAL DirisAscExportComment (OFSTRUCT &of, const char *lpCommentString) 
/*XX*/	ErrCode ExportComment (OFSTRUCT &of, const char *lpCommentString) 
{
register int fh;        // FileHandle
register ErrCode EC;

	if ((fh = OpenFile (NULL, &of, OF_REOPEN+OF_WRITE)) < 0)
	// Fehler: kann Datei nicht eröffnen
		return EC_NOFILE;
	_llseek (fh, 0L, SEEK_END);
	setmode (fh, O_TEXT);
	if ((EC = DirisAscExportLine (fh, ';', lpCommentString)) < 0) {
		_lclose (fh);
		return EC;
	}

return (ErrCode)_lclose (fh);
}


// Ausgeben der HeaderInformation ---------------------------------------------
//XX	ErrCode EXPORTFLT PASCAL DirisAscExportHeader (OFSTRUCT &of, const char *lpHeaderString) 
/*XX*/	ErrCode ExportHeader (OFSTRUCT &of, const char *lpHeaderString) 
{
register int fh;        // FileHandle
register ErrCode EC;

	if ((fh = OpenFile (NULL, &of, OF_REOPEN+OF_WRITE)) < 0)
	// Fehler: kann Datei nicht eröffnen
		return EC_NOFILE;
	_llseek (fh, 0L, SEEK_END);
	setmode (fh, O_TEXT);
	if ((EC = DirisAscExportLine (fh, 'H', lpHeaderString)) < 0) {
		_lclose (fh);
		return EC;
	}

return (ErrCode)_lclose (fh);
}
static char outBuff[_MAX_PATH];

//XX	// Ausgeben der BeschreibungsInformation --------------------------------------
//XX	//XX	ErrCode EXPORTFLT PASCAL DirisAscExportDescription (OFSTRUCT &of, const char *lpKeyInfo, const char *lpDescString) 
//XX	/*XX*/	ErrCode ExportDescription (OFSTRUCT &of, const char *lpKeyInfo, const char *lpDescString) 
//XX	{
//XX	register int fh;        // FileHandle
//XX	register ErrCode EC;
//XX	
//XX		if ((fh = OpenFile (NULL, &of, OF_REOPEN+OF_WRITE)) < 0)
//XX		// Fehler: kann Datei nicht eröffnen
//XX			return EC_NOFILE;
//XX		_llseek (fh, 0L, SEEK_END);
//XX		setmode (fh, O_TEXT);
//XX		wsprintf (outBuff, "Entry \"%-16.16s\" \"%.80s\"", lpKeyInfo, lpDescString);
//XX		if ((EC = DirisAscExportLine (fh, 'D', outBuff)) < 0) {
//XX			_lclose (fh);
//XX			return EC;
//XX		}
//XX	
//XX	// wenn UniqueIdent ausgegeben wurde, dann diesen merken
//XX	
//XX	//XX	if (!strcmp (lpKeyInfo, ResString (IDS_UNIQUEIDENT, 17))) 
//XX	/*XX*/	USES_CONVERSION;
//XX	/*XX*/	CComBSTR	strUniqueIdent;
//XX	/*XX*/	strUniqueIdent.LoadString(IDS_UNIQUEIDENT);
//XX	/*XX*/		if (!strcmp (lpKeyInfo, W2A(strUniqueIdent) )) 
//XX			lUIdent = atol (lpDescString);
//XX			
//XX	return (ErrCode)_lclose (fh);
//XX	}

//XX	ErrCode EXPORTFLT PASCAL DirisAscExportDescriptionEx ( OFSTRUCT &of, LPCSTR lpKeyInfo, LPCSTR lpDescString, DWORD dwStyle) 
/*XX*/	ErrCode ExportDescriptionEx ( OFSTRUCT &of, LPCSTR lpKeyInfo, LPCSTR lpDescString, DWORD dwStyle) 
{
register int fh;        // FileHandle
register ErrCode EC;

	if ((fh = OpenFile (NULL, &of, OF_REOPEN+OF_WRITE)) < 0)
	// Fehler: kann Datei nicht eröffnen
		return EC_NOFILE;
	_llseek (fh, 0L, SEEK_END);
	setmode (fh, O_TEXT);
	wsprintf (outBuff, "Entry%s%s \"%-16.16s\" \"%.255s\"", 
				(dwStyle & HEADER_READONLY) ? "Ro" : "",
				(dwStyle & HEADER_SYSTEM) ? "Sys" : "", 
				lpKeyInfo, lpDescString);
	if ((EC = DirisAscExportLine (fh, 'D', outBuff)) < 0) {
		_lclose (fh);
		return EC;
	}

// wenn UniqueIdent ausgegeben wurde, dann diesen merken
//XX	if (!strcmp (lpKeyInfo, ResString (IDS_UNIQUEIDENT, 17))) 
/*XX*/	USES_CONVERSION;
/*XX*/	CComBSTR	strUniqueIdent;
/*XX*/	strUniqueIdent.LoadString(IDS_UNIQUEIDENT);
/*XX*/		if (!strcmp (lpKeyInfo, W2A(strUniqueIdent) )) 
		lUIdent = atol (lpDescString);
		
return (ErrCode)_lclose (fh);
}

// Ausgeben der TrailerInformation --------------------------------------------
//XX	ErrCode EXPORTFLT PASCAL DirisAscExportTrailer (OFSTRUCT &of, const char *) 
/*XX*/	ErrCode ExportTrailer (OFSTRUCT &of, const char *) 
{
register int fh;        // FileHandle
register ErrCode EC;

	if ((fh = OpenFile (NULL, &of, OF_REOPEN+OF_WRITE)) < 0)
	// Fehler: kann Datei nicht eröffnen
		return EC_NOFILE;
	_llseek (fh, 0L, SEEK_END);
	setmode (fh, O_TEXT);
	if ((EC = DirisAscExportLine (fh, 'E')) < 0) {
		_lclose (fh);
		return EC;
	}

return (ErrCode)_lclose (fh);
}


// Ausgabe eines Geometrieobjektes mit Merkmalsinformation --------------------
//XX	ErrCode EXPORTFLT PASCAL DirisAscExportData (OFSTRUCT &of, GSTRUCT &GS, MFELD *MF, RSTRUCT *pRS, char *pUniqueId) 
/*XX*/	ErrCode ExportData (OFSTRUCT &of, GSTRUCT &GS, MFELD *MF, RSTRUCT *pRS, 
	LPCTSTR pUniqueId, LPCTSTR lpszGUID, LPCTSTR pParentClass) 
{
register int fh;        // DateiHandle
char cTyp = ' ';

// wenn noch kein UIdent-Satz geschrieben ist, dann einen generieren
	if (iFirstData && lUIdent == -1) {
		lUIdent = DEX_GetUniqueSysMCode();
		//XX	DirisAscExportDescription (of, ResString (IDS_UNIQUEIDENT, 17), ltoa (lUIdent, outBuff, 10));
		/*XX*/	USES_CONVERSION;
		/*XX*/	CComBSTR	strUniqueIdent;
		/*XX*/	strUniqueIdent.LoadString(IDS_UNIQUEIDENT);
		/*XX*/	ExportDescriptionEx (of, W2A(strUniqueIdent), ltoa (lUIdent, outBuff, 10), HEADER_SYSTEMRO );
	}
	iFirstData = FALSE;

// Datei eröffnen
	if ((fh = OpenFile (NULL, &of, OF_REOPEN+OF_WRITE)) < 0)
	// Fehler: kann Datei nicht eröffnen
		return EC_NOFILE;
	_llseek (fh, 0L, SEEK_END);
	setmode (fh, O_TEXT);
// KK000204 Guid-Code kontrollieren

ULONG hClass = DEX_GetObjIdent( GS.ON );
long lCurrentGUIDMCode = DEX_GetObjGuidMCode( hClass );

// evtl. ObjektGuid exportieren
OBJECTGUID OUID;
TCHAR	cbGuid[GUID_CCH + 1];

	INITSTRUCT(OUID, OBJECTGUID);
	OUID.lONr = GS.ON;
	cbGuid[0] = '\0';

bool fHasGuid = false;

	if( NULL != lpszGUID && *lpszGUID != '\0') {
		strncpy( cbGuid, lpszGUID, GUID_CCH );
		fHasGuid = true;	// Notlösung : falls kein GUID vorhanden, diesen auch nicht ausgeben
	} 

//  Assertion rausnehmen
/*-----
	} else {
		_ASSERTE( lpszGUID );		// das sollte jetzt nicht passieren!!

		if (SUCCEEDED(DEX_GetObjectGuid(OUID))) {
			CComBSTR	strGUID(OUID.guid);		// CComBSTR is schon ä bissel schlau ;-))
			USES_CONVERSION;
			strncpy( cbGuid, W2A(strGUID), GUID_CCH );

//XX		OLECHAR coleBuffer[GUID_CCH];

//XX			if (SUCCEEDED(StringFromGUID2 (OUID.guid, coleBuffer, GUID_CCH))) {
//XX				strcpy (cbGuid, AnsiString(coleBuffer));
//XX				fHasGuid = true;
//XX			}
		}
	}
--------------------------*/

// Identifikatorzeile generieren und ausgeben
//XX	char cbIdBuff[MAX_OKS_LENX];
//XX	HRESULT hr = ClassFromIdentX (GS.Id, cbIdBuff, MAX_OKS_LENX);

//XX	if (FAILED(hr)) return EC_ILLPARS;

//XX		if (S_OK == hr)
//XX	wsprintf (outBuff, "%8ld \"%s\" %4ld", GS.ON, cbIdBuff, GS.GSize);
/*XX*/			wsprintf (outBuff, "%8ld \"%s\" %4ld", GS.ON, pParentClass, GS.GSize);
//XX		else {
//XX			if (10 == DEX_GetIdBase())
//XX		wsprintf (outBuff, "%8ld %s %4ld", GS.ON, cbIdBuff, GS.GSize);
//XX			else 
//XX				wsprintf (outBuff, "%8ld 0x%s %4ld", GS.ON, cbIdBuff, GS.GSize);
//XX		}

	if (fHasGuid) {
		strcat (outBuff, " \"");
		strcat (outBuff, cbGuid);
		strcat (outBuff, "\"");
	}

// ggf. Identbeschreibung ausgeben
register ErrCode EC = EC_OKAY;
CIdentMap::iterator it = g_Idents.find(pParentClass);

	if (it != g_Idents.end()) {
	// das ist das erste Objekt mit diesem OKS
	char cbBuffer[_MAX_PATH];

		wsprintf (cbBuffer, "ClassDesc(%s): %s", pParentClass, (*it).second.c_str());
		if ((EC = DirisAscExportLine (fh, ';', cbBuffer)) < 0) {
			_lclose (fh);
			return EC;
		}
		g_Idents.erase(it);		// nur einmal ausgeben
	}

// Kopfsatz ausgeben
	switch (GS.Typ) {
		case OT_PUNKT:	cTyp = 'P'; break;
		case OT_KANTE:	cTyp = 'L'; break;
		case OT_FLAECHE:	cTyp = 'F'; break;
		case OT_TEXT:	cTyp = 'B'; break;
		default:	// Fehler: falscher ObjektTyp
			_lclose (fh);	
			return EC_OKAY;
	}	
	if ((EC = DirisAscExportLine (fh, cTyp, outBuff)) < 0) {
		_lclose (fh);
		return EC;
	}
// Merkmale ausgeben
	if ((EC = DirisAscExportMerkmale (fh, MF)) < 0) {
		_lclose (fh);
		return EC;
	}

// evtl. UniqueIdent generieren
ErrCode RC;

	if (pUniqueId == NULL) {
	char UIString[64];

		_splitpath (of.szPathName, NULL, NULL, UIString, NULL);
		strupr (UIString);
		wsprintf (UIString, "%s_%ld", UIString, GS.ON);
		DBASSERT(DirisAscExportEinMerkmal (fh, 'A', lUIdent, UIString));
	} 
	else {
	LPCTSTR pT = pUniqueId;

		if (!strncmp (pUniqueId, "[P]", 3) || !strncmp (pUniqueId, "[B]", 3) || 
		    !strncmp (pUniqueId, "[T]", 3))
		    	pT += 3;
		
		DBASSERT(DirisAscExportEinMerkmal (fh, 'A', lUIdent, pT));
	}

// Relationen ausgeben
	if ((EC = DirisAscExportRelationen (fh, pRS)) < 0) {
		_lclose (fh);
		return EC;
	}

// Geometrieinformation ausgeben
	if ((EC = DirisAscExportGeometrie (fh, GS)) < 0) {
		_lclose (fh);
		return EC;
	}

return (ErrCode)_lclose (fh);
}


// Ende des DatenExports ------------------------------------------------------
//XX	ErrCode EXPORTFLT PASCAL DirisAscExportEnd (OFSTRUCT &) { return EC_OKAY; } 
/*XX*/	ErrCode ExportEnd (OFSTRUCT &) 
{ 
	g_MCodes.clear();	// MCodemap leeren
	return EC_OKAY; 
} 


// Abbrechen des Datenexportes ------------------------------------------------
//XX	ErrCode EXPORTFLT PASCAL DirisAscExportBreak (OFSTRUCT &of) 
/*XX*/	ErrCode ExportBreak (OFSTRUCT &of) 
{ 
// Datei löschen, damit keine Reste bleiben
	OpenFile (of.szPathName, &of, OF_DELETE);
	g_MCodes.clear();	// MCodemap leeren
	return EC_OKAY; 
} 

//XX	}	// extern "C"

// Statische Funktionen -------------------------------------------------------
// Merkmalsinformation ausgeben
static ErrCode DirisAscExportEinMerkmal (int fh, short iMTyp, long lMCode, LPCTSTR pText)
{
ErrCode RC = EC_OKAY;
CMCodeMap::iterator it = g_MCodes.find(lMCode);

	if (it != g_MCodes.end()) {
	// das ist das erste Merkmal mit diesem MCode
	char cbBuffer[_MAX_PATH];

		wsprintf (cbBuffer, "AttrDesc(%ld): %s", lMCode, (*it).second.c_str());
		if ((RC = DirisAscExportLine (fh, ';', cbBuffer)) < 0) {
			_lclose (fh);
			return RC;
		}
		g_MCodes.erase(it);		// nur einmal ausgeben
	}

// jetzt Merkmal normal ausgeben
long Len = strlen (pText);        	// MerkmalsLänge

	if (iMTyp != 'T') {
	// kein TextObjekt: MerkmalsKopfsatz ausgeben
		if (s_iMkBase == 10) 
			wsprintf (outBuff, "%08ld 1 %c %4ld", lMCode, iMTyp, Len);
		else
			wsprintf (outBuff, "0x%08lx 1 %c %4ld", lMCode, iMTyp, Len);

		DBASSERT (DirisAscExportLine (fh, 'M', outBuff));
	}

	switch (iMTyp) {
	case 'A':       // Textmerkmal
	case 'T':	// TextObjekt
		{
		long outLen = 0;        // bereits ausgegebene Länge
		LPCTSTR cptr = pText;

			if (iMTyp == 'T' && lMCode != -1L) {
			// IndirektText
				if (s_iMkBase == 10) 
					wsprintf (outBuff, "%08ld" , lMCode);
				else
					wsprintf (outBuff, "0x%08lx" , lMCode);

				DBASSERT (DirisAscExportLine (fh, 'I', outBuff));
			} else {
			bool fFirst = true;
			char format[12];
			char ScopeChar = strchr (cptr, '\"') == NULL ? '\"' : '\'';

				if (0 == Len) {
					wsprintf (outBuff, "%c%c", ScopeChar, ScopeChar);
					DBASSERT (DirisAscExportLine (fh, 
				 			(iMTyp == 'T') && fFirst ? 'I' : 'W', 
							outBuff));
				} else {
					while (outLen < Len) {
					int actLen = (Len - outLen) > 70 ? 70 : (int)(Len - outLen);
		
						wsprintf (format, "%c%%-%02d.%02ds%c", ScopeChar, actLen, actLen, ScopeChar);
						wsprintf (outBuff, format, cptr);
						DBASSERT (DirisAscExportLine (fh, 
				 				(iMTyp == 'T') && fFirst ? 'I' : 'W', 
								outBuff));
						fFirst = false;		// nur 1. Zeile mit 'I'
						cptr += actLen;
						outLen += actLen;
					}
				}
			}
		}
		break;

	case 'I':       // IntegerMerkmal
	case 'F':       // DoubleMerkmal
		DBASSERT (DirisAscExportLine (fh, 'W', pText));
		break;

	default:
		return EC_ILLPARS;
	}

return EC_OKAY;
}


static ErrCode DirisAscExportMerkmale (int fh, MFELD *MF) 
{
register ErrCode RC;

	if ( NULL == MF)
		return EC_OKAY;

	while (MF -> MCode != 0) {		// für alle Merkmale
	short locMTyp = toupper (MF -> MTyp);

		if (locMTyp == 'B' || locMTyp == 'C') {		// #HK950720
		// Sicht- oder IdentMerkmal ist reingeraten
			MF++;
			continue;
		}

		if (lUIdent == MF -> MCode) {
			MF++;
			continue;		// UIdent wird extra ausgegeben
		}

	// eigentliche MerkmalsWertAusgabe
		DBASSERT(DirisAscExportEinMerkmal (fh, locMTyp, MF -> MCode, MF -> MText));

		MF++;           // nächstes Merkmal
	}

return EC_OKAY;
}

// Geometrieinformation ausgeben
static ErrCode DirisAscExportGeometrie (int fh, GSTRUCT &GS) 
{
register ErrCode RC;
char tBuff[64];
char *dFormat = "%10.3f";

	if ( 0 == GS.GSize)
		return EC_OKAY;

	for (long i = 0; i < GS.GSize; i++) {
	// Geometriezeile generieren
		strcpy (outBuff, DtoAFlt (tBuff, dFormat, ((double HUGE *)GS.x)[i]/* /1000.0 */));
		strcat (outBuff, " ");
		strcat (outBuff, DtoAFlt (tBuff, dFormat, ((double HUGE *)GS.y)[i]/* /1000.0 */));
		if (i + 1 < GS.GSize) {
			strcat (outBuff, " ");
			strcat (outBuff, DtoAFlt (tBuff, dFormat, ((double HUGE *)GS.x)[i+1]/* /1000.0 */));
			strcat (outBuff, " ");
			strcat (outBuff, DtoAFlt (tBuff, dFormat, ((double HUGE *)GS.y)[i+1]/* /1000.0 */));
			i++;
		}


		if (i + 1 < GS.GSize) {
			strcat (outBuff, " ");
			strcat (outBuff, DtoAFlt (tBuff, dFormat, ((double HUGE *)GS.x)[i+1]/* /1000.0 */));
			strcat (outBuff, " ");
			strcat (outBuff, DtoAFlt (tBuff, dFormat, ((double HUGE *)GS.y)[i+1]/* /1000.0 */));
			i++;
		}


	// Geometriezeile ausgeben
		DBASSERT (DirisAscExportLine (fh, 'G', outBuff));
	}

return EC_OKAY;
}

// Ausgabe der Relationen -----------------------------------------------------
static ErrCode DirisAscExportRelationen (int fh, RSTRUCT *pRS) 
{
ErrCode RC;

	if (pRS == NULL) return EC_OKAY;	// no relations, no fun

	while (pRS -> RCode != -1) {
		switch (pRS -> RTyp) {
		case RT_BEGLEIT:
			wsprintf (outBuff, "B %ld", pRS -> RON);
			break;

		case RT_GLEICHR:
			wsprintf (outBuff, "H %ld %ld", pRS -> RCode, pRS -> RON);
			break;

		case RT_KOMPLEX:
			wsprintf (outBuff, "K %ld %ld", pRS -> RCode, pRS -> RON);
			break;

		default:
			outBuff[0] = '\0';
			break;
		}
		DBASSERT (DirisAscExportLine (fh, 'R', outBuff));
		pRS++;		// nächste Relation
	}

return EC_OKAY;
}

static ErrCode DirisAscExportLine (int fh, char cTyp, const char *Line) 
{
// Ausgabe der ZeilenKennung
char cptr[3];

	cptr[2] = '\0';
	memset (cptr, ' ', 2);
	if (cTyp != '\0') {             // nur, wenn Kennung gegeben ist
		cptr[0] = cTyp;
		if (_lwrite (fh, cptr, 2) != 2)
			return EC_NOSPACE;
	}
// Ausgabe der Zeile
	if (Line != NULL) {
	UINT Len = strlen (Line);

		if (_lwrite (fh, (char *)Line, Len) != Len)
			return EC_NOSPACE;
	} 
// NewLine ausgeben
	strcpy (cptr, "\r\n");		// CR,LF
	if (_lwrite (fh, cptr, 2) != 2)
		return EC_NOSPACE;            

return EC_OKAY;
}

