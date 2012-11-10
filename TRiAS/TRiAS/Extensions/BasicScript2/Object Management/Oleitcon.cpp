
#include "stdafx.h"
#include "resource.h"

DefineSmartInterface(Stream);

// GUIDS
#include "objmanguid.h"
#include "macrguid.h"
#include "iobjmex.h"
#include <iObjMan.h>

#include "enumex.h"
#include "ObjMn.h"

//////////////////////////////////////////////////////////////////
// 
STDMETHODIMP CObjectManagement::ParseDisplayName(LPBC, LPOLESTR, ULONG*, LPMONIKER*)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return E_NOTIMPL;
}

//////////////////////////////////////////////////////////////////
// 
STDMETHODIMP CObjectManagement::EnumObjects(DWORD grfFlags, LPENUMUNKNOWN* ppEnumUnk)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return m_pEnumObjects -> Clone(ppEnumUnk);
}

//////////////////////////////////////////////////////////////////
// 
STDMETHODIMP CObjectManagement::LockContainer(BOOL)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return E_NOTIMPL;
}

//////////////////////////////////////////////////////////////////
// 
STDMETHODIMP CObjectManagement::GetObject(LPOLESTR lpolestr, DWORD, LPBINDCTX, REFIID riid, LPVOID* lplpvoid)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	ASSERT(NULL != lpolestr);
	ASSERT(NULL != m_lpIStorage);

	COM_TRY {	
	// Geladenes Item ?
		THROW_FAILED_HRESULT(GetLoad(lpolestr));
	
	// Stream auf jeden Fall öffnen, bei Low-Memory auch Speichern möglich
	WStream IStream;

		THROW_FAILED_HRESULT(OpenStream (lpolestr, m_lpIStorage, IStream.ppi()));

	// Richtiges Interface rausreichen
		THROW_FAILED_HRESULT(GetUnknownFromStream (IStream, riid, lplpvoid));

	} COM_CATCH;
	return S_OK;
}

//////////////////////////////////////////////////////////////////
// 
STDMETHODIMP CObjectManagement::GetObjectStorage(LPOLESTR lpolestr, LPBINDCTX, REFIID riid, LPVOID* ppvStorage)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return E_NOTIMPL;
}

/////////////////////////////////////////////////////////////////
// 
STDMETHODIMP CObjectManagement::IsRunning(LPOLESTR)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return E_NOTIMPL;
}

