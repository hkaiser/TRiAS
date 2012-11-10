// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 23.06.99 10:39:27 
//
// @doc
// @module PropertyBagOnStorage.h | Implementation eines PropertyBags auf der Basis
// eines Storages

#if !defined(_PROPERTYBAGONSTORAGE_H__21EEB5E0_2947_11D3_94F5_0080C786297B__INCLUDED_)
#define _PROPERTYBAGONSTORAGE_H__21EEB5E0_2947_11D3_94F5_0080C786297B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <Com/PropVariant.h>
#include <Com/MemoryHelper.h>

#if defined(_USE_STREAMCOMPRESSION)
#include <ZLib/ZLibHelper.h>
#endif // defined(_USE_STREAMCOMPRESSION)

///////////////////////////////////////////////////////////////////////////////
// {4950F500-2947-11D3-94F5-0080C786297B}
extern "C" const IID __declspec(selectany) CLSID_PropertyBagOnStorage = 
	{0x4950f500,0x2947,0x11d3,{0x94,0xf5,0x00,0x80,0xc7,0x86,0x29,0x7b}};

///////////////////////////////////////////////////////////////////////////////
// benötigte SmartIF's
DefineSmartInterface(LockBytes);
DefineSmartInterface(Stream);
DefineSmartInterface(Storage);
DefineSmartInterface(PropertyBag);
DefineSmartInterface(PropertyStorage);
DefineSmartInterface(EnumSTATPROPSTG);

///////////////////////////////////////////////////////////////////////////////
// Wrapper/Adaptor um IStorage durch einen IPropertyBag zu verpacken
class CPropertyBagOnStorage :
	public CComObjectRootEx<CComObjectThreadModel>,
	public IPropertyBag,
	public CComCoClass<CPropertyBagOnStorage, &CLSID_PropertyBagOnStorage>
{
public:
	CPropertyBagOnStorage() : 
		m_ulPropId(100), m_rgType(PROPERTYBAGTYPE_Unknown), 
		m_fIsDirty(false), m_fIsInitialized(false)
	{
	}
	~CPropertyBagOnStorage() {}

	enum PROPERTYBAGTYPE {
		PROPERTYBAGTYPE_Unknown = 0,
		PROPERTYBAGTYPE_Read = 1,
		PROPERTYBAGTYPE_Write = 2,
	};
	
	DECLARE_NO_REGISTRY()
	BEGIN_COM_MAP(CPropertyBagOnStorage)
		COM_INTERFACE_ENTRY(IPropertyBag)
	END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()
	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	void FinalRelease()
	{
		COM_TRY {
		// alles freigeben
			if (m_fIsDirty) 
			{
				THROW_FAILED_HRESULT(m_Props -> Commit (STGC_DEFAULT));
			}
			m_Props.Assign(NULL);

			if (m_rgType == PROPERTYBAGTYPE_Write) {
			// ursprünglichen Stream hinter den PropertySet positionieren
				THROW_FAILED_HRESULT(m_StgStg -> Commit (STGC_DEFAULT));
				m_StgStg.Assign (NULL);		// Storage schließen
				
			// gespeicherten PropertySet abholen
			HGLOBAL hGbl = NULL;

				THROW_FAILED_HRESULT(::GetHGlobalFromILockBytes (m_LockBytes, &hGbl));

			// zuerst am Anfang die Endposition vermerken, dann eigentliche Info hinterher
				{
				CGlobalMem::Lock<BYTE> MemLock (hGbl); 

					if (!MemLock) 
						_com_issue_error(E_OUTOFMEMORY);

				ULARGE_INTEGER uliReal;

					uliReal.QuadPart = MemLock.GetSize();

			// in jedem Fall neues Format schreiben (2*LARGE_INTEGER)
#if defined(_USE_STREAMCOMPRESSION)
				ULARGE_INTEGER uli = uliReal;
				CZLibWrapper ZLib (uliReal.LowPart, MemLock);
				CGlobalMem ZLibMem;

					THROW_FAILED_HRESULT(ZLib.Compress (&uli.LowPart, &ZLibMem));
					if (uli.QuadPart < uliReal.QuadPart) {	// nur wenns weniger geworden ist
						THROW_FAILED_HRESULT(m_Strm -> Write (&uli, sizeof(ULARGE_INTEGER), NULL));
						THROW_FAILED_HRESULT(m_Strm -> Write (&uliReal, sizeof(ULARGE_INTEGER), NULL));
						THROW_FAILED_HRESULT(m_Strm -> Write (CGlobalMem::Lock<BYTE>(ZLibMem), uli.LowPart, NULL));
					} else {
						THROW_FAILED_HRESULT(m_Strm -> Write (&uliReal, sizeof(ULARGE_INTEGER), NULL));
						THROW_FAILED_HRESULT(m_Strm -> Write (&uliReal, sizeof(ULARGE_INTEGER), NULL));
						THROW_FAILED_HRESULT(m_Strm -> Write (MemLock, uliReal.LowPart, NULL));
					}
#else
					THROW_FAILED_HRESULT(m_Strm -> Write (&uliReal, sizeof(ULARGE_INTEGER), NULL));
					THROW_FAILED_HRESULT(m_Strm -> Write (&uliReal, sizeof(ULARGE_INTEGER), NULL));
					THROW_FAILED_HRESULT(m_Strm -> Write (MemLock, uliReal.LowPart, NULL));
#endif // defined(_USE_STREAMCOMPRESSION)
				}
			} 

		// Streams etc. freigeben
			m_LockBytes.Assign (NULL);
			m_Strm.Assign (NULL);

		} COM_CATCH_NORETURN;
	}

public:
// IPropertyBag
	STDMETHOD(Read)(LPCOLESTR pszPropName, VARIANT *pVar, IErrorLog *pErrorLog)
	{
		_ASSERTE(m_fIsInitialized);
		_ASSERTE(m_Props.IsValid());
		_ASSERTE(m_rgType != PROPERTYBAGTYPE_Unknown);

	CPropVariant vVal;

		RETURN_FAILED_HRESULT(vVal.ReadFromPropertyStorage (m_Props, pszPropName));
		return vVal.Detach (pVar);
	}
	STDMETHOD(Write)(LPCOLESTR pszPropName, VARIANT *pVar)
	{
		_ASSERTE(m_fIsInitialized);
		_ASSERTE(m_Props.IsValid());
		_ASSERTE(m_rgType == PROPERTYBAGTYPE_Write);
		_ASSERTE(NULL != pszPropName);

	CPropVariant vVal;

		COM_TRY {
			THROW_FAILED_HRESULT(vVal.Attach (pVar));
			THROW_FAILED_HRESULT(vVal.WriteToPropertyStorage (m_Props, pszPropName, ++m_ulPropId));
		} COM_CATCH_OP(vVal.Detach(pVar));
		m_fIsDirty = true;
		return S_OK;
	}
	
protected:
	HRESULT InitForWriting (IStream *pIStrm, REFFMTID rfmtid, IStorage **ppIStg = NULL)
	{
		if (m_fIsInitialized)
			return E_UNEXPECTED;

		_ASSERTE(NULL != pIStrm);
		m_Strm = pIStrm;

	// PropertyStorage im Speicher erzeugen
		RETURN_FAILED_HRESULT(::CreateILockBytesOnHGlobal (NULL, TRUE, m_LockBytes.ppi()));
		RETURN_FAILED_HRESULT(::StgCreateDocfileOnILockBytes (m_LockBytes, STGM_CREATE|STGM_READWRITE|STGM_SHARE_EXCLUSIVE|STGM_TRANSACTED, 0L, m_StgStg.ppi()));
		RETURN_FAILED_HRESULT(::StgCreatePropStg (m_StgStg, rfmtid, &CLSID_PropertyBagOnStorage, PROPSETFLAG_NONSIMPLE, 0L, m_Props.ppi()));
		RETURN_FAILED_HRESULT(m_Props -> Commit (STGC_DEFAULT));	// #HK000123: Added for empty sets

	// evtl. Storage liefern (z.B. um Streams reinzuhängen)
		if (NULL != ppIStg) {
		WStorage Stg (m_StgStg);

			*ppIStg = Stg.detach();
		}

		m_rgType = PROPERTYBAGTYPE_Write;
		m_fIsDirty = false;
		m_fIsInitialized = true;
		return S_OK;
	}
	HRESULT InitForReading (IStream *pIStrm, REFFMTID rfmtid, bool fUseZLib)
	{
		if (m_fIsInitialized)
			return E_UNEXPECTED;

		_ASSERTE(NULL != pIStrm);
		m_Strm = pIStrm;

	ULARGE_INTEGER uli, uliReal;
	bool fIsCompressed = false;

		THROW_FAILED_HRESULT(m_Strm -> Read (&uli, sizeof(ULARGE_INTEGER), NULL));

		if (fUseZLib) { 		// reine Versionskontrolle
			THROW_FAILED_HRESULT(m_Strm -> Read (&uliReal, sizeof(ULARGE_INTEGER), NULL));
			_ASSERTE(uli.QuadPart <= uliReal.QuadPart);
			fIsCompressed = (uli.QuadPart != uliReal.QuadPart) ? true : false;
		}

	CGlobalMem Mem (uli.LowPart);

		COM_TRY {
		// PropertyStorage im Speicher erzeugen
#if defined(_USE_STREAMCOMPRESSION)
			if (fUseZLib && fIsCompressed) {
			CGlobalMem::Lock<BYTE> MemLock (Mem); 

				if (!MemLock) _com_issue_error(E_OUTOFMEMORY);
				THROW_FAILED_HRESULT(m_Strm -> Read (MemLock, uli.LowPart, NULL));

			CZLibWrapper ZLib (uli.LowPart, MemLock);
			CGlobalMem ZLibMem;

				THROW_FAILED_HRESULT(ZLib.UnCompress (uliReal.LowPart, &ZLibMem));
				THROW_FAILED_HRESULT(::CreateILockBytesOnHGlobal (ZLibMem.Detach(), TRUE, m_LockBytes.ppi()));	// Mem wird jetzt vom Stream verwaltet
			} 
#else
			if (fUseZLib && fIsCompressed) {
				THROW_FAILED_HRESULT(E_UNEXPECTED);		// komprimiert, aber nicht reingeneriert
			}
#endif // defined(_USE_STREAMCOMPRESSION)
			else {
				{
				CGlobalMem::Lock<BYTE> MemLock (Mem); 

					if (!MemLock) _com_issue_error(E_OUTOFMEMORY);
					THROW_FAILED_HRESULT(m_Strm -> Read (MemLock, uli.LowPart, NULL));
				}
				THROW_FAILED_HRESULT(::CreateILockBytesOnHGlobal (Mem.Detach(), TRUE, m_LockBytes.ppi()));	// Mem wird jetzt vom Stream verwaltet
			}

			THROW_FAILED_HRESULT(::StgOpenStorageOnILockBytes (m_LockBytes, NULL, STGM_READ|STGM_SHARE_EXCLUSIVE|STGM_TRANSACTED, NULL, 0L, m_StgStg.ppi()));
			THROW_FAILED_HRESULT(::StgOpenPropStg (m_StgStg, rfmtid, PROPSETFLAG_NONSIMPLE, 0L, m_Props.ppi()));

		} COM_CATCH;

		m_rgType = PROPERTYBAGTYPE_Read;
		m_fIsInitialized = true;
		return S_OK;
	}
	HRESULT Enum (IEnumSTATPROPSTG **ppIEnum)
	{
		_ASSERTE(m_fIsInitialized);
		_ASSERTE(m_Props.IsValid());
		return m_Props -> Enum (ppIEnum);
	}

private:
	WStream m_Strm;
	WStorage m_StgStg;
	WLockBytes m_LockBytes;

	WPropertyStorage m_Props;
	ULONG m_ulPropId;
	PROPERTYBAGTYPE m_rgType;

	bool m_fIsDirty;
	bool m_fIsInitialized;

	friend inline HRESULT CreatePropertyBagOnIStorage (IStream *pStrm, REFFMTID rfmtid, IPropertyBag **ppIBag, IStorage **ppIStg = NULL);
	friend inline HRESULT OpenPropertyBagOnIStorage (IStream *pStrm, REFFMTID rfmtid, IPropertyBag **ppIBag, IEnumSTATPROPSTG **ppIEnum = NULL, bool fUseZLib = false);
};

///////////////////////////////////////////////////////////////////////////////
// Helperfunktion, welche ein PropertyBag-Objekt auf einem beliebigen Stream 
// erzeugt
inline
HRESULT CreatePropertyBagOnIStorage (
	IStream *pStrm, REFFMTID rfmtid, IPropertyBag **ppIBag, IStorage **ppIStg)
{
	if (NULL == ppIBag) return E_POINTER;
	COM_TRY {
	CComObject<CPropertyBagOnStorage> *pBag = NULL;

		THROW_FAILED_HRESULT(CComObject<CPropertyBagOnStorage>::CreateInstance (&pBag));

	WPropertyBag Bag (pBag);		// pendig AddRef

		THROW_FAILED_HRESULT(pBag -> InitForWriting (pStrm, rfmtid, ppIStg));
		*ppIBag = Bag.detach();

	} COM_CATCH;
	return S_OK;
}

inline
HRESULT OpenPropertyBagOnIStorage (
	IStream *pStrm, REFFMTID rfmtid, IPropertyBag **ppIBag, IEnumSTATPROPSTG **ppIEnum, bool fUseZLib)
{
	if (NULL == ppIBag) return E_POINTER;
	COM_TRY {
	CComObject<CPropertyBagOnStorage> *pBag = NULL;

		THROW_FAILED_HRESULT(CComObject<CPropertyBagOnStorage>::CreateInstance (&pBag));

	WPropertyBag Bag (pBag);		// pendig AddRef

		THROW_FAILED_HRESULT(pBag -> InitForReading (pStrm, rfmtid, fUseZLib));
		if (NULL != ppIEnum) 
		{
			THROW_FAILED_HRESULT(pBag -> Enum (ppIEnum))
		}
		*ppIBag = Bag.detach();

	} COM_CATCH;
	return S_OK;
}

#endif // !defined(_PROPERTYBAGONSTORAGE_H__21EEB5E0_2947_11D3_94F5_0080C786297B__INCLUDED_)
