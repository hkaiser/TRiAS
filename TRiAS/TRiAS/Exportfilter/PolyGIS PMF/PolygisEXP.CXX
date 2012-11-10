// Routinen zum schreiben des DIRIS-Austauschformates
// File: POLYGISEXP.CXX

#include "stdafx.h"
#include "PolygisPMFImpl.h"

#include <string.h>
#include <fcntl.h>
#include <io.h>
#include <stdlib.h>
#include <ctype.h>
#include "PMFExp.h"
#include <containr.hxx>
#include "PolygisDLG.hxx"

#include "PolygisTree.hxx"


#include <ERRINSTX.HXX>
#include <REGISTRX.HXX>

#if !defined(HUGE)
#if !defined(WIN32)
#define HUGE __huge
#else
#define HUGE
#endif // WIN32
#endif // HUGE


ResourceFile *pRF = NULL;

TR_OBJTree *g_Tree = NULL;

//---------------------------------------------------------------------------------

short iKeyLen = PMFKEYCOUNT + 1;


//OberThemenName
char cOberThemenName[80];

// ThemenName
char cThemenName[80];

//GruppenName
char cGruppeStrassen[80];
char cGruppeZusatz[80];
char cGruppenName[80];

DWORD dKeyLen = BNAKEYLEN;

char g_cKey [PMFKEYCOUNT][BNAKEYLEN];

long g_lKey[PMFKEYCOUNT] = { 0L,0L,0L,0L,0L,0L,0L,0L};
UINT PMFKEYFELD [PMFKEYCOUNT] = { IDS_PMFKEY01,IDS_PMFKEY02,IDS_PMFKEY03,IDS_PMFKEY04,IDS_PMFKEY05,IDS_PMFKEY06,IDS_PMFKEY07,IDS_PMFKEY08};

char UniqueIdent[_MAX_PATH];
short iNumberUnique = -1;

char g_cOrdnung[BNAKEYLEN];

char g_cSuffix[BNAKEYLEN];
char g_cMemo[BNAKEYLEN];
char g_cMemoSuffix[BNAKEYLEN];
char g_cMemoKlasse[_MAX_PATH];

char g_cGruppe1[BNAKEYLEN];
char g_cGruppe2[BNAKEYLEN];
char g_cKeyThema[BNAKEYLEN];

char PolyGIType[7] = {0,0,0,0,0,0,0};


char PMFArt [7][20] = {"Std.-Punkte","Std.-Strecken","Std.-Kreise","Std.-Texte","Std.-Bemaßungen","Std.-Polylinien","Std.-Flächen"};
char PMFStruc [7][20] = {"tPoint","tLine","tArc","tText","tMeter","tSeg","tPoly"};
char TRiASTyp [7][2] = {"P","K","K","T","M","L","F"};

char ParentRefClass[_MAX_PATH] = {"-"};

double ExportContainer[4] = { dMaxCont,dMinCont,dMaxCont,dMinCont};
long ExportPos = 0L;

// Registrierung
static LPCTSTR g_cbBNALocal	= TEXT("Software\\%s\\%s\\%s\\%s\\%s");
static LPCTSTR g_cbBNA	= TEXT("Software\\%s\\%s\\%s\\%s");



//XX	#define INLINE inline
extern "C" char *PASCAL DtoAFlt (char *, char *, double);

// lokale FunktionsPrototypen
static ErrCode PolygisPmfExportGeometrie (int fh, GSTRUCT &GS);
static ErrCode PolygisPmfExportLine (int fh, const char *lpStr = NULL);
static ErrCode PolygisPMFExportMerkmale (int fh, MFELD *MF); 

// PMF-Strukturen
//static ErrCode PolygisPMFExportHeaderInfo (int fh,LPCTSTR pParentClass,GSTRUCT &GS, MFELD *MF); 
static ErrCode PolygisPMFExportHeaderInfo (int fh,GSTRUCT &GS, MFELD *MF); 
static ErrCode PolygisPMFExportHeaderGIInfo (int fh,short iPTyp, MFELD *MF); 

static ErrCode PolygisPMFExportProjekt (int fh); 
static ErrCode PolygisPMFExportTypen (int fh,short Typ,MFELD *MF ); 
static ErrCode PolygisPMFExportEntity (int fh); 
static ErrCode PolygisPMFExportGroup (int fh); 
static ErrCode PolygisPMFExportLayer (int fh, short Typ); 
static ErrCode PolygisPMFExportObjekt (int fh); 
static ErrCode MerkmalsWertAusgabe ( short,long, MFELD *);

short PolygisGITyp ( long lONr );
void LayerText (int fh, char *pLayer,long lIdent);
bool ExportRegistry (void);
bool TypeDefined(short);
bool TypeDelete(void);
void SetExportContainer(void);
// KK021121
void SetKeyStandards ( void);
void DeleteKeyStandards (void);
void SetKeyInformation (long , UINT );
void SetPMFRegistryKeyData ( CCurrentUser * , long ,UINT );

int StoreTypInTree (long lIdent , short iTyp); 
int StoreInTree (long lIdent , const char *pWert, short iTyp);
int RetrieveFromTree (long lIdent);
char * RetrieveTypLayer(long,short);
void ResetTree (void); 

///////////////////////////////////////////////////////////////////////////////
// Map für MerkmalsCodes
typedef map<INT_PTR, os_string, less<INT_PTR> > CMCodeMap;
CMCodeMap g_MCodes;

///////////////////////////////////////////////////////////////////////////////


const int MAX_OKS_LENX = 32;

const int MAX_POLY_ATT = 30;

//  globale Variablen
HWND __hWndM;
UINT __DexCmd;
extern "C" {
UINT __DexxCmd;
}

extern "C" {
	#include <xtensnxx.h>   	// DEXX_MAINWINDOW
}

//  externe Variablen
extern "C" {
extern char pDLLName [_MAX_PATH];           // Puffer für DLL-Name
}

static char outBuff[1024];
static char tBuff[_MAX_PATH];

static char Layer[_MAX_PATH];
static short iGiTyp = FALSE;			// PolyGIS-Spezifik : Ebenname pro GI-Typ eindeutig - nur erste GI!!
static short iFirstData = TRUE;
static long lUIdent = -1L;

static short iFirstType = TRUE;
static short iFirstReg = TRUE;
static short iNoKey = TRUE;			// Kein Registry-Eintrag
static short iFirstHeader = TRUE;
static short iFirstZusatz = TRUE;	// Gruppe2 noch nicht definiert
static short iFirstOKS = TRUE;		// Erster Klassenwechsel

HPROJECT g_hPr = 0;

#if !defined(DELETE_OBJ)
#define DELETE_OBJ(x)	if(!(x)){}else{delete(x);x=NULL;}
#define DELETE_VEC(x)	if(!(x)){}else{delete[](x);x=NULL;}
#endif // DELETE_OBJ

// KK001023

ErrCode ExportKeyDescription( long lMCode, char *pBuf) {

	HPROJECT hPr = DEX_GetFeatureProject(lMCode) ;


	if (0 == hPr || g_hPr != hPr) 
		return EC_OKAY;


	long i = 0;
	while ( i < PMFKEYCOUNT ) {
		if ( strcmp ((LPTSTR) &g_cKey[i][0],(LPTSTR)pBuf ) == 0 ) {
			g_lKey[i] = lMCode;
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

//KK021121

	long i = 0;

	while ( i < PMFKEYCOUNT ) {


		if ( g_cKey[i][0] != '\0') {

			lMCode = DEX_GetMCodeFromFeatureNameEx (g_hPr,(LPTSTR)&g_cKey[i][0]);
			
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

//ErrCode ExportIdentDescription(OFSTRUCT &of, const char* lpszOKS, const char* lpszShortDescription, const char* lpszLongDescription, const long lVisType, const VISINFO* pVI ) {
ErrCode ExportIdentDescription(OFSTRUCT &of, const char* lpszOKS, const char* lpszShortDescription, const char* lpszLongDescription, const long lVisType, const VISINFO* pVI , long lIdent) {


	return EC_OKAY;
}

ErrCode ExportMerkmalDescription(long lMCode, char *pbuf, short iTyp,short iLen ) {

// Registry auslesen
	if ( iFirstReg ) {	
		iNoKey = ExportRegistry();
		iFirstReg = FALSE;
		TypeDelete();					// StandardTypen zurücksetzen
	}


   	// aktive Datenquelle bsorgen
     g_hPr = DEX_GetDataSourceHandle();
     _ASSERTE(NULL != g_hPr);


	ExportKeyDescription(lMCode, pbuf) ;

CMCodeMap::iterator it = g_MCodes.find(lMCode);

	if (it == g_MCodes.end())
		g_MCodes.insert(CMCodeMap::value_type(lMCode, os_string(pbuf)));

	return EC_OKAY;
}

// Begin des DatenExports -----------------------------------------------------
//ErrCode EXPORTFLT PASCAL PolygisPmfExportBegin (char *lpFileName, OFSTRUCT &of, OutMode OutFlag, HWND hWnd) 
ErrCode ExportBegin (char *lpFileName, OFSTRUCT &of, OutMode OutFlag, HWND hWnd, const char* lpszDatasource ) 
{
ErrCode EC;


//  Resource-File-Objekt init.
// 
	if (!pRF)
		pRF = new ResourceFile ((char *) pDLLName);
	if (!pRF)
		return EC = EC_NOMEMORY;


// FensterHandle merken
	USES_CONVERSION;
	CComBSTR	strDEXMessage;
	strDEXMessage.LoadString(IDS_DEXMESSAGE);
	__hWndM = hWnd;
//XX		__DexCmd = RegisterWindowMessage (ResString (IDS_DEXMESSAGE, 30));
	__DexCmd = RegisterWindowMessage(W2A(strDEXMessage));


// Datei anlegen
register int fh;        // File Handle
register int OpenMode = OF_WRITE;

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
//XX	ErrCode EXPORTFLT PASCAL PolygisPmfExportComment (OFSTRUCT &, const char *) 
ErrCode ExportComment (OFSTRUCT &, const char *) 
{
	return EC_OKAY;
}

// Ausgeben der HeaderInformation ---------------------------------------------
//XX	ErrCode EXPORTFLT PASCAL PolygisPmfExportHeader (OFSTRUCT &, const char *) 
ErrCode ExportHeader (OFSTRUCT &of, const char * lpszDatasource) 
{


	return EC_OKAY;
}

// Ausgeben der BeschreibungsInformation --------------------------------------
//XX	ErrCode EXPORTFLT PASCAL PolygisPmfExportDescription (OFSTRUCT &, const char *, const char *) 
ErrCode ExportDescription (OFSTRUCT &, const char *, const char *) 
{
	return EC_OKAY;
}

ErrCode ExportDescriptionEx(OFSTRUCT &, LPCSTR lpKeyInfo, LPCSTR lpDescString, DWORD dwStyle )
{

	lUIdent = atol (lpDescString);

	return EC_OKAY;
}

// Ausgeben der TrailerInformation --------------------------------------------
//XX	ErrCode EXPORTFLT PASCAL PolygisPmfExportTrailer (OFSTRUCT &, const char *) 
ErrCode ExportTrailer (OFSTRUCT &of, const char *lpTrailerString)
{
	return EC_OKAY;
}

////////////////////////////////////////////////////////////////////////////////////////

void SetUniqueIdent(long lONr)
{

ulong ulMCode = DEX_GetUniqueIdentMCodeEx (DEX_GetObjectProject(lONr));

TARGETMERKMAL TM;

	INITSTRUCT (TM, TARGETMERKMAL);
	TM.lTarget = (LPARAM)lONr;
	TM.lMCode = ulMCode;
	TM.iTTyp = TT_Objekt;		//nur von Objekten !!!

	char *pMText = new char [_MAX_PATH];
	*pMText = NULL;
	TM.pMText = pMText;
	TM.imaxLen = _MAX_PATH-1;


	if ( DEX_GetTextMerkmal (TM)) {

		if ( NULL != *pMText) {
			strcpy (UniqueIdent,pMText);
			DELETE_OBJ(pMText);
			return;
		}

	} else {		// Falls kein UID existiert
		char cbBuffer[_MAX_PATH];

		if (NULL != DEX_GetDataSourceShortName (g_hPr, cbBuffer)) 
			wsprintf ( pMText,"%s_%ld",cbBuffer,lONr);
		strcpy (UniqueIdent,pMText);
	}
	DELETE_OBJ(pMText);

}



// Ausgabe eines Geometrieobjektes mit Merkmalsinformation --------------------
//XX	ErrCode EXPORTFLT PASCAL PolygisPmfExportData (OFSTRUCT &of, GSTRUCT &GS, MFELD *MF, RSTRUCT *, char *pUIdent) 
ErrCode ExportData (OFSTRUCT &of, GSTRUCT &GS, MFELD *MF, RSTRUCT *, LPCTSTR pUIdent, LPCTSTR lpszGUID, LPCTSTR pParentClass )
{

register ErrCode RC;

register int fh;        // DateiHandle

ErrCode EC;



// Datei eröffnen
	if ((fh = OpenFile (NULL, &of, OF_REOPEN+OF_WRITE)) < 0)
	// Fehler: kann Datei nicht eröffnen
		return EC_NOFILE;
	_llseek (fh, 0L, SEEK_END);
	setmode (fh, O_TEXT);

	iFirstOKS = FALSE;

	if ( strcmp ( pParentClass, ParentRefClass) != 0 ) {

		iFirstData = TRUE;

		HPROJECT hPr = DEX_GetObjectsProject(GS.Id);

		if ( ParentRefClass[0] == '-' || hPr != g_hPr) {

			g_hPr = hPr;
			SetExportKeyDescription();		// Key-Definitionen überprüfen
		}

		strcpy ( ParentRefClass,pParentClass);
		iFirstOKS = TRUE;

	}

	if ( iFirstHeader) {


		if ( iNoKey) {		// Keine Registry
			// ThemenName vordefinieren-Projektname
			char cbBuffer[_MAX_PATH];

			if (NULL != DEX_GetActiveProject (cbBuffer)) {

				char *cptr = strrchr (cbBuffer,'\\');
				if (cptr) {
					strcpy(cThemenName,cptr+1);
					char *eptr = strrchr(cThemenName,'.');
					if (eptr)
						*eptr = NULL;
				}
			}
	

			// GruppenName vordefinieren-Datenquelle
			HPROJECT hPr = DEX_GetObjectsProject(GS.Id);

			DEX_GetDataSourceShortName (hPr, cGruppenName);

			// OberThemenName vordefinieren-Projektname
			DEX_GetDataSourceShortName (hPr, cOberThemenName);
		}


		// Dialog Thema
		USES_CONVERSION;
		CComBSTR	strDEXMessage;
		strDEXMessage.LoadString(IDS_DEXXMESSAGE);
		__DexxCmd = RegisterWindowMessage(W2A(strDEXMessage));

	//  Elternfenster bestimmen
		Window *pParent = (Window *) SendMessage (__hWndM, __DexxCmd,
											   DEXX_MAINWINDOW, 0L);

		if (!pParent)
			return EC_NODEXMESSAGE;
		
	//	Dialog zur zum Einstellen der Export-Parameter	           

			CConfigDlg CDlg (pParent ,cOberThemenName,cThemenName,cGruppenName);

			CDlg.Show (Centre);
			if ( CDlg.Result()) {
				
				if ( CDlg.GetOberThema())
					strcpy ( cOberThemenName, CDlg.GetOberThema());

				if ( CDlg.GetThema())
					strcpy ( cThemenName, CDlg.GetThema());
				
				if ( CDlg.GetGruppe())
					strcpy ( cGruppenName, CDlg.GetGruppe());
			}

// Falls kein OberThema angegeben - Projektname

			if ( cOberThemenName[0] == '\0') {
				HPROJECT hPro = DEX_GetObjectsProject(GS.Id);

				// OberThemenName vordefinieren-Projektname
				DEX_GetDataSourceShortName (hPro, cOberThemenName);
			}

// KK020603
// ProjektKopf
			SetExportContainer();

			if ((EC = PolygisPMFExportProjekt ( fh)) < 0) {
				_lclose (fh);
				return EC;
			}


	}

// wenn noch kein PMF-Header
	if (iFirstData ) {

//		TypeDelete();

		if ((EC = PolygisPMFExportHeaderInfo ( fh,GS, MF)) < 0) {
			_lclose (fh);
			return EC;
		}

	}
	iFirstData = FALSE;

//--------------------------------------------------------------------------------

// GeometrieTyp feststellen

	short iPTyp = PolygisGITyp ( GS.ON);

	g_hPr = DEX_GetObjectProject(GS.ON);


	UniqueIdent[0] = '\0';

// UniqueIdent merken
	if ( pUIdent)
		strcpy(UniqueIdent,pUIdent);
	else
		SetUniqueIdent(GS.ON);



	StoreInTree (GS.Id ,Layer, iPTyp);

	if ( !TypeDefined(iPTyp)) {

		if ( iGiTyp ) {

			if ((EC = PolygisPMFExportHeaderGIInfo (fh,iPTyp, MF)) < 0) {
				_lclose (fh);
				return EC;
			}
		} else {
			char *pTypLayer = RetrieveTypLayer(GS.Id,iPTyp);
			if (pTypLayer)
				strcpy(Layer,pTypLayer);

			if ((EC = PolygisPMFExportHeaderGIInfo (fh,iPTyp, MF)) < 0) {
				_lclose (fh);
				return EC;
			}
		}

	}

// Geometrieinformation ausgeben

try {

	wsprintf (tBuff, dObjektKopf,GS.ON,PMFStruc[iPTyp]);
	strcpy (outBuff, tBuff);
	DBASSERT (PolygisPmfExportLine (fh, outBuff));

	if ((EC = PolygisPmfExportGeometrie (fh, GS)) < 0) {
		_lclose (fh);
		return EC;
	}


// Merkmale

	char *ptr = &outBuff[0];
	strcpy (outBuff, dTab);
	ptr = ptr + 2;



	if (iGiTyp)
		wsprintf (tBuff, dMerkmalsKopf0,Layer,TRiASTyp[iPTyp]);
	else
		wsprintf (tBuff, dMerkmalsKopf,Layer);

	strcpy (ptr, tBuff);
	DBASSERT (PolygisPmfExportLine (fh, outBuff));

	strcpy (ptr, dMerkmalsKopf1);
	DBASSERT (PolygisPmfExportLine (fh, outBuff));

	if ((EC = PolygisPMFExportMerkmale (fh,MF)) < 0) {
		_lclose (fh);
		return EC;
	}

	strcpy (ptr, dEnd);
	DBASSERT (PolygisPmfExportLine (fh, outBuff));

	strcpy (outBuff, dEnd);
	DBASSERT (PolygisPmfExportLine (fh, outBuff));

} catch ( ... ) {

	USES_CONVERSION;
	CComBSTR	strCaption;
	strCaption.LoadString(IDS_DISPLAYNAME);
	CComBSTR	strErr;
	strErr.LoadString(IDS_PMFERROR);

	MessageBox (__hWndM,
		W2A(strErr),
		W2A(strCaption),
		MB_OK | MB_ICONINFORMATION );
}

return (ErrCode)_lclose (fh);
}
////////////////////////////////////////////////////////////////////////////

// Ende des DatenExports ------------------------------------------------------
//XX	ErrCode EXPORTFLT PASCAL PolygisPmfExportEnd (OFSTRUCT &) 
ErrCode ExportEnd (OFSTRUCT &of)
{ 
	g_MCodes.clear();	// MCodemap leeren

// Datei eröffnen

register int fh;        // DateiHandle

ErrCode EC;
	if ((fh = OpenFile (NULL, &of, OF_REOPEN+OF_WRITE)) < 0)
	// Fehler: kann Datei nicht eröffnen
		return EC_NOFILE;
	_llseek (fh, 0L, SEEK_END);
	setmode (fh, O_TEXT);

// ProjektKopf

	if ((EC = PolygisPMFExportProjekt ( fh)) < 0) {
		_lclose (fh);
		return EC;
	}

	ResetTree();

//-----------------------------------------------------------------------------
	// Standardeinstellungen
	iGiTyp = FALSE;			// PolyGIS-Spezifik : Ebenname pro GI-Typ eindeutig - nur 1. GI!!
	iFirstData = TRUE;
	lUIdent = -1L;

	iFirstType = TRUE;
	iFirstOKS = TRUE;

	iFirstReg = TRUE;
	iNoKey = TRUE;			// Kein Registry-Eintrag
	iFirstHeader = TRUE;
	iFirstZusatz = TRUE;	// Gruppe2 noch nicht definiert

//-----------------------------------------------------------------------------
	return EC_OKAY;
}

// Abbrechen des Datenexportes ------------------------------------------------
//XX	ErrCode EXPORTFLT PASCAL PolygisPmfExportBreak (OFSTRUCT &of) 
ErrCode ExportBreak (OFSTRUCT &of)
{ 
// Datei löschen, damit keine Reste bleiben
	OpenFile (of.szPathName, &of, OF_DELETE);
	g_MCodes.clear();	// MCodemap leeren

	ResetTree();
	
	return EC_OKAY; 
} 

//XX	}	// extern "C"

// Statische Funktionen -------------------------------------------------------

// PMF-Header  - pro Klasse 
//static ErrCode PolygisPMFExportHeaderInfo (int fh,LPCTSTR pParentClass, GSTRUCT &GS, MFELD *MF)
static ErrCode PolygisPMFExportHeaderInfo (int fh,GSTRUCT &GS, MFELD *MF)

{

ErrCode EC;

// Gruppen unterscheiden
	LayerText (fh,&Layer[0],GS.Id);				// Layer für Merkmale merken


// Allgemeine DatenTypen- nur einmal am Anfang

	iFirstType = FALSE;

	// GeometrieTyp feststellen

	short iPTyp = PolygisGITyp ( GS.ON);

	if ( !TypeDefined(iPTyp)) {

		iFirstType = TRUE;

		if ((EC = PolygisPMFExportTypen ( fh, iPTyp,MF)) < 0) {	// STD-Definitionen mit AliasNamen
			_lclose (fh);
			return EC;
		}

	} else {
// Gleicher GI-Typ , aber andere Klasse
		if ( iFirstOKS ) {
			iFirstType = TRUE;
		}

	}




// Nur einmal pro Projekt !!!
	if ( iFirstHeader) {

		iFirstHeader = FALSE;

	// EntityKopf
		if ((EC = PolygisPMFExportEntity ( fh)) < 0) {
			_lclose (fh);
			return EC;
		}


	// Group
	
		if ((EC = PolygisPMFExportGroup ( fh)) < 0) {
			_lclose (fh);
			return EC;
		}


	}



// UserLayer
// Hier GI-Typen beachten !!!

	if ( iFirstType ) {
 

		if ((EC = PolygisPMFExportLayer ( fh,iPTyp)) < 0) {
			_lclose (fh);
			return EC;
		}
	}



return EC_OKAY; 

}

//-----------------------------------------------------------------------------
// PMF-Einträge  - pro GITyp einer Klasse 
static ErrCode PolygisPMFExportHeaderGIInfo (int fh,short iPTyp, MFELD *MF)

{

ErrCode EC;

	iFirstType = TRUE;

// Allgemeine DatenTypen- nur einmal am Anfang

	if ((EC = PolygisPMFExportTypen ( fh, iPTyp,MF)) < 0) {	// STD-Definitionen mit AliasNamen
		_lclose (fh);
		return EC;
	}


// UserLayer
// Hier GI-Typen beachten !!!

	if ( iFirstType ) {


		if ((EC = PolygisPMFExportLayer ( fh,iPTyp)) < 0) {
			_lclose (fh);
			return EC;
		}
	}



return EC_OKAY; 

}


//-----------------------------------------------------------------------------


//PMF-Struktur
static ErrCode PolygisPMFExportProjekt (int fh)
{

register ErrCode RC;

	char Buff[4][20];
	char *dFormat = "%11.3f";

// ProjektKopf
// KK020603

	if ( iFirstHeader ) {

		wsprintf ( tBuff,dProjektKopf,cOberThemenName);
		strcpy (outBuff, tBuff);
		DBASSERT (PolygisPmfExportLine (fh, outBuff));



		for ( int i = 0; i < 4; i++ ) 
			DtoAFlt (Buff[i], dFormat, ExportContainer[i]);
	
		wsprintf ( tBuff,dProjekt1,Buff[0],Buff[2],Buff[1],Buff[3]);
		strcpy (outBuff, tBuff);

		ExportPos = _llseek (fh, 0L, SEEK_CUR);                 // Anz.-Pos.ExportContainer merken

		DBASSERT (PolygisPmfExportLine (fh, outBuff));

		strcpy (outBuff,dEnd );

		DBASSERT (PolygisPmfExportLine (fh, outBuff));

	} else {

		for ( int i = 0; i < 4; i++ ) 
			DtoAFlt (Buff[i], dFormat, ExportContainer[i]);
	
		wsprintf ( tBuff,dProjekt1,Buff[0],Buff[2],Buff[1],Buff[3]);
		strcpy (outBuff, tBuff);

	    _llseek (fh, ExportPos, SEEK_SET);
		DBASSERT (PolygisPmfExportLine (fh, outBuff));

	    _llseek (fh, 0L, SEEK_END);     // File-Ende

	}


	return EC_OKAY;
}


//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

static ErrCode PolygisPMFExportEntity (int fh)
{

register ErrCode RC;


	wsprintf ( tBuff,dEntityKopf,cThemenName);
	strcpy (outBuff, tBuff);
	DBASSERT (PolygisPmfExportLine (fh, outBuff));

	wsprintf ( tBuff,dEntity0,cOberThemenName);
	strcpy (outBuff,tBuff );
	DBASSERT (PolygisPmfExportLine (fh, outBuff));

	strcpy (outBuff,dEnd );
	DBASSERT (PolygisPmfExportLine (fh, outBuff));


return EC_OKAY;
}

//-----------------------------------------------------------------------------

static ErrCode PolygisPMFExportGroup (int fh)
{

register ErrCode RC;


	wsprintf ( tBuff,dGroupKopf,cGruppenName);
	strcpy (outBuff, tBuff);
	DBASSERT (PolygisPmfExportLine (fh, outBuff));

	wsprintf ( tBuff,dGroup0,cThemenName);
	strcpy (outBuff, tBuff);
	DBASSERT (PolygisPmfExportLine (fh, outBuff));

	strcpy (outBuff,dEnd );
	DBASSERT (PolygisPmfExportLine (fh, outBuff));


return EC_OKAY;
}

//-----------------------------------------------------------------------------

static ErrCode PolygisPMFExportLayer (int fh, short iPMFTyp)
{

// Hier werden GI-Typen verarbeitet 

register ErrCode RC;


	if (iGiTyp)
		wsprintf ( tBuff,dLayerKopf,Layer,TRiASTyp[iPMFTyp]);
	else
		wsprintf ( tBuff,dLayerKopfN,Layer);

	strcpy (outBuff, tBuff);
	DBASSERT (PolygisPmfExportLine (fh, outBuff));


	wsprintf ( tBuff,dLayer0,iPMFTyp);
	strcpy (outBuff,tBuff );
	DBASSERT (PolygisPmfExportLine (fh, outBuff));

	wsprintf ( tBuff,dLayer1,cThemenName);
	strcpy (outBuff, tBuff);
	DBASSERT (PolygisPmfExportLine (fh, outBuff));

	wsprintf ( tBuff,dLayer2,cGruppenName);
	strcpy (outBuff, tBuff);
	DBASSERT (PolygisPmfExportLine (fh, outBuff));

	wsprintf ( tBuff,dLayer3,PMFArt[iPMFTyp]);
	strcpy (outBuff,tBuff );
	DBASSERT (PolygisPmfExportLine (fh, outBuff));

	strcpy (outBuff,dEnd );
	DBASSERT (PolygisPmfExportLine (fh, outBuff));


return EC_OKAY;
}
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
static ErrCode PolygisPMFExportTypen (int fh, short iPMFTyp,MFELD *MF)
{

// Hier werden allgemeine DatenTypen verarbeitet 

register ErrCode RC;


	wsprintf ( tBuff,dTypenKopf,PMFArt[iPMFTyp]);
	strcpy (outBuff, tBuff);
	DBASSERT (PolygisPmfExportLine (fh, outBuff));


	wsprintf ( tBuff,dTypen0,iPMFTyp);
	strcpy (outBuff,tBuff );
	DBASSERT (PolygisPmfExportLine (fh, outBuff));


// Hier Key-Werte setzen

	short iFirst = 1;	// Key01


	//*--------------------------------------------------------
	if ( iNoKey ) {		// Keine Registry - volle Merkmale
	while (MF -> MCode != 0) {		// für alle Merkmale

		short locMTyp = toupper (MF -> MTyp);

		if (locMTyp == 'B' || locMTyp == 'C') {	
		// Sicht- oder IdentMerkmal ist reingeraten
			MF++;
			continue;
		}

		if (lUIdent == MF -> MCode) {
			MF++;
			continue;		// UIdent wird extra ausgegeben
		}

	// eigentliche MerkmalsWertAusgabe

		wsprintf ( tBuff,dTypenKey,iFirst);
		strcpy (outBuff,tBuff );
		DBASSERT (PolygisPmfExportLine (fh, outBuff));

		long lMCode = MF -> MCode;

		CMCodeMap::iterator it = g_MCodes.find(lMCode);

		if (it != g_MCodes.end()) {

			wsprintf ( tBuff,dTypenAliasEx,iFirst,(*it).second.c_str());
			strcpy (outBuff,tBuff );
			DBASSERT (PolygisPmfExportLine (fh, outBuff));

			wsprintf ( tBuff,dTypenShortEx,iFirst,(*it).second.c_str());
			strcpy (outBuff,tBuff );
			DBASSERT (PolygisPmfExportLine (fh, outBuff));


		} else {
			wsprintf ( tBuff,dTypenAlias,iFirst);
			strcpy (outBuff,tBuff );
			DBASSERT (PolygisPmfExportLine (fh, outBuff));

			wsprintf ( tBuff,dTypenShort,iFirst);
			strcpy (outBuff,tBuff );
			DBASSERT (PolygisPmfExportLine (fh, outBuff));
		}

		wsprintf ( tBuff,dTypenFld,iFirst);
		strcpy (outBuff,tBuff );
		DBASSERT (PolygisPmfExportLine (fh, outBuff));

		iFirst++;

		MF++;           // nächstes Merkmal
	}

//------------------------------------------------------------*/
	} else {
	// eigentliche MerkmalsWertAusgabe Key01 bis Key07

	for ( iFirst = 1; iFirst < iKeyLen; iFirst++ ) {		// für alle Merkmale


	// eigentliche MerkmalsWertAusgabe

		wsprintf ( tBuff,dTypenKey,iFirst);
		strcpy (outBuff,tBuff );
		DBASSERT (PolygisPmfExportLine (fh, outBuff));

// Ist Merkmalskode
		long lMCode = g_lKey[iFirst-1];


		CMCodeMap::iterator it = g_MCodes.find(lMCode);

		if (it != g_MCodes.end()) {

			wsprintf ( tBuff,dTypenAliasEx,iFirst,(*it).second.c_str());
			strcpy (outBuff,tBuff );
			DBASSERT (PolygisPmfExportLine (fh, outBuff));

			wsprintf ( tBuff,dTypenShortEx,iFirst,(*it).second.c_str());
			strcpy (outBuff,tBuff );
			DBASSERT (PolygisPmfExportLine (fh, outBuff));


		} else {
			wsprintf ( tBuff,dTypenAlias,iFirst);
			strcpy (outBuff,tBuff );
			DBASSERT (PolygisPmfExportLine (fh, outBuff));

			wsprintf ( tBuff,dTypenShort,iFirst);
			strcpy (outBuff,tBuff );
			DBASSERT (PolygisPmfExportLine (fh, outBuff));
		}

		wsprintf ( tBuff,dTypenFld,iFirst);
		strcpy (outBuff,tBuff );
		DBASSERT (PolygisPmfExportLine (fh, outBuff));

	}	



	for ( short i = iFirst; i < MAX_POLY_ATT + 1 ; i++ ) {


		wsprintf ( tBuff,dTypenKey,i);
		strcpy (outBuff,tBuff );
		DBASSERT (PolygisPmfExportLine (fh, outBuff));


		wsprintf ( tBuff,dTypenAlias,i);
		strcpy (outBuff,tBuff );
		DBASSERT (PolygisPmfExportLine (fh, outBuff));

		wsprintf ( tBuff,dTypenShort,i);
		strcpy (outBuff,tBuff );
		DBASSERT (PolygisPmfExportLine (fh, outBuff));

		wsprintf ( tBuff,dTypenFld,i);
		strcpy (outBuff,tBuff );
		DBASSERT (PolygisPmfExportLine (fh, outBuff));
	}


	} //----------------Nokey-else


	strcpy (outBuff,dEnd );
	DBASSERT (PolygisPmfExportLine (fh, outBuff));

//////////////////////////////////////////////////////////////////

return EC_OKAY;
}//-----------------------------------------------------------------------------

// Merkmale ausgeben

static ErrCode PolygisPMFExportMerkmale (int fh, MFELD *MF) 
{

	register ErrCode RC;

	if ( NULL == MF)
		return EC_OKAY;


	char *ptr = &outBuff[0];
	strcpy (outBuff, dTab);
	ptr = ptr + 2;

	short iCount = 1;


	if ( iNoKey) {
	//*----

	while (MF -> MCode != 0) {		// für alle Merkmale

	short locMTyp = toupper (MF -> MTyp);

		if (locMTyp == 'B' || locMTyp == 'C') {	
		// Sicht- oder IdentMerkmal ist reingeraten
			MF++;
			continue;
		}


	// eigentliche MerkmalsWertAusgabe

		char oBuff[_MAX_PATH];
		OemToChar ( (LPCTSTR) MF->MText,(LPTSTR)oBuff);

		if ( strlen  (oBuff) > POLYGISKEYLEN)				// PolyGIS ist in allem zu kurz geraten
			oBuff[POLYGISKEYLEN] = '\0';

		wsprintf (tBuff, dMerkmal,iCount,oBuff);
		strcpy (ptr, tBuff);
		DBASSERT (PolygisPmfExportLine (fh, outBuff));
		iCount++;
		MF++;           // nächstes Merkmal
	}

//  ----------------------------------------*/
	} else {



/////////////////////////////////////////////////////////////////

		for ( iCount = 1; iCount < iKeyLen; iCount ++ ) {


		MerkmalsWertAusgabe ( iCount,g_lKey[iCount-1],MF);

			strcpy (ptr, tBuff);
			DBASSERT (PolygisPmfExportLine (fh, outBuff));

		}


	} // iNokey - else

return EC_OKAY;
}
//-----------------------------------------------------------------------------
static ErrCode MerkmalsWertAusgabe ( short iCount,long lMCode, MFELD *MF) 
{

	if ( lMCode == 0L) {
		wsprintf (tBuff, dMerkmal,iCount," ");
		return EC_OKAY;
	}

	while (MF -> MCode != 0) {		// für alle Merkmale

	short locMTyp = toupper (MF -> MTyp);

		if (locMTyp == 'B' || locMTyp == 'C') {	
		// Sicht- oder IdentMerkmal ist reingeraten
			MF++;
			continue;
		}


		if (lMCode != MF -> MCode) {
			MF++;
			continue;		// UIdent wird extra ausgegeben
		}

	// eigentliche MerkmalsWertAusgabe

		char oBuff[_MAX_PATH];

		OemToChar ( (LPCTSTR) MF->MText,(LPTSTR)oBuff);


		if ( strlen  (oBuff) > POLYGISKEYLEN)				// PolyGIS ist in allem zu kurz geraten
			oBuff[POLYGISKEYLEN] = '\0';

		wsprintf (tBuff, dMerkmal,iCount,oBuff);
		return EC_OKAY;           // nächstes Merkmal
	}

	if ( iCount == iNumberUnique) {

		char oBuff[_MAX_PATH];

		OemToChar ( UniqueIdent,(LPTSTR)oBuff);

		wsprintf (tBuff, dMerkmal,iCount,oBuff);
		return EC_OKAY;           // nächstes Merkmal

	}

	wsprintf (tBuff, dMerkmal,iCount," ");

	return EC_OKAY;

}

//-----------------------------------------------------------------------------

// Geometrieinformation ausgeben
static ErrCode PolygisPmfExportGeometrie (int fh, GSTRUCT &GS) 
{
register ErrCode RC;
long sumIndex = 0;
long lCount = 0L;

double xEnd, yEnd;
char Buff[40];
char *dFormat = "%11.3f";

	// GSIZE enthält Gesamtanzahl
	lCount = GS.GSize;

	if (GS.Typ == OT_FLAECHE ) {
		lCount = 0;
		for (short iKontur = 0; GS.cnt[iKontur] != 0; iKontur++) {
			lCount = lCount + GS.cnt[iKontur];
		}
		lCount = lCount + iKontur - 1;
	}


	wsprintf (tBuff, dObjektCount,lCount);	// Koordinatenanzahl
	strcpy (outBuff, tBuff);
	// Geometriezeile ausgeben
	DBASSERT (PolygisPmfExportLine (fh, outBuff));

	char *ptr;

	for (short iKontur = 0; GS.cnt[iKontur] != 0; iKontur++) {
	// für alle Konturen

		ptr = &outBuff[0];

		strcpy (outBuff, dTab);
		ptr = ptr + 2;

		for (long actIndex = 0; 
		     actIndex < GS.cnt[iKontur];
		     actIndex++, sumIndex++) {

		// Geometriezeile generieren

			strcpy (ptr, dKoordinatenKopf);
		// Geometriezeile ausgeben
			DBASSERT (PolygisPmfExportLine (fh, outBuff));

			DtoAFlt (Buff, dFormat, ((double HUGE *)GS.x)[sumIndex]);
			wsprintf (tBuff, dKoordinatenR, Buff);
			strcpy (ptr, tBuff);
		// Geometriezeile ausgeben
			DBASSERT (PolygisPmfExportLine (fh, outBuff));

			DtoAFlt (Buff, dFormat, ((double HUGE *)GS.y)[sumIndex]);
			wsprintf (tBuff, dKoordinatenH, Buff);
			strcpy (ptr, tBuff);
		// Geometriezeile ausgeben
			DBASSERT (PolygisPmfExportLine (fh, outBuff));


			strcpy (ptr, dEnd);
		// Geometriezeile ausgeben
			DBASSERT (PolygisPmfExportLine (fh, outBuff));


// Gi für Container

			if ( ExportContainer[0] > ((double HUGE *)GS.x)[sumIndex] )
				ExportContainer[0] = ((double HUGE *)GS.x)[sumIndex];
			if ( ExportContainer[1] < ((double HUGE *)GS.x)[sumIndex] )
				ExportContainer[1] = ((double HUGE *)GS.x)[sumIndex];
			if ( ExportContainer[2] > ((double HUGE *)GS.y)[sumIndex] )
				ExportContainer[2] = ((double HUGE *)GS.y)[sumIndex];
			if ( ExportContainer[3] < ((double HUGE *)GS.y)[sumIndex] )
				ExportContainer[3] = ((double HUGE *)GS.y)[sumIndex];

		}

		if (iKontur == 0) {
		// Endpunkt der Außenkontur merken
			xEnd = ((double HUGE *)GS.x)[actIndex-1];
			yEnd = ((double HUGE *)GS.y)[actIndex-1];

		} else {
		// nochmal Endpunkt der Außenkontur ausgeben

			ptr = &outBuff[0];
			strcpy (outBuff, dTab);
			ptr = ptr + 2;

		// Geometriezeile generieren

			strcpy (ptr, dKoordinatenKopf);
		// Geometriezeile ausgeben
			DBASSERT (PolygisPmfExportLine (fh, outBuff));

			DtoAFlt (Buff, dFormat, xEnd);
			wsprintf (tBuff, dKoordinatenR, Buff);
			strcpy (ptr, tBuff);
		// Geometriezeile ausgeben
			DBASSERT (PolygisPmfExportLine (fh, outBuff));


			DtoAFlt (Buff, dFormat, yEnd);
			wsprintf (tBuff, dKoordinatenH, Buff);
			strcpy (ptr, tBuff);
		// Geometriezeile ausgeben
			DBASSERT (PolygisPmfExportLine (fh, outBuff));

			strcpy (ptr, dEnd);
		// Geometriezeile ausgeben
			DBASSERT (PolygisPmfExportLine (fh, outBuff));

		}


	}


return EC_OKAY;
}

//-----------------------------------------------------------------------
static ErrCode PolygisPmfExportLine (int fh, const char *pLine) 
{
// Ausgabe der Zeile
	if (pLine != NULL) {
	UINT iLen = strlen (pLine);

		if (_lwrite (fh, (char *)pLine, iLen) != iLen)
			return EC_NOSPACE;
	} 
// NewLine ausgeben
char *cptr = "\r\n";		// CR,LF

	if (_lwrite (fh, cptr, 2) != 2)
		return EC_NOSPACE;            

return EC_OKAY;
}
//------------------------------------------------------------------------

short PolygisGITyp ( long lONr ) {


	short iGTyp = DEX_GetObjectType (lONr);

	if ( iGTyp == OGPunkt)
		return PMFPunkt;

	if ( iGTyp == OGLinie)
		return PMFPolyLinie;

	if ( iGTyp == OGFlaeche)
		return PMFFlaeche;

	if ( iGTyp == OGKreis)
		return PMFKreis;

	if ( iGTyp == OGText)
		return PMFText;

	return -1;

}
//---------------------------------------------------------------------------
void LayerText (int fh, char *pLayer,long lIdent) {

	if (!pLayer)
		return;

	ErrCode EC;
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

	if ( !iNoKey) {		// Registry ausgewertet
		strcpy ( cGruppenName,cGruppeStrassen);

		if ( g_cMemoKlasse[0] != '\0') {		// MemoSuffix

			int iLenM = strlen (g_cMemoKlasse);
			int iLen = strlen (pLayer);

			if (iLen > iLenM) {
				char * ptr = pLayer;
				ptr = ptr + ( iLen-iLenM);
				if ( strcmp(ptr,g_cMemoKlasse) == 0 ) {
					strcpy (cGruppenName,cGruppeZusatz);
					if ( iFirstZusatz) {
						iFirstZusatz = FALSE;
	
						if ((EC = PolygisPMFExportGroup ( fh)) < 0) {
							_lclose (fh);
							return;
						}

					}

				}


			}
		}
	}

	return ;

}
//-------------------------------------------------------------------------------
bool ExportRegistry(void)
{
// Registry-Einträge

//KK021121
	DeleteKeyStandards();

	g_cSuffix[0] = '\0';
	g_cMemo[0] = '\0';
	g_cMemoSuffix[0] = '\0';
	g_cOrdnung[0] = '\0';

	g_cMemoKlasse[0] = '\0';

	g_cGruppe1[0] = '\0';
	g_cGruppe2[0] = '\0';
	g_cKeyThema[0] = '\0';


// OberThema,Thema,Gruppen
	cOberThemenName[0] = '\0';
	cThemenName[0] = '\0';
	cGruppeStrassen[0] = '\0';
	cGruppeZusatz[0] = '\0';


	TCHAR szBNAKey[_MAX_PATH];

	USES_CONVERSION;

	CComBSTR Projekt;
	Projekt.LoadString(IDS_PROJEKTLAYER);
	
	CComBSTR Export;
	Export.LoadString(IDS_EXPORT);

	CComBSTR Thema;
	Thema.LoadString(IDS_STANDARD);


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


	CComBSTR Suffix;
	Suffix.LoadString(IDS_POLYSUFFIX);
	strcat ( g_cSuffix,W2A(Suffix.m_str));

	CComBSTR KeyGr1;
	KeyGr1.LoadString(IDS_KEYGRUPPE1);
	strcat ( g_cGruppe1,W2A(KeyGr1.m_str));

	CComBSTR KeyGr2;
	KeyGr2.LoadString(IDS_KEYGRUPPE2);
	strcat ( g_cGruppe2,W2A(KeyGr2.m_str));

	CComBSTR KeyThema;
	KeyThema.LoadString(IDS_KEYTHEMA);
	strcat ( g_cKeyThema,W2A(KeyThema.m_str));

	//  MemoSuffix-fuer Gruppe Zusatz
	CComBSTR MeSuff;
	MeSuff.LoadString(IDS_MEMOSUFFIX);
	strcat ( g_cMemoSuffix,W2A(MeSuff.m_str));

	// Merkmal Strassenordnung
	CComBSTR Ordn;
	Ordn.LoadString(IDS_STRASSENORDNUNG);
	strcat ( g_cOrdnung,W2A(Ordn.m_str));

	//  MemoSuffix-fuer Gruppe Zusatz
	CComBSTR MeK;
	MeK.LoadString(IDS_MEMOKLASSE);
	strcat ( g_cMemoKlasse,W2A(MeK.m_str));

	//  Them
	CComBSTR Them;
	Them.LoadString(IDS_THEMENNAME);
	strcat ( cThemenName,W2A(Them.m_str));

	//  Gruppe Strassen
	CComBSTR Gruppe1;
	Gruppe1.LoadString(IDS_GRUPPESTRASSEN);
	strcat ( cGruppeStrassen,W2A(Gruppe1.m_str));

	//  Gruppe Zusatz
	CComBSTR Gruppe2;
	Gruppe2.LoadString(IDS_GRUPPEZUSATZ);
	strcat ( cGruppeZusatz,W2A(Gruppe2.m_str));


	// GeometrieTyp anhängen
	CComBSTR GiT;
	GiT.LoadString(IDS_GEOMETRIETYP);


	wsprintf(szBNAKey,g_cbBNALocal,REG_COMPANY_KEY,REG_PRODUCT_KEY,W2A(Projekt),W2A(Export),W2A(Thema));


		{	

			CCurrentUser rgMass(szBNAKey, true);


	//KK021121
			
			for ( long i = 0; i < PMFKEYCOUNT; i++ ) {
				SetPMFRegistryKeyData ( &rgMass,i,PMFKEYFELD[i]);
			}




			// BNASuffix
			dKeyLen = BNAKEYLEN;
			rgMass.GetSubSZ ((LPCTSTR )W2A(Suffix), (LPTSTR) g_cSuffix, dKeyLen);


			// Merkmal MemoSuffix
			dKeyLen = BNAKEYLEN;
			
			if ( !rgMass.GetSubSZ ((LPCTSTR )W2A(MeSuff), (LPTSTR) g_cMemoKlasse, dKeyLen))
				strcat ( g_cMemoKlasse,W2A(MeK.m_str));
				
			// Merkmal Strassenordnung
			dKeyLen = BNAKEYLEN;
			rgMass.GetSubSZ ((LPCTSTR )W2A(Ordn), (LPTSTR) g_cOrdnung, dKeyLen);

			// ThemenName
			dKeyLen = BNAKEYLEN;
			if ( !rgMass.GetSubSZ ((LPCTSTR )W2A(KeyThema), (LPTSTR) cThemenName, dKeyLen))
				strcat ( cThemenName,W2A(Them.m_str));

			// Gruppe Strassen
			dKeyLen = BNAKEYLEN;
			if (!rgMass.GetSubSZ ((LPCTSTR )W2A(KeyGr1), (LPTSTR) cGruppeStrassen, dKeyLen))
					strcat ( cGruppeStrassen,W2A(Gruppe1.m_str));


			// Gruppe Zusatz
			dKeyLen = BNAKEYLEN;
			if (!rgMass.GetSubSZ ((LPCTSTR )W2A(KeyGr2), (LPTSTR) cGruppeZusatz, dKeyLen))
				strcat ( cGruppeZusatz,W2A(Gruppe2.m_str));

			// GiTyp
			DWORD m_dGI = 0;

			if (rgMass.GetDWORD ((LPCTSTR )W2A(GiT), m_dGI))
				iGiTyp = (short)m_dGI;

		}

		return FALSE;
		

}
//------------------------------------------------------------------------

void SetExportContainer(void) {

	ExportContainer[0] = ExportContainer[2] = dMaxCont;

	ExportContainer[1] = ExportContainer[3] = dMinCont;

}
//------------------------------------------------------------------------

bool TypeDefined ( short iTyp) 
{
	if ( 0 == PolyGIType[iTyp]) {
		PolyGIType[iTyp] = 1;
		return false;
	}
	return true;

}
//------------------------------------------------------------------------
bool TypeDelete ( void) 
{
	for ( short i = PMFPunkt ; i <= PMFFlaeche; i++ )
		PolyGIType[i] = 0;
	return true;

}
//------------------------------------------------------------------------
void SetKeyStandards ( void )
{


	for ( long i = 0; i < PMFKEYCOUNT; i++ ) {
		SetKeyInformation ( i,PMFKEYFELD[i]);
	}


}
//-----------------------------------------------------------------------
void SetKeyInformation (long i, UINT Id)
{

	USES_CONVERSION;

	CComBSTR PMFKey;
	PMFKey.LoadString(Id);
	strcat ( &g_cKey[i][0],W2A(PMFKey.m_str));

}

//------------------------------------------------------------------------
void DeleteKeyStandards ( void )
{
	for ( long i = 0 ; i < PMFKEYCOUNT; i++ ) {
		g_cKey[i][0] = '\0';
	}

}

//-----------------------------------------------------------------------
void SetPMFRegistryKeyData ( CCurrentUser * pCU, long i,UINT Id)
{

	USES_CONVERSION;

	CComBSTR Uniq;
	Uniq.LoadString (IDS_PMFUNIQUEIDENT);

	CComBSTR PMFKey;
	PMFKey.LoadString (Id);

	DWORD dKeyLen = BNAKEYLEN;
	pCU->GetSubSZ ((LPCTSTR )W2A(PMFKey), (LPTSTR) &g_cKey[i][0], dKeyLen);

	if ( strcmp ((LPTSTR) &g_cKey[i][0],(LPTSTR) W2A(Uniq.m_str)) == 0 )
		iNumberUnique = i + 1;	// i von "0" bis ..., iNumberUnique von "1" bis ...

}
//-----------------------------------------------------------------------

///////////////////////////////////////////////////////////////////////////////
// Baum der LayerKlassen//////// ///////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

int StoreInTree (long lIdent , const char *pWert, short iTyp) 
{
	if (g_Tree == NULL) {
	// erstes Element: Baum muß angelegt werden

		g_Tree = new TR_OBJTree();
		if (g_Tree == NULL) return false;
	}

	CTable t (*g_Tree);

	if (!t.Find (&lIdent)) {

		TR_OBJCreator OSCr (*g_Tree);
		return ContCreate(OSCr, TR_OBJ)(lIdent, pWert, iTyp) != NULL;
	} else {

		TR_OBJLock l(t);

		if (l) 
			l->SetTyp(iTyp);
	}

	return true;
}
//////////////////////////////////////////////////////////////////////////////////
int StoreTypInTree (long lIdent , short iTyp) 
{

	if (g_Tree == NULL) return false;


	CTable t (*g_Tree);

	if (t.Find (&lIdent)) {
		TR_OBJLock l(t);

		if (l) 
			l->SetTyp(iTyp);

	}

	return true;
}
//----------------------------------------------------------------------

// Wiederauffinden einer ObjektNummer an Hand einer gegebenen SatzNummer
int RetrieveFromTree (long lIdent) 
{
	if ( g_Tree	== NULL) return false;

	CTable t (*g_Tree);

	if (t.Find (&lIdent)) {
		TR_OBJLock l(t);

		if (l) return true;
	}

	return false;
}
//----------------------------------------------------------------------
char * RetrieveTypLayer(long lIdent,short iTyp)
{
	if (g_Tree == NULL) return NULL;

	CTable t (*g_Tree);

	if (t.Find (&lIdent)) {

		TR_OBJLock l(t);

		if (l) 
			return l->GetLayerText(iTyp);

	}

	return NULL;

}
//----------------------------------------------------------------------

// Baum wieder zurücksetzen
void ResetTree (void) 
{
	DELETE_OBJ(g_Tree);
}

//------------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
