
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the proxy stub code */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Thu Jan 17 12:57:25 2002
 */
/* Compiler settings for GeometryIdl.idl:
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


#include "GeometryIdl.h"

#define TYPE_FORMAT_STRING_SIZE   1115                              
#define PROC_FORMAT_STRING_SIZE   233                               
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   2            

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


extern const MIDL_SERVER_INFO IGeometry_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IGeometry_ProxyInfo;


/* [propget] */ HRESULT STDMETHODCALLTYPE IGeometry_get_Dimension_Proxy( 
    IGeometry * This,
    /* [retval][out] */ long *dimension)
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
        
        
        
        if(!dimension)
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
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            *dimension = *(( long * )_StubMsg.Buffer)++;
            
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
                         ( void * )dimension);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IGeometry_get_Dimension_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    long _M0	=	0;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    long *dimension;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( long * )dimension = 0;
    RpcTryFinally
        {
        dimension = &_M0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IGeometry*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_Dimension((IGeometry *) ((CStdStubBuffer *)This)->pvServerObject,dimension);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 36;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( long * )_StubMsg.Buffer)++ = *dimension;
        
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


/* [propget] */ HRESULT STDMETHODCALLTYPE IGeometry_get_SpatialReference_Proxy( 
    IGeometry * This,
    /* [retval][out] */ ISpatialReference **spatialRef)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(spatialRef)
        {
        MIDL_memset(
               spatialRef,
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
                      4);
        
        
        
        if(!spatialRef)
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
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[6] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&spatialRef,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[6],
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[6],
                         ( void * )spatialRef);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IGeometry_get_SpatialReference_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    ISpatialReference *_M1;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    ISpatialReference **spatialRef;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( ISpatialReference ** )spatialRef = 0;
    RpcTryFinally
        {
        spatialRef = &_M1;
        _M1 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IGeometry*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_SpatialReference((IGeometry *) ((CStdStubBuffer *)This)->pvServerObject,spatialRef);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char *)spatialRef,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[6] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char *)spatialRef,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[6] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char *)spatialRef,
                        &__MIDL_TypeFormatString.Format[6] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [propputref] */ HRESULT STDMETHODCALLTYPE IGeometry_putref_SpatialReference_Proxy( 
    IGeometry * This,
    /* [in] */ ISpatialReference *spatialRef)
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
                      5);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrInterfacePointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                           (unsigned char *)spatialRef,
                                           (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[10] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrInterfacePointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                         (unsigned char *)spatialRef,
                                         (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[10] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[12] );
            
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

void __RPC_STUB IGeometry_putref_SpatialReference_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    ISpatialReference *spatialRef;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    spatialRef = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[12] );
        
        NdrInterfacePointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char * *)&spatialRef,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[10],
                                       (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IGeometry*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> putref_SpatialReference((IGeometry *) ((CStdStubBuffer *)This)->pvServerObject,spatialRef);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrInterfacePointerFree( &_StubMsg,
                                 (unsigned char *)spatialRef,
                                 &__MIDL_TypeFormatString.Format[10] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [propget] */ HRESULT STDMETHODCALLTYPE IGeometry_get_IsEmpty_Proxy( 
    IGeometry * This,
    /* [retval][out] */ VARIANT_BOOL *isEmpty)
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
        
        
        
        if(!isEmpty)
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
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[18] );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 1) & ~ 0x1);
            *isEmpty = *(( VARIANT_BOOL * )_StubMsg.Buffer)++;
            
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[28],
                         ( void * )isEmpty);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IGeometry_get_IsEmpty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    VARIANT_BOOL _M2	=	0;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    VARIANT_BOOL *isEmpty;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( VARIANT_BOOL * )isEmpty = 0;
    RpcTryFinally
        {
        isEmpty = &_M2;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IGeometry*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_IsEmpty((IGeometry *) ((CStdStubBuffer *)This)->pvServerObject,isEmpty);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 34;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 1) & ~ 0x1);
        *(( VARIANT_BOOL * )_StubMsg.Buffer)++ = *isEmpty;
        
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


HRESULT STDMETHODCALLTYPE IGeometry_SetEmpty_Proxy( 
    IGeometry * This)
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
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[24] );
            
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

void __RPC_STUB IGeometry_SetEmpty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    RpcTryFinally
        {
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IGeometry*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> SetEmpty((IGeometry *) ((CStdStubBuffer *)This)->pvServerObject);
        
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


/* [propget] */ HRESULT STDMETHODCALLTYPE IGeometry_get_IsSimple_Proxy( 
    IGeometry * This,
    /* [retval][out] */ VARIANT_BOOL *isSimple)
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
        
        
        
        if(!isSimple)
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
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[18] );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 1) & ~ 0x1);
            *isSimple = *(( VARIANT_BOOL * )_StubMsg.Buffer)++;
            
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[28],
                         ( void * )isSimple);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IGeometry_get_IsSimple_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    VARIANT_BOOL _M3	=	0;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    VARIANT_BOOL *isSimple;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( VARIANT_BOOL * )isSimple = 0;
    RpcTryFinally
        {
        isSimple = &_M3;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IGeometry*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_IsSimple((IGeometry *) ((CStdStubBuffer *)This)->pvServerObject,isSimple);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 34;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 1) & ~ 0x1);
        *(( VARIANT_BOOL * )_StubMsg.Buffer)++ = *isSimple;
        
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


HRESULT STDMETHODCALLTYPE IGeometry_Envelope_Proxy( 
    IGeometry * This,
    /* [retval][out] */ IGeometry **envelope)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(envelope)
        {
        MIDL_memset(
               envelope,
               0,
               sizeof( IGeometry ** ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      9);
        
        
        
        if(!envelope)
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
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[26] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&envelope,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[32],
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[32],
                         ( void * )envelope);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IGeometry_Envelope_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    IGeometry *_M4;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    IGeometry **envelope;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( IGeometry ** )envelope = 0;
    RpcTryFinally
        {
        envelope = &_M4;
        _M4 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IGeometry*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> Envelope((IGeometry *) ((CStdStubBuffer *)This)->pvServerObject,envelope);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char *)envelope,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[32] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char *)envelope,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[32] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char *)envelope,
                        &__MIDL_TypeFormatString.Format[32] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


HRESULT STDMETHODCALLTYPE IGeometry_Clone_Proxy( 
    IGeometry * This,
    /* [retval][out] */ IGeometry **newShape)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(newShape)
        {
        MIDL_memset(
               newShape,
               0,
               sizeof( IGeometry ** ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      10);
        
        
        
        if(!newShape)
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
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[26] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&newShape,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[32],
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[32],
                         ( void * )newShape);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IGeometry_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    IGeometry *_M5;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    IGeometry **newShape;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( IGeometry ** )newShape = 0;
    RpcTryFinally
        {
        newShape = &_M5;
        _M5 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IGeometry*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> Clone((IGeometry *) ((CStdStubBuffer *)This)->pvServerObject,newShape);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char *)newShape,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[32] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char *)newShape,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[32] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char *)newShape,
                        &__MIDL_TypeFormatString.Format[32] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


HRESULT STDMETHODCALLTYPE IGeometry_Project_Proxy( 
    IGeometry * This,
    /* [in] */ ISpatialReference *newSystem,
    /* [retval][out] */ IGeometry **result)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(result)
        {
        MIDL_memset(
               result,
               0,
               sizeof( IGeometry ** ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      11);
        
        
        
        if(!result)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrInterfacePointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                           (unsigned char *)newSystem,
                                           (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[10] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrInterfacePointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                         (unsigned char *)newSystem,
                                         (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[10] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[32] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&result,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[32],
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[32],
                         ( void * )result);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IGeometry_Project_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    IGeometry *_M6;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    ISpatialReference *newSystem;
    IGeometry **result;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    newSystem = 0;
    ( IGeometry ** )result = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[32] );
        
        NdrInterfacePointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char * *)&newSystem,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[10],
                                       (unsigned char)0 );
        
        result = &_M6;
        _M6 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IGeometry*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> Project(
           (IGeometry *) ((CStdStubBuffer *)This)->pvServerObject,
           newSystem,
           result);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char *)result,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[32] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char *)result,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[32] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrInterfacePointerFree( &_StubMsg,
                                 (unsigned char *)newSystem,
                                 &__MIDL_TypeFormatString.Format[10] );
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char *)result,
                        &__MIDL_TypeFormatString.Format[32] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


HRESULT STDMETHODCALLTYPE IGeometry_Extent2D_Proxy( 
    IGeometry * This,
    /* [out] */ double *minX,
    /* [out] */ double *minY,
    /* [out] */ double *maxX,
    /* [out] */ double *maxY)
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
        
        
        
        if(!minX)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        if(!minY)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        if(!maxX)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        if(!maxY)
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
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[42] );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 7) & ~ 0x7);
            *minX = *(( double * )_StubMsg.Buffer)++;
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 7) & ~ 0x7);
            *minY = *(( double * )_StubMsg.Buffer)++;
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 7) & ~ 0x7);
            *maxX = *(( double * )_StubMsg.Buffer)++;
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 7) & ~ 0x7);
            *maxY = *(( double * )_StubMsg.Buffer)++;
            
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
                         ( void * )minX);
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[54],
                         ( void * )minY);
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[54],
                         ( void * )maxX);
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[54],
                         ( void * )maxY);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IGeometry_Extent2D_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    double _M10	=	0;
    double _M7	=	0;
    double _M8	=	0;
    double _M9	=	0;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    double *maxX;
    double *maxY;
    double *minX;
    double *minY;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( double * )minX = 0;
    ( double * )minY = 0;
    ( double * )maxX = 0;
    ( double * )maxY = 0;
    RpcTryFinally
        {
        minX = &_M7;
        minY = &_M8;
        maxX = &_M9;
        maxY = &_M10;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IGeometry*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> Extent2D(
            (IGeometry *) ((CStdStubBuffer *)This)->pvServerObject,
            minX,
            minY,
            maxX,
            maxY);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 152;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 7) & ~ 0x7);
        *(( double * )_StubMsg.Buffer)++ = *minX;
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 7) & ~ 0x7);
        *(( double * )_StubMsg.Buffer)++ = *minY;
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 7) & ~ 0x7);
        *(( double * )_StubMsg.Buffer)++ = *maxX;
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 7) & ~ 0x7);
        *(( double * )_StubMsg.Buffer)++ = *maxY;
        
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


extern const MIDL_SERVER_INFO IWks_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IWks_ProxyInfo;


HRESULT STDMETHODCALLTYPE IWks_ExportToWKB_Proxy( 
    IWks * This,
    /* [retval][out] */ VARIANT *wkb)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(wkb)
        {
        MIDL_memset(
               wkb,
               0,
               sizeof( VARIANT  ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      3);
        
        
        
        if(!wkb)
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
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[60] );
            
            NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char * *)&wkb,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1018],
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[58],
                         ( void * )wkb);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IWks_ExportToWKB_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    VARIANT _M11;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    VARIANT *wkb;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( VARIANT * )wkb = 0;
    RpcTryFinally
        {
        wkb = &_M11;
        MIDL_memset(
               wkb,
               0,
               sizeof( VARIANT  ));
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IWks*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> ExportToWKB((IWks *) ((CStdStubBuffer *)This)->pvServerObject,wkb);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char *)wkb,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1018] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                (unsigned char *)wkb,
                                (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1018] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char *)wkb,
                        &__MIDL_TypeFormatString.Format[58] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


HRESULT STDMETHODCALLTYPE IWks_ExportToWKT_Proxy( 
    IWks * This,
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
                      4);
        
        
        
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
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[66] );
            
            NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char * *)&wkt,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1032],
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[1028],
                         ( void * )wkt);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IWks_ExportToWKT_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    BSTR _M12;
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
        wkt = &_M12;
        MIDL_memset(
               wkt,
               0,
               sizeof( BSTR  ));
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IWks*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> ExportToWKT((IWks *) ((CStdStubBuffer *)This)->pvServerObject,wkt);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char *)wkt,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1032] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                (unsigned char *)wkt,
                                (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1032] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char *)wkt,
                        &__MIDL_TypeFormatString.Format[1028] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


HRESULT STDMETHODCALLTYPE IWks_ImportFromWKB_Proxy( 
    IWks * This,
    /* [in] */ VARIANT wkb,
    /* [in] */ ISpatialReference *spatialRef)
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
                      5);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char *)&wkb,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1046] );
            
            NdrInterfacePointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                           (unsigned char *)spatialRef,
                                           (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[10] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                    (unsigned char *)&wkb,
                                    (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1046] );
            
            NdrInterfacePointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                         (unsigned char *)spatialRef,
                                         (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[10] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[72] );
            
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

void __RPC_STUB IWks_ImportFromWKB_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    void *_p_wkb;
    ISpatialReference *spatialRef;
    VARIANT wkb;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    _p_wkb = &wkb;
    MIDL_memset(
               _p_wkb,
               0,
               sizeof( VARIANT  ));
    spatialRef = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[72] );
        
        NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&_p_wkb,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1046],
                                  (unsigned char)0 );
        
        NdrInterfacePointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char * *)&spatialRef,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[10],
                                       (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IWks*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> ImportFromWKB(
                 (IWks *) ((CStdStubBuffer *)This)->pvServerObject,
                 wkb,
                 spatialRef);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrUserMarshalFree( &_StubMsg,
                            (unsigned char *)&wkb,
                            &__MIDL_TypeFormatString.Format[1046] );
        
        NdrInterfacePointerFree( &_StubMsg,
                                 (unsigned char *)spatialRef,
                                 &__MIDL_TypeFormatString.Format[10] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


HRESULT STDMETHODCALLTYPE IWks_ImportFromWKT_Proxy( 
    IWks * This,
    /* [in] */ BSTR wkt,
    /* [in] */ ISpatialReference *spatialRef)
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
                                      (unsigned char *)&wkt,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1060] );
            
            NdrInterfacePointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                           (unsigned char *)spatialRef,
                                           (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[10] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                    (unsigned char *)&wkt,
                                    (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1060] );
            
            NdrInterfacePointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                         (unsigned char *)spatialRef,
                                         (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[10] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[82] );
            
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

void __RPC_STUB IWks_ImportFromWKT_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    void *_p_wkt;
    ISpatialReference *spatialRef;
    BSTR wkt;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    _p_wkt = &wkt;
    MIDL_memset(
               _p_wkt,
               0,
               sizeof( BSTR  ));
    spatialRef = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[82] );
        
        NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&_p_wkt,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1060],
                                  (unsigned char)0 );
        
        NdrInterfacePointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char * *)&spatialRef,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[10],
                                       (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IWks*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> ImportFromWKT(
                 (IWks *) ((CStdStubBuffer *)This)->pvServerObject,
                 wkt,
                 spatialRef);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrUserMarshalFree( &_StubMsg,
                            (unsigned char *)&wkt,
                            &__MIDL_TypeFormatString.Format[1060] );
        
        NdrInterfacePointerFree( &_StubMsg,
                                 (unsigned char *)spatialRef,
                                 &__MIDL_TypeFormatString.Format[10] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IGeometryFactory_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IGeometryFactory_ProxyInfo;


HRESULT STDMETHODCALLTYPE IGeometryFactory_CreateFromWKB_Proxy( 
    IGeometryFactory * This,
    /* [in] */ VARIANT wkb,
    /* [in] */ ISpatialReference *spatialRef,
    /* [retval][out] */ IGeometry **geometry)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(geometry)
        {
        MIDL_memset(
               geometry,
               0,
               sizeof( IGeometry ** ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      3);
        
        
        
        if(!geometry)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char *)&wkb,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1046] );
            
            NdrInterfacePointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                           (unsigned char *)spatialRef,
                                           (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[10] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                    (unsigned char *)&wkb,
                                    (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1046] );
            
            NdrInterfacePointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                         (unsigned char *)spatialRef,
                                         (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[10] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[92] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&geometry,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[32],
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[32],
                         ( void * )geometry);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IGeometryFactory_CreateFromWKB_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    IGeometry *_M13;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    void *_p_wkb;
    IGeometry **geometry;
    ISpatialReference *spatialRef;
    VARIANT wkb;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    _p_wkb = &wkb;
    MIDL_memset(
               _p_wkb,
               0,
               sizeof( VARIANT  ));
    spatialRef = 0;
    ( IGeometry ** )geometry = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[92] );
        
        NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&_p_wkb,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1046],
                                  (unsigned char)0 );
        
        NdrInterfacePointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char * *)&spatialRef,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[10],
                                       (unsigned char)0 );
        
        geometry = &_M13;
        _M13 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IGeometryFactory*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> CreateFromWKB(
                 (IGeometryFactory *) ((CStdStubBuffer *)This)->pvServerObject,
                 wkb,
                 spatialRef,
                 geometry);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char *)geometry,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[32] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char *)geometry,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[32] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrUserMarshalFree( &_StubMsg,
                            (unsigned char *)&wkb,
                            &__MIDL_TypeFormatString.Format[1046] );
        
        NdrInterfacePointerFree( &_StubMsg,
                                 (unsigned char *)spatialRef,
                                 &__MIDL_TypeFormatString.Format[10] );
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char *)geometry,
                        &__MIDL_TypeFormatString.Format[32] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


HRESULT STDMETHODCALLTYPE IGeometryFactory_CreateFromWKT_Proxy( 
    IGeometryFactory * This,
    /* [in] */ BSTR wkt,
    /* [in] */ ISpatialReference *spatialRef,
    /* [retval][out] */ IGeometry **geometry)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(geometry)
        {
        MIDL_memset(
               geometry,
               0,
               sizeof( IGeometry ** ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      4);
        
        
        
        if(!geometry)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char *)&wkt,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1060] );
            
            NdrInterfacePointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                           (unsigned char *)spatialRef,
                                           (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[10] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                    (unsigned char *)&wkt,
                                    (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1060] );
            
            NdrInterfacePointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                         (unsigned char *)spatialRef,
                                         (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[10] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[106] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&geometry,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[32],
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[32],
                         ( void * )geometry);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IGeometryFactory_CreateFromWKT_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    IGeometry *_M14;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    void *_p_wkt;
    IGeometry **geometry;
    ISpatialReference *spatialRef;
    BSTR wkt;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    _p_wkt = &wkt;
    MIDL_memset(
               _p_wkt,
               0,
               sizeof( BSTR  ));
    spatialRef = 0;
    ( IGeometry ** )geometry = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[106] );
        
        NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&_p_wkt,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1060],
                                  (unsigned char)0 );
        
        NdrInterfacePointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char * *)&spatialRef,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[10],
                                       (unsigned char)0 );
        
        geometry = &_M14;
        _M14 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IGeometryFactory*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> CreateFromWKT(
                 (IGeometryFactory *) ((CStdStubBuffer *)This)->pvServerObject,
                 wkt,
                 spatialRef,
                 geometry);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char *)geometry,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[32] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char *)geometry,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[32] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrUserMarshalFree( &_StubMsg,
                            (unsigned char *)&wkt,
                            &__MIDL_TypeFormatString.Format[1060] );
        
        NdrInterfacePointerFree( &_StubMsg,
                                 (unsigned char *)spatialRef,
                                 &__MIDL_TypeFormatString.Format[10] );
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char *)geometry,
                        &__MIDL_TypeFormatString.Format[32] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IPoint_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IPoint_ProxyInfo;


HRESULT STDMETHODCALLTYPE IPoint_Coords_Proxy( 
    IPoint * This,
    /* [out] */ double *x,
    /* [out] */ double *y)
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
                      13);
        
        
        
        if(!x)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        if(!y)
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
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 7) & ~ 0x7);
            *x = *(( double * )_StubMsg.Buffer)++;
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 7) & ~ 0x7);
            *y = *(( double * )_StubMsg.Buffer)++;
            
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
                         ( void * )x);
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[54],
                         ( void * )y);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IPoint_Coords_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    double _M15	=	0;
    double _M16	=	0;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    double *x;
    double *y;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( double * )x = 0;
    ( double * )y = 0;
    RpcTryFinally
        {
        x = &_M15;
        y = &_M16;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IPoint*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> Coords(
          (IPoint *) ((CStdStubBuffer *)This)->pvServerObject,
          x,
          y);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 80;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 7) & ~ 0x7);
        *(( double * )_StubMsg.Buffer)++ = *x;
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 7) & ~ 0x7);
        *(( double * )_StubMsg.Buffer)++ = *y;
        
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


/* [propget] */ HRESULT STDMETHODCALLTYPE IPoint_get_X_Proxy( 
    IPoint * This,
    /* [retval][out] */ double *x)
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
        
        
        
        if(!x)
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
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[130] );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 7) & ~ 0x7);
            *x = *(( double * )_StubMsg.Buffer)++;
            
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
                         ( void * )x);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IPoint_get_X_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    double _M17	=	0;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    double *x;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( double * )x = 0;
    RpcTryFinally
        {
        x = &_M17;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IPoint*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_X((IPoint *) ((CStdStubBuffer *)This)->pvServerObject,x);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 44;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 7) & ~ 0x7);
        *(( double * )_StubMsg.Buffer)++ = *x;
        
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


/* [propget] */ HRESULT STDMETHODCALLTYPE IPoint_get_Y_Proxy( 
    IPoint * This,
    /* [retval][out] */ double *y)
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
                      15);
        
        
        
        if(!y)
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
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[130] );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 7) & ~ 0x7);
            *y = *(( double * )_StubMsg.Buffer)++;
            
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
                         ( void * )y);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IPoint_get_Y_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    double _M18	=	0;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    double *y;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( double * )y = 0;
    RpcTryFinally
        {
        y = &_M18;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IPoint*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_Y((IPoint *) ((CStdStubBuffer *)This)->pvServerObject,y);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 44;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 7) & ~ 0x7);
        *(( double * )_StubMsg.Buffer)++ = *y;
        
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


extern const MIDL_SERVER_INFO IPointZ_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IPointZ_ProxyInfo;


/* [propget] */ HRESULT STDMETHODCALLTYPE IPointZ_get_Z_Proxy( 
    IPointZ * This,
    /* [retval][out] */ double *z)
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
        
        
        
        if(!z)
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
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[130] );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 7) & ~ 0x7);
            *z = *(( double * )_StubMsg.Buffer)++;
            
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
                         ( void * )z);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IPointZ_get_Z_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    double _M19	=	0;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    double *z;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( double * )z = 0;
    RpcTryFinally
        {
        z = &_M19;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IPointZ*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_Z((IPointZ *) ((CStdStubBuffer *)This)->pvServerObject,z);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 44;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 7) & ~ 0x7);
        *(( double * )_StubMsg.Buffer)++ = *z;
        
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


extern const MIDL_SERVER_INFO ICurve_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO ICurve_ProxyInfo;


/* [propget] */ HRESULT STDMETHODCALLTYPE ICurve_get_Length_Proxy( 
    ICurve * This,
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
                      13);
        
        
        
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
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[130] );
            
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[54],
                         ( void * )value);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB ICurve_get_Length_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    double _M20	=	0;
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
        value = &_M20;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ICurve*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_Length((ICurve *) ((CStdStubBuffer *)This)->pvServerObject,value);
        
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


HRESULT STDMETHODCALLTYPE ICurve_StartPoint_Proxy( 
    ICurve * This,
    /* [retval][out] */ IPoint **sp)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(sp)
        {
        MIDL_memset(
               sp,
               0,
               sizeof( IPoint ** ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      14);
        
        
        
        if(!sp)
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
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[136] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&sp,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070],
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[1070],
                         ( void * )sp);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB ICurve_StartPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    IPoint *_M21;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    IPoint **sp;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( IPoint ** )sp = 0;
    RpcTryFinally
        {
        sp = &_M21;
        _M21 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ICurve*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> StartPoint((ICurve *) ((CStdStubBuffer *)This)->pvServerObject,sp);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char *)sp,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char *)sp,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char *)sp,
                        &__MIDL_TypeFormatString.Format[1070] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


HRESULT STDMETHODCALLTYPE ICurve_EndPoint_Proxy( 
    ICurve * This,
    /* [retval][out] */ IPoint **ep)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(ep)
        {
        MIDL_memset(
               ep,
               0,
               sizeof( IPoint ** ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      15);
        
        
        
        if(!ep)
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
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[136] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&ep,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070],
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[1070],
                         ( void * )ep);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB ICurve_EndPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    IPoint *_M22;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    IPoint **ep;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( IPoint ** )ep = 0;
    RpcTryFinally
        {
        ep = &_M22;
        _M22 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ICurve*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> EndPoint((ICurve *) ((CStdStubBuffer *)This)->pvServerObject,ep);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char *)ep,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char *)ep,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char *)ep,
                        &__MIDL_TypeFormatString.Format[1070] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [propget] */ HRESULT STDMETHODCALLTYPE ICurve_get_IsClosed_Proxy( 
    ICurve * This,
    /* [retval][out] */ VARIANT_BOOL *isClosed)
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
        
        
        
        if(!isClosed)
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
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[18] );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 1) & ~ 0x1);
            *isClosed = *(( VARIANT_BOOL * )_StubMsg.Buffer)++;
            
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[28],
                         ( void * )isClosed);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB ICurve_get_IsClosed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    VARIANT_BOOL _M23	=	0;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    VARIANT_BOOL *isClosed;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( VARIANT_BOOL * )isClosed = 0;
    RpcTryFinally
        {
        isClosed = &_M23;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ICurve*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_IsClosed((ICurve *) ((CStdStubBuffer *)This)->pvServerObject,isClosed);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 34;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 1) & ~ 0x1);
        *(( VARIANT_BOOL * )_StubMsg.Buffer)++ = *isClosed;
        
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


HRESULT STDMETHODCALLTYPE ICurve_Value_Proxy( 
    ICurve * This,
    /* [in] */ double t,
    /* [retval][out] */ IPoint **p)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(p)
        {
        MIDL_memset(
               p,
               0,
               sizeof( IPoint ** ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      17);
        
        
        
        if(!p)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 16;
            NdrProxyGetBuffer(This, &_StubMsg);
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 7) & ~ 0x7);
            *(( double * )_StubMsg.Buffer)++ = t;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[142] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&p,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070],
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[1070],
                         ( void * )p);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB ICurve_Value_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    IPoint *_M24;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    IPoint **p;
    double t;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    t = 0;
    ( IPoint ** )p = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[142] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 7) & ~ 0x7);
        
        if(_StubMsg.Buffer + 8 > _StubMsg.BufferEnd)
            {
            RpcRaiseException(RPC_X_BAD_STUB_DATA);
            }
        t = *(( double * )_StubMsg.Buffer)++;
        
        p = &_M24;
        _M24 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ICurve*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> Value(
         (ICurve *) ((CStdStubBuffer *)This)->pvServerObject,
         t,
         p);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char *)p,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char *)p,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char *)p,
                        &__MIDL_TypeFormatString.Format[1070] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO ILineString_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO ILineString_ProxyInfo;


/* [propget] */ HRESULT STDMETHODCALLTYPE ILineString_get_NumPoints_Proxy( 
    ILineString * This,
    /* [retval][out] */ long *numPoints)
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
        
        
        
        if(!numPoints)
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
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            *numPoints = *(( long * )_StubMsg.Buffer)++;
            
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
                         ( void * )numPoints);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB ILineString_get_NumPoints_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    long _M25	=	0;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    long *numPoints;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( long * )numPoints = 0;
    RpcTryFinally
        {
        numPoints = &_M25;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ILineString*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_NumPoints((ILineString *) ((CStdStubBuffer *)This)->pvServerObject,numPoints);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 36;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( long * )_StubMsg.Buffer)++ = *numPoints;
        
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


HRESULT STDMETHODCALLTYPE ILineString_Point_Proxy( 
    ILineString * This,
    /* [in] */ long index,
    /* [retval][out] */ IPoint **point)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(point)
        {
        MIDL_memset(
               point,
               0,
               sizeof( IPoint ** ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      19);
        
        
        
        if(!point)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 8;
            NdrProxyGetBuffer(This, &_StubMsg);
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            *(( long * )_StubMsg.Buffer)++ = index;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[150] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&point,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070],
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[1070],
                         ( void * )point);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB ILineString_Point_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    IPoint *_M26;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    long index;
    IPoint **point;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    index = 0;
    ( IPoint ** )point = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[150] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        
        if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
            {
            RpcRaiseException(RPC_X_BAD_STUB_DATA);
            }
        index = *(( long * )_StubMsg.Buffer)++;
        
        point = &_M26;
        _M26 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ILineString*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> Point(
         (ILineString *) ((CStdStubBuffer *)This)->pvServerObject,
         index,
         point);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char *)point,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char *)point,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char *)point,
                        &__MIDL_TypeFormatString.Format[1070] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO ILinearRing_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO ILinearRing_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO ISurface_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO ISurface_ProxyInfo;


/* [propget] */ HRESULT STDMETHODCALLTYPE ISurface_get_Area_Proxy( 
    ISurface * This,
    /* [retval][out] */ double *area)
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
                      13);
        
        
        
        if(!area)
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
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[130] );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 7) & ~ 0x7);
            *area = *(( double * )_StubMsg.Buffer)++;
            
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
                         ( void * )area);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB ISurface_get_Area_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    double _M27	=	0;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    double *area;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( double * )area = 0;
    RpcTryFinally
        {
        area = &_M27;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISurface*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_Area((ISurface *) ((CStdStubBuffer *)This)->pvServerObject,area);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 44;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 7) & ~ 0x7);
        *(( double * )_StubMsg.Buffer)++ = *area;
        
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


HRESULT STDMETHODCALLTYPE ISurface_Centroid_Proxy( 
    ISurface * This,
    /* [retval][out] */ IPoint **result)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(result)
        {
        MIDL_memset(
               result,
               0,
               sizeof( IPoint ** ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      14);
        
        
        
        if(!result)
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
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[136] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&result,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070],
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[1070],
                         ( void * )result);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB ISurface_Centroid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    IPoint *_M28;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    IPoint **result;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( IPoint ** )result = 0;
    RpcTryFinally
        {
        result = &_M28;
        _M28 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISurface*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> Centroid((ISurface *) ((CStdStubBuffer *)This)->pvServerObject,result);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char *)result,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char *)result,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char *)result,
                        &__MIDL_TypeFormatString.Format[1070] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


HRESULT STDMETHODCALLTYPE ISurface_PointOnSurface_Proxy( 
    ISurface * This,
    /* [retval][out] */ IPoint **result)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(result)
        {
        MIDL_memset(
               result,
               0,
               sizeof( IPoint ** ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      15);
        
        
        
        if(!result)
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
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[136] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&result,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070],
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[1070],
                         ( void * )result);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB ISurface_PointOnSurface_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    IPoint *_M29;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    IPoint **result;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( IPoint ** )result = 0;
    RpcTryFinally
        {
        result = &_M29;
        _M29 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISurface*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> PointOnSurface((ISurface *) ((CStdStubBuffer *)This)->pvServerObject,result);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char *)result,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char *)result,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char *)result,
                        &__MIDL_TypeFormatString.Format[1070] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IGeometryCollection_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IGeometryCollection_ProxyInfo;


/* [propget] */ HRESULT STDMETHODCALLTYPE IGeometryCollection_get_NumGeometries_Proxy( 
    IGeometryCollection * This,
    /* [retval][out] */ long *numberOf)
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
                      13);
        
        
        
        if(!numberOf)
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
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            *numberOf = *(( long * )_StubMsg.Buffer)++;
            
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
                         ( void * )numberOf);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IGeometryCollection_get_NumGeometries_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    long _M30	=	0;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    long *numberOf;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( long * )numberOf = 0;
    RpcTryFinally
        {
        numberOf = &_M30;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IGeometryCollection*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_NumGeometries((IGeometryCollection *) ((CStdStubBuffer *)This)->pvServerObject,numberOf);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 36;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( long * )_StubMsg.Buffer)++ = *numberOf;
        
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


HRESULT STDMETHODCALLTYPE IGeometryCollection_Geometry_Proxy( 
    IGeometryCollection * This,
    /* [in] */ long index,
    /* [retval][out] */ IGeometry **geometry)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(geometry)
        {
        MIDL_memset(
               geometry,
               0,
               sizeof( IGeometry ** ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      14);
        
        
        
        if(!geometry)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 8;
            NdrProxyGetBuffer(This, &_StubMsg);
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            *(( long * )_StubMsg.Buffer)++ = index;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[158] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&geometry,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[32],
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[32],
                         ( void * )geometry);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IGeometryCollection_Geometry_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    IGeometry *_M31;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    IGeometry **geometry;
    long index;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    index = 0;
    ( IGeometry ** )geometry = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[158] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        
        if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
            {
            RpcRaiseException(RPC_X_BAD_STUB_DATA);
            }
        index = *(( long * )_StubMsg.Buffer)++;
        
        geometry = &_M31;
        _M31 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IGeometryCollection*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> Geometry(
            (IGeometryCollection *) ((CStdStubBuffer *)This)->pvServerObject,
            index,
            geometry);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char *)geometry,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[32] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char *)geometry,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[32] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char *)geometry,
                        &__MIDL_TypeFormatString.Format[32] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IPolygon_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IPolygon_ProxyInfo;


HRESULT STDMETHODCALLTYPE IPolygon_ExteriorRing_Proxy( 
    IPolygon * This,
    /* [retval][out] */ ILinearRing **exteriorRing)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(exteriorRing)
        {
        MIDL_memset(
               exteriorRing,
               0,
               sizeof( ILinearRing ** ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      16);
        
        
        
        if(!exteriorRing)
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
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[166] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&exteriorRing,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1092],
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[1092],
                         ( void * )exteriorRing);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IPolygon_ExteriorRing_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    ILinearRing *_M32;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    ILinearRing **exteriorRing;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( ILinearRing ** )exteriorRing = 0;
    RpcTryFinally
        {
        exteriorRing = &_M32;
        _M32 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IPolygon*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> ExteriorRing((IPolygon *) ((CStdStubBuffer *)This)->pvServerObject,exteriorRing);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char *)exteriorRing,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1092] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char *)exteriorRing,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1092] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char *)exteriorRing,
                        &__MIDL_TypeFormatString.Format[1092] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [propget] */ HRESULT STDMETHODCALLTYPE IPolygon_get_NumInteriorRings_Proxy( 
    IPolygon * This,
    /* [retval][out] */ long *count)
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
        
        
        
        if(!count)
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
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            *count = *(( long * )_StubMsg.Buffer)++;
            
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
                         ( void * )count);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IPolygon_get_NumInteriorRings_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    long _M33	=	0;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    long *count;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( long * )count = 0;
    RpcTryFinally
        {
        count = &_M33;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IPolygon*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_NumInteriorRings((IPolygon *) ((CStdStubBuffer *)This)->pvServerObject,count);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 36;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( long * )_StubMsg.Buffer)++ = *count;
        
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


HRESULT STDMETHODCALLTYPE IPolygon_InteriorRing_Proxy( 
    IPolygon * This,
    /* [in] */ long index,
    /* [retval][out] */ ILinearRing **interiorRing)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(interiorRing)
        {
        MIDL_memset(
               interiorRing,
               0,
               sizeof( ILinearRing ** ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      18);
        
        
        
        if(!interiorRing)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 8;
            NdrProxyGetBuffer(This, &_StubMsg);
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            *(( long * )_StubMsg.Buffer)++ = index;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[172] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&interiorRing,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1092],
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[1092],
                         ( void * )interiorRing);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IPolygon_InteriorRing_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    ILinearRing *_M34;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    long index;
    ILinearRing **interiorRing;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    index = 0;
    ( ILinearRing ** )interiorRing = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[172] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        
        if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
            {
            RpcRaiseException(RPC_X_BAD_STUB_DATA);
            }
        index = *(( long * )_StubMsg.Buffer)++;
        
        interiorRing = &_M34;
        _M34 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IPolygon*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> InteriorRing(
                (IPolygon *) ((CStdStubBuffer *)This)->pvServerObject,
                index,
                interiorRing);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char *)interiorRing,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1092] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char *)interiorRing,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1092] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char *)interiorRing,
                        &__MIDL_TypeFormatString.Format[1092] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IMultiCurve_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IMultiCurve_ProxyInfo;


/* [propget] */ HRESULT STDMETHODCALLTYPE IMultiCurve_get_Length_Proxy( 
    IMultiCurve * This,
    /* [retval][out] */ double *length)
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
                      15);
        
        
        
        if(!length)
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
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[130] );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 7) & ~ 0x7);
            *length = *(( double * )_StubMsg.Buffer)++;
            
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
                         ( void * )length);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IMultiCurve_get_Length_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    double _M35	=	0;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    double *length;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( double * )length = 0;
    RpcTryFinally
        {
        length = &_M35;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IMultiCurve*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_Length((IMultiCurve *) ((CStdStubBuffer *)This)->pvServerObject,length);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 44;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 7) & ~ 0x7);
        *(( double * )_StubMsg.Buffer)++ = *length;
        
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


/* [propget] */ HRESULT STDMETHODCALLTYPE IMultiCurve_get_IsClosed_Proxy( 
    IMultiCurve * This,
    /* [retval][out] */ VARIANT_BOOL *isClosed)
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
        
        
        
        if(!isClosed)
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
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[18] );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 1) & ~ 0x1);
            *isClosed = *(( VARIANT_BOOL * )_StubMsg.Buffer)++;
            
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[28],
                         ( void * )isClosed);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IMultiCurve_get_IsClosed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    VARIANT_BOOL _M36	=	0;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    VARIANT_BOOL *isClosed;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( VARIANT_BOOL * )isClosed = 0;
    RpcTryFinally
        {
        isClosed = &_M36;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IMultiCurve*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_IsClosed((IMultiCurve *) ((CStdStubBuffer *)This)->pvServerObject,isClosed);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 34;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 1) & ~ 0x1);
        *(( VARIANT_BOOL * )_StubMsg.Buffer)++ = *isClosed;
        
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


extern const MIDL_SERVER_INFO IMultiSurface_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IMultiSurface_ProxyInfo;


/* [propget] */ HRESULT STDMETHODCALLTYPE IMultiSurface_get_Area_Proxy( 
    IMultiSurface * This,
    /* [retval][out] */ double *area)
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
                      15);
        
        
        
        if(!area)
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
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[130] );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 7) & ~ 0x7);
            *area = *(( double * )_StubMsg.Buffer)++;
            
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
                         ( void * )area);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IMultiSurface_get_Area_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    double _M37	=	0;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    double *area;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( double * )area = 0;
    RpcTryFinally
        {
        area = &_M37;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IMultiSurface*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_Area((IMultiSurface *) ((CStdStubBuffer *)This)->pvServerObject,area);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 44;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 7) & ~ 0x7);
        *(( double * )_StubMsg.Buffer)++ = *area;
        
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


HRESULT STDMETHODCALLTYPE IMultiSurface_Centroid_Proxy( 
    IMultiSurface * This,
    /* [retval][out] */ IPoint **result)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(result)
        {
        MIDL_memset(
               result,
               0,
               sizeof( IPoint ** ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      16);
        
        
        
        if(!result)
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
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[136] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&result,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070],
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[1070],
                         ( void * )result);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IMultiSurface_Centroid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    IPoint *_M38;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    IPoint **result;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( IPoint ** )result = 0;
    RpcTryFinally
        {
        result = &_M38;
        _M38 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IMultiSurface*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> Centroid((IMultiSurface *) ((CStdStubBuffer *)This)->pvServerObject,result);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char *)result,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char *)result,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char *)result,
                        &__MIDL_TypeFormatString.Format[1070] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


HRESULT STDMETHODCALLTYPE IMultiSurface_PointOnSurface_Proxy( 
    IMultiSurface * This,
    /* [retval][out] */ IPoint **result)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(result)
        {
        MIDL_memset(
               result,
               0,
               sizeof( IPoint ** ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      17);
        
        
        
        if(!result)
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
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[136] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&result,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070],
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[1070],
                         ( void * )result);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IMultiSurface_PointOnSurface_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    IPoint *_M39;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    IPoint **result;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( IPoint ** )result = 0;
    RpcTryFinally
        {
        result = &_M39;
        _M39 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IMultiSurface*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> PointOnSurface((IMultiSurface *) ((CStdStubBuffer *)This)->pvServerObject,result);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char *)result,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char *)result,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1070] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char *)result,
                        &__MIDL_TypeFormatString.Format[1070] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO ISpatialRelation_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO ISpatialRelation_ProxyInfo;


HRESULT STDMETHODCALLTYPE ISpatialRelation_Equals_Proxy( 
    ISpatialRelation * This,
    /* [in] */ IGeometry *other,
    /* [retval][out] */ VARIANT_BOOL *equals)
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
        
        
        
        if(!equals)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrInterfacePointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                           (unsigned char *)other,
                                           (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[36] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrInterfacePointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                         (unsigned char *)other,
                                         (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[36] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[180] );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 1) & ~ 0x1);
            *equals = *(( VARIANT_BOOL * )_StubMsg.Buffer)++;
            
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[28],
                         ( void * )equals);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB ISpatialRelation_Equals_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    VARIANT_BOOL _M40	=	0;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    VARIANT_BOOL *equals;
    IGeometry *other;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    other = 0;
    ( VARIANT_BOOL * )equals = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[180] );
        
        NdrInterfacePointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char * *)&other,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[36],
                                       (unsigned char)0 );
        
        equals = &_M40;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISpatialRelation*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> Equals(
          (ISpatialRelation *) ((CStdStubBuffer *)This)->pvServerObject,
          other,
          equals);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 34;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 1) & ~ 0x1);
        *(( VARIANT_BOOL * )_StubMsg.Buffer)++ = *equals;
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrInterfacePointerFree( &_StubMsg,
                                 (unsigned char *)other,
                                 &__MIDL_TypeFormatString.Format[36] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


HRESULT STDMETHODCALLTYPE ISpatialRelation_Touches_Proxy( 
    ISpatialRelation * This,
    /* [in] */ IGeometry *other,
    /* [retval][out] */ VARIANT_BOOL *touches)
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
        
        
        
        if(!touches)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrInterfacePointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                           (unsigned char *)other,
                                           (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[36] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrInterfacePointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                         (unsigned char *)other,
                                         (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[36] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[180] );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 1) & ~ 0x1);
            *touches = *(( VARIANT_BOOL * )_StubMsg.Buffer)++;
            
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[28],
                         ( void * )touches);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB ISpatialRelation_Touches_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    VARIANT_BOOL _M41	=	0;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    IGeometry *other;
    VARIANT_BOOL *touches;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    other = 0;
    ( VARIANT_BOOL * )touches = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[180] );
        
        NdrInterfacePointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char * *)&other,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[36],
                                       (unsigned char)0 );
        
        touches = &_M41;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISpatialRelation*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> Touches(
           (ISpatialRelation *) ((CStdStubBuffer *)This)->pvServerObject,
           other,
           touches);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 34;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 1) & ~ 0x1);
        *(( VARIANT_BOOL * )_StubMsg.Buffer)++ = *touches;
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrInterfacePointerFree( &_StubMsg,
                                 (unsigned char *)other,
                                 &__MIDL_TypeFormatString.Format[36] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


HRESULT STDMETHODCALLTYPE ISpatialRelation_Contains_Proxy( 
    ISpatialRelation * This,
    /* [in] */ IGeometry *other,
    /* [retval][out] */ VARIANT_BOOL *contains)
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
                      5);
        
        
        
        if(!contains)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrInterfacePointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                           (unsigned char *)other,
                                           (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[36] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrInterfacePointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                         (unsigned char *)other,
                                         (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[36] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[180] );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 1) & ~ 0x1);
            *contains = *(( VARIANT_BOOL * )_StubMsg.Buffer)++;
            
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[28],
                         ( void * )contains);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB ISpatialRelation_Contains_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    VARIANT_BOOL _M42	=	0;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    VARIANT_BOOL *contains;
    IGeometry *other;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    other = 0;
    ( VARIANT_BOOL * )contains = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[180] );
        
        NdrInterfacePointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char * *)&other,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[36],
                                       (unsigned char)0 );
        
        contains = &_M42;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISpatialRelation*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> Contains(
            (ISpatialRelation *) ((CStdStubBuffer *)This)->pvServerObject,
            other,
            contains);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 34;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 1) & ~ 0x1);
        *(( VARIANT_BOOL * )_StubMsg.Buffer)++ = *contains;
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrInterfacePointerFree( &_StubMsg,
                                 (unsigned char *)other,
                                 &__MIDL_TypeFormatString.Format[36] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


HRESULT STDMETHODCALLTYPE ISpatialRelation_Within_Proxy( 
    ISpatialRelation * This,
    /* [in] */ IGeometry *other,
    /* [retval][out] */ VARIANT_BOOL *within)
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
        
        
        
        if(!within)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrInterfacePointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                           (unsigned char *)other,
                                           (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[36] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrInterfacePointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                         (unsigned char *)other,
                                         (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[36] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[180] );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 1) & ~ 0x1);
            *within = *(( VARIANT_BOOL * )_StubMsg.Buffer)++;
            
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[28],
                         ( void * )within);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB ISpatialRelation_Within_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    VARIANT_BOOL _M43	=	0;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    IGeometry *other;
    VARIANT_BOOL *within;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    other = 0;
    ( VARIANT_BOOL * )within = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[180] );
        
        NdrInterfacePointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char * *)&other,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[36],
                                       (unsigned char)0 );
        
        within = &_M43;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISpatialRelation*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> Within(
          (ISpatialRelation *) ((CStdStubBuffer *)This)->pvServerObject,
          other,
          within);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 34;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 1) & ~ 0x1);
        *(( VARIANT_BOOL * )_StubMsg.Buffer)++ = *within;
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrInterfacePointerFree( &_StubMsg,
                                 (unsigned char *)other,
                                 &__MIDL_TypeFormatString.Format[36] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


HRESULT STDMETHODCALLTYPE ISpatialRelation_Disjoint_Proxy( 
    ISpatialRelation * This,
    /* [in] */ IGeometry *other,
    /* [retval][out] */ VARIANT_BOOL *disjoint)
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
        
        
        
        if(!disjoint)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrInterfacePointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                           (unsigned char *)other,
                                           (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[36] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrInterfacePointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                         (unsigned char *)other,
                                         (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[36] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[180] );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 1) & ~ 0x1);
            *disjoint = *(( VARIANT_BOOL * )_StubMsg.Buffer)++;
            
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[28],
                         ( void * )disjoint);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB ISpatialRelation_Disjoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    VARIANT_BOOL _M44	=	0;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    VARIANT_BOOL *disjoint;
    IGeometry *other;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    other = 0;
    ( VARIANT_BOOL * )disjoint = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[180] );
        
        NdrInterfacePointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char * *)&other,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[36],
                                       (unsigned char)0 );
        
        disjoint = &_M44;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISpatialRelation*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> Disjoint(
            (ISpatialRelation *) ((CStdStubBuffer *)This)->pvServerObject,
            other,
            disjoint);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 34;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 1) & ~ 0x1);
        *(( VARIANT_BOOL * )_StubMsg.Buffer)++ = *disjoint;
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrInterfacePointerFree( &_StubMsg,
                                 (unsigned char *)other,
                                 &__MIDL_TypeFormatString.Format[36] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


HRESULT STDMETHODCALLTYPE ISpatialRelation_Crosses_Proxy( 
    ISpatialRelation * This,
    /* [in] */ IGeometry *other,
    /* [retval][out] */ VARIANT_BOOL *crosses)
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
        
        
        
        if(!crosses)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrInterfacePointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                           (unsigned char *)other,
                                           (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[36] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrInterfacePointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                         (unsigned char *)other,
                                         (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[36] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[180] );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 1) & ~ 0x1);
            *crosses = *(( VARIANT_BOOL * )_StubMsg.Buffer)++;
            
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[28],
                         ( void * )crosses);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB ISpatialRelation_Crosses_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    VARIANT_BOOL _M45	=	0;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    VARIANT_BOOL *crosses;
    IGeometry *other;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    other = 0;
    ( VARIANT_BOOL * )crosses = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[180] );
        
        NdrInterfacePointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char * *)&other,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[36],
                                       (unsigned char)0 );
        
        crosses = &_M45;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISpatialRelation*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> Crosses(
           (ISpatialRelation *) ((CStdStubBuffer *)This)->pvServerObject,
           other,
           crosses);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 34;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 1) & ~ 0x1);
        *(( VARIANT_BOOL * )_StubMsg.Buffer)++ = *crosses;
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrInterfacePointerFree( &_StubMsg,
                                 (unsigned char *)other,
                                 &__MIDL_TypeFormatString.Format[36] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


HRESULT STDMETHODCALLTYPE ISpatialRelation_Overlaps_Proxy( 
    ISpatialRelation * This,
    /* [in] */ IGeometry *other,
    /* [retval][out] */ VARIANT_BOOL *overlaps)
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
                      9);
        
        
        
        if(!overlaps)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrInterfacePointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                           (unsigned char *)other,
                                           (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[36] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrInterfacePointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                         (unsigned char *)other,
                                         (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[36] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[180] );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 1) & ~ 0x1);
            *overlaps = *(( VARIANT_BOOL * )_StubMsg.Buffer)++;
            
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[28],
                         ( void * )overlaps);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB ISpatialRelation_Overlaps_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    VARIANT_BOOL _M46	=	0;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    IGeometry *other;
    VARIANT_BOOL *overlaps;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    other = 0;
    ( VARIANT_BOOL * )overlaps = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[180] );
        
        NdrInterfacePointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char * *)&other,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[36],
                                       (unsigned char)0 );
        
        overlaps = &_M46;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISpatialRelation*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> Overlaps(
            (ISpatialRelation *) ((CStdStubBuffer *)This)->pvServerObject,
            other,
            overlaps);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 34;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 1) & ~ 0x1);
        *(( VARIANT_BOOL * )_StubMsg.Buffer)++ = *overlaps;
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrInterfacePointerFree( &_StubMsg,
                                 (unsigned char *)other,
                                 &__MIDL_TypeFormatString.Format[36] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


HRESULT STDMETHODCALLTYPE ISpatialRelation_Intersects_Proxy( 
    ISpatialRelation * This,
    /* [in] */ IGeometry *other,
    /* [retval][out] */ VARIANT_BOOL *overlaps)
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
        
        
        
        if(!overlaps)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrInterfacePointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                           (unsigned char *)other,
                                           (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[36] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrInterfacePointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                         (unsigned char *)other,
                                         (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[36] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[180] );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 1) & ~ 0x1);
            *overlaps = *(( VARIANT_BOOL * )_StubMsg.Buffer)++;
            
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[28],
                         ( void * )overlaps);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB ISpatialRelation_Intersects_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    VARIANT_BOOL _M47	=	0;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    IGeometry *other;
    VARIANT_BOOL *overlaps;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    other = 0;
    ( VARIANT_BOOL * )overlaps = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[180] );
        
        NdrInterfacePointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char * *)&other,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[36],
                                       (unsigned char)0 );
        
        overlaps = &_M47;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISpatialRelation*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> Intersects(
              (ISpatialRelation *) ((CStdStubBuffer *)This)->pvServerObject,
              other,
              overlaps);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 34;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 1) & ~ 0x1);
        *(( VARIANT_BOOL * )_StubMsg.Buffer)++ = *overlaps;
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrInterfacePointerFree( &_StubMsg,
                                 (unsigned char *)other,
                                 &__MIDL_TypeFormatString.Format[36] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO ISpatialRelation2_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO ISpatialRelation2_ProxyInfo;


HRESULT STDMETHODCALLTYPE ISpatialRelation2_Relate_Proxy( 
    ISpatialRelation2 * This,
    /* [in] */ IGeometry *other,
    /* [in] */ BSTR patternMatrix,
    /* [retval][out] */ VARIANT_BOOL *isRelated)
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
        
        
        
        if(!isRelated)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrInterfacePointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                           (unsigned char *)other,
                                           (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[36] );
            
            NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char *)&patternMatrix,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1060] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrInterfacePointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                         (unsigned char *)other,
                                         (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[36] );
            
            NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                    (unsigned char *)&patternMatrix,
                                    (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1060] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[190] );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 1) & ~ 0x1);
            *isRelated = *(( VARIANT_BOOL * )_StubMsg.Buffer)++;
            
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[28],
                         ( void * )isRelated);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB ISpatialRelation2_Relate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    VARIANT_BOOL _M48	=	0;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    void *_p_patternMatrix;
    VARIANT_BOOL *isRelated;
    IGeometry *other;
    BSTR patternMatrix;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    other = 0;
    _p_patternMatrix = &patternMatrix;
    MIDL_memset(
               _p_patternMatrix,
               0,
               sizeof( BSTR  ));
    ( VARIANT_BOOL * )isRelated = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[190] );
        
        NdrInterfacePointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char * *)&other,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[36],
                                       (unsigned char)0 );
        
        NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&_p_patternMatrix,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1060],
                                  (unsigned char)0 );
        
        isRelated = &_M48;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISpatialRelation2*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> Relate(
          (ISpatialRelation2 *) ((CStdStubBuffer *)This)->pvServerObject,
          other,
          patternMatrix,
          isRelated);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 34;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 1) & ~ 0x1);
        *(( VARIANT_BOOL * )_StubMsg.Buffer)++ = *isRelated;
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrInterfacePointerFree( &_StubMsg,
                                 (unsigned char *)other,
                                 &__MIDL_TypeFormatString.Format[36] );
        
        NdrUserMarshalFree( &_StubMsg,
                            (unsigned char *)&patternMatrix,
                            &__MIDL_TypeFormatString.Format[1060] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO ISpatialOperator_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO ISpatialOperator_ProxyInfo;


HRESULT STDMETHODCALLTYPE ISpatialOperator_Distance_Proxy( 
    ISpatialOperator * This,
    /* [in] */ IGeometry *other,
    /* [retval][out] */ double *distance)
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
        
        
        
        if(!distance)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrInterfacePointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                           (unsigned char *)other,
                                           (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[36] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrInterfacePointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                         (unsigned char *)other,
                                         (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[36] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[204] );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 7) & ~ 0x7);
            *distance = *(( double * )_StubMsg.Buffer)++;
            
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
                         ( void * )distance);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB ISpatialOperator_Distance_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    double _M49	=	0;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    double *distance;
    IGeometry *other;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    other = 0;
    ( double * )distance = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[204] );
        
        NdrInterfacePointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char * *)&other,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[36],
                                       (unsigned char)0 );
        
        distance = &_M49;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISpatialOperator*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> Distance(
            (ISpatialOperator *) ((CStdStubBuffer *)This)->pvServerObject,
            other,
            distance);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 44;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 7) & ~ 0x7);
        *(( double * )_StubMsg.Buffer)++ = *distance;
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrInterfacePointerFree( &_StubMsg,
                                 (unsigned char *)other,
                                 &__MIDL_TypeFormatString.Format[36] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


HRESULT STDMETHODCALLTYPE ISpatialOperator_Boundary_Proxy( 
    ISpatialOperator * This,
    /* [retval][out] */ IGeometry **boundary)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(boundary)
        {
        MIDL_memset(
               boundary,
               0,
               sizeof( IGeometry ** ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      4);
        
        
        
        if(!boundary)
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
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[26] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&boundary,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[32],
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[32],
                         ( void * )boundary);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB ISpatialOperator_Boundary_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    IGeometry *_M50;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    IGeometry **boundary;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( IGeometry ** )boundary = 0;
    RpcTryFinally
        {
        boundary = &_M50;
        _M50 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISpatialOperator*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> Boundary((ISpatialOperator *) ((CStdStubBuffer *)This)->pvServerObject,boundary);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char *)boundary,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[32] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char *)boundary,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[32] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char *)boundary,
                        &__MIDL_TypeFormatString.Format[32] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


HRESULT STDMETHODCALLTYPE ISpatialOperator_Buffer_Proxy( 
    ISpatialOperator * This,
    /* [in] */ double distance,
    /* [retval][out] */ IGeometry **result)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(result)
        {
        MIDL_memset(
               result,
               0,
               sizeof( IGeometry ** ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      5);
        
        
        
        if(!result)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 16;
            NdrProxyGetBuffer(This, &_StubMsg);
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 7) & ~ 0x7);
            *(( double * )_StubMsg.Buffer)++ = distance;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[214] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&result,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[32],
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[32],
                         ( void * )result);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB ISpatialOperator_Buffer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    IGeometry *_M51;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    double distance;
    IGeometry **result;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    distance = 0;
    ( IGeometry ** )result = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[214] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 7) & ~ 0x7);
        
        if(_StubMsg.Buffer + 8 > _StubMsg.BufferEnd)
            {
            RpcRaiseException(RPC_X_BAD_STUB_DATA);
            }
        distance = *(( double * )_StubMsg.Buffer)++;
        
        result = &_M51;
        _M51 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISpatialOperator*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> Buffer(
          (ISpatialOperator *) ((CStdStubBuffer *)This)->pvServerObject,
          distance,
          result);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char *)result,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[32] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char *)result,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[32] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char *)result,
                        &__MIDL_TypeFormatString.Format[32] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


HRESULT STDMETHODCALLTYPE ISpatialOperator_ConvexHull_Proxy( 
    ISpatialOperator * This,
    /* [retval][out] */ IGeometry **result)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(result)
        {
        MIDL_memset(
               result,
               0,
               sizeof( IGeometry ** ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      6);
        
        
        
        if(!result)
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
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[26] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&result,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[32],
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[32],
                         ( void * )result);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB ISpatialOperator_ConvexHull_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    IGeometry *_M52;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    IGeometry **result;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( IGeometry ** )result = 0;
    RpcTryFinally
        {
        result = &_M52;
        _M52 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISpatialOperator*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> ConvexHull((ISpatialOperator *) ((CStdStubBuffer *)This)->pvServerObject,result);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char *)result,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[32] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char *)result,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[32] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char *)result,
                        &__MIDL_TypeFormatString.Format[32] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


HRESULT STDMETHODCALLTYPE ISpatialOperator_Intersection_Proxy( 
    ISpatialOperator * This,
    /* [in] */ IGeometry *other,
    /* [retval][out] */ IGeometry **result)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(result)
        {
        MIDL_memset(
               result,
               0,
               sizeof( IGeometry ** ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      7);
        
        
        
        if(!result)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrInterfacePointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                           (unsigned char *)other,
                                           (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[36] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrInterfacePointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                         (unsigned char *)other,
                                         (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[36] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[222] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&result,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[32],
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[32],
                         ( void * )result);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB ISpatialOperator_Intersection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    IGeometry *_M53;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    IGeometry *other;
    IGeometry **result;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    other = 0;
    ( IGeometry ** )result = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[222] );
        
        NdrInterfacePointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char * *)&other,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[36],
                                       (unsigned char)0 );
        
        result = &_M53;
        _M53 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISpatialOperator*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> Intersection(
                (ISpatialOperator *) ((CStdStubBuffer *)This)->pvServerObject,
                other,
                result);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char *)result,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[32] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char *)result,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[32] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrInterfacePointerFree( &_StubMsg,
                                 (unsigned char *)other,
                                 &__MIDL_TypeFormatString.Format[36] );
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char *)result,
                        &__MIDL_TypeFormatString.Format[32] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


HRESULT STDMETHODCALLTYPE ISpatialOperator_Union_Proxy( 
    ISpatialOperator * This,
    /* [in] */ IGeometry *other,
    /* [retval][out] */ IGeometry **result)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(result)
        {
        MIDL_memset(
               result,
               0,
               sizeof( IGeometry ** ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      8);
        
        
        
        if(!result)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrInterfacePointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                           (unsigned char *)other,
                                           (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[36] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrInterfacePointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                         (unsigned char *)other,
                                         (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[36] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[222] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&result,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[32],
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[32],
                         ( void * )result);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB ISpatialOperator_Union_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    IGeometry *_M54;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    IGeometry *other;
    IGeometry **result;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    other = 0;
    ( IGeometry ** )result = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[222] );
        
        NdrInterfacePointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char * *)&other,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[36],
                                       (unsigned char)0 );
        
        result = &_M54;
        _M54 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISpatialOperator*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> Union(
         (ISpatialOperator *) ((CStdStubBuffer *)This)->pvServerObject,
         other,
         result);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char *)result,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[32] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char *)result,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[32] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrInterfacePointerFree( &_StubMsg,
                                 (unsigned char *)other,
                                 &__MIDL_TypeFormatString.Format[36] );
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char *)result,
                        &__MIDL_TypeFormatString.Format[32] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


HRESULT STDMETHODCALLTYPE ISpatialOperator_Difference_Proxy( 
    ISpatialOperator * This,
    /* [in] */ IGeometry *other,
    /* [retval][out] */ IGeometry **result)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(result)
        {
        MIDL_memset(
               result,
               0,
               sizeof( IGeometry ** ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      9);
        
        
        
        if(!result)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrInterfacePointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                           (unsigned char *)other,
                                           (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[36] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrInterfacePointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                         (unsigned char *)other,
                                         (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[36] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[222] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&result,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[32],
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[32],
                         ( void * )result);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB ISpatialOperator_Difference_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    IGeometry *_M55;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    IGeometry *other;
    IGeometry **result;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    other = 0;
    ( IGeometry ** )result = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[222] );
        
        NdrInterfacePointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char * *)&other,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[36],
                                       (unsigned char)0 );
        
        result = &_M55;
        _M55 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISpatialOperator*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> Difference(
              (ISpatialOperator *) ((CStdStubBuffer *)This)->pvServerObject,
              other,
              result);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char *)result,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[32] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char *)result,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[32] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrInterfacePointerFree( &_StubMsg,
                                 (unsigned char *)other,
                                 &__MIDL_TypeFormatString.Format[36] );
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char *)result,
                        &__MIDL_TypeFormatString.Format[32] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


HRESULT STDMETHODCALLTYPE ISpatialOperator_SymmetricDifference_Proxy( 
    ISpatialOperator * This,
    /* [in] */ IGeometry *other,
    /* [retval][out] */ IGeometry **result)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(result)
        {
        MIDL_memset(
               result,
               0,
               sizeof( IGeometry ** ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      10);
        
        
        
        if(!result)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0;
            NdrInterfacePointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                           (unsigned char *)other,
                                           (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[36] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrInterfacePointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                         (unsigned char *)other,
                                         (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[36] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[222] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&result,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[32],
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[32],
                         ( void * )result);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB ISpatialOperator_SymmetricDifference_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    IGeometry *_M56;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    IGeometry *other;
    IGeometry **result;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    other = 0;
    ( IGeometry ** )result = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[222] );
        
        NdrInterfacePointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char * *)&other,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[36],
                                       (unsigned char)0 );
        
        result = &_M56;
        _M56 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISpatialOperator*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> SymmetricDifference(
                       (ISpatialOperator *) ((CStdStubBuffer *)This)->pvServerObject,
                       other,
                       result);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char *)result,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[32] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char *)result,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[32] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrInterfacePointerFree( &_StubMsg,
                                 (unsigned char *)other,
                                 &__MIDL_TypeFormatString.Format[36] );
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char *)result,
                        &__MIDL_TypeFormatString.Format[32] );
        
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
			0x51,		/* FC_OUT_PARAM */
			0x1,		/* x86 stack size = 1 */
/*  8 */	NdrFcShort( 0x6 ),	/* Type Offset=6 */
/* 10 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 12 */	
			0x4d,		/* FC_IN_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 14 */	NdrFcShort( 0xa ),	/* Type Offset=10 */
/* 16 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 18 */	
			0x51,		/* FC_OUT_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 20 */	NdrFcShort( 0x1c ),	/* Type Offset=28 */
/* 22 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 24 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 26 */	
			0x51,		/* FC_OUT_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 28 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */
/* 30 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 32 */	
			0x4d,		/* FC_IN_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 34 */	NdrFcShort( 0xa ),	/* Type Offset=10 */
/* 36 */	
			0x51,		/* FC_OUT_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 38 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */
/* 40 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 42 */	
			0x51,		/* FC_OUT_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 44 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */
/* 46 */	
			0x51,		/* FC_OUT_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 48 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */
/* 50 */	
			0x51,		/* FC_OUT_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 52 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */
/* 54 */	
			0x51,		/* FC_OUT_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 56 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */
/* 58 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 60 */	
			0x51,		/* FC_OUT_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 62 */	NdrFcShort( 0x3a ),	/* Type Offset=58 */
/* 64 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 66 */	
			0x51,		/* FC_OUT_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 68 */	NdrFcShort( 0x404 ),	/* Type Offset=1028 */
/* 70 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 72 */	
			0x4d,		/* FC_IN_PARAM */
			0x4,		/* x86 stack size = 4 */
/* 74 */	NdrFcShort( 0x416 ),	/* Type Offset=1046 */
/* 76 */	
			0x4d,		/* FC_IN_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 78 */	NdrFcShort( 0xa ),	/* Type Offset=10 */
/* 80 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 82 */	
			0x4d,		/* FC_IN_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 84 */	NdrFcShort( 0x424 ),	/* Type Offset=1060 */
/* 86 */	
			0x4d,		/* FC_IN_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 88 */	NdrFcShort( 0xa ),	/* Type Offset=10 */
/* 90 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 92 */	
			0x4d,		/* FC_IN_PARAM */
			0x4,		/* x86 stack size = 4 */
/* 94 */	NdrFcShort( 0x416 ),	/* Type Offset=1046 */
/* 96 */	
			0x4d,		/* FC_IN_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 98 */	NdrFcShort( 0xa ),	/* Type Offset=10 */
/* 100 */	
			0x51,		/* FC_OUT_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 102 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */
/* 104 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 106 */	
			0x4d,		/* FC_IN_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 108 */	NdrFcShort( 0x424 ),	/* Type Offset=1060 */
/* 110 */	
			0x4d,		/* FC_IN_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 112 */	NdrFcShort( 0xa ),	/* Type Offset=10 */
/* 114 */	
			0x51,		/* FC_OUT_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 116 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */
/* 118 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 120 */	
			0x51,		/* FC_OUT_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 122 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */
/* 124 */	
			0x51,		/* FC_OUT_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 126 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */
/* 128 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 130 */	
			0x51,		/* FC_OUT_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 132 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */
/* 134 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 136 */	
			0x51,		/* FC_OUT_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 138 */	NdrFcShort( 0x42e ),	/* Type Offset=1070 */
/* 140 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 142 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0xc,		/* FC_DOUBLE */
/* 144 */	
			0x51,		/* FC_OUT_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 146 */	NdrFcShort( 0x42e ),	/* Type Offset=1070 */
/* 148 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 150 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 152 */	
			0x51,		/* FC_OUT_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 154 */	NdrFcShort( 0x42e ),	/* Type Offset=1070 */
/* 156 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 158 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 160 */	
			0x51,		/* FC_OUT_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 162 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */
/* 164 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 166 */	
			0x51,		/* FC_OUT_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 168 */	NdrFcShort( 0x444 ),	/* Type Offset=1092 */
/* 170 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 172 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 174 */	
			0x51,		/* FC_OUT_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 176 */	NdrFcShort( 0x444 ),	/* Type Offset=1092 */
/* 178 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 180 */	
			0x4d,		/* FC_IN_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 182 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */
/* 184 */	
			0x51,		/* FC_OUT_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 186 */	NdrFcShort( 0x1c ),	/* Type Offset=28 */
/* 188 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 190 */	
			0x4d,		/* FC_IN_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 192 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */
/* 194 */	
			0x4d,		/* FC_IN_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 196 */	NdrFcShort( 0x424 ),	/* Type Offset=1060 */
/* 198 */	
			0x51,		/* FC_OUT_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 200 */	NdrFcShort( 0x1c ),	/* Type Offset=28 */
/* 202 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 204 */	
			0x4d,		/* FC_IN_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 206 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */
/* 208 */	
			0x51,		/* FC_OUT_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 210 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */
/* 212 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 214 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0xc,		/* FC_DOUBLE */
/* 216 */	
			0x51,		/* FC_OUT_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 218 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */
/* 220 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 222 */	
			0x4d,		/* FC_IN_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 224 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */
/* 226 */	
			0x51,		/* FC_OUT_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 228 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */
/* 230 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
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
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/*  4 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/*  6 */	
			0x11, 0x14,	/* FC_RP [alloced_on_stack] [pointer_deref] */
/*  8 */	NdrFcShort( 0x2 ),	/* Offset= 2 (10) */
/* 10 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 12 */	NdrFcLong( 0x4c4c5c00 ),	/* 1280072704 */
/* 16 */	NdrFcShort( 0xfe1e ),	/* -482 */
/* 18 */	NdrFcShort( 0x11d0 ),	/* 4560 */
/* 20 */	0xad,		/* 173 */
			0x87,		/* 135 */
/* 22 */	0x8,		/* 8 */
			0x0,		/* 0 */
/* 24 */	0x9,		/* 9 */
			0xb6,		/* 182 */
/* 26 */	0xf2,		/* 242 */
			0x2b,		/* 43 */
/* 28 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 30 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 32 */	
			0x11, 0x14,	/* FC_RP [alloced_on_stack] [pointer_deref] */
/* 34 */	NdrFcShort( 0x2 ),	/* Offset= 2 (36) */
/* 36 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 38 */	NdrFcLong( 0x6a124031 ),	/* 1779580977 */
/* 42 */	NdrFcShort( 0xfe38 ),	/* -456 */
/* 44 */	NdrFcShort( 0x11d0 ),	/* 4560 */
/* 46 */	0xbe,		/* 190 */
			0xce,		/* 206 */
/* 48 */	0x0,		/* 0 */
			0x80,		/* 128 */
/* 50 */	0x5f,		/* 95 */
			0x7c,		/* 124 */
/* 52 */	0x42,		/* 66 */
			0x68,		/* 104 */
/* 54 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 56 */	0xc,		/* FC_DOUBLE */
			0x5c,		/* FC_PAD */
/* 58 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 60 */	NdrFcShort( 0x3be ),	/* Offset= 958 (1018) */
/* 62 */	
			0x13, 0x0,	/* FC_OP */
/* 64 */	NdrFcShort( 0x3a6 ),	/* Offset= 934 (998) */
/* 66 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 68 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 70 */	NdrFcShort( 0xfff8 ),	/* -8 */
/* 72 */	NdrFcShort( 0x2 ),	/* Offset= 2 (74) */
/* 74 */	NdrFcShort( 0x10 ),	/* 16 */
/* 76 */	NdrFcShort( 0x2b ),	/* 43 */
/* 78 */	NdrFcLong( 0x3 ),	/* 3 */
/* 82 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 84 */	NdrFcLong( 0x11 ),	/* 17 */
/* 88 */	NdrFcShort( 0x8002 ),	/* Simple arm type: FC_CHAR */
/* 90 */	NdrFcLong( 0x2 ),	/* 2 */
/* 94 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 96 */	NdrFcLong( 0x4 ),	/* 4 */
/* 100 */	NdrFcShort( 0x800a ),	/* Simple arm type: FC_FLOAT */
/* 102 */	NdrFcLong( 0x5 ),	/* 5 */
/* 106 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 108 */	NdrFcLong( 0xb ),	/* 11 */
/* 112 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 114 */	NdrFcLong( 0xa ),	/* 10 */
/* 118 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 120 */	NdrFcLong( 0x6 ),	/* 6 */
/* 124 */	NdrFcShort( 0xd6 ),	/* Offset= 214 (338) */
/* 126 */	NdrFcLong( 0x7 ),	/* 7 */
/* 130 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 132 */	NdrFcLong( 0x8 ),	/* 8 */
/* 136 */	NdrFcShort( 0xd0 ),	/* Offset= 208 (344) */
/* 138 */	NdrFcLong( 0xd ),	/* 13 */
/* 142 */	NdrFcShort( 0xe2 ),	/* Offset= 226 (368) */
/* 144 */	NdrFcLong( 0x9 ),	/* 9 */
/* 148 */	NdrFcShort( 0xee ),	/* Offset= 238 (386) */
/* 150 */	NdrFcLong( 0x2000 ),	/* 8192 */
/* 154 */	NdrFcShort( 0xfa ),	/* Offset= 250 (404) */
/* 156 */	NdrFcLong( 0x24 ),	/* 36 */
/* 160 */	NdrFcShort( 0x304 ),	/* Offset= 772 (932) */
/* 162 */	NdrFcLong( 0x4024 ),	/* 16420 */
/* 166 */	NdrFcShort( 0x2fe ),	/* Offset= 766 (932) */
/* 168 */	NdrFcLong( 0x4011 ),	/* 16401 */
/* 172 */	NdrFcShort( 0x2fc ),	/* Offset= 764 (936) */
/* 174 */	NdrFcLong( 0x4002 ),	/* 16386 */
/* 178 */	NdrFcShort( 0x2fa ),	/* Offset= 762 (940) */
/* 180 */	NdrFcLong( 0x4003 ),	/* 16387 */
/* 184 */	NdrFcShort( 0x2f8 ),	/* Offset= 760 (944) */
/* 186 */	NdrFcLong( 0x4004 ),	/* 16388 */
/* 190 */	NdrFcShort( 0x2f6 ),	/* Offset= 758 (948) */
/* 192 */	NdrFcLong( 0x4005 ),	/* 16389 */
/* 196 */	NdrFcShort( 0x2f4 ),	/* Offset= 756 (952) */
/* 198 */	NdrFcLong( 0x400b ),	/* 16395 */
/* 202 */	NdrFcShort( 0x2e2 ),	/* Offset= 738 (940) */
/* 204 */	NdrFcLong( 0x400a ),	/* 16394 */
/* 208 */	NdrFcShort( 0x2e0 ),	/* Offset= 736 (944) */
/* 210 */	NdrFcLong( 0x4006 ),	/* 16390 */
/* 214 */	NdrFcShort( 0x2e6 ),	/* Offset= 742 (956) */
/* 216 */	NdrFcLong( 0x4007 ),	/* 16391 */
/* 220 */	NdrFcShort( 0x2dc ),	/* Offset= 732 (952) */
/* 222 */	NdrFcLong( 0x4008 ),	/* 16392 */
/* 226 */	NdrFcShort( 0x2de ),	/* Offset= 734 (960) */
/* 228 */	NdrFcLong( 0x400d ),	/* 16397 */
/* 232 */	NdrFcShort( 0x2dc ),	/* Offset= 732 (964) */
/* 234 */	NdrFcLong( 0x4009 ),	/* 16393 */
/* 238 */	NdrFcShort( 0x2da ),	/* Offset= 730 (968) */
/* 240 */	NdrFcLong( 0x6000 ),	/* 24576 */
/* 244 */	NdrFcShort( 0x2d8 ),	/* Offset= 728 (972) */
/* 246 */	NdrFcLong( 0x400c ),	/* 16396 */
/* 250 */	NdrFcShort( 0x2d6 ),	/* Offset= 726 (976) */
/* 252 */	NdrFcLong( 0x10 ),	/* 16 */
/* 256 */	NdrFcShort( 0x8002 ),	/* Simple arm type: FC_CHAR */
/* 258 */	NdrFcLong( 0x12 ),	/* 18 */
/* 262 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 264 */	NdrFcLong( 0x13 ),	/* 19 */
/* 268 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 270 */	NdrFcLong( 0x16 ),	/* 22 */
/* 274 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 276 */	NdrFcLong( 0x17 ),	/* 23 */
/* 280 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 282 */	NdrFcLong( 0xe ),	/* 14 */
/* 286 */	NdrFcShort( 0x2ba ),	/* Offset= 698 (984) */
/* 288 */	NdrFcLong( 0x400e ),	/* 16398 */
/* 292 */	NdrFcShort( 0x2be ),	/* Offset= 702 (994) */
/* 294 */	NdrFcLong( 0x4010 ),	/* 16400 */
/* 298 */	NdrFcShort( 0x27e ),	/* Offset= 638 (936) */
/* 300 */	NdrFcLong( 0x4012 ),	/* 16402 */
/* 304 */	NdrFcShort( 0x27c ),	/* Offset= 636 (940) */
/* 306 */	NdrFcLong( 0x4013 ),	/* 16403 */
/* 310 */	NdrFcShort( 0x27a ),	/* Offset= 634 (944) */
/* 312 */	NdrFcLong( 0x4016 ),	/* 16406 */
/* 316 */	NdrFcShort( 0x274 ),	/* Offset= 628 (944) */
/* 318 */	NdrFcLong( 0x4017 ),	/* 16407 */
/* 322 */	NdrFcShort( 0x26e ),	/* Offset= 622 (944) */
/* 324 */	NdrFcLong( 0x0 ),	/* 0 */
/* 328 */	NdrFcShort( 0x0 ),	/* Offset= 0 (328) */
/* 330 */	NdrFcLong( 0x1 ),	/* 1 */
/* 334 */	NdrFcShort( 0x0 ),	/* Offset= 0 (334) */
/* 336 */	NdrFcShort( 0xffffffff ),	/* Offset= -1 (335) */
/* 338 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 340 */	NdrFcShort( 0x8 ),	/* 8 */
/* 342 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 344 */	
			0x13, 0x0,	/* FC_OP */
/* 346 */	NdrFcShort( 0xc ),	/* Offset= 12 (358) */
/* 348 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 350 */	NdrFcShort( 0x2 ),	/* 2 */
/* 352 */	0x9,		/* Corr desc: FC_ULONG */
			0x0,		/*  */
/* 354 */	NdrFcShort( 0xfffc ),	/* -4 */
/* 356 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 358 */	
			0x17,		/* FC_CSTRUCT */
			0x3,		/* 3 */
/* 360 */	NdrFcShort( 0x8 ),	/* 8 */
/* 362 */	NdrFcShort( 0xfffffff2 ),	/* Offset= -14 (348) */
/* 364 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 366 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 368 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 370 */	NdrFcLong( 0x0 ),	/* 0 */
/* 374 */	NdrFcShort( 0x0 ),	/* 0 */
/* 376 */	NdrFcShort( 0x0 ),	/* 0 */
/* 378 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 380 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 382 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 384 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 386 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 388 */	NdrFcLong( 0x20400 ),	/* 132096 */
/* 392 */	NdrFcShort( 0x0 ),	/* 0 */
/* 394 */	NdrFcShort( 0x0 ),	/* 0 */
/* 396 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 398 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 400 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 402 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 404 */	
			0x13, 0x0,	/* FC_OP */
/* 406 */	NdrFcShort( 0x1fc ),	/* Offset= 508 (914) */
/* 408 */	
			0x2a,		/* FC_ENCAPSULATED_UNION */
			0x49,		/* 73 */
/* 410 */	NdrFcShort( 0x18 ),	/* 24 */
/* 412 */	NdrFcShort( 0xa ),	/* 10 */
/* 414 */	NdrFcLong( 0x8 ),	/* 8 */
/* 418 */	NdrFcShort( 0x58 ),	/* Offset= 88 (506) */
/* 420 */	NdrFcLong( 0xd ),	/* 13 */
/* 424 */	NdrFcShort( 0x78 ),	/* Offset= 120 (544) */
/* 426 */	NdrFcLong( 0x9 ),	/* 9 */
/* 430 */	NdrFcShort( 0x94 ),	/* Offset= 148 (578) */
/* 432 */	NdrFcLong( 0xc ),	/* 12 */
/* 436 */	NdrFcShort( 0xbc ),	/* Offset= 188 (624) */
/* 438 */	NdrFcLong( 0x24 ),	/* 36 */
/* 442 */	NdrFcShort( 0x114 ),	/* Offset= 276 (718) */
/* 444 */	NdrFcLong( 0x800d ),	/* 32781 */
/* 448 */	NdrFcShort( 0x130 ),	/* Offset= 304 (752) */
/* 450 */	NdrFcLong( 0x10 ),	/* 16 */
/* 454 */	NdrFcShort( 0x148 ),	/* Offset= 328 (782) */
/* 456 */	NdrFcLong( 0x2 ),	/* 2 */
/* 460 */	NdrFcShort( 0x160 ),	/* Offset= 352 (812) */
/* 462 */	NdrFcLong( 0x3 ),	/* 3 */
/* 466 */	NdrFcShort( 0x178 ),	/* Offset= 376 (842) */
/* 468 */	NdrFcLong( 0x14 ),	/* 20 */
/* 472 */	NdrFcShort( 0x190 ),	/* Offset= 400 (872) */
/* 474 */	NdrFcShort( 0xffffffff ),	/* Offset= -1 (473) */
/* 476 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 478 */	NdrFcShort( 0x4 ),	/* 4 */
/* 480 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 482 */	NdrFcShort( 0x0 ),	/* 0 */
/* 484 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 486 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 488 */	NdrFcShort( 0x4 ),	/* 4 */
/* 490 */	NdrFcShort( 0x0 ),	/* 0 */
/* 492 */	NdrFcShort( 0x1 ),	/* 1 */
/* 494 */	NdrFcShort( 0x0 ),	/* 0 */
/* 496 */	NdrFcShort( 0x0 ),	/* 0 */
/* 498 */	0x13, 0x0,	/* FC_OP */
/* 500 */	NdrFcShort( 0xffffff72 ),	/* Offset= -142 (358) */
/* 502 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 504 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 506 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 508 */	NdrFcShort( 0x8 ),	/* 8 */
/* 510 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 512 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 514 */	NdrFcShort( 0x4 ),	/* 4 */
/* 516 */	NdrFcShort( 0x4 ),	/* 4 */
/* 518 */	0x11, 0x0,	/* FC_RP */
/* 520 */	NdrFcShort( 0xffffffd4 ),	/* Offset= -44 (476) */
/* 522 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 524 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 526 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 528 */	NdrFcShort( 0x0 ),	/* 0 */
/* 530 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 532 */	NdrFcShort( 0x0 ),	/* 0 */
/* 534 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 538 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 540 */	NdrFcShort( 0xffffff54 ),	/* Offset= -172 (368) */
/* 542 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 544 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 546 */	NdrFcShort( 0x8 ),	/* 8 */
/* 548 */	NdrFcShort( 0x0 ),	/* 0 */
/* 550 */	NdrFcShort( 0x6 ),	/* Offset= 6 (556) */
/* 552 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 554 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 556 */	
			0x11, 0x0,	/* FC_RP */
/* 558 */	NdrFcShort( 0xffffffe0 ),	/* Offset= -32 (526) */
/* 560 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 562 */	NdrFcShort( 0x0 ),	/* 0 */
/* 564 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 566 */	NdrFcShort( 0x0 ),	/* 0 */
/* 568 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 572 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 574 */	NdrFcShort( 0xffffff44 ),	/* Offset= -188 (386) */
/* 576 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 578 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 580 */	NdrFcShort( 0x8 ),	/* 8 */
/* 582 */	NdrFcShort( 0x0 ),	/* 0 */
/* 584 */	NdrFcShort( 0x6 ),	/* Offset= 6 (590) */
/* 586 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 588 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 590 */	
			0x11, 0x0,	/* FC_RP */
/* 592 */	NdrFcShort( 0xffffffe0 ),	/* Offset= -32 (560) */
/* 594 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 596 */	NdrFcShort( 0x4 ),	/* 4 */
/* 598 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 600 */	NdrFcShort( 0x0 ),	/* 0 */
/* 602 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 604 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 606 */	NdrFcShort( 0x4 ),	/* 4 */
/* 608 */	NdrFcShort( 0x0 ),	/* 0 */
/* 610 */	NdrFcShort( 0x1 ),	/* 1 */
/* 612 */	NdrFcShort( 0x0 ),	/* 0 */
/* 614 */	NdrFcShort( 0x0 ),	/* 0 */
/* 616 */	0x13, 0x0,	/* FC_OP */
/* 618 */	NdrFcShort( 0x17c ),	/* Offset= 380 (998) */
/* 620 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 622 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 624 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 626 */	NdrFcShort( 0x8 ),	/* 8 */
/* 628 */	NdrFcShort( 0x0 ),	/* 0 */
/* 630 */	NdrFcShort( 0x6 ),	/* Offset= 6 (636) */
/* 632 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 634 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 636 */	
			0x11, 0x0,	/* FC_RP */
/* 638 */	NdrFcShort( 0xffffffd4 ),	/* Offset= -44 (594) */
/* 640 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 642 */	NdrFcLong( 0x2f ),	/* 47 */
/* 646 */	NdrFcShort( 0x0 ),	/* 0 */
/* 648 */	NdrFcShort( 0x0 ),	/* 0 */
/* 650 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 652 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 654 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 656 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 658 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 660 */	NdrFcShort( 0x1 ),	/* 1 */
/* 662 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 664 */	NdrFcShort( 0x4 ),	/* 4 */
/* 666 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 668 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 670 */	NdrFcShort( 0x10 ),	/* 16 */
/* 672 */	NdrFcShort( 0x0 ),	/* 0 */
/* 674 */	NdrFcShort( 0xa ),	/* Offset= 10 (684) */
/* 676 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 678 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 680 */	NdrFcShort( 0xffffffd8 ),	/* Offset= -40 (640) */
/* 682 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 684 */	
			0x13, 0x0,	/* FC_OP */
/* 686 */	NdrFcShort( 0xffffffe4 ),	/* Offset= -28 (658) */
/* 688 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 690 */	NdrFcShort( 0x4 ),	/* 4 */
/* 692 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 694 */	NdrFcShort( 0x0 ),	/* 0 */
/* 696 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 698 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 700 */	NdrFcShort( 0x4 ),	/* 4 */
/* 702 */	NdrFcShort( 0x0 ),	/* 0 */
/* 704 */	NdrFcShort( 0x1 ),	/* 1 */
/* 706 */	NdrFcShort( 0x0 ),	/* 0 */
/* 708 */	NdrFcShort( 0x0 ),	/* 0 */
/* 710 */	0x13, 0x0,	/* FC_OP */
/* 712 */	NdrFcShort( 0xffffffd4 ),	/* Offset= -44 (668) */
/* 714 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 716 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 718 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 720 */	NdrFcShort( 0x8 ),	/* 8 */
/* 722 */	NdrFcShort( 0x0 ),	/* 0 */
/* 724 */	NdrFcShort( 0x6 ),	/* Offset= 6 (730) */
/* 726 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 728 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 730 */	
			0x11, 0x0,	/* FC_RP */
/* 732 */	NdrFcShort( 0xffffffd4 ),	/* Offset= -44 (688) */
/* 734 */	
			0x1d,		/* FC_SMFARRAY */
			0x0,		/* 0 */
/* 736 */	NdrFcShort( 0x8 ),	/* 8 */
/* 738 */	0x2,		/* FC_CHAR */
			0x5b,		/* FC_END */
/* 740 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 742 */	NdrFcShort( 0x10 ),	/* 16 */
/* 744 */	0x8,		/* FC_LONG */
			0x6,		/* FC_SHORT */
/* 746 */	0x6,		/* FC_SHORT */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 748 */	0x0,		/* 0 */
			NdrFcShort( 0xfffffff1 ),	/* Offset= -15 (734) */
			0x5b,		/* FC_END */
/* 752 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 754 */	NdrFcShort( 0x18 ),	/* 24 */
/* 756 */	NdrFcShort( 0x0 ),	/* 0 */
/* 758 */	NdrFcShort( 0xa ),	/* Offset= 10 (768) */
/* 760 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 762 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 764 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (740) */
/* 766 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 768 */	
			0x11, 0x0,	/* FC_RP */
/* 770 */	NdrFcShort( 0xffffff0c ),	/* Offset= -244 (526) */
/* 772 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 774 */	NdrFcShort( 0x1 ),	/* 1 */
/* 776 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 778 */	NdrFcShort( 0x0 ),	/* 0 */
/* 780 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 782 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 784 */	NdrFcShort( 0x8 ),	/* 8 */
/* 786 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 788 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 790 */	NdrFcShort( 0x4 ),	/* 4 */
/* 792 */	NdrFcShort( 0x4 ),	/* 4 */
/* 794 */	0x13, 0x0,	/* FC_OP */
/* 796 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (772) */
/* 798 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 800 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 802 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 804 */	NdrFcShort( 0x2 ),	/* 2 */
/* 806 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 808 */	NdrFcShort( 0x0 ),	/* 0 */
/* 810 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 812 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 814 */	NdrFcShort( 0x8 ),	/* 8 */
/* 816 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 818 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 820 */	NdrFcShort( 0x4 ),	/* 4 */
/* 822 */	NdrFcShort( 0x4 ),	/* 4 */
/* 824 */	0x13, 0x0,	/* FC_OP */
/* 826 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (802) */
/* 828 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 830 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 832 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 834 */	NdrFcShort( 0x4 ),	/* 4 */
/* 836 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 838 */	NdrFcShort( 0x0 ),	/* 0 */
/* 840 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 842 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 844 */	NdrFcShort( 0x8 ),	/* 8 */
/* 846 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 848 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 850 */	NdrFcShort( 0x4 ),	/* 4 */
/* 852 */	NdrFcShort( 0x4 ),	/* 4 */
/* 854 */	0x13, 0x0,	/* FC_OP */
/* 856 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (832) */
/* 858 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 860 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 862 */	
			0x1b,		/* FC_CARRAY */
			0x7,		/* 7 */
/* 864 */	NdrFcShort( 0x8 ),	/* 8 */
/* 866 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 868 */	NdrFcShort( 0x0 ),	/* 0 */
/* 870 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 872 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 874 */	NdrFcShort( 0x8 ),	/* 8 */
/* 876 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 878 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 880 */	NdrFcShort( 0x4 ),	/* 4 */
/* 882 */	NdrFcShort( 0x4 ),	/* 4 */
/* 884 */	0x13, 0x0,	/* FC_OP */
/* 886 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (862) */
/* 888 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 890 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 892 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 894 */	NdrFcShort( 0x8 ),	/* 8 */
/* 896 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 898 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 900 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 902 */	NdrFcShort( 0x8 ),	/* 8 */
/* 904 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 906 */	NdrFcShort( 0xffd8 ),	/* -40 */
/* 908 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 910 */	NdrFcShort( 0xffffffee ),	/* Offset= -18 (892) */
/* 912 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 914 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 916 */	NdrFcShort( 0x28 ),	/* 40 */
/* 918 */	NdrFcShort( 0xffffffee ),	/* Offset= -18 (900) */
/* 920 */	NdrFcShort( 0x0 ),	/* Offset= 0 (920) */
/* 922 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 924 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 926 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 928 */	NdrFcShort( 0xfffffdf8 ),	/* Offset= -520 (408) */
/* 930 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 932 */	
			0x13, 0x0,	/* FC_OP */
/* 934 */	NdrFcShort( 0xfffffef6 ),	/* Offset= -266 (668) */
/* 936 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 938 */	0x2,		/* FC_CHAR */
			0x5c,		/* FC_PAD */
/* 940 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 942 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 944 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 946 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 948 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 950 */	0xa,		/* FC_FLOAT */
			0x5c,		/* FC_PAD */
/* 952 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 954 */	0xc,		/* FC_DOUBLE */
			0x5c,		/* FC_PAD */
/* 956 */	
			0x13, 0x0,	/* FC_OP */
/* 958 */	NdrFcShort( 0xfffffd94 ),	/* Offset= -620 (338) */
/* 960 */	
			0x13, 0x10,	/* FC_OP [pointer_deref] */
/* 962 */	NdrFcShort( 0xfffffd96 ),	/* Offset= -618 (344) */
/* 964 */	
			0x13, 0x10,	/* FC_OP [pointer_deref] */
/* 966 */	NdrFcShort( 0xfffffdaa ),	/* Offset= -598 (368) */
/* 968 */	
			0x13, 0x10,	/* FC_OP [pointer_deref] */
/* 970 */	NdrFcShort( 0xfffffdb8 ),	/* Offset= -584 (386) */
/* 972 */	
			0x13, 0x10,	/* FC_OP [pointer_deref] */
/* 974 */	NdrFcShort( 0xfffffdc6 ),	/* Offset= -570 (404) */
/* 976 */	
			0x13, 0x10,	/* FC_OP [pointer_deref] */
/* 978 */	NdrFcShort( 0x2 ),	/* Offset= 2 (980) */
/* 980 */	
			0x13, 0x0,	/* FC_OP */
/* 982 */	NdrFcShort( 0x10 ),	/* Offset= 16 (998) */
/* 984 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 986 */	NdrFcShort( 0x10 ),	/* 16 */
/* 988 */	0x6,		/* FC_SHORT */
			0x2,		/* FC_CHAR */
/* 990 */	0x2,		/* FC_CHAR */
			0x8,		/* FC_LONG */
/* 992 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 994 */	
			0x13, 0x0,	/* FC_OP */
/* 996 */	NdrFcShort( 0xfffffff4 ),	/* Offset= -12 (984) */
/* 998 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 1000 */	NdrFcShort( 0x20 ),	/* 32 */
/* 1002 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1004 */	NdrFcShort( 0x0 ),	/* Offset= 0 (1004) */
/* 1006 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1008 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 1010 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 1012 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1014 */	NdrFcShort( 0xfffffc4c ),	/* Offset= -948 (66) */
/* 1016 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1018 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1020 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1022 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1024 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1026 */	NdrFcShort( 0xfffffc3c ),	/* Offset= -964 (62) */
/* 1028 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 1030 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1032) */
/* 1032 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1034 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1036 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1038 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1040 */	NdrFcShort( 0xfffffd48 ),	/* Offset= -696 (344) */
/* 1042 */	
			0x12, 0x0,	/* FC_UP */
/* 1044 */	NdrFcShort( 0xffffffd2 ),	/* Offset= -46 (998) */
/* 1046 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1048 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1050 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1052 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1054 */	NdrFcShort( 0xfffffff4 ),	/* Offset= -12 (1042) */
/* 1056 */	
			0x12, 0x0,	/* FC_UP */
/* 1058 */	NdrFcShort( 0xfffffd44 ),	/* Offset= -700 (358) */
/* 1060 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1062 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1064 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1066 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1068 */	NdrFcShort( 0xfffffff4 ),	/* Offset= -12 (1056) */
/* 1070 */	
			0x11, 0x14,	/* FC_RP [alloced_on_stack] [pointer_deref] */
/* 1072 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1074) */
/* 1074 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1076 */	NdrFcLong( 0x6a124035 ),	/* 1779580981 */
/* 1080 */	NdrFcShort( 0xfe38 ),	/* -456 */
/* 1082 */	NdrFcShort( 0x11d0 ),	/* 4560 */
/* 1084 */	0xbe,		/* 190 */
			0xce,		/* 206 */
/* 1086 */	0x0,		/* 0 */
			0x80,		/* 128 */
/* 1088 */	0x5f,		/* 95 */
			0x7c,		/* 124 */
/* 1090 */	0x42,		/* 66 */
			0x68,		/* 104 */
/* 1092 */	
			0x11, 0x14,	/* FC_RP [alloced_on_stack] [pointer_deref] */
/* 1094 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1096) */
/* 1096 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1098 */	NdrFcLong( 0x6a124038 ),	/* 1779580984 */
/* 1102 */	NdrFcShort( 0xfe38 ),	/* -456 */
/* 1104 */	NdrFcShort( 0x11d0 ),	/* 4560 */
/* 1106 */	0xbe,		/* 190 */
			0xce,		/* 206 */
/* 1108 */	0x0,		/* 0 */
			0x80,		/* 128 */
/* 1110 */	0x5f,		/* 95 */
			0x7c,		/* 124 */
/* 1112 */	0x42,		/* 66 */
			0x68,		/* 104 */

			0x0
        }
    };

static const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ] = 
        {
            
            {
            VARIANT_UserSize
            ,VARIANT_UserMarshal
            ,VARIANT_UserUnmarshal
            ,VARIANT_UserFree
            },
            {
            BSTR_UserSize
            ,BSTR_UserMarshal
            ,BSTR_UserUnmarshal
            ,BSTR_UserFree
            }

        };



/* Standard interface: __MIDL_itf_GeometryIdl_0000, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}} */


/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IGeometry, ver. 0.0,
   GUID={0x6A124031,0xFE38,0x11d0,{0xBE,0xCE,0x00,0x80,0x5F,0x7C,0x42,0x68}} */

#pragma code_seg(".orpc")
static const unsigned short IGeometry_FormatStringOffsetTable[] =
    {
    0,
    6,
    12,
    18,
    24,
    18,
    26,
    26,
    32,
    42
    };

static const MIDL_STUBLESS_PROXY_INFO IGeometry_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IGeometry_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IGeometry_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IGeometry_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
const CINTERFACE_PROXY_VTABLE(13) _IGeometryProxyVtbl = 
{
    &IID_IGeometry,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    IGeometry_get_Dimension_Proxy ,
    IGeometry_get_SpatialReference_Proxy ,
    IGeometry_putref_SpatialReference_Proxy ,
    IGeometry_get_IsEmpty_Proxy ,
    IGeometry_SetEmpty_Proxy ,
    IGeometry_get_IsSimple_Proxy ,
    IGeometry_Envelope_Proxy ,
    IGeometry_Clone_Proxy ,
    IGeometry_Project_Proxy ,
    IGeometry_Extent2D_Proxy
};


static const PRPC_STUB_FUNCTION IGeometry_table[] =
{
    IGeometry_get_Dimension_Stub,
    IGeometry_get_SpatialReference_Stub,
    IGeometry_putref_SpatialReference_Stub,
    IGeometry_get_IsEmpty_Stub,
    IGeometry_SetEmpty_Stub,
    IGeometry_get_IsSimple_Stub,
    IGeometry_Envelope_Stub,
    IGeometry_Clone_Stub,
    IGeometry_Project_Stub,
    IGeometry_Extent2D_Stub
};

const CInterfaceStubVtbl _IGeometryStubVtbl =
{
    &IID_IGeometry,
    &IGeometry_ServerInfo,
    13,
    &IGeometry_table[-3],
    CStdStubBuffer_METHODS
};


/* Object interface: IWks, ver. 0.0,
   GUID={0x6A124032,0xFE38,0x11d0,{0xBE,0xCE,0x00,0x80,0x5F,0x7C,0x42,0x68}} */

#pragma code_seg(".orpc")
static const unsigned short IWks_FormatStringOffsetTable[] =
    {
    60,
    66,
    72,
    82
    };

static const MIDL_STUBLESS_PROXY_INFO IWks_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IWks_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IWks_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IWks_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
const CINTERFACE_PROXY_VTABLE(7) _IWksProxyVtbl = 
{
    &IID_IWks,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    IWks_ExportToWKB_Proxy ,
    IWks_ExportToWKT_Proxy ,
    IWks_ImportFromWKB_Proxy ,
    IWks_ImportFromWKT_Proxy
};


static const PRPC_STUB_FUNCTION IWks_table[] =
{
    IWks_ExportToWKB_Stub,
    IWks_ExportToWKT_Stub,
    IWks_ImportFromWKB_Stub,
    IWks_ImportFromWKT_Stub
};

const CInterfaceStubVtbl _IWksStubVtbl =
{
    &IID_IWks,
    &IWks_ServerInfo,
    7,
    &IWks_table[-3],
    CStdStubBuffer_METHODS
};


/* Object interface: IGeometryFactory, ver. 0.0,
   GUID={0x6A124033,0xFE38,0x11d0,{0xBE,0xCE,0x00,0x80,0x5F,0x7C,0x42,0x68}} */

#pragma code_seg(".orpc")
static const unsigned short IGeometryFactory_FormatStringOffsetTable[] =
    {
    92,
    106
    };

static const MIDL_STUBLESS_PROXY_INFO IGeometryFactory_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IGeometryFactory_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IGeometryFactory_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IGeometryFactory_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
const CINTERFACE_PROXY_VTABLE(5) _IGeometryFactoryProxyVtbl = 
{
    &IID_IGeometryFactory,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    IGeometryFactory_CreateFromWKB_Proxy ,
    IGeometryFactory_CreateFromWKT_Proxy
};


static const PRPC_STUB_FUNCTION IGeometryFactory_table[] =
{
    IGeometryFactory_CreateFromWKB_Stub,
    IGeometryFactory_CreateFromWKT_Stub
};

const CInterfaceStubVtbl _IGeometryFactoryStubVtbl =
{
    &IID_IGeometryFactory,
    &IGeometryFactory_ServerInfo,
    5,
    &IGeometryFactory_table[-3],
    CStdStubBuffer_METHODS
};


/* Object interface: IPoint, ver. 0.0,
   GUID={0x6A124035,0xFE38,0x11d0,{0xBE,0xCE,0x00,0x80,0x5F,0x7C,0x42,0x68}} */

#pragma code_seg(".orpc")
static const unsigned short IPoint_FormatStringOffsetTable[] =
    {
    0,
    6,
    12,
    18,
    24,
    18,
    26,
    26,
    32,
    42,
    120,
    130,
    130
    };

static const MIDL_STUBLESS_PROXY_INFO IPoint_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IPoint_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IPoint_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IPoint_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
const CINTERFACE_PROXY_VTABLE(16) _IPointProxyVtbl = 
{
    &IID_IPoint,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    IGeometry_get_Dimension_Proxy ,
    IGeometry_get_SpatialReference_Proxy ,
    IGeometry_putref_SpatialReference_Proxy ,
    IGeometry_get_IsEmpty_Proxy ,
    IGeometry_SetEmpty_Proxy ,
    IGeometry_get_IsSimple_Proxy ,
    IGeometry_Envelope_Proxy ,
    IGeometry_Clone_Proxy ,
    IGeometry_Project_Proxy ,
    IGeometry_Extent2D_Proxy ,
    IPoint_Coords_Proxy ,
    IPoint_get_X_Proxy ,
    IPoint_get_Y_Proxy
};


static const PRPC_STUB_FUNCTION IPoint_table[] =
{
    IGeometry_get_Dimension_Stub,
    IGeometry_get_SpatialReference_Stub,
    IGeometry_putref_SpatialReference_Stub,
    IGeometry_get_IsEmpty_Stub,
    IGeometry_SetEmpty_Stub,
    IGeometry_get_IsSimple_Stub,
    IGeometry_Envelope_Stub,
    IGeometry_Clone_Stub,
    IGeometry_Project_Stub,
    IGeometry_Extent2D_Stub,
    IPoint_Coords_Stub,
    IPoint_get_X_Stub,
    IPoint_get_Y_Stub
};

const CInterfaceStubVtbl _IPointStubVtbl =
{
    &IID_IPoint,
    &IPoint_ServerInfo,
    16,
    &IPoint_table[-3],
    CStdStubBuffer_METHODS
};


/* Object interface: IPointZ, ver. 0.0,
   GUID={0xD4579E2D,0x1D2B,0x11d3,{0x80,0xBE,0x00,0xC0,0x4F,0x68,0x0F,0xFF}} */

#pragma code_seg(".orpc")
static const unsigned short IPointZ_FormatStringOffsetTable[] =
    {
    0,
    6,
    12,
    18,
    24,
    18,
    26,
    26,
    32,
    42,
    120,
    130,
    130,
    130
    };

static const MIDL_STUBLESS_PROXY_INFO IPointZ_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IPointZ_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IPointZ_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IPointZ_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
const CINTERFACE_PROXY_VTABLE(17) _IPointZProxyVtbl = 
{
    &IID_IPointZ,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    IGeometry_get_Dimension_Proxy ,
    IGeometry_get_SpatialReference_Proxy ,
    IGeometry_putref_SpatialReference_Proxy ,
    IGeometry_get_IsEmpty_Proxy ,
    IGeometry_SetEmpty_Proxy ,
    IGeometry_get_IsSimple_Proxy ,
    IGeometry_Envelope_Proxy ,
    IGeometry_Clone_Proxy ,
    IGeometry_Project_Proxy ,
    IGeometry_Extent2D_Proxy ,
    IPoint_Coords_Proxy ,
    IPoint_get_X_Proxy ,
    IPoint_get_Y_Proxy ,
    IPointZ_get_Z_Proxy
};


static const PRPC_STUB_FUNCTION IPointZ_table[] =
{
    IGeometry_get_Dimension_Stub,
    IGeometry_get_SpatialReference_Stub,
    IGeometry_putref_SpatialReference_Stub,
    IGeometry_get_IsEmpty_Stub,
    IGeometry_SetEmpty_Stub,
    IGeometry_get_IsSimple_Stub,
    IGeometry_Envelope_Stub,
    IGeometry_Clone_Stub,
    IGeometry_Project_Stub,
    IGeometry_Extent2D_Stub,
    IPoint_Coords_Stub,
    IPoint_get_X_Stub,
    IPoint_get_Y_Stub,
    IPointZ_get_Z_Stub
};

const CInterfaceStubVtbl _IPointZStubVtbl =
{
    &IID_IPointZ,
    &IPointZ_ServerInfo,
    17,
    &IPointZ_table[-3],
    CStdStubBuffer_METHODS
};


/* Object interface: ICurve, ver. 0.0,
   GUID={0x6A124036,0xFE38,0x11d0,{0xBE,0xCE,0x00,0x80,0x5F,0x7C,0x42,0x68}} */

#pragma code_seg(".orpc")
static const unsigned short ICurve_FormatStringOffsetTable[] =
    {
    0,
    6,
    12,
    18,
    24,
    18,
    26,
    26,
    32,
    42,
    130,
    136,
    136,
    18,
    142
    };

static const MIDL_STUBLESS_PROXY_INFO ICurve_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &ICurve_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO ICurve_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &ICurve_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
const CINTERFACE_PROXY_VTABLE(18) _ICurveProxyVtbl = 
{
    &IID_ICurve,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    IGeometry_get_Dimension_Proxy ,
    IGeometry_get_SpatialReference_Proxy ,
    IGeometry_putref_SpatialReference_Proxy ,
    IGeometry_get_IsEmpty_Proxy ,
    IGeometry_SetEmpty_Proxy ,
    IGeometry_get_IsSimple_Proxy ,
    IGeometry_Envelope_Proxy ,
    IGeometry_Clone_Proxy ,
    IGeometry_Project_Proxy ,
    IGeometry_Extent2D_Proxy ,
    ICurve_get_Length_Proxy ,
    ICurve_StartPoint_Proxy ,
    ICurve_EndPoint_Proxy ,
    ICurve_get_IsClosed_Proxy ,
    ICurve_Value_Proxy
};


static const PRPC_STUB_FUNCTION ICurve_table[] =
{
    IGeometry_get_Dimension_Stub,
    IGeometry_get_SpatialReference_Stub,
    IGeometry_putref_SpatialReference_Stub,
    IGeometry_get_IsEmpty_Stub,
    IGeometry_SetEmpty_Stub,
    IGeometry_get_IsSimple_Stub,
    IGeometry_Envelope_Stub,
    IGeometry_Clone_Stub,
    IGeometry_Project_Stub,
    IGeometry_Extent2D_Stub,
    ICurve_get_Length_Stub,
    ICurve_StartPoint_Stub,
    ICurve_EndPoint_Stub,
    ICurve_get_IsClosed_Stub,
    ICurve_Value_Stub
};

const CInterfaceStubVtbl _ICurveStubVtbl =
{
    &IID_ICurve,
    &ICurve_ServerInfo,
    18,
    &ICurve_table[-3],
    CStdStubBuffer_METHODS
};


/* Object interface: ILineString, ver. 0.0,
   GUID={0x6A124037,0xFE38,0x11d0,{0xBE,0xCE,0x00,0x80,0x5F,0x7C,0x42,0x68}} */

#pragma code_seg(".orpc")
static const unsigned short ILineString_FormatStringOffsetTable[] =
    {
    0,
    6,
    12,
    18,
    24,
    18,
    26,
    26,
    32,
    42,
    130,
    136,
    136,
    18,
    142,
    0,
    150
    };

static const MIDL_STUBLESS_PROXY_INFO ILineString_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &ILineString_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO ILineString_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &ILineString_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
const CINTERFACE_PROXY_VTABLE(20) _ILineStringProxyVtbl = 
{
    &IID_ILineString,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    IGeometry_get_Dimension_Proxy ,
    IGeometry_get_SpatialReference_Proxy ,
    IGeometry_putref_SpatialReference_Proxy ,
    IGeometry_get_IsEmpty_Proxy ,
    IGeometry_SetEmpty_Proxy ,
    IGeometry_get_IsSimple_Proxy ,
    IGeometry_Envelope_Proxy ,
    IGeometry_Clone_Proxy ,
    IGeometry_Project_Proxy ,
    IGeometry_Extent2D_Proxy ,
    ICurve_get_Length_Proxy ,
    ICurve_StartPoint_Proxy ,
    ICurve_EndPoint_Proxy ,
    ICurve_get_IsClosed_Proxy ,
    ICurve_Value_Proxy ,
    ILineString_get_NumPoints_Proxy ,
    ILineString_Point_Proxy
};


static const PRPC_STUB_FUNCTION ILineString_table[] =
{
    IGeometry_get_Dimension_Stub,
    IGeometry_get_SpatialReference_Stub,
    IGeometry_putref_SpatialReference_Stub,
    IGeometry_get_IsEmpty_Stub,
    IGeometry_SetEmpty_Stub,
    IGeometry_get_IsSimple_Stub,
    IGeometry_Envelope_Stub,
    IGeometry_Clone_Stub,
    IGeometry_Project_Stub,
    IGeometry_Extent2D_Stub,
    ICurve_get_Length_Stub,
    ICurve_StartPoint_Stub,
    ICurve_EndPoint_Stub,
    ICurve_get_IsClosed_Stub,
    ICurve_Value_Stub,
    ILineString_get_NumPoints_Stub,
    ILineString_Point_Stub
};

const CInterfaceStubVtbl _ILineStringStubVtbl =
{
    &IID_ILineString,
    &ILineString_ServerInfo,
    20,
    &ILineString_table[-3],
    CStdStubBuffer_METHODS
};


/* Object interface: ILinearRing, ver. 0.0,
   GUID={0x6A124038,0xFE38,0x11d0,{0xBE,0xCE,0x00,0x80,0x5F,0x7C,0x42,0x68}} */

#pragma code_seg(".orpc")
static const unsigned short ILinearRing_FormatStringOffsetTable[] =
    {
    0,
    6,
    12,
    18,
    24,
    18,
    26,
    26,
    32,
    42,
    130,
    136,
    136,
    18,
    142,
    0,
    150,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO ILinearRing_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &ILinearRing_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO ILinearRing_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &ILinearRing_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
const CINTERFACE_PROXY_VTABLE(20) _ILinearRingProxyVtbl = 
{
    &IID_ILinearRing,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    IGeometry_get_Dimension_Proxy ,
    IGeometry_get_SpatialReference_Proxy ,
    IGeometry_putref_SpatialReference_Proxy ,
    IGeometry_get_IsEmpty_Proxy ,
    IGeometry_SetEmpty_Proxy ,
    IGeometry_get_IsSimple_Proxy ,
    IGeometry_Envelope_Proxy ,
    IGeometry_Clone_Proxy ,
    IGeometry_Project_Proxy ,
    IGeometry_Extent2D_Proxy ,
    ICurve_get_Length_Proxy ,
    ICurve_StartPoint_Proxy ,
    ICurve_EndPoint_Proxy ,
    ICurve_get_IsClosed_Proxy ,
    ICurve_Value_Proxy ,
    ILineString_get_NumPoints_Proxy ,
    ILineString_Point_Proxy
};


static const PRPC_STUB_FUNCTION ILinearRing_table[] =
{
    IGeometry_get_Dimension_Stub,
    IGeometry_get_SpatialReference_Stub,
    IGeometry_putref_SpatialReference_Stub,
    IGeometry_get_IsEmpty_Stub,
    IGeometry_SetEmpty_Stub,
    IGeometry_get_IsSimple_Stub,
    IGeometry_Envelope_Stub,
    IGeometry_Clone_Stub,
    IGeometry_Project_Stub,
    IGeometry_Extent2D_Stub,
    ICurve_get_Length_Stub,
    ICurve_StartPoint_Stub,
    ICurve_EndPoint_Stub,
    ICurve_get_IsClosed_Stub,
    ICurve_Value_Stub,
    ILineString_get_NumPoints_Stub,
    ILineString_Point_Stub
};

const CInterfaceStubVtbl _ILinearRingStubVtbl =
{
    &IID_ILinearRing,
    &ILinearRing_ServerInfo,
    20,
    &ILinearRing_table[-3],
    CStdStubBuffer_METHODS
};


/* Object interface: ISurface, ver. 0.0,
   GUID={0x6A124039,0xFE38,0x11d0,{0xBE,0xCE,0x00,0x80,0x5F,0x7C,0x42,0x68}} */

#pragma code_seg(".orpc")
static const unsigned short ISurface_FormatStringOffsetTable[] =
    {
    0,
    6,
    12,
    18,
    24,
    18,
    26,
    26,
    32,
    42,
    130,
    136,
    136
    };

static const MIDL_STUBLESS_PROXY_INFO ISurface_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &ISurface_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO ISurface_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &ISurface_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
const CINTERFACE_PROXY_VTABLE(16) _ISurfaceProxyVtbl = 
{
    &IID_ISurface,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    IGeometry_get_Dimension_Proxy ,
    IGeometry_get_SpatialReference_Proxy ,
    IGeometry_putref_SpatialReference_Proxy ,
    IGeometry_get_IsEmpty_Proxy ,
    IGeometry_SetEmpty_Proxy ,
    IGeometry_get_IsSimple_Proxy ,
    IGeometry_Envelope_Proxy ,
    IGeometry_Clone_Proxy ,
    IGeometry_Project_Proxy ,
    IGeometry_Extent2D_Proxy ,
    ISurface_get_Area_Proxy ,
    ISurface_Centroid_Proxy ,
    ISurface_PointOnSurface_Proxy
};


static const PRPC_STUB_FUNCTION ISurface_table[] =
{
    IGeometry_get_Dimension_Stub,
    IGeometry_get_SpatialReference_Stub,
    IGeometry_putref_SpatialReference_Stub,
    IGeometry_get_IsEmpty_Stub,
    IGeometry_SetEmpty_Stub,
    IGeometry_get_IsSimple_Stub,
    IGeometry_Envelope_Stub,
    IGeometry_Clone_Stub,
    IGeometry_Project_Stub,
    IGeometry_Extent2D_Stub,
    ISurface_get_Area_Stub,
    ISurface_Centroid_Stub,
    ISurface_PointOnSurface_Stub
};

const CInterfaceStubVtbl _ISurfaceStubVtbl =
{
    &IID_ISurface,
    &ISurface_ServerInfo,
    16,
    &ISurface_table[-3],
    CStdStubBuffer_METHODS
};


/* Object interface: IGeometryCollection, ver. 0.0,
   GUID={0x6A12403A,0xFE38,0x11d0,{0xBE,0xCE,0x00,0x80,0x5F,0x7C,0x42,0x68}} */

#pragma code_seg(".orpc")
static const unsigned short IGeometryCollection_FormatStringOffsetTable[] =
    {
    0,
    6,
    12,
    18,
    24,
    18,
    26,
    26,
    32,
    42,
    0,
    158
    };

static const MIDL_STUBLESS_PROXY_INFO IGeometryCollection_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IGeometryCollection_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IGeometryCollection_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IGeometryCollection_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
const CINTERFACE_PROXY_VTABLE(15) _IGeometryCollectionProxyVtbl = 
{
    &IID_IGeometryCollection,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    IGeometry_get_Dimension_Proxy ,
    IGeometry_get_SpatialReference_Proxy ,
    IGeometry_putref_SpatialReference_Proxy ,
    IGeometry_get_IsEmpty_Proxy ,
    IGeometry_SetEmpty_Proxy ,
    IGeometry_get_IsSimple_Proxy ,
    IGeometry_Envelope_Proxy ,
    IGeometry_Clone_Proxy ,
    IGeometry_Project_Proxy ,
    IGeometry_Extent2D_Proxy ,
    IGeometryCollection_get_NumGeometries_Proxy ,
    IGeometryCollection_Geometry_Proxy
};


static const PRPC_STUB_FUNCTION IGeometryCollection_table[] =
{
    IGeometry_get_Dimension_Stub,
    IGeometry_get_SpatialReference_Stub,
    IGeometry_putref_SpatialReference_Stub,
    IGeometry_get_IsEmpty_Stub,
    IGeometry_SetEmpty_Stub,
    IGeometry_get_IsSimple_Stub,
    IGeometry_Envelope_Stub,
    IGeometry_Clone_Stub,
    IGeometry_Project_Stub,
    IGeometry_Extent2D_Stub,
    IGeometryCollection_get_NumGeometries_Stub,
    IGeometryCollection_Geometry_Stub
};

const CInterfaceStubVtbl _IGeometryCollectionStubVtbl =
{
    &IID_IGeometryCollection,
    &IGeometryCollection_ServerInfo,
    15,
    &IGeometryCollection_table[-3],
    CStdStubBuffer_METHODS
};


/* Object interface: IPolygon, ver. 0.0,
   GUID={0x6A12403C,0xFE38,0x11d0,{0xBE,0xCE,0x00,0x80,0x5F,0x7C,0x42,0x68}} */

#pragma code_seg(".orpc")
static const unsigned short IPolygon_FormatStringOffsetTable[] =
    {
    0,
    6,
    12,
    18,
    24,
    18,
    26,
    26,
    32,
    42,
    130,
    136,
    136,
    166,
    0,
    172
    };

static const MIDL_STUBLESS_PROXY_INFO IPolygon_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IPolygon_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IPolygon_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IPolygon_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
const CINTERFACE_PROXY_VTABLE(19) _IPolygonProxyVtbl = 
{
    &IID_IPolygon,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    IGeometry_get_Dimension_Proxy ,
    IGeometry_get_SpatialReference_Proxy ,
    IGeometry_putref_SpatialReference_Proxy ,
    IGeometry_get_IsEmpty_Proxy ,
    IGeometry_SetEmpty_Proxy ,
    IGeometry_get_IsSimple_Proxy ,
    IGeometry_Envelope_Proxy ,
    IGeometry_Clone_Proxy ,
    IGeometry_Project_Proxy ,
    IGeometry_Extent2D_Proxy ,
    ISurface_get_Area_Proxy ,
    ISurface_Centroid_Proxy ,
    ISurface_PointOnSurface_Proxy ,
    IPolygon_ExteriorRing_Proxy ,
    IPolygon_get_NumInteriorRings_Proxy ,
    IPolygon_InteriorRing_Proxy
};


static const PRPC_STUB_FUNCTION IPolygon_table[] =
{
    IGeometry_get_Dimension_Stub,
    IGeometry_get_SpatialReference_Stub,
    IGeometry_putref_SpatialReference_Stub,
    IGeometry_get_IsEmpty_Stub,
    IGeometry_SetEmpty_Stub,
    IGeometry_get_IsSimple_Stub,
    IGeometry_Envelope_Stub,
    IGeometry_Clone_Stub,
    IGeometry_Project_Stub,
    IGeometry_Extent2D_Stub,
    ISurface_get_Area_Stub,
    ISurface_Centroid_Stub,
    ISurface_PointOnSurface_Stub,
    IPolygon_ExteriorRing_Stub,
    IPolygon_get_NumInteriorRings_Stub,
    IPolygon_InteriorRing_Stub
};

const CInterfaceStubVtbl _IPolygonStubVtbl =
{
    &IID_IPolygon,
    &IPolygon_ServerInfo,
    19,
    &IPolygon_table[-3],
    CStdStubBuffer_METHODS
};


/* Object interface: IMultiCurve, ver. 0.0,
   GUID={0x6A12403D,0xFE38,0x11d0,{0xBE,0xCE,0x00,0x80,0x5F,0x7C,0x42,0x68}} */

#pragma code_seg(".orpc")
static const unsigned short IMultiCurve_FormatStringOffsetTable[] =
    {
    0,
    6,
    12,
    18,
    24,
    18,
    26,
    26,
    32,
    42,
    0,
    158,
    130,
    18
    };

static const MIDL_STUBLESS_PROXY_INFO IMultiCurve_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IMultiCurve_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IMultiCurve_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IMultiCurve_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
const CINTERFACE_PROXY_VTABLE(17) _IMultiCurveProxyVtbl = 
{
    &IID_IMultiCurve,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    IGeometry_get_Dimension_Proxy ,
    IGeometry_get_SpatialReference_Proxy ,
    IGeometry_putref_SpatialReference_Proxy ,
    IGeometry_get_IsEmpty_Proxy ,
    IGeometry_SetEmpty_Proxy ,
    IGeometry_get_IsSimple_Proxy ,
    IGeometry_Envelope_Proxy ,
    IGeometry_Clone_Proxy ,
    IGeometry_Project_Proxy ,
    IGeometry_Extent2D_Proxy ,
    IGeometryCollection_get_NumGeometries_Proxy ,
    IGeometryCollection_Geometry_Proxy ,
    IMultiCurve_get_Length_Proxy ,
    IMultiCurve_get_IsClosed_Proxy
};


static const PRPC_STUB_FUNCTION IMultiCurve_table[] =
{
    IGeometry_get_Dimension_Stub,
    IGeometry_get_SpatialReference_Stub,
    IGeometry_putref_SpatialReference_Stub,
    IGeometry_get_IsEmpty_Stub,
    IGeometry_SetEmpty_Stub,
    IGeometry_get_IsSimple_Stub,
    IGeometry_Envelope_Stub,
    IGeometry_Clone_Stub,
    IGeometry_Project_Stub,
    IGeometry_Extent2D_Stub,
    IGeometryCollection_get_NumGeometries_Stub,
    IGeometryCollection_Geometry_Stub,
    IMultiCurve_get_Length_Stub,
    IMultiCurve_get_IsClosed_Stub
};

const CInterfaceStubVtbl _IMultiCurveStubVtbl =
{
    &IID_IMultiCurve,
    &IMultiCurve_ServerInfo,
    17,
    &IMultiCurve_table[-3],
    CStdStubBuffer_METHODS
};


/* Object interface: IMultiSurface, ver. 0.0,
   GUID={0x6A12403F,0xFE38,0x11d0,{0xBE,0xCE,0x00,0x80,0x5F,0x7C,0x42,0x68}} */

#pragma code_seg(".orpc")
static const unsigned short IMultiSurface_FormatStringOffsetTable[] =
    {
    0,
    6,
    12,
    18,
    24,
    18,
    26,
    26,
    32,
    42,
    0,
    158,
    130,
    136,
    136
    };

static const MIDL_STUBLESS_PROXY_INFO IMultiSurface_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IMultiSurface_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IMultiSurface_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IMultiSurface_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
const CINTERFACE_PROXY_VTABLE(18) _IMultiSurfaceProxyVtbl = 
{
    &IID_IMultiSurface,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    IGeometry_get_Dimension_Proxy ,
    IGeometry_get_SpatialReference_Proxy ,
    IGeometry_putref_SpatialReference_Proxy ,
    IGeometry_get_IsEmpty_Proxy ,
    IGeometry_SetEmpty_Proxy ,
    IGeometry_get_IsSimple_Proxy ,
    IGeometry_Envelope_Proxy ,
    IGeometry_Clone_Proxy ,
    IGeometry_Project_Proxy ,
    IGeometry_Extent2D_Proxy ,
    IGeometryCollection_get_NumGeometries_Proxy ,
    IGeometryCollection_Geometry_Proxy ,
    IMultiSurface_get_Area_Proxy ,
    IMultiSurface_Centroid_Proxy ,
    IMultiSurface_PointOnSurface_Proxy
};


static const PRPC_STUB_FUNCTION IMultiSurface_table[] =
{
    IGeometry_get_Dimension_Stub,
    IGeometry_get_SpatialReference_Stub,
    IGeometry_putref_SpatialReference_Stub,
    IGeometry_get_IsEmpty_Stub,
    IGeometry_SetEmpty_Stub,
    IGeometry_get_IsSimple_Stub,
    IGeometry_Envelope_Stub,
    IGeometry_Clone_Stub,
    IGeometry_Project_Stub,
    IGeometry_Extent2D_Stub,
    IGeometryCollection_get_NumGeometries_Stub,
    IGeometryCollection_Geometry_Stub,
    IMultiSurface_get_Area_Stub,
    IMultiSurface_Centroid_Stub,
    IMultiSurface_PointOnSurface_Stub
};

const CInterfaceStubVtbl _IMultiSurfaceStubVtbl =
{
    &IID_IMultiSurface,
    &IMultiSurface_ServerInfo,
    18,
    &IMultiSurface_table[-3],
    CStdStubBuffer_METHODS
};


/* Object interface: ISpatialRelation, ver. 0.0,
   GUID={0x6A124040,0xFE38,0x11d0,{0xBE,0xCE,0x00,0x80,0x5F,0x7C,0x42,0x68}} */

#pragma code_seg(".orpc")
static const unsigned short ISpatialRelation_FormatStringOffsetTable[] =
    {
    180,
    180,
    180,
    180,
    180,
    180,
    180,
    180
    };

static const MIDL_STUBLESS_PROXY_INFO ISpatialRelation_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &ISpatialRelation_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO ISpatialRelation_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &ISpatialRelation_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
const CINTERFACE_PROXY_VTABLE(11) _ISpatialRelationProxyVtbl = 
{
    &IID_ISpatialRelation,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    ISpatialRelation_Equals_Proxy ,
    ISpatialRelation_Touches_Proxy ,
    ISpatialRelation_Contains_Proxy ,
    ISpatialRelation_Within_Proxy ,
    ISpatialRelation_Disjoint_Proxy ,
    ISpatialRelation_Crosses_Proxy ,
    ISpatialRelation_Overlaps_Proxy ,
    ISpatialRelation_Intersects_Proxy
};


static const PRPC_STUB_FUNCTION ISpatialRelation_table[] =
{
    ISpatialRelation_Equals_Stub,
    ISpatialRelation_Touches_Stub,
    ISpatialRelation_Contains_Stub,
    ISpatialRelation_Within_Stub,
    ISpatialRelation_Disjoint_Stub,
    ISpatialRelation_Crosses_Stub,
    ISpatialRelation_Overlaps_Stub,
    ISpatialRelation_Intersects_Stub
};

const CInterfaceStubVtbl _ISpatialRelationStubVtbl =
{
    &IID_ISpatialRelation,
    &ISpatialRelation_ServerInfo,
    11,
    &ISpatialRelation_table[-3],
    CStdStubBuffer_METHODS
};


/* Object interface: ISpatialRelation2, ver. 0.0,
   GUID={0x6A124041,0xFE38,0x11d0,{0xBE,0xCE,0x00,0x80,0x5F,0x7C,0x42,0x68}} */

#pragma code_seg(".orpc")
static const unsigned short ISpatialRelation2_FormatStringOffsetTable[] =
    {
    190
    };

static const MIDL_STUBLESS_PROXY_INFO ISpatialRelation2_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &ISpatialRelation2_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO ISpatialRelation2_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &ISpatialRelation2_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
const CINTERFACE_PROXY_VTABLE(4) _ISpatialRelation2ProxyVtbl = 
{
    &IID_ISpatialRelation2,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    ISpatialRelation2_Relate_Proxy
};


static const PRPC_STUB_FUNCTION ISpatialRelation2_table[] =
{
    ISpatialRelation2_Relate_Stub
};

const CInterfaceStubVtbl _ISpatialRelation2StubVtbl =
{
    &IID_ISpatialRelation2,
    &ISpatialRelation2_ServerInfo,
    4,
    &ISpatialRelation2_table[-3],
    CStdStubBuffer_METHODS
};


/* Object interface: ISpatialOperator, ver. 0.0,
   GUID={0x6A124042,0xFE38,0x11d0,{0xBE,0xCE,0x00,0x80,0x5F,0x7C,0x42,0x68}} */

#pragma code_seg(".orpc")
static const unsigned short ISpatialOperator_FormatStringOffsetTable[] =
    {
    204,
    26,
    214,
    26,
    222,
    222,
    222,
    222
    };

static const MIDL_STUBLESS_PROXY_INFO ISpatialOperator_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &ISpatialOperator_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO ISpatialOperator_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &ISpatialOperator_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
const CINTERFACE_PROXY_VTABLE(11) _ISpatialOperatorProxyVtbl = 
{
    &IID_ISpatialOperator,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    ISpatialOperator_Distance_Proxy ,
    ISpatialOperator_Boundary_Proxy ,
    ISpatialOperator_Buffer_Proxy ,
    ISpatialOperator_ConvexHull_Proxy ,
    ISpatialOperator_Intersection_Proxy ,
    ISpatialOperator_Union_Proxy ,
    ISpatialOperator_Difference_Proxy ,
    ISpatialOperator_SymmetricDifference_Proxy
};


static const PRPC_STUB_FUNCTION ISpatialOperator_table[] =
{
    ISpatialOperator_Distance_Stub,
    ISpatialOperator_Boundary_Stub,
    ISpatialOperator_Buffer_Stub,
    ISpatialOperator_ConvexHull_Stub,
    ISpatialOperator_Intersection_Stub,
    ISpatialOperator_Union_Stub,
    ISpatialOperator_Difference_Stub,
    ISpatialOperator_SymmetricDifference_Stub
};

const CInterfaceStubVtbl _ISpatialOperatorStubVtbl =
{
    &IID_ISpatialOperator,
    &ISpatialOperator_ServerInfo,
    11,
    &ISpatialOperator_table[-3],
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

const CInterfaceProxyVtbl * _GeometryIdl_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_IPointZProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IGeometryProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IWksProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IGeometryFactoryProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IPointProxyVtbl,
    ( CInterfaceProxyVtbl *) &_ICurveProxyVtbl,
    ( CInterfaceProxyVtbl *) &_ILineStringProxyVtbl,
    ( CInterfaceProxyVtbl *) &_ILinearRingProxyVtbl,
    ( CInterfaceProxyVtbl *) &_ISurfaceProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IGeometryCollectionProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IPolygonProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IMultiCurveProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IMultiSurfaceProxyVtbl,
    ( CInterfaceProxyVtbl *) &_ISpatialRelationProxyVtbl,
    ( CInterfaceProxyVtbl *) &_ISpatialRelation2ProxyVtbl,
    ( CInterfaceProxyVtbl *) &_ISpatialOperatorProxyVtbl,
    0
};

const CInterfaceStubVtbl * _GeometryIdl_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_IPointZStubVtbl,
    ( CInterfaceStubVtbl *) &_IGeometryStubVtbl,
    ( CInterfaceStubVtbl *) &_IWksStubVtbl,
    ( CInterfaceStubVtbl *) &_IGeometryFactoryStubVtbl,
    ( CInterfaceStubVtbl *) &_IPointStubVtbl,
    ( CInterfaceStubVtbl *) &_ICurveStubVtbl,
    ( CInterfaceStubVtbl *) &_ILineStringStubVtbl,
    ( CInterfaceStubVtbl *) &_ILinearRingStubVtbl,
    ( CInterfaceStubVtbl *) &_ISurfaceStubVtbl,
    ( CInterfaceStubVtbl *) &_IGeometryCollectionStubVtbl,
    ( CInterfaceStubVtbl *) &_IPolygonStubVtbl,
    ( CInterfaceStubVtbl *) &_IMultiCurveStubVtbl,
    ( CInterfaceStubVtbl *) &_IMultiSurfaceStubVtbl,
    ( CInterfaceStubVtbl *) &_ISpatialRelationStubVtbl,
    ( CInterfaceStubVtbl *) &_ISpatialRelation2StubVtbl,
    ( CInterfaceStubVtbl *) &_ISpatialOperatorStubVtbl,
    0
};

PCInterfaceName const _GeometryIdl_InterfaceNamesList[] = 
{
    "IPointZ",
    "IGeometry",
    "IWks",
    "IGeometryFactory",
    "IPoint",
    "ICurve",
    "ILineString",
    "ILinearRing",
    "ISurface",
    "IGeometryCollection",
    "IPolygon",
    "IMultiCurve",
    "IMultiSurface",
    "ISpatialRelation",
    "ISpatialRelation2",
    "ISpatialOperator",
    0
};


#define _GeometryIdl_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _GeometryIdl, pIID, n)

int __stdcall _GeometryIdl_IID_Lookup( const IID * pIID, int * pIndex )
{
    IID_BS_LOOKUP_SETUP

    IID_BS_LOOKUP_INITIAL_TEST( _GeometryIdl, 16, 8 )
    IID_BS_LOOKUP_NEXT_TEST( _GeometryIdl, 4 )
    IID_BS_LOOKUP_NEXT_TEST( _GeometryIdl, 2 )
    IID_BS_LOOKUP_NEXT_TEST( _GeometryIdl, 1 )
    IID_BS_LOOKUP_RETURN_RESULT( _GeometryIdl, 16, *pIndex )
    
}

const ExtendedProxyFileInfo GeometryIdl_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _GeometryIdl_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _GeometryIdl_StubVtblList,
    (const PCInterfaceName * ) & _GeometryIdl_InterfaceNamesList,
    0, // no delegation
    & _GeometryIdl_IID_Lookup, 
    16,
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
/* at Thu Jan 17 12:57:25 2002
 */
/* Compiler settings for GeometryIdl.idl:
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


#include "GeometryIdl.h"

#define TYPE_FORMAT_STRING_SIZE   1095                              
#define PROC_FORMAT_STRING_SIZE   2119                              
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   2            

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


extern const MIDL_SERVER_INFO IGeometry_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IGeometry_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IWks_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IWks_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IGeometryFactory_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IGeometryFactory_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IPoint_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IPoint_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IPointZ_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IPointZ_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO ICurve_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO ICurve_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO ILineString_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO ILineString_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO ILinearRing_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO ILinearRing_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO ISurface_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO ISurface_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IGeometryCollection_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IGeometryCollection_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IPolygon_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IPolygon_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IMultiCurve_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IMultiCurve_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IMultiSurface_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IMultiSurface_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO ISpatialRelation_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO ISpatialRelation_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO ISpatialRelation2_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO ISpatialRelation2_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO ISpatialOperator_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO ISpatialOperator_ProxyInfo;


extern const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ];

#if !defined(__RPC_WIN64__)
#error  Invalid build platform for this stub.
#endif

static const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure get_Dimension */

			0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/*  2 */	NdrFcLong( 0x0 ),	/* 0 */
/*  6 */	NdrFcShort( 0x3 ),	/* 3 */
/*  8 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 10 */	NdrFcShort( 0x0 ),	/* 0 */
/* 12 */	NdrFcShort( 0x24 ),	/* 36 */
/* 14 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 16 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 18 */	NdrFcShort( 0x0 ),	/* 0 */
/* 20 */	NdrFcShort( 0x0 ),	/* 0 */
/* 22 */	NdrFcShort( 0x0 ),	/* 0 */
/* 24 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter dimension */

/* 26 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 28 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 30 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 32 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 34 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 36 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_SpatialReference */

/* 38 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 40 */	NdrFcLong( 0x0 ),	/* 0 */
/* 44 */	NdrFcShort( 0x4 ),	/* 4 */
/* 46 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 48 */	NdrFcShort( 0x0 ),	/* 0 */
/* 50 */	NdrFcShort( 0x8 ),	/* 8 */
/* 52 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 54 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 56 */	NdrFcShort( 0x0 ),	/* 0 */
/* 58 */	NdrFcShort( 0x0 ),	/* 0 */
/* 60 */	NdrFcShort( 0x0 ),	/* 0 */
/* 62 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter spatialRef */

/* 64 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 66 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 68 */	NdrFcShort( 0x6 ),	/* Type Offset=6 */

	/* Return value */

/* 70 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 72 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 74 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure putref_SpatialReference */

/* 76 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 78 */	NdrFcLong( 0x0 ),	/* 0 */
/* 82 */	NdrFcShort( 0x5 ),	/* 5 */
/* 84 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 86 */	NdrFcShort( 0x0 ),	/* 0 */
/* 88 */	NdrFcShort( 0x8 ),	/* 8 */
/* 90 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 92 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 94 */	NdrFcShort( 0x0 ),	/* 0 */
/* 96 */	NdrFcShort( 0x0 ),	/* 0 */
/* 98 */	NdrFcShort( 0x0 ),	/* 0 */
/* 100 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter spatialRef */

/* 102 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 104 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 106 */	NdrFcShort( 0xa ),	/* Type Offset=10 */

	/* Return value */

/* 108 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 110 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 112 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_IsEmpty */

/* 114 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 116 */	NdrFcLong( 0x0 ),	/* 0 */
/* 120 */	NdrFcShort( 0x6 ),	/* 6 */
/* 122 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 124 */	NdrFcShort( 0x0 ),	/* 0 */
/* 126 */	NdrFcShort( 0x22 ),	/* 34 */
/* 128 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 130 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 132 */	NdrFcShort( 0x0 ),	/* 0 */
/* 134 */	NdrFcShort( 0x0 ),	/* 0 */
/* 136 */	NdrFcShort( 0x0 ),	/* 0 */
/* 138 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter isEmpty */

/* 140 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 142 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 144 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 146 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 148 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 150 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetEmpty */

/* 152 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 154 */	NdrFcLong( 0x0 ),	/* 0 */
/* 158 */	NdrFcShort( 0x7 ),	/* 7 */
/* 160 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 162 */	NdrFcShort( 0x0 ),	/* 0 */
/* 164 */	NdrFcShort( 0x8 ),	/* 8 */
/* 166 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 168 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 170 */	NdrFcShort( 0x0 ),	/* 0 */
/* 172 */	NdrFcShort( 0x0 ),	/* 0 */
/* 174 */	NdrFcShort( 0x0 ),	/* 0 */
/* 176 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 178 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 180 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 182 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_IsSimple */

/* 184 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 186 */	NdrFcLong( 0x0 ),	/* 0 */
/* 190 */	NdrFcShort( 0x8 ),	/* 8 */
/* 192 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 194 */	NdrFcShort( 0x0 ),	/* 0 */
/* 196 */	NdrFcShort( 0x22 ),	/* 34 */
/* 198 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 200 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 202 */	NdrFcShort( 0x0 ),	/* 0 */
/* 204 */	NdrFcShort( 0x0 ),	/* 0 */
/* 206 */	NdrFcShort( 0x0 ),	/* 0 */
/* 208 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter isSimple */

/* 210 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 212 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 214 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 216 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 218 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 220 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Envelope */

/* 222 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 224 */	NdrFcLong( 0x0 ),	/* 0 */
/* 228 */	NdrFcShort( 0x9 ),	/* 9 */
/* 230 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 232 */	NdrFcShort( 0x0 ),	/* 0 */
/* 234 */	NdrFcShort( 0x8 ),	/* 8 */
/* 236 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 238 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 240 */	NdrFcShort( 0x0 ),	/* 0 */
/* 242 */	NdrFcShort( 0x0 ),	/* 0 */
/* 244 */	NdrFcShort( 0x0 ),	/* 0 */
/* 246 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter envelope */

/* 248 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 250 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 252 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 254 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 256 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 258 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Clone */

/* 260 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 262 */	NdrFcLong( 0x0 ),	/* 0 */
/* 266 */	NdrFcShort( 0xa ),	/* 10 */
/* 268 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 270 */	NdrFcShort( 0x0 ),	/* 0 */
/* 272 */	NdrFcShort( 0x8 ),	/* 8 */
/* 274 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 276 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 278 */	NdrFcShort( 0x0 ),	/* 0 */
/* 280 */	NdrFcShort( 0x0 ),	/* 0 */
/* 282 */	NdrFcShort( 0x0 ),	/* 0 */
/* 284 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newShape */

/* 286 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 288 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 290 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 292 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 294 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 296 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Project */

/* 298 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 300 */	NdrFcLong( 0x0 ),	/* 0 */
/* 304 */	NdrFcShort( 0xb ),	/* 11 */
/* 306 */	NdrFcShort( 0x20 ),	/* ia64 Stack size/offset = 32 */
/* 308 */	NdrFcShort( 0x0 ),	/* 0 */
/* 310 */	NdrFcShort( 0x8 ),	/* 8 */
/* 312 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 314 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 316 */	NdrFcShort( 0x0 ),	/* 0 */
/* 318 */	NdrFcShort( 0x0 ),	/* 0 */
/* 320 */	NdrFcShort( 0x0 ),	/* 0 */
/* 322 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newSystem */

/* 324 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 326 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 328 */	NdrFcShort( 0xa ),	/* Type Offset=10 */

	/* Parameter result */

/* 330 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 332 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 334 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 336 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 338 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 340 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Extent2D */

/* 342 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 344 */	NdrFcLong( 0x0 ),	/* 0 */
/* 348 */	NdrFcShort( 0xc ),	/* 12 */
/* 350 */	NdrFcShort( 0x30 ),	/* ia64 Stack size/offset = 48 */
/* 352 */	NdrFcShort( 0x0 ),	/* 0 */
/* 354 */	NdrFcShort( 0x98 ),	/* 152 */
/* 356 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x5,		/* 5 */
/* 358 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 360 */	NdrFcShort( 0x0 ),	/* 0 */
/* 362 */	NdrFcShort( 0x0 ),	/* 0 */
/* 364 */	NdrFcShort( 0x0 ),	/* 0 */
/* 366 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter minX */

/* 368 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 370 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 372 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Parameter minY */

/* 374 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 376 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 378 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Parameter maxX */

/* 380 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 382 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 384 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Parameter maxY */

/* 386 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 388 */	NdrFcShort( 0x20 ),	/* ia64 Stack size/offset = 32 */
/* 390 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 392 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 394 */	NdrFcShort( 0x28 ),	/* ia64 Stack size/offset = 40 */
/* 396 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ExportToWKB */

/* 398 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 400 */	NdrFcLong( 0x0 ),	/* 0 */
/* 404 */	NdrFcShort( 0x3 ),	/* 3 */
/* 406 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 408 */	NdrFcShort( 0x0 ),	/* 0 */
/* 410 */	NdrFcShort( 0x8 ),	/* 8 */
/* 412 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 414 */	0xa,		/* 10 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 416 */	NdrFcShort( 0x20 ),	/* 32 */
/* 418 */	NdrFcShort( 0x0 ),	/* 0 */
/* 420 */	NdrFcShort( 0x0 ),	/* 0 */
/* 422 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter wkb */

/* 424 */	NdrFcShort( 0x6113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=24 */
/* 426 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 428 */	NdrFcShort( 0x3e6 ),	/* Type Offset=998 */

	/* Return value */

/* 430 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 432 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 434 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ExportToWKT */

/* 436 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 438 */	NdrFcLong( 0x0 ),	/* 0 */
/* 442 */	NdrFcShort( 0x4 ),	/* 4 */
/* 444 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 446 */	NdrFcShort( 0x0 ),	/* 0 */
/* 448 */	NdrFcShort( 0x8 ),	/* 8 */
/* 450 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 452 */	0xa,		/* 10 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 454 */	NdrFcShort( 0x1 ),	/* 1 */
/* 456 */	NdrFcShort( 0x0 ),	/* 0 */
/* 458 */	NdrFcShort( 0x0 ),	/* 0 */
/* 460 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter wkt */

/* 462 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 464 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 466 */	NdrFcShort( 0x3f4 ),	/* Type Offset=1012 */

	/* Return value */

/* 468 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 470 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 472 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ImportFromWKB */

/* 474 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 476 */	NdrFcLong( 0x0 ),	/* 0 */
/* 480 */	NdrFcShort( 0x5 ),	/* 5 */
/* 482 */	NdrFcShort( 0x30 ),	/* ia64 Stack size/offset = 48 */
/* 484 */	NdrFcShort( 0x0 ),	/* 0 */
/* 486 */	NdrFcShort( 0x8 ),	/* 8 */
/* 488 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 490 */	0xa,		/* 10 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 492 */	NdrFcShort( 0x0 ),	/* 0 */
/* 494 */	NdrFcShort( 0x20 ),	/* 32 */
/* 496 */	NdrFcShort( 0x0 ),	/* 0 */
/* 498 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter wkb */

/* 500 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 502 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 504 */	NdrFcShort( 0x402 ),	/* Type Offset=1026 */

	/* Parameter spatialRef */

/* 506 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 508 */	NdrFcShort( 0x20 ),	/* ia64 Stack size/offset = 32 */
/* 510 */	NdrFcShort( 0xa ),	/* Type Offset=10 */

	/* Return value */

/* 512 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 514 */	NdrFcShort( 0x28 ),	/* ia64 Stack size/offset = 40 */
/* 516 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ImportFromWKT */

/* 518 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 520 */	NdrFcLong( 0x0 ),	/* 0 */
/* 524 */	NdrFcShort( 0x6 ),	/* 6 */
/* 526 */	NdrFcShort( 0x20 ),	/* ia64 Stack size/offset = 32 */
/* 528 */	NdrFcShort( 0x0 ),	/* 0 */
/* 530 */	NdrFcShort( 0x8 ),	/* 8 */
/* 532 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 534 */	0xa,		/* 10 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 536 */	NdrFcShort( 0x0 ),	/* 0 */
/* 538 */	NdrFcShort( 0x1 ),	/* 1 */
/* 540 */	NdrFcShort( 0x0 ),	/* 0 */
/* 542 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter wkt */

/* 544 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 546 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 548 */	NdrFcShort( 0x410 ),	/* Type Offset=1040 */

	/* Parameter spatialRef */

/* 550 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 552 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 554 */	NdrFcShort( 0xa ),	/* Type Offset=10 */

	/* Return value */

/* 556 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 558 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 560 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure CreateFromWKB */

/* 562 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 564 */	NdrFcLong( 0x0 ),	/* 0 */
/* 568 */	NdrFcShort( 0x3 ),	/* 3 */
/* 570 */	NdrFcShort( 0x38 ),	/* ia64 Stack size/offset = 56 */
/* 572 */	NdrFcShort( 0x0 ),	/* 0 */
/* 574 */	NdrFcShort( 0x8 ),	/* 8 */
/* 576 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 578 */	0xa,		/* 10 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 580 */	NdrFcShort( 0x0 ),	/* 0 */
/* 582 */	NdrFcShort( 0x20 ),	/* 32 */
/* 584 */	NdrFcShort( 0x0 ),	/* 0 */
/* 586 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter wkb */

/* 588 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 590 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 592 */	NdrFcShort( 0x402 ),	/* Type Offset=1026 */

	/* Parameter spatialRef */

/* 594 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 596 */	NdrFcShort( 0x20 ),	/* ia64 Stack size/offset = 32 */
/* 598 */	NdrFcShort( 0xa ),	/* Type Offset=10 */

	/* Parameter geometry */

/* 600 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 602 */	NdrFcShort( 0x28 ),	/* ia64 Stack size/offset = 40 */
/* 604 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 606 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 608 */	NdrFcShort( 0x30 ),	/* ia64 Stack size/offset = 48 */
/* 610 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure CreateFromWKT */

/* 612 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 614 */	NdrFcLong( 0x0 ),	/* 0 */
/* 618 */	NdrFcShort( 0x4 ),	/* 4 */
/* 620 */	NdrFcShort( 0x28 ),	/* ia64 Stack size/offset = 40 */
/* 622 */	NdrFcShort( 0x0 ),	/* 0 */
/* 624 */	NdrFcShort( 0x8 ),	/* 8 */
/* 626 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 628 */	0xa,		/* 10 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 630 */	NdrFcShort( 0x0 ),	/* 0 */
/* 632 */	NdrFcShort( 0x1 ),	/* 1 */
/* 634 */	NdrFcShort( 0x0 ),	/* 0 */
/* 636 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter wkt */

/* 638 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 640 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 642 */	NdrFcShort( 0x410 ),	/* Type Offset=1040 */

	/* Parameter spatialRef */

/* 644 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 646 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 648 */	NdrFcShort( 0xa ),	/* Type Offset=10 */

	/* Parameter geometry */

/* 650 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 652 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 654 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 656 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 658 */	NdrFcShort( 0x20 ),	/* ia64 Stack size/offset = 32 */
/* 660 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Coords */

/* 662 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 664 */	NdrFcLong( 0x0 ),	/* 0 */
/* 668 */	NdrFcShort( 0xd ),	/* 13 */
/* 670 */	NdrFcShort( 0x20 ),	/* ia64 Stack size/offset = 32 */
/* 672 */	NdrFcShort( 0x0 ),	/* 0 */
/* 674 */	NdrFcShort( 0x50 ),	/* 80 */
/* 676 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 678 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 680 */	NdrFcShort( 0x0 ),	/* 0 */
/* 682 */	NdrFcShort( 0x0 ),	/* 0 */
/* 684 */	NdrFcShort( 0x0 ),	/* 0 */
/* 686 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter x */

/* 688 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 690 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 692 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Parameter y */

/* 694 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 696 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 698 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 700 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 702 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 704 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_X */

/* 706 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 708 */	NdrFcLong( 0x0 ),	/* 0 */
/* 712 */	NdrFcShort( 0xe ),	/* 14 */
/* 714 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 716 */	NdrFcShort( 0x0 ),	/* 0 */
/* 718 */	NdrFcShort( 0x2c ),	/* 44 */
/* 720 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 722 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 724 */	NdrFcShort( 0x0 ),	/* 0 */
/* 726 */	NdrFcShort( 0x0 ),	/* 0 */
/* 728 */	NdrFcShort( 0x0 ),	/* 0 */
/* 730 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter x */

/* 732 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 734 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 736 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 738 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 740 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 742 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Area */


	/* Procedure get_Length */


	/* Procedure get_Y */

/* 744 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 746 */	NdrFcLong( 0x0 ),	/* 0 */
/* 750 */	NdrFcShort( 0xf ),	/* 15 */
/* 752 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 754 */	NdrFcShort( 0x0 ),	/* 0 */
/* 756 */	NdrFcShort( 0x2c ),	/* 44 */
/* 758 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 760 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 762 */	NdrFcShort( 0x0 ),	/* 0 */
/* 764 */	NdrFcShort( 0x0 ),	/* 0 */
/* 766 */	NdrFcShort( 0x0 ),	/* 0 */
/* 768 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter area */


	/* Parameter length */


	/* Parameter y */

/* 770 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 772 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 774 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */


	/* Return value */

/* 776 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 778 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 780 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Z */

/* 782 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 784 */	NdrFcLong( 0x0 ),	/* 0 */
/* 788 */	NdrFcShort( 0x10 ),	/* 16 */
/* 790 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 792 */	NdrFcShort( 0x0 ),	/* 0 */
/* 794 */	NdrFcShort( 0x2c ),	/* 44 */
/* 796 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 798 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 800 */	NdrFcShort( 0x0 ),	/* 0 */
/* 802 */	NdrFcShort( 0x0 ),	/* 0 */
/* 804 */	NdrFcShort( 0x0 ),	/* 0 */
/* 806 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter z */

/* 808 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 810 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 812 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 814 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 816 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 818 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Area */


	/* Procedure get_Length */

/* 820 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 822 */	NdrFcLong( 0x0 ),	/* 0 */
/* 826 */	NdrFcShort( 0xd ),	/* 13 */
/* 828 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 830 */	NdrFcShort( 0x0 ),	/* 0 */
/* 832 */	NdrFcShort( 0x2c ),	/* 44 */
/* 834 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 836 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 838 */	NdrFcShort( 0x0 ),	/* 0 */
/* 840 */	NdrFcShort( 0x0 ),	/* 0 */
/* 842 */	NdrFcShort( 0x0 ),	/* 0 */
/* 844 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter area */


	/* Parameter value */

/* 846 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 848 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 850 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */

/* 852 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 854 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 856 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Centroid */


	/* Procedure StartPoint */

/* 858 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 860 */	NdrFcLong( 0x0 ),	/* 0 */
/* 864 */	NdrFcShort( 0xe ),	/* 14 */
/* 866 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 868 */	NdrFcShort( 0x0 ),	/* 0 */
/* 870 */	NdrFcShort( 0x8 ),	/* 8 */
/* 872 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 874 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 876 */	NdrFcShort( 0x0 ),	/* 0 */
/* 878 */	NdrFcShort( 0x0 ),	/* 0 */
/* 880 */	NdrFcShort( 0x0 ),	/* 0 */
/* 882 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter result */


	/* Parameter sp */

/* 884 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 886 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 888 */	NdrFcShort( 0x41a ),	/* Type Offset=1050 */

	/* Return value */


	/* Return value */

/* 890 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 892 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 894 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure PointOnSurface */


	/* Procedure EndPoint */

/* 896 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 898 */	NdrFcLong( 0x0 ),	/* 0 */
/* 902 */	NdrFcShort( 0xf ),	/* 15 */
/* 904 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 906 */	NdrFcShort( 0x0 ),	/* 0 */
/* 908 */	NdrFcShort( 0x8 ),	/* 8 */
/* 910 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 912 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 914 */	NdrFcShort( 0x0 ),	/* 0 */
/* 916 */	NdrFcShort( 0x0 ),	/* 0 */
/* 918 */	NdrFcShort( 0x0 ),	/* 0 */
/* 920 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter result */


	/* Parameter ep */

/* 922 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 924 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 926 */	NdrFcShort( 0x41a ),	/* Type Offset=1050 */

	/* Return value */


	/* Return value */

/* 928 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 930 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 932 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_IsClosed */


	/* Procedure get_IsClosed */

/* 934 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 936 */	NdrFcLong( 0x0 ),	/* 0 */
/* 940 */	NdrFcShort( 0x10 ),	/* 16 */
/* 942 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 944 */	NdrFcShort( 0x0 ),	/* 0 */
/* 946 */	NdrFcShort( 0x22 ),	/* 34 */
/* 948 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 950 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 952 */	NdrFcShort( 0x0 ),	/* 0 */
/* 954 */	NdrFcShort( 0x0 ),	/* 0 */
/* 956 */	NdrFcShort( 0x0 ),	/* 0 */
/* 958 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter isClosed */


	/* Parameter isClosed */

/* 960 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 962 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 964 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */

/* 966 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 968 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 970 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Value */

/* 972 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 974 */	NdrFcLong( 0x0 ),	/* 0 */
/* 978 */	NdrFcShort( 0x11 ),	/* 17 */
/* 980 */	NdrFcShort( 0x20 ),	/* ia64 Stack size/offset = 32 */
/* 982 */	NdrFcShort( 0x10 ),	/* 16 */
/* 984 */	NdrFcShort( 0x8 ),	/* 8 */
/* 986 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 988 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 990 */	NdrFcShort( 0x0 ),	/* 0 */
/* 992 */	NdrFcShort( 0x0 ),	/* 0 */
/* 994 */	NdrFcShort( 0x0 ),	/* 0 */
/* 996 */	NdrFcShort( 0x8 ),	/* 8 */

	/* Parameter t */

/* 998 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1000 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 1002 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Parameter p */

/* 1004 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 1006 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 1008 */	NdrFcShort( 0x41a ),	/* Type Offset=1050 */

	/* Return value */

/* 1010 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1012 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 1014 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_NumPoints */

/* 1016 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1018 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1022 */	NdrFcShort( 0x12 ),	/* 18 */
/* 1024 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 1026 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1028 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1030 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 1032 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1034 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1036 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1038 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1040 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter numPoints */

/* 1042 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1044 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 1046 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1048 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1050 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 1052 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Point */

/* 1054 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1056 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1060 */	NdrFcShort( 0x13 ),	/* 19 */
/* 1062 */	NdrFcShort( 0x20 ),	/* ia64 Stack size/offset = 32 */
/* 1064 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1066 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1068 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 1070 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1072 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1074 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1076 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1078 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter index */

/* 1080 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1082 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 1084 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter point */

/* 1086 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 1088 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 1090 */	NdrFcShort( 0x41a ),	/* Type Offset=1050 */

	/* Return value */

/* 1092 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1094 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 1096 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_NumGeometries */

/* 1098 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1100 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1104 */	NdrFcShort( 0xd ),	/* 13 */
/* 1106 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 1108 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1110 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1112 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 1114 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1116 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1118 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1120 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1122 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter numberOf */

/* 1124 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1126 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 1128 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1130 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1132 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 1134 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Geometry */

/* 1136 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1138 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1142 */	NdrFcShort( 0xe ),	/* 14 */
/* 1144 */	NdrFcShort( 0x20 ),	/* ia64 Stack size/offset = 32 */
/* 1146 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1148 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1150 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 1152 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1154 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1156 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1158 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1160 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter index */

/* 1162 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1164 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 1166 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter geometry */

/* 1168 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 1170 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 1172 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 1174 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1176 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 1178 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ExteriorRing */

/* 1180 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1182 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1186 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1188 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 1190 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1192 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1194 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 1196 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1198 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1200 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1202 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1204 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter exteriorRing */

/* 1206 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 1208 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 1210 */	NdrFcShort( 0x430 ),	/* Type Offset=1072 */

	/* Return value */

/* 1212 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1214 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 1216 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_NumInteriorRings */

/* 1218 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1220 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1224 */	NdrFcShort( 0x11 ),	/* 17 */
/* 1226 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 1228 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1230 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1232 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 1234 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1236 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1238 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1240 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1242 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter count */

/* 1244 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1246 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 1248 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1250 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1252 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 1254 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure InteriorRing */

/* 1256 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1258 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1262 */	NdrFcShort( 0x12 ),	/* 18 */
/* 1264 */	NdrFcShort( 0x20 ),	/* ia64 Stack size/offset = 32 */
/* 1266 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1268 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1270 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 1272 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1274 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1276 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1278 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1280 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter index */

/* 1282 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1284 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 1286 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter interiorRing */

/* 1288 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 1290 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 1292 */	NdrFcShort( 0x430 ),	/* Type Offset=1072 */

	/* Return value */

/* 1294 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1296 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 1298 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Centroid */

/* 1300 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1302 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1306 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1308 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 1310 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1312 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1314 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 1316 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1318 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1320 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1322 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1324 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter result */

/* 1326 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 1328 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 1330 */	NdrFcShort( 0x41a ),	/* Type Offset=1050 */

	/* Return value */

/* 1332 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1334 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 1336 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure PointOnSurface */

/* 1338 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1340 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1344 */	NdrFcShort( 0x11 ),	/* 17 */
/* 1346 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 1348 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1350 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1352 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 1354 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1356 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1358 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1360 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1362 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter result */

/* 1364 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 1366 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 1368 */	NdrFcShort( 0x41a ),	/* Type Offset=1050 */

	/* Return value */

/* 1370 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1372 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 1374 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Equals */

/* 1376 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1378 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1382 */	NdrFcShort( 0x3 ),	/* 3 */
/* 1384 */	NdrFcShort( 0x20 ),	/* ia64 Stack size/offset = 32 */
/* 1386 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1388 */	NdrFcShort( 0x22 ),	/* 34 */
/* 1390 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 1392 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1394 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1396 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1398 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1400 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter other */

/* 1402 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 1404 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 1406 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */

	/* Parameter equals */

/* 1408 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1410 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 1412 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 1414 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1416 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 1418 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Touches */

/* 1420 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1422 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1426 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1428 */	NdrFcShort( 0x20 ),	/* ia64 Stack size/offset = 32 */
/* 1430 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1432 */	NdrFcShort( 0x22 ),	/* 34 */
/* 1434 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 1436 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1438 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1440 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1442 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1444 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter other */

/* 1446 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 1448 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 1450 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */

	/* Parameter touches */

/* 1452 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1454 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 1456 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 1458 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1460 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 1462 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Contains */

/* 1464 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1466 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1470 */	NdrFcShort( 0x5 ),	/* 5 */
/* 1472 */	NdrFcShort( 0x20 ),	/* ia64 Stack size/offset = 32 */
/* 1474 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1476 */	NdrFcShort( 0x22 ),	/* 34 */
/* 1478 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 1480 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1482 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1484 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1486 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1488 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter other */

/* 1490 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 1492 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 1494 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */

	/* Parameter contains */

/* 1496 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1498 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 1500 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 1502 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1504 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 1506 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Within */

/* 1508 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1510 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1514 */	NdrFcShort( 0x6 ),	/* 6 */
/* 1516 */	NdrFcShort( 0x20 ),	/* ia64 Stack size/offset = 32 */
/* 1518 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1520 */	NdrFcShort( 0x22 ),	/* 34 */
/* 1522 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 1524 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1526 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1528 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1530 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1532 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter other */

/* 1534 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 1536 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 1538 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */

	/* Parameter within */

/* 1540 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1542 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 1544 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 1546 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1548 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 1550 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Disjoint */

/* 1552 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1554 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1558 */	NdrFcShort( 0x7 ),	/* 7 */
/* 1560 */	NdrFcShort( 0x20 ),	/* ia64 Stack size/offset = 32 */
/* 1562 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1564 */	NdrFcShort( 0x22 ),	/* 34 */
/* 1566 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 1568 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1570 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1572 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1574 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1576 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter other */

/* 1578 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 1580 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 1582 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */

	/* Parameter disjoint */

/* 1584 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1586 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 1588 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 1590 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1592 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 1594 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Crosses */

/* 1596 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1598 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1602 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1604 */	NdrFcShort( 0x20 ),	/* ia64 Stack size/offset = 32 */
/* 1606 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1608 */	NdrFcShort( 0x22 ),	/* 34 */
/* 1610 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 1612 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1614 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1616 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1618 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1620 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter other */

/* 1622 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 1624 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 1626 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */

	/* Parameter crosses */

/* 1628 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1630 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 1632 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 1634 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1636 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 1638 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Overlaps */

/* 1640 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1642 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1646 */	NdrFcShort( 0x9 ),	/* 9 */
/* 1648 */	NdrFcShort( 0x20 ),	/* ia64 Stack size/offset = 32 */
/* 1650 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1652 */	NdrFcShort( 0x22 ),	/* 34 */
/* 1654 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 1656 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1658 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1660 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1662 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1664 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter other */

/* 1666 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 1668 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 1670 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */

	/* Parameter overlaps */

/* 1672 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1674 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 1676 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 1678 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1680 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 1682 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Intersects */

/* 1684 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1686 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1690 */	NdrFcShort( 0xa ),	/* 10 */
/* 1692 */	NdrFcShort( 0x20 ),	/* ia64 Stack size/offset = 32 */
/* 1694 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1696 */	NdrFcShort( 0x22 ),	/* 34 */
/* 1698 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 1700 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1702 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1704 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1706 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1708 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter other */

/* 1710 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 1712 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 1714 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */

	/* Parameter overlaps */

/* 1716 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1718 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 1720 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 1722 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1724 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 1726 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Relate */

/* 1728 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1730 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1734 */	NdrFcShort( 0x3 ),	/* 3 */
/* 1736 */	NdrFcShort( 0x28 ),	/* ia64 Stack size/offset = 40 */
/* 1738 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1740 */	NdrFcShort( 0x22 ),	/* 34 */
/* 1742 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 1744 */	0xa,		/* 10 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 1746 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1748 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1750 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1752 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter other */

/* 1754 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 1756 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 1758 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */

	/* Parameter patternMatrix */

/* 1760 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1762 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 1764 */	NdrFcShort( 0x410 ),	/* Type Offset=1040 */

	/* Parameter isRelated */

/* 1766 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1768 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 1770 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 1772 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1774 */	NdrFcShort( 0x20 ),	/* ia64 Stack size/offset = 32 */
/* 1776 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Distance */

/* 1778 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1780 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1784 */	NdrFcShort( 0x3 ),	/* 3 */
/* 1786 */	NdrFcShort( 0x20 ),	/* ia64 Stack size/offset = 32 */
/* 1788 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1790 */	NdrFcShort( 0x2c ),	/* 44 */
/* 1792 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 1794 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1796 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1798 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1800 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1802 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter other */

/* 1804 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 1806 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 1808 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */

	/* Parameter distance */

/* 1810 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1812 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 1814 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 1816 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1818 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 1820 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Boundary */

/* 1822 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1824 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1828 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1830 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 1832 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1834 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1836 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 1838 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1840 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1842 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1844 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1846 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter boundary */

/* 1848 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 1850 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 1852 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 1854 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1856 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 1858 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Buffer */

/* 1860 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1862 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1866 */	NdrFcShort( 0x5 ),	/* 5 */
/* 1868 */	NdrFcShort( 0x20 ),	/* ia64 Stack size/offset = 32 */
/* 1870 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1872 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1874 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 1876 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1878 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1880 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1882 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1884 */	NdrFcShort( 0x8 ),	/* 8 */

	/* Parameter distance */

/* 1886 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1888 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 1890 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Parameter result */

/* 1892 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 1894 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 1896 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 1898 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1900 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 1902 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ConvexHull */

/* 1904 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1906 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1910 */	NdrFcShort( 0x6 ),	/* 6 */
/* 1912 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 1914 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1916 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1918 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 1920 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1922 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1924 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1926 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1928 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter result */

/* 1930 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 1932 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 1934 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 1936 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1938 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 1940 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Intersection */

/* 1942 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1944 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1948 */	NdrFcShort( 0x7 ),	/* 7 */
/* 1950 */	NdrFcShort( 0x20 ),	/* ia64 Stack size/offset = 32 */
/* 1952 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1954 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1956 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 1958 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1960 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1962 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1964 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1966 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter other */

/* 1968 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 1970 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 1972 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */

	/* Parameter result */

/* 1974 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 1976 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 1978 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 1980 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1982 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 1984 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Union */

/* 1986 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1988 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1992 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1994 */	NdrFcShort( 0x20 ),	/* ia64 Stack size/offset = 32 */
/* 1996 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1998 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2000 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 2002 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2004 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2006 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2008 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2010 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter other */

/* 2012 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 2014 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 2016 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */

	/* Parameter result */

/* 2018 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 2020 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 2022 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 2024 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2026 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 2028 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Difference */

/* 2030 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2032 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2036 */	NdrFcShort( 0x9 ),	/* 9 */
/* 2038 */	NdrFcShort( 0x20 ),	/* ia64 Stack size/offset = 32 */
/* 2040 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2042 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2044 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 2046 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2048 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2050 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2052 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2054 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter other */

/* 2056 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 2058 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 2060 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */

	/* Parameter result */

/* 2062 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 2064 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 2066 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 2068 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2070 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 2072 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SymmetricDifference */

/* 2074 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2076 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2080 */	NdrFcShort( 0xa ),	/* 10 */
/* 2082 */	NdrFcShort( 0x20 ),	/* ia64 Stack size/offset = 32 */
/* 2084 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2086 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2088 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 2090 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2092 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2094 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2096 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2098 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter other */

/* 2100 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 2102 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 2104 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */

	/* Parameter result */

/* 2106 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 2108 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 2110 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 2112 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2114 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 2116 */	0x8,		/* FC_LONG */
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
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/*  4 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/*  6 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/*  8 */	NdrFcShort( 0x2 ),	/* Offset= 2 (10) */
/* 10 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 12 */	NdrFcLong( 0x4c4c5c00 ),	/* 1280072704 */
/* 16 */	NdrFcShort( 0xfe1e ),	/* -482 */
/* 18 */	NdrFcShort( 0x11d0 ),	/* 4560 */
/* 20 */	0xad,		/* 173 */
			0x87,		/* 135 */
/* 22 */	0x8,		/* 8 */
			0x0,		/* 0 */
/* 24 */	0x9,		/* 9 */
			0xb6,		/* 182 */
/* 26 */	0xf2,		/* 242 */
			0x2b,		/* 43 */
/* 28 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 30 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 32 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 34 */	NdrFcShort( 0x2 ),	/* Offset= 2 (36) */
/* 36 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 38 */	NdrFcLong( 0x6a124031 ),	/* 1779580977 */
/* 42 */	NdrFcShort( 0xfe38 ),	/* -456 */
/* 44 */	NdrFcShort( 0x11d0 ),	/* 4560 */
/* 46 */	0xbe,		/* 190 */
			0xce,		/* 206 */
/* 48 */	0x0,		/* 0 */
			0x80,		/* 128 */
/* 50 */	0x5f,		/* 95 */
			0x7c,		/* 124 */
/* 52 */	0x42,		/* 66 */
			0x68,		/* 104 */
/* 54 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 56 */	0xc,		/* FC_DOUBLE */
			0x5c,		/* FC_PAD */
/* 58 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 60 */	NdrFcShort( 0x3aa ),	/* Offset= 938 (998) */
/* 62 */	
			0x13, 0x0,	/* FC_OP */
/* 64 */	NdrFcShort( 0x392 ),	/* Offset= 914 (978) */
/* 66 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 68 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 70 */	NdrFcShort( 0xfff8 ),	/* -8 */
/* 72 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 74 */	NdrFcShort( 0x2 ),	/* Offset= 2 (76) */
/* 76 */	NdrFcShort( 0x10 ),	/* 16 */
/* 78 */	NdrFcShort( 0x2b ),	/* 43 */
/* 80 */	NdrFcLong( 0x3 ),	/* 3 */
/* 84 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 86 */	NdrFcLong( 0x11 ),	/* 17 */
/* 90 */	NdrFcShort( 0x8002 ),	/* Simple arm type: FC_CHAR */
/* 92 */	NdrFcLong( 0x2 ),	/* 2 */
/* 96 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 98 */	NdrFcLong( 0x4 ),	/* 4 */
/* 102 */	NdrFcShort( 0x800a ),	/* Simple arm type: FC_FLOAT */
/* 104 */	NdrFcLong( 0x5 ),	/* 5 */
/* 108 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 110 */	NdrFcLong( 0xb ),	/* 11 */
/* 114 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 116 */	NdrFcLong( 0xa ),	/* 10 */
/* 120 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 122 */	NdrFcLong( 0x6 ),	/* 6 */
/* 126 */	NdrFcShort( 0xd6 ),	/* Offset= 214 (340) */
/* 128 */	NdrFcLong( 0x7 ),	/* 7 */
/* 132 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 134 */	NdrFcLong( 0x8 ),	/* 8 */
/* 138 */	NdrFcShort( 0xd0 ),	/* Offset= 208 (346) */
/* 140 */	NdrFcLong( 0xd ),	/* 13 */
/* 144 */	NdrFcShort( 0xe4 ),	/* Offset= 228 (372) */
/* 146 */	NdrFcLong( 0x9 ),	/* 9 */
/* 150 */	NdrFcShort( 0xf0 ),	/* Offset= 240 (390) */
/* 152 */	NdrFcLong( 0x2000 ),	/* 8192 */
/* 156 */	NdrFcShort( 0xfc ),	/* Offset= 252 (408) */
/* 158 */	NdrFcLong( 0x24 ),	/* 36 */
/* 162 */	NdrFcShort( 0x2ee ),	/* Offset= 750 (912) */
/* 164 */	NdrFcLong( 0x4024 ),	/* 16420 */
/* 168 */	NdrFcShort( 0x2e8 ),	/* Offset= 744 (912) */
/* 170 */	NdrFcLong( 0x4011 ),	/* 16401 */
/* 174 */	NdrFcShort( 0x2e6 ),	/* Offset= 742 (916) */
/* 176 */	NdrFcLong( 0x4002 ),	/* 16386 */
/* 180 */	NdrFcShort( 0x2e4 ),	/* Offset= 740 (920) */
/* 182 */	NdrFcLong( 0x4003 ),	/* 16387 */
/* 186 */	NdrFcShort( 0x2e2 ),	/* Offset= 738 (924) */
/* 188 */	NdrFcLong( 0x4004 ),	/* 16388 */
/* 192 */	NdrFcShort( 0x2e0 ),	/* Offset= 736 (928) */
/* 194 */	NdrFcLong( 0x4005 ),	/* 16389 */
/* 198 */	NdrFcShort( 0x2de ),	/* Offset= 734 (932) */
/* 200 */	NdrFcLong( 0x400b ),	/* 16395 */
/* 204 */	NdrFcShort( 0x2cc ),	/* Offset= 716 (920) */
/* 206 */	NdrFcLong( 0x400a ),	/* 16394 */
/* 210 */	NdrFcShort( 0x2ca ),	/* Offset= 714 (924) */
/* 212 */	NdrFcLong( 0x4006 ),	/* 16390 */
/* 216 */	NdrFcShort( 0x2d0 ),	/* Offset= 720 (936) */
/* 218 */	NdrFcLong( 0x4007 ),	/* 16391 */
/* 222 */	NdrFcShort( 0x2c6 ),	/* Offset= 710 (932) */
/* 224 */	NdrFcLong( 0x4008 ),	/* 16392 */
/* 228 */	NdrFcShort( 0x2c8 ),	/* Offset= 712 (940) */
/* 230 */	NdrFcLong( 0x400d ),	/* 16397 */
/* 234 */	NdrFcShort( 0x2c6 ),	/* Offset= 710 (944) */
/* 236 */	NdrFcLong( 0x4009 ),	/* 16393 */
/* 240 */	NdrFcShort( 0x2c4 ),	/* Offset= 708 (948) */
/* 242 */	NdrFcLong( 0x6000 ),	/* 24576 */
/* 246 */	NdrFcShort( 0x2c2 ),	/* Offset= 706 (952) */
/* 248 */	NdrFcLong( 0x400c ),	/* 16396 */
/* 252 */	NdrFcShort( 0x2c0 ),	/* Offset= 704 (956) */
/* 254 */	NdrFcLong( 0x10 ),	/* 16 */
/* 258 */	NdrFcShort( 0x8002 ),	/* Simple arm type: FC_CHAR */
/* 260 */	NdrFcLong( 0x12 ),	/* 18 */
/* 264 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 266 */	NdrFcLong( 0x13 ),	/* 19 */
/* 270 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 272 */	NdrFcLong( 0x16 ),	/* 22 */
/* 276 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 278 */	NdrFcLong( 0x17 ),	/* 23 */
/* 282 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 284 */	NdrFcLong( 0xe ),	/* 14 */
/* 288 */	NdrFcShort( 0x2a4 ),	/* Offset= 676 (964) */
/* 290 */	NdrFcLong( 0x400e ),	/* 16398 */
/* 294 */	NdrFcShort( 0x2a8 ),	/* Offset= 680 (974) */
/* 296 */	NdrFcLong( 0x4010 ),	/* 16400 */
/* 300 */	NdrFcShort( 0x268 ),	/* Offset= 616 (916) */
/* 302 */	NdrFcLong( 0x4012 ),	/* 16402 */
/* 306 */	NdrFcShort( 0x266 ),	/* Offset= 614 (920) */
/* 308 */	NdrFcLong( 0x4013 ),	/* 16403 */
/* 312 */	NdrFcShort( 0x264 ),	/* Offset= 612 (924) */
/* 314 */	NdrFcLong( 0x4016 ),	/* 16406 */
/* 318 */	NdrFcShort( 0x25e ),	/* Offset= 606 (924) */
/* 320 */	NdrFcLong( 0x4017 ),	/* 16407 */
/* 324 */	NdrFcShort( 0x258 ),	/* Offset= 600 (924) */
/* 326 */	NdrFcLong( 0x0 ),	/* 0 */
/* 330 */	NdrFcShort( 0x0 ),	/* Offset= 0 (330) */
/* 332 */	NdrFcLong( 0x1 ),	/* 1 */
/* 336 */	NdrFcShort( 0x0 ),	/* Offset= 0 (336) */
/* 338 */	NdrFcShort( 0xffffffff ),	/* Offset= -1 (337) */
/* 340 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 342 */	NdrFcShort( 0x8 ),	/* 8 */
/* 344 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 346 */	
			0x13, 0x0,	/* FC_OP */
/* 348 */	NdrFcShort( 0xe ),	/* Offset= 14 (362) */
/* 350 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 352 */	NdrFcShort( 0x2 ),	/* 2 */
/* 354 */	0x9,		/* Corr desc: FC_ULONG */
			0x0,		/*  */
/* 356 */	NdrFcShort( 0xfffc ),	/* -4 */
/* 358 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 360 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 362 */	
			0x17,		/* FC_CSTRUCT */
			0x3,		/* 3 */
/* 364 */	NdrFcShort( 0x8 ),	/* 8 */
/* 366 */	NdrFcShort( 0xfffffff0 ),	/* Offset= -16 (350) */
/* 368 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 370 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 372 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 374 */	NdrFcLong( 0x0 ),	/* 0 */
/* 378 */	NdrFcShort( 0x0 ),	/* 0 */
/* 380 */	NdrFcShort( 0x0 ),	/* 0 */
/* 382 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 384 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 386 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 388 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 390 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 392 */	NdrFcLong( 0x20400 ),	/* 132096 */
/* 396 */	NdrFcShort( 0x0 ),	/* 0 */
/* 398 */	NdrFcShort( 0x0 ),	/* 0 */
/* 400 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 402 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 404 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 406 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 408 */	
			0x13, 0x0,	/* FC_OP */
/* 410 */	NdrFcShort( 0x1e4 ),	/* Offset= 484 (894) */
/* 412 */	
			0x2a,		/* FC_ENCAPSULATED_UNION */
			0x89,		/* 137 */
/* 414 */	NdrFcShort( 0x20 ),	/* 32 */
/* 416 */	NdrFcShort( 0xa ),	/* 10 */
/* 418 */	NdrFcLong( 0x8 ),	/* 8 */
/* 422 */	NdrFcShort( 0x50 ),	/* Offset= 80 (502) */
/* 424 */	NdrFcLong( 0xd ),	/* 13 */
/* 428 */	NdrFcShort( 0x70 ),	/* Offset= 112 (540) */
/* 430 */	NdrFcLong( 0x9 ),	/* 9 */
/* 434 */	NdrFcShort( 0x90 ),	/* Offset= 144 (578) */
/* 436 */	NdrFcLong( 0xc ),	/* 12 */
/* 440 */	NdrFcShort( 0xb0 ),	/* Offset= 176 (616) */
/* 442 */	NdrFcLong( 0x24 ),	/* 36 */
/* 446 */	NdrFcShort( 0x102 ),	/* Offset= 258 (704) */
/* 448 */	NdrFcLong( 0x800d ),	/* 32781 */
/* 452 */	NdrFcShort( 0x11e ),	/* Offset= 286 (738) */
/* 454 */	NdrFcLong( 0x10 ),	/* 16 */
/* 458 */	NdrFcShort( 0x138 ),	/* Offset= 312 (770) */
/* 460 */	NdrFcLong( 0x2 ),	/* 2 */
/* 464 */	NdrFcShort( 0x14e ),	/* Offset= 334 (798) */
/* 466 */	NdrFcLong( 0x3 ),	/* 3 */
/* 470 */	NdrFcShort( 0x164 ),	/* Offset= 356 (826) */
/* 472 */	NdrFcLong( 0x14 ),	/* 20 */
/* 476 */	NdrFcShort( 0x17a ),	/* Offset= 378 (854) */
/* 478 */	NdrFcShort( 0xffffffff ),	/* Offset= -1 (477) */
/* 480 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 482 */	NdrFcShort( 0x0 ),	/* 0 */
/* 484 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 486 */	NdrFcShort( 0x0 ),	/* 0 */
/* 488 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 490 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 494 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 496 */	
			0x13, 0x0,	/* FC_OP */
/* 498 */	NdrFcShort( 0xffffff78 ),	/* Offset= -136 (362) */
/* 500 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 502 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 504 */	NdrFcShort( 0x10 ),	/* 16 */
/* 506 */	NdrFcShort( 0x0 ),	/* 0 */
/* 508 */	NdrFcShort( 0x6 ),	/* Offset= 6 (514) */
/* 510 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 512 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 514 */	
			0x11, 0x0,	/* FC_RP */
/* 516 */	NdrFcShort( 0xffffffdc ),	/* Offset= -36 (480) */
/* 518 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 520 */	NdrFcShort( 0x0 ),	/* 0 */
/* 522 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 524 */	NdrFcShort( 0x0 ),	/* 0 */
/* 526 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 528 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 532 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 534 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 536 */	NdrFcShort( 0xffffff5c ),	/* Offset= -164 (372) */
/* 538 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 540 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 542 */	NdrFcShort( 0x10 ),	/* 16 */
/* 544 */	NdrFcShort( 0x0 ),	/* 0 */
/* 546 */	NdrFcShort( 0x6 ),	/* Offset= 6 (552) */
/* 548 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 550 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 552 */	
			0x11, 0x0,	/* FC_RP */
/* 554 */	NdrFcShort( 0xffffffdc ),	/* Offset= -36 (518) */
/* 556 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 558 */	NdrFcShort( 0x0 ),	/* 0 */
/* 560 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 562 */	NdrFcShort( 0x0 ),	/* 0 */
/* 564 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 566 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 570 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 572 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 574 */	NdrFcShort( 0xffffff48 ),	/* Offset= -184 (390) */
/* 576 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 578 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 580 */	NdrFcShort( 0x10 ),	/* 16 */
/* 582 */	NdrFcShort( 0x0 ),	/* 0 */
/* 584 */	NdrFcShort( 0x6 ),	/* Offset= 6 (590) */
/* 586 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 588 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 590 */	
			0x11, 0x0,	/* FC_RP */
/* 592 */	NdrFcShort( 0xffffffdc ),	/* Offset= -36 (556) */
/* 594 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 596 */	NdrFcShort( 0x0 ),	/* 0 */
/* 598 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 600 */	NdrFcShort( 0x0 ),	/* 0 */
/* 602 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 604 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 608 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 610 */	
			0x13, 0x0,	/* FC_OP */
/* 612 */	NdrFcShort( 0x16e ),	/* Offset= 366 (978) */
/* 614 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 616 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 618 */	NdrFcShort( 0x10 ),	/* 16 */
/* 620 */	NdrFcShort( 0x0 ),	/* 0 */
/* 622 */	NdrFcShort( 0x6 ),	/* Offset= 6 (628) */
/* 624 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 626 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 628 */	
			0x11, 0x0,	/* FC_RP */
/* 630 */	NdrFcShort( 0xffffffdc ),	/* Offset= -36 (594) */
/* 632 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 634 */	NdrFcLong( 0x2f ),	/* 47 */
/* 638 */	NdrFcShort( 0x0 ),	/* 0 */
/* 640 */	NdrFcShort( 0x0 ),	/* 0 */
/* 642 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 644 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 646 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 648 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 650 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 652 */	NdrFcShort( 0x1 ),	/* 1 */
/* 654 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 656 */	NdrFcShort( 0x4 ),	/* 4 */
/* 658 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 660 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 662 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 664 */	NdrFcShort( 0x18 ),	/* 24 */
/* 666 */	NdrFcShort( 0x0 ),	/* 0 */
/* 668 */	NdrFcShort( 0xa ),	/* Offset= 10 (678) */
/* 670 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 672 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 674 */	NdrFcShort( 0xffffffd6 ),	/* Offset= -42 (632) */
/* 676 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 678 */	
			0x13, 0x0,	/* FC_OP */
/* 680 */	NdrFcShort( 0xffffffe2 ),	/* Offset= -30 (650) */
/* 682 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 684 */	NdrFcShort( 0x0 ),	/* 0 */
/* 686 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 688 */	NdrFcShort( 0x0 ),	/* 0 */
/* 690 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 692 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 696 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 698 */	
			0x13, 0x0,	/* FC_OP */
/* 700 */	NdrFcShort( 0xffffffda ),	/* Offset= -38 (662) */
/* 702 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 704 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 706 */	NdrFcShort( 0x10 ),	/* 16 */
/* 708 */	NdrFcShort( 0x0 ),	/* 0 */
/* 710 */	NdrFcShort( 0x6 ),	/* Offset= 6 (716) */
/* 712 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 714 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 716 */	
			0x11, 0x0,	/* FC_RP */
/* 718 */	NdrFcShort( 0xffffffdc ),	/* Offset= -36 (682) */
/* 720 */	
			0x1d,		/* FC_SMFARRAY */
			0x0,		/* 0 */
/* 722 */	NdrFcShort( 0x8 ),	/* 8 */
/* 724 */	0x2,		/* FC_CHAR */
			0x5b,		/* FC_END */
/* 726 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 728 */	NdrFcShort( 0x10 ),	/* 16 */
/* 730 */	0x8,		/* FC_LONG */
			0x6,		/* FC_SHORT */
/* 732 */	0x6,		/* FC_SHORT */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 734 */	0x0,		/* 0 */
			NdrFcShort( 0xfffffff1 ),	/* Offset= -15 (720) */
			0x5b,		/* FC_END */
/* 738 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 740 */	NdrFcShort( 0x20 ),	/* 32 */
/* 742 */	NdrFcShort( 0x0 ),	/* 0 */
/* 744 */	NdrFcShort( 0xa ),	/* Offset= 10 (754) */
/* 746 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 748 */	0x36,		/* FC_POINTER */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 750 */	0x0,		/* 0 */
			NdrFcShort( 0xffffffe7 ),	/* Offset= -25 (726) */
			0x5b,		/* FC_END */
/* 754 */	
			0x11, 0x0,	/* FC_RP */
/* 756 */	NdrFcShort( 0xffffff12 ),	/* Offset= -238 (518) */
/* 758 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 760 */	NdrFcShort( 0x1 ),	/* 1 */
/* 762 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 764 */	NdrFcShort( 0x0 ),	/* 0 */
/* 766 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 768 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 770 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 772 */	NdrFcShort( 0x10 ),	/* 16 */
/* 774 */	NdrFcShort( 0x0 ),	/* 0 */
/* 776 */	NdrFcShort( 0x6 ),	/* Offset= 6 (782) */
/* 778 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 780 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 782 */	
			0x13, 0x0,	/* FC_OP */
/* 784 */	NdrFcShort( 0xffffffe6 ),	/* Offset= -26 (758) */
/* 786 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 788 */	NdrFcShort( 0x2 ),	/* 2 */
/* 790 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 792 */	NdrFcShort( 0x0 ),	/* 0 */
/* 794 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 796 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 798 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 800 */	NdrFcShort( 0x10 ),	/* 16 */
/* 802 */	NdrFcShort( 0x0 ),	/* 0 */
/* 804 */	NdrFcShort( 0x6 ),	/* Offset= 6 (810) */
/* 806 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 808 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 810 */	
			0x13, 0x0,	/* FC_OP */
/* 812 */	NdrFcShort( 0xffffffe6 ),	/* Offset= -26 (786) */
/* 814 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 816 */	NdrFcShort( 0x4 ),	/* 4 */
/* 818 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 820 */	NdrFcShort( 0x0 ),	/* 0 */
/* 822 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 824 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 826 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 828 */	NdrFcShort( 0x10 ),	/* 16 */
/* 830 */	NdrFcShort( 0x0 ),	/* 0 */
/* 832 */	NdrFcShort( 0x6 ),	/* Offset= 6 (838) */
/* 834 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 836 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 838 */	
			0x13, 0x0,	/* FC_OP */
/* 840 */	NdrFcShort( 0xffffffe6 ),	/* Offset= -26 (814) */
/* 842 */	
			0x1b,		/* FC_CARRAY */
			0x7,		/* 7 */
/* 844 */	NdrFcShort( 0x8 ),	/* 8 */
/* 846 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 848 */	NdrFcShort( 0x0 ),	/* 0 */
/* 850 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 852 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 854 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 856 */	NdrFcShort( 0x10 ),	/* 16 */
/* 858 */	NdrFcShort( 0x0 ),	/* 0 */
/* 860 */	NdrFcShort( 0x6 ),	/* Offset= 6 (866) */
/* 862 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 864 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 866 */	
			0x13, 0x0,	/* FC_OP */
/* 868 */	NdrFcShort( 0xffffffe6 ),	/* Offset= -26 (842) */
/* 870 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 872 */	NdrFcShort( 0x8 ),	/* 8 */
/* 874 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 876 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 878 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 880 */	NdrFcShort( 0x8 ),	/* 8 */
/* 882 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 884 */	NdrFcShort( 0xffc8 ),	/* -56 */
/* 886 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 888 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 890 */	NdrFcShort( 0xffffffec ),	/* Offset= -20 (870) */
/* 892 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 894 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 896 */	NdrFcShort( 0x38 ),	/* 56 */
/* 898 */	NdrFcShort( 0xffffffec ),	/* Offset= -20 (878) */
/* 900 */	NdrFcShort( 0x0 ),	/* Offset= 0 (900) */
/* 902 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 904 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 906 */	0x40,		/* FC_STRUCTPAD4 */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 908 */	0x0,		/* 0 */
			NdrFcShort( 0xfffffe0f ),	/* Offset= -497 (412) */
			0x5b,		/* FC_END */
/* 912 */	
			0x13, 0x0,	/* FC_OP */
/* 914 */	NdrFcShort( 0xffffff04 ),	/* Offset= -252 (662) */
/* 916 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 918 */	0x2,		/* FC_CHAR */
			0x5c,		/* FC_PAD */
/* 920 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 922 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 924 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 926 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 928 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 930 */	0xa,		/* FC_FLOAT */
			0x5c,		/* FC_PAD */
/* 932 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 934 */	0xc,		/* FC_DOUBLE */
			0x5c,		/* FC_PAD */
/* 936 */	
			0x13, 0x0,	/* FC_OP */
/* 938 */	NdrFcShort( 0xfffffdaa ),	/* Offset= -598 (340) */
/* 940 */	
			0x13, 0x10,	/* FC_OP [pointer_deref] */
/* 942 */	NdrFcShort( 0xfffffdac ),	/* Offset= -596 (346) */
/* 944 */	
			0x13, 0x10,	/* FC_OP [pointer_deref] */
/* 946 */	NdrFcShort( 0xfffffdc2 ),	/* Offset= -574 (372) */
/* 948 */	
			0x13, 0x10,	/* FC_OP [pointer_deref] */
/* 950 */	NdrFcShort( 0xfffffdd0 ),	/* Offset= -560 (390) */
/* 952 */	
			0x13, 0x10,	/* FC_OP [pointer_deref] */
/* 954 */	NdrFcShort( 0xfffffdde ),	/* Offset= -546 (408) */
/* 956 */	
			0x13, 0x10,	/* FC_OP [pointer_deref] */
/* 958 */	NdrFcShort( 0x2 ),	/* Offset= 2 (960) */
/* 960 */	
			0x13, 0x0,	/* FC_OP */
/* 962 */	NdrFcShort( 0x10 ),	/* Offset= 16 (978) */
/* 964 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 966 */	NdrFcShort( 0x10 ),	/* 16 */
/* 968 */	0x6,		/* FC_SHORT */
			0x2,		/* FC_CHAR */
/* 970 */	0x2,		/* FC_CHAR */
			0x8,		/* FC_LONG */
/* 972 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 974 */	
			0x13, 0x0,	/* FC_OP */
/* 976 */	NdrFcShort( 0xfffffff4 ),	/* Offset= -12 (964) */
/* 978 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 980 */	NdrFcShort( 0x20 ),	/* 32 */
/* 982 */	NdrFcShort( 0x0 ),	/* 0 */
/* 984 */	NdrFcShort( 0x0 ),	/* Offset= 0 (984) */
/* 986 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 988 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 990 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 992 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 994 */	NdrFcShort( 0xfffffc60 ),	/* Offset= -928 (66) */
/* 996 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 998 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1000 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1002 */	NdrFcShort( 0x18 ),	/* 24 */
/* 1004 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1006 */	NdrFcShort( 0xfffffc50 ),	/* Offset= -944 (62) */
/* 1008 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 1010 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1012) */
/* 1012 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1014 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1016 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1018 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1020 */	NdrFcShort( 0xfffffd5e ),	/* Offset= -674 (346) */
/* 1022 */	
			0x12, 0x0,	/* FC_UP */
/* 1024 */	NdrFcShort( 0xffffffd2 ),	/* Offset= -46 (978) */
/* 1026 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1028 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1030 */	NdrFcShort( 0x18 ),	/* 24 */
/* 1032 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1034 */	NdrFcShort( 0xfffffff4 ),	/* Offset= -12 (1022) */
/* 1036 */	
			0x12, 0x0,	/* FC_UP */
/* 1038 */	NdrFcShort( 0xfffffd5c ),	/* Offset= -676 (362) */
/* 1040 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1042 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1044 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1046 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1048 */	NdrFcShort( 0xfffffff4 ),	/* Offset= -12 (1036) */
/* 1050 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 1052 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1054) */
/* 1054 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1056 */	NdrFcLong( 0x6a124035 ),	/* 1779580981 */
/* 1060 */	NdrFcShort( 0xfe38 ),	/* -456 */
/* 1062 */	NdrFcShort( 0x11d0 ),	/* 4560 */
/* 1064 */	0xbe,		/* 190 */
			0xce,		/* 206 */
/* 1066 */	0x0,		/* 0 */
			0x80,		/* 128 */
/* 1068 */	0x5f,		/* 95 */
			0x7c,		/* 124 */
/* 1070 */	0x42,		/* 66 */
			0x68,		/* 104 */
/* 1072 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 1074 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1076) */
/* 1076 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1078 */	NdrFcLong( 0x6a124038 ),	/* 1779580984 */
/* 1082 */	NdrFcShort( 0xfe38 ),	/* -456 */
/* 1084 */	NdrFcShort( 0x11d0 ),	/* 4560 */
/* 1086 */	0xbe,		/* 190 */
			0xce,		/* 206 */
/* 1088 */	0x0,		/* 0 */
			0x80,		/* 128 */
/* 1090 */	0x5f,		/* 95 */
			0x7c,		/* 124 */
/* 1092 */	0x42,		/* 66 */
			0x68,		/* 104 */

			0x0
        }
    };

static const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ] = 
        {
            
            {
            VARIANT_UserSize
            ,VARIANT_UserMarshal
            ,VARIANT_UserUnmarshal
            ,VARIANT_UserFree
            },
            {
            BSTR_UserSize
            ,BSTR_UserMarshal
            ,BSTR_UserUnmarshal
            ,BSTR_UserFree
            }

        };



/* Standard interface: __MIDL_itf_GeometryIdl_0000, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}} */


/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IGeometry, ver. 0.0,
   GUID={0x6A124031,0xFE38,0x11d0,{0xBE,0xCE,0x00,0x80,0x5F,0x7C,0x42,0x68}} */

#pragma code_seg(".orpc")
static const unsigned short IGeometry_FormatStringOffsetTable[] =
    {
    0,
    38,
    76,
    114,
    152,
    184,
    222,
    260,
    298,
    342
    };

static const MIDL_STUBLESS_PROXY_INFO IGeometry_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IGeometry_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IGeometry_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IGeometry_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(13) _IGeometryProxyVtbl = 
{
    &IGeometry_ProxyInfo,
    &IID_IGeometry,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IGeometry::get_Dimension */ ,
    (void *) (INT_PTR) -1 /* IGeometry::get_SpatialReference */ ,
    (void *) (INT_PTR) -1 /* IGeometry::putref_SpatialReference */ ,
    (void *) (INT_PTR) -1 /* IGeometry::get_IsEmpty */ ,
    (void *) (INT_PTR) -1 /* IGeometry::SetEmpty */ ,
    (void *) (INT_PTR) -1 /* IGeometry::get_IsSimple */ ,
    (void *) (INT_PTR) -1 /* IGeometry::Envelope */ ,
    (void *) (INT_PTR) -1 /* IGeometry::Clone */ ,
    (void *) (INT_PTR) -1 /* IGeometry::Project */ ,
    (void *) (INT_PTR) -1 /* IGeometry::Extent2D */
};

const CInterfaceStubVtbl _IGeometryStubVtbl =
{
    &IID_IGeometry,
    &IGeometry_ServerInfo,
    13,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IWks, ver. 0.0,
   GUID={0x6A124032,0xFE38,0x11d0,{0xBE,0xCE,0x00,0x80,0x5F,0x7C,0x42,0x68}} */

#pragma code_seg(".orpc")
static const unsigned short IWks_FormatStringOffsetTable[] =
    {
    398,
    436,
    474,
    518
    };

static const MIDL_STUBLESS_PROXY_INFO IWks_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IWks_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IWks_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IWks_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(7) _IWksProxyVtbl = 
{
    &IWks_ProxyInfo,
    &IID_IWks,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IWks::ExportToWKB */ ,
    (void *) (INT_PTR) -1 /* IWks::ExportToWKT */ ,
    (void *) (INT_PTR) -1 /* IWks::ImportFromWKB */ ,
    (void *) (INT_PTR) -1 /* IWks::ImportFromWKT */
};

const CInterfaceStubVtbl _IWksStubVtbl =
{
    &IID_IWks,
    &IWks_ServerInfo,
    7,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IGeometryFactory, ver. 0.0,
   GUID={0x6A124033,0xFE38,0x11d0,{0xBE,0xCE,0x00,0x80,0x5F,0x7C,0x42,0x68}} */

#pragma code_seg(".orpc")
static const unsigned short IGeometryFactory_FormatStringOffsetTable[] =
    {
    562,
    612
    };

static const MIDL_STUBLESS_PROXY_INFO IGeometryFactory_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IGeometryFactory_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IGeometryFactory_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IGeometryFactory_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(5) _IGeometryFactoryProxyVtbl = 
{
    &IGeometryFactory_ProxyInfo,
    &IID_IGeometryFactory,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IGeometryFactory::CreateFromWKB */ ,
    (void *) (INT_PTR) -1 /* IGeometryFactory::CreateFromWKT */
};

const CInterfaceStubVtbl _IGeometryFactoryStubVtbl =
{
    &IID_IGeometryFactory,
    &IGeometryFactory_ServerInfo,
    5,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IPoint, ver. 0.0,
   GUID={0x6A124035,0xFE38,0x11d0,{0xBE,0xCE,0x00,0x80,0x5F,0x7C,0x42,0x68}} */

#pragma code_seg(".orpc")
static const unsigned short IPoint_FormatStringOffsetTable[] =
    {
    0,
    38,
    76,
    114,
    152,
    184,
    222,
    260,
    298,
    342,
    662,
    706,
    744
    };

static const MIDL_STUBLESS_PROXY_INFO IPoint_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IPoint_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IPoint_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IPoint_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(16) _IPointProxyVtbl = 
{
    &IPoint_ProxyInfo,
    &IID_IPoint,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IGeometry::get_Dimension */ ,
    (void *) (INT_PTR) -1 /* IGeometry::get_SpatialReference */ ,
    (void *) (INT_PTR) -1 /* IGeometry::putref_SpatialReference */ ,
    (void *) (INT_PTR) -1 /* IGeometry::get_IsEmpty */ ,
    (void *) (INT_PTR) -1 /* IGeometry::SetEmpty */ ,
    (void *) (INT_PTR) -1 /* IGeometry::get_IsSimple */ ,
    (void *) (INT_PTR) -1 /* IGeometry::Envelope */ ,
    (void *) (INT_PTR) -1 /* IGeometry::Clone */ ,
    (void *) (INT_PTR) -1 /* IGeometry::Project */ ,
    (void *) (INT_PTR) -1 /* IGeometry::Extent2D */ ,
    (void *) (INT_PTR) -1 /* IPoint::Coords */ ,
    (void *) (INT_PTR) -1 /* IPoint::get_X */ ,
    (void *) (INT_PTR) -1 /* IPoint::get_Y */
};

const CInterfaceStubVtbl _IPointStubVtbl =
{
    &IID_IPoint,
    &IPoint_ServerInfo,
    16,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IPointZ, ver. 0.0,
   GUID={0xD4579E2D,0x1D2B,0x11d3,{0x80,0xBE,0x00,0xC0,0x4F,0x68,0x0F,0xFF}} */

#pragma code_seg(".orpc")
static const unsigned short IPointZ_FormatStringOffsetTable[] =
    {
    0,
    38,
    76,
    114,
    152,
    184,
    222,
    260,
    298,
    342,
    662,
    706,
    744,
    782
    };

static const MIDL_STUBLESS_PROXY_INFO IPointZ_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IPointZ_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IPointZ_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IPointZ_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(17) _IPointZProxyVtbl = 
{
    &IPointZ_ProxyInfo,
    &IID_IPointZ,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IGeometry::get_Dimension */ ,
    (void *) (INT_PTR) -1 /* IGeometry::get_SpatialReference */ ,
    (void *) (INT_PTR) -1 /* IGeometry::putref_SpatialReference */ ,
    (void *) (INT_PTR) -1 /* IGeometry::get_IsEmpty */ ,
    (void *) (INT_PTR) -1 /* IGeometry::SetEmpty */ ,
    (void *) (INT_PTR) -1 /* IGeometry::get_IsSimple */ ,
    (void *) (INT_PTR) -1 /* IGeometry::Envelope */ ,
    (void *) (INT_PTR) -1 /* IGeometry::Clone */ ,
    (void *) (INT_PTR) -1 /* IGeometry::Project */ ,
    (void *) (INT_PTR) -1 /* IGeometry::Extent2D */ ,
    (void *) (INT_PTR) -1 /* IPoint::Coords */ ,
    (void *) (INT_PTR) -1 /* IPoint::get_X */ ,
    (void *) (INT_PTR) -1 /* IPoint::get_Y */ ,
    (void *) (INT_PTR) -1 /* IPointZ::get_Z */
};

const CInterfaceStubVtbl _IPointZStubVtbl =
{
    &IID_IPointZ,
    &IPointZ_ServerInfo,
    17,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: ICurve, ver. 0.0,
   GUID={0x6A124036,0xFE38,0x11d0,{0xBE,0xCE,0x00,0x80,0x5F,0x7C,0x42,0x68}} */

#pragma code_seg(".orpc")
static const unsigned short ICurve_FormatStringOffsetTable[] =
    {
    0,
    38,
    76,
    114,
    152,
    184,
    222,
    260,
    298,
    342,
    820,
    858,
    896,
    934,
    972
    };

static const MIDL_STUBLESS_PROXY_INFO ICurve_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &ICurve_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO ICurve_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &ICurve_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(18) _ICurveProxyVtbl = 
{
    &ICurve_ProxyInfo,
    &IID_ICurve,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IGeometry::get_Dimension */ ,
    (void *) (INT_PTR) -1 /* IGeometry::get_SpatialReference */ ,
    (void *) (INT_PTR) -1 /* IGeometry::putref_SpatialReference */ ,
    (void *) (INT_PTR) -1 /* IGeometry::get_IsEmpty */ ,
    (void *) (INT_PTR) -1 /* IGeometry::SetEmpty */ ,
    (void *) (INT_PTR) -1 /* IGeometry::get_IsSimple */ ,
    (void *) (INT_PTR) -1 /* IGeometry::Envelope */ ,
    (void *) (INT_PTR) -1 /* IGeometry::Clone */ ,
    (void *) (INT_PTR) -1 /* IGeometry::Project */ ,
    (void *) (INT_PTR) -1 /* IGeometry::Extent2D */ ,
    (void *) (INT_PTR) -1 /* ICurve::get_Length */ ,
    (void *) (INT_PTR) -1 /* ICurve::StartPoint */ ,
    (void *) (INT_PTR) -1 /* ICurve::EndPoint */ ,
    (void *) (INT_PTR) -1 /* ICurve::get_IsClosed */ ,
    (void *) (INT_PTR) -1 /* ICurve::Value */
};

const CInterfaceStubVtbl _ICurveStubVtbl =
{
    &IID_ICurve,
    &ICurve_ServerInfo,
    18,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: ILineString, ver. 0.0,
   GUID={0x6A124037,0xFE38,0x11d0,{0xBE,0xCE,0x00,0x80,0x5F,0x7C,0x42,0x68}} */

#pragma code_seg(".orpc")
static const unsigned short ILineString_FormatStringOffsetTable[] =
    {
    0,
    38,
    76,
    114,
    152,
    184,
    222,
    260,
    298,
    342,
    820,
    858,
    896,
    934,
    972,
    1016,
    1054
    };

static const MIDL_STUBLESS_PROXY_INFO ILineString_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &ILineString_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO ILineString_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &ILineString_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(20) _ILineStringProxyVtbl = 
{
    &ILineString_ProxyInfo,
    &IID_ILineString,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IGeometry::get_Dimension */ ,
    (void *) (INT_PTR) -1 /* IGeometry::get_SpatialReference */ ,
    (void *) (INT_PTR) -1 /* IGeometry::putref_SpatialReference */ ,
    (void *) (INT_PTR) -1 /* IGeometry::get_IsEmpty */ ,
    (void *) (INT_PTR) -1 /* IGeometry::SetEmpty */ ,
    (void *) (INT_PTR) -1 /* IGeometry::get_IsSimple */ ,
    (void *) (INT_PTR) -1 /* IGeometry::Envelope */ ,
    (void *) (INT_PTR) -1 /* IGeometry::Clone */ ,
    (void *) (INT_PTR) -1 /* IGeometry::Project */ ,
    (void *) (INT_PTR) -1 /* IGeometry::Extent2D */ ,
    (void *) (INT_PTR) -1 /* ICurve::get_Length */ ,
    (void *) (INT_PTR) -1 /* ICurve::StartPoint */ ,
    (void *) (INT_PTR) -1 /* ICurve::EndPoint */ ,
    (void *) (INT_PTR) -1 /* ICurve::get_IsClosed */ ,
    (void *) (INT_PTR) -1 /* ICurve::Value */ ,
    (void *) (INT_PTR) -1 /* ILineString::get_NumPoints */ ,
    (void *) (INT_PTR) -1 /* ILineString::Point */
};

const CInterfaceStubVtbl _ILineStringStubVtbl =
{
    &IID_ILineString,
    &ILineString_ServerInfo,
    20,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: ILinearRing, ver. 0.0,
   GUID={0x6A124038,0xFE38,0x11d0,{0xBE,0xCE,0x00,0x80,0x5F,0x7C,0x42,0x68}} */

#pragma code_seg(".orpc")
static const unsigned short ILinearRing_FormatStringOffsetTable[] =
    {
    0,
    38,
    76,
    114,
    152,
    184,
    222,
    260,
    298,
    342,
    820,
    858,
    896,
    934,
    972,
    1016,
    1054,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO ILinearRing_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &ILinearRing_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO ILinearRing_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &ILinearRing_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(20) _ILinearRingProxyVtbl = 
{
    0,
    &IID_ILinearRing,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* forced delegation IGeometry::get_Dimension */ ,
    0 /* forced delegation IGeometry::get_SpatialReference */ ,
    0 /* forced delegation IGeometry::putref_SpatialReference */ ,
    0 /* forced delegation IGeometry::get_IsEmpty */ ,
    0 /* forced delegation IGeometry::SetEmpty */ ,
    0 /* forced delegation IGeometry::get_IsSimple */ ,
    0 /* forced delegation IGeometry::Envelope */ ,
    0 /* forced delegation IGeometry::Clone */ ,
    0 /* forced delegation IGeometry::Project */ ,
    0 /* forced delegation IGeometry::Extent2D */ ,
    0 /* forced delegation ICurve::get_Length */ ,
    0 /* forced delegation ICurve::StartPoint */ ,
    0 /* forced delegation ICurve::EndPoint */ ,
    0 /* forced delegation ICurve::get_IsClosed */ ,
    0 /* forced delegation ICurve::Value */ ,
    0 /* forced delegation ILineString::get_NumPoints */ ,
    0 /* forced delegation ILineString::Point */
};


static const PRPC_STUB_FUNCTION ILinearRing_table[] =
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
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _ILinearRingStubVtbl =
{
    &IID_ILinearRing,
    &ILinearRing_ServerInfo,
    20,
    &ILinearRing_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: ISurface, ver. 0.0,
   GUID={0x6A124039,0xFE38,0x11d0,{0xBE,0xCE,0x00,0x80,0x5F,0x7C,0x42,0x68}} */

#pragma code_seg(".orpc")
static const unsigned short ISurface_FormatStringOffsetTable[] =
    {
    0,
    38,
    76,
    114,
    152,
    184,
    222,
    260,
    298,
    342,
    820,
    858,
    896
    };

static const MIDL_STUBLESS_PROXY_INFO ISurface_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &ISurface_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO ISurface_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &ISurface_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(16) _ISurfaceProxyVtbl = 
{
    &ISurface_ProxyInfo,
    &IID_ISurface,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IGeometry::get_Dimension */ ,
    (void *) (INT_PTR) -1 /* IGeometry::get_SpatialReference */ ,
    (void *) (INT_PTR) -1 /* IGeometry::putref_SpatialReference */ ,
    (void *) (INT_PTR) -1 /* IGeometry::get_IsEmpty */ ,
    (void *) (INT_PTR) -1 /* IGeometry::SetEmpty */ ,
    (void *) (INT_PTR) -1 /* IGeometry::get_IsSimple */ ,
    (void *) (INT_PTR) -1 /* IGeometry::Envelope */ ,
    (void *) (INT_PTR) -1 /* IGeometry::Clone */ ,
    (void *) (INT_PTR) -1 /* IGeometry::Project */ ,
    (void *) (INT_PTR) -1 /* IGeometry::Extent2D */ ,
    (void *) (INT_PTR) -1 /* ISurface::get_Area */ ,
    (void *) (INT_PTR) -1 /* ISurface::Centroid */ ,
    (void *) (INT_PTR) -1 /* ISurface::PointOnSurface */
};

const CInterfaceStubVtbl _ISurfaceStubVtbl =
{
    &IID_ISurface,
    &ISurface_ServerInfo,
    16,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IGeometryCollection, ver. 0.0,
   GUID={0x6A12403A,0xFE38,0x11d0,{0xBE,0xCE,0x00,0x80,0x5F,0x7C,0x42,0x68}} */

#pragma code_seg(".orpc")
static const unsigned short IGeometryCollection_FormatStringOffsetTable[] =
    {
    0,
    38,
    76,
    114,
    152,
    184,
    222,
    260,
    298,
    342,
    1098,
    1136
    };

static const MIDL_STUBLESS_PROXY_INFO IGeometryCollection_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IGeometryCollection_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IGeometryCollection_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IGeometryCollection_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(15) _IGeometryCollectionProxyVtbl = 
{
    &IGeometryCollection_ProxyInfo,
    &IID_IGeometryCollection,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IGeometry::get_Dimension */ ,
    (void *) (INT_PTR) -1 /* IGeometry::get_SpatialReference */ ,
    (void *) (INT_PTR) -1 /* IGeometry::putref_SpatialReference */ ,
    (void *) (INT_PTR) -1 /* IGeometry::get_IsEmpty */ ,
    (void *) (INT_PTR) -1 /* IGeometry::SetEmpty */ ,
    (void *) (INT_PTR) -1 /* IGeometry::get_IsSimple */ ,
    (void *) (INT_PTR) -1 /* IGeometry::Envelope */ ,
    (void *) (INT_PTR) -1 /* IGeometry::Clone */ ,
    (void *) (INT_PTR) -1 /* IGeometry::Project */ ,
    (void *) (INT_PTR) -1 /* IGeometry::Extent2D */ ,
    (void *) (INT_PTR) -1 /* IGeometryCollection::get_NumGeometries */ ,
    (void *) (INT_PTR) -1 /* IGeometryCollection::Geometry */
};

const CInterfaceStubVtbl _IGeometryCollectionStubVtbl =
{
    &IID_IGeometryCollection,
    &IGeometryCollection_ServerInfo,
    15,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IPolygon, ver. 0.0,
   GUID={0x6A12403C,0xFE38,0x11d0,{0xBE,0xCE,0x00,0x80,0x5F,0x7C,0x42,0x68}} */

#pragma code_seg(".orpc")
static const unsigned short IPolygon_FormatStringOffsetTable[] =
    {
    0,
    38,
    76,
    114,
    152,
    184,
    222,
    260,
    298,
    342,
    820,
    858,
    896,
    1180,
    1218,
    1256
    };

static const MIDL_STUBLESS_PROXY_INFO IPolygon_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IPolygon_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IPolygon_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IPolygon_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(19) _IPolygonProxyVtbl = 
{
    &IPolygon_ProxyInfo,
    &IID_IPolygon,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IGeometry::get_Dimension */ ,
    (void *) (INT_PTR) -1 /* IGeometry::get_SpatialReference */ ,
    (void *) (INT_PTR) -1 /* IGeometry::putref_SpatialReference */ ,
    (void *) (INT_PTR) -1 /* IGeometry::get_IsEmpty */ ,
    (void *) (INT_PTR) -1 /* IGeometry::SetEmpty */ ,
    (void *) (INT_PTR) -1 /* IGeometry::get_IsSimple */ ,
    (void *) (INT_PTR) -1 /* IGeometry::Envelope */ ,
    (void *) (INT_PTR) -1 /* IGeometry::Clone */ ,
    (void *) (INT_PTR) -1 /* IGeometry::Project */ ,
    (void *) (INT_PTR) -1 /* IGeometry::Extent2D */ ,
    (void *) (INT_PTR) -1 /* ISurface::get_Area */ ,
    (void *) (INT_PTR) -1 /* ISurface::Centroid */ ,
    (void *) (INT_PTR) -1 /* ISurface::PointOnSurface */ ,
    (void *) (INT_PTR) -1 /* IPolygon::ExteriorRing */ ,
    (void *) (INT_PTR) -1 /* IPolygon::get_NumInteriorRings */ ,
    (void *) (INT_PTR) -1 /* IPolygon::InteriorRing */
};

const CInterfaceStubVtbl _IPolygonStubVtbl =
{
    &IID_IPolygon,
    &IPolygon_ServerInfo,
    19,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IMultiCurve, ver. 0.0,
   GUID={0x6A12403D,0xFE38,0x11d0,{0xBE,0xCE,0x00,0x80,0x5F,0x7C,0x42,0x68}} */

#pragma code_seg(".orpc")
static const unsigned short IMultiCurve_FormatStringOffsetTable[] =
    {
    0,
    38,
    76,
    114,
    152,
    184,
    222,
    260,
    298,
    342,
    1098,
    1136,
    744,
    934
    };

static const MIDL_STUBLESS_PROXY_INFO IMultiCurve_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IMultiCurve_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IMultiCurve_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IMultiCurve_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(17) _IMultiCurveProxyVtbl = 
{
    &IMultiCurve_ProxyInfo,
    &IID_IMultiCurve,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IGeometry::get_Dimension */ ,
    (void *) (INT_PTR) -1 /* IGeometry::get_SpatialReference */ ,
    (void *) (INT_PTR) -1 /* IGeometry::putref_SpatialReference */ ,
    (void *) (INT_PTR) -1 /* IGeometry::get_IsEmpty */ ,
    (void *) (INT_PTR) -1 /* IGeometry::SetEmpty */ ,
    (void *) (INT_PTR) -1 /* IGeometry::get_IsSimple */ ,
    (void *) (INT_PTR) -1 /* IGeometry::Envelope */ ,
    (void *) (INT_PTR) -1 /* IGeometry::Clone */ ,
    (void *) (INT_PTR) -1 /* IGeometry::Project */ ,
    (void *) (INT_PTR) -1 /* IGeometry::Extent2D */ ,
    (void *) (INT_PTR) -1 /* IGeometryCollection::get_NumGeometries */ ,
    (void *) (INT_PTR) -1 /* IGeometryCollection::Geometry */ ,
    (void *) (INT_PTR) -1 /* IMultiCurve::get_Length */ ,
    (void *) (INT_PTR) -1 /* IMultiCurve::get_IsClosed */
};

const CInterfaceStubVtbl _IMultiCurveStubVtbl =
{
    &IID_IMultiCurve,
    &IMultiCurve_ServerInfo,
    17,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IMultiSurface, ver. 0.0,
   GUID={0x6A12403F,0xFE38,0x11d0,{0xBE,0xCE,0x00,0x80,0x5F,0x7C,0x42,0x68}} */

#pragma code_seg(".orpc")
static const unsigned short IMultiSurface_FormatStringOffsetTable[] =
    {
    0,
    38,
    76,
    114,
    152,
    184,
    222,
    260,
    298,
    342,
    1098,
    1136,
    744,
    1300,
    1338
    };

static const MIDL_STUBLESS_PROXY_INFO IMultiSurface_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IMultiSurface_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IMultiSurface_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IMultiSurface_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(18) _IMultiSurfaceProxyVtbl = 
{
    &IMultiSurface_ProxyInfo,
    &IID_IMultiSurface,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IGeometry::get_Dimension */ ,
    (void *) (INT_PTR) -1 /* IGeometry::get_SpatialReference */ ,
    (void *) (INT_PTR) -1 /* IGeometry::putref_SpatialReference */ ,
    (void *) (INT_PTR) -1 /* IGeometry::get_IsEmpty */ ,
    (void *) (INT_PTR) -1 /* IGeometry::SetEmpty */ ,
    (void *) (INT_PTR) -1 /* IGeometry::get_IsSimple */ ,
    (void *) (INT_PTR) -1 /* IGeometry::Envelope */ ,
    (void *) (INT_PTR) -1 /* IGeometry::Clone */ ,
    (void *) (INT_PTR) -1 /* IGeometry::Project */ ,
    (void *) (INT_PTR) -1 /* IGeometry::Extent2D */ ,
    (void *) (INT_PTR) -1 /* IGeometryCollection::get_NumGeometries */ ,
    (void *) (INT_PTR) -1 /* IGeometryCollection::Geometry */ ,
    (void *) (INT_PTR) -1 /* IMultiSurface::get_Area */ ,
    (void *) (INT_PTR) -1 /* IMultiSurface::Centroid */ ,
    (void *) (INT_PTR) -1 /* IMultiSurface::PointOnSurface */
};

const CInterfaceStubVtbl _IMultiSurfaceStubVtbl =
{
    &IID_IMultiSurface,
    &IMultiSurface_ServerInfo,
    18,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: ISpatialRelation, ver. 0.0,
   GUID={0x6A124040,0xFE38,0x11d0,{0xBE,0xCE,0x00,0x80,0x5F,0x7C,0x42,0x68}} */

#pragma code_seg(".orpc")
static const unsigned short ISpatialRelation_FormatStringOffsetTable[] =
    {
    1376,
    1420,
    1464,
    1508,
    1552,
    1596,
    1640,
    1684
    };

static const MIDL_STUBLESS_PROXY_INFO ISpatialRelation_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &ISpatialRelation_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO ISpatialRelation_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &ISpatialRelation_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(11) _ISpatialRelationProxyVtbl = 
{
    &ISpatialRelation_ProxyInfo,
    &IID_ISpatialRelation,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* ISpatialRelation::Equals */ ,
    (void *) (INT_PTR) -1 /* ISpatialRelation::Touches */ ,
    (void *) (INT_PTR) -1 /* ISpatialRelation::Contains */ ,
    (void *) (INT_PTR) -1 /* ISpatialRelation::Within */ ,
    (void *) (INT_PTR) -1 /* ISpatialRelation::Disjoint */ ,
    (void *) (INT_PTR) -1 /* ISpatialRelation::Crosses */ ,
    (void *) (INT_PTR) -1 /* ISpatialRelation::Overlaps */ ,
    (void *) (INT_PTR) -1 /* ISpatialRelation::Intersects */
};

const CInterfaceStubVtbl _ISpatialRelationStubVtbl =
{
    &IID_ISpatialRelation,
    &ISpatialRelation_ServerInfo,
    11,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: ISpatialRelation2, ver. 0.0,
   GUID={0x6A124041,0xFE38,0x11d0,{0xBE,0xCE,0x00,0x80,0x5F,0x7C,0x42,0x68}} */

#pragma code_seg(".orpc")
static const unsigned short ISpatialRelation2_FormatStringOffsetTable[] =
    {
    1728
    };

static const MIDL_STUBLESS_PROXY_INFO ISpatialRelation2_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &ISpatialRelation2_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO ISpatialRelation2_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &ISpatialRelation2_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(4) _ISpatialRelation2ProxyVtbl = 
{
    &ISpatialRelation2_ProxyInfo,
    &IID_ISpatialRelation2,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* ISpatialRelation2::Relate */
};

const CInterfaceStubVtbl _ISpatialRelation2StubVtbl =
{
    &IID_ISpatialRelation2,
    &ISpatialRelation2_ServerInfo,
    4,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: ISpatialOperator, ver. 0.0,
   GUID={0x6A124042,0xFE38,0x11d0,{0xBE,0xCE,0x00,0x80,0x5F,0x7C,0x42,0x68}} */

#pragma code_seg(".orpc")
static const unsigned short ISpatialOperator_FormatStringOffsetTable[] =
    {
    1778,
    1822,
    1860,
    1904,
    1942,
    1986,
    2030,
    2074
    };

static const MIDL_STUBLESS_PROXY_INFO ISpatialOperator_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &ISpatialOperator_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO ISpatialOperator_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &ISpatialOperator_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(11) _ISpatialOperatorProxyVtbl = 
{
    &ISpatialOperator_ProxyInfo,
    &IID_ISpatialOperator,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* ISpatialOperator::Distance */ ,
    (void *) (INT_PTR) -1 /* ISpatialOperator::Boundary */ ,
    (void *) (INT_PTR) -1 /* ISpatialOperator::Buffer */ ,
    (void *) (INT_PTR) -1 /* ISpatialOperator::ConvexHull */ ,
    (void *) (INT_PTR) -1 /* ISpatialOperator::Intersection */ ,
    (void *) (INT_PTR) -1 /* ISpatialOperator::Union */ ,
    (void *) (INT_PTR) -1 /* ISpatialOperator::Difference */ ,
    (void *) (INT_PTR) -1 /* ISpatialOperator::SymmetricDifference */
};

const CInterfaceStubVtbl _ISpatialOperatorStubVtbl =
{
    &IID_ISpatialOperator,
    &ISpatialOperator_ServerInfo,
    11,
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

const CInterfaceProxyVtbl * _GeometryIdl_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_IPointZProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IGeometryProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IWksProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IGeometryFactoryProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IPointProxyVtbl,
    ( CInterfaceProxyVtbl *) &_ICurveProxyVtbl,
    ( CInterfaceProxyVtbl *) &_ILineStringProxyVtbl,
    ( CInterfaceProxyVtbl *) &_ILinearRingProxyVtbl,
    ( CInterfaceProxyVtbl *) &_ISurfaceProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IGeometryCollectionProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IPolygonProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IMultiCurveProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IMultiSurfaceProxyVtbl,
    ( CInterfaceProxyVtbl *) &_ISpatialRelationProxyVtbl,
    ( CInterfaceProxyVtbl *) &_ISpatialRelation2ProxyVtbl,
    ( CInterfaceProxyVtbl *) &_ISpatialOperatorProxyVtbl,
    0
};

const CInterfaceStubVtbl * _GeometryIdl_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_IPointZStubVtbl,
    ( CInterfaceStubVtbl *) &_IGeometryStubVtbl,
    ( CInterfaceStubVtbl *) &_IWksStubVtbl,
    ( CInterfaceStubVtbl *) &_IGeometryFactoryStubVtbl,
    ( CInterfaceStubVtbl *) &_IPointStubVtbl,
    ( CInterfaceStubVtbl *) &_ICurveStubVtbl,
    ( CInterfaceStubVtbl *) &_ILineStringStubVtbl,
    ( CInterfaceStubVtbl *) &_ILinearRingStubVtbl,
    ( CInterfaceStubVtbl *) &_ISurfaceStubVtbl,
    ( CInterfaceStubVtbl *) &_IGeometryCollectionStubVtbl,
    ( CInterfaceStubVtbl *) &_IPolygonStubVtbl,
    ( CInterfaceStubVtbl *) &_IMultiCurveStubVtbl,
    ( CInterfaceStubVtbl *) &_IMultiSurfaceStubVtbl,
    ( CInterfaceStubVtbl *) &_ISpatialRelationStubVtbl,
    ( CInterfaceStubVtbl *) &_ISpatialRelation2StubVtbl,
    ( CInterfaceStubVtbl *) &_ISpatialOperatorStubVtbl,
    0
};

PCInterfaceName const _GeometryIdl_InterfaceNamesList[] = 
{
    "IPointZ",
    "IGeometry",
    "IWks",
    "IGeometryFactory",
    "IPoint",
    "ICurve",
    "ILineString",
    "ILinearRing",
    "ISurface",
    "IGeometryCollection",
    "IPolygon",
    "IMultiCurve",
    "IMultiSurface",
    "ISpatialRelation",
    "ISpatialRelation2",
    "ISpatialOperator",
    0
};

const IID *  _GeometryIdl_BaseIIDList[] = 
{
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    &IID_ILineString,   /* forced */
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
};


#define _GeometryIdl_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _GeometryIdl, pIID, n)

int __stdcall _GeometryIdl_IID_Lookup( const IID * pIID, int * pIndex )
{
    IID_BS_LOOKUP_SETUP

    IID_BS_LOOKUP_INITIAL_TEST( _GeometryIdl, 16, 8 )
    IID_BS_LOOKUP_NEXT_TEST( _GeometryIdl, 4 )
    IID_BS_LOOKUP_NEXT_TEST( _GeometryIdl, 2 )
    IID_BS_LOOKUP_NEXT_TEST( _GeometryIdl, 1 )
    IID_BS_LOOKUP_RETURN_RESULT( _GeometryIdl, 16, *pIndex )
    
}

const ExtendedProxyFileInfo GeometryIdl_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _GeometryIdl_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _GeometryIdl_StubVtblList,
    (const PCInterfaceName * ) & _GeometryIdl_InterfaceNamesList,
    (const IID ** ) & _GeometryIdl_BaseIIDList,
    & _GeometryIdl_IID_Lookup, 
    16,
    2,
    0, /* table of [async_uuid] interfaces */
    0, /* Filler1 */
    0, /* Filler2 */
    0  /* Filler3 */
};


#endif /* defined(_M_IA64) || defined(_M_AMD64)*/

