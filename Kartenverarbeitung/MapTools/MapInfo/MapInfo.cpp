#include "stdafx.h"
#include <locale.h>

#include "PictApplications.h"

void main( int argc, const char *argv[] ) {
	exit( TRUE == MapInfo( argc, argv, cin, cout, cerr ) ? 0 : 1 );
}

static ostream& Usage( ostream& s ) {
	s 	<< "MapInfo [options] fileIn" << endl
		;
	return s;
}

int MapInfo( const int argc, const char *argv[], istream& s_in, ostream& s_out, ostream& s_err ) {
	int		c;
	bool	bRaw = false;
	LPCTSTR	optarg;
	int		optind = 1;

	while( EOF != ( c = getopt( argc, argv, "rg?", optind, optarg ) ) ) {
		switch( c ) {
		case 'r' :	bRaw = true; break;
		case 'g' :	setlocale( LC_ALL, _T("German") ); break;
		case '?' :	Usage( s_err ); return TRUE;
		}
	}
	if( argc < optind ) {
		Usage( s_err );
		return FALSE;
	}
	CMemBlock		memPict( Size4MB );
	CRuntimeClass	*pRT;
	CPicture		*pPict;
	CFile			fileInput;
	for( ; optind < argc; optind++ ) {
		if( fileInput.Open( argv[optind], CFile::modeRead | CFile::typeBinary ) ) {
			pRT = ::GetPictureType( &fileInput );
			if( NULL != pRT && NULL != ( pPict = (CPicture*) pRT->CreateObject() ) ) {
				VERIFY( pPict->Attach( &fileInput ) && pPict->ReadHeader() );
				pPict->DumpTags( s_out, bRaw );
				pPict->Detach();
				delete pPict;
			} else {
				s_err << _T("cannot determine FileType: ") << argv[optind] << endl;
			}
			fileInput.Close();
		} else {
			s_err << _T("cannot open File: ") << argv[optind] << endl;
		}
	}
	return TRUE;
}
