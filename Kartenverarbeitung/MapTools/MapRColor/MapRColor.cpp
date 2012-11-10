#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////

static void Usage() {
	fprintf( stderr,
		"MapRColor -h Histfile [options] fileIn fileOut\n"
		"\t-p\t0 ... without dithering\n"
		"\t\t1 ... use 3x3 dithering\n"
		"\t-t\tTagsToMerge (Format: tagNum,Value|tagNum,Value|...)"
		"\t-?\tprint help\n"
		);
}

void main( int argc, LPCTSTR *argv ) {
	int		c;
	LPCTSTR	optarg;
	int		optind = 1;

	LPCTSTR	pszInFile = NULL;
	LPCTSTR	pszOutFile = NULL;
	LPCTSTR	pszFltFile = NULL;
	MEDIANCUTPARAM	fp;

	INIT_FILTERSTRUCT( &fp, CMedianCut );
	fp.m = DITHER_NONE;

	while( EOF != ( c = getopt( argc, argv, "t:p:h:?", optind, optarg ) ) ) {
		switch( c ) {
		case 'p' :
			switch( atoi(optarg) ) {
			case 3 : fp.m = DITHER_3; break;
			case 4 : fp.m = DITHER_4; break;
			}
			break;
		case 'h' :	pszFltFile = optarg; break;
		case 't' :	fp.p.lpszTagsToMerge = optarg; break;
		case '?' :
			Usage(); exit(1);
		}
	}

	if( optind == argc || NULL == pszFltFile ) {
		Usage();
		exit(1);
	}

	pszInFile = argv[optind++];
	pszOutFile = argv[optind++];

	CMemBlock	mbIn( Size2MB );
	CMemBlock	mbOut( Size2MB );
	CTifPicture	pictIn( &mbIn );
	CTifPicture	pictOut( &mbOut );
	CFile		fileIn, fileOut;
	CMedianCut	*mcut;
	
	CMapStringToOb	l;
	CFile		arFile( pszFltFile, CFile::modeRead );
	CArchive	ar( &arFile, CArchive::load );

	WORD tag;
	ar >> tag;
	l.Serialize( ar );
	VERIFY( l.Lookup( "CMedianCut", (CObject*&) mcut ) );

	BOOL ret = FALSE;
	mcut->SetFilterData( &fp.p );

	if( fileIn.Open( pszInFile, CFile::modeRead | CFile::shareDenyWrite ) ) {
		if( pictIn.Attach( &fileIn ) && pictIn.ReadHeader( ) ) {
			if( PICT_COLOR_RGB == pictIn.GetColorspace() ) {
				if( fileOut.Open( pszOutFile, CFile::modeWrite | CFile::modeCreate ) ) {
					if( pictOut.Attach( &fileOut ) ) {
						TRY {
							ret = mcut->Filter( &pictIn, &pictOut );
						} CATCH( CPictException, e ) {
							lpictdll::ReportPictException( e );
							e->Delete();
						}
						END_CATCH
						pictOut.Detach();
					}
					fileOut.Close( );
				}
				else
					fprintf( stderr, "Cannot open infile: %s\n", pszInFile );
			}
			pictIn.Detach();
		}
		fileIn.Close( );
	}
	else
		fprintf( stderr, "Cannot open infile: %s\n", pszInFile );

	CString	key;
	CObject	*pObj;
	for( POSITION pos = l.GetStartPosition(); NULL != pos; ) {
		l.GetNextAssoc( pos, key, (CObject*&) pObj );
		delete pObj;
	}

	exit( TRUE == ret ? 0 : 1 );
}
