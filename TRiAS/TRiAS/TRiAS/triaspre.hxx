///////////////////////////////////////////////////////////////////////////
// Precompiled Header für TRiAS®
// Triaspre.hxx

#if !defined(_TRIASPRE_HXX__A37D8266_4A3F_11d1_96DC_00A024D6F582__INCLUDED_)
#define _TRIASPRE_HXX__A37D8266_4A3F_11d1_96DC_00A024D6F582__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#pragma warning (disable: 4304 4114 4786)

#include "TRiASMainConfig.h"
#include <TRiASConfig.h>
#include "TRiASMainConfigVersion.h"

#include <bool.h>

#include <ctfm.hxx>		// Manifestkonstanten
#include <trias01m.hxx>
#include <trias02m.hxx>
#include <trias03m.hxx>
#include <triasm.hxx>

#include <dbconfig.h>

///////////////////////////////////////////////////////////////////////////////
// notwendige Makros für solche Konstrukte wie '#pragma message(...)'
#define STR(x)		#x
#define STR2(x)		STR(x)
#define MESSAGE(desc)	message(__FILE__ "(" STR2(__LINE__) ") : " #desc)
#define TODO(desc)		message(__FILE__ "(" STR2(__LINE__) ") : TODO: " #desc)

#if !defined(_countof)
#define _countof(x)	(sizeof(x)/sizeof(x[0]))
#endif // _countof

///////////////////////////////////////////////////////////////////////////////
//
#include <windows.h>
#include <windowsx.h>
#include <commdlg.h>

#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <ctype.h>
#include <ctl3d.h>

#include <ole2.h>
#include <objbase.h>
#include <comcat.h>

#include <d_lib/d_lib.h>

#define _RISDB_NO_STRUCTS
#include <protos.h>
#include <funcs02.h>
#include <dbdtempl.h>

#include <xtension.h>
#include <xtensnx.h>
#include <xtensnn.h>

#include <tstring>		// STDCPP

///////////////////////////////////////////////////////////////////////////////
// ATL-related stuff 
#if defined(__ATL_20_USED__)
using namespace ::ospace::std;
#include <atl20.h>
#elif defined(__ATL_11_USED__)
#include <atl11.h>
#else
#error "Must define '__ATL_11_USED__ or __ATL_20_USED__'"
#endif // __ATL__
extern CComModule _Module;		// Hauptmodule für ATL

///////////////////////////////////////////////////////////////////////////////
// STL related stuff
#include <ospace/std/list>
#include <ospace/com/smartif.h>

#include <commonvu.hxx>
#include <stddlg.hxx>
#include <clipbrd.hxx>
#include <drawobj.hxx>
#include <cvext.hxx>
#include <containr.hxx>
#include <dcreator.hxx>
#include <deltree.hxx>
#include <epen.hxx>

#include <TRiASDB.h>
#include <TRiASHelper.h>

#include <ixtensn.hxx>

#include <resstrg.h>
#include <ristypes.hxx>
#include <errcodes.hxx>
#include <errinst.hxx>

#if defined(_FORCE_LEGACY_CODE)
#include <pbd.hxx>
#include <merkmal.hxx>
#include <geo_obj.hxx>
#include <geo_obj1.hxx>
#else
#include <GeoObjekt.h>
#endif // _FORCE_LEGACY_CODE

#include <geotext.hxx>
#include <komplex.hxx>
#include <transfrm.hxx>

#include <attribs.hxx>
#include <db.hxx>
#include <hdrentry.hxx>
#if defined(_FORCE_LEGACY_CODE)
#include <ident.hxx>
#endif // _FORCE_LEGACY_CODE

#include <objliste.hxx>
#include <profile.hxx>
#include <dllbind.hxx>
#include <objmtree.hxx>
#include <eieruhr.hxx>
#include <ctf.hxx>
#include <numedit.hxx>
#include <dblnumed.hxx>
#include <dblpair.hxx>
#include <muscroll.hxx>
#include <spinctrl.hxx>
#include <bmpbox.hxx>
#include <strdup.hxx>
#include <dbasrt02.h>
#include <funcs03.h>

#include <oddlgwin.hxx>
#include <ownlist.hxx>
#include <ownliste.hxx>

#if !defined(_FORCE_LEGACY_CODE)
#include "Identifikator.h"
#endif // !defined(_FORCE_LEGACY_CODE)
#include "clbmpobj.hxx"
#include "draw_obj.hxx"
#include "drw_obj1.hxx"
#include "iris.hxx"

///////////////////////////////////////////////////////////////////////////////
// Helper, um reine [out] Parameter sauber zu halten
inline BSTR *CLEARED (BSTR *pbstr)
{
	_ASSERTE(NULL != pbstr);
	if (NULL != pbstr) {
		::SysFreeString(*pbstr);
		*pbstr = NULL;
	}
	return pbstr;
}

inline VARIANT *CLEARED (CComVariant *pv)
{
	_ASSERTE(NULL != pv);
	pv -> Clear();
	return pv;
}

#endif // !defined(_TRIASPRE_HXX__A37D8266_4A3F_11d1_96DC_00A024D6F582__INCLUDED_)
