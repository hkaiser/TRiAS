/*
 *  INT64.H   C++ class implementation for
 *  -------   Windows NT 64 bit integer arithmetic
 *
 */

#include <largeint.h>


class LARGE {
public:
  // constructors
  inline LARGE() {};
  inline LARGE(INT n);
  inline LARGE(UINT u);
  inline LARGE(UINT uLow, INT nHigh);
  inline LARGE(LARGE_INTEGER li);
  inline LARGE(ULARGE_INTEGER uli);
  inline LARGE(FILETIME ft);
  // unary operators
  inline LARGE operator-();
  // binary operators
  inline LARGE operator+(LARGE lg);
  inline LARGE operator-(LARGE lg);
  inline LARGE operator*(INT n);
  friend LARGE operator*(INT n1, LARGE lg2);
  inline LARGE operator/(LARGE lg);
  inline LARGE operator/(UINT u);
  inline LARGE operator%(LARGE lg);
  inline UINT  operator%(UINT u);
  inline LARGE operator<<(INT nShift);
  inline LARGE operator>>(INT nShift);
  inline LARGE operator&(LARGE lg);
  // comparations
  friend BOOL operator<(LARGE lg1, LARGE lg2);
  friend BOOL operator<=(LARGE lg1, LARGE lg2);
  friend BOOL operator==(LARGE lg1, LARGE lg2);
  friend BOOL operator!=(LARGE lg1, LARGE lg2);
  friend BOOL operator>=(LARGE lg1, LARGE lg2);
  friend BOOL operator>(LARGE lg1, LARGE lg2);
  // cast operators
  inline operator UINT();
  inline operator INT();
  inline operator FILETIME();
  // special functions
  friend LARGE Product(INT n1, INT n2);
  friend LARGE Product(UINT u1, UINT u2);
  inline VOID MagicDivide(LARGE lgMagicDivisor, CCHAR ShiftCount);
  inline INT GetHigher();
  inline UINT GetLower();

  inline operator LARGE_INTEGER &();
  inline operator ULARGE_INTEGER &();

// friendly functions
inline friend LARGE operator*(INT l1, LARGE lg2);
inline friend BOOL operator<(LARGE lg1, LARGE lg2);
inline friend BOOL operator<=(LARGE lg1, LARGE lg2);
inline friend BOOL operator==(LARGE lg1, LARGE lg2);
inline friend BOOL operator!=(LARGE lg1, LARGE lg2);
inline friend BOOL operator>=(LARGE lg1, LARGE lg2);
inline friend BOOL operator>(LARGE lg1, LARGE lg2);
inline friend LARGE Product(INT n1, INT n2);
inline friend LARGE Product(UINT u1, UINT u2);

  LARGE_INTEGER li;
}; /* prefix "lg" */


/* ----------------------
   inline implementations
   ----------------------
*/

LARGE::LARGE(INT n)
{
  li = ConvertLongToLargeInteger(n);
} /* LARGE() */


LARGE::LARGE(UINT u)
{
  li = ConvertUlongToLargeInteger(u);
} /* LARGE() */


LARGE::LARGE(UINT uLow, INT nHigh)
{
  li.LowPart = uLow;
  li.HighPart = nHigh;
} /* LARGE() */

LARGE::LARGE(LARGE_INTEGER arg)
{
  li.LowPart = arg.LowPart;
  li.HighPart = arg.HighPart;
}

LARGE::LARGE(ULARGE_INTEGER arg)
{
  li.LowPart = arg.LowPart;
  li.HighPart = arg.HighPart;
}

LARGE::LARGE(FILETIME ft)
{
  li.LowPart = ft.dwLowDateTime;
  _ASSERTE(ft.dwHighDateTime <= LONG_MAX);
  li.HighPart = ft.dwHighDateTime;
} /* LARGE() */


LARGE LARGE::operator-()
{
  LARGE lgResult;
  lgResult.li = LargeIntegerNegate(li);
  return lgResult;
} /* operator- */


LARGE LARGE::operator+(LARGE lg)
{
  LARGE lgResult;
  lgResult.li = LargeIntegerAdd(li, lg.li);
  return lgResult;
} /* operator+ */


LARGE LARGE::operator-(LARGE lg)
{
  LARGE lgResult;
  lgResult.li = LargeIntegerSubtract(li, lg.li);
  return lgResult;
} /* operator+ */


LARGE LARGE::operator*(INT n)
{
  LARGE lgResult;
  lgResult.li = ExtendedIntegerMultiply(li, n);
  return lgResult;
} /* operator*() */


LARGE operator*(INT n1, LARGE lg2)
{
  LARGE lgResult;
  lgResult.li = ExtendedIntegerMultiply(lg2.li, n1);
  return lgResult;
} /* operator*() */


LARGE LARGE::operator/(LARGE lg)
{
  LARGE lgResult;
  lgResult.li = LargeIntegerDivide(li, lg.li, NULL);
  return lgResult;
} /* operator/() */


LARGE LARGE::operator/(UINT u)
{
  LARGE lgResult;
  lgResult.li = ExtendedLargeIntegerDivide(li, u, NULL);
  return lgResult;
} /* operator/() */


LARGE LARGE::operator%(LARGE lg)
{
  LARGE lgResult;
  LargeIntegerDivide(li, lg.li, &lgResult.li);
  return lgResult;
} /* operator%() */


UINT LARGE::operator%(UINT u)
{
  ULONG ulRmd;
  ExtendedLargeIntegerDivide(li, u, &ulRmd);
  return (UINT)ulRmd;
} /* operator%() */


LARGE LARGE::operator<<(INT nShift)
{
  LARGE lgResult;
  lgResult.li = LargeIntegerShiftLeft(li, nShift);
  return lgResult;
} /* operator<<() */


LARGE LARGE::operator>>(INT nShift)
{
  LARGE lgResult;
  // shift sign-based (arithmetic)
  lgResult.li = LargeIntegerArithmeticShift(li, nShift);
  return lgResult;
} /* operator>>() */


LARGE LARGE::operator&(LARGE lg)
{
  LARGE lgResult;
  LargeIntegerAnd(lgResult.li, li, lg.li);
  return lgResult;
} /* operator&() */


inline BOOL operator<(LARGE lg1, LARGE lg2)
{
 return LargeIntegerLessThan(lg1.li, lg2.li);
} /* operator< */


inline BOOL operator<=(LARGE lg1, LARGE lg2)
{
  return LargeIntegerLessThanOrEqualTo(lg1.li, lg2.li);
} /* operator<= */


inline BOOL operator==(LARGE lg1, LARGE lg2)
{
  return LargeIntegerEqualTo(lg1.li, lg2.li);
} /* operator== */


inline BOOL operator!=(LARGE lg1, LARGE lg2)
{
  return LargeIntegerNotEqualTo(lg1.li, lg2.li);
} /* operator!= */


inline BOOL operator>=(LARGE lg1, LARGE lg2)
{
  return LargeIntegerGreaterThanOrEqualTo(lg1.li, lg2.li);
} /* operator>= */


inline BOOL operator>(LARGE lg1, LARGE lg2)
{
  return LargeIntegerGreaterThan(lg1.li, lg2.li);
} /* operator> */


LARGE::operator INT()
{
  return (INT)li.LowPart;
} /* operator long() */


LARGE::operator UINT()
{
  return (UINT)li.LowPart;
} /* operator int() */


LARGE::operator FILETIME()
{
  FILETIME ft;
  ft.dwLowDateTime = li.LowPart;
  _ASSERTE(li.HighPart >= 0);
  ft.dwHighDateTime = li.HighPart;
  return ft;
} /* operator int() */

LARGE::operator LARGE_INTEGER & (void)
{
	return li;
}

LARGE::operator ULARGE_INTEGER & (void)
{
	return (ULARGE_INTEGER &)li;
}

LARGE Product(INT n1, INT n2)
{
  LARGE lgResult;
  lgResult.li = EnlargedIntegerMultiply(n1, n2);
  return lgResult;
} /* Product() */


LARGE Product(UINT u1, UINT u2)
{
  LARGE lgResult;
  lgResult.li = EnlargedUnsignedMultiply(u1, u2);
  return lgResult;
} /* Product() */


VOID LARGE::MagicDivide(LARGE lgMagicDivisor, CCHAR ShiftCount)
{
  li = ExtendedMagicDivide(li, lgMagicDivisor.li, ShiftCount);
} /* MagicDivide() */


INT LARGE::GetHigher()
{
  return (INT)li.HighPart;
} /* GetHigherLong() */


UINT LARGE::GetLower()
{
  return (UINT)li.LowPart;
} /* GetLowerLong() */

/* ==============
   end of int64.h
   ============== */