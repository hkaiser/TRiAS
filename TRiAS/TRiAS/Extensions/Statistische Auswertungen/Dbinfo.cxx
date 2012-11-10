// ----------------Datenbankübersicht -----------------------------
// File: DBINFO.CXX

#include "statistp.hxx"
#include "geostat.h"
#include <igeometr.hxx>

#include "dirmath.h"
#include <clipbrd.hxx>

#include "idkey.hxx"
#include "objkey.hxx"
#include "trfkoord.hxx"
#include "classkey.hxx"
#include "sclipbrd.hxx"
#include "dbinfo.hxx"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG && WIN32

 
// Konstruktoren/Destruktoren der DialogFenster --------------------------------

#pragma warning (disable: 4355)

DataBaseInformation :: DataBaseInformation (pWindow pW, uint res, ResourceFile &RF, IDMTree *pIDM )
	     : DialogWindow (pW, ResID ( res, &RF)),
	       _DBName (this,IDT_DBDATABASENAME),
	       _DBBeschreibung (this,IDT_DBDATABASEPBD),
	       _DBInfo (this,IDCB_DBDATABASEINFO),
	       _Datum (this,IDT_DBDATABASEDATUM),
	       _RF (RF),
	       OKButton (this, IDOK),
	       CancelButton (this, IDCANCEL)

{

//	StartWerte
	_pW = pW;
//	pW->Disable();
	_pIDM = pIDM;
	_pDBInfoFeld = new short [20];

	if ( !_pDBInfoFeld)
		return;
	_iDBInfo = -1;
	
	OKButton.Disable();

	ShowDataBaseParam ();

	FillDataBaseInformation();

	return;
}

#pragma warning (default: 4355)


DataBaseInformation :: ~DataBaseInformation (void)
{
//	_pW->Enable();
	DELETE_OBJ ( _pDBInfoFeld);
}
//---------------------------------------------------------
void _XTENSN_EXPORT DataBaseInformation :: ListBoxSel (ControlEvt e )
{
	switch ((unsigned int)e.GetControlID()) {
	case IDCB_DBDATABASEINFO:
	{
		_iDBInfo = GetDBInfo();
	}
	break;
	

	}
}

void _XTENSN_EXPORT DataBaseInformation :: ButtonClick (ControlEvt e)
{
	switch ((unsigned int)e.GetControlID()) {
	case IDOK: 
		{
		EndDlg (1);
		}
		break;

	case IDCANCEL:
		{
		EndDlg (0);
		}
		break;
	}
}
//Member
void DataBaseInformation :: FillDataBaseInformation ( void )
{
	char *pBuf = new char [_MAX_PATH];
	if ( !pBuf)
		return;
	short Number = 0;
	long lNumSight = NumberSights ( );
	if ( lNumSight > 0L) {
		*(_pDBInfoFeld + Number ) = (short) DBSicht;
		Number++;
		wsprintf (pBuf, ResString( ResID( IDS_DBDATABASESIGHT,&_RF),50),lNumSight);
		_DBInfo.AddString(pBuf);
	}

	_lIdents = NumberIdents ();
	if (_lIdents > 0L ) {
		*(_pDBInfoFeld + Number ) = (short) DBObjektKlasse;
		Number++;
		wsprintf (pBuf, ResString( ResID( IDS_DBDATABASEOBJCLASS,&_RF),50),_lIdents);
		_DBInfo.AddString(pBuf);
	}

	long lNumMCode = NumberMCodes ( );
	if ( lNumMCode > 0L ) {
		*(_pDBInfoFeld + Number ) = (short) DBMerkmalsCode;
		Number++;
		wsprintf (pBuf, ResString( ResID( IDS_DBDATABASEMCODE,&_RF),50),lNumMCode);
		_DBInfo.AddString(pBuf);
	}

	long lNumDB = NumberDBase ( );
	if ( lNumDB > 0L) {
		*(_pDBInfoFeld + Number ) = (short) DBdBaseDaten;
		Number++;
		wsprintf (pBuf, ResString( ResID( IDS_DBDATABASEDBASE,&_RF),50),lNumDB);
		_DBInfo.AddString(pBuf);
	}

	long lNumTP = NumberTProjects ( );
	if ( lNumTP > 0L) {
		*(_pDBInfoFeld + Number ) = (short) DBTeilProjekte;
		Number++;
		wsprintf (pBuf, ResString( ResID( IDS_DBDATABASETPROJECT,&_RF),50),lNumTP);
		_DBInfo.AddString(pBuf);
	}


	long lNumPerm = NumberPerm ( );
	if ( lNumPerm > 0L) {
		*(_pDBInfoFeld + Number ) = (short) DBSachDaten;
		Number++;
		wsprintf (pBuf, ResString( ResID( IDS_DBDATABASEPERM,&_RF),50),lNumPerm);
		_DBInfo.AddString(pBuf);
	}

	DELETE_OBJ (pBuf);
	return;
}
//-------------------------------------------------------------------
short DataBaseInformation :: GetDBInfo ( void )
{
short InfoTyp = -1L;
	OKButton.Disable();
	int iIndex = _DBInfo.GetCurrentIndex();
	if (iIndex != -1) {
		InfoTyp = *(_pDBInfoFeld+iIndex);
		if ( InfoTyp == DBObjektKlasse)
			OKButton.Enable();
	}
	return InfoTyp;
}

//-------------------------------------------------------------------
void DataBaseInformation :: ShowDataBaseParam ( void )
{

char *pText= new char [_MAX_PATH];
	if ( pText == NULL )
		return;

char *pDrive = new char [_MAX_DRIVE];
char *pPath = new char [_MAX_DIR];
char *pName = new char [_MAX_FNAME];
char *pExt = new char [_MAX_EXT];
char *pFullName = new char [_MAX_PATH];

	if ( pFullName == NULL || pDrive == NULL || pPath == NULL || pName == NULL || pExt == NULL){
		DELETE_OBJ (pDrive);
		DELETE_OBJ (pPath);
		DELETE_OBJ (pName);
		DELETE_OBJ ( pExt);
		DELETE_OBJ ( pFullName);
		return;
	}

//----------------------	Projektname	----------------------
	*pText = '\0';
	pText = DEX_GetActiveProject (pText);
	if ( *pText != '\0' ) {
		if ( strlen (pText ) > MAXDBSTRING ) {
// Dateinamen neu generieren
			_splitpath (pText, pDrive, pPath, pName, pExt);
			int len = strlen(pDrive) + strlen(pName) + strlen(pExt);
			len = MAXDBSTRING - len;
			KurzerPfad ( len, pPath );
		// vollen ProFileNamen zusammenbauen
			_makepath (pFullName, pDrive, pPath, pName, 
				    pExt);
			 _DBName.SetText (pFullName);
		} else 
			_DBName.SetText (pText);
	} else
		_DBName.SetText(NULL);

//---------------------------	Beschreibungsdaten	---------------------
	*pText = '\0';

	if ( DEX_GetPBDName (pText) != NULL ) {

		if ( strlen ( pText ) > MAXDBSTRING ) {
// Dateinamen neu generieren
			_splitpath (pText, pDrive, pPath, pName, pExt);

			int len = strlen(pDrive) + strlen(pName) + strlen(pExt);
			len = MAXDBSTRING - len;
			KurzerPfad ( len, pPath );
		// vollen ProFileNamen zusammenbauen
			_makepath (pFullName, pDrive, pPath, pName, 
			    pExt);
			 _DBBeschreibung.SetText (pFullName);
		} else {
			if ( *pText == '\0')
				wsprintf (pText, ResString( ResID( IDE_ERRNOPBD,&_RF),50));
			_DBBeschreibung.SetText (pText);
				
		}

	} else {
		wsprintf (pText, ResString( ResID( IDE_ERRNOPBD,&_RF),50));
		_DBBeschreibung.SetText (pText);
	}

//---------------------	User in Caption	------------------------

	pText = DEX_GetActiveUser (pText);
char * pOut = new char [_MAX_PATH];
	if ( pOut == NULL )
		return;
	if (pText != NULL ) {
		pFullName = GetCaption ( pFullName , _MAX_PATH -1);
		wsprintf ( pOut,pFullName, pText);
		SetCaption ( pOut);
	}
	DELETE_OBJ (pOut);

//-----------------	Erstellungsdatum	---------------------------
	*pFullName = '\0';
	strcat ( pFullName, ResString ( ResID(IDT_HEADAENDATUM,&_RF),35));

	char *pDatum = GetHeaderMText ( pFullName );              

	if ( pDatum != NULL ) {
		_Datum.SetText ( pDatum );
		DELETE_OBJ ( pDatum );
	} else
		_Datum.SetText ( "kein TRIAS - dbput" );



// Speicher freigeben
	DELETE_OBJ (pDrive);
	DELETE_OBJ (pPath);
	DELETE_OBJ (pName);
	DELETE_OBJ (pExt);
	DELETE_OBJ ( pFullName );
	DELETE_OBJ ( pText );

}

//-------------------------------------------------------------------
long DataBaseInformation :: NumberSights ( void )
{
//----------Anzahl der Sichten----------------------

long lCnt = 0L;

ENUMNOKEY ENK;
	ENK.eFcn = ( ENUMNOKEYPROC) NumerationDB;
	ENK.ePtr = &lCnt;
	DEX_EnumSights(ENK);
	return lCnt;
}

//-------------------------------------------------------------------
long DataBaseInformation :: NumberIdents ( void )
{
//--------------------Identifikatoren-----------------------------------------
	long lCnt = 0L;
	if (_pIDM == NULL )
		return lCnt;

	CTable t(*_pIDM);
	ulong UCount = _pIDM->Count();
	lCnt = (long) UCount;
	return lCnt;
}
//-------------------------------------------------------------------
long DataBaseInformation :: NumberMCodes ( void )
{
//----------Anzahl der MerkmalsCodes----------------------

long lCnt = 0L;

ENUMNOKEY ENK;
	ENK.eFcn = ( ENUMNOKEYPROC) NumerationMK;
	ENK.ePtr = &lCnt;
	DEX_EnumMCodes(ENK);
	return lCnt;
}
//-------------------------------------------------------------------
long DataBaseInformation :: NumberTProjects ( void )
{
	long Number = 0L;
// aktuelles Projektverzeichnis besorgen
	char *pLocDir = new char [_MAX_PATH];
	if ( pLocDir == NULL ) 
		return Number;
	if (DEX_GetActiveProject (pLocDir) == NULL) {
	// Projekt eröffnet
		DELETE_OBJ ( pLocDir);
		return Number;
	}
	char *pFileName = new char [MaxString];

	if ( pFileName == NULL ) {
		DELETE_OBJ ( pLocDir);
		return Number;	
	}
	
	ResString Projects (ResID (IDS_DBDATABASEPROJECTS, &_RF), 13);

char *pDrive = new char [_MAX_DRIVE];
char *pPath = new char [_MAX_DIR];
char *pDBName = new char [_MAX_FNAME];

	if ( pDrive == NULL || pPath == NULL || pDBName == NULL ) {
		DELETE_OBJ ( pLocDir);
		DELETE_OBJ ( pFileName);
		DELETE_OBJ ( pDrive);
		DELETE_OBJ ( pPath);
		DELETE_OBJ ( pDBName);
		return Number;
	}

// Dateinamen der ProfileDatei neu generieren
	_splitpath (pLocDir, pDrive, pPath, pDBName, NULL);
	// vollen ProFileNamen zusammenbauen  
	char *pExt = new char [ _MAX_EXT];
	if ( pExt == NULL ) {
		DELETE_OBJ ( pLocDir);
		DELETE_OBJ ( pFileName);
		DELETE_OBJ (pDrive);
		DELETE_OBJ (pPath);
		DELETE_OBJ (pDBName);
		return Number;
	}
	*pExt = '\0';
	strcat ( pExt,ResString (ResID (IDS_DBDATABASEPROFEXT, &_RF), 5));
	_makepath (pLocDir, pDrive, pPath, pDBName, pExt);

// Speicher freigeben
	DELETE_OBJ (pDrive);
	DELETE_OBJ (pPath);
	DELETE_OBJ (pDBName);
	DELETE_OBJ (pExt);

//	Fllen von pLocDir mit allen DB-Schlsseln aus ProFile
	GetPrivateProfileString (Projects, NULL, "", pFileName, MaxString, pLocDir);
	if (*pFileName != '\0') {	// was gefunden

		// Zusammenstellen der MenuPunkte

		//	Achtung - neu durchz„hlen !!!
	
		char *aptr = &pFileName[0];

		while ( *aptr != NULL ) {
			char *ptr = strrchr (aptr, '\0');
			if ( ptr != NULL ) {
				aptr = ptr +1;
				Number++;
			}
		}
	}
	DELETE_OBJ ( pLocDir);
	DELETE_OBJ ( pFileName);
	return Number;
}

//-------------------------------------------------------------------
long DataBaseInformation :: NumberDBase ( void )
{
	long Number = 0L;
// aktuelles Projektverzeichnis besorgen
	char *pLocDir = new char [_MAX_PATH];
	if ( pLocDir == NULL ) 
		return Number;
	if (DEX_GetActiveProject (pLocDir) == NULL) {
	// Projekt eröffnet
		DELETE_OBJ ( pLocDir);
		return Number;
	}
	char *pFileName = new char [MaxString];

	if ( pFileName == NULL ) {
		DELETE_OBJ ( pLocDir);
		return Number;	
	}
	
	ResString Projects (ResID (IDS_DBDATABASEDBDAT, &_RF), 13);

char *pDrive = new char [_MAX_DRIVE];
char *pPath = new char [_MAX_DIR];
char *pDBName = new char [_MAX_FNAME];

	if ( pDrive == NULL || pPath == NULL || pDBName == NULL ) {
		DELETE_OBJ ( pLocDir);
		DELETE_OBJ ( pFileName);
		DELETE_OBJ ( pDrive);
		DELETE_OBJ ( pPath);
		DELETE_OBJ ( pDBName);
		return Number;
	}

// Dateinamen der ProfileDatei neu generieren
	_splitpath (pLocDir, pDrive, pPath, pDBName, NULL);
	// vollen ProFileNamen zusammenbauen  
	char *pExt = new char [ _MAX_EXT];
	if ( pExt == NULL ) {
		DELETE_OBJ ( pLocDir);
		DELETE_OBJ ( pFileName);
		DELETE_OBJ (pDrive);
		DELETE_OBJ (pPath);
		DELETE_OBJ (pDBName);
		return Number;
	}
	*pExt = '\0';
	strcat ( pExt,ResString (ResID (IDS_DBDATABASEPROFEXT, &_RF), 5));
	_makepath (pLocDir, pDrive, pPath, pDBName, pExt);

// Speicher freigeben
	DELETE_OBJ (pDrive);
	DELETE_OBJ (pPath);
	DELETE_OBJ (pDBName);
	DELETE_OBJ (pExt);

//	Fllen von pLocDir mit allen DB-Schlsseln aus ProFile
	GetPrivateProfileString (Projects, NULL, "", pFileName, MaxString, pLocDir);
	if (*pFileName != '\0') {	// was gefunden

		// Zusammenstellen der MenuPunkte

		//	Achtung - neu durchz„hlen !!!
	
		char *aptr = &pFileName[0];

		while ( *aptr != NULL ) {
			char *ptr = strrchr (aptr, '\0');
			if ( ptr != NULL ) {
				aptr = ptr +1;
				Number++;
			}
		}
	}
	DELETE_OBJ ( pLocDir);
	DELETE_OBJ ( pFileName);
	return Number;
}
//------------------------------------------------------------------
//-------------------------------------------------------------------
long DataBaseInformation :: NumberPerm ( void )
{
long lCnt = 0L; 
char *pHText = new char[17];
	if (!pHText)
		return lCnt;
		
	strcpy ( pHText,ResString (ResID(IDS_DBDATABASEPERMHCODE,&_RF),17));

// Permdaten????
	if ( GetHeaderMText (pHText)) {
		long lHeadMCode = atol ( ResString (ResID(IDS_DBDATABASEPERMMCODE,&_RF),17));
//----------Anzahl der Objekte----------------------
		ENUMRECHTEXTMERKMAL EM;
		memset (&EM, '\0', sizeof(ENUMRECHTEXTMERKMAL));
		EM.dwSize = sizeof(ENUMRECHTEXTMERKMAL);
		EM.lMCode = lHeadMCode;
		EM.iMode = SMExactMatch;
		EM.eFcn = (RECHTEXTMERKMALCALLBACK) NumerationMK;
		EM.pData = &lCnt;
		DEX_EnumRechTextMerkmal(EM);
	}
	DELETE_OBJ ( pHText);
	return lCnt;
}
//-------------------------------------------------------------------

//-------------------------------------------------------------------
char *DataBaseInformation :: GetHeaderMText ( char *pHDR )
{
char * pHText = new char [MCODESIZE + 1];
	if ( pHText == NULL )
		return NULL;

GEODBHDRENTRY hdrEntry;
	*pHText = '\0';
	memset (&hdrEntry,'\0',sizeof(GEODBHDRENTRY));
	hdrEntry.dwSize = sizeof(GEODBHDRENTRY);
	strncpy (hdrEntry.hdrKey, pHDR,16);
	hdrEntry.lphdrText = pHText;
	hdrEntry.hdrTextLen = MCODESIZE;

	if (DEX_ReadGeoDBHdrEntry (hdrEntry) == EC_OKAY) {
	// HeaderEintrag existiert
		return pHText;
	} else
		return NULL;
}

//-------------------------------------------------------------------
double DataBaseInformation :: GetHeaderDWert ( char *pHDR )
{
double result = 1.0;
char * pHText = new char [MCODESIZE + 1];
	if ( pHText == NULL )
		return result;

GEODBHDRENTRY hdrEntry;
	*pHText = '\0';
	memset (&hdrEntry,'\0',sizeof(GEODBHDRENTRY));
	hdrEntry.dwSize = sizeof(GEODBHDRENTRY);
	strncpy (hdrEntry.hdrKey, pHDR,16);
	hdrEntry.lphdrText = pHText;
	hdrEntry.hdrTextLen = MCODESIZE;

	if (DEX_ReadGeoDBHdrEntry (hdrEntry) == EC_OKAY) {
	// HeaderEintrag existiert
		result = atof(pHText);
	} else
		result = -1.0;

	DELETE_OBJ ( pHText );
	return result;
}
//--------------------------------------------------------
void KurzerPfad ( int len, char *pPath )
{
char * pNPath = new char [_MAX_PATH];
char *aptr,*eptr;

	if ( pNPath == NULL )
		return;
	*pNPath = '\0';
	aptr = strchr ( pPath+1, '\\');
	eptr = strrchr ( pPath+1, '\\');
	if ( eptr - aptr + 4 > len )
		aptr = strchr ( aptr+1 , '\\' );
	strcat ( pNPath , "\\...");
	strcat ( pNPath, aptr );
	*pPath = '\0';
	strcpy ( pPath,pNPath);
	DELETE_OBJ ( pNPath);
	return;
}
//--------------------------------------------------------------
//-----------------------------------------------------------------------
//------------------------INFO-Fenster-----------------------------------
//-----------------------------------------------------------------------

// Konstruktoren/Destruktoren der DialogFenster --------------------------------

#pragma warning (disable: 4355)

IdentInformation :: IdentInformation (pWindow pW, uint res, ResourceFile &RF,IDMTree *pIDM, pchar pCaption, long iRange)
	     : ModeLessDialog (pW, ResID ( res, &RF)),
//	       _IDKey (this,IDT_SHOWIDENTKEY),
//	       _IDNumber (this,IDT_SHOWIDENTNUMBER),
	       _Status (this,IDG_SHOWSTATUSGAUGE),
	       _RF (RF),
	       CancelButton (this, IDCANCEL)

{
// Variablen initialisieren
	_fWasInterrupted = false;

	_pW = pW;

//	pW -> Disable();

	_lIdents = 0;
	_Number =0;
	SetCaption ( pCaption);
	_iRangeAll = iRange;
	_iCurrVal = -1;
	_Status.SetRange ( (short)iRange);
	_Status.SetPosition (0);
	_Status.SetDeltaPos(1);
	if ( pIDM == NULL )
		return;
	_pIDM = pIDM;
	return;
}

#pragma warning (default: 4355)


IdentInformation :: ~IdentInformation (void)
{
//	_pW -> Enable();

}

void IdentInformation :: SetStart ( void )
{
static char s_pTmp[_MAX_PATH];
	wsprintf (s_pTmp, ResString( ResID( IDS_STARTRECHERCHE,&_RF),50));
	_Status.SetText (s_pTmp);

}

void IdentInformation :: SetText ( long lCnt )
{
static char s_pTmp[_MAX_PATH];
	wsprintf (s_pTmp, ResString( ResID( IDS_OBJEKTRECHERCHE,&_RF),50),lCnt);
	_Status.SetText (s_pTmp);

}

void IdentInformation :: SetObjectText ( long lCnt )
{

char *pBuffer = new char [_MAX_PATH];
	if ( !pBuffer ) 
		return;
	wsprintf (pBuffer, ResString( ResID( IDS_TIMERCAPTION,&_RF),50),lCnt);

static char s_pTmp[_MAX_PATH];

	wsprintf (s_pTmp, ResString( ResID(IDS_GAUGEBOX,&_RF),50), pBuffer);
	_Status.SetText (s_pTmp);
	DELETE_OBJ ( pBuffer);
	return;
}

void IdentInformation :: ModifyWindow ( long Ident )
{

//char pNum[20];	

PBDDATA pbdData;
char *pKText = new char [MAXFCTNAME+1];
	if ( pKText == NULL )
		return;
	*pKText = '\0';

	_Key = Ident;
	_Number++;
	memset (&pbdData, '\0', sizeof(PBDDATA));

	pbdData.dwSize = sizeof(PBDDATA);
	pbdData.pbdTyp = 'i';
	pbdData.pbdCode = _Key;
	pbdData.pbdKText = pKText;
	pbdData.pbdKTextLen = MAXFCTNAME;
	pbdData.pbdLTextLen = 0;
	DEX_GetPBDData (pbdData);

//-------pKText betrachten, falls kein Text da -----
	if ( *pKText == NULL )
		strcpy ( pKText , ResString( ResID(IDS_NODEFOBJCLASS,&_RF),50) );
	*(pKText+MAXFCTNAME) = '\0';

static char s_pTmp[_MAX_PATH];
	wsprintf (s_pTmp, ResString( ResID(IDS_GAUGEBOX,&_RF),50), pKText);
	_Status.SetText (s_pTmp);

	DELETE_OBJ (pKText);
	return;
}

void IdentInformation :: ModifyGIWindow ( long Ident , double First, double Second )
{

//char pNum[20];	
	_Key = Ident;
	_Number++;
//	_IDNumber.SetText(ltoa(_Number,pNum,10));
char * pBuffer0 = new char [_MAX_PATH];
char * pBuffer1 = new char [_MAX_PATH];

	if ( pBuffer0 == NULL || pBuffer1 == NULL ) {
		DELETE_OBJ (pBuffer0);
		DELETE_OBJ (pBuffer1);
		return;
	}
    *pBuffer0 = '\0';
	strcat ( pBuffer0, " : [");
	ST_DtoA (pBuffer1, "%10.3f", First);
	strcat (pBuffer0,pBuffer1);
	strcat ( pBuffer0, " , ");
	ST_DtoA (pBuffer1, "%10.3f", Second);
	strcat (pBuffer0,pBuffer1);
	strcat ( pBuffer0, "]");

//	_IDKey.SetText( pBuffer0);
static char s_pTmp[_MAX_PATH];

	wsprintf (s_pTmp, ResString( ResID(IDS_GAUGEBOX,&_RF),50), pBuffer0);
	_Status.SetText (s_pTmp);


	DELETE_OBJ (pBuffer0);
	DELETE_OBJ (pBuffer1);
	return;
}

void _XTENSN_EXPORT IdentInformation :: ButtonClick (ControlEvt )
{
	_fWasInterrupted = true;		// Analyse abbrechen

}

    
//-------------------------------------------------------------------

//-------------------------------------------------------------------

//-------------Objektklassenübersicht einer Datenbank----------------

// Konstruktoren/Destruktoren der DialogFenster --------------------------------

#pragma warning (disable: 4355)

DataBaseObjClass :: DataBaseObjClass (pWindow pW, uint res, ResourceFile &RF , short MFlag, IDMTree *pIDM, OBJCLList *pOCL, long *pMCode) 
	     : DialogWindow (pW, ResID ( res, &RF)),
	       _ObjClassList (this, IDLB_OCLPCLASSLIST),
	       _BezugsList (this, IDCB_OCLPBEZUGSKLASSE),
	       _ObjClassCount (this,IDT_OCLPCLASSCOUNT),
	       _Objekte ( this,IDT_OCLPOBJECTCOUNT),
	       _Minimum ( this,IDT_OCLPMINIMUM),
	       _Maximum ( this,IDT_OCLPMAXIMUM),
	       _MedianWert ( this,IDT_OCLPMEDIANWERT),
	       _MittelWert ( this,IDT_OCLPMITTELWERT),
	       _Summe ( this,IDT_OCLPCUMULCLASS),
	       _Anteil ( this,IDT_OCLPPROZANTEIL),
	       _BezugsBox ( this,IDC_OCLPBEZUGEINAUS),
	       _BezObjekte ( this,IDT_OCLPALLOBJECTSCOUNT),
	       _BezMinimum ( this,IDT_OCLPBEZMINIMUM),
	       _BezMaximum ( this,IDT_OCLPBEZMAXIMUM),
	       _BezMedianWert ( this,IDT_OCLPBEZMEDIANWERT),
	       _BezMittelWert ( this,IDT_OCLPBEZMITTELWERT),
	       _BezSumme ( this,IDT_OCLPCLASSSUMME),
	       _RF (RF),
	       _PutClipBoard ( this,IDB_OCLPCLIPBOARD),
	       CancelButton (this, IDCANCEL)
{
	if ( pIDM == NULL || pOCL == NULL )
		return;
	_pIDM = pIDM;
	_pOCL = pOCL;
	_MCode = 0L;
	_MFlag = MFlag;

	if ( pMCode )
		_MCode = *pMCode;
	_pHelpText = NULL;
	_pHelpText = CHelpTextX :: CreateInstance (this, IDT_OCLPBESCHREIBUNG);
	if (_pHelpText == NULL)
		return;

	CEierUhr Wait ( pW );
//--------------Startbedingungen---------------------------------------
	_pW = pW;
        _PutClipBoard.Disable();
	_pOBJ = NULL;
	_pOBJ = new OBJTree;
	if ( _pOBJ == NULL)
		return;
	_IdCount = 0;
	_OBJCount = 0;
	_pIdent = NULL; // Selektierte Klassen

	_pEinheit = new char [_MAX_PATH];
	if ( _pEinheit == NULL )
		return;

	_BezugsID = 0L;
	_BezugsTyp = '\0';
	_SelTyp = '\0';
//---------Linien/kumulativ--------------------
	_MinL = 0.0;
	_MaxL = 0.0;
	_ObjectsL = 0;
	_CumulL = 0.0;
	_MedianL = 0.0;
	_MWertL = 0.0;
//----------Flaechen/kumulativ-----------------	
	_MinF = 0.0;
	_MaxF = 0.0;
	_ObjectsF = 0;
	_CumulF = 0.0;
	_MedianF = 0;
	_MWertF = 0;
//----------ObjKlassen/angeklickt----------------
	_Minim = 0.0;
	_Maxim = 0.0;
	_NumObjects = 0;
	_SumObject = 0.0;
	_Median = 0.0;
	_Mittelwert = 0.0;

char * pNum = new char[_MAX_PATH];
//char * pNum = new char[20];
	if ( pNum == NULL )
		return;

	_BezugsBox.SetChecked(FALSE);

//-------------ObjektklassenListe füllen------------
	FillObjKlassenList (pOCL);

	_ObjClassCount.SetText ( ltoa ( _IdCount,pNum,10));

	DELETE_OBJ ( pNum );

	return;
}

#pragma warning (default: 4355)


DataBaseObjClass :: ~DataBaseObjClass (void)
{

	DELETE_OBJ ( _pEinheit);       
	DELETE_OBJ ( _pOBJ);
	DELETE_OBJ ( _pIdent);
	DELETE_OBJ (_pHelpText);
}

void DataBaseObjClass :: FillObjKlassenList ( OBJCLList * pOCL )
{
	if ( _pIDM == NULL || _pOCL == NULL )
		return;

	CRing r( *_pOCL);
	_IdCount = 0L;
	_OBJCount = 0L;
// Startbedingungen
	GIEXTREMUM EXTL;
	GIEXTREMUM EXTF;
	SetExtremumZero ( &EXTL);
	SetExtremumZero ( &EXTF);
//---------------------------------------------
	if ( _pOBJ != NULL )
		DELETE_OBJ ( _pOBJ);
	_pOBJ = new OBJTree ;
	if ( _pOBJ == NULL )
		return;

    char CTyp;

	char *outBuff = new char [_MAX_PATH];

	if (!outBuff)
		return;

	for (r.First(); r.Valid() ; r.Next()  ) {
	   OBJCLLock l(r);

		*outBuff = '\0';

	   if ( l) {
		long Ident = ( l->OBJCLIdent());
		short Typ = l->OBJCLTyp();
		short BezugsTyp = l->OBJCLBezugsTyp();


		if ( Typ == OTFlaeche || Typ == OTLinie )

			if (l->OBJCLLine())
				strcpy (outBuff,&l->OBJCLLine());

			if ( BezugsTyp) {
		#if _MSC_VER < 1200
				_ObjClassList.AddString ( &l->OBJCLLine());
		#else
			// wenn mehr als eine Datenquelle geöffnet ist, dann den Namen der zugehörigen in
			// Klammern hinten anhängen
				if (DEX_GetOpenConnectionCount (QDCAllOpen) > 1) {
					char cbBuffer[_MAX_PATH];
					HPROJECT hPr = DEX_GetObjectsProject(Ident);

					TX_ASSERT(NULL != hPr);
					if (NULL != DEX_GetDataSourceShortName (hPr, cbBuffer)) {
						strcat (outBuff, " (");
						strcat (outBuff, cbBuffer);
						strcat (outBuff, ")");
					}
				}

			// Ident am jeweiligen Item speichern
				int iIndex = _ObjClassList.AddString (outBuff);

				_ObjClassList.SetItemData (iIndex, Ident);
		#endif // _MSC_VER < 1200

				_IdCount++;
			}


	#if _MSC_VER < 1200
			_BezugsList.AddString ( &l->OBJCLLine());
	#else
		// wenn mehr als eine Datenquelle geöffnet ist, dann den Namen der zugehörigen in
		// Klammern hinten anhängen
			if (DEX_GetOpenConnectionCount (QDCAllOpen) > 1) {
				char cbBuffer[_MAX_PATH];
				HPROJECT hPr = DEX_GetObjectsProject(Ident);

				TX_ASSERT(NULL != hPr);
				if (NULL != DEX_GetDataSourceShortName (hPr, cbBuffer)) {
					strcat (outBuff, " (");
					strcat (outBuff, cbBuffer);
					strcat (outBuff, ")");
				}
			}

		// Ident am jeweiligen Item speichern
			int iIndex = _BezugsList.AddString (outBuff);

			_BezugsList.SetItemData (iIndex, Ident);
	#endif // _MSC_VER < 1200

			
			if ( (Typ & OTLinie) > 0 ) { 
				CTyp = 'L';
				AddCountObjClassTypes ( FALSE, Ident , &CTyp, &EXTL);
			}
			if ( (Typ & OTFlaeche) > 0 ) { 
				CTyp = 'F';
				AddCountObjClassTypes ( FALSE, Ident , &CTyp, &EXTF);
			}
		}
	}
//-----------------------------------------------------------------------
	DELETE_OBJ ( outBuff);

	CTyp = 'L';
	BuildExtremum ( &CTyp, &EXTL);

	_MinL = EXTL.rMinimum;
	_MaxL = EXTL.rMaximum;
	_ObjectsL = EXTL.lObjCount;
	_CumulL = EXTL.rSumme;
	_MedianL = EXTL.rMedianWert;
	_MWertL = EXTL.rMittelWert;
	
	CTyp = 'F';
	BuildExtremum ( &CTyp, &EXTF);

	_MinF = EXTF.rMinimum;
	_MaxF = EXTF.rMaximum;
	_ObjectsF = EXTF.lObjCount;
	_CumulF = EXTF.rSumme;
	_MedianF = EXTF.rMedianWert;
	_MWertF = EXTF.rMittelWert;

}
//-----------------------------------------------------------------
void DataBaseObjClass :: LoadObjKlassenList ( short *CTyp )
{
	if ( _pOCL == NULL )
		return;
	
	CRing r(*_pOCL );
	_ObjClassList.Clear();
	_IdCount = 0L;

	char *outBuff = new char [_MAX_PATH];

	if (!outBuff)
		return;

	for (r.First(); r.Valid() ; r.Next()  ) {
	
	   OBJCLLock l(r);

		*outBuff = '\0';
	   if ( l) {
		long Ident = ( l->OBJCLIdent());
	
		short Typ = l->OBJCLTyp();
		short BezugsTyp = l->OBJCLBezugsTyp();
		if ( l->OBJCLLine())
			strcpy (outBuff,&l->OBJCLLine());

		if ( (*CTyp & Typ) > 0 ) { 
		   if ( BezugsTyp ) {
			_IdCount++;

	#if _MSC_VER < 1200
			_ObjClassList.AddString ( &l->OBJCLLine());
	#else
		// wenn mehr als eine Datenquelle geöffnet ist, dann den Namen der zugehörigen in
		// Klammern hinten anhängen
			if (DEX_GetOpenConnectionCount (QDCAllOpen) > 1) {
				char cbBuffer[_MAX_PATH];
				HPROJECT hPr = DEX_GetObjectsProject(Ident);

				TX_ASSERT(NULL != hPr);
				if (NULL != DEX_GetDataSourceShortName (hPr, cbBuffer)) {
					strcat (outBuff, " (");
					strcat (outBuff, cbBuffer);
					strcat (outBuff, ")");
				}
			}

		// Ident am jeweiligen Item speichern
			int iIndex = _ObjClassList.AddString (outBuff);

			_ObjClassList.SetItemData (iIndex, Ident);

		#endif // _MSC_VER < 1200

		   }
		}
	   }
	} 

	DELETE_OBJ(outBuff);
}

//----------------------------------------------------------------
void DataBaseObjClass :: SelectIdents ( void )
{

	if ( _pIdent == NULL )
		return;

int iCount = _ObjClassList.GetCount();
	if ( iCount == 0 ) 
		return;

	char * pBuff = new char [_MAX_PATH];
	if ( pBuff == NULL )
		return;
	long Number = 0L;
	long Ident;
	for ( int i = 0; i < iCount ; i++) {
		_ObjClassList.GetString (pBuff, i, _MAX_PATH);
		char *ptr = strchr (pBuff, ':');
		if ( ptr == NULL ) {
			DELETE_OBJ ( pBuff);
			return;
		} else
			*ptr = '\0';


		ulong uIdent = 0;
// Identifikator besorgen !

#if _MSC_VER < 1200

		HRESULT hr = IdentFromClassX (pBuff, &uIdent);
		if (FAILED(hr)) {
			uIdent = 0;
		}
#else
		uIdent = _ObjClassList.GetItemData (i);		// Ident ist am Item gespeichert
		TX_ASSERT(0 != uIdent);
#endif // _MSC_VER < 1200


		Ident = (long) uIdent;


		*ptr = ':';
		if ( Ident == *(_pIdent + Number + 1) ) {
			_ObjClassList.ChangeSelected ( i, TRUE );
			Number++;
			if ( Number >= *_pIdent )
				return;
		}
	}
	DELETE_OBJ ( pBuff);
	if ( Number == 0L ) {		// Keine Idents!
		DELETE_OBJ (_pIdent);
		_NumObjects = 0L;
	}
}
//------------------------------------------------------------------------

//-----------------------------------------------------------------
void _XTENSN_EXPORT DataBaseObjClass :: ButtonClick (ControlEvt e)
{

	switch ((unsigned int)e.GetControlID()) {

	case IDCANCEL:
		EndDlg (0);
		break;

	case IDC_OCLPBEZUGEINAUS:
		{
		if ( _BezugsBox.isChecked() ) {
			_BezugsBox.SetChecked ( TRUE );
			if ( _BezugsID != 0L ) {	// schon einmal selektiert
				BezugsKlassenAuswahl();
				short CTyp = '\0';
				if ( _BezugsTyp == 'F')
					CTyp = OTFlaeche;
				else
					CTyp = OTLinie;
				LoadObjKlassenList ( &CTyp);
				if ( _SelTyp != '\0' && _SelTyp == _BezugsTyp ) {
					if ( _pIdent != NULL )
						SelectIdents();
				} else {
					DELETE_OBJ (_pIdent);
					_SelTyp = '\0';
				}
				ShowCountObjects (&_BezugsTyp );
			}
		} else {
			_BezugsBox.SetChecked ( FALSE );
			if ( _BezugsTyp != '\0' ) {
			   short CTyp = OTLinie | OTFlaeche;
			   LoadObjKlassenList ( &CTyp);
			   if ( _NumObjects > 0 ) {
				LoadBezugsWert (&_BezugsTyp);
				SelectIdents();
				if ( _BezugsTyp == 'F' )
					_pHelpText -> SetHelpText (ResID(IDH_HELPBEZFLAECHENOKL,&_RF));
				else
					_pHelpText -> SetHelpText (ResID(IDH_HELPBEZLINIENOKL,&_RF));
				ShowCountObjects (&_BezugsTyp );
			   } else {	//	Keine OKL selektiert
				_pHelpText -> SetHelpText (ResID(IDH_HELPNOBESCHREIBUNG,&_RF));
				ShowNoBezugsKlasse();
			   }
			}
		}
		}
		break;

	case IDB_OCLPCLIPBOARD:
		{

		CEierUhr Wait(_pW);
		_pHelpText -> SetHelpText (ResID(IDH_HELPCLIPBOARD,&_RF));

		PutIdentToClipBoard ();
		
		}
		break;

	}
}
//---------------------------------------------------------
void _XTENSN_EXPORT DataBaseObjClass :: ListBoxSel (ControlEvt e )
{
	switch ((unsigned int)e.GetControlID()) {

	case IDLB_OCLPCLASSLIST:
		{
		CEierUhr Wait(_pW);
		KlassenAuswahl();
		_PutClipBoard.Enable();
		}
		break;

	case IDCB_OCLPBEZUGSKLASSE:
		{
		CEierUhr Wait(_pW);
		BezugsKlassenAuswahl();
		}
		break;
	}
}

//---------------------------------------------
void _XTENSN_EXPORT DataBaseObjClass :: ListBoxClk (ControlEvt e)
{
	switch ((unsigned int)e.GetControlID()) {

	case IDLB_OCLPCLASSLIST:
		{
		CEierUhr Wait(_pW);
		KlassenAuswahl();
		}
		break;
	}

}

//----------------------------------------------------------------
void DataBaseObjClass :: KlassenAuswahl ( void )
{

int iIndex = _ObjClassList.GetFirstSelected();
int iCount = _ObjClassList.GetCount();

	if (iIndex == -1 || iCount == 0 ) 
		return;
	
//----------------------------Struktur GI-Typen-----------------------
	if ( _pOBJ != NULL )
		DELETE_OBJ ( _pOBJ);
	_pOBJ = new OBJTree ;
	if ( _pOBJ == NULL )
		return;

//	Startbedingungen
	GIEXTREMUM EXT;
	SetExtremumZero ( &EXT);
	_OBJCount = 0;
	char Typ = '\0';

	char * pBuff = new char [_MAX_PATH];
	if ( _pIdent != NULL )
		DELETE_OBJ ( _pIdent);

	_pIdent = new long [ iCount + 1];
	int * pIndex = new int [ iCount + 1];
	if ( pBuff == NULL || _pIdent == NULL || pIndex == NULL ) { 
		DELETE_OBJ ( _pIdent);
		DELETE_OBJ ( pIndex);
		DELETE_OBJ ( pBuff);
		return;
	}
	long Ident;
	long Number = 0L;

	_ObjClassList.GetString (pBuff, iIndex, _MAX_PATH);
	char *ptr = strchr (pBuff, ':');
	if ( ptr == NULL ) {
		DELETE_OBJ ( _pIdent);
		DELETE_OBJ ( pIndex);
		DELETE_OBJ ( pBuff);
		return;
	} else
		*ptr = '\0';

	ulong uIdent = 0L;

// Identifikator besorgen !

#if _MSC_VER < 1200

	HRESULT hr = IdentFromClassX (pBuff, &uIdent);
	if (FAILED(hr)) {
		uIdent = 0;
	}
#else
	uIdent = _ObjClassList.GetItemData (iIndex);		// Ident ist am Item gespeichert
	TX_ASSERT(0 != uIdent);
#endif // _MSC_VER < 1200


	Ident = (long) uIdent;


	*ptr = ':';
	if ( _BezugsTyp != '\0' && _BezugsBox.isChecked())
		Typ = _BezugsTyp;
	else
		Typ = *(ptr+1);

	_SelTyp = Typ;
	Number++;
	*(_pIdent+Number) = Ident;
	*(pIndex+Number) = iIndex;
	
	iIndex=_ObjClassList.GetNextSelected ();

	while ( iIndex != -1 ) {

		_ObjClassList.GetString (pBuff, iIndex, _MAX_PATH);
		char *ptr = strchr (pBuff, ':');
		if ( ptr == NULL ) {
			DELETE_OBJ ( _pIdent);
			DELETE_OBJ ( pIndex);
			DELETE_OBJ ( pBuff);
			return;
		} else
			*ptr = '\0';


		ulong uIdent = (ulong)Ident;

	#if _MSC_VER < 1200

		HRESULT hr = IdentFromClassX (pBuff, &uIdent);
		if (FAILED(hr)) {
			uIdent = 0;
		}
	#else
		uIdent = _ObjClassList.GetItemData (iIndex);		// Ident ist am Item gespeichert
		TX_ASSERT(0 != uIdent);
	#endif // _MSC_VER < 1200

		Ident = (long) uIdent;

		if ( Typ == *(ptr+1) ) {
			Number++;
			*(_pIdent+Number) = Ident;
			*(pIndex+Number) = iIndex;
		}

		iIndex=_ObjClassList.GetNextSelected ();
	}

	*_pIdent = Number;
	*pIndex = ( int) Number;
	_ObjClassList.ChangeSelected( Range (0,iCount-1),FALSE);
	for ( int i = 0; i < *pIndex ; i++ ) {
		iIndex = *(pIndex + i + 1);
		_ObjClassList.ChangeSelected ( iIndex,TRUE);
		Ident = *(_pIdent+i+1);
		AddCountObjClassTypes ( TRUE, Ident , &Typ, &EXT);
	}
//----------HelpText----------------------------------------------
	if ( *pIndex > 0 ) {
		if ( *pIndex == 1 )
			ShowPBDText ( Ident, 'i' );
		else
			_pHelpText -> SetHelpText (ResID(IDH_HELPOKLSUMM,&_RF));
	}

	DELETE_OBJ ( pIndex);	
	DELETE_OBJ ( pBuff);

	BuildExtremum ( &Typ, &EXT);

	_Minim = EXT.rMinimum;
	_Maxim = EXT.rMaximum;
	_NumObjects = EXT.lObjCount;
	_SumObject = EXT.rSumme;
	_Median = EXT.rMedianWert;
	_Mittelwert = EXT.rMittelWert;

	if ( !_BezugsBox.isChecked() || _BezugsID == 0 ) 
		LoadBezugsWert ( &Typ );

	ShowCountObjects (&Typ );

	return;	
}
//--------------------------------------------------------------------

//----------------------------------------------------------------
void DataBaseObjClass :: BezugsKlassenAuswahl ( void )
{

	if ( _pOBJ != NULL )
		DELETE_OBJ ( _pOBJ);
	_pOBJ = new OBJTree ;
	if ( _pOBJ == NULL )
		return;

int iIndex = _BezugsList.GetCurrentIndex();
	
//----------------------------Struktur GI-Typen-----------------------

	if (iIndex != -1) {

		char * pBuff = new char [_MAX_PATH];
		if ( pBuff == NULL ) 
			return;
//	Startbedingungen
	GIEXTREMUM EXT;
		SetExtremumZero ( &EXT);
		_OBJCount = 0;
		char Typ = '\0';

		long Ident = 0L;
		_BezugsList.GetCurrentString (pBuff);
		char *ptr = strchr (pBuff, ':');
		if ( ptr == NULL ) {
			DELETE_OBJ ( pBuff);
			return;
		} else
			*ptr = '\0';

		ulong uIdent = (ulong)Ident;
	#if _MSC_VER < 1200

		HRESULT hr = IdentFromClassX (pBuff, &uIdent);
		if (FAILED(hr)) {
			uIdent = 0;
		}
	#else
		uIdent = _BezugsList.GetItemData (iIndex);		// Ident ist am Item gespeichert
		TX_ASSERT(0 != uIdent);
	#endif // _MSC_VER < 1200


		Ident = (long) uIdent;

		*ptr = ':';
		Typ = *(ptr+1);

		ShowBezugsPBDText( Ident, 'i');

		AddCountObjClassTypes ( FALSE, Ident , &Typ, &EXT);

		DELETE_OBJ ( pBuff);

		BuildExtremum ( &Typ, &EXT);


		_BezMinim = EXT.rMinimum;
		_BezMaxim = EXT.rMaximum;
		_BezNumObjects = EXT.lObjCount;
		_BezSumObject = EXT.rSumme;
		_BezMedian = EXT.rMedianWert;
		_BezMittelwert = EXT.rMittelWert;


		if ( !_BezugsBox.isChecked() ) {
			_BezugsBox.SetChecked ( TRUE );
			short CTyp = OTFlaeche;
			if ( Typ == 'L' )
				CTyp = OTLinie;
			LoadObjKlassenList( &CTyp);
			if ( _SelTyp == Typ ) {
				SelectIdents();
				ShowCountObjects (&Typ );
			} else {		// TypWechsel
				DELETE_OBJ ( _pIdent);
				_SelTyp = '\0';
				_NumObjects = 0L;
				ShowCountObjects(&Typ);
			}
		} else {
			if ( _SelTyp != Typ ) {
				short CTyp = OTFlaeche;
				if ( Typ == 'L' )
					CTyp = OTLinie;
				LoadObjKlassenList( &CTyp);
				DELETE_OBJ ( _pIdent);
				_SelTyp = '\0';
				_NumObjects = 0;
				ShowCountObjects ( &Typ);
			} else {
				if ( _BezugsID == 0L ) {		//1.Mal
					short CTyp = OTFlaeche;
					if ( Typ == 'L' )
						CTyp = OTLinie;
					LoadObjKlassenList( &CTyp);
				}
				SelectIdents();
				ShowCountObjects (&Typ );
			}
		}

		_BezugsTyp = Typ;
		_BezugsID = Ident;

	}
	return;	
}
//--------------------------------------------------------------------
void DataBaseObjClass :: AddCountObjClassTypes ( Bool Flag, long Key, char * Typ , struct GIEXTREMUM *p) 
{
	if ( _pIDM == NULL )
		return;
	CTable t ( *_pIDM );
	if ( t.Find ( &Key)) {
		IDMLock l(t);
		double Wert;

//-----------------Objekte sammeln---------------
		IDGITYP Id;
		SetZero(&Id);

		if ( Flag )		// MKode wird beachtet
			Id.lMCode = _MCode;
		
		OBJTree * pOBJ = l->pObjects();
		if ( !pOBJ)
			return;

		if ( Id.lMCode == 0L) {
			if ( *Typ == 'F' ) {
				if ( 0.0 == Id.rArea ) {
					CreateObjectTree ( pOBJ, Typ, &Id);
					l->SetFlaechenParam(&Id);
				} else {
					Id.lArea = l->Flaeche();
					Id.rArea = l->FlInhalt();
					Id.rAreaMin = l->rAreaMin();
					Id.rAreaMax = l->rAreaMax();
				}
			} else {
				if ( 0.0 == Id.rPolyLen ) {
					CreateObjectTree ( pOBJ, Typ, &Id);
					l->SetLinienParam(&Id);
				} else {
					Id.lLine = l->Linie();
					Id.rPolyLen = l->LinLaenge();
					Id.rPolyLenMin = l->rPolyLenMin();
					Id.rPolyLenMax = l->rPolyLenMax();
				}
			}

		} else 
			CreateObjectTree ( pOBJ, Typ , &Id);

		if ( *Typ == 'F' ) {
			p->lObjCount = p->lObjCount + Id.lArea;
			p->rSumme = p->rSumme + Id.rArea;
			Wert = Id.rAreaMin;
			if ( p->rMinimum == -1.0 )
				p->rMinimum = Id.rAreaMin;
			else {
				if ( p->rMinimum > Wert )
					p->rMinimum = Id.rAreaMin;
			}
			Wert = Id.rAreaMax;
			if ( p->rMaximum == -1.0 )
				p->rMaximum = Id.rAreaMax;
			else {
				if ( p->rMaximum < Wert )
					p->rMaximum = Id.rAreaMax;
			}
		}
		if ( *Typ == 'L' ) {
			p->lObjCount = p->lObjCount + Id.lLine;
			p->rSumme = p->rSumme + Id.rPolyLen;
			Wert = Id.rPolyLenMin;
			if ( p->rMinimum == -1.0 )
				p->rMinimum = Id.rPolyLenMin;
			else {
				if ( p->rMinimum > Wert )
					p->rMinimum = Id.rPolyLenMin;
			}
			Wert = Id.rPolyLenMax;
			if ( p->rMaximum == -1.0 )
				p->rMaximum = Id.rPolyLenMax;
			else {
				if ( p->rMaximum < Wert )
					p->rMaximum = Id.rPolyLenMax;
			}
		}
	}
	return;
}
//--------------------------------------------------------------------
void DataBaseObjClass :: CreateObjectTree (OBJTree *pObj , char * Typ, IDGITYP *p)
{
	if ( _pOBJ == NULL)
		return;
	if ( pObj == NULL)
		return;

	CTable t(*pObj);
	Bool Flag = FALSE;
	for ( t.First(); t.Valid(); t.Next() ) {
		OBJLock l(t);
		Flag = FALSE;
		long ONr = l->Object();
		OBJECTTYP ObjStr;
		SetObjZero ( &ObjStr );
		ObjStr.lIdent = l->Ident();
		ObjStr.iGITyp = l->ObjectTyp();
		ObjStr.rPolyLen = l->LinLaenge();
		ObjStr.rArea = l->FlInhalt();
		if ( *Typ == 'F' && ObjStr.iGITyp == OTFlaeche )
			Flag = TRUE;
		if ( *Typ == 'L' && ObjStr.iGITyp == OTLinie )
			Flag = TRUE;
		if ( p->lMCode != 0L ) {
			if ( !ExistMCodeInObject ( _MFlag, p->lMCode, ONr ) )
				Flag = FALSE;
		}
		if ( Flag ) {
			_OBJCount++;
			OBJCreator OBJCr ( *_pOBJ );
			ContCreate ( OBJCr, OBJ ) ( ONr, &ObjStr );
//			if ( p->lMCode != 0L ) {
				if ( *Typ == 'L' ) {
					p->lLine ++;
					p->rPolyLen = p->rPolyLen + l->LinLaenge(); 
					if ( p->rPolyLenMin > l->LinLaenge() )
						p->rPolyLenMin = l->LinLaenge();
					if ( p->rPolyLenMax < l->LinLaenge() )
						p->rPolyLenMax = l->LinLaenge();
				}
				if ( *Typ == 'F') {
					p->lArea ++;
					p->rArea = p->rArea + l->FlInhalt();
					if ( p->rAreaMin > l->FlInhalt())
						p->rAreaMin = l->FlInhalt();
					if ( p->rAreaMax < l->FlInhalt())
						p->rAreaMax = l->FlInhalt();
				}
//			}
		}
	}
	_pOBJ->Optimize();
// Hier kann bereits der Mittelwert pro Ident bestimmt werden!
	return;

}
//-----------------------------------------------------------------------
void DataBaseObjClass :: BuildExtremum ( char *Typ , struct GIEXTREMUM *p)
{
	if ( _pOBJ == NULL )
		return;
double * pMWert;
	pMWert = MittelWertBerechnung ( _pOBJ );
	if ( pMWert == NULL )
		p->rMittelWert = 0.0;
	else {
		if ( *Typ == 'F' ) {
			p->rMittelWert = *pMWert;
		} else {
			p->rMittelWert = *(pMWert+1);
		}
		DELETE_OBJ ( pMWert);
	}

double * pMedian;
	long Count = _OBJCount;
	pMedian = MedianWertBestimmung ( Count, _pOBJ);
	if ( pMedian == NULL )
		p->rMedianWert = 0.0;
	else {
		if ( *Typ == 'F' ) {
			p->rMedianWert = *pMedian;
		} else {
			p->rMedianWert = *(pMedian+1);
		}
		DELETE_OBJ ( pMedian);
	}
	return;

}
//-----------------------------------------------------------------------
void DataBaseObjClass :: LoadBezugsWert ( char *Typ )
{
	if ( *Typ == 'F' ) {
		_BezNumObjects = _ObjectsF;
		_BezSumObject = _CumulF;
		_BezMinim = _MinF;
		_BezMaxim = _MaxF;
		_BezMedian = _MedianF;
		_BezMittelwert = _MWertF;
	} else {
		_BezNumObjects = _ObjectsL;
		_BezSumObject = _CumulL;
		_BezMinim = _MinL;
		_BezMaxim = _MaxL;
		_BezMedian = _MedianL;
		_BezMittelwert = _MWertL;
	}	
	return;
}
//-----------------------------------------------------------------------
void DataBaseObjClass :: ShowBezugsPBDText ( long Key, short TCode )
{
PBDDATA pbdData;
char *pLText = new char [1000];
	if ( pLText == NULL )
		 return;
	*pLText = NULL;
	memset (&pbdData, '\0', sizeof(PBDDATA));
	pbdData.dwSize = sizeof(PBDDATA);
	pbdData.pbdTyp = TCode;
	pbdData.pbdCode = Key;
	pbdData.pbdLText = pLText;
	pbdData.pbdKTextLen = 0;
	pbdData.pbdLTextLen = 999;
	DEX_GetPBDData (pbdData);

	if ( SucheLeerZeichen ( pLText ))
			*pLText = NULL;

	if (pLText != NULL && *pLText != NULL ) {
		if ( pbdData.pbdTemp ) {
			_pHelpText -> SetHelpText (ResID(IDH_HELPTEMPOKL,&_RF));
		} else {
			_pHelpText -> SetHelpTextV ( ResID(IDH_HELPBEZOKLBESCHREIBUNG,&_RF),pLText);
		}
	} else  {
		if ( TCode == 'i' ) {
			_pHelpText -> SetHelpText (ResID(IDT_KEINIDLANGTEXT,&_RF));
		}
	}

	DELETE_OBJ (pLText);

}
//---------------------------------------------------------------------
void DataBaseObjClass :: ShowPBDText ( long Key, short TCode )
{
PBDDATA pbdData;
char *pLText = new char [1000];
	if ( pLText == NULL )
		 return;
	*pLText = NULL;
	memset (&pbdData, '\0', sizeof(PBDDATA));
	pbdData.dwSize = sizeof(PBDDATA);
	pbdData.pbdTyp = TCode;
	pbdData.pbdCode = Key;
	pbdData.pbdLText = pLText;
	pbdData.pbdKTextLen = 0;
	pbdData.pbdLTextLen = 999;
	DEX_GetPBDData (pbdData);

	if (pLText != NULL && *pLText != NULL ) {
		if ( pbdData.pbdTemp ) {
			_pHelpText -> SetHelpText (ResID(IDH_HELPTEMPOKL,&_RF));
		} else {
			if ( TCode == 'i')
				_pHelpText -> SetHelpTextV ( ResID(IDH_HELPOKLBESCHREIBUNG,&_RF),pLText);
			else
				_pHelpText -> SetHelpTextV ( ResID(IDH_HELPMKBESCHREIBUNG,&_RF),pLText);
		}
	} else  {
		if ( TCode == 'i' ) {
			_pHelpText -> SetHelpText (ResID(IDT_KEINIDLANGTEXT,&_RF));
		} else {
			_pHelpText -> SetHelpText (ResID(IDT_KEINMKLANGTEXT,&_RF));
		}
	}

	DELETE_OBJ (pLText);

}

//-----------------------------------------------------------------------
void DataBaseObjClass :: ShowNoObjects ( void )
{

char *pBuff = new char[TEXTLEN+20];
	if ( pBuff == NULL)
		return;
	ResString rsKT ( ResID (IDT_KEINE, &_RF), 35);

	wsprintf ( pBuff,  ResString( ResID( IDT_OCLOBJEKTE,&_RF),35),  rsKT.Addr());
	_Objekte.SetText( pBuff );

	_ObjClassCount.SetText ( ltoa ( _IdCount,pBuff,10));

	_Minimum.SetText( NULL );
	_Maximum.SetText( NULL );
	_MedianWert.SetText( NULL );
	_MittelWert.SetText( NULL );
	_Summe.SetText( NULL );
	_Anteil.SetText( NULL );
	_NumObjects = 0L;
	DELETE_OBJ ( pBuff);
}

//-----------------------------------------------------------------------
void DataBaseObjClass :: ShowNoBezugsKlasse ( void )
{

char *pBuff = new char[TEXTLEN+20];
	if ( pBuff == NULL)
		return;
	ResString rsKT ( ResID (IDT_KEINE, &_RF), 35);

	wsprintf ( pBuff,  ResString( ResID( IDT_OCLOBJEKTE,&_RF),35),  rsKT.Addr());
	_BezObjekte.SetText( pBuff );

	_ObjClassCount.SetText ( ltoa ( _IdCount,pBuff,10));

	_BezMinimum.SetText( NULL );
	_BezMaximum.SetText( NULL );
	_BezMedianWert.SetText( NULL );
	_BezMittelWert.SetText( NULL );
	_BezSumme.SetText( NULL );
	_NumObjects = 0L;
	DELETE_OBJ ( pBuff);
}
//-----------------------------------------------------------------------
void DataBaseObjClass :: ShowCountObjects ( char *Typ )
{
//char *pNum = new char[20];
char *pNum = new char[_MAX_PATH];
char *pBuff = new char[_MAX_PATH];
	if ( pNum == NULL || pBuff == NULL) {
		DELETE_OBJ ( pBuff);
		DELETE_OBJ ( pNum);
		return;
	}
double SumObject,Minim,Maxim,Median,Mittelwert;
double BezSumObject,BezMinim,BezMaxim,BezMedian,BezMittelwert;


	_ObjClassCount.SetText ( ltoa ( _IdCount,pBuff,10));
	short iMass = 0;
	if ( _NumObjects > 0 ) {
		if ( *Typ == 'F' ) {
			_Prozent = _SumObject * 100.0 / _BezSumObject;
			if ( _SumObject /(double)QuadratKiloMeter >= 0.1) {
				SumObject = _SumObject/(double)QuadratKiloMeter;
				Minim = _Minim/(double)QuadratKiloMeter;
				Maxim = _Maxim/(double)QuadratKiloMeter;
				Median = _Median / (double)QuadratKiloMeter;
				Mittelwert = _Mittelwert / (double)QuadratKiloMeter;
				*_pEinheit = '\0';
				strcat ( _pEinheit,ResString( ResID( IDT_UNITQKM,&_RF),15));	
			} else if ( _SumObject /(double)Hektar >= 0.1) {
					SumObject = _SumObject/(double)Hektar;
					Minim = _Minim/(double)Hektar;
					Maxim = _Maxim/(double)Hektar;
					Median = _Median / (double)Hektar;
					Mittelwert = _Mittelwert / (double)Hektar;
					*_pEinheit = '\0';
					strcat ( _pEinheit,ResString( ResID( IDT_UNITHA,&_RF),15));	
					iMass = 1;
			} else {
					SumObject = _SumObject/(double)QuadratMeter;
					Minim = _Minim/(double)QuadratMeter;
					Maxim = _Maxim/(double)QuadratMeter;
					Median = _Median / (double)QuadratMeter;
					Mittelwert = _Mittelwert / (double)QuadratMeter;
					*_pEinheit = '\0';
					strcat ( _pEinheit,ResString( ResID( IDT_UNITQM,&_RF),15));	
					iMass = 2;
			}
		} else {
			_Prozent = _SumObject * 100.0 / _BezSumObject;
			if ( _SumObject / (double) KiloMeter >= 0.1) {
				SumObject = _SumObject/(double)KiloMeter;
				Minim = _Minim/(double)KiloMeter;
				Maxim = _Maxim/(double)KiloMeter;
				Median = _Median / (double)KiloMeter;
				Mittelwert = _Mittelwert / (double)KiloMeter;
				*_pEinheit = '\0';
				strcat ( _pEinheit,ResString( ResID( IDT_UNITKM,&_RF),15));	
			} else {
				SumObject = _SumObject/(double)Meter;
				Minim = _Minim/(double)Meter;
				Maxim = _Maxim/(double)Meter;
				Median = _Median / (double)Meter;
				Mittelwert = _Mittelwert / (double)Meter;
				*_pEinheit = '\0';
				strcat ( _pEinheit,ResString( ResID( IDT_UNITM,&_RF),15));	
				iMass = 1;
			}

		}	

//----------Selektierte Klassen---------------------------------
		wsprintf ( pBuff, ResString( ResID( IDT_OCLOBJEKTE,&_RF),35), ltoa ( _NumObjects,pNum,10) );
		if ( _NumObjects == 1L ) {
			wsprintf ( pBuff, ResString( ResID( IDT_OCLOBJEKT,&_RF),35), ltoa ( _NumObjects,pNum,10) );
		}
		strcat ( pBuff , "   ");
		strcat ( pBuff , _pEinheit);
		strcat ( pBuff , "  ");
		_Objekte.SetText( pBuff );
	
		ST_DtoA ( pNum, "%8.3f", Minim);
		_Minimum.SetText( pNum );
	
		ST_DtoA ( pNum, "%8.3f", Maxim);
		_Maximum.SetText( pNum );

		ST_DtoA ( pNum, "%8.3f", Median);
		_MedianWert.SetText( pNum );

		ST_DtoA ( pNum, "%8.3f", Mittelwert);
		_MittelWert.SetText( pNum );

		ST_DtoA ( pNum, "%8.3f", SumObject);
		_Summe.SetText( pNum );

		ST_DtoA ( pNum, "%5.2f", _Prozent);
		_Anteil.SetText( pNum );
	} else
		ShowNoObjects();

//----------BezugsKlassen---------------------------------
	if ( _BezNumObjects > 0 ) {
		if ( *Typ == 'F' ) {
			if ( iMass == 0) {
				BezSumObject = _BezSumObject/(double)QuadratKiloMeter;
				BezMinim = _BezMinim/(double)QuadratKiloMeter;
				BezMaxim = _BezMaxim/(double)QuadratKiloMeter;
				BezMedian = _BezMedian/(double)QuadratKiloMeter;
				BezMittelwert = _BezMittelwert/(double)QuadratKiloMeter;
				*_pEinheit = '\0';
				strcat ( _pEinheit,ResString( ResID( IDT_UNITQKM,&_RF),15));	
			} else if ( iMass == 1 ) {
				BezSumObject = _BezSumObject/(double)Hektar;
				BezMinim = _BezMinim/(double)Hektar;
				BezMaxim = _BezMaxim/(double)Hektar;
				BezMedian = _BezMedian/(double)Hektar;
				BezMittelwert = _BezMittelwert/(double)Hektar;
				*_pEinheit = '\0';
				strcat ( _pEinheit,ResString( ResID( IDT_UNITHA,&_RF),15));	

			} else {
				BezSumObject = _BezSumObject/(double)QuadratMeter;
				BezMinim = _BezMinim/(double)QuadratMeter;
				BezMaxim = _BezMaxim/(double)QuadratMeter;
				BezMedian = _BezMedian/(double)QuadratMeter;
				BezMittelwert = _BezMittelwert/(double)QuadratMeter;
				*_pEinheit = '\0';
				strcat ( _pEinheit,ResString( ResID( IDT_UNITQM,&_RF),15));	
			}
		} else {
			if ( iMass == 0 ) {
				*_pEinheit = '\0';
				strcat ( _pEinheit,ResString( ResID( IDT_UNITKM,&_RF),15));	

				BezSumObject = _BezSumObject / (double)KiloMeter;
				BezMinim = _BezMinim / (double)KiloMeter;
				BezMaxim = _BezMaxim / (double)KiloMeter;
				BezMedian = _BezMedian / (double)KiloMeter;
				BezMittelwert = _BezMittelwert / (double)KiloMeter;
			} else {
				*_pEinheit = '\0';
				strcat ( _pEinheit,ResString( ResID( IDT_UNITM,&_RF),15));	

				BezSumObject = _BezSumObject / (double)Meter;
				BezMinim = _BezMinim / (double)Meter;
				BezMaxim = _BezMaxim / (double)Meter;
				BezMedian = _BezMedian / (double)Meter;
				BezMittelwert = _BezMittelwert / (double)Meter;
			}
		}	

		wsprintf ( pBuff, ResString( ResID( IDT_OCLOBJEKTE,&_RF),35), ltoa ( _BezNumObjects,pNum,10) );
		if ( _BezNumObjects == 1L ) {
			wsprintf ( pBuff, ResString( ResID( IDT_OCLOBJEKT,&_RF),35), ltoa ( _BezNumObjects,pNum,10) );
		}
		strcat ( pBuff , "   ");
		strcat ( pBuff , _pEinheit);
		strcat ( pBuff , "  ");
		_BezObjekte.SetText( pBuff );

		ST_DtoA ( pNum, "%8.3f", BezMinim);
		_BezMinimum.SetText( pNum );

		ST_DtoA ( pNum, "%8.3f", BezMaxim);
		_BezMaximum.SetText( pNum );

		ST_DtoA ( pNum, "%8.3f", BezMedian);
		_BezMedianWert.SetText( pNum );

		ST_DtoA ( pNum, "%8.3f", BezMittelwert);
		_BezMittelWert.SetText( pNum );

		ST_DtoA ( pNum, "%8.3f", BezSumObject);
		_BezSumme.SetText( pNum );
	}

	DELETE_OBJ ( pNum);
	DELETE_OBJ ( pBuff);

	return;
}         
//////////////////////////////////////////////////////////////////////

//------------------ClipBoard------------------------------------
void DataBaseObjClass :: PutIdentToClipBoard ( void )
{

	int max = _ObjClassList.GetCount();
	if ( max <= 0 )
		return;

	unsigned short * pParam = new unsigned short [ MaxParam];
	if ( pParam == NULL )
		return;

	short MFlag = TRUE;

	_isClipUeberschrift = true;
	_isClipKumulativ = true;
	_isClipEintrag = true;
	_isClipEigenschaft = true;

	CEierUhr Wait ( _pW);

	ClipBoardClass CBC ( this, CLIPBOARDVIEW, _RF, OKlDataBase, pParam);
	CBC.Show();
	if ( CBC.Result()== 0 ) {
		DELETE_OBJ ( pParam);
		return;
	} else {
		_isClipUeberschrift = CBC.Ueberschrift_isChecked();
		_isClipKumulativ = CBC.Kumulativ_isChecked();
		_isClipEintrag = CBC.Eintrag_isChecked();
		_isClipEigenschaft = CBC.Eigenschaft_isChecked();
	}

	int MaxBuf = ( max + 10) * (int) MAXRECORD;
	char * pBuf = new char [ MaxBuf ];
	if ( pBuf == NULL ) {
		DELETE_OBJ ( pParam);
		return;
	}

	*pBuf = '\0';

	{	//	ClipBoard
		CClipboard CLP;
	
		long Mkode = 0L;
//
		{	// GlobalClass
		void * pData; 
	
		pData = ( void *) _pIDM;  
		short iTyp = OTLinie;

		if (_SelTyp == 'F' )
			iTyp = OTFlaeche;
		
		GlobalObjClass GOC ( &_RF, MFlag, Mkode, pData , OKlDataBase, pParam, iTyp);
		if ( 0.0 < _BezSumObject )
			GOC.SetGlobalWert(_BezSumObject);
		char *pText;

		if ( _isClipUeberschrift ) {
			pText = GOC.GetCaption();
			strcat ( pBuf , pText);
		}

		int iIndex = _ObjClassList.GetFirstSelected();

		if (iIndex != -1) {
			long Ident = SetIdent ( iIndex );

			pText = GOC.GetText ( Ident , _isClipEigenschaft);
			if ( _isClipEigenschaft )
				strcat ( pBuf , pText);

			iIndex=_ObjClassList.GetNextSelected ();
			while ( iIndex != -1 ) {
				Ident = SetIdent ( iIndex );
				pText = GOC.GetText ( Ident , _isClipEigenschaft);
				if ( _isClipEigenschaft )
					strcat ( pBuf , pText);
				iIndex=_ObjClassList.GetNextSelected ();
			}
		}
//	Kumulativ
		if ( _isClipKumulativ ) {
			pText = GOC.GetCumulate();
			strcat ( pBuf , pText);
		}
//	Eintraege
		if ( _isClipEintrag ) {
			pText = GOC.GetEintrag();
			strcat ( pBuf , pText);
		}
		CLP.Insert ( pBuf );
		}	// GlobalClass

	}   // ClipBoard
	DELETE_OBJ ( pBuf );
	DELETE_OBJ ( pParam);
	return;
}
//----------------------------------------------------------------
long DataBaseObjClass :: SetIdent ( int iIndex )
{

	char * pBuff = new char [_MAX_PATH];
	if ( pBuff == NULL ) 
		return 0;
	long Ident;
	_ObjClassList.GetString (pBuff, iIndex, _MAX_PATH);
	char *ptr = strchr (pBuff, ':');
	if ( ptr == NULL ) {
		DELETE_OBJ ( pBuff);
		return 0;
	} else
		*ptr = '\0';

	ulong uIdent = 0;

// Identifikator besorgen !

#if _MSC_VER < 1200

	HRESULT hr = IdentFromClassX (pBuff, &uIdent);
	if (FAILED(hr)) {
		uIdent = 0;
	}
#else
	uIdent = _ObjClassList.GetItemData (iIndex);		// Ident ist am Item gespeichert
	TX_ASSERT(0 != uIdent);
#endif // _MSC_VER < 1200

	Ident = (long) uIdent;

	*ptr = ':';
	DELETE_OBJ ( pBuff);

	return Ident;	

}
//-----------------------------------------------------------------

//---------------------------------------------------------------------
//--------------------------------------------------------------------
//--------------------------------------------------------------------
void SetExtremumZero ( GIEXTREMUM * p )
{
	p->lObjCount = 0L;
	p->rMinimum = -1.0;
	p->rMaximum = -1.0;
	p->rSumme = 0.0;
	p->rMittelWert = -1.0;
	p->rMedianWert = -1.0;
	return;
}
//---------------------------------------------------------------------------
//------------------EXTERNE--------------------------------------------------
//-------------------Objektklassenanzahl-----------------
extern "C"  Bool PASCAL _XTENSN_EXPORT NumerateIdents ( long Ident, Bool, void *pData)
  {
	
	CTable t( * ((IDPOINT * ) pData)->pID );
	if ( !t.Find (&Ident) ) {
		IDGITYP InStr;
		SetZero ( &InStr );	
		InStr.lMCode = 0L;
		InStr.iITyp = DEX_GetIdentObjTypes(Ident);
		IDMCreator IDMCr ( * ((IDPOINT * )pData)->pID );
		ContCreate ( IDMCr, IDM ) ( Ident,&InStr );

		((IDPOINT *)pData)->Number++;
		
	}
	return TRUE;
  }
//------------------------------------------------------
extern "C"  Bool PASCAL _XTENSN_EXPORT SearchObjects ( long ONr, short iObjTyp, void *pData)
  {

	if ( (((TYPVECTOR *)pData)->GiTyp & iObjTyp) == 0 )
			return TRUE;
	long * pObj = ((TYPVECTOR *)pData)->pOBJ;
	*pObj= *pObj + 1;
	long L = *pObj;
	*(pObj + L ) = ONr;
	*(pObj + L + 1 ) = ( long ) iObjTyp; 
	*pObj= *pObj + 1;
	return TRUE;
  }
//-----Sichten/Identifikatoren--------
extern "C"  Bool PASCAL _XTENSN_EXPORT NumerationDB ( char *pPtr, Bool iNotLast, void *pData)
  {
	(* (long *)pData)++;
	return TRUE;
  }

//-----Merkmale--------
extern "C"  Bool PASCAL _XTENSN_EXPORT NumerationMK ( long MKode, Bool iNotLast, void *pData)
  {
	(* (long *)pData)++;
	return TRUE;
  }

//------------------EXTERNE--------------------------------------------------

//---------------------------------------------------------------------------
//-----------------Nur für uns ----------------------------------------------
//----------------Suchen eines Datenbankobjektes ----------------------------
 
// Konstruktoren/Destruktoren der DialogFenster --------------------------------

#pragma warning (disable: 4355)

DataBaseObject :: DataBaseObject (pWindow pW, uint res, ResourceFile &RF )
	     : DialogWindow (pW, ResID ( res, &RF)),
	       _RF (RF),
	       _Objekt ( this, IDS_DBOBJECTANZEIGE),
	       OKButton (this, IDOK),
	       CancelButton (this, IDCANCEL)

{
//	StartWerte
	_pW = pW;
//	pW->Disable();
	_Objekt.SetText( NULL);	
	_Objekt.SetFocus();

	return;
}
//-----------------------------------------------------------
#pragma warning (default: 4355)

DataBaseObject :: ~DataBaseObject (void)
{
//	_pW->Enable();
}
//---------------------------------------------------------

//-----------------------------------------------------------------
void _XTENSN_EXPORT DataBaseObject :: ButtonClick (ControlEvt e)
{

	switch ((unsigned int)e.GetControlID()) {

	case IDCANCEL:
		{
		EndDlg (0);
		}
		break;

	case IDOK:
		{
		_lONr = 0L;
		char *pBuf = new char [_MAX_PATH];
		if (pBuf) {
			_Objekt.GetText ( pBuf , _MAX_PATH );
			_lONr = atol ( pBuf );
			DELETE_OBJ ( pBuf);
		}
		EndDlg (1);
		}
		break;
	}
}

//---------------------------------------------------------------------------
// Ende DBINFO.CXX
