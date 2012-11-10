#include "StdAfx.h"

#include "iostream.h"
#include "fstream.h"
#include "fltMosaic.h"
#include "MapMosaic.h"

#include <io.h>			// _access

BOOL g_bCheckOnly = FALSE;

static void usage() {
	fprintf( stderr, 
		"Usage: MapMosaic [Initoptions outfile] [Composeoptions infile outfile]\n"
		"where Options are:\n"
		"(1) Initoptions:\n"
		"    -i cols;rows\n"
		"         initialize (create an empty) Picture with cols x rows\n"
		"    -P Palettefile\n"
		"         use (Photostyler-) Palettefile as Palettetemplate\n"
		"         (if -P not given, MapMosaic will create a default 6-6-6 Palette\n"
		"\n"
		"(2) Composeoptions:\n"
		"    -R x0;y0;x1;y1;x2;y2;x3;y3\n"
		"         determines the corner coordinates for the input picture\n"
		"    -C x0;y0;x1;y1;x2;y2;x3;y3\n"
		"         determines the clip points for the input picture\n"
		"    -O col0;row0;nCols;nRows\n"
		"         determines the layout - position for the output - picture\n"
		"\n"
		"   Example:\n"
		"\n"
		"  R0 +----------------------+ R1         +---------------------------+\n"
		"     | C0 +                 |            |                           |\n"
		"     |                  + C1|            |   O0              O1      |\n"
		"     |                      |            |    +--------------+       |\n"
		"     |                      |            |    |              |       |\n"
		"     |                      |            |    |              |       |\n"
		"     |                      |   =====>   |    |              |       |\n"
		"     |                      |            |    |              |       |\n"
		"     |                      |            |    |              |       |\n"
		"     |                      |            |    |              |       |\n"
		"     | C3 +                 |            |    +--------------+       |\n"
		"     |                + C2  |            |   O3              O2      |\n"
		"  R3 +----------------------+ R2         +---------------------------+\n"
		"\n"
		"(3) other Options:\n"
		"    -?               print this help\n"
		"    -f Commandfile   read Composeoptions -R, -C, -O from Commandfile\n"
		"    -p Protocolfile  Write debug output to Protocolfile\n"
		"\n"
		);
}

BOOL Process( CFile *pSrcFile, CFile *pDstFile, PICTMOSAICPARAM& rParam, ostream *protStream );

static void GetOption( int opt, LPCTSTR optarg, PICTMOSAICPARAM *cPar ) {
	CString	S;

	switch( opt ) {
	case 'R' :
		::AfxExtractSubString( S, optarg, 0, ';' ); cPar->m_Ref[0].x = atof( S );
		::AfxExtractSubString( S, optarg, 1, ';' ); cPar->m_Ref[0].y = atof( S );
		::AfxExtractSubString( S, optarg, 2, ';' ); cPar->m_Ref[1].x = atof( S );
		::AfxExtractSubString( S, optarg, 3, ';' ); cPar->m_Ref[1].y = atof( S );
		::AfxExtractSubString( S, optarg, 4, ';' ); cPar->m_Ref[2].x = atof( S );
		::AfxExtractSubString( S, optarg, 5, ';' ); cPar->m_Ref[2].y = atof( S );
		::AfxExtractSubString( S, optarg, 6, ';' ); cPar->m_Ref[3].x = atof( S );
		::AfxExtractSubString( S, optarg, 7, ';' ); cPar->m_Ref[3].y = atof( S );
		break;
	case 'C' :
		::AfxExtractSubString( S, optarg, 0, ';' ); cPar->m_Clip[0].x = atof( S );
		::AfxExtractSubString( S, optarg, 1, ';' ); cPar->m_Clip[0].y = atof( S );
		::AfxExtractSubString( S, optarg, 2, ';' ); cPar->m_Clip[1].x = atof( S );
		::AfxExtractSubString( S, optarg, 3, ';' ); cPar->m_Clip[1].y = atof( S );
		::AfxExtractSubString( S, optarg, 4, ';' ); cPar->m_Clip[2].x = atof( S );
		::AfxExtractSubString( S, optarg, 5, ';' ); cPar->m_Clip[2].y = atof( S );
		::AfxExtractSubString( S, optarg, 6, ';' ); cPar->m_Clip[3].x = atof( S );
		::AfxExtractSubString( S, optarg, 7, ';' ); cPar->m_Clip[3].y = atof( S );
		break;
	case 'O' :
		::AfxExtractSubString( S, optarg, 0, ';' ); cPar->m_rcDst.left = atol( S );
		::AfxExtractSubString( S, optarg, 1, ';' ); cPar->m_rcDst.top = atol( S );
		::AfxExtractSubString( S, optarg, 2, ';' ); cPar->m_rcDst.right = atol( S );
		::AfxExtractSubString( S, optarg, 3, ';' ); cPar->m_rcDst.bottom = atol( S );
		break;
	}
}

static void ReadClut( LPRGBQUAD pClut, LPCTSTR lpszFile ) {
	CStdioFile f( lpszFile, CFile::modeRead );
	CString	S, S1;
	int nColors = 256, i = 0;

	f.ReadString( S );
	if( "CWPAL" == S ) {
		f.ReadString( S );
		f.ReadString( S );
		nColors = atoi( S );
	}
	if( nColors > 256 )
		return;
	for( i = 0; i < nColors && f.ReadString( S ); i++ ) {
		pClut[i].rgbReserved = 0;
		::AfxExtractSubString( S1, S, 0, ' ' ); pClut[i].rgbRed   = atoi( S1 );
		::AfxExtractSubString( S1, S, 1, ' ' ); pClut[i].rgbGreen = atoi( S1 );
		::AfxExtractSubString( S1, S, 2, ' ' ); pClut[i].rgbBlue  = atoi( S1 );
	}
}

static void CreateDefaultClut( LPRGBQUAD pClut ) {
}

void main( int argc, LPCTSTR *argv ) {
	int		c;
	LPCTSTR	optarg;
	int		optind = 1;

	PICTMOSAICPARAM	cPar;
	INIT_FILTERSTRUCT( &cPar, CPictMosaic );

	CString		strSrcFile;
	CString		strDstFile;
	CString		strOptFile;
	CString		strPalFile;

	fstream		fProt;
	ostream	*pstr;
#ifdef _DEBUG
	pstr = &cout;
#else
	pstr = NULL;
#endif

	CString	S, S1;
	BOOL	bInitializeOnly = FALSE;

	while( EOF != ( c = getopt( argc, argv, "i:P:R:C:O:p:f:?", optind, optarg ) ) ) {
		switch( c ) {
		case 'i' :
			bInitializeOnly = TRUE;
			::AfxExtractSubString( S, optarg, 0, ';' ); cPar.m_rcDst.right = atol(S);
			::AfxExtractSubString( S, optarg, 1, ';' ); cPar.m_rcDst.bottom = atol(S);
			break;
		case 'R' :
		case 'C' :
		case 'O' :
			GetOption( c, optarg, &cPar );
			break;
		case 'P' :
			strPalFile = optarg;
			break;
		case 'p' :
			fProt.open( optarg, ios::out );
			if( fProt.good() )
				pstr = &fProt;
			break;
		case 'f' :
			strOptFile = optarg;
			break;
		case '?' :
			usage();
			exit( 2 );
			break;
		}
	}

	if( argc == optind ) {
		usage();
		return;
	}
	if( !strOptFile.IsEmpty() ) {
		CStdioFile	f( strOptFile, CFile::modeRead | CFile::typeText );
		while( f.ReadString( S ) ) {
			::AfxExtractSubString( S1, S, 1, ' ' );
			GetOption( S[1], S1, &cPar );
		}
	}

#define	W_MODE	CFile::modeReadWrite | CFile::typeBinary
#define C_MODE	W_MODE | CFile::modeCreate
#define	R_MODE	CFile::modeRead | CFile::typeBinary

	////////////////////////////////////////////////////////////////////
	// exit - Status:
	//
	//	0 - OK
	//	1 - Quelldatei kann nicht geöffnet werden
	//	2 - Zieldatei kann nicht geöffnet werden
	//	3 - Fehler im Quellbild
	//	4 - Fehler im Zielbild

	CFile			srcFile, dstFile;
	CPictMosaic		pictCopy;
	CRuntimeClass	*pRTSrc, *pRTDst;
	CPicture		*pSrc, *pDst;

	if( bInitializeOnly ) {
		strDstFile = argv[optind++];
		RGBQUAD	clut[256];
		if( !strPalFile.IsEmpty() )
			ReadClut( clut, strPalFile );
		else
			CreateDefaultClut( clut );
		if( !dstFile.Open( strDstFile, C_MODE ) )
			exit( 2 );
		VERIFY( pDst = (CPicture*) RUNTIME_CLASS( CTifPicture )->CreateObject() );
		pDst->Attach( &dstFile );
		TRY {
			CRect	rcCore(0,0,0,0), rcPict = cPar.m_rcDst;
			pDst->SetColorspace( PICT_COLOR_PALETTE );
			pDst->SetCompression( PICT_COMPR_NOCOMPR );
			pDst->SetPictRect( rcPict );
			pDst->SetCoreRect( pDst->GetBestCorePictRect() );
			rcCore = pDst->GetCorePictRect();
			if( PICT_ORIENT_LOWERLEFT == pDst->GetOrientation() ) {
				rcPict = pDst->GetPictRect();
				long	off = rcPict.Height() - rcCore.Height();
				rcCore.OffsetRect( 0, off );
			}
			pDst->SetClut( clut );
			pDst->WriteHeader();
			while( rcCore.top < rcPict.bottom ) {
				pDst->SetCoreRect( rcCore );
				pDst->Write( rcCore );
				rcCore.OffsetRect( 0, rcCore.Height() );
				if( rcCore.bottom > rcPict.bottom ) 
					rcCore.bottom = rcPict.bottom;
				rcCore.bottom = min( rcCore.bottom, rcPict.bottom );
			}
			pDst->WriteTrailer();
		} CATCH( CPictException, e ) {
			lpictdll::ReportPictException( e );
			DELETE_EXCEPTION( e );
		} END_CATCH
		pDst->Detach();
		delete pDst;
		dstFile.Close();
	} else {
		strSrcFile = argv[optind++];
		strDstFile = argv[optind++];

		//////////////////////////////////////////////////////
		// Clippunkte und Referenzpunkte in (0,0) verschieben

		cPar.m_Clip[0].x -= cPar.m_Ref[3].x; cPar.m_Clip[0].y -= cPar.m_Ref[3].y;
		cPar.m_Clip[1].x -= cPar.m_Ref[3].x; cPar.m_Clip[1].y -= cPar.m_Ref[3].y;
		cPar.m_Clip[2].x -= cPar.m_Ref[3].x; cPar.m_Clip[2].y -= cPar.m_Ref[3].y;
		cPar.m_Clip[3].x -= cPar.m_Ref[3].x; cPar.m_Clip[3].y -= cPar.m_Ref[3].y;

		cPar.m_Ref[0].x -= cPar.m_Ref[3].x; cPar.m_Ref[0].y -= cPar.m_Ref[3].y;
		cPar.m_Ref[1].x -= cPar.m_Ref[3].x; cPar.m_Ref[1].y -= cPar.m_Ref[3].y;
		cPar.m_Ref[2].x -= cPar.m_Ref[3].x; cPar.m_Ref[2].y -= cPar.m_Ref[3].y;
		cPar.m_Ref[3].x -= cPar.m_Ref[3].x; cPar.m_Ref[3].y -= cPar.m_Ref[3].y;

		CTime	tStart, tEnd;

		if( srcFile.Open( strSrcFile, R_MODE ) ) {
			if( dstFile.Open( strDstFile, 0 == _access( strDstFile, 04 ) ? W_MODE : C_MODE ) ) {
				if( NULL != ( pRTSrc = GetPictureType( &srcFile ) ) ) {
					VERIFY( pSrc = (CPicture*) pRTSrc->CreateObject() );
					VERIFY( pSrc->Attach( &srcFile ) );
					VERIFY( pSrc->ReadHeader( ) );

					if( NULL != ( pRTDst = GetPictureType( &dstFile ) ) ) {
						VERIFY( pDst = (CPicture*) pRTDst->CreateObject() );
						VERIFY( pDst->Attach( &dstFile ) );
						VERIFY( pDst->ReadHeader( ) );

						if( pstr ) {
							tStart = CTime::GetCurrentTime();
							*pstr << "Start processing at: " << tStart.Format( "%H:%M:%S" ) << endl;
						}
						pictCopy.SetFilterData( &cPar.p );
						pictCopy.Filter( pSrc, pDst, pstr );

						if( pstr ) {
							tEnd = CTime::GetCurrentTime();
							*pstr << "End processing at: " << tEnd.Format( "%H:%M:%S" ) << endl;
							CTimeSpan	tDiff( tEnd.GetTime() - tStart.GetTime() );
							*pstr << "Elapsed Time: " << tDiff.Format( "%H:%M:%S" ) << endl;
						}

						pDst->Detach();
						delete pDst;
					}
					pSrc->Detach();
					delete pSrc;
				}
				dstFile.Close();
			}
			srcFile.Close();
		}
	}
//	exit( 0 );
}
