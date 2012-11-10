// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 17.01.2002 14:45:11 
//
// @doc
// @module TRiASCSTearOff.h | Declaration of the <c CTRiASCSTearOff> class

#if !defined(_TRIASCSTEAROFF_H__EA864F0B_1D2A_4C9D_B0FD_BC3497BD25E6__INCLUDED_)
#define _TRIASCSTEAROFF_H__EA864F0B_1D2A_4C9D_B0FD_BC3497BD25E6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// CTRiASCSTearOff
template <typename BaseT>
class ATL_NO_VTABLE CTRiASCSTearOff :
	public CComTearOffObjectBase<BaseT>,
	public IPersistStreamInit,
	public ITRiASTransformGeometry
{
public:
	CTRiASCSTearOff() {}
	~CTRiASCSTearOff() {}

	BEGIN_COM_MAP(CTRiASCSTearOff)
		COM_INTERFACE_ENTRY(IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersistStream, IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
		COM_INTERFACE_ENTRY(ITRiASTransformGeometry)
	END_COM_MAP()

	ULONG OuterRelease()
	{
	ULONG ulCnt = CComTearOffObjectBase<BaseT>::OuterRelease();

		if (1 == ulCnt)		// wird nur noch vom Owner festgehalten
			return m_pOwner->m_TearOff.Release(), 0;

		return ulCnt;
	}

// IPersist
	STDMETHOD(GetClassID)(CLSID * pClassID)
	{
		return m_pOwner->GetClassID(pClassID);
	}

// IPersistStream
	STDMETHOD(IsDirty)()
	{
		return m_pOwner->IsDirty();
	}
	STDMETHOD(Load)(LPSTREAM pStm)
	{
		return m_pOwner->Load(pStm);
	}
	STDMETHOD(Save)(LPSTREAM pStm, BOOL fClearDirty)
	{
		return m_pOwner->Save(pStm, fClearDirty);
	}
	STDMETHOD(GetSizeMax)(ULARGE_INTEGER * pcbSize)
	{
		return m_pOwner->GetSizeMax(pcbSize);
	}

// IPersistStreamInit
	STDMETHOD(InitNew)()
	{
		return m_pOwner->InitNew();
	}

// IPersistMemory
	STDMETHOD(Load)(void * pvMem, ULONG cbSize)
	{
		return m_pOwner->Load(pvMem, cbSize);
	}
	STDMETHOD(Save)(void * pvMem, BOOL fClearDirty, ULONG cbSize)
	{
		return m_pOwner->Save(pvMem, fClearDirty, cbSize);
	}
	STDMETHOD(GetSizeMax)(ULONG * pcbSize)
	{
		return m_pOwner->GetSizeMax(pcbSize);
	}

// ITRiASTransformGeometry
	STDMETHOD(Transform)(/* [in]*/ struct CSID csGUID, /*[in]*/ ITRiASCSTransform * pCSTransform)
	{
		return m_pOwner->Transform(csGUID, pCSTransform);
	}
	STDMETHOD(TransformInverse)(/*[in]*/ struct CSID csGUID, /*[in]*/ ITRiASCSTransform * pCSTransform)
	{
		return m_pOwner->TransformInverse(csGUID, pCSTransform);
	}
};

///////////////////////////////////////////////////////////////////////////////
// CTRiASCSTearOff
template <typename BaseT>
class ATL_NO_VTABLE CTRiASCSTearOff2 :
	public CComTearOffObjectBase<BaseT>,
	public IPersistStreamInit,
	public IPersistMemoryWks,
	public ITRiASTransformGeometry
{
public:
	CTRiASCSTearOff2() {}
	~CTRiASCSTearOff2() {}

	BEGIN_COM_MAP(CTRiASCSTearOff2)
		COM_INTERFACE_ENTRY(IPersistMemoryGDO)
		COM_INTERFACE_ENTRY2(IPersistMemory, IPersistMemoryGDO)
		COM_INTERFACE_ENTRY(IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersistStream, IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
		COM_INTERFACE_ENTRY(IPersistMemoryWks)
		COM_INTERFACE_ENTRY(ITRiASTransformGeometry)
	END_COM_MAP()

	ULONG OuterRelease()
	{
	ULONG ulCnt = CComTearOffObjectBase<BaseT>::OuterRelease();

		if (1 == ulCnt)		// wird nur noc vom Owner festgehalten
			return m_pOwner->m_TearOff.Release(), 0;

		return ulCnt;
	}

// IPersist
	STDMETHOD(GetClassID)(CLSID * pClassID)
	{
		return m_pOwner->GetClassID(pClassID);
	}

// IPersistStream
	STDMETHOD(IsDirty)()
	{
		return m_pOwner->IsDirty();
	}
	STDMETHOD(Load)(LPSTREAM pStm)
	{
		return m_pOwner->Load(pStm);
	}
	STDMETHOD(Save)(LPSTREAM pStm, BOOL fClearDirty)
	{
		return m_pOwner->Save(pStm, fClearDirty);
	}
	STDMETHOD(GetSizeMax)(ULARGE_INTEGER * pcbSize)
	{
		return m_pOwner->GetSizeMax(pcbSize);
	}

// IPersistStreamInit
	STDMETHOD(InitNew)()
	{
		return m_pOwner->InitNew();
	}

// IPersistMemory
	STDMETHOD(Load)(void * pvMem, ULONG cbSize)
	{
		return m_pOwner->Load(pvMem, cbSize);
	}
	STDMETHOD(Save)(void * pvMem, BOOL fClearDirty, ULONG cbSize)
	{
		return m_pOwner->Save(pvMem, fClearDirty, cbSize);
	}
	STDMETHOD(GetSizeMax)(ULONG * pcbSize)
	{
		return m_pOwner->GetSizeMax(pcbSize);
	}

// IPersistMemoryGDO
	STDMETHOD(LoadGDO)(VOID * pMem, ULONG cbSize)
	{
		return m_pOwner->LoadGDO(pMem, cbSize);
	}
	STDMETHOD(SaveGDO)(VOID * pMem, BOOL fClearDirty, ULONG cbSize)
	{
		return m_pOwner->SaveGDO(pMem, fClearDirty, cbSize);
	}

// IPersistMemoryWks
	STDMETHODIMP GetSizeMaxWkb(ULONG *pulSize)
	{
		return m_pOwner->GetSizeMaxWkb(pulSize);
	}
	STDMETHODIMP LoadWkb(LPVOID pMem, ULONG cbSize)
	{
		return m_pOwner->LoadWkb(pMem, cbSize);
	}
	STDMETHODIMP SaveWkb(LPVOID pMem, BOOL fClearDirty, ULONG cbSize)
	{
		return m_pOwner->SaveWkb(pMem, fClearDirty, cbSize);
	}
	STDMETHODIMP LoadWkt(BSTR WKT)
	{
		return m_pOwner->LoadWkt(WKT);
	}
	STDMETHODIMP SaveWkt(BSTR *WKT, BOOL fClearDirty)
	{
		return m_pOwner->SaveWkt(WKT, fClearDirty);
	}

// ITRiASTransformGeometry
	STDMETHOD(Transform)(/* [in]*/ struct CSID csGUID, /*[in]*/ ITRiASCSTransform * pCSTransform)
	{
		return m_pOwner->Transform(csGUID, pCSTransform);
	}
	STDMETHOD(TransformInverse)(/*[in]*/ struct CSID csGUID, /*[in]*/ ITRiASCSTransform * pCSTransform)
	{
		return m_pOwner->TransformInverse(csGUID, pCSTransform);
	}
};

#endif // !defined(_TRIASCSTEAROFF_H__EA864F0B_1D2A_4C9D_B0FD_BC3497BD25E6__INCLUDED_)
