// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 13.02.2000 19:48:37 
//
// @doc
// @module StdAfx.h | Include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently and related definitions

#if !defined(AFX_STDAFX_H__36D78AE7_2F23_11D1_969F_00A024D6F582__INCLUDED_)
#define AFX_STDAFX_H__36D78AE7_2F23_11D1_969F_00A024D6F582__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "TRiASGDOConfig.h"
#include <TRiASConfig.h>

#include "Basetsd.h"		// 64-bit Definitionen

///////////////////////////////////////////////////////////////////////////////
// STL-related stuff 
#include <stl.h>

///////////////////////////////////////////////////////////////////////////////
// ATL-related stuff 

#include <atlbase.h>
#include <atlapp.h>
extern CAppModule _Module;
#include <atlcom.h>
#include <atlcomx.h>

#include <atlctl.h>
#include <atlwin.h>
#include <atlmisc.h>
#include <atlctrls.h>
#include <atlctrlx.h>
#include <atlcrack.h>
#include <atldlgs.h>

#include <ospace/com/smartif.h>
#include <Com/DefSmartIf.h>
#include <ospace/com/iterenum.h>

#include <stdio.h>

///////////////////////////////////////////////////////////////////////////////
// notwendige Makros für solche Konstrukte wie '#pragma message(...)'
#define STR(x)		#x
#define STR2(x)		STR(x)
#define	XMSG(xm,m)	message(__FILE__ "(" STR2(__LINE__) "): " xm ": " m)
#define TODO(m)		XMSG("TODO",m)
#define	CHECK(m)	XMSG("Überprüfen",m)
#define MFCDEL(m)	XMSG("MFCDEL",m)

///////////////////////////////////////////////////////////////////////////////
// sonstige Makros
#define _countof(x) (sizeof(x)/sizeof(x[0]))
#define DATATYPE_FROM_VT(x)	MAKELONG(0,(x))				// für Features

///////////////////////////////////////////////////////////////////////////////
// Zerlegen eines Objektes/Arrays
#if !defined(DELETE_OBJ)
#define DELETE_OBJ(x)	if(!x) {} else { delete(x); x = NULL; }
#endif // DELETE_OBJ

#if !defined(DELETE_VEC)
#define DELETE_VEC(x)	if(!x) {} else { delete[](x); x = NULL; }
#endif // DELETE_VEC

///////////////////////////////////////////////////////////////////////////////
// TRiASDB - Messagetabellen
#include "../TRiASDB/DBMSG.hmc"	

///////////////////////////////////////////////////////////////////////////////
// insbesondere wegen Safearray...
#include "McKinney/OleType.h"

///////////////////////////////////////////////////////////////////////////////
// externe Interfaces / Objekte...

///////////////////////////////////////////////////////////////////////////////
//	(1)	Geomedia
#include "GMObjects/GMObjects.h"

///////////////////////////////////////////////////////////////////////////////
//	(2)	TRiAS (mit Tricks und Kniffen, weil die Typelibrary offensichtlich nicht
//		ganz korrekt erzeugt worden ist
struct __declspec(uuid("710B2C36-890F-11D2-9EFB-006008447800"))
/* dual interface */ ITRiASBase;
_COM_SMARTPTR_TYPEDEF(ITRiASBase, __uuidof(ITRiASBase));
struct __declspec(uuid("710B2C36-890F-11D2-9EFB-006008447800"))
ITRiASBase : IDispatch
{
    //
    // Raw methods provided by interface
    //

    virtual HRESULT __stdcall get_Application (
        IDispatch * * pVal ) = 0;
    virtual HRESULT __stdcall put_Application (
        IDispatch * pVal ) = 0;
    virtual HRESULT __stdcall get_Parent (
        IDispatch * * pVal ) = 0;
    virtual HRESULT __stdcall put_Parent (
        IDispatch * pVal ) = 0;
};
extern "C" const IID __declspec(selectany) IID_ITRiASBase = 
	{0x710b2c36,0x890f,0x11d2,{0x9e,0xfb,0x00,0x60,0x08,0x44,0x78,0x00}};

struct __declspec(uuid("97993c78-5fe6-11d1-b9e6-080036d63803"))
/* dual interface */ ITRiASPropertyBase;
_COM_SMARTPTR_TYPEDEF(ITRiASPropertyBase, __uuidof(ITRiASPropertyBase));
struct __declspec(uuid("97993c78-5fe6-11d1-b9e6-080036d63803"))
ITRiASPropertyBase : IDispatch
{
    //
    // Raw methods provided by interface
    //

    virtual HRESULT __stdcall get_Properties (
        struct ITRiASProperties * * pVal ) = 0;
    virtual HRESULT __stdcall put_Properties (
        struct ITRiASProperties * pVal ) = 0;
    virtual HRESULT __stdcall get_Property (
        BSTR Which,
        struct ITRiASProperty * * pVal ) = 0;
    virtual HRESULT __stdcall CreateProperty (
        BSTR Which,
        struct ITRiASProperty * * Prop ) = 0;
    virtual HRESULT __stdcall RemoveProperty (
        BSTR Name ) = 0;
};
extern "C" const GUID __declspec(selectany) IID_ITRiASPropertyBase =
    {0x97993c78,0x5fe6,0x11d1,{0xb9,0xe6,0x08,0x00,0x36,0xd6,0x38,0x03}};

//#pragma CHECK("DTRiASBaseClass unverändert???")
struct __declspec(uuid("8de4e3e0-4d53-101b-aae1-e7e7e7e7e7e7"))
/* dual interface */ DTRiASBaseClass;
_COM_SMARTPTR_TYPEDEF(DTRiASBaseClass, __uuidof(DTRiASBaseClass));
struct __declspec(uuid("8de4e3e0-4d53-101b-aae1-e7e7e7e7e7e7"))
DTRiASBaseClass : IDispatch
{
    //
    // Raw methods provided by interface
    //

    virtual HRESULT __stdcall get_isA (
        long * RTTI ) = 0;
    virtual HRESULT __stdcall get_Parent (
        IDispatch * * Base ) = 0;
    virtual HRESULT __stdcall put_Parent (
        IDispatch * Base ) = 0;
    virtual HRESULT __stdcall get_Application (
        IDispatch * * App ) = 0;
    virtual HRESULT __stdcall put_Application (
        IDispatch * App ) = 0;
};
extern "C" const GUID __declspec(selectany) IID_DTRiASBaseClass =
    {0x8de4e3e0,0x4d53,0x101b,{0xaa,0xe1,0xe7,0xe7,0xe7,0xe7,0xe7,0xe7}};

#define TRiASEXTIFACE_IMPORT_OPTIONS	\
	raw_interfaces_only \
	raw_dispinterfaces	\
	no_namespace \
	named_guids
#define	TRiASEXTIFACE_EXCLUDES		\
	exclude("_LARGE_INTEGER")		\
	exclude("_ULARGE_INTEGER")		\
	exclude("_FILETIME")			\
	exclude("tagSTATSTG")			\
	exclude("IStream","ISequentialStream")	\
	exclude("IPersist","IPersistStreamInit","IPersistMemory" )	\
	exclude("ITRiASBase","ITRiASPropertyBase","DTRiASBaseClass")

#pragma warning (disable: 4192)		// automatically excluding 'bla' while importing type library 'bla'
#import "tlb/TErrTrk.tlb"	TRiASEXTIFACE_IMPORT_OPTIONS
#import "tlb/TDBGeo.tlb"	TRiASEXTIFACE_IMPORT_OPTIONS	\
	exclude("IPersist","IPersistMemory" )
#import "tlb/TRiASCS.tlb"	TRiASEXTIFACE_IMPORT_OPTIONS
#import "tlb/TRiASDB.tlb"	TRiASEXTIFACE_IMPORT_OPTIONS	\
	TRiASEXTIFACE_EXCLUDES

#import	"tlb/TRiASMDS.tlb"	TRiASEXTIFACE_IMPORT_OPTIONS

#import "tlb/Helper.tlb"	TRiASEXTIFACE_IMPORT_OPTIONS	\
	exclude("IComposeStringPairs")

///////////////////////////////////////////////////////////////////////////////
// die eigenen Zusätze
#include <Com/DebugFuncEntry.h>
#include <Com/ErrorMacros2.h>
#include <ospace/com/ComErrorMacros.h>

#include <Atl/AtlAggregate.h>
#include <Atl/atlbasex.h>
#include <Atl/DebugObjectCount.h>	// globale Objektzähler für einzelne Objekttypen
#include <Atl/ciid.h>

///////////////////////////////////////////////////////////////////////////////
// Properties
DefineSmartInterface(TRiASPropertyBase);			// WTRiASPropertyBase
DefineSmartInterface(TRiASProperty);				// WTRiASProperty
DefineSmartInterface(TRiASProperties);				// WTRiASProperties
DefineSmartInterface(TRiASPropertySupport);			// WTRiASPropertySupport

#define TYPELIB_TRIASDB_VERSION_MAJOR	TYPELIB_TRiASDB_VERSION_MAJOR
#define TYPELIB_TRIASDB_VERSION_MINOR	TYPELIB_TRiASDB_VERSION_MINOR
#include "../TRiASDB/PropertySupport.h"	
#include "../TRiASDB/PropertyBase.h"
#include "../TRiASDB/CPTRiASPropertyEvents.h"		// connection point
#include "../TRiASDB/TRiASDBGUIDs.h"

#include <Com/OleItemContainerSupport.h>
#include <Com/ClassFactoryCache.h>
#include <Com/ComBool.h>

#include <OneSizeHeapList.h>

/////////////////////////////////////////////////////////////////////
// Struktur für TRiAS-Headerentrys
typedef struct tagVALANDTYPE {
	CComVariant		m_val;
	PROPERTY_TYPE	m_type;
} VALANDTYPE;

///////////////////////////////////////////////////////////////////////////////
// hier jetzt benötigte STL-typedefs (Maps, Listen etc.)
#include <Com/BSTRHelpers.h>
#include <Com/GUIDHelpers.h>

typedef map<CComBSTR, CComBSTR> MapCB2CB;
typedef map<CComBSTR, CComVariant> MapCB2CV;
typedef map<CComBSTR, VALANDTYPE> MapCB2VALANDTYPE;

typedef vector<CComBSTR> vectorOfBSTR;

///////////////////////////////////////////////////////////////////////////////
// GUID's für TRiAS-Extensions
#include <xtsnguid.h>

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__36D78AE7_2F23_11D1_969F_00A024D6F582__INCLUDED)
