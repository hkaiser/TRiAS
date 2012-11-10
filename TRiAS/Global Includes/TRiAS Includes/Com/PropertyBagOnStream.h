// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 10/18/1998 11:11:34 PM
//
// @doc
// @module PropertyBagOnStream.h | Description goes here

#if !defined(_PROPERTYBAGONSTREAM_H__7CD55719_6427_11D2_9EDE_006008447800__INCLUDED_)
#define _PROPERTYBAGONSTREAM_H__7CD55719_6427_11D2_9EDE_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#if !defined(_USE_INMEMORYSTREAMS_FOR_BLOBS)
#include <Com/BlobSupport.h>
#else
#include <Com/InMemoryBlobSupport.h>
#endif 
#include <Com/PropVariant.h>
#include <Com/MemoryHelper.h>

#if defined(_USE_STREAMCOMPRESSION)
#include <ZLib/ZLibHelper.h>
#endif // defined(_USE_STREAMCOMPRESSION)

///////////////////////////////////////////////////////////////////////////////
// {7CD55718-6427-11D2-9EDE-006008447800}
extern "C" const CLSID __declspec(selectany) CLSID_PropertyBagOnStream = 
	{0x7cd55718,0x6427,0x11d2,{0x9e,0xde,0x00,0x60,0x08,0x44,0x78,0x00}};

///////////////////////////////////////////////////////////////////////////////
// benötigte SmartIF's
DefineSmartInterface(Stream);
DefineSmartInterface(PropertyBag);
DefineSmartInterface(PropertyStorage);
DefineSmartInterface(EnumSTATPROPSTG);

///////////////////////////////////////////////////////////////////////////////
// Wrapper/Adaptor um IStream durch einen IPropertyBag zu verpacken
class CPropertyBagOnStream :
	public CComObjectRootEx<CComObjectThreadModel>,
	public IPropertyBag,
	public CComCoClass<CPropertyBagOnStream, &CLSID_PropertyBagOnStream>
{
public:
	CPropertyBagOnStream() : 
		m_ulPropId(100), m_rgType(PROPERTYBAGTYPE_Unknown), 
		m_fIsDirty(false), m_fIsInitialized(false)
	{
	}
	~CPropertyBagOnStream() {}

	enum PROPERTYBAGTYPE {
		PROPERTYBAGTYPE_Unknown = 0,
		PROPERTYBAGTYPE_Read = 1,
		PROPERTYBAGTYPE_Write = 2,
	};
	
	DECLARE_NO_REGISTRY()
	BEGIN_COM_MAP(CPropertyBagOnStream)
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
			LARGE_INTEGER uliReal;

				uliReal.QuadPart = 0;
				THROW_FAILED_HRESULT(m_StrmStg -> Commit (STGC_DEFAULT));
				THROW_FAILED_HRESULT(m_StrmStg -> Seek (uliReal, STREAM_SEEK_END, (ULARGE_INTEGER *)&uliReal));

			// gespeicherten PropertySet abholen
			HGLOBAL hGbl = NULL;

				THROW_FAILED_HRESULT(::GetHGlobalFromStream (m_StrmStg, &hGbl));

			// zuerst am Anfang die Endposition vermerken, dann eigentliche Info hinterher
				{
				CGlobalMem::Lock<BYTE> MemLock (hGbl); 

					if (!MemLock) _com_issue_error(E_OUTOFMEMORY);

			// in jedem Fall neues Format schreiben (2*LARGE_INTEGER)
#if defined(_USE_STREAMCOMPRESSION)
				LARGE_INTEGER uli = uliReal;
				CZLibWrapper ZLib (uliReal.LowPart, MemLock);
				CGlobalMem ZLibMem;

					THROW_FAILED_HRESULT(ZLib.Compress (&uli.LowPart, &ZLibMem));
					if (uli.QuadPart < uliReal.QuadPart) {		// wenns weniger geworden ist
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

		// Streams freigeben
			m_StrmStg.Assign (NULL);
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
		} COM_CATCH;
		m_fIsDirty = true;
		return S_OK;
	}
	
protected:
	HRESULT InitForWriting (IStream *pIStrm, REFFMTID rfmtid)
	{
		if (m_fIsInitialized)
			return E_UNEXPECTED;

		_ASSERTE(NULL != pIStrm);
		m_Strm = pIStrm;

	// PropertyStorage im Speicher erzeugen
		RETURN_FAILED_HRESULT(::CreateStreamOnHGlobal (NULL, TRUE, m_StrmStg.ppi()));
		RETURN_FAILED_HRESULT(::StgCreatePropStg (m_StrmStg, rfmtid, &CLSID_PropertyBagOnStream, PROPSETFLAG_DEFAULT, 0L, m_Props.ppi()));
		RETURN_FAILED_HRESULT(m_Props -> Commit (STGC_DEFAULT));	// #HK000123: Added for empty sets

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
		THROW_FAILED_HRESULT(m_Strm -> Read (&uliReal, sizeof(ULARGE_INTEGER), NULL));

		if (fUseZLib) {		// Versionskontrolle
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
				THROW_FAILED_HRESULT(::CreateStreamOnHGlobal (ZLibMem.Detach(), TRUE, m_StrmStg.ppi()));	// Mem wird jetzt vom Stream verwaltet
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
				THROW_FAILED_HRESULT(::CreateStreamOnHGlobal (Mem.Detach(), TRUE, m_StrmStg.ppi()));	// Mem wird jetzt vom Stream verwaltet
			}
			THROW_FAILED_HRESULT(::StgOpenPropStg (m_StrmStg, rfmtid, PROPSETFLAG_DEFAULT, 0L, m_Props.ppi()));

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
	WStream m_StrmStg;

	WPropertyStorage m_Props;
	ULONG m_ulPropId;
	PROPERTYBAGTYPE m_rgType;

	bool m_fIsDirty;
	bool m_fIsInitialized;

	friend inline HRESULT CreatePropertyBagOnIStream (IStream *pStrm, REFFMTID rfmtid, IPropertyBag **ppIBag);
	friend inline HRESULT OpenPropertyBagOnIStream (IStream *pStrm, REFFMTID rfmtid, IPropertyBag **ppIBag, IEnumSTATPROPSTG **ppIEnum = NULL, bool fUseZLib = false);
};

///////////////////////////////////////////////////////////////////////////////
// Helperfunktion, welche ein PropertyBag-Objekt auf einem beliebigen Stream 
// erzeugt
inline
HRESULT CreatePropertyBagOnIStream (
	IStream *pStrm, REFFMTID rfmtid, IPropertyBag **ppIBag)
{
	if (NULL == ppIBag) return E_POINTER;
	COM_TRY {
	CComObject<CPropertyBagOnStream> *pBag = NULL;

		THROW_FAILED_HRESULT(CComObject<CPropertyBagOnStream>::CreateInstance (&pBag));

	WPropertyBag Bag (pBag);		// pendig AddRef

		THROW_FAILED_HRESULT(pBag -> InitForWriting (pStrm, rfmtid));
		*ppIBag = Bag.detach();

	} COM_CATCH;
	return S_OK;
}

inline
HRESULT OpenPropertyBagOnIStream (
	IStream *pStrm, REFFMTID rfmtid, IPropertyBag **ppIBag, IEnumSTATPROPSTG **ppIEnum, bool fUseZLib)
{
	if (NULL == ppIBag) return E_POINTER;
	COM_TRY {
	CComObject<CPropertyBagOnStream> *pBag = NULL;

		THROW_FAILED_HRESULT(CComObject<CPropertyBagOnStream>::CreateInstance (&pBag));

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

#endif // !defined(_PROPERTYBAGONSTREAM_H__7CD55719_6427_11D2_9EDE_006008447800__INCLUDED_)
