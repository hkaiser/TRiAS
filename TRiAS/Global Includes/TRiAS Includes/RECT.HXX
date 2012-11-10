// Operatoren fuer Rectangle --------------------------------------------------
// File: RECT.HXX

#if !defined(_RECT_HXX)

_TRIAS02_ENTRY bool EXPORT02 operator ! (Rectangle &);
_TRIAS02_ENTRY bool EXPORT02 operator ^ (Rectangle &, Rectangle &);
_TRIAS02_ENTRY Rectangle EXPORT02 operator & (Rectangle &, Rectangle &);
_TRIAS02_ENTRY Rectangle EXPORT02 operator + (Rectangle &, Rectangle &);

#endif // _RECT_HXX

