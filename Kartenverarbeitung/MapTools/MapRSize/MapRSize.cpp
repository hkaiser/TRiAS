#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

#define Size32MB	(32*Size1MB)

static void Usage( ) {
	fprintf( stderr,
		"MapRSize [options] fileIn fileOut\n"
		"\t-?\tprint help\n"
		"\t-s\tSample Rate [default 2]\n"
		"\t-t\tTagsToMerge (Format: tagNum,Value|tagNum,Value|...)\n"
		"\t-p\tSample Param\n"
		"\t\tBilevel Images:\n"
		"\t\t0 (low) ... 3 (high) Quality Level\n"
		"\t\tPalette & RGB Images:\n"
		"\t\t0, 1, 2 Nearest Neighbour; 3 bilinear Interpolation\n"
		"\t-o\toutput picture type\n"
		);
}

CWinApp theApp;

int main( int argc, LPCTSTR *argv ) {
	int		c;
	LPCTSTR	optarg;
	int		optind = 1;

	theApp.InitInstance();
	theApp.m_hInstance = (HINSTANCE) ::GetCurrentProcess();
	afxCurrentResourceHandle = (HINSTANCE) ::GetCurrentProcess();
	PICTSAMPLEPARAM	fp;
	INIT_FILTERSTRUCT( &fp, CPictSample );

	fp.sampleRate = 2;
	fp.sampleParam = 0;
	CString	strInFile;
	CString	strOutFile;

	while( EOF != ( c = getopt( argc, argv, "t:s:p:?", optind, optarg ) ) ) {
		switch( c ) {
		case 's' :	fp.sampleRate = atoi( optarg ); break;
		case 'p' :	fp.sampleParam = atoi( optarg ); break;
		case 't' :	fp.p.lpszTagsToMerge = optarg; break;
		case '?' :	Usage(); exit( 1 );
		}
	}

	if( optind + 2 < argc ) {
		Usage( );
		exit( 1 );
	}

	strInFile = argv[optind++];
	strOutFile = argv[optind++];

	BOOL	bRet;
	CMemBlock	memInput( Size4MB );
	CMemBlock	memOutput( Size2MB );
	CRuntimeClass	*pInRT;
	CRuntimeClass	*pOutRT = NULL;
	CPicture		*pInPict;
	CPicture		*pOutPict;

	CFile		fileInput;
	CFile		fileOutput;

	CPictSample	filter;
	filter.SetFilterData( &fp.p );

	if( fileInput.Open( strInFile, CFile::modeRead | CFile::typeBinary ) ) {
		pInRT = ::GetPictureType( &fileInput );
		if( NULL == pOutRT )
			pOutRT = pInRT;
		if( NULL != pInRT && NULL != ( pInPict = (CPicture*) pInRT->CreateObject() ) ) {
			if( fileOutput.Open( strOutFile, CFile::modeReadWrite | CFile::modeCreate | CFile::typeBinary ) ) {
				VERIFY( NULL != ( pOutPict = (CPicture*) pOutRT->CreateObject() ) );
				if( pInPict->Attach( &fileInput ) && pInPict->ReadHeader() ) {
					if( pOutPict->Attach( &fileOutput ) ) {
						bRet = filter.Filter( pInPict, pOutPict );
						pOutPict->Detach();
					}
					pInPict->Detach();
				}
				fileOutput.Close();
				delete pOutPict;
			}
			delete pInPict;
		}
		fileInput.Close();
	}
	return TRUE == bRet ? 0 : 1;
}
