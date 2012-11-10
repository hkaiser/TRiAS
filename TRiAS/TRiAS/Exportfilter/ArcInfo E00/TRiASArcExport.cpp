#include "stdafx.h"
#include "TRiASArcImpl.h"

#include "../ExtDataEngineImpl.h"
#include "../CTRiASOEProxyImpl.h"

#include "TRiASArcExport.h"

/////////////////////////////////////////////////////////////////////////////
// CPersistStreamInitImpl

HRESULT	CTRiASArcExport::OnInitNew( ) {
	COM_TRY {
		CExtDataEngineImpl_t::OnInitNew();
// KK000816
		CExtDataEngineImpl_t::put_SeparateOutput(FALSE);
		CExtDataEngineImpl_t::put_SeparateDirs(FALSE);
	} COM_CATCH;
	return S_OK;
}
HRESULT CTRiASArcExport::LoadData( LPSTREAM pStm, DWORD dwVersion ) {
	COM_TRY {
		CExtDataEngineImpl_t::LoadData(pStm);
// KK000816
		CExtDataEngineImpl_t::put_SeparateOutput(FALSE);
		CExtDataEngineImpl_t::put_SeparateDirs(FALSE);
//		CExtDataEngineImpl_t::put_SeparateOutput(TRUE);
	} COM_CATCH;
	return S_OK;
}
HRESULT CTRiASArcExport::SaveData( LPSTREAM pStm, BOOL bClearDirty ) {
	COM_TRY {
		CExtDataEngineImpl_t::SaveData(pStm,bClearDirty);
	} COM_CATCH;
	return S_OK;
}
LONGLONG CTRiASArcExport::GetDataSize( ) {
	ULARGE_INTEGER	uliSize, uliSum;
	uliSize.QuadPart = 0;
	uliSum.QuadPart = 0;
	COM_TRY {
		uliSize.QuadPart = CExtDataEngineImpl_t::GetDataSize();
		uliSum.QuadPart += uliSize.QuadPart;
	} COM_CATCH;
	return uliSum.QuadPart;
}
