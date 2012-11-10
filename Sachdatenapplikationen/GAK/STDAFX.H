// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#ifndef _STDAFX_H
#define _STDAFX_H

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#define DELETE_VEC(x)   {if(x){delete [] (x); (x)=NULL;}}
#define DELETE_OBJ(x)   {if(x){delete (x); (x)=NULL;}} 

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdao.h>			// MFC DAO database classes
// BGSAbgl
#include <AFXDB.H>			// MFC ODBC-classes
#include <afxcoll.h>		// CMapStringToOb
// BGSAbgl
#include <afxtempl.h>		// Template-Unterstützung
#include <afxmt.h>			// CMutex u.a.	
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows 95 Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT
#include "waitcext.h"		// CWaitCursorExt
#include "daotools.h"		// Fehlerbehandlung u.a.

//	Hilfe-Konstanten
#define HelpCommandOffset		0x10000
#define HelpDialogOffset        0x20000
#define HelpPromptOffset		0x30000
#define HelpFrameOffset         0x50000

//	globale Prototypen
void CallMessageQueue (void);	// Nachrichtenwarte-Schlange abarbeiten
char *DtoA (double Wert, char *String, const char *Format = NULL /* %.5lf" */); // double to ascii
char *AnsiStringNew (LPCWSTR strIn);				// wide string to ansii

//	lese Parameterwert einer Abfrage in einen CString
void GetQueryParamValue (const CDaoParameterInfo &Info, CString &strValue);

//	schreibe Parameterwert (CString) in Parameterinfo
BOOL WriteQueryParamValue (CDaoParameterInfo &Info, const CString &strValue);

//	MDB-Konstanten
const short MaxTableNameLen = 64;		// max. 64 Zeichen pro Tabelle
const short MaxQueryDefNameLen = 64;	// max. 64 Zeichen für Namen einer Abfrage

//	globale Konstanten zum Drucken
const short HeaderSpace = 25;				// 1/4 Zoll
const short HeaderLineSpace = 35;			// 1/10 Zoll unterhalb des Textes
const char NeueZeile = '\n';				// Formular-Steuer-Zeichen
const char ZeileUnterStreichen = '\r';

//	globale Konstanten für Arbeit mit der Datenbank
const short BranchenNummerLaenge = 7;
const short AbfallArtNummerLaenge = 5;
const short GemeindekennzahlLaenge = 7; 
const short KreiskennzahlLaenge = 5;
const short KurzNummerLaenge = 5;
// const short HausNrLaenge = KurzNummerLaenge;
const short HausNrLaenge = 10;
const short PlzLaenge = KurzNummerLaenge;

const short NummerLaenge = 10;
const short ErzNummerLaenge = 9;
const short BilanzNummerLaenge = 12;
const short GkzLaenge = NummerLaenge;
const short BrNummerLaenge = NummerLaenge;

const short TelNummerLaenge = 20;
const short TelefonLaenge = TelNummerLaenge;
const short TelefaxLaenge = TelNummerLaenge;

const short UserNameLen = 20;

const short PartnerNamenLaenge = 30;

const short OrtsNamenLaenge = 50;

const short NamenLaenge = 80;
const short FirmenLaenge = NamenLaenge;
const short StrassenLaenge = NamenLaenge;
const short EntsorgungsArtLaenge = NamenLaenge;
const short AnfallLaenge = NamenLaenge;
const short BetriebLaenge = NamenLaenge;
const short BrNameLaenge = 140;
const char BilanzKennung [] = "B_";

#define IDM_RB_DOWN                     WM_USER+1

//	Typdefinitionen
//	Tabellenindex
typedef struct 
{
	char *pIndexName;					// Name des Index
	BOOL bDisAllowNull;					// Erlaubt keine NULL-Eintrag
} IndexFieldInfo;

//	QueryParameter
typedef enum { NoPage = 0, ErzeugerPage = 1, BranchenPage = 2, GebietsPage = 4,
			   AbfallPage = 8, ErgebnisPage = 16 } PageType;

typedef struct 
{
	char *pName;	
	int iValType;
	PageType tpPage;
 } QueryParameter;


// macros
#include "macros.h"

// BGSAbgl
//	globale Funktionen               
void OutputInfo (const CString strInfo);           
void OutputError (const CString &strError);
void OutputMemoryError ();
void OutputFileError (int iCause);
char *ChangeUmlaute (const char *pText);

extern "C" {
char *OutputResourceTemplate (UINT uiResID) ;
}

//	Konstanten                            
const long lBilanzMenge = 5;			// voreingestellte Bilanzierungsmenge                            
const short sMaxErzNrLen = 10;
const short sMinErzNrLen = 9;   
const short sMaxEntsorgerLen = 10;
const short sMaxTranspLen = 10;
const short sMaxAsnNrLen = 10;
const short sMaxEnSnLen = 20;
const short sMaxVerfahrenLen = 3;
const short sMaxPrioLen = 1;
const int iColumnsCount = 10;			//	Spaltenanzahl für ListBoxen
#define szMengenFormat "%.2lf"

#define IDM_RB_DOWN			WM_USER+1
           
//	Struktur zum überprüfen der Tabellenfelder           
typedef struct 
{
	char *pFieldName;					// Name des Feldes
	short sType;						// FeldTyp --> dbText ...
	short sLen;							// -1: keine Angabe	
} FieldInfo;	
typedef FieldInfo * pFieldInfo;

BOOL TableOK (CDatabase *pDatabase, const CString &strTable, FieldInfo *pInfo, UINT uiErrorString, 
			  BOOL bOutputError = TRUE);
// BGSAbgl

typedef UINT uint;		  // needed for odbci.h

#endif			// _STDAFX_H





