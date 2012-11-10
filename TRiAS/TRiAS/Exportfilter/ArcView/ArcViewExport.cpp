// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 03.07.2000 11:16:22
//
// @doc
// @module ArcViewExport.cpp | Implementation of the <c CArcViewExport> class

#include "stdafx.h"
#include "ArcViewImpl.h"

#include "../ExtDataEngineImpl.h"
#include "../CTRiASOEProxyImpl.h"

#include "ArcViewExport.h"

/////////////////////////////////////////////////////////////////////////////
// CPersistStreamInitImpl

HRESULT	CArcViewExport::OnInitNew() 
{
	COM_TRY {
		CExtDataEngineImpl_t::OnInitNew();
		CExtDataEngineImpl_t::put_SeparateOutput(FALSE);
		CExtDataEngineImpl_t::put_SeparateDirs(FALSE);
	} COM_CATCH;
	return S_OK;
}

HRESULT CArcViewExport::LoadData(LPSTREAM pStm, DWORD dwVersion) 
{
	COM_TRY {
		CExtDataEngineImpl_t::LoadData(pStm);
			CExtDataEngineImpl_t::put_SeparateOutput(FALSE);
			CExtDataEngineImpl_t::put_SeparateDirs(FALSE);
	} COM_CATCH;
	return S_OK;
}

HRESULT CArcViewExport::SaveData(LPSTREAM pStm, BOOL bClearDirty) 
{
	COM_TRY {
		CExtDataEngineImpl_t::SaveData(pStm, bClearDirty);
	} COM_CATCH;
	return S_OK;
}

LONGLONG CArcViewExport::GetDataSize() 
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
