// Inlines for lafx.h

#ifdef _AFX_INLINE

//////////////////////////////////////////////////////////////////////
//	Inlines für CPath
//////////////////////////////////////////////////////////////////////

_AFX_INLINE CPath::CPath()
	: CObject( )
	{}
_AFX_INLINE CPath::operator LPCTSTR   () const
	{ return (LPCTSTR ) m_sPath; }
_AFX_INLINE LPCTSTR  CPath::operator()() const
	{ return (LPCTSTR ) m_sPath; }
_AFX_INLINE CString CPath::Path( ) const
	{ return m_sPath; }
_AFX_INLINE CString CPath::Drive( ) const		
	{ return m_sDrv; }
_AFX_INLINE CString CPath::Dir( ) const		
	{ return m_sDir; }
_AFX_INLINE CString CPath::Prefix( ) const		
	{ return m_sPfx; }
_AFX_INLINE CString CPath::Suffix( ) const		
	{ return m_sExt; }
_AFX_INLINE CString CPath::FileName( ) const	
	{ return CString( m_sPfx + m_sExt ); }

//////////////////////////////////////////////////////////////////////
// CDSize

_AFX_INLINE CDSize::CDSize()
	{ cx = cy = 0; }
_AFX_INLINE CDSize::CDSize(double initCX, double initCY)
	{ cx = initCX; cy = initCY; }
_AFX_INLINE CDSize::CDSize(DSIZE initSize)
	{ *(DSIZE*)this = initSize; }
_AFX_INLINE CDSize::CDSize(DPOINT initPt)
	{ *(DPOINT*)this = initPt; }
_AFX_INLINE CDSize::CDSize(DWORD dwSize)
	{
		cx = (short)LOWORD(dwSize);
		cy = (short)HIWORD(dwSize);
	}
_AFX_INLINE BOOL CDSize::operator==(DSIZE size) const
	{ return (cx == size.cx && cy == size.cy); }
_AFX_INLINE BOOL CDSize::operator!=(DSIZE size) const
	{ return (cx != size.cx || cy != size.cy); }

_AFX_INLINE void CDSize::operator+=(DSIZE size)
	{ cx += size.cx; cy += size.cy; }
_AFX_INLINE void CDSize::operator-=(DSIZE size)
	{ cx -= size.cx; cy -= size.cy; }

_AFX_INLINE CDSize CDSize::operator+(DSIZE size) const
	{ return CDSize(cx + size.cx, cy + size.cy); }
_AFX_INLINE CDSize CDSize::operator-(DSIZE size) const
	{ return CDSize(cx - size.cx, cy - size.cy); }
_AFX_INLINE CDSize CDSize::operator-() const
	{ return CDSize(-cx, -cy); }
_AFX_INLINE CDPoint CDSize::operator+(DPOINT point) const
	{ return CDPoint(cx + point.x, cy + point.y); }
_AFX_INLINE CDPoint CDSize::operator-(DPOINT point) const
	{ return CDPoint(cx - point.x, cy - point.y); }
_AFX_INLINE CDRect CDSize::operator+(const DRECT* lpRect) const
	{ return CDRect(lpRect) + *this; }
_AFX_INLINE CDRect CDSize::operator-(const DRECT* lpRect) const
	{ return CDRect(lpRect) - *this; }

//////////////////////////////////////////////////////////////////////
// CDPoint
_AFX_INLINE CDPoint::CDPoint()
	{ x = y = 0; }
_AFX_INLINE CDPoint::CDPoint(double initX, double initY)
	{ x = initX; y = initY; }
_AFX_INLINE CDPoint::CDPoint(DPOINT initPt)
	{ *(DPOINT*)this = initPt; }
_AFX_INLINE CDPoint::CDPoint(DSIZE initSize)
	{ *(DSIZE*)this = initSize; }
_AFX_INLINE CDPoint::CDPoint(DWORD dwPoint)
	{
		x = (short)LOWORD(dwPoint);
		y = (short)HIWORD(dwPoint);
	}
_AFX_INLINE void CDPoint::Offset(double xOffset, double yOffset)
	{ x += xOffset; y += yOffset; }
_AFX_INLINE void CDPoint::Offset(DPOINT point)
	{ x += point.x; y += point.y; }
_AFX_INLINE void CDPoint::Offset(DSIZE size)
	{ x += size.cx; y += size.cy; }
_AFX_INLINE BOOL CDPoint::operator==(DPOINT point) const
	{ return (x == point.x && y == point.y); }
_AFX_INLINE BOOL CDPoint::operator!=(DPOINT point) const
	{ return (x != point.x || y != point.y); }

_AFX_INLINE void CDPoint::operator+=(SIZE size)
	{ x += size.cx; y += size.cy; }
_AFX_INLINE void CDPoint::operator-=(SIZE size)
	{ x -= size.cx; y -= size.cy; }
_AFX_INLINE void CDPoint::operator+=(POINT point)
	{ x += point.x; y += point.y; }
_AFX_INLINE void CDPoint::operator-=(POINT point)
	{ x -= point.x; y -= point.y; }

_AFX_INLINE void CDPoint::operator+=(DSIZE size)
	{ x += size.cx; y += size.cy; }
_AFX_INLINE void CDPoint::operator-=(DSIZE size)
	{ x -= size.cx; y -= size.cy; }
_AFX_INLINE void CDPoint::operator+=(DPOINT point)
	{ x += point.x; y += point.y; }
_AFX_INLINE void CDPoint::operator-=(DPOINT point)
	{ x -= point.x; y -= point.y; }

_AFX_INLINE void CDPoint::operator=(const DPOINT& srcPoint)
	{ x = srcPoint.x; y = srcPoint.y; }
_AFX_INLINE CDPoint CDPoint::operator+(DSIZE size) const
	{ return CDPoint(x + size.cx, y + size.cy); }
_AFX_INLINE CDPoint CDPoint::operator-(DSIZE size) const
	{ return CDPoint(x - size.cx, y - size.cy); }
_AFX_INLINE CDPoint CDPoint::operator-() const
	{ return CDPoint(-x, -y); }
_AFX_INLINE CDPoint CDPoint::operator+(DPOINT point) const
	{ return CDPoint(x + point.x, y + point.y); }
_AFX_INLINE CDSize CDPoint::operator-(DPOINT point) const
	{ return CDSize(x - point.x, y - point.y); }
_AFX_INLINE CDRect CDPoint::operator+(const DRECT* lpRect) const
	{ return CDRect(lpRect) + *this; }
_AFX_INLINE CDRect CDPoint::operator-(const DRECT* lpRect) const
	{ return CDRect(lpRect) - *this; }

//////////////////////////////////////////////////////////////////////
// CDRect

_AFX_INLINE CDRect::CDRect()
	{ left = right = top = bottom = 0; }
_AFX_INLINE CDRect::CDRect(double l, double t, double r, double b)
	{ left = l; top = t; right = r; bottom = b; }
_AFX_INLINE CDRect::CDRect(const DRECT& srcRect)
	{ CopyRect(&srcRect); }
_AFX_INLINE CDRect::CDRect(LPCDRECT lpSrcRect)
	{ CopyRect(lpSrcRect); }
_AFX_INLINE CDRect::CDRect(DPOINT point, DSIZE size)
	{ right = (left = point.x) + size.cx; bottom = (top = point.y) + size.cy; }
_AFX_INLINE CDRect::CDRect(DPOINT topLeft, DPOINT bottomRight)
	{ left = topLeft.x; top = topLeft.y;
		right = bottomRight.x; bottom = bottomRight.y; }
_AFX_INLINE double CDRect::Width() const
	{ return right - left; }
_AFX_INLINE double CDRect::Height() const
	{ return bottom - top; }
_AFX_INLINE CDSize CDRect::Size() const
	{ return CDSize(right - left, bottom - top); }
_AFX_INLINE CDPoint& CDRect::TopLeft()
	{ return *((CDPoint*)this); }
_AFX_INLINE CDPoint& CDRect::BottomRight()
	{ return *((CDPoint*)this+1); }
_AFX_INLINE const CDPoint& CDRect::TopLeft() const
	{ return *((CDPoint*)this); }
_AFX_INLINE const CDPoint& CDRect::BottomRight() const
	{ return *((CDPoint*)this+1); }
_AFX_INLINE CDPoint CDRect::CenterPoint() const
	{ return CDPoint((left+right)/2, (top+bottom)/2); }
_AFX_INLINE CDRect::operator LPRECTD()
	{ return this; }
_AFX_INLINE CDRect::operator LPCDRECT() const
	{ return this; }
_AFX_INLINE BOOL CDRect::IsRectEmpty() const
	{ return right == left && bottom == top; }
_AFX_INLINE BOOL CDRect::IsRectNull() const
	{ return (left == 0 && right == 0 && top == 0 && bottom == 0); }
_AFX_INLINE BOOL CDRect::PtInRect(DPOINT point) const
	{ return point.x >= left && point.x < right && point.y >= top && point.y < bottom; }
_AFX_INLINE void CDRect::SetRect(double x1, double y1, double x2, double y2)
	{ left = x1; top = y1; right = x2; bottom = y2; }
_AFX_INLINE void CDRect::SetRect(DPOINT topLeft, DPOINT bottomRight)
	{ SetRect( topLeft.x, topLeft.y, bottomRight.x, bottomRight.y); }
_AFX_INLINE void CDRect::SetRectEmpty()
	{ left = right = top = bottom = 0; }
_AFX_INLINE void CDRect::CopyRect(LPCDRECT lpSrcRect)
	{ left = lpSrcRect->left; right = lpSrcRect->right; top = lpSrcRect->top; bottom = lpSrcRect->bottom; }
_AFX_INLINE BOOL CDRect::EqualRect(LPCDRECT lpRect) const
	{ return left == lpRect->left && right == lpRect->right && top == lpRect->top && bottom == lpRect->bottom; }
_AFX_INLINE void CDRect::InflateRect(double x, double y)
	{ left -= x; right += x; top -= y; bottom += y; }
_AFX_INLINE void CDRect::InflateRect(DSIZE size)
	{ InflateRect(size.cx, size.cy); }
_AFX_INLINE void CDRect::InflateRect(double l, double t, double r, double b)
	{ left -= l; right += r; top -= t; bottom += b; }
_AFX_INLINE void CDRect::InflateRect(LPCDRECT lpRect)
	{ InflateRect( lpRect->left, lpRect->right, lpRect->top, lpRect->bottom ); }
_AFX_INLINE void CDRect::DeflateRect(double x, double y)
	{ InflateRect(-x, -y); }
_AFX_INLINE void CDRect::DeflateRect(DSIZE size)
	{ InflateRect(-size.cx, -size.cy); }
_AFX_INLINE void CDRect::DeflateRect(LPCDRECT lpRect)
	{ InflateRect( -lpRect->left, -lpRect->right, -lpRect->top, -lpRect->bottom ); }
_AFX_INLINE void CDRect::OffsetRect(double x, double y)
	{ left += x; right += x; top += y; bottom += y; }
_AFX_INLINE void CDRect::OffsetRect(DPOINT point)
	{ OffsetRect(point.x, point.y); }
_AFX_INLINE void CDRect::OffsetRect(DSIZE size)
	{ OffsetRect(size.cx, size.cy); }

_AFX_INLINE void CDRect::operator=(const DRECT& srcRect)
	{ CopyRect(&srcRect); }
_AFX_INLINE BOOL CDRect::operator==(const DRECT& rect) const
	{ return EqualRect(&rect); }
_AFX_INLINE BOOL CDRect::operator!=(const DRECT& rect) const
	{ return !EqualRect(&rect); }
_AFX_INLINE void CDRect::operator+=(DPOINT point)
	{ OffsetRect(point.x, point.y); }
_AFX_INLINE void CDRect::operator+=(DSIZE size)
	{ OffsetRect(size.cx, size.cy); }
_AFX_INLINE void CDRect::operator+=(LPCDRECT lpRect)
	{ InflateRect(lpRect); }
_AFX_INLINE void CDRect::operator-=(DPOINT point)
	{ OffsetRect(-point.x, -point.y); }
_AFX_INLINE void CDRect::operator-=(DSIZE size)
	{ OffsetRect(-size.cx, -size.cy); }
_AFX_INLINE void CDRect::operator-=(LPCDRECT lpRect)
	{ DeflateRect(lpRect); }
_AFX_INLINE void CDRect::operator&=(const DRECT& rect)
	{ IntersectRect(this, &rect); }
_AFX_INLINE void CDRect::operator|=(const DRECT& rect)
	{ UnionRect(this, &rect); }
_AFX_INLINE CDRect CDRect::operator+(DPOINT pt) const
	{ CDRect rect(*this); rect.OffsetRect( pt.x, pt.y); return rect; }
_AFX_INLINE CDRect CDRect::operator-(DPOINT pt) const
	{ CDRect rect(*this); rect.OffsetRect(-pt.x, -pt.y); return rect; }
_AFX_INLINE CDRect CDRect::operator+(DSIZE size) const
	{ CDRect rect(*this); rect.OffsetRect(size.cx, size.cy); return rect; }
_AFX_INLINE CDRect CDRect::operator-(DSIZE size) const
	{ CDRect rect(*this); rect.OffsetRect(-size.cx, -size.cy); return rect; }
_AFX_INLINE CDRect CDRect::operator+(LPCDRECT lpRect) const
	{ CDRect rect(this); rect.InflateRect(lpRect); return rect; }
_AFX_INLINE CDRect CDRect::operator-(LPCDRECT lpRect) const
	{ CDRect rect(this); rect.DeflateRect(lpRect); return rect; }
_AFX_INLINE CDRect CDRect::operator&(const DRECT& rect2) const
	{ CDRect rect; rect.IntersectRect(this, &rect2); return rect; }
_AFX_INLINE CDRect CDRect::operator|(const DRECT& rect2) const
	{ CDRect rect; rect.UnionRect(this, &rect2); return rect; }

//////////////////////////////////////////////////////////////////////
//	CLine

_AFX_INLINE	CLine::CLine( )
	{ Construct(); }
_AFX_INLINE	CLine::CLine( CLine& rLine )
	{ Construct( rLine ); }
_AFX_INLINE	CLine::CLine( CStraith& rStraith )
	{ Construct( rStraith ); }
_AFX_INLINE	CLine::CLine( DPOINT& rP1, DPOINT& rP2 )
	{ Construct( rP1, rP2 ); }
_AFX_INLINE	CLine::CLine( DPOINT& rP, double angle )
	{ }
_AFX_INLINE	CLine::CLine( double x0, double y0, double x1, double y1 )
	{ Construct( x0, y0, x1, y1 ); }
_AFX_INLINE	CLine::CLine( double a, double b, double c )
	{ Construct( a, b, c ); }

_AFX_INLINE	void CLine::Construct( )
	{ m_A = m_B = m_C = 0; }
_AFX_INLINE	void CLine::Construct( CLine& rL )
	{ m_A = rL.m_A; m_B = rL.m_B; m_C = rL.m_C; }
_AFX_INLINE	void CLine::Construct( CStraith& rS )
	{ m_A = rS.P1().y - rS.P0().y; m_B = rS.P0().x - rS.P1().x; m_C = rS.P1().x * rS.P0().y - rS.P0().x * rS.P1().y; }
_AFX_INLINE	void CLine::Construct( DPOINT& rP0, DPOINT& rP1 )
	{ m_A = rP1.y - rP0.y; m_B = rP0.x - rP1.x; m_C = rP1.x * rP0.y - rP0.x * rP1.y; }
_AFX_INLINE	void CLine::Construct( double x0, double y0, double x1, double y1 )
	{ m_A = y1 - y0; m_B = x0 - x1; m_C = x1 * y0 - x0 * y1; }
_AFX_INLINE	void CLine::Construct( double a, double b, double c )
	{ m_A = a; m_B = b; m_C = c; }

_AFX_INLINE	const double CLine::A() const
	{ return m_A; }
_AFX_INLINE	const double CLine::B() const
	{ return m_B; }
_AFX_INLINE	const double CLine::C() const
	{ return m_C; }

_AFX_INLINE CLine& CLine::operator=( CLine& rL )
	{ m_A = rL.m_A; m_B = rL.m_B; m_C = rL.m_C; return *this; }

_AFX_INLINE BOOL operator==( CLine& rL1, CLine& rL2 )
	{ return rL1.A() == rL2.A() && rL1.B() == rL2.B() && rL1.C() == rL2.C(); }
_AFX_INLINE BOOL operator!=( CLine& rL1, CLine& rL2 )
	{ return !operator==( rL1, rL2 ); }

//////////////////////////////////////////////////////////////////////
//	CStraith

_AFX_INLINE	CStraith::CStraith( )
	{ Construct(); }
_AFX_INLINE	CStraith::CStraith( CStraith& rS )
	{ Construct( rS ); }
_AFX_INLINE	CStraith::CStraith( DPOINT& p0, DPOINT& p1 )
	{ Construct( p0, p1 ); }
_AFX_INLINE	CStraith::CStraith( double x0, double y0, double x1, double y1 )
	{ Construct( x0, y0, x1, y1 ); }

_AFX_INLINE	void CStraith::Construct( )
	{ m_P0.x = m_P0.y = m_P1.x = m_P1.y = 0; }
_AFX_INLINE	void CStraith::Construct( CStraith& rS )
	{ m_P0 = rS.m_P0; m_P1 = rS.m_P1; }
_AFX_INLINE	void CStraith::Construct( DPOINT& rP0, DPOINT& rP1 )
	{ m_P0 = rP0; m_P1 = rP1; }
_AFX_INLINE	void CStraith::Construct( double x0, double y0, double x1, double y1 )
	{ m_P0.x = x0; m_P0.y = y0; m_P1.x = x1; m_P1.y = y1; }

_AFX_INLINE	const DPOINT CStraith::P0( ) const
	{ return m_P0; }
_AFX_INLINE	const DPOINT CStraith::P1( ) const
	{ return m_P1; }

_AFX_INLINE CStraith& CStraith::operator=( CStraith& rS )
	{ m_P0 = rS.m_P0; m_P1 = rS.m_P1; return *this; }

_AFX_INLINE BOOL operator==( CStraith& rS1, CStraith& rS2 )
	{	return rS1.P0() == rS2.P0() && rS1.P1() == rS2.P1(); }
_AFX_INLINE BOOL operator!=( CStraith& rS1, CStraith& rS2 )
	{ return !operator==( rS1, rS2 ); }

//////////////////////////////////////////////////////////////////////
// common helpers

_AFX_INLINE BOOL operator==( const POINT& rP1, const POINT& rP2 )
	{ return rP1.x == rP2.x && rP1.y == rP2.y; }
_AFX_INLINE BOOL operator!=( const POINT& rP1, const POINT& rP2 )
	{ return !( rP1 == rP2 ); }

_AFX_INLINE BOOL operator==( const POINTL& rP1, const POINTL& rP2 )
	{ return rP1.x == rP2.x && rP1.y == rP2.y; }
_AFX_INLINE BOOL operator!=( const POINTL& rP1, const POINTL& rP2 )
	{ return !( rP1 == rP2 ); }

_AFX_INLINE BOOL operator==( const DPOINT& rP1, const DPOINT& rP2 )
	{ return rP1.x == rP2.x && rP1.y == rP2.y; }
_AFX_INLINE BOOL operator!=( const DPOINT& rP1, const DPOINT& rP2 )
	{ return !( rP1 == rP2 ); }

_AFX_INLINE double Distance( long X0, long Y0, long X1, long Y1 )
{ double dx = (X1 - X0), dy = (double) (Y1 - Y0);
	return sqrt( dx * dx + dy * dy ); }
_AFX_INLINE double Distance( POINT& rP1, POINT& rP2 )
{ double dx = rP2.x - rP1.x, dy = rP2.y - rP1.y;
	return sqrt( dx * dx + dy * dy ); }
_AFX_INLINE double Distance( POINTL& rP1, POINTL& rP2 )
{ double dx = rP2.x - rP1.x, dy = rP2.y - rP1.y;
	return sqrt( dx * dx + dy * dy ); }
_AFX_INLINE double Distance( DPOINT& rP1, DPOINT& rP2 )
{ double dx = rP2.x - rP1.x, dy = rP2.y - rP1.y;
	return sqrt( dx * dx + dy * dy ); }
_AFX_INLINE long froundl( double v )
	{ return (long) ( v < 0 ? v - 0.5 : v + 0.5); }
_AFX_INLINE short frounds( double v )
	{ return (short) ( v < 0 ? v - 0.5 : v + 0.5); }

//////////////////////////////////////////////////////////////////////
// CVector

_AFX_INLINE CVector::CVector( )
	{ m_r = 0; m_data = NULL; }

_AFX_INLINE CVector::CVector( const short r )
	{ m_r = 0; m_data = NULL; Construct( r ); }

_AFX_INLINE CVector::CVector( const short r, const double *v )
	{ m_r = 0; m_data = NULL; Construct( r ); memcpy( m_data, v, m_r * sizeof( double ) ); }

_AFX_INLINE CVector::CVector( const CVector& rV )
	{ m_r = 0; m_data = NULL; Copy( rV ); }

_AFX_INLINE CVector::~CVector( )
	{ if( NULL != m_data ) delete[] m_data; }

_AFX_INLINE const short CVector::R() const
	{ return m_r; }

_AFX_INLINE double& CVector::operator()( short i )
	{ return m_data[ i ]; }
_AFX_INLINE const double CVector::operator()( short i ) const
	{ return m_data[ i ]; }

_AFX_INLINE void CVector::Clear( )
	{ memset( (void*) m_data, 0x00, m_r * sizeof( double ) ); }

_AFX_INLINE CVector& CVector::operator=( CVector& rV )
	{ Copy( rV ); return *this; }

//////////////////////////////////////////////////////////////////////
// CMatrix

_AFX_INLINE 	CMatrix::CMatrix( )
	{ m_r = m_c = 0; m_data = NULL; }

_AFX_INLINE 	CMatrix::CMatrix( short n )
	{ m_r = m_c = 0; m_data = NULL; Construct( n ); }

_AFX_INLINE 	CMatrix::CMatrix( short n, double *v )
	{ m_r = m_c = 0; m_data = NULL; Construct( n ); memcpy( m_data, v, m_r * m_c * sizeof( double ) ); }

_AFX_INLINE 	CMatrix::CMatrix( short r, short c )
	{ m_r = m_c = 0; m_data = NULL; Construct( r, c ); }

_AFX_INLINE 	CMatrix::CMatrix( short r, short c, double *v )
	{ m_r = m_c = 0; m_data = NULL; Construct( r, c ); memcpy( m_data, v, m_r * m_c * sizeof( double ) ); }

_AFX_INLINE 	CMatrix::~CMatrix( )
	{ if( NULL != m_data ) delete[] m_data; }

_AFX_INLINE 	CMatrix::CMatrix( CMatrix& rM )
	{ m_r = m_c = 0; m_data = NULL; Copy( rM ); }

_AFX_INLINE 	const short	CMatrix::R( ) const
	{ return m_r; }

_AFX_INLINE 	const short	CMatrix::C( ) const
	{ return m_c; }

_AFX_INLINE 	const double CMatrix::operator()( short i, short j ) const
	{ return m_data[ m_c * i + j ]; }
_AFX_INLINE 	double&	CMatrix::operator()( short i, short j )
	{ return m_data[ m_c * i + j ]; }

_AFX_INLINE 	void		CMatrix::Clear( )
	{ memset( (void*) m_data, 0x00, m_r * m_c * sizeof( double ) ); }

_AFX_INLINE 	CMatrix&	CMatrix::operator=( const CMatrix& rM )
	{ Copy( rM ); return *this; }

#endif //_AFX_INLINE
