/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Oct 22 10:52:08 2001
 */
/* Compiler settings for D:\TRiASDev.MVC\TRiASHP\TRiASHP.idl:
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

#ifndef __TRiASHP_h__
#define __TRiASHP_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __TRiASHPDBEngine_FWD_DEFINED__
#define __TRiASHPDBEngine_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASHPDBEngine TRiASHPDBEngine;
#else
typedef struct TRiASHPDBEngine TRiASHPDBEngine;
#endif /* __cplusplus */

#endif 	/* __TRiASHPDBEngine_FWD_DEFINED__ */


#ifndef __TRiASHPDatabase_FWD_DEFINED__
#define __TRiASHPDatabase_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASHPDatabase TRiASHPDatabase;
#else
typedef struct TRiASHPDatabase TRiASHPDatabase;
#endif /* __cplusplus */

#endif 	/* __TRiASHPDatabase_FWD_DEFINED__ */


#ifndef __TRiASHPObjectsCollection_FWD_DEFINED__
#define __TRiASHPObjectsCollection_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASHPObjectsCollection TRiASHPObjectsCollection;
#else
typedef struct TRiASHPObjectsCollection TRiASHPObjectsCollection;
#endif /* __cplusplus */

#endif 	/* __TRiASHPObjectsCollection_FWD_DEFINED__ */


#ifndef __TRiASHPObjects_FWD_DEFINED__
#define __TRiASHPObjects_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASHPObjects TRiASHPObjects;
#else
typedef struct TRiASHPObjects TRiASHPObjects;
#endif /* __cplusplus */

#endif 	/* __TRiASHPObjects_FWD_DEFINED__ */


#ifndef __TRiASHPObject_FWD_DEFINED__
#define __TRiASHPObject_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASHPObject TRiASHPObject;
#else
typedef struct TRiASHPObject TRiASHPObject;
#endif /* __cplusplus */

#endif 	/* __TRiASHPObject_FWD_DEFINED__ */


#ifndef __TRiASHPFeatures_FWD_DEFINED__
#define __TRiASHPFeatures_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASHPFeatures TRiASHPFeatures;
#else
typedef struct TRiASHPFeatures TRiASHPFeatures;
#endif /* __cplusplus */

#endif 	/* __TRiASHPFeatures_FWD_DEFINED__ */


#ifndef __TRiASHPFeature_FWD_DEFINED__
#define __TRiASHPFeature_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASHPFeature TRiASHPFeature;
#else
typedef struct TRiASHPFeature TRiASHPFeature;
#endif /* __cplusplus */

#endif 	/* __TRiASHPFeature_FWD_DEFINED__ */


#ifndef __TRiASHPGeoFeatures_FWD_DEFINED__
#define __TRiASHPGeoFeatures_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASHPGeoFeatures TRiASHPGeoFeatures;
#else
typedef struct TRiASHPGeoFeatures TRiASHPGeoFeatures;
#endif /* __cplusplus */

#endif 	/* __TRiASHPGeoFeatures_FWD_DEFINED__ */


#ifndef __TRiASHPGeoFeature_FWD_DEFINED__
#define __TRiASHPGeoFeature_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASHPGeoFeature TRiASHPGeoFeature;
#else
typedef struct TRiASHPGeoFeature TRiASHPGeoFeature;
#endif /* __cplusplus */

#endif 	/* __TRiASHPGeoFeature_FWD_DEFINED__ */


#ifndef __TRiASHPCursorProperty_FWD_DEFINED__
#define __TRiASHPCursorProperty_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASHPCursorProperty TRiASHPCursorProperty;
#else
typedef struct TRiASHPCursorProperty TRiASHPCursorProperty;
#endif /* __cplusplus */

#endif 	/* __TRiASHPCursorProperty_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 


#ifndef __TRiASHPLib_LIBRARY_DEFINED__
#define __TRiASHPLib_LIBRARY_DEFINED__

/* library TRiASHPLib */
/* [helpstring][lcid][version][uuid] */ 


enum TRIASHP_VERSIONS
    {	TYPELIB_TRIASHP_MAJOR_VERSION	= 1,
	TYPELIB_TRIASHP_MINOR_VERSION	= 0
    };

EXTERN_C const IID LIBID_TRiASHPLib;

EXTERN_C const CLSID CLSID_TRiASHPDBEngine;

#ifdef __cplusplus

class DECLSPEC_UUID("4597A774-90C5-4D8E-927E-B9CDA8C4EB2A")
TRiASHPDBEngine;
#endif

EXTERN_C const CLSID CLSID_TRiASHPDatabase;

#ifdef __cplusplus

class DECLSPEC_UUID("276A84C8-F3E9-4A2E-9318-1B258A5EC435")
TRiASHPDatabase;
#endif

EXTERN_C const CLSID CLSID_TRiASHPObjectsCollection;

#ifdef __cplusplus

class DECLSPEC_UUID("741FB831-1001-479C-844A-E48BE38CF0AB")
TRiASHPObjectsCollection;
#endif

EXTERN_C const CLSID CLSID_TRiASHPObjects;

#ifdef __cplusplus

class DECLSPEC_UUID("8DB4929F-EE82-4D1B-9EAA-7EE526E8046D")
TRiASHPObjects;
#endif

EXTERN_C const CLSID CLSID_TRiASHPObject;

#ifdef __cplusplus

class DECLSPEC_UUID("0E7ABCCA-5EA3-4FD0-A037-D3716E4C3D32")
TRiASHPObject;
#endif

EXTERN_C const CLSID CLSID_TRiASHPFeatures;

#ifdef __cplusplus

class DECLSPEC_UUID("749773FD-C7E8-4FD7-8AFF-29E5C37C4795")
TRiASHPFeatures;
#endif

EXTERN_C const CLSID CLSID_TRiASHPFeature;

#ifdef __cplusplus

class DECLSPEC_UUID("50235297-921D-4507-BD47-83F32B13670E")
TRiASHPFeature;
#endif

EXTERN_C const CLSID CLSID_TRiASHPGeoFeatures;

#ifdef __cplusplus

class DECLSPEC_UUID("366F3BB4-2A84-45BC-9C8C-F917FC9E7713")
TRiASHPGeoFeatures;
#endif

EXTERN_C const CLSID CLSID_TRiASHPGeoFeature;

#ifdef __cplusplus

class DECLSPEC_UUID("708DDEBA-13AF-463E-B727-0936F7C84EBA")
TRiASHPGeoFeature;
#endif

EXTERN_C const CLSID CLSID_TRiASHPCursorProperty;

#ifdef __cplusplus

class DECLSPEC_UUID("B27ED5F8-220F-41ED-ACA1-BEAA3AF3819C")
TRiASHPCursorProperty;
#endif
#endif /* __TRiASHPLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
