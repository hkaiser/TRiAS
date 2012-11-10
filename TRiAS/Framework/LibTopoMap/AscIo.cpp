#include "stdafx.h"

#include "libTopoMap/LibTopoMap.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

#pragma warning( disable : 4270 )

//////////////////////////////////////////////////////////////////////////////
// I/O - Stream - Manipulatoren für ASC - Export

ostream& os_format_ascHeaderRecord( ostream& os, tagASCRECORDINFO ri )
{
	os << "D Entry ";
	os << '\"'; os.width(16); os.setf( ios::left ); os << ri.pszEntryName << "\" ";
	os << '\"'; os.width(16); os.setf( ios::left ); os << ri.pszEntryText << "\"" << endl;
	return os;
}

OMANIP(tagASCRECORDINFO)	ASCHR( LPCTSTR pszHdrEntry, LPCTSTR pszEntryText )
{
	tagASCRECORDINFO	ri;
	ri.pszEntryName = pszHdrEntry;
	ri.pszEntryText = pszEntryText;
	return OMANIP(tagASCRECORDINFO) (os_format_ascHeaderRecord, ri);
}

ostream& os_format_ascHeaderRecordLong( ostream& os, tagASCRECORDINFO ri )
{
	os << "D Entry \"";
	os.width(16); os.setf( ios::left ); os << ri.pszEntryName << "\" \"";
	if( 10 == ri.iBase ) os << dec; else os << hex;
	os << ri.dval << "\"" << dec << endl;
	return os;
}

OMANIP(tagASCRECORDINFO)	ASCHR( LPCTSTR pszHdrEntry, long lValue, int b )
{
	tagASCRECORDINFO	ri;
	ri.pszEntryName = pszHdrEntry;
	ri.dval = lValue;
	ri.iBase = b;
	return OMANIP(tagASCRECORDINFO) (os_format_ascHeaderRecordLong, ri);
}

ostream& os_format_ascIdentRecord( ostream& os, tagASCRECORDINFO ri )
{
	os << "F " << ri.lval1 << ' ';
	if( ri.iVersion >= 5 )
		os << '\"';
	if( 10 == ri.iBase ) os << dec; else os << hex;
	os << ri.dval << dec;
	if( ri.iVersion >= 5 )
		os << '\"';
	os << ' '  << ri.lval2 << endl;
	return os;
}

OMANIP(tagASCRECORDINFO)	ASCIR( DWORD ident, long recno, long nPoints, int b, int version )
{
	tagASCRECORDINFO	ri;
	ri.iBase = b;
	ri.dval = ident;
	ri.lval1 = recno;
	ri.lval2 = nPoints;
	ri.iVersion = version;
	return OMANIP(tagASCRECORDINFO) (os_format_ascIdentRecord, ri);
}

ostream& os_format_ascMcodeRecord( ostream& os, tagASCRECORDINFO ri )
{
	int len = NULL == ri.pszEntryText ? 0 : strlen( ri.pszEntryText );
	os << "M ";
	if( 10 == ri.iBase ) os << dec; else os << hex; 
	os << ri.dval << dec;
	os << " 1 A " << len << endl;
	for( int start = 0, end = nMaxMCodeLineLength ; end < len; start += nMaxMCodeLineLength, end += nMaxMCodeLineLength )
	{
		CString	S( &ri.pszEntryText[start], nMaxMCodeLineLength );
		os << "W \"" << (LPCTSTR) S << '\"' << endl;
	}
	if( end - len > 0 )
	{
		CString	S( &ri.pszEntryText[start], end - ( end - len ) );
		os << "W \"" << (LPCTSTR) S << '\"' << endl;
	}
	return os;
}

OMANIP(tagASCRECORDINFO)	ASCMR( DWORD mCode, LPCTSTR pszRecordText, int b )
{
	tagASCRECORDINFO	ri;
	ri.iBase = b;
	ri.dval = mCode;
	ri.pszEntryText = pszRecordText;
	return OMANIP(tagASCRECORDINFO) (os_format_ascMcodeRecord, ri);
}

ostream& os_format_ascCommentRecord( ostream& os, tagASCRECORDINFO ri )
{
	os << "; " << ri.pszEntryText << endl;
	return os;
}

OMANIP(tagASCRECORDINFO)	ASCTR( LPCTSTR pszComment )
{
	tagASCRECORDINFO	ri;
	ri.pszEntryText = pszComment;
	return OMANIP(tagASCRECORDINFO) (os_format_ascCommentRecord, ri);
}

ostream& os_format_ascCoordRecord( ostream& os, tagASCRECORDINFO ri )
{
	os << dec << "G " << ri.x << " " << ri.y << endl;
	return os;
}

OMANIP(tagASCRECORDINFO)	ASCCR( double x, double y )
{
	tagASCRECORDINFO	ri;
	ri.x = x;
	ri.y = y;
	return OMANIP(tagASCRECORDINFO) (os_format_ascCoordRecord, ri);
}

/////////////////////////////////////////////////////////////////////////////

static char buf[512];

void WriteAscHeader( iostream& os, ASC_HEADER *pH )
{
	ostrstream	osFmt( buf, sizeof(buf));

	os << "H by MapManager generated DIRIS-File" << endl;
	os << ASCHR( "CoordTransform", pH->m_strCoordTrans );
	osFmt.setf( osFmt.flags() | ios::fixed );
	osFmt.precision( 1 );
	osFmt.seekp(0); osFmt << (double) pH->m_dwOffsetX << ' ' << (double) pH->m_dwOffsetY << ends;
	os << ASCHR( "Offset", osFmt.str() );
	osFmt.seekp(0); osFmt << (double) pH->m_dwScale11 << ' ' << (double) pH->m_dwScale12 << ' ' << (double) pH->m_dwScale21 << ' ' << (double) pH->m_dwScale22 << ends;
	os << ASCHR( "Scale", osFmt.str() );
}

void WriteAscTrailer( iostream& os )
{
	os << "E" << endl;
}
