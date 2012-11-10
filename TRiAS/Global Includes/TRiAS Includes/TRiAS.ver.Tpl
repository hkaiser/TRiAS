#if defined(__midl)
	cpp_quote("#define TYPELIB_@L_VERSION_MAJOR @D")
	cpp_quote("#define TYPELIB_@L_VERSION_MINOR @E")
	cpp_quote("#define TYPELIB_@L_VERSION \"@D.@E\"")
	cpp_quote("#define TYPELIB_@L_LCID 0")
	#define TYPELIB_@L_VERSION_MAJOR	@D
	#define TYPELIB_@L_VERSION_MINOR	@E
	#define TYPELIB_@L_VERSION			@D.@E
	#define TYPELIB_@L_LCID				0
	#define TYPELIB_@L_HELPSTRING		"TRiAS® @M V@D.@E"
#else
	#define	TRIAS_MAJOR	@I
	#define	TRIAS_MINOR	@J

	#define	APP_VERSION	@A
	#define	APP_RELEASE	@B
	#define	APP_BUILD	@C
	#define	APP_STRING	"TRiAS® @M V@A.@B.@C"
	#define	STR_TRIAS_MAJOR	_T("@I")
	#define	STR_TRIAS_MINOR	_T("@J")
	#define	STR_APP_NAME	_T("@L")
	#define	STR_APP_VERSION	_T("@A")
	#define	STR_APP_RELEASE	_T("@B")
	#define	STR_APP_BUILD	_T("@C")
#endif

