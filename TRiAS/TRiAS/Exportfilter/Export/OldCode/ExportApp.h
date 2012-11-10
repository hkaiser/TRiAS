/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu May 06 00:14:57 1999
 */
/* Compiler settings for D:\TRiASDev.MVC\EXPORT\Export\ExportApp.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __ExportApp_h__
#define __ExportApp_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __Export_FWD_DEFINED__
#define __Export_FWD_DEFINED__

#ifdef __cplusplus
typedef class Export Export;
#else
typedef struct Export Export;
#endif /* __cplusplus */

#endif 	/* __Export_FWD_DEFINED__ */


#ifndef __ExportPropertyAction_FWD_DEFINED__
#define __ExportPropertyAction_FWD_DEFINED__

#ifdef __cplusplus
typedef class ExportPropertyAction ExportPropertyAction;
#else
typedef struct ExportPropertyAction ExportPropertyAction;
#endif /* __cplusplus */

#endif 	/* __ExportPropertyAction_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "ProgInd2.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 


#ifndef __Export_LIBRARY_DEFINED__
#define __Export_LIBRARY_DEFINED__

/* library Export */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_Export;

EXTERN_C const CLSID CLSID_Export;

#ifdef __cplusplus

class DECLSPEC_UUID("BD1B0ED1-FFAF-11D2-94C3-0080C786297B")
Export;
#endif

EXTERN_C const CLSID CLSID_ExportPropertyAction;

#ifdef __cplusplus

class DECLSPEC_UUID("65C6A760-FFB4-11D2-94C5-0080C786297B")
ExportPropertyAction;
#endif
#endif /* __Export_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
