
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


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


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __TRiASMI_h__
#define __TRiASMI_h__

/* Forward Declarations */ 

#ifndef __TRiASMIDBEngine_FWD_DEFINED__
#define __TRiASMIDBEngine_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASMIDBEngine TRiASMIDBEngine;
#else
typedef struct TRiASMIDBEngine TRiASMIDBEngine;
#endif /* __cplusplus */

#endif 	/* __TRiASMIDBEngine_FWD_DEFINED__ */


#ifndef __TRiASMIDatabase_FWD_DEFINED__
#define __TRiASMIDatabase_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASMIDatabase TRiASMIDatabase;
#else
typedef struct TRiASMIDatabase TRiASMIDatabase;
#endif /* __cplusplus */

#endif 	/* __TRiASMIDatabase_FWD_DEFINED__ */


#ifndef __TRiASMIObjectsCollection_FWD_DEFINED__
#define __TRiASMIObjectsCollection_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASMIObjectsCollection TRiASMIObjectsCollection;
#else
typedef struct TRiASMIObjectsCollection TRiASMIObjectsCollection;
#endif /* __cplusplus */

#endif 	/* __TRiASMIObjectsCollection_FWD_DEFINED__ */


#ifndef __TRiASMIObjects_FWD_DEFINED__
#define __TRiASMIObjects_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASMIObjects TRiASMIObjects;
#else
typedef struct TRiASMIObjects TRiASMIObjects;
#endif /* __cplusplus */

#endif 	/* __TRiASMIObjects_FWD_DEFINED__ */


#ifndef __TRiASMIObject_FWD_DEFINED__
#define __TRiASMIObject_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASMIObject TRiASMIObject;
#else
typedef struct TRiASMIObject TRiASMIObject;
#endif /* __cplusplus */

#endif 	/* __TRiASMIObject_FWD_DEFINED__ */


#ifndef __TRiASMIFeatures_FWD_DEFINED__
#define __TRiASMIFeatures_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASMIFeatures TRiASMIFeatures;
#else
typedef struct TRiASMIFeatures TRiASMIFeatures;
#endif /* __cplusplus */

#endif 	/* __TRiASMIFeatures_FWD_DEFINED__ */


#ifndef __TRiASMIFeature_FWD_DEFINED__
#define __TRiASMIFeature_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASMIFeature TRiASMIFeature;
#else
typedef struct TRiASMIFeature TRiASMIFeature;
#endif /* __cplusplus */

#endif 	/* __TRiASMIFeature_FWD_DEFINED__ */


#ifndef __TRiASMIGeoFeatures_FWD_DEFINED__
#define __TRiASMIGeoFeatures_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASMIGeoFeatures TRiASMIGeoFeatures;
#else
typedef struct TRiASMIGeoFeatures TRiASMIGeoFeatures;
#endif /* __cplusplus */

#endif 	/* __TRiASMIGeoFeatures_FWD_DEFINED__ */


#ifndef __TRiASMIGeoFeature_FWD_DEFINED__
#define __TRiASMIGeoFeature_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASMIGeoFeature TRiASMIGeoFeature;
#else
typedef struct TRiASMIGeoFeature TRiASMIGeoFeature;
#endif /* __cplusplus */

#endif 	/* __TRiASMIGeoFeature_FWD_DEFINED__ */


#ifndef __TRiASMICursorProperty_FWD_DEFINED__
#define __TRiASMICursorProperty_FWD_DEFINED__

#ifdef __cplusplus
typedef class TRiASMICursorProperty TRiASMICursorProperty;
#else
typedef struct TRiASMICursorProperty TRiASMICursorProperty;
#endif /* __cplusplus */

#endif 	/* __TRiASMICursorProperty_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 


#ifndef __TRiASMILib_LIBRARY_DEFINED__
#define __TRiASMILib_LIBRARY_DEFINED__

/* library TRiASMILib */
/* [helpstring][lcid][version][uuid] */ 


enum TRIASMI_VERSIONS
    {	TYPELIB_TRIASMI_MAJOR_VERSION	= 1,
	TYPELIB_TRIASMI_MINOR_VERSION	= 0
    };

EXTERN_C const IID LIBID_TRiASMILib;

EXTERN_C const CLSID CLSID_TRiASMIDBEngine;

#ifdef __cplusplus

class DECLSPEC_UUID("B27268B8-2598-44A4-9228-03602B8767C9")
TRiASMIDBEngine;
#endif

EXTERN_C const CLSID CLSID_TRiASMIDatabase;

#ifdef __cplusplus

class DECLSPEC_UUID("DA3DD80A-6589-4616-ADBE-2D915D90689A")
TRiASMIDatabase;
#endif

EXTERN_C const CLSID CLSID_TRiASMIObjectsCollection;

#ifdef __cplusplus

class DECLSPEC_UUID("27BAAB3D-F0E6-47E4-9B00-C6CA9C43E49A")
TRiASMIObjectsCollection;
#endif

EXTERN_C const CLSID CLSID_TRiASMIObjects;

#ifdef __cplusplus

class DECLSPEC_UUID("66E0F829-6877-4B11-878F-218F4E7B00BF")
TRiASMIObjects;
#endif

EXTERN_C const CLSID CLSID_TRiASMIObject;

#ifdef __cplusplus

class DECLSPEC_UUID("434A57DC-7F5C-4E4F-9502-6E273DEC03FA")
TRiASMIObject;
#endif

EXTERN_C const CLSID CLSID_TRiASMIFeatures;

#ifdef __cplusplus

class DECLSPEC_UUID("4D3C4EB9-E634-4945-83AB-F9E114A616F3")
TRiASMIFeatures;
#endif

EXTERN_C const CLSID CLSID_TRiASMIFeature;

#ifdef __cplusplus

class DECLSPEC_UUID("FABC07D6-1ADD-417E-97B3-719771F4D010")
TRiASMIFeature;
#endif

EXTERN_C const CLSID CLSID_TRiASMIGeoFeatures;

#ifdef __cplusplus

class DECLSPEC_UUID("64556500-CDC7-457B-AB89-530BFCEB64FB")
TRiASMIGeoFeatures;
#endif

EXTERN_C const CLSID CLSID_TRiASMIGeoFeature;

#ifdef __cplusplus

class DECLSPEC_UUID("94D106DF-72D1-4016-BAFA-EDE2135C3DD6")
TRiASMIGeoFeature;
#endif

EXTERN_C const CLSID CLSID_TRiASMICursorProperty;

#ifdef __cplusplus

class DECLSPEC_UUID("41F06F7A-E993-4C7F-85CC-41DE75C5889E")
TRiASMICursorProperty;
#endif
#endif /* __TRiASMILib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


