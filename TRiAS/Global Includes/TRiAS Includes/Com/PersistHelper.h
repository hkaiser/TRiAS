// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 28.06.2000 05:48:24 
//
// @doc
// @module PersistHelper.h | Declaration of the <c CPersistHelper> class

#if !defined(_PERSISTHELPER_H__128B64D5_AA13_4818_A108_D689E0477C13__INCLUDED_)
#define _PERSISTHELPER_H__128B64D5_AA13_4818_A108_D689E0477C13__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// Implementation des IPersist als Basisklasse für CPersistFileImpl und 
// CPersistStreamInitImpl
template<typename T, typename BaseIF, const GUID *pCLSID = &T::GetObjectCLSID()>
class ATL_NO_VTABLE CPersistImpl
	: public BaseIF
{
public:
	CPersistImpl() : m_fIsDirty(false), m_fIsInitialized(false) {}
	~CPersistImpl() {}
	
#if _MSC_VER <= 1100
	STDMETHOD(QueryInterface)(REFIID riid, void **ppvObject) = 0;
#endif // _MSC_VER <= 1100

	BEGIN_COM_MAP(CPersistImpl)
		COM_INTERFACE_ENTRY(IPersist)
	END_COM_MAP()

// IPersist
	STDMETHOD(GetClassID)(CLSID *pClassID) 
	{
		*pClassID = *pCLSID;
		return S_OK;
	}

protected:
	__int64 GetDataSize() { return sizeof(DWORD) + sizeof(DWORD); }	// Signatur, Version, SizeMax

	void SetDirty (bool fDirty = true) { m_fIsDirty = fDirty; }
	bool IsObjectDirty() { return m_fIsDirty; }

	void SetInitialized (bool fIsInitialized = true) { m_fIsInitialized = fIsInitialized; }
	bool IsInitialized() { return m_fIsInitialized; }

private:
	bool m_fIsDirty;
	bool m_fIsInitialized;
};

#endif // !defined(_PERSISTHELPER_H__128B64D5_AA13_4818_A108_D689E0477C13__INCLUDED_)
