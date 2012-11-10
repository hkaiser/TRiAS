#if defined(_M_I86MM) || defined(_M_I86LM) // far code
#define LAFX_CORE_SEG	"LAFX_CORE_TEXT"
#define LAFX_COLL_SEG	"LAFX_COLL_TEXT"
#define LAFX_FUNC_SEG	"LAFX_FUNC_TEXT"
#define LAFX_GEOM_SEG	"LAFX_GEOM_TEXT"
#define LAFX_MATH_SEG	"LAFX_MATH_TEXT"

#define LAFX_WINC_SEG	"LAFX_WINC_TEXT"		// Windows I (classes)
#define LAFX_WINF_SEG	"LAFX_WINF_TEXT"		// Windows II (functions)

#define LAFX_ODBC_SEG	"LAFX_ODBC_TEXT"  		// ODBC
#endif

#ifdef _DOS
#include	<lafx_dos.h>
#endif

/////////////////////////////////////////////////////////////////////
// verschiedene Definitionen, die erst bei MFC3/4... auftauchen, aber
// durchaus sinnvoll sind

#if _MFC_VER < 0x0400
#define	ASSERT_KINDOF( ClassName, pObject ) \
	ASSERT( NULL != pObject );	\
	ASSERT( (pObject)->IsKindOf( RUNTIME_CLASS( ClassName ) ) )
#endif // _MFC_VER < 0x0400

#ifdef _AFXDLL
	#if _MFC_VER == 0x0400
		#if defined(_DEBUG)
			#define THIS_DLL "lmfcx40d.dll"
			#define IMPORT_THIS_DLL "lmfcx40d.lib"
		#elif defined(_RDEBUG)
			#define THIS_DLL "lmfcx40r.dll"
			#define IMPORT_THIS_DLL "lmfcx40r.lib"
		#else
			#define THIS_DLL "lmfcx40.dll"
			#define IMPORT_THIS_DLL "lmfcx40.lib"
		#endif
	#elif _MFC_VER >= 0x0420
		#if defined(_DEBUG)
			#define THIS_DLL "lmfcx42d.dll"
			#define IMPORT_THIS_DLL "lmfcx42d.lib"
		#elif defined(_RDEBUG)
			#define THIS_DLL "lmfcx42r.dll"
			#define IMPORT_THIS_DLL "lmfcx42r.lib"
		#else
			#define THIS_DLL "lmfcx42.dll"
			#define IMPORT_THIS_DLL "lmfcx42.lib"
		#endif
	#endif	// _MFC_VER
#endif	// _AFXDLL

/////////////////////////////////////////////////////////////////////
// Definitionen für DLL-Version

#if _MFC_VER < 0x0400 // && defined( _AFXDLL )
#define	AFX_EXT_CLASS
#define AFX_EXT_API
#endif

/////////////////////////////////////////////////////////////////////
// POINTL gibt es erst unter 32 bit; Definition für 16 bit bereitstellen
