
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Mon Mar 31 14:30:47 2003
 */
/* Compiler settings for D:\TRiASDev.MVC\xtension\LineTools\LineTools.idl:
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

#ifndef __LineTools_h__
#define __LineTools_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __LineTools_FWD_DEFINED__
#define __LineTools_FWD_DEFINED__

#ifdef __cplusplus
typedef class LineTools LineTools;
#else
typedef struct LineTools LineTools;
#endif /* __cplusplus */

#endif 	/* __LineTools_FWD_DEFINED__ */


#ifndef __CodeCheck_FWD_DEFINED__
#define __CodeCheck_FWD_DEFINED__

#ifdef __cplusplus
typedef class CodeCheck CodeCheck;
#else
typedef struct CodeCheck CodeCheck;
#endif /* __cplusplus */

#endif 	/* __CodeCheck_FWD_DEFINED__ */


#ifndef __CCodeStat_FWD_DEFINED__
#define __CCodeStat_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCodeStat CCodeStat;
#else
typedef struct CCodeStat CCodeStat;
#endif /* __cplusplus */

#endif 	/* __CCodeStat_FWD_DEFINED__ */


#ifndef __CodeLine_FWD_DEFINED__
#define __CodeLine_FWD_DEFINED__

#ifdef __cplusplus
typedef class CodeLine CodeLine;
#else
typedef struct CodeLine CodeLine;
#endif /* __cplusplus */

#endif 	/* __CodeLine_FWD_DEFINED__ */


#ifndef __ClsfyByCode_FWD_DEFINED__
#define __ClsfyByCode_FWD_DEFINED__

#ifdef __cplusplus
typedef class ClsfyByCode ClsfyByCode;
#else
typedef struct ClsfyByCode ClsfyByCode;
#endif /* __cplusplus */

#endif 	/* __ClsfyByCode_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "ProgInd2.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 


#ifndef __LineTools_LIBRARY_DEFINED__
#define __LineTools_LIBRARY_DEFINED__

/* library LineTools */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_LineTools;

EXTERN_C const CLSID CLSID_LineTools;

#ifdef __cplusplus

class DECLSPEC_UUID("169526E8-9BEA-4FA8-B47D-FAD4B7601B13")
LineTools;
#endif

EXTERN_C const CLSID CLSID_CodeCheck;

#ifdef __cplusplus

class DECLSPEC_UUID("F04E9701-1841-4817-BDAF-22A466F8E911")
CodeCheck;
#endif

EXTERN_C const CLSID CLSID_CCodeStat;

#ifdef __cplusplus

class DECLSPEC_UUID("5C31EB85-952F-484F-8EF6-E9564C012837")
CCodeStat;
#endif

EXTERN_C const CLSID CLSID_CodeLine;

#ifdef __cplusplus

class DECLSPEC_UUID("D2A96DE5-3EEC-491B-B35C-924660022503")
CodeLine;
#endif

EXTERN_C const CLSID CLSID_ClsfyByCode;

#ifdef __cplusplus

class DECLSPEC_UUID("E4A07A4C-E542-4149-9518-3043FE97B067")
ClsfyByCode;
#endif
#endif /* __LineTools_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


