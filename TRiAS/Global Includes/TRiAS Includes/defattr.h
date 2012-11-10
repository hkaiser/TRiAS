// StandardAttribute ----------------------------------------------------------
// File: DEFATTR.H

#if !defined(_DEFATTR_H)
#define _DEFATTR_H

#define DEF_STYLE 		0
#define DEF_STYLE_PUNKT		3
#define DEF_STYLE_TEXT		FF_SWISS

#define DEF_PRIO 		500

#if defined(__CV__)
#define DEF_COLOR 		(Color((ColorVal)0,(ColorVal)0,(ColorVal)0))
#define DEF_SECCOLOR	(Color((ColorVal)0xff, (ColorVal)0xff, (ColorVal)0xff))
#else
#define DEF_COLOR 		(Color((ColorVal)0,(ColorVal)0,(ColorVal)0))
#define DEF_SECCOLOR	(Color((ColorVal)0xff, (ColorVal)0xff, (ColorVal)0xff))
#endif

#undef DEF_PRIORITY
#define DEF_PRIORITY		500	// Standard-DarstellungsPriorität
#define DEF_PRIORITY_FLAECHE	200
#define DEF_PRIORITY_LINIE	400
#define DEF_PRIORITY_PUNKT	600
#define DEF_PRIORITY_TEXT	800

#define DEF_SIZE_PUNKT_X	200
#define DEF_SIZE_PUNKT_Y	200
#if defined(__CV__)
#define DEF_SIZE_PUNKT		(Dimension(DEF_SIZE_PUNKT_X,DEF_SIZE_PUNKT_Y))
#else
#define DEF_SIZE_PUNKT		(CSize(DEF_SIZE_PUNKT_X,DEF_SIZE_PUNKT_Y))
#endif

#define DEF_SIZE_TEXT_X		0
#define DEF_SIZE_TEXT_Y		-14
#if defined(__CV__)
#define DEF_SIZE_TEXT		(Dimension(DEF_SIZE_TEXT_X,DEF_SIZE_TEXT_Y))
#else
#define DEF_SIZE_TEXT		(CSize(DEF_SIZE_TEXT_X,DEF_SIZE_TEXT_Y))
#endif

#define DEF_WIDTH_LINIE		0
#define DEF_WIDTH_FRAME		0

#define DEF_FONT_TEXT		"Arial"
#define DEF_TYP_TEXT		0x0

#if !defined(VISNAMESIZE)
#define VISNAMESIZE		32
#endif

#endif // _DEFATTR_H
