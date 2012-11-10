// CDynQueryObjEnums.cpp : Implementation of CDynQueryApp and DLL registration.

#include "stdafx.h"
#include "DynQueryRes.h"

#include <ospace/source.h>
#include <ospace/stream.h>
#include <ospace/com/olestrea.h>

#include "Helper.h"
#include "DynQuery.hxx"

/////////////////////////////////////////////////////////////////////////////
// SmartInterfaces
DefineSmartInterface(PersistStream);
DefineSmartInterface(Stream);

/////////////////////////////////////////////////////////////////////////////
// streaming support
OS_STREAMABLE_0((map<os_string, CVisEnum, less<os_string> > *), os_user_start_id+1)
OS_STREAMABLE_0((CVisEnum *), os_user_start_id+2)

/////////////////////////////////////////////////////////////////////////////
// IDynQueryObjEnums methods
STDMETHODIMP CDynQueryObjEnums::Insert(BSTR bstrName, IEnumObjectsByNumber * pIObjs, DVisInfo * pIVis)
{
	USES_CONVERSION;

LPCSTR pcName = OLE2A(bstrName);

// evtl. existierende Einträge ersetzen
	if (m_mapEnums.find (pcName) != m_mapEnums.end()) {
		m_mapEnums.erase (pcName);
		m_fIsDirty = true;
	}

pair<CEnumList::iterator, bool> p =
	m_mapEnums.insert (pcName, CVisEnum(pIObjs, pIVis));

	if (p.second) {
		m_fIsDirty = true;
		return S_OK;
	} else 
		return S_FALSE;
}

STDMETHODIMP CDynQueryObjEnums::Erase(BSTR bstrName)
{
	USES_CONVERSION;

	if (m_mapEnums.erase (OLE2A(bstrName)) == 1) {
		m_fIsDirty = true;
		return S_OK;
	} else
		return E_FAIL;
}

STDMETHODIMP CDynQueryObjEnums::Find(long lONr, BSTR *pbstrName, DVisInfo **ppIVis)
{
	TEST_E_POINTER("CDynQueryObjEnums::Find", pbstrName);

	for (CEnumList::iterator it = m_mapEnums.begin(); 
		 it != m_mapEnums.end(); ++it)
	{
		if ((*it).second.find (lONr)) {
		// wer zuerst kommt, malt zuerst
		CComBSTR bstrName ((*it).first.c_str());

			*pbstrName = bstrName.Detach();
			if (NULL != ppIVis) {
				*ppIVis = (*it).second.vis();
				if (*ppIVis) (*ppIVis) -> AddRef();
			}
			return S_OK;
		}
	}
	return S_FALSE;
}

STDMETHODIMP CDynQueryObjEnums::get_ViewName(BSTR * pVal)
{
	if (!m_fInitialized) return E_UNEXPECTED;
	TEST_E_POINTER("CDynQueryObjEnums::get_ViewName", pVal);

	try {
	CComBSTR bstr (m_strView.c_str());

		*pVal = bstr.Detach();
	
	} catch (_com_error &e) {
		return _COM_ERROR(e);
	}

	return S_OK;
}

STDMETHODIMP CDynQueryObjEnums::put_ViewName(BSTR newVal)
{
	if (!m_fInitialized)
		return E_UNEXPECTED;

	USES_CONVERSION;

	m_strView = OLE2A(newVal);
	m_fIsDirty = true;
	return S_OK;
}

STDMETHODIMP CDynQueryObjEnums::ClassFromIdent (long lIdent, BSTR *pbstrOKS)
{
	if (!m_fInitialized) return E_UNEXPECTED;
	TEST_E_POINTER("CDynQueryObjEnums::ClassFromIdent", pbstrOKS);

	for (CEnumList::iterator it = m_mapEnums.begin(); 
		 it != m_mapEnums.end(); ++it)
	{
		if ((ULONG)lIdent == (*it).second.PseudoIdent()) {
		// wer zuerst kommt, malt zuerst
		CComBSTR bstrName ((*it).first.c_str());

			*pbstrOKS = bstrName.Detach();
			return S_OK;
		}
	}

	return S_FALSE;		// nichts gefunden
}

STDMETHODIMP CDynQueryObjEnums::IdentFromClass(BSTR bstrOKS, long *plIdent)
{
	if (!m_fInitialized) return E_UNEXPECTED;
	TEST_E_POINTER("CDynQueryObjEnums::IdentFromClass", plIdent);

	USES_CONVERSION;

CEnumList::iterator it = m_mapEnums.find (OLE2A(bstrOKS));

	if (it == m_mapEnums.end()) 
		return S_FALSE;		// nichts gefunden

	*plIdent = (*it).second.PseudoIdent();
	return S_OK;
}

STDMETHODIMP CDynQueryObjEnums::EnumIdents(IUnknown **ppIIdents)
{
	if (!m_fInitialized) return E_UNEXPECTED;
	TEST_E_POINTER("CDynQueryObjEnums::EnumIdents", ppIIdents);

	*ppIIdents = NULL;

	try {
	WEnumObjectsByNumber Enum (CLSID_EnumObjectsByNumber);

		for (CEnumList::iterator it = m_mapEnums.begin(); 
			 it != m_mapEnums.end(); ++it)
		{
			THROW_FAILED_HRESULT(Enum -> AddItem ((*it).second.PseudoIdent()));
		}

		*ppIIdents = Enum.detach();

	} catch (_com_error &e) {
		return _COM_ERROR(e); 
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// *** IPersist methods ***
STDMETHODIMP CDynQueryObjEnums::GetClassID (THIS_ CLSID *pClsID)
{
	TEST_E_POINTER("CDynQueryObjEnums::GetClassID", pClsID);
	*pClsID = CLSID_DynQueryObjEnums;
	return S_OK;
}

// *** IPersistStream methods ***
STDMETHODIMP CDynQueryObjEnums::IsDirty (void)
{
	return m_fIsDirty ? S_OK : S_FALSE;
}

STDMETHODIMP CDynQueryObjEnums::Load (IStream *pStm)
{
	if (m_fInitialized) return E_UNEXPECTED;

	try {
	iolestream stream;

		stream.setbuf (NULL, 0);
		stream.attach (pStm);

	os_bstream instream (os_adapter_for(stream));
	LONG dwVersion = 0;
	LONG fFlag = 0L;

		instream >> fFlag;
		instream.tag_primitives (fFlag ? true : false);

		instream >> dwVersion;
		if (dwVersion > DYNQUERYOBJENUMS_PERSISTVERSION)
			return E_UNEXPECTED;	// falsches Format

		instream >> m_strView;
		instream >> m_mapEnums;
		
	} catch (_com_error &e) {
		return _COM_ERROR(e);
	} catch (...) {
		return E_FAIL;
	}

	m_fInitialized = true;
	return S_OK;
}

STDMETHODIMP CDynQueryObjEnums::Save (IStream *pStm, BOOL fClearDirty)
{
	try {
	oolestream stream;

		stream.setbuf (NULL, 0);
		stream.attach (pStm);

	os_bstream outstream (os_adapter_for(stream));

#if defined(_DEBUG)
		outstream << 1L;
		outstream.tag_primitives (true);
#else
		outstream << 0L;
		outstream.tag_primitives (false);
#endif // _DEBUG

		outstream << LONG(DYNQUERYOBJENUMS_PERSISTVERSION);
		outstream << m_strView;
		outstream << m_mapEnums;
		
		if (fClearDirty)
			m_fIsDirty = false;
	
	} catch (_com_error &e) {
		return _COM_ERROR(e);
	} catch (...) {
		return E_FAIL;
	}
	return S_OK;
}

STDMETHODIMP CDynQueryObjEnums::GetSizeMax (ULARGE_INTEGER * pcbSize)
{
	ATLTRACENOTIMPL("CDynQueryObjEnums::GetSizeMax");
}

// *** IPersistStreamInit methods ***
STDMETHODIMP CDynQueryObjEnums::InitNew (void)
{
	if (m_fInitialized) return E_UNEXPECTED;

	m_fInitialized = true;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Speichern der Elemente einer ObjektListe

void os_write (os_bstream& stream, const CVisEnum& l)
{
WPersistStream SaveObjs (l.objs());
WPersistStream SaveVis (l.vis());

// neuen Stream im Speicher anlegen
WStream Stm;

	THROW_FAILED_HRESULT(CreateStreamOnHGlobal (NULL, true, Stm.ppi()));
	THROW_FAILED_HRESULT(OleSaveToStream (SaveVis, Stm));
	THROW_FAILED_HRESULT(OleSaveToStream (SaveObjs, Stm));

HGLOBAL hMem = NULL;

	THROW_FAILED_HRESULT(GetHGlobalFromStream (Stm, &hMem));

LPVOID pv = GlobalLock (hMem);
DWORD dwSize = GlobalSize (hMem);

	stream << dwSize;
	stream.write_chunk (pv, dwSize);

	GlobalUnlock (hMem);

	stream << l.PseudoIdent();
}

void os_read (os_bstream& stream, CVisEnum& l)
{
WFindLONG Objs;
WDVisInfo Vis;
DWORD dwSize;

	stream >> dwSize;

HGLOBAL hMem = GlobalAlloc (GHND, dwSize);

	if (NULL == hMem) _com_issue_error(E_OUTOFMEMORY);

LPVOID pv = GlobalLock (hMem);

	stream.read_chunk (pv, dwSize);
	GlobalUnlock (hMem);

// neuen Stream im Speicher anlegen
WStream Stm;

	THROW_FAILED_HRESULT(CreateStreamOnHGlobal (hMem, true, Stm.ppi()));

	THROW_FAILED_HRESULT(OleLoadFromStream (Stm, IID_DVisInfo, Vis.ppv()));
	THROW_FAILED_HRESULT(OleLoadFromStream (Stm, IID_IFindLONG, Objs.ppv()));

	l.m_Objs = Objs;
	l.m_Vis = Vis;

ULONG ulIdent;

	stream >> ulIdent;
	l.SetPseudoIdent(ulIdent);
}
