// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 28.06.2000 04:22:28 
//
// @doc
// @module PersistFileHelper.h | Declaration of the <c CPersistFileHelper> class

#if !defined(_PERSISTFILEHELPER_H__CDC00369_9F35_470A_A114_33A8526F9559__INCLUDED_)
#define _PERSISTFILEHELPER_H__CDC00369_9F35_470A_A114_33A8526F9559__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <Atl/Ciid.h>
#include <Com/PersistHelper.h>

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(Storage);
DefineSmartInterface(Stream);

///////////////////////////////////////////////////////////////////////////////
// Implementation des IPersistFile auf der Grundlage der Methode und Schnittstellen
// die auch in <Com/StreamHelpers.h> verwendet sind
template<typename T, const GUID *pCLSID = &T::GetObjectCLSID()>
class ATL_NO_VTABLE CPersistFileImpl
	: public CPersistImpl<T, IPersistFile, pCLSID>
{
public:
	typedef CPersistFileImpl<T, pCLSID> CPersistFileImpl_t;
	typedef CPersistImpl<T, IPersistFile, pCLSID> CPersistImpl_t;

	CPersistFileImpl() : 
		m_bstrName(T::GetFileExt()), m_fHasFileName(false) {}
	~CPersistFileImpl() {}

	BEGIN_COM_MAP(CPersistFileImpl)
		COM_INTERFACE_ENTRY(IPersistFile)
		COM_INTERFACE_ENTRY2(IPersist, IPersistFile)
	END_COM_MAP()

// IPersistFile
	STDMETHOD(IsDirty)(void)
	{
		return IsObjectDirty() ? S_OK : S_FALSE;
	}
	STDMETHOD(Load)(LPCOLESTR pszFileName, DWORD dwMode)
	{
	WStorage Stg;
	WStream Strm;
	DWORD rgMode = STGM_DIRECT|STGM_SHARE_EXCLUSIVE;

		if (STGM_READWRITE & dwMode)
			rgMode |= STGM_READWRITE;
		else
			rgMode |= STGM_READ;

	HRESULT hr = StgOpenStorage(pszFileName, NULL, rgMode, NULL, 0L, Stg.ppi());

		if (SUCCEEDED(hr)) {
		CIID ClsId;

			RETURN_FAILED_HRESULT(ReadClassStg(Stg, &ClsId));
			if (!InlineIsEqualGUID(ClsId, *pCLSID))
				return E_UNEXPECTED;	// bad file format

			RETURN_FAILED_HRESULT(Stg -> OpenStream(T::GetSubStreamName(), NULL, 
				STGM_DIRECT|STGM_SHARE_EXCLUSIVE|STGM_READ, 0L, Strm.ppi()));

		char szSignat[4];
		DWORD dwVersion;

			RETURN_FAILED_HRESULT(LoadItem (Strm, szSignat));
			RETURN_FAILED_HRESULT(LoadItem (Strm, dwVersion));
			RETURN_FAILED_HRESULT(static_cast<T *>(this) -> LoadData (Strm, dwVersion));

			m_bstrName = pszFileName;
			m_fHasFileName = true;
		}
		return hr;
	}
	STDMETHOD(Save)(LPCOLESTR pszFileName, BOOL fRemember)
	{
	// Datei/Substream erzeugen
	CComBSTR bstrName;

		if (NULL == pszFileName) {
			if (!m_fHasFileName)
				return E_UNEXPECTED;
			bstrName = m_bstrName;
		} else
			bstrName = pszFileName;

	WStorage Stg;
	WStream Strm;
	DWORD rgMode = STGM_DIRECT|STGM_READWRITE|STGM_SHARE_EXCLUSIVE|STGM_CREATE;
	
		RETURN_FAILED_HRESULT(StgCreateDocfile(bstrName, rgMode, 0L, Stg.ppi()));
		RETURN_FAILED_HRESULT(WriteClassStg(Stg, *pCLSID));
		RETURN_FAILED_HRESULT(WriteFmtUserTypeStg(Stg, T::GetClipFormat(), T::GetUserType()));
		RETURN_FAILED_HRESULT(Stg -> CreateStream(T::GetSubStreamName(), rgMode, 0L, 0L, Strm.ppi()));

	// eigentliche Daten speichern
	DWORD dw = static_cast<T *>(this) -> GetSignature();

		RETURN_FAILED_HRESULT(SaveItem(Strm, dw));
		dw = static_cast<T *>(this) -> GetVersion();							
		RETURN_FAILED_HRESULT(SaveItem(Strm, dw));

	bool fClearDirty = (NULL == pszFileName || (fRemember && !wcscmp (pszFileName, m_bstrName)));
	HRESULT hr = static_cast<T *>(this) -> SaveData (Strm, fClearDirty);

	// ggf. PropertySet speichern
		RETURN_FAILED_HRESULT(static_cast<T *>(this) -> SavePropertySet(Stg, rgMode));
		RETURN_FAILED_HRESULT(Stg -> Commit(STGC_DEFAULT));

	// ggf. Dateinamen speichern
		if (SUCCEEDED(hr)) {
			if (fRemember) {
			// Save As or Save Copy As			
				_ASSERTE(NULL != pszFileName);
				m_bstrName = pszFileName;
				m_fHasFileName = true;
			}
			if (fClearDirty)
				SetDirty(false);
		}
		return hr;
	}
	STDMETHOD(SaveCompleted)(LPCOLESTR pszFileName)
	{
		return S_OK;
	}
	STDMETHOD(GetCurFile)(LPOLESTR *ppszFileName)
	{
		if (NULL == ppszFileName)
			return E_POINTER;
		wcscpy (*ppszFileName, m_bstrName);
		return m_fHasFileName ? S_OK : S_FALSE;
	}

protected:
	CComBSTR m_bstrName;
	bool m_fHasFileName;

// Notanker für fehlende Funktionen in abgeleiteter Klasse
	static CLIPFORMAT GetClipFormat() { return RegisterClipboardFormat("PersistFileImpl"); }
	static LPWSTR GetUserType() { return L"PersistFileImpl"; }
	static LPCWSTR GetSubStreamName() { return GetUserType(); }

	HRESULT SavePropertySet(IStorage *pIStg, DWORD rgMode) { return S_OK; }
};

#endif // !defined(_PERSISTFILEHELPER_H__CDC00369_9F35_470A_A114_33A8526F9559__INCLUDED_)
