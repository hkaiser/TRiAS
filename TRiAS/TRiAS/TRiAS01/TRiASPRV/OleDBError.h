// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 31.05.2001 22:35:27 
//
// @doc
// @module OleDBError.h | Deklaration der globalen Fehlerbehandlungsfunktionen

#if !defined(_OLEDBERROR_H__A6D24F2E_09B6_4122_95A9_57230177D603__INCLUDED_)
#define _OLEDBERROR_H__A6D24F2E_09B6_4122_95A9_57230177D603__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <OleDBMsg.hmc>
#include <ospace/std/map>

///////////////////////////////////////////////////////////////////////////////
// globale Fehlerbehandlungsfunktionen
HRESULT WINAPI OleDBError(HRESULT hrErr, REFCLSID rClsId, REFIID rIId, 
	DWORD dwMinor = IDENTIFIER_SDK_ERROR, DWORD dwDynamicErrorID = 0,
	DISPID dwDispId = 0, DISPPARAMS *pDispParams = NULL);

///////////////////////////////////////////////////////////////////////////////
// Klasse, welche die dynamischen Fehlertexte verwaltet
template<typename ThreadModel>
class CDynamicErrors :
	public map<DWORD, CComBSTR, less<DWORD> >
{
public:
	typedef ThreadModel _ThreadModel;
	typedef _ThreadModel::AutoCriticalSection _CritSec;

	CDynamicErrors() : m_dwCookie(100) {}
	~CDynamicErrors() {}

// neuen Eintrag hinzufügen
	DWORD GetNextId(LPCOLESTR pcoleErrText) 
	{ 
	CDynamicErrorLock l(this);

		_ASSERTE(find (m_dwCookie+1) == end());		// Eintrag darf noch nicht existieren

		ATLTRY(insert (value_type(++m_dwCookie, CComBSTR(pcoleErrText))));
		return m_dwCookie; 
	}

// Eintrag entfernen
	bool RemoveId(const DWORD dwCookie)
	{
	CDynamicErrorLock l(this);

		_ASSERTE(find (dwCookie) != end());			// Eintrag muß existieren

	iterator it = find (dwCookie);

		if (it != end()) {
			erase(it);
			return true;
		}
		return false;
	}

// Eintrag wiederfinden
	bool GetEntry (DWORD dwCookie, BSTR *pbstrError)
	{
		_ASSERTE(NULL != pbstrError);

	CDynamicErrorLock l(this);
	iterator it = find (dwCookie);

		if (it != end()) {
			*pbstrError = CComBSTR((*it).second).Detach();
			return true;
		}
		return false;		// not defined here
	}

	void Lock() { m_critsec.Lock(); }
	void Unlock() { m_critsec.Unlock(); }

private:
	_CritSec m_critsec;
	DWORD m_dwCookie;

// eigene LockKlasse
	class CDynamicErrorLock
	{
	public:
		CDynamicErrorLock(CDynamicErrors<ThreadModel> *p)
		{
			if (p)
				p->Lock();
			m_p = p;
		}

		~CDynamicErrorLock()
		{
			if (m_p)
				m_p->Unlock();
		}
		CDynamicErrors<ThreadModel> *m_p;
	};
};
extern CDynamicErrors<CComGlobalsThreadModel> s_mapDynErrors;

///////////////////////////////////////////////////////////////////////////////
// BasisKlasse, für sämtliche Objekte, die Fehlerbehandlung brauchen
template<typename T, const IID *pIId, const CLSID *pclsid = &CLSID_TRiASOleDB>
class ATL_NO_VTABLE CTRiASOleDBErrorBase 
{
public:
	CTRiASOleDBErrorBase() {}
	~CTRiASOleDBErrorBase () {}

// 'normale', statische Fehlermeldung registrieren
	HRESULT OleDBError(HRESULT hrErr, DWORD dwMinor = IDENTIFIER_SDK_ERROR, REFIID rIId = *pIId, 
		DISPID dwDispId = 0, DISPPARAMS *pDispParams = NULL)
	{
#if defined(_DEBUG)
	// Testen, ob das gegebene Interface auch ErrorInfos liefern kann
	CComQIPtr<ISupportErrorInfo> SEI(static_cast<T *>(this) -> GetUnknown());

		_ASSERTE(SEI != NULL && (InlineIsEqualGUID(rIId, IID_NULL) || S_OK == SEI -> InterfaceSupportsErrorInfo(rIId)));
#endif // defined(_DEBUG)

		return ::OleDBError(hrErr, *pclsid, rIId, dwMinor, 0, dwDispId, pDispParams);
	}

// dynamische Fehlermeldung registrieren
	HRESULT OleDBError(HRESULT hrErr, LPCSTR pcErrText, REFIID rIId = *pIId)
	{
		USES_CONVERSION;
		return OleDBError(hrErr, A2OLE(pcErrText), rIId);
	}
	HRESULT OleDBError(HRESULT hrErr, LPCOLESTR pcoleErrText, REFIID rIId = *pIId)
	{
#if defined(_DEBUG)
	// Testen, ob das gegebene Interface auch ErrorInfos liefern kann
	CComQIPtr<ISupportErrorInfo> SEI(static_cast<T *>(this) -> GetUnknown());

		_ASSERTE(SEI != NULL && (InlineIsEqualGUID(rIId, IID_NULL) || S_OK == SEI -> InterfaceSupportsErrorInfo(rIId)));
#endif // defined(_DEBUG)

		return ::OleDBError(hrErr, *pclsid, rIId, 0, s_mapDynErrors.GetNextId(pcoleErrText));
	}
};

///////////////////////////////////////////////////////////////////////////////
// Makros für Fehlertest und -registrierung

// neues Fehlerobjekt erzeugen, Systemfehlermeldung verwenden
#define MAKE_OLEDB_ERROR(x)	{ \
	HRESULT __hr=(x); \
		if(SUCCEEDED(__hr)) { \
			/* intentionally empty */ \
		} else { \
			return OleDBError(__hr); \
		} \
	}

// neues Fehlerobjekt erzeugen, eigene Fehlermeldung verwenden
#define MAKE_OLEDB_ERROR_EX(x, dwMinor)	{ \
	HRESULT __hr=(x); \
		if(SUCCEEDED(__hr)) { \
			/* intentionally empty */ \
		} else { \
			return OleDBError(__hr, dwMinor); \
		} \
	}
#define MAKE_OLEDB_ERROR_EX2(x, hr)	{ \
	HRESULT __hr=(x); \
		if(SUCCEEDED(__hr)) { \
			/* intentionally empty */ \
		} else { \
			return OleDBError(hr, __hr); \
		} \
	}

// evtl. aufgetretenen Fehler einfach weiterreichen
#define RETURN_ERROR(x) { \
	HRESULT __hr=(x); \
		if(SUCCEEDED(__hr)) { \
			/* intentionally empty */ \
		} else { \
			return (__hr); \
		} \
	}

#endif // !defined(_OLEDBERROR_H__A6D24F2E_09B6_4122_95A9_57230177D603__INCLUDED_)
