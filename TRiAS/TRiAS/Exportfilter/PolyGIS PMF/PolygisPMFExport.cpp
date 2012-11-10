// PolygisPMFExport.cpp : Implementation of CPolygisPMFExport
#include "stdafx.h"

#include <esnecil.h>
#include "PolygisPMFImpl.h"

#include "../ExtDataEngineImpl.h"
#include "../CTRiASOEProxyImpl.h"

#include <Errcodes.hxx>

#include "PolygisPMFExport.h"

// Registrieren nur, wenn GCO Produktion aktiv ist
HRESULT WINAPI CPolygisPMFExport::UpdateRegistry(BOOL bRegister)
{
CEsnecil esnecil;

	if (esnecil.VerifyOptions(CKIOPTION_GCOPRODUCTION))
		return _Module.UpdateRegistryFromResource(IDR_POLYGISPMFEXPORT, bRegister);

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// CPersistStreamInitImpl

HRESULT	CPolygisPMFExport::OnInitNew( ) {
	COM_TRY {
		CExtDataEngineImpl_t::OnInitNew();
// KK000816
		CExtDataEngineImpl_t::put_SeparateOutput(FALSE);
		CExtDataEngineImpl_t::put_SeparateDirs(FALSE);
	} COM_CATCH;
	return S_OK;
}
HRESULT CPolygisPMFExport::LoadData( LPSTREAM pStm, DWORD dwVersion ) {
	COM_TRY {
		CExtDataEngineImpl_t::LoadData(pStm);
// KK000816
		CExtDataEngineImpl_t::put_SeparateOutput(FALSE);
		CExtDataEngineImpl_t::put_SeparateDirs(FALSE);
//		CExtDataEngineImpl_t::put_SeparateOutput(TRUE);
	} COM_CATCH;
	return S_OK;
}
HRESULT CPolygisPMFExport::SaveData( LPSTREAM pStm, BOOL bClearDirty ) {
	COM_TRY {
		CExtDataEngineImpl_t::SaveData(pStm,bClearDirty);
	} COM_CATCH;
	return S_OK;
}
LONGLONG CPolygisPMFExport::GetDataSize( ) {
	ULARGE_INTEGER	uliSize, uliSum;
	uliSize.QuadPart = 0;
	uliSum.QuadPart = 0;
	COM_TRY {
		uliSize.QuadPart = CExtDataEngineImpl_t::GetDataSize();
		uliSum.QuadPart += uliSize.QuadPart;
	} COM_CATCH;
	return uliSum.QuadPart;
}
