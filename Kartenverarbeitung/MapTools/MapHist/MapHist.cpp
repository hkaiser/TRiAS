#include "stdafx.h"

/////////////////////////////////////////////////////////////////////////////
/*{{RCS
initial version
RCS}}*/
static char* pszRCS = "$Id:$";
// $History: $
/* $Log: maprsize.cpp $
// Revision 1.1  1996/07/12  10:43:22  andy
// initial version
//
//
*/
/////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////

static void Usage();

int main( int argc, LPCTSTR *argv )
{
	int		c;
	LPCTSTR	optarg;
	int		optind = 1;

	CString			strHistFile, strInFile;

	CObject			*obj;
	CString			key;
	CMapStringToOb	objects;
	BOOL			bReduceOnly = FALSE;
	BOOL			bInitTable = FALSE;

	while( EOF != ( c = getopt( argc, argv, "irh:?", optind, optarg ) ) )
	{
		switch( c )
		{
		case 'h' :	strHistFile = optarg; break;
		case 'r' :	bReduceOnly = TRUE; break;
		case 'i' :	bInitTable = TRUE; break;
		case '?' :
			Usage(); return 1;
		}
	}

	if( optind == argc )
		return 1;

	CFile		f;
	if( !strHistFile.IsEmpty() && f.Open( strHistFile, CFile::modeRead | CFile::typeBinary ) )
	{
		CArchive	ar( &f, CArchive::load );
		WORD	v;
		ar >> v;
		objects.Serialize( ar );
		ar.Close();
		f.Close();
	}

	if( !objects.Lookup( RUNTIME_CLASS( CPictHistogramm )->m_lpszClassName, obj ) )
		objects.SetAt( RUNTIME_CLASS( CPictHistogramm )->m_lpszClassName, new CPictHistogramm );
	if( !objects.Lookup( RUNTIME_CLASS( CMedianCut )->m_lpszClassName, obj ) )
		objects.SetAt( RUNTIME_CLASS( CMedianCut )->m_lpszClassName, new CMedianCut );

	CMemBlock	mb( Size16MB );
	CTifPicture	p( &mb );
	CPictFilter	*hist, *mcut;
	
	VERIFY( objects.Lookup( RUNTIME_CLASS( CPictHistogramm )->m_lpszClassName, (CObject*&) hist ) );
	VERIFY( objects.Lookup( RUNTIME_CLASS( CMedianCut )->m_lpszClassName, (CObject*&) mcut ) );

	if( !bReduceOnly )
	{
		if( bInitTable )
			hist->Init();
		for( ; optind < argc; optind++ )
		{
			if( !f.Open( argv[optind], CFile::modeRead | CFile::typeBinary ) )
				continue;
			if( !p.Attach( &f ) )
				continue;
			if( p.ReadHeader() )
			{
				cerr << argv[optind] << endl;
				hist->Filter( &p );
			}
			p.Detach();
			f.Close();
		}
	}

	mcut->Filter( hist );

	if( !strHistFile.IsEmpty() && f.Open( strHistFile, CFile::modeWrite | CFile::modeCreate | CFile::typeBinary ) )
	{
		CArchive	ar( &f, CArchive::store );
		WORD	v = 0x0100;
		ar << v;
		objects.Serialize( ar );
		ar.Close();
		f.Close();
	}

	for( POSITION pos = objects.GetStartPosition(); pos; )
	{
		objects.GetNextAssoc( pos, key, obj );
		objects.RemoveKey( key );
		delete obj;
	}
	return 0;
}

static void Usage()
{
	cerr << "Usage: MapHist [-i] [-r] -h HistFile InputFile[s]" << endl;
	cerr << "\t-h\tHistogrammfile" << endl;
	cerr << "\t-i\tinitialize Histogrammfile" << endl;
	cerr << "\t-r\tonly reduce Histogramm to colortable" << endl;
}