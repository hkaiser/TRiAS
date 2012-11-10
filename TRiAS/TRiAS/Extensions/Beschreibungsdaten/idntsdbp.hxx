// Precompiled Header für IDENTSDB.EXT ----------------------------------------
// File: IDNTSDBP.HXX

#if !defined(_IDNTSDB_HXX)
#define _IDNTSDB_HXX

#if _MSC_VER >= 1100
#include "IdentsDBConfig.h"
#include <TRiASConfig.h>
#endif // _MSC_VER 

#include <bool.h>
#include <xtensnm.hxx>

#include <windows.h>
#include <commdlg.h>
#include <ctl3d.h>
#include <errno.h>
#include <direct.h>
#include <tstring>
#include <stdlib.h>

#if !defined(WIN16)
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

#if _MSC_VER < 1100 && !defined(DECLSPEC_UUID)
#define DECLSPEC_UUID(x)
#endif // _MSC_VER < 1100 && !defined(DECLSPEC_UUID)

#include <ospace/com/smartif.h>
#include <triastlb.h>
#else
#include <dlgs.h> 
#include <tchar.h>
#include <shellapi.h>
#endif // WIN16

#include <ole2.h>

#include <commonvu.hxx>
#include <stddlg.hxx>

#include <numeditx.hxx>
#include <resstrg.h>

#include <errcodes.hxx>
#include <xtension.h>

#include <xtensnx.h>
#include <xtensnn.h>
#include <xtensnxx.h>

#include <ixtensn.hxx>
#include <xtencunk.hxx>
#include <xtsnprop.hxx>
#include <xtsnaux.hxx>

#include <bmpbox.hxx>

#include <containr.hxx>

#include <TRiASHelper.h>

///////////////////////////////////////////////////////////////////////////////
// Adresse des Endes einer Zeichenkette 
inline char *EOS (char *pBuffer) { return &pBuffer[strlen(pBuffer)]; }

#if !defined(DELETE_OBJ)
#define DELETE_OBJ(x) if(!(x)){}else{delete(x);(x)=NULL;}
#endif // DELETE_OBJ

///////////////////////////////////////////////////////////////////////////////
// notwendige Makros für solche Konstrukte wie '#pragma message(...)'
#define STR(x)		#x
#define STR2(x)		STR(x)
#define MESSAGE(desc)	message(__FILE__ "(" STR2(__LINE__) "): " desc)

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
	pv -> Clear();			//lint !e534, !e613
	return pv;
}

#endif // _IDNTSDB_HXX
