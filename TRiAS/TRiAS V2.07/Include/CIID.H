// CIID.h - Definition/implementation of CIID a class for managing IIDs in ATL
// (c) Alex Stockton
// modified for ospace-strings: #HK971119
//////////////////////////////////////////////////////////////////////

#if !defined(_CIID_H__78EB26C0_D5BB_11d0_97C7_762411000000__INCLUDED_)
#define _CIID_H__78EB26C0_D5BB_11d0_97C7_762411000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <atlbase.h>
#include <ospace/std/string>

#ifndef ATL_NO_NAMESPACE
namespace ATL
{
#endif
	
#ifndef __IID_DEFINED__
#define __IID_DEFINED__
	
	typedef struct _IID
	{
		unsigned long Data1;
		unsigned short Data2;
		unsigned short Data3;
		unsigned char  Data4[8];
	} IID;
	
#endif // __IID_DEFINED__
	
	class CIID : public IID
	{
	public:
		enum INITCIID {
			INITCIID_InitFromGuid = 1,
			INITCIID_InitFromProgId = 2,
		};

		CIID()
		{
			*this = New();
		} // CIID_template()
		
		CIID(const GUID& guid)
		{
			*this = guid;
		} // CIID_template(const GUID& guid)
		
		CIID(const char* pstr, INITCIID rgMode = INITCIID_InitFromGuid)
		{
			USES_CONVERSION;
			IID* pIID = (IID*) CoTaskMemAlloc(sizeof(IID));
			HRESULT hr = S_OK;
			if (INITCIID_InitFromGuid == rgMode) {
				hr = IIDFromString(T2OLE(pstr), pIID);
				if (SUCCEEDED(hr))
					*this = *pIID;
			} else {
				hr = CLSIDFromProgID(T2OLE(pstr), pIID);
				if (SUCCEEDED(hr))
					*this = *pIID;
			}
			if (FAILED(hr))
				*this = GUID_NULL;
			CoTaskMemFree(pIID);
		} // CIID_template(const T* pstr)
		
		CIID(BSTR pstr, INITCIID rgMode = INITCIID_InitFromGuid)
		{
			IID* pIID = (IID *) CoTaskMemAlloc(sizeof(IID));
			HRESULT hr = S_OK;
			if (INITCIID_InitFromGuid == rgMode) {
				hr = IIDFromString(pstr, pIID);
				if (SUCCEEDED(hr))
					*this = *pIID;
			} else {
				hr = CLSIDFromProgID(pstr, pIID);
				if (SUCCEEDED(hr))
					*this = *pIID;
			}
			if (FAILED(hr))
				*this = GUID_NULL;
			CoTaskMemFree(pIID);
		} // CIID_template(const T* pstr)
		
		CIID(const os_string& str)
		{
			*this = str.c_str();
		} // CIID_template(const os_string& str)
		
		CIID& New()
		{
			GUID* pGUID = (GUID*) CoTaskMemAlloc(sizeof(GUID));
			if (SUCCEEDED(CoCreateGuid(pGUID)))
				*this = *pGUID;
			CoTaskMemFree(pGUID);
			return *this;
		} // CIID& New()
		
		CIID& operator=(const GUID& guid)
		{
			Data1 = guid.Data1;
			Data2 = guid.Data2;
			Data3 = guid.Data3;
			memcpy(Data4, guid.Data4, 8);
			return *this;
		} // CIID& operator=(const GUID& guid)
		
		os_string Description() const
		{
			os_string strRetVal(_T(""));
			
			os_string strKey(_T("Interface\\"));
			strKey += *this;
			
			CRegKey reg;
			if (ERROR_SUCCESS == reg.Open(HKEY_CLASSES_ROOT, strKey.c_str(), KEY_QUERY_VALUE))
			{
				DWORD dwLength = 256;
				LPTSTR pstr = NULL;
				
				ATLTRY(pstr = new TCHAR [dwLength]);
				if (ERROR_SUCCESS == reg.QueryValue(dwLength, pstr))
					strRetVal = pstr;
				
				delete [] pstr;
			}
			return strRetVal;
		} // os_string Description() const
		
		os_string ProgID() const
		{
			os_string strRetVal(_T(""));
			os_string strKey(_T("CLSID"));
			
			strKey += _T("\\");
			strKey += *this;
			strKey += _T("\\");
			strKey += _T("ProgID");
			
			CRegKey reg;
			
			if (ERROR_SUCCESS == reg.Open(HKEY_CLASSES_ROOT, strKey.c_str(), KEY_QUERY_VALUE))
			{
				DWORD dwLength = 256;
				LPTSTR pstr = NULL;
				
				ATLTRY(pstr = new TCHAR [dwLength]);
				if (ERROR_SUCCESS == reg.QueryValue(dwLength, pstr))
					strRetVal = pstr;
				
				delete [] pstr;
			}
			return strRetVal;
		} // os_string ProgID() const
		
		operator os_string() const
		{      
			USES_CONVERSION;
			LPOLESTR pstr = NULL;
			if (SUCCEEDED(StringFromIID(*this, &pstr)))
			{
				os_string str (OLE2CT(pstr));
				CoTaskMemFree(pstr);
				return str;
			}
			return _T("");
		} // operator os_string() const

		int operator== (const GUID& guid)
		{
			return (Data1 == guid.Data1 && Data2 == guid.Data2 &&
					Data3 == guid.Data3 && !memcmp(Data4, guid.Data4, 8)) ? true : false;
		}
		bool operator! ()
		{
			return (*this == GUID_NULL) ? true : false;
		}
				
   }; // class CIID
   
#ifndef ATL_NO_NAMESPACE
}; //namespace ATL
#endif

#endif // !defined(_CIID_H__78EB26C0_D5BB_11d0_97C7_762411000000__INCLUDED_)
