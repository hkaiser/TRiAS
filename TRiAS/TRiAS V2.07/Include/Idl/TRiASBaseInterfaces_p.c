/* this ALWAYS GENERATED file contains the proxy stub code */


/* File created by MIDL compiler version 3.01.76 */
/* at Fri Feb 06 17:59:49 1998
 */
/* Compiler settings for TRiASBaseInterfaces.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )

#define USE_STUBLESS_PROXY

#include "rpcproxy.h"
#include "TRiASBaseInterfaces.h"

#define TYPE_FORMAT_STRING_SIZE   909                               
#define PROC_FORMAT_STRING_SIZE   439                               

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


/* Standard interface: __MIDL_itf_TRiASBaseInterfaces_0000, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}} */


/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IDispatch, ver. 0.0,
   GUID={0x00020400,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: DTRiASBaseClass, ver. 0.0,
   GUID={0x8DE4E3E0,0x4D53,0x101B,{0xAA,0xE1,0xE7,0xE7,0xE7,0xE7,0xE7,0xE7}} */


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO DTRiASBaseClass_ServerInfo;

#pragma code_seg(".orpc")
static const unsigned short DTRiASBaseClass_FormatStringOffsetTable[] = 
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    0,
    24,
    48,
    72,
    96
    };

static const MIDL_SERVER_INFO DTRiASBaseClass_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &DTRiASBaseClass_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO DTRiASBaseClass_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &DTRiASBaseClass_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };

CINTERFACE_PROXY_VTABLE(12) _DTRiASBaseClassProxyVtbl = 
{
    &DTRiASBaseClass_ProxyInfo,
    &IID_DTRiASBaseClass,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *)-1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *)-1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *)-1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *)-1 /* DTRiASBaseClass::get_isA */ ,
    (void *)-1 /* DTRiASBaseClass::get_Parent */ ,
    (void *)-1 /* DTRiASBaseClass::put_Parent */ ,
    (void *)-1 /* DTRiASBaseClass::get_Application */ ,
    (void *)-1 /* DTRiASBaseClass::put_Application */
};


static const PRPC_STUB_FUNCTION DTRiASBaseClass_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _DTRiASBaseClassStubVtbl =
{
    &IID_DTRiASBaseClass,
    &DTRiASBaseClass_ServerInfo,
    12,
    &DTRiASBaseClass_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: DTRiASCollection, ver. 0.0,
   GUID={0x8DE4E3DF,0x4D53,0x101B,{0xAA,0xE1,0xE7,0xE7,0xE7,0xE7,0xE7,0xE7}} */


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO DTRiASCollection_ServerInfo;

#pragma code_seg(".orpc")
static const unsigned short DTRiASCollection_FormatStringOffsetTable[] = 
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    0,
    24,
    48,
    72,
    96,
    120,
    144,
    174,
    198,
    228,
    252
    };

static const MIDL_SERVER_INFO DTRiASCollection_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &DTRiASCollection_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO DTRiASCollection_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &DTRiASCollection_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };

CINTERFACE_PROXY_VTABLE(18) _DTRiASCollectionProxyVtbl = 
{
    &DTRiASCollection_ProxyInfo,
    &IID_DTRiASCollection,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *)-1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *)-1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *)-1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *)-1 /* DTRiASBaseClass::get_isA */ ,
    (void *)-1 /* DTRiASBaseClass::get_Parent */ ,
    (void *)-1 /* DTRiASBaseClass::put_Parent */ ,
    (void *)-1 /* DTRiASBaseClass::get_Application */ ,
    (void *)-1 /* DTRiASBaseClass::put_Application */ ,
    (void *)-1 /* DTRiASCollection::get_Count */ ,
    (void *)-1 /* DTRiASCollection::Item */ ,
    (void *)-1 /* DTRiASCollection::_NewEnum */ ,
    (void *)-1 /* DTRiASCollection::Add */ ,
    (void *)-1 /* DTRiASCollection::Remove */ ,
    (void *)-1 /* DTRiASCollection::Refresh */
};


static const PRPC_STUB_FUNCTION DTRiASCollection_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
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

CInterfaceStubVtbl _DTRiASCollectionStubVtbl =
{
    &IID_DTRiASCollection,
    &DTRiASCollection_ServerInfo,
    18,
    &DTRiASCollection_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: DTRiASProperty, ver. 0.0,
   GUID={0x079638C1,0x3123,0x101C,{0xBB,0x62,0x00,0xAA,0x00,0x18,0x49,0x7C}} */


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO DTRiASProperty_ServerInfo;

#pragma code_seg(".orpc")
static const unsigned short DTRiASProperty_FormatStringOffsetTable[] = 
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    0,
    24,
    48,
    72,
    96,
    270,
    294,
    318,
    342,
    366,
    390,
    414
    };

static const MIDL_SERVER_INFO DTRiASProperty_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &DTRiASProperty_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO DTRiASProperty_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &DTRiASProperty_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };

CINTERFACE_PROXY_VTABLE(19) _DTRiASPropertyProxyVtbl = 
{
    &DTRiASProperty_ProxyInfo,
    &IID_DTRiASProperty,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *)-1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *)-1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *)-1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *)-1 /* DTRiASBaseClass::get_isA */ ,
    (void *)-1 /* DTRiASBaseClass::get_Parent */ ,
    (void *)-1 /* DTRiASBaseClass::put_Parent */ ,
    (void *)-1 /* DTRiASBaseClass::get_Application */ ,
    (void *)-1 /* DTRiASBaseClass::put_Application */ ,
    (void *)-1 /* DTRiASProperty::get_Value */ ,
    (void *)-1 /* DTRiASProperty::put_Value */ ,
    (void *)-1 /* DTRiASProperty::get_Name */ ,
    (void *)-1 /* DTRiASProperty::put_Name */ ,
    (void *)-1 /* DTRiASProperty::get_Inherited */ ,
    (void *)-1 /* DTRiASProperty::get_Type */ ,
    (void *)-1 /* DTRiASProperty::put_Type */
};


static const PRPC_STUB_FUNCTION DTRiASProperty_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
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

CInterfaceStubVtbl _DTRiASPropertyStubVtbl =
{
    &IID_DTRiASProperty,
    &DTRiASProperty_ServerInfo,
    19,
    &DTRiASProperty_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: DTRiASProperties, ver. 0.0,
   GUID={0x079638C2,0x3123,0x101C,{0xBB,0x62,0x00,0xAA,0x00,0x18,0x49,0x7C}} */


extern const MIDL_STUB_DESC Object_StubDesc;


#pragma code_seg(".orpc")
extern const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[2];

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

CINTERFACE_PROXY_VTABLE(18) _DTRiASPropertiesProxyVtbl = 
{
    0,
    &IID_DTRiASProperties,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *)-1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *)-1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *)-1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    0 /* forced delegation DTRiASBaseClass::get_isA */ ,
    0 /* forced delegation DTRiASBaseClass::get_Parent */ ,
    0 /* forced delegation DTRiASBaseClass::put_Parent */ ,
    0 /* forced delegation DTRiASBaseClass::get_Application */ ,
    0 /* forced delegation DTRiASBaseClass::put_Application */ ,
    0 /* forced delegation DTRiASCollection::get_Count */ ,
    0 /* forced delegation DTRiASCollection::Item */ ,
    0 /* forced delegation DTRiASCollection::_NewEnum */ ,
    0 /* forced delegation DTRiASCollection::Add */ ,
    0 /* forced delegation DTRiASCollection::Remove */ ,
    0 /* forced delegation DTRiASCollection::Refresh */
};


static const PRPC_STUB_FUNCTION DTRiASProperties_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
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

CInterfaceStubVtbl _DTRiASPropertiesStubVtbl =
{
    &IID_DTRiASProperties,
    0,
    18,
    &DTRiASProperties_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};

#pragma data_seg(".rdata")

static const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[2] = 
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


#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

#if !(TARGET_IS_NT40_OR_LATER)
#error You need a Windows NT 4.0 or later to run this stub because it uses these features:
#error   -Oif or -Oicf, [wire_marshal] or [user_marshal] attribute.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will die there with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure get_isA */

			0x33,		/* FC_AUTO_HANDLE */
			0x64,		/* 100 */
/*  2 */	NdrFcShort( 0x7 ),	/* 7 */
#ifndef _ALPHA_
/*  4 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/*  6 */	NdrFcShort( 0x0 ),	/* 0 */
/*  8 */	NdrFcShort( 0x10 ),	/* 16 */
/* 10 */	0x4,		/* 4 */
			0x2,		/* 2 */

	/* Parameter RTTI */

/* 12 */	NdrFcShort( 0x2150 ),	/* 8528 */
#ifndef _ALPHA_
/* 14 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 16 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 18 */	NdrFcShort( 0x70 ),	/* 112 */
#ifndef _ALPHA_
/* 20 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 22 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Parent */

/* 24 */	0x33,		/* FC_AUTO_HANDLE */
			0x64,		/* 100 */
/* 26 */	NdrFcShort( 0x8 ),	/* 8 */
#ifndef _ALPHA_
/* 28 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 30 */	NdrFcShort( 0x0 ),	/* 0 */
/* 32 */	NdrFcShort( 0x8 ),	/* 8 */
/* 34 */	0x5,		/* 5 */
			0x2,		/* 2 */

	/* Parameter Base */

/* 36 */	NdrFcShort( 0x13 ),	/* 19 */
#ifndef _ALPHA_
/* 38 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 40 */	NdrFcShort( 0x4 ),	/* Type Offset=4 */

	/* Return value */

/* 42 */	NdrFcShort( 0x70 ),	/* 112 */
#ifndef _ALPHA_
/* 44 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 46 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Parent */

/* 48 */	0x33,		/* FC_AUTO_HANDLE */
			0x64,		/* 100 */
/* 50 */	NdrFcShort( 0x9 ),	/* 9 */
#ifndef _ALPHA_
/* 52 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 54 */	NdrFcShort( 0x0 ),	/* 0 */
/* 56 */	NdrFcShort( 0x8 ),	/* 8 */
/* 58 */	0x6,		/* 6 */
			0x2,		/* 2 */

	/* Parameter Base */

/* 60 */	NdrFcShort( 0xb ),	/* 11 */
#ifndef _ALPHA_
/* 62 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 64 */	NdrFcShort( 0x8 ),	/* Type Offset=8 */

	/* Return value */

/* 66 */	NdrFcShort( 0x70 ),	/* 112 */
#ifndef _ALPHA_
/* 68 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 70 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Application */

/* 72 */	0x33,		/* FC_AUTO_HANDLE */
			0x64,		/* 100 */
/* 74 */	NdrFcShort( 0xa ),	/* 10 */
#ifndef _ALPHA_
/* 76 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 78 */	NdrFcShort( 0x0 ),	/* 0 */
/* 80 */	NdrFcShort( 0x8 ),	/* 8 */
/* 82 */	0x5,		/* 5 */
			0x2,		/* 2 */

	/* Parameter App */

/* 84 */	NdrFcShort( 0x13 ),	/* 19 */
#ifndef _ALPHA_
/* 86 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 88 */	NdrFcShort( 0x4 ),	/* Type Offset=4 */

	/* Return value */

/* 90 */	NdrFcShort( 0x70 ),	/* 112 */
#ifndef _ALPHA_
/* 92 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 94 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Application */

/* 96 */	0x33,		/* FC_AUTO_HANDLE */
			0x64,		/* 100 */
/* 98 */	NdrFcShort( 0xb ),	/* 11 */
#ifndef _ALPHA_
/* 100 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 102 */	NdrFcShort( 0x0 ),	/* 0 */
/* 104 */	NdrFcShort( 0x8 ),	/* 8 */
/* 106 */	0x6,		/* 6 */
			0x2,		/* 2 */

	/* Parameter App */

/* 108 */	NdrFcShort( 0xb ),	/* 11 */
#ifndef _ALPHA_
/* 110 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 112 */	NdrFcShort( 0x8 ),	/* Type Offset=8 */

	/* Return value */

/* 114 */	NdrFcShort( 0x70 ),	/* 112 */
#ifndef _ALPHA_
/* 116 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 118 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Count */

/* 120 */	0x33,		/* FC_AUTO_HANDLE */
			0x64,		/* 100 */
/* 122 */	NdrFcShort( 0xc ),	/* 12 */
#ifndef _ALPHA_
/* 124 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 126 */	NdrFcShort( 0x0 ),	/* 0 */
/* 128 */	NdrFcShort( 0x10 ),	/* 16 */
/* 130 */	0x4,		/* 4 */
			0x2,		/* 2 */

	/* Parameter Count */

/* 132 */	NdrFcShort( 0x2150 ),	/* 8528 */
#ifndef _ALPHA_
/* 134 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 136 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 138 */	NdrFcShort( 0x70 ),	/* 112 */
#ifndef _ALPHA_
/* 140 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 142 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Item */

/* 144 */	0x33,		/* FC_AUTO_HANDLE */
			0x64,		/* 100 */
/* 146 */	NdrFcShort( 0xd ),	/* 13 */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 148 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
#else
			NdrFcShort( 0x20 ),	/* MIPS & PPC Stack size/offset = 32 */
#endif
#else
			NdrFcShort( 0x28 ),	/* Alpha Stack size/offset = 40 */
#endif
/* 150 */	NdrFcShort( 0x0 ),	/* 0 */
/* 152 */	NdrFcShort( 0x8 ),	/* 8 */
/* 154 */	0x7,		/* 7 */
			0x3,		/* 3 */

	/* Parameter Which */

/* 156 */	NdrFcShort( 0x8b ),	/* 139 */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 158 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* MIPS & PPC Stack size/offset = 8 */
#endif
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 160 */	NdrFcShort( 0x32a ),	/* Type Offset=810 */

	/* Parameter Item */

/* 162 */	NdrFcShort( 0x13 ),	/* 19 */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 164 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
#else
			NdrFcShort( 0x18 ),	/* MIPS & PPC Stack size/offset = 24 */
#endif
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 166 */	NdrFcShort( 0x4 ),	/* Type Offset=4 */

	/* Return value */

/* 168 */	NdrFcShort( 0x70 ),	/* 112 */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 170 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
#else
			NdrFcShort( 0x1c ),	/* MIPS & PPC Stack size/offset = 28 */
#endif
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 172 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure _NewEnum */

/* 174 */	0x33,		/* FC_AUTO_HANDLE */
			0x64,		/* 100 */
/* 176 */	NdrFcShort( 0xe ),	/* 14 */
#ifndef _ALPHA_
/* 178 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 180 */	NdrFcShort( 0x0 ),	/* 0 */
/* 182 */	NdrFcShort( 0x8 ),	/* 8 */
/* 184 */	0x5,		/* 5 */
			0x2,		/* 2 */

	/* Parameter NewEnum */

/* 186 */	NdrFcShort( 0x13 ),	/* 19 */
#ifndef _ALPHA_
/* 188 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 190 */	NdrFcShort( 0x334 ),	/* Type Offset=820 */

	/* Return value */

/* 192 */	NdrFcShort( 0x70 ),	/* 112 */
#ifndef _ALPHA_
/* 194 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 196 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Add */

/* 198 */	0x33,		/* FC_AUTO_HANDLE */
			0x64,		/* 100 */
/* 200 */	NdrFcShort( 0xf ),	/* 15 */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 202 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
#else
			NdrFcShort( 0x20 ),	/* MIPS & PPC Stack size/offset = 32 */
#endif
#else
			NdrFcShort( 0x28 ),	/* Alpha Stack size/offset = 40 */
#endif
/* 204 */	NdrFcShort( 0x0 ),	/* 0 */
/* 206 */	NdrFcShort( 0x8 ),	/* 8 */
/* 208 */	0x7,		/* 7 */
			0x3,		/* 3 */

	/* Parameter ToAdd */

/* 210 */	NdrFcShort( 0x8b ),	/* 139 */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 212 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* MIPS & PPC Stack size/offset = 8 */
#endif
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 214 */	NdrFcShort( 0x338 ),	/* Type Offset=824 */

	/* Parameter NewItem */

/* 216 */	NdrFcShort( 0x13 ),	/* 19 */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 218 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
#else
			NdrFcShort( 0x18 ),	/* MIPS & PPC Stack size/offset = 24 */
#endif
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 220 */	NdrFcShort( 0x4 ),	/* Type Offset=4 */

	/* Return value */

/* 222 */	NdrFcShort( 0x70 ),	/* 112 */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 224 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
#else
			NdrFcShort( 0x1c ),	/* MIPS & PPC Stack size/offset = 28 */
#endif
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 226 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Remove */

/* 228 */	0x33,		/* FC_AUTO_HANDLE */
			0x64,		/* 100 */
/* 230 */	NdrFcShort( 0x10 ),	/* 16 */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 232 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
#else
			NdrFcShort( 0x1c ),	/* MIPS & PPC Stack size/offset = 28 */
#endif
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 234 */	NdrFcShort( 0x0 ),	/* 0 */
/* 236 */	NdrFcShort( 0x8 ),	/* 8 */
/* 238 */	0x6,		/* 6 */
			0x2,		/* 2 */

	/* Parameter ToRemove */

/* 240 */	NdrFcShort( 0x8b ),	/* 139 */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 242 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* MIPS & PPC Stack size/offset = 8 */
#endif
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 244 */	NdrFcShort( 0x342 ),	/* Type Offset=834 */

	/* Return value */

/* 246 */	NdrFcShort( 0x70 ),	/* 112 */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 248 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
#else
			NdrFcShort( 0x18 ),	/* MIPS & PPC Stack size/offset = 24 */
#endif
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 250 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Refresh */

/* 252 */	0x33,		/* FC_AUTO_HANDLE */
			0x64,		/* 100 */
/* 254 */	NdrFcShort( 0x11 ),	/* 17 */
#ifndef _ALPHA_
/* 256 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 258 */	NdrFcShort( 0x0 ),	/* 0 */
/* 260 */	NdrFcShort( 0x8 ),	/* 8 */
/* 262 */	0x4,		/* 4 */
			0x1,		/* 1 */

	/* Return value */

/* 264 */	NdrFcShort( 0x70 ),	/* 112 */
#ifndef _ALPHA_
/* 266 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 268 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Value */

/* 270 */	0x33,		/* FC_AUTO_HANDLE */
			0x64,		/* 100 */
/* 272 */	NdrFcShort( 0xc ),	/* 12 */
#ifndef _ALPHA_
/* 274 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 276 */	NdrFcShort( 0x0 ),	/* 0 */
/* 278 */	NdrFcShort( 0x8 ),	/* 8 */
/* 280 */	0x5,		/* 5 */
			0x2,		/* 2 */

	/* Parameter Value */

/* 282 */	NdrFcShort( 0x4113 ),	/* 16659 */
#ifndef _ALPHA_
/* 284 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 286 */	NdrFcShort( 0x354 ),	/* Type Offset=852 */

	/* Return value */

/* 288 */	NdrFcShort( 0x70 ),	/* 112 */
#ifndef _ALPHA_
/* 290 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 292 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Value */

/* 294 */	0x33,		/* FC_AUTO_HANDLE */
			0x64,		/* 100 */
/* 296 */	NdrFcShort( 0xd ),	/* 13 */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 298 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
#else
			NdrFcShort( 0x1c ),	/* MIPS & PPC Stack size/offset = 28 */
#endif
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 300 */	NdrFcShort( 0x0 ),	/* 0 */
/* 302 */	NdrFcShort( 0x8 ),	/* 8 */
/* 304 */	0x6,		/* 6 */
			0x2,		/* 2 */

	/* Parameter Value */

/* 306 */	NdrFcShort( 0x8b ),	/* 139 */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 308 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* MIPS & PPC Stack size/offset = 8 */
#endif
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 310 */	NdrFcShort( 0x35e ),	/* Type Offset=862 */

	/* Return value */

/* 312 */	NdrFcShort( 0x70 ),	/* 112 */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 314 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
#else
			NdrFcShort( 0x18 ),	/* MIPS & PPC Stack size/offset = 24 */
#endif
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 316 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Name */

/* 318 */	0x33,		/* FC_AUTO_HANDLE */
			0x64,		/* 100 */
/* 320 */	NdrFcShort( 0xe ),	/* 14 */
#ifndef _ALPHA_
/* 322 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 324 */	NdrFcShort( 0x0 ),	/* 0 */
/* 326 */	NdrFcShort( 0x8 ),	/* 8 */
/* 328 */	0x5,		/* 5 */
			0x2,		/* 2 */

	/* Parameter Name */

/* 330 */	NdrFcShort( 0x2113 ),	/* 8467 */
#ifndef _ALPHA_
/* 332 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 334 */	NdrFcShort( 0x370 ),	/* Type Offset=880 */

	/* Return value */

/* 336 */	NdrFcShort( 0x70 ),	/* 112 */
#ifndef _ALPHA_
/* 338 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 340 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Name */

/* 342 */	0x33,		/* FC_AUTO_HANDLE */
			0x64,		/* 100 */
/* 344 */	NdrFcShort( 0xf ),	/* 15 */
#ifndef _ALPHA_
/* 346 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 348 */	NdrFcShort( 0x0 ),	/* 0 */
/* 350 */	NdrFcShort( 0x8 ),	/* 8 */
/* 352 */	0x6,		/* 6 */
			0x2,		/* 2 */

	/* Parameter Name */

/* 354 */	NdrFcShort( 0x8b ),	/* 139 */
#ifndef _ALPHA_
/* 356 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 358 */	NdrFcShort( 0x37a ),	/* Type Offset=890 */

	/* Return value */

/* 360 */	NdrFcShort( 0x70 ),	/* 112 */
#ifndef _ALPHA_
/* 362 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 364 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Inherited */

/* 366 */	0x33,		/* FC_AUTO_HANDLE */
			0x64,		/* 100 */
/* 368 */	NdrFcShort( 0x10 ),	/* 16 */
#ifndef _ALPHA_
/* 370 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 372 */	NdrFcShort( 0x0 ),	/* 0 */
/* 374 */	NdrFcShort( 0xe ),	/* 14 */
/* 376 */	0x4,		/* 4 */
			0x2,		/* 2 */

	/* Parameter IsInherited */

/* 378 */	NdrFcShort( 0x2150 ),	/* 8528 */
#ifndef _ALPHA_
/* 380 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 382 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 384 */	NdrFcShort( 0x70 ),	/* 112 */
#ifndef _ALPHA_
/* 386 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 388 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Type */

/* 390 */	0x33,		/* FC_AUTO_HANDLE */
			0x64,		/* 100 */
/* 392 */	NdrFcShort( 0x11 ),	/* 17 */
#ifndef _ALPHA_
/* 394 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 396 */	NdrFcShort( 0x0 ),	/* 0 */
/* 398 */	NdrFcShort( 0xe ),	/* 14 */
/* 400 */	0x4,		/* 4 */
			0x2,		/* 2 */

	/* Parameter PropType */

/* 402 */	NdrFcShort( 0x2010 ),	/* 8208 */
#ifndef _ALPHA_
/* 404 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 406 */	NdrFcShort( 0x388 ),	/* Type Offset=904 */

	/* Return value */

/* 408 */	NdrFcShort( 0x70 ),	/* 112 */
#ifndef _ALPHA_
/* 410 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 412 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Type */

/* 414 */	0x33,		/* FC_AUTO_HANDLE */
			0x64,		/* 100 */
/* 416 */	NdrFcShort( 0x12 ),	/* 18 */
#ifndef _ALPHA_
/* 418 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 420 */	NdrFcShort( 0x6 ),	/* 6 */
/* 422 */	NdrFcShort( 0x8 ),	/* 8 */
/* 424 */	0x4,		/* 4 */
			0x2,		/* 2 */

	/* Parameter PropType */

/* 426 */	NdrFcShort( 0x48 ),	/* 72 */
#ifndef _ALPHA_
/* 428 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 430 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Return value */

/* 432 */	NdrFcShort( 0x70 ),	/* 112 */
#ifndef _ALPHA_
/* 434 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 436 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

			0x0
        }
    };

static const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString =
    {
        0,
        {
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/*  2 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/*  4 */	
			0x11, 0x10,	/* FC_RP */
/*  6 */	NdrFcShort( 0x2 ),	/* Offset= 2 (8) */
/*  8 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 10 */	NdrFcLong( 0x20400 ),	/* 132096 */
/* 14 */	NdrFcShort( 0x0 ),	/* 0 */
/* 16 */	NdrFcShort( 0x0 ),	/* 0 */
/* 18 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 20 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 22 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 24 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 26 */	
			0x12, 0x0,	/* FC_UP */
/* 28 */	NdrFcShort( 0x2fa ),	/* Offset= 762 (790) */
/* 30 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x6,		/* FC_SHORT */
/* 32 */	0x6,		/* 6 */
			0x0,		/*  */
/* 34 */	NdrFcShort( 0xfffffff8 ),	/* -8 */
/* 36 */	NdrFcShort( 0x2 ),	/* Offset= 2 (38) */
/* 38 */	NdrFcShort( 0x10 ),	/* 16 */
/* 40 */	NdrFcShort( 0x29 ),	/* 41 */
/* 42 */	NdrFcLong( 0x3 ),	/* 3 */
/* 46 */	NdrFcShort( 0xffff8008 ),	/* Offset= -32760 (-32714) */
/* 48 */	NdrFcLong( 0x11 ),	/* 17 */
/* 52 */	NdrFcShort( 0xffff8002 ),	/* Offset= -32766 (-32714) */
/* 54 */	NdrFcLong( 0x2 ),	/* 2 */
/* 58 */	NdrFcShort( 0xffff8006 ),	/* Offset= -32762 (-32704) */
/* 60 */	NdrFcLong( 0x4 ),	/* 4 */
/* 64 */	NdrFcShort( 0xffff800a ),	/* Offset= -32758 (-32694) */
/* 66 */	NdrFcLong( 0x5 ),	/* 5 */
/* 70 */	NdrFcShort( 0xffff800c ),	/* Offset= -32756 (-32686) */
/* 72 */	NdrFcLong( 0xb ),	/* 11 */
/* 76 */	NdrFcShort( 0xffff8006 ),	/* Offset= -32762 (-32686) */
/* 78 */	NdrFcLong( 0xa ),	/* 10 */
/* 82 */	NdrFcShort( 0xffff8008 ),	/* Offset= -32760 (-32678) */
/* 84 */	NdrFcLong( 0x6 ),	/* 6 */
/* 88 */	NdrFcShort( 0xca ),	/* Offset= 202 (290) */
/* 90 */	NdrFcLong( 0x7 ),	/* 7 */
/* 94 */	NdrFcShort( 0xffff800c ),	/* Offset= -32756 (-32662) */
/* 96 */	NdrFcLong( 0x8 ),	/* 8 */
/* 100 */	NdrFcShort( 0xc4 ),	/* Offset= 196 (296) */
/* 102 */	NdrFcLong( 0xd ),	/* 13 */
/* 106 */	NdrFcShort( 0xd6 ),	/* Offset= 214 (320) */
/* 108 */	NdrFcLong( 0x9 ),	/* 9 */
/* 112 */	NdrFcShort( 0xffffff98 ),	/* Offset= -104 (8) */
/* 114 */	NdrFcLong( 0x2000 ),	/* 8192 */
/* 118 */	NdrFcShort( 0xdc ),	/* Offset= 220 (338) */
/* 120 */	NdrFcLong( 0x4011 ),	/* 16401 */
/* 124 */	NdrFcShort( 0x25a ),	/* Offset= 602 (726) */
/* 126 */	NdrFcLong( 0x4002 ),	/* 16386 */
/* 130 */	NdrFcShort( 0x258 ),	/* Offset= 600 (730) */
/* 132 */	NdrFcLong( 0x4003 ),	/* 16387 */
/* 136 */	NdrFcShort( 0x256 ),	/* Offset= 598 (734) */
/* 138 */	NdrFcLong( 0x4004 ),	/* 16388 */
/* 142 */	NdrFcShort( 0x254 ),	/* Offset= 596 (738) */
/* 144 */	NdrFcLong( 0x4005 ),	/* 16389 */
/* 148 */	NdrFcShort( 0x252 ),	/* Offset= 594 (742) */
/* 150 */	NdrFcLong( 0x400b ),	/* 16395 */
/* 154 */	NdrFcShort( 0x240 ),	/* Offset= 576 (730) */
/* 156 */	NdrFcLong( 0x400a ),	/* 16394 */
/* 160 */	NdrFcShort( 0x23e ),	/* Offset= 574 (734) */
/* 162 */	NdrFcLong( 0x4006 ),	/* 16390 */
/* 166 */	NdrFcShort( 0x244 ),	/* Offset= 580 (746) */
/* 168 */	NdrFcLong( 0x4007 ),	/* 16391 */
/* 172 */	NdrFcShort( 0x23a ),	/* Offset= 570 (742) */
/* 174 */	NdrFcLong( 0x4008 ),	/* 16392 */
/* 178 */	NdrFcShort( 0x23c ),	/* Offset= 572 (750) */
/* 180 */	NdrFcLong( 0x400d ),	/* 16397 */
/* 184 */	NdrFcShort( 0x23a ),	/* Offset= 570 (754) */
/* 186 */	NdrFcLong( 0x4009 ),	/* 16393 */
/* 190 */	NdrFcShort( 0x238 ),	/* Offset= 568 (758) */
/* 192 */	NdrFcLong( 0x6000 ),	/* 24576 */
/* 196 */	NdrFcShort( 0x236 ),	/* Offset= 566 (762) */
/* 198 */	NdrFcLong( 0x400c ),	/* 16396 */
/* 202 */	NdrFcShort( 0x234 ),	/* Offset= 564 (766) */
/* 204 */	NdrFcLong( 0x10 ),	/* 16 */
/* 208 */	NdrFcShort( 0xffff8002 ),	/* Offset= -32766 (-32558) */
/* 210 */	NdrFcLong( 0x12 ),	/* 18 */
/* 214 */	NdrFcShort( 0xffff8006 ),	/* Offset= -32762 (-32548) */
/* 216 */	NdrFcLong( 0x13 ),	/* 19 */
/* 220 */	NdrFcShort( 0xffff8008 ),	/* Offset= -32760 (-32540) */
/* 222 */	NdrFcLong( 0x16 ),	/* 22 */
/* 226 */	NdrFcShort( 0xffff8008 ),	/* Offset= -32760 (-32534) */
/* 228 */	NdrFcLong( 0x17 ),	/* 23 */
/* 232 */	NdrFcShort( 0xffff8008 ),	/* Offset= -32760 (-32528) */
/* 234 */	NdrFcLong( 0xe ),	/* 14 */
/* 238 */	NdrFcShort( 0x218 ),	/* Offset= 536 (774) */
/* 240 */	NdrFcLong( 0x400e ),	/* 16398 */
/* 244 */	NdrFcShort( 0x21e ),	/* Offset= 542 (786) */
/* 246 */	NdrFcLong( 0x4010 ),	/* 16400 */
/* 250 */	NdrFcShort( 0x1dc ),	/* Offset= 476 (726) */
/* 252 */	NdrFcLong( 0x4012 ),	/* 16402 */
/* 256 */	NdrFcShort( 0x1da ),	/* Offset= 474 (730) */
/* 258 */	NdrFcLong( 0x4013 ),	/* 16403 */
/* 262 */	NdrFcShort( 0x1d8 ),	/* Offset= 472 (734) */
/* 264 */	NdrFcLong( 0x4016 ),	/* 16406 */
/* 268 */	NdrFcShort( 0x1d2 ),	/* Offset= 466 (734) */
/* 270 */	NdrFcLong( 0x4017 ),	/* 16407 */
/* 274 */	NdrFcShort( 0x1cc ),	/* Offset= 460 (734) */
/* 276 */	NdrFcLong( 0x0 ),	/* 0 */
/* 280 */	NdrFcShort( 0x0 ),	/* Offset= 0 (280) */
/* 282 */	NdrFcLong( 0x1 ),	/* 1 */
/* 286 */	NdrFcShort( 0x0 ),	/* Offset= 0 (286) */
/* 288 */	NdrFcShort( 0xffffffff ),	/* Offset= -1 (287) */
/* 290 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 292 */	NdrFcShort( 0x8 ),	/* 8 */
/* 294 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 296 */	
			0x12, 0x0,	/* FC_UP */
/* 298 */	NdrFcShort( 0xc ),	/* Offset= 12 (310) */
/* 300 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 302 */	NdrFcShort( 0x2 ),	/* 2 */
/* 304 */	0x9,		/* 9 */
			0x0,		/*  */
/* 306 */	NdrFcShort( 0xfffffffc ),	/* -4 */
/* 308 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 310 */	
			0x17,		/* FC_CSTRUCT */
			0x3,		/* 3 */
/* 312 */	NdrFcShort( 0x8 ),	/* 8 */
/* 314 */	NdrFcShort( 0xfffffff2 ),	/* Offset= -14 (300) */
/* 316 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 318 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 320 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 322 */	NdrFcLong( 0x0 ),	/* 0 */
/* 326 */	NdrFcShort( 0x0 ),	/* 0 */
/* 328 */	NdrFcShort( 0x0 ),	/* 0 */
/* 330 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 332 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 334 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 336 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 338 */	
			0x12, 0x0,	/* FC_UP */
/* 340 */	NdrFcShort( 0x170 ),	/* Offset= 368 (708) */
/* 342 */	
			0x2a,		/* FC_ENCAPSULATED_UNION */
			0x48,		/* 72 */
/* 344 */	NdrFcShort( 0x8 ),	/* 8 */
/* 346 */	NdrFcShort( 0x8 ),	/* 8 */
/* 348 */	NdrFcLong( 0x8 ),	/* 8 */
/* 352 */	NdrFcShort( 0x4c ),	/* Offset= 76 (428) */
/* 354 */	NdrFcLong( 0xd ),	/* 13 */
/* 358 */	NdrFcShort( 0x6c ),	/* Offset= 108 (466) */
/* 360 */	NdrFcLong( 0x9 ),	/* 9 */
/* 364 */	NdrFcShort( 0x88 ),	/* Offset= 136 (500) */
/* 366 */	NdrFcLong( 0xc ),	/* 12 */
/* 370 */	NdrFcShort( 0xb0 ),	/* Offset= 176 (546) */
/* 372 */	NdrFcLong( 0x10 ),	/* 16 */
/* 376 */	NdrFcShort( 0xc8 ),	/* Offset= 200 (576) */
/* 378 */	NdrFcLong( 0x2 ),	/* 2 */
/* 382 */	NdrFcShort( 0xe0 ),	/* Offset= 224 (606) */
/* 384 */	NdrFcLong( 0x3 ),	/* 3 */
/* 388 */	NdrFcShort( 0xf8 ),	/* Offset= 248 (636) */
/* 390 */	NdrFcLong( 0x14 ),	/* 20 */
/* 394 */	NdrFcShort( 0x110 ),	/* Offset= 272 (666) */
/* 396 */	NdrFcShort( 0x0 ),	/* Offset= 0 (396) */
/* 398 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 400 */	NdrFcShort( 0x4 ),	/* 4 */
/* 402 */	0x18,		/* 24 */
			0x0,		/*  */
/* 404 */	NdrFcShort( 0x0 ),	/* 0 */
/* 406 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 408 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 410 */	NdrFcShort( 0x4 ),	/* 4 */
/* 412 */	NdrFcShort( 0x0 ),	/* 0 */
/* 414 */	NdrFcShort( 0x1 ),	/* 1 */
/* 416 */	NdrFcShort( 0x0 ),	/* 0 */
/* 418 */	NdrFcShort( 0x0 ),	/* 0 */
/* 420 */	0x12, 0x0,	/* FC_UP */
/* 422 */	NdrFcShort( 0xffffff90 ),	/* Offset= -112 (310) */
/* 424 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 426 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 428 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 430 */	NdrFcShort( 0x8 ),	/* 8 */
/* 432 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 434 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 436 */	NdrFcShort( 0x4 ),	/* 4 */
/* 438 */	NdrFcShort( 0x4 ),	/* 4 */
/* 440 */	0x11, 0x0,	/* FC_RP */
/* 442 */	NdrFcShort( 0xffffffd4 ),	/* Offset= -44 (398) */
/* 444 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 446 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 448 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 450 */	NdrFcShort( 0x0 ),	/* 0 */
/* 452 */	0x18,		/* 24 */
			0x0,		/*  */
/* 454 */	NdrFcShort( 0x0 ),	/* 0 */
/* 456 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 460 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 462 */	NdrFcShort( 0xffffff72 ),	/* Offset= -142 (320) */
/* 464 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 466 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 468 */	NdrFcShort( 0x8 ),	/* 8 */
/* 470 */	NdrFcShort( 0x0 ),	/* 0 */
/* 472 */	NdrFcShort( 0x6 ),	/* Offset= 6 (478) */
/* 474 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 476 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 478 */	
			0x11, 0x0,	/* FC_RP */
/* 480 */	NdrFcShort( 0xffffffe0 ),	/* Offset= -32 (448) */
/* 482 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 484 */	NdrFcShort( 0x0 ),	/* 0 */
/* 486 */	0x18,		/* 24 */
			0x0,		/*  */
/* 488 */	NdrFcShort( 0x0 ),	/* 0 */
/* 490 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 494 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 496 */	NdrFcShort( 0xfffffe18 ),	/* Offset= -488 (8) */
/* 498 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 500 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 502 */	NdrFcShort( 0x8 ),	/* 8 */
/* 504 */	NdrFcShort( 0x0 ),	/* 0 */
/* 506 */	NdrFcShort( 0x6 ),	/* Offset= 6 (512) */
/* 508 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 510 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 512 */	
			0x11, 0x0,	/* FC_RP */
/* 514 */	NdrFcShort( 0xffffffe0 ),	/* Offset= -32 (482) */
/* 516 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 518 */	NdrFcShort( 0x4 ),	/* 4 */
/* 520 */	0x18,		/* 24 */
			0x0,		/*  */
/* 522 */	NdrFcShort( 0x0 ),	/* 0 */
/* 524 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 526 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 528 */	NdrFcShort( 0x4 ),	/* 4 */
/* 530 */	NdrFcShort( 0x0 ),	/* 0 */
/* 532 */	NdrFcShort( 0x1 ),	/* 1 */
/* 534 */	NdrFcShort( 0x0 ),	/* 0 */
/* 536 */	NdrFcShort( 0x0 ),	/* 0 */
/* 538 */	0x12, 0x0,	/* FC_UP */
/* 540 */	NdrFcShort( 0xfa ),	/* Offset= 250 (790) */
/* 542 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 544 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 546 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 548 */	NdrFcShort( 0x8 ),	/* 8 */
/* 550 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 552 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 554 */	NdrFcShort( 0x4 ),	/* 4 */
/* 556 */	NdrFcShort( 0x4 ),	/* 4 */
/* 558 */	0x11, 0x0,	/* FC_RP */
/* 560 */	NdrFcShort( 0xffffffd4 ),	/* Offset= -44 (516) */
/* 562 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 564 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 566 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 568 */	NdrFcShort( 0x1 ),	/* 1 */
/* 570 */	0x19,		/* 25 */
			0x0,		/*  */
/* 572 */	NdrFcShort( 0x0 ),	/* 0 */
/* 574 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 576 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 578 */	NdrFcShort( 0x8 ),	/* 8 */
/* 580 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 582 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 584 */	NdrFcShort( 0x4 ),	/* 4 */
/* 586 */	NdrFcShort( 0x4 ),	/* 4 */
/* 588 */	0x12, 0x0,	/* FC_UP */
/* 590 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (566) */
/* 592 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 594 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 596 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 598 */	NdrFcShort( 0x2 ),	/* 2 */
/* 600 */	0x19,		/* 25 */
			0x0,		/*  */
/* 602 */	NdrFcShort( 0x0 ),	/* 0 */
/* 604 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 606 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 608 */	NdrFcShort( 0x8 ),	/* 8 */
/* 610 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 612 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 614 */	NdrFcShort( 0x4 ),	/* 4 */
/* 616 */	NdrFcShort( 0x4 ),	/* 4 */
/* 618 */	0x12, 0x0,	/* FC_UP */
/* 620 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (596) */
/* 622 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 624 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 626 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 628 */	NdrFcShort( 0x4 ),	/* 4 */
/* 630 */	0x19,		/* 25 */
			0x0,		/*  */
/* 632 */	NdrFcShort( 0x0 ),	/* 0 */
/* 634 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 636 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 638 */	NdrFcShort( 0x8 ),	/* 8 */
/* 640 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 642 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 644 */	NdrFcShort( 0x4 ),	/* 4 */
/* 646 */	NdrFcShort( 0x4 ),	/* 4 */
/* 648 */	0x12, 0x0,	/* FC_UP */
/* 650 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (626) */
/* 652 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 654 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 656 */	
			0x1b,		/* FC_CARRAY */
			0x7,		/* 7 */
/* 658 */	NdrFcShort( 0x8 ),	/* 8 */
/* 660 */	0x19,		/* 25 */
			0x0,		/*  */
/* 662 */	NdrFcShort( 0x0 ),	/* 0 */
/* 664 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 666 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 668 */	NdrFcShort( 0x8 ),	/* 8 */
/* 670 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 672 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 674 */	NdrFcShort( 0x4 ),	/* 4 */
/* 676 */	NdrFcShort( 0x4 ),	/* 4 */
/* 678 */	0x12, 0x0,	/* FC_UP */
/* 680 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (656) */
/* 682 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 684 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 686 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 688 */	NdrFcShort( 0x8 ),	/* 8 */
/* 690 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 692 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 694 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 696 */	NdrFcShort( 0x8 ),	/* 8 */
/* 698 */	0x6,		/* 6 */
			0x0,		/*  */
/* 700 */	NdrFcShort( 0xffffffe8 ),	/* -24 */
/* 702 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 704 */	NdrFcShort( 0xffffffee ),	/* Offset= -18 (686) */
/* 706 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 708 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 710 */	NdrFcShort( 0x18 ),	/* 24 */
/* 712 */	NdrFcShort( 0xffffffee ),	/* Offset= -18 (694) */
/* 714 */	NdrFcShort( 0x0 ),	/* Offset= 0 (714) */
/* 716 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 718 */	0x38,		/* FC_ALIGNM4 */
			0x8,		/* FC_LONG */
/* 720 */	0x8,		/* FC_LONG */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 722 */	0x0,		/* 0 */
			NdrFcShort( 0xfffffe83 ),	/* Offset= -381 (342) */
			0x5b,		/* FC_END */
/* 726 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 728 */	0x2,		/* FC_CHAR */
			0x5c,		/* FC_PAD */
/* 730 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 732 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 734 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 736 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 738 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 740 */	0xa,		/* FC_FLOAT */
			0x5c,		/* FC_PAD */
/* 742 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 744 */	0xc,		/* FC_DOUBLE */
			0x5c,		/* FC_PAD */
/* 746 */	
			0x12, 0x0,	/* FC_UP */
/* 748 */	NdrFcShort( 0xfffffe36 ),	/* Offset= -458 (290) */
/* 750 */	
			0x12, 0x10,	/* FC_UP */
/* 752 */	NdrFcShort( 0xfffffe38 ),	/* Offset= -456 (296) */
/* 754 */	
			0x12, 0x10,	/* FC_UP */
/* 756 */	NdrFcShort( 0xfffffe4c ),	/* Offset= -436 (320) */
/* 758 */	
			0x12, 0x10,	/* FC_UP */
/* 760 */	NdrFcShort( 0xfffffd10 ),	/* Offset= -752 (8) */
/* 762 */	
			0x12, 0x10,	/* FC_UP */
/* 764 */	NdrFcShort( 0xfffffe56 ),	/* Offset= -426 (338) */
/* 766 */	
			0x12, 0x10,	/* FC_UP */
/* 768 */	NdrFcShort( 0x2 ),	/* Offset= 2 (770) */
/* 770 */	
			0x12, 0x0,	/* FC_UP */
/* 772 */	NdrFcShort( 0xfffffcfc ),	/* Offset= -772 (0) */
/* 774 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 776 */	NdrFcShort( 0x10 ),	/* 16 */
/* 778 */	0x6,		/* FC_SHORT */
			0x2,		/* FC_CHAR */
/* 780 */	0x2,		/* FC_CHAR */
			0x38,		/* FC_ALIGNM4 */
/* 782 */	0x8,		/* FC_LONG */
			0x39,		/* FC_ALIGNM8 */
/* 784 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 786 */	
			0x12, 0x0,	/* FC_UP */
/* 788 */	NdrFcShort( 0xfffffff2 ),	/* Offset= -14 (774) */
/* 790 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 792 */	NdrFcShort( 0x20 ),	/* 32 */
/* 794 */	NdrFcShort( 0x0 ),	/* 0 */
/* 796 */	NdrFcShort( 0x0 ),	/* Offset= 0 (796) */
/* 798 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 800 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 802 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 804 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 806 */	NdrFcShort( 0xfffffcf8 ),	/* Offset= -776 (30) */
/* 808 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 810 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 812 */	NdrFcShort( 0x0 ),	/* 0 */
/* 814 */	NdrFcShort( 0x10 ),	/* 16 */
/* 816 */	NdrFcShort( 0x0 ),	/* 0 */
/* 818 */	NdrFcShort( 0xfffffce8 ),	/* Offset= -792 (26) */
/* 820 */	
			0x11, 0x10,	/* FC_RP */
/* 822 */	NdrFcShort( 0xfffffe0a ),	/* Offset= -502 (320) */
/* 824 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 826 */	NdrFcShort( 0x0 ),	/* 0 */
/* 828 */	NdrFcShort( 0x10 ),	/* 16 */
/* 830 */	NdrFcShort( 0x0 ),	/* 0 */
/* 832 */	NdrFcShort( 0xfffffcda ),	/* Offset= -806 (26) */
/* 834 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 836 */	NdrFcShort( 0x0 ),	/* 0 */
/* 838 */	NdrFcShort( 0x10 ),	/* 16 */
/* 840 */	NdrFcShort( 0x0 ),	/* 0 */
/* 842 */	NdrFcShort( 0xfffffcd0 ),	/* Offset= -816 (26) */
/* 844 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 846 */	NdrFcShort( 0x6 ),	/* Offset= 6 (852) */
/* 848 */	
			0x13, 0x0,	/* FC_OP */
/* 850 */	NdrFcShort( 0xffffffc4 ),	/* Offset= -60 (790) */
/* 852 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 854 */	NdrFcShort( 0x0 ),	/* 0 */
/* 856 */	NdrFcShort( 0x10 ),	/* 16 */
/* 858 */	NdrFcShort( 0x0 ),	/* 0 */
/* 860 */	NdrFcShort( 0xfffffff4 ),	/* Offset= -12 (848) */
/* 862 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 864 */	NdrFcShort( 0x0 ),	/* 0 */
/* 866 */	NdrFcShort( 0x10 ),	/* 16 */
/* 868 */	NdrFcShort( 0x0 ),	/* 0 */
/* 870 */	NdrFcShort( 0xfffffcb4 ),	/* Offset= -844 (26) */
/* 872 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 874 */	NdrFcShort( 0x6 ),	/* Offset= 6 (880) */
/* 876 */	
			0x13, 0x0,	/* FC_OP */
/* 878 */	NdrFcShort( 0xfffffdc8 ),	/* Offset= -568 (310) */
/* 880 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 882 */	NdrFcShort( 0x1 ),	/* 1 */
/* 884 */	NdrFcShort( 0x4 ),	/* 4 */
/* 886 */	NdrFcShort( 0x0 ),	/* 0 */
/* 888 */	NdrFcShort( 0xfffffff4 ),	/* Offset= -12 (876) */
/* 890 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 892 */	NdrFcShort( 0x1 ),	/* 1 */
/* 894 */	NdrFcShort( 0x4 ),	/* 4 */
/* 896 */	NdrFcShort( 0x0 ),	/* 0 */
/* 898 */	NdrFcShort( 0xfffffda6 ),	/* Offset= -602 (296) */
/* 900 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 902 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 904 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 906 */	0xd,		/* FC_ENUM16 */
			0x5c,		/* FC_PAD */

			0x0
        }
    };

const CInterfaceProxyVtbl * _TRiASBaseInterfaces_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_DTRiASPropertyProxyVtbl,
    ( CInterfaceProxyVtbl *) &_DTRiASPropertiesProxyVtbl,
    ( CInterfaceProxyVtbl *) &_DTRiASCollectionProxyVtbl,
    ( CInterfaceProxyVtbl *) &_DTRiASBaseClassProxyVtbl,
    0
};

const CInterfaceStubVtbl * _TRiASBaseInterfaces_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_DTRiASPropertyStubVtbl,
    ( CInterfaceStubVtbl *) &_DTRiASPropertiesStubVtbl,
    ( CInterfaceStubVtbl *) &_DTRiASCollectionStubVtbl,
    ( CInterfaceStubVtbl *) &_DTRiASBaseClassStubVtbl,
    0
};

PCInterfaceName const _TRiASBaseInterfaces_InterfaceNamesList[] = 
{
    "DTRiASProperty",
    "DTRiASProperties",
    "DTRiASCollection",
    "DTRiASBaseClass",
    0
};

const IID *  _TRiASBaseInterfaces_BaseIIDList[] = 
{
    &IID_IDispatch,
    &IID_IDispatch,
    &IID_IDispatch,
    &IID_IDispatch,
    0
};


#define _TRiASBaseInterfaces_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _TRiASBaseInterfaces, pIID, n)

int __stdcall _TRiASBaseInterfaces_IID_Lookup( const IID * pIID, int * pIndex )
{
    IID_BS_LOOKUP_SETUP

    IID_BS_LOOKUP_INITIAL_TEST( _TRiASBaseInterfaces, 4, 2 )
    IID_BS_LOOKUP_NEXT_TEST( _TRiASBaseInterfaces, 1 )
    IID_BS_LOOKUP_RETURN_RESULT( _TRiASBaseInterfaces, 4, *pIndex )
    
}

const ExtendedProxyFileInfo TRiASBaseInterfaces_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _TRiASBaseInterfaces_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _TRiASBaseInterfaces_StubVtblList,
    (const PCInterfaceName * ) & _TRiASBaseInterfaces_InterfaceNamesList,
    (const IID ** ) & _TRiASBaseInterfaces_BaseIIDList,
    & _TRiASBaseInterfaces_IID_Lookup, 
    4,
    2
};
