/* File: CADDYASC.CXX

   Das Modul beinhaltet die Einsprungroutinen des CADdy-Filters.
   Erzeugt wird das CADdy-ASCII-Format der Version 7.00.

   Stand vom: 11. Mai 1994
*/

#include "pheader.h"

extern "C" {
	#include <io.h>		 	// setmode ()
	#include <fcntl.h>	  	// O_TEXT
	#include <string.h>	 	// memset ()
	#include <xtensnxx.h>   // DEXX_MAINWINDOW
}

#include <attribs.hxx>		// IdentDescription u.a.
#include <ristypes.hxx>		// OT_Punkt u.a.
#include <impexp.hxx>		// MFELD, GSTRUCT, IdentDescription ...
#include <strdup.hxx>	   	// StringDup u.a.
#include <resstrg.h>		// Resourcen-Defines

#include "caddyasc.hr"	   	// Konstanten
#include "caddyasc.hxx"	 	// zugeh. Header
#include "caddyrec.hxx"	 	// CaddyRekordBaum

#ifndef __NT__
#define HUGE __huge
#else
#define HUGE
#endif

// Konstanten
const short DummyKoOrdSize = 20;			// Größe der Bildmaße-Koordinaten
const short DummySize = (2 * DummyKoOrdSize) + 2; // Größe des Dummy-Bereiches
const pchar pFormatBildMasse = "%20.4f";
const double KorrFakt = 1.05;		  		// Bildmaße um 5% vergrößern
const char VersionText [] = "7.00";	 		// CADdy-Versions-Text
const char DateiEndeText [] = "Ende der Datei";
char pKoordFormat [] = "%-11.5f"; 			// Format für Ausgabe einer Koordinate
const char ColorExtension [] = ".VIS";	  	// Datei-Extension f. Vis-Info
const char VisTempFile [] = "VISINFO";	  	// Name der VisInfo-Template-Datei
const char VisTempFileExt [] = ".TPL";	  	// zugeh. Extension
const char IniFileExt []	 = ".INI";	  	// Ini-File-Extension
const double StandardSymGroesse = 30;	   	// Standard-Symbolgröße

// globale Variablen
CaddyRekordBaum *pCRB = NULL;				// Caddy-Attribute-Baum
OFSTRUCT *pColFileStruct = NULL;		 	// VisInfo-File-Struct
OFSTRUCT *pVisInfoTemplStruct = NULL;		// VisInfo-Template-Struct
ResourceFile *pRF = NULL;
char pIniFilePath [_MAX_PATH] = "";	 		// vollst. Ini-File-Name

double XMax = 0;							// größten Koordinaten
double YMax = XMax;

double SymGroesse = StandardSymGroesse;  	// aktuelle Symbolgröße

long BildMassePos = 0;				  		// Datei-Position der Bildmaße
Bool FirstData = True;				  		// erstmaliges Datenausgeben

HWND __hWndM;						   		// Handle auf Elternfenster
UINT __DexCmd;
UINT __DexxCmd;
extern "C" {
extern char pDLLName [_MAX_PATH];			// Puffer für DLL-Name
}

extern short StandEbene;					// Standard-Ebene
extern double StandLinBrFakt;   			// Linien-Breiten-Faktor
extern long StandMKode;		 				// Merkmals-Kode für CADdy-Anbindung
extern double StandTextAbstFakt;			// Zeichenabstand = 0.25 * Zeichenhöhe
extern double StandTextBreitenFakt;	 		// Breite = Hoehe * 0.5
extern double StandTextHoehFakt;			// Text-Höhe korrigieren
extern double StandTextRotFakt;		 		// math pos. drehen
extern long StandTextMKode;			 		// Merkmalskode eines Textwertes

ErrCode OutputWarnungIdent (short ResourceId, long Ident); // Warnung ausgeben
void _GetTextObjKode (void);		// Merkmalskode für Textanbindung lesen

#ifdef _DEBUG
HRESULT ClassFromIdentX (ULONG ulIdent, char *pBuffer, int iBuffLen)
{
CLASSFROMIDENT CFI;

	INITSTRUCT(CFI, CLASSFROMIDENT);
	CFI.ulIdent = ulIdent;
	CFI.pClass = pBuffer;
	CFI.iBuffLen = iBuffLen;
	if (NULL != pBuffer && iBuffLen > 0)
		pBuffer[0] = '\0';
	return DEX_GetClassFromIdent(CFI);
}
#endif

extern "C" {	// alle exportierten Funktionen sollen _pascal sein

// Beginn des DatenExports ------------------------------------------------
ErrCode EXPORTFLT PASCAL CadAscExportBegin (char *lpFileName, OFSTRUCT &of,
											OutMode OutFlag, HWND hParWnd) {
	int fh, VIT_FileHandle, ColFileHandle;  // File-Handle
	int OpenMode = OF_WRITE;

	char OutPath[_MAX_PATH];
	char Drive[_MAX_DRIVE], Dir[_MAX_DIR];
	char FName[_MAX_FNAME], Ext[_MAX_EXT];

//  globale Variablen init.
	XMax = YMax = 0;
	pCRB = NULL;
	__hWndM = hParWnd;
	FirstData = True;
	BildMassePos = 0;

//  Resource-File-Objekt init.
	pRF = new ResourceFile ((char *) pDLLName);
	if (!pRF)
		return EC_NOMEMORY;

//  Nachrichten registrieren lassen
	ResString RS (IDS_DEXMESSAGE, 80);
	if (!(__DexCmd = RegisterWindowMessage (RS.Addr ())))
		return EC_NODEXMESSAGE;

//  für C++ Nachrichten
	RS = ResString (IDS_DEXXMESSAGE, 80);
	if (!(__DexxCmd = RegisterWindowMessage (RS.Addr ()))) {
		DELETE_OBJ (pRF);
		return EC_NODEXMESSAGE;
	}

//  Ini-Datei-Namen bilden: nur vollständigen Dateinamen !
	_splitpath (pDLLName, Drive, Dir, FName, Ext);
	lstrcpy (pIniFilePath, FName);
	lstrcat (pIniFilePath, IniFileExt);

//  evtl. Standard-Werte init.
	char Buffer [81] = "";
	double Val;

//  Text-Höhen-Faktor
	RS = ResString (ResID (IDS_STANDARDSECT, pRF), 80);
	ResString RS1 (ResString (ResID (IDS_STTEXTHOEFAKT, pRF), 80));
	if (GetPrivateProfileString (RS.Addr (), RS1.Addr (), "",
			Buffer, sizeof (Buffer) - 1 , pIniFilePath)) {
			Val = atof (Buffer);
			if (Val)							// wenn gültiger Wert,
				StandTextHoehFakt = Val;		// dann übernehmen
	}

//  Text-Breiten-Faktor
	RS1 = ResString (ResID (IDS_STTEXTBRFAKT, pRF), 80);
	if (GetPrivateProfileString (RS.Addr (), RS1.Addr (), "",
			Buffer, sizeof (Buffer) - 1 , pIniFilePath)) {
			Val = atof (Buffer);
			if (Val)							// wenn gültiger Wert,
				StandTextBreitenFakt = Val;	 // dann übernehmen
	}

//  Text-Abstands-Faktor
	RS1 = ResString (ResID (IDS_STTEXTABSTFAKT, pRF), 80);
	if (GetPrivateProfileString (RS.Addr (), RS1.Addr (), "",
			Buffer, sizeof (Buffer) - 1 , pIniFilePath)) {
			Val = atof (Buffer);
			if (Val)							// wenn gültiger Wert,
				StandTextAbstFakt = Val;		// dann übernehmen
	}

//  Text-Rotations-Faktor
	RS1 = ResString (ResID (IDS_STTEXTROTFAKT, pRF), 80);
	if (GetPrivateProfileString (RS.Addr (), RS1.Addr (), "",
			Buffer, sizeof (Buffer) - 1 , pIniFilePath)) {
			Val = atof (Buffer);
			if (Val)							// wenn gültiger Wert,
				StandTextRotFakt = Val; // dann übernehmen
	}

//  Merkmalskode für Textwert lesen
	_GetTextObjKode ();

//  Linien-Breiten-Faktor
	RS1 = ResString (ResID (IDS_STLINBRFAKT, pRF), 80);
	if (GetPrivateProfileString (RS.Addr (), RS1.Addr (), "",
			Buffer, sizeof (Buffer) - 1 , pIniFilePath)) {
			Val = atof (Buffer);
			if (Val)							// wenn gültiger Wert,
				StandLinBrFakt = Val;		   // dann übernehmen
	}

//  Merkmals-Kode
	RS1 = ResString (ResID (IDS_STMERKMKODE, pRF), 80);
	if (GetPrivateProfileString (RS.Addr (), RS1.Addr (), "",
			Buffer, sizeof (Buffer) - 1 , pIniFilePath)) {
			long Kode = atol (Buffer);
			if (Kode)						   // wenn gültiger Wert,
				StandMKode = Kode;			  // dann übernehmen
	}

//  Symbolgroessen-Faktor für Skalierung
	SymGroesse = StandardSymGroesse;
	RS1 = ResString (ResID (IDS_STSYMGROESSE, pRF), 80);
	if (GetPrivateProfileString (RS.Addr (), RS1.Addr (), "",
			Buffer, sizeof (Buffer) - 1 , pIniFilePath)) {
			Val = atof (Buffer);
			if (Val)							// wenn gültiger Wert,
				SymGroesse = Val;			   // dann übernehmen
	}

//  Ebene
	RS1 = ResString (ResID (IDS_STEBENENNR, pRF), 80);
	if (GetPrivateProfileString (RS.Addr (), RS1.Addr (), "",
			Buffer, sizeof (Buffer) - 1 , pIniFilePath)) {
			short EbNr = atoi (Buffer);
			if (EbNr)						   // wenn gültiger Wert,
				StandEbene = EbNr;			  // dann übernehmen
	}

//  wenn neue Info angehängt werden soll
	if (OutFlag == OMConcatinate) {
                DEX_Error (RC_CADDYASC, WC_NOTAPPEND);
                return WC_NOTAPPEND;
	}

	if ((fh = OpenFile (lpFileName, &of, OF_EXIST + OF_WRITE)) >= 0) {
		if (OutFlag == OMOverwrite) // Datei exist. u. überschreiben
			OpenMode += OF_CREATE;
	} else
		OpenMode += OF_CREATE;	  // Datei existiert nicht

//  Datei öffnen
	if ((fh = OpenFile (lpFileName, &of, OpenMode)) < 0)
		return EC_NOFILE;

//  Datei für VisInfo-Tabelle öffnen
	_splitpath (lpFileName, Drive, Dir, FName, Ext);
	_makepath (OutPath, Drive, Dir, FName, ColorExtension);
	pColFileStruct = new OFSTRUCT;
        if (!pColFileStruct)  {
                DEX_Error (RC_ACADDXF, EC_NOMEMORY);
                return EC_NOMEMORY;
        }                
	if ((ColFileHandle = OpenFile (OutPath, pColFileStruct,
								   OF_EXIST + OF_CREATE + OF_WRITE)) < 0)
		return EC_NOFILE;

//  Datei für VisInfo-Template öffnen
	_makepath (OutPath, Drive, Dir, VisTempFile, VisTempFileExt);
		pVisInfoTemplStruct = new OFSTRUCT;
        if (!pVisInfoTemplStruct) {
                DEX_Error (RC_ACADDXF, EC_NOMEMORY);
                return EC_NOMEMORY;                        
        }
	if ((VIT_FileHandle = OpenFile (OutPath, pVisInfoTemplStruct,
								   OF_EXIST + OF_CREATE + OF_WRITE)) < 0)
		return EC_NOFILE;

//  Beschreibungsbäume anlegen
	pCRB = new CaddyRekordBaum ();
        if (!pCRB) {
                DEX_Error (RC_CADDYASC, EC_NOMEMORY);
                return EC_NOMEMORY;
        }

	return (ErrCode) _lclose (fh);
}

// Ausgeben einer Kommentarzeile -------------------------------------------
ErrCode EXPORTFLT PASCAL CadAscExportComment (OFSTRUCT &, char *) {
	return EC_OKAY;
}

// Ausgeben der HeaderInformation ----------------------------------------
ErrCode EXPORTFLT PASCAL CadAscExportHeader (OFSTRUCT &, char *) {

	return EC_OKAY;
}

// Ausgeben der BeschreibungsInformation ------------------------------------
ErrCode EXPORTFLT PASCAL CadAscExportDescription (OFSTRUCT &, char *,
												 char *) {
	return EC_OKAY;
}

// Lesen und speichern aller ID-Eigenschaften -------------------------------
ErrCode EXPORTFLT PASCAL CadAscExportIdentDescription (IdentDescription &ID)
{
	ErrCode EC = EC_OKAY;

	if (!pCRB)
		return EC_SYSERROR;

//  prüfe Parameter
	VisInfo *pVI = &ID.VisInfoObj ();
	if (!pVI)                                  
		return OutputWarnungIdent (IDS_IDENTWARNGTYP, ID.ID ());
	
	switch (pVI -> isA ()) {
		case VT_Punkt : {
		//  Symbol ggf. ersetzen
			switch (pVI -> Style ()) {
				case 20:
					pVI -> Style () = 178;
				break;
				case 249:
					pVI -> Style () = 250;
				break;
			}
		}
		break;
		case VT_Linie:
		break;
		case VT_Flaeche:
		break;
		case VT_Text:
		break;
		case VT_Default:
		default:                                   
			return OutputWarnungIdent (IDS_IDENTWARNGTYP, ID.ID ());
		break;
	}

//  VisInfo-Datei öffnen
	int cfh;
	if ((cfh = OpenFile (NULL, pColFileStruct, OF_REOPEN+OF_WRITE)) < 0) {
		_lclose (cfh);
		return EC_NOFILE;
	}
	setmode (cfh, O_TEXT);
	_llseek (cfh, 0L, SEEK_END);				// Datei-Zeiger ans Ende
	if ((EC = pCRB -> AddCaddyRekord (ID, cfh)) == EC_OKAY)
		return (ErrCode) _lclose (cfh);
	else
		return EC;
}

// Lesen und speichern aller Merkmals-Eigenschaften -------------------------_
ErrCode EXPORTFLT PASCAL CadAscExportMerkmalDescription (MerkmalDescription &)
{
	return EC_OKAY;
}

// Ausgeben der TrailerInformation --------------------------------------
ErrCode EXPORTFLT PASCAL CadAscExportTrailer (OFSTRUCT &of, const char *)
{
	register int fh;	 // FileHandle
	register ErrCode EC;
		
	if ((fh = OpenFile (NULL, &of, OF_REOPEN+OF_READWRITE)) < 0)
	// Fehler: kann Datei nicht eröffnen
		return EC_NOFILE;
	_llseek (fh, 0L, SEEK_END);
	setmode (fh, O_TEXT);

	if ((EC = ExportLine (fh, DateiEndeText)) < 0) {
		_lclose (fh);
		return EC;
	}

//  Bildmaße ausgeben
	if ((EC = ExportBildMasse (fh)) < 0) {
		_lclose (fh);
		return EC;
	}

	return (ErrCode) _lclose (fh);
}

// Ausgabe eines Geometrie-Objektes -----------------------------------------
ErrCode EXPORTFLT PASCAL CadAscExportData (OFSTRUCT &of, GSTRUCT &GS, MFELD *MF,
										  RSTRUCT *, char *)
{
	ErrCode EC = EC_OKAY;			   // return-Kode
	int fh;							 // File-Handle

//  existiert der Caddy-Beschreibungs-Baum ?
	if (!pCRB)
		return EC_SYSERROR;

//  ASCII-Datei öffnen
	if ((fh = OpenFile (NULL, &of, OF_REOPEN+OF_READWRITE)) < 0)
		return EC_NOFILE;
	setmode (fh, O_TEXT);

//  vor den ersten Daten Kopf ausgeben
	if (FirstData) {
		FirstData = False;				  // Flag rücksetzen

		pCRB -> Optimize ();					// Baum optimieren

	//  VisInfo-Template-Datei öffnen
		int v_fh;
		if ((v_fh = OpenFile (NULL, pVisInfoTemplStruct,
						  OF_REOPEN+OF_WRITE)) < 0) {
			_lclose (fh);
			return EC_NOFILE;
		}
		setmode (v_fh, O_TEXT);

	//  VisInfo-Template-Datei schreiben
		if (!OutputResourceTemplate (v_fh, VIS_INFO_TABLE)) {
			_lclose (fh);
			_lclose (v_fh);
                        DEX_Error (RC_CADDYASC, EC_NOVISINFOTEMPLATE);
                        return EC_NOVISINFOTEMPLATE;
		}
		_lclose (v_fh);

		_llseek (fh, 0L, SEEK_SET);		 // Datei-Zeiger auf Anfang
		if ((EC = ExportVersion (fh)) < 0)  // Version u. Bildmasse korr.
			return EC;
	}
	_llseek (fh, 0L, SEEK_END);			 // Datei-Zeiger auf Ende

//  Caddy-Element ausgeben
	OutputParams OP (fh, &GS, 0, MF);
	if ((EC = pCRB -> OuputCaddyRekord (OP, MF)) < 0)
		return EC;

	return (ErrCode) _lclose (fh);
}

// Ende des DatenExports ------------------------------------------------------
ErrCode EXPORTFLT PASCAL CadAscExportEnd (OFSTRUCT &)
{
	DELETE_OBJ (pCRB);				  // ID-Beschr.-Baum löschen

	DELETE_OBJ (pColFileStruct);		// File-Struktur für VisInfo-Tabelle

	DELETE_OBJ (pVisInfoTemplStruct);   // File-Struktur für VisInf-Template löschen

	DELETE_OBJ (pRF);	   

	return EC_OKAY;
}

ErrCode EXPORTFLT PASCAL CadAscExportBreak (OFSTRUCT &of)
{
//  ASCII-File löschen
	remove (of.szPathName);

//  Visualisierungs-Dateien
	remove (pColFileStruct -> szPathName);
	remove (pVisInfoTemplStruct -> szPathName);

	return EC_OKAY;
}

}	   // extern "C"

//--------------------------------------------------------------------------
// lokale Funktionen

// Ausgeben einer Zeile in das CADdy-ASCII-File
ErrCode ExportLine (int fh, const char *pText)
{
   char Buff [3];

// Zeile ausgeben
	if (pText) {
		register short Len = lstrlen (pText);
		if (_lwrite (fh, pText, Len) != (uint) Len)
			return EC_NOSPACE;
	}

// NewLine ausgeben
	lstrcpy (Buff, "\r\n");
	if (_lwrite (fh, Buff, 2) != 2)
		return EC_NOSPACE;

	return EC_OKAY;
}

// Bildmasse ausgeben
ErrCode ExportBildMasse (int fh)
{
	char Buff [DummyKoOrdSize + 1];
	register ErrCode EC;

	_llseek (fh, BildMassePos, SEEK_SET);  // auf BildMasse-Position

//  Abmaße korrigieren
	XMax *= KorrFakt;
	YMax *= KorrFakt;

//  max. Ext.
	if ((EC = ExportLine (fh, DtoA (Buff, pFormatBildMasse, XMax))) < 0)
		return EC;
	if ((EC = ExportLine (fh, DtoA (Buff, pFormatBildMasse, YMax))) < 0)
		return EC;

	_llseek (fh, 0L, SEEK_END);	 // auf Dateiende

	return EC;
}

// Version und Dummy-Bildmasse ausgeben
ErrCode ExportVersion (int fh) {

	register ErrCode EC = EC_OKAY;

//  Version-Rekord ausgeben
	if ((EC = ExportLine (fh, "V")) < 0) {
		_lclose (fh);
		return EC;
	}
	if ((EC = ExportLine (fh, "0")) < 0) {
		_lclose (fh);
		return EC;
	}
	if ((EC = ExportLine (fh, "0")) < 0) {
		_lclose (fh);
		return EC;
	}
	if ((EC = ExportLine (fh, "0")) < 0) {
		_lclose (fh);
		return EC;
	}
	if ((EC = ExportLine (fh, VersionText)) < 0) {
		_lclose (fh);
		return EC;
	}

//  Bilsmaßen-Rekord ausgeben
	if ((EC = ExportLine (fh, "Q")) < 0) {
		_lclose (fh);
		return EC;
	}
	if ((EC = ExportLine (fh, "0")) < 0) {
		_lclose (fh);
		return EC;
	}
	if ((EC = ExportLine (fh, "0")) < 0) {
		_lclose (fh);
		return EC;
	}
	if ((EC = ExportLine (fh, "0")) < 0) {
		_lclose (fh);
		return EC;
	}

//  akt. Datei-Position merken
	BildMassePos = _llseek (fh, 0L, SEEK_CUR);

//  Dummy-Koordinaten ausgeben
	pchar pDummy = new char [DummySize + 1];
        if (!pDummy) {
                DEX_Error (RC_CADDYASC, EC_NOMEMORY);
                return EC_NOMEMORY;
        }
	memset (pDummy, ' ', DummySize);
	pDummy [DummySize] = '\0';
	if ((EC = ExportLine (fh, pDummy)) < 0) {
		return EC;
	}

	DELETE_VEC (pDummy);		// Speicher freigeben

	return EC;
}

// einzelnen Punkt ausgeben
ErrCode ExportPunkt (int fh, double X, double Y)
{
	char Buff [20];
	register ErrCode EC;

//  max. Koordinaten erneut prüfen
	if (XMax < X)
		XMax = X;
	if (YMax < Y)
		YMax = Y;

	if ((EC = ExportLine (fh, DtoA (Buff, pKoordFormat, X))) < 0)
		return EC;

	return ExportLine (fh, DtoA (Buff, pKoordFormat, Y));
}

ErrCode OutputWarnungIdent (short ResourceId, long lIdent) {
	if (!pRF)
	   return EC_SYSERROR;

	Window *pParent = (Window *) SendMessage (__hWndM, __DexCmd,
											  DEXX_MAINWINDOW, 0L);
	if (!pParent)
		return EC_NODEXMESSAGE;

	ResString Caption (ResID (IDS_WARNUNG, pRF), 20);
	ResString TextFormat (ResID (ResourceId, pRF), 80);
	char Buffer [100] = "";
	char tBuffer [30] = "";
	ClassFromIdentX (lIdent, tBuffer, sizeof(tBuffer));
	wsprintf (Buffer, TextFormat.Addr (), tBuffer);
	MessBox MB (Caption.Addr (), Buffer, pParent);
	MB.SetType (OkayButton | ExclamationIcon);
	MB.Show ();
	return EC_OKAY;
}

//  Merkmalskode für Textwert lesen
void _GetTextObjKode (void) {
//  Variablen init.
	char Kode [20] = "";
	GEODBHDRENTRY Entry;
	Entry.dwSize = sizeof (GEODBHDRENTRY);
	Entry.lphdrText = Kode;
	Entry.hdrTextLen = sizeof (Kode);
	short KeySize = sizeof (Entry.hdrKey);
	ResString KeyRes (ResID (IDS_TEXTOBJMKODE, pRF), KeySize);
	lstrcpy (Entry.hdrKey, KeyRes.Addr ());
	short i = lstrlen (Entry.hdrKey);
	for (; i < KeySize; i++)		 // Key mit ' ' auffüllen
		Entry.hdrKey [i] = ' ';

//  Kode von TRIAS lesen
	DEX_ReadGeoDBHdrEntry (Entry);
	if (Kode [0] && atol (Kode))
		StandTextMKode = atol (Kode);
	else
		StandTextMKode = 0L;
}
