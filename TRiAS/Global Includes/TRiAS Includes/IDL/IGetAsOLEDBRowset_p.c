/* this ALWAYS GENERATED file contains the proxy stub code */


/* File created by MIDL compiler version 5.01.0164 */
/* at Sat May 05 21:35:49 2001
 */
/* Compiler settings for IGetAsOLEDBRowset.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcproxy.h> version is high enough to compile this file*/
#ifndef __REDQ_RPCPROXY_H_VERSION__
#define __REQUIRED_RPCPROXY_H_VERSION__ 440
#endif


#include "rpcproxy.h"
#ifndef __RPCPROXY_H_VERSION__
#error this stub requires an updated version of <rpcproxy.h>
#endif // __RPCPROXY_H_VERSION__


#include "IGetAsOLEDBRowset.h"

#define TYPE_FORMAT_STRING_SIZE   57                                
#define PROC_FORMAT_STRING_SIZE   23                                

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


/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: _IGetAsOLEDBRowset, ver. 0.0,
   GUID={0x0C60F1D3,0x0C52,0x11d3,{0x80,0x22,0x00,0x80,0x5F,0x9B,0x64,0x5A}} */


extern const MIDL_STUB_DESC Object_StubDesc;


#pragma code_seg(".orpc")

HRESULT STDMETHODCALLTYPE _IGetAsOLEDBRowset_GetAsRowset_Proxy( 
    _IGetAsOLEDBRowset __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *pUnkCreator,
    /* [in] */ IUnknown __RPC_FAR *pUnkOuter,
    /* [in] */ REFIID riid,
    /* [out] */ LONG __RPC_FAR *pcRowsAffected,
    /* [iid_is][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppRowset)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(ppRowset)
        {
        MIDL_memset(
               ppRowset,
               0,
               sizeof( IUnknown __RPC_FAR *__RPC_FAR * ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      3);
        
        
        
        if(!riid)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        if(!pcRowsAffected)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        if(!ppRowset)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U + 0U + 0U;
            NdrInterfacePointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                           (unsigned char __RPC_FAR *)pUnkCreator,
                                           (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2] );
            
            NdrInterfacePointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                           (unsigned char __RPC_FAR *)pUnkOuter,
                                           (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2] );
            
            NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)riid,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[30] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrInterfacePointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                         (unsigned char __RPC_FAR *)pUnkCreator,
                                         (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2] );
            
            NdrInterfacePointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                         (unsigned char __RPC_FAR *)pUnkOuter,
                                         (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2] );
            
            NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)riid,
                                     (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[30] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[0] );
            
            *pcRowsAffected = *(( LONG __RPC_FAR * )_StubMsg.Buffer)++;
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&ppRowset,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[46],
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[42],
                         ( void __RPC_FAR * )pcRowsAffected);
        _StubMsg.MaxCount = (unsigned long) ( riid );
        
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[46],
                         ( void __RPC_FAR * )ppRowset);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB _IGetAsOLEDBRowset_GetAsRowset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    LONG _M0;
    IUnknown __RPC_FAR *__RPC_FAR *_M1;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    IUnknown __RPC_FAR *pUnkCreator;
    IUnknown __RPC_FAR *pUnkOuter;
    LONG __RPC_FAR *pcRowsAffected;
    IUnknown __RPC_FAR *__RPC_FAR *ppRowset;
    REFIID riid;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    pUnkCreator = 0;
    pUnkOuter = 0;
    ( REFIID  )riid = 0;
    ( LONG __RPC_FAR * )pcRowsAffected = 0;
    ( IUnknown __RPC_FAR *__RPC_FAR * )ppRowset = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[0] );
        
        NdrInterfacePointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&pUnkCreator,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2],
                                       (unsigned char)0 );
        
        NdrInterfacePointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&pUnkOuter,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[2],
                                       (unsigned char)0 );
        
        NdrSimpleStructUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR * __RPC_FAR *)&riid,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[30],
                                   (unsigned char)0 );
        
        pcRowsAffected = &_M0;
        ppRowset = &_M1;
        _M1 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((_IGetAsOLEDBRowset*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> GetAsRowset(
               (_IGetAsOLEDBRowset *) ((CStdStubBuffer *)This)->pvServerObject,
               pUnkCreator,
               pUnkOuter,
               riid,
               pcRowsAffected,
               ppRowset);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U + 0U + 4U;
        _StubMsg.MaxCount = (unsigned long) ( riid );
        
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR *)ppRowset,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[46] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( LONG __RPC_FAR * )_StubMsg.Buffer)++ = *pcRowsAffected;
        
        _StubMsg.MaxCount = (unsigned long) ( riid );
        
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char __RPC_FAR *)ppRowset,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[46] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrInterfacePointerFree( &_StubMsg,
                                 (unsigned char __RPC_FAR *)pUnkCreator,
                                 &__MIDL_TypeFormatString.Format[2] );
        
        NdrInterfacePointerFree( &_StubMsg,
                                 (unsigned char __RPC_FAR *)pUnkOuter,
                                 &__MIDL_TypeFormatString.Format[2] );
        
        _StubMsg.MaxCount = (unsigned long) ( riid );
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)ppRowset,
                        &__MIDL_TypeFormatString.Format[46] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


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
    0x10001, /* Ndr library version */
    0,
    0x50100a4, /* MIDL Version 5.1.164 */
    0,
    0,
    0,  /* notify & notify_flag routine table */
    1,  /* Flags */
    0,  /* Reserved3 */
    0,  /* Reserved4 */
    0   /* Reserved5 */
    };

const CINTERFACE_PROXY_VTABLE(4) __IGetAsOLEDBRowsetProxyVtbl = 
{
    &IID__IGetAsOLEDBRowset,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    _IGetAsOLEDBRowset_GetAsRowset_Proxy
};


static const PRPC_STUB_FUNCTION _IGetAsOLEDBRowset_table[] =
{
    _IGetAsOLEDBRowset_GetAsRowset_Stub
};

const CInterfaceStubVtbl __IGetAsOLEDBRowsetStubVtbl =
{
    &IID__IGetAsOLEDBRowset,
    0,
    4,
    &_IGetAsOLEDBRowset_table[-3],
    CStdStubBuffer_METHODS
};

#pragma data_seg(".rdata")

#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

static const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString =
    {
        0,
        {
			
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/*  2 */	NdrFcShort( 0x2 ),	/* Type Offset=2 */
/*  4 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/*  6 */	NdrFcShort( 0x2 ),	/* Type Offset=2 */
/*  8 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 10 */	NdrFcShort( 0x14 ),	/* Type Offset=20 */
/* 12 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 14 */	NdrFcShort( 0x2a ),	/* Type Offset=42 */
/* 16 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 18 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */
/* 20 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
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
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/*  4 */	NdrFcLong( 0x0 ),	/* 0 */
/*  8 */	NdrFcShort( 0x0 ),	/* 0 */
/* 10 */	NdrFcShort( 0x0 ),	/* 0 */
/* 12 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 14 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 16 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 18 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 20 */	
			0x11, 0x0,	/* FC_RP */
/* 22 */	NdrFcShort( 0x8 ),	/* Offset= 8 (30) */
/* 24 */	
			0x1d,		/* FC_SMFARRAY */
			0x0,		/* 0 */
/* 26 */	NdrFcShort( 0x8 ),	/* 8 */
/* 28 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 30 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 32 */	NdrFcShort( 0x10 ),	/* 16 */
/* 34 */	0x8,		/* FC_LONG */
			0x6,		/* FC_SHORT */
/* 36 */	0x6,		/* FC_SHORT */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 38 */	0x0,		/* 0 */
			NdrFcShort( 0xfffffff1 ),	/* Offset= -15 (24) */
			0x5b,		/* FC_END */
/* 42 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 44 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 46 */	
			0x11, 0x14,	/* FC_RP [alloced_on_stack] */
/* 48 */	NdrFcShort( 0x2 ),	/* Offset= 2 (50) */
/* 50 */	
			0x2f,		/* FC_IP */
			0x5c,		/* FC_PAD */
/* 52 */	0x28,		/* Corr desc:  parameter, FC_LONG */
			0x0,		/*  */
#ifndef _ALPHA_
/* 54 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif

			0x0
        }
    };

const CInterfaceProxyVtbl * _IGetAsOLEDBRowset_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &__IGetAsOLEDBRowsetProxyVtbl,
    0
};

const CInterfaceStubVtbl * _IGetAsOLEDBRowset_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &__IGetAsOLEDBRowsetStubVtbl,
    0
};

PCInterfaceName const _IGetAsOLEDBRowset_InterfaceNamesList[] = 
{
    "_IGetAsOLEDBRowset",
    0
};


#define _IGetAsOLEDBRowset_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _IGetAsOLEDBRowset, pIID, n)

int __stdcall _IGetAsOLEDBRowset_IID_Lookup( const IID * pIID, int * pIndex )
{
    
    if(!_IGetAsOLEDBRowset_CHECK_IID(0))
        {
        *pIndex = 0;
        return 1;
        }

    return 0;
}

const ExtendedProxyFileInfo IGetAsOLEDBRowset_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _IGetAsOLEDBRowset_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _IGetAsOLEDBRowset_StubVtblList,
    (const PCInterfaceName * ) & _IGetAsOLEDBRowset_InterfaceNamesList,
    0, // no delegation
    & _IGetAsOLEDBRowset_IID_Lookup, 
    1,
    1,
    0, /* table of [async_uuid] interfaces */
    0, /* Filler1 */
    0, /* Filler2 */
    0  /* Filler3 */
};
