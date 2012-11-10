
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the proxy stub code */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Mon Feb 04 21:48:28 2002
 */
/* Compiler settings for SpatialReference.idl:
    Os, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#if !defined(_M_IA64) && !defined(_M_AMD64)

/* verify that the <rpcproxy.h> version is high enough to compile this file*/
#ifndef __REDQ_RPCPROXY_H_VERSION__
#define __REQUIRED_RPCPROXY_H_VERSION__ 440
#endif


#include "rpcproxy.h"
#ifndef __RPCPROXY_H_VERSION__
#error this stub requires an updated version of <rpcproxy.h>
#endif // __RPCPROXY_H_VERSION__


#include "SpatialReference.h"

#define TYPE_FORMAT_STRING_SIZE   561                               
#define PROC_FORMAT_STRING_SIZE   277                               
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   1            

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


static RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};


extern const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString;
extern const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO ISpatialReferenceInfo_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO ISpatialReferenceInfo_ProxyInfo;


/* [propget] */ HRESULT STDMETHODCALLTYPE ISpatialReferenceInfo_get_Name_Proxy( 
    ISpatialReferenceInfo * This,
    /* [retval][out] */ BSTR *name)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(name)
        {
        MIDL_memset(
               name,
               0,
               sizeof( BSTR  ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      3);
        
        
        
        if(!name)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[0] );
            
            NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char * *)&name,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[30],
                                      (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[2],
                         ( void * )name);
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
    BSTR *name;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( BSTR * )name = 0;
    RpcTryFinally
        {
        name = &_M0;
        MIDL_memset(
               name,
               0,
               sizeof( BSTR  ));
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISpatialReferenceInfo*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_Name((ISpatialReferenceInfo *) ((CStdStubBuffer *)This)->pvServerObject,name);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char *)name,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[30] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                (unsigned char *)name,
                                (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[30] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char *)name,
                        &__MIDL_TypeFormatString.Format[2] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [propput] */ HRESULT STDMETHODCALLTYPE ISpatialReferenceInfo_put_Name_Proxy( 
    ISpatialReferenceInfo * This,
    /* [in] */ BSTR name)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      4);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char *)&name,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[44] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                    (unsigned char *)&name,
                                    (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[44] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[6] );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
    void *_p_name;
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
                                  (unsigned char * *)&_p_name,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[44],
                                  (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISpatialReferenceInfo*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> put_Name((ISpatialReferenceInfo *) ((CStdStubBuffer *)This)->pvServerObject,name);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrUserMarshalFree( &_StubMsg,
                            (unsigned char *)&name,
                            &__MIDL_TypeFormatString.Format[44] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [propget] */ HRESULT STDMETHODCALLTYPE ISpatialReferenceInfo_get_Authority_Proxy( 
    ISpatialReferenceInfo * This,
    /* [retval][out] */ BSTR *name)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(name)
        {
        MIDL_memset(
               name,
               0,
               sizeof( BSTR  ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      5);
        
        
        
        if(!name)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[0] );
            
            NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char * *)&name,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[30],
                                      (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[2],
                         ( void * )name);
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
    BSTR *name;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( BSTR * )name = 0;
    RpcTryFinally
        {
        name = &_M1;
        MIDL_memset(
               name,
               0,
               sizeof( BSTR  ));
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISpatialReferenceInfo*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_Authority((ISpatialReferenceInfo *) ((CStdStubBuffer *)This)->pvServerObject,name);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char *)name,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[30] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                (unsigned char *)name,
                                (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[30] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char *)name,
                        &__MIDL_TypeFormatString.Format[2] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [propput] */ HRESULT STDMETHODCALLTYPE ISpatialReferenceInfo_put_Authority_Proxy( 
    ISpatialReferenceInfo * This,
    /* [in] */ BSTR name)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      6);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char *)&name,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[44] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                    (unsigned char *)&name,
                                    (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[44] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[6] );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
    void *_p_name;
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
                                  (unsigned char * *)&_p_name,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[44],
                                  (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISpatialReferenceInfo*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> put_Authority((ISpatialReferenceInfo *) ((CStdStubBuffer *)This)->pvServerObject,name);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrUserMarshalFree( &_StubMsg,
                            (unsigned char *)&name,
                            &__MIDL_TypeFormatString.Format[44] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [propget] */ HRESULT STDMETHODCALLTYPE ISpatialReferenceInfo_get_Code_Proxy( 
    ISpatialReferenceInfo * This,
    /* [retval][out] */ long *code)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      7);
        
        
        
        if(!code)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[12] );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            *code = *(( long * )_StubMsg.Buffer)++;
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[54],
                         ( void * )code);
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
    long _M2	=	0;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    long *code;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( long * )code = 0;
    RpcTryFinally
        {
        code = &_M2;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISpatialReferenceInfo*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_Code((ISpatialReferenceInfo *) ((CStdStubBuffer *)This)->pvServerObject,code);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 36;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( long * )_StubMsg.Buffer)++ = *code;
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [propput] */ HRESULT STDMETHODCALLTYPE ISpatialReferenceInfo_put_Code_Proxy( 
    ISpatialReferenceInfo * This,
    /* [in] */ long code)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      8);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 8;
            NdrProxyGetBuffer(This, &_StubMsg);
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            *(( long * )_StubMsg.Buffer)++ = code;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[18] );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
    code = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[18] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        
        if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
            {
            RpcRaiseException(RPC_X_BAD_STUB_DATA);
            }
        code = *(( long * )_StubMsg.Buffer)++;
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISpatialReferenceInfo*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> put_Code((ISpatialReferenceInfo *) ((CStdStubBuffer *)This)->pvServerObject,code);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [propget] */ HRESULT STDMETHODCALLTYPE ISpatialReferenceInfo_get_Alias_Proxy( 
    ISpatialReferenceInfo * This,
    /* [retval][out] */ BSTR *alias)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(alias)
        {
        MIDL_memset(
               alias,
               0,
               sizeof( BSTR  ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      9);
        
        
        
        if(!alias)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[0] );
            
            NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char * *)&alias,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[30],
                                      (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[2],
                         ( void * )alias);
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
    BSTR *alias;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( BSTR * )alias = 0;
    RpcTryFinally
        {
        alias = &_M3;
        MIDL_memset(
               alias,
               0,
               sizeof( BSTR  ));
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISpatialReferenceInfo*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_Alias((ISpatialReferenceInfo *) ((CStdStubBuffer *)This)->pvServerObject,alias);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char *)alias,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[30] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                (unsigned char *)alias,
                                (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[30] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char *)alias,
                        &__MIDL_TypeFormatString.Format[2] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [propput] */ HRESULT STDMETHODCALLTYPE ISpatialReferenceInfo_put_Alias_Proxy( 
    ISpatialReferenceInfo * This,
    /* [in] */ BSTR alias)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      10);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char *)&alias,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[44] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                    (unsigned char *)&alias,
                                    (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[44] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[6] );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
    void *_p_alias;
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
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[6] );
        
        NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&_p_alias,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[44],
                                  (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISpatialReferenceInfo*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> put_Alias((ISpatialReferenceInfo *) ((CStdStubBuffer *)This)->pvServerObject,alias);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrUserMarshalFree( &_StubMsg,
                            (unsigned char *)&alias,
                            &__MIDL_TypeFormatString.Format[44] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [propget] */ HRESULT STDMETHODCALLTYPE ISpatialReferenceInfo_get_Abbreviation_Proxy( 
    ISpatialReferenceInfo * This,
    /* [retval][out] */ BSTR *abbrev)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(abbrev)
        {
        MIDL_memset(
               abbrev,
               0,
               sizeof( BSTR  ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      11);
        
        
        
        if(!abbrev)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[0] );
            
            NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char * *)&abbrev,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[30],
                                      (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[2],
                         ( void * )abbrev);
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
    BSTR *abbrev;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( BSTR * )abbrev = 0;
    RpcTryFinally
        {
        abbrev = &_M4;
        MIDL_memset(
               abbrev,
               0,
               sizeof( BSTR  ));
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISpatialReferenceInfo*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_Abbreviation((ISpatialReferenceInfo *) ((CStdStubBuffer *)This)->pvServerObject,abbrev);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char *)abbrev,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[30] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                (unsigned char *)abbrev,
                                (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[30] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char *)abbrev,
                        &__MIDL_TypeFormatString.Format[2] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [propput] */ HRESULT STDMETHODCALLTYPE ISpatialReferenceInfo_put_Abbreviation_Proxy( 
    ISpatialReferenceInfo * This,
    /* [in] */ BSTR abbrev)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      12);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char *)&abbrev,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[44] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                    (unsigned char *)&abbrev,
                                    (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[44] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[6] );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
    void *_p_abbrev;
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
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[6] );
        
        NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&_p_abbrev,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[44],
                                  (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISpatialReferenceInfo*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> put_Abbreviation((ISpatialReferenceInfo *) ((CStdStubBuffer *)This)->pvServerObject,abbrev);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrUserMarshalFree( &_StubMsg,
                            (unsigned char *)&abbrev,
                            &__MIDL_TypeFormatString.Format[44] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [propget] */ HRESULT STDMETHODCALLTYPE ISpatialReferenceInfo_get_Remarks_Proxy( 
    ISpatialReferenceInfo * This,
    /* [retval][out] */ BSTR *remarks)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(remarks)
        {
        MIDL_memset(
               remarks,
               0,
               sizeof( BSTR  ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      13);
        
        
        
        if(!remarks)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[0] );
            
            NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char * *)&remarks,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[30],
                                      (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[2],
                         ( void * )remarks);
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
    BSTR *remarks;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( BSTR * )remarks = 0;
    RpcTryFinally
        {
        remarks = &_M5;
        MIDL_memset(
               remarks,
               0,
               sizeof( BSTR  ));
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISpatialReferenceInfo*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_Remarks((ISpatialReferenceInfo *) ((CStdStubBuffer *)This)->pvServerObject,remarks);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char *)remarks,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[30] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                (unsigned char *)remarks,
                                (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[30] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char *)remarks,
                        &__MIDL_TypeFormatString.Format[2] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [propput] */ HRESULT STDMETHODCALLTYPE ISpatialReferenceInfo_put_Remarks_Proxy( 
    ISpatialReferenceInfo * This,
    /* [in] */ BSTR remarks)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      14);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char *)&remarks,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[44] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                    (unsigned char *)&remarks,
                                    (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[44] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[6] );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
    void *_p_remarks;
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
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[6] );
        
        NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&_p_remarks,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[44],
                                  (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISpatialReferenceInfo*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> put_Remarks((ISpatialReferenceInfo *) ((CStdStubBuffer *)This)->pvServerObject,remarks);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrUserMarshalFree( &_StubMsg,
                            (unsigned char *)&remarks,
                            &__MIDL_TypeFormatString.Format[44] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [propget] */ HRESULT STDMETHODCALLTYPE ISpatialReferenceInfo_get_WellKnownText_Proxy( 
    ISpatialReferenceInfo * This,
    /* [retval][out] */ BSTR *wkt)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(wkt)
        {
        MIDL_memset(
               wkt,
               0,
               sizeof( BSTR  ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      15);
        
        
        
        if(!wkt)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[0] );
            
            NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char * *)&wkt,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[30],
                                      (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[2],
                         ( void * )wkt);
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
    BSTR *wkt;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( BSTR * )wkt = 0;
    RpcTryFinally
        {
        wkt = &_M6;
        MIDL_memset(
               wkt,
               0,
               sizeof( BSTR  ));
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISpatialReferenceInfo*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_WellKnownText((ISpatialReferenceInfo *) ((CStdStubBuffer *)This)->pvServerObject,wkt);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char *)wkt,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[30] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                (unsigned char *)wkt,
                                (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[30] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char *)wkt,
                        &__MIDL_TypeFormatString.Format[2] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IUnit_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IUnit_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IAngularUnit_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IAngularUnit_ProxyInfo;


/* [propget] */ HRESULT STDMETHODCALLTYPE IAngularUnit_get_RadiansPerUnit_Proxy( 
    IAngularUnit * This,
    /* [retval][out] */ double *factor)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      16);
        
        
        
        if(!factor)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[22] );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 7) & ~ 0x7);
            *factor = *(( double * )_StubMsg.Buffer)++;
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[58],
                         ( void * )factor);
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
    double _M7	=	0;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    double *factor;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( double * )factor = 0;
    RpcTryFinally
        {
        factor = &_M7;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IAngularUnit*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_RadiansPerUnit((IAngularUnit *) ((CStdStubBuffer *)This)->pvServerObject,factor);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 44;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 7) & ~ 0x7);
        *(( double * )_StubMsg.Buffer)++ = *factor;
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [propput] */ HRESULT STDMETHODCALLTYPE IAngularUnit_put_RadiansPerUnit_Proxy( 
    IAngularUnit * This,
    /* [in] */ double factor)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      17);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 16;
            NdrProxyGetBuffer(This, &_StubMsg);
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 7) & ~ 0x7);
            *(( double * )_StubMsg.Buffer)++ = factor;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[28] );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
    factor = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[28] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 7) & ~ 0x7);
        
        if(_StubMsg.Buffer + 8 > _StubMsg.BufferEnd)
            {
            RpcRaiseException(RPC_X_BAD_STUB_DATA);
            }
        factor = *(( double * )_StubMsg.Buffer)++;
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IAngularUnit*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> put_RadiansPerUnit((IAngularUnit *) ((CStdStubBuffer *)This)->pvServerObject,factor);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO ILinearUnit_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO ILinearUnit_ProxyInfo;


/* [propget] */ HRESULT STDMETHODCALLTYPE ILinearUnit_get_MetersPerUnit_Proxy( 
    ILinearUnit * This,
    /* [retval][out] */ double *factor)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      16);
        
        
        
        if(!factor)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[22] );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 7) & ~ 0x7);
            *factor = *(( double * )_StubMsg.Buffer)++;
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[58],
                         ( void * )factor);
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
    double _M8	=	0;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    double *factor;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( double * )factor = 0;
    RpcTryFinally
        {
        factor = &_M8;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ILinearUnit*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_MetersPerUnit((ILinearUnit *) ((CStdStubBuffer *)This)->pvServerObject,factor);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 44;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 7) & ~ 0x7);
        *(( double * )_StubMsg.Buffer)++ = *factor;
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [propput] */ HRESULT STDMETHODCALLTYPE ILinearUnit_put_MetersPerUnit_Proxy( 
    ILinearUnit * This,
    /* [in] */ double factor)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      17);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 16;
            NdrProxyGetBuffer(This, &_StubMsg);
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 7) & ~ 0x7);
            *(( double * )_StubMsg.Buffer)++ = factor;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[28] );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
    factor = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[28] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 7) & ~ 0x7);
        
        if(_StubMsg.Buffer + 8 > _StubMsg.BufferEnd)
            {
            RpcRaiseException(RPC_X_BAD_STUB_DATA);
            }
        factor = *(( double * )_StubMsg.Buffer)++;
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ILinearUnit*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> put_MetersPerUnit((ILinearUnit *) ((CStdStubBuffer *)This)->pvServerObject,factor);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IEllipsoid_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IEllipsoid_ProxyInfo;


/* [propget] */ HRESULT STDMETHODCALLTYPE IEllipsoid_get_SemiMajorAxis_Proxy( 
    IEllipsoid * This,
    /* [retval][out] */ double *axis)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      16);
        
        
        
        if(!axis)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[22] );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 7) & ~ 0x7);
            *axis = *(( double * )_StubMsg.Buffer)++;
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[58],
                         ( void * )axis);
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
    double _M9	=	0;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    double *axis;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( double * )axis = 0;
    RpcTryFinally
        {
        axis = &_M9;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IEllipsoid*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_SemiMajorAxis((IEllipsoid *) ((CStdStubBuffer *)This)->pvServerObject,axis);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 44;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 7) & ~ 0x7);
        *(( double * )_StubMsg.Buffer)++ = *axis;
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [propput] */ HRESULT STDMETHODCALLTYPE IEllipsoid_put_SemiMajorAxis_Proxy( 
    IEllipsoid * This,
    /* [in] */ double axis)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      17);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 16;
            NdrProxyGetBuffer(This, &_StubMsg);
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 7) & ~ 0x7);
            *(( double * )_StubMsg.Buffer)++ = axis;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[28] );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
    axis = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[28] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 7) & ~ 0x7);
        
        if(_StubMsg.Buffer + 8 > _StubMsg.BufferEnd)
            {
            RpcRaiseException(RPC_X_BAD_STUB_DATA);
            }
        axis = *(( double * )_StubMsg.Buffer)++;
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IEllipsoid*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> put_SemiMajorAxis((IEllipsoid *) ((CStdStubBuffer *)This)->pvServerObject,axis);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [propget] */ HRESULT STDMETHODCALLTYPE IEllipsoid_get_SemiMinorAxis_Proxy( 
    IEllipsoid * This,
    /* [retval][out] */ double *axis)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      18);
        
        
        
        if(!axis)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[22] );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 7) & ~ 0x7);
            *axis = *(( double * )_StubMsg.Buffer)++;
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[58],
                         ( void * )axis);
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
    double _M10	=	0;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    double *axis;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( double * )axis = 0;
    RpcTryFinally
        {
        axis = &_M10;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IEllipsoid*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_SemiMinorAxis((IEllipsoid *) ((CStdStubBuffer *)This)->pvServerObject,axis);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 44;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 7) & ~ 0x7);
        *(( double * )_StubMsg.Buffer)++ = *axis;
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [propput] */ HRESULT STDMETHODCALLTYPE IEllipsoid_put_SemiMinorAxis_Proxy( 
    IEllipsoid * This,
    /* [in] */ double axis)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      19);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 16;
            NdrProxyGetBuffer(This, &_StubMsg);
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 7) & ~ 0x7);
            *(( double * )_StubMsg.Buffer)++ = axis;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[28] );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
    axis = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[28] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 7) & ~ 0x7);
        
        if(_StubMsg.Buffer + 8 > _StubMsg.BufferEnd)
            {
            RpcRaiseException(RPC_X_BAD_STUB_DATA);
            }
        axis = *(( double * )_StubMsg.Buffer)++;
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IEllipsoid*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> put_SemiMinorAxis((IEllipsoid *) ((CStdStubBuffer *)This)->pvServerObject,axis);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [propget] */ HRESULT STDMETHODCALLTYPE IEllipsoid_get_InverseFlattening_Proxy( 
    IEllipsoid * This,
    /* [retval][out] */ double *invFlat)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      20);
        
        
        
        if(!invFlat)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[22] );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 7) & ~ 0x7);
            *invFlat = *(( double * )_StubMsg.Buffer)++;
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[58],
                         ( void * )invFlat);
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
    double _M11	=	0;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    double *invFlat;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( double * )invFlat = 0;
    RpcTryFinally
        {
        invFlat = &_M11;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IEllipsoid*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_InverseFlattening((IEllipsoid *) ((CStdStubBuffer *)This)->pvServerObject,invFlat);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 44;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 7) & ~ 0x7);
        *(( double * )_StubMsg.Buffer)++ = *invFlat;
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [propput] */ HRESULT STDMETHODCALLTYPE IEllipsoid_put_InverseFlattening_Proxy( 
    IEllipsoid * This,
    /* [in] */ double invFlat)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      21);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 16;
            NdrProxyGetBuffer(This, &_StubMsg);
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 7) & ~ 0x7);
            *(( double * )_StubMsg.Buffer)++ = invFlat;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[28] );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
    invFlat = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[28] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 7) & ~ 0x7);
        
        if(_StubMsg.Buffer + 8 > _StubMsg.BufferEnd)
            {
            RpcRaiseException(RPC_X_BAD_STUB_DATA);
            }
        invFlat = *(( double * )_StubMsg.Buffer)++;
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IEllipsoid*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> put_InverseFlattening((IEllipsoid *) ((CStdStubBuffer *)This)->pvServerObject,invFlat);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [propget] */ HRESULT STDMETHODCALLTYPE IEllipsoid_get_AxisUnit_Proxy( 
    IEllipsoid * This,
    /* [retval][out] */ ILinearUnit **unit)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(unit)
        {
        MIDL_memset(
               unit,
               0,
               sizeof( ILinearUnit ** ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      22);
        
        
        
        if(!unit)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[32] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&unit,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[62],
                                  (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[62],
                         ( void * )unit);
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
    ILinearUnit *_M12;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    ILinearUnit **unit;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( ILinearUnit ** )unit = 0;
    RpcTryFinally
        {
        unit = &_M12;
        _M12 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IEllipsoid*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_AxisUnit((IEllipsoid *) ((CStdStubBuffer *)This)->pvServerObject,unit);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char *)unit,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[62] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char *)unit,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[62] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char *)unit,
                        &__MIDL_TypeFormatString.Format[62] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [propput] */ HRESULT STDMETHODCALLTYPE IEllipsoid_put_AxisUnit_Proxy( 
    IEllipsoid * This,
    /* [in] */ ILinearUnit *unit)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      23);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrInterfacePointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                           (unsigned char *)unit,
                                           (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[66] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrInterfacePointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                         (unsigned char *)unit,
                                         (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[66] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[38] );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
    ILinearUnit *unit;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    unit = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[38] );
        
        NdrInterfacePointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char * *)&unit,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[66],
                                       (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IEllipsoid*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> put_AxisUnit((IEllipsoid *) ((CStdStubBuffer *)This)->pvServerObject,unit);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrInterfacePointerFree( &_StubMsg,
                                 (unsigned char *)unit,
                                 &__MIDL_TypeFormatString.Format[66] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IHorizontalDatum_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IHorizontalDatum_ProxyInfo;


/* [propget] */ HRESULT STDMETHODCALLTYPE IHorizontalDatum_get_Ellipsoid_Proxy( 
    IHorizontalDatum * This,
    /* [retval][out] */ IEllipsoid **ellipsoid)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(ellipsoid)
        {
        MIDL_memset(
               ellipsoid,
               0,
               sizeof( IEllipsoid ** ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      16);
        
        
        
        if(!ellipsoid)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[44] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&ellipsoid,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[84],
                                  (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[84],
                         ( void * )ellipsoid);
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
    IEllipsoid *_M13;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    IEllipsoid **ellipsoid;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( IEllipsoid ** )ellipsoid = 0;
    RpcTryFinally
        {
        ellipsoid = &_M13;
        _M13 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IHorizontalDatum*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_Ellipsoid((IHorizontalDatum *) ((CStdStubBuffer *)This)->pvServerObject,ellipsoid);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char *)ellipsoid,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[84] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char *)ellipsoid,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[84] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char *)ellipsoid,
                        &__MIDL_TypeFormatString.Format[84] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [propput] */ HRESULT STDMETHODCALLTYPE IHorizontalDatum_put_Ellipsoid_Proxy( 
    IHorizontalDatum * This,
    /* [in] */ IEllipsoid *ellipsoid)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      17);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrInterfacePointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                           (unsigned char *)ellipsoid,
                                           (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[88] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrInterfacePointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                         (unsigned char *)ellipsoid,
                                         (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[88] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[50] );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
    IEllipsoid *ellipsoid;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ellipsoid = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[50] );
        
        NdrInterfacePointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char * *)&ellipsoid,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[88],
                                       (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IHorizontalDatum*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> put_Ellipsoid((IHorizontalDatum *) ((CStdStubBuffer *)This)->pvServerObject,ellipsoid);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrInterfacePointerFree( &_StubMsg,
                                 (unsigned char *)ellipsoid,
                                 &__MIDL_TypeFormatString.Format[88] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IPrimeMeridian_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IPrimeMeridian_ProxyInfo;


/* [propget] */ HRESULT STDMETHODCALLTYPE IPrimeMeridian_get_Longitude_Proxy( 
    IPrimeMeridian * This,
    /* [retval][out] */ double *longitude)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      16);
        
        
        
        if(!longitude)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[22] );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 7) & ~ 0x7);
            *longitude = *(( double * )_StubMsg.Buffer)++;
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[58],
                         ( void * )longitude);
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
    double _M14	=	0;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    double *longitude;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( double * )longitude = 0;
    RpcTryFinally
        {
        longitude = &_M14;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IPrimeMeridian*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_Longitude((IPrimeMeridian *) ((CStdStubBuffer *)This)->pvServerObject,longitude);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 44;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 7) & ~ 0x7);
        *(( double * )_StubMsg.Buffer)++ = *longitude;
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [propput] */ HRESULT STDMETHODCALLTYPE IPrimeMeridian_put_Longitude_Proxy( 
    IPrimeMeridian * This,
    /* [in] */ double longitude)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      17);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 16;
            NdrProxyGetBuffer(This, &_StubMsg);
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 7) & ~ 0x7);
            *(( double * )_StubMsg.Buffer)++ = longitude;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[28] );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
    longitude = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[28] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 7) & ~ 0x7);
        
        if(_StubMsg.Buffer + 8 > _StubMsg.BufferEnd)
            {
            RpcRaiseException(RPC_X_BAD_STUB_DATA);
            }
        longitude = *(( double * )_StubMsg.Buffer)++;
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IPrimeMeridian*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> put_Longitude((IPrimeMeridian *) ((CStdStubBuffer *)This)->pvServerObject,longitude);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [propget] */ HRESULT STDMETHODCALLTYPE IPrimeMeridian_get_AngularUnit_Proxy( 
    IPrimeMeridian * This,
    /* [retval][out] */ IAngularUnit **unit)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(unit)
        {
        MIDL_memset(
               unit,
               0,
               sizeof( IAngularUnit ** ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      18);
        
        
        
        if(!unit)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[56] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&unit,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[106],
                                  (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[106],
                         ( void * )unit);
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
    IAngularUnit *_M15;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    IAngularUnit **unit;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( IAngularUnit ** )unit = 0;
    RpcTryFinally
        {
        unit = &_M15;
        _M15 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IPrimeMeridian*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_AngularUnit((IPrimeMeridian *) ((CStdStubBuffer *)This)->pvServerObject,unit);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char *)unit,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[106] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char *)unit,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[106] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char *)unit,
                        &__MIDL_TypeFormatString.Format[106] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [propput] */ HRESULT STDMETHODCALLTYPE IPrimeMeridian_put_AngularUnit_Proxy( 
    IPrimeMeridian * This,
    /* [in] */ IAngularUnit *unit)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      19);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrInterfacePointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                           (unsigned char *)unit,
                                           (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[110] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrInterfacePointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                         (unsigned char *)unit,
                                         (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[110] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[62] );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
    IAngularUnit *unit;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    unit = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[62] );
        
        NdrInterfacePointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char * *)&unit,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[110],
                                       (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IPrimeMeridian*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> put_AngularUnit((IPrimeMeridian *) ((CStdStubBuffer *)This)->pvServerObject,unit);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrInterfacePointerFree( &_StubMsg,
                                 (unsigned char *)unit,
                                 &__MIDL_TypeFormatString.Format[110] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO ISpatialReference_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO ISpatialReference_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IGeodeticSpatialReference_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IGeodeticSpatialReference_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IGeographicCoordinateSystem_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IGeographicCoordinateSystem_ProxyInfo;


/* [propget] */ HRESULT STDMETHODCALLTYPE IGeographicCoordinateSystem_get_Usage_Proxy( 
    IGeographicCoordinateSystem * This,
    /* [retval][out] */ BSTR *usage)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(usage)
        {
        MIDL_memset(
               usage,
               0,
               sizeof( BSTR  ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      16);
        
        
        
        if(!usage)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[0] );
            
            NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char * *)&usage,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[30],
                                      (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[2],
                         ( void * )usage);
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
    BSTR *usage;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( BSTR * )usage = 0;
    RpcTryFinally
        {
        usage = &_M16;
        MIDL_memset(
               usage,
               0,
               sizeof( BSTR  ));
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IGeographicCoordinateSystem*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_Usage((IGeographicCoordinateSystem *) ((CStdStubBuffer *)This)->pvServerObject,usage);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char *)usage,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[30] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                (unsigned char *)usage,
                                (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[30] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char *)usage,
                        &__MIDL_TypeFormatString.Format[2] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [propput] */ HRESULT STDMETHODCALLTYPE IGeographicCoordinateSystem_put_Usage_Proxy( 
    IGeographicCoordinateSystem * This,
    /* [in] */ BSTR usage)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      17);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char *)&usage,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[44] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                    (unsigned char *)&usage,
                                    (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[44] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[6] );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
    void *_p_usage;
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
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[6] );
        
        NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&_p_usage,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[44],
                                  (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IGeographicCoordinateSystem*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> put_Usage((IGeographicCoordinateSystem *) ((CStdStubBuffer *)This)->pvServerObject,usage);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrUserMarshalFree( &_StubMsg,
                            (unsigned char *)&usage,
                            &__MIDL_TypeFormatString.Format[44] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [propget] */ HRESULT STDMETHODCALLTYPE IGeographicCoordinateSystem_get_HorizontalDatum_Proxy( 
    IGeographicCoordinateSystem * This,
    /* [retval][out] */ IHorizontalDatum **datum)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(datum)
        {
        MIDL_memset(
               datum,
               0,
               sizeof( IHorizontalDatum ** ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      18);
        
        
        
        if(!datum)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[68] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&datum,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[128],
                                  (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
                         ( void * )datum);
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
    IHorizontalDatum *_M17;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    IHorizontalDatum **datum;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( IHorizontalDatum ** )datum = 0;
    RpcTryFinally
        {
        datum = &_M17;
        _M17 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IGeographicCoordinateSystem*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_HorizontalDatum((IGeographicCoordinateSystem *) ((CStdStubBuffer *)This)->pvServerObject,datum);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char *)datum,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[128] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char *)datum,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[128] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char *)datum,
                        &__MIDL_TypeFormatString.Format[128] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [propput] */ HRESULT STDMETHODCALLTYPE IGeographicCoordinateSystem_put_HorizontalDatum_Proxy( 
    IGeographicCoordinateSystem * This,
    /* [in] */ IHorizontalDatum *datum)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      19);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrInterfacePointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                           (unsigned char *)datum,
                                           (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[132] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrInterfacePointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                         (unsigned char *)datum,
                                         (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[132] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[74] );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
    IHorizontalDatum *datum;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    datum = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[74] );
        
        NdrInterfacePointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char * *)&datum,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[132],
                                       (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IGeographicCoordinateSystem*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> put_HorizontalDatum((IGeographicCoordinateSystem *) ((CStdStubBuffer *)This)->pvServerObject,datum);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrInterfacePointerFree( &_StubMsg,
                                 (unsigned char *)datum,
                                 &__MIDL_TypeFormatString.Format[132] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [propget] */ HRESULT STDMETHODCALLTYPE IGeographicCoordinateSystem_get_AngularUnit_Proxy( 
    IGeographicCoordinateSystem * This,
    /* [retval][out] */ IAngularUnit **unit)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(unit)
        {
        MIDL_memset(
               unit,
               0,
               sizeof( IAngularUnit ** ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      20);
        
        
        
        if(!unit)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[56] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&unit,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[106],
                                  (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[106],
                         ( void * )unit);
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
    IAngularUnit *_M18;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    IAngularUnit **unit;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( IAngularUnit ** )unit = 0;
    RpcTryFinally
        {
        unit = &_M18;
        _M18 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IGeographicCoordinateSystem*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_AngularUnit((IGeographicCoordinateSystem *) ((CStdStubBuffer *)This)->pvServerObject,unit);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char *)unit,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[106] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char *)unit,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[106] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char *)unit,
                        &__MIDL_TypeFormatString.Format[106] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [propput] */ HRESULT STDMETHODCALLTYPE IGeographicCoordinateSystem_put_AngularUnit_Proxy( 
    IGeographicCoordinateSystem * This,
    /* [in] */ IAngularUnit *unit)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      21);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrInterfacePointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                           (unsigned char *)unit,
                                           (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[110] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrInterfacePointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                         (unsigned char *)unit,
                                         (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[110] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[62] );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
    IAngularUnit *unit;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    unit = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[62] );
        
        NdrInterfacePointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char * *)&unit,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[110],
                                       (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IGeographicCoordinateSystem*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> put_AngularUnit((IGeographicCoordinateSystem *) ((CStdStubBuffer *)This)->pvServerObject,unit);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrInterfacePointerFree( &_StubMsg,
                                 (unsigned char *)unit,
                                 &__MIDL_TypeFormatString.Format[110] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [propget] */ HRESULT STDMETHODCALLTYPE IGeographicCoordinateSystem_get_PrimeMeridian_Proxy( 
    IGeographicCoordinateSystem * This,
    /* [retval][out] */ IPrimeMeridian **prmMerid)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(prmMerid)
        {
        MIDL_memset(
               prmMerid,
               0,
               sizeof( IPrimeMeridian ** ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      22);
        
        
        
        if(!prmMerid)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[80] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&prmMerid,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[150],
                                  (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[150],
                         ( void * )prmMerid);
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
    IPrimeMeridian *_M19;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    IPrimeMeridian **prmMerid;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( IPrimeMeridian ** )prmMerid = 0;
    RpcTryFinally
        {
        prmMerid = &_M19;
        _M19 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IGeographicCoordinateSystem*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_PrimeMeridian((IGeographicCoordinateSystem *) ((CStdStubBuffer *)This)->pvServerObject,prmMerid);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char *)prmMerid,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[150] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char *)prmMerid,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[150] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char *)prmMerid,
                        &__MIDL_TypeFormatString.Format[150] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [propput] */ HRESULT STDMETHODCALLTYPE IGeographicCoordinateSystem_put_PrimeMeridian_Proxy( 
    IGeographicCoordinateSystem * This,
    /* [in] */ IPrimeMeridian *prmMerid)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      23);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrInterfacePointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                           (unsigned char *)prmMerid,
                                           (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[154] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrInterfacePointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                         (unsigned char *)prmMerid,
                                         (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[154] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[86] );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
    IPrimeMeridian *prmMerid;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    prmMerid = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[86] );
        
        NdrInterfacePointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char * *)&prmMerid,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[154],
                                       (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IGeographicCoordinateSystem*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> put_PrimeMeridian((IGeographicCoordinateSystem *) ((CStdStubBuffer *)This)->pvServerObject,prmMerid);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrInterfacePointerFree( &_StubMsg,
                                 (unsigned char *)prmMerid,
                                 &__MIDL_TypeFormatString.Format[154] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IParameter_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IParameter_ProxyInfo;


/* [propput] */ HRESULT STDMETHODCALLTYPE IParameter_put_ValueUnit_Proxy( 
    IParameter * This,
    /* [in] */ IUnit *unit)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      16);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrInterfacePointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                           (unsigned char *)unit,
                                           (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[172] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrInterfacePointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                         (unsigned char *)unit,
                                         (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[172] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[92] );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
    IUnit *unit;
    
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
                                       (unsigned char * *)&unit,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[172],
                                       (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IParameter*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> put_ValueUnit((IParameter *) ((CStdStubBuffer *)This)->pvServerObject,unit);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrInterfacePointerFree( &_StubMsg,
                                 (unsigned char *)unit,
                                 &__MIDL_TypeFormatString.Format[172] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [propget] */ HRESULT STDMETHODCALLTYPE IParameter_get_ValueUnit_Proxy( 
    IParameter * This,
    /* [retval][out] */ IUnit **unit)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(unit)
        {
        MIDL_memset(
               unit,
               0,
               sizeof( IUnit ** ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      17);
        
        
        
        if(!unit)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[98] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&unit,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[190],
                                  (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[190],
                         ( void * )unit);
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
    IUnit *_M20;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    IUnit **unit;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( IUnit ** )unit = 0;
    RpcTryFinally
        {
        unit = &_M20;
        _M20 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IParameter*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_ValueUnit((IParameter *) ((CStdStubBuffer *)This)->pvServerObject,unit);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char *)unit,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[190] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char *)unit,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[190] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char *)unit,
                        &__MIDL_TypeFormatString.Format[190] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [propput] */ HRESULT STDMETHODCALLTYPE IParameter_put_Value_Proxy( 
    IParameter * This,
    /* [in] */ double value)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      18);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 16;
            NdrProxyGetBuffer(This, &_StubMsg);
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 7) & ~ 0x7);
            *(( double * )_StubMsg.Buffer)++ = value;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[28] );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
    value = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[28] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 7) & ~ 0x7);
        
        if(_StubMsg.Buffer + 8 > _StubMsg.BufferEnd)
            {
            RpcRaiseException(RPC_X_BAD_STUB_DATA);
            }
        value = *(( double * )_StubMsg.Buffer)++;
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IParameter*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> put_Value((IParameter *) ((CStdStubBuffer *)This)->pvServerObject,value);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [propget] */ HRESULT STDMETHODCALLTYPE IParameter_get_Value_Proxy( 
    IParameter * This,
    /* [retval][out] */ double *value)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      19);
        
        
        
        if(!value)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[22] );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 7) & ~ 0x7);
            *value = *(( double * )_StubMsg.Buffer)++;
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[58],
                         ( void * )value);
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
    double _M21	=	0;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    double *value;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( double * )value = 0;
    RpcTryFinally
        {
        value = &_M21;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IParameter*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_Value((IParameter *) ((CStdStubBuffer *)This)->pvServerObject,value);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 44;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 7) & ~ 0x7);
        *(( double * )_StubMsg.Buffer)++ = *value;
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IParameterInfo_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IParameterInfo_ProxyInfo;


/* [propget] */ HRESULT STDMETHODCALLTYPE IParameterInfo_get_NumParameters_Proxy( 
    IParameterInfo * This,
    /* [retval][out] */ long *numParameters)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      3);
        
        
        
        if(!numParameters)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[12] );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            *numParameters = *(( long * )_StubMsg.Buffer)++;
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[54],
                         ( void * )numParameters);
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
    long _M22	=	0;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    long *numParameters;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( long * )numParameters = 0;
    RpcTryFinally
        {
        numParameters = &_M22;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IParameterInfo*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_NumParameters((IParameterInfo *) ((CStdStubBuffer *)This)->pvServerObject,numParameters);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 36;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( long * )_StubMsg.Buffer)++ = *numParameters;
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [propget] */ HRESULT STDMETHODCALLTYPE IParameterInfo_get_DefaultParameters_Proxy( 
    IParameterInfo * This,
    /* [in] */ long size,
    /* [size_is][out] */ IParameter *parameters[  ])
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(parameters)
        {
        MIDL_memset(
               parameters,
               0,
               sizeof( IParameter *[ 1 ] ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      4);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 8;
            NdrProxyGetBuffer(This, &_StubMsg);
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            *(( long * )_StubMsg.Buffer)++ = size;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[104] );
            
            NdrComplexArrayUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char * *)&parameters,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[212],
                                       (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _StubMsg.MaxCount = ( unsigned long  )size;
        
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[212],
                         ( void * )parameters);
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
    IParameter *( *parameters )[  ];
    long size;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    size = 0;
    parameters = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[104] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        
        if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
            {
            RpcRaiseException(RPC_X_BAD_STUB_DATA);
            }
        size = *(( long * )_StubMsg.Buffer)++;
        
        if(size * 4 < 0)
            {
            RpcRaiseException(RPC_X_INVALID_BOUND);
            }
        parameters = NdrAllocate(&_StubMsg,size * 4);
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IParameterInfo*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_DefaultParameters(
                         (IParameterInfo *) ((CStdStubBuffer *)This)->pvServerObject,
                         size,
                         *parameters);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        _StubMsg.MaxCount = ( unsigned long  )size;
        
        NdrComplexArrayBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char *)*parameters,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[212] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.MaxCount = ( unsigned long  )size;
        
        NdrComplexArrayMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char *)*parameters,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[212] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        _StubMsg.MaxCount = ( unsigned long  )size;
        
        NdrComplexArrayFree( &_StubMsg,
                             (unsigned char *)parameters,
                             &__MIDL_TypeFormatString.Format[212] );
        
        if ( parameters )
            _StubMsg.pfnFree( parameters );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [propget] */ HRESULT STDMETHODCALLTYPE IParameterInfo_get_Parameters_Proxy( 
    IParameterInfo * This,
    /* [in] */ long size,
    /* [size_is][out] */ IParameter *parameters[  ])
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(parameters)
        {
        MIDL_memset(
               parameters,
               0,
               sizeof( IParameter *[ 1 ] ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      5);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 8;
            NdrProxyGetBuffer(This, &_StubMsg);
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            *(( long * )_StubMsg.Buffer)++ = size;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[104] );
            
            NdrComplexArrayUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char * *)&parameters,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[212],
                                       (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _StubMsg.MaxCount = ( unsigned long  )size;
        
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[212],
                         ( void * )parameters);
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
    IParameter *( *parameters )[  ];
    long size;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    size = 0;
    parameters = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[104] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        
        if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
            {
            RpcRaiseException(RPC_X_BAD_STUB_DATA);
            }
        size = *(( long * )_StubMsg.Buffer)++;
        
        if(size * 4 < 0)
            {
            RpcRaiseException(RPC_X_INVALID_BOUND);
            }
        parameters = NdrAllocate(&_StubMsg,size * 4);
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IParameterInfo*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_Parameters(
                  (IParameterInfo *) ((CStdStubBuffer *)This)->pvServerObject,
                  size,
                  *parameters);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        _StubMsg.MaxCount = ( unsigned long  )size;
        
        NdrComplexArrayBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char *)*parameters,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[212] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.MaxCount = ( unsigned long  )size;
        
        NdrComplexArrayMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char *)*parameters,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[212] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        _StubMsg.MaxCount = ( unsigned long  )size;
        
        NdrComplexArrayFree( &_StubMsg,
                             (unsigned char *)parameters,
                             &__MIDL_TypeFormatString.Format[212] );
        
        if ( parameters )
            _StubMsg.pfnFree( parameters );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [propput] */ HRESULT STDMETHODCALLTYPE IParameterInfo_put_Parameters_Proxy( 
    IParameterInfo * This,
    /* [in] */ long size,
    /* [size_is][in] */ IParameter *parameters[  ])
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      6);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 8;
            _StubMsg.MaxCount = ( unsigned long  )size;
            
            NdrComplexArrayBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char *)parameters,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[212] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            *(( long * )_StubMsg.Buffer)++ = size;
            
            _StubMsg.MaxCount = ( unsigned long  )size;
            
            NdrComplexArrayMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char *)parameters,
                                     (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[212] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[112] );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
    IParameter *( *parameters )[  ];
    long size;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    size = 0;
    parameters = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[112] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        
        if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
            {
            RpcRaiseException(RPC_X_BAD_STUB_DATA);
            }
        size = *(( long * )_StubMsg.Buffer)++;
        
        NdrComplexArrayUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char * *)&parameters,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[212],
                                   (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IParameterInfo*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> put_Parameters(
                  (IParameterInfo *) ((CStdStubBuffer *)This)->pvServerObject,
                  size,
                  *parameters);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        _StubMsg.MaxCount = ( unsigned long  )size;
        
        NdrComplexArrayFree( &_StubMsg,
                             (unsigned char *)parameters,
                             &__MIDL_TypeFormatString.Format[212] );
        
        if ( parameters )
            _StubMsg.pfnFree( parameters );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IGeographicTransform_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IGeographicTransform_ProxyInfo;


/* [propget] */ HRESULT STDMETHODCALLTYPE IGeographicTransform_get_SourceGCS_Proxy( 
    IGeographicTransform * This,
    /* [out] */ IGeographicCoordinateSystem **gcs)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(gcs)
        {
        MIDL_memset(
               gcs,
               0,
               sizeof( IGeographicCoordinateSystem ** ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      16);
        
        
        
        if(!gcs)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[120] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&gcs,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[230],
                                  (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[230],
                         ( void * )gcs);
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
    IGeographicCoordinateSystem *_M26;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    IGeographicCoordinateSystem **gcs;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( IGeographicCoordinateSystem ** )gcs = 0;
    RpcTryFinally
        {
        gcs = &_M26;
        _M26 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IGeographicTransform*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_SourceGCS((IGeographicTransform *) ((CStdStubBuffer *)This)->pvServerObject,gcs);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char *)gcs,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[230] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char *)gcs,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[230] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char *)gcs,
                        &__MIDL_TypeFormatString.Format[230] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [propput] */ HRESULT STDMETHODCALLTYPE IGeographicTransform_put_SourceGCS_Proxy( 
    IGeographicTransform * This,
    /* [in] */ IGeographicCoordinateSystem *gcs)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      17);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrInterfacePointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                           (unsigned char *)gcs,
                                           (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[234] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrInterfacePointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                         (unsigned char *)gcs,
                                         (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[234] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[126] );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
    IGeographicCoordinateSystem *gcs;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    gcs = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[126] );
        
        NdrInterfacePointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char * *)&gcs,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[234],
                                       (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IGeographicTransform*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> put_SourceGCS((IGeographicTransform *) ((CStdStubBuffer *)This)->pvServerObject,gcs);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrInterfacePointerFree( &_StubMsg,
                                 (unsigned char *)gcs,
                                 &__MIDL_TypeFormatString.Format[234] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [propget] */ HRESULT STDMETHODCALLTYPE IGeographicTransform_get_TargetGCS_Proxy( 
    IGeographicTransform * This,
    /* [out] */ IGeographicCoordinateSystem **gcs)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(gcs)
        {
        MIDL_memset(
               gcs,
               0,
               sizeof( IGeographicCoordinateSystem ** ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      18);
        
        
        
        if(!gcs)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[120] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&gcs,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[230],
                                  (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[230],
                         ( void * )gcs);
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
    IGeographicCoordinateSystem *_M27;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    IGeographicCoordinateSystem **gcs;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( IGeographicCoordinateSystem ** )gcs = 0;
    RpcTryFinally
        {
        gcs = &_M27;
        _M27 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IGeographicTransform*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_TargetGCS((IGeographicTransform *) ((CStdStubBuffer *)This)->pvServerObject,gcs);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char *)gcs,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[230] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char *)gcs,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[230] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char *)gcs,
                        &__MIDL_TypeFormatString.Format[230] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [propput] */ HRESULT STDMETHODCALLTYPE IGeographicTransform_put_TargetGCS_Proxy( 
    IGeographicTransform * This,
    /* [in] */ IGeographicCoordinateSystem *gcs)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      19);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrInterfacePointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                           (unsigned char *)gcs,
                                           (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[234] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrInterfacePointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                         (unsigned char *)gcs,
                                         (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[234] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[126] );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
    IGeographicCoordinateSystem *gcs;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    gcs = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[126] );
        
        NdrInterfacePointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char * *)&gcs,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[234],
                                       (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IGeographicTransform*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> put_TargetGCS((IGeographicTransform *) ((CStdStubBuffer *)This)->pvServerObject,gcs);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrInterfacePointerFree( &_StubMsg,
                                 (unsigned char *)gcs,
                                 &__MIDL_TypeFormatString.Format[234] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [propget] */ HRESULT STDMETHODCALLTYPE IGeographicTransform_get_ParameterInfo_Proxy( 
    IGeographicTransform * This,
    /* [out] */ IParameterInfo **paramInfo)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(paramInfo)
        {
        MIDL_memset(
               paramInfo,
               0,
               sizeof( IParameterInfo ** ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      20);
        
        
        
        if(!paramInfo)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[132] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&paramInfo,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[252],
                                  (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[252],
                         ( void * )paramInfo);
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
    IParameterInfo *_M28;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    IParameterInfo **paramInfo;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( IParameterInfo ** )paramInfo = 0;
    RpcTryFinally
        {
        paramInfo = &_M28;
        _M28 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IGeographicTransform*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_ParameterInfo((IGeographicTransform *) ((CStdStubBuffer *)This)->pvServerObject,paramInfo);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char *)paramInfo,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[252] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char *)paramInfo,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[252] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char *)paramInfo,
                        &__MIDL_TypeFormatString.Format[252] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


HRESULT STDMETHODCALLTYPE IGeographicTransform_Forward_Proxy( 
    IGeographicTransform * This,
    /* [in] */ long count,
    /* [size_is][out][in] */ WKSPoint points[  ])
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      21);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 8;
            _StubMsg.MaxCount = ( unsigned long  )count;
            
            NdrConformantArrayBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                          (unsigned char *)points,
                                          (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[282] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            *(( long * )_StubMsg.Buffer)++ = count;
            
            _StubMsg.MaxCount = ( unsigned long  )count;
            
            NdrConformantArrayMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                        (unsigned char *)points,
                                        (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[282] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[138] );
            
            NdrConformantArrayUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                          (unsigned char * *)&points,
                                          (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[282],
                                          (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _StubMsg.MaxCount = ( unsigned long  )count;
        
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[282],
                         ( void * )points);
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
    WKSPoint ( *points )[  ];
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    count = 0;
    points = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[138] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        
        if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
            {
            RpcRaiseException(RPC_X_BAD_STUB_DATA);
            }
        count = *(( long * )_StubMsg.Buffer)++;
        
        NdrConformantArrayUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char * *)&points,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[282],
                                      (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IGeographicTransform*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> Forward(
           (IGeographicTransform *) ((CStdStubBuffer *)This)->pvServerObject,
           count,
           *points);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        _StubMsg.MaxCount = ( unsigned long  )count;
        
        NdrConformantArrayBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char *)*points,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[282] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.MaxCount = ( unsigned long  )count;
        
        NdrConformantArrayMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                    (unsigned char *)*points,
                                    (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[282] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


HRESULT STDMETHODCALLTYPE IGeographicTransform_Inverse_Proxy( 
    IGeographicTransform * This,
    /* [in] */ long count,
    /* [size_is][out][in] */ WKSPoint points[  ])
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      22);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 8;
            _StubMsg.MaxCount = ( unsigned long  )count;
            
            NdrConformantArrayBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                          (unsigned char *)points,
                                          (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[282] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            *(( long * )_StubMsg.Buffer)++ = count;
            
            _StubMsg.MaxCount = ( unsigned long  )count;
            
            NdrConformantArrayMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                        (unsigned char *)points,
                                        (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[282] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[138] );
            
            NdrConformantArrayUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                          (unsigned char * *)&points,
                                          (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[282],
                                          (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _StubMsg.MaxCount = ( unsigned long  )count;
        
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[282],
                         ( void * )points);
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
    WKSPoint ( *points )[  ];
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    count = 0;
    points = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[138] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        
        if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
            {
            RpcRaiseException(RPC_X_BAD_STUB_DATA);
            }
        count = *(( long * )_StubMsg.Buffer)++;
        
        NdrConformantArrayUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char * *)&points,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[282],
                                      (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IGeographicTransform*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> Inverse(
           (IGeographicTransform *) ((CStdStubBuffer *)This)->pvServerObject,
           count,
           *points);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        _StubMsg.MaxCount = ( unsigned long  )count;
        
        NdrConformantArrayBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char *)*points,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[282] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.MaxCount = ( unsigned long  )count;
        
        NdrConformantArrayMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                    (unsigned char *)*points,
                                    (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[282] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IProjection_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IProjection_ProxyInfo;


/* [propget] */ HRESULT STDMETHODCALLTYPE IProjection_get_Usage_Proxy( 
    IProjection * This,
    /* [retval][out] */ BSTR *usage)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(usage)
        {
        MIDL_memset(
               usage,
               0,
               sizeof( BSTR  ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      16);
        
        
        
        if(!usage)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[0] );
            
            NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char * *)&usage,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[30],
                                      (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[2],
                         ( void * )usage);
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
    BSTR *usage;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( BSTR * )usage = 0;
    RpcTryFinally
        {
        usage = &_M31;
        MIDL_memset(
               usage,
               0,
               sizeof( BSTR  ));
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IProjection*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_Usage((IProjection *) ((CStdStubBuffer *)This)->pvServerObject,usage);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char *)usage,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[30] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                (unsigned char *)usage,
                                (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[30] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char *)usage,
                        &__MIDL_TypeFormatString.Format[2] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [propget] */ HRESULT STDMETHODCALLTYPE IProjection_get_Classification_Proxy( 
    IProjection * This,
    /* [retval][out] */ BSTR *classification)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(classification)
        {
        MIDL_memset(
               classification,
               0,
               sizeof( BSTR  ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      17);
        
        
        
        if(!classification)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[0] );
            
            NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char * *)&classification,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[30],
                                      (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[2],
                         ( void * )classification);
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
    BSTR *classification;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( BSTR * )classification = 0;
    RpcTryFinally
        {
        classification = &_M32;
        MIDL_memset(
               classification,
               0,
               sizeof( BSTR  ));
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IProjection*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_Classification((IProjection *) ((CStdStubBuffer *)This)->pvServerObject,classification);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char *)classification,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[30] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                (unsigned char *)classification,
                                (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[30] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char *)classification,
                        &__MIDL_TypeFormatString.Format[2] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


HRESULT STDMETHODCALLTYPE IProjection_Forward_Proxy( 
    IProjection * This,
    /* [in] */ long count,
    /* [size_is][out][in] */ WKSPoint points[  ])
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      18);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 8;
            _StubMsg.MaxCount = ( unsigned long  )count;
            
            NdrConformantArrayBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                          (unsigned char *)points,
                                          (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[282] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            *(( long * )_StubMsg.Buffer)++ = count;
            
            _StubMsg.MaxCount = ( unsigned long  )count;
            
            NdrConformantArrayMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                        (unsigned char *)points,
                                        (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[282] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[138] );
            
            NdrConformantArrayUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                          (unsigned char * *)&points,
                                          (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[282],
                                          (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _StubMsg.MaxCount = ( unsigned long  )count;
        
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[282],
                         ( void * )points);
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
    WKSPoint ( *points )[  ];
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    count = 0;
    points = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[138] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        
        if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
            {
            RpcRaiseException(RPC_X_BAD_STUB_DATA);
            }
        count = *(( long * )_StubMsg.Buffer)++;
        
        NdrConformantArrayUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char * *)&points,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[282],
                                      (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IProjection*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> Forward(
           (IProjection *) ((CStdStubBuffer *)This)->pvServerObject,
           count,
           *points);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        _StubMsg.MaxCount = ( unsigned long  )count;
        
        NdrConformantArrayBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char *)*points,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[282] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.MaxCount = ( unsigned long  )count;
        
        NdrConformantArrayMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                    (unsigned char *)*points,
                                    (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[282] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


HRESULT STDMETHODCALLTYPE IProjection_Inverse_Proxy( 
    IProjection * This,
    /* [in] */ long count,
    /* [size_is][out][in] */ WKSPoint points[  ])
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      19);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 8;
            _StubMsg.MaxCount = ( unsigned long  )count;
            
            NdrConformantArrayBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                          (unsigned char *)points,
                                          (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[282] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            *(( long * )_StubMsg.Buffer)++ = count;
            
            _StubMsg.MaxCount = ( unsigned long  )count;
            
            NdrConformantArrayMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                        (unsigned char *)points,
                                        (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[282] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[138] );
            
            NdrConformantArrayUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                          (unsigned char * *)&points,
                                          (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[282],
                                          (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _StubMsg.MaxCount = ( unsigned long  )count;
        
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[282],
                         ( void * )points);
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
    WKSPoint ( *points )[  ];
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    count = 0;
    points = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[138] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        
        if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
            {
            RpcRaiseException(RPC_X_BAD_STUB_DATA);
            }
        count = *(( long * )_StubMsg.Buffer)++;
        
        NdrConformantArrayUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char * *)&points,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[282],
                                      (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IProjection*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> Inverse(
           (IProjection *) ((CStdStubBuffer *)This)->pvServerObject,
           count,
           *points);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        _StubMsg.MaxCount = ( unsigned long  )count;
        
        NdrConformantArrayBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char *)*points,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[282] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.MaxCount = ( unsigned long  )count;
        
        NdrConformantArrayMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                    (unsigned char *)*points,
                                    (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[282] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [propget] */ HRESULT STDMETHODCALLTYPE IProjection_get_ParameterInfo_Proxy( 
    IProjection * This,
    /* [retval][out] */ IParameterInfo **paramInfo)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(paramInfo)
        {
        MIDL_memset(
               paramInfo,
               0,
               sizeof( IParameterInfo ** ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      20);
        
        
        
        if(!paramInfo)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[132] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&paramInfo,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[252],
                                  (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[252],
                         ( void * )paramInfo);
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
    IParameterInfo *_M35;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    IParameterInfo **paramInfo;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( IParameterInfo ** )paramInfo = 0;
    RpcTryFinally
        {
        paramInfo = &_M35;
        _M35 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IProjection*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_ParameterInfo((IProjection *) ((CStdStubBuffer *)This)->pvServerObject,paramInfo);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char *)paramInfo,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[252] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char *)paramInfo,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[252] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char *)paramInfo,
                        &__MIDL_TypeFormatString.Format[252] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [propget] */ HRESULT STDMETHODCALLTYPE IProjection_get_AngularUnit_Proxy( 
    IProjection * This,
    /* [retval][out] */ IAngularUnit **unit)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(unit)
        {
        MIDL_memset(
               unit,
               0,
               sizeof( IAngularUnit ** ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      21);
        
        
        
        if(!unit)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[146] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&unit,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[296],
                                  (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[296],
                         ( void * )unit);
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
    IAngularUnit *_M36;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    IAngularUnit **unit;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( IAngularUnit ** )unit = 0;
    RpcTryFinally
        {
        unit = &_M36;
        _M36 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IProjection*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_AngularUnit((IProjection *) ((CStdStubBuffer *)This)->pvServerObject,unit);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char *)unit,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[296] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char *)unit,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[296] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char *)unit,
                        &__MIDL_TypeFormatString.Format[296] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [propput] */ HRESULT STDMETHODCALLTYPE IProjection_put_AngularUnit_Proxy( 
    IProjection * This,
    /* [in] */ IAngularUnit *unit)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      22);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrInterfacePointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                           (unsigned char *)unit,
                                           (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[300] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrInterfacePointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                         (unsigned char *)unit,
                                         (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[300] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[152] );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
    IAngularUnit *unit;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    unit = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[152] );
        
        NdrInterfacePointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char * *)&unit,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[300],
                                       (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IProjection*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> put_AngularUnit((IProjection *) ((CStdStubBuffer *)This)->pvServerObject,unit);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrInterfacePointerFree( &_StubMsg,
                                 (unsigned char *)unit,
                                 &__MIDL_TypeFormatString.Format[300] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [propget] */ HRESULT STDMETHODCALLTYPE IProjection_get_LinearUnit_Proxy( 
    IProjection * This,
    /* [retval][out] */ ILinearUnit **unit)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(unit)
        {
        MIDL_memset(
               unit,
               0,
               sizeof( ILinearUnit ** ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      23);
        
        
        
        if(!unit)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[158] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&unit,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[318],
                                  (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[318],
                         ( void * )unit);
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
    ILinearUnit *_M37;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    ILinearUnit **unit;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( ILinearUnit ** )unit = 0;
    RpcTryFinally
        {
        unit = &_M37;
        _M37 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IProjection*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_LinearUnit((IProjection *) ((CStdStubBuffer *)This)->pvServerObject,unit);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char *)unit,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[318] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char *)unit,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[318] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char *)unit,
                        &__MIDL_TypeFormatString.Format[318] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [propput] */ HRESULT STDMETHODCALLTYPE IProjection_put_LinearUnit_Proxy( 
    IProjection * This,
    /* [in] */ ILinearUnit *unit)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      24);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrInterfacePointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                           (unsigned char *)unit,
                                           (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[322] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrInterfacePointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                         (unsigned char *)unit,
                                         (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[322] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[164] );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
    ILinearUnit *unit;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    unit = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[164] );
        
        NdrInterfacePointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char * *)&unit,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[322],
                                       (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IProjection*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> put_LinearUnit((IProjection *) ((CStdStubBuffer *)This)->pvServerObject,unit);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrInterfacePointerFree( &_StubMsg,
                                 (unsigned char *)unit,
                                 &__MIDL_TypeFormatString.Format[322] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [propget] */ HRESULT STDMETHODCALLTYPE IProjection_get_Ellipsoid_Proxy( 
    IProjection * This,
    /* [retval][out] */ IEllipsoid **ellipsoid)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(ellipsoid)
        {
        MIDL_memset(
               ellipsoid,
               0,
               sizeof( IEllipsoid ** ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      25);
        
        
        
        if(!ellipsoid)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[170] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&ellipsoid,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[340],
                                  (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[340],
                         ( void * )ellipsoid);
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
    IEllipsoid *_M38;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    IEllipsoid **ellipsoid;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( IEllipsoid ** )ellipsoid = 0;
    RpcTryFinally
        {
        ellipsoid = &_M38;
        _M38 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IProjection*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_Ellipsoid((IProjection *) ((CStdStubBuffer *)This)->pvServerObject,ellipsoid);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char *)ellipsoid,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[340] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char *)ellipsoid,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[340] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char *)ellipsoid,
                        &__MIDL_TypeFormatString.Format[340] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [propput] */ HRESULT STDMETHODCALLTYPE IProjection_put_Ellipsoid_Proxy( 
    IProjection * This,
    /* [in] */ IEllipsoid *ellipsoid)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      26);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrInterfacePointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                           (unsigned char *)ellipsoid,
                                           (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[344] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrInterfacePointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                         (unsigned char *)ellipsoid,
                                         (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[344] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[176] );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
    IEllipsoid *ellipsoid;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ellipsoid = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[176] );
        
        NdrInterfacePointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char * *)&ellipsoid,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[344],
                                       (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IProjection*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> put_Ellipsoid((IProjection *) ((CStdStubBuffer *)This)->pvServerObject,ellipsoid);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrInterfacePointerFree( &_StubMsg,
                                 (unsigned char *)ellipsoid,
                                 &__MIDL_TypeFormatString.Format[344] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IProjectedCoordinateSystem_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IProjectedCoordinateSystem_ProxyInfo;


/* [propget] */ HRESULT STDMETHODCALLTYPE IProjectedCoordinateSystem_get_Usage_Proxy( 
    IProjectedCoordinateSystem * This,
    /* [retval][out] */ BSTR *usage)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(usage)
        {
        MIDL_memset(
               usage,
               0,
               sizeof( BSTR  ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      16);
        
        
        
        if(!usage)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[0] );
            
            NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char * *)&usage,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[30],
                                      (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[2],
                         ( void * )usage);
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
    BSTR *usage;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( BSTR * )usage = 0;
    RpcTryFinally
        {
        usage = &_M39;
        MIDL_memset(
               usage,
               0,
               sizeof( BSTR  ));
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IProjectedCoordinateSystem*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_Usage((IProjectedCoordinateSystem *) ((CStdStubBuffer *)This)->pvServerObject,usage);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char *)usage,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[30] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                (unsigned char *)usage,
                                (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[30] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char *)usage,
                        &__MIDL_TypeFormatString.Format[2] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [propput] */ HRESULT STDMETHODCALLTYPE IProjectedCoordinateSystem_put_Usage_Proxy( 
    IProjectedCoordinateSystem * This,
    /* [in] */ BSTR usage)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      17);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char *)&usage,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[44] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                    (unsigned char *)&usage,
                                    (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[44] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[6] );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
    void *_p_usage;
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
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[6] );
        
        NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&_p_usage,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[44],
                                  (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IProjectedCoordinateSystem*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> put_Usage((IProjectedCoordinateSystem *) ((CStdStubBuffer *)This)->pvServerObject,usage);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrUserMarshalFree( &_StubMsg,
                            (unsigned char *)&usage,
                            &__MIDL_TypeFormatString.Format[44] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [propget] */ HRESULT STDMETHODCALLTYPE IProjectedCoordinateSystem_get_GeographicCoordinateSystem_Proxy( 
    IProjectedCoordinateSystem * This,
    /* [retval][out] */ IGeographicCoordinateSystem **gcs)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(gcs)
        {
        MIDL_memset(
               gcs,
               0,
               sizeof( IGeographicCoordinateSystem ** ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      18);
        
        
        
        if(!gcs)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[120] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&gcs,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[230],
                                  (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[230],
                         ( void * )gcs);
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
    IGeographicCoordinateSystem *_M40;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    IGeographicCoordinateSystem **gcs;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( IGeographicCoordinateSystem ** )gcs = 0;
    RpcTryFinally
        {
        gcs = &_M40;
        _M40 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IProjectedCoordinateSystem*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_GeographicCoordinateSystem((IProjectedCoordinateSystem *) ((CStdStubBuffer *)This)->pvServerObject,gcs);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char *)gcs,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[230] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char *)gcs,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[230] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char *)gcs,
                        &__MIDL_TypeFormatString.Format[230] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [propput] */ HRESULT STDMETHODCALLTYPE IProjectedCoordinateSystem_put_GeographicCoordinateSystem_Proxy( 
    IProjectedCoordinateSystem * This,
    /* [in] */ IGeographicCoordinateSystem *gcs)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      19);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrInterfacePointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                           (unsigned char *)gcs,
                                           (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[234] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrInterfacePointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                         (unsigned char *)gcs,
                                         (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[234] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[126] );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
    IGeographicCoordinateSystem *gcs;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    gcs = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[126] );
        
        NdrInterfacePointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char * *)&gcs,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[234],
                                       (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IProjectedCoordinateSystem*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> put_GeographicCoordinateSystem((IProjectedCoordinateSystem *) ((CStdStubBuffer *)This)->pvServerObject,gcs);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrInterfacePointerFree( &_StubMsg,
                                 (unsigned char *)gcs,
                                 &__MIDL_TypeFormatString.Format[234] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [propget] */ HRESULT STDMETHODCALLTYPE IProjectedCoordinateSystem_get_LinearUnit_Proxy( 
    IProjectedCoordinateSystem * This,
    /* [retval][out] */ ILinearUnit **unit)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(unit)
        {
        MIDL_memset(
               unit,
               0,
               sizeof( ILinearUnit ** ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      20);
        
        
        
        if(!unit)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[158] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&unit,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[318],
                                  (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[318],
                         ( void * )unit);
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
    ILinearUnit *_M41;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    ILinearUnit **unit;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( ILinearUnit ** )unit = 0;
    RpcTryFinally
        {
        unit = &_M41;
        _M41 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IProjectedCoordinateSystem*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_LinearUnit((IProjectedCoordinateSystem *) ((CStdStubBuffer *)This)->pvServerObject,unit);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char *)unit,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[318] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char *)unit,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[318] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char *)unit,
                        &__MIDL_TypeFormatString.Format[318] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [propput] */ HRESULT STDMETHODCALLTYPE IProjectedCoordinateSystem_put_LinearUnit_Proxy( 
    IProjectedCoordinateSystem * This,
    /* [in] */ ILinearUnit *unit)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      21);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrInterfacePointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                           (unsigned char *)unit,
                                           (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[322] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrInterfacePointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                         (unsigned char *)unit,
                                         (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[322] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[164] );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
    ILinearUnit *unit;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    unit = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[164] );
        
        NdrInterfacePointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char * *)&unit,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[322],
                                       (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IProjectedCoordinateSystem*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> put_LinearUnit((IProjectedCoordinateSystem *) ((CStdStubBuffer *)This)->pvServerObject,unit);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrInterfacePointerFree( &_StubMsg,
                                 (unsigned char *)unit,
                                 &__MIDL_TypeFormatString.Format[322] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [propget] */ HRESULT STDMETHODCALLTYPE IProjectedCoordinateSystem_get_Projection_Proxy( 
    IProjectedCoordinateSystem * This,
    /* [retval][out] */ IProjection **projection)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(projection)
        {
        MIDL_memset(
               projection,
               0,
               sizeof( IProjection ** ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      22);
        
        
        
        if(!projection)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[182] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&projection,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[362],
                                  (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
                         ( void * )projection);
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
    IProjection *_M42;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    IProjection **projection;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( IProjection ** )projection = 0;
    RpcTryFinally
        {
        projection = &_M42;
        _M42 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IProjectedCoordinateSystem*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_Projection((IProjectedCoordinateSystem *) ((CStdStubBuffer *)This)->pvServerObject,projection);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char *)projection,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[362] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char *)projection,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[362] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char *)projection,
                        &__MIDL_TypeFormatString.Format[362] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [propput] */ HRESULT STDMETHODCALLTYPE IProjectedCoordinateSystem_put_Projection_Proxy( 
    IProjectedCoordinateSystem * This,
    /* [in] */ IProjection *projection)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      23);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrInterfacePointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                           (unsigned char *)projection,
                                           (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[366] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrInterfacePointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                         (unsigned char *)projection,
                                         (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[366] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[188] );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
    IProjection *projection;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    projection = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[188] );
        
        NdrInterfacePointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char * *)&projection,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[366],
                                       (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IProjectedCoordinateSystem*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> put_Projection((IProjectedCoordinateSystem *) ((CStdStubBuffer *)This)->pvServerObject,projection);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrInterfacePointerFree( &_StubMsg,
                                 (unsigned char *)projection,
                                 &__MIDL_TypeFormatString.Format[366] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [propget] */ HRESULT STDMETHODCALLTYPE IProjectedCoordinateSystem_get_ParameterInfo_Proxy( 
    IProjectedCoordinateSystem * This,
    /* [retval][out] */ IParameterInfo **paramInfo)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(paramInfo)
        {
        MIDL_memset(
               paramInfo,
               0,
               sizeof( IParameterInfo ** ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      24);
        
        
        
        if(!paramInfo)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[132] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&paramInfo,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[252],
                                  (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[252],
                         ( void * )paramInfo);
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
    IParameterInfo *_M43;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    IParameterInfo **paramInfo;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( IParameterInfo ** )paramInfo = 0;
    RpcTryFinally
        {
        paramInfo = &_M43;
        _M43 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IProjectedCoordinateSystem*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_ParameterInfo((IProjectedCoordinateSystem *) ((CStdStubBuffer *)This)->pvServerObject,paramInfo);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char *)paramInfo,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[252] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char *)paramInfo,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[252] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char *)paramInfo,
                        &__MIDL_TypeFormatString.Format[252] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


HRESULT STDMETHODCALLTYPE IProjectedCoordinateSystem_Forward_Proxy( 
    IProjectedCoordinateSystem * This,
    /* [in] */ long count,
    /* [size_is][out][in] */ WKSPoint points[  ])
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      25);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 8;
            _StubMsg.MaxCount = ( unsigned long  )count;
            
            NdrConformantArrayBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                          (unsigned char *)points,
                                          (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[282] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            *(( long * )_StubMsg.Buffer)++ = count;
            
            _StubMsg.MaxCount = ( unsigned long  )count;
            
            NdrConformantArrayMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                        (unsigned char *)points,
                                        (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[282] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[138] );
            
            NdrConformantArrayUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                          (unsigned char * *)&points,
                                          (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[282],
                                          (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _StubMsg.MaxCount = ( unsigned long  )count;
        
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[282],
                         ( void * )points);
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
    WKSPoint ( *points )[  ];
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    count = 0;
    points = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[138] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        
        if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
            {
            RpcRaiseException(RPC_X_BAD_STUB_DATA);
            }
        count = *(( long * )_StubMsg.Buffer)++;
        
        NdrConformantArrayUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char * *)&points,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[282],
                                      (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IProjectedCoordinateSystem*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> Forward(
           (IProjectedCoordinateSystem *) ((CStdStubBuffer *)This)->pvServerObject,
           count,
           *points);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        _StubMsg.MaxCount = ( unsigned long  )count;
        
        NdrConformantArrayBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char *)*points,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[282] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.MaxCount = ( unsigned long  )count;
        
        NdrConformantArrayMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                    (unsigned char *)*points,
                                    (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[282] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


HRESULT STDMETHODCALLTYPE IProjectedCoordinateSystem_Inverse_Proxy( 
    IProjectedCoordinateSystem * This,
    /* [in] */ long count,
    /* [size_is][out][in] */ WKSPoint points[  ])
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      26);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 8;
            _StubMsg.MaxCount = ( unsigned long  )count;
            
            NdrConformantArrayBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                          (unsigned char *)points,
                                          (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[282] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            *(( long * )_StubMsg.Buffer)++ = count;
            
            _StubMsg.MaxCount = ( unsigned long  )count;
            
            NdrConformantArrayMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                        (unsigned char *)points,
                                        (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[282] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[138] );
            
            NdrConformantArrayUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                          (unsigned char * *)&points,
                                          (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[282],
                                          (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _StubMsg.MaxCount = ( unsigned long  )count;
        
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[282],
                         ( void * )points);
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
    WKSPoint ( *points )[  ];
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    count = 0;
    points = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[138] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        
        if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
            {
            RpcRaiseException(RPC_X_BAD_STUB_DATA);
            }
        count = *(( long * )_StubMsg.Buffer)++;
        
        NdrConformantArrayUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char * *)&points,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[282],
                                      (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IProjectedCoordinateSystem*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> Inverse(
           (IProjectedCoordinateSystem *) ((CStdStubBuffer *)This)->pvServerObject,
           count,
           *points);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        _StubMsg.MaxCount = ( unsigned long  )count;
        
        NdrConformantArrayBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char *)*points,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[282] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.MaxCount = ( unsigned long  )count;
        
        NdrConformantArrayMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                    (unsigned char *)*points,
                                    (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[282] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO ISpatialReferenceFactory_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO ISpatialReferenceFactory_ProxyInfo;


HRESULT STDMETHODCALLTYPE ISpatialReferenceFactory_CreateFromWKT_Proxy( 
    ISpatialReferenceFactory * This,
    /* [in] */ BSTR wktSpatialReference,
    /* [out] */ ISpatialReference **sref)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(sref)
        {
        MIDL_memset(
               sref,
               0,
               sizeof( ISpatialReference ** ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      3);
        
        
        
        if(!sref)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char *)&wktSpatialReference,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[44] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                    (unsigned char *)&wktSpatialReference,
                                    (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[44] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[194] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&sref,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[384],
                                  (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
                         ( void * )sref);
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
    ISpatialReference *_M46;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    void *_p_wktSpatialReference;
    ISpatialReference **sref;
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
    ( ISpatialReference ** )sref = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[194] );
        
        NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&_p_wktSpatialReference,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[44],
                                  (unsigned char)0 );
        
        sref = &_M46;
        _M46 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISpatialReferenceFactory*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> CreateFromWKT(
                 (ISpatialReferenceFactory *) ((CStdStubBuffer *)This)->pvServerObject,
                 wktSpatialReference,
                 sref);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char *)sref,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[384] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char *)sref,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[384] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrUserMarshalFree( &_StubMsg,
                            (unsigned char *)&wktSpatialReference,
                            &__MIDL_TypeFormatString.Format[44] );
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char *)sref,
                        &__MIDL_TypeFormatString.Format[384] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO ISpatialReferenceAuthorityFactory_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO ISpatialReferenceAuthorityFactory_ProxyInfo;


/* [propget] */ HRESULT STDMETHODCALLTYPE ISpatialReferenceAuthorityFactory_get_Authority_Proxy( 
    ISpatialReferenceAuthorityFactory * This,
    /* [out] */ BSTR *authority)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(authority)
        {
        MIDL_memset(
               authority,
               0,
               sizeof( BSTR  ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      3);
        
        
        
        if(!authority)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[0] );
            
            NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char * *)&authority,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[30],
                                      (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[2],
                         ( void * )authority);
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
    BSTR *authority;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( BSTR * )authority = 0;
    RpcTryFinally
        {
        authority = &_M47;
        MIDL_memset(
               authority,
               0,
               sizeof( BSTR  ));
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISpatialReferenceAuthorityFactory*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_Authority((ISpatialReferenceAuthorityFactory *) ((CStdStubBuffer *)This)->pvServerObject,authority);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char *)authority,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[30] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                (unsigned char *)authority,
                                (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[30] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char *)authority,
                        &__MIDL_TypeFormatString.Format[2] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


HRESULT STDMETHODCALLTYPE ISpatialReferenceAuthorityFactory_CreateProjectedCoordinateSystem_Proxy( 
    ISpatialReferenceAuthorityFactory * This,
    /* [in] */ long code,
    /* [out] */ IProjectedCoordinateSystem **pcs)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(pcs)
        {
        MIDL_memset(
               pcs,
               0,
               sizeof( IProjectedCoordinateSystem ** ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      4);
        
        
        
        if(!pcs)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 8;
            NdrProxyGetBuffer(This, &_StubMsg);
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            *(( long * )_StubMsg.Buffer)++ = code;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[204] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&pcs,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[406],
                                  (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[406],
                         ( void * )pcs);
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
    IProjectedCoordinateSystem *_M48;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    long code;
    IProjectedCoordinateSystem **pcs;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    code = 0;
    ( IProjectedCoordinateSystem ** )pcs = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[204] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        
        if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
            {
            RpcRaiseException(RPC_X_BAD_STUB_DATA);
            }
        code = *(( long * )_StubMsg.Buffer)++;
        
        pcs = &_M48;
        _M48 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISpatialReferenceAuthorityFactory*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> CreateProjectedCoordinateSystem(
                                   (ISpatialReferenceAuthorityFactory *) ((CStdStubBuffer *)This)->pvServerObject,
                                   code,
                                   pcs);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char *)pcs,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[406] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char *)pcs,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[406] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char *)pcs,
                        &__MIDL_TypeFormatString.Format[406] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


HRESULT STDMETHODCALLTYPE ISpatialReferenceAuthorityFactory_CreateGeographicCoordinateSystem_Proxy( 
    ISpatialReferenceAuthorityFactory * This,
    /* [in] */ long code,
    /* [out] */ IGeographicCoordinateSystem **gcs)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(gcs)
        {
        MIDL_memset(
               gcs,
               0,
               sizeof( IGeographicCoordinateSystem ** ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      5);
        
        
        
        if(!gcs)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 8;
            NdrProxyGetBuffer(This, &_StubMsg);
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            *(( long * )_StubMsg.Buffer)++ = code;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[212] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&gcs,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[230],
                                  (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[230],
                         ( void * )gcs);
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
    IGeographicCoordinateSystem *_M49;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    long code;
    IGeographicCoordinateSystem **gcs;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    code = 0;
    ( IGeographicCoordinateSystem ** )gcs = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[212] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        
        if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
            {
            RpcRaiseException(RPC_X_BAD_STUB_DATA);
            }
        code = *(( long * )_StubMsg.Buffer)++;
        
        gcs = &_M49;
        _M49 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISpatialReferenceAuthorityFactory*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> CreateGeographicCoordinateSystem(
                                    (ISpatialReferenceAuthorityFactory *) ((CStdStubBuffer *)This)->pvServerObject,
                                    code,
                                    gcs);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char *)gcs,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[230] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char *)gcs,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[230] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char *)gcs,
                        &__MIDL_TypeFormatString.Format[230] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


HRESULT STDMETHODCALLTYPE ISpatialReferenceAuthorityFactory_CreateProjection_Proxy( 
    ISpatialReferenceAuthorityFactory * This,
    /* [in] */ long code,
    /* [out] */ IProjection **projection)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(projection)
        {
        MIDL_memset(
               projection,
               0,
               sizeof( IProjection ** ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      6);
        
        
        
        if(!projection)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 8;
            NdrProxyGetBuffer(This, &_StubMsg);
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            *(( long * )_StubMsg.Buffer)++ = code;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[220] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&projection,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[362],
                                  (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
                         ( void * )projection);
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
    IProjection *_M50;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    long code;
    IProjection **projection;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    code = 0;
    ( IProjection ** )projection = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[220] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        
        if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
            {
            RpcRaiseException(RPC_X_BAD_STUB_DATA);
            }
        code = *(( long * )_StubMsg.Buffer)++;
        
        projection = &_M50;
        _M50 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISpatialReferenceAuthorityFactory*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> CreateProjection(
                    (ISpatialReferenceAuthorityFactory *) ((CStdStubBuffer *)This)->pvServerObject,
                    code,
                    projection);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char *)projection,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[362] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char *)projection,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[362] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char *)projection,
                        &__MIDL_TypeFormatString.Format[362] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


HRESULT STDMETHODCALLTYPE ISpatialReferenceAuthorityFactory_CreateGeographicTransform_Proxy( 
    ISpatialReferenceAuthorityFactory * This,
    /* [in] */ long code,
    /* [out] */ IGeographicTransform **gt)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(gt)
        {
        MIDL_memset(
               gt,
               0,
               sizeof( IGeographicTransform ** ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      7);
        
        
        
        if(!gt)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 8;
            NdrProxyGetBuffer(This, &_StubMsg);
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            *(( long * )_StubMsg.Buffer)++ = code;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[228] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&gt,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[428],
                                  (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
                         ( void * )gt);
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
    IGeographicTransform *_M51;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    long code;
    IGeographicTransform **gt;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    code = 0;
    ( IGeographicTransform ** )gt = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[228] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        
        if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
            {
            RpcRaiseException(RPC_X_BAD_STUB_DATA);
            }
        code = *(( long * )_StubMsg.Buffer)++;
        
        gt = &_M51;
        _M51 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISpatialReferenceAuthorityFactory*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> CreateGeographicTransform(
                             (ISpatialReferenceAuthorityFactory *) ((CStdStubBuffer *)This)->pvServerObject,
                             code,
                             gt);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char *)gt,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[428] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char *)gt,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[428] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char *)gt,
                        &__MIDL_TypeFormatString.Format[428] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


HRESULT STDMETHODCALLTYPE ISpatialReferenceAuthorityFactory_CreateHorizontalDatum_Proxy( 
    ISpatialReferenceAuthorityFactory * This,
    /* [in] */ long code,
    /* [out] */ IHorizontalDatum **datum)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(datum)
        {
        MIDL_memset(
               datum,
               0,
               sizeof( IHorizontalDatum ** ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      8);
        
        
        
        if(!datum)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 8;
            NdrProxyGetBuffer(This, &_StubMsg);
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            *(( long * )_StubMsg.Buffer)++ = code;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[236] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&datum,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[450],
                                  (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[450],
                         ( void * )datum);
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
    IHorizontalDatum *_M52;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    long code;
    IHorizontalDatum **datum;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    code = 0;
    ( IHorizontalDatum ** )datum = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[236] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        
        if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
            {
            RpcRaiseException(RPC_X_BAD_STUB_DATA);
            }
        code = *(( long * )_StubMsg.Buffer)++;
        
        datum = &_M52;
        _M52 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISpatialReferenceAuthorityFactory*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> CreateHorizontalDatum(
                         (ISpatialReferenceAuthorityFactory *) ((CStdStubBuffer *)This)->pvServerObject,
                         code,
                         datum);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char *)datum,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[450] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char *)datum,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[450] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char *)datum,
                        &__MIDL_TypeFormatString.Format[450] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


HRESULT STDMETHODCALLTYPE ISpatialReferenceAuthorityFactory_CreateEllipsoid_Proxy( 
    ISpatialReferenceAuthorityFactory * This,
    /* [in] */ long code,
    /* [out] */ IEllipsoid **ellipsoid)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(ellipsoid)
        {
        MIDL_memset(
               ellipsoid,
               0,
               sizeof( IEllipsoid ** ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      9);
        
        
        
        if(!ellipsoid)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 8;
            NdrProxyGetBuffer(This, &_StubMsg);
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            *(( long * )_StubMsg.Buffer)++ = code;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[244] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&ellipsoid,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[472],
                                  (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[472],
                         ( void * )ellipsoid);
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
    IEllipsoid *_M53;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    long code;
    IEllipsoid **ellipsoid;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    code = 0;
    ( IEllipsoid ** )ellipsoid = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[244] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        
        if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
            {
            RpcRaiseException(RPC_X_BAD_STUB_DATA);
            }
        code = *(( long * )_StubMsg.Buffer)++;
        
        ellipsoid = &_M53;
        _M53 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISpatialReferenceAuthorityFactory*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> CreateEllipsoid(
                   (ISpatialReferenceAuthorityFactory *) ((CStdStubBuffer *)This)->pvServerObject,
                   code,
                   ellipsoid);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char *)ellipsoid,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[472] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char *)ellipsoid,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[472] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char *)ellipsoid,
                        &__MIDL_TypeFormatString.Format[472] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


HRESULT STDMETHODCALLTYPE ISpatialReferenceAuthorityFactory_CreatePrimeMeridian_Proxy( 
    ISpatialReferenceAuthorityFactory * This,
    /* [in] */ long code,
    /* [out] */ IPrimeMeridian **prmMerid)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(prmMerid)
        {
        MIDL_memset(
               prmMerid,
               0,
               sizeof( IPrimeMeridian ** ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      10);
        
        
        
        if(!prmMerid)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 8;
            NdrProxyGetBuffer(This, &_StubMsg);
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            *(( long * )_StubMsg.Buffer)++ = code;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[252] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&prmMerid,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[494],
                                  (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[494],
                         ( void * )prmMerid);
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
    IPrimeMeridian *_M54;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    long code;
    IPrimeMeridian **prmMerid;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    code = 0;
    ( IPrimeMeridian ** )prmMerid = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[252] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        
        if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
            {
            RpcRaiseException(RPC_X_BAD_STUB_DATA);
            }
        code = *(( long * )_StubMsg.Buffer)++;
        
        prmMerid = &_M54;
        _M54 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISpatialReferenceAuthorityFactory*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> CreatePrimeMeridian(
                       (ISpatialReferenceAuthorityFactory *) ((CStdStubBuffer *)This)->pvServerObject,
                       code,
                       prmMerid);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char *)prmMerid,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[494] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char *)prmMerid,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[494] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char *)prmMerid,
                        &__MIDL_TypeFormatString.Format[494] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


HRESULT STDMETHODCALLTYPE ISpatialReferenceAuthorityFactory_CreateLinearUnit_Proxy( 
    ISpatialReferenceAuthorityFactory * This,
    /* [in] */ long code,
    /* [out] */ ILinearUnit **unit)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(unit)
        {
        MIDL_memset(
               unit,
               0,
               sizeof( ILinearUnit ** ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      11);
        
        
        
        if(!unit)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 8;
            NdrProxyGetBuffer(This, &_StubMsg);
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            *(( long * )_StubMsg.Buffer)++ = code;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[260] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&unit,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[516],
                                  (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[516],
                         ( void * )unit);
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
    ILinearUnit *_M55;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    long code;
    ILinearUnit **unit;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    code = 0;
    ( ILinearUnit ** )unit = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[260] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        
        if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
            {
            RpcRaiseException(RPC_X_BAD_STUB_DATA);
            }
        code = *(( long * )_StubMsg.Buffer)++;
        
        unit = &_M55;
        _M55 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISpatialReferenceAuthorityFactory*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> CreateLinearUnit(
                    (ISpatialReferenceAuthorityFactory *) ((CStdStubBuffer *)This)->pvServerObject,
                    code,
                    unit);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char *)unit,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[516] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char *)unit,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[516] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char *)unit,
                        &__MIDL_TypeFormatString.Format[516] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


HRESULT STDMETHODCALLTYPE ISpatialReferenceAuthorityFactory_CreateAngularUnit_Proxy( 
    ISpatialReferenceAuthorityFactory * This,
    /* [in] */ long code,
    /* [out] */ IAngularUnit **unit)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(unit)
        {
        MIDL_memset(
               unit,
               0,
               sizeof( IAngularUnit ** ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      12);
        
        
        
        if(!unit)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 8;
            NdrProxyGetBuffer(This, &_StubMsg);
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            *(( long * )_StubMsg.Buffer)++ = code;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[268] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&unit,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[538],
                                  (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            
            if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
                {
                RpcRaiseException(RPC_X_BAD_STUB_DATA);
                }
            _RetVal = *(( HRESULT * )_StubMsg.Buffer)++;
            
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[538],
                         ( void * )unit);
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
    IAngularUnit *_M56;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    long code;
    IAngularUnit **unit;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    code = 0;
    ( IAngularUnit ** )unit = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[268] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        
        if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
            {
            RpcRaiseException(RPC_X_BAD_STUB_DATA);
            }
        code = *(( long * )_StubMsg.Buffer)++;
        
        unit = &_M56;
        _M56 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISpatialReferenceAuthorityFactory*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> CreateAngularUnit(
                     (ISpatialReferenceAuthorityFactory *) ((CStdStubBuffer *)This)->pvServerObject,
                     code,
                     unit);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char *)unit,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[538] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char *)unit,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[538] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char *)unit,
                        &__MIDL_TypeFormatString.Format[538] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


extern const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ];

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
			0x1,		/* x86 stack size = 1 */
/*  2 */	NdrFcShort( 0x2 ),	/* Type Offset=2 */
/*  4 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/*  6 */	
			0x4d,		/* FC_IN_PARAM */
			0x1,		/* x86 stack size = 1 */
/*  8 */	NdrFcShort( 0x2c ),	/* Type Offset=44 */
/* 10 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 12 */	
			0x51,		/* FC_OUT_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 14 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */
/* 16 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 18 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 20 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 22 */	
			0x51,		/* FC_OUT_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 24 */	NdrFcShort( 0x3a ),	/* Type Offset=58 */
/* 26 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 28 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0xc,		/* FC_DOUBLE */
/* 30 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 32 */	
			0x51,		/* FC_OUT_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 34 */	NdrFcShort( 0x3e ),	/* Type Offset=62 */
/* 36 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 38 */	
			0x4d,		/* FC_IN_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 40 */	NdrFcShort( 0x42 ),	/* Type Offset=66 */
/* 42 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 44 */	
			0x51,		/* FC_OUT_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 46 */	NdrFcShort( 0x54 ),	/* Type Offset=84 */
/* 48 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 50 */	
			0x4d,		/* FC_IN_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 52 */	NdrFcShort( 0x58 ),	/* Type Offset=88 */
/* 54 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 56 */	
			0x51,		/* FC_OUT_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 58 */	NdrFcShort( 0x6a ),	/* Type Offset=106 */
/* 60 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 62 */	
			0x4d,		/* FC_IN_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 64 */	NdrFcShort( 0x6e ),	/* Type Offset=110 */
/* 66 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 68 */	
			0x51,		/* FC_OUT_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 70 */	NdrFcShort( 0x80 ),	/* Type Offset=128 */
/* 72 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 74 */	
			0x4d,		/* FC_IN_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 76 */	NdrFcShort( 0x84 ),	/* Type Offset=132 */
/* 78 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 80 */	
			0x51,		/* FC_OUT_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 82 */	NdrFcShort( 0x96 ),	/* Type Offset=150 */
/* 84 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 86 */	
			0x4d,		/* FC_IN_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 88 */	NdrFcShort( 0x9a ),	/* Type Offset=154 */
/* 90 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 92 */	
			0x4d,		/* FC_IN_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 94 */	NdrFcShort( 0xac ),	/* Type Offset=172 */
/* 96 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 98 */	
			0x51,		/* FC_OUT_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 100 */	NdrFcShort( 0xbe ),	/* Type Offset=190 */
/* 102 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 104 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 106 */	
			0x51,		/* FC_OUT_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 108 */	NdrFcShort( 0xd4 ),	/* Type Offset=212 */
/* 110 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 112 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 114 */	
			0x4d,		/* FC_IN_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 116 */	NdrFcShort( 0xd4 ),	/* Type Offset=212 */
/* 118 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 120 */	
			0x51,		/* FC_OUT_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 122 */	NdrFcShort( 0xe6 ),	/* Type Offset=230 */
/* 124 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 126 */	
			0x4d,		/* FC_IN_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 128 */	NdrFcShort( 0xea ),	/* Type Offset=234 */
/* 130 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 132 */	
			0x51,		/* FC_OUT_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 134 */	NdrFcShort( 0xfc ),	/* Type Offset=252 */
/* 136 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 138 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 140 */	
			0x50,		/* FC_IN_OUT_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 142 */	NdrFcShort( 0x11a ),	/* Type Offset=282 */
/* 144 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 146 */	
			0x51,		/* FC_OUT_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 148 */	NdrFcShort( 0x128 ),	/* Type Offset=296 */
/* 150 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 152 */	
			0x4d,		/* FC_IN_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 154 */	NdrFcShort( 0x12c ),	/* Type Offset=300 */
/* 156 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 158 */	
			0x51,		/* FC_OUT_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 160 */	NdrFcShort( 0x13e ),	/* Type Offset=318 */
/* 162 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 164 */	
			0x4d,		/* FC_IN_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 166 */	NdrFcShort( 0x142 ),	/* Type Offset=322 */
/* 168 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 170 */	
			0x51,		/* FC_OUT_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 172 */	NdrFcShort( 0x154 ),	/* Type Offset=340 */
/* 174 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 176 */	
			0x4d,		/* FC_IN_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 178 */	NdrFcShort( 0x158 ),	/* Type Offset=344 */
/* 180 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 182 */	
			0x51,		/* FC_OUT_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 184 */	NdrFcShort( 0x16a ),	/* Type Offset=362 */
/* 186 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 188 */	
			0x4d,		/* FC_IN_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 190 */	NdrFcShort( 0x16e ),	/* Type Offset=366 */
/* 192 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 194 */	
			0x4d,		/* FC_IN_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 196 */	NdrFcShort( 0x2c ),	/* Type Offset=44 */
/* 198 */	
			0x51,		/* FC_OUT_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 200 */	NdrFcShort( 0x180 ),	/* Type Offset=384 */
/* 202 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 204 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 206 */	
			0x51,		/* FC_OUT_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 208 */	NdrFcShort( 0x196 ),	/* Type Offset=406 */
/* 210 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 212 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 214 */	
			0x51,		/* FC_OUT_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 216 */	NdrFcShort( 0xe6 ),	/* Type Offset=230 */
/* 218 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 220 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 222 */	
			0x51,		/* FC_OUT_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 224 */	NdrFcShort( 0x16a ),	/* Type Offset=362 */
/* 226 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 228 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 230 */	
			0x51,		/* FC_OUT_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 232 */	NdrFcShort( 0x1ac ),	/* Type Offset=428 */
/* 234 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 236 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 238 */	
			0x51,		/* FC_OUT_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 240 */	NdrFcShort( 0x1c2 ),	/* Type Offset=450 */
/* 242 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 244 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 246 */	
			0x51,		/* FC_OUT_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 248 */	NdrFcShort( 0x1d8 ),	/* Type Offset=472 */
/* 250 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 252 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 254 */	
			0x51,		/* FC_OUT_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 256 */	NdrFcShort( 0x1ee ),	/* Type Offset=494 */
/* 258 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 260 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 262 */	
			0x51,		/* FC_OUT_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 264 */	NdrFcShort( 0x204 ),	/* Type Offset=516 */
/* 266 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 268 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 270 */	
			0x51,		/* FC_OUT_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 272 */	NdrFcShort( 0x21a ),	/* Type Offset=538 */
/* 274 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */

			0x0
        }
    };

static const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */
/*  2 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/*  4 */	NdrFcShort( 0x1a ),	/* Offset= 26 (30) */
/*  6 */	
			0x13, 0x0,	/* FC_OP */
/*  8 */	NdrFcShort( 0xc ),	/* Offset= 12 (20) */
/* 10 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 12 */	NdrFcShort( 0x2 ),	/* 2 */
/* 14 */	0x9,		/* Corr desc: FC_ULONG */
			0x0,		/*  */
/* 16 */	NdrFcShort( 0xfffc ),	/* -4 */
/* 18 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 20 */	
			0x17,		/* FC_CSTRUCT */
			0x3,		/* 3 */
/* 22 */	NdrFcShort( 0x8 ),	/* 8 */
/* 24 */	NdrFcShort( 0xfffffff2 ),	/* Offset= -14 (10) */
/* 26 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 28 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 30 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 32 */	NdrFcShort( 0x0 ),	/* 0 */
/* 34 */	NdrFcShort( 0x4 ),	/* 4 */
/* 36 */	NdrFcShort( 0x0 ),	/* 0 */
/* 38 */	NdrFcShort( 0xffffffe0 ),	/* Offset= -32 (6) */
/* 40 */	
			0x12, 0x0,	/* FC_UP */
/* 42 */	NdrFcShort( 0xffffffea ),	/* Offset= -22 (20) */
/* 44 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 46 */	NdrFcShort( 0x0 ),	/* 0 */
/* 48 */	NdrFcShort( 0x4 ),	/* 4 */
/* 50 */	NdrFcShort( 0x0 ),	/* 0 */
/* 52 */	NdrFcShort( 0xfffffff4 ),	/* Offset= -12 (40) */
/* 54 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 56 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 58 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 60 */	0xc,		/* FC_DOUBLE */
			0x5c,		/* FC_PAD */
/* 62 */	
			0x11, 0x14,	/* FC_RP [alloced_on_stack] [pointer_deref] */
/* 64 */	NdrFcShort( 0x2 ),	/* Offset= 2 (66) */
/* 66 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 68 */	NdrFcLong( 0x80855df0 ),	/* -2138743312 */
/* 72 */	NdrFcShort( 0xfe1d ),	/* -483 */
/* 74 */	NdrFcShort( 0x11d0 ),	/* 4560 */
/* 76 */	0xad,		/* 173 */
			0x87,		/* 135 */
/* 78 */	0x8,		/* 8 */
			0x0,		/* 0 */
/* 80 */	0x9,		/* 9 */
			0xb6,		/* 182 */
/* 82 */	0xf2,		/* 242 */
			0x2b,		/* 43 */
/* 84 */	
			0x11, 0x14,	/* FC_RP [alloced_on_stack] [pointer_deref] */
/* 86 */	NdrFcShort( 0x2 ),	/* Offset= 2 (88) */
/* 88 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 90 */	NdrFcLong( 0xce7266c0 ),	/* -831363392 */
/* 94 */	NdrFcShort( 0xfe1d ),	/* -483 */
/* 96 */	NdrFcShort( 0x11d0 ),	/* 4560 */
/* 98 */	0xad,		/* 173 */
			0x87,		/* 135 */
/* 100 */	0x8,		/* 8 */
			0x0,		/* 0 */
/* 102 */	0x9,		/* 9 */
			0xb6,		/* 182 */
/* 104 */	0xf2,		/* 242 */
			0x2b,		/* 43 */
/* 106 */	
			0x11, 0x14,	/* FC_RP [alloced_on_stack] [pointer_deref] */
/* 108 */	NdrFcShort( 0x2 ),	/* Offset= 2 (110) */
/* 110 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 112 */	NdrFcLong( 0x4febc550 ),	/* 1340851536 */
/* 116 */	NdrFcShort( 0xfe1d ),	/* -483 */
/* 118 */	NdrFcShort( 0x11d0 ),	/* 4560 */
/* 120 */	0xad,		/* 173 */
			0x87,		/* 135 */
/* 122 */	0x8,		/* 8 */
			0x0,		/* 0 */
/* 124 */	0x9,		/* 9 */
			0xb6,		/* 182 */
/* 126 */	0xf2,		/* 242 */
			0x2b,		/* 43 */
/* 128 */	
			0x11, 0x14,	/* FC_RP [alloced_on_stack] [pointer_deref] */
/* 130 */	NdrFcShort( 0x2 ),	/* Offset= 2 (132) */
/* 132 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 134 */	NdrFcLong( 0xf699c510 ),	/* -157694704 */
/* 138 */	NdrFcShort( 0xfe1d ),	/* -483 */
/* 140 */	NdrFcShort( 0x11d0 ),	/* 4560 */
/* 142 */	0xad,		/* 173 */
			0x87,		/* 135 */
/* 144 */	0x8,		/* 8 */
			0x0,		/* 0 */
/* 146 */	0x9,		/* 9 */
			0xb6,		/* 182 */
/* 148 */	0xf2,		/* 242 */
			0x2b,		/* 43 */
/* 150 */	
			0x11, 0x14,	/* FC_RP [alloced_on_stack] [pointer_deref] */
/* 152 */	NdrFcShort( 0x2 ),	/* Offset= 2 (154) */
/* 154 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 156 */	NdrFcLong( 0x15129940 ),	/* 353540416 */
/* 160 */	NdrFcShort( 0xfe1e ),	/* -482 */
/* 162 */	NdrFcShort( 0x11d0 ),	/* 4560 */
/* 164 */	0xad,		/* 173 */
			0x87,		/* 135 */
/* 166 */	0x8,		/* 8 */
			0x0,		/* 0 */
/* 168 */	0x9,		/* 9 */
			0xb6,		/* 182 */
/* 170 */	0xf2,		/* 242 */
			0x2b,		/* 43 */
/* 172 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 174 */	NdrFcLong( 0x221733b0 ),	/* 571945904 */
/* 178 */	NdrFcShort( 0xfe1d ),	/* -483 */
/* 180 */	NdrFcShort( 0x11d0 ),	/* 4560 */
/* 182 */	0xad,		/* 173 */
			0x87,		/* 135 */
/* 184 */	0x8,		/* 8 */
			0x0,		/* 0 */
/* 186 */	0x9,		/* 9 */
			0xb6,		/* 182 */
/* 188 */	0xf2,		/* 242 */
			0x2b,		/* 43 */
/* 190 */	
			0x11, 0x14,	/* FC_RP [alloced_on_stack] [pointer_deref] */
/* 192 */	NdrFcShort( 0xffffffec ),	/* Offset= -20 (172) */
/* 194 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 196 */	NdrFcLong( 0x9a5e32d0 ),	/* -1705102640 */
/* 200 */	NdrFcShort( 0xfe1f ),	/* -481 */
/* 202 */	NdrFcShort( 0x11d0 ),	/* 4560 */
/* 204 */	0xad,		/* 173 */
			0x87,		/* 135 */
/* 206 */	0x8,		/* 8 */
			0x0,		/* 0 */
/* 208 */	0x9,		/* 9 */
			0xb6,		/* 182 */
/* 210 */	0xf2,		/* 242 */
			0x2b,		/* 43 */
/* 212 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 214 */	NdrFcShort( 0x0 ),	/* 0 */
/* 216 */	0x28,		/* Corr desc:  parameter, FC_LONG */
			0x0,		/*  */
/* 218 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 220 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 224 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 226 */	NdrFcShort( 0xffffffe0 ),	/* Offset= -32 (194) */
/* 228 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 230 */	
			0x11, 0x14,	/* FC_RP [alloced_on_stack] [pointer_deref] */
/* 232 */	NdrFcShort( 0x2 ),	/* Offset= 2 (234) */
/* 234 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 236 */	NdrFcLong( 0xa3fd5390 ),	/* -1543679088 */
/* 240 */	NdrFcShort( 0xfe1e ),	/* -482 */
/* 242 */	NdrFcShort( 0x11d0 ),	/* 4560 */
/* 244 */	0xad,		/* 173 */
			0x87,		/* 135 */
/* 246 */	0x8,		/* 8 */
			0x0,		/* 0 */
/* 248 */	0x9,		/* 9 */
			0xb6,		/* 182 */
/* 250 */	0xf2,		/* 242 */
			0x2b,		/* 43 */
/* 252 */	
			0x11, 0x14,	/* FC_RP [alloced_on_stack] [pointer_deref] */
/* 254 */	NdrFcShort( 0x2 ),	/* Offset= 2 (256) */
/* 256 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 258 */	NdrFcLong( 0x7309b460 ),	/* 1930015840 */
/* 262 */	NdrFcShort( 0xfe1f ),	/* -481 */
/* 264 */	NdrFcShort( 0x11d0 ),	/* 4560 */
/* 266 */	0xad,		/* 173 */
			0x87,		/* 135 */
/* 268 */	0x8,		/* 8 */
			0x0,		/* 0 */
/* 270 */	0x9,		/* 9 */
			0xb6,		/* 182 */
/* 272 */	0xf2,		/* 242 */
			0x2b,		/* 43 */
/* 274 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 276 */	NdrFcShort( 0x10 ),	/* 16 */
/* 278 */	0xc,		/* FC_DOUBLE */
			0xc,		/* FC_DOUBLE */
/* 280 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 282 */	
			0x1b,		/* FC_CARRAY */
			0x7,		/* 7 */
/* 284 */	NdrFcShort( 0x10 ),	/* 16 */
/* 286 */	0x28,		/* Corr desc:  parameter, FC_LONG */
			0x0,		/*  */
/* 288 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 290 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 292 */	NdrFcShort( 0xffffffee ),	/* Offset= -18 (274) */
/* 294 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 296 */	
			0x11, 0x14,	/* FC_RP [alloced_on_stack] [pointer_deref] */
/* 298 */	NdrFcShort( 0x2 ),	/* Offset= 2 (300) */
/* 300 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 302 */	NdrFcLong( 0x4febc550 ),	/* 1340851536 */
/* 306 */	NdrFcShort( 0xfe1d ),	/* -483 */
/* 308 */	NdrFcShort( 0x11d0 ),	/* 4560 */
/* 310 */	0xad,		/* 173 */
			0x87,		/* 135 */
/* 312 */	0x8,		/* 8 */
			0x0,		/* 0 */
/* 314 */	0x9,		/* 9 */
			0xb6,		/* 182 */
/* 316 */	0xf2,		/* 242 */
			0x2b,		/* 43 */
/* 318 */	
			0x11, 0x14,	/* FC_RP [alloced_on_stack] [pointer_deref] */
/* 320 */	NdrFcShort( 0x2 ),	/* Offset= 2 (322) */
/* 322 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 324 */	NdrFcLong( 0x80855df0 ),	/* -2138743312 */
/* 328 */	NdrFcShort( 0xfe1d ),	/* -483 */
/* 330 */	NdrFcShort( 0x11d0 ),	/* 4560 */
/* 332 */	0xad,		/* 173 */
			0x87,		/* 135 */
/* 334 */	0x8,		/* 8 */
			0x0,		/* 0 */
/* 336 */	0x9,		/* 9 */
			0xb6,		/* 182 */
/* 338 */	0xf2,		/* 242 */
			0x2b,		/* 43 */
/* 340 */	
			0x11, 0x14,	/* FC_RP [alloced_on_stack] [pointer_deref] */
/* 342 */	NdrFcShort( 0x2 ),	/* Offset= 2 (344) */
/* 344 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 346 */	NdrFcLong( 0xce7266c0 ),	/* -831363392 */
/* 350 */	NdrFcShort( 0xfe1d ),	/* -483 */
/* 352 */	NdrFcShort( 0x11d0 ),	/* 4560 */
/* 354 */	0xad,		/* 173 */
			0x87,		/* 135 */
/* 356 */	0x8,		/* 8 */
			0x0,		/* 0 */
/* 358 */	0x9,		/* 9 */
			0xb6,		/* 182 */
/* 360 */	0xf2,		/* 242 */
			0x2b,		/* 43 */
/* 362 */	
			0x11, 0x14,	/* FC_RP [alloced_on_stack] [pointer_deref] */
/* 364 */	NdrFcShort( 0x2 ),	/* Offset= 2 (366) */
/* 366 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 368 */	NdrFcLong( 0x5002f420 ),	/* 1342370848 */
/* 372 */	NdrFcShort( 0xfe1f ),	/* -481 */
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
			0x11, 0x14,	/* FC_RP [alloced_on_stack] [pointer_deref] */
/* 386 */	NdrFcShort( 0x2 ),	/* Offset= 2 (388) */
/* 388 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 390 */	NdrFcLong( 0x4c4c5c00 ),	/* 1280072704 */
/* 394 */	NdrFcShort( 0xfe1e ),	/* -482 */
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
			0x11, 0x14,	/* FC_RP [alloced_on_stack] [pointer_deref] */
/* 408 */	NdrFcShort( 0x2 ),	/* Offset= 2 (410) */
/* 410 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 412 */	NdrFcLong( 0x3dc39ff0 ),	/* 1036230640 */
/* 416 */	NdrFcShort( 0xfe1f ),	/* -481 */
/* 418 */	NdrFcShort( 0x11d0 ),	/* 4560 */
/* 420 */	0xad,		/* 173 */
			0x87,		/* 135 */
/* 422 */	0x8,		/* 8 */
			0x0,		/* 0 */
/* 424 */	0x9,		/* 9 */
			0xb6,		/* 182 */
/* 426 */	0xf2,		/* 242 */
			0x2b,		/* 43 */
/* 428 */	
			0x11, 0x14,	/* FC_RP [alloced_on_stack] [pointer_deref] */
/* 430 */	NdrFcShort( 0x2 ),	/* Offset= 2 (432) */
/* 432 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 434 */	NdrFcLong( 0x5eb513c0 ),	/* 1588925376 */
/* 438 */	NdrFcShort( 0xfe1f ),	/* -481 */
/* 440 */	NdrFcShort( 0x11d0 ),	/* 4560 */
/* 442 */	0xad,		/* 173 */
			0x87,		/* 135 */
/* 444 */	0x8,		/* 8 */
			0x0,		/* 0 */
/* 446 */	0x9,		/* 9 */
			0xb6,		/* 182 */
/* 448 */	0xf2,		/* 242 */
			0x2b,		/* 43 */
/* 450 */	
			0x11, 0x14,	/* FC_RP [alloced_on_stack] [pointer_deref] */
/* 452 */	NdrFcShort( 0x2 ),	/* Offset= 2 (454) */
/* 454 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 456 */	NdrFcLong( 0xf699c510 ),	/* -157694704 */
/* 460 */	NdrFcShort( 0xfe1d ),	/* -483 */
/* 462 */	NdrFcShort( 0x11d0 ),	/* 4560 */
/* 464 */	0xad,		/* 173 */
			0x87,		/* 135 */
/* 466 */	0x8,		/* 8 */
			0x0,		/* 0 */
/* 468 */	0x9,		/* 9 */
			0xb6,		/* 182 */
/* 470 */	0xf2,		/* 242 */
			0x2b,		/* 43 */
/* 472 */	
			0x11, 0x14,	/* FC_RP [alloced_on_stack] [pointer_deref] */
/* 474 */	NdrFcShort( 0x2 ),	/* Offset= 2 (476) */
/* 476 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 478 */	NdrFcLong( 0xce7266c0 ),	/* -831363392 */
/* 482 */	NdrFcShort( 0xfe1d ),	/* -483 */
/* 484 */	NdrFcShort( 0x11d0 ),	/* 4560 */
/* 486 */	0xad,		/* 173 */
			0x87,		/* 135 */
/* 488 */	0x8,		/* 8 */
			0x0,		/* 0 */
/* 490 */	0x9,		/* 9 */
			0xb6,		/* 182 */
/* 492 */	0xf2,		/* 242 */
			0x2b,		/* 43 */
/* 494 */	
			0x11, 0x14,	/* FC_RP [alloced_on_stack] [pointer_deref] */
/* 496 */	NdrFcShort( 0x2 ),	/* Offset= 2 (498) */
/* 498 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 500 */	NdrFcLong( 0x15129940 ),	/* 353540416 */
/* 504 */	NdrFcShort( 0xfe1e ),	/* -482 */
/* 506 */	NdrFcShort( 0x11d0 ),	/* 4560 */
/* 508 */	0xad,		/* 173 */
			0x87,		/* 135 */
/* 510 */	0x8,		/* 8 */
			0x0,		/* 0 */
/* 512 */	0x9,		/* 9 */
			0xb6,		/* 182 */
/* 514 */	0xf2,		/* 242 */
			0x2b,		/* 43 */
/* 516 */	
			0x11, 0x14,	/* FC_RP [alloced_on_stack] [pointer_deref] */
/* 518 */	NdrFcShort( 0x2 ),	/* Offset= 2 (520) */
/* 520 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 522 */	NdrFcLong( 0x80855df0 ),	/* -2138743312 */
/* 526 */	NdrFcShort( 0xfe1d ),	/* -483 */
/* 528 */	NdrFcShort( 0x11d0 ),	/* 4560 */
/* 530 */	0xad,		/* 173 */
			0x87,		/* 135 */
/* 532 */	0x8,		/* 8 */
			0x0,		/* 0 */
/* 534 */	0x9,		/* 9 */
			0xb6,		/* 182 */
/* 536 */	0xf2,		/* 242 */
			0x2b,		/* 43 */
/* 538 */	
			0x11, 0x14,	/* FC_RP [alloced_on_stack] [pointer_deref] */
/* 540 */	NdrFcShort( 0x2 ),	/* Offset= 2 (542) */
/* 542 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 544 */	NdrFcLong( 0x4febc550 ),	/* 1340851536 */
/* 548 */	NdrFcShort( 0xfe1d ),	/* -483 */
/* 550 */	NdrFcShort( 0x11d0 ),	/* 4560 */
/* 552 */	0xad,		/* 173 */
			0x87,		/* 135 */
/* 554 */	0x8,		/* 8 */
			0x0,		/* 0 */
/* 556 */	0x9,		/* 9 */
			0xb6,		/* 182 */
/* 558 */	0xf2,		/* 242 */
			0x2b,		/* 43 */

			0x0
        }
    };

static const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ] = 
        {
            
            {
            BSTR_UserSize
            ,BSTR_UserMarshal
            ,BSTR_UserUnmarshal
            ,BSTR_UserFree
            }

        };



/* Standard interface: __MIDL_itf_SpatialReference_0000, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}} */


/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: ISpatialReferenceInfo, ver. 0.0,
   GUID={0xbcca38a0,0xfe1c,0x11d0,{0xad,0x87,0x08,0x00,0x09,0xb6,0xf2,0x2b}} */

#pragma code_seg(".orpc")
static const unsigned short ISpatialReferenceInfo_FormatStringOffsetTable[] =
    {
    0,
    6,
    0,
    6,
    12,
    18,
    0,
    6,
    0,
    6,
    0,
    6,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO ISpatialReferenceInfo_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &ISpatialReferenceInfo_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO ISpatialReferenceInfo_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &ISpatialReferenceInfo_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
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
    &ISpatialReferenceInfo_ServerInfo,
    16,
    &ISpatialReferenceInfo_table[-3],
    CStdStubBuffer_METHODS
};


/* Object interface: IUnit, ver. 0.0,
   GUID={0x221733b0,0xfe1d,0x11d0,{0xad,0x87,0x08,0x00,0x09,0xb6,0xf2,0x2b}} */

#pragma code_seg(".orpc")
static const unsigned short IUnit_FormatStringOffsetTable[] =
    {
    0,
    6,
    0,
    6,
    12,
    18,
    0,
    6,
    0,
    6,
    0,
    6,
    0,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO IUnit_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IUnit_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IUnit_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IUnit_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
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
    &IUnit_ServerInfo,
    16,
    &IUnit_table[-3],
    CStdStubBuffer_METHODS
};


/* Object interface: IAngularUnit, ver. 0.0,
   GUID={0x4febc550,0xfe1d,0x11d0,{0xad,0x87,0x08,0x00,0x09,0xb6,0xf2,0x2b}} */

#pragma code_seg(".orpc")
static const unsigned short IAngularUnit_FormatStringOffsetTable[] =
    {
    0,
    6,
    0,
    6,
    12,
    18,
    0,
    6,
    0,
    6,
    0,
    6,
    0,
    22,
    28
    };

static const MIDL_STUBLESS_PROXY_INFO IAngularUnit_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IAngularUnit_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IAngularUnit_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IAngularUnit_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
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
    &IAngularUnit_ServerInfo,
    18,
    &IAngularUnit_table[-3],
    CStdStubBuffer_METHODS
};


/* Object interface: ILinearUnit, ver. 0.0,
   GUID={0x80855df0,0xfe1d,0x11d0,{0xad,0x87,0x08,0x00,0x09,0xb6,0xf2,0x2b}} */

#pragma code_seg(".orpc")
static const unsigned short ILinearUnit_FormatStringOffsetTable[] =
    {
    0,
    6,
    0,
    6,
    12,
    18,
    0,
    6,
    0,
    6,
    0,
    6,
    0,
    22,
    28
    };

static const MIDL_STUBLESS_PROXY_INFO ILinearUnit_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &ILinearUnit_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO ILinearUnit_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &ILinearUnit_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
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
    &ILinearUnit_ServerInfo,
    18,
    &ILinearUnit_table[-3],
    CStdStubBuffer_METHODS
};


/* Object interface: IEllipsoid, ver. 0.0,
   GUID={0xce7266c0,0xfe1d,0x11d0,{0xad,0x87,0x08,0x00,0x09,0xb6,0xf2,0x2b}} */

#pragma code_seg(".orpc")
static const unsigned short IEllipsoid_FormatStringOffsetTable[] =
    {
    0,
    6,
    0,
    6,
    12,
    18,
    0,
    6,
    0,
    6,
    0,
    6,
    0,
    22,
    28,
    22,
    28,
    22,
    28,
    32,
    38
    };

static const MIDL_STUBLESS_PROXY_INFO IEllipsoid_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IEllipsoid_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IEllipsoid_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IEllipsoid_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
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
    &IEllipsoid_ServerInfo,
    24,
    &IEllipsoid_table[-3],
    CStdStubBuffer_METHODS
};


/* Object interface: IHorizontalDatum, ver. 0.0,
   GUID={0xf699c510,0xfe1d,0x11d0,{0xad,0x87,0x08,0x00,0x09,0xb6,0xf2,0x2b}} */

#pragma code_seg(".orpc")
static const unsigned short IHorizontalDatum_FormatStringOffsetTable[] =
    {
    0,
    6,
    0,
    6,
    12,
    18,
    0,
    6,
    0,
    6,
    0,
    6,
    0,
    44,
    50
    };

static const MIDL_STUBLESS_PROXY_INFO IHorizontalDatum_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IHorizontalDatum_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IHorizontalDatum_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IHorizontalDatum_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
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
    &IHorizontalDatum_ServerInfo,
    18,
    &IHorizontalDatum_table[-3],
    CStdStubBuffer_METHODS
};


/* Object interface: IPrimeMeridian, ver. 0.0,
   GUID={0x15129940,0xfe1e,0x11d0,{0xad,0x87,0x08,0x00,0x09,0xb6,0xf2,0x2b}} */

#pragma code_seg(".orpc")
static const unsigned short IPrimeMeridian_FormatStringOffsetTable[] =
    {
    0,
    6,
    0,
    6,
    12,
    18,
    0,
    6,
    0,
    6,
    0,
    6,
    0,
    22,
    28,
    56,
    62
    };

static const MIDL_STUBLESS_PROXY_INFO IPrimeMeridian_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IPrimeMeridian_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IPrimeMeridian_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IPrimeMeridian_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
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
    &IPrimeMeridian_ServerInfo,
    20,
    &IPrimeMeridian_table[-3],
    CStdStubBuffer_METHODS
};


/* Object interface: ISpatialReference, ver. 0.0,
   GUID={0x4c4c5c00,0xfe1e,0x11d0,{0xad,0x87,0x08,0x00,0x09,0xb6,0xf2,0x2b}} */

#pragma code_seg(".orpc")
static const unsigned short ISpatialReference_FormatStringOffsetTable[] =
    {
    0,
    6,
    0,
    6,
    12,
    18,
    0,
    6,
    0,
    6,
    0,
    6,
    0,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO ISpatialReference_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &ISpatialReference_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO ISpatialReference_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &ISpatialReference_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
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
    &ISpatialReference_ServerInfo,
    16,
    &ISpatialReference_table[-3],
    CStdStubBuffer_METHODS
};


/* Object interface: IGeodeticSpatialReference, ver. 0.0,
   GUID={0x7c3c56d0,0xfe1e,0x11d0,{0xad,0x87,0x08,0x00,0x09,0xb6,0xf2,0x2b}} */

#pragma code_seg(".orpc")
static const unsigned short IGeodeticSpatialReference_FormatStringOffsetTable[] =
    {
    0,
    6,
    0,
    6,
    12,
    18,
    0,
    6,
    0,
    6,
    0,
    6,
    0,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO IGeodeticSpatialReference_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IGeodeticSpatialReference_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IGeodeticSpatialReference_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IGeodeticSpatialReference_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
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
    &IGeodeticSpatialReference_ServerInfo,
    16,
    &IGeodeticSpatialReference_table[-3],
    CStdStubBuffer_METHODS
};


/* Object interface: IGeographicCoordinateSystem, ver. 0.0,
   GUID={0xa3fd5390,0xfe1e,0x11d0,{0xad,0x87,0x08,0x00,0x09,0xb6,0xf2,0x2b}} */

#pragma code_seg(".orpc")
static const unsigned short IGeographicCoordinateSystem_FormatStringOffsetTable[] =
    {
    0,
    6,
    0,
    6,
    12,
    18,
    0,
    6,
    0,
    6,
    0,
    6,
    0,
    0,
    6,
    68,
    74,
    56,
    62,
    80,
    86
    };

static const MIDL_STUBLESS_PROXY_INFO IGeographicCoordinateSystem_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IGeographicCoordinateSystem_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IGeographicCoordinateSystem_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IGeographicCoordinateSystem_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
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
    &IGeographicCoordinateSystem_ServerInfo,
    24,
    &IGeographicCoordinateSystem_table[-3],
    CStdStubBuffer_METHODS
};


/* Object interface: IParameter, ver. 0.0,
   GUID={0x9a5e32d0,0xfe1f,0x11d0,{0xad,0x87,0x08,0x00,0x09,0xb6,0xf2,0x2b}} */

#pragma code_seg(".orpc")
static const unsigned short IParameter_FormatStringOffsetTable[] =
    {
    0,
    6,
    0,
    6,
    12,
    18,
    0,
    6,
    0,
    6,
    0,
    6,
    0,
    92,
    98,
    28,
    22
    };

static const MIDL_STUBLESS_PROXY_INFO IParameter_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IParameter_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IParameter_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IParameter_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
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
    &IParameter_ServerInfo,
    20,
    &IParameter_table[-3],
    CStdStubBuffer_METHODS
};


/* Object interface: IParameterInfo, ver. 0.0,
   GUID={0x7309b460,0xfe1f,0x11d0,{0xad,0x87,0x08,0x00,0x09,0xb6,0xf2,0x2b}} */

#pragma code_seg(".orpc")
static const unsigned short IParameterInfo_FormatStringOffsetTable[] =
    {
    12,
    104,
    104,
    112
    };

static const MIDL_STUBLESS_PROXY_INFO IParameterInfo_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IParameterInfo_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IParameterInfo_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IParameterInfo_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
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
    &IParameterInfo_ServerInfo,
    7,
    &IParameterInfo_table[-3],
    CStdStubBuffer_METHODS
};


/* Object interface: IGeographicTransform, ver. 0.0,
   GUID={0x5eb513c0,0xfe1f,0x11d0,{0xad,0x87,0x08,0x00,0x09,0xb6,0xf2,0x2b}} */

#pragma code_seg(".orpc")
static const unsigned short IGeographicTransform_FormatStringOffsetTable[] =
    {
    0,
    6,
    0,
    6,
    12,
    18,
    0,
    6,
    0,
    6,
    0,
    6,
    0,
    120,
    126,
    120,
    126,
    132,
    138,
    138
    };

static const MIDL_STUBLESS_PROXY_INFO IGeographicTransform_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IGeographicTransform_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IGeographicTransform_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IGeographicTransform_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
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
    &IGeographicTransform_ServerInfo,
    23,
    &IGeographicTransform_table[-3],
    CStdStubBuffer_METHODS
};


/* Object interface: IProjection, ver. 0.0,
   GUID={0x5002f420,0xfe1f,0x11d0,{0xad,0x87,0x08,0x00,0x09,0xb6,0xf2,0x2b}} */

#pragma code_seg(".orpc")
static const unsigned short IProjection_FormatStringOffsetTable[] =
    {
    0,
    6,
    0,
    6,
    12,
    18,
    0,
    6,
    0,
    6,
    0,
    6,
    0,
    0,
    0,
    138,
    138,
    132,
    146,
    152,
    158,
    164,
    170,
    176
    };

static const MIDL_STUBLESS_PROXY_INFO IProjection_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IProjection_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IProjection_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IProjection_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
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
    &IProjection_ServerInfo,
    27,
    &IProjection_table[-3],
    CStdStubBuffer_METHODS
};


/* Object interface: IProjectedCoordinateSystem, ver. 0.0,
   GUID={0x3dc39ff0,0xfe1f,0x11d0,{0xad,0x87,0x08,0x00,0x09,0xb6,0xf2,0x2b}} */

#pragma code_seg(".orpc")
static const unsigned short IProjectedCoordinateSystem_FormatStringOffsetTable[] =
    {
    0,
    6,
    0,
    6,
    12,
    18,
    0,
    6,
    0,
    6,
    0,
    6,
    0,
    0,
    6,
    120,
    126,
    158,
    164,
    182,
    188,
    132,
    138,
    138
    };

static const MIDL_STUBLESS_PROXY_INFO IProjectedCoordinateSystem_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IProjectedCoordinateSystem_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IProjectedCoordinateSystem_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IProjectedCoordinateSystem_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
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
    &IProjectedCoordinateSystem_ServerInfo,
    27,
    &IProjectedCoordinateSystem_table[-3],
    CStdStubBuffer_METHODS
};


/* Object interface: ISpatialReferenceFactory, ver. 0.0,
   GUID={0x620600B1,0xFEA1,0x11d0,{0xB0,0x4B,0x00,0x80,0xC7,0xF7,0x94,0x81}} */

#pragma code_seg(".orpc")
static const unsigned short ISpatialReferenceFactory_FormatStringOffsetTable[] =
    {
    194
    };

static const MIDL_STUBLESS_PROXY_INFO ISpatialReferenceFactory_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &ISpatialReferenceFactory_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO ISpatialReferenceFactory_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &ISpatialReferenceFactory_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
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
    &ISpatialReferenceFactory_ServerInfo,
    4,
    &ISpatialReferenceFactory_table[-3],
    CStdStubBuffer_METHODS
};


/* Object interface: ISpatialReferenceAuthorityFactory, ver. 0.0,
   GUID={0x30ae14f0,0xfe1f,0x11d0,{0xad,0x87,0x08,0x00,0x09,0xb6,0xf2,0x2b}} */

#pragma code_seg(".orpc")
static const unsigned short ISpatialReferenceAuthorityFactory_FormatStringOffsetTable[] =
    {
    0,
    204,
    212,
    220,
    228,
    236,
    244,
    252,
    260,
    268
    };

static const MIDL_STUBLESS_PROXY_INFO ISpatialReferenceAuthorityFactory_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &ISpatialReferenceAuthorityFactory_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO ISpatialReferenceAuthorityFactory_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &ISpatialReferenceAuthorityFactory_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
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
    &ISpatialReferenceAuthorityFactory_ServerInfo,
    13,
    &ISpatialReferenceAuthorityFactory_table[-3],
    CStdStubBuffer_METHODS
};

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
    1, /* -error bounds_check flag */
    0x20000, /* Ndr library version */
    0,
    0x600015b, /* MIDL Version 6.0.347 */
    0,
    UserMarshalRoutines,
    0,  /* notify & notify_flag routine table */
    0x1, /* MIDL flag */
    0, /* cs routines */
    0,   /* proxy/server info */
    0   /* Reserved5 */
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
    1,
    0, /* table of [async_uuid] interfaces */
    0, /* Filler1 */
    0, /* Filler2 */
    0  /* Filler3 */
};


#endif /* !defined(_M_IA64) && !defined(_M_AMD64)*/


#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the proxy stub code */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Mon Feb 04 21:48:28 2002
 */
/* Compiler settings for SpatialReference.idl:
    Oicf, W1, Zp8, env=Win64 (32b run,appending)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#if defined(_M_IA64) || defined(_M_AMD64)
#define USE_STUBLESS_PROXY


/* verify that the <rpcproxy.h> version is high enough to compile this file*/
#ifndef __REDQ_RPCPROXY_H_VERSION__
#define __REQUIRED_RPCPROXY_H_VERSION__ 475
#endif


#include "rpcproxy.h"
#ifndef __RPCPROXY_H_VERSION__
#error this stub requires an updated version of <rpcproxy.h>
#endif // __RPCPROXY_H_VERSION__


#include "SpatialReference.h"

#define TYPE_FORMAT_STRING_SIZE   569                               
#define PROC_FORMAT_STRING_SIZE   2927                              
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   1            

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


static RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};


extern const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString;
extern const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO ISpatialReferenceInfo_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO ISpatialReferenceInfo_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IUnit_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IUnit_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IAngularUnit_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IAngularUnit_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO ILinearUnit_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO ILinearUnit_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IEllipsoid_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IEllipsoid_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IHorizontalDatum_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IHorizontalDatum_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IPrimeMeridian_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IPrimeMeridian_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO ISpatialReference_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO ISpatialReference_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IGeodeticSpatialReference_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IGeodeticSpatialReference_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IGeographicCoordinateSystem_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IGeographicCoordinateSystem_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IParameter_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IParameter_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IParameterInfo_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IParameterInfo_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IGeographicTransform_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IGeographicTransform_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IProjection_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IProjection_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IProjectedCoordinateSystem_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IProjectedCoordinateSystem_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO ISpatialReferenceFactory_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO ISpatialReferenceFactory_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO ISpatialReferenceAuthorityFactory_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO ISpatialReferenceAuthorityFactory_ProxyInfo;


extern const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ];

#if !defined(__RPC_WIN64__)
#error  Invalid build platform for this stub.
#endif

static const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure get_Authority */


	/* Procedure get_Name */

			0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/*  2 */	NdrFcLong( 0x0 ),	/* 0 */
/*  6 */	NdrFcShort( 0x3 ),	/* 3 */
/*  8 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 10 */	NdrFcShort( 0x0 ),	/* 0 */
/* 12 */	NdrFcShort( 0x8 ),	/* 8 */
/* 14 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 16 */	0xa,		/* 10 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 18 */	NdrFcShort( 0x1 ),	/* 1 */
/* 20 */	NdrFcShort( 0x0 ),	/* 0 */
/* 22 */	NdrFcShort( 0x0 ),	/* 0 */
/* 24 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter authority */


	/* Parameter name */

/* 26 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 28 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 30 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */


	/* Return value */

/* 32 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 34 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 36 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Name */

/* 38 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 40 */	NdrFcLong( 0x0 ),	/* 0 */
/* 44 */	NdrFcShort( 0x4 ),	/* 4 */
/* 46 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 48 */	NdrFcShort( 0x0 ),	/* 0 */
/* 50 */	NdrFcShort( 0x8 ),	/* 8 */
/* 52 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 54 */	0xa,		/* 10 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 56 */	NdrFcShort( 0x0 ),	/* 0 */
/* 58 */	NdrFcShort( 0x1 ),	/* 1 */
/* 60 */	NdrFcShort( 0x0 ),	/* 0 */
/* 62 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter name */

/* 64 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 66 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 68 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Return value */

/* 70 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 72 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 74 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Authority */

/* 76 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 78 */	NdrFcLong( 0x0 ),	/* 0 */
/* 82 */	NdrFcShort( 0x5 ),	/* 5 */
/* 84 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 86 */	NdrFcShort( 0x0 ),	/* 0 */
/* 88 */	NdrFcShort( 0x8 ),	/* 8 */
/* 90 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 92 */	0xa,		/* 10 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 94 */	NdrFcShort( 0x1 ),	/* 1 */
/* 96 */	NdrFcShort( 0x0 ),	/* 0 */
/* 98 */	NdrFcShort( 0x0 ),	/* 0 */
/* 100 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter name */

/* 102 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 104 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 106 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 108 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 110 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 112 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Authority */

/* 114 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 116 */	NdrFcLong( 0x0 ),	/* 0 */
/* 120 */	NdrFcShort( 0x6 ),	/* 6 */
/* 122 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 124 */	NdrFcShort( 0x0 ),	/* 0 */
/* 126 */	NdrFcShort( 0x8 ),	/* 8 */
/* 128 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 130 */	0xa,		/* 10 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 132 */	NdrFcShort( 0x0 ),	/* 0 */
/* 134 */	NdrFcShort( 0x1 ),	/* 1 */
/* 136 */	NdrFcShort( 0x0 ),	/* 0 */
/* 138 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter name */

/* 140 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 142 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 144 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Return value */

/* 146 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 148 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 150 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Code */

/* 152 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 154 */	NdrFcLong( 0x0 ),	/* 0 */
/* 158 */	NdrFcShort( 0x7 ),	/* 7 */
/* 160 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 162 */	NdrFcShort( 0x0 ),	/* 0 */
/* 164 */	NdrFcShort( 0x24 ),	/* 36 */
/* 166 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 168 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 170 */	NdrFcShort( 0x0 ),	/* 0 */
/* 172 */	NdrFcShort( 0x0 ),	/* 0 */
/* 174 */	NdrFcShort( 0x0 ),	/* 0 */
/* 176 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter code */

/* 178 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 180 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 182 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 184 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 186 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 188 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Code */

/* 190 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 192 */	NdrFcLong( 0x0 ),	/* 0 */
/* 196 */	NdrFcShort( 0x8 ),	/* 8 */
/* 198 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 200 */	NdrFcShort( 0x8 ),	/* 8 */
/* 202 */	NdrFcShort( 0x8 ),	/* 8 */
/* 204 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 206 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 208 */	NdrFcShort( 0x0 ),	/* 0 */
/* 210 */	NdrFcShort( 0x0 ),	/* 0 */
/* 212 */	NdrFcShort( 0x0 ),	/* 0 */
/* 214 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter code */

/* 216 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 218 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 220 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 222 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 224 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 226 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Alias */

/* 228 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 230 */	NdrFcLong( 0x0 ),	/* 0 */
/* 234 */	NdrFcShort( 0x9 ),	/* 9 */
/* 236 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 238 */	NdrFcShort( 0x0 ),	/* 0 */
/* 240 */	NdrFcShort( 0x8 ),	/* 8 */
/* 242 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 244 */	0xa,		/* 10 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 246 */	NdrFcShort( 0x1 ),	/* 1 */
/* 248 */	NdrFcShort( 0x0 ),	/* 0 */
/* 250 */	NdrFcShort( 0x0 ),	/* 0 */
/* 252 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter alias */

/* 254 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 256 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 258 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 260 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 262 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 264 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Alias */

/* 266 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 268 */	NdrFcLong( 0x0 ),	/* 0 */
/* 272 */	NdrFcShort( 0xa ),	/* 10 */
/* 274 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 276 */	NdrFcShort( 0x0 ),	/* 0 */
/* 278 */	NdrFcShort( 0x8 ),	/* 8 */
/* 280 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 282 */	0xa,		/* 10 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 284 */	NdrFcShort( 0x0 ),	/* 0 */
/* 286 */	NdrFcShort( 0x1 ),	/* 1 */
/* 288 */	NdrFcShort( 0x0 ),	/* 0 */
/* 290 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter alias */

/* 292 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 294 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 296 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Return value */

/* 298 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 300 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 302 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Abbreviation */

/* 304 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 306 */	NdrFcLong( 0x0 ),	/* 0 */
/* 310 */	NdrFcShort( 0xb ),	/* 11 */
/* 312 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 314 */	NdrFcShort( 0x0 ),	/* 0 */
/* 316 */	NdrFcShort( 0x8 ),	/* 8 */
/* 318 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 320 */	0xa,		/* 10 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 322 */	NdrFcShort( 0x1 ),	/* 1 */
/* 324 */	NdrFcShort( 0x0 ),	/* 0 */
/* 326 */	NdrFcShort( 0x0 ),	/* 0 */
/* 328 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter abbrev */

/* 330 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 332 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 334 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 336 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 338 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 340 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Abbreviation */

/* 342 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 344 */	NdrFcLong( 0x0 ),	/* 0 */
/* 348 */	NdrFcShort( 0xc ),	/* 12 */
/* 350 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 352 */	NdrFcShort( 0x0 ),	/* 0 */
/* 354 */	NdrFcShort( 0x8 ),	/* 8 */
/* 356 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 358 */	0xa,		/* 10 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 360 */	NdrFcShort( 0x0 ),	/* 0 */
/* 362 */	NdrFcShort( 0x1 ),	/* 1 */
/* 364 */	NdrFcShort( 0x0 ),	/* 0 */
/* 366 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter abbrev */

/* 368 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 370 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 372 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Return value */

/* 374 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 376 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 378 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Remarks */

/* 380 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 382 */	NdrFcLong( 0x0 ),	/* 0 */
/* 386 */	NdrFcShort( 0xd ),	/* 13 */
/* 388 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 390 */	NdrFcShort( 0x0 ),	/* 0 */
/* 392 */	NdrFcShort( 0x8 ),	/* 8 */
/* 394 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 396 */	0xa,		/* 10 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 398 */	NdrFcShort( 0x1 ),	/* 1 */
/* 400 */	NdrFcShort( 0x0 ),	/* 0 */
/* 402 */	NdrFcShort( 0x0 ),	/* 0 */
/* 404 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter remarks */

/* 406 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 408 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 410 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 412 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 414 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 416 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Remarks */

/* 418 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 420 */	NdrFcLong( 0x0 ),	/* 0 */
/* 424 */	NdrFcShort( 0xe ),	/* 14 */
/* 426 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 428 */	NdrFcShort( 0x0 ),	/* 0 */
/* 430 */	NdrFcShort( 0x8 ),	/* 8 */
/* 432 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 434 */	0xa,		/* 10 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 436 */	NdrFcShort( 0x0 ),	/* 0 */
/* 438 */	NdrFcShort( 0x1 ),	/* 1 */
/* 440 */	NdrFcShort( 0x0 ),	/* 0 */
/* 442 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter remarks */

/* 444 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 446 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 448 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Return value */

/* 450 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 452 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 454 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_WellKnownText */

/* 456 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 458 */	NdrFcLong( 0x0 ),	/* 0 */
/* 462 */	NdrFcShort( 0xf ),	/* 15 */
/* 464 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 466 */	NdrFcShort( 0x0 ),	/* 0 */
/* 468 */	NdrFcShort( 0x8 ),	/* 8 */
/* 470 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 472 */	0xa,		/* 10 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 474 */	NdrFcShort( 0x1 ),	/* 1 */
/* 476 */	NdrFcShort( 0x0 ),	/* 0 */
/* 478 */	NdrFcShort( 0x0 ),	/* 0 */
/* 480 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter wkt */

/* 482 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 484 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 486 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 488 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 490 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 492 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Longitude */


	/* Procedure get_SemiMajorAxis */


	/* Procedure get_MetersPerUnit */


	/* Procedure get_RadiansPerUnit */

/* 494 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 496 */	NdrFcLong( 0x0 ),	/* 0 */
/* 500 */	NdrFcShort( 0x10 ),	/* 16 */
/* 502 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 504 */	NdrFcShort( 0x0 ),	/* 0 */
/* 506 */	NdrFcShort( 0x2c ),	/* 44 */
/* 508 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 510 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 512 */	NdrFcShort( 0x0 ),	/* 0 */
/* 514 */	NdrFcShort( 0x0 ),	/* 0 */
/* 516 */	NdrFcShort( 0x0 ),	/* 0 */
/* 518 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter longitude */


	/* Parameter axis */


	/* Parameter factor */


	/* Parameter factor */

/* 520 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 522 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 524 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */

/* 526 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 528 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 530 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Longitude */


	/* Procedure put_SemiMajorAxis */


	/* Procedure put_MetersPerUnit */


	/* Procedure put_RadiansPerUnit */

/* 532 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 534 */	NdrFcLong( 0x0 ),	/* 0 */
/* 538 */	NdrFcShort( 0x11 ),	/* 17 */
/* 540 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 542 */	NdrFcShort( 0x10 ),	/* 16 */
/* 544 */	NdrFcShort( 0x8 ),	/* 8 */
/* 546 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 548 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 550 */	NdrFcShort( 0x0 ),	/* 0 */
/* 552 */	NdrFcShort( 0x0 ),	/* 0 */
/* 554 */	NdrFcShort( 0x0 ),	/* 0 */
/* 556 */	NdrFcShort( 0x8 ),	/* 8 */

	/* Parameter longitude */


	/* Parameter axis */


	/* Parameter factor */


	/* Parameter factor */

/* 558 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 560 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 562 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */

/* 564 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 566 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 568 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_SemiMinorAxis */

/* 570 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 572 */	NdrFcLong( 0x0 ),	/* 0 */
/* 576 */	NdrFcShort( 0x12 ),	/* 18 */
/* 578 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 580 */	NdrFcShort( 0x0 ),	/* 0 */
/* 582 */	NdrFcShort( 0x2c ),	/* 44 */
/* 584 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 586 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 588 */	NdrFcShort( 0x0 ),	/* 0 */
/* 590 */	NdrFcShort( 0x0 ),	/* 0 */
/* 592 */	NdrFcShort( 0x0 ),	/* 0 */
/* 594 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter axis */

/* 596 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 598 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 600 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 602 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 604 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 606 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_SemiMinorAxis */

/* 608 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 610 */	NdrFcLong( 0x0 ),	/* 0 */
/* 614 */	NdrFcShort( 0x13 ),	/* 19 */
/* 616 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 618 */	NdrFcShort( 0x10 ),	/* 16 */
/* 620 */	NdrFcShort( 0x8 ),	/* 8 */
/* 622 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 624 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 626 */	NdrFcShort( 0x0 ),	/* 0 */
/* 628 */	NdrFcShort( 0x0 ),	/* 0 */
/* 630 */	NdrFcShort( 0x0 ),	/* 0 */
/* 632 */	NdrFcShort( 0x8 ),	/* 8 */

	/* Parameter axis */

/* 634 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 636 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 638 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 640 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 642 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 644 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_InverseFlattening */

/* 646 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 648 */	NdrFcLong( 0x0 ),	/* 0 */
/* 652 */	NdrFcShort( 0x14 ),	/* 20 */
/* 654 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 656 */	NdrFcShort( 0x0 ),	/* 0 */
/* 658 */	NdrFcShort( 0x2c ),	/* 44 */
/* 660 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 662 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 664 */	NdrFcShort( 0x0 ),	/* 0 */
/* 666 */	NdrFcShort( 0x0 ),	/* 0 */
/* 668 */	NdrFcShort( 0x0 ),	/* 0 */
/* 670 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter invFlat */

/* 672 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 674 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 676 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 678 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 680 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 682 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_InverseFlattening */

/* 684 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 686 */	NdrFcLong( 0x0 ),	/* 0 */
/* 690 */	NdrFcShort( 0x15 ),	/* 21 */
/* 692 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 694 */	NdrFcShort( 0x10 ),	/* 16 */
/* 696 */	NdrFcShort( 0x8 ),	/* 8 */
/* 698 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 700 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 702 */	NdrFcShort( 0x0 ),	/* 0 */
/* 704 */	NdrFcShort( 0x0 ),	/* 0 */
/* 706 */	NdrFcShort( 0x0 ),	/* 0 */
/* 708 */	NdrFcShort( 0x8 ),	/* 8 */

	/* Parameter invFlat */

/* 710 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 712 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 714 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 716 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 718 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 720 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_AxisUnit */

/* 722 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 724 */	NdrFcLong( 0x0 ),	/* 0 */
/* 728 */	NdrFcShort( 0x16 ),	/* 22 */
/* 730 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 732 */	NdrFcShort( 0x0 ),	/* 0 */
/* 734 */	NdrFcShort( 0x8 ),	/* 8 */
/* 736 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 738 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 740 */	NdrFcShort( 0x0 ),	/* 0 */
/* 742 */	NdrFcShort( 0x0 ),	/* 0 */
/* 744 */	NdrFcShort( 0x0 ),	/* 0 */
/* 746 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter unit */

/* 748 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 750 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 752 */	NdrFcShort( 0x40 ),	/* Type Offset=64 */

	/* Return value */

/* 754 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 756 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 758 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_AxisUnit */

/* 760 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 762 */	NdrFcLong( 0x0 ),	/* 0 */
/* 766 */	NdrFcShort( 0x17 ),	/* 23 */
/* 768 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 770 */	NdrFcShort( 0x0 ),	/* 0 */
/* 772 */	NdrFcShort( 0x8 ),	/* 8 */
/* 774 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 776 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 778 */	NdrFcShort( 0x0 ),	/* 0 */
/* 780 */	NdrFcShort( 0x0 ),	/* 0 */
/* 782 */	NdrFcShort( 0x0 ),	/* 0 */
/* 784 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter unit */

/* 786 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 788 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 790 */	NdrFcShort( 0x44 ),	/* Type Offset=68 */

	/* Return value */

/* 792 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 794 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 796 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Ellipsoid */

/* 798 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 800 */	NdrFcLong( 0x0 ),	/* 0 */
/* 804 */	NdrFcShort( 0x10 ),	/* 16 */
/* 806 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 808 */	NdrFcShort( 0x0 ),	/* 0 */
/* 810 */	NdrFcShort( 0x8 ),	/* 8 */
/* 812 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 814 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 816 */	NdrFcShort( 0x0 ),	/* 0 */
/* 818 */	NdrFcShort( 0x0 ),	/* 0 */
/* 820 */	NdrFcShort( 0x0 ),	/* 0 */
/* 822 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ellipsoid */

/* 824 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 826 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 828 */	NdrFcShort( 0x56 ),	/* Type Offset=86 */

	/* Return value */

/* 830 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 832 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 834 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Ellipsoid */

/* 836 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 838 */	NdrFcLong( 0x0 ),	/* 0 */
/* 842 */	NdrFcShort( 0x11 ),	/* 17 */
/* 844 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 846 */	NdrFcShort( 0x0 ),	/* 0 */
/* 848 */	NdrFcShort( 0x8 ),	/* 8 */
/* 850 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 852 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 854 */	NdrFcShort( 0x0 ),	/* 0 */
/* 856 */	NdrFcShort( 0x0 ),	/* 0 */
/* 858 */	NdrFcShort( 0x0 ),	/* 0 */
/* 860 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ellipsoid */

/* 862 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 864 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 866 */	NdrFcShort( 0x5a ),	/* Type Offset=90 */

	/* Return value */

/* 868 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 870 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 872 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_AngularUnit */

/* 874 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 876 */	NdrFcLong( 0x0 ),	/* 0 */
/* 880 */	NdrFcShort( 0x12 ),	/* 18 */
/* 882 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 884 */	NdrFcShort( 0x0 ),	/* 0 */
/* 886 */	NdrFcShort( 0x8 ),	/* 8 */
/* 888 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 890 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 892 */	NdrFcShort( 0x0 ),	/* 0 */
/* 894 */	NdrFcShort( 0x0 ),	/* 0 */
/* 896 */	NdrFcShort( 0x0 ),	/* 0 */
/* 898 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter unit */

/* 900 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 902 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 904 */	NdrFcShort( 0x6c ),	/* Type Offset=108 */

	/* Return value */

/* 906 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 908 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 910 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_AngularUnit */

/* 912 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 914 */	NdrFcLong( 0x0 ),	/* 0 */
/* 918 */	NdrFcShort( 0x13 ),	/* 19 */
/* 920 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 922 */	NdrFcShort( 0x0 ),	/* 0 */
/* 924 */	NdrFcShort( 0x8 ),	/* 8 */
/* 926 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 928 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 930 */	NdrFcShort( 0x0 ),	/* 0 */
/* 932 */	NdrFcShort( 0x0 ),	/* 0 */
/* 934 */	NdrFcShort( 0x0 ),	/* 0 */
/* 936 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter unit */

/* 938 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 940 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 942 */	NdrFcShort( 0x70 ),	/* Type Offset=112 */

	/* Return value */

/* 944 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 946 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 948 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Usage */


	/* Procedure get_Usage */


	/* Procedure get_Usage */

/* 950 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 952 */	NdrFcLong( 0x0 ),	/* 0 */
/* 956 */	NdrFcShort( 0x10 ),	/* 16 */
/* 958 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 960 */	NdrFcShort( 0x0 ),	/* 0 */
/* 962 */	NdrFcShort( 0x8 ),	/* 8 */
/* 964 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 966 */	0xa,		/* 10 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 968 */	NdrFcShort( 0x1 ),	/* 1 */
/* 970 */	NdrFcShort( 0x0 ),	/* 0 */
/* 972 */	NdrFcShort( 0x0 ),	/* 0 */
/* 974 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter usage */


	/* Parameter usage */


	/* Parameter usage */

/* 976 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 978 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 980 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */


	/* Return value */


	/* Return value */

/* 982 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 984 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 986 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Usage */


	/* Procedure put_Usage */

/* 988 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 990 */	NdrFcLong( 0x0 ),	/* 0 */
/* 994 */	NdrFcShort( 0x11 ),	/* 17 */
/* 996 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 998 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1000 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1002 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 1004 */	0xa,		/* 10 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 1006 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1008 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1010 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1012 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter usage */


	/* Parameter usage */

/* 1014 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1016 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 1018 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Return value */


	/* Return value */

/* 1020 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1022 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 1024 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_HorizontalDatum */

/* 1026 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1028 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1032 */	NdrFcShort( 0x12 ),	/* 18 */
/* 1034 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 1036 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1038 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1040 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 1042 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1044 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1046 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1048 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1050 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter datum */

/* 1052 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 1054 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 1056 */	NdrFcShort( 0x82 ),	/* Type Offset=130 */

	/* Return value */

/* 1058 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1060 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 1062 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_HorizontalDatum */

/* 1064 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1066 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1070 */	NdrFcShort( 0x13 ),	/* 19 */
/* 1072 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 1074 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1076 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1078 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 1080 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1082 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1084 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1086 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1088 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter datum */

/* 1090 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 1092 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 1094 */	NdrFcShort( 0x86 ),	/* Type Offset=134 */

	/* Return value */

/* 1096 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1098 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 1100 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_AngularUnit */

/* 1102 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1104 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1108 */	NdrFcShort( 0x14 ),	/* 20 */
/* 1110 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 1112 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1114 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1116 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 1118 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1120 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1122 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1124 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1126 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter unit */

/* 1128 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 1130 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 1132 */	NdrFcShort( 0x6c ),	/* Type Offset=108 */

	/* Return value */

/* 1134 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1136 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 1138 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_AngularUnit */

/* 1140 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1142 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1146 */	NdrFcShort( 0x15 ),	/* 21 */
/* 1148 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 1150 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1152 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1154 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 1156 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1158 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1160 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1162 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1164 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter unit */

/* 1166 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 1168 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 1170 */	NdrFcShort( 0x70 ),	/* Type Offset=112 */

	/* Return value */

/* 1172 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1174 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 1176 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_PrimeMeridian */

/* 1178 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1180 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1184 */	NdrFcShort( 0x16 ),	/* 22 */
/* 1186 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 1188 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1190 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1192 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 1194 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1196 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1198 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1200 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1202 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter prmMerid */

/* 1204 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 1206 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 1208 */	NdrFcShort( 0x98 ),	/* Type Offset=152 */

	/* Return value */

/* 1210 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1212 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 1214 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_PrimeMeridian */

/* 1216 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1218 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1222 */	NdrFcShort( 0x17 ),	/* 23 */
/* 1224 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 1226 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1228 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1230 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 1232 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1234 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1236 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1238 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1240 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter prmMerid */

/* 1242 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 1244 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 1246 */	NdrFcShort( 0x9c ),	/* Type Offset=156 */

	/* Return value */

/* 1248 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1250 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 1252 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_ValueUnit */

/* 1254 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1256 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1260 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1262 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 1264 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1266 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1268 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 1270 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1272 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1274 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1276 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1278 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter unit */

/* 1280 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 1282 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 1284 */	NdrFcShort( 0xae ),	/* Type Offset=174 */

	/* Return value */

/* 1286 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1288 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 1290 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_ValueUnit */

/* 1292 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1294 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1298 */	NdrFcShort( 0x11 ),	/* 17 */
/* 1300 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 1302 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1304 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1306 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 1308 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1310 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1312 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1314 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1316 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter unit */

/* 1318 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 1320 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 1322 */	NdrFcShort( 0xc0 ),	/* Type Offset=192 */

	/* Return value */

/* 1324 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1326 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 1328 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Value */

/* 1330 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1332 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1336 */	NdrFcShort( 0x12 ),	/* 18 */
/* 1338 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 1340 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1342 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1344 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 1346 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1348 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1350 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1352 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1354 */	NdrFcShort( 0x8 ),	/* 8 */

	/* Parameter value */

/* 1356 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1358 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 1360 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 1362 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1364 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 1366 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Value */

/* 1368 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1370 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1374 */	NdrFcShort( 0x13 ),	/* 19 */
/* 1376 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 1378 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1380 */	NdrFcShort( 0x2c ),	/* 44 */
/* 1382 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 1384 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1386 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1388 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1390 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1392 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter value */

/* 1394 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1396 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 1398 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 1400 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1402 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 1404 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_NumParameters */

/* 1406 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1408 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1412 */	NdrFcShort( 0x3 ),	/* 3 */
/* 1414 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 1416 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1418 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1420 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 1422 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1424 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1426 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1428 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1430 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter numParameters */

/* 1432 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1434 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 1436 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1438 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1440 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 1442 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_DefaultParameters */

/* 1444 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1446 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1450 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1452 */	NdrFcShort( 0x20 ),	/* ia64 Stack size/offset = 32 */
/* 1454 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1456 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1458 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 1460 */	0xa,		/* 10 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 1462 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1464 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1466 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1468 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter size */

/* 1470 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1472 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 1474 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter parameters */

/* 1476 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 1478 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 1480 */	NdrFcShort( 0xd6 ),	/* Type Offset=214 */

	/* Return value */

/* 1482 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1484 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 1486 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Parameters */

/* 1488 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1490 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1494 */	NdrFcShort( 0x5 ),	/* 5 */
/* 1496 */	NdrFcShort( 0x20 ),	/* ia64 Stack size/offset = 32 */
/* 1498 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1500 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1502 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 1504 */	0xa,		/* 10 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 1506 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1508 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1510 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1512 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter size */

/* 1514 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1516 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 1518 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter parameters */

/* 1520 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 1522 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 1524 */	NdrFcShort( 0xd6 ),	/* Type Offset=214 */

	/* Return value */

/* 1526 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1528 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 1530 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Parameters */

/* 1532 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1534 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1538 */	NdrFcShort( 0x6 ),	/* 6 */
/* 1540 */	NdrFcShort( 0x20 ),	/* ia64 Stack size/offset = 32 */
/* 1542 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1544 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1546 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 1548 */	0xa,		/* 10 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 1550 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1552 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1554 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1556 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter size */

/* 1558 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1560 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 1562 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter parameters */

/* 1564 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 1566 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 1568 */	NdrFcShort( 0xd6 ),	/* Type Offset=214 */

	/* Return value */

/* 1570 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1572 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 1574 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_SourceGCS */

/* 1576 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1578 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1582 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1584 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 1586 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1588 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1590 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 1592 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1594 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1596 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1598 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1600 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter gcs */

/* 1602 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 1604 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 1606 */	NdrFcShort( 0xec ),	/* Type Offset=236 */

	/* Return value */

/* 1608 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1610 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 1612 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_SourceGCS */

/* 1614 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1616 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1620 */	NdrFcShort( 0x11 ),	/* 17 */
/* 1622 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 1624 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1626 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1628 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 1630 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1632 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1634 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1636 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1638 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter gcs */

/* 1640 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 1642 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 1644 */	NdrFcShort( 0xf0 ),	/* Type Offset=240 */

	/* Return value */

/* 1646 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1648 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 1650 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_GeographicCoordinateSystem */


	/* Procedure get_TargetGCS */

/* 1652 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1654 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1658 */	NdrFcShort( 0x12 ),	/* 18 */
/* 1660 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 1662 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1664 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1666 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 1668 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1670 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1672 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1674 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1676 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter gcs */


	/* Parameter gcs */

/* 1678 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 1680 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 1682 */	NdrFcShort( 0xec ),	/* Type Offset=236 */

	/* Return value */


	/* Return value */

/* 1684 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1686 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 1688 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_GeographicCoordinateSystem */


	/* Procedure put_TargetGCS */

/* 1690 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1692 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1696 */	NdrFcShort( 0x13 ),	/* 19 */
/* 1698 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 1700 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1702 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1704 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 1706 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1708 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1710 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1712 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1714 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter gcs */


	/* Parameter gcs */

/* 1716 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 1718 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 1720 */	NdrFcShort( 0xf0 ),	/* Type Offset=240 */

	/* Return value */


	/* Return value */

/* 1722 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1724 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 1726 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_ParameterInfo */


	/* Procedure get_ParameterInfo */

/* 1728 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1730 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1734 */	NdrFcShort( 0x14 ),	/* 20 */
/* 1736 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 1738 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1740 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1742 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 1744 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1746 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1748 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1750 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1752 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter paramInfo */


	/* Parameter paramInfo */

/* 1754 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 1756 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 1758 */	NdrFcShort( 0x102 ),	/* Type Offset=258 */

	/* Return value */


	/* Return value */

/* 1760 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1762 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 1764 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Forward */

/* 1766 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1768 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1772 */	NdrFcShort( 0x15 ),	/* 21 */
/* 1774 */	NdrFcShort( 0x20 ),	/* ia64 Stack size/offset = 32 */
/* 1776 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1778 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1780 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 1782 */	0xa,		/* 10 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 1784 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1786 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1788 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1790 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter count */

/* 1792 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1794 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 1796 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter points */

/* 1798 */	NdrFcShort( 0x1b ),	/* Flags:  must size, must free, in, out, */
/* 1800 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 1802 */	NdrFcShort( 0x120 ),	/* Type Offset=288 */

	/* Return value */

/* 1804 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1806 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 1808 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Inverse */

/* 1810 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1812 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1816 */	NdrFcShort( 0x16 ),	/* 22 */
/* 1818 */	NdrFcShort( 0x20 ),	/* ia64 Stack size/offset = 32 */
/* 1820 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1822 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1824 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 1826 */	0xa,		/* 10 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 1828 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1830 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1832 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1834 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter count */

/* 1836 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1838 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 1840 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter points */

/* 1842 */	NdrFcShort( 0x1b ),	/* Flags:  must size, must free, in, out, */
/* 1844 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 1846 */	NdrFcShort( 0x120 ),	/* Type Offset=288 */

	/* Return value */

/* 1848 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1850 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 1852 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Classification */

/* 1854 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1856 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1860 */	NdrFcShort( 0x11 ),	/* 17 */
/* 1862 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 1864 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1866 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1868 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 1870 */	0xa,		/* 10 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 1872 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1874 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1876 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1878 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter classification */

/* 1880 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 1882 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 1884 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 1886 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1888 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 1890 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Forward */

/* 1892 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1894 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1898 */	NdrFcShort( 0x12 ),	/* 18 */
/* 1900 */	NdrFcShort( 0x20 ),	/* ia64 Stack size/offset = 32 */
/* 1902 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1904 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1906 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 1908 */	0xa,		/* 10 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 1910 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1912 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1914 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1916 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter count */

/* 1918 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1920 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 1922 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter points */

/* 1924 */	NdrFcShort( 0x1b ),	/* Flags:  must size, must free, in, out, */
/* 1926 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 1928 */	NdrFcShort( 0x120 ),	/* Type Offset=288 */

	/* Return value */

/* 1930 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1932 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 1934 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Inverse */

/* 1936 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1938 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1942 */	NdrFcShort( 0x13 ),	/* 19 */
/* 1944 */	NdrFcShort( 0x20 ),	/* ia64 Stack size/offset = 32 */
/* 1946 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1948 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1950 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 1952 */	0xa,		/* 10 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 1954 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1956 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1958 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1960 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter count */

/* 1962 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1964 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 1966 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter points */

/* 1968 */	NdrFcShort( 0x1b ),	/* Flags:  must size, must free, in, out, */
/* 1970 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 1972 */	NdrFcShort( 0x120 ),	/* Type Offset=288 */

	/* Return value */

/* 1974 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1976 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 1978 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_AngularUnit */

/* 1980 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1982 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1986 */	NdrFcShort( 0x15 ),	/* 21 */
/* 1988 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 1990 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1992 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1994 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 1996 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1998 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2000 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2002 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2004 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter unit */

/* 2006 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 2008 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 2010 */	NdrFcShort( 0x130 ),	/* Type Offset=304 */

	/* Return value */

/* 2012 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2014 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 2016 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_AngularUnit */

/* 2018 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2020 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2024 */	NdrFcShort( 0x16 ),	/* 22 */
/* 2026 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 2028 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2030 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2032 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 2034 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2036 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2038 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2040 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2042 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter unit */

/* 2044 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 2046 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 2048 */	NdrFcShort( 0x134 ),	/* Type Offset=308 */

	/* Return value */

/* 2050 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2052 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 2054 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_LinearUnit */

/* 2056 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2058 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2062 */	NdrFcShort( 0x17 ),	/* 23 */
/* 2064 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 2066 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2068 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2070 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 2072 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2074 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2076 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2078 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2080 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter unit */

/* 2082 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 2084 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 2086 */	NdrFcShort( 0x146 ),	/* Type Offset=326 */

	/* Return value */

/* 2088 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2090 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 2092 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_LinearUnit */

/* 2094 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2096 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2100 */	NdrFcShort( 0x18 ),	/* 24 */
/* 2102 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 2104 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2106 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2108 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 2110 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2112 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2114 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2116 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2118 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter unit */

/* 2120 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 2122 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 2124 */	NdrFcShort( 0x14a ),	/* Type Offset=330 */

	/* Return value */

/* 2126 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2128 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 2130 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Ellipsoid */

/* 2132 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2134 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2138 */	NdrFcShort( 0x19 ),	/* 25 */
/* 2140 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 2142 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2144 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2146 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 2148 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2150 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2152 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2154 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2156 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ellipsoid */

/* 2158 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 2160 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 2162 */	NdrFcShort( 0x15c ),	/* Type Offset=348 */

	/* Return value */

/* 2164 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2166 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 2168 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Ellipsoid */

/* 2170 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2172 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2176 */	NdrFcShort( 0x1a ),	/* 26 */
/* 2178 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 2180 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2182 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2184 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 2186 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2188 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2190 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2192 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2194 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ellipsoid */

/* 2196 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 2198 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 2200 */	NdrFcShort( 0x160 ),	/* Type Offset=352 */

	/* Return value */

/* 2202 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2204 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 2206 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_LinearUnit */

/* 2208 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2210 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2214 */	NdrFcShort( 0x14 ),	/* 20 */
/* 2216 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 2218 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2220 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2222 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 2224 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2226 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2228 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2230 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2232 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter unit */

/* 2234 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 2236 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 2238 */	NdrFcShort( 0x146 ),	/* Type Offset=326 */

	/* Return value */

/* 2240 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2242 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 2244 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_LinearUnit */

/* 2246 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2248 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2252 */	NdrFcShort( 0x15 ),	/* 21 */
/* 2254 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 2256 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2258 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2260 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 2262 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2264 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2266 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2268 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2270 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter unit */

/* 2272 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 2274 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 2276 */	NdrFcShort( 0x14a ),	/* Type Offset=330 */

	/* Return value */

/* 2278 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2280 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 2282 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Projection */

/* 2284 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2286 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2290 */	NdrFcShort( 0x16 ),	/* 22 */
/* 2292 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 2294 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2296 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2298 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 2300 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2302 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2304 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2306 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2308 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter projection */

/* 2310 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 2312 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 2314 */	NdrFcShort( 0x172 ),	/* Type Offset=370 */

	/* Return value */

/* 2316 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2318 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 2320 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Projection */

/* 2322 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2324 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2328 */	NdrFcShort( 0x17 ),	/* 23 */
/* 2330 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 2332 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2334 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2336 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 2338 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2340 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2342 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2344 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2346 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter projection */

/* 2348 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 2350 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 2352 */	NdrFcShort( 0x176 ),	/* Type Offset=374 */

	/* Return value */

/* 2354 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2356 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 2358 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_ParameterInfo */

/* 2360 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2362 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2366 */	NdrFcShort( 0x18 ),	/* 24 */
/* 2368 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 2370 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2372 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2374 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 2376 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2378 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2380 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2382 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2384 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter paramInfo */

/* 2386 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 2388 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 2390 */	NdrFcShort( 0x102 ),	/* Type Offset=258 */

	/* Return value */

/* 2392 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2394 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 2396 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Forward */

/* 2398 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2400 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2404 */	NdrFcShort( 0x19 ),	/* 25 */
/* 2406 */	NdrFcShort( 0x20 ),	/* ia64 Stack size/offset = 32 */
/* 2408 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2410 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2412 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 2414 */	0xa,		/* 10 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 2416 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2418 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2420 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2422 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter count */

/* 2424 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2426 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 2428 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter points */

/* 2430 */	NdrFcShort( 0x1b ),	/* Flags:  must size, must free, in, out, */
/* 2432 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 2434 */	NdrFcShort( 0x120 ),	/* Type Offset=288 */

	/* Return value */

/* 2436 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2438 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 2440 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Inverse */

/* 2442 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2444 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2448 */	NdrFcShort( 0x1a ),	/* 26 */
/* 2450 */	NdrFcShort( 0x20 ),	/* ia64 Stack size/offset = 32 */
/* 2452 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2454 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2456 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 2458 */	0xa,		/* 10 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 2460 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2462 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2464 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2466 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter count */

/* 2468 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2470 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 2472 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter points */

/* 2474 */	NdrFcShort( 0x1b ),	/* Flags:  must size, must free, in, out, */
/* 2476 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 2478 */	NdrFcShort( 0x120 ),	/* Type Offset=288 */

	/* Return value */

/* 2480 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2482 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 2484 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure CreateFromWKT */

/* 2486 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2488 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2492 */	NdrFcShort( 0x3 ),	/* 3 */
/* 2494 */	NdrFcShort( 0x20 ),	/* ia64 Stack size/offset = 32 */
/* 2496 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2498 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2500 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 2502 */	0xa,		/* 10 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 2504 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2506 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2508 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2510 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter wktSpatialReference */

/* 2512 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2514 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 2516 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Parameter sref */

/* 2518 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 2520 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 2522 */	NdrFcShort( 0x188 ),	/* Type Offset=392 */

	/* Return value */

/* 2524 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2526 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 2528 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure CreateProjectedCoordinateSystem */

/* 2530 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2532 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2536 */	NdrFcShort( 0x4 ),	/* 4 */
/* 2538 */	NdrFcShort( 0x20 ),	/* ia64 Stack size/offset = 32 */
/* 2540 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2542 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2544 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 2546 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2548 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2550 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2552 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2554 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter code */

/* 2556 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2558 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 2560 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pcs */

/* 2562 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 2564 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 2566 */	NdrFcShort( 0x19e ),	/* Type Offset=414 */

	/* Return value */

/* 2568 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2570 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 2572 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure CreateGeographicCoordinateSystem */

/* 2574 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2576 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2580 */	NdrFcShort( 0x5 ),	/* 5 */
/* 2582 */	NdrFcShort( 0x20 ),	/* ia64 Stack size/offset = 32 */
/* 2584 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2586 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2588 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 2590 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2592 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2594 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2596 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2598 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter code */

/* 2600 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2602 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 2604 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter gcs */

/* 2606 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 2608 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 2610 */	NdrFcShort( 0xec ),	/* Type Offset=236 */

	/* Return value */

/* 2612 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2614 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 2616 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure CreateProjection */

/* 2618 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2620 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2624 */	NdrFcShort( 0x6 ),	/* 6 */
/* 2626 */	NdrFcShort( 0x20 ),	/* ia64 Stack size/offset = 32 */
/* 2628 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2630 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2632 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 2634 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2636 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2638 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2640 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2642 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter code */

/* 2644 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2646 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 2648 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter projection */

/* 2650 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 2652 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 2654 */	NdrFcShort( 0x172 ),	/* Type Offset=370 */

	/* Return value */

/* 2656 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2658 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 2660 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure CreateGeographicTransform */

/* 2662 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2664 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2668 */	NdrFcShort( 0x7 ),	/* 7 */
/* 2670 */	NdrFcShort( 0x20 ),	/* ia64 Stack size/offset = 32 */
/* 2672 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2674 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2676 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 2678 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2680 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2682 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2684 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2686 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter code */

/* 2688 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2690 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 2692 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter gt */

/* 2694 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 2696 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 2698 */	NdrFcShort( 0x1b4 ),	/* Type Offset=436 */

	/* Return value */

/* 2700 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2702 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 2704 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure CreateHorizontalDatum */

/* 2706 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2708 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2712 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2714 */	NdrFcShort( 0x20 ),	/* ia64 Stack size/offset = 32 */
/* 2716 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2718 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2720 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 2722 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2724 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2726 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2728 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2730 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter code */

/* 2732 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2734 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 2736 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter datum */

/* 2738 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 2740 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 2742 */	NdrFcShort( 0x1ca ),	/* Type Offset=458 */

	/* Return value */

/* 2744 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2746 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 2748 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure CreateEllipsoid */

/* 2750 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2752 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2756 */	NdrFcShort( 0x9 ),	/* 9 */
/* 2758 */	NdrFcShort( 0x20 ),	/* ia64 Stack size/offset = 32 */
/* 2760 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2762 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2764 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 2766 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2768 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2770 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2772 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2774 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter code */

/* 2776 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2778 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 2780 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter ellipsoid */

/* 2782 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 2784 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 2786 */	NdrFcShort( 0x1e0 ),	/* Type Offset=480 */

	/* Return value */

/* 2788 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2790 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 2792 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure CreatePrimeMeridian */

/* 2794 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2796 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2800 */	NdrFcShort( 0xa ),	/* 10 */
/* 2802 */	NdrFcShort( 0x20 ),	/* ia64 Stack size/offset = 32 */
/* 2804 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2806 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2808 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 2810 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2812 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2814 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2816 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2818 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter code */

/* 2820 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2822 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 2824 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter prmMerid */

/* 2826 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 2828 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 2830 */	NdrFcShort( 0x1f6 ),	/* Type Offset=502 */

	/* Return value */

/* 2832 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2834 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 2836 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure CreateLinearUnit */

/* 2838 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2840 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2844 */	NdrFcShort( 0xb ),	/* 11 */
/* 2846 */	NdrFcShort( 0x20 ),	/* ia64 Stack size/offset = 32 */
/* 2848 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2850 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2852 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 2854 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2856 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2858 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2860 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2862 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter code */

/* 2864 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2866 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 2868 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter unit */

/* 2870 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 2872 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 2874 */	NdrFcShort( 0x20c ),	/* Type Offset=524 */

	/* Return value */

/* 2876 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2878 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 2880 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure CreateAngularUnit */

/* 2882 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2884 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2888 */	NdrFcShort( 0xc ),	/* 12 */
/* 2890 */	NdrFcShort( 0x20 ),	/* ia64 Stack size/offset = 32 */
/* 2892 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2894 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2896 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 2898 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2900 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2902 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2904 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2906 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter code */

/* 2908 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2910 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 2912 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter unit */

/* 2914 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 2916 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 2918 */	NdrFcShort( 0x222 ),	/* Type Offset=546 */

	/* Return value */

/* 2920 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2922 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 2924 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

			0x0
        }
    };

static const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */
/*  2 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/*  4 */	NdrFcShort( 0x1c ),	/* Offset= 28 (32) */
/*  6 */	
			0x13, 0x0,	/* FC_OP */
/*  8 */	NdrFcShort( 0xe ),	/* Offset= 14 (22) */
/* 10 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 12 */	NdrFcShort( 0x2 ),	/* 2 */
/* 14 */	0x9,		/* Corr desc: FC_ULONG */
			0x0,		/*  */
/* 16 */	NdrFcShort( 0xfffc ),	/* -4 */
/* 18 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 20 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 22 */	
			0x17,		/* FC_CSTRUCT */
			0x3,		/* 3 */
/* 24 */	NdrFcShort( 0x8 ),	/* 8 */
/* 26 */	NdrFcShort( 0xfffffff0 ),	/* Offset= -16 (10) */
/* 28 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 30 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 32 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 34 */	NdrFcShort( 0x0 ),	/* 0 */
/* 36 */	NdrFcShort( 0x8 ),	/* 8 */
/* 38 */	NdrFcShort( 0x0 ),	/* 0 */
/* 40 */	NdrFcShort( 0xffffffde ),	/* Offset= -34 (6) */
/* 42 */	
			0x12, 0x0,	/* FC_UP */
/* 44 */	NdrFcShort( 0xffffffea ),	/* Offset= -22 (22) */
/* 46 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 48 */	NdrFcShort( 0x0 ),	/* 0 */
/* 50 */	NdrFcShort( 0x8 ),	/* 8 */
/* 52 */	NdrFcShort( 0x0 ),	/* 0 */
/* 54 */	NdrFcShort( 0xfffffff4 ),	/* Offset= -12 (42) */
/* 56 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 58 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 60 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 62 */	0xc,		/* FC_DOUBLE */
			0x5c,		/* FC_PAD */
/* 64 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 66 */	NdrFcShort( 0x2 ),	/* Offset= 2 (68) */
/* 68 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 70 */	NdrFcLong( 0x80855df0 ),	/* -2138743312 */
/* 74 */	NdrFcShort( 0xfe1d ),	/* -483 */
/* 76 */	NdrFcShort( 0x11d0 ),	/* 4560 */
/* 78 */	0xad,		/* 173 */
			0x87,		/* 135 */
/* 80 */	0x8,		/* 8 */
			0x0,		/* 0 */
/* 82 */	0x9,		/* 9 */
			0xb6,		/* 182 */
/* 84 */	0xf2,		/* 242 */
			0x2b,		/* 43 */
/* 86 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 88 */	NdrFcShort( 0x2 ),	/* Offset= 2 (90) */
/* 90 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 92 */	NdrFcLong( 0xce7266c0 ),	/* -831363392 */
/* 96 */	NdrFcShort( 0xfe1d ),	/* -483 */
/* 98 */	NdrFcShort( 0x11d0 ),	/* 4560 */
/* 100 */	0xad,		/* 173 */
			0x87,		/* 135 */
/* 102 */	0x8,		/* 8 */
			0x0,		/* 0 */
/* 104 */	0x9,		/* 9 */
			0xb6,		/* 182 */
/* 106 */	0xf2,		/* 242 */
			0x2b,		/* 43 */
/* 108 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 110 */	NdrFcShort( 0x2 ),	/* Offset= 2 (112) */
/* 112 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 114 */	NdrFcLong( 0x4febc550 ),	/* 1340851536 */
/* 118 */	NdrFcShort( 0xfe1d ),	/* -483 */
/* 120 */	NdrFcShort( 0x11d0 ),	/* 4560 */
/* 122 */	0xad,		/* 173 */
			0x87,		/* 135 */
/* 124 */	0x8,		/* 8 */
			0x0,		/* 0 */
/* 126 */	0x9,		/* 9 */
			0xb6,		/* 182 */
/* 128 */	0xf2,		/* 242 */
			0x2b,		/* 43 */
/* 130 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 132 */	NdrFcShort( 0x2 ),	/* Offset= 2 (134) */
/* 134 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 136 */	NdrFcLong( 0xf699c510 ),	/* -157694704 */
/* 140 */	NdrFcShort( 0xfe1d ),	/* -483 */
/* 142 */	NdrFcShort( 0x11d0 ),	/* 4560 */
/* 144 */	0xad,		/* 173 */
			0x87,		/* 135 */
/* 146 */	0x8,		/* 8 */
			0x0,		/* 0 */
/* 148 */	0x9,		/* 9 */
			0xb6,		/* 182 */
/* 150 */	0xf2,		/* 242 */
			0x2b,		/* 43 */
/* 152 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 154 */	NdrFcShort( 0x2 ),	/* Offset= 2 (156) */
/* 156 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 158 */	NdrFcLong( 0x15129940 ),	/* 353540416 */
/* 162 */	NdrFcShort( 0xfe1e ),	/* -482 */
/* 164 */	NdrFcShort( 0x11d0 ),	/* 4560 */
/* 166 */	0xad,		/* 173 */
			0x87,		/* 135 */
/* 168 */	0x8,		/* 8 */
			0x0,		/* 0 */
/* 170 */	0x9,		/* 9 */
			0xb6,		/* 182 */
/* 172 */	0xf2,		/* 242 */
			0x2b,		/* 43 */
/* 174 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 176 */	NdrFcLong( 0x221733b0 ),	/* 571945904 */
/* 180 */	NdrFcShort( 0xfe1d ),	/* -483 */
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
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 194 */	NdrFcShort( 0xffffffec ),	/* Offset= -20 (174) */
/* 196 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 198 */	NdrFcLong( 0x9a5e32d0 ),	/* -1705102640 */
/* 202 */	NdrFcShort( 0xfe1f ),	/* -481 */
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
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 216 */	NdrFcShort( 0x0 ),	/* 0 */
/* 218 */	0x28,		/* Corr desc:  parameter, FC_LONG */
			0x0,		/*  */
/* 220 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 222 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 224 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 228 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 230 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 232 */	NdrFcShort( 0xffffffdc ),	/* Offset= -36 (196) */
/* 234 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 236 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 238 */	NdrFcShort( 0x2 ),	/* Offset= 2 (240) */
/* 240 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 242 */	NdrFcLong( 0xa3fd5390 ),	/* -1543679088 */
/* 246 */	NdrFcShort( 0xfe1e ),	/* -482 */
/* 248 */	NdrFcShort( 0x11d0 ),	/* 4560 */
/* 250 */	0xad,		/* 173 */
			0x87,		/* 135 */
/* 252 */	0x8,		/* 8 */
			0x0,		/* 0 */
/* 254 */	0x9,		/* 9 */
			0xb6,		/* 182 */
/* 256 */	0xf2,		/* 242 */
			0x2b,		/* 43 */
/* 258 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 260 */	NdrFcShort( 0x2 ),	/* Offset= 2 (262) */
/* 262 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 264 */	NdrFcLong( 0x7309b460 ),	/* 1930015840 */
/* 268 */	NdrFcShort( 0xfe1f ),	/* -481 */
/* 270 */	NdrFcShort( 0x11d0 ),	/* 4560 */
/* 272 */	0xad,		/* 173 */
			0x87,		/* 135 */
/* 274 */	0x8,		/* 8 */
			0x0,		/* 0 */
/* 276 */	0x9,		/* 9 */
			0xb6,		/* 182 */
/* 278 */	0xf2,		/* 242 */
			0x2b,		/* 43 */
/* 280 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 282 */	NdrFcShort( 0x10 ),	/* 16 */
/* 284 */	0xc,		/* FC_DOUBLE */
			0xc,		/* FC_DOUBLE */
/* 286 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 288 */	
			0x1b,		/* FC_CARRAY */
			0x7,		/* 7 */
/* 290 */	NdrFcShort( 0x10 ),	/* 16 */
/* 292 */	0x28,		/* Corr desc:  parameter, FC_LONG */
			0x0,		/*  */
/* 294 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 296 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 298 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 300 */	NdrFcShort( 0xffffffec ),	/* Offset= -20 (280) */
/* 302 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 304 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 306 */	NdrFcShort( 0x2 ),	/* Offset= 2 (308) */
/* 308 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 310 */	NdrFcLong( 0x4febc550 ),	/* 1340851536 */
/* 314 */	NdrFcShort( 0xfe1d ),	/* -483 */
/* 316 */	NdrFcShort( 0x11d0 ),	/* 4560 */
/* 318 */	0xad,		/* 173 */
			0x87,		/* 135 */
/* 320 */	0x8,		/* 8 */
			0x0,		/* 0 */
/* 322 */	0x9,		/* 9 */
			0xb6,		/* 182 */
/* 324 */	0xf2,		/* 242 */
			0x2b,		/* 43 */
/* 326 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 328 */	NdrFcShort( 0x2 ),	/* Offset= 2 (330) */
/* 330 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 332 */	NdrFcLong( 0x80855df0 ),	/* -2138743312 */
/* 336 */	NdrFcShort( 0xfe1d ),	/* -483 */
/* 338 */	NdrFcShort( 0x11d0 ),	/* 4560 */
/* 340 */	0xad,		/* 173 */
			0x87,		/* 135 */
/* 342 */	0x8,		/* 8 */
			0x0,		/* 0 */
/* 344 */	0x9,		/* 9 */
			0xb6,		/* 182 */
/* 346 */	0xf2,		/* 242 */
			0x2b,		/* 43 */
/* 348 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 350 */	NdrFcShort( 0x2 ),	/* Offset= 2 (352) */
/* 352 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 354 */	NdrFcLong( 0xce7266c0 ),	/* -831363392 */
/* 358 */	NdrFcShort( 0xfe1d ),	/* -483 */
/* 360 */	NdrFcShort( 0x11d0 ),	/* 4560 */
/* 362 */	0xad,		/* 173 */
			0x87,		/* 135 */
/* 364 */	0x8,		/* 8 */
			0x0,		/* 0 */
/* 366 */	0x9,		/* 9 */
			0xb6,		/* 182 */
/* 368 */	0xf2,		/* 242 */
			0x2b,		/* 43 */
/* 370 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 372 */	NdrFcShort( 0x2 ),	/* Offset= 2 (374) */
/* 374 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 376 */	NdrFcLong( 0x5002f420 ),	/* 1342370848 */
/* 380 */	NdrFcShort( 0xfe1f ),	/* -481 */
/* 382 */	NdrFcShort( 0x11d0 ),	/* 4560 */
/* 384 */	0xad,		/* 173 */
			0x87,		/* 135 */
/* 386 */	0x8,		/* 8 */
			0x0,		/* 0 */
/* 388 */	0x9,		/* 9 */
			0xb6,		/* 182 */
/* 390 */	0xf2,		/* 242 */
			0x2b,		/* 43 */
/* 392 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 394 */	NdrFcShort( 0x2 ),	/* Offset= 2 (396) */
/* 396 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 398 */	NdrFcLong( 0x4c4c5c00 ),	/* 1280072704 */
/* 402 */	NdrFcShort( 0xfe1e ),	/* -482 */
/* 404 */	NdrFcShort( 0x11d0 ),	/* 4560 */
/* 406 */	0xad,		/* 173 */
			0x87,		/* 135 */
/* 408 */	0x8,		/* 8 */
			0x0,		/* 0 */
/* 410 */	0x9,		/* 9 */
			0xb6,		/* 182 */
/* 412 */	0xf2,		/* 242 */
			0x2b,		/* 43 */
/* 414 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 416 */	NdrFcShort( 0x2 ),	/* Offset= 2 (418) */
/* 418 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 420 */	NdrFcLong( 0x3dc39ff0 ),	/* 1036230640 */
/* 424 */	NdrFcShort( 0xfe1f ),	/* -481 */
/* 426 */	NdrFcShort( 0x11d0 ),	/* 4560 */
/* 428 */	0xad,		/* 173 */
			0x87,		/* 135 */
/* 430 */	0x8,		/* 8 */
			0x0,		/* 0 */
/* 432 */	0x9,		/* 9 */
			0xb6,		/* 182 */
/* 434 */	0xf2,		/* 242 */
			0x2b,		/* 43 */
/* 436 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 438 */	NdrFcShort( 0x2 ),	/* Offset= 2 (440) */
/* 440 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 442 */	NdrFcLong( 0x5eb513c0 ),	/* 1588925376 */
/* 446 */	NdrFcShort( 0xfe1f ),	/* -481 */
/* 448 */	NdrFcShort( 0x11d0 ),	/* 4560 */
/* 450 */	0xad,		/* 173 */
			0x87,		/* 135 */
/* 452 */	0x8,		/* 8 */
			0x0,		/* 0 */
/* 454 */	0x9,		/* 9 */
			0xb6,		/* 182 */
/* 456 */	0xf2,		/* 242 */
			0x2b,		/* 43 */
/* 458 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 460 */	NdrFcShort( 0x2 ),	/* Offset= 2 (462) */
/* 462 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 464 */	NdrFcLong( 0xf699c510 ),	/* -157694704 */
/* 468 */	NdrFcShort( 0xfe1d ),	/* -483 */
/* 470 */	NdrFcShort( 0x11d0 ),	/* 4560 */
/* 472 */	0xad,		/* 173 */
			0x87,		/* 135 */
/* 474 */	0x8,		/* 8 */
			0x0,		/* 0 */
/* 476 */	0x9,		/* 9 */
			0xb6,		/* 182 */
/* 478 */	0xf2,		/* 242 */
			0x2b,		/* 43 */
/* 480 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 482 */	NdrFcShort( 0x2 ),	/* Offset= 2 (484) */
/* 484 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 486 */	NdrFcLong( 0xce7266c0 ),	/* -831363392 */
/* 490 */	NdrFcShort( 0xfe1d ),	/* -483 */
/* 492 */	NdrFcShort( 0x11d0 ),	/* 4560 */
/* 494 */	0xad,		/* 173 */
			0x87,		/* 135 */
/* 496 */	0x8,		/* 8 */
			0x0,		/* 0 */
/* 498 */	0x9,		/* 9 */
			0xb6,		/* 182 */
/* 500 */	0xf2,		/* 242 */
			0x2b,		/* 43 */
/* 502 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 504 */	NdrFcShort( 0x2 ),	/* Offset= 2 (506) */
/* 506 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 508 */	NdrFcLong( 0x15129940 ),	/* 353540416 */
/* 512 */	NdrFcShort( 0xfe1e ),	/* -482 */
/* 514 */	NdrFcShort( 0x11d0 ),	/* 4560 */
/* 516 */	0xad,		/* 173 */
			0x87,		/* 135 */
/* 518 */	0x8,		/* 8 */
			0x0,		/* 0 */
/* 520 */	0x9,		/* 9 */
			0xb6,		/* 182 */
/* 522 */	0xf2,		/* 242 */
			0x2b,		/* 43 */
/* 524 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 526 */	NdrFcShort( 0x2 ),	/* Offset= 2 (528) */
/* 528 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 530 */	NdrFcLong( 0x80855df0 ),	/* -2138743312 */
/* 534 */	NdrFcShort( 0xfe1d ),	/* -483 */
/* 536 */	NdrFcShort( 0x11d0 ),	/* 4560 */
/* 538 */	0xad,		/* 173 */
			0x87,		/* 135 */
/* 540 */	0x8,		/* 8 */
			0x0,		/* 0 */
/* 542 */	0x9,		/* 9 */
			0xb6,		/* 182 */
/* 544 */	0xf2,		/* 242 */
			0x2b,		/* 43 */
/* 546 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 548 */	NdrFcShort( 0x2 ),	/* Offset= 2 (550) */
/* 550 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 552 */	NdrFcLong( 0x4febc550 ),	/* 1340851536 */
/* 556 */	NdrFcShort( 0xfe1d ),	/* -483 */
/* 558 */	NdrFcShort( 0x11d0 ),	/* 4560 */
/* 560 */	0xad,		/* 173 */
			0x87,		/* 135 */
/* 562 */	0x8,		/* 8 */
			0x0,		/* 0 */
/* 564 */	0x9,		/* 9 */
			0xb6,		/* 182 */
/* 566 */	0xf2,		/* 242 */
			0x2b,		/* 43 */

			0x0
        }
    };

static const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ] = 
        {
            
            {
            BSTR_UserSize
            ,BSTR_UserMarshal
            ,BSTR_UserUnmarshal
            ,BSTR_UserFree
            }

        };



/* Standard interface: __MIDL_itf_SpatialReference_0000, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}} */


/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: ISpatialReferenceInfo, ver. 0.0,
   GUID={0xbcca38a0,0xfe1c,0x11d0,{0xad,0x87,0x08,0x00,0x09,0xb6,0xf2,0x2b}} */

#pragma code_seg(".orpc")
static const unsigned short ISpatialReferenceInfo_FormatStringOffsetTable[] =
    {
    0,
    38,
    76,
    114,
    152,
    190,
    228,
    266,
    304,
    342,
    380,
    418,
    456
    };

static const MIDL_STUBLESS_PROXY_INFO ISpatialReferenceInfo_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &ISpatialReferenceInfo_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO ISpatialReferenceInfo_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &ISpatialReferenceInfo_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(16) _ISpatialReferenceInfoProxyVtbl = 
{
    &ISpatialReferenceInfo_ProxyInfo,
    &IID_ISpatialReferenceInfo,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_Name */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::put_Name */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_Authority */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::put_Authority */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_Code */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::put_Code */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_Alias */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::put_Alias */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_Abbreviation */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::put_Abbreviation */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_Remarks */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::put_Remarks */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_WellKnownText */
};

const CInterfaceStubVtbl _ISpatialReferenceInfoStubVtbl =
{
    &IID_ISpatialReferenceInfo,
    &ISpatialReferenceInfo_ServerInfo,
    16,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IUnit, ver. 0.0,
   GUID={0x221733b0,0xfe1d,0x11d0,{0xad,0x87,0x08,0x00,0x09,0xb6,0xf2,0x2b}} */

#pragma code_seg(".orpc")
static const unsigned short IUnit_FormatStringOffsetTable[] =
    {
    0,
    38,
    76,
    114,
    152,
    190,
    228,
    266,
    304,
    342,
    380,
    418,
    456,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO IUnit_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IUnit_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IUnit_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IUnit_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(16) _IUnitProxyVtbl = 
{
    0,
    &IID_IUnit,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* forced delegation ISpatialReferenceInfo::get_Name */ ,
    0 /* forced delegation ISpatialReferenceInfo::put_Name */ ,
    0 /* forced delegation ISpatialReferenceInfo::get_Authority */ ,
    0 /* forced delegation ISpatialReferenceInfo::put_Authority */ ,
    0 /* forced delegation ISpatialReferenceInfo::get_Code */ ,
    0 /* forced delegation ISpatialReferenceInfo::put_Code */ ,
    0 /* forced delegation ISpatialReferenceInfo::get_Alias */ ,
    0 /* forced delegation ISpatialReferenceInfo::put_Alias */ ,
    0 /* forced delegation ISpatialReferenceInfo::get_Abbreviation */ ,
    0 /* forced delegation ISpatialReferenceInfo::put_Abbreviation */ ,
    0 /* forced delegation ISpatialReferenceInfo::get_Remarks */ ,
    0 /* forced delegation ISpatialReferenceInfo::put_Remarks */ ,
    0 /* forced delegation ISpatialReferenceInfo::get_WellKnownText */
};


static const PRPC_STUB_FUNCTION IUnit_table[] =
{
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IUnitStubVtbl =
{
    &IID_IUnit,
    &IUnit_ServerInfo,
    16,
    &IUnit_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IAngularUnit, ver. 0.0,
   GUID={0x4febc550,0xfe1d,0x11d0,{0xad,0x87,0x08,0x00,0x09,0xb6,0xf2,0x2b}} */

#pragma code_seg(".orpc")
static const unsigned short IAngularUnit_FormatStringOffsetTable[] =
    {
    0,
    38,
    76,
    114,
    152,
    190,
    228,
    266,
    304,
    342,
    380,
    418,
    456,
    494,
    532
    };

static const MIDL_STUBLESS_PROXY_INFO IAngularUnit_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IAngularUnit_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IAngularUnit_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IAngularUnit_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(18) _IAngularUnitProxyVtbl = 
{
    &IAngularUnit_ProxyInfo,
    &IID_IAngularUnit,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_Name */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::put_Name */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_Authority */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::put_Authority */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_Code */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::put_Code */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_Alias */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::put_Alias */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_Abbreviation */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::put_Abbreviation */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_Remarks */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::put_Remarks */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_WellKnownText */ ,
    (void *) (INT_PTR) -1 /* IAngularUnit::get_RadiansPerUnit */ ,
    (void *) (INT_PTR) -1 /* IAngularUnit::put_RadiansPerUnit */
};

const CInterfaceStubVtbl _IAngularUnitStubVtbl =
{
    &IID_IAngularUnit,
    &IAngularUnit_ServerInfo,
    18,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: ILinearUnit, ver. 0.0,
   GUID={0x80855df0,0xfe1d,0x11d0,{0xad,0x87,0x08,0x00,0x09,0xb6,0xf2,0x2b}} */

#pragma code_seg(".orpc")
static const unsigned short ILinearUnit_FormatStringOffsetTable[] =
    {
    0,
    38,
    76,
    114,
    152,
    190,
    228,
    266,
    304,
    342,
    380,
    418,
    456,
    494,
    532
    };

static const MIDL_STUBLESS_PROXY_INFO ILinearUnit_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &ILinearUnit_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO ILinearUnit_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &ILinearUnit_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(18) _ILinearUnitProxyVtbl = 
{
    &ILinearUnit_ProxyInfo,
    &IID_ILinearUnit,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_Name */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::put_Name */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_Authority */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::put_Authority */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_Code */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::put_Code */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_Alias */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::put_Alias */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_Abbreviation */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::put_Abbreviation */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_Remarks */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::put_Remarks */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_WellKnownText */ ,
    (void *) (INT_PTR) -1 /* ILinearUnit::get_MetersPerUnit */ ,
    (void *) (INT_PTR) -1 /* ILinearUnit::put_MetersPerUnit */
};

const CInterfaceStubVtbl _ILinearUnitStubVtbl =
{
    &IID_ILinearUnit,
    &ILinearUnit_ServerInfo,
    18,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IEllipsoid, ver. 0.0,
   GUID={0xce7266c0,0xfe1d,0x11d0,{0xad,0x87,0x08,0x00,0x09,0xb6,0xf2,0x2b}} */

#pragma code_seg(".orpc")
static const unsigned short IEllipsoid_FormatStringOffsetTable[] =
    {
    0,
    38,
    76,
    114,
    152,
    190,
    228,
    266,
    304,
    342,
    380,
    418,
    456,
    494,
    532,
    570,
    608,
    646,
    684,
    722,
    760
    };

static const MIDL_STUBLESS_PROXY_INFO IEllipsoid_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IEllipsoid_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IEllipsoid_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IEllipsoid_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(24) _IEllipsoidProxyVtbl = 
{
    &IEllipsoid_ProxyInfo,
    &IID_IEllipsoid,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_Name */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::put_Name */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_Authority */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::put_Authority */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_Code */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::put_Code */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_Alias */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::put_Alias */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_Abbreviation */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::put_Abbreviation */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_Remarks */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::put_Remarks */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_WellKnownText */ ,
    (void *) (INT_PTR) -1 /* IEllipsoid::get_SemiMajorAxis */ ,
    (void *) (INT_PTR) -1 /* IEllipsoid::put_SemiMajorAxis */ ,
    (void *) (INT_PTR) -1 /* IEllipsoid::get_SemiMinorAxis */ ,
    (void *) (INT_PTR) -1 /* IEllipsoid::put_SemiMinorAxis */ ,
    (void *) (INT_PTR) -1 /* IEllipsoid::get_InverseFlattening */ ,
    (void *) (INT_PTR) -1 /* IEllipsoid::put_InverseFlattening */ ,
    (void *) (INT_PTR) -1 /* IEllipsoid::get_AxisUnit */ ,
    (void *) (INT_PTR) -1 /* IEllipsoid::put_AxisUnit */
};

const CInterfaceStubVtbl _IEllipsoidStubVtbl =
{
    &IID_IEllipsoid,
    &IEllipsoid_ServerInfo,
    24,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IHorizontalDatum, ver. 0.0,
   GUID={0xf699c510,0xfe1d,0x11d0,{0xad,0x87,0x08,0x00,0x09,0xb6,0xf2,0x2b}} */

#pragma code_seg(".orpc")
static const unsigned short IHorizontalDatum_FormatStringOffsetTable[] =
    {
    0,
    38,
    76,
    114,
    152,
    190,
    228,
    266,
    304,
    342,
    380,
    418,
    456,
    798,
    836
    };

static const MIDL_STUBLESS_PROXY_INFO IHorizontalDatum_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IHorizontalDatum_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IHorizontalDatum_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IHorizontalDatum_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(18) _IHorizontalDatumProxyVtbl = 
{
    &IHorizontalDatum_ProxyInfo,
    &IID_IHorizontalDatum,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_Name */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::put_Name */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_Authority */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::put_Authority */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_Code */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::put_Code */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_Alias */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::put_Alias */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_Abbreviation */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::put_Abbreviation */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_Remarks */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::put_Remarks */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_WellKnownText */ ,
    (void *) (INT_PTR) -1 /* IHorizontalDatum::get_Ellipsoid */ ,
    (void *) (INT_PTR) -1 /* IHorizontalDatum::put_Ellipsoid */
};

const CInterfaceStubVtbl _IHorizontalDatumStubVtbl =
{
    &IID_IHorizontalDatum,
    &IHorizontalDatum_ServerInfo,
    18,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IPrimeMeridian, ver. 0.0,
   GUID={0x15129940,0xfe1e,0x11d0,{0xad,0x87,0x08,0x00,0x09,0xb6,0xf2,0x2b}} */

#pragma code_seg(".orpc")
static const unsigned short IPrimeMeridian_FormatStringOffsetTable[] =
    {
    0,
    38,
    76,
    114,
    152,
    190,
    228,
    266,
    304,
    342,
    380,
    418,
    456,
    494,
    532,
    874,
    912
    };

static const MIDL_STUBLESS_PROXY_INFO IPrimeMeridian_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IPrimeMeridian_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IPrimeMeridian_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IPrimeMeridian_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(20) _IPrimeMeridianProxyVtbl = 
{
    &IPrimeMeridian_ProxyInfo,
    &IID_IPrimeMeridian,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_Name */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::put_Name */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_Authority */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::put_Authority */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_Code */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::put_Code */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_Alias */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::put_Alias */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_Abbreviation */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::put_Abbreviation */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_Remarks */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::put_Remarks */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_WellKnownText */ ,
    (void *) (INT_PTR) -1 /* IPrimeMeridian::get_Longitude */ ,
    (void *) (INT_PTR) -1 /* IPrimeMeridian::put_Longitude */ ,
    (void *) (INT_PTR) -1 /* IPrimeMeridian::get_AngularUnit */ ,
    (void *) (INT_PTR) -1 /* IPrimeMeridian::put_AngularUnit */
};

const CInterfaceStubVtbl _IPrimeMeridianStubVtbl =
{
    &IID_IPrimeMeridian,
    &IPrimeMeridian_ServerInfo,
    20,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: ISpatialReference, ver. 0.0,
   GUID={0x4c4c5c00,0xfe1e,0x11d0,{0xad,0x87,0x08,0x00,0x09,0xb6,0xf2,0x2b}} */

#pragma code_seg(".orpc")
static const unsigned short ISpatialReference_FormatStringOffsetTable[] =
    {
    0,
    38,
    76,
    114,
    152,
    190,
    228,
    266,
    304,
    342,
    380,
    418,
    456,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO ISpatialReference_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &ISpatialReference_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO ISpatialReference_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &ISpatialReference_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(16) _ISpatialReferenceProxyVtbl = 
{
    0,
    &IID_ISpatialReference,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* forced delegation ISpatialReferenceInfo::get_Name */ ,
    0 /* forced delegation ISpatialReferenceInfo::put_Name */ ,
    0 /* forced delegation ISpatialReferenceInfo::get_Authority */ ,
    0 /* forced delegation ISpatialReferenceInfo::put_Authority */ ,
    0 /* forced delegation ISpatialReferenceInfo::get_Code */ ,
    0 /* forced delegation ISpatialReferenceInfo::put_Code */ ,
    0 /* forced delegation ISpatialReferenceInfo::get_Alias */ ,
    0 /* forced delegation ISpatialReferenceInfo::put_Alias */ ,
    0 /* forced delegation ISpatialReferenceInfo::get_Abbreviation */ ,
    0 /* forced delegation ISpatialReferenceInfo::put_Abbreviation */ ,
    0 /* forced delegation ISpatialReferenceInfo::get_Remarks */ ,
    0 /* forced delegation ISpatialReferenceInfo::put_Remarks */ ,
    0 /* forced delegation ISpatialReferenceInfo::get_WellKnownText */
};


static const PRPC_STUB_FUNCTION ISpatialReference_table[] =
{
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _ISpatialReferenceStubVtbl =
{
    &IID_ISpatialReference,
    &ISpatialReference_ServerInfo,
    16,
    &ISpatialReference_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IGeodeticSpatialReference, ver. 0.0,
   GUID={0x7c3c56d0,0xfe1e,0x11d0,{0xad,0x87,0x08,0x00,0x09,0xb6,0xf2,0x2b}} */

#pragma code_seg(".orpc")
static const unsigned short IGeodeticSpatialReference_FormatStringOffsetTable[] =
    {
    0,
    38,
    76,
    114,
    152,
    190,
    228,
    266,
    304,
    342,
    380,
    418,
    456,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO IGeodeticSpatialReference_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IGeodeticSpatialReference_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IGeodeticSpatialReference_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IGeodeticSpatialReference_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(16) _IGeodeticSpatialReferenceProxyVtbl = 
{
    0,
    &IID_IGeodeticSpatialReference,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* forced delegation ISpatialReferenceInfo::get_Name */ ,
    0 /* forced delegation ISpatialReferenceInfo::put_Name */ ,
    0 /* forced delegation ISpatialReferenceInfo::get_Authority */ ,
    0 /* forced delegation ISpatialReferenceInfo::put_Authority */ ,
    0 /* forced delegation ISpatialReferenceInfo::get_Code */ ,
    0 /* forced delegation ISpatialReferenceInfo::put_Code */ ,
    0 /* forced delegation ISpatialReferenceInfo::get_Alias */ ,
    0 /* forced delegation ISpatialReferenceInfo::put_Alias */ ,
    0 /* forced delegation ISpatialReferenceInfo::get_Abbreviation */ ,
    0 /* forced delegation ISpatialReferenceInfo::put_Abbreviation */ ,
    0 /* forced delegation ISpatialReferenceInfo::get_Remarks */ ,
    0 /* forced delegation ISpatialReferenceInfo::put_Remarks */ ,
    0 /* forced delegation ISpatialReferenceInfo::get_WellKnownText */
};


static const PRPC_STUB_FUNCTION IGeodeticSpatialReference_table[] =
{
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IGeodeticSpatialReferenceStubVtbl =
{
    &IID_IGeodeticSpatialReference,
    &IGeodeticSpatialReference_ServerInfo,
    16,
    &IGeodeticSpatialReference_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IGeographicCoordinateSystem, ver. 0.0,
   GUID={0xa3fd5390,0xfe1e,0x11d0,{0xad,0x87,0x08,0x00,0x09,0xb6,0xf2,0x2b}} */

#pragma code_seg(".orpc")
static const unsigned short IGeographicCoordinateSystem_FormatStringOffsetTable[] =
    {
    0,
    38,
    76,
    114,
    152,
    190,
    228,
    266,
    304,
    342,
    380,
    418,
    456,
    950,
    988,
    1026,
    1064,
    1102,
    1140,
    1178,
    1216
    };

static const MIDL_STUBLESS_PROXY_INFO IGeographicCoordinateSystem_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IGeographicCoordinateSystem_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IGeographicCoordinateSystem_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IGeographicCoordinateSystem_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(24) _IGeographicCoordinateSystemProxyVtbl = 
{
    &IGeographicCoordinateSystem_ProxyInfo,
    &IID_IGeographicCoordinateSystem,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_Name */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::put_Name */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_Authority */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::put_Authority */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_Code */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::put_Code */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_Alias */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::put_Alias */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_Abbreviation */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::put_Abbreviation */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_Remarks */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::put_Remarks */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_WellKnownText */ ,
    (void *) (INT_PTR) -1 /* IGeographicCoordinateSystem::get_Usage */ ,
    (void *) (INT_PTR) -1 /* IGeographicCoordinateSystem::put_Usage */ ,
    (void *) (INT_PTR) -1 /* IGeographicCoordinateSystem::get_HorizontalDatum */ ,
    (void *) (INT_PTR) -1 /* IGeographicCoordinateSystem::put_HorizontalDatum */ ,
    (void *) (INT_PTR) -1 /* IGeographicCoordinateSystem::get_AngularUnit */ ,
    (void *) (INT_PTR) -1 /* IGeographicCoordinateSystem::put_AngularUnit */ ,
    (void *) (INT_PTR) -1 /* IGeographicCoordinateSystem::get_PrimeMeridian */ ,
    (void *) (INT_PTR) -1 /* IGeographicCoordinateSystem::put_PrimeMeridian */
};

const CInterfaceStubVtbl _IGeographicCoordinateSystemStubVtbl =
{
    &IID_IGeographicCoordinateSystem,
    &IGeographicCoordinateSystem_ServerInfo,
    24,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IParameter, ver. 0.0,
   GUID={0x9a5e32d0,0xfe1f,0x11d0,{0xad,0x87,0x08,0x00,0x09,0xb6,0xf2,0x2b}} */

#pragma code_seg(".orpc")
static const unsigned short IParameter_FormatStringOffsetTable[] =
    {
    0,
    38,
    76,
    114,
    152,
    190,
    228,
    266,
    304,
    342,
    380,
    418,
    456,
    1254,
    1292,
    1330,
    1368
    };

static const MIDL_STUBLESS_PROXY_INFO IParameter_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IParameter_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IParameter_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IParameter_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(20) _IParameterProxyVtbl = 
{
    &IParameter_ProxyInfo,
    &IID_IParameter,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_Name */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::put_Name */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_Authority */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::put_Authority */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_Code */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::put_Code */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_Alias */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::put_Alias */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_Abbreviation */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::put_Abbreviation */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_Remarks */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::put_Remarks */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_WellKnownText */ ,
    (void *) (INT_PTR) -1 /* IParameter::put_ValueUnit */ ,
    (void *) (INT_PTR) -1 /* IParameter::get_ValueUnit */ ,
    (void *) (INT_PTR) -1 /* IParameter::put_Value */ ,
    (void *) (INT_PTR) -1 /* IParameter::get_Value */
};

const CInterfaceStubVtbl _IParameterStubVtbl =
{
    &IID_IParameter,
    &IParameter_ServerInfo,
    20,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IParameterInfo, ver. 0.0,
   GUID={0x7309b460,0xfe1f,0x11d0,{0xad,0x87,0x08,0x00,0x09,0xb6,0xf2,0x2b}} */

#pragma code_seg(".orpc")
static const unsigned short IParameterInfo_FormatStringOffsetTable[] =
    {
    1406,
    1444,
    1488,
    1532
    };

static const MIDL_STUBLESS_PROXY_INFO IParameterInfo_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IParameterInfo_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IParameterInfo_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IParameterInfo_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(7) _IParameterInfoProxyVtbl = 
{
    &IParameterInfo_ProxyInfo,
    &IID_IParameterInfo,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IParameterInfo::get_NumParameters */ ,
    (void *) (INT_PTR) -1 /* IParameterInfo::get_DefaultParameters */ ,
    (void *) (INT_PTR) -1 /* IParameterInfo::get_Parameters */ ,
    (void *) (INT_PTR) -1 /* IParameterInfo::put_Parameters */
};

const CInterfaceStubVtbl _IParameterInfoStubVtbl =
{
    &IID_IParameterInfo,
    &IParameterInfo_ServerInfo,
    7,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IGeographicTransform, ver. 0.0,
   GUID={0x5eb513c0,0xfe1f,0x11d0,{0xad,0x87,0x08,0x00,0x09,0xb6,0xf2,0x2b}} */

#pragma code_seg(".orpc")
static const unsigned short IGeographicTransform_FormatStringOffsetTable[] =
    {
    0,
    38,
    76,
    114,
    152,
    190,
    228,
    266,
    304,
    342,
    380,
    418,
    456,
    1576,
    1614,
    1652,
    1690,
    1728,
    1766,
    1810
    };

static const MIDL_STUBLESS_PROXY_INFO IGeographicTransform_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IGeographicTransform_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IGeographicTransform_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IGeographicTransform_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(23) _IGeographicTransformProxyVtbl = 
{
    &IGeographicTransform_ProxyInfo,
    &IID_IGeographicTransform,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_Name */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::put_Name */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_Authority */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::put_Authority */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_Code */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::put_Code */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_Alias */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::put_Alias */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_Abbreviation */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::put_Abbreviation */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_Remarks */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::put_Remarks */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_WellKnownText */ ,
    (void *) (INT_PTR) -1 /* IGeographicTransform::get_SourceGCS */ ,
    (void *) (INT_PTR) -1 /* IGeographicTransform::put_SourceGCS */ ,
    (void *) (INT_PTR) -1 /* IGeographicTransform::get_TargetGCS */ ,
    (void *) (INT_PTR) -1 /* IGeographicTransform::put_TargetGCS */ ,
    (void *) (INT_PTR) -1 /* IGeographicTransform::get_ParameterInfo */ ,
    (void *) (INT_PTR) -1 /* IGeographicTransform::Forward */ ,
    (void *) (INT_PTR) -1 /* IGeographicTransform::Inverse */
};

const CInterfaceStubVtbl _IGeographicTransformStubVtbl =
{
    &IID_IGeographicTransform,
    &IGeographicTransform_ServerInfo,
    23,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IProjection, ver. 0.0,
   GUID={0x5002f420,0xfe1f,0x11d0,{0xad,0x87,0x08,0x00,0x09,0xb6,0xf2,0x2b}} */

#pragma code_seg(".orpc")
static const unsigned short IProjection_FormatStringOffsetTable[] =
    {
    0,
    38,
    76,
    114,
    152,
    190,
    228,
    266,
    304,
    342,
    380,
    418,
    456,
    950,
    1854,
    1892,
    1936,
    1728,
    1980,
    2018,
    2056,
    2094,
    2132,
    2170
    };

static const MIDL_STUBLESS_PROXY_INFO IProjection_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IProjection_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IProjection_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IProjection_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(27) _IProjectionProxyVtbl = 
{
    &IProjection_ProxyInfo,
    &IID_IProjection,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_Name */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::put_Name */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_Authority */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::put_Authority */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_Code */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::put_Code */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_Alias */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::put_Alias */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_Abbreviation */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::put_Abbreviation */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_Remarks */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::put_Remarks */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_WellKnownText */ ,
    (void *) (INT_PTR) -1 /* IProjection::get_Usage */ ,
    (void *) (INT_PTR) -1 /* IProjection::get_Classification */ ,
    (void *) (INT_PTR) -1 /* IProjection::Forward */ ,
    (void *) (INT_PTR) -1 /* IProjection::Inverse */ ,
    (void *) (INT_PTR) -1 /* IProjection::get_ParameterInfo */ ,
    (void *) (INT_PTR) -1 /* IProjection::get_AngularUnit */ ,
    (void *) (INT_PTR) -1 /* IProjection::put_AngularUnit */ ,
    (void *) (INT_PTR) -1 /* IProjection::get_LinearUnit */ ,
    (void *) (INT_PTR) -1 /* IProjection::put_LinearUnit */ ,
    (void *) (INT_PTR) -1 /* IProjection::get_Ellipsoid */ ,
    (void *) (INT_PTR) -1 /* IProjection::put_Ellipsoid */
};

const CInterfaceStubVtbl _IProjectionStubVtbl =
{
    &IID_IProjection,
    &IProjection_ServerInfo,
    27,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IProjectedCoordinateSystem, ver. 0.0,
   GUID={0x3dc39ff0,0xfe1f,0x11d0,{0xad,0x87,0x08,0x00,0x09,0xb6,0xf2,0x2b}} */

#pragma code_seg(".orpc")
static const unsigned short IProjectedCoordinateSystem_FormatStringOffsetTable[] =
    {
    0,
    38,
    76,
    114,
    152,
    190,
    228,
    266,
    304,
    342,
    380,
    418,
    456,
    950,
    988,
    1652,
    1690,
    2208,
    2246,
    2284,
    2322,
    2360,
    2398,
    2442
    };

static const MIDL_STUBLESS_PROXY_INFO IProjectedCoordinateSystem_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IProjectedCoordinateSystem_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IProjectedCoordinateSystem_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IProjectedCoordinateSystem_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(27) _IProjectedCoordinateSystemProxyVtbl = 
{
    &IProjectedCoordinateSystem_ProxyInfo,
    &IID_IProjectedCoordinateSystem,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_Name */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::put_Name */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_Authority */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::put_Authority */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_Code */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::put_Code */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_Alias */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::put_Alias */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_Abbreviation */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::put_Abbreviation */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_Remarks */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::put_Remarks */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceInfo::get_WellKnownText */ ,
    (void *) (INT_PTR) -1 /* IProjectedCoordinateSystem::get_Usage */ ,
    (void *) (INT_PTR) -1 /* IProjectedCoordinateSystem::put_Usage */ ,
    (void *) (INT_PTR) -1 /* IProjectedCoordinateSystem::get_GeographicCoordinateSystem */ ,
    (void *) (INT_PTR) -1 /* IProjectedCoordinateSystem::put_GeographicCoordinateSystem */ ,
    (void *) (INT_PTR) -1 /* IProjectedCoordinateSystem::get_LinearUnit */ ,
    (void *) (INT_PTR) -1 /* IProjectedCoordinateSystem::put_LinearUnit */ ,
    (void *) (INT_PTR) -1 /* IProjectedCoordinateSystem::get_Projection */ ,
    (void *) (INT_PTR) -1 /* IProjectedCoordinateSystem::put_Projection */ ,
    (void *) (INT_PTR) -1 /* IProjectedCoordinateSystem::get_ParameterInfo */ ,
    (void *) (INT_PTR) -1 /* IProjectedCoordinateSystem::Forward */ ,
    (void *) (INT_PTR) -1 /* IProjectedCoordinateSystem::Inverse */
};

const CInterfaceStubVtbl _IProjectedCoordinateSystemStubVtbl =
{
    &IID_IProjectedCoordinateSystem,
    &IProjectedCoordinateSystem_ServerInfo,
    27,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: ISpatialReferenceFactory, ver. 0.0,
   GUID={0x620600B1,0xFEA1,0x11d0,{0xB0,0x4B,0x00,0x80,0xC7,0xF7,0x94,0x81}} */

#pragma code_seg(".orpc")
static const unsigned short ISpatialReferenceFactory_FormatStringOffsetTable[] =
    {
    2486
    };

static const MIDL_STUBLESS_PROXY_INFO ISpatialReferenceFactory_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &ISpatialReferenceFactory_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO ISpatialReferenceFactory_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &ISpatialReferenceFactory_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(4) _ISpatialReferenceFactoryProxyVtbl = 
{
    &ISpatialReferenceFactory_ProxyInfo,
    &IID_ISpatialReferenceFactory,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceFactory::CreateFromWKT */
};

const CInterfaceStubVtbl _ISpatialReferenceFactoryStubVtbl =
{
    &IID_ISpatialReferenceFactory,
    &ISpatialReferenceFactory_ServerInfo,
    4,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: ISpatialReferenceAuthorityFactory, ver. 0.0,
   GUID={0x30ae14f0,0xfe1f,0x11d0,{0xad,0x87,0x08,0x00,0x09,0xb6,0xf2,0x2b}} */

#pragma code_seg(".orpc")
static const unsigned short ISpatialReferenceAuthorityFactory_FormatStringOffsetTable[] =
    {
    0,
    2530,
    2574,
    2618,
    2662,
    2706,
    2750,
    2794,
    2838,
    2882
    };

static const MIDL_STUBLESS_PROXY_INFO ISpatialReferenceAuthorityFactory_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &ISpatialReferenceAuthorityFactory_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO ISpatialReferenceAuthorityFactory_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &ISpatialReferenceAuthorityFactory_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(13) _ISpatialReferenceAuthorityFactoryProxyVtbl = 
{
    &ISpatialReferenceAuthorityFactory_ProxyInfo,
    &IID_ISpatialReferenceAuthorityFactory,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceAuthorityFactory::get_Authority */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceAuthorityFactory::CreateProjectedCoordinateSystem */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceAuthorityFactory::CreateGeographicCoordinateSystem */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceAuthorityFactory::CreateProjection */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceAuthorityFactory::CreateGeographicTransform */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceAuthorityFactory::CreateHorizontalDatum */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceAuthorityFactory::CreateEllipsoid */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceAuthorityFactory::CreatePrimeMeridian */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceAuthorityFactory::CreateLinearUnit */ ,
    (void *) (INT_PTR) -1 /* ISpatialReferenceAuthorityFactory::CreateAngularUnit */
};

const CInterfaceStubVtbl _ISpatialReferenceAuthorityFactoryStubVtbl =
{
    &IID_ISpatialReferenceAuthorityFactory,
    &ISpatialReferenceAuthorityFactory_ServerInfo,
    13,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};

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
    1, /* -error bounds_check flag */
    0x50002, /* Ndr library version */
    0,
    0x600015b, /* MIDL Version 6.0.347 */
    0,
    UserMarshalRoutines,
    0,  /* notify & notify_flag routine table */
    0x1, /* MIDL flag */
    0, /* cs routines */
    0,   /* proxy/server info */
    0   /* Reserved5 */
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

const IID *  _SpatialReference_BaseIIDList[] = 
{
    &IID_ISpatialReferenceInfo,   /* forced */
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    &IID_ISpatialReferenceInfo,   /* forced */
    0,
    0,
    0,
    0,
    &IID_ISpatialReference,   /* forced */
    0,
    0,
    0,
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
    (const IID ** ) & _SpatialReference_BaseIIDList,
    & _SpatialReference_IID_Lookup, 
    17,
    2,
    0, /* table of [async_uuid] interfaces */
    0, /* Filler1 */
    0, /* Filler2 */
    0  /* Filler3 */
};


#endif /* defined(_M_IA64) || defined(_M_AMD64)*/

