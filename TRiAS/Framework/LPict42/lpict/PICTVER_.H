#if defined(_M_I86MM) || defined(_M_I86LM) // far code
#define LAFX_PICT_SEG	"LAFX_PICT_TEXT"		// Pictures
#endif

#ifdef _AFXDLL
	#if _MFC_VER == 0x0400
		#if defined(_DEBUG)
			#define PICT_DLL "lpict40d.dll"
			#define IMPORT_PICT_DLL "lpict40d.lib"
		#elif defined(_RDEBUG)
			#define PICT_DLL "lpict40r.dll"
			#define IMPORT_PICT_DLL "lpict40r.lib"
		#else
			#define PICT_DLL "lpict40.dll"
			#define IMPORT_PICT_DLL "lpict40.lib"
		#endif
	#elif _MFC_VER >= 0x0420
		#if defined(_DEBUG)
			#define PICT_DLL "lpict42d.dll"
			#define IMPORT_PICT_DLL "lpict42d.lib"
		#elif defined(_RDEBUG)
			#define PICT_DLL "lpict42r.dll"
			#define IMPORT_PICT_DLL "lpict42r.lib"
		#else
			#define PICT_DLL "lpict42.dll"
			#define IMPORT_PICT_DLL "lpict42.lib"
		#endif
	#endif	// _MFC_VER
#else
#error "Weder _AFXDLL noch _COMOBJECT definiert"
#endif	// _AFXDLL

#if _MFC_VER < 0x0400
#define	AFX_EXT_CLASS
#define AFX_EXT_API
#endif
