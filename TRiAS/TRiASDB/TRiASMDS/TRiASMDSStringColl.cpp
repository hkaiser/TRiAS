// TRiASMDSStringColl.cpp : Implementation of CTRiASMDSStringColl

#include "stdafx.h"
#include "TRiASMDSImpl.h"
#include "TRiASMDSStringColl.h"

#if defined(_DEBUG)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTRiASMDSStringColl

HRESULT CTRiASMDSStringColl::FinalConstruct() 
{
	COM_TRY {
		m_enumOfStrings = new NEnumBSTR;
		m_enumOfStrings->Release();
	} COM_CATCH
	return S_OK;
}

STDMETHODIMP CTRiASMDSStringColl::_NewEnum(/*[out,retval]*/ IUnknown** ppIEnum) 
{
	CHECKINPOINTER(ppIEnum);
	COM_TRY {
	ObjectLock l(this);

		MakeEnumVARIANT(m_enumOfStrings, GetUnknown(), ppIEnum);
	} COM_CATCH
	return S_OK;
}

STDMETHODIMP CTRiASMDSStringColl::Add(BSTR strNewVal) 
{
	COM_TRY {
	ObjectLock l(this);

		m_enumOfStrings->AddItem(strNewVal);
	} COM_CATCH
	return S_OK;
}
