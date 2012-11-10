#if !defined(_EXPORTIMPL_H__865F4EB5_6879_438C_A882_57B756AD4CF0__INCLUDED_)
#define _EXPORTIMPL_H__865F4EB5_6879_438C_A882_57B756AD4CF0__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"
#include "../ExportStdResrc.h"
#include "Export.hmc"
#include "Export.h"
#include "Strings.h"

#include <trias01m.hxx>
#include <versions.h>

#define _RISDB_NO_STRUCTS
#include <risdb.h>
#include <ristypes.hxx>

#include <triashelper.h>
#include <triastlb.h>

#define IDM_EXPORT_ORIG                 801		// ursprünglicher TRiAS-MenuID für Export

#pragma warning(disable: 4192)	//automatically excluding 'I...' while importing type library '...'

#import "tlb/ExportDef.tlb"	\
	raw_interfaces_only		\
	, raw_native_types		\
	, no_namespace			\
	, named_guids			\
	exclude("_tagOBJECTTYPE")

DefineSmartInterface(TRiASExtDataEngine)
DefineSmartInterface(TRiASOEProxy)

#import	"tlb/TRiASCS.tlb"	\
	raw_interfaces_only		\
	, raw_native_types		\
	, no_namespace			\
	, named_guids 

DefineSmartInterface(TRiASCS)
DefineSmartInterface(TRiASCSGCS)
DefineSmartInterface(TRiASCSPCS)
DefineSmartInterface(TRiASCSTransform)

#define _EXCLUDE_IPARSE_ETC_FROM_HELPER_TLH

#include <Com/PropertyActionBase.h>
#include <com/XMLInterTRiAS.h>

DefineSmartInterface(ProgressIndicator)
DefineSmartInterface(ProgressIndicator2)
DefineSmartInterface(PropertySequenceService)

DEFINE_GUID(CLSID_ProgressIndicator, 0x07963819L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);

/////////////////////////////////////////////////////////////////////////////
// 

HRESULT LoadEngines (map<CLSID,WTRiASExtDataEngine, less<CLSID> >& mapOfRegisteredEngines);
HRESULT TestExistsEngine();

class CVerifyExportLicense {
protected:
	static BOOL VerifyLicenseKey(BSTR bstr);
	static BOOL GetLicenseKey (DWORD, BSTR *pBstr);
	static BOOL IsLicenseValid();
};

/////////////////////////////////////////////////////////////////////////////
// Declaration diverser Klassen

#include <ienumobj.hxx>
#include <ospace/com/iterenum.h>
#include <ospace/std/set>

#if !defined(_ENUM_LONG_ENUMERATOR_DEFINED)
#define _ENUM_LONG_ENUMERATOR_DEFINED

DefineSortingEnumerator(LONG);		// definiert SEnumLONG
DefineSmartEnumerator2(LONG, __uuidof(IEnumLONG));		// definiert WEnumLONG (Wrapper für IEnum<LONG>)
DefineEnumInputIterator(LONG);		// definiert InEnumLONG
DefineEnumOutputIterator(LONG);		// definiert OutEnumLONG 

#endif // _ENUM_LONG_ENUMERATOR_DEFINED

///////////////////////////////////////////////////////////////////////////////
// sonstige nützliche Makros
#define _countof(array) (sizeof(array)/sizeof(array[0]))

#if !defined(DELETE_OBJ)
#define DELETE_OBJ(x)	if(!(x)){}else{delete(x);x=NULL;}
#define DELETE_VEC(x)	if(!(x)){}else{delete[](x);x=NULL;}
#endif // DELETE_OBJ

#if !defined(TX_TRY)
#define TX_TRY(x)		try{x;} catch(...) { _ASSERTE(NULL); }
#endif

#if _MSC_VER < 1100			// der neue midl generiert sowas
#define DECLSPEC_UUID(x)
#define DECLSPEC_SELECTANY
#else
#define DECLSPEC_SELECTANY __declspec(selectany)
#endif // _MSC_VER < 1100

#endif // !defined(_EXPORTIMPL_H__865F4EB5_6879_438C_A882_57B756AD4CF0__INCLUDED_)
