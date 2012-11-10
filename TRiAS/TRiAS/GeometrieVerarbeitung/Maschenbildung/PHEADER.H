// Precompiled Header für LINVER.EXT -----------------------------------------
// File: pheader.h

#if !defined(_PHEADER_H)
#define _PHEADER_H

#include <bool.h>

#if _MSC_VER >= 1100		
#include "LinVerConfig.h"
#include <TRiASConfig.h>
#endif // _MSC_VER 

#include <afxole.h>				// MFC-Core, windows.h

#include <stdio.h>
#include <stdlib.h>

#ifndef EXPORT02
#define EXPORT02
#endif

#ifndef _TRIAS02_ENTRY
#define _TRIAS02_ENTRY
#endif

//#include <new>
#include <tstring>
#include <xtension.h>	
#include <ixtensn.hxx>
#include <xtensnx.h>
#if defined(__ATL_20_USED__)
#include <atl20.h>
#elif defined(__ATL_11_USED__)
#include <atl11.h>
#else
#error "Must define '__ATL_11_USED__ or __ATL_20_USED__'"
#endif // __ATL__
#include <xtencatl.hxx>			// CTriasExtension			  
#include <ipropseq.hxx>
#include <containr.hxx>			// CSyncMonitor	

#include <hpp/errcodesodbc.hxx>         // FehlerCodes
//#include <ristypes.hxx>			// KoOrd
//#include <hpp/protos.h>				// DELETE ()
//#include <errcodes.hxx>			// TRIAS-Fehlerkodes

#include "objcont.hpp"			// CObjecContainer	

extern CComModule _Module;

//	Konstanten
const short MaxUseCnt = 2;			// max. Benutzung einer Linie zur Bildung einer Masche
const short MinAreaVerticeCnt = 4;	// min. Anzahl der Stützpunkte einer Fläche
const ULONG ulEps = 2;				// Epsilon für Gleichheit zweier Punkte (#WM990622)


//	Konvertierung von double nach long
inline long DtoL (double D)
{
	if (D > 0)
		return (long)(D + 0.5);
	else
		return (long)(D - 0.5);
}


//	Enumeratoren
enum UnionEnum { NotUnion, FlaechenUnion, LinienUnion };
enum LineUionEnum { NoAppend, LastFirst, LastLast, FirstLast, FirstFirst };

//	Prototypen
extern char *DtoA (double Wert, char *String, const char *Format = NULL); 

// fje
#if _MSC_VER < 1100 && !defined(DECLSPEC_UUID)
#define DECLSPEC_UUID(x)
#endif // _MSC_VER < 1100 && !defined(DECLSPEC_UUID)
// fje

#if !defined(DELETE_OBJ)
#define DELETE_OBJ(x) if(!(x)){}else{delete(x); (x)=NULL;}
#endif // !DELETE_OBJ

#if !defined(DELETE_VEC)
#define DELETE_VEC(x)	if(NULL==x){}else{delete[](x);(x)=NULL;}
#endif // !defined(DELETE_VEC)

#endif // _PHEADER_H



