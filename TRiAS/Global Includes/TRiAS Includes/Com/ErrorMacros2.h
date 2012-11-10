// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 07.11.2002 21:07:22 
//
// @doc
// @module ErrorMacros2.h | Declaration of the <c CErrorMacros2> class

#if !defined(_ERRORMACROS2_A677EDC0_4812_11d2_8FB8_0060085FC1CE)
#define	_ERRORMACROS2_A677EDC0_4812_11d2_8FB8_0060085FC1CE

#if !defined(_NO_ERROR_MACROS)

///////////////////////////////////////////////////////////////////////////////
// @doc ERROR TRiASDB
// @module ErrorMacros2.h | Fehlermakros

#import "tlb/TErrTrk.tlb"	\
	raw_interfaces_only \
	raw_dispinterfaces	\
	no_namespace \
	named_guids

//DefineSmartInterface(ErrorStack)
//DefineSmartInterface(ErrorInfo)
//DefineSmartInterface(CreateErrorInfo)

//////////////////////////////////////////////////////////////////////////////
// Supportfunktionen
#if defined(_DEBUG)
inline int __cdecl _FailHRReport(int type, LPCTSTR strFile, int line, LPCTSTR strModuleName, LPCTSTR strFormat ) {
	USES_CONVERSION;
	CComBSTR strExpr(A2W(strFormat));
	IErrorInfo *ei = NULL;
	GetErrorInfo( 0, &ei );
	if(ei) {
		CComBSTR strInfo;
		ei->GetDescription(&strInfo);
		SetErrorInfo( 0, ei );	// aktuellen Fehlerstatus unverändert lassen!
		ei->Release();
		strExpr.Append(_T("\r\n")); 
		strExpr.Append(strInfo);
	}
	return _CrtDbgReport(type, strFile, line, strModuleName, W2A(strExpr) );
}

inline int __cdecl FormatDebuggerLine( CComBSTR& strMsg, HRESULT hr, LPCTSTR strFilename, long line, LPCTSTR strExpr ) {
	TCHAR	msgBuf[4096];
	try {
		wsprintf( msgBuf, _T("%s(%ld): [0x%08lx] = %s"), strFilename, line, hr, strExpr );
		strMsg = msgBuf;
	} catch(...) {
		return 0;
	}
	return 1;
}
#endif //_DEBUG

#if defined(_DEBUG)
#define __RETURN_FAILED_HRESULT(expr)									\
	{ HRESULT __hr=(expr); if(!SUCCEEDED(__hr))	{						\
		do { if( 1 == _FailHRReport(_CRT_ASSERT, __FILE__, __LINE__, NULL, #expr ) ) _CrtDbgBreak(); } while (0); \
		return(__hr);													\
	} }
#else
#define __RETURN_FAILED_HRESULT(expr)									\
	{ HRESULT __hr=(expr); if(!SUCCEEDED(__hr))	{						\
		return(__hr);													\
	} }
#endif	//_DEBUG

#if defined(_DEBUG)
#define __RETURN_EXPR_TRUE(expr,hr)										\
	{ if(expr) {														\
		do { if( 1 == _FailHRReport(_CRT_ASSERT, __FILE__, __LINE__, NULL, #expr ) ) _CrtDbgBreak(); } while (0); \
		return hr;														\
	} }
#else
#define __RETURN_EXPR_TRUE(expr,hr)										\
	{ if(expr) return hr; }	
#endif

#if defined(_DEBUG)
#define __EXT_RETURN_FAILED_HRESULT(expr)								\
	{ SetErrorInfo(0,NULL); HRESULT __hr=(expr); if(FAILED(__hr))	{	\
		PushError();													\
		do { if( 1 == _FailHRReport(_CRT_ASSERT, __FILE__, __LINE__, NULL, #expr ) ) _CrtDbgBreak(); } while (0); \
		return(__hr);													\
	} }
#else
#define __EXT_RETURN_FAILED_HRESULT(expr)								\
	{ SetErrorInfo(0,NULL); HRESULT __hr=(expr); if(FAILED(__hr))	{	\
		PushError();													\
		return(__hr);													\
	} }
#endif	//_DEBUG

//////////////////////////////////////////////////////////////////////////////
// Fehler in Systemfunktionen (diese setzen ::SetLastError() )
#if defined(_DEBUG)
#define __SYS_ERROR(expr,hr)											\
	{ if(expr) {														\
		DWORD err = HRESULT_FROM_WIN32( ::GetLastError() );				\
		(this)->GenerateError(#expr, __FILE__, __LINE__, err);			\
		PushError();													\
		do { if( 1 == _FailHRReport(_CRT_ASSERT, __FILE__, __LINE__, NULL, #expr ) ) _CrtDbgBreak(); } while (0); \
		(this)->GenerateError(#expr, __FILE__, __LINE__, hr);			\
		PushError();													\
		return hr;														\
	} }
#else
#define __SYS_ERROR(expr,hr)											\
	{ if(expr) {														\
		(this)->GenerateError(HRESULT_FROM_WIN32(::GetLastError()));	\
		PushError();													\
		(this)->GenerateError(hr);										\
		PushError();													\
		return hr;														\
	} }
#endif	//_DEBUG

//////////////////////////////////////////////////////////////////////////////
// Fehler in Windows-API Funktionen (diese liefern mal 0, mal nicht 0 bei Fehler)
#if defined(_DEBUG)
#define __WIN_ERROR_NOTSUCCESS(expr,hr)	\
	{ SCODE __sc=(expr); if(ERROR_SUCCESS != __sc)	{					\
		(this)->GenerateError(#expr, __FILE__, __LINE__, HRESULT_FROM_WIN32(__sc));		\
		PushError();													\
		do { if( 1 == _FailHRReport(_CRT_ASSERT, __FILE__, __LINE__, NULL, #expr ) ) _CrtDbgBreak(); } while (0); \
		return hr;														\
	} }
#else
#define __WIN_ERROR_NOTSUCCESS(expr,hr)	\
	{ SCODE __sc=(expr); if(ERROR_SUCCESS != __sc)	{					\
		(this)->GenerateError(HRESULT_FROM_WIN32(__sc));				\
		PushError();													\
		return hr;														\
	} }
#endif

//////////////////////////////////////////////////////////////////////////////
// Fehler in COM-Funktionen (diese liefern S_OK/S_FALSE)
#if defined(_DEBUG)
#define __CO_ERROR_FAILED_HRESULT(expr,hr)	\
	{ HRESULT __hr=(expr); if(!SUCCEEDED(__hr))	{						\
		(this)->GenerateError(#expr, __FILE__, __LINE__, __hr);			\
		PushError();													\
		do { if( 1 == _FailHRReport(_CRT_ASSERT, __FILE__, __LINE__, NULL, #expr ) ) _CrtDbgBreak(); } while (0); \
		(this)->GenerateError(#expr, __FILE__, __LINE__, hr);			\
		PushError();													\
		return hr;														\
	} }
#else
#define __CO_ERROR_FAILED_HRESULT(expr,hr)	\
	{ HRESULT __hr=(expr); if(!SUCCEEDED(__hr))	{						\
		(this)->GenerateError(__hr);									\
		PushError();													\
		(this)->GenerateError(hr);										\
		PushError();													\
		return hr;														\
	} }
#endif

//////////////////////////////////////////////////////////////////////////////
// ein allgemeiner Expression-Test mit Fehlererzeugung
#if defined(_DEBUG)
#define __ERROR_EXPR_TRUE(expr,hr)										\
	{ if(expr) {														\
		(this)->GenerateError( #expr, __FILE__, __LINE__, hr );			\
		PushError();													\
		do { if( 1 == _FailHRReport(_CRT_ASSERT, __FILE__, __LINE__, NULL, #expr ) ) _CrtDbgBreak(); } while (0); \
		return hr;														\
	} }
#else
#define __ERROR_EXPR_TRUE(expr,hr)										\
	{ if(expr) {														\
		(this)->GenerateError(hr);										\
		PushError();													\
		return hr;														\
	} }
#endif	//_DEBUG

#define __ERROR_EXPR_FALSE(expr,hr)		__ERROR_EXPR_TRUE(!(expr),hr)

//////////////////////////////////////////////////////////////////////////////
// ein allgemeiner Expression-Test mit Fehlererzeugung und 'GegenCode'
#if defined(_DEBUG)
#define __ERROR_EXPR_TRUEEX(expr,hr,code)									\
	{ 	if(expr) {															\
			(this)->GenerateError( #expr, __FILE__, __LINE__, hr );			\
			PushError();													\
			do { if( 1 == _FailHRReport(_CRT_ASSERT, __FILE__, __LINE__, NULL, #expr ) ) _CrtDbgBreak(); } while (0); \
			return hr;														\
		} else { code; } }
#else
#define __ERROR_EXPR_TRUEEX(expr,hr,code)									\
	{	if(expr) {															\
			(this)->GenerateError(hr);										\
			PushError();													\
			return hr;														\
		} else { code; } }
#endif	//_DEBUG

#define __ERROR_EXPR_FALSEEX(expr,hr,code)		__ERROR_EXPR_TRUEEX(!(expr),hr,code)

//////////////////////////////////////////////////////////////////////////////
// COM-Interfaces die bekannterweise das Fehlerobjekt korrekt setzen
// z.B. Geomedia macht das sauber... na mal was ;-)
#if defined(_DEBUG)
#define __EXT_ERROR_FAILED_HRESULT(expr,hr)								\
	{ SetErrorInfo(0,NULL); if(FAILED(expr)) {							\
		PushError();													\
		do { if( 1 == _FailHRReport(_CRT_ASSERT, __FILE__, __LINE__, NULL, #expr ) ) _CrtDbgBreak(); } while (0); \
		(this)->GenerateError( #expr, __FILE__, __LINE__, hr );			\
		PushError();													\
		return hr;														\
	} }
#else
#define __EXT_ERROR_FAILED_HRESULT(expr,hr)								\
	{ SetErrorInfo(0,NULL); if(FAILED(expr)) {							\
		PushError();													\
		(this)->GenerateError(hr);										\
		PushError();													\
		return hr;														\
	} }
#endif	//_DEBUG

//////////////////////////////////////////////////////////////////////////////
// COM-Interfaces die kein Fehlerobjekt erzeugen (braucht dann auch nicht 
// gesichert zu werden)

#define __ERROR_FAILED_HRESULT(expr,hr)	__ERROR_EXPR_TRUE(FAILED(expr), hr)

inline void PushError( ) {
	CComQIPtr<IErrorStack,&IID_IErrorStack>	pErr;
	pErr.CoCreateInstance(CLSID_ErrorStack);
	if( !!pErr ) {
		IErrorInfo	*ei = NULL;
		GetErrorInfo( 0, &ei );
		if( ei ) {
			pErr->Push( ei );		// Fehler merken
			SetErrorInfo( 0, ei );	// aktuellen Status unverändert lassen
			ei->Release();
		}
	}
}

#endif // !defined(_NO_ERROR_MACROS)

#if defined(_DEBUG)
HRESULT GenerateError (LPCTSTR strExpr, LPCTSTR strFile, int line, REFCLSID rClsId, REFIID riid, LPCOLESTR pcHelpFile, HRESULT hRes);
HRESULT GenerateErrorV (LPCTSTR strExpr, LPCTSTR strFile, int line, REFCLSID rClsId, REFIID riid, LPCOLESTR pcHelpFile, HRESULT hRes, va_list arglist);
inline HRESULT GenerateErrorE (LPCTSTR strExpr, LPCTSTR strFile, int line, REFCLSID rClsId, REFIID riid, LPCOLESTR pcHelpFile, HRESULT hRes, ...) {
	va_list argList;
	va_start(argList, hRes);
	HRESULT hr = ::GenerateErrorV(strExpr, strFile, line, rClsId, riid, pcHelpFile, hRes, argList);
	va_end(argList);
	return hr;
}
#else
HRESULT GenerateError (REFCLSID rClsId, REFIID riid, LPCOLESTR pcHelpFile, HRESULT hRes);
HRESULT GenerateErrorV (REFCLSID rClsId, REFIID riid, LPCOLESTR pcHelpFile, HRESULT hRes, va_list arglist);
inline HRESULT GenerateErrorE (REFCLSID rClsId, REFIID riid, LPCOLESTR pcHelpFile, HRESULT hRes, ...) {
	va_list argList;
	va_start(argList, hRes);
	HRESULT hr = ::GenerateErrorV(rClsId, riid, pcHelpFile, hRes, argList);
	va_end(argList);
	return hr;
}
#endif

///////////////////////////////////////////////////////////////////////////////
// @class CErrSupport | Basisklasse für die Fehlerbendlung.
// @normal CErrSupport ist Grundlage für das Funktionieren der Makros
// @index func | ERREXPR

template< class T, const IID *pIID>
class CErrSupport : public ISupportErrorInfoImpl<pIID> {
	static LPCOLESTR GetHelpFileName( ) { return NULL; }
public:
	typedef CErrSupport<T, pIID> CErrSupport_t;
	typedef CErrSupport<T, pIID> errsupport_t;		// obsolete, sollte nicht mehr verwendet werden!

	BEGIN_COM_MAP(CErrSupport)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

#if defined(_DEBUG)
	HRESULT GenerateErrorV (LPCTSTR strExpr, LPCTSTR strFile, int line, HRESULT hRes, ...) {
		_ASSERTE( S_OK == (this->InterfaceSupportsErrorInfo( *pIID )) );
		va_list argList;
		va_start(argList, hRes );
		HRESULT hr = ::GenerateErrorV(strExpr, strFile, line, T::GetObjectCLSID(), *pIID, GetHelpFileName(), hRes, arglist);
		va_end(argList);
		return hr;
	}
	virtual HRESULT GenerateError (LPCTSTR strExpr, LPCTSTR strFile, int line, HRESULT hRes) {
		_ASSERTE( S_OK == (this->InterfaceSupportsErrorInfo( *pIID )) );
		return ::GenerateError(strExpr, strFile, line, T::GetObjectCLSID(), *pIID, GetHelpFileName(), hRes);
	}
#else
	HRESULT GenerateErrorV (HRESULT hRes, ...) {
		va_list argList;
		va_start(argList, hRes);
		HRESULT hr = ::GenerateErrorV(T::GetObjectCLSID(), *pIID, GetHelpFileName(), hRes, arglist);
		va_end(argList);
		return hr;
	}
	virtual HRESULT GenerateError (HRESULT hRes) {
		return ::GenerateError(T::GetObjectCLSID(), *pIID, GetHelpFileName(), hRes);
	}
#endif // _DEBUG
};

#if !defined(_NO_ERROR_MACROS)

///////////////////////////////////////////////////////////////////////////////
// @doc ERROR MACRO TRiASDB
// @func DECLARE_ERRSUPPORTENTRY(Class,pIID) | Unterstützung für Fehlerbehandlung bei
//		Multiple Inheritance
// @normal Die Behandlung von Fehlern ist stets an die Klasse gebunden für die
//		CErrSupport\<Class,pIID\> Basisklasse ist. Wird eine Klasse von mehreren
//		Klassen abgeleitet die CErrSupport als Basisklasse haben muß dem Fehlermakros
//		die Möglichkeit gegeben werden die korrekte Funktion zur Fehlerbehandlung
//		auszuwählen. Dazu wird über DECLARE_ERRSUPPORTENTRY(cls) ein entsprechender
//		Eintrittspunkt geschaffen.
// @ex |
//		template <class T, const IID* pIID> class CFoo
//			: public InterfaceOfFoo
//			, public CErrSupport<T, &IID_InterfaceOfFoo>
//		{
//		public:
//			STDMETHOD(FFoo)( IUnknown* p) {
//				CHECKINPOINTER(p);
//				return S_OK;
//			}
//		};
//		template <class T, const IID* pIID> class CBar
//			: public InterfaceOfBar
//			, public CErrSupport<T, &IID_InterfaceOfBar>
//		{
//		public:
//			STDMETHOD(FBar)( IUnknown* p) {
//				CHECKINPOINTER(p);
//				return S_OK;
//			}
//		};
//		class ATL_NO_VTABLE CFooBar
//			: public CComObjectRootEx<CComSingleThreadModel>
//			...
//			, public InterfaceOfFooBar
//			, public CFoo<CFooBar,&IID_IFooBar>
//			, public CBar<CFooBar,&IID_IFooBar>
//		{
//			DECLARE_ERRSUPPORTENTRY(CFooBar,&IID_InterfaceOfFooBar)	// Fehler ohne diesen Eintrag!
//		public:
//			STDMETHOD(FFooBar)( IUnknown* p) {
//				CHECKINPOINTER(p);
//				return S_OK;
//			}
//		}

#if defined(_DEBUG)
#define	DECLARE_ERRSUPPORTENTRY(cls,pIID) HRESULT GenerateError (LPCTSTR strExpr, LPCTSTR strFile, int line, HRESULT hRes) {	\
		do { return CErrSupport<cls,pIID>::GenerateError( strExpr, strFile, line, hRes); } while(0); \
	}
#else
#define	DECLARE_ERRSUPPORTENTRY(cls,pIID) HRESULT GenerateError (HRESULT hRes) {	\
		do { return CErrSupport<cls,pIID>::GenerateError( hRes); } while(0); \
	}
#endif

//////////////////////////////////////////////////////////////////////////////////
// @doc ERROR MACRO TRiASDB
// @func | CLEAN_ERROR |
//		Setzt das Fehlerobjekt zurück
// @devnote dieses Makro sollte stets am Eingang von Funktionen die Fehlerobjekte
//		erzeugen können, ausgeführt werden
#define	CLEAN_ERROR()		{ SetErrorInfo(0,NULL); }
// @func | MAKE_ERROR |
//		Erzeugt ein Fehlerobjekt mit dem Status <l STATUS_SEVERITY_ERROR>
#define	MAKE_ERROR(hr)						__ERROR_EXPR_TRUE(#hr,hr)
// @func | SYS_ERROR |
//		SYS_ERROR kann für die Behandlung von Fehlern in den Systemfunktionen eingesetzt werden.
//		Die Fehlerbedingung wird durch (expr)==true gegeben. SYS_ERROR liest den aufgetreten Fehler
//		mit ::GetLastError() aus und erzeugt daraus einen gültigen HRESULT-Code. 
// @normal Momentan wird nur der durch ::GetLastError() gelieferte Fehlercode im Stack abgelegt,
//		der zweite Makroparameter aber nicht weiter ausgewertet. Dieser muß aus Kompatibilitätsgründen
//		allerdings mit angegeben werden und sollte auch sinnvoll belegt werden (vielleicht passen wir
//		das Makro ja später nochmal an ;-)).
// @normal Die Fehlerbedingung muß explizit angegeben werden, da manche Funktionen '0', andere nicht '0' im
//		Fehlerfall zurückgeben (siehe Beispiel):
// @ex Anwendungsbeispiel |
//	HANDLE	hFile = NULL; DWORD dwSize = NULL; DWORD dwRead = 0;
//	hFile = ::CreateFile( strFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_READONLY, NULL );
//	SYS_ERROR( INVALID_HANDLE_VALUE == hFile, E_FAIL );
//	SYS_ERROR( 0xFFFFFFFFL == (dwSize = ::GetFileSize( hFile, NULL )), E_FAIL );
//	SYS_ERROR( 0 == ::ReadFile( hFile, ein_Zeiger_auf_viel_Speicher, dwSize, &dwRead, NULL ), E_CANNOTREADDATA  );
//	SYS_ERROR( 0 == ::CloseHandle( hFile ), E_FAIL);
#define	SYS_ERROR(expr,hr)	__SYS_ERROR(expr,hr)
// @func | WIN_ERROR_FAILED_HRESULT |
//		Test auf Fehler in Windows-API-Funktionen die im Fehlerfall was anderes als ERROR_SUCCESS
//		zurückliefern.
#define WIN_ERROR_NOTSUCCESS(expr,hr)		__WIN_ERROR_NOTSUCCESS(expr,hr)
// @func | CO_ERROR_FAILED_HRESULT |
//		Test auf Fehler in COM-Libraryfunktionen (Co...).
#define	CO_ERROR_FAILED_HRESULT(expr,hr)	__CO_ERROR_FAILED_HRESULT(expr,hr)
// @func | ERROR_FAILED_HRESULT |
//		Testet den <l HRESULT> der Anweisung (expr). Wenn der Status nicht <l SUCCEEDED> ist,
//		wird ein Fehlerobjekt mit dem angegebenen <l HRESULT> erzeugt, im Fehlerstack abgelegt 
//		(sofern dieser instantiiert werden kann), und die Funktion verlassen.
#define ERROR_FAILED_HRESULT(expr,hr)		__ERROR_FAILED_HRESULT(expr, hr )
// @func | EXT_ERROR_FAILED_HRESULT |
//		Testet den <l HRESULT> der aufgerufenen Anweisung. Wenn der Status nicht <l SUCCEEDED> ist,
//		wird ein Fehlerobjekt mit dem angegebenen <l HRESULT> erzeugt, im Fehlerstack abgelegt 
//		(sofern dieser instantiiert werden kann), und die Funktion verlassen.
//		Dieses Makro setzt vor Abarbeitung von <b expr> das Fehlerobjekt zurück. Trat ein Fehler auf,
//		wird das durch die gerufene Methode ggf. erzeugte Fehlerobjekt im Stack gesichert und danach
//		erst das eigene erzeugt.
// @devnote Dieses Makro ist geeignet für den Aufruf von COM-Objekten die selbst Fehlerobjekte
//		erzeugen, diese aber nicht im Errorstack (wie bei b ERROR_...) ablegen.
#define	EXT_ERROR_FAILED_HRESULT(expr,hr)	__EXT_ERROR_FAILED_HRESULT(expr,hr)
// @func | ERROR_EXPR_TRUE |
//		Testet den Ausdruck <b expr>. Wenn der Test den Wert <b true> ergibt 
//		wird ein Fehlerobjekt mit dem angegebenen <l HRESULT> erzeugt, im Fehlerstack abgelegt 
//		(sofern dieser instantiiert werden kann), und die Funktion verlassen.
// @ex Wenn in der Dispatch-Map unter dem gegebenen GUID nichts gefunden wird (iterator i == map.end())
//		, die Funktion verlassen |
//	LPDispatchMap::iterator i = m_mapOfCS.find( inCS );
//	ERROR_EXPR_TRUE( m_mapOfCS.end()==i, CST_E_COORDSYSTEMNOTFOUND );
#define	ERROR_EXPR_TRUE(expr,hr)			__ERROR_EXPR_FALSE( !(expr), hr )
#define	ERROR_EXPR_TRUEEX(expr,hr,code)		__ERROR_EXPR_FALSEEX( !(expr), hr, code )
// @doc ERROR ERREXPR MACRO TRiASDB
// @func | ERROR_EXPR_FALSE |
//		Testet den Ausdruck <b expr>. Wenn der Test den Wert <b false> ergibt 
//		wird ein Fehlerobjekt mit dem angegebenen <l HRESULT> erzeugt, im Fehlerstack abgelegt 
//		(sofern dieser instantiiert werden kann), und die Funktion verlassen.
// @ex Die Funktion verlassen wenn kein Ausgangskoordinatensystem definiert ist. |
//	ERROR_EXPR_FALSE( !!m_pOutputCS, CST_E_INVALIDOUTPUTCOORDSYSTEM );
#define	ERROR_EXPR_FALSE(expr,hr)			__ERROR_EXPR_FALSE( expr, hr )
#define	ERROR_EXPR_FALSEEX(expr,hr,code)	__ERROR_EXPR_FALSEEX( expr, hr, code )

// @func | RETURN_FAILED_HRESULT |
//		Wie <l ERROR_FAILED_HRESULT> jedoch ohne erzeugen eines Fehlerobjektes.
// @devnote Aus Kompatibilitätsgründen kann dem Makro <b kein> Statuscode übergeben werden
//		(Vielleicht später mal, bei gaaaaaaanz viel Zeit).
#if defined(RETURN_FAILED_HRESULT)
#undef RETURN_FAILED_HRESULT
#endif
#define	RETURN_FAILED_HRESULT(expr)			__RETURN_FAILED_HRESULT(expr)
// @func | EXT_RETURN_FAILED_HRESULT |
//		Wie <l EXT_ERROR_FAILED_HRESULT> jedoch ohne erzeugen eines Fehlerobjektes; das ggf. erzeugte
//		wird jedoch gesichert.
#define	EXT_RETURN_FAILED_HRESULT(expr)		__EXT_RETURN_FAILED_HRESULT(expr)
// @doc ERROR MACRO TRiASDB
// @func | RETURN_EXPR_TRUE |
//		Wie <l ERROR_EXPR_TRUE> jedoch ohne erzeugen eines Fehlerobjektes.
#define RETURN_EXPR_TRUE(expr,hr)			__RETURN_EXPR_TRUE(expr,hr)
// @func | RETURN_EXPR_FALSE |
//		Wie <l ERROR_EXPR_FALSE> jedoch ohne erzeugen eines Fehlerobjektes.
#define	RETURN_EXPR_FALSE(expr,hr)			RETURN_EXPR_TRUE(!(expr),hr)

#if !defined(__INIT_POINTER_FUNCS)
#define __INIT_POINTER_FUNCS
template<class T> inline void __InitPointer (T *p) { *p = T(NULL); }
inline void __InitPointer (VARIANT *p) { VariantInit(p); V_VT(p) = VT_ERROR; V_ERROR(p) = DISP_E_PARAMNOTFOUND; }
#endif // !defined(__INIT_POINTER_FUNCS)

// @func | CHECKINPOINTER |
//		Ist definiert als: { ERROR_EXPR_FALSE(!!(p),E_POINTER);}
#define	CHECKINPOINTER(p)	{ ERROR_EXPR_FALSE(!!(p),E_POINTER);}
// @func | CHECKOUTPOINTER |
//		Ist definiert als: { <l ERROR_EXPR_FALSEEX>(!!(p),E_POINTER,__InitPointer(p));}
#define	CHECKOUTPOINTER(p)	{ ERROR_EXPR_FALSEEX(!!(p),E_POINTER,__InitPointer(p));}

// @func | FUNC_NOT_IMPL |
//		Ist zu verwenden wenn Interfaceentrys nocht nicht ausprogrammiert sind
//		und mit einer Assertion darauf hingewiesen werden soll.
#define FUNC_NOT_IMPL()	{ _ASSERTE(SUCCEEDED(E_NOTIMPL)); return E_NOTIMPL; }

#if defined(_DEBUG)
#define GENERATE_ERROR_NOASSERT(expr)	\
	{ HRESULT __hr = (expr); if (SUCCEEDED(__hr)) {} else {	\
		(this)->GenerateError(#expr, __FILE__, __LINE__, __hr); \
		PushError();										\
		return __hr;										\
	} }
#else
#define GENERATE_ERROR_NOASSERT(expr)	\
	{ HRESULT __hr = (expr); if (SUCCEEDED(__hr)) {} else {	\
		(this)->GenerateError(__hr);						\
		PushError();										\
		return __hr;										\
	} }
#endif

#endif // !defined(_NO_ERROR_MACROS)

#endif // _ERRORMACROS2_A677EDC0_4812_11d2_8FB8_0060085FC1CE
