// Routinen zum Schreiben des DIRIS-Austauschformates -------------------------
// File: PolygisDat.CXX

#include "stdafx.h"
#include "PolygisDatImpl.h"

#include <string.h>
#include <fcntl.h>
#include <io.h>
#include <ctype.h>
#include <stdlib.h>

#include <ERRINSTX.HXX>
#include <REGISTRX.HXX>


#include <trias01m.hxx>
#include <versions.h>
#include <risdb.h>

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

static ErrCode PolygisDatExportMerkmale (int fh, char cTyp, MFELD *MF , GSTRUCT &GS);
static ErrCode PolygisDatExportGeometrie (int fh, GSTRUCT &GS);
static ErrCode PolygisDatExportRelationen (int fh, RSTRUCT *pRS);
static ErrCode PolygisDatExportLine (int fh, char cTyp, const char *lpStr = NULL);
static ErrCode PolygisDatExportEinMerkmal (int fh, short iMTyp, long lMCode, LPCTSTR pText);
static ErrCode GetLayerInfo ( char *pLayer,long lIdent);
static ErrCode SetHeaderInfo ( char cTyp, char *Line, char * pLayer);
static ErrCode SetPointStructure (char cTyp, char * pLine, GSTRUCT &GS);

static ErrCode ExportRegistryMerkmal ( MFELD *MF, char * pOut) ;
static ErrCode ExportRegistryPunktMerkmal ( MFELD *MF, char * pOut) ;
static ErrCode ExportPolygisDatMerkmal ( MFELD *MF, char * pOut) ;
static ErrCode ExportPolygisDatPunktMerkmal ( MFELD *MF, char * pOut); 

ErrCode SetExportKeyDescription( void) ;
ErrCode SetExportPointKeyDescription( void) ;

ErrCode ExportKeyDescription( long lMCode, char *pBuf);
ErrCode ExportPointKeyDescription( long lMCode, char *pBuf);

ErrCode SetErrorMasterKey( char cTyp, char *pKey);

static long lUIdent = -1L;
static short iFirstData = FALSE;

static short iFirstError = TRUE;
static short iFirstPointError = TRUE;


static short s_iMkBase = 10;

HPROJECT g_hPr = 0;

static char Layer[_MAX_PATH];
char ParentRefClass[_MAX_PATH] = {"-"};


#if defined(WIN32)
char *AnsiString (LPCWSTR strIn);
#endif // WIN32

///////////////////////////////////////////////////////////////////////////////
// Map für MerkmalsCodes
typedef map<INT_PTR, os_string, less<INT_PTR> > CMCodeMap;
CMCodeMap g_MCodes;

///////////////////////////////////////////////////////////////////////////////
// Zuordnung Ident <--> Objektklassenschlüssel
/*XX*/	#define INLINE inline

const int MAX_OKS_LENX = 32;
const int HDRENTRYTEXTLEN = 255;		//hdrentry.hxx

static short iFirstPointOKS = TRUE;		// Erster Klassenwechsel

static short iFirstOKS = TRUE;		// Erster Klassenwechsel
static short iNoReg = TRUE;			// Kein Registry-Eintrag
static short iShowReg = TRUE;		// Registry soll gelesen werden

const int BNAKEYLEN = 80;
const int KEYCOUNT = 8;

long m_lNumberUnique = 0;					// Position/Reihenfolge des UniqueIdent

long m_lNumberKey = 0;						// Maximaler Keyxx-Wert
long m_lNumberPointKey = 0;						// Maximaler Keyxx-Wert

////////////////////// Registrierung //////////////////////////////////////////

DWORD dKeyLen = BNAKEYLEN;

char g_cKey [KEYCOUNT][BNAKEYLEN];
//Punkte
char g_cKeyP [KEYCOUNT][BNAKEYLEN];

long g_lKey[KEYCOUNT] = { 0L,0L,0L,0L,0L,0L,0L,0L};
long g_lKeyP[KEYCOUNT] = { 0L,0L,0L,0L,0L,0L,0L,0L};


UINT KEYFELD [KEYCOUNT] = { IDS_KEY01,IDS_KEY02,IDS_KEY03,IDS_KEY04,IDS_KEY05,IDS_KEY06,IDS_KEY07,IDS_KEY08};


// Registrierung
static LPCTSTR g_cbBNALocal	= TEXT("Software\\%s\\%s\\%s\\%s\\%s");
static LPCTSTR g_cbBNA	= TEXT("Software\\%s\\%s\\%s\\%s");

bool ExportRegistry (void);

void SetKeyStandards ( void);
void DeleteKeyStandards (void);
void SetKeyInformation (long , UINT );
void SetRegistryKeyData ( CCurrentUser * , long ,UINT );
void SetRegistryPointKeyData ( CCurrentUser * , long ,UINT );

///////////////////////////////////////////////////////////////////////////////
//XX	extern "C" {	// alle exportierten Funktionen sollen _pascal sein 

HWND __hWndM;
UINT __DexCmd;

// KK001023
//ErrCode ExportIdentDescription(OFSTRUCT &of, const char* lpszOKS, const char* lpszShortDescription, const char* lpszLongDescription, const long lVisType, const VISINFO* pVI ) {
ErrCode ExportIdentDescription(OFSTRUCT &of, const char* lpszOKS, const char* lpszShortDescription, const char* lpszLongDescription, const long lVisType, const VISINFO* pVI , long lIdent) {


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


   	// aktive Datenquelle bsorgen
     g_hPr = DEX_GetDataSourceHandle();
     _ASSERTE(NULL != g_hPr);

	if (iShowReg ) {
		iNoReg = ExportRegistry();
		iShowReg = FALSE;
		iFirstError = TRUE;
		iFirstPointError = TRUE;
	}

	ExportKeyDescription(lMCode, pbuf) ;
	ExportPointKeyDescription(lMCode, pbuf) ;


	CMCodeMap::iterator it = g_MCodes.find(lMCode);

	if (it == g_MCodes.end())
		g_MCodes.insert(CMCodeMap::value_type(lMCode, os_string(pbuf)));

	return EC_OKAY;
}
//----------------------------------------------------------------------------------
ErrCode ExportIDDescription(char* lpszOKS,char* lpszShortDescription, char* lpszLongDescription, long lVisType, DWORD *pVis) {
	return EC_OKAY;
}
//----------------------------------------------------------------------------------

// Begin des DatenExports -----------------------------------------------------
//XX	ErrCode EXPORTFLT PASCAL PolygisDatExportBegin (char *lpFileName, OFSTRUCT &of, OutMode OutFlag, HWND hWnd) {
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

return (ErrCode)_lclose (fh);
}


// Ausgeben einer Kommentarzeile ----------------------------------------------
//XX	ErrCode EXPORTFLT PASCAL PolygisDatExportComment (OFSTRUCT &of, const char *lpCommentString) 
/*XX*/	ErrCode ExportComment (OFSTRUCT &of, const char *lpCommentString) 
{
	return EC_OKAY;
}


// Ausgeben der HeaderInformation ---------------------------------------------
//XX	ErrCode EXPORTFLT PASCAL PolygisDatExportHeader (OFSTRUCT &of, const char *lpHeaderString) 
/*XX*/	ErrCode ExportHeader (OFSTRUCT &of, const char *lpHeaderString) 
{
	return EC_OKAY;

}

static char outBuff[_MAX_PATH];

//XX	ErrCode EXPORTFLT PASCAL PolygisDatExportDescriptionEx ( OFSTRUCT &of, LPCSTR lpKeyInfo, LPCSTR lpDescString, DWORD dwStyle) 
/*XX*/	ErrCode ExportDescriptionEx ( OFSTRUCT &of, LPCSTR lpKeyInfo, LPCSTR lpDescString, DWORD dwStyle) 
{
	return EC_OKAY;
}

// Ausgeben der TrailerInformation --------------------------------------------
//XX	ErrCode EXPORTFLT PASCAL PolygisDatExportTrailer (OFSTRUCT &of, const char *) 
/*XX*/	ErrCode ExportTrailer (OFSTRUCT &of, const char *) 
{

	return EC_OKAY;
}


// Ausgabe eines geometrieobjektes mit Merkmalsinformation --------------------
//XX	ErrCode EXPORTFLT PASCAL PolygisDatExportData (OFSTRUCT &of, GSTRUCT &GS, MFELD *MF, RSTRUCT *pRS, char *pUniqueId) 
/*XX*/	ErrCode ExportData (OFSTRUCT &of, GSTRUCT &GS, MFELD *MF, RSTRUCT *pRS, LPCTSTR pUniqueId, LPCTSTR lpszGUID, LPCTSTR pParentClass ) 
{
register int fh;        // DateiHandle
char cTyp = ' ';

// wenn noch kein UIdent-Satz geschrieben ist, dann einen generieren
	if (iFirstData && lUIdent == -1) {
		lUIdent = DEX_GetUniqueSysMCode();
		//XX	PolygisDatExportDescription (of, ResString (IDS_UNIQUEIDENT, 17), ltoa (lUIdent, outBuff, 10));
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

register ErrCode EC = EC_OKAY;
ErrCode RC;


// Klassenwechsel ??
	iFirstOKS = FALSE;

	if ( strcmp ( pParentClass, ParentRefClass) != 0 ) {

		HPROJECT hPr = DEX_GetObjectsProject(GS.Id);

		if ( ParentRefClass[0] == '-' || hPr != g_hPr) {

			g_hPr = hPr;

			iFirstPointOKS = TRUE;

			if (GS.Typ == OT_PUNKT ) {
				SetExportPointKeyDescription();		// Key-Definitionen überprüfen
				iFirstPointOKS = FALSE;
			} else {
				SetExportKeyDescription();		// Key-Definitionen überprüfen
			}
		}

		strcpy ( ParentRefClass,pParentClass);

		GetLayerInfo ( Layer,GS.Id);
		iFirstOKS = TRUE;

	}

	if (GS.Typ == OT_PUNKT && iFirstPointOKS) {
		iFirstPointOKS = FALSE;
		SetExportPointKeyDescription();		// Key-Definitionen überprüfen
	}

	switch (GS.Typ) {
		case OT_PUNKT:	cTyp = 'P'; break;
		case OT_KANTE:	cTyp = 'L'; break;
		case OT_FLAECHE:	cTyp = 'F'; break;
		case OT_TEXT:	cTyp = 'B'; break;
		default:	// Fehler: falscher ObjektTyp
			_lclose (fh);	
			return EC_OKAY;
	}	

	if ( iFirstOKS) {
// LAYERDEF: POINT	GCOPunkte_ohne_DLK	GCO	Geocodierte Objekte
		outBuff[0] = '\0';
		if ((EC =  SetHeaderInfo ( cTyp, outBuff, Layer)) < 0)
			return EC;

		DBASSERT (PolygisDatExportLine (fh, 'D', outBuff));
	}
	
// Merkmale ausgeben
	if ((EC = PolygisDatExportMerkmale (fh, cTyp, MF, GS)) < 0) {
		_lclose (fh);
		return EC;
	}

// evtl. UniqueIdent generieren

	if (pUniqueId == NULL) {
	char UIString[64];

		_splitpath (of.szPathName, NULL, NULL, UIString, NULL);
		strupr (UIString);
		wsprintf (UIString, "%s_%ld", UIString, GS.ON);
		DBASSERT(PolygisDatExportEinMerkmal (fh, 'A', lUIdent, UIString));
	} 
	else {
	LPCTSTR pT = pUniqueId;

		if (!strncmp (pUniqueId, "[P]", 3) || !strncmp (pUniqueId, "[B]", 3) || 
		    !strncmp (pUniqueId, "[T]", 3))
		    	pT += 3;
		
		DBASSERT(PolygisDatExportEinMerkmal (fh, 'A', lUIdent, pT));
	}



	if ( cTyp != 'P') {	// Punkte haben andere Struktur
// Geometrieinformation ausgeben
		if ((EC = PolygisDatExportGeometrie (fh, GS)) < 0) {
			_lclose (fh);
			return EC;
		}
	}

return (ErrCode)_lclose (fh);
}


// Ende des DatenExports ------------------------------------------------------
//XX	ErrCode EXPORTFLT PASCAL PolygisDatExportEnd (OFSTRUCT &) { return EC_OKAY; } 
/*XX*/	ErrCode ExportEnd (OFSTRUCT &) 
{ 
	g_MCodes.clear();	// MCodemap leeren
	return EC_OKAY; 
} 


// Abbrechen des Datenexportes ------------------------------------------------
//XX	ErrCode EXPORTFLT PASCAL PolygisDatExportBreak (OFSTRUCT &of) 
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
static ErrCode PolygisDatExportEinMerkmal (int fh, short iMTyp, long lMCode, LPCTSTR pText)
{
ErrCode RC = EC_OKAY;


return EC_OKAY;
}

//----------------------------------------------------------------------------------------
static ErrCode PolygisDatExportMerkmale (int fh,char cTyp, MFELD *MF, GSTRUCT &GS ) 
{
register ErrCode RC;

	if ( NULL == MF)
		return EC_OKAY;

	outBuff[0] = '\0';

	strcpy(outBuff,Layer);

	strcat (outBuff, "\t");

	if ( cTyp == 'P') {
		DBASSERT (SetPointStructure (cTyp, outBuff, GS));

		if ( iNoReg ) {				// Keine Registry-Einträge - MK in ankommender Reihenfolge
			ExportPolygisDatPunktMerkmal ( MF, outBuff);	//Nur GCA-Kurzcode
		} else {
			ExportRegistryPunktMerkmal ( MF, outBuff);
		}

	} else {

		if ( iNoReg ) {				// Keine Registry-Einträge - MK in ankommender Reihenfolge
			ExportPolygisDatMerkmal ( MF, outBuff);
		} else {
			ExportRegistryMerkmal ( MF, outBuff);
		}
	}
	// Geometriezeile ausgeben
	DBASSERT (PolygisDatExportLine (fh, cTyp, outBuff));

return EC_OKAY;
}
//----------------------------------------------------------------------------------------

// Geometrieinformation ausgeben
static ErrCode PolygisDatExportGeometrie (int fh, GSTRUCT &GS) 
{
register ErrCode RC;
char tBuff[64];
char *dFormat = "%10.3f";

	if ( 0 == GS.GSize)
		return EC_OKAY;

	double dZusatz = 0.0;

	for (long i = 0; i < GS.GSize; i++) {
	// Geometriezeile generieren
		strcpy (outBuff, DtoAFlt (tBuff, dFormat, ((double HUGE *)GS.x)[i]/* /1000.0 */));
		strcat (outBuff, "\t");
		strcat (outBuff, DtoAFlt (tBuff, dFormat, ((double HUGE *)GS.y)[i]/* /1000.0 */));
		strcat (outBuff, "\t");
		strcat (outBuff, "0.000");


	// Geometriezeile ausgeben
		DBASSERT (PolygisDatExportLine (fh, 'G', outBuff));
	}

	// END setzen
	DBASSERT (PolygisDatExportLine (fh, 'E', outBuff));


return EC_OKAY;
}

// Ausgabe der Relationen -----------------------------------------------------
static ErrCode PolygisDatExportRelationen (int fh, RSTRUCT *pRS) 
{
return EC_OKAY;
}

static ErrCode PolygisDatExportLine (int fh, char cTyp, const char *Line) 
{
// Ausgabe der ZeilenKennung

char cptr[15];

	cptr[0] = '\0';

	switch (cTyp) {

		case 'P': 
			strcat (cptr,"POINT");
			break;
		case 'L':
			strcat (cptr,"SEG");
			break;
		case 'F':
			strcat (cptr,"POLY");
			break;
		case 'B':
			strcat (cptr,"POINT");
			break;
		case 'G':
			strcat (cptr,"PP");
			break;
		case 'D':
			strcat (cptr,"LAYERDEF:");
			break;
		case 'E':
			strcat (cptr,"END");
			break;

		default:	// Fehler: falscher ObjektTyp
			_lclose (fh);	
			return EC_OKAY;
	}	

	strcat (cptr,"\t");

	UINT LenP = strlen (cptr);

	if (_lwrite (fh, cptr, LenP) != LenP)
		return EC_NOSPACE;

	
	if ( cTyp != 'E') {

// Ausgabe der Zeile
		if (Line != NULL) {
		UINT Len = strlen (Line);

		if (_lwrite (fh, (char *)Line, Len) != Len)
			return EC_NOSPACE;
		} 

	}

// NewLine ausgeben
	strcpy (cptr, "\r\n");		// CR,LF
	if (_lwrite (fh, cptr, 2) != 2)
		return EC_NOSPACE;            

	return EC_OKAY;
}
//------------------------------------------------------------------------------------------
static ErrCode GetLayerInfo ( char *pLayer,long lIdent) {


	*pLayer = '\0';

	HPROJECT hPr = DEX_GetObjectsProject(lIdent);


	PBDDATA pbdData;

	memset (&pbdData, '\0', sizeof(PBDDATA));

	pbdData.dwSize = sizeof(PBDDATA);
	pbdData.pbdTyp = 'i';
	pbdData.pbdCode = lIdent;
	pbdData.pbdKText = pLayer;
	pbdData.pbdKTextLen = _MAX_PATH -1;
	pbdData.pbdLTextLen = 0;
	
	{

	ErrInstall EI ( WC_NOIDENT);

	DEX_GetPBDDataEx (hPr,pbdData);
	}

	return EC_OKAY;

}
//------------------------------------------------------------------------------------------
static ErrCode SetHeaderInfo ( char cTyp, char *Line, char * pLayer) 
{
// Ausgabe der ZeilenKennung

	if ( !Line )
		return EC_NOSPACE;    
	
	if ( !pLayer )
		return EC_NOSPACE;            

	switch (cTyp) {

		case 'P': 
			strcpy (Line,"POINT");
			break;
		case 'L':
			strcpy (Line,"SEG ");
			break;
		case 'F':
			strcpy (Line,"POLY ");
			break;

		default:	// Fehler: falscher ObjektTyp
			return EC_NOSPACE;
	}	

	strcat ( Line, "\t");
	strcat ( Line, pLayer);
	strcat ( Line, "\t");
	strcat ( Line, "GCO\tGeocodierte Objekte");
	
	return EC_OKAY;

}
//-----------------------------------------------------------------------------------------
static ErrCode SetPointStructure (char cTyp, char * pLine, GSTRUCT &GS)
{

	if ( cTyp != 'P')
		return EC_OKAY;

	char tBuff[64];
	char *dFormat = "%10.3f";

	if ( 0 == GS.GSize)
		return EC_OKAY;

	long i = 0;
	// Geometriezeile generieren
	strcat (pLine, DtoAFlt (tBuff, dFormat, ((double HUGE *)GS.x)[i]/* /1000.0 */));
	strcat (pLine, "\t");
	strcat (pLine, DtoAFlt (tBuff, dFormat, ((double HUGE *)GS.y)[i]/* /1000.0 */));
	strcat (pLine, "\t");
	strcat (pLine, "0.000");
	strcat (pLine, "\t");


	// Sonderdaten - 	0		N	0.000	0.000

	strcat (pLine, "0\t\tN\t0.000\t0.000\t");

	return EC_OKAY;

}


//-----------------------------------------------------------------------------------------
/////////////// Registrierung /////////////////////////////////////////////////////////////
//-------------------------------------------------------------------------------
bool ExportRegistry(void)
{
// Registry-Einträge

	DeleteKeyStandards();

	TCHAR szBNAKey[_MAX_PATH];

	USES_CONVERSION;

	CComBSTR Projekt;
	Projekt.LoadString(IDS_PROJEKTLAYER);
	
	CComBSTR Export;
	Export.LoadString(IDS_EXPORT);

	CComBSTR Thema;
	Thema.LoadString(IDS_STANDARD);

	CComBSTR ThemaP;
	ThemaP.LoadString(IDS_PUNKTSTANDARD);

	wsprintf(szBNAKey,g_cbBNA,REG_COMPANY_KEY,REG_PRODUCT_KEY,W2A(Projekt),W2A(Export));

		{	

			CCurrentUser rgMass(szBNAKey, true);

			char cbBuffer[80];

			long lLen = BNAKEYLEN;

			// Existiert Registry-Eintrag - falls nein - Merkmale beliebig!

			if ( !rgMass.GetSZ ((LPCTSTR )W2A(Thema), (LPTSTR) cbBuffer, lLen))
				return TRUE;		// beliebige Merkmalsvergabe

		}

// Standardeinträge


	wsprintf(szBNAKey,g_cbBNALocal,REG_COMPANY_KEY,REG_PRODUCT_KEY,W2A(Projekt),W2A(Export),W2A(Thema));


		{	

			CCurrentUser rgMass(szBNAKey, true);


			for ( long i = 0; i < KEYCOUNT; i++ ) {
				SetRegistryKeyData ( &rgMass,i,KEYFELD[i]);
			}




		}


// PunktEinträge ??

	wsprintf(szBNAKey,g_cbBNALocal,REG_COMPANY_KEY,REG_PRODUCT_KEY,W2A(Projekt),W2A(Export),W2A(ThemaP));


		{	

			CCurrentUser rgMass(szBNAKey, true);


			for ( long i = 0; i < KEYCOUNT; i++ ) {
				SetRegistryPointKeyData ( &rgMass,i,KEYFELD[i]);
			}




		}


		return FALSE;
		

}
//------------------------------------------------------------------------

//------------------------------------------------------------------------
void SetKeyStandards ( void )
{


	for ( long i = 0; i < KEYCOUNT; i++ ) {
		SetKeyInformation ( i,KEYFELD[i]);
	}


}
//-----------------------------------------------------------------------
void SetKeyInformation (long i, UINT Id)
{

	USES_CONVERSION;

	CComBSTR Key;
	Key.LoadString(Id);
	strcat ( &g_cKey[i][0],W2A(Key.m_str));

}

//------------------------------------------------------------------------
void DeleteKeyStandards ( void )
{
	for ( long i = 0 ; i < KEYCOUNT; i++ ) {
		g_cKey[i][0] = '\0';
	}

}
//-----------------------------------------------------------------------
void SetRegistryPointKeyData ( CCurrentUser * pCU, long i,UINT Id)
{

	USES_CONVERSION;

	CComBSTR Key;
	Key.LoadString (Id);

	DWORD dKeyLen = BNAKEYLEN;
	pCU->GetSubSZ ((LPCTSTR )W2A(Key), (LPTSTR) &g_cKeyP[i][0], dKeyLen);

}

//-----------------------------------------------------------------------
void SetRegistryKeyData ( CCurrentUser * pCU, long i,UINT Id)
{

	USES_CONVERSION;

	CComBSTR Uniq;
	Uniq.LoadString (IDS_UNIQUEIDENT);

	CComBSTR Key;
	Key.LoadString (Id);

	DWORD dKeyLen = BNAKEYLEN;
	pCU->GetSubSZ ((LPCTSTR )W2A(Key), (LPTSTR) &g_cKey[i][0], dKeyLen);

	if ( strcmp ((LPTSTR) &g_cKey[i][0],(LPTSTR) W2A(Uniq.m_str)) == 0 )
		m_lNumberUnique = i + 1;	// i von "0" bis ..., lNumberUnique von "1" bis ...

}
//-----------------------------------------------------------------------
ErrCode ExportPointKeyDescription( long lMCode, char *pBuf) {

	HPROJECT hPr = DEX_GetFeatureProject(lMCode) ;


	if (0 == hPr || g_hPr != hPr) 
		return EC_OKAY;


	long i = 0;
	while ( i < KEYCOUNT ) {
		if ( strcmp ((LPTSTR) &g_cKeyP[i][0],(LPTSTR)pBuf ) == 0 ) {
			g_lKeyP[i] = lMCode;
			if ( i > m_lNumberPointKey)
				m_lNumberPointKey = i;
			break;
		}
		i++;
	}


	return EC_OKAY;
}
///////////////////////////////////////////////////////////////////////////////////////////////

ErrCode ExportKeyDescription( long lMCode, char *pBuf) {

	HPROJECT hPr = DEX_GetFeatureProject(lMCode) ;


	if (0 == hPr || g_hPr != hPr) 
		return EC_OKAY;


	long i = 0;
	while ( i < KEYCOUNT ) {
		if ( strcmp ((LPTSTR) &g_cKey[i][0],(LPTSTR)pBuf ) == 0 ) {
			g_lKey[i] = lMCode;
			if ( i > m_lNumberKey)
				m_lNumberKey = i;
			break;
		}
		i++;
	}


	return EC_OKAY;
}
///////////////////////////////////////////////////////////////////////////////////////////////
ErrCode SetExportKeyDescription( void) {

	if ( 0 == g_hPr)
		return EC_OKAY;

	long lMCode = 0;

	long i = 0;

	while ( i <= m_lNumberKey ) {
		if ( g_cKey[i][0] != '\0') {
			lMCode = DEX_GetMCodeFromFeatureNameEx (g_hPr,(LPTSTR)&g_cKey[i][0]);

// KK030320
			g_lKey[i] = DEX_MapHandleToMCode(lMCode);			
//			g_lKey[i] = DEX_MapMCodeToHandle(g_hPr,lMCode);

			// Falls Attribut in Datenquwelle nicht definiert
			if ( g_lKey[i] == 0L) {
				USES_CONVERSION;
				CComBSTR	strCaption;
				strCaption.LoadString(IDS_DISPLAYNAME);
				CComBSTR	strFormat;
				strFormat.LoadString(IDS_ERRORFORMAT);

				TCHAR szText[_MAX_PATH];

				char cbBuffer[_MAX_PATH];

				if (NULL != DEX_GetDataSourceShortName (g_hPr, cbBuffer)) 
					wsprintf ( szText, W2A(strFormat),i+1,(LPTSTR) &g_cKey[i][0],cbBuffer); // Keyxx = Name
			
				MessageBox (__hWndM,
					szText,
					W2A(strCaption),
					MB_OK | MB_ICONINFORMATION );
			}


		}
		i++;
	}


	return EC_OKAY;
}
//////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
ErrCode SetErrorMasterKey( char cTyp, char *pKey) {

	if ( 0 == g_hPr)
		return EC_OKAY;


	if ( cTyp == 'P') {

		if ( !iFirstPointError)
			return EC_OKAY;

		iFirstPointError = FALSE;

	} else {

		if ( !iFirstError)
			return EC_OKAY;

		iFirstError = FALSE;
	}

	long i = 0;

			
	USES_CONVERSION;
	CComBSTR	strCaption;
	strCaption.LoadString(IDS_DISPLAYNAME);
	CComBSTR	strFormat;
	strFormat.LoadString(IDS_ERROROBJECT);

	TCHAR szText[_MAX_PATH];

	char cbBuffer[_MAX_PATH];

	if (NULL != DEX_GetDataSourceShortName (g_hPr, cbBuffer)) 
		wsprintf ( szText, W2A(strFormat),pKey,cbBuffer); // Keyxx = Name
			
	MessageBox (__hWndM,
		szText,
		W2A(strCaption),
		MB_OK | MB_ICONINFORMATION );


	return EC_OKAY;
}
//////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////
ErrCode SetExportPointKeyDescription( void) {

	if ( 0 == g_hPr)
		return EC_OKAY;

	long lMCode = 0;

	long i = 0;

	while ( i <= m_lNumberPointKey ) {
		if ( g_cKeyP[i][0] != '\0') {
			lMCode = DEX_GetMCodeFromFeatureNameEx (g_hPr,(LPTSTR)&g_cKeyP[i][0]);
			
			g_lKeyP[i] = DEX_MapHandleToMCode(lMCode);
//			g_lKeyP[i] = DEX_MapMCodeToHandle(g_hPr,lMCode);

			// Falls Attribut in Datenquwelle nicht definiert
			if ( g_lKeyP[i] == 0L) {
				USES_CONVERSION;
				CComBSTR	strCaption;
				strCaption.LoadString(IDS_DISPLAYNAME);
				CComBSTR	strFormat;
				strFormat.LoadString(IDS_ERRORFORMAT);

				TCHAR szText[_MAX_PATH];

				char cbBuffer[_MAX_PATH];

				if (NULL != DEX_GetDataSourceShortName (g_hPr, cbBuffer)) 
					wsprintf ( szText, W2A(strFormat),i+1,(LPTSTR) &g_cKeyP[i][0],cbBuffer); // Keyxx = Name
			
				MessageBox (__hWndM,
					szText,
					W2A(strCaption),
					MB_OK | MB_ICONINFORMATION );
			}


		}
		i++;
	}


	return EC_OKAY;
}
//////////////////////////////////////////////////////////////////////////////////////////


////////////Export GCA-Kurzcode für Punkte////////////////////////////////////////////////
static ErrCode ExportPolygisDatPunktMerkmal ( MFELD *MF, char * pOut) 
{

	if ( !pOut)
		return EC_NOSPACE;

	USES_CONVERSION;
	CComBSTR	strCode;
	strCode.LoadString(IDS_GCAKURZCODE);
	long lMCode = DEX_GetMCodeFromFeatureNameEx (g_hPr,W2A(strCode));
	long lRefMCode = DEX_MapHandleToMCode(lMCode);

	
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

		if (lRefMCode != MF -> MCode) {
			MF++;
			continue;		// UIdent wird extra ausgegeben
		}

	// eigentliche MerkmalsWertAusgabe
	//	DBASSERT(PolygisDatExportEinMerkmal (fh, locMTyp, MF -> MCode, MF -> MText));
		strcat (pOut, MF -> MText);

		strcat (pOut, "\t");

		MF++;           // nächstes Merkmal
	}

	return EC_OKAY;
}

//----------------------------------------------------------------------------------------
static ErrCode ExportPolygisDatMerkmal ( MFELD *MF, char * pOut) 
{

	if ( !pOut)
		return EC_NOSPACE;


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
	//	DBASSERT(PolygisDatExportEinMerkmal (fh, locMTyp, MF -> MCode, MF -> MText));
		strcat (pOut, MF -> MText);

		strcat (pOut, "\t");

		MF++;           // nächstes Merkmal
	}

	return EC_OKAY;
}

//-----------------------------------------------------------------------------------------
static ErrCode ExportRegistryMerkmal ( MFELD *OF, char * pOut) 
{

	if ( !pOut)
		return EC_NOSPACE;

	MFELD * MF;


	for ( long iCount = 1; iCount <= m_lNumberKey + 1; iCount ++ ) {

		MF = OF;

		long lMCode = g_lKey[iCount-1];

		if ( 0 == lMCode ) {
			if ( iCount == 1)
				SetErrorMasterKey( 'L', (char *) &g_cKey[iCount-1][0]);
			MF++;
			strcat (pOut, "\t");
			continue;		// UIdent wird extra ausgegeben
		}

		bool iNothing = true;

		while (MF -> MCode != 0) {		// für alle Merkmale
			short locMTyp = toupper (MF -> MTyp);

			if (locMTyp == 'B' || locMTyp == 'C') {		// #HK950720
			// Sicht- oder IdentMerkmal ist reingeraten
				MF++;
				continue;
			}

			if (lMCode != MF -> MCode) {
				MF++;
				continue;		// UIdent wird extra ausgegeben
			}

			// eigentliche MerkmalsWertAusgabe
			strcat (pOut, MF -> MText);

			strcat (pOut, "\t");

			iNothing = false;

//			MF++;           // nächstes Merkmal
			break;
		}

		if ( iCount == 1 && iNothing)
			SetErrorMasterKey( 'L', (char *) &g_cKey[iCount-1][0]);

		if (iNothing)
			strcat (pOut, "\t");


	}

	return EC_OKAY;
}

//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
static ErrCode ExportRegistryPunktMerkmal ( MFELD *OF, char * pOut) 
{

	if ( !pOut)
		return EC_NOSPACE;

	MFELD * MF;

	for ( long iCount = 1; iCount <= m_lNumberPointKey + 1; iCount ++ ) {

		MF = OF;

		long lMCode = g_lKeyP[iCount-1];

		if ( 0 == lMCode ) {
			if ( iCount == 1)
				SetErrorMasterKey( 'P', (char *) &g_cKeyP[iCount-1][0]);

			MF++;
			strcat (pOut, "\t");
			continue;		// UIdent wird extra ausgegeben
		}

		bool iNothing = true;

		while (MF -> MCode != 0) {		// für alle Merkmale
			short locMTyp = toupper (MF -> MTyp);

			if (locMTyp == 'B' || locMTyp == 'C') {		// #HK950720
			// Sicht- oder IdentMerkmal ist reingeraten
				MF++;
				continue;
			}

			if (lMCode != MF -> MCode) {
				MF++;
				continue;		// UIdent wird extra ausgegeben
			}

			// eigentliche MerkmalsWertAusgabe
			strcat (pOut, MF -> MText);

			strcat (pOut, "\t");

			iNothing = false;

//			MF++;           // nächstes Merkmal
			break;
		}

		if ( iCount == 1 && iNothing)
			SetErrorMasterKey( 'P', (char *) &g_cKeyP[iCount-1][0]);

		if (iNothing)
			strcat (pOut, "\t");


	}

	return EC_OKAY;
}

//-----------------------------------------------------------------------------------------
