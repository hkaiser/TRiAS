
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the proxy stub code */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Wed Mar 13 17:42:56 2002
 */
/* Compiler settings for .\Visinfo.idl:
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


#include "Visinfo.h"

#define TYPE_FORMAT_STRING_SIZE   1067                              
#define PROC_FORMAT_STRING_SIZE   139                               
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


extern const MIDL_SERVER_INFO IVisObjExt_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IVisObjExt_ProxyInfo;


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVisObjExt_GetVisInfoClass_Proxy( 
    IVisObjExt * This,
    /* [in] */ long lIdent,
    /* [in] */ VISINFOTYPE rgType,
    /* [optional][in] */ VARIANT vViewName,
    /* [retval][out] */ DVisInfo **ppIVisInfo)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(ppIVisInfo)
        {
        MIDL_memset(
               ppIVisInfo,
               0,
               sizeof( DVisInfo ** ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      3);
        
        
        
        if(!ppIVisInfo)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 14;
            NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char *)&vViewName,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[994] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            *(( long * )_StubMsg.Buffer)++ = lIdent;
            
            NdrSimpleTypeMarshall(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( unsigned char * )&rgType,
                         13);
            NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                    (unsigned char *)&vViewName,
                                    (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[994] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[0] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&ppIVisInfo,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1004],
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[1004],
                         ( void * )ppIVisInfo);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IVisObjExt_GetVisInfoClass_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    DVisInfo *_M0;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    void *_p_vViewName;
    long lIdent;
    DVisInfo **ppIVisInfo;
    VISINFOTYPE rgType;
    VARIANT vViewName;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    lIdent = 0;
    rgType = 0;
    _p_vViewName = &vViewName;
    MIDL_memset(
               _p_vViewName,
               0,
               sizeof( VARIANT  ));
    ( DVisInfo ** )ppIVisInfo = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[0] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        
        if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
            {
            RpcRaiseException(RPC_X_BAD_STUB_DATA);
            }
        lIdent = *(( long * )_StubMsg.Buffer)++;
        
        NdrSimpleTypeUnmarshall(
                           ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                           ( unsigned char * )&rgType,
                           13);
        NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&_p_vViewName,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[994],
                                  (unsigned char)0 );
        
        ppIVisInfo = &_M0;
        _M0 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IVisObjExt*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> GetVisInfoClass(
                   (IVisObjExt *) ((CStdStubBuffer *)This)->pvServerObject,
                   lIdent,
                   rgType,
                   vViewName,
                   ppIVisInfo);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char *)ppIVisInfo,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1004] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char *)ppIVisInfo,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1004] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrUserMarshalFree( &_StubMsg,
                            (unsigned char *)&vViewName,
                            &__MIDL_TypeFormatString.Format[994] );
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char *)ppIVisInfo,
                        &__MIDL_TypeFormatString.Format[1004] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVisObjExt_SetVisInfoClass_Proxy( 
    IVisObjExt * This,
    /* [in] */ long lIdent,
    /* [in] */ VISINFOTYPE rgType,
    /* [in] */ DVisInfo *pIVisInfo,
    /* [optional][in] */ VARIANT vViewName)
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
            
            _StubMsg.BufferLength = 14;
            NdrInterfacePointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                           (unsigned char *)pIVisInfo,
                                           (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1008] );
            
            NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char *)&vViewName,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[994] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            *(( long * )_StubMsg.Buffer)++ = lIdent;
            
            NdrSimpleTypeMarshall(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( unsigned char * )&rgType,
                         13);
            NdrInterfacePointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                         (unsigned char *)pIVisInfo,
                                         (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1008] );
            
            NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                    (unsigned char *)&vViewName,
                                    (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[994] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[14] );
            
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

void __RPC_STUB IVisObjExt_SetVisInfoClass_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    void *_p_vViewName;
    long lIdent;
    DVisInfo *pIVisInfo;
    VISINFOTYPE rgType;
    VARIANT vViewName;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    lIdent = 0;
    rgType = 0;
    pIVisInfo = 0;
    _p_vViewName = &vViewName;
    MIDL_memset(
               _p_vViewName,
               0,
               sizeof( VARIANT  ));
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[14] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        
        if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
            {
            RpcRaiseException(RPC_X_BAD_STUB_DATA);
            }
        lIdent = *(( long * )_StubMsg.Buffer)++;
        
        NdrSimpleTypeUnmarshall(
                           ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                           ( unsigned char * )&rgType,
                           13);
        NdrInterfacePointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char * *)&pIVisInfo,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1008],
                                       (unsigned char)0 );
        
        NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&_p_vViewName,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[994],
                                  (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IVisObjExt*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> SetVisInfoClass(
                   (IVisObjExt *) ((CStdStubBuffer *)This)->pvServerObject,
                   lIdent,
                   rgType,
                   pIVisInfo,
                   vViewName);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrInterfacePointerFree( &_StubMsg,
                                 (unsigned char *)pIVisInfo,
                                 &__MIDL_TypeFormatString.Format[1008] );
        
        NdrUserMarshalFree( &_StubMsg,
                            (unsigned char *)&vViewName,
                            &__MIDL_TypeFormatString.Format[994] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVisObjExt_ResetVisInfoClass_Proxy( 
    IVisObjExt * This,
    /* [in] */ long lIdent,
    /* [in] */ VISINFOTYPE rgType,
    /* [optional][in] */ VARIANT vView)
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
            
            _StubMsg.BufferLength = 14;
            NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char *)&vView,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[994] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            *(( long * )_StubMsg.Buffer)++ = lIdent;
            
            NdrSimpleTypeMarshall(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( unsigned char * )&rgType,
                         13);
            NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                    (unsigned char *)&vView,
                                    (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[994] );
            
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

void __RPC_STUB IVisObjExt_ResetVisInfoClass_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    void *_p_vView;
    long lIdent;
    VISINFOTYPE rgType;
    VARIANT vView;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    lIdent = 0;
    rgType = 0;
    _p_vView = &vView;
    MIDL_memset(
               _p_vView,
               0,
               sizeof( VARIANT  ));
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[28] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        
        if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
            {
            RpcRaiseException(RPC_X_BAD_STUB_DATA);
            }
        lIdent = *(( long * )_StubMsg.Buffer)++;
        
        NdrSimpleTypeUnmarshall(
                           ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                           ( unsigned char * )&rgType,
                           13);
        NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&_p_vView,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[994],
                                  (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IVisObjExt*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> ResetVisInfoClass(
                     (IVisObjExt *) ((CStdStubBuffer *)This)->pvServerObject,
                     lIdent,
                     rgType,
                     vView);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrUserMarshalFree( &_StubMsg,
                            (unsigned char *)&vView,
                            &__MIDL_TypeFormatString.Format[994] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVisObjExt_GetVisInfoObject_Proxy( 
    IVisObjExt * This,
    /* [in] */ long lONr,
    /* [in] */ VISINFOTYPE rgType,
    /* [optional][in] */ VARIANT vViewName,
    /* [retval][out] */ DVisInfo **ppIVisInfo)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(ppIVisInfo)
        {
        MIDL_memset(
               ppIVisInfo,
               0,
               sizeof( DVisInfo ** ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      6);
        
        
        
        if(!ppIVisInfo)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 14;
            NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char *)&vViewName,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[994] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            *(( long * )_StubMsg.Buffer)++ = lONr;
            
            NdrSimpleTypeMarshall(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( unsigned char * )&rgType,
                         13);
            NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                    (unsigned char *)&vViewName,
                                    (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[994] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[0] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&ppIVisInfo,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1004],
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[1004],
                         ( void * )ppIVisInfo);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IVisObjExt_GetVisInfoObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    DVisInfo *_M1;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    void *_p_vViewName;
    long lONr;
    DVisInfo **ppIVisInfo;
    VISINFOTYPE rgType;
    VARIANT vViewName;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    lONr = 0;
    rgType = 0;
    _p_vViewName = &vViewName;
    MIDL_memset(
               _p_vViewName,
               0,
               sizeof( VARIANT  ));
    ( DVisInfo ** )ppIVisInfo = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[0] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        
        if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
            {
            RpcRaiseException(RPC_X_BAD_STUB_DATA);
            }
        lONr = *(( long * )_StubMsg.Buffer)++;
        
        NdrSimpleTypeUnmarshall(
                           ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                           ( unsigned char * )&rgType,
                           13);
        NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&_p_vViewName,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[994],
                                  (unsigned char)0 );
        
        ppIVisInfo = &_M1;
        _M1 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IVisObjExt*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> GetVisInfoObject(
                    (IVisObjExt *) ((CStdStubBuffer *)This)->pvServerObject,
                    lONr,
                    rgType,
                    vViewName,
                    ppIVisInfo);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char *)ppIVisInfo,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1004] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char *)ppIVisInfo,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1004] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrUserMarshalFree( &_StubMsg,
                            (unsigned char *)&vViewName,
                            &__MIDL_TypeFormatString.Format[994] );
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char *)ppIVisInfo,
                        &__MIDL_TypeFormatString.Format[1004] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVisObjExt_SetVisInfoObject_Proxy( 
    IVisObjExt * This,
    /* [in] */ long lONr,
    /* [in] */ VISINFOTYPE rgType,
    /* [in] */ DVisInfo *pIVisInfo,
    /* [in] */ VARIANT_BOOL fSameAsSource,
    /* [optional][in] */ VARIANT vViewName)
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
            
            _StubMsg.BufferLength = 20;
            NdrInterfacePointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                           (unsigned char *)pIVisInfo,
                                           (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1008] );
            
            NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char *)&vViewName,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[994] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            *(( long * )_StubMsg.Buffer)++ = lONr;
            
            NdrSimpleTypeMarshall(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( unsigned char * )&rgType,
                         13);
            NdrInterfacePointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                         (unsigned char *)pIVisInfo,
                                         (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1008] );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 1) & ~ 0x1);
            *(( VARIANT_BOOL * )_StubMsg.Buffer)++ = fSameAsSource;
            
            NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                    (unsigned char *)&vViewName,
                                    (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[994] );
            
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

void __RPC_STUB IVisObjExt_SetVisInfoObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    void *_p_vViewName;
    VARIANT_BOOL fSameAsSource;
    long lONr;
    DVisInfo *pIVisInfo;
    VISINFOTYPE rgType;
    VARIANT vViewName;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    lONr = 0;
    rgType = 0;
    pIVisInfo = 0;
    fSameAsSource = 0;
    _p_vViewName = &vViewName;
    MIDL_memset(
               _p_vViewName,
               0,
               sizeof( VARIANT  ));
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[38] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        
        if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
            {
            RpcRaiseException(RPC_X_BAD_STUB_DATA);
            }
        lONr = *(( long * )_StubMsg.Buffer)++;
        
        NdrSimpleTypeUnmarshall(
                           ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                           ( unsigned char * )&rgType,
                           13);
        NdrInterfacePointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char * *)&pIVisInfo,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1008],
                                       (unsigned char)0 );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 1) & ~ 0x1);
        
        if(_StubMsg.Buffer + 2 > _StubMsg.BufferEnd)
            {
            RpcRaiseException(RPC_X_BAD_STUB_DATA);
            }
        fSameAsSource = *(( VARIANT_BOOL * )_StubMsg.Buffer)++;
        
        NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&_p_vViewName,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[994],
                                  (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IVisObjExt*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> SetVisInfoObject(
                    (IVisObjExt *) ((CStdStubBuffer *)This)->pvServerObject,
                    lONr,
                    rgType,
                    pIVisInfo,
                    fSameAsSource,
                    vViewName);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrInterfacePointerFree( &_StubMsg,
                                 (unsigned char *)pIVisInfo,
                                 &__MIDL_TypeFormatString.Format[1008] );
        
        NdrUserMarshalFree( &_StubMsg,
                            (unsigned char *)&vViewName,
                            &__MIDL_TypeFormatString.Format[994] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVisObjExt_ResetVisInfoObject_Proxy( 
    IVisObjExt * This,
    /* [in] */ long lONr,
    /* [in] */ VISINFOTYPE rgType,
    /* [optional][in] */ VARIANT vViewName)
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
            
            _StubMsg.BufferLength = 14;
            NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char *)&vViewName,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[994] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            *(( long * )_StubMsg.Buffer)++ = lONr;
            
            NdrSimpleTypeMarshall(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( unsigned char * )&rgType,
                         13);
            NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                    (unsigned char *)&vViewName,
                                    (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[994] );
            
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

void __RPC_STUB IVisObjExt_ResetVisInfoObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    void *_p_vViewName;
    long lONr;
    VISINFOTYPE rgType;
    VARIANT vViewName;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    lONr = 0;
    rgType = 0;
    _p_vViewName = &vViewName;
    MIDL_memset(
               _p_vViewName,
               0,
               sizeof( VARIANT  ));
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[28] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        
        if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
            {
            RpcRaiseException(RPC_X_BAD_STUB_DATA);
            }
        lONr = *(( long * )_StubMsg.Buffer)++;
        
        NdrSimpleTypeUnmarshall(
                           ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                           ( unsigned char * )&rgType,
                           13);
        NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&_p_vViewName,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[994],
                                  (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IVisObjExt*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> ResetVisInfoObject(
                      (IVisObjExt *) ((CStdStubBuffer *)This)->pvServerObject,
                      lONr,
                      rgType,
                      vViewName);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrUserMarshalFree( &_StubMsg,
                            (unsigned char *)&vViewName,
                            &__MIDL_TypeFormatString.Format[994] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVisObjExt_GetObjectHiddenStatus_Proxy( 
    IVisObjExt * This,
    /* [in] */ long lONr,
    /* [optional][in] */ VARIANT vViewName,
    /* [retval][out] */ VARIANT_BOOL *pfShow)
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
        
        
        
        if(!pfShow)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 8;
            NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char *)&vViewName,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[994] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            *(( long * )_StubMsg.Buffer)++ = lONr;
            
            NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                    (unsigned char *)&vViewName,
                                    (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[994] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[54] );
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 1) & ~ 0x1);
            *pfShow = *(( VARIANT_BOOL * )_StubMsg.Buffer)++;
            
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[1026],
                         ( void * )pfShow);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IVisObjExt_GetObjectHiddenStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    VARIANT_BOOL _M2	=	0;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    void *_p_vViewName;
    long lONr;
    VARIANT_BOOL *pfShow;
    VARIANT vViewName;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    lONr = 0;
    _p_vViewName = &vViewName;
    MIDL_memset(
               _p_vViewName,
               0,
               sizeof( VARIANT  ));
    ( VARIANT_BOOL * )pfShow = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[54] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        
        if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
            {
            RpcRaiseException(RPC_X_BAD_STUB_DATA);
            }
        lONr = *(( long * )_StubMsg.Buffer)++;
        
        NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&_p_vViewName,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[994],
                                  (unsigned char)0 );
        
        pfShow = &_M2;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IVisObjExt*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> GetObjectHiddenStatus(
                         (IVisObjExt *) ((CStdStubBuffer *)This)->pvServerObject,
                         lONr,
                         vViewName,
                         pfShow);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 34;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 1) & ~ 0x1);
        *(( VARIANT_BOOL * )_StubMsg.Buffer)++ = *pfShow;
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrUserMarshalFree( &_StubMsg,
                            (unsigned char *)&vViewName,
                            &__MIDL_TypeFormatString.Format[994] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVisObjExt_SetObjectHiddenStatus_Proxy( 
    IVisObjExt * This,
    /* [in] */ long lONr,
    /* [in] */ VARIANT_BOOL fShow,
    /* [optional][in] */ VARIANT vViewName)
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
            
            _StubMsg.BufferLength = 14;
            NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char *)&vViewName,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[994] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            *(( long * )_StubMsg.Buffer)++ = lONr;
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 1) & ~ 0x1);
            *(( VARIANT_BOOL * )_StubMsg.Buffer)++ = fShow;
            
            NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                    (unsigned char *)&vViewName,
                                    (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[994] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[66] );
            
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

void __RPC_STUB IVisObjExt_SetObjectHiddenStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    void *_p_vViewName;
    VARIANT_BOOL fShow;
    long lONr;
    VARIANT vViewName;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    lONr = 0;
    fShow = 0;
    _p_vViewName = &vViewName;
    MIDL_memset(
               _p_vViewName,
               0,
               sizeof( VARIANT  ));
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[66] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        
        if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
            {
            RpcRaiseException(RPC_X_BAD_STUB_DATA);
            }
        lONr = *(( long * )_StubMsg.Buffer)++;
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 1) & ~ 0x1);
        
        if(_StubMsg.Buffer + 2 > _StubMsg.BufferEnd)
            {
            RpcRaiseException(RPC_X_BAD_STUB_DATA);
            }
        fShow = *(( VARIANT_BOOL * )_StubMsg.Buffer)++;
        
        NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&_p_vViewName,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[994],
                                  (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IVisObjExt*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> SetObjectHiddenStatus(
                         (IVisObjExt *) ((CStdStubBuffer *)This)->pvServerObject,
                         lONr,
                         fShow,
                         vViewName);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrUserMarshalFree( &_StubMsg,
                            (unsigned char *)&vViewName,
                            &__MIDL_TypeFormatString.Format[994] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IVisQuery_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IVisQuery_ProxyInfo;


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVisQuery_GetIdentMode_Proxy( 
    IVisQuery * This,
    /* [in] */ LONG Ident,
    BSTR View,
    /* [out][in] */ IDENTVISMODE *VisMode)
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
        
        
        
        if(!VisMode)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 34;
            NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char *)&View,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1030] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            *(( LONG * )_StubMsg.Buffer)++ = Ident;
            
            NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                    (unsigned char *)&View,
                                    (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1030] );
            
            NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                (unsigned char *)VisMode,
                                (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1040] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[76] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&VisMode,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1040],
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[1040],
                         ( void * )VisMode);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IVisQuery_GetIdentMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    LONG Ident;
    BSTR View;
    IDENTVISMODE *VisMode;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    void *_p_View;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    Ident = 0;
    _p_View = &View;
    MIDL_memset(
               _p_View,
               0,
               sizeof( BSTR  ));
    ( IDENTVISMODE * )VisMode = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[76] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        
        if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
            {
            RpcRaiseException(RPC_X_BAD_STUB_DATA);
            }
        Ident = *(( LONG * )_StubMsg.Buffer)++;
        
        NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&_p_View,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1030],
                                  (unsigned char)0 );
        
        NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char * *)&VisMode,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1040],
                              (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IVisQuery*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> GetIdentMode(
                (IVisQuery *) ((CStdStubBuffer *)This)->pvServerObject,
                Ident,
                View,
                VisMode);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 34;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char *)VisMode,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1040] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrUserMarshalFree( &_StubMsg,
                            (unsigned char *)&View,
                            &__MIDL_TypeFormatString.Format[1030] );
        
        if ( VisMode )
            _StubMsg.pfnFree( VisMode );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVisQuery_GetObjectVis_Proxy( 
    IVisQuery * This,
    /* [in] */ LONG ObjNr,
    /* [out][in] */ DVisInfo **Vis)
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
        
        
        
        if(!Vis)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 8;
            NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char *)Vis,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1044] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            *(( LONG * )_StubMsg.Buffer)++ = ObjNr;
            
            NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                (unsigned char *)Vis,
                                (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1044] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[88] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&Vis,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1044],
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[1044],
                         ( void * )Vis);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IVisQuery_GetObjectVis_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    LONG ObjNr;
    DVisInfo **Vis;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ObjNr = 0;
    ( DVisInfo ** )Vis = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[88] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        
        if(_StubMsg.Buffer + 4 > _StubMsg.BufferEnd)
            {
            RpcRaiseException(RPC_X_BAD_STUB_DATA);
            }
        ObjNr = *(( LONG * )_StubMsg.Buffer)++;
        
        NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char * *)&Vis,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1044],
                              (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IVisQuery*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> GetObjectVis(
                (IVisQuery *) ((CStdStubBuffer *)This)->pvServerObject,
                ObjNr,
                Vis);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char *)Vis,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1044] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char *)Vis,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1044] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char *)Vis,
                        &__MIDL_TypeFormatString.Format[1044] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IMergeVisInfo_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IMergeVisInfo_ProxyInfo;


HRESULT STDMETHODCALLTYPE IMergeVisInfo_MergeVisInfo_Proxy( 
    IMergeVisInfo * This,
    /* [in] */ VARIANT_BOOL OnlyChanged,
    /* [out][in] */ DVisInfo **VisInfo)
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
        
        
        
        if(!VisInfo)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 6;
            NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char *)VisInfo,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1044] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 1) & ~ 0x1);
            *(( VARIANT_BOOL * )_StubMsg.Buffer)++ = OnlyChanged;
            
            NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                (unsigned char *)VisInfo,
                                (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1044] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[96] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&VisInfo,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1044],
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[1044],
                         ( void * )VisInfo);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IMergeVisInfo_MergeVisInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    VARIANT_BOOL OnlyChanged;
    DVisInfo **VisInfo;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    OnlyChanged = 0;
    ( DVisInfo ** )VisInfo = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[96] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 1) & ~ 0x1);
        
        if(_StubMsg.Buffer + 2 > _StubMsg.BufferEnd)
            {
            RpcRaiseException(RPC_X_BAD_STUB_DATA);
            }
        OnlyChanged = *(( VARIANT_BOOL * )_StubMsg.Buffer)++;
        
        NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char * *)&VisInfo,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1044],
                              (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IMergeVisInfo*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> MergeVisInfo(
                (IMergeVisInfo *) ((CStdStubBuffer *)This)->pvServerObject,
                OnlyChanged,
                VisInfo);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char *)VisInfo,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1044] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char *)VisInfo,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1044] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char *)VisInfo,
                        &__MIDL_TypeFormatString.Format[1044] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRawVisInfo_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRawVisInfo_ProxyInfo;


HRESULT STDMETHODCALLTYPE IRawVisInfo_SetRawData_Proxy( 
    IRawVisInfo * This,
    /* [in] */ VISINFOTYPE rgType,
    /* [in] */ BSTR Data)
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
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 6;
            NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char *)&Data,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1030] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrSimpleTypeMarshall(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( unsigned char * )&rgType,
                         13);
            NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                    (unsigned char *)&Data,
                                    (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1030] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[104] );
            
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

void __RPC_STUB IRawVisInfo_SetRawData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    BSTR Data;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    void *_p_Data;
    VISINFOTYPE rgType;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    rgType = 0;
    _p_Data = &Data;
    MIDL_memset(
               _p_Data,
               0,
               sizeof( BSTR  ));
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[104] );
        
        NdrSimpleTypeUnmarshall(
                           ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                           ( unsigned char * )&rgType,
                           13);
        NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&_p_Data,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1030],
                                  (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IRawVisInfo*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> SetRawData(
              (IRawVisInfo *) ((CStdStubBuffer *)This)->pvServerObject,
              rgType,
              Data);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrUserMarshalFree( &_StubMsg,
                            (unsigned char *)&Data,
                            &__MIDL_TypeFormatString.Format[1030] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


HRESULT STDMETHODCALLTYPE IRawVisInfo_RetrieveRawData_Proxy( 
    IRawVisInfo * This,
    /* [in] */ VISINFOTYPE rgType,
    /* [retval][out] */ BSTR *Data)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(Data)
        {
        MIDL_memset(
               Data,
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
        
        
        
        if(!Data)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 6;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrSimpleTypeMarshall(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( unsigned char * )&rgType,
                         13);
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[112] );
            
            NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char * *)&Data,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1056],
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[1048],
                         ( void * )Data);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IRawVisInfo_RetrieveRawData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    BSTR *Data;
    BSTR _M3;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    VISINFOTYPE rgType;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    rgType = 0;
    ( BSTR * )Data = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[112] );
        
        NdrSimpleTypeUnmarshall(
                           ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                           ( unsigned char * )&rgType,
                           13);
        Data = &_M3;
        MIDL_memset(
               Data,
               0,
               sizeof( BSTR  ));
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IRawVisInfo*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> RetrieveRawData(
                   (IRawVisInfo *) ((CStdStubBuffer *)This)->pvServerObject,
                   rgType,
                   Data);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char *)Data,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1056] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                (unsigned char *)Data,
                                (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1056] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char *)Data,
                        &__MIDL_TypeFormatString.Format[1048] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IExtendedObjectVisInfo_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IExtendedObjectVisInfo_ProxyInfo;


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IExtendedObjectVisInfo_get_HasInfos_Proxy( 
    IExtendedObjectVisInfo * This,
    /* [retval][out] */ VARIANT_BOOL *HasInfos)
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
        
        
        
        if(!HasInfos)
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
            
            _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 1) & ~ 0x1);
            *HasInfos = *(( VARIANT_BOOL * )_StubMsg.Buffer)++;
            
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[1026],
                         ( void * )HasInfos);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IExtendedObjectVisInfo_get_HasInfos_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    VARIANT_BOOL *HasInfos;
    VARIANT_BOOL _M4	=	0;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( VARIANT_BOOL * )HasInfos = 0;
    RpcTryFinally
        {
        HasInfos = &_M4;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IExtendedObjectVisInfo*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_HasInfos((IExtendedObjectVisInfo *) ((CStdStubBuffer *)This)->pvServerObject,HasInfos);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 34;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 1) & ~ 0x1);
        *(( VARIANT_BOOL * )_StubMsg.Buffer)++ = *HasInfos;
        
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


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IExtendedObjectVisInfo_get_ModuleInfo_Proxy( 
    IExtendedObjectVisInfo * This,
    /* [retval][out] */ BSTR *ModuleName)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(ModuleName)
        {
        MIDL_memset(
               ModuleName,
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
        
        
        
        if(!ModuleName)
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
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[126] );
            
            NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char * *)&ModuleName,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1056],
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[1048],
                         ( void * )ModuleName);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IExtendedObjectVisInfo_get_ModuleInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    BSTR *ModuleName;
    BSTR _M5;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( BSTR * )ModuleName = 0;
    RpcTryFinally
        {
        ModuleName = &_M5;
        MIDL_memset(
               ModuleName,
               0,
               sizeof( BSTR  ));
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IExtendedObjectVisInfo*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_ModuleInfo((IExtendedObjectVisInfo *) ((CStdStubBuffer *)This)->pvServerObject,ModuleName);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char *)ModuleName,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1056] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                (unsigned char *)ModuleName,
                                (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1056] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char *)ModuleName,
                        &__MIDL_TypeFormatString.Format[1048] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IExtendedObjectVisInfo_put_ModuleInfo_Proxy( 
    IExtendedObjectVisInfo * This,
    /* [in] */ BSTR ModuleName)
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
                                      (unsigned char *)&ModuleName,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1030] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                    (unsigned char *)&ModuleName,
                                    (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1030] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[132] );
            
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

void __RPC_STUB IExtendedObjectVisInfo_put_ModuleInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    BSTR ModuleName;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    void *_p_ModuleName;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    _p_ModuleName = &ModuleName;
    MIDL_memset(
               _p_ModuleName,
               0,
               sizeof( BSTR  ));
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[132] );
        
        NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&_p_ModuleName,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1030],
                                  (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IExtendedObjectVisInfo*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> put_ModuleInfo((IExtendedObjectVisInfo *) ((CStdStubBuffer *)This)->pvServerObject,ModuleName);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrUserMarshalFree( &_StubMsg,
                            (unsigned char *)&ModuleName,
                            &__MIDL_TypeFormatString.Format[1030] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IExtendedObjectVisInfo_get_ExtendedInfo_Proxy( 
    IExtendedObjectVisInfo * This,
    /* [retval][out] */ BSTR *VisString)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(VisString)
        {
        MIDL_memset(
               VisString,
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
                      6);
        
        
        
        if(!VisString)
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
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[126] );
            
            NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char * *)&VisString,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1056],
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[1048],
                         ( void * )VisString);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IExtendedObjectVisInfo_get_ExtendedInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    BSTR *VisString;
    BSTR _M6;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( BSTR * )VisString = 0;
    RpcTryFinally
        {
        VisString = &_M6;
        MIDL_memset(
               VisString,
               0,
               sizeof( BSTR  ));
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IExtendedObjectVisInfo*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_ExtendedInfo((IExtendedObjectVisInfo *) ((CStdStubBuffer *)This)->pvServerObject,VisString);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char *)VisString,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1056] );
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                (unsigned char *)VisString,
                                (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1056] );
        
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char *)VisString,
                        &__MIDL_TypeFormatString.Format[1048] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)(_StubMsg.Buffer - (unsigned char *)_pRpcMessage->Buffer);
    
}


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IExtendedObjectVisInfo_put_ExtendedInfo_Proxy( 
    IExtendedObjectVisInfo * This,
    /* [in] */ BSTR VisString)
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
            NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char *)&VisString,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1030] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                    (unsigned char *)&VisString,
                                    (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1030] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            _StubMsg.BufferStart = (unsigned char *) _RpcMessage.Buffer; 
            _StubMsg.BufferEnd   = _StubMsg.BufferStart + _RpcMessage.BufferLength;
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[132] );
            
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

void __RPC_STUB IExtendedObjectVisInfo_put_ExtendedInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    BSTR VisString;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    void *_p_VisString;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    _p_VisString = &VisString;
    MIDL_memset(
               _p_VisString,
               0,
               sizeof( BSTR  ));
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[132] );
        
        NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char * *)&_p_VisString,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1030],
                                  (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IExtendedObjectVisInfo*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> put_ExtendedInfo((IExtendedObjectVisInfo *) ((CStdStubBuffer *)This)->pvServerObject,VisString);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.Buffer = (unsigned char *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrUserMarshalFree( &_StubMsg,
                            (unsigned char *)&VisString,
                            &__MIDL_TypeFormatString.Format[1030] );
        
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
			0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/*  2 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0xd,		/* FC_ENUM16 */
/*  4 */	
			0x4d,		/* FC_IN_PARAM */
			0x4,		/* x86 stack size = 4 */
/*  6 */	NdrFcShort( 0x3e2 ),	/* Type Offset=994 */
/*  8 */	
			0x51,		/* FC_OUT_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 10 */	NdrFcShort( 0x3ec ),	/* Type Offset=1004 */
/* 12 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 14 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 16 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0xd,		/* FC_ENUM16 */
/* 18 */	
			0x4d,		/* FC_IN_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 20 */	NdrFcShort( 0x3f0 ),	/* Type Offset=1008 */
/* 22 */	
			0x4d,		/* FC_IN_PARAM */
			0x4,		/* x86 stack size = 4 */
/* 24 */	NdrFcShort( 0x3e2 ),	/* Type Offset=994 */
/* 26 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 28 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 30 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0xd,		/* FC_ENUM16 */
/* 32 */	
			0x4d,		/* FC_IN_PARAM */
			0x4,		/* x86 stack size = 4 */
/* 34 */	NdrFcShort( 0x3e2 ),	/* Type Offset=994 */
/* 36 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 38 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 40 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0xd,		/* FC_ENUM16 */
/* 42 */	
			0x4d,		/* FC_IN_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 44 */	NdrFcShort( 0x3f0 ),	/* Type Offset=1008 */
/* 46 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x6,		/* FC_SHORT */
/* 48 */	
			0x4d,		/* FC_IN_PARAM */
			0x4,		/* x86 stack size = 4 */
/* 50 */	NdrFcShort( 0x3e2 ),	/* Type Offset=994 */
/* 52 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 54 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 56 */	
			0x4d,		/* FC_IN_PARAM */
			0x4,		/* x86 stack size = 4 */
/* 58 */	NdrFcShort( 0x3e2 ),	/* Type Offset=994 */
/* 60 */	
			0x51,		/* FC_OUT_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 62 */	NdrFcShort( 0x402 ),	/* Type Offset=1026 */
/* 64 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 66 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 68 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x6,		/* FC_SHORT */
/* 70 */	
			0x4d,		/* FC_IN_PARAM */
			0x4,		/* x86 stack size = 4 */
/* 72 */	NdrFcShort( 0x3e2 ),	/* Type Offset=994 */
/* 74 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 76 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 78 */	
			0x4d,		/* FC_IN_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 80 */	NdrFcShort( 0x406 ),	/* Type Offset=1030 */
/* 82 */	
			0x50,		/* FC_IN_OUT_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 84 */	NdrFcShort( 0x410 ),	/* Type Offset=1040 */
/* 86 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 88 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 90 */	
			0x50,		/* FC_IN_OUT_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 92 */	NdrFcShort( 0x414 ),	/* Type Offset=1044 */
/* 94 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 96 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x6,		/* FC_SHORT */
/* 98 */	
			0x50,		/* FC_IN_OUT_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 100 */	NdrFcShort( 0x414 ),	/* Type Offset=1044 */
/* 102 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 104 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0xd,		/* FC_ENUM16 */
/* 106 */	
			0x4d,		/* FC_IN_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 108 */	NdrFcShort( 0x406 ),	/* Type Offset=1030 */
/* 110 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 112 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0xd,		/* FC_ENUM16 */
/* 114 */	
			0x51,		/* FC_OUT_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 116 */	NdrFcShort( 0x418 ),	/* Type Offset=1048 */
/* 118 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 120 */	
			0x51,		/* FC_OUT_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 122 */	NdrFcShort( 0x402 ),	/* Type Offset=1026 */
/* 124 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 126 */	
			0x51,		/* FC_OUT_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 128 */	NdrFcShort( 0x418 ),	/* Type Offset=1048 */
/* 130 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 132 */	
			0x4d,		/* FC_IN_PARAM */
			0x1,		/* x86 stack size = 1 */
/* 134 */	NdrFcShort( 0x406 ),	/* Type Offset=1030 */
/* 136 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
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
			0x12, 0x0,	/* FC_UP */
/*  4 */	NdrFcShort( 0x3ca ),	/* Offset= 970 (974) */
/*  6 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/*  8 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 10 */	NdrFcShort( 0xfff8 ),	/* -8 */
/* 12 */	NdrFcShort( 0x2 ),	/* Offset= 2 (14) */
/* 14 */	NdrFcShort( 0x10 ),	/* 16 */
/* 16 */	NdrFcShort( 0x2f ),	/* 47 */
/* 18 */	NdrFcLong( 0x14 ),	/* 20 */
/* 22 */	NdrFcShort( 0x800b ),	/* Simple arm type: FC_HYPER */
/* 24 */	NdrFcLong( 0x3 ),	/* 3 */
/* 28 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 30 */	NdrFcLong( 0x11 ),	/* 17 */
/* 34 */	NdrFcShort( 0x8001 ),	/* Simple arm type: FC_BYTE */
/* 36 */	NdrFcLong( 0x2 ),	/* 2 */
/* 40 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 42 */	NdrFcLong( 0x4 ),	/* 4 */
/* 46 */	NdrFcShort( 0x800a ),	/* Simple arm type: FC_FLOAT */
/* 48 */	NdrFcLong( 0x5 ),	/* 5 */
/* 52 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 54 */	NdrFcLong( 0xb ),	/* 11 */
/* 58 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 60 */	NdrFcLong( 0xa ),	/* 10 */
/* 64 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 66 */	NdrFcLong( 0x6 ),	/* 6 */
/* 70 */	NdrFcShort( 0xe8 ),	/* Offset= 232 (302) */
/* 72 */	NdrFcLong( 0x7 ),	/* 7 */
/* 76 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 78 */	NdrFcLong( 0x8 ),	/* 8 */
/* 82 */	NdrFcShort( 0xe2 ),	/* Offset= 226 (308) */
/* 84 */	NdrFcLong( 0xd ),	/* 13 */
/* 88 */	NdrFcShort( 0xf4 ),	/* Offset= 244 (332) */
/* 90 */	NdrFcLong( 0x9 ),	/* 9 */
/* 94 */	NdrFcShort( 0x100 ),	/* Offset= 256 (350) */
/* 96 */	NdrFcLong( 0x2000 ),	/* 8192 */
/* 100 */	NdrFcShort( 0x10c ),	/* Offset= 268 (368) */
/* 102 */	NdrFcLong( 0x24 ),	/* 36 */
/* 106 */	NdrFcShort( 0x31a ),	/* Offset= 794 (900) */
/* 108 */	NdrFcLong( 0x4024 ),	/* 16420 */
/* 112 */	NdrFcShort( 0x314 ),	/* Offset= 788 (900) */
/* 114 */	NdrFcLong( 0x4011 ),	/* 16401 */
/* 118 */	NdrFcShort( 0x312 ),	/* Offset= 786 (904) */
/* 120 */	NdrFcLong( 0x4002 ),	/* 16386 */
/* 124 */	NdrFcShort( 0x310 ),	/* Offset= 784 (908) */
/* 126 */	NdrFcLong( 0x4003 ),	/* 16387 */
/* 130 */	NdrFcShort( 0x30e ),	/* Offset= 782 (912) */
/* 132 */	NdrFcLong( 0x4014 ),	/* 16404 */
/* 136 */	NdrFcShort( 0x30c ),	/* Offset= 780 (916) */
/* 138 */	NdrFcLong( 0x4004 ),	/* 16388 */
/* 142 */	NdrFcShort( 0x30a ),	/* Offset= 778 (920) */
/* 144 */	NdrFcLong( 0x4005 ),	/* 16389 */
/* 148 */	NdrFcShort( 0x308 ),	/* Offset= 776 (924) */
/* 150 */	NdrFcLong( 0x400b ),	/* 16395 */
/* 154 */	NdrFcShort( 0x2f2 ),	/* Offset= 754 (908) */
/* 156 */	NdrFcLong( 0x400a ),	/* 16394 */
/* 160 */	NdrFcShort( 0x2f0 ),	/* Offset= 752 (912) */
/* 162 */	NdrFcLong( 0x4006 ),	/* 16390 */
/* 166 */	NdrFcShort( 0x2fa ),	/* Offset= 762 (928) */
/* 168 */	NdrFcLong( 0x4007 ),	/* 16391 */
/* 172 */	NdrFcShort( 0x2f0 ),	/* Offset= 752 (924) */
/* 174 */	NdrFcLong( 0x4008 ),	/* 16392 */
/* 178 */	NdrFcShort( 0x2f2 ),	/* Offset= 754 (932) */
/* 180 */	NdrFcLong( 0x400d ),	/* 16397 */
/* 184 */	NdrFcShort( 0x2f0 ),	/* Offset= 752 (936) */
/* 186 */	NdrFcLong( 0x4009 ),	/* 16393 */
/* 190 */	NdrFcShort( 0x2ee ),	/* Offset= 750 (940) */
/* 192 */	NdrFcLong( 0x6000 ),	/* 24576 */
/* 196 */	NdrFcShort( 0x2ec ),	/* Offset= 748 (944) */
/* 198 */	NdrFcLong( 0x400c ),	/* 16396 */
/* 202 */	NdrFcShort( 0x2ea ),	/* Offset= 746 (948) */
/* 204 */	NdrFcLong( 0x10 ),	/* 16 */
/* 208 */	NdrFcShort( 0x8002 ),	/* Simple arm type: FC_CHAR */
/* 210 */	NdrFcLong( 0x12 ),	/* 18 */
/* 214 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 216 */	NdrFcLong( 0x13 ),	/* 19 */
/* 220 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 222 */	NdrFcLong( 0x15 ),	/* 21 */
/* 226 */	NdrFcShort( 0x800b ),	/* Simple arm type: FC_HYPER */
/* 228 */	NdrFcLong( 0x16 ),	/* 22 */
/* 232 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 234 */	NdrFcLong( 0x17 ),	/* 23 */
/* 238 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 240 */	NdrFcLong( 0xe ),	/* 14 */
/* 244 */	NdrFcShort( 0x2c8 ),	/* Offset= 712 (956) */
/* 246 */	NdrFcLong( 0x400e ),	/* 16398 */
/* 250 */	NdrFcShort( 0x2cc ),	/* Offset= 716 (966) */
/* 252 */	NdrFcLong( 0x4010 ),	/* 16400 */
/* 256 */	NdrFcShort( 0x2ca ),	/* Offset= 714 (970) */
/* 258 */	NdrFcLong( 0x4012 ),	/* 16402 */
/* 262 */	NdrFcShort( 0x286 ),	/* Offset= 646 (908) */
/* 264 */	NdrFcLong( 0x4013 ),	/* 16403 */
/* 268 */	NdrFcShort( 0x284 ),	/* Offset= 644 (912) */
/* 270 */	NdrFcLong( 0x4015 ),	/* 16405 */
/* 274 */	NdrFcShort( 0x282 ),	/* Offset= 642 (916) */
/* 276 */	NdrFcLong( 0x4016 ),	/* 16406 */
/* 280 */	NdrFcShort( 0x278 ),	/* Offset= 632 (912) */
/* 282 */	NdrFcLong( 0x4017 ),	/* 16407 */
/* 286 */	NdrFcShort( 0x272 ),	/* Offset= 626 (912) */
/* 288 */	NdrFcLong( 0x0 ),	/* 0 */
/* 292 */	NdrFcShort( 0x0 ),	/* Offset= 0 (292) */
/* 294 */	NdrFcLong( 0x1 ),	/* 1 */
/* 298 */	NdrFcShort( 0x0 ),	/* Offset= 0 (298) */
/* 300 */	NdrFcShort( 0xffffffff ),	/* Offset= -1 (299) */
/* 302 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 304 */	NdrFcShort( 0x8 ),	/* 8 */
/* 306 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 308 */	
			0x12, 0x0,	/* FC_UP */
/* 310 */	NdrFcShort( 0xc ),	/* Offset= 12 (322) */
/* 312 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 314 */	NdrFcShort( 0x2 ),	/* 2 */
/* 316 */	0x9,		/* Corr desc: FC_ULONG */
			0x0,		/*  */
/* 318 */	NdrFcShort( 0xfffc ),	/* -4 */
/* 320 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 322 */	
			0x17,		/* FC_CSTRUCT */
			0x3,		/* 3 */
/* 324 */	NdrFcShort( 0x8 ),	/* 8 */
/* 326 */	NdrFcShort( 0xfffffff2 ),	/* Offset= -14 (312) */
/* 328 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 330 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 332 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 334 */	NdrFcLong( 0x0 ),	/* 0 */
/* 338 */	NdrFcShort( 0x0 ),	/* 0 */
/* 340 */	NdrFcShort( 0x0 ),	/* 0 */
/* 342 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 344 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 346 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 348 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 350 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 352 */	NdrFcLong( 0x20400 ),	/* 132096 */
/* 356 */	NdrFcShort( 0x0 ),	/* 0 */
/* 358 */	NdrFcShort( 0x0 ),	/* 0 */
/* 360 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 362 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 364 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 366 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 368 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 370 */	NdrFcShort( 0x2 ),	/* Offset= 2 (372) */
/* 372 */	
			0x12, 0x0,	/* FC_UP */
/* 374 */	NdrFcShort( 0x1fc ),	/* Offset= 508 (882) */
/* 376 */	
			0x2a,		/* FC_ENCAPSULATED_UNION */
			0x49,		/* 73 */
/* 378 */	NdrFcShort( 0x18 ),	/* 24 */
/* 380 */	NdrFcShort( 0xa ),	/* 10 */
/* 382 */	NdrFcLong( 0x8 ),	/* 8 */
/* 386 */	NdrFcShort( 0x58 ),	/* Offset= 88 (474) */
/* 388 */	NdrFcLong( 0xd ),	/* 13 */
/* 392 */	NdrFcShort( 0x78 ),	/* Offset= 120 (512) */
/* 394 */	NdrFcLong( 0x9 ),	/* 9 */
/* 398 */	NdrFcShort( 0x94 ),	/* Offset= 148 (546) */
/* 400 */	NdrFcLong( 0xc ),	/* 12 */
/* 404 */	NdrFcShort( 0xbc ),	/* Offset= 188 (592) */
/* 406 */	NdrFcLong( 0x24 ),	/* 36 */
/* 410 */	NdrFcShort( 0x114 ),	/* Offset= 276 (686) */
/* 412 */	NdrFcLong( 0x800d ),	/* 32781 */
/* 416 */	NdrFcShort( 0x130 ),	/* Offset= 304 (720) */
/* 418 */	NdrFcLong( 0x10 ),	/* 16 */
/* 422 */	NdrFcShort( 0x148 ),	/* Offset= 328 (750) */
/* 424 */	NdrFcLong( 0x2 ),	/* 2 */
/* 428 */	NdrFcShort( 0x160 ),	/* Offset= 352 (780) */
/* 430 */	NdrFcLong( 0x3 ),	/* 3 */
/* 434 */	NdrFcShort( 0x178 ),	/* Offset= 376 (810) */
/* 436 */	NdrFcLong( 0x14 ),	/* 20 */
/* 440 */	NdrFcShort( 0x190 ),	/* Offset= 400 (840) */
/* 442 */	NdrFcShort( 0xffffffff ),	/* Offset= -1 (441) */
/* 444 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 446 */	NdrFcShort( 0x4 ),	/* 4 */
/* 448 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 450 */	NdrFcShort( 0x0 ),	/* 0 */
/* 452 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 454 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 456 */	NdrFcShort( 0x4 ),	/* 4 */
/* 458 */	NdrFcShort( 0x0 ),	/* 0 */
/* 460 */	NdrFcShort( 0x1 ),	/* 1 */
/* 462 */	NdrFcShort( 0x0 ),	/* 0 */
/* 464 */	NdrFcShort( 0x0 ),	/* 0 */
/* 466 */	0x12, 0x0,	/* FC_UP */
/* 468 */	NdrFcShort( 0xffffff6e ),	/* Offset= -146 (322) */
/* 470 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 472 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 474 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 476 */	NdrFcShort( 0x8 ),	/* 8 */
/* 478 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 480 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 482 */	NdrFcShort( 0x4 ),	/* 4 */
/* 484 */	NdrFcShort( 0x4 ),	/* 4 */
/* 486 */	0x11, 0x0,	/* FC_RP */
/* 488 */	NdrFcShort( 0xffffffd4 ),	/* Offset= -44 (444) */
/* 490 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 492 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 494 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 496 */	NdrFcShort( 0x0 ),	/* 0 */
/* 498 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 500 */	NdrFcShort( 0x0 ),	/* 0 */
/* 502 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 506 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 508 */	NdrFcShort( 0xffffff50 ),	/* Offset= -176 (332) */
/* 510 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 512 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 514 */	NdrFcShort( 0x8 ),	/* 8 */
/* 516 */	NdrFcShort( 0x0 ),	/* 0 */
/* 518 */	NdrFcShort( 0x6 ),	/* Offset= 6 (524) */
/* 520 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 522 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 524 */	
			0x11, 0x0,	/* FC_RP */
/* 526 */	NdrFcShort( 0xffffffe0 ),	/* Offset= -32 (494) */
/* 528 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 530 */	NdrFcShort( 0x0 ),	/* 0 */
/* 532 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 534 */	NdrFcShort( 0x0 ),	/* 0 */
/* 536 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 540 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 542 */	NdrFcShort( 0xffffff40 ),	/* Offset= -192 (350) */
/* 544 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 546 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 548 */	NdrFcShort( 0x8 ),	/* 8 */
/* 550 */	NdrFcShort( 0x0 ),	/* 0 */
/* 552 */	NdrFcShort( 0x6 ),	/* Offset= 6 (558) */
/* 554 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 556 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 558 */	
			0x11, 0x0,	/* FC_RP */
/* 560 */	NdrFcShort( 0xffffffe0 ),	/* Offset= -32 (528) */
/* 562 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 564 */	NdrFcShort( 0x4 ),	/* 4 */
/* 566 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 568 */	NdrFcShort( 0x0 ),	/* 0 */
/* 570 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 572 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 574 */	NdrFcShort( 0x4 ),	/* 4 */
/* 576 */	NdrFcShort( 0x0 ),	/* 0 */
/* 578 */	NdrFcShort( 0x1 ),	/* 1 */
/* 580 */	NdrFcShort( 0x0 ),	/* 0 */
/* 582 */	NdrFcShort( 0x0 ),	/* 0 */
/* 584 */	0x12, 0x0,	/* FC_UP */
/* 586 */	NdrFcShort( 0x184 ),	/* Offset= 388 (974) */
/* 588 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 590 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 592 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 594 */	NdrFcShort( 0x8 ),	/* 8 */
/* 596 */	NdrFcShort( 0x0 ),	/* 0 */
/* 598 */	NdrFcShort( 0x6 ),	/* Offset= 6 (604) */
/* 600 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 602 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 604 */	
			0x11, 0x0,	/* FC_RP */
/* 606 */	NdrFcShort( 0xffffffd4 ),	/* Offset= -44 (562) */
/* 608 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 610 */	NdrFcLong( 0x2f ),	/* 47 */
/* 614 */	NdrFcShort( 0x0 ),	/* 0 */
/* 616 */	NdrFcShort( 0x0 ),	/* 0 */
/* 618 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 620 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 622 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 624 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 626 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 628 */	NdrFcShort( 0x1 ),	/* 1 */
/* 630 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 632 */	NdrFcShort( 0x4 ),	/* 4 */
/* 634 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 636 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 638 */	NdrFcShort( 0x10 ),	/* 16 */
/* 640 */	NdrFcShort( 0x0 ),	/* 0 */
/* 642 */	NdrFcShort( 0xa ),	/* Offset= 10 (652) */
/* 644 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 646 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 648 */	NdrFcShort( 0xffffffd8 ),	/* Offset= -40 (608) */
/* 650 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 652 */	
			0x12, 0x0,	/* FC_UP */
/* 654 */	NdrFcShort( 0xffffffe4 ),	/* Offset= -28 (626) */
/* 656 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 658 */	NdrFcShort( 0x4 ),	/* 4 */
/* 660 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 662 */	NdrFcShort( 0x0 ),	/* 0 */
/* 664 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 666 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 668 */	NdrFcShort( 0x4 ),	/* 4 */
/* 670 */	NdrFcShort( 0x0 ),	/* 0 */
/* 672 */	NdrFcShort( 0x1 ),	/* 1 */
/* 674 */	NdrFcShort( 0x0 ),	/* 0 */
/* 676 */	NdrFcShort( 0x0 ),	/* 0 */
/* 678 */	0x12, 0x0,	/* FC_UP */
/* 680 */	NdrFcShort( 0xffffffd4 ),	/* Offset= -44 (636) */
/* 682 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 684 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 686 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 688 */	NdrFcShort( 0x8 ),	/* 8 */
/* 690 */	NdrFcShort( 0x0 ),	/* 0 */
/* 692 */	NdrFcShort( 0x6 ),	/* Offset= 6 (698) */
/* 694 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 696 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 698 */	
			0x11, 0x0,	/* FC_RP */
/* 700 */	NdrFcShort( 0xffffffd4 ),	/* Offset= -44 (656) */
/* 702 */	
			0x1d,		/* FC_SMFARRAY */
			0x0,		/* 0 */
/* 704 */	NdrFcShort( 0x8 ),	/* 8 */
/* 706 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 708 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 710 */	NdrFcShort( 0x10 ),	/* 16 */
/* 712 */	0x8,		/* FC_LONG */
			0x6,		/* FC_SHORT */
/* 714 */	0x6,		/* FC_SHORT */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 716 */	0x0,		/* 0 */
			NdrFcShort( 0xfffffff1 ),	/* Offset= -15 (702) */
			0x5b,		/* FC_END */
/* 720 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 722 */	NdrFcShort( 0x18 ),	/* 24 */
/* 724 */	NdrFcShort( 0x0 ),	/* 0 */
/* 726 */	NdrFcShort( 0xa ),	/* Offset= 10 (736) */
/* 728 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 730 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 732 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (708) */
/* 734 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 736 */	
			0x11, 0x0,	/* FC_RP */
/* 738 */	NdrFcShort( 0xffffff0c ),	/* Offset= -244 (494) */
/* 740 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 742 */	NdrFcShort( 0x1 ),	/* 1 */
/* 744 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 746 */	NdrFcShort( 0x0 ),	/* 0 */
/* 748 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 750 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 752 */	NdrFcShort( 0x8 ),	/* 8 */
/* 754 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 756 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 758 */	NdrFcShort( 0x4 ),	/* 4 */
/* 760 */	NdrFcShort( 0x4 ),	/* 4 */
/* 762 */	0x12, 0x0,	/* FC_UP */
/* 764 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (740) */
/* 766 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 768 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 770 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 772 */	NdrFcShort( 0x2 ),	/* 2 */
/* 774 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 776 */	NdrFcShort( 0x0 ),	/* 0 */
/* 778 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 780 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 782 */	NdrFcShort( 0x8 ),	/* 8 */
/* 784 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 786 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 788 */	NdrFcShort( 0x4 ),	/* 4 */
/* 790 */	NdrFcShort( 0x4 ),	/* 4 */
/* 792 */	0x12, 0x0,	/* FC_UP */
/* 794 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (770) */
/* 796 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 798 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 800 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 802 */	NdrFcShort( 0x4 ),	/* 4 */
/* 804 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 806 */	NdrFcShort( 0x0 ),	/* 0 */
/* 808 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 810 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 812 */	NdrFcShort( 0x8 ),	/* 8 */
/* 814 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 816 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 818 */	NdrFcShort( 0x4 ),	/* 4 */
/* 820 */	NdrFcShort( 0x4 ),	/* 4 */
/* 822 */	0x12, 0x0,	/* FC_UP */
/* 824 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (800) */
/* 826 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 828 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 830 */	
			0x1b,		/* FC_CARRAY */
			0x7,		/* 7 */
/* 832 */	NdrFcShort( 0x8 ),	/* 8 */
/* 834 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 836 */	NdrFcShort( 0x0 ),	/* 0 */
/* 838 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 840 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 842 */	NdrFcShort( 0x8 ),	/* 8 */
/* 844 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 846 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 848 */	NdrFcShort( 0x4 ),	/* 4 */
/* 850 */	NdrFcShort( 0x4 ),	/* 4 */
/* 852 */	0x12, 0x0,	/* FC_UP */
/* 854 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (830) */
/* 856 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 858 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 860 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 862 */	NdrFcShort( 0x8 ),	/* 8 */
/* 864 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 866 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 868 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 870 */	NdrFcShort( 0x8 ),	/* 8 */
/* 872 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 874 */	NdrFcShort( 0xffd8 ),	/* -40 */
/* 876 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 878 */	NdrFcShort( 0xffffffee ),	/* Offset= -18 (860) */
/* 880 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 882 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 884 */	NdrFcShort( 0x28 ),	/* 40 */
/* 886 */	NdrFcShort( 0xffffffee ),	/* Offset= -18 (868) */
/* 888 */	NdrFcShort( 0x0 ),	/* Offset= 0 (888) */
/* 890 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 892 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 894 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 896 */	NdrFcShort( 0xfffffdf8 ),	/* Offset= -520 (376) */
/* 898 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 900 */	
			0x12, 0x0,	/* FC_UP */
/* 902 */	NdrFcShort( 0xfffffef6 ),	/* Offset= -266 (636) */
/* 904 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 906 */	0x1,		/* FC_BYTE */
			0x5c,		/* FC_PAD */
/* 908 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 910 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 912 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 914 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 916 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 918 */	0xb,		/* FC_HYPER */
			0x5c,		/* FC_PAD */
/* 920 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 922 */	0xa,		/* FC_FLOAT */
			0x5c,		/* FC_PAD */
/* 924 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 926 */	0xc,		/* FC_DOUBLE */
			0x5c,		/* FC_PAD */
/* 928 */	
			0x12, 0x0,	/* FC_UP */
/* 930 */	NdrFcShort( 0xfffffd8c ),	/* Offset= -628 (302) */
/* 932 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 934 */	NdrFcShort( 0xfffffd8e ),	/* Offset= -626 (308) */
/* 936 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 938 */	NdrFcShort( 0xfffffda2 ),	/* Offset= -606 (332) */
/* 940 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 942 */	NdrFcShort( 0xfffffdb0 ),	/* Offset= -592 (350) */
/* 944 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 946 */	NdrFcShort( 0xfffffdbe ),	/* Offset= -578 (368) */
/* 948 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 950 */	NdrFcShort( 0x2 ),	/* Offset= 2 (952) */
/* 952 */	
			0x12, 0x0,	/* FC_UP */
/* 954 */	NdrFcShort( 0x14 ),	/* Offset= 20 (974) */
/* 956 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 958 */	NdrFcShort( 0x10 ),	/* 16 */
/* 960 */	0x6,		/* FC_SHORT */
			0x1,		/* FC_BYTE */
/* 962 */	0x1,		/* FC_BYTE */
			0x8,		/* FC_LONG */
/* 964 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 966 */	
			0x12, 0x0,	/* FC_UP */
/* 968 */	NdrFcShort( 0xfffffff4 ),	/* Offset= -12 (956) */
/* 970 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 972 */	0x2,		/* FC_CHAR */
			0x5c,		/* FC_PAD */
/* 974 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 976 */	NdrFcShort( 0x20 ),	/* 32 */
/* 978 */	NdrFcShort( 0x0 ),	/* 0 */
/* 980 */	NdrFcShort( 0x0 ),	/* Offset= 0 (980) */
/* 982 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 984 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 986 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 988 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 990 */	NdrFcShort( 0xfffffc28 ),	/* Offset= -984 (6) */
/* 992 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 994 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 996 */	NdrFcShort( 0x0 ),	/* 0 */
/* 998 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1000 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1002 */	NdrFcShort( 0xfffffc18 ),	/* Offset= -1000 (2) */
/* 1004 */	
			0x11, 0x14,	/* FC_RP [alloced_on_stack] [pointer_deref] */
/* 1006 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1008) */
/* 1008 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1010 */	NdrFcLong( 0x796386b ),	/* 127285355 */
/* 1014 */	NdrFcShort( 0x3123 ),	/* 12579 */
/* 1016 */	NdrFcShort( 0x101c ),	/* 4124 */
/* 1018 */	0xbb,		/* 187 */
			0x62,		/* 98 */
/* 1020 */	0x0,		/* 0 */
			0xaa,		/* 170 */
/* 1022 */	0x0,		/* 0 */
			0x18,		/* 24 */
/* 1024 */	0x49,		/* 73 */
			0x7c,		/* 124 */
/* 1026 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 1028 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 1030 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1032 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1034 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1036 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1038 */	NdrFcShort( 0xfffffd26 ),	/* Offset= -730 (308) */
/* 1040 */	
			0x11, 0x8,	/* FC_RP [simple_pointer] */
/* 1042 */	0xd,		/* FC_ENUM16 */
			0x5c,		/* FC_PAD */
/* 1044 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 1046 */	NdrFcShort( 0xffffffda ),	/* Offset= -38 (1008) */
/* 1048 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 1050 */	NdrFcShort( 0x6 ),	/* Offset= 6 (1056) */
/* 1052 */	
			0x13, 0x0,	/* FC_OP */
/* 1054 */	NdrFcShort( 0xfffffd24 ),	/* Offset= -732 (322) */
/* 1056 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1058 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1060 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1062 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1064 */	NdrFcShort( 0xfffffff4 ),	/* Offset= -12 (1052) */

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



/* Standard interface: __MIDL_itf_Visinfo_0000, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}} */


/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IVisObjExt, ver. 0.0,
   GUID={0x079638E0,0x3123,0x101C,{0xBB,0x62,0x00,0xAA,0x00,0x18,0x49,0x7C}} */

#pragma code_seg(".orpc")
static const unsigned short IVisObjExt_FormatStringOffsetTable[] =
    {
    0,
    14,
    28,
    0,
    38,
    28,
    54,
    66
    };

static const MIDL_STUBLESS_PROXY_INFO IVisObjExt_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IVisObjExt_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IVisObjExt_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IVisObjExt_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
const CINTERFACE_PROXY_VTABLE(11) _IVisObjExtProxyVtbl = 
{
    &IID_IVisObjExt,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    IVisObjExt_GetVisInfoClass_Proxy ,
    IVisObjExt_SetVisInfoClass_Proxy ,
    IVisObjExt_ResetVisInfoClass_Proxy ,
    IVisObjExt_GetVisInfoObject_Proxy ,
    IVisObjExt_SetVisInfoObject_Proxy ,
    IVisObjExt_ResetVisInfoObject_Proxy ,
    IVisObjExt_GetObjectHiddenStatus_Proxy ,
    IVisObjExt_SetObjectHiddenStatus_Proxy
};


static const PRPC_STUB_FUNCTION IVisObjExt_table[] =
{
    IVisObjExt_GetVisInfoClass_Stub,
    IVisObjExt_SetVisInfoClass_Stub,
    IVisObjExt_ResetVisInfoClass_Stub,
    IVisObjExt_GetVisInfoObject_Stub,
    IVisObjExt_SetVisInfoObject_Stub,
    IVisObjExt_ResetVisInfoObject_Stub,
    IVisObjExt_GetObjectHiddenStatus_Stub,
    IVisObjExt_SetObjectHiddenStatus_Stub
};

const CInterfaceStubVtbl _IVisObjExtStubVtbl =
{
    &IID_IVisObjExt,
    &IVisObjExt_ServerInfo,
    11,
    &IVisObjExt_table[-3],
    CStdStubBuffer_METHODS
};


/* Object interface: IVisQuery, ver. 0.0,
   GUID={0x079638E3,0x3123,0x101C,{0xBB,0x62,0x00,0xAA,0x00,0x18,0x49,0x7C}} */

#pragma code_seg(".orpc")
static const unsigned short IVisQuery_FormatStringOffsetTable[] =
    {
    76,
    88
    };

static const MIDL_STUBLESS_PROXY_INFO IVisQuery_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IVisQuery_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IVisQuery_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IVisQuery_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
const CINTERFACE_PROXY_VTABLE(5) _IVisQueryProxyVtbl = 
{
    &IID_IVisQuery,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    IVisQuery_GetIdentMode_Proxy ,
    IVisQuery_GetObjectVis_Proxy
};


static const PRPC_STUB_FUNCTION IVisQuery_table[] =
{
    IVisQuery_GetIdentMode_Stub,
    IVisQuery_GetObjectVis_Stub
};

const CInterfaceStubVtbl _IVisQueryStubVtbl =
{
    &IID_IVisQuery,
    &IVisQuery_ServerInfo,
    5,
    &IVisQuery_table[-3],
    CStdStubBuffer_METHODS
};


/* Object interface: IMergeVisInfo, ver. 0.0,
   GUID={0x079638E4,0x3123,0x101C,{0xBB,0x62,0x00,0xAA,0x00,0x18,0x49,0x7C}} */

#pragma code_seg(".orpc")
static const unsigned short IMergeVisInfo_FormatStringOffsetTable[] =
    {
    96
    };

static const MIDL_STUBLESS_PROXY_INFO IMergeVisInfo_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IMergeVisInfo_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IMergeVisInfo_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IMergeVisInfo_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
const CINTERFACE_PROXY_VTABLE(4) _IMergeVisInfoProxyVtbl = 
{
    &IID_IMergeVisInfo,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    IMergeVisInfo_MergeVisInfo_Proxy
};


static const PRPC_STUB_FUNCTION IMergeVisInfo_table[] =
{
    IMergeVisInfo_MergeVisInfo_Stub
};

const CInterfaceStubVtbl _IMergeVisInfoStubVtbl =
{
    &IID_IMergeVisInfo,
    &IMergeVisInfo_ServerInfo,
    4,
    &IMergeVisInfo_table[-3],
    CStdStubBuffer_METHODS
};


/* Object interface: IRawVisInfo, ver. 0.0,
   GUID={0x4BAB20A3,0xA922,0x11D1,{0x85,0x88,0x00,0x60,0x08,0x75,0x13,0x8A}} */

#pragma code_seg(".orpc")
static const unsigned short IRawVisInfo_FormatStringOffsetTable[] =
    {
    104,
    112
    };

static const MIDL_STUBLESS_PROXY_INFO IRawVisInfo_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IRawVisInfo_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRawVisInfo_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IRawVisInfo_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
const CINTERFACE_PROXY_VTABLE(5) _IRawVisInfoProxyVtbl = 
{
    &IID_IRawVisInfo,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    IRawVisInfo_SetRawData_Proxy ,
    IRawVisInfo_RetrieveRawData_Proxy
};


static const PRPC_STUB_FUNCTION IRawVisInfo_table[] =
{
    IRawVisInfo_SetRawData_Stub,
    IRawVisInfo_RetrieveRawData_Stub
};

const CInterfaceStubVtbl _IRawVisInfoStubVtbl =
{
    &IID_IRawVisInfo,
    &IRawVisInfo_ServerInfo,
    5,
    &IRawVisInfo_table[-3],
    CStdStubBuffer_METHODS
};


/* Object interface: IExtendedObjectVisInfo, ver. 0.0,
   GUID={0x8B4834A5,0xEB76,0x4567,{0xA9,0x7A,0xD3,0x8A,0xCE,0xE0,0x77,0xA6}} */

#pragma code_seg(".orpc")
static const unsigned short IExtendedObjectVisInfo_FormatStringOffsetTable[] =
    {
    120,
    126,
    132,
    126,
    132
    };

static const MIDL_STUBLESS_PROXY_INFO IExtendedObjectVisInfo_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IExtendedObjectVisInfo_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IExtendedObjectVisInfo_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IExtendedObjectVisInfo_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
const CINTERFACE_PROXY_VTABLE(8) _IExtendedObjectVisInfoProxyVtbl = 
{
    &IID_IExtendedObjectVisInfo,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    IExtendedObjectVisInfo_get_HasInfos_Proxy ,
    IExtendedObjectVisInfo_get_ModuleInfo_Proxy ,
    IExtendedObjectVisInfo_put_ModuleInfo_Proxy ,
    IExtendedObjectVisInfo_get_ExtendedInfo_Proxy ,
    IExtendedObjectVisInfo_put_ExtendedInfo_Proxy
};


static const PRPC_STUB_FUNCTION IExtendedObjectVisInfo_table[] =
{
    IExtendedObjectVisInfo_get_HasInfos_Stub,
    IExtendedObjectVisInfo_get_ModuleInfo_Stub,
    IExtendedObjectVisInfo_put_ModuleInfo_Stub,
    IExtendedObjectVisInfo_get_ExtendedInfo_Stub,
    IExtendedObjectVisInfo_put_ExtendedInfo_Stub
};

const CInterfaceStubVtbl _IExtendedObjectVisInfoStubVtbl =
{
    &IID_IExtendedObjectVisInfo,
    &IExtendedObjectVisInfo_ServerInfo,
    8,
    &IExtendedObjectVisInfo_table[-3],
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

const CInterfaceProxyVtbl * _Visinfo_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_IRawVisInfoProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IExtendedObjectVisInfoProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IVisObjExtProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IVisQueryProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IMergeVisInfoProxyVtbl,
    0
};

const CInterfaceStubVtbl * _Visinfo_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_IRawVisInfoStubVtbl,
    ( CInterfaceStubVtbl *) &_IExtendedObjectVisInfoStubVtbl,
    ( CInterfaceStubVtbl *) &_IVisObjExtStubVtbl,
    ( CInterfaceStubVtbl *) &_IVisQueryStubVtbl,
    ( CInterfaceStubVtbl *) &_IMergeVisInfoStubVtbl,
    0
};

PCInterfaceName const _Visinfo_InterfaceNamesList[] = 
{
    "IRawVisInfo",
    "IExtendedObjectVisInfo",
    "IVisObjExt",
    "IVisQuery",
    "IMergeVisInfo",
    0
};


#define _Visinfo_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _Visinfo, pIID, n)

int __stdcall _Visinfo_IID_Lookup( const IID * pIID, int * pIndex )
{
    IID_BS_LOOKUP_SETUP

    IID_BS_LOOKUP_INITIAL_TEST( _Visinfo, 5, 4 )
    IID_BS_LOOKUP_NEXT_TEST( _Visinfo, 2 )
    IID_BS_LOOKUP_NEXT_TEST( _Visinfo, 1 )
    IID_BS_LOOKUP_RETURN_RESULT( _Visinfo, 5, *pIndex )
    
}

const ExtendedProxyFileInfo Visinfo_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _Visinfo_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _Visinfo_StubVtblList,
    (const PCInterfaceName * ) & _Visinfo_InterfaceNamesList,
    0, // no delegation
    & _Visinfo_IID_Lookup, 
    5,
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
/* at Wed Mar 13 17:42:56 2002
 */
/* Compiler settings for .\Visinfo.idl:
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


#include "Visinfo.h"

#define TYPE_FORMAT_STRING_SIZE   1047                              
#define PROC_FORMAT_STRING_SIZE   847                               
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


extern const MIDL_SERVER_INFO IVisObjExt_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IVisObjExt_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IVisQuery_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IVisQuery_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IMergeVisInfo_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IMergeVisInfo_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRawVisInfo_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRawVisInfo_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IExtendedObjectVisInfo_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IExtendedObjectVisInfo_ProxyInfo;


extern const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ];

#if !defined(__RPC_WIN64__)
#error  Invalid build platform for this stub.
#endif

static const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure GetVisInfoClass */

			0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/*  2 */	NdrFcLong( 0x0 ),	/* 0 */
/*  6 */	NdrFcShort( 0x3 ),	/* 3 */
/*  8 */	NdrFcShort( 0x40 ),	/* ia64 Stack size/offset = 64 */
/* 10 */	NdrFcShort( 0xe ),	/* 14 */
/* 12 */	NdrFcShort( 0x8 ),	/* 8 */
/* 14 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x5,		/* 5 */
/* 16 */	0xa,		/* 10 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 18 */	NdrFcShort( 0x0 ),	/* 0 */
/* 20 */	NdrFcShort( 0x20 ),	/* 32 */
/* 22 */	NdrFcShort( 0x0 ),	/* 0 */
/* 24 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter lIdent */

/* 26 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 28 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 30 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter rgType */

/* 32 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 34 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 36 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter vViewName */

/* 38 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 40 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 42 */	NdrFcShort( 0x3ce ),	/* Type Offset=974 */

	/* Parameter ppIVisInfo */

/* 44 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 46 */	NdrFcShort( 0x30 ),	/* ia64 Stack size/offset = 48 */
/* 48 */	NdrFcShort( 0x3d8 ),	/* Type Offset=984 */

	/* Return value */

/* 50 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 52 */	NdrFcShort( 0x38 ),	/* ia64 Stack size/offset = 56 */
/* 54 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetVisInfoClass */

/* 56 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 58 */	NdrFcLong( 0x0 ),	/* 0 */
/* 62 */	NdrFcShort( 0x4 ),	/* 4 */
/* 64 */	NdrFcShort( 0x40 ),	/* ia64 Stack size/offset = 64 */
/* 66 */	NdrFcShort( 0xe ),	/* 14 */
/* 68 */	NdrFcShort( 0x8 ),	/* 8 */
/* 70 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x5,		/* 5 */
/* 72 */	0xa,		/* 10 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 74 */	NdrFcShort( 0x0 ),	/* 0 */
/* 76 */	NdrFcShort( 0x20 ),	/* 32 */
/* 78 */	NdrFcShort( 0x0 ),	/* 0 */
/* 80 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter lIdent */

/* 82 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 84 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 86 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter rgType */

/* 88 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 90 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 92 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter pIVisInfo */

/* 94 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 96 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 98 */	NdrFcShort( 0x3dc ),	/* Type Offset=988 */

	/* Parameter vViewName */

/* 100 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 102 */	NdrFcShort( 0x20 ),	/* ia64 Stack size/offset = 32 */
/* 104 */	NdrFcShort( 0x3ce ),	/* Type Offset=974 */

	/* Return value */

/* 106 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 108 */	NdrFcShort( 0x38 ),	/* ia64 Stack size/offset = 56 */
/* 110 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ResetVisInfoClass */

/* 112 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 114 */	NdrFcLong( 0x0 ),	/* 0 */
/* 118 */	NdrFcShort( 0x5 ),	/* 5 */
/* 120 */	NdrFcShort( 0x38 ),	/* ia64 Stack size/offset = 56 */
/* 122 */	NdrFcShort( 0xe ),	/* 14 */
/* 124 */	NdrFcShort( 0x8 ),	/* 8 */
/* 126 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 128 */	0xa,		/* 10 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 130 */	NdrFcShort( 0x0 ),	/* 0 */
/* 132 */	NdrFcShort( 0x20 ),	/* 32 */
/* 134 */	NdrFcShort( 0x0 ),	/* 0 */
/* 136 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter lIdent */

/* 138 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 140 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 142 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter rgType */

/* 144 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 146 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 148 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter vView */

/* 150 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 152 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 154 */	NdrFcShort( 0x3ce ),	/* Type Offset=974 */

	/* Return value */

/* 156 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 158 */	NdrFcShort( 0x30 ),	/* ia64 Stack size/offset = 48 */
/* 160 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetVisInfoObject */

/* 162 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 164 */	NdrFcLong( 0x0 ),	/* 0 */
/* 168 */	NdrFcShort( 0x6 ),	/* 6 */
/* 170 */	NdrFcShort( 0x40 ),	/* ia64 Stack size/offset = 64 */
/* 172 */	NdrFcShort( 0xe ),	/* 14 */
/* 174 */	NdrFcShort( 0x8 ),	/* 8 */
/* 176 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x5,		/* 5 */
/* 178 */	0xa,		/* 10 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 180 */	NdrFcShort( 0x0 ),	/* 0 */
/* 182 */	NdrFcShort( 0x20 ),	/* 32 */
/* 184 */	NdrFcShort( 0x0 ),	/* 0 */
/* 186 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter lONr */

/* 188 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 190 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 192 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter rgType */

/* 194 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 196 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 198 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter vViewName */

/* 200 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 202 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 204 */	NdrFcShort( 0x3ce ),	/* Type Offset=974 */

	/* Parameter ppIVisInfo */

/* 206 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 208 */	NdrFcShort( 0x30 ),	/* ia64 Stack size/offset = 48 */
/* 210 */	NdrFcShort( 0x3d8 ),	/* Type Offset=984 */

	/* Return value */

/* 212 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 214 */	NdrFcShort( 0x38 ),	/* ia64 Stack size/offset = 56 */
/* 216 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetVisInfoObject */

/* 218 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 220 */	NdrFcLong( 0x0 ),	/* 0 */
/* 224 */	NdrFcShort( 0x7 ),	/* 7 */
/* 226 */	NdrFcShort( 0x48 ),	/* ia64 Stack size/offset = 72 */
/* 228 */	NdrFcShort( 0x14 ),	/* 20 */
/* 230 */	NdrFcShort( 0x8 ),	/* 8 */
/* 232 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x6,		/* 6 */
/* 234 */	0xa,		/* 10 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 236 */	NdrFcShort( 0x0 ),	/* 0 */
/* 238 */	NdrFcShort( 0x20 ),	/* 32 */
/* 240 */	NdrFcShort( 0x0 ),	/* 0 */
/* 242 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter lONr */

/* 244 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 246 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 248 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter rgType */

/* 250 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 252 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 254 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter pIVisInfo */

/* 256 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 258 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 260 */	NdrFcShort( 0x3dc ),	/* Type Offset=988 */

	/* Parameter fSameAsSource */

/* 262 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 264 */	NdrFcShort( 0x20 ),	/* ia64 Stack size/offset = 32 */
/* 266 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter vViewName */

/* 268 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 270 */	NdrFcShort( 0x28 ),	/* ia64 Stack size/offset = 40 */
/* 272 */	NdrFcShort( 0x3ce ),	/* Type Offset=974 */

	/* Return value */

/* 274 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 276 */	NdrFcShort( 0x40 ),	/* ia64 Stack size/offset = 64 */
/* 278 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ResetVisInfoObject */

/* 280 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 282 */	NdrFcLong( 0x0 ),	/* 0 */
/* 286 */	NdrFcShort( 0x8 ),	/* 8 */
/* 288 */	NdrFcShort( 0x38 ),	/* ia64 Stack size/offset = 56 */
/* 290 */	NdrFcShort( 0xe ),	/* 14 */
/* 292 */	NdrFcShort( 0x8 ),	/* 8 */
/* 294 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 296 */	0xa,		/* 10 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 298 */	NdrFcShort( 0x0 ),	/* 0 */
/* 300 */	NdrFcShort( 0x20 ),	/* 32 */
/* 302 */	NdrFcShort( 0x0 ),	/* 0 */
/* 304 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter lONr */

/* 306 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 308 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 310 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter rgType */

/* 312 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 314 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 316 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter vViewName */

/* 318 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 320 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 322 */	NdrFcShort( 0x3ce ),	/* Type Offset=974 */

	/* Return value */

/* 324 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 326 */	NdrFcShort( 0x30 ),	/* ia64 Stack size/offset = 48 */
/* 328 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetObjectHiddenStatus */

/* 330 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 332 */	NdrFcLong( 0x0 ),	/* 0 */
/* 336 */	NdrFcShort( 0x9 ),	/* 9 */
/* 338 */	NdrFcShort( 0x38 ),	/* ia64 Stack size/offset = 56 */
/* 340 */	NdrFcShort( 0x8 ),	/* 8 */
/* 342 */	NdrFcShort( 0x22 ),	/* 34 */
/* 344 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 346 */	0xa,		/* 10 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 348 */	NdrFcShort( 0x0 ),	/* 0 */
/* 350 */	NdrFcShort( 0x20 ),	/* 32 */
/* 352 */	NdrFcShort( 0x0 ),	/* 0 */
/* 354 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter lONr */

/* 356 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 358 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 360 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter vViewName */

/* 362 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 364 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 366 */	NdrFcShort( 0x3ce ),	/* Type Offset=974 */

	/* Parameter pfShow */

/* 368 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 370 */	NdrFcShort( 0x28 ),	/* ia64 Stack size/offset = 40 */
/* 372 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 374 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 376 */	NdrFcShort( 0x30 ),	/* ia64 Stack size/offset = 48 */
/* 378 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetObjectHiddenStatus */

/* 380 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 382 */	NdrFcLong( 0x0 ),	/* 0 */
/* 386 */	NdrFcShort( 0xa ),	/* 10 */
/* 388 */	NdrFcShort( 0x38 ),	/* ia64 Stack size/offset = 56 */
/* 390 */	NdrFcShort( 0xe ),	/* 14 */
/* 392 */	NdrFcShort( 0x8 ),	/* 8 */
/* 394 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 396 */	0xa,		/* 10 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 398 */	NdrFcShort( 0x0 ),	/* 0 */
/* 400 */	NdrFcShort( 0x20 ),	/* 32 */
/* 402 */	NdrFcShort( 0x0 ),	/* 0 */
/* 404 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter lONr */

/* 406 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 408 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 410 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter fShow */

/* 412 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 414 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 416 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter vViewName */

/* 418 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 420 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 422 */	NdrFcShort( 0x3ce ),	/* Type Offset=974 */

	/* Return value */

/* 424 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 426 */	NdrFcShort( 0x30 ),	/* ia64 Stack size/offset = 48 */
/* 428 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetIdentMode */

/* 430 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 432 */	NdrFcLong( 0x0 ),	/* 0 */
/* 436 */	NdrFcShort( 0x3 ),	/* 3 */
/* 438 */	NdrFcShort( 0x28 ),	/* ia64 Stack size/offset = 40 */
/* 440 */	NdrFcShort( 0x22 ),	/* 34 */
/* 442 */	NdrFcShort( 0x22 ),	/* 34 */
/* 444 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 446 */	0xa,		/* 10 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 448 */	NdrFcShort( 0x0 ),	/* 0 */
/* 450 */	NdrFcShort( 0x1 ),	/* 1 */
/* 452 */	NdrFcShort( 0x0 ),	/* 0 */
/* 454 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter Ident */

/* 456 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 458 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 460 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter View */

/* 462 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 464 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 466 */	NdrFcShort( 0x3f2 ),	/* Type Offset=1010 */

	/* Parameter VisMode */

/* 468 */	NdrFcShort( 0x2018 ),	/* Flags:  in, out, srv alloc size=8 */
/* 470 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 472 */	NdrFcShort( 0x3fc ),	/* Type Offset=1020 */

	/* Return value */

/* 474 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 476 */	NdrFcShort( 0x20 ),	/* ia64 Stack size/offset = 32 */
/* 478 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetObjectVis */

/* 480 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 482 */	NdrFcLong( 0x0 ),	/* 0 */
/* 486 */	NdrFcShort( 0x4 ),	/* 4 */
/* 488 */	NdrFcShort( 0x20 ),	/* ia64 Stack size/offset = 32 */
/* 490 */	NdrFcShort( 0x8 ),	/* 8 */
/* 492 */	NdrFcShort( 0x8 ),	/* 8 */
/* 494 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 496 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 498 */	NdrFcShort( 0x0 ),	/* 0 */
/* 500 */	NdrFcShort( 0x0 ),	/* 0 */
/* 502 */	NdrFcShort( 0x0 ),	/* 0 */
/* 504 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ObjNr */

/* 506 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 508 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 510 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter Vis */

/* 512 */	NdrFcShort( 0x201b ),	/* Flags:  must size, must free, in, out, srv alloc size=8 */
/* 514 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 516 */	NdrFcShort( 0x400 ),	/* Type Offset=1024 */

	/* Return value */

/* 518 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 520 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 522 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure MergeVisInfo */

/* 524 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 526 */	NdrFcLong( 0x0 ),	/* 0 */
/* 530 */	NdrFcShort( 0x3 ),	/* 3 */
/* 532 */	NdrFcShort( 0x20 ),	/* ia64 Stack size/offset = 32 */
/* 534 */	NdrFcShort( 0x6 ),	/* 6 */
/* 536 */	NdrFcShort( 0x8 ),	/* 8 */
/* 538 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 540 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 542 */	NdrFcShort( 0x0 ),	/* 0 */
/* 544 */	NdrFcShort( 0x0 ),	/* 0 */
/* 546 */	NdrFcShort( 0x0 ),	/* 0 */
/* 548 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter OnlyChanged */

/* 550 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 552 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 554 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter VisInfo */

/* 556 */	NdrFcShort( 0x201b ),	/* Flags:  must size, must free, in, out, srv alloc size=8 */
/* 558 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 560 */	NdrFcShort( 0x400 ),	/* Type Offset=1024 */

	/* Return value */

/* 562 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 564 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 566 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetRawData */

/* 568 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 570 */	NdrFcLong( 0x0 ),	/* 0 */
/* 574 */	NdrFcShort( 0x3 ),	/* 3 */
/* 576 */	NdrFcShort( 0x20 ),	/* ia64 Stack size/offset = 32 */
/* 578 */	NdrFcShort( 0x6 ),	/* 6 */
/* 580 */	NdrFcShort( 0x8 ),	/* 8 */
/* 582 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 584 */	0xa,		/* 10 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 586 */	NdrFcShort( 0x0 ),	/* 0 */
/* 588 */	NdrFcShort( 0x1 ),	/* 1 */
/* 590 */	NdrFcShort( 0x0 ),	/* 0 */
/* 592 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter rgType */

/* 594 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 596 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 598 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter Data */

/* 600 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 602 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 604 */	NdrFcShort( 0x3f2 ),	/* Type Offset=1010 */

	/* Return value */

/* 606 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 608 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 610 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure RetrieveRawData */

/* 612 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 614 */	NdrFcLong( 0x0 ),	/* 0 */
/* 618 */	NdrFcShort( 0x4 ),	/* 4 */
/* 620 */	NdrFcShort( 0x20 ),	/* ia64 Stack size/offset = 32 */
/* 622 */	NdrFcShort( 0x6 ),	/* 6 */
/* 624 */	NdrFcShort( 0x8 ),	/* 8 */
/* 626 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 628 */	0xa,		/* 10 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 630 */	NdrFcShort( 0x1 ),	/* 1 */
/* 632 */	NdrFcShort( 0x0 ),	/* 0 */
/* 634 */	NdrFcShort( 0x0 ),	/* 0 */
/* 636 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter rgType */

/* 638 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 640 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 642 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter Data */

/* 644 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 646 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 648 */	NdrFcShort( 0x40c ),	/* Type Offset=1036 */

	/* Return value */

/* 650 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 652 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 654 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_HasInfos */

/* 656 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 658 */	NdrFcLong( 0x0 ),	/* 0 */
/* 662 */	NdrFcShort( 0x3 ),	/* 3 */
/* 664 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 666 */	NdrFcShort( 0x0 ),	/* 0 */
/* 668 */	NdrFcShort( 0x22 ),	/* 34 */
/* 670 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 672 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 674 */	NdrFcShort( 0x0 ),	/* 0 */
/* 676 */	NdrFcShort( 0x0 ),	/* 0 */
/* 678 */	NdrFcShort( 0x0 ),	/* 0 */
/* 680 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter HasInfos */

/* 682 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 684 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 686 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 688 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 690 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 692 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_ModuleInfo */

/* 694 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 696 */	NdrFcLong( 0x0 ),	/* 0 */
/* 700 */	NdrFcShort( 0x4 ),	/* 4 */
/* 702 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 704 */	NdrFcShort( 0x0 ),	/* 0 */
/* 706 */	NdrFcShort( 0x8 ),	/* 8 */
/* 708 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 710 */	0xa,		/* 10 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 712 */	NdrFcShort( 0x1 ),	/* 1 */
/* 714 */	NdrFcShort( 0x0 ),	/* 0 */
/* 716 */	NdrFcShort( 0x0 ),	/* 0 */
/* 718 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ModuleName */

/* 720 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 722 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 724 */	NdrFcShort( 0x40c ),	/* Type Offset=1036 */

	/* Return value */

/* 726 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 728 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 730 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_ModuleInfo */

/* 732 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 734 */	NdrFcLong( 0x0 ),	/* 0 */
/* 738 */	NdrFcShort( 0x5 ),	/* 5 */
/* 740 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 742 */	NdrFcShort( 0x0 ),	/* 0 */
/* 744 */	NdrFcShort( 0x8 ),	/* 8 */
/* 746 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 748 */	0xa,		/* 10 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 750 */	NdrFcShort( 0x0 ),	/* 0 */
/* 752 */	NdrFcShort( 0x1 ),	/* 1 */
/* 754 */	NdrFcShort( 0x0 ),	/* 0 */
/* 756 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ModuleName */

/* 758 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 760 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 762 */	NdrFcShort( 0x3f2 ),	/* Type Offset=1010 */

	/* Return value */

/* 764 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 766 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 768 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_ExtendedInfo */

/* 770 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 772 */	NdrFcLong( 0x0 ),	/* 0 */
/* 776 */	NdrFcShort( 0x6 ),	/* 6 */
/* 778 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 780 */	NdrFcShort( 0x0 ),	/* 0 */
/* 782 */	NdrFcShort( 0x8 ),	/* 8 */
/* 784 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 786 */	0xa,		/* 10 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 788 */	NdrFcShort( 0x1 ),	/* 1 */
/* 790 */	NdrFcShort( 0x0 ),	/* 0 */
/* 792 */	NdrFcShort( 0x0 ),	/* 0 */
/* 794 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter VisString */

/* 796 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 798 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 800 */	NdrFcShort( 0x40c ),	/* Type Offset=1036 */

	/* Return value */

/* 802 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 804 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 806 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_ExtendedInfo */

/* 808 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 810 */	NdrFcLong( 0x0 ),	/* 0 */
/* 814 */	NdrFcShort( 0x7 ),	/* 7 */
/* 816 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 818 */	NdrFcShort( 0x0 ),	/* 0 */
/* 820 */	NdrFcShort( 0x8 ),	/* 8 */
/* 822 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 824 */	0xa,		/* 10 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 826 */	NdrFcShort( 0x0 ),	/* 0 */
/* 828 */	NdrFcShort( 0x1 ),	/* 1 */
/* 830 */	NdrFcShort( 0x0 ),	/* 0 */
/* 832 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter VisString */

/* 834 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 836 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 838 */	NdrFcShort( 0x3f2 ),	/* Type Offset=1010 */

	/* Return value */

/* 840 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 842 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 844 */	0x8,		/* FC_LONG */
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
			0x12, 0x0,	/* FC_UP */
/*  4 */	NdrFcShort( 0x3b6 ),	/* Offset= 950 (954) */
/*  6 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/*  8 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 10 */	NdrFcShort( 0xfff8 ),	/* -8 */
/* 12 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 14 */	NdrFcShort( 0x2 ),	/* Offset= 2 (16) */
/* 16 */	NdrFcShort( 0x10 ),	/* 16 */
/* 18 */	NdrFcShort( 0x2f ),	/* 47 */
/* 20 */	NdrFcLong( 0x14 ),	/* 20 */
/* 24 */	NdrFcShort( 0x800b ),	/* Simple arm type: FC_HYPER */
/* 26 */	NdrFcLong( 0x3 ),	/* 3 */
/* 30 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 32 */	NdrFcLong( 0x11 ),	/* 17 */
/* 36 */	NdrFcShort( 0x8001 ),	/* Simple arm type: FC_BYTE */
/* 38 */	NdrFcLong( 0x2 ),	/* 2 */
/* 42 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 44 */	NdrFcLong( 0x4 ),	/* 4 */
/* 48 */	NdrFcShort( 0x800a ),	/* Simple arm type: FC_FLOAT */
/* 50 */	NdrFcLong( 0x5 ),	/* 5 */
/* 54 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 56 */	NdrFcLong( 0xb ),	/* 11 */
/* 60 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 62 */	NdrFcLong( 0xa ),	/* 10 */
/* 66 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 68 */	NdrFcLong( 0x6 ),	/* 6 */
/* 72 */	NdrFcShort( 0xe8 ),	/* Offset= 232 (304) */
/* 74 */	NdrFcLong( 0x7 ),	/* 7 */
/* 78 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 80 */	NdrFcLong( 0x8 ),	/* 8 */
/* 84 */	NdrFcShort( 0xe2 ),	/* Offset= 226 (310) */
/* 86 */	NdrFcLong( 0xd ),	/* 13 */
/* 90 */	NdrFcShort( 0xf6 ),	/* Offset= 246 (336) */
/* 92 */	NdrFcLong( 0x9 ),	/* 9 */
/* 96 */	NdrFcShort( 0x102 ),	/* Offset= 258 (354) */
/* 98 */	NdrFcLong( 0x2000 ),	/* 8192 */
/* 102 */	NdrFcShort( 0x10e ),	/* Offset= 270 (372) */
/* 104 */	NdrFcLong( 0x24 ),	/* 36 */
/* 108 */	NdrFcShort( 0x304 ),	/* Offset= 772 (880) */
/* 110 */	NdrFcLong( 0x4024 ),	/* 16420 */
/* 114 */	NdrFcShort( 0x2fe ),	/* Offset= 766 (880) */
/* 116 */	NdrFcLong( 0x4011 ),	/* 16401 */
/* 120 */	NdrFcShort( 0x2fc ),	/* Offset= 764 (884) */
/* 122 */	NdrFcLong( 0x4002 ),	/* 16386 */
/* 126 */	NdrFcShort( 0x2fa ),	/* Offset= 762 (888) */
/* 128 */	NdrFcLong( 0x4003 ),	/* 16387 */
/* 132 */	NdrFcShort( 0x2f8 ),	/* Offset= 760 (892) */
/* 134 */	NdrFcLong( 0x4014 ),	/* 16404 */
/* 138 */	NdrFcShort( 0x2f6 ),	/* Offset= 758 (896) */
/* 140 */	NdrFcLong( 0x4004 ),	/* 16388 */
/* 144 */	NdrFcShort( 0x2f4 ),	/* Offset= 756 (900) */
/* 146 */	NdrFcLong( 0x4005 ),	/* 16389 */
/* 150 */	NdrFcShort( 0x2f2 ),	/* Offset= 754 (904) */
/* 152 */	NdrFcLong( 0x400b ),	/* 16395 */
/* 156 */	NdrFcShort( 0x2dc ),	/* Offset= 732 (888) */
/* 158 */	NdrFcLong( 0x400a ),	/* 16394 */
/* 162 */	NdrFcShort( 0x2da ),	/* Offset= 730 (892) */
/* 164 */	NdrFcLong( 0x4006 ),	/* 16390 */
/* 168 */	NdrFcShort( 0x2e4 ),	/* Offset= 740 (908) */
/* 170 */	NdrFcLong( 0x4007 ),	/* 16391 */
/* 174 */	NdrFcShort( 0x2da ),	/* Offset= 730 (904) */
/* 176 */	NdrFcLong( 0x4008 ),	/* 16392 */
/* 180 */	NdrFcShort( 0x2dc ),	/* Offset= 732 (912) */
/* 182 */	NdrFcLong( 0x400d ),	/* 16397 */
/* 186 */	NdrFcShort( 0x2da ),	/* Offset= 730 (916) */
/* 188 */	NdrFcLong( 0x4009 ),	/* 16393 */
/* 192 */	NdrFcShort( 0x2d8 ),	/* Offset= 728 (920) */
/* 194 */	NdrFcLong( 0x6000 ),	/* 24576 */
/* 198 */	NdrFcShort( 0x2d6 ),	/* Offset= 726 (924) */
/* 200 */	NdrFcLong( 0x400c ),	/* 16396 */
/* 204 */	NdrFcShort( 0x2d4 ),	/* Offset= 724 (928) */
/* 206 */	NdrFcLong( 0x10 ),	/* 16 */
/* 210 */	NdrFcShort( 0x8002 ),	/* Simple arm type: FC_CHAR */
/* 212 */	NdrFcLong( 0x12 ),	/* 18 */
/* 216 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 218 */	NdrFcLong( 0x13 ),	/* 19 */
/* 222 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 224 */	NdrFcLong( 0x15 ),	/* 21 */
/* 228 */	NdrFcShort( 0x800b ),	/* Simple arm type: FC_HYPER */
/* 230 */	NdrFcLong( 0x16 ),	/* 22 */
/* 234 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 236 */	NdrFcLong( 0x17 ),	/* 23 */
/* 240 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 242 */	NdrFcLong( 0xe ),	/* 14 */
/* 246 */	NdrFcShort( 0x2b2 ),	/* Offset= 690 (936) */
/* 248 */	NdrFcLong( 0x400e ),	/* 16398 */
/* 252 */	NdrFcShort( 0x2b6 ),	/* Offset= 694 (946) */
/* 254 */	NdrFcLong( 0x4010 ),	/* 16400 */
/* 258 */	NdrFcShort( 0x2b4 ),	/* Offset= 692 (950) */
/* 260 */	NdrFcLong( 0x4012 ),	/* 16402 */
/* 264 */	NdrFcShort( 0x270 ),	/* Offset= 624 (888) */
/* 266 */	NdrFcLong( 0x4013 ),	/* 16403 */
/* 270 */	NdrFcShort( 0x26e ),	/* Offset= 622 (892) */
/* 272 */	NdrFcLong( 0x4015 ),	/* 16405 */
/* 276 */	NdrFcShort( 0x26c ),	/* Offset= 620 (896) */
/* 278 */	NdrFcLong( 0x4016 ),	/* 16406 */
/* 282 */	NdrFcShort( 0x262 ),	/* Offset= 610 (892) */
/* 284 */	NdrFcLong( 0x4017 ),	/* 16407 */
/* 288 */	NdrFcShort( 0x25c ),	/* Offset= 604 (892) */
/* 290 */	NdrFcLong( 0x0 ),	/* 0 */
/* 294 */	NdrFcShort( 0x0 ),	/* Offset= 0 (294) */
/* 296 */	NdrFcLong( 0x1 ),	/* 1 */
/* 300 */	NdrFcShort( 0x0 ),	/* Offset= 0 (300) */
/* 302 */	NdrFcShort( 0xffffffff ),	/* Offset= -1 (301) */
/* 304 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 306 */	NdrFcShort( 0x8 ),	/* 8 */
/* 308 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 310 */	
			0x12, 0x0,	/* FC_UP */
/* 312 */	NdrFcShort( 0xe ),	/* Offset= 14 (326) */
/* 314 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 316 */	NdrFcShort( 0x2 ),	/* 2 */
/* 318 */	0x9,		/* Corr desc: FC_ULONG */
			0x0,		/*  */
/* 320 */	NdrFcShort( 0xfffc ),	/* -4 */
/* 322 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 324 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 326 */	
			0x17,		/* FC_CSTRUCT */
			0x3,		/* 3 */
/* 328 */	NdrFcShort( 0x8 ),	/* 8 */
/* 330 */	NdrFcShort( 0xfffffff0 ),	/* Offset= -16 (314) */
/* 332 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 334 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 336 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 338 */	NdrFcLong( 0x0 ),	/* 0 */
/* 342 */	NdrFcShort( 0x0 ),	/* 0 */
/* 344 */	NdrFcShort( 0x0 ),	/* 0 */
/* 346 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 348 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 350 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 352 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 354 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 356 */	NdrFcLong( 0x20400 ),	/* 132096 */
/* 360 */	NdrFcShort( 0x0 ),	/* 0 */
/* 362 */	NdrFcShort( 0x0 ),	/* 0 */
/* 364 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 366 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 368 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 370 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 372 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 374 */	NdrFcShort( 0x2 ),	/* Offset= 2 (376) */
/* 376 */	
			0x12, 0x0,	/* FC_UP */
/* 378 */	NdrFcShort( 0x1e4 ),	/* Offset= 484 (862) */
/* 380 */	
			0x2a,		/* FC_ENCAPSULATED_UNION */
			0x89,		/* 137 */
/* 382 */	NdrFcShort( 0x20 ),	/* 32 */
/* 384 */	NdrFcShort( 0xa ),	/* 10 */
/* 386 */	NdrFcLong( 0x8 ),	/* 8 */
/* 390 */	NdrFcShort( 0x50 ),	/* Offset= 80 (470) */
/* 392 */	NdrFcLong( 0xd ),	/* 13 */
/* 396 */	NdrFcShort( 0x70 ),	/* Offset= 112 (508) */
/* 398 */	NdrFcLong( 0x9 ),	/* 9 */
/* 402 */	NdrFcShort( 0x90 ),	/* Offset= 144 (546) */
/* 404 */	NdrFcLong( 0xc ),	/* 12 */
/* 408 */	NdrFcShort( 0xb0 ),	/* Offset= 176 (584) */
/* 410 */	NdrFcLong( 0x24 ),	/* 36 */
/* 414 */	NdrFcShort( 0x102 ),	/* Offset= 258 (672) */
/* 416 */	NdrFcLong( 0x800d ),	/* 32781 */
/* 420 */	NdrFcShort( 0x11e ),	/* Offset= 286 (706) */
/* 422 */	NdrFcLong( 0x10 ),	/* 16 */
/* 426 */	NdrFcShort( 0x138 ),	/* Offset= 312 (738) */
/* 428 */	NdrFcLong( 0x2 ),	/* 2 */
/* 432 */	NdrFcShort( 0x14e ),	/* Offset= 334 (766) */
/* 434 */	NdrFcLong( 0x3 ),	/* 3 */
/* 438 */	NdrFcShort( 0x164 ),	/* Offset= 356 (794) */
/* 440 */	NdrFcLong( 0x14 ),	/* 20 */
/* 444 */	NdrFcShort( 0x17a ),	/* Offset= 378 (822) */
/* 446 */	NdrFcShort( 0xffffffff ),	/* Offset= -1 (445) */
/* 448 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 450 */	NdrFcShort( 0x0 ),	/* 0 */
/* 452 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 454 */	NdrFcShort( 0x0 ),	/* 0 */
/* 456 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 458 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 462 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 464 */	
			0x12, 0x0,	/* FC_UP */
/* 466 */	NdrFcShort( 0xffffff74 ),	/* Offset= -140 (326) */
/* 468 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 470 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 472 */	NdrFcShort( 0x10 ),	/* 16 */
/* 474 */	NdrFcShort( 0x0 ),	/* 0 */
/* 476 */	NdrFcShort( 0x6 ),	/* Offset= 6 (482) */
/* 478 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 480 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 482 */	
			0x11, 0x0,	/* FC_RP */
/* 484 */	NdrFcShort( 0xffffffdc ),	/* Offset= -36 (448) */
/* 486 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 488 */	NdrFcShort( 0x0 ),	/* 0 */
/* 490 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 492 */	NdrFcShort( 0x0 ),	/* 0 */
/* 494 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 496 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 500 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 502 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 504 */	NdrFcShort( 0xffffff58 ),	/* Offset= -168 (336) */
/* 506 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 508 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 510 */	NdrFcShort( 0x10 ),	/* 16 */
/* 512 */	NdrFcShort( 0x0 ),	/* 0 */
/* 514 */	NdrFcShort( 0x6 ),	/* Offset= 6 (520) */
/* 516 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 518 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 520 */	
			0x11, 0x0,	/* FC_RP */
/* 522 */	NdrFcShort( 0xffffffdc ),	/* Offset= -36 (486) */
/* 524 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 526 */	NdrFcShort( 0x0 ),	/* 0 */
/* 528 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 530 */	NdrFcShort( 0x0 ),	/* 0 */
/* 532 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 534 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 538 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 540 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 542 */	NdrFcShort( 0xffffff44 ),	/* Offset= -188 (354) */
/* 544 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 546 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 548 */	NdrFcShort( 0x10 ),	/* 16 */
/* 550 */	NdrFcShort( 0x0 ),	/* 0 */
/* 552 */	NdrFcShort( 0x6 ),	/* Offset= 6 (558) */
/* 554 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 556 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 558 */	
			0x11, 0x0,	/* FC_RP */
/* 560 */	NdrFcShort( 0xffffffdc ),	/* Offset= -36 (524) */
/* 562 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 564 */	NdrFcShort( 0x0 ),	/* 0 */
/* 566 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 568 */	NdrFcShort( 0x0 ),	/* 0 */
/* 570 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 572 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 576 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 578 */	
			0x12, 0x0,	/* FC_UP */
/* 580 */	NdrFcShort( 0x176 ),	/* Offset= 374 (954) */
/* 582 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 584 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 586 */	NdrFcShort( 0x10 ),	/* 16 */
/* 588 */	NdrFcShort( 0x0 ),	/* 0 */
/* 590 */	NdrFcShort( 0x6 ),	/* Offset= 6 (596) */
/* 592 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 594 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 596 */	
			0x11, 0x0,	/* FC_RP */
/* 598 */	NdrFcShort( 0xffffffdc ),	/* Offset= -36 (562) */
/* 600 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 602 */	NdrFcLong( 0x2f ),	/* 47 */
/* 606 */	NdrFcShort( 0x0 ),	/* 0 */
/* 608 */	NdrFcShort( 0x0 ),	/* 0 */
/* 610 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 612 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 614 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 616 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 618 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 620 */	NdrFcShort( 0x1 ),	/* 1 */
/* 622 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 624 */	NdrFcShort( 0x4 ),	/* 4 */
/* 626 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 628 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 630 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 632 */	NdrFcShort( 0x18 ),	/* 24 */
/* 634 */	NdrFcShort( 0x0 ),	/* 0 */
/* 636 */	NdrFcShort( 0xa ),	/* Offset= 10 (646) */
/* 638 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 640 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 642 */	NdrFcShort( 0xffffffd6 ),	/* Offset= -42 (600) */
/* 644 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 646 */	
			0x12, 0x0,	/* FC_UP */
/* 648 */	NdrFcShort( 0xffffffe2 ),	/* Offset= -30 (618) */
/* 650 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 652 */	NdrFcShort( 0x0 ),	/* 0 */
/* 654 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 656 */	NdrFcShort( 0x0 ),	/* 0 */
/* 658 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 660 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 664 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 666 */	
			0x12, 0x0,	/* FC_UP */
/* 668 */	NdrFcShort( 0xffffffda ),	/* Offset= -38 (630) */
/* 670 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 672 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 674 */	NdrFcShort( 0x10 ),	/* 16 */
/* 676 */	NdrFcShort( 0x0 ),	/* 0 */
/* 678 */	NdrFcShort( 0x6 ),	/* Offset= 6 (684) */
/* 680 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 682 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 684 */	
			0x11, 0x0,	/* FC_RP */
/* 686 */	NdrFcShort( 0xffffffdc ),	/* Offset= -36 (650) */
/* 688 */	
			0x1d,		/* FC_SMFARRAY */
			0x0,		/* 0 */
/* 690 */	NdrFcShort( 0x8 ),	/* 8 */
/* 692 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 694 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 696 */	NdrFcShort( 0x10 ),	/* 16 */
/* 698 */	0x8,		/* FC_LONG */
			0x6,		/* FC_SHORT */
/* 700 */	0x6,		/* FC_SHORT */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 702 */	0x0,		/* 0 */
			NdrFcShort( 0xfffffff1 ),	/* Offset= -15 (688) */
			0x5b,		/* FC_END */
/* 706 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 708 */	NdrFcShort( 0x20 ),	/* 32 */
/* 710 */	NdrFcShort( 0x0 ),	/* 0 */
/* 712 */	NdrFcShort( 0xa ),	/* Offset= 10 (722) */
/* 714 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 716 */	0x36,		/* FC_POINTER */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 718 */	0x0,		/* 0 */
			NdrFcShort( 0xffffffe7 ),	/* Offset= -25 (694) */
			0x5b,		/* FC_END */
/* 722 */	
			0x11, 0x0,	/* FC_RP */
/* 724 */	NdrFcShort( 0xffffff12 ),	/* Offset= -238 (486) */
/* 726 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 728 */	NdrFcShort( 0x1 ),	/* 1 */
/* 730 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 732 */	NdrFcShort( 0x0 ),	/* 0 */
/* 734 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 736 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 738 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 740 */	NdrFcShort( 0x10 ),	/* 16 */
/* 742 */	NdrFcShort( 0x0 ),	/* 0 */
/* 744 */	NdrFcShort( 0x6 ),	/* Offset= 6 (750) */
/* 746 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 748 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 750 */	
			0x12, 0x0,	/* FC_UP */
/* 752 */	NdrFcShort( 0xffffffe6 ),	/* Offset= -26 (726) */
/* 754 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 756 */	NdrFcShort( 0x2 ),	/* 2 */
/* 758 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 760 */	NdrFcShort( 0x0 ),	/* 0 */
/* 762 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 764 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 766 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 768 */	NdrFcShort( 0x10 ),	/* 16 */
/* 770 */	NdrFcShort( 0x0 ),	/* 0 */
/* 772 */	NdrFcShort( 0x6 ),	/* Offset= 6 (778) */
/* 774 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 776 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 778 */	
			0x12, 0x0,	/* FC_UP */
/* 780 */	NdrFcShort( 0xffffffe6 ),	/* Offset= -26 (754) */
/* 782 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 784 */	NdrFcShort( 0x4 ),	/* 4 */
/* 786 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 788 */	NdrFcShort( 0x0 ),	/* 0 */
/* 790 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 792 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 794 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 796 */	NdrFcShort( 0x10 ),	/* 16 */
/* 798 */	NdrFcShort( 0x0 ),	/* 0 */
/* 800 */	NdrFcShort( 0x6 ),	/* Offset= 6 (806) */
/* 802 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 804 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 806 */	
			0x12, 0x0,	/* FC_UP */
/* 808 */	NdrFcShort( 0xffffffe6 ),	/* Offset= -26 (782) */
/* 810 */	
			0x1b,		/* FC_CARRAY */
			0x7,		/* 7 */
/* 812 */	NdrFcShort( 0x8 ),	/* 8 */
/* 814 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 816 */	NdrFcShort( 0x0 ),	/* 0 */
/* 818 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 820 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 822 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 824 */	NdrFcShort( 0x10 ),	/* 16 */
/* 826 */	NdrFcShort( 0x0 ),	/* 0 */
/* 828 */	NdrFcShort( 0x6 ),	/* Offset= 6 (834) */
/* 830 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 832 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 834 */	
			0x12, 0x0,	/* FC_UP */
/* 836 */	NdrFcShort( 0xffffffe6 ),	/* Offset= -26 (810) */
/* 838 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 840 */	NdrFcShort( 0x8 ),	/* 8 */
/* 842 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 844 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 846 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 848 */	NdrFcShort( 0x8 ),	/* 8 */
/* 850 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 852 */	NdrFcShort( 0xffc8 ),	/* -56 */
/* 854 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 856 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 858 */	NdrFcShort( 0xffffffec ),	/* Offset= -20 (838) */
/* 860 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 862 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 864 */	NdrFcShort( 0x38 ),	/* 56 */
/* 866 */	NdrFcShort( 0xffffffec ),	/* Offset= -20 (846) */
/* 868 */	NdrFcShort( 0x0 ),	/* Offset= 0 (868) */
/* 870 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 872 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 874 */	0x40,		/* FC_STRUCTPAD4 */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 876 */	0x0,		/* 0 */
			NdrFcShort( 0xfffffe0f ),	/* Offset= -497 (380) */
			0x5b,		/* FC_END */
/* 880 */	
			0x12, 0x0,	/* FC_UP */
/* 882 */	NdrFcShort( 0xffffff04 ),	/* Offset= -252 (630) */
/* 884 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 886 */	0x1,		/* FC_BYTE */
			0x5c,		/* FC_PAD */
/* 888 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 890 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 892 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 894 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 896 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 898 */	0xb,		/* FC_HYPER */
			0x5c,		/* FC_PAD */
/* 900 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 902 */	0xa,		/* FC_FLOAT */
			0x5c,		/* FC_PAD */
/* 904 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 906 */	0xc,		/* FC_DOUBLE */
			0x5c,		/* FC_PAD */
/* 908 */	
			0x12, 0x0,	/* FC_UP */
/* 910 */	NdrFcShort( 0xfffffda2 ),	/* Offset= -606 (304) */
/* 912 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 914 */	NdrFcShort( 0xfffffda4 ),	/* Offset= -604 (310) */
/* 916 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 918 */	NdrFcShort( 0xfffffdba ),	/* Offset= -582 (336) */
/* 920 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 922 */	NdrFcShort( 0xfffffdc8 ),	/* Offset= -568 (354) */
/* 924 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 926 */	NdrFcShort( 0xfffffdd6 ),	/* Offset= -554 (372) */
/* 928 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 930 */	NdrFcShort( 0x2 ),	/* Offset= 2 (932) */
/* 932 */	
			0x12, 0x0,	/* FC_UP */
/* 934 */	NdrFcShort( 0x14 ),	/* Offset= 20 (954) */
/* 936 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 938 */	NdrFcShort( 0x10 ),	/* 16 */
/* 940 */	0x6,		/* FC_SHORT */
			0x1,		/* FC_BYTE */
/* 942 */	0x1,		/* FC_BYTE */
			0x8,		/* FC_LONG */
/* 944 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 946 */	
			0x12, 0x0,	/* FC_UP */
/* 948 */	NdrFcShort( 0xfffffff4 ),	/* Offset= -12 (936) */
/* 950 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 952 */	0x2,		/* FC_CHAR */
			0x5c,		/* FC_PAD */
/* 954 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 956 */	NdrFcShort( 0x20 ),	/* 32 */
/* 958 */	NdrFcShort( 0x0 ),	/* 0 */
/* 960 */	NdrFcShort( 0x0 ),	/* Offset= 0 (960) */
/* 962 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 964 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 966 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 968 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 970 */	NdrFcShort( 0xfffffc3c ),	/* Offset= -964 (6) */
/* 972 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 974 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 976 */	NdrFcShort( 0x0 ),	/* 0 */
/* 978 */	NdrFcShort( 0x18 ),	/* 24 */
/* 980 */	NdrFcShort( 0x0 ),	/* 0 */
/* 982 */	NdrFcShort( 0xfffffc2c ),	/* Offset= -980 (2) */
/* 984 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 986 */	NdrFcShort( 0x2 ),	/* Offset= 2 (988) */
/* 988 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 990 */	NdrFcLong( 0x796386b ),	/* 127285355 */
/* 994 */	NdrFcShort( 0x3123 ),	/* 12579 */
/* 996 */	NdrFcShort( 0x101c ),	/* 4124 */
/* 998 */	0xbb,		/* 187 */
			0x62,		/* 98 */
/* 1000 */	0x0,		/* 0 */
			0xaa,		/* 170 */
/* 1002 */	0x0,		/* 0 */
			0x18,		/* 24 */
/* 1004 */	0x49,		/* 73 */
			0x7c,		/* 124 */
/* 1006 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 1008 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 1010 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1012 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1014 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1016 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1018 */	NdrFcShort( 0xfffffd3c ),	/* Offset= -708 (310) */
/* 1020 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 1022 */	0xd,		/* FC_ENUM16 */
			0x5c,		/* FC_PAD */
/* 1024 */	
			0x11, 0x14,	/* FC_RP [alloced_on_stack] [pointer_deref] */
/* 1026 */	NdrFcShort( 0xffffffda ),	/* Offset= -38 (988) */
/* 1028 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 1030 */	NdrFcShort( 0x6 ),	/* Offset= 6 (1036) */
/* 1032 */	
			0x13, 0x0,	/* FC_OP */
/* 1034 */	NdrFcShort( 0xfffffd3c ),	/* Offset= -708 (326) */
/* 1036 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1038 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1040 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1042 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1044 */	NdrFcShort( 0xfffffff4 ),	/* Offset= -12 (1032) */

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



/* Standard interface: __MIDL_itf_Visinfo_0000, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}} */


/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IVisObjExt, ver. 0.0,
   GUID={0x079638E0,0x3123,0x101C,{0xBB,0x62,0x00,0xAA,0x00,0x18,0x49,0x7C}} */

#pragma code_seg(".orpc")
static const unsigned short IVisObjExt_FormatStringOffsetTable[] =
    {
    0,
    56,
    112,
    162,
    218,
    280,
    330,
    380
    };

static const MIDL_STUBLESS_PROXY_INFO IVisObjExt_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IVisObjExt_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IVisObjExt_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IVisObjExt_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(11) _IVisObjExtProxyVtbl = 
{
    &IVisObjExt_ProxyInfo,
    &IID_IVisObjExt,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IVisObjExt::GetVisInfoClass */ ,
    (void *) (INT_PTR) -1 /* IVisObjExt::SetVisInfoClass */ ,
    (void *) (INT_PTR) -1 /* IVisObjExt::ResetVisInfoClass */ ,
    (void *) (INT_PTR) -1 /* IVisObjExt::GetVisInfoObject */ ,
    (void *) (INT_PTR) -1 /* IVisObjExt::SetVisInfoObject */ ,
    (void *) (INT_PTR) -1 /* IVisObjExt::ResetVisInfoObject */ ,
    (void *) (INT_PTR) -1 /* IVisObjExt::GetObjectHiddenStatus */ ,
    (void *) (INT_PTR) -1 /* IVisObjExt::SetObjectHiddenStatus */
};

const CInterfaceStubVtbl _IVisObjExtStubVtbl =
{
    &IID_IVisObjExt,
    &IVisObjExt_ServerInfo,
    11,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IVisQuery, ver. 0.0,
   GUID={0x079638E3,0x3123,0x101C,{0xBB,0x62,0x00,0xAA,0x00,0x18,0x49,0x7C}} */

#pragma code_seg(".orpc")
static const unsigned short IVisQuery_FormatStringOffsetTable[] =
    {
    430,
    480
    };

static const MIDL_STUBLESS_PROXY_INFO IVisQuery_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IVisQuery_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IVisQuery_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IVisQuery_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(5) _IVisQueryProxyVtbl = 
{
    &IVisQuery_ProxyInfo,
    &IID_IVisQuery,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IVisQuery::GetIdentMode */ ,
    (void *) (INT_PTR) -1 /* IVisQuery::GetObjectVis */
};

const CInterfaceStubVtbl _IVisQueryStubVtbl =
{
    &IID_IVisQuery,
    &IVisQuery_ServerInfo,
    5,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IMergeVisInfo, ver. 0.0,
   GUID={0x079638E4,0x3123,0x101C,{0xBB,0x62,0x00,0xAA,0x00,0x18,0x49,0x7C}} */

#pragma code_seg(".orpc")
static const unsigned short IMergeVisInfo_FormatStringOffsetTable[] =
    {
    524
    };

static const MIDL_STUBLESS_PROXY_INFO IMergeVisInfo_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IMergeVisInfo_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IMergeVisInfo_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IMergeVisInfo_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(4) _IMergeVisInfoProxyVtbl = 
{
    &IMergeVisInfo_ProxyInfo,
    &IID_IMergeVisInfo,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IMergeVisInfo::MergeVisInfo */
};

const CInterfaceStubVtbl _IMergeVisInfoStubVtbl =
{
    &IID_IMergeVisInfo,
    &IMergeVisInfo_ServerInfo,
    4,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IRawVisInfo, ver. 0.0,
   GUID={0x4BAB20A3,0xA922,0x11D1,{0x85,0x88,0x00,0x60,0x08,0x75,0x13,0x8A}} */

#pragma code_seg(".orpc")
static const unsigned short IRawVisInfo_FormatStringOffsetTable[] =
    {
    568,
    612
    };

static const MIDL_STUBLESS_PROXY_INFO IRawVisInfo_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IRawVisInfo_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRawVisInfo_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IRawVisInfo_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(5) _IRawVisInfoProxyVtbl = 
{
    &IRawVisInfo_ProxyInfo,
    &IID_IRawVisInfo,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IRawVisInfo::SetRawData */ ,
    (void *) (INT_PTR) -1 /* IRawVisInfo::RetrieveRawData */
};

const CInterfaceStubVtbl _IRawVisInfoStubVtbl =
{
    &IID_IRawVisInfo,
    &IRawVisInfo_ServerInfo,
    5,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IExtendedObjectVisInfo, ver. 0.0,
   GUID={0x8B4834A5,0xEB76,0x4567,{0xA9,0x7A,0xD3,0x8A,0xCE,0xE0,0x77,0xA6}} */

#pragma code_seg(".orpc")
static const unsigned short IExtendedObjectVisInfo_FormatStringOffsetTable[] =
    {
    656,
    694,
    732,
    770,
    808
    };

static const MIDL_STUBLESS_PROXY_INFO IExtendedObjectVisInfo_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IExtendedObjectVisInfo_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IExtendedObjectVisInfo_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IExtendedObjectVisInfo_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(8) _IExtendedObjectVisInfoProxyVtbl = 
{
    &IExtendedObjectVisInfo_ProxyInfo,
    &IID_IExtendedObjectVisInfo,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IExtendedObjectVisInfo::get_HasInfos */ ,
    (void *) (INT_PTR) -1 /* IExtendedObjectVisInfo::get_ModuleInfo */ ,
    (void *) (INT_PTR) -1 /* IExtendedObjectVisInfo::put_ModuleInfo */ ,
    (void *) (INT_PTR) -1 /* IExtendedObjectVisInfo::get_ExtendedInfo */ ,
    (void *) (INT_PTR) -1 /* IExtendedObjectVisInfo::put_ExtendedInfo */
};

const CInterfaceStubVtbl _IExtendedObjectVisInfoStubVtbl =
{
    &IID_IExtendedObjectVisInfo,
    &IExtendedObjectVisInfo_ServerInfo,
    8,
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

const CInterfaceProxyVtbl * _Visinfo_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_IRawVisInfoProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IExtendedObjectVisInfoProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IVisObjExtProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IVisQueryProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IMergeVisInfoProxyVtbl,
    0
};

const CInterfaceStubVtbl * _Visinfo_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_IRawVisInfoStubVtbl,
    ( CInterfaceStubVtbl *) &_IExtendedObjectVisInfoStubVtbl,
    ( CInterfaceStubVtbl *) &_IVisObjExtStubVtbl,
    ( CInterfaceStubVtbl *) &_IVisQueryStubVtbl,
    ( CInterfaceStubVtbl *) &_IMergeVisInfoStubVtbl,
    0
};

PCInterfaceName const _Visinfo_InterfaceNamesList[] = 
{
    "IRawVisInfo",
    "IExtendedObjectVisInfo",
    "IVisObjExt",
    "IVisQuery",
    "IMergeVisInfo",
    0
};


#define _Visinfo_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _Visinfo, pIID, n)

int __stdcall _Visinfo_IID_Lookup( const IID * pIID, int * pIndex )
{
    IID_BS_LOOKUP_SETUP

    IID_BS_LOOKUP_INITIAL_TEST( _Visinfo, 5, 4 )
    IID_BS_LOOKUP_NEXT_TEST( _Visinfo, 2 )
    IID_BS_LOOKUP_NEXT_TEST( _Visinfo, 1 )
    IID_BS_LOOKUP_RETURN_RESULT( _Visinfo, 5, *pIndex )
    
}

const ExtendedProxyFileInfo Visinfo_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _Visinfo_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _Visinfo_StubVtblList,
    (const PCInterfaceName * ) & _Visinfo_InterfaceNamesList,
    0, // no delegation
    & _Visinfo_IID_Lookup, 
    5,
    2,
    0, /* table of [async_uuid] interfaces */
    0, /* Filler1 */
    0, /* Filler2 */
    0  /* Filler3 */
};


#endif /* defined(_M_IA64) || defined(_M_AMD64)*/

