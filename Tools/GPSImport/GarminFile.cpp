// GarminFile.cpp: Implementierung der Klasse CGarminFile.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GarminFile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// Datensatz TRK-File
//T  N3519.3778 W08540.4498 24-MAR-94 02:00:00 -9999
char *Koord = "T  N%s E%s %s %s -9999";

// Route
//R  00
char * dRoute = "R  %.2d";

//H  IDNT   LATITUDE   LONGITUDE   DATE      TIME     ALT   DESCRIPTION                              PROXIMITY ;waypts

//W  HOME   N3519.3776 W08540.4503 24-MAR-94 02:00:00 -9999 MY HOUSE                                 1.00000e+03
//char * dRouteKoord = "W  HOME   N%s E%s %s %s -9999 MY HOUSE                                 1.00000e+03";
char * dRouteKoord = "W  %.3s%.3d     N%s E%s %s %s -9999 %s                                   1.00000e+02";
//char * dRouteKoord0 = "W  R%.2d%.3d     N%s E%s %s %s -9999 %s                                1.00000e+02";
char * dRouteKoord0 = "W  %.3d%.3d     N%s E%s %s %s -9999 %s                                1.00000e+02";


///////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
// Einfügen von Zeichen ab einer bestimmten Position des gegebenen Strings
static LPSTR PASCAL NEAR
StrInsNChr (LPSTR String, char c, int Pos, int n) 
{
	memmove (&String[Pos+n], &String[Pos], strlen (String)-Pos+1);
	memset (&String[Pos], c, n);

return String;
}
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
// Umwandlung eines Double-Wertes entsprechend Format-String 
// in eine Zeichenkette

extern "C" LPSTR PASCAL DtoAFlt (LPSTR String, LPSTR Format, double Wert) 
{
register int Laenge;
register int StrLaenge;
int NachKomma = 0;
int KommaPos;
int Sign;
LPSTR lpA;
LPSTR lpB;

	lpA = Format + strcspn (Format, "0123456789");
	lpB = strchr (Format, '.');
	if (lpB) 
		NachKomma = atoi (lpB+1);
	else {
		lpB = lpA;
		NachKomma = 3;
	}
	if (lpA <= lpB) 
		Laenge = atoi (lpA);
	else
		Laenge = 7;
	strcpy (String, fcvt (Wert, NachKomma, &KommaPos, &Sign));
	if (KommaPos <= 0) {
	    StrInsNChr (String, '0', 0, abs (KommaPos) + 1);
	    StrInsNChr (String, '.', 1, 1);
	}
	else
	    StrInsNChr (String, '.', KommaPos, 1);
	if (*(strchr(Format, '%')+1) == '+') {
		if (!Sign)
			StrInsNChr (String, '+', 0, 1);
	}
	if (Sign)
		StrInsNChr (String, '-', 0, 1);
	if (!strchr (Format, '-') &&	 // wenn keine linksbündige Ausgabe
	    (Laenge > (StrLaenge = strlen(String))))
//		StrInsNChr (String, ' ', 
		StrInsNChr (String, '0', 
			(String[1] == '0' && (*String == '-' || *String == '+')) ?
				1 : 0, Laenge - StrLaenge);
	if (String[Laenge = (strlen(String) -1)] == '.')
		String[Laenge] = '\0';

	return String;
}
////////////////////////////////////////////////////////////////////////////

// Objekttyp aus Geometriefeld des Kopfsatzes berechnen
void GetCoordinates (double *pX, double *pY, LPSTR StringX, LPSTR StringY)
{
		double xRef = *pX;
		double yRef = *pY;

		long lX = (long) (xRef/3600.0);		// Degree
		long lY = (long) (yRef/3600.0);		// Degree

		double xDiff = xRef - ((double) lX * 3600);
		double yDiff = yRef - ((double) lY * 3600);		// RestSec

		xDiff = xDiff/60.0;
		yDiff = yDiff/60.0;		// Minute

		xDiff = xDiff + ((double) lX * 100.0);
		yDiff = yDiff + ((double) lY * 100.0);


		char *dFormatY = "%9.4f";
		char *dFormatX = "%10.4f";

		DtoAFlt (StringX, dFormatX, xDiff);

		DtoAFlt (StringY, dFormatY, yDiff);

}


//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CGarminFile::CGarminFile()
{

	m_IsValid = InitTime();	// Datum/Zeit

	m_iCount = 0;		// Routenzähler
	m_iLocalCount = 0;	// Koordinatenzähler in Route
	m_iType = 1;		// Route (rte)
	
	m_FileName[0] = '\0';	// Ausgabedateiname
	m_Description[0] = '\0';	// Beschreibung ( Datei)
	m_IDNT[0] = '\0';
	m_ID[0] = '\0';


}

CGarminFile::~CGarminFile(void)
{
	if ( m_IsValid){
		if (m_fh)
			_lclose (m_fh);
	}
}

HRESULT CGarminFile :: Init (const char *pFileName, int iType) 
{


	m_iType = iType;

	if (m_IsValid) {

		if ( !pFileName || *pFileName == '\0') {
			m_IsValid = false;
			return S_FALSE;
		} else {
			strcpy(m_FileName,pFileName);
		}
		return InitGarmin();
	}

	return S_FALSE;

}

HRESULT CGarminFile :: InitGarmin(void)
{
// Datei anlegen
	if ( m_IsValid) {
		if ((m_fh = OpenFile (m_FileName, &m_ofs,OF_CREATE  + OF_WRITE)) < 0) {
		// Fehler: kann Datei nicht eröffnen
			m_IsValid = false;
			return S_FALSE;

		} else {
			WriteHeader();
			m_iCount = 0;
			return S_OK;
		}
	}
	return S_FALSE;

}

bool CGarminFile :: InitTime(void)
{
	char dFormatTime[] = "%.2d:%.2d:%.2d";
	char dFormatDate[] = "%.2d-%s-%.2d";
	// Datum
	char Month[12][4] = {"JAN","FEB","MAR","APR","MAY","JUN","JUL","AUG","SEP","OCT","NOV","DEC"};

    SYSTEMTIME st;

    GetSystemTime(&st);       // gets current time

	wsprintf ( m_Date, dFormatDate, st.wDay,Month[st.wMonth-1],st.wYear-2000);
	wsprintf ( m_Time, dFormatTime, st.wHour,st.wMinute,st.wSecond);

	return true;

}

bool CGarminFile :: InitFeature (string &ID,string &Name1,string &Name2)
{

	if (m_IsValid ) {
		m_ID[0] = '\0';
		m_IDNT[0] = '\0';
		m_Description[0] = '\0';

		strcpy (m_ID, ID.c_str());
		strcpy (m_IDNT, Name1.c_str());
		strcpy (m_Description, Name2.c_str());
		return true;
	} else
		return false;

}


void CGarminFile :: WriteHeader(void)
{
// Header in Datei ausgeben
	if ( m_IsValid) {

		ExportHeader();
	}

}
void CGarminFile :: WriteTRKLine( double *pX, double *pY)
{
// Record in Datei ausgeben
//T  N3519.3778 W08540.4498 24-MAR-94 02:00:00 -9999

static char outBuff[1024];

	if ( m_IsValid) {

		char Buff1[20];
		char Buff2[20];

		GetCoordinates(pX,pY,Buff1,Buff2);

		wsprintf (outBuff, Koord, Buff2,Buff1,m_Date,m_Time);


		ExportLine(outBuff);

	}

}
void CGarminFile :: WriteRTEHeader( string &ID,string &Name1,string &Name2)
{
// Record in Datei ausgeben


static char outBuff[1024];

	m_IsValid = InitTime();	// System-Datum/Zeit für jede Route aktuell

	m_IsValid = InitFeature( ID,Name1,Name2);	

	if ( m_IsValid) {

		wsprintf (outBuff, dRoute,m_iCount);
		ExportLine(outBuff);

		m_iCount++;

		ExportLine (RouteHeader); 
		m_iLocalCount = 0;
	}

}

void CGarminFile :: WriteRTELine( double *pX, double *pY)
{
// Record in Datei ausgeben

static char outBuff[1024];

	if ( m_IsValid) {

		char Buff1[20];
		char Buff2[20];

		GetCoordinates(pX,pY,Buff1,Buff2);

		m_iLocalCount++;

		if ( m_IDNT[0] == '\0')

			wsprintf (outBuff, dRouteKoord0,m_iCount-1,m_iLocalCount, Buff2,Buff1,m_Date,m_Time,m_Description);	// Lat/Lon - DM = Degree - decimal minute
		else
			wsprintf (outBuff, dRouteKoord,&m_IDNT,m_iLocalCount, Buff2,Buff1,m_Date,m_Time,m_Description);	// Lat/Lon - DM = Degree - decimal minute


		ExportLine(outBuff);


	}

}

bool CGarminFile :: ExportLine ( const char *pLine) 
{
// Ausgabe der Zeile
	if (pLine != NULL) {

		UINT iLen = strlen (pLine);

		if (_lwrite (m_fh, (char *)pLine, iLen) != iLen)
			return false;
	} 

// NewLine ausgeben
	char *cptr = "\r\n";		// CR,LF

	if (_lwrite (m_fh, cptr, 2) != 2)
		return false;            

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////
void CGarminFile :: ExportHeader ( void)
{

		ExportLine (Header1); 
		ExportLine (Header2); 
		ExportLine (Header3); 
		ExportLine (Header4); 
		ExportLine (Header5); 
		ExportLine (Header6); 
		if (!m_iType)
			ExportLine (Header7);	// Header für TRK-File

}

///////////////////////////////////////////////////////////////////////////////////////////////////