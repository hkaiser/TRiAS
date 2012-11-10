#ifndef	__PICTURE_CODEC_H__
#define	__PICTURE_CODEC_H__

#ifdef _AFXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

static const long LINEBUFSIZE = 0xffff;

class CPictCodec : public CObject
{
	DECLARE_DYNAMIC( CPictCodec );
protected:
	CPictCodec( );

	CPicture	*m_pPicture;
	HPBYTE	m_pSrc;
	HPBYTE	m_pDst;
	long	m_srcStart, m_srcEnd;
	long	m_srcPos;
	long	m_dstPos;

	long	m_lineLength;

	virtual	long	DecodeLine( long nBytes ) = 0;
public:
	virtual ~CPictCodec();
	BOOL Attach( CPicture* pPicture );
	virtual void Reset();
	virtual BOOL Setup();
	virtual BOOL Init();
	virtual BOOL Encode( HPBYTE pSrcData, HPBYTE& pDstData, long nSrcBytes ) = 0;
	virtual BOOL Decode( const CRect& rcPict );
};

//////////////////////////////////////////////////////////////////
// TIFF-Codecs

class CCodecPackBits : public CPictCodec
{
	DECLARE_DYNCREATE( CCodecPackBits );
	short	m_nCopy;
	short	m_nExpand;
protected:
	CCodecPackBits( );
	virtual	long	DecodeLine( long nBytes );
public:
	virtual ~CCodecPackBits( );
	virtual void Reset();
	virtual BOOL Setup();
	virtual BOOL Init();
	virtual BOOL Encode( HPBYTE pSrcData, HPBYTE& pDstData, long nSrcBytes );
};

class CCodecLZWTiff : public CPictCodec
{
	DECLARE_DYNCREATE( CCodecLZWTiff );
protected:
	CCodecLZWTiff( );
	virtual	long	DecodeLine( long nBytes );
public:
	virtual ~CCodecLZWTiff( );
	virtual void Reset();
	virtual BOOL Setup();
	virtual BOOL Init();
	virtual BOOL Encode( HPBYTE pSrcData, HPBYTE& pDstData, long nSrcBytes );
	virtual BOOL Decode( const CRect& rcPict );
};

typedef DWORD	uint32;
typedef WORD	uint16;
typedef BYTE	u_char;

typedef struct {
	int	mode;					/* operating mode */
	uint32	rowbytes;			/* bytes in a decoded scanline */
	uint32	rowpixels;			/* pixels in a scanline */

	uint16	cleanfaxdata;		/* CleanFaxData tag */
	uint32	badfaxrun;			/* BadFaxRun tag */
	uint32	badfaxlines;		/* BadFaxLines tag */
	uint32	groupoptions;		/* Group 3/4 options tag */
	uint32	recvparams;			/* encoded Class 2 session params */
	char*	subaddress;			/* subaddress string */
	uint32	recvtime;			/* time spent receiving (secs) */
} Fax3BaseState;

typedef struct {
	Fax3BaseState b;
	const u_char* bitmap;		/* bit reversal table */
	uint32	data;				/* current i/o byte/word */
	int	bit;					/* current i/o bit in byte */
	int	EOLcnt;					/* count of EOL codes recognized */
	uint16*	runs;				/* b&w runs for current/previous row */
	uint16*	refruns;			/* runs for reference line */
	uint16*	curruns;			/* runs for current line */
} Fax3DecodeState;

typedef struct {
	Fax3BaseState b;
	int	data;					/* current i/o byte */
	int	bit;					/* current i/o bit in byte */
	enum { G3_1D, G3_2D } tag;	/* encoding state */
	u_char*	refline;			/* reference line for 2d decoding */
	int	k;						/* #rows left that can be 2d encoded */
	int	maxk;					/* max #rows that can be 2d encoded */
} Fax3EncodeState;

typedef enum {
	S_Null = 0,
	S_Pass = 1,
	S_Horiz = 2,
	S_V0 = 3,
	S_VR = 4,
	S_VL = 5,
	S_Ext = 6,
	S_TermW = 7,
	S_TermB = 8,
	S_MakeUpW = 9,
	S_MakeUpB = 10,
	S_MakeUp = 11,
	S_EOL = 12,
} G3STATE;

typedef struct {				/* state table entry */
	G3STATE State;				/* see above */
	unsigned char Width;		/* width of code in bits */
	uint16	Param;				/* unsigned 16-bit run length in bits */
} TIFFFaxTabEnt;

extern	const TIFFFaxTabEnt TIFFFaxMainTable[];
extern	const TIFFFaxTabEnt TIFFFaxWhiteTable[];
extern	const TIFFFaxTabEnt TIFFFaxBlackTable[];

class CCodecFax : public CPictCodec
{
	DECLARE_DYNAMIC( CCodecFax );
protected:
	typedef struct {
	BYTE*	cp;						/* next byte of input data */
	BYTE*	ep;						/* end of input data */
	WORD*	runs;					/* b&w runs for current/previous row */
	WORD*	thisrun;				/* current row's run array */
	WORD*	curruns;				/* runs for current line */
	WORD*	refruns;				/* runs for reference line */
	WORD*	pa;						/* place to stuff next run */
	WORD*	pb;						/* next run in reference line */
	int	b1;							/* next change on prev line */

	int		a0;						/* reference element */
	int		lastx;					/* last element in row */
	DWORD	BitAcc;					/* bit accumulator */
	int		BitsAvail;				/* # valid bits in BitAcc */
	int		RunLength;				/* length of current run */
	int		EOLcnt;					/* # EOL codes recognized */
	const	BYTE* bitmap;			/* input data bit reverser */
	const	TIFFFaxTabEnt* TabEnt;
	} STATE;

	STATE	m_l;
	DWORD	m_dwOptions;

	void	unexpected( LPCTSTR lpszCause );
	void	extension( );
	void	badlength( );
	void	prematureEOF( );

	BOOL	_EndOfData();
	void	_ClrBits( int n );
	uint32	_GetBits( int n );
	BOOL	_NeedBits8( int n );
	BOOL	_NeedBits16( int n );
	BOOL	_LOOKUP8( int wid, const TIFFFaxTabEnt* tab );
	BOOL	_LOOKUP16( int wid, const TIFFFaxTabEnt* tab );
	void	_SETVAL( int x );
	void	_CHECK_b1( );
	void	_CLEANUP_RUNS();
	BOOL	_SYNC_EOL();

protected:
	CCodecFax( );
	virtual	long	DecodeLine( long nBytes ) = 0;
	BOOL _EXPAND2D( );
	BOOL _EXPAND1D( );
	void _ZERO( long n, BYTE* cp);
	void _FILL( long n, BYTE *cp);
	void CopyFaxRuns( BYTE* buf, WORD* runs, WORD* erun, int lastx);
public:
	virtual ~CCodecFax( );
	virtual void Reset();
	virtual BOOL Setup();
	virtual BOOL Init();
	virtual BOOL Encode( HPBYTE pSrcData, HPBYTE& pDstData, long nSrcBytes );
};

class CCodecFaxG3 : public CCodecFax
{
	DECLARE_DYNCREATE( CCodecFaxG3 );
	long	Decode1D( long nBytes );
	long	Decode2D( long nBytes );
	long (CCodecFaxG3::*m_pCodecfunc)(long);
protected:
	CCodecFaxG3( );
	virtual	long	DecodeLine( long nBytes );
public:
	virtual ~CCodecFaxG3( );
	virtual void Reset();
	virtual BOOL Setup();
	virtual BOOL Init();
	virtual BOOL Encode( HPBYTE pSrcData, HPBYTE& pDstData, long nSrcBytes );
};

class CCodecFaxG4 : public CCodecFax
{
	DECLARE_DYNCREATE( CCodecFaxG4 );
protected:
	CCodecFaxG4( );
	virtual	long	DecodeLine( long nBytes );
public:
	virtual ~CCodecFaxG4( );
	virtual void Reset();
	virtual BOOL Setup();
	virtual BOOL Init();
	virtual BOOL Encode( HPBYTE pSrcData, HPBYTE& pDstData, long nSrcBytes );
};

//////////////////////////////////////////////////////////////////
// BMP-Codecs

class CCodecRLE4 : public CPictCodec
{
	DECLARE_DYNCREATE( CCodecRLE4 );
protected:
	CCodecRLE4( );
	virtual	long	DecodeLine( long nBytes );
public:
	virtual ~CCodecRLE4( );
	virtual void Reset();
	virtual BOOL Setup();
	virtual BOOL Init();
	virtual BOOL Encode( HPBYTE pSrcData, HPBYTE& pDstData, long nSrcBytes );
};

class CCodecRLE8 : public CPictCodec
{
	DECLARE_DYNCREATE( CCodecRLE8 );
	signed char	m_nSymbol;
	BOOL	m_bHaveSymbol;
	short	m_nCopy, m_nCopyAdd;
	short	m_nExpand;
	short	m_dx, m_dy;
protected:
	CCodecRLE8( );
	virtual	long	DecodeLine( long nBytes );
public:
	virtual ~CCodecRLE8( );
	virtual void Reset();
	virtual BOOL Setup();
	virtual BOOL Init();
	virtual BOOL Encode( HPBYTE pSrcData, HPBYTE& pDstData, long nSrcBytes );
};

#ifdef	_AFX_ENABLE_INLINES
#if !defined(_AFX_INLINE)
#define	_AFX_INLINE inline
#endif
#include	"lpict/PictCod.inl"
#endif

#ifdef _AFXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR
#endif

#endif // __PICTURE_CODEC_H__
