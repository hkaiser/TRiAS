// Zusatzklassen zur ATL
// File: ATLCOMX.H

#ifndef __ATLCOMX_H__
#define __ATLCOMX_H__

#ifndef __cplusplus
	#error ATL requires C++ compilation (use a .cpp suffix)
#endif

#ifndef __ATLBASE_H__
	#error atlcom.h requires atlbase.h to be included first
#endif

#pragma pack(push, _ATL_PACKING)

template <class T, IID* piid, GUID* plibid, WORD wMajor = 1, WORD wMinor = 0>
class CComDispatchImpl : public T
{
public:
	CComDispatchImpl() {_tih.AddRef(); m_pIUnk = NULL;}
	~CComDispatchImpl() {_tih.Release();}

	STDMETHOD(GetTypeInfoCount)(UINT* pctinfo)
	{*pctinfo = 1; return S_OK;}

	STDMETHOD(GetTypeInfo)(UINT itinfo, LCID lcid, ITypeInfo** pptinfo)
	{return _tih.GetTypeInfo(itinfo, lcid, pptinfo);}

	STDMETHOD(GetIDsOfNames)(REFIID riid, LPOLESTR* rgszNames, UINT cNames,
		LCID lcid, DISPID* rgdispid)
	{return _tih.GetIDsOfNames(riid, rgszNames, cNames, lcid, rgdispid);}

	STDMETHOD(Invoke)(DISPID dispidMember, REFIID riid,
		LCID lcid, WORD wFlags, DISPPARAMS* pdispparams, VARIANT* pvarResult,
		EXCEPINFO* pexcepinfo, UINT* puArgErr)
	{	_ASSERTE(NULL != m_pIUnk);	// forgot to call SetProgIF ?
		return _tih.Invoke((IDispatch*)m_pIUnk, dispidMember, riid, lcid,
			wFlags, pdispparams, pvarResult, pexcepinfo, puArgErr);}
	void SetProgIF (IUnknown *pIUnk) { m_pIUnk = pIUnk; }	// no AddRef !
protected:
	static CComTypeInfoHolder _tih;
	static HRESULT GetTI(LCID lcid, ITypeInfo** ppInfo)
	{return _tih.GetTI(lcid, ppInfo);}
private:
	IUnknown *m_pIUnk;
};

template <class T, IID* piid, GUID* plibid, WORD wMajor = 1, WORD wMinor = 0>
CComTypeInfoHolder CComDispatchImpl<T, piid, plibid, wMajor, wMinor>::_tih =
{ piid, plibid, wMajor, wMinor, NULL, 0};

/////////////////////////////////////////////////////////////////////////////

#pragma pack(pop)

#endif // __ATLCOM_H__

/////////////////////////////////////////////////////////////////////////////
