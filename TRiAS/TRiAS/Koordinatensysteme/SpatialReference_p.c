/* this ALWAYS GENERATED file contains the proxy stub code */


/* File created by MIDL compiler version 3.01.76 */
/* at Fri Apr 24 18:33:54 1998
 */
/* Compiler settings for SpatialReference.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )

#include "rpcproxy.h"
#include "SpatialReference.h"

#define TYPE_FORMAT_STRING_SIZE   593                               
#define PROC_FORMAT_STRING_SIZE   337                               

typedef struct _MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } MIDL_TYPE_FORMAT_STRING;

typedef struct _MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } MIDL_PROC_FORMAT_STRING;


extern const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString;
extern const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString;


/* Standard interface: __MIDL_itf_SpatialReference_0000, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}} */


/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: ISpatialReferenceInfo, ver. 0.0,
   GUID={0xbcca38a0,0xfe1c,0x11d0,{0xad,0x87,0x08,0x00,0x09,0xb6,0xf2,0x2b}} */


extern const MIDL_STUB_DESC Object_StubDesc;


#pragma code_seg(".orpc")

/* [propget] */ HRESULT STDMETHODCALLTYPE ISpatialReferenceInfo_get_Name_Proxy( 
    ISpatialReferenceInfo __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *name)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    MIDL_memset(
               name,
               0,
               sizeof( BSTR  ));
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      3);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[0] );
            
            NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR * __RPC_FAR *)&name,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[28],
                                      (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[0],
                         ( void __RPC_FAR * )name);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB ISpatialReferenceInfo_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    BSTR _M0;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    BSTR __RPC_FAR *name;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    name = 0;
    RpcTryFinally
        {
        name = &_M0;
        MIDL_memset(
               name,
               0,
               sizeof( BSTR  ));
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISpatialReferenceInfo *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_Name((ISpatialReferenceInfo *) ((CStdStubBuffer *)This)->pvServerObject,name);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U + 11U;
        NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR *)name,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[28] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                (unsigned char __RPC_FAR *)name,
                                (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[28] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)name,
                        &__MIDL_TypeFormatString.Format[0] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [propput] */ HRESULT STDMETHODCALLTYPE ISpatialReferenceInfo_put_Name_Proxy( 
    ISpatialReferenceInfo __RPC_FAR * This,
    /* [in] */ BSTR name)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      4);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 4U;
            NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR *)&name,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[42] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                    (unsigned char __RPC_FAR *)&name,
                                    (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[42] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[6] );
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB ISpatialReferenceInfo_put_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    void __RPC_FAR *_p_name;
    BSTR name;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    _p_name = &name;
    MIDL_memset(
               _p_name,
               0,
               sizeof( BSTR  ));
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[6] );
        
        NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&_p_name,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[42],
                                  (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISpatialReferenceInfo *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> put_Name((ISpatialReferenceInfo *) ((CStdStubBuffer *)This)->pvServerObject,name);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrUserMarshalFree( &_StubMsg,
                            (unsigned char __RPC_FAR *)&name,
                            &__MIDL_TypeFormatString.Format[42] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [propget] */ HRESULT STDMETHODCALLTYPE ISpatialReferenceInfo_get_Authority_Proxy( 
    ISpatialReferenceInfo __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *name)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    MIDL_memset(
               name,
               0,
               sizeof( BSTR  ));
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      5);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[12] );
            
            NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR * __RPC_FAR *)&name,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[56],
                                      (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[52],
                         ( void __RPC_FAR * )name);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB ISpatialReferenceInfo_get_Authority_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    BSTR _M1;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    BSTR __RPC_FAR *name;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    name = 0;
    RpcTryFinally
        {
        name = &_M1;
        MIDL_memset(
               name,
               0,
               sizeof( BSTR  ));
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISpatialReferenceInfo *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_Authority((ISpatialReferenceInfo *) ((CStdStubBuffer *)This)->pvServerObject,name);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U + 11U;
        NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR *)name,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[56] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                (unsigned char __RPC_FAR *)name,
                                (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[56] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)name,
                        &__MIDL_TypeFormatString.Format[52] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [propput] */ HRESULT STDMETHODCALLTYPE ISpatialReferenceInfo_put_Authority_Proxy( 
    ISpatialReferenceInfo __RPC_FAR * This,
    /* [in] */ BSTR name)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      6);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 4U;
            NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR *)&name,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[66] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                    (unsigned char __RPC_FAR *)&name,
                                    (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[66] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[18] );
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB ISpatialReferenceInfo_put_Authority_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    void __RPC_FAR *_p_name;
    BSTR name;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    _p_name = &name;
    MIDL_memset(
               _p_name,
               0,
               sizeof( BSTR  ));
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[18] );
        
        NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&_p_name,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[66],
                                  (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISpatialReferenceInfo *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> put_Authority((ISpatialReferenceInfo *) ((CStdStubBuffer *)This)->pvServerObject,name);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrUserMarshalFree( &_StubMsg,
                            (unsigned char __RPC_FAR *)&name,
                            &__MIDL_TypeFormatString.Format[66] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [propget] */ HRESULT STDMETHODCALLTYPE ISpatialReferenceInfo_get_Code_Proxy( 
    ISpatialReferenceInfo __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *code)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      7);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[24] );
            
            *code = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[76],
                         ( void __RPC_FAR * )code);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB ISpatialReferenceInfo_get_Code_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    long _M2;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    long __RPC_FAR *code;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    code = 0;
    RpcTryFinally
        {
        code = &_M2;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISpatialReferenceInfo *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_Code((ISpatialReferenceInfo *) ((CStdStubBuffer *)This)->pvServerObject,code);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U + 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( long __RPC_FAR * )_StubMsg.Buffer)++ = *code;
        
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [propput] */ HRESULT STDMETHODCALLTYPE ISpatialReferenceInfo_put_Code_Proxy( 
    ISpatialReferenceInfo __RPC_FAR * This,
    /* [in] */ long code)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      8);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 4U;
            NdrProxyGetBuffer(This, &_StubMsg);
            *(( long __RPC_FAR * )_StubMsg.Buffer)++ = code;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[30] );
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB ISpatialReferenceInfo_put_Code_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    long code;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[30] );
        
        code = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISpatialReferenceInfo *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> put_Code((ISpatialReferenceInfo *) ((CStdStubBuffer *)This)->pvServerObject,code);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [propget] */ HRESULT STDMETHODCALLTYPE ISpatialReferenceInfo_get_Alias_Proxy( 
    ISpatialReferenceInfo __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *alias)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    MIDL_memset(
               alias,
               0,
               sizeof( BSTR  ));
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      9);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[34] );
            
            NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR * __RPC_FAR *)&alias,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[84],
                                      (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[80],
                         ( void __RPC_FAR * )alias);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB ISpatialReferenceInfo_get_Alias_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    BSTR _M3;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    BSTR __RPC_FAR *alias;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    alias = 0;
    RpcTryFinally
        {
        alias = &_M3;
        MIDL_memset(
               alias,
               0,
               sizeof( BSTR  ));
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISpatialReferenceInfo *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_Alias((ISpatialReferenceInfo *) ((CStdStubBuffer *)This)->pvServerObject,alias);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U + 11U;
        NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR *)alias,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[84] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                (unsigned char __RPC_FAR *)alias,
                                (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[84] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)alias,
                        &__MIDL_TypeFormatString.Format[80] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [propput] */ HRESULT STDMETHODCALLTYPE ISpatialReferenceInfo_put_Alias_Proxy( 
    ISpatialReferenceInfo __RPC_FAR * This,
    /* [in] */ BSTR alias)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      10);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 4U;
            NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR *)&alias,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[94] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                    (unsigned char __RPC_FAR *)&alias,
                                    (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[94] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[40] );
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB ISpatialReferenceInfo_put_Alias_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    void __RPC_FAR *_p_alias;
    BSTR alias;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    _p_alias = &alias;
    MIDL_memset(
               _p_alias,
               0,
               sizeof( BSTR  ));
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[40] );
        
        NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&_p_alias,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[94],
                                  (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISpatialReferenceInfo *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> put_Alias((ISpatialReferenceInfo *) ((CStdStubBuffer *)This)->pvServerObject,alias);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrUserMarshalFree( &_StubMsg,
                            (unsigned char __RPC_FAR *)&alias,
                            &__MIDL_TypeFormatString.Format[94] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [propget] */ HRESULT STDMETHODCALLTYPE ISpatialReferenceInfo_get_Abbreviation_Proxy( 
    ISpatialReferenceInfo __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *abbrev)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    MIDL_memset(
               abbrev,
               0,
               sizeof( BSTR  ));
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      11);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[46] );
            
            NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR * __RPC_FAR *)&abbrev,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[108],
                                      (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[104],
                         ( void __RPC_FAR * )abbrev);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB ISpatialReferenceInfo_get_Abbreviation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    BSTR _M4;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    BSTR __RPC_FAR *abbrev;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    abbrev = 0;
    RpcTryFinally
        {
        abbrev = &_M4;
        MIDL_memset(
               abbrev,
               0,
               sizeof( BSTR  ));
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISpatialReferenceInfo *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_Abbreviation((ISpatialReferenceInfo *) ((CStdStubBuffer *)This)->pvServerObject,abbrev);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U + 11U;
        NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR *)abbrev,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[108] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                (unsigned char __RPC_FAR *)abbrev,
                                (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[108] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)abbrev,
                        &__MIDL_TypeFormatString.Format[104] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [propput] */ HRESULT STDMETHODCALLTYPE ISpatialReferenceInfo_put_Abbreviation_Proxy( 
    ISpatialReferenceInfo __RPC_FAR * This,
    /* [in] */ BSTR abbrev)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      12);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 4U;
            NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR *)&abbrev,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[118] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                    (unsigned char __RPC_FAR *)&abbrev,
                                    (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[118] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[52] );
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB ISpatialReferenceInfo_put_Abbreviation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    void __RPC_FAR *_p_abbrev;
    BSTR abbrev;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    _p_abbrev = &abbrev;
    MIDL_memset(
               _p_abbrev,
               0,
               sizeof( BSTR  ));
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[52] );
        
        NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&_p_abbrev,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[118],
                                  (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISpatialReferenceInfo *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> put_Abbreviation((ISpatialReferenceInfo *) ((CStdStubBuffer *)This)->pvServerObject,abbrev);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrUserMarshalFree( &_StubMsg,
                            (unsigned char __RPC_FAR *)&abbrev,
                            &__MIDL_TypeFormatString.Format[118] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [propget] */ HRESULT STDMETHODCALLTYPE ISpatialReferenceInfo_get_Remarks_Proxy( 
    ISpatialReferenceInfo __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *remarks)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    MIDL_memset(
               remarks,
               0,
               sizeof( BSTR  ));
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      13);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[58] );
            
            NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR * __RPC_FAR *)&remarks,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[132],
                                      (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[128],
                         ( void __RPC_FAR * )remarks);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB ISpatialReferenceInfo_get_Remarks_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    BSTR _M5;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    BSTR __RPC_FAR *remarks;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    remarks = 0;
    RpcTryFinally
        {
        remarks = &_M5;
        MIDL_memset(
               remarks,
               0,
               sizeof( BSTR  ));
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISpatialReferenceInfo *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_Remarks((ISpatialReferenceInfo *) ((CStdStubBuffer *)This)->pvServerObject,remarks);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U + 11U;
        NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR *)remarks,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[132] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                (unsigned char __RPC_FAR *)remarks,
                                (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[132] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)remarks,
                        &__MIDL_TypeFormatString.Format[128] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [propput] */ HRESULT STDMETHODCALLTYPE ISpatialReferenceInfo_put_Remarks_Proxy( 
    ISpatialReferenceInfo __RPC_FAR * This,
    /* [in] */ BSTR remarks)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      14);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 4U;
            NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR *)&remarks,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[142] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                    (unsigned char __RPC_FAR *)&remarks,
                                    (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[142] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[64] );
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB ISpatialReferenceInfo_put_Remarks_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    void __RPC_FAR *_p_remarks;
    BSTR remarks;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    _p_remarks = &remarks;
    MIDL_memset(
               _p_remarks,
               0,
               sizeof( BSTR  ));
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[64] );
        
        NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&_p_remarks,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[142],
                                  (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISpatialReferenceInfo *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> put_Remarks((ISpatialReferenceInfo *) ((CStdStubBuffer *)This)->pvServerObject,remarks);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrUserMarshalFree( &_StubMsg,
                            (unsigned char __RPC_FAR *)&remarks,
                            &__MIDL_TypeFormatString.Format[142] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [propget] */ HRESULT STDMETHODCALLTYPE ISpatialReferenceInfo_get_WellKnownText_Proxy( 
    ISpatialReferenceInfo __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *wkt)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    MIDL_memset(
               wkt,
               0,
               sizeof( BSTR  ));
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      15);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[70] );
            
            NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR * __RPC_FAR *)&wkt,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[156],
                                      (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[152],
                         ( void __RPC_FAR * )wkt);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB ISpatialReferenceInfo_get_WellKnownText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    BSTR _M6;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    BSTR __RPC_FAR *wkt;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    wkt = 0;
    RpcTryFinally
        {
        wkt = &_M6;
        MIDL_memset(
               wkt,
               0,
               sizeof( BSTR  ));
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISpatialReferenceInfo *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_WellKnownText((ISpatialReferenceInfo *) ((CStdStubBuffer *)This)->pvServerObject,wkt);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U + 11U;
        NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR *)wkt,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[156] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                (unsigned char __RPC_FAR *)wkt,
                                (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[156] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)wkt,
                        &__MIDL_TypeFormatString.Format[152] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

const CINTERFACE_PROXY_VTABLE(16) _ISpatialReferenceInfoProxyVtbl = 
{
    &IID_ISpatialReferenceInfo,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    ISpatialReferenceInfo_get_Name_Proxy ,
    ISpatialReferenceInfo_put_Name_Proxy ,
    ISpatialReferenceInfo_get_Authority_Proxy ,
    ISpatialReferenceInfo_put_Authority_Proxy ,
    ISpatialReferenceInfo_get_Code_Proxy ,
    ISpatialReferenceInfo_put_Code_Proxy ,
    ISpatialReferenceInfo_get_Alias_Proxy ,
    ISpatialReferenceInfo_put_Alias_Proxy ,
    ISpatialReferenceInfo_get_Abbreviation_Proxy ,
    ISpatialReferenceInfo_put_Abbreviation_Proxy ,
    ISpatialReferenceInfo_get_Remarks_Proxy ,
    ISpatialReferenceInfo_put_Remarks_Proxy ,
    ISpatialReferenceInfo_get_WellKnownText_Proxy
};


static const PRPC_STUB_FUNCTION ISpatialReferenceInfo_table[] =
{
    ISpatialReferenceInfo_get_Name_Stub,
    ISpatialReferenceInfo_put_Name_Stub,
    ISpatialReferenceInfo_get_Authority_Stub,
    ISpatialReferenceInfo_put_Authority_Stub,
    ISpatialReferenceInfo_get_Code_Stub,
    ISpatialReferenceInfo_put_Code_Stub,
    ISpatialReferenceInfo_get_Alias_Stub,
    ISpatialReferenceInfo_put_Alias_Stub,
    ISpatialReferenceInfo_get_Abbreviation_Stub,
    ISpatialReferenceInfo_put_Abbreviation_Stub,
    ISpatialReferenceInfo_get_Remarks_Stub,
    ISpatialReferenceInfo_put_Remarks_Stub,
    ISpatialReferenceInfo_get_WellKnownText_Stub
};

const CInterfaceStubVtbl _ISpatialReferenceInfoStubVtbl =
{
    &IID_ISpatialReferenceInfo,
    0,
    16,
    &ISpatialReferenceInfo_table[-3],
    CStdStubBuffer_METHODS
};


/* Object interface: IUnit, ver. 0.0,
   GUID={0x221733b0,0xfe1d,0x11d0,{0xad,0x87,0x08,0x00,0x09,0xb6,0xf2,0x2b}} */


extern const MIDL_STUB_DESC Object_StubDesc;


#pragma code_seg(".orpc")
const CINTERFACE_PROXY_VTABLE(16) _IUnitProxyVtbl = 
{
    &IID_IUnit,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    ISpatialReferenceInfo_get_Name_Proxy ,
    ISpatialReferenceInfo_put_Name_Proxy ,
    ISpatialReferenceInfo_get_Authority_Proxy ,
    ISpatialReferenceInfo_put_Authority_Proxy ,
    ISpatialReferenceInfo_get_Code_Proxy ,
    ISpatialReferenceInfo_put_Code_Proxy ,
    ISpatialReferenceInfo_get_Alias_Proxy ,
    ISpatialReferenceInfo_put_Alias_Proxy ,
    ISpatialReferenceInfo_get_Abbreviation_Proxy ,
    ISpatialReferenceInfo_put_Abbreviation_Proxy ,
    ISpatialReferenceInfo_get_Remarks_Proxy ,
    ISpatialReferenceInfo_put_Remarks_Proxy ,
    ISpatialReferenceInfo_get_WellKnownText_Proxy
};


static const PRPC_STUB_FUNCTION IUnit_table[] =
{
    ISpatialReferenceInfo_get_Name_Stub,
    ISpatialReferenceInfo_put_Name_Stub,
    ISpatialReferenceInfo_get_Authority_Stub,
    ISpatialReferenceInfo_put_Authority_Stub,
    ISpatialReferenceInfo_get_Code_Stub,
    ISpatialReferenceInfo_put_Code_Stub,
    ISpatialReferenceInfo_get_Alias_Stub,
    ISpatialReferenceInfo_put_Alias_Stub,
    ISpatialReferenceInfo_get_Abbreviation_Stub,
    ISpatialReferenceInfo_put_Abbreviation_Stub,
    ISpatialReferenceInfo_get_Remarks_Stub,
    ISpatialReferenceInfo_put_Remarks_Stub,
    ISpatialReferenceInfo_get_WellKnownText_Stub
};

const CInterfaceStubVtbl _IUnitStubVtbl =
{
    &IID_IUnit,
    0,
    16,
    &IUnit_table[-3],
    CStdStubBuffer_METHODS
};


/* Object interface: IAngularUnit, ver. 0.0,
   GUID={0x4febc550,0xfe1d,0x11d0,{0xad,0x87,0x08,0x00,0x09,0xb6,0xf2,0x2b}} */


extern const MIDL_STUB_DESC Object_StubDesc;


#pragma code_seg(".orpc")

/* [propget] */ HRESULT STDMETHODCALLTYPE IAngularUnit_get_RadiansPerUnit_Proxy( 
    IAngularUnit __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *factor)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      16);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[76] );
            
            *factor = *(( double __RPC_FAR * )_StubMsg.Buffer)++;
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[166],
                         ( void __RPC_FAR * )factor);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IAngularUnit_get_RadiansPerUnit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    double _M7;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    double __RPC_FAR *factor;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    factor = 0;
    RpcTryFinally
        {
        factor = &_M7;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IAngularUnit *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_RadiansPerUnit((IAngularUnit *) ((CStdStubBuffer *)This)->pvServerObject,factor);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8U + 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( double __RPC_FAR * )_StubMsg.Buffer)++ = *factor;
        
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [propput] */ HRESULT STDMETHODCALLTYPE IAngularUnit_put_RadiansPerUnit_Proxy( 
    IAngularUnit __RPC_FAR * This,
    /* [in] */ double factor)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      17);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 8U;
            NdrProxyGetBuffer(This, &_StubMsg);
            *(( double __RPC_FAR * )_StubMsg.Buffer)++ = factor;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[82] );
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IAngularUnit_put_RadiansPerUnit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    double factor;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[82] );
        
        factor = *(( double __RPC_FAR * )_StubMsg.Buffer)++;
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IAngularUnit *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> put_RadiansPerUnit((IAngularUnit *) ((CStdStubBuffer *)This)->pvServerObject,factor);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

const CINTERFACE_PROXY_VTABLE(18) _IAngularUnitProxyVtbl = 
{
    &IID_IAngularUnit,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    ISpatialReferenceInfo_get_Name_Proxy ,
    ISpatialReferenceInfo_put_Name_Proxy ,
    ISpatialReferenceInfo_get_Authority_Proxy ,
    ISpatialReferenceInfo_put_Authority_Proxy ,
    ISpatialReferenceInfo_get_Code_Proxy ,
    ISpatialReferenceInfo_put_Code_Proxy ,
    ISpatialReferenceInfo_get_Alias_Proxy ,
    ISpatialReferenceInfo_put_Alias_Proxy ,
    ISpatialReferenceInfo_get_Abbreviation_Proxy ,
    ISpatialReferenceInfo_put_Abbreviation_Proxy ,
    ISpatialReferenceInfo_get_Remarks_Proxy ,
    ISpatialReferenceInfo_put_Remarks_Proxy ,
    ISpatialReferenceInfo_get_WellKnownText_Proxy ,
    IAngularUnit_get_RadiansPerUnit_Proxy ,
    IAngularUnit_put_RadiansPerUnit_Proxy
};


static const PRPC_STUB_FUNCTION IAngularUnit_table[] =
{
    ISpatialReferenceInfo_get_Name_Stub,
    ISpatialReferenceInfo_put_Name_Stub,
    ISpatialReferenceInfo_get_Authority_Stub,
    ISpatialReferenceInfo_put_Authority_Stub,
    ISpatialReferenceInfo_get_Code_Stub,
    ISpatialReferenceInfo_put_Code_Stub,
    ISpatialReferenceInfo_get_Alias_Stub,
    ISpatialReferenceInfo_put_Alias_Stub,
    ISpatialReferenceInfo_get_Abbreviation_Stub,
    ISpatialReferenceInfo_put_Abbreviation_Stub,
    ISpatialReferenceInfo_get_Remarks_Stub,
    ISpatialReferenceInfo_put_Remarks_Stub,
    ISpatialReferenceInfo_get_WellKnownText_Stub,
    IAngularUnit_get_RadiansPerUnit_Stub,
    IAngularUnit_put_RadiansPerUnit_Stub
};

const CInterfaceStubVtbl _IAngularUnitStubVtbl =
{
    &IID_IAngularUnit,
    0,
    18,
    &IAngularUnit_table[-3],
    CStdStubBuffer_METHODS
};


/* Object interface: ILinearUnit, ver. 0.0,
   GUID={0x80855df0,0xfe1d,0x11d0,{0xad,0x87,0x08,0x00,0x09,0xb6,0xf2,0x2b}} */


extern const MIDL_STUB_DESC Object_StubDesc;


#pragma code_seg(".orpc")

/* [propget] */ HRESULT STDMETHODCALLTYPE ILinearUnit_get_MetersPerUnit_Proxy( 
    ILinearUnit __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *factor)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      16);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[76] );
            
            *factor = *(( double __RPC_FAR * )_StubMsg.Buffer)++;
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[166],
                         ( void __RPC_FAR * )factor);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB ILinearUnit_get_MetersPerUnit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    double _M8;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    double __RPC_FAR *factor;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    factor = 0;
    RpcTryFinally
        {
        factor = &_M8;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ILinearUnit *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_MetersPerUnit((ILinearUnit *) ((CStdStubBuffer *)This)->pvServerObject,factor);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8U + 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( double __RPC_FAR * )_StubMsg.Buffer)++ = *factor;
        
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [propput] */ HRESULT STDMETHODCALLTYPE ILinearUnit_put_MetersPerUnit_Proxy( 
    ILinearUnit __RPC_FAR * This,
    /* [in] */ double factor)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      17);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 8U;
            NdrProxyGetBuffer(This, &_StubMsg);
            *(( double __RPC_FAR * )_StubMsg.Buffer)++ = factor;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[82] );
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB ILinearUnit_put_MetersPerUnit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    double factor;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[82] );
        
        factor = *(( double __RPC_FAR * )_StubMsg.Buffer)++;
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ILinearUnit *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> put_MetersPerUnit((ILinearUnit *) ((CStdStubBuffer *)This)->pvServerObject,factor);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

const CINTERFACE_PROXY_VTABLE(18) _ILinearUnitProxyVtbl = 
{
    &IID_ILinearUnit,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    ISpatialReferenceInfo_get_Name_Proxy ,
    ISpatialReferenceInfo_put_Name_Proxy ,
    ISpatialReferenceInfo_get_Authority_Proxy ,
    ISpatialReferenceInfo_put_Authority_Proxy ,
    ISpatialReferenceInfo_get_Code_Proxy ,
    ISpatialReferenceInfo_put_Code_Proxy ,
    ISpatialReferenceInfo_get_Alias_Proxy ,
    ISpatialReferenceInfo_put_Alias_Proxy ,
    ISpatialReferenceInfo_get_Abbreviation_Proxy ,
    ISpatialReferenceInfo_put_Abbreviation_Proxy ,
    ISpatialReferenceInfo_get_Remarks_Proxy ,
    ISpatialReferenceInfo_put_Remarks_Proxy ,
    ISpatialReferenceInfo_get_WellKnownText_Proxy ,
    ILinearUnit_get_MetersPerUnit_Proxy ,
    ILinearUnit_put_MetersPerUnit_Proxy
};


static const PRPC_STUB_FUNCTION ILinearUnit_table[] =
{
    ISpatialReferenceInfo_get_Name_Stub,
    ISpatialReferenceInfo_put_Name_Stub,
    ISpatialReferenceInfo_get_Authority_Stub,
    ISpatialReferenceInfo_put_Authority_Stub,
    ISpatialReferenceInfo_get_Code_Stub,
    ISpatialReferenceInfo_put_Code_Stub,
    ISpatialReferenceInfo_get_Alias_Stub,
    ISpatialReferenceInfo_put_Alias_Stub,
    ISpatialReferenceInfo_get_Abbreviation_Stub,
    ISpatialReferenceInfo_put_Abbreviation_Stub,
    ISpatialReferenceInfo_get_Remarks_Stub,
    ISpatialReferenceInfo_put_Remarks_Stub,
    ISpatialReferenceInfo_get_WellKnownText_Stub,
    ILinearUnit_get_MetersPerUnit_Stub,
    ILinearUnit_put_MetersPerUnit_Stub
};

const CInterfaceStubVtbl _ILinearUnitStubVtbl =
{
    &IID_ILinearUnit,
    0,
    18,
    &ILinearUnit_table[-3],
    CStdStubBuffer_METHODS
};


/* Object interface: IEllipsoid, ver. 0.0,
   GUID={0xce7266c0,0xfe1d,0x11d0,{0xad,0x87,0x08,0x00,0x09,0xb6,0xf2,0x2b}} */


extern const MIDL_STUB_DESC Object_StubDesc;


#pragma code_seg(".orpc")

/* [propget] */ HRESULT STDMETHODCALLTYPE IEllipsoid_get_SemiMajorAxis_Proxy( 
    IEllipsoid __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *axis)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      16);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[76] );
            
            *axis = *(( double __RPC_FAR * )_StubMsg.Buffer)++;
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[166],
                         ( void __RPC_FAR * )axis);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IEllipsoid_get_SemiMajorAxis_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    double _M9;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    double __RPC_FAR *axis;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    axis = 0;
    RpcTryFinally
        {
        axis = &_M9;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IEllipsoid *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_SemiMajorAxis((IEllipsoid *) ((CStdStubBuffer *)This)->pvServerObject,axis);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8U + 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( double __RPC_FAR * )_StubMsg.Buffer)++ = *axis;
        
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [propput] */ HRESULT STDMETHODCALLTYPE IEllipsoid_put_SemiMajorAxis_Proxy( 
    IEllipsoid __RPC_FAR * This,
    /* [in] */ double axis)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      17);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 8U;
            NdrProxyGetBuffer(This, &_StubMsg);
            *(( double __RPC_FAR * )_StubMsg.Buffer)++ = axis;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[82] );
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IEllipsoid_put_SemiMajorAxis_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    double axis;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[82] );
        
        axis = *(( double __RPC_FAR * )_StubMsg.Buffer)++;
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IEllipsoid *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> put_SemiMajorAxis((IEllipsoid *) ((CStdStubBuffer *)This)->pvServerObject,axis);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [propget] */ HRESULT STDMETHODCALLTYPE IEllipsoid_get_SemiMinorAxis_Proxy( 
    IEllipsoid __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *axis)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      18);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[76] );
            
            *axis = *(( double __RPC_FAR * )_StubMsg.Buffer)++;
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[166],
                         ( void __RPC_FAR * )axis);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IEllipsoid_get_SemiMinorAxis_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    double _M10;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    double __RPC_FAR *axis;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    axis = 0;
    RpcTryFinally
        {
        axis = &_M10;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IEllipsoid *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_SemiMinorAxis((IEllipsoid *) ((CStdStubBuffer *)This)->pvServerObject,axis);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8U + 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( double __RPC_FAR * )_StubMsg.Buffer)++ = *axis;
        
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [propput] */ HRESULT STDMETHODCALLTYPE IEllipsoid_put_SemiMinorAxis_Proxy( 
    IEllipsoid __RPC_FAR * This,
    /* [in] */ double axis)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      19);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 8U;
            NdrProxyGetBuffer(This, &_StubMsg);
            *(( double __RPC_FAR * )_StubMsg.Buffer)++ = axis;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[82] );
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IEllipsoid_put_SemiMinorAxis_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    double axis;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[82] );
        
        axis = *(( double __RPC_FAR * )_StubMsg.Buffer)++;
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IEllipsoid *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> put_SemiMinorAxis((IEllipsoid *) ((CStdStubBuffer *)This)->pvServerObject,axis);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [propget] */ HRESULT STDMETHODCALLTYPE IEllipsoid_get_InverseFlattening_Proxy( 
    IEllipsoid __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *invFlat)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      20);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[76] );
            
            *invFlat = *(( double __RPC_FAR * )_StubMsg.Buffer)++;
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[166],
                         ( void __RPC_FAR * )invFlat);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IEllipsoid_get_InverseFlattening_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    double _M11;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    double __RPC_FAR *invFlat;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    invFlat = 0;
    RpcTryFinally
        {
        invFlat = &_M11;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IEllipsoid *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_InverseFlattening((IEllipsoid *) ((CStdStubBuffer *)This)->pvServerObject,invFlat);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8U + 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( double __RPC_FAR * )_StubMsg.Buffer)++ = *invFlat;
        
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [propput] */ HRESULT STDMETHODCALLTYPE IEllipsoid_put_InverseFlattening_Proxy( 
    IEllipsoid __RPC_FAR * This,
    /* [in] */ double invFlat)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      21);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 8U;
            NdrProxyGetBuffer(This, &_StubMsg);
            *(( double __RPC_FAR * )_StubMsg.Buffer)++ = invFlat;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[82] );
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IEllipsoid_put_InverseFlattening_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    double invFlat;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[82] );
        
        invFlat = *(( double __RPC_FAR * )_StubMsg.Buffer)++;
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IEllipsoid *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> put_InverseFlattening((IEllipsoid *) ((CStdStubBuffer *)This)->pvServerObject,invFlat);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [propget] */ HRESULT STDMETHODCALLTYPE IEllipsoid_get_AxisUnit_Proxy( 
    IEllipsoid __RPC_FAR * This,
    /* [retval][out] */ ILinearUnit __RPC_FAR *__RPC_FAR *unit)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    *unit = 0;
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      22);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[86] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&unit,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[170],
                                  (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[170],
                         ( void __RPC_FAR * )unit);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IEllipsoid_get_AxisUnit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    ILinearUnit __RPC_FAR *_M12;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    ILinearUnit __RPC_FAR *__RPC_FAR *unit;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    unit = 0;
    RpcTryFinally
        {
        unit = &_M12;
        _M12 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IEllipsoid *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_AxisUnit((IEllipsoid *) ((CStdStubBuffer *)This)->pvServerObject,unit);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 0U + 4U;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR *)unit,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[170] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char __RPC_FAR *)unit,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[170] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)unit,
                        &__MIDL_TypeFormatString.Format[170] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [propput] */ HRESULT STDMETHODCALLTYPE IEllipsoid_put_AxisUnit_Proxy( 
    IEllipsoid __RPC_FAR * This,
    /* [in] */ ILinearUnit __RPC_FAR *unit)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      23);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrInterfacePointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                           (unsigned char __RPC_FAR *)unit,
                                           (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[174] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrInterfacePointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                         (unsigned char __RPC_FAR *)unit,
                                         (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[174] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[92] );
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IEllipsoid_put_AxisUnit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    ILinearUnit __RPC_FAR *unit;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    unit = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[92] );
        
        NdrInterfacePointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&unit,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[174],
                                       (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IEllipsoid *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> put_AxisUnit((IEllipsoid *) ((CStdStubBuffer *)This)->pvServerObject,unit);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrInterfacePointerFree( &_StubMsg,
                                 (unsigned char __RPC_FAR *)unit,
                                 &__MIDL_TypeFormatString.Format[174] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

const CINTERFACE_PROXY_VTABLE(24) _IEllipsoidProxyVtbl = 
{
    &IID_IEllipsoid,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    ISpatialReferenceInfo_get_Name_Proxy ,
    ISpatialReferenceInfo_put_Name_Proxy ,
    ISpatialReferenceInfo_get_Authority_Proxy ,
    ISpatialReferenceInfo_put_Authority_Proxy ,
    ISpatialReferenceInfo_get_Code_Proxy ,
    ISpatialReferenceInfo_put_Code_Proxy ,
    ISpatialReferenceInfo_get_Alias_Proxy ,
    ISpatialReferenceInfo_put_Alias_Proxy ,
    ISpatialReferenceInfo_get_Abbreviation_Proxy ,
    ISpatialReferenceInfo_put_Abbreviation_Proxy ,
    ISpatialReferenceInfo_get_Remarks_Proxy ,
    ISpatialReferenceInfo_put_Remarks_Proxy ,
    ISpatialReferenceInfo_get_WellKnownText_Proxy ,
    IEllipsoid_get_SemiMajorAxis_Proxy ,
    IEllipsoid_put_SemiMajorAxis_Proxy ,
    IEllipsoid_get_SemiMinorAxis_Proxy ,
    IEllipsoid_put_SemiMinorAxis_Proxy ,
    IEllipsoid_get_InverseFlattening_Proxy ,
    IEllipsoid_put_InverseFlattening_Proxy ,
    IEllipsoid_get_AxisUnit_Proxy ,
    IEllipsoid_put_AxisUnit_Proxy
};


static const PRPC_STUB_FUNCTION IEllipsoid_table[] =
{
    ISpatialReferenceInfo_get_Name_Stub,
    ISpatialReferenceInfo_put_Name_Stub,
    ISpatialReferenceInfo_get_Authority_Stub,
    ISpatialReferenceInfo_put_Authority_Stub,
    ISpatialReferenceInfo_get_Code_Stub,
    ISpatialReferenceInfo_put_Code_Stub,
    ISpatialReferenceInfo_get_Alias_Stub,
    ISpatialReferenceInfo_put_Alias_Stub,
    ISpatialReferenceInfo_get_Abbreviation_Stub,
    ISpatialReferenceInfo_put_Abbreviation_Stub,
    ISpatialReferenceInfo_get_Remarks_Stub,
    ISpatialReferenceInfo_put_Remarks_Stub,
    ISpatialReferenceInfo_get_WellKnownText_Stub,
    IEllipsoid_get_SemiMajorAxis_Stub,
    IEllipsoid_put_SemiMajorAxis_Stub,
    IEllipsoid_get_SemiMinorAxis_Stub,
    IEllipsoid_put_SemiMinorAxis_Stub,
    IEllipsoid_get_InverseFlattening_Stub,
    IEllipsoid_put_InverseFlattening_Stub,
    IEllipsoid_get_AxisUnit_Stub,
    IEllipsoid_put_AxisUnit_Stub
};

const CInterfaceStubVtbl _IEllipsoidStubVtbl =
{
    &IID_IEllipsoid,
    0,
    24,
    &IEllipsoid_table[-3],
    CStdStubBuffer_METHODS
};


/* Object interface: IHorizontalDatum, ver. 0.0,
   GUID={0xf699c510,0xfe1d,0x11d0,{0xad,0x87,0x08,0x00,0x09,0xb6,0xf2,0x2b}} */


extern const MIDL_STUB_DESC Object_StubDesc;


#pragma code_seg(".orpc")

/* [propget] */ HRESULT STDMETHODCALLTYPE IHorizontalDatum_get_Ellipsoid_Proxy( 
    IHorizontalDatum __RPC_FAR * This,
    /* [retval][out] */ IEllipsoid __RPC_FAR *__RPC_FAR *ellipsoid)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    *ellipsoid = 0;
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      16);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[98] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&ellipsoid,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[192],
                                  (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[192],
                         ( void __RPC_FAR * )ellipsoid);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IHorizontalDatum_get_Ellipsoid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    IEllipsoid __RPC_FAR *_M13;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    IEllipsoid __RPC_FAR *__RPC_FAR *ellipsoid;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ellipsoid = 0;
    RpcTryFinally
        {
        ellipsoid = &_M13;
        _M13 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IHorizontalDatum *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_Ellipsoid((IHorizontalDatum *) ((CStdStubBuffer *)This)->pvServerObject,ellipsoid);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 0U + 4U;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR *)ellipsoid,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[192] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char __RPC_FAR *)ellipsoid,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[192] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)ellipsoid,
                        &__MIDL_TypeFormatString.Format[192] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [propput] */ HRESULT STDMETHODCALLTYPE IHorizontalDatum_put_Ellipsoid_Proxy( 
    IHorizontalDatum __RPC_FAR * This,
    /* [in] */ IEllipsoid __RPC_FAR *ellipsoid)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      17);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrInterfacePointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                           (unsigned char __RPC_FAR *)ellipsoid,
                                           (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[196] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrInterfacePointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                         (unsigned char __RPC_FAR *)ellipsoid,
                                         (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[196] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[104] );
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IHorizontalDatum_put_Ellipsoid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    IEllipsoid __RPC_FAR *ellipsoid;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ellipsoid = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[104] );
        
        NdrInterfacePointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&ellipsoid,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[196],
                                       (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IHorizontalDatum *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> put_Ellipsoid((IHorizontalDatum *) ((CStdStubBuffer *)This)->pvServerObject,ellipsoid);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrInterfacePointerFree( &_StubMsg,
                                 (unsigned char __RPC_FAR *)ellipsoid,
                                 &__MIDL_TypeFormatString.Format[196] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

const CINTERFACE_PROXY_VTABLE(18) _IHorizontalDatumProxyVtbl = 
{
    &IID_IHorizontalDatum,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    ISpatialReferenceInfo_get_Name_Proxy ,
    ISpatialReferenceInfo_put_Name_Proxy ,
    ISpatialReferenceInfo_get_Authority_Proxy ,
    ISpatialReferenceInfo_put_Authority_Proxy ,
    ISpatialReferenceInfo_get_Code_Proxy ,
    ISpatialReferenceInfo_put_Code_Proxy ,
    ISpatialReferenceInfo_get_Alias_Proxy ,
    ISpatialReferenceInfo_put_Alias_Proxy ,
    ISpatialReferenceInfo_get_Abbreviation_Proxy ,
    ISpatialReferenceInfo_put_Abbreviation_Proxy ,
    ISpatialReferenceInfo_get_Remarks_Proxy ,
    ISpatialReferenceInfo_put_Remarks_Proxy ,
    ISpatialReferenceInfo_get_WellKnownText_Proxy ,
    IHorizontalDatum_get_Ellipsoid_Proxy ,
    IHorizontalDatum_put_Ellipsoid_Proxy
};


static const PRPC_STUB_FUNCTION IHorizontalDatum_table[] =
{
    ISpatialReferenceInfo_get_Name_Stub,
    ISpatialReferenceInfo_put_Name_Stub,
    ISpatialReferenceInfo_get_Authority_Stub,
    ISpatialReferenceInfo_put_Authority_Stub,
    ISpatialReferenceInfo_get_Code_Stub,
    ISpatialReferenceInfo_put_Code_Stub,
    ISpatialReferenceInfo_get_Alias_Stub,
    ISpatialReferenceInfo_put_Alias_Stub,
    ISpatialReferenceInfo_get_Abbreviation_Stub,
    ISpatialReferenceInfo_put_Abbreviation_Stub,
    ISpatialReferenceInfo_get_Remarks_Stub,
    ISpatialReferenceInfo_put_Remarks_Stub,
    ISpatialReferenceInfo_get_WellKnownText_Stub,
    IHorizontalDatum_get_Ellipsoid_Stub,
    IHorizontalDatum_put_Ellipsoid_Stub
};

const CInterfaceStubVtbl _IHorizontalDatumStubVtbl =
{
    &IID_IHorizontalDatum,
    0,
    18,
    &IHorizontalDatum_table[-3],
    CStdStubBuffer_METHODS
};


/* Object interface: IPrimeMeridian, ver. 0.0,
   GUID={0x15129940,0xfe1e,0x11d0,{0xad,0x87,0x08,0x00,0x09,0xb6,0xf2,0x2b}} */


extern const MIDL_STUB_DESC Object_StubDesc;


#pragma code_seg(".orpc")

/* [propget] */ HRESULT STDMETHODCALLTYPE IPrimeMeridian_get_Longitude_Proxy( 
    IPrimeMeridian __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *longitude)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      16);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[76] );
            
            *longitude = *(( double __RPC_FAR * )_StubMsg.Buffer)++;
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[166],
                         ( void __RPC_FAR * )longitude);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IPrimeMeridian_get_Longitude_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    double _M14;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    double __RPC_FAR *longitude;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    longitude = 0;
    RpcTryFinally
        {
        longitude = &_M14;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IPrimeMeridian *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_Longitude((IPrimeMeridian *) ((CStdStubBuffer *)This)->pvServerObject,longitude);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8U + 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( double __RPC_FAR * )_StubMsg.Buffer)++ = *longitude;
        
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [propput] */ HRESULT STDMETHODCALLTYPE IPrimeMeridian_put_Longitude_Proxy( 
    IPrimeMeridian __RPC_FAR * This,
    /* [in] */ double longitude)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      17);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 8U;
            NdrProxyGetBuffer(This, &_StubMsg);
            *(( double __RPC_FAR * )_StubMsg.Buffer)++ = longitude;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[82] );
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IPrimeMeridian_put_Longitude_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    double longitude;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[82] );
        
        longitude = *(( double __RPC_FAR * )_StubMsg.Buffer)++;
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IPrimeMeridian *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> put_Longitude((IPrimeMeridian *) ((CStdStubBuffer *)This)->pvServerObject,longitude);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [propget] */ HRESULT STDMETHODCALLTYPE IPrimeMeridian_get_AngularUnit_Proxy( 
    IPrimeMeridian __RPC_FAR * This,
    /* [retval][out] */ IAngularUnit __RPC_FAR *__RPC_FAR *unit)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    *unit = 0;
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      18);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[110] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&unit,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[214],
                                  (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[214],
                         ( void __RPC_FAR * )unit);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IPrimeMeridian_get_AngularUnit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    IAngularUnit __RPC_FAR *_M15;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    IAngularUnit __RPC_FAR *__RPC_FAR *unit;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    unit = 0;
    RpcTryFinally
        {
        unit = &_M15;
        _M15 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IPrimeMeridian *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_AngularUnit((IPrimeMeridian *) ((CStdStubBuffer *)This)->pvServerObject,unit);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 0U + 4U;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR *)unit,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[214] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char __RPC_FAR *)unit,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[214] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)unit,
                        &__MIDL_TypeFormatString.Format[214] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [propput] */ HRESULT STDMETHODCALLTYPE IPrimeMeridian_put_AngularUnit_Proxy( 
    IPrimeMeridian __RPC_FAR * This,
    /* [in] */ IAngularUnit __RPC_FAR *unit)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      19);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrInterfacePointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                           (unsigned char __RPC_FAR *)unit,
                                           (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[218] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrInterfacePointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                         (unsigned char __RPC_FAR *)unit,
                                         (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[218] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[116] );
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IPrimeMeridian_put_AngularUnit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    IAngularUnit __RPC_FAR *unit;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    unit = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[116] );
        
        NdrInterfacePointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&unit,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[218],
                                       (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IPrimeMeridian *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> put_AngularUnit((IPrimeMeridian *) ((CStdStubBuffer *)This)->pvServerObject,unit);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrInterfacePointerFree( &_StubMsg,
                                 (unsigned char __RPC_FAR *)unit,
                                 &__MIDL_TypeFormatString.Format[218] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

const CINTERFACE_PROXY_VTABLE(20) _IPrimeMeridianProxyVtbl = 
{
    &IID_IPrimeMeridian,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    ISpatialReferenceInfo_get_Name_Proxy ,
    ISpatialReferenceInfo_put_Name_Proxy ,
    ISpatialReferenceInfo_get_Authority_Proxy ,
    ISpatialReferenceInfo_put_Authority_Proxy ,
    ISpatialReferenceInfo_get_Code_Proxy ,
    ISpatialReferenceInfo_put_Code_Proxy ,
    ISpatialReferenceInfo_get_Alias_Proxy ,
    ISpatialReferenceInfo_put_Alias_Proxy ,
    ISpatialReferenceInfo_get_Abbreviation_Proxy ,
    ISpatialReferenceInfo_put_Abbreviation_Proxy ,
    ISpatialReferenceInfo_get_Remarks_Proxy ,
    ISpatialReferenceInfo_put_Remarks_Proxy ,
    ISpatialReferenceInfo_get_WellKnownText_Proxy ,
    IPrimeMeridian_get_Longitude_Proxy ,
    IPrimeMeridian_put_Longitude_Proxy ,
    IPrimeMeridian_get_AngularUnit_Proxy ,
    IPrimeMeridian_put_AngularUnit_Proxy
};


static const PRPC_STUB_FUNCTION IPrimeMeridian_table[] =
{
    ISpatialReferenceInfo_get_Name_Stub,
    ISpatialReferenceInfo_put_Name_Stub,
    ISpatialReferenceInfo_get_Authority_Stub,
    ISpatialReferenceInfo_put_Authority_Stub,
    ISpatialReferenceInfo_get_Code_Stub,
    ISpatialReferenceInfo_put_Code_Stub,
    ISpatialReferenceInfo_get_Alias_Stub,
    ISpatialReferenceInfo_put_Alias_Stub,
    ISpatialReferenceInfo_get_Abbreviation_Stub,
    ISpatialReferenceInfo_put_Abbreviation_Stub,
    ISpatialReferenceInfo_get_Remarks_Stub,
    ISpatialReferenceInfo_put_Remarks_Stub,
    ISpatialReferenceInfo_get_WellKnownText_Stub,
    IPrimeMeridian_get_Longitude_Stub,
    IPrimeMeridian_put_Longitude_Stub,
    IPrimeMeridian_get_AngularUnit_Stub,
    IPrimeMeridian_put_AngularUnit_Stub
};

const CInterfaceStubVtbl _IPrimeMeridianStubVtbl =
{
    &IID_IPrimeMeridian,
    0,
    20,
    &IPrimeMeridian_table[-3],
    CStdStubBuffer_METHODS
};


/* Object interface: ISpatialReference, ver. 0.0,
   GUID={0x4c4c5c00,0xfe1e,0x11d0,{0xad,0x87,0x08,0x00,0x09,0xb6,0xf2,0x2b}} */


extern const MIDL_STUB_DESC Object_StubDesc;


#pragma code_seg(".orpc")
const CINTERFACE_PROXY_VTABLE(16) _ISpatialReferenceProxyVtbl = 
{
    &IID_ISpatialReference,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    ISpatialReferenceInfo_get_Name_Proxy ,
    ISpatialReferenceInfo_put_Name_Proxy ,
    ISpatialReferenceInfo_get_Authority_Proxy ,
    ISpatialReferenceInfo_put_Authority_Proxy ,
    ISpatialReferenceInfo_get_Code_Proxy ,
    ISpatialReferenceInfo_put_Code_Proxy ,
    ISpatialReferenceInfo_get_Alias_Proxy ,
    ISpatialReferenceInfo_put_Alias_Proxy ,
    ISpatialReferenceInfo_get_Abbreviation_Proxy ,
    ISpatialReferenceInfo_put_Abbreviation_Proxy ,
    ISpatialReferenceInfo_get_Remarks_Proxy ,
    ISpatialReferenceInfo_put_Remarks_Proxy ,
    ISpatialReferenceInfo_get_WellKnownText_Proxy
};


static const PRPC_STUB_FUNCTION ISpatialReference_table[] =
{
    ISpatialReferenceInfo_get_Name_Stub,
    ISpatialReferenceInfo_put_Name_Stub,
    ISpatialReferenceInfo_get_Authority_Stub,
    ISpatialReferenceInfo_put_Authority_Stub,
    ISpatialReferenceInfo_get_Code_Stub,
    ISpatialReferenceInfo_put_Code_Stub,
    ISpatialReferenceInfo_get_Alias_Stub,
    ISpatialReferenceInfo_put_Alias_Stub,
    ISpatialReferenceInfo_get_Abbreviation_Stub,
    ISpatialReferenceInfo_put_Abbreviation_Stub,
    ISpatialReferenceInfo_get_Remarks_Stub,
    ISpatialReferenceInfo_put_Remarks_Stub,
    ISpatialReferenceInfo_get_WellKnownText_Stub
};

const CInterfaceStubVtbl _ISpatialReferenceStubVtbl =
{
    &IID_ISpatialReference,
    0,
    16,
    &ISpatialReference_table[-3],
    CStdStubBuffer_METHODS
};


/* Object interface: IGeodeticSpatialReference, ver. 0.0,
   GUID={0x7c3c56d0,0xfe1e,0x11d0,{0xad,0x87,0x08,0x00,0x09,0xb6,0xf2,0x2b}} */


extern const MIDL_STUB_DESC Object_StubDesc;


#pragma code_seg(".orpc")
const CINTERFACE_PROXY_VTABLE(16) _IGeodeticSpatialReferenceProxyVtbl = 
{
    &IID_IGeodeticSpatialReference,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    ISpatialReferenceInfo_get_Name_Proxy ,
    ISpatialReferenceInfo_put_Name_Proxy ,
    ISpatialReferenceInfo_get_Authority_Proxy ,
    ISpatialReferenceInfo_put_Authority_Proxy ,
    ISpatialReferenceInfo_get_Code_Proxy ,
    ISpatialReferenceInfo_put_Code_Proxy ,
    ISpatialReferenceInfo_get_Alias_Proxy ,
    ISpatialReferenceInfo_put_Alias_Proxy ,
    ISpatialReferenceInfo_get_Abbreviation_Proxy ,
    ISpatialReferenceInfo_put_Abbreviation_Proxy ,
    ISpatialReferenceInfo_get_Remarks_Proxy ,
    ISpatialReferenceInfo_put_Remarks_Proxy ,
    ISpatialReferenceInfo_get_WellKnownText_Proxy
};


static const PRPC_STUB_FUNCTION IGeodeticSpatialReference_table[] =
{
    ISpatialReferenceInfo_get_Name_Stub,
    ISpatialReferenceInfo_put_Name_Stub,
    ISpatialReferenceInfo_get_Authority_Stub,
    ISpatialReferenceInfo_put_Authority_Stub,
    ISpatialReferenceInfo_get_Code_Stub,
    ISpatialReferenceInfo_put_Code_Stub,
    ISpatialReferenceInfo_get_Alias_Stub,
    ISpatialReferenceInfo_put_Alias_Stub,
    ISpatialReferenceInfo_get_Abbreviation_Stub,
    ISpatialReferenceInfo_put_Abbreviation_Stub,
    ISpatialReferenceInfo_get_Remarks_Stub,
    ISpatialReferenceInfo_put_Remarks_Stub,
    ISpatialReferenceInfo_get_WellKnownText_Stub
};

const CInterfaceStubVtbl _IGeodeticSpatialReferenceStubVtbl =
{
    &IID_IGeodeticSpatialReference,
    0,
    16,
    &IGeodeticSpatialReference_table[-3],
    CStdStubBuffer_METHODS
};


/* Object interface: IGeographicCoordinateSystem, ver. 0.0,
   GUID={0xa3fd5390,0xfe1e,0x11d0,{0xad,0x87,0x08,0x00,0x09,0xb6,0xf2,0x2b}} */


extern const MIDL_STUB_DESC Object_StubDesc;


#pragma code_seg(".orpc")

/* [propget] */ HRESULT STDMETHODCALLTYPE IGeographicCoordinateSystem_get_Usage_Proxy( 
    IGeographicCoordinateSystem __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *usage)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    MIDL_memset(
               usage,
               0,
               sizeof( BSTR  ));
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      16);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[122] );
            
            NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR * __RPC_FAR *)&usage,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[240],
                                      (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[236],
                         ( void __RPC_FAR * )usage);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IGeographicCoordinateSystem_get_Usage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    BSTR _M16;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    BSTR __RPC_FAR *usage;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    usage = 0;
    RpcTryFinally
        {
        usage = &_M16;
        MIDL_memset(
               usage,
               0,
               sizeof( BSTR  ));
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IGeographicCoordinateSystem *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_Usage((IGeographicCoordinateSystem *) ((CStdStubBuffer *)This)->pvServerObject,usage);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U + 11U;
        NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR *)usage,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[240] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                (unsigned char __RPC_FAR *)usage,
                                (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[240] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)usage,
                        &__MIDL_TypeFormatString.Format[236] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [propput] */ HRESULT STDMETHODCALLTYPE IGeographicCoordinateSystem_put_Usage_Proxy( 
    IGeographicCoordinateSystem __RPC_FAR * This,
    /* [in] */ BSTR usage)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      17);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 4U;
            NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR *)&usage,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[250] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                    (unsigned char __RPC_FAR *)&usage,
                                    (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[250] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[128] );
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IGeographicCoordinateSystem_put_Usage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    void __RPC_FAR *_p_usage;
    BSTR usage;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    _p_usage = &usage;
    MIDL_memset(
               _p_usage,
               0,
               sizeof( BSTR  ));
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[128] );
        
        NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&_p_usage,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[250],
                                  (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IGeographicCoordinateSystem *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> put_Usage((IGeographicCoordinateSystem *) ((CStdStubBuffer *)This)->pvServerObject,usage);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrUserMarshalFree( &_StubMsg,
                            (unsigned char __RPC_FAR *)&usage,
                            &__MIDL_TypeFormatString.Format[250] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [propget] */ HRESULT STDMETHODCALLTYPE IGeographicCoordinateSystem_get_HorizontalDatum_Proxy( 
    IGeographicCoordinateSystem __RPC_FAR * This,
    /* [retval][out] */ IHorizontalDatum __RPC_FAR *__RPC_FAR *datum)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    *datum = 0;
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      18);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[134] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&datum,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[260],
                                  (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[260],
                         ( void __RPC_FAR * )datum);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IGeographicCoordinateSystem_get_HorizontalDatum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    IHorizontalDatum __RPC_FAR *_M17;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    IHorizontalDatum __RPC_FAR *__RPC_FAR *datum;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    datum = 0;
    RpcTryFinally
        {
        datum = &_M17;
        _M17 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IGeographicCoordinateSystem *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_HorizontalDatum((IGeographicCoordinateSystem *) ((CStdStubBuffer *)This)->pvServerObject,datum);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 0U + 4U;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR *)datum,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[260] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char __RPC_FAR *)datum,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[260] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)datum,
                        &__MIDL_TypeFormatString.Format[260] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [propput] */ HRESULT STDMETHODCALLTYPE IGeographicCoordinateSystem_put_HorizontalDatum_Proxy( 
    IGeographicCoordinateSystem __RPC_FAR * This,
    /* [in] */ IHorizontalDatum __RPC_FAR *datum)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      19);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrInterfacePointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                           (unsigned char __RPC_FAR *)datum,
                                           (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[264] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrInterfacePointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                         (unsigned char __RPC_FAR *)datum,
                                         (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[264] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[140] );
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IGeographicCoordinateSystem_put_HorizontalDatum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    IHorizontalDatum __RPC_FAR *datum;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    datum = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[140] );
        
        NdrInterfacePointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&datum,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[264],
                                       (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IGeographicCoordinateSystem *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> put_HorizontalDatum((IGeographicCoordinateSystem *) ((CStdStubBuffer *)This)->pvServerObject,datum);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrInterfacePointerFree( &_StubMsg,
                                 (unsigned char __RPC_FAR *)datum,
                                 &__MIDL_TypeFormatString.Format[264] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [propget] */ HRESULT STDMETHODCALLTYPE IGeographicCoordinateSystem_get_AngularUnit_Proxy( 
    IGeographicCoordinateSystem __RPC_FAR * This,
    /* [retval][out] */ IAngularUnit __RPC_FAR *__RPC_FAR *unit)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    *unit = 0;
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      20);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[110] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&unit,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[214],
                                  (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[214],
                         ( void __RPC_FAR * )unit);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IGeographicCoordinateSystem_get_AngularUnit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    IAngularUnit __RPC_FAR *_M18;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    IAngularUnit __RPC_FAR *__RPC_FAR *unit;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    unit = 0;
    RpcTryFinally
        {
        unit = &_M18;
        _M18 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IGeographicCoordinateSystem *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_AngularUnit((IGeographicCoordinateSystem *) ((CStdStubBuffer *)This)->pvServerObject,unit);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 0U + 4U;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR *)unit,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[214] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char __RPC_FAR *)unit,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[214] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)unit,
                        &__MIDL_TypeFormatString.Format[214] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [propput] */ HRESULT STDMETHODCALLTYPE IGeographicCoordinateSystem_put_AngularUnit_Proxy( 
    IGeographicCoordinateSystem __RPC_FAR * This,
    /* [in] */ IAngularUnit __RPC_FAR *unit)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      21);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrInterfacePointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                           (unsigned char __RPC_FAR *)unit,
                                           (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[218] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrInterfacePointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                         (unsigned char __RPC_FAR *)unit,
                                         (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[218] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[116] );
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IGeographicCoordinateSystem_put_AngularUnit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    IAngularUnit __RPC_FAR *unit;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    unit = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[116] );
        
        NdrInterfacePointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&unit,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[218],
                                       (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IGeographicCoordinateSystem *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> put_AngularUnit((IGeographicCoordinateSystem *) ((CStdStubBuffer *)This)->pvServerObject,unit);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrInterfacePointerFree( &_StubMsg,
                                 (unsigned char __RPC_FAR *)unit,
                                 &__MIDL_TypeFormatString.Format[218] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [propget] */ HRESULT STDMETHODCALLTYPE IGeographicCoordinateSystem_get_PrimeMeridian_Proxy( 
    IGeographicCoordinateSystem __RPC_FAR * This,
    /* [retval][out] */ IPrimeMeridian __RPC_FAR *__RPC_FAR *prmMerid)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    *prmMerid = 0;
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      22);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[146] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&prmMerid,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[282],
                                  (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[282],
                         ( void __RPC_FAR * )prmMerid);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IGeographicCoordinateSystem_get_PrimeMeridian_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    IPrimeMeridian __RPC_FAR *_M19;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    IPrimeMeridian __RPC_FAR *__RPC_FAR *prmMerid;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    prmMerid = 0;
    RpcTryFinally
        {
        prmMerid = &_M19;
        _M19 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IGeographicCoordinateSystem *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_PrimeMeridian((IGeographicCoordinateSystem *) ((CStdStubBuffer *)This)->pvServerObject,prmMerid);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 0U + 4U;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR *)prmMerid,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[282] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char __RPC_FAR *)prmMerid,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[282] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)prmMerid,
                        &__MIDL_TypeFormatString.Format[282] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [propput] */ HRESULT STDMETHODCALLTYPE IGeographicCoordinateSystem_put_PrimeMeridian_Proxy( 
    IGeographicCoordinateSystem __RPC_FAR * This,
    /* [in] */ IPrimeMeridian __RPC_FAR *prmMerid)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      23);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrInterfacePointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                           (unsigned char __RPC_FAR *)prmMerid,
                                           (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[286] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrInterfacePointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                         (unsigned char __RPC_FAR *)prmMerid,
                                         (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[286] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[152] );
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IGeographicCoordinateSystem_put_PrimeMeridian_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    IPrimeMeridian __RPC_FAR *prmMerid;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    prmMerid = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[152] );
        
        NdrInterfacePointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&prmMerid,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[286],
                                       (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IGeographicCoordinateSystem *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> put_PrimeMeridian((IGeographicCoordinateSystem *) ((CStdStubBuffer *)This)->pvServerObject,prmMerid);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrInterfacePointerFree( &_StubMsg,
                                 (unsigned char __RPC_FAR *)prmMerid,
                                 &__MIDL_TypeFormatString.Format[286] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

const CINTERFACE_PROXY_VTABLE(24) _IGeographicCoordinateSystemProxyVtbl = 
{
    &IID_IGeographicCoordinateSystem,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    ISpatialReferenceInfo_get_Name_Proxy ,
    ISpatialReferenceInfo_put_Name_Proxy ,
    ISpatialReferenceInfo_get_Authority_Proxy ,
    ISpatialReferenceInfo_put_Authority_Proxy ,
    ISpatialReferenceInfo_get_Code_Proxy ,
    ISpatialReferenceInfo_put_Code_Proxy ,
    ISpatialReferenceInfo_get_Alias_Proxy ,
    ISpatialReferenceInfo_put_Alias_Proxy ,
    ISpatialReferenceInfo_get_Abbreviation_Proxy ,
    ISpatialReferenceInfo_put_Abbreviation_Proxy ,
    ISpatialReferenceInfo_get_Remarks_Proxy ,
    ISpatialReferenceInfo_put_Remarks_Proxy ,
    ISpatialReferenceInfo_get_WellKnownText_Proxy ,
    IGeographicCoordinateSystem_get_Usage_Proxy ,
    IGeographicCoordinateSystem_put_Usage_Proxy ,
    IGeographicCoordinateSystem_get_HorizontalDatum_Proxy ,
    IGeographicCoordinateSystem_put_HorizontalDatum_Proxy ,
    IGeographicCoordinateSystem_get_AngularUnit_Proxy ,
    IGeographicCoordinateSystem_put_AngularUnit_Proxy ,
    IGeographicCoordinateSystem_get_PrimeMeridian_Proxy ,
    IGeographicCoordinateSystem_put_PrimeMeridian_Proxy
};


static const PRPC_STUB_FUNCTION IGeographicCoordinateSystem_table[] =
{
    ISpatialReferenceInfo_get_Name_Stub,
    ISpatialReferenceInfo_put_Name_Stub,
    ISpatialReferenceInfo_get_Authority_Stub,
    ISpatialReferenceInfo_put_Authority_Stub,
    ISpatialReferenceInfo_get_Code_Stub,
    ISpatialReferenceInfo_put_Code_Stub,
    ISpatialReferenceInfo_get_Alias_Stub,
    ISpatialReferenceInfo_put_Alias_Stub,
    ISpatialReferenceInfo_get_Abbreviation_Stub,
    ISpatialReferenceInfo_put_Abbreviation_Stub,
    ISpatialReferenceInfo_get_Remarks_Stub,
    ISpatialReferenceInfo_put_Remarks_Stub,
    ISpatialReferenceInfo_get_WellKnownText_Stub,
    IGeographicCoordinateSystem_get_Usage_Stub,
    IGeographicCoordinateSystem_put_Usage_Stub,
    IGeographicCoordinateSystem_get_HorizontalDatum_Stub,
    IGeographicCoordinateSystem_put_HorizontalDatum_Stub,
    IGeographicCoordinateSystem_get_AngularUnit_Stub,
    IGeographicCoordinateSystem_put_AngularUnit_Stub,
    IGeographicCoordinateSystem_get_PrimeMeridian_Stub,
    IGeographicCoordinateSystem_put_PrimeMeridian_Stub
};

const CInterfaceStubVtbl _IGeographicCoordinateSystemStubVtbl =
{
    &IID_IGeographicCoordinateSystem,
    0,
    24,
    &IGeographicCoordinateSystem_table[-3],
    CStdStubBuffer_METHODS
};


/* Object interface: IParameter, ver. 0.0,
   GUID={0x9a5e32d0,0xfe1f,0x11d0,{0xad,0x87,0x08,0x00,0x09,0xb6,0xf2,0x2b}} */


extern const MIDL_STUB_DESC Object_StubDesc;


#pragma code_seg(".orpc")

/* [propput] */ HRESULT STDMETHODCALLTYPE IParameter_put_ValueUnit_Proxy( 
    IParameter __RPC_FAR * This,
    /* [in] */ IUnit __RPC_FAR *unit)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      16);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrInterfacePointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                           (unsigned char __RPC_FAR *)unit,
                                           (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[304] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrInterfacePointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                         (unsigned char __RPC_FAR *)unit,
                                         (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[304] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[158] );
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IParameter_put_ValueUnit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    IUnit __RPC_FAR *unit;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    unit = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[158] );
        
        NdrInterfacePointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&unit,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[304],
                                       (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IParameter *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> put_ValueUnit((IParameter *) ((CStdStubBuffer *)This)->pvServerObject,unit);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrInterfacePointerFree( &_StubMsg,
                                 (unsigned char __RPC_FAR *)unit,
                                 &__MIDL_TypeFormatString.Format[304] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [propget] */ HRESULT STDMETHODCALLTYPE IParameter_get_ValueUnit_Proxy( 
    IParameter __RPC_FAR * This,
    /* [retval][out] */ IUnit __RPC_FAR *__RPC_FAR *unit)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    *unit = 0;
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      17);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[164] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&unit,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[322],
                                  (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[322],
                         ( void __RPC_FAR * )unit);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IParameter_get_ValueUnit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    IUnit __RPC_FAR *_M20;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    IUnit __RPC_FAR *__RPC_FAR *unit;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    unit = 0;
    RpcTryFinally
        {
        unit = &_M20;
        _M20 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IParameter *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_ValueUnit((IParameter *) ((CStdStubBuffer *)This)->pvServerObject,unit);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 0U + 4U;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR *)unit,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[322] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char __RPC_FAR *)unit,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[322] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)unit,
                        &__MIDL_TypeFormatString.Format[322] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [propput] */ HRESULT STDMETHODCALLTYPE IParameter_put_Value_Proxy( 
    IParameter __RPC_FAR * This,
    /* [in] */ double value)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      18);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 8U;
            NdrProxyGetBuffer(This, &_StubMsg);
            *(( double __RPC_FAR * )_StubMsg.Buffer)++ = value;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[82] );
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IParameter_put_Value_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    double value;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[82] );
        
        value = *(( double __RPC_FAR * )_StubMsg.Buffer)++;
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IParameter *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> put_Value((IParameter *) ((CStdStubBuffer *)This)->pvServerObject,value);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [propget] */ HRESULT STDMETHODCALLTYPE IParameter_get_Value_Proxy( 
    IParameter __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *value)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      19);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[76] );
            
            *value = *(( double __RPC_FAR * )_StubMsg.Buffer)++;
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[166],
                         ( void __RPC_FAR * )value);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IParameter_get_Value_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    double _M21;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    double __RPC_FAR *value;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    value = 0;
    RpcTryFinally
        {
        value = &_M21;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IParameter *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_Value((IParameter *) ((CStdStubBuffer *)This)->pvServerObject,value);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8U + 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( double __RPC_FAR * )_StubMsg.Buffer)++ = *value;
        
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

const CINTERFACE_PROXY_VTABLE(20) _IParameterProxyVtbl = 
{
    &IID_IParameter,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    ISpatialReferenceInfo_get_Name_Proxy ,
    ISpatialReferenceInfo_put_Name_Proxy ,
    ISpatialReferenceInfo_get_Authority_Proxy ,
    ISpatialReferenceInfo_put_Authority_Proxy ,
    ISpatialReferenceInfo_get_Code_Proxy ,
    ISpatialReferenceInfo_put_Code_Proxy ,
    ISpatialReferenceInfo_get_Alias_Proxy ,
    ISpatialReferenceInfo_put_Alias_Proxy ,
    ISpatialReferenceInfo_get_Abbreviation_Proxy ,
    ISpatialReferenceInfo_put_Abbreviation_Proxy ,
    ISpatialReferenceInfo_get_Remarks_Proxy ,
    ISpatialReferenceInfo_put_Remarks_Proxy ,
    ISpatialReferenceInfo_get_WellKnownText_Proxy ,
    IParameter_put_ValueUnit_Proxy ,
    IParameter_get_ValueUnit_Proxy ,
    IParameter_put_Value_Proxy ,
    IParameter_get_Value_Proxy
};


static const PRPC_STUB_FUNCTION IParameter_table[] =
{
    ISpatialReferenceInfo_get_Name_Stub,
    ISpatialReferenceInfo_put_Name_Stub,
    ISpatialReferenceInfo_get_Authority_Stub,
    ISpatialReferenceInfo_put_Authority_Stub,
    ISpatialReferenceInfo_get_Code_Stub,
    ISpatialReferenceInfo_put_Code_Stub,
    ISpatialReferenceInfo_get_Alias_Stub,
    ISpatialReferenceInfo_put_Alias_Stub,
    ISpatialReferenceInfo_get_Abbreviation_Stub,
    ISpatialReferenceInfo_put_Abbreviation_Stub,
    ISpatialReferenceInfo_get_Remarks_Stub,
    ISpatialReferenceInfo_put_Remarks_Stub,
    ISpatialReferenceInfo_get_WellKnownText_Stub,
    IParameter_put_ValueUnit_Stub,
    IParameter_get_ValueUnit_Stub,
    IParameter_put_Value_Stub,
    IParameter_get_Value_Stub
};

const CInterfaceStubVtbl _IParameterStubVtbl =
{
    &IID_IParameter,
    0,
    20,
    &IParameter_table[-3],
    CStdStubBuffer_METHODS
};


/* Object interface: IParameterInfo, ver. 0.0,
   GUID={0x7309b460,0xfe1f,0x11d0,{0xad,0x87,0x08,0x00,0x09,0xb6,0xf2,0x2b}} */


extern const MIDL_STUB_DESC Object_StubDesc;


#pragma code_seg(".orpc")

/* [propget] */ HRESULT STDMETHODCALLTYPE IParameterInfo_get_NumParameters_Proxy( 
    IParameterInfo __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *numParameters)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      3);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[24] );
            
            *numParameters = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[76],
                         ( void __RPC_FAR * )numParameters);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IParameterInfo_get_NumParameters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    long _M22;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    long __RPC_FAR *numParameters;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    numParameters = 0;
    RpcTryFinally
        {
        numParameters = &_M22;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IParameterInfo *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_NumParameters((IParameterInfo *) ((CStdStubBuffer *)This)->pvServerObject,numParameters);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U + 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( long __RPC_FAR * )_StubMsg.Buffer)++ = *numParameters;
        
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [propget] */ HRESULT STDMETHODCALLTYPE IParameterInfo_get_DefaultParameters_Proxy( 
    IParameterInfo __RPC_FAR * This,
    /* [in] */ long size,
    /* [size_is][out] */ IParameter __RPC_FAR *__RPC_FAR parameters[  ])
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    MIDL_memset(
               parameters,
               0,
               sizeof( IParameter __RPC_FAR *[  ] ));
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      4);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 4U;
            NdrProxyGetBuffer(This, &_StubMsg);
            *(( long __RPC_FAR * )_StubMsg.Buffer)++ = size;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[170] );
            
            NdrComplexArrayUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&parameters,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[344],
                                       (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _StubMsg.MaxCount = size;
        
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[344],
                         ( void __RPC_FAR * )parameters);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IParameterInfo_get_DefaultParameters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    IParameter __RPC_FAR *( __RPC_FAR *parameters )[  ];
    long size;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    parameters = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[170] );
        
        size = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        parameters = _StubMsg.pfnAllocate(size * 4);
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IParameterInfo *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_DefaultParameters(
                         (IParameterInfo *) ((CStdStubBuffer *)This)->pvServerObject,
                         size,
                         *parameters);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U + 7U;
        _StubMsg.MaxCount = size;
        
        NdrComplexArrayBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)*parameters,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[344] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.MaxCount = size;
        
        NdrComplexArrayMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)*parameters,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[344] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        _StubMsg.MaxCount = size;
        
        NdrComplexArrayFree( &_StubMsg,
                             (unsigned char __RPC_FAR *)parameters,
                             &__MIDL_TypeFormatString.Format[344] );
        
        if ( parameters )
            _StubMsg.pfnFree( parameters );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [propget] */ HRESULT STDMETHODCALLTYPE IParameterInfo_get_Parameters_Proxy( 
    IParameterInfo __RPC_FAR * This,
    /* [in] */ long size,
    /* [size_is][out] */ IParameter __RPC_FAR *__RPC_FAR parameters[  ])
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    MIDL_memset(
               parameters,
               0,
               sizeof( IParameter __RPC_FAR *[  ] ));
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      5);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 4U;
            NdrProxyGetBuffer(This, &_StubMsg);
            *(( long __RPC_FAR * )_StubMsg.Buffer)++ = size;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[170] );
            
            NdrComplexArrayUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&parameters,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[344],
                                       (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _StubMsg.MaxCount = size;
        
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[344],
                         ( void __RPC_FAR * )parameters);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IParameterInfo_get_Parameters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    IParameter __RPC_FAR *( __RPC_FAR *parameters )[  ];
    long size;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    parameters = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[170] );
        
        size = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        parameters = _StubMsg.pfnAllocate(size * 4);
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IParameterInfo *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_Parameters(
                  (IParameterInfo *) ((CStdStubBuffer *)This)->pvServerObject,
                  size,
                  *parameters);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U + 7U;
        _StubMsg.MaxCount = size;
        
        NdrComplexArrayBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)*parameters,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[344] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.MaxCount = size;
        
        NdrComplexArrayMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)*parameters,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[344] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        _StubMsg.MaxCount = size;
        
        NdrComplexArrayFree( &_StubMsg,
                             (unsigned char __RPC_FAR *)parameters,
                             &__MIDL_TypeFormatString.Format[344] );
        
        if ( parameters )
            _StubMsg.pfnFree( parameters );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [propput] */ HRESULT STDMETHODCALLTYPE IParameterInfo_put_Parameters_Proxy( 
    IParameterInfo __RPC_FAR * This,
    /* [in] */ long size,
    /* [size_is][in] */ IParameter __RPC_FAR *__RPC_FAR parameters[  ])
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      6);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 4U + 4U;
            _StubMsg.MaxCount = size;
            
            NdrComplexArrayBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)parameters,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[344] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            *(( long __RPC_FAR * )_StubMsg.Buffer)++ = size;
            
            _StubMsg.MaxCount = size;
            
            NdrComplexArrayMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)parameters,
                                     (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[344] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[178] );
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IParameterInfo_put_Parameters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    IParameter __RPC_FAR *( __RPC_FAR *parameters )[  ];
    long size;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    parameters = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[178] );
        
        size = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        NdrComplexArrayUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR * __RPC_FAR *)&parameters,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[344],
                                   (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IParameterInfo *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> put_Parameters(
                  (IParameterInfo *) ((CStdStubBuffer *)This)->pvServerObject,
                  size,
                  *parameters);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        _StubMsg.MaxCount = size;
        
        NdrComplexArrayFree( &_StubMsg,
                             (unsigned char __RPC_FAR *)parameters,
                             &__MIDL_TypeFormatString.Format[344] );
        
        if ( parameters )
            _StubMsg.pfnFree( parameters );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

const CINTERFACE_PROXY_VTABLE(7) _IParameterInfoProxyVtbl = 
{
    &IID_IParameterInfo,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    IParameterInfo_get_NumParameters_Proxy ,
    IParameterInfo_get_DefaultParameters_Proxy ,
    IParameterInfo_get_Parameters_Proxy ,
    IParameterInfo_put_Parameters_Proxy
};


static const PRPC_STUB_FUNCTION IParameterInfo_table[] =
{
    IParameterInfo_get_NumParameters_Stub,
    IParameterInfo_get_DefaultParameters_Stub,
    IParameterInfo_get_Parameters_Stub,
    IParameterInfo_put_Parameters_Stub
};

const CInterfaceStubVtbl _IParameterInfoStubVtbl =
{
    &IID_IParameterInfo,
    0,
    7,
    &IParameterInfo_table[-3],
    CStdStubBuffer_METHODS
};


/* Object interface: IGeographicTransform, ver. 0.0,
   GUID={0x5eb513c0,0xfe1f,0x11d0,{0xad,0x87,0x08,0x00,0x09,0xb6,0xf2,0x2b}} */


extern const MIDL_STUB_DESC Object_StubDesc;


#pragma code_seg(".orpc")

/* [propget] */ HRESULT STDMETHODCALLTYPE IGeographicTransform_get_SourceGCS_Proxy( 
    IGeographicTransform __RPC_FAR * This,
    /* [out] */ IGeographicCoordinateSystem __RPC_FAR *__RPC_FAR *gcs)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    *gcs = 0;
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      16);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[186] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&gcs,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[362],
                                  (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[362],
                         ( void __RPC_FAR * )gcs);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IGeographicTransform_get_SourceGCS_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    IGeographicCoordinateSystem __RPC_FAR *_M26;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    IGeographicCoordinateSystem __RPC_FAR *__RPC_FAR *gcs;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    gcs = 0;
    RpcTryFinally
        {
        gcs = &_M26;
        _M26 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IGeographicTransform *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_SourceGCS((IGeographicTransform *) ((CStdStubBuffer *)This)->pvServerObject,gcs);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 0U + 4U;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR *)gcs,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[362] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char __RPC_FAR *)gcs,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[362] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)gcs,
                        &__MIDL_TypeFormatString.Format[362] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [propput] */ HRESULT STDMETHODCALLTYPE IGeographicTransform_put_SourceGCS_Proxy( 
    IGeographicTransform __RPC_FAR * This,
    /* [in] */ IGeographicCoordinateSystem __RPC_FAR *gcs)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      17);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrInterfacePointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                           (unsigned char __RPC_FAR *)gcs,
                                           (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[366] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrInterfacePointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                         (unsigned char __RPC_FAR *)gcs,
                                         (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[366] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[192] );
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IGeographicTransform_put_SourceGCS_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    IGeographicCoordinateSystem __RPC_FAR *gcs;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    gcs = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[192] );
        
        NdrInterfacePointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&gcs,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[366],
                                       (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IGeographicTransform *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> put_SourceGCS((IGeographicTransform *) ((CStdStubBuffer *)This)->pvServerObject,gcs);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrInterfacePointerFree( &_StubMsg,
                                 (unsigned char __RPC_FAR *)gcs,
                                 &__MIDL_TypeFormatString.Format[366] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [propget] */ HRESULT STDMETHODCALLTYPE IGeographicTransform_get_TargetGCS_Proxy( 
    IGeographicTransform __RPC_FAR * This,
    /* [out] */ IGeographicCoordinateSystem __RPC_FAR *__RPC_FAR *gcs)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    *gcs = 0;
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      18);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[186] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&gcs,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[362],
                                  (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[362],
                         ( void __RPC_FAR * )gcs);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IGeographicTransform_get_TargetGCS_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    IGeographicCoordinateSystem __RPC_FAR *_M27;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    IGeographicCoordinateSystem __RPC_FAR *__RPC_FAR *gcs;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    gcs = 0;
    RpcTryFinally
        {
        gcs = &_M27;
        _M27 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IGeographicTransform *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_TargetGCS((IGeographicTransform *) ((CStdStubBuffer *)This)->pvServerObject,gcs);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 0U + 4U;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR *)gcs,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[362] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char __RPC_FAR *)gcs,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[362] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)gcs,
                        &__MIDL_TypeFormatString.Format[362] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [propput] */ HRESULT STDMETHODCALLTYPE IGeographicTransform_put_TargetGCS_Proxy( 
    IGeographicTransform __RPC_FAR * This,
    /* [in] */ IGeographicCoordinateSystem __RPC_FAR *gcs)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      19);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrInterfacePointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                           (unsigned char __RPC_FAR *)gcs,
                                           (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[366] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrInterfacePointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                         (unsigned char __RPC_FAR *)gcs,
                                         (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[366] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[192] );
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IGeographicTransform_put_TargetGCS_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    IGeographicCoordinateSystem __RPC_FAR *gcs;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    gcs = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[192] );
        
        NdrInterfacePointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&gcs,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[366],
                                       (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IGeographicTransform *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> put_TargetGCS((IGeographicTransform *) ((CStdStubBuffer *)This)->pvServerObject,gcs);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrInterfacePointerFree( &_StubMsg,
                                 (unsigned char __RPC_FAR *)gcs,
                                 &__MIDL_TypeFormatString.Format[366] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [propget] */ HRESULT STDMETHODCALLTYPE IGeographicTransform_get_ParameterInfo_Proxy( 
    IGeographicTransform __RPC_FAR * This,
    /* [out] */ IParameterInfo __RPC_FAR *__RPC_FAR *paramInfo)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    *paramInfo = 0;
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      20);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[198] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&paramInfo,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[384],
                                  (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[384],
                         ( void __RPC_FAR * )paramInfo);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IGeographicTransform_get_ParameterInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    IParameterInfo __RPC_FAR *_M28;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    IParameterInfo __RPC_FAR *__RPC_FAR *paramInfo;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    paramInfo = 0;
    RpcTryFinally
        {
        paramInfo = &_M28;
        _M28 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IGeographicTransform *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_ParameterInfo((IGeographicTransform *) ((CStdStubBuffer *)This)->pvServerObject,paramInfo);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 0U + 4U;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR *)paramInfo,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[384] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char __RPC_FAR *)paramInfo,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[384] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)paramInfo,
                        &__MIDL_TypeFormatString.Format[384] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


HRESULT STDMETHODCALLTYPE IGeographicTransform_Forward_Proxy( 
    IGeographicTransform __RPC_FAR * This,
    /* [in] */ long count,
    /* [size_is][out][in] */ WKSPoint __RPC_FAR points[  ])
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      21);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 4U + 4U;
            _StubMsg.MaxCount = count;
            
            NdrConformantArrayBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                          (unsigned char __RPC_FAR *)points,
                                          (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[414] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            *(( long __RPC_FAR * )_StubMsg.Buffer)++ = count;
            
            _StubMsg.MaxCount = count;
            
            NdrConformantArrayMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                        (unsigned char __RPC_FAR *)points,
                                        (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[414] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[204] );
            
            NdrConformantArrayUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                          (unsigned char __RPC_FAR * __RPC_FAR *)&points,
                                          (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[414],
                                          (unsigned char)0 );
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _StubMsg.MaxCount = count;
        
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[414],
                         ( void __RPC_FAR * )points);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IGeographicTransform_Forward_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    long count;
    WKSPoint ( __RPC_FAR *points )[  ];
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    points = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[204] );
        
        count = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        NdrConformantArrayUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR * __RPC_FAR *)&points,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[414],
                                      (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IGeographicTransform *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> Forward(
           (IGeographicTransform *) ((CStdStubBuffer *)This)->pvServerObject,
           count,
           *points);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U + 8U;
        _StubMsg.MaxCount = count;
        
        NdrConformantArrayBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR *)*points,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[414] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.MaxCount = count;
        
        NdrConformantArrayMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                    (unsigned char __RPC_FAR *)*points,
                                    (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[414] );
        
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


HRESULT STDMETHODCALLTYPE IGeographicTransform_Inverse_Proxy( 
    IGeographicTransform __RPC_FAR * This,
    /* [in] */ long count,
    /* [size_is][out][in] */ WKSPoint __RPC_FAR points[  ])
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      22);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 4U + 4U;
            _StubMsg.MaxCount = count;
            
            NdrConformantArrayBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                          (unsigned char __RPC_FAR *)points,
                                          (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[414] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            *(( long __RPC_FAR * )_StubMsg.Buffer)++ = count;
            
            _StubMsg.MaxCount = count;
            
            NdrConformantArrayMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                        (unsigned char __RPC_FAR *)points,
                                        (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[414] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[204] );
            
            NdrConformantArrayUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                          (unsigned char __RPC_FAR * __RPC_FAR *)&points,
                                          (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[414],
                                          (unsigned char)0 );
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _StubMsg.MaxCount = count;
        
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[414],
                         ( void __RPC_FAR * )points);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IGeographicTransform_Inverse_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    long count;
    WKSPoint ( __RPC_FAR *points )[  ];
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    points = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[204] );
        
        count = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        NdrConformantArrayUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR * __RPC_FAR *)&points,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[414],
                                      (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IGeographicTransform *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> Inverse(
           (IGeographicTransform *) ((CStdStubBuffer *)This)->pvServerObject,
           count,
           *points);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U + 8U;
        _StubMsg.MaxCount = count;
        
        NdrConformantArrayBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR *)*points,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[414] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.MaxCount = count;
        
        NdrConformantArrayMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                    (unsigned char __RPC_FAR *)*points,
                                    (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[414] );
        
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

const CINTERFACE_PROXY_VTABLE(23) _IGeographicTransformProxyVtbl = 
{
    &IID_IGeographicTransform,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    ISpatialReferenceInfo_get_Name_Proxy ,
    ISpatialReferenceInfo_put_Name_Proxy ,
    ISpatialReferenceInfo_get_Authority_Proxy ,
    ISpatialReferenceInfo_put_Authority_Proxy ,
    ISpatialReferenceInfo_get_Code_Proxy ,
    ISpatialReferenceInfo_put_Code_Proxy ,
    ISpatialReferenceInfo_get_Alias_Proxy ,
    ISpatialReferenceInfo_put_Alias_Proxy ,
    ISpatialReferenceInfo_get_Abbreviation_Proxy ,
    ISpatialReferenceInfo_put_Abbreviation_Proxy ,
    ISpatialReferenceInfo_get_Remarks_Proxy ,
    ISpatialReferenceInfo_put_Remarks_Proxy ,
    ISpatialReferenceInfo_get_WellKnownText_Proxy ,
    IGeographicTransform_get_SourceGCS_Proxy ,
    IGeographicTransform_put_SourceGCS_Proxy ,
    IGeographicTransform_get_TargetGCS_Proxy ,
    IGeographicTransform_put_TargetGCS_Proxy ,
    IGeographicTransform_get_ParameterInfo_Proxy ,
    IGeographicTransform_Forward_Proxy ,
    IGeographicTransform_Inverse_Proxy
};


static const PRPC_STUB_FUNCTION IGeographicTransform_table[] =
{
    ISpatialReferenceInfo_get_Name_Stub,
    ISpatialReferenceInfo_put_Name_Stub,
    ISpatialReferenceInfo_get_Authority_Stub,
    ISpatialReferenceInfo_put_Authority_Stub,
    ISpatialReferenceInfo_get_Code_Stub,
    ISpatialReferenceInfo_put_Code_Stub,
    ISpatialReferenceInfo_get_Alias_Stub,
    ISpatialReferenceInfo_put_Alias_Stub,
    ISpatialReferenceInfo_get_Abbreviation_Stub,
    ISpatialReferenceInfo_put_Abbreviation_Stub,
    ISpatialReferenceInfo_get_Remarks_Stub,
    ISpatialReferenceInfo_put_Remarks_Stub,
    ISpatialReferenceInfo_get_WellKnownText_Stub,
    IGeographicTransform_get_SourceGCS_Stub,
    IGeographicTransform_put_SourceGCS_Stub,
    IGeographicTransform_get_TargetGCS_Stub,
    IGeographicTransform_put_TargetGCS_Stub,
    IGeographicTransform_get_ParameterInfo_Stub,
    IGeographicTransform_Forward_Stub,
    IGeographicTransform_Inverse_Stub
};

const CInterfaceStubVtbl _IGeographicTransformStubVtbl =
{
    &IID_IGeographicTransform,
    0,
    23,
    &IGeographicTransform_table[-3],
    CStdStubBuffer_METHODS
};


/* Object interface: IProjection, ver. 0.0,
   GUID={0x5002f420,0xfe1f,0x11d0,{0xad,0x87,0x08,0x00,0x09,0xb6,0xf2,0x2b}} */


extern const MIDL_STUB_DESC Object_StubDesc;


#pragma code_seg(".orpc")

/* [propget] */ HRESULT STDMETHODCALLTYPE IProjection_get_Usage_Proxy( 
    IProjection __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *usage)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    MIDL_memset(
               usage,
               0,
               sizeof( BSTR  ));
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      16);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[212] );
            
            NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR * __RPC_FAR *)&usage,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[432],
                                      (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[428],
                         ( void __RPC_FAR * )usage);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IProjection_get_Usage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    BSTR _M31;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    BSTR __RPC_FAR *usage;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    usage = 0;
    RpcTryFinally
        {
        usage = &_M31;
        MIDL_memset(
               usage,
               0,
               sizeof( BSTR  ));
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IProjection *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_Usage((IProjection *) ((CStdStubBuffer *)This)->pvServerObject,usage);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U + 11U;
        NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR *)usage,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[432] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                (unsigned char __RPC_FAR *)usage,
                                (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[432] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)usage,
                        &__MIDL_TypeFormatString.Format[428] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [propget] */ HRESULT STDMETHODCALLTYPE IProjection_get_Classification_Proxy( 
    IProjection __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *classification)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    MIDL_memset(
               classification,
               0,
               sizeof( BSTR  ));
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      17);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[218] );
            
            NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR * __RPC_FAR *)&classification,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[446],
                                      (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[442],
                         ( void __RPC_FAR * )classification);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IProjection_get_Classification_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    BSTR _M32;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    BSTR __RPC_FAR *classification;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    classification = 0;
    RpcTryFinally
        {
        classification = &_M32;
        MIDL_memset(
               classification,
               0,
               sizeof( BSTR  ));
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IProjection *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_Classification((IProjection *) ((CStdStubBuffer *)This)->pvServerObject,classification);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U + 11U;
        NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR *)classification,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[446] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                (unsigned char __RPC_FAR *)classification,
                                (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[446] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)classification,
                        &__MIDL_TypeFormatString.Format[442] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


HRESULT STDMETHODCALLTYPE IProjection_Forward_Proxy( 
    IProjection __RPC_FAR * This,
    /* [in] */ long count,
    /* [size_is][out][in] */ WKSPoint __RPC_FAR points[  ])
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      18);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 4U + 4U;
            _StubMsg.MaxCount = count;
            
            NdrConformantArrayBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                          (unsigned char __RPC_FAR *)points,
                                          (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[414] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            *(( long __RPC_FAR * )_StubMsg.Buffer)++ = count;
            
            _StubMsg.MaxCount = count;
            
            NdrConformantArrayMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                        (unsigned char __RPC_FAR *)points,
                                        (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[414] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[204] );
            
            NdrConformantArrayUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                          (unsigned char __RPC_FAR * __RPC_FAR *)&points,
                                          (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[414],
                                          (unsigned char)0 );
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _StubMsg.MaxCount = count;
        
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[414],
                         ( void __RPC_FAR * )points);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IProjection_Forward_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    long count;
    WKSPoint ( __RPC_FAR *points )[  ];
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    points = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[204] );
        
        count = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        NdrConformantArrayUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR * __RPC_FAR *)&points,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[414],
                                      (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IProjection *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> Forward(
           (IProjection *) ((CStdStubBuffer *)This)->pvServerObject,
           count,
           *points);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U + 8U;
        _StubMsg.MaxCount = count;
        
        NdrConformantArrayBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR *)*points,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[414] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.MaxCount = count;
        
        NdrConformantArrayMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                    (unsigned char __RPC_FAR *)*points,
                                    (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[414] );
        
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


HRESULT STDMETHODCALLTYPE IProjection_Inverse_Proxy( 
    IProjection __RPC_FAR * This,
    /* [in] */ long count,
    /* [size_is][out][in] */ WKSPoint __RPC_FAR points[  ])
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      19);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 4U + 4U;
            _StubMsg.MaxCount = count;
            
            NdrConformantArrayBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                          (unsigned char __RPC_FAR *)points,
                                          (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[414] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            *(( long __RPC_FAR * )_StubMsg.Buffer)++ = count;
            
            _StubMsg.MaxCount = count;
            
            NdrConformantArrayMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                        (unsigned char __RPC_FAR *)points,
                                        (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[414] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[204] );
            
            NdrConformantArrayUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                          (unsigned char __RPC_FAR * __RPC_FAR *)&points,
                                          (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[414],
                                          (unsigned char)0 );
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _StubMsg.MaxCount = count;
        
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[414],
                         ( void __RPC_FAR * )points);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IProjection_Inverse_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    long count;
    WKSPoint ( __RPC_FAR *points )[  ];
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    points = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[204] );
        
        count = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        NdrConformantArrayUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR * __RPC_FAR *)&points,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[414],
                                      (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IProjection *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> Inverse(
           (IProjection *) ((CStdStubBuffer *)This)->pvServerObject,
           count,
           *points);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U + 8U;
        _StubMsg.MaxCount = count;
        
        NdrConformantArrayBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR *)*points,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[414] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.MaxCount = count;
        
        NdrConformantArrayMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                    (unsigned char __RPC_FAR *)*points,
                                    (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[414] );
        
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [propget] */ HRESULT STDMETHODCALLTYPE IProjection_get_ParameterInfo_Proxy( 
    IProjection __RPC_FAR * This,
    /* [retval][out] */ IParameterInfo __RPC_FAR *__RPC_FAR *paramInfo)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    *paramInfo = 0;
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      20);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[198] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&paramInfo,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[384],
                                  (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[384],
                         ( void __RPC_FAR * )paramInfo);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IProjection_get_ParameterInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    IParameterInfo __RPC_FAR *_M35;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    IParameterInfo __RPC_FAR *__RPC_FAR *paramInfo;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    paramInfo = 0;
    RpcTryFinally
        {
        paramInfo = &_M35;
        _M35 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IProjection *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_ParameterInfo((IProjection *) ((CStdStubBuffer *)This)->pvServerObject,paramInfo);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 0U + 4U;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR *)paramInfo,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[384] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char __RPC_FAR *)paramInfo,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[384] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)paramInfo,
                        &__MIDL_TypeFormatString.Format[384] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [propget] */ HRESULT STDMETHODCALLTYPE IProjection_get_AngularUnit_Proxy( 
    IProjection __RPC_FAR * This,
    /* [retval][out] */ IAngularUnit __RPC_FAR *__RPC_FAR *unit)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    *unit = 0;
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      21);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[110] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&unit,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[214],
                                  (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[214],
                         ( void __RPC_FAR * )unit);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IProjection_get_AngularUnit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    IAngularUnit __RPC_FAR *_M36;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    IAngularUnit __RPC_FAR *__RPC_FAR *unit;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    unit = 0;
    RpcTryFinally
        {
        unit = &_M36;
        _M36 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IProjection *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_AngularUnit((IProjection *) ((CStdStubBuffer *)This)->pvServerObject,unit);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 0U + 4U;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR *)unit,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[214] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char __RPC_FAR *)unit,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[214] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)unit,
                        &__MIDL_TypeFormatString.Format[214] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [propput] */ HRESULT STDMETHODCALLTYPE IProjection_put_AngularUnit_Proxy( 
    IProjection __RPC_FAR * This,
    /* [in] */ IAngularUnit __RPC_FAR *unit)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      22);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrInterfacePointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                           (unsigned char __RPC_FAR *)unit,
                                           (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[218] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrInterfacePointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                         (unsigned char __RPC_FAR *)unit,
                                         (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[218] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[116] );
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IProjection_put_AngularUnit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    IAngularUnit __RPC_FAR *unit;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    unit = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[116] );
        
        NdrInterfacePointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&unit,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[218],
                                       (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IProjection *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> put_AngularUnit((IProjection *) ((CStdStubBuffer *)This)->pvServerObject,unit);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrInterfacePointerFree( &_StubMsg,
                                 (unsigned char __RPC_FAR *)unit,
                                 &__MIDL_TypeFormatString.Format[218] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [propget] */ HRESULT STDMETHODCALLTYPE IProjection_get_LinearUnit_Proxy( 
    IProjection __RPC_FAR * This,
    /* [retval][out] */ ILinearUnit __RPC_FAR *__RPC_FAR *unit)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    *unit = 0;
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      23);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[86] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&unit,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[170],
                                  (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[170],
                         ( void __RPC_FAR * )unit);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IProjection_get_LinearUnit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    ILinearUnit __RPC_FAR *_M37;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    ILinearUnit __RPC_FAR *__RPC_FAR *unit;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    unit = 0;
    RpcTryFinally
        {
        unit = &_M37;
        _M37 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IProjection *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_LinearUnit((IProjection *) ((CStdStubBuffer *)This)->pvServerObject,unit);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 0U + 4U;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR *)unit,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[170] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char __RPC_FAR *)unit,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[170] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)unit,
                        &__MIDL_TypeFormatString.Format[170] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [propput] */ HRESULT STDMETHODCALLTYPE IProjection_put_LinearUnit_Proxy( 
    IProjection __RPC_FAR * This,
    /* [in] */ ILinearUnit __RPC_FAR *unit)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      24);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrInterfacePointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                           (unsigned char __RPC_FAR *)unit,
                                           (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[174] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrInterfacePointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                         (unsigned char __RPC_FAR *)unit,
                                         (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[174] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[92] );
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IProjection_put_LinearUnit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    ILinearUnit __RPC_FAR *unit;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    unit = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[92] );
        
        NdrInterfacePointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&unit,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[174],
                                       (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IProjection *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> put_LinearUnit((IProjection *) ((CStdStubBuffer *)This)->pvServerObject,unit);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrInterfacePointerFree( &_StubMsg,
                                 (unsigned char __RPC_FAR *)unit,
                                 &__MIDL_TypeFormatString.Format[174] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [propget] */ HRESULT STDMETHODCALLTYPE IProjection_get_Ellipsoid_Proxy( 
    IProjection __RPC_FAR * This,
    /* [retval][out] */ IEllipsoid __RPC_FAR *__RPC_FAR *ellipsoid)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    *ellipsoid = 0;
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      25);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[98] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&ellipsoid,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[192],
                                  (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[192],
                         ( void __RPC_FAR * )ellipsoid);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IProjection_get_Ellipsoid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    IEllipsoid __RPC_FAR *_M38;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    IEllipsoid __RPC_FAR *__RPC_FAR *ellipsoid;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ellipsoid = 0;
    RpcTryFinally
        {
        ellipsoid = &_M38;
        _M38 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IProjection *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_Ellipsoid((IProjection *) ((CStdStubBuffer *)This)->pvServerObject,ellipsoid);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 0U + 4U;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR *)ellipsoid,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[192] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char __RPC_FAR *)ellipsoid,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[192] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)ellipsoid,
                        &__MIDL_TypeFormatString.Format[192] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [propput] */ HRESULT STDMETHODCALLTYPE IProjection_put_Ellipsoid_Proxy( 
    IProjection __RPC_FAR * This,
    /* [in] */ IEllipsoid __RPC_FAR *ellipsoid)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      26);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrInterfacePointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                           (unsigned char __RPC_FAR *)ellipsoid,
                                           (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[196] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrInterfacePointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                         (unsigned char __RPC_FAR *)ellipsoid,
                                         (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[196] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[104] );
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IProjection_put_Ellipsoid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    IEllipsoid __RPC_FAR *ellipsoid;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ellipsoid = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[104] );
        
        NdrInterfacePointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&ellipsoid,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[196],
                                       (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IProjection *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> put_Ellipsoid((IProjection *) ((CStdStubBuffer *)This)->pvServerObject,ellipsoid);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrInterfacePointerFree( &_StubMsg,
                                 (unsigned char __RPC_FAR *)ellipsoid,
                                 &__MIDL_TypeFormatString.Format[196] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

const CINTERFACE_PROXY_VTABLE(27) _IProjectionProxyVtbl = 
{
    &IID_IProjection,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    ISpatialReferenceInfo_get_Name_Proxy ,
    ISpatialReferenceInfo_put_Name_Proxy ,
    ISpatialReferenceInfo_get_Authority_Proxy ,
    ISpatialReferenceInfo_put_Authority_Proxy ,
    ISpatialReferenceInfo_get_Code_Proxy ,
    ISpatialReferenceInfo_put_Code_Proxy ,
    ISpatialReferenceInfo_get_Alias_Proxy ,
    ISpatialReferenceInfo_put_Alias_Proxy ,
    ISpatialReferenceInfo_get_Abbreviation_Proxy ,
    ISpatialReferenceInfo_put_Abbreviation_Proxy ,
    ISpatialReferenceInfo_get_Remarks_Proxy ,
    ISpatialReferenceInfo_put_Remarks_Proxy ,
    ISpatialReferenceInfo_get_WellKnownText_Proxy ,
    IProjection_get_Usage_Proxy ,
    IProjection_get_Classification_Proxy ,
    IProjection_Forward_Proxy ,
    IProjection_Inverse_Proxy ,
    IProjection_get_ParameterInfo_Proxy ,
    IProjection_get_AngularUnit_Proxy ,
    IProjection_put_AngularUnit_Proxy ,
    IProjection_get_LinearUnit_Proxy ,
    IProjection_put_LinearUnit_Proxy ,
    IProjection_get_Ellipsoid_Proxy ,
    IProjection_put_Ellipsoid_Proxy
};


static const PRPC_STUB_FUNCTION IProjection_table[] =
{
    ISpatialReferenceInfo_get_Name_Stub,
    ISpatialReferenceInfo_put_Name_Stub,
    ISpatialReferenceInfo_get_Authority_Stub,
    ISpatialReferenceInfo_put_Authority_Stub,
    ISpatialReferenceInfo_get_Code_Stub,
    ISpatialReferenceInfo_put_Code_Stub,
    ISpatialReferenceInfo_get_Alias_Stub,
    ISpatialReferenceInfo_put_Alias_Stub,
    ISpatialReferenceInfo_get_Abbreviation_Stub,
    ISpatialReferenceInfo_put_Abbreviation_Stub,
    ISpatialReferenceInfo_get_Remarks_Stub,
    ISpatialReferenceInfo_put_Remarks_Stub,
    ISpatialReferenceInfo_get_WellKnownText_Stub,
    IProjection_get_Usage_Stub,
    IProjection_get_Classification_Stub,
    IProjection_Forward_Stub,
    IProjection_Inverse_Stub,
    IProjection_get_ParameterInfo_Stub,
    IProjection_get_AngularUnit_Stub,
    IProjection_put_AngularUnit_Stub,
    IProjection_get_LinearUnit_Stub,
    IProjection_put_LinearUnit_Stub,
    IProjection_get_Ellipsoid_Stub,
    IProjection_put_Ellipsoid_Stub
};

const CInterfaceStubVtbl _IProjectionStubVtbl =
{
    &IID_IProjection,
    0,
    27,
    &IProjection_table[-3],
    CStdStubBuffer_METHODS
};


/* Object interface: IProjectedCoordinateSystem, ver. 0.0,
   GUID={0x3dc39ff0,0xfe1f,0x11d0,{0xad,0x87,0x08,0x00,0x09,0xb6,0xf2,0x2b}} */


extern const MIDL_STUB_DESC Object_StubDesc;


#pragma code_seg(".orpc")

/* [propget] */ HRESULT STDMETHODCALLTYPE IProjectedCoordinateSystem_get_Usage_Proxy( 
    IProjectedCoordinateSystem __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *usage)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    MIDL_memset(
               usage,
               0,
               sizeof( BSTR  ));
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      16);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[224] );
            
            NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR * __RPC_FAR *)&usage,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[460],
                                      (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[456],
                         ( void __RPC_FAR * )usage);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IProjectedCoordinateSystem_get_Usage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    BSTR _M39;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    BSTR __RPC_FAR *usage;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    usage = 0;
    RpcTryFinally
        {
        usage = &_M39;
        MIDL_memset(
               usage,
               0,
               sizeof( BSTR  ));
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IProjectedCoordinateSystem *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_Usage((IProjectedCoordinateSystem *) ((CStdStubBuffer *)This)->pvServerObject,usage);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U + 11U;
        NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR *)usage,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[460] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                (unsigned char __RPC_FAR *)usage,
                                (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[460] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)usage,
                        &__MIDL_TypeFormatString.Format[456] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [propput] */ HRESULT STDMETHODCALLTYPE IProjectedCoordinateSystem_put_Usage_Proxy( 
    IProjectedCoordinateSystem __RPC_FAR * This,
    /* [in] */ BSTR usage)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      17);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 4U;
            NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR *)&usage,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[470] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                    (unsigned char __RPC_FAR *)&usage,
                                    (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[470] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[230] );
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IProjectedCoordinateSystem_put_Usage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    void __RPC_FAR *_p_usage;
    BSTR usage;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    _p_usage = &usage;
    MIDL_memset(
               _p_usage,
               0,
               sizeof( BSTR  ));
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[230] );
        
        NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&_p_usage,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[470],
                                  (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IProjectedCoordinateSystem *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> put_Usage((IProjectedCoordinateSystem *) ((CStdStubBuffer *)This)->pvServerObject,usage);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrUserMarshalFree( &_StubMsg,
                            (unsigned char __RPC_FAR *)&usage,
                            &__MIDL_TypeFormatString.Format[470] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [propget] */ HRESULT STDMETHODCALLTYPE IProjectedCoordinateSystem_get_GeographicCoordinateSystem_Proxy( 
    IProjectedCoordinateSystem __RPC_FAR * This,
    /* [retval][out] */ IGeographicCoordinateSystem __RPC_FAR *__RPC_FAR *gcs)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    *gcs = 0;
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      18);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[186] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&gcs,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[362],
                                  (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[362],
                         ( void __RPC_FAR * )gcs);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IProjectedCoordinateSystem_get_GeographicCoordinateSystem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    IGeographicCoordinateSystem __RPC_FAR *_M40;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    IGeographicCoordinateSystem __RPC_FAR *__RPC_FAR *gcs;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    gcs = 0;
    RpcTryFinally
        {
        gcs = &_M40;
        _M40 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IProjectedCoordinateSystem *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_GeographicCoordinateSystem((IProjectedCoordinateSystem *) ((CStdStubBuffer *)This)->pvServerObject,gcs);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 0U + 4U;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR *)gcs,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[362] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char __RPC_FAR *)gcs,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[362] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)gcs,
                        &__MIDL_TypeFormatString.Format[362] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [propput] */ HRESULT STDMETHODCALLTYPE IProjectedCoordinateSystem_put_GeographicCoordinateSystem_Proxy( 
    IProjectedCoordinateSystem __RPC_FAR * This,
    /* [in] */ IGeographicCoordinateSystem __RPC_FAR *gcs)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      19);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrInterfacePointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                           (unsigned char __RPC_FAR *)gcs,
                                           (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[366] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrInterfacePointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                         (unsigned char __RPC_FAR *)gcs,
                                         (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[366] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[192] );
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IProjectedCoordinateSystem_put_GeographicCoordinateSystem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    IGeographicCoordinateSystem __RPC_FAR *gcs;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    gcs = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[192] );
        
        NdrInterfacePointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&gcs,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[366],
                                       (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IProjectedCoordinateSystem *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> put_GeographicCoordinateSystem((IProjectedCoordinateSystem *) ((CStdStubBuffer *)This)->pvServerObject,gcs);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrInterfacePointerFree( &_StubMsg,
                                 (unsigned char __RPC_FAR *)gcs,
                                 &__MIDL_TypeFormatString.Format[366] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [propget] */ HRESULT STDMETHODCALLTYPE IProjectedCoordinateSystem_get_LinearUnit_Proxy( 
    IProjectedCoordinateSystem __RPC_FAR * This,
    /* [retval][out] */ ILinearUnit __RPC_FAR *__RPC_FAR *unit)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    *unit = 0;
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      20);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[86] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&unit,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[170],
                                  (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[170],
                         ( void __RPC_FAR * )unit);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IProjectedCoordinateSystem_get_LinearUnit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    ILinearUnit __RPC_FAR *_M41;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    ILinearUnit __RPC_FAR *__RPC_FAR *unit;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    unit = 0;
    RpcTryFinally
        {
        unit = &_M41;
        _M41 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IProjectedCoordinateSystem *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_LinearUnit((IProjectedCoordinateSystem *) ((CStdStubBuffer *)This)->pvServerObject,unit);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 0U + 4U;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR *)unit,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[170] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char __RPC_FAR *)unit,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[170] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)unit,
                        &__MIDL_TypeFormatString.Format[170] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [propput] */ HRESULT STDMETHODCALLTYPE IProjectedCoordinateSystem_put_LinearUnit_Proxy( 
    IProjectedCoordinateSystem __RPC_FAR * This,
    /* [in] */ ILinearUnit __RPC_FAR *unit)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      21);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrInterfacePointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                           (unsigned char __RPC_FAR *)unit,
                                           (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[174] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrInterfacePointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                         (unsigned char __RPC_FAR *)unit,
                                         (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[174] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[92] );
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IProjectedCoordinateSystem_put_LinearUnit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    ILinearUnit __RPC_FAR *unit;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    unit = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[92] );
        
        NdrInterfacePointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&unit,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[174],
                                       (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IProjectedCoordinateSystem *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> put_LinearUnit((IProjectedCoordinateSystem *) ((CStdStubBuffer *)This)->pvServerObject,unit);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrInterfacePointerFree( &_StubMsg,
                                 (unsigned char __RPC_FAR *)unit,
                                 &__MIDL_TypeFormatString.Format[174] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [propget] */ HRESULT STDMETHODCALLTYPE IProjectedCoordinateSystem_get_Projection_Proxy( 
    IProjectedCoordinateSystem __RPC_FAR * This,
    /* [retval][out] */ IProjection __RPC_FAR *__RPC_FAR *projection)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    *projection = 0;
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      22);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[236] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&projection,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[480],
                                  (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[480],
                         ( void __RPC_FAR * )projection);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IProjectedCoordinateSystem_get_Projection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    IProjection __RPC_FAR *_M42;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    IProjection __RPC_FAR *__RPC_FAR *projection;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    projection = 0;
    RpcTryFinally
        {
        projection = &_M42;
        _M42 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IProjectedCoordinateSystem *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_Projection((IProjectedCoordinateSystem *) ((CStdStubBuffer *)This)->pvServerObject,projection);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 0U + 4U;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR *)projection,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[480] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char __RPC_FAR *)projection,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[480] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)projection,
                        &__MIDL_TypeFormatString.Format[480] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [propput] */ HRESULT STDMETHODCALLTYPE IProjectedCoordinateSystem_put_Projection_Proxy( 
    IProjectedCoordinateSystem __RPC_FAR * This,
    /* [in] */ IProjection __RPC_FAR *projection)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      23);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrInterfacePointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                           (unsigned char __RPC_FAR *)projection,
                                           (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[484] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrInterfacePointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                         (unsigned char __RPC_FAR *)projection,
                                         (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[484] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[242] );
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IProjectedCoordinateSystem_put_Projection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    IProjection __RPC_FAR *projection;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    projection = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[242] );
        
        NdrInterfacePointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&projection,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[484],
                                       (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IProjectedCoordinateSystem *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> put_Projection((IProjectedCoordinateSystem *) ((CStdStubBuffer *)This)->pvServerObject,projection);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrInterfacePointerFree( &_StubMsg,
                                 (unsigned char __RPC_FAR *)projection,
                                 &__MIDL_TypeFormatString.Format[484] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [propget] */ HRESULT STDMETHODCALLTYPE IProjectedCoordinateSystem_get_ParameterInfo_Proxy( 
    IProjectedCoordinateSystem __RPC_FAR * This,
    /* [retval][out] */ IParameterInfo __RPC_FAR *__RPC_FAR *paramInfo)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    *paramInfo = 0;
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      24);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[198] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&paramInfo,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[384],
                                  (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[384],
                         ( void __RPC_FAR * )paramInfo);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IProjectedCoordinateSystem_get_ParameterInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    IParameterInfo __RPC_FAR *_M43;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    IParameterInfo __RPC_FAR *__RPC_FAR *paramInfo;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    paramInfo = 0;
    RpcTryFinally
        {
        paramInfo = &_M43;
        _M43 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IProjectedCoordinateSystem *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_ParameterInfo((IProjectedCoordinateSystem *) ((CStdStubBuffer *)This)->pvServerObject,paramInfo);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 0U + 4U;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR *)paramInfo,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[384] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char __RPC_FAR *)paramInfo,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[384] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)paramInfo,
                        &__MIDL_TypeFormatString.Format[384] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


HRESULT STDMETHODCALLTYPE IProjectedCoordinateSystem_Forward_Proxy( 
    IProjectedCoordinateSystem __RPC_FAR * This,
    /* [in] */ long count,
    /* [size_is][out][in] */ WKSPoint __RPC_FAR points[  ])
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      25);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 4U + 4U;
            _StubMsg.MaxCount = count;
            
            NdrConformantArrayBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                          (unsigned char __RPC_FAR *)points,
                                          (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[414] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            *(( long __RPC_FAR * )_StubMsg.Buffer)++ = count;
            
            _StubMsg.MaxCount = count;
            
            NdrConformantArrayMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                        (unsigned char __RPC_FAR *)points,
                                        (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[414] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[204] );
            
            NdrConformantArrayUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                          (unsigned char __RPC_FAR * __RPC_FAR *)&points,
                                          (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[414],
                                          (unsigned char)0 );
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _StubMsg.MaxCount = count;
        
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[414],
                         ( void __RPC_FAR * )points);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IProjectedCoordinateSystem_Forward_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    long count;
    WKSPoint ( __RPC_FAR *points )[  ];
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    points = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[204] );
        
        count = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        NdrConformantArrayUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR * __RPC_FAR *)&points,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[414],
                                      (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IProjectedCoordinateSystem *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> Forward(
           (IProjectedCoordinateSystem *) ((CStdStubBuffer *)This)->pvServerObject,
           count,
           *points);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U + 8U;
        _StubMsg.MaxCount = count;
        
        NdrConformantArrayBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR *)*points,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[414] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.MaxCount = count;
        
        NdrConformantArrayMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                    (unsigned char __RPC_FAR *)*points,
                                    (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[414] );
        
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


HRESULT STDMETHODCALLTYPE IProjectedCoordinateSystem_Inverse_Proxy( 
    IProjectedCoordinateSystem __RPC_FAR * This,
    /* [in] */ long count,
    /* [size_is][out][in] */ WKSPoint __RPC_FAR points[  ])
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      26);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 4U + 4U;
            _StubMsg.MaxCount = count;
            
            NdrConformantArrayBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                          (unsigned char __RPC_FAR *)points,
                                          (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[414] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            *(( long __RPC_FAR * )_StubMsg.Buffer)++ = count;
            
            _StubMsg.MaxCount = count;
            
            NdrConformantArrayMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                        (unsigned char __RPC_FAR *)points,
                                        (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[414] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[204] );
            
            NdrConformantArrayUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                          (unsigned char __RPC_FAR * __RPC_FAR *)&points,
                                          (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[414],
                                          (unsigned char)0 );
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _StubMsg.MaxCount = count;
        
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[414],
                         ( void __RPC_FAR * )points);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IProjectedCoordinateSystem_Inverse_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    long count;
    WKSPoint ( __RPC_FAR *points )[  ];
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    points = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[204] );
        
        count = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        NdrConformantArrayUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR * __RPC_FAR *)&points,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[414],
                                      (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IProjectedCoordinateSystem *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> Inverse(
           (IProjectedCoordinateSystem *) ((CStdStubBuffer *)This)->pvServerObject,
           count,
           *points);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U + 8U;
        _StubMsg.MaxCount = count;
        
        NdrConformantArrayBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR *)*points,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[414] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.MaxCount = count;
        
        NdrConformantArrayMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                    (unsigned char __RPC_FAR *)*points,
                                    (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[414] );
        
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

const CINTERFACE_PROXY_VTABLE(27) _IProjectedCoordinateSystemProxyVtbl = 
{
    &IID_IProjectedCoordinateSystem,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    ISpatialReferenceInfo_get_Name_Proxy ,
    ISpatialReferenceInfo_put_Name_Proxy ,
    ISpatialReferenceInfo_get_Authority_Proxy ,
    ISpatialReferenceInfo_put_Authority_Proxy ,
    ISpatialReferenceInfo_get_Code_Proxy ,
    ISpatialReferenceInfo_put_Code_Proxy ,
    ISpatialReferenceInfo_get_Alias_Proxy ,
    ISpatialReferenceInfo_put_Alias_Proxy ,
    ISpatialReferenceInfo_get_Abbreviation_Proxy ,
    ISpatialReferenceInfo_put_Abbreviation_Proxy ,
    ISpatialReferenceInfo_get_Remarks_Proxy ,
    ISpatialReferenceInfo_put_Remarks_Proxy ,
    ISpatialReferenceInfo_get_WellKnownText_Proxy ,
    IProjectedCoordinateSystem_get_Usage_Proxy ,
    IProjectedCoordinateSystem_put_Usage_Proxy ,
    IProjectedCoordinateSystem_get_GeographicCoordinateSystem_Proxy ,
    IProjectedCoordinateSystem_put_GeographicCoordinateSystem_Proxy ,
    IProjectedCoordinateSystem_get_LinearUnit_Proxy ,
    IProjectedCoordinateSystem_put_LinearUnit_Proxy ,
    IProjectedCoordinateSystem_get_Projection_Proxy ,
    IProjectedCoordinateSystem_put_Projection_Proxy ,
    IProjectedCoordinateSystem_get_ParameterInfo_Proxy ,
    IProjectedCoordinateSystem_Forward_Proxy ,
    IProjectedCoordinateSystem_Inverse_Proxy
};


static const PRPC_STUB_FUNCTION IProjectedCoordinateSystem_table[] =
{
    ISpatialReferenceInfo_get_Name_Stub,
    ISpatialReferenceInfo_put_Name_Stub,
    ISpatialReferenceInfo_get_Authority_Stub,
    ISpatialReferenceInfo_put_Authority_Stub,
    ISpatialReferenceInfo_get_Code_Stub,
    ISpatialReferenceInfo_put_Code_Stub,
    ISpatialReferenceInfo_get_Alias_Stub,
    ISpatialReferenceInfo_put_Alias_Stub,
    ISpatialReferenceInfo_get_Abbreviation_Stub,
    ISpatialReferenceInfo_put_Abbreviation_Stub,
    ISpatialReferenceInfo_get_Remarks_Stub,
    ISpatialReferenceInfo_put_Remarks_Stub,
    ISpatialReferenceInfo_get_WellKnownText_Stub,
    IProjectedCoordinateSystem_get_Usage_Stub,
    IProjectedCoordinateSystem_put_Usage_Stub,
    IProjectedCoordinateSystem_get_GeographicCoordinateSystem_Stub,
    IProjectedCoordinateSystem_put_GeographicCoordinateSystem_Stub,
    IProjectedCoordinateSystem_get_LinearUnit_Stub,
    IProjectedCoordinateSystem_put_LinearUnit_Stub,
    IProjectedCoordinateSystem_get_Projection_Stub,
    IProjectedCoordinateSystem_put_Projection_Stub,
    IProjectedCoordinateSystem_get_ParameterInfo_Stub,
    IProjectedCoordinateSystem_Forward_Stub,
    IProjectedCoordinateSystem_Inverse_Stub
};

const CInterfaceStubVtbl _IProjectedCoordinateSystemStubVtbl =
{
    &IID_IProjectedCoordinateSystem,
    0,
    27,
    &IProjectedCoordinateSystem_table[-3],
    CStdStubBuffer_METHODS
};


/* Object interface: ISpatialReferenceFactory, ver. 0.0,
   GUID={0x620600B1,0xFEA1,0x11d0,{0xB0,0x4B,0x00,0x80,0xC7,0xF7,0x94,0x81}} */


extern const MIDL_STUB_DESC Object_StubDesc;


#pragma code_seg(".orpc")

HRESULT STDMETHODCALLTYPE ISpatialReferenceFactory_CreateFromWKT_Proxy( 
    ISpatialReferenceFactory __RPC_FAR * This,
    /* [in] */ BSTR wktSpatialReference,
    /* [out] */ ISpatialReference __RPC_FAR *__RPC_FAR *sref)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    *sref = 0;
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      3);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 4U;
            NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR *)&wktSpatialReference,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[502] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                    (unsigned char __RPC_FAR *)&wktSpatialReference,
                                    (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[502] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[248] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&sref,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[512],
                                  (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[512],
                         ( void __RPC_FAR * )sref);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB ISpatialReferenceFactory_CreateFromWKT_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    ISpatialReference __RPC_FAR *_M46;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    void __RPC_FAR *_p_wktSpatialReference;
    ISpatialReference __RPC_FAR *__RPC_FAR *sref;
    BSTR wktSpatialReference;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    _p_wktSpatialReference = &wktSpatialReference;
    MIDL_memset(
               _p_wktSpatialReference,
               0,
               sizeof( BSTR  ));
    sref = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[248] );
        
        NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&_p_wktSpatialReference,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[502],
                                  (unsigned char)0 );
        
        sref = &_M46;
        _M46 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISpatialReferenceFactory *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> CreateFromWKT(
                 (ISpatialReferenceFactory *) ((CStdStubBuffer *)This)->pvServerObject,
                 wktSpatialReference,
                 sref);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 0U + 4U;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR *)sref,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[512] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char __RPC_FAR *)sref,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[512] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrUserMarshalFree( &_StubMsg,
                            (unsigned char __RPC_FAR *)&wktSpatialReference,
                            &__MIDL_TypeFormatString.Format[502] );
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)sref,
                        &__MIDL_TypeFormatString.Format[512] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

const CINTERFACE_PROXY_VTABLE(4) _ISpatialReferenceFactoryProxyVtbl = 
{
    &IID_ISpatialReferenceFactory,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    ISpatialReferenceFactory_CreateFromWKT_Proxy
};


static const PRPC_STUB_FUNCTION ISpatialReferenceFactory_table[] =
{
    ISpatialReferenceFactory_CreateFromWKT_Stub
};

const CInterfaceStubVtbl _ISpatialReferenceFactoryStubVtbl =
{
    &IID_ISpatialReferenceFactory,
    0,
    4,
    &ISpatialReferenceFactory_table[-3],
    CStdStubBuffer_METHODS
};


/* Object interface: ISpatialReferenceAuthorityFactory, ver. 0.0,
   GUID={0x30ae14f0,0xfe1f,0x11d0,{0xad,0x87,0x08,0x00,0x09,0xb6,0xf2,0x2b}} */


extern const MIDL_STUB_DESC Object_StubDesc;


#pragma code_seg(".orpc")

/* [propget] */ HRESULT STDMETHODCALLTYPE ISpatialReferenceAuthorityFactory_get_Authority_Proxy( 
    ISpatialReferenceAuthorityFactory __RPC_FAR * This,
    /* [out] */ BSTR __RPC_FAR *authority)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    MIDL_memset(
               authority,
               0,
               sizeof( BSTR  ));
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      3);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[258] );
            
            NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR * __RPC_FAR *)&authority,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[538],
                                      (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[534],
                         ( void __RPC_FAR * )authority);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB ISpatialReferenceAuthorityFactory_get_Authority_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    BSTR _M47;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    BSTR __RPC_FAR *authority;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    authority = 0;
    RpcTryFinally
        {
        authority = &_M47;
        MIDL_memset(
               authority,
               0,
               sizeof( BSTR  ));
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISpatialReferenceAuthorityFactory *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_Authority((ISpatialReferenceAuthorityFactory *) ((CStdStubBuffer *)This)->pvServerObject,authority);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U + 11U;
        NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR *)authority,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[538] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                (unsigned char __RPC_FAR *)authority,
                                (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[538] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)authority,
                        &__MIDL_TypeFormatString.Format[534] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


HRESULT STDMETHODCALLTYPE ISpatialReferenceAuthorityFactory_CreateProjectedCoordinateSystem_Proxy( 
    ISpatialReferenceAuthorityFactory __RPC_FAR * This,
    /* [in] */ long code,
    /* [out] */ IProjectedCoordinateSystem __RPC_FAR *__RPC_FAR *pcs)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    *pcs = 0;
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      4);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 4U;
            NdrProxyGetBuffer(This, &_StubMsg);
            *(( long __RPC_FAR * )_StubMsg.Buffer)++ = code;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[264] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&pcs,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[548],
                                  (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[548],
                         ( void __RPC_FAR * )pcs);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB ISpatialReferenceAuthorityFactory_CreateProjectedCoordinateSystem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    IProjectedCoordinateSystem __RPC_FAR *_M48;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    long code;
    IProjectedCoordinateSystem __RPC_FAR *__RPC_FAR *pcs;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    pcs = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[264] );
        
        code = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        pcs = &_M48;
        _M48 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISpatialReferenceAuthorityFactory *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> CreateProjectedCoordinateSystem(
                                   (ISpatialReferenceAuthorityFactory *) ((CStdStubBuffer *)This)->pvServerObject,
                                   code,
                                   pcs);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 0U + 4U;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR *)pcs,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[548] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char __RPC_FAR *)pcs,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[548] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)pcs,
                        &__MIDL_TypeFormatString.Format[548] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


HRESULT STDMETHODCALLTYPE ISpatialReferenceAuthorityFactory_CreateGeographicCoordinateSystem_Proxy( 
    ISpatialReferenceAuthorityFactory __RPC_FAR * This,
    /* [in] */ long code,
    /* [out] */ IGeographicCoordinateSystem __RPC_FAR *__RPC_FAR *gcs)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    *gcs = 0;
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      5);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 4U;
            NdrProxyGetBuffer(This, &_StubMsg);
            *(( long __RPC_FAR * )_StubMsg.Buffer)++ = code;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[272] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&gcs,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[362],
                                  (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[362],
                         ( void __RPC_FAR * )gcs);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB ISpatialReferenceAuthorityFactory_CreateGeographicCoordinateSystem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    IGeographicCoordinateSystem __RPC_FAR *_M49;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    long code;
    IGeographicCoordinateSystem __RPC_FAR *__RPC_FAR *gcs;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    gcs = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[272] );
        
        code = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        gcs = &_M49;
        _M49 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISpatialReferenceAuthorityFactory *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> CreateGeographicCoordinateSystem(
                                    (ISpatialReferenceAuthorityFactory *) ((CStdStubBuffer *)This)->pvServerObject,
                                    code,
                                    gcs);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 0U + 4U;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR *)gcs,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[362] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char __RPC_FAR *)gcs,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[362] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)gcs,
                        &__MIDL_TypeFormatString.Format[362] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


HRESULT STDMETHODCALLTYPE ISpatialReferenceAuthorityFactory_CreateProjection_Proxy( 
    ISpatialReferenceAuthorityFactory __RPC_FAR * This,
    /* [in] */ long code,
    /* [out] */ IProjection __RPC_FAR *__RPC_FAR *projection)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    *projection = 0;
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      6);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 4U;
            NdrProxyGetBuffer(This, &_StubMsg);
            *(( long __RPC_FAR * )_StubMsg.Buffer)++ = code;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[280] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&projection,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[480],
                                  (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[480],
                         ( void __RPC_FAR * )projection);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB ISpatialReferenceAuthorityFactory_CreateProjection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    IProjection __RPC_FAR *_M50;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    long code;
    IProjection __RPC_FAR *__RPC_FAR *projection;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    projection = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[280] );
        
        code = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        projection = &_M50;
        _M50 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISpatialReferenceAuthorityFactory *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> CreateProjection(
                    (ISpatialReferenceAuthorityFactory *) ((CStdStubBuffer *)This)->pvServerObject,
                    code,
                    projection);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 0U + 4U;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR *)projection,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[480] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char __RPC_FAR *)projection,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[480] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)projection,
                        &__MIDL_TypeFormatString.Format[480] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


HRESULT STDMETHODCALLTYPE ISpatialReferenceAuthorityFactory_CreateGeographicTransform_Proxy( 
    ISpatialReferenceAuthorityFactory __RPC_FAR * This,
    /* [in] */ long code,
    /* [out] */ IGeographicTransform __RPC_FAR *__RPC_FAR *gt)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    *gt = 0;
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      7);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 4U;
            NdrProxyGetBuffer(This, &_StubMsg);
            *(( long __RPC_FAR * )_StubMsg.Buffer)++ = code;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[288] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&gt,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[570],
                                  (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[570],
                         ( void __RPC_FAR * )gt);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB ISpatialReferenceAuthorityFactory_CreateGeographicTransform_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    IGeographicTransform __RPC_FAR *_M51;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    long code;
    IGeographicTransform __RPC_FAR *__RPC_FAR *gt;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    gt = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[288] );
        
        code = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        gt = &_M51;
        _M51 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISpatialReferenceAuthorityFactory *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> CreateGeographicTransform(
                             (ISpatialReferenceAuthorityFactory *) ((CStdStubBuffer *)This)->pvServerObject,
                             code,
                             gt);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 0U + 4U;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR *)gt,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[570] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char __RPC_FAR *)gt,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[570] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)gt,
                        &__MIDL_TypeFormatString.Format[570] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


HRESULT STDMETHODCALLTYPE ISpatialReferenceAuthorityFactory_CreateHorizontalDatum_Proxy( 
    ISpatialReferenceAuthorityFactory __RPC_FAR * This,
    /* [in] */ long code,
    /* [out] */ IHorizontalDatum __RPC_FAR *__RPC_FAR *datum)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    *datum = 0;
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      8);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 4U;
            NdrProxyGetBuffer(This, &_StubMsg);
            *(( long __RPC_FAR * )_StubMsg.Buffer)++ = code;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[296] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&datum,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[260],
                                  (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[260],
                         ( void __RPC_FAR * )datum);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB ISpatialReferenceAuthorityFactory_CreateHorizontalDatum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    IHorizontalDatum __RPC_FAR *_M52;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    long code;
    IHorizontalDatum __RPC_FAR *__RPC_FAR *datum;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    datum = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[296] );
        
        code = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        datum = &_M52;
        _M52 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISpatialReferenceAuthorityFactory *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> CreateHorizontalDatum(
                         (ISpatialReferenceAuthorityFactory *) ((CStdStubBuffer *)This)->pvServerObject,
                         code,
                         datum);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 0U + 4U;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR *)datum,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[260] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char __RPC_FAR *)datum,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[260] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)datum,
                        &__MIDL_TypeFormatString.Format[260] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


HRESULT STDMETHODCALLTYPE ISpatialReferenceAuthorityFactory_CreateEllipsoid_Proxy( 
    ISpatialReferenceAuthorityFactory __RPC_FAR * This,
    /* [in] */ long code,
    /* [out] */ IEllipsoid __RPC_FAR *__RPC_FAR *ellipsoid)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    *ellipsoid = 0;
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      9);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 4U;
            NdrProxyGetBuffer(This, &_StubMsg);
            *(( long __RPC_FAR * )_StubMsg.Buffer)++ = code;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[304] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&ellipsoid,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[192],
                                  (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[192],
                         ( void __RPC_FAR * )ellipsoid);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB ISpatialReferenceAuthorityFactory_CreateEllipsoid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    IEllipsoid __RPC_FAR *_M53;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    long code;
    IEllipsoid __RPC_FAR *__RPC_FAR *ellipsoid;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ellipsoid = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[304] );
        
        code = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        ellipsoid = &_M53;
        _M53 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISpatialReferenceAuthorityFactory *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> CreateEllipsoid(
                   (ISpatialReferenceAuthorityFactory *) ((CStdStubBuffer *)This)->pvServerObject,
                   code,
                   ellipsoid);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 0U + 4U;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR *)ellipsoid,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[192] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char __RPC_FAR *)ellipsoid,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[192] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)ellipsoid,
                        &__MIDL_TypeFormatString.Format[192] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


HRESULT STDMETHODCALLTYPE ISpatialReferenceAuthorityFactory_CreatePrimeMeridian_Proxy( 
    ISpatialReferenceAuthorityFactory __RPC_FAR * This,
    /* [in] */ long code,
    /* [out] */ IPrimeMeridian __RPC_FAR *__RPC_FAR *prmMerid)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    *prmMerid = 0;
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      10);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 4U;
            NdrProxyGetBuffer(This, &_StubMsg);
            *(( long __RPC_FAR * )_StubMsg.Buffer)++ = code;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[312] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&prmMerid,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[282],
                                  (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[282],
                         ( void __RPC_FAR * )prmMerid);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB ISpatialReferenceAuthorityFactory_CreatePrimeMeridian_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    IPrimeMeridian __RPC_FAR *_M54;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    long code;
    IPrimeMeridian __RPC_FAR *__RPC_FAR *prmMerid;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    prmMerid = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[312] );
        
        code = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        prmMerid = &_M54;
        _M54 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISpatialReferenceAuthorityFactory *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> CreatePrimeMeridian(
                       (ISpatialReferenceAuthorityFactory *) ((CStdStubBuffer *)This)->pvServerObject,
                       code,
                       prmMerid);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 0U + 4U;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR *)prmMerid,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[282] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char __RPC_FAR *)prmMerid,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[282] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)prmMerid,
                        &__MIDL_TypeFormatString.Format[282] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


HRESULT STDMETHODCALLTYPE ISpatialReferenceAuthorityFactory_CreateLinearUnit_Proxy( 
    ISpatialReferenceAuthorityFactory __RPC_FAR * This,
    /* [in] */ long code,
    /* [out] */ ILinearUnit __RPC_FAR *__RPC_FAR *unit)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    *unit = 0;
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      11);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 4U;
            NdrProxyGetBuffer(This, &_StubMsg);
            *(( long __RPC_FAR * )_StubMsg.Buffer)++ = code;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[320] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&unit,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[170],
                                  (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[170],
                         ( void __RPC_FAR * )unit);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB ISpatialReferenceAuthorityFactory_CreateLinearUnit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    ILinearUnit __RPC_FAR *_M55;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    long code;
    ILinearUnit __RPC_FAR *__RPC_FAR *unit;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    unit = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[320] );
        
        code = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        unit = &_M55;
        _M55 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISpatialReferenceAuthorityFactory *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> CreateLinearUnit(
                    (ISpatialReferenceAuthorityFactory *) ((CStdStubBuffer *)This)->pvServerObject,
                    code,
                    unit);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 0U + 4U;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR *)unit,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[170] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char __RPC_FAR *)unit,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[170] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)unit,
                        &__MIDL_TypeFormatString.Format[170] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


HRESULT STDMETHODCALLTYPE ISpatialReferenceAuthorityFactory_CreateAngularUnit_Proxy( 
    ISpatialReferenceAuthorityFactory __RPC_FAR * This,
    /* [in] */ long code,
    /* [out] */ IAngularUnit __RPC_FAR *__RPC_FAR *unit)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    *unit = 0;
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      12);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 4U;
            NdrProxyGetBuffer(This, &_StubMsg);
            *(( long __RPC_FAR * )_StubMsg.Buffer)++ = code;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[328] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&unit,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[214],
                                  (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[214],
                         ( void __RPC_FAR * )unit);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB ISpatialReferenceAuthorityFactory_CreateAngularUnit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    IAngularUnit __RPC_FAR *_M56;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    long code;
    IAngularUnit __RPC_FAR *__RPC_FAR *unit;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    unit = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[328] );
        
        code = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        unit = &_M56;
        _M56 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISpatialReferenceAuthorityFactory *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> CreateAngularUnit(
                     (ISpatialReferenceAuthorityFactory *) ((CStdStubBuffer *)This)->pvServerObject,
                     code,
                     unit);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 0U + 4U;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR *)unit,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[214] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char __RPC_FAR *)unit,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[214] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)unit,
                        &__MIDL_TypeFormatString.Format[214] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

extern const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[1];

static const MIDL_STUB_DESC Object_StubDesc = 
    {
    0,
    NdrOleAllocate,
    NdrOleFree,
    0,
    0,
    0,
    0,
    0,
    __MIDL_TypeFormatString.Format,
    0, /* -error bounds_check flag */
    0x20000, /* Ndr library version */
    0,
    0x301004c, /* MIDL Version 3.1.76 */
    0,
    UserMarshalRoutines,
    0,  /* Reserved1 */
    0,  /* Reserved2 */
    0,  /* Reserved3 */
    0,  /* Reserved4 */
    0   /* Reserved5 */
    };

const CINTERFACE_PROXY_VTABLE(13) _ISpatialReferenceAuthorityFactoryProxyVtbl = 
{
    &IID_ISpatialReferenceAuthorityFactory,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    ISpatialReferenceAuthorityFactory_get_Authority_Proxy ,
    ISpatialReferenceAuthorityFactory_CreateProjectedCoordinateSystem_Proxy ,
    ISpatialReferenceAuthorityFactory_CreateGeographicCoordinateSystem_Proxy ,
    ISpatialReferenceAuthorityFactory_CreateProjection_Proxy ,
    ISpatialReferenceAuthorityFactory_CreateGeographicTransform_Proxy ,
    ISpatialReferenceAuthorityFactory_CreateHorizontalDatum_Proxy ,
    ISpatialReferenceAuthorityFactory_CreateEllipsoid_Proxy ,
    ISpatialReferenceAuthorityFactory_CreatePrimeMeridian_Proxy ,
    ISpatialReferenceAuthorityFactory_CreateLinearUnit_Proxy ,
    ISpatialReferenceAuthorityFactory_CreateAngularUnit_Proxy
};


static const PRPC_STUB_FUNCTION ISpatialReferenceAuthorityFactory_table[] =
{
    ISpatialReferenceAuthorityFactory_get_Authority_Stub,
    ISpatialReferenceAuthorityFactory_CreateProjectedCoordinateSystem_Stub,
    ISpatialReferenceAuthorityFactory_CreateGeographicCoordinateSystem_Stub,
    ISpatialReferenceAuthorityFactory_CreateProjection_Stub,
    ISpatialReferenceAuthorityFactory_CreateGeographicTransform_Stub,
    ISpatialReferenceAuthorityFactory_CreateHorizontalDatum_Stub,
    ISpatialReferenceAuthorityFactory_CreateEllipsoid_Stub,
    ISpatialReferenceAuthorityFactory_CreatePrimeMeridian_Stub,
    ISpatialReferenceAuthorityFactory_CreateLinearUnit_Stub,
    ISpatialReferenceAuthorityFactory_CreateAngularUnit_Stub
};

const CInterfaceStubVtbl _ISpatialReferenceAuthorityFactoryStubVtbl =
{
    &IID_ISpatialReferenceAuthorityFactory,
    0,
    13,
    &ISpatialReferenceAuthorityFactory_table[-3],
    CStdStubBuffer_METHODS
};

#pragma data_seg(".rdata")

static const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[1] = 
        {
            
            {
            BSTR_UserSize
            ,BSTR_UserMarshal
            ,BSTR_UserUnmarshal
            ,BSTR_UserFree
            }

        };


#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

#if !(TARGET_IS_NT40_OR_LATER)
#error You need a Windows NT 4.0 or later to run this stub because it uses these features:
#error   [wire_marshal] or [user_marshal] attribute.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will die there with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString =
    {
        0,
        {
			
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/*  2 */	NdrFcShort( 0x0 ),	/* Type Offset=0 */
/*  4 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/*  6 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/*  8 */	NdrFcShort( 0x2a ),	/* Type Offset=42 */
/* 10 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 12 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 14 */	NdrFcShort( 0x34 ),	/* Type Offset=52 */
/* 16 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 18 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 20 */	NdrFcShort( 0x42 ),	/* Type Offset=66 */
/* 22 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 24 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 26 */	NdrFcShort( 0x4c ),	/* Type Offset=76 */
/* 28 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 30 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 32 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 34 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 36 */	NdrFcShort( 0x50 ),	/* Type Offset=80 */
/* 38 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 40 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 42 */	NdrFcShort( 0x5e ),	/* Type Offset=94 */
/* 44 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 46 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 48 */	NdrFcShort( 0x68 ),	/* Type Offset=104 */
/* 50 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 52 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 54 */	NdrFcShort( 0x76 ),	/* Type Offset=118 */
/* 56 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 58 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 60 */	NdrFcShort( 0x80 ),	/* Type Offset=128 */
/* 62 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 64 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 66 */	NdrFcShort( 0x8e ),	/* Type Offset=142 */
/* 68 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 70 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 72 */	NdrFcShort( 0x98 ),	/* Type Offset=152 */
/* 74 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 76 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 78 */	NdrFcShort( 0xa6 ),	/* Type Offset=166 */
/* 80 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 82 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0xc,		/* FC_DOUBLE */
/* 84 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 86 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 88 */	NdrFcShort( 0xaa ),	/* Type Offset=170 */
/* 90 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 92 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 94 */	NdrFcShort( 0xae ),	/* Type Offset=174 */
/* 96 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 98 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 100 */	NdrFcShort( 0xc0 ),	/* Type Offset=192 */
/* 102 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 104 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 106 */	NdrFcShort( 0xc4 ),	/* Type Offset=196 */
/* 108 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 110 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 112 */	NdrFcShort( 0xd6 ),	/* Type Offset=214 */
/* 114 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 116 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 118 */	NdrFcShort( 0xda ),	/* Type Offset=218 */
/* 120 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 122 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 124 */	NdrFcShort( 0xec ),	/* Type Offset=236 */
/* 126 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 128 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 130 */	NdrFcShort( 0xfa ),	/* Type Offset=250 */
/* 132 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 134 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 136 */	NdrFcShort( 0x104 ),	/* Type Offset=260 */
/* 138 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 140 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 142 */	NdrFcShort( 0x108 ),	/* Type Offset=264 */
/* 144 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 146 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 148 */	NdrFcShort( 0x11a ),	/* Type Offset=282 */
/* 150 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 152 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 154 */	NdrFcShort( 0x11e ),	/* Type Offset=286 */
/* 156 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 158 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 160 */	NdrFcShort( 0x130 ),	/* Type Offset=304 */
/* 162 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 164 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 166 */	NdrFcShort( 0x142 ),	/* Type Offset=322 */
/* 168 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 170 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 172 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 174 */	NdrFcShort( 0x158 ),	/* Type Offset=344 */
/* 176 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 178 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 180 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 182 */	NdrFcShort( 0x158 ),	/* Type Offset=344 */
/* 184 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 186 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 188 */	NdrFcShort( 0x16a ),	/* Type Offset=362 */
/* 190 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 192 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 194 */	NdrFcShort( 0x16e ),	/* Type Offset=366 */
/* 196 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 198 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 200 */	NdrFcShort( 0x180 ),	/* Type Offset=384 */
/* 202 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 204 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 206 */	
			0x50,		/* FC_IN_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 208 */	NdrFcShort( 0x19e ),	/* Type Offset=414 */
/* 210 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 212 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 214 */	NdrFcShort( 0x1ac ),	/* Type Offset=428 */
/* 216 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 218 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 220 */	NdrFcShort( 0x1ba ),	/* Type Offset=442 */
/* 222 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 224 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 226 */	NdrFcShort( 0x1c8 ),	/* Type Offset=456 */
/* 228 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 230 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 232 */	NdrFcShort( 0x1d6 ),	/* Type Offset=470 */
/* 234 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 236 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 238 */	NdrFcShort( 0x1e0 ),	/* Type Offset=480 */
/* 240 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 242 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 244 */	NdrFcShort( 0x1e4 ),	/* Type Offset=484 */
/* 246 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 248 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 250 */	NdrFcShort( 0x1f6 ),	/* Type Offset=502 */
/* 252 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 254 */	NdrFcShort( 0x200 ),	/* Type Offset=512 */
/* 256 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 258 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 260 */	NdrFcShort( 0x216 ),	/* Type Offset=534 */
/* 262 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 264 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 266 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 268 */	NdrFcShort( 0x224 ),	/* Type Offset=548 */
/* 270 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 272 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 274 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 276 */	NdrFcShort( 0x16a ),	/* Type Offset=362 */
/* 278 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 280 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 282 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 284 */	NdrFcShort( 0x1e0 ),	/* Type Offset=480 */
/* 286 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 288 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 290 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 292 */	NdrFcShort( 0x23a ),	/* Type Offset=570 */
/* 294 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 296 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 298 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 300 */	NdrFcShort( 0x104 ),	/* Type Offset=260 */
/* 302 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 304 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 306 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 308 */	NdrFcShort( 0xc0 ),	/* Type Offset=192 */
/* 310 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 312 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 314 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 316 */	NdrFcShort( 0x11a ),	/* Type Offset=282 */
/* 318 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 320 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 322 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 324 */	NdrFcShort( 0xaa ),	/* Type Offset=170 */
/* 326 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 328 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 330 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 332 */	NdrFcShort( 0xd6 ),	/* Type Offset=214 */
/* 334 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */

			0x0
        }
    };

static const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString =
    {
        0,
        {
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/*  2 */	NdrFcShort( 0x1a ),	/* Offset= 26 (28) */
/*  4 */	
			0x13, 0x0,	/* FC_OP */
/*  6 */	NdrFcShort( 0xc ),	/* Offset= 12 (18) */
/*  8 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 10 */	NdrFcShort( 0x2 ),	/* 2 */
/* 12 */	0x9,		/* 9 */
			0x0,		/*  */
/* 14 */	NdrFcShort( 0xfffffffc ),	/* -4 */
/* 16 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 18 */	
			0x17,		/* FC_CSTRUCT */
			0x3,		/* 3 */
/* 20 */	NdrFcShort( 0x8 ),	/* 8 */
/* 22 */	NdrFcShort( 0xfffffff2 ),	/* Offset= -14 (8) */
/* 24 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 26 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 28 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 30 */	NdrFcShort( 0x0 ),	/* 0 */
/* 32 */	NdrFcShort( 0x4 ),	/* 4 */
/* 34 */	NdrFcShort( 0x0 ),	/* 0 */
/* 36 */	NdrFcShort( 0xffffffe0 ),	/* Offset= -32 (4) */
/* 38 */	
			0x12, 0x0,	/* FC_UP */
/* 40 */	NdrFcShort( 0xffffffea ),	/* Offset= -22 (18) */
/* 42 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 44 */	NdrFcShort( 0x0 ),	/* 0 */
/* 46 */	NdrFcShort( 0x4 ),	/* 4 */
/* 48 */	NdrFcShort( 0x0 ),	/* 0 */
/* 50 */	NdrFcShort( 0xfffffff4 ),	/* Offset= -12 (38) */
/* 52 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 54 */	NdrFcShort( 0x2 ),	/* Offset= 2 (56) */
/* 56 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 58 */	NdrFcShort( 0x0 ),	/* 0 */
/* 60 */	NdrFcShort( 0x4 ),	/* 4 */
/* 62 */	NdrFcShort( 0x0 ),	/* 0 */
/* 64 */	NdrFcShort( 0xffffffc4 ),	/* Offset= -60 (4) */
/* 66 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 68 */	NdrFcShort( 0x0 ),	/* 0 */
/* 70 */	NdrFcShort( 0x4 ),	/* 4 */
/* 72 */	NdrFcShort( 0x0 ),	/* 0 */
/* 74 */	NdrFcShort( 0xffffffdc ),	/* Offset= -36 (38) */
/* 76 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 78 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 80 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 82 */	NdrFcShort( 0x2 ),	/* Offset= 2 (84) */
/* 84 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 86 */	NdrFcShort( 0x0 ),	/* 0 */
/* 88 */	NdrFcShort( 0x4 ),	/* 4 */
/* 90 */	NdrFcShort( 0x0 ),	/* 0 */
/* 92 */	NdrFcShort( 0xffffffa8 ),	/* Offset= -88 (4) */
/* 94 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 96 */	NdrFcShort( 0x0 ),	/* 0 */
/* 98 */	NdrFcShort( 0x4 ),	/* 4 */
/* 100 */	NdrFcShort( 0x0 ),	/* 0 */
/* 102 */	NdrFcShort( 0xffffffc0 ),	/* Offset= -64 (38) */
/* 104 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 106 */	NdrFcShort( 0x2 ),	/* Offset= 2 (108) */
/* 108 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 110 */	NdrFcShort( 0x0 ),	/* 0 */
/* 112 */	NdrFcShort( 0x4 ),	/* 4 */
/* 114 */	NdrFcShort( 0x0 ),	/* 0 */
/* 116 */	NdrFcShort( 0xffffff90 ),	/* Offset= -112 (4) */
/* 118 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 120 */	NdrFcShort( 0x0 ),	/* 0 */
/* 122 */	NdrFcShort( 0x4 ),	/* 4 */
/* 124 */	NdrFcShort( 0x0 ),	/* 0 */
/* 126 */	NdrFcShort( 0xffffffa8 ),	/* Offset= -88 (38) */
/* 128 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 130 */	NdrFcShort( 0x2 ),	/* Offset= 2 (132) */
/* 132 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 134 */	NdrFcShort( 0x0 ),	/* 0 */
/* 136 */	NdrFcShort( 0x4 ),	/* 4 */
/* 138 */	NdrFcShort( 0x0 ),	/* 0 */
/* 140 */	NdrFcShort( 0xffffff78 ),	/* Offset= -136 (4) */
/* 142 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 144 */	NdrFcShort( 0x0 ),	/* 0 */
/* 146 */	NdrFcShort( 0x4 ),	/* 4 */
/* 148 */	NdrFcShort( 0x0 ),	/* 0 */
/* 150 */	NdrFcShort( 0xffffff90 ),	/* Offset= -112 (38) */
/* 152 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 154 */	NdrFcShort( 0x2 ),	/* Offset= 2 (156) */
/* 156 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 158 */	NdrFcShort( 0x0 ),	/* 0 */
/* 160 */	NdrFcShort( 0x4 ),	/* 4 */
/* 162 */	NdrFcShort( 0x0 ),	/* 0 */
/* 164 */	NdrFcShort( 0xffffff60 ),	/* Offset= -160 (4) */
/* 166 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 168 */	0xc,		/* FC_DOUBLE */
			0x5c,		/* FC_PAD */
/* 170 */	
			0x11, 0x14,	/* FC_RP [alloced_on_stack] */
/* 172 */	NdrFcShort( 0x2 ),	/* Offset= 2 (174) */
/* 174 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 176 */	NdrFcLong( 0x80855df0 ),	/* -2138743312 */
/* 180 */	NdrFcShort( 0xfffffe1d ),	/* -483 */
/* 182 */	NdrFcShort( 0x11d0 ),	/* 4560 */
/* 184 */	0xad,		/* 173 */
			0x87,		/* 135 */
/* 186 */	0x8,		/* 8 */
			0x0,		/* 0 */
/* 188 */	0x9,		/* 9 */
			0xb6,		/* 182 */
/* 190 */	0xf2,		/* 242 */
			0x2b,		/* 43 */
/* 192 */	
			0x11, 0x14,	/* FC_RP [alloced_on_stack] */
/* 194 */	NdrFcShort( 0x2 ),	/* Offset= 2 (196) */
/* 196 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 198 */	NdrFcLong( 0xce7266c0 ),	/* -831363392 */
/* 202 */	NdrFcShort( 0xfffffe1d ),	/* -483 */
/* 204 */	NdrFcShort( 0x11d0 ),	/* 4560 */
/* 206 */	0xad,		/* 173 */
			0x87,		/* 135 */
/* 208 */	0x8,		/* 8 */
			0x0,		/* 0 */
/* 210 */	0x9,		/* 9 */
			0xb6,		/* 182 */
/* 212 */	0xf2,		/* 242 */
			0x2b,		/* 43 */
/* 214 */	
			0x11, 0x14,	/* FC_RP [alloced_on_stack] */
/* 216 */	NdrFcShort( 0x2 ),	/* Offset= 2 (218) */
/* 218 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 220 */	NdrFcLong( 0x4febc550 ),	/* 1340851536 */
/* 224 */	NdrFcShort( 0xfffffe1d ),	/* -483 */
/* 226 */	NdrFcShort( 0x11d0 ),	/* 4560 */
/* 228 */	0xad,		/* 173 */
			0x87,		/* 135 */
/* 230 */	0x8,		/* 8 */
			0x0,		/* 0 */
/* 232 */	0x9,		/* 9 */
			0xb6,		/* 182 */
/* 234 */	0xf2,		/* 242 */
			0x2b,		/* 43 */
/* 236 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 238 */	NdrFcShort( 0x2 ),	/* Offset= 2 (240) */
/* 240 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 242 */	NdrFcShort( 0x0 ),	/* 0 */
/* 244 */	NdrFcShort( 0x4 ),	/* 4 */
/* 246 */	NdrFcShort( 0x0 ),	/* 0 */
/* 248 */	NdrFcShort( 0xffffff0c ),	/* Offset= -244 (4) */
/* 250 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 252 */	NdrFcShort( 0x0 ),	/* 0 */
/* 254 */	NdrFcShort( 0x4 ),	/* 4 */
/* 256 */	NdrFcShort( 0x0 ),	/* 0 */
/* 258 */	NdrFcShort( 0xffffff24 ),	/* Offset= -220 (38) */
/* 260 */	
			0x11, 0x14,	/* FC_RP [alloced_on_stack] */
/* 262 */	NdrFcShort( 0x2 ),	/* Offset= 2 (264) */
/* 264 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 266 */	NdrFcLong( 0xf699c510 ),	/* -157694704 */
/* 270 */	NdrFcShort( 0xfffffe1d ),	/* -483 */
/* 272 */	NdrFcShort( 0x11d0 ),	/* 4560 */
/* 274 */	0xad,		/* 173 */
			0x87,		/* 135 */
/* 276 */	0x8,		/* 8 */
			0x0,		/* 0 */
/* 278 */	0x9,		/* 9 */
			0xb6,		/* 182 */
/* 280 */	0xf2,		/* 242 */
			0x2b,		/* 43 */
/* 282 */	
			0x11, 0x14,	/* FC_RP [alloced_on_stack] */
/* 284 */	NdrFcShort( 0x2 ),	/* Offset= 2 (286) */
/* 286 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 288 */	NdrFcLong( 0x15129940 ),	/* 353540416 */
/* 292 */	NdrFcShort( 0xfffffe1e ),	/* -482 */
/* 294 */	NdrFcShort( 0x11d0 ),	/* 4560 */
/* 296 */	0xad,		/* 173 */
			0x87,		/* 135 */
/* 298 */	0x8,		/* 8 */
			0x0,		/* 0 */
/* 300 */	0x9,		/* 9 */
			0xb6,		/* 182 */
/* 302 */	0xf2,		/* 242 */
			0x2b,		/* 43 */
/* 304 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 306 */	NdrFcLong( 0x221733b0 ),	/* 571945904 */
/* 310 */	NdrFcShort( 0xfffffe1d ),	/* -483 */
/* 312 */	NdrFcShort( 0x11d0 ),	/* 4560 */
/* 314 */	0xad,		/* 173 */
			0x87,		/* 135 */
/* 316 */	0x8,		/* 8 */
			0x0,		/* 0 */
/* 318 */	0x9,		/* 9 */
			0xb6,		/* 182 */
/* 320 */	0xf2,		/* 242 */
			0x2b,		/* 43 */
/* 322 */	
			0x11, 0x14,	/* FC_RP [alloced_on_stack] */
/* 324 */	NdrFcShort( 0xffffffec ),	/* Offset= -20 (304) */
/* 326 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 328 */	NdrFcLong( 0x9a5e32d0 ),	/* -1705102640 */
/* 332 */	NdrFcShort( 0xfffffe1f ),	/* -481 */
/* 334 */	NdrFcShort( 0x11d0 ),	/* 4560 */
/* 336 */	0xad,		/* 173 */
			0x87,		/* 135 */
/* 338 */	0x8,		/* 8 */
			0x0,		/* 0 */
/* 340 */	0x9,		/* 9 */
			0xb6,		/* 182 */
/* 342 */	0xf2,		/* 242 */
			0x2b,		/* 43 */
/* 344 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 346 */	NdrFcShort( 0x0 ),	/* 0 */
/* 348 */	0x28,		/* 40 */
			0x0,		/*  */
#ifndef _ALPHA_
/* 350 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 352 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 356 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 358 */	NdrFcShort( 0xffffffe0 ),	/* Offset= -32 (326) */
/* 360 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 362 */	
			0x11, 0x14,	/* FC_RP [alloced_on_stack] */
/* 364 */	NdrFcShort( 0x2 ),	/* Offset= 2 (366) */
/* 366 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 368 */	NdrFcLong( 0xa3fd5390 ),	/* -1543679088 */
/* 372 */	NdrFcShort( 0xfffffe1e ),	/* -482 */
/* 374 */	NdrFcShort( 0x11d0 ),	/* 4560 */
/* 376 */	0xad,		/* 173 */
			0x87,		/* 135 */
/* 378 */	0x8,		/* 8 */
			0x0,		/* 0 */
/* 380 */	0x9,		/* 9 */
			0xb6,		/* 182 */
/* 382 */	0xf2,		/* 242 */
			0x2b,		/* 43 */
/* 384 */	
			0x11, 0x14,	/* FC_RP [alloced_on_stack] */
/* 386 */	NdrFcShort( 0x2 ),	/* Offset= 2 (388) */
/* 388 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 390 */	NdrFcLong( 0x7309b460 ),	/* 1930015840 */
/* 394 */	NdrFcShort( 0xfffffe1f ),	/* -481 */
/* 396 */	NdrFcShort( 0x11d0 ),	/* 4560 */
/* 398 */	0xad,		/* 173 */
			0x87,		/* 135 */
/* 400 */	0x8,		/* 8 */
			0x0,		/* 0 */
/* 402 */	0x9,		/* 9 */
			0xb6,		/* 182 */
/* 404 */	0xf2,		/* 242 */
			0x2b,		/* 43 */
/* 406 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 408 */	NdrFcShort( 0x10 ),	/* 16 */
/* 410 */	0xc,		/* FC_DOUBLE */
			0xc,		/* FC_DOUBLE */
/* 412 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 414 */	
			0x1b,		/* FC_CARRAY */
			0x7,		/* 7 */
/* 416 */	NdrFcShort( 0x10 ),	/* 16 */
/* 418 */	0x28,		/* 40 */
			0x0,		/*  */
#ifndef _ALPHA_
/* 420 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 422 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 424 */	NdrFcShort( 0xffffffee ),	/* Offset= -18 (406) */
/* 426 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 428 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 430 */	NdrFcShort( 0x2 ),	/* Offset= 2 (432) */
/* 432 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 434 */	NdrFcShort( 0x0 ),	/* 0 */
/* 436 */	NdrFcShort( 0x4 ),	/* 4 */
/* 438 */	NdrFcShort( 0x0 ),	/* 0 */
/* 440 */	NdrFcShort( 0xfffffe4c ),	/* Offset= -436 (4) */
/* 442 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 444 */	NdrFcShort( 0x2 ),	/* Offset= 2 (446) */
/* 446 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 448 */	NdrFcShort( 0x0 ),	/* 0 */
/* 450 */	NdrFcShort( 0x4 ),	/* 4 */
/* 452 */	NdrFcShort( 0x0 ),	/* 0 */
/* 454 */	NdrFcShort( 0xfffffe3e ),	/* Offset= -450 (4) */
/* 456 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 458 */	NdrFcShort( 0x2 ),	/* Offset= 2 (460) */
/* 460 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 462 */	NdrFcShort( 0x0 ),	/* 0 */
/* 464 */	NdrFcShort( 0x4 ),	/* 4 */
/* 466 */	NdrFcShort( 0x0 ),	/* 0 */
/* 468 */	NdrFcShort( 0xfffffe30 ),	/* Offset= -464 (4) */
/* 470 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 472 */	NdrFcShort( 0x0 ),	/* 0 */
/* 474 */	NdrFcShort( 0x4 ),	/* 4 */
/* 476 */	NdrFcShort( 0x0 ),	/* 0 */
/* 478 */	NdrFcShort( 0xfffffe48 ),	/* Offset= -440 (38) */
/* 480 */	
			0x11, 0x14,	/* FC_RP [alloced_on_stack] */
/* 482 */	NdrFcShort( 0x2 ),	/* Offset= 2 (484) */
/* 484 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 486 */	NdrFcLong( 0x5002f420 ),	/* 1342370848 */
/* 490 */	NdrFcShort( 0xfffffe1f ),	/* -481 */
/* 492 */	NdrFcShort( 0x11d0 ),	/* 4560 */
/* 494 */	0xad,		/* 173 */
			0x87,		/* 135 */
/* 496 */	0x8,		/* 8 */
			0x0,		/* 0 */
/* 498 */	0x9,		/* 9 */
			0xb6,		/* 182 */
/* 500 */	0xf2,		/* 242 */
			0x2b,		/* 43 */
/* 502 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 504 */	NdrFcShort( 0x0 ),	/* 0 */
/* 506 */	NdrFcShort( 0x4 ),	/* 4 */
/* 508 */	NdrFcShort( 0x0 ),	/* 0 */
/* 510 */	NdrFcShort( 0xfffffe28 ),	/* Offset= -472 (38) */
/* 512 */	
			0x11, 0x14,	/* FC_RP [alloced_on_stack] */
/* 514 */	NdrFcShort( 0x2 ),	/* Offset= 2 (516) */
/* 516 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 518 */	NdrFcLong( 0x4c4c5c00 ),	/* 1280072704 */
/* 522 */	NdrFcShort( 0xfffffe1e ),	/* -482 */
/* 524 */	NdrFcShort( 0x11d0 ),	/* 4560 */
/* 526 */	0xad,		/* 173 */
			0x87,		/* 135 */
/* 528 */	0x8,		/* 8 */
			0x0,		/* 0 */
/* 530 */	0x9,		/* 9 */
			0xb6,		/* 182 */
/* 532 */	0xf2,		/* 242 */
			0x2b,		/* 43 */
/* 534 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 536 */	NdrFcShort( 0x2 ),	/* Offset= 2 (538) */
/* 538 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 540 */	NdrFcShort( 0x0 ),	/* 0 */
/* 542 */	NdrFcShort( 0x4 ),	/* 4 */
/* 544 */	NdrFcShort( 0x0 ),	/* 0 */
/* 546 */	NdrFcShort( 0xfffffde2 ),	/* Offset= -542 (4) */
/* 548 */	
			0x11, 0x14,	/* FC_RP [alloced_on_stack] */
/* 550 */	NdrFcShort( 0x2 ),	/* Offset= 2 (552) */
/* 552 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 554 */	NdrFcLong( 0x3dc39ff0 ),	/* 1036230640 */
/* 558 */	NdrFcShort( 0xfffffe1f ),	/* -481 */
/* 560 */	NdrFcShort( 0x11d0 ),	/* 4560 */
/* 562 */	0xad,		/* 173 */
			0x87,		/* 135 */
/* 564 */	0x8,		/* 8 */
			0x0,		/* 0 */
/* 566 */	0x9,		/* 9 */
			0xb6,		/* 182 */
/* 568 */	0xf2,		/* 242 */
			0x2b,		/* 43 */
/* 570 */	
			0x11, 0x14,	/* FC_RP [alloced_on_stack] */
/* 572 */	NdrFcShort( 0x2 ),	/* Offset= 2 (574) */
/* 574 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 576 */	NdrFcLong( 0x5eb513c0 ),	/* 1588925376 */
/* 580 */	NdrFcShort( 0xfffffe1f ),	/* -481 */
/* 582 */	NdrFcShort( 0x11d0 ),	/* 4560 */
/* 584 */	0xad,		/* 173 */
			0x87,		/* 135 */
/* 586 */	0x8,		/* 8 */
			0x0,		/* 0 */
/* 588 */	0x9,		/* 9 */
			0xb6,		/* 182 */
/* 590 */	0xf2,		/* 242 */
			0x2b,		/* 43 */

			0x0
        }
    };

const CInterfaceProxyVtbl * _SpatialReference_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_ISpatialReferenceProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IHorizontalDatumProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IProjectionProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IPrimeMeridianProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IAngularUnitProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IParameterInfoProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IGeographicCoordinateSystemProxyVtbl,
    ( CInterfaceProxyVtbl *) &_ISpatialReferenceInfoProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IUnitProxyVtbl,
    ( CInterfaceProxyVtbl *) &_ISpatialReferenceFactoryProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IGeographicTransformProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IEllipsoidProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IParameterProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IGeodeticSpatialReferenceProxyVtbl,
    ( CInterfaceProxyVtbl *) &_ISpatialReferenceAuthorityFactoryProxyVtbl,
    ( CInterfaceProxyVtbl *) &_ILinearUnitProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IProjectedCoordinateSystemProxyVtbl,
    0
};

const CInterfaceStubVtbl * _SpatialReference_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_ISpatialReferenceStubVtbl,
    ( CInterfaceStubVtbl *) &_IHorizontalDatumStubVtbl,
    ( CInterfaceStubVtbl *) &_IProjectionStubVtbl,
    ( CInterfaceStubVtbl *) &_IPrimeMeridianStubVtbl,
    ( CInterfaceStubVtbl *) &_IAngularUnitStubVtbl,
    ( CInterfaceStubVtbl *) &_IParameterInfoStubVtbl,
    ( CInterfaceStubVtbl *) &_IGeographicCoordinateSystemStubVtbl,
    ( CInterfaceStubVtbl *) &_ISpatialReferenceInfoStubVtbl,
    ( CInterfaceStubVtbl *) &_IUnitStubVtbl,
    ( CInterfaceStubVtbl *) &_ISpatialReferenceFactoryStubVtbl,
    ( CInterfaceStubVtbl *) &_IGeographicTransformStubVtbl,
    ( CInterfaceStubVtbl *) &_IEllipsoidStubVtbl,
    ( CInterfaceStubVtbl *) &_IParameterStubVtbl,
    ( CInterfaceStubVtbl *) &_IGeodeticSpatialReferenceStubVtbl,
    ( CInterfaceStubVtbl *) &_ISpatialReferenceAuthorityFactoryStubVtbl,
    ( CInterfaceStubVtbl *) &_ILinearUnitStubVtbl,
    ( CInterfaceStubVtbl *) &_IProjectedCoordinateSystemStubVtbl,
    0
};

PCInterfaceName const _SpatialReference_InterfaceNamesList[] = 
{
    "ISpatialReference",
    "IHorizontalDatum",
    "IProjection",
    "IPrimeMeridian",
    "IAngularUnit",
    "IParameterInfo",
    "IGeographicCoordinateSystem",
    "ISpatialReferenceInfo",
    "IUnit",
    "ISpatialReferenceFactory",
    "IGeographicTransform",
    "IEllipsoid",
    "IParameter",
    "IGeodeticSpatialReference",
    "ISpatialReferenceAuthorityFactory",
    "ILinearUnit",
    "IProjectedCoordinateSystem",
    0
};


#define _SpatialReference_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _SpatialReference, pIID, n)

int __stdcall _SpatialReference_IID_Lookup( const IID * pIID, int * pIndex )
{
    IID_BS_LOOKUP_SETUP

    IID_BS_LOOKUP_INITIAL_TEST( _SpatialReference, 17, 16 )
    IID_BS_LOOKUP_NEXT_TEST( _SpatialReference, 8 )
    IID_BS_LOOKUP_NEXT_TEST( _SpatialReference, 4 )
    IID_BS_LOOKUP_NEXT_TEST( _SpatialReference, 2 )
    IID_BS_LOOKUP_NEXT_TEST( _SpatialReference, 1 )
    IID_BS_LOOKUP_RETURN_RESULT( _SpatialReference, 17, *pIndex )
    
}

const ExtendedProxyFileInfo SpatialReference_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _SpatialReference_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _SpatialReference_StubVtblList,
    (const PCInterfaceName * ) & _SpatialReference_InterfaceNamesList,
    0, // no delegation
    & _SpatialReference_IID_Lookup, 
    17,
    1
};
