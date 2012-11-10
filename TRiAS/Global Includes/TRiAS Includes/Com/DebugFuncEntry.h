#if !defined(__DEBUG_FUNCENTRY_H__D371C6C0_1BC0_11d2_8F7D_0060085FC1CE)
#define __DEBUG_FUNCENTRY_H__D371C6C0_1BC0_11d2_8F7D_0060085FC1CE
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
#if defined(_DEBUG_FUNCENTRY)
#define DFE(c,m) ATLTRACE(_T("%s(0x%lx) -->%s\n"), #c, this, #m )
#define	DFL(c,m,r) ATLTRACE(_T("%s(0x%lx) <--%s<<0x%08lx>>\n"), #c, this, #m, r)
#else
#define DFE(c,m)
#define	DFL(c,m,r)
#endif
////////////////////////////////////////////////////////////////
// 0 Argumente
#if defined(_DEBUG)
#define DECLARE_DEBUG_FUNCENTRY_0(c,m) STDMETHOD(m)() {DFE(c,m);HRESULT hr=c##m();DFL(c,m,hr);return hr;} STDMETHOD(c##m)()
#define _DECLARE_DEBUG_FUNCENTRY_0(c,m) STDMETHOD(m)() {return c##m();} STDMETHOD(c##m)()
#define IMPLEMENT_DEBUG_FUNCENTRY_0(c,m) STDMETHODIMP c::c##m()
#else
#define DECLARE_DEBUG_FUNCENTRY_0(c,m) STDMETHOD(m)()
#define _DECLARE_DEBUG_FUNCENTRY_0(c,m) STDMETHOD(m)()
#define IMPLEMENT_DEBUG_FUNCENTRY_0(c,m) STDMETHODIMP c::m()
#endif
////////////////////////////////////////////////////////////////
// 1 Argument
#if defined(_DEBUG)
#define DECLARE_DEBUG_FUNCENTRY_1(c,m,t1,a1) STDMETHOD(m)(t1 a1) {DFE(c,m);HRESULT hr=c##m(a1);DFL(c,m,hr);return hr;} STDMETHOD(c##m)(t1 a1)
#define _DECLARE_DEBUG_FUNCENTRY_1(c,m,t1,a1) STDMETHOD(m)(t1 a1) {return c##m(a1);} STDMETHOD(c##m)(t1 a1)
#define IMPLEMENT_DEBUG_FUNCENTRY_1(c,m,t1,a1) STDMETHODIMP c::c##m(t1 a1)
#else
#define DECLARE_DEBUG_FUNCENTRY_1(c,m,t1,a1) STDMETHOD(m)(t1 a1)
#define _DECLARE_DEBUG_FUNCENTRY_1(c,m,t1,a1) STDMETHOD(m)(t1 a1)
#define IMPLEMENT_DEBUG_FUNCENTRY_1(c,m,t1,a1) STDMETHODIMP c::m(t1 a1)
#endif
////////////////////////////////////////////////////////////////
// 2 Argumente
#if defined(_DEBUG)
#define DECLARE_DEBUG_FUNCENTRY_2(c,m,t1,a1,t2,a2) STDMETHOD(m)(t1 a1,t2 a2) {DFE(c,m);HRESULT hr=c##m(a1,a2);DFL(c,m,hr);return hr;} STDMETHOD(c##m)(t1 a1,t2 a2)
#define _DECLARE_DEBUG_FUNCENTRY_2(c,m,t1,a1,t2,a2) STDMETHOD(m)(t1 a1,t2 a2) {return c##m(a1,a2);} STDMETHOD(c##m)(t1 a1,t2 a2)
#define IMPLEMENT_DEBUG_FUNCENTRY_2(c,m,t1,a1,t2,a2) STDMETHODIMP c::c##m(t1 a1,t2 a2)
#else
#define DECLARE_DEBUG_FUNCENTRY_2(c,m,t1,a1,t2,a2) STDMETHOD(m)(t1 a1,t2 a2)
#define _DECLARE_DEBUG_FUNCENTRY_2(c,m,t1,a1,t2,a2) STDMETHOD(m)(t1 a1,t2 a2)
#define IMPLEMENT_DEBUG_FUNCENTRY_2(c,m,t1,a1,t2,a2) STDMETHODIMP c::m(t1 a1,t2 a2)
#endif
////////////////////////////////////////////////////////////////
// 3 Argumente
#if defined(_DEBUG)
#define DECLARE_DEBUG_FUNCENTRY_3(c,m,t1,a1,t2,a2,t3,a3) STDMETHOD(m)(t1 a1,t2 a2,t3 a3) {DFE(c,m);HRESULT hr=c##m(a1,a2,a3);DFL(c,m,hr);return hr;} STDMETHOD(c##m)(t1 a1,t2 a2,t3 a3)
#define _DECLARE_DEBUG_FUNCENTRY_3(c,m,t1,a1,t2,a2,t3,a3) STDMETHOD(m)(t1 a1,t2 a2,t3 a3) {return c##m(a1,a2,a3);} STDMETHOD(c##m)(t1 a1,t2 a2,t3 a3)
#define IMPLEMENT_DEBUG_FUNCENTRY_3(c,m,t1,a1,t2,a2,t3,a3) STDMETHODIMP c::c##m(t1 a1,t2 a2,t3 a3)
#else
#define DECLARE_DEBUG_FUNCENTRY_3(c,m,t1,a1,t2,a2,t3,a3) STDMETHOD(m)(t1 a1,t2 a2,t3 a3)
#define _DECLARE_DEBUG_FUNCENTRY_3(c,m,t1,a1,t2,a2,t3,a3) STDMETHOD(m)(t1 a1,t2 a2,t3 a3)
#define IMPLEMENT_DEBUG_FUNCENTRY_3(c,m,t1,a1,t2,a2,t3,a3) STDMETHODIMP c::m(t1 a1,t2 a2,t3 a3)
#endif
////////////////////////////////////////////////////////////////
// 4 Argumente
#if defined(_DEBUG)
#define DECLARE_DEBUG_FUNCENTRY_4(c,m,t1,a1,t2,a2,t3,a3,t4,a4) STDMETHOD(m)(t1 a1,t2 a2,t3 a3,t4 a4) {DFE(c,m);HRESULT hr=c##m(a1,a2,a3,a4);DFL(c,m,hr);return hr;} STDMETHOD(c##m)(t1 a1,t2 a2,t3 a3,t4 a4)
#define _DECLARE_DEBUG_FUNCENTRY_4(c,m,t1,a1,t2,a2,t3,a3,t4,a4) STDMETHOD(m)(t1 a1,t2 a2,t3 a3,t4 a4) {return c##m(a1,a2,a3,a4);} STDMETHOD(c##m)(t1 a1,t2 a2,t3 a3,t4 a4)
#define IMPLEMENT_DEBUG_FUNCENTRY_4(c,m,t1,a1,t2,a2,t3,a3,t4,a4) STDMETHODIMP c::c##m(t1 a1,t2 a2,t3 a3,t4 a4)
#else
#define DECLARE_DEBUG_FUNCENTRY_4(c,m,t1,a1,t2,a2,t3,a3,t4,a4) STDMETHOD(m)(t1 a1,t2 a2,t3 a3,t4 a4)
#define _DECLARE_DEBUG_FUNCENTRY_4(c,m,t1,a1,t2,a2,t3,a3,t4,a4) STDMETHOD(m)(t1 a1,t2 a2,t3 a3,t4 a4)
#define IMPLEMENT_DEBUG_FUNCENTRY_4(c,m,t1,a1,t2,a2,t3,a3,t4,a4) STDMETHODIMP c::m(t1 a1,t2 a2,t3 a3,t4 a4)
#endif
////////////////////////////////////////////////////////////////
// 5 Argumente
#if defined(_DEBUG)
#define DECLARE_DEBUG_FUNCENTRY_5(c,m,t1,a1,t2,a2,t3,a3,t4,a4,t5,a5) STDMETHOD(m)(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5) {DFE(c,m);HRESULT hr=c##m(a1,a2,a3,a4,a5);DFL(c,m,hr);return hr;} STDMETHOD(c##m)(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5)
#define _DECLARE_DEBUG_FUNCENTRY_5(c,m,t1,a1,t2,a2,t3,a3,t4,a4,t5,a5) STDMETHOD(m)(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5) {return c##m(a1,a2,a3,a4,a5);} STDMETHOD(c##m)(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5)
#define IMPLEMENT_DEBUG_FUNCENTRY_5(c,m,t1,a1,t2,a2,t3,a3,t4,a4,t5,a5) STDMETHODIMP c::c##m(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5)
#else
#define DECLARE_DEBUG_FUNCENTRY_5(c,m,t1,a1,t2,a2,t3,a3,t4,a4,t5,a5) STDMETHOD(m)(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5)
#define _DECLARE_DEBUG_FUNCENTRY_5(c,m,t1,a1,t2,a2,t3,a3,t4,a4,t5,a5) STDMETHOD(m)(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5)
#define IMPLEMENT_DEBUG_FUNCENTRY_5(c,m,t1,a1,t2,a2,t3,a3,t4,a4,t5,a5) STDMETHODIMP c::m(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5)
#endif
////////////////////////////////////////////////////////////////
// 6 Argumente
#if defined(_DEBUG)
#define DECLARE_DEBUG_FUNCENTRY_6(c,m,t1,a1,t2,a2,t3,a3,t4,a4,t5,a5,t6,a6) STDMETHOD(m)(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6) {DFE(c,m);HRESULT hr=c##m(a1,a2,a3,a4,a5,a6);DFL(c,m,hr);return hr;} STDMETHOD(c##m)(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6)
#define _DECLARE_DEBUG_FUNCENTRY_6(c,m,t1,a1,t2,a2,t3,a3,t4,a4,t5,a5,t6,a6) STDMETHOD(m)(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6) {return c##m(a1,a2,a3,a4,a5,a6);} STDMETHOD(c##m)(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6)
#define IMPLEMENT_DEBUG_FUNCENTRY_6(c,m,t1,a1,t2,a2,t3,a3,t4,a4,t5,a5,t6,a6) STDMETHODIMP c::c##m(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6)
#else
#define DECLARE_DEBUG_FUNCENTRY_6(c,m,t1,a1,t2,a2,t3,a3,t4,a4,t5,a5,t6,a6) STDMETHOD(m)(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6)
#define _DECLARE_DEBUG_FUNCENTRY_6(c,m,t1,a1,t2,a2,t3,a3,t4,a4,t5,a5,t6,a6) STDMETHOD(m)(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6)
#define IMPLEMENT_DEBUG_FUNCENTRY_6(c,m,t1,a1,t2,a2,t3,a3,t4,a4,t5,a5,t6,a6) STDMETHODIMP c::m(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6)
#endif
////////////////////////////////////////////////////////////////
// 7 Argumente
#if defined(_DEBUG)
#define DECLARE_DEBUG_FUNCENTRY_7(c,m,t1,a1,t2,a2,t3,a3,t4,a4,t5,a5,t6,a6,t7,a7) STDMETHOD(m)(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7) {DFE(c,m);HRESULT hr=c##m(a1,a2,a3,a4,a5,a6,a7);DFL(c,m,hr);return hr;} STDMETHOD(c##m)(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7)
#define _DECLARE_DEBUG_FUNCENTRY_7(c,m,t1,a1,t2,a2,t3,a3,t4,a4,t5,a5,t6,a6,t7,a7) STDMETHOD(m)(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7) {return c##m(a1,a2,a3,a4,a5,a6,a7);} STDMETHOD(c##m)(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7)
#define IMPLEMENT_DEBUG_FUNCENTRY_7(c,m,t1,a1,t2,a2,t3,a3,t4,a4,t5,a5,t6,a6,t7,a7) STDMETHODIMP c::c##m(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7)
#else
#define DECLARE_DEBUG_FUNCENTRY_7(c,m,t1,a1,t2,a2,t3,a3,t4,a4,t5,a5,t6,a6,t7,a7) STDMETHOD(m)(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7)
#define _DECLARE_DEBUG_FUNCENTRY_7(c,m,t1,a1,t2,a2,t3,a3,t4,a4,t5,a5,t6,a6,t7,a7) STDMETHOD(m)(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7)
#define IMPLEMENT_DEBUG_FUNCENTRY_7(c,m,t1,a1,t2,a2,t3,a3,t4,a4,t5,a5,t6,a6,t7,a7) STDMETHODIMP c::m(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7)
#endif
////////////////////////////////////////////////////////////////
// 8 Argumente
#if defined(_DEBUG)
#define DECLARE_DEBUG_FUNCENTRY_8(c,m,t1,a1,t2,a2,t3,a3,t4,a4,t5,a5,t6,a6,t7,a7,t8,a8) STDMETHOD(m)(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8) {DFE(c,m);HRESULT hr=c##m(a1,a2,a3,a4,a5,a6,a7,a8);DFL(c,m,hr);return hr;} STDMETHOD(c##m)(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8)
#define _DECLARE_DEBUG_FUNCENTRY_8(c,m,t1,a1,t2,a2,t3,a3,t4,a4,t5,a5,t6,a6,t7,a7,t8,a8) STDMETHOD(m)(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8) {return c##m(a1,a2,a3,a4,a5,a6,a7,a8);} STDMETHOD(c##m)(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8)
#define IMPLEMENT_DEBUG_FUNCENTRY_8(c,m,t1,a1,t2,a2,t3,a3,t4,a4,t5,a5,t6,a6,t7,a7,t8,a8) STDMETHODIMP c::c##m(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8)
#else
#define DECLARE_DEBUG_FUNCENTRY_8(c,m,t1,a1,t2,a2,t3,a3,t4,a4,t5,a5,t6,a6,t7,a7,t8,a8) STDMETHOD(m)(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8)
#define _DECLARE_DEBUG_FUNCENTRY_8(c,m,t1,a1,t2,a2,t3,a3,t4,a4,t5,a5,t6,a6,t7,a7,t8,a8) STDMETHOD(m)(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8)
#define IMPLEMENT_DEBUG_FUNCENTRY_8(c,m,t1,a1,t2,a2,t3,a3,t4,a4,t5,a5,t6,a6,t7,a7,t8,a8) STDMETHODIMP c::m(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8)
#endif
////////////////////////////////////////////////////////////////
// 9 Argumente
#if defined(_DEBUG)
#define DECLARE_DEBUG_FUNCENTRY_9(c,m,t1,a1,t2,a2,t3,a3,t4,a4,t5,a5,t6,a6,t7,a7,t8,a8,t9,a9) STDMETHOD(m)(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9) {DFE(c,m);HRESULT hr=c##m(a1,a2,a3,a4,a5,a6,a7,a8,a9);DFL(c,m,hr);return hr;} STDMETHOD(c##m)(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9)
#define _DECLARE_DEBUG_FUNCENTRY_9(c,m,t1,a1,t2,a2,t3,a3,t4,a4,t5,a5,t6,a6,t7,a7,t8,a8,t9,a9) STDMETHOD(m)(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9) {return c##m(a1,a2,a3,a4,a5,a6,a7,a8,a9);} STDMETHOD(c##m)(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9)
#define IMPLEMENT_DEBUG_FUNCENTRY_9(c,m,t1,a1,t2,a2,t3,a3,t4,a4,t5,a5,t6,a6,t7,a7,t8,a8,t9,a9) STDMETHODIMP c::c##m(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9)
#else
#define DECLARE_DEBUG_FUNCENTRY_9(c,m,t1,a1,t2,a2,t3,a3,t4,a4,t5,a5,t6,a6,t7,a7,t8,a8,t9,a9) STDMETHOD(m)(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9)
#define _DECLARE_DEBUG_FUNCENTRY_9(c,m,t1,a1,t2,a2,t3,a3,t4,a4,t5,a5,t6,a6,t7,a7,t8,a8,t9,a9) STDMETHOD(m)(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9)
#define IMPLEMENT_DEBUG_FUNCENTRY_9(c,m,t1,a1,t2,a2,t3,a3,t4,a4,t5,a5,t6,a6,t7,a7,t8,a8,t9,a9) STDMETHODIMP c::m(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9)
#endif
////////////////////////////////////////////////////////////////
// 10 Argumente
#if defined(_DEBUG)
#define DECLARE_DEBUG_FUNCENTRY_10(c,m,t1,a1,t2,a2,t3,a3,t4,a4,t5,a5,t6,a6,t7,a7,t8,a8,t9,a9,t10,a10) STDMETHOD(m)(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10) {DFE(c,m);HRESULT hr=c##m(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10);DFL(c,m,hr);return hr;} STDMETHOD(c##m)(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10)
#define _DECLARE_DEBUG_FUNCENTRY_10(c,m,t1,a1,t2,a2,t3,a3,t4,a4,t5,a5,t6,a6,t7,a7,t8,a8,t9,a9,t10,a10) STDMETHOD(m)(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10) {return c##m(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10);} STDMETHOD(c##m)(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10)
#define IMPLEMENT_DEBUG_FUNCENTRY_10(c,m,t1,a1,t2,a2,t3,a3,t4,a4,t5,a5,t6,a6,t7,a7,t8,a8,t9,a9,t10,a10) STDMETHODIMP c::c##m(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10)
#else
#define DECLARE_DEBUG_FUNCENTRY_10(c,m,t1,a1,t2,a2,t3,a3,t4,a4,t5,a5,t6,a6,t7,a7,t8,a8,t9,a9,t10,a10) STDMETHOD(m)(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10)
#define _DECLARE_DEBUG_FUNCENTRY_10(c,m,t1,a1,t2,a2,t3,a3,t4,a4,t5,a5,t6,a6,t7,a7,t8,a8,t9,a9,t10,a10) STDMETHOD(m)(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10)
#define IMPLEMENT_DEBUG_FUNCENTRY_10(c,m,t1,a1,t2,a2,t3,a3,t4,a4,t5,a5,t6,a6,t7,a7,t8,a8,t9,a9,t10,a10) STDMETHODIMP c::m(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10)
#endif
////////////////////////////////////////////////////////////////
// 11 Argumente
#if defined(_DEBUG)
#define DECLARE_DEBUG_FUNCENTRY_11(c,m,t1,a1,t2,a2,t3,a3,t4,a4,t5,a5,t6,a6,t7,a7,t8,a8,t9,a9,t10,a10,t11,a11) STDMETHOD(m)(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11) {DFE(c,m);HRESULT hr=c##m(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11);DFL(c,m,hr);return hr;} STDMETHOD(c##m)(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11)
#define _DECLARE_DEBUG_FUNCENTRY_11(c,m,t1,a1,t2,a2,t3,a3,t4,a4,t5,a5,t6,a6,t7,a7,t8,a8,t9,a9,t10,a10,t11,a11) STDMETHOD(m)(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11) {return c##m(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11);} STDMETHOD(c##m)(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11)
#define IMPLEMENT_DEBUG_FUNCENTRY_11(c,m,t1,a1,t2,a2,t3,a3,t4,a4,t5,a5,t6,a6,t7,a7,t8,a8,t9,a9,t10,a10,t11,a11) STDMETHODIMP c::c##m(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11)
#else
#define DECLARE_DEBUG_FUNCENTRY_11(c,m,t1,a1,t2,a2,t3,a3,t4,a4,t5,a5,t6,a6,t7,a7,t8,a8,t9,a9,t10,a10,t11,a11) STDMETHOD(m)(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11)
#define _DECLARE_DEBUG_FUNCENTRY_11(c,m,t1,a1,t2,a2,t3,a3,t4,a4,t5,a5,t6,a6,t7,a7,t8,a8,t9,a9,t10,a10,t11,a11) STDMETHOD(m)(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11)
#define IMPLEMENT_DEBUG_FUNCENTRY_11(c,m,t1,a1,t2,a2,t3,a3,t4,a4,t5,a5,t6,a6,t7,a7,t8,a8,t9,a9,t10,a10,t11,a11) STDMETHODIMP c::m(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11)
#endif
////////////////////////////////////////////////////////////////
// 12 Argumente
#if defined(_DEBUG)
#define DECLARE_DEBUG_FUNCENTRY_12(c,m,t1,a1,t2,a2,t3,a3,t4,a4,t5,a5,t6,a6,t7,a7,t8,a8,t9,a9,t10,a10,t11,a11,t12,a12) STDMETHOD(m)(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12) {DFE(c,m);HRESULT hr=c##m(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12);DFL(c,m,hr);return hr;} STDMETHOD(c##m)(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12)
#define _DECLARE_DEBUG_FUNCENTRY_12(c,m,t1,a1,t2,a2,t3,a3,t4,a4,t5,a5,t6,a6,t7,a7,t8,a8,t9,a9,t10,a10,t11,a11,t12,a12) STDMETHOD(m)(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12) {return c##m(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12);} STDMETHOD(c##m)(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12)
#define IMPLEMENT_DEBUG_FUNCENTRY_12(c,m,t1,a1,t2,a2,t3,a3,t4,a4,t5,a5,t6,a6,t7,a7,t8,a8,t9,a9,t10,a10,t11,a11,t12,a12) STDMETHODIMP c::c##m(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12)
#else
#define DECLARE_DEBUG_FUNCENTRY_12(c,m,t1,a1,t2,a2,t3,a3,t4,a4,t5,a5,t6,a6,t7,a7,t8,a8,t9,a9,t10,a10,t11,a11,t12,a12) STDMETHOD(m)(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12)
#define _DECLARE_DEBUG_FUNCENTRY_12(c,m,t1,a1,t2,a2,t3,a3,t4,a4,t5,a5,t6,a6,t7,a7,t8,a8,t9,a9,t10,a10,t11,a11,t12,a12) STDMETHOD(m)(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12)
#define IMPLEMENT_DEBUG_FUNCENTRY_12(c,m,t1,a1,t2,a2,t3,a3,t4,a4,t5,a5,t6,a6,t7,a7,t8,a8,t9,a9,t10,a10,t11,a11,t12,a12) STDMETHODIMP c::m(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12)
#endif
////////////////////////////////////////////////////////////////
// 13 Argumente
#if defined(_DEBUG)
#define DECLARE_DEBUG_FUNCENTRY_13(c,m,t1,a1,t2,a2,t3,a3,t4,a4,t5,a5,t6,a6,t7,a7,t8,a8,t9,a9,t10,a10,t11,a11,t12,a12,t13,a13) STDMETHOD(m)(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12,t13 a13) {DFE(c,m);HRESULT hr=c##m(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13);DFL(c,m,hr);return hr;} STDMETHOD(c##m)(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12,t13 a13)
#define _DECLARE_DEBUG_FUNCENTRY_13(c,m,t1,a1,t2,a2,t3,a3,t4,a4,t5,a5,t6,a6,t7,a7,t8,a8,t9,a9,t10,a10,t11,a11,t12,a12,t13,a13) STDMETHOD(m)(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12,t13 a13) {return c##m(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13);} STDMETHOD(c##m)(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12,t13 a13)
#define IMPLEMENT_DEBUG_FUNCENTRY_13(c,m,t1,a1,t2,a2,t3,a3,t4,a4,t5,a5,t6,a6,t7,a7,t8,a8,t9,a9,t10,a10,t11,a11,t12,a12,t13,a13) STDMETHODIMP c::c##m(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12,t13 a13)
#else
#define DECLARE_DEBUG_FUNCENTRY_13(c,m,t1,a1,t2,a2,t3,a3,t4,a4,t5,a5,t6,a6,t7,a7,t8,a8,t9,a9,t10,a10,t11,a11,t12,a12,t13,a13) STDMETHOD(m)(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12,t13 a13)
#define _DECLARE_DEBUG_FUNCENTRY_13(c,m,t1,a1,t2,a2,t3,a3,t4,a4,t5,a5,t6,a6,t7,a7,t8,a8,t9,a9,t10,a10,t11,a11,t12,a12,t13,a13) STDMETHOD(m)(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12,t13 a13)
#define IMPLEMENT_DEBUG_FUNCENTRY_13(c,m,t1,a1,t2,a2,t3,a3,t4,a4,t5,a5,t6,a6,t7,a7,t8,a8,t9,a9,t10,a10,t11,a11,t12,a12,t13,a13) STDMETHODIMP c::m(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12,t13 a13)
#endif
////////////////////////////////////////////////////////////////
// 14 Argumente
#if defined(_DEBUG)
#define DECLARE_DEBUG_FUNCENTRY_14(c,m,t1,a1,t2,a2,t3,a3,t4,a4,t5,a5,t6,a6,t7,a7,t8,a8,t9,a9,t10,a10,t11,a11,t12,a12,t13,a13,t14,a14) STDMETHOD(m)(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12,t13 a13,t14 a14) {DFE(c,m);HRESULT hr=c##m(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14);DFL(c,m,hr);return hr;} STDMETHOD(c##m)(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12,t13 a13,t14 a14)
#define _DECLARE_DEBUG_FUNCENTRY_14(c,m,t1,a1,t2,a2,t3,a3,t4,a4,t5,a5,t6,a6,t7,a7,t8,a8,t9,a9,t10,a10,t11,a11,t12,a12,t13,a13,t14,a14) STDMETHOD(m)(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12,t13 a13,t14 a14) {return c##m(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14);} STDMETHOD(c##m)(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12,t13 a13,t14 a14)
#define IMPLEMENT_DEBUG_FUNCENTRY_14(c,m,t1,a1,t2,a2,t3,a3,t4,a4,t5,a5,t6,a6,t7,a7,t8,a8,t9,a9,t10,a10,t11,a11,t12,a12,t13,a13,t14,a14) STDMETHODIMP c::c##m(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12,t13 a13,t14 a14)
#else
#define DECLARE_DEBUG_FUNCENTRY_14(c,m,t1,a1,t2,a2,t3,a3,t4,a4,t5,a5,t6,a6,t7,a7,t8,a8,t9,a9,t10,a10,t11,a11,t12,a12,t13,a13,t14,a14) STDMETHOD(m)(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12,t13 a13,t14 a14)
#define _DECLARE_DEBUG_FUNCENTRY_14(c,m,t1,a1,t2,a2,t3,a3,t4,a4,t5,a5,t6,a6,t7,a7,t8,a8,t9,a9,t10,a10,t11,a11,t12,a12,t13,a13,t14,a14) STDMETHOD(m)(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12,t13 a13,t14 a14)
#define IMPLEMENT_DEBUG_FUNCENTRY_14(c,m,t1,a1,t2,a2,t3,a3,t4,a4,t5,a5,t6,a6,t7,a7,t8,a8,t9,a9,t10,a10,t11,a11,t12,a12,t13,a13,t14,a14) STDMETHODIMP c::m(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12,t13 a13,t14 a14)
#endif
////////////////////////////////////////////////////////////////
// 15 Argumente
#if defined(_DEBUG)
#define DECLARE_DEBUG_FUNCENTRY_15(c,m,t1,a1,t2,a2,t3,a3,t4,a4,t5,a5,t6,a6,t7,a7,t8,a8,t9,a9,t10,a10,t11,a11,t12,a12,t13,a13,t14,a14,t15,a15) STDMETHOD(m)(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12,t13 a13,t14 a14,t15 a15) {DFE(c,m);HRESULT hr=c##m(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15);DFL(c,m,hr);return hr;} STDMETHOD(c##m)(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12,t13 a13,t14 a14,t15 a15)
#define _DECLARE_DEBUG_FUNCENTRY_15(c,m,t1,a1,t2,a2,t3,a3,t4,a4,t5,a5,t6,a6,t7,a7,t8,a8,t9,a9,t10,a10,t11,a11,t12,a12,t13,a13,t14,a14,t15,a15) STDMETHOD(m)(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12,t13 a13,t14 a14,t15 a15) {return c##m(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15);} STDMETHOD(c##m)(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12,t13 a13,t14 a14,t15 a15)
#define IMPLEMENT_DEBUG_FUNCENTRY_15(c,m,t1,a1,t2,a2,t3,a3,t4,a4,t5,a5,t6,a6,t7,a7,t8,a8,t9,a9,t10,a10,t11,a11,t12,a12,t13,a13,t14,a14,t15,a15) STDMETHODIMP c::c##m(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12,t13 a13,t14 a14,t15 a15)
#else
#define DECLARE_DEBUG_FUNCENTRY_15(c,m,t1,a1,t2,a2,t3,a3,t4,a4,t5,a5,t6,a6,t7,a7,t8,a8,t9,a9,t10,a10,t11,a11,t12,a12,t13,a13,t14,a14,t15,a15) STDMETHOD(m)(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12,t13 a13,t14 a14,t15 a15)
#define _DECLARE_DEBUG_FUNCENTRY_15(c,m,t1,a1,t2,a2,t3,a3,t4,a4,t5,a5,t6,a6,t7,a7,t8,a8,t9,a9,t10,a10,t11,a11,t12,a12,t13,a13,t14,a14,t15,a15) STDMETHOD(m)(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12,t13 a13,t14 a14,t15 a15)
#define IMPLEMENT_DEBUG_FUNCENTRY_15(c,m,t1,a1,t2,a2,t3,a3,t4,a4,t5,a5,t6,a6,t7,a7,t8,a8,t9,a9,t10,a10,t11,a11,t12,a12,t13,a13,t14,a14,t15,a15) STDMETHODIMP c::m(t1 a1,t2 a2,t3 a3,t4 a4,t5 a5,t6 a6,t7 a7,t8 a8,t9 a9,t10 a10,t11 a11,t12 a12,t13 a13,t14 a14,t15 a15)
#endif
#endif // __DEBUG_FUNCENTRY_H__D371C6C0_1BC0_11d2_8F7D_0060085FC1CE
