// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 16.09.98 20:21:24 
//
// @doc 
// @module ComErrorMacros.h | Makrodefinitionen für die Fehlerauswertung

#if !defined(_COMERRORMACROS_H__48172D62_AB72_11D1_858D_00600875138A__INCLUDED_)
#define _COMERRORMACROS_H__48172D62_AB72_11D1_858D_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <new>

#if _MSC_VER >= 1100
#include <comdef.h>
#define _COM_ERROR(ec)	ec.Error()
#define _COM_MSG(ec)	ec.ErrorMessage()
#define BAD_ALLOC		std::bad_alloc
#else
#define _com_error HRESULT
#define _com_issue_error(ec) throw (ec)
#define _COM_ERROR(ec)	(ec)
#define _COM_MSG(ec)	_T("")
#define BAD_ALLOC		bad_alloc
#endif // _MSC_VER

#if defined(NO_QI_EXCEPTION)
inline HRESULT GetLastHRESULT (void) { return (HRESULT)::GetLastError(); }
#else

inline bool IMPL_AND_FAILED(HRESULT hr)
{
	return (FAILED(hr)&&!(E_NOTIMPL==hr));
}

#if !defined(_ASSERT_ON_THROW_FAILED_HRESULT)
#define THROW_FAILED_HRESULT(x)		{HRESULT __hr=(x);if(SUCCEEDED(__hr)){}else{_com_issue_error(__hr);}}	//lint --e(774)
#define THROW_FAILED_HRESULT_ASSERT(x)		{HRESULT __hr=(x);if(SUCCEEDED(__hr)){}else{_ASSERTE(SUCCEEDED(__hr));_com_issue_error(__hr);}}	//lint --e(774)
#else 
#define THROW_FAILED_HRESULT(x)		{HRESULT __hr=(x);if(SUCCEEDED(__hr)){}else{_ASSERTE(SUCCEEDED(__hr));_com_issue_error(__hr);}}	//lint --e(774)
#endif // defined(_NO_ASSERT_ON_THROW_FAILED_HRESULT)

#define RETURN_FAILED_HRESULT(x)	{HRESULT __hr=(x);if(SUCCEEDED(__hr)){}else{_ASSERTE(SUCCEEDED(__hr));return(__hr);}}	//lint --e(774)
#define RETURN_HRESULT(x)			{_ASSERTE(SUCCEEDED(x)); return(x);}

#define THROW_FAILED_HRESULTEX(x)	{HRESULT __hr=(x);if(SUCCEEDED(__hr)){}else{_com_issue_errorex(__hr, this, __uuidof(this));}}	//lint --e(774)

#define THROW_IMPL_AND_FAILED(x)	{HRESULT __hr=(x);if(!IMPL_AND_FAILED(__hr)){}else{_com_issue_error(__hr);}}	//lint --e(774)
#define RETURN_IMPL_AND_FAILED(x)	{HRESULT __hr=(x);if(!IMPL_AND_FAILED(__hr)){}else{return(__hr);}}	//lint --e(774)

/////////////////////////////////////////////////////////////////////////////
// Makros für Paremetertest
#if !defined(BEGIN_OUT_PARAMS)

#if !defined(__INIT_POINTER_FUNCS)
#define __INIT_POINTER_FUNCS
template<class T> inline void __InitPointer (T *p) { *p = T(NULL); }
inline void __InitPointer (VARIANT *p) { VariantInit(p); V_VT(p) = VT_ERROR; V_ERROR(p) = DISP_E_PARAMNOTFOUND; }
#endif // !defined(__INIT_POINTER_FUNCS)

// die folgenden Macros sollten noch in Error-Behandlung eingebaut werden
#define BEGIN_OUT_PARAMS()	{ HRESULT __hr = S_OK;
#define OUT_PARAM(p)		{ if (p) __InitPointer(p); else __hr = E_POINTER; }
#define IN_PARAM(p)			{ if (NULL == p) __hr = E_POINTER; }
#define END_OUT_PARAMS()	if (FAILED(__hr)) {COM_ASSERT_EX2(__hr); return __hr; }}

#define BEGIN_TEST_PARAMS()	BEGIN_OUT_PARAMS()
#define END_TEST_PARAMS()	END_OUT_PARAMS()

// Variante für einen [out]-Parameter
#define TEST_OUT_PARAM(p)	BEGIN_TEST_PARAMS(); OUT_PARAM(p); END_TEST_PARAMS();

// Variante für einen [in]-Parameter
#define TEST_IN_PARAM(p)	BEGIN_TEST_PARAMS(); IN_PARAM(p); END_TEST_PARAMS();

#endif // !defined(BEGIN_OUT_PARAMS)

/////////////////////////////////////////////////////////////////////////////
// Makros für COM-orientierte try/catch Konstrukte
#define COM_TRY				SetLastError(S_OK); try 
#define COM_CATCH_EX(e)		catch (_com_error &e)

#if defined(_DEBUG) && defined(_ATLX_ASSERT_ON_FAILURE)
#define COM_ASSERT()		_ASSERTE(SUCCEEDED(E_UNEXPECTED))	/*lint --e(506), --e(774)*/
#define COM_ASSERT_EX(e)	_ASSERTE(SUCCEEDED(_COM_ERROR(e)))
#define COM_ASSERT_EX2(e)	_ASSERTE(SUCCEEDED(e))
#define COM_TRACEUNKNOWNERROR()	ATLTRACE(_T("%s(%d): Unknown error\n"), THIS_FILE, __LINE__)
#define COM_TRACECOMERROR(e)	ATLTRACE(_T("%s(%d): _com_error: %s\n"), THIS_FILE, __LINE__, _COM_MSG(e))
#define COM_TRACEOUTOFMEMORY()	ATLTRACE(_T("%s(%d): Out of memory\n"), THIS_FILE, __LINE__)
#else
#define COM_ASSERT()
#define COM_ASSERT_EX(e)
#define COM_ASSERT_EX2(e)
#define COM_TRACEUNKNOWNERROR()	
#define COM_TRACECOMERROR(e)
#define COM_TRACEOUTOFMEMORY()	
#endif // defined(_DEBUG) && defined(ASSERT_ON_FAILURE)

#define COM_CATCH_ALL \
	catch (...) { \
		SetLastError((DWORD)E_UNEXPECTED); \
		COM_TRACEUNKNOWNERROR(); \
		COM_ASSERT(); \
		return E_UNEXPECTED; /*lint --e(570)*/ \
	}
#define COM_CATCH_ALL_RETURN(r) \
	catch (...) { \
		SetLastError((DWORD)E_UNEXPECTED); \
		COM_TRACEUNKNOWNERROR(); \
		COM_ASSERT(); \
		return (r); \
	}
#define COM_CATCH_ALL_NORETURN \
	catch (...) { \
		SetLastError((DWORD)E_UNEXPECTED); \
		COM_TRACEUNKNOWNERROR(); \
		COM_ASSERT(); \
		return; \
	}
#define COM_CATCH_ALL_NORETURN_OP(x) \
	catch (...) { \
		SetLastError((DWORD)E_UNEXPECTED); \
		x; \
		COM_TRACEUNKNOWNERROR(); \
		COM_ASSERT(); \
		return; \
	}
#define COM_CATCH_ALL_OP(x) \
	catch (...) { \
		SetLastError((DWORD)E_UNEXPECTED); \
		x; \
		COM_TRACEUNKNOWNERROR(); \
		COM_ASSERT(); \
		return E_UNEXPECTED; /*lint --e(570)*/ \
	}
#define COM_CATCH_ALL_OP_RETURN(x,r) \
	catch (...) { \
		SetLastError((DWORD)E_UNEXPECTED); \
		x; \
		COM_TRACEUNKNOWNERROR(); \
		COM_ASSERT(); \
		return (r); \
	}

#define COM_CATCH \
	catch (const _com_error &e) { \
		SetLastError((DWORD)_COM_ERROR(e)); \
		COM_TRACECOMERROR(e); \
		COM_ASSERT_EX(e); \
		return _COM_ERROR(e); \
	} catch (const BAD_ALLOC &) { \
		SetLastError((DWORD)E_OUTOFMEMORY); \
		COM_TRACEOUTOFMEMORY(); \
		COM_ASSERT_EX2((DWORD)E_OUTOFMEMORY); \
		return E_OUTOFMEMORY; /*lint --e(570)*/ \
	} COM_CATCH_ALL

#define COM_CATCH_NOASSERT_ON(ignore) \
	catch (const _com_error &e) { \
		SetLastError((DWORD)_COM_ERROR(e)); \
		COM_TRACECOMERROR(e); \
		if (_COM_ERROR(e) != ignore) { COM_ASSERT_EX(e); } \
		return _COM_ERROR(e); \
	} catch (const BAD_ALLOC &) { \
		SetLastError((DWORD)E_OUTOFMEMORY); \
		COM_TRACEOUTOFMEMORY(); \
		COM_ASSERT_EX2((DWORD)E_OUTOFMEMORY); \
		return E_OUTOFMEMORY; /*lint --e(570)*/ \
	} COM_CATCH_ALL

#define COM_CATCH_RETURN(r) \
	catch (const _com_error &e) { \
		SetLastError((DWORD)_COM_ERROR(e)); \
		COM_TRACECOMERROR(e); \
		COM_ASSERT_EX(e); \
		return (r); \
	} catch (const BAD_ALLOC &) { \
		SetLastError((DWORD)E_OUTOFMEMORY); \
		COM_TRACEOUTOFMEMORY(); \
		COM_ASSERT_EX2(E_OUTOFMEMORY); \
		return (r); \
	} COM_CATCH_ALL_RETURN(r)

#define COM_CATCH_NORETURN \
	catch (const _com_error &e) { \
		SetLastError((DWORD)_COM_ERROR(e)); \
		COM_TRACECOMERROR(e); \
		COM_ASSERT_EX(e); \
		return; \
	} catch (const BAD_ALLOC &) { \
		SetLastError((DWORD)E_OUTOFMEMORY); \
		COM_TRACEOUTOFMEMORY(); \
		COM_ASSERT_EX2(E_OUTOFMEMORY); \
		return; \
	} COM_CATCH_ALL_NORETURN

#define COM_CATCH_NORETURN_OP(x) \
	catch (const _com_error &e) { \
		SetLastError((DWORD)_COM_ERROR(e)); \
		x; \
		COM_TRACECOMERROR(e); \
		COM_ASSERT_EX(e); \
		return; \
	} catch (const BAD_ALLOC &) { \
		SetLastError((DWORD)E_OUTOFMEMORY); \
		x; \
		COM_TRACEOUTOFMEMORY(); \
		COM_ASSERT_EX2(E_OUTOFMEMORY); \
		return; \
	} COM_CATCH_ALL_NORETURN_OP(x)

#define COM_CATCH_OP(x) \
	catch (const _com_error &e) { \
		SetLastError((DWORD)_COM_ERROR(e)); \
		x; \
		COM_TRACECOMERROR(e); \
		COM_ASSERT_EX(e); \
		return _COM_ERROR(e); \
	} catch (const BAD_ALLOC &) { \
		SetLastError((DWORD)E_OUTOFMEMORY); \
		x; \
		COM_TRACEOUTOFMEMORY(); \
		COM_ASSERT_EX2(E_OUTOFMEMORY); \
		return E_OUTOFMEMORY; /*lint --e(570)*/ \
	} COM_CATCH_ALL_OP(x)

#define COM_CATCH_OP_NOASSERT_ON(x,ignore) \
	catch (const _com_error &e) { \
		SetLastError((DWORD)_COM_ERROR(e)); \
		x; \
		COM_TRACECOMERROR(e); \
		if (_COM_ERROR(e) != ignore) { COM_ASSERT_EX(e); } \
		return _COM_ERROR(e); \
	} catch (const BAD_ALLOC &) { \
		SetLastError((DWORD)E_OUTOFMEMORY); \
		x; \
		COM_TRACEOUTOFMEMORY(); \
		COM_ASSERT_EX2(E_OUTOFMEMORY); \
		return E_OUTOFMEMORY; /*lint --e(570)*/ \
	} COM_CATCH_ALL_OP(x)

#define COM_CATCH_OP_RETURN(x,r) \
	catch (const _com_error &e) { \
		SetLastError((DWORD)_COM_ERROR(e)); \
		x; \
		COM_TRACECOMERROR(e); \
		COM_ASSERT_EX(e); \
		return (r); \
	} catch (const BAD_ALLOC &) { \
		SetLastError((DWORD)E_OUTOFMEMORY); \
		x; \
		COM_TRACEOUTOFMEMORY(); \
		COM_ASSERT_EX2(E_OUTOFMEMORY); \
		return (r); \
	} COM_CATCH_ALL_OP_RETURN(x,r)

#define COM_CATCH_NOASSERT_ON_RETURN(ignore,r) \
	catch (const _com_error &e) { \
		SetLastError((DWORD)_COM_ERROR(e)); \
		COM_TRACECOMERROR(e); \
		if (_COM_ERROR(e) != ignore) { COM_ASSERT_EX(e); } \
		return (r); \
	} catch (const BAD_ALLOC &) { \
		SetLastError((DWORD)E_OUTOFMEMORY); \
		COM_TRACEOUTOFMEMORY(); \
		COM_ASSERT_EX2((DWORD)E_OUTOFMEMORY); \
		return (r); /*lint --e(570)*/ \
	} COM_CATCH_ALL_RETURN(r)

#define COM_CATCH_IGNORE \
	catch (...) {}

#endif // !NO_QI_EXCEPTION

#endif // !defined(_COMERRORMACROS_H__48172D62_AB72_11D1_858D_00600875138A__INCLUDED_)
