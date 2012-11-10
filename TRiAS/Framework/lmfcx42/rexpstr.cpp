#include	"stdafx.h"

#ifdef LAFX_FUNC_SEG
#pragma code_seg(LAFX_FUNC_SEG)
#endif

/////////////////////////////////////////////////////////////////////////////
/*{{RCS
initial version
RCS}}*/
static char* pszRCS = "$Id: rexpstr.cpp 1.1 1996/07/12 17:16:19 andy Exp $";
/* $Log: rexpstr.cpp $
// Revision 1.1  1996/07/12  17:16:19  andy
// initial version
//
*/
/////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////

#define new DEBUG_NEW

IMPLEMENT_DYNAMIC( CRex, CObject )

//////////////////////////////////////////////////////////////////////////

#define	NEXPR	256 			// max. size of compiled regex - string

#define	CNUL	'\0'

#define	CBRA	0x02				// 0x02 0000 0010
#define	CCHR	0x04				// 0x04 0000 0100
#define	CDOT	0x08				// 0x08 0000 1000
#define	CCL		0x0c				// 0x0c 0000 0110
#define	CDOL	0x14				// 0x14 0001 0010
#define	CCEOF	0x16				// 0x16 0001 0110
#define	CKET	0x18				// 0x18 0001 1000
#define	CBACK	0x24				// 0x24 0010 0100

#define	STAR	0x01				// 0x01 0000 0001
#define RNGE	0x03				// 0x03 0000 0011

static	BYTE	bittab[] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 };


#define PLACE(ebuf,c)	((ebuf)[(BYTE)(c)>>3]|=bittab[(BYTE)(c)&0x07])
#define ISTHERE(eBuf,c)	((eBuf)[(BYTE)(c)>>3]&bittab[(BYTE)(c)&0x07])

CRex::CRex( )
	{ Construct(); }

CRex::CRex( LPCTSTR instring, char seof )
	{ Construct(); Compile( instring, seof ); }

void CRex::Construct()
{
	m_pEB = (BYTE *) new char[ NEXPR ];
	m_pszBrackSList = (LPCTSTR*) new char[ NBRA * sizeof( LPCTSTR ) ];
	m_pszBrackEList = (LPCTSTR*) new char[ NBRA * sizeof( LPCTSTR ) ];
}

CRex::~CRex( )
{
	ASSERT( m_pEB );
	delete[] m_pEB;
	ASSERT( m_pszBrackSList );
	delete[] m_pszBrackSList;
	ASSERT( m_pszBrackEList );
	delete[] m_pszBrackEList;
}

void CRex::Initialize( )
{
	memset( (void*) m_pEB, 0x00, NEXPR );
	m_pEBCurr = m_pEB;
	m_pEBEnd = &m_pEB[ NEXPR ];

	m_bIsSed = FALSE;
	m_bIsNoDelim = FALSE;
	m_bIsCircf = FALSE;
	m_nEof = DEF_EOF;
	m_nRegErr = 0;
	m_pszRegErr = NULL;
	m_nBrackets = 0;
}

CString CRex::Found( int n )
{
	if( 0 == n )
	{
		if( NULL != m_pszMatchStart )
			return CString( m_pszMatchStart, m_pszMatchEnd - m_pszMatchStart );
		else
			return CString( "" );
	}
	else if( m_nBrackets >= n )
	{
		return CString( m_pszBrackSList[n-1], m_pszBrackEList[n-1] - m_pszBrackSList[n-1] );
	}
	else
		return CString( "" );
}

BOOL CRex::Compile( LPCTSTR instring, char seof )
{
	LPCTSTR	sp;

#define	GETC( )		( *sp++ )
#define	PEEKC( )	( *sp )
#define	UNGETC( )	( --sp )
#define	REXERROR( n )	{ m_nRegErr = n; m_pszRegErr = ( sp == instring ) ? sp : sp - 1; return FALSE; }

	char	c;
	char	lc;
	BYTE	*lastep;
	int		cclcnt;

	BYTE	bracket[NBRA];
	BYTE	*bracketp;
	int		n_Brackets;
	int		n_ClosedBrack;

	int		i;

	BOOL	neg;
	BOOL	commaFlag;

	Initialize( );

	lastep = NULL;
	sp = instring;
	m_nEof = seof;

	c = GETC( );
	if( c == m_nEof || c == '\n' )
	{
		if( c == '\n' )
		{
			UNGETC( );
			m_bIsNoDelim = TRUE;
		}
		if( *m_pEBCurr == '\0' && !m_bIsSed )
			REXERROR( E_REXSTRING_EMPTY );
	}
	bracketp = bracket;
	n_Brackets = n_ClosedBrack = 0;
	if( c == '^' )
		m_bIsCircf = TRUE;
	else
		UNGETC( );
	while( 1 )
	{
		if( m_pEBCurr >= m_pEBEnd )
			REXERROR( E_REXBUF_OVERFLOW );
		c = GETC( );
		if( c != '*' && ( ( c != '\\' ) || ( PEEKC( ) != '{' ) ) )
			lastep = m_pEBCurr;
		if( c == m_nEof )
		{
			*m_pEBCurr++ = CCEOF;
			return TRUE;
		}

		switch( c )
		{
		case '.':
			*m_pEBCurr++ = CDOT;
			continue;

		case '\n':
			if( !m_bIsSed )
				REXERROR( E_REXSTRING_NEWLINE );
			UNGETC( );
			*m_pEBCurr++ = CCEOF;
			m_bIsNoDelim = TRUE;
			return TRUE;

		case '*':
			if( lastep == NULL || *lastep == CBRA || *lastep == CKET )
				goto _lbl_defchar;
			*lastep |= STAR;
			continue;

		case '$':
			if( PEEKC( ) != m_nEof && PEEKC( ) != '\n' )
				goto _lbl_defchar;
			*m_pEBCurr++ = CDOL;
			continue;

		case '[':
			if( &m_pEBCurr[17] >= m_pEBEnd )
				REXERROR( E_REXBUF_OVERFLOW );

			*m_pEBCurr++ = CCL;
			lc = '\0';
			// for( i = 0; i < 16; i++ )
			//	m_pEBCurr[i] = 0x00;
//			memset( (void*) m_pEBCurr, 0x00, 16 );

			neg = FALSE;
			if( ( c = GETC( ) ) == '^' )
			{
				neg = TRUE;
				c = GETC( );
			}

			do
			{
				if( c == '\0' || c == '\n' )
					REXERROR( E_RANGE_EOF );
				if( c == '-' && lc != '\0' )
				{
					if( ( c = GETC( ) ) == ']' )
					{
						PLACE( m_pEBCurr, '-' );
						break;
					}
					while( lc < c )
					{
						PLACE( m_pEBCurr, lc );
						lc++;
					}
				}
				lc = c;
				PLACE( m_pEBCurr, c );
			} while( ( c = GETC( ) ) != ']' );
			if( neg == TRUE )
			{
				for( cclcnt = 0; cclcnt < 16; cclcnt++ )
					m_pEBCurr[cclcnt] ^= 0xff;
				m_pEBCurr[0] &= 0376;
			}
			m_pEBCurr += 16;
			continue;

		case '\\':						// handles the special characters
			switch( c = GETC( ) )
			{
			case '(':
				if( n_Brackets >= NBRA )
					REXERROR( E_BRACKET_COUNT );
				*bracketp++ = (char) n_Brackets;
				*m_pEBCurr++ = CBRA;
				*m_pEBCurr++ = (char) n_Brackets++;
				continue;

			case ')':
				if( bracketp <= bracket || ++n_ClosedBrack != n_Brackets )
					REXERROR( E_BRACKET_CLOSE );
				*m_pEBCurr++ = CKET;
				*m_pEBCurr++ = *--bracketp;
				m_nBrackets++;
				continue;

			case '{':
				if( lastep == NULL )
					goto _lbl_defchar;
				*lastep |= RNGE;
				commaFlag = FALSE;
_lbl_nlim:
				c = GETC( );
				i = 0;
				do
				{
					if( c >= '0' && c <= '9' )
						i = 10 * i + c - '0';
					else
						REXERROR( E_RANGE_INVALIDCHAR );
				} while( ( ( c = GETC( ) ) != '\\' ) && ( c != ',' ) );
				if( i > 255 )
					REXERROR( E_RANGE_TOBIG );
				*m_pEBCurr++ = (char) i;
				if( c == ',' )
				{
					if( commaFlag == TRUE )
						REXERROR( E_RANGE_COMMA );
					commaFlag = TRUE;
					if( ( c = GETC( ) ) == '\\' )
						*m_pEBCurr++ = 255;
					else
					{
						UNGETC( );
						goto _lbl_nlim;			// get 2'nd number
					}
				}
				if( GETC( ) != '}' )
					REXERROR( E_RANGE_NOTCLOSED );
				if( commaFlag == FALSE )		// one number
					*m_pEBCurr++ = (char) i;
				else
					if( ( m_pEBCurr[-1] & 0377 ) < ( m_pEBCurr[-2] & 0377 ) )
						REXERROR( E_RANGE_SIZE );
				continue;

			case '\n':
				REXERROR( E_REXSTRING_NEWLINE );

			case 'n':
				c = '\n';
				goto _lbl_defchar;

			default:
				if( c >= '1' && c <= '9' )
				{
					if( (int) ( c -= '1' ) >= m_nBrackets )
						REXERROR( E_BRACKET_UNDEF );
					*m_pEBCurr++ = CBACK;
					*m_pEBCurr++ = c;
					continue;
				}
			}

_lbl_defchar:		// Drop through to default to use \ to turn off special chars
		default:
			lastep = m_pEBCurr;
			*m_pEBCurr++ = CCHR;
			*m_pEBCurr++ = c;
		}
	}
	return TRUE;
}

BOOL CRex::Compare( LPCTSTR string )
{
	char	c;

	m_pszStart = string;
	m_pszMatchStart = NULL;

	if( Error( ) )
		return FALSE;
	if( m_bIsCircf )
	{
		m_pszMatchStart = (char*) string;
		return( Advance( string, m_pEB ) );
	}
	if( *m_pEB == CCHR )				// fast check for first character */
	{
		c = m_pEB[1];
		do
		{
			if( *string != c )
				continue;
			if( Advance( string, m_pEB ) )
			{
				m_pszMatchStart = (char*) string;
				return TRUE;
			}
		} while( *string++ );
		return FALSE;
	}
	do							// regular algorithm */
	{
		if( Advance( string, m_pEB ) )
		{
			m_pszMatchStart = (char*) string;
			return TRUE;
		}
	} while( *string++ );
	return FALSE;
}

inline void CRex::GetRange( BYTE * exprBuf, int& nLow, int& nSize )
{
	nLow = (int) ( *exprBuf++ & 0x7f );
	nSize = (int) ( *exprBuf == 0xff ? 20000 : ( *exprBuf & 0x7f ) - nLow );
}

inline BOOL CRex::Ecmp( LPCTSTR a, LPCTSTR b, int count )
{
	while( count-- )
		if( *a++ != *b++ )
			return FALSE;
	return TRUE;
}

BOOL CRex::Advance( LPCTSTR lp, BYTE *exprBuf )
{
	LPCTSTR	curlp;
	LPCTSTR	bbeg;
	char	 c;
	int		 ct;

	while( 1 )
	{
		switch( *exprBuf++ )
		{
		case CCHR:
			if( *lp++ == (char) *exprBuf++ )
				continue;
			return FALSE;

		case CDOT:
			if( *lp++ )
				continue;
			return FALSE;

		case CDOL:
			if( *lp == '\0' )
				return TRUE;
			else
				return FALSE;

//			if( *lp == '\0' )
//				continue;		// ???
//			return FALSE;

		case CCEOF:
			if( *lp == m_nEof )
			{
				m_pszMatchEnd = lp;
				return TRUE;
			}
			return FALSE;

		case CCL:
			c = (char) ( *lp++ & 0177 );
			if( ISTHERE( exprBuf, c ) )
			{
				exprBuf += 16;
				continue;
			}
			return FALSE;

		case CBRA:
			m_pszBrackSList[*exprBuf++] = lp;
			continue;

		case CKET:
			m_pszBrackEList[*exprBuf++] = lp;
			continue;

		case CCHR|RNGE:
			{
				int	nLow, nSize;
				c = *exprBuf++;
				GetRange( exprBuf, nLow, nSize );
				while( nLow-- )
					if( *lp++ != c )
						return FALSE;
				curlp = (char*) lp;
				while( nSize-- )
					if( *lp++ != c )
						break;
				if( nSize < 0 )
					lp++;
				exprBuf += 2;
				goto _lbl_star;
			}

		case CDOT|RNGE:
			{
				int	nLow, nSize;
				GetRange( exprBuf, nLow, nSize );
				while( nLow-- )
					if( *lp++ == '\0' )
						return FALSE;
				curlp = lp;
				while( nSize-- )
					if( *lp++ == '\0' )
						break;
				if( nSize < 0 )
					lp++;
				exprBuf += 2;
				goto _lbl_star;
			}

		case CCL|RNGE:
			{
				int	nLow, nSize;
				GetRange( exprBuf + 16, nLow, nSize );
				while( nLow-- )
				{
					c = (char) ( *lp++ & 0x7f );
					if( !ISTHERE( exprBuf, c ) )
						return FALSE;
				}
				curlp = lp;
				while( nSize-- )
				{
					c = (char) ( *lp++ & 0x7f );
					if( !ISTHERE( exprBuf, c ) )
						break;
				}
				if( nSize < 0 )
					lp++;
				exprBuf += 18;				// 16 ... CCL - Table, 2 ... Range
				goto _lbl_star;
			}

		case CBACK:
			bbeg = m_pszBrackSList[ *exprBuf ];
			ct = m_pszBrackEList[ *exprBuf++ ] - bbeg;

			if( Ecmp( bbeg, lp, ct ) )
			{
				lp += ct;
				continue;
			}
			return FALSE;

		case CBACK|STAR:
			bbeg = m_pszBrackSList[ *exprBuf ];
			ct = m_pszBrackEList[ *exprBuf++ ] - bbeg;
			curlp = lp;
			while( Ecmp( bbeg, lp, ct ) )
				lp += ct;

			while( lp >= curlp )
			{
				if( Advance( lp, exprBuf ) )
					return TRUE;
				lp -= ct;
			}
			return FALSE;

		case CDOT|STAR:
			curlp = lp;
			while( *lp++ );
			goto _lbl_star;

		case CCHR|STAR:
			curlp = lp;
			while( *lp++ == (char) *exprBuf );
			exprBuf++;
			goto _lbl_star;

		case CCL|STAR:
			curlp = lp;
			do
			{
				c = (char) ( *lp++ & 0x7f );
			} while( ISTHERE( exprBuf, c ) );
			exprBuf += 16;
			goto _lbl_star;

_lbl_star:
			do
			{
				if( --lp == m_pszStart )
					break;
				if( Advance( lp, exprBuf ) )
					return TRUE;
			} while( lp > curlp );
			return FALSE;
		}
	}
}

#if	defined( _DEBUG )

#include	<iostream.h>

void
CRex::Dump( CDumpContext& dc )
{
	BYTE	*cp;
	strstream	str;

	if( Error( ) )
		return;
	for( cp = m_pEB; cp != m_pEBCurr; )
	{
		hex( str );
		str.width( 2 );
		str.fill( '0' );
		str << ( (int) *cp );

		str.width( 15 );
		str.fill( ' ' );

		switch( *cp++ )
		{
		case CBRA	:	str << " CBRA"; break;
		case CCHR	:	str << " CCHR"; DumpCCHR( cp, str ); break;
		case CDOT	:	str << " CDOT"; break;
		case CCL	:	str << " CCL"; DumpCCL( cp, str ); break;
		case CDOL	:	str << " CDOL"; break;
		case CCEOF	:	str << " CCEOF"; break;
		case CKET	:	str << " CKET"; break;
		case CBACK	:	str << " CBACK"; break;

		case CBRA  | STAR :	str << " CBRA | STAR"; break;
		case CCHR  | STAR :	str << " CCHR | STAR"; DumpCCHR( cp, str ); break;
		case CDOT  | STAR :	str << " CDOT | STAR"; break;
		case CCL   | STAR :	str << " CCL | STAR"; DumpCCL( cp, str ); break;
		case CDOL  | STAR :	str << " CDOL | STAR"; break;
		case CCEOF | STAR :	str << " CCEOF | STAR"; break;
		case CKET  | STAR :	str << " CKET | STAR"; break;
		case CBACK | STAR :	str << " CBACK | STAR"; break;

		case CCHR  | RNGE :
			str << " CCHR | RNGE"; DumpCCHR( cp, str ); DumpRange( cp, str ); break;
		case CDOT  | RNGE :
			str << " CDOT | RNGE"; DumpRange( cp, str ); break;
		case CCL   | RNGE :
			str << " CCL | RNGE"; DumpCCL( cp, str ); DumpRange( cp, str ); break;
		}
		str << endl;
	}
	dc << str.str( );
}

void
CRex::DumpCCHR( BYTE*& cp, strstream& str )
{
	str << ' ' << *cp++;
}

void
CRex::DumpCCL( BYTE*& cp, strstream& str )
{
	hex( str );
	str.fill( '0' );

	for( int i = 0; i < 16; i++ )
	{
		str << ' ';
		str.width( 2 );
		str << ( (int) *cp++ );
	}
}

void
CRex::DumpRange( BYTE*& cp, strstream& str )
{
	dec( str );
	str.fill( ' ' );
	str.width( 4 ); str << ( (int) *cp++ ) << ',';
	str.width( 4 ); str << ( (int) *cp++ );
}

#endif
