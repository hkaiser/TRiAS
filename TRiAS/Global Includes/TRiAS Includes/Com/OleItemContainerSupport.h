// $Header: $
// Copyright© 1999 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 28.05.99 10:27:15 
//
// @doc
// @module OleItemContainerSupport.h | Definition of supportclass for <i IOleItemContainer>

#if !defined(_OLEITEMCONTAINERSUPPORT_H__46709DA3_ED5C_11D1_8625_00600875138A__INCLUDED_)
#define _OLEITEMCONTAINERSUPPORT_H__46709DA3_ED5C_11D1_8625_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// OleItemCOntainer für beliebige Objekte

template<class T>
class ATL_NO_VTABLE COleItemContainerSupport :
	public IOleItemContainer
{
protected:
	HRESULT GetRunning (LPOLESTR pszItem, DWORD dwSpeedNeeded, IBindCtx *pbc, 
		REFIID riid, void **ppvObject, bool fTestRunningOnly)
	{
#if defined(_MFC_VER)
		AFX_MANAGE_STATE(AfxGetStaticModuleState())
#endif // _MFC_VER
		USES_CONVERSION;

	_KNOWNOBJECT_ENTRY *pObjs = T::_GetOleItemContainerSupportEntries();
	LPCTSTR pcItem = OLE2A(pszItem);

		while (NULL != pObjs->pcObjName) {
			if (0 == _tcsnccmp (pcItem, pObjs->pcObjName, pObjs->iObjNameSize)) 
			// retrieve object, eat ObjectTypeName and ':'
				return (((T *)this) ->* (pObjs->fnGetObject)) (pcItem+pObjs->iObjNameSize+1, dwSpeedNeeded, riid, ppvObject, fTestRunningOnly);
		
		// next objecttype
			pObjs++;
		}

	// hier noch nach embedded objects sehen (s.Inside OLE S. 484)
	// ...
		return E_FAIL;		// not supported or not found
	}


public:
/////////////////////////////////////////////////////////////////////////////
// Strukturen/Datentypen für Binding
	typedef HRESULT (T::* GETOBJECTPROC) (LPCTSTR pcItem, DWORD dwSpeedNeeded, REFIID riid, LPVOID *ppvObj, bool fTestRunningOnly);
	typedef HRESULT (T::* PARSEDISPLAYNAMEPROC) (LPCTSTR pcItem, ULONG ulSkipped, ULONG *pulEaten, IMoniker **ppmkOut);
	struct _KNOWNOBJECT_ENTRY {
		LPCTSTR pcObjName;			// ObjektTyp
		size_t iObjNameSize;		// Länge des ObjektTypBezeichners
		GETOBJECTPROC fnGetObject;
		PARSEDISPLAYNAMEPROC fnParseDisplayName;
	};

/////////////////////////////////////////////////////////////////////////////
// IParseDisplayName
	STDMETHOD(ParseDisplayName)(IBindCtx *pbc, LPOLESTR pszDisplayName, ULONG *pchEaten, IMoniker **ppmkOut)
	{
#if defined(_MFC_VER)
		AFX_MANAGE_STATE(AfxGetStaticModuleState())
#endif // _MFC_VER
		USES_CONVERSION;

		if (*pszDisplayName == L'!') {
			(*pchEaten)++;
			pszDisplayName++;
		}

	_KNOWNOBJECT_ENTRY *pObjs = T::_GetOleItemContainerSupportEntries();
	LPCTSTR pcItem = OLE2A(pszDisplayName);

		while (NULL != pObjs->pcObjName) {
			if (0 == _tcsnccmp (pcItem, pObjs->pcObjName, pObjs->iObjNameSize) && 
				NULL != pObjs->fnParseDisplayName) 
			{
			// eat remaining characters up to 0 or next '!'
				return (((T *)this) ->* (pObjs->fnParseDisplayName)) (pcItem, pObjs->iObjNameSize+1, pchEaten, ppmkOut);
			}

		// next objecttype
			pObjs++;
		}
		return MK_E_SYNTAX;
	}

// IOleContainer
	STDMETHOD(EnumObjects)(DWORD grfFlags, IEnumUnknown **ppenum)
	{
		return E_NOTIMPL; 
	}
	STDMETHOD(LockContainer)(BOOL fLock)
	{
		return ::CoLockObjectExternal (((T *)this) -> GetUnknown(), fLock, true);
	}

// IOleItemContainer
	STDMETHOD(GetObject)(LPOLESTR pszItem, DWORD dwSpeedNeeded, IBindCtx *pbc, REFIID riid, void **ppvObject)
	{
	HRESULT hr = GetRunning (pszItem, dwSpeedNeeded, pbc, riid, ppvObject, false);

		if (BINDSPEED_IMMEDIATE == dwSpeedNeeded && S_OK != hr)
			return MK_E_EXCEEDEDDEADLINE;

	// if object was running we are done!
		if (S_OK == hr) return S_OK;

	// alles andere muß explizit erst geladen und instantiiert werden
	// ...
		return hr;
	}
	STDMETHOD(GetObjectStorage)(LPOLESTR pszItem, IBindCtx *pbc, REFIID riid, void **ppvStorage)
	{
		return E_NOTIMPL; 
	}
	STDMETHOD(IsRunning)(LPOLESTR pszItem)
	{
		return GetRunning (pszItem, BINDSPEED_INDEFINITE, NULL, IID_NULL, NULL, true);
	}
};

/////////////////////////////////////////////////////////////////////////////
// OLEITEMCONTAINERSUPPORT-Map Makros
#define BEGIN_OLEITEMCONTAINERSUPPORT_MAP(x) public: \
	typedef x _ComOleItemContainerClass; \
	static _KNOWNOBJECT_ENTRY* WINAPI _GetOleItemContainerSupportEntries() { \
	static _KNOWNOBJECT_ENTRY _entries[] = { 

#define OLEITEMCONTAINERSUPPORT_ENTRY(key,func)\
	{key, _tcsclen(key), _ComOleItemContainerClass::func, NULL},
#define OLEITEMCONTAINERSUPPORT_ENTRYEX(key,func1,func2)\
	{key, _tcsclen(key), _ComOleItemContainerClass::func1, _ComOleItemContainerClass::func2},

#define END_OLEITEMCONTAINERSUPPORT_MAP()   {NULL, 0, NULL, NULL}}; \
	return _entries; }

#endif // !defined(_OLEITEMCONTAINERSUPPORT_H__46709DA3_ED5C_11D1_8625_00600875138A__INCLUDED_)
