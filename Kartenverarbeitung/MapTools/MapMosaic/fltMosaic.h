typedef struct tagSIZED {
	double cx;
	double cy;
	tagSIZED& operator=( tagSIZED& s )
		{ cx = s.cx; cy = s.cy; return *this; }
} SIZED;

typedef struct tagPOINTD {
	double x;
	double y;
	tagPOINTD& operator=( tagPOINTD& p )
		{ x = p.x; y = p.y; return *this; }
	tagPOINTD& operator=( POINTL& p )
		{ x = p.x; y = p.y; return *this; }
	tagPOINTD& operator=( POINT& p )
		{ x = p.x; y = p.y; return *this; }
	tagPOINTD& operator+=( SIZED& s )
		{ x += s.cx; y += s.cy; return *this; }
} POINTD;

typedef enum {
	NEARESTNEIGHBOUR,
	BILINEAR,
	CUBICSPLINE,
} SAMPLEMETHOD;


typedef struct tagPICTMOSAICPARAM {
	FILTERPARAM		p;
	POINTD			m_Ref[4];
	POINTD			m_Clip[4];
	CRect			m_rcDst;		// Zielrechteck
	SAMPLEMETHOD	m_method;
	tagPICTMOSAICPARAM();
	tagPICTMOSAICPARAM& operator=( tagPICTMOSAICPARAM& p );
	tagPICTMOSAICPARAM& operator=( tagPICTMOSAICPARAM *p );
} PICTMOSAICPARAM;

typedef PICTMOSAICPARAM FAR* LPPICTMOSAICPARAM;


class CPictMosaic : public CPictFilter
{
protected:
	DECLARE_SERIAL( CPictMosaic );
	PICTMOSAICPARAM	m_param;
	BOOL samplePal8( POINTD& pl, SIZED& szl, POINTD& pr, SIZED& szr );
	BOOL sampleGray( POINTD& pl, SIZED& szl, POINTD& pr, SIZED& szr );
	BOOL sampleRGB( POINTD& pl, SIZED& szl, POINTD& pr, SIZED& szr );
public:
	CPictMosaic( );
	~CPictMosaic( );

	virtual	BOOL	SetFilterData( LPFILTERPARAM pData );
	BOOL	Filter( CPicture *pInPicture, CPicture *pOutPicture, ostream* pstr = NULL );
public:
	virtual	void	Serialize( CArchive& ar );
};
