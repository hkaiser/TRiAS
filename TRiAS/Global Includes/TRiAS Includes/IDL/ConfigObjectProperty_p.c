

/* this ALWAYS GENERATED file contains the proxy stub code */


 /* File created by MIDL compiler version 6.00.0361 */
/* at Thu Jan 16 12:35:34 2003
 */
/* Compiler settings for ConfigObjectProperty.Idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#if !defined(_M_IA64) && !defined(_M_AMD64)


#pragma warning( disable: 4049 )  /* more than 64k source lines */
#if _MSC_VER >= 1200
#pragma warning(push)
#endif
#pragma warning( disable: 4100 ) /* unreferenced arguments in x86 call */
#pragma warning( disable: 4211 )  /* redefine extent to static */
#pragma warning( disable: 4232 )  /* dllimport identity*/
#define USE_STUBLESS_PROXY


/* verify that the <rpcproxy.h> version is high enough to compile this file*/
#ifndef __REDQ_RPCPROXY_H_VERSION__
#define __REQUIRED_RPCPROXY_H_VERSION__ 475
#endif


#include "rpcproxy.h"
#ifndef __RPCPROXY_H_VERSION__
#error this stub requires an updated version of <rpcproxy.h>
#endif // __RPCPROXY_H_VERSION__


#include "ConfigObjectProperty.h"

#define TYPE_FORMAT_STRING_SIZE   1153                              
#define PROC_FORMAT_STRING_SIZE   187                               
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   3            

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


extern const MIDL_SERVER_INFO IConfigObjectProperty_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IConfigObjectProperty_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IConfigSequenceForObjectProperty_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IConfigSequenceForObjectProperty_ProxyInfo;


extern const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ];

#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

#if !(TARGET_IS_NT50_OR_LATER)
#error You need a Windows 2000 or later to run this stub because it uses these features:
#error   /robust command line switch.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will die there with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure ConfigObjectProperty */

			0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/*  2 */	NdrFcLong( 0x0 ),	/* 0 */
/*  6 */	NdrFcShort( 0x3 ),	/* 3 */
/*  8 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 10 */	NdrFcShort( 0x0 ),	/* 0 */
/* 12 */	NdrFcShort( 0x8 ),	/* 8 */
/* 14 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 16 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 18 */	NdrFcShort( 0x0 ),	/* 0 */
/* 20 */	NdrFcShort( 0x1 ),	/* 1 */
/* 22 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter hWnd */

/* 24 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 26 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 28 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */

	/* Return value */

/* 30 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 32 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 34 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_IsConfigured */

/* 36 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 38 */	NdrFcLong( 0x0 ),	/* 0 */
/* 42 */	NdrFcShort( 0x4 ),	/* 4 */
/* 44 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 46 */	NdrFcShort( 0x0 ),	/* 0 */
/* 48 */	NdrFcShort( 0x22 ),	/* 34 */
/* 50 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 52 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 54 */	NdrFcShort( 0x0 ),	/* 0 */
/* 56 */	NdrFcShort( 0x0 ),	/* 0 */
/* 58 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ConfigState */

/* 60 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 62 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 64 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 66 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 68 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 70 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure AddAction */

/* 72 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 74 */	NdrFcLong( 0x0 ),	/* 0 */
/* 78 */	NdrFcShort( 0x3 ),	/* 3 */
/* 80 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 82 */	NdrFcShort( 0x0 ),	/* 0 */
/* 84 */	NdrFcShort( 0x8 ),	/* 8 */
/* 86 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 88 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 90 */	NdrFcShort( 0x0 ),	/* 0 */
/* 92 */	NdrFcShort( 0x0 ),	/* 0 */
/* 94 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pIAct */

/* 96 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 98 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 100 */	NdrFcShort( 0x28 ),	/* Type Offset=40 */

	/* Return value */

/* 102 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 104 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 106 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure AddActionsByCLSID */

/* 108 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 110 */	NdrFcLong( 0x0 ),	/* 0 */
/* 114 */	NdrFcShort( 0x4 ),	/* 4 */
/* 116 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 118 */	NdrFcShort( 0x0 ),	/* 0 */
/* 120 */	NdrFcShort( 0x8 ),	/* 8 */
/* 122 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 124 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 126 */	NdrFcShort( 0x0 ),	/* 0 */
/* 128 */	NdrFcShort( 0x23 ),	/* 35 */
/* 130 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pcsClsId */

/* 132 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 134 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 136 */	NdrFcShort( 0x446 ),	/* Type Offset=1094 */

	/* Return value */

/* 138 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 140 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 142 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure PrepareActions */

/* 144 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 146 */	NdrFcLong( 0x0 ),	/* 0 */
/* 150 */	NdrFcShort( 0x5 ),	/* 5 */
/* 152 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 154 */	NdrFcShort( 0x0 ),	/* 0 */
/* 156 */	NdrFcShort( 0x8 ),	/* 8 */
/* 158 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 160 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 162 */	NdrFcShort( 0x0 ),	/* 0 */
/* 164 */	NdrFcShort( 0x1 ),	/* 1 */
/* 166 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter hParent */

/* 168 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 170 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 172 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */

	/* Parameter pIData */

/* 174 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 176 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 178 */	NdrFcShort( 0x46e ),	/* Type Offset=1134 */

	/* Return value */

/* 180 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 182 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 184 */	0x8,		/* FC_LONG */
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
/*  4 */	NdrFcShort( 0x2 ),	/* Offset= 2 (6) */
/*  6 */	
			0x2a,		/* FC_ENCAPSULATED_UNION */
			0x48,		/* 72 */
/*  8 */	NdrFcShort( 0x4 ),	/* 4 */
/* 10 */	NdrFcShort( 0x2 ),	/* 2 */
/* 12 */	NdrFcLong( 0x48746457 ),	/* 1215587415 */
/* 16 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 18 */	NdrFcLong( 0x52746457 ),	/* 1383359575 */
/* 22 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 24 */	NdrFcShort( 0xffff ),	/* Offset= -1 (23) */
/* 26 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 28 */	NdrFcShort( 0x0 ),	/* 0 */
/* 30 */	NdrFcShort( 0x4 ),	/* 4 */
/* 32 */	NdrFcShort( 0x0 ),	/* 0 */
/* 34 */	NdrFcShort( 0xffe0 ),	/* Offset= -32 (2) */
/* 36 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 38 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 40 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 42 */	NdrFcLong( 0x0 ),	/* 0 */
/* 46 */	NdrFcShort( 0x0 ),	/* 0 */
/* 48 */	NdrFcShort( 0x0 ),	/* 0 */
/* 50 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 52 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 54 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 56 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 58 */	
			0x11, 0x0,	/* FC_RP */
/* 60 */	NdrFcShort( 0x40a ),	/* Offset= 1034 (1094) */
/* 62 */	
			0x12, 0x0,	/* FC_UP */
/* 64 */	NdrFcShort( 0x8 ),	/* Offset= 8 (72) */
/* 66 */	
			0x1d,		/* FC_SMFARRAY */
			0x0,		/* 0 */
/* 68 */	NdrFcShort( 0x8 ),	/* 8 */
/* 70 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 72 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 74 */	NdrFcShort( 0x10 ),	/* 16 */
/* 76 */	0x8,		/* FC_LONG */
			0x6,		/* FC_SHORT */
/* 78 */	0x6,		/* FC_SHORT */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 80 */	0x0,		/* 0 */
			NdrFcShort( 0xfff1 ),	/* Offset= -15 (66) */
			0x5b,		/* FC_END */
/* 84 */	
			0x12, 0x0,	/* FC_UP */
/* 86 */	NdrFcShort( 0x3dc ),	/* Offset= 988 (1074) */
/* 88 */	
			0x12, 0x0,	/* FC_UP */
/* 90 */	NdrFcShort( 0x3c4 ),	/* Offset= 964 (1054) */
/* 92 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 94 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 96 */	NdrFcShort( 0xfff8 ),	/* -8 */
/* 98 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 100 */	NdrFcShort( 0x2 ),	/* Offset= 2 (102) */
/* 102 */	NdrFcShort( 0x10 ),	/* 16 */
/* 104 */	NdrFcShort( 0x2f ),	/* 47 */
/* 106 */	NdrFcLong( 0x14 ),	/* 20 */
/* 110 */	NdrFcShort( 0x800b ),	/* Simple arm type: FC_HYPER */
/* 112 */	NdrFcLong( 0x3 ),	/* 3 */
/* 116 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 118 */	NdrFcLong( 0x11 ),	/* 17 */
/* 122 */	NdrFcShort( 0x8001 ),	/* Simple arm type: FC_BYTE */
/* 124 */	NdrFcLong( 0x2 ),	/* 2 */
/* 128 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 130 */	NdrFcLong( 0x4 ),	/* 4 */
/* 134 */	NdrFcShort( 0x800a ),	/* Simple arm type: FC_FLOAT */
/* 136 */	NdrFcLong( 0x5 ),	/* 5 */
/* 140 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 142 */	NdrFcLong( 0xb ),	/* 11 */
/* 146 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 148 */	NdrFcLong( 0xa ),	/* 10 */
/* 152 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 154 */	NdrFcLong( 0x6 ),	/* 6 */
/* 158 */	NdrFcShort( 0xe8 ),	/* Offset= 232 (390) */
/* 160 */	NdrFcLong( 0x7 ),	/* 7 */
/* 164 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 166 */	NdrFcLong( 0x8 ),	/* 8 */
/* 170 */	NdrFcShort( 0xe2 ),	/* Offset= 226 (396) */
/* 172 */	NdrFcLong( 0xd ),	/* 13 */
/* 176 */	NdrFcShort( 0xff78 ),	/* Offset= -136 (40) */
/* 178 */	NdrFcLong( 0x9 ),	/* 9 */
/* 182 */	NdrFcShort( 0xf0 ),	/* Offset= 240 (422) */
/* 184 */	NdrFcLong( 0x2000 ),	/* 8192 */
/* 188 */	NdrFcShort( 0xfc ),	/* Offset= 252 (440) */
/* 190 */	NdrFcLong( 0x24 ),	/* 36 */
/* 194 */	NdrFcShort( 0x312 ),	/* Offset= 786 (980) */
/* 196 */	NdrFcLong( 0x4024 ),	/* 16420 */
/* 200 */	NdrFcShort( 0x30c ),	/* Offset= 780 (980) */
/* 202 */	NdrFcLong( 0x4011 ),	/* 16401 */
/* 206 */	NdrFcShort( 0x30a ),	/* Offset= 778 (984) */
/* 208 */	NdrFcLong( 0x4002 ),	/* 16386 */
/* 212 */	NdrFcShort( 0x308 ),	/* Offset= 776 (988) */
/* 214 */	NdrFcLong( 0x4003 ),	/* 16387 */
/* 218 */	NdrFcShort( 0x306 ),	/* Offset= 774 (992) */
/* 220 */	NdrFcLong( 0x4014 ),	/* 16404 */
/* 224 */	NdrFcShort( 0x304 ),	/* Offset= 772 (996) */
/* 226 */	NdrFcLong( 0x4004 ),	/* 16388 */
/* 230 */	NdrFcShort( 0x302 ),	/* Offset= 770 (1000) */
/* 232 */	NdrFcLong( 0x4005 ),	/* 16389 */
/* 236 */	NdrFcShort( 0x300 ),	/* Offset= 768 (1004) */
/* 238 */	NdrFcLong( 0x400b ),	/* 16395 */
/* 242 */	NdrFcShort( 0x2ea ),	/* Offset= 746 (988) */
/* 244 */	NdrFcLong( 0x400a ),	/* 16394 */
/* 248 */	NdrFcShort( 0x2e8 ),	/* Offset= 744 (992) */
/* 250 */	NdrFcLong( 0x4006 ),	/* 16390 */
/* 254 */	NdrFcShort( 0x2f2 ),	/* Offset= 754 (1008) */
/* 256 */	NdrFcLong( 0x4007 ),	/* 16391 */
/* 260 */	NdrFcShort( 0x2e8 ),	/* Offset= 744 (1004) */
/* 262 */	NdrFcLong( 0x4008 ),	/* 16392 */
/* 266 */	NdrFcShort( 0x2ea ),	/* Offset= 746 (1012) */
/* 268 */	NdrFcLong( 0x400d ),	/* 16397 */
/* 272 */	NdrFcShort( 0x2e8 ),	/* Offset= 744 (1016) */
/* 274 */	NdrFcLong( 0x4009 ),	/* 16393 */
/* 278 */	NdrFcShort( 0x2e6 ),	/* Offset= 742 (1020) */
/* 280 */	NdrFcLong( 0x6000 ),	/* 24576 */
/* 284 */	NdrFcShort( 0x2e4 ),	/* Offset= 740 (1024) */
/* 286 */	NdrFcLong( 0x400c ),	/* 16396 */
/* 290 */	NdrFcShort( 0x2e2 ),	/* Offset= 738 (1028) */
/* 292 */	NdrFcLong( 0x10 ),	/* 16 */
/* 296 */	NdrFcShort( 0x8002 ),	/* Simple arm type: FC_CHAR */
/* 298 */	NdrFcLong( 0x12 ),	/* 18 */
/* 302 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 304 */	NdrFcLong( 0x13 ),	/* 19 */
/* 308 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 310 */	NdrFcLong( 0x15 ),	/* 21 */
/* 314 */	NdrFcShort( 0x800b ),	/* Simple arm type: FC_HYPER */
/* 316 */	NdrFcLong( 0x16 ),	/* 22 */
/* 320 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 322 */	NdrFcLong( 0x17 ),	/* 23 */
/* 326 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 328 */	NdrFcLong( 0xe ),	/* 14 */
/* 332 */	NdrFcShort( 0x2c0 ),	/* Offset= 704 (1036) */
/* 334 */	NdrFcLong( 0x400e ),	/* 16398 */
/* 338 */	NdrFcShort( 0x2c4 ),	/* Offset= 708 (1046) */
/* 340 */	NdrFcLong( 0x4010 ),	/* 16400 */
/* 344 */	NdrFcShort( 0x2c2 ),	/* Offset= 706 (1050) */
/* 346 */	NdrFcLong( 0x4012 ),	/* 16402 */
/* 350 */	NdrFcShort( 0x27e ),	/* Offset= 638 (988) */
/* 352 */	NdrFcLong( 0x4013 ),	/* 16403 */
/* 356 */	NdrFcShort( 0x27c ),	/* Offset= 636 (992) */
/* 358 */	NdrFcLong( 0x4015 ),	/* 16405 */
/* 362 */	NdrFcShort( 0x27a ),	/* Offset= 634 (996) */
/* 364 */	NdrFcLong( 0x4016 ),	/* 16406 */
/* 368 */	NdrFcShort( 0x270 ),	/* Offset= 624 (992) */
/* 370 */	NdrFcLong( 0x4017 ),	/* 16407 */
/* 374 */	NdrFcShort( 0x26a ),	/* Offset= 618 (992) */
/* 376 */	NdrFcLong( 0x0 ),	/* 0 */
/* 380 */	NdrFcShort( 0x0 ),	/* Offset= 0 (380) */
/* 382 */	NdrFcLong( 0x1 ),	/* 1 */
/* 386 */	NdrFcShort( 0x0 ),	/* Offset= 0 (386) */
/* 388 */	NdrFcShort( 0xffff ),	/* Offset= -1 (387) */
/* 390 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 392 */	NdrFcShort( 0x8 ),	/* 8 */
/* 394 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 396 */	
			0x12, 0x0,	/* FC_UP */
/* 398 */	NdrFcShort( 0xe ),	/* Offset= 14 (412) */
/* 400 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 402 */	NdrFcShort( 0x2 ),	/* 2 */
/* 404 */	0x9,		/* Corr desc: FC_ULONG */
			0x0,		/*  */
/* 406 */	NdrFcShort( 0xfffc ),	/* -4 */
/* 408 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 410 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 412 */	
			0x17,		/* FC_CSTRUCT */
			0x3,		/* 3 */
/* 414 */	NdrFcShort( 0x8 ),	/* 8 */
/* 416 */	NdrFcShort( 0xfff0 ),	/* Offset= -16 (400) */
/* 418 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 420 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 422 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 424 */	NdrFcLong( 0x20400 ),	/* 132096 */
/* 428 */	NdrFcShort( 0x0 ),	/* 0 */
/* 430 */	NdrFcShort( 0x0 ),	/* 0 */
/* 432 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 434 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 436 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 438 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 440 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 442 */	NdrFcShort( 0x2 ),	/* Offset= 2 (444) */
/* 444 */	
			0x12, 0x0,	/* FC_UP */
/* 446 */	NdrFcShort( 0x204 ),	/* Offset= 516 (962) */
/* 448 */	
			0x2a,		/* FC_ENCAPSULATED_UNION */
			0x49,		/* 73 */
/* 450 */	NdrFcShort( 0x18 ),	/* 24 */
/* 452 */	NdrFcShort( 0xa ),	/* 10 */
/* 454 */	NdrFcLong( 0x8 ),	/* 8 */
/* 458 */	NdrFcShort( 0x5a ),	/* Offset= 90 (548) */
/* 460 */	NdrFcLong( 0xd ),	/* 13 */
/* 464 */	NdrFcShort( 0x7e ),	/* Offset= 126 (590) */
/* 466 */	NdrFcLong( 0x9 ),	/* 9 */
/* 470 */	NdrFcShort( 0x9e ),	/* Offset= 158 (628) */
/* 472 */	NdrFcLong( 0xc ),	/* 12 */
/* 476 */	NdrFcShort( 0xc8 ),	/* Offset= 200 (676) */
/* 478 */	NdrFcLong( 0x24 ),	/* 36 */
/* 482 */	NdrFcShort( 0x124 ),	/* Offset= 292 (774) */
/* 484 */	NdrFcLong( 0x800d ),	/* 32781 */
/* 488 */	NdrFcShort( 0x12e ),	/* Offset= 302 (790) */
/* 490 */	NdrFcLong( 0x10 ),	/* 16 */
/* 494 */	NdrFcShort( 0x148 ),	/* Offset= 328 (822) */
/* 496 */	NdrFcLong( 0x2 ),	/* 2 */
/* 500 */	NdrFcShort( 0x162 ),	/* Offset= 354 (854) */
/* 502 */	NdrFcLong( 0x3 ),	/* 3 */
/* 506 */	NdrFcShort( 0x17c ),	/* Offset= 380 (886) */
/* 508 */	NdrFcLong( 0x14 ),	/* 20 */
/* 512 */	NdrFcShort( 0x196 ),	/* Offset= 406 (918) */
/* 514 */	NdrFcShort( 0xffff ),	/* Offset= -1 (513) */
/* 516 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 518 */	NdrFcShort( 0x4 ),	/* 4 */
/* 520 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 522 */	NdrFcShort( 0x0 ),	/* 0 */
/* 524 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 526 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 528 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 530 */	NdrFcShort( 0x4 ),	/* 4 */
/* 532 */	NdrFcShort( 0x0 ),	/* 0 */
/* 534 */	NdrFcShort( 0x1 ),	/* 1 */
/* 536 */	NdrFcShort( 0x0 ),	/* 0 */
/* 538 */	NdrFcShort( 0x0 ),	/* 0 */
/* 540 */	0x12, 0x0,	/* FC_UP */
/* 542 */	NdrFcShort( 0xff7e ),	/* Offset= -130 (412) */
/* 544 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 546 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 548 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 550 */	NdrFcShort( 0x8 ),	/* 8 */
/* 552 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 554 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 556 */	NdrFcShort( 0x4 ),	/* 4 */
/* 558 */	NdrFcShort( 0x4 ),	/* 4 */
/* 560 */	0x11, 0x0,	/* FC_RP */
/* 562 */	NdrFcShort( 0xffd2 ),	/* Offset= -46 (516) */
/* 564 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 566 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 568 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 570 */	NdrFcShort( 0x0 ),	/* 0 */
/* 572 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 574 */	NdrFcShort( 0x0 ),	/* 0 */
/* 576 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 578 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 582 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 584 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 586 */	NdrFcShort( 0xfdde ),	/* Offset= -546 (40) */
/* 588 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 590 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 592 */	NdrFcShort( 0x8 ),	/* 8 */
/* 594 */	NdrFcShort( 0x0 ),	/* 0 */
/* 596 */	NdrFcShort( 0x6 ),	/* Offset= 6 (602) */
/* 598 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 600 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 602 */	
			0x11, 0x0,	/* FC_RP */
/* 604 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (568) */
/* 606 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 608 */	NdrFcShort( 0x0 ),	/* 0 */
/* 610 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 612 */	NdrFcShort( 0x0 ),	/* 0 */
/* 614 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 616 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 620 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 622 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 624 */	NdrFcShort( 0xff36 ),	/* Offset= -202 (422) */
/* 626 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 628 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 630 */	NdrFcShort( 0x8 ),	/* 8 */
/* 632 */	NdrFcShort( 0x0 ),	/* 0 */
/* 634 */	NdrFcShort( 0x6 ),	/* Offset= 6 (640) */
/* 636 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 638 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 640 */	
			0x11, 0x0,	/* FC_RP */
/* 642 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (606) */
/* 644 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 646 */	NdrFcShort( 0x4 ),	/* 4 */
/* 648 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 650 */	NdrFcShort( 0x0 ),	/* 0 */
/* 652 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 654 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 656 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 658 */	NdrFcShort( 0x4 ),	/* 4 */
/* 660 */	NdrFcShort( 0x0 ),	/* 0 */
/* 662 */	NdrFcShort( 0x1 ),	/* 1 */
/* 664 */	NdrFcShort( 0x0 ),	/* 0 */
/* 666 */	NdrFcShort( 0x0 ),	/* 0 */
/* 668 */	0x12, 0x0,	/* FC_UP */
/* 670 */	NdrFcShort( 0x180 ),	/* Offset= 384 (1054) */
/* 672 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 674 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 676 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 678 */	NdrFcShort( 0x8 ),	/* 8 */
/* 680 */	NdrFcShort( 0x0 ),	/* 0 */
/* 682 */	NdrFcShort( 0x6 ),	/* Offset= 6 (688) */
/* 684 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 686 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 688 */	
			0x11, 0x0,	/* FC_RP */
/* 690 */	NdrFcShort( 0xffd2 ),	/* Offset= -46 (644) */
/* 692 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 694 */	NdrFcLong( 0x2f ),	/* 47 */
/* 698 */	NdrFcShort( 0x0 ),	/* 0 */
/* 700 */	NdrFcShort( 0x0 ),	/* 0 */
/* 702 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 704 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 706 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 708 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 710 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 712 */	NdrFcShort( 0x1 ),	/* 1 */
/* 714 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 716 */	NdrFcShort( 0x4 ),	/* 4 */
/* 718 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 720 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 722 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 724 */	NdrFcShort( 0x10 ),	/* 16 */
/* 726 */	NdrFcShort( 0x0 ),	/* 0 */
/* 728 */	NdrFcShort( 0xa ),	/* Offset= 10 (738) */
/* 730 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 732 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 734 */	NdrFcShort( 0xffd6 ),	/* Offset= -42 (692) */
/* 736 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 738 */	
			0x12, 0x0,	/* FC_UP */
/* 740 */	NdrFcShort( 0xffe2 ),	/* Offset= -30 (710) */
/* 742 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 744 */	NdrFcShort( 0x4 ),	/* 4 */
/* 746 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 748 */	NdrFcShort( 0x0 ),	/* 0 */
/* 750 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 752 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 754 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 756 */	NdrFcShort( 0x4 ),	/* 4 */
/* 758 */	NdrFcShort( 0x0 ),	/* 0 */
/* 760 */	NdrFcShort( 0x1 ),	/* 1 */
/* 762 */	NdrFcShort( 0x0 ),	/* 0 */
/* 764 */	NdrFcShort( 0x0 ),	/* 0 */
/* 766 */	0x12, 0x0,	/* FC_UP */
/* 768 */	NdrFcShort( 0xffd2 ),	/* Offset= -46 (722) */
/* 770 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 772 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 774 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 776 */	NdrFcShort( 0x8 ),	/* 8 */
/* 778 */	NdrFcShort( 0x0 ),	/* 0 */
/* 780 */	NdrFcShort( 0x6 ),	/* Offset= 6 (786) */
/* 782 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 784 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 786 */	
			0x11, 0x0,	/* FC_RP */
/* 788 */	NdrFcShort( 0xffd2 ),	/* Offset= -46 (742) */
/* 790 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 792 */	NdrFcShort( 0x18 ),	/* 24 */
/* 794 */	NdrFcShort( 0x0 ),	/* 0 */
/* 796 */	NdrFcShort( 0xa ),	/* Offset= 10 (806) */
/* 798 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 800 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 802 */	NdrFcShort( 0xfd26 ),	/* Offset= -730 (72) */
/* 804 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 806 */	
			0x11, 0x0,	/* FC_RP */
/* 808 */	NdrFcShort( 0xff10 ),	/* Offset= -240 (568) */
/* 810 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 812 */	NdrFcShort( 0x1 ),	/* 1 */
/* 814 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 816 */	NdrFcShort( 0x0 ),	/* 0 */
/* 818 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 820 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 822 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 824 */	NdrFcShort( 0x8 ),	/* 8 */
/* 826 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 828 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 830 */	NdrFcShort( 0x4 ),	/* 4 */
/* 832 */	NdrFcShort( 0x4 ),	/* 4 */
/* 834 */	0x12, 0x0,	/* FC_UP */
/* 836 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (810) */
/* 838 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 840 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 842 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 844 */	NdrFcShort( 0x2 ),	/* 2 */
/* 846 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 848 */	NdrFcShort( 0x0 ),	/* 0 */
/* 850 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 852 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 854 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 856 */	NdrFcShort( 0x8 ),	/* 8 */
/* 858 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 860 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 862 */	NdrFcShort( 0x4 ),	/* 4 */
/* 864 */	NdrFcShort( 0x4 ),	/* 4 */
/* 866 */	0x12, 0x0,	/* FC_UP */
/* 868 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (842) */
/* 870 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 872 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 874 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 876 */	NdrFcShort( 0x4 ),	/* 4 */
/* 878 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 880 */	NdrFcShort( 0x0 ),	/* 0 */
/* 882 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 884 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 886 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 888 */	NdrFcShort( 0x8 ),	/* 8 */
/* 890 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 892 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 894 */	NdrFcShort( 0x4 ),	/* 4 */
/* 896 */	NdrFcShort( 0x4 ),	/* 4 */
/* 898 */	0x12, 0x0,	/* FC_UP */
/* 900 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (874) */
/* 902 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 904 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 906 */	
			0x1b,		/* FC_CARRAY */
			0x7,		/* 7 */
/* 908 */	NdrFcShort( 0x8 ),	/* 8 */
/* 910 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 912 */	NdrFcShort( 0x0 ),	/* 0 */
/* 914 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 916 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 918 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 920 */	NdrFcShort( 0x8 ),	/* 8 */
/* 922 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 924 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 926 */	NdrFcShort( 0x4 ),	/* 4 */
/* 928 */	NdrFcShort( 0x4 ),	/* 4 */
/* 930 */	0x12, 0x0,	/* FC_UP */
/* 932 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (906) */
/* 934 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 936 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 938 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 940 */	NdrFcShort( 0x8 ),	/* 8 */
/* 942 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 944 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 946 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 948 */	NdrFcShort( 0x8 ),	/* 8 */
/* 950 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 952 */	NdrFcShort( 0xffd8 ),	/* -40 */
/* 954 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 956 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 958 */	NdrFcShort( 0xffec ),	/* Offset= -20 (938) */
/* 960 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 962 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 964 */	NdrFcShort( 0x28 ),	/* 40 */
/* 966 */	NdrFcShort( 0xffec ),	/* Offset= -20 (946) */
/* 968 */	NdrFcShort( 0x0 ),	/* Offset= 0 (968) */
/* 970 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 972 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 974 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 976 */	NdrFcShort( 0xfdf0 ),	/* Offset= -528 (448) */
/* 978 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 980 */	
			0x12, 0x0,	/* FC_UP */
/* 982 */	NdrFcShort( 0xfefc ),	/* Offset= -260 (722) */
/* 984 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 986 */	0x1,		/* FC_BYTE */
			0x5c,		/* FC_PAD */
/* 988 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 990 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 992 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 994 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 996 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 998 */	0xb,		/* FC_HYPER */
			0x5c,		/* FC_PAD */
/* 1000 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 1002 */	0xa,		/* FC_FLOAT */
			0x5c,		/* FC_PAD */
/* 1004 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 1006 */	0xc,		/* FC_DOUBLE */
			0x5c,		/* FC_PAD */
/* 1008 */	
			0x12, 0x0,	/* FC_UP */
/* 1010 */	NdrFcShort( 0xfd94 ),	/* Offset= -620 (390) */
/* 1012 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 1014 */	NdrFcShort( 0xfd96 ),	/* Offset= -618 (396) */
/* 1016 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 1018 */	NdrFcShort( 0xfc2e ),	/* Offset= -978 (40) */
/* 1020 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 1022 */	NdrFcShort( 0xfda8 ),	/* Offset= -600 (422) */
/* 1024 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 1026 */	NdrFcShort( 0xfdb6 ),	/* Offset= -586 (440) */
/* 1028 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 1030 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1032) */
/* 1032 */	
			0x12, 0x0,	/* FC_UP */
/* 1034 */	NdrFcShort( 0x14 ),	/* Offset= 20 (1054) */
/* 1036 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 1038 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1040 */	0x6,		/* FC_SHORT */
			0x1,		/* FC_BYTE */
/* 1042 */	0x1,		/* FC_BYTE */
			0x8,		/* FC_LONG */
/* 1044 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 1046 */	
			0x12, 0x0,	/* FC_UP */
/* 1048 */	NdrFcShort( 0xfff4 ),	/* Offset= -12 (1036) */
/* 1050 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 1052 */	0x2,		/* FC_CHAR */
			0x5c,		/* FC_PAD */
/* 1054 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 1056 */	NdrFcShort( 0x20 ),	/* 32 */
/* 1058 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1060 */	NdrFcShort( 0x0 ),	/* Offset= 0 (1060) */
/* 1062 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1064 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 1066 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 1068 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1070 */	NdrFcShort( 0xfc2e ),	/* Offset= -978 (92) */
/* 1072 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1074 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1076 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1078 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1080 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1082 */	NdrFcShort( 0xfc1e ),	/* Offset= -994 (88) */
/* 1084 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1086 */	NdrFcShort( 0x2 ),	/* 2 */
/* 1088 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1090 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1092 */	NdrFcShort( 0xfd48 ),	/* Offset= -696 (396) */
/* 1094 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 1096 */	NdrFcShort( 0x1c ),	/* 28 */
/* 1098 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1100 */	NdrFcShort( 0xa ),	/* Offset= 10 (1110) */
/* 1102 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 1104 */	0x36,		/* FC_POINTER */
			0x36,		/* FC_POINTER */
/* 1106 */	0x36,		/* FC_POINTER */
			0x36,		/* FC_POINTER */
/* 1108 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 1110 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 1112 */	NdrFcShort( 0xfbe6 ),	/* Offset= -1050 (62) */
/* 1114 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 1116 */	NdrFcShort( 0xfbcc ),	/* Offset= -1076 (40) */
/* 1118 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 1120 */	NdrFcShort( 0xfbf4 ),	/* Offset= -1036 (84) */
/* 1122 */	
			0x12, 0x0,	/* FC_UP */
/* 1124 */	NdrFcShort( 0xffd8 ),	/* Offset= -40 (1084) */
/* 1126 */	
			0x12, 0x0,	/* FC_UP */
/* 1128 */	NdrFcShort( 0xffd4 ),	/* Offset= -44 (1084) */
/* 1130 */	
			0x12, 0x0,	/* FC_UP */
/* 1132 */	NdrFcShort( 0xffd0 ),	/* Offset= -48 (1084) */
/* 1134 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1136 */	NdrFcLong( 0x10e ),	/* 270 */
/* 1140 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1142 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1144 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 1146 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 1148 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 1150 */	0x0,		/* 0 */
			0x46,		/* 70 */

			0x0
        }
    };

static const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ] = 
        {
            
            {
            HWND_UserSize
            ,HWND_UserMarshal
            ,HWND_UserUnmarshal
            ,HWND_UserFree
            },
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



/* Standard interface: __MIDL_itf_ConfigObjectProperty_0000, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}} */


/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IConfigObjectProperty, ver. 0.0,
   GUID={0x101228D6,0xD0B0,0x41D3,{0x8F,0x95,0x37,0x0E,0x88,0x8F,0x04,0x46}} */

#pragma code_seg(".orpc")
static const unsigned short IConfigObjectProperty_FormatStringOffsetTable[] =
    {
    0,
    36
    };

static const MIDL_STUBLESS_PROXY_INFO IConfigObjectProperty_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IConfigObjectProperty_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IConfigObjectProperty_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IConfigObjectProperty_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(5) _IConfigObjectPropertyProxyVtbl = 
{
    &IConfigObjectProperty_ProxyInfo,
    &IID_IConfigObjectProperty,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IConfigObjectProperty::ConfigObjectProperty */ ,
    (void *) (INT_PTR) -1 /* IConfigObjectProperty::get_IsConfigured */
};

const CInterfaceStubVtbl _IConfigObjectPropertyStubVtbl =
{
    &IID_IConfigObjectProperty,
    &IConfigObjectProperty_ServerInfo,
    5,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IConfigSequenceForObjectProperty, ver. 0.0,
   GUID={0xF7D428CF,0x8D5A,0x4B93,{0xA1,0x29,0xF1,0xD7,0xC1,0xED,0xE5,0x97}} */

#pragma code_seg(".orpc")
static const unsigned short IConfigSequenceForObjectProperty_FormatStringOffsetTable[] =
    {
    72,
    108,
    144
    };

static const MIDL_STUBLESS_PROXY_INFO IConfigSequenceForObjectProperty_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IConfigSequenceForObjectProperty_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IConfigSequenceForObjectProperty_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IConfigSequenceForObjectProperty_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(6) _IConfigSequenceForObjectPropertyProxyVtbl = 
{
    &IConfigSequenceForObjectProperty_ProxyInfo,
    &IID_IConfigSequenceForObjectProperty,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IConfigSequenceForObjectProperty::AddAction */ ,
    (void *) (INT_PTR) -1 /* IConfigSequenceForObjectProperty::AddActionsByCLSID */ ,
    (void *) (INT_PTR) -1 /* IConfigSequenceForObjectProperty::PrepareActions */
};

const CInterfaceStubVtbl _IConfigSequenceForObjectPropertyStubVtbl =
{
    &IID_IConfigSequenceForObjectProperty,
    &IConfigSequenceForObjectProperty_ServerInfo,
    6,
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
    0x6000169, /* MIDL Version 6.0.361 */
    0,
    UserMarshalRoutines,
    0,  /* notify & notify_flag routine table */
    0x1, /* MIDL flag */
    0, /* cs routines */
    0,   /* proxy/server info */
    0   /* Reserved5 */
    };

const CInterfaceProxyVtbl * _ConfigObjectProperty_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_IConfigSequenceForObjectPropertyProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IConfigObjectPropertyProxyVtbl,
    0
};

const CInterfaceStubVtbl * _ConfigObjectProperty_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_IConfigSequenceForObjectPropertyStubVtbl,
    ( CInterfaceStubVtbl *) &_IConfigObjectPropertyStubVtbl,
    0
};

PCInterfaceName const _ConfigObjectProperty_InterfaceNamesList[] = 
{
    "IConfigSequenceForObjectProperty",
    "IConfigObjectProperty",
    0
};


#define _ConfigObjectProperty_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _ConfigObjectProperty, pIID, n)

int __stdcall _ConfigObjectProperty_IID_Lookup( const IID * pIID, int * pIndex )
{
    IID_BS_LOOKUP_SETUP

    IID_BS_LOOKUP_INITIAL_TEST( _ConfigObjectProperty, 2, 1 )
    IID_BS_LOOKUP_RETURN_RESULT( _ConfigObjectProperty, 2, *pIndex )
    
}

const ExtendedProxyFileInfo ConfigObjectProperty_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _ConfigObjectProperty_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _ConfigObjectProperty_StubVtblList,
    (const PCInterfaceName * ) & _ConfigObjectProperty_InterfaceNamesList,
    0, // no delegation
    & _ConfigObjectProperty_IID_Lookup, 
    2,
    2,
    0, /* table of [async_uuid] interfaces */
    0, /* Filler1 */
    0, /* Filler2 */
    0  /* Filler3 */
};
#if _MSC_VER >= 1200
#pragma warning(pop)
#endif


#endif /* !defined(_M_IA64) && !defined(_M_AMD64)*/



/* this ALWAYS GENERATED file contains the proxy stub code */


 /* File created by MIDL compiler version 6.00.0361 */
/* at Thu Jan 16 12:35:34 2003
 */
/* Compiler settings for ConfigObjectProperty.Idl:
    Oicf, W1, Zp8, env=Win64 (32b run,appending)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#if defined(_M_IA64) || defined(_M_AMD64)


#pragma warning( disable: 4049 )  /* more than 64k source lines */
#if _MSC_VER >= 1200
#pragma warning(push)
#endif

#pragma warning( disable: 4211 )  /* redefine extent to static */
#pragma warning( disable: 4232 )  /* dllimport identity*/
#define USE_STUBLESS_PROXY


/* verify that the <rpcproxy.h> version is high enough to compile this file*/
#ifndef __REDQ_RPCPROXY_H_VERSION__
#define __REQUIRED_RPCPROXY_H_VERSION__ 475
#endif


#include "rpcproxy.h"
#ifndef __RPCPROXY_H_VERSION__
#error this stub requires an updated version of <rpcproxy.h>
#endif // __RPCPROXY_H_VERSION__


#include "ConfigObjectProperty.h"

#define TYPE_FORMAT_STRING_SIZE   1105                              
#define PROC_FORMAT_STRING_SIZE   197                               
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   3            

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


extern const MIDL_SERVER_INFO IConfigObjectProperty_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IConfigObjectProperty_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IConfigSequenceForObjectProperty_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IConfigSequenceForObjectProperty_ProxyInfo;


extern const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ];

#if !defined(__RPC_WIN64__)
#error  Invalid build platform for this stub.
#endif

static const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure ConfigObjectProperty */

			0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/*  2 */	NdrFcLong( 0x0 ),	/* 0 */
/*  6 */	NdrFcShort( 0x3 ),	/* 3 */
/*  8 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 10 */	NdrFcShort( 0x0 ),	/* 0 */
/* 12 */	NdrFcShort( 0x8 ),	/* 8 */
/* 14 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 16 */	0xa,		/* 10 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 18 */	NdrFcShort( 0x0 ),	/* 0 */
/* 20 */	NdrFcShort( 0x1 ),	/* 1 */
/* 22 */	NdrFcShort( 0x0 ),	/* 0 */
/* 24 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter hWnd */

/* 26 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 28 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 30 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */

	/* Return value */

/* 32 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 34 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 36 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_IsConfigured */

/* 38 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 40 */	NdrFcLong( 0x0 ),	/* 0 */
/* 44 */	NdrFcShort( 0x4 ),	/* 4 */
/* 46 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 48 */	NdrFcShort( 0x0 ),	/* 0 */
/* 50 */	NdrFcShort( 0x22 ),	/* 34 */
/* 52 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 54 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 56 */	NdrFcShort( 0x0 ),	/* 0 */
/* 58 */	NdrFcShort( 0x0 ),	/* 0 */
/* 60 */	NdrFcShort( 0x0 ),	/* 0 */
/* 62 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ConfigState */

/* 64 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 66 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 68 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 70 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 72 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 74 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure AddAction */

/* 76 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 78 */	NdrFcLong( 0x0 ),	/* 0 */
/* 82 */	NdrFcShort( 0x3 ),	/* 3 */
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

	/* Parameter pIAct */

/* 102 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 104 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 106 */	NdrFcShort( 0x28 ),	/* Type Offset=40 */

	/* Return value */

/* 108 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 110 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 112 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure AddActionsByCLSID */

/* 114 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 116 */	NdrFcLong( 0x0 ),	/* 0 */
/* 120 */	NdrFcShort( 0x4 ),	/* 4 */
/* 122 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 124 */	NdrFcShort( 0x0 ),	/* 0 */
/* 126 */	NdrFcShort( 0x8 ),	/* 8 */
/* 128 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 130 */	0xa,		/* 10 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 132 */	NdrFcShort( 0x0 ),	/* 0 */
/* 134 */	NdrFcShort( 0x23 ),	/* 35 */
/* 136 */	NdrFcShort( 0x0 ),	/* 0 */
/* 138 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pcsClsId */

/* 140 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 142 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 144 */	NdrFcShort( 0x414 ),	/* Type Offset=1044 */

	/* Return value */

/* 146 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 148 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 150 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure PrepareActions */

/* 152 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 154 */	NdrFcLong( 0x0 ),	/* 0 */
/* 158 */	NdrFcShort( 0x5 ),	/* 5 */
/* 160 */	NdrFcShort( 0x20 ),	/* ia64 Stack size/offset = 32 */
/* 162 */	NdrFcShort( 0x0 ),	/* 0 */
/* 164 */	NdrFcShort( 0x8 ),	/* 8 */
/* 166 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 168 */	0xa,		/* 10 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 170 */	NdrFcShort( 0x0 ),	/* 0 */
/* 172 */	NdrFcShort( 0x1 ),	/* 1 */
/* 174 */	NdrFcShort( 0x0 ),	/* 0 */
/* 176 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter hParent */

/* 178 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 180 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 182 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */

	/* Parameter pIData */

/* 184 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 186 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 188 */	NdrFcShort( 0x43e ),	/* Type Offset=1086 */

	/* Return value */

/* 190 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 192 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 194 */	0x8,		/* FC_LONG */
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
/*  4 */	NdrFcShort( 0x2 ),	/* Offset= 2 (6) */
/*  6 */	
			0x2a,		/* FC_ENCAPSULATED_UNION */
			0x48,		/* 72 */
/*  8 */	NdrFcShort( 0x4 ),	/* 4 */
/* 10 */	NdrFcShort( 0x2 ),	/* 2 */
/* 12 */	NdrFcLong( 0x48746457 ),	/* 1215587415 */
/* 16 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 18 */	NdrFcLong( 0x52746457 ),	/* 1383359575 */
/* 22 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 24 */	NdrFcShort( 0xffff ),	/* Offset= -1 (23) */
/* 26 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 28 */	NdrFcShort( 0x0 ),	/* 0 */
/* 30 */	NdrFcShort( 0x8 ),	/* 8 */
/* 32 */	NdrFcShort( 0x0 ),	/* 0 */
/* 34 */	NdrFcShort( 0xffe0 ),	/* Offset= -32 (2) */
/* 36 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 38 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 40 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 42 */	NdrFcLong( 0x0 ),	/* 0 */
/* 46 */	NdrFcShort( 0x0 ),	/* 0 */
/* 48 */	NdrFcShort( 0x0 ),	/* 0 */
/* 50 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 52 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 54 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 56 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 58 */	
			0x11, 0x0,	/* FC_RP */
/* 60 */	NdrFcShort( 0x3d8 ),	/* Offset= 984 (1044) */
/* 62 */	
			0x12, 0x0,	/* FC_UP */
/* 64 */	NdrFcShort( 0x8 ),	/* Offset= 8 (72) */
/* 66 */	
			0x1d,		/* FC_SMFARRAY */
			0x0,		/* 0 */
/* 68 */	NdrFcShort( 0x8 ),	/* 8 */
/* 70 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 72 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 74 */	NdrFcShort( 0x10 ),	/* 16 */
/* 76 */	0x8,		/* FC_LONG */
			0x6,		/* FC_SHORT */
/* 78 */	0x6,		/* FC_SHORT */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 80 */	0x0,		/* 0 */
			NdrFcShort( 0xfff1 ),	/* Offset= -15 (66) */
			0x5b,		/* FC_END */
/* 84 */	
			0x12, 0x0,	/* FC_UP */
/* 86 */	NdrFcShort( 0x3aa ),	/* Offset= 938 (1024) */
/* 88 */	
			0x12, 0x0,	/* FC_UP */
/* 90 */	NdrFcShort( 0x392 ),	/* Offset= 914 (1004) */
/* 92 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 94 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 96 */	NdrFcShort( 0xfff8 ),	/* -8 */
/* 98 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 100 */	NdrFcShort( 0x2 ),	/* Offset= 2 (102) */
/* 102 */	NdrFcShort( 0x10 ),	/* 16 */
/* 104 */	NdrFcShort( 0x2f ),	/* 47 */
/* 106 */	NdrFcLong( 0x14 ),	/* 20 */
/* 110 */	NdrFcShort( 0x800b ),	/* Simple arm type: FC_HYPER */
/* 112 */	NdrFcLong( 0x3 ),	/* 3 */
/* 116 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 118 */	NdrFcLong( 0x11 ),	/* 17 */
/* 122 */	NdrFcShort( 0x8001 ),	/* Simple arm type: FC_BYTE */
/* 124 */	NdrFcLong( 0x2 ),	/* 2 */
/* 128 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 130 */	NdrFcLong( 0x4 ),	/* 4 */
/* 134 */	NdrFcShort( 0x800a ),	/* Simple arm type: FC_FLOAT */
/* 136 */	NdrFcLong( 0x5 ),	/* 5 */
/* 140 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 142 */	NdrFcLong( 0xb ),	/* 11 */
/* 146 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 148 */	NdrFcLong( 0xa ),	/* 10 */
/* 152 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 154 */	NdrFcLong( 0x6 ),	/* 6 */
/* 158 */	NdrFcShort( 0xe8 ),	/* Offset= 232 (390) */
/* 160 */	NdrFcLong( 0x7 ),	/* 7 */
/* 164 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 166 */	NdrFcLong( 0x8 ),	/* 8 */
/* 170 */	NdrFcShort( 0xe2 ),	/* Offset= 226 (396) */
/* 172 */	NdrFcLong( 0xd ),	/* 13 */
/* 176 */	NdrFcShort( 0xff78 ),	/* Offset= -136 (40) */
/* 178 */	NdrFcLong( 0x9 ),	/* 9 */
/* 182 */	NdrFcShort( 0xf0 ),	/* Offset= 240 (422) */
/* 184 */	NdrFcLong( 0x2000 ),	/* 8192 */
/* 188 */	NdrFcShort( 0xfc ),	/* Offset= 252 (440) */
/* 190 */	NdrFcLong( 0x24 ),	/* 36 */
/* 194 */	NdrFcShort( 0x2e0 ),	/* Offset= 736 (930) */
/* 196 */	NdrFcLong( 0x4024 ),	/* 16420 */
/* 200 */	NdrFcShort( 0x2da ),	/* Offset= 730 (930) */
/* 202 */	NdrFcLong( 0x4011 ),	/* 16401 */
/* 206 */	NdrFcShort( 0x2d8 ),	/* Offset= 728 (934) */
/* 208 */	NdrFcLong( 0x4002 ),	/* 16386 */
/* 212 */	NdrFcShort( 0x2d6 ),	/* Offset= 726 (938) */
/* 214 */	NdrFcLong( 0x4003 ),	/* 16387 */
/* 218 */	NdrFcShort( 0x2d4 ),	/* Offset= 724 (942) */
/* 220 */	NdrFcLong( 0x4014 ),	/* 16404 */
/* 224 */	NdrFcShort( 0x2d2 ),	/* Offset= 722 (946) */
/* 226 */	NdrFcLong( 0x4004 ),	/* 16388 */
/* 230 */	NdrFcShort( 0x2d0 ),	/* Offset= 720 (950) */
/* 232 */	NdrFcLong( 0x4005 ),	/* 16389 */
/* 236 */	NdrFcShort( 0x2ce ),	/* Offset= 718 (954) */
/* 238 */	NdrFcLong( 0x400b ),	/* 16395 */
/* 242 */	NdrFcShort( 0x2b8 ),	/* Offset= 696 (938) */
/* 244 */	NdrFcLong( 0x400a ),	/* 16394 */
/* 248 */	NdrFcShort( 0x2b6 ),	/* Offset= 694 (942) */
/* 250 */	NdrFcLong( 0x4006 ),	/* 16390 */
/* 254 */	NdrFcShort( 0x2c0 ),	/* Offset= 704 (958) */
/* 256 */	NdrFcLong( 0x4007 ),	/* 16391 */
/* 260 */	NdrFcShort( 0x2b6 ),	/* Offset= 694 (954) */
/* 262 */	NdrFcLong( 0x4008 ),	/* 16392 */
/* 266 */	NdrFcShort( 0x2b8 ),	/* Offset= 696 (962) */
/* 268 */	NdrFcLong( 0x400d ),	/* 16397 */
/* 272 */	NdrFcShort( 0x2b6 ),	/* Offset= 694 (966) */
/* 274 */	NdrFcLong( 0x4009 ),	/* 16393 */
/* 278 */	NdrFcShort( 0x2b4 ),	/* Offset= 692 (970) */
/* 280 */	NdrFcLong( 0x6000 ),	/* 24576 */
/* 284 */	NdrFcShort( 0x2b2 ),	/* Offset= 690 (974) */
/* 286 */	NdrFcLong( 0x400c ),	/* 16396 */
/* 290 */	NdrFcShort( 0x2b0 ),	/* Offset= 688 (978) */
/* 292 */	NdrFcLong( 0x10 ),	/* 16 */
/* 296 */	NdrFcShort( 0x8002 ),	/* Simple arm type: FC_CHAR */
/* 298 */	NdrFcLong( 0x12 ),	/* 18 */
/* 302 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 304 */	NdrFcLong( 0x13 ),	/* 19 */
/* 308 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 310 */	NdrFcLong( 0x15 ),	/* 21 */
/* 314 */	NdrFcShort( 0x800b ),	/* Simple arm type: FC_HYPER */
/* 316 */	NdrFcLong( 0x16 ),	/* 22 */
/* 320 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 322 */	NdrFcLong( 0x17 ),	/* 23 */
/* 326 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 328 */	NdrFcLong( 0xe ),	/* 14 */
/* 332 */	NdrFcShort( 0x28e ),	/* Offset= 654 (986) */
/* 334 */	NdrFcLong( 0x400e ),	/* 16398 */
/* 338 */	NdrFcShort( 0x292 ),	/* Offset= 658 (996) */
/* 340 */	NdrFcLong( 0x4010 ),	/* 16400 */
/* 344 */	NdrFcShort( 0x290 ),	/* Offset= 656 (1000) */
/* 346 */	NdrFcLong( 0x4012 ),	/* 16402 */
/* 350 */	NdrFcShort( 0x24c ),	/* Offset= 588 (938) */
/* 352 */	NdrFcLong( 0x4013 ),	/* 16403 */
/* 356 */	NdrFcShort( 0x24a ),	/* Offset= 586 (942) */
/* 358 */	NdrFcLong( 0x4015 ),	/* 16405 */
/* 362 */	NdrFcShort( 0x248 ),	/* Offset= 584 (946) */
/* 364 */	NdrFcLong( 0x4016 ),	/* 16406 */
/* 368 */	NdrFcShort( 0x23e ),	/* Offset= 574 (942) */
/* 370 */	NdrFcLong( 0x4017 ),	/* 16407 */
/* 374 */	NdrFcShort( 0x238 ),	/* Offset= 568 (942) */
/* 376 */	NdrFcLong( 0x0 ),	/* 0 */
/* 380 */	NdrFcShort( 0x0 ),	/* Offset= 0 (380) */
/* 382 */	NdrFcLong( 0x1 ),	/* 1 */
/* 386 */	NdrFcShort( 0x0 ),	/* Offset= 0 (386) */
/* 388 */	NdrFcShort( 0xffff ),	/* Offset= -1 (387) */
/* 390 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 392 */	NdrFcShort( 0x8 ),	/* 8 */
/* 394 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 396 */	
			0x12, 0x0,	/* FC_UP */
/* 398 */	NdrFcShort( 0xe ),	/* Offset= 14 (412) */
/* 400 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 402 */	NdrFcShort( 0x2 ),	/* 2 */
/* 404 */	0x9,		/* Corr desc: FC_ULONG */
			0x0,		/*  */
/* 406 */	NdrFcShort( 0xfffc ),	/* -4 */
/* 408 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 410 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 412 */	
			0x17,		/* FC_CSTRUCT */
			0x3,		/* 3 */
/* 414 */	NdrFcShort( 0x8 ),	/* 8 */
/* 416 */	NdrFcShort( 0xfff0 ),	/* Offset= -16 (400) */
/* 418 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 420 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 422 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 424 */	NdrFcLong( 0x20400 ),	/* 132096 */
/* 428 */	NdrFcShort( 0x0 ),	/* 0 */
/* 430 */	NdrFcShort( 0x0 ),	/* 0 */
/* 432 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 434 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 436 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 438 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 440 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 442 */	NdrFcShort( 0x2 ),	/* Offset= 2 (444) */
/* 444 */	
			0x12, 0x0,	/* FC_UP */
/* 446 */	NdrFcShort( 0x1d2 ),	/* Offset= 466 (912) */
/* 448 */	
			0x2a,		/* FC_ENCAPSULATED_UNION */
			0x89,		/* 137 */
/* 450 */	NdrFcShort( 0x20 ),	/* 32 */
/* 452 */	NdrFcShort( 0xa ),	/* 10 */
/* 454 */	NdrFcLong( 0x8 ),	/* 8 */
/* 458 */	NdrFcShort( 0x50 ),	/* Offset= 80 (538) */
/* 460 */	NdrFcLong( 0xd ),	/* 13 */
/* 464 */	NdrFcShort( 0x70 ),	/* Offset= 112 (576) */
/* 466 */	NdrFcLong( 0x9 ),	/* 9 */
/* 470 */	NdrFcShort( 0x90 ),	/* Offset= 144 (614) */
/* 472 */	NdrFcLong( 0xc ),	/* 12 */
/* 476 */	NdrFcShort( 0xb0 ),	/* Offset= 176 (652) */
/* 478 */	NdrFcLong( 0x24 ),	/* 36 */
/* 482 */	NdrFcShort( 0x102 ),	/* Offset= 258 (740) */
/* 484 */	NdrFcLong( 0x800d ),	/* 32781 */
/* 488 */	NdrFcShort( 0x10c ),	/* Offset= 268 (756) */
/* 490 */	NdrFcLong( 0x10 ),	/* 16 */
/* 494 */	NdrFcShort( 0x126 ),	/* Offset= 294 (788) */
/* 496 */	NdrFcLong( 0x2 ),	/* 2 */
/* 500 */	NdrFcShort( 0x13c ),	/* Offset= 316 (816) */
/* 502 */	NdrFcLong( 0x3 ),	/* 3 */
/* 506 */	NdrFcShort( 0x152 ),	/* Offset= 338 (844) */
/* 508 */	NdrFcLong( 0x14 ),	/* 20 */
/* 512 */	NdrFcShort( 0x168 ),	/* Offset= 360 (872) */
/* 514 */	NdrFcShort( 0xffff ),	/* Offset= -1 (513) */
/* 516 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 518 */	NdrFcShort( 0x0 ),	/* 0 */
/* 520 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 522 */	NdrFcShort( 0x0 ),	/* 0 */
/* 524 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 526 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 530 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 532 */	
			0x12, 0x0,	/* FC_UP */
/* 534 */	NdrFcShort( 0xff86 ),	/* Offset= -122 (412) */
/* 536 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 538 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 540 */	NdrFcShort( 0x10 ),	/* 16 */
/* 542 */	NdrFcShort( 0x0 ),	/* 0 */
/* 544 */	NdrFcShort( 0x6 ),	/* Offset= 6 (550) */
/* 546 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 548 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 550 */	
			0x11, 0x0,	/* FC_RP */
/* 552 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (516) */
/* 554 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 556 */	NdrFcShort( 0x0 ),	/* 0 */
/* 558 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 560 */	NdrFcShort( 0x0 ),	/* 0 */
/* 562 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 564 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 568 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 570 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 572 */	NdrFcShort( 0xfdec ),	/* Offset= -532 (40) */
/* 574 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 576 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 578 */	NdrFcShort( 0x10 ),	/* 16 */
/* 580 */	NdrFcShort( 0x0 ),	/* 0 */
/* 582 */	NdrFcShort( 0x6 ),	/* Offset= 6 (588) */
/* 584 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 586 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 588 */	
			0x11, 0x0,	/* FC_RP */
/* 590 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (554) */
/* 592 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 594 */	NdrFcShort( 0x0 ),	/* 0 */
/* 596 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 598 */	NdrFcShort( 0x0 ),	/* 0 */
/* 600 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 602 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 606 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 608 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 610 */	NdrFcShort( 0xff44 ),	/* Offset= -188 (422) */
/* 612 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 614 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 616 */	NdrFcShort( 0x10 ),	/* 16 */
/* 618 */	NdrFcShort( 0x0 ),	/* 0 */
/* 620 */	NdrFcShort( 0x6 ),	/* Offset= 6 (626) */
/* 622 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 624 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 626 */	
			0x11, 0x0,	/* FC_RP */
/* 628 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (592) */
/* 630 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 632 */	NdrFcShort( 0x0 ),	/* 0 */
/* 634 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 636 */	NdrFcShort( 0x0 ),	/* 0 */
/* 638 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 640 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 644 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 646 */	
			0x12, 0x0,	/* FC_UP */
/* 648 */	NdrFcShort( 0x164 ),	/* Offset= 356 (1004) */
/* 650 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 652 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 654 */	NdrFcShort( 0x10 ),	/* 16 */
/* 656 */	NdrFcShort( 0x0 ),	/* 0 */
/* 658 */	NdrFcShort( 0x6 ),	/* Offset= 6 (664) */
/* 660 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 662 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 664 */	
			0x11, 0x0,	/* FC_RP */
/* 666 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (630) */
/* 668 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 670 */	NdrFcLong( 0x2f ),	/* 47 */
/* 674 */	NdrFcShort( 0x0 ),	/* 0 */
/* 676 */	NdrFcShort( 0x0 ),	/* 0 */
/* 678 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 680 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 682 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 684 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 686 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 688 */	NdrFcShort( 0x1 ),	/* 1 */
/* 690 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 692 */	NdrFcShort( 0x4 ),	/* 4 */
/* 694 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 696 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 698 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 700 */	NdrFcShort( 0x18 ),	/* 24 */
/* 702 */	NdrFcShort( 0x0 ),	/* 0 */
/* 704 */	NdrFcShort( 0xa ),	/* Offset= 10 (714) */
/* 706 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 708 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 710 */	NdrFcShort( 0xffd6 ),	/* Offset= -42 (668) */
/* 712 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 714 */	
			0x12, 0x0,	/* FC_UP */
/* 716 */	NdrFcShort( 0xffe2 ),	/* Offset= -30 (686) */
/* 718 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 720 */	NdrFcShort( 0x0 ),	/* 0 */
/* 722 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 724 */	NdrFcShort( 0x0 ),	/* 0 */
/* 726 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 728 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 732 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 734 */	
			0x12, 0x0,	/* FC_UP */
/* 736 */	NdrFcShort( 0xffda ),	/* Offset= -38 (698) */
/* 738 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 740 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 742 */	NdrFcShort( 0x10 ),	/* 16 */
/* 744 */	NdrFcShort( 0x0 ),	/* 0 */
/* 746 */	NdrFcShort( 0x6 ),	/* Offset= 6 (752) */
/* 748 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 750 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 752 */	
			0x11, 0x0,	/* FC_RP */
/* 754 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (718) */
/* 756 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 758 */	NdrFcShort( 0x20 ),	/* 32 */
/* 760 */	NdrFcShort( 0x0 ),	/* 0 */
/* 762 */	NdrFcShort( 0xa ),	/* Offset= 10 (772) */
/* 764 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 766 */	0x36,		/* FC_POINTER */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 768 */	0x0,		/* 0 */
			NdrFcShort( 0xfd47 ),	/* Offset= -697 (72) */
			0x5b,		/* FC_END */
/* 772 */	
			0x11, 0x0,	/* FC_RP */
/* 774 */	NdrFcShort( 0xff24 ),	/* Offset= -220 (554) */
/* 776 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 778 */	NdrFcShort( 0x1 ),	/* 1 */
/* 780 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 782 */	NdrFcShort( 0x0 ),	/* 0 */
/* 784 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 786 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 788 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 790 */	NdrFcShort( 0x10 ),	/* 16 */
/* 792 */	NdrFcShort( 0x0 ),	/* 0 */
/* 794 */	NdrFcShort( 0x6 ),	/* Offset= 6 (800) */
/* 796 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 798 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 800 */	
			0x12, 0x0,	/* FC_UP */
/* 802 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (776) */
/* 804 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 806 */	NdrFcShort( 0x2 ),	/* 2 */
/* 808 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 810 */	NdrFcShort( 0x0 ),	/* 0 */
/* 812 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 814 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 816 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 818 */	NdrFcShort( 0x10 ),	/* 16 */
/* 820 */	NdrFcShort( 0x0 ),	/* 0 */
/* 822 */	NdrFcShort( 0x6 ),	/* Offset= 6 (828) */
/* 824 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 826 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 828 */	
			0x12, 0x0,	/* FC_UP */
/* 830 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (804) */
/* 832 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 834 */	NdrFcShort( 0x4 ),	/* 4 */
/* 836 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 838 */	NdrFcShort( 0x0 ),	/* 0 */
/* 840 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 842 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 844 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 846 */	NdrFcShort( 0x10 ),	/* 16 */
/* 848 */	NdrFcShort( 0x0 ),	/* 0 */
/* 850 */	NdrFcShort( 0x6 ),	/* Offset= 6 (856) */
/* 852 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 854 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 856 */	
			0x12, 0x0,	/* FC_UP */
/* 858 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (832) */
/* 860 */	
			0x1b,		/* FC_CARRAY */
			0x7,		/* 7 */
/* 862 */	NdrFcShort( 0x8 ),	/* 8 */
/* 864 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 866 */	NdrFcShort( 0x0 ),	/* 0 */
/* 868 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 870 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 872 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 874 */	NdrFcShort( 0x10 ),	/* 16 */
/* 876 */	NdrFcShort( 0x0 ),	/* 0 */
/* 878 */	NdrFcShort( 0x6 ),	/* Offset= 6 (884) */
/* 880 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 882 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 884 */	
			0x12, 0x0,	/* FC_UP */
/* 886 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (860) */
/* 888 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 890 */	NdrFcShort( 0x8 ),	/* 8 */
/* 892 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 894 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 896 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 898 */	NdrFcShort( 0x8 ),	/* 8 */
/* 900 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 902 */	NdrFcShort( 0xffc8 ),	/* -56 */
/* 904 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 906 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 908 */	NdrFcShort( 0xffec ),	/* Offset= -20 (888) */
/* 910 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 912 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 914 */	NdrFcShort( 0x38 ),	/* 56 */
/* 916 */	NdrFcShort( 0xffec ),	/* Offset= -20 (896) */
/* 918 */	NdrFcShort( 0x0 ),	/* Offset= 0 (918) */
/* 920 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 922 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 924 */	0x40,		/* FC_STRUCTPAD4 */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 926 */	0x0,		/* 0 */
			NdrFcShort( 0xfe21 ),	/* Offset= -479 (448) */
			0x5b,		/* FC_END */
/* 930 */	
			0x12, 0x0,	/* FC_UP */
/* 932 */	NdrFcShort( 0xff16 ),	/* Offset= -234 (698) */
/* 934 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 936 */	0x1,		/* FC_BYTE */
			0x5c,		/* FC_PAD */
/* 938 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 940 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 942 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 944 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 946 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 948 */	0xb,		/* FC_HYPER */
			0x5c,		/* FC_PAD */
/* 950 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 952 */	0xa,		/* FC_FLOAT */
			0x5c,		/* FC_PAD */
/* 954 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 956 */	0xc,		/* FC_DOUBLE */
			0x5c,		/* FC_PAD */
/* 958 */	
			0x12, 0x0,	/* FC_UP */
/* 960 */	NdrFcShort( 0xfdc6 ),	/* Offset= -570 (390) */
/* 962 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 964 */	NdrFcShort( 0xfdc8 ),	/* Offset= -568 (396) */
/* 966 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 968 */	NdrFcShort( 0xfc60 ),	/* Offset= -928 (40) */
/* 970 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 972 */	NdrFcShort( 0xfdda ),	/* Offset= -550 (422) */
/* 974 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 976 */	NdrFcShort( 0xfde8 ),	/* Offset= -536 (440) */
/* 978 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 980 */	NdrFcShort( 0x2 ),	/* Offset= 2 (982) */
/* 982 */	
			0x12, 0x0,	/* FC_UP */
/* 984 */	NdrFcShort( 0x14 ),	/* Offset= 20 (1004) */
/* 986 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 988 */	NdrFcShort( 0x10 ),	/* 16 */
/* 990 */	0x6,		/* FC_SHORT */
			0x1,		/* FC_BYTE */
/* 992 */	0x1,		/* FC_BYTE */
			0x8,		/* FC_LONG */
/* 994 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 996 */	
			0x12, 0x0,	/* FC_UP */
/* 998 */	NdrFcShort( 0xfff4 ),	/* Offset= -12 (986) */
/* 1000 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 1002 */	0x2,		/* FC_CHAR */
			0x5c,		/* FC_PAD */
/* 1004 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 1006 */	NdrFcShort( 0x20 ),	/* 32 */
/* 1008 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1010 */	NdrFcShort( 0x0 ),	/* Offset= 0 (1010) */
/* 1012 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1014 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 1016 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 1018 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1020 */	NdrFcShort( 0xfc60 ),	/* Offset= -928 (92) */
/* 1022 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1024 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1026 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1028 */	NdrFcShort( 0x18 ),	/* 24 */
/* 1030 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1032 */	NdrFcShort( 0xfc50 ),	/* Offset= -944 (88) */
/* 1034 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1036 */	NdrFcShort( 0x2 ),	/* 2 */
/* 1038 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1040 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1042 */	NdrFcShort( 0xfd7a ),	/* Offset= -646 (396) */
/* 1044 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 1046 */	NdrFcShort( 0x38 ),	/* 56 */
/* 1048 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1050 */	NdrFcShort( 0xc ),	/* Offset= 12 (1062) */
/* 1052 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 1054 */	0x36,		/* FC_POINTER */
			0x36,		/* FC_POINTER */
/* 1056 */	0x36,		/* FC_POINTER */
			0x36,		/* FC_POINTER */
/* 1058 */	0x36,		/* FC_POINTER */
			0x36,		/* FC_POINTER */
/* 1060 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1062 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 1064 */	NdrFcShort( 0xfc16 ),	/* Offset= -1002 (62) */
/* 1066 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 1068 */	NdrFcShort( 0xfbfc ),	/* Offset= -1028 (40) */
/* 1070 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 1072 */	NdrFcShort( 0xfc24 ),	/* Offset= -988 (84) */
/* 1074 */	
			0x12, 0x0,	/* FC_UP */
/* 1076 */	NdrFcShort( 0xffd6 ),	/* Offset= -42 (1034) */
/* 1078 */	
			0x12, 0x0,	/* FC_UP */
/* 1080 */	NdrFcShort( 0xffd2 ),	/* Offset= -46 (1034) */
/* 1082 */	
			0x12, 0x0,	/* FC_UP */
/* 1084 */	NdrFcShort( 0xffce ),	/* Offset= -50 (1034) */
/* 1086 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1088 */	NdrFcLong( 0x10e ),	/* 270 */
/* 1092 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1094 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1096 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 1098 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 1100 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 1102 */	0x0,		/* 0 */
			0x46,		/* 70 */

			0x0
        }
    };

static const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ] = 
        {
            
            {
            HWND_UserSize
            ,HWND_UserMarshal
            ,HWND_UserUnmarshal
            ,HWND_UserFree
            },
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



/* Standard interface: __MIDL_itf_ConfigObjectProperty_0000, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}} */


/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IConfigObjectProperty, ver. 0.0,
   GUID={0x101228D6,0xD0B0,0x41D3,{0x8F,0x95,0x37,0x0E,0x88,0x8F,0x04,0x46}} */

#pragma code_seg(".orpc")
static const unsigned short IConfigObjectProperty_FormatStringOffsetTable[] =
    {
    0,
    38
    };

static const MIDL_STUBLESS_PROXY_INFO IConfigObjectProperty_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IConfigObjectProperty_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IConfigObjectProperty_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IConfigObjectProperty_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(5) _IConfigObjectPropertyProxyVtbl = 
{
    &IConfigObjectProperty_ProxyInfo,
    &IID_IConfigObjectProperty,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IConfigObjectProperty::ConfigObjectProperty */ ,
    (void *) (INT_PTR) -1 /* IConfigObjectProperty::get_IsConfigured */
};

const CInterfaceStubVtbl _IConfigObjectPropertyStubVtbl =
{
    &IID_IConfigObjectProperty,
    &IConfigObjectProperty_ServerInfo,
    5,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IConfigSequenceForObjectProperty, ver. 0.0,
   GUID={0xF7D428CF,0x8D5A,0x4B93,{0xA1,0x29,0xF1,0xD7,0xC1,0xED,0xE5,0x97}} */

#pragma code_seg(".orpc")
static const unsigned short IConfigSequenceForObjectProperty_FormatStringOffsetTable[] =
    {
    76,
    114,
    152
    };

static const MIDL_STUBLESS_PROXY_INFO IConfigSequenceForObjectProperty_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IConfigSequenceForObjectProperty_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IConfigSequenceForObjectProperty_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IConfigSequenceForObjectProperty_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(6) _IConfigSequenceForObjectPropertyProxyVtbl = 
{
    &IConfigSequenceForObjectProperty_ProxyInfo,
    &IID_IConfigSequenceForObjectProperty,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IConfigSequenceForObjectProperty::AddAction */ ,
    (void *) (INT_PTR) -1 /* IConfigSequenceForObjectProperty::AddActionsByCLSID */ ,
    (void *) (INT_PTR) -1 /* IConfigSequenceForObjectProperty::PrepareActions */
};

const CInterfaceStubVtbl _IConfigSequenceForObjectPropertyStubVtbl =
{
    &IID_IConfigSequenceForObjectProperty,
    &IConfigSequenceForObjectProperty_ServerInfo,
    6,
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
    0x6000169, /* MIDL Version 6.0.361 */
    0,
    UserMarshalRoutines,
    0,  /* notify & notify_flag routine table */
    0x1, /* MIDL flag */
    0, /* cs routines */
    0,   /* proxy/server info */
    0   /* Reserved5 */
    };

const CInterfaceProxyVtbl * _ConfigObjectProperty_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_IConfigSequenceForObjectPropertyProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IConfigObjectPropertyProxyVtbl,
    0
};

const CInterfaceStubVtbl * _ConfigObjectProperty_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_IConfigSequenceForObjectPropertyStubVtbl,
    ( CInterfaceStubVtbl *) &_IConfigObjectPropertyStubVtbl,
    0
};

PCInterfaceName const _ConfigObjectProperty_InterfaceNamesList[] = 
{
    "IConfigSequenceForObjectProperty",
    "IConfigObjectProperty",
    0
};


#define _ConfigObjectProperty_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _ConfigObjectProperty, pIID, n)

int __stdcall _ConfigObjectProperty_IID_Lookup( const IID * pIID, int * pIndex )
{
    IID_BS_LOOKUP_SETUP

    IID_BS_LOOKUP_INITIAL_TEST( _ConfigObjectProperty, 2, 1 )
    IID_BS_LOOKUP_RETURN_RESULT( _ConfigObjectProperty, 2, *pIndex )
    
}

const ExtendedProxyFileInfo ConfigObjectProperty_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _ConfigObjectProperty_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _ConfigObjectProperty_StubVtblList,
    (const PCInterfaceName * ) & _ConfigObjectProperty_InterfaceNamesList,
    0, // no delegation
    & _ConfigObjectProperty_IID_Lookup, 
    2,
    2,
    0, /* table of [async_uuid] interfaces */
    0, /* Filler1 */
    0, /* Filler2 */
    0  /* Filler3 */
};
#if _MSC_VER >= 1200
#pragma warning(pop)
#endif


#endif /* defined(_M_IA64) || defined(_M_AMD64)*/

