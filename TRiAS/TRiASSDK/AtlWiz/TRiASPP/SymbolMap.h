#ifndef __SymbolMap_h__
#define __SymbolMap_h__
#include "unknwn.h"
   interface DECLSPEC_UUID("C6D58201-1FA3-11D0-BF1E-0000E8D0D146")
   ISymbolMap : public IUnknown
   {
   public:
     virtual HRESULT STDMETHODCALLTYPE Set( 
         /* [in] */ LPCOLESTR strSymbol,
         /* [in] */ LPCOLESTR strValue) = 0;
  
     virtual HRESULT STDMETHODCALLTYPE Get( 
         /* [in] */ LPCOLESTR strSymbol,
         /* [retval][out] */ BSTR __RPC_FAR *pstrValue) = 0;
  
     virtual HRESULT STDMETHODCALLTYPE Clear( void) = 0;
  
     virtual HRESULT STDMETHODCALLTYPE SetStatus( 
         /* [in] */ const CLSID __RPC_FAR *pclsid,
         /* [in] */ BOOL bEnableOK) = 0;
  
   };
   EXTERN_C const IID IID_ISymbolMap;
#endif