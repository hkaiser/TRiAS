//***********************************************
// Author:  Kjell Tangen (kat@computas.com)
// Filename: BxComExt.h
// Part of: BRIX COM Frameworks
// Copyright (C) Kjell Tangen, 1998-1999
// http://www.computas.com/brix/downloads/
//-----------------------------------------------
// Description:
// This file contains implementation classes for COM
// CComTypeInfoHolderEx - Extends ATL::CComTypeInfoHolder
// IDispatchImplEx      - Replaces ATL::IDispatchImpl
//
// The implementation uses ATL (3.0) and STL. 
// This file should be included right after the ATL-includes 
// (normally in stdafx.h)
//-----------------------------------------------
// Created: 1998-03-06  
// 1.0  1998-05-07
// 2.0  1998-11-19: Converted to ATL 3.0
// 3.0  1999-07-10: Uses IProvideClassInfo if implemented.
//                  If typeinfo lookup of the CLSID fails (e.g. if the
//                  class and interface are defined in different typelibs
//                  the correct type library for the class will be inquired.
//***********************************************

#if !defined(_DISPATCHIMPLEX_H__AE35CF30_3831_11D3_94FA_0080C786297B__INCLUDED_)
#define _DISPATCHIMPLEX_H__AE35CF30_3831_11D3_94FA_0080C786297B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#if !defined(_USE_DISPATCHIMPLEX)

// alles bleibt beim Alten
template <class T, const IID* piid, const CLSID* pclsid, const GUID* plibid, WORD wMajor, WORD wMinor, class tihclass>
class IDispatchImplEx :
public IDispatchImpl<T, piid, plibid, wMajor, wMinor, tihclass>
{
};

#else

// original code follows
#pragma warning( disable : 4786) // identifier truncated to 255 chars

// Required by STL:
bool operator < (const GUID g1, const GUID g2);

#ifndef _stdDispIdBase			// Override this to have another default
#define _stdDispIdBase -0x10F0
#endif

//***************************************************************************
// Class CComTypeInfoHolderEx
// Kjell Tangen, 1998 (kat@computas.com)
// Computas, Norway
// 
// CComTypeInfoHolderEx is used by the IDispatchImplEx template class to access
// the object's  type information in order to support dispatch clients.
// This class uses type info to dispatch to any dual or dispatchable
// interface on the class. If you have an ATL-based implementation,
// use the IDispatchImplEx class instead of the standard ATL::IDispatchImpl
// class if your COM-class has multiple dual interfaces and you want your 
// class to be scriptable. CComTypeInfoHolderEx will search through the type 
// info on each of the interfaces on the class and try to bind to the 
// dispatch member requested by the client.
// Even if your implementation is not based on ATL, this class can be used by
// your dual interface implementation, just look in the IDispatchImplEx
// class for details on how to use it.
// If the type info for an interface is in another type library than the class
// implementing it, the class should implement the IProvideClassInfo interface.
// Using ATL, this can be done using the IProvideClassInfo2Impl template.
//
// New in version 3.0:
// -------------------
// CComTypeInfoHolderEx now supports multiinterface dispatch in cases where a
// class implements interfaces defined by other another type library than the 
// module the class belongs to. Requirements for multiinterface dispatch to work
// in this more general case are:
// * The class implements IProvideClassInfo
// or
// * The class has a registered type library, i.e. a "TypeLib" subkey in the
// registry with a REG_SZ value equal to the LIBID of the module which the class belongs to 
//  
// Intented usage:
// ---------------
// If you have an ATL-based COM implementation, you will not use
// CComTypeInfoHolderEx directly. Instead you will just implement your dual interfaces
// by deriving your class from IDispatchImplEx instead of IDispatchImpl:
// class ATL_NO_VTABLE CMyClass : 
// public IProvideClassInfo2Impl<&CLSID_MyClass,&GUID_NULL, &LIBID_MyModule>
//	public IDispatchImplEx<IMyInterface, &IID_IMyInterface, &CLSID_MyClass, &LIBID_MyModule>,
//
// If the interface is defined in an imported type library, this will still work:
// class ATL_NO_VTABLE CMyClass : 
// public IProvideClassInfo2Impl<&CLSID_MyClass,&GUID_NULL, &LIBID_MyModule>
//	public IDispatchImplEx<IMyInterface, &IID_IMyInterface, &CLSID_MyClass, &LIBID_ImportedLib>,
// 
//
//***************************************************************************
/* Example:

  IDL:
  ----
	importlib("ImportedLib.tlb"); // Interface IC is defined here
	interface IA : IDispatch
	{
		HRESULT MethodOnIA();
	}:
	interface IB : IDispatch
	{
		HRESULT MethodOnIB();
	};
	coclass MyClass
	{
		[default] interface IA;
		interface IB;
		interface IC; // Defined in ImportedLib.tlb
	};

	C++ implementation:
	---------------------
	class ATL_NO_VTABLE CMyClass : 
	public IProvideClassInfo2Impl<&CLSID_MyClass,&GUID_NULL, &LIBID_MyLib>,
	public IDispatchImplEx<IA, &IID_IA, &CLSID_MyClass, &LIBID_MyLib>,
	public IDispatchImplEx<IB, &IID_IB, &CLSID_MyClass, &LIBID_MyLib>,
	public IDispatchImplEx<IC, &IID_IC, &CLSID_MyClass, &LIBID_ImportedLib>,
	public CComCoClass<CMyClass, &CLSID_MyClass>,
	public ISupportErrorInfo,
	public CComObjectRoot
	{
	..standard ATL implementation
	
	VB script client:
	-----------------
	  
	Dim instanceOfMyClass
	... got instanceOfMyClass from somewhere
	' Regardless of which interface I got hold of, 
	' I can script towards all methods on the class:
	instanceOfMyClass.MethodOnIA
	instanceOfMyClass.MethodOnIB
	instanceOfMyClass.MethodOnIC
*/

template<const IID* piid, const CLSID* pclsid, const GUID* plibid, long DispIdBase = _stdDispIdBase>
class CComTypeInfoHolderEx :
public CComTypeInfoHolder
{
private:
	typedef pair<long, IID> _dispidEntry;
	typedef vector<_dispidEntry> _idispidContainer;
	typedef map<_dispidEntry, long> _cdispidContainer;
	typedef _cdispidContainer::value_type  _cdispValue;
	typedef _idispidContainer::value_type  _idispValue;
	
	long m_nextIdx;
	_idispidContainer m_idispCont; // Contains Interface-specific dispids
	_cdispidContainer m_cdispCont; // Maps pairs of IID+dispid to class-specific dispids
	const GUID* m_pclsid;
	
public:
	CComTypeInfoHolderEx(const IID* pIID = piid, const CLSID* pCLSID = pclsid, const GUID* pLIBID = plibid) 
		: m_idispCont() 
	{
		m_nextIdx = 0;
		m_pguid = pIID;
		m_pclsid = pCLSID;
		m_plibid = pLIBID;
		m_wMajor = 1;
		m_wMinor = 0;
		m_pInfo = NULL;
		m_dwRef = 0;
	}
	long GetCDIDFromIdx(long idx) {return (DispIdBase + idx);}
	long GetIdxFromCDID(long cdid){return (cdid - DispIdBase);}
	long AddEntry(long lDID, IID);
	long GetDIDFromIdx(long idx){return m_idispCont[idx].first;}
	IID& GetIIDFromIdx(long idx) {return m_idispCont[idx].second;}
	HRESULT _FindName(ITypeInfo* pInfo, LPOLESTR* rgszNames, UINT cNames, DISPID* rgdispid);
	HRESULT _FindNameByReg(LPOLESTR* rgszNames, UINT cNames, DISPID* rgdispid);
	HRESULT GetIDsOfNames(IDispatch* pDisp, REFIID riid, LPOLESTR* rgszNames, UINT cNames,
		LCID lcid, DISPID* rgdispid);
	HRESULT Invoke(IDispatch* p, DISPID dispidMember, REFIID riid,
		LCID lcid, WORD wFlags, DISPPARAMS* pdispparams, VARIANT* pvarResult,
		EXCEPINFO* pexcepinfo, UINT* puArgErr);
};

template<const IID* piid, const CLSID* pclsid, const GUID* plibid, long DispIdBase>
inline long CComTypeInfoHolderEx<piid,pclsid,plibid,DispIdBase>::AddEntry(long lDID, IID riid)
{
	long lNewId;
	_dispidEntry e(lDID,riid);
	lNewId = m_nextIdx;
	// Check if the entry exist
	_cdispidContainer::iterator iter = m_cdispCont.find(e);
	if(iter != m_cdispCont.end())
	{
		lNewId = (*iter).second;
	}
	else
	{
		m_idispCont.insert(m_idispCont.end(), e);
		m_cdispCont.insert(_cdispValue(e,lNewId));
		InterlockedIncrement(&m_nextIdx);
	}
	return lNewId;
}

template<const IID* piid, const CLSID* pclsid, const GUID* plibid, long DispIdBase>
inline HRESULT CComTypeInfoHolderEx<piid,pclsid,plibid,DispIdBase>::_FindNameByReg(LPOLESTR* rgszNames, UINT cNames, DISPID* rgdispid)
{
	HRESULT hRes;
	// Search for the type library registered for the class
	LPOLESTR psClass = NULL;
	hRes = StringFromCLSID(*pclsid,&psClass);
	if(SUCCEEDED(hRes))
	{
		TCHAR sRegKey[64];
		USES_CONVERSION;
		_stprintf(sRegKey,_T("CLSID\\%s\\TypeLib"), OLE2T(psClass));
		HKEY hKey;
		hRes = ::RegOpenKeyEx(HKEY_CLASSES_ROOT, sRegKey,0, KEY_READ, &hKey);
		if(hRes == ERROR_SUCCESS)
		{
			TCHAR sLibId[40];
			DWORD dwSize = 40;
			DWORD dwType = REG_SZ;
			hRes = ::RegQueryValueEx(hKey, _T(""), NULL, &dwType, (LPBYTE)sLibId, &dwSize);
			if(SUCCEEDED(hRes))
			{
				GUID libid;
				hRes = ::CLSIDFromString(T2OLE(sLibId),&libid);
				if(SUCCEEDED(hRes))
				{
					ITypeLib* pTypeLib;
					// I know, I know - this is a hack, but it will work in most cases.
					// If it doesn't, tough luck. We have gone far enough!
					// If it fails here, you should try implementing IProvideClassInfo
					// on your class.
					hRes = LoadRegTypeLib(libid, 1, 0, LOCALE_USER_DEFAULT, &pTypeLib);
					if (SUCCEEDED(hRes))
					{
						ITypeInfo* pTypeInfo;
						hRes = pTypeLib->GetTypeInfoOfGuid(*pclsid, &pTypeInfo);
						if (SUCCEEDED(hRes))
						{
							hRes = _FindName(pTypeInfo, rgszNames, cNames, rgdispid);
							pTypeInfo->Release();
						}
						pTypeLib->Release();
					}
				}
			}
			::RegCloseKey(hKey);
		}
		CoTaskMemFree(psClass);
	}
	return hRes;
}

template<const IID* piid, const CLSID* pclsid, const GUID* plibid, long DispIdBase>
inline HRESULT CComTypeInfoHolderEx<piid,pclsid,plibid,DispIdBase>::_FindName(ITypeInfo* pClassTI, LPOLESTR* rgszNames, UINT cNames, DISPID* rgdispid)
{
	HRESULT hRes;
	// Search through the class type info
	TYPEATTR* pTAttr = NULL;
	hRes = pClassTI->GetTypeAttr(&pTAttr);
	if(SUCCEEDED(hRes) && pTAttr != NULL)
	{
		HREFTYPE hRefType;
		unsigned int i;
		bool bComplete = false;
		for(i = 0; !bComplete && i < pTAttr->cImplTypes; ++i)
		{
			hRes = pClassTI->GetRefTypeOfImplType(i,&hRefType);
			if(SUCCEEDED(hRes))
			{
				ITypeInfo* pifTypeInfo2;
				hRes = pClassTI->GetRefTypeInfo(hRefType, &pifTypeInfo2);
				if(SUCCEEDED(hRes) && pifTypeInfo2 != NULL)
				{
					long lDispId;
					hRes = pifTypeInfo2->GetIDsOfNames(rgszNames, cNames, &lDispId);
					if(SUCCEEDED(hRes))
					{
						TYPEATTR* pTAttr2 = NULL;
						hRes = pifTypeInfo2->GetTypeAttr(&pTAttr2);
						if(SUCCEEDED(hRes) && pTAttr2 != NULL)
						{
							bComplete = true;
							EnterCriticalSection(&_Module.m_csTypeInfoHolder);
							long idx = AddEntry(lDispId, (IID&)pTAttr2->guid);
							*rgdispid = GetCDIDFromIdx(idx);
							LeaveCriticalSection(&_Module.m_csTypeInfoHolder);
							pifTypeInfo2->ReleaseTypeAttr(pTAttr2);
						}
					}
					pifTypeInfo2->Release();
				}
			}
		}
		pClassTI->ReleaseTypeAttr(pTAttr);
	}
	return hRes;
}

template<const IID* piid, const CLSID* pclsid, const GUID* plibid, long DispIdBase>
inline HRESULT CComTypeInfoHolderEx<piid,pclsid,plibid,DispIdBase>::GetIDsOfNames(IDispatch* pDisp, REFIID riid, LPOLESTR* rgszNames,
																				  UINT cNames, LCID lcid, DISPID* rgdispid)
{
	HRESULT hRes;
	hRes = CComTypeInfoHolder::GetIDsOfNames(riid,rgszNames,cNames,
		lcid,rgdispid);
	if(SUCCEEDED(hRes))
		return hRes;
	else if(hRes != DISP_E_UNKNOWNNAME)
		return hRes;
	LPOLESTR psName = rgszNames[0];
	ITypeInfo* pInfo;
	// First, check for IProviderClassInfo
	if(!pDisp)
		return E_POINTER;
	IProvideClassInfo* pClassInfo = NULL;
	hRes = pDisp->QueryInterface(IID_IProvideClassInfo,(void**)&pClassInfo);
	if(SUCCEEDED(hRes))
	{
		hRes = pClassInfo->GetClassInfo(&pInfo);
		pClassInfo->Release();
		if(SUCCEEDED(hRes))
		{
			long lDispId;
			hRes = _FindName(pInfo, rgszNames, cNames, &lDispId);
			if(SUCCEEDED(hRes))
			{
				*rgdispid = lDispId;
				return S_OK;
			}
		}
	}
	hRes = GetTI(lcid, &pInfo);
	if (pInfo != NULL)
	{
		unsigned int idx;
		ITypeLib* pifTypeLib = NULL;
		hRes = pInfo->GetContainingTypeLib(&pifTypeLib, &idx);
		if(SUCCEEDED(hRes) && pifTypeLib != NULL)
		{
			ITypeInfo* pClassTI = NULL;
			hRes = pifTypeLib->GetTypeInfoOfGuid(*pclsid,&pClassTI);
			if(SUCCEEDED(hRes) && pClassTI != NULL)
			{
				ITypeComp* pifTypeComp = NULL;
				hRes = pInfo->GetTypeComp(&pifTypeComp);
				if(pifTypeComp != NULL)
				{
					ITypeInfo* pifTypeInfo2 = NULL;
					DESCKIND dc;
					BINDPTR bp;
					long lHashId = LHashValOfName(lcid,psName);
					hRes = pifTypeComp->Bind(psName,lHashId, 0,
						&pifTypeInfo2, &dc, &bp);
					if(SUCCEEDED(hRes) && pifTypeInfo2 != NULL)
					{
						long lDispId;
						hRes = pifTypeInfo2->GetIDsOfNames(rgszNames, cNames, &lDispId);
						if(SUCCEEDED(hRes))
						{
							TYPEATTR* pTAttr = NULL;
							hRes = pifTypeInfo2->GetTypeAttr(&pTAttr);
							if(SUCCEEDED(hRes) && pTAttr != NULL)
							{
								long idx;
								EnterCriticalSection(&_Module.m_csTypeInfoHolder);
								idx = AddEntry(lDispId, (IID&)pTAttr->guid);
								*rgdispid = GetCDIDFromIdx(idx);
								LeaveCriticalSection(&_Module.m_csTypeInfoHolder);
								pifTypeInfo2->ReleaseTypeAttr(pTAttr);
							}
						}
						pifTypeInfo2->Release();
					}
					else if(SUCCEEDED(hRes))
					{
						// Search through the class type info
						hRes = _FindName(pClassTI, rgszNames, cNames, rgdispid);
					}
					pifTypeComp->Release();
				}
				pClassTI->Release();
			}
			pifTypeLib->Release();
		}
		
		pInfo->Release();
	}
	if(FAILED(hRes) && !pClassInfo)
	{
		// One last shot: Search for another, registered type library
		hRes = _FindNameByReg(rgszNames, cNames, rgdispid);
	}
	return hRes;
}

template<const IID* piid, const CLSID* pclsid, const GUID* plibid, long DispIdBase>
inline HRESULT CComTypeInfoHolderEx<piid,pclsid,plibid,DispIdBase>::Invoke(IDispatch* p, DISPID dispidMember, REFIID riid,
																		   LCID lcid, WORD wFlags, DISPPARAMS* pdispparams, VARIANT* pvarResult,
																		   EXCEPINFO* pexcepinfo, UINT* puArgErr)
{
	HRESULT hRes;
	hRes = CComTypeInfoHolder::Invoke(p, dispidMember, riid, lcid, wFlags, 
		pdispparams, pvarResult,pexcepinfo, puArgErr);
	if(SUCCEEDED(hRes))
		return hRes;
	else if(hRes != DISP_E_MEMBERNOTFOUND)
		return hRes;
	
	SetErrorInfo(0, NULL);
	ITypeInfo* pInfo;
	hRes = GetTI(lcid, &pInfo);
	if (pInfo != NULL)
	{
		long ldid;
		unsigned int uTypeIndex;
		try
		{
			EnterCriticalSection(&_Module.m_csTypeInfoHolder);
			long idx = GetIdxFromCDID(dispidMember);
			_dispidEntry e = m_idispCont.at(idx);
			ldid = m_idispCont.at(idx).first;
			IID riid2 = m_idispCont.at(idx).second;
			LeaveCriticalSection(&_Module.m_csTypeInfoHolder);
			
			ITypeLib* pifTypeLib = NULL;
			hRes = pInfo->GetContainingTypeLib(&pifTypeLib, &uTypeIndex);
			if(pifTypeLib != NULL)
			{
				ITypeInfo* pifTypeInfo2 = NULL;
				hRes = pifTypeLib->GetTypeInfoOfGuid(riid2,&pifTypeInfo2);
				if(SUCCEEDED(hRes) && pifTypeInfo2 != NULL)
				{
					IDispatch* p2 = NULL;
					hRes = p->QueryInterface(riid2,(void**)&p2);
					if(p2 != NULL)
					{
						hRes = pifTypeInfo2->Invoke(p2, ldid, wFlags, pdispparams, pvarResult, pexcepinfo, puArgErr);
						p2->Release();
					}
					pifTypeInfo2->Release();
				}
				pifTypeLib->Release();
			}
		}
		catch(os_range_error)
		{
			return DISP_E_MEMBERNOTFOUND;
		}
		pInfo->Release();
	}
	return hRes;
}

template <class T, const IID* piid, const CLSID* pclsid, const GUID* plibid, WORD wMajor = 1,
WORD wMinor = 0, class tihclass = CComTypeInfoHolderEx<piid,pclsid,plibid> >
class ATL_NO_VTABLE IDispatchImplEx : public T
{
public:
	typedef tihclass _tihclass;
	IDispatchImplEx() 
	{
#if _ATL_VER == 0x0210 // AddRef/Release is used on the typeinfo holder in ATL2.1, so we must protect it
		_tih.AddRef(); 
#endif
	}
	~IDispatchImplEx() 
	{
#if _ATL_VER == 0x0210 // AddRef/Release is used on the typeinfo holder in ATL2.1, so we must protect it
		_tih.Release();
#endif
	}
	
	STDMETHOD(GetTypeInfoCount)(UINT* pctinfo)
	{*pctinfo = 1; return S_OK;}
	
	STDMETHOD(GetTypeInfo)(UINT itinfo, LCID lcid, ITypeInfo** pptinfo)
	{return _tih.GetTypeInfo(itinfo, lcid, pptinfo);}
	
	STDMETHOD(GetIDsOfNames)(REFIID riid, LPOLESTR* rgszNames, UINT cNames,
		LCID lcid, DISPID* rgdispid)
	{return _tih.GetIDsOfNames((IDispatch*)this, riid, rgszNames, cNames, lcid, rgdispid);}
	
	STDMETHOD(Invoke)(DISPID dispidMember, REFIID riid,
		LCID lcid, WORD wFlags, DISPPARAMS* pdispparams, VARIANT* pvarResult,
		EXCEPINFO* pexcepinfo, UINT* puArgErr)
	{return _tih.Invoke((IDispatch*)this, dispidMember, riid, lcid,
	wFlags, pdispparams, pvarResult, pexcepinfo, puArgErr);}

protected:
	static _tihclass _tih;
	static HRESULT GetTI(LCID lcid, ITypeInfo** ppInfo)
	{return _tih.GetTI(lcid, ppInfo);}
};

template <class T, const IID* piid, const CLSID* pclsid, const GUID* plibid, WORD wMajor,
WORD wMinor, class tihclass>
IDispatchImplEx<T, piid, pclsid, plibid, wMajor, wMinor, tihclass>::_tihclass
IDispatchImplEx<T, piid, pclsid, plibid, wMajor, wMinor, tihclass>::_tih;

// Required by STL
inline bool operator < (const GUID g1, const GUID g2)
{
	union
	{
		GUID g;
		struct
		{
			ULONG l1;
			ULONG l2;
			ULONG l3;
			ULONG l4;
		} l;
	} u1, u2;
	u1.g = g1;
	u2.g = g2;
	if(g1 == g2)
		return false;
	if(u1.l.l1 > u2.l.l1)
		return false;
	else if(u1.l.l1 < u2.l.l1)
		return true;
	else 
	{
		if(u1.l.l2 > u2.l.l2)
			return false;
		else if(u1.l.l2 < u2.l.l2)
			return true;
		else
		{
			if(u1.l.l3 > u2.l.l3)
				return false;
			else if(u1.l.l3 < u2.l.l3)
				return true;
			else
			{
				if(u1.l.l4 < u2.l.l4)
					return true;
				else
					return false;
			}
		}
	}
}

#endif // !defined(_USE_DISPATCHIMPLEX)

#endif // !defined(_DISPATCHIMPLEX_H__AE35CF30_3831_11D3_94FA_0080C786297B__INCLUDED_)
