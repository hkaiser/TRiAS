
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 5.03.0280 */
/* at Thu Sep 14 21:25:18 2000
 */
/* Compiler settings for D:\TRiASDev.MVC\TRiASMI\TRiASMI.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32 (32b run), ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#if !defined(_M_IA64) && !defined(_M_AXP64)

#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, LIBID_TRiASMILib,0xEE31A3CF,0x69DE,0x4628,0x91,0xC8,0x01,0x51,0x3D,0x8B,0x9A,0x70);


MIDL_DEFINE_GUID(CLSID, CLSID_TRiASMIDBEngine,0xB27268B8,0x2598,0x44A4,0x92,0x28,0x03,0x60,0x2B,0x87,0x67,0xC9);


MIDL_DEFINE_GUID(CLSID, CLSID_TRiASMIDatabase,0xDA3DD80A,0x6589,0x4616,0xAD,0xBE,0x2D,0x91,0x5D,0x90,0x68,0x9A);


MIDL_DEFINE_GUID(CLSID, CLSID_TRiASMIObjectsCollection,0x27BAAB3D,0xF0E6,0x47E4,0x9B,0x00,0xC6,0xCA,0x9C,0x43,0xE4,0x9A);


MIDL_DEFINE_GUID(CLSID, CLSID_TRiASMIObjects,0x66E0F829,0x6877,0x4B11,0x87,0x8F,0x21,0x8F,0x4E,0x7B,0x00,0xBF);


MIDL_DEFINE_GUID(CLSID, CLSID_TRiASMIObject,0x434A57DC,0x7F5C,0x4E4F,0x95,0x02,0x6E,0x27,0x3D,0xEC,0x03,0xFA);


MIDL_DEFINE_GUID(CLSID, CLSID_TRiASMIFeatures,0x4D3C4EB9,0xE634,0x4945,0x83,0xAB,0xF9,0xE1,0x14,0xA6,0x16,0xF3);


MIDL_DEFINE_GUID(CLSID, CLSID_TRiASMIFeature,0xFABC07D6,0x1ADD,0x417E,0x97,0xB3,0x71,0x97,0x71,0xF4,0xD0,0x10);


MIDL_DEFINE_GUID(CLSID, CLSID_TRiASMIGeoFeatures,0x64556500,0xCDC7,0x457B,0xAB,0x89,0x53,0x0B,0xFC,0xEB,0x64,0xFB);


MIDL_DEFINE_GUID(CLSID, CLSID_TRiASMIGeoFeature,0x94D106DF,0x72D1,0x4016,0xBA,0xFA,0xED,0xE2,0x13,0x5C,0x3D,0xD6);


MIDL_DEFINE_GUID(CLSID, CLSID_TRiASMICursorProperty,0x41F06F7A,0xE993,0x4C7F,0x85,0xCC,0x41,0xDE,0x75,0xC5,0x88,0x9E);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



#endif /* !defined(_M_IA64) && !defined(_M_AXP64)*/

