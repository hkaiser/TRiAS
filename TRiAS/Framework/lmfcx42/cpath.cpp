#include	"stdafx.h"
#include	<ctype.h>

#ifdef LAFX_CORE_SEG
#pragma code_seg(LAFX_CORE_SEG)
#endif

/////////////////////////////////////////////////////////////////////////////
/*{{RCS
initial version
RCS}}*/
static char* pszRCS = "$Id: cpath.cpp 1.1 1996/07/12 17:16:24 andy Exp $";
/* $Log: cpath.cpp $
// Revision 1.1  1996/07/12  17:16:24  andy
// initial version
//
*/
/////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL( CPath, CObject, 0 );

#define	new	DEBUG_NEW

//////////////////////////////////////////////////////////////////////////

CPath::~CPath( )
	{ Cleanup( ); }

CPath::CPath( const char *pszPath )
	{ Path( pszPath ); }

void CPath::Cleanup( )
{
	m_sDrv.Empty( );
	m_sDir.Empty( );
	m_sPfx.Empty( );
	m_sExt.Empty( );
	m_sPath.Empty( );
}

/////////////////////////////////////////////////////////////////////
//              member functions
/////////////////////////////////////////////////////////////////////

void
CPath::Path( const char * p )
{
	_splitpath( p,
		m_sDrv.GetBufferSetLength( _MAX_DRIVE + 1 ),
		m_sDir.GetBufferSetLength( _MAX_DIR + 1 ),
		m_sPfx.GetBufferSetLength( _MAX_FNAME + 1 ),
		m_sExt.GetBufferSetLength( _MAX_EXT + 1 ) );

	m_sDrv.ReleaseBuffer( -1 );
	m_sDir.ReleaseBuffer( -1 );
	m_sPfx.ReleaseBuffer( -1 );
	m_sExt.ReleaseBuffer( -1 );

	m_Drive = (int) *(const char*) m_sDrv;
	m_Drive = isalpha( m_Drive ) ? tolower( m_Drive ) - 'a' : -1;

	NewFile();
}

void
CPath::Drive( const char *pszDrive )
{
	m_sDrv = pszDrive;
	m_Drive = (int) *(const char*) m_sDrv;
	m_Drive = isalpha( m_Drive ) ? tolower( m_Drive ) - 'a' : -1;
	NewFile( );
}

void CPath::Dir( const char *pszDir )
	{ m_sDir = pszDir; NewFile( ); }

void CPath::Prefix( const char *pszPrefix )
	{ m_sPfx = pszPrefix; NewFile( ); }

void CPath::Suffix( const char * pszExtension )
	{ m_sExt = pszExtension; NewFile( ); }

void CPath::FileName( const char * p )
{

	_splitpath( p, NULL, NULL,
		m_sPfx.GetBufferSetLength( _MAX_FNAME + 1 ),
		m_sExt.GetBufferSetLength( _MAX_EXT + 1 )  );

	m_sPfx.ReleaseBuffer( -1 );
	m_sExt.ReleaseBuffer( -1 );
	NewFile();
}

void CPath::NewFile( )
	{ m_sPath = m_sDrv + m_sDir + m_sPfx + m_sExt; }

void CPath::Serialize( CArchive& ar )
{
	ASSERT_VALID( this );

	CObject::Serialize( ar );

	if( ar.IsStoring() )
	{
		ar << m_sDrv;
		ar << m_sDir;
		ar << m_sPfx;
		ar << m_sExt;
	}
	else
	{
		ar >> m_sDrv;
		ar >> m_sDir;
		ar >> m_sPfx;
		ar >> m_sExt;
		NewFile( );
	}
}

#ifdef	_DEBUG
void CPath::AssertValid( ) const 
{
	CObject::AssertValid( );
}

void CPath::Dump( CDumpContext& dc ) const
{
	ASSERT_VALID( this );
	CObject::Dump( dc );
	dc << m_sDrv;
	dc << m_sDir;
	dc << m_sPfx;
	dc << m_sExt;
}
#endif
