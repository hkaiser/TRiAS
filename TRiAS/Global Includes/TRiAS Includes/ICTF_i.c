
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Fri Dec 03 14:21:54 2004
 */
/* Compiler settings for CTF.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#if !defined(_M_IA64) && !defined(_M_AMD64)

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

MIDL_DEFINE_GUID(IID, IID__DGMPoint,0xCE361C90,0xB00C,0x11CF,0xAB,0xEF,0x08,0x00,0x36,0x01,0xB7,0x69);


MIDL_DEFINE_GUID(IID, IID__DGMPoints,0x4DBFC540,0xB33E,0x11CF,0xAB,0xEF,0x08,0x00,0x36,0x01,0xB7,0x69);


MIDL_DEFINE_GUID(IID, IID_ICoordTransform,0x0BDC3C18,0x503F,0x11D1,0x96,0xF0,0x00,0xA0,0x24,0xD6,0xF5,0x82);


MIDL_DEFINE_GUID(IID, IID_ICoordTransformInit,0x0BDC3C1B,0x503F,0x11d1,0x96,0xF0,0x00,0xA0,0x24,0xD6,0xF5,0x82);


MIDL_DEFINE_GUID(IID, IID_ICTFExContext,0x5FA91F05,0xA839,0x11D1,0xA0,0x60,0x00,0x60,0x97,0x55,0x66,0xB4);


MIDL_DEFINE_GUID(IID, IID_ICoordTransformEvents,0x764CA444,0xDFF6,0x11D1,0x86,0x08,0x00,0x60,0x08,0x75,0x13,0x8A);


MIDL_DEFINE_GUID(IID, LIBID_CoordTransLib,0x0BDC3C09,0x503F,0x11D1,0x96,0xF0,0x00,0xA0,0x24,0xD6,0xF5,0x82);


MIDL_DEFINE_GUID(CLSID, CLSID_DefaultCoordTrans,0x0BDC3C19,0x503F,0x11D1,0x96,0xF0,0x00,0xA0,0x24,0xD6,0xF5,0x82);


MIDL_DEFINE_GUID(CLSID, CLSID_ManageCoordParam,0x95F58F37,0xDF2C,0x11D1,0x86,0x06,0x00,0x60,0x08,0x75,0x13,0x8A);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



#endif /* !defined(_M_IA64) && !defined(_M_AMD64)*/


#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Fri Dec 03 14:21:54 2004
 */
/* Compiler settings for CTF.idl:
    Oicf, W1, Zp8, env=Win64 (32b run,appending)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#if defined(_M_IA64) || defined(_M_AMD64)

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

MIDL_DEFINE_GUID(IID, IID__DGMPoint,0xCE361C90,0xB00C,0x11CF,0xAB,0xEF,0x08,0x00,0x36,0x01,0xB7,0x69);


MIDL_DEFINE_GUID(IID, IID__DGMPoints,0x4DBFC540,0xB33E,0x11CF,0xAB,0xEF,0x08,0x00,0x36,0x01,0xB7,0x69);


MIDL_DEFINE_GUID(IID, IID_ICoordTransform,0x0BDC3C18,0x503F,0x11D1,0x96,0xF0,0x00,0xA0,0x24,0xD6,0xF5,0x82);


MIDL_DEFINE_GUID(IID, IID_ICoordTransformInit,0x0BDC3C1B,0x503F,0x11d1,0x96,0xF0,0x00,0xA0,0x24,0xD6,0xF5,0x82);


MIDL_DEFINE_GUID(IID, IID_ICTFExContext,0x5FA91F05,0xA839,0x11D1,0xA0,0x60,0x00,0x60,0x97,0x55,0x66,0xB4);


MIDL_DEFINE_GUID(IID, IID_ICoordTransformEvents,0x764CA444,0xDFF6,0x11D1,0x86,0x08,0x00,0x60,0x08,0x75,0x13,0x8A);


MIDL_DEFINE_GUID(IID, LIBID_CoordTransLib,0x0BDC3C09,0x503F,0x11D1,0x96,0xF0,0x00,0xA0,0x24,0xD6,0xF5,0x82);


MIDL_DEFINE_GUID(CLSID, CLSID_DefaultCoordTrans,0x0BDC3C19,0x503F,0x11D1,0x96,0xF0,0x00,0xA0,0x24,0xD6,0xF5,0x82);


MIDL_DEFINE_GUID(CLSID, CLSID_ManageCoordParam,0x95F58F37,0xDF2C,0x11D1,0x86,0x06,0x00,0x60,0x08,0x75,0x13,0x8A);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



#endif /* defined(_M_IA64) || defined(_M_AMD64)*/

