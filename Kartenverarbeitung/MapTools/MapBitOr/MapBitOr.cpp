#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// CWinApp	theApp;

/////////////////////////////////////////////////////////////////////////////

#define Size32MB	(32*Size1MB)

static void Usage( ) {
	fprintf( stderr,
		"MapBitOr [options] fileIn fileOut\n"
		"\t-?\tprint help\n"
		"\t-l\tBitLevel to OR from source file to destination file\n"
		"\t-t\tTagsToMerge (Format: tagNum,Value|tagNum,Value|...)\n"
		"\t-C\tstartColumn:nColumns\n"
		"\t-R\tstartRow:nRows\n"
		);
}

int main( int argc, LPCTSTR *argv ) {
	int		c;
	LPCTSTR	optarg;
	int		optind = 1;

	BITORPARAM	fp;
	INIT_FILTERSTRUCT( &fp, CPictBitOr );

	fp.m_nLevelToOr = 2;
//	fp.sampleParam = 0;
	CString	strInFile;
	CString	strOutFile;

	while( EOF != ( c = getopt( argc, argv, "t:l:C:R:?", optind, optarg ) ) ) {
		switch( c ) {
		case 'l' :	fp.m_nLevelToOr = atoi( optarg ); break;
//		case 'p' :	fp.sampleParam = atoi( optarg ); break;
		case 't' :	fp.p.lpszTagsToMerge = optarg; break;
		case 'C' :	{
				CString	S;
				::AfxExtractSubString( S, optarg, 0, ':' );
				fp.m_l = atoi( S );
				::AfxExtractSubString( S, optarg, 1, ':' );
				fp.m_r = fp.m_l + atoi( S );
//				fp.m_r = atoi( S );
			}
			break;
		case 'R' :	{
				CString	S;
				::AfxExtractSubString( S, optarg, 0, ':' );
				fp.m_t = atoi( S );
				::AfxExtractSubString( S, optarg, 1, ':' );
				fp.m_b = fp.m_t + atoi( S );
//				fp.m_b = atoi( S );
			}
			break;
		case '?' :	Usage(); exit( 1 );
		}
	}

	if( optind + 2 < argc )
	{
		Usage( );
		exit( 1 );
	}

	strInFile = argv[optind++];
	strOutFile = argv[optind++];

	BOOL	bRet;
	CMemBlock	memInput( Size2MB );
	CMemBlock	memOutput( Size2MB );
	CRuntimeClass	*pInRT = NULL;
	CRuntimeClass	*pOutRT = NULL;
	CPicture		*pInPict;
	CPicture		*pOutPict;

	CFile		fileInput;
	CFile		fileOutput;

	CPictBitOr	filter;
	filter.SetFilterData( &fp.p );

	if( fileInput.Open( strInFile, CFile::modeRead | CFile::typeBinary ) )
	{
		pInRT = ::GetPictureType( &fileInput );
		if( NULL != pInRT && NULL != ( pInPict = (CPicture*) pInRT->CreateObject() ) )
		{
			VERIFY( pInPict->Attach( &fileInput ) );
			if( fileOutput.Open( strOutFile, CFile::modeReadWrite | CFile::typeBinary ) )
			{
				if( NULL != ( pOutRT = ::GetPictureType( &fileOutput ) ) && NULL != ( pOutPict = (CPicture*) pOutRT->CreateObject() ) )
				{
					VERIFY( pOutPict->Attach( &fileOutput ) );

					VERIFY( pInPict->ReadHeader() );
					VERIFY( pOutPict->ReadHeader() );
					TRY {
						bRet = filter.Filter( pInPict, pOutPict );
					}
					CATCH( CPictException, e )
					{
						lpictdll::ReportPictException( e );
						DELETE_EXCEPTION(e);
					}
					END_CATCH
					pOutPict->Detach();
					delete pOutPict;
				}
				fileOutput.Close();
			}
			pInPict->Detach();
			delete pInPict;
		}
		fileInput.Close();
	}
	return TRUE == bRet ? 0 : 1;
}
