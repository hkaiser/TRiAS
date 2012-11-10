// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 23.01.2001 12:47:16 
//
// @doc
// @module MapInfoExport.cpp | Definition of the <c CMapInfoExport> class

#include "stdafx.h"
#include "MapInfoImpl.h"

#include "../ExtDataEngineImpl.h"
#include "../CTRiASOEProxyImpl.h"

#include "MapInfoExport.h"

/////////////////////////////////////////////////////////////////////////////
// CPersistStreamInitImpl

HRESULT	CMapInfoExport::OnInitNew() 
{
	COM_TRY {
		CExtDataEngineImpl_t::OnInitNew();
		CExtDataEngineImpl_t::put_SeparateOutput(FALSE);
		CExtDataEngineImpl_t::put_SeparateDirs(FALSE);
	} COM_CATCH;
	return S_OK;
}

HRESULT CMapInfoExport::LoadData(LPSTREAM pStm, DWORD dwVersion) 
{
	COM_TRY {
		CExtDataEngineImpl_t::LoadData(pStm);
			CExtDataEngineImpl_t::put_SeparateOutput(FALSE);
			CExtDataEngineImpl_t::put_SeparateDirs(FALSE);
	} COM_CATCH;
	return S_OK;
}

HRESULT CMapInfoExport::SaveData(LPSTREAM pStm, BOOL bClearDirty) 
{
	COM_TRY {
		CExtDataEngineImpl_t::SaveData(pStm, bClearDirty);
	} COM_CATCH;
	return S_OK;
}

LONGLONG CMapInfoExport::GetDataSize() 
{
	ULARGE_INTEGER	uliSize, uliSum;
	uliSize.QuadPart = 0;
	uliSum.QuadPart = 0;
	COM_TRY {
		uliSize.QuadPart = CExtDataEngineImpl_t::GetDataSize();
		uliSum.QuadPart += uliSize.QuadPart;
	} COM_CATCH;
	return uliSum.QuadPart;
}
