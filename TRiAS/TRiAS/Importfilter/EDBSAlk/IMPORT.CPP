///////////////////////////////////////////////////////////////////////
//	TRiAS - Erweiterung: EDBS - Import
///////////////////////////////////////////////////////////////////////
//	Datei:			import.cpp
//
//	Stand:			31.08.1995
//	Beschreibung:	Import-Objekt
//	Entwicklung:	15.11.94	Beginn der Kodierung
//					31.08.95	Umstellung auf lineares Parsing
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "resource.h"
#include "import.hpp"
#include "geoobj.hpp"
#include "objpool.hpp"
#include "actdia.hpp"
#include "setupdlg.hpp"
#include "DlgConfig.h"
#include "trif.hpp"
#include "cxstring.h"

#include "koorpaar.h"
#include "linie.h"
#include "edbssatz.h"
#include "atkissat.h"
#include "GeoCvt.h"

//#include "statimpl.hxx"
#include "istatus.h"
#include "edbs.hpp"

#include "cwc.h"

static CErrStream *pLogStream;
#define cout	(*((ostream*)pLogStream))

#define _ENABLE_KOMMENTAR_	1
//#define _KOMMENTAR_LEVEL_	3
static DWORD	g_iLogLevel;

#include	<errno.h>


void		Kommentar( const char*, const DWORD );
void		Kommentar( int, const DWORD );
void		Kommentar( long, const DWORD );
void		Kommentar( double, const DWORD );
void		Kommentar( char, const DWORD );
void		Meldung( const char* );
void		Meldung( int );
void		Meldung( long );
void		KommNL( const char*, const DWORD );
void		KommNL( int, const DWORD );
void		KommNL( long, const DWORD );
void		KommNL( double, const DWORD );
void		KommNL( char, const DWORD );
void		MeldNL( const char* );
void		MeldNL( int );
void		MeldNL( long );
void		MeldNL( double );
//int			Trimm( CString& );
//int			LTrimm( CString& );
//int			AllTrimm( CString& );
//void		Transform( CString& );


//#fje980727//=====================================================================
//#include "W:\Projekte\GeoCvt\GeometryConversionService.h"
//#include "W:\Projekte\GeoCvt\GeometryConversionService_i.c"
//extern IArcConversion *g_pIArcConversion;

///////////////////////////////////////////////////////////////////////
//	CImportEDBS

//CImportEDBS :: CImportEDBS( LPUNKNOWN pExt )
//		: CImportGeoData( pExt )
CImportEDBS :: CImportEDBS()
		: CImportGeoData()
{
	m_hWnd = NULL;
	g_pObjektPool = NULL;
	g_pTriasInterface = NULL;

	m_pktStart = NULL;
	m_pktEnd = NULL;
	m_bDataSaved = FALSE;
	m_bSavedDataUsed = FALSE;
	m_bAENDprocessed = false;
}


CImportEDBS :: ~CImportEDBS()
{
	if ( g_pObjektPool )		delete g_pObjektPool;
	if ( g_pTriasInterface )	delete g_pTriasInterface;
	if ( pLogStream )			delete pLogStream;
	if ( m_pktStart != NULL )	delete m_pktStart;
	if ( m_pktEnd != NULL )		delete m_pktEnd;
	m_pktStart = NULL;
	m_pktEnd = NULL;
}

// *** IImportGeoData methods -------------------------------------------------
// Abfrage der Eigenschaften und Möglichkkeiten des ImportModuls (siehe Flags
// in File IXTENSN.HXX IMPORTCAPS_...
STDMETHODIMP_(DWORD) CImportEDBS :: Capabilities (void)
{
	CCfg	*pConfiguration;

	pConfiguration = &((CEDBSExtension*)g_pTE)->Configuration;
	
	if( pConfiguration->m_tEnabled )
		return IMPORTCAPS_CANIMPORTGEOMETRY  | /*IMPORTCAPS_OPTIMPORTFEATURES |*/
	       /*IMPORTCAPS_CANIMPORTRELATIONS | IMPORTCAPS_OPTIMPORTGEOMETRY |*/
	       IMPORTCAPS_CANIMPORTFEATURES  | /*IMPORTCAPS_OPTIMPORTRELATIONS*/
	       IMPORTCAPS_MULTIPLEFILES /*| IMPORTCAPS_SHOULDCONFIG*/;
	else
		return IMPORTCAPS_CANIMPORTGEOMETRY  | /*IMPORTCAPS_OPTIMPORTFEATURES |*/
	       /*IMPORTCAPS_CANIMPORTRELATIONS | IMPORTCAPS_OPTIMPORTGEOMETRY |*/
	       IMPORTCAPS_CANIMPORTFEATURES  | /*IMPORTCAPS_OPTIMPORTRELATIONS*/
	       IMPORTCAPS_MULTIPLEFILES /*| IMPORTCAPS_SHOULDCONFIG*/;

}

// Diese Funktion wird nur dann gerufen, wenn 'Capabilities' das Flag
// IMPORTCAPS_SHOULDCONFIGURE geliefert hat. Im dieser Funktion sollte die
// Konfiguration des Modules für den nächsten Import durchgeführt werden.
STDMETHODIMP CImportEDBS :: Configure (HWND hWnd)
{
/*
	CCfg*	pConfiguration;
	CPropertySheet	dlgConfig;
	CDlgCfgCommon	pagCommon;
	CDlgCfgDefault	pagDefault;
	CDlgCfgExtra	pagExtra;

	m_hWnd = hWnd;
	
	pConfiguration = &((CEDBSExtension*)g_pTE)->Configuration;
	pConfiguration->ppagCommon = &pagCommon;
	pConfiguration->ppagDefault = &pagDefault;
	if (DEX_QueryMode() & QMSysAdmin)
		pConfiguration->ppagExtra = &pagExtra;
	else
		pConfiguration->ppagExtra = NULL;

	dlgConfig.AddPage( &pagCommon );
	dlgConfig.SetWizardMode();

	if( ID_WIZFINISH == dlgConfig.DoModal() )
		((CEDBSExtension*)g_pTE)->Configuration.Save();
*/	
	return ResultFromScode (NOERROR);
}

STDMETHODIMP CImportEDBS::put_CS(IUnknown *pICS)
{
	m_CS = pICS;
	return S_OK;
}

// Das ist die eigentliche ImportFunktion, die einmal gerufen wird und dann alles
// machen muß, was sie für richtig hält. 
// Der Enumerator pEnumFiles liefert die Dateinamen der zu importierenden Datei(en)
// (ACHTUNG: UNICODE!!! und OLE-TaskAllocator)

#ifndef _WIN32
typedef LPSTR	LPWSTR;
#endif

STDMETHODIMP CImportEDBS :: ImportData (IEnumString *pEnumFiles, DWORD dwFlags)
{
	LPWSTR pFile = NULL;
	ULONG ulGot = 0;
	HRESULT hr = ResultFromScode (E_FAIL);
	CWaitCur	wait_cursor;

	CStringArray	FileListe;
	CxString	filename, maske, text;
	short		i, n;


	// Statusfenster erzeugen
	((CEDBSExtension*)g_pTE) -> CreateStatusDialog();

	((CEDBSExtension*)g_pTE) -> InitStatusDialog( "Laden der Metadaten", (ULONG)0, NULL );
//	g_pMetaData->SetDefinition( "EDBSALK.INI" );

	if( NULL == g_pMetaData ) {
		g_pMetaData = new CMetaData;
		g_pMetaData->Load();
	}

	i = 0;
	while (S_OK == pEnumFiles -> Next (1, (LPOLESTR *)&pFile, &ulGot))
	{	FileListe.SetAtGrow( i++, AnsiString (pFile));
		CoTaskMemFree (pFile);
	}

//	text.GetPrivateProfileString( "Report", "Level", "0", 255, g_pMetaData->strIniFileName );
//	g_iLogLevel = atoi( text );
	g_iLogLevel = ((CEDBSExtension*)g_pTE)->Configuration.m_dwReportBase;

	maske.LoadString( IDS_MULTIFILE );
	text.LoadString( IDS_ONEFILE );
	n = FileListe.GetSize();
	m_iFileCount = n;
	for ( i = 0; i < n; i++ ) {
		filename = FileListe[i];
		m_iCurrFileNum = i;
		if( m_iFileCount > 1 )
			text.printf( maske, m_iCurrFileNum+1, m_iFileCount );

		((CEDBSExtension*)g_pTE) -> ChangeStatusText( text, NULL );

try {
	// alle Dateien nacheinander abarbeiten
		hr = ImportEDBS( filename );
}
catch( ... ) {
	AfxMessageBox( "Unerwarteter Fehler in ImportData",0,0);
}
		if( FAILED(hr) )
			break;
		if( ((CEDBSExtension*)g_pTE) ->NutzerAbbruch() )
			break;
	}


	// Statusfenster schließen
	((CEDBSExtension*)g_pTE) -> ReleaseStatusDialog();

	delete g_pMetaData;
	g_pMetaData = NULL;

	return hr;
}


STDMETHODIMP CImportEDBS :: ImportEDBS (const char *pFile )
{
	HRESULT hr = NOERROR;
	BOOL	bHdrUpdate = FALSE;
	int	pos1, pos2;

	m_strFileName = pFile;

	g_pTriasInterface = new CTriasInterface;
	g_pTriasInterface->strImportFullFileName = m_strFileName;
	pos1 = m_strFileName.ReverseFind('\\');
	if( pos1 ) 
		g_pTriasInterface->strImportFileName = m_strFileName.Mid(pos1+1);
	else
		g_pTriasInterface->strImportFileName = m_strFileName;
	pos2 = m_strFileName.ReverseFind('.');
	if( pos1 > 0 && pos2 > pos1 ) {
		g_pTriasInterface->strImportFullLogFileName = m_strFileName.Left(pos2+1);
		g_pTriasInterface->strImportFullLogFileName += "log";
		TRY {
		    CFile::Remove( g_pTriasInterface->strImportFullLogFileName );
		} CATCH( CFileException, e )
		{
#ifdef _DEBUG
        afxDump << "File " << g_pTriasInterface->strImportFullLogFileName << " cannot be removed\n";
#endif
		}
		END_CATCH
		if( g_iLogLevel > 0 )
			pLogStream = new CErrStream( g_pTriasInterface->strImportFullLogFileName );

		g_pTriasInterface->strImportFullErrorLogFileName = m_strFileName.Left(pos2+1);
		g_pTriasInterface->strImportFullErrorLogFileName += "err";
		TRY {
		    CFile::Remove( g_pTriasInterface->strImportFullErrorLogFileName );
		} CATCH( CFileException, e )
		{
#ifdef _DEBUG
        afxDump << "File " << g_pTriasInterface->strImportFullErrorLogFileName << " cannot be removed\n";
#endif
		}
		END_CATCH
	}
	else {
		g_pTriasInterface->strImportFullLogFileName.Empty();
		g_pTriasInterface->strImportFullErrorLogFileName.Empty();
	}

	g_pObjektPool = new CObjektPool;

	if ( g_pTriasInterface && g_pObjektPool )
		StartImport();

	if ( g_pObjektPool ) {
		if( ((CEDBSExtension*)g_pTE) ->NutzerAbbruch() ) {
			g_pObjektPool -> Clear();
		}
		delete g_pObjektPool;
	}
	g_pObjektPool = NULL;

	if ( pLogStream )
		delete pLogStream;
	pLogStream = NULL;

	if ( g_pTriasInterface )
		delete g_pTriasInterface;
	g_pTriasInterface = NULL;

	return hr;
}

extern HRESULT UnzipFileFromFile(CString strSourceFileName, CString& strDestinationFileName );

void CImportEDBS :: StartImport()
{	long					num_parser_calls;
//	long				edbs_file_length, edbs_file_pos;
	long				edbs_file_pos;
	char				edbs_file_type[2];
//	CActiDialog			Dlg;
	CEdbsSatz			EdbsSatz;
	CAtkisSatz			AtkisSatz;
	CFile				f;

	POSITION			pos;
	CxString			text, temp, maske, stattext;
	CString				strSourceFileName;
	HRESULT				hResult;
	CStringList			*pL;
	MSG					msg;
	bool				tIsZipFile;
//	zuerst Datei testen
	if ( !f.Open( m_strFileName, CFile::modeRead ))
		return;

	UINT nBytesRead = f.Read( edbs_file_type, 2 );

	if( edbs_file_type[0] == 'P' && edbs_file_type[1] == 'K' ) {
		f.Close(); 
//        Me!StatusBar.Panels(1).Text = strSourceDir & strSourceFile & " wird entpackt ..."
        hResult = UnzipFileFromFile(m_strFileName, strSourceFileName);
		if ( !f.Open( strSourceFileName, CFile::modeRead ))
			return;
		tIsZipFile = true;
	}
	else
		tIsZipFile = false;
	edbs_file_length = f.GetLength();

	f.SeekToBegin();
	CArchive	Ar( &f, CArchive::load );

	((CEDBSExtension*)g_pTE) -> SetDefaultStatusTexte( NULL, NULL, "Datei:", NULL );

	text = m_strFileName;
	maske.LoadString( IDS_MULTIFILE );
	stattext.LoadString( IDS_ONEFILE );
	if ( m_iFileCount > 1 ) stattext.printf( maske, m_iCurrFileNum+1, m_iFileCount );
	((CEDBSExtension*)g_pTE) -> InitStatusDialog( text, (ULONG)edbs_file_length, stattext );

	char	zeile[64];
	sprintf( zeile, "%ld Byte", edbs_file_length );

	for (num_parser_calls = 1; ; ++num_parser_calls) {
		// lex and parse the input file pausing after each statement
		EdbsSatz.Lesen( &Ar );
		if ( EdbsSatz.Gueltig()) {
			AtkisSatz.Lesen( num_parser_calls, EdbsSatz.Daten());
			edbs_file_pos = f.GetPosition();

			m_bEnde = ((edbs_file_pos * 1.1) > edbs_file_length );
			sprintf( zeile, "%ld Byte", edbs_file_pos );
//			Dlg.SetFilePos( zeile );
			((CEDBSExtension*)g_pTE) -> SetupStatus( (ULONG)edbs_file_pos );

		// check to see if the parser is all done parsing a program

			if ( AtkisSatz.Komplett()) {
				Interpretiere( &AtkisSatz );
			}

		// und eine kleine Pause
			while ( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ))
			{	TranslateMessage( &msg );
				DispatchMessage( &msg );
			}

			if( ((CEDBSExtension*)g_pTE) -> NutzerAbbruch() ) {
				if ( AfxMessageBox( "Alle bisher gelesenen Informationen gehen beim Abbruch verloren!\nTatsächlich abbrechen?",
					MB_ICONQUESTION|MB_YESNO ) == IDYES ) {
					KommNL( "Nutzerabbruch!", 0 );
					break;
				}
				else
					((CEDBSExtension*)g_pTE) -> ResetAbbruch();
			}	
		}
		else {
			KommNL( "Syntaxfehler in der EDBS-Struktur!", 0 );
			break;
		}
	}

	if( ((CEDBSExtension*)g_pTE) ->NutzerAbbruch() )
		Meldung( "Import abgebrochen!" );
	else if( !m_bAENDprocessed )
		g_pObjektPool -> WriteBack( true );
	
	Meldung( num_parser_calls );
	Meldung( " Parser-Aufrufe!\n" );


	KommNL( " ", 3 );
	KommNL( "Aufgetretene Attribute/Merkmale:", 3 );
	pL  = &g_pTriasInterface -> MerkmalList();
	pos = pL -> GetHeadPosition();
	while ( pos )
	{	text = pL -> GetNext( pos );
		KommNL( text, 3 );
	}

	g_pTriasInterface -> Flush();

	if( tIsZipFile ) 
		DeleteFile( strSourceFileName );

}	// StartImport


void CImportEDBS :: Interpretiere( void *pvSatz )
{
	CxString	maske, stattext;

	CAtkisSatz		*pSatz = (CAtkisSatz*)pvSatz;
	m_bAENDprocessed = false;
	switch ( pSatz -> Start()) {
	case CAtkisSatz::AKND:
		KommNL( "AKND  (Anfang!)", 1 );
		break;
	case CAtkisSatz::BKRT:
		KommNL( "BKRT  (nicht ausgewertet!!)", 1 );
		break;
	case CAtkisSatz::BINF:
		KommNL( "BINF  (nicht ausgewertet!)", 1 );
		break;
	case CAtkisSatz::BSPE:
		KommNL( "BSPE  (Objekt ausgewertet!)", 1 );
		GeoObjektEinordnen( pvSatz );
		break;
	case CAtkisSatz::FEIN:
		KommNL( "FEIN  (Objekt eingeordnet!)", 1 );
		GeoObjektEinordnen( pvSatz );
		break;
	case CAtkisSatz::FAEN:
		KommNL( "FAEN  (nicht ausgewertet!)", 1 );
		break;
	case CAtkisSatz::FLOE:
		KommNL( "FLOE  (nicht ausgewertet!)", 1 );
		break;
	case CAtkisSatz::FALG:
		KommNL( "FALG  (nicht ausgewertet!)", 1 );
		break;
	case CAtkisSatz::AEND:
		m_bAENDprocessed = true;
		KommNL( "AEND  (Ende!)", 1 );
		Kommentar( g_pObjektPool -> GetSize(), 1 );
		KommNL( " Objekte gelesen", 1 );
//		g_pTriasInterface -> EnableCrtMemDbgFlag( TRUE );
		g_pObjektPool -> WriteBack( m_bEnde );
//		g_pTriasInterface -> EnableCrtMemDbgFlag( FALSE );
		// StatusDialog zurücksetzen
		maske.LoadString( IDS_MULTIFILE );
		stattext.LoadString( IDS_ONEFILE );
		if ( m_iFileCount > 1 ) stattext.printf( maske, m_iCurrFileNum+1, m_iFileCount );
		((CEDBSExtension*)g_pTE) -> InitStatusDialog( m_strFileName,
					(ULONG)edbs_file_length, stattext );
		break;
	default:
		KommNL( "unbekannter Satztyp!!", 1 );
		break;
	}
}	// Interpretiere


void CImportEDBS :: GeoObjektEinordnen( void *pvSatz )
{
	CAtkisSatz*		pSatz = (CAtkisSatz*)pvSatz;
	int				i, iAnzahlPunkte, j, k, k1;
	int				iArtGeo;
	CxString		txt, txt1, txt2, txt3, txt4;
	CxString		xsID, xsKey, xsText, xsTemp;

	
	if ( pSatz -> ObjektDaten()) {
		Kommentar( "Start ", 3 );
		Kommentar( pSatz -> GrundPunktHoch(), 3 ); Kommentar( " : ", 3 );
		KommNL( pSatz -> GrundPunktRechts(), 3 );

		if ( pSatz -> AnzahlLinien() < 1 )
			KommNL( "Keine Linien!", 3 );
		for ( i = 0; i < pSatz -> AnzahlLinien(); i++ ) {
			Kommentar( "Linie ", 3 ); Kommentar( i+1, 3 ); Kommentar( " : ", 3 );
			Kommentar( pSatz -> ArtGeometrie( i ), 3 );
			switch ( atoi( pSatz -> ArtGeometrie( i ))) {
			case _Gerade:
				KommNL( " (Gerade)", 3 );
				break;
			case _Polygonzug:
				KommNL( " (Polygon)", 3 );
				if( pSatz -> AnzahlPunkte( i ) == 0 )
					KommNL( " (Polygon zu kurz)", 3 );
				break;
			case _Kreisbogen_rechts:
				KommNL( " (Kreisbogen rechts)", 3 );
				if( pSatz -> AnzahlPunkte( i ) == 0 )
					KommNL( " (Kreis ohne Mittelpunkt)", 3 );
				break;
			case _Kreisbogen_links:
				KommNL( " (Kreisbogen links)", 3 );
				if( pSatz -> AnzahlPunkte( i ) == 0 )
					KommNL( " (Kreis ohne Mittelpunkt)", 3 );
				break;
			case _Kurve:
				KommNL( " (Kurve)", 3 );
				Kommentar( "Splinekennung: ", 3 );
				KommNL( pSatz -> SplineKennung( i ), 3 );
				break;
			default:
				KommNL( " (???)", 3 );
				break;
			}

			iAnzahlPunkte = pSatz -> AnzahlPunkte( i );
			iArtGeo = atoi( pSatz -> ArtGeometrie( i ));
			Kommentar( "    Anzahl Punkte = ", 3 ); KommNL( iAnzahlPunkte + 2, 3 );

			if ( !pSatz -> HatObjekte( i )) {
				KommNL( "    Keine Objekte!", 3 );
				if ( GeometrieSaved()) {
					// gespeicherte Geometrie mit akt. Obj. einordnen
					SavedGeoDataEinordnen( pSatz, i );
					m_bSavedDataUsed = TRUE;
				}
				else
					KommNL( "!!! Fehler! Geometrie ohne Objektanbindung! !!!", 1 );
			}
			else {
				if ( GeometrieSaved()) {
					if ( !m_bSavedDataUsed ) {
						KommNL( "!!! Fehler! Unvollständige Geometrie: Kurve/Polygon entartet!", 1 );
						GeoDataEinordnen( pSatz, i );
					}
					FreeSavedData();
				}

				if (( iAnzahlPunkte == 0 ) &&
					(( iArtGeo == _Polygonzug ) || ( iArtGeo == _Kurve ))) {
					SaveData( pSatz );
					m_bSavedDataUsed = FALSE;
					// nicht speichern!!
				}
				else
					GeoDataEinordnen( pSatz, i );
			}
		}

		Kommentar( "ObjektFunktionen: ", 3 );
		if ( pSatz -> ObjFkt( 0 )) {
			KommNL( " ", 3 );

			j = 0;
			while ( pSatz -> ObjFkt( j ))
			{	Kommentar( "    Folie:         ", 3 ); KommNL( pSatz -> OF_Folie( j ), 3 );
				Kommentar( "    Objektart:     ", 3 ); KommNL( pSatz -> OF_Objektart( j ), 3 );
				Kommentar( "    Aktualitaet:   ", 3 ); KommNL( pSatz -> OF_Aktuali( j ), 3 );
				Kommentar( "    Objekttyp:     ", 3 ); KommNL( pSatz -> OF_Objekttyp( j ), 3 );
				Kommentar( "    Objektnummer:  ", 3 ); KommNL( pSatz -> OF_Objektnummer( j ), 3 );
				Kommentar( "    Modelltyp:     ", 3 ); KommNL( pSatz -> OF_Modelltyp( j ), 3 );
				Kommentar( "    Datum:         ", 3 ); KommNL( pSatz -> OF_Datum( j ), 3 );
				Kommentar( "    AenderKennung: ", 3 ); KommNL( pSatz -> OF_Aender( j ), 3 );

				if ( pSatz -> OF_AnzahlBesInfo( j )) {
					Kommentar( "    Besondere Infos:    ", 3 ); KommNL( k = pSatz -> OF_AnzahlBesInfo( j ), 3 );
					k1 = 0;
					while ( k1 < k ) {
						Kommentar( "        Anzahl:         ", 3 ); KommNL( pSatz -> OF_BI_Anzahl( j, k1 ), 3 );
						Kommentar( "        Art der Info:   ", 3 ); KommNL( pSatz -> OF_BI_Art( j, k1 ), 3 );
						Kommentar( "        Kartentyp:      ", 3 ); KommNL( pSatz -> OF_BI_Kartentyp( j, k1 ), 3 );
						Kommentar( "        Objektart:      ", 3 ); KommNL( pSatz -> OF_BI_Objektart( j, k1 ), 3 );
						Kommentar( "        Text:           ", 3 );
							txt = pSatz -> OF_BI_Text( j, k1 ); 
							txt.Transform(g_pMetaData->pConfiguration->m_sCodePage);
							KommNL( txt, 3 );
						Kommentar( "        Art Geometrie:  ", 3 ); KommNL( pSatz -> OF_BI_ArtGeo( j, k1 ), 3 );
						Kommentar( "        Objektteil Nr.: ", 3 ); KommNL( pSatz -> OF_BI_ObjTeilNr( j, k1 ), 3 );
						if ( pSatz -> OF_BI_GeoAngaben( j, k1 )) {
						}
						k1++;
					}	
				}
				else
					KommNL( "        Besondere Infos nicht vorhanden!", 3 );

				j++;
			}
		}
		else
			KommNL( "nicht vorhanden!", 3 );

		if ( pSatz -> ObjFkt( 0 )) {
			j = 0;
			while ( pSatz -> ObjFkt( j )) {
				txt = pSatz -> OF_Objektnummer( j );
				txt += "H";
				txt4 = pSatz -> OF_Objektart( j );
				txt4.TrimAll();
				if ( pSatz -> OF_AnzahlBesInfo( j )) {
					k = pSatz -> OF_AnzahlBesInfo( j );
					k1 = 0;
					while ( k1 < k ) {	
						g_pObjektPool -> BesondInfo( j, k1, pSatz );
						k1++;
					}	
				}

				txt1 = pSatz -> OF_Objekttyp( j );
				txt1.TrimAll();
				txt3 = pSatz -> OF_Folie( j );
				txt3.TrimAll();
				g_pObjektPool -> DefType( txt, txt1, txt4, txt3 );

				j++;
			}	
		}
	}
	else
		KommNL( "Keine Objektdaten!", 3 );

	if ( pSatz -> AttributSatz())
	{	Kommentar( "Attribute zu: ", 3 );
			Kommentar( pSatz -> AttrObjNr(), 3 );
			Kommentar( "-", 3 );
			Kommentar( pSatz -> AttrObjTeilNr(), 3 );
			Kommentar( "  ", 3 );
			KommNL( pSatz -> AttrPruefZeichen(), 3 );
		if ( pSatz -> AttrAnzahl())
			KommNL( pSatz -> Attribute(), 3 );

		if ( pSatz -> AttrAnzahl())
		{	xsID   = pSatz -> AttrObjNr();
			xsID.TrimAll();
			xsTemp = pSatz -> Attribute();
			for ( i = 1; i <= pSatz -> AttrAnzahl(); i++ )
			{	xsText = xsTemp.Left( 11 );
				if ( i ) xsTemp = xsTemp.Mid( 11 );
				xsKey  = xsText.Left( 4 );
				xsText = xsText.Mid( 4 );
				xsKey.TrimAll();
				xsText.TrimAll();
				if ( !xsKey.IsEmpty() && !xsText.IsEmpty())
					g_pObjektPool -> AddMerkmal( xsID, xsKey, xsText );
	}	}	}
	else
		KommNL( "Keine Attribute!", 3 );

	KommNL( " ", 3 );
}	// GeoObjektEinordnen

void CImportEDBS :: CreateTriasObjekt( void* ptr )
{	CGeoObj		*pGO = (CGeoObj*)ptr;
}	// CreateTriasObjekt

///////////////////////////////////////////////////////////////////////
//	CErrStream

CErrStream :: CErrStream( const char* filename )
: ofstream( filename )
{}


CErrStream :: ~CErrStream()
{}


///////////////////////////////////////////////////////////////////////
//	diverse Zugriffsfunktionen

/*-------------------------------------------------------------------
	SatzKoerper
	  >	InfoName
		  >	AuftragsKennSatz
			| IBENKRT
			| ULOTEX
			| ObjektDaten
			| AttributSatz
			| ULBENFOL
			| ULBENGEO
			| ULBENOBJ
			| Space_8     // EndeSatz

	AuftragsKennSatz
	  >	INT4
	  >	TEXT    //  1. DST
	  >	TEXT    //  2. 9xSpace
	  > TEXT    //  3. ANR
	  >	TEXT    //  4. DLQA0003
	  >	TEXT    //  5. DLQA1000
	  >	TEXT    //  6. ATA
	  >	TEXT    //  7. DLQA3000
	  >	TEXT    //  8. DLQA4000
	  >	TEXT    //  9. BGD
	  >	TEXT    // 10. ATH
	  >	TEXT    // 11. ATK
	  >	TEXT    // 12. FFA
	  >	TEXT    // 13. TXT
	  >	TEXT    // 14. UEM
	  >	TEXT    // 15. AZA
	  >	TEXT    // 16. Inhalt
	  >	TEXT    // 17. DLQA8006
	  >	TEXT    // 18. DLQA8007
	  >	TEXT    // 19. DLQA8008
	  >	TEXT    // 20. DLQA8009
	  >	TEXT    // 21. DLQA800A
	  >	TEXT    // 22. MSA
	  >	TEXT    // 23. VHW
	  >	TEXT    // 24. DLQA9001
	  > TEXT    // 25. DLQA9002
	  > TEXT    // 26. DLQA9003
	  > TEXT    // 27. DLQAA000
	  > TEXT    // 28. DLQAB000
	  > TEXT    // 29. DLQAC001
	  > TEXT    // 30. DLQAC002
	  > TEXT    // 31. DLQAC003
	  > TEXT    // 32. ZSP
	  > TEXT    // 33. DLQAF000
	  > TEXT    // 34. DLQAG000
	  > TEXT    // 35. LTE
	  > TEXT    // 36. FPE
	  > TEXT    // 37. LTK
	  > TEXT    // 38. FPV
	  > TEXT    // 39. DLQAK000
	  > TEXT    // 40. DLQAL000
	  > TEXT    // 41. ATR

	ObjektDaten
	  > GrundrissKennDaten
	  >	( whf0 INT4
		  | Linien )
	  >	( D0 D0
		  Objekte+
		  STOP )?

	AttributSatz
	  > TEXT	// ObjektNummer
	  > TEXT	// ObjektteilNummer
	  > TEXT	// Prüfzeichen/Aktualität
	  > ( whf0 |
	      Attribute )

	Attribute
	  > whf_n
	  > TEXT	// Attribute (whf_n)

	GrundrissKennDaten
	  >	Koordi
	  >	TEXT	// Pruefzeichen

	Linien
	  >	whf_n
	  >	D0
	  >	Linie*
	  >	STOP
	  >	I4

	Linie
	  >	D0
	  >	D0
	  >	D1
	  >	Koordi
	  >	TEXT    // Art der Geometrie
	  >	( whf0 | Fktparam )
	  >	I4
	  >	Lageparam

	Fktparam
	  >	whf_n
	  >	Funktion*
	  >	STOP

	Funktion
	  >	whf1
	  >	TEXT        // Folie
	  >	TEXT        // ObjArt
	  >	TEXT        // ObjNummer 1
	  >	TEXT        // ObjNummer 2
	  >	TEXT        // ObjTeilNr 1
	  >	TEXT        // ObjTeilNr 2
	  >	TEXT        // LinienTeilung 1
	  >	TEXT        // LinienTeilung 2
	  >	( whf0 | Fachparam )

	Fachparam
	  >	whf_n
	  >	TEXT        // Art
	  >	TEXT        // Kennung
	  >	TEXT        // Wert

	Lageparam
	  >	( Koord | Koordi | Fortsetzung )*
	  >	STOP

	Fortsetzung
	  >	NL
	  >	TEXT

	Objekte
	  >	D0
	  >	D1
	  >	ObjFunktion
	  >	LOOK
	  >	( LOOK_0 | LOOK_N BesondInfo* )

	ObjFunktion
	  >	TEXT    // Folie
	  >	TEXT    // Objektart
	  >	TEXT    // Aktualität des Objektes
	  >	TEXT    // Objekttyp
	  >	TEXT    // Objektnummer
	  >	TEXT    // Modelltyp
	  >	TEXT    // Entstehungsdatum
	  >	TEXT    // Veränderungskennung

	BesondInfo
	  >	whf_n
	  >	TEXT    // Art der Information
	  >	TEXT    // Kartentyp
	  >	TEXT    // Objektart
	  >	TEXT    // Text
	  >	TEXT    // Art der Geometrieangabe
	  >	TEXT    // Objektteilnummer
	  >	LOOK
	  >	( LOOK_0 | GeometrieAngaben )

	GeometrieAngaben
	  >	LOOK_N
	  >	KoordinatenPaar

  -------------------------------------------------------------------*/

void Kommentar( const char* txt, const DWORD j )
{
#ifdef	_ENABLE_KOMMENTAR_
	if( pLogStream )
		if ( j <= g_iLogLevel ) cout << txt;
#endif
}


void Kommentar( int i, const DWORD j )
{
#ifdef	_ENABLE_KOMMENTAR_
	if( pLogStream )
		if ( j <= g_iLogLevel ) cout << i;
#endif
}


void Kommentar( long i, const DWORD j )
{
#ifdef	_ENABLE_KOMMENTAR_
	if( pLogStream )
		if ( j <= g_iLogLevel ) cout << i;
#endif
}


void Kommentar( double i, const DWORD j )
{
#ifdef	_ENABLE_KOMMENTAR_
	if( pLogStream )
		if ( j <= g_iLogLevel ) cout << i;
#endif
}


void Kommentar( char c, const DWORD j )
{
#ifdef	_ENABLE_KOMMENTAR_
	if( pLogStream )
		if ( j <= g_iLogLevel ) cout << "'" << c << "'";
#endif
}


void Meldung( const char* txt )
{
	if( pLogStream )
		cout << txt;
}


void Meldung( int i )
{
	if( pLogStream )
		cout << i;
}


void Meldung( long i )
{	
	if( pLogStream )
		cout << i;
}


void Meldung( double i )
{
	if( pLogStream )
		cout << i;
}


void KommNL( const char* txt, const DWORD j )
{
#ifdef	_ENABLE_KOMMENTAR_
	if( pLogStream )
		if ( j <= g_iLogLevel ) cout << txt << "\n";
#endif
}


void KommNL( int i, const DWORD j )
{
#ifdef	_ENABLE_KOMMENTAR_
	if( pLogStream )
		if ( j <= g_iLogLevel ) cout << i << "\n";
#endif
}


void KommNL( long i, const DWORD j )
{
#ifdef	_ENABLE_KOMMENTAR_
	if( pLogStream )
		if ( j <= g_iLogLevel ) cout << i << "\n";
#endif
}


void KommNL( double i, const DWORD j )
{
#ifdef	_ENABLE_KOMMENTAR_
	if( pLogStream )
		if ( j <= g_iLogLevel ) cout << i << "\n";
#endif
}


void KommNL( char c, const DWORD j )
{
#ifdef	_ENABLE_KOMMENTAR_
	if( pLogStream )
		if ( j <= g_iLogLevel ) cout << "'" << c << "'" << "\n";
#endif
}


void MeldNL( const char* txt )
{
	if( pLogStream )
		cout << txt << "\n";
}


void MeldNL( int i )
{
	if( pLogStream )
		cout << i << "\n";
}


void MeldNL( long i )
{
	if( pLogStream )
		cout << i << "\n";
}


int Trimm( CString& Str )
{	while (( Str.GetLength()) &&
	       ( Str.GetAt( Str.GetLength() - 1 ) == ' ' )) Str = Str.Left( Str.GetLength() - 1 );
	return Str.GetLength();
}


int LTrimm( CString& Str )
{	while (( Str.GetLength()) &&
		   ( Str[0] == ' ' )) Str = Str.Right( Str.GetLength() - 1 );
	return Str.GetLength();
}


/*
void AllTrimm( CString& Str )
{
	Str.TrimLeft(); Str.TrimRight();
}
*/


BOOL CImportEDBS::GeometrieSaved()
{
	return m_bDataSaved;
}

void CImportEDBS::SaveData( void* pvSatz )
{
	CAtkisSatz*		pSatz = (CAtkisSatz*)pvSatz;
	int				i, l;
	CxString			txt, txt1, txt2, txt3;

	FreeSavedData();

	if ( pSatz -> AnzahlLinien() > 1 )
	{
		KommNL( "**************** !!! Fehler! Mehrere Linie im Fortsetzungssatz! Fehler!!! ************", 1 );
	}
	i = 0;

	for ( l = 0; l < pSatz -> NumFktParam( i ); l++ ) {
		txt2 = pSatz -> ObjektNummerRechts( i, l );
		txt2.TrimAll();
		if ( txt2.GetLength()) {
			Kommentar( "*   Objekt Rechts = ", 3 );
				Kommentar( pSatz -> ObjektNummerRechts( i, l ), 3 );
			Kommentar( "-", 3 );
				Kommentar( pSatz -> ObjektteilNummerRechts( i, l ), 3 );
			Kommentar( "  Teilung: ", 3 );
				Kommentar( pSatz -> LinienTeilungRechts( i, l ), 3 );
			Kommentar( "  Folie: ", 3 );
				Kommentar( pSatz -> Folie( i, l ), 3 );
			Kommentar( "  Art: ", 3 );
				KommNL( pSatz -> ObjektArt( i, l ), 3 );
		}
		txt2 = pSatz -> ObjektNummerLinks( i, l );
		txt2.TrimAll();
		if(pSatz -> ObjektNummerLinks( i, l ) == "   0005")
			i=i;
		if ( txt2.GetLength()) {
			Kommentar( "*   Objekt Links  = ", 3 );
				Kommentar( pSatz -> ObjektNummerLinks( i, l ), 3 );
			Kommentar( "-", 3 );
				Kommentar( pSatz -> ObjektteilNummerLinks( i, l ), 3 );
			Kommentar( "  Teilung: ", 3 );
				Kommentar( pSatz -> LinienTeilungLinks( i, l ), 3 );
			Kommentar( "  Folie: ", 3 );
				Kommentar( pSatz -> Folie( i, l ), 3 );
			Kommentar( "  Art: ", 3 );
				KommNL( pSatz -> ObjektArt( i, l ), 3 );
		}	
	}

	for ( l = 0; l < pSatz -> NumFktParam( i ); l++ ) {
		txt2 = pSatz -> Folie( i, l );
		txt2.TrimAll();
		txt3 = pSatz -> ObjektArt( i, l );
		txt3.TrimAll();
		txt = pSatz -> ObjektNummerRechts( i, l );
		txt1 = pSatz -> ObjektteilNummerRechts( i, l );
		txt.TrimAll();
		txt1.TrimAll();
		if ( txt.GetLength()) {
			m_strarrTxt.Add( txt );
			m_strarrTxt1.Add( txt1 );
			m_strarrTxt2.Add( txt2 );
			m_strarrTxt3.Add( txt3 );
		}

		txt = pSatz -> ObjektNummerLinks( i, l );
		txt1 = pSatz -> ObjektteilNummerLinks( i, l );
		txt.TrimAll();
		txt1.TrimAll();
		if ( txt.GetLength()) {
			m_strarrTxt.Add( txt );
			m_strarrTxt1.Add( txt1 );
			m_strarrTxt2.Add( txt2 );
			m_strarrTxt3.Add( txt3 );
		}	
	}

	m_pktStart = new CPunkt( pSatz -> GrundPunktHoch(), pSatz -> GrundPunktRechts());
	m_pktEnd = new CPunkt( pSatz -> EndPunktHoch( i ), pSatz -> EndPunktRechts( i ));

	m_bDataSaved = TRUE;
	m_bSavedDataUsed = FALSE;
}

void CImportEDBS::FreeSavedData()
{
	m_strarrTxt.RemoveAll();
	m_strarrTxt1.RemoveAll();
	m_strarrTxt2.RemoveAll();
	m_strarrTxt3.RemoveAll();
	if ( m_pktStart != NULL )	delete m_pktStart;
	if ( m_pktEnd != NULL )		delete m_pktEnd;
	m_pktStart = NULL;
	m_pktEnd = NULL;
	m_bDataSaved = FALSE;
}

void CImportEDBS::SavedGeoDataEinordnen( void* pvSatz, int i )
{
	CAtkisSatz*		pSatz = (CAtkisSatz*)pvSatz;
	int				iAnzahlPunkte, l, offs;
	CPunktFolge*	pPF;
	CString			txt, txt1, txt2, txt3;

	iAnzahlPunkte = pSatz -> AnzahlPunkte( i );
	offs = 1;
	if ( atoi( pSatz -> ArtGeometrie( i )) == _Kurve ) {
		iAnzahlPunkte -= 1;
		offs = 0;
		switch ( pSatz -> SplineKennung( i )) {
		case '2':
			offs = -2;
			iAnzahlPunkte -= 2;
			break;
		case '3':
			iAnzahlPunkte -= 2;
			break;
		case '4':
			offs = -2;
			iAnzahlPunkte -= 4;
			break;
		}
	}

	pPF = new CPunktFolge( iAnzahlPunkte + 2 );

	(*pPF)[0] = new CPunkt( pSatz -> GrundPunktHoch(), pSatz -> GrundPunktRechts());
	(*pPF)[iAnzahlPunkte + 1] = new CPunkt( pSatz -> EndPunktHoch( i ), pSatz -> EndPunktRechts( i ));

	Kommentar( "Start ", 3 ); Kommentar( pSatz -> GrundPunktHoch(), 3 );
		Kommentar( " : ", 3 ); KommNL( pSatz -> GrundPunktRechts(), 3 );

	for ( l = 1; l <= iAnzahlPunkte; l++ ) {
		(*pPF)[l] = new CPunkt( pSatz -> LinienPunktHoch( i, l-offs ),
								pSatz -> LinienPunktRechts( i, l-offs ));
		Kommentar( "Punkt  ", 3 ); Kommentar( pSatz -> LinienPunktHoch( i, l-offs ), 3 );
			Kommentar( " : ", 3 ); KommNL( pSatz -> LinienPunktRechts( i, l-offs ), 3 );
	}

	Kommentar( "Ende  ", 3 ); Kommentar( pSatz -> EndPunktHoch( i ), 3 );
		Kommentar( " : ", 3 ); KommNL( pSatz -> EndPunktRechts( i ), 3 );

	for ( l = 0; l < m_strarrTxt.GetSize(); l++ ) {
		txt = m_strarrTxt[l];
		txt1 = m_strarrTxt1[l];
		txt2 = m_strarrTxt2[l];
		txt3 = m_strarrTxt3[l];
		if ( txt.GetLength()) {
			g_pObjektPool -> AddLine( txt, pPF, NULL, txt1, txt2, txt3 );
			g_pObjektPool -> Fertig();
		}
	}

	delete pPF;		// CPunkt-Einträge werden automatisch gelöscht!
}

void CImportEDBS::GeoDataEinordnen( void* pvSatz, int i )
{
	CAtkisSatz*		pSatz = (CAtkisSatz*)pvSatz;
	int				l;
	CGeometry*		pG = NULL;
	CPunktFolge*	pPF = NULL;
	CxString			txt, txt1, txt2, txt3, txt4;


	for ( l = 0; l < pSatz -> NumFktParam( i ); l++ ) {
		txt2 = pSatz -> ObjektNummerRechts( i, l );
		txt2.TrimAll();
		if ( txt2.GetLength()) {
			Kommentar( "    Objekt Rechts = ", 3 );
				Kommentar( pSatz -> ObjektNummerRechts( i, l ), 3 );
			Kommentar( "-", 3 );
				Kommentar( pSatz -> ObjektteilNummerRechts( i, l ), 3 );
			Kommentar( "  Teilung: ", 3 );
				Kommentar( pSatz -> LinienTeilungRechts( i, l ), 3 );
			Kommentar( "  Folie: ", 3 );
				Kommentar( pSatz -> Folie( i, l ), 3 );
			Kommentar( "  Art: ", 3 );
				KommNL( pSatz -> ObjektArt( i, l ), 3 );
		}
		txt2 = pSatz -> ObjektNummerLinks( i, l );
		txt2.TrimAll();
		if ( txt2.GetLength()) {
			Kommentar( "    Objekt Links  = ", 3 );
				Kommentar( pSatz -> ObjektNummerLinks( i, l ), 3 );
			Kommentar( "-", 3 );
				Kommentar( pSatz -> ObjektteilNummerLinks( i, l ), 3 );
			Kommentar( "  Teilung: ", 3 );
				Kommentar( pSatz -> LinienTeilungLinks( i, l ), 3 );
			Kommentar( "  Folie: ", 3 );
				Kommentar( pSatz -> Folie( i, l ), 3 );
			Kommentar( "  Art: ", 3 );
				KommNL( pSatz -> ObjektArt( i, l ), 3 );
		}
	}

	int iAnzahlPunkte = pSatz -> AnzahlPunkte( i );

	switch ( atoi( pSatz -> ArtGeometrie( i ))) {
	case _Gerade:
		if( iAnzahlPunkte != 0 )
			iAnzahlPunkte = iAnzahlPunkte;
		pPF = new CPunktFolge( iAnzahlPunkte + 2 );

		(*pPF)[0] = new CPunkt( pSatz -> GrundPunktHoch(), pSatz -> GrundPunktRechts());
		(*pPF)[iAnzahlPunkte + 1] = new CPunkt( pSatz -> EndPunktHoch( i ), pSatz -> EndPunktRechts( i ));

		for ( l = 1; l <= iAnzahlPunkte; l++ ) {
			(*pPF)[l] = new CPunkt( pSatz -> LinienPunktHoch( i, l-1 ),
										pSatz -> LinienPunktRechts( i, l-1 ));
		}
		break;
	case _Polygonzug:
		if( iAnzahlPunkte == 0 )
			iAnzahlPunkte = iAnzahlPunkte;
		pPF = new CPunktFolge( iAnzahlPunkte + 2 );

		(*pPF)[0] = new CPunkt( pSatz -> GrundPunktHoch(), pSatz -> GrundPunktRechts());
		(*pPF)[iAnzahlPunkte + 1] = new CPunkt( pSatz -> EndPunktHoch( i ), pSatz -> EndPunktRechts( i ));
		for ( l = 1; l <= iAnzahlPunkte; l++ ) {
			(*pPF)[l] = new CPunkt( pSatz -> LinienPunktHoch( i, l-1 ),
										pSatz -> LinienPunktRechts( i, l-1 ));
		}
		break;
	case _Kreisbogen_rechts:
		if( iAnzahlPunkte == 1 ) {
			SAFEARRAY *psa = NULL;
			ConvertArc1(
					pSatz -> EndPunktHoch( i ), pSatz -> EndPunktRechts( i ),
					pSatz -> LinienPunktHoch( i, 0 ),	pSatz -> LinienPunktRechts( i, 0 ),
					pSatz -> GrundPunktHoch(), pSatz -> GrundPunktRechts(),
					&psa );
/*			if( !g_pIArcConversion ) {
				if (FAILED(CoCreateInstance( CLSID_ArcConversion, NULL, CLSCTX_LOCAL_SERVER, IID_IArcConversion, (LPVOID *)&g_pIArcConversion )))
					break;
				g_pIArcConversion->put_Anisotropy( 1.0 );
				g_pIArcConversion->put_Precision( g_pMetaData->dArcPrecision );
			}
			if (FAILED(g_pIArcConversion -> Convert1(
					pSatz -> EndPunktHoch( i ), pSatz -> EndPunktRechts( i ),
					pSatz -> LinienPunktHoch( i, 0 ),	pSatz -> LinienPunktRechts( i, 0 ),
					pSatz -> GrundPunktHoch(), pSatz -> GrundPunktRechts(),
					&psa )))
			break;

			CArcConversion cvt;
			cvt.put_Anisotropy( 1.0 );
			cvt.put_Precision( g_pMetaData->dArcPrecision );
			cvt.Convert1(
					pSatz -> EndPunktHoch( i ), pSatz -> EndPunktRechts( i ),
					pSatz -> LinienPunktHoch( i, 0 ),	pSatz -> LinienPunktRechts( i, 0 ),
					pSatz -> GrundPunktHoch(), pSatz -> GrundPunktRechts(),
					&psa );
*/			
			if( psa ) {
				iAnzahlPunkte = psa->rgsabound[0].cElements / 2;
				if( iAnzahlPunkte > 0 ) {
					pPF = new CPunktFolge( iAnzahlPunkte );
					do {
						--iAnzahlPunkte;
							(*pPF)[iAnzahlPunkte] = new CPunkt( *(((double*)psa->pvData) + iAnzahlPunkte*2), *(((double*)psa->pvData) + iAnzahlPunkte*2 + 1) );
					} while( iAnzahlPunkte > 0);
				}
				SafeArrayDestroy( psa );
				psa = NULL;
			}
		}
		else {	//Korrektur für Kreise aus zwei Punkten
			pPF = new CPunktFolge( 2 );

			(*pPF)[0] = new CPunkt( pSatz -> GrundPunktHoch(), pSatz -> GrundPunktRechts());
			(*pPF)[1] = new CPunkt( pSatz -> EndPunktHoch( i ), pSatz -> EndPunktRechts( i ));
		}
		break;
	case _Kreisbogen_links:
		if( iAnzahlPunkte == 1 ) {
			SAFEARRAY *psa = NULL;
			ConvertArc1(
					pSatz -> GrundPunktHoch(), pSatz -> GrundPunktRechts(),
					pSatz -> LinienPunktHoch( i, 0 ),	pSatz -> LinienPunktRechts( i, 0 ),
					pSatz -> EndPunktHoch( i ), pSatz -> EndPunktRechts( i ),
					&psa );
/*			if( !g_pIArcConversion ) {
				if (FAILED(CoCreateInstance( CLSID_ArcConversion, NULL, CLSCTX_INPROC_SERVER, IID_IArcConversion, (LPVOID *)&g_pIArcConversion )))
					break;
				g_pIArcConversion->put_Anisotropy( 1.0 );
				g_pIArcConversion->put_Precision( g_pMetaData->dArcPrecision );
			}
			if (FAILED(g_pIArcConversion -> Convert1(
					pSatz -> GrundPunktHoch(), pSatz -> GrundPunktRechts(),
					pSatz -> LinienPunktHoch( i, 0 ),	pSatz -> LinienPunktRechts( i, 0 ),
					pSatz -> EndPunktHoch( i ), pSatz -> EndPunktRechts( i ),
					&psa )))
				break;

			CArcConversion cvt;
			cvt.put_Anisotropy( 1.0 );
			cvt.put_Precision( g_pMetaData->dArcPrecision );
			cvt.Convert1(
					pSatz -> GrundPunktHoch(), pSatz -> GrundPunktRechts(),
					pSatz -> LinienPunktHoch( i, 0 ),	pSatz -> LinienPunktRechts( i, 0 ),
					pSatz -> EndPunktHoch( i ), pSatz -> EndPunktRechts( i ),
					&psa );
*/
			if( psa ) {
				iAnzahlPunkte = psa->rgsabound[0].cElements / 2;
				if( iAnzahlPunkte > 0 ) {
					pPF = new CPunktFolge( iAnzahlPunkte );
					do {
						--iAnzahlPunkte;
						(*pPF)[iAnzahlPunkte] = new CPunkt( *(((double*)psa->pvData) + iAnzahlPunkte*2), *(((double*)psa->pvData) + iAnzahlPunkte*2 + 1) );
					} while( iAnzahlPunkte > 0);
				}
				SafeArrayDestroy( psa );
				psa = NULL;
			}
		}
		else {	//Korrektur für Kreise aus zwei Punkten
			pPF = new CPunktFolge( 2 );

			(*pPF)[0] = new CPunkt( pSatz -> GrundPunktHoch(), pSatz -> GrundPunktRechts());
			(*pPF)[1] = new CPunkt( pSatz -> EndPunktHoch( i ), pSatz -> EndPunktRechts( i ));
		}
		break;
	case _Kurve:
		iAnzahlPunkte = 0;
		pPF = new CPunktFolge( iAnzahlPunkte + 2 );
		(*pPF)[0] = new CPunkt( pSatz -> GrundPunktHoch(), pSatz -> GrundPunktRechts());
		(*pPF)[iAnzahlPunkte + 1] = new CPunkt( pSatz -> EndPunktHoch( i ), pSatz -> EndPunktRechts( i ));
		break;
	default:
		_ASSERT( 0 == "Unbearbeiteter Geometrietyp" );
		break;
	}

	Kommentar( "Start ", 3 ); Kommentar( pSatz -> GrundPunktHoch(), 3 );
		Kommentar( " : ", 3 ); KommNL( pSatz -> GrundPunktRechts(), 3 );

//	(*pPF)[0] = new CPunkt( pSatz -> GrundPunktHoch(), pSatz -> GrundPunktRechts());
//	(*pPF)[iAnzahlPunkte + 1] = new CPunkt( pSatz -> EndPunktHoch( i ), pSatz -> EndPunktRechts( i ));

	for ( l = 1; l <= iAnzahlPunkte; l++ ) {
//		(*pPF)[l] = new CPunkt( pSatz -> LinienPunktHoch( i, l-1 ),
//								pSatz -> LinienPunktRechts( i, l-1 ));
		Kommentar( "Punkt  ", 3 ); Kommentar( pSatz -> LinienPunktHoch( i, l-1 ), 3 );
			Kommentar( " : ", 3 ); KommNL( pSatz -> LinienPunktRechts( i, l-1 ), 3 );
	}

	Kommentar( "Ende  ", 3 ); Kommentar( pSatz -> EndPunktHoch( i ), 3 );
		Kommentar( " : ", 3 ); KommNL( pSatz -> EndPunktRechts( i ), 3 );

	if ( NULL != pPF ) {
		for ( l = 0; l < pSatz -> NumFktParam( i ); l++ ) {
			txt2 = pSatz -> Folie( i, l );
			txt2.TrimAll();
			txt3 = pSatz -> ObjektArt( i, l );
			txt3.TrimAll();
			txt = pSatz -> ObjektNummerRechts( i, l );
			txt1 = pSatz -> ObjektteilNummerRechts( i, l );
			txt.TrimAll();
			txt1.TrimAll();
			if ( txt.GetLength() > 0 ) {
				g_pObjektPool -> AddLine( pSatz -> ObjektNummerRechts( i, l ), pPF, NULL, txt1, txt2, txt3 );
				g_pObjektPool -> Fertig();
			}

			txt = pSatz -> ObjektNummerLinks( i, l );
			txt1 = pSatz -> ObjektteilNummerLinks( i, l );
			txt.TrimAll();
			txt1.TrimAll();
			if ( txt.GetLength() > 0) {
				g_pObjektPool -> AddLine( pSatz -> ObjektNummerLinks( i, l ), pPF, NULL, txt1, txt2, txt3 );
				g_pObjektPool -> Fertig();
			}
		}

		delete pPF;		// CPunkt-Einträge werden automatisch gelöscht!
	}
}
