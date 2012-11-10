
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Fri Jul 19 09:14:24 2002
 */
/* Compiler settings for D:\TRiASDev.MVC\xtension\Segment\Segment.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __Segment_h__
#define __Segment_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __Segment_FWD_DEFINED__
#define __Segment_FWD_DEFINED__

#ifdef __cplusplus
typedef class Segment Segment;
#else
typedef struct Segment Segment;
#endif /* __cplusplus */

#endif 	/* __Segment_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 


#ifndef __Segment_LIBRARY_DEFINED__
#define __Segment_LIBRARY_DEFINED__

/* library Segment */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_Segment;

EXTERN_C const CLSID CLSID_Segment;

#ifdef __cplusplus

class DECLSPEC_UUID("BBD89FC4-352B-4A35-BFCD-ADF8D3BF2E3F")
Segment;
#endif
#endif /* __Segment_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


