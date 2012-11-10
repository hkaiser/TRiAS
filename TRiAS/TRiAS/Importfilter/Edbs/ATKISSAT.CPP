//	Datei:	AtkisSat.cpp
//	Stand:	30.08.1995
//	Autor:	Denkewitz
//	(c) 1995 uve GmbH FEZ Potsdam

#include "stdafx.h"
#include "koorpaar.h"
#include "atkissat.h"
#include "linie.h"

extern void		Kommentar( const char*, const int );
extern void		Kommentar( int, const int );
extern void		Kommentar( long, const int );
extern void		Kommentar( double, const int );
extern void		Meldung( const char* );
extern void		Meldung( int );
extern void		Meldung( long );
extern void		KommNL( const char*, const int );
extern void		KommNL( int, const int );
extern void		KommNL( long, const int );
extern void		KommNL( double, const int );
extern void		MeldNL( const char* );
extern void		MeldNL( int );
extern void		MeldNL( long );
extern void		MeldNL( double );

extern int		AllTrimm( CString& );

CAtkisSatz :: CAtkisSatz()
{
	m_bGueltig = FALSE;
	m_bObjektDaten = FALSE;
	m_fIsFloeDelta = FALSE;
	m_strBuffer.Empty();
}	// Konstruktion

CAtkisSatz :: ~CAtkisSatz()
{
	short	i, n = m_Linien.GetSize();

	for ( i = 0; i < n; i++ )
		delete (CLinie*)m_Linien[i];
	m_Linien.RemoveAll();

	n = m_Objekte.GetSize();
	for ( i = 0; i < n; i++ )
		delete (CObjekt*)m_Objekte[i];
	m_Objekte.RemoveAll();

	n = m_Infos.GetSize();
	for ( i = 0; i < n; i++ )
		delete (CInfo*)m_Infos[i];
	m_Infos.RemoveAll();
}	// Destruktion

void CAtkisSatz :: Lesen( const char *txt )
{	short	i, n;
	CString		satz = txt;
	CString		teil;

	// Initialisierung der Variablen
	n = m_Linien.GetSize();
	for ( i = 0; i < n; i++ )
		delete (CLinie*)m_Linien[i];
	m_Linien.RemoveAll();

	n = m_Objekte.GetSize();
	for ( i = 0; i < n; i++ )
		delete (CObjekt*)m_Objekte[i];
	m_Objekte.RemoveAll();

	n = m_Infos.GetSize();
	for ( i = 0; i < n; i++ )
		delete (CInfo*)m_Infos[i];
	m_Infos.RemoveAll();

	m_bObjektDaten = FALSE;
	m_bAttrSatz = FALSE;
	m_bGueltig = FALSE;

	// Gueltigkeit testen
	if ( satz.IsEmpty() || ( satz.GetLength() < 4 ))
		return;

	// Anfangskennung
	teil = satz.Left( 4 );

	if ( teil == "FEIN" )		m_eStart = FEIN;
	else if ( teil == "BSPE" )	m_eStart = BSPE;
	else if ( teil == "AKND" )	m_eStart = AKND;
	else if ( teil == "AEND" )	m_eStart = AEND;
	else if ( teil == "BKRT" )	m_eStart = BKRT;
	else if ( teil == "BINF" )	m_eStart = BINF;
	else if ( teil == "FAEN" )	m_eStart = FAEN;
	else if ( teil == "FLOE" )	m_eStart = FLOE;
	else if ( teil == "FALG" )	m_eStart = FALG;

	// Kennung + sechsstellige Satznummer ignorieren
	satz = satz.Mid( 10 );
	if ( satz[0] == ' ' )			m_bKomplett = TRUE;
	else if ( satz[0] == 'E' )		m_bKomplett = TRUE;
	else							m_bKomplett = FALSE;

	// Fortsetzungskennung ausgewertet
	satz = satz.Mid( 2 );

	// Int4 wegschlucken
	satz = satz.Mid( 4 );
	teil = satz.Left( 8 );
	satz = satz.Mid( 8 );

	// Satztyp
	if      ( teil == "ULOBNN  " )	m_eTyp = ULOBNN;
	else if ( teil == "ULTANN  " )	m_eTyp = ULTANN;
	else if ( teil == "ULQA0000" )	m_eTyp = ULQA0000;
	else if ( teil == "IBENKRT " )	m_eTyp = IBENKRT;
	else if ( teil == "ULOTEX  " )	m_eTyp = ULOTEX;
	else if ( teil == "ULBENFOL" )	m_eTyp = ULBENFOL;
	else if ( teil == "ULBENGEO" )	m_eTyp = ULBENGEO;
	else if ( teil == "ULBENOBJ" )	m_eTyp = ULBENOBJ;
	else if ( teil == "ULPUNN  " )	m_eTyp = ULPUNN;
	else if ( teil.Left(3) == "ULO" )	m_eTyp = ULOALK;

	m_strBuffer += satz;

	if ( Komplett()) {
		switch (Start()) {
		case AKND:	
			AnfangsSatz( m_strBuffer );
			break;
		
		case AEND:	
			EndeSatz( m_strBuffer );
			break;
		
		case FEIN:
		case BSPE:	
			DatenSatz( m_strBuffer );
			break;

		case FLOE:			// 011112
			LoeschSatz (m_strBuffer);
			break;
		}
		m_strBuffer.Empty();
	}
}

void CAtkisSatz :: AnfangsSatz( const char* )
{
}	// AnfangsSatz

void CAtkisSatz :: EndeSatz( const char* )
{
}	// EndeSatz

void CAtkisSatz :: DatenSatz( const char *daten )
{
	switch ( Typ())
	{	case ULOBNN:	ObjektDaten( daten );
						break;
		case ULOALK:	ALK_Daten( daten );
						break;
		case ULTANN:	AttributSatz( daten );
						break;
		case ULQA0000:	AuftragsKennSatz( daten );
						break;
		case ULPUNN:	ALK_Punktdaten( daten );
						break;
	}
}	// DatenSatz

void CAtkisSatz :: AuftragsKennSatz( const char* )
{
}	// AuftragsKennSatz

// Löschsatz (Update)
#if defined(_DEBUG)
typedef struct tagDELINFO {
	INT_PTR m_lMCode;
	LPCSTR m_pcObjNr;
	size_t m_ulLen;
} DELINFO;
#endif // defined(_DEBUG)

extern "C"
BOOL CALLBACK DeleteUpdatedObject (long lONr, BOOL, void *pData)
{
#if defined(_DEBUG)
DELINFO *pDI = reinterpret_cast<DELINFO *>(pData);
TARGETMERKMAL TM;
char cbBuffer[_MAX_PATH];

	INITSTRUCT(TM, TARGETMERKMAL);
	TM.iTTyp = TT_Objekt;
	TM.lTarget = lONr;
	TM.lMCode = pDI -> m_lMCode;
	TM.pMText = cbBuffer;
	TM.imaxLen = sizeof(cbBuffer);
	if (NULL != DEX_GetTextMerkmal(TM)) {
		_ASSERTE(!strncmp (pDI -> m_pcObjNr, cbBuffer, pDI -> m_ulLen));
	}
#endif // defined(_DEBUG)
	DEX_DeleteObject(lONr);		// Objekt einfach so löschen
	return TRUE;				// immer weiter machen
}

extern "C"
BOOL CALLBACK DeleteUpdatedAttribute (long lMCode, DWORD, void *pData)
{
TARGETMERKMAL TM;

	INITSTRUCT(TM, TARGETMERKMAL);
	TM.lTarget = reinterpret_cast<HOBJECT>(pData);
	TM.iTTyp = TT_Objekt;
	TM.lMCode = lMCode;
	DEX_ModTextMerkmal(TM);		// Attribut löschen
	return TRUE;
}

extern "C"
BOOL CALLBACK DeleteUpdatedObjectAttributes (long lONr, BOOL, void *pData)
{
#if defined(_DEBUG)
DELINFO *pDI = reinterpret_cast<DELINFO *>(pData);
TARGETMERKMAL TM;
char cbBuffer[_MAX_PATH];

	INITSTRUCT(TM, TARGETMERKMAL);
	TM.iTTyp = TT_Objekt;
	TM.lTarget = lONr;
	TM.lMCode = pDI -> m_lMCode;
	TM.pMText = cbBuffer;
	TM.imaxLen = sizeof(cbBuffer);
	if (NULL != DEX_GetTextMerkmal(TM)) {
		_ASSERTE(!strncmp (pDI -> m_pcObjNr, cbBuffer, pDI -> m_ulLen));
	}
#endif // defined(_DEBUG)

// jetzt alle Attribute löschen
ENUMLONGKEYEX ELK;

	ELK.eKey = lONr;
	ELK.eFcn = (ENUMLONGKEYEXPROC)DeleteUpdatedAttribute;
	ELK.ePtr = reinterpret_cast<void *>(lONr);
	ELK.eData = MPObjectFeature|MPSystemFeatures|MPReadOnlyFeatures;	// alles löschen
	DEX_EnumObjektMerkmaleEx(ELK);
	return TRUE;						// immer weiter machen
}

void CAtkisSatz::LoeschSatz(LPCSTR pcDaten)
{
// Objektnummer des zu löschenden Objektes herausfischen
CString strBuffer(pcDaten);
CString strObjektnummer, strAktualitaet;
int pos = strBuffer.Find("DLOB2005EQ");

	if (pos >= 0) {
	// DLOB2005
		strObjektnummer = strBuffer.Mid(pos + 10, 7);
		pos = strBuffer.Find("DLOB2003EQ");
		if (pos >= 0)
			strAktualitaet = strBuffer.Mid(pos + 10, 2);
	}

	if (pos < 0) {
	// evtl. DLTA1001
		pos = strBuffer.Find("DLTA0001EQ");
		if (pos >= 0)
			strObjektnummer = strBuffer.Mid(pos + 10, 7);

		strcpy (m_AttrObjNr, strObjektnummer);
		m_AttrObjNr[7] = '\0';

		pos = strBuffer.Find("DLTA0004EQ");
		if (pos >= 0)
			strAktualitaet = strBuffer.Mid(pos + 10, 2);

		pos = strBuffer.Find("DLTA0002EQ");
		m_AttrOTNr[0] = '\0';
		if (pos >= 0) {
		CString strTeilNr = strBuffer.Mid(pos + 10, 3);

			AllTrimm (strTeilNr);	// ggf. ist TeilNr leer
			strcat (m_AttrOTNr, strTeilNr);
		}

		m_fIsFloeDelta = TRUE;

	// hier alle Attribute dieses Objektes löschen
	INT_PTR lMCode = DEX_GetMCodeFromFeatureNameCIEx(DEX_GetDataSourceHandle(), "ATKIS-Objektnummer");

		_ASSERTE(0 != lMCode);
		if (0 != lMCode) {
#if defined(_DEBUG)
		DELINFO DI;

			DI.m_lMCode = lMCode;
			DI.m_pcObjNr = strObjektnummer;
			DI.m_ulLen = strObjektnummer.GetLength();
#endif // defined(_DEBUG)

		ENUMRECHTEXTMERKMAL ERTM;

			INITSTRUCT(ERTM, ENUMRECHTEXTMERKMAL);
			ERTM.pView = NULL;
			ERTM.lMCode = lMCode;
			ERTM.pMWert = (LPSTR)(LPCSTR)strObjektnummer;
			ERTM.iMode = SMSubStringStartMatch;
			ERTM.eFcn = DeleteUpdatedObjectAttributes;
#if defined(_DEBUG)
			ERTM.pData = &DI;
#endif // defined(_DEBUG)
			DEX_EnumRechTextMerkmal(ERTM);
		}
		return;
	}

	if (pos < 0) 
		return;		// nichts für uns

// dieses Objekt in TRiAS löschen
INT_PTR lMCode = DEX_GetMCodeFromFeatureNameCIEx(DEX_GetDataSourceHandle(), "ATKIS-Objektnummer");

	_ASSERTE(0 != lMCode);
	if (0 != lMCode) {
		_ASSERTE(strObjektnummer.GetLength() > 0);

#if defined(_DEBUG)
	DELINFO DI;

		DI.m_lMCode = lMCode;
		DI.m_pcObjNr = strObjektnummer;
		DI.m_ulLen = strObjektnummer.GetLength();
#endif // defined(_DEBUG)

	ENUMRECHTEXTMERKMAL ERTM;

		INITSTRUCT(ERTM, ENUMRECHTEXTMERKMAL);
		ERTM.pView = NULL;
		ERTM.lMCode = lMCode;
		ERTM.pMWert = (LPSTR)(LPCSTR)strObjektnummer;
		ERTM.iMode = SMSubStringStartMatch;
		ERTM.eFcn = DeleteUpdatedObject;
#if defined(_DEBUG)
		ERTM.pData = &DI;
#endif // defined(_DEBUG)
		DEX_EnumRechTextMerkmal(ERTM);
	} 
}

void CAtkisSatz :: AttributSatz( const char *daten )
{
	CString		teil, buffer = daten;
	const char	*pos = daten;
	short		i;

	// Int4 + Int4 wegschlucken!
	pos += 8;
	buffer = buffer.Mid( 8 );

	for ( i = 0; i < 7; m_AttrObjNr[i++] = *pos++ );
		m_AttrObjNr[7] = '\0';
	for ( i = 0; i < 3; m_AttrOTNr[i++] = *pos++ );
		m_AttrOTNr[3] = '\0';
	for ( i = 0; i < 3; m_AttrPruef[i++] = *pos++ );
		m_AttrPruef[3] = '\0';

	buffer = buffer.Mid( 13 );
	teil = buffer.Left( 4 ); buffer = buffer.Mid( 4 );

	m_Attribute.Empty();

	m_AttrAnzahl = i = atoi( teil );
	if ( buffer.GetLength() < i * 11 )
		return;

	if (0 != i) {	
		m_Attribute = buffer.Left( i * 11 );
		buffer = buffer.Mid( i * 11 );
	}

	m_bAttrSatz = TRUE;
	m_bGueltig = TRUE;
}	// AttributSatz

void CAtkisSatz :: ObjektDaten( const char *daten )
{
	CString		buffer = daten;
	CString		temp;
	short		i, j, n;
	CKoordPaar	k;
	CString		art;
	CLinie		*L;
	CObjekt		*O;
	CInfo		*I;

	// Int4 + Int4 überlesen
	buffer = buffer.Mid( 8 );

	GrundrissKennDaten( buffer );

	// StartKoord + Prüfzeichen gelesen
	buffer = buffer.Mid( 21 );
	
	// Linienzahl prüfen
	temp = buffer.Left( 4 );
	buffer = buffer.Mid( 4 );

	n = atoi( temp );
	for ( i = 0; i < n; i++ )
	{	
		temp = buffer.Left( 4 );
		buffer = buffer.Mid( 4 );
		if ( atoi( temp ) != 1 )
		{	m_bGueltig = FALSE;
			Kommentar( "Syntaxfehler: Erwartet 0001, gefunden ", 3 );
			KommNL( temp, 3 );
			return;
		}

		L = new CLinie;
		if ( !L )
		{	
			m_bGueltig = FALSE;
			KommNL( "Nicht genug Speicher!", 3 );
			return;
		}

CString		strLinieInfo( buffer );
		j = L -> Lesen( buffer );
		if ( j )
			buffer = buffer.Mid( j );

		if ( L -> Gueltig())	m_Linien.Add( L );
		else
		{
			KommNL( "Ungültige Linie! (ATKIS-Daten)", 3 );
KommNL( strLinieInfo, 3 );
			delete L;
	}	}

	// Objektzahl prüfen
	temp = buffer.Left( 4 );
	buffer = buffer.Mid( 4 );

	n = atoi( temp );
	if ( n )
	{	for ( i = 0; i < n; i++ )
		{	temp = buffer.Left( 4 );
			buffer = buffer.Mid( 4 );
			if ( atoi( temp ) != 1 )
			{	m_bGueltig = FALSE;
				Kommentar( "Syntaxfehler: Erwartet 0001, gefunden ", 3 );
				KommNL( temp, 3 );
				return;
			}

			O = new CObjekt;
			if ( !O )
			{	m_bGueltig = FALSE;
				KommNL( "Nicht genug Speicher!", 3 );
				return;
			}

			j = O -> Lesen( buffer );
			if ( j )
				buffer = buffer.Mid( j );

			if ( O -> Gueltig())	m_Objekte.Add( O );
			else
			{
				KommNL( "Ungültiges Objekt!", 3 );
				delete O;
		}	}

	// Besondere Infos prüfen
		temp = buffer.Left( 4 );
		buffer = buffer.Mid( 4 );

		n = atoi( temp );
		for ( i = 0; i < n; i++ )
		{	temp = buffer.Left( 4 );
			buffer = buffer.Mid( 4 );
			if ( atoi( temp ) != 1 )
			{	m_bGueltig = FALSE;
				Kommentar( "Syntaxfehler: Erwartet 0001, gefunden ", 3 );
				KommNL( temp, 3 );
				return;
			}

			I = new CInfo;
			if ( !I )
			{	m_bGueltig = FALSE;
				KommNL( "Nicht genug Speicher!", 3 );
				return;
			}

			j = I -> Lesen( buffer );
			if ( j )
				buffer = buffer.Mid( j );

			if ( I -> Gueltig())	m_Infos.Add( I );
			else
			{
				KommNL( "Ungültige Information!", 3 );
				delete I;
	}	}	}

	m_bObjektDaten = TRUE;
}	// ObjektDaten

void CAtkisSatz :: ALK_Daten( const char *daten )
{
	CString		buffer = daten;
	CString		temp;
	short		i, j, n;
	CKoordPaar	k;
	CString		art;
	CLinie		*L;
	CObjekt		*O;
	CInfo		*I;

	// Int4 + Int4 überlesen
	buffer = buffer.Mid( 8 );

	GrundrissKennDaten( buffer );

	// StartKoord + Prüfzeichen gelesen
	buffer = buffer.Mid( 21 );
	
	// Linienzahl prüfen
	temp = buffer.Left( 4 );
	buffer = buffer.Mid( 4 );

	n = atoi( temp );
	for ( i = 0; i < n; i++ )
	{	temp = buffer.Left( 4 );
		buffer = buffer.Mid( 4 );
		if ( atoi( temp ) != 1 )
		{	m_bGueltig = FALSE;
			Kommentar( "Syntaxfehler: Erwartet 0001, gefunden ", 3 );
			KommNL( temp, 3 );
			return;
		}

		L = new CLinie;
		if ( !L )
		{	m_bGueltig = FALSE;
			KommNL( "Nicht genug Speicher!", 3 );
			return;
		}

CString		strLinieInfo( buffer );
		j = L -> LesenALK( buffer );
		if ( j )
			buffer = buffer.Mid( j );

/*// Herausfiltern Linienteilung == 0
if ( L -> FktZahl())
{	CString		sollteilung, space;
	sollteilung = "0";
	space = " ";

	if ( L -> Funktion(0))
		if (( L -> Funktion(0) -> LinienTeilung1() != sollteilung ) &&
			( L -> Funktion(0) -> LinienTeilung1() != space ))
				L -> Gueltig() = FALSE;
	if ( L -> Funktion(0))
		if (( L -> Funktion(0) -> LinienTeilung2() != sollteilung ) &&
			( L -> Funktion(0) -> LinienTeilung2() != space ))
				L -> Gueltig() = FALSE;
}
*/

		if ( L -> Gueltig())	m_Linien.Add( L );
		else
		{
			KommNL( "Ungültige Linie! (ALK-Daten)", 3 );
KommNL( "Dump1:", 3);
KommNL( daten, 3 );
KommNL( "Dump2:", 3);
KommNL( strLinieInfo, 3 );
			delete L;
	}	}

	// Objektzahl prüfen
	temp = buffer.Left( 4 );
	buffer = buffer.Mid( 4 );

	n = atoi( temp );
	if ( n )
	{	for ( i = 0; i < n; i++ )
		{	temp = buffer.Left( 4 );
			buffer = buffer.Mid( 4 );
			if ( atoi( temp ) != 1 )
			{	m_bGueltig = FALSE;
				Kommentar( "Syntaxfehler: Erwartet 0001, gefunden ", 3 );
				KommNL( temp, 3 );
				return;
			}

			O = new CObjekt;
			if ( !O )
			{	m_bGueltig = FALSE;
				KommNL( "Nicht genug Speicher!", 3 );
				return;
			}

			j = O -> LesenALK( buffer );
			if ( j )
				buffer = buffer.Mid( j );

			if ( O -> Gueltig())	m_Objekte.Add( O );
			else
			{
				KommNL( "Ungültiges Objekt!", 3 );
				delete O;
		}	}

	// Besondere Infos prüfen
		temp = buffer.Left( 4 );
		buffer = buffer.Mid( 4 );

		n = atoi( temp );
		for ( i = 0; i < n; i++ )
		{	temp = buffer.Left( 4 );
			buffer = buffer.Mid( 4 );
			if ( atoi( temp ) != 1 )
			{	m_bGueltig = FALSE;
				Kommentar( "Syntaxfehler: Erwartet 0001, gefunden ", 3 );
				KommNL( temp, 3 );
				return;
			}

			I = new CInfo;
			if ( !I )
			{	m_bGueltig = FALSE;
				KommNL( "Nicht genug Speicher!", 3 );
				return;
			}

			j = I -> LesenALK( buffer );
			if ( j )
				buffer = buffer.Mid( j );

			if ( I -> Gueltig())	m_Infos.Add( I );
			else
			{
				KommNL( "Ungültige Info!", 3 );
				delete I;
	}	}	}

	m_bObjektDaten = TRUE;
}	// ALK_Daten

void CAtkisSatz::ALK_Punktdaten( const char* daten )
{
	CString		buffer = daten;
	CString		temp;
	short		n, i;

	// Int4 + Int4 überlesen
	buffer = buffer.Mid( 8 );

//	Punktverwaltungsdatengruppe!!!
	temp = buffer.Left( 8 );
	buffer = buffer.Mid( 8 );
KommNL( "ALK_Punktdaten:", 3 );
Kommentar( "Nummerierungsbezirk: ", 3 );
KommNL( temp, 3 );
	temp = buffer.Left( 6 );
	buffer = buffer.Mid( 6 );

Kommentar( "Punktart: ", 3 );
KommNL( temp.Left( 1 ), 3 );
Kommentar( "Punktnummer: ", 3 );
KommNL( temp.Mid( 1 ), 3 );
	temp = buffer.Left( 2 );
	buffer = buffer.Mid( 2 );

Kommentar( "Prüfzeichen: ", 3 );
KommNL( temp.Left( 1 ), 3 );
Kommentar( "Punktstatus: ", 3 );
KommNL( temp.Right( 1 ), 3 );
	temp = buffer.Left( 7 );
	buffer = buffer.Mid( 7 );

Kommentar( "Zuständige Stelle: ", 3 );
KommNL( temp, 3 );
	temp = buffer.Left( 4 );
	buffer = buffer.Mid( 4 );

Kommentar( "Aktualität/spezielle Aktualität: ", 3 );
KommNL( temp, 3 );
	temp = buffer.Left( 7 );
	buffer = buffer.Mid( 7 );

Kommentar( "Vermarkungsart, Bemerk.: ", 3 );
KommNL( temp, 3 );
	temp = buffer.Left( 15 );
	buffer = buffer.Mid( 15 );

Kommentar( "Entstehung: ", 3 );
KommNL( temp, 3 );
	temp = buffer.Left( 15 );
	buffer = buffer.Mid( 15 );

Kommentar( "Untergang: ", 3 );
KommNL( temp, 3 );
	temp = buffer.Left( 1 );
	buffer = buffer.Mid( 1 );

Kommentar( "Kennung für Bemerkungen: ", 3 );
KommNL( temp, 3 );

//	Lagedatengruppen
	temp = buffer.Left( 4 );	// Endekennung "0000"
	buffer = buffer.Mid( 4 );
	temp = buffer.Left( 4 );	// Anzahl Lagedatengruppen
	buffer = buffer.Mid( 4 );
	n = atoi( temp );
Kommentar( "Anzahl Lagedatengruppen: ", 3 );
KommNL( n, 3 );
	for ( i = 0; i < n; i++ )
	{
		temp = buffer.Left( 3 );
		buffer = buffer.Mid( 3 );
Kommentar( "Lagestatus: ", 3 );
Kommentar( temp, 3 );
		if ( temp == "489" )
			KommNL( "  (amtl. Bezugssystem der Lage ETRS89)", 3 );
		else if ( temp == "150" )
			KommNL( "  (Bezugssystem der Lage 42/83)", 3 );
		else
			KommNL( "  (unbekanntes Bezugssystem)", 3 );
		temp = buffer.Left( 10 );
		buffer = buffer.Mid( 10 );
Kommentar( "Rechtswert: ", 3 );
KommNL( temp, 3 );
		temp = buffer.Left( 10 );
		buffer = buffer.Mid( 10 );
Kommentar( "Hochwert: ", 3 );
KommNL( temp, 3 );
		temp = buffer.Left( 9 );
		buffer = buffer.Mid( 9 );
Kommentar( "Art der Lagegenauigkeit: ", 3 );
KommNL( temp.Left( 1 ), 3 );
Kommentar( "Wert der Lagegenauigkeit: ", 3 );
KommNL( temp.Mid( 1 ), 3 );
		temp = buffer.Left( 1 );
		buffer = buffer.Mid( 1 );
Kommentar( "Lagezuverlässigkeit: ", 3 );
KommNL( temp, 3 );
		temp = buffer.Left( 3 );
		buffer = buffer.Mid( 3 );
Kommentar( "Jahr der Berechnung: 1", 3 );
KommNL( temp, 3 );
		temp = buffer.Left( 9 );
		buffer = buffer.Mid( 9 );
Kommentar( "Aktenhinweis: ", 3 );
KommNL( temp, 3 );
	}

	temp = buffer.Left( 4 );	// Anzahl Höhendatengruppen
	buffer = buffer.Mid( 4 );
	n = atoi( temp );
Kommentar( "Anzahl Höhendatengruppen: ", 3 );
KommNL( n, 3 );
	for ( i = 0; i < n; i++ )
	{
		temp = buffer.Left( 3 );
		buffer = buffer.Mid( 3 );
Kommentar( "Höhenstatus: ", 3 );
KommNL( temp, 3 );
		temp = buffer.Left( 8 );
		buffer = buffer.Mid( 8 );
Kommentar( "Höhenangabe: ", 3 );
KommNL( temp, 3 );
		temp = buffer.Left( 5 );
		buffer = buffer.Mid( 5 );
Kommentar( "Jahr/Monat der Höhenmessung: 1", 3 );
KommNL( temp, 3 );
		temp = buffer.Left( 5 );
		buffer = buffer.Mid( 5 );
Kommentar( "Art der Höhengenauigkeit: ", 3 );
KommNL( temp.Left( 1 ), 3 );
Kommentar( "Wert der Höhengenauigkeit: ", 3 );
KommNL( temp.Mid( 1 ), 3 );
		temp = buffer.Left( 1 );
		buffer = buffer.Mid( 1 );
Kommentar( "Höhenzuverlässigkeit: ", 3 );
KommNL( temp, 3 );
		temp = buffer.Left( 3 );
		buffer = buffer.Mid( 3 );
Kommentar( "Jahr der Berechnung: 1", 3 );
KommNL( temp, 3 );
		temp = buffer.Left( 9 );
		buffer = buffer.Mid( 9 );
Kommentar( "Aktenhinweis: ", 3 );
KommNL( temp, 3 );
	}

	if ((( n > 0 ) && ( buffer == "000000000000" )) ||
		(( buffer == "00000000" ) && ( n == 0 )))
	{
		KommNL( "Daten korrekt abgeschlossen!", 3 );
	}
	else
	{
		KommNL( "Syntaxfehler!", 3 );
		Kommentar( "Rest: >", 3 );
		Kommentar( buffer, 3 );
		KommNL( "<", 3 );
	}
}

void CAtkisSatz :: GrundrissKennDaten( const char *daten )
{
	m_StartPunkt.Setzen( daten );

}	// GrundrissKennDaten

const char * CAtkisSatz :: ArtGeometrie( short lnr )
{
	if ( lnr < m_Linien.GetSize())
		return ((CLinie*)m_Linien[lnr]) -> ArtGeometrie();
	else
		return NULL;
}	// ArtGeometrie

short CAtkisSatz :: AnzahlPunkte( short lnr )
{
	if ( lnr < m_Linien.GetSize())
		return ((CLinie*)m_Linien[lnr]) -> PunkteZahl();
	else
		return 0;
}	// 

short CAtkisSatz :: NumFktParam( short lnr )
{
	if ( lnr < m_Linien.GetSize())
		return ((CLinie*)m_Linien[lnr]) -> FktZahl();
	else
		return 0;
}	// 

const char *CAtkisSatz :: ObjektNummerRechts( short lnr, short fnr )
{
	if ( lnr < m_Linien.GetSize())
		if ( fnr < ((CLinie*)m_Linien[lnr]) -> FktZahl())
			return ((CLinie*)m_Linien[lnr]) ->
					Funktion( fnr ) -> ObjNr1();
		else
			return NULL;
	else
		return NULL;
}	// 

const char *CAtkisSatz :: ObjektteilNummerRechts( short lnr, short fnr )
{
	if ( lnr < m_Linien.GetSize())
		if ( fnr < ((CLinie*)m_Linien[lnr]) -> FktZahl())
			return ((CLinie*)m_Linien[lnr]) ->
					Funktion( fnr ) -> ObjTeilNr1();
		else
			return NULL;
	else
		return NULL;
}	// 

const char *CAtkisSatz :: LinienTeilungRechts( short lnr, short fnr )
{
	if ( lnr < m_Linien.GetSize())
		if ( fnr < ((CLinie*)m_Linien[lnr]) -> FktZahl())
			return ((CLinie*)m_Linien[lnr]) ->
					Funktion( fnr ) -> LinienTeilung1();
		else
			return NULL;
	else
		return NULL;
}	// 

const char *CAtkisSatz :: Folie( short lnr, short fnr )
{
	if ( lnr < m_Linien.GetSize())
		if ( fnr < ((CLinie*)m_Linien[lnr]) -> FktZahl())
			return ((CLinie*)m_Linien[lnr]) ->
					Funktion( fnr ) -> Folie();
		else
			return NULL;
	else
		return NULL;
}	// 

const char *CAtkisSatz :: ObjektArt( short lnr, short fnr )
{
	if ( lnr < m_Linien.GetSize())
		if ( fnr < ((CLinie*)m_Linien[lnr]) -> FktZahl())
			return ((CLinie*)m_Linien[lnr]) ->
					Funktion( fnr ) -> ObjArt();
		else
			return NULL;
	else
		return NULL;
}	// 

const char *CAtkisSatz :: ObjektNummerLinks( short lnr, short fnr )
{
	if ( lnr < m_Linien.GetSize())
		if ( fnr < ((CLinie*)m_Linien[lnr]) -> FktZahl())
			return ((CLinie*)m_Linien[lnr]) ->
					Funktion( fnr ) -> ObjNr2();
		else
			return NULL;
	else
		return NULL;
}	// 

const char *CAtkisSatz :: ObjektteilNummerLinks( short lnr, short fnr )
{
	if ( lnr < m_Linien.GetSize())
		if ( fnr < ((CLinie*)m_Linien[lnr]) -> FktZahl())
			return ((CLinie*)m_Linien[lnr]) ->
					Funktion( fnr ) -> ObjTeilNr2();
		else
			return NULL;
	else
		return NULL;
}	// 

const char *CAtkisSatz :: LinienTeilungLinks( short lnr, short fnr )
{
	if ( lnr < m_Linien.GetSize())
		if ( fnr < ((CLinie*)m_Linien[lnr]) -> FktZahl())
			return ((CLinie*)m_Linien[lnr]) ->
					Funktion( fnr ) -> LinienTeilung2();
		else
			return NULL;
	else
		return NULL;
}	// 

double CAtkisSatz :: EndPunktHoch( short lnr )
{
	if ( lnr < m_Linien.GetSize())
		return ((CLinie*)m_Linien[lnr]) -> EndPunktHoch();
	else
		return 0L;
}	// 

double CAtkisSatz :: EndPunktRechts( short lnr )
{
	if ( lnr < m_Linien.GetSize())
		return ((CLinie*)m_Linien[lnr]) -> EndPunktRechts();
	else
		return 0L;
}	// 

BOOL CAtkisSatz :: ObjFkt( short onr )
{
	return ( onr < m_Objekte.GetSize());
}	// 

const char *CAtkisSatz :: OF_Folie( short onr )
{
	if ( onr < m_Objekte.GetSize())
		return ((CObjekt*)m_Objekte[onr]) -> Folie();
	else
		return NULL;
}	// 

const char *CAtkisSatz :: OF_Objektart( short onr )
{
	if ( onr < m_Objekte.GetSize())
		return ((CObjekt*)m_Objekte[onr]) -> ObjArt();
	else
		return NULL;
}	// 

const char *CAtkisSatz :: OF_Aktuali( short onr )
{
	if ( onr < m_Objekte.GetSize())
		return ((CObjekt*)m_Objekte[onr]) -> Aktuali();
	else
		return NULL;
}	// 

const char *CAtkisSatz :: OF_Objekttyp( short onr )
{
	if ( onr < m_Objekte.GetSize())
		return ((CObjekt*)m_Objekte[onr]) -> ObjTyp();
	else
		return NULL;
}	// 

const char *CAtkisSatz :: OF_Objektnummer( short onr )
{
	if ( onr < m_Objekte.GetSize())
		return ((CObjekt*)m_Objekte[onr]) -> ObjNr();
	else
		return NULL;
}	// 

const char *CAtkisSatz :: OF_Modelltyp( short onr )
{
	if ( onr < m_Objekte.GetSize())
		return ((CObjekt*)m_Objekte[onr]) -> ModellTyp();
	else
		return NULL;
}	// 

const char *CAtkisSatz :: OF_Datum( short onr )
{
	if ( onr < m_Objekte.GetSize())
		return ((CObjekt*)m_Objekte[onr]) -> EDatum();
	else
		return NULL;
}	// 

const char *CAtkisSatz :: OF_Aender( short onr )
{
	if ( onr < m_Objekte.GetSize())
		return ((CObjekt*)m_Objekte[onr]) -> ModKenn();
	else
		return NULL;
}	// 

short CAtkisSatz :: OF_AnzahlBesInfo( short onr )
{
	if ( onr != 0 )
		AfxMessageBox( "Syntaxfehler!\nDatenverlust möglich!" );

	return m_Infos.GetSize();
}	// 

short CAtkisSatz :: OF_BI_Anzahl( short, short )
{
	return 1;
}	// 

const char *CAtkisSatz :: OF_BI_Art( short, short inr )
{
	if ( inr < m_Infos.GetSize())
		return ((CInfo*)m_Infos[inr]) -> ArtInfo();
	else
		return NULL;
}	// 

const char *CAtkisSatz :: OF_BI_Kartentyp( short, short inr )
{
	if ( inr < m_Infos.GetSize())
		return ((CInfo*)m_Infos[inr]) -> KartenTyp();
	else
		return NULL;
}	// 

const char *CAtkisSatz :: OF_BI_Objektart( short, short inr )
{
	if ( inr < m_Infos.GetSize())
		return ((CInfo*)m_Infos[inr]) -> ObjArt();
	else
		return NULL;
}	// 

const char *CAtkisSatz :: OF_BI_Text( short, short inr )
{
	if ( inr < m_Infos.GetSize())
		return ((CInfo*)m_Infos[inr]) -> Text();
	else
		return NULL;
}	// 

const char *CAtkisSatz :: OF_BI_ArtGeo( short, short inr )
{
	if ( inr < m_Infos.GetSize())
		return ((CInfo*)m_Infos[inr]) -> ArtGeo();
	else
		return NULL;
}	// 

const char *CAtkisSatz :: OF_BI_ObjTeilNr( short, short inr )
{
	if ( inr < m_Infos.GetSize())
		return ((CInfo*)m_Infos[inr]) -> ObjTeilNr();
	else
		return NULL;
}	// 

BOOL CAtkisSatz :: OF_BI_GeoAngaben( short, short inr )
{
	if ( inr < m_Infos.GetSize())
		return ((CInfo*)m_Infos[inr]) -> GeoAngaben();
	else
		return FALSE;
}	// 

double CAtkisSatz :: OF_BI_Koord1Hoch( short, short inr )
{
	if ( inr < m_Infos.GetSize())
		return ((CInfo*)m_Infos[inr]) -> Pkt1Hoch();
	else
		return 0.0;
}	// 

double CAtkisSatz :: OF_BI_Koord1Rechts( short, short inr )
{
	if ( inr < m_Infos.GetSize())
		return ((CInfo*)m_Infos[inr]) -> Pkt1Rechts();
	else
		return 0.0;
}	// 

double CAtkisSatz :: OF_BI_Koord2Hoch( short, short inr )
{
	if ( inr < m_Infos.GetSize())
		return ((CInfo*)m_Infos[inr]) -> Pkt2Hoch();
	else
		return 0.0;
}	// 

double CAtkisSatz :: OF_BI_Koord2Rechts( short, short inr )
{
	if ( inr < m_Infos.GetSize())
		return ((CInfo*)m_Infos[inr]) -> Pkt2Rechts();
	else
		return 0.0;
}	// 

double CAtkisSatz :: OF_BI_Koord3Hoch( short, short inr )
{
	if ( inr < m_Infos.GetSize())
		return ((CInfo*)m_Infos[inr]) -> Pkt3Hoch();
	else
		return 0.0;
}	// 

double CAtkisSatz :: OF_BI_Koord3Rechts( short, short inr )
{
	if ( inr < m_Infos.GetSize())
		return ((CInfo*)m_Infos[inr]) -> Pkt3Rechts();
	else
		return 0.0;
}	// 

BOOL CAtkisSatz::OF_BI_PunktGueltig( short inr, short n )
{
	if ( inr < m_Infos.GetSize())
		return ((CInfo*)m_Infos[inr]) -> PktGueltig( n );
	else
		return FALSE;
}

double CAtkisSatz :: LinienPunktHoch( short lnr, short pnr )
{
	if ( lnr < m_Linien.GetSize())
		return ((CLinie*)m_Linien[lnr]) -> PunktHoch( pnr );
	else
		return 0.0;
}	// LinienPunktHoch

double CAtkisSatz :: LinienPunktRechts( short lnr, short pnr )
{
	if ( lnr < m_Linien.GetSize())
		return ((CLinie*)m_Linien[lnr]) -> PunktRechts( pnr );
	else
		return 0.0;
}	// LinienPunktRechts

IMPLEMENT_SERIAL( CAtkisSatz, CObject, 0 )

BOOL CAtkisSatz::HatObjekte( int i )
{
	CString	txt;
	BOOL	result = FALSE;
	int		l;

	for ( l = 0; l < NumFktParam( i ); l++ )
	{
		txt = ObjektNummerRechts( i, l );
		AllTrimm( txt );
		if ( txt.GetLength())	result = TRUE;

		txt = ObjektNummerLinks( i, l );
		AllTrimm( txt );
		if ( txt.GetLength())	result = TRUE;
	}
	return result;
}	// HatObjekte

char CAtkisSatz::SplineKennung( short lnr )
{
	if ( lnr < m_Linien.GetSize())
		return ((CLinie*)m_Linien[lnr]) -> SplineKennung();
	else
		return ' ';
}	// SplineKennung
