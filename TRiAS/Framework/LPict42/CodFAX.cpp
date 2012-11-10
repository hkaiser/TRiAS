#include "stdafx.h"
#include "LPictImpl.h"

#ifdef LAFX_PICT_SEG
#pragma code_seg(LAFX_PICT_SEG)
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define	new	DEBUG_NEW

IMPLEMENT_DYNAMIC( CCodecFax, CPictCodec );

#define NO_TRACING

#ifdef NO_TRACING
#undef TRACE
#define TRACE              1 ? (void)0 : ::AfxTrace
#endif

void CCodecFax::Reset( ) {
	CPictCodec::Reset();
	if( NULL != m_l.runs )
		delete[] m_l.runs;
	memset( &m_l, 0x00, sizeof( m_l ) );
	m_l.runs = m_l.thisrun = m_l.refruns = NULL;
}

BOOL CCodecFax::Setup( ) { if( !CPictCodec::Setup() )
		return FALSE;
	ASSERT_VALID( m_pPicture );
	TAG	t;
//	ASSERT_POINTER( m_pSrc, BYTE );
//	ASSERT_POINTER( m_pDst, BYTE );

	if( NULL != m_l.runs )
		delete[] m_l.runs;
	m_l.runs = NULL;

	PICT_COMPR c = m_pPicture->GetCompression( );
	PICT_FORDER	o = m_pPicture->GetFillOrder( );

	if( PICT_FILLORD_SEVENISZERO != o && PICT_FILLORD_ZEROISZERO != o )
		return FALSE;
	if( PICT_COMPR_FAXG3 == c ) 
		if( m_pPicture->GetTag( PICT_PROP_G3OPTIONS, t ) )
			m_dwOptions = t.ulVal();
	else if( PICT_COMPR_FAXG4 == c )
		if( m_pPicture->GetTag( PICT_PROP_G4OPTIONS, t ) )
			m_dwOptions = t.ulVal();
	else
		return FALSE;

	m_l.lastx = m_pPicture->GetPictRect().Width();
	m_l.bitmap = PICT_FILLORD_SEVENISZERO == o ? &BitRevTable[0] : &NoBitRevTable[0];

	int	nRows = m_pPicture->GetPictRect().Height();
	int	nRuns = TIFFroundup( nRows, 32 );
	
	if( (PICT_G3OPTIONS) m_dwOptions & PICT_G3_2DENCODING || PICT_COMPR_FAXG4 == c )
		nRuns *= 2;
	
	m_l.runs = new WORD[ nRuns ];
	memset( (void*) m_l.runs, 0x00, nRuns * sizeof( WORD ) );
	m_l.curruns = m_l.runs;

	if( (PICT_G3OPTIONS) m_dwOptions & PICT_G3_2DENCODING || PICT_COMPR_FAXG4 == c )
		m_l.refruns = m_l.curruns + ( nRuns >> 1 );

	return TRUE;
}

BOOL CCodecFax::Init( ) {
	ASSERT_VALID( m_pPicture );
	if( !CPictCodec::Init() )
		return FALSE;
	m_l.cp = m_pSrc;
	m_l.BitAcc = 0;
	m_l.BitsAvail = 0;
	m_l.EOLcnt = 0;
	if( NULL != m_l.refruns ) {
		m_l.refruns[0] = (short) m_pPicture->GetPictRect().Width();
		m_l.refruns[1] = 0;
	}
	return TRUE;
}

BOOL CCodecFax::Encode( HPBYTE pSrcData, HPBYTE& pDstData, long nSrcBytes ) {
	ASSERT( NULL != m_pPicture );
	return FALSE;
}

void	CCodecFax::unexpected( LPCTSTR lpszCause ) {
}
void	CCodecFax::extension( ) {
}
void	CCodecFax::badlength( ) {
}
void	CCodecFax::prematureEOF( ) {
}

//////////////////////////////////////////////////////////////////////////////

BOOL CCodecFax::_EndOfData() {
	return (m_l.cp >= m_l.ep);
}

DWORD CCodecFax::_GetBits( int n ) {
	return m_l.BitAcc & ( ( 1 << n ) ) - 1;
}

void CCodecFax::_ClrBits( int n ) {
	m_l.BitsAvail -= n; m_l.BitAcc >>= n;
}

void CCodecFax::_CHECK_b1( ) {
    if (m_l.pa != m_l.thisrun)
	{
		while (m_l.b1 <= m_l.a0 && m_l.b1 < m_l.lastx)
		{
			m_l.b1 += m_l.pb[0] + m_l.pb[1];
			m_l.pb += 2;
		}
	}
}

BOOL CCodecFax::_NeedBits8( int n ) {
    if (m_l.BitsAvail < n ) {
		if( _EndOfData() ) {
			if (m_l.BitsAvail == 0)		/* no valid bits */
				return FALSE;
			m_l.BitsAvail = (n);		/* pad with zeros */
		} else {
			m_l.BitAcc |= ((uint32) m_l.bitmap[*m_l.cp++])<<m_l.BitsAvail;
			m_l.BitsAvail += 8;
		}
    }
	return TRUE;
}

BOOL CCodecFax::_NeedBits16( int n ) {
    if (m_l.BitsAvail < (n)) {
		if (_EndOfData()) {
		    if (m_l.BitsAvail == 0)		/* no valid bits */
				return FALSE;
			m_l.BitsAvail = (n);		/* pad with zeros */
		} else {
			m_l.BitAcc |= ((uint32) m_l.bitmap[*m_l.cp++])<<m_l.BitsAvail;
			if ((m_l.BitsAvail += 8) < (n)) {
				if(_EndOfData()) {
					/* NB: we know BitsAvail is non-zero here */
					m_l.BitsAvail = (n);	/* pad with zeros */
				} else {
					m_l.BitAcc |= ((uint32) m_l.bitmap[*m_l.cp++])<<m_l.BitsAvail;
					m_l.BitsAvail += 8;
				}
			}
		}
    }
	return TRUE;
}

static const char* StateNames[] = {
    "Null   ",
    "Pass   ",
    "Horiz  ",
    "V0     ",
    "VR     ",
    "VL     ",
    "Ext    ",
    "TermW  ",
    "TermB  ",
    "MakeUpW",
    "MakeUpB",
    "MakeUp ",
    "EOL    ",
};

BOOL CCodecFax::_LOOKUP8( int wid, const TIFFFaxTabEnt* tab ) {
	if( !_NeedBits8(wid) )
		return FALSE;
    m_l.TabEnt = tab + _GetBits(wid);
	TRACE( "LOOK8  %08lx/%-3d: %s%5d\n", (DWORD) m_l.BitAcc, m_l.BitsAvail, StateNames[m_l.TabEnt->State], m_l.TabEnt->Param );
    _ClrBits(m_l.TabEnt->Width);
	return TRUE;
}

BOOL CCodecFax::_LOOKUP16( int wid, const TIFFFaxTabEnt* tab ) {
	if( !_NeedBits16(wid) )
		return FALSE;
	m_l.TabEnt = tab + _GetBits(wid);
	TRACE( "LOOK16 %08lX/%-3d: %s%5d\n", (DWORD) m_l.BitAcc, m_l.BitsAvail, StateNames[m_l.TabEnt->State], m_l.TabEnt->Param );
	_ClrBits(m_l.TabEnt->Width);
	return TRUE;
}

void CCodecFax::_SETVAL( int x ) { 
	*m_l.pa++ = m_l.RunLength + x;
	TRACE( "SETVAL %d\t%d\n", m_l.RunLength + x, m_l.a0 );
	m_l.a0 += x;
	m_l.RunLength = 0;
}

void CCodecFax::_CLEANUP_RUNS() {
    if (m_l.RunLength)
		_SETVAL(0);
    if (m_l.a0 != m_l.lastx) {
		badlength( );
		while (m_l.a0 > m_l.lastx && m_l.pa > m_l.thisrun)
			m_l.a0 -= *--m_l.pa;
		if (m_l.a0 < m_l.lastx) {
			if (m_l.a0 < 0)
				m_l.a0 = 0;
			if ((m_l.pa-m_l.thisrun)&1)
				_SETVAL(0);
			_SETVAL(m_l.lastx - m_l.a0);
		} else if (m_l.a0 > m_l.lastx) {
			_SETVAL(m_l.lastx);
			_SETVAL(0);
		}
    }
}

BOOL CCodecFax::_SYNC_EOL() {
    if (m_l.EOLcnt == 0) {
		for (;;) {
			if( !_NeedBits16( 11 ) )
				return FALSE;
			if (_GetBits(11) == 0)
				break;
			_ClrBits(1);
		}
    }
    for (;;) {
		if( !_NeedBits8( 8 ) )
			return FALSE;
		if (_GetBits(8))
			break;
		_ClrBits(8);
    }
    while (_GetBits(1) == 0)
		_ClrBits(1);
    _ClrBits(1);				/* EOL bit */
    m_l.EOLcnt = 0;			/* reset EOL counter/flag */
	return TRUE;
}

BOOL CCodecFax::_EXPAND1D( ) {
	for (;;) {
		for (;;) {
			if( !_LOOKUP16( 12, TIFFFaxWhiteTable ) )
				goto eof1d;
			switch (m_l.TabEnt->State) {
			case S_EOL:
				m_l.EOLcnt = 1;
				goto done1d;
			case S_TermW:
				_SETVAL( m_l.TabEnt->Param );
				goto doneWhite1d;
			case S_MakeUpW:
			case S_MakeUp:
				m_l.a0 += m_l.TabEnt->Param;
				m_l.RunLength += m_l.TabEnt->Param;
				break;
			default:
				unexpected( _T("WhiteTable") );
				goto done1d;
			}
		}
doneWhite1d:
		if (m_l.a0 >= m_l.lastx)
			goto done1d;
		for (;;) {
			if( !_LOOKUP16( 13, TIFFFaxBlackTable) )
				goto eof1d;
			switch( m_l.TabEnt->State ) {
			case S_EOL:
				m_l.EOLcnt = 1;
				goto done1d;
			case S_TermB:
				_SETVAL(m_l.TabEnt->Param);
				goto doneBlack1d;
			case S_MakeUpB:
			case S_MakeUp:
				m_l.a0 += m_l.TabEnt->Param;
				m_l.RunLength += m_l.TabEnt->Param;
				break;
			default:
				unexpected( _T("BlackTable") );
				goto done1d;
			}
		}
doneBlack1d:
		if (m_l.a0 >= m_l.lastx)
			goto done1d;
	}
eof1d:
	prematureEOF( );
	_CLEANUP_RUNS();
	return FALSE;
done1d:
	_CLEANUP_RUNS();
	return TRUE;
}

BOOL CCodecFax::_EXPAND2D( ) {
	do {
		while( m_l.a0 < m_l.lastx) {
			if( !_LOOKUP8(7, TIFFFaxMainTable) )	// LOOKUP8(7, TIFFFaxMainTable, eof2d);
				goto eof2d;
			switch (m_l.TabEnt->State) {
			case S_Pass:			
			    _CHECK_b1();			
			    m_l.b1 += *m_l.pb++;		
			    m_l.RunLength += m_l.b1 - m_l.a0;
			    m_l.a0 = m_l.b1;			
			    m_l.b1 += *m_l.pb++;		
			    break;				
			case S_Horiz:			
				if( ( m_l.pa - m_l.thisrun ) & 1 ) {
					for (;;) {	/* black first */
					    if( !_LOOKUP16(13, TIFFFaxBlackTable) )	// LOOKUP16(13, TIFFFaxBlackTable, eof2d);
							goto eof2d;
					    switch (m_l.TabEnt->State) {
						case S_TermB:			
							_SETVAL(m_l.TabEnt->Param);	
							goto doneWhite2da;		
						case S_MakeUpB:			
						case S_MakeUp:			
							m_l.a0 += m_l.TabEnt->Param;	
							m_l.RunLength += m_l.TabEnt->Param;
							break;
						default:
							goto badBlack2d;
					    }
					}
doneWhite2da:;
					for (;;) {	/* then white */
						if( !_LOOKUP16(12, TIFFFaxWhiteTable) )	// LOOKUP16(12, TIFFFaxWhiteTable, eof2d);
							goto eof2d;
						switch (m_l.TabEnt->State) {
						case S_TermW:
							_SETVAL(m_l.TabEnt->Param);
							goto doneBlack2da;
						case S_MakeUpW:	
						case S_MakeUp:	
							m_l.a0 += m_l.TabEnt->Param;
							m_l.RunLength += m_l.TabEnt->Param;
							break;
						default:
							goto badWhite2d;
					    }
					}
doneBlack2da:;
				} else {
					for (;;) {	/* white first */
						if( !_LOOKUP16(12, TIFFFaxWhiteTable) ) // LOOKUP16(12, TIFFFaxWhiteTable, eof2d);
							goto eof2d;
						switch (m_l.TabEnt->State) {
						case S_TermW:
							_SETVAL(m_l.TabEnt->Param);
							goto doneWhite2db;
						case S_MakeUpW:
						case S_MakeUp:
							m_l.a0 += m_l.TabEnt->Param;
							m_l.RunLength += m_l.TabEnt->Param;
							break;
						default:
							goto badWhite2d;
						}
					}
doneWhite2db:;
					for (;;) {	/* then black */
						if( !_LOOKUP16(13, TIFFFaxBlackTable) ) // LOOKUP16(13, TIFFFaxBlackTable, eof2d);
							goto eof2d;
						switch (m_l.TabEnt->State) {
						case S_TermB:
							_SETVAL(m_l.TabEnt->Param);
							goto doneBlack2db;
						case S_MakeUpB:
						case S_MakeUp:
							m_l.a0 += m_l.TabEnt->Param;
							m_l.RunLength += m_l.TabEnt->Param;
							break;
						default:
							goto badBlack2d;
					    }
					}
doneBlack2db:;
				}
				_CHECK_b1();							
				break;							
			case S_V0:							
				_CHECK_b1();							
				_SETVAL(m_l.b1 - m_l.a0);						
				m_l.b1 += *m_l.pb++;						
				break;							
			case S_VR:							
				_CHECK_b1();							
				_SETVAL(m_l.b1 - m_l.a0 + m_l.TabEnt->Param);				
				m_l.b1 += *m_l.pb++;						
				break;							
			case S_VL:							
				_CHECK_b1( );
				_SETVAL(m_l.b1 - m_l.a0 - m_l.TabEnt->Param);				
				m_l.b1 -= *--m_l.pb;						
				break;							
			case S_Ext:							
				*m_l.pa++ = m_l.lastx - m_l.a0;						
				extension( );
				goto eol2d;							
			case S_EOL:							
				*m_l.pa++ = m_l.lastx - m_l.a0;						
				if( !_NeedBits8(5) ) // NeedBits8(5,eof2d);
					goto eof2d;
				if(_GetBits(5))						
					unexpected(_T("EOL"));
				m_l.EOLcnt = 1;							
				goto eol2d;							
			default:							
badMain2d:							
				unexpected(_T("MainTable"));				
				goto eol2d;							
badBlack2d:							
				unexpected(_T("BlackTable"));				
				goto eol2d;							
badWhite2d:							
				unexpected("WhiteTable");				
				goto eol2d;							
eof2d:								
				prematureEOF();						
				_CLEANUP_RUNS();						
				return FALSE;		// #AK goto eoflab;						
			}								
		}									
		if (m_l.RunLength) {							
			/* expect a final V0 */						
			if( !_NeedBits8(1) ) // NeedBits8(1,eof2d);						
				goto eof2d;
			if (!_GetBits(1))						
				goto badMain2d;						
			_ClrBits(1);							
			_SETVAL(0);							
		}									
eol2d:									
		_CLEANUP_RUNS();							
	} while (0);
	return TRUE;
}

void CCodecFax::_FILL( long n, BYTE *cp) {
}
void CCodecFax::_ZERO(long n, BYTE *cp) {
}

/*
 * The ZERO & FILL macros must handle spans < 2*sizeof(long) bytes.
 * For machines with 64-bit longs this is <16 bytes; otherwise
 * this is <8 bytes.  We optimize the code here to reflect the
 * machine characteristics.
 */

#if defined(__alpha) || _MIPS_SZLONG == 64
#define FILL(n, cp)							    \
    switch (n) {							    \
    case 15:(cp)[14] = 0xff; case 14:(cp)[13] = 0xff; case 13: (cp)[12] = 0xff;\
    case 12:(cp)[11] = 0xff; case 11:(cp)[10] = 0xff; case 10: (cp)[9] = 0xff;\
    case  9: (cp)[8] = 0xff; case  8: (cp)[7] = 0xff; case  7: (cp)[6] = 0xff;\
    case  6: (cp)[5] = 0xff; case  5: (cp)[4] = 0xff; case  4: (cp)[3] = 0xff;\
    case  3: (cp)[2] = 0xff; case  2: (cp)[1] = 0xff;			      \
    case  1: (cp)[0] = 0xff; (cp) += (n); case 0:  ;			      \
    }
#define ZERO(n, cp)							\
    switch (n) {							\
    case 15:(cp)[14] = 0; case 14:(cp)[13] = 0; case 13: (cp)[12] = 0;	\
    case 12:(cp)[11] = 0; case 11:(cp)[10] = 0; case 10: (cp)[9] = 0;	\
    case  9: (cp)[8] = 0; case  8: (cp)[7] = 0; case  7: (cp)[6] = 0;	\
    case  6: (cp)[5] = 0; case  5: (cp)[4] = 0; case  4: (cp)[3] = 0;	\
    case  3: (cp)[2] = 0; case  2: (cp)[1] = 0;			      	\
    case  1: (cp)[0] = 0; (cp) += (n); case 0:  ;			\
    }
#else
#define FILL(n, cp)							    \
    switch (n) {							    \
    case 7: (cp)[6] = 0xff; case 6: (cp)[5] = 0xff; case 5: (cp)[4] = 0xff; \
    case 4: (cp)[3] = 0xff; case 3: (cp)[2] = 0xff; case 2: (cp)[1] = 0xff; \
    case 1: (cp)[0] = 0xff; (cp) += (n); case 0:  ;			    \
    }
#define ZERO(n, cp)							\
    switch (n) {							\
    case 7: (cp)[6] = 0; case 6: (cp)[5] = 0; case 5: (cp)[4] = 0;	\
    case 4: (cp)[3] = 0; case 3: (cp)[2] = 0; case 2: (cp)[1] = 0;	\
    case 1: (cp)[0] = 0; (cp) += (n); case 0:  ;			\
    }
#endif

void CCodecFax::CopyFaxRuns( BYTE* buf, WORD* runs, WORD* erun, int lastx) {
	static const unsigned char _fillmasks[] =
	    { 0x00, 0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfe, 0xff };

	BYTE*	cp;
	int		x, bx;
	WORD	run;
	long	n, nw;
	long*	lp;

	if( ( erun - runs ) & 1 )
	    *erun++ = 0;
	x = 0;
	for (; runs < erun; runs += 2) {
	    run = runs[0];
	    if (x+run > lastx)
			run = runs[0] = lastx - x;
	    if (run) {
			cp = buf + (x>>3);
			bx = x&7;
			if (run > 8-bx) {
				if (bx) {				/* align to byte boundary */
					*cp++ &= 0xff << (8-bx);
					run -= 8-bx;
			    }
				if (n = run >> 3) {		/* multiple bytes to fill */
					if ((n/sizeof (long)) > 1) {
					    /* Align to longword boundary and fill. */
					    for (; n && !isAligned(cp, long); n--)
						    *cp++ = 0x00;
					    lp = (long*) cp;
					    nw = (long)(n / sizeof (long));
					    n -= nw * sizeof (long);
					    do {
						    *lp++ = 0L;
					    } while (--nw);
					    cp = (u_char*) lp;
					}
					ZERO(n, cp);
					run &= 7;
				}
#ifdef PURIFY
			    if (run)
					cp[0] &= 0xff >> run;
#else
			    cp[0] &= 0xff >> run;
#endif
			}
			else
			    cp[0] &= ~(_fillmasks[run]>>bx);
			x += runs[0];
		}
	    run = runs[1];
	    if (x+run > lastx)
		run = runs[1] = lastx - x;
	    if (run)  {
			cp = buf + (x>>3);
			bx = x&7;
			if (run > 8-bx) {
				if (bx) {			/* align to byte boundary */
					*cp++ |= 0xff >> bx;
					run -= 8-bx;
			    }
				if (n = run>>3) {		/* multiple bytes to fill */
					if ((n/sizeof (long)) > 1) {
						/* Align to longword boundary and fill. */
					    for (; n && !isAligned(cp, long); n--)
							*cp++ = 0xff;
					    lp = (long*) cp;
					    nw = (long)(n / sizeof (long));
					    n -= nw * sizeof (long);
					    do {
							*lp++ = -1L;
					    } while (--nw);
					    cp = (u_char*) lp;
					}
					FILL(n, cp);
					run &= 7;
			    }
#ifdef PURIFY
			    if (run)
					cp[0] |= 0xff00 >> run;
#else
			    cp[0] |= 0xff00 >> run;
#endif
			}
			else
			    cp[0] |= _fillmasks[run]>>bx;
			x += runs[1];
	    }
	}
	ASSERT(x == lastx);
}
#undef	ZERO
#undef	FILL
