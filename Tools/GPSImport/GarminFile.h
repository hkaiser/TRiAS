// GarminFile.h: Schnittstelle für die Klasse CGarminFile.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GARMINFILE_H__956A9CC9_6B95_4ED5_8DF6_6F2FD5097862__INCLUDED_)
#define AFX_GARMINFILE_H__956A9CC9_6B95_4ED5_8DF6_6F2FD5097862__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif
/////////////////////////////////////////////////////////////////////////
#define Header1 "H  SOFTWARE NAME & VERSION"
#define Header2 "I  PCX5 2.09"
#define Header3 "H  R DATUM        IDX  DA            DF             DX          DY"

#define Header4 "M  G WGS 84               121 +0.000000e+00 +0.000000e+00 +0.000000e+00 +0.000000e+00 +0.000000e+00"
//#define Header4 "M  G WGS 84               0   +0.000000e+00 +0.000000e+00 +0.000000e+00 +0.000000e+00 +0.000000e+00"
#define Header5 "H  COORDINATE SYSTEM"
#define Header6 "U  LAT LON DM"

// Nur für TRK
#define Header7 "H  LATITUDE   LONGITUDE   DATE      TIME     ALT    ;track"

//T  N3519.3778 W08540.4498 24-MAR-94 02:00:00 -9999
//char *Koord = "T  N%s E%s %s %s -9999";

// Route
//R  00

//H  IDNT   LATITUDE   LONGITUDE   DATE      TIME     ALT   DESCRIPTION                              PROXIMITY ;waypts
#define RouteHeader "H    IDNT       LATITUDE   LONGITUDE   DATE      TIME     ALT   DESCRIPTION                            PROXIMITY ;waypts"
//W  HOME   N3519.3776 W08540.4503 24-MAR-94 02:00:00 -9999 MY HOUSE                                 1.00000e+03


/////////////////////////////////////////////////////////////////////////
class CGarminFile  
{
public:
	CGarminFile();
	virtual ~CGarminFile();

	bool IsValid() { return m_IsValid; }
	HRESULT Init(const char *, int);
	HRESULT InitGarmin(void);
	void WriteHeader(void);
	void WriteTRKLine(double *,double*);
	void WriteRTELine(double *,double*);
	void WriteRTEHeader(string &ID,string &Name1,string &Name2);
	bool InitFeature(string &ID,string &Name1,string &Name2);
protected:
	void ExportHeader(void);
	bool ExportLine(const char *);
	bool InitTime(void);
private:
	int  m_iType;		// =1 Route, = 0 TRK
	int  m_iCount;		// Routenzähler
	int  m_iLocalCount;	// Koordinatenzähler in Route
	bool m_IsValid;
	FILE *m_infile;
	int  m_fh;			// Für OpenFile - Ausgabedatei
	OFSTRUCT m_ofs;
	char m_FileName[_MAX_PATH];	// Ausgabedateiname
	char m_Description[_MAX_PATH];	// Beschreibung ( Datei)
	char m_IDNT[_MAX_PATH];
	char m_ID[_MAX_PATH];
	char m_Date[20];			// System - Datum
	char m_Time[20];			// + Uhrzeit
};

#endif // !defined(AFX_GARMINFILE_H__956A9CC9_6B95_4ED5_8DF6_6F2FD5097862__INCLUDED_)
